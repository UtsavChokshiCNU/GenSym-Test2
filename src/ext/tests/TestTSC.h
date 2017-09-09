#ifndef _TEST_TSC_H
#define _TEST_TSC_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestTSC : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestTSC);
		CPPUNIT_TEST(testCellIndex);
		CPPUNIT_TEST(testTSCHandling);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testCellIndex();
	void testTSCHandling();
};

#endif
