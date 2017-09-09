#include "catch.hpp"
#include "suite.hpp"

class TestResults : public g2::fasth::suite<TestResults> {
public:
    TestResults()
        : suite("TestResults", g2::fasth::test_order::implied, g2::fasth::log_level::SILENT) {
    }
};

TEST_CASE("There should not be any test results if there is no test case to execute.") {
    TestResults test_suite;
    test_suite.execute();
    auto results = test_suite.get_results();
    REQUIRE(results.size() == 0);
}