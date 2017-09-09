#include <cstring>
#include <iostream>
#include <signal.h>
#include "g2fasth.hpp"

#ifdef WIN32
#include <io.h>
#include <stdio.h>
#else
#include <unistd.h>
#endif

static const char kLogLevelFlag[] = "log_level";
static const char kOutputFlag[] = "output";
static const char kReportFlag[] = "report";

g2::fasth::g2_options::g2_options() : d_log_level(0), d_init(0), d_logger(g2::fasth::log_level::REGULAR)
{
    d_logger.add_output_stream(std::cout, g2::fasth::log_level::REGULAR);
}

const char* g2::fasth::g2_options::parse_flag_value(const char* str, const char* flag, bool def_optional) {
    // str and flag must not be NULL.
    if (str == nullptr || flag == nullptr)
        return nullptr;

    // The flag must start with "-".
    const std::string flag_str = std::string("-") + flag;
    const size_t flag_len = flag_str.length();
    if (strncmp(str, flag_str.c_str(), flag_len) != 0)
        return nullptr;

    // Skips the flag name.
    const char* flag_end = str + flag_len;

    // When def_optional is true, it's OK to not have a "=value" part.
    if (def_optional && (flag_end[0] == '\0')) {
        return flag_end;
    }

    if (flag_end[0] != '=')
        return nullptr;

    // Returns the string after "=".
    return flag_end + 1;
}

bool g2::fasth::g2_options::parse_bool_flag(const char* str, const char* flag, bool* value) {
    // Gets the value of the flag as a string.
    const char* const value_str = parse_flag_value(str, flag, true);
    if (value_str == nullptr)
        return false;

    // Converts the string value to a bool.
    *value = !(*value_str == '0' || *value_str == 'f' || *value_str == 'F');
    return true;
}

bool g2::fasth::g2_options::parse_int_flag(const char* str, const char* flag, int* value) {
    // Gets the value of the flag as a string.
    const char* const value_str = parse_flag_value(str, flag, false);
    if (value_str == nullptr)
        return false;

    // Sets *value to the value of the flag.
    *value = strtol(value_str, nullptr, 10);
    return true;
}

bool g2::fasth::g2_options::parse_string_flag(const char* str, const char* flag, std::string* value) {
    // Gets the value of the flag as a string.
    const char* const value_str = parse_flag_value(str, flag, false);
    if (value_str == nullptr)
        return false;

    // Sets *value to the value of the flag.
    *value = value_str;
    return true;
}

bool g2::fasth::g2_options::parse_flag(const char* const arg) {
    return parse_int_flag(arg, kLogLevelFlag, &d_log_level) ||
        parse_string_flag(arg, kOutputFlag, &d_output) ||
        parse_string_flag(arg, kReportFlag, &d_report);
}

void g2::fasth::g2_options::parse_flags_only(int* argc, char** argv) {
    for (int i = 1; i < *argc; i++) {
        const char* const argValue = argv[i];

        if (parse_flag(argValue)) {
            // Shift the remainder of the argv list left by one.
            memmove(&argv[i], &argv[i + 1], (*argc - i) * sizeof(char*));

            // Decrements the argument count.
            (*argc)--;

            // Decrement the iterator as we just removed an element.
            i--;
        }
    }
}

void g2::fasth::g2_options::parse_arguments(int* argc, char** argv)
{
    if (is_g2_tests_initialized())
        return;

    if (*argc <= 0)
        return; 

    d_init = *argc;
    parse_flags_only(argc, argv);
}

static volatile bool g_exit = true;
extern "C" void signal_handler( int sig_num )
{
    char* message = nullptr;
    switch (sig_num) {
    case SIGINT:
        message = "SIGINT - Terminal interrupt signal\n"; break;
    case SIGILL:
        message = "SIGILL - Illegal instruction signal\n"; break;
    case SIGFPE:
        message = "SIGFPE - Floating point error signal\n"; break;
    case SIGSEGV:
        message = "SIGSEGV - Segmentation violation signal\n"; break;
    case SIGTERM:
        message = "SIGTERM - Termination request signal\n"; break;
#ifdef WIN32
    case SIGBREAK:
        message = "SIGBREAK - Ctrl-Break sequence signal\n"; break;
#else
    case SIGUSR1:
    case SIGUSR2:
    case SIGALRM:
    case SIGVTALRM:
    case SIGPROF:
    case SIGCHLD:
    case SIGHUP:
    case SIGTTIN:
    case SIGTTOU:
    case SIGURG:
        //  Reset handler to catch signal next time.
        signal(sig_num, signal_handler);
        return;
#endif
    case SIGABRT:
        message = "SIGABRT - Abort (abnormal termination) signal"; break;
    default:
        message = "Unknown signal"; break;
    }

#ifdef WIN32
    _write(_fileno(stdout), message, strlen(message));
#else
    write(STDOUT_FILENO, message, strlen(message));
#endif
    if (g_exit)
        exit(0);
}

void g2::fasth::g2_options::set_signal_handler(bool exit)
{
    g_exit = exit;
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGINT handler");
    if (signal(SIGILL, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGILL handler");
    if (signal(SIGFPE, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGFPE handler");
    if (signal(SIGSEGV, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGSEGV handler");
    if (signal(SIGTERM, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGTERM handler");
#ifdef WIN32
    if (signal(SIGBREAK, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGBREAK handler");
#else
    if (signal(SIGUSR1, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGUSR1 handler");
    if (signal(SIGUSR2, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGUSR2 handler");
    if (signal(SIGALRM, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGALRM handler");
    if (signal(SIGVTALRM, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGVTALRM handler");
    if (signal(SIGPROF, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGPROF handler");
    if (signal(SIGCHLD, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGCHLD handler");
    if (signal(SIGHUP, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGHUP handler");
    if (signal(SIGTTIN, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGTTIN handler");
    if (signal(SIGTTOU, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGTTOU handler");
    if (signal(SIGURG, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGURG handler");
#endif
    if (signal(SIGABRT, signal_handler) == SIG_ERR)
        d_logger.log(g2::fasth::log_level::SILENT, "Can't set SIGABRT handler");
}
