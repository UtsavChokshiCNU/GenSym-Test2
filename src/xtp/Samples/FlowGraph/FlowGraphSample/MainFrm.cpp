// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FlowGraphSample.h"

#include "MainFrm.h"
#include "DialogPerfomanceTest.h"
#include "DialogControlsTest.h"
#include "DialogPageTransitionTest.h"

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
	ON_COMMAND(ID_TEST_GRAPHWITH500NODES, OnTestGraphwith500nodes)
	ON_COMMAND(ID_TEST_NODESWITHCONTROLS, OnTestNodeswithcontrols)
	ON_COMMAND(ID_TEST_PAGETRANSITION, OnTestPagetransition)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
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
	
	XTPPaintManager()->SetTheme(xtpThemeRibbon);
	
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

	pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME, IDR_TOOLBAR_ALPHA);

	CXTPStatusBarPane* pPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_ZOOM);
	pPane->SetText(_T("100%"));
	pPane->SetButton();
	pPane->SetTextAlignment(DT_CENTER);
	pPane->SetPadding(8, 0, 8, 0);
	pPane->SetWidth(pPane->GetBestFit());
	pPane->SetTooltip(_T("Zoom level. Click to open the Zoom dialog box."));
	pPane->SetCaption(_T("&Zoom"));
	pPane->SetBeginGroup(FALSE);
	
	CXTPStatusBarSliderPane* pZoomPane = (CXTPStatusBarSliderPane*)m_wndStatusBar.AddIndicator(new CXTPStatusBarSliderPane(), ID_INDICATOR_ZOOMSLIDER);
	pZoomPane->SetBeginGroup(FALSE);
	pZoomPane->SetWidth(130);
	pZoomPane->SetPos(500); // We will convert 0 -> 10%, 500 -> 100 %, 1000 -> 500 %
	pZoomPane->SetRange(0, 1000);
	pZoomPane->SetCaption(_T("&Zoom Slider"));
	pZoomPane->SetTooltip(_T("Zoom"));
	pZoomPane->SetTooltipPart(XTP_HTSCROLLUP, _T("Zoom Out"));
	pZoomPane->SetTooltipPart(XTP_HTSCROLLDOWN, _T("Zoom In"));

	EnableOffice2007Frame(pCommandBars);
	
	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));
	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

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


void CMainFrame::OnTestGraphwith500nodes()
{
	CDialogPerfomanceTest cd;
	cd.DoModal();
}

void CMainFrame::OnTestNodeswithcontrols()
{
	CDialogControlsTest cd;
	cd.DoModal();

}

void CMainFrame::OnTestPagetransition()
{
	CDialogPageTransitionTest cd;
	cd.DoModal();
}
