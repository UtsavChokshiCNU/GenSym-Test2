#if !defined(AFX_EXCELTABPROPERTIES_H__F85EB7E8_88A6_4854_86CE_8F6AAF84DD4B__INCLUDED_)
#define AFX_EXCELTABPROPERTIES_H__F85EB7E8_88A6_4854_86CE_8F6AAF84DD4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExcelTabProperties.h : header file
//

class CExcelTabDlg;

/////////////////////////////////////////////////////////////////////////////
// CExcelTabProperties dialog

class CExcelTabProperties : public CDialog
{
// Construction
public:
	CExcelTabProperties(BOOL& bBottom, BOOL& bHasArrows, BOOL& bHasHomeEnd, BOOL& bHScroll, CExcelTabDlg* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExcelTabProperties)
	enum { IDD = IDD_EXCELTAB_PROPERTIES };
	CXTPColorPicker	m_cpSelText;
	CXTPColorPicker	m_cpText;
	CXTPColorPicker	m_cpSelBack;
	CXTPColorPicker	m_cpBack;
	CButton	m_btnModifyTab;
	CButton	m_btnDeleteTab;
	CButton	m_btnDeleteAll;
	CButton	m_btnAddTab;
	int		m_iTabNum;
	CString	m_csText;
	//}}AFX_DATA
	COLORREF m_crText;
	COLORREF m_crBack;
	COLORREF m_crSelText;
	COLORREF m_crSelBack;

	BOOL&	m_bBottom;
	BOOL&	m_bHasArrows;
	BOOL&	m_bHasHomeEnd;
	BOOL&	m_bHScroll;
	
	CExcelTabDlg* m_pParentWnd;
	CXTPExcelTabCtrl* m_pExcelTabCtrl;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelTabProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateDlgStatus();
	void UpdateTabColors();

	// Generated message map functions
	//{{AFX_MSG(CExcelTabProperties)
	afx_msg void OnFtsXtBottom();
	afx_msg void OnFtsXtHasarrows();
	afx_msg void OnFtsXtHashomeend();
	afx_msg void OnFtsXtHscroll();
	afx_msg void OnAddTab();
	afx_msg void OnDeleteAll();
	afx_msg void OnDeleteTab();
	afx_msg void OnModifyTab();
	afx_msg void OnChangeText();
	afx_msg void OnChangeTabNum();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnSelEndOkTextClr();
	afx_msg void OnSelEndOkBackClr();
	afx_msg void OnSelEndOkSelTextClr();
	afx_msg void OnSelEndOkSelBackClr();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTABPROPERTIES_H__F85EB7E8_88A6_4854_86CE_8F6AAF84DD4B__INCLUDED_)
