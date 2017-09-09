#include "catch.hpp"
#include "suite.hpp"
#include "tinythread.h"

using namespace g2::fasth;

class TestTimeouts : public g2::fasth::suite<TestTimeouts> {
public:
    int sleep_time;
    TestTimeouts()
        : suite("TestTimeouts", g2::fasth::test_order::implied, g2::fasth::log_level::NONE)
    {
        sleep_time = 0;
    };
    TestTimeouts(chrono::milliseconds default_timeout)
        : suite("TestTimeouts", g2::fasth::test_order::implied, g2::fasth::log_level::NONE, "", default_timeout)
    {
        sleep_time = 0;
    };

    void sync_test(const std::string& test_case_name)
    {
        tthread::this_thread::sleep_for(tthread::chrono::milliseconds(sleep_time));
        
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void async_test(const std::string& test_case_name)
    {
        go_async(test_case_name, &TestTimeouts::sync_test);
    }
};

TEST_CASE("Timeout is not specified") {
    TestTimeouts test_suite;
    test_suite.sleep_time = 500;
    test_suite.run(&TestTimeouts::sync_test, "sync_test");
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
}

TEST_CASE("Test is in time") {
    TestTimeouts test_suite;
    test_suite.sleep_time = 500;
    test_suite.run(&TestTimeouts::sync_test, "sync_test", chrono::milliseconds(10000));
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
}

TEST_CASE("Test is timed out") {
    TestTimeouts test_suite;
    test_suite.sleep_time = 10000;
    test_suite.run(&TestTimeouts::sync_test, "sync_test", chrono::milliseconds(500));
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
}

TEST_CASE("Default timeout pass test") {
    TestTimeouts test_suite(chrono::milliseconds(10000));
    test_suite.sleep_time = 500;
    test_suite.run(&TestTimeouts::sync_test, "sync_test");
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
}

TEST_CASE("Default timeout fail test") {
    TestTimeouts test_suite(chrono::milliseconds(500));
    test_suite.sleep_time = 10000;
    test_suite.run(&TestTimeouts::sync_test, "sync_test");
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
}

TEST_CASE("Async test, default timeout pass test") {
    TestTimeouts test_suite(chrono::milliseconds(10000));
    test_suite.sleep_time = 500;
    test_suite.run(&TestTimeouts::async_test, "async_test");
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
}

TEST_CASE("Async test, default timeout fail test") {
    TestTimeouts test_suite(chrono::milliseconds(500));
    test_suite.sleep_time = 10000;
    test_suite.run(&TestTimeouts::async_test, "async_test");
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
}

TEST_CASE("Async test, timeout pass test") {
    TestTimeouts test_suite;
    test_suite.sleep_time = 500;
    test_suite.run(&TestTimeouts::async_test, "async_test", chrono::milliseconds(10000));
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
}

TEST_CASE("Async test, timeout fail test") {
    TestTimeouts test_suite;
    test_suite.sleep_time = 10000;
    test_suite.run(&TestTimeouts::async_test, "async_test", chrono::milliseconds(500));
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
}
