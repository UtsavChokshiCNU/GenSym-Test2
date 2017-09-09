#include "catch.hpp"
#include "gsi_callbacks.h"
#include "libgsi.hpp"

#include <cstring>

TEST_CASE("Conversion from string to Gensym string and back") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.continuous(false);
    gsiobj.port(22041);
    gsiobj.startgsi();

    short gensym_str[100];
    gsiobj.gensym_string("Test string", gensym_str, 100);
    std::string result = gsiobj.c_string(gensym_str);
    REQUIRE(result == "Test string");
}

TEST_CASE("Conversion from wide string to Gensym string and back") {
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();

    short gensym_str[100];
    gsiobj.gensym_string(L"Test wide string", gensym_str, 100);
    std::wstring result = gsiobj.wide_string(gensym_str);
    REQUIRE(result == L"Test wide string");
}