#pragma once

#include <cppunit/extensions/HelperMacros.h>

class TestG2ChartView: public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(TestG2ChartView);
  CPPUNIT_TEST(testArrowKeys);
  CPPUNIT_TEST_SUITE_END();
  
public:
  void testArrowKeys();

  virtual void setUp();
	virtual void tearDown();
};