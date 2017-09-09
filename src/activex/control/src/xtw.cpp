// xtw.cpp : Implementation of the CTelewindowsCtrl ActiveX Control class.

#include "classes-twax.hxx"

#include <sys/stat.h>

#ifdef _DEBUG
#  undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void set_minimum_debug_level (short debug_level);
extern BOOL initialize_logger ();
extern BOOL initialize_logger_with_logfile (TCHAR *logfile_name);

IMPLEMENT_DYNCREATE(CTelewindowsCtrl, COleControl)

#ifdef L_IMPL_OBJECTSAFETY
BEGIN_INTERFACE_MAP(CTelewindowsCtrl, COleControl)
  INTERFACE_PART(CTelewindowsCtrl, IID_IObjectSafety, ObjectSafety)
END_INTERFACE_MAP()
#endif // L_IMPL_OBJECTSAFETY
/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CTelewindowsCtrl, COleControl)
	//{{AFX_MSG_MAP(CTelewindowsCtrl)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CTelewindowsCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CTelewindowsCtrl)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "TwLocation",
			 GetTwLocation, SetTwLocation, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchHost",
			 GetLaunchHost, SetLaunchHost, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchPort",
			 GetLaunchPort, SetLaunchPort, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchUserName",
			 GetLaunchUserName, SetLaunchUserName, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchUserMode",
			 GetLaunchUserMode, SetLaunchUserMode, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchPassword",
			 GetLaunchPassword, SetLaunchPassword, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchBackground",
			 GetLaunchBackground, SetLaunchBackground, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "InitString",
			 GetInitString, SetInitString, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "Splashtime",
			 GetSplashtime, SetSplashtime, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchUI",
			 GetLaunchUI, SetLaunchUI, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchWindow",
			 GetLaunchWindow, SetLaunchWindow, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchWorkspace",
			 GetLaunchWorkspace, SetLaunchWorkspace, VT_BSTR)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LaunchWorkspaceUUID",
			 GetLaunchWorkspaceUUID, SetLaunchWorkspaceUUID, VT_BSTR)
	DISP_FUNCTION(CTelewindowsCtrl, "ConnectToG2",
		      ConnectToG2, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX(CTelewindowsCtrl, "LogFile",
			 GetLogFile, SetLogFile , VT_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CTelewindowsCtrl, COleControl)
	//{{AFX_EVENT_MAP(CTelewindowsCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CTelewindowsCtrl, 1)
	PROPPAGEID(CTwControlPropPage::guid)
END_PROPPAGEIDS(CTelewindowsCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTelewindowsCtrl, "TW.Telewindows.1",
	0xec99e4ee, 0xf5f1, 0x4323, 0x98, 0x29, 0x6, 0xe9, 0xb0, 0xaf, 0xb9, 0x34)

#define KEYNAME_CLSID TEXT("CLSID")
#define CLSID_AS_TEXT TEXT("{EC99E4EE-F5F1-4323-9829-06E9B0AFB934}")
#define KEYNAME_INPROC TEXT("InprocServer32")

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CTelewindowsCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DTwControl =
		{ 0xa3132a7d, 0x1a9a, 0x41c0, { 0x84, 0x68, 0x7a, 0xb, 0x2b,
						0xa3, 0xb0, 0xe8 } };
const IID BASED_CODE IID_DTwControlEvents =
		{ 0x480b1a49, 0xd990, 0x4385, { 0x9f, 0x67, 0x90, 0xb1, 0xc9,
						0x17, 0x4e, 0xea } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwTwControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CTelewindowsCtrl, IDS_TWAX, _dwTwControlOleMisc)


/////////////////////////////////////////////////////////////////////////////
// Global variables
//
// tw_ax_flags

static TCHAR *tw_ax_flags[TW_AX_NUMBER_OF_PROPERTIES][2] = 
{
  TW_WINDOWHANDLE_CMD, TEXT("-no-log"),
  NULL, NULL,  // Note the default value for TwLocation should NOT be
               // TW_DEFAULT_EXE, because this value overrides what's in
               // the registry, while TW_DEFAULT_EXE is only a last resort.
  TEXT("-remote-host-name"), DEFAULT_G2_HOST,
  TEXT("-remote-port-name-or-number"), DEFAULT_G2_PORT,
  TEXT("-user-name"), NULL,
  TEXT("-user-mode"), NULL,
  TEXT("-password"), NULL,
  TEXT("-background"), TEXT("light-gray"),
  TEXT("-init-string"), NULL,
  TEXT("-splashtime"), TEXT("0"),
  TEXT("-ui"), NULL,
  TEXT("-window"), NULL,
  TEXT("-workspace"), NULL,
  TEXT("-workspace-uuid"), NULL
};


/////////////////////////////////////////////////////////////////////////////
// FindTwWindow_1 -- is inelegant and a little paranoid.  First of all, it's a
// static method.  It is passed as a parameter to EnumChildWindows, and it's not
// possible to specify a member function to be a callback.  Secondly, the memset
// we do every time is pretty paranoid, but I really don't want to "operate" on
// any window which is not  Telewindows, so I want to make sure the buffer is
// not just still filled in from the last invocation.  jv, 6/16/03

BOOL CALLBACK CTelewindowsCtrl::FindTwWindow_1 (HWND child_hWnd,
                                                LPARAM tw_hwnd_out_lparam)
{
  int rval;
  HWND *tw_hwnd_out = (HWND *) tw_hwnd_out_lparam;
  static TCHAR window_class_name[LENGTH_OF_TW_CLASSNAME];

  memset(window_class_name, '\0', LENGTH_OF_TW_CLASSNAME);  // see above
  rval = GetClassName(child_hWnd, window_class_name, LENGTH_OF_TW_CLASSNAME);
  if (rval == 0) {
    dprintf(DERROR, "Could not obtain window class for hwnd 0x%x; not resizing",
	    child_hWnd);
    return FALSE;
  }

  rval = _tcsncmp(window_class_name, NAME_OF_TELEWINDOWS_WINDOW,
		  LENGTH_OF_TW_CLASSNAME);
  if (rval != 0) {
    dprintf(DERROR, "Child window 0x%x is of class %s, not %s",
	    child_hWnd, window_class_name, NAME_OF_TELEWINDOWS_WINDOW);
    return FALSE;
  }

  *tw_hwnd_out = child_hWnd;
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// InitializeStringProperties - just sets each member of the array to NULL.
// If any were not null previously, they need to be free'd before calling
// this function.

void CTelewindowsCtrl::InitializeStringProperties ()
{
  int i;

  for (i=0; i<TW_AX_NUMBER_OF_PROPERTIES; i++) {
    m_Properties[i] = NULL;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TextFitInBuffer - returns TRUE if the copied text fit into the buffer
// allocated for it, FALSE otherwise.  This maybe needs to be improved... 
// you think?  Still, it would never happen unless someone was actively trying
// to break things.  All of our buffer sizes are set exceedingly large to avoid
// these problems.

BOOL CTelewindowsCtrl::TextFitInBuffer (PTSTR p_buffer, size_t p_size)
{
  if ((int)_tcslen(p_buffer) > p_size) {
    dprintf(DERROR, "Sorry... overwrote buffer options.");
    dprintf(DERROR, "Your executable space is now corrupt.");
    // This is a kind of DLL loaded into the container... we are corrupting
    // the container's space, and we could presumably exit out of it entirely
    // here.  That might be a bit severe, though.
    return FALSE;
  }
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CouldNotInvokeError - puts up an informative dialog box when there was an
// error invoking TW.  (Usually this error will be that the path found in
// the registry or by default did not point to an actual file.)  Note that
// FormatMessage is supposed to do just that... format it any way we like.
// However, I found the interface painful and decided, for now at least, to
// just use wsprintf instead.

void CTelewindowsCtrl::CouldNotInvokeError (PTSTR p_tw_executable)
{
  PVOID lpMsgBuf = NULL;
  int length;
  PTSTR messageString;
  LPCTSTR introString = TEXT("Attempting to invoke ");

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(PTSTR) &lpMsgBuf, 0, NULL);
  length = 3 + _tcslen((PTSTR)lpMsgBuf) + _tcslen(p_tw_executable) +
    _tcslen(introString);  // bad to hard-code 3?  colon, space, null terminator
  messageString = (PTSTR)malloc(length * sizeof(TCHAR));
  wsprintf(messageString, TEXT("%s%s: %s"), introString, p_tw_executable,
	   (PTSTR)lpMsgBuf);
  LocalFree(lpMsgBuf);

  MessageBox((LPCTSTR)messageString, TEXT("Error"), MB_OK | MB_ICONINFORMATION);
  free(messageString);
}


/////////////////////////////////////////////////////////////////////////////
// StartTwInHwnd - finds tw.exe, builds a command line using either the
// user-specified options or the defaults, creates the TW process, and hooks
// it up to the HWND.

void CTelewindowsCtrl::StartTwInHwnd ()
{
  PROCESS_INFORMATION pinfo;
  STARTUPINFO si;
  TCHAR cbuf[MAX_PATH];
  TCHAR tw_executable[MAX_PATH];
  TCHAR options[MAX_PATH];
  int cx, cy;

  dprintf(DUMP, "xtw StartTwInHwnd method call");
  if (m_hWnd == (HWND) NULL) {
    dprintf(DERROR, "Error: StartTWHwnd called with NULL");
    return;
  }
  dprintf(PROGRESS, "hwnd = 0x%x", (long) m_hWnd);

  if (m_hProcess != 0) {
    TerminateProcess(m_hProcess, 0);
  }

  m_child_hWnd = NULL;
  m_startTWAfterDraw = FALSE;
  GetControlSize(&cx, &cy);
  LookupTWProgram(tw_executable, MAX_PATH);
  BuildTWOptions(options, MAX_PATH);
  wsprintf(cbuf, TEXT("%s %s %s -width %d -height %d %s"),
	   tw_executable, m_Properties[TW_AX_CL_HOST],
	   m_Properties[TW_AX_CL_PORT], cx, cy, options);
  dprintf(PROGRESS, "built command line: %s", cbuf);

  if (!TextFitInBuffer(cbuf, MAX_PATH)) return;

  ZeroMemory(&pinfo, sizeof(PROCESS_INFORMATION));
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);

  if (0 == CreateProcess(NULL, cbuf, NULL, NULL, FALSE, DETACHED_PROCESS, 
			 NULL, NULL, &si, &pinfo)) {
    CouldNotInvokeError(tw_executable);
    return;
  }

  m_hProcess = pinfo.hProcess;
  m_dwThreadId = pinfo.dwThreadId;
  dprintf(DETAIL, "got 0x%x as thread id", m_dwThreadId);

  InvalidateControl();
  UpdateWindow();
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::CTelewindowsCtrl - Constructor

CTelewindowsCtrl::CTelewindowsCtrl ()
{
  LPTSTR temp;
  DWORD env_var_length;

  dprintf(DUMP, "xtw constructor method call");
  InitializeIIDs(&IID_DTwControl, &IID_DTwControlEvents);
  InitializeStringProperties();

  temp = (TCHAR *)malloc((_tcslen(DEFAULT_G2_HOST) + 1) * sizeof(TCHAR));
  (void)_tcscpy(temp, DEFAULT_G2_HOST);
  m_Properties[TW_AX_CL_HOST] = temp;

  temp = (TCHAR *)malloc((_tcslen(DEFAULT_G2_PORT) + 1) * sizeof(TCHAR));
  (void)_tcscpy(temp, DEFAULT_G2_PORT);
  m_Properties[TW_AX_CL_PORT] = temp;

  m_hProcess = 0;
  m_dwThreadId = 0;
  m_hWnd = NULL;
  m_child_hWnd = NULL;

  m_TWLocationPerEnv = (TCHAR *)malloc(MAX_PATH * sizeof(TCHAR));
  env_var_length = GetEnvironmentVariable(TW_AX_ENV_VAR,
					  m_TWLocationPerEnv, MAX_PATH);
  if ((env_var_length <= 0) || (env_var_length > MAX_PATH)) {
    free(m_TWLocationPerEnv);
    m_TWLocationPerEnv = NULL;
    dprintf(DETAIL, "no value found for environment variable %s",
	    TW_AX_ENV_VAR);
  }

  // If this were to really be like TW, it would attempt to connect to G2 as
  // soon as it started up.  But it's more powerful this way -- you can set
  // parameters and otherwise operate on the control before connecting.
  m_startTWAfterDraw = FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::OnResetState - Reset control to default state

void CTelewindowsCtrl::OnResetState ()
{
  dprintf(DUMP, "xtw OnResetState method call");
  COleControl::OnResetState();  // Resets defaults found in DoPropExchange

  // TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::DoPropExchange - Persistence support

void CTelewindowsCtrl::DoPropExchange (CPropExchange *pPX)
{
  dprintf(DUMP, "xtw DoPropExchange method call");
  ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
  COleControl::DoPropExchange(pPX);

  // TODO: Call PX_ functions for each persistent custom property.
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::FindTwWindow - uses EnumChildWindows and the helper C
// function FindTwWindow_1 to look for a child of m_hWnd which is of the
// Telewindows class.

BOOL CTelewindowsCtrl::FindTwWindow ()
{
  dprintf(DUMP, "xtw FindTwWindow method call");

  if (m_hWnd == NULL) {
    dprintf(PROGRESS, "m_hWnd is NULL, cannot find child window of it");
    return FALSE;
  }
  ::EnumChildWindows(m_hWnd, FindTwWindow_1, LPARAM(&m_child_hWnd));
  if (m_child_hWnd == NULL) {
    dprintf(DETAIL, "Could not find child window for hwnd 0x%x.  Not connected",
	    m_hWnd);
    return FALSE;
  }
  dprintf(PROGRESS, "Obtained HWND 0x%x for Telewindows window.",
	  (unsigned long) m_child_hWnd);
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::OnSetExtent -- gets called when the control is resized.
// When that happens, we then want to tell Telewindows to resize itself so
// that it continues to take up the exact size of the control's window, no
// more and no less.  Then, at the end of the function, we redraw the entire
// window.  That is probably extreme, but I don't feel that comfortable figuring
// out which region of TW should become invalidated by the resize.  I would have
// hoped that calling SetWindowPos would have caused TW to determine for itself
// what regions were invalid.  It seems to work fine with VB, but not with the
// ActiveX Control Test Container.  Redrawing the whole window leaves us
// confident that it will work 100% of the time, albeit perhaps with a slight
// flicker. jv, 6/16/03, 1/12/04

BOOL CTelewindowsCtrl::OnSetExtent (PSIZEL pSizeL) 
{
  BOOL found_child = FALSE, succeeded = FALSE;

  dprintf(DUMP, "xtw OnSetExtent method call");

  if ((m_child_hWnd != NULL) && (! ::IsWindow(m_child_hWnd))) {
    // Whoops, something happened!!  Presumably, this happens if TW shuts down
    // unexpectedly.  If that's the case, we throw away the HWND we used to
    // have.  We then go on, because, in theory, TW might have shut down and
    // restarted already.  That seems very unlikely, but what's the big deal
    // about checking just to make sure?
    dprintf(DERROR, "Error: former child HWND 0x%x no longer exists.",
	    (unsigned long) m_child_hWnd);
    m_child_hWnd = NULL;
  }

  // OK, now it's NULL.  The only place we set m_child_hWnd to a non-NULL value
  // is in FindTwWindow, and this is the only place we call FindTwWindow, so it
  // will be the case that m_child_hWnd at least once per TW invocation.  In
  // other words, reaching this code does NOT necessarily imply anything has
  // gone wrong.  -jv, 1/15/04
  if (m_child_hWnd == NULL) {
    dprintf(DETAIL, "m_child_hWnd == NULL; calling FindTwWindow");
    FindTwWindow();
  } else {
    dprintf(DUMP, "using existing value of 0x%x for TW's window",
	    (unsigned long) m_child_hWnd);
  }

  // OK, third time we're checking it.  If it's NULL at THIS point, that means
  // we ran EnumChildWindows and were unable to find a TW child window.  We have
  // already printed an error messsage in FindTwWindow.  If we get inside this
  // block, we are finally in the success case.  We do a lot of "C" Win32 stuff
  // here.  Controlling a child HWND is not very C++.
  if (m_child_hWnd != NULL) {
    CClientDC dc(CWnd::FromHandle(::GetDesktopWindow()));
    CSize sz(pSizeL->cx, pSizeL->cy);

    dc.HIMETRICtoDP(&sz); // Convert the size to pixels
    ::SetWindowPos(m_child_hWnd, NULL, 0, 0, sz.cx, sz.cy,
		   (SWP_NOMOVE | SWP_NOZORDER));
    // Redraw the entire window; see comments above.
    ::RedrawWindow(m_child_hWnd, NULL, NULL, (RDW_INVALIDATE | RDW_UPDATENOW));
    found_child = TRUE;
  }
  // Call superior method whether we obtained the child HWND or not
  succeeded = COleControl::OnSetExtent(pSizeL);
  return (found_child && succeeded);
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::IsSubclassedControl - This is a subclassed control

BOOL CTelewindowsCtrl::IsSubclassedControl ()
{
  dprintf(DUMP, "xtw IsSubclassedControl method call");
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::OnSize

void CTelewindowsCtrl::OnSize (UINT p_type, int p_cx, int p_cy)
{
#ifdef _DEBUG
  TCHAR *messageType;

  switch (p_type) {
  case SIZE_RESTORED:
    messageType = TEXT("Restored");
    break;

  case SIZE_MAXIMIZED:
    messageType = TEXT("Maximized");
    break;

  case SIZE_MINIMIZED:
    messageType = TEXT("Minimized");
    break;

  case SIZE_MAXHIDE:
    messageType = TEXT("MaxHide");
    break;

  case SIZE_MAXSHOW:
    messageType = TEXT("MaxShow");
    break;

  default:
    messageType = TEXT("other");
  }

  dprintf(DUMP, "xtw OnSize %s method call; x = %d, y = %d",
	  messageType, p_cx, p_cy);
#endif // _DEBUG

  // TODO: Add your message handler code here
  COleControl::OnSize(p_type, p_cx, p_cy);
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::OnDraw - Drawing function

void CTelewindowsCtrl::OnDraw (CDC *pdc, const CRect &rcBounds, const CRect&)
{
  dprintf(DUMP, "xtw OnDraw method call, (%d, %d) - (%d, %d)",
	  rcBounds.left, rcBounds.top, rcBounds.right, rcBounds.bottom);
  if (m_hWnd == (HWND) NULL) {
    m_hWnd = (HWND)GetHwnd();
    if (! ::IsWindow(m_hWnd)) {
      dprintf(DERROR, "Error: value obtained for HWND is not a window!  (0x%x)",
	      (unsigned long) m_hWnd);
      m_hWnd = (HWND)NULL;
    }
    if (m_hWnd != (HWND) NULL) {
      dprintf(PROGRESS, "got hwnd 0x%x from OnDraw", (long) m_hWnd);
      if (m_startTWAfterDraw) {
	StartTwInHwnd();
      }
    }
  }
  // This draw really should only happen if TW is not drawing into the window;
  // however, we really don't know if that is happening or not.  That is a
  // problem in general.  If TW dies unexpectedly, we're not aware of it.
  // Maybe this would be a good place to do a little polling; if TW is still
  // up and running, we don't have to draw here.  If it is dead, we draw the
  // gray rectangle, and also do other stuff that is appropriate, knowing that
  // we are no longer connected.  -jv, 1/15/04
  pdc->FillRect(rcBounds,
		CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::~CTelewindowsCtrl - Destructor

CTelewindowsCtrl::~CTelewindowsCtrl ()
{
  int i;

  dprintf(DUMP, "xtw destructor method call");
  for (i=0; i<TW_AX_NUMBER_OF_PROPERTIES; i++) {
    if (m_Properties[i] != NULL) {
      free(m_Properties[i]);
    }
  }
  InitializeStringProperties();
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsCtrl::CTelewindowsCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CTelewindowsCtrl

BOOL CTelewindowsCtrl::CTelewindowsCtrlFactory::UpdateRegistry (BOOL bRegister)
{
  dprintf(DUMP, "xtw %s method call", 
	  "CTelewindowsCtrl::CTelewindowsCtrlFactory::UpdateRegistry");
  // TODO: Verify that your control follows apartment-model threading rules.
  // Refer to MFC TechNote 64 for more information.
  // If your control does not conform to the apartment-model rules, then
  // you must modify the code below, changing the 6th parameter from
  // afxRegApartmentThreading to 0.

  if (bRegister) {
    return AfxOleRegisterControlClass(AfxGetInstanceHandle(),
				      m_clsid,
				      m_lpszProgID,
				      IDS_TWAX,
				      IDB_TWAX,
				      afxRegApartmentThreading,
				      _dwTwControlOleMisc,
				      _tlid,
				      _wVerMajor,
				      _wVerMinor);
  } else {
    return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
  }
}


#ifdef L_IMPL_OBJECTSAFETY

/////////////////////////////////////////////////////////////////////////////
// GetInterfaceSafetyOptions - Implementation of IObjectSafety

STDMETHODIMP CTelewindowsCtrl::XObjectSafety::GetInterfaceSafetyOptions
   (REFIID riid, 
    DWORD __RPC_FAR *pdwSupportedOptions, 
    DWORD __RPC_FAR *pdwEnabledOptions)
{
  METHOD_PROLOGUE_EX(CTelewindowsCtrl, ObjectSafety)

  dprintf(DUMP, "xtw %s method call",
	  "CTelewindowsCtrl::XObjectSafety::GetInterfaceSafetyOptions");
  if (!pdwSupportedOptions || !pdwEnabledOptions) {
    return E_POINTER;
  }

  *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER |
    INTERFACESAFE_FOR_UNTRUSTED_DATA;
  *pdwEnabledOptions = 0;

  if (NULL == pThis->GetInterface(&riid)) {
    dprintf(DERROR, "Requested interface is not supported.");
    return E_NOINTERFACE;
  }

  if (riid == IID_IDispatch) {
    // Client wants to know if object is safe for scripting
    *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
    return S_OK;
  } else if (riid == IID_IPersistPropertyBag 
	     || riid == IID_IPersistStreamInit
	     || riid == IID_IPersistStorage
	     || riid == IID_IPersistMemory) {
    // Those are the persistence interfaces COleControl derived controls support
    // as indicated in AFXCTL.H.  Client wants to know if object is safe for
    // initializing from persistent data
    *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
    return S_OK;
  } else {
    // Find out what interface this is, and decide what options to enable
    dprintf(DERROR, "We didn't account for the safety of this interface, %s",
	    "and it's one we support...");
    return E_NOINTERFACE;
  }
}

/////////////////////////////////////////////////////////////////////////////
// SetInterfaceSafetyOptions

STDMETHODIMP CTelewindowsCtrl::XObjectSafety::SetInterfaceSafetyOptions
   (REFIID riid, 
    DWORD dwOptionSetMask, 
    DWORD dwEnabledOptions)
{
  METHOD_PROLOGUE_EX(CTelewindowsCtrl, ObjectSafety)

  OLECHAR szGUID[GUID_STRING_LENGTH];

  dprintf(DUMP, "xtw %s method call",
	  "CTelewindowsCtrl::XObjectSafety::SetInterfaceSafetyOptions");
  // What is this interface anyway?
  // We can do a quick lookup in the registry under HKEY_CLASSES_ROOT\Interface
  StringFromGUID2(riid, szGUID, GUID_STRING_LENGTH);

  if (0 == dwOptionSetMask && 0 == dwEnabledOptions) {
    // the control certainly supports NO requests through the specified interface
    // so it's safe to return S_OK even if the interface isn't supported.
    return S_OK;
  }

  // Do we support the specified interface?
  if (NULL == pThis->GetInterface(&riid)) {
    // IDispatchEx
    dprintf(DERROR, "%lS is not supported.", szGUID);
    return E_FAIL;
  }


  if (riid == IID_IDispatch) {
    dprintf(DETAIL, "Client asking if it's safe to call through IDispatch.");
    dprintf(DETAIL, "In other words, is the control safe for scripting?");
    if (INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwOptionSetMask && 
	INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwEnabledOptions) {
      return S_OK;
    } else {
      return E_FAIL;
    }
  } else if (riid == IID_IPersistPropertyBag 
	     || riid == IID_IPersistStreamInit
	     || riid == IID_IPersistStorage
	     || riid == IID_IPersistMemory) {
    dprintf(DETAIL, "Client asking if it's safe to call through IPersist*.");
    dprintf(DETAIL, "%s, %s",
	    "In other words",
	    "is the control safe for initializing from persistent data?");

    if (INTERFACESAFE_FOR_UNTRUSTED_DATA == dwOptionSetMask &&
	INTERFACESAFE_FOR_UNTRUSTED_DATA == dwEnabledOptions) {
      return NOERROR;
    } else {
      return E_FAIL;
    }
  } else {
    dprintf(DERROR, "We didn't account for the safety of %s, %s...",
	    szGUID, "and it's one we support");
    return E_FAIL;
  }
}

/////////////////////////////////////////////////////////////////////////////
// AddRef

STDMETHODIMP_(ULONG) CTelewindowsCtrl::XObjectSafety::AddRef()
{
  METHOD_PROLOGUE_EX_(CTelewindowsCtrl, ObjectSafety)
  dprintf(DUMP, "xtw CTelewindowsCtrl::XObjectSafety::AddRef method call");
  return (ULONG)pThis->ExternalAddRef();
}

/////////////////////////////////////////////////////////////////////////////
// Release

STDMETHODIMP_(ULONG) CTelewindowsCtrl::XObjectSafety::Release()
{
  METHOD_PROLOGUE_EX_(CTelewindowsCtrl, ObjectSafety)
  dprintf(DUMP, "xtw CTelewindowsCtrl::XObjectSafety::Release method call");
  return (ULONG)pThis->ExternalRelease();
}

/////////////////////////////////////////////////////////////////////////////
// QueryInterface

STDMETHODIMP CTelewindowsCtrl::XObjectSafety::QueryInterface (REFIID iid,
							      PVOID* ppvObj)
{
  METHOD_PROLOGUE_EX_(CTelewindowsCtrl, ObjectSafety)
  dprintf(DUMP, "xtw %s method call",
	  "CTelewindowsCtrl::XObjectSafety::QueryInterface");
  return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

#endif // L_IMPL_OBJECTSAFETY


/////////////////////////////////////////////////////////////////////////////
// MaybeRemoveSlash
//
// if the given string ends with a slash, remove it
void CTelewindowsCtrl::MaybeRemoveSlash (PTSTR string, size_t length)
{
  if (string[length - 1] == PATH_SEPARATOR_AS_CHAR)
    string[length - 1] = '\0';
}


/////////////////////////////////////////////////////////////////////////////
// CanExecute
//
//  PURPOSE: returns true if the given string represents a pathname on which the
//    user has execute permission.
//
//  COMMENTS:  Depending on the filesystem, Windows *kind of* has the notion
//    of user- and group-permissions, but I really don't think it's worth
//    worrying about.  We can just use the results of stat, and if the file
//    is marked _S_IEXEC, trust that we can execute it, and that if it isn't,
//    we can't.
BOOL CTelewindowsCtrl::CanExecute (struct _stat *stat_buf)
{
  return ((_S_IEXEC & stat_buf->st_mode) == _S_IEXEC);
}


/////////////////////////////////////////////////////////////////////////////
// ComposeExeNameFromOcx
// 
// We check the registry to find "our" own location; that is, where is this
// OCX located.  It stands to reason there might be a much more direct way
// to obtain this information, to find out exactly what file has been loaded
// into the container, but for the time being, I don't know any better way
// to do it than this.  I think this is the standard way.  I just look up
// our CLSID in the registry, and get the value of InprocServer32.  The
// key names and CLSID are coded in #define's at the top of this file.
//    Note that this logic is not necessarily very helpful for 7.0a0 if used
// with the registerTwControl.bat file, because in that case it's unlikely
// that the TwControl.ocx and tw.exe actually are in the same directory.
// However, if the control is registered through the cab file, it will install
// tw.exe in the same place, and everything should work groovy.
//    Here's where we can store stuff: HKEY_LOCAL_MACHINE\SOFTWARE\Gensym
// and HKEY_CURRENT_USER\SOFTWARE\Gensym
//
// Given a pathname to an OCX, this method fills in a value of a Telewindows
// executable in the same directory.
//   This method is not Unicode friendly.  It should be adapted to work in
// either character set.

BOOL CTelewindowsCtrl::ComposeExeNameFromOcx (PTSTR p_buf, size_t p_length)
{
  HKEY clsid_key, my_key;
  LONG kstatus;
  TCHAR ocx_name[MAX_PATH];
  long ocx_strlen, i;

  dprintf(DUMP, "xtw ComposeExeNameFromOcx method call");

  kstatus = RegOpenKeyEx(HKEY_CLASSES_ROOT, KEYNAME_CLSID, 0,
			 KEY_READ, &clsid_key);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed to open root CLSID key");
    return FALSE;
  }
  kstatus = RegOpenKeyEx(clsid_key, CLSID_AS_TEXT, 0, KEY_ALL_ACCESS, &my_key);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed to open TwControl's clsid key");
    return FALSE;
  }
  kstatus = RegQueryValue(my_key, KEYNAME_INPROC, ocx_name, &ocx_strlen);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed getting inproc server, key status = 0x%x", kstatus);
    return FALSE;
  }

  for (i=ocx_strlen-1; (i>0) && (ocx_name[i] != '\\'); i--)
    ;
  if (ocx_name[i] != '\\') {
    dprintf(PROGRESS, "did not find backslash in %s", ocx_name);
    return FALSE;
  }
  if ((++i + TW_NAME_LEN) > p_length) {
    dprintf(DERROR, "pathname of ocx too long to use for executable");
    return FALSE;
  }
  _tcsncpy(p_buf, ocx_name, i);
  _tcsncpy((p_buf+i), TW_FILENAME, TW_NAME_LEN);
  p_buf[i + TW_NAME_LEN] = '\0';
  dprintf(DUMP, "composed executable name = \"%s\"", p_buf);
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// ReadWindowsRegistry
//
// We check the registry to find where Telewindows is installed.  We expect the
// G2 Bundle Installer to write the directory into the following key:
//     HKEY_LOCAL_MACHINE\SOFTWARE\Gensym\Telewindows\<version>\installDirClassic

BOOL CTelewindowsCtrl::ReadWindowsRegistry (PTSTR p_buf, size_t p_length)
{
  HKEY tw_key, vs_key;
  LONG kstatus;
  DWORD return_type;
  PTSTR szTwDir;
  BOOL need_slash = TRUE;
  unsigned long twdir_len = MAX_PATH;
  unsigned char tw_install_dir[MAX_PATH];

  dprintf(DUMP, "cws ReadWindowsRegistry method call");

  kstatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TW_AX_TELEWINDOWS_KEY, 0, KEY_READ, &tw_key);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed to open %s key", TW_AX_TELEWINDOWS_KEY);
    return FALSE;
  }
  // At this point, maybe we should query to see what versions are available,
  // instead of just looking for 8.0a0.  To be improved.
  kstatus = RegOpenKeyEx(tw_key, TW_AX_VERSION_KEY, 0, KEY_ALL_ACCESS, &vs_key);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed to open %s key", TW_AX_VERSION_KEY);
    RegCloseKey(tw_key);
    return FALSE;
  }
  kstatus = RegQueryValueEx(vs_key, TW_AX_DIR_VALUE, NULL, &return_type,
			    tw_install_dir, &twdir_len);
  RegCloseKey(vs_key);
  RegCloseKey(tw_key);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed getting value of %s subkey, status = 0x%x",
	    TW_AX_DIR_VALUE, kstatus);
    return FALSE;
  }
  if (return_type != REG_SZ) {
    dprintf(DERROR, "received unknown type of data, %d, from %s subkey",
	    return_type, TW_AX_DIR_VALUE);
    return FALSE;
  }

  szTwDir = (PTSTR) tw_install_dir;
  // There's one little thing about the return values I don't quite understand.
  // The length returned seems to be one too long.  Well, whatever.  Adjust
  // length so that szTwDir[len]==0, and szTwDir[len-1]!=0.
  while (szTwDir[twdir_len - 1] == 0) twdir_len--;
  need_slash = (szTwDir[twdir_len - 1] != PATH_SEPARATOR_AS_CHAR);

  if ((twdir_len + TW_NAME_LEN + (need_slash ? 1 : 0)) > p_length) {
    dprintf(DERROR, "pathname of install dir too long to use for executable");
    return FALSE;
  }

  _tcsncpy(p_buf, (PTSTR) tw_install_dir, twdir_len);
  if (need_slash) {
    p_buf[twdir_len] = PATH_SEPARATOR_AS_CHAR;
    twdir_len++;
  }
  _tcsncpy((p_buf+twdir_len), TW_FILENAME, TW_NAME_LEN);
  p_buf[twdir_len + TW_NAME_LEN] = '\0';
  dprintf(DUMP, "composed executable name = \"%s\"", p_buf);
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// LookupTWProgram - private method to figure out which tw.exe we want to
// invoke in StartTwInHwnd.
//    We first check the environment variable.  The name of the environment
// variable is defined by the preprocessor constant TW_AX_ENV_VAR, declared in
// defs-twax.h and technically it could change, but it probably will always be
// TW_HOME_FOR_ACTIVEX.  We check the value of that variable when the control is
// constructed; however, we check the *validity* of that value each time this
// method is called.  That is because the executable could appear or disappear
// between the time the object is created and the time that connectToG2 is
// called.  If no TW is found in the location given by the environment variable,
// we check the registry.  If we don't find a valid value there, we have a
// default to try.

BOOL CTelewindowsCtrl::LookupTWProgram (TCHAR *p_buf, size_t p_length)
{
  int len, snrval, status;
  struct _stat stat_buf;

  dprintf(DUMP, "xtw LookupTwProgram method call");

  if (m_Properties[TW_AX_TW_LOCATION] != NULL) {
    _tcsncpy(p_buf, m_Properties[TW_AX_TW_LOCATION], p_length);
    dprintf(DUMP, "using already-filled-in property of %s for tw.exe",
	    p_buf);
    return TRUE;
  }

  // Check the environment variable.
  if (m_TWLocationPerEnv != NULL) {
    len = _tcslen(m_TWLocationPerEnv);
    MaybeRemoveSlash(m_TWLocationPerEnv, len);
    if (len > 0) {
      status = _tstat(m_TWLocationPerEnv, &stat_buf);
      if (status == 0) {
	if (S_ISDIR(stat_buf.st_mode)) {
	  dprintf(PROGRESS, "%s is a directory, %s",
		  TW_AX_ENV_VAR, m_TWLocationPerEnv);
	  snrval = _sntprintf(p_buf, p_length, _T("%s\\%s"), m_TWLocationPerEnv,
			      TW_FILENAME);
	  if (snrval <= 0) {
	    dprintf(DERROR, "Error: value of environment variable %s %s",
		    TW_AX_ENV_VAR, ": string too long");
	    return FALSE;
	  }
	} else {
	  _tcsncpy(p_buf, m_TWLocationPerEnv, p_length);
	  if (p_buf[p_length - 1] != '\0') {
	    dprintf(DERROR, "Error: value of environment variable %s %s",
		    TW_AX_ENV_VAR, ": string too long");
	    return FALSE;
	  }
	}
	if (CanExecute(&stat_buf)) {
	  dprintf(DUMP, "using environment variable value of %s for tw.exe",
		  p_buf);
	  return TRUE;
	}
	dprintf(DERROR, "Error: %s is not executable; ignoring value.", p_buf);
      } else {
	dprintf(DERROR, "Error: could not stat %s; ignoring value.",
		m_TWLocationPerEnv);
      }
    }
  }

  // Look in the registry
  if (ComposeExeNameFromOcx(p_buf, p_length)) {
    dprintf(PROGRESS, "registry filled in TW home with %s", p_buf);
    return TRUE;
  }

  // If not found, use the default:
  _tcsncpy(p_buf, TW_DEFAULT_EXE, p_length);
  dprintf(DUMP, "no alternative found; using default value of %s for tw.exe",
	  p_buf);
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// BuildTWOptions - private method to build the command line for tw.exe
// to be invoked in StartTwInHwnd

BOOL CTelewindowsCtrl::BuildTWOptions (TCHAR *p_buf, size_t p_length)
{
  TCHAR *options;
  int i;

  // At this point, m_hWnd should never be NULL, but if it is, start TW in
  // its own window, so the problem is obvious.  If we are in debug mode, start
  // with no-long so we can better debug it.
  if (m_hWnd != (HWND)NULL) {
    wsprintf(p_buf, TEXT("%s 0x%x"), TW_WINDOWHANDLE_CMD, m_hWnd);
  } else {
    dprintf(DERROR, "No HWND available when TW to be launched.");
#ifdef _DEBUG
    wsprintf(p_buf, TEXT("-no-log"));
#endif
  }
  options = p_buf + _tcslen(p_buf);

  for (i=TW_AX_OPTIONAL_ARGS_BEGIN; i<=TW_AX_OPTIONAL_ARGS_END; i++) {
    if (m_Properties[i] && (0 == _tcslen(m_Properties[i]))) {
      // Does discarding a zero-length string leak?  Probably...
      // however, no reason to take a risk for this particular commit.
      // Clean up soon.  - jv, 10/2/02
      m_Properties[i] = NULL;
    }
    dprintf(PROGRESS, "flags[%d] = %s, properties[%d] = %s",
	    i, tw_ax_flags[i][0], i, m_Properties[i]);
    if (m_Properties[i]) {
      wsprintf(options, _T(" %s %s"), tw_ax_flags[i][0], m_Properties[i]);
      options = p_buf + _tcslen(p_buf);
    } else if (tw_ax_flags[i][1]) {
      wsprintf(options, _T(" %s %s"), tw_ax_flags[i][0], tw_ax_flags[i][1]);
      options = p_buf + _tcslen(p_buf);
    }
  }

  return TextFitInBuffer(p_buf, p_length);
}

/////////////////////////////////////////////////////////////////////////////
// GetActiveXStringProperty
//
// I don't like this implementation.  The macros USES_CONVERSION and T2OLE come
// from afxpriv.h, which is not really standard and has the contract that it
// can change in an incompatible way if Microsoft pleases.  It is also ugly to
// use weird things like USES_CONVERSION.  There has got to be a real, standard,
// preferably Win32 way to go from a PTSTR to a BSTR.  -jv, 1/17/04

BSTR CTelewindowsCtrl::GetActiveXStringProperty (int ax_prop_id)
{
  USES_CONVERSION;
  return SysAllocString(T2OLE(m_Properties[ax_prop_id]));
}

/////////////////////////////////////////////////////////////////////////////
// SetActiveXStringProperty

void CTelewindowsCtrl::SetActiveXStringProperty (int ax_prop_id,
						 LPCTSTR pszNewValue)
{
  if (m_Properties[ax_prop_id] != NULL) free(m_Properties[ax_prop_id]);
  m_Properties[ax_prop_id] = (TCHAR *)malloc((_tcslen(pszNewValue) + 1) *
					     sizeof(TCHAR));
  _tcscpy(m_Properties[ax_prop_id], pszNewValue);

  SetModifiedFlag();
}



/////////////////////////////////////////////////////////////////////////////
// GetTwLocation and SetTwLocation

BSTR CTelewindowsCtrl::GetTwLocation () 
{
  dprintf(DUMP, "xtw GetTwLocation method call");
  return GetActiveXStringProperty(TW_AX_TW_LOCATION);
}

void CTelewindowsCtrl::SetTwLocation (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "xtw SetTwLocation method call");
  SetActiveXStringProperty(TW_AX_TW_LOCATION, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchHost and SetLaunchHost - the LaunchHost is used to create the
// command line for StartTwInHwnd.  If TW is running, calling SetLaunchHost
// does nothing except change the value.  The value will be used the *next*
// time TW is started up, but until then, setting the LaunchHost does little
// besides  changing the value returned by GetLaunchHost.
//   So, the value returned by GetLaunchHost is not necessarily "correct"
// either... it does not tell you the host that was launched to in the 
// running TW... it simply is the last value set.

BSTR CTelewindowsCtrl::GetLaunchHost () 
{
  dprintf(DUMP, "xtw GetLaunchHost method call");
  return GetActiveXStringProperty(TW_AX_CL_HOST);
}

void CTelewindowsCtrl::SetLaunchHost (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "xtw SetLaunchHost method call");
  SetActiveXStringProperty(TW_AX_CL_HOST, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchPort and SetLaunchPort

BSTR CTelewindowsCtrl::GetLaunchPort () 
{
  dprintf(DUMP, "xtw GetLaunchPort method call");
  return GetActiveXStringProperty(TW_AX_CL_PORT);
}

void CTelewindowsCtrl::SetLaunchPort (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchPort method call");
  SetActiveXStringProperty(TW_AX_CL_PORT, pszNewValue);
}

/////////////////////////////////////////////////////////////////////////////
// GetLaunchUserName and SetLaunchUserName - every "window" in G2 has an
// associated user-name and user-mode, and possibly a password.  

BSTR CTelewindowsCtrl::GetLaunchUserName () 
{
  dprintf(DUMP, "xtw GetLaunchUserName method call");
  return GetActiveXStringProperty(TW_AX_CL_USER_NAME);
}

void CTelewindowsCtrl::SetLaunchUserName (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchUserName method call");
  SetActiveXStringProperty(TW_AX_CL_USER_NAME, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchUserMode and SetLaunchUserMode - every "window" in G2 has an
// associated user-name and user-mode, and possibly a password.  

BSTR CTelewindowsCtrl::GetLaunchUserMode () 
{
  dprintf(DUMP, "xtw GetLaunchUserMode method call");
  return GetActiveXStringProperty(TW_AX_CL_USER_MODE);
}

void CTelewindowsCtrl::SetLaunchUserMode (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchUserMode method call");
  SetActiveXStringProperty(TW_AX_CL_USER_MODE, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchPassword and SetLaunchPassword - every "window" in G2 has an
// associated user-name and user-mode, and possibly a password.  

BSTR CTelewindowsCtrl::GetLaunchPassword () 
{
  dprintf(DUMP, "xtw GetLaunchPassword method call");
  return GetActiveXStringProperty(TW_AX_CL_PASSWORD);
}

void CTelewindowsCtrl::SetLaunchPassword (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchPassword method call");
  SetActiveXStringProperty(TW_AX_CL_PASSWORD, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchBackground and SetLaunchBackground

BSTR CTelewindowsCtrl::GetLaunchBackground () 
{
  dprintf(DUMP, "xtw GetLaunchBackground method call");
  return GetActiveXStringProperty(TW_AX_CL_BACKGROUND);
}

void CTelewindowsCtrl::SetLaunchBackground (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchBackground method call");
  SetActiveXStringProperty(TW_AX_CL_BACKGROUND, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetInitString and SetInitString - InitString doesn't quite suffer from
// the same problems as the other properties, because you wouldn't really
// expect setting the "InitString" to do anything instantly, just to be used
// to initialize the application when the application starts.  Still, calling
// GetInitString doesn't necessarily get you the string that was used to start
// Telewindows.

BSTR CTelewindowsCtrl::GetInitString () 
{
  dprintf(DUMP, "xtw GetInitString method call");
  return GetActiveXStringProperty(TW_AX_CL_INIT_STRING);
}

void CTelewindowsCtrl::SetInitString (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetInitString method call");
  SetActiveXStringProperty(TW_AX_CL_INIT_STRING, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetSplashtime and SetSplashtime - Splashtime doesn't suffer from the same
// problems as the other properties, because it is obvious it only has an
// effect at startup time.

BSTR CTelewindowsCtrl::GetSplashtime () 
{
  dprintf(DUMP, "xtw GetSplashtime method call");
  return GetActiveXStringProperty(TW_AX_CL_SPLASHTIME);
}

void CTelewindowsCtrl::SetSplashtime (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetSplashtime method call");
  SetActiveXStringProperty(TW_AX_CL_SPLASHTIME, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchUI and SetLaunchUI

BSTR CTelewindowsCtrl::GetLaunchUI () 
{
  dprintf(DUMP, "xtw GetLaunchUI method call");
  return GetActiveXStringProperty(TW_AX_CL_UI_MODE);
}

void CTelewindowsCtrl::SetLaunchUI (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchUI method call");

  if (0 == _tcscmp(pszNewValue, TEXT("verbose"))) {
    set_minimum_debug_level(DETAIL);
    pszNewValue = TEXT("standard");
  } else if (0 == _tcscmp(pszNewValue, TEXT("verbose-classic"))) {
    set_minimum_debug_level(DETAIL);
    pszNewValue = TEXT("classic");
  }
  SetActiveXStringProperty(TW_AX_CL_UI_MODE, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchWindow and SetLaunchWindow

BSTR CTelewindowsCtrl::GetLaunchWindow () 
{
  dprintf(DUMP, "xtw GetLaunchWindow method call");
  return GetActiveXStringProperty(TW_AX_CL_WINDOW_STYLE);
}

void CTelewindowsCtrl::SetLaunchWindow (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchWindow method call");
  SetActiveXStringProperty(TW_AX_CL_WINDOW_STYLE, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchWorkspace and SetLaunchWorkspace

BSTR CTelewindowsCtrl::GetLaunchWorkspace () 
{
  dprintf(DUMP, "xtw GetLaunchWorkspace method call");
  return GetActiveXStringProperty(TW_AX_CL_WORKSPACE);
}

void CTelewindowsCtrl::SetLaunchWorkspace (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchWorkspace method call");
  SetActiveXStringProperty(TW_AX_CL_WORKSPACE, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchWorkspaceUUID and SetLaunchWorkspaceUUID

BSTR CTelewindowsCtrl::GetLaunchWorkspaceUUID () 
{
  dprintf(DUMP, "xtw GetLaunchWorkspaceUUID method call");
  return GetActiveXStringProperty(TW_AX_CL_WORKSPACE_UUID);
}

void CTelewindowsCtrl::SetLaunchWorkspaceUUID (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLaunchWorkspaceUUID method call");
  SetActiveXStringProperty(TW_AX_CL_WORKSPACE_UUID, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// ConnectToG2 - attempts to obtain the HWND and either starts up TW
// if succeeded, or sets a variable which will cause TW to be started as soon
// as we do get the HWND.

void CTelewindowsCtrl::ConnectToG2 () 
{
  LPTSTR logFileStatus = NULL;

  dprintf(DUMP, "xtw ConnectToG2 method call");

  logFileStatus = m_Properties[TW_AX_CL_LOGFILE];
  if (logFileStatus == NULL) {
    initialize_logger();
  } else if (0 != _tcsicmp(logFileStatus, TEXT("false"))) {
    // user has requested a particular file name; try to use it
    initialize_logger_with_logfile(logFileStatus);
  }
  // else, user has supplied the string "false" for the logfile, which means,
  // do not create a log file

  if (m_hWnd != (HWND) NULL) {
    dprintf(PROGRESS, "already had hwnd 0x%x", (long) m_hWnd);
  } else {
    // Should this be set by default?  Even if it should be, give it one more
    // chance...
    m_hWnd = (HWND)GetHwnd();
  }

  // but, if still not set...
  if (m_hWnd == (HWND) NULL) {
    dprintf(DERROR, "Warning: could not obtain HWND; delaying starting TW");
    m_startTWAfterDraw = TRUE;
    return;
  }

  StartTwInHwnd();
}


/////////////////////////////////////////////////////////////////////////////
// GetLogFile and SetLogFile - LogFile may not suffer from the same problems as
// most of the other properties, because it is probably obvious it only has an
// effect at startup time.

BSTR CTelewindowsCtrl::GetLogFile ()
{
  dprintf(DUMP, "xtw GetLogFile method call");
  return GetActiveXStringProperty(TW_AX_CL_LOGFILE);
}

void CTelewindowsCtrl::SetLogFile (LPCTSTR pszNewValue) 
{
  dprintf(DUMP, "xtw SetLogFile method call");
  SetActiveXStringProperty(TW_AX_CL_LOGFILE, pszNewValue);
}
