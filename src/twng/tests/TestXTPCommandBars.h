// TestXTPCommandBars.h: interface for the CTestXTPCommandBars class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CMainFrame;

class CTestXTPCommandBars : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE(CTestXTPCommandBars);
	CPPUNIT_TEST(testContexMenu);
	CPPUNIT_TEST_SUITE_END();

public:
	CTestXTPCommandBars();
	virtual ~CTestXTPCommandBars();
	virtual void setUp();
	virtual void tearDown();
	void testContexMenu();
private:
	CMainFrame* m_pMainFrame;
};
