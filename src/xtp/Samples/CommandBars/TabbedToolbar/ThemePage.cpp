// ThemePage.cpp : implementation file
//

#include "stdafx.h"
#include "TabbedToolbar.h"
#include "ThemePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThemePage property page

IMPLEMENT_DYNCREATE(CThemePage, CPropertyPage)

CThemePage::CThemePage() : CPropertyPage(CThemePage::IDD)
{
	//{{AFX_DATA_INIT(CThemePage)
	m_nTheme = 2;
	//}}AFX_DATA_INIT
}

CThemePage::~CThemePage()
{
}

void CThemePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThemePage)
	DDX_Radio(pDX, IDC_RADIO_THEME, m_nTheme);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThemePage, CPropertyPage)
	//{{AFX_MSG_MAP(CThemePage)
	ON_BN_CLICKED(IDC_RADIO_THEME, OnRadioTheme)
	ON_BN_CLICKED(IDC_RADIO_THEME2, OnRadioTheme)
	ON_BN_CLICKED(IDC_RADIO_THEME3, OnRadioTheme)
	ON_BN_CLICKED(IDC_RADIO_THEME4, OnRadioTheme)
	ON_BN_CLICKED(IDC_RADIO_THEME5, OnRadioTheme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThemePage message handlers


void CThemePage::OnRadioTheme() 
{
	UpdateData();

	CXTPMDIFrameWnd* pFrame = (CXTPMDIFrameWnd*)AfxGetMainWnd();
	CXTPCommandBars* pCommandBars = pFrame->GetCommandBars();
	CXTPTabToolBar* pToolBar = (CXTPTabToolBar*)pCommandBars->GetToolBar(IDR_MAINFRAME);

	if (m_nTheme == 0)
	{
		CXTPPaintManager::SetTheme(xtpThemeOffice2000);
		pToolBar->GetPaintManager()->m_bDisableLunaColors = TRUE;
		pToolBar->GetPaintManager()->m_bFillBackground = TRUE;
		pToolBar->GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage);
	}
	if (m_nTheme == 1)
	{
		CXTPPaintManager::SetTheme(xtpThemeOfficeXP);
		pToolBar->GetPaintManager()->m_bDisableLunaColors = TRUE;
		pToolBar->GetPaintManager()->m_bFillBackground = TRUE;
		pToolBar->GetPaintManager()->SetAppearance(xtpTabAppearanceVisualStudio);
	}
	if (m_nTheme == 2)
	{
		CXTPPaintManager::SetTheme(xtpThemeOffice2003);
		pToolBar->GetPaintManager()->m_bDisableLunaColors = FALSE;
		pToolBar->GetPaintManager()->m_bFillBackground = FALSE;
		pToolBar->GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage2003);
	}
	if (m_nTheme == 3)
	{
		CXTPPaintManager::SetTheme(xtpThemeWhidbey);
		pToolBar->GetPaintManager()->m_bDisableLunaColors = TRUE;
		pToolBar->GetPaintManager()->m_bFillBackground = FALSE;
		pToolBar->GetPaintManager()->SetAppearance(xtpTabAppearanceVisualStudio2005);
	}
	if (m_nTheme == 4)
	{
		CXTPPaintManager::SetTheme(xtpThemeNativeWinXP);
		pToolBar->GetPaintManager()->m_bDisableLunaColors = TRUE;
		pToolBar->GetPaintManager()->m_bFillBackground = FALSE;
		pToolBar->GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage);
		pToolBar->GetPaintManager()->SetColor(xtpTabColorWinNative);
	}
	
	pCommandBars->RedrawCommandBars();


	((CView*)GetParent()->GetParent())->GetDocument()->UpdateAllViews(0);
}

void CThemePage::Update()
{

}
