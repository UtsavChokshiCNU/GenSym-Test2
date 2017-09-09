// ChartDialogDlg.h : header file
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

#if !defined(AFX_CHARTDIALOGDLG_H__9F1720D3_90FC_46D0_A55A_F09BE1970E19__INCLUDED_)
#define AFX_CHARTDIALOGDLG_H__9F1720D3_90FC_46D0_A55A_F09BE1970E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChartDialogDlg dialog

class CChartDialogDlg : public CDialog
{
// Construction
public:
	CChartDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChartDialogDlg)
	enum { IDD = IDD_CHARTDIALOG_DIALOG };
	CComboBox	m_wndPalette;
	CComboBox	m_wndAppearance;
	int		m_nAppearance;
	int		m_nStyle;
	int		m_nPalette;
	BOOL	m_bLegend;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CXTPChartControl m_wndChartControl;

	void AddTitles();
	void AddSeries();

	// Generated message map functions
	//{{AFX_MSG(CChartDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeComboStyle();
	afx_msg void OnChangeComboAppearance();
	afx_msg void OnChangeComboPalette();
	afx_msg void OnCheckLegend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTDIALOGDLG_H__9F1720D3_90FC_46D0_A55A_F09BE1970E19__INCLUDED_)
