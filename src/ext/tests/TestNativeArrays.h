#ifndef _TEST_NATIVE_ARRAYS_H_
#define _TEST_NATIVE_ARRAYS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// Tests for g2pvt_enter_modal_loop() and g2pvt_exit_modal_loop()
class CTestNativeArrays : public CPPUNIT_NS::TestFixture  
{
    CPPUNIT_TEST_SUITE(CTestNativeArrays);
		CPPUNIT_TEST(testIntegerArrays);
		CPPUNIT_TEST(testFloatArrays);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testIntegerArrays();
	void testFloatArrays();
};

#endif