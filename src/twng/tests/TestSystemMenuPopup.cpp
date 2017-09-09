#include "stdafx.h"
#include "TestSystemMenuPopup.h"
#include "twng.h"
#include "mainfrm.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestSystemMenuPopup);


void TestSystemMenuPopup::test()
{
	CPPUNIT_ASSERT(m_pMainFrame != NULL);
	CPPUNIT_ASSERT(IsWindow(m_pMainFrame->m_hWnd));

	UINT nResult = (UINT)m_pMainFrame->WindowProc(WM_NCRBUTTONDOWN, HTCAPTION, 3605003); 
	CPPUNIT_ASSERT(nResult == 0);

	nResult = (UINT)m_pMainFrame->WindowProc(WM_NCRBUTTONUP, HTCAPTION, 3605003); 
	CPPUNIT_ASSERT(nResult == 0);

	nResult = (UINT)m_pMainFrame->WindowProc(WM_NCRBUTTONDOWN, HTSYSMENU, 3605003); 
	CPPUNIT_ASSERT(nResult == 0);

	nResult = (UINT)m_pMainFrame->WindowProc(WM_NCRBUTTONUP, HTSYSMENU, 3605003); 
	CPPUNIT_ASSERT(nResult == 0);
}

void TestSystemMenuPopup::setUp()
{
	m_pMainFrame = GetMainWnd();
}

void TestSystemMenuPopup::tearDown()
{
}
