#include "stdafx.h"
#include "TestTabularViewSort.h"

#include "Twng.h"
#include "NativeView.h"
#include "TabularView.h"
#include "MainFrm.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestTabularViewSort);

void TestTabularViewSort::test()
{
	CMainFrame *pFrame = GetMainWnd();
	G2TabularView *pTV = new G2TabularView(0);
  
	pTV->Create(WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SHAREIMAGELISTS,
	      WinSize(200,300), pFrame, 0);

	pTV->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
	pTV->m_g2pointer = SavePtr(pTV->m_hWnd);
	
	pTV->SaveSortColumn(3);
	pTV->SaveSortAscending(TRUE);
	pTV->InsertColumn(0,_T("test1"),0,1,0);
	pTV->InsertColumn(1,_T("test2"),0,1,0);
	pTV->InsertColumn(2,_T("test3"),0,1,0);
	pTV->InsertColumn(3,_T("test4"),0,1,0);
	pTV->SortRows();
	
	int sortColumn = pTV->GetSortColumn();
	CPPUNIT_ASSERT(sortColumn == 3);
	
	BOOL sortAscending = pTV->GetSortAscending();
	CPPUNIT_ASSERT(sortAscending == TRUE);
	
}

void TestTabularViewSort::setUp()
{
}

void TestTabularViewSort::tearDown()
{
}
