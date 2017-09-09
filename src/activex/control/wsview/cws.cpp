/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Filename:      cws.cpp
 +
 + Gensym module: activex/control/wsview
 +
 + File Summmary: Implementation of the Workspace View class
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +   MS Windows portions:
 +              2001 - 2005      jv
 +
 + Description:
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP
 +
 + External Interface:
 +
 + Dependencies:
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   01/19/04,  jv: Created, from activex/control/src/xtw.cpp.  Through some CVS
 +   trickery, this file appears to have a much longer history.  I did that for
 +   archeological purposes, being able to find out when code changed or was
 +   introduced (in xtw.cpp).  What I imagine we should _really_ be doing is
 +   sharing the code to a much greater extent; but since they are two different
 +   C++ classes, that can be painful.  We need to get this done for 8.0a0, and
 +   this is how I'm doing it, and in four years I can look back and read this
 +   comment and be sad.
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <sys/stat.h>
#include "props-ws.h"
#include "G2Com_i.c"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define NOT_CONNECTED_TO_TW (m_SessionId < GWVC_LOWEST_VALID_TW_SESSION)

#ifdef _DEBUG
#  undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CWorkspaceViewModule theApp;

IMPLEMENT_DYNCREATE(CWorkspaceView, COleControl)

#ifdef L_IMPL_OBJECTSAFETY
BEGIN_INTERFACE_MAP(CWorkspaceView, COleControl)
  INTERFACE_PART(CWorkspaceView, IID_IObjectSafety, ObjectSafety)
END_INTERFACE_MAP()
#endif // L_IMPL_OBJECTSAFETY
/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWorkspaceView, COleControl)
        //{{AFX_MSG_MAP(CWorkspaceView)
        ON_WM_SIZE()
        ON_MESSAGE(WM_TELEWINDOWS_SESSION_ID, OnTWMessage)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CWorkspaceView, COleControl)
        //{{AFX_DISPATCH_MAP(CWorkspaceView)
        DISP_PROPERTY_EX(CWorkspaceView, "TwLocation",
                         GetTwLocation, SetTwLocation, VT_BSTR)
        DISP_PROPERTY_EX(CWorkspaceView, "WorkspaceName",
                         GetWorkspaceName, SetWorkspaceName, VT_BSTR)
        DISP_PROPERTY_EX(CWorkspaceView, "WorkspaceUUID",
                         GetWorkspaceUUID, SetWorkspaceUUID, VT_BSTR)
        DISP_PROPERTY_EX(CWorkspaceView, "LaunchUserName",
                         GetLaunchUserName, SetLaunchUserName, VT_BSTR)
        DISP_PROPERTY_EX(CWorkspaceView, "LaunchUserMode",
                         GetLaunchUserMode, SetLaunchUserMode, VT_BSTR)
        DISP_PROPERTY_EX(CWorkspaceView, "LaunchPassword",
                         GetLaunchPassword, SetLaunchPassword, VT_BSTR)
        DISP_PROPERTY_EX(CWorkspaceView, "LaunchWindow",
                         GetLaunchWindow, SetLaunchWindow, VT_BSTR)
        DISP_PROPERTY_EX(CWorkspaceView, "G2Gateway",
                         GetG2Gateway, SetG2Gateway, VT_UNKNOWN)
        DISP_PROPERTY_EX(CWorkspaceView, "Reconnect",
                         GetReconnect, SetReconnect, VT_BOOL)
        DISP_FUNCTION(CWorkspaceView, "ConnectToG2Gateway",
                      ConnectToG2Gateway, VT_ERROR, VTS_UNKNOWN)
        DISP_FUNCTION(CWorkspaceView, "ShowWorkspaceWithName",
                      ShowWorkspaceWithName, VT_ERROR, VTS_BSTR)
        DISP_FUNCTION(CWorkspaceView, "ShowWorkspaceWithUUID",
                      ShowWorkspaceWithUUID, VT_ERROR, VTS_BSTR)
        //}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CWorkspaceView, COleControl)
        //{{AFX_EVENT_MAP(CWorkspaceView)
        // NOTE - ClassWizard will add and remove event map entries
        //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWorkspaceView, "Gensym.WorkspaceView.1",
        0xA02C8A0F, 0x46E9, 0x450f, 0xB1, 0x73, 0xFB, 0xC8, 0x5F, 0x1F, 0x5E, 0x91)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CWorkspaceView, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DWorkspaceView =
                { 0x3068339E, 0x6be7, 0x4bbd,
                  { 0x85, 0x3f, 0x84, 0x92, 0xf1, 0x50, 0xd2, 0xa4 } };

const IID BASED_CODE IID_DWorkspaceViewEvents =
                { 0x50985B9F, 0x47e6, 0x4e26,
                  { 0xb0, 0x41, 0xdf, 0xa1, 0x23, 0xcf, 0xfb, 0xba } };



/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwWorkspaceViewOleMisc =
        OLEMISC_ACTIVATEWHENVISIBLE |
        OLEMISC_SETCLIENTSITEFIRST |
        OLEMISC_INSIDEOUT |
        OLEMISC_CANTLINKINSIDE |
        OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CWorkspaceView, IDS_GWVC, _dwWorkspaceViewOleMisc)


/////////////////////////////////////////////////////////////////////////////
// Global variables
//
// telewindows_flags

static TCHAR *telewindows_flags[GWVC_NUMBER_OF_PROPERTIES][2] =
{
  TW_WINDOWHANDLE_CMD, TEXT("-no-log"),
  NULL, NULL,  // Note the default value for TwLocation should NOT be
               // TW_DEFAULT_EXE, because this value overrides what's in
               // the registry, while TW_DEFAULT_EXE is only a last resort.
  TEXT("-workspace"), NULL,
  TEXT("-workspace-uuid"), NULL,
  TEXT("-user-name"), NULL,
  TEXT("-user-mode"), NULL,
  TEXT("-password"), NULL,
  TEXT("-window"), NULL
};


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP
 %
 % Description:
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/////////////////////////////////////////////////////////////////////////////
// FindTwWindow_1 -- is inelegant and a little paranoid.  First of all, it's a
// static method.  It is passed as a parameter to EnumChildWindows, and it's not
// possible to specify a member function to be a callback.  Secondly, the memset
// we do every time is pretty paranoid, but I really don't want to "operate" on
// any window which is not  Telewindows, so I want to make sure the buffer is
// not just still filled in from the last invocation.  jv, 6/16/03

BOOL CALLBACK CWorkspaceView::FindTwWindow_1 (HWND child_hWnd,
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

  rval = _tcsncmp(window_class_name, NAME_OF_WORKSPACE_VIEW_WINDOW,
                  LENGTH_OF_TW_CLASSNAME);
  if (rval != 0) {
    dprintf(DERROR, "Warning: child window 0x%x is of class %s, not %s",
            child_hWnd, window_class_name, NAME_OF_WORKSPACE_VIEW_WINDOW);
    // We used to exit the method here, but for the 8.0a0 release, at least
    // we won't.  We want to make sure we resize whatever is the child window,
    // regardless of class.  -jv, 1/20/04
    // return FALSE;
  }

  *tw_hwnd_out = child_hWnd;
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// SetVerbosity -- add a way to call this!!!

void CWorkspaceView::SetVerbosity (short new_level, BOOL allow_quieting)
{
  dprintf(DUMP, "cws SetVerbosity method call");

  if (allow_quieting) {
    set_debug_level(new_level);
  } else {
    set_minimum_debug_level(new_level);
  }
}


/////////////////////////////////////////////////////////////////////////////
// InitializeStringProperties - just sets each member of the array to NULL.
// If any were not null previously, they need to be free'd before calling
// this function.

void CWorkspaceView::InitializeStringProperties ()
{
  int i;

  for (i=0; i<GWVC_NUMBER_OF_PROPERTIES; i++) {
    m_Properties[i] = NULL;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TextFitInBuffer - returns TRUE if the copied text fit into the buffer
// allocated for it, FALSE otherwise.  This maybe needs to be improved...
// you think?  Still, it would never happen unless someone was actively trying
// to break things.  All of our buffer sizes are set exceedingly large to avoid
// these problems.

BOOL CWorkspaceView::TextFitInBuffer (PTSTR p_buffer, size_t p_size)
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
BOOL CWorkspaceView::CanExecute (struct stat *stat_buf)
{
  return ((_S_IEXEC & stat_buf->st_mode) == _S_IEXEC);
}


/////////////////////////////////////////////////////////////////////////////
// MaybeRemoveSlash
//
// if the given string ends with a slash, remove it
void CWorkspaceView::MaybeRemoveSlash (PTSTR string, size_t length)
{
  if (string[length - 1] == PATH_SEPARATOR_AS_CHAR)
    string[length - 1] = '\0';
}


/////////////////////////////////////////////////////////////////////////////
// CouldNotInvokeError - puts up an informative dialog box when there was an
// error invoking TW.  (Usually this error will be that the path found in
// the registry or by default did not point to an actual file.)  Note that
// FormatMessage is supposed to do just that... format it any way we like.
// However, I found the interface painful and decided, for now at least, to
// just use wsprintf instead.

void CWorkspaceView::CouldNotInvokeError (PTSTR p_tw_executable)
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
// ReadWindowsRegistry
//
// We check the registry to find where Telewindows is installed.  We expect the
// G2 Bundle Installer to write the directory into the following key:
//     HKEY_LOCAL_MACHINE\SOFTWARE\Gensym\Telewindows\<version>\installDir
//
// Note: this function and those it calls "know" that the buffer we are using is
// MAX_PATH characters long.  This should be improved.

BOOL CWorkspaceView::ReadWindowsRegistry (PTSTR p_buf)
{
  LONG kstatus;
  PTSTR szTwDir;
  unsigned long twdir_len = MAX_PATH;
  unsigned char tw_install_dir[MAX_PATH];

  dprintf(DUMP, "cws ReadWindowsRegistry method call");

#if 0
  HKEY tw_key, vs_key;
  DWORD return_type;

  kstatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, GWVC_TELEWINDOWS_KEY, 0,
                         KEY_READ, &tw_key);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed to open %s key", GWVC_TELEWINDOWS_KEY);
    return FALSE;
  }
  // At this point, maybe we should query to see what versions are available,
  // instead of just looking for 8.0r0.  To be improved.  Bug HQ-4720342,
  // "workspace view registry lookup is too version-specific" -jv, 6/20/04
  kstatus = RegOpenKeyEx(tw_key, GWVC_VERSION_KEY, 0, KEY_ALL_ACCESS, &vs_key);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed to open %s key", GWVC_VERSION_KEY);
    RegCloseKey(tw_key);
    return FALSE;
  }
  kstatus = RegQueryValueEx(vs_key, GWVC_DIR_VALUE, NULL, &return_type,
                            tw_install_dir, &twdir_len);
  RegCloseKey(vs_key);
  RegCloseKey(tw_key);
  if (kstatus != ERROR_SUCCESS) {
    dprintf(DERROR, "failed getting value of %s subkey, status = 0x%x",
            GWVC_DIR_VALUE, kstatus);
    return FALSE;
  }
  if (return_type != REG_SZ) {
    dprintf(DERROR, "received unknown type of data, %d, from %s subkey",
            return_type, GWVC_DIR_VALUE);
    return FALSE;
  }
#endif

  // BEGIN new registry stuff

  // Look in the registry
  ZeroMemory(tw_install_dir, twdir_len);
  if (!GetVersion((LPTSTR)tw_install_dir)) {
    kstatus = -1;
    dprintf(DERROR, "failed getting tw.exe out of registry");
    return FALSE;
  }
  // END new registry stuff

  szTwDir = (PTSTR) tw_install_dir;
  // There's one little thing about the return values I don't quite understand.
  // The length returned seems to be one too long.  Well, whatever.  Adjust
  // length so that szTwDir[len]==0, and szTwDir[len-1]!=0.
  while (szTwDir[twdir_len - 1] == 0) {
    twdir_len--;
  }

#if 0
  BOOL need_slash = TRUE;

  need_slash = (szTwDir[twdir_len - 1] != PATH_SEPARATOR_AS_CHAR);

  int len = twdir_len+TW_NAME_LEN+(need_slash?1:0);

  if ((twdir_len + TW_NAME_LEN + (need_slash ? 1 : 0)) > MAX_PATH) {
    dprintf(DERROR, "pathname of install dir too long to use for executable");
    return FALSE;
  }
#endif

  ZeroMemory(p_buf, twdir_len+sizeof(TCHAR));
  _tcsncpy(p_buf, (PTSTR) tw_install_dir, twdir_len);
  dprintf(DUMP, "composed executable name = \"%s\"", p_buf);

  return TRUE;

#if 0
  if (need_slash) {
    p_buf[twdir_len] = PATH_SEPARATOR_AS_CHAR;
    twdir_len++;
  }
  _tcsncpy((p_buf+twdir_len), TW_FILENAME, TW_NAME_LEN);
  p_buf[twdir_len + TW_NAME_LEN] = '\0';
  dprintf(DUMP, "composed executable name = \"%s\"", p_buf);
  return TRUE;
#endif
}


/////////////////////////////////////////////////////////////////////////////
// LookupTWProgram - private method to figure out which tw.exe we want to
// invoke in StartTwInHwnd.
//    We first check the environment variable.  The name of the environment
// variable is defined by the preprocessor constant TW_AX_ENV_VAR, declared in
// defs-ws.h and technically it could change, but it probably will always be
// TW_HOME_FOR_ACTIVEX.  We check the value of that variable when the control is
// constructed; however, we check the *validity* of that value each time this
// method is called.  That is because the executable could appear or disappear
// between the time the object is created and the time that connectToG2 is
// called.  If no TW is found in the location given by the environment variable,
// we check the registry.  If we don't find a valid value there, we have a
// default to try.

BOOL CWorkspaceView::LookupTWProgram (TCHAR *p_buf, size_t p_length)
{
  int len, snrval, status;
  struct stat stat_buf;
  TCHAR module_name[MAX_PATH];

  dprintf(DUMP, "cws LookupTwProgram method call");

  module_name[0] = 0;
  // GetModuleFileNameEx(0, 0, module_name, MAX_PATH);
  dprintf(0, "module name = \"%s\"", module_name);

  if (m_Properties[GWVC_TW_LOCATION] != NULL) {
    _tcsncpy(p_buf, m_Properties[GWVC_TW_LOCATION], p_length);
    dprintf(DUMP, "using already-filled-in property of %s for tw.exe",
            p_buf);
    return TRUE;
  }

  // Check the environment variable.
  if (m_TWLocationPerEnv != NULL) {
    len = _tcslen(m_TWLocationPerEnv);
    MaybeRemoveSlash(m_TWLocationPerEnv, len);
    if (len > 0) {
      status = stat(m_TWLocationPerEnv, &stat_buf);
      if (status == 0) {
        if (S_ISDIR(stat_buf.st_mode)) {
          dprintf(PROGRESS, "%s is a directory, %s",
                  TW_AX_ENV_VAR, m_TWLocationPerEnv);
          snrval = _sntprintf(p_buf, p_length, "%s\\%s", m_TWLocationPerEnv,
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

  if (ReadWindowsRegistry(p_buf)) {
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

BOOL CWorkspaceView::BuildTWOptions (TCHAR *p_buf, size_t p_length)
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

  for (i=GWVC_OPTIONAL_ARGS_BEGIN; i<=GWVC_OPTIONAL_ARGS_END; i++) {
    if (m_Properties[i] && (0 == _tcslen(m_Properties[i]))) {
      // Does discarding a zero-length string leak?  Probably...
      // however, no reason to take a risk for this particular commit.
      // Clean up soon.  - jv, 10/2/02
      m_Properties[i] = NULL;
    }
    dprintf(DUMP, "flags[%d] = %s, properties[%d] = %s",
            i, telewindows_flags[i][0], i, m_Properties[i]);
    if (m_Properties[i]) {
      wsprintf(options, " %s %s", telewindows_flags[i][0], m_Properties[i]);
      options = p_buf + _tcslen(p_buf);
    } else if (telewindows_flags[i][1]) {
      wsprintf(options, " %s %s", telewindows_flags[i][0],
               telewindows_flags[i][1]);
      options = p_buf + _tcslen(p_buf);
    }
  }

  return TextFitInBuffer(p_buf, p_length);
}

/////////////////////////////////////////////////////////////////////////////
// StartTwInHwnd - finds tw.exe, builds a command line using either the
// user-specified options or the defaults, creates the TW process, and hooks
// it up to the HWND.  Ideally, this code would live in ActiveX Link, but
// for the Alpha, at least, it remains here.

void CWorkspaceView::StartTwInHwnd ()
{
  PROCESS_INFORMATION pinfo;
  STARTUPINFO si;
  TCHAR cbuf[MAX_PATH];
  TCHAR tw_executable[MAX_PATH];
  TCHAR options[MAX_PATH];
  int cx, cy;

  if (m_Host == NULL) {
    dprintf(DERROR, "Warning: G2 Host not set; not starting TW");
    return;
  } else if (m_Port == NULL) {
    dprintf(DERROR, "Warning: G2 Port not set; not starting TW");
    return;
  }

  dprintf(DUMP, "cws StartTwInHwnd method call");
  if (m_hWnd == (HWND) NULL) {
    dprintf(DERROR, "Error: StartTWHwnd called with NULL");
    return;
  }
  dprintf(PROGRESS, "hwnd = 0x%x", (long) m_hWnd);

  if (m_hProcess != GWVC_NO_TW_PROCESS_ID) {
    TerminateProcess(m_hProcess, 0);
  }

  m_child_hWnd = NULL;
  GetControlSize(&cx, &cy);
  LookupTWProgram(tw_executable, MAX_PATH);
  BuildTWOptions(options, MAX_PATH);

  wsprintf(cbuf, TEXT("%s %s %s -ui multiwindow -width %d -height %d %s"),
           tw_executable, m_Host, m_Port, cx, cy, options);
  dprintf(PROGRESS, "built command line: %s", cbuf);

  if (!TextFitInBuffer(cbuf, MAX_PATH)) return;

  ZeroMemory(&pinfo, sizeof(PROCESS_INFORMATION));
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);

  if (0 == CreateProcess(NULL, cbuf, NULL, NULL, FALSE, DETACHED_PROCESS,
                         NULL, NULL, &si, &pinfo)) {
    CouldNotInvokeError(tw_executable);
    DisconnectFromTW();
    return;
  }

  m_startTWAfterDraw = FALSE;
  m_hProcess = pinfo.hProcess;
  m_dwThreadId = pinfo.dwThreadId;
  dprintf(DETAIL, "got 0x%x as thread id", m_dwThreadId);

  InvalidateControl();
  UpdateWindow();
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::CWorkspaceView - Constructor

CWorkspaceView::CWorkspaceView ()
{
  DWORD env_var_length;

  dprintf(DUMP, "cws constructor method call");
  InitializeIIDs(&IID_DWorkspaceView, &IID_DWorkspaceViewEvents);
  InitializeStringProperties();

  m_hProcess = GWVC_NO_TW_PROCESS_ID;
  m_dwThreadId = 0;
  m_SessionId = GWVC_NO_TW_SESSION;
  m_WorkspaceSpecification = GWVC_SHOW_BY_UUID;
  m_nothingToShow = TRUE;
  m_startTWAfterDraw = FALSE;

  m_hWnd = NULL;
  m_child_hWnd = NULL;
  m_gw = NULL;
  m_Host = NULL;
  m_Port = NULL;
  m_InstanceId = theApp.GetWorkspaceNumber(this);

  m_TWLocationPerEnv = (TCHAR *)malloc(MAX_PATH * sizeof(TCHAR));
  env_var_length = GetEnvironmentVariable(TW_AX_ENV_VAR,
                                          m_TWLocationPerEnv, MAX_PATH);
  if ((env_var_length <= 0) || (env_var_length > MAX_PATH)) {
    free(m_TWLocationPerEnv);
    m_TWLocationPerEnv = NULL;
    dprintf(DETAIL, "no value found for environment variable %s",
            TW_AX_ENV_VAR);
  }
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::OnResetState - Reset control to default state

void CWorkspaceView::OnResetState ()
{
  dprintf(DUMP, "cws OnResetState method call");
  COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::OnTWMessage

LRESULT CWorkspaceView::OnTWMessage (WPARAM wp_SessionId, LPARAM)
{
  HRESULT hr;
  int session_id = (int) wp_SessionId;

  dprintf(DUMP, "cws OnTWMessage method call");

  if (session_id < GWVC_LOWEST_VALID_TW_SESSION) {
    // TW has sent us a message saying it is shutting down.
    return DisconnectFromTW();
  }

  m_SessionId = session_id;
  theApp.SetSessionId(this, m_SessionId);
  dprintf(PROGRESS, "ws %d, tw.exe set session id to %d",
          m_InstanceId, m_SessionId);

  if (m_gw == NULL) {
    dprintf(DERROR, "received session id, but no G2Gateway pointer");
    return (LRESULT)0;
  }

  hr = m_gw->put_TWHandle(m_SessionId);
  dprintf(PROGRESS, "called put_TWHandle with %d; result = %d",
          m_SessionId, hr);
  theApp.BroadcastTWConnection(m_gw, m_SessionId);
  InitializeWorkspaceView();

  return (LRESULT)0;
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::DoPropExchange - Persistence support

void CWorkspaceView::DoPropExchange (CPropExchange *pPX)
{
  dprintf(DUMP, "cws DoPropExchange method call");
  ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
  COleControl::DoPropExchange(pPX);
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::FindTwWindow - uses EnumChildWindows and the helper C
// function FindTwWindow_1 to look for a child of m_hWnd which is of the
// Telewindows class.

BOOL CWorkspaceView::FindTwWindow ()
{
  dprintf(DUMP, "cws FindTwWindow method call");

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
  dprintf(PROGRESS, "Obtained HWND 0x%x for Telewindows child window.",
          (unsigned long) m_child_hWnd);
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::OnSetExtent -- gets called when the control is resized.
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

BOOL CWorkspaceView::OnSetExtent (PSIZEL pSizeL)
{
  BOOL found_child = FALSE, succeeded = FALSE;

  dprintf(DUMP, "cws OnSetExtent method call");

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
// CWorkspaceView::IsSubclassedControl - This is a subclassed control.  The
// MSDN doc says, "Called by the framework to determine if the control
// subclasses a Windows control. You must override this function and return TRUE
// if your OLE control subclasses a Windows control."  And so we do.  But this
// is very ininteresting, so we don't even do a DUMP-level dprintf here.
//
// Update: removing this dprintf caused HQ-4711916 "workspace view disappears"
// on my work PC.  I've been unable to reproduce it on other machines.  But it
// is very reproducible on the one machine.  Here's what I do: Run the VB Demo.
// Have the VB window in the foreground, with a larger window behind it.  Hit
// the iconify button of the larger window.  One of the workspace views may turn
// grey.  Clicking in the workspace view (to give it focus) and hitting F5 does
// restore things, and so do various other things that cause a redraw (such as
// resizing the VB app window).
//
// Putting the dprintf back in stopped the problem.  I then verified that it
// really is a race condition by putting the Sleep() call in below.  25 ms
// (milliseconds, 1/40 of a second) really does seem to be enough.  There's
// very little harm in sticking it in there.
//
// The real solution, I think, is to only draw our gray rectangle when TW is not
// drawing us.  However, as of 8.0a0, we are actually quite far from being able
// to know reliably whether or not TW is drawing us.  -jv, 1/28/04

BOOL CWorkspaceView::IsSubclassedControl ()
{
  // dprintf(DUMP, "cws IsSubclassedControl method call");
  Sleep(25);
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::OnSize

void CWorkspaceView::OnSize (UINT p_type, int p_cx, int p_cy)
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

  dprintf(DUMP, "cws OnSize %s method call; x = %d, y = %d",
          messageType, p_cx, p_cy);
#endif // _DEBUG

  COleControl::OnSize(p_type, p_cx, p_cy);
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::OnDraw - Drawing function

void CWorkspaceView::OnDraw (CDC *pdc, const CRect &rcBounds, const CRect&)
{
  dprintf(DUMP, "cws %d OnDraw method call, (%d, %d) - (%d, %d)", m_InstanceId,
          rcBounds.left, rcBounds.top, rcBounds.right, rcBounds.bottom);

  // This draw really should only happen if TW is not drawing into the window;
  // however, we really don't know if that is happening or not.  That is a
  // problem in general.  If TW dies unexpectedly, we're not aware of it.
  // Maybe this would be a good place to do a little polling; if TW is still
  // up and running, we don't have to draw here.  If it is dead, we draw the
  // gray rectangle, and also do other stuff that is appropriate, knowing that
  // we are no longer connected.  -jv, 1/15/04
  pdc->FillRect(rcBounds,
                CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));

  if (m_hWnd == (HWND) NULL) {
    m_hWnd = (HWND)GetHwnd();
    if (! ::IsWindow(m_hWnd)) {
      dprintf(DERROR, "Error: value obtained for HWND is not a window!  (0x%x)",
              (unsigned long) m_hWnd);
      m_hWnd = (HWND)NULL;
    }
    if (m_hWnd == (HWND) NULL) {
      dprintf(DERROR, "Warning: even in OnDraw, cannot obtain HWND");
    } else {
      dprintf(PROGRESS, "got hwnd 0x%x from OnDraw", (long) m_hWnd);
      if (m_startTWAfterDraw) {
        StartTwInHwnd();
      }
    }
  }

  if (!m_nothingToShow && NOT_CONNECTED_TO_TW) {
    RunOrConnectToTW();
  }
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::~CWorkspaceView - Destructor

CWorkspaceView::~CWorkspaceView ()
{
  int i;

  dprintf(DUMP, "cws destructor method call");
  for (i=0; i<GWVC_NUMBER_OF_PROPERTIES; i++) {
    if (m_Properties[i] != NULL) {
      free(m_Properties[i]);
    }
  }
  InitializeStringProperties();
  theApp.DestroyMe(this, m_hProcess);
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView::CWorkspaceViewFactory::UpdateRegistry -
// Adds or removes system registry entries for CWorkspaceView

BOOL CWorkspaceView::CWorkspaceViewFactory::UpdateRegistry (BOOL bRegister)
{
  dprintf(DUMP, "cws %s method call",
          "CWorkspaceView::CWorkspaceViewFactory::UpdateRegistry");
  // TODO: Verify that your control follows apartment-model threading rules.
  // Refer to MFC TechNote 64 for more information.
  // If your control does not conform to the apartment-model rules, then
  // you must modify the code below, changing the 6th parameter from
  // afxRegApartmentThreading to 0.

  if (bRegister) {
    return AfxOleRegisterControlClass(AfxGetInstanceHandle(),
                                      m_clsid,
                                      m_lpszProgID,
                                      IDS_GWVC,
                                      IDB_GWVC,
                                      afxRegApartmentThreading,
                                      _dwWorkspaceViewOleMisc,
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

STDMETHODIMP CWorkspaceView::XObjectSafety::GetInterfaceSafetyOptions
   (REFIID riid,
    DWORD __RPC_FAR *pdwSupportedOptions,
    DWORD __RPC_FAR *pdwEnabledOptions)
{
  METHOD_PROLOGUE_EX(CWorkspaceView, ObjectSafety)

  dprintf(DUMP, "cws %s method call",
          "CWorkspaceView::XObjectSafety::GetInterfaceSafetyOptions");
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

STDMETHODIMP CWorkspaceView::XObjectSafety::SetInterfaceSafetyOptions
   (REFIID riid,
    DWORD dwOptionSetMask,
    DWORD dwEnabledOptions)
{
  METHOD_PROLOGUE_EX(CWorkspaceView, ObjectSafety)

  OLECHAR szGUID[GUID_STRING_LENGTH];

  dprintf(DUMP, "cws %s method call",
          "CWorkspaceView::XObjectSafety::SetInterfaceSafetyOptions");
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

STDMETHODIMP_(ULONG) CWorkspaceView::XObjectSafety::AddRef()
{
  METHOD_PROLOGUE_EX_(CWorkspaceView, ObjectSafety)
  dprintf(DUMP, "cws CWorkspaceView::XObjectSafety::AddRef method call");
  return (ULONG)pThis->ExternalAddRef();
}

/////////////////////////////////////////////////////////////////////////////
// Release

STDMETHODIMP_(ULONG) CWorkspaceView::XObjectSafety::Release()
{
  METHOD_PROLOGUE_EX_(CWorkspaceView, ObjectSafety)
  dprintf(DUMP, "cws CWorkspaceView::XObjectSafety::Release method call");
  return (ULONG)pThis->ExternalRelease();
}

/////////////////////////////////////////////////////////////////////////////
// QueryInterface

STDMETHODIMP CWorkspaceView::XObjectSafety::QueryInterface (REFIID iid,
                                                            PVOID* ppvObj)
{
  METHOD_PROLOGUE_EX_(CWorkspaceView, ObjectSafety)
  dprintf(DUMP, "cws %s method call",
          "CWorkspaceView::XObjectSafety::QueryInterface");
  return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

#endif // L_IMPL_OBJECTSAFETY


/////////////////////////////////////////////////////////////////////////////
// GetActiveXStringProperty
//
// I don't like this implementation.  The macros USES_CONVERSION and T2OLE come
// from afxpriv.h, which is not really standard and has the contract that it
// can change in an incompatible way if Microsoft pleases.  It is also ugly to
// use weird things like USES_CONVERSION.  There has got to be a real, standard,
// preferably Win32 way to go from a PTSTR to a BSTR.  -jv, 1/17/04

BSTR CWorkspaceView::GetActiveXStringProperty (int ax_prop_id)
{
  USES_CONVERSION;
  return SysAllocString(T2OLE(m_Properties[ax_prop_id]));
}

/////////////////////////////////////////////////////////////////////////////
// SetActiveXStringProperty

void CWorkspaceView::SetActiveXStringProperty (int ax_prop_id,
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

BSTR CWorkspaceView::GetTwLocation ()
{
  dprintf(DUMP, "cws GetTwLocation method call");
  return GetActiveXStringProperty(GWVC_TW_LOCATION);
}

void CWorkspaceView::SetTwLocation (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "cws SetTwLocation method call");
  SetActiveXStringProperty(GWVC_TW_LOCATION, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchUserName and SetLaunchUserName - every "window" in G2 has an
// associated user-name and user-mode, and possibly a password.

BSTR CWorkspaceView::GetLaunchUserName ()
{
  dprintf(DUMP, "cws GetLaunchUserName method call");
  return GetActiveXStringProperty(GWVC_CL_USER_NAME);
}

void CWorkspaceView::SetLaunchUserName (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "cws SetLaunchUserName method call");
  SetActiveXStringProperty(GWVC_CL_USER_NAME, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchUserMode and SetLaunchUserMode - every "window" in G2 has an
// associated user-name and user-mode, and possibly a password.

BSTR CWorkspaceView::GetLaunchUserMode ()
{
  dprintf(DUMP, "cws GetLaunchUserMode method call");
  return GetActiveXStringProperty(GWVC_CL_USER_MODE);
}

void CWorkspaceView::SetLaunchUserMode (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "cws SetLaunchUserMode method call");
  SetActiveXStringProperty(GWVC_CL_USER_MODE, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchPassword and SetLaunchPassword - every "window" in G2 has an
// associated user-name and user-mode, and possibly a password.

BSTR CWorkspaceView::GetLaunchPassword ()
{
  dprintf(DUMP, "cws GetLaunchPassword method call");
  return GetActiveXStringProperty(GWVC_CL_PASSWORD);
}

void CWorkspaceView::SetLaunchPassword (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "cws SetLaunchPassword method call");
  SetActiveXStringProperty(GWVC_CL_PASSWORD, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetG2Gateway and SetG2Gateway

IUnknown *CWorkspaceView::GetG2Gateway ()
{
  return m_pUnk;
}

void CWorkspaceView::SetG2Gateway (IUnknown *p_pUnk)
{
  ConnectToG2Gateway(p_pUnk);
}


/////////////////////////////////////////////////////////////////////////////
// GetLaunchWindow and SetLaunchWindow

BSTR CWorkspaceView::GetLaunchWindow ()
{
  dprintf(DUMP, "cws GetLaunchWindow method call");
  return GetActiveXStringProperty(GWVC_CL_WINDOW_STYLE);
}

void CWorkspaceView::SetLaunchWindow (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "cws SetLaunchWindow method call");
  SetActiveXStringProperty(GWVC_CL_WINDOW_STYLE, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetWorkspaceName and SetWorkspaceName

BSTR CWorkspaceView::GetWorkspaceName ()
{
  dprintf(DUMP, "cws GetWorkspaceName method call");
  return GetActiveXStringProperty(GWVC_CL_WORKSPACE);
}

void CWorkspaceView::SetWorkspaceName (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "cws SetWorkspaceName to %s", pszNewValue);
  m_nothingToShow = FALSE;
  m_WorkspaceSpecification = GWVC_SHOW_BY_NAME;
  SetActiveXStringProperty(GWVC_CL_WORKSPACE, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetWorkspaceUUID and SetWorkspaceUUID

BSTR CWorkspaceView::GetWorkspaceUUID ()
{
  dprintf(DUMP, "cws GetWorkspaceUUID method call");
  return GetActiveXStringProperty(GWVC_CL_WORKSPACE_UUID);
}

void CWorkspaceView::SetWorkspaceUUID (LPCTSTR pszNewValue)
{
  dprintf(DUMP, "cws SetWorkspaceUUID to %s", pszNewValue);
  m_nothingToShow = FALSE;
  m_WorkspaceSpecification = GWVC_SHOW_BY_UUID;
  SetActiveXStringProperty(GWVC_CL_WORKSPACE_UUID, pszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// GetReconnect and SetReconnect - Reconnect doesn't suffer from the same
// problems as the other properties, because it is obvious it only has an
// effect when connecting to the Gateway.

BOOL CWorkspaceView::GetReconnect ()
{
  dprintf(DUMP, "cws GetReconnect method call");
  return m_reconnect;
}

void CWorkspaceView::SetReconnect (BOOL pReconnect)
{
  m_reconnect = pReconnect;
  SetModifiedFlag();
}



/////////////////////////////////////////////////////////////////////////////
// ShowWorkspace

void CWorkspaceView::ShowWorkspace (BSTR ws_to_show, BOOL uuid_p)
{
  long hwnd_as_long;
  long ix[1];
  BSTR proc_for_call;
  HRESULT hr;
  SAFEARRAY *psa;
  SAFEARRAYBOUND aDim[1];
  VARIANT varNextArg;
  VARIANT varRet;

  // The following code is cribbed from the OnDraw() method, above.  It should,
  // of course, be turned into a separate subfunction, which both use.  Adding
  // this code fixes bug HQ-4843500 "With two WorkspaceViews on two Forms, a
  // workspace is shown in the wrong WSV", and I am adding here (rather than
  // generalizing it above) in order to have the simplest fix, so we can have
  // a patch.  This code should be improved for the actual 8.0r1 release.
  // -jv, 7/26/04
  if (m_hWnd == (HWND) NULL) {
    m_hWnd = (HWND)GetHwnd();
    if (! ::IsWindow(m_hWnd)) {
      dprintf(DERROR, "%s  (0x%x)", NOT_AN_HWND_MSG, (unsigned long) m_hWnd);
      m_hWnd = (HWND)NULL;
    }
    if (m_hWnd == (HWND) NULL) {
      dprintf(DERROR, "Warning: even in ShowWorkspace, cannot obtain HWND.");
      dprintf(DERROR, "   Not calling ShowWorkspace!");
      return;
    } else {
      dprintf(PROGRESS, "got hwnd 0x%x from ShowWorkspace", (long) m_hWnd);
    }
  }

  if (ws_to_show == NULL) {
    // This should not happen; we should not be called if there is nothing to
    // show!!!
    dprintf(DERROR, "no workspace to show; returning");
    return;
  }
  dprintf(PROGRESS, "cws ws %d, ShowWorkspace \"%S\"", m_InstanceId, ws_to_show);

  proc_for_call = SysAllocString((uuid_p ?
                                  TWAXL_WS_UUID_PROCEDURE :
                                  TWAXL_WS_NAME_PROCEDURE));
  if (proc_for_call == NULL) {
    dprintf(DERROR, "Out of memory attempting to make a BSTR");
    return;
  }

  aDim[0].lLbound = 1;                // Lower bound of 1 -- weird
  aDim[0].cElements = 4;
  psa = SafeArrayCreate(VT_VARIANT, 1, aDim);
  if (psa == NULL) {
    dprintf(DERROR, "Out of memory attempting to make RPC to G2");
    SysFreeString(proc_for_call);  // maybe should use a goto?
    return;
  }

  if (!uuid_p) {
    // This modifies the argument in place, which is the string that WE received
    // as an argument.  We assume that the BSTR is going to be reclaimed as soon
    // as this function returns.  In any case, this is just a hack for 8.0a0.
    // In future releases, G2 should do the case-conversion; we should be able
    // to send it a text and have it pass it through the normal "reader" and
    // case it accordingly.  Since that's not there in 8.0a0, we upper-case it
    // here.  -jv, 1/26/04
    _wcsupr(ws_to_show);
  }
  m_child_hWnd = NULL;

  dprintf(PROGRESS, "going to try to call G2 procedure");

  // pack the SafeArray
  // -----------------------------------------------------
  VariantInit(&varNextArg);
  varNextArg.vt = VT_I4;
  varNextArg.lVal = m_SessionId;
  ix[0] = 1;
  SafeArrayPutElement(psa, ix, &varNextArg);
  VariantClear(&varNextArg);

  hwnd_as_long = (long) m_hWnd;
  VariantInit(&varNextArg);
  varNextArg.vt = VT_I4;
  varNextArg.lVal = HIWORD(hwnd_as_long);
  ix[0] = 2;
  SafeArrayPutElement(psa, ix, &varNextArg);
  VariantClear(&varNextArg);

  VariantInit(&varNextArg);
  varNextArg.vt = VT_I4;
  varNextArg.lVal = LOWORD(hwnd_as_long);
  ix[0] = 3;
  SafeArrayPutElement(psa, ix, &varNextArg);
  VariantClear(&varNextArg);

  VariantInit(&varNextArg);
  varNextArg.vt = VT_BSTR;
  varNextArg.bstrVal = ws_to_show;
  ix[0] = 4;
  SafeArrayPutElement(psa, ix, &varNextArg);
  VariantClear(&varNextArg);

  hr = m_gw->Call(proc_for_call, &psa, &varRet);
  if (FAILED(hr)) {
    dprintf(DERROR, "Show workspace call failed returned 0x%08.8lX", hr);
  } else {
    dprintf(PROGRESS, "Show workspace call succeeded");
    FindTwWindow();
  }

  // Free up the memory that we have used
  // ------------------------------------
  VariantClear(&varRet);
  SafeArrayDestroy(psa);
  SysFreeString(proc_for_call);
}


/////////////////////////////////////////////////////////////////////////////
// InitializeWorkspaceView

void CWorkspaceView::InitializeWorkspaceView ()
{
  BSTR ws_to_show;
  BOOL show_by_uuid = (m_WorkspaceSpecification == GWVC_SHOW_BY_UUID);

  if (NOT_CONNECTED_TO_TW) {
    dprintf(DERROR, "Can't call ShowWorkspace, do not have a session id yet.");
    return;
  }

  if (m_nothingToShow) {
    dprintf(DERROR, "ws %d, InitializeWorkspaceView, no workspace requested",
            m_InstanceId);
    return;
  }

  if (show_by_uuid) {
    ws_to_show = GetWorkspaceUUID();
  } else {
    ws_to_show = GetWorkspaceName();
  }

  // This should not happen; if there is no workspace to show, then
  // m_nothingToShow should have been true.
  if (ws_to_show == NULL) {
    dprintf(DERROR, "ws %d, no workspace to show; returning", m_InstanceId);
    m_nothingToShow = TRUE;
    return;
  }
  dprintf(PROGRESS, "attempting to show workspace %S", ws_to_show);

  ShowWorkspace(ws_to_show, show_by_uuid);
  SysFreeString(ws_to_show);
}


/////////////////////////////////////////////////////////////////////////////
// ObtainHostAndPort

BOOL CWorkspaceView::ObtainHostAndPort (BSTR location)
{
  unsigned len, colon, chr;

  // Note for printf, use capital S for BSTR / Unicode string
  dprintf(ALWAYS, "obtained location %S", location);
  len = SysStringLen(location);
  // I thought "colon" should be initialized to 1 here, because the length is
  // stored at the beginning, but apparently Microsoft has figured that out.
  for (colon=0; (colon<len) && (location[colon] != ':'); colon++) {
    // empty loop
  }
  if (colon == len) {
    dprintf(DERROR, "Could not break up %S into host and port", location);
    return FALSE;
  }

  // Copy from OLECHAR, which could be Unicode or ASCII and is determined only
  // at run-time, to ASCII.  Do it pedantically.
  m_Host = (char *) malloc(colon+1 * sizeof(char));
  for (chr=0; chr<colon; chr++) {
    m_Host[chr] = (char) location[chr];
  }
  m_Host[colon] = 0;
  dprintf(DUMP, "Obtained host %S", m_Host);

  m_Port = (char *) malloc((len-colon) * sizeof(char));
  for (chr=colon+1; chr<len; chr++) {
    m_Port[chr-colon-1] = (char) location[chr];
  }
  m_Port[len-colon-1] = 0;
  dprintf(DUMP, "Obtained port %S", m_Port);

  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// RunTwNowOrDeferred - attempts to obtain the host and port from the gateway,
// and find our HWND, and then either starts up TW if succeeded, or sets a
// variable which will cause TW to be started as soon as we do get the HWND.

HRESULT CWorkspaceView::RunTwNowOrDeferred ()
{
  BSTR location;
  BOOL gotHostAndPort;
  HRESULT hr;

  dprintf(DUMP, "cws RunTwNowOrDeferred method call");

  hr = m_gw->get_G2Location(&location);
  if (FAILED(hr)) {
    dprintf(DERROR, "could not obtain location information from AxL");
    return hr;
  }
  gotHostAndPort = ObtainHostAndPort(location);
  SysFreeString(location);

  if (!gotHostAndPort) {
    // Should investigate HRESULTs and see if there's a more appropriate one to
    // use here than the very generic E_FAIL.
    return E_FAIL;
  }

  if (m_hWnd != (HWND) NULL) {
    dprintf(DETAIL, "already had hwnd 0x%x", (long) m_hWnd);
  } else {
    m_hWnd = (HWND)GetHwnd();
  }

  // Now, check if the GetHwnd succeeded...
  if (m_hWnd == (HWND) NULL) {
    m_startTWAfterDraw = TRUE;
    dprintf(DERROR, "Warning: could not obtain HWND; delaying starting TW");
  } else {
    m_startTWAfterDraw = FALSE;
    StartTwInHwnd();
  }
  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// DisconnectFromTW

LRESULT CWorkspaceView::DisconnectFromTW ()
{
  HRESULT hr;
  int old_session = m_SessionId;

  m_nothingToShow = TRUE;
  m_SessionId = GWVC_NO_TW_SESSION;
  theApp.SetSessionId(this, m_SessionId);
  theApp.BroadcastTWShutdown(m_gw, old_session);
  m_gw->ClearTWLock();
  hr = m_gw->put_TWHandle(0);
  dprintf(PROGRESS, "ws %d, disconnecting TW from gateway; result = %d",
          m_InstanceId, hr);
  return (LRESULT) 0;
}


/////////////////////////////////////////////////////////////////////////////
// NoteTWShutdown

void CWorkspaceView::NoteTWShutdown (AXL_IFACE *p_gw, int p_SessionId)
{
  if ((p_gw == m_gw) && (p_SessionId == m_SessionId)) {
    dprintf(PROGRESS, "ws %d, TW has shut down", m_InstanceId);
    m_nothingToShow = TRUE;
    m_SessionId = GWVC_NO_TW_SESSION;
    theApp.SetSessionId(this, m_SessionId);
  }
}


/////////////////////////////////////////////////////////////////////////////
// NoteTWConnection

void CWorkspaceView::NoteTWConnection (AXL_IFACE *p_gw, int p_SessionId)
{
  if ((m_gw != NULL) && (m_gw == p_gw) && NOT_CONNECTED_TO_TW) {
    m_SessionId = p_SessionId;
    theApp.SetSessionId(this, m_SessionId);
    dprintf(PROGRESS, "ws %d, got session id %d from theApp",
            m_InstanceId, m_SessionId);
    if (m_hWnd == (HWND) NULL) {
      m_hWnd = (HWND)GetHwnd();
    }
    if (m_hWnd == (HWND) NULL) {
      dprintf(DERROR, "ws %d, no hwnd", m_SessionId);
    } else {
      InitializeWorkspaceView();
    }
  }
}


/////////////////////////////////////////////////////////////////////////////
// ReceiveTWProcId

void CWorkspaceView::ReceiveTWProcId (HANDLE p_pid)
{
  m_hProcess = p_pid;
}


/////////////////////////////////////////////////////////////////////////////
// RunOrConnectToTW

HRESULT CWorkspaceView::RunOrConnectToTW ()
{
  VARIANT_BOOL obtained_lock = VARIANT_FALSE;
  long session_id = 0;

  // assert (! m_nothingToShow)
  // assert (NOT_CONNECTED_TO_TW)
  if (m_gw == NULL) {
    dprintf(DERROR, "ws %d cannot run or connect to TW, no m_gw",
            m_InstanceId);
    return E_FAIL;
  }
  // don't bother with hr here, method always returns S_OK
  m_gw->ObtainTWLockIfUnused(&obtained_lock);

  if (obtained_lock) {
    dprintf(PROGRESS, "ws %d, obtained lock -- tw is not running!",
            m_InstanceId);
    return RunTwNowOrDeferred();
  }

  dprintf(PROGRESS, "ws %d doesn't have lock to run tw; waiting for a session id",
          m_InstanceId);

  m_gw->get_TWHandle(&session_id);
  if (session_id < GWVC_LOWEST_VALID_TW_SESSION) {
    // RACE CONDITION!!!  We should, at this point, perhaps begin polling, and
    // continue when (and only when) we get a session id.  Instead, we give up
    // for now, and try again when OnDraw is next called.  This will need to
    // improve post-Alpha.
    dprintf(PROGRESS, "ws %d cannot start, do not have a session id yet",
            m_InstanceId);
  } else {
    m_SessionId = session_id;
    theApp.SetSessionId(this, m_SessionId);
    dprintf(PROGRESS, "ws %d, AxL set session id to %d",
            m_InstanceId, m_SessionId);
    InitializeWorkspaceView();
  }
  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// ConnectToG2Gateway -- purely a user method.  Our code never calls this
// directly.

HRESULT CWorkspaceView::ConnectToG2Gateway (IUnknown *gateway_object)
{
  HRESULT hr;
  AXL_IFACE *gw_if = (AXL_IFACE *) NULL;

  dprintf(DUMP, "cws ConnectToG2Gateway method call");
  m_SessionId = GWVC_NO_TW_SESSION;
  theApp.SetSessionId(this, m_SessionId);

  if (gateway_object == (IUnknown *) NULL) {
    dprintf(DERROR, "Received NULL IUnknown object");
    return E_INVALIDARG;
  }

  hr = gateway_object->QueryInterface(AXL_IFACE_IID, (void **) &gw_if);
  if (FAILED(hr)) {
    dprintf(DERROR, "Unable to obtain %s interface", AXL_IFACE_NAME_AS_STRING);
    if (hr == E_NOINTERFACE) {
      dprintf(DERROR, "The IUnknown pointer we received does not support %s",
              AXL_IFACE_NAME_AS_STRING);
    } else {
      // I guess here I should call that standard function that takes an HRESULT
      // and returns an error message, but I'm too lazy for the moment.
      dprintf(DERROR, "Some unexpected error, 0x%x, occurred", (unsigned int) hr);
    }
    return E_INVALIDARG;
  }
  dprintf(PROGRESS, "ws %d got %s interface!!!", m_InstanceId,
          AXL_IFACE_NAME_AS_STRING);
  m_gw = gw_if;
  theApp.SetGateway(this, m_gw);

  if (m_nothingToShow) {
    return S_OK;
  }

  RunOrConnectToTW();
  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// ShowWorkspaceWithName

HRESULT CWorkspaceView::ShowWorkspaceWithName (LPCTSTR workspace_name)
{
  dprintf(PROGRESS, "ws %d wants to see name %s", m_InstanceId, workspace_name);
  SetWorkspaceName(workspace_name);
  if (NOT_CONNECTED_TO_TW) {
    RunOrConnectToTW();
  } else {
    BSTR ws_name = GetWorkspaceName();
    ShowWorkspace(ws_name, FALSE);
    SysFreeString(ws_name);
  }
  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// ShowWorkspaceWithUUID

HRESULT CWorkspaceView::ShowWorkspaceWithUUID (LPCTSTR workspace_uuid)
{
  dprintf(PROGRESS, "ws %d wants to see uuid %s", m_InstanceId, workspace_uuid);
  SetWorkspaceUUID(workspace_uuid);
  if (NOT_CONNECTED_TO_TW) {
    RunOrConnectToTW();
  } else {
    BSTR ws_uuid = GetWorkspaceUUID();
    ShowWorkspace(ws_uuid, TRUE);
    SysFreeString(ws_uuid);
  }
  return S_OK;
}

BOOL CWorkspaceView::GetVersion (LPTSTR szVer)
{
  BYTE *pbData = NULL;
  DWORD dwLen = 0;
  TCHAR szFullPath[MAX_PATH] = {0};
  DWORD dwHandle = 0;
  BOOL bRet = FALSE;
  UINT uiSize = 0;
  VS_FIXEDFILEINFO* pFFI;
  UINT uiProduct, uiVersion, uiSubVersion, uiBuild;
  uiProduct = uiVersion = uiSubVersion = uiBuild = 0;
  TCHAR szTwPath[MAX_PATH] = {0};

  // first, get our module name
  if (!GetModuleFileName(AfxGetInstanceHandle(), szFullPath, MAX_PATH)) {
    return FALSE;
  }

  // get size of buffer needed
  dwLen = GetFileVersionInfoSize(szFullPath, &dwHandle);

  // allocate the receiving buffer
  pbData = new BYTE[dwLen];
  ZeroMemory(pbData, dwLen);

  // fill the buffer
  if (GetFileVersionInfo(szFullPath, NULL, dwLen*sizeof(TCHAR), (LPVOID) pbData)) {
    uiSize = sizeof(pFFI);
    VerQueryValue(pbData, TEXT("\\"), (LPVOID*)&pFFI, &uiSize);

    uiProduct = HIWORD(pFFI->dwProductVersionMS);
    uiVersion = LOWORD(pFFI->dwProductVersionMS);
    uiSubVersion = HIWORD(pFFI->dwProductVersionLS);
    uiBuild = LOWORD(pFFI->dwProductVersionLS);

    bRet = FindTwPath(szTwPath, uiProduct, uiVersion, uiSubVersion);
  }
  else {
    bRet = FALSE;
  }

  // deallocate
  delete [] pbData;
  pbData = NULL;

  _tcscpy(szVer, szTwPath);
  return bRet;
}


BOOL CWorkspaceView::ParseRegKeyName (LPCTSTR szRegKey, UINT &uiMajor,
                                      UINT &uiMinor, UINT &uiRev)
{
  TCHAR sepPeriod[] = TEXT(".");
  TCHAR sepSpace[] = TEXT(" ");
  TCHAR *token = NULL;
  TCHAR szTemp[MAX_REGKEY_LEN] = {0};

  _tcscpy(szTemp, szRegKey);

  // parse out major version delimited by '.'
  token = _tcstok(szTemp, sepPeriod);
  if (token) {
    uiMajor = _ttoi(token);
  }
  else {
    return FALSE;
  }

  // parse out minor version delimited by ' '
  token = _tcstok(NULL, sepSpace);
  if (token) {
    uiMinor = _ttoi(token);
  }
  else {
    return FALSE;
  }

  // parse out the revision
  token = _tcstok(NULL, sepPeriod);
  token = _tcstok(NULL, sepSpace);
  if (token) {
    // TODO: take out any spaces??
    uiRev = _ttoi(token);
  }
  else {
    return FALSE;
  }

  return TRUE;
}


// Returns:
//  -1 if vi1 is > vi2
//  0 if vi1 = vi2
//  1 if vi1 is < vi2
int CWorkspaceView::CompareVersions (LPVERINFO vi1, LPVERINFO vi2)
{
  if (vi1->uiMajor > vi2->uiMajor) {
    return (-1);
  }
  else if (vi1->uiMajor < vi2->uiMajor) {
    return (1);
  }

  // major versions are equal, so now let's look
  // at the minor version
  if (vi1->uiMinor > vi2->uiMinor) {
    return (-1);
  }
  else if (vi1->uiMinor < vi2->uiMinor) {
    return (1);
  }

  // minor versions are equal, so now let's look
  // at the revision number
  if (vi1->uiRev > vi2->uiRev) {
    return (-1);
  }
  else if (vi1->uiRev < vi2->uiRev) {
    return (1);
  }
  else {
    // versions are equal
    return (0);
  }
}


BOOL CWorkspaceView::UpdateLatestVersionInfo (LPVERINFO vi, UINT uiMajor,
                                              UINT uiMinor, UINT uiRev,
                                              LPTSTR szRegKeyName)
{
  VERINFO vi2;
  ZeroMemory(&vi2, sizeof(VERINFO));
  vi2.uiMajor = uiMajor;
  vi2.uiMinor = uiMinor;
  vi2.uiRev = uiRev;
  _tcscpy(vi2.szRegKeyName, szRegKeyName);

  if (CompareVersions(vi, &vi2)) {
    // replace contents of vi
    vi->uiMajor = uiMajor;
    vi->uiMinor = uiMinor;
    vi->uiRev = uiRev;
    ZeroMemory(vi->szRegKeyName, MAX_PATH);
    _tcscpy(vi->szRegKeyName, szRegKeyName);
  }

  return TRUE;
}


BOOL CWorkspaceView::FindTwPath (LPTSTR szTwPath, UINT uiVersion,
                                 UINT uiSubVersion, UINT uiBuild)
{
  HKEY hKey = NULL;
  int i = 0;
  TCHAR szBuffer[MAX_PATH] = {0};
  UINT uiMajor, uiMinor, uiRev;
  uiMajor = uiMinor = uiRev = 0;
  BOOL bRet = FALSE;
  int nCompare = 0;
  VERINFO vi1;
  ZeroMemory(&vi1, sizeof(VERINFO));
  BOOL bFound = FALSE;

  // for keeping track of latest version found
  VERINFO vi;
  ZeroMemory(&vi, sizeof(VERINFO));
  vi.uiMajor = vi.uiMinor = vi.uiRev = -1;

  // open the TW registry key
  if (ERROR_SUCCESS !=
      RegOpenKeyEx(HKEY_LOCAL_MACHINE, GWVC_TELEWINDOWS_KEY, 0, KEY_READ, &hKey))
  {
    return FALSE;
  }

  // enum through the subkeys
  for (i = 0; RegEnumKey(hKey, i, szBuffer, sizeof(szBuffer)) == 0; i++) {
    if (!ParseRegKeyName(szBuffer, uiMajor, uiMinor, uiRev)) {
      RegCloseKey(hKey);
      return FALSE;
    }

    // keep latest version found
    UpdateLatestVersionInfo(&vi, uiMajor, uiMinor, uiRev, szBuffer);
    if (!bFound) {
      bFound = TRUE;
    }

/*  NOTE:  keep this around in case they want to try to exactly match
    versions!

    // if we have a match, extract the full path exe and return it
    if ( (uiVersion == uiMajor) &&
         (uiSubVersion == uiMinor) &&
         (uiBuild == uiRev) ) {

      // retrieve the install dir
      if (GetInstallDir(hKey, szBuffer, (LPBYTE)szTwPath)) {
        bRet = TRUE;
        break;
      }
      else {
        bRet = FALSE;
      }
    }
    else {
      bRet = FALSE;
    }
*/
  }

  // did we find at least one occurrence?
  if (bFound) {
    vi1.uiMajor = uiVersion;
    vi1.uiMinor = uiSubVersion;
    vi1.uiRev = uiBuild;

    // did we exactly match versions?
    nCompare = CompareVersions(&vi1, &vi);
    if (nCompare != 0) {
      // no, so log it
      dprintf(PROGRESS, "Version comparison does not result in exact match!");
    }

    if (GetInstallDir(hKey, vi.szRegKeyName, (LPBYTE)szTwPath)) {
      bRet = TRUE;
    }
  }

  RegCloseKey(hKey);
  return bRet;
}


BOOL CWorkspaceView::GetInstallDir (HKEY hKey, LPTSTR szSubKey,
                                    LPBYTE szInstallDir)
{
  HKEY hSubKey = NULL;
  BOOL bRet = FALSE;
  DWORD dwInstallDirLen = MAX_PATH;

  // open the subkey
  if (ERROR_SUCCESS == RegOpenKeyEx(hKey, szSubKey, 0, KEY_READ, &hSubKey)) {
    // now query the installDir value
    if (ERROR_SUCCESS ==
        RegQueryValueEx(hSubKey, GWVC_DIR_VALUE, NULL, NULL,
			(LPBYTE)szInstallDir, &dwInstallDirLen))
    {
       RegCloseKey(hSubKey);
       bRet = TRUE;
    }
  }

  return bRet;
}
