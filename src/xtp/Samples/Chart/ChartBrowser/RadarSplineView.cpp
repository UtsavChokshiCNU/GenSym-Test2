// RadarSplineView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "RadarSplineView.h"


// CRadarSplineView

IMPLEMENT_DYNCREATE(CRadarSplineView, CBaseView)

CRadarSplineView::CRadarSplineView()
	: CBaseView(CRadarSplineView::IDD)
{
	m_strCaption = _T("Radar Line Style");
	m_bShowLabels = FALSE;
	
	m_bShowAxisX = 1;
	m_bShowAxisY = 1;
	m_bInterlaced = TRUE;
}

CRadarSplineView::~CRadarSplineView()
{
}

void CRadarSplineView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_AXISX, m_bShowAxisX);
	DDX_Check(pDX, IDC_CHECK_AXISY, m_bShowAxisY);
	DDX_Check(pDX, IDC_CHECK_INTERLACED, m_bInterlaced);
}

BEGIN_MESSAGE_MAP(CRadarSplineView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)

	ON_BN_CLICKED(IDC_CHECK_AXISX, OnCheckShowAxisX)
	ON_BN_CLICKED(IDC_CHECK_AXISY, OnCheckShowAxisY)
	ON_BN_CLICKED(IDC_CHECK_INTERLACED, OnCheckInterlaced)

END_MESSAGE_MAP()


// CRadarSplineView diagnostics

#ifdef _DEBUG
void CRadarSplineView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CRadarSplineView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRadarSplineView message handlers

void CRadarSplineView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}

void CRadarSplineView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Polar Chart"));


	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	
	pSeries->SetName(_T("Series 1"));
	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);
	
	CXTPChartRadarSplineAreaSeriesStyle* pSplineAreaStyle = new CXTPChartRadarSplineAreaSeriesStyle();
	pSplineAreaStyle->GetMarker()->SetVisible(FALSE);
	pSeries->SetStyle(pSplineAreaStyle);


	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(0, 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(30, 1.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(60, 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(90, 4));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(120, 2));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(150, 10));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(180, 9.2));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(210, 2));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(240, 3.7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(270, 8.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(300, 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(330, 6));
	


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Series 2"));
	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);

	CXTPChartRadarSplineSeriesStyle* pSplineStyle = new CXTPChartRadarSplineSeriesStyle();
	pSplineStyle->GetMarker()->SetVisible(FALSE);

	pSeries->SetStyle(pSplineStyle);


	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(0, 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(20, 3));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(30, 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(50, 4.8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(60, 6.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(70, 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(80, 8.6));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(90, 9));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(105, 7.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(120, 9));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(150, 5.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(170, 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(180, 3));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(195, 9));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(210, 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(220, 9));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(230, 9));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(240, 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(260, 2.3));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(270, 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(285, 4));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(300, 1.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(315, 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(330, 8.2));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(345, 9));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(0, 8));
	


	
	CXTPChartRadarDiagram* pDiagram = DYNAMIC_DOWNCAST(CXTPChartRadarDiagram, pSeries->GetDiagram());
	ASSERT (pDiagram);
	
	pDiagram->GetAxisX()->SetInterlaced(m_bInterlaced);
	pDiagram->GetAxisY()->SetInterlaced(FALSE);

	pDiagram->GetAxisX()->GetRange()->SetMinValue(0);
	pDiagram->GetAxisX()->GetRange()->SetMaxValue(360 - 30);
	pDiagram->GetAxisX()->GetRange()->SetAutoRange(FALSE);

	pDiagram->GetAxisX()->SetGridSpacing(30);
	pDiagram->GetAxisX()->SetGridSpacingAuto(FALSE);


	OnCheckShowLabels();

}

void CRadarSplineView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void CRadarSplineView::OnCheckShowAxisX() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisX()->SetVisible(m_bShowAxisX);
}

void CRadarSplineView::OnCheckShowAxisY() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisY()->SetVisible(m_bShowAxisY);
}

void CRadarSplineView::OnCheckInterlaced() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisX()->SetInterlaced(m_bInterlaced);
}
