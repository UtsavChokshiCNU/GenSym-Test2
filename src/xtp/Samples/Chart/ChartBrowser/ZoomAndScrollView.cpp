// ZoomAndScrollView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "ZoomAndScrollView.h"


// CZoomAndScrollView

IMPLEMENT_DYNCREATE(CZoomAndScrollView, CBaseView)

CZoomAndScrollView::CZoomAndScrollView()
	: CBaseView(CZoomAndScrollView::IDD)
{
	m_strCaption = _T("Zoom and Scroll");
	
	m_bShowLabels = FALSE;
	m_bShowMarkers = FALSE;

	m_bAllowZoom = TRUE;
	m_bAllowScroll = TRUE;	
}

CZoomAndScrollView::~CZoomAndScrollView()
{
}

void CZoomAndScrollView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_SHOWMARKERS, m_bShowMarkers);

	DDX_Check(pDX, IDC_CHECK_ALLOWSCROLL, m_bAllowScroll);
	DDX_Check(pDX, IDC_CHECK_ALLOWZOOM, m_bAllowZoom);

}

BEGIN_MESSAGE_MAP(CZoomAndScrollView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_SHOWMARKERS, OnCheckShowMarkers)

	ON_BN_CLICKED(IDC_CHECK_ALLOWSCROLL, OnCheckAllowScroll)
	ON_BN_CLICKED(IDC_CHECK_ALLOWZOOM, OnCheckAllowZoom)
END_MESSAGE_MAP()


// CZoomAndScrollView diagnostics

#ifdef _DEBUG
void CZoomAndScrollView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CZoomAndScrollView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CZoomAndScrollView message handlers


void CZoomAndScrollView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();


}


void CZoomAndScrollView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(FALSE);

	CXTPChartTitle* pSubTitle = m_wndChartControl.GetContent()->GetTitles()->Add(new CXTPChartTitle());
	pSubTitle->SetText(_T("Use mouse wheel to zoom chart"));
	pSubTitle->SetDocking(xtpChartDockBottom);
	pSubTitle->SetAlignment(xtpChartAlignFar);
	pSubTitle->SetFont(CXTPChartFont::GetTahoma8());
	pSubTitle->SetTextColor(CXTPChartColor::Gray);


	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	if (pCollection)
	{
		CXTPChartSeries* pSeries1 = pCollection->Add(new CXTPChartSeries());
		if (pSeries1)
		{

			CXTPChartSeriesPointCollection* pPoints = pSeries1->GetPoints();
			if (pPoints)
			{
				// Fill series data
				double yValue = 50.0;
				for(int pointIndex = 0; pointIndex < 300; pointIndex ++)
				{
					yValue = yValue + ( (double)rand() / RAND_MAX * 10.0 - 5.0 );

					pPoints->Add(new CXTPChartSeriesPoint(pointIndex, yValue));
				}

			}

			CXTPChartPointSeriesStyle* pStyle =  new CXTPChartLineSeriesStyle();
			pSeries1->SetStyle(pStyle);

			pStyle->GetLabel()->SetVisible(FALSE);
			pStyle->GetMarker()->SetSize(5);
			pStyle->GetMarker()->SetVisible(FALSE);

			pSeries1->SetArgumentScaleType(xtpChartScaleNumerical);

			CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeries1->GetDiagram());

			pDiagram->GetAxisX()->GetRange()->SetViewAutoRange(FALSE);
			pDiagram->GetAxisX()->GetRange()->SetViewMinValue(0);
			pDiagram->GetAxisX()->GetRange()->SetViewMaxValue(200);

			
		}

	}

	// Set the X and Y Axis title for the series.
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pCollection->GetAt(0)->GetDiagram());
	ASSERT (pDiagram);


	pDiagram->SetAllowZoom(TRUE);
	pDiagram->SetAllowScroll(TRUE);

}



void CZoomAndScrollView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void CZoomAndScrollView::OnCheckShowMarkers() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetVisible(m_bShowMarkers);
	}
}

void CZoomAndScrollView::OnCheckAllowScroll() 
{
	UpdateData();
	
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, m_wndChartControl.GetContent()->GetPanels()->GetAt(0));
	ASSERT(pDiagram);
	
	pDiagram->SetAllowScroll(m_bAllowScroll);
}

void CZoomAndScrollView::OnCheckAllowZoom() 
{
	UpdateData();
	
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, m_wndChartControl.GetContent()->GetPanels()->GetAt(0));
	ASSERT(pDiagram);
	
	pDiagram->SetAllowZoom(m_bAllowZoom);
}
