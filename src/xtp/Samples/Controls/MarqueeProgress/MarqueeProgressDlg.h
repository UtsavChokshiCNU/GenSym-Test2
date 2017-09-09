// MarqueeProgressDlg.h : header file
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

#if !defined(AFX_MARQUEEPROGRESSDLG_H__1B6039D9_ECBB_4EAD_94C2_E2067EB02A68__INCLUDED_)
#define AFX_MARQUEEPROGRESSDLG_H__1B6039D9_ECBB_4EAD_94C2_E2067EB02A68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMarqueeProgressDlg dialog

class CMarqueeProgressDlg : public CDialog
{
// Construction
public:
	CMarqueeProgressDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMarqueeProgressDlg)
	enum { IDD = IDD_MARQUEEPROGRESS_DIALOG };
	CButton	m_staticTransparency;
	CButton	m_staticSettings;
	CStatic	m_staticInterval;
	CStatic	m_staticGap;
	CStatic	m_staticCX;
	CStatic	m_staticChunk5;
	CStatic	m_staticChunk4;
	CStatic	m_staticChunk3;
	CStatic	m_staticChunk2;
	CStatic	m_staticChunk1;
	CEdit	m_editInterval;
	CEdit	m_editGap;
	CEdit	m_editCX;
	CEdit	m_editChunk5;
	CEdit	m_editChunk4;
	CEdit	m_editChunk3;
	CEdit	m_editChunk2;
	CEdit	m_editChunk1;
	CSpinButtonCtrl	m_spinInterval;
	CSpinButtonCtrl	m_spinGap;
	CSpinButtonCtrl	m_spinCX;
	CSpinButtonCtrl	m_spinChunk5;
	CSpinButtonCtrl	m_spinChunk4;
	CSpinButtonCtrl	m_spinChunk3;
	CSpinButtonCtrl	m_spinChunk2;
	CSpinButtonCtrl	m_spinChunk1;
	CXTPMarqueeCtrl	m_wndProgVert;
	CXTPMarqueeCtrl	m_wndProgHorz;
	BOOL	m_bMarquee;
	int		m_nAlpha1;
	int		m_nAlpha2;
	int		m_nAlpha3;
	int		m_nAlpha4;
	int		m_nAlpha5;
	int		m_cxChunk;
	int		m_nGap;
	int		m_nInterval;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarqueeProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	void ValidateRange(CEdit& wndEdit, int nLower, int nUpper);
	void EnableWindows();

	// Generated message map functions
	//{{AFX_MSG(CMarqueeProgressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEditInterval();
	afx_msg void OnChangeEditGap();
	afx_msg void OnChangeEditCx();
	afx_msg void OnChangeEditChunk1();
	afx_msg void OnChangeEditChunk2();
	afx_msg void OnChangeEditChunk3();
	afx_msg void OnChangeEditChunk4();
	afx_msg void OnChangeEditChunk5();
	afx_msg void OnChkMarqueeStyle();
	afx_msg void OnBtnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARQUEEPROGRESSDLG_H__1B6039D9_ECBB_4EAD_94C2_E2067EB02A68__INCLUDED_)
