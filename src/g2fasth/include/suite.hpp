#pragma once
#ifndef INC_LIBG2FASTH_SUITE_H
#define INC_LIBG2FASTH_SUITE_H

#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iterator>
#include <fstream>
#include <ios>

#include "test_run_spec.hpp"
#include "g2fasth_typedefs.hpp"
#include "junit_report.hpp"
#include "base_suite.hpp"

namespace g2 {
namespace fasth {

/**
* Stores relationship between a test case and its outcome.
*/
struct test_result {
    test_result(std::string test_case_name, test_outcome test_outcome)
        : d_test_case_name(test_case_name), d_test_outcome(test_outcome)
    {
    }
    std::string test_case_name() {
        return d_test_case_name;
    }
    test_outcome outcome() {
        return d_test_outcome;
    }
private:
    std::string d_test_case_name;
    test_outcome d_test_outcome;
};

// Max timeout for tests
#define G2FASTH_MAX_TIMEOUT      7*24*3600*1000  // 1 week
// Default timeout for tests
#define G2FASTH_DEFAULT_TIMEOUT  600*1000        // 10 min

template <class T>
class suite : public base_suite {
public:
    /**
    * Constructor that sets the name of the suite, its execution order and log level.
    * @param suite_name name of the test suite.
    * @param test_order order of execution of test cases.
    * @param logger_file_path absolute path to the log file.
    * @param suite_log_level log level of test suite.
    */
    suite(std::string suite_name, test_order test_order=test_order::random,
        log_level suite_log_level=log_level::VERBOSE, std::string logger_file_path = "", 
        const chrono::milliseconds& default_timeout=chrono::milliseconds(G2FASTH_DEFAULT_TIMEOUT))
            : base_suite(suite_name)
        , d_order(test_order)
        , d_logger(suite_log_level)
        , d_default_timeout(default_timeout)
        , d_state(not_yet)
        , d_parallel(true)
    {
        if (d_default_timeout.count() > G2FASTH_MAX_TIMEOUT)
            d_default_timeout = chrono::milliseconds(G2FASTH_MAX_TIMEOUT);
        d_logger.add_output_stream(std::cout, log_level::REGULAR);
        if (!logger_file_path.empty())
        {
            d_logger.add_output_stream(new std::ofstream(logger_file_path, std::ios_base::app), log_level::VERBOSE);
        }
    }
    ~suite()
    {
        int cancelled = 0;
        while (d_threads_to_cancel.size())
        {
            if (d_threads_to_cancel.front()->cancel())
                cancelled++;
            d_threads_to_cancel.pop_front();
        }
        timing start;
        while (d_threads_to_wait.size())
        {
            d_threads_to_wait.front()->join();
            d_threads_to_wait.pop_front();
        }
#ifndef WIN32
        if (cancelled)
        {   // Let cancelled threads (in Linux) to stop
            int sleep = 10000 - start.elapsed();
            //printf("Wait %d ms for cancelled threads(%d)...\n", sleep, cancelled);
            if (sleep > 0)
                tthread::this_thread::sleep_for(tthread::chrono::milliseconds(sleep));
        }
#endif
    }
    void set_parallel(bool parallel)
    {
        d_parallel = parallel;
    }
    /**
    * This function executes test suite. First it setups test track and then starts execution.
    * @param report_file_name Absolute path of the JUnit report xml, can be empty if report is not to be written
    * @return JUnit report in string format.
    */
    inline std::string execute(std::string report_file_name = "") override {
        int count;
        {
            tthread::lock_guard<tthread::mutex> lg(d_mutex);
            count = d_test_specs.size();
            if (!d_thread_pool)
                d_thread_pool = std::make_shared<tthread::thread_pool>(); 
        }
        if (count == 0)
        {
            d_logger.log(log_level::SILENT, "Setting up test track for test suite : " + get_suite_name());
            setup_test_track();
            d_logger.log(log_level::SILENT, "Test track setup done for test suite : " + get_suite_name());
        }
        return start(report_file_name);
    }

    void execute_test_case(const std::string& name, bool unconditionally = false, const std::string& reason = "")
    {
        std::shared_ptr<test_run_spec<T>> test_case;
        {
            tthread::lock_guard<tthread::mutex> lg(d_mutex);
            auto it = std::find_if(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
                return spec->name() == name;
            });
            if (it == d_test_specs.end())
            {
                throw std::invalid_argument("Test case '" + name + "' doesn't exist.");
            }
            test_case = *it;
            if (!unconditionally)
            {
                if (test_case->state() != test_run_state::not_yet)
                    throw std::invalid_argument("Test case '" + name + "' is already being executed or completed.");
                if (!test_case->valid_to_execute())
                    throw std::invalid_argument("Test case '" + name + "' could not be executed right now.");
            }
        }
        before();
        if (test_case->execute(nullptr, reason))
            after();
    }

    /**
    * This function schedules a test case for execution.
    * @param ptr_test_case pointer to test case to be executed.
    * @param test_case_name name of test case.
    * @param timeout timeout of test case.
    * @return Handle of created test run instance.
    */
    inline test_run_spec<T>& run(typename test_helper<T>::pmf_t ptr_test_case
            , const std::string& test_case_name
            , const chrono::milliseconds& timeout=chrono::milliseconds(0)) {
        std::function<void(const std::string&)> action =
            std::bind(ptr_test_case, static_cast<T*>(this), std::placeholders::_1);
        auto ptr = schedule(action, test_case_name, ptr_test_case, timeout);
        assert(ptr != nullptr);
        return *(ptr.get());
    }
    /**
    * This function schedules a series of test case for execution.
    * @param count Series size.
    * @param ptr_test_case pointer to test case to be executed.
    * @param test_case_name name of test case.
    * @param timeout timeout of test case.
    * @return List of handles of created test run instances.
    */
    std::list<std::shared_ptr<test_run_spec<T>>> run_series(size_t count
            , typename test_helper<T>::pmf_t ptr_test_case
            , const std::string& test_case_name
            , const chrono::milliseconds& timeout=chrono::milliseconds(0)) {
        std::function<void(const std::string&)> action =
            std::bind(ptr_test_case, static_cast<T*>(this), std::placeholders::_1);
        std::list<std::shared_ptr<test_run_spec<T>>> series;
        for (size_t i=0; i<count; i++)
        {
            auto ptr = schedule(action, test_case_name+"."+std::to_string((long long)i), ptr_test_case, timeout);
            assert(ptr != nullptr);
            series.push_back(ptr);
        }
        return series;
    }
    /**
    * Returns test run instance by name.
    * @param name Name of test run instance to return.
    * @return Handle of specified test run instance.
    */
    inline test_run_spec<T>& instance(const std::string& name) {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        auto it = std::find_if(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
            return spec->name() == name;
        });
        if (it == d_test_specs.end())
        {
            throw std::invalid_argument("Instance " + name + " doesn't exist.");
        }
        return *(it->get());
    }
    /**
    * This function returns an instance of logger which can be used to log any data.
    * @return An instance of logger.
    */
    inline logger& get_logger() {
        return d_logger;
    }
    /**
    * This function return true or false depending on if test case exists in schedule.
    * @param test_case test case existence for which is to be verified.
    * @return true or false.
    */
    inline bool test_case_exists(typename test_helper<T>::pmf_t test_case) {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        return internal_test_case_exists(test_case);
    }
    /**
    * This function returns instance of spec.
    * @param ptr_test_case pointer to test case for which test spec is to be returned.
    * @return instance of test spec.
    */
    test_run_spec<T>& get_spec(typename test_helper<T>::pmf_t test_case) {
        return *(std::find_if(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
            return spec->get_ptr_test_case() == test_case;
        })->get());
    }
    /**
    * This function validates if there exists cycle in test spec.
    * @return true or false.
    */
    inline bool validate_cycle() {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        graph<T> test_case_graph(d_test_specs.size());
        for (auto it = d_test_specs.begin(); it != d_test_specs.end(); ++it)
        {
            if (it->get()->get_ptr_after_test_case() != nullptr)
            {
                test_case_graph.add_edge(get_index_of_test_case((*it)->get_ptr_after_test_case()),
                    get_index_of_test_case((*it)->get_ptr_test_case()));
            }
            if ((*it)->get_ptr_after_success_of_test_case() != nullptr)
            {
                test_case_graph.add_edge(get_index_of_test_case((*it)->get_ptr_after_success_of_test_case()),
                    get_index_of_test_case((*it)->get_ptr_test_case()));
            }
        }
        return test_case_graph.is_cyclic();
    }
    /**
    * This function checks test timeouts.
    * @return true or false.
    */
     void check_test_timeouts() {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        std::for_each(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
            if (spec->is_timeout())
                spec->complete(test_outcome::fail);
        });
    }
    /**
    * This function checks is all tests (sync & async) are completed.
    * @return true or false.
    */
    inline bool are_all_tests_completed() {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        return std::find_if(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
            return spec->state() != test_run_state::done;
        }) == d_test_specs.end();
    }
    /**
    * This function checks if some tests are still executing.
    * @return true or false.
    */
    inline bool are_tests_executing() {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        return std::find_if(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
            return spec->state() == test_run_state::ongoing;
        }) != d_test_specs.end();
    }
    /**
    * This function returns result of test cases.
    * @return collection of result.
    */
    inline std::vector<test_result> get_results() {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        return d_results;
    }
    /**
    * This function validates if a schedule is invalid.
    */
    inline void schedule_before(typename test_helper<T>::pmf_t before, typename test_helper<T>::pmf_t after) {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        if (internal_test_case_exists(before) && internal_test_case_exists(after)
            && get_index_of_test_case(before) > get_index_of_test_case(after))
        {
            auto after_it = d_test_specs.begin();
            std::advance(after_it, get_index_of_test_case(after));
            auto before_it = d_test_specs.begin();
            std::advance(before_it, get_index_of_test_case(before));
            throw std::invalid_argument("Test case " + (*before_it)->name() + " should be scheduled before " + (*after_it)->name() + ".");
        }
    }

    void complete_test_case(const std::string& name, test_outcome outcome)
    {
        instance(name).complete(outcome);
    }

    void add_thread_to_cancel(std::shared_ptr<tthread::thread> thread)
    {
        tthread::lock_guard<tthread::mutex> lg(d_cancel_threads_mutex);
        d_threads_to_cancel.push_back(thread);
    }

protected:
    virtual void before() {};
    virtual void after() {};
    virtual void setup_test_track() {};
    /**
    * Creates a clone of test run instance.
    * @param name Name of cloned test run instance.
    * @return Handle of cloned test run instance.
    */
    inline test_run_spec<T>& clone(const test_run_spec<T>& instance, const std::string& name) {
        d_logger.log(log_level::VERBOSE, "Cloning test case " + name + " for execution");
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        d_test_specs.push_back(instance.clone(name));
        test_run_spec<T>& new_spec = *d_test_specs.back();
        return new_spec;
    }

    /**
    * Continues test case execution asynchronously.
    * @param test_case_name Name of the test case.
    * @param async_func_obj Functional object to run asynchronously.
    *   If not specified (nullptr), then test case itself will be called asynchronuosly,
    */
    void go_async(const std::string& test_case_name
        , typename test_helper<T>::pmf_t func_obj=nullptr)
    {
        internal_async(test_case_name, func_obj, chrono::milliseconds(0));
    }
    /**
    * Continues test case execution asynchronously as a timer.
    * @param test_case_name Name of the test case.
    * @param interval Timer interval.
    * @param timer_func_obj Functional object to call periodically.
    *   If not specified (nullptr), then test case itself will be called as timer object,
    */
    void start_timer(const std::string& test_case_name
        , const chrono::milliseconds& interval
        , typename test_helper<T>::pmf_t func_obj=nullptr)
    {
        assert(interval.count() > 0);
        if (interval.count() <= 0)
            return;
        internal_async(test_case_name, func_obj, interval);
    }
    /**
    * Stops the timer.
    * @param test_case_name Name of the test case.
    * @param timer_func_obj Timer functional object
    */
    void stop_timer(const std::string& test_case_name, typename test_helper<T>::pmf_t timer_func_obj)
    {
        instance(test_case_name).stop_timer(timer_func_obj);
    }
private:
    suite(const suite&);
    suite& operator=(const suite&);

    void set_state(test_run_state new_state) override
    {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        d_state = new_state;
    }
    test_run_state state() override
    {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        return d_state;
    }
    inline std::string start(std::string report_file_name) {
        check_time();
        timing start;
        d_logger.log(log_level::SILENT, "Starting execution of test suite : " + get_suite_name());
        // Execute tests
        if (d_parallel)
        {
            int task = d_thread_pool->task_create();
            internal_start(task);
            d_thread_pool->task_wait(task);
        }
        else
        {
            internal_start();
        }
        extract_result();
        for (auto result = d_results.begin(); result != d_results.end(); ++result)
        {
            d_logger.log(log_level::REGULAR, "Outcome of " + result->test_case_name() + " is " + test_outcome_str[(int)result->outcome()] + ".");
        }
        d_logger.log(log_level::SILENT, "Done executing test suite : " + get_suite_name());
        return generate_junit_report(report_file_name, start.elapsed());
    }
    static void s_start_thread_proc(void* p)
    {
        try {
            test_run_spec<T>* spec = (test_run_spec<T>*)p;
            spec->get_suite()->before();
            if (spec->execute())
                spec->get_suite()->after();
        } catch (...) {}
    }
    void internal_start(int task = 0)
    {
        while(true)
        {
            check_test_timeouts();
            auto test_case = get_test_case_to_execute();
            if (test_case)
            {
                if (d_parallel)
                {
                    d_thread_pool->task_perform(task, std::make_pair(&suite::s_start_thread_proc, test_case.get()));
                }
                else
                {
                    before();
                    if (test_case->execute(nullptr, REASON_DEFAULT))
                        after();
                }
            }
            else if (are_all_tests_completed())
                break;
            else if (are_tests_executing())
            {
                //puts("Start - wait 100 ms...");
                tthread::this_thread::sleep_for(tthread::chrono::milliseconds(100));
            }
            else    // there are some not competed tests and no tests are executing
            {
                // fail all remaining tests
                tthread::lock_guard<tthread::mutex> lg(d_mutex);
                std::for_each(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
                    if (spec->state()==test_run_state::not_yet)
                        spec->complete(test_outcome::fail);
                });
            }
        }
    }
    std::shared_ptr<test_run_spec<T>> get_test_case_to_execute() {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        std::list<std::shared_ptr<test_run_spec<T>>> test_cases;
        std::for_each(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
            if (spec->state()==test_run_state::not_yet && spec->valid_to_execute())
                test_cases.push_back(spec);
        });
        if (0 == test_cases.size())
            return nullptr;
        std::shared_ptr<test_run_spec<T>> test_case = test_cases.front();
        if (test_order::random==d_order && test_cases.size()>1)
        {
            srand(time(NULL));
            int rnd = rand() % test_cases.size();
            auto it = test_cases.begin();
            for (int i=0; i<rnd; i++)
                it++;
            test_case = *it;
        }
        test_case->set_state(test_run_state::ongoing);
        return test_case;
    }
    inline std::string generate_junit_report(std::string report_file_name, int elapsed) {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        testsuite_data test_suite(d_test_specs.size(), d_start_time, elapsed);
        for (auto it = d_test_specs.begin(); it != d_test_specs.end(); ++it)
        {
            test_run_spec<T>* test_spec = it->get();
            auto test_case = test_suite.add_testcase(get_suite_name() + "." + test_spec->name(), test_spec->name(), test_spec->run_time());
            if (test_spec->outcome() != test_outcome::pass)
            {
                test_case->fail_test_case(test_outcome_str[(int)test_spec->outcome()], "This has failed due to unknow reasons.");
            }
        }
        return test_suite.to_xml(report_file_name);
    }
    typename std::shared_ptr<test_run_spec<T>> schedule(
            std::function<void(const std::string&)> test_action,
            const std::string& test_case_name,
            typename test_helper<T>::pmf_t ptr_test_case,
            const chrono::milliseconds& timeout) {
        auto insert = true;
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        if (std::find_if(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
            return spec->get_ptr_test_case() == ptr_test_case && spec->name() == test_case_name;
        }) != d_test_specs.end())
        {
            insert = false;
        }
        if (insert)
        {
            d_test_specs.push_back(std::make_shared<test_run_spec<T>>(test_action,
                test_case_name, ptr_test_case, this, correct_timeout(timeout)));
        }
        for (auto it = d_test_specs.begin(); it != d_test_specs.end(); ++it)
        {
            auto ptr = *it;
            if (ptr->name() == test_case_name)
            {
                return ptr;
            }
        }
        return nullptr;
    }
    void extract_result() {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        d_results.clear();
        for (auto it = d_test_specs.begin(); it != d_test_specs.end(); ++it)
        {
            d_results.push_back(test_result((*it)->name(), (*it)->outcome()));
        }
    }
    int get_index_of_test_case(typename test_helper<T>::pmf_t test_case) {
        auto index = 0;
        for (auto it = d_test_specs.begin(); it != d_test_specs.end(); ++it, ++index)
        {
            if ((*it)->get_ptr_test_case() == test_case)
            {
                return index;
            }
        }
        return -1;
    }
    chrono::milliseconds correct_timeout(const chrono::milliseconds& in)
    {
        chrono::milliseconds timeout = in;
        if (timeout.count() == 0)
            timeout = d_default_timeout;
        if (timeout.count() > G2FASTH_MAX_TIMEOUT)
            timeout = chrono::milliseconds(G2FASTH_MAX_TIMEOUT);
        return timeout;
    }
    bool internal_test_case_exists(typename test_helper<T>::pmf_t test_case) {
        return std::find_if(d_test_specs.begin(), d_test_specs.end(), [&](std::shared_ptr<test_run_spec<T>> spec) {
            return spec->get_ptr_test_case() == test_case;
        }) != d_test_specs.end();
    }
    void internal_async(const std::string& test_case_name
        , typename test_helper<T>::pmf_t func_obj
        , const chrono::milliseconds& interval)
    {
        std::unique_ptr<async_run_data<T>> data(new async_run_data<T>);
        data->test_suite = this;
        data->test_case = nullptr;
        data->test_case_name = test_case_name;
        if (func_obj)
        {
            data->func_obj = std::bind(func_obj, static_cast<T*>(this), std::placeholders::_1);
            data->user_func_ptr = func_obj;
        }
        else
        {
            data->func_obj = nullptr;
            data->user_func_ptr = nullptr;
        }
        data->interval = (int)interval.count();
        std::shared_ptr<tthread::thread> thread = std::make_shared<tthread::thread>(s_async_thread_proc, data.release());
        tthread::lock_guard<tthread::mutex> lg(d_wait_threads_mutex);
        d_threads_to_wait.push_back(thread);
    }
    static void s_async_thread_proc(void* p)
    {
        std::unique_ptr<async_run_data<T>> data((async_run_data<T>*)p);
        try {
            suite* _this = data->test_suite;
            test_run_spec<T>& test = _this->instance(data->test_case_name);
            if (test.state() != test_run_state::ongoing)
            {
                test.complete(test_outcome::fail);
                return;
            }
            try {
                if (test.execute(data.release()))
                    _this->after();
            }
            catch (... ) {
                test.complete(test_outcome::fail);
            }
        }
        catch (... ) {
        }
    }
    void check_time()
    {
        char buf[64];
        int y, mo, d, h, mi, s, ms;
#ifdef _WIN32
        SYSTEMTIME st;
        ::GetSystemTime(&st);
        y  = st.wYear;
        mo = st.wMonth;
        d  = st.wDay;
        h  = st.wHour;
        mi = st.wMinute;
        s  = st.wSecond;
        ms = st.wMilliseconds;
#else
        timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        tzset();
        tm t;
        localtime_r(&ts.tv_sec, &t);
        y  = t.tm_year + 1900;
        mo = t.tm_mon + 1;
        d  = t.tm_mday;
        h  = t.tm_hour;
        mi = t.tm_min;
        s  = t.tm_sec;
        ms = ts.tv_nsec / 1000000;
#endif
        sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d.%03d", y, mo, d, h, mi, s, ms);
        d_start_time = buf;
    }

private:
    tthread::mutex d_mutex;
    test_order d_order;
    std::list<std::shared_ptr<test_run_spec<T>>> d_test_specs;
    logger d_logger;
    std::vector<test_result> d_results;
    chrono::milliseconds d_default_timeout;
    tthread::mutex d_wait_threads_mutex;
    std::list<std::shared_ptr<tthread::thread>> d_threads_to_wait;
    tthread::mutex d_cancel_threads_mutex;
    std::list<std::shared_ptr<tthread::thread>> d_threads_to_cancel;
    test_run_state d_state;
    bool d_parallel;
    std::string d_start_time;
};

}
}

#endif // !INC_LIBG2FASTH_SUITE_H