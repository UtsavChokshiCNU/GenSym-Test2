#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CMainFrame;

class CTestModalLoop : public CPPUNIT_NS::TestFixture  
{
	CPPUNIT_TEST_SUITE(CTestModalLoop);
		CPPUNIT_TEST(testCommandBars);
		CPPUNIT_TEST(testDockingPanes);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testCommandBars();
	void testDockingPanes();

private:
	CMainFrame* m_pMainFrame;
};
