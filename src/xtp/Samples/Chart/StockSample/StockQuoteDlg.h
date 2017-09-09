// StockQuoteDlg.h : header file
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

#if !defined(AFX_STOCKQUOTEDLG_H__1D7C2A48_6FCE_40BE_AD59_D164C56C3773__INCLUDED_)
#define AFX_STOCKQUOTEDLG_H__1D7C2A48_6FCE_40BE_AD59_D164C56C3773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStockQuoteDlg dialog

class CStockQuoteDlg : public CDialog
{
// Construction
public:
	CStockQuoteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStockQuoteDlg)
	enum { IDD = IDD_STOCKQUOTE };
	CStatic	m_txtVolume;
	CStatic	m_txtTradeTime;
	CStatic	m_txtPrevClose;
	CStatic	m_txtOpen;
	CStatic	m_txtName;
	CStatic	m_txtMarketCap;
	CStatic	m_txtLastTrade;
	CStatic	m_txtDaysRange;
	CStatic	m_txtChange;
	CStatic	m_txtBid;
	CStatic	m_txtAvgVol;
	CStatic	m_txtAsk;
	CStatic	m_txt52WkRange;
	CStatic	m_txt1yTargetEst;
	CString	m_strSymbol;
	CString	m_str1yTargetEst;
	CString	m_str52WkRange;
	CString	m_strAsk;
	CString	m_strAvgVol;
	CString	m_strBid;
	CString	m_strChange;
	CString	m_strDaysRange;
	CString	m_strLastTrade;
	CString	m_strMarketCap;
	CString	m_strName;
	CString	m_strOpen;
	CString	m_strPrevClose;
	CString	m_strTradeTime;
	CString	m_strVolume;
	int		m_nStyle;
	//}}AFX_DATA

	CFont m_fontBold;
	CYahooQuote m_quote;
	COLORREF m_crRed;
	COLORREF m_crGreen;
	CDocument* m_pDoc;

	BOOL Create(UINT nIDTemplate, CWnd* pParentWnd, CDocument* pDoc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockQuoteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString FormatNumber(LONGLONG ulNumber);

	// Generated message map functions
	//{{AFX_MSG(CStockQuoteDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnGetQuote();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendOkComboStyle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKQUOTEDLG_H__1D7C2A48_6FCE_40BE_AD59_D164C56C3773__INCLUDED_)
