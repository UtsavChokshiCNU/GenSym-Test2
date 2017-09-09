#pragma once

#include <cppunit/extensions/HelperMacros.h>

class JServerMessage;

class TestJServerMessages: public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(TestJServerMessages);
  CPPUNIT_TEST(Test);
  CPPUNIT_TEST_SUITE_END();
  
public:
  void Test();

private:

	bool TestSetIntXML() const;
	bool TestSetStringXML() const;
	bool TestSetDoubleXML() const;
	bool TestSetDoubleArrayXML() const;
	bool TestCreateXML() const;
	bool TestServerSimpleMessage(JServerMessage&, long, CString) const;
	bool TestExportAction() const;

};
