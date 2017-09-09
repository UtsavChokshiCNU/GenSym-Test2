// ListCtrlDlg.cpp : implementation file
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
#include "ListCtrl.h"
#include "ListCtrlDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BoolType(b) b?true:false

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg dialog

CListCtrlDlg::CListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CListCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListCtrlDlg)
	m_iTheme = 1;
	m_iDisableSizing = 0;
	m_iMinSize = 25;
	m_bBoldText  = FALSE;
	m_bSortArrow = TRUE;
	m_bAutoSize = TRUE;
	m_bContextMenus = TRUE;
	m_bHotTracking = TRUE;
	m_bHeaderImages = TRUE;
	m_bWinTheme = FALSE;
	m_bDisableSizing = FALSE;
	m_bMinSize = FALSE;
	m_bSortColor = TRUE;
	m_bFullRowSel = TRUE;
	m_bGridLines = FALSE;
	m_bCheckBoxes = FALSE;
	m_bDragDrop = FALSE;
	m_bListColor = TRUE;
	m_bRowColor = TRUE;
	m_bEnableList = TRUE;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nSortedCol = 1;
	m_bAscending = true;

	CXTPWinThemeWrapper themeWrapper;
	m_bWinTheme  = themeWrapper.IsThemeActive();
}

void CListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCtrlDlg)
	DDX_CBIndex(pDX, IDC_COMBO_THEMES, m_iTheme);
	DDX_CBIndex(pDX, IDC_COMBO_DISABLESIZE, m_iDisableSizing);
	DDX_Text(pDX, IDC_EDIT_MINSIZE, m_iMinSize);
	DDX_Check(pDX, IDC_CHK_BOLDTEXT, m_bBoldText);
	DDX_Check(pDX, IDC_CHK_SORTARW, m_bSortArrow);
	DDX_Check(pDX, IDC_CHK_AUTOSIZE, m_bAutoSize);
	DDX_Check(pDX, IDC_CHK_CONTEXTMENUS, m_bContextMenus);
	DDX_Check(pDX, IDC_CHK_HOTTRACKING, m_bHotTracking);
	DDX_Check(pDX, IDC_CHK_IMAGES, m_bHeaderImages);
	DDX_Check(pDX, IDC_CHK_WINTHEME, m_bWinTheme);
	DDX_Check(pDX, IDC_CHK_DISABLESIZING, m_bDisableSizing);
	DDX_Check(pDX, IDC_CHK_MINIMUMSIZE, m_bMinSize);
	DDX_Check(pDX, IDC_CHK_SORTCOLOR, m_bSortColor);
	DDX_Control(pDX, IDC_EDIT_MINSIZE, m_editMinSize);
	DDX_Control(pDX, IDC_CHK_WINTHEME, m_btnWinTheme);
	DDX_Control(pDX, IDC_CHK_HOTTRACKING, m_btnHotTracking);
	DDX_Control(pDX, IDC_COMBO_THEMES, m_comboThemes);
	DDX_Control(pDX, IDC_COMBO_DISABLESIZE, m_comboDisableSize);
	DDX_Check(pDX, IDC_CHK_FULLROWSELECT, m_bFullRowSel);
	DDX_Check(pDX, IDC_CHK_GRIDLINES, m_bGridLines);
	DDX_Check(pDX, IDC_CHK_CHECKBOXES, m_bCheckBoxes);
	DDX_Check(pDX, IDC_CHK_DRAGDROP, m_bDragDrop);
	DDX_Check(pDX, IDC_CHK_LISTCOLOR, m_bListColor);
	DDX_Check(pDX, IDC_CHK_ROWCOLOR, m_bRowColor);
	DDX_Control(pDX, IDC_LIST_CTRL, m_listCtrl);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnableList);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_GBOX_LIST, m_gboxList);
	DDX_Control(pDX, IDC_GBOX_HEADER, m_gboxHeader);
	DDX_Control(pDX, IDC_CLR_SORTBACK, m_cpSortBack);
	DDX_Control(pDX, IDC_CLR_SORTTEXT, m_cpSortText);
	DDX_Control(pDX, IDC_CLR_LISTBACK, m_cpListBack);
	DDX_Control(pDX, IDC_CLR_LISTTEXT, m_cpListText);
	DDX_Control(pDX, IDC_CLR_ROWBACK, m_cpRowBack);
	DDX_Control(pDX, IDC_CLR_ROWTEXT, m_cpRowText);
	DDX_XTPColorPicker(pDX, IDC_CLR_SORTBACK, m_crSortBack);
	DDX_XTPColorPicker(pDX, IDC_CLR_SORTTEXT, m_crSortText);
	DDX_XTPColorPicker(pDX, IDC_CLR_LISTBACK, m_crListBack);
	DDX_XTPColorPicker(pDX, IDC_CLR_LISTTEXT, m_crListText);
	DDX_XTPColorPicker(pDX, IDC_CLR_ROWBACK, m_crRowBack);
	DDX_XTPColorPicker(pDX, IDC_CLR_ROWTEXT, m_crRowText);
}

BEGIN_MESSAGE_MAP(CListCtrlDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CListCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHK_BOLDTEXT, OnChkBoldtext)
	ON_BN_CLICKED(IDC_CHK_SORTARW, OnChkSortarw)
	ON_WM_DESTROY()
	ON_CBN_SELENDOK(IDC_COMBO_THEMES, OnSelendokComboThemes)
	ON_CBN_SELENDOK(IDC_COMBO_DISABLESIZE, OnSelendokComboDisablesize)
	ON_BN_CLICKED(IDC_CHK_WINTHEME, OnChkWintheme)
	ON_BN_CLICKED(IDC_CHK_HOTTRACKING, OnChkHottracking)
	ON_BN_CLICKED(IDC_CHK_IMAGES, OnChkImages)
	ON_BN_CLICKED(IDC_CHK_AUTOSIZE, OnChkAutosize)
	ON_BN_CLICKED(IDC_CHK_CONTEXTMENUS, OnChkContextmenus)
	ON_EN_CHANGE(IDC_EDIT_MINSIZE, OnChangeEditMinsize)
	ON_BN_CLICKED(IDC_CHK_DISABLESIZING, OnChkDisablesizing)
	ON_BN_CLICKED(IDC_CHK_MINIMUMSIZE, OnChkMinimumsize)
	ON_BN_CLICKED(IDC_CHK_SORTCOLOR, OnChkSortcolor)
	ON_BN_CLICKED(IDC_CHK_FULLROWSELECT, OnChkFullRowSelect)
	ON_BN_CLICKED(IDC_CHK_GRIDLINES, OnChkGridLines)
	ON_BN_CLICKED(IDC_CHK_CHECKBOXES, OnChkCheckBoxes)
	ON_BN_CLICKED(IDC_CHK_DRAGDROP, OnChkHeaderDragDrop)
	ON_BN_CLICKED(IDC_CHK_LISTCOLOR, OnChkListcolor)
	ON_BN_CLICKED(IDC_CHK_ROWCOLOR, OnChkRowcolor)
	ON_BN_CLICKED(IDC_BTN_SIZETOFIT, OnBtnSizeToFit)
	ON_BN_CLICKED(IDC_CHK_ENABLE, OnChkEnable)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	//}}AFX_MSG_MAP
	ON_CPN_XTP_SELENDOK(IDC_CLR_SORTBACK, OnSelEndOkSortBackColor)
	ON_CPN_XTP_SELENDOK(IDC_CLR_SORTTEXT, OnSelEndOkSortTextColor)
	ON_CPN_XTP_SELENDOK(IDC_CLR_LISTBACK, OnSelEndOkListBackColor)
	ON_CPN_XTP_SELENDOK(IDC_CLR_LISTTEXT, OnSelEndOkListTextColor)
	ON_CPN_XTP_SELENDOK(IDC_CLR_ROWBACK, OnSelEndOkRowBackColor)
	ON_CPN_XTP_SELENDOK(IDC_CLR_ROWTEXT, OnSelEndOkRowTextColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDlg message handlers

BOOL CListCtrlDlg::OnInitDialog()
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
	SetResize(IDOK,                  XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDCANCEL,              XTP_ANCHOR_TOPRIGHT,   XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_LIST_CTRL,         XTP_ANCHOR_TOPLEFT,    XTP_ANCHOR_BOTTOMRIGHT);

	SetResize(IDC_GBOX_HEADER,       XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_COMBO_THEMES,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_AUTOSIZE,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BTN_SIZETOFIT,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_DISABLESIZING, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_COMBO_DISABLESIZE, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_MINIMUMSIZE,   XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_EDIT_MINSIZE,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_WINTHEME,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_HOTTRACKING,   XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_IMAGES,        XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_BOLDTEXT,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_SORTARW,       XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_CONTEXTMENUS,  XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);

	SetResize(IDC_GBOX_LIST,         XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_CHK_LISTCOLOR,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_LISTBACK,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_LISTTEXT,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_ROWCOLOR,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_ROWBACK,       XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_ROWTEXT,       XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_SORTCOLOR,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_SORTBACK,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CLR_SORTTEXT,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_FULLROWSELECT, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_GRIDLINES,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_CHECKBOXES,    XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_DRAGDROP,      XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHK_ENABLE,        XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);

	SetResize(IDC_BTN_UPDATE,        XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BTN_RESET,         XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	
	// Load window placement
	LoadPlacement(_T("CListCtrlDlg"));

	// TODO: Add extra initialization here
	m_listCtrl.InsertColumn(0, _T("Column One"),   LVCFMT_LEFT, 125);
	m_listCtrl.InsertColumn(1, _T("Column Two"),   LVCFMT_LEFT, 125);
	m_listCtrl.InsertColumn(2, _T("Column Three"), LVCFMT_LEFT, 125);

	int iItem;
	for (iItem = 0; iItem < 100; ++iItem)
	{
		CString strItem;
		CString strSubA;
		CString strSubB;

		strItem.Format(_T("Item %d"), iItem);
		strSubA.Format(_T("Sub A %d"), iItem);
		strSubB.Format(_T("Sub B %d"), iItem);

		m_listCtrl.InsertItem(iItem, strItem, 0);
		m_listCtrl.SetItem(iItem, 1, LVIF_TEXT, strSubA, 0, NULL, NULL, NULL);
		m_listCtrl.SetItem(iItem, 2, LVIF_TEXT, strSubB, 0, NULL, NULL, NULL);
	}

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_listCtrl.GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);

	// add bitmap images.
	m_header.SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
	m_header.SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
	m_header.SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));

	// enable auto sizing.
	m_header.EnableAutoSize(TRUE);
	m_header.ResizeColumnsToFit();
	SortColumn(m_nSortedCol, m_bAscending);

	m_cpSortBack.ShowText(TRUE);
	m_cpSortBack.SetColor(m_listCtrl.GetSortBackColor());
	m_cpSortBack.SetDefaultColor(m_listCtrl.GetSortBackColor());

	m_cpSortText.ShowText(TRUE);
	m_cpSortText.SetColor(m_listCtrl.GetSortTextColor());
	m_cpSortText.SetDefaultColor(m_listCtrl.GetSortTextColor());

	m_cpListBack.ShowText(TRUE);
	m_cpListBack.SetColor(m_listCtrl.GetListBackColor());
	m_cpListBack.SetDefaultColor(m_listCtrl.GetListBackColor());

	m_cpListText.ShowText(TRUE);
	m_cpListText.SetColor(m_listCtrl.GetListTextColor());
	m_cpListText.SetDefaultColor(m_listCtrl.GetListTextColor());

	m_cpRowBack.ShowText(TRUE);
	m_cpRowText.SetColor(m_listCtrl.GetListTextColor());
	m_cpRowBack.SetDefaultColor(m_listCtrl.GetListBackColor());

	m_cpRowText.ShowText(TRUE);
	m_cpRowBack.SetColor(m_listCtrl.GetListBackColor());
	m_cpRowText.SetDefaultColor(m_listCtrl.GetListTextColor());

	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_EX_FULLROWSELECT);
	m_listCtrl.EnableUserSortColor(BoolType(m_bSortColor));
	m_listCtrl.EnableUserListColor(BoolType(m_bListColor));
	m_listCtrl.EnableUserRowColor(BoolType(m_bRowColor));

	OnSelendokComboThemes();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListCtrlDlg::OnDestroy()
{
	// Save window placement
	SavePlacement(_T("CListCtrlDlg"));

	CXTPResizeDialog::OnDestroy();
}

void CListCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListCtrlDlg::OnPaint()
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
HCURSOR CListCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CListCtrlDlg::SortColumn(int iCol, bool bAsc)
{
	m_bAscending = bAsc;
	m_nSortedCol = iCol;

	// set sort image for header and sort column.
	m_listCtrl.SetSortImage(m_nSortedCol, m_bAscending);

	CXTPSortClass csc(&m_listCtrl, m_nSortedCol);
	csc.Sort(m_bAscending, xtpSortString);
}

BOOL CListCtrlDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;

	if (pHDNotify->hdr.code == HDN_ITEMCLICKA ||
		pHDNotify->hdr.code == HDN_ITEMCLICKW)
	{
		if (pHDNotify->iItem == m_nSortedCol)
			SortColumn(pHDNotify->iItem, !m_bAscending);
		else
			SortColumn(pHDNotify->iItem, BoolType(m_header.GetAscending()));
	}

	return CXTPResizeDialog::OnNotify(wParam, lParam, pResult);
}

void CListCtrlDlg::OnSelendokComboThemes()
{
	UpdateData();

	switch (m_iTheme)
	{
	case 0:
		m_bHotTracking = FALSE;
		m_bWinTheme = FALSE;
		m_header.SetTheme(new CXTPHeaderCtrlThemeOfficeXP());
		CXTPPaintManager::SetTheme(xtpThemeOfficeXP);
		break;
	case 1:
		m_bHotTracking = FALSE;
		m_bWinTheme = FALSE;
		m_header.SetTheme(new CXTPHeaderCtrlThemeOffice2003());
		CXTPPaintManager::SetTheme(xtpThemeOffice2003);
		break;
	case 2:
		m_bHotTracking = TRUE;
		m_bWinTheme = TRUE;
		m_header.SetTheme(new CXTPHeaderCtrlThemeExplorer());
		CXTPPaintManager::SetTheme(xtpThemeOffice2000);
		break;
	case 3:
		m_bHotTracking = TRUE;
		m_bWinTheme = TRUE;
		m_header.SetTheme(new CXTPHeaderCtrlTheme());
		CXTPPaintManager::SetTheme(xtpThemeOffice2000);
		break;
	}

	UpdateData(FALSE);

	DWORD dwStyle = 0L;
	if (m_bWinTheme && m_iTheme >= 2)
		dwStyle |= HDR_XTP_WINDEF;

	if (m_bWinTheme && m_iTheme >= 2 && m_bHotTracking)
		dwStyle |= HDR_XTP_HOTTRACKING;

	if (m_bSortArrow)
		dwStyle |= HDR_XTP_SORTARROW;

	CXTPHeaderCtrlTheme* pTheme = m_header.GetTheme();
	if (pTheme)
	{
		pTheme->SetDrawStyle(dwStyle, &m_header);
		EnableControls();
	}
}

void CListCtrlDlg::OnSelendokComboDisablesize()
{
	UpdateData();

	// thaw all columns.
	m_header.ThawAllColumns();

	if (m_iDisableSizing > 0)
		m_header.FreezeColumn(m_iDisableSizing-1);
}

void CListCtrlDlg::ModifyDrawStyle(UINT uFlag, BOOL bRemove)
{
	CXTPHeaderCtrlTheme* pTheme = m_header.GetTheme();
	if (pTheme)
	{
		DWORD dwStyle = pTheme->GetDrawStyle() & ~uFlag;

		if (bRemove)
			dwStyle |= uFlag;

		pTheme->SetDrawStyle(dwStyle, &m_header);
		m_header.RedrawWindow();
	}
}

void CListCtrlDlg::OnChkWintheme()
{
	UpdateData();
	EnableControls(FALSE);
	ModifyDrawStyle(HDR_XTP_WINDEF, m_bWinTheme);
}

void CListCtrlDlg::OnChkHottracking()
{
	UpdateData();
	ModifyDrawStyle(HDR_XTP_HOTTRACKING, m_bHotTracking);
}

void CListCtrlDlg::OnChkImages()
{
	UpdateData();

	// add / remove bitmap images.
	m_header.SetBitmap(0, IDB_COLUMN_0, !m_bHeaderImages, RGB(0,255,0));
	m_header.SetBitmap(1, IDB_COLUMN_1, !m_bHeaderImages, RGB(0,255,0));
	m_header.SetBitmap(2, IDB_COLUMN_2, !m_bHeaderImages, RGB(0,255,0));
}

void CListCtrlDlg::OnChkBoldtext()
{
	UpdateData();
	m_header.InitializeHeader(BoolType(m_bBoldText));
	m_header.RedrawWindow();
}

void CListCtrlDlg::OnChkSortarw()
{
	UpdateData();
	ModifyDrawStyle(HDR_XTP_SORTARROW, m_bSortArrow);
}

void CListCtrlDlg::OnChkContextmenus()
{
	UpdateData();
	m_header.EnablePopupMenus(m_bContextMenus);
}

void CListCtrlDlg::OnChangeEditMinsize()
{
	UpdateData();
	m_header.SetMinSize(m_iMinSize);
}

void CListCtrlDlg::EnableControls(BOOL bRedraw/*=TRUE*/)
{
	m_editMinSize.EnableWindow(m_bMinSize);
	m_comboDisableSize.EnableWindow(m_bDisableSizing);
	m_btnWinTheme.EnableWindow(XTPSystemVersion()->IsWinXPOrGreater());
	m_btnHotTracking.EnableWindow(XTPSystemVersion()->IsWinXPOrGreater() && m_bWinTheme);
	m_cpSortBack.EnableWindow(m_bSortColor);
	m_cpSortText.EnableWindow(m_bSortColor);
	m_cpRowBack.EnableWindow(m_bRowColor);
	m_cpRowText.EnableWindow(m_bRowColor);
	m_cpListBack.EnableWindow(m_bListColor);
	m_cpListText.EnableWindow(m_bListColor);

	if (bRedraw)
	{
		RedrawWindow(NULL, NULL,
			RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
	}
}

void CListCtrlDlg::OnChkAutosize()
{
	UpdateData();
	EnableControls(FALSE);

	// enable auto sizing.
	m_header.EnableAutoSize(BoolType(m_bAutoSize));

	if (m_bAutoSize)
		m_header.ResizeColumnsToFit();
}

void CListCtrlDlg::OnChkDisablesizing()
{
	UpdateData();
	EnableControls(FALSE);

	if (!m_bDisableSizing)
	{
		m_iDisableSizing = 0;
		m_header.ThawAllColumns();
		UpdateData(FALSE);
	}
}

void CListCtrlDlg::OnChkMinimumsize()
{
	UpdateData();
	EnableControls(FALSE);

	// enable minimum sizing.
	m_iMinSize = 25;
	m_header.SetMinSize(m_iMinSize);
	UpdateData(FALSE);
}

void CListCtrlDlg::OnChkSortcolor()
{
	UpdateData();
	EnableControls(FALSE);

	m_listCtrl.EnableUserSortColor(BoolType(m_bSortColor));
	m_listCtrl.RedrawWindow();
}

void CListCtrlDlg::OnSelEndOkSortBackColor()
{
	UpdateData();
}

void CListCtrlDlg::OnSelEndOkSortTextColor()
{
	UpdateData();
}

void CListCtrlDlg::OnChkListcolor()
{
	UpdateData();
	EnableControls(FALSE);

	m_listCtrl.EnableUserListColor(BoolType(m_bListColor));
	m_listCtrl.RedrawWindow();
}

void CListCtrlDlg::OnSelEndOkListBackColor()
{
	UpdateData();
}

void CListCtrlDlg::OnSelEndOkListTextColor()
{
	UpdateData();
}

void CListCtrlDlg::OnChkRowcolor()
{
	UpdateData();
	EnableControls(FALSE);

	m_listCtrl.EnableUserRowColor(BoolType(m_bRowColor));
	m_listCtrl.RedrawWindow();
}

void CListCtrlDlg::OnSelEndOkRowBackColor()
{
	UpdateData();
}

void CListCtrlDlg::OnSelEndOkRowTextColor()
{
	UpdateData();
}

void CListCtrlDlg::OnChkFullRowSelect()
{
	UpdateData();

	m_listCtrl.ModifyExtendedStyle( m_bFullRowSel ? 0 : LVS_EX_FULLROWSELECT,
		m_bFullRowSel ? LVS_EX_FULLROWSELECT : 0 );
}

void CListCtrlDlg::OnChkGridLines()
{
	UpdateData();

	m_listCtrl.ModifyExtendedStyle( m_bGridLines ? 0 : LVS_EX_GRIDLINES,
		m_bGridLines ? LVS_EX_GRIDLINES : 0 );
}

void CListCtrlDlg::OnChkCheckBoxes()
{
	UpdateData();

	m_listCtrl.ModifyExtendedStyle( m_bCheckBoxes ? 0 : LVS_EX_CHECKBOXES,
		m_bCheckBoxes ? LVS_EX_CHECKBOXES : 0 );
}

void CListCtrlDlg::OnChkHeaderDragDrop()
{
	UpdateData();

	m_listCtrl.ModifyExtendedStyle( m_bDragDrop ? 0 : LVS_EX_HEADERDRAGDROP,
		m_bDragDrop ? LVS_EX_HEADERDRAGDROP : 0 );
}

void CListCtrlDlg::OnBtnSizeToFit()
{
	m_header.ResizeColumnsToFit();
}

void CListCtrlDlg::OnChkEnable()
{
	UpdateData();
	m_listCtrl.EnableWindow(m_bEnableList);
}

void CListCtrlDlg::ClearSelection()
{
	for (int iItem = 0; iItem < m_listCtrl.GetItemCount(); ++iItem)
	{
		m_listCtrl.SetItemState(iItem, 0, LVIS_SELECTED);
	}
}

void CListCtrlDlg::OnBtnUpdate()
{
	if (m_bListColor)
	{
		m_listCtrl.SetListTextColor(m_crListText);
		m_listCtrl.SetListBackColor(m_crListBack);
	}

	if (m_bRowColor)
	{
		for (POSITION pos = m_listCtrl.GetFirstSelectedItemPosition(); pos;)
		{
			int iItem = m_listCtrl.GetNextSelectedItem(pos);
			m_listCtrl.SetRowColor(iItem, m_crRowText, m_crRowBack);
		}

		ClearSelection();
	}

	if (m_bSortColor)
	{
		m_listCtrl.SetSortBackColor(m_cpSortBack.GetColor());
		m_listCtrl.SetSortTextColor(m_cpSortText.GetColor());
	}

	m_listCtrl.RedrawWindow();
}

void CListCtrlDlg::OnBtnReset()
{
	COLORREF crSortBack(GetXtremeColor(COLOR_WINDOW));
	crSortBack = RGB(max(0, GetRValue(crSortBack) - 8), max(0, GetGValue(crSortBack) - 8), max(0, GetBValue(crSortBack) - 8));

	m_crRowText  = GetXtremeColor(COLOR_WINDOWTEXT);
	m_crListText = GetXtremeColor(COLOR_WINDOWTEXT);
	m_crSortText = GetXtremeColor(COLOR_WINDOWTEXT);
	m_crRowBack  = GetXtremeColor(COLOR_WINDOW);
	m_crListBack = GetXtremeColor(COLOR_WINDOW);
	m_crSortBack = crSortBack;

	m_listCtrl.SetListTextColor(m_crListText);
	m_listCtrl.SetListBackColor(m_crListBack);
	m_listCtrl.SetSortTextColor(m_crSortText);
	m_listCtrl.SetSortBackColor(m_crSortBack);
	m_listCtrl.RemoveRowColors();

	UpdateData(FALSE);
	m_listCtrl.RedrawWindow();
}
