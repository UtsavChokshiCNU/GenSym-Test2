/* -*- Mode: C -*-
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Module msmain -- note that this file is somewhat misnamed!
 *
 * This module contains Microsoft specific routines, but does not actually
 * contain a function called WinMain(), which is the entry point for Windows
 * executables.  However, it contains all of the actual functionality for
 * our WinMain function in the function g2ext_gensym_winmain.
 *
 * Pre 8-93: Richard Haggard, Kamal Bijlani
 *
 * mpc 8-13-93: In an effort to bring back the forked PC TW code,
 *     this file was created to hold the windows main functions,
 *     windows callback functions, and their exclusive support
 *     functions.
 *
 * mhd 12-1-99 (& past several months) - Unicode and IME event
 *     support.
 */

/*************************************************************************/
/* INCLUDES                                                              */
/*************************************************************************/
#ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x400
#endif

#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <malloc.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <locale.h>

#include "cprim.h"
#include "graphics.h"
#include "msincls.h"

#include "networks.h"
#include "netevent.h"


/*************************************************************************/
/* GLOBAL VARIABLES                                                      */
/*************************************************************************/

/* Maximum number of command line arguments to support */
#define MAX_ARGS 100

/* Registry Information */
#define TELEWINDOWS_KEY          "SOFTWARE\\Gensym\\Telewindows"
#define KEY_VALUE_NAME_TWNG      "installDir"
#define KEY_VALUE_NAME_ORIG      "installDirClassic"
#define TW_CLASS_ID              "{BEBC23AE-67A8-44AC-86AA-C9C5F059E08F}"
#define PATH_SEPARATOR_AS_CHAR   '\\'

#define SHUT_DOWN_QUESTION "Completely shut down G2?\nAny unsaved changes to your kb will be lost."


HPALETTE GensymPalette;               /* Handle to the color palette. */
HFONT MenuFont = NULL;                /* Cached handle to system menu font. */
int screenlock = FALSE;               /* Turns off the system menu. */
FILE *g2pvt_outstream = NULL;
HANDLE g2pvt_mutex = NULL;	      /* For licensing races. */

HWND parent_GhwndWin = NULL;    /* Will parent our window to this window if
                                   specified on startup, via the -WINDOWHANDLE
                                   command-line option. */

HKL default_hkl;

#define MOVE_RESIZE_TIMER_ID 624
static int g2pvt_move_resize_timeout = 0; /* milliseconds, 0 disables (infinite timeout) */

static int program_argc;
static char *program_args[MAX_ARGS];
static char logfile_name[TEMP_FILE_LENGTH] = "";
char icon_name[TEMP_FILE_LENGTH] = "";

static int timerRunning = 0;

int g_Gensym69 = 0;
BOOL g2pvt_use_status_area_icon = TRUE;
static HMENU gStatusMenu = NULL;
static NOTIFYICONDATA gIconData;


/*************************************************************************/
/* EXTERNS                                                               */
/*************************************************************************/
extern int No_window;		      /* defined in networks.c */
extern int unicode_is_handled_by_g2;  /* defined/set in windows.c */
extern HCURSOR g_mouseCursor;	      /* Overriding mouse cursor. */

extern void StoreNextEvent (HWND hwnd,
                            long eventtype,
                            long x,
                            long y,
                            long width, long height,
                            long key_code, long key_bits);
extern LPG2INFO GetlpG2Info(HWND);

extern void g2pvt_free_window_info(HWND hwnd);
extern void g2pvt_on_wm_paint(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, BOOL mdi_p);

extern HMENU dummyMenuBar;

extern BOOL Inside_modal_scrollbar_loop;

extern void ne_enqueue_next_event();

extern G2pointer ne_lookup_handle_for_fd(); /* defined in nt-next-event.c */
extern G2pointer get_and_decache_socket_to_NI_handle(long resolver_handle);
extern void g2pvt_tcpip_reconnect(NETWORK_INTERFACE *ni);

extern int timer_is_set;
extern DWORD tick_count_at_expiry;

extern BOOL ConfirmProgramExit;
extern int screenlock;
extern FILE *g2pvt_outstream;
extern int g2pvt_closebox;
extern int g2pvt_minimize;
extern int g2ext_product;

extern BOOL g2pvt_win32_init (HANDLE);
extern char *g2pvt_string_token (char *, char *, int);
extern void g2pvt_set_up_standard_files ();
extern char *g2ext_string_to_uppercase ();
extern void ne_set_ni_last_error ();
extern long g2ext_return_environment_variable ();
extern void g2ext_set_gensym_product ();
extern void g2ext_check_windows_platform ();
extern long g2pvt_network_listener_port (NETWORK_INTERFACE *listener, char *buffer, long size);
extern LRESULT g2pvt_taskbar_notify (HWND hwnd, WPARAM wParam, LPARAM lParam);
extern LRESULT g2pvt_taskbar_command (HWND hwnd, WPARAM wParam, LPARAM lParam);
extern NETWORK_INTERFACE *g2ext_primary_listener;
extern long g2pvt_simple_dialog (HWND, LPCWSTR, LPCWSTR, LPCWSTR, long,
                                 LPCWSTR, long, LPCWSTR, long, long);
extern int main (int, char *[]);
extern long g2ext_write_string_to_console(char *string);
extern int g2pvt_set_indicator_icon(long enable, LPCSTR iconName, LPCSTR tooltip);
extern HICON g2pvt_get_native_icon(int icon);
extern void g2pvt_inform_user(int flags, char *title, char *format, ...);

/*************************************************************************/
/* FORWARD REFERENCES                                                    */
/*************************************************************************/
extern UINT g2_event_code_for_windows_code(UINT);
extern UINT g2_mouse_code_for_windows_code(UINT,WPARAM);
extern UINT g2_keycode_for_virtual_key(UINT);
extern UINT g2pvt_compute_ansi_keycode(WPARAM, LPARAM);
extern BOOL windows_system_accelerator_key_p (long, BOOL, BOOL, BOOL);
static void g2_keypress (HWND, int, BOOL, BOOL, BOOL, BOOL);
void g2pvt_do_some_event_cycles(void);
int g2ext_app_init (HINSTANCE hInstance, LPSTR lpCmdLine, LPSTR productName);
int g2ext_app_run(void);

extern UINT g2use_ldap;

/*************************************************************************/
/* FUNCTIONS                                                             */
/*************************************************************************/

void g2pvt_note_ssl_connection (void *ssl, char *protocol, int nbits, char *cipher,
				char *subject, char *issuer)
{
  char buf[256];

  _snprintf(buf, sizeof(buf), "SSL Secured (%s %d bit %s)", protocol, nbits, cipher);
  buf[sizeof(buf)-1] = '\0';
  g2pvt_set_indicator_icon(TRUE, "Locked", buf);

  _snprintf(buf, sizeof(buf), "[Telewindows: SSL Secured %s %d bit %s]", protocol, nbits, cipher);
  buf[sizeof(buf)-1] = '\0';
  g2ext_write_string_to_console(buf);
}

void CleanUpAll ()                /* This used to be in graphics.c */
{
  if(IsMenu(gStatusMenu))
    DestroyMenu(gStatusMenu);

  DeleteObject(GhbmDummy);
  DeleteObject(GensymPalette);

  if (MenuFont != NULL)
    DeleteObject(MenuFont);

  g2pvt_destroy_native_icons(TRUE);

  if (IsMenu(dummyMenuBar))
    DestroyMenu(dummyMenuBar);

  ReleaseDC(GhwndWin, Ghdc);
  DeleteDC(GhdcMem);
  DeleteDC(GhdcOffscreen);
  if (IsWindow(hwndFrame))
    DestroyWindow(hwndFrame);        /* This will destroy all the child windows.
                                   And owned windows?? */
  if (IsWindow(GhwndWin))
    DestroyWindow(GhwndWin);
}

/* TODO: handle nested timer calls */
void g2pvt_enter_modal_loop(void)
{
  if(g2ext_product == G2_CMD)
    return;

  timerRunning++;
  //PRINTF("g2pvt_enter_modal_loop %d\n", timerRunning);

  // set timer only at first g2pvt_enter_modal_loop() call
  if (timerRunning == 1)
    SetTimer(hwndFrame, ANTIMODAL_TIMER_ID, ANTIMODAL_TIMER_PERIOD, NULL);
}

void g2pvt_exit_modal_loop(void)
{
  if(g2ext_product == G2_CMD)
    return;

  timerRunning--;
  //PRINTF("g2pvt_exit_modal_loop %d\n", timerRunning);

  // kill timer only on last g2pvt_exit_modal_loop() call
  if (timerRunning == 0)
    KillTimer(hwndFrame, ANTIMODAL_TIMER_ID);
}


/* Return the nearest (in path-to-root sense) workspace view containing given
 * point, in hwndPoint client-coordinates, or NULL if none. */
HWND g2pvt_workspace_view_from_point(HWND hwndPoint, POINT p)
{
  HWND hwnd;
  POINT q = p;

  MapWindowPoints(hwndPoint, NULL, &q, 1);
  hwnd = WindowFromPoint(q);

  while(hwnd && !g2pvt_workspace_view_p(hwnd))
    hwnd = g2pvt_parent_window(hwnd);
  return hwnd;
}

/* Is given hwnd (a G2-managed window) embedded into a dialog or some other
 * frame window.  At the moment, this means that the parent is not something we
 * know about, namely the MDI client window or the desktop. */
BOOL g2pvt_embedded_window_p(HWND hwnd)
{
  if(g2pvt_mdi_child_window_p(hwnd))
    return FALSE;
  else if(g2pvt_parent_window(hwnd) == NULL)
    return FALSE;
  else
    return TRUE;
}

/* Begin "mouse hover tracking" on given window if we are not already. */
void g2pvt_ensure_mouse_hover_tracking(HWND hwnd)
{
  TRACKMOUSEEVENT tme = {0};
  tme.cbSize = sizeof(tme);
  tme.dwFlags = TME_QUERY;
  tme.hwndTrack = hwnd;
  tme.dwHoverTime = HOVER_DEFAULT;
  TrackMouseEvent(&tme);

  if(tme.hwndTrack == hwnd && tme.dwFlags & TME_HOVER)
    return;			/* Already tracking */

  tme.cbSize = sizeof(tme);
  tme.dwFlags = TME_HOVER;
  tme.hwndTrack = hwnd;
  tme.dwHoverTime = HOVER_DEFAULT;
  TrackMouseEvent(&tme);
}

/* The function g2pvt_on_wm_mouse processes all mouse events for all wndprocs in
   G2 and TW. It must be very careful about the coordinate systems.

   MouseWheel messages arrive in screen coordinates, so they are first converted
   to hwnd coordinates, which is what all other mouse messages use.

   In the non-MDI case, we want the mouse position in hwndMain coordinates in
   all cases.

   In the MDI case, we want the position stored in frame_info to be in hwndMain
   coordinates, but the position supplied to StoreNextEvent to be in
   child-hwnd-under-mouse coordinates

   The hwnd supplied to g2pvt_on_wm_mouse is already the child-hwnd-under-mouse,
   except possibly when the mouse is captured, in which case we compute it via
   ChildWindowFromPoint().

   FIXME: In the SWV case, windows aren't necessarily children of hwndMain */

BOOL g2pvt_on_wm_mouse(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  UINT eventcode, keycode, lKeyBits;
  BOOL bAltKey;
  LPG2INFO lpG2Info = GetlpG2Info(hwnd);
  LPG2INFO frame_info = GetlpG2Info(hwndMain);
  HWND wsv;
  POINT p,q;

  bAltKey = (GetKeyState(VK_MENU) < 0);
  lKeyBits = 0;
  lKeyBits |= ((wParam & MK_CONTROL) ? X11_CONTROL_BIT : 0);
  lKeyBits |= ((wParam & MK_SHIFT) ? X11_SHIFT_BIT : 0);
  lKeyBits |= bAltKey ? X11_ALTERNATE_BIT : 0;
  if (message == WM_LBUTTONDBLCLK || message == WM_MBUTTONDBLCLK || message == WM_RBUTTONDBLCLK)
    lKeyBits |= X11_DOUBLE_BIT;

  /* G2 wants the SIGNED 16bit value */
  p.x = GET_X_LPARAM(lParam);
  p.y = GET_Y_LPARAM(lParam);

  /* Mouse wheel messages are always sent to the focus window,
     regardless of the window under the mouse.  In this way, they
     behave more like keystrokes. This is probably the reason why
     Windows provides the location in screen coordinates.
     Warning: duplicated code. */
  if (message == WM_MOUSEWHEEL)
    ScreenToClient(hwnd, &p);

  eventcode = g2_event_code_for_windows_code(message);
  keycode = g2_mouse_code_for_windows_code(message,wParam);

  q = p;                        /* Maintain winproc_cursor_x/y in hwndMain coor. */
  if (hwnd != hwndCoor)
    MapWindowPoints(hwnd, hwndCoor, &q, 1);
  frame_info->winproc_cursor_x = q.x;
  frame_info->winproc_cursor_y = q.y;

  /* In MDI case, if mouse is captured, convert to workspace-view-under-mouse coor,
   * where a workspace view is special since events on it are managed by G2. */
  if (Frame_is_MDI && GetCapture() && (wsv = g2pvt_workspace_view_from_point(hwndCoor,q)))
    if (hwnd != wsv) {
      MapWindowPoints(hwnd, wsv, &p, 1);
      hwnd=wsv;
    }

  if (message == WM_MOUSEMOVE) {
    if (frame_info->mouse_tracking)
      StoreNextEvent(hwnd, eventcode, p.x, p.y, 0L, 0L, keycode, lKeyBits);
    if(!Inside_modal_scrollbar_loop)
      g2pvt_ensure_mouse_hover_tracking(hwnd);
    
  } else {
    StoreNextEvent(hwnd, eventcode, p.x, p.y, 0L, 0L, keycode, lKeyBits);
    if (message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN)
      SetCapture(hwnd);        /* Gets mouse events even when they are outside our window. */
    else
      ReleaseCapture();
  }
  return FALSE;
}

/* Common WM_KEYDOWN and WM_SYSKEYDOWN handler. Returns TRUE if default wndproc should run. */
/* Windows sends us a SYSKEYDOWN message for any key, when either ALT key
 * is depressed and the CONTROL key is not.  We ignore it if it's the right
 * ALT key (AltGr). */
/* Windows sends us a KEYDOWN message for every key, except when the ALT
 * modifier is down. */
static BOOL on_wm_keydown (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  UINT vkey, keycode;
  BOOL bCtrlKey, bShiftKey, bAltKey, bAltGr;
  LPG2INFO lpG2Info = GetlpG2Info(hwnd);

  vkey = LOWORD(wParam);
  bCtrlKey = (GetKeyState(VK_CONTROL) < 0);
  bShiftKey = (GetKeyState(VK_SHIFT) < 0);
  bAltKey = (GetKeyState(VK_MENU) < 0);
  bAltGr = (GetKeyState(VK_RMENU) < 0); /* The AltGr key on international keyboards. */

  keycode = g2_keycode_for_virtual_key(vkey);

  /* System accelerator key? */
  if (windows_system_accelerator_key_p(vkey, bCtrlKey, bShiftKey, bAltKey))
    return TRUE;                /* Run the default wndproc. */

  /* Potential international character. Punt.
   * This means that one must use the LEFT alt key to
   * generate alt chars for G2. Even on US keyboards.
   * Also do this for space + modifier key. */
  else if (bAltGr || ((vkey == 32) && !(bCtrlKey || bShiftKey || bAltKey)))
    {
      return TRUE;                /* Run the default wndproc. */
    }

  /* Function keys, etc, which G2 understands. */
  else if (keycode != 0)
    {
      g2_keypress(hwnd, keycode, bCtrlKey, bShiftKey, bAltKey, FALSE);
      return FALSE;
    }
  /* Control chars and control+alt chars */
  else if (bCtrlKey && (keycode = g2pvt_compute_ansi_keycode(wParam, lParam)))
    {
      /* If CapsLock is depressed, we get an uppercase letter for keycode.
         However, we want only the shift key to determine whether we have
         an uppercase control key, so convert to lower case here.
         */
      if (isupper(keycode))
        keycode = tolower(keycode);
      g2_keypress(hwnd, keycode, bCtrlKey, bShiftKey, bAltKey, FALSE);
      return FALSE;
    }
  /* Simple chars, Alt chars, and Alt+shift chars. */
  else
    {
      return TRUE;                /* Run the default wndproc. */
    }
}

static BOOL on_wm_char(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  UINT keycode;
  BOOL bCtrlKey, bShiftKey, bAltKey;
  LPG2INFO lpG2Info = GetlpG2Info(hwnd);

  keycode = LOWORD(wParam);
  bCtrlKey = (GetKeyState(VK_CONTROL) < 0);
  bShiftKey = (GetKeyState(VK_SHIFT) < 0);
  bAltKey = (GetKeyState(VK_MENU) < 0);

  /* Windows sends a CHAR message for printing characters, include those
   * created by the use of the alt key and the numeric keypad.  We pass them
   * on to G2 unmodified.  The keycode is UNICODE here. */

  /* These characters never get any modifiers.  On some international
   * keyboards, the character was generated by holding down altGr, and
   * we don't want to propagate that to G2. */

  /* Control chars, space + modifier key, and delete are handled in KEYDOWN. */
  if (keycode < 32 || (keycode == 32 && (bCtrlKey || bShiftKey || bAltKey)) || keycode == 127)
    ;

  else if (unicode_is_handled_by_g2)
    g2_keypress(hwnd, keycode, FALSE, FALSE, FALSE, TRUE);

  else {                        /* Convert to ANSI (only for G2 5.x or earlier). */
    int i, n;
    BYTE ansi[4];
    WCHAR wch = keycode;
    n = WideCharToMultiByte(CP_ACP, 0, &wch, 1, ansi, 4, NULL, NULL);
    for(i=0; i<n; i++)
      g2_keypress(hwnd, ansi[i], FALSE, FALSE, FALSE, FALSE);
  }

  return FALSE;
}

/* Given an ASCII character code as supplied by WM_CHAR or WM_SYSCHAR,
 * return the corresponding virtual key. */
static UINT virtual_key_for_char_code(TCHAR ch)
{
  return VkKeyScan(ch) & 255;
}

/* Windows sends a SYSCHAR message when a character key is pressed
 * with ONLY the ALT key down.  Pass these on to G2 with the ALT
 * bit, so that users can bind alt+a, for example. */

/* TODO: Let the default wndproc run if G2 is not binding the particular key,
   so that Alt+char will activate that menu item. Note that the Alt+char bindings
   that G2 has by default are non-standard and relatively useless. */
static BOOL on_wm_syschar(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  UINT vkey, keycode;
  BOOL bCtrlKey, bShiftKey, bAltKey;
  LPG2INFO lpG2Info = GetlpG2Info(hwnd);

  keycode = LOWORD(wParam);
  bCtrlKey = (GetKeyState(VK_CONTROL) < 0);
  bShiftKey = (GetKeyState(VK_SHIFT) < 0);
  bAltKey = (GetKeyState(VK_MENU) < 0);

  vkey = virtual_key_for_char_code((TCHAR)keycode);
  if (windows_system_accelerator_key_p(vkey, bCtrlKey, bShiftKey, bAltKey))
    return TRUE;

  /* Control chars, space + modifier key, and delete are handled
     in KEYDOWN. */
  else if (keycode < 32 || (keycode == 32 && (bCtrlKey || bShiftKey || bAltKey)) || keycode == 127)
      ;
  else
    {
      g2_keypress(hwnd, keycode, bCtrlKey, bShiftKey, bAltKey, FALSE);
    }
  return FALSE;
}


BOOL g2pvt_on_wm_keyboard(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message) {
   case WM_CHAR:
     return on_wm_char(hwnd, message, wParam, lParam);

   case WM_SYSCHAR:
     return on_wm_syschar(hwnd, message, wParam, lParam);

   case WM_SYSKEYDOWN:
   case WM_KEYDOWN:
     return on_wm_keydown(hwnd, message, wParam, lParam);
  }
  return TRUE;
}


BOOL g2pvt_on_wm_querynewpalette(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  return 0;
}

BOOL g2pvt_on_wm_palettechanged(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  return 0;
}

BOOL g2pvt_on_wm_setcursor(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  if(g_mouseCursor) {
    SetCursor(g_mouseCursor);
    return FALSE;		/* Don't run default wndproc */
  }
  return TRUE;			/* Run default wndproc */
}

/* This is called only for WM_DESTROY on the classic window or the frame window.
 * Destroying an individual MDI child window, of course, does not shut us down
 * completely (see mdi_child_on_wm_destroy). */
BOOL g2pvt_on_wm_destroy(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int i;

  ne_enqueue_next_event(quit_event,0,0); /* Probably useless */
  g2pvt_free_window_info(hwnd);

  /* Do the rest of this stuff only once. */
  if (g2ext_window_destroyed)
    return TRUE;

  if (g2pvt_outstream) { /* handle to log file */
    fflush(stdout);
    fflush(stderr);
    FlushFileBuffers(g2pvt_outstream);
    CloseHandle(g2pvt_outstream);
    ConfirmProgramExit = FALSE; /* And now don't try to ask them anything on this non-console */
    g2pvt_outstream = NULL;
  }
  /* To ensure we call cleanup enough times, call it in a loop
   * until it returns error. (most likely WSANOTINITIALISED)
   * In case an implementor does not return this, put in a
   * safety valve which kills the loop after 10 calls.
   */
  for (i=0; (WSACleanup() == 0) && (i<10); i++);
  g2ext_window_destroyed = TRUE;
  No_window = TRUE;		/* Prohibit attempts to draw to destroyed window. */

  if (g2pvt_mutex)		/* Mutex for licensing */
    CloseHandle(g2pvt_mutex);

  /* it appears that PostQuitMessage does not actually work.  this
   * function never receives the WM_QUIT message in any event.
   * So, we set a variable above to communicate this fact to our
   * event loop. */
  PostQuitMessage(0);
  return TRUE;
}

/*
 * Modeless Queries
 */

typedef enum {ModelessMenu, ModelessMsgBox} ModelessOpcode;

typedef struct {
  ModelessOpcode opcode;
  DWORD main_threadID;
  HWND hwnd;			/* The owner window */
  LPCSTR text;
  LPCSTR caption;
  HMENU menu;
  UINT flags;
  UINT msg;
  int x,y;
} ModelessMenuInfo;

static DWORD WINAPI post_modeless_query_thread_1(LPVOID lpParameter);
static HANDLE modeless_query_thread = NULL;

static BOOL post_modeless_query(ModelessOpcode opcode, 
				HWND hwnd, LPCSTR text, LPCSTR caption,
				HMENU menu, UINT flags, UINT msg, int x, int y)
{
  static ModelessMenuInfo info;

  if(modeless_query_thread) {	/* Only one thread is allowed. */
    fprintf(stderr, "Modeless query thread is already active.\n");
    return FALSE;
  }

  info.opcode = opcode;
  info.main_threadID = GetCurrentThreadId();
  info.text = text;
  info.caption = caption;
  info.hwnd = hwnd;
  info.menu = menu;
  info.flags = flags;
  info.msg = msg;
  info.x = x;
  info.y = y;

  modeless_query_thread = CreateThread(NULL, 0, &post_modeless_query_thread_1, (LPVOID)&info, 0, NULL);

  if(modeless_query_thread == NULL) {
    fprintf(stderr, "CreateThread failed: %d\n", GetLastError());
    return FALSE;
  }
  return TRUE;
}

BOOL g2pvt_modeless_menu(HWND hwndOwner, HMENU menu, UINT flags, UINT msg, int x, int y)
{
  return post_modeless_query(ModelessMenu, hwndOwner, NULL, NULL, menu, flags, msg, x, y);
}

BOOL g2pvt_modeless_msgbox(HWND hwndOwner, LPCSTR text, LPCSTR caption, UINT flags, UINT msg)
{
  return post_modeless_query(ModelessMsgBox, hwndOwner, text, caption, NULL, flags, msg, 0, 0);
}

BOOL g2pvt_modeless_inform(LPCSTR text)
{
  return post_modeless_query(ModelessMsgBox, NULL, text, "G2", NULL, MB_OK|MB_ICONINFORMATION, WM_NULL, 0, 0);
}

BOOL g2pvt_modeless_error(char *format, ...)
{
  va_list ap;
  static char buf[1024];

  va_start(ap, format);
  _vsnprintf(buf, sizeof(buf), format, ap);
  va_end(ap);
  buf[sizeof(buf)-1] = 0;

  return post_modeless_query(ModelessMsgBox, NULL, buf, "G2", NULL, MB_OK|MB_ICONEXCLAMATION, WM_NULL, 0, 0);
}

/* Note: It's not safe to call any C runtime routines from this function. */
static DWORD WINAPI post_modeless_query_thread_1(LPVOID lpParameter)
{
  ModelessMenuInfo *pMI = (ModelessMenuInfo *)lpParameter;
  HWND hwndOwner = CreateWindow("BUTTON", "Dummy", WS_CHILD, 0,0,0,0, pMI->hwnd, NULL, hInst, NULL);
  int choice = 0;
  BOOL choiceMade = FALSE;

  AttachThreadInput(GetCurrentThreadId(), pMI->main_threadID, TRUE);
  SetFocus(hwndOwner);

  switch(pMI->opcode) {
   case ModelessMenu:
     //Gensym-562-CC-BF-JIRA-46906-Twng and G2 stops drawing
	 SetForegroundWindow(pMI->hwnd);
     //Gensym-562-CC-BF-JIRA-46906-Twng and G2 stops drawing
     choice = TrackPopupMenu(pMI->menu, TPM_RETURNCMD | TPM_NONOTIFY | pMI->flags, pMI->x, pMI->y,
			     0, hwndOwner, NULL);
     choiceMade = (choice != 0);
	 //Gensym-562-CC-BF-JIRA-46906-Twng and G2 stops drawing
	 SendMessage(pMI->hwnd, WM_NULL, 0, 0);
	 Sleep(50);
	 //Gensym-562-CC-BF-JIRA-46906-Twng and G2 stops drawing
     break;
   case ModelessMsgBox:
     choice = MessageBox(hwndOwner, pMI->text, pMI->caption, pMI->flags);
     choiceMade = (choice != IDCANCEL);
     break;
  }

  CloseHandle(modeless_query_thread);
  modeless_query_thread = NULL;

  if(choiceMade)
    PostMessage(pMI->hwnd, pMI->msg, choice, 0);

  return 0;
}

/* Grays or ungrays the items we know about. */
static void initialize_system_menu(HWND hwnd, HMENU hmenu)
{
  DWORD style = GetWindowLongA(hwnd, GWL_STYLE);
  DWORD cstyle = GetClassLongA(hwnd, GCL_STYLE);
  BOOL mined = style & WS_MINIMIZE;
  BOOL maxed = style & WS_MAXIMIZE;

  EnableMenuItem(hmenu, SC_RESTORE, (mined || maxed) ? MF_ENABLED : MF_GRAYED);
  EnableMenuItem(hmenu, SC_MOVE, maxed ? MF_GRAYED : MF_ENABLED);
  EnableMenuItem(hmenu, SC_SIZE, ((style & WS_THICKFRAME) && !mined && !maxed) ? MF_ENABLED : MF_GRAYED);
  EnableMenuItem(hmenu, SC_MINIMIZE, ((style & WS_MINIMIZEBOX) && !mined) ? MF_ENABLED : MF_GRAYED);
  EnableMenuItem(hmenu, SC_MAXIMIZE, ((style & WS_MAXIMIZEBOX) && !maxed) ? MF_ENABLED : MF_GRAYED);

  if (cstyle & CS_NOCLOSE)
    EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);        /* Never ungray, in case grayed by user. */
}

static void post_system_menu_in_separate_thread(HWND hwnd, int x, int y)
{
  HMENU hmenu = GetSystemMenu(hwnd,FALSE);
  initialize_system_menu(hwnd, hmenu);
  g2pvt_modeless_menu(hwnd, hmenu, 0, WM_SYSCOMMAND, x, y);
}


/* TRUE if we are running as a noninteractive NT service, and hence have no
 * visible desktop (and in particular, no Shell) */
long g2ext_noninteractive_service_p(void)
{
  HWINSTA wsta;
  USEROBJECTFLAGS flags;
  DWORD len;

  GetDesktopWindow();
  wsta = GetProcessWindowStation();
  if(wsta && GetUserObjectInformation(wsta, UOI_FLAGS, &flags, sizeof(flags), &len))
    return (flags.dwFlags & WSF_VISIBLE) == 0;
  return 0;
}

/*************************************************************************
*  LRESULT create_taskbar_menu (HWND hWnd)
*
*  Purpose:
*  Entry:
*  Returns:
*  Comments:
*************************************************************************/
static LRESULT create_taskbar_menu (HWND hWnd)
{
  POINT pt;

  if (gStatusMenu == NULL) {
    gStatusMenu = CreatePopupMenu();
    if (gStatusMenu == NULL)
      return FALSE;
    InsertMenu(gStatusMenu, -1, MF_BYPOSITION, GWM_CONNECT, "Connect Telewindows");
    InsertMenu(gStatusMenu, -1, MF_BYPOSITION, GWM_EXIT, "Shut Down G2");
  }

  /* note: must set window to the foreground or the menu won't disappear when
   * it should
   */
  SetForegroundWindow(hWnd);

  GetCursorPos(&pt);
  g2pvt_modeless_menu(hWnd, gStatusMenu, TPM_BOTTOMALIGN, WM_COMMAND, pt.x, pt.y);
  return TRUE;
}


/*************************************************************************
*  void g2pvt_add_g2_status_icon (HANDLE instance)
*
*  Purpose:
*  Entry:
*  Returns:
*  Comments:
*************************************************************************/
void g2pvt_add_g2_status_icon (HANDLE instance)
{
  if (G2_CMD == g2ext_product) {

    ZeroMemory((PVOID) &gIconData, sizeof(NOTIFYICONDATA));

    /* Default initialization for the NOTIFYICONDATA base struct. */
    gIconData.cbSize           = sizeof(NOTIFYICONDATA);
    gIconData.hWnd             = GhwndWin;
    gIconData.uID              = 0;
    gIconData.uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    gIconData.uCallbackMessage = WM_STATUS_AREA_NOTIFY;
    gIconData.hIcon            = LoadImage(instance, "g2", IMAGE_ICON,
                                           16, 16, LR_DEFAULTCOLOR);

    if (gIconData.hIcon == NULL) {
      g2pvt_notify_user("Unable to load icon for status area: %s",
			g2pvt_get_last_error_string());
    }

    strncpy(gIconData.szTip, "G2 is initializing", 64);

    if (!Shell_NotifyIcon(NIM_ADD, &gIconData)) {
      g2pvt_notify_user("Unable to add icon to status area");
      return;
    }
  }
}


/*************************************************************************
*  LRESULT g2pvt_taskbar_notify (HWND hwnd, WPARAM wParam, LPARAM lParam)
*
*  Purpose:
*  Entry:
*  Returns:
*  Comments:
*************************************************************************/
LRESULT g2pvt_taskbar_notify (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  LRESULT lr = FALSE;

  switch (lParam) {
  case WM_RBUTTONUP:
    lr = create_taskbar_menu(hwnd);
    break;
  }

  return lr;
}


/*************************************************************************
*  void g2pvt_windows_shutdown ()
*
*  Purpose:
*  Entry:
*  Returns:
*  Comments:
*************************************************************************/
void g2pvt_windows_shutdown ()
{
  if ((G2_CMD == g2ext_product) && g2pvt_use_status_area_icon) {
    if (!Shell_NotifyIcon(NIM_DELETE, &gIconData)) {
      g2pvt_notify_user("Unable to remove icon from status area");
    }
  }
}


/*************************************************************************
*  void g2pvt_update_taskbar_status_area ()
*
*  Purpose:
*  Entry:
*  Returns:
*  Comments:
*************************************************************************/
void g2pvt_update_taskbar_status_area ()
{
  if (g2pvt_use_status_area_icon) {
    strncpy(gIconData.szTip, g2ext_primary_listener->nw_pathname, 64);
    if(g2ext_primary_listener->secure_connection_requested
       && strlen(gIconData.szTip) < 55)
      strcat(gIconData.szTip, "/SSL");

    if (!Shell_NotifyIcon(NIM_MODIFY, &gIconData)) {
      g2pvt_notify_user("Unable to update icon in status area");
    }
  }
}

/*************************************************************************
 *  void g2ext_update_system_tray(long icon)
 *
 *  Purpose: Updates taskbar notification area icon and/or tooltip.
 *  Entry:
 *  Returns:
 *  Comments:
 *************************************************************************/
long g2ext_update_system_tray (long icon, char *iconName, LPWSTR tooltip)
{
  NOTIFYICONDATAW iconData;
  HICON hIcon = NULL;
  int rc;

  if(g2ext_product != G2_CMD)
    return 0;
  if(!g2pvt_use_status_area_icon)
    return 0;

  ZeroMemory((PVOID) &iconData, sizeof(NOTIFYICONDATAW));
  iconData.cbSize           = sizeof(NOTIFYICONDATAW);
  iconData.hWnd             = GhwndWin;
  iconData.uID              = 0;
  iconData.uFlags           = 0;

  if(icon >= 0)
    hIcon = g2pvt_get_native_icon(icon);
  else if(iconName && iconName[0])
    hIcon = LoadImage(hInst, iconName, IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

  if(hIcon) {
    iconData.uFlags |= NIF_ICON;
    iconData.hIcon = hIcon;
  }

  if(tooltip && tooltip[0] != L'\0') {
    iconData.uFlags |= NIF_TIP;
    wcsncpy(iconData.szTip, tooltip, 63);
  }

  rc = Shell_NotifyIconW(NIM_MODIFY, &iconData);
  if(hIcon)
    DestroyIcon(hIcon);
  return rc;
}


#define WIDTH_OF_WINDOW_BORDER 6 /* Sync with lisp default-width-of-window-border */

static BOOL on_wm_size(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int width = LOWORD(lParam);
  int height = HIWORD(lParam);
  int dx, dy;
  LPG2INFO lpG2Info = GetlpG2Info(hwnd);
  RECT r;

  if (! lpG2Info)
    return TRUE;

  dx = width - lpG2Info->winproc_width;
  dy = height - lpG2Info->winproc_height;

  lpG2Info->winproc_width = width;
  lpG2Info->winproc_height = height;

  if (wParam == SIZE_MINIMIZED)		       /* Suppress reshape if minimizing. */
    return FALSE;

  StoreNextEvent(hwnd, X11_RESHAPE, 0, 0, width, height, 0L, 0L);

  /* Now do further invals so that G2's pane borders get refreshed. */
  r.left = width - max(dx,0) - WIDTH_OF_WINDOW_BORDER;
  r.top = 0;
  r.right = width;
  r.bottom = height;
  InvalidateRect(hwnd, &r, FALSE);

  r.left = 0;
  r.top = height - max(dy,0) - WIDTH_OF_WINDOW_BORDER;
  r.right = width;
  r.bottom = height;
  InvalidateRect(hwnd, &r, FALSE);

  return FALSE;
}

/*************************************************************************\
 *
 *               G2WndProc(HWND, unsigned, WORD, LONG)
 *
 *  Purpose:
 *
 *     Process the G2 server window's messages.
 *     WARNING: Not used in SDI, MDI, or Embedded modes.
 *
 *  Entry:
 *
 *               HWND            hwnd            - handle to window.
 *               unsigned        iMessage        - message ID>
 *               WORD            wParam
 *               LONG            lParam
 *
 *  Returns:
 *
 *               long with message dependent meanings.
 *
 *  Comments:
 *     12/20/94, mpc: These WndProc's are inherent messy. The giant switch
 *        statement makes the code difficult to manage. Consider in the future
 *        using a handler array as in the WMHANDLER sample on the MSDN CD.
 *
 *     8/19/01, mhd: Note about calls to ne_enqueue_next_event:
 *        scheduler events are global to all sockets.
 \*************************************************************************/

LONG WINAPI G2WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LPG2INFO        lpG2Info;
  PAINTSTRUCT     ps;
  G2pointer       socket;
  BOOL rundef = TRUE;                /* Whether to run the default wndproc. */
  long retval = 0;		     /* Return value if default wndproc NOT run. */

  lpG2Info = GetlpG2Info(hwnd);

  switch (message) {
   case NE_SCHEDULER_EVENT:        /* I think this message is no longer sent. */
     ne_enqueue_next_event(scheduler_event, 0, 0);
     break;

   case WM_TIMER:
     switch(wParam) {
      case ANTIMODAL_TIMER_ID:
	g2pvt_do_some_event_cycles();
	return 0;

      case MOVE_RESIZE_TIMER_ID:
	KillTimer(hwnd, wParam);
	SendMessage(hwnd, WM_CANCELMODE, 0, 0);
	g2ext_write_string_to_console("Warning: Window move/resize cancelled after timeout.");
	return 0;

      case NE_TIMER_ID:                         /* Don't kill timers we don't
                                                   own.  For HQ-4751266, also
                                                   part the unofficial "WM_TIMER
                                                   patch" for Siemens.*/
       KillTimer(hwnd, wParam);            /* make sure this timer is a one-shot. */
       timer_is_set = FALSE;            /* Defined in ntevent.c */
       tick_count_at_expiry = 0;
       ne_enqueue_next_event(scheduler_event, 0, 0);
       return 0;
     }
     break;

   case WM_SETCURSOR:
     rundef = g2pvt_on_wm_setcursor(hwnd, message, wParam, lParam);
     retval = TRUE;
     break;

   case WM_MOUSEMOVE:
   case WM_MOUSEHOVER:

   case WM_LBUTTONDOWN:
   case WM_MBUTTONDOWN:
   case WM_RBUTTONDOWN:
     /* Change to click-to-focus (8.1a0, also in 71r3) -fmw, 1/10/05 */
     if (message != WM_MOUSEMOVE && parent_GhwndWin && GetFocus() != hwnd)
       SetFocus(hwnd);

   case WM_LBUTTONUP:
   case WM_MBUTTONUP:
   case WM_RBUTTONUP:
   case WM_MOUSEWHEEL:
   case WM_LBUTTONDBLCLK:
   case WM_MBUTTONDBLCLK:
   case WM_RBUTTONDBLCLK:
     rundef = g2pvt_on_wm_mouse(hwnd, message, wParam, lParam);
     break;

   case WM_CHAR:
   case WM_SYSCHAR:
   case WM_SYSKEYDOWN:
   case WM_KEYDOWN:
     rundef = g2pvt_on_wm_keyboard(hwnd, message, wParam, lParam);
     break;

   case WM_DRAWITEM:
     g2pvt_on_draw_item(hwnd, (int)wParam, (LPDRAWITEMSTRUCT)lParam);
     break;

   case WM_MEASUREITEM:
     g2pvt_on_measure_item(hwnd, (int)wParam, (LPMEASUREITEMSTRUCT)lParam);
     break;

   case WM_UNDOCUMENTED_SYSMENU:
     post_system_menu_in_separate_thread(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
     return 0;

   case WM_SYSCOMMAND:
     switch(wParam & 0xFFF0) {
      case SC_KEYMENU:
        if (screenlock)                /* Suppress system menu in screenlock mode. */
          return 0;
        else {
          POINT p = {0, 0};
          ClientToScreen(hwnd,&p);
          post_system_menu_in_separate_thread(hwnd, p.x, p.y);
          return 0;
        }
      case SC_MOUSEMENU:
        post_system_menu_in_separate_thread(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
      case SC_SIZE:
      case SC_MOVE:
	if(g2pvt_move_resize_timeout > 0 && g2ext_product == G2_CMD) { /* Only in G2. */
	  int rc;
	  SetTimer(hwnd, MOVE_RESIZE_TIMER_ID, g2pvt_move_resize_timeout, NULL);
	  rc = DefWindowProcW(hwnd, message, wParam, lParam);
	  KillTimer(hwnd, MOVE_RESIZE_TIMER_ID);
	  return rc;
	}
     }
     break;

   case WM_NCRBUTTONDOWN:
     /* Windows actually enters the modal menu loop on button-down,
	so don't let it, and wait for buttonup to post the menu. */
     if(wParam == HTCAPTION || wParam == HTSYSMENU)
       return 0;
     break;

   case WM_NCRBUTTONUP:
     if(wParam == HTCAPTION || wParam == HTSYSMENU) {
       post_system_menu_in_separate_thread(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
       return 0;
     }
     break;

   case WM_SIZE:
     rundef = on_wm_size(hwnd, message, wParam, lParam);
     break;

     /* Ask host to repaint us. */
   case WM_PAINT:
     if (!lpG2Info || !lpG2Info->is_connected) {
       BeginPaint(hwnd, &ps);
       EndPaint(hwnd, &ps);
     } else if (lpG2Info->winproc_update_count > 0) {  /* If we get a WM_PAINT */
       BeginPaint(hwnd, &ps);	                       /* after a palette change, */
       EndPaint(hwnd, &ps);			       /* redraw the entire window. */
       lpG2Info->winproc_update_count = 0;
       InvalidateRect(hwnd, NULL, TRUE);
     } else {
       g2pvt_on_wm_paint(hwnd, message, wParam, lParam, FALSE);
     }
     return 0;

     /* The Windows event WM_ACTIVATE most closely acts like the X event
     ** FocusIn, despite its name. WM_SETFOCUS can happen later, after the
     ** window is activated, but before any input event (key click, mouse)
     ** has happened. */
   case WM_ACTIVATE:
     if (WA_INACTIVE != LOWORD(wParam)) {
       StoreNextEvent (hwnd, X11_FOCUS_IN, 0L, 0L, 0L, 0L, 0L, 0L);
       rundef = FALSE;
     }
     break;

   case WM_QUERYNEWPALETTE:
     rundef = g2pvt_on_wm_querynewpalette(hwnd, message, wParam, lParam);
     break;

   case WM_PALETTECHANGED:
     rundef = g2pvt_on_wm_palettechanged(hwnd, message, wParam, lParam);
     break;

   case WM_WINDOWPOSCHANGING:
     if (screenlock) {
       LPWINDOWPOS lpwp = (LPWINDOWPOS) lParam;
       WINDOWPLACEMENT wndpl;
       wndpl.length = sizeof(WINDOWPLACEMENT);
       if (GetWindowPlacement(hwnd, &wndpl)) {
         /* lpwp->flags = SWP_NOMOVE; */
         lpwp->x = wndpl.rcNormalPosition.left;
         lpwp->y = wndpl.rcNormalPosition.top;
       }
     }
     break;

     /* This message comes when we start to resize/move. */
   case WM_ENTERSIZEMOVE:
     g2pvt_enter_modal_loop();
     break;

     /* This message (usually) comes when we finish a resize/move. */
   case WM_EXITSIZEMOVE:
     g2pvt_exit_modal_loop();
     break;

   case WSA_NETEVENT:
     socket = ne_lookup_handle_for_fd(wParam);
     if (socket != -1) {
       int eventcode = 0;
       int err = WSAGETSELECTERROR(lParam);
       ne_set_ni_last_error(socket,err);
       switch (WSAGETSELECTEVENT(lParam)) {
        case FD_CONNECT: {
          NETWORK_INTERFACE *ni =
            (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(socket);
          if (ni->connected_p) break; /* try to avoid a Windows 95 bug */
          if (err == 0) ne_connect_ni(socket);
          ni->connect_status = err;
          eventcode = connect_event; break;
        }
        case FD_ACCEPT:  eventcode = accept_event;
          ne_set_next_timer_event(500); break;
        case FD_READ:    eventcode = read_and_block_event; break;
        case FD_WRITE:   eventcode = write_event;   break;
        case FD_CLOSE:   eventcode = close_event;   break;
       }
       if (eventcode != 0)
         ne_enqueue_next_event(eventcode, socket, err);
     }
     rundef = FALSE;
     break;

   case WSA_NETEVENT_NS: {
     int buflen, error;
     NETWORK_INTERFACE *ni;
     socket = get_and_decache_socket_to_NI_handle((long)wParam);
     if (!socket) break;
     ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(socket);
     if (!ni) break;
     ni->resolver_handle = 0;

     buflen = WSAGETASYNCBUFLEN(lParam);
     error = WSAGETASYNCERROR(lParam);

     if (error)
	errno = TCPIP_CONNECT_NO_SUCH_HOST;
     else
	g2pvt_tcpip_reconnect(ni);

     if (errno) {
	ni->connect_status = errno;
	ne_enqueue_next_event(connect_event, socket, errno);
     }
     break;
   }

   case WM_DESTROY:
     rundef = g2pvt_on_wm_destroy(hwnd, message, wParam, lParam);
     break;

   case WM_STATUS_AREA_NOTIFY:
     return g2pvt_taskbar_notify(hwnd, wParam, lParam);
     break;

   case WM_COMMAND:
     return g2pvt_taskbar_command(hwnd, wParam, lParam);
     break;
  }

  if (rundef)
    return DefWindowProcW(hwnd, message, wParam, lParam);
  else
    return retval;
}

#ifdef GENFLEX

/* G2WndProc Wrapper */
LONG GenflexWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LONG result;
    
    result = G2WndProc(hwnd, message, wParam, lParam);
    //g2_event_cycle(0); // UNDONE: do we need this here?

    return result;
}

#endif

/* g2pvt_do_some_event_cycles is called once for each WM_TIMER event we receive during
 * modal Win32 event loops.  We start and stop the timer (ANTIMODAL_TIMER_ID)
 * around calls to modal Win32 functions. */
void g2pvt_do_some_event_cycles (void)
{
  int quit_p;
  static int inside_event_cycle = 0;

  if (inside_event_cycle) {        /* Disallow recursion. */
/* PRINT("Warning: recursive g2pvt_do_some_event_cycles ignored: %d\n", inside_event_cycle); */
    return;
  }

  inside_event_cycle++;
  quit_p = g2_event_cycle(0);
  inside_event_cycle--;

  if (quit_p)
    ne_enqueue_next_event(quit_event,0,0);
  else
    ne_enqueue_next_event(display_event, 0, 0); /* Needed? */
}


/* Sets the maximum time we let the main thread be in a move/resize-window modal
 * loop.  0 means no timeout. Note that once the bug is fixed, this call can be
 * ignored, since the main thread will always spend 0 seconds in the modal
 * loop. Returns the previous value.  -fmw, 6/24/05 */
long g2ext_set_move_resize_time_limit(long seconds)
{
  int prev = g2pvt_move_resize_timeout;
  g2pvt_move_resize_timeout = max(0,1000*seconds);
  return prev;
}


/***************************************************************************\
*
*       windows_system_accelerator_key_p (vk, ctrl, shift, alt)
*
*       PURPOSE: Tests for system accelerator keys
*
*       COMMENTS:
*        We do not want to override Windows system acclerator keys under
*       any circumstances.  So we test for them explicitly.  G2 will simply
*       never see these keys.
*        Although F1 is a standard help key, only G2 can provide any help,
*       so let it through.  Likewise for print screen.  We ignore close messages
*       anyways, so we can also let ctrl+F4 and alt+F4 through.
*
*       TODO
*        We also need to pass all of the Alt+menuChar keys, which of course
*        depends on what menubar is posted, as well as F10 and Shift+F10.
*
*       Here's the complete list that Windows defines:
*         ALT+ESC        Switches to the next application.
*         ALT+HYPHEN        Opens the System menu for a document window.
*         ALT+SPACEBAR        Opens the System menu for an application window.
*         ALT+TAB        Switches to the next application.
*         CTRL+ESC        Switches to Windows Task List.
*         SHIFT+ALT+TAB        Switches to the previous application.
*
*         F1                Starts Help if the application has Help.
*         ALT+F4        Closes an application or a window.
*         CTRL+F4        Closes the active group or document window.
*         PRINT SCREEN        Copies an image on the screen onto the clipboard.
*         ALT+PRINT SCREEN        Copies an image in the active window onto the clipboard.
*
\***************************************************************************/
BOOL windows_system_accelerator_key_p (vk, ctrl, shift, alt)
  long vk;
  BOOL ctrl;
  BOOL shift;
  BOOL alt;
{
  if (!ctrl && !shift && alt) {
    return (vk == VK_ESCAPE) || (vk == VK_OEM_MINUS) ||
      (vk == VK_PRINT) || (vk == VK_SPACE) ||
      (vk == VK_TAB) || (vk == VK_F4);
  }

  else if (ctrl && !shift && !alt) {
    return (vk == VK_ESCAPE);
  }

  else if (!ctrl && shift && alt) {
    return (vk == VK_TAB);
  }

  else if (ctrl) /* added to support ctrl+tab or ctrl+shift+tab in MDI
                    children. Consider limiting to that case only! */
    {
      if (Frame_is_MDI)
        return (vk == VK_TAB) || (!shift && vk == VK_F4);
    }

  /* F10 activates a native menu bar in Win32, and Shift+F10 posts a context menu,
   * so we ought to let windows handle it. Another key G2 users should not bind. */
/*   else if (vk == VK_F10) */
/*     return TRUE; */

  return FALSE;
}




/***************************************************************************\
*
*       g2pvt_compute_ansi_keycode (wparam, lparam)
*
*       PURPOSE: Computes the ANSI key for the given params, if any.
*
*       COMMENTS:
*        This is the only way to lookup the ANSI keycode when the control
*       key is depressed.  Windows won't translate for us in that case.
*       It's quite gross that we have to get the entire keyboard state to
*       do this.
*
\***************************************************************************/
UINT g2pvt_compute_ansi_keycode(WPARAM wparam, LPARAM lparam)
{
  UINT vkey;
  BYTE keystate[256];
  WORD ansi;
  UINT scancode;
  int len;

  vkey = LOWORD(wparam);
  scancode = HIWORD(lparam) & 0xFF,

  GetKeyboardState(keystate);
  /* Turn off the modifiers, else we won't get a translation. */
  keystate[VK_CONTROL] = 0;
  keystate[VK_LCONTROL] = 0;
  keystate[VK_RCONTROL] = 0;

  /* Turn off the ALT bit, too? */
#if 0
  keystate[VK_MENU] = 0;
  keystate[VK_LMENU] = 0;
  keystate[VK_RMENU] = 0;
#endif

  len = ToAsciiEx(vkey, scancode, keystate, &ansi, 0, default_hkl);

  if (len == 1)
      return (UINT)(ansi & 0xff);
  else
    return 0;
}

/* Compute the G2 keycode, with modifiers, for given virtual key and scan code,
   as supplied in a WM_KEYDOWN message. */
UINT g2pvt_compute_gensym_keycode(UINT vKey, UINT scanCode)
{
  BYTE state[256];
  WCHAR wp[2];
  UINT key = 0;
  BOOL ctrl, alt, shift;

  GetKeyboardState(state);
  ctrl = (state[VK_CONTROL] & 0x80) != 0;
  alt = (state[VK_MENU] & 0x80) != 0;
  shift = (state[VK_SHIFT] & 0x80) != 0;

  key = g2_keycode_for_virtual_key(vKey);

  if(key == 0) {
    /* Turn off the modifiers, else we won't get a translation. */
    state[VK_CONTROL] = 0;
    state[VK_LCONTROL] = 0;
    state[VK_RCONTROL] = 0;
    if(ToUnicode(vKey, scanCode, state, wp, 2, 0) == 1) {
      key = wp[0] | (wp[0]&0xFF00 ? X11_UNICODE_BIT : 0);
      shift = FALSE;		/* Implicit in the key code */
    }
  }

  if(key == 0)
    return 0;

  if(ctrl)
    key |= X11_CONTROL_BIT;

  if(alt)
    key |= X11_ALTERNATE_BIT;

  if(shift)
    key |= X11_SHIFT_BIT;

  return key;
}


/***************************************************************************\
*
*       g2_keypress (keycode, control, shift, alt, unicode)
*
*       PURPOSE: Enqueues a G2 keypress event.
*
*       Remark: unicode is new for the release pending 5/17/99. When
*        unicode is TRUE, all of the other modifiers must be FALSE.
*
\***************************************************************************/
static void g2_keypress (HWND hwnd, int keycode, BOOL control, BOOL shift, BOOL alt, BOOL unicode)
{
  LPG2INFO info = GetlpG2Info(hwndMain);
  HWND wsv;
  POINT p;
  long bits = 0;

  if (keycode == 0)
    return;

  if (shift)
    bits |= X11_SHIFT_BIT;

  if (control)
    bits |= X11_CONTROL_BIT;

  if (alt)
    bits |= X11_ALTERNATE_BIT;

  if (unicode)
    bits |= X11_UNICODE_BIT;

  p.x = info->winproc_cursor_x; /* In hwndCoor client coordinates. */
  p.y = info->winproc_cursor_y;

  /* If we have workspace view windows, whether embedded or in an MDI
     frame, it is important that the event is in terms of the
     workspace view window under the mouse. This is G2's unusual
     convention about focus. */
  if (Frame_is_MDI && (wsv = g2pvt_workspace_view_from_point(hwndCoor,p))) {
    hwnd = wsv;
    MapWindowPoints(hwndMain, wsv, &p, 1);

  } else if (Frame_is_embedded) {
    /* G2 wants the window under the mouse, not the focus window,
       but that is odd in the embedded case, because we won't even get
       the keyboard event unless the mouse is over one of our windows.
       So, we send the event relative to the focus window, hwnd. */
    MapWindowPoints(hwndCoor, hwnd, &p, 1);
  } else {
    hwnd = hwndMain;
  }

  StoreNextEvent(hwnd, X11_KEYPRESS, p.x, p.y, 0L, 0L, keycode, bits);
}




/***************************************************************************\
*
*       g2_event_code_for_windows_code(UINT)
*
*       PURPOSE: Translates Windows mouse message to a G2 event code.
*
\***************************************************************************/
UINT g2_event_code_for_windows_code(message)
  UINT message;
{
  switch (message)
    {
    case WM_MOUSEMOVE:
    case WM_MOUSEHOVER:
      return X11_POINTER_MOTION;

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
    case WM_MBUTTONDBLCLK:
    case WM_RBUTTONDBLCLK:
      return X11_BUTTON_PRESS;

    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
      return X11_BUTTON_RELEASE;

    case WM_MOUSEWHEEL:
      return X11_KEYPRESS;        /* Behaves like a keystroke for G2. */

    default:
      return 0;
    }
}



/***************************************************************************\
*
*       g2_mouse_code_for_windows_code(UINT)
*
*       PURPOSE: Translates Windows mouse message to a G2 mouse key code.
*
\***************************************************************************/
UINT g2_mouse_code_for_windows_code(UINT message, WPARAM wParam)
{
  int delta;
  switch(message)
    {
    case WM_MOUSEMOVE:
      return GENSYM_MOUSE_MOTION;

     case WM_MOUSEHOVER:
      return GENSYM_MOUSE_HOVER;

    case WM_LBUTTONDOWN:
      return GENSYM_MOUSE_LEFT_DOWN;

    case WM_MBUTTONDOWN:
      return GENSYM_MOUSE_MIDDLE_DOWN;

    case WM_RBUTTONDOWN:
      return GENSYM_MOUSE_RIGHT_DOWN;

    case WM_LBUTTONUP:
      return GENSYM_MOUSE_LEFT_UP;

    case WM_MBUTTONUP:
      return GENSYM_MOUSE_MIDDLE_UP;

    case WM_RBUTTONUP:
      return GENSYM_MOUSE_RIGHT_UP;

    case WM_MOUSEWHEEL:
      delta = GET_WHEEL_DELTA_WPARAM(wParam);
      return (delta>0) ? GENSYM_MOUSE_WHEEL_FORWARD : GENSYM_MOUSE_WHEEL_BACKWARD;

    case WM_LBUTTONDBLCLK:
      return GENSYM_MOUSE_LEFT_DOWN;

    case WM_MBUTTONDBLCLK:
      return GENSYM_MOUSE_MIDDLE_DOWN;

    case WM_RBUTTONDBLCLK:
      return GENSYM_MOUSE_RIGHT_DOWN;
    default:
      return 0;
    }
}

UINT g2pvt_compute_gensym_mouse_keycode(UINT message)
{
  BOOL ctrl, alt, shift, duble;
  UINT key;

  ctrl = (GetKeyState(VK_CONTROL) < 0);
  alt = (GetKeyState(VK_MENU) < 0);
  shift = (GetKeyState(VK_SHIFT) < 0);
  duble = (message==WM_LBUTTONDBLCLK) || (message==WM_MBUTTONDBLCLK) || (message ==WM_RBUTTONDBLCLK);
  key = g2_mouse_code_for_windows_code(message, 0);
  return key | 
    (ctrl ? X11_CONTROL_BIT : 0) | 
    (alt ? X11_ALTERNATE_BIT : 0) | 
    (shift ? X11_SHIFT_BIT : 0) |
    (duble ? X11_DOUBLE_BIT : 0);
}


/***************************************************************************\
*
*       g2_keycode_for_virtual_key(UINT)
*
*       PURPOSE: Translates a Windows virtual key code to a G2 key code.
*
*       COMMENTS:
*        This routine translates any virtual keys which NEVER generate
*       printing characters.  These we have to handle in WM_KEYDOWN.
*
\***************************************************************************/

UINT g2_keycode_for_virtual_key(UINT vk)
{
  switch (vk)
    {
    case VK_SPACE:                /* Let this one through. */
      return GENSYM_SPACE;

    case VK_BACK:
      return GENSYM_BACKSPACE;

    case VK_LEFT:                /* Arrow keys. */
      return GENSYM_LEFT_ARROW;
    case VK_RIGHT:
      return GENSYM_RIGHT_ARROW;
    case VK_UP:
      return GENSYM_UP_ARROW;
    case VK_DOWN:
      return GENSYM_DOWN_ARROW;

    case VK_CANCEL:                /* control-Break on an IBM keyboard. */
      return GENSYM_CANCEL;
    case VK_HELP:
      return GENSYM_HELP;
    case VK_INSERT:
      return GENSYM_INSERT;
    case VK_DELETE:                /* Do we get this in WM_CHAR, too? */
      return GENSYM_DELETE;
    case VK_SELECT:
      return GENSYM_SELECT;
    case VK_EXECUTE:
      return GENSYM_EXECUTE;

    case VK_TAB:
      return GENSYM_TAB;
    case VK_RETURN:
      return GENSYM_RETURN;

    case VK_ESCAPE:
      return GENSYM_ESCAPE;
    case VK_PRIOR:                /* Page up */
      return GENSYM_PRIOR;
    case VK_NEXT:                /* Page down */
      return GENSYM_NEXT;
    case VK_HOME:
      return GENSYM_HOME;
    case VK_END:
      return GENSYM_END;

    case VK_F1:
      return GENSYM_F1;
    case VK_F2:
      return GENSYM_F2;
    case VK_F3:
      return GENSYM_F3;
    case VK_F4:
      return GENSYM_F4;
    case VK_F5:
      return GENSYM_F5;
    case VK_F6:
      return GENSYM_F6;
    case VK_F7:
      return GENSYM_F7;
    case VK_F8:
      return GENSYM_F8;

    case VK_F9:
      return GENSYM_F9;
    case VK_F10:
      return GENSYM_F10;
    case VK_F11:
      return GENSYM_F11;
    case VK_F12:
      return GENSYM_F12;
    case VK_F13:
      return GENSYM_F13;
    case VK_F14:
      return GENSYM_F14;
    case VK_F15:
      return GENSYM_F15;
    case VK_F16:
      return GENSYM_F16;

    case VK_APPS:
      return GENSYM_MENU;
    case VK_PAUSE:                /* Labeled Pause/Break */
      return GENSYM_PAUSE;
    default:
      return 0;
    }
}



/***************************************************************************\
*
*       g2pvt_string_token(char *ptr, char *buffer, int max_buffer_length)
*
*       PURPOSE: Tokenizes the command line string into args delimited
*         by matching single or double quotes or by spaces.
*
*       COMMENTS:
*         This function mimics the strtok() function, with a different
*       interface. ptr is the pointer to the current position in the string
*       which is to be tokenized. buffer is the character pointer to the string
*       that will hold the token. max_buffer_length specifies the maximum
*       permissible length of the buffer. If ptr points to the end of the
*       string, then this function returns NULL. If ptr points to a single
*       or double quote, then all the characters upto the next matching quote
*       or the end of the string (whichever applicable) are copied as a token
*       into buffer. Else, whitespace is taken as the delimiter to get the
*       token.
*
\***************************************************************************/

char *g2pvt_string_token(ptr, buffer, max_buffer_length)
     char *ptr;
     char *buffer;
     int  max_buffer_length;
{
  int     i;
  char    delimiter;

  /* If the pointer is NULL, then return NULL. This may happen if this function
   * is called repeatedly on a string that has been tokenized.
   */

  if (ptr == NULL) {
      buffer[0] = '\0';
      return NULL;
  }

  /* Skip all the leading whitespace. */

  while (isspace(*ptr))
      ptr++;

  /* If the pointer is at the end of the string then copy the null character
   * into the buffer and return NULL.
   */

  if (*ptr == '\0') {
      buffer[0] = '\0';
      return NULL;
  }

  /* If the current character as pointed by the pointer is a single or double
   * quote then copy the characters following it into the buffer till the
   * matching single or double quote (whichever is applicable) is reached, or
   * till the end of the command line string. If the string terminates without
   * a matching quote, then all the characters from the starting of the quotes
   * to the end of the string are taken as one argument and no error message
   * is sent for the missing quotes.
   */

  if (*ptr == '"' || *ptr == '\'') {
      delimiter = *ptr;
      ptr++;
      for (i = 0; *ptr != delimiter && *ptr != '\0'; ptr++) {

          /* Copy characters for the argument into the buffer upto
           * the maximum permissible length for the argument. If the
           * argument exceeds the max_buffer_length -1, then truncate it.
           */

          if (i < max_buffer_length - 1) {
              buffer[i] = *ptr;
              i++;
          }
      }
      buffer[i] = '\0';

      /* If the pointer is at the delimiter i.e. quotes, then increment the
       * pointer to go past it. If the end of the string has been reached,
       * don't increment the pointer - as the subsequent call to the function
       * will return NULL.
       */

      if (*ptr == delimiter)
          ptr++;
  } else {

      /* If the first character is not a quote, then whitespace is taken
       * to be the delimiter.
       */

      for (i = 0; !(isspace(*ptr)) && *ptr != '\0'; ptr++) {
          if (i < max_buffer_length - 1) {
              buffer[i] = *ptr;
              i++;
          }
      }
      buffer[i] = '\0';
  }

  return ptr;
}


/***************************************************************************\
*
*         g2pvt_set_up_standard_files(HANDLE stream)
*
*         PURPOSE: sets up standard output and error to point to the
*         handle to either a log file or the console, which has been
*         allocated by the caller.
*
*         COMMENTS: Side-effects stdout and stderr. What we do is set
*         these to a FILE structure we create from a Microsoft HANDLE.
*         The reason for the * in the assignment is that stderr and
*         stdout are implemented as #define's in the header file, and
*         so you can't just assign to them in the obvious way.  This
*         code is used in a Microsoft example.  (It is unfortunate
*         that it is hard to mix and match POSIX and Microsoft
*         implementations, and that mostly you can't just use POSIX,
*         because something ends up not working.)
*
\***************************************************************************/
void g2pvt_set_up_standard_files()
{
    int fd;
    HANDLE hout;
    FILE *fp;

    if (g2pvt_outstream != NULL)
        hout = g2pvt_outstream;
    else
        hout = GetStdHandle(STD_OUTPUT_HANDLE);
    fd = _open_osfhandle((long)hout, _O_TEXT);
    fp = _fdopen(fd, "w");
    *stdout = *fp;
    *stderr = *fp;
}

/***************************************************************************\
*       g2ext_date_name_file (char *directory, char *extension)
*
*       PURPOSE: determine a log file name in directory, which has the
*       format <product>-yymmdd-ID.<extension>, where ID is a unique
*       identifier.
*
*       COMMENTS:
*
*       searches through the directory for files named
*       <product>-yymmdd*.extension in order to determine what the
*       next ID should be, and fills in the filename argument.
*
\***************************************************************************/

void g2ext_date_name_file (char *directory, char *extension)
{
  char temp[TEMP_FILE_LENGTH];
  char scaninput[TEMP_FILE_LENGTH];
  char *product_name;
  int ID, tempID = 0;
  HANDLE h;
  WIN32_FIND_DATA data;
  SYSTEMTIME today;
  char *maybeslash = "\\";

  if (directory[strlen(directory)-1]=='\\') {
    maybeslash = "";
  }

  switch(g2ext_product) {
  case TW_CMD: product_name = "TW";break;
  case G2_CMD:
  case ALL_CMD: product_name = "G2";break;
  default: product_name = "GNSM";break;
  }

  GetLocalTime(& today);
  sprintf(temp, "%s%s%s-%02d%02d%02d-*.%s", directory, maybeslash,
          product_name, today.wYear%100, today.wMonth, today.wDay,
          extension);
  sprintf(scaninput, "%s-%02d%02d%02d-%cd.%s", product_name,
          today.wYear%100, today.wMonth, today.wDay, '%',
          extension);

  h = FindFirstFile (temp, &data);
  if (h == INVALID_HANDLE_VALUE) {
    ID = 1;
  } else {
    ID = 0;
    do {
      sscanf(data.cFileName, scaninput, &tempID);
      ID = max (ID, tempID);
    } while (FindNextFile (h, &data));
    ID = ID + 1;
  }
  sprintf(logfile_name, "%s%s%s-%02d%02d%02d-%d.%s", directory, maybeslash,
          product_name, today.wYear%100, today.wMonth, today.wDay,
          ID, extension);
}


/***************************************************************************\
*       g2pvt_determine_default_logfile()
*
*       PURPOSE: automatically create the log file, if not specified
*       on commandline.
*
*       COMMENTS:
*
*       Calls the Microsoft function to generate the temporary
*       directory name.  Generates the filename as follows: the
*       product name plus a representation of the date plus a unique
*       identifier plus .log.
*
*       (above is desired behavior: at present uses Microsoft
*       temporary filename generator, which is inadequate because it
*       doesn't allow the user to specify the extension of the file,
*       and it uses .tmp.)
*
\***************************************************************************/

void g2pvt_determine_default_logfile ()
{
  char tmpdirectory[TEMP_FILE_LENGTH] = "";

  if (GetTempPath (TEMP_FILE_LENGTH, tmpdirectory))
    g2ext_date_name_file(tmpdirectory, "log");
}


/***************************************************************************\
*       void initialize_logfile ()
*
*       PURPOSE:
*
*       COMMENTS: we only support NT, but for the time being (and hopefully
*         not much longer), the non-NT code lives on here.  -jv, 1/20/05
*
\***************************************************************************/
static void initialize_logfile ()
{
  if (WIN32_IS_NT) {
    SECURITY_ATTRIBUTES sec;
    int fd;
    FILE *fp;

    /* give it the default security descriptor for child processes; we
       really only care about inherit handle */
    sec.nLength = sizeof(SECURITY_ATTRIBUTES);
    sec.lpSecurityDescriptor = NULL;
    sec.bInheritHandle = WIN32_IS_NT;
    g2pvt_outstream = CreateFile(logfile_name, GENERIC_READ|GENERIC_WRITE,
                                 FILE_SHARE_READ|FILE_SHARE_WRITE, &sec,
                                 CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (g2pvt_outstream == INVALID_HANDLE_VALUE)
      g2pvt_outstream = NULL;
    else {
      SetStdHandle(STD_OUTPUT_HANDLE,g2pvt_outstream);
      SetStdHandle(STD_ERROR_HANDLE,g2pvt_outstream);

      //We should open the osfhandle here to directly use the logfile handle,
      //Avoid the call to GetStdHandle which would return a wrong outstream. 
      fd = _open_osfhandle((long)g2pvt_outstream, _O_TEXT);
      fp = _fdopen(fd, "w");

      *stdout = *fp;
      *stderr = *fp;
    }
  } else {
    /* evidence suggests that Windows 95/98 do not properly
       implement the standard handle stuff as documented by
       Microsoft, while NT does.  Use the tried-and-true method from
       G2 5.1 -- yduJ, 3/00 */
    g2pvt_outstream = freopen(logfile_name,"w",stdout);
    freopen(logfile_name,"a",stderr);
  }
  logging_to_file = TRUE;
}


/***************************************************************************\
* int g2ext_gensym_winmain ()
*
* PURPOSE: to implement everything we actually want to do in our WinMain
*   function, but outside of WinMain.  This allows us to have alternate entry
*   points into the TW or G2 functionality.
*
* COMMENTS: in order to really use TW or G2 in different ways, we might still
*   need to break this up further, but at the very least, this alone lets us
*   link in all the code that makes up the product, while easily excluding the
*   WinMain function.
*
*   This function calls the application initialization routine and the instance
*   initialization routine.  It then executes a message retrieval and dispatch
*   loop that is the top-level control structure for the remainder of execution.
*   The loop is terminated when a WM_QUIT message is received, at which time
*   this function exits the application instance by returning the value passed
*   by PostQuitMessage().  If this function must abort before entering the
*   message loop, it returns FALSE.
*
\***************************************************************************/
int g2ext_gensym_winmain (HINSTANCE hInstance,
                          LPSTR lpCmdLine,
                          LPSTR productName)
{
  MSG msg;

  g2ext_check_windows_platform();

  if (g2ext_app_init(hInstance, lpCmdLine, productName) == FALSE)
    return 0;

  g2ext_app_run();
  /*NOTREACHED*/

  /* G2 is done.  Dispatch window messages in the standard way
     until we get a WM_QUIT */
  while (GetMessageW(&msg, (HWND)NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
  }

  return (msg.wParam);       /* Returns the value from PostQuitMessage */

}


static char *g2_tw_version_key = NULL;
extern char *g2pvt_get_FileVersion(char *moduleName);
static char *get_g2_tw_version_key()
{
  char *s;
  if (!g2_tw_version_key) {
    s = g2pvt_get_FileVersion(NULL);
    g2_tw_version_key = (char *)malloc(strlen(s)+1);
    strcpy(g2_tw_version_key, s);
  }
    
  return g2_tw_version_key;
}

/***************************************************************************\
* char *telewindows_sub_key ()
*
* PURPOSE: generate the registry key where Telewindows (and TWNG) should
*   register and unregister themselves.
*
\***************************************************************************/
char *telewindows_sub_key ()
{
  size_t sub_key_strlen = 0;
  char *rval = NULL;
  char *g2_tw_version_key = NULL;
  
  sub_key_strlen = strlen(TELEWINDOWS_KEY) + strlen(get_g2_tw_version_key()) + 2;
  rval = (char *) malloc(sub_key_strlen * sizeof(char));
  if (rval == NULL) {
    return NULL;
  }
  _snprintf(rval, sub_key_strlen, "%s%c%s", TELEWINDOWS_KEY,
            PATH_SEPARATOR_AS_CHAR, get_g2_tw_version_key());
  rval[sub_key_strlen] = 0;

  return rval;
}


/***************************************************************************\
*       enter_server_into_registry (BOOL)
*
*       PURPOSE: checks if this is a product which supports registration in the
*         Windows registry.  If it is, registers the product and exits.  Does
*         not allow the program itself to run.
*
*       COMMENTS: what should happen if someone runs a product (say, G2 8.1r0)
*         with "-regserver", but it doesn't know how to register itself?  We
*         could ignore it, or we could throw up a message box for the error and
*         then continue to run, but I think the right thing is to report the
*         error and exit.
*
*       What do we register for TW?  The installer registers:
*           HKLM\SOFTWARE\Gensym\Telewindows\8.1 Rev. 0\installDir
*       We also had thought of registering:
*           HKLM\Software\Microsoft\Windows\CurrentVersion\App Paths\tw.exe
*
*       For the purposes of the cab file, I've generated a UUID for tw.exe.  It
*       is: BEBC23AE-67A8-44AC-86AA-C9C5F059E08F
*
*       For Telewindows 8.0r0, the installer has hard-coded knowledge of TW, and
*       TW knows nothing about its own place in the registry.  That should
*       change.  TW should have the abiilty to register itself, and then the
*       bundle installer should be changed to, instead of doing something
*       complicated, simply run "tw.exe -regserver".  The "register all ActiveX
*       controls" batch file should also be changed to register TW (does that
*       imply it will have to be renamed?).
*
*       I was reminded of this when Federica pointed out that on machines which
*       want to use the workspace view, but don't want to use G2, they probably
*       don't want to install the bundle; under that circumstance, our
*       workaround (having the bundle installer do the registration directly)
*       does not suffice.
*
*       From MS Documentation: "If the server is packaged in an EXE module, then
*       the application wishing to register the server launches the EXE server
*       with the command-line argument /RegServer or -RegServer
*       (case-insensitive). If the application wishes to unregister the server,
*       it launches the EXE with the command-line argument /UnregServer or
*       -UnregServer. The self-registering EXE detects these command-line
*       arguments and invokes the same operations as a DLL would within
*       DllRegisterServer and DllUnregisterServer, respectively, registering its
*       module path under LocalServer32 instead of InprocServer32 or
*       InprocHandler32."
*
\***************************************************************************/
void enter_server_into_registry (BOOL silent_p)
{
  LONG hResult = E_FAIL;
  char szFileName[MAX_PATH];
  char *sub_key_name = NULL;
  HKEY hKey;
  DWORD Disposition;
  int nRet;

  switch (g2ext_product) {
  case TW_CMD:
    nRet = GetModuleFileName(NULL, szFileName, MAX_PATH);
    if (nRet != 0)
    {
      sub_key_name = telewindows_sub_key();
      if (sub_key_name) {
        hResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, sub_key_name, 0, TW_CLASS_ID,
                                 0, KEY_ALL_ACCESS, NULL, &hKey, &Disposition);
        /* sub_key_name is leaked */
      } else {
        hResult = ERROR_NOT_ENOUGH_MEMORY;
      }
      if (hResult == ERROR_SUCCESS)
      {
#ifdef CODEJOCK
        hResult = RegSetValueEx(hKey, KEY_VALUE_NAME_TWNG, 0, REG_SZ,
                                szFileName, nRet);
#else
        hResult = RegSetValueEx(hKey, KEY_VALUE_NAME_ORIG, 0, REG_SZ,
                                szFileName, nRet);
#endif
      }
    }
    if (hResult != ERROR_SUCCESS)
    {
      /* are we supposed to consider silent_p here? */
      g2pvt_inform_user(0, "Telewindows",
			"Error: Attempt to register Telewindows failed: %s",
			g2pvt_get_last_error_string());
      exit(-7);
    }
    if (!silent_p)
    {
      MessageBox(NULL, "Telewindows registration succeeded.",
                 "Telewindows", MB_OK);
    }
    exit(0);
  case G2_CMD:
    MessageBox(NULL, "Error: G2 does not self-register.", "G2", MB_OK);
    exit(-4);
  case GSI_CMD:
    MessageBox(NULL, "Error: GSI bridges do not self-register.", "GSI", MB_OK);
    exit(-4);
  default:
    MessageBox(NULL, "Error: this product does not know how to self-register.",
               "Gensym", MB_OK);
    exit(-4);
  }
}


/***************************************************************************\
*       remove_server_from_registry (BOOL)
*
*       PURPOSE:
*
*       COMMENTS: regarding the error message, I intentionally didn't change
*         them to talk about "unregistering".  That might make it seem that
*         it could register but not unregister.  I think it's better to have
*         the error message be the same whether it was asked to register or
*         unregister.
*
\***************************************************************************/
void remove_server_from_registry (BOOL silent_p)
{
  HRESULT hResult;
  HKEY hKey = NULL;
  char *sub_key_name = NULL;
  DWORD nSubKeys, nValues;

  switch (g2ext_product) {
  case TW_CMD:
    sub_key_name = telewindows_sub_key();
    if (sub_key_name) {
      hResult = RegOpenKeyEx(
               HKEY_LOCAL_MACHINE,
               sub_key_name,
               0,
               KEY_ALL_ACCESS,
               &hKey );
      if (hKey != NULL) {

#ifdef CODEJOCK
	hResult = RegDeleteValue(hKey, KEY_VALUE_NAME_TWNG);
#else
	hResult = RegDeleteValue(hKey, KEY_VALUE_NAME_ORIG);
#endif
	if (hResult == ERROR_SUCCESS) {
	  /* Value deleted, now query the key. */
	  hResult= RegQueryInfoKey(hKey, // handle to key to query
				   NULL, NULL, NULL,
				   &nSubKeys, // number of subkeys
				   NULL, NULL,
				   &nValues, // number of value entries
				   NULL, NULL, NULL, NULL);
	  if (hResult == ERROR_SUCCESS) {
	    /* If empty, kill key too. */
	    if (nValues == 0 && nSubKeys == 0)
	      hResult = RegDeleteKey(HKEY_LOCAL_MACHINE, (LPCTSTR) sub_key_name);
	  }
	}
      }
      /* sub_key_name is leaked */
    } else {
      hResult = ERROR_NOT_ENOUGH_MEMORY;
    }
    if (hResult != ERROR_SUCCESS)
    {
      /* are we supposed to consider silent_p here? */
      MessageBox(NULL, "Attempt to unregister Telewindows failed.",
                 "Telewindows", MB_OK);
      exit(-6);
    }
    if (!silent_p)
    {
      MessageBox(NULL, "Telewindows unregistration succeeded.",
                 "Telewindows", MB_OK);
    }
    exit(0);
  case G2_CMD:
    MessageBox(NULL, "Error: G2 does not self-register.", "G2", MB_OK);
    exit(-5);
  case GSI_CMD:
    MessageBox(NULL, "Error: GSI bridges do not self-register.", "GSI", MB_OK);
    exit(-5);
  default:
    MessageBox(NULL, "Error: this product does not know how to self-register.",
               "Gensym", MB_OK);
    exit(-5);
  }
}


/*************************************************************************
*  BOOL lookup_tw_key_value (HKEY vs_key, LPCSTR value_name, char *tw_dir,
*                            LPDWORD buf_len)
*
*  Returns: TRUE on success
*
*  Comments: 
*************************************************************************/
static BOOL lookup_tw_key_value (HKEY vs_key, LPCSTR value_name, char *tw_dir,
                                 LPDWORD buf_len)
{
  LONG kstatus;
  DWORD return_type;

  kstatus = RegQueryValueEx(vs_key, value_name, NULL, &return_type,
                            tw_dir, buf_len);
  if (kstatus != ERROR_SUCCESS) {
    g2pvt_gprintf(G2PVT_ERROR, "failed getting value of %s subkey, status = 0x%x\n",
                  value_name, kstatus);
    return FALSE;
  }
  if (return_type != REG_SZ) {
    g2pvt_gprintf(G2PVT_ERROR, "received unknown type of data, %d, from %s subkey\n",
                  return_type, value_name);
    return FALSE;
  }
  return TRUE;
}


/*************************************************************************
*  BOOL read_windows_registry (PTSTR p_buf, size_t p_length)
*
*  We check the registry to find where Telewindows is installed.  We expect
*  the G2 Bundle Installer to write the directory into the following key:
*     HKEY_LOCAL_MACHINE\SOFTWARE\Gensym\Telewindows\<version>\installDir
*
*  Returns: TRUE on success
*
*  Comments: this function and those it calls "know" that the buffer we are using is
*    MAX_PATH characters long.  This should be improved.
*************************************************************************/
static BOOL read_windows_registry (PTSTR p_buf, size_t p_length)
{
  HKEY tw_key, vs_key;
  LONG kstatus;
  BOOL got_tw_value = FALSE;
  PTSTR szTwDir;
  BOOL need_slash = TRUE;
  unsigned long twdir_len = MAX_PATH;
  char tw_install_dir[MAX_PATH];

  kstatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TELEWINDOWS_KEY, 0, KEY_READ|KEY_WOW64_32KEY, &tw_key);
  if (kstatus != ERROR_SUCCESS) {
    g2pvt_gprintf(G2PVT_ERROR, "failed to open %s key\n", TELEWINDOWS_KEY);
    return FALSE;
  }
  /* At this point, maybe we should query to see what versions are available,
   * instead of just looking for 8.0a0.  To be improved.
   */
  kstatus = RegOpenKeyEx(tw_key, get_g2_tw_version_key(), 0, KEY_READ|KEY_WOW64_32KEY, &vs_key);
  if (kstatus != ERROR_SUCCESS) {
    g2pvt_gprintf(G2PVT_ERROR, "failed to open %s key\n", get_g2_tw_version_key());
    RegCloseKey(tw_key);
    return FALSE;
  }

  got_tw_value = lookup_tw_key_value(vs_key, KEY_VALUE_NAME_TWNG,
                                     tw_install_dir, &twdir_len);
  if (!got_tw_value) {
    /* We were unable to find registration info for TWNG, which is always our
     * first choice; try standard TW as a backup plan.
     */
    got_tw_value = lookup_tw_key_value(vs_key, KEY_VALUE_NAME_ORIG,
                                       tw_install_dir, &twdir_len);
  }
  RegCloseKey(vs_key);
  RegCloseKey(tw_key);
  if (!got_tw_value) {
    return FALSE;
  }

  szTwDir = (PTSTR) tw_install_dir;
  /* There's one little thing about the return values I don't quite understand.
   * The length returned seems to be one too long.  Well, whatever.  Adjust
   * length so that szTwDir[len]==0, and szTwDir[len-1]!=0.
   */
  while (szTwDir[twdir_len - 1] == 0) twdir_len--;
  need_slash = (szTwDir[twdir_len - 1] != PATH_SEPARATOR_AS_CHAR);

  if (twdir_len > p_length) {
    g2pvt_gprintf(G2PVT_ERROR, "pathname of install dir too long to use for executable\n");
    return FALSE;
  }

  strncpy(p_buf, (PTSTR) tw_install_dir, twdir_len);
  p_buf[twdir_len] = '\0';
  return TRUE;
}


/*************************************************************************
*  long g2ext_run_telewindows_here ()
*
*  Purpose:
*  Entry:
*  Returns:0 on success, -1 on failure
*  Comments:
*************************************************************************/
long g2ext_run_telewindows_here ()
{
  char port_string[10];
  char tw_location[MAX_PATH];
  char *command_line = NULL;
  BOOL bcp = FALSE;
  PROCESS_INFORMATION pinfo;
  STARTUPINFO si;
  int len;

  len = g2pvt_network_listener_port(g2ext_primary_listener, port_string, 10);
  if (len == -1) {
    g2pvt_modeless_error("Unable to determine port number of G2!");
  }

  bcp = read_windows_registry(tw_location, MAX_PATH);
  if (FALSE == bcp) {
    g2pvt_modeless_inform("Unable to obtain Telewindows location from the registry");
    return -1;
  }

  command_line = (char *)malloc(MAX_PATH * sizeof(char));
  _snprintf(command_line, MAX_PATH, "TW localhost %s%s", 
	    port_string,
	    g2ext_primary_listener->secure_connection_requested ? " -secure" : "");

  ZeroMemory((PVOID)&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);
  ZeroMemory((PVOID)&pinfo, sizeof(PROCESS_INFORMATION));
  bcp = CreateProcess(tw_location, command_line,
                      NULL, NULL, FALSE, DETACHED_PROCESS,
                      NULL, NULL, &si, &pinfo);
  if (0 == bcp) {
    g2pvt_modeless_error("Unable to launch Telewindows (\"%s\")", tw_location);
    return -1;
  }
  return 0;
}


/*************************************************************************
*  void possibly_shut_down_g2 ()
*
*  Purpose:
*  Entry:
*  Returns:
*  Comments:
*************************************************************************/
static void possibly_shut_down_g2 (HWND hwnd)
{
  g2pvt_modeless_msgbox(hwnd, SHUT_DOWN_QUESTION, "G2", MB_OKCANCEL | MB_ICONEXCLAMATION, WM_CLOSE);
}


/*************************************************************************
*  LRESULT g2pvt_taskbar_command (HWND hwnd, WPARAM wParam, LPARAM lParam)
*
*  Purpose:
*  Entry:
*  Returns:
*  Comments:
*************************************************************************/
LRESULT g2pvt_taskbar_command (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  int wmId, wmEvent;

  wmId    = LOWORD(wParam);
  wmEvent = HIWORD(wParam);

  switch (wmId) {
  case GWM_CONNECT:
  case IDOK:
    g2ext_run_telewindows_here();
    break;
  case GWM_EXIT:
    possibly_shut_down_g2(hwnd);
    break;
  default:
    break;
  }

  return TRUE;
}


/***************************************************************************\
*       void set_up_and_handle_program_args (LPSTR lpCmdLine)
*
*       PURPOSE:
*
*       COMMENTS:
*         We should support the forward slash, as well as the hyphen, for ALL
*         command line options on Windows.  (Suggestion HQ-4281781, "mswin
*         command-line arguments should work with slashes as well as hyphens")
*         We haven't implemented that, although it is likely very simple to do.
*         But for /regserver and /unregserver, I think it is important enough to
*         make a special case until the general solution is here.  -jv, 1/20/05
*
\***************************************************************************/
static void set_up_and_handle_program_args (LPSTR lpCmdLine)
{
  char    *psOptions, *psOptionsPtr, *psToken, *next_arg;
  char    buf[_MAX_PATH];
  int     max_arg_length, i;
  BOOL    reg_server_p = FALSE, unreg_server_p = FALSE, silent_p = FALSE;

  /*****************************************************************************
   * This section finds the file name of "this" module.  This can be retrieved *
   * by the user with the g2-get-command-line-argument-from-launch system      *
   * procedure.  -jv, 1/25/05                                                  *
   ****************************************************************************/
  buf[0] = '\0';
  if (GetModuleFileName(NULL, buf, sizeof(buf)/sizeof(char)) == 0)
  {
    fprintf(stderr, "GetModuleFileName failed: %d\n", GetLastError());
  }

  /****************************************************************************
   * This section builds up the global variable "program_args".               *
   ****************************************************************************/
  program_args[0] = strdup(buf);
  max_arg_length = strlen(lpCmdLine) + 1;
  psOptions = malloc (max_arg_length * sizeof (char));
  strcpy(psOptions, lpCmdLine);
  psToken = malloc (max_arg_length * sizeof (char));
  psOptionsPtr = g2pvt_string_token(psOptions, psToken, max_arg_length);

  program_argc = 1;
  while ((psOptionsPtr != NULL) && (program_argc < MAX_ARGS))
  {
    program_args[program_argc] = malloc((strlen(psToken) + 1) * sizeof(char));
    strcpy (program_args[program_argc], psToken);
    program_argc++;
    psOptionsPtr = g2pvt_string_token(psOptionsPtr, psToken, max_arg_length);
  }

  free(psToken);
  free(psOptions);


  /****************************************************************************
   * This section iterates over the program arguments, and checks for Windows-
   * specific flags.  Since commandline options should be case-insensitive, we
   * use case-insensitive string comparison (_stricmp).
   ****************************************************************************/
  i = 0;
  while (++i < program_argc) {
    next_arg = program_args[i];

    if ((0==_stricmp(next_arg, "-REGSERVER")) ||
        (0==_stricmp(next_arg, "/REGSERVER"))) {
      reg_server_p = TRUE;
    } else if ((0==_stricmp(next_arg, "-UNREGSERVER")) ||
               (0==_stricmp(next_arg, "/UNREGSERVER"))) {
      unreg_server_p = TRUE;
    } else if ((0==_stricmp(next_arg, "-s")) ||
               (0==_stricmp(next_arg, "/s"))) {
      silent_p = TRUE;
    } else if (0==_stricmp(next_arg, "-SCREENLOCK")) {
      screenlock = TRUE;
    } else if (0==_stricmp(next_arg, "-NO-TRAY")) {
      g2pvt_use_status_area_icon = FALSE;
    } else if (0==_stricmp(next_arg, "-NO-CONFIRM-ON-EXIT")) {
      ConfirmProgramExit = FALSE;
    } else if ((0==_stricmp(next_arg, "-NO-LOG")) ||
               (0==_stricmp(next_arg, "-HELP"))) {
      logging_to_file = FALSE;
    } else if (0==_stricmp(next_arg, "-LOG")) {
      if (i < program_argc - 1) {
        /* Note, increment loop variable here */
        strcpy(logfile_name, program_args[++i]);
      }
      /* Else, should we give warning?  I (jv) think so, but we never have. */
    } else if (0==_stricmp(next_arg, "-ICON")) {
      if (i < program_argc - 1) {
        /* Note, increment loop variable here */
        strcpy(icon_name, program_args[++i]);
      }
    } else if (0==_stricmp(next_arg, "-CLOSEBOX")) {
      /* Note, increment loop variable here */
      next_arg = program_args[++i];
      if (_stricmp(next_arg, "enable")==0)
        g2pvt_closebox = 1;
      else if (_stricmp(next_arg, "disable")==0)
        g2pvt_closebox = 0;
      else if (_stricmp(next_arg, "default")==0)
        ;
      /* It would be nice to warn about mispellings here, but stdout is not
         usable at this point! */
    } else if (0==_stricmp(next_arg, "-MINIMIZE")) {
      /* Note, increment loop variable here */
      next_arg = program_args[++i];
      if (_stricmp(next_arg, "enable")==0)
        g2pvt_minimize = 1;
      else if (_stricmp(next_arg, "disable")==0)
        g2pvt_minimize = 0;
    } else if (0==_stricmp(next_arg, "-USELDAP")) {
        g2use_ldap = 1;
    }
  }

  if (reg_server_p) {
      enter_server_into_registry(silent_p);
  }
  if (unreg_server_p) {
    remove_server_from_registry(silent_p);
  }
}

/***************************************************************************\
*       ConsoleEventHandler(code)
*
*       PURPOSE: Called by Windows, from another thread, when some sort of
*                "close" event occurs on the console.
*
*       COMMENTS:
*
*       Return TRUE if handled, FALSE to let the default handlers run.
*
\***************************************************************************/
static BOOL WINAPI ConsoleEventHandler(DWORD fdwCtrlType) 
{ 
  switch (fdwCtrlType) {
    case CTRL_C_EVENT: 
    case CTRL_BREAK_EVENT: 
    case CTRL_LOGOFF_EVENT: 
    case CTRL_CLOSE_EVENT: 
    case CTRL_SHUTDOWN_EVENT:

      /* Windows by default calls ExitProcess(). That doesn't seem to allow all
       * of the cleanup routines to run for loaded DLLs, such as MFC.  If our
       * frame window still exists, shut down gently by sending it a WM_CLOSE,
       * after ensuring we won't get stuck waiting for a return key. If the
       * frame window is already destroyed, then the cleanups have already
       * happened, and we can let the default handler call ExitProcess(), after
       * cleaning up our tray icon, is any. If the frame window never existed,
       * because we are running -no-window, then we must be G2, and can also
       * just call ExitProcess(). If G2 ever uses MFC, this may have to be
       * revisited. -fmw, 4/24/05 */

      ConfirmProgramExit = FALSE;
      if(IsWindow(hwndFrame)) {
	PostMessage(hwndFrame, WM_CLOSE, 0, 0);
	return TRUE; 
      }
      /* Ensure the tray icon is cleaned up. */
      g2pvt_windows_shutdown();
  }
  return FALSE; 
}

/***************************************************************************\
*       g2ext_app_init (HINSTANCE hInstance, LPSTR lpCmdLine, LPSTR productName)
*
*       PURPOSE: Initialize the current LISP application.
*
*       COMMENTS:
*
*       Returns TRUE on success, FALSE on failure.
*
\***************************************************************************/
int g2ext_app_init (HINSTANCE hInstance,
                    LPSTR lpCmdLine,
                    LPSTR productName)
{
  char buf[_MAX_PATH] = "";

  ne_use_sck = FALSE;

  g2ext_set_gensym_product(productName);

  set_up_and_handle_program_args(lpCmdLine);

  if (g2ext_return_environment_variable("G2_NO_LOG", buf) == SUCCESS && buf[0] != '0')
    logging_to_file = FALSE;

  /* should test to make sure that we have not given a log file, but also said not to log. */
  /* if we haven't said not to log (with -no-log), but we haven't supplied
     one, figure out a default name */
  if (logging_to_file && strlen(logfile_name)== 0) {
    g2pvt_determine_default_logfile();
  }

  /* Perform Win32-specific initializations */
  if (!g2pvt_win32_init(hInstance))
      return (FALSE);                /* Exits if unable to initialize   */

  if (strlen(logfile_name)) {
    initialize_logfile();
  }

  /* Set the default keyboard layout according to what it was in the
     the current thread that started G2.  To be used as arg to
     ToAsciiEx.  Consider having it be the user default keyboard
     layout.  This is only to be used for mapping control keys (i.e.,
     shortcut keys), as recommended by Microsoft.  See Kano book, page
     180. -mhd */
  default_hkl = GetKeyboardLayout (0); /* 0 = for current thread */

  if ((g2pvt_outstream == NULL) && AllocConsole()) {
    g2pvt_set_up_standard_files();
    logging_to_file = FALSE;

    if (strlen(logfile_name))
      printf("Could not open logfile \"%s\".\n\n", logfile_name);

    SetConsoleCtrlHandler(ConsoleEventHandler, TRUE);

    printf("Initializing...\n");
  }

  /* Set up connection-completion callback for SSL (TW-only) */
  if(!strcmp(productName,"TW") || !strcmp(productName,"TWNG"))
    g2pvt_ssl_set_callback(g2pvt_note_ssl_connection);

  return TRUE;
}

/***************************************************************************\
*       g2ext_app_run()
*
*       PURPOSE: Runs the current LISP application. Must be initialized first
*                with g2ext_app_init().
*
*       COMMENTS:
*
*       Currently never returns, since the Chestnut-generated main calls lexit().
*
\***************************************************************************/
int g2ext_app_run(void)
{
  /* The main() function resides in g2/c/main.c or tw/c/main.c */
  return main(program_argc, program_args);
  /*NOTREACHED*/
}


/***************************************************************************\
 * For use by twng.
\***************************************************************************/

int g2ext_app_set_windows(HWND frame, HWND client)
{
  if (frame && client) {         /* Tell g2ext_x11_initialize to use provided windows. */
    Frame_is_MFC = TRUE;
    hwndFrame = frame;
    hwndClient = client;
  }
  return 1;
}

void g2ext_app_exit(void)
{
  if (hwndFrame)
    g2pvt_on_wm_destroy(hwndFrame, WM_DESTROY, 0, 0);
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      UUID Generation
 %
 % Description:
 %   This function is for creating UUIDs on Windows.  It is stubbed out
 %   in xwindows.c on Unix and various bridge products on windows.
 % Notes:
 %   This is not particularly "main", and "msmain.c" might not be the ideal spot
 %   for it, but I'm moving this here from cprim.c because the functionality is
 %   not necessary for GSI, and we want to remove the GSI false depenedency on
 %   rpcrt4.  I looked for a better file which is in libcprim but not libtcp,
 %   but didn't find one.  -jv, 3/13/05
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %   Moved g2ext_uuid_create back to cprim, changed name of this function to
 %      g2pvt_uuid_create.  Hacked comments.  --yduJ, 3/14/05
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*
 * The function g2pvt_uuid_create should only be called from g2ext_uuid_create,
 * defined in cprim.c.  It fills in the UUID structure.
 */

long g2pvt_uuid_create (UUID *uuid)
{
  static RPC_STATUS (RPC_ENTRY *pUuidCreate)(UUID *Uuid) = NULL;
  OSVERSIONINFO osvi;
  HMODULE hModule;

  if (pUuidCreate == NULL) {
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);

    /* For NT5 or greater, try to use the faster, unobfuscated UuidCreateSequential */
    if ((osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osvi.dwMajorVersion >= 5)) {
      hModule = GetModuleHandle("rpcrt4.dll");

      if (hModule != NULL)
        (FARPROC) pUuidCreate = GetProcAddress(hModule, "UuidCreateSequential");
    }

    if (pUuidCreate == NULL)
      pUuidCreate = UuidCreate;
  }

  return (long)pUuidCreate(uuid);
}
