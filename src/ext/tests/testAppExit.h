#ifndef _TEST_APP_EXIT_H_
#define _TEST_APP_EXIT_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestAppExit : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestAppExit);
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();
};

#endif //_TEST_APP_EXIT_H_
