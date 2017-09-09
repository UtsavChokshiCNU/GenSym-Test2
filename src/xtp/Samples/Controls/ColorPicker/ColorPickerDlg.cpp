// ColorPickerDlg.cpp : implementation file
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
#include "ColorPicker.h"
#include "ColorPickerDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorPickerDlg dialog

CColorPickerDlg::CColorPickerDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CColorPickerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorPickerDlg)
	m_bExtended = TRUE;
	m_bMoreColors = TRUE;
	m_bNoFill = FALSE;
	m_3DBorder = TRUE;
	m_bDisable = FALSE;
	m_bDisplayHex = TRUE;
	m_bColorText = FALSE;
	m_bShowText = FALSE;
	m_iTheme = 2;
	m_bEyeDropper = TRUE;
	//}}AFX_DATA_INIT

	m_clrText = RGB(0xff,0xff,0xff);
	m_clrBack = RGB(0x00,0x00,0xff);

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorPickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPickerDlg)
	DDX_Control(pDX, IDC_GBOX_BUTTON, m_gboxButton);
	DDX_Control(pDX, IDC_GBOX_POPUP, m_gboxPopup);
	DDX_Control(pDX, IDC_GBOX_DIALOG, m_gboxDialog);
	DDX_Control(pDX, IDC_GBOX_THEME, m_gboxTheme);
	DDX_Control(pDX, IDC_COMBO_DEMO, m_comboBox);
	DDX_Control(pDX, IDC_CLR_TEXT, m_cpTextColor);
	DDX_Control(pDX, IDC_CLR_BACK, m_cpBackColor);
	DDX_Check(pDX, IDC_CHK_EXTENDED, m_bExtended);
	DDX_Check(pDX, IDC_CHK_MORECOLORS, m_bMoreColors);
	DDX_Check(pDX, IDC_CHK_NOFILL, m_bNoFill);
	DDX_Check(pDX, IDC_CHK_3DBORDER, m_3DBorder);
	DDX_Check(pDX, IDC_CHK_DISABLE, m_bDisable);
	DDX_Check(pDX, IDC_CHK_DISPLAY_HEX, m_bDisplayHex);
	DDX_Check(pDX, IDC_CHK_COLORTEXT, m_bColorText);
	DDX_Check(pDX, IDC_CHK_NOTEXT, m_bShowText);
	DDX_Radio(pDX, IDC_RADIO_DEFAULT, m_iTheme);
	DDX_Check(pDX, IDC_CHK_EYEDROPPER, m_bEyeDropper);
	//}}AFX_DATA_MAP
	DDX_XTPColorPicker(pDX, IDC_CLR_TEXT, m_clrText);
	DDX_XTPColorPicker(pDX, IDC_CLR_BACK, m_clrBack);
}

BEGIN_MESSAGE_MAP(CColorPickerDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CColorPickerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_CPN_XTP_SELENDOK(IDC_CLR_TEXT, OnSelEndOkTextClr)
	ON_CPN_XTP_SELENDOK(IDC_CLR_BACK, OnSelEndOkBackClr)
	ON_BN_CLICKED(IDC_CHK_NOFILL, OnChkNofill)
	ON_BN_CLICKED(IDC_CHK_EXTENDED, OnChkExtended)
	ON_BN_CLICKED(IDC_CHK_MORECOLORS, OnChkMorecolors)
	ON_CBN_SETFOCUS(IDC_COMBO_DEMO, OnSetfocusComboDemo)
	ON_BN_CLICKED(IDC_CHK_3DBORDER, OnChk3dborder)
	ON_BN_CLICKED(IDC_CHK_DISPLAY_HEX, OnChkDisplayHex)
	ON_BN_CLICKED(IDC_CHK_DISABLE, OnChkDisable)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHK_NOTEXT, OnChkNoText)
	ON_BN_CLICKED(IDC_CHK_COLORTEXT, OnChkColorText)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT, OnRadioDefault)
	ON_BN_CLICKED(IDC_RADIO_OFFICEXP, OnRadioOfficeXP)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003, OnRadioOffice2003)
	ON_BN_CLICKED(IDC_CHK_EYEDROPPER, OnChkEyeDropper)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPickerDlg message handlers

BOOL CColorPickerDlg::OnInitDialog()
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
	SetResize(IDC_COMBO_DEMO,  XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
	SetResize(IDCANCEL,        XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_BUTTON, XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_POPUP,  XTP_ANCHOR_TOPLEFT,   XTP_ANCHOR_TOPCENTER);
	SetResize(IDC_GBOX_THEME,  XTP_ANCHOR_TOPCENTER, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_GBOX_DIALOG, XTP_ANCHOR_TOPLEFT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_RADIO_DEFAULT,  XTP_ANCHOR_TOPCENTER,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_RADIO_OFFICEXP,  XTP_ANCHOR_TOPCENTER,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_RADIO_OFFICE2003,  XTP_ANCHOR_TOPCENTER,   XTP_ANCHOR_TOPRIGHT);

	// prevent vertical resizing.
	SetFlag(xtpResizeNoVertical);

	// Load window placement
	LoadPlacement(_T("CColorPickerDlg"));

	//------------------------------------
	// TODO: Add extra initialization here
	//------------------------------------

	m_comboBox.SetCurSel(0);

	m_cpBackColor.SetColor(m_clrBack);
	m_cpBackColor.SetDefaultColor(GetSysColor(COLOR_WINDOW));
	m_cpBackColor.ShowText(m_bShowText);

	m_cpTextColor.SetColor(m_clrText);
	m_cpTextColor.SetDefaultColor(GetSysColor(COLOR_WINDOWTEXT));
	m_cpTextColor.ShowText(m_bShowText);

	// Add some user defined color values.
	CUIntArray arUserColors;
	arUserColors.Add(RGB(150,0,0));
	arUserColors.Add(RGB(0,150,0));
	arUserColors.Add(RGB(0,0,150));
	CXTPColorSelectorCtrl::SetUserColors(arUserColors);

/*
	SetColors method used to set custom colors for color popup

	static XTP_PICK_BUTTON standardColors[] =
	{
		{   RGB(0x00, 0x00, 0x00), XTP_IDS_CLR_BLACK            },
		{   RGB(0x80, 0x80, 0x80), XTP_IDS_CLR_GRAY             },
		{   RGB(0x80, 0x00, 0x00), XTP_IDS_CLR_MAROON           },
		{   RGB(0x80, 0x80, 0x00), XTP_IDS_CLR_OLIVE            },
		{   RGB(0x00, 0x80, 0x00), XTP_IDS_CLR_GREEN            },
		{   RGB(0x00, 0x80, 0x80), XTP_IDS_CLR_TEAL             },
		{   RGB(0x00, 0x00, 0x80), XTP_IDS_CLR_NAVY             },
		{   RGB(0x80, 0x00, 0x80), XTP_IDS_CLR_PURPLE           },
		{   RGB(0xFF, 0xFF, 0xFF), XTP_IDS_CLR_WHITE            },
		{   RGB(0xC0, 0xC0, 0xC0), XTP_IDS_CLR_SILVER           },
		{   RGB(0xFF, 0x00, 0x00), XTP_IDS_CLR_RED              },
		{   RGB(0xFF, 0xFF, 0x00), XTP_IDS_CLR_YELLOW           },
		{   RGB(0x00, 0xFF, 0x00), XTP_IDS_CLR_LIME             },
		{   RGB(0x00, 0xFF, 0xFF), XTP_IDS_CLR_AQUA             },
		{   RGB(0x00, 0x00, 0xFF), XTP_IDS_CLR_BLUE             },
		{   RGB(0xFF, 0x00, 0xFF), XTP_IDS_CLR_FUCHSIA          },
	};
	m_cpTextColor.SetColors(standardColors, _countof(standardColors), 8);
*/

	OnChkExtended();
	OnChkMorecolors();
	OnChk3dborder();
	OnChkDisplayHex();
	OnChkEyeDropper();
	OnRadioOffice2003();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorPickerDlg::OnDestroy()
{
	// Save window placement
	SavePlacement(_T("CColorPickerDlg"));

	CXTPResizeDialog::OnDestroy();
}

void CColorPickerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CColorPickerDlg::OnPaint()
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
HCURSOR CColorPickerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CColorPickerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CXTPResizeDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	int nItem = pWnd->GetDlgCtrlID();
	switch (nItem)
	{
		case IDC_COMBO_DEMO:
			if( pWnd->IsWindowEnabled( ))
			{
				pDC->SetTextColor(m_clrText);
				pDC->SetBkColor(m_clrBack);
			}
			break;
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CColorPickerDlg::OnSelEndOkTextClr()
{
	UpdateData();
	m_comboBox.Invalidate();
}

void CColorPickerDlg::OnSelEndOkBackClr()
{
	UpdateData();
	m_comboBox.Invalidate();
}

void CColorPickerDlg::OnChkNofill()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	DWORD dwRem = m_bNoFill ? 0 : CPS_XTP_NOFILL;
	DWORD dwAdd = m_bNoFill ? CPS_XTP_NOFILL : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkExtended()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	DWORD dwRem = m_bExtended ? 0 : CPS_XTP_EXTENDED;
	DWORD dwAdd = m_bExtended ? CPS_XTP_EXTENDED : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkMorecolors()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	DWORD dwRem = m_bMoreColors ? 0 : CPS_XTP_MORECOLORS;
	DWORD dwAdd = m_bMoreColors ? CPS_XTP_MORECOLORS : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChk3dborder()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	DWORD dwRem = m_3DBorder ? 0 : CPS_XTP_SHOW3DSELECTION;
	DWORD dwAdd = m_3DBorder ? CPS_XTP_SHOW3DSELECTION : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkDisplayHex()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	DWORD dwRem = m_bDisplayHex ? 0 : CPS_XTP_SHOWHEXVALUE;
	DWORD dwAdd = m_bDisplayHex ? CPS_XTP_SHOWHEXVALUE : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkEyeDropper() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	DWORD dwRem = m_bEyeDropper ? 0 : CPS_XTP_SHOWEYEDROPPER;
	DWORD dwAdd = m_bEyeDropper ? CPS_XTP_SHOWEYEDROPPER : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}

void CColorPickerDlg::OnChkDisable()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_cpBackColor.EnableWindow(!m_bDisable);
	m_cpTextColor.EnableWindow(!m_bDisable);
}

void CColorPickerDlg::OnSetfocusComboDemo()
{
	// don't allow interaction with combo box.
	m_cpTextColor.SetFocus();
}

void CColorPickerDlg::OnChkNoText()
{
	UpdateData();
	m_cpBackColor.ShowText(m_bShowText);
	m_cpTextColor.ShowText(m_bShowText);
}

void CColorPickerDlg::OnChkColorText()
{
	UpdateData();
	m_cpBackColor.ShowTextInColor(m_bColorText);
	m_cpTextColor.ShowTextInColor(m_bColorText);
}

void CColorPickerDlg::OnRadioDefault() 
{
// 	XTPControlThemeManager()->SetTheme(xtpControlThemeOffice2000);
}

void CColorPickerDlg::OnRadioOfficeXP() 
{
// 	XTPControlThemeManager()->SetTheme(xtpControlThemeOfficeXP);
}

void CColorPickerDlg::OnRadioOffice2003() 
{
// 	XTPControlThemeManager()->SetTheme(xtpControlThemeOffice2003);
}
