#include "taskqueue.h"

//添加任务
void TaskQueue::addTask(TaskPtr task)
{
    unique_lock<mutex> lock(m_mutex);

    while (m_tasks.size() == m_capacity)
    {
        m_producerCond.wait(lock);
    }

    printf("--- add task :[%s] in ---\n", task->getName().c_str());
    m_tasks.push(task);
    m_producerCond.notify_one();
    lock.unlock();
}

//获取任务
TaskPtr TaskQueue::getTask()
{
    unique_lock<mutex> lock(m_mutex);

    while (m_tasks.empty())
    {
        m_consumerCond.wait(lock);
    }
    
    TaskPtr task = m_tasks.front(); 
    m_tasks.pop();
    m_consumerCond.notify_one();
    return task;
}

int TaskQueue::getSize() {
    lock_guard<mutex> lock(m_mutex);
    return m_tasks.size();
}

bool TaskQueue::isEmpty()
{
    lock_guard<mutex> lock(m_mutex); 
    return m_tasks.empty();
}