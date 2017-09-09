// HexEditDlg.cpp : implementation file
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
#include "HexEdit.h"
#include "HexEditDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexEditDlg dialog

CHexEditDlg::CHexEditDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CHexEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHexEditDlg)
	m_bAddress = TRUE;
	m_bHex = TRUE;
	m_bASCII = TRUE;
	m_bWideAddress = TRUE;
	m_bEnable = TRUE;
	m_bCaret = TRUE;
	m_crBackEnabled = m_editHex.GetBackColor();
	m_crTextEnabled = m_editHex.GetTextColor();
	m_crBackHiliteEnabled = m_editHex.GetHighlightBackColor();
	m_crTextHiliteEnabled = m_editHex.GetHighlightTextColor();
	m_crBackDisabled = m_editHex.GetDisabledBackColor();
	m_crTextDisabled = m_editHex.GetDisabledTextColor();
	m_crBackHiliteDisabled = m_editHex.GetDisabledHighlightBackColor();
	m_crTextHiliteDisabled = m_editHex.GetDisabledHighlightTextColor();
	m_bAllowDel = TRUE;
	m_bReadOnly = FALSE;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pData = (LPBYTE) // don't use _T()
		"This is some test data for CXTPHexEdit without any special meaning. "
		"You can type 10 characters past the end.";
}

void CHexEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHexEditDlg)
	DDX_Control(pDX, IDC_CLR_TEXT_HILITE_DISABLED, m_cpTextHiliteDisabled);
	DDX_Control(pDX, IDC_CLR_BACK_HILITE_DISABLED, m_cpBackHiliteDisabled);
	DDX_Control(pDX, IDC_CLR_TEXT_DISABLED, m_cpTextEnabledDisabled);
	DDX_Control(pDX, IDC_CLR_BACK_DISABLED, m_cpBackEnabledDisabled);
	DDX_Control(pDX, IDC_CLR_TEXT_HILITE_ENABLED, m_cpTextHiliteEnabled);
	DDX_Control(pDX, IDC_CLR_BACK_HILITE_ENABLED, m_cpBackHiliteEnabled);
	DDX_Control(pDX, IDC_CLR_TEXT_ENABLED, m_cpTextEnabled);
	DDX_Control(pDX, IDC_CLR_BACK_ENABLED, m_cpBackEnabled);
	DDX_Control(pDX, IDC_EDIT_BASEADDR, m_editBaseAddress);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_HEXEDIT, m_editHex);
	DDX_Control(pDX, IDC_TXT_ENABLED, m_txtEnabled);
	DDX_Control(pDX, IDC_TXT_DISABLED, m_txtDisabled);
	DDX_Check(pDX, IDC_CHK_ADDRESS, m_bAddress);
	DDX_Check(pDX, IDC_CHK_HEXCODE, m_bHex);
	DDX_Check(pDX, IDC_CHK_ASCII, m_bASCII);
	DDX_Check(pDX, IDC_CHK_WIDE_ADDRESS, m_bWideAddress);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHK_CARET, m_bCaret);
	DDX_XTPColorPicker(pDX, IDC_CLR_BACK_ENABLED, m_crBackEnabled);
	DDX_XTPColorPicker(pDX, IDC_CLR_TEXT_ENABLED, m_crTextEnabled);
	DDX_XTPColorPicker(pDX, IDC_CLR_BACK_HILITE_ENABLED, m_crBackHiliteEnabled);
	DDX_XTPColorPicker(pDX, IDC_CLR_TEXT_HILITE_ENABLED, m_crTextHiliteEnabled);
	DDX_XTPColorPicker(pDX, IDC_CLR_BACK_DISABLED, m_crBackDisabled);
	DDX_XTPColorPicker(pDX, IDC_CLR_TEXT_DISABLED, m_crTextDisabled);
	DDX_XTPColorPicker(pDX, IDC_CLR_BACK_HILITE_DISABLED, m_crBackHiliteDisabled);
	DDX_XTPColorPicker(pDX, IDC_CLR_TEXT_HILITE_DISABLED, m_crTextHiliteDisabled);
	DDX_Check(pDX, IDC_CHK_ALLOWDEL, m_bAllowDel);
	DDX_Check(pDX, IDC_CHK_READONLY, m_bReadOnly);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHexEditDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CHexEditDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHK_ADDRESS, OnChkAddress)
	ON_BN_CLICKED(IDC_CHK_HEXCODE, OnChkHexCode)
	ON_BN_CLICKED(IDC_CHK_ASCII, OnChkAscii)
	ON_BN_CLICKED(IDC_CHK_WIDE_ADDRESS, OnChkWideAddress)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_BASEADDR, OnChangeBaseAddress)
	ON_BN_CLICKED(IDC_CHK_ENABLE, OnEnable)
	ON_CPN_XTP_SELENDOK(IDC_CLR_BACK_ENABLED, OnClrBackEnabled)
	ON_CPN_XTP_SELENDOK(IDC_CLR_TEXT_ENABLED, OnClrTextEnabled)
	ON_CPN_XTP_SELENDOK(IDC_CLR_BACK_HILITE_ENABLED, OnClrBackHiliteEnabled)
	ON_CPN_XTP_SELENDOK(IDC_CLR_TEXT_HILITE_ENABLED, OnClrTextHiliteEnabled)
	ON_CPN_XTP_SELENDOK(IDC_CLR_BACK_DISABLED, OnClrBackDisabled)
	ON_CPN_XTP_SELENDOK(IDC_CLR_TEXT_DISABLED, OnClrTextDisabled)
	ON_CPN_XTP_SELENDOK(IDC_CLR_BACK_HILITE_DISABLED, OnClrBackHiliteDisabled)
	ON_CPN_XTP_SELENDOK(IDC_CLR_TEXT_HILITE_DISABLED, OnClrTextHiliteDisabled)
	ON_BN_CLICKED(IDC_CHK_CARET, OnChkCaret)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHK_ALLOWDEL, OnChkAllowdel)
	ON_BN_CLICKED(IDC_CHK_READONLY, OnChkReadonly)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexEditDlg message handlers

BOOL CHexEditDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	m_slider.SetRange(1, 16);
	m_slider.SetPos(8);
	m_editHex.SetBPR(8);

	const int len = (int)strlen((char *)m_pData);
	m_editHex.SetData(m_pData, len, len + 10);
	m_editBaseAddress.SetEditMask(_T("0xHHHHHHHH"), _T("0x________"), _T("0x00000000"));

	m_cpBackEnabled.SetColor(m_crBackEnabled);
	m_cpBackEnabled.SetDefaultColor(m_crBackEnabled);

	m_cpTextEnabled.SetColor(m_crTextEnabled);
	m_cpTextEnabled.SetDefaultColor(m_crTextEnabled);

	m_cpBackHiliteEnabled.SetColor(m_crBackHiliteEnabled);
	m_cpBackHiliteEnabled.SetDefaultColor(m_crBackHiliteEnabled);

	m_cpTextHiliteEnabled.SetColor(m_crTextHiliteEnabled);
	m_cpTextHiliteEnabled.SetDefaultColor(m_crTextHiliteEnabled);

	m_cpBackEnabledDisabled.SetColor(m_crBackDisabled);
	m_cpBackEnabledDisabled.SetDefaultColor(m_crBackDisabled);

	m_cpTextEnabledDisabled.SetColor(m_crTextDisabled);
	m_cpTextEnabledDisabled.SetDefaultColor(m_crTextDisabled);

	m_cpBackHiliteDisabled.SetColor(m_crBackHiliteDisabled);
	m_cpBackHiliteDisabled.SetDefaultColor(m_crBackHiliteDisabled);

	m_cpTextHiliteDisabled.SetColor(m_crTextHiliteDisabled);
	m_cpTextHiliteDisabled.SetDefaultColor(m_crTextHiliteDisabled);

	// set the font for the separators
	m_txtEnabled.SetFont(&XTPAuxData().fontBold);
	m_txtDisabled.SetFont(&XTPAuxData().fontBold);

	// Set control resizing.
	SetResize(IDC_HEXEDIT,                  XTP_ANCHOR_TOPLEFT,    XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK,                         XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDCANCEL,                     XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_TXT_BASEADDR,             XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_EDIT_BASEADDR,            XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHK_ADDRESS,              XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHK_HEXCODE,              XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHK_ASCII,                XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHK_WIDE_ADDRESS,         XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_TXT_BYTE,                 XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_SLIDER,                   XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHK_ENABLE,               XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHK_CARET,                XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHK_READONLY,             XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHK_ALLOWDEL,             XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_TXT_ENABLED,              XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_DISABLED,             XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_BACK_ENABLED,         XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_BACK_ENABLED,         XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_TEXT_ENABLED,         XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_TEXT_ENABLED,         XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_BACK_HILITE_ENABLED,  XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_BACK_HILITE_ENABLED,  XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_TEXT_HILITE_ENABLED,  XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_TEXT_HILITE_ENABLED,  XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_BACK_DISABLED,        XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_BACK_DISABLED,        XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_TEXT_DISABLED,        XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_TEXT_DISABLED,        XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_BACK_HILITE_DISABLED, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_BACK_HILITE_DISABLED, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_TXT_TEXT_HILITE_DISABLED, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_TEXT_HILITE_DISABLED, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_GBOX_ENABLED,             XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_GBOX_DISABLED,            XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMRIGHT);

	// Load window placement
	LoadPlacement(_T("CHexEditDlg"));

	CXTPPaintManager::SetTheme(xtpThemeOfficeXP);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHexEditDlg::OnDestroy()
{
	// Save window placement
	SavePlacement(_T("CHexEditDlg"));

	CXTPResizeDialog::OnDestroy();
}

void CHexEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHexEditDlg::OnPaint()
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
HCURSOR CHexEditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHexEditDlg::OnChkAddress()
{
	UpdateData(TRUE);
	m_editHex.SetOptions(m_bAddress, m_bHex, m_bASCII, m_bWideAddress);
	m_editHex.RedrawWindow();
}

void CHexEditDlg::OnChkHexCode()
{
	UpdateData(TRUE);
	m_editHex.SetOptions(m_bAddress, m_bHex, m_bASCII, m_bWideAddress);
	m_editHex.RedrawWindow();
}

void CHexEditDlg::OnChkAscii()
{
	UpdateData(TRUE);
	m_editHex.SetOptions(m_bAddress, m_bHex, m_bASCII, m_bWideAddress);
	m_editHex.RedrawWindow();
}

void CHexEditDlg::OnChkWideAddress()
{
	UpdateData(TRUE);
	m_editHex.SetOptions(m_bAddress, m_bHex, m_bASCII, m_bWideAddress);
	m_editHex.RedrawWindow();
}

void CHexEditDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	m_editHex.SetBPR(m_slider.GetPos());
	m_editHex.ModifyStyle(WS_HSCROLL,
		(m_slider.GetPos() > 8)? WS_HSCROLL : 0);
	m_editHex.SendMessage(WM_VSCROLL, MAKEWPARAM(HIWORD(SB_THUMBTRACK),LOWORD(0)), NULL);
	m_editHex.RedrawWindow();

	CXTPResizeDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CHexEditDlg::OnChangeBaseAddress()
{
	UpdateData(TRUE);
	CString cs;
	DWORD dwAddress;
	m_editBaseAddress.GetWindowText(cs);

	SCANF_S((LPCTSTR)cs, _T("%lx"), &dwAddress);
	m_editHex.SetAddressBase(dwAddress);
	m_editHex.RedrawWindow();
}

void CHexEditDlg::OnEnable()
{
	UpdateData();
	m_editHex.EnableWindow(m_bEnable);
}

void CHexEditDlg::OnClrBackEnabled()
{
	UpdateData();
	m_editHex.SetBackColor(m_crBackEnabled);
	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}

void CHexEditDlg::OnClrTextEnabled()
{
	UpdateData();
	m_editHex.SetTextColor(m_crTextEnabled);
	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}

void CHexEditDlg::OnClrBackHiliteEnabled()
{
	UpdateData();
	m_editHex.SetHighlightBackColor(m_crBackHiliteEnabled);
	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}

void CHexEditDlg::OnClrTextHiliteEnabled()
{
	UpdateData();
	m_editHex.SetHighlightTextColor(m_crTextHiliteEnabled);
	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}

void CHexEditDlg::OnClrBackDisabled()
{
	UpdateData();
	m_editHex.SetDisabledBackColor(m_crBackDisabled);
	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}

void CHexEditDlg::OnClrTextDisabled()
{
	UpdateData();
	m_editHex.SetDisabledTextColor(m_crTextDisabled);
	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}

void CHexEditDlg::OnClrBackHiliteDisabled()
{
	UpdateData();
	m_editHex.SetDisabledHighlightBackColor(m_crBackHiliteDisabled);
	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}

void CHexEditDlg::OnClrTextHiliteDisabled()
{
	UpdateData();
	m_editHex.SetDisabledHighlightTextColor(m_crTextHiliteDisabled);
	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}

void CHexEditDlg::OnChkCaret()
{
	UpdateData();
	m_editHex.EnableCaret(m_bCaret ? true : false);
}

void CHexEditDlg::OnChkAllowdel()
{
	UpdateData();
	m_editHex.SetAllowDeletes(m_bAllowDel == TRUE);
}

void CHexEditDlg::OnChkReadonly()
{
	UpdateData();

	m_editHex.ModifyStyle( m_bReadOnly ? 0 :ES_READONLY,
		m_bReadOnly ? ES_READONLY : 0 );

	m_editHex.Invalidate();
	m_editHex.UpdateWindow();
}
