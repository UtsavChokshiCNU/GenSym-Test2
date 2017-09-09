#ifndef _TEST_G2_LONGINT_H_
#define _TEST_G2_LONGINT_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
	#include "g2longint.h"
}

class TestG2Longint : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestG2Longint);
		CPPUNIT_TEST(testAllocation);
		CPPUNIT_TEST(testCopy);
		CPPUNIT_TEST(testSummation);
		CPPUNIT_TEST(testMultiplication);
		CPPUNIT_TEST(testDivision);
		CPPUNIT_TEST(testString2G2Longint);
		CPPUNIT_TEST(testGSIComposer);
		CPPUNIT_TEST(testG2Longint2Double);
		CPPUNIT_TEST(testG2Longint2String);
		CPPUNIT_TEST(testSubtraction);
		CPPUNIT_TEST(testPredicates);
		CPPUNIT_TEST(testICPComposition);
		CPPUNIT_TEST(testOverflow);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	void testAllocation();
	void testCopy();
	void testSummation();
	void testSubtraction();
	void testMultiplication();
	void testDivision();
	void testString2G2Longint();
	void testG2Longint2String();
	void testGSIComposer();
	void testG2Longint2Double();
	void testPredicates();
	void testICPComposition();
	void testOverflow();
};

#endif