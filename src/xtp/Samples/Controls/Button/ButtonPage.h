// ButtonDlg.h : header file
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

#if !defined(AFX_BUTTONDLG_H__7838AF65_FBA8_45D4_B811_4979E8FE9761__INCLUDED_)
#define AFX_BUTTONDLG_H__7838AF65_FBA8_45D4_B811_4979E8FE9761__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CButtonPage dialog

class CButtonPage : public CXTPResizePropertyPage
{
// Construction
public:
	CButtonPage();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CButtonPage)
	enum { IDD = IDD_PAGE_SIMPLEBUTTONS };
	int		m_nTheme;
	BOOL	m_bFlatStyle;
	BOOL	m_bUseVisualStyle;
	BOOL	m_bEnable;
	BOOL	m_bAlphaIcons;
	BOOL	m_bToggleButtons;
	BOOL	m_bShowFocus;
	int		m_nRelation;
	int		m_nPushButtonStyle;
	int		m_nImageAlignment;
	int		m_nTextAlignment;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CBitmap m_bitmap;
	CImageList m_imageList;

	CXTPButton m_btnRun;
	CXTPButton m_btnSettings;
	CXTPButton m_btnHelp;
	CXTPButton m_btnFind;

	CXTPButton m_btnState1;
	CXTPButton m_btnState2;

	CXTPButton m_btnOption1;
	CXTPButton m_btnOption2;


	CXTPButton m_frmRegular;
	CXTPButton m_frmTwoRows;
	CXTPButton m_frmCheckboxes;
	CXTPButton m_frmRadio;
	CXTPButton m_frmJustification;
	CXTPButton m_frmTheme;
	CXTPButton m_frmOptions;

	void UpdateIcons(BOOL bAlpha);

	// Generated message map functions
	//{{AFX_MSG(CButtonPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadTheme();
	afx_msg void OnCheckFlatstyle();
	afx_msg void OnCheckWinxpThemes();
	afx_msg void OnCheckEnabled();
	afx_msg void OnCheckAlpha();
	afx_msg void OnCheckToggle();
	afx_msg void OnCheckFocus();
	afx_msg void OnSelchangeComboRelation();
	afx_msg void OnSelchangeComboStyle();
	afx_msg void OnSelchangeComboImagealignment();
	afx_msg void OnSelchangeComboTextalignment();
	//}}AFX_MSG
	afx_msg void OnButtonClicked(UINT nID);
	afx_msg void OnButtonDropDown(UINT nID);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONDLG_H__7838AF65_FBA8_45D4_B811_4979E8FE9761__INCLUDED_)
