#ifndef _TEST_MORE_WINDOWS_MENU_H_
#define _TEST_MORE_WINDOWS_MENU_H_


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/*
 * Class that contains G2 hanles tests
 */

class TestMoreWindowsMenu : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestMoreWindowsMenu);
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();
};

#endif
