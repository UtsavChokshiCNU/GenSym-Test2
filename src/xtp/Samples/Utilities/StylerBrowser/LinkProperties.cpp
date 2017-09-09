// LinkProperties.cpp : implementation file
//

#include "stdafx.h"
#include "styler.h"
#include "LinkProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkProperties dialog


CLinkProperties::CLinkProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CLinkProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinkProperties)
	m_strAddress = _T("");
	m_strTitle = _T("");
	m_strParent = _T("");
	//}}AFX_DATA_INIT
}


void CLinkProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinkProperties)
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_STATIC_PARENT, m_strParent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinkProperties, CDialog)
	//{{AFX_MSG_MAP(CLinkProperties)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinkProperties message handlers
