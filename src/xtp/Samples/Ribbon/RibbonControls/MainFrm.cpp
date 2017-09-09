// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RibbonControls.h"
#include "GalleryItems.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_XTP_CREATECONTROL()
	
	ON_COMMAND(ID_BUTTON_LARGETOGGLEBUTTON, OnToggleButton)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_LARGETOGGLEBUTTON, OnUpdateToggleButton)

	ON_UPDATE_COMMAND_UI_RANGE(ID_BUTTON_LARGESIMPLEBUTTON, ID_BUTTON_SMALLSPLITPOPUPBUTTON, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_POPUP_OPTION1, ID_POPUP_OPTION3, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_EDITOR_EDIT, ID_EDITOR_COMBO, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_EDITOR_EXTENDEDEDIT, ID_EDITOR_EXTENDEDCOMBO, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GALLERY_FONTFACE, ID_EDITOR_POPUP, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GALLERY_STYLES, ID_GALLERY_TABLE, OnEnableButton)

	ON_UPDATE_COMMAND_UI(ID_GALLERY_COLOR, OnUpdateSelectorText)
	ON_XTP_EXECUTE(ID_GALLERY_COLOR, OnSelectorText)

	ON_UPDATE_COMMAND_UI(ID_GALLERY_UNDO, OnUpdateEditUndo)
	ON_XTP_EXECUTE(ID_GALLERY_UNDO, OnEditUndo)

	ON_COMMAND_RANGE(ID_BUTTON_CHECKBOX1, ID_BUTTON_CHECKBOX3, OnCheckbox)
	ON_COMMAND_RANGE(ID_BUTTON_RADIOBUTTON1, ID_BUTTON_RADIOBUTTON3, OnRadioButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BUTTON_CHECKBOX1, ID_BUTTON_CHECKBOX3, OnUpdateCheckbox)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BUTTON_RADIOBUTTON1, ID_BUTTON_RADIOBUTTON3, OnUpdateRadioButton)

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
	m_bCheckbox[0] = TRUE;
	m_bCheckbox[1] = FALSE;
	m_bCheckbox[2] = FALSE;
	m_nRadioButton = 1;
	m_bToggleButton = FALSE;

	m_nRibbonStyle = ID_OPTIONS_STYLEBLUE;
	m_clr = 0;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	XTPPaintManager()->SetTheme(xtpThemeRibbon);

	if (!CreateStatusBar())
		return -1;

	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();
	m_wndStatusBar.SetCommandBars(pCommandBars);

	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon\n");
		return -1;
	}

	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(xtpToolTipResource);
	pToolTipContext->ShowTitleAndDescription();
	pToolTipContext->ShowImage(TRUE, 0);
	pToolTipContext->SetMargin(CRect(2, 2, 2, 2));
	pToolTipContext->SetMaxTipWidth(180);
	pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());
	pToolTipContext->SetDelayTime(TTDT_INITIAL, 900);

	pCommandBars->GetCommandBarsOptions()->bShowKeyboardTips = TRUE;


	return 0;
}

BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;      // fail to create
	}

	m_wndStatusBar.AddIndicator(0);
	m_wndStatusBar.AddIndicator(ID_INDICATOR_CAPS);
	m_wndStatusBar.AddIndicator(ID_INDICATOR_NUM);
	m_wndStatusBar.AddIndicator(ID_INDICATOR_SCRL);

	return TRUE;
}

BOOL CMainFrame::CreateRibbonBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CMenu menu;
	menu.Attach(::GetMenu(m_hWnd));
	SetMenu(NULL);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)pCommandBars->Add(_T("The Ribbon"), xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));
	if (!pRibbonBar)
	{
		return FALSE;
	}

	pRibbonBar->EnableDocking(0);

	CXTPControlPopup* pControlFile = (CXTPControlPopup*)pRibbonBar->AddSystemButton(ID_MENU_FILE);
	pControlFile->SetCommandBar(menu.GetSubMenu(0));
	pControlFile->GetCommandBar()->SetIconSize(CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(ID_MENU_FILE);
	pControlFile->SetCaption(_T("&File"));
	
	pControlFile->SetIconId(IDB_GEAR);
	UINT uCommand = {IDB_GEAR};
	pCommandBars->GetImageManager()->SetIcons(IDB_GEAR, &uCommand, 1, CSize(0, 0), xtpImageNormal);
	
	CXTPRibbonTab* pTabHome = pRibbonBar->AddTab(ID_TAB_BUTTONS);

	// Large Buttons
	if (pTabHome)
	{
		CXTPControl* pControl;

		CXTPRibbonGroup* pGroup = pTabHome->AddGroup(ID_GROUP_LARGEBUTTONS);
		pGroup->ShowOptionButton();

		pControl = pGroup->Add(xtpControlButton, ID_BUTTON_LARGESIMPLEBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton, ID_BUTTON_LARGETOGGLEBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButtonPopup, ID_BUTTON_LARGEPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlSplitButtonPopup, ID_BUTTON_LARGESPLITPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);


		UINT nIDs[] = {ID_BUTTON_LARGESIMPLEBUTTON, ID_BUTTON_LARGEPOPUPBUTTON, ID_BUTTON_LARGESPLITPOPUPBUTTON, ID_BUTTON_LARGETOGGLEBUTTON};
		pCommandBars->GetImageManager()->SetIcons(ID_GROUP_LARGEBUTTONS, nIDs, 4, CSize(32, 32), xtpImageNormal);
		pCommandBars->GetImageManager()->SetIcons(ID_GROUP_SMALLBUTTONS, nIDs, 4, CSize(16, 16), xtpImageNormal);
	}

	// Small Buttons
	if (pTabHome)
	{
		CXTPControl* pControl;

		CXTPRibbonGroup* pGroup = pTabHome->AddGroup(ID_GROUP_SMALLBUTTONS);

		pControl = pGroup->Add(xtpControlButton, ID_BUTTON_SMALLSIMPLEBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaption);

		pControl = pGroup->Add(xtpControlPopup, ID_BUTTON_SMALLPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaption);

		pControl = pGroup->Add(xtpControlSplitButtonPopup, ID_BUTTON_SMALLSPLITPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaption);

		pControl = pGroup->Add(xtpControlButton, ID_BUTTON_SMALLSIMPLEBUTTON);
		pControl->SetStyle(xtpButtonIcon);

		pControl = pGroup->Add(xtpControlPopup, ID_BUTTON_SMALLPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIcon);

		pControl = pGroup->Add(xtpControlSplitButtonPopup, ID_BUTTON_SMALLSPLITPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIcon);

		UINT nIDs[] = {ID_BUTTON_SMALLSIMPLEBUTTON, ID_BUTTON_SMALLPOPUPBUTTON, ID_BUTTON_SMALLSPLITPOPUPBUTTON};
		pCommandBars->GetImageManager()->SetIcons(ID_GROUP_SMALLBUTTONS, nIDs, 3, CSize(16, 16), xtpImageNormal);
	}

	// CheckBoxes and Radio Buttons
	if (pTabHome)
	{

		CXTPRibbonGroup* pGroup = pTabHome->AddGroup(ID_GROUP_CHECKBOXES);
		CXTPControl* pControl;

		pControl = pGroup->Add(xtpControlCheckBox, ID_BUTTON_CHECKBOX1);

		pControl = pGroup->Add(xtpControlCheckBox, ID_BUTTON_CHECKBOX2);

		pControl = pGroup->Add(xtpControlCheckBox, ID_BUTTON_CHECKBOX3);


		pControl = pGroup->Add(xtpControlRadioButton, ID_BUTTON_RADIOBUTTON1);
		pControl->SetBeginGroup(TRUE);

		pControl = pGroup->Add(xtpControlRadioButton, ID_BUTTON_RADIOBUTTON2);

		pControl = pGroup->Add(xtpControlRadioButton, ID_BUTTON_RADIOBUTTON3);
	}

	if (pTabHome)
	{
		CXTPRibbonGroup* pGroup = pTabHome->AddGroup(ID_GROUP_GROUP);
		pGroup->SetControlsGrouping(TRUE);
		pGroup->SetControlsCentering(TRUE);

		pGroup->LoadToolBar(IDR_MAINFRAME);
	}

	CXTPRibbonTab* pTabEditors = pRibbonBar->AddTab(ID_TAB_EDITORS);

	// Standard Editors
	if (pTabEditors)
	{
		CXTPRibbonGroup* pGroup = pTabEditors->AddGroup(ID_GROUP_STANDARDEDITORS);

		CXTPControlEdit* pControlEdit = (CXTPControlEdit*)pGroup->Add(xtpControlEdit, ID_EDITOR_EDIT);
		pControlEdit->SetEditText("Edit");
		//pControlEdit->ShowSpinButtons(TRUE);
		pControlEdit->SetWidth(150);
		pControlEdit->SetStyle(xtpButtonIcon);

		CXTPControlComboBox* pControlCombo = (CXTPControlComboBox*)pGroup->Add(xtpControlComboBox, ID_EDITOR_COMBO);
		
		pControlCombo->GetCommandBar()->SetCommandBars(pCommandBars);
		pControlCombo->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		pControlCombo->SetWidth(150);
		pControlCombo->SetStyle(xtpButtonIcon);
		pControlCombo->SetDropDownListStyle();
		pControlCombo->SetEditText(_T("ComboBox"));
		pControlCombo->AddString(_T("Item 1"));
		pControlCombo->AddString(_T("Item 2"));

		pControlCombo = (CXTPControlComboBox*)pGroup->Add(xtpControlComboBox, ID_EDITOR_COMBO);

		pControlCombo->GetCommandBar()->SetCommandBars(pCommandBars);
		pControlCombo->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		pControlCombo->SetWidth(150);
		pControlCombo->SetStyle(xtpButtonIcon);

		pControlCombo->AddString(_T("ComboBox"));
		pControlCombo->AddString(_T("Item 1"));
		pControlCombo->AddString(_T("Item 2"));
		pControlCombo->SetCurSel(0);
	}

	// Extended Editors
	if (pTabEditors)
	{
		CXTPRibbonGroup* pGroup = pTabEditors->AddGroup(ID_GROUP_EXTENDEDEDITORS);

		CXTPControlEdit* pControlEdit = (CXTPControlEdit*)pGroup->Add(xtpControlEdit, ID_EDITOR_EXTENDEDEDIT);
		pControlEdit->SetEditText("0");
		pControlEdit->ShowSpinButtons(TRUE);
		pControlEdit->SetWidth(150);
		pControlEdit->SetStyle(xtpButtonIconAndCaption);

		CXTPControlComboBox* pControlCombo = (CXTPControlComboBox*)pGroup->Add(xtpControlComboBox, ID_EDITOR_EXTENDEDCOMBO);
		
		pControlCombo->GetCommandBar()->SetCommandBars(pCommandBars);
		pControlCombo->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		pControlCombo->SetWidth(150);
		pControlCombo->SetStyle(xtpButtonIconAndCaption);
		pControlCombo->SetDropDownListStyle();
		pControlCombo->SetEditText(_T("ComboBox"));
		pControlCombo->AddString(_T("Item 1"));
		pControlCombo->AddString(_T("Item 2"));

		pControlCombo = (CXTPControlComboBox*)pGroup->Add(xtpControlComboBox, ID_EDITOR_EXTENDEDCOMBO);

		pControlCombo->GetCommandBar()->SetCommandBars(pCommandBars);
		pControlCombo->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		pControlCombo->SetWidth(150);
		pControlCombo->SetStyle(xtpButtonIconAndCaption);

		pControlCombo->AddString(_T("ComboBox"));
		pControlCombo->AddString(_T("Item 1"));
		pControlCombo->AddString(_T("Item 2"));
		pControlCombo->SetCurSel(0);

		UINT nIDs[] = {ID_EDITOR_EXTENDEDEDIT, ID_EDITOR_EXTENDEDCOMBO};
		pCommandBars->GetImageManager()->SetIcons(ID_GROUP_EXTENDEDEDITORS, nIDs, 2, CSize(16, 16), xtpImageNormal);
	}

	// Gallery Editors
	{
		CXTPRibbonGroup* pGroup = pTabEditors->AddGroup(ID_GROUP_GALLERY);

		
		CXTPControlGalleryItems* m_pItemsFontFace = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTFACE);
		m_pItemsFontFace->SetItemSize(CSize(0, 26));
		CGalleryItemFontFace::AddFontItems(m_pItemsFontFace);


		CXTPControlComboBox* pComboFont = new CXTPControlComboBox();
		pGroup->Add(pComboFont, ID_GALLERY_FONTFACE);
		
		pComboFont->SetDropDownListStyle();
		pComboFont->EnableAutoComplete();
		pComboFont->SetWidth(150);
		
		CXTPPopupBar* pPopupBarGallery = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(pCommandBars);
		
		pComboFont->SetCommandBar(pPopupBarGallery);
		
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(290, 508));
		pControlGallery->SetResizable(FALSE, TRUE);
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsFontFace);
		
		pPopupBarGallery->GetControls()->Add(pControlGallery, ID_GALLERY_FONTFACE);
		
		pPopupBarGallery->InternalRelease();
		
		
		CXTPControlComboBox* pComboPopup = new CXTPControlComboBox();
		pComboPopup->SetWidth(150);

		pGroup->Add(pComboPopup, ID_EDITOR_POPUP);

		CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(pCommandBars);
		pPopupBar->SetWidth(150);
		
		pComboPopup->SetCommandBar(pPopupBar);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_OPTIONS);
		pPopupBar->LoadMenu(menu.GetSubMenu(0));

		pPopupBar->InternalRelease();

	}


	CXTPRibbonTab* pTabGallery = pRibbonBar->AddTab(ID_TAB_GALLERIES);

	// Create Gallery Items
	{

		m_pItemsStyles = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_STYLES);
		
		m_pItemsStyles->GetImageManager()->SetMaskColor(0xFF00FF);
		m_pItemsStyles->GetImageManager()->SetIcons(ID_GALLERY_STYLES, 0, 0, CSize(64, 48));
		m_pItemsStyles->GetImageManager()->SetMaskColor(COLORREF_NULL); // Default TopLeft Pixel.
		
		m_pItemsStyles->SetItemSize(CSize(72, 56));
		
		for (int nStyle = 0; nStyle < 16; nStyle++)
			m_pItemsStyles->AddItem(nStyle, nStyle);

		m_pItemsTable = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_TABLE);
		m_pItemsTable->ClipItems(FALSE); //Redraw all Items if selection changed
		m_pItemsTable->SetItemSize(CSize(19, 19));
		
		CXTPControlGalleryItem* pItem = m_pItemsTable->AddItem(new CGalleryItemTableLabel());
		int nItem;
		for (nItem = 0; nItem < 10 * 8; nItem++)
			m_pItemsTable->AddItem(new CGalleryItemTable(nItem));

		m_pItemsFontTextColor = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_COLOR);
		m_pItemsFontTextColor->SetItemSize(CSize(17, 17));
		
		pItem = m_pItemsFontTextColor->AddLabel(0);
		pItem->SetCaption(_T("Theme Colors"));
		CGalleryItemFontColor::AddThemeColors(m_pItemsFontTextColor, 0);
		
		pItem = m_pItemsFontTextColor->AddLabel(0);
		pItem->SetCaption(_T("Standard Colors"));
		CGalleryItemFontColor::AddStandardColors(m_pItemsFontTextColor);

		m_pItemsUndo = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_UNDO);
		m_pItemsUndo->SetItemSize(CSize(0, 21));
		m_pItemsUndo->ClipItems(FALSE);	

	}

	// Create Popup Gallery
	if (pTabGallery)
	{
		CXTPRibbonGroup* pGroup = pTabGallery->AddGroup(ID_GROUP_POPUP);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlPopup* pControl = (CXTPControlPopup*)pGroup->Add(xtpControlButtonPopup, ID_GALLERY_STYLES);
		
		CMenu menu;
		menu.LoadMenu(ID_STYLES_QUICKSTYLES);
		
		CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
		pPopupBar->LoadMenu(menu.GetSubMenu(0));
		
		pControl->SetCommandBar(pPopupBar);
		pPopupBar->InternalRelease();



		pControl = (CXTPControlPopup*)pGroup->Add(xtpControlButtonPopup, ID_GALLERY_TABLE);

		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(190, 175));
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->ShowScrollBar(FALSE);
		pControlGallery->SetItems(m_pItemsTable);

		pControl->GetCommandBar()->GetControls()->Add(pControlGallery);

		pControl = (CXTPControlPopup*)pGroup->Add(xtpControlButtonPopup, ID_GALLERY_COLOR);

		pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(171, 145));
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->ShowScrollBar(FALSE);
		pControlGallery->SetItems(m_pItemsFontTextColor);

		pControl->GetCommandBar()->GetControls()->Add(pControlGallery);

		CXTPControlPopup* pControlUndo = (CXTPControlPopup*)pGroup->Add(xtpControlSplitButtonPopup, ID_GALLERY_UNDO);

		pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
		pPopupBar->SetShowGripper(FALSE);
		
		pControlUndo->SetCommandBar(pPopupBar);
		
		pControlGallery = new CControlGalleryUndo();
		pControlGallery->SetItems(m_pItemsUndo);
		pControlGallery->SetWidth(120);
		pControlGallery->ShowScrollBar(FALSE);
		pPopupBar->GetControls()->Add(pControlGallery, ID_GALLERY_UNDO);
		
		CXTPControlStatic* pControlListBoxInfo = (CXTPControlStatic*)pPopupBar->GetControls()->Add(new CXTPControlStatic(), ID_GALLERY_UNDO);
		pControlListBoxInfo->SetWidth(120);
		pControlListBoxInfo->SetFlags(xtpFlagSkipFocus);
		
		pPopupBar->InternalRelease();	

		
		UINT nIDs[] = {ID_GALLERY_STYLES, ID_GALLERY_TABLE, ID_GALLERY_COLOR, ID_GALLERY_UNDO};
		pCommandBars->GetImageManager()->SetIcons(ID_GROUP_INLINE, nIDs, 4, CSize(32, 32), xtpImageNormal);
	}

	// Create Inline Gallery
	if (pTabGallery)
	{
		CXTPRibbonGroup* pGroup = pTabGallery->AddGroup(ID_GROUP_INLINE);
		pGroup->SetControlsCentering(TRUE);


		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(171 + 19, 60));
		pControlGallery->ShowLabels(FALSE);
		pControlGallery->ShowScrollBar(TRUE);
		pControlGallery->ShowBorders(TRUE);
		pControlGallery->SetItems(m_pItemsFontTextColor);

		pGroup->Add(pControlGallery, ID_GALLERY_STYLES);


		pControlGallery = new CXTPControlGallery();
		pControlGallery->SetBeginGroup(TRUE);
		pControlGallery->SetControlSize(CSize(235, 60));
		pControlGallery->SetResizable();
		pControlGallery->SetItemsMargin(0, 1, 0, 1);
		pControlGallery->ShowLabels(FALSE);
		pControlGallery->ShowBorders(TRUE);
		pControlGallery->SetItems(m_pItemsStyles);
		
		
		CMenu menu;
		menu.LoadMenu(ID_STYLES_QUICKSTYLES);
		
		CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
		pPopupBar->LoadMenu(menu.GetSubMenu(0));
		
		pControlGallery->SetCommandBar(pPopupBar);
		pPopupBar->InternalRelease();
		
		pGroup->Add(pControlGallery, ID_GALLERY_STYLES);
	}

	CXTPRibbonTab* pTabMisc = pRibbonBar->AddTab(ID_TAB_MISC);

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_LABEL);
		pGroup->SetControlsCentering(TRUE);

		CXTPControl* pControl = pGroup->Add(xtpControlLabel, 0);
		pControl->SetCaption(_T("Label Text 1"));
		pControl->SetStyle(xtpButtonCaption);
		
		pControl = pGroup->Add(xtpControlLabel, 0);
		pControl->SetCaption(_T("Label Text 2"));
		pControl->SetStyle(xtpButtonCaption);

		pControl = pGroup->Add(xtpControlLabel, 0);
		pControl->SetCaption(_T("Label Text 3"));
		pControl->SetStyle(xtpButtonCaption);

#ifdef _XTP_INCLUDE_MARKUP
		CXTPControlMarkupLabel* pLabel = new CXTPControlMarkupLabel();
		pGroup->Add(pLabel, 0);

		pLabel->SetBeginGroup(TRUE);
		pLabel->SetCaption(_T("<TextBlock TextAlignment='Center'><Underline>This is</Underline><LineBreak/><Bold>Markup</Bold> <Run Foreground='Red'>Label</Run><LineBreak/><Italic>Control</Italic></TextBlock>"));
#endif
	}

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_BITMAP);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlBitmap* pLabel = new CXTPControlBitmap();
		pGroup->Add(pLabel, ID_BUTTON_BITMAP);

		UINT nIDs[] = {ID_BUTTON_BITMAP};
		pCommandBars->GetImageManager()->SetIcons(ID_BUTTON_BITMAP, nIDs, 1, CSize(0, 0), xtpImageNormal);
	}

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_HYPERLINK);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlHyperlink* pLabel = new CXTPControlHyperlink();
		pLabel->SetFlags(xtpFlagManualUpdate);
		pGroup->Add(pLabel, ID_BUTTON_URLLINK);

		pLabel = new CXTPControlHyperlink();
		pLabel->SetFlags(xtpFlagManualUpdate);
		pGroup->Add(pLabel, ID_BUTTON_EMAILLINK);
	}
	
	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_PROGRESS);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlProgress* pControl = (CXTPControlProgress*)pGroup->Add(new CXTPControlProgress(), 0);
		pControl->SetPos(30);
		pControl->SetFlags(xtpFlagNoMovable | xtpFlagSkipFocus);
	}

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_SCROLLBAR);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlScrollBar* pControl = (CXTPControlScrollBar*)pGroup->Add(new CXTPControlScrollBar(), 0);
		pControl->SetFlags(xtpFlagNoMovable | xtpFlagSkipFocus);
		pControl->SetPos(30);
		pControl->SetWidth(100);
	}

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_SLIDER);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlScrollBar* pControl = (CXTPControlScrollBar*)pGroup->Add(new CXTPControlScrollBar(), 0);
		pControl->SetScrollBarStyle(xtpScrollStyleSlider);
		pControl->SetPos(30);
		pControl->SetFlags(xtpFlagNoMovable | xtpFlagSkipFocus);
		pControl->SetWidth(100);
	}


	// Options
	{
		CXTPControlPopup* pControlOptions = (CXTPControlPopup*)pRibbonBar->GetControls()->Add(xtpControlPopup, -1);
		pControlOptions->SetFlags(xtpFlagRightAlign);
		CMenu mnuOptions;
		mnuOptions.LoadMenu(IDR_MENU_OPTIONS);
		pControlOptions->SetCommandBar(mnuOptions.GetSubMenu(0));
		pControlOptions->SetCaption(_T("Options"));
		
		
		CXTPControl* pControlAbout = pRibbonBar->GetControls()->Add(xtpControlButton, ID_APP_ABOUT);
		pControlAbout->SetFlags(xtpFlagRightAlign);

		pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME);	

	}

	// Quick Access
	{

		pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_NEW);
		pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_OPEN)->SetHideFlag(xtpHideCustomize, TRUE);
		pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_SAVE);
		
		pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_PRINT);
		pRibbonBar->GetQuickAccessControls()->CreateOriginalControls();

	}

	pRibbonBar->SetCloseable(FALSE);
	pRibbonBar->EnableFrameTheme();

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = 730;
	cs.cy = 600;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;


	return TRUE;
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


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == ID_FILE_RECENTDOCUMENTS)
	{		
		lpCreateControl->pControl = new CXTPRibbonControlSystemRecentFileList();
		return TRUE;
	}

	if (lpCreateControl->nID == ID_APP_EXIT || lpCreateControl->nID == ID_APP_OPTIONS)
	{		
		lpCreateControl->pControl = new CXTPRibbonControlSystemPopupBarButton();

		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_STYLES)
	{
		
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetResizable();
		pControlGallery->SetControlSize(CSize(235 + 72, 56 * 3));
		pControlGallery->SetItems(m_pItemsStyles);
		
		lpCreateControl->pControl = pControlGallery;

		return TRUE;
	}
	return FALSE;

}

void CMainFrame::OnEnableButton(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}


void CMainFrame::OnCheckbox(UINT nID)
{
	m_bCheckbox[nID - ID_BUTTON_CHECKBOX1] ^= 1;

}

void CMainFrame::OnRadioButton(UINT nID)
{
	m_nRadioButton = nID - ID_BUTTON_RADIOBUTTON1;
}

void CMainFrame::OnUpdateCheckbox(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bCheckbox[(int)pCmdUI->m_nID - ID_BUTTON_CHECKBOX1]);

}

void CMainFrame::OnUpdateRadioButton(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_BUTTON_RADIOBUTTON1 == m_nRadioButton);
}

void CMainFrame::OnToggleButton()
{
	m_bToggleButton ^= 1;
}

void CMainFrame::OnUpdateToggleButton(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bToggleButton);
}


void CMainFrame::OnOptionsRighttoleft() 
{
	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		GetCommandBars()->SetLayoutRTL(FALSE);
		ModifyStyleEx(WS_EX_LAYOUTRTL, 0);
	}
	else
	{
		GetCommandBars()->SetLayoutRTL(TRUE);
		ModifyStyleEx(0, WS_EX_LAYOUTRTL);
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

	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);


	m_nRibbonStyle = nStyle;
}


void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmd)
{
	CXTPControlGallery* pControlUndo = DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmd));

	if (pControlUndo)
	{
		pCmd->Enable(TRUE);

		CXTPControlGalleryItems* pItems = pControlUndo->GetItems();
		pItems->RemoveAll();

		int nCount = RAND_S() % 20 + 3;

		for (int i = 0; i < nCount; i++)
		{
			CString str;
			str.Format(_T("Undo String %i"), i + 1);
			pItems->AddItem(new CGalleryItemUndo(str), i);
		}

		pControlUndo->OnSelectedItemChanged();
		pControlUndo->SetHeight(pItems->GetItemSize().cy * nCount + 2);

	}
	else
	{
		pCmd->Enable();
	}

}

void CMainFrame::OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult)
{
	CXTPControlGallery* pControlUndo = DYNAMIC_DOWNCAST(CXTPControlGallery, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlUndo)
	{
		CString str;
		str.Format(_T("Undo last %i actions"), pControlUndo->GetSelectedItem() + 1);

		AfxMessageBox(str);
	}
	*pResult = 1; // Handled;
}


void CMainFrame::OnUpdateSelectorText(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pControl = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));

	if (pControl)
	{
		pControl->SetCheckedItem(m_clr);
	}

	pCmdUI->Enable(TRUE);

}

void CMainFrame::OnSelectorText(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pControl = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pControl)
	{
		CXTPControlGalleryItem* pItem = pControl->GetItem(pControl->GetSelectedItem());
		if (pItem)
		{
			m_clr = (COLORREF)pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}


	*pResult = 1;
}

