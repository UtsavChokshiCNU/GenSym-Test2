// StackedBarView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "StackedBarView.h"


// CStackedBarView

IMPLEMENT_DYNCREATE(CStackedBarView, CBaseView)

CStackedBarView::CStackedBarView()
	: CBaseView(CStackedBarView::IDD)
{

	m_bShowLabels = TRUE;
	m_strCaption = _T("Stacked Bar Style");
	m_bRotated = FALSE;
}

CStackedBarView::~CStackedBarView()
{
}

void CStackedBarView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	DDX_Check(pDX, IDC_CHECK_ROTATED, m_bRotated);
}

BEGIN_MESSAGE_MAP(CStackedBarView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_ROTATED, OnBnClickedCheckRotated)
END_MESSAGE_MAP()


// CStackedBarView diagnostics

#ifdef _DEBUG
void CStackedBarView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CStackedBarView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStackedBarView message handlers


void CStackedBarView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}

void CStackedBarView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Total Hours Worked"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Quoted"));
	pSeries->SetStyle(new CXTPChartStackedBarSeriesStyle());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Sam"), 11));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Jesse"), 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Dave"), 4.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Max"), 6));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Brian"), 5));


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Hourly"));
	pSeries->SetStyle(new CXTPChartStackedBarSeriesStyle());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Sam"), 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Jesse"), 9.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Dave"), 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Max"), 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Brian"), 11));


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Unbillable"));
	pSeries->SetStyle(new CXTPChartStackedBarSeriesStyle());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Sam"), 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Jesse"), 2));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Dave"), 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Max"), 1));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Brian"), 4));


	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Employee"));

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Hours"));
}

void CStackedBarView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

//////////////////////////////////////////////////////////////////////////
// CFullStackedBarView

IMPLEMENT_DYNCREATE(CFullStackedBarView, CStackedBarView)

CFullStackedBarView::CFullStackedBarView()
{
	m_strCaption = _T("100% Stacked Bar Style");
}

void CFullStackedBarView::OnInitialUpdate()
{
	CStackedBarView::OnInitialUpdate();

	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	for(int i = 0; i < pContent->GetSeries()->GetCount(); i++)
	{
		CXTPChartStackedBarSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartStackedBarSeriesStyle, 
			 pContent->GetSeries()->GetAt(i)->GetStyle());
		ASSERT(pStyle);

		pStyle->SetStackHeight(100);
	}

	CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pContent->GetPrimaryDiagram());
	pDiagram->GetAxisY()->GetRange()->SetSideMargins(FALSE);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetPattern(_T("{V}%%"));
	


}
void CStackedBarView::OnBnClickedCheckRotated()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeriesCollection->GetAt(0)->GetDiagram());

	pDiagram->SetRotated(m_bRotated);
}
