#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;

class TestBeforeAfterConstruct : public suite<TestBeforeAfterConstruct> {
public:
    TestBeforeAfterConstruct()
        : suite("TestBeforeAfterConstruct", test_order::implied, g2::fasth::log_level::SILENT)
    {
    }
    void before() override
    {
        output.push_back("before");
    };
    void after() override
    {
        output.push_back("after");
    };
    void setup_test_track() override
    {
        run(&TestBeforeAfterConstruct::first_test, "first_test");
        run(&TestBeforeAfterConstruct::second_test, "second_test");
    };
    void first_test(const std::string& test_case_name)
    {
        output.push_back("first_test");
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void second_test(const std::string& test_case_name)
    {
        output.push_back("second_test");
        complete_test_case(test_case_name, test_outcome::pass);
    }
    std::vector<std::string> output;
};

TEST_CASE("Before and after should be called in correct sequence while executing of test case") {
    TestBeforeAfterConstruct testsuite;
    testsuite.set_parallel(false);
    testsuite.execute();
    std::stringstream imploded;
    for (auto i = 0; i < testsuite.output.size(); ++i)
    {
        if (i != 0)
            imploded << ",";
        imploded << testsuite.output[i];
    }
    REQUIRE(imploded.str() == "before,first_test,after,before,second_test,after");
}
