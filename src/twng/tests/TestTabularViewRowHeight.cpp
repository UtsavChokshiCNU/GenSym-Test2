#include "stdafx.h"
#include "TestTabularViewRowHeight.h"

#include "Twng.h"
#include "NativeView.h"
#include "TabularView.h"
#include "MainFrm.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestTabularViewRowHeight);

void TestTabularViewRowHeight::test()
{
	CMainFrame *pFrame = GetMainWnd();
	G2TabularView *pTV = new G2TabularView(0);
  
	pTV->Create(WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SHAREIMAGELISTS,
	      WinSize(200,300), pFrame, 0);

	pTV->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	pTV->m_g2pointer = SavePtr(pTV->m_hWnd);
	
	pTV->InsertColumn(0,_T("test1"),0,1,0);
	pTV->InsertColumn(1,_T("test2"),0,1,0);
	
	pTV->InsertRow(-1, 0, L"", 0, 255, false);
	pTV->SetCellText(0, 0, L"aaa");
	pTV->SetCellText(0, 1, L"bbb");

	CRect r;
	pTV->SetRowHeight(40);
	pTV->GetCellRect(0, 0, LVIR_LABEL, r);
	CPPUNIT_ASSERT(r.Height() == 40+1);

	pTV->InvalidateRect(NULL); //set redraw to invoke MultilineCustomDraw

	pTV->GetCellRect(0, 0, LVIR_LABEL, r);
	CPPUNIT_ASSERT(r.Height() == 40+1);
}

void TestTabularViewRowHeight::setUp()
{
}

void TestTabularViewRowHeight::tearDown()
{
}
