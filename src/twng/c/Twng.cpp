// Twng.cpp : Defines the class behaviors for the application.

#include "stdafx.h"
#include "Twng.h"
#include "NativeView.h"
#include "WorkspaceView.h"
#include "HtmlView.h"
#include "TreeView.h"
#include "ShortcutBar.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include <crtdbg.h>  // For _CrtSetReportMode

void myInvalidParameterHandler(const wchar_t* expression,
   const wchar_t* function, 
   const wchar_t* file, 
   unsigned int line, 
   uintptr_t pReserved)
{
   wprintf(L"Invalid parameter detected in function %s."
            L" File: %s Line: %d\n", function, file, line);
   wprintf(L"Expression: %s\n", expression);
}

BEGIN_MESSAGE_MAP(CTwngApp, CWinApp)
  ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
  ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

static int exit_instance_rc = 0; // Return code from MFC ExitInstance.
BOOL g_print_menu_on_custom_dialog = FALSE;

/*
 * Utilities
 */

/* Convert a wide string to a "T" string. */
LPTSTR TStr(LPWSTR str)
{
#ifdef UNICODE
  return str;
#else
  static char buf[500];
  wcstombs(buf, str, 499);
  return buf;
#endif
}

/* Convert a "T" string to a wide string. */
LPWSTR WStr(LPCTSTR str)
{
#ifdef UNICODE
  return (LPWSTR)str;
#else
  static wchar_t buf[500];
  mbstowcs(buf, str, 499);
  buf[499] = L'\0';
  return buf;
#endif
}

/* Return the TW command line as a char*, and without the program name. */
char *get_tw_cmdline(void)
{
  char *buf;
  LPCTSTR line = GetCommandLine();
  LPCTSTR tail = (line[0] == '"') ? _tcschr(line+1,'"')+1 : _tcschr(line,' ');
  UINT lenOfCommandLineStr = _tcslen(line) * sizeof(TCHAR);
  // GENSYMCID-807: TWNG cannot connect to G2 Server without arguments in CMD window
  if (tail == NULL)
    return "";
  buf = new char[lenOfCommandLineStr];
  memset(buf, 0, lenOfCommandLineStr);
#ifdef UNICODE
  tail = tail ? (wcslen(tail) > 0 ? tail + 1 : tail) : line;
  wcstombs(buf, tail, lenOfCommandLineStr);
#else
  tail = tail ? (strlen(tail) > 0 ? tail + 1 : tail) : line;
  strncpy(buf, (char *)tail, lenOfCommandLineStr);
#endif
  return buf;
}

/* GENSYMCID-1215: twng locks up (workaround) */
static int g_refresh_maximized_window_interval = -1;
static int g_last_user_action_timestamp = 0;
static int g_record_user_action_per_count = 10;
static int g_user_action_count = 0;

static int g2pvt_get_last_user_action_timestamp()
{
  return g_last_user_action_timestamp;
}

static void g2pvt_capture_user_action_timestamp()
{
  g_last_user_action_timestamp = time(NULL);
}

// icon path of workspace view window
static std::wstring workspaceViewIconPath;

std::wstring Twng_GetWorkspaceViewIconPath() {
  return workspaceViewIconPath;
}

static bool logbookDisabled = false;

bool Twng_LogbookDisabled() {
  return logbookDisabled;
}

static bool messageBoardDisabled = false;

bool Twng_MessageBoardDisabled() {
  return messageBoardDisabled;
}

void parse_twng_cmdline ()
{
  for (int i = 0; i < __argc; i++) {
    if ((0 == _tcscmp(__targv[i], _T("/print-menu-on-custom-dialog"))) ||
	(0 == _tcscmp(__targv[i], _T("-print-menu-on-custom-dialog")))) {
      // GENSYMCID-943: Print menu on custom dialog
      g_print_menu_on_custom_dialog = TRUE;
      break;
    }
    // GENSYMCID-1215: twng locking up (workaround)
    if ((0 == _tcscmp(__targv[i], _T("/auto-refresh-maximized-window"))) ||
        (0 == _tcscmp(__targv[i], _T("-auto-refresh-maximized-window")))) {
      if (i + 1 >= __argc) continue;
      // check if the next argument is integer, convert the string to integer
      int v = 0;
      for (int j = 0; j < _tcslen(__targv[i + 1]); j++) {
        int c = (int)__targv[i + 1][j];
        if (c >= 48 && c <= 57)
          v = v * 10 + c - 48;
        else {
          // next argument is not integer, return -1 then
          v = -1;
          break;
        }
      }
      g_refresh_maximized_window_interval = v;
    }
    if ((0 == _tcsicmp(__targv[i], _T("/ws-icon"))) ||
        (0 == _tcsicmp(__targv[i], _T("-ws-icon")))) {
      if (i + 1 < __argc)
        workspaceViewIconPath = __targv[i + 1];
    }
    if ((0 == _tcsicmp(__targv[i], _T("/no-logbook"))) ||
        (0 == _tcsicmp(__targv[i], _T("-no-logbook")))) {
      logbookDisabled = true;
    }
    if ((0 == _tcsicmp(__targv[i], _T("/no-message-board"))) ||
        (0 == _tcsicmp(__targv[i], _T("-no-message-board")))) {
      messageBoardDisabled = true;
    }
    if ((0 == _tcsicmp(__targv[i], _T("/clean"))) ||
        (0 == _tcsicmp(__targv[i], _T("-clean")))) {
      logbookDisabled = true;
      messageBoardDisabled = true;
    }
  }
}

int GetCommonControlsVersion()
{
  static int version = -1;

  if(version < 0) {
    HINSTANCE hMod = LoadLibrary(_T("comctl32.dll"));
    version = 4;
    if(hMod) {
      DLLGETVERSIONPROC pProc = (DLLGETVERSIONPROC) GetProcAddress(hMod, "DllGetVersion");
      if(pProc) {
	DLLVERSIONINFO dvi = {0};
	dvi.cbSize = sizeof(DLLVERSIONINFO);
	(*pProc)(&dvi);
	version = dvi.dwMajorVersion;
      }
      FreeLibrary(hMod);
    }
  }
  return version;
}

/*
 * Dummy Document Class
 */

class CDummyDoc : public CDocument
{
public:
 DECLARE_DYNCREATE(CDummyDoc)
 CDummyDoc();
 virtual ~CDummyDoc();
};
IMPLEMENT_DYNCREATE(CDummyDoc, CDocument)
CDummyDoc::CDummyDoc() {}
CDummyDoc::~CDummyDoc() {}


/*
 * MFC Application object
 */

CTwngApp theApp;

CTwngApp::CTwngApp() {}

BOOL CTwngApp::InitInstance()
{
  InitCommonControls();		// I think MFC does this for us.
  CWinApp::InitInstance();

  SetRegistryKey(_T("Gensym"));	// HKEY_CURRENT_USER\Software\Gensym\Telewindows\...
  // LoadStdProfileSettings(4);	// Useless

  // We seem to need this, even though we currently never create a document or
  // view. Doc/view will be useful later for splitter windows.

  // Note that G2WorkspaceView is actually a CFrameWnd not a CView.

  m_pDocTemplateWorkspace = new CMultiDocTemplate(IDR_TwngTYPE, 
						  RUNTIME_CLASS(CDummyDoc),
						  RUNTIME_CLASS(G2WorkspaceView),
						  RUNTIME_CLASS(CView));
  AddDocTemplate(m_pDocTemplateWorkspace);

  // Parse command-line arguments.
  g2ext_app_init(AfxGetInstanceHandle(), get_tw_cmdline(), "TWNG");
  parse_twng_cmdline();

  // GENSYMCID-1215: twng locks up (workaround)
  SetUpMWMonitorTimer();

  // TODO: Create SDI frame if -ui standard
  CMainFrame* pMainFrame = new CMainFrame;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
    return FALSE;
  m_pMainWnd = pMainFrame;

  // TODO: Obey -no-window

  // Tell libcprim what windows to use.
  g2ext_app_set_windows(pMainFrame->m_hWnd, pMainFrame->m_hWndMDIClient);

  _invalid_parameter_handler oldHandler, newHandler;
  newHandler = myInvalidParameterHandler;
  oldHandler = _set_invalid_parameter_handler(newHandler);

  // Disable the message box for assertions.
  _CrtSetReportMode(_CRT_ASSERT, 0);

  return TRUE;
}

int CTwngApp::Run()
{
  g2ext_app_run();		// Enter TW scheduler. Calls EventCycle() periodically.
  return exit_instance_rc;
}


/* When the dialog inside a MDI child destroys itself, the wndproc for "gensym
 * forms" then destroys the form window, too, via WM_PARENTNOTIFY (in mdi.c).
 * In Twng, the form window is attached to a MFC CChildFrm. It seems that
 * destroying the HWND attached to a CFrame does _not_ affect the frame in any
 * way; it just sits around with this now invalid m_hWnd slot, which causes an
 * ASSERT failure down inside the OnIdle handler for CWinThread. So we clean up
 * these broken frames before CWinApp::OnIdle() gets a chance to run.  This is a
 * kludge until we can make MDI child dialogs the right way, out of CFormView's
 * or something like them. -fmw, 22May04 */

void CTwngApp::CleanupDialogs(void)
{
  CFrameWnd *pFrame, *pNext;
  AFX_MODULE_THREAD_STATE* pState = _AFX_CMDTARGET_GETSTATE()->m_thread;

  /* The loop here is copied from CWinThread::OnIdle(). It seems that our
   * half-dead MDI child dialog frames are still on the m_frameList, even though
   * they are no longer windows, and so don't appear in a GetWindow()-style
   * loop. */

  for(pFrame=pState->m_frameList; pFrame; pFrame=pNext) {
    pNext = pFrame->m_pNextFrameWnd;
    if(pFrame->IsKindOf(RUNTIME_CLASS(CChildFrm)) &&
       pFrame->m_hWnd &&
       (!IsWindow(pFrame->m_hWnd))) {

      VTRACE("CleanupDialogs %08X\n", pFrame);

      pFrame->Detach();
      delete pFrame;
    }
  }
}

BOOL CTwngApp::OnIdle(LONG lCount)
{
  CleanupDialogs();
  return CWinApp::OnIdle(lCount);
}

static BOOL was_paint = FALSE;

/* Copied from CWinThread::Run() Returns msgcode or -1 on error.
 *
 * If we are inside a simple RPC, only get and dispatch ICP (WSA_NETEVENT) and
 * WM_PAINT events. This is to prevent arbitrary UI code from running inside of
 * the RPC, for example, XTP attempting to post a menu while within posting a
 * menu. -fmw, 1/12/05 */

int CTwngApp::EventCycle(int opcode, MSG* pMsg)
{
  static BOOL bIdle = TRUE;
  static LONG lIdleCount = 0;
  BOOL peek = FALSE;

  switch(opcode) {
   case 0:			// Wait
     while (bIdle && !(peek = ::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))) {
       if (!OnIdle(lIdleCount++))
         bIdle = FALSE;
     }
     if(!peek)			// If Peek has already seen a message, WaitMessage won't.
       ::WaitMessage();
     return 0;
     
   case 1:			// Peek
     was_paint = FALSE;
     if(!Inside_simple_rpc)
       peek = PeekMessage(&m_msgCur, NULL, 0, 0, PM_NOREMOVE);
     else {
       peek = PeekMessage(&m_msgCur, NULL, WSA_NETEVENT, WSA_NETEVENT, PM_NOREMOVE);
       if(!peek)
         was_paint = peek = PeekMessage(&m_msgCur, NULL, WM_PAINT, WM_PAINT, PM_NOREMOVE);
     }
     pMsg->message = m_msgCur.message;
     // GENSYMCID-1215: twng locks up (workaround)
     if (pMsg->message < WM_USER) {
       // avoiding performance overhead
       switch (pMsg->message) {
         // Mouse actions
         case WM_MOUSEWHEEL:
         case WM_LBUTTONDOWN:
         case WM_MBUTTONDOWN:
         case WM_RBUTTONDOWN:
         case WM_LBUTTONUP:
         case WM_MBUTTONUP:
         case WM_RBUTTONUP:
         case WM_LBUTTONDBLCLK:
         case WM_MBUTTONDBLCLK:
         case WM_RBUTTONDBLCLK:
         case WM_MOUSEMOVE:
         case WM_MOUSEHOVER:
         // Keyboard actions
         case WM_CHAR:
         case WM_SYSCHAR:
         case WM_SYSKEYDOWN:
         case WM_KEYDOWN:
		   g_user_action_count++;
		   if (g_user_action_count > g_record_user_action_per_count) {
		     // avoiding performance overhead
		     g_user_action_count = 0;
		     g2pvt_capture_user_action_timestamp();
		   }
	   }
	 }
     return peek;

   case 2:			// Pump
     if (!PumpMessage()) {
       exit_instance_rc = ExitInstance();
       // g2pvt_trace("ExitInstance returned: %d\n", exit_instance_rc);
       return -1;
     }

     // Reset "no idle" state after pumping "normal" message
     if (IsIdleMessage(&m_msgCur)) {
       bIdle = TRUE;
       lIdleCount = 0;
     }
     return m_msgCur.message;
  }
  return -1;
}

// GENSYMCID-1215: twng locks up
// Create timer for monitor when g_refresh_maximized_window_interval is not -1

void CTwngApp::SetUpMWMonitorTimer()
{
  if (g_refresh_maximized_window_interval != -1)
    m_nMWMonitorTimer = SetTimer(NULL, CTwngApp::MWMonitorTimerID, 1000 * g_refresh_maximized_window_interval, &CTwngApp::MWMonitorProc);
}

void CALLBACK CTwngApp::MWMonitorProc(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime)
{
  if (g_refresh_maximized_window_interval == -1)
    return;
  int last_user_action_timestamp = g2pvt_get_last_user_action_timestamp();
  int cur_timestamp = time(NULL);
  if (g_refresh_maximized_window_interval < (cur_timestamp - last_user_action_timestamp)) {
    fixing_twng_locks_up();
    g2pvt_capture_user_action_timestamp();
  }
}

/* Get and dispatch a message, maybe with message filtering.
 * Partly copied from CWinThread::PumpMessage() */
BOOL CTwngApp::PumpMessage()
{
  BOOL rc;

  if(! Inside_simple_rpc)
    rc = ::GetMessage(&m_msgCur, NULL, 0, 0);

  else if(was_paint)
    rc = ::GetMessage(&m_msgCur, NULL, WM_PAINT, WM_PAINT);

  else
    rc = ::GetMessage(&m_msgCur, NULL, WSA_NETEVENT, WSA_NETEVENT);

  if(!rc)
    return FALSE;

  if (m_msgCur.message != WM_KICKIDLE && !PreTranslateMessage(&m_msgCur)) {
    ::TranslateMessage(&m_msgCur);
    ::DispatchMessage(&m_msgCur);
  }

  return TRUE;
}

#if defined(_MFC_VER)&&_MFC_VER>=0x0900//VS2008 MFC and more		
MSG& CTwngApp::get_m_msgCur()
{
	return AfxGetThreadState()->m_msgCur;
}
#endif

/*
 * Called from TW
 */

int g2pvt_wait_message(void)
{
  return theApp.EventCycle(0,NULL);
}

int g2pvt_peek_message(MSG* pMsg)
{
  return theApp.EventCycle(1,pMsg);
}

int g2pvt_pump_message(MSG* pMsg)
{
  return theApp.EventCycle(2,pMsg);
}

// Ensures that we have a permanent MFC object for hwnd.
HWND g2pvt_bless_mdi_child(HWND hwnd, int handle)
{
  CFrameWnd *pFrame = new CChildFrm(handle);
  pFrame->Attach(hwnd);
  return hwnd;
}

/*
 * Dialog Panes
 */

int g2pvt_show_dialog_in_pane(HWND hwndDlg, int handle,
			      int x, int y, int width, int height,
			      int dock, int neighborID, int icon)
{
  CMainFrame *pFrame = GetMainWnd();
  CWnd *pDlg = CWnd::FromHandlePermanent(hwndDlg);

  if(!pDlg) return -1;

  ::SetWindowLong(hwndDlg, GWL_STYLE, WS_CHILD); // As in g2pvt_create_mdi_child_dialog()
  ::SetWindowLong(hwndDlg, GWL_EXSTYLE, WS_EX_CONTROLPARENT | WS_EX_CLIENTEDGE);
  ::SetWindowPos(hwndDlg, HWND_BOTTOM, 0,0,0,0,
		 SWP_NOACTIVATE|SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOZORDER|SWP_NOSIZE);
  CSize min_size(0, 0);
  pFrame->WrapWnd(pDlg, handle, x, y, width, height, dock, neighborID, min_size, nullptr, icon);
  return 1;
}

/* Called when a CDynamicDlg is being destroyed. If the dialog is inside a pane,
 * first destroy the pane. */
void g2pvt_destroy_containing_pane_if_any(HWND hwnd, int handle)
{
  CMainFrame *pFrame = GetMainWnd();
  CXTPDockingPaneManager *pMgr = pFrame->GetDockingPaneManager();
  CXTPDockingPane *pPane = g2pvt_find_pane(handle);

  // This works around a bad interaction between dialog navigation, parent
  // windows, and CXTPPropertyGrid's.

  // Once we've destroyed our pane, our parent seems to become the main
  // frame. When CXTPPropertyGrid::GetNextGridTabItem() walks parent links, it
  // then tries to use GetNextDlgTabItem on the main frame, which leads to an
  // infinite loop.

  // The workaround is to turn off this dialog's WS_EX_CONTROLPARENT bit
  // here. Since we're being destroyed, it isn't needed.
  CWnd::FromHandle(hwnd)->ModifyStyleEx(WS_EX_CONTROLPARENT, 0);

  if(pPane)
    pMgr->DestroyPane(pPane);

  HICON hIcon = CWnd::FromHandle(hwnd)->GetIcon(FALSE);
  if(hIcon && DestroyIcon(hIcon))
	CWnd::FromHandle(hwnd)->SetIcon(NULL, FALSE);
}
