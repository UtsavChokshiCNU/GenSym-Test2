// BarView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "BarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarView

IMPLEMENT_DYNCREATE(CBarView, CBaseView)

CBarView::CBarView()
	: CBaseView(CBarView::IDD)
{
	//{{AFX_DATA_INIT(CBarView)
	m_nPosition = 0;
	m_bShowLabels = TRUE;
	m_bRotated = FALSE;
	//}}AFX_DATA_INIT

	m_strCaption = _T("Bar Style");
}

CBarView::~CBarView()
{
} 

void CBarView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBarView)
	//DDX_Control(pDX, IDC_COMBO_LABEL_POSITION, m_cboPosition);
	//DDX_Control(pDX, IDC_CHECK_SHOWLABELS, m_chkShowLabels);
	DDX_CBIndex(pDX, IDC_COMBO_LABEL_POSITION, m_nPosition);
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Check(pDX, IDC_CHECK_ROTATED, m_bRotated);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

}


BEGIN_MESSAGE_MAP(CBarView, CBaseView)
	//{{AFX_MSG_MAP(CBarView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_POSITION, OnCbnSelchangeComboLabelPosition)
	ON_BN_CLICKED(IDC_CHECK_ROTATED, OnBnClickedCheckRotated)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarView diagnostics

#ifdef _DEBUG
void CBarView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CBarView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBarView message handlers


void CBarView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}

void CBarView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Total Hours Worked"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());

	pSeries->SetName(_T("Quoted"));
	pSeries->SetStyle(new CXTPChartBarSeriesStyle());

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Sam"), 11));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Jesse"), 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Dave"), 4.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Max"), 6));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Brian"), 5));


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	
	pSeries->SetName(_T("Hourly"));
	pSeries->SetStyle(new CXTPChartBarSeriesStyle());
	
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Sam"), 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Jesse"), 9.5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Dave"), 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Max"), 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Brian"), 11));

	
	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	
	pSeries->SetName(_T("Unbillable"));
	pSeries->SetStyle(new CXTPChartBarSeriesStyle());
	
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Sam"), 7));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Jesse"), 2));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Dave"), 5));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Max"), 1));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Brian"), 4));


	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Employee"));

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Hours"));
}

void CBarView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}

	GetDlgItem(IDC_COMBO_LABEL_POSITION)->EnableWindow(m_bShowLabels);
	
}

void CBarView::OnCbnSelchangeComboLabelPosition()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		CXTPChartBarSeriesLabel* pLabel = (CXTPChartBarSeriesLabel*)pStyle->GetLabel();

		pLabel->SetPosition((XTPChartBarLabelPosition)m_nPosition);
	}
}

void CBarView::OnBnClickedCheckRotated()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeriesCollection->GetAt(0)->GetDiagram());

	pDiagram->SetRotated(m_bRotated);


}
