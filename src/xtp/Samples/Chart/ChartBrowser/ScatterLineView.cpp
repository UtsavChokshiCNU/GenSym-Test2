// ScatterLineView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "ScatterLineView.h"


// CScatterLineView

IMPLEMENT_DYNCREATE(CScatterLineView, CBaseView)

CScatterLineView::CScatterLineView()
	: CBaseView(CScatterLineView::IDD)
{
	m_strCaption = _T("Scatter Line Style");
	
	m_bShowLabels = FALSE;
	m_bShowMarkers = TRUE;

	m_nMarkerType = 0;
	m_nMarkerSize = 1;
}

CScatterLineView::~CScatterLineView()
{
}

void CScatterLineView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_SHOWMARKERS, m_bShowMarkers);

	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_SIZE, m_nMarkerSize);

}

BEGIN_MESSAGE_MAP(CScatterLineView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_SHOWMARKERS, OnCheckShowMarkers)

	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_SIZE, OnCbnSelchangeComboMarkerSize)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)
END_MESSAGE_MAP()


// CScatterLineView diagnostics

#ifdef _DEBUG
void CScatterLineView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CScatterLineView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScatterLineView message handlers


void CScatterLineView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();



	CComboBox* pComboBoxSize = (CComboBox*)GetDlgItem(IDC_COMBO_MARKER_SIZE);
	for (int i = 8; i <= 30; i += 2)
	{
		CString strSize;
		strSize.Format(_T("%d"), i);

		pComboBoxSize->AddString(strSize);
	}
	pComboBoxSize->SetCurSel(1);

	CreateChart();
}


void CScatterLineView::SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY)
{
	if (pDiagram)
	{
		CXTPChartAxis* pAxisX = pDiagram->GetAxisX();
		if (pAxisX)
		{
			CXTPChartAxisTitle* pTitle = pAxisX->GetTitle();
			if (pTitle)
			{
				pTitle->SetText(strAxisX);
				pTitle->SetVisible(TRUE);
			}
		}

		CXTPChartAxis* pAxisY = pDiagram->GetAxisY();
		if (pAxisY)
		{
			CXTPChartAxisTitle* pTitle = pAxisY->GetTitle();
			if (pTitle)
			{
				pTitle->SetText(strAxisY);
				pTitle->SetVisible(TRUE);
			}
		}
	}
}

void CScatterLineView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(FALSE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());

	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	if (pCollection)
	{

		pContent->EnableMarkup();
				
		pContent->GetLegend()->SetVisible(FALSE);

		CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
		pTitle->SetText(_T("Iso-Operational Curves - 1/d=0.5"));
		pTitle->SetDocking(xtpChartDockTop);


		pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
		pTitle->SetText(_T("<TextBlock FontSize='20'>µ/1000</TextBlock>"));
		pTitle->SetDocking(xtpChartDockLeft);

		pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
		pTitle->SetText(_T("<TextBlock FontSize='20' Margin = '1'>h<Run BaselineAlignment='Bottom' FontSize='10'>min</Run>[µm]</TextBlock>"));
		pTitle->SetDocking(xtpChartDockBottom);

		CXTPChartSeries* Series = pCollection->Add(new CXTPChartSeries());
		Series->SetName(_T("Series U/w = 60"));

		CXTPChartSeriesPointCollection* pPoints = Series->GetPoints();
		CXTPChartSeriesPoint* pPoint = NULL;

		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7, 3.1));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(8, 2.8));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.3, 2.7));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(11, 3.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(11.5, 4));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(12, 6.1));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(11.7, 8.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(11.1, 11.7));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(10.5, 14));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.5, 18));

		Series->SetStyle(new CXTPChartScatterLineSeriesStyle());
		Series->SetArgumentScaleType(xtpChartScaleNumerical);

		CXTPChartScatterLineSeriesStyle* pStyle = (CXTPChartScatterLineSeriesStyle*)Series->GetStyle();		
		pStyle->GetMarker()->SetType(xtpChartMarkerCircle);

		Series = pCollection->Add(new CXTPChartSeries());
		Series->SetName(_T("Series U/w = 50"));

		pPoints = Series->GetPoints();
		pPoint = NULL;
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5.9, 3.2));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7.1, 2.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(8.1, 2.3));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.5, 2.8));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(10.3, 3.6));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(10.6, 5.2));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(10.5, 7));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(10.2, 9.1));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.8, 11.4));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.1, 14.6));

		Series->SetStyle(new CXTPChartScatterLineSeriesStyle());
		Series->SetArgumentScaleType(xtpChartScaleNumerical);

		pStyle = (CXTPChartScatterLineSeriesStyle*)Series->GetStyle();		
		pStyle->GetMarker()->SetType(xtpChartMarkerHexagon);

		Series = pCollection->Add(new CXTPChartSeries());
		Series->SetName(_T("Series U/w = 40"));
		pPoints = Series->GetPoints();
		pPoint = NULL;
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(4.8, 3.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5.8, 2.3));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7, 2.1));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(8.4, 2.2));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.1, 2.8));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.5, 4.1));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.6, 5.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9.3, 7));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(9, 8.8));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(8.4, 11.6));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7.5, 15.8));

		Series->SetStyle(new CXTPChartScatterLineSeriesStyle());
		Series->SetArgumentScaleType(xtpChartScaleNumerical);

		pStyle = (CXTPChartScatterLineSeriesStyle*)Series->GetStyle();		
		pStyle->GetMarker()->SetType(xtpChartMarkerPentagon);
    

		Series = pCollection->Add(new CXTPChartSeries());
		Series->SetName(_T("Series U/w = 30"));
		pPoints = Series->GetPoints();
		pPoint = NULL;
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5.3, 1.9));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(6.9, 1.8));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7.7, 2.2));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(8.3, 3.2));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(8.5, 4));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(8.4, 5.1));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(8.2, 6.3));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7.8, 8.1));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(6.9, 11.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(6.3, 13.8));


		Series->SetStyle(new CXTPChartScatterLineSeriesStyle());
		Series->SetArgumentScaleType(xtpChartScaleNumerical);

		pStyle = (CXTPChartScatterLineSeriesStyle*)Series->GetStyle();		
		pStyle->GetMarker()->SetType(xtpChartMarkerDiamond);


		Series = pCollection->Add(new CXTPChartSeries());
		Series->SetName(_T("Series U/w = 20"));
		pPoints = Series->GetPoints();
		pPoint = NULL;
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(2.3, 5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(2.9, 3.3));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(3.8, 2));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5, 1.7));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5.8, 1.8));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(6.6, 2));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7, 2.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7.2, 3.1));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(7.1, 4));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(6.9, 5.3));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(6.4, 7.3));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5.9, 8.9));


		Series->SetStyle(new CXTPChartScatterLineSeriesStyle());
		Series->SetArgumentScaleType(xtpChartScaleNumerical);

		pStyle = (CXTPChartScatterLineSeriesStyle*)Series->GetStyle();		
		pStyle->GetMarker()->SetType(xtpChartMarkerStar);


		Series = pCollection->Add(new CXTPChartSeries());
		Series->SetName(_T("Series U/w = 10"));
		pPoints = Series->GetPoints();
		pPoint = NULL;
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(1.6, 5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(2.3, 2.3));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(2.7, 1.6));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(3.3, 1.4));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(4.2, 1.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(4.8, 1.7));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5, 1.8));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5.1, 2));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5.2, 2.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(5.1, 3.5));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(4.8, 4.4));

		Series->SetStyle(new CXTPChartScatterLineSeriesStyle());
		Series->SetArgumentScaleType(xtpChartScaleNumerical);

		pStyle = (CXTPChartScatterLineSeriesStyle*)Series->GetStyle();		
		pStyle->GetMarker()->SetType(xtpChartMarkerTriangle);
		
	}

	OnCheckShowLabels();
	OnCbnSelchangeComboMarkerSize();


	// Set the X and Y Axis title for the series.
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pCollection->GetAt(0)->GetDiagram());
	ASSERT (pDiagram);

	//pDiagram->GetAxisX()->SetInterlaced(FALSE);

}



void CScatterLineView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void CScatterLineView::OnCheckShowMarkers() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetVisible(m_bShowMarkers);
	}
}

void CScatterLineView::OnCbnSelchangeComboMarkerSize()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetSize(8 + 2 * m_nMarkerSize);
	}
}


void CScatterLineView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}