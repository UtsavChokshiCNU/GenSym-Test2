// GanttView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "GanttView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGanttView

IMPLEMENT_DYNCREATE(CGanttView, CBaseView)

CGanttView::CGanttView()
	: CBaseView(CGanttView::IDD)
{
	//{{AFX_DATA_INIT(CGanttView)
	m_bShowLabels = FALSE;
	//}}AFX_DATA_INIT

	m_bSideBySide = FALSE;
	m_strCaption = _T("Ganntt Style");
	m_bShowMarkers = FALSE;
}

CGanttView::~CGanttView()
{
} 

void CGanttView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGanttView)
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_SIDEBYSIDE, m_bSideBySide);
	DDX_Check(pDX, IDC_CHECK_SHOWMARKERS, m_bShowMarkers);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

}


BEGIN_MESSAGE_MAP(CGanttView, CBaseView)
	//{{AFX_MSG_MAP(CGanttView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_SIDEBYSIDE, OnCheckSideBySide)
	ON_BN_CLICKED(IDC_CHECK_SHOWMARKERS, OnCheckShowMarkers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGanttView diagnostics

#ifdef _DEBUG
void CGanttView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CGanttView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGanttView message handlers


void CGanttView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();

	OnCheckShowLabels();
	OnCheckSideBySide();
}

double GetDate(int nMonth, int nDay)
{
	//return COleDateTime(2010, nMonth, nDay, 0, 0, 0);
	return (nMonth - 1) * 31 + (nDay - 1);
}

void CGanttView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);
	pContent->GetLegend()->SetHorizontalAlignment(xtpChartLegendFar);
	pContent->GetLegend()->SetDirection(xtpChartLegendLeftToRight);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Project Development Schedule"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Planned"));
	pSeries->SetStyle(new CXTPChartGanttSeriesStyle());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Explore Market Need"), GetDate(1, 1), GetDate(3, 4)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Develop Concept for Product"), GetDate(2, 1), GetDate(3, 10)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Begin Development Cycle"), GetDate(3, 10), GetDate(10, 20)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Develop GUI"), GetDate(5, 1), GetDate(8, 15)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("User Interface Test Evaluation"), GetDate(7, 1), GetDate(8, 25)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Alpha Version Release"), GetDate(7, 13), GetDate(7, 24)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Beta Version Release"), GetDate(10, 13), GetDate(10, 24)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Design Box and CD Labels"), GetDate(10, 1), GetDate(11, 1)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Final Quality Testing"), GetDate(10, 1), GetDate(11, 25)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("FCS Release"), GetDate(11, 12), GetDate(11, 23)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Production and Packaging"), GetDate(11, 12), GetDate(11, 25)));


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	
	pSeries->SetName(_T("Completed"));

	CXTPChartGanttSeriesStyle* pStyle = new CXTPChartGanttSeriesStyle();
	pSeries->SetStyle(pStyle);
	pStyle->SetBarWidth(0.3);
	
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Explore Market Need"), GetDate(1, 1), GetDate(3, 4)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Develop Concept for Product"), GetDate(2, 1), GetDate(3, 10)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Begin Development Cycle"), GetDate(3, 10), GetDate(7, 7)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Develop GUI"), GetDate(5, 1), GetDate(7, 7)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("User Interface Test Evaluation"), GetDate(7, 1), GetDate(7, 7)));

	




	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Tasks"));
	pDiagram->GetAxisX()->SetReversed(TRUE);

	pDiagram->GetAxisY()->GetTitle()->SetVisible(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetShowZeroLevel(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetSideMargins(FALSE);

	CXTPChartAxisConstantLine* pProgressLine = pDiagram->GetAxisY()->GetConstantLines()->Add(new CXTPChartAxisConstantLine());
	pProgressLine->SetText(_T("Progress Line"));
	pProgressLine->SetAxisValue(GetDate(7, 7));
	pProgressLine->SetLegendVisible(FALSE);

	pDiagram->SetRotated(TRUE);
}

void CGanttView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels && i == 0);
	}
	
}


void CGanttView::OnCheckSideBySide() 
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		pStyle->SetSideBySide(m_bSideBySide);
	}
	
}


void CGanttView::OnCheckShowMarkers() 
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartGanttSeriesStyle* pStyle = (CXTPChartGanttSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		pStyle->GetMinValueMarker()->SetVisible(m_bShowMarkers);
		pStyle->GetMaxValueMarker()->SetVisible(m_bShowMarkers);
	}
}