#include <cstdio>
#include "rt-suite.hpp"

void RegTestSuite::setup_test_track()
{
    if (get_suite_name() == "3227")
        run(&RegTestSuite::test_3227, "Test-3227");
    else if (get_suite_name() == "3228")
        run(&RegTestSuite::test_3228, "Test-3228");
    else if (get_suite_name() == "3229")
        run(&RegTestSuite::test_3229, "Test-3229");
    else if (get_suite_name() == "3230")
        run(&RegTestSuite::test_3230, "Test-3230");
}

void RegTestSuite::test_3227(const std::string& test_case_name)
{
    std::list<std::string> not_dec_vars = gsi.get_not_declared_variables();
    if (not_dec_vars.size())
        complete_test_case(test_case_name, test_outcome::fail);
    else
        complete_test_case(test_case_name, test_outcome::pass);
}

void RegTestSuite::test_3228(const std::string& test_case_name)
{
    std::list<std::string> not_dec_vars = gsi.get_not_declared_variables();
    if (not_dec_vars.size())
        complete_test_case(test_case_name, test_outcome::fail);
    else
        complete_test_case(test_case_name, test_outcome::pass);
}

void RegTestSuite::test_3229(const std::string& test_case_name)
{
    std::list<std::string> not_reg_vars = gsi.get_not_registered_variables();
    if (not_reg_vars.size())
        complete_test_case(test_case_name, test_outcome::fail);
    else
        complete_test_case(test_case_name, test_outcome::pass);
}

void RegTestSuite::test_3230(const std::string& test_case_name)
{
    std::list<std::string> not_reg_vars = gsi.get_not_registered_variables();
    if (not_reg_vars.size())
        complete_test_case(test_case_name, test_outcome::fail);
    else
        complete_test_case(test_case_name, test_outcome::pass);
}

