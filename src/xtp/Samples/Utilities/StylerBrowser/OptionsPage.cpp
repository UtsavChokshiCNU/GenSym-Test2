// OptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsPage property page

IMPLEMENT_DYNCREATE(COptionsPage, CPropertyPage)

COptionsPage::COptionsPage(UINT nIDTemplate) : CPropertyPage(nIDTemplate)
{
	//{{AFX_DATA_INIT(COptionsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strTitle.LoadString(nIDTemplate);
}

COptionsPage::~COptionsPage()
{
}

void COptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPage message handlers

BOOL COptionsPage::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB && GetKeyState(VK_CONTROL) < 0)
		return GetParent()->PreTranslateMessage(pMsg);

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return GetParent()->PreTranslateMessage(pMsg);

	if(IsDialogMessage(pMsg))
		return TRUE;
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}



void ConvertMenuItem(CString &strTitle)
{

	strTitle.Replace(_T("&"), _T(""));
	strTitle.Replace(_T("."), _T(""));
	strTitle.Replace(_T(" "), _T(""));
	
	int nIndex = strTitle.Find('\t');
	if (nIndex >= 0)
		strTitle.Delete(nIndex, strTitle.GetLength() - nIndex);
}  
