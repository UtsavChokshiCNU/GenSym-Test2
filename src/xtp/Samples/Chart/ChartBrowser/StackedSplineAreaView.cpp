// StackedSplineAreaView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "StackedSplineAreaView.h"


// CStackedSplineAreaView

IMPLEMENT_DYNCREATE(CStackedSplineAreaView, CBaseView)

CStackedSplineAreaView::CStackedSplineAreaView()
	: CBaseView(CStackedSplineAreaView::IDD)
{
	m_strCaption = _T("Stacked Area Style");

	m_nTransparency = 1;
	m_nMarkerType = 0;
	m_bShowLabels = TRUE;
	m_nLabelAngle = 1;
	m_b100 = FALSE;
}

CStackedSplineAreaView::~CStackedSplineAreaView()
{
}

void CStackedSplineAreaView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	
	DDX_CBIndex(pDX, IDC_COMBO_LABEL_ANGLE, m_nLabelAngle);
	DDX_CBIndex(pDX, IDC_COMBO_TRANSPARENCY, m_nTransparency);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
}

BEGIN_MESSAGE_MAP(CStackedSplineAreaView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)

	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_ANGLE, OnCbnSelchangeComboLabelAngle)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSPARENCY, OnCbnSelchangeComboTransparency)
END_MESSAGE_MAP()


// CStackedSplineAreaView diagnostics

#ifdef _DEBUG
void CStackedSplineAreaView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CStackedSplineAreaView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStackedSplineAreaView message handlers


void CStackedSplineAreaView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}


void CStackedSplineAreaView::SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY)
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

void CStackedSplineAreaView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Points Scored in the AFC East (FootBall)"));

	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	CXTPChartStackedSplineAreaSeriesStyle* pStyle = new CXTPChartStackedSplineAreaSeriesStyle();
	pStyle->SetTransparency(165);

	if (pCollection)
	{
		CXTPChartSeries* pSeries1 = pCollection->Add(new CXTPChartSeries());
		if (pSeries1)
		{
			pSeries1->SetName(_T("New England"));

			CXTPChartSeriesPointCollection* pPoints = pSeries1->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2005, 379));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2006, 385));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2007, 589));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2008, 410));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2009, 427));
			}

			pSeries1->SetStyle(pStyle);
			pStyle->InternalAddRef();
		}

		CXTPChartSeries* pSeries2 = pCollection->Add(new CXTPChartSeries());
		if (pSeries2)
		{
			pSeries2->SetName(_T("Minnesota"));

			CXTPChartSeriesPointCollection* pPoints = pSeries2->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2005, 306));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2006, 282));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2007, 365));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2008, 379));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2009, 470));
			}

			pSeries2->SetStyle(pStyle);
			pStyle->InternalAddRef();
		}

		CXTPChartSeries* pSeries3 = pCollection->Add(new CXTPChartSeries());
		if (pSeries3)
		{
			pSeries3->SetName(_T("New York"));

			CXTPChartSeriesPointCollection* pPoints = pSeries3->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2005, 240));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2006, 316));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2007, 268));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2008, 405));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2009, 348));
			}

			pSeries3->SetStyle(pStyle);
			pStyle->InternalAddRef();
		}

		CXTPChartSeries* pSeries4 = pCollection->Add(new CXTPChartSeries());
		if (pSeries4)
		{
			pSeries4->SetName(_T("Miami"));

			CXTPChartSeriesPointCollection* pPoints = pSeries4->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2005, 318));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2006, 260));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2007, 267));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2008, 345));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(2009, 360));
			}

			pSeries4->SetStyle(pStyle);
			pStyle->InternalAddRef();
		}
	}

	pStyle->InternalRelease();

	// Set the X and Y Axis title for the series.
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pCollection->GetAt(0)->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetRange()->SetSideMargins(FALSE);

	OnCbnSelchangeComboTransparency();

	SetAxisTitle(pDiagram, _T("Season"), _T("Number of Points Scored"));
}



void CStackedSplineAreaView::OnCbnSelchangeComboTransparency()
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

void CStackedSplineAreaView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}
void CStackedSplineAreaView::OnCheckShowLabels() 
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

void CStackedSplineAreaView::OnCbnSelchangeComboLabelAngle()
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

void CStackedSplineAreaView::OnCheck100()
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartStackedSplineAreaSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartStackedSplineAreaSeriesStyle, pSeriesCollection->GetAt(i)->GetStyle());
		ASSERT (pStyle);
	
		
		pStyle->SetStackHeight(m_b100 ? 100 : 0);
	}

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, m_wndChartControl.GetContent()->GetPanels()->GetAt(0));
	ASSERT (pDiagram);
	
	pDiagram->GetAxisY()->GetLabel()->SetFormat(m_b100? _T("{V}%%") : _T("{V}"));

	
	pDiagram->GetAxisY()->GetRange()->SetSideMargins(!m_b100);

};

//////////////////////////////////////////////////////////////////////////
// CFullStackedSplineAreaView

IMPLEMENT_DYNCREATE(CFullStackedSplineAreaView, CStackedSplineAreaView)

CFullStackedSplineAreaView::CFullStackedSplineAreaView()
{
	m_strCaption = _T("100% Stacked Spline Area Style");
	m_b100 = TRUE;
}

void CFullStackedSplineAreaView::OnInitialUpdate()
{
	CStackedSplineAreaView::OnInitialUpdate();
	
	OnCheck100();
	
}
