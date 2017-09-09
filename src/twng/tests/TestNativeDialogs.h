#ifndef _TEST_NATIVEDIALOGS_H_
#define _TEST_NATIVEDIALOGS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/*
 * Class that contains Native Dialog pos for multi monitors test
 */


class TestNativeDialogs : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestNativeDialogs);
		CPPUNIT_TEST(testGetMonitorRect);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	void testGetMonitorRect();
private:

};

#endif