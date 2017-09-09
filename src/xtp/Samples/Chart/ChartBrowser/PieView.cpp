// PieView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "PieView.h"


// CPieView

IMPLEMENT_DYNCREATE(CPieView, CBaseView)

CPieView::CPieView(UINT nID)
	: CBaseView(nID)
{
	m_strCaption = _T("Pie Style");
	m_bShowLabels = TRUE;
	m_nPosition = 0;
	m_nExplodedPoints = 2;

}

CPieView::~CPieView()
{
}

void CPieView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_CBIndex(pDX, IDC_COMBO_LABEL_POSITION, m_nPosition);
	DDX_CBIndex(pDX, IDC_COMBO_EXPLODED_POINTS, m_nExplodedPoints);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
}

BEGIN_MESSAGE_MAP(CPieView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnBnClickedCheckShowlabels)
	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_POSITION, OnCbnSelchangeComboLabelPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPLODED_POINTS, OnCbnSelchangeComboExplodedPoints)
END_MESSAGE_MAP()


// CPieView diagnostics

#ifdef _DEBUG
void CPieView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CPieView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPieView message handlers


void CPieView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}

CXTPChartSeriesPoint* CreatPiePoint(LPCTSTR lpszLegendText, double nYear, double nValue, double dWidth, BOOL bPie)
{
	CXTPChartSeriesPoint* pPoint = new CXTPChartSeriesPoint(nYear, nValue, dWidth);
	pPoint->SetLegentText(lpszLegendText);
	return pPoint;
}

void CPieView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Top 10 States by Population"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Top 10 States by Population"));
	CXTPChartPieSeriesStyle* pStyle = new CXTPChartPieSeriesStyle();
	pSeries->SetStyle(pStyle);

	CXTPChartSeriesPoint* pPoint = NULL;
	CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();
	BOOL bPie = TRUE;

	pPoint = pPoints->Add(CreatPiePoint(_T("California"), 10, 37.623, 11.95, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreatPiePoint(_T("Texas"), 9, 25.532, 7.81, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("New York"), 8, 20.987, 6.31, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("Florida"), 7, 18.145, 5.97, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("Illinois"), 6, 13.320, 4.2, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreatPiePoint(_T("Pennsylvania"), 5, 12.875, 4.06, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("Ohio"), 4, 11.650, 3.75, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("Michigan"), 3, 10.340, 3.29, bPie));
	pPoint->m_bSpecial = TRUE;
	pPoint = pPoints->Add(CreatPiePoint(_T("Georgia"), 2, 9.964, 3.12, bPie));
	pPoint = pPoints->Add(CreatPiePoint(_T("North Carolina"), 1, 9.120, 3, bPie));

	pStyle->GetLabel()->SetFormat(_T("{V} Million"));
}

void CPieView::OnBnClickedCheckShowlabels()
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

void CPieView::OnCbnSelchangeComboLabelPosition()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartPieSeriesStyle* pStyle = (CXTPChartPieSeriesStyle*)pSeriesCollection->GetAt(0)->GetStyle();

	CXTPChartPieSeriesLabel* pLabel = (CXTPChartPieSeriesLabel*)pStyle->GetLabel();

	pLabel->SetPosition((XTPChartPieLabelPosition)m_nPosition);

}

void CPieView::OnCbnSelchangeComboExplodedPoints()
{
	UpdateData();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	int i;
	for (i = 0; i < pSeries->GetPoints()->GetCount(); i++)
	{
		CXTPChartSeriesPoint* pPoint = pSeries->GetPoints()->GetAt(i);

		pPoint->m_bSpecial = m_nExplodedPoints == 1;
	}

	if (m_nExplodedPoints == 2)
	{
		pSeries->GetPoints()->GetAt(0)->m_bSpecial = TRUE;
		pSeries->GetPoints()->GetAt(4)->m_bSpecial = TRUE;
		pSeries->GetPoints()->GetAt(7)->m_bSpecial = TRUE;

	}
	m_wndChartControl.OnChartChanged();
}
