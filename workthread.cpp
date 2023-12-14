#include "workthread.h"
WorkThread::WorkThread(TaskQueue& taskQue) : m_taskQue(taskQue), m_state(STATE_WAIT), m_finish(false)
{
    //ʹ��lambda���ʽ�����߳�
    m_thread = thread([this]()
        {
            //�����߳�û�н�����ʱ��
            while (!m_finish)
            {
                m_state = STATE_WAIT; //�߳�Ĭ������״̬

                //���߳�û�н������Ҷ���Ϊ�յ�ʱ��������ǰ�߳�
                while (!m_finish && m_taskQue.isEmpty())
                {
                    sleep_for(std::chrono::microseconds(50));
                }

                //���߳̽�����,����ѭ��
                if (m_finish)
                {
                    break;
                }

                //���е��˴�,˵�����в�Ϊ��,ȡ�������е�����
                TaskPtr task = m_taskQue.getTask();
                if (task != nullptr)
                {
                    //��ʱ״̬����Ϊ����״̬
                    m_state = STATE_WORK;
                    cout << "--- thread[" << get_id() << "]:run task [" << task->getName().c_str() << "] << begin\n"; 
                    //���е�ǰ�߳�����
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
