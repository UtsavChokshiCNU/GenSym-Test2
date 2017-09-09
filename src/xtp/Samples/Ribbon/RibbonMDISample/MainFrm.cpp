// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RibbonMDISample.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
	ON_COMMAND(ID_VIEW_NORMAL, OnViewNormal)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMAL, OnUpdateViewNormal)
	ON_COMMAND(ID_WINDOW_ARRANGE, OnWindowArrange)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_SWITCH, OnUpdateWindowSwitch)

	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(XTP_ID_RIBBONCONTROLTAB, OnUpdateRibbonTab)

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_COMMAND(XTP_ID_RIBBONCUSTOMIZE, OnCustomizeQuickAccess)

	ON_COMMAND(ID_OPTIONS_RIGHTTOLEFT, OnOptionsRighttoleft)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_RIGHTTOLEFT, OnUpdateOptionsRighttoleft)
	
	ON_COMMAND_RANGE(ID_OPTIONS_STYLEBLUE, ID_OPTIONS_STYLEAQUA, OnOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLEBLUE, ID_OPTIONS_STYLEAQUA, OnUpdateOptionsStyle)


END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nRibbonStyle = ID_OPTIONS_STYLEBLUE;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();

	XTPPaintManager()->SetTheme(xtpThemeRibbon);
	
	m_wndStatusBar.SetDrawDisabledText(FALSE);
	m_wndStatusBar.SetCommandBars(pCommandBars);
	m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(22);
	m_wndStatusBar.GetPane(0)->SetMargins(8, 1, 2, 1);

	//////////////////////////////////////////////////////////////////////////	
	// IMPORTANT:
	// Ribbon bitmaps resources by default located in application executable. 
	//
	// You also can specify handle to find ribbon resources:
	//((CXTPOffice2007Theme*)XTPPaintManager())->SetImageHandle(hHandle);

	//HMODULE hModule = LoadLibrary(m_csStylesPath + _T("Office2007.dll"));
	//((CXTPOffice2007Theme*)pCommandBars->GetPaintManager())->SetImageHandle(hModule);

	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(xtpToolTipResource);
	pToolTipContext->ShowTitleAndDescription();
	pToolTipContext->SetMargin(CRect(2, 2, 2, 2));
	pToolTipContext->SetMaxTipWidth(180);
	pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());

	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
	pCommandBars->GetCommandBarsOptions()->bToolBarAccelTips = TRUE;

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	LoadIcons();

	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon\n");
		return -1;
	}

	m_wndClient.Attach(this, FALSE);
	m_wndClient.GetToolTipContext()->SetStyle(xtpToolTipResource);

	m_bShowWorkspace = TRUE;

	LoadCommandBars(_T("CommandBars"));


	return 0;
}

void CMainFrame::LoadIcons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->GetImageManager()->SetIcons(IDR_SMALLICONS);
	pCommandBars->GetImageManager()->SetIcons(IDR_LARGEICONS);

	UINT uiGroupClipboard[] = {ID_EDIT_PASTE, ID_EDIT_CUT, ID_EDIT_COPY, ID_FORMAT_PAINTER};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_CLIPBOARD, uiGroupClipboard, _countof(uiGroupClipboard), CSize(16, 16));

	UINT uiGroupFind[] = {ID_EDIT_FIND, ID_EDIT_REPLACE, ID_EDIT_GOTO, ID_EDIT_SELECT};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_EDITING, uiGroupFind, _countof(uiGroupFind), CSize(16, 16));

	UINT uCommand = {IDB_GEAR};
	pCommandBars->GetImageManager()->SetIcons(IDB_GEAR, &uCommand, 1, CSize(0, 0), xtpImageNormal);


}

//#define CREATE_FROM_XML

BOOL CMainFrame::CreateRibbonBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CMenu menu;
	menu.Attach(::GetMenu(m_hWnd));
	SetMenu(NULL);

#ifndef CREATE_FROM_XML
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)pCommandBars->Add(_T("The Ribbon"), xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));
	if (!pRibbonBar)
	{
		return FALSE;
	}


	pRibbonBar->EnableDocking(0);

	CXTPControlPopup* pControlFile = (CXTPControlPopup*)pRibbonBar->AddSystemButton(0);
	pControlFile->SetCommandBar(menu.GetSubMenu(0));
	
	pControlFile->SetIconId(IDB_GEAR);

	CXTPRibbonTab* pTabHome = pRibbonBar->AddTab(ID_TAB_HOME);

	CXTPRibbonGroup* pGroupFile = pTabHome->AddGroup(ID_GROUP_FILE);
	pGroupFile->Add(xtpControlButton, ID_FILE_NEW);
	pGroupFile->Add(xtpControlButton, ID_FILE_OPEN);
	pGroupFile->Add(xtpControlButton, ID_FILE_CLOSE);
	CXTPControlPopup* pControlSave = (CXTPControlPopup*)pGroupFile->Add(xtpControlSplitButtonPopup, ID_FILE_SAVE);
	pControlSave->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_FILE_SAVE);
	pControlSave->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_FILE_SAVE_AS);

	CXTPControlPopup* pControlPrint = (CXTPControlPopup*)pGroupFile->Add(xtpControlSplitButtonPopup, ID_FILE_PRINT);
	pControlPrint->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_FILE_PRINT);
	pControlPrint->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_FILE_PRINT_SETUP);
	pControlPrint->SetBeginGroup(TRUE);


	CXTPRibbonTab* pTabEdit = pRibbonBar->AddTab(ID_TAB_EDIT);


	CXTPRibbonGroup* pGroupClipborad = pTabEdit->AddGroup(ID_GROUP_CLIPBOARD);
	pGroupClipborad->ShowOptionButton();
	
	CXTPControlPopup* pControlPaste = (CXTPControlPopup*)pGroupClipborad->Add(xtpControlSplitButtonPopup, ID_EDIT_PASTE);
	pControlPaste->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_PASTE);
	pControlPaste->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_PASTE_SPECIAL);
	pGroupClipborad->Add(xtpControlButton, ID_EDIT_CUT);
	pGroupClipborad->Add(xtpControlButton, ID_EDIT_COPY);	
	pGroupClipborad->Add(xtpControlButton, ID_FORMAT_PAINTER);

	CXTPRibbonGroup* pGroupEditing = pTabEdit->AddGroup(ID_GROUP_EDITING);
	pGroupEditing->Add(xtpControlButton, ID_EDIT_FIND);
	pGroupEditing->Add(xtpControlButton, ID_EDIT_REPLACE);
	pGroupEditing->Add(xtpControlButton, ID_EDIT_GOTO);
	CXTPControlPopup* pControlSelect = (CXTPControlPopup*)pGroupEditing->Add(xtpControlPopup, ID_EDIT_SELECT);
	pControlSelect->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_SELECT_ALL);
	pControlSelect->SetFlags(xtpFlagManualUpdate);
	

	
	
	CXTPRibbonTab* pTabView = pRibbonBar->AddTab(ID_TAB_VIEW);

	CXTPRibbonGroup* pGroupDocumentView = pTabView->AddGroup(ID_GROUP_DOCUMENTVIEWS);
	pGroupDocumentView->Add(xtpControlButton, ID_VIEW_NORMAL);
	pGroupDocumentView->Add(xtpControlButton, ID_FILE_PRINT_PREVIEW);
	pGroupDocumentView->Add(xtpControlButton, ID_VIEW_FULLSCREEN);

	CXTPRibbonGroup* pGroupShowHide = pTabView->AddGroup(ID_GROUP_SHOWHIDE);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_STATUS_BAR);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_WORKSPACE);

	CXTPRibbonGroup* pGroupWindow = pTabView->AddGroup(ID_GROUP_WINDOW);
	pGroupWindow->Add(xtpControlButton, ID_WINDOW_NEW);
	pGroupWindow->Add(xtpControlButton, ID_WINDOW_ARRANGE);
	CXTPControlPopup* pControlSwitchWindows = (CXTPControlPopup*)pGroupWindow->Add(xtpControlPopup, ID_WINDOW_SWITCH);
	pControlSwitchWindows->GetCommandBar()->GetControls()->Add(xtpControlButton, XTP_ID_WINDOWLIST);


	CXTPControlPopup* pControlOptions = (CXTPControlPopup*)pRibbonBar->GetControls()->Add(xtpControlPopup, -1);
	pControlOptions->SetFlags(xtpFlagRightAlign);
	CMenu mnuOptions;
	mnuOptions.LoadMenu(IDR_MENU_OPTIONS);
	pControlOptions->SetCommandBar(mnuOptions.GetSubMenu(0));
	pControlOptions->SetCaption(_T("Options"));

	CXTPControl* pControlAbout = pRibbonBar->GetControls()->Add(xtpControlButton, ID_APP_ABOUT);
	pControlAbout->SetFlags(xtpFlagRightAlign);

	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_SAVE);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_EDIT_UNDO);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_PRINT);
	pRibbonBar->GetQuickAccessControls()->CreateOriginalControls();

#else
	CXTPPropExchangeXMLNode px(TRUE, 0, _T("Settings"));

	if (px.LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_LAYOUT), RT_HTML))
	{
		CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; 
		param.bSerializeControls = TRUE;
		GetCommandBars()->DoPropExchange(&pxCommandBars, &param);
	}
	else
	{
		AfxMessageBox(_T("Can't load Layout"));
		return FALSE;
	}
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();
	pRibbonBar->EnableCustomization(FALSE);

	pRibbonBar->GetQuickAccessControls()->SetOriginalControls(new CXTPOriginalControls());
	pRibbonBar->GetQuickAccessControls()->GetOriginalControls()->Add(xtpControlButton, ID_FILE_SAVE);
	pRibbonBar->GetQuickAccessControls()->GetOriginalControls()->Add(xtpControlButton, ID_EDIT_UNDO);
	pRibbonBar->GetQuickAccessControls()->GetOriginalControls()->Add(xtpControlButton, ID_FILE_PRINT);

#endif


	pRibbonBar->EnableFrameTheme();
	return TRUE;
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

/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnUpdateRibbonTab(CCmdUI* pCmdUI)
{
	CXTPRibbonControlTab* pControl = DYNAMIC_DOWNCAST(CXTPRibbonControlTab, CXTPControl::FromUI(pCmdUI));
	if (!pControl)
		return;

	CXTPRibbonTab* pTab = pControl->FindTab(ID_TAB_EDIT);
	if (!pTab)
		return;

	pTab->SetVisible(MDIGetActive() != NULL);
}

void CMainFrame::OnViewFullscreen() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewNormal() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateViewNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(1);	
}

void CMainFrame::OnWindowArrange() 
{
	::SendMessage(m_hWndMDIClient, WM_MDITILE, MDITILE_HORIZONTAL, 0);

	
}

void CMainFrame::OnUpdateWindowSwitch(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(MDIGetActive() != NULL ? TRUE : FALSE);
	
}

void CMainFrame::OnViewWorkspace()
{
	m_bShowWorkspace ^= 1;
	m_wndClient.ShowWorkspace(m_bShowWorkspace);
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowWorkspace);
}

void CMainFrame::OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState)
{
// Toggle CommandBars
	GetCommandBars()->OnSetPreviewMode(bPreview);

// Toggle Tab Client
	m_wndClient.ShowWorkspace(!bPreview);

	CMDIFrameWnd::OnSetPreviewMode(bPreview, pState);
}

void CMainFrame::OnClose() 
{	
/*	CXTPPropExchangeXMLNode px(FALSE, 0, _T("Settings"));

	if (px.OnBeforeExchange()) 
	{
		CXTPPropExchangeSection pxCommandBars(px.GetSection(_T("CommandBars")));
		XTP_COMMANDBARS_PROPEXCHANGE_PARAM param; 
		param.bSerializeControls = TRUE; 
		param.bSaveOriginalControls = FALSE;
		param.bSerializeOptions = TRUE;
		GetCommandBars()->DoPropExchange(&pxCommandBars, &param);

		px.SaveToFile(_T("C:\\save.xml"));
	}*/

	SaveCommandBars(_T("CommandBars"));

	
	CXTPMDIFrameWnd::OnClose();
}

void CMainFrame::ShowCustomizeDialog(int nSelectedPage)
{
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPRibbonCustomizeQuickAccessPage pageQuickAccess(&cs);
	cs.AddPage(&pageQuickAccess);
	pageQuickAccess.AddCategories(IDR_MAINFRAME);

	CXTPCustomizeKeyboardPage pageKeyboard(&cs);
	cs.AddPage(&pageKeyboard);
	pageKeyboard.AddCategories(IDR_MAINFRAME);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_MAINFRAME);

	cs.SetActivePage(nSelectedPage);

	cs.DoModal();
}

void CMainFrame::OnCustomize()
{
	ShowCustomizeDialog(0);
}

void CMainFrame::OnCustomizeQuickAccess()
{
	ShowCustomizeDialog(2);
}




void CMainFrame::OnOptionsRighttoleft() 
{
	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		GetCommandBars()->SetLayoutRTL(FALSE);
		ModifyStyleEx(WS_EX_LAYOUTRTL, 0);
		m_wndClient.SetLayoutRTL(FALSE);
	}
	else
	{
		GetCommandBars()->SetLayoutRTL(TRUE);
		ModifyStyleEx(0, WS_EX_LAYOUTRTL);
		m_wndClient.SetLayoutRTL(TRUE);
	}	

}

void CMainFrame::OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI) 
{
	if (XTPSystemVersion()->IsLayoutRTLSupported())
	{
		pCmdUI->SetCheck(GetExStyle() & WS_EX_LAYOUTRTL ? TRUE : FALSE);	
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateOptionsStyle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonStyle ? 1 : 0);

}
void CMainFrame::OnOptionsStyle(UINT nStyle)
{
	HMODULE hModule = AfxGetInstanceHandle();

	LPCTSTR lpszIniFile = 0;
	switch (nStyle)
	{
		case ID_OPTIONS_STYLEBLUE: 
			lpszIniFile = _T("OFFICE2007BLUE.INI"); break;
		case ID_OPTIONS_STYLEBLACK: 
			lpszIniFile = _T("OFFICE2007BLACK.INI"); break;
		case ID_OPTIONS_STYLEAQUA: 
			lpszIniFile = _T("OFFICE2007AQUA.INI"); break;
		case ID_OPTIONS_STYLESILVER: 
			lpszIniFile = _T("OFFICE2007SILVER.INI"); break;
	}


	((CXTPOffice2007Theme*)GetCommandBars()->GetPaintManager())->SetImageHandle(hModule, lpszIniFile);

	GetCommandBars()->GetImageManager()->RefreshAll();
	GetCommandBars()->RedrawCommandBars();
	SendMessage(WM_NCPAINT);

	m_wndClient.GetPaintManager()->RefreshMetrics();

	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);


	m_nRibbonStyle = nStyle;
}


