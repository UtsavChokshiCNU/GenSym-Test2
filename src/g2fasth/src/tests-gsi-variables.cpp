#include "catch.hpp"
#include "libgsi.hpp"

int int_handler()
{
    return 1234;
}

double float_handler()
{
    return 3.14;
}

bool bool_handler()
{
    return true;
}

std::string string_handler()
{
    return "String value from handler";
}

TEST_CASE("Tests returning the empty value when no other values are set") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.ignore_not_registered_variables();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("INT-VAR-0"));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("FLOAT-VAR-0"));
    REQUIRE(true == gsiobj.declare_g2_variable<bool>("BOOL-VAR-0"));
    REQUIRE(true == gsiobj.declare_g2_variable<std::string>("STRING-VAR-0"));

    g2::fasth::libgsi::variable_map vars = gsiobj.get_g2_variables();

    g2::fasth::g2_variable* int_ptr = vars.find("INT-VAR-0")->second.get();
    g2::fasth::g2_variable* float_ptr = vars.find("FLOAT-VAR-0")->second.get();
    g2::fasth::g2_variable* bool_ptr = vars.find("BOOL-VAR-0")->second.get();
    g2::fasth::g2_variable* string_ptr = vars.find("STRING-VAR-0")->second.get();

    REQUIRE(int_ptr->dec_type == g2::fasth::g2_integer);
    REQUIRE(float_ptr->dec_type == g2::fasth::g2_float);
    REQUIRE(bool_ptr->dec_type == g2::fasth::g2_logical);
    REQUIRE(string_ptr->dec_type == g2::fasth::g2_string);

    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 0);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 0.0);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == false);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "");
}

TEST_CASE("Tests handlers for providing a variable value") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.ignore_not_registered_variables();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("INT-VAR-1", int_handler));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("FLOAT-VAR-1", float_handler));
    REQUIRE(true == gsiobj.declare_g2_variable<bool>("BOOL-VAR-1", bool_handler));
    REQUIRE(true == gsiobj.declare_g2_variable<std::string>("STRING-VAR-1", string_handler));

    g2::fasth::libgsi::variable_map vars = gsiobj.get_g2_variables();

    g2::fasth::g2_variable* int_ptr = vars.find("INT-VAR-1")->second.get();
    g2::fasth::g2_variable* float_ptr = vars.find("FLOAT-VAR-1")->second.get();
    g2::fasth::g2_variable* bool_ptr = vars.find("BOOL-VAR-1")->second.get();
    g2::fasth::g2_variable* string_ptr = vars.find("STRING-VAR-1")->second.get();

    REQUIRE(int_ptr->dec_type == g2::fasth::g2_integer);
    REQUIRE(float_ptr->dec_type == g2::fasth::g2_float);
    REQUIRE(bool_ptr->dec_type == g2::fasth::g2_logical);
    REQUIRE(string_ptr->dec_type == g2::fasth::g2_string);

    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 1234);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 3.14);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == true);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "String value from handler");
}

TEST_CASE("Tests setting the default value which returns always") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.ignore_not_registered_variables();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("INT-VAR-2"));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("FLOAT-VAR-2"));
    REQUIRE(true == gsiobj.declare_g2_variable<bool>("BOOL-VAR-2"));
    REQUIRE(true == gsiobj.declare_g2_variable<std::string>("STRING-VAR-2"));

    REQUIRE(true == gsiobj.assign_def_value("INT-VAR-2", 60));
    REQUIRE(true == gsiobj.assign_def_value("FLOAT-VAR-2", 9.9));
    REQUIRE(true == gsiobj.assign_def_value("BOOL-VAR-2", false));
    REQUIRE(true == gsiobj.assign_def_value("STRING-VAR-2", std::string("Default string value")));

    g2::fasth::libgsi::variable_map vars = gsiobj.get_g2_variables();

    g2::fasth::g2_variable* int_ptr = vars.find("INT-VAR-2")->second.get();
    g2::fasth::g2_variable* float_ptr = vars.find("FLOAT-VAR-2")->second.get();
    g2::fasth::g2_variable* bool_ptr = vars.find("BOOL-VAR-2")->second.get();
    g2::fasth::g2_variable* string_ptr = vars.find("STRING-VAR-2")->second.get();

    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 60);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 9.9);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == false);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "Default string value");
}

TEST_CASE("Tests returning the value for just one read") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.ignore_not_registered_variables();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("INT-VAR-3"));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("FLOAT-VAR-3"));
    REQUIRE(true == gsiobj.declare_g2_variable<bool>("BOOL-VAR-3"));
    REQUIRE(true == gsiobj.declare_g2_variable<std::string>("STRING-VAR-3"));

    REQUIRE(true == gsiobj.assign_def_value("INT-VAR-3", 60));
    REQUIRE(true == gsiobj.assign_def_value("FLOAT-VAR-3", 9.9));
    REQUIRE(true == gsiobj.assign_def_value("BOOL-VAR-3", false));
    REQUIRE(true == gsiobj.assign_def_value("STRING-VAR-3", std::string("Default string value")));

    REQUIRE(true == gsiobj.assign_temp_value("INT-VAR-3", 90));
    REQUIRE(true == gsiobj.assign_temp_value("FLOAT-VAR-3", 19.9));
    REQUIRE(true == gsiobj.assign_temp_value("BOOL-VAR-3", true));
    REQUIRE(true == gsiobj.assign_temp_value("STRING-VAR-3", std::string("Temporary string value")));

    g2::fasth::libgsi::variable_map vars = gsiobj.get_g2_variables();

    g2::fasth::g2_variable* int_ptr = vars.find("INT-VAR-3")->second.get();
    g2::fasth::g2_variable* float_ptr = vars.find("FLOAT-VAR-3")->second.get();
    g2::fasth::g2_variable* bool_ptr = vars.find("BOOL-VAR-3")->second.get();
    g2::fasth::g2_variable* string_ptr = vars.find("STRING-VAR-3")->second.get();

    // First read
    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 90);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 19.9);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == true);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "Temporary string value");

    // Second read
    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 60);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 9.9);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == false);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "Default string value");
}

TEST_CASE("Tests returning the value for next N reads") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.ignore_not_registered_variables();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("INT-VAR-4"));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("FLOAT-VAR-4"));
    REQUIRE(true == gsiobj.declare_g2_variable<bool>("BOOL-VAR-4"));
    REQUIRE(true == gsiobj.declare_g2_variable<std::string>("STRING-VAR-4"));

    REQUIRE(true == gsiobj.assign_def_value("INT-VAR-4", 60));
    REQUIRE(true == gsiobj.assign_def_value("FLOAT-VAR-4", 9.9));
    REQUIRE(true == gsiobj.assign_def_value("BOOL-VAR-4", false));
    REQUIRE(true == gsiobj.assign_def_value("STRING-VAR-4", std::string("Default string value")));

    REQUIRE(true == gsiobj.assign_temp_value("INT-VAR-4", 90, 1));      // 1 read
    REQUIRE(true == gsiobj.assign_temp_value("FLOAT-VAR-4", 19.9, 2));  // 2 reads
    REQUIRE(true == gsiobj.assign_temp_value("BOOL-VAR-4", true, 2));   // 2 reads
    REQUIRE(true == gsiobj.assign_temp_value("STRING-VAR-4", std::string("Temporary string value"), 3));    // 3 reads

    g2::fasth::libgsi::variable_map vars = gsiobj.get_g2_variables();

    g2::fasth::g2_variable* int_ptr = vars.find("INT-VAR-4")->second.get();
    g2::fasth::g2_variable* float_ptr = vars.find("FLOAT-VAR-4")->second.get();
    g2::fasth::g2_variable* bool_ptr = vars.find("BOOL-VAR-4")->second.get();
    g2::fasth::g2_variable* string_ptr = vars.find("STRING-VAR-4")->second.get();

    // First read
    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 90);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 19.9);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == true);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "Temporary string value");

    // Second read
    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 60);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 19.9);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == true);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "Temporary string value");

    // Third read
    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 60);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 9.9);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == false);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "Temporary string value");

    // Fourth read
    REQUIRE(((g2::fasth::g2_typed_variable<int>*) int_ptr)->value() == 60);
    REQUIRE(((g2::fasth::g2_typed_variable<double>*) float_ptr)->value() == 9.9);
    REQUIRE(((g2::fasth::g2_typed_variable<bool>*) bool_ptr)->value() == false);
    REQUIRE(((g2::fasth::g2_typed_variable<std::string>*) string_ptr)->value() == "Default string value");
}

TEST_CASE("Assigning to undeclared variable or variable with wrong type should fail") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.ignore_not_registered_variables();

    REQUIRE(true == gsiobj.declare_g2_variable<int>("INT-VAR-5"));
    REQUIRE(true == gsiobj.declare_g2_variable<double>("FLOAT-VAR-5"));
    REQUIRE(true == gsiobj.declare_g2_variable<bool>("BOOL-VAR-5"));
    REQUIRE(true == gsiobj.declare_g2_variable<std::string>("STRING-VAR-5"));

    REQUIRE(false == gsiobj.assign_def_value("INT-VAR-6", 60));
    REQUIRE(false == gsiobj.assign_def_value("FLOAT-VAR-6", 9.9));
    REQUIRE(false == gsiobj.assign_def_value("INT-VAR-5", false));
    REQUIRE(false == gsiobj.assign_def_value("BOOL-VAR-5", std::string("Default string value")));

    REQUIRE(false == gsiobj.assign_temp_value("BOOL-VAR-5", 90, 1));      // 1 read
    REQUIRE(false == gsiobj.assign_temp_value("STRING-VAR-5", 19.9, 2));  // 2 reads
    REQUIRE(false == gsiobj.assign_temp_value("BOOL-VAR-6", true, 2));   // 2 reads
    REQUIRE(false == gsiobj.assign_temp_value("STRING-VAR-6", std::string("Temporary string value"), 3));    // 3 reads
}
