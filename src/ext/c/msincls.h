/* -*- Mode: C -*-
 *
 * Module:      MSINCLS.H
 *
 * DESCRIPTION: This file contains the assorted types, defined,
 *              and global references for the PC specific files.
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Pre 8-93: Richard Haggard & Kamal Bijlani
 *
 * mpc 12-10-93: In an effort to bring back the forked PC TW code,
 *     this file was created to encapsulate the contents of numerous
 *     header files which were included by the MS specific files.
 */

#if defined(WIN32)

/*************************************************************************/
/* TYPEDEFS                                                              */
/*************************************************************************/

typedef struct G2Event {
    struct G2Event *next;
    HWND hwnd;
    long window_handle;               /* Assigned by G2. */
    long type;
    long x;
    long y;
    long width;
    long height;
    long key_code;
    long key_bits;
    long time;
    unsigned short *value;            /* Associated wide string or NULL. */
} G2EVENT;


/* TODO: Almost all of this structure is needed only by the main window. */
typedef struct tagG2INFO {
  long type;                          /* NIP_WINTYPE_MDICHILD, etc. */
  HWND hwnd;                          /* The hwnd this represents. */
  long window_index;                  /* g2pointer for this hwnd (a cpointer) */
  long window_handle;                 /* Assigned by G2. */
  long window_icon;		      /* Native icon handle */

  long      nTileBG;                  /* Colors for tiling. */
  long      nTileFG;                  /* */
  HBRUSH    Tilehbr;                  /* Tiling Pattern Brush */
  RECT      rcPaint;                  /* Last paint message coords. */
  struct G2Event *events_head;
  struct G2Event *events_tail;
  long            G2Context;

  long last_event_mouse_x;
  long last_event_mouse_y;
  long last_event_time;
  long last_event_bits;
  long last_event_expose_x;
  long last_event_expose_y;
  long last_event_expose_width;
  long last_event_expose_height;
  long last_event_window_handle;
  unsigned short *last_event_value;   /* Wide string or NULL */

  BOOL mouse_tracking;                /* initialize to false */
  HDC hdc;                            /* previously Ghdc, the Global Handle to Device Context */

  BOOL offscreen;                     /* Offscreen drawing enabled? */
  HBITMAP offscreen_bitmap;
  HBITMAP offscreen_old_hbm;          /* Previous HBM in offscreen_hdc */

  BOOL is_connected;    /* initially false, set true by g2ext_x11_set_window_is_connected */

  /* The following pair of members are x/y mouse cursor positions,
     recorded into by some winproc message handlers, and used by
     some. (These replace previous usage of static variables named
     xPos, yPos, nWidth, and nHeight, respectively, in the G2WndProc
     function.) */
  long winproc_cursor_x;
  long winproc_cursor_y;
  long winproc_width;                 /* Going away soon. */
  long winproc_height;                /* ditto */
  
  long mdi_menu_index;                /* Index of menu bar for this MDI child. */
  long mdi_menu_nms_handle;           /* NMS menu handle for this MDI child.*/

  /* The following state variables are used by the MDI child winproc
     message handlers on the MDI frame window (the child's parent's
     parent). They are global to all of the children. Though they are
     present in each child's window-info structure, these slots never
     to be used in a child's window-info structure. */
  int winproc_update_count;

  POINT max_tracking_size;            /* Used only by MDI child windows. */
  UINT chart_update_tick;	      /* Used only by chart views. */
  UINT chart_data_tick;		      /* Used only by chart views. */
} G2INFO, *LPG2INFO;


typedef struct tagXCOLOR {
  char       *szColor;
  COLORREF    rgbColor;
} XCOLOR, *LPXCOLOR;


/* Bits in flags, below. */
#define G2M_BLACK_LINE    1           /* Draw black line underneath item. */
#define G2M_FOREGROUND    2           /* Draw in custom fg color. */
#define G2M_BACKGROUND    4           /* Draw in custom bg color.. */
#define G2M_ICON          8           /* Draw icon to left of item. */
#define G2M_SEPARATOR    16           /* Draw standard separator bar. */
#define G2M_TEXT         32           /* Draw the string. */
#define G2M_WIDE         64           /* Make wide enough to accomodate an icon
                                       * (even if no icon is present). */

#define G2_MENU_ITEM_MAGIC 0x7AFEBABE

/* An item in a G2 owner-drawn menu item. */
typedef struct tagG2MENUITEM {
  int magic;                          /* Attempt to catch owner-drawn items other than ours. */
  int flags;
  LPCWSTR string;                     /* Owned by LISP. */
  COLORREF fg;
  COLORREF bg;
  int icon;                           /* Index into some ImageList. */
} G2_MENU_ITEM;


#define DLGTEMPLATE_WORKING_SIZE 4096


/*************************************************************************/
/* DEFINES                                                               */
/*************************************************************************/

/* Server extra word defines. */

#define WW_G2_S_INFO       0          /* Server specific information. */
#define WW_G2_S_EXTRA      4


/* temporarily define globals here   */
#define DEFAULT_COLORS     69   /* Number of default colors*/

#define TOTAL_NUMBER_OF_COLORS     72   /* Number of colors including metacolors */

/* used in several places to allocate storage on the stack for filenames */
#define TEMP_FILE_LENGTH 256

/* Win2K or later, which currently equates to Win2K or WinXP. */
#define WIN32_IS_WIN2K   ((GetVersion() & 0x80000000)==0 && (LOBYTE(LOWORD(GetVersion()))) >= 5)
#define WIN32_IS_NT       (GetVersion() < 0x80000000)
#define WIN32_IS_WIN32S  ((GetVersion() & 0x80000000) && \
                          (LOBYTE(LOWORD(GetVersion())) <4))
#define WIN32_IS_WIN95   ((GetVersion() & 0x80000000) && \
                          (LOBYTE(LOWORD(GetVersion())) >=4))

#define G2EVENT_NET_READ      1
#define G2EVENT_NET_WRITE     2
#define G2EVENT_NET_CONNECT   3
#define G2EVENT_NET_ACCEPT    4
#define G2EVENT_NET_CLOSE     5
#define G2EVENT_SCHEDULER     6


/* Netevents message number. WM_USER is 0x0400 = 1024, for use by private window classes. */
#define WSA_NETEVENT     (WM_USER + 1)
#define WSA_NETEVENT_NS   (WM_USER + 16)

/* After quite a bit of research, I'm still not sure how to find out the maximum
 * number of sockets available to us on Windows.  The first part of the answer
 * is, it depends on the Winsock implementation, which apparently can be
 * supplied by different vendors.  I don't know how to find out information
 * about specific Winsock implementations.  Here's a page which disusses the
 * issue in some depth: http://tangentsoft.net/wskfaq/advanced.html
 *
 * I do know that what we did for Winsock 1, use "WSAStartupData.iMaxSockets" is
 * wrong.  I also know that we seem to have some problems with ICP and with
 * licensing and with scaling and probably with other things, which limits our
 * practical use of sockets.  Using the incorrect Winsock 1 method, on my
 * machine, we think we can use 32,767 sockets, which is just ridiculous.
 *
 * At some point, maybe we will get the maximum number of sockets from the
 * Winsock implementation at run time, and then we can use that in our code
 * to make arrays of the exact size we would need.  For now, we will (a) save
 * some space compared to allocating 32,767; (b) have enough space in the event
 * that, on some other machine, using the old method actually gives us a number
 * which is too _low_; and (c) have some reasonable answer to tell Siemens or
 * anyone else who inquires about how many sockets we support.  It's arbitrary,
 * but it's definite: we support 2048.
 *
 * Then, we go about the work of improving G2's ability to actually _use_ more
 * sockets than it can right now.  -jv, 3/01/05
 */
#define G2_MAX_SOCKETS_WIN32 2048

/* Choice from an NMS popup menu.
 *  wParam is the item's ID
 *  lParam is the menu handle, if known, or -1. */
#define WM_NMS_MENU_CHOICE (WM_USER + 2)

/* TODO: Since this is sent between processes, it ought to be a registered
   message instead of a constant (see RegisterWindowMessage) */
#define WM_TELEWINDOWS_SESSION_ID (WM_USER + 3)

/* Notify a child window that its parent has entered size/move. */
#define WM_PARENT_IS_MOVING (WM_USER + 4)

/* Notify G2 (or TW?) that someone wants it to shut down cleanly */
#define WM_SHUT_DOWN_G2 (WM_USER + 5)

/* Reflect WM_COMMAND message from MDI child container to child. */
#define WM_REFLECT_COMMAND (WM_USER + 6)

/* Used with the new G2 task bar icon. */
#define WM_STATUS_AREA_NOTIFY (WM_USER + 7)

/* Notify the child of MDI child container parent is being destroyed. */
#define WM_PARENT_IS_CLOSING (WM_USER + 8)

/* Notify window that a native icon has changed. */
#define WM_ICON_CHANGED (WM_USER + 9)

/* Set icon of window given a G2 native icon handle. */
#define WM_SET_NATIVE_ICON (WM_USER + 10)

/* Window was reparented. */
#define WM_PARENT_CHANGED (WM_USER + 11)

/* Used by TWNG */
#define WM_GETCOMMANDBARS (WM_USER + 12)

/* Used by TWNG */
#define WM_QUERY_CLOSE (WM_USER + 13)

/* Update the edit control info to send to G2 */
#define WM_GENSYM_SEND_INFO_TO_G2 (WM_USER + 14)

/* Used by custom dialogs. */
#define WM_GENSYM_UPDATE_TEXT_BOX (WM_USER + 15)


/* Menu items from taskbar system area popup menu */
#define GWM_EXIT        WM_APP + 1   /* quit G2 */
#define GWM_CONNECT     WM_APP + 2   /* connect Telewindows */



/* These are WM_COMMAND IDs (as opposed to WM_xxx message numbers)
 * for use by the local window, and must be distinct from those use by NMS.
 * Actually, they must be in the range of NMS "stock command" IDs
 * Command IDs are 16 bits.  Windows uses IDs above 0xF000, and MFC uses
 * IDs above 0xE000.  I don't think there are any conventions other than
 * that. */
#define TWPRO_CONNECT                   1001 /* Keep these in sync with commands0.lisp */
#define TWPRO_CLOSEALL                  1002
#define TWPRO_CLOSE                     1003
#define TWPRO_CASCADE                   1005
#define TWPRO_EXIT                      1006
#define TWPRO_TILE                      1007 /* Same as tile-vertically */
#define TWPRO_TILE_VERTICALLY           1008
#define TWPRO_TILE_HORIZONTALLY         1009
#define TWPRO_ABOUT                     1010
#define TWPRO_TEST                      1011 /* Unused */
#define TWPRO_STATUSBAR                 1012
#define TWPRO_OPEN                      1013 /* Unused */
#define TWPRO_SAVE_AS                   1014 /* Unused */
#define TWPRO_TOOLBARS                  1015
#define TWPRO_INSERT_OBJECT             1016 /* NYI */
#define TWPRO_HELP                      1017
#define TWPRO_PRINTWINDOW               1018
#define TWPRO_MINIMIZE_ALL              1019
#define TWPRO_MENU_SMALL            	1020  //HQ-5476610 menu font size options for Twng - Nov 19 2008
#define TWPRO_MENU_MEDIUM             	1021  //HQ-5476610 menu font size options for Twng - Nov 19 2008
#define TWPRO_MENU_LARGE              	1022  //HQ-5476610 menu font size options for Twng - Nov 19 2008
#define TWPRO_MORE_WINDOWS              65279 //Gensym-2041-TAM3-CH-SUCA-JIRA-46986-Add the ability to exclude "more windows" menu choice

/* True for locally executed TW command IDs. No need to consult G2. */
#define g2pvt_local_command_p(id) ((id)>=1001 && (id)<=1050)

#define HELP_FILE_NAME_DEFAULT "..\\doc-chm\\Master.chm"
#define HELP_FILE_NAME_ENVAR "G2_HTML_HELP_FILE"

/* Command IDs for user-defined NMS menu choices range from NMS_NO_CHOICE+1 upwards.
 * Stock commands range from 1001 to 1499, giving us 499 stock commands. */
#define NMS_NO_CHOICE 1500

/* Child ID's for various subwindows. */
#define IDC_TOOLBAR                     140
#define IDC_STATUS                      141
#define IDC_PROGRESS                    142 /* Child of status */

/* A timer we use to get around the modal event loops
 * in menus and dialogs.  We start this timer so that we get WM_TIMER
 * events during the modal loop, and keep ICP messages
 * flowing by called g2_event_cycle in the WM_TIMER handler.
 * -fmw, 3/15/02  */
#define ANTIMODAL_TIMER_ID 1228
#define ANTIMODAL_TIMER_PERIOD 10       /* Milliseconds. 10ms still yields 0% CPU usage. */

#define IDD_FORMVIEW                    101
#define IDC_USER_NAME                   1001
#define IDC_PASSWORD1                   1003
#define IDC_OK                          1006
#define IDC_CANCEL                      1007
#define IDC_HOST                        1008
#define IDC_PORT                        1009
#define IDC_ADDITIONAL                  1010
#define IDC_TEXT                        1011
#ifndef IDC_STATIC
#  define IDC_STATIC                     (-1)
#endif

/* Unique string naming the Windows message TW sends back to the TW ActiveX
   Workspace View Control (if TW was started by one). */
#define SESSIONID_MSG_STRING "Gensym_SessionID"

/* This is a full Unicode font which matches G2's font metrics reasonably closely.
 * Windows file name is arialuni.ttf. Other possibilities: Arial, MS_Mincho */

#define FULL_UNICODE_FONT   "Arial Unicode MS"
#define FULL_UNICODE_FONTW L"Arial Unicode MS"

/* Our own system metrics for pixels/dialog unit, scaled by 100. If Microsoft
 * ever defines metrics at these indices, then G2 simply sees these instead. */
#define SM_CXDIALOG 82
#define SM_CYDIALOG 83

/* Keep x,y coordinates relative to this window's client area. */
#define hwndCoor (Frame_is_embedded ? GetDesktopWindow() : hwndMain)

/*************************************************************************/
/* GLOBAL REFS                                                           */
/*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

extern HDC      Ghdc;                 /* the Global Handle to Device Context */
extern HDC      GhdcMem;              /* the Global Handle to Memory Device Context */
extern HDC      GhdcOffscreen;
extern HBITMAP  GhbmDummy;

extern  HPALETTE     GensymPalette;        /* Handle to the color palette. */
extern  XCOLOR       XColorArray[DEFAULT_COLORS];
extern  int          iNumColors;           /* Number of colors in custom palette */
extern  int          iNumStandardColors;   /* Number of colors before the extended ones. */

extern BOOL logging_to_file;           /* Needed for spawning processes, to know how to handle window creation. */
extern BOOL g2ext_window_destroyed;    /* used by the event loop to determine if the window has been destroyed.  Set by G2WndProc */

extern HFONT MenuFont;                /* Cached font used in Win32 menus. */

extern HWND GhwndWin;                 /* Event window. */
extern HWND parent_GhwndWin;          /* Parent window handle, if embedded. */

extern HWND hwndFrame;                /* Handle to toplevel window */
extern HWND hwndClient;
extern HWND hwndStatus;
extern HWND hwndMain;

extern BOOL Frame_is_MDI;
extern BOOL Frame_is_MFC;
extern BOOL Frame_has_client;
extern BOOL Frame_is_embedded;
extern HANDLE hInst;                  /* Handle to instance's data selector/segment. */

extern BOOL msh_MouseWheelPresent;
extern UINT msh_MouseWheelLines;      /* Number of lines wheel should scroll */
extern BOOL msh_MouseWheelAutoScroll; /* TRUE if wheel automatically sends scroll msgs. */
extern UINT msh_MouseWheelMsg;        /* Alternate mouse wheel message. */

/*************************************************************************/
/* Window Classes                                                        */
/*************************************************************************/

extern LPCWSTR GensymWindowClass;
extern LPCWSTR GensymTelewindowClass;
extern LPCWSTR GensymFrameClass;
extern LPCWSTR GensymWorkspaceViewClass;
extern LPCWSTR GensymMDIChildClass;

/*************************************************************************/
/* Functions                                                             */
/*************************************************************************/
extern void g2pvt_enter_modal_loop(void);
extern void g2pvt_exit_modal_loop(void);

extern LPG2INFO g2pvt_make_new_window_info(HWND hwnd, int handle);
extern LPG2INFO GetlpG2Info(HWND);
extern void g2pvt_free_window_info(HWND hwnd);
extern int g2pvt_window_handle(HWND);
extern void g2pvt_record_window_handle(HWND hwnd, int handle);
extern HWND g2pvt_find_window(int handle);
extern BOOL g2pvt_mdi_child_window_p(HWND hwnd);
extern HWND g2pvt_mdi_child_parent(HWND hwnd);
extern void g2pvt_activate_window(HWND hwnd);
extern HWND g2pvt_parent_window(HWND hwnd);
extern HWND g2pvt_frame_window(HWND hwnd);
extern void g2pvt_reshape_window_within_parent(HWND hwnd, RECT *r);
extern void g2pvt_get_screen_rect(RECT *r);
extern void g2pvt_destroy_window(HWND hwnd);
extern BOOL g2pvt_syscommand_enabled_p(HWND hwnd, UINT nID);
extern BOOL g2pvt_local_command_enabled_p(int nID);

extern void StoreNextEvent (HWND hwnd, long eventtype, long x, long y,
                            long width, long height, long key_code, long key_bits);
extern void StoreNextEventEx (HWND hwnd, long eventtype, long x, long y,
                              long width, long height, long key_code, long key_bits,
                              LPWSTR value);
extern void g2pvt_send_event(HWND hwnd, int handle, int eventtype, 
                             long x, long y, long width, long height, 
                             long key_code, long key_bits, LPWSTR value);

extern void ClientToWindowEx(RECT *r, DWORD style, DWORD exStyle);

extern void set_win_device_palette(HWND);
extern void g2pvt_do_some_event_cycles(void);
extern char *g2pvt_get_last_error_string(void);

extern int g2pvt_on_measure_item(HWND hwnd, int controlID, LPMEASUREITEMSTRUCT lpmis);
extern int g2pvt_on_draw_item(HWND hwnd, int controlID, LPDRAWITEMSTRUCT lpdis);

extern void g2pvt_designate_mdi_client(HWND hwnd);
extern HWND g2pvt_show_mdi_dialog(HWND hwndDlg, int handle);
extern HWND g2pvt_create_mdi_child_dialog(HWND hwndDlg, int handle, BOOL show_p);
extern HWND g2pvt_bless_mdi_child(HWND hwnd, int handle);
extern int g2pvt_show_dialog_in_pane(HWND hwndDlg, int handle,
				     int x, int y, int width, int height,
				     int dock, int neighborID, int icon);

extern void g2pvt_send_control_event(HWND, int, int, int, int, int);
extern void g2pvt_fire_control_event(int type, int handle, int x, int y, int w, int h, LPCWSTR string);

extern void g2pvt_send_window_activated(HWND hwnd, int handle);
extern void g2pvt_send_window_refresh(HWND hwnd, int handle, RECT *r);
extern void g2pvt_send_window_moved(HWND hwnd, int handle, int x, int y);
extern void g2pvt_send_window_sized(HWND hwnd, int handle, UINT type, int cx, int cy);
extern void g2pvt_send_window_vscroll(HWND hwnd, int handle, int code, int pos, int id);
extern void g2pvt_send_window_hscroll(HWND hwnd, int handle, int code, int pos, int id);
extern void g2pvt_send_window_closed(HWND hwnd, int handle);
extern void g2pvt_destroy_native_icons(BOOL);

extern BOOL g2pvt_window_has_info_slot_p(HWND);
extern BOOL g2pvt_embedded_window_p(HWND hwnd);
extern BOOL g2pvt_workspace_view_p(HWND hwnd);
extern BOOL g2pvt_tw_workspace_view_p (HWND hwnd);
extern HWND g2pvt_workspace_view_from_point(HWND hwndPoint, POINT p);

extern void g2pvt_refresh_native_icon(int handle, int where);
extern void g2pvt_set_window_icon(HWND hwnd, int icon);
extern void g2pvt_refresh_dialog_icon(int native_icon);
extern void g2pvt_refresh_mdi_child_icon(int native_icon);

extern long g2ext_html_help(long cmd, char *dir, char *file, char *string, long id, long x, long y, long flags);

#ifdef __cplusplus
}
#endif /* __cplusplus */


/* Keep in sync with xtp/src/CommandBars/XTPCommandBarDefines.h */
#define GENSYM_XTP_ABORT_MENU 666

/*************************************************************************/
/* Win32 definitions not present when compiling for our default WINVER   */
/*************************************************************************/

#ifndef WM_ENTERSIZEMOVE
#define WM_ENTERSIZEMOVE   0x0231
#endif

#ifndef WM_EXITSIZEMOVE
#define WM_EXITSIZEMOVE    0x0232
#endif

/* This message is sent only on Win 98/2K/XP. We define it by hand rather
 * than changing WINVER and getting a bunch of other stuff. */
#ifndef WM_UNINITMENUPOPUP
#define WM_UNINITMENUPOPUP 0x0125
#endif

/* This is an undocumented message which an app receives when the user
 * right clicks on the app's taskbar button. It posts the system menu
 * at the location given in lParam. */
#ifndef WM_UNDOCUMENTED_SYSMENU
#define WM_UNDOCUMENTED_SYSMENU 0x0313
#endif

/* winuser.h for Visual Studio 6.0 seems to be missing some defines. */
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif

#ifndef GET_WHEEL_DELTA_WPARAM
#define GET_WHEEL_DELTA_WPARAM(wparam) ((short)HIWORD (wparam))
#endif

/* Mentioned in MSDN but not in winuser.h. */
#define VK_OEM_PLUS 0xBB
#define VK_OEM_MINUS 0xBD

/* Windows 2000/XP only */
#ifndef SW_SMOOTHSCROLL
#define SW_SMOOTHSCROLL 0x0010
#endif

/* Taken from zmouse.h */
#ifndef MSH_MOUSEWHEEL
#define MSH_MOUSEWHEEL "MSWHEEL_ROLLMSG"
#endif

/* Windows NT 4.0 or higher */
#ifndef SPI_GETWHEELSCROLLLINES
#define SPI_GETWHEELSCROLLLINES 104
#endif

#ifndef SM_MOUSEWHEELPRESENT
#define SM_MOUSEWHEELPRESENT 75
#endif

/* Windows XP or higher */
#ifndef SPI_GETFLATMENU
#define SPI_GETFLATMENU 0x1022
#endif

#endif /* WIN32 */
