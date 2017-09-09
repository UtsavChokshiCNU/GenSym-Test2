// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GallerySample.h"

#include "MainFrm.h"
#include "GalleryItems.h"

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
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_STYLES_CHANGE, OnStylesChange)
	ON_COMMAND(ID_VIEW_ANIMATE, OnViewAnimate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANIMATE, OnUpdateViewAnimate)
	//}}AFX_MSG_MAP
	ON_XTP_CREATECONTROL()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

	ON_XTP_EXECUTE(ID_GALLERY_SHAPES, OnGalleryShapes)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_SHAPES, OnUpdateGalleryShapes)

	ON_XTP_EXECUTE(ID_GALLERY_STYLES, OnGalleryStyles)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_STYLES, OnUpdateGalleryStyles)

	ON_XTP_EXECUTE(ID_GALLERY_STYLESET, OnGalleryStyleSet)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_STYLESET, OnUpdateGalleryStyleSet)	

	ON_XTP_EXECUTE(ID_GALLERY_COLORS, OnGalleryThemeColors)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_COLORS, OnUpdateGalleryThemeColors)	

	ON_XTP_EXECUTE(ID_GALLERY_TABLE, OnGalleryTable)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_TABLE, OnUpdateGalleryTable)	
	


	ON_XTP_EXECUTE(ID_GALLERY_FONTS, OnGalleryThemeFonts)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_FONTS, OnUpdateGalleryThemeFonts)	

	ON_COMMAND_RANGE(ID_VIEW_THEME_OFFICE2000, ID_VIEW_THEME_RIBBON, OnViewTheme)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_THEME_OFFICE2000, ID_VIEW_THEME_RIBBON, OnUpdateViewTheme)

	ON_NOTIFY(XTP_GN_PREVIEWSTART, ID_GALLERY_STYLES, OnStylesPreviewStart)
	ON_NOTIFY(XTP_GN_PREVIEWCANCEL, ID_GALLERY_STYLES, OnStylesPreviewCancel)
	ON_NOTIFY(XTP_GN_PREVIEWAPPLY, ID_GALLERY_STYLES, OnStylesPreviewApply)
	ON_NOTIFY(XTP_GN_PREVIEWCHANGE, ID_GALLERY_STYLES, OnStylesPreviewChange)


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
	m_pItemsShapes = 0;
	m_pItemsStyles = 0;
	m_pItemsStyleSet = 0;
	m_pItemsThemeColors = 0;
	m_pItemsThemeFonts = 0;
	m_pItemsTable = 0;
	m_pItemsFontTextColor = 0;
	m_pItemsFontBackColor = 0;
	m_pItemsFontFace = 0;
	m_pItemsFontSize = 0;

	
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

	// Inserted to resources
	//XTPResourceImages()->SetHandle(csStylesPath + _T("\\Styles\\Office2007.dll"));
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
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

	m_wndStatusBar.SetCommandBars(GetCommandBars());

	CreateGalleries();

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);

	CXTPToolBar* pStandardBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar ||
		!pStandardBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	
	CXTPToolBar* pFormatBar = (CXTPToolBar*)pCommandBars->Add(_T("Format"), xtpBarTop);
	if (!pFormatBar ||
		!pFormatBar->LoadToolBar(IDR_TOOLBAR_FORMAT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	DockRightOf(pFormatBar, pStandardBar);

	CXTPToolBar* pStylesBar = (CXTPToolBar*)pCommandBars->Add(_T("Styles"), xtpBarTop);
	if (!pStylesBar || 
		!pStylesBar->LoadToolBar(IDR_TOOLBAR_STYLES))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pStylesBar->SetIconSize(CSize(16, 16));

	DockRightOf(pStylesBar, pFormatBar);
	

	CXTPToolBar* pShapesBar = (CXTPToolBar*)pCommandBars->Add(_T("Shapes"), xtpBarLeft);
	if (!pShapesBar)
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pShapesBar->SetBarID(100);

	CXTPControlGallery* pControlGalleryShapes4 = new CXTPControlGallery();
	pControlGalleryShapes4->SetControlSize(CSize(120, 200));
	pControlGalleryShapes4->SetResizable();
	pControlGalleryShapes4->ShowBorders(TRUE);
	pControlGalleryShapes4->SetItems(m_pItemsShapes);

	pShapesBar->GetControls()->Add(pControlGalleryShapes4, ID_GALLERY_SHAPES);

	pShapesBar->GetControls()->CreateOriginalControls();

	pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_MAINFRAME_LARGE);


	pCommandBars->SetTheme(xtpThemeRibbon);
	EnableOffice2007Frame(GetCommandBars());
	pCommandBars->GetPaintManager()->m_bEnableAnimation = TRUE;


	LoadCommandBars(_T("CommandBars2"));
	return 0;
}

void CMainFrame::CreateGalleries()
{
	m_pItemsShapes = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_SHAPES);

	m_pItemsShapes->GetImageManager()->SetIcons(ID_GALLERY_SHAPES, 0, 0, CSize(20, 20));

	m_pItemsShapes->SetItemSize(CSize(20, 20));

	CXTPControlGalleryItem* pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Lines"));

	int nShape;
	for (nShape = 0; nShape < 12; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Basic Shapes"));

	for (; nShape < 12 + 32; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Block Arrows"));

	for (; nShape < 12 + 32 + 27; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Flowchart"));

	for (; nShape < 12 + 32 + 27 + 28; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Callouts"));

	for (; nShape < 12 + 32 + 27 + 28 + 20; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	pItem = m_pItemsShapes->AddLabel(0);
	pItem->SetCaption(_T("Stars and Banners"));

	for (; nShape < 12 + 32 + 27 + 28 + 20 + 16; nShape++)
		m_pItemsShapes->AddItem(nShape, nShape);

	m_nShape = -1;
	m_nStyle = 0;


	m_pItemsStyles = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_STYLES);
	
	m_pItemsStyles->GetImageManager()->SetMaskColor(0xFF00FF);
	m_pItemsStyles->GetImageManager()->SetIcons(ID_GALLERY_STYLES, 0, 0, CSize(64, 48));
	m_pItemsStyles->GetImageManager()->SetMaskColor(COLORREF_NULL); // Default TopLeft Pixel.

	m_pItemsStyles->SetItemSize(CSize(72, 56));

	for (int nStyle = 0; nStyle < 16; nStyle++)
		m_pItemsStyles->AddItem(nStyle, nStyle);


	m_nStyleSet = 0;

	m_pItemsStyleSet = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_STYLESET);
	m_pItemsStyleSet->SetItemSize(CSize(0, 22));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(0, _T("Classic")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(1, _T("Default")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(2, _T("Distinctive")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(3, _T("Elegant")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(4, _T("Fancy")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(5, _T("Formal")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(6, _T("Manuscript")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(7, _T("Modern")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(8, _T("Simple")));
	m_pItemsStyleSet->AddItem(new CGalleryItemStyleSet(9, _T("Traditional")));

	m_nThemeColors = 0;
	m_pItemsThemeColors = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_COLORS);
	m_pItemsThemeColors->SetItemSize(CSize(0, 20));

	pItem = m_pItemsThemeColors->AddLabel(0);
	pItem->SetCaption(_T("Built-In"));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(0, _T("Office")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(1, _T("Grayscale")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(2, _T("Apex")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(3, _T("Aspect")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(4, _T("Civic")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(5, _T("Concourse")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(6, _T("Currency")));
	m_pItemsThemeColors->AddItem(new CGalleryItemThemeColors(7, _T("Deluxe")));

	m_nThemeFonts = 0;
	m_pItemsThemeFonts = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTS);
	m_pItemsThemeFonts->SetItemSize(CSize(0, 60));

	pItem = m_pItemsThemeFonts->AddLabel(0);
	pItem->SetCaption(_T("Built-In"));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(0, _T("Office")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(1, _T("Apex")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(2, _T("Aspect")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(3, _T("Civic")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(4, _T("Concourse")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(5, _T("Currency")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(6, _T("Deluxe")));
	m_pItemsThemeFonts->AddItem(new CGalleryItemThemeFonts(7, _T("Equity")));

	
	
	m_pItemsTable = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_TABLE);
	m_pItemsTable->ClipItems(FALSE); //Redraw all Items if selection changed
	m_pItemsTable->SetItemSize(CSize(19, 19));
	
	pItem = m_pItemsTable->AddItem(new CGalleryItemTableLabel());
	int nItem;
	for (nItem = 0; nItem < 10 * 8; nItem++)
		m_pItemsTable->AddItem(new CGalleryItemTable(nItem));


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

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
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
	if (lpCreateControl->nID == ID_STYLES_CHANGE)
	{
		lpCreateControl->controlType =  xtpControlButtonPopup;
		lpCreateControl->buttonStyle = xtpButtonIconAndCaptionBelow;
		return TRUE;
	}
	
	if (lpCreateControl->bToolBar && lpCreateControl->pCommandBar->GetBarID() == IDR_MAINFRAME)
	{
		lpCreateControl->buttonStyle = xtpButtonIconAndCaptionBelow;
		return TRUE;
	}

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
		pControlGallery->SetResizable();
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsThemeColors);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_TABLE)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(190, 175));
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->ShowScrollBar(FALSE);
		pControlGallery->SetItems(m_pItemsTable);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_EDIT_FONT)
	{
		CXTPControlComboBox* pComboFont = new CXTPControlComboBox();
		pComboFont->SetDropDownListStyle();
		pComboFont->EnableAutoComplete();
		pComboFont->SetWidth(145);

		CXTPPopupBar* pPopupBar = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(GetCommandBars());
		
		pComboFont->SetCommandBar(pPopupBar);

		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(290, 508));
		pControlGallery->SetResizable(FALSE, TRUE);
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsFontFace);

		pPopupBar->GetControls()->Add(pControlGallery, ID_GALLERY_FONTFACE);

		pPopupBar->InternalRelease();
		
		lpCreateControl->pControl = pComboFont;
		return TRUE;
	}
	if (lpCreateControl->nID == ID_EDIT_SIZE)
	{
		CXTPControlComboBox* pComboFont = new CXTPControlComboBox();
		pComboFont->SetDropDownListStyle();
		pComboFont->SetWidth(45);

		CXTPPopupBar* pPopupBar = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(GetCommandBars());

		pComboFont->SetCommandBar(pPopupBar);

		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(42, 16 * 17));
		pControlGallery->SetResizable(FALSE, TRUE);
		pControlGallery->SetItems(m_pItemsFontSize);

		pPopupBar->GetControls()->Add(pControlGallery, ID_GALLERY_FONTSIZE);

		pPopupBar->InternalRelease();
		
		lpCreateControl->pControl = pComboFont;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_EDIT_UNDO)
	{

		CXTPControlPopup* pControlUndo = CXTPControlPopup::CreateControlPopup(xtpControlSplitButtonPopup);
		pControlUndo->SetID(ID_EDIT_UNDO);

		CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
		pPopupBar->SetShowGripper(FALSE);

		pControlUndo->SetCommandBar(pPopupBar);

		CXTPControlGallery* pControlGallery = new CControlGalleryUndo();
		pControlGallery->SetItems(m_pItemsUndo);
		pControlGallery->SetWidth(120);
		pPopupBar->GetControls()->Add(pControlGallery, ID_EDIT_UNDO);

		CXTPControlStatic* pControlListBoxInfo = (CXTPControlStatic*)pPopupBar->GetControls()->Add(new CXTPControlStatic(), ID_EDIT_UNDO);
		pControlListBoxInfo->SetWidth(120);
		pControlListBoxInfo->SetFlags(xtpFlagSkipFocus);

		pPopupBar->InternalRelease();
		
		lpCreateControl->pControl = pControlUndo;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_FORMAT_BOLD)
	{
		CXTPControlButton* pControl = new CXTPControlButton();
		pControl ->SetFlags(xtpFlagWrapRow);		
		lpCreateControl->pControl = pControl;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_VIEW_ANIMATE)
	{
		CXTPControlButton* pControl = new CXTPControlCheckBox();
		pControl ->SetFlags(xtpFlagRightAlign);		
		lpCreateControl->pControl = pControl;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_FORMAT_BACKCOLOR)
	{
		CXTPControlPopupColor* pPopupColor = new CXTPControlPopupColor();
		
		CXTPPopupBar* pColorBar = (CXTPPopupBar*)CXTPPopupBar::CreatePopupBar(GetCommandBars());
		
		CMenu menu;
		menu.LoadMenu(ID_GALLERY_FONTBACKCOLOR);
		pColorBar->LoadMenu(menu.GetSubMenu(0));
		
		pPopupColor->SetCommandBar(pColorBar);
		pColorBar->EnableCustomization(FALSE);
		pColorBar->InternalRelease();

		pPopupColor->SetFlags(xtpFlagWrapRow);
		
		lpCreateControl->pControl = pPopupColor;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_FORMAT_FONTCOLOR)
	{
		CXTPControlPopupColor* pPopupColor = new CXTPControlPopupColor();
		
		CXTPPopupBar* pColorBar = (CXTPPopupBar*)CXTPPopupBar::CreatePopupBar(GetCommandBars());
		
		CMenu menu;
		menu.LoadMenu(ID_GALLERY_FONTTEXTCOLOR);
		pColorBar->LoadMenu(menu.GetSubMenu(0));
		
		pPopupColor->SetCommandBar(pColorBar);
		pColorBar->EnableCustomization(FALSE);
		pColorBar->InternalRelease();

		lpCreateControl->pControl = pPopupColor;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_FONTTEXTCOLOR)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(171, 145));
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->ShowScrollBar(FALSE);
		pControlGallery->SetItems(m_pItemsFontTextColor);

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
		pControlGallery->SetResizable();
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsThemeFonts);

		lpCreateControl->pControl = pControlGallery;
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_STYLES)
	{
		if (lpCreateControl->bToolBar)
		{
			CXTPControlGallery* pControlGallery = new CXTPControlGallery();
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
			
			lpCreateControl->pControl = pControlGallery;
		}
		else
		{
			CXTPControlGallery* pControlGallery = new CXTPControlGallery();
			pControlGallery->SetResizable();
			pControlGallery->SetControlSize(CSize(235 + 72, 56 * 3));
			pControlGallery->SetItems(m_pItemsStyles);

			lpCreateControl->pControl = pControlGallery;
		}
		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_SHAPES)
	{
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(200, 200));
		pControlGallery->SetResizable();
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsShapes);
		
		lpCreateControl->pControl = pControlGallery;
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

	pCommands->InsertAllCommandsCategory();
	pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pCommands->InsertNewMenuCategory();


	cs.DoModal();
}

void CMainFrame::OnViewTheme(UINT nTheme)
{
	EnableOffice2007Frame(NULL);

	BOOL bEnableAnimation = GetCommandBars()->GetPaintManager()->m_bEnableAnimation;
	GetCommandBars()->SetTheme((XTPPaintTheme)(nTheme - ID_VIEW_THEME_OFFICE2000));
	GetCommandBars()->GetPaintManager()->m_bEnableAnimation = bEnableAnimation;

	if (nTheme >= ID_VIEW_THEME_OFFICE2007)
	{
		EnableOffice2007Frame(GetCommandBars());
	}

	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateViewTheme(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((int)pCmdUI->m_nID == GetCommandBars()->GetPaintManager()->GetCurrentTheme() + ID_VIEW_THEME_OFFICE2000 ? TRUE : FALSE);

}


void CMainFrame::OnClose()
{
	SaveCommandBars(_T("CommandBars2"));

	CFrameWnd::OnClose();
}

void CMainFrame::OnGalleryShapes(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nShape = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryShapes(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nShape);
	}
	pCmdUI->Enable(TRUE);
}



void CMainFrame::OnGalleryStyles(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nStyle = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryStyles(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nStyle);
	}
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnGalleryStyleSet(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			m_nStyleSet = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryStyleSet(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nStyleSet);
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

void CMainFrame::OnUpdateGalleryThemeColors(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nThemeColors);
	}
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnGalleryThemeFonts(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		
		if (pItem)
		{
			m_nThemeFonts = pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryThemeFonts(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pGallery = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));
	
	if (pGallery)
	{
		pGallery->SetCheckedItem(m_nThemeFonts);
	}
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnStylesChange() 
{
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnGalleryTable(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pGallery = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pGallery)
	{
		CXTPControlGalleryItem* pItem = pGallery->GetItem(pGallery->GetSelectedItem());
		if (pItem)
		{
			
		}

		*pResult = TRUE; // Handled
	}
}

void CMainFrame::OnUpdateGalleryTable(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnViewAnimate() 
{
	GetCommandBars()->GetPaintManager()->m_bEnableAnimation ^= 1;
	
}

void CMainFrame::OnUpdateViewAnimate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetCommandBars()->GetPaintManager()->m_bEnableAnimation);	
}



void CMainFrame::OnStylesPreviewStart(NMHDR* /*pHdr*/, LRESULT* /*presult*/)
{
	TRACE(_T("\nOnStylesPreviewStart\n"));
}

void CMainFrame::OnStylesPreviewCancel(NMHDR* /*pHdr*/, LRESULT* /*presult*/)
{
	TRACE(_T("OnStylesPreviewCancel\n"));
}

void CMainFrame::OnStylesPreviewApply(NMHDR* /*pHdr*/, LRESULT* /*presult*/)
{
	TRACE(_T("OnStylesPreviewApply\n"));
}

void CMainFrame::OnStylesPreviewChange(NMHDR* pHdr, LRESULT* /*presult*/)
{
	NMXTPCONTROL* pNM = (NMXTPCONTROL*)pHdr;
	if (pNM->pControl->GetType() == xtpControlGallery)
	{
		CXTPControlGallery* pGallery = (CXTPControlGallery*)pNM->pControl;
		int nSelected = (pGallery->IsItemSelected() ? pGallery->GetSelectedItem() : -1);

		TRACE(_T("OnStylesPreviewChange, %i\n"), nSelected);
	}
}
