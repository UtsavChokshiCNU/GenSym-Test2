// MarkupTitleView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "MarkupTitleView.h"


// CMarkupTitleView

IMPLEMENT_DYNCREATE(CMarkupTitleView, CBaseView)

CMarkupTitleView::CMarkupTitleView()
	: CBaseView(CMarkupTitleView::IDD)
{
	m_strCaption = _T("Markup Titles");

	m_pTitle = NULL;

	m_nDock = -1;
	m_nAlignment = -1;
}

CMarkupTitleView::~CMarkupTitleView()
{
}

void CMarkupTitleView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
	
	DDX_CBIndex(pDX, IDC_COMBO_DOCK, m_nDock);
	DDX_CBIndex(pDX, IDC_COMBO_ALIGNMENT, m_nAlignment);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);

}

BEGIN_MESSAGE_MAP(CMarkupTitleView, CBaseView)
	ON_NOTIFY(NM_CLICK, IDC_CHARTCONTROL, OnChartClick)

	ON_CBN_SELCHANGE(IDC_COMBO_DOCK, OnCbnSelchangeComboDock)
	ON_CBN_SELCHANGE(IDC_COMBO_ALIGNMENT, OnCbnSelchangeComboAlignment)
	ON_EN_CHANGE(IDC_EDIT_TEXT, OnEditChangedText)

END_MESSAGE_MAP()


// CMarkupTitleView diagnostics

#ifdef _DEBUG
void CMarkupTitleView::AssertValid() const
{
	CBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CMarkupTitleView::Dump(CDumpContext& dc) const
{
	CBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMarkupTitleView message handlers


void CMarkupTitleView::OnInitialUpdate() 
{
	CBaseView::OnInitialUpdate();

	//SetResize(IDC_EDIT_TEXT,       XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);		

	CreateChart();

	SetTitle(0);
}


void CMarkupTitleView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	pContent->EnableMarkup();

	pContent->GetLegend()->SetVisible(FALSE);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("<TextBlock><Bold>Chart Control</Bold> <Run>supports</Run> <Run Foreground='Green'>Titles</Run> </TextBlock>"));


	pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Left Title"));
	pTitle->SetDocking(xtpChartDockLeft);

	pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("<TextBlock><Run Foreground='Blue'>Right</Run> <Run Foreground='Red'>Title</Run></TextBlock>"));
	pTitle->SetDocking(xtpChartDockRight);

	pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(_T("<TextBlock FontSize = '20px'>Click Title to set its propeties</TextBlock>"));
	pTitle->SetDocking(xtpChartDockBottom);

	CXTPChartSeriesCollection* pCollection = pContent->GetSeries();
	pCollection->RemoveAll();

	if (pCollection)
	{
		CXTPChartSeries* pSeries1 = pCollection->Add(new CXTPChartSeries());
		if (pSeries1)
		{
			pSeries1->SetName(_T("Serise"));

			CXTPChartSeriesPointCollection* pPoints = pSeries1->GetPoints();
			if (pPoints)
			{
				CXTPChartSeriesPoint* pPoint = NULL;

				for (int i = 0; i < 30; i++)
				{
					pPoint = pPoints->Add(new CXTPChartSeriesPoint(i, rand() % 30 + 30));
				}
			}

			pSeries1->SetStyle(new CXTPChartAreaSeriesStyle());

			pSeries1->GetStyle()->GetLabel()->SetVisible(FALSE);
		}

		CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pContent->GetPanels()->GetAt(0));

		pDiagram->GetAxisX()->GetLabel()->SetVisible(FALSE);
		pDiagram->GetAxisY()->GetLabel()->SetVisible(FALSE);

		pDiagram->GetAxisX()->GetRange()->SetSideMargins(FALSE);
	
	}
}

void CMarkupTitleView::SetTitle(CXTPChartTitle* pTitle)
{
	m_pTitle = pTitle;

	if (m_pTitle)
	{
		GetDlgItem(IDC_EDIT_TEXT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_ALIGNMENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DOCK)->EnableWindow(TRUE);

		m_nAlignment = m_pTitle->GetAlignment();
		m_nDock = m_pTitle->GetDocking();
		m_strText = m_pTitle->GetText();

		UpdateData(FALSE);
	
	}
	else
	{
		GetDlgItem(IDC_EDIT_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_ALIGNMENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOCK)->EnableWindow(FALSE);

	}
}


void CMarkupTitleView::OnChartClick(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
	CPoint pt;
	GetCursorPos(&pt);
	m_wndChartControl.ScreenToClient(&pt);

	CXTPChartElement* pElement = m_wndChartControl.HitTest(pt);

	if (DYNAMIC_DOWNCAST(CXTPChartTitle, pElement))
	{
		CXTPChartTitle* pTitle = (CXTPChartTitle*)pElement;

		SetTitle(pTitle);
	}	
	else
	{
		SetTitle(NULL);
	}
}

void CMarkupTitleView::OnCbnSelchangeComboDock()
{
	UpdateData();

	if (m_pTitle)
	{
		m_pTitle->SetDocking((XTPChartDocking)m_nDock);
	}

}

void CMarkupTitleView::OnCbnSelchangeComboAlignment()
{
	UpdateData();

	if (m_pTitle)
	{
		m_pTitle->SetAlignment((XTPChartStringAlignment )m_nAlignment);
	}

}

void CMarkupTitleView::OnEditChangedText()
{
	UpdateData();

	if (m_pTitle)
	{
		m_pTitle->SetText(m_strText);
	}
}