#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__
#include "taskqueue.h"
#include <atomic>
#include <memory>
#include <thread>
using std::thread;
using std::atomic_bool;     //声明原子操作类型
using std::atomic_int;      //声明原子操作类型
using std::this_thread::sleep_for;
using std::this_thread::get_id; 
using std::cout;
using std::endl;

class WorkThread {
public:
    
    constexpr static int STATE_WAIT = 1;
    constexpr static int STATE_WORK = 2;
    constexpr static int STATE_EXIT = 3;

    WorkThread(TaskQueue& taskQue);
    ~WorkThread();
    int getState() const;
    void finish();
    thread::id getId() const;
    thread& getCurrentThread();

private:
    TaskQueue& m_taskQue;   //任务队列
    atomic_int m_state;     //判断当前线程状态
    atomic_bool m_finish;   //线程结束标值
    thread m_thread;        //保存当前线程地址
};

using ThreadPtr = std::shared_ptr<WorkThread>;

#endif