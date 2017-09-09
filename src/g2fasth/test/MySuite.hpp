#ifndef INC_BASETEST_MYSUITE_H
#define INC_BASETEST_MYSUITE_H

#pragma once
#include "suite.hpp"

class MySuite : public g2::fasth::suite<MySuite>
{
public:
    MySuite(std::string, int, std::string, bool, std::string);
    ~MySuite();
    void first_test(const std::string&);
    void second_test(const std::string&);
    void third_test(const std::string&);
    void fourth_test(const std::string&);
    void timeout_pass_test(const std::string&);
    void timeout_fail_test(const std::string&);
    void default_timeout_pass_test(const std::string&);
    void default_timeout_fail_test(const std::string&);

    void sync_test(const std::string&);
    void async_test_controlled(const std::string&);
    void async_test_func_obj(const std::string&);
    void async_test_uncontrolled(const std::string&);

    void timer_test(const std::string&);     // Main test method
    void timer_func_obj(const std::string&); // Timer functional object
    void timer_monitor(const std::string&);  // Some async helper just for demo

private:
    const int d_iParam;
    const std::string d_sParam;
    const bool d_bParam;
    void before() override;
    void after() override;
    void setup_test_track() override;
    std::list<std::shared_ptr<tthread::thread>> d_threads;
};

#endif // !INC_BASETEST_MYSUITE_H