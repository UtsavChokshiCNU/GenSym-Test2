#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <memory>
#include <utility>
#include <queue>
#include <vector>
#include "tinythread.h"

namespace tthread {

class thread_pool
{
public:
    typedef std::pair<std::function<void(void*)>, void*> Job;

    thread_pool();
    ~thread_pool();

    unsigned thread_limit();
    void set_thread_limit(unsigned thread_limit);
    unsigned max_thread_limit();
    unsigned max_thread_count();

    int     task_create();
    bool    task_finished(int task) const;
    void    task_perform(int task, const Job& job);
    void    task_wait(int task);

private:
    thread_pool(const thread_pool&);
    thread_pool& operator=(const thread_pool&);

    static void worker_main(void* p);

    bool                        _running;
    mutable tthread::mutex          _mutex;
    std::vector<std::shared_ptr<tthread::thread>>   _threads;

    size_t                      _task_size;
    std::vector<int>            _free_tasks;
    std::vector<unsigned>       _task_pending_count;

    size_t                      _job_size;
    std::queue<int>            _job_task;
    std::queue<Job>            _job_function;

    tthread::condition_variable     _cv_worker;
    tthread::condition_variable     _cv_master;

    unsigned _thread_limit;
    unsigned _max_thread_limit;
    unsigned _max_thread_count;
};

}

#endif // THREAD_POOL_H
