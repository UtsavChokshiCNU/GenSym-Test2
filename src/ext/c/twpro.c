/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      twpro.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +   MS Windows portions:
 +              2002 - 2005                fmw, mhd, jv
 +
 + Description:  New TW Pro
 +
 +
 + Key:
 +   (obsolete)
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - Window Management Functions
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
 +   02/27/02,  jv: Created, from code committed by mhd to other files
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

#define OEMRESOURCE

#include <windows.h>
#include "msincls.h"

#include <windowsx.h>          /* WINDOWSX.H extensions */
#include <commctrl.h>
#include <wchar.h>
#include <tchar.h>              /* For _tcsicmp & friends */
#include <assert.h>

#include <shlobj.h>

#include <htmlhelp.h>
#pragma comment(lib, "htmlhelp.lib")

#include "cprim.h"
#include "networks.h"
#include "netevent.h"
#include "graphics.h"
#include "filedlg.h"
#include "ddrsc.h"
#include "messagebox.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* From NT 5.0 includes. */
#ifndef ODS_HOTLIGHT
#define ODS_HOTLIGHT 0x0040
#endif

#ifndef ODS_INACTIVE
#define ODS_INACTIVE        0x0080
#endif

#ifndef ODS_NOACCEL
#define ODS_NOACCEL         0x0100
#endif

#ifndef COLOR_MENUBAR
#define COLOR_MENUBAR 30
#endif

#ifndef DT_HIDEPREFIX
#define DT_HIDEPREFIX               0x00100000
#endif

#define NO_BITMAP ((HBITMAP)(-1))

#define PTRACE G2TRACE

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

BOOL Frame_is_MDI = FALSE;	/* True if hwndFrame is a MDI frame. */
BOOL Frame_is_MFC = FALSE;	/* Frame and client windows provided by MFC. */
BOOL Frame_has_client = FALSE;	/* If true we will get menu bar and status bar. */
BOOL Frame_is_embedded = FALSE; /* If true, our "frame" is not owned by us. */

/* Based on Petzold's recipe for MDI: */
HWND hwndMain = NULL;		/* The G2 event and pane background window. */
HWND hwndFrame = NULL;		/* MDI frame window */
HWND hwndClient = NULL;		/* MDI client window if Frame_is_MDI is true */
HWND hwndStatus = NULL;		/* Optional statusbar */
HWND hwndProgress = NULL;	/* Optional progress bar */
HMENU hMenuBar = NULL;		/* Handle to current menu bar. */
long nms_menu_bar_handle = 0;	/* NMS handle to current menu bar. */
HMENU hViewMenu = NULL;		/* Handle to the View menu in current menu bar. */
HMENU hWindowMenu = NULL;	/* Handle to the Windows menu in current menu bar. */
HMENU hHelpMenu = NULL;		/* Handle to the Help menu in current menu bar. */

HMENU hMenuInit = NULL;		/* Initial (default) menu bar */
HMENU hMenuInitWindow = NULL;
HMENU hMenuInitView = NULL;	/* Handle to the View menu in default menu bar. */
HMENU hMenuInitHelp = NULL;	/* Handle to initial Help menu */

BOOL bViewStatusbar = TRUE;	/* statusbar currently visible */

HCURSOR g_mouseCursor;		/* Overriding mouse cursor. */

static int inside_print_dialog = 0;

extern void SetlpG2Info(HWND hwnd, LPG2INFO info);
extern void g2pvt_update_statusbar_visibility(void);
extern HFONT g2pvt_get_unicode_font(HDC hdc, int pointSize, int angle, int flags);
extern void g2pvt_info_exit(char *, ...);
extern void g2pvt_cancel_all_dynamic_dialogs();
extern long g2ext_write_string_to_console(char * string);
extern HWND g2pvt_find_dialog_hwnd_by_handle(int g2_id);

extern void update_remote_sys_drives(LPCSTR name);

extern DLGTEMPLATE *g2pvt_dialog_template(DLGITEMTEMPLATE **, UINT, int,
          int, int, int, DWORD, DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, int);

/* extern dialog functions */
extern DLGITEMTEMPLATE *g2pvt_create_ltext(DLGITEMTEMPLATE *, LPCWSTR, short, int, int,
			       int, int, DWORD, DWORD);
extern DLGITEMTEMPLATE *g2pvt_create_combobox(DLGITEMTEMPLATE *, short, int, int, int, int,
				  DWORD, DWORD);
extern DLGITEMTEMPLATE *g2pvt_create_autocheckbox(DLGITEMTEMPLATE *, LPCWSTR, short, int, int,
				      int, int, DWORD, DWORD);
extern DLGITEMTEMPLATE *g2pvt_add_control_to_dialog_template(DLGITEMTEMPLATE *item, LPCWSTR text,
							     int id, LPCWSTR classname,
							     DWORD style,
							     int x, int y, int cx, int cy,
							     DWORD exstyle);



/* Forward refs */
static int g2pvt_ensure_status_bar_parts(HWND, int);
void g2pvt_set_statusbar_text(LPCWSTR string);
void g2pvt_layout_status_bar(void);
long g2ext_abort_printing(void);

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

/* Return the Windows error string for the last Win32 error,
 * as a static string. */
char *g2pvt_get_last_error_string(void)
{
  LPVOID last_err_buf;
  static char msg[256];

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &last_err_buf, 0, NULL);
  strncpy(msg,last_err_buf,256);
  msg[255] = '\0';
  LocalFree(last_err_buf);
  return msg;
}

/* make_new_window_info_1 creates a new window info structure (of type LPG2INFO),
using malloc, and initializes slots as needed. However, if malloc fails and
returns NULL, that is the return value. */

static LPG2INFO make_new_window_info_1(HWND hwnd)
{
  LPG2INFO info = (LPG2INFO)malloc(sizeof(G2INFO));

  if(info == NULL)
    return NULL;

  memset(info, 0, sizeof(G2INFO)); /* initialize with all 0's. */
  
  info->hwnd = hwnd;
  info->mouse_tracking = FALSE;
  info->events_head = (G2EVENT *)NULL;
  info->events_tail = (G2EVENT *)NULL;
  info->is_connected = FALSE;
  info->winproc_cursor_x = 0;
  info->winproc_cursor_y = 0;
  info->winproc_width = 0;
  info->winproc_height = 0;
  info->winproc_update_count = 0;
  info->max_tracking_size.x = 0;
  info->max_tracking_size.y = 0;
  info->chart_update_tick = 0;
  info->chart_data_tick = 0;

  info->hdc = GetDC(hwnd);

  /* Create and save the g2pointer for the hwnd, i.e., TW/G2's native window. */
  info->window_index = g2ext_cache_cpointer(hwnd);
  info->window_handle = -1;
  info->window_icon = -1;

  /* Default menu bar indices. */
  info->mdi_menu_index = -1;	/* Default unconnected menu bar. */
  info->mdi_menu_nms_handle = -1;

  PTRACE("make_new_window_info_1: winfo:%x hwnd:%x index:%d hdc:%x\n",
	 info, hwnd, info->window_index, info->hdc);

  return(info);
}


void g2pvt_free_window_info(HWND hwnd)
{
  LPG2INFO info;
  HDC hdc;
  HICON hIcon;

  info = GetlpG2Info(hwnd);
  if(info == NULL) return;

  g2ext_decache_g2pointer(info->window_index);
  hdc = info->hdc;
  free(info);
  SetlpG2Info(hwnd,NULL);

  /* HQ-5647541-TWNG crashed with many warning messages fix */
  hIcon = (HICON)SendMessage(hwnd, WM_SETICON, ICON_SMALL, NULL);
  if(hIcon)
    DestroyIcon(hIcon);

  hIcon = (HICON)SendMessage(hwnd, WM_SETICON, ICON_BIG, NULL);
  if(hIcon)
    DestroyIcon(hIcon);
  /* End of HQ-5647541-TWNG crashed with many warning messages fix */

  /* Delete the Device contexts. */
  /* Select NULL first in order to free all objects */
  SelectObject (hdc, (HPEN) NULL);
  SelectObject (hdc, (HBRUSH) NULL);
  SelectObject (hdc, (HBITMAP) NULL);
  ReleaseDC(hwnd, hdc);
}


LPG2INFO g2pvt_make_new_window_info(HWND hwnd, int handle)
{
  LPG2INFO info = GetlpG2Info(hwnd);

  if(info) {
    if(handle != info->window_handle)
      fprintf(stderr,"Warning: inconsistent handles %d and %d\n", handle, info->window_handle);
  } else {
    info = make_new_window_info_1(hwnd);
    info->window_handle = handle;
    // GetClassName(hwnd, class, sizeof(class)) && !strcmp(class,"#32770");
    SetlpG2Info(hwnd,info);	// Dangerous! Hwnd must have our extra class slots
  }

  return info;
}

/* Record G2 window handle, for windows which either have no INFO slot, or don't
 * need the full LPG2INFO structure. Handle must be >0 to add, <=0 to remove. */
void g2pvt_record_window_handle(HWND hwnd, int handle)
{
  if (!IsWindow(hwnd))
    return;
  else if(handle>0)
    SetProp(hwnd,"G2_HANDLE",(HANDLE)handle);
  else
    RemoveProp(hwnd,"G2_HANDLE");
}

/* Returns the G2-assigned handle for hwnd, or -1 if none found. */
int g2pvt_window_handle(HWND hwnd)
{
  LPG2INFO info;

  if (!IsWindow(hwnd))
    return -1;
  else if((info = GetlpG2Info(hwnd)))
    return info->window_handle;
  else {
    int handle = (int) GetProp(hwnd,"G2_HANDLE");
    return handle>0 ? handle : -1;
  }
}

typedef struct {
  HWND hwnd; 
  int handle;
} WindowAndHandle;

static BOOL CALLBACK cb_find_window(HWND hwnd, LPARAM lParam)
{
  WindowAndHandle *pWh = (WindowAndHandle *)lParam;

  LPG2INFO info = GetlpG2Info(hwnd);
  if(info && info->window_handle == pWh->handle) {
    pWh->hwnd = hwnd;
    return FALSE;
  }
  return TRUE;
}

/* Find HWND with given G2-assigned handle.
 * FIXME: Use a hash table. */
HWND g2pvt_find_window(int handle)
{
  WindowAndHandle wh = {0,0};
  HWND hwnd;

  if(handle<0)
    return NULL;

  /* First try MDI child windows. I don't want to use EnumChildWindows since it
     finds all children, recursively, which if we have a bunch of MDI child
     dialogs, could be a lot of windows. */
  if(hwndClient)
    for(hwnd=GetWindow(hwndClient,GW_CHILD); IsWindow(hwnd); hwnd=GetWindow(hwnd,GW_HWNDNEXT))
      if(g2pvt_window_handle(hwnd) == handle)
	return hwnd;

  /* Now try dialogs */
  hwnd = g2pvt_find_dialog_hwnd_by_handle(handle);
  if(hwnd)
    return hwnd;

  /* Try top-level and owned windows. */
  wh.handle = handle;
  EnumThreadWindows(GetCurrentThreadId(), cb_find_window, (LPARAM) &wh);
  return wh.hwnd;
}

/* Return the parent window of hwnd, not including the owner.  Same as
   GetAncestor(hwnd,GA_PARENT), but does not require NT 4.0 SP4. */
HWND g2pvt_parent_window(HWND hwnd)
{
  HWND parent = GetParent(hwnd);
  HWND owner = GetWindow(hwnd, GW_OWNER);
  if(parent == owner) return NULL;
  else return parent;
}

/* Return the "frame window" for hwnd. The frame window is the closest parent
 * which has, or could have, a title bar, close button, etc. It is either an MDI
 * child window or a top-level window. */
HWND g2pvt_frame_window(HWND hwnd)
{
  HWND parent;

  while(IsWindow(hwnd)) {
    parent = g2pvt_parent_window(hwnd);
    if(parent == NULL || parent == hwndClient)
      return hwnd;
    hwnd = parent;
  }
  return NULL;
}
 
BOOL g2pvt_mdi_child_window_p(HWND hwnd)
{
  return Frame_is_MDI && hwndClient && IsWindow(hwnd) && g2pvt_parent_window(hwnd) == hwndClient;
}

/* Return the MDI child window containing or equal to hwnd, or NULL if none. */
HWND g2pvt_mdi_child_parent(HWND hwnd)
{
  if(!(Frame_is_MDI && hwndClient && IsWindow(hwnd)))
    return NULL;

  while(hwnd) {
    if(g2pvt_parent_window(hwnd) == hwndClient)
      return hwnd;
    hwnd = g2pvt_parent_window(hwnd);
  }
  return NULL;
}

void g2pvt_activate_window(HWND hwnd)
{
  ShowWindow(hwnd, SW_SHOW);
  if(g2pvt_mdi_child_window_p(hwnd)) {
    SendMessage(hwndClient, WM_MDIACTIVATE, (WPARAM)hwnd, 0);
    SendMessage(hwndClient, WM_MDIREFRESHMENU, 0, 0);
    DrawMenuBar(hwndFrame);
  }
}

void g2pvt_reshape_window_within_parent(HWND hwnd, RECT *r)
{
  HWND parent = g2pvt_parent_window(hwnd);
  RECT p;

  if(parent)
    GetClientRect(parent,&p);
  else
    g2pvt_get_screen_rect(&p);

  SetWindowPos(hwnd, 0, 
	       MAX(MIN(r->left,p.right - 50), 5),
	       MAX(MIN(r->top,p.bottom - 50), 5),
	       r->right - r->left,
	       r->bottom - r->top, 0);
}

void g2pvt_get_screen_rect(RECT *pRect)
{
  if(!SystemParametersInfo(SPI_GETWORKAREA, sizeof(RECT), pRect, 0))
    SetRect(pRect, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

void g2pvt_destroy_window(HWND hwnd)
{
  if(g2pvt_mdi_child_window_p(hwnd))
    SendMessage(hwndClient, WM_MDIDESTROY, (WPARAM)hwnd, 0);
  else
    DestroyWindow(hwnd);
}


void g2pvt_inform_user(int flags, char *title, char *format, ...)
{
  va_list ap;
  char msg[512];

  va_start(ap, format);
  _vsnprintf(msg, sizeof(msg), format, ap);
  va_end(ap);

  msg[sizeof(msg)-1] = '\0';

  g2ext_write_string_to_console(msg);

  g2pvt_enter_modal_loop();
  MessageBox(hwndFrame, msg, title, MB_OK | flags);
  g2pvt_exit_modal_loop();
}



/*
 * Native Icons
 */

/* Must match defconstants in telestubs.lisp */
#define TEMP_ICON_FLAG (1<<21)
#define STOCK_ICON_FLAG (1<<20)
#define ICON_OFFSET_MASK (STOCK_ICON_FLAG-1)

#define SAVE_NATIVE_ICON 3
#define DESTROY_NATIVE_ICONS 4
#define STOP_DRAWING_TO_ICON 5
#define REFRESH_NATIVE_ICON 6

extern HBITMAP ImageCluster_ExtractBitmap(int handle);
extern void ImageCluster_ReclaimExtractedBitmap(int handle, HBITMAP hbm);

/* Arbitrary-size, temporary icons. These are created by G2 then transfered out
 * to their final destination and deleted from this list. */
typedef struct _TempIcon {
  struct _TempIcon *next;
  int handle;
  HICON hIcon;
} TempIcon;

static TempIcon *temp_icons = NULL;

static HIMAGELIST imagelist_16 = NULL;
static HIMAGELIST imagelist_32 = NULL;
static int number_of_stock_icons = 0;

static HIMAGELIST *get_image_list_ptr(int size)
{
  switch(size) {
   case 16: return &imagelist_16;
   case 32: return &imagelist_32;
   default:
     fprintf(stderr, "Unsupported icon size: %d\n", size);
     return NULL;
  }
}

/* Returns new bitmap scaled by N, reclaiming the old one. */
static HBITMAP scale_bitmap(HBITMAP hbm, int n)
{
  BITMAP bm;
  HBITMAP hbm2, hOldBM, hOldBM2;
  HDC hdc;
  int w,h;

  GetObject(hbm, sizeof(bm), &bm);
  w = bm.bmWidth;
  h = bm.bmHeight;

  hdc = CreateCompatibleDC(Ghdc);
  hbm2 = CreateCompatibleBitmap(Ghdc, n*w, n*h);

  hOldBM2 = SelectObject(hdc, hbm);
  hOldBM = SelectObject(GhdcMem,hbm2);
  StretchBlt(GhdcMem, 0, 0, n*w, n*h, hdc, 0, 0, w, h, SRCCOPY);
  SelectObject(GhdcMem, hOldBM);
  SelectObject(hdc, hOldBM2);

  DeleteDC(hdc);
  DeleteObject(hbm);
  return hbm2;
}

#ifdef DEBUG_IMAGELISTS
static void draw_imagelist(HIMAGELIST himl, int size)
{
  int i;
  HDC hdc = GetDC(hwndMain);
  for(i=0; i<ImageList_GetImageCount(himl); i++)
    ImageList_Draw(himl, i, hdc, 5+size*i, 5+2*size, ILD_TRANSPARENT);
  ReleaseDC(hwndMain,hdc);
}
#endif

/* Add the stock icons to our imagelists. Count returned. */
static int load_stock_icons(HIMAGELIST himl, int size)
{
  HBITMAP hbm;
  COLORREF crMask = RGB(255,0,255); // Magenta
  int i;
  /* Keep in sync with LISP parameter stock-native-icons !! */
  static char *bitmaps[] = {"toolbar", NULL};     // More files to come...

  // TODO: Someday we'll have nice 32x32 versions of the stock icons. For now,
  // we just scale up the 16x16 ones.

  for(i=0; bitmaps[i]; i++) {
    hbm = LoadBitmap(hInst, bitmaps[i]);
    if(hbm == NULL)
      fprintf(stderr, "Unable to load bitmap resource \"%s\".\n", bitmaps[i]);
    else {
      if(size == 32)
	hbm = scale_bitmap(hbm,2);
      ImageList_AddMasked(himl, hbm, crMask);
      DeleteObject(hbm);
    }
  }
  return ImageList_GetImageCount(himl);
}

/* Return the image number in the imagelist (of any size).*/
int g2pvt_icon_index(int icon)
{
  int offset = icon & ICON_OFFSET_MASK;
  if(icon<0) return -1;
  return (icon & STOCK_ICON_FLAG) ? offset : number_of_stock_icons + offset;
}

HIMAGELIST g2pvt_get_image_list(int size)
{
  HIMAGELIST *pIml = get_image_list_ptr(size);

  if(pIml == NULL) return NULL;

  if(*pIml == NULL)
    *pIml = ImageList_Create(size, size, ILC_COLOR24 | ILC_MASK, 64, 64);

  if(ImageList_GetImageCount(*pIml) == 0)
    number_of_stock_icons = load_stock_icons(*pIml, size);

  return *pIml;
}

/* On KB reset we just want to empty out the image lists, without destroying them,
 * since TWNG may hold references to them. When exiting, we destroy them. */
void g2pvt_destroy_native_icon_imagelists(BOOL destroy)
{
  TempIcon *p, *next;

  for(p=temp_icons; p; p=next) {
    next = p->next;
    DestroyIcon(p->hIcon);
    free(p);
  }
  temp_icons = NULL;

  if(imagelist_16) {
    if(destroy) {
      ImageList_Destroy(imagelist_16);
      imagelist_16 = NULL;
    } else {
      ImageList_RemoveAll(imagelist_16);
      load_stock_icons(imagelist_16, 16);
    }
  }

  if(imagelist_32) {
    if(destroy) {
      ImageList_Destroy(imagelist_32);
      imagelist_32 = NULL;
    } else {
      ImageList_RemoveAll(imagelist_32);
      load_stock_icons(imagelist_32, 32);
    }
  }
}

/* Retrieve and take ownership of an arb size temp icon. */
static HICON get_temp_icon(int handle)
{
  TempIcon *q, *p;
  HICON hIcon;

  for(q=NULL, p=temp_icons; p; q=p, p=p->next)
    if(handle == p->handle) {
      if(q)
	q->next = p->next;
      else
	temp_icons = p->next;
      hIcon = p->hIcon;
      free(p);
      return hIcon;
    }
  return NULL;
}

static int save_temp_icon(int handle, int pixmap_index, int mask_index, int width, int height)
{
  HBITMAP pixmap, mask;
  HIMAGELIST himl;
  HICON hIcon;
  TempIcon *p;

  pixmap = ImageCluster_ExtractBitmap(pixmap_index);
  if(pixmap == NULL)
    return -1;

  mask = ImageCluster_ExtractBitmap(mask_index);
  if(mask == NULL) {
    ImageCluster_ReclaimExtractedBitmap(pixmap_index, pixmap);
    return -1;
  }

  /* Create the icon via an imagelist, which is doing something magical
   * that CreateIconIndirect(&ici) does not. */
  himl = ImageList_Create(width, height, ILC_COLOR24 | ILC_MASK, 1, 1);
  if(!himl)
    return -1;

  ImageList_Add(himl, pixmap, mask);
  hIcon = ImageList_ExtractIcon(0, himl, 0);
  ImageList_Destroy(himl);

  ImageCluster_ReclaimExtractedBitmap(pixmap_index, pixmap);
  ImageCluster_ReclaimExtractedBitmap(mask_index, mask);

  if(!hIcon)
    return -1;

  p = MakeInstance(TempIcon);
  if(p == NULL)
    return -1;

  p->next = temp_icons;		/* NOTE: Pushing onto end would speed up get_temp_icon. */
  temp_icons = p;

  p->handle = handle;
  p->hIcon = hIcon;

  return 1;
}

/* Manages our imagelists. Not all of the arguments are used, depending on the opcode.
 * At the moment, there is only one user-defined image list, but that may change. */
long g2ext_x11_manage_native_icons(long window_index, long opcode,
				   long handle, long width, long height,
				   long pixmap_index, long mask_index)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  LPG2INFO info = GetlpG2Info(hwnd);
  HBITMAP pixmap, mask;
  HIMAGELIST himl;
  int i, n, rc;

  PTRACE("g2ext_x11_manage_native_icons op=%d, handle=%d, %dx%d, p=%d mask=%d\n",
	 opcode, handle, width, height, pixmap_index, mask_index);

  switch(opcode) {
   case SAVE_NATIVE_ICON:	   /* Save scratchpad into user-defined imagelist. */
     if(handle & TEMP_ICON_FLAG)   /* A temp icon */
       return save_temp_icon(handle, pixmap_index, mask_index, width, height);

     if(handle & STOCK_ICON_FLAG) /* Attempted to save a stock icon. */
       return -1;

     pixmap = ImageCluster_ExtractBitmap(pixmap_index);
     if(pixmap == NULL)
       return -1;

     mask = ImageCluster_ExtractBitmap(mask_index);
     if(mask == NULL) {
       ImageCluster_ReclaimExtractedBitmap(pixmap_index, pixmap);
       return -1;
     }

     himl = g2pvt_get_image_list(width);
     if(himl == NULL)
       return -1;

     i = g2pvt_icon_index(handle);

     n = ImageList_GetImageCount(himl);
     PTRACE("  handle=%d, Index=%d, n=%d\n", handle, i, n);
     if(i < n)
       rc = ImageList_Replace(himl, i, pixmap, mask);
     else if(i == n)
       rc = ImageList_Add(himl, pixmap, mask);
     else {
       ImageList_SetImageCount(himl, i+1); // FIXME: Speed killer on Win2K??
       rc = ImageList_Replace(himl, i, pixmap, mask);
     }

     ImageCluster_ReclaimExtractedBitmap(pixmap_index, pixmap);
     ImageCluster_ReclaimExtractedBitmap(mask_index, mask);

     if(rc == 0)
       g2ext_write_string_to_console("Warning: failed to create native icon.");       
     break;

   case DESTROY_NATIVE_ICONS:
     g2pvt_destroy_native_icons(FALSE);
     break;

   case REFRESH_NATIVE_ICON:
     /* handle = icon to refresh, width = bitmask of places it lives */
     g2pvt_refresh_native_icon(handle, width);
     break;

   default:
     return -1;
  }
  return 1;
}

/* This creates a new icon on each call, so it should be cached, since creating
   an icon is relatively slow. Only sizes 16 and 32 are allowed. */
HICON g2pvt_get_native_iconEx(int icon, int size)
{
  HIMAGELIST himl = NULL;
  HICON hIcon = NULL;

  if(icon >= 0)
    himl = g2pvt_get_image_list(size);

  if(himl)
    hIcon = ImageList_ExtractIcon(0, himl, g2pvt_icon_index(icon));
 
  if(hIcon == NULL)
    g2pvt_trace("Warning: no icon found for handle:%08X himl:%08X size %dx%d\n",
		icon, himl, size, size);

  return hIcon;
}

/* Get a persistent icon of default size (16x16), or a temp icon of arbitrary
   size. */
HICON g2pvt_get_native_icon(int icon)
{
  if(icon<0)
    return NULL;
  else if(icon & TEMP_ICON_FLAG)
    return get_temp_icon(icon);
  else
    return g2pvt_get_native_iconEx(icon, 16);
}

void g2pvt_set_window_icon_internal(HWND hwnd, int native_icon)
{
  HICON hIcon = g2pvt_get_native_icon(native_icon);
  HICON hClassIcon = (HICON) GetClassLongPtr(hwnd, GCLP_HICONSM);
  HICON hOldIcon;
  LPG2INFO info;

  /* MDI child windows always have an icon. The best we can do when the user
     requests no icon is to set it to an empty (blank) one. */
 if(hIcon == NULL && g2pvt_mdi_child_window_p(hwnd))
   hIcon = LoadIcon(hInst, "Empty");

  hOldIcon = (HICON) SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

  /* Reclaim the old icon if has been set. */
  /* FIXME: Also need to reclaim when window is destroyed */
  if(hOldIcon && hOldIcon != hClassIcon)
    DestroyIcon(hOldIcon);

  info = GetlpG2Info(hwnd);
  if(info) info->window_icon = native_icon;

  /* If we transitioned between icon and no icon, Windows doesn't automatically
     refresh the title bar for us. */
  if((hIcon != NULL) != (hOldIcon != NULL))
    SetWindowPos(hwnd, NULL, 0,0,0,0, SWP_DRAWFRAME | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}

/* Set window icon given a native_icon id */
void g2pvt_set_window_icon(HWND hwnd, int native_icon)
{
  if(native_icon == -2)		/* Unspecified, leave at default */
    return;

  if(SendMessage(hwnd, WM_SET_NATIVE_ICON, native_icon, 0))
    return;

  g2pvt_set_window_icon_internal(hwnd, native_icon);
}

/* Refresh the window-icon in every MDI child using native-icon. */
void g2pvt_refresh_mdi_child_icon(int native_icon)
{
  HWND hwnd;
  LPG2INFO info;

  if(!hwndClient)
    return;

  for(hwnd=GetWindow(hwndClient,GW_CHILD); IsWindow(hwnd); hwnd=GetWindow(hwnd,GW_HWNDNEXT)) {
    info = GetlpG2Info(hwnd);
    if(info && info->window_icon == native_icon)
      g2pvt_set_window_icon(hwnd, native_icon);
  }
}

long g2ext_native_icons_limit()
{
  OSVERSIONINFO ver;

  ZeroMemory(&ver, sizeof(ver));
  ver.dwOSVersionInfoSize = sizeof(ver);
  GetVersionEx(&ver);

  if((ver.dwMajorVersion == 5 && ver.dwMinorVersion >= 1) || (ver.dwMajorVersion > 5))
    return 131000;		/* Windows XP or higher */
  else
    return 4000;		/* Win2K, NT4 */
}



/* GDI utility functions */

static void reset_dc(HDC hdc)
{
  SetMapMode(hdc, MM_TEXT);
  SetWindowOrgEx(hdc, 0, 0, NULL);
  SetViewportOrgEx(hdc, 0, 0, NULL);
  SelectClipRgn(hdc,NULL);
}

static void fill_rect(HDC hdc, RECT *r, COLORREF color)
{
  HBRUSH hbr, old_brush;

  hbr = CreateSolidBrush(color);
  old_brush = (HBRUSH) SelectObject(hdc,hbr);
  FillRect(hdc, r, hbr);
  SelectObject(hdc,old_brush);
  DeleteObject(hbr);
}

/* Draw line of text, with portion after tab right-justified. */
static void draw_tabbed_text (HDC hdc, RECT *r, LPCWSTR string,
			      COLORREF color, BOOL noaccel)
{
  int n;
  LPCWSTR tab;
  COLORREF old;
  int flags = DT_SINGLELINE | DT_VCENTER | (noaccel ? DT_HIDEPREFIX : 0);

  n = wcslen(string);
  tab = wcschr(string, L'\t');
  if(tab)
    n = tab - string;

  old = SetTextColor(hdc,color);
  DrawTextW(hdc, string, n, r, flags | DT_LEFT);
  if(tab)
    DrawTextW(hdc, tab+1, wcslen(tab+1), r, flags | DT_RIGHT);
  SetTextColor(hdc,old);
}

/* From coolmenu. Draws i-th image from image list in embossed (disabled) fashion. */
static void imagelist_emboss(HIMAGELIST im, int i, HDC hdc, int x, int y)
{
  HBITMAP bm, oldBitmap;
  HBRUSH hbr, oldBrush;
  COLORREF oldBG;
  HDC memdc;
  int cx, cy;
  const DWORD MAGICROP = 0xb8074a; /* ((Dest XOR Pattern) AND Source) XOR Pattern */

  ImageList_GetIconSize(im, &cx, &cy);

  memdc = CreateCompatibleDC(hdc);
  bm = CreateBitmap(cx, cy, 1, 1, NULL);

  /* Draw image transparently into memory DC, with a white background. */
  oldBitmap = SelectObject(memdc, bm);
  PatBlt(memdc, 0, 0, cx, cy, WHITENESS);
  ImageList_Draw(im, i, memdc, 0, 0, ILD_TRANSPARENT);

  /* This seems to be required. Why, I don't know. ??? */
  oldBG = SetBkColor(hdc, RGB(255,255,255));

  /* Draw using hilite offset by (1,1), then shadow */
  hbr = CreateSolidBrush(GetSysColor(COLOR_3DHIGHLIGHT));
  oldBrush = SelectObject(hdc, hbr);
  BitBlt(hdc, x+1, y+1, cx, cy, memdc, 0, 0, MAGICROP);

  hbr = CreateSolidBrush(GetSysColor(COLOR_3DSHADOW));
  DeleteObject(SelectObject(hdc, hbr));
  BitBlt(hdc, x, y, cx, cy, memdc, 0, 0, MAGICROP);

  DeleteObject(SelectObject(hdc, oldBrush));
  SetBkColor(hdc, oldBG);
  SelectObject(memdc, oldBitmap);
  DeleteObject(bm);
  DeleteDC(memdc);
}

/* Instead of being able to just draw a radio button, we have to draw
 * first to a monochrome bitmap and then bitblt that, in order to
 * get transparency. See DrawFrameControl in MSDN. */
static HBITMAP create_radio_button_bitmap(HDC hdc)
{
  HBITMAP hbm, oldHBM;
  HDC memdc;
  int cx = GetSystemMetrics(SM_CXMENUCHECK);
  int cy = GetSystemMetrics(SM_CYMENUCHECK);
  RECT r;

  /* TODO: Cache this? */
  memdc = CreateCompatibleDC(hdc);
  hbm = CreateBitmap(cx, cy, 1, 1, NULL);
  oldHBM = SelectObject(memdc,hbm);
  r.left = 0;
  r.top = 0;
  r.right = cx;
  r.bottom = cy;
  DrawFrameControl(memdc, &r, DFC_MENU, DFCS_MENUBULLET);
  SelectObject(memdc,oldHBM);
  DeleteDC(memdc);

  return hbm;
}

/* Draw monochrome bitmap centered in given rectangle. */
static void draw_centered_bitmap(HDC hdc, RECT *r,
				 COLORREF fg, COLORREF bg, HBITMAP hbm)
{
  BITMAP bm;
  HBITMAP oldHBM;
  COLORREF oldFG, oldBG;
  int x, y, cx, cy;
  HDC memdc;
  RECT rr;

  GetObject(hbm, sizeof(bm), &bm);
  cx = bm.bmWidth;
  cy = bm.bmHeight;

  PTRACE("  draw_checkmark: %dx%d\n", cx, cy);

  /* Center in rect if bitmap is smaller, else clip to rect. */
  rr = *r;
  x = y = 0;
  if(cx < (rr.right - rr.left)) {
    rr.left = (rr.left + rr.right - cx) / 2;
    rr.right = rr.left + cx;
  }
  else {
    x = (cx - rr.right + rr.left)/2;
  }

  if(cy < (rr.bottom - rr.top)) {
    rr.top = (rr.top + rr.bottom - cy) / 2;
    rr.bottom = rr.top + cy;
  }
  else {
    y = (cy - rr.bottom + rr.top)/2;
  }

  memdc = CreateCompatibleDC(hdc);

  oldHBM = (HBITMAP) SelectObject(memdc, hbm);
  oldFG = SetTextColor(hdc,fg);
  oldBG = SetBkColor(hdc,bg);
  BitBlt(hdc, rr.left, rr.top, rr.right-rr.left, rr.bottom-rr.top, memdc, x, y, SRCCOPY);
  SetBkColor(hdc, oldBG);
  SetTextColor(hdc, oldFG);
  SelectObject(memdc, oldHBM);

  DeleteDC(memdc);

  /* TODO: draw pushed-in highlight (to match Office 2000 menus). */
  /*  DrawEdge(hdc, r, BDR_SUNKENOUTER, BF_RECT); */
}




/******************************************************************************
 * Owner-drawn menu items for G2
 *
 * This code duplicates, unfortunately, Microsoft's menu item drawing, while adding
 * the features of a color bitmap beside each item, as well as custom fg and bg
 * colors. A lot of the details for fudge factors and workarounds are derived from
 * the "CoolMenu" MFC example at http://www.microsoft.com/msj/0198/coolmenu.aspx
 * The drawing is designed to replicate the look of Office 2000 menus.
 *
 * -fmw, 6/27/03
 ******************************************************************************/

/* Various fudge factors, from coolmenu */
#define CXLEFT 4		/* Addl left margin for standard menus. */
#define CXRIGHT 6		/* Addl right margin for standard menus. */
#define CXGAP 2			/* num pixels between button and text */
#define CXTEXTMARGIN 2		/* num pixels after hilite to start text */
#define CXBUTTONMARGIN 2	/* num pixels wider button is than bitmap */
#define CYBUTTONMARGIN 2	/* ditto for height */
#define BUTTONSIZE 16
#define CXBUTTON (BUTTONSIZE + 2*CXBUTTONMARGIN)
#define CYBUTTON (BUTTONSIZE + 2*CYBUTTONMARGIN)

/* An item has two possible geometries, depending on the G2M_WIDE bit in
 * the item flags. If not set, then the item gets the Windows standard geometry,
 * so that it will align with non-owner-drawn items. If set, then we make a roomier
 * item, which has space for an icon and is a little taller (matches Office 2000).
 * The wide bit will always be set if the icon bit is. */
void g2pvt_size_custom_menu_item(HDC hdc, G2_MENU_ITEM *item, LONG *cx, LONG *cy)
{
  int cymenu = GetSystemMetrics(SM_CYMENU);
  int check = GetSystemMetrics(SM_CXMENUCHECK);
  int adjust = check - 1;	/* Always added to returned width by Windows. */
  int wide = item->flags & G2M_WIDE;
  int left_margin  = wide ? CXBUTTON + CXGAP : check + CXLEFT;
  int right_margin = wide ? CXBUTTON - 1     : check + CXRIGHT;
  int height       = wide ? cymenu           : cymenu - 2;

  if (item->flags & G2M_SEPARATOR) {  /* Separator. */
    *cx = 0;
    *cy = (cymenu>>1) + (wide ? 1 : 0);

  } else if(item->flags & G2M_TEXT) { /* String and maybe icon. */
    RECT r={0,0,0,0};
    DrawTextW(hdc, item->string, -1, &r, DT_SINGLELINE | DT_CALCRECT);
    *cx = (r.right - r.left) + left_margin + right_margin - adjust;
    *cy = max(height, r.bottom - r.top);

  } else if(item->flags & G2M_ICON) { /* Just an icon. */
    *cx = CXBUTTON + (CXBUTTONMARGIN>>1) - adjust;
    *cy = CYBUTTON;

  } else {			      /* No icon and no string. */
    *cx = 0;
    *cy = height;
  }
}

/* A WinXP thing */
static BOOL flat_menubar_p()
{
  BOOL b = FALSE;
  SystemParametersInfo(SPI_GETFLATMENU, 0, &b, 0);
  return b;
}

void g2pvt_draw_custom_menu_item(HMENU menu, HDC hdc, UINT itemState, UINT itemID,
				 RECT *r, G2_MENU_ITEM *item)
{
  HWND hwnd = WindowFromDC(hdc);
  int is_menubar = hwnd && (GetMenu(hwnd) == menu);
  int selected = itemState & ODS_SELECTED;
  int grayed   = itemState & ODS_GRAYED;
  int checked  = itemState & ODS_CHECKED;
  int hotlight = itemState & ODS_HOTLIGHT;
  /*   int noaccel  = itemState & ODS_NOACCEL; */ /* Doesn't seem to be dependable */
  int noaccel  = 0;
  int has_colors = item->flags & (G2M_FOREGROUND | G2M_BACKGROUND);
  int has_text = item->flags & G2M_TEXT;
  int has_icon = item->flags & G2M_ICON;
  int icon     = item->icon;
  int check = GetSystemMetrics(SM_CXMENUCHECK);
  int wide = item->flags & G2M_WIDE;
  int left_margin  = wide ? CXBUTTON + CXGAP : check + CXLEFT;
  int right_margin = wide ? CXBUTTON - 1     : check + CXRIGHT;
  int height       = r->bottom - r->top;
  int dx,dy,old_mode;
  RECT rr;
  HIMAGELIST himl;
  MENUITEMINFO mii;
  COLORREF fg, bg, t, bgmenu;

  ZeroMemory(&mii,sizeof(MENUITEMINFO));
  mii.cbSize = sizeof(MENUITEMINFO);
  mii.fMask = MIIM_TYPE | MIIM_CHECKMARKS | MIIM_SUBMENU;
  if(!GetMenuItemInfo(menu, itemID, FALSE, &mii))
    fprintf(stderr,"GetMenuItemInfo failed: %s\n", g2pvt_get_last_error_string());

  if(has_icon)			/* Get imagelist, if needed. */
    himl = g2pvt_get_image_list(16);

  if (item->flags & G2M_SEPARATOR) {  /* Draw separator and return. */
    rr = *r;
    rr.top += height/2;
    rr.left++;			    /* Indented a bit. */
    rr.right--;
    DrawEdge(hdc, &rr, EDGE_ETCHED, BF_TOP);
    return;
  }

  /* Everything else. */
  fg = GetSysColor(COLOR_MENUTEXT);
  bg = GetSysColor(COLOR_MENU);

  if(is_menubar && flat_menubar_p() && (GetSysColorBrush(COLOR_MENUBAR) != NULL))
    bgmenu = GetSysColor(COLOR_MENUBAR);
  else
    bgmenu = bg;

  if(item->flags & G2M_FOREGROUND)
    fg = item->fg;
  if(item->flags & G2M_BACKGROUND)
    bg = item->bg;

  if(grayed)
    fg = GetSysColor(COLOR_GRAYTEXT);

  if(selected && !is_menubar) {
    /* Selected menubar items just get popout border. */
    if(has_colors) {
      t = fg;
      fg = bg;
      bg = t;
    } else {
      if(!grayed)
	fg = GetSysColor(COLOR_HIGHLIGHTTEXT);
      bg = GetSysColor(COLOR_HIGHLIGHT);
    }
  }

  PTRACE("draw_item: menu 0x%0x id %d %ls wide %d lm %d rm %d fg %06x bg %06x\n",
	 menu, itemID, item->string ? item->string : L"(none)",
	 wide, left_margin, right_margin, fg, bg);

  /* Draw background. */
  fill_rect(hdc, r, bg);

  /* Draw text. */
  if(has_text) {
    rr = *r;
    rr.left += left_margin;
    rr.right -= right_margin;
    old_mode = SetBkMode(hdc, TRANSPARENT);
    if(grayed && !selected) {
      OffsetRect(&rr,1,1);
      draw_tabbed_text(hdc, &rr, item->string, GetSysColor(COLOR_3DHILIGHT), noaccel);
      OffsetRect(&rr,-1,-1);
    }
    draw_tabbed_text(hdc, &rr, item->string, fg, noaccel);
    SetBkMode(hdc, old_mode);
  }

  /* Draw icon. */
  if(has_icon) {
    rr = *r;
    rr.right = rr.left + left_margin - CXTEXTMARGIN;
    fill_rect(hdc, &rr, bgmenu);      /* Icon background. */

    dx = CXBUTTONMARGIN;
    dy = ((height - CYBUTTON)>>1) + CYBUTTONMARGIN;
    if(himl == NULL)
      g2ext_write_string_to_console("Cannot draw native icon: no imagelist.\n");
    else if(grayed)
      imagelist_emboss(himl, g2pvt_icon_index(icon), hdc, r->left+dx, r->top+dy);
    else
      ImageList_Draw(himl, g2pvt_icon_index(icon), hdc, r->left+dx, r->top+dy, ILD_TRANSPARENT);

    /* Highlight box around icon when selected or hotlit. */
    /* Different on NT and XP. Check for more syscolors we may need to use. */
    if(selected || hotlight) {
      rr.right = rr.left + CXBUTTON;
      DrawEdge(hdc, &rr, is_menubar ? (selected ? BDR_SUNKENOUTER : BDR_RAISEDINNER) :
	       (selected ? BDR_RAISEDINNER : BDR_SUNKENOUTER),
	       BF_RECT);
    }

  } else if (checked || mii.hbmpUnchecked) {    /* Draw checkmark. */
    /* TODO: Draw sunken box around checkmark. */
    HBITMAP hbm = checked ? mii.hbmpChecked : mii.hbmpUnchecked;
    HBITMAP hbmCheck = NULL;
    if(hbm == NULL) {
      if(mii.fType & MFT_RADIOCHECK)
	hbmCheck = create_radio_button_bitmap(hdc);
      else
	hbmCheck = LoadBitmap(NULL, (LPCSTR)OBM_CHECK);
      hbm = hbmCheck;
    }
    rr = *r;
    rr.right = rr.left + left_margin;
    draw_centered_bitmap(hdc, &rr, fg, bg, hbm);
    if (hbmCheck)
      DeleteObject(hbmCheck);
  }

  /* Windows draws the submenu arrow for us. */

  /* Draw underline */
  if(item->flags & G2M_BLACK_LINE) {
    MoveToEx(hdc, r->left, r->bottom-1, NULL);
    LineTo(hdc, r->right, r->bottom-1);
  }
}

/* This is the mostly useless "unconnected" or "built-in" menu bar. You only see
 * it if you connect to a pre-7.0 or a non-responding G2. Someday, it may
 * provide a Connect command, which would make it actually useful. */
HMENU
g2pvt_make_initial_menubar()
{
  HMENU menu_bar = CreateMenu();
  HMENU file_menu = CreatePopupMenu();
  HMENU view_menu = CreatePopupMenu();
  HMENU help_menu = CreatePopupMenu();

  hMenuInit = menu_bar;
  hMenuInitView = view_menu;
  hMenuInitWindow = NULL;
  hMenuInitHelp = help_menu;

  hViewMenu = view_menu;
  hWindowMenu = NULL;
  hHelpMenu = help_menu;

  AppendMenu(menu_bar, MF_POPUP|MF_STRING, (int)file_menu, "&File");
  AppendMenu(menu_bar, MF_POPUP|MF_STRING, (int)view_menu, "&View");
  AppendMenu(menu_bar, MF_POPUP|MF_STRING, (int)help_menu, "&Help");

  AppendMenu(file_menu, MF_STRING, TWPRO_PRINTWINDOW, "&Print Window");
  AppendMenu(file_menu, MF_STRING, TWPRO_EXIT, "E&xit");

  AppendMenu(view_menu, MF_STRING | (bViewStatusbar ? MF_CHECKED:MF_UNCHECKED),
	     TWPRO_STATUSBAR, "&Statusbar");

  AppendMenu(help_menu, MF_STRING, TWPRO_HELP, "Help Topics");
  AppendMenu(help_menu, MF_STRING, TWPRO_ABOUT, "&About Telewindows");

  return menu_bar;
}



/***********************************************************************
 * Common NMS routines
 *
 * Routines common to all native menu backends (Win32, XTP, MFC, etc).
 ***********************************************************************/

HMENU dummyMenuBar = NULL;	/* Global only because msmain references it. */
static LPWSTR fetch_help_string_result = NULL;

/* Called only from C.  Fetch help string for menu item ID.  */
LPWSTR g2pvt_nms_help_string(int id)
{
  extern long nms_fetch_help_string(long,long);
  LPG2INFO info = GetlpG2Info(hwndMain);
  int window_index = (info==NULL) ? 0 : info->window_index;

  fetch_help_string_result = NULL;
  nms_fetch_help_string(window_index, id); /* In Lisp */
  return fetch_help_string_result;
}


/* LISP calls this during nms_fetch_help_string to provide the result.
 * All because I don't know how to return strings from calls to LISP code. */
long g2ext_nms_fetch_help_string_result(LPWSTR string)
{
  fetch_help_string_result = string;
  return 1;
}


int nms_flag = 0;		/* Used to signal reception of nms_enable_items message */

long g2ext_nms_set_flag(long flag)
{
  long old_value = nms_flag;
  nms_flag = flag;

  return old_value;
}



/***********************************************************************
 * Progress Bar Control
 *
 * The Win32 progress bar is pretty lame, but it is standard, and by
 * using it we get appearance updates and theme support on XP.
 *
 * We want to put this into the status bar. Possibly, place in a modal
 * dialog someday.
 ***********************************************************************/

#define PROGRESS_BAR_WIDTH 160	/* Pixels */

#define window_visible_p(hwnd) ((GetWindowLong(hwnd,GWL_STYLE) & WS_VISIBLE) != 0)

HWND g2pvt_create_progress_bar(HWND parent)
{
  HWND hwnd;
  hwnd = CreateWindowExW(0, PROGRESS_CLASSW, (LPWSTR) NULL, 
			 WS_CHILD | WS_CLIPSIBLINGS | PBS_SMOOTH,
			 0, 0, PROGRESS_BAR_WIDTH, 30,
			 parent, (HMENU) IDC_PROGRESS, hInst, NULL); 
  SendMessage(hwnd, PBM_SETPOS, 0, 0);
  return hwnd;
}

static int progress_bar_active_p(void)
{
  return hwndProgress!=NULL && window_visible_p(hwndProgress);
}

static void resize_progress_bar(int left, int height)
{
  int dx, dy, borders[3];

  if(hwndStatus == NULL || hwndProgress == NULL)
    return;

  SendMessage(hwndStatus, SB_GETBORDERS, 0, (LPARAM)borders);
  dy = borders[1];
  dx = borders[2];
  MoveWindow(hwndProgress,
	     left + dx,
	     dy,
	     PROGRESS_BAR_WIDTH - dx,
	     height-dy,
	     TRUE);
}

/* Shows or hides the progress bar and sets its text and doneness. */
#ifndef CODEJOCK
long g2ext_note_progress(LPWSTR message, long doneness)
{
  RECT r;
  int left;

  if(hwndStatus == NULL)
     return -1;

  if(hwndProgress == NULL)
    hwndProgress = g2pvt_create_progress_bar(hwndStatus);
  if(hwndProgress == NULL)
    return -1;

  GetClientRect(hwndFrame, &r);

  if(doneness < 0) {		// TODO: Set a timer to do this.
    if(window_visible_p(hwndProgress)) {
      ShowWindow(hwndProgress, SW_HIDE);
      g2pvt_ensure_status_bar_parts(hwndStatus, r.right);
    }
    g2pvt_set_statusbar_text(message);
  } else {
    if(! window_visible_p(hwndProgress)) {
      ShowWindow(hwndProgress, SW_SHOW);
      left = g2pvt_ensure_status_bar_parts(hwndStatus, r.right);
      GetClientRect(hwndStatus, &r);
      resize_progress_bar(left, r.bottom - r.top);
    }
    g2pvt_set_statusbar_text(message);
    SendMessage(hwndProgress, PBM_SETPOS, (WPARAM)doneness, 0);
  }

  return 1;
}
#endif

/***********************************************************************
 * Indicator Icon
 ***********************************************************************/

/* Another little part in the status bar: an icon with a tooltip. */

static BOOL indicator_icon_p = FALSE;

#ifndef CODEJOCK
BOOL g2pvt_set_indicator_icon(BOOL enable, LPCSTR iconName, LPCSTR tooltip)
{
  int nIndex = 1;
  static HICON hIcon = NULL;

  if(hwndStatus == NULL)
    return -1;

  if(indicator_icon_p != enable) {
    indicator_icon_p = enable;
    g2pvt_layout_status_bar();
  }

  if(indicator_icon_p) {
    if(!hIcon)
      hIcon = LoadImage(hInst, iconName, IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR | LR_SHARED);
    SendMessage(hwndStatus, SB_SETICON, nIndex, (LPARAM)hIcon);
    SendMessage(hwndStatus, SB_SETTEXT, nIndex | SBT_NOBORDERS, (LPARAM)0);
    SendMessage(hwndStatus, SB_SETTIPTEXT, nIndex, (LPARAM)tooltip);
    InvalidateRect(hwndStatus, NULL, TRUE); // Some borders aren't getting redrawn.
  }
  return indicator_icon_p;
}
#endif

/***********************************************************************
 * Status Bar Control
 ***********************************************************************/

/* Create a status window (aka status bar), which is the thin window at the
 * bottom of the frame displaying menu help strings, etc. */
HWND g2pvt_create_status_bar(HWND parent)
{
  HWND hwnd;
  LPCWSTR label = L"";		/* Default status bar text. Was: "Press F1 for help" */

  hwnd = CreateStatusWindowW(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | 
			     SBARS_SIZEGRIP | WS_CLIPSIBLINGS | SBT_TOOLTIPS,
			     label,
			     parent,
			     IDC_STATUS);   /* Child ID. */
  return hwnd;
}

/* Ensure status bar has correct number of parts at the correct
   positions. Returns left edge of progress bar window, if any. */
static int g2pvt_ensure_status_bar_parts(HWND hwnd, int right)
{
  int iconWidth = 22;		/* Magical size which doesn't clip borders. */
  int pbarWidth = PROGRESS_BAR_WIDTH;
  int gripWidth = 18;		/* 18 is width of SBARS_SIZEGRIP.
				   Couldn't find a system metric for it. */
  int i, nRet, nparts, rights[10];

  nRet=0;
  i = 10;

  right -= gripWidth;
  rights[--i] = -1;

  if(progress_bar_active_p()) {
    right -= pbarWidth;
    rights[--i] = right;
    nRet = right;
  }

  if(indicator_icon_p) {
    right -= iconWidth;
    rights[--i] = right;
  }

  nparts = 10-i;
  if(nparts==1)
    SendMessage(hwnd, SB_SIMPLE, TRUE, 0);
  else {
    SendMessage(hwnd, SB_SETPARTS, nparts, (LPARAM) &rights[i]);
    SendMessage(hwnd, SB_SIMPLE, FALSE, 0);
  }
  return nRet;
}

/* Ensure correct parts and positions */
void g2pvt_layout_status_bar()
{
  RECT r;
  int left;

  GetClientRect(hwndFrame, &r);

  left = g2pvt_ensure_status_bar_parts(hwndStatus, r.right);

  if(progress_bar_active_p()) {
    GetClientRect(hwndStatus, &r);
    resize_progress_bar(left, r.bottom - r.top);
  }
}

/* Ensure status bar has correct size and number of parts. */
void g2pvt_resize_status_bar(HWND hwnd, RECT *r)
{
  RECT sr;
  int right, height;

  right = g2pvt_ensure_status_bar_parts(hwnd,r->right);

  GetClientRect(hwnd, &sr);
  height = sr.bottom - sr.top;

  MoveWindow(hwnd, r->left, r->bottom, r->right - r->left, height, TRUE);

  if(progress_bar_active_p())
    resize_progress_bar(right, height);
}

void g2pvt_set_statusbar_text(LPCWSTR string)
{
  if(hwndStatus == NULL || ! IsWindow(hwndStatus))
    return;

  if(SendMessage(hwndStatus, SB_GETPARTS, 0, 0) > 1)
    SendMessageW(hwndStatus, SB_SETTEXTW, 0, (LPARAM) string);
  else
    SendMessageW(hwndStatus, SB_SETTEXTW, 255, (LPARAM) string);
}

#ifndef CODEJOCK
/* Defined differently for TWNG. */
long g2ext_manage_status_bar(long opcode, long pane, LPWSTR string, long number)
{
  if(hwndStatus == NULL || ! IsWindow(hwndStatus))
    return -1;

  switch(opcode) {
   case 0: 
     bViewStatusbar = FALSE;	/* Hide */
     g2pvt_update_statusbar_visibility();
     break;

   case 1:			/* Show */
     bViewStatusbar = TRUE;
     g2pvt_update_statusbar_visibility();
     break;

   case 2:			/* Set text for part 0. */
     g2pvt_set_statusbar_text(string);
     break;
  }
  return 1;
}
#endif

/* Get properties for monitor to the passed rect  */
BOOL GetMonitorRect(LPRECT prc, LPRECT rcWork)
{
    HMONITOR hMonitor;
    MONITORINFO mi;
	BOOL  Result;
    //
    // get the nearest monitor to the passed rect.
    //
    hMonitor = MonitorFromRect(prc, MONITOR_DEFAULTTONEAREST);

    //
    // get the work area monitor rect.
    //
    mi.cbSize = sizeof(mi);
    Result = GetMonitorInfo(hMonitor, &mi);

	rcWork->left	= mi.rcWork.left;
	rcWork->right	= mi.rcWork.right;
	rcWork->top		= mi.rcWork.top;
	rcWork->bottom	= mi.rcWork.bottom;

	return Result;
}


/***********************************************************************
 *
 * Random Windows Utilities
 *
 ***********************************************************************/

/* (1) From Rector and Newcomer's pizza\Utility.c: */

//
//   BOOL g2pvt_center_window (HWND hwndCentered, HWND hwndPreferredOwner)
//
//   PURPOSE: Centers a child window within its parent window. 
//
//   COMMENTS:
//

BOOL g2pvt_center_window (HWND hwndCentered, HWND hwndPreferredOwner)
{
    BOOL  Result;
    POINT OwnerCenter , CenteredUL;
    RECT  WindowRect, OwnerRect, WorkArea;
    SIZE  CenteredWindow;

    assert (NULL != hwndCentered);
    assert (IsWindow (hwndCentered));

    // If a preferred owner isn't specified...
    if (NULL == hwndPreferredOwner)
        // Use the owner of the window to be centered
        hwndPreferredOwner = GetWindowOwner (hwndCentered);

	// Get the rectangle for the workarea
	//Result = SystemParametersInfo (SPI_GETWORKAREA, sizeof (RECT), &WorkArea, 0);
	// For the current monitor
	GetWindowRect (hwndCentered, &WindowRect);
	Result = GetMonitorRect(&WindowRect, &WorkArea);


    // If the above call failed, the new shell probably isn't running
    // therefore there is no tray and no workarea.

    // Use the screen size as the workarea size.
	// Use the virtual screen if we have more than one monitor
    if (!Result) {
        SetRect (&WorkArea,
                 0, 0, 
                 GetSystemMetrics (SM_XVIRTUALSCREEN),
                 GetSystemMetrics (SM_YVIRTUALSCREEN));
    }

    // Center around the owner window, if one,
    // otherwise center in the work area
    if (NULL != hwndPreferredOwner) {
        assert (IsWindow (hwndPreferredOwner));
        GetWindowRect (hwndPreferredOwner, &OwnerRect);
		// For the current monitor
		GetMonitorRect(&OwnerRect, &WorkArea);
    }
    else
        OwnerRect = WorkArea;

    // Preferred center point
    OwnerCenter.x = (OwnerRect.left + OwnerRect.right) / 2;
    OwnerCenter.y = (OwnerRect.top + OwnerRect.bottom) / 2;

    // Get the centered window's rectangle and compute height/width
    GetWindowRect (hwndCentered, &WindowRect);
    CenteredWindow.cx = WindowRect.right - WindowRect.left;
    CenteredWindow.cy = WindowRect.bottom - WindowRect.top;

    // Center window in owner horizontally
    // Calculates the left side coordinate
    CenteredUL.x = OwnerCenter.x - CenteredWindow.cx / 2;

    // Center window in owner vertically
    // Calculates the top side coordinate
    CenteredUL.y = OwnerCenter.y - CenteredWindow.cy / 2;

    // If the left edge of the centered window is clipped by the workarea
    // move the window horizontally to the right until left edge is exposed.
    if (CenteredUL.x < WorkArea.left)
        CenteredUL.x = WorkArea.left;

    // If the right edge of the centered window is clipped by the workarea
    // move the window horizontally to the left until right edge is exposed.
    else if (CenteredUL.x + CenteredWindow.cx > WorkArea.right)
        CenteredUL.x = WorkArea.right - CenteredWindow.cx;
	
    // If the top edge of the centered window is clipped by the workarea
    // move the window vertically down until top edge is exposed.
    if (CenteredUL.y < WorkArea.top)
        CenteredUL.y = WorkArea.top;

    // If the bottom edge of the centered window is clipped by the workarea
    // move the window vertically up until bottom edge is exposed.
    else if (CenteredUL.y + CenteredWindow.cy > WorkArea.bottom)
        CenteredUL.y = WorkArea.bottom - CenteredWindow.cy;

    // Reposition the window centered (within visibility constraints)
    return SetWindowPos (hwndCentered, NULL, 
                         CenteredUL.x, CenteredUL.y,
                         0, 0, SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
}



/* These routines convert from G2's icon indicator (a small integer at the
 * moment) to Win32's various ways of specifying an icon. Keep in sync
 * with lisp dlg-icon-question, etc. */

int g2pvt_get_icon_resource(int icon)
{
  switch(icon)
    {
     case -1: return 0;
     case 0: return (int) IDI_QUESTION;
     case 1: return (int) IDI_INFORMATION;
     case 2: return (int) IDI_WARNING;
     case 3: return (int) IDI_ERROR;
     default:return (int) IDI_QUESTION;
    }
}

UINT g2pvt_get_beep_for_icon(LPCSTR icon)
{
  if(icon == IDI_INFORMATION) return MB_ICONASTERISK;
  if(icon == IDI_WARNING)     return MB_ICONEXCLAMATION;
  if(icon == IDI_ERROR)       return MB_ICONHAND;
  if(icon == IDI_QUESTION)    return MB_ICONQUESTION;
  if(icon == (LPCSTR)0)       return MB_OK;
  return 0;
}

static char *get_icon_string_resource(int icon)
{
  static char buf[20];
  sprintf(buf, "#%d", g2pvt_get_icon_resource(icon));
  return buf;
}

static BOOL dialog_box_p(HWND hwnd)
{
  char c[50];
  return GetClassName(hwnd, c, sizeof(c)) && !strcmp(c, "#32770");
}

static void set_unicode_font(HWND hwnd, int fontSize)
{
  HDC hdc;
  HFONT hfont;

  if(fontSize <= 0)
    fontSize = 14;		/* Default fontsize */

  hdc = GetDC(hwnd);
  hfont = g2pvt_get_unicode_font(hdc,fontSize,0,0);
  if(hfont != NULL) {
    SendMessage(hwnd, WM_SETFONT, (WPARAM)hfont, 0);
    SelectObject(hdc,hfont);
  }
  ReleaseDC(hwnd,hdc);
}

static BOOL CALLBACK cb_cancel_mode(HWND hwnd, LPARAM lParam)
{
  PostMessage(hwnd, WM_CANCELMODE, 0, 0);
  return TRUE;
}

static BOOL CALLBACK cb_end_dialog(HWND hwnd, LPARAM lParam)
{
  /* The print dialog requires a special way to abort it.  See doc for
   * PrintHookProc in MSDN. All other dialogs (that we currently use) can be
   * aborted with EndDialog. */

  if(dialog_box_p(hwnd)) {
    if(inside_print_dialog)
      PostMessage(hwnd, WM_CLOSE, 0, 0);  /* Print dialog */
    else
      EndDialog(hwnd,IDCANCEL);	          /* Other dialogs */
  }
  return TRUE;
}

/* Cancel all modal contexts: menu or dialog. */
long g2ext_cancel_modal_dialogs_and_menus(void)
{
  /* Cancel modal menu traversal. TODO: Codejock menus require something else. */
  SendMessage(hwndFrame, WM_CANCELMODE, 0, 0);
  EnumChildWindows(hwndFrame, cb_cancel_mode, 0);

  /* Cancel dynamic dialogs, both modal and non-modal. */
  g2pvt_cancel_all_dynamic_dialogs();

  /* Cancel top-level modal dialogs owned by us. */
  EnumThreadWindows(GetCurrentThreadId(), cb_end_dialog, 0);

  return 1;
}

// First string is selection, rest are listbox contents.
void g2pvt_populate_combo_box (HWND hwnd, LPCWSTR dnstr)
{
  LPCWSTR s;
  if(IsWindow(hwnd))
    for(s=dnstr; *s; s+=wcslen(s)+1)
      if(s==dnstr)
	SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)s);
      else
	SendMessageW(hwnd, CB_ADDSTRING, 0, (LPARAM)s);
}




/*
 * Built-In Dialogs
 */

#define DLGM_SETTEXT 1		// Types for initialization data
#define DLGM_ADDSTRINGS 2
#define DLGM_SETICON 3
#define DLGM_CHECK 4
#define DLGM_SNDMSG 5

#define DLGT_SHORT 1		// Types for packed result value.
#define DLGT_STRING 2

typedef struct {
  int nControls;
  BOOL resizeable;
  Resizer *resizer;
  USHORT *ids;
  int *flags;
  LPWSTR *data;
  DLGTEMPLATE *templ;
  DLGITEMTEMPLATE *item;
  LPWSTR resultBuf;
  int buflen;
} DialogInfo;

static HWND current_modal_dialog;

static BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

long g2ext_make_dialog(LPWSTR caption, long size, int nControls,
		       long x, long y, long width, long height,
		       long styleHi, long styleLo,
		       long exstyleHi, long exstyleLo, long flags,
		       LPWSTR fontName, long fontSize)
{
  DLGTEMPLATE *templ;
  DLGITEMTEMPLATE *item;
  DialogInfo *pDI;
  BOOL resizeable = (flags&1);
  DWORD style = (styleHi<<16) | styleLo;
  DWORD exstyle = (exstyleHi<<16) | exstyleLo;

  templ = g2pvt_dialog_template(&item, size, x, y, width, height, style, exstyle,
				NULL, NULL, caption, fontName, fontSize);
  if(!templ) return 0;
  pDI = MakeInstance(DialogInfo);
  pDI->nControls = nControls;
  pDI->resizeable = resizeable;
  pDI->ids = (USHORT *)calloc(nControls,sizeof(USHORT));
  pDI->flags = (int *)calloc(nControls,sizeof(int));
  pDI->data = (LPWSTR *)calloc(nControls,sizeof(LPWSTR));
  pDI->templ = templ;
  pDI->item = item;
  return g2ext_cache_cpointer(pDI);
}

long g2ext_add_control(long dlg_index, LPWSTR class, LPWSTR text, long id,
		       long x, long y, long width, long height,
		       long styleHi, long styleLo,
		       long exstyleHi, long exstyleLo,
		       long flags, LPWSTR data)
{
  DialogInfo *pDI = (DialogInfo*) g2ext_map_g2pointer_to_cpointer(dlg_index);
  int i = pDI->templ->cdit;
  DWORD style = (styleHi<<16) | styleLo;
  DWORD exstyle = (exstyleHi<<16) | exstyleLo;

  if(i>=pDI->nControls)
    return -1;

  pDI->ids[i] = (USHORT)id;
  pDI->flags[i] = flags;
  pDI->data[i] = data;

  pDI->templ->cdit++;
  pDI->item = g2pvt_add_control_to_dialog_template(pDI->item, text, id, class,
						   style, x, y, width, height, exstyle);
  return pDI->templ->cdit;
}

long g2ext_post_dialog(long dlg_index, long beep, LPWSTR buf, long buflen)
{
  DialogInfo *pDI;
  int rc;

  if(dlg_index < 0) {		/* Hack: means to cancel current dialog. */
    if(IsWindow(current_modal_dialog))
      EndDialog(current_modal_dialog, IDCANCEL);
    return 0;
  }

  pDI = (DialogInfo*) g2ext_map_g2pointer_to_cpointer(dlg_index);

  ZeroMemory(buf, buflen*sizeof(wchar_t));
  pDI->resultBuf = buf;
  pDI->buflen = buflen;

  if(beep) MessageBeep(beep);

  g2pvt_enter_modal_loop();
  rc = DialogBoxIndirectParamW(hInst, pDI->templ, hwndFrame, DlgProc, (LPARAM)pDI);
  g2pvt_exit_modal_loop();

  free(pDI->ids);
  free(pDI->data);
  free(pDI->templ);
  free(pDI);
  g2ext_decache_g2pointer(dlg_index);
  return rc;
}

static void DlgInit(HWND hwndDlg, DialogInfo *pDI)
{
  int i, id, meth, count, flags;
  LPWSTR strData;
  DWORD *intData;
  HWND hwnd;

  if(pDI->resizeable)
    pDI->resizer = g2pvt_resizer_create(hwndDlg, pDI->nControls);

  for(i=0; i<pDI->nControls; i++) {
    id = pDI->ids[i];
    hwnd = GetDlgItem(hwndDlg,id);
    if(hwnd) {
      flags = pDI->flags[i];
      strData = pDI->data[i];
      meth = *strData++;
      count = *strData++;
      intData = (UINT*)strData;
      switch(meth) {
       case DLGM_SETTEXT:
	 SetWindowTextW(hwnd, strData);
	 break;
       case DLGM_ADDSTRINGS:
	 g2pvt_populate_combo_box(hwnd, strData);
	 break;
       case DLGM_SETICON:
	 SendMessage(hwnd, STM_SETICON, (WPARAM)g2pvt_get_native_icon(intData[0]), 0);
	 break;
       case DLGM_CHECK:
	 SendMessage(hwnd, BM_SETCHECK, (WPARAM)strData[0], 0);
	 break;
       case DLGM_SNDMSG:
	 for(i=0; i<3*count; i+=3)
	   SendMessage(hwnd, intData[i], intData[i+1], intData[i+2]);
	 break;
      }
      if(pDI->resizeable)
	g2pvt_resizer_add(pDI->resizer, id, flags&0xF);
    }
  }
  if(pDI->resizeable)
    g2pvt_resizer_lock(pDI->resizer);
}

static void DlgPackResults(HWND hwndDlg, DialogInfo *pDI)
{
  LPWSTR ptr = pDI->resultBuf;
  int buflen = pDI->buflen;
  LPWSTR end = ptr + buflen - 1;
  int i, meth, flags, len;
  USHORT id;

  for(i=0; i<pDI->nControls && ptr<end; i++) {
    id = pDI->ids[i];
    meth = (pDI->data[i])[0];
    flags = pDI->flags[i];
    if((flags&0x10)==0) {
      *ptr++ = id;
      switch(meth) {
       case DLGM_CHECK:
	 *ptr++ = DLGT_SHORT;	// One word
	 *ptr++ = IsDlgButtonChecked(hwndDlg,id);
	 break;
       default:
	 *ptr++ = DLGT_STRING;	// Counted string
	 len = GetDlgItemTextW(hwndDlg, id, ptr+1, end-ptr-1);
	 *ptr++ = len;
	 ptr += len;
	 break;
      }
    }
  }
  *ptr++ = 0;
}

static BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  DialogInfo *pDI;

  switch (message) {
   case WM_INITDIALOG:
     pDI = (DialogInfo*)lParam;
     SetProp(hwnd,"DlgInfo",(HANDLE)pDI);
     DlgInit(hwnd, pDI);
     current_modal_dialog = hwnd;
     g2pvt_center_window(hwnd, hwndCoor);
     ShowWindow(hwnd,SW_SHOWNORMAL);
     return 1;

   case WM_COMMAND:
     pDI = (DialogInfo *)GetProp(hwnd,"DlgInfo");
     switch (LOWORD(wParam)) {
      case IDOK:
      case IDYES:
      case IDNO:
	DlgPackResults(hwnd, pDI);
      case IDCANCEL:
      case IDABORT:
      case IDCLOSE: 
	EndDialog(hwnd,LOWORD(wParam));
	return TRUE;
     }
     break;

   case WM_DESTROY:
     RemoveProp(hwnd,"DlgInfo");
     current_modal_dialog = NULL;
     break;
  }
  return FALSE;
}



/*
 * List Box Dialog
 */

typedef struct {
  LPCWSTR caption;
  LPCWSTR message;
  LPCWSTR columns;
  LPCWSTR rows;
  LPCSTR icon;
  BOOL checkable;
  PVOID data;
  int data_size;
} InfoForDlg;

static BOOL CALLBACK LBDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/*
 * The "List Box Dialog" is a modal, resizable OK/cancel dialog with an
 * additional multicolumn, readonly list view. It returns 1 for OK and 0 for
 * cancelled. Currently used only for the Load/Save modules confirmation dialog.
 */

//long g2ext_list_box(LPCWSTR caption, LPCWSTR message, LPCWSTR rows, LPCWSTR columns, int icon)
long g2ext_list_box(LPCWSTR caption, LPCWSTR message, LPCWSTR rows, LPCWSTR columns, int icon,
					int checkable, char* state_buffer, int buffer_size)
{
  int rc;
  InfoForDlg info;

  info.caption = caption;
  info.message = message;
  info.rows = rows;
  info.columns = columns;
  info.icon = (LPCSTR) g2pvt_get_icon_resource(icon);
  info.checkable = checkable;
  info.data = state_buffer;
  info.data_size = buffer_size;

  g2pvt_enter_modal_loop();

  //--- commented by Kvazar-Micro
  //rc = DialogBoxParamW(hInst, (LPCWSTR)IDD_MODULES, hwndFrame, LBDlgProc, (LPARAM)&info);
  //-------------------------------------------
  //--- added by Kvazar-Micro
  //--- Client/External Mapping ID:  	 Gensym-46839 
  #ifdef GENFLEX
  hInst  = GetModuleHandle("twdll.dll");
  rc = DialogBoxParamW(hInst, MAKEINTRESOURCE(IDD_MODULES), hwndClient, LBDlgProc, (LPARAM)&info);
  #else
  rc = DialogBoxParamW(hInst, (LPCWSTR)IDD_MODULES, hwndFrame, LBDlgProc, (LPARAM)&info);
  #endif
  //-------------------------------------------
  g2pvt_exit_modal_loop();

  return (rc == IDOK) ? 1 : 0;
}

/* Initially layout dialog to fit the text box. */
static void layout_list_box_dialog(HWND hwnd, LPCWSTR label)
{
  HWND hwndIcon = GetDlgItem(hwnd,IDC_MYICON);
  HWND hwndText = GetDlgItem(hwnd,IDC_LABEL);
  HWND hwndList = GetDlgItem(hwnd,IDC_LIST);
  HWND hwndOK = GetDlgItem(hwnd,IDOK);
  HWND hwndCancel = GetDlgItem(hwnd,IDCANCEL);
  HDC hdc;
  HFONT hFont, hOldFont;
  RECT r;
  int icon_left, icon_top, icon_width, icon_height;
  int text_left, text_top, text_width, text_height;
  int list_left, list_top, list_height;
  int ok_left, ok_top, ok_height, cancel_left, cancel_top;
  int dialog_width, dialog_height;
  int h, w, space = 8;

  GetWindowRect(hwndIcon, &r);                            /* Icon */
  MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);
  icon_left = r.left;
  icon_top = r.top;
  icon_width = r.right - r.left;
  icon_height = r.bottom - r.top;

  GetClientRect(hwndText, &r);				  /* Text */
  r.top = r.left = r.bottom = 0;
  text_width = r.right;
  hFont = (HFONT) SendMessage(hwndText, WM_GETFONT, 0, 0);
  hdc = GetDC(hwndText);
  hOldFont = SelectObject(hdc, hFont);
  DrawTextW(hdc, label, -1, &r, DT_LEFT | DT_EXPANDTABS | DT_WORDBREAK | DT_CALCRECT);
  SelectObject(hdc,hOldFont);
  ReleaseDC(hwnd,hdc);
  /* icon_left is gutter, too. */
  text_left = icon_left + icon_width + icon_left;
  text_top = icon_top;
  text_height = r.bottom;

  GetWindowRect(hwndList, &r);				  /* List */
  MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);
  list_left = r.left;
  list_top = text_top + max(icon_height,text_height) + space;
  list_height = r.bottom - r.top;

  GetWindowRect(hwndOK, &r);				  /* OK */
  MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);
  ok_left = r.left;
  ok_top = list_top + list_height + space;
  ok_height = r.bottom - r.top;

  GetWindowRect(hwndCancel, &r);			  /* Cancel */
  MapWindowPoints(NULL, hwnd, (LPPOINT)&r, 2);
  cancel_left = r.left;
  cancel_top = ok_top;

  GetWindowRect(hwnd, &r);	                          /* Window */
  h = r.bottom - r.top;
  w = r.right - r.left;
  GetClientRect(hwnd, &r);
  h -= r.bottom - r.top;
  w -= r.right - r.left;

  dialog_width = w + text_left + text_width + icon_left;
  dialog_height = h + ok_top + ok_height + icon_top;

  SetWindowPos(hwndText, 0, text_left, text_top, text_width, text_height,
	       SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);

  SetWindowPos(hwndList, 0, list_left, list_top, 0, 0,
	       SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);

  SetWindowPos(hwndOK, 0, ok_left, ok_top, 0, 0,
	       SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);

  SetWindowPos(hwndCancel, 0, cancel_left, cancel_top, 0, 0,
	       SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);

  SetWindowPos(hwnd, 0, 0, 0, dialog_width, dialog_height,
	       SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREDRAW);
}

/* Populate a list-view control from double-NUL-terminated strings of row
 * contents and column labels. */
void g2pvt_populate_list_view (HWND hwndLV, LPCWSTR rows, LPCWSTR columns, BOOL checkable)
{
  int i, sum, width, ncols;
  LV_COLUMNW lvc = {0};
  LV_ITEMW lvi = {0};
  LPCWSTR s;
  RECT r;
  int default_column_width = 75; /* Random */

  GetClientRect(hwndLV,&r);

  /* First count the columns */
  for(ncols=0, s=columns; *s; s+=wcslen(s)+1, ncols++);

  /* Add the columns, making last one fill remaining width. */
  sum=0;
  for(i=0, s=columns; *s; s+=wcslen(s)+1, i++) {
    width = (i==ncols-1) ? (r.right-r.left-sum) : default_column_width;
    lvc.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_FMT|LVCF_SUBITEM;
    lvc.fmt = LVCFMT_LEFT;
    lvc.pszText = (LPWSTR)s;
    lvc.cx = width;
    lvc.iSubItem = i;
    SendMessageW(hwndLV, LVM_INSERTCOLUMNW, i, (LPARAM)&lvc);
    sum += width;
  }

  if (checkable) {
    ListView_SetExtendedListViewStyle(hwndLV, LVS_EX_CHECKBOXES);
  }

  /* Add the rows */
  for(i=0, s=rows; *s; s+=wcslen(s)+1, i++) {
    lvi.mask = LVIF_TEXT;
    lvi.pszText = (LPWSTR)s;
    lvi.iItem = i/ncols;
    lvi.iSubItem = i%ncols;
    if(lvi.iSubItem == 0)
      SendMessageW(hwndLV, LVM_INSERTITEMW, 0, (LPARAM)&lvi);
    else
      SendMessageW(hwndLV, LVM_SETITEMW, 0, (LPARAM)&lvi);

    if (checkable) {
      ListView_SetCheckState(hwndLV, lvi.iItem, TRUE);
    }
   }
}

static void listview_stretch_last_column(HWND hwndList)
{
  ListView_SetColumnWidth(hwndList,
			  Header_GetItemCount(ListView_GetHeader(hwndList)) - 1,
			  LVSCW_AUTOSIZE_USEHEADER);
}

static void listview_get_checked_items(HWND hwndList, char* buff, int size)
{
  int i, list_view_count;

  if (buff == NULL || size == 0)
  {
	  return;
  }

  list_view_count = ListView_GetItemCount(hwndList);
  //list_view_count = size;

  for(i = 0; i < list_view_count && i < size; i++)
  {
	  if (ListView_GetCheckState(hwndList, i))
	  {
		  buff[i] = '1';
	  }
	  else
	  {
		  buff[i] = '0';
	  }
  }

  for(; i < size; i++)
  {
	  buff[i] = '0';
  }
}

static BOOL CALLBACK LBDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  Resizer *resizer = (Resizer *)GetProp(hwnd,"Resizer");
  HWND hwndList = GetDlgItem(hwnd,IDC_LIST);
  HWND hwndText = GetDlgItem(hwnd,IDC_LABEL);
  InfoForDlg *pInfo;
  int rc, beep;

  if(message == WM_SIZE)
    SendMessage(hwndList, WM_SETREDRAW, FALSE, 0);

  if(g2pvt_resizer_dlgproc(resizer, &rc, hwnd, message, wParam, lParam)) {
    if(message == WM_SIZE) {
      listview_stretch_last_column(hwndList);
      InvalidateRect(hwndText, NULL, TRUE); /* Static text seems to need this. */
      SendMessage(hwndList, WM_SETREDRAW, TRUE, 0);
    }
    return rc;
  }

  if(message == WM_SIZE)
    SendMessage(hwndList, WM_SETREDRAW, TRUE, 0);

  switch (message) {
   case WM_INITDIALOG:
     pInfo = (InfoForDlg*)lParam;

     SetWindowTextW(hwnd, pInfo->caption);
     SetDlgItemTextW(hwnd, IDC_LABEL, pInfo->message);
     SendDlgItemMessage(hwnd, IDC_MYICON, STM_SETICON, (WPARAM)LoadIcon(0,pInfo->icon), 0);

     layout_list_box_dialog(hwnd, pInfo->message);

     resizer = g2pvt_resizer_create(hwnd,10);
     g2pvt_resizer_add(resizer, IDC_LABEL,  ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_TOP);
     g2pvt_resizer_add(resizer, IDOK,       ANCHOR_RIGHT|ANCHOR_BOTTOM);
     g2pvt_resizer_add(resizer, IDCANCEL,   ANCHOR_RIGHT|ANCHOR_BOTTOM);
     g2pvt_resizer_add(resizer, IDC_LIST,   ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_TOP|ANCHOR_BOTTOM);
     g2pvt_resizer_lock(resizer);
     SetProp(hwnd,"Resizer",(HANDLE)resizer);

     SendMessage(hwndList, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
     g2pvt_populate_list_view(hwndList, pInfo->rows, pInfo->columns, pInfo->checkable);
     listview_stretch_last_column(hwndList);

     g2pvt_center_window(hwnd, hwndCoor);
	 SetWindowLongPtr(hwnd, GWLP_USERDATA, pInfo);
     ShowWindow(hwnd,SW_SHOW);
     if((beep=g2pvt_get_beep_for_icon(pInfo->icon)))
       MessageBeep(beep);
     return 1;

   case WM_COMMAND:
     switch (LOWORD(wParam)) {
      case IDOK:
		  pInfo = (InfoForDlg*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
		  if (pInfo->checkable && (ListView_GetExtendedListViewStyle(hwndList) & LVS_EX_CHECKBOXES) != 0)
		  {
			  listview_get_checked_items(hwndList, pInfo->data, pInfo->data_size);
		  }
      case IDCANCEL:
		  EndDialog(hwnd,LOWORD(wParam));
		  return TRUE;
     }
     break;

   case WM_DESTROY:
     RemoveProp(hwnd,"Resizer");
     break;
  }
  return FALSE;
}



/********************************************************************************
 *
 * Vanilla window
 *
 * Vanilla is a little buttonless window you can drag around by clicking left
 * anywhere upon it. It is used as the container for notification dialogs, but
 * may have other uses.
 ********************************************************************************/

static LONG WINAPI vanillaWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message) {
   case WM_NCHITTEST:
     return HTCAPTION;
   case WM_ENTERSIZEMOVE:
     g2pvt_enter_modal_loop();
     break;
   case WM_EXITSIZEMOVE:
     g2pvt_exit_modal_loop();
     break;
  }
  return DefWindowProcW(hwnd, message, wParam, lParam);
}

static HWND create_vanilla_window (HWND parent, LPCWSTR caption, UINT style)
{
  WNDCLASSW wc;
  static int done = 0;

  if(!done) {
    done=1;
    wc.lpszClassName 	= L"Vanilla";
    wc.hInstance 	= hInst;
    wc.lpfnWndProc	= vanillaWndProc;
    wc.hCursor		= LoadCursor(NULL,IDC_ARROW);
    wc.hIcon		= LoadIcon(NULL,IDI_APPLICATION);
    wc.lpszMenuName	= NULL;
    wc.hbrBackground	= (HBRUSH) (COLOR_MENU+1);
    wc.style		= CS_OWNDC;
    wc.cbClsExtra	= 0;
    wc.cbWndExtra	= 0;
    if(!RegisterClassW(&wc))
      return NULL;
  }



  return CreateWindowExW(WS_EX_DLGMODALFRAME,
			 L"Vanilla", caption, style,
			 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			 parent, (HMENU)NULL, (HANDLE)hInst, (LPSTR)NULL);
}



/************************************************************
 *
 * Notification Dialog (Non-modal)
 *
 ************************************************************/

static HWND hwndNotification = NULL;

static long g2pvt_destroy_notification(void)
{
  HWND hwndText;
  HFONT hfont;

  if(hwndNotification == NULL)
    return 0;

  hwndText = GetDlgItem(hwndNotification,IDC_LABEL);

  if(hwndText != NULL) {
    hfont = (HFONT) SendMessage(hwndText, WM_GETFONT, 0, 0);
    SendMessage(hwndText, WM_SETFONT, 0, 0);
    if(hfont != NULL)
      DeleteObject(hfont);
  }

  DestroyWindow(hwndNotification);
  hwndNotification = NULL;

  return 1;
}

/* Used for delay and regular notifications. width&height are the size of the
 * icon or animation to the left of the text box. */
static void layout_notification_window(HWND hwnd, LPCWSTR message, int width, int height)
{
  HWND hwndText = GetDlgItem(hwnd,IDC_LABEL);
  HDC hdc;
  int w, h;
  int gutter=5, margin=5;
  RECT r={0,0,1024,1024};

  if(hwndText == NULL) return;

  /* Resize text control to fit message.*/
  hdc = GetDC(hwndText);
  SelectObject(hdc,(HFONT) SendMessage(hwndText, WM_GETFONT, 0, 0));
  DrawTextW(hdc, message, -1, &r, DT_LEFT | DT_NOPREFIX | DT_CALCRECT | DT_WORDBREAK);
  ReleaseDC(hwndText,hdc);

  w = r.right - r.left;
  h = r.bottom - r.top;
  SetWindowPos(hwndText, 0, width+gutter,0, w+margin, MAX(height,h+margin), SWP_NOZORDER);
  SetWindowTextW(hwndText, message);

  /* Resize container to fit icon + text + frame. */
  r.left = 0;
  r.top = 0;
  r.right = width + gutter + w + margin;
  r.bottom = MAX(height,h+margin);
  AdjustWindowRectEx(&r, WS_CAPTION, FALSE, WS_EX_DLGMODALFRAME);

  /* This also activates it and lifts it to the top. */
  SetWindowPos(hwnd, 0, 0,0, r.right-r.left, r.bottom-r.top, SWP_NOMOVE);
}

static long g2pvt_create_notification(LPCWSTR caption, LPCWSTR message,
				      long fontSize, long icon)
{
  HWND parent, hwndIcon, hwndText;

  g2pvt_destroy_notification(); /* Destroy existing, if any. */

  parent = create_vanilla_window(hwndFrame, caption, WS_POPUP | WS_CAPTION);
  hwndIcon = CreateWindowEx(0, "Static", get_icon_string_resource(icon),
			    WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SS_ICON,
			    0, 0, 32, 32,
			    parent, (HMENU)IDC_MYICON, hInst, NULL);

  hwndText = CreateWindowExW(0, L"Static", L"Text",
			     WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SS_LEFT,
			     0, 0, 32, 32,
			     parent, (HMENU)IDC_LABEL, hInst, NULL);

  /* TODO: Probably want a bolder font. */
  set_unicode_font(hwndText, fontSize);
  layout_notification_window(parent, message, 32, 32);

  g2pvt_center_window(parent,hwndCoor);
  ShowWindow(parent, SW_SHOW);
//  ShowWindow(parent, SW_SHOWNA);
  hwndNotification = parent;
  return 1;
}

long g2ext_manage_notification(long opcode, LPCWSTR caption, LPCWSTR message,
			       long fontSize, long icon)
{
  switch(opcode&255)
    {
    case 0:			/* Create */
      g2pvt_create_notification(caption, message, fontSize, icon);
      break;
    case 1:			/* Remove */
      g2pvt_destroy_notification();
      break;
    case 2:			/* Update message */
      if(hwndNotification != NULL)
	layout_notification_window(hwndNotification, message, 32, 32);
      break;
    }
  return 1;
}



/************************************************************
 *
 * Animation Control
 *
 ************************************************************/

static HWND hwndAnimate = NULL;	/* Handle to parent window. */
static int avi_frame_count = 0;
static int avi_width = 0;
static int avi_height = 0;

/* See Windows vfw.h for file format. */
static int get_avi_frame_count(LPCWSTR pathname)
{
  FILE *fd;
  int n;
  unsigned char buf[64];

  fd = _wfopen(pathname,L"rb");
  if(fd == NULL) return 0;
  n = fread(buf, 1, 64, fd);
  fclose(fd);

  if(n==64 && 
     buf[0] == 'R' && buf[1] == 'I' && buf[2]  == 'F' && buf[3]  == 'F' &&
     buf[8] == 'A' && buf[9] == 'V' && buf[10] == 'I' && buf[11] == ' ')
    return (buf[49]<<8) | buf[48];

  return 0;
}

/* Create a native version of the Guide "delay-notification" dialog, which is
 * a little animation plus label. At most one of these is allowed to exist
 * per process. Attempting to create a second without killing the first 
 * merely updates the existing one. */
static long g2pvt_create_animation(LPCWSTR caption, LPCWSTR message,
				   LPCWSTR avi, long fontSize)
{
  HWND parent, anim, text;
  RECT r;

  if(hwndAnimate != NULL)
    return -1;

  if(avi == NULL || *avi == L'\0') {    /* Default animation. */
    avi = L"AVI";			/* Compiled-in resource. */
    avi_frame_count = 8;
  } else {
    avi_frame_count = get_avi_frame_count(avi);
  }

  parent = create_vanilla_window(hwndFrame, caption, WS_POPUP | WS_CAPTION);
  anim = CreateWindowW(ANIMATE_CLASSW, NULL,
		       WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | ACS_TIMER | ACS_TRANSPARENT,
		       0, 0, 0, 0, parent, (HMENU)IDC_ANIMATE, hInst, NULL);

  if(! SendMessageW(anim, ACM_OPENW, 0, (LPARAM) avi)) {
    fprintf(stderr, "Error: Cannot open animation resource/file \"%S\": %s\n",
	    avi, g2pvt_get_last_error_string());
    DestroyWindow(parent);
    return -1;
  }
  GetWindowRect(anim, &r);		/* Get size of the animation. */
  avi_width = r.right - r.left;
  avi_height = r.bottom - r.top;

  text = CreateWindowExW(0, L"Static", message,
			 WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SS_LEFT,
			 0, 0, 32, 32,
			 parent, (HMENU)IDC_LABEL, hInst, NULL);

  set_unicode_font(text, fontSize);
  layout_notification_window(parent, message, avi_width, avi_height);

  /* Place window near upper-left corner of client area of frame. */
  GetClientRect(hwndCoor, &r);
  ClientToScreen(hwndCoor, (POINT*)&r);
  SetWindowPos(parent, 0, r.left+10,r.top+10, 0,0, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);

//  ShowWindow(parent, SW_SHOWNA);
  ShowWindow(parent, SW_SHOW);
  Animate_Play(anim, 0, -1, -1); 
  hwndAnimate = parent;
  return 1;
}

static void g2pvt_destroy_animation(void)
{
  HWND anim=NULL, text=NULL;
  HFONT hfont;

  if(hwndAnimate != NULL) {
    anim = GetDlgItem(hwndAnimate,IDC_ANIMATE);
    text = GetDlgItem(hwndAnimate,IDC_LABEL);
  }

  if(anim != NULL)
    Animate_Close(anim);	/* Needed? */

  if(text != NULL) {
    hfont = (HFONT) SendMessage(text, WM_GETFONT, 0, 0);
    SendMessage(text, WM_SETFONT, 0, 0);
    if(hfont != NULL)
      DeleteObject(hfont);
  }
  if(hwndAnimate != NULL)
    DestroyWindow(hwndAnimate);
  hwndAnimate = NULL;
}

/* Destroy, step, or set label of animation control. */
long g2ext_manage_animation(long opcode, LPCWSTR caption, LPCWSTR message, 
			    long fontSize, LPCWSTR aviFile)
{
  HWND anim=NULL, text=NULL;
  static int frame = 0;

  PTRACE("g2ext_manage_animation(%d, \"%ls\", \"%ls\")\n", opcode, message, aviFile);

  if(hwndAnimate != NULL) {
    anim = GetDlgItem(hwndAnimate,IDC_ANIMATE);
    text = GetDlgItem(hwndAnimate,IDC_LABEL);
  }

  switch(opcode&255)
    {
    case 0:			/* Create or recreate, and start playing. */
      if(hwndAnimate != NULL)
	g2pvt_destroy_animation();
      return g2pvt_create_animation(caption, message, aviFile, fontSize);
      break;

    case 1:			/* Destroy */
      g2pvt_destroy_animation();
      break;

    case 2:			/* Change message */
      if(text != NULL)
	layout_notification_window(hwndAnimate, message, avi_width, avi_height);
      break;

    case 3:			/* Stop */
      if(anim != NULL)
	Animate_Stop(anim);
      break;

    case 4:			/* Start */
      if(anim != NULL)
	Animate_Play(anim, 0, -1, -1);
      break;

    case 5:			/* Seek. */
      frame = (opcode>>8) & 0xFFFF;
      if(anim != NULL)
	Animate_Seek(anim, frame);
      break;

    case 6:			/* Step. */
      if(anim != NULL) {
	Animate_Stop(anim);
	Animate_Seek(anim, frame);
	frame = (frame+1) % avi_frame_count;
      }
      break;

    default:			/* Error */
      return -1;
    }
  return 1;
}



/*
 * TreeView Utilities
 */

static HTREEITEM TreeView_AddChild(HWND hwndTV, HTREEITEM parent, LPWSTR label)
{
  TVINSERTSTRUCTW tvi = {0};
  BOOL hasChildren = TRUE;

  if(label[0] == L'\001') {	// See list-subdirectories-encoded
    label++;
    hasChildren = FALSE;
  }
  tvi.hParent = parent;
  tvi.hInsertAfter = TVI_LAST;
  tvi.item.mask = TVIF_IMAGE | TVIF_CHILDREN | TVIF_TEXT | TVIF_PARAM;
  tvi.item.iImage = 0;		// Closed folder icon (see CreateFolderImageList)
  tvi.item.iSelectedImage = 1;	// Open folder
  tvi.item.cChildren = hasChildren ? 1 : 0;
  tvi.item.pszText = label;
  tvi.item.lParam = 0;		// Not yet expanded
  return (HTREEITEM) SendMessageW(hwndTV, TVM_INSERTITEMW, (WPARAM)0, (LPARAM)&tvi);
}

static LPARAM TreeView_GetItemParam(HWND hwndTV, HTREEITEM hItem)
{
  TVITEM tvi = {0};
  tvi.mask = TVIF_HANDLE | TVIF_PARAM;
  tvi.hItem = hItem;
  TreeView_GetItem(hwndTV, &tvi);
  return tvi.lParam;
}

static void TreeView_SetItemParam(HWND hwndTV, HTREEITEM hItem, LPARAM lParam)
{
  TVITEM tvi = {0};
  tvi.mask = TVIF_HANDLE | TVIF_PARAM;
  tvi.hItem = hItem;
  tvi.lParam = lParam;
  TreeView_SetItem(hwndTV, &tvi);
}

static void TreeView_SetItemCChildren(HWND hwndTV, HTREEITEM hItem, int cChildren)
{
  TVITEM tvi = {0};
  tvi.mask = TVIF_HANDLE | TVIF_CHILDREN;
  tvi.hItem = hItem;
  tvi.cChildren = cChildren;
  TreeView_SetItem(hwndTV, &tvi);
}

/* Find child of parent with given name. */
static HTREEITEM TreeView_FindChild(HWND hwndTV, HTREEITEM parent, LPCWSTR name, BOOL caseSensitive)
{
  HTREEITEM child;
  TVITEMW tvi = {0};
  wchar_t buf[256];

  tvi.mask = TVIF_HANDLE | TVIF_TEXT;
  tvi.pszText = buf;
  tvi.cchTextMax = sizeof(buf)/sizeof(wchar_t);

  for(child=TreeView_GetChild(hwndTV, parent); child; child=TreeView_GetNextSibling(hwndTV, child)) {
    buf[0] = L'\0';
    tvi.hItem = child;
    if(!SendMessageW(hwndTV, TVM_GETITEMW, 0, (LPARAM)&tvi))
      break;
    if(caseSensitive ? (wcscmp(tvi.pszText, name)==0) : (_wcsicmp(tvi.pszText, name) == 0))
      return child;
  }

  return NULL;
}

/* Construct pathname to currently selected item. */
static LPWSTR TreeView_GetPath(HWND hwndTV, HTREEITEM hItem, int skip, 
			       LPWSTR separator, LPWSTR buf, int buflen)
{
  HTREEITEM hItems[256];
  LPWSTR ptr;
  TVITEMW tvi = {0};
  int i;

  i = 0;
  for(; hItem && i<256; hItem=TreeView_GetParent(hwndTV,hItem))
    hItems[i++] = hItem;

  ptr=buf;
  i -= skip;			// Skip first N entries in path.
  while(--i>=0) {
    ZeroMemory(&tvi, sizeof(tvi));
    tvi.mask = TVIF_TEXT;
    tvi.hItem = hItems[i];
    tvi.pszText = ptr;
    tvi.cchTextMax = buflen - (ptr - buf);
    if(SendMessageW(hwndTV, TVM_GETITEMW, 0, (LPARAM)&tvi)) {
      ptr += wcslen(ptr);
      if(i>0) *ptr++ = separator[0];
    }
  }
  *ptr++ = L'\0';
  return buf;
}



/**********************************************************************
 *
 * Native File Dialog
 *
 **********************************************************************/

/* This is defined only for Win2K/XP/98 */
#define OFN_ENABLESIZING 0x00800000

static int checkboxes_count = 0;    /* Number of checkboxes */
static unsigned short checkmarks_bitmask = 0; /* Initial and final value of checkmarks. */
static LPCWSTR combobox_strings  = NULL; /* Contents of combo box and label.*/
static int combobox_choice = -1;
static LPCWSTR default_extension;
static int special_checkbox = -1;
static LPCSTR special_string = NULL;
static LPCWSTR ok_button_label = NULL;
static LPCWSTR cancel_button_label = NULL;

#define IDC_COMBOBOX 666	/* Control ID for combobox */
#define CHECKBOX_ID_ORIGIN 667	/* Control ID for zeroth checkbox */ 


/* Sets the filename of the file dialog to the combobox id's current selected
 * entry, appended with "." and the default_extension. */
static void set_file_dialog_filename_from_combobox(HWND hdlg, int id)
{
  int sel, len;
  wchar_t *buffer;
  HWND hwnd = GetDlgItem(hdlg,id);

  if(hwnd == NULL) return;
  sel = SendMessageW(hwnd, CB_GETCURSEL, 0, 0);
  len = SendMessageW(hwnd, CB_GETLBTEXTLEN, sel, 0);
  buffer = (wchar_t*)malloc((len + wcslen(default_extension)+1 + 1) * sizeof(wchar_t));
  if(buffer == NULL) return;
  SendMessageW(hwnd, CB_GETLBTEXT, sel, (LPARAM)buffer);

  wcscat(buffer, L".");
  wcscat(buffer, default_extension);

  SendMessageW(GetParent(hdlg), CDM_SETCONTROLTEXT, edt1, (LPARAM)buffer);
  free(buffer);
}

/* Enables/disables all of our custom file dialog controls except one with given id. */
static void enable_all_controls_except(HWND hdlg, int id, BOOL enable)
{
  HWND hwnd;
  int i,j;

  hwnd = GetDlgItem(hdlg, IDC_COMBOBOX);  
  if(hwnd != NULL) EnableWindow(hwnd,enable);
  for(i=0; i<checkboxes_count; i++) {
    j = i + CHECKBOX_ID_ORIGIN;
    if(j != id && (hwnd = GetDlgItem(hdlg, j)))
      EnableWindow(hwnd,enable);
  }
}

/* This is an OFNHookProc (see MSDN). */
static UINT CALLBACK checkboxes_file_dialog_hook(HWND hdlg, UINT message,
						 WPARAM wParam, LPARAM lParam)
{
  int i,id,len;
  LPCWSTR p;
  HWND hwnd;
  LPOFNOTIFY lpof;

  switch (message)
    {
    case WM_INITDIALOG:
      /* Populate combobox using CB_ADDSTRING. */
      hwnd = GetDlgItem(hdlg, IDC_COMBOBOX);
      if(hwnd != NULL) {
	len = wcslen(combobox_strings);
	for(p=combobox_strings+len+1; *p; p+=len+1) {
	  len = wcslen(p);
	  SendMessageW(hwnd, CB_ADDSTRING, 0, (LPARAM)p);
	}
	SendMessage(hwnd, CB_SETCURSEL, 0, 0);
      }

      /* Initially check some boxes */
      id = CHECKBOX_ID_ORIGIN;
      for(i=0; i<checkboxes_count; i++) {
	if((checkmarks_bitmask>>i)&1)
	  CheckDlgButton(hdlg, id, TRUE);
	id++;
      }
      checkmarks_bitmask = 0;	    /* Used to return final value, too. */

      if(ok_button_label != NULL) {
	HWND parent = GetParent(hdlg);
	hwnd = GetDlgItem(parent, IDOK);
	if(hwnd) SetWindowTextW(hwnd,ok_button_label);
      }

      if(cancel_button_label != NULL) {
	HWND parent = GetParent(hdlg);
	hwnd = GetDlgItem(parent, IDCANCEL);
	if(hwnd) SetWindowTextW(hwnd,cancel_button_label);
      }

      return FALSE;		    /* Returning FALSE lets the default dialog proc run. */

    case WM_COMMAND:
      id = LOWORD(wParam);
      hwnd = (HWND)lParam;
      switch(HIWORD(wParam))
	{
	case CBN_SELCHANGE:
	  /* Selecting a combobox item sets the filename to <item>.kb */
	  if(id == IDC_COMBOBOX)
	    set_file_dialog_filename_from_combobox(hdlg, IDC_COMBOBOX);
	  break;
	case BN_CLICKED:
	  /* Selecting one special checkbox sets the filename to special_string, and
	   * disables all other controls. */
	  if(id == special_checkbox) {
	    if(IsDlgButtonChecked(hdlg,id)) {
	      static wchar_t s_zero_wc = L'\0';
	      char const *s = special_string;
	      mbstate_t mbst = {0};
	      size_t wc_to_allocate = mbsrtowcs(NULL, &s, 0, &mbst);
	      if (wc_to_allocate != (size_t)-1) {
		wchar_t *special_string_w = (wchar_t*)malloc((wc_to_allocate+1) * sizeof(wchar_t));
		if (NULL == special_string_w) {
		  SendMessage(GetParent(hdlg), CDM_SETCONTROLTEXT, edt1, (LPARAM)&s_zero_wc);
		}
		else {
		  s = special_string;
		  memset(&mbst, 0, sizeof mbst);
		  mbsrtowcs(special_string_w, &s, wc_to_allocate, &mbst);
		  special_string_w[wc_to_allocate] = L'\0';
		  SendMessage(GetParent(hdlg), CDM_SETCONTROLTEXT, edt1, (LPARAM)special_string_w);
		  free(special_string_w);
		}
	      }
	      else {
		SendMessage(GetParent(hdlg), CDM_SETCONTROLTEXT, edt1, (LPARAM)&s_zero_wc);
	      }
	      enable_all_controls_except(hdlg, id, FALSE);
	    }
	    else {
	      set_file_dialog_filename_from_combobox(hdlg, IDC_COMBOBOX);
	      enable_all_controls_except(hdlg, id, TRUE);
	    }
	  }
	  break;
	}
      return FALSE;

    case WM_NOTIFY:
      lpof = (LPOFNOTIFY) lParam;
      switch(lpof->hdr.code)
	{
	case CDN_FILEOK:
	  /* Get bitmask of final set of checks. */
	  id = CHECKBOX_ID_ORIGIN;
	  for(i=0; i<checkboxes_count; i++) {
	    if(IsDlgButtonChecked(hdlg,id))
	      checkmarks_bitmask |= (1<<i);
	    id++;
	  }
	  /* Get combobox selection. */
	  hwnd = GetDlgItem(hdlg, IDC_COMBOBOX);
	  if(hwnd != NULL) 
	    combobox_choice = SendMessage(hwnd, CB_GETCURSEL, 0, 0);

	  return FALSE;
	}
      break;
    }

  return FALSE;
}


/* add_extras_to_file_dialog adds extra controls to a file dialog box by creating
 * a subdialog and attaching it in the standard way. We can add the following things,
 * in order, each of which is optional:
 *
 *  A static string
 *  A combo box with a label
 *  A two-column array of checkboxes.
 *
 * Combobox and checkboxes are the concatenation of all of the choices or checkbox
 * labels, including each trailing NUL, followed by an extra NUL. 
 *
 * Checks is a bitmask of the boxes to be initially checked, with bit 0 corresponding
 * to the first checkbox, placed in the upper left. If a checkbox's label begins with
 * '*', it has special magical properties. Namely, checking it sets the dialog's filename
 * to the given special string, and disables all of the other controls in the dialog.
 * This is the hack to handle saving a rollup KB of all modules.

/* This code is a bit of a mess. It started simple, handling only a table of checkboxes,
 * and then grew.  It should be replaced by a general dialog layout facility, when one
 * is written for GUIDE, or else should be moved up into lisp.
 * -fmw, 11/11/02 */
static DLGTEMPLATE *add_extras_to_file_dialog(OPENFILENAMEW *ofn, 
					       LPCWSTR message,
					       LPCWSTR combobox,
					       LPCWSTR checkboxes, int checks, 
					       LPCSTR  special,
					       LPCWSTR ok_label,
					       LPCWSTR cancel_label)
{
  DLGTEMPLATE *templ;
  DLGITEMTEMPLATE *item;
  int left = WIN32_IS_WIN2K ? 68 : 8; /* Left margin. Leave space for places bar if Win2K/XP */
  int top = 0;			/* Top margin, dialog units. */
  int width, height;		/* Dialog units */
  int row_spacing = 12;		/* Height of each line, dialog units */
  int cy = 10;			/* Height of each control. */
  int n;			/* Number of checkboxes. */
  int lw=0, rw=0;		/* Max string width (d.u.) for Left, right columns. */
  short id;
  int odd, len, x, y, cx, bw, cw, sw, sh;
  LPCWSTR p,q;

  /* Compute total width/height needed for all of the extra controls. */

  /* First, the static string. */
  width = 0;
  height = 0;
  if(message && *message) {
    len = wcslen(message);
    sw = 4*60;			/* String control width (60 chars). */
    sh = 1 + (len-1)/60;	/* String control height in lines. */
    width = MAX(width,sw);
    height += sh*cy;
  }

  /* Then the combobox. */
  cw=0;
  if(combobox && *combobox) {
    p = combobox;			     /* First string is the label. */
    len = wcslen(p);
    bw = 4*len;
    p+=len+1;
    for(; *p; p+=len+1) {
      len = wcslen(p);
      cw = MAX(cw,len*4);
    }
    height += row_spacing;
    width = MAX(width, cw + bw + 8);
  }

  /* Finally, the checkboxes, in two columns */
  n=0;
  for(odd=0, p=checkboxes; *p; p+=len+1, odd=!odd) {
    len = wcslen(p);
    if(odd)
      rw = MAX(rw,4*len);	/* 4 dialog units/character (average) */
    else
      lw = MAX(lw,4*len);
    n++;
  }

  width = left + MAX(width,lw + rw + 32);
  height += top + row_spacing * (n+1)/2;


  /* Now that we know the size, create the dialog and the controls. */
  templ = g2pvt_dialog_template(&item, DLGTEMPLATE_WORKING_SIZE,
		 0, 0, width, height,
		 WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | DS_3DLOOK | DS_CONTROL,
		 0, NULL, NULL, L"Internal subdialog",
		 L"MS Shell Dlg", 8);

  if(templ == NULL)
    return NULL;

  x = left;
  y = top;

  /* Create static string control. */
  id = -1;
  if(message && *message) {
    templ->cdit++;
    item = g2pvt_create_ltext(item, message, id, x, y, sw, sh*cy, SS_LEFT | WS_VISIBLE, 0);
    y += sh*cy;
  }

  /* Create combobox and label. */
  if(combobox && *combobox) {
    cx = 4*wcslen(combobox);
    id = -1;
    templ->cdit++;
    item = g2pvt_create_ltext(item, combobox, id, x, y+2, cx, cy, WS_VISIBLE, 0);
    x += cx + 4;
    cx = cw + 40;		/* +40 is space for the dropdown arrow. */
    id = IDC_COMBOBOX;
    templ->cdit++;
    item = g2pvt_create_combobox(item, id, x, y, cx, 7*cy, 
		    WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL, 0);
    y += row_spacing + 4;
  }

  /* Create checkboxes, in two columns */
  x = left;
  id = CHECKBOX_ID_ORIGIN;
  special_checkbox = -1;
  for(odd=0, p=checkboxes; *p; p+=len+1, odd=!odd) {
    len = wcslen(p);
    if(odd) {
      x = left + lw + 32;
      cx = rw + 16;
    } else {
      x = left;
      cx = lw + 16;
    }
    q = p;
    if(q[0] == '*') {		/* Special checkbox: label begins with '*' */
      q++;
      special_checkbox = id;
    }
    templ->cdit++;
    item = g2pvt_create_autocheckbox(item, q, id, x, y, cx, cy, WS_VISIBLE | WS_TABSTOP, 0);
    if (odd) y += row_spacing;
    id++;
  }

  /* Save info in global variables for use by the hook proc. */
  checkboxes_count = n;
  checkmarks_bitmask = checks;
  combobox_strings = combobox;
  combobox_choice = -1;
  default_extension = ofn->lpstrDefExt;
  special_string = special;
  ok_button_label = ok_label;
  cancel_button_label = cancel_label;

  /* Attach to file dialog. */
  ofn->Flags |= OFN_ENABLETEMPLATEHANDLE | OFN_ENABLEHOOK | OFN_EXPLORER | OFN_ENABLESIZING;
  ofn->hInstance = (HINSTANCE) templ;
  ofn->lpfnHook = checkboxes_file_dialog_hook;
  return templ;
}


/*
 * Server File Dialog
 */

#define LD_REQUEST_FULL_LISTING 0 /* List-directory request opcodes */
#define LD_REQUEST_CHILDREN 1
#define LD_REQUEST_REFRESH 2

static ListDirCallback listdir_callback = NULL;

static void send_list_directory_request(int opcode, int handle, LPWSTR str)
{
  StoreNextEventEx(hwndMain, X11_CONTROL, handle, opcode, -1, -1, GENSYM_LIST_DIRECTORY, 0, str);
}

void g2pvt_request_server_directory(LPWSTR directory, ListDirCallback callback)
{
  send_list_directory_request(LD_REQUEST_FULL_LISTING, 123, directory);
  listdir_callback = callback;
}


/* LISP (list-directory-response) provides the listing in three stages
 * 0. the total count
 * 1. each file in order
 * 2. Finish,
 * or if there was an error, in one call:
 * 3. Error (error message is in NAME)
 */

/* TODO: discard results if dialog is gone (or handle doesn't match). */
long g2ext_list_directory_response(long opcode, long type, long size,
				   long hi_time, long low_time, LPWSTR name)
{
  static FileInfo *fi = NULL;
  static int i = 0;
  static int count = 0;

  switch(opcode) {
   case 0:			/* Begin list of files. */
     i = 0;
     count = type;
     fi = (FileInfo*)calloc(count,sizeof(FileInfo));
     break;
   case 1:			/* i-th file */
     fi[i].type = type;
     fi[i].size = size;
     fi[i].time = ((unsigned long)hi_time)<<16 | low_time;
     fi[i].name = _wcsdup(name);
     i++;
     break;
   case 2:			/* End list of files. */
   case 3:			/* Error */
     if(listdir_callback)
       (*listdir_callback) (fi, count);
     listdir_callback = NULL;
     i = count = 0;
     fi = NULL;

     /* TODO: Show this within the file dialog? */
     if(opcode == 3)		/* Error */
       MessageBoxW(NULL, name, L"Error listing directory", MB_ICONERROR);
     break;
  }
  return 1;
}


void g2ext_list_sys_drives_response(LPCSTR name)
{
  update_remote_sys_drives(name);
}



/* Post a native file open or save dialog, optionally with some additional dialog controls
 * on the bottom. Returns 0 if cancelled, else non-zero. 
 * response[0] holds initial/final bitmask of checked boxes.
 * response[1] gets the index of the selected combobox entry, if any.
 * buffer gets the full pathname chosen. */
long
g2ext_file_dialog(long window_index, 
		  long flags,                /* Bit0:Savep, Bit1:serverp */
		  LPCWSTR title,               /* TODO: unicode */
		  LPCWSTR initial_filename,    /* Just the filename.ext portion, or empty string. */
		  LPCWSTR initial_directory,   /* Must be absolute (rooted) */
		  LPCWSTR default_extension,   /* Without the dot. Used if user omits extension. */
		  LPCWSTR filter,              /* NUL-separated set of strings. */
		  LPWSTR drives,	
		  LPWSTR places,		     /* NUL-separated set of strings. */
		  LPCWSTR message,	     /* Message to add below. */
		  LPCWSTR checkboxes,        /* NUL-separated set of strings. */
		  LPCWSTR combobox,	     /* NUL-separated set of strings. */
		  LPCSTR special,	     /* Special filename string for special checkbox */
		  LPCWSTR ok_label,          /* Label for OK button. */
		  LPCWSTR cancel_label,	     /* Label for Cancel button. */
		  unsigned short *response,  /* Initial/final checks[0], combo choice[1] */
		  LPWSTR buffer,		     /* Returned pathname */
		  long buflen)		     /* length of buffer */
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  wchar_t pathname[MAX_PATH];
  LPCWSTR dir, ext;
  BOOL result;
  BOOL open_dialog_p = (flags&1) == 0;
  BOOL server_p = (flags&2) != 0;
  OPENFILENAMEW *ofn;
  int ofnsize = (WIN32_IS_WIN2K) ? 88 : 76; /* Only way to get the places bar back. */
  DLGTEMPLATE *templ = NULL;

  OFNCustomData_s custom_data;

  char tempFileName[MAX_PATH * 2];
  int tempFileNameSize;

  ZeroMemory(pathname,sizeof(pathname));
  if(initial_filename)
    wcsncpy(pathname, initial_filename, min(sizeof(pathname)-1, wcslen(initial_filename)));

  dir = NULL;
  if(initial_directory && *initial_directory)
    dir = initial_directory;

  ext = NULL;
  if(default_extension && *default_extension)
    ext = default_extension;

  if(sizeof(OPENFILENAMEW) != 88 && sizeof(OPENFILENAMEW) != 76) {
    fprintf(stderr,"Openfilename size %d not supported.\n", sizeof(OPENFILENAMEW));
    ofnsize = sizeof(OPENFILENAMEW);
  }

  ofn = (OPENFILENAMEW*) malloc(ofnsize);
  ZeroMemory(ofn,ofnsize);
  ofn->lStructSize = ofnsize;
  //Changes for gensym-950 by Cage 2010/2/25
  ofn->hwndOwner = hwndClient;	/* If not owned, then appears as a taskbar button! */
  //End of changes
  ofn->hInstance = NULL;
  ofn->lpstrFilter = filter;
  ofn->lpstrCustomFilter = NULL;
  ofn->nMaxCustFilter = 0;
  ofn->nFilterIndex = 0;
  ofn->lpstrFile = pathname;
  ofn->nMaxFile = sizeof(pathname);
  ofn->lpstrFileTitle = NULL;
  ofn->nMaxFileTitle = 0;
  ofn->lpstrInitialDir = dir;
  ofn->lpstrTitle = title;
  ofn->Flags = OFN_HIDEREADONLY;
  if(open_dialog_p)
    ofn->Flags |= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
  ofn->nFileOffset = 0;
  ofn->nFileExtension = 0;
  ofn->lpstrDefExt = ext;
  ofn->lCustData = 0L;
  ofn->lpfnHook = NULL;

  strlist_copy( custom_data.shortcuts,      places);
  // why?
  strlist_copy( custom_data.shortcut_names, L"My Recent Documents\0Desktop\0My Documents\0My Computer\0My Network Places\0\0");
  strlist_copy( custom_data.drives,         drives);

  if(server_p) {
    ofn->lpTemplateName = (LPCWSTR) g2pvt_request_server_directory;
    ofn->lCustData = (LPARAM) &custom_data;	/* Places bar */
  }

  if((message && *message) || (combobox && *combobox) || (checkboxes && *checkboxes) ||
     (ok_label && *ok_label) || (cancel_label && *cancel_label))
    templ = add_extras_to_file_dialog(ofn, message, combobox, checkboxes, response[0], 
				      special,
				      *ok_label ? ok_label : NULL,
				      *cancel_label ? cancel_label : NULL);
  else {
    ok_button_label = NULL;
    cancel_button_label = NULL;
  }

  g2pvt_enter_modal_loop();
  if(server_p)
    result = GetServerFileName(ofn);
  else if(open_dialog_p)
    result = GetOpenFileNameW(ofn);
  else
    result = GetSaveFileNameW(ofn);
  g2pvt_exit_modal_loop();

  /* Only client-side functions set commdlg error. */
  if((result == 0) && (!server_p)) {
    int err = CommDlgExtendedError();
    switch(err) {
      case FNERR_INVALIDFILENAME: /* This is the only error likely to happen. */
        if (!ofn->lpstrFile) {
          g2pvt_inform_user(MB_ICONERROR, "File dialog failed",
                            "Invalid pathname: (null)");
        } else {
          tempFileNameSize = wcstombs(tempFileName, ofn->lpstrFile, MAX_PATH * 2 - 1);
          tempFileName[tempFileNameSize] = '\0';
          g2pvt_inform_user(MB_ICONERROR, "File dialog failed",
                            "Invalid pathname: \"%s\"", tempFileName);
        }
        break;
      case FNERR_BUFFERTOOSMALL:
        g2pvt_inform_user(MB_ICONERROR, "File dialog failed", "Buffer too small");
        break;
    }
  }

  buffer[0] = L'\0';
  if (result)
    wcsncpy(buffer, pathname, min(wcslen(pathname), buflen - 1));
  buffer[min(wcslen(pathname), buflen - 1)] = L'\0';

  if(templ) free(templ);
  free(ofn);

  response[0] = checkmarks_bitmask;
  response[1] = combobox_choice;

  return result;
}



/*
 * Choose Directory
 */

#define CD_POST_CLIENT_DIALOG 0	/* Opcodes */
#define CD_POST_SERVER_DIALOG 2
#define CD_ADD_CHILDREN 1
#define CD_REFRESH 3

#define MAX_PATH_CHARS 512

typedef struct {
  BOOL active;
  HWND hwndTV;
  LPWSTR caption;
  LPWSTR okLabel;
  LPWSTR cancelLabel;
  LPWSTR root;			/* Root directory (an opaque string to prepend) */
  LPWSTR tree;			/* Initial tree */
  LPWSTR separator;		/* Pathname separator, as one-element string. */
  LPWSTR pathname;		/* Input/output */
  int buflen;			/* In characters */
  BOOL caseSensitive;
} ChooseDirDlg;

static ChooseDirDlg g_chooseDir;

/* Tree is of the form "node\0child\0...child\0\0\0" */
static void populate_directory_tree(HWND hwndTV, LPWSTR tree, BOOL caseSensitive)
{
  HTREEITEM parent = NULL;
  LPWSTR str;

  str = tree;
  while(*str) {
    if(parent)
      parent = TreeView_FindChild(hwndTV, parent, str, caseSensitive);
    else
      parent = TreeView_AddChild(hwndTV, NULL, str);

    for(str+=wcslen(str)+1; *str; str += wcslen(str)+1)
      TreeView_AddChild(hwndTV, parent, str);
    str++;
  }
  TreeView_SelectItem(hwndTV, parent);
}

static void pack_root_and_path(ChooseDirDlg *pDialog, HTREEITEM hItem,
			       BOOL prefixRoot, LPWSTR buf, int buflen)
{
  HWND hwndTV = pDialog->hwndTV;
  LPWSTR ptr = buf;

  if(prefixRoot) {		// Unpacked by unpack-list-directory-request-value
    wcscpy(ptr, pDialog->root);
    wcscat(ptr, L"\001");
    ptr += wcslen(ptr);
  }

  wcscpy(ptr, pDialog->root);
  if(wcslen(ptr)>0 && ptr[wcslen(ptr)-1] != pDialog->separator[0]) // Last-minute hack
    wcscat(ptr, pDialog->separator);
  ptr += wcslen(ptr);

  TreeView_GetPath(hwndTV, hItem, 1, pDialog->separator, ptr, buflen-(ptr-buf));
}

static void request_children_if_needed(ChooseDirDlg *pDialog, HTREEITEM hItem)
{
  HWND hwndTV = pDialog->hwndTV;
  wchar_t str[MAX_PATH_CHARS];

  if(TreeView_GetChild(hwndTV, hItem) || TreeView_GetItemParam(hwndTV, hItem))
     return;			// Initially expanded or expanded by user

  TreeView_SetItemParam(hwndTV, hItem, 1);
  pack_root_and_path(pDialog, hItem, TRUE, str, MAX_PATH_CHARS);
  send_list_directory_request(LD_REQUEST_CHILDREN, 1234, str);
}

static void request_full_refresh(ChooseDirDlg *pDialog)
{
  HWND hwndTV = pDialog->hwndTV;
  HTREEITEM hItem = TreeView_GetSelection(hwndTV);
  wchar_t str[MAX_PATH_CHARS];

  pack_root_and_path(pDialog, hItem, TRUE, str, MAX_PATH_CHARS);
  TreeView_DeleteAllItems(hwndTV);
  send_list_directory_request(LD_REQUEST_REFRESH, 1234, str);
}

static void return_full_pathname(ChooseDirDlg *pDialog)
{
  HWND hwndTV = pDialog->hwndTV;
  HTREEITEM hItem = TreeView_GetSelection(hwndTV);
  pack_root_and_path(pDialog, hItem, FALSE, pDialog->pathname, pDialog->buflen);
}

// Response is path to node, then children of node. Expand node after adding children.
static void add_children_to_active_server_dialog(LPWSTR str)
{
  HWND hwndTV = g_chooseDir.hwndTV;
  HTREEITEM parent;
  BOOL caseSensitive = g_chooseDir.caseSensitive;

  if(!hwndTV) return;

  parent = NULL;
  while(*str && ((parent = TreeView_FindChild(hwndTV, parent, str, caseSensitive))))
    str += wcslen(str)+1;

  str++;
  while(*str) {
    TreeView_AddChild(hwndTV, parent, str);
    str += wcslen(str)+1;
  }

  // Since we now know definitively whether we have children or not, either
  // expand the node if we do, or change the node to a leaf if we do not.
  if(TreeView_GetChild(hwndTV, parent))
    TreeView_Expand(hwndTV, parent, TVE_EXPAND);
  else
    TreeView_SetItemCChildren(hwndTV, parent, 0);
}

static void refresh_active_server_dialog(LPWSTR tree)
{
  HWND hwndTV = g_chooseDir.hwndTV;
  BOOL caseSensitive = g_chooseDir.caseSensitive;

  if(!hwndTV) return;
  populate_directory_tree(hwndTV, tree, caseSensitive);
}


static BOOL CALLBACK FolderDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HWND hwndTV = GetDlgItem(hwnd,IDC_TREE1);
  ChooseDirDlg *pDialog = &g_chooseDir;

  switch (message) {
   case WM_INITDIALOG: {
     pDialog->hwndTV = hwndTV;

     SetDlgItemTextW(hwnd, IDC_STATIC, pDialog->caption);

     if(pDialog->okLabel && pDialog->okLabel[0])
       SetDlgItemTextW(hwnd, IDOK, pDialog->okLabel);

     if(pDialog->cancelLabel && pDialog->cancelLabel[0])
       SetDlgItemTextW(hwnd, IDCANCEL, pDialog->cancelLabel);

     TreeView_SetImageList(hwndTV, CreateFolderImageList(), TVSIL_NORMAL);
     populate_directory_tree(hwndTV, pDialog->tree, pDialog->caseSensitive);
     SetFocus(hwndTV);
     return FALSE;
   }
   break;

   case WM_NOTIFY:
     if(wParam == IDC_TREE1) {
       NMTREEVIEW *pTree = (NMTREEVIEW *)lParam;

       switch(pTree->hdr.code) {
        case TVN_ITEMEXPANDING:
	  request_children_if_needed(pDialog, pTree->itemNew.hItem);
	  break;

	case TVN_KEYDOWN:
	  if(((NMTVKEYDOWN *)lParam)->wVKey == VK_F5)
	    request_full_refresh(pDialog);
	  break;
       }
     }
     return TRUE;

   case WM_COMMAND:
     switch (LOWORD(wParam)) {
      case IDOK:
	return_full_pathname(pDialog);
      case IDCANCEL:
        EndDialog(hwnd, LOWORD(wParam));
        return TRUE;
     }
     break;

   case WM_DESTROY:
     if(hwndTV && TreeView_GetImageList(hwndTV,TVSIL_NORMAL))
       ImageList_Destroy(TreeView_GetImageList(hwndTV,TVSIL_NORMAL));
     break;
  }
  return FALSE;
}

static int ChooseDirectoryOnServer(LPWSTR caption, LPWSTR pathname, 
				   LPWSTR root, LPWSTR tree, LPWSTR separator,
				   LPWSTR okLabel, LPWSTR cancelLabel)
{
  int rc;
  if(g_chooseDir.active) {
    g2pvt_notify_user("Attempted to create nested choose-directory dialogs.");
    return 0;
  }

  g_chooseDir.active = TRUE;
  g_chooseDir.hwndTV = NULL;
  g_chooseDir.caption = caption;
  g_chooseDir.okLabel = okLabel;
  g_chooseDir.cancelLabel = cancelLabel;
  g_chooseDir.root = root;
  g_chooseDir.tree = tree;
  g_chooseDir.separator = separator;
  g_chooseDir.pathname = pathname;
  g_chooseDir.buflen = MAX_PATH_CHARS;
  g_chooseDir.caseSensitive = (separator[0] == L'/');

  rc = DialogBoxParam(hInst, (LPCTSTR)IDD_DIRDLG, hwndFrame, FolderDlgProc, 0);

  g_chooseDir.active = FALSE;
  g_chooseDir.hwndTV = NULL;

  if(rc < 0)
    g2pvt_notify_user("Failed to create choose directory DialogBox.\n");
  return rc == IDOK;
}

/* Post a native browse for folder dialog */
long g2ext_choose_directory(long opcode, LPWSTR caption, LPWSTR pathname, 
			    LPWSTR root, LPWSTR tree, LPWSTR separator,
			    LPWSTR okLabel, LPWSTR cancelLabel)
{
  int result = 0;

  switch(opcode&3) {
   case CD_POST_CLIENT_DIALOG:
     g2pvt_enter_modal_loop();
     result = BrowseForFolder(hwndFrame, caption, pathname, root, okLabel, cancelLabel);
     g2pvt_exit_modal_loop();
     break;

   case CD_POST_SERVER_DIALOG:
     g2pvt_enter_modal_loop();
     result = ChooseDirectoryOnServer(caption, pathname, root, tree, separator, okLabel, cancelLabel);
     g2pvt_exit_modal_loop();
     break;

   case CD_ADD_CHILDREN:
     add_children_to_active_server_dialog(tree);
     break;

   case CD_REFRESH:
     refresh_active_server_dialog(tree);
     break;
  }
  return result;
}



/*
 * Html Help
 */

static HWND g_hwndHelp = NULL;

#define HH_DISPLAY_ENVAR_TOPIC 0x80

/* Old routine, used directly by TW without G2 interaction. */
void g2pvt_show_tw_help(HWND hwnd)
{
  g2ext_html_help(HH_DISPLAY_ENVAR_TOPIC, NULL, NULL, NULL, 0, 0, 0, 0);
}

/* Returns potentially new cmd value */
static int compute_help_file(int cmd, char *dir, char *file, char *helpfile, int len)
{
  char *envar, *filepart, *cp;

  helpfile[0] = '\0';

  if(cmd == HH_DISPLAY_ENVAR_TOPIC) { // Old way, using PATH and envar.
    if((envar = getenv(HELP_FILE_NAME_ENVAR)))
      strncpy(helpfile, envar, len-1);

    else if(SearchPath(NULL, HELP_FILE_NAME_DEFAULT, NULL, len-1, helpfile, &filepart) == 0)
      strncpy(helpfile, HELP_FILE_NAME_DEFAULT, len-1);
    helpfile[len-1] = '\0';
    return HH_DISPLAY_TOPIC;
  }

  if(dir && dir[0]) {
    strcpy(helpfile, dir);
  } else {
    GetModuleFileName(hInst, helpfile, len);
    cp = strrchr(helpfile, '\\');
    if(cp) cp[1] = '\0';
  }

  if(file && file[0]) {
    if(helpfile[strlen(helpfile)-1] != '\\')
      strcat(helpfile, "\\");
    strcat(helpfile,file);
  }
  return cmd;
}

/* This is checking for the standard help file shown by "Help Topics" */
BOOL g2pvt_help_available_p(void)
{
  char helpfile[MAX_PATH];

  compute_help_file(HH_DISPLAY_ENVAR_TOPIC, NULL, NULL, helpfile, sizeof(helpfile));
  return GetFileAttributes(helpfile) != INVALID_FILE_ATTRIBUTES;
}

long g2ext_html_help(long cmd, char *dir, char *file, char *string, long id, long x, long y, long flags)
{
  char *str = (string && string[0]) ? string : NULL;
  char helpfile[MAX_PATH];
  HH_POPUP p;
  HH_AKLINK k;
  HH_FTS_QUERY q;

  cmd = compute_help_file(cmd, dir, file, helpfile, sizeof(helpfile));

  switch(cmd) {
   case HH_DISPLAY_TOPIC:
   case HH_DISPLAY_TOC:
   case HH_DISPLAY_INDEX:
     g_hwndHelp = HtmlHelp(hwndFrame, helpfile, cmd, (DWORD)str);
     break;

   case HH_HELP_CONTEXT:
     g_hwndHelp = HtmlHelp(hwndFrame, helpfile, cmd, id);
     break;

   case HH_DISPLAY_TEXT_POPUP:
     ZeroMemory(&p,sizeof(p));
     p.cbStruct = sizeof(HH_POPUP);
     p.hinst = NULL;
     p.idString = str ? 0 : id;
     p.pszText = str;
     if(x == -1 && y == -1)
       GetCursorPos(&p.pt);
     else {
       p.pt.x = x;
       p.pt.y = y;
     }
     p.clrForeground = -1;
     p.clrBackground = -1;
     SetRect(&p.rcMargins, -1, -1, -1, -1);
     p.pszFont = NULL;
     g_hwndHelp = HtmlHelp(hwndFrame, helpfile, cmd, (DWORD)&p);
     break;

   case HH_ALINK_LOOKUP:
   case HH_KEYWORD_LOOKUP:
     if(!g_hwndHelp)
       g_hwndHelp = HtmlHelp(hwndFrame, helpfile, HH_DISPLAY_TOPIC, 0);
     ZeroMemory(&k,sizeof(k));
     k.cbStruct = sizeof(HH_AKLINK);
     k.fReserved = FALSE;
     k.pszKeywords = string;
     k.pszUrl = NULL;		// Topic to display on failure.
     k.pszMsgText = NULL;	// Message to display on failure
     k.pszMsgTitle = NULL;	// Title of msgbox
     k.pszWindow = NULL;
     k.fIndexOnFail = TRUE;
     g_hwndHelp = HtmlHelp(hwndFrame, helpfile, cmd, (DWORD)&k);
     break;

   case HH_DISPLAY_SEARCH:	// Useless, just displays the search tab.
     ZeroMemory(&q,sizeof(q));
     q.cbStruct = sizeof(HH_FTS_QUERY);
     q.fUniCodeStrings = FALSE;
     q.pszSearchQuery = string;
     q.iProximity = HH_FTS_DEFAULT_PROXIMITY;
     q.fStemmedSearch = (flags&2) ? TRUE : FALSE;
     q.fTitleOnly     = (flags&4) ? TRUE : FALSE;
     q.fExecute = TRUE;		// Doesn't work.
     q.pszWindow = NULL;
     g_hwndHelp = HtmlHelp(hwndFrame, helpfile, cmd, (DWORD)&q);
     break;

   case HH_CLOSE_ALL:
     HtmlHelp(NULL, NULL, HH_CLOSE_ALL, 0);
     g_hwndHelp = NULL;
     return 1;
  }

  if(g_hwndHelp)
    return 1;

  g2pvt_inform_user(MB_ICONERROR, "Help Error", 
		    "Unable to display help file \"%s\"", helpfile);
  return 0;
}



/*
 * Mouse Cursors
 */

#ifndef IDC_HAND		/* Temporary fix!! */
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif

int g2pvt_set_mouse_cursor(int window_index, int cursorID)
{
  static LPCSTR shapes[] = {NULL, IDC_ARROW, IDC_CROSS, IDC_HAND, IDC_HELP, IDC_IBEAM,
			    IDC_NO, IDC_SIZEALL, IDC_SIZENESW, IDC_SIZENS,
			    IDC_SIZENWSE, IDC_SIZEWE, IDC_UPARROW, 
			    IDC_WAIT};
  if(cursorID<=0 || cursorID >= sizeof(shapes)/sizeof(LPCSTR)) {
    SetCursor(LoadCursor(NULL,IDC_ARROW)); // TODO: Ought to be window-under-mouse's cursor.
    g_mouseCursor = NULL;
  } else {
    g_mouseCursor = LoadCursor(NULL,shapes[cursorID]);
    SetCursor(g_mouseCursor);
  }

  return 1;
}



/***********************************************************************
 *
 * Print Dialog
 *
 ***********************************************************************/

/* Post the Win32 print dialog. Returns printer HDC or NULL on error. */
static HDC g2pvt_print_dialog(HWND hwnd, char *printerName, int buflen, int npages,
			      BOOL useDefaultPrinter, BOOL *pPrintToFile)
{
  HINSTANCE hinst = GetWindowInstance(hwnd);
  DEVMODE *dm;
  int rc;
  BOOL printToFile;
  DWORD flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC | PD_NOPAGENUMS | PD_NOSELECTION;

  /* These memory blocks hold the current user preferences for printing:
   * printer choice, page orientation, etc. They are local to the TW process.
   * Possibly they ought to be per-Window, but that would be non-standard
   * compared to other Windows apps. */
  static HGLOBAL devmode = NULL; // TODO: free HGLOBALs on process exit (?)
  static HGLOBAL devnames = NULL;
  static PRINTDLG pd;

  if(inside_print_dialog)
    return NULL;

  if(useDefaultPrinter) {
    flags |= PD_RETURNDEFAULT;
    if(devmode) GlobalFree(devmode);
    if(devnames) GlobalFree(devnames);
    devmode = devnames = NULL;
  }

  ZeroMemory(&pd,sizeof(pd));
  pd.lStructSize = sizeof(pd);
  pd.hwndOwner   = hwnd;
  pd.Flags       = flags;
  pd.hDevMode    = devmode;
  pd.hDevNames   = devnames;
  pd.nCopies     = 1;
  /*
    pd.nFromPage   = 1; 
    pd.nToPage     = 1;
    pd.nMinPage    = 1; 
    pd.nMaxPage    = npages;
    */

  inside_print_dialog = 1;
  rc = PrintDlg(&pd);
  inside_print_dialog = 0;

  devmode = pd.hDevMode;
  devnames = pd.hDevNames;

  if(rc == 0)
    return NULL;

  printToFile = (pd.Flags & PD_PRINTTOFILE) != 0;
  if(pPrintToFile)
    *pPrintToFile = printToFile;

  if(printerName != NULL) {	/* Optionally return printer name. */
    printerName[0] = 0;
    if(printToFile) {		/* If printing to a file, return the filename instead. */
      OPENFILENAME ofn;
      ZeroMemory(printerName, buflen);
      ZeroMemory(&ofn,sizeof(OPENFILENAME));
      ofn.lStructSize = sizeof(OPENFILENAME);
      ofn.hwndOwner = hwndFrame;
      ofn.lpstrFile = printerName;
      ofn.nMaxFile = buflen;
      ofn.lpstrTitle = "Print to File";

      /* Taken from mfc/include/afxprint.rc (English) */
      ofn.lpstrFilter = "Printer Files (*.prn)\0*.prn\0All Files (*.*)\0*.*\0";
      ofn.lpstrDefExt = "prn";

      ofn.Flags = OFN_OVERWRITEPROMPT;
      if(!GetSaveFileName(&ofn)) { /* TODO: Maintain last chosen directory */
	DeleteDC(pd.hDC);
	return NULL;
      }
    } else {
      dm = (DEVMODE *)GlobalLock(devmode);
      strncpy(printerName, dm->dmDeviceName, buflen-1);
      GlobalUnlock(devmode);
    }
    printerName[buflen-1] = '\0';
  }
  return pd.hDC;
}

/***********************************************************************
 *
 * Print window as bitmap.
 * From Q186736 HOWTO: Capture and Print an Entire Window
 *
 ***********************************************************************/

// Create a 24-bit-per-pixel surface.
static HBITMAP Create24BPPDIBSection(HDC hDC, int width, int height)
{
  BITMAPINFO bmi;
  LPBYTE pBits; 

  ZeroMemory(&bmi, sizeof(bmi)); 
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = width;
  bmi.bmiHeader.biHeight = height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB; 

  return CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0); 
} 


/* Capture the on-screen bits of given window into a DIB bitmap,
 * and return the bitmap handle, or NULL on failure. */
static HBITMAP capture_window_bitmap(HWND hwnd)
{
  HBITMAP hbm;
  HDC hdcMemory, hdcWindow;
  POINT p;
  RECT r;
  HPALETTE hPal = NULL;

  if (!IsWindow(hwnd))
    return NULL;

  // Get the HDC for the entire window.
  hdcWindow  = GetWindowDC(hwnd); 
  p.x = p.y = 0;
  ClientToScreen(hwnd, &p);
  GetWindowRect(hwnd, &r);
  p.x -= r.left;
  p.y -= r.top;
  GetClientRect(hwnd, &r); 

  // Create the intermediate drawing surface at window resolution.
  hbm = Create24BPPDIBSection(hdcWindow, r.right, r.bottom);
  if (!hbm) {
    fprintf(stderr,"Cannot allocate %dx%d DIB section.\n", r.right, r.bottom);
    ReleaseDC(hwnd, hdcWindow);
    return FALSE;
  } 

  // Prepare the surface for drawing.
  hdcMemory = CreateCompatibleDC(hdcWindow);
  SelectObject(hdcMemory, hbm); 

  if (hPal) {
    // Apply the palette to the source DC.
    SelectPalette(hdcWindow, hPal, FALSE);
    RealizePalette(hdcWindow); 

    // Apply the palette to the destination DC.
    SelectPalette(hdcMemory, hPal, FALSE);
    RealizePalette(hdcMemory);
  } 

  // Copy the window contents to the memory surface.
  /* TODO: Want offscreen parts to be white, not black. */
  BitBlt(hdcMemory, 0, 0, r.right, r.bottom,
	 hdcWindow, p.x, p.y, SRCCOPY);

  ReleaseDC(hwnd, hdcWindow);
  DeleteDC(hdcMemory);
  return hbm;
}


static LPCWSTR window_title(HWND hwnd)
{
  static wchar_t title[256];

  if(GetWindowTextW(hwnd, title, 255) > 0)
    title[255] = L'\0';
  else
    wcscpy(title,L"G2-Window");
  return title;
}

/* Print given bitmap, which must be a 24-bit RGB DIB. */
static BOOL print_bitmap(HWND hwnd, HBITMAP hbm, LPCWSTR title, BOOL useDefaultPrinter)
{
  HDC hdcPrinter;
  DIBSECTION ds;
  int w,h;			/* Bitmap dimensions. */
  int width, height;		/* Page dimensions. */
  DOCINFOW di;
  BOOL printToFile = FALSE;
  char printerName[MAX_PATH];
  wchar_t outputFile[MAX_PATH];

  hdcPrinter = g2pvt_print_dialog(hwnd, printerName, sizeof(printerName), 1, useDefaultPrinter, &printToFile);
  if (hdcPrinter == NULL)
    return FALSE;

  // Get bitmap dimensions.
  GetObject(hbm, sizeof(DIBSECTION), &ds);
  w = ds.dsBm.bmWidth;
  h = ds.dsBm.bmHeight;

  // Get the resolution of the printer device.
  width  = GetDeviceCaps(hdcPrinter, HORZRES);
  height = GetDeviceCaps(hdcPrinter, VERTRES);

  // Scale to fit page.
  if(width*h < height*w)
    height = (int) (h * width/(double)w);
  else
    width = (int) (w * height/(double)h);

  ZeroMemory(&di, sizeof(di));
  di.cbSize = sizeof(di);
  di.lpszDocName = title;
  if(printToFile) {
    mbstowcs(outputFile, printerName, MAX_PATH);
    outputFile[MAX_PATH-1] = 0;
    di.lpszOutput = outputFile;
  }

  if (StartDocW(hdcPrinter, &di) > 0) {
    if (StartPage(hdcPrinter) > 0) {
      StretchDIBits(hdcPrinter,
		    0, 0, width, height,
		    0, 0, w, h,
		    ds.dsBm.bmBits,
		    (LPBITMAPINFO)&ds.dsBmih,
		    DIB_RGB_COLORS,
		    SRCCOPY);
      EndPage(hdcPrinter);
    }
    EndDoc(hdcPrinter);
  }
  DeleteDC(hdcPrinter);
  return TRUE;
}


/* Display print dialog and print client area of given window. */
long g2ext_print_window(long window_index, LPCWSTR jobname, long flags)
{
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  HBITMAP hbm;
  int rc;
  BOOL useDefaultPrinter = (flags&1) != 0;

  if(!IsWindow(hwnd))
    return -1;

  /* Special case to get the title from the frame 
     if given hwndClient (which is titleless). */
  if(jobname == NULL || wcslen(jobname) == 0)
    jobname = window_title(hwnd==hwndClient ? hwndFrame : hwnd);

  hbm = capture_window_bitmap(hwnd);
  if(hbm == NULL)
    return -2;

  g2pvt_enter_modal_loop();
  rc = print_bitmap(hwnd, hbm, jobname, useDefaultPrinter);
  g2pvt_exit_modal_loop();

  DeleteObject(hbm);
  return rc;
}



/***********************************************************************
 *
 * Full-resolution Native Printing
 *
 ***********************************************************************/

HDC printer_dc = NULL;		/* If non-NULL, printing is in progress. */
extern int draw_to_printer;	/* If TRUE, graphics temporarily go to printer DC. */
static int page_count;
static BOOL printing_in_progress = FALSE;
static wchar_t page_title[256];
static wchar_t printerOutputFile[MAX_PATH];

long g2ext_start_doc(long, LPWSTR);

static BOOL CALLBACK AbortProc(HDC hdc, int nCode)
{
  MSG msg;

  PTRACE("AbortProc(%d)\n", nCode);

  while (PeekMessageW(&msg, (HWND) NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
  return printing_in_progress;
} 

/* Post the Win32 print dialog. Returns 1 unless cancelled or error. */
long g2ext_print_dialog(long window_index, LPWSTR title, long flags,
			char *printer, long buflen,
			short *results)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  HINSTANCE hinst = GetWindowInstance(hwnd);
  int rc;
  BOOL useDefaultPrinter = (flags&1) != 0;
  BOOL printToFile = FALSE;

  if(printer_dc != NULL) {
    // Ask to abort current job? Needs help from G2.
    g2pvt_inform_user(MB_ICONERROR, 
		      "Printing failed",
		      "Can't post dialog: Printing already in progress.");
    return -1;
  }

  g2pvt_enter_modal_loop();
  printer_dc = g2pvt_print_dialog(hwnd, printer, buflen, 1, useDefaultPrinter, &printToFile);
  g2pvt_exit_modal_loop();

  if(printer_dc == NULL)
    return -2;

  printerOutputFile[0] = 0;
  if(printToFile) {
    mbstowcs(printerOutputFile, printer, MAX_PATH);
    printerOutputFile[MAX_PATH-1] = 0;
  }

  /* Must match code in print-dialog-1 in telestubs.lisp */
  results[0] = GetDeviceCaps(printer_dc,HORZRES);
  results[1] = GetDeviceCaps(printer_dc,VERTRES);
  results[2] = GetDeviceCaps(printer_dc,LOGPIXELSX);
  results[3] = GetDeviceCaps(printer_dc,LOGPIXELSY);
  results[4] = GetDeviceCaps(printer_dc,PHYSICALWIDTH);
  results[5] = GetDeviceCaps(printer_dc,PHYSICALHEIGHT);
  results[6] = GetDeviceCaps(printer_dc,PHYSICALOFFSETX);
  results[7] = GetDeviceCaps(printer_dc,PHYSICALOFFSETY);
  results[8] = 0;			       // pd.nFromPage;
  results[9] = 0;			       // pd.nToPage;

  PTRACE("Printer %s %dx%d dots, %dx%d dpi\n",
	 printer, results[0], results[1], results[2], results[3]);

  rc = g2ext_start_doc(window_index, title);
  return rc;
}

long g2ext_start_doc(long window_index, LPWSTR title)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  DOCINFOW di;
  int job,n;

  PTRACE("g2ext_start_doc %ls\n", title);
  if(printer_dc == NULL) return -1;

  ZeroMemory(&di, sizeof(di));
  di.cbSize = sizeof(di);
  di.lpszDocName = title;
  if(printerOutputFile[0])
    di.lpszOutput = printerOutputFile;    

  wcscpy(page_title, L"G2 Workspace: "); /* Compute title for each  page. */
  n = wcslen(page_title);
  wcsncpy(page_title+n, title, 255-n);
  page_title[255] = L'\0';

  /* StartDoc may post a dialog (for choosing an output file). */
  g2pvt_enter_modal_loop();
  job = StartDocW(printer_dc, &di);
  g2pvt_exit_modal_loop();

  PTRACE("StartDoc job = %d\n", job);

  /* AbortProc is pretty useless on NT/2K/XP. */
  if(job > 0) {
    printing_in_progress = TRUE;
    SetAbortProc(printer_dc, AbortProc);
  } else {
    g2ext_abort_printing();
  }
  return job;
}

/* Draw little legend in margins at lower-left corner of page.
 * Vertical space available is given in device units. */
static void draw_multipage_legend(HDC hdc, int page, int nrows, int ncolumns,
				  int physical_width, int physical_height,
				  int x, int y, int space)
{
  int i,j,p,dx,dy,ydpi,dy_max;
  RECT r;
  HBRUSH gray, black;

  ydpi = GetDeviceCaps(printer_dc,LOGPIXELSY);
  dy_max = (int) (ydpi * .2);	// Max height of pagelet (.2 inches)
  dy = MIN(dy_max,MAX(0, space/nrows));
  dx = (dy * physical_width) / physical_height;

  PTRACE("space %d x %d y %d dx %d dy %d\n", space, x, y, dx, dy);

  if(dx<1 || dy<5) return;

  y -= dy*nrows;
  reset_dc(hdc);

  gray = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
  black = (HBRUSH) GetStockObject(BLACK_BRUSH);
  p=1;
  for(i=0; i<nrows; i++)
    for(j=0; j<ncolumns; j++) {
      r.left = x + j*dx;
      r.top = y + i*dy;
      r.right = r.left + dx;
      r.bottom = r.top + dy;
      if(p == page)
	FillRect(hdc, &r, gray);
      FrameRect(hdc, &r, black);
      p++;
    }
}

static int page_width, page_height;           /* Printable area, in dots. */
static int page_lm, page_tm, page_rm, page_bm;

/* Add current time to top right of page. */
static void draw_page_date(HDC hdc)
{
  char *str;
  int oldAlign;
  extern char *g2ext_current_time(void);

  str = g2ext_current_time();

  SetBkMode(hdc, TRANSPARENT);
  SetTextColor(hdc, RGB(0,0,0));
  oldAlign = SetTextAlign(hdc, TA_RIGHT|TA_BOTTOM);
  TextOut(hdc, page_width-page_rm, page_tm, str, strlen(str)-1); /* -1 for \n at end. */
  SetTextAlign(hdc, oldAlign);
  SetBkMode(hdc, OPAQUE);
}

/* Add job title to top left of page. */
static void draw_page_title(HDC hdc)
{
  int oldAlign;

  SetBkMode(hdc, TRANSPARENT);
  SetTextColor(hdc, RGB(0,0,0));
  oldAlign = SetTextAlign(hdc, TA_LEFT|TA_BOTTOM);
  TextOutW(hdc, page_lm, page_tm, page_title, wcslen(page_title));
  SetTextAlign(hdc, oldAlign);
  SetBkMode(hdc, OPAQUE);
}

/* Add label to bottom left */
static void draw_page_label(HDC hdc, LPWSTR label)
{
  int oldAlign;

  SetBkMode(hdc, TRANSPARENT);
  SetTextColor(hdc, RGB(0,0,0));
  oldAlign = SetTextAlign(hdc, TA_LEFT|TA_TOP);
  TextOutW(hdc, page_lm, page_height-page_bm, label, wcslen(label));
  SetTextAlign(hdc, oldAlign);
  SetBkMode(hdc, OPAQUE);
}

/* Add page number to bottom right */
static void draw_page_number(HDC hdc, int page, int npages)
{
  int oldAlign;
  char buf[32];

  SetBkMode(hdc, TRANSPARENT);
  SetTextColor(hdc, RGB(0,0,0));
  oldAlign = SetTextAlign(hdc, TA_RIGHT|TA_TOP);
  sprintf(buf,"Page %d of %d", page, npages);
  TextOut(hdc, page_width-page_rm, page_height-page_bm, buf, strlen(buf));
  SetTextAlign(hdc, oldAlign);
  SetBkMode(hdc, OPAQUE);
}

/* Draws a dotted line around the printed area of current page. */
static void draw_page_frame(HDC hdc)
{
  HPEN hpen, oldPen;

  hpen = CreatePen(PS_DOT, 1, 0);
  oldPen = SelectObject(hdc, hpen);
  MoveToEx(hdc,page_lm, page_tm,NULL);
  LineTo(hdc,page_width-page_rm, page_tm);
  LineTo(hdc,page_width-page_rm, page_height-page_bm);
  LineTo(hdc,page_lm, page_height-page_bm);
  LineTo(hdc,page_lm, page_tm);
  SelectObject(hdc, oldPen);
  DeleteObject(hpen);
}

long g2ext_start_page(long page, LPWSTR label,
		      long nrows, long ncolumns,
		      long left_margin, long top_margin,
		      long right_margin, long bottom_margin,
		      long scale, long flags)
{
  int rc, xdpi, ydpi, xoff, yoff, pw, ph;

  PTRACE("g2ext_start_page(%d, %dx%d, margins=%d,%d,%d,%d scale=%d, flags=0x%0x)\n",
	 page, nrows, ncolumns, left_margin, top_margin, right_margin, bottom_margin,
	 scale, flags);

  if(printer_dc == NULL) return -1;

  rc = StartPage(printer_dc);

  xdpi = GetDeviceCaps(printer_dc,LOGPIXELSX);
  ydpi = GetDeviceCaps(printer_dc,LOGPIXELSY);
  xoff = GetDeviceCaps(printer_dc,PHYSICALOFFSETX);
  yoff = GetDeviceCaps(printer_dc,PHYSICALOFFSETY);
  page_width = GetDeviceCaps(printer_dc,HORZRES);
  page_height = GetDeviceCaps(printer_dc,VERTRES);
  pw = GetDeviceCaps(printer_dc,PHYSICALWIDTH);
  ph = GetDeviceCaps(printer_dc,PHYSICALHEIGHT);

  /* Margins are in tenths of inches, relative to the edges of the paper.
   * Convert to dots, relative to the edges of the printable area. */
  page_lm = (left_margin * xdpi)/10 - xoff;
  page_tm = (top_margin  * ydpi)/10 - yoff;
  page_rm = (right_margin  * xdpi)/10 - (pw - xoff - page_width);
  page_bm = (bottom_margin * ydpi)/10 - (ph - yoff - page_height);

  PTRACE(" lm %d tm %d rm %d bm %d\n", page_lm, page_tm, page_rm, page_bm);

  page_count = nrows*ncolumns;

  reset_dc(printer_dc);		/* Revert to MM_TEXT (device coordinates). */
  draw_page_title(printer_dc);
  draw_page_date(printer_dc);
  draw_page_number(printer_dc, page, page_count);

  if((flags&1) && page_count>1)
    draw_multipage_legend(printer_dc, page, nrows, ncolumns, pw, ph,
			  page_lm, page_height, page_bm);
  else				/* No room for label if multipage legend present. */
    draw_page_label(printer_dc, label);

  /* Clip to page. */
  IntersectClipRect(printer_dc, page_lm, page_tm, page_width-page_rm, page_height-page_bm);

  SetMapMode(printer_dc, MM_ISOTROPIC);
  SetWindowOrgEx(printer_dc, 0, 0, NULL);
  SetViewportOrgEx(printer_dc, page_lm, page_tm, NULL);

  /* Scale is in workspace units per ten inches. */
  SetWindowExtEx(printer_dc, scale, scale, NULL);
  SetViewportExtEx(printer_dc, 10*xdpi, 10*ydpi, NULL);

  return rc;
}

/* Switch between drawing to normal screen DC or printer DC. */
long g2ext_draw_to_printer(long window_index, long enable)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  PTRACE("g2ext_draw_to_printer %d\n", enable);
  if(printer_dc == NULL) return -1;
  draw_to_printer = enable&1;
  return draw_to_printer;
}

long g2ext_end_page(void)
{
  PTRACE("g2ext_end_page\n");
  if(printer_dc == NULL) return -1;

  reset_dc(printer_dc);		/* Revert to MM_TEXT (device coordinates). */
  if(page_count > 1)
    draw_page_frame(printer_dc);

  return EndPage(printer_dc);
}

long g2ext_end_doc(void)
{
  int rc;
  PTRACE("g2ext_end_doc\n");

  if(printer_dc == NULL) return -1;
  rc = EndDoc(printer_dc);
  DeleteDC(printer_dc);
  printer_dc = NULL;
  page_title[0] = L'\0';
  return rc;
}

long g2ext_abort_printing(void)
{
  int rc;
  PTRACE("g2ext_abort_printing\n");

  if(printer_dc == NULL) return -1;
  printing_in_progress = FALSE;
  rc = AbortDoc(printer_dc);
  DeleteDC(printer_dc);		// When to do this?
  printer_dc = NULL;
  return rc;
}


#ifndef CODEJOCK
long g2ext_is_message_board_enabled() {
  return 1;
}
long g2ext_is_operator_logbook_enabled() {
  return 1;
}
#endif
