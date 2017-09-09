/* -*- Mode: C -*-
 *
 * Module MSINITS
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Pre 7-93: Richard Haggard, Kamal Bijlani
 *
 * Post 1/28/02: mhd, fmw, css, jv
 *
 * mpc 7-8-93: In an effort to bring back the forked PC TW code,
 *       the pc platform file init.c was moved here and cleaned
 *       up.
 *
 */


/*************************************************************************/
/* INCLUDES                                                              */
/*************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winsock.h>
#include <commctrl.h>
#include "cprim.h"
#include "graphics.h"
#include "msincls.h"


/*************************************************************************/
/* DEFINES                                                               */
/*************************************************************************/
typedef void maybe_wait_for_return_key_type ();



/*************************************************************************/
/* GLOBALS and EXTERNS                                                   */
/*************************************************************************/

/* This is the color map of names to rbg values. It is needed during
 * InitPalette() and in g2ext_get_pixel to crossref a color value to a name. */
XCOLOR XColorArray[DEFAULT_COLORS] =
{
   "aquamarine", RGB(127, 255, 212),
   "black", RGB(0, 0, 0),
   "blue", RGB(0, 0, 255),
   "brown", RGB(165, 42, 42),
   "cadet blue", RGB(95, 158, 160),
   "coral", RGB(255, 127, 80),
   "cyan", RGB(0, 255, 255),
   "dark gray", RGB(128, 128, 128),
   "dark grey", RGB(128, 128, 128),
   "dark slate blue", RGB(72, 61, 139),
   "dim gray", RGB(105, 105, 105),
   "dim grey", RGB(105, 105, 105),
   "forest green", RGB(34, 139, 34),
   "gold", RGB(255, 215, 0),
   "goldenrod", RGB(218, 165, 32),
   "gray", RGB(169, 169, 169),
   "grey", RGB(169, 169, 169),
   "green", RGB(0, 255, 0),
   "green yellow", RGB(173, 255, 47),
   "indian red", RGB(205, 92, 92),
   "khaki", RGB(240, 230, 140),
   "light blue", RGB(173, 216, 230),
   "light gray", RGB(211, 211, 211),
   "light grey", RGB(211, 211, 211),
   "lime green", RGB(50, 205, 50),
   "magenta", RGB(255, 0, 255),
   "maroon", RGB(128, 0, 0),
   "medium aquamarine", RGB(102, 205, 170),
   "medium blue", RGB(0, 0, 205),
   "medium goldenrod", RGB(234, 234, 173),
   "medium orchid", RGB(186, 85, 211),
   "orange", RGB(255, 165, 0),
   "pale green", RGB(152, 251, 152),
   "pink", RGB(255, 192, 203),
   "plum", RGB(221, 160, 221),
   "purple", RGB(128, 0, 128),
   "red", RGB(255, 0, 0),
   "salmon", RGB(250, 128, 114),
   "sienna", RGB(160, 82, 45),
   "sky blue", RGB(135, 206, 235),
   "slate blue", RGB(106, 90, 205),
   "tan", RGB(210, 180, 140),
   "thistle", RGB(216, 191, 216),
   "turquoise", RGB(64, 224, 208),
   "violet", RGB(238, 130, 238),
   "violet red", RGB(204, 50, 153),
   "wheat", RGB(245, 222, 179),
   "white", RGB(255, 255, 255),
   "yellow", RGB(255, 255, 0),
   "smoke", RGB(245, 245, 245),
   "white smoke", RGB(245, 245, 245),
   "floral white", RGB(255, 250, 240),
   "linen", RGB(250, 240, 230),
   "antique white", RGB(250, 235, 215),
   "ivory", RGB(255, 255, 240),
   "azure", RGB(240, 255, 255),
   "lavender", RGB(230, 230, 250),
   "light steel blue", RGB(176, 196, 222),
   "powder blue", RGB(176, 224, 230),
   "pale turquoise", RGB(175, 238, 238),
   "light cyan", RGB(224, 255, 255),
   "pale goldenrod", RGB(238, 232, 170),
   "light goldenrod yellow", RGB(250, 250, 210),
   "light yellow", RGB(255, 255, 224),
   "light goldenrod", RGB(238, 221, 130),
   "beige", RGB(245, 245, 220),
   "light pink", RGB(255, 182, 193),
   "extra light gray", RGB(229, 229, 229),
   "extra light grey", RGB(229, 229, 229)
};

XCOLOR XMetaColorArray[TOTAL_NUMBER_OF_COLORS] =
{
   "transparent", RGB(255, 255, 255),
   "foreground", RGB(0, 0, 0),
   "background", RGB(255, 255, 255),
   "aquamarine", RGB(127, 255, 212),
   "black", RGB(0, 0, 0),
   "blue", RGB(0, 0, 255),
   "brown", RGB(165, 42, 42),
   "cadet blue", RGB(95, 158, 160),
   "coral", RGB(255, 127, 80),
   "cyan", RGB(0, 255, 255),
   "dark gray", RGB(128, 128, 128),
   "dark grey", RGB(128, 128, 128),
   "dark slate blue", RGB(72, 61, 139),
   "dim gray", RGB(105, 105, 105),
   "dim grey", RGB(105, 105, 105),
   "forest green", RGB(34, 139, 34),
   "gold", RGB(255, 215, 0),
   "goldenrod", RGB(218, 165, 32),
   "gray", RGB(169, 169, 169),
   "grey", RGB(169, 169, 169),
   "green", RGB(0, 255, 0),
   "green yellow", RGB(173, 255, 47),
   "indian red", RGB(205, 92, 92),
   "khaki", RGB(240, 230, 140),
   "light blue", RGB(173, 216, 230),
   "light gray", RGB(211, 211, 211),
   "light grey", RGB(211, 211, 211),
   "lime green", RGB(50, 205, 50),
   "magenta", RGB(255, 0, 255),
   "maroon", RGB(128, 0, 0),
   "medium aquamarine", RGB(102, 205, 170),
   "medium blue", RGB(0, 0, 205),
   "medium goldenrod", RGB(234, 234, 173),
   "medium orchid", RGB(186, 85, 211),
   "orange", RGB(255, 165, 0),
   "pale green", RGB(152, 251, 152),
   "pink", RGB(255, 192, 203),
   "plum", RGB(221, 160, 221),
   "purple", RGB(128, 0, 128),
   "red", RGB(255, 0, 0),
   "salmon", RGB(250, 128, 114),
   "sienna", RGB(160, 82, 45),
   "sky blue", RGB(135, 206, 235),
   "slate blue", RGB(106, 90, 205),
   "tan", RGB(210, 180, 140),
   "thistle", RGB(216, 191, 216),
   "turquoise", RGB(64, 224, 208),
   "violet", RGB(238, 130, 238),
   "violet red", RGB(204, 50, 153),
   "wheat", RGB(245, 222, 179),
   "white", RGB(255, 255, 255),
   "yellow", RGB(255, 255, 0),
   "smoke", RGB(245, 245, 245),
   "white smoke", RGB(245, 245, 245),
   "floral white", RGB(255, 250, 240),
   "linen", RGB(250, 240, 230),
   "antique white", RGB(250, 235, 215),
   "ivory", RGB(255, 255, 240),
   "azure", RGB(240, 255, 255),
   "lavender", RGB(230, 230, 250),
   "light steel blue", RGB(176, 196, 222),
   "powder blue", RGB(176, 224, 230),
   "pale turquoise", RGB(175, 238, 238),
   "light cyan", RGB(224, 255, 255),
   "pale goldenrod", RGB(238, 232, 170),
   "light goldenrod yellow", RGB(250, 250, 210),
   "light yellow", RGB(255, 255, 224),
   "light goldenrod", RGB(238, 221, 130),
   "beige", RGB(245, 245, 220),
   "light pink", RGB(255, 182, 193),
   "extra light gray", RGB(229, 229, 229),
   "extra light grey", RGB(229, 229, 229)
};


int g2pvt_closebox = -1;           /* Enable=1, Disable=0, Default=-1 */
int g2pvt_minimize = 1;            /* Enable=1, Disable=0 */
int iNumColors;                    /* Number of colors in custom palette currently. */
int iNumStandardColors;            /* Number of colors in G2's standard set. */
BOOL ConfirmProgramExit = TRUE;


extern FILE *g2pvt_outstream;
extern int g2ext_max_number_of_sockets;
extern BOOL g2pvt_use_status_area_icon;

extern LONG WINAPI G2WndProc(HWND, unsigned, WORD, LONG);
extern void ne_initialize_event_handling(); /* ntevent.c */
extern BOOL init_window_globals();          /* windows.c */
extern void g2pvt_add_g2_status_icon (HANDLE);
LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WorkspaceViewWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK GensymMDIChildWndProc(HWND, UINT, WPARAM, LPARAM);

extern maybe_wait_for_return_key_type *g2ext_maybe_wait_for_return_key_fn;

extern char icon_name[];
extern int g2ext_product;

/*************************************************************************/
/* Window Classes                                                        */
/*************************************************************************/

/* Note that the TW ActiveX Control depends on GensymTelewindowClass, so it
 * should not change.  If it does ever need to change, the TW ActiveX Control
 * needs to be modified to know about the new class name, probably while still
 * recognizing the old name, which it is not presently set up to do.  */

LPCWSTR  GensymWindowClass         =  L"GensymClass";
LPCWSTR  GensymTelewindowClass     =  L"GensymTelewindowClass";
LPCWSTR  GensymFrameClass          =  L"GensymFrameClass";
LPCWSTR  GensymWorkspaceViewClass  =  L"GensymWorkspaceViewClass";
LPCWSTR  GensymMDIChildClass       =  L"GensymMDIChildClass";

static ATOM atom_GensymWindowClass;
static ATOM atom_GensymTelewindowClass;
static ATOM atom_GensymFrameClass;
static ATOM atom_GensymWorkspaceViewClass;
static ATOM atom_GensymMDIChildClass;


/*************************************************************************/
/* FUNCTIONS                                                             */
/*************************************************************************/

/*****************************************************************************
* BOOL g2pvt_window_has_info_slot_p (HWND hwnd)
*
*   Description: We need a quick predicate to determine whether a particular
*     window has the info slot we use for storing G2INFO structures.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL g2pvt_window_has_info_slot_p (HWND hwnd)
{
  ATOM atom = (ATOM) GetClassLong(hwnd,GCW_ATOM);
  return(atom == atom_GensymTelewindowClass ||
         atom == atom_GensymWorkspaceViewClass ||
         atom == atom_GensymFrameClass ||
         atom == atom_GensymWindowClass ||
	 atom == atom_GensymMDIChildClass);
}

BOOL g2pvt_tw_workspace_view_p (HWND hwnd)
{
  return ((ATOM)GetClassLong(hwnd,GCW_ATOM)) == atom_GensymWorkspaceViewClass;
}

/* TWNG uses a different window class for workspace views, so this function has
 * to be generic. */
#ifndef CODEJOCK
BOOL g2pvt_workspace_view_p (HWND hwnd)
{
  return g2pvt_tw_workspace_view_p(hwnd);
}
#endif

/***************************************************************************\

* void maybe_wait_for_return_key_internal()
*
*   Purpose:
*     If this is MS Windows, and there is no active logfile,
*     pause execution until the user presses a key.
*   Input Arguments: none
*   Returns: nothing
*   Comments:
*     All of msinits.c is MS Windows only.
*
*     G2/TW does not normally have standard input open, but
*     we have to have it open to see a return key. To be
*     safe, we open it here at the last possible moment.
*
*     This function is misnamed: it waits for any key to
*     be pressed, not just return.
*
*     Assumption: next action is to exit G2/TW.
\***************************************************************************/
static void maybe_wait_for_return_key_internal ()
{
  HANDLE hin;
  char buffer[4];
  DWORD numRead;

  if ((g2pvt_outstream == NULL) && ConfirmProgramExit) { /* logfile active? */
    hin = GetStdHandle(STD_INPUT_HANDLE);
    /* Note that ENABLE_LINE_INPUT is not listed, to enable single chars */
    SetConsoleMode(hin, ENABLE_ECHO_INPUT & ENABLE_PROCESSED_INPUT &
                   ENABLE_MOUSE_INPUT);
    printf("\nPress any key to end: ");
    /* wait for any key to be pressed */
    ReadFile(hin, &buffer, 1, &numRead, NULL);
  }
}


/*************************************************************************
*
*  BOOL init_winsock_api
*
*************************************************************************/
static BOOL init_winsock_api ()
{
#if defined(_WINSOCKAPI_)
  {
    WSADATA WSAStartupData;
    if (WSAStartup(MAKEWORD(1,1), &WSAStartupData) != 0) {
      printf("WINSOCK Startup Error.\n");
      return(FALSE);
    }
    g2ext_max_number_of_sockets = G2_MAX_SOCKETS_WIN32;
  }
#endif
  return(TRUE);
}


/*************************************************************************
*
*  BOOL register_window_classes
*
*************************************************************************/
static BOOL register_window_classes (HANDLE instance)
{
  WNDCLASSW wc;
  UINT basic_style = CS_BYTEALIGNWINDOW | CS_BYTEALIGNCLIENT | CS_DBLCLKS;
  HICON application_icon = NULL;
  HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
  HBRUSH background_brush = GetStockObject(LTGRAY_BRUSH);
  LPCWSTR menu_name = NULL;

  /* GENSYMCID-753: The -icon parameter has no effect in Windows */
  if (g2ext_product == TW_CMD && strlen(icon_name) > 0) {
    application_icon = LoadImage(instance, icon_name, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
  }
  if (application_icon == NULL) {
    application_icon = LoadIcon(instance, "g2");
  }

  wc.style = basic_style;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = WW_G2_S_EXTRA;
  wc.hInstance = instance;
  wc.hIcon = application_icon;
  wc.hCursor = cursor;
  wc.hbrBackground = background_brush;
  wc.lpszMenuName = menu_name;

  /* Note: this class is used just for the "event window" */
  wc.lpfnWndProc = (WNDPROC) G2WndProc;
  wc.lpszClassName = GensymWindowClass;
  if (!(atom_GensymWindowClass = RegisterClassW(&wc))) return(FALSE);

  /* For G2 and "classic UI" TW, we disable the close box.  We could instead
   * enable it but handle it so that it does not immediately kill the process.
   * If we want to do that, the place to handle it is in the WndProc in case
   * WM_SYSCOMMAND/SC_CLOSE.  We could put up a dialog box or something; maybe
   * totally disallow it for G2, but use a dialog box for TW.  For now, though
   * continue disabling the close box altogether.  - jv, 10/18/02
   */

  /* The -closebox option now controls the close button as follows:
   *   -closebox     G2/TW classic     TW standard/multiwindow
   *  -------------  -------------     -----------------------
   *  default (-1):    disable                enable
   *  enable  (1):     enable                 enable
   *  disable (0):     disable                disable
   *
   * Someday, G2 may be able to override TW's setting. -fmw, 2/24/04 */

  wc.style = basic_style | ((g2pvt_closebox == 1) ? 0 : CS_NOCLOSE);
  wc.lpfnWndProc = (WNDPROC) G2WndProc;
  wc.lpszClassName = GensymTelewindowClass; /* Note: this class is used for G2 and TW. */
  if (!(atom_GensymTelewindowClass = RegisterClassW(&wc))) return(FALSE);

  /* Restore the close box for the standard UI. */
  /* Turn off V/HREDRAW */
  wc.style = basic_style | ((g2pvt_closebox == 0) ? CS_NOCLOSE : 0);

  wc.lpfnWndProc = (WNDPROC)FrameWndProc;    /* Used for SDI and MDI modes. */
  wc.lpszClassName = GensymFrameClass;
  if (!(atom_GensymFrameClass = RegisterClassW(&wc))) return(FALSE);

  wc.style = basic_style;        /* Restore the closebox for workspace view windows. */
  wc.lpfnWndProc = (WNDPROC)WorkspaceViewWndProc;
  wc.lpszClassName = GensymWorkspaceViewClass;
  if (!(atom_GensymWorkspaceViewClass = RegisterClassW(&wc))) return(FALSE);

  wc.lpfnWndProc = (WNDPROC)GensymMDIChildWndProc; /* General purpose container. */
  wc.lpszClassName = GensymMDIChildClass;
  if (!(atom_GensymMDIChildClass = RegisterClassW(&wc))) return(FALSE);

  return(TRUE);
}


/*************************************************************************
*  BOOL g2pvt_win32_init (HANDLE instance)
*  Purpose:
*          First instance initialization.
*  Entry:
*          HANDLE instance - global DS selector for this program
*  Returns:
*           TRUE if successful.
*           FALSE otherwise.
*  Comments:
*************************************************************************/
BOOL g2pvt_win32_init (HANDLE instance)
{
  BOOL rc;
  BOOL rval;
  extern int ne_use_sck;

  ne_use_sck = FALSE;
  g2ext_maybe_wait_for_return_key_fn = maybe_wait_for_return_key_internal;

  if (!init_winsock_api())
    return(FALSE);
  ne_initialize_event_handling();

  rc = register_window_classes(instance);
  if (!rc)
    return(FALSE);

  InitCommonControls();
  /* Instance handle is needed when we create our window. Since this is
   *  done in g2ext_x11_initialize() we keep it as a global.
   */
  hInst = instance;

  rval = init_window_globals();
  if (g2pvt_use_status_area_icon) {
    g2pvt_add_g2_status_icon(instance);
  }
  return(rval);
}
