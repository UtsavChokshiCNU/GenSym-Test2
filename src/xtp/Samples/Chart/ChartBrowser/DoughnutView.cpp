// DoughnutView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "DoughnutView.h"


// CDoughnutView

IMPLEMENT_DYNCREATE(CDoughnutView, CPieView)

CDoughnutView::CDoughnutView(UINT nID)
	: CPieView(nID)	
{
	m_strCaption = _T("Doughnut Style");
	m_nHoleRadius = 60;

}

CDoughnutView::~CDoughnutView()
{
}

void CDoughnutView::DoDataExchange(CDataExchange* pDX)
{
	CPieView::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_HOLE_RADIUS, m_nHoleRadius);
}

BEGIN_MESSAGE_MAP(CDoughnutView, CPieView)
	ON_EN_CHANGE(IDC_EDIT_HOLE_RADIUS, OnEnChangeEditHoleRadius)
END_MESSAGE_MAP()


// CDoughnutView diagnostics

#ifdef _DEBUG
void CDoughnutView::AssertValid() const
{
	CPieView::AssertValid();
}

#ifndef _WIN32_WCE
void CDoughnutView::Dump(CDumpContext& dc) const
{
	CPieView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDoughnutView message handlers

void CDoughnutView::OnInitialUpdate() 
{
	CPieView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartPieSeriesStyle* pStyle = (CXTPChartPieSeriesStyle*)pSeries->GetStyle();

	pStyle->SetHolePercent(60);
}

void CDoughnutView::OnEnChangeEditHoleRadius()
{
	UpdateData();

	if (m_nHoleRadius > 0 && m_nHoleRadius <= 100)
	{
		CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

		CXTPChartPieSeriesStyle* pStyle = (CXTPChartPieSeriesStyle*)pSeries->GetStyle();

		pStyle->SetHolePercent(m_nHoleRadius);

	}
}
