// HighLowView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "HighLowView.h"


// CHighLowView

IMPLEMENT_DYNCREATE(CHighLowView, CBaseView)

CHighLowView::CHighLowView(UINT nIDD)
	: CBaseView(nIDD)
{
	m_strCaption = _T("HighLow Style");

	m_bThickStyle = TRUE;

}

CHighLowView::~CHighLowView()
{
}

void CHighLowView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	DDX_Check(pDX, IDC_CHECK_THICKSTYLE, m_bThickStyle);
}

BEGIN_MESSAGE_MAP(CHighLowView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_THICKSTYLE, OnCheckThickStyle)
END_MESSAGE_MAP()


// CHighLowView diagnostics

#ifdef _DEBUG
void CHighLowView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CHighLowView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHighLowView message handlers

void CHighLowView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}

inline void AddCandleStylePoint(CXTPChartSeries* pSeries, LPCTSTR arg,  double low, double high, double open, double close)
{
	CXTPChartSeriesPoint* pPoint;	
	pPoint = pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(arg, low, high, open, close));	
}

inline void AddCustomLabel(CXTPChartDiagram2D* pDiagram, LPCTSTR lpszName, LPCTSTR lpszLabel)
{
	CXTPChartAxisCustomLabel* pLabel = new CXTPChartAxisCustomLabel();
	pLabel->SetAxisValue(lpszLabel);
	pLabel->SetText(lpszName);

	pDiagram->GetAxisX()->GetCustomLabels()->Add(pLabel);

}

void CHighLowView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Stock Prices"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetArgumentScaleType(xtpChartScaleQualitative);

	pSeries->SetName(_T("Microsoft"));
	pSeries->SetStyle(new CXTPChartHighLowSeriesStyle());

	AddCandleStylePoint(pSeries, _T("2009-12-28"), 30.89, 31.18, 31, 31.17);
	AddCandleStylePoint(pSeries, _T("2009-12-29"), 31.23, 31.5, 31.35, 31.39);
	AddCandleStylePoint(pSeries, _T("2009-12-30"), 30.8, 31.29, 31.15, 30.96);
	AddCandleStylePoint(pSeries, _T("2009-12-31"), 30.48, 30.99, 30.98, 30.48);
	AddCandleStylePoint(pSeries, _T("2010-01-04"), 30.59, 31.1, 30.62, 30.95);
	AddCandleStylePoint(pSeries, _T("2010-01-05"), 30.64, 31.1, 30.85, 30.96);
	AddCandleStylePoint(pSeries, _T("2010-01-06"), 30.52, 31.08, 30.88, 30.77);
	AddCandleStylePoint(pSeries, _T("2010-01-07"), 30.19, 30.7, 30.63, 30.45);
	AddCandleStylePoint(pSeries, _T("2010-01-08"), 30.24, 30.88, 30.28, 30.66);
	AddCandleStylePoint(pSeries, _T("2010-01-11"), 30.12, 30.76, 30.71, 30.27);
	AddCandleStylePoint(pSeries, _T("2010-01-12"), 29.91, 30.4, 30.15, 30.07);
	AddCandleStylePoint(pSeries, _T("2010-01-13"), 30.01, 30.52, 30.26, 30.35);
	AddCandleStylePoint(pSeries, _T("2010-01-14"), 30.26, 31.1, 30.31, 30.96);
	AddCandleStylePoint(pSeries, _T("2010-01-15"), 30.71, 31.24, 31.08, 30.86);
	AddCandleStylePoint(pSeries, _T("2010-01-19"), 30.68, 31.24, 30.75, 31.1);
	AddCandleStylePoint(pSeries, _T("2010-01-20"), 30.31, 30.94, 30.81, 30.59);
	AddCandleStylePoint(pSeries, _T("2010-01-21"), 30, 30.72, 30.61, 30.01);
	AddCandleStylePoint(pSeries, _T("2010-01-22"), 28.84, 30.2, 30, 28.96);
	AddCandleStylePoint(pSeries, _T("2010-01-25"), 29.1, 29.66, 29.24, 29.32);
	AddCandleStylePoint(pSeries, _T("2010-01-26"), 29.09, 29.85, 29.2, 29.5);
	AddCandleStylePoint(pSeries, _T("2010-01-27"), 29.02, 29.82, 29.35, 29.67);
	AddCandleStylePoint(pSeries, _T("2010-01-28"), 28.89, 29.87, 29.84, 29.16);
	AddCandleStylePoint(pSeries, _T("2010-01-29"), 27.66, 29.92, 29.9, 28.18);
	AddCandleStylePoint(pSeries, _T("2010-02-01"), 27.92, 28.48, 28.39, 28.41);
	AddCandleStylePoint(pSeries, _T("2010-02-02"), 28.14, 28.5, 28.37, 28.46);
	AddCandleStylePoint(pSeries, _T("2010-02-03"), 28.12, 28.79, 28.26, 28.63);
	AddCandleStylePoint(pSeries, _T("2010-02-04"), 27.81, 28.5, 28.38, 27.84);
	AddCandleStylePoint(pSeries, _T("2010-02-05"), 27.57, 28.28, 28, 28.02);
	AddCandleStylePoint(pSeries, _T("2010-02-08"), 27.57, 28.08, 28.01, 27.72);
	AddCandleStylePoint(pSeries, _T("2010-02-09"), 27.75, 28.34, 27.97, 28.01);
	AddCandleStylePoint(pSeries, _T("2010-02-10"), 27.84, 28.24, 28.03, 27.99);
	AddCandleStylePoint(pSeries, _T("2010-02-11"), 27.7, 28.4, 27.93, 28.12);
	AddCandleStylePoint(pSeries, _T("2010-02-12"), 27.58, 28.06, 27.81, 27.93);
	AddCandleStylePoint(pSeries, _T("2010-02-16"), 28.02, 28.37, 28.13, 28.35);
	AddCandleStylePoint(pSeries, _T("2010-02-17"), 28.36, 28.65, 28.53, 28.59);
	AddCandleStylePoint(pSeries, _T("2010-02-18"), 28.51, 29.03, 28.59, 28.97);
	AddCandleStylePoint(pSeries, _T("2010-02-19"), 28.69, 28.92, 28.79, 28.77);
	AddCandleStylePoint(pSeries, _T("2010-02-22"), 28.65, 28.94, 28.84, 28.73);
	AddCandleStylePoint(pSeries, _T("2010-02-23"), 28.09, 28.83, 28.68, 28.33);
	AddCandleStylePoint(pSeries, _T("2010-02-24"), 28.38, 28.79, 28.52, 28.63);
	AddCandleStylePoint(pSeries, _T("2010-02-25"), 28.02, 28.65, 28.27, 28.6);
	AddCandleStylePoint(pSeries, _T("2010-02-26"), 28.51, 28.85, 28.65, 28.67);
	AddCandleStylePoint(pSeries, _T("2010-03-01"), 28.53, 29.05, 28.77, 29.02);
	AddCandleStylePoint(pSeries, _T("2010-03-02"), 28.24, 29.3, 29.08, 28.46);
	AddCandleStylePoint(pSeries, _T("2010-03-09"), 28.35, 28.61, 28.51, 28.46);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);


	pDiagram->GetAxisY()->GetTitle()->SetText(_T("US Dollars"));
	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetRange()->SetShowZeroLevel(FALSE);
	pDiagram->GetAxisY()->GetGridLines()->SetMinorVisible(TRUE);

	pDiagram->GetAxisX()->GetLabel()->SetVisible(TRUE);

    AddCustomLabel(pDiagram, _T("29"), _T("2009-12-29"));
    AddCustomLabel(pDiagram, _T("Jan"), _T("2010-01-04"));
    AddCustomLabel(pDiagram, _T("12"), _T("2010-01-12"));
    AddCustomLabel(pDiagram, _T("21"), _T("2010-01-21"));
    AddCustomLabel(pDiagram, _T("28"), _T("2010-01-28"));
    AddCustomLabel(pDiagram, _T("Feb"), _T("2010-02-01"));
    AddCustomLabel(pDiagram, _T("8"), _T("2010-02-08"));
    AddCustomLabel(pDiagram, _T("17"), _T("2010-02-17"));
    AddCustomLabel(pDiagram, _T("25"), _T("2010-02-25"));
    AddCustomLabel(pDiagram, _T("Mar"), _T("2010-03-01"));
    AddCustomLabel(pDiagram, _T("9"), _T("2010-03-09"));
}


void CHighLowView::OnCheckThickStyle()
{
	UpdateData();

	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	

	CXTPChartHighLowSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartHighLowSeriesStyle, pContent->GetSeries()->GetAt(0)->GetStyle());
	ASSERT(pStyle);

	pStyle->SetLineThickness(m_bThickStyle ? 2 : 1);

}