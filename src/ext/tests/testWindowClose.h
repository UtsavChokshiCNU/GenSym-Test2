#ifndef _TEST_WINDOW_CLOSE_H_
#define _TEST_WINDOW_CLOSE_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestWindowClose : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestWindowClose);
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();
};

#endif //_TEST_WINDOW_CLOSE_H_
