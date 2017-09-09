#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;

class TestSuite : public g2::fasth::suite<TestSuite> {
public:
    TestSuite()
        :suite("TestSuite", g2::fasth::test_order::implied, g2::fasth::log_level::NONE)
        , secondCalled(false)
        , testExecutionCounterOFirstTest(0)
        , testExecutionCounterOThirdTest(0) {
    };
    void before() override
    {
        beforeCalled = true;
    };
    void after() override
    {
        afterCalled = true;
    };
    void setup_test_track() override
    {
        setupTestTrackCalled = true;
        run(&TestSuite::first_test, "first_test");
        run(&TestSuite::first_test, "first_test_again1");
        run(&TestSuite::first_test, "first_test_again2");
        run(&TestSuite::third_test, "third_test");
        run(&TestSuite::third_test, "third_test_again");
    };
    void first_test(const std::string& test_case_name)
    {
        firstCalled = true;
        ++testExecutionCounterOFirstTest;
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void second_test(const std::string& test_case_name)
    {
        secondCalled = true;
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void third_test(const std::string& test_case_name)
    {
        ++testExecutionCounterOThirdTest;
        complete_test_case(test_case_name, test_outcome::pass);
    }
    bool setupTestTrackCalled;
    bool beforeCalled;
    bool afterCalled;
    bool firstCalled;
    bool secondCalled;
    int testExecutionCounterOFirstTest;
    int testExecutionCounterOThirdTest;
private:
    int d_iParam;
};

class TestAfterConstruct : public g2::fasth::suite<TestAfterConstruct> {
public:
    TestAfterConstruct()
        :suite("TestAfterConstruct", g2::fasth::test_order::implied, g2::fasth::log_level::SILENT)
        , second_test_executed(false) {
    };
    void setup_test_track() override
    {
        run(&TestAfterConstruct::first_test, "first_test");
        run(&TestAfterConstruct::second_test, "second_test").after_success_of(&TestAfterConstruct::first_test);
    };
    void first_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::fail);
    }
    void second_test(const std::string& test_case_name)
    {
        second_test_executed = true;
        complete_test_case(test_case_name, test_outcome::pass);
    }
    bool second_test_executed;
};

TEST_CASE("Test Run Spec should throw exception on calling after without scheduling test case") {
    g2::fasth::test_run_spec<TestSuite> spec;
    REQUIRE_THROWS(spec.after(&TestSuite::first_test));
}

TEST_CASE("Test Run Spec should throw exception on calling after_success_of without scheduling test case") {
    g2::fasth::test_run_spec<TestSuite> spec;
    REQUIRE_THROWS(spec.after_success_of(&TestSuite::first_test));
}

TEST_CASE("Test Run Spec should return false on calling testcaseExists if no test exists") {
    TestSuite testsuite;
    g2::fasth::test_run_spec<TestSuite> spec;
    REQUIRE(testsuite.are_all_tests_completed());
}

TEST_CASE("Test Run Spec should schedule test case on calling schedule") {
    TestSuite testsuite;
    g2::fasth::test_run_spec<TestSuite> spec;
    testsuite.run(&TestSuite::first_test, "sample_test");
    REQUIRE_FALSE(testsuite.are_all_tests_completed());
}

TEST_CASE("Test Run Spec should validate parent method on calling after") {
    TestSuite testsuite;
    g2::fasth::test_run_spec<TestSuite> spec;
    testsuite.run(&TestSuite::first_test, "sample_test");
    REQUIRE_THROWS(spec.after(&TestSuite::second_test));
}

TEST_CASE("Test Run Spec should validate parent method on calling after_success_of") {
    TestSuite testsuite;
    g2::fasth::test_run_spec<TestSuite> spec;
    testsuite.run(&TestSuite::first_test, "sample_test");
    REQUIRE_THROWS(spec.after_success_of(&TestSuite::second_test));
}

TEST_CASE("Test Run Spec should set pointer on calling after after scheduling a test case") {
    TestSuite testsuite;
    g2::fasth::test_run_spec<TestSuite> spec;
    testsuite.run(&TestSuite::first_test, "sample1_test");
    testsuite.run(&TestSuite::second_test, "sample2_test");
    testsuite.instance("sample2_test").after_success_of(&TestSuite::first_test);
    REQUIRE_FALSE(testsuite.are_all_tests_completed());
}

TEST_CASE("Test Suite should setup test track before execution") {
    TestSuite testsuite;
    testsuite.execute();
    REQUIRE(testsuite.setupTestTrackCalled);
}

TEST_CASE("Test Suite should call before before execution of each test") {
    TestSuite testsuite;
    testsuite.execute();
    REQUIRE(testsuite.beforeCalled);
}

TEST_CASE("Test Suite should call after after execution of each test") {
    TestSuite testsuite;
    testsuite.execute();
    REQUIRE(testsuite.afterCalled);
}

TEST_CASE("Test Suite should execute only test cases present in test track") {
    TestSuite testsuite;
    testsuite.execute();
    REQUIRE(testsuite.firstCalled);
    REQUIRE(!testsuite.secondCalled);
}

TEST_CASE("Test Suite should execute test cases scheduled multiple times present in test track") {
    TestSuite testsuite;
    testsuite.execute();
    REQUIRE(testsuite.firstCalled);
    REQUIRE(!testsuite.secondCalled);
    REQUIRE(testsuite.testExecutionCounterOFirstTest == 3);
    REQUIRE(testsuite.testExecutionCounterOThirdTest == 2);
}

TEST_CASE("Test case should not be executed and marked as failed test if dependent test has failed") {
    TestAfterConstruct testsuite;
    testsuite.execute();
    REQUIRE_FALSE(testsuite.second_test_executed);
}