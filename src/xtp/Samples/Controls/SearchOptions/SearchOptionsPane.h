// SearchOptionsPane.h : header file
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

#if !defined(AFX_SEARCHOPTIONSPANE_H__DCF380B3_6C33_4F6C_AC12_FD22771EEC76__INCLUDED_)
#define AFX_SEARCHOPTIONSPANE_H__DCF380B3_6C33_4F6C_AC12_FD22771EEC76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSearchOptionsPane form view

class CSearchOptionsPane : public CXTPSearchOptionsView
{
protected:
	CSearchOptionsPane();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSearchOptionsPane)

// Form Data
public:
	//{{AFX_DATA(CSearchOptionsPane)
	enum { IDD = IDD_FORMVIEW };
	CStatic m_txtSep;
	CXTPSearchOptionsCtrl    m_expKeywords;
	CXTPSearchOptionsCtrl    m_expFilters;
	CComboBox   m_combFavorites;
	CComboBox   m_combAtMost;
	CComboBox   m_combAtLeast;
	CButton m_chkAtMost;
	CButton m_chkAtLeast;
	CButton m_btnSearch;
	CButton m_btnSave;
	CButton m_btnDelete;
	CButton m_btnClear;
	//}}AFX_DATA

	bool m_bFirstTime;

	// draw text items flicker free.
	CXTPNoFlickerWnd <CStatic> m_txtButNot;
	CXTPNoFlickerWnd <CStatic> m_txtContaining;
	CXTPNoFlickerWnd <CStatic> m_icoSearch;
	CXTPNoFlickerWnd <CStatic> m_txtWords;
	CXTPNoFlickerWnd <CStatic> m_txtLetters;
	CXTPNoFlickerWnd <CStatic> m_txtHideWords;
	CXTPNoFlickerWnd <CStatic> m_txtHideLetters;
	CXTPNoFlickerWnd <CStatic> m_txtFavorites;
	CXTPNoFlickerWnd <CStatic> m_txtTitle;

	CXTPNoFlickerWnd <CEdit> m_editWords;
	CXTPNoFlickerWnd <CEdit> m_editLetters;
	CXTPNoFlickerWnd <CEdit> m_editContaining;
	CXTPNoFlickerWnd <CEdit> m_editButNot;
	CXTPNoFlickerWnd <CEdit> m_editAtMost;
	CXTPNoFlickerWnd <CEdit> m_editAtLeast;

// Attributes
protected:

	HICON      m_hIcon;
	CXTPCaption m_wndCaption;

	void InitFileFilters();
	void InitKeywordFilters();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchOptionsPane)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSearchOptionsPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSearchOptionsPane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnCaptionClose();

	afx_msg void OnFiltersContracting();
	afx_msg void OnFiltersContract();
	afx_msg void OnFiltersExpanding();
	afx_msg void OnFiltersExpand();
	afx_msg void OnKeywordContracting();
	afx_msg void OnKeywordContract();
	afx_msg void OnKeywordExpanding();
	afx_msg void OnKeywordExpand();

	DECLARE_MESSAGE_MAP()

	friend class CMainFrame;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHOPTIONSPANE_H__DCF380B3_6C33_4F6C_AC12_FD22771EEC76__INCLUDED_)
