// SelectionView.cpp : implementation file
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
#include "SelectionView.h"
#include "ReportSampleView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////
// CSelectionFrame


BEGIN_MESSAGE_MAP(CSelectionFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CSelectionFrame)
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


int CSelectionFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
       !m_wndStatusBar.SetIndicators(indicators, _countof(indicators)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}



	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_TASKLIST);


	return 0;
}

void CSelectionFrame::OnDestroy()
{
	((CReportSampleView*)m_pOwnerView)->m_pWndSelection = NULL;

	CFrameWnd::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CSelectionView

IMPLEMENT_DYNCREATE(CSelectionView, CXTPReportView)

CSelectionView::CSelectionView()
{
}

CSelectionView::~CSelectionView()
{
}


BEGIN_MESSAGE_MAP(CSelectionView, CXTPReportView)
	//{{AFX_MSG_MAP(CSelectionView)
	// Window
	ON_WM_CREATE()
	// Report control
	ON_NOTIFY(XTP_NM_REPORT_VALUECHANGED,      XTP_ID_REPORT_CONTROL, OnReportValueChanged)
	ON_NOTIFY(XTP_NM_REPORT_SELCHANGED,        XTP_ID_REPORT_CONTROL, OnReportSelChanged )
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectionView drawing

/////////////////////////////////////////////////////////////////////////////
// CSelectionView diagnostics

#ifdef _DEBUG
void CSelectionView::AssertValid() const
{
	CView::AssertValid();
}

void CSelectionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSelectionView message handlers

int CSelectionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CXTPReportControl& wndReport = GetReportCtrl();


	wndReport.ShowHeaderRows(TRUE);
	wndReport.HeaderRowsAllowEdit(TRUE);

	wndReport.AddColumn(new CXTPReportColumn(0, _T("ID")    ,  50, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(1, _T("String"), 100, TRUE ));

	CXTPReportRecord *pRecord;

	pRecord = new CXTPReportRecord();
	pRecord->AddItem(new CXTPReportRecordItemText(_T("")));
	pRecord->AddItem(new CXTPReportRecordItemText(_T("")))->SetBackgroundColor(RGB(255,255,0));
	wndReport.GetHeaderRecords()->Add(pRecord);

	for (int i=0; i<2000; i++)
	{
		CString sId;
		CString sString;

		sId.Format(_T("%d"), i);

		     if (i <  100) sString = _T("AAA");
		else if (i <  300) sString = _T("BBB");
		else if (i <  600) sString = _T("CCC");
		else if (i <  900) sString = _T("DDD");
		else if (i < 1200) sString = _T("EEE");
		else if (i < 1500) sString = _T("FFF");
		else if (i < 1800) sString = _T("GGG");
		else               sString = _T("HHH");

		pRecord = new CXTPReportRecord();
		pRecord->AddItem(new CXTPReportRecordItemText(sId    ));
		pRecord->AddItem(new CXTPReportRecordItemText(sString));
		wndReport.AddRecord(pRecord);

	}

	wndReport.Populate();


	return 0;
}


void CSelectionView::OnReportValueChanged(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM *pItemNotify = (XTP_NM_REPORTRECORDITEM*)pNotifyStruct;

	CXTPReportControl& wndReport = GetReportCtrl();
	
	CXTPReportRecords *pRecords;
	CXTPReportRecord  *pRecord;
	CXTPReportRecordItemText *pFilter;
	CXTPReportRecordItemText *pItem;

	// Get header record item
	pRecords = wndReport.GetHeaderRecords();
	pRecord  = pRecords->GetAt(0);
	pFilter  = reinterpret_cast<CXTPReportRecordItemText*>(pRecord->GetItem(1));

	CString sFilter = pFilter->GetValue();

	for (int i=0; i<wndReport.GetRecords()->GetCount(); i++)
	{
		pRecords = wndReport.GetRecords();
		pRecord  = pRecords->GetAt(i);
		
		pItem = reinterpret_cast<CXTPReportRecordItemText*>(pRecord->GetItem(1));

		if (sFilter == _T("") ||
			 sFilter == pItem->GetValue().Left(sFilter.GetLength()))
		{
			pRecord->SetVisible(TRUE);
		}
		else
		{
			pRecord->SetVisible(FALSE);
		}
	}

	wndReport.Populate();
}


void CSelectionView::OnReportSelChanged(NMHDR * pNotifyStruct, LRESULT* pResult)
{
	CXTPReportControl &wndReport = GetReportCtrl();

	int nCount = wndReport.GetSelectedRows()->GetCount();
}
