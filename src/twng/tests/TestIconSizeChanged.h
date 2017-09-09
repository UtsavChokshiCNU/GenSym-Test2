#ifndef _TEST_ICONSIZECHANGED_H_
#define _TEST_ICONSIZECHANGED_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


/*
 * Class that contains TWNG focus-changed test
 */

class TestIconSizeChanged : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestIconSizeChanged);
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	void test();

};

#endif