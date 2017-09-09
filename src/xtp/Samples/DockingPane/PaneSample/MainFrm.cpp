// MainFrm.cpp : implementation of the CMainFrame class
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
#include "Pane.h"

#include "MainFrm.h"

//#define VISIO_EDIT_BACKGROUND
//#define VISIO_OFFICE2003_THEME
BOOL m_bMinMaxSample = FALSE;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace XTPDockingPanePaintThemes;

class CCustomTheme :  public CXTPDockingPaneGripperedTheme
{
	virtual void DrawCaption(CDC* pDC, CXTPDockingPaneTabbedContainer* pPane, CRect rc)
	{
		CRect rcCaption(0, 2, rc.right, m_nTitleHeight + 1);

		// Drawing Frame
		pDC->FillSolidRect(rcCaption, GetSysColor(COLOR_3DFACE));
		pDC->Draw3dRect(1, rc.top + 1, rc.Width() -1, rcCaption.bottom + 1, GetSysColor(COLOR_WINDOW), GetSysColor(COLOR_WINDOW));
		pDC->Draw3dRect(0, rc.top, rc.Width() - 1 , rcCaption.bottom + 2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));

		COLORREF clrText = GetSysColor(COLOR_BTNTEXT);

		rcCaption.right -= 3;
		DrawCaptionButtons(pDC, pPane->GetCaptionButtons(), rcCaption, clrText, 14, 2, FALSE);

		// Drawing Title
		if (pPane->GetSelected())
		{
			CRect rcText(rcCaption.left + 4, rcCaption.top + 1, rcCaption.right, rcCaption.bottom);

			pDC->SetTextColor(clrText);
			CXTPFontDC font(pDC, &m_fntTitle);
			pDC->DrawText(pPane->GetSelected()->GetTitle(), rcText, DT_SINGLELINE|DT_END_ELLIPSIS|DT_VCENTER);
		}
	}

};



// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(IDR_PANE1, IDR_PANE10, OnShowPane)

	ON_COMMAND(ID_THEME_DEFAULT, OnThemeDefault)
	ON_COMMAND(ID_THEME_OFFICE, OnThemeOffice)
	ON_COMMAND(ID_THEME_OFFICE2003, OnThemeOffice2003)
	ON_COMMAND(ID_THEME_WINXP, OnThemeWinXP)
	ON_COMMAND(ID_THEME_GRIPPERED, OnThemeGrippered)
	ON_COMMAND(ID_THEME_WHIDBEY, OnThemeWhidbey)
	ON_COMMAND(ID_THEME_SHORTCUTBAR2003, OnThemeShortcutBar2003)
	ON_COMMAND(ID_THEME_EXPLORER, OnThemeExplorer)
	ON_COMMAND(ID_THEME_OFFICE2007, OnThemeOffice2007)
	ON_COMMAND(ID_THEME_WORD2007, OnThemeWord2007)
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_DEFAULT, ID_THEME_CUSTOM4, OnUpdateTheme)

	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_COMMAND(ID_LAYOUT_EDITOR, OnLayoutEditor)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_EDITOR, OnUpdateLayoutEditor)
	ON_COMMAND(ID_LAYOUT_RUN, OnLayoutRun)
	ON_UPDATE_COMMAND_UI(ID_LAYOUT_RUN, OnUpdateLayoutRun)
	ON_WM_DESTROY()

	ON_COMMAND(ID_THEME_VISIO_OFFICE2000, OnThemeVisio2000)
	ON_COMMAND(ID_THEME_VISIO, OnThemeVisio)
	ON_COMMAND(ID_THEME_VISIO_OFFICE2003, OnThemeVisio2003)

	ON_COMMAND(ID_THEME_CUSTOM, OnThemeCustom)
	ON_COMMAND(ID_THEME_CUSTOM2, OnThemeCustom2)
	ON_COMMAND(ID_THEME_CUSTOM3, OnThemeCustom3)
	ON_COMMAND(ID_THEME_CUSTOM4, OnThemeCustom4)

	ON_COMMAND(ID_LAYOUT_LOADFROMFILE, OnLoadFromFile)
	ON_COMMAND(ID_LAYOUT_SAVETOFILE, OnSaveToFile)
	ON_COMMAND(ID_LAYOUT_LOADFROMRESOURCE, OnLoadFromResource)

	ON_COMMAND(ID_DOCKINGPANE_HIDECLIENT, OnHideClient)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_HIDECLIENT, OnUpdateHideClient)

	ON_COMMAND(ID_DOCKINGPANE_USESPLITTERTRACKER, OnUseSplitterTracker)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_USESPLITTERTRACKER, OnUpdateUseSplitterTracker)

	ON_COMMAND(ID_DOCKINGPANE_THEMEDFLOATINGFRAMES, OnThemedFloatingFrames)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_THEMEDFLOATINGFRAMES, OnUpdateThemedFloatingFrames)

	ON_COMMAND(ID_DOCKINGCONTEXT_ALPHACONTEXT, OnAlphaContext)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGCONTEXT_ALPHACONTEXT, OnUpdateAlphaContext)

	ON_COMMAND(ID_DOCKINGCONTEXT_DOCKINGSTICKERS, OnDockingStickers)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGCONTEXT_DOCKINGSTICKERS, OnUpdateDockingStickers)

	ON_COMMAND(ID_DOCKINGPANE_MINMAXSAMPLE, OnMinMaxSamlpe)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_MINMAXSAMPLE, OnUpdateMinMaxSamlpe)
	ON_WM_GETMINMAXINFO()


	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_CLOSEBUTTON, OnCaptionButtonClose)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_CLOSEBUTTON, OnUpdateCaptionButtonClose)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_AUTOHIDEBUTTON, OnCaptionButtonAutoHide)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_AUTOHIDEBUTTON, OnUpdateCaptionButtonAutoHide)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_MENUBUTTON, OnCaptionButtonMenu)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_MENUBUTTON, OnUpdateCaptionButtonMenu)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONBUTTONS_MAXIMIZERESTOREBUTTON, OnCaptionButtonMaximize)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONBUTTONS_MAXIMIZERESTOREBUTTON, OnUpdateCaptionButtonMaximize)

	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_VISIBLE, OnCaptionVisible)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_HORIZONTAL, OnCaptionHorizontal)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_VERTICAL, OnCaptionVertical)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_AUTOBYSIZE, OnCaptionAutoBySize)
	ON_COMMAND(ID_DOCKINGPANE_CAPTIONS_AUTOBYPOSITION, OnCaptionAutoByPosition)

	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_VISIBLE, OnUpdateCaptionVisible)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_HORIZONTAL, OnUpdateCaptionHorizontal)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_VERTICAL, OnUpdateCaptionVertical)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_AUTOBYSIZE, OnUpdateCaptionAutoBySize)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CAPTIONS_AUTOBYPOSITION, OnUpdateCaptionAutoByPosition)

	ON_COMMAND(ID_DOCKINGPANE_CLOSEBUTTONAFFECTS, OnCloseButtonAffects)
	ON_COMMAND(ID_DOCKINGPANE_AUTOHIDEBUTTONAFFECTS, OnAutoHideButtonAffects)

	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_CLOSEBUTTONAFFECTS, OnUpdateCloseButtonAffects)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_AUTOHIDEBUTTONAFFECTS, OnUpdateAutoHideButtonAffects)

	ON_COMMAND(ID_DOCKINGCONTEXT_SHOWWHILEDRAGGING, OnShowContentsWhileDragging)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGCONTEXT_SHOWWHILEDRAGGING, OnUpdateShowContentsWhileDragging)

	ON_COMMAND(ID_DOCKINGPANE_STICKYFLOATINGFRAMES, OnStickyFloatingFrames)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_STICKYFLOATINGFRAMES, OnUpdateStickyFloatingFrames)

	ON_COMMAND(ID_DOCKINGPANE_TRANSPARENTFLOATINGFRAMES, OnTransparentFloatingFrames)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGPANE_TRANSPARENTFLOATINGFRAMES, OnUpdateTransparentFloatingFrames)

	ON_COMMAND(ID_DOCKINGCONTEXT_ENABLESIDEDOCKING, OnEnableSideDocking)
	ON_UPDATE_COMMAND_UI(ID_DOCKINGCONTEXT_ENABLESIDEDOCKING, OnUpdateEnableSideDocking)
	

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_WM_CLOSE()

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: m_pEditorLayout(NULL)
, m_pRunLayout(NULL)
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	LOGFONT lfIcon;
	VERIFY( ::SystemParametersInfo( SPI_GETICONTITLELOGFONT, sizeof( lfIcon ), &lfIcon, 0 ) );
	m_fntEdit.CreateFontIndirect(&lfIcon);



	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	XTPPaintManager()->SetTheme(xtpThemeOfficeXP);

	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagAddMDISysPopup);


	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));


	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	SetDockingPaneTheme(xtpPaneThemeOffice2003);
	m_paneManager.SetFloatingFrameCaption(_T("Panes"));
	m_paneManager.SetStickyFloatingFrames(TRUE);
	m_paneManager.SetThemedFloatingFrames(TRUE);

	m_paneManager.SetSideDockingMargin(CRect(2, 2, 2, 2));
	m_paneManager.EnableSideDocking();

	m_paneManager.EnableKeyboardNavigate();

	// Create docking panes.
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		IDR_PANE1, CRect(0, 0,200, 120), xtpPaneDockTop);
	m_paneManager.CreatePane(
		IDR_PANE2, CRect(0, 0,200, 120), xtpPaneDockLeft, pwndPane1);
	CXTPDockingPane* pwndPane3 = m_paneManager.CreatePane(
		IDR_PANE3, CRect(0, 0,200, 120), xtpPaneDockLeft);
	CXTPDockingPane* pwndPane4 = m_paneManager.CreatePane(
		IDR_PANE4, CRect(0, 0,200, 120), xtpPaneDockTop, pwndPane3);
	CXTPDockingPane* pwndPane5 = m_paneManager.CreatePane(
		IDR_PANE5, CRect(0, 0,200, 120), xtpPaneDockLeft, pwndPane4);
	CXTPDockingPane* pwndPane6 = m_paneManager.CreatePane(
		IDR_PANE6, CRect(0, 0,200, 120), xtpPaneDockTop, pwndPane5);
	CXTPDockingPane* pwndPane7 = m_paneManager.CreatePane(
		IDR_PANE7, CRect(0, 0,200, 120), xtpPaneDockTop, pwndPane6);
	CXTPDockingPane* pwndPane8 = m_paneManager.CreatePane(
		IDR_PANE8, CRect(0, 0,200, 120), xtpPaneDockRight);
	CXTPDockingPane* pwndPane9 = m_paneManager.CreatePane(
		IDR_PANE9, CRect(0, 0,200, 120), xtpPaneDockBottom, pwndPane8);
	CXTPDockingPane* pwndPane10 = m_paneManager.CreatePane(
		IDR_PANE10, CRect(0, 0,200, 120), xtpPaneDockBottom, pwndPane9);

	// Create the layout manager for run mode.  Layouts define how
	// the panes will appear when docked, you can define multiple
	// layouts.

	// If "RunLayout" layout does not exist, save the current configuration
	// as "RunLayout", otherwise load previous state.
	m_pRunLayout = m_paneManager.CreateLayout();
	if (!m_pRunLayout->Load(_T("RunLayout"))) {
		m_paneManager.GetLayout(m_pRunLayout);
	}

	// Initialize the default layout for "EditorLayout".
	m_paneManager.AttachPane(
		pwndPane9, pwndPane8);
	m_paneManager.AttachPane(
		pwndPane6, pwndPane1);
	m_paneManager.AttachPane(
		pwndPane4, pwndPane7);
	m_paneManager.HidePane(
		pwndPane7);

	CXTPDockingPaneSidePanel* pPanel = m_paneManager.DockSidePane(pwndPane10, xtpPaneDockRight, CRect(0, 100, 120, 300));
	pPanel->Collapse();

	// If "EditorLayout" layout does not exist, save the current configuration
	// as "EditorLayout", otherwise load previous state and set it as the active
	// layout.
	m_pEditorLayout = m_paneManager.CreateLayout();

	if (m_pEditorLayout->Load(_T("EditorLayout"))) {
		m_paneManager.SetLayout(m_pEditorLayout);
	}
	else {
		m_paneManager.GetLayout(m_pEditorLayout);
	}

	// Get a pointer to IDR_PANE1 and set the title.
	CXTPDockingPane* pPane = m_paneManager.FindPane(IDR_PANE1);
	ASSERT(pPane);
	if (pPane) {
		pPane->SetTitle(_T("Pane 1 - Long Title\nPane 1"));
	}

	// Get a pointer to IDR_PANE2 and set the title.
	pPane = m_paneManager.FindPane(IDR_PANE2);
	ASSERT(pPane);
	if (pPane) {
		pPane->SetTitle(_T("Pane 2 - No Closeable\nPane 2"));
		pPane->SetOptions(xtpPaneNoCloseable);
	}

	// Get a pointer to IDR_PANE3 and set the title.
	pPane = m_paneManager.FindPane(IDR_PANE3);
	ASSERT(pPane);
	if (pPane) {
		pPane->SetTitle(_T("Pane 3 - No Hideable\nPane 3"));
		pPane->SetOptions(xtpPaneNoHideable);
	}


	m_bEditor = TRUE;

	// Set the icons for the docking pane tabs.
	int nIDs1[] = {IDR_PANE1, IDR_PANE2, IDR_PANE3, IDR_PANE4, IDR_PANE5};
	m_paneManager.SetIcons(IDB_BITMAP1, nIDs1, 5, RGB(0, 255, 0));

	int nIDs2[] = {IDR_PANE6, IDR_PANE7, IDR_PANE8, IDR_PANE9, IDR_PANE10};
	m_paneManager.SetIcons(IDB_BITMAP2, nIDs2, 5, RGB(0, 255, 0));

	if (XTPResourceImages()->IsValid())
	{
		OnThemeOffice2007();
	}
	else
	{
		OnThemeOffice2003();
	}
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			int nIndex = pPane->GetID() - IDR_PANE1;
			ASSERT(nIndex >=0 &&  nIndex < sizeof(m_wndPanes) / sizeof(m_wndPanes[0]));
			CEditPane& wndEdit = m_wndPanes[nIndex];

			// create and attach the edit control for this pane.
			if (!::IsWindow(wndEdit.m_hWnd))
			{
				if (!wndEdit.CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""),
					WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE, CRect(0, 0,200, 120), this, pPane->GetID()))
				{
					TRACE0( "Error creating pane edit control.\n" );
				}
				wndEdit.SetFont(&m_fntEdit);

				AdjustStyle(m_paneManager.GetCurrentTheme());
			}

			pPane->Attach(&wndEdit);
		}

		return TRUE; // handled
	}

	if (wParam == XTP_DPN_CONTEXTMENU)
	{
		XTP_DOCKINGPANE_CLICK* pClick = (XTP_DOCKINGPANE_CLICK*)lParam;

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_POPUP_PANES));
		CMenu* pPopup = menu.GetSubMenu(0);
		TrackPopupMenu(pPopup->GetSafeHmenu(), TPM_RIGHTBUTTON, pClick->pt.x, pClick->pt.y, 0, AfxGetMainWnd()->GetSafeHwnd(), 0);

		return TRUE;
	}

	return FALSE;
}

void CMainFrame::AdjustStyle(XTPDockingPanePaintTheme theme)
{
	BOOL bBorder = FALSE, bStaticEdge = FALSE, bClientEdge = FALSE;
	switch(theme)
	{
		case xtpPaneThemeVisualStudio2003: bStaticEdge = TRUE;    break;
		case xtpPaneThemeDefault: bBorder = TRUE; break;
		case xtpPaneThemeGrippered: bClientEdge = TRUE; break;
	}

	for (int i = 0; i < sizeof(m_wndPanes) / sizeof(m_wndPanes[0]); i++)
	{
		if (!m_wndPanes[i].m_hWnd)
		{
			if (!m_wndPanes[i].CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""),
				WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE, CRect(0, 0,0, 0), this, IDR_PANE1 + i))
			{
				TRACE0( "Error creating pane edit control.\n" );
			}
			m_wndPanes[i].SetFont(&m_fntEdit);

		}
		m_wndPanes[i].ModifyStyle(bBorder? 0: WS_BORDER, bBorder? WS_BORDER: 0, SWP_FRAMECHANGED|SWP_DRAWFRAME);
		m_wndPanes[i].ModifyStyleEx(bStaticEdge? 0: WS_EX_STATICEDGE, bStaticEdge? WS_EX_STATICEDGE: 0, SWP_FRAMECHANGED|SWP_DRAWFRAME );
		m_wndPanes[i].ModifyStyleEx(bClientEdge? 0: WS_EX_CLIENTEDGE, bClientEdge? WS_EX_CLIENTEDGE: 0, SWP_FRAMECHANGED|SWP_DRAWFRAME );
	}
}
// CMainFrame message handlers

void CMainFrame::OnShowPane(UINT nID)
{
	m_paneManager.ShowPane(nID);
}


void CMainFrame::SwitchLayout()
{
	if (m_bMinMaxSample)
		OnMinMaxSamlpe();

	if (m_bEditor)
	{
		m_paneManager.GetLayout(m_pEditorLayout);
		m_paneManager.SetLayout(m_pRunLayout);
	} else
	{
		m_paneManager.GetLayout(m_pRunLayout);
		m_paneManager.SetLayout(m_pEditorLayout);
	}
	m_bEditor = !m_bEditor;
}

void CMainFrame::OnLayoutEditor()
{
	if (!m_bEditor) SwitchLayout();

}

void CMainFrame::OnLayoutRun()
{
	if (m_bEditor) SwitchLayout();
}

void CMainFrame::OnUpdateLayoutEditor(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bEditor);
}

void CMainFrame::OnUpdateLayoutRun(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!m_bEditor);
}

void CMainFrame::OnDestroy()
{
	if (m_bMinMaxSample)
	{
		OnMinMaxSamlpe();
	}

	CMDIFrameWnd::OnDestroy();

	m_paneManager.GetLayout(m_bEditor? m_pEditorLayout: m_pRunLayout);

	m_pEditorLayout->Save(_T("EditorLayout"));
	m_pRunLayout->Save(_T("RunLayout"));


	delete m_pEditorLayout;
	delete m_pRunLayout;
}

void CMainFrame::OnThemeDefault()
{
	AdjustStyle(xtpPaneThemeDefault);
	SetDockingPaneTheme(xtpPaneThemeDefault);
	m_nSelectedTheme = ID_THEME_DEFAULT;

	SetCommandBarsTheme(xtpThemeOffice2000);
}
void CMainFrame::OnThemeOffice()
{
	AdjustStyle(xtpPaneThemeVisualStudio2003);
	SetDockingPaneTheme(xtpPaneThemeVisualStudio2003);
	m_nSelectedTheme = ID_THEME_OFFICE;

	SetCommandBarsTheme(xtpThemeOfficeXP);

}

void CMainFrame::OnThemeWhidbey()
{
	AdjustStyle(xtpPaneThemeVisualStudio2003);
	SetDockingPaneTheme(xtpPaneThemeVisualStudio2005);
	m_nSelectedTheme = ID_THEME_WHIDBEY;

	SetCommandBarsTheme(xtpThemeWhidbey);

}

void CMainFrame::OnThemeExplorer()
{
	AdjustStyle(xtpPaneThemeGrippered);
	SetDockingPaneTheme(xtpPaneThemeWinExplorer);
	m_nSelectedTheme = ID_THEME_EXPLORER;

	SetCommandBarsTheme(xtpThemeNativeWinXP);

}

void CMainFrame::SetCommandBarsTheme(XTPPaintTheme paintTheme)
{
	CXTPPaintManager::SetTheme(paintTheme);

	EnableOffice2007Frame(paintTheme == xtpThemeRibbon ? GetCommandBars() : NULL);

	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnThemeOffice2007()
{
	AdjustStyle(xtpPaneThemeVisualStudio2003);
	SetDockingPaneTheme(xtpPaneThemeResource);
	m_nSelectedTheme = ID_THEME_OFFICE2007;

	SetCommandBarsTheme(xtpThemeRibbon);

}

void CMainFrame::OnThemeWord2007()
{
	AdjustStyle(xtpPaneThemeVisualStudio2003);
	SetDockingPaneTheme(xtpPaneThemeOffice2007Word);
	m_nSelectedTheme = ID_THEME_WORD2007;

	SetCommandBarsTheme(xtpThemeRibbon);

}

void CMainFrame::OnThemeOffice2003()
{
	AdjustStyle(xtpPaneThemeVisualStudio2003);
	SetDockingPaneTheme(xtpPaneThemeOffice2003);
	m_nSelectedTheme = ID_THEME_OFFICE2003;

	SetCommandBarsTheme(xtpThemeOffice2003);
}

void CMainFrame::SetDockingPaneTheme(XTPDockingPanePaintTheme theme)
{
	m_paneManager.SetClientMargin(theme == xtpPaneThemeResource ? 3 : 0);
	m_paneManager.SetTheme(theme);
}

void CMainFrame::OnThemeShortcutBar2003()
{
	AdjustStyle(xtpPaneThemeVisualStudio2003);
	SetDockingPaneTheme(xtpPaneThemeOffice2003Outlook);
	m_nSelectedTheme = ID_THEME_SHORTCUTBAR2003;

	SetCommandBarsTheme(xtpThemeOffice2003);
}

void CMainFrame::OnThemeWinXP()
{
	AdjustStyle(xtpPaneThemeGrippered);
	SetDockingPaneTheme(xtpPaneThemeWinNative);
	m_nSelectedTheme = ID_THEME_WINXP;

	SetCommandBarsTheme(xtpThemeNativeWinXP);

}



void CMainFrame::OnThemeGrippered()
{
	AdjustStyle(xtpPaneThemeGrippered);
	SetDockingPaneTheme(xtpPaneThemeGrippered);
	m_nSelectedTheme = ID_THEME_GRIPPERED;

	m_paneManager.GetPaintManager()->GetTabPaintManager()->m_clientFrame = xtpTabFrameBorder;

	SetCommandBarsTheme(xtpThemeOffice2000);

}

void CMainFrame::OnThemeVisio()
{
	AdjustStyle(xtpPaneThemeOffice2002Visio);
	SetDockingPaneTheme(xtpPaneThemeOffice2002Visio);
	m_nSelectedTheme = ID_THEME_VISIO;

	SetCommandBarsTheme(xtpThemeOfficeXP);

}

void CMainFrame::OnThemeVisio2003()
{
	AdjustStyle(xtpPaneThemeOffice2002Visio);
	SetDockingPaneTheme(xtpPaneThemeOffice2003);
	m_nSelectedTheme = ID_THEME_VISIO_OFFICE2003;

	m_paneManager.GetPaintManager()->GetTabPaintManager()->SetAppearance(xtpTabAppearanceVisio);
	m_paneManager.GetPaintManager()->GetTabPaintManager()->SetColor(xtpTabColorOffice2003);
	m_paneManager.GetPaintManager()->GetTabPaintManager()->m_bHotTracking = TRUE;

	m_paneManager.GetPaintManager()->GetPanelPaintManager()->SetColor(xtpTabColorOffice2003);


	SetCommandBarsTheme(xtpThemeOffice2003);

}

void CMainFrame::OnThemeVisio2000()
{
	AdjustStyle(xtpPaneThemeOffice2002Visio);
	SetDockingPaneTheme(xtpPaneThemeDefault);
	m_nSelectedTheme = ID_THEME_VISIO_OFFICE2000;

	m_paneManager.GetPaintManager()->GetTabPaintManager()->SetAppearance(xtpTabAppearanceVisio);

	SetCommandBarsTheme(xtpThemeOffice2000);
}


void CMainFrame::OnThemeCustom()
{
	AdjustStyle(xtpPaneThemeCustom);
	m_paneManager.SetCustomTheme(new CCustomTheme());
	m_nSelectedTheme = ID_THEME_CUSTOM;

	SetCommandBarsTheme(xtpThemeOfficeXP);

}

void CMainFrame::OnThemeCustom2()
{
	AdjustStyle(xtpPaneThemeGrippered);
	m_paneManager.SetCustomTheme(new CXTPDockingPaneDefaultTheme());
	m_nSelectedTheme = ID_THEME_CUSTOM2;

	CXTPTabPaintManager* pTabPaintManager = m_paneManager.GetPaintManager()->GetTabPaintManager();

	pTabPaintManager->SetPosition(xtpTabPositionTop);
	pTabPaintManager->m_clientFrame = xtpTabFrameBorder;


	SetCommandBarsTheme(xtpThemeOffice2000);

}

void CMainFrame::OnThemeCustom3()
{
	AdjustStyle(xtpPaneThemeVisualStudio2003);
	m_nSelectedTheme = ID_THEME_CUSTOM3;

	m_paneManager.SetCustomTheme(new CXTPDockingPaneVisualStudio2003Theme());
	m_paneManager.GetPaintManager()->GetTabPaintManager()->SetAppearance(xtpTabAppearanceStateButtons);
	m_paneManager.GetPaintManager()->GetPanelPaintManager()->SetAppearance(xtpTabAppearanceStateButtons);

	SetCommandBarsTheme(xtpThemeOfficeXP);

}

void CMainFrame::OnThemeCustom4()
{
	AdjustStyle(xtpPaneThemeOffice2002Visio);
	m_nSelectedTheme = ID_THEME_CUSTOM4;

	m_paneManager.SetCustomTheme(new CXTPDockingPaneVisualStudio2003Theme());

	CXTPTabPaintManager* pTabPaintManager = m_paneManager.GetPaintManager()->GetTabPaintManager();
	pTabPaintManager->SetAppearance(xtpTabAppearanceExcel);
	pTabPaintManager->m_clientFrame = xtpTabFrameBorder;

	pTabPaintManager = m_paneManager.GetPaintManager()->GetPanelPaintManager();
	pTabPaintManager->SetAppearance(xtpTabAppearanceExcel);


	SetCommandBarsTheme(xtpThemeOfficeXP);

}

void CMainFrame::OnUpdateTheme(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nSelectedTheme == pCmdUI->m_nID);
}


void CMainFrame::OnHideClient()
{
	m_paneManager.HideClient(!m_paneManager.IsClientHidden());
}

void CMainFrame::OnUpdateHideClient(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsClientHidden()? TRUE: FALSE);
}

void CMainFrame::OnUseSplitterTracker()
{
	m_paneManager.UseSplitterTracker(!m_paneManager.IsSplitterTrackerUsed());
}

void CMainFrame::OnUpdateUseSplitterTracker(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsSplitterTrackerUsed()? TRUE: FALSE);
}

void CMainFrame::OnThemedFloatingFrames()
{
	m_paneManager.SetThemedFloatingFrames(!m_paneManager.IsThemedFloatingFrames());
}
void CMainFrame::OnUpdateThemedFloatingFrames(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsThemedFloatingFrames()? TRUE: FALSE);
}

void CMainFrame::OnAlphaContext()
{
	m_paneManager.SetAlphaDockingContext(!m_paneManager.IsAlphaDockingContext());

}
void CMainFrame::OnUpdateAlphaContext(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsAlphaDockingContext()? TRUE: FALSE);
}

void CMainFrame::OnDockingStickers()
{
	m_paneManager.SetShowDockingContextStickers(!m_paneManager.IsShowDockingContextStickers());
}
void CMainFrame::OnUpdateDockingStickers(CCmdUI *pCmdUI)
{
	if (m_paneManager.IsAlphaDockingContext())
	{
		pCmdUI->SetCheck(m_paneManager.IsShowDockingContextStickers()? TRUE: FALSE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnMinMaxSamlpe()
{
	m_bMinMaxSample = !m_bMinMaxSample;

	if (m_bMinMaxSample)
	{
		CXTPDockingPane* pPane = m_paneManager.FindPane(IDR_PANE1);
		ASSERT(pPane);
		pPane->SetMinTrackSize(CSize(100, 100));
		pPane->SetMaxTrackSize(CSize(150, 150));

		pPane = m_paneManager.FindPane(IDR_PANE2);
		ASSERT(pPane);
		pPane->SetMinTrackSize(CSize(130, 130));
		pPane->SetMaxTrackSize(CSize(130, 130));
	}
	else
	{
		CXTPDockingPane* pPane = m_paneManager.FindPane(IDR_PANE1);
		ASSERT(pPane);
		pPane->SetMinTrackSize(CSize(0, 0));
		pPane->SetMaxTrackSize(CSize(32000, 32000));

		pPane = m_paneManager.FindPane(IDR_PANE2);
		ASSERT(pPane);
		pPane->SetMinTrackSize(CSize(0, 0));
		pPane->SetMaxTrackSize(CSize(32000, 32000));
	}

	for (int i = 0; i < sizeof(m_wndPanes) / sizeof(m_wndPanes[0]); i++)
	{
		if (m_wndPanes[i].m_hWnd)
		{
			m_wndPanes[i].OnSize(0, 0, 0);
			m_wndPanes[i].RedrawWindow();

		}
	}
	m_paneManager.RedrawPanes();
}

void CMainFrame::OnUpdateMinMaxSamlpe(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bMinMaxSample);
}





void CMainFrame::OnLoadFromFile()
{
	CXTPDockingPaneLayout* pLayout = m_bEditor? m_pEditorLayout: m_pRunLayout;

	CString strFilter = _T("XML Document(*.xml)|*.xml|All files (*.*)|*.*||");
	CFileDialog fd(TRUE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST, strFilter);
	if (fd.DoModal() == IDOK)
	{
#ifndef _XTP_EXCLUDE_XML
		if (pLayout->LoadFromFile(fd.GetPathName(), _T("Common")))
		{
			m_paneManager.SetLayout(pLayout);
		}
#else
		CFile file(fd.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);

		pLayout->Serialize(ar);
		if (pLayout->IsValid())
		{
			m_paneManager.SetLayout(pLayout);
		}

#endif
	}
}

void CMainFrame::OnSaveToFile()
{
	CXTPDockingPaneLayout* pLayout = m_bEditor? m_pEditorLayout: m_pRunLayout;

	CString strFilter = _T("XML Document(*.xml)|*.xml|All files (*.*)|*.*||");
	CFileDialog fd(FALSE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() == IDOK)
	{
#ifndef _XTP_EXCLUDE_XML

		m_paneManager.GetLayout(pLayout);
		pLayout->SaveToFile(fd.GetPathName(), _T("Common"));
#else
		m_paneManager.GetLayout(pLayout);
		CFile file(fd.GetPathName(), CFile::modeCreate|CFile::modeWrite);
		CArchive ar(&file, CArchive::store);

		pLayout->Serialize(ar);

#endif
	}

}

void CMainFrame::OnLoadFromResource()
{

#ifndef _XTP_EXCLUDE_XML

	LPCTSTR lpszResourceName = MAKEINTRESOURCE(IDR_SPIRAL);

	CXTPPropExchangeXMLNode px(TRUE, NULL, _T("DockingPaneLayouts"));

	if (px.LoadFromResource(AfxGetInstanceHandle(), lpszResourceName, RT_HTML))
	{
		CXTPDockingPaneLayout* pLayout = m_bEditor? m_pEditorLayout: m_pRunLayout;
		CXTPPropExchangeSection pxCommon(px.GetSection(_T("Common")));

		if (pLayout->DoPropExchange(&pxCommon))
		{
			m_paneManager.SetLayout(pLayout);
		}

	}

#endif

}


void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instanciate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_PaneTYPE);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_PaneTYPE);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
}

void CMainFrame::OnClose()
{
	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));
	CMDIFrameWnd::OnClose();
}



void CMainFrame::OnGetMinMaxInfo(LPMINMAXINFO pMinMaxInfo)
{
	CMDIFrameWnd::OnGetMinMaxInfo(pMinMaxInfo);

	if (m_bMinMaxSample)
	{
		CXTPWindowRect rcWindow(this);

		CRect rcTopPane= m_paneManager.GetTopPane()->GetPaneWindowRect();

		CSize szBorder = rcWindow.Size() - rcTopPane.Size();

		MINMAXINFO mmi;
		m_paneManager.GetTopPane()->GetMinMaxInfo(&mmi);

		pMinMaxInfo->ptMinTrackSize = CPoint(mmi.ptMinTrackSize) + szBorder;
	}
}


//////////////////////////////////////////////////////////////////////////
// CEditPane

CEditPane::CEditPane()
{
}

LRESULT CEditPane::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCPAINT && GetExStyle() & WS_EX_STATICEDGE)
	{
		CRect rc;
		GetWindowRect(&rc);
		CWindowDC dc(this);
		rc.OffsetRect(-rc.TopLeft());
		
		COLORREF clrFrame = ((CMainFrame*)AfxGetMainWnd())->m_paneManager.GetPaintManager()->GetXtremeColor(XPCOLOR_FRAME);

		dc.Draw3dRect(rc, clrFrame, clrFrame);
		return TRUE;
	}
	return CXTPEdit::WindowProc(message, wParam, lParam);
}


BEGIN_MESSAGE_MAP(CEditPane, CXTPEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

HBRUSH CEditPane::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	static CBrush brush(RGB(0xFF, 230, 191));

	pDC->SetBkMode(TRANSPARENT);

	if (!m_bMinMaxSample)
		return GetSysColorBrush(COLOR_WINDOW);

	CXTPDockingPaneManager& paneManager = ((CMainFrame*)AfxGetMainWnd())->m_paneManager;

	CXTPDockingPane* pPane = paneManager.FindPane(GetDlgCtrlID());

	if (pPane)
	{
		MINMAXINFO mmi;
		pPane->GetMinMaxInfo(&mmi);

		if (mmi.ptMinTrackSize.x > 0)
		{
			return brush;
		}
	}
	return GetSysColorBrush(COLOR_WINDOW);
}

void CEditPane::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);

	if (!m_bMinMaxSample || (cx == 0 && cy == 0))
		return;
	CXTPDockingPaneManager& paneManager = ((CMainFrame*)AfxGetMainWnd())->m_paneManager;

	CXTPDockingPane* pPane = paneManager.FindPane(GetDlgCtrlID());

	if (pPane)
	{
		MINMAXINFO mmi;
		pPane->GetMinMaxInfo(&mmi);

		CString strInfo;

		if (mmi.ptMinTrackSize.x > 0)
		{
			CXTPWindowRect rc(this);

			strInfo.Format(_T("Tracking Size:\r\nMin (%i, %i)\r\nMax (%i, %i)\r\nCurrent (%i, %i)"),
				mmi.ptMinTrackSize.x, mmi.ptMinTrackSize.y, mmi.ptMaxTrackSize.x, mmi.ptMaxTrackSize.y, rc.Width(), rc.Height());
		}
		SetWindowText(strInfo);
	}
}


void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{

	// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);


// Toggle Docking Panes.
	m_paneManager.OnSetPreviewMode(bPreview);


	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}


void CMainFrame::SwitchDefaultPaneOptions(XTPDockingPaneOptions dwOption)
{
	DWORD dwOptions = m_paneManager.GetDefaultPaneOptions();

	m_paneManager.SetDefaultPaneOptions(dwOptions & dwOption? dwOptions & ~dwOption: dwOptions | dwOption);
	m_paneManager.RecalcFramesLayout();
}

void CMainFrame::OnCaptionButtonClose()
{
	SwitchDefaultPaneOptions(xtpPaneNoCloseable);
}

void CMainFrame::OnUpdateCaptionButtonClose(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetDefaultPaneOptions() & xtpPaneNoCloseable? FALSE: TRUE);

}

void CMainFrame::OnCaptionButtonAutoHide()
{
	SwitchDefaultPaneOptions(xtpPaneNoHideable);

}

void CMainFrame::OnUpdateCaptionButtonAutoHide(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetDefaultPaneOptions() & xtpPaneNoHideable? FALSE: TRUE);
}

void CMainFrame::OnCaptionButtonMenu()
{
	SwitchDefaultPaneOptions(xtpPaneHasMenuButton);

}

void CMainFrame::OnUpdateCaptionButtonMenu(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetDefaultPaneOptions() & xtpPaneHasMenuButton? TRUE: FALSE);
}

void CMainFrame::OnCaptionButtonMaximize()
{
	m_paneManager.ShowCaptionMaximizeButton(!m_paneManager.IsCaptionMaximizeButtonsVisible());
}

void CMainFrame::OnUpdateCaptionButtonMaximize(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsCaptionMaximizeButtonsVisible()? TRUE: FALSE);

}

void CMainFrame::OnCaptionVisible()
{
	m_paneManager.GetPaintManager()->m_bShowCaption = !m_paneManager.GetPaintManager()->m_bShowCaption;
	m_paneManager.RedrawPanes();
}

void CMainFrame::OnCaptionHorizontal()
{
	m_paneManager.SetCaptionDirection(xtpPaneCaptionHorizontal);
}

void CMainFrame::OnCaptionVertical()
{
	m_paneManager.SetCaptionDirection(xtpPaneCaptionVertical);
}

void CMainFrame::OnCaptionAutoBySize()
{
	m_paneManager.SetCaptionDirection(xtpPaneCaptionAutoBySize);
}

void CMainFrame::OnCaptionAutoByPosition()
{
	m_paneManager.SetCaptionDirection(xtpPaneCaptionAutoByPosition);
}

void CMainFrame::OnUpdateCaptionVisible(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetPaintManager()->m_bShowCaption? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionHorizontal(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetCaptionDirection() == xtpPaneCaptionHorizontal? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionVertical(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetCaptionDirection() == xtpPaneCaptionVertical? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionAutoBySize(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetCaptionDirection() == xtpPaneCaptionAutoBySize? TRUE: FALSE);
}

void CMainFrame::OnUpdateCaptionAutoByPosition(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetCaptionDirection() == xtpPaneCaptionAutoByPosition? TRUE: FALSE);
}

void CMainFrame::OnCloseButtonAffects()
{
	m_paneManager.m_bCloseGroupOnButtonClick = !m_paneManager.m_bCloseGroupOnButtonClick;
}

void CMainFrame::OnAutoHideButtonAffects()
{
	m_paneManager.m_bHideGroupOnButtonClick = !m_paneManager.m_bHideGroupOnButtonClick;
}

void CMainFrame::OnUpdateCloseButtonAffects(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.m_bCloseGroupOnButtonClick? FALSE: TRUE);
}

void CMainFrame::OnUpdateAutoHideButtonAffects(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.m_bHideGroupOnButtonClick? FALSE: TRUE);
}


void CMainFrame::OnUpdateShowContentsWhileDragging(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetShowContentsWhileDragging()? TRUE: FALSE);
}

void CMainFrame::OnShowContentsWhileDragging()
{
	m_paneManager.SetShowContentsWhileDragging(!m_paneManager.GetShowContentsWhileDragging());
}

void CMainFrame::OnStickyFloatingFrames()
{
	m_paneManager.SetStickyFloatingFrames(!m_paneManager.IsStickyFloatingFrames());
}

void CMainFrame::OnUpdateStickyFloatingFrames(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsStickyFloatingFrames() ? TRUE: FALSE);
}

void CMainFrame::OnTransparentFloatingFrames()
{
	m_paneManager.SetFloatingFramesOpacity(m_paneManager.GetFloatingFramesOpacity() != 255 ? 255 : 200);
}

void CMainFrame::OnUpdateTransparentFloatingFrames(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.GetFloatingFramesOpacity() != 255);
}

void CMainFrame::OnEnableSideDocking()
{
	m_paneManager.EnableSideDocking(!m_paneManager.IsSideDockingEnabled());
}

void CMainFrame::OnUpdateEnableSideDocking(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_paneManager.IsSideDockingEnabled());
}
