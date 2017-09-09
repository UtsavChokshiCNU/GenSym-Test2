#if !defined(AFX_PROXYSETTINGSDLG_H__DACFE028_A429_43FA_9432_92472E66706D__INCLUDED_)
#define AFX_PROXYSETTINGSDLG_H__DACFE028_A429_43FA_9432_92472E66706D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProxySettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProxySettingsDlg dialog

class CProxySettingsDlg : public CDialog
{
// Construction
public:
	CProxySettingsDlg(CWnd* pParent = NULL);   // standard constructor
	int loadFromFile(CString filename);
	int writeToFile(CString filename);
// Dialog Data
	//{{AFX_DATA(CProxySettingsDlg)
	enum { IDD = IDD_PROPPAGE_SMALL };
	CString	m_password;
	CString	m_domain;
	CString	m_username;
	CString	m_script;
	CString	m_proxyserver;
	BOOL	m_useauthentication;
	BOOL	m_useautoconfig;
	BOOL	m_useproxy;
	CString	m_port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProxySettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProxySettingsDlg)
	afx_msg void OnCheckUseauthentication();
	afx_msg void OnCheckUseautoconfig();
	afx_msg void OnCheckUseproxy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROXYSETTINGSDLG_H__DACFE028_A429_43FA_9432_92472E66706D__INCLUDED_)
