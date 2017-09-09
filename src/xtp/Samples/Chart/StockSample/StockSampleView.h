// StockSampleView.h : interface of the CStockSampleView class
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

#if !defined(AFX_STOCKSAMPLEVIEW_H__E4BA6578_52B4_4E3C_8A42_893DE0BD5E23__INCLUDED_)
#define AFX_STOCKSAMPLEVIEW_H__E4BA6578_52B4_4E3C_8A42_893DE0BD5E23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStockSampleView : public CView
{
protected: // create from serialization only
	CStockSampleView();
	DECLARE_DYNCREATE(CStockSampleView)

// Attributes
public:
	CStockSampleDoc* GetDocument();

// Operations
public:
	void UpdateHistory(LPCTSTR lpszSymbol, BOOL bCandleStick, int nDays = 90);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockSampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStockSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	BOOL m_bCandleStick;
	BOOL m_bThickLine;

	CXTPChartControl m_wndChartControl;
	CStockQuoteDlg m_dlgStockQuote;

	void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	void OnFilePrintPreview();
	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CStockSampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewStockquote();
	afx_msg void OnUpdateViewStockquote(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewThickstyle();
	afx_msg void OnUpdateViewThickstyle(CCmdUI *pCmdUI);
	afx_msg void OnViewCandles();
	afx_msg void OnUpdateViewCandles(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in StockSampleView.cpp
inline CStockSampleDoc* CStockSampleView::GetDocument()
   { return (CStockSampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKSAMPLEVIEW_H__E4BA6578_52B4_4E3C_8A42_893DE0BD5E23__INCLUDED_)
