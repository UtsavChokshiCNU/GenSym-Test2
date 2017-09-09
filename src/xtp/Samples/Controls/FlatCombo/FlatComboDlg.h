// FlatComboDlg.h : header file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLATCOMBODLG_H__03B48B0F_47BD_4632_B28B_BCE982A01581__INCLUDED_)
#define AFX_FLATCOMBODLG_H__03B48B0F_47BD_4632_B28B_BCE982A01581__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFlatComboDlg dialog

#include "FlatComboBox.h"
#include "afxwin.h"

class CFlatComboDlg : public CXTPResizeDialog
{
// Construction
public:
	CFlatComboDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
	//{{AFX_DATA(CFlatComboDlg)
	enum { IDD = IDD_FLATCOMBO_DIALOG };
	CXTPEdit m_wndFlatEdit;
	CButton m_gboxList;
	CButton m_gboxDown;
	CButton m_gboxAppear;
	CXTPColorPicker  m_cpText2;
	CXTPColorPicker  m_cpBack2;
	CXTPColorPicker  m_cpText1;
	CXTPColorPicker  m_cpBack1;
	CFlatComboBox   m_wndFlatCombo1;
	CFlatComboBox   m_wndFlatCombo2;

	BOOL m_bAutoComplete;
	BOOL m_bDisable1;
	BOOL m_bDisable2;
	BOOL m_bFlatBorders;
	int  m_nTheme;
	//}}AFX_DATA

	CString m_strStylesPath;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON    m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFlatComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDroplistDisable();
	afx_msg void OnDropdownDisable();
	afx_msg void OnDropdownAutocomp();
	afx_msg void OnSelEndOKDLTxtClr();
	afx_msg void OnSelEndOKDLBakClr();
	afx_msg void OnSelEndOKDDTxtClr();
	afx_msg void OnSelEndOKDDBakClr();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnThemeChanged();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChkFlatboarders();
	CComboBox m_wndComboColor;
	afx_msg void OnCbnSelendokComboColor();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATCOMBODLG_H__03B48B0F_47BD_4632_B28B_BCE982A01581__INCLUDED_)
