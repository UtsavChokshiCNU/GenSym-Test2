// PageProgressBar.cpp : implementation file
//

#include "stdafx.h"
#include "controls.h"
#include "PageProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar dialog


CPageProgressBar::CPageProgressBar()
	: CXTPResizePropertyPage(CPageProgressBar::IDD)
{
	//{{AFX_DATA_INIT(CPageProgressBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bPause = FALSE;
}


void CPageProgressBar::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageProgressBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_PROGRESS7, m_wndProgressBar[6]);
	DDX_Control(pDX, IDC_PROGRESS6, m_wndProgressBar[5]);
	DDX_Control(pDX, IDC_PROGRESS5, m_wndProgressBar[4]);
	DDX_Control(pDX, IDC_PROGRESS4, m_wndProgressBar[3]);
	DDX_Control(pDX, IDC_PROGRESS3, m_wndProgressBar[2]);
	DDX_Control(pDX, IDC_PROGRESS2, m_wndProgressBar[1]);
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgressBar[0]);

}


BEGIN_MESSAGE_MAP(CPageProgressBar, CXTPResizePropertyPage)
	//{{AFX_MSG_MAP(CPageProgressBar)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STEP, OnButtonStep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar message handlers

BOOL CPageProgressBar::OnInitDialog() 
{
	CXTPResizePropertyPage::OnInitDialog();
	
	m_wndProgressBar[2].SetTheme(xtpControlThemeUltraFlat);
	m_wndProgressBar[3].SetTheme(xtpControlThemeOffice2003);
	
	m_wndProgressBar[4].SetTheme(xtpControlThemeOffice2000);
	m_wndProgressBar[4].SetWindowText(_T("Loading..."));

	m_wndProgressBar[5].SetTheme(xtpControlThemeFlat);
	m_wndProgressBar[5].SetBarColor(RGB(255,128,0));
	m_wndProgressBar[5].SetBkColor(RGB(192,255,255));


	m_wndProgressBar[6].SetTheme(xtpControlThemeResource);

	for (int i = 0; i < 7; i++)
	{
		m_wndProgressBar[i].SetPos(rand() % 100);
	}

	m_wndProgressBar[1].ModifyStyle(0, PBS_MARQUEE);
	m_wndProgressBar[3].ModifyStyle(0, PBS_MARQUEE);

	m_wndProgressBar[1].SetMarquee(1, 100);
	m_wndProgressBar[3].SetMarquee(1, 100);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageProgressBar::OnButtonPause() 
{
	m_bPause = !m_bPause;

	if (m_bPause)
	{
		m_wndProgressBar[1].SetMarquee(0, 100);
		m_wndProgressBar[3].SetMarquee(0, 100);
	}
	else
	{
		m_wndProgressBar[1].SetMarquee(1, 100);
		m_wndProgressBar[3].SetMarquee(1, 100);

	}
	
}

void CPageProgressBar::OnButtonStep() 
{
	for (int i = 0; i < 7; i++)
	{
		m_wndProgressBar[i].StepIt();
	}
	
}
