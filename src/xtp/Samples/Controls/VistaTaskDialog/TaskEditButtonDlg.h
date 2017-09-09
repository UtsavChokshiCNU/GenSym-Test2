#if !defined(AFX_TASKEDITBUTTONDLG_H__AEF40CD1_D8B9_4867_8BAA_0E592EE8F3C4__INCLUDED_)
#define AFX_TASKEDITBUTTONDLG_H__AEF40CD1_D8B9_4867_8BAA_0E592EE8F3C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaskEditButtonDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTaskEditButtonDlg dialog

class CTaskSheetProperties;
class CTaskEditButtonDlg : public CDialog
{
public:
	CTaskEditButtonDlg(CComboBox* pWndCombo = NULL, BOOL bIsEdit = TRUE, CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CTaskEditButtonDlg)
	enum { IDD = IDD_TASKDIALOG_BUTTONEDIT };
	CEdit m_wndEditCtrl;
	CEdit m_wndEditText;
	CSpinButtonCtrl	m_wndSpinCtrl;
	CString	m_strText;
	int		m_nID;
	//}}AFX_DATA

	BOOL m_bIsEdit;
	CComboBox* m_pWndCombo;

	//{{AFX_VIRTUAL(CTaskEditButtonDlg)
	protected:
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	CArray<TASKDIALOG_BUTTON,TASKDIALOG_BUTTON&> m_arButtons;
	CTaskSheetProperties*                        m_pDlgParent;

	void GetNextAvailableID(BOOL bUpdateData = FALSE);
	void AddButton(PCWSTR pszText, int nButtonID);

	//{{AFX_MSG(CTaskEditButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKEDITBUTTONDLG_H__AEF40CD1_D8B9_4867_8BAA_0E592EE8F3C4__INCLUDED_)
