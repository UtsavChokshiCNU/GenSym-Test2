#include "catch.hpp"
#include "suite.hpp"
#include "tinythread.h"

using namespace g2::fasth;

class TestOrders : public g2::fasth::suite<TestOrders> {
public:
    std::string log;
    std::string implied_log;
    TestOrders(test_order order)
        : suite("TestOrders", order, log_level::REGULAR)
    {
        implied_log = "0123456789";
    };
    TestOrders() : suite("TestOrders")
    {
        implied_log = "0123456789";
    };

    void test(const std::string& test_case_name)
    {
        //puts(test_case_name.c_str());
        log += test_case_name;
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

TEST_CASE("Test order - explicit implied") {
    TestOrders ts(test_order::implied);
    ts.set_parallel(false);
    ts.run(&TestOrders::test, "0");
    ts.run(&TestOrders::test, "1");
    ts.run(&TestOrders::test, "2");
    ts.run(&TestOrders::test, "3");
    ts.run(&TestOrders::test, "4");
    ts.run(&TestOrders::test, "5");
    ts.run(&TestOrders::test, "6");
    ts.run(&TestOrders::test, "7");
    ts.run(&TestOrders::test, "8");
    ts.run(&TestOrders::test, "9");
    ts.execute();
    REQUIRE(ts.log == ts.implied_log);
}

TEST_CASE("Test order - explicit random") {
    TestOrders ts(test_order::random);
    ts.set_parallel(false);
    ts.run(&TestOrders::test, "0");
    ts.run(&TestOrders::test, "1");
    ts.run(&TestOrders::test, "2");
    ts.run(&TestOrders::test, "3");
    ts.run(&TestOrders::test, "4");
    ts.run(&TestOrders::test, "5");
    ts.run(&TestOrders::test, "6");
    ts.run(&TestOrders::test, "7");
    ts.run(&TestOrders::test, "8");
    ts.run(&TestOrders::test, "9");
    ts.execute();
    REQUIRE(ts.log.length() == ts.implied_log.length());
    REQUIRE(ts.log != ts.implied_log);
}

TEST_CASE("Test order - default random") {
    TestOrders ts;
    ts.set_parallel(false);
    ts.run(&TestOrders::test, "0");
    ts.run(&TestOrders::test, "1");
    ts.run(&TestOrders::test, "2");
    ts.run(&TestOrders::test, "3");
    ts.run(&TestOrders::test, "4");
    ts.run(&TestOrders::test, "5");
    ts.run(&TestOrders::test, "6");
    ts.run(&TestOrders::test, "7");
    ts.run(&TestOrders::test, "8");
    ts.run(&TestOrders::test, "9");
    ts.execute();
    REQUIRE(ts.log.length() == ts.implied_log.length());
    REQUIRE(ts.log != ts.implied_log);
}

