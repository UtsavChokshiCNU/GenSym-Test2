#ifndef _FIXNUM_TIME_TEST_H_
#define _FIXNUM_TIME_TEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class FixnumTimeTest : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(FixnumTimeTest);
		CPPUNIT_TEST(TestGetInternalRealTimeRollback);
		CPPUNIT_TEST(TestGetInternalRealTimeInitialValue);
		CPPUNIT_TEST(TestGetInternalRealTimeCommonValue);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	FixnumTimeTest();
	void TestGetInternalRealTimeRollback();
	void TestGetInternalRealTimeInitialValue();
	void TestGetInternalRealTimeCommonValue();
private:
	unsigned long initial_time;
};

#endif
