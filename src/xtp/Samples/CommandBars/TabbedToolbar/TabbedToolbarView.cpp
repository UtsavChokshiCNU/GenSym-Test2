// TabbedToolbarView.cpp : implementation of the CTabbedToolbarView class
//

#include "stdafx.h"
#include "TabbedToolbar.h"

#include "TabbedToolbarDoc.h"
#include "TabbedToolbarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarView

IMPLEMENT_DYNCREATE(CTabbedToolbarView, CFormView)

BEGIN_MESSAGE_MAP(CTabbedToolbarView, CFormView)
	//{{AFX_MSG_MAP(CTabbedToolbarView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarView construction/destruction

CTabbedToolbarView::CTabbedToolbarView()
	: CFormView(CTabbedToolbarView::IDD)
{
	//{{AFX_DATA_INIT(CTabbedToolbarView)
	//}}AFX_DATA_INIT
}

CTabbedToolbarView::~CTabbedToolbarView()
{
}

void CTabbedToolbarView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabbedToolbarView)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TABCONTROL, m_wndTabControl);
}

BOOL CTabbedToolbarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTabbedToolbarView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	
	m_pageTabControl.Create(IDD_PAGE_ADVANCED, &m_wndTabControl);
	m_pageTabControl.ModifyStyle(0, DS_CONTROL);
	m_pageTabControl.ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	m_pageTheme.Create(IDD_PAGE_THEME, &m_wndTabControl);
	m_pageTheme.ModifyStyle(0, DS_CONTROL);
	m_pageTheme.ModifyStyleEx(0, WS_EX_CONTROLPARENT);


	m_wndTabControl.InsertItem(0, _T("Theme"), m_pageTheme, 0);
	m_wndTabControl.InsertItem(1, _T("Advanced"), m_pageTabControl, 0);
	m_wndTabControl.ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	m_wndTabControl.GetPaintManager()->m_bDisableLunaColors = TRUE;
	m_wndTabControl.SetAppearance(xtpTabAppearanceVisualStudio2005);


}

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarView diagnostics

#ifdef _DEBUG
void CTabbedToolbarView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTabbedToolbarView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTabbedToolbarDoc* CTabbedToolbarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabbedToolbarDoc)));
	return (CTabbedToolbarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarView message handlers



void CTabbedToolbarView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/) 
{
	if (m_pageTabControl.GetSafeHwnd())
	{
		m_pageTabControl.Update();
	}

	if (m_pageTheme.GetSafeHwnd())
	{
		m_pageTheme.Update();
	}
	
}
