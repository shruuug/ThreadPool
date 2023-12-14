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
//任务队列
class TaskQueue{
public:
    TaskQueue() = default;
    ~TaskQueue() = default;
    //队列中添加任务
    void addTask(TaskPtr task);
    //队列中取出任务
    TaskPtr getTask();
    //获得队列中任务的个数
    int getSize();
    //判断队列是否为空
    bool isEmpty();

private:
    queue<TaskPtr> m_tasks;     //定义队列保存任务
    mutex m_mutex;              //定义互斥锁
    int m_capacity = 100;       //定义阻塞队列中任务数最大值
    condition_variable m_producerCond;
    condition_variable m_consumerCond;
};
#endif