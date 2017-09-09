// Pie3DView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "Pie3DView.h"


// CPie3DView

IMPLEMENT_DYNCREATE(CPie3DView, CPieView)

CPie3DView::CPie3DView()
	: CPieView(CPie3DView::IDD)
{
	m_strCaption = _T("Pie3D Style");

}

CPie3DView::~CPie3DView()
{
}

void CPie3DView::DoDataExchange(CDataExchange* pDX)
{
	CPieView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPie3DView, CPieView)
END_MESSAGE_MAP()


// CPie3DView diagnostics

#ifdef _DEBUG
void CPie3DView::AssertValid() const
{
	CPieView::AssertValid();
}

#ifndef _WIN32_WCE
void CPie3DView::Dump(CDumpContext& dc) const
{
	CPieView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPie3DView message handlers
void CPie3DView::OnInitialUpdate() 
{
	CPieView::OnInitialUpdate();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartPie3DSeriesStyle* pStyle = new CXTPChartPie3DSeriesStyle();
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
