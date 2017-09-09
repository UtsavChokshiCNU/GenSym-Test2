// RealtimeLineView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "FastLineView.h"


static const int SeriesCount[] =
{
    1,
	2,
	3,
	4,
	5,
};

static const int Interval[] =
{
	1000,
	900,
	800,
	700,
	600,
	500,
	400,
	300,
	200,
	100
};


// CFastLineView

IMPLEMENT_DYNCREATE(CFastLineView, CBaseView)

CFastLineView::CFastLineView()
: CBaseView(CFastLineView::IDD)
{
	m_strCaption = _T("FastLine Style");
	
	m_nSeriesCount = 0;
	m_nInterval    = 9;
	
	m_nTimer = 0;
	
	m_dwTickCount = 0;

	m_bInterlaced = FALSE;
	m_bAntialiased = TRUE;
}

CFastLineView::~CFastLineView()
{
}

void CFastLineView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);

	DDX_Check(pDX, IDC_CHECK_INTERLACED, m_bInterlaced);
	DDX_Check(pDX, IDC_CHECK_ANTIALIASED, m_bAntialiased);
	
	DDX_CBIndex(pDX, IDC_COMBO_SERIES,   m_nSeriesCount);
	DDX_CBIndex(pDX, IDC_COMBO_INTERVAL, m_nInterval);
}

BEGIN_MESSAGE_MAP(CFastLineView, CBaseView)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIES,   OnCbnSelchangeComboSeriesCount)
	ON_CBN_SELCHANGE(IDC_COMBO_INTERVAL, OnCbnSelchangeComboInterval)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)

	ON_BN_CLICKED(IDC_CHECK_INTERLACED, OnInterlacedClick)
	ON_BN_CLICKED(IDC_CHECK_ANTIALIASED, OnAntialiasedClick)

	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CFastLineView diagnostics

#ifdef _DEBUG
void CFastLineView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CFastLineView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFastLineView message handlers


void CFastLineView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();
	
	int i;
	
	//////////////////////////////////////////////////////////////////////////
	
	CComboBox* pComboBoxSeries = (CComboBox*)GetDlgItem(IDC_COMBO_SERIES);
	for (i=0; i<sizeof(SeriesCount)/sizeof(SeriesCount[0]); i++)
	{
		CString strCount;
		strCount.Format(_T("%d"), SeriesCount[i]);
		
		pComboBoxSeries->AddString(strCount);
	}
	pComboBoxSeries->SetCurSel(m_nSeriesCount);
	
	
	//////////////////////////////////////////////////////////////////////////
	
	CComboBox* pComboBoxInterval = (CComboBox*)GetDlgItem(IDC_COMBO_INTERVAL);
	for (i=0; i<sizeof(Interval)/sizeof(Interval[0]); i++)
	{
		CString strInterval;
		strInterval.Format(_T("%d"), Interval[i]);
		
		pComboBoxInterval->AddString(strInterval);
	}
	pComboBoxInterval->SetCurSel(m_nInterval);
	
	//////////////////////////////////////////////////////////////////////////


	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	
	
	CXTPChartTitle* pSubTitle = m_wndChartControl.GetContent()->GetTitles()->Add(new CXTPChartTitle());
	pSubTitle->SetText(_T("Use mouse wheel to zoom chart"));
	pSubTitle->SetDocking(xtpChartDockBottom);
	pSubTitle->SetAlignment(xtpChartAlignFar);
	pSubTitle->SetFont(CXTPChartFont::GetTahoma8());
	pSubTitle->SetTextColor(CXTPChartColor::Gray);
	
	

	
	CreateChart();
	SetInterval();
}

void CFastLineView::OnDestroy()
{
	KillTimer(m_nTimer);
}

void CFastLineView::AddPoint()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	
	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();

	int nCount;
	
	if (pCollection)
	{
		for (int s = 0; s < pCollection->GetCount(); s++)
		{
			CXTPChartSeries* pSeries = pCollection->GetAt(s);
			if (pSeries)
			{
				int nValue = 50;

				nCount = pSeries->GetPoints()->GetCount();
				
				if (nCount)
					nValue = (int)pSeries->GetPoints()->GetAt(nCount - 1)->GetValue(0);
				
				nValue = nValue + (rand() % 20) - 10;
				
				if (nValue < 0) nValue = 0;
				if (nValue > 100) nValue = 100;
				
				pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(nCount, nValue));

			}
		}
	}

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, 
		m_wndChartControl.GetContent()->GetPanels()->GetAt(0));
	ASSERT (pDiagram);


	if (nCount > 100)
	{
		CXTPChartAxisRange* pRange = pDiagram->GetAxisX()->GetRange();

		BOOL bAutoScroll = pRange->GetViewMaxValue() == pRange->GetMaxValue();

		pRange->SetMaxValue(nCount);

		if (bAutoScroll)
		{
			double delta = pRange->GetViewMaxValue() - pRange->GetViewMinValue();

			pRange->SetViewAutoRange(FALSE);
			pRange->SetViewMaxValue(nCount);
			pRange->SetViewMinValue(nCount - delta);
		}

	}

}

void CFastLineView::OnTimer(UINT_PTR nIDEvent)
{
	DWORD dwTickCount = GetTickCount();
	
	m_dwTickCount = dwTickCount;
	
	AddPoint();
	
}



void CFastLineView::SetAxisTitle(CXTPChartDiagram2D* pDiagram, CString strAxisX, CString strAxisY)
{
	if (pDiagram)
	{
		CXTPChartAxis* pAxisX = pDiagram->GetAxisX();
		if (pAxisX)
		{
			CXTPChartAxisTitle* pTitle = pAxisX->GetTitle();
			if (pTitle)
			{
				pTitle->SetText(strAxisX);
				pTitle->SetVisible(TRUE);
			}
		}
		
		CXTPChartAxis* pAxisY = pDiagram->GetAxisY();
		if (pAxisY)
		{
			CXTPChartAxisTitle* pTitle = pAxisY->GetTitle();
			if (pTitle)
			{
				pTitle->SetText(strAxisY);
				pTitle->SetVisible(TRUE);
			}
		}
	}
}

void CFastLineView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();

	
	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();
	
	if (pCollection)
	{
		for (int s = 0; s < SeriesCount[m_nSeriesCount]; s++)
		{
			CXTPChartSeries* pSeries = pCollection->Add(new CXTPChartSeries());
			if (pSeries)
			{
				pSeries->SetName(_T("Series"));				
				
				CXTPChartFastLineSeriesStyle*pStyle = new CXTPChartFastLineSeriesStyle();
				pSeries->SetStyle(pStyle);

				pStyle->SetAntialiasing(m_bAntialiased);				
				
				pSeries->SetArgumentScaleType(xtpChartScaleNumerical);
			}
		}
	}
	
	// Set the X and Y Axis title for the series.
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pCollection->GetAt(0)->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->SetAllowZoom(TRUE);
	
	
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(100.1);
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->SetAllowZoom(FALSE);
	
	pDiagram->GetAxisX()->GetRange()->SetMaxValue(100.1);
	pDiagram->GetAxisX()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisX()->GetRange()->SetZoomLimit(10);
	
	pDiagram->GetAxisX()->SetInterlaced(FALSE);
	pDiagram->GetAxisY()->SetInterlaced(FALSE);	
	
	pDiagram->GetPane()->GetFillStyle()->SetFillMode(xtpChartFillSolid);

}




void CFastLineView::OnCbnSelchangeComboSeriesCount()
{
	UpdateData();
	CreateChart();
}


void CFastLineView::OnCbnSelchangeComboInterval()
{
	UpdateData();
	SetInterval();
}

void CFastLineView::SetInterval()
{
	if (0 != m_nTimer)
	{
		KillTimer(m_nTimer);
	}
	
	m_nTimer = (int)SetTimer(1, Interval[m_nInterval], NULL);
}

void CFastLineView::OnButtonAdd()
{
	for (int i = 0; i < 1000; i++)
		AddPoint();
	
}


void CFastLineView::OnInterlacedClick()
{
	UpdateData();

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, 
		m_wndChartControl.GetContent()->GetPanels()->GetAt(0));
	ASSERT (pDiagram);

	pDiagram->GetAxisY()->SetInterlaced(m_bInterlaced);

}

void CFastLineView::OnAntialiasedClick()
{
	UpdateData();

	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	
	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	

	if (pCollection)
	{
		for (int s = 0; s < pCollection->GetCount(); s++)
		{
			CXTPChartSeries* pSeries = pCollection->GetAt(s);
			if (pSeries)
			{
				CXTPChartFastLineSeriesStyle* pStyle = (CXTPChartFastLineSeriesStyle*)pSeries->GetStyle();
				pStyle->SetAntialiasing(m_bAntialiased);				
			}
		}
	}	
}
