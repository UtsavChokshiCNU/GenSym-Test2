#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;

class TestSuiteCycle : public suite<TestSuiteCycle> {
public:
    TestSuiteCycle()
        :suite("TestSuiteCycle", test_order::implied, log_level::NONE) {
    };
    void setup_test_track() override
    {
        run(&TestSuiteCycle::first_test, "first_test");
        run(&TestSuiteCycle::second_test, "second_test").after(&TestSuiteCycle::first_test);
        run(&TestSuiteCycle::first_test, "third_test").after(&TestSuiteCycle::second_test);
        run(&TestSuiteCycle::first_test, "first_test").after(&TestSuiteCycle::third_test);
    };
    void first_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void second_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void third_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

class TestSuiteAfterSuccessOfCycle : public suite<TestSuiteAfterSuccessOfCycle> {
public:
    TestSuiteAfterSuccessOfCycle()
        :suite("TestSuiteAfterSuccessOfCycle", test_order::implied, log_level::SILENT) {
    };
    void setup_test_track() override
    {
        run(&TestSuiteAfterSuccessOfCycle::first_test, "first_test");
        run(&TestSuiteAfterSuccessOfCycle::second_test, "second_test").after_success_of(&TestSuiteAfterSuccessOfCycle::first_test);
        run(&TestSuiteAfterSuccessOfCycle::first_test, "third_test").after_success_of(&TestSuiteAfterSuccessOfCycle::second_test);
        run(&TestSuiteAfterSuccessOfCycle::first_test, "first_test").after_success_of(&TestSuiteAfterSuccessOfCycle::third_test);
    };
    void first_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void second_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void third_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

class TestSuiteSameTestCase : public suite<TestSuiteSameTestCase> {
public:
    TestSuiteSameTestCase()
        :suite("TestSuiteSameTestCase", test_order::implied, log_level::SILENT) {
    };
    void setup_test_track() override
    {
        run(&TestSuiteSameTestCase::first_test, "first_test");
        run(&TestSuiteSameTestCase::first_test, "first_test").after(&TestSuiteSameTestCase::first_test);
    };
    void first_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

class TestSuiteSameSuccessTestCase : public suite<TestSuiteSameSuccessTestCase> {
public:
    TestSuiteSameSuccessTestCase()
        :suite("TestSuiteSameSuccessTestCase", test_order::implied, log_level::NONE) {
    };
    void setup_test_track() override
    {
        run(&TestSuiteSameSuccessTestCase::first_test, "first_test");
        run(&TestSuiteSameSuccessTestCase::first_test, "first_test").after_success_of(&TestSuiteSameSuccessTestCase::first_test);
    };
    void first_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

TEST_CASE("Test suite should throw exception if it detects cycle in after construct") {
    TestSuiteCycle testsuite;
    REQUIRE_THROWS(testsuite.setup_test_track());
}

TEST_CASE("Test suite should throw exception if it detects cycle in after_success_of construct") {
    TestSuiteAfterSuccessOfCycle testsuite;
    REQUIRE_THROWS(testsuite.setup_test_track());
}

TEST_CASE("Test suite should throw exception if same test is scheduled as dependent test case in after construct") {
    TestSuiteSameTestCase testsuite;
    REQUIRE_THROWS(testsuite.setup_test_track());
}

TEST_CASE("Test suite should throw exception if same test is scheduled as dependent test case in after_success_of construct") {
    TestSuiteSameSuccessTestCase testsuite;
    REQUIRE_THROWS(testsuite.setup_test_track());
}

class ParallelTestCases : public suite<ParallelTestCases> {
public:
    tthread::mutex d_mutex;
    std::string log;
    ParallelTestCases()
        :suite("ParallelTestCases", test_order::implied, log_level::NONE) {
    };
    void test(const std::string& test_case_name)
    {
        add_log(">");
        tthread::this_thread::sleep_for(chrono::milliseconds(3000));
        complete_test_case(test_case_name, test_outcome::pass);
        add_log("<");
    }
    void add_log(const std::string& s)
    {
        tthread::lock_guard<tthread::mutex> lg(d_mutex);
        log += s;
    }
};

TEST_CASE("Parallel test case execution") {
    ParallelTestCases ts;

    for (long long i=1; i<=4; i++)
        ts.run(&ParallelTestCases::test, std::to_string(i));

    ts.execute("");

    REQUIRE(ts.log.length() == 8);
}

class TestCaseSeries : public suite<TestCaseSeries> {
    tthread::mutex d_mutex;
public:
    int count;
    std::string log;
    TestCaseSeries()
        :suite("TestCaseSeries"), count(0) {
    };
    TestCaseSeries(test_order to)
        :suite("TestCaseSeries", to, log_level::NONE), count(0) {
    };
    void test1(const std::string& test_case_name)
    {
        {
            tthread::lock_guard<tthread::mutex> lg(d_mutex);
            count++;
        }
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void test2(const std::string& test_case_name)
    {
        {
            tthread::lock_guard<tthread::mutex> lg(d_mutex);
            log += test_case_name;
        }
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

class ManualTestCaseExec : public suite<ManualTestCaseExec> {
public:
    std::string log;
    ManualTestCaseExec()
        :suite("ManualTestCaseExec", test_order::implied, log_level::NONE) {
            set_parallel(false);
    };
    void test(const std::string& test_case_name)
    {
        log += test_case_name;
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

TEST_CASE("Test case series") {
    TestCaseSeries ts;
    ts.set_parallel(false);

    int count = 10;
    ts.run_series(count, &TestCaseSeries::test1, "t");

    ts.execute("");

    REQUIRE(ts.count == count);
}

TEST_CASE("Test case series, implied, sequential") {
    TestCaseSeries ts(test_order::implied);
    ts.set_parallel(false);

    std::string log;
    int count = 10;
    ts.run_series(count, &TestCaseSeries::test2, "t");
    
    for (int i=0; i<count; i++)
        log += "t." + std::to_string((long long)i);

    ts.execute("");

    REQUIRE(ts.log == log);
}

TEST_CASE("Manual test case execution - without execution of all test cases") {
    ManualTestCaseExec ts;

    ts.run(&ManualTestCaseExec::test, "1");
    ts.run(&ManualTestCaseExec::test, "2");

    ts.execute_test_case("1");

    REQUIRE(ts.log == "1");
}

TEST_CASE("Manual test case execution - exception on not scheduled test case") {
    ManualTestCaseExec ts;

    ts.run(&ManualTestCaseExec::test, "1");
    ts.run(&ManualTestCaseExec::test, "2");

    REQUIRE_THROWS(ts.execute_test_case("3"));
}

TEST_CASE("Manual test case execution - exception after execution of all test cases") {
    ManualTestCaseExec ts;

    ts.run(&ManualTestCaseExec::test, "1");
    ts.run(&ManualTestCaseExec::test, "2");

    ts.execute("");

    REQUIRE_THROWS(ts.execute_test_case("1"));
    REQUIRE(ts.log == "12");
}

TEST_CASE("Manual test case execution - exception after execution the same test case") {
    ManualTestCaseExec ts;

    ts.run(&ManualTestCaseExec::test, "1");
    ts.run(&ManualTestCaseExec::test, "2");

    ts.execute_test_case("1");

    REQUIRE_THROWS(ts.execute_test_case("1"));
    REQUIRE(ts.log == "1");
}

TEST_CASE("Manual test case execution - exception because of dependence was not executed") {
    ManualTestCaseExec ts;

    auto& t1 = ts.run(&ManualTestCaseExec::test, "1");
    ts.run(&ManualTestCaseExec::test, "2").after(t1);

    REQUIRE_THROWS(ts.execute_test_case("2"));
}


TEST_CASE("Manual test case execution - workaround exception after execution of all test cases") {
    ManualTestCaseExec ts;

    ts.run(&ManualTestCaseExec::test, "1");
    ts.run(&ManualTestCaseExec::test, "2");

    ts.execute("");
    ts.execute_test_case("1",true);

    REQUIRE(ts.log == "121");
}

TEST_CASE("Manual test case execution - workaround exception after execution the same test case") {
    ManualTestCaseExec ts;

    ts.run(&ManualTestCaseExec::test, "1");
    ts.run(&ManualTestCaseExec::test, "2");

    ts.execute_test_case("1");
    ts.execute_test_case("1",true);

    REQUIRE(ts.log == "11");
}

TEST_CASE("Manual test case execution - workaround exception because of dependence was not executed") {
    ManualTestCaseExec ts;

    auto& t1 = ts.run(&ManualTestCaseExec::test, "1");
    ts.run(&ManualTestCaseExec::test, "2").after(t1);

    ts.execute_test_case("2", true);

    REQUIRE(ts.log == "2");
}
