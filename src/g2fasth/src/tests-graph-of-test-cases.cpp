#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;

class TestSuiteComplexCycle : public g2::fasth::suite<TestSuiteComplexCycle> {
public:
    TestSuiteComplexCycle()
        :suite("TestSuiteComplexCycle", g2::fasth::test_order::implied, g2::fasth::log_level::SILENT) {
    };
    void setup_test_track() override
    {
        run(&TestSuiteComplexCycle::first_test, "first_test");
        run(&TestSuiteComplexCycle::second_test, "second_test").after(&TestSuiteComplexCycle::first_test);
        run(&TestSuiteComplexCycle::third_test, "third_test").after(&TestSuiteComplexCycle::second_test);
        run(&TestSuiteComplexCycle::first_test, "first_test").after_success_of(&TestSuiteComplexCycle::third_test);
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

TEST_CASE("Test suite should throw exception if it detects complex cycle") {
    TestSuiteComplexCycle testsuite;
    REQUIRE_THROWS(testsuite.setup_test_track());
}