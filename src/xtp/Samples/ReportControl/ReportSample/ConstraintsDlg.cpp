// ConstraintsDlg.cpp : implementation of the CConstraintsDlg class
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
#include "ConstraintsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CConstraintsDlg::CConstraintsDlg(CWnd *pParent)
	: CDialog(CConstraintsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstraintsDlg)
	//}}AFX_DATA_INIT
}


void CConstraintsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstraintsDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstraintsDlg, CDialog)
	//{{AFX_MSG_MAP(CConstraintsDlg)
	ON_BN_CLICKED(IDC_CAPTION, OnCaption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CConstraintsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndReport.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnReorder(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);

	m_wndReport.AllowEdit(FALSE);
	m_wndReport.EditOnClick(TRUE);
	m_wndReport.SetFullColumnScrolling(FALSE);

	CXTPReportColumn *pColumn; 
	
	pColumn = m_wndReport.AddColumn(new CXTPReportColumn(0, _T("Column 1"), 450, TRUE));
	pColumn->GetEditOptions()->AddConstraint(_T("State Off"), 0);
	pColumn->GetEditOptions()->AddConstraint(_T("State On" ), 1);
	pColumn->GetEditOptions()->m_bConstraintEdit = TRUE;

	pColumn = m_wndReport.AddColumn(new CXTPReportColumn(1, _T("Column 2"), 150, TRUE));
	pColumn->GetEditOptions()->AddConstraint(_T("No" ), 5);
	pColumn->GetEditOptions()->AddConstraint(_T("Yes"), 8);
	pColumn->GetEditOptions()->m_bConstraintEdit = TRUE;

	for (int nRecord=0; nRecord<20; nRecord++)
	{
		CXTPReportRecord *pRecord = new CXTPReportRecord();
		m_wndReport.AddRecord(pRecord);

		CXTPReportRecordItemVariant *pItem;

		COleVariant variant;

		variant = long(1);
		pItem = new CXTPReportRecordItemVariant(variant);
		pRecord->AddItem(pItem);

		variant = long(8);
		pItem = new CXTPReportRecordItemVariant(variant);
		pRecord->AddItem(pItem);
	}

	m_wndReport.Populate();

	return FALSE;
}

void CConstraintsDlg::OnOK()
{
	CDialog::OnOK();
}

void CConstraintsDlg::OnCaption() 
{
	CXTPReportRecord *pRecord;
	CXTPReportRecordItem *pItem;
	CString sCaption;

	for (int nRecord=0; nRecord<m_wndReport.GetRecords()->GetCount(); nRecord++)
	{
		pRecord = m_wndReport.GetRecords()->GetAt(nRecord);

		for (int nItem=0; nItem<pRecord->GetItemCount(); nItem++)
		{
			pItem = DYNAMIC_DOWNCAST(CXTPReportRecordItem, pRecord->GetItem(nItem));
			sCaption = pItem->GetCaption();
			TRACE(_T("%s "), sCaption);
		}
		TRACE(_T("\n"));
	}
}
