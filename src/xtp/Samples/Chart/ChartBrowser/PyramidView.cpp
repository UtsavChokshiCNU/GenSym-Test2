// PyramidView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "PyramidView.h"


// CPyramidView

IMPLEMENT_DYNCREATE(CPyramidView, CBaseView)

CPyramidView::CPyramidView(UINT nID)
	: CBaseView(nID)
{
	m_strCaption = _T("Pyramid Style");
	m_bShowLabels = TRUE;
	m_nPosition = 1;
	m_strPointDistance = _T("4");

	m_strHeightToWidth = _T("1");

}

CPyramidView::~CPyramidView()
{
}

void CPyramidView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_CBIndex(pDX, IDC_COMBO_LABEL_POSITION, m_nPosition);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_CBString(pDX, IDC_COMBO_POINTDISTANCE, m_strPointDistance);
	DDX_Control(pDX, IDC_COMBO_POINTDISTANCE, m_cboPointDistance);

	DDX_CBString(pDX, IDC_COMBO_HEIGHTTOWIDTH, m_strHeightToWidth);
	DDX_Control(pDX, IDC_COMBO_HEIGHTTOWIDTH, m_cboHeightToWidth);
}

BEGIN_MESSAGE_MAP(CPyramidView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnBnClickedCheckShowlabels)
	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_POSITION, OnCbnSelchangeComboLabelPosition)

	ON_CBN_EDITCHANGE(IDC_COMBO_POINTDISTANCE, OnEditChangePointDistance)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTDISTANCE, OnSelChangePointDistance)

	ON_CBN_EDITCHANGE(IDC_COMBO_HEIGHTTOWIDTH, OnEditChangeHeightToWidth)
	ON_CBN_SELCHANGE(IDC_COMBO_HEIGHTTOWIDTH, OnSelChangeHeightToWidth)

END_MESSAGE_MAP()


// CPyramidView diagnostics

#ifdef _DEBUG
void CPyramidView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CPyramidView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPyramidView message handlers


void CPyramidView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}


void CPyramidView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);
	pContent->GetLegend()->SetHorizontalAlignment(xtpChartLegendFar);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Corporate Actives"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Corporate Actives"));
	CXTPChartPyramidSeriesStyle* pStyle = new CXTPChartPyramidSeriesStyle();
	pSeries->SetStyle(pStyle);

	CXTPChartSeriesPoint* pPoint = NULL;
	CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();
	BOOL bPyramid = TRUE;

	pPoints->Add(new CXTPChartSeriesPoint(_T("Funds US $43K"), 43));
	pPoints->Add(new CXTPChartSeriesPoint(_T("Bonds US $100K"), 100));
	pPoints->Add(new CXTPChartSeriesPoint(_T("Stocks US $150K"), 150));
	pPoints->Add(new CXTPChartSeriesPoint(_T("Cash US $216K"), 216));

	pStyle->GetLabel()->SetFormat(_T("{A}"));
	pSeries->SetPointLegendFormat(_T("{A}"));
}

void CPyramidView::OnBnClickedCheckShowlabels()
{
	UpdateData();
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartSeriesStyle* pStyle = pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}

	GetDlgItem(IDC_COMBO_LABEL_POSITION)->EnableWindow(m_bShowLabels);
}

void CPyramidView::OnCbnSelchangeComboLabelPosition()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartPyramidSeriesStyle* pStyle = (CXTPChartPyramidSeriesStyle*)pSeriesCollection->GetAt(0)->GetStyle();

	CXTPChartPyramidSeriesLabel* pLabel = (CXTPChartPyramidSeriesLabel*)pStyle->GetLabel();

	pLabel->SetPosition((XTPChartPyramidLabelPosition)m_nPosition);

}

void CPyramidView::OnEditChangePointDistance()
{
	UpdateData();	

	int nPointDistance = _ttoi(m_strPointDistance);

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartPyramidSeriesStyle* pStyle = STATIC_DOWNCAST(CXTPChartPyramidSeriesStyle, pSeries->GetStyle());

	pStyle->SetPointDistance(nPointDistance);

}

void CPyramidView::OnSelChangePointDistance()
{
	UpdateData();	
	
	m_cboPointDistance.GetLBText(m_cboPointDistance.GetCurSel(), m_strPointDistance);
	
	int nPointDistance = _ttoi(m_strPointDistance);
	
	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	
	CXTPChartPyramidSeriesStyle* pStyle = STATIC_DOWNCAST(CXTPChartPyramidSeriesStyle, pSeries->GetStyle());
	
	pStyle->SetPointDistance(nPointDistance);
	
}


inline double StringToDouble(LPCTSTR lpszStr)
{
	USES_CONVERSION;
	return atof(T2A((LPTSTR)lpszStr));
}

void CPyramidView::OnEditChangeHeightToWidth()
{
	UpdateData();	
	
	double dHeightToWidth = StringToDouble(m_strHeightToWidth);
	
	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	
	CXTPChartPyramidSeriesStyle* pStyle = STATIC_DOWNCAST(CXTPChartPyramidSeriesStyle, pSeries->GetStyle());
	
	pStyle->SetHeightToWidthRatio(dHeightToWidth);
	
}

void CPyramidView::OnSelChangeHeightToWidth()
{
	UpdateData();	
	
	m_cboHeightToWidth.GetLBText(m_cboHeightToWidth.GetCurSel(), m_strHeightToWidth);
	
	double dHeightToWidth = StringToDouble(m_strHeightToWidth);
	
	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	
	CXTPChartPyramidSeriesStyle* pStyle = STATIC_DOWNCAST(CXTPChartPyramidSeriesStyle, pSeries->GetStyle());
	
	pStyle->SetHeightToWidthRatio(dHeightToWidth);
	
}