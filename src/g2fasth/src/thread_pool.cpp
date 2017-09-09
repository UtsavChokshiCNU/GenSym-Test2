#include <thread_pool.h>

namespace tthread {

thread_pool::thread_pool()
: _running(true)
, _task_size(0u)
, _job_size(0u)
, _max_thread_count(0)
{
    _thread_limit = tthread::thread::hardware_concurrency();

    if (_thread_limit <= 2)
        _thread_limit = 4;
    _max_thread_limit = _thread_limit * 4;

    _threads.reserve(_thread_limit);

    for (size_t i = 0; i < _thread_limit; ++i)
        _threads.push_back(std::make_shared<tthread::thread>(&thread_pool::worker_main, this));
    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(100));
}

thread_pool::~thread_pool()
{
    tthread::lock_guard<tthread::mutex> lock(_mutex);

    _running = false;

    _cv_worker.notify_all();
    _mutex.unlock();
    for (auto t = _threads.begin(); t != _threads.end(); ++t)
        (*t)->join();
}

unsigned thread_pool::thread_limit()
{
    lock_guard<mutex> lg(_mutex);
    return _thread_limit;
}
void thread_pool::set_thread_limit(unsigned thread_limit)
{
    lock_guard<mutex> lg(_mutex);
    if (thread_limit > _max_thread_limit)
        thread_limit = _max_thread_limit;
    _thread_limit  = thread_limit;
}
unsigned thread_pool::max_thread_limit()
{
    return _max_thread_limit;
}
unsigned thread_pool::max_thread_count()
{
    lock_guard<mutex> lg(_mutex);
    return _max_thread_count;
}

int thread_pool::task_create()
{
    tthread::lock_guard<tthread::mutex> lock(_mutex);
    int task;

    if (_free_tasks.empty())
    {
        task = static_cast<int>(_task_size);
        _task_size++;
        _task_pending_count.resize(_task_size);
    }
    else
    {
        task = _free_tasks.back();
        _free_tasks.pop_back();
    }
    _task_pending_count[task] = 0u;

    return task;
}

bool thread_pool::task_finished(int task) const
{
    tthread::lock_guard<tthread::mutex> lock(_mutex);

    return _task_pending_count[task] == 0u;
}

void thread_pool::task_perform(int task, const Job& job)
{
    tthread::lock_guard<tthread::mutex> lock(_mutex);

    _job_task.push(task);
    _job_function.push(job);
    _task_pending_count[task]++;
    _job_size++;
    _cv_worker.notify_one();
}

void thread_pool::task_wait(int task)
{
    tthread::lock_guard<tthread::mutex> lock(_mutex);

    while (_task_pending_count[task] > 0)
        _cv_master.wait(_mutex);

    _free_tasks.push_back(task);
}

void thread_pool::worker_main(void* p)
{
    thread_pool* tp = (thread_pool*)p;
    tthread::lock_guard<tthread::mutex> lock(tp->_mutex);

    while (tp->_running)
    {
        tp->_cv_worker.wait(tp->_mutex);

        for (;;)
        {
            if (tp->_job_size == 0)
                break;

            int task = tp->_job_task.front();
            Job job = tp->_job_function.front();
            tp->_job_task.pop();
            tp->_job_function.pop();
            tp->_job_size--;

            tp->_max_thread_count++;
            tp->_mutex.unlock();

            job.first(job.second);

            tp->_mutex.lock();
            tp->_max_thread_count--;
            
            tp->_task_pending_count[task]--;
            if (tp->_task_pending_count[task] == 0)
                tp->_cv_master.notify_all();
        }
    }
}

}
