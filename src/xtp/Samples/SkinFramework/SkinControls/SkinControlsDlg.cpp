// SkinControlsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SkinControls.h"
#include "SkinControlsDlg.h"
#include "FiltersDialog.h"
#include "DialogSample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_TOOLBAR 300
/////////////////////////////////////////////////////////////////////////////
// CSkinControlsDlg dialog

CSkinControlsDlg::CSkinControlsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkinControlsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkinControlsDlg)
	m_nHorizAlign = 0;
	m_nVertAlign = 0;
	m_bEnabled = TRUE;
	m_nVisualTheme = 4;
	m_bRightButton = FALSE;
	m_nScrollPos = 0;
	m_bMultiLine = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


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


	//XTPSkinManager()->AddColorFilter(new CXTPSkinManagerColorFilterColorize(50, 100, 1));

	XTPSkinManager()->SetApplyOptions(XTPSkinManager()->GetApplyOptions() | xtpSkinApplyMetrics);
	XTPSkinManager()->LoadSkin(m_strStylesPath + _T("Vista.cjstyles"), _T("NormalBlack2.ini"));	
}

CSkinControlsDlg::~CSkinControlsDlg()
{
}

void CSkinControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkinControlsDlg)
	DDX_Control(pDX, IDC_SLIDER_SAMPLE, m_wndSlider);
	DDX_Control(pDX, IDC_TAB_SAMPLE, m_wndTab);
	DDX_Control(pDX, IDC_PROGRESS_SAMPLE, m_wndProgress);
	DDX_Control(pDX, IDC_LISTCTRL_SAMPLE, m_wndListCtrl);
	DDX_Control(pDX, IDC_LIST_SAMPLE, m_wndListBox);
	DDX_Control(pDX, IDC_SCROLLBAR_HORZ_SAMPLE, m_wndScrollBar);
	DDX_Control(pDX, IDC_CHECK_SAMPLE, m_wndCheckBox);
	DDX_Control(pDX, IDC_RADIO_SAMPLE, m_wndRadio);
	DDX_Control(pDX, IDC_BUTTON_SAMPLE, m_wndButton);
	DDX_CBIndex(pDX, IDC_COMBO_HORIZONTAL, m_nHorizAlign);
	DDX_CBIndex(pDX, IDC_COMBO_VERTICAL, m_nVertAlign);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnabled);
	DDX_Radio(pDX, IDC_RADIO_VISUALTHEME, m_nVisualTheme);
	DDX_Check(pDX, IDC_CHECK_RIGHTBUTTON, m_bRightButton);
	DDX_Text(pDX, IDC_EDIT_SCROLLPOS, m_nScrollPos);
	DDX_Check(pDX, IDC_CHECK_MULTILINE, m_bMultiLine);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSkinControlsDlg, CDialog)
	//{{AFX_MSG_MAP(CSkinControlsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_HORIZONTAL, OnSelChangeComboHorizontal)
	ON_CBN_SELCHANGE(IDC_COMBO_VERTICAL, OnSelChangeComboVertical)
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	ON_BN_CLICKED(IDC_RADIO_VISUALTHEME, OnRadioVisualTheme)
	ON_BN_CLICKED(IDC_CHECK_RIGHTBUTTON, OnCheckRightbutton)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_MULTILINE, OnCheckMultiline)
	ON_BN_CLICKED(ID_BUTTON_FILTERS, OnFilters)
	ON_NOTIFY(TBN_DROPDOWN, IDC_TOOLBAR, OnToolbarDropDown)
	ON_BN_CLICKED(IDC_RADIO_VISUALTHEME2, OnRadioVisualTheme)
	ON_BN_CLICKED(IDC_RADIO_VISUALTHEME3, OnRadioVisualTheme)
	ON_BN_CLICKED(IDC_RADIO_VISUALTHEME4, OnRadioVisualTheme)
	ON_BN_CLICKED(IDC_RADIO_VISUALTHEME5, OnRadioVisualTheme)
	ON_BN_CLICKED(IDC_BUTTON_MULT, OnButtonMult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinControlsDlg message handlers

BOOL CSkinControlsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SCROLLINFO si;
	si.fMask = SIF_ALL;
	si.nPos = 0;
	//si.nPage = 20;
	//si.nMax = 100 + si.nPage - 1;

	si.nPage = 2;
	si.nMax = 10 + si.nPage - 1;

	si.nMin = 0;
	m_wndScrollBar.SetScrollInfo(&si);

	m_wndSlider.SetRange(0, 10);
	m_wndSlider.SetSelection(2, 5);

	int i;
	for (i = 0; i < 20; i++)
	{
		CString strItem;
		strItem.Format(_T("item %i"), i);
		m_wndListBox.AddString(strItem);
	}

	m_wndListCtrl.InsertColumn(0, _T("Items"), LVCFMT_LEFT, 100);
	
	for (i = 0; i < 20; i++) 
	{
		CString strItem;
		strItem.Format(_T("Item %i"), i);
		m_wndListCtrl.InsertItem(i, strItem);
	}

	m_wndProgress.SetPos(50);
	m_wndTab.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	TCITEM item;
	item.mask = TCIF_TEXT;
	
	item.pszText = _T("Item &1");	
	m_wndTab.InsertItem(0, &item);

	item.pszText = _T("Item &2");
	m_wndTab.InsertItem(1, &item);

	//////////////////////////////////////////////////////////////////////////
	m_ilToolbarTools.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_TOOLBAR);
	m_ilToolbarTools.Add(&bmp, 0xC0C0C0);

	TBBUTTON nButtons[] = {{1, 0, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1}, 
		{2, 12, TBSTATE_ENABLED, TBSTYLE_DROPDOWN}, {0, 0, TBSTATE_ENABLED, TBSTYLE_SEP}, {3, 13, 0, TBSTYLE_BUTTON},
		{4, 14, 0, TBSTYLE_BUTTON}, {5, 15, 0, TBSTYLE_BUTTON}, {6, 16, TBSTATE_CHECKED | TBSTATE_ENABLED, TBSTYLE_BUTTON}};

	CXTPWindowRect rc(GetDlgItem(IDC_STATIC_TOOLBAR));
	ScreenToClient(&rc);
	GetDlgItem(IDC_STATIC_TOOLBAR)->ShowWindow(SW_HIDE);

	m_wndToolBar.Create(TBSTYLE_FLAT | WS_CHILD | WS_VISIBLE | CBRS_TOOLTIPS | 
		CCS_NOPARENTALIGN | CCS_NOMOVEY | CCS_NODIVIDER | CCS_NORESIZE, rc, this, IDC_TOOLBAR);

	m_wndToolBar.SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);

	m_wndToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)m_ilToolbarTools.GetSafeHandle());
	m_wndToolBar.AddButtons(7, nButtons);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSkinControlsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSkinControlsDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSkinControlsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSkinControlsDlg::ModifyButtonsStyle(DWORD dwRemove, DWORD dwAdd)
{
	m_wndButton.ModifyStyle(dwRemove, dwAdd);
	m_wndButton.Invalidate(FALSE);

	m_wndRadio.ModifyStyle(dwRemove, dwAdd);
	m_wndRadio.Invalidate(FALSE);

	m_wndCheckBox.ModifyStyle(dwRemove, dwAdd);
	m_wndCheckBox.Invalidate(FALSE);
}

void CSkinControlsDlg::OnSelChangeComboHorizontal() 
{
	UpdateData();
	
	ModifyButtonsStyle(BS_LEFT | BS_RIGHT | BS_CENTER, 
		m_nHorizAlign == 1 ? BS_LEFT : m_nHorizAlign == 2 ? BS_CENTER : m_nHorizAlign == 3 ? BS_RIGHT : 0);
}

void CSkinControlsDlg::OnSelChangeComboVertical() 
{
	UpdateData();
	
	ModifyButtonsStyle(BS_TOP | BS_BOTTOM | BS_VCENTER, 
		m_nVertAlign == 1 ? BS_TOP : m_nVertAlign == 2 ? BS_VCENTER : m_nVertAlign == 3 ? BS_BOTTOM : 0);
}


void CSkinControlsDlg::OnCheckEnabled() 
{
	UpdateData();

	m_wndButton.EnableWindow(m_bEnabled);
	m_wndRadio.EnableWindow(m_bEnabled);
	m_wndCheckBox.EnableWindow(m_bEnabled);
}

void CSkinControlsDlg::OnCheckRightbutton() 
{
	UpdateData();

	m_wndRadio.ModifyStyle(BS_RIGHTBUTTON, m_bRightButton ? BS_RIGHTBUTTON : 0);
	m_wndRadio.Invalidate(FALSE);
	m_wndCheckBox.ModifyStyle(BS_RIGHTBUTTON,  m_bRightButton ? BS_RIGHTBUTTON : 0);	
	m_wndCheckBox.Invalidate(FALSE);

}

void CSkinControlsDlg::OnRadioVisualTheme() 
{
	UpdateData();

	switch (m_nVisualTheme)
	{	
		case 0:
			XTPSkinManager()->LoadSkin(m_strStylesPath + _T("WinXP.Luna.cjstyles"));	
			break;
		case 2:
			XTPSkinManager()->LoadSkin(m_strStylesPath + _T("WinXP.Royale.cjstyles"));	
			break;
		case 3:
			XTPSkinManager()->LoadSkin(m_strStylesPath + _T("Office2007.cjstyles"));	
			break;
		case 4:
			XTPSkinManager()->LoadSkin(m_strStylesPath + _T("Vista.cjstyles"));	
			break;

		default:
			XTPSkinManager()->LoadSkin(_T(""), _T(""));	
			break;
	}

	RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
}


void CSkinControlsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar == &m_wndScrollBar)
	{
		SCROLLINFO si;
		m_wndScrollBar.GetScrollInfo(&si, SIF_ALL);

		int nCurPos = si.nPos;
		
		// decide what to do for each diffrent scroll event
		switch (nSBCode)
		{
		case SB_TOP: nCurPos = 0; break;
		case SB_BOTTOM: nCurPos = pScrollBar->GetScrollLimit(); break;
		case SB_LINEUP: nCurPos = max(nCurPos - 1, 0); break;
		case SB_LINEDOWN: nCurPos = min(nCurPos + 1, pScrollBar->GetScrollLimit()); break;
			
		case SB_PAGEUP: nCurPos = max(nCurPos - (int)si.nPage, 0); break;
		case SB_PAGEDOWN: nCurPos = min(nCurPos + (int)si.nPage, pScrollBar->GetScrollLimit()); break;
			
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			nCurPos = nPos;
			
		/*	{
				SCROLLINFO si;
				ZeroMemory(&si, sizeof(SCROLLINFO));
				si.cbSize = sizeof(SCROLLINFO);
				si.fMask = SIF_TRACKPOS;
				
				if (!::GetScrollInfo(pScrollBar->GetSafeHwnd(), SB_CTL, &si))
					return;
				nCurPos = si.nTrackPos;
			}*/
			break;
		}
		pScrollBar->SetScrollPos(nCurPos);

		m_nScrollPos = nCurPos;
		UpdateData(FALSE);

	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSkinControlsDlg::OnCheckMultiline() 
{
	UpdateData();

	m_wndButton.SetWindowText(m_bMultiLine ? _T("Multiline\n&Sample Button") : _T("&Sample Button"));
	m_wndButton.ModifyStyle(BS_MULTILINE, m_bMultiLine ? BS_MULTILINE : 0);
	m_wndButton.Invalidate(FALSE);
}

void CSkinControlsDlg::OnFilters()
{
	CFiltersDialog fd;
	fd.DoModal();

}


void CSkinControlsDlg::OnToolbarDropDown(NMHDR* /*pNotifyStruct*/, LRESULT* /*result*/ )
{
	RECT rc;
	m_wndToolBar.GetItemRect(1, &rc);
	m_wndToolBar.ClientToScreen(&rc);

	CMenu menu;
	menu.LoadMenu(IDR_MENU_POPUP);

	TrackPopupMenu(menu.GetSubMenu(0)->GetSafeHmenu(), 0, rc.left, rc.bottom, 0, m_hWnd, 0);
}

void CSkinControlsDlg::OnButtonMult() 
{
	CDialogSample sd;
	sd.DoModal();
	
}
