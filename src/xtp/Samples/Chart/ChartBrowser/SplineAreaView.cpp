// SplineAreaView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "SplineAreaView.h"


// CSplineAreaView dialog

IMPLEMENT_DYNCREATE(CSplineAreaView, CBaseView)

CSplineAreaView::CSplineAreaView()
	: CBaseView(CSplineAreaView::IDD)
{
	m_strCaption = _T("Spline Area Style");

	m_nTransparency = 1;
	m_nMarkerType = 0;
	m_bShowLabels = TRUE;
	m_nLabelAngle = 1;
}

CSplineAreaView::~CSplineAreaView()
{
}

void CSplineAreaView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	
	DDX_CBIndex(pDX, IDC_COMBO_LABEL_ANGLE, m_nLabelAngle);
	DDX_CBIndex(pDX, IDC_COMBO_TRANSPARENCY, m_nTransparency);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
}

BEGIN_MESSAGE_MAP(CSplineAreaView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)

	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_ANGLE, OnCbnSelchangeComboLabelAngle)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSPARENCY, OnCbnSelchangeComboTransparency)
END_MESSAGE_MAP()



void CSplineAreaView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}


void CSplineAreaView::SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY)
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

void CSplineAreaView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Population by U.S. State"));

	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	if (pCollection)
	{
		CXTPChartSeries* pSeries1 = pCollection->Add(new CXTPChartSeries());
		if (pSeries1)
		{
			pSeries1->SetName(_T("New York"));

			CXTPChartSeriesPointCollection* pPoints = pSeries1->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1900, 7268));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1950, 14830));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1990, 17990));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2000, 18976));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2008, 19490));
			}

			pSeries1->SetStyle(new CXTPChartSplineAreaSeriesStyle());
		}

		CXTPChartSeries* pSeries2 = pCollection->Add(new CXTPChartSeries());
		if (pSeries2)
		{
			pSeries2->SetName(_T("California"));

			CXTPChartSeriesPointCollection* pPoints = pSeries2->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1900, 1485));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1950, 10586));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1990, 29760));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2000, 33871));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2008, 36756));
			}

			pSeries2->SetStyle(new CXTPChartSplineAreaSeriesStyle());
		}

		CXTPChartSeries* pSeries3 = pCollection->Add(new CXTPChartSeries());
		if (pSeries3)
		{
			pSeries3->SetName(_T("Florida"));

			CXTPChartSeriesPointCollection* pPoints = pSeries3->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1900, 528));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1950, 2771));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1990, 12937));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2000, 15982));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2008, 18328));
			}

			pSeries3->SetStyle(new CXTPChartSplineAreaSeriesStyle());
		}

		CXTPChartSeries* pSeries4 = pCollection->Add(new CXTPChartSeries());
		if (pSeries4)
		{
			pSeries4->SetName(_T("Texas"));

			CXTPChartSeriesPointCollection* pPoints = pSeries4->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1900, 3048));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1950, 7711));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(1990, 16986));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2000, 20851));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2008, 24326));
			}

			pSeries4->SetStyle(new CXTPChartSplineAreaSeriesStyle());
		}
	}

	// Set the X and Y Axis title for the series.
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pCollection->GetAt(0)->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetRange()->SetSideMargins(FALSE);

	OnCbnSelchangeComboTransparency();

	SetAxisTitle(pDiagram, _T("Decade / Year"), _T("Population Growth (Thousands)"));

}


void CSplineAreaView::OnCbnSelchangeComboTransparency()
{
	UpdateData();
	
	int nTransparency = m_nTransparency * 45;
	if (nTransparency > 255) nTransparency = 255;
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartAreaSeriesStyle* pStyle = (CXTPChartAreaSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		pStyle->SetTransparency(nTransparency);
	}
	
}

void CSplineAreaView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}
void CSplineAreaView::OnCheckShowLabels() 
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
	
	GetDlgItem(IDC_COMBO_LABEL_ANGLE)->EnableWindow(m_bShowLabels);
}

void CSplineAreaView::OnCbnSelchangeComboLabelAngle()
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		CXTPChartPointSeriesLabel* pLabel = (CXTPChartPointSeriesLabel*)pStyle->GetLabel();
		
		pLabel->SetAngle(45 * m_nLabelAngle);
	}
	
}