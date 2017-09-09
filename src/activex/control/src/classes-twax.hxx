#if !defined(AFX_CLASSES_TWAX_H__INCLUDED_)
#define AFX_CLASSES_TWAX_H__INCLUDED_

// classes-twax.hxx : Declaration of the CTelewindowsCtrl ActiveX Control class.

#include "gafx.h"
#include "defs-twax.h"

/////////////////////////////////////////////////////////////////////////////
// CTwAxInstance : See instance.cpp for implementation.

class CTwAxInstance : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

////////////////////////////////////////////////////////////////////////////
// CTwControlPropPage : See page.cpp for implementation.

class CTwControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTwControlPropPage)
	DECLARE_OLECREATE_EX(CTwControlPropPage)

// Constructor
public:
	CTwControlPropPage();

// Dialog Data
	//{{AFX_DATA(CTwControlPropPage)
	enum { IDD = IDD_PROPPAGE_TWAX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CTwControlPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl : See xtw.cpp for implementation.

class CTelewindowsCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTelewindowsCtrl)

// Constructor
public:
	CTelewindowsCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelewindowsCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL OnSetExtent(LPSIZEL lpSizeL);
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CTelewindowsCtrl();

	DECLARE_OLECREATE_EX(CTelewindowsCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CTelewindowsCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTelewindowsCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CTelewindowsCtrl)		// Type name and misc status
	
	// Subclassed control support
	BOOL IsSubclassedControl();

// Message maps
	//{{AFX_MSG(CTelewindowsCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
#ifdef L_IMPL_OBJECTSAFETY
	BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety)
		STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD __RPC_FAR *pdwSupportedOptions, DWORD __RPC_FAR *pdwEnabledOptions);
		STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
	END_INTERFACE_PART(ObjectSafety)

	DECLARE_INTERFACE_MAP();
#endif // L_IMPL_OBJECTSAFETY

// Dispatch maps
	//{{AFX_DISPATCH(CTelewindowsCtrl)
	afx_msg BSTR GetLaunchHost();
	afx_msg void SetLaunchHost(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchPort();
	afx_msg void SetLaunchPort(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchUserName();
	afx_msg void SetLaunchUserName(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchUserMode();
	afx_msg void SetLaunchUserMode(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchPassword();
	afx_msg void SetLaunchPassword(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchBackground();
	afx_msg void SetLaunchBackground(LPCTSTR lpszNewValue);
	afx_msg BSTR GetInitString();
	afx_msg void SetInitString(LPCTSTR lpszNewValue);
	afx_msg BSTR GetSplashtime();
	afx_msg void SetSplashtime(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchUI();
	afx_msg void SetLaunchUI(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchWindow();
	afx_msg void SetLaunchWindow(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchWorkspace();
	afx_msg void SetLaunchWorkspace(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLaunchWorkspaceUUID();
	afx_msg void SetLaunchWorkspaceUUID(LPCTSTR lpszNewValue);
	afx_msg BSTR GetTwLocation();
	afx_msg void SetTwLocation(LPCTSTR lpszNewValue);
	afx_msg BSTR GetLogFile();
	afx_msg void SetLogFile(LPCTSTR lpszNewValue);
	afx_msg void ConnectToG2();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CTelewindowsCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CTelewindowsCtrl)
	dispidTwLocation = 1L,
	dispidLaunchHost = 2L,
	dispidLaunchPort = 3L,
	dispidLaunchUserName = 4L,
	dispidLaunchUserMode = 5L,
	dispidLaunchPassword = 6L,
	dispidLaunchBackground = 7L,
	dispidInitString = 8L,
	dispidSplashtime = 9L,
	dispidLaunchUI = 10L,
	dispidLaunchWindow = 11L,
	dispidLaunchWorkspace = 12L,
	dispidLaunchWorkspaceUUID = 13L,
	dispidConnectToG2 = 14L,
	dispidLogFile = 15L,
	//}}AFX_DISP_ID
	};

private:
	HWND  m_hWnd;
	HWND  m_child_hWnd;

	HANDLE m_hProcess;
	DWORD m_dwThreadId;

	PTSTR m_Properties[TW_AX_NUMBER_OF_PROPERTIES];
        PTSTR m_TWLocationPerEnv;

	BOOL m_startTWAfterDraw;

	void StartTwInHwnd();
        void CouldNotInvokeError(TCHAR *);
        void InitializeStringProperties();
        BSTR GetActiveXStringProperty(int);
        void SetActiveXStringProperty(int, LPCTSTR);
	BOOL LookupTWProgram(TCHAR *, size_t);
	BOOL BuildTWOptions(TCHAR *, size_t);
        BOOL TextFitInBuffer(PTSTR, size_t);
        void MaybeRemoveSlash(PTSTR, size_t);
        BOOL CanExecute(struct _stat *);
        BOOL ComposeExeNameFromOcx(PTSTR, size_t);
	BOOL ReadWindowsRegistry(PTSTR, size_t);
	BOOL FindTwWindow();
	static BOOL CALLBACK FindTwWindow_1(HWND, LPARAM);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSES_TWAX_H__INCLUDED)
