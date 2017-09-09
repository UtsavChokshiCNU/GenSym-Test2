#ifndef _TEST_HLA_H_INCLUDED_
#define _TEST_HLA_H_INCLUDED_

#include "stdafx.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
//////////////////////////////////////////////////////////////////////
// CTestHLA class
//
//  Test class that is used to test added functionality
//   into G2_createAndJoinFederation()
//////////////////////////////////////////////////////////////////////

class CTestHLA : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CTestHLA);
	CPPUNIT_TEST(testHLA1);
	CPPUNIT_TEST(testHLA2);
	CPPUNIT_TEST(testHLA3);
	CPPUNIT_TEST(testHLA4);
	CPPUNIT_TEST(testHLA5);
	CPPUNIT_TEST_SUITE_END();

public:
	CTestHLA();
	virtual ~CTestHLA();

	// Set up test
	virtual void setUp();

	// Free test resources
	virtual void tearDown();

	void testHLA1();
	void testHLA2();
	void testHLA3();
	void testHLA4();
	void testHLA5();
private:
};

#endif // _TEST_HLA_H_INCLUDED_
