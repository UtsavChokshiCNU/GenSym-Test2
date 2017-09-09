// StackedAreaView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "StackedAreaView.h"


// CStackedAreaView

IMPLEMENT_DYNCREATE(CStackedAreaView, CBaseView)

CStackedAreaView::CStackedAreaView()
	: CBaseView(CStackedAreaView::IDD)
{
	m_strCaption = _T("Stacked Area Style");

	m_nTransparency = 1;
	m_nMarkerType = 0;
	m_bShowLabels = TRUE;
	m_nLabelAngle = 1;
}

CStackedAreaView::~CStackedAreaView()
{
}

void CStackedAreaView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	
	DDX_CBIndex(pDX, IDC_COMBO_LABEL_ANGLE, m_nLabelAngle);
	DDX_CBIndex(pDX, IDC_COMBO_TRANSPARENCY, m_nTransparency);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
}

BEGIN_MESSAGE_MAP(CStackedAreaView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)

	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_ANGLE, OnCbnSelchangeComboLabelAngle)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSPARENCY, OnCbnSelchangeComboTransparency)
END_MESSAGE_MAP()


// CStackedAreaView diagnostics

#ifdef _DEBUG
void CStackedAreaView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CStackedAreaView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStackedAreaView message handlers


void CStackedAreaView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}


void CStackedAreaView::SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY)
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

void CStackedAreaView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Points Scored in the AFC East (FootBall)"));

	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	CXTPChartStackedAreaSeriesStyle* pStyle = new CXTPChartStackedAreaSeriesStyle();
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



void CStackedAreaView::OnCbnSelchangeComboTransparency()
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

void CStackedAreaView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}
void CStackedAreaView::OnCheckShowLabels() 
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

void CStackedAreaView::OnCbnSelchangeComboLabelAngle()
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
//////////////////////////////////////////////////////////////////////////
// CFullStackedAreaView

IMPLEMENT_DYNCREATE(CFullStackedAreaView, CStackedAreaView)

CFullStackedAreaView::CFullStackedAreaView()
{
	m_strCaption = _T("100% Stacked Area Style");
}

void CFullStackedAreaView::OnInitialUpdate()
{
	CStackedAreaView::OnInitialUpdate();

	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	for(int i = 0; i < pContent->GetSeries()->GetCount(); i++)
	{
		CXTPChartStackedAreaSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartStackedAreaSeriesStyle, 
			pContent->GetSeries()->GetAt(i)->GetStyle());
		ASSERT(pStyle);

		pStyle->SetStackHeight(100);
		
	}

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pContent->GetPanels()->GetAt(0));
	ASSERT(pDiagram);

	pDiagram->GetAxisY()->GetLabel()->SetFormat(_T("{V}%%"));

	pDiagram->GetAxisY()->GetRange()->SetSideMargins(FALSE);


}
