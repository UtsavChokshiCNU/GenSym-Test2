// RadarAreaView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "RadarAreaView.h"


// CRadarAreaView

IMPLEMENT_DYNCREATE(CRadarAreaView, CBaseView)

CRadarAreaView::CRadarAreaView()
	: CBaseView(CRadarAreaView::IDD)
{
	m_strCaption = _T("Radar Area Style");
	m_bShowLabels = TRUE;
	
	m_bShowAxisX = 1;
	m_bShowAxisY = 1;
	m_nMarkerType = 0;
	m_nMarkerSize = 0;

	m_bInterlaced = TRUE;
}

CRadarAreaView::~CRadarAreaView()
{
}

void CRadarAreaView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_AXISX, m_bShowAxisX);
	DDX_Check(pDX, IDC_CHECK_AXISY, m_bShowAxisY);
	DDX_Check(pDX, IDC_CHECK_INTERLACED, m_bInterlaced);

	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_SIZE, m_nMarkerSize);



}

BEGIN_MESSAGE_MAP(CRadarAreaView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)

	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_SIZE, OnCbnSelchangeComboMarkerSize)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)

	ON_BN_CLICKED(IDC_CHECK_AXISX, OnCheckShowAxisX)
	ON_BN_CLICKED(IDC_CHECK_AXISY, OnCheckShowAxisY)
	ON_BN_CLICKED(IDC_CHECK_INTERLACED, OnCheckInterlaced)

END_MESSAGE_MAP()


// CRadarAreaView diagnostics

#ifdef _DEBUG
void CRadarAreaView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CRadarAreaView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRadarAreaView message handlers

void CRadarAreaView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();

	int i;

	CComboBox* pComboBoxSize = (CComboBox*)GetDlgItem(IDC_COMBO_MARKER_SIZE);
	for (i = 8; i <= 30; i += 2)
	{
		CString strSize;
		strSize.Format(_T("%d"), i);

		pComboBoxSize->AddString(strSize);
	}
	pComboBoxSize->SetCurSel(0);
}

void CRadarAreaView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Radar Area Chart"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Area 1"));
	pSeries->SetStyle(new CXTPChartRadarAreaSeriesStyle());

	
	CXTPChartRadarDiagram* pDiagram = DYNAMIC_DOWNCAST(CXTPChartRadarDiagram, pSeries->GetDiagram());
	ASSERT (pDiagram);
	
	pDiagram->GetAxisX()->SetInterlaced(FALSE);
	pDiagram->GetAxisY()->SetInterlaced(m_bInterlaced);

#if 1
	pSeries->SetArgumentScaleType(xtpChartScaleDateTime);
	for (int nMonth = 1; nMonth <= 12; nMonth++)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(COleDateTime(2011, nMonth, 1, 0, 0, 0), 50 + (rand() % 50)));
	}

	pDiagram->GetAxisX()->GetLabel()->GetFormat()->SetDateTimeFormat(_T("MMMM"));
	pDiagram->GetAxisX()->GetLabel()->GetFormat()->SetDateTimeCategory(xtpChartDateTimeCustom);	
	pDiagram->GetAxisX()->SetDateTimeScaleUnit(xtpChartScaleMonth);

	pDiagram->GetAxisX()->SetGridSpacingAuto(FALSE);
	pDiagram->GetAxisX()->SetGridSpacing(1);
#else
	pSeries->SetArgumentScaleType(xtpChartScaleQualitative);

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("January"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("February"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("March"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("April"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("May"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("June"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("July"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Argust"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("September"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("October"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("November"), 50 + (rand() % 50)));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("December"), 50 + (rand() % 50)));


#endif

}

void CRadarAreaView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void CRadarAreaView::OnCheckShowAxisX() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisX()->SetVisible(m_bShowAxisX);
}

void CRadarAreaView::OnCheckShowAxisY() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisY()->SetVisible(m_bShowAxisY);
}

void CRadarAreaView::OnCheckInterlaced() 
{
	UpdateData();
	
	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();
	
	pDiagram->GetAxisY()->SetInterlaced(m_bInterlaced);
}





void CRadarAreaView::OnCbnSelchangeComboMarkerSize()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetSize(8 + 2 * m_nMarkerSize);

		// Solid Mode
		// pStyle->GetMarker()->GetFillStyle()->SetFillMode(xtpChartFillSolid);
	}
}


void CRadarAreaView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}