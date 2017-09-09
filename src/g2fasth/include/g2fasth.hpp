#pragma once
#ifndef INC_LIBG2FASTH_OPTIONS_H
#define INC_LIBG2FASTH_OPTIONS_H

#include <string>
#include "logger.hpp"

namespace g2 {
namespace fasth {
/// Parses and stores global G2FASTH options
class g2_options {
public:
    g2_options();
    /**
    * Initializes G2 test options using command line arguments
    * @param argc Commandline argument count
    * @param argv Commandline argument vector
    */
    void parse_arguments(int* argc, char** argv);
    /**
    * Checks if G2 test options are initialized.
    * @return True if G2 test options are initialized
    */
    bool is_g2_tests_initialized() const { return d_init > 0; }
    /**
    * Returns current log level
    * @return Log level
    */
    int get_log_level() const { return d_log_level; }
    /**
    * Returns path to output file
    * @return Output file
    */
    const std::string& get_output_file() const { return d_output; }
    /**
    * Returns current log level
    * @return Log level
    */
    const std::string& get_report_type() const { return d_report; }
    /**
    * Set OS signal handler
    */
    void set_signal_handler(bool exit = true);
private:
    /// Parses value for specified flag from string "flag=value"
    const char* parse_flag_value(const char* str, const char* flag, bool def_optional);
    /// Parses boolean value for specified flag
    bool parse_bool_flag(const char* str, const char* flag, bool* value);
    /// Parses integer value for specified flag
    bool parse_int_flag(const char* str, const char* flag, int* value);
    /// Parses string value for specified flag
    bool parse_string_flag(const char* str, const char* flag, std::string* value);
    /// Parses possible values for expected flag
    bool parse_flag(const char* const arg);
    /// Parses flags from command line arguments and removes parsed arguments
    void parse_flags_only(int* argc, char** argv);
    int d_log_level;
    std::string d_output;
    std::string d_report;
    int d_init;
    logger d_logger;
};
}
}

#endif // !INC_LIBG2FASTH_OPTIONS_H