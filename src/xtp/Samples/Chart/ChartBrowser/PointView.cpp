// PointView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "PointView.h"


// CPointView

IMPLEMENT_DYNCREATE(CPointView, CBaseView)

CPointView::CPointView()
	: CBaseView(CPointView::IDD)
{
	m_strCaption = _T("Scatter Point Style");
	m_bShowLabels = TRUE;
	
	m_nLabelAngle = 1;
	m_nMarkerType = 0;
	m_nMarkerSize = 0;
}

CPointView::~CPointView()
{
}

void CPointView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);

	DDX_CBIndex(pDX, IDC_COMBO_LABEL_ANGLE, m_nLabelAngle);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
	DDX_CBIndex(pDX, IDC_COMBO_MARKER_SIZE, m_nMarkerSize);



}

BEGIN_MESSAGE_MAP(CPointView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)

	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_ANGLE, OnCbnSelchangeComboLabelAngle)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_SIZE, OnCbnSelchangeComboMarkerSize)
	ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)

END_MESSAGE_MAP()


// CPointView diagnostics

#ifdef _DEBUG
void CPointView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CPointView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPointView message handlers

void CPointView::OnInitialUpdate() 
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

void CPointView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Scatter Point Chart"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);

	pSeries->SetName(_T("Points 1"));
	pSeries->SetStyle(new CXTPChartPointSeriesStyle());

	int i;
	for (i = 0; i < 20; i++)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(rand() % 40, 50 + (rand() % 50)));
	}

	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);

	pSeries->SetName(_T("Points 2"));
	pSeries->SetStyle(new CXTPChartPointSeriesStyle());

	for (i = 0; i < 20; i++)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(40 + (rand() % 40), rand() % 50));
	}

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	
}

void CPointView::OnCheckShowLabels() 
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

void CPointView::OnCbnSelchangeComboLabelAngle()
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

void CPointView::OnCbnSelchangeComboMarkerSize()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetSize(8 + 2 * m_nMarkerSize);

		// Solid Mode
		// pStyle->GetMarker()->GetFillStyle()->SetFillMode(xtpChartFillSolid);
	}
}


void CPointView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}