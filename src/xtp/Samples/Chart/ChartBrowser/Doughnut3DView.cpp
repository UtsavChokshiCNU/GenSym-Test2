// Doughnut3DView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "Doughnut3DView.h"


// CDoughnut3DView

IMPLEMENT_DYNCREATE(CDoughnut3DView, CDoughnutView)

CDoughnut3DView::CDoughnut3DView()
	: CDoughnutView(CDoughnut3DView::IDD)
{
	m_strCaption = _T("Doughnut3D Style");

}

CDoughnut3DView::~CDoughnut3DView()
{
}

void CDoughnut3DView::DoDataExchange(CDataExchange* pDX)
{
	CDoughnutView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDoughnut3DView, CDoughnutView)
END_MESSAGE_MAP()


// CDoughnut3DView diagnostics

#ifdef _DEBUG
void CDoughnut3DView::AssertValid() const
{
	CDoughnutView::AssertValid();
}

#ifndef _WIN32_WCE
void CDoughnut3DView::Dump(CDumpContext& dc) const
{
	CDoughnutView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDoughnut3DView message handlers

void CDoughnut3DView::OnInitialUpdate() 
{
	CPieView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartPie3DSeriesStyle* pStyle = new CXTPChartPie3DSeriesStyle();
	pStyle->SetHolePercent(60);
	pSeries->SetStyle(pStyle);

	pStyle->GetLabel()->SetFormat(_T("{V} Million"));

	//pStyle->GetLabel()->SetAntialiasing(TRUE);
	// set chart subtitle.
	CXTPChartTitle* pSubTitle = m_wndChartControl.GetContent()->GetTitles()->Add(new CXTPChartTitle());
	pSubTitle->SetText(_T("Click and drag to rotate"));
	pSubTitle->SetDocking(xtpChartDockBottom);
	pSubTitle->SetAlignment(xtpChartAlignFar);
	pSubTitle->SetFont(CXTPChartFont::GetTahoma8());
	pSubTitle->SetTextColor(CXTPChartColor::Gray);

}
