#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;

std::string string_output(std::vector<g2::fasth::test_result> results)
{
    std::stringstream imploded;
    for (int i = 0; i != results.size(); ++i)
    {
        if (i != 0)
            imploded << ",";
        imploded << test_outcome_str[(int)results[i].outcome()];
    }
    return imploded.str();
}

class TestFailRemaining : public g2::fasth::suite<TestFailRemaining> {
public:
    TestFailRemaining()
        : suite("TestFailRemaining", g2::fasth::test_order::implied, g2::fasth::log_level::NONE)
        , output("") {
            set_parallel(false);
    };
    void setup_test_track_scenario1()
    {
        run(&TestFailRemaining::first_test, "A");
        run(&TestFailRemaining::fourth_test, "D");
        run(&TestFailRemaining::second_test, "B").after(&TestFailRemaining::first_test);
        run(&TestFailRemaining::third_test, "C").after(&TestFailRemaining::fourth_test).guard([]{ return false; });
    };
    void setup_test_track_scenario2()
    {
        run(&TestFailRemaining::first_test, "A");
        run(&TestFailRemaining::fourth_test, "D");
        run(&TestFailRemaining::second_test, "B").after(&TestFailRemaining::fourth_test).guard([]{ return false; });
        run(&TestFailRemaining::third_test, "C").after(&TestFailRemaining::second_test);
    };
    void setup_test_track_scenario3()
    {
        run(&TestFailRemaining::first_test, "A");
        run(&TestFailRemaining::second_test, "B").after(&TestFailRemaining::first_test).guard([]{ return false; });
        run(&TestFailRemaining::third_test, "C").after(&TestFailRemaining::second_test);
        run(&TestFailRemaining::fourth_test, "D").after(&TestFailRemaining::third_test);
    };
    void first_test(const std::string& test_case_name)
    {
        output += "<A>";
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void second_test(const std::string& test_case_name)
    {
        output += "<B>";
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void third_test(const std::string& test_case_name)
    {
        output += "<C>";
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void fourth_test(const std::string& test_case_name)
    {
        output += "<D>";
        complete_test_case(test_case_name, test_outcome::fail);
    }
    std::string output;
};

TEST_CASE("Test suite should fail test case with unmet guard condition (Scenario 1).") {
    TestFailRemaining test_suite;
    test_suite.setup_test_track_scenario1();
    test_suite.execute();
    REQUIRE(test_suite.output == "<A><D><B>");
    REQUIRE(string_output(test_suite.get_results()) == "Pass,Fail,Pass,Fail");
}

TEST_CASE("Test suite should fail 2 test cases with unmet guard conditions (Scenario 2).") {
    TestFailRemaining test_suite;
    test_suite.setup_test_track_scenario2();
    test_suite.execute();
    REQUIRE(test_suite.output == "<A><D>");
    REQUIRE(string_output(test_suite.get_results()) == "Pass,Fail,Fail,Fail");
}

TEST_CASE("Test suite should fail 2 test cases with unmet guard conditions (Scenario 3).") {
    TestFailRemaining test_suite;
    test_suite.setup_test_track_scenario3();
    test_suite.execute();
    REQUIRE(test_suite.output == "<A>");
    REQUIRE(string_output(test_suite.get_results()) == "Pass,Fail,Fail,Fail");
}
