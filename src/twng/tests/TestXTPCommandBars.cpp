// TestXTPCommandBars.cpp: implementation of the CTestXTPCommandBars class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TestXTPCommandBars.h"
#include "MainFrm.h"
#include "twng.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CTestXTPCommandBars);


CTestXTPCommandBars::CTestXTPCommandBars()
{

}

CTestXTPCommandBars::~CTestXTPCommandBars()
{

}

void CTestXTPCommandBars::setUp()
{
	m_pMainFrame = GetMainWnd();
}

void CTestXTPCommandBars::tearDown()
{
}

void CTestXTPCommandBars::testContexMenu()
{
	CPPUNIT_ASSERT(m_pMainFrame != NULL);
	CXTPCommandBars *bars = CXTPCommandBars::CreateCommandBars();
	bars->ContextMenu(NULL, CPoint(40, 40));
}
