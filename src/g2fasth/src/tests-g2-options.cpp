#include <signal.h>
#include "catch.hpp"
#include "g2fasth.hpp"

using namespace g2::fasth;

TEST_CASE("is_g2_tests_initialized should be FALSE before initialization and TRUE after") {
    g2_options options;
    REQUIRE_FALSE(options.is_g2_tests_initialized());
    int argc = 1;
    char argv0[] = "test";
    char* argv[] = {argv0, nullptr};
    options.parse_arguments(&argc, argv);
    REQUIRE(options.is_g2_tests_initialized());
    REQUIRE(argc == 1);
    REQUIRE(argv[1] == 0);
}

TEST_CASE("parse_arguments should properly parse input arguments") {
    g2_options options;
    int argc = 4;
    char argv0[] = "test";
    char argv1[] = "-log_level=1";
    char argv2[] = "-output=x.log";
    char argv3[] = "-report=xml";
    char* argv[] = {argv0, argv1, argv2, argv3, nullptr};
    options.parse_arguments(&argc, argv);
    REQUIRE(options.get_log_level() == 1);
    REQUIRE(options.get_output_file() == std::string("x.log"));
    REQUIRE(options.get_report_type() == std::string("xml"));
    REQUIRE(argc == 1);
    REQUIRE(argv[1] == 0);
}

TEST_CASE("Options should stay uninitialized when flags do not match") {
    g2_options options;
    int argc = 4;
    char argv0[] = "test";
    char argv1[] = "-loglevel=1";
    char argv2[] = "-outpu=x.log";
    char argv3[] = "-reports=xml";
    char* argv[] = {argv0, argv1, argv2, argv3, nullptr};
    options.parse_arguments(&argc, argv);
    REQUIRE(options.get_log_level() == 0);
    REQUIRE(options.get_output_file() == std::string(""));
    REQUIRE(options.get_report_type() == std::string(""));
    REQUIRE(argc == 4);
    REQUIRE(argv[1] == std::string("-loglevel=1"));
}

TEST_CASE("Arguments should be parsed correctly if some flags match and some don't") {
    g2_options options;
    int argc = 4;
    char argv0[] = "test";
    char argv1[] = "-log_level=1";
    char argv2[] = "-outpu=x.log";
    char argv3[] = "-reports=xml";
    char* argv[] = {argv0, argv1, argv2, argv3, nullptr};
    options.parse_arguments(&argc, argv);
    REQUIRE(options.get_log_level() == 1);
    REQUIRE(options.get_output_file() == std::string(""));
    REQUIRE(options.get_report_type() == std::string(""));
    REQUIRE(argc == 3);
    REQUIRE(argv[1] == std::string("-outpu=x.log"));
}

TEST_CASE("Arguments should not be parsed when no values are provided") {
    g2_options options;
    int argc = 4;
    char argv0[] = "test";
    char argv1[] = "-log_level";
    char argv2[] = "-output";
    char argv3[] = "-report";
    char* argv[] = {argv0, argv1, argv2, argv3, nullptr};
    options.parse_arguments(&argc, argv);
    REQUIRE(options.get_log_level() == 0);
    REQUIRE(options.get_output_file() == std::string(""));
    REQUIRE(options.get_report_type() == std::string(""));
    REQUIRE(argc == 4);
    REQUIRE(argv[1] == std::string("-log_level"));
}

TEST_CASE("Options are not initialized with argc = 0") {
    g2_options options;
    int argc = 0;
    char* argv[] = {nullptr};
    options.parse_arguments(&argc, argv);
    REQUIRE_FALSE(options.is_g2_tests_initialized());
}

TEST_CASE("Options are not initialized with argc < 0") {
    g2_options options;
    int argc = -4;
    char* argv[] = {nullptr};
    options.parse_arguments(&argc, argv);
    REQUIRE_FALSE(options.is_g2_tests_initialized());
}

TEST_CASE("argv[] may contain null pointers") {
    g2_options options;
    int argc = 4;
    char argv0[] = "test";
    char argv2[] = "-output=x.log";
    char argv3[] = "-report=xml";
    char* argv[] = {argv0, nullptr, argv2, argv3, nullptr};
    options.parse_arguments(&argc, argv);
    REQUIRE(options.get_log_level() == 0);
    REQUIRE(options.get_output_file() == std::string("x.log"));
    REQUIRE(options.get_report_type() == std::string("xml"));
    REQUIRE(argc == 2);
    REQUIRE(argv[1] == 0);
}

TEST_CASE("Signal handling") {
    g2_options options;
    options.set_signal_handler(false);
    raise(SIGILL);
}
