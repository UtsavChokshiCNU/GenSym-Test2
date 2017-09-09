// MarqueeProgressDlg.cpp : implementation file
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
#include "MarqueeProgress.h"
#include "MarqueeProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarqueeProgressDlg dialog

CMarqueeProgressDlg::CMarqueeProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMarqueeProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMarqueeProgressDlg)
	m_bMarquee = TRUE;
	m_nAlpha1 = 25;
	m_nAlpha2 = 50;
	m_nAlpha3 = 75;
	m_nAlpha4 = 100;
	m_nAlpha5 = 100;
	m_cxChunk = 12;
	m_nGap = 2;
	m_nInterval = 50;
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMarqueeProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarqueeProgressDlg)
	DDX_Control(pDX, IDC_STATIC_TRANSPARENCY, m_staticTransparency);
	DDX_Control(pDX, IDC_STATIC_SETTINGS, m_staticSettings);
	DDX_Control(pDX, IDC_STATIC_INTERVAL, m_staticInterval);
	DDX_Control(pDX, IDC_STATIC_GAP, m_staticGap);
	DDX_Control(pDX, IDC_STATIC_CX, m_staticCX);
	DDX_Control(pDX, IDC_STATIC_CHUNK5, m_staticChunk5);
	DDX_Control(pDX, IDC_STATIC_CHUNK4, m_staticChunk4);
	DDX_Control(pDX, IDC_STATIC_CHUNK3, m_staticChunk3);
	DDX_Control(pDX, IDC_STATIC_CHUNK2, m_staticChunk2);
	DDX_Control(pDX, IDC_STATIC_CHUNK1, m_staticChunk1);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_editInterval);
	DDX_Control(pDX, IDC_EDIT_GAP, m_editGap);
	DDX_Control(pDX, IDC_EDIT_CX, m_editCX);
	DDX_Control(pDX, IDC_EDIT_CHUNK5, m_editChunk5);
	DDX_Control(pDX, IDC_EDIT_CHUNK4, m_editChunk4);
	DDX_Control(pDX, IDC_EDIT_CHUNK3, m_editChunk3);
	DDX_Control(pDX, IDC_EDIT_CHUNK2, m_editChunk2);
	DDX_Control(pDX, IDC_EDIT_CHUNK1, m_editChunk1);
	DDX_Control(pDX, IDC_SPIN_INTERVAL, m_spinInterval);
	DDX_Control(pDX, IDC_SPIN_GAP, m_spinGap);
	DDX_Control(pDX, IDC_SPIN_CX, m_spinCX);
	DDX_Control(pDX, IDC_SPIN_CHUNK5, m_spinChunk5);
	DDX_Control(pDX, IDC_SPIN_CHUNK4, m_spinChunk4);
	DDX_Control(pDX, IDC_SPIN_CHUNK3, m_spinChunk3);
	DDX_Control(pDX, IDC_SPIN_CHUNK2, m_spinChunk2);
	DDX_Control(pDX, IDC_SPIN_CHUNK1, m_spinChunk1);
	DDX_Control(pDX, IDC_PROG_VERT, m_wndProgVert);
	DDX_Control(pDX, IDC_PROG_HORZ, m_wndProgHorz);
	DDX_Check(pDX, IDC_CHK_MARQUEE, m_bMarquee);
	DDX_Text(pDX, IDC_EDIT_CHUNK1, m_nAlpha1);
	DDX_Text(pDX, IDC_EDIT_CHUNK2, m_nAlpha2);
	DDX_Text(pDX, IDC_EDIT_CHUNK3, m_nAlpha3);
	DDX_Text(pDX, IDC_EDIT_CHUNK4, m_nAlpha4);
	DDX_Text(pDX, IDC_EDIT_CHUNK5, m_nAlpha5);
	DDX_Text(pDX, IDC_EDIT_CX, m_cxChunk);
	DDX_Text(pDX, IDC_EDIT_GAP, m_nGap);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_nInterval);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMarqueeProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CMarqueeProgressDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_INTERVAL, OnChangeEditInterval)
	ON_EN_CHANGE(IDC_EDIT_GAP, OnChangeEditGap)
	ON_EN_CHANGE(IDC_EDIT_CX, OnChangeEditCx)
	ON_EN_CHANGE(IDC_EDIT_CHUNK1, OnChangeEditChunk1)
	ON_EN_CHANGE(IDC_EDIT_CHUNK2, OnChangeEditChunk2)
	ON_EN_CHANGE(IDC_EDIT_CHUNK3, OnChangeEditChunk3)
	ON_EN_CHANGE(IDC_EDIT_CHUNK4, OnChangeEditChunk4)
	ON_EN_CHANGE(IDC_EDIT_CHUNK5, OnChangeEditChunk5)
	ON_BN_CLICKED(IDC_CHK_MARQUEE, OnChkMarqueeStyle)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarqueeProgressDlg message handlers

BOOL CMarqueeProgressDlg::OnInitDialog()
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
	
	// set progress bar values.
	m_wndProgVert.SetRange(0, 100);
	m_wndProgVert.SetStep(1);
	m_wndProgVert.SetPos(0);

	// set progress bar values.
	m_wndProgHorz.SetRange(0, 100);
	m_wndProgHorz.SetStep(1);
	m_wndProgHorz.SetPos(0);

	// set spin control range.
	m_spinInterval.SetRange(5,500);
	m_spinGap.SetRange(0,5);
	m_spinCX.SetRange(1,25);
	m_spinChunk5.SetRange(0,100);
	m_spinChunk4.SetRange(0,100);
	m_spinChunk3.SetRange(0,100);
	m_spinChunk2.SetRange(0,100);
	m_spinChunk1.SetRange(0,100);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMarqueeProgressDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMarqueeProgressDlg::OnPaint() 
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
HCURSOR CMarqueeProgressDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMarqueeProgressDlg::ValidateRange(CEdit& wndEdit, int nLower, int nUpper)
{
	if (::IsWindow(wndEdit.m_hWnd))
	{
		CString strEdit;
		wndEdit.GetWindowText(strEdit);
		
		if (!strEdit.IsEmpty())
		{
			int nValue = _ttoi(strEdit);
			
			if (nValue > nUpper)
			{
				strEdit.Format(_T("%d"), nUpper);
				wndEdit.SetWindowText(strEdit);
			}
			
			if (nValue < nLower)
			{
				strEdit.Format(_T("%d"), nLower);
				wndEdit.SetWindowText(strEdit);
			}
		}
	}
}

void CMarqueeProgressDlg::OnChangeEditInterval() 
{
	ValidateRange(m_editInterval, 1, 500);
}

void CMarqueeProgressDlg::OnChangeEditGap() 
{
	ValidateRange(m_editGap, 0, 5);
}

void CMarqueeProgressDlg::OnChangeEditCx() 
{
	ValidateRange(m_editCX, 1, 25);
}

void CMarqueeProgressDlg::OnChangeEditChunk1() 
{
	ValidateRange(m_editChunk1, 0, 100);
}

void CMarqueeProgressDlg::OnChangeEditChunk2() 
{
	ValidateRange(m_editChunk2, 0, 100);
}

void CMarqueeProgressDlg::OnChangeEditChunk3() 
{
	ValidateRange(m_editChunk3, 0, 100);
}

void CMarqueeProgressDlg::OnChangeEditChunk4() 
{
	ValidateRange(m_editChunk4, 0, 100);
}

void CMarqueeProgressDlg::OnChangeEditChunk5() 
{
	ValidateRange(m_editChunk5, 0, 100);
}

void CMarqueeProgressDlg::EnableWindows()
{
	m_editInterval.EnableWindow(m_bMarquee);
	m_editGap.EnableWindow(m_bMarquee);
	m_editCX.EnableWindow(m_bMarquee);
	m_editChunk1.EnableWindow(m_bMarquee);
	m_editChunk2.EnableWindow(m_bMarquee);
	m_editChunk3.EnableWindow(m_bMarquee);
	m_editChunk4.EnableWindow(m_bMarquee);
	m_editChunk5.EnableWindow(m_bMarquee);

	m_spinInterval.EnableWindow(m_bMarquee);
	m_spinGap.EnableWindow(m_bMarquee);
	m_spinCX.EnableWindow(m_bMarquee);
	m_spinChunk1.EnableWindow(m_bMarquee);
	m_spinChunk2.EnableWindow(m_bMarquee);
	m_spinChunk3.EnableWindow(m_bMarquee);
	m_spinChunk4.EnableWindow(m_bMarquee);
	m_spinChunk5.EnableWindow(m_bMarquee);
	
	m_staticInterval.EnableWindow(m_bMarquee);
	m_staticGap.EnableWindow(m_bMarquee);
	m_staticCX.EnableWindow(m_bMarquee);
	m_staticChunk1.EnableWindow(m_bMarquee);
	m_staticChunk2.EnableWindow(m_bMarquee);
	m_staticChunk3.EnableWindow(m_bMarquee);
	m_staticChunk4.EnableWindow(m_bMarquee);
	m_staticChunk5.EnableWindow(m_bMarquee);
}

void CMarqueeProgressDlg::OnBtnUpdate() 
{
	OnChkMarqueeStyle();

	if (!m_bMarquee)
	{
		m_wndProgHorz.SetPos(0);
		m_wndProgVert.SetPos(0);
		
		for (int i = 0; i < 100; ++i)
		{
			m_wndProgHorz.StepIt();
			m_wndProgVert.StepIt();
			
			Sleep(20);
		}
	}
}

void CMarqueeProgressDlg::OnChkMarqueeStyle() 
{
	UpdateData();

	int piAlpha[5] = { m_nAlpha1, m_nAlpha2, m_nAlpha3, m_nAlpha4, m_nAlpha5 };

	m_wndProgVert.SetMarquee(m_bMarquee, m_nInterval, m_nGap, m_cxChunk, piAlpha);
	m_wndProgHorz.SetMarquee(m_bMarquee, m_nInterval, m_nGap, m_cxChunk, piAlpha);
	
	EnableWindows();
}
