#if !defined(AFX_GNSM_PROPS_WS_H__INCLUDED_)
#define AFX_GNSM_PROPS_WS_H__INCLUDED_

// props-ws.h : Declaration of the CWorkspaceView ActiveX Control class.

#include "afx-ws.h"
#include "defs-ws.h"

// registry tw version info
typedef struct tag_VerInfo
{
  int uiMajor;
  int uiMinor;
  int uiRev;
  TCHAR szRegKeyName[MAX_PATH];
} VERINFO, *LPVERINFO;

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewModule : See inst-ws.cpp for implementation.

typedef struct wsv_instance_struct
{
  class CWorkspaceView *theInstance;
  int session_id;
  AXL_IFACE *gateway;
  struct wsv_instance_struct *next;
} wsv_instance;


class CWorkspaceViewModule : public COleControlModule
{
public:
  BOOL InitInstance();
  int ExitInstance();
  int GetWorkspaceNumber(class CWorkspaceView *);
  void DestroyMe(class CWorkspaceView *, HANDLE);
  void SetGateway(class CWorkspaceView *, AXL_IFACE *);
  void SetSessionId(class CWorkspaceView *, int);
  void BroadcastTWConnection(AXL_IFACE *, int);
  void BroadcastTWShutdown(AXL_IFACE *, int);
  
private:
  int cWorkspaces;
  wsv_instance *m_InstanceChain;
};

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView : See cws.cpp for implementation.

class CWorkspaceView : public COleControl
{
  DECLARE_DYNCREATE(CWorkspaceView)
    
    // Constructor
public:
  CWorkspaceView();
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CWorkspaceView)
public:
  virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
  virtual void DoPropExchange(CPropExchange* pPX);
  virtual void OnResetState();
  virtual BOOL OnSetExtent(LPSIZEL lpSizeL);
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  ~CWorkspaceView();
  
  DECLARE_OLECREATE_EX(CWorkspaceView)    // Class factory and guid
    DECLARE_OLETYPELIB(CWorkspaceView)      // GetTypeInfo
    DECLARE_OLECTLTYPE(CWorkspaceView)		// Type name and misc status
    
    // Subclassed control support
    BOOL IsSubclassedControl();
  
  // Message maps
  //{{AFX_MSG(CWorkspaceView)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg LRESULT OnTWMessage(WPARAM, LPARAM);
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
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
    //{{AFX_DISPATCH(CWorkspaceView)
    afx_msg BSTR GetTwLocation();
    afx_msg void SetTwLocation(LPCTSTR lpszNewValue);
    afx_msg BSTR GetWorkspaceName();
    afx_msg void SetWorkspaceName(LPCTSTR lpszNewValue);
    afx_msg BSTR GetWorkspaceUUID();
    afx_msg void SetWorkspaceUUID(LPCTSTR lpszNewValue);
    afx_msg BSTR GetLaunchUserName();
    afx_msg void SetLaunchUserName(LPCTSTR lpszNewValue);
    afx_msg BSTR GetLaunchUserMode();
    afx_msg void SetLaunchUserMode(LPCTSTR lpszNewValue);
    afx_msg BSTR GetLaunchPassword();
    afx_msg void SetLaunchPassword(LPCTSTR lpszNewValue);
    afx_msg BSTR GetLaunchWindow();
    afx_msg void SetLaunchWindow(LPCTSTR lpszNewValue);
    afx_msg IUnknown *GetG2Gateway();
    afx_msg void SetG2Gateway(IUnknown *p_pUnk);
    afx_msg BOOL GetReconnect();
    afx_msg void SetReconnect(BOOL bNewValue);
    afx_msg HRESULT ConnectToG2Gateway(IUnknown *gateway_object);
    afx_msg HRESULT ShowWorkspaceWithName(LPCTSTR workspace_name);
    afx_msg HRESULT ShowWorkspaceWithUUID(LPCTSTR workspace_uuid);
    //}}AFX_DISPATCH
    DECLARE_DISPATCH_MAP()
      
      // Event maps
      //{{AFX_EVENT(CWorkspaceView)
      //}}AFX_EVENT
      DECLARE_EVENT_MAP()
      
      // Dispatch and event IDs
public:
  enum {
    //{{AFX_DISP_ID(CWorkspaceView)
    dispidTwLocation = 1L,
      dispidWorkspaceName = 2L,
      dispidWorkspaceUUID = 3L,
      dispidLaunchUserName = 4L,
      dispidLaunchUserMode = 5L,
      dispidLaunchPassword = 6L,
      dispidLaunchWindow = 7L,
      dispidG2Gateway = 8L,
      dispidReconnect = 9L,
      dispidConnectToG2Gateway = 10L,
      dispidShowWorkspaceWithName = 11L,
      dispidShowWorkspaceWithUUID = 12L,
      //}}AFX_DISP_ID
  };
  
public:
  void NoteTWConnection(AXL_IFACE *, int);
  void NoteTWShutdown(AXL_IFACE *, int);
  void ReceiveTWProcId(HANDLE);
  
private:
  // These variables are the internal representation of the user-visible
  // properties of the WorkspaceView control
  PTSTR m_Properties[GWVC_NUMBER_OF_PROPERTIES];
  short m_WorkspaceSpecification;
  
  HWND  m_hWnd;
  HWND  m_child_hWnd;
  AXL_IFACE *m_gw;
  IUnknown *m_pUnk;
  
  HANDLE m_hProcess;
  DWORD m_dwThreadId;
  
  PTSTR m_TWLocationPerEnv;
  // These are always ASCII strings because TW only understands ASCII
  // on the command line.
  char *m_Host;
  char *m_Port;
  int m_SessionId;
  int m_InstanceId;
  
  BOOL m_nothingToShow;
  BOOL m_reconnect;
  BOOL m_startTWAfterDraw;
  
  BOOL BuildTWOptions(TCHAR *, size_t);
  BOOL CanExecute(struct stat *);
  BOOL FindTwWindow();
  BOOL LookupTWProgram(TCHAR *, size_t);
  BOOL ObtainHostAndPort(BSTR);
  BOOL ReadWindowsRegistry(PTSTR);
  BOOL TextFitInBuffer(PTSTR, size_t);
  BSTR GetActiveXStringProperty(int);
  HRESULT RunOrConnectToTW();
  HRESULT RunTwNowOrDeferred();
  void CouldNotInvokeError(TCHAR *);
  LRESULT DisconnectFromTW();
  void InitializeStringProperties();
  void MaybeRemoveSlash(PTSTR, size_t);
  void SetActiveXStringProperty(int, LPCTSTR);
  void SetVerbosity(short, BOOL);
  void ShowWorkspace(BSTR, BOOL);
  void InitializeWorkspaceView();
  void StartTwInHwnd();
  static BOOL CALLBACK FindTwWindow_1(HWND, LPARAM);
  BOOL GetVersion(LPTSTR szVer);
  BOOL ParseRegKeyName(LPCTSTR szRegKey, UINT &uiMajor, UINT &uiMinor, UINT &uiRev);
  BOOL FindTwPath(LPTSTR szTwPath, UINT uiVersion, UINT uiSubVersion, UINT uiBuild);
  BOOL UpdateLatestVersionInfo(LPVERINFO vi, UINT uiMajor, UINT uiMinor, UINT uiRev, LPTSTR szRegKeyName);
  BOOL GetInstallDir(HKEY hKey, LPTSTR szSubKey, LPBYTE szInstallDir);
  int CompareVersions(LPVERINFO vi1, LPVERINFO vi2);  
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GNSM_PROPS_WS_H__INCLUDED)
