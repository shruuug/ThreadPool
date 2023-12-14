#pragma once
#include "task.hpp"
#include <functional>
#include <future>
template<typename ReturnType>
class FuncTask : public Task
{
public:
    FuncTask(const string& taskName = "") : Task(taskName) { };
    
    template <typename F, typename... Args>
    void init(F&& f, Args&&...args)
    {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        auto taskptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        m_warpperFunc = [taskptr]() {
            (*taskptr)();
        };

        m_future = taskptr->get_future();
        
    }

    void run() override
    {
        if (m_warpperFunc) {
            m_warpperFunc();
        }
    }

    ReturnType getResult()
    {
        std::chrono::milliseconds timeout(1000);
        std::future_status status = m_future.wait_for(timeout);
        if (status == std::future_status::ready) {
            m_result = m_future.get();
            m_finished = true;
        }
        return m_result;
    }


private:
    std::function<void()> m_warpperFunc;
    ReturnType m_result;
    std::shared_future<ReturnType> m_future;

};

template<>
class FuncTask<void> : public Task
{
public:
    FuncTask(const string& taskName = "") : Task(taskName) { };

    template <typename F, typename... Args>
    void init(F&& f, Args&&...args)
    {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        auto taskptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        m_warpperFunc = [taskptr]() {
            (*taskptr)();
        };
    }

    void run() override
    {
        if (m_warpperFunc) {
            m_warpperFunc();
        }
    }

private:
    std::function<void()> m_warpperFunc;

};
