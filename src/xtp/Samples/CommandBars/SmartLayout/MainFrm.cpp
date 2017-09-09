// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SmartLayout.h"

#include "MainFrm.h"
#include "ControlSelector.h"

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
	ON_COMMAND(ID_VIEW_THEME_OFFICE2003, OnViewThemeOffice2003)
	ON_COMMAND(ID_VIEW_THEME_OFFICE2000, OnViewThemeOffice2000)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_OFFICE2000, OnUpdateViewThemeOffice2000)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THEME_OFFICE2003, OnUpdateViewThemeOffice2003)
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_XTP_AFTERCREATECONTROL()
	ON_XTP_CREATECONTROL()
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
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create Status bar.
	// Important: All control bars including the Status Bar
	// must be created before CommandBars....
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
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_STANDARDBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pToolBar->EnableDocking(xtpFlagAlignAny | xtpFlagFloating | xtpFlagHideWrap | xtpFlagSmartLayout);

	// Create ToolBar
	CXTPToolBar* pFormatBar = (CXTPToolBar*)
		pCommandBars->Add(_T("Format"), xtpBarTop);
	if (!pFormatBar || !pFormatBar->LoadToolBar(IDR_FORMATBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pFormatBar->EnableDocking(xtpFlagAlignAny | xtpFlagFloating | xtpFlagHideWrap | xtpFlagSmartLayout);
	
	pFormatBar->GetControls()->FindControl(ID_BDR_NONE)->SetHideFlags(xtpHideCustomize);
	pFormatBar->GetControls()->CreateOriginalControls();

	pCommandBars->GetImageManager()->SetIcons(IDB_LARGEICONS);

	UINT nCommands[] = {ID_EDIT_UNDO, ID_EDIT_REDO, ID_VIEW_MAP, ID_EDIT_COPY, ID_EDIT_CUT};
	pCommandBars->GetImageManager()->SetIcons(IDB_EDITUNDO, nCommands, _countof(nCommands), xtpImageNormal);

	UINT nCommands2[] = {ID_CHAR_BOLD, ID_CHAR_ITALIC, ID_CHAR_UNDERLINE, ID_BUTTON_TEXT, ID_PARA_LEFT, ID_PARA_CENTER, ID_PARA_RIGHT, ID_INSERT_BULLET, ID_FORMAT_FONT};
	pCommandBars->GetImageManager()->SetIcons(IDB_FORMATBARLARGE, nCommands2, _countof(nCommands2), xtpImageNormal);

	GetCommandBars()->GetImageManager()->RemoveIcon(ID_COMBO_FONT);
	GetCommandBars()->GetImageManager()->RemoveIcon(ID_COMBO_SIZE);

	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, AFX_IDW_PANE_FIRST);
	CXTPWindowRect rcBar(pToolBar);
	rcBar.OffsetRect(470, 0);	
	GetCommandBars()->DockCommandBar(pFormatBar, rcBar, pToolBar->GetDockBar());

	// Set Office 2003 Theme
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));


	return 0;
}

void CMainFrame::OnClose()
{
	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));
	RecalcLayout();

	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instanciate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the keyboard page to the customize dialog.
		CXTPCustomizeKeyboardPage pageKeyboard(&dlg);
		dlg.AddPage(&pageKeyboard);
		pageKeyboard.AddCategories(IDR_SMARTLTYPE);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_SMARTLTYPE);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_SMARTLTYPE);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
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

void CMainFrame::OnAfterCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	lpCreateControl;
}

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	CXTPToolBar* pToolBar = lpCreateControl->bToolBar? DYNAMIC_DOWNCAST(CXTPToolBar, lpCreateControl->pCommandBar): NULL;

	if (lpCreateControl->nID == ID_COMBO_FONT && pToolBar && pToolBar->GetBarID() == IDR_FORMATBAR)
	{
		CXTPControlComboBox* pComboFont = new CXTPControlFontComboBox();
		pComboFont->SetDropDownListStyle();

		lpCreateControl->pControl = pComboFont;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_BDR_NONE && pToolBar)
	{
		CXTPControlPopup* pPopup = CXTPControlPopup::CreateControlPopup(xtpControlSplitButtonPopup);

		CXTPPopupToolBar* pPopupBar = CXTPPopupToolBar::CreatePopupToolBar(GetCommandBars());

		pPopupBar->LoadToolBar(IDR_BORDERS);
		pPopupBar->SetWidth(52 * 5 + 6);
		pPopupBar->SetTearOffPopup(_T("Borders"), IDR_BORDERS, 52 * 5 + 6);

		pPopup->SetCommandBar(pPopupBar);
		pPopupBar->InternalRelease();

		lpCreateControl->pControl = pPopup;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_COMBO_SIZE && pToolBar && pToolBar->GetBarID() == IDR_FORMATBAR)
	{
		CXTPControlComboBox* pComboSize = new CXTPControlSizeComboBox();
		pComboSize->SetDropDownListStyle();
		pComboSize->SetWidth(80);

		lpCreateControl->pControl = pComboSize;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_BUTTON_TEXT && pToolBar && pToolBar->GetBarID() == IDR_FORMATBAR)
	{
		CXTPControlPopupColor* pPopupColor = new CXTPControlPopupColor();

		CXTPPopupBar* pColorBar = (CXTPPopupBar*)CXTPPopupToolBar::CreateObject();

		CXTPControlButtonColor* pButtonAutomatic = (CXTPControlButtonColor*)pColorBar->GetControls()->Add(new CXTPControlButtonColor(), XTP_IDS_AUTOMATIC);
		pButtonAutomatic->SetColor(GetSysColor(COLOR_BTNTEXT));

		pColorBar->GetControls()->Add(new CXTPControlColorSelector(), ID_SELECTOR_TEXT);
		pColorBar->GetControls()->Add(new CXTPControlButtonColor(), XTP_IDS_MORE_COLORS);

		pPopupColor->SetCommandBar(pColorBar);

		pColorBar->SetTearOffPopup(_T("Text Color"), IDR_COLORTEXT_POPUP, 0);
		pColorBar->EnableCustomization(FALSE);

		pColorBar->InternalRelease();

		lpCreateControl->pControl = pPopupColor;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_EDIT_UNDO && pToolBar)
	{
		CXTPControlPopup* pButtonUndo = CXTPControlPopup::CreateControlPopup(xtpControlSplitButtonPopup);

		CXTPPopupToolBar* pUndoBar = CXTPPopupToolBar::CreatePopupToolBar(GetCommandBars());
		pUndoBar->EnableCustomization(FALSE);
		pUndoBar->SetBorders(CRect(2, 2, 2, 2));
		pUndoBar->DisableShadow();


		CXTPControlListBox* pControlListBox = (CXTPControlListBox*)pUndoBar->GetControls()->Add(new CXTPControlListBox(), ID_EDIT_UNDO);
		pControlListBox->SetWidth(140);
		pControlListBox->SetLinesMinMax(1, 6);
		pControlListBox->SetMultiplSel(TRUE);

		CXTPControlStatic* pControlListBoxInfo = (CXTPControlStatic*)pUndoBar->GetControls()->Add(new CXTPControlStatic(), ID_EDIT_UNDO);
		pControlListBoxInfo->SetWidth(140);


		pButtonUndo->SetCommandBar(pUndoBar);
		pUndoBar->InternalRelease();

		lpCreateControl->pControl = pButtonUndo;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_INSERT_COLUMNS)
	{
		CXTPControlPopup* pButtonColumns = CXTPControlPopup::CreateControlPopup(xtpControlPopup);

		CXTPPopupToolBar* pColumnsBar = CXTPPopupToolBar::CreatePopupToolBar(GetCommandBars());
		pColumnsBar->EnableCustomization(FALSE);
		pColumnsBar->SetBorders(CRect(2, 2, 2, 2));

		pColumnsBar->DisableShadow();


		pColumnsBar->GetControls()->Add(new CControlColumns(), ID_INSERT_COLUMNS);


		CXTPControlStatic* pControlColumnsInfo = (CXTPControlStatic*)pColumnsBar->GetControls()->Add(new CXTPControlStatic(), ID_INSERT_COLUMNS);
		pControlColumnsInfo->SetFlags(xtpFlagManualUpdate);

		pButtonColumns->SetCommandBar(pColumnsBar);
		pColumnsBar->InternalRelease();

		lpCreateControl->pControl = pButtonColumns;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_INSERT_TABLE)
	{
		CXTPControlPopup* pButtonTable = CXTPControlPopup::CreateControlPopup(xtpControlPopup);

		CXTPPopupToolBar* pTableBar = CXTPPopupToolBar::CreatePopupToolBar(GetCommandBars());
		pTableBar->EnableCustomization(FALSE);
		pTableBar->SetBorders(CRect(2, 2, 2, 2));

		pTableBar->DisableShadow();


		pTableBar->GetControls()->Add(new CControlTable(), ID_INSERT_TABLE);


		CXTPControlStatic* pControlTableInfo = (CXTPControlStatic*)pTableBar->GetControls()->Add(new CXTPControlStatic(), ID_INSERT_TABLE);
		pControlTableInfo->SetFlags(xtpFlagManualUpdate);

		pButtonTable->SetCommandBar(pTableBar);
		pTableBar->InternalRelease();

		lpCreateControl->pControl = pButtonTable;
		return TRUE;

	}

	return FALSE;
}


void CMainFrame::OnViewThemeOffice2003() 
{
	XTPPaintManager()->SetTheme(xtpThemeOffice2003);
	GetCommandBars()->RedrawCommandBars();	
}

void CMainFrame::OnViewThemeOffice2000() 
{
	XTPPaintManager()->SetTheme(xtpThemeOffice2000);
	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateViewThemeOffice2000(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(XTPPaintManager()->GetCurrentTheme() == xtpThemeOffice2000);
	
}

void CMainFrame::OnUpdateViewThemeOffice2003(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(XTPPaintManager()->GetCurrentTheme() == xtpThemeOffice2003);
	
}
