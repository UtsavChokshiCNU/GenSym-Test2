// SideBySideStackedBarView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "SideBySideStackedBarView.h"


// CSideBySideStackedBarView

IMPLEMENT_DYNCREATE(CSideBySideStackedBarView, CBaseView)

CSideBySideStackedBarView::CSideBySideStackedBarView()
	: CBaseView(CSideBySideStackedBarView::IDD)
{

	m_bShowLabels = FALSE;
	m_strCaption = _T("Side-by-Side Stacked Bar Style");
	m_bRotated = FALSE;

	m_nGroup = 1;
	m_b100 = FALSE;
}

CSideBySideStackedBarView::~CSideBySideStackedBarView()
{
}

void CSideBySideStackedBarView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	DDX_Check(pDX, IDC_CHECK_ROTATED, m_bRotated);
	DDX_Radio(pDX, IDC_RADIO_GROUP, m_nGroup);
	DDX_Check(pDX, IDC_CHECK_100, m_b100);
}

BEGIN_MESSAGE_MAP(CSideBySideStackedBarView, CBaseView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	ON_BN_CLICKED(IDC_CHECK_ROTATED, OnBnClickedCheckRotated)
	
	ON_BN_CLICKED(IDC_RADIO_GROUP, OnClickedGroup)
	ON_BN_CLICKED(IDC_RADIO_QUATER, OnClickedGroup)
	ON_BN_CLICKED(IDC_CHECK_100, OnCheck100)
END_MESSAGE_MAP()


// CSideBySideStackedBarView diagnostics

#ifdef _DEBUG
void CSideBySideStackedBarView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CSideBySideStackedBarView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSideBySideStackedBarView message handlers


void CSideBySideStackedBarView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();

	OnCheckShowLabels();
}

void CSideBySideStackedBarView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());

	for (int i = 0; i < 4; i++)
	{
		CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
		
		CString strName;
		strName.Format(_T("Q%d Project 1"), i + 1);

		pSeries->SetName(strName);

		CXTPChartStackedBarSeriesStyle* pStyle = new CXTPChartStackedBarSeriesStyle();			
		pSeries->SetStyle(pStyle);
		pStyle->SetStackGroup(i);
		
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("USA"), 8 + rand() % 20));
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Europe"),  12 + rand() % 20));
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Asia"),  7 + rand() % 20));

		pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
		
		strName;
		strName.Format(_T("Q%d Project 2"), i + 1);
		
		pSeries->SetName(strName);
		
		pStyle = new CXTPChartStackedBarSeriesStyle();
		pSeries->SetStyle(pStyle);
		pStyle->SetStackGroup(i);
		
		
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("USA"), 10 + rand() % 20));
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Europe"),  8 + rand() % 20));
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(_T("Asia"),  12 + rand() % 20));
	
	}

}

void CSideBySideStackedBarView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

//////////////////////////////////////////////////////////////////////////
// CFullSideBySideStackedBarView

IMPLEMENT_DYNCREATE(CFullSideBySideStackedBarView, CSideBySideStackedBarView)

CFullSideBySideStackedBarView::CFullSideBySideStackedBarView()
{
	m_strCaption = _T("Side-by-Side Stacked Bar Style");
}

void CFullSideBySideStackedBarView::OnInitialUpdate()
{
	CSideBySideStackedBarView::OnInitialUpdate();

	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	for(int i = 0; i < pContent->GetSeries()->GetCount(); i++)
	{
		CXTPChartStackedBarSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartStackedBarSeriesStyle, 
			 pContent->GetSeries()->GetAt(i)->GetStyle());
		ASSERT(pStyle);

		pStyle->SetStackHeight(100);
	}


}
void CSideBySideStackedBarView::OnBnClickedCheckRotated()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	CXTPChartDiagram2D* pDiagram = STATIC_DOWNCAST(CXTPChartDiagram2D, pSeriesCollection->GetAt(0)->GetDiagram());

	pDiagram->SetRotated(m_bRotated);
}

void CSideBySideStackedBarView::OnClickedGroup()
{
	UpdateData();

	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	if (m_nGroup == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			CXTPChartSeries* pSeries = pContent->GetSeries()->GetAt(i);
			
			CXTPChartStackedBarSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartStackedBarSeriesStyle, pSeries->GetStyle());
			ASSERT(pStyle);

			pStyle->SetStackGroup(i % 2);			
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			CXTPChartSeries* pSeries = pContent->GetSeries()->GetAt(i);
			
			CXTPChartStackedBarSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartStackedBarSeriesStyle, pSeries->GetStyle());
			ASSERT(pStyle);
			
			pStyle->SetStackGroup(i % 4);			
		}
	
	}
}


void CSideBySideStackedBarView::OnCheck100()
{
	UpdateData();
	
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	
	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartStackedBarSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChartStackedBarSeriesStyle, pSeriesCollection->GetAt(i)->GetStyle());
		ASSERT (pStyle);
		
		
		pStyle->SetStackHeight(m_b100 ? 100 : 0);
		
	}

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, m_wndChartControl.GetContent()->GetPanels()->GetAt(0));
	ASSERT (pDiagram);

	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetPattern(m_b100? _T("{V}%%") : _T("{V}"));
	pDiagram->GetAxisY()->GetRange()->SetSideMargins(!m_b100);
};
