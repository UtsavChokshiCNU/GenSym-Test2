#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;

std::string stringify_output(std::vector<g2::fasth::test_result> results)
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

class TestExecutionScenario1 : public g2::fasth::suite<TestExecutionScenario1> {
public:
    TestExecutionScenario1()
        : suite("TestExecutionScenario1", g2::fasth::test_order::implied, g2::fasth::log_level::NONE)
        , output("") {
		set_parallel(false);
    };
    void setup_test_track_scenario1()
    {
        // C->B->A (all test cases pass)
        run(&TestExecutionScenario1::first_test, "A");
        run(&TestExecutionScenario1::second_test, "B").after(&TestExecutionScenario1::first_test);
        run(&TestExecutionScenario1::third_test, "C").after(&TestExecutionScenario1::second_test);
    };
    void setup_test_track_scenario2()
    {
        // C->B->D  (some test cases pass)
        run(&TestExecutionScenario1::fourth_test, "D");
        run(&TestExecutionScenario1::second_test, "B").after(&TestExecutionScenario1::fourth_test);
        run(&TestExecutionScenario1::third_test, "C").after(&TestExecutionScenario1::second_test);
    };
    void setup_test_track_scenario3()
    {
        // C->B=>D  (some test cases pass)
        run(&TestExecutionScenario1::fourth_test, "D");
        run(&TestExecutionScenario1::second_test, "B").after_success_of(&TestExecutionScenario1::fourth_test);
        run(&TestExecutionScenario1::third_test, "C").after(&TestExecutionScenario1::second_test);
    };
    void setup_test_track_scenario4()
    {
        // C=>B=>D  (some test cases pass)
        run(&TestExecutionScenario1::fourth_test, "D");
        run(&TestExecutionScenario1::second_test, "B").after_success_of(&TestExecutionScenario1::fourth_test);
        run(&TestExecutionScenario1::third_test, "C").after_success_of(&TestExecutionScenario1::second_test);
    };
    void setup_test_track_scenario5()
    {
        set_parallel(false);
        // B->A (all test cases pass)
        // B->D (some test cases pass)
        run(&TestExecutionScenario1::first_test, "A");
        run(&TestExecutionScenario1::fourth_test, "D");
        run(&TestExecutionScenario1::second_test, "B").after(&TestExecutionScenario1::first_test);
        run(&TestExecutionScenario1::second_test, "B").after_success_of(&TestExecutionScenario1::fourth_test);
    };
    void setup_test_track_scenario6()
    {
        // C->B->A (all test cases pass)
        auto &first_run = run(&TestExecutionScenario1::first_test, "A");
        auto &second_run = run(&TestExecutionScenario1::second_test, "B").after(first_run);
        run(&TestExecutionScenario1::third_test, "C").after(second_run);
    };
    void setup_test_track_scenario7()
    {
        // C->B->D  (some test cases pass)
        auto &first_run = run(&TestExecutionScenario1::fourth_test, "D");
        auto &second_run = run(&TestExecutionScenario1::second_test, "B").after(first_run);
        run(&TestExecutionScenario1::third_test, "C").after(second_run);
    };
    void setup_test_track_scenario8()
    {
        // C->B=>D  (some test cases pass)
        auto &first_run = run(&TestExecutionScenario1::fourth_test, "D");
        auto &second_run = run(&TestExecutionScenario1::second_test, "B").after_success_of(first_run);
        run(&TestExecutionScenario1::third_test, "C").after(second_run);
    };
    void setup_test_track_scenario9()
    {
        // C=>B=>D  (some test cases pass)
        auto &d_run = run(&TestExecutionScenario1::fourth_test, "D");
        auto &b_run = run(&TestExecutionScenario1::second_test, "B").after_success_of(d_run);
        run(&TestExecutionScenario1::third_test, "C").after_success_of(b_run);
    };
    void setup_test_track_scenario10()
    {
        set_parallel(false);
        // B->A (all test cases pass)
        // B->D (some test cases pass)
        auto &a_run = run(&TestExecutionScenario1::first_test, "A");
        auto &d_run = run(&TestExecutionScenario1::fourth_test, "D");
        auto &b_run = run(&TestExecutionScenario1::second_test, "B").after(a_run);
        run(&TestExecutionScenario1::second_test, "B").after_success_of(d_run);
    };
    void setup_test_track_scenario11()
    {
        set_parallel(false);
        // C->B->A (all test cases pass)
        run(&TestExecutionScenario1::first_test, "A");
        run(&TestExecutionScenario1::second_test, "B");
        run(&TestExecutionScenario1::third_test, "C");
        run(&TestExecutionScenario1::second_test, "B").after(instance("D"));
    }
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

TEST_CASE("Test suite should execute sync test cases in correct order specified after construct (Scenario 1).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario1();
    test_suite.execute();
    REQUIRE(test_suite.output == "<A><B><C>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Pass,Pass,Pass");
}

TEST_CASE("Test suite should execute sync test cases in correct order specified after construct (Scenario 2).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario2();
    test_suite.execute();
    REQUIRE(test_suite.output == "<D><B><C>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Fail,Pass,Pass");
}

TEST_CASE("Test case should fail and not execute if dependent test case (after_success_of) fails (Scenario 4).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario3();
    test_suite.execute();
    REQUIRE(test_suite.output == "<D><C>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Fail,Fail,Pass");
}

TEST_CASE("Test case should fail and not execute if dependent test case (after_success_of) fails (Scenario 5).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario4();
    test_suite.execute();
    REQUIRE(test_suite.output == "<D>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Fail,Fail,Fail");
}

TEST_CASE("Test case should still execute even if dependent test case (after) fails (Scenario 1).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario5();
    test_suite.execute();
    REQUIRE(test_suite.output == "<A><D>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Pass,Fail,Fail");
}

TEST_CASE("Test case should still execute even if dependent test case (after) fails (Scenario 2).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario6();
    test_suite.execute();
    REQUIRE(test_suite.output == "<A><B><C>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Pass,Pass,Pass");
}

TEST_CASE("Test case should still execute even if dependent test case (after) fails (Scenario 3).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario7();
    test_suite.execute();
    REQUIRE(test_suite.output == "<D><B><C>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Fail,Pass,Pass");
}

TEST_CASE("Test case should fail and not execute if dependent test case (after_success_of) fails (Scenario 1).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario9();
    test_suite.execute();
    REQUIRE(test_suite.output == "<D>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Fail,Fail,Fail");
}

TEST_CASE("Test case should fail and not execute if dependent test case (after_success_of) fails (Scenario 2).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario10();
    test_suite.execute();
    REQUIRE(test_suite.output == "<A><D>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Pass,Fail,Fail");
}

TEST_CASE("Test case should fail and not execute if dependent test case (after_success_of) fails (Scenario 3).") {
    TestExecutionScenario1 test_suite;
    test_suite.setup_test_track_scenario8();
    test_suite.execute();
    REQUIRE(test_suite.output == "<D><C>");
    REQUIRE(stringify_output(test_suite.get_results()) == "Fail,Fail,Pass");
}

TEST_CASE("Setup phase should throw exception if a test used in after construct is not scheduled before.") {
    TestExecutionScenario1 test_suite;
    REQUIRE_THROWS(test_suite.setup_test_track_scenario11());
}