#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include "workthread.h"
#include <atomic>
#include <unordered_map>
using std::atomic_bool;
using std::unordered_map;
using std::make_shared;
class ThreadPool {
public:
    ThreadPool(int min = 10, int max = 50);
    ~ThreadPool();
    //添加任务队列任务到线程池中
    void addTask(TaskPtr task);
    //关闭线程池
    void shutdown();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

private:
    //创建线程,向线程池中添加线程
    void addThread();
    //删除线程,删除线程池中的线程
    void delThread();

    //保证原子操作
    atomic_bool m_finish; //线程池结束标志

    //存储工作线程信息
    unordered_map<thread::id, ThreadPtr> m_thread;

    thread m_managerThread;//管理线程

    TaskQueue m_taskQue;//创建用户自定义任务对象
    
    int m_max;//最大线程数
    int m_min;//最小线程数
};
#endif




