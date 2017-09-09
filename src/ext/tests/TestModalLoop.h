#ifndef _TEST_MODAL_LOOP_H_
#define _TEST_MODAL_LOOP_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// Tests for g2pvt_enter_modal_loop() and g2pvt_exit_modal_loop()
class CTestModalLoop : public CPPUNIT_NS::TestFixture  
{
    CPPUNIT_TEST_SUITE(CTestModalLoop);
		CPPUNIT_TEST(testEnterModalLoop);
		CPPUNIT_TEST(testExitModalLoop);
		CPPUNIT_TEST(testEnterExitModalLoop);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testEnterModalLoop();
	void testExitModalLoop();
	void testEnterExitModalLoop();
};

#endif
