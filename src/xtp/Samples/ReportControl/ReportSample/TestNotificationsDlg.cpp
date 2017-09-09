// TestNotificationsDlg.cpp : implementation of the CTestNotificationsDlg class
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
#include "Resource.h"
#include "TestNotificationsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestNotificationsDlg dialog


CTestNotificationsDlg::CTestNotificationsDlg(CWnd *pParent)
	: CDialog(CTestNotificationsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestNotificationsDlg)
	m_bCancelFocusChanging = FALSE;
	m_bCancelLButtonDown = FALSE;
	m_bCancelLButtonUp = FALSE;
	m_bCancelSelectionClear = FALSE;
	m_bCancelSelectionAdd = FALSE;
	//}}AFX_DATA_INIT
}


void CTestNotificationsDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestNotificationsDlg)
	DDX_Check(pDX, IDC_CANCEL_FOCUS_CHANGING, m_bCancelFocusChanging);
	DDX_Check(pDX, IDC_CANCEL_LBUTTON_DOWN, m_bCancelLButtonDown);
	DDX_Check(pDX, IDC_CANCEL_LBUTTON_UP, m_bCancelLButtonUp);
	DDX_Control(pDX, IDC_REPORT,			m_wndReport);
	DDX_Control(pDX, IDC_NOTIFICATIONS, m_wndNotifications);
	DDX_Check(pDX, IDC_CANCEL_SELECTION_CLEAR, m_bCancelSelectionClear);
	DDX_Check(pDX, IDC_CANCEL_SELECTION_ADD, m_bCancelSelectionAdd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestNotificationsDlg, CDialog)
	//{{AFX_MSG_MAP(CTestNotificationsDlg)
	ON_NOTIFY(NM_CLICK,								IDC_REPORT, OnReportClick)
	ON_NOTIFY(NM_RCLICK,								IDC_REPORT, OnReportRClick)
	ON_NOTIFY(NM_DBLCLK,								IDC_REPORT, OnReportDblClick)
	ON_NOTIFY(XTP_NM_REPORT_LBUTTONDOWN,		IDC_REPORT, OnReportLButtonDown)
	ON_NOTIFY(XTP_NM_REPORT_LBUTTONUP,			IDC_REPORT, OnReportLButtonUp)
	ON_NOTIFY(XTP_NM_REPORT_SELCHANGING,		IDC_REPORT, OnReportSelChanging)
	ON_NOTIFY(XTP_NM_REPORT_SELCHANGED,			IDC_REPORT, OnReportSelChanged)
	ON_NOTIFY(XTP_NM_REPORT_FOCUS_CHANGING,	IDC_REPORT, OnReportFocusChanging)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestNotificationsDlg message handlers


BOOL CTestNotificationsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum Constants
	{
		ColumnCount =  3,
		RecordCount = 10
	};

	// Initialize list control first
	m_wndNotifications.InsertColumn(0, _T("Notification"), LVCFMT_LEFT, 225);
	m_wndNotifications.InsertColumn(1, _T("Row index"),    LVCFMT_LEFT,  75);
	m_wndNotifications.InsertColumn(2, _T("Parameter"),    LVCFMT_LEFT, 150);

	CString sName;

	// Add columns
	for (int nColumn=0; nColumn<ColumnCount; nColumn++)
	{
		sName.Format(_T("Column %d"), nColumn);
		m_wndReport.AddColumn(new CXTPReportColumn(nColumn, sName, 100));
	}

	// Add sample records
	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord = m_wndReport.AddRecord(new CXTPReportRecord());

		for (nColumn=0; nColumn<ColumnCount; nColumn++)
		{
			sName.Format(_T("Item %d, %d"), nRecord, nColumn);
			pRecord->AddItem(new CXTPReportRecordItemText(sName));
		}
	}

	m_wndReport.Populate();

	return FALSE;
}

void CTestNotificationsDlg::OnOK()
{
	CDialog::OnOK();
}

int CTestNotificationsDlg::AddNotification(LPCTSTR pszNotification, int nRow, LPCTSTR pszParameter)
{
	int nItem = m_wndNotifications.InsertItem(m_wndNotifications.GetItemCount(), pszNotification);

	CString sRow;
	sRow.Format(_T("%d"), nRow);

	VERIFY(m_wndNotifications.SetItemText(nItem, 1, sRow));
	VERIFY(m_wndNotifications.SetItemText(nItem, 2, pszParameter));

	m_wndNotifications.EnsureVisible(nItem, FALSE);

	return nItem;
}

/////////////////////////////////////////////////////////////////////////////
// Notifications
/////////////////////////////////////////////////////////////////////////////

void CTestNotificationsDlg::OnReportClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}

	int nItem = AddNotification(_T("NM_CLICK"), nRow);
}

void CTestNotificationsDlg::OnReportRClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}
	
	int nItem = AddNotification(_T("NM_RCLICK"), nRow);
}

void CTestNotificationsDlg::OnReportDblClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}
	
	int nItem = AddNotification(_T("NM_DBLCLICK"), nRow);
}

void CTestNotificationsDlg::OnReportLButtonDown(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}

	int nItem = AddNotification(_T("XTP_NM_REPORT_LBUTTONDOWN"), nRow);

	UpdateData();
	*pResult = m_bCancelLButtonDown;
}

void CTestNotificationsDlg::OnReportLButtonUp(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTRECORDITEM *pItemNotify = reinterpret_cast<XTP_NM_REPORTRECORDITEM*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}

	int nItem = AddNotification(_T("XTP_NM_REPORT_LBUTTONUP"), nRow);

	UpdateData();
	*pResult = m_bCancelLButtonUp;
}

static const LPCTSTR XTPReportSelectionChangeTypeString[] =
{
	_T("xtpReportSelectionAdd"),
	_T("xtpReportSelectionRemove"),
	_T("xtpReportSelectionClear")
};

void CTestNotificationsDlg::OnReportSelChanging(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_SELECTION_CHANGING *pItemNotify = reinterpret_cast<XTP_NM_SELECTION_CHANGING*>(pNotifyStruct);

	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}

	int nItem = AddNotification(_T("XTP_NM_REPORT_SELCHANGING"), nRow, XTPReportSelectionChangeTypeString[pItemNotify->nType]);

	UpdateData();
	switch(pItemNotify->nType)
	{
	case xtpReportSelectionAdd:
		*pResult = m_bCancelSelectionAdd;
		break;
	case xtpReportSelectionRemove:
		break;
	case xtpReportSelectionClear:
		*pResult = m_bCancelSelectionClear;
		break;
	}
}

void CTestNotificationsDlg::OnReportSelChanged(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	int nItem = AddNotification(_T("XTP_NM_REPORT_SELCHANGED"), -1);
}

void CTestNotificationsDlg::OnReportFocusChanging(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	ASSERT(NULL != pNotifyStruct);
	ASSERT(NULL != pResult);

	XTP_NM_REPORTREQUESTEDIT *pItemNotify = reinterpret_cast<XTP_NM_REPORTREQUESTEDIT*>(pNotifyStruct);
	
	int nRow = -1;
	
	if (pItemNotify->pRow)
	{
		nRow = pItemNotify->pRow->GetIndex();
	}
	
	int nItem = AddNotification(_T("XTP_NM_REPORT_FOCUS_CHANGING"), nRow);

	UpdateData();
	pItemNotify->bCancel = m_bCancelFocusChanging;
}
