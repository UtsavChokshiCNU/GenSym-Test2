// PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TreeCtrl.h"
#include "PropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg dialog

CPropertiesDlg::CPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertiesDlg::IDD, pParent)
	, m_pTreeCtrl(NULL)
{
	//{{AFX_DATA_INIT(CPropertiesDlg)
	m_nIndex = 0;
	m_bBoldCheck = FALSE;
	m_strFontSize = _T("");
	//}}AFX_DATA_INIT

	m_crText = ::GetSysColor(COLOR_WINDOWTEXT);
	m_crBack = ::GetSysColor(COLOR_WINDOW);
	m_strFontSize = _T("8");
}

void CPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertiesDlg)
	DDX_Control(pDX, IDC_BTN_APPLY, m_btnApply);
	DDX_Control(pDX, IDC_SIZE_COMBO, m_comboSize);
	DDX_Control(pDX, IDC_COLOR_TEXT, m_cpText);
	DDX_Control(pDX, IDC_COLOR_BACK, m_cpBack);
	DDX_Control(pDX, IDC_FONT_COMBO, m_comboFont);
	DDX_CBIndex(pDX, IDC_FONT_COMBO, m_nIndex);
	DDX_Check(pDX, IDC_BOLD_CHECK, m_bBoldCheck);
	DDX_CBString(pDX, IDC_SIZE_COMBO, m_strFontSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertiesDlg)
	ON_BN_CLICKED(IDC_BOLD_CHECK, OnBoldCheck)
	ON_CBN_SELENDOK(IDC_SIZE_COMBO, OnSelendokSizeCombo)
	ON_CBN_SELENDOK(IDC_FONT_COMBO, OnSelendokFontCombo)
	ON_CPN_XTP_SELENDOK(IDC_COLOR_TEXT, OnSelEndOkColorText)
	ON_CPN_XTP_SELENDOK(IDC_COLOR_BACK, OnSelEndOkColorBack)
	ON_CBN_EDITCHANGE(IDC_SIZE_COMBO, OnEditchangeSizeCombo)
	ON_BN_CLICKED(IDC_BTN_APPLY, OnBtnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg message handlers

void CPropertiesDlg::OnSelendokFontCombo()
{
	m_comboFont.GetSelFont(m_LogFont);
}

void CPropertiesDlg::OnSelendokSizeCombo()
{
	UpdateData();
}

void CPropertiesDlg::OnBoldCheck()
{
	UpdateData();
}

void CPropertiesDlg::OnSelEndOkColorText()
{
	// a color selection was made, update the
	// appropriate member data.
	m_crText = m_cpText.GetColor();
}

void CPropertiesDlg::OnSelEndOkColorBack()
{
	// a color selection was made, update the
	// appropriate member data.
	m_crBack = m_cpBack.GetColor();
}

void CPropertiesDlg::OnEditchangeSizeCombo()
{
	UpdateData();
}

BOOL CPropertiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ASSERT_VALID(m_pTreeCtrl);

	m_cpText.SetColor(m_crText);
	m_cpBack.SetColor(m_crBack);
	m_comboSize.SetCurSel(0);

	// select the tree control's font
	LOGFONT lf;
	m_pTreeCtrl->GetFont()->GetLogFont(&lf);
	m_comboFont.InitControl(lf.lfFaceName, 285);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertiesDlg::UpdateItem(HTREEITEM hItem)
{
	m_pTreeCtrl->SetItemFont(hItem, m_LogFont);
	m_pTreeCtrl->SetItemBold(hItem, m_bBoldCheck);
	m_pTreeCtrl->SetItemColor(hItem, m_crText);
	m_pTreeCtrl->SetItemBackColor(hItem, m_crBack);
}

void CPropertiesDlg::OnBtnApply() 
{
	ASSERT_VALID(m_pTreeCtrl);

	HDC hDC = ::GetDC(m_pTreeCtrl->m_hWnd);
	m_LogFont.lfHeight = -MulDiv(_ttoi(m_strFontSize), ::GetDeviceCaps(hDC, LOGPIXELSY), 72);
	::ReleaseDC(m_pTreeCtrl->m_hWnd, hDC);

	if (m_pTreeCtrl->IsMultiSelect())
	{
		HTREEITEM hItem = m_pTreeCtrl->GetFirstSelectedItem();
		while (hItem != NULL)
		{
			UpdateItem(hItem);
			m_pTreeCtrl->SetItemState(hItem, 0, TVIS_SELECTED);
			hItem = m_pTreeCtrl->GetNextSelectedItem(hItem);
		}
	}
	else
	{
		HTREEITEM hItem = m_pTreeCtrl->GetSelectedItem();
		UpdateItem(hItem);
	}

	m_pTreeCtrl->SendMessage(WM_ERASEBKGND, (WPARAM)hDC, (LPARAM)0);
	m_pTreeCtrl->Invalidate();

	CDialog::OnOK();
}

int CPropertiesDlg::DoModalEx(CXTPTreeCtrl* pTreeCtrl) 
{
	ASSERT_VALID(pTreeCtrl);
	m_pTreeCtrl = pTreeCtrl;
	
	return (int)CDialog::DoModal();
}
