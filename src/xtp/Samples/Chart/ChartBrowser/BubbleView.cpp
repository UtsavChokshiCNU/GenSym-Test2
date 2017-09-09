// BubbleView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "BubbleView.h"


// CBubbleView

IMPLEMENT_DYNCREATE(CBubbleView, CBaseView)

CBubbleView::CBubbleView()
	: CBaseView(CBubbleView::IDD)
{
	m_strCaption = _T("Bubble Style");

	m_dMinSize = 1.5;
	m_dMaxSize = 3.5;
	m_nTransparency = 3;
	m_nMarkerType = 0;

}

CBubbleView::~CBubbleView()
{
}

void CBubbleView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	DDX_Text(pDX, IDC_EDIT_MIN, m_dMinSize);
	DDX_Text(pDX, IDC_EDIT_MAX, m_dMaxSize);
	DDX_CBIndex(pDX, IDC_COMBO_TRANSPARENCY, m_nTransparency);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
}

BEGIN_MESSAGE_MAP(CBubbleView, CBaseView)
	ON_EN_CHANGE(IDC_EDIT_MIN, OnEnChangeEditMin)
	ON_EN_CHANGE(IDC_EDIT_MAX, OnEnChangeEditMax)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSPARENCY, OnCbnSelchangeComboTransparency)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)
END_MESSAGE_MAP()


// CBubbleView diagnostics

#ifdef _DEBUG
void CBubbleView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CBubbleView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBubbleView message handlers


void CBubbleView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();

	CreateChart();
}

CXTPChartSeriesPoint* CreateBubblePoint(LPCTSTR lpszLegendText, double nYear, double nValue, double dWidth, BOOL bPie)
{
	CXTPChartSeriesPoint* pPoint = new CXTPChartSeriesPoint((bPie ? nValue : nYear), (bPie ? nYear : nValue), dWidth);
	pPoint->SetLegentText(lpszLegendText);
	return pPoint;
}

void CBubbleView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Top 10 States by Population"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);

	pSeries->SetName(_T("Top 10 States by Population"));
	CXTPChartBubbleSeriesStyle* pStyle = new CXTPChartBubbleSeriesStyle();
	pSeries->SetStyle(pStyle);

	CXTPChartSeriesPoint* pPoint = NULL;
	CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();
	BOOL bPie = FALSE;

	pPoint = pPoints->Add(CreateBubblePoint(_T("California"), 10, 37.623, 11.95, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreateBubblePoint(_T("Texas"), 9, 25.532, 7.81, bPie));
	pPoint = pPoints->Add(CreateBubblePoint(_T("New York"), 8, 20.987, 6.31, bPie));
	pPoint = pPoints->Add(CreateBubblePoint(_T("Florida"), 7, 18.145, 5.97, bPie));
	pPoint = pPoints->Add(CreateBubblePoint(_T("Illinois"), 6, 13.320, 4.2, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreateBubblePoint(_T("Pennsylvania"), 5, 12.875, 4.06, bPie));
	pPoint = pPoints->Add(CreateBubblePoint(_T("Ohio"), 4, 11.650, 3.75, bPie));
	pPoint = pPoints->Add(CreateBubblePoint(_T("Michigan"), 3, 10.340, 3.29, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreateBubblePoint(_T("Georgia"), 2, 9.964, 3.12, bPie));
	pPoint = pPoints->Add(CreateBubblePoint(_T("North Carolina"), 1, 9.120, 3, bPie));

	pStyle->GetLabel()->SetFormat(_T("{V}%%"));

	pStyle->SetMinSize(1.5);
	pStyle->SetMaxSize(3.5);
	pStyle->SetTransparency(135);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	// Set the X and Y Axis title for the series.
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Population in Millions"));
	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);

	pDiagram->GetAxisX()->SetReversed(TRUE);
	pDiagram->GetAxisX()->GetLabel()->SetVisible(FALSE);
	pDiagram->GetAxisX()->GetTickMarks()->SetVisible(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(48);
	pDiagram->GetAxisY()->GetRange()->SetMinValue(5);
	pDiagram->GetAxisX()->GetRange()->SetShowZeroLevel(FALSE);
}

void CBubbleView::UpdateBubbleSize()
{
	UpdateData();

	if (m_dMinSize <= m_dMaxSize)
	{
		CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

		CXTPChartBubbleSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartBubbleSeriesStyle, pSeries->GetStyle());
		ASSERT(pStyle);

		pStyle->SetMinSize(m_dMinSize);
		pStyle->SetMaxSize(m_dMaxSize);
	}

}


void CBubbleView::OnEnChangeEditMin()
{
	UpdateBubbleSize();
}

void CBubbleView::OnEnChangeEditMax()
{
	UpdateBubbleSize();
}

void CBubbleView::OnCbnSelchangeComboTransparency()
{
	UpdateData();

	int nTransparency = m_nTransparency * 45;
	if (nTransparency > 255) nTransparency = 255;

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartBubbleSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartBubbleSeriesStyle, pSeries->GetStyle());
	ASSERT(pStyle);

	pStyle->SetTransparency(nTransparency);

}

void CBubbleView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartBubbleSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartBubbleSeriesStyle, pSeries->GetStyle());
	ASSERT(pStyle);

	pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
}