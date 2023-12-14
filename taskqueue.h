#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include "task.hpp"
#include "functask.h"
#include <queue>
#include <mutex>
using std::queue; 
using std::mutex;
using std::lock_guard;
using std::unique_lock;
using std::condition_variable;
//�������
class TaskQueue{
public:
    TaskQueue() = default;
    ~TaskQueue() = default;
    //�������������
    void addTask(TaskPtr task);
    //������ȡ������
    TaskPtr getTask();
    //��ö���������ĸ���
    int getSize();
    //�ж϶����Ƿ�Ϊ��
    bool isEmpty();

private:
    queue<TaskPtr> m_tasks;     //������б�������
    mutex m_mutex;              //���廥����
    int m_capacity = 100;       //�����������������������ֵ
    condition_variable m_producerCond;
    condition_variable m_consumerCond;
};
#endif