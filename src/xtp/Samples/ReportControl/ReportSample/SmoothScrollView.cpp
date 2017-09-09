// SmoothScrollView.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ReportSample.h"
#include "ReportSampleView.h"
#include "SmoothScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////
// CSmoothScrollFrame

BEGIN_MESSAGE_MAP(CSmoothScrollFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CSmoothScrollFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP    
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int CSmoothScrollFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		 !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}



	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_SMOOTHSCROLL);


	return 0;
}

void CSmoothScrollFrame::OnDestroy()
{
	((CReportSampleView*)m_pOwnerView)->m_pWndSmoothScroll = NULL;

	CFrameWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CSmoothScrollView

IMPLEMENT_DYNCREATE(CSmoothScrollView, CXTPReportView)

CSmoothScrollView::CSmoothScrollView()
{
}

CSmoothScrollView::~CSmoothScrollView()
{
}


BEGIN_MESSAGE_MAP(CSmoothScrollView, CXTPReportView)
	//{{AFX_MSG_MAP(CSmoothScrollView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmoothScrollView diagnostics

#ifdef _DEBUG
void CSmoothScrollView::AssertValid() const
{
	CView::AssertValid();
}

void CSmoothScrollView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSmoothScrollView message handlers

int CSmoothScrollView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CXTPReportControl& wndReport = GetReportCtrl();

	wndReport.GetReportHeader()->AllowColumnReorder(FALSE);
	wndReport.GetReportHeader()->AllowColumnSort(FALSE);
	wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);

	CXTPReportColumn *pColumn;
	pColumn = wndReport.AddColumn(new CXTPReportColumn(0, _T("Date Logged"), 100, TRUE));
	pColumn->SetAlignment(DT_CENTER & DT_WORDBREAK);
	pColumn->SetHeaderAlignment(DT_CENTER);

	pColumn = wndReport.AddColumn(new CXTPReportColumn(1, _T("Comment"), 600, TRUE));
	pColumn->SetAlignment(DT_CENTER & DT_WORDBREAK);
	pColumn->SetHeaderAlignment(DT_CENTER);

	pColumn = wndReport.AddColumn(new CXTPReportColumn(2, _T("User"), 150, TRUE));
	pColumn->SetAlignment(DT_CENTER & DT_WORDBREAK);
	pColumn->SetHeaderAlignment(DT_CENTER);

	wndReport.SetFreezeColumnsCount(1);
	wndReport.SetMultipleSelection(FALSE);
	wndReport.GetPaintManager()->SetFixedRowHeight(FALSE);

	CString strMultiLineComment =
		_T("Subject: RE: AND another question!\n\n")
		_T("Hi Steven,\n\n")
		_T("Unfortunately WHEN it comes to signatures Blackberry (nor any other device) synch signatures WITH your Outlook.\n\n")
		_T("To change OR DELETE your auto signature FROM your handheld please do the following:\n\n")
		_T("(1) FROM the Messages screen, click Menu, AND THEN scroll down AND choose Options.\n\n")
		_T("(2) SELECT Email Settings, AND click.\n\n")
		_T("(3) Move the cursor to the Use Auto Signature field, AND SELECT Yes. IN the text box that appears, enter a new auto signature.\n\n")
		_T("Note: The handheld IS NOT configured to use auto signature BY default. Because there IS some latency BETWEEN WHEN you make changes AND WHEN they take effect ON the server, you may want to send yourself test messages to verify your signature changes are working properly.\n\n")
		_T("(4) After you've made your changes, click Menu and choose Save.")
		;

	CXTPReportRecord *pRecord;
	
	for (int i=1; i<=2; i++)
	{
		pRecord = wndReport.AddRecord(new CXTPReportRecord());
		pRecord->AddItem(new CXTPReportRecordItemText(_T("")));
		pRecord->AddItem(new CXTPReportRecordItemText(strMultiLineComment));

		CString sUser;
		sUser.Format(_T("User %d"), i);
		pRecord->AddItem(new CXTPReportRecordItemText(sUser));
	}

	wndReport.Populate();
	wndReport.SetFocus();

	wndReport.SetScrollMode(xtpReportOrientationAll, xtpReportScrollModeSmooth);

	return 0;
}
