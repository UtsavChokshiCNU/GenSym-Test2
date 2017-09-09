// Pyramid3DView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "Pyramid3DView.h"


// CPyramid3DView

IMPLEMENT_DYNCREATE(CPyramid3DView, CBaseView)

CPyramid3DView::CPyramid3DView(UINT nID)
	: CBaseView(nID)
{
	m_strCaption = _T("Pyramid 3D Style");
	m_bShowLabels = TRUE;
	m_nPosition = 1;
	m_strPointDistance = _T("4");

	m_strTransparency = _T("235");

}

CPyramid3DView::~CPyramid3DView()
{
}

void CPyramid3DView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_CBIndex(pDX, IDC_COMBO_LABEL_POSITION, m_nPosition);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_CBString(pDX, IDC_COMBO_POINTDISTANCE, m_strPointDistance);
	DDX_Control(pDX, IDC_COMBO_POINTDISTANCE, m_cboPointDistance);

	DDX_CBString(pDX, IDC_COMBO_TRANSPARENCY, m_strTransparency);
	DDX_Control(pDX, IDC_COMBO_TRANSPARENCY, m_cboTransparency);
}

BEGIN_MESSAGE_MAP(CPyramid3DView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnBnClickedCheckShowlabels)
	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_POSITION, OnCbnSelchangeComboLabelPosition)

	ON_CBN_EDITCHANGE(IDC_COMBO_POINTDISTANCE, OnEditChangePointDistance)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTDISTANCE, OnSelChangePointDistance)

	ON_CBN_EDITCHANGE(IDC_COMBO_TRANSPARENCY, OnEditChangeTransparency)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSPARENCY, OnSelChangeTransparency)

END_MESSAGE_MAP()


// CPyramid3DView diagnostics

#ifdef _DEBUG
void CPyramid3DView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CPyramid3DView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPyramid3DView message handlers


void CPyramid3DView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}


void CPyramid3DView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);
	pContent->GetLegend()->SetHorizontalAlignment(xtpChartLegendFar);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Corporate Actives"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Corporate Actives"));
	CXTPChartPyramid3DSeriesStyle* pStyle = new CXTPChartPyramid3DSeriesStyle();
	pSeries->SetStyle(pStyle);

	CXTPChartSeriesPoint* pPoint = NULL;
	CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();
	BOOL bPyramid3D = TRUE;

	pPoints->Add(new CXTPChartSeriesPoint(_T("Funds US $43K"), 43));
	pPoints->Add(new CXTPChartSeriesPoint(_T("Bonds US $100K"), 100));
	pPoints->Add(new CXTPChartSeriesPoint(_T("Stocks US $150K"), 150));
	pPoints->Add(new CXTPChartSeriesPoint(_T("Cash US $216K"), 216));

	pStyle->GetLabel()->SetFormat(_T("{A}"));
	pSeries->SetPointLegendFormat(_T("{A}"));
}

void CPyramid3DView::OnBnClickedCheckShowlabels()
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

void CPyramid3DView::OnCbnSelchangeComboLabelPosition()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartPyramid3DSeriesStyle* pStyle = (CXTPChartPyramid3DSeriesStyle*)pSeriesCollection->GetAt(0)->GetStyle();

	CXTPChartPyramidSeriesLabel* pLabel = (CXTPChartPyramidSeriesLabel*)pStyle->GetLabel();

	pLabel->SetPosition((XTPChartPyramidLabelPosition)m_nPosition);

}

void CPyramid3DView::OnEditChangePointDistance()
{
	UpdateData();	

	int nPointDistance = _ttoi(m_strPointDistance);

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartPyramid3DSeriesStyle* pStyle = STATIC_DOWNCAST(CXTPChartPyramid3DSeriesStyle, pSeries->GetStyle());

	pStyle->SetPointDistance(nPointDistance);

}

void CPyramid3DView::OnSelChangePointDistance()
{
	UpdateData();	
	
	m_cboPointDistance.GetLBText(m_cboPointDistance.GetCurSel(), m_strPointDistance);
	
	int nPointDistance = _ttoi(m_strPointDistance);
	
	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	
	CXTPChartPyramid3DSeriesStyle* pStyle = STATIC_DOWNCAST(CXTPChartPyramid3DSeriesStyle, pSeries->GetStyle());
	
	pStyle->SetPointDistance(nPointDistance);
	
}


inline double StringToDouble(LPCTSTR lpszStr)
{
	USES_CONVERSION;
	return atof(T2A((LPTSTR)lpszStr));
}

void CPyramid3DView::OnEditChangeTransparency()
{
	UpdateData();	
	
	int nTransparency = _ttoi(m_strTransparency);
	
	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	
	CXTPChartPyramid3DSeriesStyle* pStyle = STATIC_DOWNCAST(CXTPChartPyramid3DSeriesStyle, pSeries->GetStyle());
	
	pStyle->SetTransparency(nTransparency);
	
}

void CPyramid3DView::OnSelChangeTransparency()
{
	UpdateData();	
	
	m_cboTransparency.GetLBText(m_cboTransparency.GetCurSel(), m_strTransparency);
	
	int nTransparency = _ttoi(m_strTransparency);
	
	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	
	CXTPChartPyramid3DSeriesStyle* pStyle = STATIC_DOWNCAST(CXTPChartPyramid3DSeriesStyle, pSeries->GetStyle());
	
	pStyle->SetTransparency(nTransparency);
	
}