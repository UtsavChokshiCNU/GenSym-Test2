#pragma once

#include <cppunit/extensions/HelperMacros.h>

class TestG2HtmlView: public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(TestG2HtmlView);
  CPPUNIT_TEST(testMouseWheel);
  CPPUNIT_TEST_SUITE_END();

public:
  void testMouseWheel();
};
