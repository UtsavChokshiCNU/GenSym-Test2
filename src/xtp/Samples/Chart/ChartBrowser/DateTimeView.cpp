// DateTimeView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "DateTimeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateTimeView

IMPLEMENT_DYNCREATE(CDateTimeView, CBaseView)

CDateTimeView::CDateTimeView()
	: CBaseView(CDateTimeView::IDD)
{
	//{{AFX_DATA_INIT(CDateTimeView)
	m_nMeasureUnits = 1;
	//}}AFX_DATA_INIT

	m_strCaption = _T("DateTime Scale");
}

CDateTimeView::~CDateTimeView()
{
} 

void CDateTimeView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDateTimeView)
	DDX_CBIndex(pDX, IDC_COMBO_MEASUREUNITS, m_nMeasureUnits);
	DDX_CBString(pDX, IDC_COMBO_LABEL_FORMAT, m_strLabelFormat);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Control(pDX, IDC_COMBO_LABEL_FORMAT, m_cmbLabelFormat);

}


BEGIN_MESSAGE_MAP(CDateTimeView, CBaseView)
	//{{AFX_MSG_MAP(CDateTimeView)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_MEASUREUNITS, OnMeasureUnitsChanged)

	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_FORMAT, OnLabelFormatIndexChanged)
	ON_CBN_EDITCHANGE(IDC_COMBO_LABEL_FORMAT, OnLabelFormatChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeView diagnostics

#ifdef _DEBUG
void CDateTimeView::AssertValid() const
{
	CBaseView::AssertValid();
}

void CDateTimeView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDateTimeView message handlers


void CDateTimeView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();


	CreateChart();
}

void CDateTimeView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetLegend()->SetVisible(FALSE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());


	CXTPChartSeries* pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetName(_T("Sales"));

	CXTPChartBarSeriesStyle* pStyle = new CXTPChartBarSeriesStyle();
	pSeries->SetStyle(pStyle);

	OnMeasureUnitsChanged();

	pStyle->GetLabel()->SetVisible(FALSE);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("Thousands of Dollars"));

	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);

	pDiagram->GetAxisX()->SetInterlaced(FALSE);
	pDiagram->GetAxisY()->GetGridLines()->SetMinorVisible(TRUE);

}

void CDateTimeView::AddDaySeries()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	pContent->GetTitles()->GetAt(0)->SetText(_T("Sales Volume by Day"));

	CXTPChartSeries* pSeries = pContent->GetSeries()->GetAt(0);

	pSeries->GetPoints()->RemoveAll();

	COleDateTime dt(2010, 1, 1, 0, 0, 0);
	COleDateTime dtLast(2010, 7, 7, 0, 0, 0);

	while (dt < dtLast)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(dt, rand() % 100));

		dt += COleDateTimeSpan(1, 0, 0, 0);
	}

	pSeries->SetArgumentScaleType(xtpChartScaleDateTime);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisX()->SetDateTimeScaleUnit(xtpChartScaleDay);
	pDiagram->GetAxisX()->GetLabel()->SetAngle(315);
	pDiagram->GetAxisX()->GetLabel()->SetAntialiasing(TRUE);


	m_cmbLabelFormat.ResetContent();

	m_cmbLabelFormat.AddString(_T("(Long Date)"));
	m_cmbLabelFormat.AddString(_T("(Short Date)"));
	m_cmbLabelFormat.AddString(_T("d MMM"));
	m_cmbLabelFormat.AddString(_T("d MMM, yyyy"));
	m_cmbLabelFormat.AddString(_T("MMMM, dd"));
	m_cmbLabelFormat.AddString(_T("MM/dd/yyyy"));

	m_strLabelFormat = _T("(Short Date)");
	UpdateData(FALSE);

}

void CDateTimeView::AddHourSeries()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	
	pContent->GetTitles()->GetAt(0)->SetText(_T("Sales Volume by Hour"));
	
	CXTPChartSeries* pSeries = pContent->GetSeries()->GetAt(0);
	
	pSeries->GetPoints()->RemoveAll();
	
	COleDateTime dt(2010, 1, 1, 0, 0, 0);
	COleDateTime dtLast(2010, 1, 3, 0, 0, 0);
	
	while (dt < dtLast)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(dt, (rand() % 100) / 24.0));
		
		dt += COleDateTimeSpan(0, 1, 0, 0);
	}
	
	pSeries->SetArgumentScaleType(xtpChartScaleDateTime);
	
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	
	pDiagram->GetAxisX()->SetDateTimeScaleUnit(xtpChartScaleHour);
	pDiagram->GetAxisX()->GetLabel()->SetAngle(0);
	pDiagram->GetAxisX()->GetLabel()->SetAntialiasing(FALSE);
	
	
	m_cmbLabelFormat.ResetContent();
	
	m_cmbLabelFormat.AddString(_T("(Long Time)"));
	m_cmbLabelFormat.AddString(_T("(Short Time)"));
	m_cmbLabelFormat.AddString(_T("HH:mm"));
	m_cmbLabelFormat.AddString(_T("ddd, HH:mm"));
	
	m_strLabelFormat = _T("(Short Time)");
	UpdateData(FALSE);

	OnLabelFormatChanged();
	
}

void CDateTimeView::AddMonthSeries()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	
	pContent->GetTitles()->GetAt(0)->SetText(_T("Sales Volume by Months"));
	
	CXTPChartSeries* pSeries = pContent->GetSeries()->GetAt(0);
	
	pSeries->GetPoints()->RemoveAll();
	
	COleDateTime dt(2010, 1, 1, 0, 0, 0);
	COleDateTime dtLast(2012, 7, 7, 0, 0, 0);
	
	while (dt < dtLast)
	{
		pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(dt, (rand() % 100)  * 30.0));
		
		dt += COleDateTimeSpan(31, 0, 0, 0);
	}
	
	pSeries->SetArgumentScaleType(xtpChartScaleDateTime);
	
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	
	pDiagram->GetAxisX()->SetDateTimeScaleUnit(xtpChartScaleMonth);
	pDiagram->GetAxisX()->GetLabel()->SetAngle(315);
	pDiagram->GetAxisX()->GetLabel()->SetAntialiasing(TRUE);
	
	
	m_cmbLabelFormat.ResetContent();
	
	m_cmbLabelFormat.AddString(_T("(Long Date)"));
	m_cmbLabelFormat.AddString(_T("(Short Date)"));
	m_cmbLabelFormat.AddString(_T("MMM"));
	m_cmbLabelFormat.AddString(_T("MMM, yyyy"));
	m_cmbLabelFormat.AddString(_T("MMMM, yyyy"));
	m_cmbLabelFormat.AddString(_T("MM/dd/yyyy"));

	
	m_strLabelFormat = _T("MMMM, yyyy");
	UpdateData(FALSE);
	
	OnLabelFormatChanged();
	
}

void CDateTimeView::AddYearSeries()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	
	pContent->GetTitles()->GetAt(0)->SetText(_T("Sales Volume by years"));
	
	CXTPChartSeries* pSeries = pContent->GetSeries()->GetAt(0);
	
	pSeries->GetPoints()->RemoveAll();

	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(COleDateTime(2008, 1, 1, 0, 0, 0), (rand() % 100)  * 30.0 * 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(COleDateTime(2009, 1, 1, 0, 0, 0), (rand() % 100)  * 30.0 * 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(COleDateTime(2010, 1, 1, 0, 0, 0), (rand() % 100)  * 30.0 * 12));
	pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(COleDateTime(2011, 1, 1, 0, 0, 0), (rand() % 100)  * 30.0 * 12));
	
	
	pSeries->SetArgumentScaleType(xtpChartScaleDateTime);
	
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	
	pDiagram->GetAxisX()->SetDateTimeScaleUnit(xtpChartScaleYear);
	pDiagram->GetAxisX()->GetLabel()->SetAngle(0);
	pDiagram->GetAxisX()->GetLabel()->SetAntialiasing(FALSE);
	
	
	m_cmbLabelFormat.ResetContent();
	
	m_cmbLabelFormat.AddString(_T("(Long Date)"));
	m_cmbLabelFormat.AddString(_T("(Short Date)"));
	m_cmbLabelFormat.AddString(_T("yyyy"));
	m_cmbLabelFormat.AddString(_T("yy"));
	
	
	m_strLabelFormat = _T("yyyy");
	UpdateData(FALSE);
	
	OnLabelFormatChanged();
	
}


void CDateTimeView::OnMeasureUnitsChanged() 
{
	UpdateData();

	if (m_nMeasureUnits == 1)
	{
		AddDaySeries();
	}
	if (m_nMeasureUnits == 0)
	{
		AddHourSeries();
	}
	if (m_nMeasureUnits == 2)
	{
		AddMonthSeries();
	}
	if (m_nMeasureUnits == 3)
	{
		AddYearSeries();
	}

}


void CDateTimeView::OnLabelFormatChanged()
{
	UpdateData();

	SetLabelFormat(m_strLabelFormat);

}

void CDateTimeView::SetLabelFormat(CString strLabelFormat)
{
	if (m_wndChartControl.GetSafeHwnd() == 0)
		return;

	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)m_wndChartControl.GetContent()->GetPrimaryDiagram();

	if (strLabelFormat == _T("(Long Time)"))
	{
		pDiagram->GetAxisX()->GetLabel()->GetFormat()->SetDateTimeCategory(xtpChartDateTimeLongTime);		
	}
	else if (strLabelFormat == _T("(Short Time)"))
	{
		pDiagram->GetAxisX()->GetLabel()->GetFormat()->SetDateTimeCategory(xtpChartDateTimeShortTime);		
	}
	else if (strLabelFormat == _T("(Long Date)"))
	{
		pDiagram->GetAxisX()->GetLabel()->GetFormat()->SetDateTimeCategory(xtpChartDateTimeLongDate);				
	}
	else if (strLabelFormat == _T("(Short Date)"))
	{
		pDiagram->GetAxisX()->GetLabel()->GetFormat()->SetDateTimeCategory(xtpChartDateTimeShortDate);				
	}
	else
	{
		pDiagram->GetAxisX()->GetLabel()->GetFormat()->SetDateTimeCategory(xtpChartDateTimeCustom);				
		pDiagram->GetAxisX()->GetLabel()->GetFormat()->SetDateTimeFormat(strLabelFormat);
	}

}

void CDateTimeView::OnLabelFormatIndexChanged()
{
	int nCurSel = m_cmbLabelFormat.GetCurSel();
	if (nCurSel != -1)
	{
		CString strText;
		m_cmbLabelFormat.GetLBText(nCurSel, strText);

		SetLabelFormat(strText);
	}
}
