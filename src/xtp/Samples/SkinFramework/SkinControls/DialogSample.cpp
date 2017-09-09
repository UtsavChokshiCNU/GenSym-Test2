// DialogSample.cpp : implementation file
//

#include "stdafx.h"
#include "skincontrols.h"
#include "DialogSample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSample dialog


CDialogSample::CDialogSample(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSample::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSample)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		
	
	m_strStylesPath = szStylesPath;
	int nIndex  = m_strStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		m_strStylesPath = m_strStylesPath.Left(nIndex);
	}
	else {
		m_strStylesPath.Empty();
	}
	m_strStylesPath += _T("\\Styles\\");

}


void CDialogSample::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSample)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSample, CDialog)
	//{{AFX_MSG_MAP(CDialogSample)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSample message handlers

BOOL CDialogSample::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CXTPSkinManager* pSkinManager = XTPSkinManager();

	CXTPSkinManagerSchema* pSchema = pSkinManager->CreateSchema(m_strStylesPath + _T("WinXP.Luna.cjstyles"), _T("NormalHomestead.ini"));
	pSkinManager->SetWindowTheme(GetSafeHwnd(), pSchema);
	CMDTARGET_RELEASE(pSchema);


	pSchema = pSkinManager->CreateSchema(m_strStylesPath + _T("WinXP.Royale.cjstyles"), _T("NormalRoyale.ini"));
	pSkinManager->SetWindowTheme(GetDlgItem(IDC_BUTTON_BLUE)->GetSafeHwnd(), pSchema);
	CMDTARGET_RELEASE(pSchema);

	pSchema = pSkinManager->CreateSchema(m_strStylesPath + _T("Vista.cjstyles"), _T("NormalBlue.ini"));
	pSkinManager->SetWindowTheme(GetDlgItem(IDC_BUTTON_METALLIC)->GetSafeHwnd(), pSchema);
	CMDTARGET_RELEASE(pSchema);

	pSchema = pSkinManager->CreateSchema(m_strStylesPath + _T("Office2007.cjstyles"), _T("NormalBlue.ini"));
	pSkinManager->SetWindowTheme(GetDlgItem(IDC_BUTTON_OLIVE)->GetSafeHwnd(), pSchema);
	CMDTARGET_RELEASE(pSchema);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
