// SecondaryAxesView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "SecondaryAxesView.h"


// CSecondaryAxesView

IMPLEMENT_DYNCREATE(CSecondaryAxesView, CBaseView)

CSecondaryAxesView::CSecondaryAxesView()
	: CBaseView(CSecondaryAxesView::IDD)
{
	m_strCaption = _T("Secondary Axes");
	
	m_bSecondaryAxisX = TRUE;
	m_bSecondaryAxisY = TRUE;

	m_bVisibleX = TRUE;
	m_bVisibleY = TRUE;
}

CSecondaryAxesView::~CSecondaryAxesView()
{
}

void CSecondaryAxesView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_AXISX, m_bSecondaryAxisX);
	DDX_Check(pDX, IDC_CHECK_AXISY, m_bSecondaryAxisY);

	DDX_Check(pDX, IDC_CHECK_VISIBLEX, m_bVisibleX);
	DDX_Check(pDX, IDC_CHECK_VISIBLEY, m_bVisibleY);

}

BEGIN_MESSAGE_MAP(CSecondaryAxesView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_AXISX, OnCheckSecondaryAxisX)
	ON_BN_CLICKED(IDC_CHECK_AXISY, OnCheckSecondaryAxisY)

	ON_BN_CLICKED(IDC_CHECK_VISIBLEX, OnCheckVisibleX)
	ON_BN_CLICKED(IDC_CHECK_VISIBLEY, OnCheckVisibleY)
END_MESSAGE_MAP()


// CSecondaryAxesView diagnostics

#ifdef _DEBUG
void CSecondaryAxesView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CSecondaryAxesView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSecondaryAxesView message handlers


void CSecondaryAxesView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}



void CSecondaryAxesView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	if (pCollection)
	{
		CXTPChartSeries* pSeries1 = pCollection->Add(new CXTPChartSeries());
		if (pSeries1)
		{
			pSeries1->SetName(_T("Series 1"));

			CXTPChartSeriesPointCollection* pPoints = pSeries1->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("A"), 1200));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("B"), 700));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("C"), 500));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("D"), 400));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("E"), 300));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("F"), 200));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("G"), 150));
			}

			CXTPChartLineSeriesStyle* pStyle = new CXTPChartLineSeriesStyle();
			pSeries1->SetStyle(pStyle);
			pStyle->GetMarker()->SetType(xtpChartMarkerTriangle);
			pStyle->GetMarker()->SetSize(16);
		}

		CXTPChartSeries* pSeries2 = pCollection->Add(new CXTPChartSeries());
		if (pSeries2)
		{
			pSeries2->SetName(_T("Series 2"));

			CXTPChartSeriesPointCollection* pPoints = pSeries2->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("A"), 50));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("B"), 40));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("C"), 30));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("D"), 20));
				pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("E"), 15));
			}

			CXTPChartLineSeriesStyle* pStyle = new CXTPChartLineSeriesStyle();
			pSeries2->SetStyle(pStyle);
			pStyle->GetMarker()->SetType(xtpChartMarkerStar);
			pStyle->GetMarker()->SetSize(16);
		}
	
	}

	OnCheckSecondaryAxisX();
	OnCheckSecondaryAxisY();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);

	
	pDiagram->GetSecondaryAxisY()->GetTitle()->SetText(_T("Series 2 (Secondary Axis Y)"));
	pDiagram->GetSecondaryAxisY()->GetTitle()->SetVisible(TRUE);

}



void CSecondaryAxesView::OnCheckSecondaryAxisX() 
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);

	if (!m_bSecondaryAxisX)
	{
		pDiagram->GetSecondaryAxisX()->SetVisible(FALSE);
	}
	else
	{
		OnCheckVisibleX();
	}

	if (m_bSecondaryAxisX)
	{
		pDiagram->GetSecondaryAxisX()->GetTitle()->SetText(_T("Series 2 (Secondary Axis X)"));
		pDiagram->GetSecondaryAxisX()->GetTitle()->SetVisible(TRUE);

		pDiagram->GetAxisX()->GetTitle()->SetText(_T("Series 1 (Primary Axis X)"));
		pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	}
	else
	{
		pDiagram->GetAxisX()->GetTitle()->SetText(_T("Series 1, Series2 (Primary Axis X)"));
		pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	}

	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)m_wndChartControl.GetContent()->GetSeries()->GetAt(1)->GetStyle();
		pStyle->SetSecondaryAxisX(m_bSecondaryAxisX);
	}

	GetDlgItem(IDC_CHECK_VISIBLEX)->EnableWindow(m_bSecondaryAxisX);
}

void CSecondaryAxesView::OnCheckSecondaryAxisY() 
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);
	
	if (!m_bSecondaryAxisY)
	{
		pDiagram->GetSecondaryAxisY()->SetVisible(FALSE);
	}
	else
	{
		OnCheckVisibleY();
	}


	if (m_bSecondaryAxisY)
	{
		pDiagram->GetSecondaryAxisY()->GetTitle()->SetText(_T("Series 2 (Secondary Axis Y)"));
		pDiagram->GetSecondaryAxisY()->GetTitle()->SetVisible(TRUE);
		
		pDiagram->GetAxisY()->GetTitle()->SetText(_T("Series 1 (Primary Axis X)"));
		pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	}
	else
	{
		pDiagram->GetAxisY()->GetTitle()->SetText(_T("Series 1, Series2 (Primary Axis Y)"));
		pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
		
	}

	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)m_wndChartControl.GetContent()->GetSeries()->GetAt(1)->GetStyle();
		pStyle->SetSecondaryAxisY(m_bSecondaryAxisY);
	}

	GetDlgItem(IDC_CHECK_VISIBLEY)->EnableWindow(m_bSecondaryAxisY);
}

void CSecondaryAxesView::OnCheckVisibleX()
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);
	
	pDiagram->GetSecondaryAxisX()->SetVisible(m_bVisibleX);

}


void CSecondaryAxesView::OnCheckVisibleY()
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPanels()->GetAt(0);
	
	pDiagram->GetSecondaryAxisY()->SetVisible(m_bVisibleY);

}