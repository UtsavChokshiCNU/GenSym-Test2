// FormulaDlg.cpp : implementation of the CFormulaDlg class
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

#include "stdafx.h"
#include "FormulaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CFormulaDlg dialog


CFormulaDlg::CFormulaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFormulaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormulaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFormulaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormulaDlg)
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormulaDlg, CDialog)
	//{{AFX_MSG_MAP(CFormulaDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaDlg message handlers

BOOL CFormulaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CXTPReportColumn *pColumnProduct = m_wndReport.AddColumn(new CXTPReportColumn(0, _T("Product"), 150));
	CXTPReportColumn *pColumnState   = m_wndReport.AddColumn(new CXTPReportColumn(1, _T("State"),   150));
	CXTPReportColumn *pColumnSales   = m_wndReport.AddColumn(new CXTPReportColumn(2, _T("Sales"),   150));

	pColumnState->SetAlignment(DT_RIGHT);
	//pColumnState->SetAlignment(DT_LEFT);

	struct Item 
	{
		LPCTSTR pszProduct;
		LPCTSTR pszState;
		int nSales;
	};

	Item items[] = {
		{_T("Pen"),		_T("NSW"), 20},
		{_T("Paper"),	_T("NSW"), 10},
		{_T("Books"),	_T("NSW"), 10},

		{_T("Pen"),		_T("SA"), 20},
		{_T("Paper"),	_T("SA"), 10},
		{_T("Books"),	_T("SA"), 10},
		
		{_T("Pen"),		_T("WA"), 20},
		{_T("Paper"),	_T("WA"), 10},
		{_T("Books"),	_T("WA"), 10},
	};

	CXTPReportRecord *pRecord;
	int i;

	for (i=0; i<_countof(items); i++)
	{
		pRecord = m_wndReport.AddRecord(new CXTPReportRecord());
		pRecord->AddItem(new CXTPReportRecordItemText(items[i].pszProduct));
		pRecord->AddItem(new CXTPReportRecordItemText(items[i].pszState));
		pRecord->AddItem(new CXTPReportRecordItemNumber(items[i].nSales));
	}

	m_wndReport.GetColumns()->GetGroupsOrder()->Add(pColumnProduct);
	m_wndReport.Populate();

	for (i=0; i<m_wndReport.GetRows()->GetCount(); i++)
	{
		CXTPReportRow *pRow = m_wndReport.GetRows()->GetAt(i);

		if (pRow->IsGroupRow())
		{
			CXTPReportGroupRow *pGroupRow = reinterpret_cast<CXTPReportGroupRow*>(pRow);
			pGroupRow->SetFormatString(_T(" Subtotal $=%.02f"));
			pGroupRow->SetFormula(_T("SUMSUB(R*C1:R*C8)"));
			pGroupRow->SetCaption(_T("x"));
		}
	}

	return FALSE;
}

void CFormulaDlg::OnOK()
{
	CDialog::OnOK();
}
