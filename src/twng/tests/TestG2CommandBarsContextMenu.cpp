// TestXTPCommandBars.cpp: implementation of the CTestXTPCommandBars class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TestG2CommandBarsContextMenu.h"
#include "MainFrm.h"
#include "twng.h"
//extern "C" int  g_Gensym69;
CPPUNIT_TEST_SUITE_REGISTRATION(CTestG2CommandBarsContextMenu);


CTestG2CommandBarsContextMenu::CTestG2CommandBarsContextMenu()
{

}

CTestG2CommandBarsContextMenu::~CTestG2CommandBarsContextMenu()
{

}

void CTestG2CommandBarsContextMenu::setUp()
{
	m_pMainFrame = GetMainWnd();
}

void CTestG2CommandBarsContextMenu::tearDown()
{
}
 
void CTestG2CommandBarsContextMenu::testContexMenu()
{
	CPPUNIT_ASSERT(m_pMainFrame != NULL);
	CG2CommandBars *bars = (CG2CommandBars *)CXTPCommandBars::CreateCommandBars();
	//g_Gensym69 = 0;
	bars->ContextMenu(NULL, CPoint(40, 40));
	
//	g_Gensym69 = 1;
	bars->ContextMenu(NULL, CPoint(40, 40));
}
