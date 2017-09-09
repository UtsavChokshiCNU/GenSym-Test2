#include <cstdio>
#include "MySuite.hpp"
#include "tinythread.h"
#include "libgsi.hpp"


using namespace g2::fasth;

struct thread_data
{
    MySuite* suite;
    std::string test_case_name;
};

void uncontrolled_test_case_thread(void* p);

MySuite::MySuite(std::string suite_name, int iParam, std::string sParam, bool bParam, std::string logger_path)
    : suite(suite_name
        , test_order::implied
        , log_level::VERBOSE
        , logger_path
        , chrono::milliseconds(5000)) // default timeout
    , d_iParam(iParam)
    , d_sParam(sParam)
    , d_bParam(bParam)
{
}
MySuite::~MySuite()
{
    while (d_threads.size())
    {
        d_threads.front()->join();
        d_threads.pop_front();
    }
}


void MySuite::before()
{
    get_logger().log(log_level::VERBOSE, "Calling before().");
}

void MySuite::after()
{
    get_logger().log(log_level::VERBOSE, "Calling after().");
}

void MySuite::first_test(const std::string& test_case_name)
{
    char buf[25];
    sprintf(buf, "%d", d_iParam);
    get_logger().log(log_level::VERBOSE, std::string("Value of d_sParam is ") + buf);
    get_logger().log(log_level::VERBOSE, std::string("Value of d_sParam is ") + d_sParam);
    get_logger().log(log_level::VERBOSE, std::string("Value of d_bParam is ") + (d_bParam ? "true" : "false"));
    
    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::second_test(const std::string& test_case_name)
{
    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::third_test(const std::string& test_case_name)
{
    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::fourth_test(const std::string& test_case_name)
{
    thread_data* data = new thread_data;
    data->suite = this;
    data->test_case_name = test_case_name;

    std::shared_ptr<tthread::thread> ptr = std::make_shared<tthread::thread>(uncontrolled_test_case_thread, data);
    d_threads.push_back(ptr);
}

void MySuite::timeout_pass_test(const std::string& test_case_name)
{
    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(3000));

    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::timeout_fail_test(const std::string& test_case_name)
{
    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(3000));

    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::default_timeout_pass_test(const std::string& test_case_name)
{
    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(4000));

    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::default_timeout_fail_test(const std::string& test_case_name)
{
    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(6000));

    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::setup_test_track()
{
    libgsi& gsiobj = libgsi::getInstance();

    gsiobj.ignore_not_declared_variables();
    gsiobj.ignore_not_registered_variables();

    gsiobj.declare_g2_variable<int>("INTEGER_DAT");
    gsiobj.assign_def_value("INTEGER_DAT", 60);

    gsiobj.declare_g2_variable<int>("INTEGER_DAT_NOT_REG");
    gsiobj.assign_def_value("INTEGER_DAT_NOT_REG", 111);

    libgsi::variable_map vars = gsiobj.get_g2_variables();
    auto& first = run(&MySuite::first_test, "TestA");
    //run(&MySuite::second_test, "TestB").after(first);
    run(&MySuite::second_test, "TestB").after(&MySuite::first_test);
    run(&MySuite::third_test, "TestC").after_success_of(instance("TestB"));
    run(&MySuite::third_test, "TestC").guard([this] { return this->d_iParam > 0; });
    run(&MySuite::fourth_test, "AsyncTest");
    clone(first, "TestA Again");

    libgsi::getInstance().declare_g2_variable<int>("INTEGER_VAR_NAME");

    run(&MySuite::timeout_pass_test, "Timeout-Pass-Test", chrono::milliseconds(4000)); // timeout 4000 ms
    run(&MySuite::timeout_fail_test, "Timeout-Fail-Test", chrono::milliseconds(2000)); // timeout 2000 ms
    run(&MySuite::default_timeout_pass_test, "Default-Timeout-Pass-Test");    // default timeout
    run(&MySuite::default_timeout_fail_test, "Default-Timeout-Fail-Test");    // default timeout

    auto& utest = run(&MySuite::async_test_uncontrolled, "Async-Test-Uncontrolled");
    auto& atest = run(&MySuite::async_test_controlled, "Async-Test").after(utest);
    auto& stest = run(&MySuite::sync_test, "Sync-Test", tthread::chrono::milliseconds(500));
    clone(stest, "Sync-Test-2").after(atest);
    clone(atest, "Async-Test-2");

    run(&MySuite::timer_test, "Timer-test");
}

void MySuite::sync_test(const std::string& test_case_name)
{
    FUNCLOG;

    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(500));

    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::async_test_controlled(const std::string& test_case_name)
{
    FUNCLOG;

    go_async(
        test_case_name                   // Test case name
        , &MySuite::async_test_func_obj  // Pointer to asynchronous functional object
    );
}
void MySuite::async_test_func_obj(const std::string& test_case_name)
{
    FUNCLOG;

    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(2000));

    complete_test_case(test_case_name, test_outcome::pass);
}

void MySuite::async_test_uncontrolled(const std::string& test_case_name)
{
    FUNCLOG;

    std::unique_ptr<thread_data> data(new thread_data);
    data->suite = this;
    data->test_case_name = test_case_name;

    std::shared_ptr<tthread::thread> thread = std::make_shared<tthread::thread>(uncontrolled_test_case_thread, data.release());
    d_threads.push_back(thread);
}
void uncontrolled_test_case_thread(void* p)
{
    FUNCLOG;

    std::unique_ptr<thread_data> data((thread_data*)p);

    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(1000));

    data->suite->complete_test_case(data->test_case_name, test_outcome::pass);
}

int timer_count = 10;
tthread::mutex mutex;
int dec_count()
{
    tthread::lock_guard<tthread::mutex> lg(mutex);
    return --timer_count;
}
int get_count()
{
    tthread::lock_guard<tthread::mutex> lg(mutex);
    return timer_count;
}

void MySuite::timer_test(const std::string& test_case_name)
{
    FUNCLOG;

    // Start timer with 100 ms interval
    start_timer(
        test_case_name                  // Test case name
        , chrono::milliseconds(100)     // Timer interval
        , &MySuite::timer_func_obj      // Pointer to timer functional object
    );

    // Start async timer monitor
    go_async(
        test_case_name
        , &MySuite::timer_monitor
    );
}

void MySuite::timer_func_obj(const std::string& test_case_name)
{
    //FUNCLOG;

    printf("Count = %d\n", dec_count());
}

void MySuite::timer_monitor(const std::string& test_case_name)
{
    FUNCLOG;

    // Wait until count==0
    while (get_count())
        tthread::this_thread::sleep_for(tthread::chrono::milliseconds(20));

    // Stop the timer, but it's not test end yet
    stop_timer(test_case_name, &MySuite::timer_func_obj);

    // 3 sec sleep
    puts("Sleep for 3 second...");
    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(3000));

    // Complete the test
    complete_test_case(test_case_name, test_outcome::pass);
}

