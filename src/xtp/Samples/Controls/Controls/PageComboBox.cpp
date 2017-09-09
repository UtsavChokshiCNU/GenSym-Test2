// PageComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "Controls.h"
#include "PageComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageComboBox property page

IMPLEMENT_DYNCREATE(CPageComboBox, CXTPResizePropertyPage)

CPageComboBox::CPageComboBox() : CXTPResizePropertyPage(CPageComboBox::IDD)
{
	//{{AFX_DATA_INIT(CPageComboBox)
	m_bEnabled = TRUE;
	m_bFlatStyle = FALSE;
	m_nTheme = 5;
	m_bUseVisualStyle = FALSE;
	m_bAutoComplete = FALSE;
	//}}AFX_DATA_INIT
}

CPageComboBox::~CPageComboBox()
{
}

void CPageComboBox::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageComboBox)
	DDX_Control(pDX, IDC_COMBO_DROPDOWN, m_cmbDropDown);
	DDX_Control(pDX, IDC_COMBO_DROPDOWNLIST, m_cmbDropDownList);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnabled);
	DDX_Check(pDX, IDC_CHECK_FLATSTYLE, m_bFlatStyle);
	DDX_Radio(pDX, IDC_RADIO_CLASSIC, m_nTheme);
	DDX_Check(pDX, IDC_CHECK_WINXP_THEMES, m_bUseVisualStyle);
	DDX_Check(pDX, IDC_CHECK_AUTOCOMPLETE, m_bAutoComplete);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageComboBox, CXTPResizePropertyPage)
	//{{AFX_MSG_MAP(CPageComboBox)
	ON_BN_CLICKED(IDC_RADIO_CLASSIC, OnRadTheme)
	ON_BN_CLICKED(IDC_CHECK_FLATSTYLE, OnCheckFlatstyle)
	ON_BN_CLICKED(IDC_CHECK_WINXP_THEMES, OnCheckWinxpThemes)
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	ON_BN_CLICKED(IDC_RADIO_FLAT, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_ULTRAFLAT, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2000, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICEXP, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003, OnRadTheme)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2007, OnRadTheme)
	ON_BN_CLICKED(IDC_CHECK_AUTOCOMPLETE, OnCheckAutocomplete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageComboBox message handlers

BOOL CPageComboBox::OnInitDialog() 
{
	CXTPResizePropertyPage::OnInitDialog();
	
	int i;

	for (i = IDC_GBOX_THEME; i <= IDC_RADIO_OFFICE2007; i++)
		SetResize(i, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));
	
	SetResize(IDC_CHECK_FLATSTYLE, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));
	SetResize(IDC_CHECK_WINXP_THEMES, CXTPResizePoint((float)(1.0/3.0), 0), CXTPResizePoint((float)(2.0/3.0), 0));
	
	SetResize(IDC_GBOX_OPTIONS, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_ENABLED, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	
	SetResize(IDC_COMBO_DROPDOWN, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));
	SetResize(IDC_COMBO_DROPDOWNLIST, XTP_ANCHOR_TOPLEFT, CXTPResizePoint((float)(1.0/3.0), 0));

	m_cmbDropDown.SetCurSel(0);
	m_cmbDropDownList.SetCurSel(0);

	OnRadTheme();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageComboBox::OnRadTheme() 
{
	UpdateData();

	m_cmbDropDown.SetTheme((XTPControlTheme)m_nTheme);
	m_cmbDropDownList.SetTheme((XTPControlTheme)m_nTheme);

	m_bUseVisualStyle = m_cmbDropDown.GetUseVisualStyle();
	UpdateData(FALSE);
}

void CPageComboBox::OnCheckFlatstyle() 
{
	UpdateData();
	
	m_cmbDropDown.SetFlatStyle(m_bFlatStyle);	
	m_cmbDropDownList.SetFlatStyle(m_bFlatStyle);		
}

void CPageComboBox::OnCheckWinxpThemes() 
{
	UpdateData();
	
	m_cmbDropDown.SetUseVisualStyle(m_bUseVisualStyle);	
	m_cmbDropDownList.SetUseVisualStyle(m_bUseVisualStyle);	
}

void CPageComboBox::OnCheckEnabled() 
{
	UpdateData();
	
	m_cmbDropDown.EnableWindow(m_bEnabled);
	m_cmbDropDownList.EnableWindow(m_bEnabled);
}

void CPageComboBox::OnCheckAutocomplete() 
{
	UpdateData();

	m_cmbDropDown.EnableAutoCompletion(m_bAutoComplete);
	
}
