#include "catch.hpp"
#include "suite.hpp"
#include "tinythread.h"

using namespace g2::fasth;

class TestTimers : public g2::fasth::suite<TestTimers> {
public:
    int timer_count;
    TestTimers()
        : suite("TestTimers", g2::fasth::test_order::implied, g2::fasth::log_level::NONE)
    {
        timer_count = 10;
    };

    void test_case_1(const std::string& test_case_name)
    {
        start_timer(test_case_name
            , chrono::milliseconds(100)
            , &TestTimers::timer_func_obj
        );
    }
    void timer_func_obj(const std::string& test_case_name)
    {
        if (!--timer_count)
            complete_test_case(test_case_name, test_outcome::pass);
    }
};

TEST_CASE("Functional object multiple calls") {
    TestTimers test_suite;
    test_suite.run(&TestTimers::test_case_1, "test_case_1");
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
}

TEST_CASE("Timer-based test case ending by timeout") {
    TestTimers test_suite;
    test_suite.run(&TestTimers::test_case_1, "test_case_1", chrono::milliseconds(3000));
    test_suite.timer_count = 0;
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
}

