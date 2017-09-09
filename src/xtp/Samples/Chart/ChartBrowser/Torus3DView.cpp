// Torus3DView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "Torus3DView.h"


// CTorus3DView

IMPLEMENT_DYNCREATE(CTorus3DView, CDoughnutView)

CTorus3DView::CTorus3DView()
	: CDoughnutView(CTorus3DView::IDD)
{
	m_strCaption = _T("Torus3D Style");

}

CTorus3DView::~CTorus3DView()
{
}

void CTorus3DView::DoDataExchange(CDataExchange* pDX)
{
	CDoughnutView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTorus3DView, CDoughnutView)
END_MESSAGE_MAP()


// CTorus3DView diagnostics

#ifdef _DEBUG
void CTorus3DView::AssertValid() const
{
	CDoughnutView::AssertValid();
}

#ifndef _WIN32_WCE
void CTorus3DView::Dump(CDumpContext& dc) const
{
	CDoughnutView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTorus3DView message handlers

void CTorus3DView::OnInitialUpdate() 
{
	CPieView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartTorus3DSeriesStyle* pStyle = new CXTPChartTorus3DSeriesStyle();
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
