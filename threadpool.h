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
    //���������������̳߳���
    void addTask(TaskPtr task);
    //�ر��̳߳�
    void shutdown();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

private:
    //�����߳�,���̳߳�������߳�
    void addThread();
    //ɾ���߳�,ɾ���̳߳��е��߳�
    void delThread();

    //��֤ԭ�Ӳ���
    atomic_bool m_finish; //�̳߳ؽ�����־

    //�洢�����߳���Ϣ
    unordered_map<thread::id, ThreadPtr> m_thread;

    thread m_managerThread;//�����߳�

    TaskQueue m_taskQue;//�����û��Զ����������
    
    int m_max;//����߳���
    int m_min;//��С�߳���
};
#endif




