// TaskPageGeneral.h : header file
//
#if !defined(__TASKPAGEGENERAT_H__)
#define __TASKPAGEGENERAT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTaskPageGeneral dialog

class CTaskSheetProperties;
class CTaskPageGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CTaskPageGeneral)

public:
	CTaskPageGeneral();
	~CTaskPageGeneral();

	//{{AFX_DATA(CTaskPageGeneral)
	enum { IDD = IDD_TASKDIALOG_GENERAL };
	BOOL	m_bAllowCancel;
	BOOL	m_bHyperLinks;
	BOOL	m_bMarquee;
	BOOL	m_bPosition;
	BOOL	m_bProgress;
	BOOL	m_bRtl;
	BOOL	m_bVerify;
	BOOL	m_bWidth;
	CString	m_strContent;
	CString	m_strFooter;
	CString	m_strMainInstruction;
	CString	m_strWindowTitle;
	CString	m_strVerificationText;
	int		m_nCount;
	int		m_nWidth;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTaskPageGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:
	CTaskSheetProperties* m_pDlgParent;

	//{{AFX_MSG(CTaskPageGeneral)
	afx_msg void OnUpdateData();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnAdd();
public:
	afx_msg void OnBnClickedBtnSub();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TASKPAGEGENERAT_H__)
