#ifndef _TEST_APPEND_NMS_MENU_H_
#define _TEST_APPEND_NMS_MENU_H_


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/*
 * Class that contains G2 hanles tests
 */

class TestAppendNmsMenu : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestAppendNmsMenu);
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();
};

#endif
