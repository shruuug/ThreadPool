#ifndef __TASK_H__
#define __TASK_H__
#include <iostream>
#include <memory>
using std::string;
using std::shared_ptr;
//用户自定义的任务类,用户后期可自定义任务，继承重写run函数来添加信息
class Task
{
public:
    //这里设计了一个 stirng 保存任务名字
    Task(const string& name = "") :m_name(name)
    {

    }
    
    string getName() const
    {
        return m_name;
    }

    bool isFinished() const
    {
        return m_finished;
    }

    //给用户重写需要的 run方法
    virtual void run() = 0;

protected:
    string m_name;
    bool m_finished = false;
};

using TaskPtr = shared_ptr<Task>;

#endif
