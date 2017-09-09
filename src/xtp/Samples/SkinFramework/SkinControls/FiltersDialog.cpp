// FiltersDialog.cpp : implementation file
//

#include "stdafx.h"
#include "skincontrols.h"
#include "FiltersDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class CColorFilterMonochrome : public CXTPSkinManagerColorFilter
{
public:
	virtual void ApplyColorFilter(COLORREF& clr)
	{
		double dGray = (GetRValue(clr) * 0.299 + GetGValue(clr) * 0.587 + GetBValue(clr) * 0.114);		
		clr = RGB(dGray, dGray, dGray);
	}
};


/////////////////////////////////////////////////////////////////////////////
// CFiltersDialog dialog


CFiltersDialog::CFiltersDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFiltersDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFiltersDialog)
	m_nHue = 10;
	m_nSaturation = 50;
	m_nBlend = 255;
	m_bColorize = XTPSkinManager()->IsColorFilterExists();
	m_bColorShift = FALSE;
	m_bCustom = FALSE;
	m_nBlue = -50;
	m_nGreen = 0;
	m_nRed = +50;
	//}}AFX_DATA_INIT
}


void CFiltersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFiltersDialog)
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_wndBlue);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_wndGreen);
	DDX_Control(pDX, IDC_SLIDER_RED, m_wndRed);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_wndSaturation);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_wndHue);
	DDX_Control(pDX, IDC_SLIDER_BLEND, m_wndBlend);
	DDX_Slider(pDX, IDC_SLIDER_HUE, m_nHue);
	DDX_Slider(pDX, IDC_SLIDER_SATURATION, m_nSaturation);
	DDX_Slider(pDX, IDC_SLIDER_BLEND, m_nBlend);
	DDX_Check(pDX, IDC_CHECK_COLORIZE, m_bColorize);
	DDX_Check(pDX, IDC_CHECK_COLORSHIFT, m_bColorShift);
	DDX_Check(pDX, IDC_CHECK_CUSTOM, m_bCustom);
	DDX_Slider(pDX, IDC_SLIDER_BLUE, m_nBlue);
	DDX_Slider(pDX, IDC_SLIDER_GREEN, m_nGreen);
	DDX_Slider(pDX, IDC_SLIDER_RED, m_nRed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFiltersDialog, CDialog)
	//{{AFX_MSG_MAP(CFiltersDialog)
	ON_BN_CLICKED(IDC_CHECK_COLORIZE, UpdateFilters)
	ON_BN_CLICKED(IDC_CHECK_COLORSHIFT, UpdateFilters)
	ON_BN_CLICKED(IDC_CHECK_CUSTOM, UpdateFilters)	
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFiltersDialog message handlers

BOOL CFiltersDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_wndBlend.SetRange(0, 100);
	m_wndHue.SetRange(0, 255);
	m_wndSaturation.SetRange(0, 255);

	m_wndRed.SetRange(-100, 100);
	m_wndGreen.SetRange(-100, 100);
	m_wndBlue.SetRange(-100, 100);

	UpdateData(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFiltersDialog::UpdateFilters()
{
	UpdateData();
	
	XTPSkinManager()->RemoveColorFilters();

	if (m_bColorize)
	{
		XTPSkinManager()->AddColorFilter(new CXTPSkinManagerColorFilterColorize((BYTE)m_nHue, (BYTE)m_nSaturation, (float)m_nBlend / 100.0f));
	}
	
	if (m_bColorShift)
	{
		XTPSkinManager()->AddColorFilter(new CXTPSkinManagerColorFilterShiftRGB(m_nRed, m_nGreen, m_nBlue));
	}

	if (m_bCustom)
	{
		XTPSkinManager()->AddColorFilter(new CColorFilterMonochrome());
	}

	XTPSkinManager()->RedrawAllControls();

}

void CFiltersDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ((CWnd*)pScrollBar == &m_wndSaturation || 
		(CWnd*)pScrollBar == &m_wndHue  || 
		(CWnd*)pScrollBar == &m_wndBlend)
	{
		UpdateData();
		m_bColorize = TRUE;
		UpdateData(FALSE);
		
		UpdateFilters();
	}

	if ((CWnd*)pScrollBar == &m_wndRed || 
		(CWnd*)pScrollBar == &m_wndBlue  || 
		(CWnd*)pScrollBar == &m_wndGreen)
	{
		UpdateData();
		m_bColorShift = TRUE;
		UpdateData(FALSE);
		
		UpdateFilters();
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
