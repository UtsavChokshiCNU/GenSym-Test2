#if !defined(AFX_PAGEEDIT_H__BF497E7A_7D9A_4F20_A1EA_0DCF588EC931__INCLUDED_)
#define AFX_PAGEEDIT_H__BF497E7A_7D9A_4F20_A1EA_0DCF588EC931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageEdit dialog

class CPageEdit : public CXTPResizePropertyPage
{
// Construction
public:
	CPageEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageEdit)
	enum { IDD = IDD_PAGE_EDIT };
	CXTPButton	m_btnBuddy;
	CXTPSpinButtonCtrl	m_btnSpinButton;
	CXTPEdit	m_edtSpin;
	CXTPEdit	m_edtButton;
	CXTPEdit	m_edtPattern;
	CXTPEdit	m_edtMultiline;
	CXTPEdit	m_edtMasked;
	CXTPEdit	m_edtSingleLine;
	BOOL	m_bEnabled;
	BOOL	m_bPassword;
	BOOL	m_bReadOnly;
	BOOL	m_bUseVisualStyle;
	int		m_nTheme;
	BOOL	m_bFlatStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageEdit)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckEnabled();
	afx_msg void OnCheckReadonly();
	afx_msg void OnCheckPassword();
	afx_msg void OnRadTheme();
	afx_msg void OnCheckFlatstyle();
	afx_msg void OnCheckWinxpThemes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEEDIT_H__BF497E7A_7D9A_4F20_A1EA_0DCF588EC931__INCLUDED_)
