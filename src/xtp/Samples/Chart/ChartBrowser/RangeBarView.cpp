// RangeBarView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "RangeBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRangeBarView

IMPLEMENT_DYNCREATE(CRangeBarView, CBaseView)

CRangeBarView::CRangeBarView()
	: CBaseView(CRangeBarView::IDD)
{
	//{{AFX_DATA_INIT(CRangeBarView)
	m_bShowLabels = FALSE;
	m_bRotated = FALSE;
	//}}AFX_DATA_INIT

	m_bSideBySide = FALSE;
	m_strCaption = _T("Range Bar Style");
}

CRangeBarView::~CRangeBarView()
{
} 

void CRangeBarView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRangeBarView)
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_ROTATED, m_bRotated);
	DDX_Check(pDX, IDC_CHECK_SIDEBYSIDE, m_bSideBySide);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

}


BEGIN_MESSAGE_MAP(CRangeBarView, CBaseView)
	//{{AFX_MSG_MAP(CRangeBarView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_SIDEBYSIDE, OnCheckSideBySide)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_ROTATED, OnBnClickedCheckRotated)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRangeBarView diagnostics

#ifdef _DEBUG
void CRangeBarView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CRangeBarView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRangeBarView message handlers


void CRangeBarView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();

	OnCheckShowLabels();
	OnCheckSideBySide();
}

void CRangeBarView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Total Hours Worked"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Odd Days"));

	CXTPChartRangeBarSeriesStyle* pStyle = new CXTPChartRangeBarSeriesStyle();
	pSeries->SetStyle(pStyle);
	pStyle->SetBarWidth(0.6);

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Sam"), 8, 14));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Jesse"), 9, 16));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Dave"), 7, 15));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Max"), 6, 15));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Brian"), 9, 17));


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	
	pSeries->SetName(_T("Even Days"));

	pStyle = new CXTPChartRangeBarSeriesStyle();
	pSeries->SetStyle(pStyle);
	pStyle->SetBarWidth(0.2);
	
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Sam"), 12, 23));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Jesse"), 14, 18));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Dave"), 12, 20));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Max"), 12, 23));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Brian"), 19, 23));

	




	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Employee"));

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Hours"));
}

void CRangeBarView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels && i == 1);
	}
	
}


void CRangeBarView::OnCheckSideBySide() 
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
		
		pStyle->SetSideBySide(m_bSideBySide);
	}
	
}

void CRangeBarView::OnBnClickedCheckRotated()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeriesCollection->GetAt(0)->GetDiagram());

	pDiagram->SetRotated(m_bRotated);


}
