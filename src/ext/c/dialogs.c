/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      dialogs.c
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):
+   MS Windows portions:
+              2002 - 2003      fmw, mhd, jv; also code from Rector & Newcomer
+              2003 - 2005      jv, fmw, mhd, hjg, ajs, lkasparek
+
+ Description:  Implementation of native dialogs (and forms?) in Telewindows
+
+ Key:
+   (obsolete)
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
+   This file is only compiled on Microsoft Windows.  API functions have
+   corresponding stubs in windows.c.  There is no current plan to actually
+   provide this native functionality under X Windows.
+
+ Modifications:
+   usage: All modifications to this file should be listed here, with most
+          recent first. In general, modification comments should merely
+          provide a reference to a detailed modification comment in the
+          appropriate section/function header.
+
+   11/06/03,  jv: Created, initially from code committed to twpro.c in the
+                  past two years.
+
+   5/22/04,  mhd: file is now defined with UNICODE/_UNICODE preprocessor
+                  flags defined.  Functions are explicit, either narrow (char),
+                  or wide (wchar_t).
+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define UNICODE
#define _UNICODE



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
#include <windows.h>
#include <commdlg.h>          /* added for File dialogs. -mhd, 3/12/02 */

#include <tchar.h>            /* For _tcsicmp & friends */

#ifndef WINVER
#define WINVER 0x0400
#endif

#include <winver.h>           /* for GetFileVersionInfoSize & friends */

#include <windowsx.h>         /* WINDOWSX.H extensions */
#include <crtdbg.h>

#include <shlobj.h>
#include <assert.h>

#include "dyndlgs.h"
#include "ddrsc.h"

#include "msincls.h"
#include "cprim.h"
#include "graphics.h"
#include "messagebox.h"

/* The constants FONT_FOR_SIMPLE_DIALOG and FONT_SIZE_FOR_SIMPLE_DIALOG define
 * the font (typeface and size) for simple dialogs.  The font is MS Sans Serif,
 * size 8. This corresponds fairly will, though not necessarily perfectly, to
 * dialogs used for Windows programs. This was chosen because it is what's
 * generated in a dialog resource file you get when you create a standard dialog
 * box using Visual Studio resource editor.
 */
#define FONT_FOR_SIMPLE_DIALOG L"MS Sans Serif"
#define FONT_SIZE_FOR_SIMPLE_DIALOG 8


/* From Rector and Newcomer's code.
*/
#define IDC_ABOUT_PROCESSORVERSION      1006
#define IDC_ABOUT_FILEDESCRIPTION       1008
#define IDC_ABOUT_VERSION               1009
#define IDC_ABOUT_LEGALCOPYRIGHT        1010
#define IDC_ABOUT_LEGALTRADEMARKS       1011
#define IDC_ABOUT_COMMENTS              1012


#ifdef ECHO_DIALOG_SPEC
#  define STRUCTURE_FILENAME_ENV_VAR "G2_DIALOG_OUTPUT_FILE"
// Note special case texts are always wide strings
#  define G2_SPECIAL_CASE_1_TEXT L"..."
#  define G2_SPECIAL_CASE_1_REPLACEMENT_TEXT L"..@."
#endif



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

GENSYMDIALOG *list_of_dialogs = NULL;

static wchar_t dialog_text_result[1024];

/* A DIALOG_CREATION structure and encapsulates the state of (dynamic) win32
 * dialog creation. Code that uses this is all in this file.
 */
typedef struct
{
  DLGTEMPLATE *template;
  DLGITEMTEMPLATE *item;
} DIALOG_CREATION;


#ifdef ECHO_DIALOG_SPEC
static FILE *echo_dialog_file_handle = NULL;
static BOOL starting_echoing_dialog_p = TRUE;

extern LPWSTR g2pvt_get_component_parent_text(CONTROLITEM *);
extern LPWSTR g2pvt_get_component_text(CONTROLITEM *);
#endif


extern int g2pvt_get_icon_resource(int);
extern BOOL g2pvt_center_window(HWND, HWND);
extern char *g2pvt_get_last_error_string(void);
extern void g2pvt_position_dialog(HWND, long, long, BOOL, POINT*, enum G2DialogMonitorPreference); // NEW! (MHD 5/14/04)
extern long g2pvt_update_dialog(GENSYMDIALOG *, CONTROLITEM *, int);
extern long g2pvt_set_dialog_responses(GENSYMDIALOG *, int, int);
extern void g2pvt_set_dialog_title(GENSYMDIALOG *);
extern void g2pvt_set_dialog_background(GENSYMDIALOG *);
extern void g2pvt_set_component_parent_text(CONTROLITEM *, LPWSTR);
extern void g2pvt_set_component_text(CONTROLITEM *, LPWSTR);

extern int g2pvt_set_component_font (CONTROLITEM* , wchar_t * , long , wchar_t * ,wchar_t * , long , long );

extern void g2pvt_set_dialog_structure_title(GENSYMDIALOG *, LPWSTR);
extern void g2pvt_set_dialog_structure_backgroundColor(GENSYMDIALOG *, DIALOGINFO *, LPWSTR);

extern void g2pvt_display_OS_version_info(HWND);
extern HWND g2pvt_create_dialog(DIALOGINFO *);
extern LPWSTR g2pvt_updated_control_value(GENSYMDIALOG *, long);
#ifdef CODEJOCK
extern HWND g2pvt_create_dialogMFC (DIALOGINFO *dlgInfo, int handle);
#endif
extern void StoreNextEventEx(HWND, long, long, long, long, long, long, long, LPWSTR);
extern void g2pvt_init_resizable_child_dialogs(HWND hwndDlg, DIALOGINFO *dlgInfo);
extern void g2pvt_clear_text_box_extra_data (EXTRA_TEXTBX_DATA *pTBData);
extern UINT g2pvt_compute_gensym_mouse_keycode(UINT message);

// forward declarations
static void add_buddy_to_dialog (long, long, long, LPWSTR,
				 long, long, long, long, long, long, long);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP - Rector & Newcomer Dialogs
%
% Description:
%
% Notes:
%   Dynamic Dialogs -- Dialogs in Windows created on the fly, not from resource
%   files. The first part of this code is taken from the sources supplied with
%   the Win32 Programming book as pizza/dlgtemplate.c by authors Rector and
%   Newcomer for unrestricted use.  The second is a basic application: creating
%   an about box. This is customized for TW Pro, but is based on the code in
%   pizza/AboutBox.c.  Other relevant files taken from the same source are
%   dlgtemplate.h, Extensions.h, and Utility.h. This is for Windows only, and
%   there are no plans at present to implement any comparable facility for
%   X. The commentary and explanation in that book are integral to this code,
%   and vital to understanding it.
%
% Modifications:
%   usage: Modifications in this header should be restricted to mentioning
%      the addition or deletion of functions within this section. Actual
%      function changes should be commented in the specific function's
%      header.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* __inline LPWORD appendString(LPWORD ptr, LPCWSTR text)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
__inline LPWORD appendString(LPWORD ptr, LPCWSTR text)
{
  LPWSTR str = (LPWSTR)ptr;
  wcscpy(str, text);
  ptr = (LPWORD)(str + wcslen(str) + 1);
  return ptr;
}


/*****************************************************************************
* __inline LPWORD SetClassName(DLGITEMTEMPLATE *item, LPCWSTR classname)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
__inline LPWORD SetClassName(DLGITEMTEMPLATE *item, LPCWSTR classname)
{
  LPWORD ptr = (LPWORD)&item[1];
  ptr = appendString(ptr, classname);
  return ptr;
}


/*****************************************************************************
* __inline LPWORD setResourceID(LPWORD ptr, short id)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
__inline LPWORD setResourceID(LPWORD ptr, short id)
{
  *ptr++ = 0xFFFF;
  *ptr++ = (WORD)id;
  return ptr;
}


/****************************************************************************
* __inline LPWORD noParms(DLGITEMTEMPLATE *item, LPWORD ptr)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
__inline LPWORD noParms(DLGITEMTEMPLATE *item, LPWORD ptr)
{
  *ptr++ = 0;   // no parameters

  if ( (((LPWORD)item) - ptr) & 1)
    *ptr++ = 0;

  return ptr;
}


/*****************************************************************************
* __inline void setItemPos(DLGITEMTEMPLATE *item, int x, int y, int cx, int cy)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
__inline void setItemPos(DLGITEMTEMPLATE *item, int x, int y, int cx, int cy)
{
  item->x = x;
  item->y = y;
  item->cx = cx;
  item->cy = cy;
}


/*****************************************************************************
* DLGITEMTEMPLATE *rector_newcomer_control(DLGITEMTEMPLATE *, LPCWSTR, short,
*                                          LPCWSTR, DWORD, int, int, int, int,
*                                          DWORD)
*
*   Description:
*
*   Input Arguments:
*
*   Returns:
*
*   Notes:
*
*
*     -----
*   Modifications:
*****************************************************************************/
static DLGITEMTEMPLATE *rector_newcomer_control(DLGITEMTEMPLATE *item, LPCWSTR text,
						short id, LPCWSTR classname,
						DWORD style,
						int x, int y, int cx, int cy,
						DWORD exstyle)
{
  LPWORD ptr = (LPWORD) &item[1];

  item->style = WS_CHILD | style;
  item->dwExtendedStyle = exstyle;
  setItemPos(item, x, y, cx, cy);
  item->id = (WORD)id;

  if (HIWORD(classname) != 0)
    ptr = SetClassName(item, classname);
  else
    ptr = setResourceID(ptr, LOWORD(classname)); // MAKEINTRESOURCEW(class)

  if (text == 0)
    ptr = appendString(ptr, L"");
  else
    if (HIWORD(text) != 0)
      ptr = appendString(ptr, text);
    else
      ptr = setResourceID(ptr, LOWORD(text));  // MAKEINTRESOURCEW(id)

    ptr = noParms(item, ptr);

    return (DLGITEMTEMPLATE *)ptr;
}

/* Provide public access. */
DLGITEMTEMPLATE *g2pvt_add_control_to_dialog_template(DLGITEMTEMPLATE *item, LPCWSTR text,
						      int id, LPCWSTR classname,
						      DWORD style,
						      int x, int y, int cx, int cy,
						      DWORD exstyle)
{
  return rector_newcomer_control(item,text,(short)id,classname,style,x,y,cx,cy,exstyle);
}

/*****************************************************************************
* DLGITEMTEMPLATE *g2pvt_create_autocheckbox(DLGITEMTEMPLATE *item, LPCWSTR text,
*                                            short id, int x, int y, int cx, int cy,
*                                            DWORD style, DWORD exstyle)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
DLGITEMTEMPLATE *g2pvt_create_autocheckbox(DLGITEMTEMPLATE *item, LPCWSTR text,
                                           short id, int x, int y, int cx, int cy,
                                           DWORD style, DWORD exstyle)
{
  return rector_newcomer_control(item, text, id, MAKEINTRESOURCEW(0x0080),
    style | BS_AUTOCHECKBOX,
    x, y, cx, cy,
    exstyle);
}


/*****************************************************************************
* DLGITEMTEMPLATE *g2pvt_create_combobox(DLGITEMTEMPLATE *item, short id,
*                                        int x, int y, int cx, int cy, DWORD style,
*                                        DWORD exstyle)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
DLGITEMTEMPLATE *g2pvt_create_combobox(DLGITEMTEMPLATE *item, short id,
                                       int x, int y, int cx, int cy, DWORD style,
                                       DWORD exstyle)
{

  return rector_newcomer_control(item, L"", id, MAKEINTRESOURCEW(0x0085),
    style,
    x, y, cx, cy,
    exstyle);

}


/*****************************************************************************
* DLGITEMTEMPLATE *g2pvt_create_ltext(DLGITEMTEMPLATE *item, LPCWSTR text, short id,
*                                     int x, int y, int cx, int cy, DWORD style,
*                                     DWORD exstyle)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
DLGITEMTEMPLATE *g2pvt_create_ltext(DLGITEMTEMPLATE *item, LPCWSTR text, short id,
                                    int x, int y, int cx, int cy, DWORD style,
                                    DWORD exstyle)
{

  return rector_newcomer_control(item, text, id,  MAKEINTRESOURCEW(0x0082),
    SS_LEFT | style,
    x, y, cx, cy,
    exstyle);
}


/*****************************************************************************
* DLGITEMTEMPLATE *rector_edittext(DLGITEMTEMPLATE *item, short id,
*                                  int x, int y, int cx, int cy, DWORD style,
*                                  DWORD exstyle)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static DLGITEMTEMPLATE *rector_edittext(DLGITEMTEMPLATE *item, short id,
                                 int x, int y, int cx, int cy, DWORD style,
                                 DWORD exstyle)
{

  return rector_newcomer_control(item, L"", id, MAKEINTRESOURCEW(0x0081),
    style,
    x, y, cx, cy,
    exstyle);

}


/*****************************************************************************
* DLGITEMTEMPLATE *rector_icon(DLGITEMTEMPLATE *item, LPCWSTR icon,
*                              short id, int x, int y, int cx, int cy,
*                              DWORD style, DWORD exstyle)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static DLGITEMTEMPLATE *rector_icon(DLGITEMTEMPLATE *item, LPCWSTR icon,
                             short id, int x, int y, int cx, int cy,
                             DWORD style, DWORD exstyle)
{
  return rector_newcomer_control(item, icon, id, MAKEINTRESOURCEW(0x0082),
    SS_ICON | style,
    x, y, cx, cy,
    exstyle);
}


/*****************************************************************************
* DLGITEMTEMPLATE *rector_rtext(DLGITEMTEMPLATE *item, LPCWSTR text, short id,
*                               int x, int y, int cx, int cy, DWORD style,
*                               DWORD exstyle)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static DLGITEMTEMPLATE *rector_rtext(DLGITEMTEMPLATE *item, LPCWSTR text, short id,
                              int x, int y, int cx, int cy, DWORD style,
                              DWORD exstyle)
{

  return rector_newcomer_control(item, text, id, MAKEINTRESOURCEW(0x0082),
    SS_RIGHT | style,
    x, y, cx, cy,
    exstyle);

}


/*****************************************************************************
* DLGITEMTEMPLATE *rector_pbutton(DLGITEMTEMPLATE *item, LPCWSTR text,
*                                 short id, int x, int y, int cx, int cy,
*                                 DWORD style, DWORD exstyle)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static DLGITEMTEMPLATE *rector_pbutton(DLGITEMTEMPLATE *item, LPCWSTR text,
                                   short id, int x, int y, int cx, int cy,
                                   DWORD style, DWORD exstyle)
{
  return rector_newcomer_control(item, text, id, MAKEINTRESOURCEW(0x0080),
    style | BS_PUSHBUTTON,
    x, y, cx, cy,
    exstyle);
}


/*****************************************************************************
* DLGITEMTEMPLATE *rector_dpbutton(DLGITEMTEMPLATE *item, LPCWSTR text,
*                                  short id, int x, int y, int cx, int cy,
*                                  DWORD style, DWORD exstyle)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static DLGITEMTEMPLATE *rector_dpbutton(DLGITEMTEMPLATE *item, LPCWSTR text,
                                      short id, int x, int y, int cx, int cy,
                                      DWORD style, DWORD exstyle)
{
  return rector_newcomer_control(item, text, id, MAKEINTRESOURCEW(0x0080),
    style | BS_DEFPUSHBUTTON,
    x, y, cx, cy,
    exstyle);
}



/*****************************************************************************
* void aboutDlg_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
*
*   Description:
*       Handle the keyboard and control notifications.  An OK button press, or
*       Enter/Esc keypress all dismiss the About dialog box.
*
*   Input Arguments:
*     hwnd            Window handle for the dialog box window
*     id              Specifies the identifier of the menu item, control, or
*                     accelerator.
*     hwndCtl         Handle of the control sending the message if the message
*                     is from a control, otherwise, this parameter is NULL.
*     codeNotify      Specifies the notification code if the message is from a
*                     control. This parameter is 1 when the message is from an
*                     accelerator. This parameter is 0 when the message is from
*                     a menu.
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void aboutDlg_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id) {
  case IDOK:                       // OK pushbutton/Enter keypress
  case IDCANCEL:                   // Esc keypress
    EndDialog (hwnd, TRUE);        // Dismiss the about dialog box
    break;

  default:
    FORWARD_WM_COMMAND (hwnd, id, hwndCtl, codeNotify, DefWindowProc);
  }
}


/*****************************************************************************
* BOOL aboutDlg_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam)
*
*   Description:
*     Initializes all the controls by extracting information from the
*     VERSIONINFO structure
*   Input Arguments:
*     hwnd            Window handle for the dialog box window
*     hwndFocus       Handle of the control which will get the initial focus
*     lParam          Parameter to DialogBoxParam (not used for About dialog)
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL aboutDlg_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
  g2pvt_center_window(hwnd, hwndCoor);
  g2pvt_display_OS_version_info(hwnd);
  return TRUE;
}


/*****************************************************************************
* BOOL CALLBACK aboutDlgProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
*
*   Description:
*     Dialog function for the About dialog box.  Display version information for
*     the application, the operating system, and the processor.
*
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL CALLBACK aboutDlgProc (HWND hwnd, UINT message,
                                   WPARAM wParam, LPARAM lParam)
{
  switch (message) {

  case WM_INITDIALOG:            // Initialization of controls complete
    return HANDLE_WM_INITDIALOG (hwnd, wParam, lParam, aboutDlg_OnInitDialog);

  case WM_COMMAND:               // Notification from a control
    return HANDLE_WM_COMMAND (hwnd, wParam, lParam, aboutDlg_OnCommand);
  }
  return FALSE;
}


/*****************************************************************************
* void simpleDlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
*
*   Description: subfunctions of simpleDlgProc(), which is used to handle
*     Windows messages while a simple dialog is being presented to the user.
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void simpleDlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
  switch (id)
  {
  case IDC_ADDITIONAL:
  case IDC_OK:
  case IDOK:
  case IDC_CANCEL:
  case IDCANCEL:
  case IDRETRY:
  case IDYES:
  case IDNO:
  case IDABORT:
  case IDIGNORE:
  case IDCLOSE:
    /* Save the text, if any. */
    dialog_text_result[0] = L'\0';
    GetDlgItemTextW(hwnd, IDC_TEXT, dialog_text_result,
      sizeof(dialog_text_result)/sizeof(wchar_t) - 1);
    EndDialog(hwnd, id);          /* Dismiss the simple dialog box, return id */
    break;

  default:
    FORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, DefWindowProc);
  }
}


/*****************************************************************************
* BOOL simpleDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL CALLBACK simpleDlgProc(HWND hwnd, UINT message,
                                   WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_INITDIALOG:            /* Initialization of controls complete */
    g2pvt_center_window(hwnd, hwndCoor);
    return 1;

  case WM_COMMAND:               /* Notification from a control */
    return HANDLE_WM_COMMAND(hwnd, wParam, lParam, simpleDlg_OnCommand);
  }
  return FALSE;
}


/*****************************************************************************
* int get_icon_mb_style(int icon)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static int get_icon_mb_style(int icon)
{
  switch(icon)
  {
  case 0: return MB_ICONQUESTION;
  case 1: return MB_ICONINFORMATION;
  case 2: return MB_ICONWARNING;
  case 3: return MB_ICONERROR;
  default:return MB_ICONQUESTION;
  }
}


/*****************************************************************************
 * DLGTEMPLATE *g2pvt_dialog_template (DLGITEMTEMPLATE **item, UINT size,
 *                                            int x, int y, int cx, int cy,
 *                                            DWORD style, DWORD exstyle,
 *                                            LPCWSTR menu, LPCWSTR class,
 *                                            LPCWSTR caption, LPCWSTR font,
 *                                            int height)
 *
 *   Description:
 *       Allocates and initializes a DLGTEMPLATE structure
 *   Input Arguments:
 *       DLGITEMTEMPLATE ** item: On successful return, will be a pointer
 *                       to the first place a DLGITEMTEMPLATE can be set
 *       UINT size: Buffer size to allocate.  If 0, a default value of
 *                       4096 is used.
 *       int x: Origin of top left corner
 *       int y: Origin of top left corner
 *       int cx: Width in dialog units
 *       int cy: Height in dialog units
 *       DWORD style: Style bits
 *       DWORD exstyle: Extended style bits
 *       LPCWSTR menu:   NULL if no menu
 *                       MAKEINTRESOURCEW(menuid) if by resource id
 *                       L"menuname" for string menu
 *       LPCWSTR class:  NULL if no class (default dialog box class)
 *                       MAKEINTRESOURCEW(atom) if atom of class given
 *                       L"classname" if class name of class given
 *       LPCWSTR caption:NULL if no caption
 *                       L"caption" if present
 *       LPCWSTR font:   NULL if no font given (DS_SETFONT will be removed
 *                               from styles)
 *                       L"font" if font specified (DS_SETFONT will be added)
 *       int height:     Font height in points (ignored if font is NULL)
 *   Returns: DLGTEMPLATE *
 *       A dialog template, or NULL if an error occurred
 *   Notes:
 *       The caller must call free() to release the template
 *       The cdit field will be set to 0; it is the caller's responsibility
 *       to increment this field each time a control is added
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
DLGTEMPLATE *g2pvt_dialog_template (DLGITEMTEMPLATE **item, UINT size,
                                    int x, int y, int cx, int cy,
                                    DWORD style, DWORD exstyle,
                                    LPCWSTR menu, LPCWSTR class,
                                    LPCWSTR caption, LPCWSTR font,
                                    int height)
{
  DLGTEMPLATE *dlg;
  LPWORD ptr;

  if (size == 0)
    size = DLGTEMPLATE_WORKING_SIZE;
  dlg = (DLGTEMPLATE *) malloc(size);
  if (dlg == NULL)
    return NULL;

  dlg->x = x;
  dlg->y = y;
  dlg->cx = cx;
  dlg->cy = cy;

  dlg->cdit = 0;  // no dialog items yet

  dlg->style = style;
  if (font == NULL)
    dlg->style &= ~DS_SETFONT;
  else
    dlg->style |= DS_SETFONT;

  dlg->dwExtendedStyle = exstyle;

  ptr = (LPWORD) &dlg[1];

  if (menu == NULL)
    *ptr++ = 0;     // no menu
  else
    if (HIWORD(menu) == 0)
      ptr = setResourceID(ptr, LOWORD(menu)); // MAKEINTRESOURCEW
    else
      ptr = appendString(ptr, menu);


  if (class == NULL)
    *ptr++ = 0;
  else
    if (HIWORD(class) == 0)
      ptr = setResourceID(ptr, LOWORD(class)); // MAKEINTRESOURCEW
    else
      ptr = appendString(ptr, class);

  ptr = appendString(ptr, (caption == NULL ? L"" : caption));

  if (font != NULL)
    { /* has font */
      *ptr++ = height;
      ptr = appendString(ptr, font);
    } /* has font */

  /* Now DWORD align ptr, which is already WORD aligned. */
  if (((ULONG)ptr)&2) ptr++;

  if (item != NULL)
    *item = (DLGITEMTEMPLATE *) ptr;

  return (DLGTEMPLATE *)dlg;
}


/*****************************************************************************
* DLGTEMPLATE *makeAboutBoxTemplate (LPCWSTR version, LPCWSTR comments)
*
*   Description:
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static DLGTEMPLATE *makeAboutBoxTemplate (LPCWSTR version, LPCWSTR comments)
{
  DLGTEMPLATE *templ;
  DLGITEMTEMPLATE *item;

  templ = g2pvt_dialog_template(&item, DLGTEMPLATE_WORKING_SIZE,
    22, 17, 204, 83,
    DS_MODALFRAME | WS_POPUP |
    WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
    0,
    NULL,                 // menu
    NULL,                 // class
    L"About Telewindows", // caption
    L"System",            // font
    8);                   // font height

  if (templ == NULL)
    return NULL;

  templ->cdit++;
  item = rector_dpbutton(item, L"OK", IDOK, 166, 63, 32, 14,
    WS_GROUP | WS_TABSTOP | WS_VISIBLE, 0);

  templ->cdit++;
  item = rector_icon(item, L"g2",
                     /* This is the TW icons for TW. originally -
                        MAKEINTRESOURCEW(IDR_MAINFRAME) */
                     IDC_STATIC, 3, 2, 18, 20,
                     WS_VISIBLE, 0);
  templ->cdit++;
  item = g2pvt_create_ltext(item, L"Telewindows", IDC_ABOUT_FILEDESCRIPTION,
    30, 2, 118, 8, WS_VISIBLE, 0);
  templ->cdit++;
  item = rector_rtext(item, version, IDC_ABOUT_VERSION,
    75, 2, 120, 8, WS_VISIBLE, 0);

  templ->cdit++;
  item = g2pvt_create_ltext(item, L"\251 2012 Gensym Corp.  All Rights Reserved.",
    IDC_ABOUT_LEGALCOPYRIGHT, 30, 10, 168, 16,
    WS_VISIBLE, 0);

  templ->cdit++;
  item = g2pvt_create_ltext(item, comments, IDC_ABOUT_COMMENTS, 30, 26, 168, 8,
    WS_VISIBLE, 0);
  templ->cdit++;
  item = rector_newcomer_control(item, L"", IDC_STATIC, L"Static",
    SS_BLACKRECT | WS_VISIBLE,
    2, 39, 200, 1, 0);

  templ->cdit++;
  item = g2pvt_create_ltext(item, L"OSVERSION", IDC_ABOUT_OSVERSION,
    4, 42, 196, 8, WS_VISIBLE, 0);

  templ->cdit++;
  item = g2pvt_create_ltext(item, L"", IDC_ABOUT_PROCESSORVERSION,
    /* skip this info for now. -mhd */
    4, 50, 196, 8, WS_VISIBLE, 0);

  templ->cdit++;
  item = rector_newcomer_control(item, L"", IDC_STATIC, L"Static",
    SS_BLACKRECT | WS_VISIBLE,
    2, 60, 200, 1, 0);

  templ->cdit++;
  item = g2pvt_create_ltext(item, L"Telewindows is a Trademark of Gensym Corp.",
    IDC_ABOUT_LEGALTRADEMARKS,
    3, 65, 156, 18, WS_VISIBLE, 0);
  return templ;
}


/*****************************************************************************
* long g2ext_about_box(long window_index, LPCWSTR version, LPCWSTR comments)
*
*   Description: Display Telewindows about box, with version info.
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_about_box(long window_index, LPCWSTR version, LPCWSTR comments)
{
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  HINSTANCE hinst = GetWindowInstance(hwnd);
  DLGTEMPLATE *temp = makeAboutBoxTemplate(version,comments);

  if (temp == NULL)
    return -1;

  g2pvt_enter_modal_loop();
  DialogBoxIndirect(hinst, temp, hwnd, (DLGPROC) aboutDlgProc);
  g2pvt_exit_modal_loop();
  free(temp);
  return 1;
}



/*****************************************************************************
* long g2pvt_simple_dialog (HWND hwnd, LPCWSTR title, LPCWSTR message_string,
*                           LPCWSTR ok_string, long ok_id,
*                           LPCWSTR cancel_string, long cancel_id,
*                           LPCWSTR additional_string, long additional_id,
*                           long id_of_default)
*
*   Description:
*
*   Input Arguments:
*     Arguments title, message_string, ok_string, cancel_string and additional_
*     string should be Unicode strings, i.e., wide strings.  I.e., if expressed
*     as string constants in C, the quotes should be preceeded L, e.g.,
*     L"Unicode Text".
*
*     Any of the ..._id arguments should be zero to indicate no button of this
*     type should be presented. In this case _string argument is ignored; in
*     this case, it should be the empty string (L"") by convention.
*
*     id_of_default should match the one of ok_id, cancel_id, or additional_id
*     that should be a default button. If none should a default button, this can
*     be anything other than one of those, by convention zero in this case.
*
*   Returns: 
*   Notes:
*      If this can catch a case of the dialog being cancelled (or aborted) for
*      any reason -- usually it can -- then cancel_id is returned.  Note in
*      particular that the case of the user cancelling by clicking the close box
*      or typing the ESC key is caught in this way.
*
*      To do: if we wish to support the center over mouse feature in G2, we can
*      use the dialog style DS_CENTERMOUSE rather than doing this ourselves by
*      hand. Review callers that need this, if any!
*     -----
*   Modifications:
*****************************************************************************/
static HHOOK g_cbtHook;
static LPCWSTR g_okString;
static LPCWSTR g_cancelString;
static LPCWSTR g_additionalString;

static LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
  HWND hwndDlg;

  if(g_cbtHook == NULL)
    return 0;

  if(nCode != HCBT_ACTIVATE)
    return CallNextHookEx(g_cbtHook, nCode, wParam, lParam);

  UnhookWindowsHookEx(g_cbtHook);
  hwndDlg = (HWND)wParam;

  if(g_okString) {
    if(GetDlgItem(hwndDlg, IDOK))
      SetWindowTextW(GetDlgItem(hwndDlg, IDOK), g_okString);
    else if(GetDlgItem(hwndDlg, IDYES))
      SetWindowTextW(GetDlgItem(hwndDlg, IDYES), g_okString);
  }

  if(g_cancelString)
    SetWindowTextW(GetDlgItem(hwndDlg, IDCANCEL), g_cancelString);

  if(g_additionalString)
    SetWindowTextW(GetDlgItem(hwndDlg, IDNO), g_additionalString);

  return 0;
}

long g2pvt_simple_dialog(HWND hwnd, LPCWSTR title, LPCWSTR message_string,
                         LPCWSTR ok_string, long ok_id,
                         LPCWSTR cancel_string, long cancel_id,
                         LPCWSTR additional_string, long additional_id,
                         long id_of_default)
{
  UINT type = 0;
  int result;

  if(ok_id && cancel_id & additional_id) /* Additional button only allowed if have all three */
    type = MB_YESNOCANCEL;
  else if(ok_id && cancel_id)
    type = MB_OKCANCEL;
  else if(cancel_id) {                /* A cancel-only dialog. */
    type = MB_OK;
    ok_id = cancel_id;
    ok_string = cancel_string;
    cancel_string = NULL;
  }
  else
    type = MB_OK;

  if(id_of_default == ok_id || id_of_default == 0)
    type |= MB_DEFBUTTON1;
  else if (id_of_default == additional_id) /* The "additional" button, if present, */
    type |= MB_DEFBUTTON2;                 /* is the middle of three */
  else if(id_of_default == cancel_id)
    type |= additional_id ? MB_DEFBUTTON3 : MB_DEFBUTTON2;
    
  type |= MB_ICONQUESTION;

  if(ok_id) g_okString = ok_string;
  if(cancel_id) g_cancelString = cancel_string;
  if(additional_id) g_additionalString = additional_string;

  g_cbtHook = SetWindowsHookEx(WH_CBT, CBTProc, NULL, GetCurrentThreadId());

  g2pvt_enter_modal_loop();
//Cage modified 
  //result = MessageBoxW(hwndFrame, message_string, title, type);
  result = MessageBoxW(hwndFrame, message_string, title, type);
//Cage__
  g2pvt_exit_modal_loop();

  g_cbtHook = (HHOOK)0;
  g_okString = g_cancelString = g_additionalString = NULL;

  switch(result) {
   case IDOK: case IDYES:
     return ok_id;
   case IDNO:
     return additional_id;
   default:
     return cancel_id;
  }
}


/*****************************************************************************
* long g2ext_simple_dialog(long window_index, LPCWSTR caption,
*                          LPCWSTR message_string,
*                          LPCWSTR ok_string, long ok_id,
*                          LPCWSTR cancel_string, long cancel_id,
*                          LPCWSTR additional_string, long additional_id,
*                          long id_of_default)
*
*   Description: creates a simple dialog from Lisp.  A small wrapper around
*     g2pvt_simple_dialog, above (qv).
*
*   Input Arguments:
*     window_index is a handle, previously obtained as the result of a call to
*     g2ext_cache_cpointer.  This is because Lisp doesn't hold on to pointers
*     well.  We use this to get the HWND.  This function also supports empty
*     "captions", unlike the g2pvt_ version.
*
*   Returns: 
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_simple_dialog(long window_index, LPCWSTR caption, LPCWSTR message_string,
                         LPCWSTR ok_string, long ok_id,
                         LPCWSTR cancel_string, long cancel_id,
                         LPCWSTR additional_string, long additional_id,
                         long id_of_default)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  LPCWSTR title = (wcslen(caption) == 0) ? L"G2" : caption;

  return g2pvt_simple_dialog(hwnd, title, message_string,
                             ok_string, ok_id, cancel_string, cancel_id,
                             additional_string, additional_id, id_of_default);
}

//jin

long g2ext_get_sys_drives_list_as_string(LPWSTR strDrives, long buflen)
{
  char *pszDrive = NULL;
  char *tok      = NULL;
  int ind        = 0;

  GetLogicalDriveStringsW(buflen, strDrives);

  return 0;
}

long g2ext_get_system_special_folders(LPWSTR strSpecialFolders, long buflen)
{
  WCHAR wcsPath[MAX_PATH];
  LPWSTR wcs_ptr;
  #define SPECIAL_FOLDERS_SIZE 5
  int SpecialFolders[SPECIAL_FOLDERS_SIZE] = { CSIDL_RECENT, CSIDL_DESKTOPDIRECTORY, CSIDL_PERSONAL, CSIDL_DRIVES, CSIDL_NETHOOD };
  int ind = 0;

  wcs_ptr = strSpecialFolders;
  for ( ind = 0; ind < SPECIAL_FOLDERS_SIZE; ++ind ) {
    if (SHGetSpecialFolderPathW( 0, wcsPath, SpecialFolders[ind], FALSE )) {
      wcscat(wcsPath, L"\\");
      wcscpy(wcs_ptr, wcsPath);
      wcs_ptr += wcslen(wcsPath)+1;
    } else {
      wcscpy(wcsPath, L"C:\\");
      wcscpy(wcs_ptr, wcsPath);
      wcs_ptr += wcslen(wcsPath)+1;
    }
  }
  *wcs_ptr++ = L'\0';

  return 0;
}

static int get_icon_mb_user_style(int icon)
{
  switch(icon)
  {
  case 0: return IDI_MBU_QUESTION;
  case 1: return IDI_MBU_INFO;
  case 2: return IDI_MBU_WARNING;
  case 3: return IDI_MBU_ERROR;
  default:return IDI_MBU_QUESTION;
  }
}

/*****************************************************************************
* long g2ext_message_box (long window_index, LPCWSTR caption, LPCWSTR message,
*                         long style, long icon)
*
*   Description:
*     Post a Win32 MessageBox, and return the choice as a G2 response code.
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_message_box (long window_index, LPCWSTR caption, LPCWSTR message,
                        long style, long icon)
{
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  int result;

  style |= get_icon_mb_style(icon);

  g2pvt_enter_modal_loop();
  result = MessageBoxW(hwndFrame, message, caption, style);
  g2pvt_exit_modal_loop();

  return result;
}


/*****************************************************************************
* long g2ext_query_box(long window_index, LPCWSTR caption, LPCWSTR message,
*                      long fontSize, long icon, LPWSTR response, long buflen)
*
*   Description:
*     Posts a modal dialog with a message, icon, and edit box and returns the
*     entered string. Return value is 1 on success, 0 on cancel, -1 on error.
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_query_box(long window_index, LPCWSTR caption, LPCWSTR message,
                     long fontSize, long icon, LPWSTR response, long buflen)
{
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  DLGTEMPLATE *template;
  DLGITEMTEMPLATE *item = NULL;
  int nlines, x, y, width, height, result, cx, cy, dx, dy;
  ULONG units = GetDialogBaseUnits();
  int px = LOWORD(units);        /* pixels = (px * dx) / 4 */
  int py = HIWORD(units);        /* pixels = (py * dy) / 8 */
  int msgWidth = 30 * 4;
  int editWidth, iconRes;
  const wchar_t *ch;

  if (fontSize <= 0)
    fontSize = 8;                /* Default font size. */

  iconRes = g2pvt_get_icon_resource(icon);

  /* Dialog units: x dimension is 4 units per char width.
  y is 8 units per line height. */
  cx = 32;                        /* Icon size in pixels. */
  cy = 32;
  dx = (cx*4)/px;                /* Icon size in dialog units. */
  dy = (cy*8)/py;

  nlines=1;
  for(ch=message; *ch; ch++)
    if (*ch == L'\n')
      nlines++;

      /* icon text
      edit
      ---sep---
    OK Cancel */

    width = 8 + dx + 12 + msgWidth + 2;
    height = 2 +  MAX(dy,nlines*8) + 8  + 12+8  + 8 + 14 + 4;

    template = g2pvt_dialog_template(&item, DLGTEMPLATE_WORKING_SIZE,
      0, 0, width, height,
      DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
      0, NULL, NULL, caption,
      FULL_UNICODE_FONTW, fontSize);

    if (template == NULL) {
      printf("g2ext_query_box: can't create dialog for %S\n", caption);
      return -1;
    }

    x = 8;                        /* In dialog units */
    y = 2;
    template->cdit++;
    item = rector_icon(item, (LPCWSTR)iconRes, IDC_STATIC, x, y, dx, dy,
                       WS_VISIBLE, 0);
    x += dx + 12;
    template->cdit++;
    item = g2pvt_create_ltext(item, message, IDC_STATIC, x, y, msgWidth,
      8*nlines, WS_VISIBLE, 0);

    editWidth = width - 16;
    x = (width - editWidth)/2;
    y += MAX(dy,nlines*8) + 8;
    template->cdit++;
    item = rector_edittext(item, IDC_TEXT, x, y, editWidth, 12,
      WS_VISIBLE|WS_TABSTOP|ES_AUTOHSCROLL, WS_EX_CLIENTEDGE);

    x = 2;
    y += 12 + 8;
    template->cdit++;
    item = rector_newcomer_control(item, L"", IDC_STATIC, L"Static",
      SS_SUNKEN | WS_VISIBLE,
      x, y, width-4, 1, 0);

    x = (width - (2*50 + 20))/2;
    y += 8;
    template->cdit++;
    item = rector_dpbutton(item, L"OK", IDOK, x, y, 50, 14, WS_TABSTOP|WS_VISIBLE,0);

    x = width - x - 50;
    template->cdit++;
    item = rector_pbutton(item, L"Cancel", IDCANCEL, x, y, 50, 14,
      WS_TABSTOP|WS_VISIBLE,0);

    dialog_text_result[0] = L'\0';
    g2pvt_enter_modal_loop();
    result = DialogBoxIndirectW(hInst, template, hwnd, (DLGPROC) simpleDlgProc);
    g2pvt_exit_modal_loop();

    if (result == -1)
      fprintf(stderr,"g2ext_query_box failed: %s\n", g2pvt_get_last_error_string());
    else
      wcsncpy(response, dialog_text_result, buflen-1);

    response[buflen-1] = '\0';
    free(template);
    return result;
}




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP - Dynamic Dialogs Basics & Debugging
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

/*****************************************************************************
* BOOL g2pvt_is_dialog_message (MSG *pMsg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL g2pvt_is_dialog_message (MSG *pMsg)
{
  GENSYMDIALOG *dialog;

  for (dialog=list_of_dialogs;
  dialog != NULL;
  dialog = dialog->next) {

    // We should not call IsDialogMessage for modal dialogs; however, our kind
    // of modal dialogs are not truly modal.  We create a window, and disable
    // the parent window, and may do some other stuff too, but we don't actually
    // use the DialogBox() API function; so we need to call IsDialogMessage for
    // all active dynamic dialogs.  -jv, 5/27/04
    // if ((dialog->_iDlgType != MODAL)
    if (IsDialogMessage(dialog->hwnd, pMsg)) {
      return TRUE;
    }
  }
  return FALSE;
}


/*****************************************************************************
*   GENSYMDIALOG *g2pvt_find_dialog_by_id (long)
*
*   Description:
*     Find a dialog structure given the dialog id
*   Input Arguments:
*     The dialog id of the dialog
*   Returns:
*     A pointer to a GENSYMDIALOG
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
GENSYMDIALOG *g2pvt_find_dialog_by_id (long dlgId)
{
  return (GENSYMDIALOG *) g2ext_map_g2pointer_to_cpointer(dlgId);
}

/* Return the GENSYMDIALOG structure, given the G2 id (== native-view handle) */
GENSYMDIALOG *g2pvt_find_dialog(int g2_id)
{
  GENSYMDIALOG *pDlg;

  for (pDlg=list_of_dialogs; pDlg; pDlg=pDlg->next)
    if(pDlg->g2_id == g2_id)
      return pDlg;
  return NULL;
}

/* Return the HWND for dialog with given G2-assigned handle, or NULL if none. */
HWND g2pvt_find_dialog_hwnd_by_handle (int g2_id)
{
  GENSYMDIALOG *pDlg = g2pvt_find_dialog(g2_id);
  return pDlg ? pDlg->hwnd : NULL;
}


/*****************************************************************************
*   CONTROLITEM *g2pvt_find_control_by_id (GENSYMDIALOG *, long)
*
*   Description:
*     Find a control structure given a dialog and a control id.
*   Input Arguments:
*     A pointer to a dialog, a dialog id
*   Returns:
*     A pointer to a control structure
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CONTROLITEM *g2pvt_lookup_control_by_id (int controlId, GENSYMDIALOG *dialog)
{
  CONTROLITEM *pitem;
  int i;

  if (dialog == NULL) {
    return NULL;
  }

  for (i=0; i < dialog->control_count; i++) {
    pitem = dialog->pcontrols[i];
    if (pitem->_controlId == controlId) {
      return pitem;
    }
  }

  return (CONTROLITEM *) NULL;
}


/*****************************************************************************
* CONTROLITEM *g2pvt_lookup_control_by_hwnd (int controlId, HWND hwndDlg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CONTROLITEM *g2pvt_lookup_control_by_hwnd (int controlId, HWND hwndDlg)
{
  // get the GENSYMDIALOG stored in our window bytes
  DIALOGINFO *pDialogInfo = (DIALOGINFO*)GetWindowLongPtr(hwndDlg,
	  GWLP_USERDATA);
  if (pDialogInfo == NULL) {
    return NULL;
  }

  // null check done in callee
  return g2pvt_lookup_control_by_id(controlId, pDialogInfo->_pdialog);
}


/*****************************************************************************
* CONTROLITEM *g2pvt_lookup_control_with_handles (int controlId, long dlgId)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CONTROLITEM *g2pvt_lookup_control_with_handles (int controlId, long dlgId)
{
  GENSYMDIALOG *dialog;

  dialog = g2pvt_find_dialog_by_id(dlgId);
  if (dialog == NULL) {
    return NULL;
  }

  // null check done in callee
  return g2pvt_lookup_control_by_id(controlId, dialog);
}


/*****************************************************************************
* LPWSTR g2pvt_empty_wide_string ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
LPWSTR g2pvt_empty_wide_string ()
{
  LPWSTR rval;

  rval = (LPWSTR)malloc(sizeof(wchar_t));
  rval[0] = 0;

  return rval;
}


/*****************************************************************************
* static BOOL start_structure_output ()
*
*   Description:
*   Input Arguments:
*   Return value:
*   Notes:
*   Modifications:
*****************************************************************************/
#ifdef ECHO_DIALOG_SPEC
static BOOL start_structure_output ()
{
  char filename[MAX_PATH];
  DWORD got_filename = 0;

  got_filename = GetEnvironmentVariableA(STRUCTURE_FILENAME_ENV_VAR,
    filename, MAX_PATH);

  if (got_filename == 0) {
    g2pvt_gprintf(G2PVT_ERROR, "No value found for environment variable %s\n",
      STRUCTURE_FILENAME_ENV_VAR);
    return FALSE;
  }
  if (got_filename > MAX_PATH) {
    g2pvt_gprintf(G2PVT_ERROR, "Could not fill in value of environment variable %s\n",
      STRUCTURE_FILENAME_ENV_VAR);
    return FALSE;
  }
  echo_dialog_file_handle = fopen(filename, "w");
  if (echo_dialog_file_handle == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "UNABLE TO OPEN FILE \"%s\"!!!\n",
      filename);
    return FALSE;
  }
  return TRUE;
}
#endif


/*****************************************************************************
* static BOOL continue_structure_output ()
*
*   Description:
*   Input Arguments:
*   Return value:
#  ifdef ECHO_DIALOG_SPEC
if (pDebugLevel == G2PVT_DIALOG_START) {
start_structure_output();
}
#  endif
#  ifdef ECHO_DIALOG_SPEC
continue_structure_output(buf, pDebugLevel);
#  else
g2ext_puts(buf);
#  endif
*   Notes:
*   Modifications:
*****************************************************************************/
#ifdef ECHO_DIALOG_SPEC
static void continue_structure_output (char *buf, short pDebugLevel)
{
  if ((echo_dialog_file_handle != NULL) &&
    ((pDebugLevel == G2PVT_DIALOG_START) ||
    (pDebugLevel == G2PVT_DIALOG_CONT) ||
    (pDebugLevel == G2PVT_DIALOG_FINISH))) {
    fputs(buf, echo_dialog_file_handle);
  } else {
    g2ext_puts(buf);
  }

  if (pDebugLevel == G2PVT_DIALOG_FINISH) {
    if (echo_dialog_file_handle != NULL) {
      if (fclose(echo_dialog_file_handle)) {
        g2ext_puts("UNABLE TO CLOSE FILE!!!\n");
      }
    }
  }
}
#endif


/*****************************************************************************
* static void start_printing_dialog ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
#ifdef ECHO_DIALOG_SPEC
static void start_printing_dialog ()
{
  g2pvt_gprintf(G2PVT_DIALOG_START, "NEW DIALOG\n");
  starting_echoing_dialog_p = TRUE;
}
#endif


/*****************************************************************************
* char *string_of_control_type (long control_type)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
#ifdef _DEBUG
char *string_of_control_type (long control_type)
{
  char *buf;

  switch (control_type) {

  case ctTabs:
    return "tab-frame";
  case ctProgressBar:
    return "progress-bar";
  case ctTrackBar:
    return "track-bar";
  case ctSlider:
    return "slider";
  case ctComboTreeView:
    return "combo-tree";
  case ctIcon:
    return "image-icon";
  case ctComboBox:
    return "combo-box";
  case ctColor:
    return "color";
  case ctListBox:
    return "list-box";
  case ctTextBx:
    return "text-box";
  case ctMaskEdit:
    return "masked-edit";
  case ctStatic:
    return "label";
  case ctSpin:
    return "spinner";
  case ctDuration:
    return "duration";
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctShortDuration:
	return "short-duration";
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctCalendar:
    return "calendar";
  case ctTimeOfDay:
    return "time-of-day";
  case ctWorkspace:
    return "workspace";
  case ctGroup:
    return "group";
  case ctRadio:
    return "radio-button";
  case ctCheck:
    return "check-box";
  case ctPushBtn:
    return "push-button";
  case ctTabularView:
    return "tabular-view";
  case ctGridView:
    return "grid-view";
  default:
    buf = (char *)malloc(20 * sizeof(char));
    sprintf(buf, "component %d", control_type);
    return buf;
  }
}
#endif


/*****************************************************************************
* static void print_dlg_style (char *style_string, BOOL *first_one)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     first_one is a read/write parameter.  It is passed by reference, its
*     value is used, and then its value may be changed.
*
*     -----
*   Modifications:
*****************************************************************************/
#ifdef ECHO_DIALOG_SPEC
static void print_dlg_style (char *style_string, BOOL *first_one)
{
  if ((*first_one) == TRUE) {
    g2pvt_gprintf(G2PVT_DIALOG_CONT, ",\n\t\t   styles: sequence( ");
    *first_one = FALSE;
  } else {
    g2pvt_gprintf(G2PVT_DIALOG_CONT, ",\n\t\t\t\t     ");
  }

  g2pvt_gprintf(G2PVT_DIALOG_CONT, "the symbol %s",
    style_string);
}
#endif


/*****************************************************************************
* static void print_g2_control_value (CONTROLITEM *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
#ifdef ECHO_DIALOG_SPEC
static void print_g2_control_value (CONTROLITEM *pItem)
{
  LPWSTR parent_text, original_text, new_text;

  parent_text = g2pvt_get_component_parent_text(pItem);
  original_text = g2pvt_get_component_text(pItem);

  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                parent-control-text: \"%ls\",\n",
    parent_text);
  free(parent_text);

  g2pvt_gprintf(G2PVT_DIALOG_CONT, "structure(text-value: \"");
  if (!wcscmp(original_text, G2_SPECIAL_CASE_1_TEXT)) {
    new_text = G2_SPECIAL_CASE_1_REPLACEMENT_TEXT;
  } else {
    new_text = original_text;
  }
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "%ls\")", new_text);
  free(original_text);
}
#endif


/*****************************************************************************
* static void print_dialog_component (CONTROLITEM *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
#ifdef ECHO_DIALOG_SPEC
static void print_dialog_component (CONTROLITEM *pItem)
{
  long styles = pItem->_styles;
  BOOL sty1 = TRUE;

  if (starting_echoing_dialog_p) {
    starting_echoing_dialog_p = FALSE;
  } else {
    // g2pvt_gprintf(G2PVT_DIALOG_CONT, "),\n");
  }

  g2pvt_gprintf(G2PVT_DIALOG_CONT, "%-15s ",
    string_of_control_type(pItem->_type));
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "response-action: %-3d",
    pItem->_respcode);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "control-id: %-3d",
    pItem->_controlId);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "%S\n", pItem->_mText);

  g2pvt_gprintf(G2PVT_DIALOG_CONT, "%-15s ",
    string_of_control_type(pItem->_type));
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "response-action: %-3d, styles = %8x ",
    pItem->_respcode, (unsigned int) pItem->_styles);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "g2 styles: %-3d",
    pItem->_g2styles);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "control-id: %-3d (%d, %d) at (%d, %d) ",
    pItem->_controlId, pItem->_width, pItem->_height,
    pItem->_x, pItem->_y);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "%S\n", pItem->_mText);
}


static void orig_print_dialog_component (CONTROLITEM *pItem)
{
  long styles = pItem->_styles;
  BOOL sty1 = TRUE;

  if (starting_echoing_dialog_p) {
    starting_echoing_dialog_p = FALSE;
  } else {
    g2pvt_gprintf(G2PVT_DIALOG_CONT, "),\n");
  }
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "       structure(control-type: the symbol %s,\n",
    string_of_control_type(pItem->_type));
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   control-id: %d,\n",
    pItem->_controlId);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   parent-control-id: %d,\n",
    pItem->_parentControlId);
  print_g2_control_value(pItem);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   height: %d,\n",
    pItem->_height);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   width: %d,\n",
    pItem->_width);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   left: %d,\n",
    pItem->_x);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   top: %d,\n",
    pItem->_y);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   response-action: %d,\n",
    pItem->_respcode);
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   control-value: ");
  g2pvt_gprintf(G2PVT_DIALOG_CONT, ",\n");

  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   is-child: %s,\n",
    (styles & WS_CHILD) ? "true" : "false");
  g2pvt_gprintf(G2PVT_DIALOG_CONT, "                   is-visible: %s",
    (styles & WS_VISIBLE) ? "true" : "false");

  // need to handle ctMaskedEdit here?
  if ((styles & ES_MULTILINE) && (pItem->_type == ctTextBx))
    print_dlg_style("es-multiline", &sty1);
  if ((styles & ES_AUTOHSCROLL) && (pItem->_type == ctTextBx))
    print_dlg_style("es-autohscroll", &sty1);
  if ((styles & WS_VSCROLL) && (pItem->_type == ctTextBx))
    print_dlg_style("ws-vscroll", &sty1);
  if ((styles & BS_AUTOCHECKBOX) && (pItem->_type == ctCheck))
    print_dlg_style("bs-autocheckbox", &sty1);
  if ((styles & BS_AUTORADIOBUTTON) && (pItem->_type == ctRadio))
    print_dlg_style("bs-autoradiobutton", &sty1);
  if ((styles & WS_GROUP) && (pItem->_type == ctRadio))
    print_dlg_style("ws-group", &sty1);
  if ((styles & BS_GROUPBOX) && (pItem->_type == ctGroup))
    print_dlg_style("bs-groupbox", &sty1);
  if ((styles & BS_DEFPUSHBUTTON) && (pItem->_type == ctPushBtn))
    print_dlg_style("bs-defpushbutton", &sty1);
  if ((styles & UDS_ALIGNRIGHT) && (pItem->_type == ctSpin))
    print_dlg_style("uds-alignright", &sty1);
  if ((styles & UDS_ARROWKEYS) && (pItem->_type == ctSpin))
    print_dlg_style("uds-arrowkeys", &sty1);
  if ((styles & UDS_SETBUDDYINT) && (pItem->_type == ctSpin))
    print_dlg_style("uds-setbuddyint", &sty1);
  if ((styles & UDS_AUTOBUDDY) && (pItem->_type == ctSpin))
    print_dlg_style("uds-autobuddy", &sty1);
  if ((styles & WS_CLIPSIBLINGS) && (pItem->_type == ctTabs))
    print_dlg_style("ws-clipsiblings", &sty1);
  if (styles & WS_TABSTOP)
    print_dlg_style("ws-tabstop", &sty1);

  if (!sty1) {
    g2pvt_gprintf(G2PVT_DIALOG_CONT, ")");
  }
}
#endif


/*****************************************************************************
* void g2pvt_finish_dialog ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
#ifdef ECHO_DIALOG_SPEC
void g2pvt_finish_dialog (long pDialog)
{
  // g2pvt_gprintf(G2PVT_DIALOG_FINISH, ")))\n");
  starting_echoing_dialog_p = FALSE;
  // g2pvt_puts("Finished specifying dialog!\n");
  g2pvt_puts("END DIALOG\n");
}
#endif




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP - Dynamic Dialogs Main Implementation
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
/*****************************************************************************
* static LONG WINAPI ModalSizeMoveWndProc(HWND hwnd, UINT message,
*                                         WPARAM wParam, LPARAM lParam)
*
*   Description:
*   Input Arguments:
*   Returns: nothing
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static LONG WINAPI ModalSizeMoveWndProc(HWND hwnd, UINT message,
                                        WPARAM wParam, LPARAM lParam)
{
  WNDPROC wndproc;

  switch(message) {
  case WM_ENTERSIZEMOVE:
    g2pvt_enter_modal_loop();
    break;
  case WM_EXITSIZEMOVE:
    g2pvt_exit_modal_loop();
    break;
  }

  if ((wndproc = (WNDPROC) GetProp(hwnd, L"OLD_WNDPROC")))
    return CallWindowProc(wndproc, hwnd, message, wParam, lParam);
  else
    return DefWindowProc(hwnd, message, wParam, lParam);
}


/*****************************************************************************
* static void handle_modal_size_move(HWND hwnd)
*
*   Description: Subclass window to hook modal loops
*   Input Arguments:
*   Returns: nothing
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void handle_modal_size_move (HWND hwnd)
{
  WNDPROC wndproc;

  wndproc = (WNDPROC) SetWindowLongPtr(hwnd, GWLP_WNDPROC,
	  (LONG)ModalSizeMoveWndProc);
  SetProp(hwnd, L"OLD_WNDPROC", (HANDLE)wndproc);
}


/* For each control with anchor bits, make it known to the resize manager. */
static void g2pvt_initialize_resizable_dialog(HWND hwndDlg, DIALOGINFO *dlgInfo)
{
  CONTROLHWND *ch;
  CONTROLITEM *pcontrol;

  dlgInfo->resizer = g2pvt_resizer_create(hwndDlg, dlgInfo->_numControlHwnds);

  for(ch = dlgInfo->_controlHwndList; ch; ch = ch->next) {
    pcontrol = g2pvt_lookup_control_by_id(ch->controlId, dlgInfo->_pdialog);

    if(pcontrol && (pcontrol->_g2styles & G2_ANCHOR_P) != 0 &&
       pcontrol->_parentControlId == PARENT_IS_ENTIRE_DIALOG && pcontrol->_type!=68)
      g2pvt_resizer_add(dlgInfo->resizer, ch->controlId, (pcontrol->_g2styles & G2_ANCHOR_MASK) >> 4);
  }

  g2pvt_resizer_lock(dlgInfo->resizer);

  // Now do the same for child dialogs in tabs.
  g2pvt_init_resizable_child_dialogs(hwndDlg, dlgInfo);
}

/* Refresh the window-icon in every dialog window using native-icon. */
void g2pvt_refresh_dialog_icon (int native_icon)
{
  GENSYMDIALOG *idialog;
  DIALOGINFO *dlgInfo;

  for (idialog=list_of_dialogs;  idialog; idialog=idialog->next) {
    if(idialog->hwnd) {
      dlgInfo = (DIALOGINFO *) GetWindowLongPtr(idialog->hwnd, GWLP_USERDATA);
      if(dlgInfo->icon == native_icon) {
	HWND hwndParent = g2pvt_parent_window(idialog->hwnd);
	if(hwndParent == NULL)
	  g2pvt_set_window_icon(idialog->hwnd, native_icon);
	else
	  g2pvt_set_window_icon(hwndParent, native_icon);
      }
    }
  }
}

// Saves an array of the G2 id's of the currently enabled top-level custom
// dialog windows, and frame window, on pForDlg.
static void save_enabled_windows(GENSYMDIALOG *pForDlg)
{
  GENSYMDIALOG *pDlg;
  int n;

  n=0;
  if(IsWindowEnabled(hwndFrame))
    n++;

  for(pDlg=list_of_dialogs;  pDlg; pDlg=pDlg->next)
    if(pDlg != pForDlg && IsWindow(pDlg->hwnd) && IsWindowEnabled(pDlg->hwnd))
      n++;

  pForDlg->enabledWindows = calloc(n+1, sizeof(int));
  if(!pForDlg->enabledWindows)
    return;

  n = 0;
  if(IsWindowEnabled(hwndFrame))
    pForDlg->enabledWindows[n++] = -123; // Indicates the frame window.

  for(pDlg=list_of_dialogs;  pDlg; pDlg=pDlg->next)
    if(pDlg != pForDlg && IsWindow(pDlg->hwnd) && IsWindowEnabled(pDlg->hwnd))
      pForDlg->enabledWindows[n++] = pDlg->g2_id;
  pForDlg->enabledWindows[n++] = 0;  
}

static void restore_enabled_windows(GENSYMDIALOG *pForDlg)
{
  int i, id;
  HWND hwnd;

  if(pForDlg->enabledWindows == NULL)
    return;

  for(i=0; pForDlg->enabledWindows[i]; i++) {
    id = pForDlg->enabledWindows[i];
    hwnd = (id == -123) ? hwndFrame : g2pvt_find_dialog_hwnd_by_handle(id);
    if(IsWindow(hwnd) && !IsWindowEnabled(hwnd))
      EnableWindow(hwnd, TRUE);
  }
}


/*****************************************************************************
* long g2ext_show_dialog (long pDialog)
*
*   Description:
*   Input Arguments:
*   Returns: A G2pointer for the HWND of the dialog's frame, or -1 on failure.
*   Notes:
*
*     -----
*   Modifications:
*    - Replace options with mdi_child_p, dock, neighbor, and icon arguments,
*      to support dialog panes. -fmw, 5/4/05
*    - Add resizable_p argument -fmw, 8/16/05
*    - Change return value -fmw, 8/25/05
*    - Save icon and set icon of dlg window in all cases. -fmw, 9/2/05
*****************************************************************************/

#ifdef DEBUG_DIALOG_LEAKS
_CrtMemState g_memCheckPoint;
#endif

long g2ext_show_dialog (long pDialog, long xPos, long yPos, long mdi_child_p,
                        long dock, long neighbor, long icon, long resizable_p,
                        long g2DlgMonPref)
{
#ifndef CODEJOCK
  return -1;
#else
  GENSYMDIALOG *found_dialog;
  HWND hwndDlg, hwndDlgFrame = NULL;
  DIALOGINFO *dlgInfo;
  RECT r, screenRect;
  POINT p;
  BOOL mdi_child_dialog_p;
  SCROLLINFO scrInfo;
  DWORD screenHeight;
  LONG style;

#ifndef CODEJOCK
  return -1;
#endif

  found_dialog = g2pvt_find_dialog_by_id(pDialog);
  if (found_dialog == NULL) {
    return -1;
  }
  found_dialog->inShowDialog = 1;

  // create dialog box
  dlgInfo = (DIALOGINFO *) malloc(sizeof(DIALOGINFO));
  if (dlgInfo == NULL) {
    found_dialog->inShowDialog = 0;
    return -1;
  }
  ZeroMemory((LPVOID)dlgInfo, sizeof(DIALOGINFO));

  dlgInfo->_pdialog = found_dialog;
  dlgInfo->_tabPages = NULL;
  dlgInfo->_controlHwndList = NULL;
  dlgInfo->_numControlHwnds = 0;
  dlgInfo->icon = icon;
  dlgInfo->resizable = resizable_p;

  hwndDlg = g2pvt_create_dialogMFC(dlgInfo, found_dialog->g2_id);

  if (hwndDlg != NULL)
  {
    // set pDialog->hwnd
    dlgInfo->_pdialog->hwnd = hwndDlg;
    if (found_dialog->_iDlgType == MODAL)
    {
      GENSYMDIALOG *idialog;

      // Save currently enabled windows, to be restored when this dialog is
      // dismissed.
      save_enabled_windows(found_dialog);

      // Fake a modal dialog box by disabling the owner window and all custom
      // dialogs.  FIXME: Need to disable other top-level owned windows besides
      // custom dialogs. Eg, basic dialogs.
      EnableWindow(hwndFrame, FALSE);
      for (idialog=list_of_dialogs;  idialog != NULL; idialog=idialog->next)
      {
        if (idialog != found_dialog && IsWindow(idialog->hwnd) && IsWindowEnabled(idialog->hwnd))
        {
          EnableWindow(idialog->hwnd, FALSE);
        }
      }
    }

    // size and show the main dialog
    r.top = 0;
    r.left = 0;
    r.right = found_dialog->width;
    r.bottom = found_dialog->height;
    MapDialogRect(hwndDlg, &r);

    // Assume non-modal
    mdi_child_dialog_p = Frame_is_MDI && mdi_child_p;

    if (mdi_child_dialog_p) {
      GetClientRect(hwndClient,&screenRect);
    } else {
      SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);
    }
    screenHeight = screenRect.bottom - screenRect.top;
    if(screenHeight < r.bottom - r.top)
      {
        // add space for VSCROLL
        r.right += GetSystemMetrics(SM_CXVSCROLL);

        // fill SCROLLINFO structure
        scrInfo.cbSize = sizeof(SCROLLINFO);
        scrInfo.fMask = SIF_ALL;
        scrInfo.nMin = 0;
        scrInfo.nMax = r.bottom;
        scrInfo.nPage = r.top + screenHeight;
        scrInfo.nPos = 0;
        scrInfo.nTrackPos = 0;

        // set new height for the dialog
        r.bottom = r.top + screenHeight;

        style = GetWindowLong(hwndDlg,GWL_STYLE);
        SetWindowLong(hwndDlg,GWL_STYLE,style | WS_VSCROLL);

        // set VSCROLL info and show it
        SetScrollInfo(hwndDlg, SB_VERT, &scrInfo, TRUE);
      }

    SetWindowPos(hwndDlg, HWND_TOP, 0, 0, r.right, r.bottom, SWP_NOMOVE);
    g2pvt_set_dialog_title(found_dialog);
    g2pvt_set_dialog_background(found_dialog);

    // move dialog to some specified (x, y) position, and then show it
    assert(g2DlgMonPref >= 0 && g2DlgMonPref <= 1);
    g2pvt_position_dialog(hwndDlg, xPos, yPos, mdi_child_dialog_p, &p,
                          (enum G2DialogMonitorPreference)g2DlgMonPref);

    hwndDlgFrame = hwndDlg;

    // This must be done while the dialog is still at its designed size.
    if(dlgInfo->resizable)
      g2pvt_initialize_resizable_dialog(hwndDlg, dlgInfo);

    if (mdi_child_dialog_p) {
      hwndDlgFrame = g2pvt_show_mdi_dialog(hwndDlg, found_dialog->g2_id);
      // GENSYMCID-710: TWNG: GDI leak when a workspace is shown
      // We should set the icon to custom dialog.
      g2pvt_set_window_icon(hwndDlg, icon);

    } else if(dock > 0) {
      g2pvt_show_dialog_in_pane(hwndDlg, found_dialog->g2_id,
				p.x, p.y, r.right, r.bottom,
				dock, neighbor, icon);
    } else {
      // This line is only necessary for modal TWNG dialogs, but it won't
      // hurt to have it here all the time. -jv, 2/28/05
      EnableWindow(hwndDlg, TRUE);
      handle_modal_size_move(hwndDlg);
      g2pvt_set_window_icon(hwndDlg, icon);
      ShowWindow(hwndDlg, SW_SHOW);
    }
  }

#ifdef ECHO_DIALOG_SPEC
  g2pvt_finish_dialog(pDialog);
#endif

  //Gensym-683-TAM1-CN-BF-JIRA-224-More TWNG leaks involving native dialogs
  //save cached cpointer into dialog_g2pointer
  if (NULL == hwndDlgFrame) {
    free(dlgInfo);
    found_dialog->inShowDialog = 0;
    return -1;
  }
  found_dialog->dialog_g2pointer = g2ext_cache_cpointer(hwndDlgFrame);
  found_dialog->inShowDialog = 0;
  return found_dialog->dialog_g2pointer;
  //return g2ext_cache_cpointer(hwndDlgFrame);
#endif /* CODEJOCK */
}

long g2ext_set_dialog_background_property (long pDialog, LPWSTR pBackgroundColor)
{
  GENSYMDIALOG *found_dialog = g2pvt_find_dialog_by_id(pDialog);
  DIALOGINFO *dlgInfo;

  if (found_dialog == NULL) 
  {
    return -1;
  }

  dlgInfo = (DIALOGINFO*) GetWindowLong(found_dialog->hwnd, GWLP_USERDATA);
  if (wcslen(pBackgroundColor)) 
  {
    dlgInfo->useBackgroundColor = TRUE;
    g2pvt_set_dialog_structure_backgroundColor(found_dialog, dlgInfo, pBackgroundColor);
  }
  else 
  {
      dlgInfo->useBackgroundColor = FALSE;
  }
  
  g2pvt_set_dialog_background(found_dialog);

  return 0;
}


/************************************************************************************
* long allocate_extra_data_ct_combo_tree_view(CONTROLITEM *p_new_item, long nHeight, long nWidth)
*
*
* The ctComboTreeView control requires extra data for creation; the dropped width and
* the dropped height.  This routine allocates the space needed for the extra 
* ctComboTreeView data and loads the data.
*
*
*Input:
* CONTROLITEM *p_new_item, long nHeight, long nWidth
*
*
*Return Value:
*
*  DYNAMIC_DIALOG_FAILED if memory can not be allocated
*  SUCCESS if success
*
*
*************************************************************************************/
long allocate_extra_data_ct_combo_tree_view(CONTROLITEM *p_new_item, long nHeight, long nWidth)
{
    EXTRA_TYPE_DATA *pETData;
    EXTRA_COMBO_TREE_VIEW_DATA *pCTVData;
    p_new_item->_pExtraTypeData =  (EXTRA_TYPE_DATA *) malloc(sizeof(EXTRA_TYPE_DATA));
    if (!(p_new_item->_pExtraTypeData))
    {
      DLGERROR("Out of memory in g2ext_add_to_dialog\n");
      return DYNAMIC_DIALOG_FAILED;
    }
    ZeroMemory((LPVOID)p_new_item->_pExtraTypeData, sizeof(EXTRA_TYPE_DATA));
    p_new_item->_pExtraTypeData->_type = ctComboTreeView;
    p_new_item->_pExtraTypeData->_pData = (EXTRA_COMBO_TREE_VIEW_DATA *)
      malloc(sizeof(EXTRA_COMBO_TREE_VIEW_DATA));

    if (!(p_new_item->_pExtraTypeData->_pData))
    {
      DLGERROR("Out of memory in g2ext_add_to_dialog\n");
      return DYNAMIC_DIALOG_FAILED;
    }
    ZeroMemory((LPVOID)p_new_item->_pExtraTypeData->_pData,
               sizeof(EXTRA_COMBO_TREE_VIEW_DATA));
    pETData = p_new_item->_pExtraTypeData;
    pCTVData = (EXTRA_COMBO_TREE_VIEW_DATA*)pETData->_pData;
    pCTVData->DroppedHeight = nHeight;
    pCTVData->DroppedWidth  = nWidth;
    return SUCCESS;
}


/*******************************************************************************
* long allocate_extra_data_text_bx (CONTROLITEM *p_new_item)
*
*
* The ctTextBx control requires extra data for creation; the selected text
* and the text and back ground colors.  This stucture initializes the space
*
* Input:
* CONTROLITEM *p_new_item, long nHeight, long nWidth
*
*
* Return Value:
*  DYNAMIC_DIALOG_FAILED if memory can not be allocated
*  SUCCESS if success
*
*
*******************************************************************************/
static long allocate_extra_data_text_bx (CONTROLITEM *p_new_item)
{
  // Allocate the first "level" of data, the generic "extra data" container
  if (!p_new_item->_pExtraTypeData)
    p_new_item->_pExtraTypeData = (EXTRA_TYPE_DATA *) malloc(sizeof(EXTRA_TYPE_DATA));
  if (!(p_new_item->_pExtraTypeData))
  {
    DLGERROR("Out of memory in g2ext_add_to_dialog\n");
    return DYNAMIC_DIALOG_FAILED;
  }
  ZeroMemory((LPVOID)p_new_item->_pExtraTypeData, sizeof(EXTRA_TYPE_DATA));
  p_new_item->_pExtraTypeData->_type = ctTextBx;

  // Now allocate the text-box specific data
  p_new_item->_pExtraTypeData->_pData =
    (EXTRA_TEXTBX_DATA *)malloc(sizeof(EXTRA_TEXTBX_DATA));
  g2pvt_clear_text_box_extra_data((EXTRA_TEXTBX_DATA *)p_new_item->_pExtraTypeData->_pData);
  if(!(p_new_item->_pExtraTypeData->_pData))
  {
    DLGERROR("Out of memory in g2ext_add_to_dialog\n");
    return DYNAMIC_DIALOG_FAILED;
  }

  return SUCCESS;
}


/*****************************************************************************
* long g2ext_add_to_dialog (long pDialogId, long pControlId,
*                           long parentControlId, LPWSTR pParentTxt,
*                           long pHeight, long pWidth, long pLeft, long pTop,
*                           long pType, LPWSTR pText, long pStylesHi, long pStylesLo,
*                           long pG2Styles, long pResponse)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     I wish there were a cleaner but still simple way to handle composite
*     controls, but this is about the best I can do.  When we get a request
*     for a spinner, we actually create a text box, not an up/down control,
*     which uses the id assigned by G2.  The text box really is the spinner,
*     much more than the up/down control; the text box therefore also gets the
*     response-action assigned by the user.
*
*     The up/down control always gets a response-action of DLG_NO_RESPONSE (aka
*     'ignore), and it gets a different id from the text box.  We trust that the
*     id+1 will not be used by G2; that is crucial, and must remain supported in
*     the Lisp code.  We make sure the up/down control is created with
*     UDS_AUTOBUDDY, even though that too is supported in Lisp and should always
*     be the case even if we didn't check it here.
*
*     We should add some _DEBUG code which keeps track of the control-id of
*     the last component, and ASSERTs that we don't create two controls with
*     the same control-id.
*
*     Note that the ctSpin/add_buddy_to_dialog code is new in 8.1r0.  In 8.0,
*     we handled the buddying in Lisp, and the C code had no idea that, to G2,
*     the two controls were conceptually one.  Now, the Lisp code will have
*     very little idea that two controls have been created.  -jv, 2/03/05
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_add_to_dialog (long pDialogId, long pControlId,
                          long parentControlId, LPWSTR pParentTxt,
                          long pHeight, long pWidth, long pLeft, long pTop,
                          LPWSTR pFont,
                          long pFontSizes,LPWSTR pFontColor, LPWSTR pControlBackgroundColor,
                          long pType, LPWSTR pText,
                          long pStylesHi, long pStylesLo,
                          long pG2Styles, long pResponse)
{
  CONTROLITEM *new_item = NULL;
  FONTDEFINITION *font=NULL;
  RGBDEFINITION *textColor=NULL;
  RGBDEFINITION *bckColor=NULL;
  GENSYMDIALOG *found_dialog = NULL;
  EXTRA_PUSH_BUTTON_DATA *pPBData = NULL;
  EXTRA_TYPE_DATA *pETData = NULL;
  long w32_styles, response_action, is_default = 0;
  int len = 0;
  long pIsBold=0,pIsItalic=0;
#ifndef CODEJOCK
  return DYNAMIC_DIALOG_FAILED;
#endif

  w32_styles = (pStylesHi << 16) | pStylesLo;

  /* Add a magic bit to indicate whether the push-button is default push-button */
  if ((pType == ctPushBtn) && (pResponse & BIT_OF_PUSH_BUTTON_IS_DEFAULT)) {
    is_default = 1;
    pResponse -= BIT_OF_PUSH_BUTTON_IS_DEFAULT;
  }

  response_action = pResponse;  // to avoid modifying pResponse

  found_dialog = g2pvt_find_dialog_by_id(pDialogId);
  if (found_dialog == NULL) {
    DLGERROR("add_to_dialog: failed to locate dialog\n");
    return DYNAMIC_DIALOG_FAILED;
  }

  if (found_dialog->control_count >= found_dialog->array_size) {
    void *new_controls;
    long new_size;

    new_size = (long) (found_dialog->array_size *
      DYNAMIC_DIALOGS_COMPONENT_MULTIPLIER);
    new_controls = realloc(found_dialog->pcontrols,
      new_size * sizeof(CONTROLITEM));
    if (new_controls == NULL) {
      DLGERROR("Out of memory attempting to realloc array in g2ext_add_to_dialog\n");
      // We were not able to make a larger array.  In this case, the old array
      // is still intact.  We do nothing except return failure.
      return DYNAMIC_DIALOG_FAILED;
    }

    // The contents of the old array were copied into the new array.  RIGHT???
    found_dialog->array_size = new_size;
    found_dialog->pcontrols = (CONTROLITEM **) new_controls;
  }

  new_item = (CONTROLITEM *) malloc(sizeof(CONTROLITEM));
  if (new_item == NULL) {
    DLGERROR("Out of memory in g2ext_add_to_dialog\n");
    return DYNAMIC_DIALOG_FAILED;
  }
  ZeroMemory((LPVOID)new_item, sizeof(CONTROLITEM));
 
  if (w32_styles & BS_AUTORADIOBUTTON)
    found_dialog->need_new_group = TRUE;
  if (!(w32_styles&BS_AUTORADIOBUTTON) && found_dialog->need_new_group) {
    w32_styles |= WS_GROUP;
    found_dialog->need_new_group = FALSE;
  }

  new_item->_controlId = pControlId;
  new_item->_parentControlId = parentControlId;
  new_item->_dialogId = pDialogId;
  new_item->_height = pHeight;
  new_item->_width = pWidth;
  new_item->_type = pType;
  new_item->_x = pLeft;
  new_item->_y = pTop;
  new_item->_g2styles = pG2Styles;
  new_item->_styles = w32_styles;
  new_item->_respcode = response_action;
  new_item->_pExtraTypeData = NULL;
  new_item->_font=NULL;
  //Error handling if the memory is unable to be assigned
  font=(FONTDEFINITION*) malloc(sizeof(FONTDEFINITION));
  if(font==NULL){
      free(new_item);
      DLGERROR("Out of memory in g2ext_add_to_dialog\n");
      return DYNAMIC_DIALOG_FAILED;
  }
  textColor=(RGBDEFINITION*)malloc(sizeof(RGBDEFINITION));
  if(textColor==NULL){
      free(new_item);
      free(font);
      DLGERROR("Out of memory in g2ext_add_to_dialog\n");
      return DYNAMIC_DIALOG_FAILED;
  }
  font->_fontColor=textColor;
  bckColor=(RGBDEFINITION*)malloc(sizeof(RGBDEFINITION));
  if(bckColor==NULL){
      free(new_item);
      free(font);
      free(textColor);
      DLGERROR("Out of memory in g2ext_add_to_dialog\n");
      return DYNAMIC_DIALOG_FAILED;
  }



  font->_fontColor=bckColor;
  new_item->_font=font;
  if (is_default) {
    pPBData = (EXTRA_PUSH_BUTTON_DATA *)malloc(sizeof(EXTRA_PUSH_BUTTON_DATA));
    if (pPBData == NULL) {
      free(new_item);
      free(font);
      free(textColor);
      free(bckColor);
      DLGERROR("Out of memory in g2ext_add_to_dialog\n");
      return DYNAMIC_DIALOG_FAILED;
    }
    pPBData->m_hwndTip = NULL;
    pPBData->m_tInfo_uId = 0;
    pPBData->isDefault = 1;

    pETData = (EXTRA_TYPE_DATA *)malloc(sizeof(EXTRA_TYPE_DATA));
    if (pETData == NULL) {
      free(new_item);
      free(font);
      free(textColor);
      free(bckColor);
      free(pPBData);
      DLGERROR("Out of memory in g2ext_add_to_dialog\n");
      return DYNAMIC_DIALOG_FAILED;
    }
    pETData->_type = ctPushBtn;
    pETData->_pData = pPBData;

    new_item->_pExtraTypeData = pETData;
  }

  g2pvt_set_component_parent_text(new_item, pParentTxt);
  g2pvt_set_component_text(new_item, pText);
  //Procedure for adding font CONTROLITEM
  if(g2pvt_set_component_font(new_item, pFont, pFontSizes, pFontColor, pControlBackgroundColor, pIsBold, pIsItalic)==0){
      free(font);
      free(textColor);
      free(bckColor);
      free(new_item);
      free(pPBData);
      free(pETData);
      DLGERROR("Out of memory in g2ext_add_to_dialog==>g2pvt_set_component_font==>g2pvt_get_color_from_color_name\n");
      return DYNAMIC_DIALOG_FAILED;
  }

  // ctComboTreeView requires more data; the height and the width
  if (ctComboTreeView == new_item->_type)
  {
     if (DYNAMIC_DIALOG_SUCCEEDED !=
         allocate_extra_data_ct_combo_tree_view(new_item,
                                                TREE_VIEW_COMBO_BOX_USE_DEF,
                                                TREE_VIEW_COMBO_BOX_USE_DEF))
     {
       free(font);
       free(textColor);
       free(bckColor);
       free(new_item);
       free(pPBData);
       free(pETData);
       return DYNAMIC_DIALOG_FAILED;
     }
  }

  // Allocate the space for the extra data
  if (ctTextBx == new_item->_type)
  {
    if (DYNAMIC_DIALOG_SUCCEEDED != 
      allocate_extra_data_text_bx(new_item))
    {
       free(font);
       free(textColor);
       free(bckColor);
       free(new_item);
       free(pPBData);
       free(pETData);
      return DYNAMIC_DIALOG_FAILED;
    }
  }

  found_dialog->pcontrols[found_dialog->control_count++] = new_item;

#ifdef ECHO_DIALOG_SPEC
  print_dialog_component(new_item);
#endif

  return DYNAMIC_DIALOG_SUCCEEDED;
}


/*****************************************************************************
* long g2ext_start_dialog ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:  4/23 lk initialize new GENSYMDIALOG member 'hwnd'
*****************************************************************************/
long g2ext_start_dialog (long g2_id, long guess_ncontrols, long width, long height,
                         long type, LPWSTR pTitle)
{
  GENSYMDIALOG *new_dialog;
  int len = 0;

#ifdef DEBUG_DIALOG_LEAKS
  _CrtCheckMemory();
  _CrtMemCheckpoint(&g_memCheckPoint);
  _RPT1(_CRT_WARN, "Memory checkpoint saved in g2ext_start_dialog %d\n", g2_id);
#endif

#ifndef CODEJOCK
  g2pvt_gprintf(G2PVT_ERROR, "Native custom-dialogs are not supported in this configuration.\n");
  return DYNAMIC_DIALOG_FAILED;
#endif

  new_dialog = (GENSYMDIALOG *) malloc(sizeof(GENSYMDIALOG));
  if (new_dialog == NULL) {
    return DYNAMIC_DIALOG_FAILED;
  }
  ZeroMemory((LPVOID) new_dialog, sizeof(GENSYMDIALOG));//hjg 02-24-2006 fix memory problems
  new_dialog->pcontrols = (CONTROLITEM **) malloc(guess_ncontrols *
    sizeof(CONTROLITEM));
  if (new_dialog->pcontrols == NULL) {
    free(new_dialog);
    return DYNAMIC_DIALOG_FAILED;
  }
  ZeroMemory((LPVOID)new_dialog->pcontrols,
    guess_ncontrols * sizeof(CONTROLITEM));
  new_dialog->control_count = 0;
  new_dialog->array_size = guess_ncontrols;
  new_dialog->g2_id = g2_id;	// G2-assigned integer handle
  new_dialog->dialog_id = g2ext_cache_cpointer(new_dialog);
  new_dialog->width = width;
  new_dialog->height = height;
  new_dialog->_iDlgType = type;
  new_dialog->mResponse = NULL;
  new_dialog->is_locked = FALSE;
  new_dialog->need_new_group = FALSE;

  g2pvt_set_dialog_structure_title(new_dialog, pTitle);

  // We might never iterate over this linked list, but we can keep it anyway
  new_dialog->next = list_of_dialogs;
  list_of_dialogs = new_dialog;

#ifdef ECHO_DIALOG_SPEC
  start_printing_dialog();
#endif

  return new_dialog->dialog_id;
}


/*****************************************************************************
* static long send_dialog_update_event (GENSYMDIALOG *dialog, int controlId,
*                                       LPWSTR wide_string, int initiator)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static long send_dialog_update_event (GENSYMDIALOG *dialog, int controlId,
                                      LPWSTR wide_string, int initiator)
{
#ifdef _DEBUG
  g2pvt_gprintf(G2PVT_DUMP, "update_event: control %4d, response = \"%ls\"\n",
                controlId, wide_string);
#endif

  StoreNextEventEx(GhwndWin, X11_CONTROL, dialog->dialog_id, controlId,
    initiator, -1, GENSYM_DIALOG_UPDATE, 0, wide_string);
  return DYNAMIC_DIALOG_SUCCEEDED;
}


/*****************************************************************************
* long g2pvt_send_dynamic_dialog_data_to_g2 (GENSYMDIALOG *dialog, long initiator)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2pvt_send_dynamic_dialog_data_to_g2 (GENSYMDIALOG *dialog, long initiator)
{
  long control_id, i, count;
  GENSYMDLGRESPONSE *response;
  LPWSTR ptr; //hjg 02-24-2006 fix memory problems

  response = dialog->mResponse;
  if (response == NULL) {
#ifdef GPRINTF
    g2pvt_gprintf(G2PVT_ERROR, "Could not find %s structure for dialog id %d\n",
                  "GENSYMDLGRESPONSE", dialog->dialog_id);
#endif
    return DYNAMIC_DIALOG_FAILED;
  }

  count = response->response_count;
  if (count > 1) {
    ptr = g2pvt_updated_control_value(dialog, response->initiating_control_id);
	if(initiator == FOCUS_CHANGED_UPDATE)
	  send_dialog_update_event(dialog, response->initiating_control_id,ptr,initiator);
	else
    send_dialog_update_event(dialog, response->initiating_control_id,
                             ptr,
                             ((initiator == TW_INITIATED_UPDATE) ?
                              TW_MULTI_UPDATE_BEGIN :
                              G2_MULTI_UPDATE_BEGIN));
							  
    free(ptr);// hjg 02-24-2006 fix memory problems 
    for (i=0; i < count; i++) {
      control_id = response->presponses[i]->_controlId;
      ptr = g2pvt_updated_control_value(dialog, control_id); //hjg 02-24-2006 fix memory problems
      send_dialog_update_event(dialog, control_id,
                               ptr,
                               ((initiator == TW_INITIATED_UPDATE) ?
                                TW_MULTI_UPDATE_CONTINUE :
                                G2_MULTI_UPDATE_CONTINUE));
      free(ptr);//hjg 02-24-2006 fix memory problems
    }
    ptr = g2pvt_updated_control_value(dialog, response->initiating_control_id);
    send_dialog_update_event(dialog, response->initiating_control_id,
                             ptr,
                             ((initiator == TW_INITIATED_UPDATE) ?
                              TW_MULTI_UPDATE_FINISH :
                              G2_MULTI_UPDATE_FINISH));
    free(ptr); //hjg 02-24-2006 fix memory problems
  } else if (count == 1) {
    control_id = response->presponses[0]->_controlId;
    ptr = g2pvt_updated_control_value(dialog, control_id);//hjg 02-24-2006 fix memory problems
    send_dialog_update_event(dialog, control_id,
                             ptr,
                             initiator);
    free(ptr);//hjg 02-24-2006 fix memory problems
  }
  return DYNAMIC_DIALOG_SUCCEEDED;
}



/*****************************************************************************
* long g2pvt_send_wsv_hwnd_to_g2 (HWND hwndParent, CONTROLITEM *pControl, HWND hwndWSV)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2pvt_send_wsv_hwnd_to_g2 (HWND hwndParent, CONTROLITEM *pControl, HWND hwndWSV)
{
  DIALOGINFO *pDlgInfo;
  long dialog_id = 0;
  wchar_t hex_address[9];

  ZeroMemory((PVOID) hex_address, sizeof(hex_address));
  _snwprintf(hex_address, 8, L"%x", (unsigned int) hwndWSV);

  pDlgInfo = (DIALOGINFO *)GetWindowLongPtr(hwndParent, GWLP_USERDATA);
  if (pDlgInfo == NULL) {
    return DYNAMIC_DIALOG_FAILED;
  }
  if (pDlgInfo->_pdialog == NULL) {
    return DYNAMIC_DIALOG_FAILED;
  }

  StoreNextEventEx(GhwndWin, X11_CONTROL, pDlgInfo->_pdialog->dialog_id,
                   pControl->_controlId, G2PVT_SEND_WSV_ADDRESS, -1,
                   GENSYM_DIALOG_MISCELLANY, 0, hex_address);
  return DYNAMIC_DIALOG_SUCCEEDED;
}



/*****************************************************************************
* long g2pvt_send_user_gesture_to_g2 (HWND hwndParent, CONTROLITEM *pControl,
*                                     int row, int col, UINT message_code, UINT keycode)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2pvt_send_user_gesture_to_g2 (HWND hwndParent, CONTROLITEM *pControl,
                                    int row, int col, UINT message_code,
									UINT keycode)
                                    
{
  DIALOGINFO *pDlgInfo;

  pDlgInfo = (DIALOGINFO *)GetWindowLongPtr(hwndParent, GWLP_USERDATA);
  if (pDlgInfo == NULL) {
    return DYNAMIC_DIALOG_FAILED;
  }
  if (pDlgInfo->_pdialog == NULL) {
    return DYNAMIC_DIALOG_FAILED;
  }

  switch(message_code) {
   case NM_CLICK:
     keycode = g2pvt_compute_gensym_mouse_keycode(WM_LBUTTONUP);
     break;
   case NM_DBLCLK:
     keycode = g2pvt_compute_gensym_mouse_keycode(WM_LBUTTONDBLCLK);
     break;
   case NM_RCLICK:
     keycode = g2pvt_compute_gensym_mouse_keycode(WM_RBUTTONUP);
     break;
   case NM_RDBLCLK:
     keycode = g2pvt_compute_gensym_mouse_keycode(WM_RBUTTONDBLCLK);
     break;
  }
  if (keycode > 0)
    g2pvt_fire_control_event(GENSYM_USER_GESTURE, pDlgInfo->_pdialog->g2_id,
			     row, col, pControl->_controlId, keycode, NULL);
  return DYNAMIC_DIALOG_SUCCEEDED;
}



/*****************************************************************************
* void g2ext_abort_dialog_query ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2ext_abort_dialog_query (long pDialog, long pQuery)
{
  /* add cleanup code here!!! */
}


/*****************************************************************************
* long g2ext_finish_dialog_query ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_finish_dialog_query (long pDialog, long pQuery)
{
  GENSYMDIALOG *dialog;
  GENSYMDLGRESPONSE *found_response = NULL;
  long success_p = DYNAMIC_DIALOG_SUCCEEDED;

  dialog = g2pvt_find_dialog_by_id(pDialog);
#ifdef GPRINTF
  g2pvt_gprintf(G2PVT_ALWAYS, "g2ext_finish_dialog_query: dialog id = %d\n",
    pDialog);
  g2pvt_gprintf(G2PVT_ALWAYS, " query = %d\n", pQuery);
#endif
  g2pvt_set_dialog_responses(dialog, -1, DLG_RESPOND_ALL);

  success_p = g2pvt_send_dynamic_dialog_data_to_g2(dialog, G2_INITIATED_UPDATE);

  if (success_p != DYNAMIC_DIALOG_SUCCEEDED) {
    return DYNAMIC_DIALOG_QUERY_FAILED;
  }

  return DYNAMIC_DIALOG_QUERY_SUCCEEDED;
}


/*****************************************************************************
* long g2ext_add_to_dialog_query ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_add_to_dialog_query (long pDialogId, long pQuery, long pControlId)
{
#ifdef GPRINTF
  g2pvt_gprintf(G2PVT_ALWAYS, "g2ext_add_to_dialog_query: dialog id = %d\n",
    pDialogId);
  g2pvt_gprintf(G2PVT_ALWAYS, " query = %d, control id = %d\n", pQuery,
    pControlId);
#endif

  return DYNAMIC_DIALOG_QUERY_FAILED;
}


/*****************************************************************************
* long g2ext_start_dialog_query ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_start_dialog_query (long pDialogId, long pQuery, long options)
{
  GENSYMDIALOG *found_dialog;

  found_dialog = g2pvt_find_dialog_by_id(pDialogId);
  if (found_dialog == NULL) {
    DLGERROR("start_dialog_query: failed to locate dialog\n");
    return DYNAMIC_DIALOG_QUERY_FAILED;
  }
#ifdef GPRINTF
  g2pvt_gprintf(G2PVT_ALWAYS, "g2ext_start_dialog_query: found dialog structure");
  g2pvt_gprintf(G2PVT_ALWAYS, " for dialog id %d\n", pDialogId);
#endif

  return pQuery;
}


/*****************************************************************************
* long g2pvt_send_tw_dialog_control_update (GENSYMDIALOG *dialog, long control_id)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static int is_char_digit(char x)
{
	if (x>='0' && x<='9')
		return 1;
	else
		return 0;
}

static int is_calendar_control(LPWSTR ptr)
{
	int i = 0, y, m, d;
	y = 0;
	while (ptr[i]!=0 && ptr[i]!=':') {
		if (!is_char_digit(ptr[i])) return 0;
		i++; ++y;
	}
	if (ptr[i]==0 || y==0) return 0;
	i++; m = 0;
	while (ptr[i]!=0 && ptr[i]!=':') {
		if (!is_char_digit(ptr[i])) return 0;
		i++; ++m;
	}
	if (ptr[i]==0 || m==0) return 0;
	i++; d = 0;
	while (ptr[i] != 0) {
		if (!is_char_digit(ptr[i])) return 0;
		i++; ++d;
	}
	if (d == 0) return 0;
	return 1;
}

clock_t Pre_calltime_for_gstdcu = -1;
GENSYMDIALOG *Pre_dialog_for_gstdcu;
long Pre_control_id;

long g2pvt_send_tw_dialog_control_update (GENSYMDIALOG *dialog, long control_id)
{
  LPWSTR ptr;
  int need_send = 1;
  clock_t diff;

  if (dialog == NULL) {
    DLGERROR("Received NULL dialog structure in g2pvt_send_tw_dialog_control_update\n");
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }
  ptr = g2pvt_updated_control_value(dialog, control_id); //hjg 02-24-2006 fix memory problems
  if (is_calendar_control(ptr)) {
	  if (Pre_calltime_for_gstdcu != -1) {
		  diff = clock() - Pre_calltime_for_gstdcu;
		  if (diff < 100 && dialog==Pre_dialog_for_gstdcu && control_id==Pre_control_id)
			  need_send = 0;
	  }
	  Pre_calltime_for_gstdcu = clock();
	  Pre_dialog_for_gstdcu = dialog;
	  Pre_control_id = control_id;
  }
  if (need_send)
	  send_dialog_update_event(dialog, control_id, ptr, TW_INITIATED_UPDATE);
  free(ptr);//hjg 02-24-2006 fix memory problems
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* long g2ext_send_dialog_control_update (long dlgId, long control_id)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_send_dialog_control_update (long dlgId, long control_id)
{
  GENSYMDIALOG *found_dialog;
  LPWSTR ptr;//hjg 02-24-2005 fix memory problems

  found_dialog = g2pvt_find_dialog_by_id(dlgId);
  if (found_dialog == NULL) {
    DLGERROR("send_dialog_control_update: failed to locate dialog\n");
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }
  g2pvt_set_dialog_responses(found_dialog, control_id, DLG_RESPOND_ALL);
  ptr =  g2pvt_updated_control_value(found_dialog, control_id);
  send_dialog_update_event(found_dialog, control_id,
    ptr,
    G2_INITIATED_UPDATE);
  free(ptr); //hjg 02-24-2005 fix memory problems
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* long g2pvt_dismiss_dialog (GENSYMDIALOG *dialog, long respcode)
*
*   Description:
*   Input Arguments:
*   Returns:
*      success or failure
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2pvt_dismiss_dialog (GENSYMDIALOG *dialog, long respcode)
{
  long success_p = DYNAMIC_DIALOG_SUCCEEDED;

  if (respcode & DLG_APPLY_CHANGES) {
    success_p = g2pvt_send_dynamic_dialog_data_to_g2(dialog, TW_INITIATED_UPDATE);
  }

  if (respcode & DLG_CLIENT_SIDE_PROBLEM) {
    g2pvt_send_control_event(GhwndWin, GENSYM_DIALOG_DISMISSED,
      dialog->dialog_id, respcode, 0, 0);
  }

  // If closing a modal dialog, reenable those windows we disabled on posting.
  if (dialog->_iDlgType == MODAL)
    restore_enabled_windows(dialog);

  // GENSYMCID-539: GDU Demo - Dynamic Dialog Specification - Example not working
  // Send correct dialog id of dismissed dialog to server.
  if (success_p == DYNAMIC_DIALOG_SUCCEEDED) {
    g2pvt_send_control_event(GhwndWin, GENSYM_DIALOG_DISMISSED,
      dialog->dialog_id, respcode, 0, 0);
  }

  DestroyWindow(dialog->hwnd);

#ifdef DEBUG_DIALOG_LEAKS
  _CrtMemDumpAllObjectsSince(&g_memCheckPoint);
  _CrtMemCheckpoint(&g_memCheckPoint);
#endif

  return success_p;
}



/*****************************************************************************
* void g2pvt_cancel_all_dynamic_dialogs ()
*
*   Description:
*   Input Arguments:
*   Returns:
*
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_cancel_all_dynamic_dialogs ()
{
  GENSYMDIALOG *idialog, *next;

  for (idialog=list_of_dialogs; idialog != NULL; idialog=next) {
    next = idialog->next;
    g2pvt_dismiss_dialog(idialog, DLG_CANCEL);
  }
}



/*****************************************************************************
* void g2ext_abort_dialog (long pDialog)
*
*   Description:
*   Input Arguments:
*   Returns: nothing
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2ext_abort_dialog (long pDialog)
{
  GENSYMDIALOG *idialog;

  for (idialog=list_of_dialogs; idialog != NULL; idialog=idialog->next) {
    if (idialog->dialog_id == pDialog) {
      g2pvt_dismiss_dialog(idialog, DLG_CANCEL);
      // We could take this opportunity to do some consistency checking, and
      // verify that there are no other dialogs with the given id; but that
      // is really well beyond the purpose of this function, so instead, we'll
      // just jump out here.
      return;
    }
  }
}


/*****************************************************************************
* void g2ext_accept_dialog (long pDialog)
*
*   Description:
*   Input Arguments:
*   Returns: nothing
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2ext_accept_dialog (long pDialog)
{
  GENSYMDIALOG *idialog;

  for (idialog=list_of_dialogs; idialog != NULL; idialog=idialog->next) {
    if (idialog->dialog_id == pDialog) {
      g2pvt_set_dialog_responses(idialog, -1, DLG_RESPOND_ALL);
      g2pvt_dismiss_dialog(idialog, DLG_OK);
      return;
    }
  }
}

/*****************************************************************************
* void g2ext_lock_dialog (long pDialog)
*
*   Description:
*   Input Arguments:
*   Returns: nothing
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2ext_lock_dialog (long dialog_id, long locked_p)
{
  GENSYMDIALOG *idialog = g2pvt_find_dialog(dialog_id);

  if (idialog != NULL)
  {
    idialog->is_locked = locked_p;
    return;
  }
}

BOOL IsLockedDialog(HWND hWnd)
{
  GENSYMDIALOG *idialog = NULL;

  for (idialog = list_of_dialogs; idialog != NULL; idialog = idialog->next)
  {
    if (idialog->hwnd == hWnd)
    {
      return idialog->is_locked;
    }
  }
  return FALSE;
}

/*****************************************************************************
*   long g2ext_dialog_component_update (long, long, LPWSTR, long)
*
*   Description: Updates a specific control in a dialog with a new control value
*   Input Arguments: The dialog id, the control id, the text of the new control
*   value, a flag to indicate the type of update. Update types are defined by
*   the constants ADD, REPLACE, HIDE, SHOW, ENABLE, DISABLE, CHECK, UNCHECK
*   defined in dyndlgs.h
*   Returns: A success code (either DYNAMIC_DIALOG_UPDATE_SUCCEEDED or
*   DYNAMIC_DIALOG_UPDATE_FAILED)
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_dialog_component_update (long dlgId,
                                    long controlId,
                                    LPWSTR pText,
                                    long updateType)
{
  CONTROLITEM *control;
  GENSYMDIALOG *dialog;
  int len = 0;

  dialog = g2pvt_find_dialog_by_id(dlgId);
  if (!dialog) {
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  control= g2pvt_lookup_control_by_id(controlId, dialog);
  if (!control) {
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  if ((control->_type != ctPushBtn && control->_type != ctStatic && control->_type != ctToggleButton) || updateType == REPLACE) {
    // when (type = ctPushBtn or ctStatic or ctToggleButton) and updateType != REPLACE, pText is empty by default
    // no need to change text at all
    g2pvt_set_component_text(control, pText);
  }

  return g2pvt_update_dialog(dialog, control, updateType);
}


/*****************************************************************************
*   long g2ext_start_dialog_update (long)
*
*   Description:
*     Called to indicate the beginning of a dialog
*   Input Arguments:
*     A dialog id
*   Returns:
*     A success code (either DYNAMIC_DIALOG_UPDATE_SUCCEEDED or
*     DYNAMIC_DIALOG_UPDATE_FAILED)
*   Notes:
*     Currently does nothing because we do not buffer the updates yet.
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_start_dialog_update (long dlgId)
{
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
*   long g2ext_end_dialog_update(long)
*
*
*   Description: Called to indicate the end of a dialog update
*   Input Arguments: A dialog id
*   Returns: A success code (either DYNAMIC_DIALOG_UPDATE_SUCCEEDED or
*   DYNAMIC_DIALOG_UPDATE_FAILED)
*   Notes: Currently does nothing because we do not buffer the updates
*   yet
*
* *     -----
*   Modifications:
*****************************************************************************/
long g2ext_end_dialog_update (long dlgId)
{
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
*   long g2ext_end_dialog_update (long)
*
*   Description:
*     Called to abort a dialog update
*   Input Arguments:
*     A dialog id
*   Returns:
*     A success code (either DYNAMIC_DIALOG_UPDATE_SUCCEEDED or
*     DYNAMIC_DIALOG_UPDATE_FAILED)
*   Notes:
*     Currently does nothing because we do not buffer the updates yet.
*
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_abort_dialog_update (long dlgId)
{
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* long g2ext_manage_grid_view (long opcode, long dlgId, long controlId,
*                              long row, long col, LPWSTR label, LPWSTR data)
*
*   Description: stub for non-TWNG
*   Input Arguments:
*   Returns: -1
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
#ifndef CODEJOCK
long g2ext_manage_grid_view (long opcode, long dlgId, long controlId,
                             long row, long col, LPWSTR label, LPWSTR data)
{
  return -1;
}
#endif


/*****************************************************************************
* long g2ext_specify_grid_view_cells (long dlgId, long controlId, LPWSTR cell_spec)
*
*   Description: 
*   Input Arguments:
*   Returns: 
*
*   Notes: 
*     -----
*   Modifications:
*****************************************************************************/
#ifndef CODEJOCK
long g2ext_specify_grid_view_cells (long dlgId, long controlId, LPWSTR cell_spec)
{
  return -1;
}
#endif
