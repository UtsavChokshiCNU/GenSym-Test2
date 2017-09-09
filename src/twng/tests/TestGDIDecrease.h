#ifndef _TEST_GDIDECREASE_H_
#define _TEST_GDIDECREASE_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/*
 * Class that contains TWNG GDI Decreasing test
 */

class TestGdiDecrease : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestGdiDecrease);
		CPPUNIT_TEST(IconDestroy);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void IconDestroy();
};

#endif
