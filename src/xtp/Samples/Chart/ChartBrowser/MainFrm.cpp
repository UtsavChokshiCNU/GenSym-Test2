// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ChartBrowser.h"

#include "MainFrm.h"
#include "BarView.h"

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
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP

#ifndef _XTP_INCLUDE_TOOLKIT
	ON_WM_INITMENUPOPUP()
#else
	ON_XTP_INITCOMMANDSPOPUP()
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
#endif

	ON_UPDATE_COMMAND_UI_RANGE(ID_APPEARANCE_APPEARANCE, (ID_APPEARANCE_APPEARANCE + 3), OnUpdateAppearance)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PALETTE_PALETTE, (ID_PALETTE_PALETTE + 30), OnUpdatePalette)

	ON_COMMAND_RANGE(ID_APPEARANCE_APPEARANCE, (ID_APPEARANCE_APPEARANCE + 3), OnAppearance)
	ON_COMMAND_RANGE(ID_PALETTE_PALETTE, (ID_PALETTE_PALETTE + 30), OnPalette)

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

LPCTSTR lpszPalettes = _T("Victorian;Vibrant Pastel;Vibrant;Tropical;Summer;Spring Time;Rainbow;Purple;Primary Colors;Postmodern;Photodesign;Pastel;Office;Orange Green;Nature;Natural;Impresionism;Illustration;Harvest;Green Brown;Green Blue;Green;Gray;Four Color;Fire;Earth Tone;Danville;Caribbean;Cappuccino;Blue Gray;Blue;");
LPCTSTR lpszAppearances = _T("Nature;Gray;Black;");

void CreateArray(CStringArray& array, LPCTSTR lpszList)
{
	CString str(lpszList);
	
	while (str.GetLength())
	{
		int nIndex = str.Find(';');
		
		CString strNext;
		if (nIndex == -1)
		{
			strNext = str;
			str.Empty();
		}
		else
		{
			strNext = str.Left(nIndex);
			str.Delete(0, nIndex + 1);
		}
		
		array.Add(strNext);
	}
}



CMainFrame::CMainFrame()
{
	m_pView = NULL;	

	m_nAppearance = 0;
	m_nPalette = 9;

	CreateArray(m_arrPalette, lpszPalettes);
	CreateArray(m_arrAppearance, lpszAppearances);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	m_pView = new CBarView();
	// create a view to occupy the client area of the frame
	if (!((CView*)m_pView)->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

#ifdef _XTP_INCLUDE_TOOLKIT
	if (!InitCommandBars())
		return -1;
	
	CXTPPaintManager::SetTheme(xtpThemeRibbon);

	CXTPCommandBars* pCommandBars = GetCommandBars();
	
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagIgnoreSetMenuMessage);

	pCommandBars->EnableFrameTheme(TRUE);

#endif


#ifdef _XTP_INCLUDE_TOOLKIT
	m_paneManager.InstallDockingPanes(this);

	m_paneManager.CreatePane(IDR_PANE_EXPLORER, CRect(0, 0, 220, 300), xtpPaneDockLeft, 0);

	m_paneManager.SetTheme(xtpPaneThemeResource);

#endif

	m_wndExplorerBar.Create(this);
	m_wndExplorerBar.SetOwner(this);

	m_wndCaption.Create(this);


	m_pView->UpdateData(FALSE);
	UpdateAppearance();
	UpdatePalette();
	
	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	
	HBRUSH hBackground = 0;
#ifndef _XTP_INCLUDE_TOOLKIT
	hBackground = GetSysColorBrush(COLOR_3DDKSHADOW);
#endif

	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME), hBackground);
	
	
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	cs.dwExStyle |= WS_EX_CONTROLPARENT;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	
	cs.cx = 1000;
	cs.cy = 700;

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



/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	if (m_pView)
	{
		// forward focus to the view window
		m_pView->SetFocus();
	}
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_pView)
	{
		// let the view have first crack at the command
		if (m_pView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;
	}
	
	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

#ifdef _XTP_INCLUDE_TOOLKIT

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
						
			pPane->Attach(&m_wndExplorerBar);
		}
		
		return TRUE; // handled
	}
	
	
	return FALSE;
}

#endif

void CMainFrame::SetView(CRuntimeClass* pViewClass)
{

	CView* pOldView = m_pView;

	if (pOldView->GetRuntimeClass() == pViewClass)
		return;

	pOldView->SetDlgCtrlID(0);

	m_pView = DYNAMIC_DOWNCAST(CBaseView, pViewClass->CreateObject());
	ASSERT(m_pView);

	// create a view to occupy the client area of the frame
	if (!((CView*)m_pView)->Create(NULL, NULL, WS_CHILD | WS_BORDER,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return;
	}

	m_wndCaption.SetContent(m_pView->m_strCaption);
	SetActiveView(m_pView);

	m_pView->OnInitialUpdate();

	UpdateAppearance();
	UpdatePalette();

	RecalcLayout();

	m_pView->ShowWindow(SW_SHOWNOACTIVATE);
	if (pOldView)
	{
		pOldView->DestroyWindow();
	}
}

void CMainFrame::UpdateAppearance()
{
	CXTPChartControl* pChartControl = 
		(CXTPChartControl*)m_pView->GetDlgItem(IDC_CHARTCONTROL);
	if (!pChartControl)
		return;
	CString strAppearance(m_arrAppearance[m_nAppearance]);
	strAppearance.MakeUpper();

	pChartControl->GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_") + strAppearance);

	pChartControl->GetContent()->OnChartChanged();

}
void CMainFrame::UpdatePalette()
{
	CXTPChartControl* pChartControl = 
		(CXTPChartControl*)m_pView->GetDlgItem(IDC_CHARTCONTROL);
	if (!pChartControl)
		return;


	CString strPalette(m_arrPalette[m_nPalette]);
	strPalette.MakeUpper();
	strPalette.Replace(_T(" "), _T(""));

	pChartControl->GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE_") + strPalette);

	pChartControl->GetContent()->OnChartChanged();

}



#ifndef _XTP_INCLUDE_TOOLKIT

void CMainFrame::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu)
{
	int nCount = pMenu->GetMenuItemCount();
	if (nCount == 1)
	{
		if (pMenu->GetMenuItemID(0) == ID_PALETTE_PALETTE)
		{
			pMenu->DeleteMenu(0, MF_BYPOSITION);
			
			for (int i = 0; i < m_arrPalette.GetSize(); i++)
			{	
				pMenu->InsertMenu(i, 0, ID_PALETTE_PALETTE + i, m_arrPalette[i]);
			}
		}
		
		if (pMenu->GetMenuItemID(0) == ID_APPEARANCE_APPEARANCE)
		{
			pMenu->DeleteMenu(0, MF_BYPOSITION);
			
			for (int i = 0; i < m_arrAppearance.GetSize(); i++)
			{	
				pMenu->InsertMenu(i, 0, ID_APPEARANCE_APPEARANCE + i, m_arrAppearance[i]);
			}
		}
	}

	CFrameWnd::OnInitMenuPopup(pMenu, nIndex, bSysMenu);

}
#else

void CMainFrame::OnInitCommandsPopup(CXTPPopupBar* pCommandBar)
{
	if (pCommandBar->GetControls()->GetCount() > 1)
		return;

	if (pCommandBar->GetControl(0)->GetID() == ID_PALETTE_PALETTE)
	{
		pCommandBar->GetControls()->Remove(0);
		
		for (int i = 0; i < m_arrPalette.GetSize(); i++)
		{
			CXTPControl* pControl = pCommandBar->GetControls()->Add(xtpControlButton, ID_PALETTE_PALETTE + i);
			pControl->SetCaption(m_arrPalette[i]);
		}
	}

	if (pCommandBar->GetControl(0)->GetID() == ID_APPEARANCE_APPEARANCE)
	{
		pCommandBar->GetControls()->Remove(0);
		
		for (int i = 0; i < m_arrAppearance.GetSize(); i++)
		{
			CXTPControl* pControl = pCommandBar->GetControls()->Add(xtpControlButton, ID_APPEARANCE_APPEARANCE + i);
			pControl->SetCaption(m_arrAppearance[i]);
		}
	}
}

#endif


void CMainFrame::OnUpdatePalette(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);

	pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_PALETTE_PALETTE == m_nPalette ? 1 : 0);
}

void CMainFrame::OnUpdateAppearance(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);

	pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_APPEARANCE_APPEARANCE == m_nAppearance ? 1 : 0);
	
}


void CMainFrame::OnPalette(UINT nID)
{
	m_nPalette = nID - ID_PALETTE_PALETTE;
	UpdatePalette();
}

void CMainFrame::OnAppearance(UINT nID)
{
	m_nAppearance = nID - ID_APPEARANCE_APPEARANCE;
	UpdateAppearance();
}


void CMainFrame::RecalcLayout(BOOL bNotify)
{
#ifdef _XTP_INCLUDE_TOOLKIT
	CFrameWnd::RecalcLayout(bNotify);
#else
	if (m_bInRecalcLayout)
		return;

	bNotify;
	
	m_bInRecalcLayout = TRUE;

	m_nIdleFlags &= ~(idleLayout|idleNotify);
	
	AFX_SIZEPARENTPARAMS layout;
	layout.hDWP = ::BeginDeferWindowPos(8);
	GetClientRect(&layout.rect);

	if (m_wndStatusBar.GetSafeHwnd())
	{
		m_wndStatusBar.SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
	}

	::InflateRect(&layout.rect, -5, -5);

	if (m_wndExplorerBar.GetSafeHwnd())
	{
		m_wndExplorerBar.SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
	}

	layout.rect.left += 5;

	if (m_wndCaption)
	{
		m_wndCaption.SendMessage(WM_SIZEPARENT, 0, (LPARAM)&layout);
	}

	if (m_pView)
	{
		AfxRepositionWindow(&layout, m_pView->GetSafeHwnd(), &layout.rect);
	}

	::EndDeferWindowPos(layout.hDWP);

	m_bInRecalcLayout = FALSE;

#endif
}



BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
	return CWnd::OnEraseBkgnd(pDC);
}
