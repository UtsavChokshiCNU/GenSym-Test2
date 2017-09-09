// TabResizablePage.cpp : implementation file
//

#include "stdafx.h"
#include "propertysheet.h"
#include "TabResizablePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabResizablePage dialog


CTabResizablePage::CTabResizablePage()
	: CXTPPropertyPage(CTabResizablePage::IDD)
{
	//{{AFX_DATA_INIT(CTabResizablePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTabResizablePage::DoDataExchange(CDataExchange* pDX)
{
	CXTPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabResizablePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabResizablePage, CXTPPropertyPage)
	//{{AFX_MSG_MAP(CTabResizablePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabResizablePage message handlers

BOOL CTabResizablePage::OnInitDialog() 
{
	CXTPPropertyPage::OnInitDialog();

	ModifyStyle(0, WS_CLIPCHILDREN | WS_VSCROLL);

	m_group1.SubclassDlgItem(IDC_STATIC_GROUP1, this);
	m_group2.SubclassDlgItem(IDC_STATIC_GROUP2, this);

	SetResize(IDC_STATIC_GROUP1,  XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPCENTER);
	SetResize(IDC_STATIC_GROUP2,  XTP_ANCHOR_TOPCENTER, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_RADIO1,  XTP_ANCHOR_TOPCENTER, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_EDIT1,  XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_BUTTON,  XTP_ANCHOR_BOTTOMCENTER, XTP_ANCHOR_BOTTOMCENTER);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
