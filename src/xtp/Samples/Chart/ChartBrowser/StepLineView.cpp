// LineView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "StepLineView.h"


// CStepLineView

IMPLEMENT_DYNCREATE(CStepLineView, CBaseView)

CStepLineView::CStepLineView()
	: CBaseView(CStepLineView::IDD)
{
	m_strCaption = _T("Step Line Style");
	
	m_bShowLabels = TRUE;
	m_bShowMarkers = TRUE;

	m_nMarkerType = 1;
	m_nMarkerSize = 4;

	m_bInvertedStep = FALSE;
}

CStepLineView::~CStepLineView()
{
}

void CStepLineView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_SHOWMARKERS, m_bShowMarkers);
	DDX_Check(pDX, IDC_CHECK_INVERTEDSTEP, m_bInvertedStep);

	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_SIZE, m_nMarkerSize);

}

BEGIN_MESSAGE_MAP(CStepLineView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_SHOWMARKERS, OnCheckShowMarkers)
	ON_BN_CLICKED(IDC_CHECK_INVERTEDSTEP, OnCheckInvertedStep)

	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_SIZE, OnCbnSelchangeComboMarkerSize)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)
END_MESSAGE_MAP()


// CStepLineView diagnostics

#ifdef _DEBUG
void CStepLineView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CStepLineView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStepLineView message handlers


void CStepLineView::OnInitialUpdate() 
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
	pComboBoxSize->SetCurSel(m_nMarkerSize);

}


void CStepLineView::SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY)
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

void CStepLineView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("U.S. Fuel Oil Prices"));

	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	if (pCollection)
	{
		CXTPChartSeries* pSeries1 = pCollection->Add(new CXTPChartSeries());
		if (pSeries1)
		{
			pSeries1->SetName(_T("Prices"));

			CXTPChartSeriesPointCollection* pPoints = pSeries1->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("January, 2005"), 138.7));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("February, 2005"), 141.4));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("March, 2005"), 159.5));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("April, 2005"), 160.7));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("May, 2005"), 148.8));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("June, 2005"), 166.6));
			}

			CXTPChartStepLineSeriesStyle* pStyle = (CXTPChartStepLineSeriesStyle*)
				pSeries1->SetStyle(new CXTPChartStepLineSeriesStyle());
			pStyle->SetColorEach(TRUE);
			pStyle->GetMarker()->SetType(xtpChartMarkerSquare);
			pStyle->GetMarker()->SetSize(16);

			pStyle->GetLabel()->SetLineLength(20);
		}

	
	}

	// Set the X and Y Axis title for the series.
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pCollection->GetAt(0)->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisY()->SetInterlaced(TRUE);
	pDiagram->GetAxisX()->SetInterlaced(FALSE);

	pDiagram->GetAxisY()->GetRange()->SetShowZeroLevel(FALSE);

	pDiagram->GetAxisX()->GetLabel()->SetAngle(360-30);
	pDiagram->GetAxisX()->GetLabel()->SetAntialiasing(TRUE);

	SetAxisTitle(pDiagram, _T(""), _T("Cents per Gallon"));

}



void CStepLineView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void CStepLineView::OnCheckShowMarkers() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetVisible(m_bShowMarkers);
	}
}

void CStepLineView::OnCbnSelchangeComboMarkerSize()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetSize(8 + 2 * m_nMarkerSize);
	}
}


void CStepLineView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}

void CStepLineView::OnCheckInvertedStep()
{
	UpdateData();
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartStepLineSeriesStyle* pStyle = (CXTPChartStepLineSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->SetInvertedStep(m_bInvertedStep);
	}
}