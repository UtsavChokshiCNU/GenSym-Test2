// TestGsiLoop.h: interface for the CTestGsiLoop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTGSILOOP_H__5AB6F8B2_A46C_47C7_9296_F1525CDF7484__INCLUDED_)
#define AFX_TESTGSILOOP_H__5AB6F8B2_A46C_47C7_9296_F1525CDF7484__INCLUDED_

#include "stdafx.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////
// CTestGsiLoop class
//
//  Test class that is used to test added functionality into GsiLoop():
//
//   * SetProcessShutdownParameters() calling.
//		Results of SetProcessShutdownParameters() calling are tested
//		using GetProcessShutdownParameters() results that must be the
//		same as parameters passed into SetProcessShutdownParameters()
//		from GsiLoop()
//
//  To use this test g2opc license should be valid, otherwise tests fail.
//////////////////////////////////////////////////////////////////////
class CTestGsiLoop : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CTestGsiLoop);
	CPPUNIT_TEST(testGsiLoop);
	CPPUNIT_TEST_SUITE_END();

public:
	CTestGsiLoop();
	virtual ~CTestGsiLoop();

	// Set up test
	virtual void setUp();

	// Free test resources
	virtual void tearDown();

	// Test GsiLoop() functionality
	void testGsiLoop();
};

#endif // !defined(AFX_TESTGSILOOP_H__5AB6F8B2_A46C_47C7_9296_F1525CDF7484__INCLUDED_)
