#include <memory>
#include "catch.hpp"
#include "logger.hpp"

using namespace g2::fasth;

struct cout_redirect {
    cout_redirect(std::streambuf * new_buffer)
        : old(std::cout.rdbuf(new_buffer))
    { }

    ~cout_redirect() {
        std::cout.rdbuf(old);
    }

private:
    std::streambuf * old;
};

TEST_CASE("Logger should log in silent mode") {
    std::stringstream buffer;
    cout_redirect redirect(buffer.rdbuf());
    logger logger_instance(g2::fasth::log_level::SILENT);
    logger_instance.add_output_stream(std::cout, g2::fasth::log_level::SILENT);
    logger_instance.log(log_level::SILENT, "Sample Log");
    REQUIRE(buffer.str() == "Sample Log\n");
}

TEST_CASE("Logger set at higher log level should log data with lower log level") {
    std::stringstream d_buffer;
    cout_redirect redirect(d_buffer.rdbuf());
    logger logger_instance(g2::fasth::log_level::VERBOSE);
    logger_instance.add_output_stream(std::cout, g2::fasth::log_level::REGULAR);
    logger_instance.log(log_level::REGULAR, "Sample Log");
    REQUIRE(d_buffer.str() == "Sample Log\n");
}

TEST_CASE("Logger set at lower log level should not log data with higher log level") {
    std::stringstream d_buffer;
    cout_redirect redirect(d_buffer.rdbuf());
    logger logger_instance(g2::fasth::log_level::SILENT);
    logger_instance.add_output_stream(std::cout, g2::fasth::log_level::REGULAR);
    logger_instance.log(log_level::REGULAR, "Sample Log");
    REQUIRE(d_buffer.str().empty());
}