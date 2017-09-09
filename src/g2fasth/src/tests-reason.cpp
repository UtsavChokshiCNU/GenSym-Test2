#include "catch.hpp"
#include "suite.hpp"
#include "tinythread.h"

using namespace g2::fasth;

class TestReasons : public g2::fasth::suite<TestReasons> {
public:
    TestReasons()
        : suite("TestReasons", g2::fasth::test_order::implied, g2::fasth::log_level::NONE)
    {
    };

    void reason_start(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void reason_async_with_separate_func_obj(const std::string& test_case_name)
    {
        go_async(test_case_name
            , &TestReasons::async_func_obj
        );
    }
    void async_func_obj(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void reason_timeout_with_separate_func_obj(const std::string& test_case_name)
    {
        start_timer(test_case_name
            , chrono::milliseconds(100)
            , &TestReasons::timer_func_obj
        );
    }
    void timer_func_obj(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void reason_async_with_same_func_obj(const std::string& test_case_name)
    {
        static bool start = true;
        if (start)
        {
            start = false;
            return go_async(test_case_name);
        }
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void reason_timeout_with_same_func_obj(const std::string& test_case_name)
    {
        static bool start = true;
        if (start)
        {
            start = false;
            return start_timer(test_case_name, chrono::milliseconds(100));
        }
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

TEST_CASE("Test reasons - start") {
    TestReasons test_suite;
    test_suite.run(&TestReasons::reason_start, "reason_start");
    test_suite.execute();
    REQUIRE(test_suite.instance("reason_start").reason() == REASON_DEFAULT);
}

TEST_CASE("Test reasons - async with separate func obj") {
    TestReasons test_suite;
    test_suite.run(&TestReasons::reason_async_with_separate_func_obj, "reason_async_with_separate_func_obj");
    test_suite.execute();
    REQUIRE(test_suite.instance("reason_async_with_separate_func_obj").reason() == REASON_ASYNC);
}

TEST_CASE("Test reasons - timeout with separate func obj") {
    TestReasons test_suite;
    test_suite.run(&TestReasons::reason_timeout_with_separate_func_obj, "reason_timeout_with_separate_func_obj");
    test_suite.execute();
    REQUIRE(test_suite.instance("reason_timeout_with_separate_func_obj").reason() == REASON_TIMEOUT);
}

TEST_CASE("Test reasons - async with the same func obj") {
    TestReasons test_suite;
    test_suite.run(&TestReasons::reason_async_with_same_func_obj, "reason_async_with_same_func_obj");
    test_suite.execute();
    REQUIRE(test_suite.instance("reason_async_with_same_func_obj").reason() == REASON_ASYNC);
}

TEST_CASE("Test reasons - timeout with the same func obj") {
    TestReasons test_suite;
    test_suite.run(&TestReasons::reason_timeout_with_same_func_obj, "reason_timeout_with_same_func_obj");
    test_suite.execute();
    REQUIRE(test_suite.instance("reason_timeout_with_same_func_obj").reason() == REASON_TIMEOUT);
}

TEST_CASE("Test reasons - custom reason") {
    TestReasons test_suite;
    test_suite.run(&TestReasons::reason_start, "reason_custom");
    test_suite.execute_test_case("reason_custom", false, "GSI RPC Response");
    REQUIRE(test_suite.instance("reason_custom").reason() == "GSI RPC Response");
}
