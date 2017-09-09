/*-*- Mode: C++ -*-
 *
 * Module MDI: MDI (and SDI) modes for Windows
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 */

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
#include "dyndlgs.h"

/* RTL headers */
#if SI_SUPPORT_THREAD
#include "special.h"
#include "uspecial.h"
#endif

/*************************************************************************/
/* DEFINES                                                               */
/*************************************************************************/
#define IDM_FIRSTCHILD   50000
#define MTRACE G2TRACE
#define MAGIC_CHART_ID 999
#define PEWN_DESTROYED (WM_USER + 4000) // Don't overlap any PEWN_xxx codes.

//#ifdef WINVER 
//#undef WINVER
//#endif 
//
//#ifdef _WIN32_WINNT 
//#undef _WIN32_WINNT
//#endif
//
//#define WINVER 0x0501 
//#define _WIN32_WINNT 0x0501 
/*************************************************************************/
/* EXTERNS                                                               */
/*************************************************************************/
extern BOOL g2pvt_on_wm_mouse   (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
extern BOOL g2pvt_on_wm_keyboard(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
extern BOOL g2pvt_on_wm_destroy (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
extern BOOL g2pvt_on_wm_setcursor(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
extern void g2pvt_menu_size(int menu_size);

extern int screenlock;
extern int g2ext_product;
extern int g2pvt_minimize;

extern HWND hwndStatus;		/* Optional statusbar */
extern HWND hwndProgress;	/* Optional progress bar */
extern HMENU hViewMenu;
extern HMENU hWindowMenu;
extern HMENU hHelpMenu;
extern BOOL bViewStatusbar;

extern HMENU hMenuInit;
extern HMENU hMenuInitWindow;
 
extern void g2pvt_show_tw_help(HWND hwnd);
extern BOOL g2pvt_help_available_p(void);

extern HWND g2pvt_create_status_bar(HWND);
extern HWND g2pvt_create_progress_bar(HWND);

extern BOOL insert_activex_object(HWND);

extern void g2pvt_size_custom_menu_item(HDC hdc, G2_MENU_ITEM *item, LONG *cx, LONG *cy);
extern void g2pvt_draw_custom_menu_item(HMENU menu, HDC hdc, UINT itemState, UINT itemID,
					RECT *r, G2_MENU_ITEM *item);

extern void g2pvt_set_statusbar_text(LPCWSTR string);
extern void g2pvt_resize_status_bar(HWND, RECT *);

extern LPWSTR g2pvt_nms_help_string(int nId); /* Get help string for menu item id */

extern int nms_flag;
extern long g2ext_nms_set_flag(long);

extern long g2ext_sys_sleep(long);

extern HWND g2pvt_create_workspace_view(long handle, HWND client, LPWSTR title, DWORD style, RECT* r);
extern void g2pvt_set_workspace_view_background_color(HWND hwnd, COLORREF color);

extern HWND g2pvt_create_editor(long handle, LPWSTR title, DWORD style, DWORD exStyle, RECT* pRect, BOOL topLevel);
extern long g2ext_write_string_to_console(char * string);
extern void g2pvt_ensure_mouse_hover_tracking(HWND hwnd);

#ifdef GENFLEX
extern HWND GetHandleOfGenflex();
extern long (*genflex_g2ext_manage_editor_callback)(long, long, LPWSTR, long, long);
extern long (*genflex_g2ext_debugger_step_callback)(long, long, LPWSTR, LPWSTR);

struct Stack_info;
extern long (*genflex_g2ext_debug_info_received_callback)(Stack_info);
extern HWND genflex_g2pvt_create_editor(long, LPWSTR, long, long, /*RECT* pRect,*/ BOOL);
extern long (*genflex_g2ext_x11_manage_window_callback)(long, long,
			     long, long, long, long,
			     LPWSTR);
				 
struct Tree_node_view_info;
extern long (*genflex_g2ext_tree_node_view_info_received_callback)(Tree_node_view_info);
extern HWND genflex_g2pvt_create_editor(long, LPWSTR, long, long, /*RECT* pRect,*/ BOOL);
extern long (*genflex_g2ext_x11_manage_window_callback)(long, long,
			     long, long, long, long,
			     LPWSTR);
extern long (*genflex_g2ext_remove_tree_nodes_range_callback)(LPWSTR);				 
#endif

/*************************************************************************/
/* Global Variables                                                      */
/*************************************************************************/

/* This variable is true when running a modal G2 event cycle
 * inside of g2pvt_simple_rpc. It is used by TWNG to filter the
 * set of Windows messages it allows in. */
BOOL Inside_simple_rpc = FALSE;

/* This variable is true if we are inside a modal scrollbar loop
 * for some workspace-view window. */
BOOL Inside_modal_scrollbar_loop = FALSE;

/*************************************************************************/
/* LISP Externs                                                          */
/*************************************************************************/

/* Lisp function. Returns the NMS handle of menu with given Win32 HMENU handle,
 * if it exists and the given flag bit is set. Otherwise, returns 0. */
extern long nms_handle_if_flag_bit(long hmenu_high, long hmenu_low, long flag);
extern long nms_id_for_menu(long hmenu_high, long hmenu_low);

#if SI_SUPPORT_THREAD

DECLARE_VARIABLE(Inside_handle_event);
#define Inside_handle_event SPECIAL_VALUE(Inside_handle_event)

#else

extern Gensym_Long Inside_handle_event; /* LISP special variable. */

#endif

/*************************************************************************/
/* Forward Refs                                                          */
/*************************************************************************/
extern HWND g2pvt_create_client_window(HWND parent);
static int on_menuselect(HWND hwnd, WPARAM wParam, LPARAM lParam);
void g2pvt_on_chart_notification(HWND hwnd, HWND hPE, int code);


/* 
 * Win32/GDI Utilities
 */

/* Draw a thick frame around inside of rect using brush. */
static void draw_inside_borders(HDC hdc, RECT *r, int thickness, HBRUSH hbr)
{
  RECT t = *r;
  t.bottom = r->top + thickness;
  FillRect(hdc, &t, hbr);	/* top */

  t.top = r->bottom - thickness;
  t.bottom = r->bottom;
  FillRect(hdc, &t, hbr);	/* bottom */

  t.top = r->top + thickness;
  t.bottom = r->bottom - thickness;
  t.right = r->left + thickness;
  FillRect(hdc, &t, hbr);	/* left */

  t.left = r->right - thickness;
  t.right = r->right;
  FillRect(hdc, &t, hbr);	/* right */
}

/* If maximized child is present, restore it. */
static void mdi_restore()
{
  HWND active = NULL;
  BOOL maxed = FALSE;

  active = (HWND) SendMessage(hwndClient, WM_MDIGETACTIVE, 0, (LPARAM)&maxed);
  if(active && maxed)
    SendMessage(hwndClient, WM_MDIRESTORE, (WPARAM)active, 0);
}

/* Return maximized MDI child window, if any. */
static HWND get_maximized_child()
{
  HWND active = NULL;
  BOOL maxed = FALSE;
  if(Frame_is_MDI && hwndClient)
    active = (HWND) SendMessage(hwndClient, WM_MDIGETACTIVE, 0, (LPARAM)&maxed);
  return (active && maxed) ? active : NULL;
}

/* GENSYMCID-1215: twng locks up (workaround) */
void fixing_twng_locks_up()
{
  HWND maximized_child = get_maximized_child();
  if (maximized_child != NULL) {
    SendMessage(hwndClient, WM_MDIRESTORE, (WPARAM)maximized_child, 0);
    SendMessage(hwndClient, WM_MDIMAXIMIZE, (WPARAM)maximized_child, 0);
  }
}

/* Convert client rect to window rect, for given style. */
void ClientToWindowEx(RECT *r, DWORD style, DWORD exStyle)
{
  AdjustWindowRectEx(r, style, FALSE, exStyle);
  if(style&WS_VSCROLL)
    r->right += GetSystemMetrics(SM_CXVSCROLL);
  if(style&WS_HSCROLL)
    r->bottom += GetSystemMetrics(SM_CYHSCROLL);
}

#ifdef _DEBUG
void PrintFont(char *label, HFONT hFont)
{
  LOGFONT lf = {0};
  GetObject(hFont, sizeof(LOGFONT), (LPVOID)&lf);
  g2pvt_trace("%s %08x '%s' %d\n",
	      label, hFont, lf.lfFaceName, MulDiv(-lf.lfHeight, 72, GetDeviceCaps(GetDC(NULL),LOGPIXELSY)));
}
#endif

/*
 * System Metrics
 */

static HFONT hGuiFont = NULL;
static LOGFONTW lfGuiFont;

HFONT GetDefaultGuiFont(LPWSTR *pFaceName, int *pPointSize)
{
  if(!hGuiFont) {
    NONCLIENTMETRICS ncm = {0};
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    if(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0))
      hGuiFont = CreateFontIndirect(&ncm.lfMessageFont);
    else
      hGuiFont = GetStockObject(DEFAULT_GUI_FONT);
  }

  if(pFaceName || pPointSize) {
    HDC hdc = GetDC(NULL);
    GetObjectW(hGuiFont, sizeof(LOGFONTW), (LPVOID)&lfGuiFont);

    if(pFaceName) *pFaceName = lfGuiFont.lfFaceName;
    if(pPointSize) *pPointSize = MulDiv(-lfGuiFont.lfHeight, 72, GetDeviceCaps(hdc,LOGPIXELSY));
    ReleaseDC(NULL,hdc);
  }

  return hGuiFont;
}

void g2pvt_decache_system_settings(UINT uFlags)
{
  // NOTE: The font may currently be in use, so we can't just delete it. So we
  // leak an HFONT whenever system settings change. Not a big deal.
  if(uFlags == SPI_SETNONCLIENTMETRICS)
    hGuiFont = NULL;
}

/* In default GUI font. */
static int pixels_per_hundred_dialog_units(BOOL xAxis)
{
  static int px, py;

  if(px==0) {
    HDC hdc = GetDC(NULL);
    HFONT hFont = GetDefaultGuiFont(NULL, NULL);
    HFONT hFontOld;
    TEXTMETRIC tm;
    SIZE size;
    int avgWidth, avgHeight;

    hFontOld = SelectObject(hdc, hFont);
    GetTextMetrics(hdc,&tm);
    GetTextExtentPoint32(hdc,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &size);
    SelectObject(hdc, hFontOld);
    ReleaseDC(NULL, hdc);
    avgWidth = (size.cx/26+1)/2;
    avgHeight = (WORD)tm.tmHeight;
    px = (100 * avgWidth + 2) / 4;	 /* Scaled by 100 */
    py = (100 * avgHeight + 4) / 8;
  }
  return xAxis ? px : py;
}

/* Return a Windows system metric, wg SM_CXVSCROLL, SM_CYHSCROLL, SM_CYCAPTION,
 * etc. We add own own new system metrics for scaled pixels per dialog unit. */
long g2ext_get_system_metric(long code)
{
  switch(code) {
   case SM_CXDIALOG:
     return pixels_per_hundred_dialog_units(TRUE);
   case SM_CYDIALOG:
     return pixels_per_hundred_dialog_units(FALSE);
   default:
     return GetSystemMetrics(code);
  }
}

/* Convert proposed client rect to required window rect, both in parent coor. */
static void ClientToWindow(HWND hwnd, RECT *r)
{
  ClientToWindowEx(r, GetWindowLong(hwnd,GWL_STYLE) & ~WS_ICONIC,
		      GetWindowLong(hwnd,GWL_EXSTYLE));
}

/* Same as SetWindowPos except takes an LPRECT and handles iconified windows by
 * changing the saved dimensions in the WINDOWPLACEMENT struct instead of the
 * actual window. */
static void SetWindowPosExx(HWND hwnd, HWND after, LPRECT r, UINT flags)
{
  WINDOWPLACEMENT wp;
  wp.length = sizeof(WINDOWPLACEMENT);

  if(!IsIconic(hwnd)) {
    if(!SetWindowPos(hwnd,after,r->left,r->top,r->right-r->left,r->bottom-r->top,flags))
      fprintf(stderr, "SetWindowPos failed: %s\n", g2pvt_get_last_error_string());

  } else if(!GetWindowPlacement(hwnd, &wp)) {
    fprintf(stderr,"GetWindowPlacement failed: %s\n", g2pvt_get_last_error_string());
    return;
  }
  else {
    MTRACE("SetWindowPlacement\n");
    wp.rcNormalPosition = *r;
    SetWindowPlacement(hwnd,&wp);
  }
}

/* Analogous function for getting the client rectangle even when minimized. */
static void GetClientRectExx(HWND hwnd, LPRECT pRect)
{
  if(! IsIconic(hwnd))
    GetClientRect(hwnd,pRect);
  else {
    WINDOWPLACEMENT wp;
    RECT r = {0};
    wp.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(hwnd, &wp);
    ClientToWindow(hwnd,&r);	     /* Get NC border sizes. */
    pRect->left = 0;
    pRect->top = 0;
    pRect->right = wp.rcNormalPosition.right - wp.rcNormalPosition.left - (r.right - r.left);
    pRect->bottom = wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - (r.bottom - r.top);
  }
}

/* Retrieve the user value passed to CreateWindowEx */
static int getCreateParam(LPARAM lParam)
{
  CREATESTRUCTW *lpcs = (CREATESTRUCTW *)lParam;
  if(lpcs->dwExStyle & WS_EX_MDICHILD) {
    MDICREATESTRUCTW *lpmcs = (MDICREATESTRUCTW *)lpcs->lpCreateParams;
    return (int)lpmcs->lParam;
  } else {
    return (int)lpcs->lpCreateParams;
  }
}

static void sysclose_active_mdi_child(HWND client)
{
  HWND hwnd;
  
  if(client == NULL)
    return;
  
  hwnd = (HWND) SendMessage(client, WM_MDIGETACTIVE, 0, 0);
  if(hwnd == NULL)
    return;
  SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
}

/* This is for use with EnumChildWindows */
static BOOL CALLBACK sysclose_child_window(HWND hwnd, LPARAM lParam)
{
  if (! GetWindow(hwnd, GW_OWNER)) /* Skip icon title windows. */
    SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
  return TRUE;
}

/* This is for use with EnumChildWindows */
static BOOL CALLBACK sysminimize_child_window(HWND hwnd, LPARAM lParam)
{
  if (! GetWindow(hwnd, GW_OWNER)) /* Skip icon title windows. */
    SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
  return TRUE;
}

/* Erase portion of window's client area outside given rectangle. */
static void erase_outside_of_rect(HWND hwnd, RECT *r)
{
  HRGN hrgn, client, oldRgn;
  RECT c;
  HDC hdc;

  GetClientRect(hwnd,&c);
  client = CreateRectRgnIndirect(&c); // Client-area
  hrgn = CreateRectRgnIndirect(r);    // Region to exclude
  CombineRgn(hrgn, client, hrgn, RGN_DIFF);

  // This would work, except we MUST not generate a WM_PAINT.
  // RedrawWindow(hwnd, NULL, hrgn, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_ERASENOW);

  hdc = GetDC(hwnd);
  oldRgn = SelectObject(hdc,hrgn);
  SendMessage(hwnd, WM_ERASEBKGND, (WPARAM)hdc, 0);

  SelectObject(hdc, oldRgn);

  ReleaseDC(hwnd,hdc);
  DeleteObject(hrgn);
  DeleteObject(client);
}

/* If the automatic generation of scroll events by the wheel is enabled, and we
   have scroll bars, and no shift keys are down, then ignore wheel events,
   because the OS takes care of them. */
static BOOL process_mouse_wheel_events_p(HWND hwnd)
{
  LONG style = GetWindowLong(hwnd,GWL_STYLE);
  BOOL sbars = (style & (WS_HSCROLL | WS_VSCROLL)) != 0;
  BOOL shifted = ((GetKeyState(VK_CONTROL) | GetKeyState(VK_SHIFT) | 
		   GetKeyState(VK_MENU)    | GetKeyState(VK_RMENU)) & 0x8000) != 0;

  MTRACE("process_mouse_wheel_events_p %x %d %d %d %d\n",
	 hwnd,
	 msh_MouseWheelPresent,
	 msh_MouseWheelAutoScroll,
	 sbars,
	 !shifted);

  if(msh_MouseWheelPresent && msh_MouseWheelAutoScroll && sbars && !shifted)
    return FALSE;
  else
    return TRUE;
}

static void draw_gensym_background(HDC hdc, RECT *r)
{
  COLORREF bg = RGB(169,169,169); /* LISP tiling-pattern-background-color (gray) */
  COLORREF fg = RGB(255,255,255); /* LISP tiling-pattern-foreground-color (white) */
  HBITMAP hbm = LoadBitmap(hInst, "GTILE"); /* Gensym tiling pattern */
  HBRUSH hbr = CreatePatternBrush(hbm);	    /* TODO: cache this. */

  SetBkColor(hdc, bg);
  SetTextColor(hdc, fg);
  FillRect(hdc, r, hbr);

  DeleteObject(hbr);
  DeleteObject(hbm);
}

long g2ext_mega_refresh(void)
{
  if(IsWindow(hwndMain))
    RedrawWindow(hwndMain, NULL, NULL,
		 RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
  return 1;
}

static int count_tabs(LPWSTR s)
{
  int n;
  wchar_t *p;
  for(n=0; p=wcschr(s,L'\t'); s=p+1)
    n++;
  return n;
}

char *g2pvt_GetFileVersionInfo(char *moduleName)
{
  int len;
  DWORD junk;
  char *info;
  char buf1[MAX_PATH];

  if (moduleName == NULL) {
    /* first, find out the filename from where we were launched */
    GetModuleFileName(NULL, buf1, MAX_PATH-1);
    buf1[MAX_PATH-1] = '\0';
    moduleName = buf1;
  }

  len = GetFileVersionInfoSize(moduleName, &junk);
  if (len <= 0)
    return NULL;

  info = malloc(len);
  if (!GetFileVersionInfo(moduleName, 0, len, info))
    return NULL;

  return info;
}

/* Get version of module (the name of a DLL or EXE) that would be found by
 * LoadLibrary or the shell, or NULL if not found. Formatted as 1.2.3.4. */
char *g2pvt_get_module_version(char *moduleName)
{
  char *info;
  UINT iLen;
  VS_FIXEDFILEINFO *ffi;
  static char buf[128];

  info = g2pvt_GetFileVersionInfo(moduleName);

  if (!info)
    return NULL;

  if (!VerQueryValue(info, "\\", (LPVOID*)&ffi, &iLen)) {
    free(info);
    return NULL;
  }

  buf[0] = '\0';
  sprintf(buf, "%d.%d.%d.%d", 
	  HIWORD(ffi->dwFileVersionMS),
	  LOWORD(ffi->dwFileVersionMS),
	  HIWORD(ffi->dwFileVersionLS),
	  LOWORD(ffi->dwFileVersionLS));
  free(info);

  return buf;
}

/* Get the file version formatted however it appears in the .rc file. */
char *g2pvt_get_FileVersion(char *moduleName)
{
  char *info,*versionstring;
  UINT iLen;
  static char buf[128];

  info = g2pvt_GetFileVersionInfo(moduleName);

  if (!info)
    return "Unknown Version";

  if (!VerQueryValue(info, "\\StringFileInfo\\040904E4\\FileVersion", (LPVOID*)&versionstring, &iLen)) {
    free(info);
    return "Unknown Version";
  }

  buf[0] = '\0';
  sprintf(buf,"%s",versionstring);

  free(info);

  return buf;
}  

/* Adjust the layer position of window to be just below the window given by
 * handle. A handle of -1 means HWND_TOP, etc. */
static set_window_zorder(HWND hwnd, long handle)
{
  HWND hwndAfter;

  switch(handle) {
   case -1:
     hwndAfter = HWND_TOP;
     break;
   case -2:
     hwndAfter = HWND_BOTTOM;
     break;
   case -3:
     hwndAfter = HWND_TOPMOST;
     break;
   case -4:
     hwndAfter = HWND_NOTOPMOST;
     break;
   default:
     hwndAfter = g2pvt_find_window(handle);
     break;
  }
  SetWindowPos(hwnd, hwndAfter, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
}

extern BOOL g2pvt_tabbed_mdi_mode_p();
extern void g2pvt_set_window_closeable(HWND hwnd, BOOL torf);

#ifndef CODEJOCK
BOOL g2pvt_tabbed_mdi_mode_p()
{
  return FALSE;
}

void g2pvt_set_window_closeable(HWND hwnd, BOOL torf)
{
  EnableMenuItem(GetSystemMenu(hwnd,FALSE), SC_CLOSE, MF_BYCOMMAND | (torf ? MF_ENABLED : MF_GRAYED));
}
#endif


BOOL g2pvt_syscommand_enabled_p(HWND hwnd, UINT nID)
{
  LONG style = GetWindowLong(hwnd,GWL_STYLE);
  LONG cstyle = GetClassLong(hwnd,GCL_STYLE);
  HMENU hMenu;

  switch(nID) {
   case SC_CLOSE:
     hMenu = GetSystemMenu(hwnd,FALSE);
     return (cstyle&CS_NOCLOSE) == 0 &&
       (hMenu==NULL || (GetMenuState(hMenu, nID, MF_BYCOMMAND) & (MF_DISABLED|MF_GRAYED)) == 0);

   case SC_MINIMIZE:
     return (style&WS_MINIMIZEBOX) != 0 && (style&WS_MINIMIZE) == 0;

   case SC_MAXIMIZE:
     return (style&WS_MAXIMIZEBOX) != 0 && (style&WS_MAXIMIZE) == 0;

   case SC_MOVE:
     return (style&WS_MAXIMIZE) == 0;

   case SC_SIZE:
     return (style&WS_THICKFRAME) != 0 && (style&(WS_MAXIMIZE|WS_MINIMIZE)) == 0;

   case SC_RESTORE:
     if((style&WS_MAXIMIZE) && !(style&WS_THICKFRAME))
       return FALSE;
     else
       return (style&(WS_MAXIMIZE|WS_MINIMIZE)) != 0;

   default:
     return TRUE;
  }
}




/* 
 * Frame, Menu, and StatusBar functions
 */

/* Resize the client window in response to a frame resize.
 * This is used in both SDI and MDI modes. */
static void layout_frame_window(HWND hwnd)
{
  RECT cr,sr;
  int height = 0;

  GetClientRect(hwnd, &cr);

  /* Compute the height of the status line */
  if(hwndStatus) {
    GetWindowRect(hwndStatus, &sr);
    height = sr.bottom - sr.top;
    if(bViewStatusbar)
      cr.bottom -= height;
  }

  if(hwndClient != NULL)
    MoveWindow(hwndClient, cr.left, cr.top, cr.right - cr.left, cr.bottom - cr.top,
	       TRUE);

  if(hwndStatus != NULL)	/* Move it even if not visible. */
    g2pvt_resize_status_bar(hwndStatus, &cr);
}

static void on_size_for_frame (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  UINT state = wParam;
  int cx = LOWORD(lParam);
  int cy = HIWORD(lParam);

  if (state == SIZE_MINIMIZED)
    return;

  layout_frame_window(hwnd);
}

/* Update the statusbar with help text for menu item. */
static LRESULT on_menu_select_for_frame(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  int id = LOWORD(wParam);
  LPWSTR string;

  on_menuselect(hwnd, wParam, lParam); /* Fire NMS callbacks, if any. */

  if(!bViewStatusbar) return 0;
  if(hwndStatus == NULL) return 0;

  string = g2pvt_nms_help_string(id);
  if(string == NULL) return 0;

  g2pvt_set_statusbar_text(string);
  return 0;
}


/* Updates the "unconnected" menu bar, which is present when TW is either not
 * connected to any G2, or is connected to a G2 earlier than version 7. */
static void update_unconnected_menu_bar(HMENU menu)
{
  /* TODO: check/uncheck View->statusbar, menubar, toolbar items here . */
  //  EnableMenuItem(menu, TWPRO_PRINTWINDOW, (active==NULL) ? MF_GRAYED : MF_ENABLED);
}


/* Send to G2 a "control event", which is an event from a native control.
 * arg1-4 are arbitrary integer parameters which go with the event, packed
 * into x, y, width, height args of the event actually sent to G2.
 *
 * controlKeyCode is a G2 keycode (see keydefs.lisp) that indicates the
 * type of control event and the interpretation of the arg1-4.
 * See LISP decode-native-control-event. */
void g2pvt_send_control_event(HWND hwnd, int controlKeyCode, 
			      int arg1, int arg2, int arg3, int arg4)
{
  StoreNextEvent(hwnd, X11_CONTROL, arg1, arg2, arg3, arg4, controlKeyCode, 0);
}

/* Send an NMS control event, which currently can be from an edit or combo
   box. ControlID is the cmd ID of the control. Selection is the index of a combo
   box selection, or -1. See LISP decode-native-control-event. */
void g2pvt_send_nms_control_event(HWND hwnd, int controlID, int selection, LPWSTR value)
{
  StoreNextEventEx(hwnd, X11_CONTROL, controlID, selection, -1, -1, 
		   GENSYM_NMS_CONTROL, 0, value);
}


/* This is used by TWNG, which stores the handle differently, so must supply it
   as an argument. */
void g2pvt_fire_control_event(int controlType, int controlHandle,
			      int arg1, int arg2, int arg3, int arg4,
			      LPCWSTR string)
{
  g2pvt_send_event(hwndMain, controlHandle, X11_CONTROL,
		   arg1, arg2, arg3, arg4, controlType, 0, (LPWSTR)string);
}

/* g2pvt_simple_rpc sends a workstation event to the connected G2, and waits for
 * a reply or timeout. The replied value is returned. */
static int g2pvt_simple_rpc(int controlKeyCode, int arg1, int arg2, int arg3, int arg4)
{
  int start, delay;
  HCURSOR oldCursor = NULL;
  /* An idle G2 running on the same PC responds in 10-20ms. A moderately
   * busy G2 on the same machine seems to respond in 100-200ms. What we
   * want here is to only put up a wait cursor if the delay has been long
   * enough that the user is wondering what is going on. To that end,
   * it probably should really be adaptive to the measured RTT to G2.
   * But that is overkill for 7.0. */
  static int wait_cursor_timeout = 200; /* Timeout before wait cursor, ms. */
  static int timeout = 10000;	        /* Timeout before we give up, ms. TODO: configurable. */

  if(Inside_simple_rpc) {
    g2ext_write_string_to_console("Warning: recursive simple rpc ignored.");
    return -2;
  }

  MTRACE("Enter g2pvt_simple_rpc %d main=%x\n", controlKeyCode, hwndMain);

  nms_flag = 1;
  g2pvt_send_control_event(hwndMain, controlKeyCode, arg1, arg2, arg3, arg4);


#ifdef GENFLEX
	/* Victor Kazarinov note: I don't know why we need wait for an return 
     * value here, because I can't find, who uses return value of this 
	 * g2pvt_simple_rpc function, but I need immidetly return,
	 * because sometimes in GenFlex we call "CommandToTw_UpdateMenuBar"
	 * in tw's thread and while it not exited, all GenFlex freezes when
	 * other commands was sended at sime time. So this function must return
	 * immidetly. */
  
	return -1;
#endif

  /* Enter a modal loop processing ICP messages until nms_flag changes value
   * (meaning we've received the menu update message), or a timeout. */
  start = GetTickCount();
  delay=0;
  Inside_simple_rpc = TRUE;
  while(nms_flag==1) {
    g2_event_cycle(0);		/* Arbitrary ICP messages received here. */
    if(nms_flag != 1) break;
    delay = GetTickCount() - start;
    if(delay > timeout)
      break;
    g2ext_sys_sleep(10);
    if(oldCursor == NULL && delay > wait_cursor_timeout)
      oldCursor = SetCursor(LoadCursor(NULL,IDC_WAIT));
  }
  Inside_simple_rpc = FALSE;

  MTRACE("Exit g2pvt_simple_rpc, rtt= %dms\n", delay);

  if(oldCursor)
    SetCursor(oldCursor);

  if(delay >= timeout) {
    char message[120];
    sprintf(message, "Warning: %dms timeout expired waiting for menu update (%d).",
	    timeout, delay);
    g2ext_write_string_to_console(message);
    return -1;
  } else {
    return nms_flag;
  }
}

int g2pvt_update_menubar(void)
{
  if(Inside_handle_event) {
    MTRACE("Aborting g2pvt_update_menubar: %08x\n", Inside_handle_event);
    return GENSYM_XTP_ABORT_MENU;
  }
  g2pvt_simple_rpc(GENSYM_MENUBAR, -1, -1, -1, -1);
  return 1;
}

/* Called when any submenu or popup menu first exposed.
 * If menu is declared dynamic, notify G2 and wait for it to be updated. */
int g2pvt_update_dynamic_menu(HANDLE menu, int posInParent)
{
  int nms_handle = nms_handle_if_flag_bit(HIWORD(menu), LOWORD(menu), MF_DYNAMIC);

  if(nms_handle <= 0)
    return 0;

  g2pvt_simple_rpc(GENSYM_MENU_POSTED, nms_handle, posInParent, -1, -1);
  return 1;
}

/* This is used for Win32 and Codejock menus, hence menu is not always an HMENU. */
int g2pvt_nms_menu_unposted(HANDLE menu)
{
  int nms_handle = nms_handle_if_flag_bit(HIWORD(menu), LOWORD(menu), MF_UNPOST);

  if(nms_handle <= 0)
    return 0;

  g2pvt_send_control_event(hwndMain, GENSYM_MENU_UNPOSTED, nms_handle, 0, 0, 0);
  return 1;
}

/* If the menu wants selection callbacks, send an event to G2.  If itemID is 0,
 * then no item is selected. This routine MUST be called with a NULL menu and
 * itemID when exiting the menu context. */
int g2pvt_fire_nms_selection_callbacks(HANDLE menu, int itemID)
{
  int handle = nms_handle_if_flag_bit(HIWORD(menu), LOWORD(menu), MF_MENUSELECT);
  static int previous_handle = 0;
  static int previous_itemID = 0;

  if((handle>0 || previous_handle>0) && (handle != previous_handle || itemID != previous_itemID))
    g2pvt_send_control_event(hwndMain, GENSYM_MENU_ITEM_SELECTED, 
			     handle, itemID,
			     previous_handle, previous_itemID);

  previous_handle = handle;
  previous_itemID = itemID;

  return 1;
}


/* Initializing a native menu (WM_INITMENU handler): give G2 a
 * chance to update the menus before entering modal loop. We do that by sending
 * a message to G2 and WAITING HERE IN A MODAL LOOP for a reply which updates
 * the menu. Even if G2 never responds, we eventually exit the modal loop,
 * after a long timeout (10 sec, comparable to the procedure execution timeout).
 */
static void on_initmenu(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  HMENU menu = (HMENU)wParam;

  MTRACE("WM_INITMENU: hwnd:%x menu:%x menubar:%x frame:%x\n",
 	 hwnd, menu, GetMenu(hwnd), hwndFrame);

  if(menu != GetMenu(hwnd))	/* Not the menu bar, nothing to do. */
    return;

  /* TODO: We get called for clicks on the Min/Restore/Close buttons for
     a maximized MDI child. So we round-trip to G2 unnecessarily in that case.
     We can't detect that case easily here. */
  
  if(menu == hMenuInit)		/* Unconnected menu bar, handle locally. */
    update_unconnected_menu_bar(menu);
  else
    g2pvt_update_menubar();
}

/* Enable/disable local command items in given menu. */
static void init_local_commands_in_menu(HMENU hMenu)
{
  int i, nID;

  for(i=0; i<GetMenuItemCount(hMenu); i++) {
    nID = GetMenuItemID(hMenu,i);
    if(g2pvt_local_command_p(nID))
      EnableMenuItem(hMenu, i, MF_BYPOSITION | 
		     (g2pvt_local_command_enabled_p(nID) ? MF_ENABLED : (MF_DISABLED|MF_GRAYED)));
  }
}

/* Used for both WM_INITMENUPOPUP and WM_UNINITMENUPOPUP */
static int on_initmenupopup(HWND hwnd, WPARAM wParam, LPARAM lParam, BOOL init)
{
  HMENU menu = (HMENU) wParam;

  if(HIWORD(lParam) != 0)  // Don't handle system menu.
    return 0;

  if(init) {
    int pos = LOWORD(lParam);
    init_local_commands_in_menu(menu); // Update local commands in menu, if any.
    return g2pvt_update_dynamic_menu((HANDLE)menu, pos);
  } else {
    return g2pvt_nms_menu_unposted((HANDLE)menu);
  }
}

static int on_menuselect(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
  int itemID = LOWORD(wParam);	/* Command ID or index if is a submenu */
  HMENU menu = (HMENU)lParam;

  if(HIWORD(wParam) == 0xFFFF && lParam == 0) /* Menu was closed */
    itemID = 0;
  else if(HIWORD(wParam) & MF_SYSMENU)        /* Menu was the system menu */
    return 0;
  else if (HIWORD(wParam) & MF_POPUP) {	      /* Item was a submenu */
    HMENU submenu = GetSubMenu(menu,itemID);
    itemID = nms_id_for_menu(HIWORD(submenu),LOWORD(submenu));
  }

  return g2pvt_fire_nms_selection_callbacks(menu, itemID);
}

/* Return data if data is almost certainly a pointer to a G2_MENU_ITEM structure. */
static G2_MENU_ITEM *g2_menu_item_p(void *data)
{ 
  __try
    {
      if(data != NULL && *(unsigned long *)data == G2_MENU_ITEM_MAGIC)
	return (G2_MENU_ITEM *)data;
    }
  __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
	    EXCEPTION_EXECUTE_HANDLER :
	    EXCEPTION_CONTINUE_SEARCH)
    { 
      return NULL; 
    } 
  return NULL;
}

/* Measure an owner-drawn menu item. */
int g2pvt_on_measure_item(HWND hwnd, int controlID, LPMEASUREITEMSTRUCT lpmis)
{
  G2_MENU_ITEM *gmi;
BOOL b;
  if(lpmis->CtlType == ODT_MENU && (gmi = g2_menu_item_p((void *)lpmis->itemData)) != NULL) {
    HDC hdc = GetDC(hwnd);
    HFONT oldFont;
    
    if(MenuFont == NULL) {
      /* GENSYMCID-1503: Issue with changing color, if application was built for Windows Server 2008 
         but must be run in Windows Server 2003, cbSize should be cut in windows server2003, for detail
         please refer to https://msdn.microsoft.com/en-us/library/windows/desktop/ff729175(v=vs.85).aspx
      */
      OSVERSIONINFOEX versionInfo;
      NONCLIENTMETRICS info;
      versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
      GetVersionEx((LPOSVERSIONINFOA)&versionInfo);
      info.cbSize = sizeof(info);
      if (versionInfo.dwMajorVersion < 6)
        info.cbSize -= sizeof(int);
      b = SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
      MenuFont = CreateFontIndirect(&info.lfMenuFont);
    }
    oldFont = SelectObject(hdc,MenuFont);

    g2pvt_size_custom_menu_item(hdc, gmi, &lpmis->itemWidth, &lpmis->itemHeight);

    SelectObject(hdc,oldFont);
    ReleaseDC(hwnd, hdc); 
    return TRUE;
  }

  return FALSE;
}

/* Draw item handler -- used for G2 color menu, and for icons in menus. */
int g2pvt_on_draw_item(HWND hwnd, int controlID, LPDRAWITEMSTRUCT lpdis)
{
  G2_MENU_ITEM *gmi;

  if(lpdis->CtlType == ODT_MENU && (gmi = g2_menu_item_p((void *)lpdis->itemData)) != NULL) {
    g2pvt_draw_custom_menu_item((HMENU)lpdis->hwndItem, lpdis->hDC, 
				lpdis->itemState, lpdis->itemID,
				(RECT *)&lpdis->rcItem, gmi);
    return TRUE;

  } else if (controlID == IDC_STATUS) {
    return TRUE;
  }

  return FALSE;
}


/* Make the statusbar window and menu item match current value of bViewStatusbar. */
void g2pvt_update_statusbar_visibility(void)
{
  BOOL was_showing;

  if(hViewMenu != NULL)
    CheckMenuItem(hViewMenu, TWPRO_STATUSBAR, bViewStatusbar ? MF_CHECKED : MF_UNCHECKED);

  if(hwndStatus != NULL) {
    was_showing = ShowWindow(hwndStatus, bViewStatusbar ? SW_SHOW : SW_HIDE) != 0;
    if(was_showing != bViewStatusbar)
      layout_frame_window(hwndFrame);
  }
}

BOOL g2pvt_local_command_enabled_p(int nID)
{
  HWND hwnd = (HWND) SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0);
  switch(nID) {
   case TWPRO_TILE:
   case TWPRO_TILE_VERTICALLY:
   case TWPRO_TILE_HORIZONTALLY:
   case TWPRO_CASCADE:
     return hwnd!=NULL;

   case TWPRO_MINIMIZE_ALL:
     return hwnd && g2pvt_syscommand_enabled_p(hwnd,SC_MINIMIZE);

   case TWPRO_CLOSE:
   case TWPRO_CLOSEALL:
     return hwnd && g2pvt_syscommand_enabled_p(hwnd,SC_CLOSE);

   case TWPRO_STATUSBAR:
     return hwndStatus != NULL;

   case TWPRO_ABOUT:
   case TWPRO_EXIT:
   case TWPRO_PRINTWINDOW:
     return TRUE;

   case TWPRO_HELP:
     return g2pvt_help_available_p();
  }
  return TRUE;
}

/* Menu choice (or dialog choice) on frame window. Returns 1 if command should
 * be passed on to the default wndproc, 0 if it was completely handled here. */
static int
on_wm_command(HWND hwnd, WPARAM wParam, LPARAM lParam) 
{
  int command = LOWORD(wParam);

  switch (command) {
   case TWPRO_EXIT:
     if(IsWindow(hwndFrame))	/* Paranoia, should never be the case. */
          SendMessage(hwndFrame, WM_CLOSE, 0, 0);
     return 0;

   case TWPRO_TILE:
   case TWPRO_TILE_VERTICALLY:
     if(Frame_is_MDI)
       SendMessage(hwndClient, WM_MDITILE, MDITILE_VERTICAL, 0);
     return 0;

   case TWPRO_TILE_HORIZONTALLY:
     if(Frame_is_MDI)
       SendMessage(hwndClient, WM_MDITILE, MDITILE_HORIZONTAL, 0);
     return 0;

   case TWPRO_CASCADE:
     if(Frame_is_MDI)
       SendMessage(hwndClient, WM_MDICASCADE, 0, 0);
     return 0;               

   case TWPRO_INSERT_OBJECT:
     insert_activex_object(hwnd);
     return 0;

   case TWPRO_ABOUT:
     g2pvt_send_control_event(hwndMain, GENSYM_ABOUTBOX, -1, -1, -1, -1);
     return 0;

   case TWPRO_STATUSBAR:	/* Toggle visibility of the statusbar */
     bViewStatusbar = !bViewStatusbar;
     g2pvt_update_statusbar_visibility();
     return 0;

   case TWPRO_CLOSE:
      if(Frame_is_MDI)
	sysclose_active_mdi_child(hwndClient);
      return 0;
   case TWPRO_MENU_SMALL:
	     g2pvt_menu_size(18); 
		 return 0;
   case TWPRO_MENU_MEDIUM :
	   g2pvt_menu_size(25);
	   return 0;
   case TWPRO_MENU_LARGE:
	   g2pvt_menu_size(30);
	   return 0;

   case TWPRO_CLOSEALL:
     if(Frame_is_MDI)
       EnumChildWindows(hwndClient, sysclose_child_window, 0);
     return 0;

   case TWPRO_MINIMIZE_ALL:
     if(Frame_is_MDI)
       EnumChildWindows(hwndClient, sysminimize_child_window, 0);
     return 0;

   case TWPRO_HELP:		/* Display html help, if possible. */
     g2pvt_show_tw_help(hwnd);
     return 0;

   case TWPRO_PRINTWINDOW:	/* Print Telewindow as bitmap. */
     g2pvt_send_control_event(hwndMain, GENSYM_PRINTWINDOW, -1, -1, -1, -1);
     return 0;

   default:
     MTRACE("on_wm_command: Send command %d\n", command);
     g2pvt_send_control_event(hwndMain, GENSYM_MENU_CHOICE, command, -1, -1, -1);
     break;
  }
  return 1;
}




/*
 * G2 Event utilities
 */

/* Compute same value as wParam in WM_SIZE */
int g2pvt_compute_window_state(HWND hwnd)
{
  return (IsIconic(hwnd) ? SIZE_MINIMIZED : IsZoomed(hwnd) ? SIZE_MAXIMIZED : SIZE_RESTORED);
}
 
void g2pvt_send_window_activated(HWND hwnd, int handle)
{
  g2pvt_send_event(hwnd, handle, X11_FOCUS_IN, 0, 0, 0, 0, 0, 0, NULL);
}

void g2pvt_send_window_refresh(HWND hwnd, int handle, RECT *r)
{
  g2pvt_send_event(hwnd, handle, X11_CONTROL,
		   r->left, r->top, r->right - r->left, r->bottom - r->top,
		   GENSYM_WINDOW_REFRESH, 0, NULL);
}

void g2pvt_send_window_moved(HWND hwnd, int handle, int x, int y)
{
  g2pvt_send_event(hwnd, handle, X11_CONTROL,
		   x, y, g2pvt_compute_window_state(hwnd), 0,
		   GENSYM_WINDOW_MOVED, 0, NULL);
}

void g2pvt_send_window_sized(HWND hwnd, int handle, UINT type, int cx, int cy)
{
  g2pvt_send_event(hwnd, handle, X11_CONTROL,
		   type, IsIconic(hwnd), cx, cy,
		   GENSYM_WINDOW_SIZED, 0, NULL);
}

void g2pvt_send_window_vscroll(HWND hwnd, int handle, int code, int pos, int id)
{
  g2pvt_send_event(hwnd, handle, X11_CONTROL,
		   code, pos, id, 0,
		   GENSYM_VSCROLL, 0, NULL);
}

void g2pvt_send_window_hscroll(HWND hwnd, int handle, int code, int pos, int id)
{
  g2pvt_send_event(hwnd, handle, X11_CONTROL,
		   code, pos, id, 0,
		   GENSYM_HSCROLL, 0, NULL);
}

void g2pvt_send_window_closed(HWND hwnd, int handle)
{
  g2pvt_send_event(hwnd, handle, X11_CONTROL,
		   0, 0, 0, 0,
		   GENSYM_WINDOW_CLOSED, 0, NULL);
}

void g2pvt_send_window_status(HWND hwnd, int handle, int status)
{
  RECT r;
  GetClientRect(hwnd,&r);
  g2pvt_send_window_sized(hwnd, handle, status, r.right-r.left, r.bottom-r.top);
}

/* 
 * Frame Wndproc
 */

static int G2_create_in_progress  = 0;
int G2_reshape_in_progress = 0;
int G2_inflate_in_progress = 0;
static int G2_window_handle = 0;

/* Skip sending refresh events for workspace views with given HWND. */
static HWND G2_inhibit_refresh_events_hwnd = NULL;

int g2pvt_frame_wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LPG2INFO info = NULL;

  switch (message) {
   case WM_TIMER:
     if(wParam == ANTIMODAL_TIMER_ID) {
       g2pvt_do_some_event_cycles();
       return 0;
     }
     break;

   case WM_SETCURSOR:
     if(g2pvt_on_wm_setcursor(hwnd, message, wParam, lParam))
       return 1;		// Run default wndproc
     else
       return 2;		// Handled, and return TRUE from WndProc

   case WM_DRAWITEM:
     if (g2pvt_on_draw_item(hwnd, (int)wParam, (LPDRAWITEMSTRUCT)lParam))
       return 2;			// Handled, and return TRUE from WndProc
     else
       return 1;
     
   case WM_MEASUREITEM:
     if (g2pvt_on_measure_item(hwnd, (int)wParam, (LPMEASUREITEMSTRUCT)lParam)) 
       return 2;			// Handled, and return TRUE from WndProc
     else
       return 1;

   case WM_SIZE:
     /* The default WM_SIZE method on frames does not account for a status bar,
      * so be sure not to let it run. */
     if(Frame_is_MFC)
       break;			// MFC takes care of it.
     on_size_for_frame(hwnd, wParam, lParam);
     return 0;

   case WM_MENUSELECT:
     if(!Frame_is_MFC)		// MFC takes care of it.
       on_menu_select_for_frame(hwnd, wParam, lParam);
     break;

   case WM_COMMAND:
     if(on_wm_command(hwnd, wParam, lParam) == 0)
       return 0;
     break;

   case WM_CREATE:
     g2pvt_make_new_window_info(hwnd, -1);
     if(Frame_has_client)
       hwndClient = g2pvt_create_client_window(hwnd);
     break;

   case WM_SETFOCUS:
     if(Frame_has_client && !Frame_is_MDI) /* When we have an SDI client window. */
       SetFocus(hwndClient);
     break;

   case WM_SYSCOMMAND:
     if(screenlock && ((wParam & 0xFFF0) == SC_MOVE))
       return 0;
     break;

   case WM_NCLBUTTONDOWN:
     /* If we are inside of handle-event-internal (a LISP function), determined
      * by Inside_handle_event (a LISP variable) being non-NIL, then for some reason
      * we cannot send or receive ICP messages, so our WM_INITMENU handler will
      * not work. This case occurs, repeatably, if you post a pop-up menu and
      * then click on the menu bar (HQ-4474652). In this case, the best
      * we can do until we figure out what is really going on is to refuse to post
      * the menu. The user will have to click on it again for it to post. If this
      * happens only when clicking when a pop-up menu is currently up, it's not
      * too objectionable, I think.  At least, it is a workaround for 7.0.
      * See also identical WM_NCLBUTTONDOWN on the frame wndproc. -fmw, 1/17/03 */
     if(Inside_handle_event && (wParam == HTMENU || wParam == HTSYSMENU))
       return 0;
     break;

   case WM_INITMENU:
     MTRACE("WM_INITMENU on frame\n");
     if((HMENU)wParam == GetMenu(hwnd)) { /* If is the menu bar. */
       on_initmenu(hwnd, wParam, lParam);
       return 0;
     } else {
       // RFP-44067: New Feature: Disable "Move" and "Resize" options in TWNG Window menu
       if (g2ext_product == TW_CMD) {
         EnableMenuItem((HMENU)wParam, SC_SIZE, MF_BYCOMMAND | MF_GRAYED);
         EnableMenuItem((HMENU)wParam, SC_MOVE, MF_BYCOMMAND | MF_GRAYED);
         if (!g2pvt_minimize)
           EnableMenuItem((HMENU)wParam, SC_MINIMIZE, MF_BYCOMMAND | MF_GRAYED);
       }
     }
     break;

   case WM_INITMENUPOPUP:
     MTRACE("WM_INITMENUPOPUP on frame\n");
     if(on_initmenupopup(hwnd, wParam, lParam, TRUE))
       return 0;
     break;

   case WM_UNINITMENUPOPUP:
     MTRACE("WM_UNINITMENUPOPUP on frame\n");
     if(on_initmenupopup(hwnd, wParam, lParam, FALSE))
       return 0;
     break;

   case WM_ENTERMENULOOP:
     MTRACE("WM_ENTERMENULOOP on frame\n");
     g2pvt_enter_modal_loop();
     break;

   case WM_ENTERSIZEMOVE:
     g2pvt_enter_modal_loop();
     return 0;

   case WM_EXITMENULOOP:
     MTRACE("WM_EXITMENULOOP on frame nms_flag=%d\n", nms_flag);
     if(nms_flag) g2ext_nms_set_flag(0); // Return from any active RPC.
     g2pvt_exit_modal_loop();
     break;

   case WM_EXITSIZEMOVE:	/* Sometimes we don't get this matching message! */
     g2pvt_exit_modal_loop();
     return 0;

   case WM_NMS_MENU_CHOICE:	/* W=choice, L=menu_handle if known */
     g2pvt_send_control_event(hwnd, GENSYM_MENU_CHOICE, wParam, lParam, -1, -1);
     return 0;

   case WM_SETTINGCHANGE:
     g2pvt_decache_system_settings(wParam);
     break;

   case WM_DESTROY:
     g2pvt_on_wm_destroy(hwnd, message, wParam, lParam);
     break;
  }
  return 1;
}

/* This wndproc is used for both SDI and MDI frame windows. */
LONG WINAPI FrameWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int rc = g2pvt_frame_wndproc(hwnd, message, wParam, lParam);

  if(rc == 0)
    return 0;
  else if (rc == 2)
    return TRUE;

  if(Frame_is_MDI)
    return DefFrameProcW(hwnd, hwndClient, message, wParam, lParam);
  else
    return DefWindowProcW(hwnd, message, wParam, lParam);
}





/*
 * MDI Client Wndproc
 */

static WNDPROC old_mdi_client_wndproc;
static COLORREF Mdi_client_background_color = (COLORREF) -1;

#define USE_SYSCOLOR (-2)

/* Record the solid background color for the overall G2 window. -1's for the
 * color means to use the default MDI client background (COLOR_APPWORKSPACE) */
void g2ext_set_mdi_client_background_color(long red, long green, long blue)
{
  if(red < 0)
    Mdi_client_background_color = USE_SYSCOLOR;
  else {
    Mdi_client_background_color = RGB(red,green,blue);
    if(hwndClient != NULL)	/* As in g2ext_x11_initialize_tile() */
      InvalidateRect(hwndClient, NULL, TRUE);
  }
}

static void erase_mdi_client_background(HWND hwnd, HDC hdc, RECT *r)
{
  LPG2INFO info = GetlpG2Info(hwnd);

  // The first time we are called, neither Tilehbr nor
  // Mdi_client_background_color have been initialized.

  if (Mdi_client_background_color == USE_SYSCOLOR) {
    FillRect(hdc, r, (HBRUSH) (COLOR_APPWORKSPACE+1));

  } else if(Mdi_client_background_color != (COLORREF)-1) {
    HBRUSH hbr = CreateSolidBrush(Mdi_client_background_color);
    FillRect(hdc, r, hbr);
    DeleteObject(hbr);

  } else if(info && info->Tilehbr) {
    SetBkColor(hdc, info->nTileBG);
    SetTextColor(hdc, info->nTileFG);
    FillRect(hdc, r, info->Tilehbr);

  } else {
    FillRect(hdc, r, (HBRUSH) (COLOR_APPWORKSPACE+1));
  }
}

static LRESULT WINAPI MDIClientWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  static int width=0, height=0;	/* Previous dimensions. */
  BOOL rundef = TRUE;
  int retval = 0;

  switch(message) {
   case WM_ERASEBKGND:
     {
       HDC hdc = (HDC)wParam;
       RECT r;

       GetClipBox(hdc,&r);
       erase_mdi_client_background(hwnd,hdc,&r);
       return 1;
     }

   case WM_SIZE:
     if (! IsIconic(hwndFrame)) { /* Note: wParam is not helpful here. */
       int w = LOWORD(lParam);
       int h = HIWORD(lParam);

       /* FIXME: want to send msg noting new size, but NOT requesting a refresh.
	  We can do that in 8.0, but earlier G2's don't have the needed message. */
       StoreNextEvent(hwnd, X11_RESHAPE, 0, 0, w, h, 0L, 0L);
     }
     break;

    case WM_SETCURSOR:
      rundef = g2pvt_on_wm_setcursor(hwnd, message, wParam, lParam);
      retval = TRUE;
      break;
 
   case WM_MOUSEWHEEL:
     if(process_mouse_wheel_events_p(hwnd))
       rundef = g2pvt_on_wm_mouse(hwnd, message, wParam, lParam);       
     break;

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
     rundef = g2pvt_on_wm_mouse(hwnd, message, wParam, lParam);
     break;

   case WM_CHAR:
   case WM_SYSCHAR:
   case WM_SYSKEYDOWN:
   case WM_KEYDOWN:
     rundef = g2pvt_on_wm_keyboard(hwnd, message, wParam, lParam);
     break;

   case WM_DESTROY:
     g2pvt_free_window_info(hwnd);
     break;
  }

  if(rundef)
    return CallWindowProcW(old_mdi_client_wndproc, hwnd, message, wParam, lParam);
  else
    return retval;
}

void g2pvt_designate_mdi_client(HWND hwnd)
{
  LPG2INFO info;

  hwndClient = hwnd;
  info = g2pvt_make_new_window_info(hwnd, 0); /* By convention, hwndClient has handle 0. */

  /* Now subclass it so that we can change the background and handle events. */
  old_mdi_client_wndproc = (WNDPROC)GetWindowLongPtrW(hwnd,GWLP_WNDPROC);
  if(old_mdi_client_wndproc == MDIClientWndProc) {
    fprintf(stderr, "Attempted to double-subclass MDI client %x!\n", hwnd);
    return;
  }
  SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG)MDIClientWndProc);
}

/* Creates and subclasses a MDICLIENT window. */
HWND g2pvt_create_mdi_client(HWND parent)
{
  HWND hwnd;
  CLIENTCREATESTRUCT ccs;
  RECT r;

  ccs.hWindowMenu = hMenuInitWindow;
  ccs.idFirstChild = IDM_FIRSTCHILD;
  GetClientRect(parent, &r);

  hwnd = CreateWindowW(L"MDICLIENT", NULL,
		       WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | MDIS_ALLCHILDSTYLES | WS_BORDER,
		       r.left, r.top,
 		       (r.right - r.left), (r.bottom - r.top),
		       parent, (HMENU)1, hInst, (PSTR)&ccs);
  if (hwnd == NULL) {
    fprintf(stderr, "Unable to create MDI client window with parent %x: %s\n",
	    parent, g2pvt_get_last_error_string());
    return NULL;
  }

  g2pvt_designate_mdi_client(hwnd);

  MTRACE("g2pvt_create_mdi_client frame:%x client:%x hwndMain:%x\n",
	 hwndFrame, hwndClient, hwndMain);
  return hwnd;
}

HWND g2pvt_create_sdi_client(HWND parent)
{
  RECT r;
  HWND hwnd;

  GetClientRect(parent, &r);
#ifdef GENFLEX
  hwnd = GetHandleOfGenflex();
#else
  hwnd = CreateWindowExW(0, GensymTelewindowClass, NULL,
			 WS_CHILD | WS_CLIPCHILDREN,
			 r.left, r.top,
			 (r.right - r.left), (r.bottom - r.top),
			 parent, (HMENU) 4, hInst, NULL);
#endif
  g2pvt_make_new_window_info(hwnd, -1);
  return hwnd;
}

HWND g2pvt_create_client_window(HWND parent)
{
  HWND hwnd;

  if(Frame_is_MDI)
    hwnd = g2pvt_create_mdi_client(parent);
  else
    hwnd = g2pvt_create_sdi_client(parent);

  /* Create a status window for menu help strings, etc. */
  /* It's also a place for a resizing grip. */
  hwndStatus   = g2pvt_create_status_bar(parent);
  hwndProgress = g2pvt_create_progress_bar(hwndStatus);

  ShowWindow(hwndStatus, SW_SHOW);
  return hwnd;
}




/*
 * Workspace View Event Handlers
 */

typedef struct {		/* We're willing to send up to 3 rects before */
  RGNDATAHEADER rdh;		/* reverting to the bounding rectangle. */
  RECT rects[3];
} SimpleRgnData;

void g2pvt_on_wm_paint(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, BOOL mdi_p)
{
  RECT r;
  RECT *rects;
  unsigned int i, nrects;
  SimpleRgnData srd;
  HRGN hrgn;
  PAINTSTRUCT ps;

  nrects=0;
  if(GetUpdateRect(hwnd, &r, FALSE)) {
    nrects = 1;
    rects = &r;
    hrgn = CreateRectRgn(0,0,0,0);
    if(GetUpdateRgn(hwnd, hrgn, FALSE) != ERROR &&
       GetRegionData(hrgn, sizeof(srd), (RGNDATA*)&srd) != 0) {
      rects = &srd.rects[0];
      nrects = srd.rdh.nCount;
    }
    DeleteObject(hrgn);
  }

  for(i=0; i<nrects; i++)
    if(mdi_p)
      g2pvt_send_window_refresh(hwnd, -1, &rects[i]);
    else
      StoreNextEvent(hwnd, X11_EXPOSURE, rects[i].left, rects[i].top,
		     rects[i].right - rects[i].left, 
		     rects[i].bottom - rects[i].top,
		     0, 0);

  BeginPaint(hwnd,&ps);
  EndPaint(hwnd,&ps);
}

/* HQ-5117737: Take the focus even if we already are the active MDI child.
 * Needed because a docked pane doesn't seem to give up the focus when
 * activating the already active MDI child. Floating panes and other top-level
 * windows work OK, however (i.e., they do give up the focus). -fmw, 9/19/05 */

/* Revised to only set focus if the focus is not already within the MDI child,
 * to fix regression HQ-5165110. -fmw, 12/2/05 */
void g2pvt_on_wm_mouseactivate(HWND hwndMDIChild)
{
  HWND hwndMDIFocus, hwndMDIActive;

  if(!hwndClient) return;

  hwndMDIActive = (HWND)SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0);
  hwndMDIFocus = g2pvt_mdi_child_parent(GetFocus());

  if(hwndMDIChild == hwndMDIActive && hwndMDIChild != hwndMDIFocus)
    SetFocus(hwndMDIChild);
}




/*
 * Scrolling
 */

/* Scroll entire client area of window. */
long g2ext_scroll_window(long window_index, long dx, long dy)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  RECT r;

  MTRACE("g2ext_scroll_window(%x, %d, %d)\n", hwnd, dx, dy);

  /* FIXME: use the inval rect for something. */
  GdiFlush();			// Probably not needed.
  ScrollWindowEx(hwnd, dx, dy, NULL, NULL, NULL, &r, SW_INVALIDATE); // | SW_ERASE);
  UpdateWindow(hwnd);
  return 1;
}

/* Set h&v scroll bar position, range, and page size.
   xmin...xmax are the allowable scroll positions (xpos). */
long g2ext_manage_scrollbars(long window_index,
			     long xmin, long xpos, long xmax,
			     long ymin, long ypos, long ymax)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  SCROLLINFO si; 
  RECT r;

  MTRACE("g2ext_manage_scrollbars(%x  %d,%d,%d  %d,%d,%d)\n", 
	 hwnd, xmin, xpos, xmax, ymin, ypos, ymax);

  GetClientRectExx(hwnd,&r);    // Deals with minimized window

  G2_reshape_in_progress++;	// It *is* a reshape if scroll bars are added or removed.

  /* Horizontal scroll bar */
  si.cbSize = sizeof(si);
  si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;
  si.nMin   = xmin;
  si.nMax   = xmax + r.right - 1; // Win32: nMax is document size, not max scrollpos.
  si.nPage  = r.right;
  si.nPos   = xpos;
  SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

  /* Vertical scroll bar */
  si.cbSize = sizeof(si);
  si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;
  si.nMin   = ymin;
  si.nMax   = ymax + r.bottom - 1;
  si.nPage  = r.bottom;
  si.nPos   = ypos;
  SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

  G2_reshape_in_progress--;

  return 0;
}

static BOOL on_wm_hscroll(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int code = LOWORD(wParam);
  int pos = HIWORD(wParam);
  HWND sbar = (HWND)lParam;
  int id = sbar ? 0 : GetDlgCtrlID(sbar);      /* If someday we use sbar controls. */
  SCROLLINFO si;

  switch(code) {
   case SB_THUMBTRACK:			       /* TODO: Option to ignore this msg. */
   case SB_THUMBPOSITION:
     si.cbSize = sizeof(si);	/* Get 32-bit track position. */
     si.fMask = SIF_TRACKPOS;
     if(GetScrollInfo(hwnd, SB_HORZ, &si))
       pos = si.nTrackPos;

     /* Fall thru */

   case SB_LINELEFT: case SB_LINERIGHT:
   case SB_PAGELEFT: case SB_PAGERIGHT:
     g2pvt_send_window_hscroll(hwnd, -1, code, pos, id);
     g2pvt_do_some_event_cycles();
     break;

   case SB_ENDSCROLL:
     break;
  }
  return FALSE;
}

static BOOL on_wm_vscroll(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int code = LOWORD(wParam);
  int pos = HIWORD(wParam);
  HWND sbar = (HWND)lParam;
  int id = sbar ? 0 : GetDlgCtrlID(sbar);
  SCROLLINFO si;

  switch(code) {
   case SB_THUMBTRACK:
   case SB_THUMBPOSITION:
     si.cbSize = sizeof(si);
     si.fMask = SIF_TRACKPOS;
     if(GetScrollInfo(hwnd, SB_VERT, &si))
       pos = si.nTrackPos;

     /* Fall thru */

   case SB_LINEUP: case SB_LINEDOWN:
   case SB_PAGEUP: case SB_PAGEDOWN:
     g2pvt_send_window_vscroll(hwnd, -1, code, pos, id);
     g2pvt_do_some_event_cycles();
     break;

   case SB_ENDSCROLL:
     break;
  }
  return FALSE;
}

LRESULT WINAPI
WorkspaceViewDefaultWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LPG2INFO window_info = GetlpG2Info(hwnd);

  if(window_info && window_info->type == NIP_WINTYPE_MDICHILD)
    return DefMDIChildProcW(hwnd, message, wParam, lParam);
  else
    return DefWindowProcW(hwnd, message, wParam, lParam);
}

/* Call this only when message==WM_SYSCOMMAND and wParam==SC_V/HSCROLL */
static LRESULT modal_scrollbar_loop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT rc;

  if(Inside_modal_scrollbar_loop) /* I don't think this can happen. */
    return 0;

  Inside_modal_scrollbar_loop = TRUE;
  g2pvt_enter_modal_loop();
  rc = WorkspaceViewDefaultWndProc(hwnd, message, wParam, lParam);
  g2pvt_exit_modal_loop();
  Inside_modal_scrollbar_loop = FALSE;

  g2pvt_ensure_mouse_hover_tracking(hwnd);
  return rc;
}





/*
 * WorkspaceView WndProc
 *  This is used for any window showing a single workspace.
 */

int g_InhibitZorderChanges = 0;		/* Global: used by TWNG, too. */
extern int g_NoRaiseOnRightClick;	/* Ditto, defined in windows.c */

int g2pvt_swv_wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pValue)
{
  LPG2INFO window_info = GetlpG2Info(hwnd);
  BOOL rundef = TRUE;

  *pValue = 0;			// Value to return from wndproc, if we don't run default.
  switch(message) {
   case WM_CREATE:
     window_info = g2pvt_make_new_window_info(hwnd, G2_window_handle);
     MTRACE("WM_CREATE hwnd %06x info %x handle %d\n", hwnd, window_info, window_info->window_handle);
     return 0;

   case WM_PAINT:
     MTRACE("g2pvt_swv_wndproc WM_PAINT %x Reshape:%d Inflate:%d iconic:%d nopaint:%0x\n",
	    hwnd, G2_reshape_in_progress, G2_inflate_in_progress, IsIconic(hwnd), 
	    G2_inhibit_refresh_events_hwnd);
     if(hwnd == G2_inhibit_refresh_events_hwnd) {
       PAINTSTRUCT ps;
       BeginPaint(hwnd,&ps);
	   EndPaint(hwnd,&ps);
       /* GENSYMCID-563: Screen refresh in Tw and TwNg is slow in Windows 7 with glass panes */
       G2_inhibit_refresh_events_hwnd = NULL;
     } else {
       g2pvt_on_wm_paint(hwnd, message, wParam, lParam, TRUE);
     }
     return 0;

   case WM_ERASEBKGND:
     // TODO: Download workspace bg from G2.
     MTRACE("g2pvt_swv_wndproc WM_ERASEBKGND %x Reshape:%d Inflate:%d iconic:%d\n",
	    hwnd, G2_reshape_in_progress, G2_inflate_in_progress, IsIconic(hwnd));
     if(G2_inflate_in_progress)
       return 1;
     break;

   case WM_HSCROLL:
     rundef = on_wm_hscroll(hwnd, message, wParam, lParam);
     break;

   case WM_VSCROLL:
     rundef = on_wm_vscroll(hwnd, message, wParam, lParam);
     break;

   case WM_WINDOWPOSCHANGING:
     if(g_InhibitZorderChanges > 0)
       ((WINDOWPOS*)lParam)->flags |= SWP_NOZORDER;
     break;

   case WM_MOVE:
     MTRACE("WM_MOVE %x %d,%d reshape/create: %d %d\n",
	    window_info, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 
	    G2_reshape_in_progress, G2_create_in_progress);
     if (!G2_reshape_in_progress && !G2_create_in_progress)
       g2pvt_send_window_moved(hwnd, -1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
     break;

   case WM_SIZE:
     MTRACE("WM_SIZE %x %dx%d reshape/create: %d %d\n",
 	    window_info, LOWORD(lParam), HIWORD(lParam),
 	    G2_reshape_in_progress, G2_create_in_progress);
     if (!G2_reshape_in_progress && !G2_create_in_progress)
       g2pvt_send_window_sized(hwnd, -1, wParam, LOWORD(lParam), HIWORD(lParam));
     break;

   case WM_GETMINMAXINFO:
     if(window_info &&		      // Msg arrives before WM_CREATE!
	window_info->max_tracking_size.x > 0
	&& window_info->max_tracking_size.y > 0) {
       ((LPMINMAXINFO)lParam)->ptMaxTrackSize = window_info->max_tracking_size;
       return 0;
     }
     break;

   case WM_MOUSEWHEEL:
     if(process_mouse_wheel_events_p(hwnd))
       rundef = g2pvt_on_wm_mouse(hwnd, message, wParam, lParam);       
     break;

   case WM_SETCURSOR:
     rundef = g2pvt_on_wm_setcursor(hwnd, message, wParam, lParam);
     if(!rundef)
       *pValue = TRUE;
     break;

   case WM_LBUTTONDOWN:
     /* Typically our parent gets the focus, not us, so this hack gives us focus
	directly as a side-effect of left-down. Note that there is no visual
	indication unless some items on the workspace are selected.

	The right way is for our parent to propagate the focus to us as
	desired, and for us to have a visual indication. But this hack will do
	for 8.0a0. -fmw, 1/20/04 */
     if((Frame_is_embedded || g2pvt_embedded_window_p(hwnd))
	&& GetFocus() != hwnd)  
       SetFocus(hwnd);

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
     rundef = g2pvt_on_wm_mouse(hwnd, message, wParam, lParam);
     break;

   case WM_GETDLGCODE:
     *pValue = DLGC_WANTALLKEYS;
     return 0;

   case WM_CHAR:
   case WM_SYSCHAR:
   case WM_SYSKEYDOWN:
   case WM_KEYDOWN:
     rundef = g2pvt_on_wm_keyboard(hwnd, message, wParam, lParam);
     break;

   case WM_ENTERMENULOOP:	/* We only get these for our system menu. */
     MTRACE("WM_ENTERMENULOOP on wsview\n");
   case WM_ENTERSIZEMOVE:
     g2pvt_enter_modal_loop();
     return 0;

   case WM_EXITMENULOOP:
     MTRACE("WM_EXITMENULOOP on wsview nms_flag=%d\n", nms_flag);
     if(nms_flag) g2ext_nms_set_flag(0); // Return from any active RPC.

   case WM_EXITSIZEMOVE:
     g2pvt_exit_modal_loop();
     return 0;

   case WM_INITMENUPOPUP:
     MTRACE("WM_INITMENUPOPUP on wsview\n");
     if(on_initmenupopup(hwnd, wParam, lParam, TRUE))
       return 0;
     break;

   case WM_UNINITMENUPOPUP:
     MTRACE("WM_UNINITMENUPOPUP on wsview\n");
     if(on_initmenupopup(hwnd, wParam, lParam, FALSE))
       return 0;
     break;

   case WM_MENUSELECT:
     MTRACE("WM_MENUSELECT on wsview\n");
     if(on_menuselect(hwnd, wParam, lParam))
       return 0;
     break;

   case WM_DRAWITEM:
     return g2pvt_on_draw_item(hwnd, (int)wParam, (LPDRAWITEMSTRUCT)lParam);

   case WM_MEASUREITEM:
     return g2pvt_on_measure_item(hwnd, (int)wParam, (LPMEASUREITEMSTRUCT)lParam);

   case WM_MOUSEACTIVATE:
     g2pvt_on_wm_mouseactivate(hwnd);
     break;

   case WM_MDIACTIVATE:
     /* If we are minimized, we don't get focus */
     if (hwnd == (HWND)lParam)
       g2pvt_send_window_activated(hwnd, -1);
     break;

   case WM_SETFOCUS:
     g2pvt_send_window_activated(hwnd, -1);
     break;			

   case WM_SYSCOMMAND:
     switch(wParam & 0xFFF0) {
      case SC_CLOSE:
	if(!g2pvt_syscommand_enabled_p(hwnd,SC_CLOSE))
	  return 0;
	break;
      case SC_VSCROLL:
      case SC_HSCROLL:
	*pValue = modal_scrollbar_loop(hwnd, message, wParam, lParam);
	return 0;
     }
     break;

   case WM_CLOSE:
     // FIXME: This is actually wrong. The window may decide to not close.
     g2pvt_send_window_closed(hwnd, -1);
     break;

   case WM_DESTROY:
     MTRACE("WindowDestroyed: hwnd %x [%d]\n", hwnd, window_info->window_handle);
     // In case window is destroyed without first being closed.
     g2pvt_send_window_closed(hwnd, -1);
     g2pvt_free_window_info(hwnd);
     break;
  }
  return rundef;
}

LRESULT WINAPI
WorkspaceViewWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT value = 0;

  if(g2pvt_swv_wndproc(hwnd, message, wParam, lParam, &value) == 0)
    return value;
  else
    return WorkspaceViewDefaultWndProc(hwnd, message, wParam, lParam);
}


/*
 * Native Image Planes C API
 */

#ifdef _DEBUG
static char *opcodeName(int opcode)
{
  switch(opcode) {
   case NIP_SHOW_WINDOW: return "SHOW_WINDOW";
   case NIP_MOVE_WINDOW: return "MOVE_WINDOW";
   case NIP_RESHAPE_WINDOW: return "RESHAPE_WINDOW";
   case NIP_RAISE_WINDOW: return "RAISE_WINDOW";
   case NIP_LOWER_WINDOW: return "LOWER_WINDOW";
   case NIP_DESTROY_WINDOW: return "DESTROY_WINDOW";
   case NIP_CAPTION_WINDOW: return "CAPTION_WINDOW";
   case NIP_INFLATE_WINDOW: return "INFLATE_WINDOW";
   case NIP_SCROLL_WINDOW: return "SCROLL_WINDOW";
   case NIP_CERASE_WINDOW: return "CERASE_WINDOW";
   case NIP_SET_MAX_SIZE: return "SET_MAX_SIZE";
   case NIP_RESTYLE_WINDOW: return "RESTYLE_WINDOW";
   case NIP_SET_ICON: return "SET_ICON";
   case NIP_SET_CLOSEABLE: return "SET_CLOSEABLE";
   case NIP_RESCALE_WINDOW: return "RESCALE_WINDOW";
   default: return "unknown";
  }
}
#endif

long g2ext_x11_create_window(long typeMask, long parent_hi, long parent_low, long handle, 
			     LPWSTR title, long style16, long exStyle,
			     long x, long y, long width, long height)
{
  HWND parent = (HWND) MAKELONG(parent_low, parent_hi);
  HWND hwnd = NULL;
  DWORD style = ((unsigned)style16) << 16;
  RECT r = {x, y, x + width, y + height};
  LPG2INFO info;
  HWND maximized_child = get_maximized_child();
  int type = typeMask & 0xF;	                /* Sync with nip-wintype-mask */
  BOOL editorWindow = (typeMask & 0x80) != 0;	/* FIXME: hack!!!! */

  MTRACE("Enter create_window typeMask=%x handle=%d style=%x parent=%x iswin:%d \"%ls\"\n", 
 	 typeMask, handle, style, parent, IsWindow(parent), title);

  ClientToWindowEx(&r, style, exStyle);

  G2_create_in_progress++;
  G2_window_handle = handle;	/* TWNG is unable to pass along the create param */

  switch(type) {
   case NIP_WINTYPE_CLASSIC:	/* Probably not useful. */
     hwnd = CreateWindowExW(exStyle, GensymTelewindowClass, NULL, style,
			    r.left, r.top, r.right-r.left, r.bottom-r.top,
			    hwndFrame, (HMENU)NULL, hInst, (LPVOID)handle);
     break;

   case NIP_WINTYPE_MDICHILD:
     if(maximized_child)
       G2_create_in_progress--;

     if(editorWindow)
       hwnd = g2pvt_create_editor(handle, title, style, exStyle, &r, FALSE);
     else
       hwnd = g2pvt_create_workspace_view(handle, hwndClient, title, style, &r);

     /* Note that new child windows (which these are) are always placed at the
        bottom on the stack, whereas G2 places new image-planes generally at the
        top of the stack. */

     info = GetlpG2Info(hwnd);
     if(info) info->window_handle = handle;

     if(maximized_child)
       G2_create_in_progress++;
     break;

   case NIP_WINTYPE_EMBEDDED:	/* An embedded window has a parent window not owned by G2. */
     if(parent != NULL && !IsWindow(parent)) {
       fprintf(stderr, "g2ext_x11_create_embedded_window: parent window %08x is invalid.\n",
	       parent);
       return -1;
     }
     if(parent != NULL)
       GetClientRect(parent, &r);	/* Overlay parent's client area exactly. */
     MTRACE("Create embedded window: parent: %08x\n", parent);

     // This is a bit of a kludge. In the case of embedded windows, the parent
     // frame of that window is what is operated on by
     // g2ext_x11_manage_window. For example, the SHOW and HIDE
     // operations. Those will effectively work on the embedded window, too, if
     // we keep the embedded window always showing. This is the kludgey fix for
     // HQ-5224819. The real problem is that we can't conflate windows and
     // frames in all cases. -fmw, 3/6/06
     style |= WS_VISIBLE;	// KLudge

     // KLudge: send MOVE/RESIZE events to G2 in this case because we've
     // completely ignored the size G2 wanted, and instead used the size from
     // our parent's client area.
     G2_create_in_progress--;
     hwnd = CreateWindowExW(exStyle, GensymWorkspaceViewClass, title, style,
			    r.left, r.top, r.right-r.left, r.bottom-r.top,
			    parent, (HMENU)NULL, hInst, (LPVOID)handle);
     G2_create_in_progress++;
     break;

   case NIP_WINTYPE_TOPLEVEL:	/* TODO: Could have a menu. */ 
     if(editorWindow)
       hwnd = g2pvt_create_editor(handle, title, style, exStyle, &r, TRUE);
     else
       hwnd = CreateWindowExW(exStyle, GensymWorkspaceViewClass, title, style,
			      r.left, r.top, r.right-r.left, r.bottom-r.top,
			      HWND_DESKTOP, (HMENU)NULL, hInst, (LPVOID)handle);
     break;
  }
  G2_window_handle = 0;
  G2_create_in_progress--;

#ifdef GENFLEX
	return handle; // this is small hack, we replace concept of window_index for genflex, so it now exactly is g2-like handle.
#endif

  if (hwnd == NULL) {
    fprintf(stderr, "Unable to create child window type %d with parent %08x: %s\n",
	    type, parent, g2pvt_get_last_error_string());
    return -1;
  }

  info = g2pvt_make_new_window_info(hwnd,handle);
  info->type = type;

  /* Update the Windows menu. Seems to require window showing first? */
  if(type == NIP_WINTYPE_MDICHILD) {
    SendMessage(hwndClient, WM_MDIREFRESHMENU, 0, 0);
    DrawMenuBar(hwndFrame);
  }

  MTRACE("Exit g2ext_x11_create_window\n");

  return info->window_index;
}

/* g2ext_x11_manage_window is a multipurpose function which gathers together
 * all of the miscellaneous operations on a native window. The arguments
 * are general purpose also, and are not always used for x,y values.
 */
long g2ext_x11_manage_window(long opcode, long window_index,
			     long x0, long y0, long x1, long y1,
			     LPWSTR string)
{
  HWND hwndArg = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  LPG2INFO info = GetlpG2Info(hwndArg);
  HWND frame = g2pvt_frame_window(hwndArg);
  HWND hwnd = frame ? frame : hwndArg; /* The hwnd on which we actually operate, in most cases. */
  HWND parent = GetParent(hwnd);
  RECT ow, nw, oc, sum, diff, t;
  HRGN hsum, hdiff;
  RECT r = {x0, y0, x1, y1};
  BOOL was_showing, allow_reshape_events;
  HWND maximized_child = get_maximized_child();


#ifdef GENFLEX
	
  /// UNDONE: use this insed af window_index: *info->window_handle*/ /* NOTE: we not need window_index at GenFlex, we need G2-like handle.*/
  /// but in GenFlex this not works, because I think 
  genflex_g2ext_x11_manage_window_callback(opcode, window_index,
			     x0, y0, x1, y1,
			     string); // TODO: do we need use here return value? Because there in this g2ext_x11_manage_window exists own return value. 
  return -1; // if we not return -1, then when this code works (for example opening small window code editor of name of workspace), then main window of genflex loose its header.
#endif

#ifdef _DEBUG
  MTRACE("%s idx:%d arg:%x frame:%x parent:%x hwnd:%x %d,%d %d,%d \"%ls\"\n",
    	 opcodeName(opcode), window_index, hwndArg, frame, parent, hwnd,
 	 x0, y0, x1, y1, string);
#endif

  if(!IsWindow(hwnd))
    return -1;

  /* If the window is iconified, then inflating is the same reshaping, since
   * the window will be fully refreshed when it is restored. */
  if(opcode == NIP_INFLATE_WINDOW && IsIconic(hwnd))
    opcode = NIP_RESHAPE_WINDOW;

  switch(opcode) {
   case NIP_SHOW_WINDOW:
     was_showing = IsWindowVisible(hwnd);
     /* Allow reshape events thru if Windows might be doing reshapes behind our back. */
     allow_reshape_events = (maximized_child != NULL) || g2pvt_tabbed_mdi_mode_p() ||
                            (x0 == SW_MAXIMIZE) || (x0 == SW_RESTORE);

     if(!allow_reshape_events)
       G2_reshape_in_progress++;
     switch(x0) {		/* nShowCmd */
      case SW_SHOWNORMAL:
      case SW_SHOW:
	ShowWindow(hwnd,x0);
	if(Frame_is_MDI)
	  SendMessage(hwndClient, WM_MDIACTIVATE, (WPARAM)hwnd, 0);
	break;

      case SW_SHOWDEFAULT:	/* We've defined this to mean activate but don't lift to top. */
	g_InhibitZorderChanges++;
	if(Frame_is_MDI)
	  SendMessage(hwndClient, WM_MDIACTIVATE, (WPARAM)hwnd, 0);
	else
	  ShowWindow(hwnd,SW_SHOW);
	g_InhibitZorderChanges--;
	break;

      case SW_SHOWNA:
      case SW_SHOWNOACTIVATE:
	ShowWindow(hwnd,x0);
	break;
      case SW_MAXIMIZE:
	if(Frame_is_MDI)
	  SendMessage(hwndClient, WM_MDIMAXIMIZE, (WPARAM)hwnd, 0);
	break;
      case SW_RESTORE:
	if(Frame_is_MDI)
	  SendMessage(hwndClient, WM_MDIRESTORE, (WPARAM)hwnd, 0);
	break;
      default:
	ShowWindow(hwnd,x0); /* Includes SW_MINIMIZE */
     }
     if(!allow_reshape_events)
       G2_reshape_in_progress--;

     /* Update Window menu if show state changed. */
     /* FIXME: Need to update all menus which have a Windows menu.
	If custom menu bar is displayed when a new window is created, we
	might not be updating the correct menu. */
     if(Frame_is_MDI && Frame_has_client && (was_showing != (IsWindowVisible(hwnd) != 0))) {
       SendMessage(hwndClient, WM_MDIREFRESHMENU, 0, 0);
       DrawMenuBar(hwndFrame);
     }
     break;

   case NIP_MOVE_WINDOW:
     /* Convert posn of client area UL corner to position of window UL corner. */
     ClientToWindow(hwnd,&r);

     MTRACE("....move-window %x from %d,%d to %d,%d iconic=%d\n",
	    hwnd, x0, y0, r.left, r.top, IsIconic(hwnd));

     mdi_restore();

     G2_reshape_in_progress++;
     SetWindowPosExx(hwnd, 0, &r, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
     G2_reshape_in_progress--;
     MTRACE("....move-window done.\n");
     break;
   
   // Added by SoftServe
   case NIP_SIZE_WINDOW:
     /* Convert posn of client area UL corner to position of window UL corner. */
     ClientToWindow(hwnd,&r);

     MTRACE("....size-window %x from %d,%d to %d,%d iconic=%d\n",
	    hwnd, x0, y0, r.left, r.top, IsIconic(hwnd));

     mdi_restore();

     G2_reshape_in_progress++;
     SetWindowPosExx(hwnd, 0, &r, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
     G2_reshape_in_progress--;
     MTRACE("....size-window done.\n");
     break;
   // End of SoftServe changes
	 
   case NIP_RESHAPE_WINDOW:
   case NIP_RESCALE_WINDOW:
     MTRACE("....reshape-window(0x%0x, %d,%d %dx%d) iconic=%d\n",
	    hwnd, x0, y0, x1-x0, y1-y0, IsIconic(hwnd));

     t=r;			      /* Save desired client rect. */
     ClientToWindow(hwnd,&r);	      /* Convert client-area shape to window shape. */
     /* GENSYMCID-1134: Fullscreen dialogs and kb saving */
     /* mdi_restore(); */	      /* TODO: first check whether really changing. */

     if(opcode == NIP_RESCALE_WINDOW)
       G2_inhibit_refresh_events_hwnd = hwnd;

     G2_reshape_in_progress++;
     SetWindowPosExx(hwnd, 0, &r, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
     UpdateWindow(hwnd);
     G2_reshape_in_progress--;

     if(opcode == NIP_RESCALE_WINDOW)
       G2_inhibit_refresh_events_hwnd = NULL;

     /* Erase any extra space outside the desired client area. */
     OffsetRect(&t, -t.left, -t.top);
     erase_outside_of_rect(hwnd,&t);

     MTRACE("....reshape-window done.\n");
     break;

   case NIP_INFLATE_WINDOW:
     /* Reshape the client area of the given window in the peculiar G2 style
	which leaves the common bits unchanged in the center, and expands or
	contracts the window edges around them.  Thus, the borders of the
	window appear to push individually outwards or inwards, rather than the
	window moving and resizing. See LISP move-image-plane-borders. */

     /* The WM_NCCALCSIZE messsage is made for this application (controlling how
	bits are saved during a resize), but I had problems getting it to work
	properly. So for now, we have this kludgely code. */

     MTRACE("Inflate-window %x, %d,%d %dx%d icon:%d\n",
	    hwnd, x0, y0, x1-x0, y1-y0, IsIconic(hwnd));

     /* I'd like to use SetWindowPosExx whether the window is minimized or not,
      * but so far I haven't been able to fix all the refresh problems when
      * inflating. So, for now we use it just for a minimized window, and do
      * region hacking and RedrawWindow otherwise. */
     t=r;			/* Save client rect. */
     if(IsIconic(hwnd)) {
       ClientToWindow(hwnd,&r);

       G2_inflate_in_progress++;
       G2_reshape_in_progress++;
       SetWindowPosExx(hwnd, 0, &r, SWP_NOZORDER | SWP_NOACTIVATE);
       G2_reshape_in_progress--;
       G2_inflate_in_progress--;

     } else {
       /* PCC = parent window's client coordinate system. */

       /* Compute old window rect in PCC. */
       GetWindowRect(hwnd,&ow);
       ScreenToClient(parent, (LPPOINT)&ow.left);
       ScreenToClient(parent, (LPPOINT)&ow.right);

       /* Compute old client rect in PCC. */
       GetClientRect(hwnd,&oc);
       MapWindowPoints(hwnd, parent, (LPPOINT)&oc, 2);

       /* Compute new window rect in PCC from new client rect (given as argument). */
       nw = r;
       ClientToWindow(hwnd,&nw);

       UnionRect(&sum,&ow,&nw);	/* Union of window rects */
       IntersectRect(&diff,&oc,&r); /* Intersection of client rects */
       hsum  = CreateRectRgnIndirect(&sum);
       hdiff = CreateRectRgnIndirect(&diff);
       CombineRgn(hsum, hsum, hdiff, RGN_DIFF);

       /* GENSYMCID-1134: Fullscreen dialogs and kb saving */
       /* mdi_restore(); */		/* FIXME: This leaves the screen a mess. */

       G2_reshape_in_progress++;
       G2_inflate_in_progress++;
       SetWindowPos(hwnd,0, nw.left, nw.top, nw.right-nw.left, nw.bottom-nw.top,
		    SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOREDRAW);
       /* Need RDW_ERASE to erase newly exposed MDI client area, even though MDI
	* children are not erased, due to the explicit check on
	* G2_inflate_in_progress in the body of their WM_ERASEBKGND handler. */
       RedrawWindow(parent, NULL, hsum, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME |
		    RDW_ALLCHILDREN | RDW_UPDATENOW);
       G2_inflate_in_progress--;
       G2_reshape_in_progress--;

       DeleteObject(hdiff);
       DeleteObject(hsum);
     }

     /* Erase any extra space outside the desired client area. */
     OffsetRect(&t, -t.left, -t.top);
     erase_outside_of_rect(hwnd,&t);

     MTRACE("....inflate-window done.\n");
     break;

   case NIP_RAISE_WINDOW:
     BringWindowToTop(hwnd);
     break;

   case NIP_LOWER_WINDOW:
     SetWindowPos(hwnd,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
     break;

   case NIP_ZORDER_WINDOW:
     set_window_zorder(hwnd, x0); /* X0 is the after-window handle or enum */
     break;

   case NIP_DESTROY_WINDOW: 
     if(Frame_is_MDI && info && info->type == NIP_WINTYPE_MDICHILD)
       SendMessage(hwndClient, WM_MDIDESTROY, (WPARAM)hwnd, 0);
     else
       DestroyWindow(hwnd);
     break;

   case NIP_CAPTION_WINDOW:
     SetWindowTextW(hwnd,string);
     break;

   case NIP_SET_MAX_SIZE:	      /* Maximum tracking size. */
     if(info) {
       ClientToWindow(hwnd,&r);
       info->max_tracking_size.x = r.right - r.left;
       info->max_tracking_size.y = r.bottom - r.top;
     }
     break;

   case NIP_CERASE_WINDOW:	      /* Erase complement of region given by rect. */
     erase_outside_of_rect(hwndArg,&r);	/* NOT on the frame! */
     break;

   case NIP_RESTYLE_WINDOW:	      /* Change window frame style */
     {
       LONG styleMask = WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME
	 | WS_SYSMENU | WS_HSCROLL | WS_VSCROLL | WS_DLGFRAME | WS_BORDER;
       LONG exStyleMask = WS_EX_DLGMODALFRAME | WS_EX_TOOLWINDOW | 
	 WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE;

       LONG style = ((x0<<16) & styleMask) | GetWindowLong(hwnd,GWL_STYLE) & (~styleMask);
       LONG exStyle = (y0 & exStyleMask) | GetWindowLong(hwnd,GWL_EXSTYLE) & (~exStyleMask);

       GetClientRect(hwnd,&r);	/* Preserve shape of the client area. */
       MapWindowPoints(hwnd, parent, (LPPOINT)&r, 2);
       SetWindowLong(hwnd, GWL_STYLE, style);
       SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);
       ClientToWindow(hwnd,&r);

       G2_reshape_in_progress++;
       SetWindowPosExx(hwnd, 0, &r, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
       G2_reshape_in_progress--;
     }
     break;

   case NIP_SET_ICON:
     g2pvt_set_window_icon(hwnd, x0);
     break;

   case NIP_SET_CLOSEABLE:
     g2pvt_set_window_closeable(hwnd, x0 != 0);
     break;

   case NIP_SET_BACKGROUND_COLOR:
     g2pvt_set_workspace_view_background_color(hwnd, (COLORREF)x0);
     break;

   default: 
     fprintf(stderr,"Unknown command to g2ext_x11_manage_window: 0x%0x\n", opcode);
     return -1;
  }

  MTRACE("Exit g2ext_x11_manage_window\n");

  return 1;
}


/* Maybe this should both restack and reposition, resize, to bring TW
 * completely in sync?  Must be called in sequence 1-2-3, with no other
 * modifications to windows in-between. This would simply take a list of
 * windows to stack if it was easier to pass lists to C. */
long g2ext_x11_stack_windows(long opcode, long prev_index, long window_index)
{
  HWND hwndPrev, hwnd;
  int flags;
  static HDWP hwdp = NULL;

  MTRACE("g2ext_x11_stack_windows %d %d %d\n", opcode, prev_index, window_index);

  switch(opcode) {
   case 1:
     mdi_restore();		// Is this really necessary?
     hwdp = BeginDeferWindowPos(prev_index); // prev_index == numWindows here.
     break;
   case 2:
     hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
     flags = SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE;
     if(prev_index<0)
       hwndPrev = HWND_TOP;
     else
       hwndPrev = (HWND)g2ext_map_g2pointer_to_cpointer(prev_index);
     hwdp = DeferWindowPos(hwdp, hwnd, hwndPrev, 0,0,0,0, flags);
     break;
   case 3:
     G2_reshape_in_progress++;
     EndDeferWindowPos(hwdp);
     G2_reshape_in_progress--;
     hwdp = NULL;
     break;
  }
  return 0;
}


/*
 * TW ActiveX Control Support
 */

static void notify_parent(UINT msg, WPARAM wParam, LPARAM lParam)
{
  if(IsWindow(parent_GhwndWin))
    PostMessage(parent_GhwndWin, msg, wParam, lParam);
}

long g2ext_x11_tell_control_our_session_id (long sessionID)
{
  if(!Frame_is_embedded)
    return -1;

  notify_parent(WM_TELEWINDOWS_SESSION_ID, (WPARAM)sessionID, (LPARAM)GhwndWin);

  return 1;
}




/*
 * MDI Child Containers -- for custom dialogs, charts, and the native editor.
 */

static BOOL inhibit_close_notify_p(HWND mdiContainerHwnd)
{
  return GetWindowLongPtr(mdiContainerHwnd, GWLP_USERDATA) == 123;
}

extern BOOL IsLockedDialog(HWND hWnd);
extern BOOL IsCommandLocked(ULONG cmd);
extern GENSYMDIALOG *g2pvt_find_dialog_by_id(long dlgId);

/* TODO: Slight change would make this useful for top-level windows, too. */

LONG WINAPI GensymMDIChildWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HWND child = GetWindow(hwnd,GW_CHILD);
  int handle = g2pvt_window_handle(hwnd);

  switch(message) {
   case WM_CREATE:
     handle = ((MDICREATESTRUCT*)(((CREATESTRUCT *)lParam)->lpCreateParams))->lParam;
     MTRACE("WM_CREATE %08x [%d]\n", hwnd, handle);
     g2pvt_record_window_handle(hwnd, handle);
     break;

   case WM_PARENTNOTIFY:
     MTRACE("WM_PARENTNOTIFY %08x %08x\n", wParam, lParam);
     if(LOWORD(wParam) == WM_DESTROY)
       PostMessage(hwnd, WM_CLOSE, 0, 0);
     return 0;

   case WM_MOUSEACTIVATE:
     MTRACE("(mdi) WM_MOUSEACTIVATE [%d] hwnd:%08x child:%08x\n", handle, hwnd, child);
     g2pvt_on_wm_mouseactivate(hwnd);
     if(LOWORD(lParam) == HTCLIENT)     /* NOTE: Near-duplicate code in CChildFrm::OnMouseActivate */
       switch(HIWORD(lParam)) {
	case WM_LBUTTONDOWN:
	  if(hwnd == (HWND)SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0))
	    BringWindowToTop(hwnd);
	  break;
	case WM_RBUTTONDOWN:
	  if(g_NoRaiseOnRightClick) {
	    g_InhibitZorderChanges++;
	    SendMessage(hwndClient, WM_MDIACTIVATE, (WPARAM)hwnd, 0);
	    g_InhibitZorderChanges--;
	    return MA_NOACTIVATE;
	  }
	  break;
       }
     break;

   case WM_MDIACTIVATE:
     MTRACE("(mdi) WM_MDIACTIVATE [%d] hwnd:%08x child:%08x\n", handle, hwnd, child);
     if (hwnd == (HWND)lParam && handle > 0)
       g2pvt_send_window_activated(hwnd, handle);
     break;

   case WM_SETFOCUS:
     MTRACE("(mdi) WM_SETFOCUS [%d] hwnd:%08x child:%08x\n", handle, hwnd, child);
     if(child) {
       SetFocus(child);
       g2pvt_send_window_activated(hwnd, handle);
     }
     return 0;

   case WM_WINDOWPOSCHANGING:
     if(g_InhibitZorderChanges > 0)
       ((WINDOWPOS*)lParam)->flags |= SWP_NOZORDER;
     break;

   case WM_MOVE:
     MTRACE("WM_MOVE [%d] %08x %d,%d\n", handle, child, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
     if(handle > 0)
       g2pvt_send_window_moved(hwnd, handle, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
     break;

   case WM_SIZE:
     {
       int w = LOWORD(lParam);
       int h = HIWORD(lParam);
       if (child && wParam != SIZE_MINIMIZED)
         SetWindowPos(child,HWND_BOTTOM,0,0,w,h,SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
       if(handle > 0) {
         GENSYMDIALOG *pDialog = g2pvt_find_dialog_by_id(handle);
         if ((pDialog == NULL) || (pDialog->inShowDialog == 0)) {
           g2pvt_send_window_sized(hwnd, handle, wParam, w, h);
         }
       }
     }
     break;

   case WM_GETMINMAXINFO:
     {
       LPMINMAXINFO pMMI = (LPMINMAXINFO) lParam;
       MINMAXINFO mmi = *pMMI;
       RECT r = {0};

       /* Permit the child have an opinion on the minimum tracking size
	* only. Then convert the child (=client) result back to our window
	* size. */

       if(SendMessage(child, message, wParam, (LPARAM)&mmi) == 0) {
	 if(mmi.ptMinTrackSize.x != pMMI->ptMinTrackSize.x ||
	    mmi.ptMinTrackSize.y != pMMI->ptMinTrackSize.y) {
	   r.right = mmi.ptMinTrackSize.x;
	   r.bottom = mmi.ptMinTrackSize.y;
	   ClientToWindow(hwnd,&r);
	 }
	 if(mmi.ptMinTrackSize.x != pMMI->ptMinTrackSize.x)
	   pMMI->ptMinTrackSize.x = r.right - r.left;
	 if(mmi.ptMinTrackSize.y != pMMI->ptMinTrackSize.y)
	   pMMI->ptMinTrackSize.y = r.bottom - r.top;
       }
     }
     break;

   case WM_ENTERSIZEMOVE:
     SendMessage(child, WM_PARENT_IS_MOVING, 0, 0);
     g2pvt_enter_modal_loop();
     break;
   case WM_EXITSIZEMOVE:
     g2pvt_exit_modal_loop();
     break;

   case WM_COMMAND:
     {
       int code = HIWORD(wParam);
       int id = LOWORD(wParam);
       HWND control = (HWND)lParam;

       if(IsWindow(child))
	 SendMessage(child, WM_REFLECT_COMMAND, wParam, lParam);

       if(id == MAGIC_CHART_ID)
	 g2pvt_on_chart_notification(hwnd, control, code);
     }
     break;

   case WM_SYSCOMMAND:
     if(((wParam & 0xFFF0) == SC_CLOSE) && !g2pvt_syscommand_enabled_p(hwnd,SC_CLOSE))
       return 0;
	 else if (IsWindow(child) && IsLockedDialog(child) && IsCommandLocked(wParam & 0xFFF0))
       return 0;
     break;

   case WM_CLOSE:
     /* For charts, we have to call PEdestroy -- just WM_CLOSE leaks GDI resources. */
     if(child && GetDlgCtrlID(child) == MAGIC_CHART_ID) {
       g2pvt_on_chart_notification(hwnd, child, PEWN_DESTROYED);
       child = NULL;
     }

     /* Ask the child if it wants to close. NOTE: This is very questionable code. */
     if(child && SendMessage(child, WM_CLOSE, 0, 0) == 0)
       return 0;
     if(handle>0 && !inhibit_close_notify_p(hwnd))
       g2pvt_send_window_closed(hwnd, handle);
     break;

   case WM_DESTROY:
     if(child)
       SendMessage(child, WM_PARENT_IS_CLOSING, (WPARAM)hwnd, 0);
     g2pvt_record_window_handle(hwnd, -1);
     g2pvt_free_window_info(hwnd);
     break;
  }
  return DefMDIChildProcW(hwnd, message, wParam, lParam);
}

/* Used only by custom dialogs. */
HWND g2pvt_show_mdi_dialog(HWND hwndDlg, int handle)
{
  HWND hwnd = g2pvt_create_mdi_child_dialog(hwndDlg, handle, TRUE);
  /* Inhibit the WM_CLOSE notification, since custom dialogs handle it their own way. */
  if(hwnd != hwndDlg)
    SetWindowLongPtr(hwnd, GWLP_USERDATA, 123);
  return hwnd;
}

/* An internal routine which shows the dialog in an MDI child window. */
HWND g2pvt_create_mdi_child_dialog(HWND hwndDlg, int handle, BOOL show_p)
{
  RECT r,w;
  DWORD style, exStyle;
  HWND hwnd;
  HICON hIcon;
  BOOL resizable;
  wchar_t title[256];
  SCROLLINFO scrInfo;

  ShowWindow(hwndDlg,SW_HIDE);
  GetWindowTextW(hwndDlg, title, 255);
  title[255] = L'\0';

  GetWindowRect(hwndDlg,&w);
  MapWindowPoints(NULL, hwndClient, (LPPOINT)&w, 2);

  GetClientRect(hwndDlg,&r);

  resizable = (GetWindowLong(hwndDlg, GWL_STYLE) & WS_THICKFRAME) != 0;
  hIcon = (HICON) SendMessage(hwndDlg, WM_GETICON, ICON_SMALL, 0);

  /* Style for the MDI child container */
  style = WS_CHILD | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_CLIPCHILDREN;
  if(resizable)
    style |= WS_MAXIMIZEBOX | WS_THICKFRAME;
  exStyle = 0;

  hwnd = CreateMDIWindowW((LPWSTR)GensymMDIChildClass, title, style,
			  w.left, w.top, w.right-w.left, w.bottom-w.top,
			  hwndClient, hInst, (LPARAM)handle);
  if(hwnd == NULL) {
    fprintf(stderr,"CreateMDIWindow %d: %s\n", GetLastError(), g2pvt_get_last_error_string());
    if(show_p)
      ShowWindow(hwndDlg,SW_SHOW);
    return hwndDlg;
  }

  g2pvt_bless_mdi_child(hwnd, handle); // If MFC, creates permanent CWnd object.

  scrInfo.cbSize = sizeof(SCROLLINFO);
  scrInfo.fMask = SIF_ALL;
  if(GetScrollInfo(hwndDlg, SB_VERT, &scrInfo)) {
    SetWindowLong(hwndDlg, GWL_STYLE, DS_SETFONT | WS_CHILD | WS_VSCROLL);
    r.right += GetSystemMetrics(SM_CXVSCROLL);
  } else {
    SetWindowLong(hwndDlg, GWL_STYLE, DS_SETFONT | WS_CHILD);
  }
  SetWindowLong(hwndDlg, GWL_EXSTYLE, WS_EX_CONTROLPARENT);

  if(!SetParent(hwndDlg,hwnd))
    fprintf(stderr, "SetParent %d: %s\n", GetLastError(), g2pvt_get_last_error_string());

  if(! SetWindowPos(hwndDlg, HWND_BOTTOM, 0,0, r.right-r.left, r.bottom-r.top,
		    SWP_NOACTIVATE|SWP_FRAMECHANGED))
    fprintf(stderr,"SetWindosPos %d: %s\n", GetLastError(), g2pvt_get_last_error_string());

  if(hIcon) {			/* Transfer icon from dialog to MDI child. */
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)0);
  }

  SetActiveWindow(hwndFrame);	// Initial dialog creation clobbered frame's activation.
  ShowWindow(hwndDlg,SW_SHOW);
  if(show_p) {
    g2pvt_activate_window(hwnd);
    InvalidateRect(hwndDlg, NULL, TRUE);
  }

  return hwnd;
}

static FARPROC get_proc_address(HMODULE hMod, LPCSTR name, int nargs)
{
  FARPROC proc;
  char buf[128];

  proc = GetProcAddress(hMod,name);
  if(!proc) {
    sprintf(buf, "_%s@%d", name, nargs*4); /* Decorated name in old DLL. */
    proc = GetProcAddress(hMod,buf);
  }

  return proc;
}

// FIXME: This creates the file if it can.
BOOL g2pvt_is_file_writable(LPCWSTR pathname)
{
  HANDLE hFile;
  BOOL rc = FALSE;
  UINT errMode = SetErrorMode(SEM_FAILCRITICALERRORS);

  hFile = CreateFileW(pathname, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if(hFile != INVALID_HANDLE_VALUE) {
    CloseHandle(hFile);
    rc = TRUE;
  }
  SetErrorMode(errMode);
  return rc;
}




/*
 * Native editor stubs
 */
typedef struct {
  struct Stack_info* next;
  LPWSTR proc_name;	
  LPWSTR args;
  LPWSTR env;
} Stack_info, *Stack_info_ptr;

typedef struct {
  struct Tree_node_view_info* next;
  LPWSTR uuid_value;	
  LPWSTR names_value;	
  LPWSTR label_value;
  LPWSTR text_value;
  LPWSTR frame_type_value;
} Tree_node_view_info, *Tree_node_view_info_ptr;

#ifndef CODEJOCK

HWND g2pvt_create_editor(long handle, LPWSTR title, DWORD style, DWORD exStyle, RECT* pRect, BOOL topLevel)
{
#ifdef GENFLEX
  return genflex_g2pvt_create_editor(handle, title, style, exStyle, topLevel);
#else
  return NULL;
#endif
}

long g2ext_manage_editor(long opcode, long handle, LPWSTR string, long n1, long n2)
{
#ifdef GENFLEX
  return genflex_g2ext_manage_editor_callback(opcode, handle, string, n1, n2);
#else
  return -1;
#endif
}

long g2ext_debugger_dialog(int opcode, LPWSTR title, LPWSTR label, LPWSTR proc, 
			   LPWSTR env, int flags, int line, int tab_width,
			   unsigned short *bkpts)
{
  return -1;
}

LPWSTR copy_string(const LPWSTR source) {
   if(source != NULL)
    {
       LPWSTR result = malloc((wcslen(source)+1)*sizeof(WCHAR));
       wcscpy(result, source);
       return result;
    }
    else
    {
       return NULL;
    }

}

Stack_info_ptr create_stack_info(LPWSTR proc_name, LPWSTR args, LPWSTR env) {
	Stack_info_ptr info_pointer = malloc(sizeof(Stack_info));
	info_pointer->next = NULL;
	info_pointer->proc_name = copy_string(proc_name);
	info_pointer->args = copy_string(args);
	info_pointer->env = copy_string(env);
	return info_pointer;
}

Stack_info_ptr g2ext_add_debug_info(Stack_info_ptr info_pointer, LPWSTR proc_name, LPWSTR args, LPWSTR env) {
  if (info_pointer == NULL) {
    info_pointer = create_stack_info(proc_name, args, env);
  }   
  else {
	Stack_info_ptr last = info_pointer;
	while (last->next != NULL)
	  last = last->next;
	last->next = create_stack_info(proc_name, args, env);
  }
  return info_pointer;
}

long g2ext_debug_info_received(Stack_info_ptr info_pointer)
{
#ifdef GENFLEX
  return genflex_g2ext_debug_info_received_callback(*info_pointer);
#else
  return -1;
#endif
}

Tree_node_view_info_ptr create_tree_node_view_info(LPWSTR uuid_value, LPWSTR names_value, LPWSTR label_value, LPWSTR text_value, LPWSTR frame_type_value) {
	Tree_node_view_info_ptr info_pointer = malloc(sizeof(Tree_node_view_info));
	info_pointer->next = NULL;
	info_pointer->uuid_value = copy_string(uuid_value);
	info_pointer->names_value = copy_string(names_value);
	info_pointer->label_value = copy_string(label_value);
	info_pointer->text_value = copy_string(text_value);
	info_pointer->frame_type_value = copy_string(frame_type_value);
	return info_pointer;
}

Tree_node_view_info_ptr g2ext_add_tree_node_view_info(Tree_node_view_info_ptr info_pointer, LPWSTR uuid_value, LPWSTR names_value, LPWSTR label_value, LPWSTR text_value, LPWSTR frame_type_value) {
  if (info_pointer == NULL) {
	  info_pointer = create_tree_node_view_info(uuid_value, names_value, label_value, text_value, frame_type_value);
  }   
  else {
	Tree_node_view_info_ptr last = info_pointer;
	while (last->next != NULL)
	  last = last->next;
	last->next = create_tree_node_view_info(uuid_value, names_value, label_value, text_value, frame_type_value);
  }
  return info_pointer;
}

long g2ext_tree_node_view_info_received(Tree_node_view_info_ptr info_pointer)
{
#ifdef GENFLEX
  return genflex_g2ext_tree_node_view_info_received_callback(*info_pointer);	
#else
  return -1;
#endif
}

long g2ext_genflex_debugger_step(long g2_handle, long line, LPWSTR proc_code, LPWSTR env)
{
#ifdef GENFLEX
  return genflex_g2ext_debugger_step_callback(g2_handle, line, proc_code, env);
#else
  return -1;
#endif
}

int g2ext_remove_tree_nodes_range(LPWSTR UUID_value){
#ifdef GENFLEX
  return genflex_g2ext_remove_tree_nodes_range_callback(UUID_value);
#else
  return -1;
#endif
}

#else

Stack_info_ptr g2ext_add_debug_info(Stack_info_ptr info_pointer, LPWSTR proc_name, LPWSTR args, LPWSTR env) {
  return NULL;
}

long g2ext_debug_info_received(Stack_info_ptr info_pointer)
{
  return -1;
}

Tree_node_view_info_ptr g2ext_add_tree_node_view_info(Tree_node_view_info_ptr info_pointer, LPWSTR uuid_value, LPWSTR names_value, LPWSTR label_value, LPWSTR text_value, LPWSTR frame_type_value) {
  return NULL;
}

long g2ext_tree_node_view_info_received(Tree_node_view_info_ptr info_pointer)
{
  return -1;
}

long g2ext_genflex_debugger_step(long g2_handle, long line, LPWSTR proc_code, LPWSTR env)
{
  return -1;
}

long g2ext_remove_tree_nodes_range(LPWSTR UUID_value){
  return -1;
}
#endif

/*
 * Charts
 */

#ifndef UNICODE
#define UNICODE
#endif

#include "pegrpapi.h"

/* Defines gTab and pe_load_functions(HMODULE hMod) and uses get_proc_address() */
#include "peimport.h"

#define CHARTING_DLL "PEGRP32F.DLL"
#define OLD_CHARTING_DLL "PEGRP32G.DLL"

// .01mm/pixel = 1/100 inch/pixel * 25.4 mm/inch * 100 .01mm/mm = 29.5
#define WMF_UNITS_PER_PIXEL 25

#define CHART_CREATE 1		// Opcodes
#define CHART_DESTROY 2
#define CHART_PRINT 3
#define CHART_UPDATE 4
#define CHART_PARTIAL_UPDATE 5
#define CHART_COPY 6
#define CHART_EXPORT 7

#define CHART_FORMAT_JPEG 1	// Export formats
#define CHART_FORMAT_PNG 2
#define CHART_FORMAT_BMP 3
#define CHART_FORMAT_WMF 4
#define CHART_FORMAT_SVG 5

#define CHART_SUCCESS 0		// Return codes
#define CHART_NO_WINDOW 1
#define CHART_INAPPROPRIATE_PROPERTY 2
#define CHART_INVALID_ARRAY_PROPERTY 3
#define CHART_INVALID_FLOAT_PROPERTY 4
#define CHART_SET_FAILED 5
#define CHART_EXPORT_FAILED 6

#define CV_EVENT_CLICK 2	// Events
#define CV_EVENT_CURSOR_MOVE 2
#define CV_EVENT_MENU_CHOICE 3

#define ETRACE G2TRACE

#define DEFAULT_DIM (-30000)	// Keep in sync with LISP cw-usedefault
#define Def(x) (((x)==DEFAULT_DIM) ? CW_USEDEFAULT : (x))

#define IsSciGraph(hPE) (PEnget(hPE,PEP_nOBJECTTYPE) == PECONTROL_SGRAPH)
#define IsContourPlottingMethod(v) ((v) == PEGPM_CONTOURCOLORS || (v) == PEGPM_CONTOURLINES)

// Returns non-zero if DLL found. Called on startup, unfortunately.
long g2ext_get_charting_library_version(char *buf, int buflen)
{
  char *version = g2pvt_get_module_version(CHARTING_DLL);
  if(!version)
    version = g2pvt_get_module_version(OLD_CHARTING_DLL);

  if(!version)
    g2pvt_notify_user("Warning: Charting DLL %s not found.\n", CHARTING_DLL);

  ZeroMemory(buf,buflen);
  if(version)
    strncpy(buf, version, buflen-1);

  return strlen(buf);
}

static BOOL ensure_charting_dll()
{
  static HMODULE hMod = NULL;

  if(hMod == NULL) {
    if((hMod = LoadLibrary(CHARTING_DLL)))
      g2pvt_notify_user("Using charting DLL %s version %s\n",
			CHARTING_DLL, g2pvt_get_module_version(CHARTING_DLL));

    else if((hMod = LoadLibrary(OLD_CHARTING_DLL)))
      g2pvt_notify_user("Warning: Latest charting DLL not found, using %s version %s\n",
			OLD_CHARTING_DLL, g2pvt_get_module_version(OLD_CHARTING_DLL));
    else
      g2pvt_notify_user("Error: Charting DLL %s not found.\n", CHARTING_DLL);

    if(hMod)
      pe_load_functions(hMod);
  }
  return (hMod != NULL) && (gTab.pPEcreate != NULL);
}


/* TWNG has different versions of these routines. */
extern HWND g2pvt_find_pechart(int handle);
extern BOOL g2pvt_pechart_ticks(HWND hPE, int **update_tick, int **data_tick);

extern long g2_jchart_set_int(long handle, long prop, long i, long j, long value);
extern long g2_jchart_set_string(long handle, long prop, long i, long j, LPWSTR string);
extern long g2_jchart_set_double(long handle, long prop, long i, long j, double value);
extern long g2_jchart_set_double_array(long handle, long prop, long start, long count, double *array);

#ifndef CODEJOCK
HWND g2pvt_find_pechart(int handle)
{
  HWND hwnd = g2pvt_find_window(handle);
  return hwnd ? GetWindow(hwnd,GW_CHILD) : NULL;
}

BOOL g2pvt_pechart_ticks(HWND hPE, int **update_tick, int **data_tick)
{
  LPG2INFO info = GetlpG2Info(GetParent(hPE)); // NOTE: Assuming MDI child here.
  *update_tick = info ? &info->chart_update_tick : NULL;
  *data_tick   = info ? &info->chart_data_tick : NULL;
  return info != NULL;
}

long g2_jchart_set_int(long handle, long prop, long i, long j, long value)
{
	return 0;
}

long g2_jchart_set_string(long handle, long prop, long i, long j, LPWSTR string)
{
	return 0;
}

long g2_jchart_set_double(long handle, long prop, long i, long j, double value)
{
	return 0;
}

long g2_jchart_set_double_array(long handle, long prop, long start, long count, double *array)
{
	return 0;
}
#endif

void g2pvt_pechart_destroy(HWND hPE)
{
  PEdestroy(hPE);
}

// Given a data property, return equivalent one for other precision
static int flip_float_property(int prop)
{
  switch(prop) {
   case PEP_faXDATA: return PEP_faXDATAII;
   case PEP_faXDATAII: return PEP_faXDATA;
   case PEP_faAPPENDXDATA: return PEP_faAPPENDXDATAII;
   case PEP_faAPPENDXDATAII: return PEP_faAPPENDXDATA;
   case PEP_faYDATA: return PEP_faYDATAII;
   case PEP_faYDATAII: return PEP_faYDATA;
   case PEP_faAPPENDYDATA: return PEP_faAPPENDYDATAII;
   case PEP_faAPPENDYDATAII: return PEP_faAPPENDYDATA;
   case PEP_faZDATA: return PEP_faZDATAII;
   case PEP_faZDATAII: return PEP_faZDATA;
   case PEP_faAPPENDZDATA: return PEP_faAPPENDZDATAII;
   case PEP_faAPPENDZDATAII: return PEP_faAPPENDZDATA;
  }
  return prop;
}

// TODO: Others?
static BOOL single_float_property_p(int prop)
{
  return (prop == PEP_faXDATA || prop == PEP_faAPPENDXDATA ||
	  prop == PEP_faYDATA || prop == PEP_faAPPENDYDATA ||
	  prop == PEP_faZDATA || prop == PEP_faAPPENDZDATA || prop == PEP_faMULTIAXESPROPORTIONS);
}

static BOOL double_float_property_p(int prop)
{
  return (prop == PEP_faXDATAII || prop == PEP_faAPPENDXDATAII ||
	  prop == PEP_faYDATAII || prop == PEP_faAPPENDYDATAII ||
	  prop == PEP_faZDATAII || prop == PEP_faAPPENDZDATAII);
}

static BOOL append_data_property_p(int prop)
{
  return (prop == PEP_faAPPENDXDATA || prop == PEP_faAPPENDXDATAII ||
	  prop == PEP_faAPPENDYDATA || prop == PEP_faAPPENDYDATAII ||
	  prop == PEP_faAPPENDZDATA || prop == PEP_faAPPENDZDATAII);
}

// Properties which affect the data display.
static BOOL data_property_p(int prop)
{
  return (single_float_property_p(prop) ||
	  double_float_property_p(prop) ||
	  prop == PEP_nSUBSETS ||
	  prop == PEP_nPOINTS ||
	  prop == PEP_dwaSUBSETCOLORS ||
	  prop == PEP_dwaPOINTCOLORS ||
	  prop == PEP_naPOINTTYPES ||
	  prop == PEP_naSUBSETFORPOINTCOLORS ||
	  prop == PEP_naSUBSETFORPOINTTYPES ||
	  prop == PEP_naSUBSETLINETYPES ||
	  prop == PEP_naSUBSETPOINTTYPES ||
	  prop == PEP_dwBARBORDERCOLOR ||
	  prop == PEP_bFIXEDLINETHICKNESS ||
	  prop == PEP_dwaSUBSETSHADES);
}

static BOOL zoom_property_p(int prop)
{
  return (prop==PEP_hZOOMCURSOR ||
	  prop==PEP_nZOOMSTYLE ||
	  prop==PEP_nUNDOZOOMMENU ||
	  prop==PEP_nALLOWZOOMING ||
	  prop==PEP_bZOOMMODE ||
	  prop==PEP_fZOOMMINY ||
	  prop==PEP_fZOOMMAXY ||
	  prop==PEP_nZOOMINTERFACEONLY ||
	  prop==PEP_fZOOMMINX ||
	  prop==PEP_fZOOMMAXX ||
	  prop==PEP_nZOOMMINAXIS ||
	  prop==PEP_nZOOMMAXAXIS ||
	  prop==PEP_fZOOMMINRY ||
	  prop==PEP_fZOOMMAXRY ||
	  prop==PEP_fZOOMMINTX ||
	  prop==PEP_fZOOMMAXTX ||
	  prop==PEP_bSCROLLINGVERTZOOM ||
	  prop==PEP_bSCROLLINGHORZZOOM);
}

static BOOL pie_property_p(int prop)
{
  return (prop == PEP_bALLOWBOTTOMTITLEHOTSPOTS ||
          prop == PEP_bALLOWCOLORPAGE ||
          prop == PEP_bALLOWCUSTOMIZATION ||
          prop == PEP_bALLOWDEBUGOUTPUT ||
          prop == PEP_bALLOWEXPORTING ||
          prop == PEP_bALLOWFONTPAGE ||
          prop == PEP_bALLOWJPEGOUTPUT ||
          prop == PEP_bALLOWMAXIMIZATION ||
          prop == PEP_bALLOWPAGE1 ||
          prop == PEP_bALLOWPAGE2 ||
          prop == PEP_bALLOWPOINTHOTSPOTS ||
          prop == PEP_bALLOWPOPUP ||
          prop == PEP_bALLOWSTYLEPAGE ||
          prop == PEP_bALLOWSUBTITLEHOTSPOTS ||
          prop == PEP_bALLOWSUBSETHOTSPOTS ||
          prop == PEP_bALLOWTITLEHOTSPOTS ||
          prop == PEP_bALLOWUSERINTERFACE ||
          prop == PEP_hARROWCURSOR ||
          prop == PEP_nAUTOEXPLODE ||
          prop == PEP_bAUTOIMAGERESET ||
          prop == PEP_nBITMAPGRADIENTMENU ||
          prop == PEP_bBITMAPGRADIENTMODE ||
          prop == PEP_nBORDERTYPEMENU ||
          prop == PEP_nBORDERTYPES ||
          prop == PEP_nCHARSET ||
          prop == PEP_bCUSTOM ||
          prop == PEP_naCUSTOMMENU ||
          prop == PEP_naCUSTOMMENULOCATION ||
          prop == PEP_naCUSTOMMENUSTATE ||
          prop == PEP_szaCUSTOMMENUTEXT ||
          prop == PEP_nCUSTOMIZEDIALOGMENU ||
          prop == PEP_nDATALABELTYPE ||
          prop == PEP_nDATAPRECISION ||
          prop == PEP_nDATAPRECISIONMENU ||
          prop == PEP_nDATASHADOWMENU ||
          prop == PEP_bDATASHADOWS ||
          prop == PEP_nDEFORIENTATION ||
          prop == PEP_szDESKBMPFILENAME ||
          prop == PEP_nDESKBMPSTYLE ||
          prop == PEP_dwDESKCOLOR ||
          prop == PEP_dwDESKCOLOR ||
          prop == PEP_dwDESKGRADIENTEND ||
          prop == PEP_dwDESKGRADIENTSTART ||
          prop == PEP_nDESKGRADIENTSTYLE ||
          prop == PEP_nDIALOGRESULT ||
          prop == PEP_bDIALOGSHOWN ||
          prop == PEP_bDIRTY ||
          prop == PEP_bDISABLE3DSHADOW ||
          prop == PEP_nDROPSHADOWOFFSETX ||
          prop == PEP_nDROPSHADOWOFFSETY ||
          prop == PEP_nDROPSHADOWSTEPS ||
          prop == PEP_nDROPSHADOWWIDTH ||
          prop == PEP_nEXPORTDIALOGMENU ||
          prop == PEP_nFIXEDFONTMENU ||
          prop == PEP_bFIXEDFONTS ||
          prop == PEP_bFOCALRECT ||
          prop == PEP_nFONTSIZE ||
          prop == PEP_fFONTSIZEALCNTL ||
          prop == PEP_fFONTSIZECPCNTL ||
          prop == PEP_fFONTSIZEGNCNTL ||
          prop == PEP_fFONTSIZEGLOBALCNTL ||
          prop == PEP_fFONTSIZEMBCNTL ||
          prop == PEP_fFONTSIZEMSCNTL ||
          prop == PEP_nFONTSIZEMENU ||
          prop == PEP_fFONTSIZETITLECNTL ||
          prop == PEP_dwGRAPHBACKCOLOR ||
          prop == PEP_szGRAPHBMPFILENAME ||
          prop == PEP_nGRAPHBMPSTYLE ||
          prop == PEP_dwGRAPHFORECOLOR ||
          prop == PEP_dwGRAPHGRADIENTEND ||
          prop == PEP_dwGRAPHGRADIENTSTART ||
          prop == PEP_nGRAPHGRADIENTSTYLE ||
          prop == PEP_nGROUPPERCENTMENU ||
          prop == PEP_nGROUPINGPERCENT ||
          prop == PEP_hHANDCURSOR ||
          prop == PEP_dwHATCHBACKCOLOR ||
          prop == PEP_szHELPFILENAME ||
          prop == PEP_nHELPMENU ||
          prop == PEP_nHIDEINTERSECTINGTEXT ||
          prop == PEP_nIMAGEADJUSTBOTTOM ||
          prop == PEP_nIMAGEADJUSTLEFT ||
          prop == PEP_nIMAGEADJUSTRIGHT ||
          prop == PEP_nIMAGEADJUSTTOP ||
          prop == PEP_nJPGQUALITY ||
          prop == PEP_bLABELBOLD ||
          prop == PEP_szLABELFONT ||
          prop == PEP_bLABELITALIC ||
          prop == PEP_bLABELUNDERLINE ||
          prop == PEP_nLASTMENUINDEX ||
          prop == PEP_nLASTSUBMENUINDEX ||
          prop == PEP_dwaLEGENDANNOTATIONCOLOR ||
          prop == PEP_szaLEGENDANNOTATIONTEXT ||
          prop == PEP_naLEGENDANNOTATIONTYPE ||
          prop == PEP_nLEGENDLOCATION ||
          prop == PEP_nLEGENDLOCATIONMENU ||
          prop == PEP_nLEGENDSTYLE ||
          prop == PEP_szMAINTITLE ||
          prop == PEP_bMAINTITLEBOLD ||
          prop == PEP_szMAINTITLEFONT ||
          prop == PEP_bMAINTITLEITALIC ||
          prop == PEP_bMAINTITLEUNDERLINE ||
          prop == PEP_nMAXDATAPRECISION ||
          prop == PEP_nMAXIMIZEMENU ||
          prop == PEP_hMEMBITMAP ||
          prop == PEP_hMEMDC ||
          prop == PEP_bMODALDIALOGS ||
          prop == PEP_bMODELESSAUTOCLOSE ||
          prop == PEP_bMODELESSONTOP ||
          prop == PEP_dwMONODESKCOLOR ||
          prop == PEP_dwMONOGRAPHBACKCOLOR ||
          prop == PEP_dwMONOGRAPHFORECOLOR ||
          prop == PEP_dwMONOSHADOWCOLOR ||
          prop == PEP_dwMONOTEXTCOLOR ||
          prop == PEP_bMONOWITHSYMBOLS ||
          prop == PEP_szaMULTIBOTTOMTITLES ||
          prop == PEP_szaMULTISUBTITLES ||
          prop == PEP_bNOCUSTOMPARMS ||
          prop == PEP_hNODROPCURSOR ||
          prop == PEP_bNOHELP ||
          prop == PEP_nOBJECTTYPE ||
          prop == PEP_nPAGEHEIGHT ||
          prop == PEP_nPAGEWIDTH ||
          prop == PEP_bPAINTING ||
          prop == PEP_nPERCENTORVALUEMENU ||
          prop == PEP_bPNGISINTERLACED ||
          prop == PEP_bPNGISTRANSPARENT ||
          prop == PEP_dwPNGTRANSPARENTCOLOR ||
          prop == PEP_naPOINTHATCH ||
          prop == PEP_szaPOINTLABELS ||
          prop == PEP_nPOINTS ||
          prop == PEP_bPREPAREIMAGES ||
          prop == PEP_nQUICKSTYLE ||
          prop == PEP_nQUICKSTYLEMENU ||
          prop == PEP_bSEPARATORMENU ||
          prop == PEP_dwSHADOWCOLOR ||
          prop == PEP_bSHOWALLTABLEANNOTATIONS ||
          prop == PEP_bSHOWLEGEND ||
          prop == PEP_nSHOWLEGENDMENU ||
          prop == PEP_nSHOWPIELABELS ||
          prop == PEP_bSHOWPIELEGEND ||
          prop == PEP_bSHOWTABLEANNOTATION ||
          prop == PEP_nSHOWTABLEANNOTATIONSMENU ||
          prop == PEP_bSIMPLELINELEGEND ||
          prop == PEP_bSIMPLEPOINTLEGEND ||
          prop == PEP_nSLICEHATCHING ||
          prop == PEP_nSLICESTARTLOCATION ||
          prop == PEP_szSUBTITLE ||
          prop == PEP_bSUBTITLEBOLD ||
          prop == PEP_szSUBTITLEFONT ||
          prop == PEP_bSUBTITLEITALIC ||
          prop == PEP_bSUBTITLEUNDERLINE ||
          prop == PEP_bSUBSETBYPOINT ||
          prop == PEP_dwaSUBSETCOLORS ||
          prop == PEP_naSUBSETHATCH ||
          prop == PEP_szaSUBSETLABELS ||
          prop == PEP_dwaSUBSETSHADES ||
          prop == PEP_nSUBSETS ||
          prop == PEP_naSUBSETSTOLEGEND ||
          prop == PEP_dwTABACKCOLOR ||
          prop == PEP_dwaTACOLOR ||
          prop == PEP_naTACOLUMNWIDTH ||
          prop == PEP_nTACOLUMNS ||
          prop == PEP_szTAFONT ||
          prop == PEP_szaTAFONTS ||
          prop == PEP_dwTAFORECOLOR ||
          prop == PEP_bTAHEADERCOLUMN ||
          prop == PEP_nTAHEADERORIENTATION ||
          prop == PEP_nTAHEADERROWS ||
          prop == PEP_naTAHOTSPOT ||
          prop == PEP_naTAJUSTIFICATION ||
          prop == PEP_nTALOCATION ||
          prop == PEP_nTAROWS ||
          prop == PEP_szaTATEXT ||
          prop == PEP_nTATEXTSIZE ||
          prop == PEP_naTATYPE ||
          prop == PEP_nTABORDER ||
          prop == PEP_dwTEXTCOLOR ||
          prop == PEP_nTEXTSHADOWS ||
          prop == PEP_nVERTSCROLLPOS ||
          prop == PEP_nVIEWINGSTYLE ||
          prop == PEP_nVIEWINGSTYLEMENU ||
          prop == PEP_nWORKINGTABLE ||
          prop == PEP_faXDATA ||
          prop == PEP_faYDATA);
}

/* Perfunctory check for a few known abort cases.
   TODO: No longer needed with the 6.0.0.46 library. */
static BOOL inappropriate_property_p(HWND hPE, int prop)
{
  switch(PEnget(hPE, PEP_nOBJECTTYPE)) {
   case PECONTROL_3D:
     return zoom_property_p(prop);
   case PECONTROL_PIE:
     return !pie_property_p(prop);
   default:
     return FALSE;
  }
}

static int single_float_property(int prop)
{
  if(single_float_property_p(prop))
    return prop;
  else
    return flip_float_property(prop);
}

static int double_float_property(int prop)
{
  if(single_float_property_p(prop))
    return flip_float_property(prop);
  else
    return prop;
}

// Return correct data property to use for prop, or -1 if there isn't one
static int normalize_chart_property(HWND hPE, int prop)
{
  int type = PEnget(hPE,PEP_nOBJECTTYPE);
  //Gensym-216-HQ-5732321-BF-TWNG aborts when redisplaying pie chart
  int meth;
  //int meth = PEnget(hPE,PEP_nPLOTTINGMETHOD);
  //Gensym-216-HQ-5732321-BF-TWNG aborts when redisplaying pie chart
  BOOL xdata = (prop == PEP_faXDATA   || prop == PEP_faAPPENDXDATA ||
		prop == PEP_faXDATAII || prop == PEP_faAPPENDXDATAII);
  BOOL ydata = (prop == PEP_faYDATA   || prop == PEP_faAPPENDYDATA ||
		prop == PEP_faYDATAII || prop == PEP_faAPPENDYDATAII);
  BOOL zdata = (prop == PEP_faZDATA   || prop == PEP_faAPPENDZDATA ||
		prop == PEP_faZDATAII || prop == PEP_faAPPENDZDATAII);

  if(!(xdata || ydata || zdata))
    return prop;

  switch(type) {
   case PECONTROL_GRAPH:				     // Double precision Y, no X or Z
     if(ydata)
       return double_float_property(prop);
     break;

   case PECONTROL_PIE:					     // Single precision X,Y, no Z
     if(xdata || ydata)					     // ydata is "slices to explode"
       return single_float_property(prop);
     break;

   case PECONTROL_SGRAPH:				     // Double precision X,Y, single Z
     if(xdata || ydata)
		 //Gensym-216-HQ-5732321-BF-TWNG aborts when redisplaying pie chart
	   {
		   meth = PEnget(hPE,PEP_nPLOTTINGMETHOD);
       return IsContourPlottingMethod(meth) ? single_float_property(prop) : double_float_property(prop);
	   }
	   //Gensym-216-HQ-5732321-BF-TWNG aborts when redisplaying pie chart
     if(zdata)						     // zdata is bubble diameter
       return single_float_property(prop);
     break;

   case PECONTROL_PGRAPH:				     // Double precision X,Y, no Z
     if(xdata || ydata)
       return double_float_property(prop);
     break;

   case PECONTROL_3D:					     // Double precision X,Y,Z
     return double_float_property(prop);
  }
  return -1;						     // Invalid property
}

// Get float property as a double, regardless of its precision in the chart.
static BOOL get_float_property(HWND hPE, int prop, int s, int p, double *pVal)
{
  float f;
  double d;

  prop = normalize_chart_property(hPE,prop);
  if(prop < 0)
    return FALSE;

  if(single_float_property_p(prop)) {
    PEvgetcellEx(hPE, prop, s, p, &f);
    d = f;
  }
  else {
    PEvgetcellEx(hPE, prop, s, p, &d);
  }
  *pVal = d;
  return TRUE;
}

// 2D contour charts require single-precision x and y data (z too, but that's
// already taken care of). Setting the flags only works if the user has not
// already added real data.
static void note_plotting_method_change(HWND hPE, int method)
{
  if(IsSciGraph(hPE) && IsContourPlottingMethod(method)) {
    PEnset(hPE, PEP_bUSINGXDATAII, FALSE);
    PEnset(hPE, PEP_bUSINGYDATAII, FALSE);
  }
}

/* Update tick if the prop indicates that chart data was changed. */
static void note_data_property_change(HWND hPE, int prop)
{
  if(data_property_p(prop)) {
    int *pUpdate, *pData;
    g2pvt_pechart_ticks(hPE, &pUpdate, &pData);
    if(pData)
      (*pData)++;
  }
}

/* Perform a partial update: just draw given points into cached bitmap,
 * and blt entire bitmap to screen. */
static void g2pvt_partial_update_chart(HWND hPE, int start, int count)
{
  int s = max(start-1,0);
  int c = count + 1;
  RECT r;

  PEpartialresetimage(hPE, s, c);
  /* TODO: Compute the minimal rectangle to invalidate.
     We can get away with invalidating everything only because the update
     is a simple bitblt at this point. */
  PEvget(hPE, PEP_rectGRAPH, &r);
  InvalidateRect(hPE, &r, FALSE);
}

/* Update the chart, dealing with 3D charts with polygons. */
static void g2pvt_update_chart(HWND hPE)
{
  int type = PEnget(hPE, PEP_nOBJECTTYPE);
  HWND hwnd = GetParent(hPE);	// FIXME: Assuming MDI child
  int *pUpdate, *pData;

  /* If it is a 3D chart with polygons (all but scatter), and some data property
   * has changed since the last update, and it's not the first update, then we
   * must completely recreate the chart to redraw the polygons to reflect the
   * new data. In later library versions, we can simply call
   * PEreconstruct3dpolygons().
   */
  if((type == PECONTROL_3D) && 
     (PEnget(hPE, PEP_nPOLYMODE) != PEPM_SCATTER) &&
     g2pvt_pechart_ticks(hPE, &pUpdate, &pData) &&
     (*pUpdate != *pData)) {

    if(*pUpdate != 0) { /* Don't need to for the very first update.*/
      HGLOBAL hGlobal = 0;
      DWORD dwSize = 0;
      PEstore(hPE, &hGlobal, &dwSize);
      PEreset(hPE);
      PEload(hPE, hGlobal);
      GlobalFree(hGlobal);
    }
    *pUpdate = *pData;
  }

  PEreinitialize(hPE);
  PEresetimage(hPE, 0, 0);
  InvalidateRect(hPE, NULL, TRUE);
  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);
}

static BOOL g2pvt_export_chart(HWND hPE, int width, int height, int format, LPWSTR pathname)
{
  POINT p = {width, height};
  int rc = 0;

  if(pathname && !g2pvt_is_file_writable(pathname)) {
    g2pvt_notify_user("Error: Cannot write to file \"%ls\"\n", pathname);
    return FALSE;
  }

  if(p.x <= 0 || p.y <= 0) {
    RECT r;
    HWND hwnd = GetParent(hPE);
    if(g2pvt_mdi_child_window_p(hwnd) && IsIconic(hwnd)) // FIXME: kludge
      GetClientRectExx(hwnd, &r);
    else
      GetClientRect(hPE, &r);
    p.x = r.right - r.left;
    p.y = r.bottom - r.top;
  }

  switch(format) {
   case CHART_FORMAT_JPEG:
     if(pathname)
       rc = PEcopyjpegtofile(hPE, &p, pathname);
     else
       rc = PEcopyjpegtoclipboard(hPE, &p);
     break;
   case CHART_FORMAT_PNG:
     if(pathname)
       rc = PEcopypngtofile(hPE, &p, pathname);
     else
       rc = PEcopypngtoclipboard(hPE, &p);
     break;
   case CHART_FORMAT_BMP:
     if(pathname)
       rc = PEcopybitmaptofile(hPE, &p, pathname);
     else
       rc = PEcopybitmaptoclipboard(hPE, &p);
     break;
   case CHART_FORMAT_WMF:
     p.x *= WMF_UNITS_PER_PIXEL;
     p.y *= WMF_UNITS_PER_PIXEL;
     if(pathname)
       rc = PEcopymetatofile(hPE, &p, pathname);
     else
       rc = PEcopymetatoclipboard(hPE, &p);
     break;
  }
  
  if(rc == 0) {
    g2pvt_notify_user("Chart export failed: width=%d height=%d format=%d destination=\"%ls\"\n",
		      width, height, format, pathname ? pathname : L"Clipboard");
    return FALSE;
  }
  return TRUE;
}

/* Create chart view of given type within parent. */
HWND g2pvt_create_chart_view(long chart_type, DWORD style, HWND hwndParent)
{
  HWND hPE;
  RECT r;

  if(!ensure_charting_dll())
    return NULL;

  if(chart_type <= 0) chart_type = PECONTROL_GRAPH;

  style |= WS_CHILD;

  GetClientRect(hwndParent, &r);

  hPE = PEcreate(chart_type, style, &r, hwndParent, MAGIC_CHART_ID);
  if(!hPE)
    return NULL;

  // Version 6 allows different rendering engines. Stick to GDI by default, for
  // compatibility with version 5. Except, we seem to need GDI+ for Unicode
  // characters to work.
#ifdef PEP_nRENDERENGINE
  PEnset(hPE, PEP_nRENDERENGINE, PERE_HYBRID);
#endif

  PEnset(hPE, PEP_bPREPAREIMAGES, TRUE); // Using backing store
  PEnset(hPE, PEP_bCACHEBMP, TRUE);      // Use it for refreshes, too.
  PEnset(hPE, PEP_bFIXEDFONTS, TRUE);

  PEszset(hPE, PEP_szMAINTITLE, L"");
  PEszset(hPE, PEP_szSUBTITLE, L"");
  if (chart_type!=PECONTROL_PIE)//bugfix for using pie chart with GigaSoft lib.
    PEszset(hPE, PEP_szLEFTMARGIN, L"xxxxxxxxxxxxxxxxx");
  PEnset(hPE, PEP_bSHOWANNOTATIONS, TRUE);
  
  // Disable the keyboard interface. We'll send all keystrokes to G2.
  PEnset(hPE, PEP_nALLOWUSERINTERFACE, PEAUI_DISABLEKEYBOARD);

  switch(chart_type) {		// Use double floats if chart type permits
   case PECONTROL_3D:
     PEnset(hPE, PEP_bUSINGZDATAII, TRUE);
   case PECONTROL_PGRAPH:
   case PECONTROL_SGRAPH:	// Except when plotting method is contour
     PEnset(hPE, PEP_bUSINGXDATAII, TRUE);
   case PECONTROL_GRAPH:
     PEnset(hPE, PEP_bUSINGYDATAII, TRUE);
     break;
  }

  PEnset(hPE, PEP_nSUBSETS, 1);	        // Default to one curve
  PEnset(hPE, PEP_nPOINTS, 1);		//  with one point
  PEnset(hPE, PEP_nQUICKSTYLE, PEQS_LIGHT_INSET); // Fancier default graphics.
  return hPE;
}

int g2pvt_manage_chart_view(HWND hPE, int opcode, long width, long height, long format, LPWSTR pathname)
{
  HWND hwnd = GetParent(hPE);

  switch(opcode) {
   case CHART_DESTROY:
     PEdestroy(hPE);
     if(g2pvt_mdi_child_window_p(hwnd))
       SendMessage(hwndClient, WM_MDIDESTROY, (WPARAM)hwnd, 0);
     break;

   case CHART_PRINT:
     // TODO: defer in TW and enter modal loop
     PElaunchprintdialog(hPE, TRUE, NULL);
     break;

   case CHART_UPDATE:
     g2pvt_update_chart(hPE);
     break;

   case CHART_PARTIAL_UPDATE:
     g2pvt_partial_update_chart(hPE, width, height);
     break;

   case CHART_EXPORT:		// Export to client-side bitmap file.
     g2pvt_export_chart(hPE, width, height, format, pathname);
     break;

   case CHART_COPY:		// Export to clipboard
     g2pvt_export_chart(hPE, 0, 0, CHART_FORMAT_WMF, NULL);
     break;

   default:
     return -1;
  }
  return CHART_SUCCESS;
}


/*
 * Event Handlers
 */

void g2pvt_pechart_keydown(HWND hPE, int handle)
{
  KEYDOWNDATA kd;
  RECT r;
  int width, height;
  int delta = -20;
  HWND hwnd = g2pvt_parent_window(hPE);

  PEvget(hPE, PEP_structKEYDOWNDATA, &kd);

  /* Maybe let G2 have the keycode and decide what to do. Although, the
   * native editor does zooming locally. */

  if(GetKeyState(VK_CONTROL) < 0 && g2pvt_mdi_child_window_p(hwnd))
    switch(kd.nChar) {
     case VK_OEM_MINUS:
     case VK_ADD:
       delta=20;
     case VK_OEM_PLUS:
     case VK_SUBTRACT:
       GetClientRect(hwndClient, &r);
       width = r.right;
       height = r.bottom;

       GetWindowRect(hwnd, &r);
       ScreenToClient(hwndClient, (LPPOINT)&r.left);
       ScreenToClient(hwndClient, (LPPOINT)&r.right);

       // FIXME: Want to expand rect around current mouse coor.

       r.left = MAX(0, r.left - delta);
       r.top = MAX(0, r.top - delta);
       r.right = MIN(width, r.right + delta);
       r.bottom = MIN(height, r.bottom + delta);
       SetWindowPos(hwnd, NULL, r.left,r.top,r.right-r.left,r.bottom-r.top,
		    SWP_NOZORDER | SWP_NOACTIVATE);
       UpdateWindow(hwnd);
       break;
    }
}

extern HWND hwndMain;

void g2pvt_pechart_click(HWND hPE, int handle)
{
  POINT pt;
  HOTSPOTDATA hsd;
  double x=0, y=0, z=0;
  wchar_t buf[129];
  size_t num = 128;
  RECT r1, r2;
  long dx, dy;
  
  GetWindowRect(hwndMain, &r1);
  GetWindowRect(hPE, &r2);
  dx = r2.top - r1.top;
  dy = r2.left - r1.left;

  PEvget(hPE, PEP_ptLASTMOUSEMOVE, &pt);
  PEgethotspot(hPE, pt.x, pt.y);
  ZeroMemory(&hsd, sizeof(hsd)); // Paranoia.
  PEvget(hPE, PEP_structHOTSPOTDATA, &hsd);

  //Gensym-2077-BF-TAM3-JIRA-46630-Not able to catch event on axis on a GigaSoft Chart view
  /*add allow-axis-shot-spots supports, when it is true, click event will be sent to G2*/
  if (hsd.nHotSpotType == PEHS_DATAPOINT
	  || (PEnget(hPE, PEP_bALLOWAXISHOTSPOTS) == 1 && hsd.nHotSpotType == PEHS_XAXIS)) {
    int s = hsd.w1;
    int p = hsd.w2;

    // Pie charts seem to swap the meanings of hsd.w1 and hsd.w2. Or maybe it
    // is a bug in PE6rc1.
    if(PEnget(hPE,PEP_nOBJECTTYPE) == PECONTROL_PIE) {
      s = hsd.w2;
      p = hsd.w1;
    }

    // TODO: Omit axes which do not apply. This needs a G2 change, too.
    get_float_property(hPE, PEP_faXDATA, s, p, &x);
    get_float_property(hPE, PEP_faYDATA, s, p, &y);
    get_float_property(hPE, PEP_faZDATA, s, p, &z);

    // NOTE: Since this string is parsed by G2, by read-chart-point-from-string,
    // its format cannot be changed.
    ZeroMemory(&buf, sizeof(buf));
    _snwprintf(buf, num, L"x=%lf, y=%lf, z=%lf", x, y, z);

    g2pvt_send_event(hPE,
		     handle,
		     X11_CONTROL,
		     s, p,	        // Subset and point
		     0,
		     CV_EVENT_CLICK,	// Event-code
		     GENSYM_CHART, 0, 
		     buf);

    g2pvt_send_event(hwndMain, -1, X11_CONTROL, pt.x+dx, pt.y+y, 0, 0, 0, 0, NULL);
  }
}

void g2pvt_pechart_cursormove(HWND hPE, int handle)
{
  double x=0, y=0, z=0;
  wchar_t buf[129];
  size_t num = 128;
  int s=0, p=0;

  s = PEnget(hPE, PEP_nCURSORSUBSET);
  p = PEnget(hPE, PEP_nCURSORPOINT);
    
  // Pie charts seem to swap the meanings of hsd.w1 and hsd.w2. Or maybe it
  // is a bug in PE6rc1.
  if(PEnget(hPE,PEP_nOBJECTTYPE) == PECONTROL_PIE) {
	  int swap = s;
	  s = p;
	  p = swap;
  }

  // TODO: Omit axes which do not apply. This needs a G2 change, too.
  get_float_property(hPE, PEP_faXDATA, s, p, &x);
  get_float_property(hPE, PEP_faYDATA, s, p, &y);
  get_float_property(hPE, PEP_faZDATA, s, p, &z);

  // NOTE: Since this string is parsed by G2, by read-chart-point-from-string,
  // its format cannot be changed.
  ZeroMemory(&buf, sizeof(buf));
  _snwprintf(buf, num, L"x=%lf, y=%lf, z=%lf", x, y, z);

  g2pvt_send_event(hPE,
    handle,
    X11_CONTROL,
    s, p,                   // Subset and point
    0,
    CV_EVENT_CURSOR_MOVE,   // Event-code
    GENSYM_CHART, 0, 
    buf);
}

void g2pvt_pechart_menu_choice(HWND hPE, int handle)
{
  g2pvt_send_event(hPE, handle, X11_CONTROL,
		   PEnget(hPE, PEP_nLASTMENUINDEX),
		   PEnget(hPE, PEP_nLASTSUBMENUINDEX),
		   0,
		   CV_EVENT_MENU_CHOICE,
		   GENSYM_CHART, 0, 
		   NULL);
}

// Send info back to G2 plus small, useful set of predefined local behaviors.
void g2pvt_on_chart_notification(HWND hwnd, HWND hPE, int code)
{
  int handle = g2pvt_window_handle(hwnd);

  switch(code) {
   case PEWN_DESTROYED:
     g2pvt_pechart_destroy(hPE);
     break;

   case PEWN_KEYDOWN:
     g2pvt_pechart_keydown(hPE, handle);
     break;

   case PEWN_CLICKED:
     g2pvt_pechart_click(hPE, handle);
     break;
     
   case PEWN_CURSORMOVE:
     g2pvt_pechart_cursormove(hPE, handle);
     break;

   case PEWN_CUSTOMMENU:
     g2pvt_pechart_menu_choice(hPE, handle);
     break;
  }
}


/*
 * Lisp Interface
 */

/* Creates a chart window inside of a MDI child window. Returns the latter. The
   window is NOT shown. */
#ifndef CODEJOCK
long g2ext_create_chart_view(long handle, LPWSTR title, long chart_type, long style16,
			     long left, long top, long width, long height,
			     long dock, long neighbor, LPWSTR lib)
{
  LPG2INFO info;
  HWND hwnd, hPE;
  DWORD style = ((unsigned)style16) << 16;

  hwnd = CreateMDIWindowW((LPWSTR)GensymMDIChildClass, title, style,
			  Def(left), Def(top), Def(width), Def(height),
			  hwndClient, hInst, (LPARAM)handle);
  if(!hwnd) return -1;

  // g2pvt_bless_mdi_child(hwnd, handle); // Offer up our window for MFC's blessing.

  hPE = g2pvt_create_chart_view(chart_type, WS_CHILD | WS_VISIBLE, hwnd);
  if(!hPE) {
    DestroyWindow(hwnd);
    return -1;
  }

  info = g2pvt_make_new_window_info(hwnd, handle);
  info->type = NIP_WINTYPE_MDICHILD;

  g2pvt_activate_window(hwnd);
  return info->window_index;
}

long g2ext_manage_chart_view(long handle, long opcode, long width, long height, long format, LPWSTR pathname)
{
  HWND hwnd = g2pvt_find_window(handle);
  HWND hPE = hwnd ? GetWindow(hwnd,GW_CHILD) : NULL;

  /* This is normal, if a chart is closed while G2 commands are in the queue. */
  if(!hPE)
    return -1;

  return g2pvt_manage_chart_view(hPE, opcode, width, height, format, pathname);
}
#endif

BOOL isNewChartLibProperty(long prop)
{
	return prop >= 10000;
}

long g2ext_chart_set_int(long handle, long prop, long i, long j, long value)
{
  HWND hPE = NULL;
  int rc;

  if (g2_jchart_set_int(handle, prop, i, j, value) || isNewChartLibProperty(prop))
	  return CHART_SUCCESS;

  hPE = g2pvt_find_pechart(handle);

  if(!hPE) 
    return CHART_NO_WINDOW;

  ETRACE("set_int [%d] %4d %d %d %d\n", handle, prop, i, j, value);

  if(inappropriate_property_p(hPE,prop))
    return CHART_INAPPROPRIATE_PROPERTY;

  if(prop == PEP_nPLOTTINGMETHOD)
    note_plotting_method_change(hPE, value);

  note_data_property_change(hPE, prop);

  if(i<0)
    rc = PEnset(hPE, prop, value);
  else if(j<0)
    rc = PEvsetcell(hPE, prop, i, &value);
  else
    rc = PEvsetcellEx(hPE, prop, i, j, &value);

  if(rc == 0)
    return CHART_SET_FAILED;
  /* GENSYMCID-1182: tell gitchart the change of this property. */
  if (prop == PEP_nPOINTS) {
    PEreinitialize(hPE);
    PEresetimage(hPE, 0, 0);
  }

  return CHART_SUCCESS;
}

#define GENSYM_CODE_FOR_LINEBREAK 0x2028
long g2ext_chart_set_string(long handle, long prop, long i, long j, LPWSTR string)
{
  HWND hPE = g2pvt_find_pechart(handle);
  long bIsJChart = g2_jchart_set_string(handle, prop, i, j, string);
  int n, rc;
  LPWSTR p = string;

  if(!hPE)
    return CHART_NO_WINDOW;

  if (bIsJChart)
	  return CHART_SUCCESS;

  ETRACE("set_string [%d] %4d %d %d \"%ls\"\n", handle, prop, i, j, string);

  if(inappropriate_property_p(hPE,prop))
    return CHART_INAPPROPRIATE_PROPERTY;

  note_data_property_change(hPE, prop);

  while (*p) {
    if (*p == GENSYM_CODE_FOR_LINEBREAK) {
      *p = L'\n';
    }
    p++;
  }
  if((n = count_tabs(string)) > 0) {
    if(i<0)
      rc = PEvset(hPE, prop, string, n);
    else
      rc = PEvsetEx(hPE, prop, i, n, string, 0); // Not sure this works.
  }
  else if(i<0)
    rc = PEszset(hPE, prop, string);
  else if(j<0)
    rc = PEvsetcell(hPE, prop, i, string);
  else
    rc = PEvsetcellEx(hPE, prop, i, j, string); // PEP_szaPOINTLABELS only

  if(rc == 0)
    return CHART_SET_FAILED;

  return CHART_SUCCESS;
}

long g2ext_chart_set_double(long handle, long prop, long i, long j, double value)
{
  HWND hPE = g2pvt_find_pechart(handle);
  long bIsJChart = g2_jchart_set_double(handle, prop, i, j, value);
  void *data = &value;
  float single = (float)value;
  int rc;

  if(!hPE)
    return CHART_NO_WINDOW;

  if (bIsJChart)
	  return CHART_SUCCESS;

  if(inappropriate_property_p(hPE,prop))
    return CHART_INAPPROPRIATE_PROPERTY;

  if((prop = normalize_chart_property(hPE,prop)) < 0)
    return CHART_INVALID_FLOAT_PROPERTY;

  ETRACE("set_double [%d] %4d %d,%d = %lf\n", handle, prop, i, j, value);

  note_data_property_change(hPE, prop);

  if(single_float_property_p(prop))
    data = &single;

  if(i<0)
    rc = PEvset(hPE, prop, data, 1);
  else if(j<0)
    rc = PEvsetcell(hPE, prop, i, data);
  else
    rc = PEvsetcellEx(hPE, prop, i, j, data);

  if(rc == 0)
    return CHART_SET_FAILED;

  return CHART_SUCCESS;
}

long g2ext_chart_set_double_array(long handle, long prop, long start, long count, double *array)
{
  HWND hPE = g2pvt_find_pechart(handle);
  long bIsJChart = g2_jchart_set_double_array(handle, prop, start, count, array);
  void *data = array;
  float *arr = NULL;
  long i, rc;

  if(!hPE)
    return CHART_NO_WINDOW;

  if (bIsJChart)
    return CHART_SUCCESS;

  if(inappropriate_property_p(hPE,prop))
    return CHART_INAPPROPRIATE_PROPERTY;

  if((prop = normalize_chart_property(hPE,prop)) < 0)
    return CHART_INVALID_ARRAY_PROPERTY;

  if(count == 0)
    return CHART_SUCCESS;

  if(append_data_property_p(prop)) {
    int ns = PEnget(hPE, PEP_nSUBSETS);
    start = 0;
    count = (ns>0) ? count/ns : 1;
  }

  ETRACE("set_double_array [%d] %4d %d %d\n", handle, prop, start, count);

  note_data_property_change(hPE, prop);

  if(single_float_property_p(prop)) {
    arr = malloc(count * sizeof(float));
    for(i=0; i<count; i++)
      arr[i] = (float) array[i];
    data = arr;
  }

  if(start == 0)
    rc = PEvset(hPE, prop, data, count);
  else
    rc = PEvsetEx(hPE, prop, start, count, data, 0);

  if(arr)
    free(arr);

  if(rc == 0)
    return CHART_SET_FAILED;

  return CHART_SUCCESS;
}

/* GENSYMCID-1225: Chart-view Gigasoft and SetSpringDayLight property */

/* MAX_CHART_STRUCT_SLOTS should be bigger then the max number of slots
   transfered by g2ext_chart_set_struct() and #'%set-chart-property */

#define MAX_CHART_STRUCT_SLOTS 32
static VARIANT cached_chart_struct_buffer[MAX_CHART_STRUCT_SLOTS];
static int cached_chart_struct_buffer_cursor = 0;

static void clear_chart_struct_cached_buffer()
{
  cached_chart_struct_buffer_cursor = 0;
}

void g2ext_chart_add_long_to_struct(long value)
{
  cached_chart_struct_buffer[cached_chart_struct_buffer_cursor++].lVal = value;
}

void g2ext_chart_add_str_to_struct(LPWSTR value)
{
  cached_chart_struct_buffer[cached_chart_struct_buffer_cursor++].puiVal = value;
}

void g2ext_chart_add_double_to_struct(double value)
{
  cached_chart_struct_buffer[cached_chart_struct_buffer_cursor++].dblVal = value;
}

#define CHART_STRUCT_SET_STRING(field) \
  wcstombs(field, (wchar_t*)cached_chart_struct_buffer[i++].puiVal, sizeof(field)/(sizeof(TCHAR)));

long g2ext_chart_set_struct(long handle, long prop)
{
  HWND hPE = NULL;
  int rc;
  void *x = NULL;
  int i = 0, j = 0;
  TM tm = {0};
  CUSTOMGRIDNUMBERS numbers = {0};
  EXTRAAXIS axis = {0};
  GRAPHLOC loc = {0};
  HOTSPOTDATA spot = {0};
  KEYDOWNDATA keydown = {0};
  PolygonData polygon = {0};

  hPE = g2pvt_find_pechart(handle);
  if(!hPE) {
    clear_chart_struct_cached_buffer();
    return CHART_NO_WINDOW;
  }

  ETRACE("set_struct [%d] %4d\n", handle, prop);

  switch (prop) {
  case PEP_structSPRINGDAYLIGHT:
  case PEP_structFALLDAYLIGHT:
    tm.nMonth = cached_chart_struct_buffer[i++].lVal;
    tm.nDay = cached_chart_struct_buffer[i++].lVal;
    tm.nHour = cached_chart_struct_buffer[i++].lVal;
    x = &tm;
    break;
  case PEP_structCUSTOMGRIDNUMBERS:
    numbers.nAxisType = cached_chart_struct_buffer[i++].lVal; 
    numbers.nAxisIndex = cached_chart_struct_buffer[i++].lVal; 
    numbers.dNumber = cached_chart_struct_buffer[i++].dblVal; 
    CHART_STRUCT_SET_STRING(numbers.szData);
    x = &numbers;
    break;
  case PEP_structEXTRAAXISX:
  case PEP_structEXTRAAXISTX:
    axis.nSize = cached_chart_struct_buffer[i++].lVal;
    axis.fMin = (float)cached_chart_struct_buffer[i++].dblVal;
    axis.fMax = (float)cached_chart_struct_buffer[i++].dblVal;
    CHART_STRUCT_SET_STRING(axis.szLabel);
    axis.fManualLine = (float)cached_chart_struct_buffer[i++].dblVal;
    axis.fManualTick = (float)cached_chart_struct_buffer[i++].dblVal;
    CHART_STRUCT_SET_STRING(axis.szFormat);
    axis.nShowAxis = cached_chart_struct_buffer[i++].lVal;
    axis.nShowTickMark = cached_chart_struct_buffer[i++].lVal;
    axis.bInvertedAxis = cached_chart_struct_buffer[i++].lVal;
    axis.bLogScale = cached_chart_struct_buffer[i++].lVal;
    axis.dwColor = cached_chart_struct_buffer[i++].lVal;
    x = &axis;
    break;
  case PEP_structGRAPHLOC:
    loc.nAxis = cached_chart_struct_buffer[i++].lVal;
    loc.fXval = cached_chart_struct_buffer[i++].dblVal;
    loc.fYval = cached_chart_struct_buffer[i++].dblVal;
    x = &loc;
    break;
  case PEP_structHOTSPOTDATA:
    spot.rectHotSpot.left = cached_chart_struct_buffer[i++].lVal;
    spot.rectHotSpot.top = cached_chart_struct_buffer[i++].lVal;
    spot.rectHotSpot.right = cached_chart_struct_buffer[i++].lVal;
    spot.rectHotSpot.bottom = cached_chart_struct_buffer[i++].lVal;
    spot.nHotSpotType = cached_chart_struct_buffer[i++].lVal;
    spot.w1 = cached_chart_struct_buffer[i++].lVal;
    spot.w2 = cached_chart_struct_buffer[i++].lVal;
    x = &spot;
    break;
  case PEP_structKEYDOWNDATA:
    keydown.nChar = cached_chart_struct_buffer[i++].lVal;
    keydown.nRepCnt = cached_chart_struct_buffer[i++].lVal;
    keydown.nFlags = cached_chart_struct_buffer[i++].lVal;
    x = &keydown;
    break;
  case PEP_structPOLYDATA:
    for (j = 0; j < 4; j++) {
      polygon.Vertices[j].X = (float)cached_chart_struct_buffer[i++].dblVal;
      polygon.Vertices[j].Y = (float)cached_chart_struct_buffer[i++].dblVal;
      polygon.Vertices[j].Z = (float)cached_chart_struct_buffer[i++].dblVal;
    }
    polygon.NumberOfVertices = cached_chart_struct_buffer[i++].lVal;
    polygon.PolyColor = cached_chart_struct_buffer[i++].lVal;
    polygon.dwReserved1 = cached_chart_struct_buffer[i++].lVal;
    polygon.dwReserved2 = cached_chart_struct_buffer[i++].lVal;
    x = &polygon;
    break;
  default:
    ETRACE("set_struct unknown prop %4d\n", prop);
    clear_chart_struct_cached_buffer();
    return CHART_SET_FAILED;
  };

  rc = PEvset(hPE,prop,x,1);
  clear_chart_struct_cached_buffer();
  if(rc == 0)
    return CHART_SET_FAILED;
  else
    return CHART_SUCCESS;
}

