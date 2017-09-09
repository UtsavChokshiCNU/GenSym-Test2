// PageEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Controls.h"
#include "PageEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageEdit dialog


CPageEdit::CPageEdit(CWnd* pParent /*=NULL*/)
	: CXTPResizePropertyPage(CPageEdit::IDD)
{
	//{{AFX_DATA_INIT(CPageEdit)
	m_bEnabled = TRUE;
	m_bPassword = FALSE;
	m_bReadOnly = FALSE;
	m_bUseVisualStyle = FALSE;
	m_nTheme = 5;
	m_bFlatStyle = FALSE;
	//}}AFX_DATA_INIT
}


void CPageEdit::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageEdit)
	DDX_Control(pDX, IDC_BUTTON, m_btnBuddy);
	DDX_Control(pDX, IDC_SPIN, m_btnSpinButton);
	DDX_Control(pDX, IDC_EDIT_SPIN, m_edtSpin);
	DDX_Control(pDX, IDC_EDIT_BUTTON, m_edtButton);
	DDX_Control(pDX, IDC_EDIT_PATTERN, m_edtPattern);
	DDX_Control(pDX, IDC_EDIT_MULTILINE, m_edtMultiline);
	DDX_Control(pDX, IDC_EDIT_MASKED, m_edtMasked);
	DDX_Control(pDX, IDC_EDIT_SINGLELINE, m_edtSingleLine);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnabled);
	DDX_Check(pDX, IDC_CHECK_PASSWORD, m_bPassword);
	DDX_Check(pDX, IDC_CHECK_READONLY, m_bReadOnly);
	DDX_Check(pDX, IDC_CHECK_WINXP_THEMES, m_bUseVisualStyle);
	DDX_Radio(pDX, IDC_RADIO_CLASSIC, m_nTheme);
	DDX_Check(pDX, IDC_CHECK_FLATSTYLE, m_bFlatStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageEdit, CXTPResizePropertyPage)
	//{{AFX_MSG_MAP(CPageEdit)
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	ON_BN_CLICKED(IDC_CHECK_READONLY, OnCheckReadonly)
	ON_BN_CLICKED(IDC_CHECK_PASSWORD, OnCheckPassword)
	ON_BN_CLICKED(IDC_RADIO_CLASSIC, OnRadTheme)
	ON_BN_CLICKED(IDC_CHECK_FLATSTYLE, OnCheckFlatstyle)
	ON_BN_CLICKED(IDC_RADIO_FLAT, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_ULTRAFLAT, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2000, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICEXP, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2007, OnRadTheme)
	ON_BN_CLICKED(IDC_CHECK_WINXP_THEMES, OnCheckWinxpThemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageEdit message handlers

BOOL CPageEdit::OnInitDialog() 
{
	CXTPResizePropertyPage::OnInitDialog();
	
	int i;	

	for (i = IDC_GBOX_THEME; i <= IDC_RADIO_OFFICE2007; i++)
		SetResize(i, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));

	SetResize(IDC_CHECK_FLATSTYLE, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));
	SetResize(IDC_CHECK_WINXP_THEMES, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));

	SetResize(IDC_GBOX_OPTIONS, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_ENABLED, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_READONLY, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_PASSWORD, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_EDIT_SINGLELINE, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));
	SetResize(IDC_EDIT_MULTILINE, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));
	SetResize(IDC_EDIT_MASKED, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));
	SetResize(IDC_EDIT_PATTERN, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));

	OnRadTheme();


	m_edtMasked.SetEditMask(_T("Phone No: (000) 000-0000"), _T("Phone No: (___) ___-____"));

	m_edtPattern.SetPattern(_T("\\d*"));

	m_btnSpinButton.SetRange(0, 100);

	m_btnBuddy.SetBuddy(&m_edtButton);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageEdit::OnCheckEnabled() 
{
	UpdateData();

	m_edtSingleLine.EnableWindow(m_bEnabled);
	m_edtMultiline.EnableWindow(m_bEnabled);
	m_edtMasked.EnableWindow(m_bEnabled);
	m_edtPattern.EnableWindow(m_bEnabled);
	
}

void CPageEdit::OnCheckReadonly() 
{
	UpdateData();

	m_edtSingleLine.SetReadOnly(m_bReadOnly);
	m_edtMultiline.SetReadOnly(m_bReadOnly);
	m_edtMasked.SetReadOnly(m_bReadOnly);
	m_edtPattern.SetReadOnly(m_bReadOnly);
	
}

void CPageEdit::OnCheckPassword() 
{
	UpdateData();

	m_edtSingleLine.SetPasswordChar(m_bPassword ? '*' : 0);
	m_edtMultiline.SetPasswordChar(m_bPassword ? '*' : 0);

	m_edtSingleLine.Invalidate();
	m_edtMultiline.Invalidate();
	
}

void CPageEdit::OnRadTheme() 
{
	UpdateData();

	m_edtSingleLine.SetTheme((XTPControlTheme)m_nTheme);
	m_edtMultiline.SetTheme((XTPControlTheme)m_nTheme);
	m_edtMasked.SetTheme((XTPControlTheme)m_nTheme);
	m_edtPattern.SetTheme((XTPControlTheme)m_nTheme);
	m_edtSpin.SetTheme((XTPControlTheme)m_nTheme);
	m_edtButton.SetTheme((XTPControlTheme)m_nTheme);

	m_btnSpinButton.SetTheme((XTPControlTheme)m_nTheme);
	m_btnBuddy.SetTheme((XTPControlTheme)m_nTheme);		

	m_bUseVisualStyle = m_edtSingleLine.GetUseVisualStyle();
	UpdateData(FALSE);

}

void CPageEdit::OnCheckFlatstyle() 
{
	UpdateData();
	
	m_edtSingleLine.SetFlatStyle(m_bFlatStyle);	
	m_edtMultiline.SetFlatStyle(m_bFlatStyle);	
	m_edtMasked.SetFlatStyle(m_bFlatStyle);	
	m_edtPattern.SetFlatStyle(m_bFlatStyle);	
}

void CPageEdit::OnCheckWinxpThemes() 
{
	UpdateData();

	m_edtSingleLine.SetUseVisualStyle(m_bUseVisualStyle);	
	m_edtMultiline.SetUseVisualStyle(m_bUseVisualStyle);	
	m_edtMasked.SetUseVisualStyle(m_bUseVisualStyle);	
	m_edtPattern.SetUseVisualStyle(m_bUseVisualStyle);		
	m_edtSpin.SetUseVisualStyle(m_bUseVisualStyle);		
	m_edtButton.SetUseVisualStyle(m_bUseVisualStyle);		
	
	m_btnSpinButton.SetUseVisualStyle(m_bUseVisualStyle);		
	m_btnBuddy.SetUseVisualStyle(m_bUseVisualStyle);		
}
