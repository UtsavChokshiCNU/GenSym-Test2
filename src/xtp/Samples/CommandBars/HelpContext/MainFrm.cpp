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
#include "HelpContext.h"

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
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)

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

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	// Add the menu bar
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}
	pMenuBar->SetFlags(xtpFlagAddMDISysPopup);

	// Create ToolBar
	CXTPToolBar* pToolBar = (CXTPToolBar*)
		pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	if (pCommandBars->GetImageManager()->IsAlphaIconsSupported())
	{
		pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_TOOLBAR_SMALL_ALPHA);
		pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_TOOLBAR_LARGE_ALPHA);

		CXTPNativeXPTheme* pTheme = new CXTPNativeXPTheme;
		pTheme->m_bSelectImageInPopupBar = TRUE;
		pTheme->m_bThickCheckMark = TRUE;
		pTheme->GetIconsInfo()->bUseFadedIcons = FALSE;

		XTPPaintManager()->SetCustomTheme(pTheme);

		pCommandBars->GetCommandBarsOptions()->szLargeIcons = CSize(24, 24);
		pCommandBars->GetCommandBarsOptions()->bLargeIcons = TRUE;
	}
	else
	{
		CXTPPaintManager::SetCustomTheme(new COrangeTheme);
	}

	pCommandBars->GetCommandBarsOptions()->bShowTextBelowIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);

	pCommandBars->GetContextMenus()->Add(IDR_CONTEXT_MENU);


	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars2"));

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

void CMainFrame::OnClose()
{
	// Save the current state for command bars.
	SaveCommandBars(_T("CommandBars2"));
	// TODO: Add your message handler code here and/or call default

	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
	// get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;

	// instanciate the customize dialog
	CXTPCustomizeSheet dlg(pCommandBars);

	// add menus page to the customize dialog.
	CXTPCustomizeMenusPage pageMenus(&dlg);
	dlg.AddPage(&pageMenus);

	// add the options page to the customize dialog.
	CXTPCustomizeOptionsPage pageOptions(&dlg);
	dlg.AddPage(&pageOptions);

	// add the commands page to the customize dialog.
	CXTPCustomizeCommandsPage* pPageCommands = dlg.GetCommandsPage();
	pPageCommands->AddCategories(IDR_HELPCOTYPE);

	// initialize the commands page page.
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_HELPCOTYPE);
	pPageCommands->InsertNewMenuCategory();

	// display the customize dialog.
	dlg.DoModal();
}

/*
void CMainFrame::WinHelp(DWORD_PTR dwData, UINT nCmd)
{
	CWinApp* pApp = AfxGetApp();
	ASSERT_VALID(pApp);
	ASSERT(pApp->m_pszHelpFilePath != NULL);
	ASSERT(pApp->m_eHelpType == afxWinHelp);
	
	CWaitCursor wait;
	
	PrepareForHelp();
	
	// need to use top level parent (for the case where m_hWnd is in DLL)
	CWnd* pWnd = EnsureTopLevelParent();
	
	TRACE(traceAppMsg, 0, _T("WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n"), pApp->m_pszHelpFilePath, dwData, nCmd);
	
	// finally, run the Windows Help engine
	if (!::WinHelp(pWnd->m_hWnd, pApp->m_pszHelpFilePath, nCmd, dwData))
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_LAUNCH_HELP);
	}
}

*/

#if _MSC_VER <= 1200 // MFC 6.0 or earlier

HWND WINAPI XTPHtmlHelp(HWND hWnd, LPCTSTR szHelpFilePath, UINT nCmd, DWORD_PTR dwData)
{
#ifdef _UNICODE
#define _HTMLHELP_ENTRY "HtmlHelpW"
#else
#define _HTMLHELP_ENTRY "HtmlHelpA"
#endif

	typedef HWND (WINAPI HTMLHELPPROC)(HWND hwndCaller, LPCTSTR pszFile, UINT uCommand, DWORD_PTR dwData);

	
	static HTMLHELPPROC* pfnHtmlHelp = (HTMLHELPPROC*)0;

	// check if the HtmlHelp library was loaded
	if (!pfnHtmlHelp)
	{
		// load the library
		HMODULE hInstHtmlHelp = LoadLibraryA("hhctrl.ocx");
		if (!hInstHtmlHelp)
			return NULL;
		pfnHtmlHelp = (HTMLHELPPROC *) GetProcAddress(hInstHtmlHelp, _HTMLHELP_ENTRY);
		if (!pfnHtmlHelp)
		{
			FreeLibrary(hInstHtmlHelp);
			pfnHtmlHelp = NULL;
			return NULL;
		}
	}
	// now call it
	return (*(pfnHtmlHelp))(hWnd, szHelpFilePath, nCmd, dwData);
}

#define HH_HELP_CONTEXT         0x000F  // display mapped numeric value in dwData
#define HH_DISPLAY_TOC          0x0001  
#define HH_HELP_FINDER          0x0000  // WinHelp equivalent

void CMainFrame::WinHelp(DWORD dwData, UINT nCmd)
{
	CWinApp* pApp = AfxGetApp();
	ASSERT_VALID(pApp);
	ASSERT(pApp->m_pszHelpFilePath != NULL);
	
	CWaitCursor wait;
	if (IsFrameWnd())
	{
		// CFrameWnd windows should be allowed to exit help mode first
		CFrameWnd* pFrameWnd = (CFrameWnd*)this;
		pFrameWnd->ExitHelpMode();
	}
	
	// cancel any tracking modes
	SendMessage(WM_CANCELMODE);
	SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);
	
	// need to use top level parent (for the case where m_hWnd is in DLL)
	CWnd* pWnd = GetTopLevelParent();
	pWnd->SendMessage(WM_CANCELMODE);
	pWnd->SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);
	
	// attempt to cancel capture
	HWND hWndCapture = ::GetCapture();
	if (hWndCapture != NULL)
		::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);
	
	TRACE3("WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n",
		pApp->m_pszHelpFilePath, dwData, nCmd);
	
	// finally, run the Windows Help engine

	if (nCmd == HELP_CONTEXT)
		nCmd = HH_HELP_CONTEXT;
	else if (nCmd == HELP_CONTENTS)
		nCmd = HH_DISPLAY_TOC;
	else if (nCmd == HELP_FINDER)
		nCmd = HH_HELP_FINDER;


	if (!XTPHtmlHelp(pWnd->m_hWnd, pApp->m_pszHelpFilePath, nCmd, dwData))
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_LAUNCH_HELP);
	}

}

#endif
