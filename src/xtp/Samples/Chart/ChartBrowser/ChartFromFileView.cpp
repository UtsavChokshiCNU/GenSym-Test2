// ChartFromFileView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "ChartFromFileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartFromFileView

IMPLEMENT_DYNCREATE(CChartFromFileView, CBaseView)

CChartFromFileView::CChartFromFileView()
	: CBaseView(CChartFromFileView::IDD)
{
	//{{AFX_DATA_INIT(CChartFromFileView)
	m_bShowLabels = TRUE;
	//}}AFX_DATA_INIT

	m_strCaption = _T("Chart From Builder File");
}

CChartFromFileView::~CChartFromFileView()
{
} 

void CChartFromFileView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartFromFileView)
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
}


BEGIN_MESSAGE_MAP(CChartFromFileView, CBaseView)
	//{{AFX_MSG_MAP(CChartFromFileView)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartFromFileView diagnostics

#ifdef _DEBUG
void CChartFromFileView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CChartFromFileView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChartFromFileView message handlers


void CChartFromFileView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();

	CreateChart();
}

void CChartFromFileView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	LPCTSTR lpszResourceName = MAKEINTRESOURCE(IDR_BUILDERFILE);

	CXTPPropExchangeXMLNode px(TRUE, NULL, _T("Content"));

	if (px.LoadFromResource(AfxGetInstanceHandle(), lpszResourceName, RT_HTML))
	{
		pContent->DoPropExchange(&px);
	}
}

void CChartFromFileView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartSeriesStyle* pStyle = pSeriesCollection->GetAt(i)->GetStyle();

		pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}
