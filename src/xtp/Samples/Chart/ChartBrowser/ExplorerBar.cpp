// ExplorerBar.cpp : implementation file
//

#include "stdafx.h"
#include "chartbrowser.h"
#include "ExplorerBar.h"

#include "BarView.h"
#include "PointView.h"
#include "BubbleView.h"
#include "LineView.h"
#include "SplineView.h"
#include "AreaView.h"
#include "SplineAreaView.h"
#include "PieView.h"
#include "DoughnutView.h"
#include "Pie3DView.h"
#include "Doughnut3DView.h"
#include "Torus3DView.h"
#include "HighLowView.h"
#include "CandleStickView.h"
#include "StackedBarView.h"
#include "StackedAreaView.h"
#include "BarAndLineView.h"
#include "ChartFromFileView.h"
#include "MarkupTitleView.h"
#include "DiagramsView.h"
#include "StepLineView.h"
#include "RangeBarView.h"
#include "SecondaryAxesView.h"
#include "MultipleView.h"
#include "ZoomAndScrollView.h"
#include "FunnelView.h"
#include "PyramidView.h"
#include "Pyramid3DView.h"
#include "FastLineView.h"
#include "ScatterLineView.h"
#include "SideBySideStackedBarView.h"
#include "StackedSplineAreaView.h"
#include "GanttView.h"
#include "RadarPointView.h"
#include "RadarLineView.h"
#include "RadarAreaView.h"
#include "RadarSplineView.h"
#include "LogarithmicView.h"
#include "DateTimeView.h"


#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CXTPExplorerPane

CXTPExplorerPane::CXTPExplorerPane()
{

}


BEGIN_MESSAGE_MAP(CXTPExplorerPane, CControlBar)
//{{AFX_MSG_MAP(CXTPExplorerPane)
	ON_WM_SIZE()
//}}AFX_MSG_MAP

#ifdef _XTP_INCLUDE_TOOLKIT
	ON_MESSAGE(XTPWM_TASKPANEL_NOTIFY, OnTaskPanelNotify)
#else
	ON_NOTIFY(TVN_SELCHANGED, 100, OnTreeSelChanged)
#endif

END_MESSAGE_MAP()

void CXTPExplorerPane::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	// update the dialog controls added to the status bar
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

void CXTPExplorerPane::Create(CWnd* pParentWnd)
{
	m_dwStyle = CBRS_LEFT;
	
	CControlBar::Create(AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)), 0, WS_CHILD | WS_VISIBLE| m_dwStyle, 
		CRect(0, 0, 0, 0), pParentWnd, 0xE807);

	m_wndExplorerBar.Create(this);
	
}

CSize CXTPExplorerPane::CalcFixedLayout(BOOL, BOOL /*bHorz*/)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	
	CSize size(240, 32767);
	return size;
}

void CXTPExplorerPane::OnSize(UINT nType, int cx, int cy)
{
	CControlBar::OnSize(nType, cx, cy);

	if (m_wndExplorerBar)
	{
		m_wndExplorerBar.MoveWindow(0, 0, cx, cy);
	}
}

#ifdef _XTP_INCLUDE_TOOLKIT

LRESULT CXTPExplorerPane::OnTaskPanelNotify(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case XTP_TPN_CLICK:
		{
			CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)lParam;
			TRACE(_T("Click Event: pItem.Caption = %s, pItem.ID = %i\n"), pItem->GetCaption(), pItem->GetID());
			
			m_wndExplorerBar.OnItemClick(pItem->GetID());
		}
		break;
	}
	return 0;
}

#else

void CXTPExplorerPane::OnTreeSelChanged(NMHDR*, LRESULT* /*pResult*/)
{
	HTREEITEM hItem = m_wndExplorerBar.GetSelectedItem();

	UINT nID = (UINT)m_wndExplorerBar.GetItemData(hItem);
	if (nID > 0)
	{
		m_wndExplorerBar.OnItemClick(nID);
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////
// CExplorerBar

CExplorerBar::CExplorerBar()
{
}

CExplorerBar::~CExplorerBar()
{
}


BEGIN_MESSAGE_MAP(CExplorerBar, CXTPTaskPanel)
	//{{AFX_MSG_MAP(CExplorerBar)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

enum IDITEM
{
	ID_ITEM_BARSTYLE = 100,
	ID_ITEM_SIDEBYDIDESTACKEDBARSTYLE,
	
	ID_ITEM_POINTSTYLE,
	ID_ITEM_BUBBLESTYLE,
	ID_ITEM_LINESTYLE ,
	ID_ITEM_SCATTERLINESTYLE,
	ID_ITEM_FASTLINESTYLE ,
	ID_ITEM_STEPLINESTYLE, 
	ID_ITEM_SPLINESTYLE ,
	
	ID_ITEM_AREASTYLE,
	ID_ITEM_SPLINEAREASTYLE,
	ID_ITEM_STACKEDSPLINEAREASTYLE,
	ID_ITEM_FULLSTACKEDSPLINEAREASTYLE,

	ID_ITEM_PIESTYLE,
	ID_ITEM_DOUGHNUTSTYLE,

	ID_ITEM_PIE3DSTYLE,
	ID_ITEM_DOUGHNUT3DSTYLE,
	ID_ITEM_TORUS3DSTYLE, 

	ID_ITEM_RADARPOINT, 
	ID_ITEM_RADARLINE, 
	ID_ITEM_RADARAREA, 
	ID_ITEM_RADARSPLINE, 

	ID_ITEM_HIGHLOWSTYLE, 
	ID_ITEM_CANDLESTICKSTYLE,

	ID_ITEM_STACKEDBARSTYLE,
	ID_ITEM_FULLSTACKEDBARSTYLE,
	ID_ITEM_STACKEDAREASTYLE, 
	ID_ITEM_FULLSTACKEDAREASTYLE, 

	ID_ITEM_FUNNELSTYLE, 
	ID_ITEM_PYRAMIDSTYLE, 
	ID_ITEM_PYRAMID3DSTYLE, 

	ID_ITEM_RANGEBARSTYLE,
	ID_ITEM_GANTTSTYLE,

	ID_ITEM_BARANDLINESTYLE, 

	ID_ITEM_LOADFROMFILE, 
	ID_ITEM_MARKUPTITLE, 
	ID_ITEM_DIAGRAMS, 
	ID_ITEM_SECONDARYAXES, 
	ID_ITEM_MULTIPLEVIEW, 
	ID_ITEM_ZOOMANDSCROLL, 
	
	ID_ITEM_DATETIME,
	ID_ITEM_LOGARITHMIC,
};

/////////////////////////////////////////////////////////////////////////////
// CExplorerBar message handlers

void* CExplorerBar::AddGroup(LPCTSTR lpszGroup)
{
#ifdef _XTP_INCLUDE_TOOLKIT
	CXTPTaskPanelGroup* pGroup = CXTPTaskPanel::AddGroup(0);
	pGroup->SetCaption(lpszGroup);
	
	return pGroup;

#else
	// add the parent item, make it bold
	HTREEITEM htiParent = InsertItem(lpszGroup);
	
	SetItemState (htiParent, TVIS_BOLD | TVIS_EXPANDED, TVIS_BOLD | TVIS_EXPANDED);
	

	return htiParent;	

#endif
}

void CExplorerBar::AddLinkItem(void* pGroup, UINT nID, LPCTSTR lpszCaption)
{
#ifdef _XTP_INCLUDE_TOOLKIT
	
	CXTPTaskPanelGroupItem* pItem = ((CXTPTaskPanelGroup*)pGroup)->AddLinkItem(nID);
	pItem->SetCaption(lpszCaption);
#else
	
	HTREEITEM htiChild = InsertItem(lpszCaption, (HTREEITEM)pGroup);
	SetItemData(htiChild, nID);

#endif
}

void CExplorerBar::Create(CWnd* pWndParent)
{

#ifdef _XTP_INCLUDE_TOOLKIT
	CXTPTaskPanel::Create(WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), pWndParent, 0);

	SetTheme(xtpTaskPanelThemeShortcutBarOffice2007);
	SetHotTrackStyle(xtpTaskPanelHighlightItem);

	SetSingleSelection(TRUE);
	SetSelectItemOnFocus(TRUE);
		
	SetIconSize(CSize(0, 0));

#else
	
	CTreeCtrl::Create(WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | 
		TVS_SHOWSELALWAYS | WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), pWndParent, 100);
	
#endif	


	void* pGroup = AddGroup(_T("Bar Styles"));

	AddLinkItem(pGroup, ID_ITEM_BARSTYLE, _T("Bar"));


	AddLinkItem(pGroup, ID_ITEM_STACKEDBARSTYLE, _T("Stacked Bar"));

	AddLinkItem(pGroup, ID_ITEM_FULLSTACKEDBARSTYLE, _T("100% Stacked Bar"));

	AddLinkItem(pGroup, ID_ITEM_SIDEBYDIDESTACKEDBARSTYLE, _T("Side-by-Side Stacked Bar"));

	pGroup = AddGroup(_T("Point Styles"));

	AddLinkItem(pGroup, ID_ITEM_POINTSTYLE, _T("Scatter Point"));

	AddLinkItem(pGroup, ID_ITEM_BUBBLESTYLE, _T("Bubble"));

	pGroup = AddGroup(_T("Line Styles"));

	AddLinkItem(pGroup, ID_ITEM_LINESTYLE, _T("Line"));

	AddLinkItem(pGroup, ID_ITEM_SCATTERLINESTYLE, _T("Scatter Line"));

	AddLinkItem(pGroup, ID_ITEM_FASTLINESTYLE, _T("Fast Line"));

	AddLinkItem(pGroup, ID_ITEM_STEPLINESTYLE, _T("Step Line"));

	AddLinkItem(pGroup, ID_ITEM_SPLINESTYLE, _T("Spline"));

	pGroup = AddGroup(_T("Area Styles"));

	AddLinkItem(pGroup, ID_ITEM_AREASTYLE, _T("Area"));

	AddLinkItem(pGroup, ID_ITEM_SPLINEAREASTYLE, _T("Spline Area"));

	AddLinkItem(pGroup, ID_ITEM_STACKEDAREASTYLE, _T("Stacked Area"));

	AddLinkItem(pGroup, ID_ITEM_STACKEDSPLINEAREASTYLE, _T("Stacked Spline Area"));

	AddLinkItem(pGroup, ID_ITEM_FULLSTACKEDAREASTYLE, _T("100% Stacked Area"));	

	AddLinkItem(pGroup, ID_ITEM_FULLSTACKEDSPLINEAREASTYLE, _T("100% Stacked Spline Area"));

	pGroup = AddGroup(_T("Range Styles"));

	AddLinkItem(pGroup, ID_ITEM_RANGEBARSTYLE, _T("Range Bar"));
	AddLinkItem(pGroup, ID_ITEM_GANTTSTYLE, _T("Gantt"));


	pGroup = AddGroup(_T("Pie Styles"));

	AddLinkItem(pGroup, ID_ITEM_PIESTYLE, _T("Pie"));

	AddLinkItem(pGroup, ID_ITEM_DOUGHNUTSTYLE, _T("Doughnut"));

	AddLinkItem(pGroup, ID_ITEM_PIE3DSTYLE, _T("Pie3D"));

	AddLinkItem(pGroup, ID_ITEM_DOUGHNUT3DSTYLE, _T("Doughnut3D"));

	AddLinkItem(pGroup, ID_ITEM_TORUS3DSTYLE, _T("Torus3D"));

	pGroup = AddGroup(_T("Radar/Polar Styles"));
	
	AddLinkItem(pGroup, ID_ITEM_RADARPOINT, _T("Radar Point"));
	AddLinkItem(pGroup, ID_ITEM_RADARLINE, _T("Radar Line"));
	AddLinkItem(pGroup, ID_ITEM_RADARAREA, _T("Radar Area"));
	AddLinkItem(pGroup, ID_ITEM_RADARSPLINE, _T("Polar Spline And Area"));


	pGroup = AddGroup(_T("Funnel and Pyramid Styles"));

	AddLinkItem(pGroup, ID_ITEM_FUNNELSTYLE, _T("Funnel"));
	
	AddLinkItem(pGroup, ID_ITEM_PYRAMIDSTYLE, _T("Pyramid"));
	
	AddLinkItem(pGroup, ID_ITEM_PYRAMID3DSTYLE, _T("Pyramid 3D"));
	


	pGroup = AddGroup(_T("Financial Styles"));

	AddLinkItem(pGroup, ID_ITEM_HIGHLOWSTYLE, _T("High Low"));

	AddLinkItem(pGroup, ID_ITEM_CANDLESTICKSTYLE, _T("Candle Stick"));


	pGroup = AddGroup(_T("Combinations"));

	AddLinkItem(pGroup, ID_ITEM_BARANDLINESTYLE, _T("Bar & Line"));

	pGroup = AddGroup(_T("Features"));

	AddLinkItem(pGroup, ID_ITEM_LOADFROMFILE, _T("Load From Builder File"));

	AddLinkItem(pGroup, ID_ITEM_MARKUPTITLE, _T("Markup Titles"));

	AddLinkItem(pGroup, ID_ITEM_DIAGRAMS, _T("Multiple Diagrams"));

	AddLinkItem(pGroup, ID_ITEM_SECONDARYAXES, _T("Secondary Axes"));
	
	AddLinkItem(pGroup, ID_ITEM_MULTIPLEVIEW, _T("Single Content/Multiple Views"));
	
	AddLinkItem(pGroup, ID_ITEM_ZOOMANDSCROLL, _T("Zoom And Scroll"));

	AddLinkItem(pGroup, ID_ITEM_DATETIME, _T("DateTime Scale"));
	
	AddLinkItem(pGroup, ID_ITEM_LOGARITHMIC, _T("Logarithmic Scale"));


#ifdef _XTP_INCLUDE_TOOLKIT
	
	Reposition();
	GetAt(0)->SetSelectedItem((CXTPTaskPanelGroupItem*)GetAt(0)->GetItems()->GetAt(0));
	OnSrollChanged(0);
#endif
}

void CExplorerBar::OnItemClick(UINT nID)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	switch (nID)
	{
	case ID_ITEM_POINTSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CPointView)); 
		break;
	case ID_ITEM_BARSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CBarView));
		break;
	case ID_ITEM_SIDEBYDIDESTACKEDBARSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CSideBySideStackedBarView));
		break;
	case ID_ITEM_RANGEBARSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CRangeBarView));
		break;
	case ID_ITEM_GANTTSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CGanttView));
		break;
	case ID_ITEM_STACKEDBARSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CStackedBarView));
		break;
	case ID_ITEM_FULLSTACKEDBARSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CFullStackedBarView));
		break;
	case ID_ITEM_BUBBLESTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CBubbleView));
		break;
	case ID_ITEM_LINESTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CLineView));
		break;
	case ID_ITEM_SCATTERLINESTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CScatterLineView));
		break;
	case ID_ITEM_FASTLINESTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CFastLineView));
		break;
	case ID_ITEM_STEPLINESTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CStepLineView));
		break;
	case ID_ITEM_SPLINESTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CSplineView));
		break;
	case ID_ITEM_AREASTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CAreaView));
		break;
	case ID_ITEM_STACKEDAREASTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CStackedAreaView));
	    break;
	case ID_ITEM_FULLSTACKEDSPLINEAREASTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CFullStackedSplineAreaView));
		break;
	case ID_ITEM_STACKEDSPLINEAREASTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CStackedSplineAreaView));
		break;
	case ID_ITEM_FULLSTACKEDAREASTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CFullStackedAreaView));
	    break;
	case ID_ITEM_SPLINEAREASTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CSplineAreaView));
	    break;
	case ID_ITEM_PIESTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CPieView));
	    break;
	case ID_ITEM_DOUGHNUTSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CDoughnutView));
	    break;
	case ID_ITEM_PIE3DSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CPie3DView));
	    break;
	case ID_ITEM_DOUGHNUT3DSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CDoughnut3DView));
	    break;
	case ID_ITEM_TORUS3DSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CTorus3DView));
	    break;
	case ID_ITEM_RADARPOINT:
		pMainFrame->SetView(RUNTIME_CLASS(CRadarPointView));
		break;
	case ID_ITEM_RADARLINE:
		pMainFrame->SetView(RUNTIME_CLASS(CRadarLineView));
		break;
	case ID_ITEM_RADARAREA:
		pMainFrame->SetView(RUNTIME_CLASS(CRadarAreaView));
		break;
	case ID_ITEM_RADARSPLINE:
		pMainFrame->SetView(RUNTIME_CLASS(CRadarSplineView));
		break;
	case ID_ITEM_FUNNELSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CFunnelView));
	    break;
	case ID_ITEM_PYRAMIDSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CPyramidView));
	    break;
	case ID_ITEM_PYRAMID3DSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CPyramid3DView));
		break;
	case ID_ITEM_HIGHLOWSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CHighLowView));
	    break;
	case ID_ITEM_CANDLESTICKSTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CCandleStickView));
	    break;
	case ID_ITEM_BARANDLINESTYLE:
		pMainFrame->SetView(RUNTIME_CLASS(CBarAndLineView));
	    break;
	case ID_ITEM_LOADFROMFILE:
		pMainFrame->SetView(RUNTIME_CLASS(CChartFromFileView));
	    break;
	case ID_ITEM_MARKUPTITLE:
		pMainFrame->SetView(RUNTIME_CLASS(CMarkupTitleView));
	    break;
	case ID_ITEM_DIAGRAMS:
		pMainFrame->SetView(RUNTIME_CLASS(CDiagramsView));
	    break;
	case ID_ITEM_SECONDARYAXES:
		pMainFrame->SetView(RUNTIME_CLASS(CSecondaryAxesView));
		break;
	case ID_ITEM_MULTIPLEVIEW:
		pMainFrame->SetView(RUNTIME_CLASS(CMultipleView));
		break;
	case ID_ITEM_ZOOMANDSCROLL:
		pMainFrame->SetView(RUNTIME_CLASS(CZoomAndScrollView));
		break;	
	case ID_ITEM_LOGARITHMIC:
		pMainFrame->SetView(RUNTIME_CLASS(CLogarithmicView));
		break;	
	case ID_ITEM_DATETIME:
		pMainFrame->SetView(RUNTIME_CLASS(CDateTimeView));
		break;	
	}
}

