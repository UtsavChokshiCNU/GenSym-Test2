#if !defined(AFX_TELEWINDOWSCTL_H__4DE919A1_A92F_44AF_A12D_3F1ADE832F43__INCLUDED_)
#define AFX_TELEWINDOWSCTL_H__4DE919A1_A92F_44AF_A12D_3F1ADE832F43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WebSCORaxCtl.h : Declaration of the CTelewindowsAxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CTelewindowsAxCtrl : See WebSCORaxCtl.cpp for implementation.

class CTelewindowsAxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTelewindowsAxCtrl)

private:
	bool m_bDidRunCode;
	CDataPathProperty ServerName;
	CDataPathProperty ServerPort;
	CDataPathProperty UserName;
	CDataPathProperty Password;
	CDataPathProperty SessionId;
	CDataPathProperty UserMode;

	void Run();
	CString GetProgramDir();

// Constructor
public:
	CTelewindowsAxCtrl();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelewindowsAxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CTelewindowsAxCtrl();

	DECLARE_OLECREATE_EX(CTelewindowsAxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CTelewindowsAxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTelewindowsAxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CTelewindowsAxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CTelewindowsAxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CTelewindowsAxCtrl)
	afx_msg BSTR GetServerPort();
	afx_msg void SetServerPort(LPCTSTR lpszNewValue);
	afx_msg BSTR GetServerName();
	afx_msg void SetServerName(LPCTSTR lpszNewValue);
	afx_msg BSTR GetUserName();
	afx_msg void SetUserName(LPCTSTR lpszNewValue);
	afx_msg BSTR GetPassword();
	afx_msg void SetPassword(LPCTSTR lpszNewValue);
	afx_msg BSTR GetSessionId();
	afx_msg void SetSessionId(LPCTSTR lpszNewValue);
	afx_msg BSTR GetUserMode();
	afx_msg void SetUserMode(LPCTSTR lpszNewValue);
	afx_msg int  Ping(LPCTSTR server, LPCTSTR port);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CTelewindowsAxCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CTelewindowsAxCtrl)
	dispidServerPort = 1L,
	dispidServerName = 2L,
	dispidUserName = 3L,
	dispidPassword = 4L,
	dispidSessionId = 5L,
	dispidUserMode = 6L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBSCORAXCTL_H__4DE919A1_A92F_44AF_A12D_3F1ADE832F43__INCLUDED)
