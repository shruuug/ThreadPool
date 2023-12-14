#include "threadpool.h"
ThreadPool::ThreadPool(int min, int max) : m_finish(false), m_min(min), m_max(max)
{
    //创建min个线程,线程池存放最小线程数
    for (int i = 0; i < min; ++i)
    {
        addThread();
    }
    // 创建管理线程
    m_managerThread = thread([this]()
    {
            //若是线程池没有关闭,就一直检测
            while (!m_finish)
            {
                //当前的任务数 > 2倍的线程数 && 已经存在的线程 < 最大线程个数，需要创建新的工作线程
                if ((m_taskQue.getSize() > 2 * m_thread.size()) && (m_thread.size() < m_max))
                {
                    addThread();
                }
                else
                {
                    //统计当前阻塞线程的数据
                    int cnt = 0;
                    for (auto it = m_thread.begin(); it != m_thread.end(); ++it)
                    {
                        //若是当前线程是阻塞线程
                        if (it->second->getState() == WorkThread::STATE_WAIT)
                        {
                            ++cnt;
                        }
                        //若是空闲的线程数 > 2倍的任务数,已经创建的线程总个数 > 最小线程数
                        //说明当前空闲的线程太多了,把多余的空闲线程销毁掉
                        if ((cnt > 2 * m_taskQue.getSize()) && (m_thread.size() > m_min))
                        {
                            delThread();
                        }
                    }
                    //休眠100微秒
                    sleep_for(std::chrono::microseconds(100));
                }
            }
    });
}

//回收管理者线程
ThreadPool::~ThreadPool()
{
    if (m_managerThread.joinable())
        m_managerThread.join();
}

//添加任务添加到任务队列中
void ThreadPool::addTask(TaskPtr task)
{
    m_taskQue.addTask(task);
}

//关闭线程池
void ThreadPool::shutdown()
{
    m_finish = true;
    for (auto it = m_thread.begin(); it != m_thread.end(); ++it)
    {
        it->second->finish();
    }
}

//创建工作线程，并把工作线程添加到unorder_map中管理
void ThreadPool::addThread()
{
    cout << "--- add thread ---\n";
    auto tidPtr = make_shared<WorkThread>(m_taskQue); 
    m_thread[tidPtr->getId()] = tidPtr;
}

//删除所有wait状态的线程
void ThreadPool::delThread()
{
    cout << "--- del thread ---\n";
    thread::id tid;

    for (auto it = m_thread.begin(); it != m_thread.end(); ++it)
    {
        //若是有线程为等待状态
        if (it->second->getState() == WorkThread::STATE_WAIT) {
            //结束当前线程
            it->second->finish();
            //获得线程的tid
            tid = it->first; 
            break;
        }
    }
    //把tid对应的线程删除
    m_thread.erase(tid);
}