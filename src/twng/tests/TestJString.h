#pragma once

#include <cppunit/extensions/HelperMacros.h>

class JString;

class TestJString: public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(TestJString);
  CPPUNIT_TEST(Test);
  CPPUNIT_TEST_SUITE_END();
  
public:
  void Test();
  bool Equal(const JString&, const JString&) const;

};
