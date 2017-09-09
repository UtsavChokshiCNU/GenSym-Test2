#pragma once
#include "suite.hpp"
#include "libgsi.hpp"

using namespace g2::fasth;

class RegTestSuite : public suite<RegTestSuite>
{
public:
    RegTestSuite(std::string suite_name): suite(suite_name, test_order::implied, g2::fasth::log_level::VERBOSE)
        , gsi(libgsi::getInstance()) {}

    void test_3227(const std::string&);
    void test_3228(const std::string&);
    void test_3229(const std::string&);
    void test_3230(const std::string&);

private:
    libgsi& gsi;
    void setup_test_track() override;
};
