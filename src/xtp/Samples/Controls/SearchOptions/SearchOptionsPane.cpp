// SearchOptionsPane.cpp : implementation file
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
#include "searchoptions.h"
#include "SearchOptionsPane.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchOptionsPane

IMPLEMENT_DYNCREATE(CSearchOptionsPane, CXTPSearchOptionsView)

CSearchOptionsPane::CSearchOptionsPane()
: CXTPSearchOptionsView(CSearchOptionsPane::IDD)
, m_bFirstTime(true)
{
	//{{AFX_DATA_INIT(CSearchOptionsPane)
	//}}AFX_DATA_INIT

	// load the search icon that is displayed in the upper left corner.
	m_hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_SEARCH), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
}

CSearchOptionsPane::~CSearchOptionsPane()
{
	// free GDI
	if (m_hIcon != NULL)
		::DestroyIcon(m_hIcon);

	CXTPRegistryManager regManager;
	regManager.WriteProfileInt(_T("Settings"), _T("Keyword"), m_expKeywords.IsExpanded());
	regManager.WriteProfileInt(_T("Settings"), _T("Filters"), m_expFilters.IsExpanded());
}

void CSearchOptionsPane::DoDataExchange(CDataExchange* pDX)
{
	CXTPSearchOptionsView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchOptionsPane)
	DDX_Control(pDX, IDC_TXT_SEP, m_txtSep);
	DDX_Control(pDX, IDC_EXP_KEYWORD, m_expKeywords);
	DDX_Control(pDX, IDC_EXP_FILTERS, m_expFilters);
	DDX_Control(pDX, IDC_COMBO_FAVORITES, m_combFavorites);
	DDX_Control(pDX, IDC_COMBO_ATMOST, m_combAtMost);
	DDX_Control(pDX, IDC_COMBO_ATLEAST, m_combAtLeast);
	DDX_Control(pDX, IDC_CHK_ATMOST, m_chkAtMost);
	DDX_Control(pDX, IDC_CHK_ATLEAST, m_chkAtLeast);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btnClear);
	DDX_Control(pDX, IDC_TXT_BUTNOT, m_txtButNot);
	DDX_Control(pDX, IDC_TXT_CONTAINING, m_txtContaining);
	DDX_Control(pDX, IDC_ICO_SEARCH, m_icoSearch);
	DDX_Control(pDX, IDC_TXT_WORDS, m_txtWords);
	DDX_Control(pDX, IDC_TXT_LETTERS, m_txtLetters);
	DDX_Control(pDX, IDC_TXT_HIDE_WORDS, m_txtHideWords);
	DDX_Control(pDX, IDC_TXT_HIDE_LETTERS, m_txtHideLetters);
	DDX_Control(pDX, IDC_TXT_FAVORITES, m_txtFavorites);
	DDX_Control(pDX, IDC_EDIT_WORDS, m_editWords);
	DDX_Control(pDX, IDC_EDIT_LETTERS, m_editLetters);
	DDX_Control(pDX, IDC_EDIT_CONTAINING, m_editContaining);
	DDX_Control(pDX, IDC_EDIT_BUTNOT, m_editButNot);
	DDX_Control(pDX, IDC_EDIT_ATMOST, m_editAtMost);
	DDX_Control(pDX, IDC_EDIT_ATLEAST, m_editAtLeast);
	DDX_Control(pDX, IDC_TXT_SEARCHTITLE, m_txtTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchOptionsPane, CXTPSearchOptionsView)
	//{{AFX_MSG_MAP(CSearchOptionsPane)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_CAPTION, OnCaptionClose)

	ON_SON_XTP_ITEMCONTRACTING(IDC_EXP_FILTERS, OnFiltersContracting)
	ON_SON_XTP_ITEMCONTRACT(IDC_EXP_FILTERS, OnFiltersContract)
	ON_SON_XTP_ITEMEXPANDING(IDC_EXP_FILTERS, OnFiltersExpanding)
	ON_SON_XTP_ITEMEXPAND(IDC_EXP_FILTERS, OnFiltersExpand)

	ON_SON_XTP_ITEMCONTRACTING(IDC_EXP_KEYWORD, OnKeywordContracting)
	ON_SON_XTP_ITEMCONTRACT(IDC_EXP_KEYWORD, OnKeywordContract)
	ON_SON_XTP_ITEMEXPANDING(IDC_EXP_KEYWORD, OnKeywordExpanding)
	ON_SON_XTP_ITEMEXPAND(IDC_EXP_KEYWORD, OnKeywordExpand)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchOptionsPane diagnostics

#ifdef _DEBUG
void CSearchOptionsPane::AssertValid() const
{
	CXTPSearchOptionsView::AssertValid();
}

void CSearchOptionsPane::Dump(CDumpContext& dc) const
{
	CXTPSearchOptionsView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSearchOptionsPane message handlers

int CSearchOptionsPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPSearchOptionsView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the caption.
	if (!m_wndCaption.Create(this, _T("Search"), CPWS_EX_RAISED_EDGE|CPWS_EX_CLOSEBUTTON,
		WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|SS_CENTER|SS_CENTERIMAGE, CRect(0,0,0,0), IDC_CAPTION))
	{
		TRACE0( "Unable to create caption.\n" );
		return -1;
	}

	// Move the caption to its default location.
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 19;
	rect.right += 2;
	m_wndCaption.MoveWindow(&rect);

	return 0;
}

void CSearchOptionsPane::OnCaptionClose()
{
	// get a pointer to the application's frame window
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT_VALID(pMainFrame);

	// hide this pane.
	pMainFrame->ToggleSearchPane();
}

void CSearchOptionsPane::OnInitialUpdate()
{
	CXTPSearchOptionsView::OnInitialUpdate();

	if ( m_bFirstTime )
	{
		// set the title icon.
		m_icoSearch.SetIcon(m_hIcon);

		// set the font for the search title.
		m_txtTitle.SetFont(&XTPAuxData().fontBold);

		m_txtTitle.ModifyStyle(NULL, SS_ELLIPSISMASK);
		m_txtContaining.ModifyStyle(NULL, SS_ELLIPSISMASK);
		m_txtButNot.ModifyStyle(NULL, SS_ELLIPSISMASK);

		// Set control resizing.
		SetResize(IDC_CAPTION,         XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_TXT_SEARCHTITLE, XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_TXT_SEP,         XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_TXT_CONTAINING,  XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_EDIT_CONTAINING, XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_TXT_BUTNOT,      XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_EDIT_BUTNOT,     XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_BTN_SEARCH,      XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_EXP_FILTERS,     XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_EDIT_ATLEAST,    XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_COMBO_ATLEAST,   XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_EDIT_ATMOST,     XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_COMBO_ATMOST,    XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_EXP_KEYWORD,     XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_EDIT_WORDS,      XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_TXT_WORDS,       XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_EDIT_LETTERS,    XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_TXT_LETTERS,     XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_TXT_FAVORITES,   XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_COMBO_FAVORITES, XTP_ANCHOR_TOPLEFT,  XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_BTN_DELETE,      XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
		SetResize(IDC_BTN_SAVE,        XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);

		// initialize the file and keyword filters search
		// option controls.
		InitFileFilters();
		InitKeywordFilters();

		// Show keywords conracted?
		CXTPRegistryManager regManager;
		if (!regManager.GetProfileInt(_T("Settings"), _T("Keyword"), FALSE)) {
			m_expKeywords.Contract();
		}

		// Show filters conracted?
		if (!regManager.GetProfileInt(_T("Settings"), _T("Filters"), FALSE)) {
			m_expFilters.Contract();
		}

		m_bFirstTime = false;
	}
}

void CSearchOptionsPane::InitFileFilters()
{
	// set the expand / contract text labels.

	m_expFilters.SetLabelText(
		_T("File Filters <<"), _T("File Filters >>"));

	// add the controls to the search options control,
	// these are the controls that are show and hidden when
	// the search options control is expanded or contracted.

	m_expFilters.AddControl(&m_chkAtLeast);
	m_expFilters.AddControl(&m_editAtLeast);
	m_expFilters.AddControl(&m_combAtLeast);
	m_expFilters.AddControl(&m_chkAtMost);
	m_expFilters.AddControl(&m_editAtMost);
	m_expFilters.AddControl(&m_combAtMost);

	// add the controls to the search options control that
	// are to be moved up or down in relation to the search
	// options control whenever the control is expanded or
	// contracted.

	m_expFilters.MoveControl(&m_expKeywords);
	m_expFilters.MoveControl(&m_txtHideWords);
	m_expFilters.MoveControl(&m_editWords);
	m_expFilters.MoveControl(&m_txtWords);
	m_expFilters.MoveControl(&m_txtHideLetters);
	m_expFilters.MoveControl(&m_editLetters);
	m_expFilters.MoveControl(&m_txtLetters);
	m_expFilters.MoveControl(&m_txtFavorites);
	m_expFilters.MoveControl(&m_combFavorites);
	m_expFilters.MoveControl(&m_btnDelete);
	m_expFilters.MoveControl(&m_btnSave);
}

void CSearchOptionsPane::InitKeywordFilters()
{
	// set the expand / contract text labels.

	m_expKeywords.SetLabelText(
		_T("Keyword / Spam Filters <<"), _T("Keyword / Spam Filters >>"));

	// add the controls to the search options control,
	// these are the controls that are show and hidden when
	// the search options control is expanded or contracted.

	m_expKeywords.AddControl(&m_txtHideWords);
	m_expKeywords.AddControl(&m_editWords);
	m_expKeywords.AddControl(&m_txtWords);
	m_expKeywords.AddControl(&m_txtHideLetters);
	m_expKeywords.AddControl(&m_editLetters);
	m_expKeywords.AddControl(&m_txtLetters);

	// add the controls to the search options control that
	// are to be moved up or down in relation to the search
	// options control whenever the control is expanded or
	// contracted.

	m_expKeywords.MoveControl(&m_txtFavorites);
	m_expKeywords.MoveControl(&m_combFavorites);
	m_expKeywords.MoveControl(&m_btnDelete);
	m_expKeywords.MoveControl(&m_btnSave);
}

void CSearchOptionsPane::OnFiltersContracting()
{
	//TODO: handle notification
}

void CSearchOptionsPane::OnFiltersContract()
{
	AdjustScrollSizes(&m_expFilters, false);
}

void CSearchOptionsPane::OnFiltersExpanding()
{
	//TODO: handle notification
}

void CSearchOptionsPane::OnFiltersExpand()
{
	AdjustScrollSizes(&m_expFilters, true);
}

void CSearchOptionsPane::OnKeywordContracting()
{
	//TODO: handle notification
}

void CSearchOptionsPane::OnKeywordContract()
{
	AdjustScrollSizes(&m_expKeywords, false);
}

void CSearchOptionsPane::OnKeywordExpanding()
{
	//TODO: handle notification
}

void CSearchOptionsPane::OnKeywordExpand()
{
	AdjustScrollSizes(&m_expKeywords, true);
}
