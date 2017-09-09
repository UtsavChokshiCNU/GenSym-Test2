// FlatComboDlg.cpp : implementation file
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
#include "FlatCombo.h"
#include "FlatComboDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CFlatComboDlg dialog

CFlatComboDlg::CFlatComboDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CFlatComboDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlatComboDlg)
	m_bAutoComplete = FALSE;
	m_bDisable1 = FALSE;
	m_bDisable2 = FALSE;
	m_bFlatBorders = FALSE;
	m_nTheme = 2;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}

	m_strStylesPath += csStylesPath + _T("\\Styles\\");
}

void CFlatComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlatComboDlg)
	DDX_Control(pDX, IDC_FLAT_EDIT, m_wndFlatEdit);
	DDX_Control(pDX, IDC_GBOX_LIST, m_gboxList);
	DDX_Control(pDX, IDC_GBOX_DOWN, m_gboxDown);
	DDX_Control(pDX, IDC_GBOX_APPEAR, m_gboxAppear);
	DDX_Control(pDX, IDC_DROPLIST_TXT_CLR, m_cpText2);
	DDX_Control(pDX, IDC_DROPLIST_BAK_CLR, m_cpBack2);
	DDX_Control(pDX, IDC_DROPDOWN_TXT_CLR, m_cpText1);
	DDX_Control(pDX, IDC_DROPDOWN_BAK_CLR, m_cpBack1);
	DDX_Control(pDX, IDC_DROPDOWN_COMBO, m_wndFlatCombo1);
	DDX_Control(pDX, IDC_DROPLIST_COMBO, m_wndFlatCombo2);
	DDX_Check(pDX, IDC_DROPDOWN_AUTOCOMP, m_bAutoComplete);
	DDX_Check(pDX, IDC_DROPDOWN_DISABLE, m_bDisable1);
	DDX_Check(pDX, IDC_DROPLIST_DISABLE, m_bDisable2);
	DDX_Check(pDX, IDC_CHK_FLATBOARDERS, m_bFlatBorders);
	DDX_Radio(pDX, IDC_RADIO_THEME_DEFAULT, m_nTheme);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_COLOR, m_wndComboColor);
}

BEGIN_MESSAGE_MAP(CFlatComboDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CFlatComboDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DROPLIST_DISABLE, OnDroplistDisable)
	ON_BN_CLICKED(IDC_DROPDOWN_DISABLE, OnDropdownDisable)
	ON_BN_CLICKED(IDC_DROPDOWN_AUTOCOMP, OnDropdownAutocomp)
	ON_CPN_XTP_SELENDOK(IDC_DROPLIST_TXT_CLR, OnSelEndOKDLTxtClr)
	ON_CPN_XTP_SELENDOK(IDC_DROPLIST_BAK_CLR, OnSelEndOKDLBakClr)
	ON_CPN_XTP_SELENDOK(IDC_DROPDOWN_TXT_CLR, OnSelEndOKDDTxtClr)
	ON_CPN_XTP_SELENDOK(IDC_DROPDOWN_BAK_CLR, OnSelEndOKDDBakClr)
	ON_BN_CLICKED(IDC_RADIO_THEME_DEFAULT, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_FLAT, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_OFFICE2000, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_OFFICEXP, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_OFFICE2003, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_OFFICE2007, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_OFFICE2010, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_WINDOWS7, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_VSTUDIO2008, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_VSTUDIO2010, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_FLAT, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_THEME_ULTRAFLAT, OnThemeChanged)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHK_FLATBOARDERS, OnBnClickedChkFlatboarders)
	ON_CBN_SELENDOK(IDC_COMBO_COLOR, OnCbnSelendokComboColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatComboDlg message handlers

BOOL CFlatComboDlg::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	// Set control resizing.
	SetResize(IDC_GBOX_LIST, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_DROPLIST_COMBO, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_DOWN, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_DROPDOWN_COMBO, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_EDIT, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_APPEAR, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDOK, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDCANCEL, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);

	// prevent vertical resizing.
	SetFlag(xtpResizeNoVertical);

	// Load window placement
	LoadPlacement(_T("CFlatComboDlg2"));

	// set each combo's index.
	m_wndFlatCombo1.SetCurSel(0);
	m_wndFlatCombo2.SetCurSel(1);

	// enable auto completion based on boolean.
	m_wndFlatCombo1.EnableAutoCompletion( m_bAutoComplete );

	// set the text color controls based on current combo color.
	m_cpText2.SetColor( m_wndFlatCombo2.GetTextColor() );
	m_cpBack2.SetColor( m_wndFlatCombo2.GetBackColor() );
	m_cpText1.SetColor( m_wndFlatCombo1.GetTextColor() );
	m_cpBack1.SetColor( m_wndFlatCombo1.GetBackColor() );

	OnThemeChanged();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFlatComboDlg::OnDestroy()
{
	// Save window placement
	SavePlacement(_T("CFlatComboDlg2"));

	CXTPResizeDialog::OnDestroy();
}

void CFlatComboDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTPResizeDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFlatComboDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CXTPResizeDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFlatComboDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFlatComboDlg::OnSelEndOKDLTxtClr()
{
	m_wndFlatCombo2.SetTextColor(m_cpText2.GetColor());
	m_wndFlatCombo2.Invalidate();
}

void CFlatComboDlg::OnSelEndOKDLBakClr()
{
	m_wndFlatCombo2.SetBackColor(m_cpBack2.GetColor());
	m_wndFlatCombo2.Invalidate();
}

void CFlatComboDlg::OnSelEndOKDDTxtClr()
{
	m_wndFlatCombo1.SetTextColor(m_cpText1.GetColor());
	m_wndFlatCombo1.Invalidate();
}

void CFlatComboDlg::OnSelEndOKDDBakClr()
{
	m_wndFlatCombo1.SetBackColor(m_cpBack1.GetColor());
	m_wndFlatCombo1.Invalidate();
}

void CFlatComboDlg::OnDroplistDisable()
{
	UpdateData();
	m_wndFlatCombo2.EnableWindow( !m_bDisable2 );
}

void CFlatComboDlg::OnDropdownDisable()
{
	UpdateData();
	m_wndFlatCombo1.EnableWindow( !m_bDisable1 );
}

void CFlatComboDlg::OnDropdownAutocomp()
{
	UpdateData();
	m_wndFlatCombo1.EnableAutoCompletion( m_bAutoComplete );
}

HBRUSH CFlatComboDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CXTPResizeDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// set the combo boxes text and background colors...
	int nItem = pWnd->GetDlgCtrlID();
	switch (nItem)
	{
		case IDC_DROPLIST_COMBO:
		case IDC_DROPDOWN_COMBO:
			if( pWnd->IsWindowEnabled( ))
			{
				pDC->SetBkColor  (((CFlatComboBox*)pWnd)->GetBackColor());
				pDC->SetTextColor(((CFlatComboBox*)pWnd)->GetTextColor());
			}
			break;
	}

	return hbr;
}

void CFlatComboDlg::OnThemeChanged()
{
	UpdateData();

	m_wndComboColor.ResetContent();
	m_wndComboColor.EnableWindow(FALSE);

	switch (m_nTheme)
	{
	case 0:
		m_wndFlatCombo1.SetTheme(xtpControlThemeDefault);
		m_wndFlatCombo2.SetTheme(xtpControlThemeDefault);
		m_wndFlatEdit.SetTheme(xtpControlThemeDefault);
		break;

	case 1:
		m_wndFlatCombo1.SetTheme(xtpControlThemeOffice2000);
		m_wndFlatCombo2.SetTheme(xtpControlThemeOffice2000);
		m_wndFlatEdit.SetTheme(xtpControlThemeOffice2000);
		break;

	case 2:
		m_wndFlatCombo1.SetTheme(xtpControlThemeOfficeXP);
		m_wndFlatCombo2.SetTheme(xtpControlThemeOfficeXP);
		m_wndFlatEdit.SetTheme(xtpControlThemeOfficeXP);
		break;

	case 3:
		m_wndFlatCombo1.SetTheme(xtpControlThemeOffice2003);
		m_wndFlatCombo2.SetTheme(xtpControlThemeOffice2003);
		m_wndFlatEdit.SetTheme(xtpControlThemeOffice2003);
		break;

	case 4:
		XTPResourceImages()->SetHandle(m_strStylesPath + _T("Office2007.dll"), _T("OFFICE2007BLUE.INI"));
		m_wndFlatCombo1.SetTheme(xtpControlThemeResource);
		m_wndFlatCombo2.SetTheme(xtpControlThemeResource);
		m_wndFlatEdit.SetTheme(xtpControlThemeResource);
		m_wndComboColor.EnableWindow(TRUE);
		m_wndComboColor.AddString(_T("Aqua"));
		m_wndComboColor.AddString(_T("Black"));
		m_wndComboColor.AddString(_T("Blue"));
		m_wndComboColor.AddString(_T("Silver"));
		m_wndComboColor.SetCurSel(2);
		break;

	case 5:
		XTPResourceImages()->SetHandle(m_strStylesPath + _T("Office2010.dll"), _T("OFFICE2010BLUE.INI"));
		m_wndFlatCombo1.SetTheme(xtpControlThemeResource);
		m_wndFlatCombo2.SetTheme(xtpControlThemeResource);
		m_wndFlatEdit.SetTheme(xtpControlThemeResource);
		m_wndComboColor.EnableWindow(TRUE);
		m_wndComboColor.AddString(_T("Black"));
		m_wndComboColor.AddString(_T("Blue"));
		m_wndComboColor.AddString(_T("Silver"));
		m_wndComboColor.SetCurSel(1);
		break;

	case 6:
		XTPResourceImages()->SetHandle(m_strStylesPath + _T("Windows7.dll"), _T("WINDOWS7BLUE.INI"));
		m_wndFlatCombo1.SetTheme(xtpControlThemeResource);
		m_wndFlatCombo2.SetTheme(xtpControlThemeResource);
		m_wndFlatEdit.SetTheme(xtpControlThemeResource);
		m_wndComboColor.EnableWindow(TRUE);
		m_wndComboColor.AddString(_T("Blue"));
		m_wndComboColor.SetCurSel(0);
		break;

	case 7:
		m_wndFlatCombo1.SetTheme(xtpControlThemeVisualStudio2008);
		m_wndFlatCombo2.SetTheme(xtpControlThemeVisualStudio2008);
		m_wndFlatEdit.SetTheme(xtpControlThemeVisualStudio2008);
		break;

	case 8:
		m_wndFlatCombo1.SetTheme(xtpControlThemeVisualStudio2010);
		m_wndFlatCombo2.SetTheme(xtpControlThemeVisualStudio2010);
		m_wndFlatEdit.SetTheme(xtpControlThemeVisualStudio2010);
		break;

	case 9:
		m_wndFlatCombo1.SetTheme(xtpControlThemeFlat);
		m_wndFlatCombo2.SetTheme(xtpControlThemeFlat);
		m_wndFlatEdit.SetTheme(xtpControlThemeFlat);
		break;

	case 10:
		m_wndFlatCombo1.SetTheme(xtpControlThemeUltraFlat);
		m_wndFlatCombo2.SetTheme(xtpControlThemeUltraFlat);
		m_wndFlatEdit.SetTheme(xtpControlThemeUltraFlat);
		break;
	}

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
}

void CFlatComboDlg::OnBnClickedChkFlatboarders()
{
	UpdateData();

	m_wndFlatCombo1.SetFlatStyle(m_bFlatBorders);
	m_wndFlatCombo2.SetFlatStyle(m_bFlatBorders);
	m_wndFlatEdit.SetFlatStyle(m_bFlatBorders);
}

void CFlatComboDlg::OnCbnSelendokComboColor()
{
	int nIndex = m_wndComboColor.GetCurSel();

	switch (m_nTheme)
	{
	case 4:
		XTPResourceImages()->SetHandle(m_strStylesPath + _T("Office2007.dll"), nIndex == 0 ? _T("OFFICE2007AQUA.INI") : nIndex == 1 ? _T("OFFICE2007BLACK.INI") : nIndex == 2 ? _T("OFFICE2007BLUE.INI") : _T("OFFICE2007SILVER.INI"));
		break;
	case 5:
		XTPResourceImages()->SetHandle(m_strStylesPath + _T("Office2010.dll"), nIndex == 0 ? _T("OFFICE2010BLACK.INI") : nIndex == 1 ? _T("OFFICE2010BLUE.INI") : _T("OFFICE2010SILVER.INI"));
		break;
	case 6:
		XTPResourceImages()->SetHandle(m_strStylesPath + _T("Windows7.dll"), _T("WINDOWS7BLUE.INI"));
		break;
	}

	m_wndFlatCombo1.RefreshMetrics();
	m_wndFlatCombo2.RefreshMetrics();
	m_wndFlatEdit.RefreshMetrics();

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
}
