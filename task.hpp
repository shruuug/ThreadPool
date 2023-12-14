#ifndef __TASK_H__
#define __TASK_H__
#include <iostream>
#include <memory>
using std::string;
using std::shared_ptr;
//�û��Զ����������,�û����ڿ��Զ������񣬼̳���дrun�����������Ϣ
class Task
{
public:
    //���������һ�� stirng ������������
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

    //���û���д��Ҫ�� run����
    virtual void run() = 0;

protected:
    string m_name;
    bool m_finished = false;
};

using TaskPtr = shared_ptr<Task>;

#endif
