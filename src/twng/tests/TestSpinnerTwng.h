#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>



class CWnd;
class CSpinnerTwng;
class TestSpinnerTwng : public CPPUNIT_NS::TestFixture  
{
	CPPUNIT_TEST_SUITE(TestSpinnerTwng);
    CPPUNIT_TEST(testSpinnerResize);
	CPPUNIT_TEST_SUITE_END();
public:
	virtual void setUp();
	virtual void tearDown();
	void testSpinnerResize();
private:

	CWnd* mainWindow;
	CSpinnerTwng * spinnertwng;
};
