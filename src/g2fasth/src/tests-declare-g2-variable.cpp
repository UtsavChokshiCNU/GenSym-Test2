#include "catch.hpp"
#include "suite.hpp"

#include "libgsi.hpp"

TEST_CASE("G2 variable declartion with not registered ignored") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("T1-VAR-1"));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("T1-VAR-2"));

    g2::fasth::libgsi::getInstance().ignore_not_registered_variables();
    g2::fasth::libgsi::variable_map vars = gsiobj.get_g2_variables();

    REQUIRE(1 == vars.count("T1-VAR-1"));
    REQUIRE(vars.find("T1-VAR-1")->second->dec_type == g2::fasth::g2_integer);

    REQUIRE(1 == vars.count("T1-VAR-2"));
    REQUIRE(vars.find("T1-VAR-2")->second->dec_type == g2::fasth::g2_float);

    REQUIRE(0 == gsiobj.get_not_registered_variables().size());
}

TEST_CASE("Variable duplicate declartion is not allowed") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("T2-VAR-1"));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("T2-VAR-2"));

    REQUIRE(false == gsiobj.declare_g2_variable<int>("T2-VAR-1")); // same name, same type
    REQUIRE(false == gsiobj.declare_g2_variable<int>("T2-VAR-2")); // same name, other type
}

TEST_CASE("G2 variable declartion with not registered not ignored") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("T3-VAR-1"));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("T3-VAR-2"));

    g2::fasth::libgsi::getInstance().dont_ignore_not_registered_variables();

    REQUIRE(0 != gsiobj.get_not_registered_variables().size());
}

