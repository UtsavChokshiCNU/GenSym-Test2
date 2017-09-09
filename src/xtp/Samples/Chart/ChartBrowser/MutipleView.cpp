// MultipleView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "MultipleView.h"
#include "MainFrm.h"


// CMultipleView

IMPLEMENT_DYNCREATE(CMultipleView, CBaseView)

CMultipleView::CMultipleView()
	: CBaseView(CMultipleView::IDD)
{
	m_strCaption = _T("Single Content for Multiple Views");

	m_bShowLabels = TRUE;
	m_b3DStyle = TRUE;

	m_pContent = 0;
}

CMultipleView::~CMultipleView()
{
	SAFE_RELEASE(m_pContent);
}

void CMultipleView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_3DSTYLE, m_b3DStyle);

}

BEGIN_MESSAGE_MAP(CMultipleView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_3DSTYLE, OnCheck3DStyle)

	ON_NOTIFY(NM_CLICK, IDC_CHARTCONTROL, OnChartClick)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMultipleView diagnostics

#ifdef _DEBUG
void CMultipleView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CMultipleView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMultipleView message handlers


void CMultipleView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();

	CreateChart();

	m_wndControlRight.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 102);
	m_wndControlLeft.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 101);

	m_wndChartControl.SetUpdateWindow(TRUE);
	m_wndControlLeft.SetUpdateWindow(TRUE);
	m_wndControlRight.SetUpdateWindow(TRUE);
}


void CMultipleView::CreateChart()
{
	SAFE_RELEASE(m_pContent);
	m_pContent = new CXTPChartContent();

	m_pContent->GetLegend()->SetVisible(FALSE);

	if (m_b3DStyle)
	{
		CXTPChartSeries* pSeries = m_pContent->GetSeries()->Add(new CXTPChartSeries());

		CXTPChartPie3DSeriesStyle* pStyle = new CXTPChartPie3DSeriesStyle();
		pSeries->SetStyle(pStyle);

		CXTPChartSeriesPoint* pPoint = NULL;
		CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();

		pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("A"), 10));
		pPoint->m_bSpecial = TRUE;
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("B"), 20));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(_T("C"), 15));

		m_wndChartControl.SetContent(m_pContent);
		m_wndControlLeft.SetContent(m_pContent);
		m_wndControlRight.SetContent(m_pContent);
	}
	else
	{
		CXTPChartSeries* pSeries = m_pContent->GetSeries()->Add(new CXTPChartSeries());

		CXTPChartPointSeriesStyle* pStyle = new CXTPChartPointSeriesStyle();
		pSeries->SetStyle(pStyle);

		CXTPChartSeriesPoint* pPoint = NULL;
		CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();

		pPoint = pPoints->Add(new CXTPChartSeriesPoint(0, 10));
		pPoint->m_bSpecial = TRUE;
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(1, 20));
		pPoint = pPoints->Add(new CXTPChartSeriesPoint(2, 15));

		pSeries->SetArgumentScaleType(xtpChartScaleNumerical);

		CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
		pDiagram->SetAllowZoom(TRUE);

		

		m_wndChartControl.SetContent(m_pContent);
		m_wndControlLeft.SetContent(m_pContent);
		m_wndControlRight.SetContent(m_pContent);
	}
}


void CMultipleView::OnChartClick(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
	CPoint pt;
	GetCursorPos(&pt);
	m_wndChartControl.ScreenToClient(&pt);

	CXTPChartElement* pElement = m_wndChartControl.HitTest(pt);
	pElement;

}


void CMultipleView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (!m_wndGroupBoxLabels.GetSafeHwnd())
		return;

	CXTPWindowRect rc(m_wndGroupBoxLabels);

	int nWidth = max(m_totalDev.cx, cx);

	m_wndGroupBoxLabels.SetWindowPos(0, 0, 0, nWidth - 2 * m_nLeftGap, rc.Height(), SWP_NOMOVE | SWP_NOZORDER);


	CXTPWindowRect rcChart(m_wndChartControl);
	ScreenToClient(&rcChart);
	
	int nHeight = max(m_totalDev.cy, cy);

	CRect rcMainChart(rcChart.left, rcChart.top, rcChart.left + nWidth - 2 * m_nLeftGap, rcChart.top + nHeight * 2 / 3 - m_nTopGap);
	CRect rcLeftChart(rcMainChart.left, rcMainChart.bottom + m_nLeftGap, rcMainChart.left + nWidth / 2 - m_nLeftGap / 2, nHeight - m_nLeftGap);
	CRect rcRightChart(rcMainChart.left + nWidth / 2 + m_nLeftGap / 2, rcMainChart.bottom + m_nLeftGap, rcMainChart.right, nHeight - m_nLeftGap);

	m_wndChartControl.SetWindowPos(0, rcMainChart.left, rcMainChart.top, rcMainChart.Width(), rcMainChart.Height(), SWP_NOMOVE | SWP_NOZORDER);

	m_wndControlLeft.SetWindowPos(0, rcLeftChart.left, rcLeftChart.top, rcLeftChart.Width(), rcLeftChart.Height(), SWP_NOZORDER);

	m_wndControlRight.SetWindowPos(0, rcRightChart.left, rcRightChart.top, rcRightChart.Width(), rcRightChart.Height(), SWP_NOZORDER);
}

void CMultipleView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void CMultipleView::OnCheck3DStyle()
{
	m_wndChartControl.SetUpdateWindow(!TRUE);
	m_wndControlLeft.SetUpdateWindow(!TRUE);
	m_wndControlRight.SetUpdateWindow(!TRUE);

	UpdateData();
	CreateChart();

	((CMainFrame*)AfxGetMainWnd())->UpdateAppearance();
	((CMainFrame*)AfxGetMainWnd())->UpdatePalette();

	m_wndChartControl.SetUpdateWindow(TRUE);
	m_wndControlLeft.SetUpdateWindow(TRUE);
	m_wndControlRight.SetUpdateWindow(TRUE);
}
