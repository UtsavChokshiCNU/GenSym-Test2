#ifndef _TEST_HANDLES_H_
#define _TEST_HANDLES_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/*
 * Class that contains G2 hanles tests
 */

class TestTabularView : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestTabularView );
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();
};

#endif
