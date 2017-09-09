// LineView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "LineView.h"


// CLineView

IMPLEMENT_DYNCREATE(CLineView, CBaseView)

CLineView::CLineView()
	: CBaseView(CLineView::IDD)
{
	m_strCaption = _T("Line Style");
	
	m_bShowLabels = TRUE;
	m_bShowMarkers = TRUE;

	m_nMarkerType = 0;
	m_nMarkerSize = 0;
}

CLineView::~CLineView()
{
}

void CLineView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_SHOWMARKERS, m_bShowMarkers);

	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_SIZE, m_nMarkerSize);

}

BEGIN_MESSAGE_MAP(CLineView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_SHOWMARKERS, OnCheckShowMarkers)

	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_SIZE, OnCbnSelchangeComboMarkerSize)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)
END_MESSAGE_MAP()


// CLineView diagnostics

#ifdef _DEBUG
void CLineView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CLineView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLineView message handlers


void CLineView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();

	CComboBox* pComboBoxSize = (CComboBox*)GetDlgItem(IDC_COMBO_MARKER_SIZE);
	for (int i = 8; i <= 30; i += 2)
	{
		CString strSize;
		strSize.Format(_T("%d"), i);

		pComboBoxSize->AddString(strSize);
	}
	pComboBoxSize->SetCurSel(0);

}


void CLineView::SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY)
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

void CLineView::CreateChart()
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

			pSeries1->SetStyle(new CXTPChartLineSeriesStyle());
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

			pSeries2->SetStyle(new CXTPChartLineSeriesStyle());
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

			pSeries3->SetStyle(new CXTPChartLineSeriesStyle());
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

			pSeries4->SetStyle(new CXTPChartLineSeriesStyle());
		}

		for (int i = 0; i < pCollection->GetCount(); i++)
		{
			CXTPChartSeriesLabel* pLabel = 
				pCollection->GetAt(i)->GetStyle()->GetLabel();

			pLabel->GetFormat()->SetCategory(xtpChartNumber);
			pLabel->GetFormat()->SetDecimalPlaces(0);
		}
	}


	// Set the X and Y Axis title for the series.
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pCollection->GetAt(0)->GetDiagram());
	ASSERT (pDiagram);

	SetAxisTitle(pDiagram, _T("Decade / Year"), _T("Population Growth (Thousands)"));

	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetDecimalPlaces(0);

}



void CLineView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void CLineView::OnCheckShowMarkers() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetVisible(m_bShowMarkers);
	}
}

void CLineView::OnCbnSelchangeComboMarkerSize()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetSize(8 + 2 * m_nMarkerSize);
	}
}


void CLineView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}