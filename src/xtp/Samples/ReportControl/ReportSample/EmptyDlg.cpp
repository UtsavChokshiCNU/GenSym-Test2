// EmptyDlg.cpp : Implementation of the CTreeViewDlg class
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
#include "EmptyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTreeViewDlg dialog


CEmptyDlg::CEmptyDlg(CWnd *pParent)
	: CDialog(CEmptyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmptyDlg)
	//}}AFX_DATA_INIT
}


void CEmptyDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmptyDlg)
	DDX_Control(pDX, IDC_REPORT1, m_wndReport1);
	DDX_Control(pDX, IDC_REPORT2, m_wndReport2);
	DDX_Control(pDX, IDC_REPORT3, m_wndReport3);
	DDX_Control(pDX, IDC_REPORT4, m_wndReport4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmptyDlg, CDialog)
	//{{AFX_MSG_MAP(CEmptyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmptyDlg message handlers


BOOL CEmptyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////
	// Report 1: Nothing
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Report 2: Populate with no columns and no rows
	//////////////////////////////////////////////////////////////////////////
	m_wndReport2.Populate();
	
	//////////////////////////////////////////////////////////////////////////
	// Report 3: Populate with one column and no rows
	//////////////////////////////////////////////////////////////////////////
	m_wndReport3.AddColumn(new CXTPReportColumn(0, _T("Column 0"), 100));
	m_wndReport3.Populate();

	//////////////////////////////////////////////////////////////////////////
	// Report 4: Populate with one column and no rows, draw grid
	//////////////////////////////////////////////////////////////////////////
	m_wndReport4.AddColumn(new CXTPReportColumn(0, _T("Column 0"), 100));
	m_wndReport4.Populate();
	m_wndReport4.GetPaintManager()->SetDrawGridForEmptySpace(TRUE);

	return FALSE;
}

void CEmptyDlg::OnOK()
{
	CDialog::OnOK();
}
