// StockSampleView.cpp : implementation of the CStockSampleView class
//
// --------------------------------------------------------------------------
// COPYRIGHT NOTICE:
// --------------------------------------------------------------------------
// 
// "Codejock Chart" is a MFC extension library for creating modern charting 
// applications. This file and the code herein are part of the Codejock Chart
// MFC extension library.
//
// This code is protected under U.S. Copyright Law and International treaties
// and is intended for registered and licensed use only. Any other use is 
// strictly prohibited. This code is subject to the terms and conditions 
// outlined in the "Codejock Chart" End User License Agreement (EULA).
//
// Copyright (c) 1998-2011 Codejock Technologies LLC, All Rights Reserved.
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"

#include "StockSample.h"

#include "StockSampleDoc.h"
#include "StockSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockSampleView

IMPLEMENT_DYNCREATE(CStockSampleView, CView)

BEGIN_MESSAGE_MAP(CStockSampleView, CView)
	//{{AFX_MSG_MAP(CStockSampleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_STOCKQUOTE, OnViewStockquote)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STOCKQUOTE, OnUpdateViewStockquote)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_VIEW_THICKSTYLE,OnViewThickstyle)
	ON_UPDATE_COMMAND_UI(ID_VIEW_THICKSTYLE, OnUpdateViewThickstyle)
	ON_COMMAND(ID_VIEW_CANDLES, OnViewCandles)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CANDLES, OnUpdateViewCandles)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockSampleView construction/destruction

CStockSampleView::CStockSampleView()
{
	m_bCandleStick = TRUE;
	m_bThickLine = FALSE;

}

CStockSampleView::~CStockSampleView()
{
}

BOOL CStockSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStockSampleView drawing

void CStockSampleView::OnDraw(CDC* pDC)
{
	CStockSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CStockSampleView diagnostics

#ifdef _DEBUG
void CStockSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CStockSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStockSampleDoc* CStockSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStockSampleDoc)));
	return (CStockSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStockSampleView message handlers

void AddDate(CXTPChartSeries* pSeries, LPCTSTR arg, double low, double high, double open, double close)
{
	CXTPChartSeriesPoint* pPoint;	
	pPoint = pSeries->GetPoints()->Add(new CXTPChartSeriesPoint(arg, low, high, open, close));	
}

void CStockSampleView::UpdateHistory(LPCTSTR lpszSymbol, BOOL bCandleStick, int nDays /*=90*/)
{
	m_wndChartControl.GetContent()->GetSeries()->RemoveAll();

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->Add(new CXTPChartSeries());
	pSeries->SetArgumentScaleType(xtpChartScaleDateTime);
	
	CTime timeEnd = CTime::GetCurrentTime();

	CTime timeStart = timeEnd;
	timeStart -= CTimeSpan(nDays,0,0,0);
	
	CYahooQuote	quote;
	CStringArray& arrQuote = quote.GetHistory(lpszSymbol, timeStart, timeEnd);

	
    CXTPChartHighLowSeriesStyle* pStyle = NULL;
    
    if (bCandleStick)
    {
        pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->SetStyle(new CXTPChartCandleStickSeriesStyle());
    }
    else
    {
        pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->SetStyle(new CXTPChartHighLowSeriesStyle());
    }
    
	pStyle->SetLineThickness(m_bThickLine ? 2 : 1);
	m_bCandleStick = bCandleStick;
	
	CXTPChartDiagram2D* pDiagram = (CXTPChartDiagram2D*)pSeries->GetDiagram();
	
	pDiagram->GetAxisY()->GetGridLines()->SetMinorVisible(TRUE);
	pDiagram->GetAxisY()->GetGridLines()->GetMinorLineStyle()->SetDashStyle(xtpChartDashStyleDot);
	
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("US Dollars"));
	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);

	pDiagram->GetAxisY()->GetRange()->SetShowZeroLevel(FALSE);
	
	pDiagram->GetAxisX()->GetLabel()->SetAngle(360-30);
	pDiagram->GetAxisX()->GetLabel()->SetAntialiasing(TRUE);


	pSeries->SetArgumentScaleType(xtpChartScaleQualitative);
	pDiagram->GetAxisX()->GetLabel()->SetVisible(TRUE);


	pDiagram->GetAxisX()->GetCustomLabels()->RemoveAll();

	for (int i = (int)arrQuote.GetSize() - 1; i > 0; --i)
	{
		AddDate(pSeries,
			quote.GetDate(arrQuote[i]),
			quote.GetLow(arrQuote[i]),
			quote.GetHigh(arrQuote[i]),
			quote.GetOpen(arrQuote[i]),
			quote.GetClose(arrQuote[i]));

		
		if ((i % 10) == 0)
		{
			CXTPChartAxisCustomLabel* pLabel = new CXTPChartAxisCustomLabel();
			pLabel->SetAxisValue(quote.GetDate(arrQuote[i]));
			pLabel->SetText(quote.GetDate(arrQuote[i]));
			pDiagram->GetAxisX()->GetCustomLabels()->Add(pLabel);
		}
	}
	


}

int CStockSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create the chart control.
	if (!m_wndChartControl.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0))
	{
		TRACE0("Error creating chart control.\n");
		return -1;
	}

	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_GRAY"));

	// set chart title.
	CXTPChartTitleCollection* pTitles = m_wndChartControl.GetContent()->GetTitles();
	CXTPChartTitle* pTitle = pTitles->Add(new CXTPChartTitle());
	pTitle->SetText(_T("Historical Stock Prices"));

	// set chart subtitle.
	CXTPChartTitle* pSubTitle = pTitles->Add(new CXTPChartTitle());
	pSubTitle->SetText(_T("www.codejock.com"));
	pSubTitle->SetDocking(xtpChartDockBottom);
	pSubTitle->SetAlignment(xtpChartAlignFar);
	pSubTitle->SetFont(CXTPChartFont::GetTahoma8());
	pSubTitle->SetTextColor(CXTPChartColor::Gray);

	// turn off legend.
	m_wndChartControl.GetContent()->GetLegend()->SetVisible(FALSE);

	// create stock quote dialog.
	if (m_dlgStockQuote.Create(IDD_STOCKQUOTE, this, m_pDocument))
	{
		// get the client area size.
		CRect rcClient;
		GetParentFrame()->GetClientRect(&rcClient);
		GetParentFrame()->ClientToScreen(&rcClient);
		
		CRect rcDialog;
		m_dlgStockQuote.GetWindowRect(&rcDialog);
		
		// offset client rect and determine dialog position.
		rcClient.OffsetRect(-20,-40);
		rcClient.left = rcClient.right - rcDialog.Width();
		rcClient.top = rcClient.bottom - rcDialog.Height();
		
		// quote dialog at new location.
		m_dlgStockQuote.MoveWindow(&rcClient, FALSE);
		m_dlgStockQuote.ShowWindow(SW_SHOW);
	}

	return 0;
}

void CStockSampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_wndChartControl.GetSafeHwnd())
	{
		m_wndChartControl.MoveWindow(0, 0, cx, cy);
	}
}

BOOL CStockSampleView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}

void CStockSampleView::OnSetFocus(CWnd* pOldWnd) 
{
	m_wndChartControl.SetFocus();
}

void CStockSampleView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (m_dlgStockQuote.m_hWnd == (HWND)lHint)
	{
		UpdateHistory(m_dlgStockQuote.m_strSymbol, (m_dlgStockQuote.m_nStyle == 0));
	}
}

void CStockSampleView::OnViewStockquote() 
{
	if (::IsWindow(m_dlgStockQuote.m_hWnd))
	{
		m_dlgStockQuote.ShowWindow(
			m_dlgStockQuote.IsWindowVisible() ? SW_HIDE : SW_SHOW);
	}
}

void CStockSampleView::OnUpdateViewStockquote(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_dlgStockQuote.IsWindowVisible());
}

void CStockSampleView::OnViewThickstyle()
{
	m_bThickLine = !m_bThickLine;

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);

	CXTPChartHighLowSeriesStyle* pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->GetStyle();

	pStyle->SetLineThickness(m_bThickLine ? 2 : 1);
}

void CStockSampleView::OnUpdateViewThickstyle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bThickLine ? 1 : 0);
}

void CStockSampleView::OnViewCandles()
{
	m_bCandleStick = !m_bCandleStick;	

	CXTPChartHighLowSeriesStyle* pStyle;

	CXTPChartSeries* pSeries = m_wndChartControl.GetContent()->GetSeries()->GetAt(0);
	
	if (m_bCandleStick)
		pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->SetStyle(new CXTPChartCandleStickSeriesStyle());
	else
		pStyle = (CXTPChartHighLowSeriesStyle*)pSeries->SetStyle(new CXTPChartHighLowSeriesStyle());

	pStyle->SetLineThickness(m_bThickLine ? 2 : 1);

	if (m_dlgStockQuote.GetSafeHwnd())
	{
		m_dlgStockQuote.m_nStyle = m_bCandleStick ? 0 : 1;
		m_dlgStockQuote.UpdateData(FALSE);
	}
}

void CStockSampleView::OnUpdateViewCandles(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bCandleStick ? 1 : 0);
}


/////////////////////////////////////////////////////////////////////////////
// CStockSampleView printing

void CStockSampleView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	//CXTPFlowGraphDrawContext dc(pDC->m_hDC, pDC->m_hAttribDC);
	//m_wndControl.OnDraw(&dc);
	
	m_wndChartControl.PrintToDC(pDC->m_hDC, pInfo->m_rectDraw);
}

BOOL CStockSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->m_nNumPreviewPages = 1;
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	
	
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStockSampleView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	
	if (!pInfo)
		return;
	
	pDC->SetMapMode(MM_ANISOTROPIC);
	
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),	pDC->GetDeviceCaps(LOGPIXELSY));
	
	pDC->SetWindowExt(96, 96);
	
	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(0, 0);
	
}


void CStockSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStockSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CStockSampleView::OnFilePrintPreview()
{
#ifdef __XTPPREVIEWVIEW_H__
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.
	
	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;
	
	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.
	
	if ( !DoPrintPreview( XTP_IDD_PREVIEW_DIALOGBAR, this,
		RUNTIME_CLASS( CXTPPreviewView ), pState ))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		TRACE0( "Error: DoPrintPreview failed.\n" );
		AfxMessageBox( AFX_IDP_COMMAND_FAILURE );
		delete pState;      // preview failed to initialize, delete State now
		
	}
#else
	CView::OnFilePrintPreview();
#endif
	
}
