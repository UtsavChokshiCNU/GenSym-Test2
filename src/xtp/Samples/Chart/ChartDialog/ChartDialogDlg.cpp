// ChartDialogDlg.cpp : implementation file
//
// --------------------------------------------------------------------------
// COPYRIGHT NOTICE:
// --------------------------------------------------------------------------
// 
// "Codejock Chart" is a MFC extension library for creating modern charting 
// applications. This file and the code herein are part of the Codejock Chart
// MFC extension library.
//
// This code is protected under U.S. Copyright Law and International treaties
// and is intended for registered and licensed use only. Any other use is 
// strictly prohibited. This code is subject to the terms and conditions 
// outlined in the "Codejock Chart" End User License Agreement (EULA).
//
// Copyright (c) 1998-2011 Codejock Technologies LLC, All Rights Reserved.
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChartDialog.h"
#include "ChartDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CChartDialogDlg dialog

CChartDialogDlg::CChartDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartDialogDlg)
	m_nAppearance = 0;
	m_nStyle = 7;
	m_nPalette = 13;
	m_bLegend = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChartDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartDialogDlg)
	DDX_Control(pDX, IDC_COMBO_PALETTE, m_wndPalette);
	DDX_Control(pDX, IDC_COMBO_APPEARANCE, m_wndAppearance);
	DDX_CBIndex(pDX, IDC_COMBO_APPEARANCE, m_nAppearance);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE, m_nStyle);
	DDX_CBIndex(pDX, IDC_COMBO_PALETTE, m_nPalette);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	DDX_Check(pDX, IDC_CHECK_LEGEND, m_bLegend);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChartDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CChartDialogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, OnChangeComboStyle)
	ON_CBN_SELCHANGE(IDC_COMBO_APPEARANCE, OnChangeComboAppearance)
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE, OnChangeComboPalette)
	ON_BN_CLICKED(IDC_CHECK_LEGEND, OnCheckLegend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartDialogDlg message handlers

void CChartDialogDlg::AddTitles()
{
	CXTPChartTitle* pTitle = m_wndChartControl.GetContent()->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Chart Control"));
}

void CChartDialogDlg::AddSeries()
{
	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->Add(new CXTPChartSeries());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(0, 0.5, 0.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(1, 2, 2));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(2, 1, 1));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(3, 1.5, 1.5));

	CXTPChartPieSeriesStyle* pPieStyle = (CXTPChartPieSeriesStyle*)pSeries->SetStyle(new CXTPChartPieSeriesStyle());
	pPieStyle->SetRotation(20);
	pSeries->SetName(_T("Series 1"));
}



BOOL CChartDialogDlg::OnInitDialog()
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
	
	
	AddTitles();
	AddSeries();

#ifdef AS_DEV
	((CComboBox*)GetDlgItem(IDC_COMBO_STYLE))->SetCurSel(10);
	OnChangeComboStyle();
#endif
	//m_wndChartControl.GetContent()->GetLegend()->SetVisible(TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChartDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChartDialogDlg::OnPaint() 
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
HCURSOR CChartDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChartDialogDlg::OnChangeComboStyle() 
{
	UpdateData();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	switch (m_nStyle)
	{
	case 0:
		pSeries->SetStyle(new CXTPChartPointSeriesStyle());
		break;
	case 1:
		pSeries->SetStyle(new CXTPChartLineSeriesStyle());
		break;
	case 2:
		pSeries->SetStyle(new CXTPChartSplineSeriesStyle());
		break;
	case 3:
		pSeries->SetStyle(new CXTPChartBarSeriesStyle());
		break;
	case 4:
		pSeries->SetStyle(new CXTPChartAreaSeriesStyle());
		break;
	case 5:
		pSeries->SetStyle(new CXTPChartSplineAreaSeriesStyle());
		break;
	case 6:
		pSeries->SetStyle(new CXTPChartBubbleSeriesStyle());
		break;
	case 7:
		pSeries->SetStyle(new CXTPChartPieSeriesStyle());
		break;
	case 8:
		{
			CXTPChartPieSeriesStyle* pPieStyle = (CXTPChartPieSeriesStyle*)pSeries->SetStyle(new CXTPChartPieSeriesStyle());
			pPieStyle->SetHolePercent(60);
			pPieStyle->SetRotation(20);
		}
		break;

	case 9:
		{
			CXTPChartPie3DSeriesStyle* pPieStyle = (CXTPChartPie3DSeriesStyle*)pSeries->SetStyle(new CXTPChartPie3DSeriesStyle());
			pPieStyle->SetHolePercent(60);
		}
		break;
	case 10:
		pSeries->SetStyle(new CXTPChartTorus3DSeriesStyle());
		break;
	}
	
}

void CChartDialogDlg::OnChangeComboAppearance() 
{
	UpdateData();
	
	CString strAppearance;
	m_wndAppearance.GetLBText(m_nAppearance, strAppearance);

	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_") + strAppearance);

	m_wndChartControl.GetContent()->OnChartChanged();
}

void CChartDialogDlg::OnChangeComboPalette() 
{
	UpdateData();
	

	CString strPalette;
	m_wndPalette.GetLBText(m_nPalette, strPalette);
	strPalette.MakeUpper();
	strPalette.Replace(_T(" "), _T(""));

	m_wndChartControl.GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE_") + strPalette);

	m_wndChartControl.GetContent()->OnChartChanged();
}

void CChartDialogDlg::OnCheckLegend() 
{
	UpdateData();

	m_wndChartControl.GetContent()->GetLegend()->SetVisible(m_bLegend);	
}
