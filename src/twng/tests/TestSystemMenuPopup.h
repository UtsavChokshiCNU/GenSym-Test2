#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CMainFrame;

class TestSystemMenuPopup :  public CPPUNIT_NS::TestFixture  
{
  CPPUNIT_TEST_SUITE(TestSystemMenuPopup);
    CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();

private:
	CMainFrame* m_pMainFrame;
};
