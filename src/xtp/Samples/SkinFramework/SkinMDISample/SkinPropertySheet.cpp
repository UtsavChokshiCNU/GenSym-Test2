// SkinPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SkinPropertySheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinPropertySheet

IMPLEMENT_DYNAMIC(CSkinPropertySheet, CPropertySheet)

CSkinPropertySheet::CSkinPropertySheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page1);
	AddPage(&m_Page2);
}

CSkinPropertySheet::~CSkinPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CSkinPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSkinPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkinPropertySheet message handlers

BOOL CSkinPropertySheet::OnInitDialog() 
{
	CPropertySheet::OnInitDialog();
	
	ModifyStyleEx(0, WS_EX_TOOLWINDOW);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


