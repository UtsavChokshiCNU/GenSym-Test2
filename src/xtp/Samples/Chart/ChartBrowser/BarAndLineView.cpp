// BarAndLineView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "BarAndLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarAndLineView

IMPLEMENT_DYNCREATE(CBarAndLineView, CBaseView)

CBarAndLineView::CBarAndLineView()
	: CBaseView(CBarAndLineView::IDD)
{
	//{{AFX_DATA_INIT(CBarAndLineView)
	m_bShowLabels = TRUE;
	m_bRotated = FALSE;
	//}}AFX_DATA_INIT

	m_strCaption = _T("2D Bar and Line");
}

CBarAndLineView::~CBarAndLineView()
{
} 

void CBarAndLineView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBarAndLineView)
	//DDX_Control(pDX, IDC_COMBO_LABEL_POSITION, m_cboPosition);
	//DDX_Control(pDX, IDC_CHECK_SHOWLABELS, m_chkShowLabels);
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_ROTATED, m_bRotated);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

}


BEGIN_MESSAGE_MAP(CBarAndLineView, CBaseView)
	//{{AFX_MSG_MAP(CBarAndLineView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_ROTATED, OnBnClickedCheckRotated)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarAndLineView diagnostics

#ifdef _DEBUG
void CBarAndLineView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CBarAndLineView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBarAndLineView message handlers


void CBarAndLineView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();

	CreateChart();
}

void CBarAndLineView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Total Hours Worked"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Daily"));
	pSeries->SetStyle(new CXTPChartBarSeriesStyle());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("1 January"), 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("2 January"), 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("3 January"), 6));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("4 January"), 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("5 January"), 7));


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	
	pSeries->SetName(_T("Summary"));

	pSeries->SetStyle(new CXTPChartLineSeriesStyle());

	CXTPChartPointSeriesLabel* pLabel = DYNAMIC_DOWNCAST(CXTPChartPointSeriesLabel, pSeries->GetStyle()->GetLabel());

	pLabel->SetLineLength(20);
	pLabel->SetAngle(70);
	
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("1 January"), 8));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("2 January"), 8 + 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("3 January"), 8 + 7 + 6));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("4 January"), 8 + 7 + 6 + 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("5 January"), 8 + 7 + 6 + 7 + 7));

	

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Date"));

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Hours"));
}

void CBarAndLineView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartSeriesStyle* pStyle = pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}	
}

void CBarAndLineView::OnBnClickedCheckRotated()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeriesCollection->GetAt(0)->GetDiagram());

	pDiagram->SetRotated(m_bRotated);


}
