// PageScrollBar.cpp : implementation file
//

#include "stdafx.h"
#include "controls.h"
#include "PageScrollBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageScrollBar property page

IMPLEMENT_DYNCREATE(CPageScrollBar, CXTPResizePropertyPage)

CPageScrollBar::CPageScrollBar() : CXTPResizePropertyPage(CPageScrollBar::IDD)
{
	//{{AFX_DATA_INIT(CPageScrollBar)
	m_bEnabled = TRUE;
	//}}AFX_DATA_INIT
}

CPageScrollBar::~CPageScrollBar()
{
}

void CPageScrollBar::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageScrollBar)
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_bEnabled);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SCROLLBAR7, m_wndScrollBar[6]);
	DDX_Control(pDX, IDC_SCROLLBAR6, m_wndScrollBar[5]);
	DDX_Control(pDX, IDC_SCROLLBAR5, m_wndScrollBar[4]);
	DDX_Control(pDX, IDC_SCROLLBAR4, m_wndScrollBar[3]);
	DDX_Control(pDX, IDC_SCROLLBAR3, m_wndScrollBar[2]);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_wndScrollBar[1]);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_wndScrollBar[0]);
}


BEGIN_MESSAGE_MAP(CPageScrollBar, CXTPResizePropertyPage)
	//{{AFX_MSG_MAP(CPageScrollBar)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_CHECK_ENABLED, OnCheckEnabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageScrollBar message handlers

BOOL CPageScrollBar::OnInitDialog() 
{
	CXTPResizePropertyPage::OnInitDialog();
	
	SetResize(IDC_GBOX_OPTIONS, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_ENABLED, CXTPResizePoint((float)(2.0/3.0), 0), XTP_ANCHOR_TOPRIGHT);

	m_wndScrollBar[1].SetUseVisualStyle(FALSE);
	m_wndScrollBar[2].SetTheme(xtpControlThemeOffice2000);
	m_wndScrollBar[3].SetTheme(xtpControlThemeFlat);
	m_wndScrollBar[4].SetTheme(xtpControlThemeUltraFlat);
	m_wndScrollBar[5].SetTheme(xtpControlThemeOfficeXP);
	m_wndScrollBar[6].SetTheme(xtpControlThemeResource);


	for (int i = 0; i < 7; i++)
	{
		m_wndScrollBar[i].SetScrollRange(0, 100);
		m_wndScrollBar[i].SetScrollPos(rand() % 100);
	}

	OnCheckEnabled();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageScrollBar::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// its horizontal scroll bar
	int nCurPos = pScrollBar->GetScrollPos();
	
	// decide what to do for each diffrent scroll event
	switch (nSBCode)
	{
	case SB_LEFT: nCurPos = 0; break;
	case SB_RIGHT: nCurPos = pScrollBar->GetScrollLimit(); break;
	case SB_LINELEFT: nCurPos = max(nCurPos - 6, 0); break;
	case SB_LINERIGHT: nCurPos = min(nCurPos + 6, pScrollBar->GetScrollLimit()); break;
	case SB_PAGELEFT: nCurPos = max(nCurPos - 20, 0); break;
	case SB_PAGERIGHT: nCurPos = min(nCurPos + 20, pScrollBar->GetScrollLimit()); break;
		
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:  nCurPos = nPos; break;
	}

	pScrollBar->SetScrollPos(nCurPos);
}

void CPageScrollBar::OnCheckEnabled() 
{
	UpdateData();

	for (int i = 0; i < 7; i++)
	{
		m_wndScrollBar[i].EnableWindow(m_bEnabled);
	}
	
}
