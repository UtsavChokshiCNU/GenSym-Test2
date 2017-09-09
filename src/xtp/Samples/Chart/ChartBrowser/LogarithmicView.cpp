// LogarithmicView.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "ChartBrowser.h"
#include "LogarithmicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogarithmicView

IMPLEMENT_DYNCREATE(CLogarithmicView, CBaseView)

CLogarithmicView::CLogarithmicView()
	: CBaseView(CLogarithmicView::IDD)
{
	//{{AFX_DATA_INIT(CLogarithmicView)
	//}}AFX_DATA_INIT

	m_strCaption = _T("Logarithmic Scale");
}

CLogarithmicView::~CLogarithmicView()
{
} 

void CLogarithmicView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogarithmicView)
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

}


BEGIN_MESSAGE_MAP(CLogarithmicView, CBaseView)
	//{{AFX_MSG_MAP(CLogarithmicView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogarithmicView diagnostics

#ifdef _DEBUG
void CLogarithmicView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CLogarithmicView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogarithmicView message handlers


void CLogarithmicView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}

CXTPChartSeriesStyle* CreateSeriesStyle()
{
	CXTPChartLineSeriesStyle* pStyle = new CXTPChartLineSeriesStyle();
	pStyle->GetMarker()->SetVisible(FALSE);
	pStyle->GetLabel()->SetVisible(FALSE);
	return pStyle;
}

void AddSeries(CXTPChartDiagram2D* pDiagram, BOOL LogY)
{
	CXTPChartContent* pContent = pDiagram->GetContent();

	CXTPChartSeries* pSeries;
	
	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetName(_T("f(x)=10^x"));

	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);
	pSeries->SetStyle(CreateSeriesStyle());

	pSeries->SetDiagram(pDiagram);
	pSeries->GetStyle()->SetColor(CXTPChartColor::Red);
	
	if (pDiagram != pContent->GetPrimaryDiagram())
		pSeries->SetLegendVisible(FALSE);

	double x;

	for (x = -2; x <= 11; x += 0.2)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(x, pow(10, x)));
	}
	

	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetName(_T("f(x)=x"));

	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);
	pSeries->SetStyle(CreateSeriesStyle());

	pSeries->SetDiagram(pDiagram);
	pSeries->GetStyle()->SetColor(CXTPChartColor::Green);

	if (pDiagram != pContent->GetPrimaryDiagram())
		pSeries->SetLegendVisible(FALSE);

	for (x = (LogY ? 0.01 : -1.0); x <= 11; x += 0.2)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(x, x));
	}


	pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetName(_T("f(x)=log(x)"));
	
	pSeries->SetArgumentScaleType(xtpChartScaleNumerical);
	pSeries->SetStyle(CreateSeriesStyle());
	
	pSeries->SetDiagram(pDiagram);
	pSeries->GetStyle()->SetColor(CXTPChartColor::Blue);
	
	if (pDiagram != pContent->GetPrimaryDiagram())
		pSeries->SetLegendVisible(FALSE);
	
	for (x = (LogY ? 1.01 : 0.2); x <= 11; x += 0.2)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(x, log(x)));
	}

}


void CLogarithmicView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(TRUE);


	CXTPChartDiagram2D* pDiagram = new CXTPChartDiagram2D();
	pContent->GetPanels()->Add(pDiagram);

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Linear"));

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Linear"));

	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetDecimalPlaces(1);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetUseThousandSeparator(TRUE);

	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetMinValue(-1);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(10);

	pDiagram->GetAxisX()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisX()->GetRange()->SetMinValue(-1);
	pDiagram->GetAxisX()->GetRange()->SetMaxValue(10);

	CXTPChartAxisConstantLine* pLine = pDiagram->GetAxisX()->GetConstantLines()->Add(new CXTPChartAxisConstantLine());
	pLine->SetAxisValue(.0);
	pLine->SetLegendVisible(FALSE);

	pLine = pDiagram->GetAxisY()->GetConstantLines()->Add(new CXTPChartAxisConstantLine());
	pLine->SetAxisValue(.0);
	pLine->SetLegendVisible(FALSE);

	AddSeries(pDiagram, FALSE);






	pDiagram = new CXTPChartDiagram2D();
	pContent->GetPanels()->Add(pDiagram);
	
	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("Linear"));
	
	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Log"));
	
	pDiagram->GetAxisY()->SetLogarithmic(TRUE);
	pDiagram->GetAxisY()->SetLogarithmicBase(10);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetDecimalPlaces(1);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetUseThousandSeparator(TRUE);
	
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetMinValue(0.1);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(1000);
	
	pDiagram->GetAxisX()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisX()->GetRange()->SetMinValue(-1);
	pDiagram->GetAxisX()->GetRange()->SetMaxValue(10);
	
	pLine = pDiagram->GetAxisX()->GetConstantLines()->Add(new CXTPChartAxisConstantLine());
	pLine->SetAxisValue(.0);
	pLine->SetLegendVisible(FALSE);
	
	
	AddSeries(pDiagram, TRUE);

}



void CLogarithmicView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	
	
	if (!m_wndChartControl.GetSafeHwnd())
		return;
	
	CXTPWindowRect rc(m_wndGroupBoxLabels);
	
	int nWidth = max(m_totalDev.cx, cx);
	int nHeight = max(m_totalDev.cy, cy);
	
	m_wndChartControl.SetWindowPos(0, 0, 0, nWidth - 2 * m_nLeftGap, nHeight - 2 * m_nLeftGap, SWP_NOMOVE | SWP_NOZORDER);
}