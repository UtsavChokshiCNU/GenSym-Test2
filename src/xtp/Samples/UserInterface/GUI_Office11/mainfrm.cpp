// mainfrm.cpp : implementation of the CMainFrame class
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

#include "wordpad.h"
#include "mainfrm.h"
#include "Galleryitems.h"
#include "wordpdoc.h"
#include "wordpvw.h"
#include "strings.h"
#include "colorlis.h"

#include "ControlSelector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_COMMAND(ID_HELP, OnHelpFinder)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_CHAR_COLOR, OnCharColor)
	ON_COMMAND(ID_PEN_TOGGLE, OnPenToggle)
	ON_WM_FONTCHANGE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_DEVMODECHANGE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_QUICK_PRINT, OnFileQuickPrint)
	ON_COMMAND(ID_FILE_SAVE_AS_OPEN_DOC_TXT, OnFileSaveAsOpenDocTxt)
	ON_COMMAND(ID_FILE_SAVE_AS_OPEN_XML, OnFileSaveAsOpenXml)
	ON_COMMAND(ID_FILE_SAVE_AS_PLAIN_TXT_DOC, OnFileSaveAsPlainTxtDoc)
	ON_COMMAND(ID_FILE_SAVE_AS_RICH_TXT, OnFileSaveAsRichTxt)
	ON_COMMAND(ID_FILE_ABOUT, OnFileAbout)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_COMMAND(ID_HELP_INDEX, OnHelpFinder)
	ON_COMMAND(ID_SEND_IN_EMAIL, OnSendInEmail)
	ON_COMMAND(ID_INSERT_PIC, OnInsertPicture)
	ON_COMMAND(ID_INSERT_PAINT_DRAWING, OnInsertDrawing)
	ON_COMMAND(ID_INSERT_DATETIME, OnInsertObject)
	ON_COMMAND(ID_INSERT_OBJECT, OnInsertDatetime)
	 
	ON_COMMAND(ID_VIEW_ZOOMIN, OnZoomIn)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnZoomOut)
	ON_COMMAND(ID_VIEW_HUNDRED_PERC, OnHundredPercent)
	
	ON_COMMAND(ID_VIEW_WORD_WRAP, OnDummyHandler)
	ON_COMMAND(ID_VIEW_WORD_WRAP_NO, OnDummyHandler)
	ON_COMMAND(ID_VIEW_WORD_WRAP_WINDOW, OnDummyHandler)
	ON_COMMAND(ID_VIEW_WORD_WRAP_RULER, OnDummyHandler)
	ON_COMMAND(ID_VIEW_MEASUREMENTS, OnDummyHandler)
	ON_COMMAND(IDS_INCHES, OnDummyHandler)
	ON_COMMAND(IDS_CENTIMETERS, OnDummyHandler)
	ON_COMMAND(IDS_POINTS, OnDummyHandler)
	ON_COMMAND(IDS_PICAS, OnDummyHandler)
	ON_COMMAND(ID_EDITING_REPLACE, OnDummyHandler)
	ON_COMMAND(ID_INSERT_COLUMNS, OnDummyHandler)

	ON_COMMAND(ID_EDITING_SELECT_ALL, OnDummyHandler)
	ON_COMMAND_RANGE(ID_THEME_OFFICE2000, ID_THEME_OFFICE2007, OnViewTheme)
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_OFFICE2000, ID_THEME_OFFICE2007, OnUpdateChangeThemes)

	//ON_COMMAND(ID_TEXT_COLOR, OnDummyHandler)

	
	//}}AFX_MSG_MAP
	// Global help commands
//  ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, OnHelpFinder)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORMATBAR, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RULER, OnUpdateControlBarMenu)
	ON_MESSAGE(WPM_BARSTATE, OnBarState)
	ON_REGISTERED_MESSAGE(CWordPadApp::m_nOpenMsg, OnOpenMsg)
	ON_COMMAND_EX(ID_VIEW_STATUS_BAR, OnBarCheck)
	ON_COMMAND_EX(ID_VIEW_TOOLBAR, OnBarCheck)
	ON_COMMAND_EX(ID_VIEW_FORMATBAR, OnBarCheck)
	ON_COMMAND_EX(ID_VIEW_RULER, OnBarCheck)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLEBLUE, ID_OPTIONS_STYLEWHITE, OnOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLEBLUE, ID_OPTIONS_STYLEWHITE, OnUpdateOptionsStyle)
	
	ON_COMMAND_RANGE(IDS_INCHES, IDS_PICAS, OnMeasurements)
	ON_UPDATE_COMMAND_UI_RANGE(IDS_PICAS, IDS_PICAS, OnUpdateMeasurements)
	ON_XTP_CREATECONTROL()
	ON_XTP_CREATECOMMANDBAR()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

	ON_COMMAND_RANGE(ID_BDR_OUTSIDE, ID_BDR_INSIDE_VERT, OnBorders)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BDR_OUTSIDE, ID_BDR_INSIDE_VERT, OnUpdateBorders)

	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)


	ON_XTP_EXECUTE(ID_GALLERY_COLORS, OnGalleryThemeColors)

END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

#define IDR_COLORTEXT_POPUP 1000

enum Borders {borderTop = 1, borderLeft = 2, borderRight = 4, borderBottom = 8, borderInsideVert = 16, borderInsideHorz = 32,
	borderOutside = borderBottom | borderTop | borderLeft | borderRight,
	borderInside = borderInsideVert | borderInsideHorz,
	borderAll = borderInside | borderOutside};



/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_hIconDoc = theApp.LoadIcon(IDI_ICON_DOC);
	m_hIconText = theApp.LoadIcon(IDI_ICON_TEXT);
	m_hIconWrite = theApp.LoadIcon(IDI_ICON_WRITE);
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		
	
	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}

	m_csStylesPath += csStylesPath + _T("\\Styles\\");

	m_nRibbonStyle = ID_OPTIONS_STYLEWHITE;
	m_dwBorders = 0;
	m_bIsRibbon = TRUE;
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	WNDCLASS wndcls;

	BOOL bRes = CFrameWnd::PreCreateWindow(cs);
	HINSTANCE hInst = AfxGetInstanceHandle();

	// see if the class already exists
	if (!::GetClassInfo(hInst, szWordPadClass, &wndcls))
	{
		// get default stuff
		::GetClassInfo(hInst, cs.lpszClass, &wndcls);
		wndcls.style &= ~(CS_HREDRAW|CS_VREDRAW);
		// register a new class
		wndcls.lpszClassName = szWordPadClass;
		wndcls.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
		ASSERT(wndcls.hIcon != NULL);
		if (!AfxRegisterClass(&wndcls))
			AfxThrowResourceException();
	}
	cs.lpszClass = szWordPadClass;
	CRect rect = theApp.m_rectInitialFrame;
	if (rect.Width() > 0 && rect.Height() > 0)
	{
		// make sure window will be visible
		CDisplayIC dc;
		CRect rectDisplay(0, 0, dc.GetDeviceCaps(HORZRES),
			dc.GetDeviceCaps(VERTRES));
		if (rectDisplay.PtInRect(rect.TopLeft()) &&
			rectDisplay.PtInRect(rect.BottomRight()))
		{
			cs.x = rect.left;
			cs.y = rect.top;
			cs.cx = rect.Width();
			cs.cy = rect.Height();
		}
	}
	return bRes;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!CreateStatusBar())
		return -1;

	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();

	EnableDocking(CBRS_ALIGN_ANY);

	if (!CreateRulerBar())
		return -1;

	CWnd* pView = GetDlgItem(AFX_IDW_PANE_FIRST);
	if (pView != NULL)
	{
		pView->SetWindowPos(&wndBottom, 0, 0, 0, 0,
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);
	}
	
	LoadIcons();
	CreateGalleries();
	EnableRibbonStyle();
	
	CXTPPaintManager::SetTheme(xtpThemeRibbon);


	return 0;
}
void CMainFrame::EnableNormalStyle()
{

	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->GetCommandBarsOptions()->bShowKeyboardTips = FALSE;


	pCommandBars->RemoveAll();
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagIgnoreSetMenuMessage);
	if (!CreateToolBars())
		return ;
	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(xtpToolTipOffice);
	pToolTipContext->ShowTitleAndDescription(FALSE);
	pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());
	pToolTipContext->SetDelayTime(TTDT_INITIAL, 900);

}
void CMainFrame::EnableRibbonStyle()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();
	pCommandBars->RemoveAll();

	LoadIcons();

	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(xtpToolTipResource);
	pToolTipContext->ShowTitleAndDescription();
	pToolTipContext->ShowImage(FALSE, 0);
	pToolTipContext->SetMargin(CRect(2, 2, 2, 2));
	pToolTipContext->SetMaxTipWidth(180);
	pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());
	pToolTipContext->SetDelayTime(TTDT_INITIAL, 900);


	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon\n");
		return ;
	}

	CreateMiniToolBar();
	OnOptionsStyle(ID_OPTIONS_STYLESCENIC);

}
void CMainFrame::LoadIcons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME1, IDB_TOOLBAR_ALPHA);
	pCommandBars->GetImageManager()->SetIcons(IDB_FORMATBAR, IDB_FORMATBAR_ALPHA);
	pCommandBars->GetImageManager()->SetIcons(IDR_SMALLICONS);
	pCommandBars->GetImageManager()->SetIcons(IDR_LARGEICONS);
	pCommandBars->GetImageManager()->SetIcons(IDR_LAYOUTTABLARGE);
	pCommandBars->GetImageManager()->SetIcons(IDR_LAYOUTTABSMALL);

	UINT uiGroups[] = {ID_GROUP_CLIPBOARD, IDB_GROUP_FONT, ID_GROUP_PARAGRAPH, ID_GROUP_FIND}; 
	pCommandBars->GetImageManager()->SetIcons(IDB_BITMAPS_GROUPS, uiGroups, _countof(uiGroups), CSize(16, 16));



	UINT uiRibbonItemsLarge[] =
	
	{ID_FILE_NEW,
	ID_FILE_OPEN, 
	ID_FILE_SAVE, 
	ID_FILE_SAVE_AS,
	ID_FILE_SAVE_AS_RICH_TXT,
	ID_FILE_SAVE_AS_OPEN_XML,
	ID_FILE_SAVE_AS_OPEN_DOC_TXT,
	ID_FILE_SAVE_AS_PLAIN_TXT_DOC,
	ID_FILE_PRINT,
	ID_FILE_QUICK_PRINT,
	ID_PAGE_SETUP, 
	ID_FILE_PRINT_PREVIEW,
	ID_SEND_IN_EMAIL,
	ID_APP_ABOUT,
	ID_APP_EXIT,
	ID_EDIT_PASTE,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_INSERT_PIC,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_INSERT_PAINT_DRAWING,
	ID_INSERT_DATETIME,
	ID_INSERT_OBJECT,
	ID_EDITING_FIND,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_VIEW_ZOOM,
	ID_VIEW_ZOOMIN,
	ID_VIEW_ZOOMOUT,
	ID_VIEW_HUNDRED_PERC,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON


	}; 
	pCommandBars->GetImageManager()->SetIcons(IDB_PNG_WORDPAD_LARGE, uiRibbonItemsLarge, _countof(uiRibbonItemsLarge), CSize(32, 32));

	UINT uiRibbonItemsSmall[] = 

	{ID_FILE_NEW,
	ID_FILE_OPEN, 
	ID_FILE_SAVE, 
	ID_FILE_SAVE_AS,
	ID_FILE_SAVE_AS_RICH_TXT,
	ID_FILE_SAVE_AS_OPEN_XML,
	ID_FILE_SAVE_AS_OPEN_DOC_TXT,
	ID_FILE_SAVE_AS_PLAIN_TXT_DOC,
	ID_FILE_PRINT,
	ID_FILE_QUICK_PRINT,
	ID_PAGE_SETUP, 
	ID_FILE_PRINT_PREVIEW,
	ID_FILEPREPARE,
	ID_FILE_ABOUT,
	ID_SEND_IN_EMAIL,
	ID_APP_EXIT,
	ID_EDIT_PASTE_SPECIAL,
	ID_HOME_CUT,
	ID_HOME_COPY,
	ID_UNDO,
	ID_REDO,
	ID_REFRESH,
	ID_FONT_COLOR,
	ID_PARA_DECREASEINDENT,
	ID_PARA_INCREASEINDENT,
	ID_PARA_INSERT_BULLET,
	ID_PARA_LINESPACING,
	ID_PARA_LEFT,
	ID_PARA_ALIGN_CENTER,
	ID_PARA_ALIGN_RIGHT,
	ID_PARA_JUSTIFY,
	ID_PARA_SHOWMARKS,
	ID_DUMMY_ICON,
	ID_CHANGE_PIC,
	ID_RESIZE_PIC,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_EDITING_FIND,
	ID_EDITING_REPLACE,
	ID_EDITING_SELECT_ALL,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_DUMMY_ICON,
	ID_VIEW_WORD_WRAP,
	ID_VIEW_MEASUREMENTS


	}; 

	
	pCommandBars->GetImageManager()->SetIcons(IDB_PNG_WORDPAD_SMALL, uiRibbonItemsSmall, _countof(uiRibbonItemsSmall), CSize(16, 16));

	UINT uiGroupFont[] = {ID_FONT_GROW, ID_FONT_SHRINK, ID_FONT_CLEAR, ID_CHAR_BOLD, ID_CHAR_ITALIC, ID_CHAR_UNDERLINE,
		ID_CHAR_STRIKETHROUGH, ID_TEXT_SUBSCRIPT,ID_TEXT_SUPERSCRIPT, ID_TEXT_CHANGECASE, ID_TEXT_COLOR, ID_TEXT_HIGHLIGHTCOLOR};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_FONT, uiGroupFont, _countof(uiGroupFont), CSize(16, 16));

	pCommandBars->GetImageManager()->SetIcons(IDR_PNG_MAIN_BTN, 0, 0, CSize(16, 32));

}

BOOL CMainFrame::CreateMiniToolBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPMiniToolBar* pMiniToolBar = CXTPMiniToolBar::CreateMiniToolBar(pCommandBars);
	pMiniToolBar->SetBarID(IDR_MENU_MINITOOLBAR);
	pMiniToolBar->SetTitle(_T("MiniBar"));


	CXTPControlComboBox* pComboFont = new CXTPControlFontComboBox();
	pMiniToolBar->GetControls()->Add(pComboFont, ID_COMBO_FONT);

	pComboFont->SetDropDownListStyle();
	pComboFont->EnableAutoComplete();
	pComboFont->SetWidth(64);

	pComboFont = new CXTPControlSizeComboBox();
	pMiniToolBar->GetControls()->Add(pComboFont, ID_COMBO_SIZE);

	pComboFont->SetDropDownListStyle();
	pComboFont->SetWidth(45);


	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_FONT_GROW);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_FONT_SHRINK);
	pMiniToolBar->GetControls()->Add(xtpControlButtonPopup, ID_STYLES_CHANGE);

	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_CHAR_BOLD);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_CHAR_ITALIC);

	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_LEFT);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_CENTER);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_RIGHT);

	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_INCREASEINDENT);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_PARA_DECREASEINDENT);
	pMiniToolBar->GetControls()->Add(xtpControlButton, ID_INSERT_BULLET);


	
	pCommandBars->GetContextMenus()->Add(pMiniToolBar);
	pMiniToolBar->SetWidth(22 * 8 + 4);

	// Add Simple context menu
	CMenu mnu;
	mnu.LoadMenu(IDR_MENU_CONTEXT);

	pCommandBars->GetContextMenus()->Add(IDR_MENU_CONTEXT, _T("Context Menu"), mnu.GetSubMenu(0));

	return TRUE;
}

void CMainFrame::CreateGalleries()
{
	CXTPControlGalleryItem* pItem;

	m_pItemsFontTextColor = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTTEXTCOLOR);
	m_pItemsFontTextColor->SetItemSize(CSize(17, 17));

	pItem = m_pItemsFontTextColor->AddLabel(0);
	pItem->SetCaption(_T("Theme Colors"));
	CGalleryItemFontColor::AddThemeColors(m_pItemsFontTextColor, 0);

	pItem = m_pItemsFontTextColor->AddLabel(0);
	pItem->SetCaption(_T("Standard Colors"));
	CGalleryItemFontColor::AddStandardColors(m_pItemsFontTextColor);


	m_pItemsFontBackColor = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTBACKCOLOR);
	m_pItemsFontBackColor->SetItemSize(CSize(30, 30));

	CGalleryItemFontColor::AddStandardBackColors(m_pItemsFontBackColor);



	m_pItemsFontFace = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTFACE);
	m_pItemsFontFace->SetItemSize(CSize(0, 26));
	CGalleryItemFontFace::AddFontItems(m_pItemsFontFace);

	m_pItemsFontSize = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTSIZE);
	m_pItemsFontSize->SetItemSize(CSize(0, 17));
	m_pItemsFontSize->AddItem(_T("8"));
	m_pItemsFontSize->AddItem(_T("9"));
	m_pItemsFontSize->AddItem(_T("10"));
	m_pItemsFontSize->AddItem(_T("11"));
	m_pItemsFontSize->AddItem(_T("12"));
	m_pItemsFontSize->AddItem(_T("14"));
	m_pItemsFontSize->AddItem(_T("16"));
	m_pItemsFontSize->AddItem(_T("18"));
	m_pItemsFontSize->AddItem(_T("20"));
	m_pItemsFontSize->AddItem(_T("22"));
	m_pItemsFontSize->AddItem(_T("24"));
	m_pItemsFontSize->AddItem(_T("26"));
	m_pItemsFontSize->AddItem(_T("28"));
	m_pItemsFontSize->AddItem(_T("36"));
	m_pItemsFontSize->AddItem(_T("48"));
	m_pItemsFontSize->AddItem(_T("72"));

	m_pItemsUndo = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_EDIT_UNDO);
	m_pItemsUndo->SetItemSize(CSize(0, 21));
	m_pItemsUndo->ClipItems(FALSE);


}

BOOL CMainFrame::CreateRibbonBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CMenu menu;
	menu.LoadMenu(IDR_MENU_RIBBON);
	SetMenu(NULL);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)pCommandBars->Add(_T("The Ribbon"), xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));
	if (!pRibbonBar)
	{
		return FALSE;
	}
	pRibbonBar->EnableDocking(0);

	pCommandBars->GetCommandBarsOptions()->bShowKeyboardTips = TRUE;


	CXTPControlPopup* pControlFile = (CXTPControlPopup*)pRibbonBar->AddSystemButton(IDR_MENU_RIBBON);
	pControlFile->SetCaption(_T("&File"));

	
	UINT uCommand = {IDR_PNG_MAIN_BTN};
	pCommandBars->GetImageManager()->SetIcons(IDR_PNG_MAIN_BTN, &uCommand, 1, CSize(32, 32), xtpImageNormal);
	
	pControlFile->SetStyle(xtpButtonIcon);
	pControlFile->SetIconId(IDR_PNG_MAIN_BTN);
	pControlFile->SetCommandBar(menu.GetSubMenu(0));
	pControlFile->GetCommandBar()->SetIconSize(CSize(32, 32));

	CXTPRibbonTab* pTabHome = pRibbonBar->AddTab(ID_TAB_HOME);

	CXTPRibbonGroup* pGroupClipborad = pTabHome->AddGroup(ID_GROUP_CLIPBOARD);
	pGroupClipborad->ShowOptionButton();
	pGroupClipborad->SetIconId(IDI_GROUP_BUTTONPOPUP);
	pGroupClipborad->GetControlGroupOption()->SetID(ID_GROUP_CLIPBOARD_OPTION);
	pGroupClipborad->SetControlsCentering();
	
	CXTPControlPopup* pControlPaste = (CXTPControlPopup*)pGroupClipborad->Add(xtpControlSplitButtonPopup, ID_EDIT_PASTE);
	pControlPaste->SetIconSize(CSize(32, 32));
	pControlPaste->SetStyle(xtpButtonIconAndCaptionBelow);

	
	pControlPaste->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_PASTE);
	pControlPaste->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_EDIT_PASTE_SPECIAL);
	CXTPControl* pControlCut = pGroupClipborad->Add(xtpControlButton, ID_EDIT_CUT);
	pControlCut->SetKeyboardTip(_T("X"));

	pGroupClipborad->Add(xtpControlButton, ID_EDIT_COPY);	
	pControlPaste->SetKeyboardTip(_T("V"));

	CXTPRibbonGroup* pGroupFont = pTabHome->AddGroup(ID_GROUP_FONT);
	pGroupFont->SetControlsGrouping();
	pGroupFont->ShowOptionButton();
	
	pGroupFont->GetControlGroupOption()->SetID(ID_GROUP_FONT_OPTION);

	CXTPControlFontComboBox* pComboFont = new CXTPControlFontComboBox();
	pGroupFont->Add(pComboFont, ID_COMBO_FONT);

	pComboFont->SetDropDownListStyle();
	pComboFont->EnableAutoComplete();
	pComboFont->SetWidth(130);

	CXTPControlSizeComboBox* pCombSize = new CXTPControlSizeComboBox();
	pCombSize->SetDropDownListStyle();
	pGroupFont->Add(pCombSize, ID_COMBO_SIZE);

	CXTPControl* pControl = pGroupFont->Add(xtpControlButton, ID_FONT_GROW);
	pControl->SetBeginGroup(FALSE);
	pGroupFont->Add(xtpControlButton, ID_FONT_SHRINK);
	pGroupFont->Add(xtpControlButton, ID_CHAR_BOLD)->SetBeginGroup(TRUE);
	pGroupFont->Add(xtpControlButton, ID_CHAR_ITALIC);
	pGroupFont->Add(xtpControlSplitButtonPopup, ID_CHAR_UNDERLINE);	

	pGroupFont->Add(xtpControlButton, ID_CHAR_STRIKETHROUGH);
	pGroupFont->Add(xtpControlButton, ID_TEXT_SUBSCRIPT);
	pGroupFont->Add(xtpControlButton, ID_TEXT_SUPERSCRIPT);	


	CXTPControlPopupColor* pPopupColor = (CXTPControlPopupColor*)pGroupFont->Add(new CXTPControlPopupColor(), ID_TEXT_HIGHLIGHTCOLOR);
	pPopupColor->SetBeginGroup(TRUE);
	CXTPPopupBar* pColorBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	CXTPControlGallery* pControlGallery = new CXTPControlGallery();
	pControlGallery->SetControlSize(CSize(150, 100));
	pControlGallery->ShowLabels(TRUE);
	pControlGallery->ShowScrollBar(FALSE);
	pControlGallery->SetItems(m_pItemsFontBackColor);
	pColorBar->GetControls()->Add(pControlGallery, ID_GALLERY_FONTBACKCOLOR);
	pColorBar->GetControls()->Add(new CXTPControlButton(), ID_BACKCOLOR_NOCOLOR);
	pPopupColor->SetCommandBar(pColorBar);
	pColorBar->InternalRelease();

	pPopupColor = (CXTPControlPopupColor*)pGroupFont->Add(new CXTPControlPopupColor, ID_TEXT_COLOR);
	
	pColorBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	
	pColorBar->GetControls()->Add(new CXTPControlButton(), XTP_IDS_AUTOMATIC);

	pControlGallery = new CXTPControlGallery();
	pControlGallery->SetControlSize(CSize(171, 145));
	pControlGallery->ShowLabels(TRUE);
	pControlGallery->ShowScrollBar(FALSE);
	pControlGallery->SetItems(m_pItemsFontTextColor);
	pColorBar->GetControls()->Add(pControlGallery, ID_GALLERY_FONTTEXTCOLOR);

	pColorBar->GetControls()->Add(new CXTPControlButton(), XTP_IDS_MORE_COLORS);
	
	pPopupColor->SetCommandBar(pColorBar);
	pColorBar->EnableCustomization(FALSE);
	pColorBar->InternalRelease();


	//Paragraph
	CXTPRibbonGroup* pGroupParagraph = pTabHome->AddGroup(ID_GROUP_PARAGRAPH);
	pGroupParagraph->SetControlsGrouping();
	pGroupParagraph->ShowOptionButton();
	pGroupParagraph->GetControlGroupOption()->SetID(ID_GROUP_PARAGRAPH_OPTION);
	
	pGroupParagraph->Add(xtpControlButton, ID_PARA_DECREASEINDENT)->SetBeginGroup(TRUE);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_INCREASEINDENT);
	
	pGroupParagraph->Add(xtpControlSplitButtonPopup, ID_PARA_INSERT_BULLET)->SetBeginGroup(TRUE);
	pGroupParagraph->Add(xtpControlButtonPopup, ID_PARA_LINESPACING)->SetBeginGroup(TRUE);

	
	pGroupParagraph->Add(xtpControlButton, ID_PARA_LEFT)->SetBeginGroup(TRUE);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_CENTER);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_RIGHT);
	pGroupParagraph->Add(xtpControlButton, ID_PARA_JUSTIFY);

	pGroupParagraph->Add(xtpControlButton, ID_PARA_SHOWMARKS)->SetBeginGroup(TRUE);


	//Insert Group
	CXTPRibbonGroup* pGroupStyles = pTabHome->AddGroup(ID_GROUP_INSERT);
	pGroupStyles->SetControlsCentering(TRUE);
	CXTPControlPopup* pControlInsetPic = (CXTPControlPopup*)pGroupStyles->Add(xtpControlSplitButtonPopup, ID_INSERT_PIC);
	pControlInsetPic->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_INSERT_PIC);
	pControlInsetPic->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_CHANGE_PIC);
	pControlInsetPic->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_RESIZE_PIC);

	pGroupStyles->Add(xtpControlButton, ID_INSERT_PAINT_DRAWING);
	pGroupStyles->Add(xtpControlButton, ID_INSERT_DATETIME);
	pGroupStyles->Add(xtpControlButton, ID_INSERT_OBJECT);



	//Editing group
	CXTPRibbonGroup* pGroupFind = pTabHome->AddGroup(ID_GROUP_EDITING);
	
	pGroupFind->Add(xtpControlButton, ID_EDIT_FIND);
	pGroupFind->Add(xtpControlButton, ID_EDIT_REPLACE);
	pGroupFind->Add(xtpControlButton, ID_EDIT_SELECT_ALL);

	//View Tab
	CXTPRibbonTab* pTabView = pRibbonBar->AddTab(ID_TAB_VIEW);

	CXTPRibbonGroup* pGroupZoom = pTabView->AddGroup(ID_GROUP_ZOOM);
	pGroupZoom->Add(xtpControlButton, ID_VIEW_ZOOMIN);
	pGroupZoom->Add(xtpControlButton, ID_VIEW_ZOOMOUT);
	pGroupZoom->Add(xtpControlButton, ID_VIEW_HUNDRED_PERC);


	CXTPRibbonGroup* pGroupShowHide = pTabView->AddGroup(ID_GROUP_SHOWHIDE);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_RULER);
	pGroupShowHide->Add(xtpControlCheckBox, ID_VIEW_STATUS_BAR);

	//Settings group
	CXTPRibbonGroup* pSettings = (CXTPRibbonGroup*) pTabView->AddGroup(ID_GROUP_SETTINGS);
	
	//Word wrap	
	CXTPControlPopup* pControlWordWrap = (CXTPControlPopup*)pSettings->Add(xtpControlSplitButtonPopup, ID_VIEW_WORD_WRAP);

	pControlWordWrap->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_VIEW_WORD_WRAP_NO);
	pControlWordWrap->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_VIEW_WORD_WRAP_WINDOW);
	pControlWordWrap->GetCommandBar()->GetControls()->Add(xtpControlButton, ID_VIEW_WORD_WRAP_RULER);

	//Measurements.
	CXTPControlPopup* pControlMeasurementUnits = (CXTPControlPopup*)pSettings->Add(xtpControlSplitButtonPopup, ID_VIEW_MEASUREMENTS);
	
	pControlMeasurementUnits->GetCommandBar()->GetControls()->Add(xtpControlButton, IDS_INCHES);
	pControlMeasurementUnits->GetCommandBar()->GetControls()->Add(xtpControlButton, IDS_CENTIMETERS);
	pControlMeasurementUnits->GetCommandBar()->GetControls()->Add(xtpControlButton, IDS_POINTS);
	pControlMeasurementUnits->GetCommandBar()->GetControls()->Add(xtpControlButton, IDS_PICAS);


	//Options popup in right side.
	CXTPControlPopup* pControlOptions = (CXTPControlPopup*)pRibbonBar->GetControls()->Add(xtpControlPopup, -1);
	pControlOptions->SetFlags(xtpFlagRightAlign);
	CMenu mnuOptions;
	mnuOptions.LoadMenu(IDR_MENU_OPTIONS);
	pControlOptions->SetCommandBar(mnuOptions.GetSubMenu(0));
	pControlOptions->SetCaption(_T("Options"));
	

	CXTPControl* pControlAbout = pRibbonBar->GetControls()->Add(xtpControlButton, ID_APP_ABOUT);
	pControlAbout->SetFlags(xtpFlagRightAlign);

	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_NEW)->SetHideFlag(xtpHideCustomize, TRUE);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_OPEN)->SetHideFlag(xtpHideCustomize, TRUE);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_SAVE);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_EDIT_UNDO);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_EDIT_REDO);
	pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_QUICK_PRINT);


	CMenu menuQuickStyles;
	menuQuickStyles.LoadMenu(ID_STYLES_QUICKSTYLES);
	CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->LoadMenu(menuQuickStyles.GetSubMenu(0));
	
	pControlGallery->SetCommandBar(pPopupBar);
	pPopupBar->EnableAnimation();
	pPopupBar->InternalRelease();
	

	pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
	pPopupBar->SetShowGripper(FALSE);
	CXTPControlStatic* pControlListBoxInfo = (CXTPControlStatic*)pPopupBar->GetControls()->Add(new CXTPControlStatic(), ID_EDIT_UNDO);
	pControlListBoxInfo->SetWidth(120);
	pControlListBoxInfo->SetFlags(xtpFlagSkipFocus);
	
	pPopupBar->InternalRelease();


	pRibbonBar->GetQuickAccessControls()->CreateOriginalControls();
	pRibbonBar->SetCloseable(FALSE);
	pRibbonBar->EnableFrameTheme();
	return TRUE;
}

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == ID_GALLERY_STYLESET)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(200, 22 * 7 + 2));
		pControlGallery->SetResizable();
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsStyleSet);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_COLORS)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(200, 20 * 9 + 2));
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsThemeColors);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_FONTBACKCOLOR)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(30 * 5, 30 * 3 + 2));
		pControlGallery->ShowScrollBar(FALSE);
		pControlGallery->SetItems(m_pItemsFontBackColor);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}
	if (lpCreateControl->nID == ID_GALLERY_FONTS)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(250, 60 * 5 + 2 + 20));
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsThemeFonts);

		lpCreateControl->pCommandBar->EnableAnimation();

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}
	if (lpCreateControl->nID == ID_FILE_RECENTDOCUMENTS)
	{		
		lpCreateControl->pControl = new CXTPRibbonControlSystemRecentFileList();
		return TRUE;
	}

	if (lpCreateControl->nID == ID_CONTENTS_TABLE)
	{		
		lpCreateControl->controlType = xtpControlButtonPopup;
		return TRUE;
	}

	if (lpCreateControl->nID >= ID_OPTIONS_STYLEBLUE && lpCreateControl->nID <= ID_OPTIONS_STYLESYSTEM)
	{		
		lpCreateControl->controlType = xtpControlRadioButton;
		return TRUE;
	}

	if (lpCreateControl->nID >= ID_OPTIONS_FONT_SYSTEM && lpCreateControl->nID <= ID_OPTIONS_FONT_EXTRALARGE)
	{		
		lpCreateControl->controlType = xtpControlRadioButton;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_FOOTNOTES_NEXT)
	{		
		lpCreateControl->controlType = xtpControlSplitButtonPopup;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_FILE_PRINT && lpCreateControl->nIndex == 5&&m_bIsRibbon)
	{		
		CXTPControlPopup* pControl = CXTPControlPopup::CreateControlPopup(xtpControlSplitButtonPopup);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_PRINT);

		CXTPRibbonSystemPopupBarPage* pPopupBar = new CXTPRibbonSystemPopupBarPage();
		pPopupBar->SetCommandBars(GetCommandBars());

		pPopupBar->LoadMenu(menu.GetSubMenu(0));

		CXTPControl* pControlLabel = pPopupBar->GetControls()->Add(xtpControlLabel, ID_FILE_PRINT_LABEL, NULL, 0);
		pControlLabel->SetWidth(296);
		pControlLabel->SetItemDefault(TRUE);
		pControlLabel->SetStyle(xtpButtonCaption);

		pPopupBar->SetShowGripper(FALSE);
		pPopupBar->SetDefaultButtonStyle(xtpButtonCaptionAndDescription);
		pPopupBar->SetIconSize(CSize(32, 32));

		pControl->SetCommandBar(pPopupBar);

		pPopupBar->InternalRelease();

		lpCreateControl->pControl = pControl;
		return TRUE;
	}
	if (lpCreateControl->nID == ID_FILE_SAVE_AS && lpCreateControl->nIndex == 3&&m_bIsRibbon)
	{		
		CXTPControlPopup* pControl = CXTPControlPopup::CreateControlPopup(xtpControlSplitButtonPopup);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_RIBBON_SAVEAS);

		CXTPRibbonSystemPopupBarPage* pPopupBar = new CXTPRibbonSystemPopupBarPage();
		pPopupBar->SetCommandBars(GetCommandBars());

		pPopupBar->LoadMenu(menu.GetSubMenu(0));

		CXTPControl* pControlLabel = pPopupBar->GetControls()->Add(xtpControlLabel, ID_FILE_SAVE_AS, NULL, 0);
		pControlLabel->SetWidth(296);
		pControlLabel->SetItemDefault(TRUE);
		pControlLabel->SetStyle(xtpButtonCaption);

		pPopupBar->SetShowGripper(FALSE);
		pPopupBar->SetDefaultButtonStyle(xtpButtonCaptionAndDescription);
		pPopupBar->SetIconSize(CSize(32, 32));

		pControl->SetCommandBar(pPopupBar);

		pPopupBar->InternalRelease();

		lpCreateControl->pControl = pControl;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_FILE_SEND)
	{		
		CXTPControlPopup* pControl = CXTPControlPopup::CreateControlPopup(xtpControlButtonPopup);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_SEND);

		CXTPRibbonSystemPopupBarPage* pPopupBar = new CXTPRibbonSystemPopupBarPage();
		pPopupBar->SetCommandBars(GetCommandBars());

		pPopupBar->LoadMenu(menu.GetSubMenu(0));

		CXTPControl* pControlLabel = pPopupBar->GetControls()->Add(xtpControlLabel, ID_FILE_SEND_LABEL, NULL, 0);
		pControlLabel->SetWidth(296);
		pControlLabel->SetItemDefault(TRUE);
		pControlLabel->SetStyle(xtpButtonCaption);

		pPopupBar->SetShowGripper(FALSE);
		pPopupBar->SetDefaultButtonStyle(xtpButtonCaptionAndDescription);
		pPopupBar->SetIconSize(CSize(32, 32));

		pControl->SetCommandBar(pPopupBar);

		pPopupBar->InternalRelease();

		pControl->SetFlags(xtpFlagManualUpdate);

		lpCreateControl->pControl = pControl;
		return TRUE;
	}
	CXTPToolBar* pToolBar = lpCreateControl->bToolBar? DYNAMIC_DOWNCAST(CXTPToolBar, lpCreateControl->pCommandBar): NULL;

	if (lpCreateControl->nID == ID_COMBO_FONT && pToolBar && pToolBar->GetBarID() == IDB_FORMATBAR)
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
		pPopupBar->SetWidth(23 * 5 + 6);
		pPopupBar->SetTearOffPopup(_T("Borders"), IDR_BORDERS, 23 * 5 + 6);

		pPopup->SetCommandBar(pPopupBar);
		pPopupBar->InternalRelease();

		lpCreateControl->pControl = pPopup;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_COMBO_SIZE && pToolBar && pToolBar->GetBarID() == IDB_FORMATBAR)
	{
		CXTPControlComboBox* pComboSize = new CXTPControlSizeComboBox();
		pComboSize->SetDropDownListStyle();

		lpCreateControl->pControl = pComboSize;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_BUTTON_TEXT && pToolBar && pToolBar->GetBarID() == IDB_FORMATBAR)
	{
		CXTPControlPopupColor* pPopupColor = new CXTPControlPopupColor();

		CXTPPopupBar* pColorBar = (CXTPPopupBar*)CXTPPopupToolBar::CreateObject();

		pColorBar->GetControls()->Add(new CXTPControlButtonColor(), XTP_IDS_AUTOMATIC);
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


	return FALSE;

}
BOOL CMainFrame::CreateToolBars()
{
	XTPImageManager()->SetMaskColor(RGB(0, 255, 0));

	CXTPCommandBars* pCommandBars = GetCommandBars();

	CXTPToolBar* pStandardBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar ||
		!pStandardBar->LoadToolBar(IDR_MAINFRAME1))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	CXTPToolBar* pFormatBar = (CXTPToolBar*)pCommandBars->Add(_T("Formating"), xtpBarTop);
	if (!pFormatBar ||
		!pFormatBar->LoadToolBar(IDB_FORMATBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	DockRightOf(pFormatBar, pStandardBar);

	
	// Create Context Menu

	CMenu menuText;
	menuText.LoadMenu(IDR_TEXT_POPUP);
	CMenu* pMenuPopup = menuText.GetSubMenu(0);
	menuText.RemoveMenu(0, MF_BYPOSITION);
	if (!GetSystemMetrics(SM_PENWINDOWS))
	{
		//delete pen specific stuff
		// remove Insert Keystrokes
		pMenuPopup->DeleteMenu(ID_PEN_LENS, MF_BYCOMMAND);
		int nIndex = pMenuPopup->GetMenuItemCount()-1; //index of last item
		// remove Edit Text...
		pMenuPopup->DeleteMenu(nIndex, MF_BYPOSITION);
		// remove separator
		pMenuPopup->DeleteMenu(nIndex-1, MF_BYPOSITION);
	}

	pCommandBars->GetContextMenus()->Add(IDR_TEXT_POPUP, _T("Context Menu"), pMenuPopup);


	return TRUE;
}

BOOL CMainFrame::CreateRulerBar()
{
	if (!m_wndRulerBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_HIDE_INPLACE, ID_VIEW_RULER))
	{
		TRACE0("Failed to create ruler\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}

BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Operations

HICON CMainFrame::GetIcon(int nDocType)
{
	switch (nDocType)
	{
		case RD_WINWORD6:
		case RD_WORDPAD:
		case RD_EMBEDDED:
		case RD_RICHTEXT:
			return m_hIconDoc;
		case RD_TEXT:
		case RD_OEMTEXT:
			return m_hIconText;
		case RD_WRITE:
			return m_hIconWrite;
	}
	return m_hIconDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFontChange()
{
	//m_wndFormatBar.SendMessage(CWordPadApp::m_nPrinterChangedMsg);
}

void CMainFrame::OnDevModeChange(LPTSTR lpDeviceName)
{
	theApp.NotifyPrinterChanged();
	CFrameWnd::OnDevModeChange(lpDeviceName); //sends message to descendants
}

void CMainFrame::OnSysColorChange()
{
	CFrameWnd::OnSysColorChange();
	m_wndRulerBar.SendMessage(WM_SYSCOLORCHANGE);
}

void CMainFrame::ActivateFrame(int nCmdShow)
{
	CFrameWnd::ActivateFrame(nCmdShow);
	// make sure and display the toolbar, ruler, etc while loading a document.
	OnIdleUpdateCmdUI();
	UpdateWindow();
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	theApp.m_bMaximized = (nType == SIZE_MAXIMIZED);
	if (nType == SIZE_RESTORED)
		GetWindowRect(theApp.m_rectInitialFrame);
}

LRESULT CMainFrame::OnBarState(WPARAM wParam, LPARAM lParam)
{
	if (lParam == -1)
		return 0L;
	ASSERT(lParam != RD_EMBEDDED);
	if (wParam == 0)
	{
		//CDockState& ds = theApp.GetDockState(lParam);
		//ds.Clear(); // empty out the dock state
		//GetDockState(ds);
	}
	else
	{
		if (IsTextType((int)lParam))
		{
			// in text mode hide the ruler and format bar so that it is the default
			CWnd* pBar = GetControlBar(ID_VIEW_RULER);
			if (pBar != NULL)
				pBar->ShowWindow(SW_HIDE);
		}
		HICON hIcon = GetIcon((int)lParam);
		SendMessage(WM_SETICON, TRUE, (LPARAM)hIcon);
		//SetDockState(theApp.GetDockState(lParam));
	}
	return 0L;
}

void CMainFrame::OnMove(int x, int y)
{
	CFrameWnd::OnMove(x, y);
	WINDOWPLACEMENT wp;
	wp.length = sizeof(wp);
	GetWindowPlacement(&wp);
	theApp.m_rectInitialFrame = wp.rcNormalPosition;
	CView* pView = GetActiveView();
	if (pView != NULL)
		pView->SendMessage(WM_MOVE);
}

LRESULT CMainFrame::OnOpenMsg(WPARAM, LPARAM lParam)
{
	TCHAR szAtomName[256];
	szAtomName[0] = NULL;
	GlobalGetAtomName((ATOM)lParam, szAtomName, 256);
	CWordPadDoc* pDoc = (CWordPadDoc*)GetActiveDocument();
	if (szAtomName[0] != NULL && pDoc != NULL)
	{
		if (lstrcmpi(szAtomName, pDoc->GetPathName()) == 0)
			return TRUE;
	}
	return FALSE;
}

void CMainFrame::OnHelpFinder()
{
	theApp.WinHelp(0, HELP_FINDER);
}

void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFileName[_MAX_PATH];
	::DragQueryFile(hDropInfo, 0, szFileName, _MAX_PATH);
	::DragFinish(hDropInfo);
	theApp.OpenDocumentFile(szFileName);
}

void CMainFrame::OnCharColor()
{
	/*CColorMenu colorMenu;
	CRect rc;
	int index = m_wndFormatBar.CommandToIndex(ID_CHAR_COLOR);
	m_wndFormatBar.GetItemRect(index, &rc);
	m_wndFormatBar.ClientToScreen(rc);
	colorMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,rc.left,rc.bottom, this);*/
}

void CMainFrame::OnPenToggle()
{

}

BOOL CMainFrame::OnQueryNewPalette()
{
	CView* pView = GetActiveView();
	if (pView != NULL)
		return (BOOL)pView->SendMessage(WM_QUERYNEWPALETTE);
	return FALSE;
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	CView* pView = GetActiveView();
	if (pView != NULL)
		pView->SendMessage(WM_PALETTECHANGED, (WPARAM)pFocusWnd->GetSafeHwnd());
}



int CMainFrame::OnCreateCommandBar(LPCREATEBARSTRUCT lpCreatePopup)
{
	if (lpCreatePopup->bTearOffBar && lpCreatePopup->nID == IDR_COLORTEXT_POPUP)
	{
		CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, lpCreatePopup->pCommandBar);
		ASSERT(pToolBar);

		// Prevent docking.
		pToolBar->EnableDocking(xtpFlagFloating);
		// Prevent customization
		pToolBar->EnableCustomization(FALSE);
		return TRUE;
	}
	return FALSE;
}
void CMainFrame::OnCustomize()
{
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);

	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_MAINFRAME);
	pCommands->GetControls(_T("File"))->Add(xtpControlButton, ID_FILE_OPEN, _T(""), 1);

	pCommands->InsertAllCommandsCategory();
	pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pCommands->InsertNewMenuCategory();

	cs.DoModal();
}

void CMainFrame::OnClose()
{
	SaveCommandBars(_T("CommandBars2"));

	CFrameWnd::OnClose();
}



void CMainFrame::SwitchBorders(DWORD dwState)
{
	if (m_dwBorders & dwState) m_dwBorders &= ~dwState; else m_dwBorders |= dwState;

}


void CMainFrame::OnBorders(UINT nID)
{
	switch (nID)
	{
		case ID_BDR_TOP: SwitchBorders(borderTop); break;
		case ID_BDR_LEFT: SwitchBorders(borderLeft); break;
		case ID_BDR_RIGHT: SwitchBorders(borderRight); break;
		case ID_BDR_BOTTOM: SwitchBorders(borderBottom); break;
		case ID_BDR_NONE: m_dwBorders = 0; break;
		case ID_BDR_OUTSIDE: SwitchBorders(borderOutside); break;
		case ID_BDR_ALL: SwitchBorders(borderAll); break;
		case ID_BDR_INSIDE_VERT: SwitchBorders(borderInsideVert); break;
		case ID_BDR_INSIDE_HORZ: SwitchBorders(borderInsideHorz); break;
		case ID_BDR_INSIDE: SwitchBorders(borderInside); break;
	}

}

void CMainFrame::OnUpdateBorders(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
		case ID_BDR_TOP: pCmdUI->SetCheck(m_dwBorders & borderTop? TRUE: FALSE); break;
		case ID_BDR_LEFT: pCmdUI->SetCheck(m_dwBorders & borderLeft? TRUE: FALSE); break;
		case ID_BDR_RIGHT: pCmdUI->SetCheck(m_dwBorders & borderRight? TRUE: FALSE); break;
		case ID_BDR_BOTTOM: pCmdUI->SetCheck(m_dwBorders & borderBottom? TRUE: FALSE); break;
		case ID_BDR_OUTSIDE : pCmdUI->SetCheck((m_dwBorders & borderOutside) == borderOutside? TRUE: FALSE); break;
		case ID_BDR_ALL : pCmdUI->SetCheck((m_dwBorders & borderAll) == borderAll? TRUE: FALSE); break;
		case ID_BDR_INSIDE_VERT: pCmdUI->SetCheck(m_dwBorders & borderInsideVert? TRUE: FALSE); break;
		case ID_BDR_INSIDE_HORZ: pCmdUI->SetCheck(m_dwBorders & borderInsideHorz? TRUE: FALSE); break;
		case ID_BDR_INSIDE: pCmdUI->SetCheck((m_dwBorders & borderInside) == borderInside? TRUE: FALSE); break;
	}
}

void CMainFrame::OnViewTheme(UINT nTheme)
{
	SetRedraw(FALSE);

	if(TRUE==m_bIsRibbon&&ID_THEME_RIBBON!=nTheme)
	{
		m_bIsRibbon = FALSE;
		EnableNormalStyle();
	}

	switch (nTheme)
	{
	case ID_THEME_OFFICE2000:
		EnableOffice2007Frame(NULL);
		XTPPaintManager()->SetTheme(xtpThemeOffice2000);
		GetCommandBars()->SetTheme(xtpThemeOffice2000);
		CXTPPaintManager:: SetTheme(xtpThemeOffice2000);
		break;
	case ID_THEME_OFFICE2002:
		EnableOffice2007Frame(NULL);
		XTPPaintManager()->SetTheme(xtpThemeOfficeXP);
		GetCommandBars()->SetTheme(xtpThemeOfficeXP);
		CXTPPaintManager:: SetTheme(xtpThemeOfficeXP);
		break;
	case ID_THEME_OFFICE2003:
		EnableOffice2007Frame(NULL);
		XTPPaintManager()->SetTheme(xtpThemeOffice2003);
		GetCommandBars()->SetTheme(xtpThemeOffice2003);
		CXTPPaintManager:: SetTheme(xtpThemeOffice2003);
		break;
	case ID_THEME_OFFICE2007:
		EnableOffice2007Frame(NULL);
		XTPPaintManager()->SetTheme(xtpThemeRibbon);
		GetCommandBars()->SetTheme(xtpThemeRibbon);
		CXTPPaintManager:: SetTheme(xtpThemeRibbon);
		EnableOffice2007Frame(GetCommandBars());
		break;
	case ID_THEME_RIBBON:
		EnableOffice2007Frame(NULL);
		m_bIsRibbon = TRUE;	
		EnableRibbonStyle();
		break;
	}

	SetRedraw(TRUE);
	GetCommandBars()->RedrawCommandBars();
	RedrawWindow(0, 0, RDW_ALLCHILDREN | RDW_INVALIDATE);
	m_nStyle = nTheme;
}

void CMainFrame::OnUpdateViewThemeOffice2000(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(XTPPaintManager()->GetCurrentTheme() == xtpThemeOffice2000);
}

void CMainFrame::OnUpdateViewThemeOffice2002(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(XTPPaintManager()->GetCurrentTheme() == xtpThemeOfficeXP);
	
}

void CMainFrame::OnUpdateViewThemeOffice2003(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(XTPPaintManager()->GetCurrentTheme() == xtpThemeOffice2003);
}

void CMainFrame::OnUpdateViewThemeOffice2007(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(XTPPaintManager()->GetCurrentTheme() == xtpThemeRibbon);
	
}

void CMainFrame::OnUpdateGalleryThemeColors(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nThemeColors);
	}
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnGalleryThemeColors(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nThemeColors = pItem->GetID();
			
			m_pItemsFontTextColor->RemoveAll();
			pItem = m_pItemsFontTextColor->AddLabel(0);
			pItem->SetCaption(_T("Theme Colors"));
			CGalleryItemFontColor::AddThemeColors(m_pItemsFontTextColor, m_nThemeColors);
			
			pItem = m_pItemsFontTextColor->AddLabel(0);
			pItem->SetCaption(_T("Standard Colors"));
			CGalleryItemFontColor::AddStandardColors(m_pItemsFontTextColor);

		}

		*pResult = TRUE; // Handled
	}
}
void CMainFrame::OnOptionsStyle(UINT nStyle)
{
	GetCommandBars()->SetTheme(xtpThemeRibbon);

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
		case ID_OPTIONS_STYLESCENIC: 
			hModule = LoadLibrary(m_csStylesPath + _T("Windows7.dll"));
			lpszIniFile = _T("WINDOWS7BLUE.INI"); break;
		case ID_OPTIONS_STYLEWHITE: 
			hModule = LoadLibrary(m_csStylesPath + _T("Office2010.dll"));
			lpszIniFile = _T("OFFICE2010SILVER.INI"); break;
	}


	if (hModule != 0)
	{
		((CXTPOffice2007Theme*)GetCommandBars()->GetPaintManager())->SetImageHandle(hModule, lpszIniFile);
	}

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();

	if (nStyle == ID_OPTIONS_STYLEWHITE || nStyle == ID_OPTIONS_STYLESCENIC)
	{
		pRibbonBar->GetSystemButton()->SetIconId(IDR_PNG_MAIN_BTN);
		pRibbonBar->GetSystemButton()->SetStyle(xtpButtonIcon);		
	}
	else
	{
		pRibbonBar->GetSystemButton()->SetIconId(IDR_PNG_MAIN_BTN);
		pRibbonBar->GetSystemButton()->SetStyle(xtpButtonAutomatic);
	}

	GetCommandBars()->SetTheme(xtpThemeRibbon);
	CXTPPaintManager:: SetTheme(xtpThemeRibbon);


	GetCommandBars()->GetImageManager()->RefreshAll();
	GetCommandBars()->RedrawCommandBars();
	SendMessage(WM_NCPAINT);
	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);
	m_nRibbonStyle = nStyle;
}
void CMainFrame::OnUpdateOptionsStyle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonStyle ? 1 : 0);

}
void CMainFrame::OnUpdateChangeThemes(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nStyle ? 1 : 0);

}
void CMainFrame::OnMeasurements(UINT nItem)
{
	m_nMeasurements = nItem;
}
void CMainFrame::OnUpdateMeasurements(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nMeasurements ? 1 : 0);

}
void CMainFrame::OnWordWrap(UINT nItem)
{
	m_nWordWrap = nItem;
}
void CMainFrame::OnUpdateWordWrap(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nWordWrap ? 1 : 0);

}



void CMainFrame::OnFileQuickPrint() 
{
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnFileSaveAsOpenDocTxt() 
{
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnFileSaveAsOpenXml() 
{
	// TODO: Add your command handler code here
	
}



void CMainFrame::OnFileSaveAsPlainTxtDoc() 
{
	// TODO: Add your command handler code here
	
}



void CMainFrame::OnFileSaveAsRichTxt() 
{
	// TODO: Add your command handler code here
	
}



void CMainFrame::OnFileAbout() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileSendMail() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnSendInEmail() 
{
	// TODO: Add your command handler code here
	
}
void CMainFrame::OnInsertPicture()
{

}
void CMainFrame::OnInsertDrawing()
{
}
void CMainFrame::OnInsertObject()
{
}

void CMainFrame::OnInsertDatetime()
{
}
void CMainFrame::OnZoomIn()
{
}
void CMainFrame::OnZoomOut()
{
}

void CMainFrame::OnHundredPercent()
{
}
void CMainFrame::OnDummyHandler()
{
}
