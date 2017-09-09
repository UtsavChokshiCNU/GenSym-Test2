// TestXTPCommandBars.h: interface for the CTestXTPCommandBars class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CMainFrame;

class CTestG2CommandBarsContextMenu : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE(CTestG2CommandBarsContextMenu);
	CPPUNIT_TEST(testContexMenu);
	CPPUNIT_TEST_SUITE_END();

public:
	CTestG2CommandBarsContextMenu();
	virtual ~CTestG2CommandBarsContextMenu();
	virtual void setUp();
	virtual void tearDown();
	void testContexMenu();
private:
	CMainFrame* m_pMainFrame;
};
