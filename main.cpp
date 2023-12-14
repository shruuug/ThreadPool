#include "threadpool.h"
//测试用例
class MyTask : public Task
{
public:
    MyTask(const string& taskName) : Task(taskName) { };
    void run() override
    {
        calculate(m_num);
    }
    void calculate(int m_num)
    {
        double sum = 0;
        for (double i = 1; ; ++i)
        {
            sum += i;
            if (sum >= goal)
            {
                result = i;
                ok = true;
                break;
            }
        }
    }

    long m_num = 100000;
    long m_cnt = 0;

    double getResult()
    {
        while (!ok);
        return result;
    }

    bool ok = false;
    double goal = 10000;
    double result = 0;
};

int caldouble(int a)
{
    printf("caldouble running\n");
    return a * 2;
}

void calplus(int &res, int a, int b)
{
    res = a + b;
}

int main()
{
    ThreadPool pool;
    shared_ptr<MyTask> test_1 = make_shared<MyTask>("task_1");
    pool.addTask(test_1);

    pool.addTask(std::move(make_shared<MyTask>("task_2")));

    FuncTask<int> task_3("task_3");
    task_3.init(caldouble, 3);
    pool.addTask(std::move(make_shared<FuncTask<int>>(task_3)));

    int res;
    FuncTask<void> task_4("task_4");
    task_4.init(calplus, std::ref(res), 1, 5);
    pool.addTask(std::move(make_shared<FuncTask<void>>(task_4)));

    //等待任务完成，输出结果
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    cout << std::dynamic_pointer_cast<MyTask>(test_1)->getResult()<<endl;
    printf("task_3 result: %d\n", task_3.getResult());
    printf("task_4 result: %d\n", res);
    //手动关闭线程池
    pool.shutdown();
    return 1;
}