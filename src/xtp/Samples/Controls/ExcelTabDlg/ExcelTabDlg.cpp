// ExcelTabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExcelTab.h"
#include "ExcelTabDlg.h"
#include "ExcelTabProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CExcelTabDlg dialog

CExcelTabDlg::CExcelTabDlg(CWnd* pParent /*=NULL*/)
: CXTPResizeDialog(CExcelTabDlg::IDD, pParent)
, m_dwTabStyle(0)
, m_bBottom(TRUE)
, m_bHasArrows(TRUE)
, m_bHasHomeEnd(FALSE)
, m_bHScroll(TRUE)
, m_pSheet7(NULL)
, m_pSheet8(NULL)
, m_pExcelTabCtrl(NULL)
{
	//{{AFX_DATA_INIT(CExcelTabDlg)
	//}}AFX_DATA_INIT

	UpdateTabsStyle();

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExcelTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExcelTabDlg)
	DDX_Control(pDX, IDC_BORDER_TAB, m_staticBorder);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExcelTabDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CExcelTabDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelTabDlg message handlers

BOOL CExcelTabDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Set control resizing.
	SetResize(IDC_BORDER_TAB, XTP_ANCHOR_TOPLEFT,     XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_PROPERTIES, XTP_ANCHOR_BOTTOMLEFT,  XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDOK,           XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDCANCEL,       XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);

	// Create  the flat tab control.
	CalcTabRect();
	CreateExcelTab();

	// Load window placement
	LoadPlacement(_T("CExcelTabDlg"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExcelTabDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExcelTabDlg::OnPaint() 
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
HCURSOR CExcelTabDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExcelTabDlg::OnDestroy() 
{
	CXTPResizeDialog::OnDestroy();
	
	// Save window placement
	SavePlacement(_T("CExcelTabDlg"));

	if (::IsWindow(m_pSheet7->GetSafeHwnd()))
		m_pSheet7->DestroyWindow();

	if (::IsWindow(m_pSheet8->GetSafeHwnd()))
		m_pSheet8->DestroyWindow();

	SAFE_DELETE(m_pExcelTabCtrl);
}

void CExcelTabDlg::UpdateTabsStyle()
{
	DWORD dwNewStyle = 0;

	if (m_bHasHomeEnd)
	{
		dwNewStyle |= FTS_XTP_HASHOMEEND;
		m_bHasArrows = TRUE;
	}

	if (m_bBottom)
		dwNewStyle |= FTS_XTP_BOTTOM;

	if (m_bHasArrows)
		dwNewStyle |= FTS_XTP_HASARROWS;

	if (m_bHScroll)
		dwNewStyle |= FTS_XTP_HSCROLL;

	dwNewStyle |= FTS_XTP_TOOLTIPS;

	if (dwNewStyle != m_dwTabStyle)
	{
		m_dwTabStyle = dwNewStyle;
	}
}

void CExcelTabDlg::CalcTabRect()
{ 
	CXTPWindowRect rcBorder(&m_staticBorder);
	ScreenToClient(&rcBorder);
	
	// get the size of the thumb box in a horizontal scroll bar.
	int cy = ::GetSystemMetrics(SM_CXHTHUMB); // SM_CYHSCROLL
	
	CRect rTabCtrl = rcBorder;
	rTabCtrl.DeflateRect(2, 2);
	
	CRect rcCtrl = rcBorder;
	rcCtrl.DeflateRect(2, 1, 2, cy + 1);
	
	// Create  the flat tab control.
	m_rTabCtrl = rTabCtrl;
}

BOOL CExcelTabDlg::CreateExcelTab()
{
	SetRedraw(FALSE);

	BOOL bResize = FALSE;

	int iSel = 0;
	CXTPEmptyRect rTab;
	RemoveResize(IDC_EXCEL_TABCTRL);

	m_pExcelTabCtrl = new CXTPExcelTabCtrl();

	// Create  the flat tab control.
	if (!m_pExcelTabCtrl->Create(WS_CHILD|WS_VISIBLE|m_dwTabStyle,
		m_rTabCtrl, this, IDC_EXCEL_TABCTRL))
	{
		TRACE0( "Failed to create flattab control\n" );
		return FALSE;
	}

	// set the tab control to have a static edge border.
	m_pExcelTabCtrl->ModifyStyleEx(NULL, WS_EX_STATICEDGE);

	if (!CreateSheet1()) return FALSE;
	if (!CreateSheet2()) return FALSE;
	if (!CreateSheet3()) return FALSE;
	if (!CreateSheet4()) return FALSE;
	if (!CreateSheet5()) return FALSE;
	if (!CreateSheet6()) return FALSE;
	if (!CreateSheet7()) return FALSE;
	if (!CreateSheet8()) return FALSE;
	
	// Insert tabs into the flat tab control.
	m_pExcelTabCtrl->InsertItem(0, _T("Build"),           &m_sheet1);
	m_pExcelTabCtrl->InsertItem(1, _T("Debug"),           &m_sheet2);
	m_pExcelTabCtrl->InsertItem(2, _T("Find in Files 1"), &m_sheet3);
	m_pExcelTabCtrl->InsertItem(3, _T("Find in Files 2"), &m_sheet4);
	m_pExcelTabCtrl->InsertItem(4, _T("Results"),         &m_sheet5);
	m_pExcelTabCtrl->InsertItem(5, _T("SQL Debugging"),   &m_sheet6);
	m_pExcelTabCtrl->InsertItem(6, _T("Form View"),       m_pSheet7);
	m_pExcelTabCtrl->InsertItem(7, _T("Scroll View"),     m_pSheet8);
	
	m_pExcelTabCtrl->SetTabBackColor(0, RGB(0x80,0x00,0x00));
	m_pExcelTabCtrl->SetTabTextColor(0, RGB(0xff,0xff,0xff));
	m_pExcelTabCtrl->SetSelTabBackColor(0, RGB(0xff,0x00,0x00));
	m_pExcelTabCtrl->SetSelTabTextColor(0, RGB(0xff,0xff,0xff));

	m_pExcelTabCtrl->SetWindowPos(&wndTop, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED);

	// enable resizing for the flat tab control.
	SetResize(IDC_EXCEL_TABCTRL, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);

	if (bResize) {
		CXTPResize::Size();
	}
	
	m_pExcelTabCtrl->SetCurSel(iSel);

	SetRedraw(TRUE);
	RedrawWindow(0,0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);

	return TRUE;
}

BOOL CExcelTabDlg::CreateSheet1()
{
	// Create the sheet1 list box.
	if (!m_sheet1.Create(WS_CHILD |
		LVS_REPORT | LVS_NOCOLUMNHEADER, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET1 ))
	{
		TRACE0( "Failed to create sheet1.\n" );
		return FALSE;
	}
	ListView_SetExtendedListViewStyleEx(m_sheet1.m_hWnd,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	m_sheet1.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet1.InsertColumn(0, _T("Column"), LVCFMT_LEFT, 512);
	m_sheet1.InsertItem(0, _T("--------------------Configuration: ExcelTabDlg - Win32 Debug--------------------"));
	m_sheet1.InsertItem(1, _T("Compiling resources..."));
	m_sheet1.InsertItem(2, _T("Compiling..."));
	m_sheet1.InsertItem(3, _T("StdAfx.cpp"));
	m_sheet1.InsertItem(5, _T("Compiling..."));
    m_sheet1.InsertItem(6, _T("ExcelEditCtrl.cpp"));
    m_sheet1.InsertItem(7, _T("ExcelFormView.cpp"));
    m_sheet1.InsertItem(8, _T("ExcelListCtrl.cpp"));
    m_sheet1.InsertItem(9, _T("ExcelScrollView.cpp"));
    m_sheet1.InsertItem(10, _T("ExcelTab.cpp"));
    m_sheet1.InsertItem(11, _T("ExcelTabDlg.cpp"));
    m_sheet1.InsertItem(12, _T("ExcelTabProperties.cpp"));
    m_sheet1.InsertItem(13, _T("ExcelTabDlg.cpp"));
    m_sheet1.InsertItem(14, _T("ExcelTabProperties.cpp"));
    m_sheet1.InsertItem(15, _T("ExcelTreeCtrl.cpp"));
    m_sheet1.InsertItem(16, _T("MainFrm.cpp"));
	m_sheet1.InsertItem(17, _T("Generating Code..."));
	m_sheet1.InsertItem(18, _T("Linking..."));
	m_sheet1.InsertItem(19, _T(""));
	m_sheet1.InsertItem(20, _T("ExcelTabDialog.exe - 0 error(s), 0 warning(s)"));

	CXTPLogFont lf;
	XTPAuxData().font.GetLogFont(&lf);
	STRCPY_S(lf.lfFaceName, LF_FACESIZE, _T("Courier New"));
	m_font.CreateFontIndirect(&lf);
	m_sheet1.SetFont(&m_font);

	return TRUE;
}

BOOL CExcelTabDlg::CreateSheet2()
{
	// Create the sheet2 list box.
	if (!m_sheet2.Create( WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN |
		WS_HSCROLL | WS_VSCROLL | ES_MULTILINE, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET2 ))
	{
		TRACE0( "Failed to create sheet2.\n" );
		return FALSE;
	}
	m_sheet2.SetFont(m_sheet1.GetFont());
	m_sheet2.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet2.SetWindowText(
		_T("Loaded 'C:\\WINNT\\System32\\ntdll.dll', no matching symbolic information found.\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MFC42D.DLL'\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MSVCRTD.DLL'\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\KERNEL32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\GDI32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\USER32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\ADVAPI32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\rpcrt4.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\SHELL32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\shlwapi.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\comctl32.dll', no matching symbolic information found.\r\n")
		_T("Loaded symbols for 'C:\\WINNT\\system32\\MFCO42D.DLL'\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\OLE32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\OLEAUT32.DLL', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\lpk.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\usp10.dll', no matching symbolic information found.\r\n")
		_T("XTTOOLKIT_DLL.DLL Initializing!\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\indicdll.dll', no matching symbolic information found.\r\n")
		_T("Loaded 'C:\\WINNT\\system32\\imm32.dll', no matching symbolic information found.\r\n")
		_T("The program 'D:\\Controls\\Bin\\ExcelTabDlg.exe' has exited with code 0 (0x0).\r\n"));
	return TRUE;
}

BOOL CExcelTabDlg::CreateSheet3()
{
	// Create the sheet3 list box.
	if (!m_sheet3.Create(
		WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | WS_VSCROLL,
		CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET3 ))
	{
		TRACE0( "Failed to create sheet3.\n" );
		return FALSE;
	}
	m_sheet3.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	HTREEITEM file;
	file = m_sheet3.InsertItem(_T("D:\\Controls\\Samples\\ExcelTabDlg\\EditCtrlForFlatTab.cpp"));
	m_sheet3.InsertItem(_T("Line 92:            pSB->Create(WS_CHILD, CRect(0, 0, 0, 0), (CWnd *)this, 0)"), 0, 0, file);
	file = m_sheet3.InsertItem(_T("D:\\Controls\\Samples\\ExcelTabDlg\\ExcelTabDlg.rc"));
	m_sheet3.InsertItem(_T("Line 190:STYLE WS_CHILD"), 0, 0, file);
	file = m_sheet3.InsertItem(_T("D:\\Controls\\Samples\\ExcelTabDlg\\ExcelTabDlg.cpp"));
	m_sheet3.InsertItem(_T("Line 92:            pSB->Create(WS_CHILD, CRect(0, 0, 0, 0), (CWnd *)this, 0)"), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 265:   if (!m_pExcelTabDlg->Create(WS_CHILD|WS_VISIBLE|m_dwTabStyle,"), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 293:   if (!m_sheet1.Create(WS_CHILD |  "), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 303:   if (!m_sheet2.Create( WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN |"), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 312:   DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;"), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 316:       WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | WS_VSCROLL, "), 0, 0, file);
	m_sheet3.InsertItem(_T("Line 348:        !((CWnd *)m_pSheet7)->Create(NULL, NULL, WS_CHILD, "), 0, 0, file);
	file = m_sheet3.InsertItem(_T("D:\\Controls\\Samples\\ExcelTabDlg\\SampleFormView.cpp"));
	m_sheet3.InsertItem(_T("Line 79:    m_ScrollBarH.Create(WS_CHILD, CRect(0, 0, 0, 0), this, 0);"), 0, 0, file);
	return TRUE;
}

BOOL CExcelTabDlg::CreateSheet4()
{
	// Define the default style for the output list boxes.
	DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;

	// Create the sheet4 list box.
	if (!m_sheet4.Create( dwStyle, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET4 ))
	{
		TRACE0( "Failed to create sheet4.\n" );
		return FALSE;
	}
	m_sheet4.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet4.SetFont(&XTPAuxData().font);
	m_sheet4.AddString(_T("Find in Files 2 Tab Output..."));
	return TRUE;
}

BOOL CExcelTabDlg::CreateSheet5()
{
	// Define the default style for the output list boxes.
	DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;

	// Create the sheet5 list box.
	if (!m_sheet5.Create( dwStyle, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET5 ))
	{
		TRACE0( "Failed to create sheet5.\n" );
		return FALSE;
	}
	m_sheet5.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet5.SetFont(&XTPAuxData().font);
	m_sheet5.AddString(_T("Results Tab Output..."));
	return TRUE;
}

BOOL CExcelTabDlg::CreateSheet6()
{
	// Define the default style for the output list boxes.
	DWORD dwStyle = WS_CHILD | LBS_NOINTEGRALHEIGHT | WS_TABSTOP | WS_VSCROLL;

	// Create the sheet6 list box.
	if (!m_sheet6.Create( dwStyle, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET6 ))
	{
		TRACE0( "Failed to create sheet6.\n" );
		return FALSE;
	}
	m_sheet6.SetBackColor(GetXtremeColor(COLOR_WINDOW));
	m_sheet6.SetFont(&XTPAuxData().font);
	m_sheet6.AddString(_T("SQL Debugging Tab Output..."));
	return TRUE;
}

BOOL CExcelTabDlg::CreateSheet7()
{
	// views must be created dynamically because they are destroyed during
	// window destruction
	CCreateContext cc;
	::ZeroMemory(&cc, sizeof(cc));
	cc.m_pCurrentDoc = NULL;

	m_pSheet7 = (CExcelFormView*)RUNTIME_CLASS(CExcelFormView)->CreateObject();
	if (!m_pSheet7  || !((CWnd *)m_pSheet7)->Create(
		NULL, NULL, WS_CHILD, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET7, &cc))
	{
		TRACE0( "Failed to create sheet7.\n" );
		return FALSE;
	}
	return TRUE;
}

BOOL CExcelTabDlg::CreateSheet8()
{
	// Create the Test Scroll View
	CCreateContext cc;
	::ZeroMemory(&cc, sizeof(cc));
	cc.m_pCurrentDoc = NULL;

	m_pSheet8 = (CExcelScrollView*)RUNTIME_CLASS(CExcelScrollView)->CreateObject();
	if (!m_pSheet8  || !((CWnd *)m_pSheet8)->Create( NULL, NULL, WS_CHILD |
		WS_VSCROLL|WS_HSCROLL, CXTPEmptyRect(), m_pExcelTabCtrl, IDC_SHEET8, &cc))
	{
		TRACE0( "Failed to create m_pSheet8.\n" );
		return FALSE;
	}
	return TRUE;
}

void CExcelTabDlg::OnProperties() 
{
	CExcelTabProperties dlg(m_bBottom, m_bHasArrows, m_bHasHomeEnd, m_bHScroll, this);
	if (dlg.DoModal() == IDOK)
	{
	}	
}

void CExcelTabDlg::UpdateExcelTab()
{
	UpdateTabsStyle();
	m_pExcelTabCtrl->SetTabStyle(m_dwTabStyle);
}

BOOL CExcelTabDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (IDC_EXCEL_TABCTRL == (UINT)wParam)
	{
		NMHDR* pNMHDR = (NMHDR*)lParam;

		switch(pNMHDR->code)
		{
		case TCN_SELCHANGING:
			break;

		case TCN_SELCHANGE:
			// For unmanaged views, you can use something like this:
//          SelectTabView(m_pFlatTabCtrl->GetCurSel());
			break;
		}
	}

	return CXTPResizeDialog::OnNotify(wParam, lParam, pResult);
}
