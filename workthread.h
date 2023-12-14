#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__
#include "taskqueue.h"
#include <atomic>
#include <memory>
#include <thread>
using std::thread;
using std::atomic_bool;     //����ԭ�Ӳ�������
using std::atomic_int;      //����ԭ�Ӳ�������
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
    TaskQueue& m_taskQue;   //�������
    atomic_int m_state;     //�жϵ�ǰ�߳�״̬
    atomic_bool m_finish;   //�߳̽�����ֵ
    thread m_thread;        //���浱ǰ�̵߳�ַ
};

using ThreadPtr = std::shared_ptr<WorkThread>;

#endif