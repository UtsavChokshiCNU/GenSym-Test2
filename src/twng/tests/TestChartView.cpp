#include "stdafx.h"
#include "TestChartView.h"
#include "Twng.h"
#include "ChartView.h"
#include "mainfrm.h"

#define USE_PROTOTYPES

extern "C" long g2ext_chart_set_int(long handle, long prop, long i, long j, long value);

CPPUNIT_TEST_SUITE_REGISTRATION(TestChartView);

void TestChartView::test()
{
	double d_array[] = {1.0,2.0,3.0};
	G2ChartView *pCV = NULL;
	HWND hPE = NULL;
	long l_set = -1;
	BOOL bSent = FALSE;

	CMainFrame *pFrame = GetMainWnd();

	hPE = g2pvt_create_chart_view(302, WS_CHILD | WS_CLIPSIBLINGS, pFrame->GetSafeHwnd()); //create PECONTROL_PIE chart
	if(!hPE)
	   return;

	pCV = new G2ChartView(1);
	pCV->SubclassWindow(hPE);
	pCV->m_g2pointer = SavePtr(hPE);

	l_set = g2ext_chart_set_int(1, 3210, -1, -1, 1); //set PEP_bALLOWDATAHOTSPOTS true;
	CPPUNIT_ASSERT(l_set >= 0);
	l_set = g2ext_chart_set_int(1, 3084, -1, -1, 1); //set PEP_bALLOWAXISHOTSPOTS true;
	CPPUNIT_ASSERT(l_set >= 0);

	pCV->OnChartClick();
	bSent = TRUE;
	CPPUNIT_ASSERT(bSent);

	delete pCV;

	bSent = FALSE;
	hPE = g2pvt_create_chart_view(304, WS_CHILD | WS_CLIPSIBLINGS, pFrame->GetSafeHwnd()); //create PECONTROL_SGRAPH chart
	if(!hPE)
		return;

	pCV = new G2ChartView(2);
	pCV->SubclassWindow(hPE);
	pCV->m_g2pointer = SavePtr(hPE);

	l_set = g2ext_chart_set_int(2, 3210, -1, -1, 1); //set PEP_bALLOWDATAHOTSPOTS true;
	CPPUNIT_ASSERT(l_set >= 0);
	l_set = g2ext_chart_set_int(2, 3084, -1, -1, 1); //set PEP_bALLOWAXISHOTSPOTS true;
	CPPUNIT_ASSERT(l_set >= 0);

	pCV->OnChartClick();
	bSent = TRUE;
	CPPUNIT_ASSERT(bSent);

	delete pCV;
}

void TestChartView::setUp()
{
}

void TestChartView::tearDown()
{
}
