#if !defined(AFX_DIALOGACTIONS_H__2E0EB4F9_8AA3_4CE2_B48F_CCA5EFE08E78__INCLUDED_)
#define AFX_DIALOGACTIONS_H__2E0EB4F9_8AA3_4CE2_B48F_CCA5EFE08E78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogActions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogActions dialog

class CDialogActions : public CDialog
{
// Construction
public:
	void FillActionsCombos();
	CDialogActions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogActions)
	enum { IDD = IDD_DIALOG_ACTIONS };
	CComboBox	m_lstActions;
	BOOL	m_bChecked;
	BOOL	m_bEnabled;
	BOOL	m_bVisible;
	CString	m_strCaption;
	CString	m_strDescription;
	CString	m_strTooltip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogActions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CXTPControlActions* m_pActions;

	// Generated message map functions
	//{{AFX_MSG(CDialogActions)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnComboActionsSelChanged();
	afx_msg void OnCheckVisible();
	afx_msg void OnCheckEnabled();
	afx_msg void OnCheckChecked();
	afx_msg void OnChangeEditCaption();
	afx_msg void OnChangeEditTooltip();
	afx_msg void OnChangeEditDescription();
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGACTIONS_H__2E0EB4F9_8AA3_4CE2_B48F_CCA5EFE08E78__INCLUDED_)
