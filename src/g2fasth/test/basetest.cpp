#include <stdio.h>
#include "suite.hpp"
#include "MySuite.hpp"
#include "g2fasth.hpp"
#include "test_agent.hpp"

#include "libgsi.hpp"

using namespace g2::fasth;

int main(int argc, char **argv) {
    g2_options options;
    options.parse_arguments(&argc, argv);
    options.set_signal_handler();

    auto suiteA = std::make_shared<MySuite>("SuiteA", 0, "TestValue", false, options.get_output_file());
    suiteA->run(&MySuite::first_test, "first_test");

    auto suiteB = std::make_shared<MySuite>("SuiteB", 100, "AnotherValue", true, options.get_output_file());

    g2::fasth::test_agent agent;
    agent.schedule_suite(suiteB);
    agent.schedule_suite(suiteA, suiteB);

    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.continuous(true);
    gsiobj.port(22040);
    agent.execute();
    gsiobj.startgsi();

    return 0;
}