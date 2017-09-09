// CandleStickView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "CandleStickView.h"


// CCandleStickView

IMPLEMENT_DYNCREATE(CCandleStickView, CHighLowView)

CCandleStickView::CCandleStickView()
	: CHighLowView(CCandleStickView::IDD)
{

}

CCandleStickView::~CCandleStickView()
{
}

void CCandleStickView::DoDataExchange(CDataExchange* pDX)
{
	CHighLowView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCandleStickView, CHighLowView)
END_MESSAGE_MAP()


// CCandleStickView diagnostics

#ifdef _DEBUG
void CCandleStickView::AssertValid() const
{
	CHighLowView::AssertValid();
}

#ifndef _WIN32_WCE
void CCandleStickView::Dump(CDumpContext& dc) const
{
	CHighLowView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCandleStickView message handlers
void CCandleStickView::OnInitialUpdate() 
{
	CHighLowView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	pSeries->SetStyle(new CXTPChartCandleStickSeriesStyle());
}
