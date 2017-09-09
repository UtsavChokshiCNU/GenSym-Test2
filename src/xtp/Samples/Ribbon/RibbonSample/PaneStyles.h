#if !defined(AFX_PANESTYLES_H__12778969_E726_421D_A3ED_D6C977E48A7A__INCLUDED_)
#define AFX_PANESTYLES_H__12778969_E726_421D_A3ED_D6C977E48A7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneStyles.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CPaneStyles dialog

class CPaneStyles : public CXTPResizeDialog
{
// Construction
public:
	CPaneStyles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPaneStyles)
	enum { IDD = IDD_PANE_STYLES };
	CXTPListBox	m_lstStyles;
	CXTPButton	m_chkLinkedStyle;
	CXTPButton	m_chkPreview;
	CXTPButton	m_btnStyleInspector;
	CXTPButton	m_btnNewStyle;
	CXTPButton	m_btnManageStyles;
	//}}AFX_DATA

	CBrush m_brush;

	void RefreshMetrics(BOOL bOffice2007);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaneStyles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnOK();
	void OnCancel();

	// Generated message map functions
	//{{AFX_MSG(CPaneStyles)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANESTYLES_H__12778969_E726_421D_A3ED_D6C977E48A7A__INCLUDED_)
