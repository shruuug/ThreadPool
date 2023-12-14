#include "workthread.h"
WorkThread::WorkThread(TaskQueue& taskQue) : m_taskQue(taskQue), m_state(STATE_WAIT), m_finish(false)
{
    //使用lambda表达式创建线程
    m_thread = thread([this]()
        {
            //工程线程没有结束的时候
            while (!m_finish)
            {
                m_state = STATE_WAIT; //线程默认阻塞状态

                //当线程没有结束并且队列为空的时候，阻塞当前线程
                while (!m_finish && m_taskQue.isEmpty())
                {
                    sleep_for(std::chrono::microseconds(50));
                }

                //当线程结束了,结束循环
                if (m_finish)
                {
                    break;
                }

                //运行到此处,说明队列不为空,取出队列中的数据
                TaskPtr task = m_taskQue.getTask();
                if (task != nullptr)
                {
                    //此时状态设置为工作状态
                    m_state = STATE_WORK;
                    cout << "--- thread[" << get_id() << "]:run task [" << task->getName().c_str() << "] << begin\n"; 
                    //运行当前线程任务
                    task->run();
                    cout << "--- thread[" << get_id() << "]:run task [" << task->getName().c_str() << "] << end\n";
                }
            }

            m_state = STATE_EXIT;
        });
    printf("-- thread [%d] : started ---in\n", m_thread.get_id());
}

WorkThread::~WorkThread()
{
    printf("-- thread [%d] :finish ---\n", m_thread.get_id());
    if (m_thread.joinable())
        m_thread.join();
}

int WorkThread::getState() const
{
    return m_state;
}
    
void WorkThread::finish()
{
    m_finish = true;
}

thread::id WorkThread::getId() const
{
    return m_thread.get_id();
}

thread& WorkThread::getCurrentThread()
{
    return m_thread;
}
