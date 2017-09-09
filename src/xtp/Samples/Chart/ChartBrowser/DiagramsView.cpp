// DiagramsView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "DiagramsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagramsView

IMPLEMENT_DYNCREATE(CDiagramsView, CBaseView)

CDiagramsView::CDiagramsView()
	: CBaseView(CDiagramsView::IDD)
{
	//{{AFX_DATA_INIT(CDiagramsView)
	m_bShowLabels = TRUE;
	m_nDirection = 1;
	//}}AFX_DATA_INIT

	m_strCaption = _T("Multiple Diagrams");
}

CDiagramsView::~CDiagramsView()
{
} 

void CDiagramsView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiagramsView)
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_CBIndex(pDX, IDC_COMBO_DIRECTION, m_nDirection);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

}


BEGIN_MESSAGE_MAP(CDiagramsView, CBaseView)
	//{{AFX_MSG_MAP(CDiagramsView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_CBN_SELCHANGE(IDC_COMBO_DIRECTION, OnDirectionChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagramsView diagnostics

#ifdef _DEBUG
void CDiagramsView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CDiagramsView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiagramsView message handlers


void CDiagramsView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}

void CDiagramsView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);
	pContent->GetLegend()->SetVerticalAlignment(xtpChartLegendFarOutside);
	pContent->GetLegend()->SetHorizontalAlignment(xtpChartLegendCenter);
	pContent->GetLegend()->SetDirection(xtpChartLegendLeftToRight);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Total Hours Worked"));


	CXTPChartDiagram2D* pDiagram1 = (CXTPChartDiagram2D*)pContent->GetPanels()->Add(new CXTPChartDiagram2D());
	CXTPChartDiagram2D* pDiagram2 = (CXTPChartDiagram2D*)pContent->GetPanels()->Add(new CXTPChartDiagram2D());
	CXTPChartPieDiagram* pDiagram3 = (CXTPChartPieDiagram*)pContent->GetPanels()->Add(new CXTPChartPieDiagram());
	pDiagram3;

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Daily"));
	pSeries->SetStyle(new CXTPChartBarSeriesStyle());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("1 January"), 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("2 January"), 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("3 January"), 6));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("4 January"), 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("5 January"), 7));
	pSeries->SetDiagram(pDiagram1);
	pDiagram1->SetRotated(TRUE);


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	
	pSeries->SetName(_T("Summary"));

	pSeries->SetStyle(new CXTPChartLineSeriesStyle());

	CXTPChartPointSeriesLabel* pLabel = DYNAMIC_DOWNCAST(CXTPChartPointSeriesLabel, pSeries->GetStyle()->GetLabel());

	pLabel->SetLineLength(20);
	pLabel->SetAngle(70);
	
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("1 January"), 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("2 January"), 8 + 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("3 January"), 8 + 7 + 6));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("4 January"), 8 + 7 + 6 + 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("5 January"), 8 + 7 + 6 + 7 + 7));
	pSeries->SetDiagram(pDiagram2);
	pDiagram2->SetRotated(TRUE);

	
	pDiagram1->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram1->GetAxisX()->GetTitle()->SetText(_T("Date"));

	pDiagram1->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram1->GetAxisY()->GetTitle()->SetText(_T("Hours"));

	pDiagram2->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram2->GetAxisY()->GetTitle()->SetText(_T("Hours"));
	pDiagram2->GetAxisX()->GetLabel()->SetVisible(FALSE);

	pDiagram2->GetAxisX()->GetTitle()->SetText(_T("Date"));
	pDiagram2->GetAxisX()->GetTitle()->SetVisible(FALSE);


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Overview"));

	pSeries->SetStyle(new CXTPChartPieSeriesStyle());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("1 January"), 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("2 January"), 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("3 January"), 6));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("4 January"), 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("5 January"), 7));
	pSeries->SetDiagram(pDiagram2);

	CXTPChartPieSeriesLabel* pPieLabel = DYNAMIC_DOWNCAST(CXTPChartPieSeriesLabel, pSeries->GetStyle()->GetLabel());
	ASSERT(pPieLabel);
	pPieLabel->SetPosition(xtpChartPieLabelRadial);

	m_wndChartControl.GetContent()->SetPanelDirection((XTPChartPanelDirection)m_nDirection);
}

void CDiagramsView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartSeriesStyle* pStyle = pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}	
}

void CDiagramsView::OnDirectionChanged()
{
	UpdateData();

	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	
	pContent->SetPanelDirection((XTPChartPanelDirection)m_nDirection);

	CXTPChartDiagram2D* pDiagram1 = (CXTPChartDiagram2D*)pContent->GetPanels()->GetAt(0);
	CXTPChartDiagram2D* pDiagram2 = (CXTPChartDiagram2D*)pContent->GetPanels()->GetAt(1);

	if (m_nDirection == xtpChartPanelVertical)
	{
		pDiagram1->SetRotated(FALSE);
		pDiagram2->SetRotated(FALSE);

		pDiagram2->GetAxisX()->GetLabel()->SetVisible(TRUE);

		pDiagram1->GetAxisX()->GetTitle()->SetVisible(FALSE);
		pDiagram2->GetAxisX()->GetTitle()->SetVisible(TRUE);
	}
	else
	{
		pDiagram1->SetRotated(TRUE);
		pDiagram2->SetRotated(TRUE);

		pDiagram2->GetAxisX()->GetLabel()->SetVisible(FALSE);

		pDiagram1->GetAxisX()->GetTitle()->SetVisible(TRUE);
		pDiagram2->GetAxisX()->GetTitle()->SetVisible(FALSE);
	}
}
