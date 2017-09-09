/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      w32_dyndlg.cpp
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):
+   MS Windows portions:
+              2004 - 2006      hjg, jv, mhd, lkasparek, ajs
+
+ Description:  Win32 Custom Native Dialog C++ routines
+
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
+
+ Modifications:
+   usage: All modifications to this file should be listed here, with most
+          recent first. In general, modification comments should merely
+          provide a reference to a detailed modification comment in the
+          appropriate section/function header.
+
+   02/13/05,  jv: Made most functions explicitly use wchar_t instead of
+                  TCHAR, and associated changes.
+
+   03/19/04,  jv: Created, from code written by Linda Kasparek for a dialogs
+                  test application.
+
+   5/22/04,  mhd: file is now defined with UNICODE/_UNICODE preprocessor
+                  flags defined.  Most functions and data are generic (TCHAR).
+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef UNICODE
#  define UNICODE
#endif

#ifndef _UNICODE
#  define _UNICODE
#endif

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      INCLUDE FILES
%
% Description:  All required include files are referenced here.
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
////////////////////////// TEMPORARY ////////////////////////////////////////
#ifdef _WIN32_IE
#  undef _WIN32_IE
#endif

#define _WIN32_IE  0x0400
/////////////////////////////////////////////////////////////////////////////

#include "dyndlgs.h"
#include "ddrsc.h"
#include "msincls.h"
extern "C" {
#include "cprim.h"
}
#include "graphics.h"
#include <assert.h>

/* VS2008 (VC9) need multimon.h for GetMonitorInfo(), and macro
   COMPILE_MULTIMON_STUBS must be defined for compiling this file.
   -- binghe, 2009/6/29
   Work for all VSs
 */
#ifndef COMPILE_MULTIMON_STUBS
#define COMPILE_MULTIMON_STUBS 1
#endif
#include <multimon.h>

#include <iostream>
using namespace std;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      GLOBALS
%
% Description:  Module specific typedefs, variables, & externs defined here
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define IDS_PLATFORM_WIN32_NT_STRING      L"Microsoft Windows NT %u.%u (Build %u)"
#define IDS_PLATFORM_WIN32s_STRING        L"Microsoft Win32s %u.%u (Build %u)"
#define IDS_PLATFORM_WIN32_WINDOWS_STRING L"Microsoft Windows 95 %u.%u (Build %u)"
#define IDS_PLATFORM_UNKNOWN_STRING       L"Unknown operating system %u.%u (Build %u)"

static const wchar_t ProductOptions []   =  L"SYSTEM\\CurrentControlSet\\Control\\ProductOptions";
static const wchar_t ProductType []      =  L"ProductType";

//  Windows NT Workstation is running
static const wchar_t WinNT []            =  L"WINNT";

//  Windows NT Server (3.5 or later) is running
static const wchar_t ServerNT []         =  L"SERVERNT";

//  Windows NT Advanced Server (3.1) is running
static const wchar_t AdvancedServerNT [] = L"LANMANNT";

typedef enum
{
  typeDefault        = 0,
  typeAdvancedServer = 1,
  typeWorkstation    = 2,
  typeServer         = 3
} NTTYPE;


// listview sort directions stored per column
#define ASCENDING   0
#define DESCENDING  1


#define COMBO_BOX_IGNORE_SELECTION  0
#define COMBO_BOX_SET_SELECTION     1
#define COMBO_BOX_DEFAULT_SELECTION 3

#define STD_COMBO_BOX               32
#define COLOR_PICKER                64


// See comments in comment-header of function create_win32_control for an
// explanation of these values.  -jv, 2/17/05
#define DIALOG_UNITS_PER_ROW                  8
#define ADDITIONAL_HEIGHT_FOR_COMBO_BOX_ROWS  16

#define SIZE_OF_DATE_TIME_STRING 22

#define EDIT_SEL_BUF_LEN 50 // big enough for selection index in character form
#define TOTAL_EDIT_SEL_BUF_LEN 102 /* big enough for  \002 + EDIT_SEL_BUF_LEN + \001 + EDIT_SEL_BUF_LEN */

#define UNICODE_LINE_SEPARATOR 0x2028

// progress-bar, track-bar, slider
typedef struct
{
  int bar_min;
  int bar_max;
  int bar_step;
  int bar_default;
} BARVALS;


static BOOL use_simple_text_boxes_p = TRUE;

static HBRUSH gv_hbrEditBG = NULL; // keep this for deletion later
static FARPROC lpfnOldTextBxProc;
static FARPROC lpfnOldComboBoxProc;

TCHAR m_DlgStrDelim[2]={'\001', 0};
TCHAR m_DlgStrDelim2[2]={'\002', 0};
TCHAR m_DlgEitherDelim[3]={'\001', '\002', 0};

#ifdef _DEBUG
static wchar_t szDebug[MAX_PATH] = {0};
#endif

// forward references -- wndprocs
LRESULT DynamicDlg_OnNotify (HWND hwndDlg, long control_id, NMHDR *pnmhdr);
LRESULT CALLBACK DynamicDlgProc (HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

void g2pvt_set_g2_selection(HWND hwndEdit, DWORD start, DWORD end);
void g2pvt_get_g2_selection(HWND hwndEdit, DWORD *pStart, DWORD *pEnd);


// begin extern "C" declarations

// external variables
extern "C" GENSYMDIALOG *list_of_dialogs;
extern "C" HANDLE hInst;
extern "C" HWND hwndFrame;
extern "C" HWND hwndMain;
extern "C" XCOLOR XMetaColorArray[];

// external functions
extern "C" CONTROLITEM *g2pvt_lookup_control_by_id (int controlId, GENSYMDIALOG *dialog);
extern "C" CONTROLITEM *g2pvt_lookup_control_by_hwnd (int controlId, HWND hwnd);
extern "C" long g2pvt_dismiss_dialog (GENSYMDIALOG *dialog, long respcode);
extern "C" long g2pvt_send_dynamic_dialog_data_to_g2 (GENSYMDIALOG *dialog,
                                                      long initiator);
extern "C" long g2pvt_send_tw_dialog_control_update (GENSYMDIALOG *dlg, long control_id);
extern "C" long g2pvt_send_wsv_hwnd_to_g2 (HWND hwndParent, CONTROLITEM *pControl, HWND hwndWSV);
extern "C" char *g2pvt_get_last_error_string (void);
extern "C" HICON g2pvt_get_native_icon(int icon);
extern "C" wchar_t *g2pvt_empty_wide_string (void);
extern "C" GENSYMDIALOG *g2pvt_find_dialog_by_id (long dlgId);
extern "C" BOOL g2pvt_validate_contents_if_buddy (HWND hwndTextBx, HWND hwndParent);

#ifdef _DEBUG
extern "C" char *string_of_control_type (long control_type);
#endif

// end of extern "C" declarations

extern long g2pvt_delete_all_grid_rows(long dialogid, long controlid);
extern long g2pvt_delete_all_grid_selected_rows(long dialogid, long controlid);
extern long g2pvt_get_grid_row_key_by_index (long dialogid, long controlid, int index);
extern long g2pvt_get_grid_selected_row_count(long dialogid, long controlid);
extern long g2pvt_get_grid_selected_row_index (long dialogid, long controlid, int start);

extern void g2pvt_get_tabular_info_tip (HWND hwndDlg, int idFrom, NMHDR *pnmhdr);
extern void g2pvt_tabular_column_click (HWND hwndDlg, int idFrom, NMHDR *pnmhdr);

#ifdef CODEJOCK
extern void g2pvt_set_twng_spin (CONTROLITEM *pctrl, HWND hwndCtrl, HWND hwndDlg);
extern TCHAR *g2pvt_control_value_of_twng_spinner (HWND hwndControl);
extern TCHAR *g2pvt_control_value_of_duration(HWND hwndControl);
extern LRESULT g2pvt_grid_view_on_wm_notify (NMHDR *pnmhdr, HWND hwndDlg,
                                             CONTROLITEM *pcontrol);
extern BOOL g2pvt_create_mfc_control (HWND hwndParent, CONTROLITEM *pcontrol, TABITEM *ptabitem);
extern void g2pvt_clear_mfc_control_data (CONTROLITEM *pcontrol);
extern void g2pvt_mfc_control_created_hook (HWND hwndParent, CONTROLITEM *pcontrol,
                                            TABITEM *ptabitem);
extern void g2pvt_set_duration_value (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg);
extern void g2pvt_process_advanced_color (WPARAM, HWND hWndDlg, CONTROLITEM *pControl);
extern long g2pvt_modify_mfc_control (CONTROLITEM *pcontrol, HWND hwndCtrl,
                                      HWND hwndDlg, wchar_t *value, int updateType);
extern TCHAR *g2pvt_control_value_of_combo_tree_view (HWND hwndControl);
extern TCHAR *g2pvt_control_value_of_check_listbox(HWND hwndControl, CONTROLITEM *pitem);
extern TCHAR *g2pvt_control_value_of_advanced_color(HWND hwndControl);
extern wchar_t *g2pvt_cell_value_of_last_gv_edit (HWND hwndControl);
extern wchar_t *g2pvt_get_contents_of_gensym_edit_control (HWND hwndControl,  CONTROLITEM *pitem);
extern long g2pvt_modify_twng_color_picker (HWND hwndCtrl, CONTROLITEM *pcontrol,
                                            wchar_t *new_value, int updateType);
extern BOOL g2pvt_check_list_box_wm_command (HWND hwndDlg, long controlId,
                                             CONTROLITEM *pcontrol, int notifyCode);

extern void g2pvt_init_G2TabWidget_resizable_child_dialog(HWND hwndTabCtrl, DIALOGINFO *dlgInfo);
extern wchar_t *g2pvt_get_contents_of_G2TabWidget_control(HWND hwndControl,  CONTROLITEM *pitem);
extern void g2pvt_cleanup_tab_pages (DIALOGINFO *pDialogInfo);
extern wchar_t *g2pvt_tabular_view_value(HWND hwndControl);
#endif

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Colour Related utilities
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* COLORREF g2pvt_get_color_ref_from_color_name(wchar_t* pColor)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     
*
*     -----
*   Modifications:
*****************************************************************************/

COLORREF g2pvt_get_color_ref_from_color_name(const wchar_t* pColor)
{
  COLORREF color=0;
  XCOLOR xcolor;
  const WCHAR *tempCol;
  for(int i=0;i<TOTAL_NUMBER_OF_COLORS;i++)
  {
    xcolor=XMetaColorArray[i];
    int nChars = MultiByteToWideChar(CP_ACP, 0, xcolor.szColor, -1, NULL, 0);
    tempCol = new WCHAR[nChars];
    MultiByteToWideChar(CP_ACP, 0, xcolor.szColor , -1, (LPWSTR)tempCol, nChars);
    if(_wcsicmp(pColor,tempCol)==0)
      return xcolor.rgbColor;
  }
  if(_wcsicmp(pColor,L"window")==0)
  {
    color=::GetSysColor(CTLCOLOR_DLG);
    return color;
  }
  return -1;
}





/*****************************************************************************
* RGBDEFINITION* g2pvt_get_color_from_color_name(wchar_t * pFontColor)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     It is called for getting the RGB colour values from the given input for
*     G2 dailog utility 
*
*     -----
*   Modifications:
*****************************************************************************/

RGBDEFINITION* g2pvt_get_color_from_color_name(const wchar_t * pFontColor)
{
  RGBDEFINITION *rgb=NULL;
  int r=0,g=0,b=0;
  COLORREF col=g2pvt_get_color_ref_from_color_name(pFontColor);
  if(col==-1)
    return NULL;
  rgb=(RGBDEFINITION*) malloc(sizeof(RGBDEFINITION));
  rgb->_blue=GetBValue(col);
  rgb->_green=GetGValue(col);
  rgb->_red=GetRValue(col);
  return rgb;
}




/*****************************************************************************
* RGBDEFINITION* g2pvt_get_default_background_color_for_control(CONTROLITEM* pcontrol)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     It is called for getting the default RGB colour values for the given 
*     control background.
*
*     -----
*   Modifications:
*****************************************************************************/

RGBDEFINITION* g2pvt_get_default_background_color_for_control(CONTROLITEM* pcontrol)
{
  switch (pcontrol->_type)
  {
    case ctTextBx:
    case ctMaskEdit:
    case ctToggleButton:
    case ctListBox:
    case ctCheckListBox:
    case ctComboTreeView:
    case ctComboBox: 
      return g2pvt_get_color_from_color_name(L"white");
    default: 
      return g2pvt_get_color_from_color_name(L"window");
  }
}





/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Text conversion utilities
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* char *g2pvt_simple_unicode_to_multibyte (wchar_t *pText)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     It is the caller's responsibility to reclaim the returned (ASCII) string,
*     as well as the original (wide) string.
*
*     -----
*   Modifications:
*****************************************************************************/
char *g2pvt_simple_unicode_to_multibyte (wchar_t *pText)
{
  int code_page = CP_ACP;
  char *buffer;
  int n_bytes  // first, just compute number of bytes needed for the result:
    = WideCharToMultiByte(code_page, // code page
                          0,         // flags
                          pText,     // wide string to be converted
                          -1,        // -1 to determine length by null termination
                          NULL,      // not used in this case
                          0,         // 0 to request size for result buffer
                          NULL,      // use default substitution character
                          NULL);     // don't record substitution

  if (n_bytes == 0) {
    g2pvt_gprintf(G2PVT_ERROR,
      "%s: failure in first call to WideCharToMultiByte: %s\n",
      "g2pvt_simple_unicode_to_multibyte",
      g2pvt_get_last_error_string());
    buffer = (char *)malloc(sizeof(char));
    if (buffer == NULL) {
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2pvt_simple_unicode_to_multibyte #1\n");
      return NULL;            // out of memory!
    }
    buffer[0] = 0;
    return buffer;
  }

  buffer = (char *)malloc(n_bytes);
  if (buffer == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2pvt_simple_unicode_to_multibyte #2\n");
    return NULL;            // out of memory!
  }
  if (WideCharToMultiByte(code_page,        // code page
                          0,                // flags
                          pText,            // wide string to be converted
                          -1,               // number of wide characters
                          buffer,           // buffer to receive converted string
                          n_bytes,          // the size, in bytes, of the buffer
                          NULL,
                          NULL)
      == 0) {
    fprintf(stderr,
      "g2pvt_simple_unicode_to_multibyte: failure in first call to WideCharToMultiByte: %s\n",
      g2pvt_get_last_error_string());
    char *nbuf = (char *)realloc(buffer, sizeof(char));
    if (nbuf == NULL) {
      free(buffer);
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2pvt_simple_unicode_to_multibyte #3\n");
      return NULL;            // out of memory!
    }
    nbuf[0] = 0;
    return nbuf;
  }

  return buffer;
}


/* g2pvt_is_multiline_string is TRUE if string contains any CR, LF, or Unicode
   newline characters. */
BOOL g2pvt_is_multiline_string(LPCWSTR string)
{
  LPCWSTR s;
  for(s=string; *s; s++)
    if(*s == UNICODE_LINE_SEPARATOR || *s == L'\n' || *s == L'\r')
      return TRUE;
  return FALSE;
}


/*****************************************************************************
* wchar_t *g2pvt_g2_to_windows_text (wchar_t *str)
*
*   Description: allocates a new wide string with line breaks encoded using the
*     Unicode/G2 linebreak encoding (Unicode line separator, U+2028) to that of
*     Windows (CRLF).
*   Input Arguments:
*   Returns: does the same thing as wide_string_copy() but also
*     converts Unicode/G2 line separators, U+2028, to Windows CRLF.
*   Notes:
*     It is the caller's responsibility to reclaim the returned (wide or
*     narrow) string, as well as the original (wide) string.
*   Modifications:
*****************************************************************************/
wchar_t *g2pvt_g2_to_windows_text (wchar_t *pText)
{
  wchar_t *rval, *p, *r;
  int len = 0;
  wchar_t uls = UNICODE_LINE_SEPARATOR,
    cr = 0xD, lf = 0xA, nul = 0;
  int n_windows_chars_per_line_sep = 2;

  for (p = pText; *p != nul; p++)
    len = len + ((*p == uls) ? n_windows_chars_per_line_sep : 1);
  rval = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
  if (rval == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2pvt_g2_to_windows_text\n");
    return NULL;            // out of memory!
  }
  for (p = pText, r = rval; *p != nul; p++) {
    if (*p == uls) {
      *r = cr;
      r++;
      *r = lf;
      r++;
    } else {
      *r = *p;
      r++;
    }

  }
  *r = nul;
  return rval;
}


/*****************************************************************************
* wchar_t *g2pvt_windows_to_g2_text (wchar_t *str)
*
*   Description: allocates a new wide string, converting Windows CRLF line
*     breaks G2/Unicode line separator, U+2028
*   Description: allocates a new wchar_t
*     string with line breaks encoded using the Windows encoding (CRLF)
*     converted to that of G2 (Unicode line separator, U+2028)
*   Input Arguments: a wide string
*   Returns: the new wide string
*   Notes:
*     - It is the caller's responsibility to reclaim the returned (wide)
*     string, as well as the original (wide) string.
*     - For generality this also converts standalone CR's and LF's.
*     -----
*   Modifications:
*****************************************************************************/
wchar_t *g2pvt_windows_to_g2_text (wchar_t *pText)
{
  wchar_t *rval, *p, *r;
  int len = 0;
  wchar_t uls = UNICODE_LINE_SEPARATOR,
    cr = 0xD, lf = 0xA, nul = 0;
  wchar_t prev;
  int n_g2_chars_per_line_sep = 1;

  for (p = pText, prev = nul; *p != nul; p++) {
    if ((*p == cr) || (*p == lf)) {
      if  (!((*p == lf) && (prev == cr)))
        len = len + n_g2_chars_per_line_sep;
    } else len++;
    prev = *p;
  }
  rval = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
  if (rval == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2pvt_windows_to_g2_text\n");
    return NULL;            // out of memory!
  }
  for (p = pText, prev = nul, r = rval; *p != nul; p++) {
    if ((*p == cr) || (*p == lf)) {
      if  (!((*p == lf) && (prev == cr))) {
        *r = uls;
        r++;
      }
    }
    else {
      *r = *p;
      r++;
    }
    prev = *p;
  }
  *r = nul;
  return rval;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Preliminary functions
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* CONTROLHWND *g2pvt_get_control_hwnd_by_controlId (DIALOGINFO *pdlgInfo,
*                                                   long controlId)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CONTROLHWND *g2pvt_get_control_hwnd_by_controlId (DIALOGINFO *pdlgInfo,
                                                  long controlId)
{
  long j;
  CONTROLHWND *pcontrolhwnd = pdlgInfo->_controlHwndList;

  for (j=0; j<pdlgInfo->_numControlHwnds; j++) {
    if (controlId == pcontrolhwnd->controlId) {
      return pcontrolhwnd;
    }
    pcontrolhwnd = pcontrolhwnd->next;
  }

  // If we get here, we didn't find it;
  return NULL;
}


/*****************************************************************************
* BOOL g2pvt_add_control_hwnd (CONTROLHWND *pControlHwnd, HWND hwnd)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL g2pvt_add_control_hwnd (CONTROLHWND *pControlHwnd, HWND hwnd)
{
  DIALOGINFO *pDialogInfo;

  pDialogInfo = (DIALOGINFO *)GetWindowLong(hwnd, GWLP_USERDATA);
  if (pDialogInfo == NULL) {
    return FALSE;
  }

  // Notice we are adding it to the front (a stack).  If for some reason this
  // is a problem with other code (I took a look and don't think it is), we
  // can change this to put it on the end.
  pControlHwnd->next = pDialogInfo->_controlHwndList;

  pDialogInfo->_controlHwndList = pControlHwnd;
  pDialogInfo->_numControlHwnds++;

  return TRUE;
}


/*****************************************************************************
* HWND g2pvt_get_dlg_item_hwnd (HWND hwndDlg, long controlId)
*
*   Description: very much like Windows API function GetDlgItem: it takes the
*     HWND of a dialog and an identifier, and returns the HWND of the control
*     which has that identifier.  We cannot rely on GetDlgItem() because we
*     could have embedded dialog windows in the case of embedded tabs.
*
*   Input Arguments:
*   Returns:
*   Notes:
*     jv, 3/26/05: removed two existing comments, made partially obsolete
*     by the above description.  The thing which still seems weird to me is
*     that there's no direct way to get the HWND from the CONTROLITEM.
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C"
HWND g2pvt_get_dlg_item_hwnd (HWND hwndDlg, long controlId)
{
  DIALOGINFO *pDialogInfo;
  CONTROLHWND *pControlHwnd;

  pDialogInfo = (DIALOGINFO *)GetWindowLong(hwndDlg, GWLP_USERDATA);

  if (pDialogInfo == NULL) {
    return NULL;
  }

  pControlHwnd = g2pvt_get_control_hwnd_by_controlId(pDialogInfo, controlId);

  // It's possible for hwndControl to be an invalid HWND if the control is a
  // native view, and was deleted out from under dialogs via the view API.
  // Users are not supposed to do that, and we may prevent it in G2, but only
  // the paranoid survive. -fmw, 2/17/06
  return ((pControlHwnd && IsWindow(pControlHwnd->hwndControl))
          ? pControlHwnd->hwndControl : NULL);
}


/*****************************************************************************
* BOOL g2pvt_get_name_of_control_type (int type, wchar_t *szClassName)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: this really should take the size of the buffer as an argument
*     and verify that the class name is not too big.
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL g2pvt_get_name_of_control_type (int type, wchar_t *szClassName)
{
  BOOL bRet = TRUE;

  switch (type)
  {
  case ctTabs: // use the same class name for TW and TWNG tabs
    wcscpy(szClassName, GDD_TABS);
    break;

  case ctProgressBar:
    wcscpy(szClassName, GDD_PROGRESS);
    break;

  case ctTrackBar:
    wcscpy(szClassName, GDD_TRACKBAR);
    break;

  case ctSlider:
    wcscpy(szClassName, GDD_SLIDER);
    break;

  case ctComboTreeView:
  case ctComboBox:
    wcscpy(szClassName, GDD_COMBO);
    break;

  case ctColor:
    wcscpy(szClassName, GDD_COLOR);
    break;

  case ctAdvancedColor:
    wcscpy(szClassName, GDD_ADVANCEDCOLOR);
    break;

  case ctCheckListBox: // twng only
    wcscpy(szClassName, GDD_CHECKLISTBOX);
    break;

  case ctListBox:
    wcscpy(szClassName, GDD_LIST);
    break;

  case ctTextBx:
    wcscpy(szClassName, GDD_TEXT);
    break;

  case ctMaskEdit:
    wcscpy(szClassName, GDD_MASKEDIT);
    break;

  case ctStatic:
    wcscpy(szClassName, GDD_STATIC);
    break;

  case ctIcon:
    wcscpy(szClassName, GDD_STATIC);
    break;

  case ctSpin:
    wcscpy(szClassName, GDD_SPIN);
    break;

  case ctDuration:
    wcscpy(szClassName, GDD_DURATION);
    break;

//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctShortDuration:
    wcscpy(szClassName, GDD_SHORTDURATION);
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls

  case ctCalendar:
    wcscpy(szClassName, GDD_CALENDAR);
    break;

  case ctTimeOfDay:
    wcscpy(szClassName, GDD_TIMEOFDAY);
    break;

  case ctWorkspace:
    wcscpy(szClassName, GDD_WORKSPACE);
    break;

  case ctGroup:
    wcscpy(szClassName, GDD_GROUPBOX);
    break;

  case ctRadio:
    wcscpy(szClassName, GDD_RADIOBUTTON);
    break;

  case ctCheck:
    wcscpy(szClassName, GDD_CHECKBOX);
    break;

  case ctToggleButton:
    wcscpy(szClassName, GDD_TOGGLEBUTTON);
    break;

  case ctPushBtn:
    wcscpy(szClassName, GDD_PUSHBUTTON);
    break;

  case ctTabularView:
    wcscpy(szClassName, GDD_GRID);
    break;

  case ctGridView:
    wcscpy(szClassName, GDD_RICHGRID);
    break;

  default:
    bRet = FALSE;
    break;

    }

    return bRet;
}


/*****************************************************************************
 * LONG GensymContainerWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
 *
 *   Description: A class which simply resizes its sole child window to fit.
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
static LONG WINAPI GensymContainerWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (message == WM_SIZE) {
    HWND child = GetWindow(hwnd,GW_CHILD);
    if (child && wParam != SIZE_MINIMIZED)
      SetWindowPos(child, HWND_BOTTOM, 0, 0,
                   LOWORD(lParam), HIWORD(lParam),
                   SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
  }
  return DefWindowProcW(hwnd, message, wParam, lParam);
}


/*****************************************************************************
* void register_gensym_controls_if_needed(void)
*
*   Description: Register window classes needed for child controls.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void register_gensym_controls_if_needed(void)
{
  WNDCLASSW wc;
  static int done = 0;

  if (done) return;

  wc.style = 0;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = (HINSTANCE)hInst;
  wc.hIcon = NULL;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszMenuName = (LPCTSTR)NULL;
  wc.lpfnWndProc = (WNDPROC) GensymContainerWndProc;
  wc.lpszClassName = G2_CONTAINER_CLASS;
  RegisterClassW(&wc);
  done = 1;
}

/* Return pointer to the extra data for a text box. */
static EXTRA_TEXTBX_DATA *get_textbox_data(HWND hwndDlg, HWND hwndEdit)
{
  CONTROLITEM *pControl = g2pvt_lookup_control_by_hwnd(GetDlgCtrlID(hwndEdit), hwndDlg);

  return (pControl && pControl->_pExtraTypeData) ?
    (EXTRA_TEXTBX_DATA *) pControl->_pExtraTypeData->_pData
    : NULL;
}

/*****************************************************************************
* LRESULT CALLBACK SubClassTextBxFunc (HWND hWnd, UINT Message, WPARAM wParam, LONG lParam)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static LRESULT CALLBACK SubClassTextBxFunc (HWND hWnd, UINT Message,
                                            WPARAM wParam, LONG lParam)
{
  HWND hwndDlg = GetParent(hWnd);
  EXTRA_TEXTBX_DATA *pTBData;
  LRESULT result;

  switch(Message)
    {
     case WM_GENSYM_UPDATE_TEXT_BOX:
       pTBData = (EXTRA_TEXTBX_DATA*)wParam;
       if (pTBData->bSelectionValuesSetByUser)
	 g2pvt_set_g2_selection(hWnd, pTBData->start, pTBData->end);  // select the text
       break;

     case WM_GETDLGCODE:
       // NOTE: Code is duplicated in CGensymEditBox::OnGetDlgCode()
       result = CallWindowProc((WNDPROC)lpfnOldTextBxProc, hWnd, Message, wParam, lParam);
       pTBData = get_textbox_data(hwndDlg, hWnd);
       if(pTBData && pTBData->bSelectionValuesSetByUser)
	 result &= ~DLGC_HASSETSEL;
       return result;

    // case WM_KEYDOWN: // the user did something, tell G2 about it
    //   if(wParam == VK_SHIFT || wParam == VK_CONTROL) break;

     case WM_LBUTTONUP:
       // Simulate EN_SELCHANGE
       // NOTE: Code is duplicated in CGensymEditBox::OnKeyDown(), etc.
       result = CallWindowProc((WNDPROC)lpfnOldTextBxProc, hWnd, Message, wParam, lParam);
       SendMessage(hwndDlg, WM_GENSYM_SEND_INFO_TO_G2, (WPARAM)hWnd, (LPARAM)0);
       return result;
    }

  return CallWindowProc((WNDPROC)lpfnOldTextBxProc, hWnd, Message, wParam, lParam);
}

/*****************************************************************************
* LRESULT CALLBACK SubClassComboBoxFunc (HWND hWnd, UINT Message, WPARAM wParam, LONG lParam)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*   This ComboBox window gets subclassed only if it is type CBS_DROPDOWN or CBS_SIMPLE.
*
*
*     -----
*   Modifications:
*****************************************************************************/
static LRESULT CALLBACK SubClassComboBoxFunc (HWND hWndEditBox, UINT Message,
                                            WPARAM wParam, LONG lParam)
{
  CONTROLITEM *pcontrol = NULL;
  HWND hWndComboBox;
  HWND hWndDlgBox;

  switch(Message)
  {
    case WM_KEYDOWN: // the user did something, tell G2 about it
    case WM_LBUTTONUP:

      hWndComboBox = GetParent(hWndEditBox);   // we sublassed the edit window...
      hWndDlgBox = GetParent(hWndComboBox); // whose parent is the combobox...
      // whose parent is the dialog box, where we send the message
      SendMessage(hWndDlgBox, WM_GENSYM_SEND_INFO_TO_G2, (WPARAM)hWndComboBox, (LPARAM)0);

    break;

  }
  return CallWindowProc((WNDPROC)lpfnOldComboBoxProc, hWndEditBox, Message, wParam, lParam);

}




/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Memory Reclamation and Cleanup
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* void cleanup_control_hwnds (DIALOGINFO *pDialogInfo)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*   01-11-2006-hjg- we no longer need extern void g2pvt_cleanup_mfc_controls because
    the MFC controls have been changed to auto delete
*****************************************************************************/
static void cleanup_control_hwnds (DIALOGINFO *pDialogInfo)
{
  CONTROLHWND *pControlHwnd;
  CONTROLHWND *pControlHwndNext;
  //Gensym-170-HQ-5699700-TWNG GDI leak
  HICON hIcon;
  //Gensym-170-HQ-5699700-TWNG GDI leak 

  if (pDialogInfo == NULL) {
    return;
  }

  pControlHwndNext = pDialogInfo->_controlHwndList;
  for (int i = 0; i < pDialogInfo->_numControlHwnds; i++) {
    pControlHwnd = pControlHwndNext;
    pControlHwndNext = pControlHwnd->next;
	//Gensym-170-HQ-5699700-TWNG GDI leak
	hIcon = (HICON)SendMessage(pControlHwnd->hwndControl, STM_GETICON, 0, 0);
	if(hIcon)
		DestroyIcon(hIcon);

	hIcon = (HICON)SendMessage(pControlHwnd->hwndControl, BM_GETIMAGE, IMAGE_ICON, 0);
	if(hIcon)
		DestroyIcon(hIcon);
	//Gensym-170-HQ-5699700-TWNG GDI leak
    delete pControlHwnd;
  }
  pDialogInfo->_controlHwndList = NULL;
  pDialogInfo->_numControlHwnds = 0;
}


/*****************************************************************************
* void cleanup_dialog_control_responses (GENSYMDLGRESPONSE *pdlgresponse)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void cleanup_dialog_control_responses (GENSYMDLGRESPONSE *pdlgresponse)
{
  int i = 0;

  for (i = 0; i < pdlgresponse->response_count; i++) {
    if (pdlgresponse->presponses[i]) {
      if(pdlgresponse->presponses[i]->_mResponseString)
 	free(pdlgresponse->presponses[i]->_mResponseString);
      delete pdlgresponse->presponses[i];
      pdlgresponse->presponses[i] = NULL;
    }
  }

  delete pdlgresponse->presponses; // Use array delete here?
  pdlgresponse->presponses = NULL;
}


/*****************************************************************************
* void g2pvt_clear_text_box_extra_data (EXTRA_TEXTBX_DATA *pTBData)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: LIMIT_TEXT_BOXES
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_clear_text_box_extra_data (EXTRA_TEXTBX_DATA *pTBData)
{
  ZeroMemory((LPVOID)pTBData, sizeof(EXTRA_TEXTBX_DATA));

  pTBData->bSelectionValuesSetByUser = FALSE;
  pTBData->bTxColorValueSetByUser = FALSE;
  pTBData->bBGColorValueSetByUser = FALSE;
  pTBData->start = 0;
  pTBData->end = 0;
  pTBData->textColor = (COLORREF) 0;
  pTBData->backgroundColor = (COLORREF) 0;
}


/*****************************************************************************
 * void free_extra_data (CONTROLITEM *p_new_item)
 *
 *   Description:
 *     Some controls require extra information. pControl->_pExtraTypeData was
 *     added for this purpose.  For any control that needs the extra information,
 *     _pExtraTypeData is allocated. Based on the type of control,
 *     _pExtraTypeData->_pData, points to the specific information needed.
 *
 *   Input Arguments:
 *   Returns:
 *   Notes: The grid-view uses _pExtraTypeData, but cleans it up on its own.
 *     We don't expect this function to be useful for the grid-view, so we don't
 *     have a check for it in the code below.  -jv, 11/11/05
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
static void free_extra_data (CONTROLITEM *p_new_item)
{
  EXTRA_TYPE_DATA *pETData;
  EXTRA_COMBO_TREE_VIEW_DATA *pCTVData;

  if (p_new_item)
  {
    pETData = p_new_item->_pExtraTypeData;
    if (pETData)
    {
      if (ctComboTreeView == pETData->_type) {
        pCTVData =  (EXTRA_COMBO_TREE_VIEW_DATA *)pETData->_pData;
        free(pCTVData);
        pETData->_pData = 0;
      } else if (ctPushBtn == pETData->_type) {
        EXTRA_PUSH_BUTTON_DATA *pPBData = NULL;

        pPBData = (EXTRA_PUSH_BUTTON_DATA *)pETData->_pData;
        if (pPBData) {
          if (pPBData->m_hwndTip) {
            DestroyWindow(pPBData->m_hwndTip);
            pPBData->m_hwndTip = NULL;
          }
          free(pPBData);
        }
        pETData->_pData = NULL;

      } else if (ctTextBx == pETData->_type) {
	EXTRA_TEXTBX_DATA *pData = (EXTRA_TEXTBX_DATA *)pETData->_pData;
	if(pData) free(pData);
	pETData->_pData = 0;
      }
    }
    free(pETData);
    p_new_item->_pExtraTypeData = 0;
  }
}


/*****************************************************************************
* void cleanup_dialog_controls (GENSYMDIALOG *dialog)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void cleanup_dialog_controls (GENSYMDIALOG *dialog)
{
  CONTROLITEM **controls;
  CONTROLITEM *pcontrol = NULL;

  if (dialog == NULL)                // Sometimes happens during TWNG shutdown.
    return;

  controls = dialog->pcontrols;

  if (controls == NULL) {
    return;
  }

  for (int i = 0; i < dialog->control_count; i++) {
    pcontrol = controls[i];
    if (pcontrol == NULL) {
      continue;
    }

#ifdef CODEJOCK
  g2pvt_clear_mfc_control_data(pcontrol);
#endif

    free(pcontrol->_parentControlText);
    pcontrol->_parentControlText = NULL;
    free(pcontrol->_mText);
    pcontrol->_mText = NULL;
    if (pcontrol->_pExtraTypeData) // if extra data was allcated for this control, free it.
      free_extra_data(pcontrol);

    free(pcontrol);
  }

  free(controls);
  dialog->control_count = 0;
  dialog->pcontrols = NULL;
}


/*****************************************************************************
* void cleanup_dialog_structures (HWND hwndDlg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void cleanup_dialog_structures (HWND hwndDlg)
{
  DIALOGINFO *dlgInfo = NULL;
  GENSYMDIALOG *dialog, *dlg;
  BOOL dialog_is_modal = FALSE;
  long succeeded = DYNAMIC_DIALOG_FAILED;

  dlgInfo = (DIALOGINFO *)GetWindowLong(hwndDlg, GWLP_USERDATA);

  if (dlgInfo == NULL)                // Sometimes happens during TWNG shutdown.
    return;

  dialog = dlgInfo->_pdialog;

  if (dialog == NULL)                // Sometimes happens during TWNG shutdown.
    return;

#ifdef _DEBUG
  if (hwndDlg != dialog->hwnd) {
    g2pvt_gprintf(G2PVT_ERROR, "Error in cleanup_dialog_structures: dialog's hwnd");
    g2pvt_gprintf(G2PVT_ERROR, "does not match hwnd which received event\n");
  }
#endif

  // remove dialog structure from the list
  if (list_of_dialogs == dialog) {
    list_of_dialogs = list_of_dialogs->next;
    succeeded = DYNAMIC_DIALOG_SUCCEEDED;
  } else {
    for (dlg = list_of_dialogs; dlg->next != NULL; dlg = dlg->next) {
      if (dlg->next == dialog) {
        dlg->next = dialog->next;
        succeeded = DYNAMIC_DIALOG_SUCCEEDED;
        break;
      }
    }
  }

  cleanup_control_hwnds(dlgInfo);
  cleanup_dialog_controls(dialog);
#ifdef CODEJOCK
  g2pvt_cleanup_tab_pages(dlgInfo);
#endif

  if (dialog->mResponse) {	// Can be NULL if dialog dismissed programmatically.
    cleanup_dialog_control_responses(dialog->mResponse);
    free(dialog->mResponse);
    dialog->mResponse = NULL;
  }

  if (dlgInfo->resizer)
    g2pvt_resizer_free(dlgInfo->resizer);
  dlgInfo->resizer = NULL;

  dialog->next = NULL;
  free(dialog->_mTitle);

  if (dlgInfo->hbrBackground) {
    DeleteObject(dlgInfo->hbrBackground);
    dlgInfo->hbrBackground = NULL;
  }

  if(dialog->enabledWindows)
    free(dialog->enabledWindows);
  dialog->enabledWindows = NULL;

  dlgInfo->_pdialog = NULL;
  // when do we clean up dlgInfo?
  // Looks like never?  Why not here? - dbk
  // Why not indeed. -fmw, 6/19/07
  SetWindowLong(hwndDlg, GWLP_USERDATA, 0);
  free(dlgInfo);

  // Gensym-683-TAM1-CN-BF-JIRA-224-More TWNG leaks involving native dialogs
  // GENSYMCID-867: TWNG dialog callback problem
  // Following code has been moved to `remove-dialog-given-client-id' (dialog.lisp)
  // This g2 pointer will be used by lisp variable `alist-of-dialog-mappings', cannot decache here.
  // -- Jingtao Xu, 2012/10/24
  // g2ext_decache_g2pointer(dialog->dialog_id);

  g2ext_decache_g2pointer(dialog->dialog_g2pointer);

  free(dialog);
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Control "getters"
%
% Description: "gets" the value of a control and turns it into a string to
%   be sent to G2
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* wchar_t *get_control_value_of_progress_bar (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns: Newly malloc'd wide string or NULL.
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_progress_bar (HWND hwndControl)
{
  wchar_t pszValue[33];
  UINT currentPos = 0;

  currentPos = SendMessage(hwndControl, PBM_GETPOS, 0, 0);

  swprintf(pszValue, L"%d", currentPos);

  return wcsdup(pszValue);
}


/*****************************************************************************
* wchar_t *get_control_value_of_track_bar (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns: Newly malloc'd wide string or NULL.
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_track_bar (HWND hwndControl)
{
  wchar_t pszValue[33];
  UINT currentPos = 0;

  currentPos = SendMessage(hwndControl, TBM_GETPOS, 0, 0);

  swprintf(pszValue, L"%d", currentPos);

  return wcsdup(pszValue);
}


/*****************************************************************************
*  wchar_t *get_control_value_of_combo_tree_view (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
wchar_t *get_control_value_of_combo_tree_view (HWND hwndControl)
{
  wchar_t *cbSelectedRowValue = NULL, *g2_combobox_text = NULL;

#ifdef CODEJOCK
  cbSelectedRowValue = g2pvt_control_value_of_combo_tree_view(hwndControl);
  g2_combobox_text = g2pvt_windows_to_g2_text(cbSelectedRowValue);

  free(cbSelectedRowValue);
#endif
  return g2_combobox_text;
}


/*****************************************************************************
* wchar_t *g2pvt_contents_of_edit_control (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns: a freshly malloc'ed wide string, or NULL
*   Notes: it is the caller's responsibility to free the returned value.
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C"
wchar_t *g2pvt_contents_of_edit_control (HWND hwndControl)
{
  wchar_t *pszValue = NULL;
  int nLen = 0;

  // get the length of the text associated with the edit control
  // does not include null terminator
  nLen = SendMessage(hwndControl, WM_GETTEXTLENGTH, 0, 0);

  pszValue = (wchar_t *)malloc((nLen+1) * sizeof(wchar_t));
  if (pszValue == NULL) {
    return NULL;            // out of memory!
  }
  ZeroMemory((PVOID)pszValue, sizeof(wchar_t) * (nLen + 1));
  SendMessage(hwndControl, WM_GETTEXT, nLen+1, (LPARAM)pszValue);

  return pszValue;
}

/*****************************************************************************
* void get_edit_box_selection (HWND hwndControl, wchar_t *pRetString)
*
*   Description: add the ComboBox EditBox Selection to end of return string
*   Input Arguments: the HWND of the control, and a buffer in which to return
*     the string
*   Returns: nothing (directly)
*   Notes:
*****************************************************************************/
static void get_edit_box_selection (HWND hwndControl, wchar_t *pRetString)
{
  WPARAM GetWparam;
  LPARAM GetLparam;
  LRESULT result;
  wchar_t begin_buf[EDIT_SEL_BUF_LEN]; // big enough to hold begin edit selection
  wchar_t end_buf[EDIT_SEL_BUF_LEN];   // big enough to hold end edit selection

  result= SendMessage(hwndControl, CB_GETEDITSEL, (WPARAM)&GetWparam, (LPARAM)&GetLparam);
  // add on selections
  if (CB_ERR != result)
  {
    _itow(GetWparam, begin_buf, 10);
    _itow(GetLparam, end_buf, 10);

    wcscat(pRetString, m_DlgStrDelim2);
    wcscat(pRetString, m_DlgStrDelim);
    wcscat(pRetString, begin_buf);
    wcscat(pRetString, m_DlgStrDelim2);
    wcscat(pRetString, end_buf);
  }
}


/*****************************************************************************
* wchar_t *get_control_value_of_combo_box (int control_id, HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_combo_box (HWND hwndControl)
{
  int nCbCurSel = 0, nCbLen = 0;
  DWORD dwCbStyle;
  wchar_t *selectedRowValue = NULL, *g2_combobox_text = NULL;
  wchar_t *pNewBuf;

  dwCbStyle = GetWindowLong(hwndControl, GWL_STYLE);

  if (dwCbStyle & CBS_DROPDOWN) {
    // get the text associated with the edit control
    selectedRowValue = g2pvt_contents_of_edit_control(hwndControl);
    if (selectedRowValue == NULL) {
      return NULL;
    }
    // new buffer with big enough for selections at the end
    pNewBuf = (wchar_t*)malloc((wcslen(selectedRowValue) + 1 + TOTAL_EDIT_SEL_BUF_LEN) * sizeof(wchar_t));
    wcscpy(pNewBuf, selectedRowValue);
    free(selectedRowValue);

    get_edit_box_selection(hwndControl, pNewBuf); //get selections

    // fix text for G2:
    g2_combobox_text = g2pvt_windows_to_g2_text(pNewBuf);
    free(pNewBuf);

    return g2_combobox_text;
  }

  // get the current selection
  nCbCurSel = SendMessage(hwndControl, CB_GETCURSEL, 0, 0);

  nCbLen = -1;
  if (nCbCurSel != CB_ERR) {
    // get the length of the text
    nCbLen = SendMessage(hwndControl, CB_GETLBTEXTLEN, nCbCurSel, 0);
  }

  if (nCbLen <= 0) {
    return NULL;
  }
  nCbLen += TOTAL_EDIT_SEL_BUF_LEN;  // add a large enough amount for new begin and end selection

  selectedRowValue = (wchar_t *)malloc((nCbLen+1) * sizeof(wchar_t));
  if (selectedRowValue == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_value_of_combo_box\n");
    return NULL;            // out of memory!
  }
  ZeroMemory((PVOID)selectedRowValue, sizeof(wchar_t) * nCbLen);

  // get the text
  SendMessage(hwndControl, CB_GETLBTEXT, nCbCurSel, (LPARAM)selectedRowValue);
  get_edit_box_selection(hwndControl, selectedRowValue);

  // fix text for G2:
  g2_combobox_text = g2pvt_windows_to_g2_text(selectedRowValue);
  free(selectedRowValue);

  return g2_combobox_text;
}


/*****************************************************************************
* wchar_t *get_control_value_of_single_selection_list (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_single_selection_list (HWND hwndControl)
{
  wchar_t *pszValue = NULL;
  wchar_t *text_copy = NULL;
  int nCurSel = 0;
  int nLen = 0;

  // get the current selection
  nCurSel = SendMessage(hwndControl, LB_GETCURSEL, 0, 0);

  nLen = -1;
  if (nCurSel != LB_ERR) {
    // get the length of the selected text
    nLen = SendMessage(hwndControl, LB_GETTEXTLEN, nCurSel, 0);
  }

  // FIXME: Why aren't we allowing zero-length strings?
  if (nLen > 0) {
    // allocate and get
    pszValue = (wchar_t*) malloc((nLen+3)*sizeof(wchar_t));//hjg 02-24-2006 fix memory problems
    if (pszValue == NULL) {
      return NULL;            // out of memory!
    }

    ZeroMemory((PVOID)pszValue, sizeof(wchar_t) * (nLen + 3));

    SendMessage(hwndControl, LB_GETTEXT, nCurSel, (LPARAM)pszValue);
    // FIXME: nLen is not guarenteed to equal the length of pszValue. See MSDN
    // doc for LB_GETTEXTLEN.
    pszValue[nLen] = m_DlgStrDelim[0];
    pszValue[nLen+1] = m_DlgStrDelim2[0];
    pszValue[nLen+2] = '\000';

    // fix text for G2:
    text_copy = g2pvt_windows_to_g2_text(pszValue);
    free(pszValue);
    pszValue = text_copy;
  } else {
    pszValue = (wchar_t*) malloc(2*sizeof(wchar_t));
    pszValue[0] = m_DlgStrDelim2[0];
    pszValue[1] = 0;
  }

  return pszValue;
}


/*****************************************************************************
* wchar_t *get_control_values_of_multiple_selection_list (HWND hwndControl)
*
*   Description: gets the selected entries for G2
*   Input Arguments: the HWND of the list-box
*   Returns: a string containing the selected entries
*   Notes:
*
*     -----
*   Modifications: rewritten as of 8.3a1 -jv, 9/21/06
*****************************************************************************/
static wchar_t *get_control_values_of_multiple_selection_list (HWND hwndControl)
{
  wchar_t *pszBigBuf = NULL, *return_string = NULL;
  int *pSelectedItems = NULL;
  wchar_t **pszSelectionEntries = NULL;
  int nNumItems = 0, nLen = 0, nTotalLen = 0, nOffset = 0, i = 0;

  // get the current selections
  nNumItems = SendMessage(hwndControl, LB_GETSELCOUNT, 0, 0);
  if ((LB_ERR == nNumItems) || (0 == nNumItems)) {
    return g2pvt_empty_wide_string();
  }

  // Windows limit on 95/98/Me
  if (nNumItems > 32767) {
    return g2pvt_empty_wide_string();
  }

  // allocate space to get selected entries
  pSelectedItems = (int *)malloc(nNumItems * sizeof(int));
  if (NULL == pSelectedItems) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_values_of_multiple...\n");
    return NULL; // out of memory
  }
  pszSelectionEntries = (wchar_t **)malloc(nNumItems * sizeof(wchar_t *));
  if (NULL == pszSelectionEntries) {
    free(pSelectedItems);
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_values_of_multiple...\n");
    return NULL; // out of memory
  }

  // find out which entries are the selected ones
  nNumItems = SendMessage(hwndControl, LB_GETSELITEMS, nNumItems, (long)pSelectedItems);
  if ((LB_ERR == nNumItems) || (0 == nNumItems)) {
    free(pSelectedItems);
    free(pszSelectionEntries);
    return g2pvt_empty_wide_string();
  }

  // get the strings of the selected entries
  nTotalLen = 0;
  for (i=0; i < nNumItems; i++) {
    // get the length of the selected text
    nLen = SendMessage(hwndControl, LB_GETTEXTLEN, *(pSelectedItems+i), 0);
    if ((LB_ERR == nLen) || (0 == nLen)) {
      for (int j = 0; j < i; ++i) {
	free(pszSelectionEntries[j]);
      }
      g2pvt_gprintf(G2PVT_ERROR, "Unable to obtain text length in list-box.\n");
      free(pSelectedItems);
      free(pszSelectionEntries);
      return g2pvt_empty_wide_string();
    }
    pszSelectionEntries[i] = (wchar_t *)malloc((nLen+1) * sizeof(wchar_t));
    if (pszSelectionEntries[i] == NULL) {
      for (int j = 0; j < i; ++i) {
	free(pszSelectionEntries[j]);
      }
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_values_of_multiple...\n");
      free(pSelectedItems);
      free(pszSelectionEntries);
      return NULL;            // out of memory!
    }
    ZeroMemory((PVOID)pszSelectionEntries[i], sizeof(wchar_t) * (nLen+1));
    SendMessage(hwndControl, LB_GETTEXT, *(pSelectedItems+i), (LPARAM)pszSelectionEntries[i]);
    nTotalLen += nLen+1;
  }
  free(pSelectedItems);

  // allocate the one big buffer
  pszBigBuf = new wchar_t[nTotalLen+2];
  if (pszBigBuf == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_values_of_multiple...\n");
    for (i = 0; i < nNumItems; ++i) {
      free(pszSelectionEntries[i]);
    }
    free(pszSelectionEntries);
    return NULL;            // out of memory!
  }
  ZeroMemory((PVOID)pszBigBuf, sizeof(wchar_t) * (nTotalLen+2));

  // copy the entries into the one big buffer
  for (i=0, nOffset=0; i<nNumItems; i++) {
    nLen = wcslen(pszSelectionEntries[i]);
    if ((nOffset + nLen + 1) > nTotalLen) {
      g2pvt_gprintf(G2PVT_ERROR, "internal error: get_control_values_of_multiple...\n");
      for (int j = i; j < nNumItems; ++j) {
	free(pszSelectionEntries[j]);
      }
      free(pszSelectionEntries);
      delete[] pszBigBuf;
      return NULL;
    }
    // don't copy the terminating zero
    wcsncpy(pszBigBuf+nOffset, pszSelectionEntries[i], nLen);
    nOffset += nLen;

    // use m_DlgStrDelim as terminator, instead
    pszBigBuf[nOffset] = m_DlgStrDelim[0];
    nOffset++;

    // done with this string
    free(pszSelectionEntries[i]);
    pszSelectionEntries[i] = NULL;
  }
  // a final (alternate) terminator to let G2 know we're done with the selections.
  // if this is a checkable list box, the checked items will follow
  pszBigBuf[nOffset] = m_DlgStrDelim2[0];
  free(pszSelectionEntries);

  // fix text for G2
  return_string = g2pvt_windows_to_g2_text(pszBigBuf);
  delete [] pszBigBuf;

  return return_string;
}


/*****************************************************************************
* wchar_t *g2pvt_get_control_value_of_list (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
wchar_t *g2pvt_get_control_value_of_list (HWND hwndControl, CONTROLITEM *pitem)
{
  if ((pitem->_styles & LBS_MULTIPLESEL) || (pitem->_styles & LBS_EXTENDEDSEL))
    return get_control_values_of_multiple_selection_list(hwndControl);
  else
    return get_control_value_of_single_selection_list(hwndControl);
}


/*****************************************************************************
* wchar_t *get_control_value_of_edit_control (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_edit_control (HWND hwndControl)
{
  wchar_t *pszValue = NULL, *converted_text = NULL;
  int nLen = 0;

  pszValue = g2pvt_contents_of_edit_control(hwndControl);
  if (pszValue == NULL) {
    return NULL;            // out of memory!
  }
  // fix text for G2:
  converted_text = g2pvt_windows_to_g2_text(pszValue);
  free(pszValue);

  return converted_text;
}

/* Set or get the start and end positions of current selection in an edit
 * control, corrected for the difference between G2 and Windows newlines. */
void g2pvt_set_g2_selection(HWND hwndEdit, DWORD start, DWORD end)
{
  BOOL style = GetWindowLong(hwndEdit, GWL_STYLE);
  DWORD n = SendMessage(hwndEdit, WM_GETTEXTLENGTH, 0, 0);
  LPWSTR buf;
  DWORD i, g2pos, winStart, winEnd;

  winStart = start;
  winEnd = end;

  if((style&ES_MULTILINE) && n>0) {
    buf = (LPWSTR) malloc(sizeof(wchar_t) * (n+1));
    if(buf) {
      SendMessage(hwndEdit, WM_GETTEXT, n+1, (LPARAM)buf);
      i = 0;
      for(g2pos=0; g2pos<=end; g2pos++, i++) {
	if(g2pos == start)
	  winStart = i;
	if(g2pos == end)
	  winEnd = i;
	if(buf[i] == L'\r' && (i<n) && buf[i+1] == L'\n') // Might access NUL terminator, but that's OK.
	  i++;
      }
      free(buf);
    }
  }
  SendMessage(hwndEdit, EM_SETSEL, (WPARAM)winStart, (LPARAM)winEnd);
}

void g2pvt_get_g2_selection(HWND hwndEdit, DWORD *pStart, DWORD *pEnd)
{
  BOOL style = GetWindowLong(hwndEdit, GWL_STYLE);
  DWORD n = SendMessage(hwndEdit, WM_GETTEXTLENGTH, 0, 0);
  LPWSTR buf;
  DWORD i, g2pos, winStart, winEnd;

  SendMessage(hwndEdit, EM_GETSEL, (WPARAM)&winStart, (LPARAM)&winEnd);

  *pStart = winStart;
  *pEnd = winEnd;

  if((style&ES_MULTILINE) && n>0) {
    buf = (LPWSTR) malloc(sizeof(wchar_t) * (n+1));
    if(buf) {
      SendMessage(hwndEdit, WM_GETTEXT, n+1, (LPARAM)buf);
      g2pos = 0;
      for(i=0; i<=winEnd; i++, g2pos++) {
	if(i == winStart)
	  *pStart = g2pos;
	if(i == winEnd)
	  *pEnd = g2pos;
	if(buf[i] == L'\r' && (i<n) && buf[i+1] == L'\n') // Might access NUL terminator.
	  i++;
      }
      free(buf);
    }
  }
}


/*****************************************************************************
* wchar_t *g2pvt_get_expanded_contents_of_edit_control (HWND hwndControl)
*
*   Description: build up the return string a la:
*     "textbox value\001start\002end\001rgb\001rgb"
*   Input Arguments:
*   Returns: a freshly malloc'ed wide string, or NULL
*   Notes: it is the caller's responsibility to free the returned value.
*     LIMIT_TEXT_BOXES
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *g2pvt_get_expanded_contents_of_edit_control (HWND hwndControl,
                                                             CONTROLITEM *pitem)
{
  union
  {
    COLORREF color_ref;
    BYTE rgb_array[sizeof(long)];
  } my_color;

  wchar_t *pszValue = NULL;
  wchar_t *converted_text;
  int nLen = 0;

  DWORD start;
  DWORD end;
  TCHAR szStartValue[10];
  TCHAR szEndValue[10];
  EXTRA_TYPE_DATA *pETData;
  EXTRA_TEXTBX_DATA *pTBData;
  TCHAR r_buf1[3];
  TCHAR g_buf1[3];
  TCHAR b_buf1[3];
  TCHAR r_buf2[3];
  TCHAR g_buf2[3];
  TCHAR b_buf2[3];

  if (use_simple_text_boxes_p)
  {
    return get_control_value_of_edit_control(hwndControl);
  }

  g2pvt_get_g2_selection(hwndControl, &start, &end);
  wsprintf(szStartValue, L"%d", start);
  wsprintf(szEndValue, L"%d", end);

  // get the colors the user set for this control earlier
  pETData = pitem->_pExtraTypeData;
  if (pETData)
  {
    pTBData = (EXTRA_TEXTBX_DATA*)pETData->_pData;
    if (pTBData)
    {
      my_color.color_ref = pTBData->textColor;

      _snwprintf(b_buf1, 3, L"%02X", my_color.rgb_array[2]);
      my_color.rgb_array[2] = 0;

      _snwprintf(g_buf1, 3, L"%02X", my_color.rgb_array[1]);
      my_color.rgb_array[1] = 0;

      _snwprintf(r_buf1, 3, L"%02X", my_color.rgb_array[0]);

      my_color.color_ref = pTBData->backgroundColor;

      _snwprintf(b_buf2, 3, L"%02X", my_color.rgb_array[2]);
      my_color.rgb_array[2] = 0;

      _snwprintf(g_buf2, 3, L"%02X", my_color.rgb_array[1]);
      my_color.rgb_array[1] = 0;

      _snwprintf(r_buf2, 3, L"%02X", my_color.rgb_array[0]);
    }
  }
  // get the length of the text associated with the edit control
  // does not include null terminator
  nLen = SendMessage(hwndControl, WM_GETTEXTLENGTH, 0, 0);
  nLen += 1;// delimiter \001
  nLen += _tcslen(szStartValue);  // start
  nLen += 1;// delimiter \002
  nLen += _tcslen(szEndValue); // end
  nLen += 1; //delimiter \001
  nLen += 6+1+6; //rgb\001rgb

  pszValue = (wchar_t *)malloc((nLen+1) * sizeof(wchar_t));
  if (pszValue == NULL) {
    return NULL;            // out of memory!
  }
  ZeroMemory((PVOID)pszValue, sizeof(wchar_t) * (nLen + 1));

  SendMessage(hwndControl, WM_GETTEXT, nLen+1, (LPARAM)pszValue);

  lstrcat(pszValue,m_DlgStrDelim);
  lstrcat(pszValue, szStartValue);
  lstrcat(pszValue,m_DlgStrDelim2);
  lstrcat(pszValue, szEndValue);
  lstrcat(pszValue,m_DlgStrDelim);
  if (pTBData && pTBData->bTxColorValueSetByUser)
  {
    lstrcat(pszValue, r_buf1);
    lstrcat(pszValue, g_buf1);
    lstrcat(pszValue, b_buf1);
  }
  lstrcat(pszValue,m_DlgStrDelim);
  if (pTBData && pTBData->bBGColorValueSetByUser)
  {
    lstrcat(pszValue, r_buf2);
    lstrcat(pszValue, g_buf2);
    lstrcat(pszValue, b_buf2);
  }

  converted_text = g2pvt_windows_to_g2_text(pszValue);
  free(pszValue);
  return converted_text;
}


/*****************************************************************************
* wchar_t *get_control_value_of_calendar (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_calendar (HWND hwndControl)
{
  SYSTEMTIME set_time;
  LRESULT lr;
  wchar_t *rval = NULL;

  lr = SendMessage(hwndControl, DTM_GETSYSTEMTIME, 0, (LPARAM) &set_time);
  if (lr != GDT_VALID) {
    g2pvt_gprintf(G2PVT_ERROR, "failed to time of date/time picker control\n");
    return NULL;
  }

  rval = (wchar_t *)malloc(SIZE_OF_DATE_TIME_STRING * sizeof(wchar_t));
  if (rval == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_value_of_calendar\n");
    return NULL;
  }
  ZeroMemory((PVOID)rval, SIZE_OF_DATE_TIME_STRING * sizeof(wchar_t));

  _snwprintf(rval, SIZE_OF_DATE_TIME_STRING, L"%d:%d:%d", set_time.wYear,
             set_time.wMonth, set_time.wDay);

  return rval;
}


/*****************************************************************************
* wchar_t *get_control_value_of_time_of_day (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_time_of_day (HWND hwndControl)
{
  SYSTEMTIME set_time;
  LRESULT lr;
  wchar_t *rval = NULL;

  lr = SendMessage(hwndControl, DTM_GETSYSTEMTIME, 0, (LPARAM) &set_time);
  if (lr != GDT_VALID) {
    g2pvt_gprintf(G2PVT_ERROR, "failed to time of date/time picker control\n");
    return NULL;
  }

  rval = (wchar_t *)malloc(SIZE_OF_DATE_TIME_STRING * sizeof(wchar_t));
  if (rval == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_value_of_time_of_day\n");
    return NULL;
  }
  ZeroMemory((PVOID)rval, SIZE_OF_DATE_TIME_STRING * sizeof(wchar_t));

  _snwprintf(rval, SIZE_OF_DATE_TIME_STRING, L"%d:%d:%d:%d:%d:%d",
             set_time.wYear, set_time.wMonth, set_time.wDay, set_time.wHour,
             set_time.wMinute, set_time.wSecond);

  return rval;
}

//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
static wchar_t *get_control_value_of_short_duration (HWND hwndControl)
{
	SYSTEMTIME set_time;
	LRESULT lr;
	wchar_t *rval = NULL;

	lr = SendMessage(hwndControl, DTM_GETSYSTEMTIME, 0, (LPARAM) &set_time);
	if (lr != GDT_VALID) {
		g2pvt_gprintf(G2PVT_ERROR, "failed to time of date/time picker control\n");
		return NULL;
	}

	rval = (wchar_t *)malloc(SIZE_OF_DATE_TIME_STRING * sizeof(wchar_t));
	if (rval == NULL) {
		g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_value_of_time_of_day\n");
		return NULL;
	}
	ZeroMemory((PVOID)rval, SIZE_OF_DATE_TIME_STRING * sizeof(wchar_t));

	_snwprintf(rval, SIZE_OF_DATE_TIME_STRING, L"%d:%d:%d",
		set_time.wHour, set_time.wMinute, set_time.wSecond);

	return rval;
}
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls


/*****************************************************************************
* wchar_t *get_control_value_of_non_pushbutton (HWND hwndControl)
*
*   Description: non_pushbutton, i.e., a button which isn't a pushbutton:
*       a radio button or a check box
*   Input Arguments:
*   Returns: Newly malloc'd wide string or NULL.
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_non_pushbutton (HWND hwndControl)
{
  LONG lResult;

  lResult = SendMessage(hwndControl, BM_GETCHECK, 0, 0);
  switch (lResult) {
  case BST_CHECKED:
    return wcsdup(L"True");

  case BST_UNCHECKED:
  case BST_INDETERMINATE:
    return wcsdup(L"False");
  }
  return NULL;
}


/*****************************************************************************
* wchar_t *get_control_value_of_pushbutton (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: an exact copy of get_control_value_of_edit_control, but I'm
*     bifurcating due to bug HQ-4797051 "sometimes control-value of push-button
*     is wrong".  In order to fix that bug, this function will likely have to
*     change.  -jv, 2/03/05
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_pushbutton (HWND hwndControl)
{
  wchar_t *pszValue = NULL, *converted_text = NULL;

  pszValue = g2pvt_contents_of_edit_control(hwndControl);
  if (pszValue == NULL) {
    return NULL;            // out of memory!
  }
  // fix text for G2:
  converted_text = g2pvt_windows_to_g2_text(pszValue);
  free(pszValue);

  return converted_text;
}


/*****************************************************************************
* wchar_t *get_control_value_of_pushbutton_depress (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: concatenate the value of the pushbutton, followed by \001,
*   followed by the  state of the button (depressed = True ; else False)
*
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value_of_pushbutton_depress (HWND hwndControl)
{
  long lResult;
  wchar_t *pszValue;
  wchar_t *pszResult;
  wchar_t *pszReturn;
  const wchar_t szTrue[] = L"True";
  const wchar_t szFalse[] = L"False";
  int size_of_buf;

  int id = GetDlgCtrlID(hwndControl);
  CONTROLITEM *pcontrol = g2pvt_lookup_control_by_hwnd(id, GetParent(hwndControl));
  assert(pcontrol);
  pszResult = (wchar_t *)(pcontrol->checked ? szTrue : szFalse);

  pszValue = get_control_value_of_pushbutton(hwndControl);

  // make  a buffer big enough for the entire composite string
  // value of pushbutton   \002  state            NULL
  size_of_buf = (sizeof(wchar_t))*(wcslen(pszValue) + 1 + wcslen(pszResult)+ 1);

  pszReturn = (wchar_t *)malloc(size_of_buf);

  wcscpy(pszReturn, pszValue);
  wcscat(pszReturn, (wchar_t * )m_DlgStrDelim2);
  wcscat(pszReturn, pszResult);

  free(pszValue);
  return pszReturn;
}


/*****************************************************************************
* wchar_t *get_control_value (GENSYMDIALOG *dialog, CONTROLITEM *pitem)
*
*   Description:
*   Input Arguments:
*   Returns: Newly allocated G2 (wide) string or NULL.
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static wchar_t *get_control_value (GENSYMDIALOG *dialog, CONTROLITEM *pitem)
{
  long control_id = pitem->_controlId;
  HWND hwndDlg = dialog->hwnd;
  HWND hwndControl = g2pvt_get_dlg_item_hwnd(hwndDlg, control_id);

  // If we've never created the HWND for the control, we cannot possibly get
  // a value for it.
  if (hwndControl == NULL) {
    return NULL;
  }

  switch (pitem->_type) {

  case ctTabs:
#ifdef CODEJOCK
   return g2pvt_get_contents_of_G2TabWidget_control(hwndControl, pitem); //TWNG tabs
#endif
    break;

  case ctProgressBar:
    return get_control_value_of_progress_bar(hwndControl);
    break;

  case ctTrackBar:
  case ctSlider:
    return get_control_value_of_track_bar(hwndControl);
    break;

  case ctComboTreeView:
    return get_control_value_of_combo_tree_view(hwndControl);
    break;

  case ctComboBox:
  case ctColor:
    return get_control_value_of_combo_box(hwndControl);
    break;

  case ctCheckListBox:
#ifdef CODEJOCK
    return g2pvt_control_value_of_check_listbox(hwndControl, pitem);
#endif
    break;

  case ctListBox:
    return g2pvt_get_control_value_of_list(hwndControl, pitem);
    break;

  case ctTextBx:
    return g2pvt_get_expanded_contents_of_edit_control(hwndControl, pitem);
  break;

  case ctMaskEdit:
#ifdef CODEJOCK
    return g2pvt_get_contents_of_gensym_edit_control(hwndControl, pitem);
#endif
  break;

  case ctStatic:
  case ctGroup:
    return get_control_value_of_edit_control(hwndControl);
    break;

  case ctCalendar:
    return get_control_value_of_calendar(hwndControl);
    break;

  case ctTimeOfDay:
    return get_control_value_of_time_of_day(hwndControl);
    break;

//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctShortDuration:
    return get_control_value_of_short_duration(hwndControl);
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls

  case ctWorkspace:
    // Could be grouped into other controls, above, which take the exact
    // same action, but it is kind of different.  Basically TW doesn't
    // really know what it is showing, and it just returns "N/A" to G2,
    // and G2 does the rest.
    return get_control_value_of_edit_control(hwndControl);
    break;

#ifdef CODEJOCK
  case ctSpin:
    return g2pvt_control_value_of_twng_spinner(hwndControl);

  case ctDuration:
    return g2pvt_control_value_of_duration(hwndControl);
#endif

  case ctRadio:
  case ctCheck:
    return get_control_value_of_non_pushbutton(hwndControl);
    break;

  case ctToggleButton:
    return get_control_value_of_pushbutton_depress(hwndControl);
    break;
  case ctPushBtn:
    return get_control_value_of_pushbutton(hwndControl);
    break;

#ifdef CODEJOCK
  case ctTabularView:
    return g2pvt_tabular_view_value(hwndControl);

  case ctGridView:
    // the function we call here is accurately named; we only return to G2
    // the cell-value of the last cell which was edited.  G2 uses that to
    // construct the full, up-to-date control-value.  -jv, 8/21/06
    return g2pvt_cell_value_of_last_gv_edit(hwndControl);
#endif

  case ctIcon:
    break;

  case ctAdvancedColor:
#ifdef CODEJOCK
    return g2pvt_control_value_of_advanced_color(hwndControl);
#endif
    break;

  default:
    break;
  }

  return NULL;
}


/*****************************************************************************
* GENSYMDLGRESPONSE *g2pvt_find_dialog_response (long dlgId)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" GENSYMDLGRESPONSE *g2pvt_find_dialog_response (GENSYMDIALOG *dialog)
{
  GENSYMDLGRESPONSE *new_response;

  if (dialog == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "Could not obtain dialog for given id.\n");
    return NULL;
  }
  if (dialog->mResponse == NULL) {
    // create our dialog response and add to linked list
    new_response = (GENSYMDLGRESPONSE *) malloc(sizeof(GENSYMDLGRESPONSE));
    if (new_response == NULL) {
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2pvt_find_dialog_response\n");
      return NULL;
    }
    dialog->mResponse = new_response;

    ZeroMemory((PVOID)new_response, sizeof(GENSYMDLGRESPONSE));

    // init
    new_response->dialog_id = dialog->dialog_id;
  }
  return dialog->mResponse;
}


/*****************************************************************************
* wchar_t *g2pvt_updated_control_value (GENSYMDIALOG *dialog, long control_id)
*
*   Description:
*   Input Arguments:
*   Returns: Newly malloc'd G2 (wide) string.
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" wchar_t *g2pvt_updated_control_value (GENSYMDIALOG *dialog,
                                                 long control_id)
{
  GENSYMDLGRESPONSE *response;
  int i;

  response = g2pvt_find_dialog_response(dialog);
  if (response == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "Unable to find dialog response in %s\n",
      "g2pvt_updated_control_value");
    return g2pvt_empty_wide_string();
  }

  for (i=0; i < response->response_count; i++) {
    if (response->presponses[i]->_controlId == control_id) {
      if (response->presponses[i]->_mResponseString == NULL) {
        response->presponses[i]->_mResponseString = (wchar_t *) malloc(sizeof(wchar_t));
        if (response->presponses[i]->_mResponseString == NULL) {
          g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2pvt_updated_control_value\n");
          return NULL;            // out of memory!
        }
        response->presponses[i]->_mResponseString[0] = 0;
      }

      return g2pvt_windows_to_g2_text(response->presponses[i]->_mResponseString);
    }
  }

  return g2pvt_empty_wide_string();
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Control "setters"
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* void parse_bar_value (BARVALS *pBarValues, wchar_t *pszText)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void parse_bar_value (BARVALS *pBarValues, wchar_t *pszText)
{
  wchar_t *token;
  wchar_t seps[] = L"|";
  wchar_t *pszTemp;
  int len;

  // defaults
  pBarValues->bar_step = 1;

  // make temp copy of incoming string to mangle with wcstok
  len = wcslen(pszText) + 1;
  pszTemp = new wchar_t [len];
  if (pszTemp == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: parse_bar_value\n");
    return;                // out of memory!
  }
  ZeroMemory((PVOID)pszTemp, sizeof(wchar_t) * len);
  wcsncpy(pszTemp, pszText, len);

  // extract default value
  token = wcstok(pszTemp, seps);
  if (token) {
    pBarValues->bar_default = wcstol(token, NULL, 10);
  }
  else
  {
    delete [] pszTemp;
    pszTemp = NULL;
    return;
  }

  // extract minimum value
  token = wcstok(NULL, seps);
  if (token) {
    pBarValues->bar_min = wcstol(token, NULL, 10);
  }
  else {
    delete [] pszTemp;
    pszTemp = NULL;
    return;
  }

  // extract maximum value
  token = wcstok(NULL, seps);
  if (token) {
    pBarValues->bar_max = wcstol(token, NULL, 10);
  }
  else {
    delete [] pszTemp;
    pszTemp = NULL;
    return;
  }

  // extract bar_step
  token = wcstok(NULL, seps);
  if (token) {
    pBarValues->bar_step = wcstol(token, NULL, 10);
    if (pBarValues->bar_step == 0) {
      pBarValues->bar_step = 1;
    }
  }
  else {
    delete [] pszTemp;
    pszTemp = NULL;
    return;
  }

  delete [] pszTemp;
  pszTemp = NULL;
}


/*****************************************************************************
* void set_progress_bar (HWND hwndParent, HWND hwndCtrl, CONTROLITEM *pcontrol)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void set_progress_bar (HWND hwndParent, HWND hwndCtrl, wchar_t *ptext)
{
  wchar_t szBuf[MAX_TEXT] = {0};
  BARVALS *pBarValues;

  pBarValues = (BARVALS *)malloc(sizeof(BARVALS));
  if (pBarValues == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_progress_bar\n");
    return;                                // out of memory!
  }
  ZeroMemory((PVOID)pBarValues, sizeof(BARVALS));

  // set up values and stuff pointer to the bar values structure
  parse_bar_value(pBarValues, ptext);

  SendMessage(hwndCtrl, PBM_SETRANGE, 0,
    MAKELPARAM(pBarValues->bar_min, pBarValues->bar_max));
  SendMessage(hwndCtrl, PBM_SETSTEP, (WPARAM) pBarValues->bar_step, 0);
  SendMessage(hwndCtrl, PBM_SETPOS, (WPARAM) pBarValues->bar_default, 0);

  // SendMessage(hwndPB, PBM_STEPIT, 0, 0);
}


/*****************************************************************************
* void set_track_bar (HWND hwndParent, HWND hwndCtrl, wchar_t *ptext)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void set_track_bar (HWND hwndParent, HWND hwndCtrl, wchar_t *ptext)
{
  wchar_t szBuf[MAX_TEXT] = {0};
  BARVALS *pBarValues;

  pBarValues = (BARVALS *)malloc(sizeof(BARVALS));
  if (pBarValues == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_track_bar\n");
    return;                                // out of memory!
  }
  ZeroMemory((PVOID)pBarValues, sizeof(BARVALS));

  // set up values and stuff pointer to the bar values structure
  parse_bar_value(pBarValues, ptext);

  SendMessage(hwndCtrl, TBM_SETRANGEMIN, (WPARAM) FALSE, pBarValues->bar_min);
  SendMessage(hwndCtrl, TBM_SETRANGEMAX, (WPARAM) FALSE, pBarValues->bar_max);
  SendMessage(hwndCtrl, TBM_SETSELSTART, (WPARAM) FALSE, pBarValues->bar_min);
  SendMessage(hwndCtrl, TBM_SETSELEND, (WPARAM) FALSE, pBarValues->bar_max);
  SendMessage(hwndCtrl, TBM_SETLINESIZE, 0, (LPARAM) pBarValues->bar_step);
  // make "page up" the same as "up arrow"?
  SendMessage(hwndCtrl, TBM_SETPAGESIZE, 0, (LPARAM) pBarValues->bar_step);
  SendMessage(hwndCtrl, TBM_SETPOS, (WPARAM) TRUE, (LPARAM) pBarValues->bar_default);
}


/*****************************************************************************
* long set_dropdown_width (CONTROLITEM *pControl, HWND hwndCtrl,
*                                 wchar_t *width_as_string)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: used to be used for the tree-view-combo-box, too.  Now only
*     applies to the C-based controls.  -jv, 5/05/06
*
*     -----
*   Modifications:
*****************************************************************************/
static long set_dropdown_width (CONTROLITEM *pControl, HWND hwndCtrl,
                                wchar_t *width_as_string)
{
  long new_width;
  LRESULT lr;
  LRESULT result;
  LPARAM tmplParam;
  WPARAM tmpwParam;

  // redundant check
  if ((pControl->_type != ctComboBox) && (pControl->_type != ctColor))
  {
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  new_width = wcstol(width_as_string, NULL, 10);
  if (new_width < pControl->_width) {
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }


  // for some reason,processing CB_SETDROPPEDWIDTH wipes out the edit
  // selection in the ComboBox.  So, we'll get it and then reset
  // it after we send CB_SETDROPPEDWIDTH - hjg 08-23-2006
  result = SendMessage(hwndCtrl, CB_GETEDITSEL, (WPARAM)&tmpwParam, (LPARAM)&tmplParam);
  lr = SendMessage(hwndCtrl, CB_SETDROPPEDWIDTH, (WPARAM) new_width, 0);
  result = SendMessage(hwndCtrl, CB_SETEDITSEL, (WPARAM)0, (LPARAM)result);
  if (lr == CB_ERR) {
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* void set_combo_list (HWND hwndDlg, HWND hwndCtrl, wchar_t *values,
*                      int update_type)
*
*   Description: parse control values and add to combo dropdown list
*   Input Arguments:
*   Returns:
*   Notes: should be combined with g2pvt_set_up_list_box; too much code duplication
*
*   The format of the "values" parameter is as follows:
*     [(selection ^A) ?] ^B ([entry]^A)* ^B ([ts-begin]^A[ts-end])?
*   where "ts" refers to the text-selection specification.
*
*     -----
*   Modifications:
*****************************************************************************/
static void set_combo_list (HWND hwndDlg, HWND hwndCtrl, wchar_t *values,
                            int update_type)
{
  wchar_t *selected_token = NULL, *entries_list = NULL, *metadata = NULL;
  wchar_t *ptr = NULL;
  int selection_index = -1;
  int search_index = 0, ntoken = 0;

#ifdef CODEJOCK
  if (update_type & COLOR_PICKER) {
    return;
  }
#endif

  // Find the first ^B, if any.
  for (search_index=0; ; search_index++) {
    if ((values[search_index] == m_DlgStrDelim2[0]) || (values[search_index] == 0))
      break;
  }

  // If the first ^B was found at position zero, that means no selection is
  // specified.  Move past the ^B and get to the entries.  If the first ^B was
  // later on in the string, that means we have a selection.
  if (search_index == 0) {
    update_type |= COMBO_BOX_DEFAULT_SELECTION;  // changes arg
    selection_index = 0;
  } else {
    // The selection ends with a superfluous ^A.  That is for compatibility
    // with the list-box, which may have multiple selections, which therefore
    // need a separator character.  For the combo-box, we only support a single
    // selection, so rather than "tokenize" this string, we just assume there's
    // a ^A there and know not to copy it into our new string.
    selected_token = new wchar_t[search_index];
    if (selected_token == NULL) {
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_combo_list #1\n");
      return;                                // out of memory!
    }
    wcsncpy(selected_token, values, search_index-1);
    selected_token[search_index-1] = 0;
  }

  // move past the selected token, if any.
  ptr = values + search_index + 1;

  // Find the end of the entries section.  The sections are delimited with ^B.
  for (search_index=0; ; search_index++) {
    if ((ptr[search_index] == m_DlgStrDelim2[0]) || (ptr[search_index] == 0))
      break;
  }

  // We should definitely find the ^B.  We add the additional check above, the
  // one to check if we've hit the end of the string, just to be able to fail
  // gracefully.  It is absolutely an error if we don't find a ^B.  In this
  // case, don't even bother trying to fill in the data.
  if (ptr[search_index] != m_DlgStrDelim2[0]) {
    delete[] selected_token;
    g2pvt_gprintf(G2PVT_ERROR, "internal error in set_combo_list\n");
    return;
  }

  entries_list = new wchar_t[search_index+1];
  if (entries_list == NULL) {
    delete[] selected_token;
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_combo_list #2\n");
    return;                                // out of memory!
  }
  wcsncpy(entries_list, ptr, search_index);
  entries_list[search_index] = 0;

  // move past the entries, if any.
  ptr = ptr + search_index + 1;
  search_index = wcslen(ptr);

  metadata = new wchar_t[search_index+1];
  if (metadata == NULL) {
    delete[] selected_token;
    delete[] entries_list;
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_combo_list #3\n");
    return;                                // out of memory!
  }
  wcsncpy(metadata, ptr, search_index);
  metadata[search_index] = 0;

  // Iterate over the entries_list, adding each entry to the combo-box.  Also
  // look for a match between each token and the requested selected token.
  ptr = wcstok(entries_list, m_DlgStrDelim);
  ntoken = 0;

  while (ptr) {
    SendMessage(hwndCtrl, CB_ADDSTRING, 0, (LPARAM)ptr);
    if ((-1 == selection_index) && (0 == wcscmp(selected_token, ptr))) {
      selection_index = ntoken;
    }
    ntoken++;
    ptr = wcstok(NULL, m_DlgStrDelim);
  }

  if (update_type & COMBO_BOX_SET_SELECTION) {
    // sanity check
    if (-1 == selection_index) {
      // This isn't an error. It happens normally when creating a combo box with
      // no entries.
      // g2pvt_gprintf(G2PVT_ERROR, "internal error setting selection in set_combo_list\n");
      selection_index = 0;
    }

    SendMessage(hwndCtrl, CB_SETCURSEL, (WPARAM) selection_index, 0);
  }

  // Extract the beginning and ending edit box selections, if they exist.  The
  // selections are delimited by ^A.
  if (metadata[0])
  {
    int nBegin = 0, nEnd = 0;
    LRESULT result;

    ptr = wcstok(metadata, m_DlgStrDelim);
    if (ptr)
      nBegin = _wtoi(ptr);
    ptr = wcstok(NULL, m_DlgStrDelim);
    if (ptr)
      nEnd = _wtoi(ptr);

    // this message succeeds for CBS_SIMPLE and CBS_DROPDOWN. It fails for CBS_DROPDOWNLIST.
    result = SendMessage(hwndCtrl, CB_SETEDITSEL, (WPARAM)0, MAKELPARAM(nBegin, nEnd));
  }

  delete [] selected_token;
  delete [] entries_list;
  delete [] metadata;
}


/*****************************************************************************
* void set_list_box_selections_1 (HWND hwndCtrl, wchar_t *selections,
*                                 int nSels, BOOL single_selection_p)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     Screw efficiency!!!  For now, anyway.  My brain is not working well today,
*     and I have to do this stupidly.  -jv, 2/22/05
*
*     -----
*   Modifications:
*****************************************************************************/
static void set_list_box_selections_1 (HWND hwndCtrl, wchar_t *selections,
                                       int nSels, BOOL single_selection_p)
{
  wchar_t **all_selections, *token, *lbSelectedRowValue;
  int i=0, j, len, nLbLen, nSelsToUse, nCount=0;

  all_selections = (wchar_t **)malloc(nSels * sizeof(wchar_t *));
  if (all_selections == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_list_box_selections_1 #1\n");
    return;            // out of memory!
  }

  // It's ok to mangle the argument.
  token = wcstok(selections, m_DlgStrDelim);
  while (token != NULL) {
    len = 1 + wcslen(token);
    all_selections[i] = (wchar_t *)malloc(len * sizeof(wchar_t));
    if (all_selections[i] == NULL) {
      for (int t = 0; t < i; ++t) {
	free(all_selections[t]);
      }
      free(all_selections);
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_list_box_selections_1 #2\n");
      return;            // out of memory!
    }
    wcsncpy(all_selections[i], token, len);
    token = wcstok(NULL, m_DlgStrDelim);
    i++;
    if (i > nSels) {
      g2pvt_gprintf(G2PVT_ERROR, "logic error in set_list_box_selections_1!\n");
      token = NULL;
    }
  }

  nSelsToUse = nSels;
  if (single_selection_p) {
    // We will only pay attention to the first requested selection.
    nSelsToUse = 1;
  }

  nCount = SendMessage(hwndCtrl, LB_GETCOUNT, 0, 0);
  for (i=0; i<nCount; i++) {
    nLbLen = SendMessage(hwndCtrl, LB_GETTEXTLEN, i, 0);
    if (nLbLen > 0) {
      lbSelectedRowValue = new wchar_t[nLbLen+1];
      if (lbSelectedRowValue == NULL) {
	for (int t = 0; t < nSels; ++t) {
	  free(all_selections[t]);
	}
	free(all_selections);
        g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_list_box_selections_1 #3\n");
        return;            // out of memory!
      }
      ZeroMemory((PVOID)lbSelectedRowValue, sizeof(wchar_t) * (nLbLen + 1));
      SendMessage(hwndCtrl, LB_GETTEXT, i, (LPARAM)lbSelectedRowValue);

      for (j=0; j<nSelsToUse; j++) {
        if (wcscmp(all_selections[j], lbSelectedRowValue) == 0) {
          if (single_selection_p) {
            SendMessage(hwndCtrl, LB_SETCURSEL, (WPARAM) i, 0);
          } else {
            SendMessage(hwndCtrl, LB_SETSEL, (WPARAM) TRUE, (LPARAM) i);
          }
        }
      }
      delete [] lbSelectedRowValue;
      lbSelectedRowValue = NULL;
    }
  }
  for (j=0; j<nSels; j++) {
    free(all_selections[j]);
    all_selections[j] = NULL;
  }
  free(all_selections);
}


/*****************************************************************************
* void set_list_box_selections (HWND hwndCtrl, wchar_t *values,
*                                      CONTROLITEM *pcontrol)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void set_list_box_selections (HWND hwndCtrl, wchar_t *selections,
                                     CONTROLITEM *pcontrol)
{
  BOOL single_selection_p;
  int i, len, nSels = 0;

  single_selection_p = (((pcontrol->_styles & LBS_MULTIPLESEL) == 0) &&
    ((pcontrol->_styles & LBS_EXTENDEDSEL) == 0));
  len = wcslen(selections);
  for (i=1; i<len; i++) {
    if ((selections[i] == m_DlgStrDelim[0]) && (selections[i-1] != m_DlgStrDelim[0])) {
      nSels++;
    }
  }
  if (nSels == 0) {
    return;
  }
  set_list_box_selections_1(hwndCtrl, selections, nSels, single_selection_p);
}


/*****************************************************************************
* void g2pvt_set_up_list_box (HWND hwndCtrl, wchar_t *values, int update_type,
*                             CONTROLITEM *pcontrol)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: should be partially combined with set_combo_list; too much code
*          duplication
*
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_set_up_list_box (HWND hwndCtrl, wchar_t *values, int update_type,
                            CONTROLITEM *pcontrol)
{
  wchar_t *entries_list = NULL, *selections = NULL, *token = NULL;
  int i, len, newLen, startEntries;

  len = wcslen(values);
  if (m_DlgStrDelim2[0] == values[0]) {
    update_type |= COMBO_BOX_DEFAULT_SELECTION;  // changes arg
    startEntries = 1;
  } else {
    startEntries = 0;
    for (i=1; i<len; i++) {
      if ((m_DlgStrDelim2[0] == values[i]) && (m_DlgStrDelim[0] == values[i-1])) {
        startEntries = i + 1;
        break;
      }
    }
  }

  if (startEntries == 0) {
    // Not necessarily an error; it is ok to create an empty list box.
    // Just return; no set up to be done.  -jv, 2/22/05
    return;
  }

  int clrStart = len;
  for (i = startEntries; i < len; i++) {
    if ((m_DlgStrDelim2[0] == values[i]) && (m_DlgStrDelim[0] == values[i - 1])) {
      clrStart = i + 1;
      break;
    }
  }
  if (clrStart != len) {
    int clrLen = len - clrStart - 1;
    wstring clrSetting(values + clrStart, clrLen);
    size_t pos = clrSetting.find(m_DlgStrDelim);
    wstring bgColorStr = clrSetting.substr(0, pos);
    wstring fgColorStr = clrSetting.substr(pos + 1);
    RGBDEFINITION* rgb;
    if (bgColorStr.length() > 0) {
      rgb = g2pvt_get_color_from_color_name(bgColorStr.c_str());
      if(rgb == NULL) {
        pcontrol->_font->_setBackgroundColor = false;
      } else {
        if (pcontrol->_font->_setBackgroundColor)
          free(pcontrol->_font->_backgroundColor);
        pcontrol->_font->_backgroundColor = rgb;
        pcontrol->_font->_setBackgroundColor = true;
      }
    }
    if (fgColorStr.length() > 0) {
      rgb = g2pvt_get_color_from_color_name(fgColorStr.c_str());
      if(rgb == NULL) {
        pcontrol->_font->_setFontColor = false;
      } else {
        if (pcontrol->_font->_fontColor)
          free(pcontrol->_font->_fontColor);
        pcontrol->_font->_fontColor = rgb;
        pcontrol->_font->_setFontColor = true;
      }
    }
  }

  // copy off the text so we can mangle it
  newLen = clrStart - startEntries;
  entries_list = new wchar_t[newLen];
  if (entries_list == NULL) {
    return;                                // out of memory!
  }
  wcsncpy(entries_list, (values + startEntries), newLen);
  entries_list[newLen-1] = 0;

  token = wcstok(entries_list, m_DlgStrDelim);
  SIZE s;
  int edgeWidth = GetSystemMetrics(SM_CXEDGE);
  int maxWidth = SendMessage(hwndCtrl, LB_GETHORIZONTALEXTENT, 0, 0) - 2 * edgeWidth;
  HFONT hfont = GetWindowFont(hwndCtrl);
  HDC dc = GetDC(hwndCtrl);
  SelectObject(dc, hfont);
  while (token != NULL) {
    SendMessage(hwndCtrl, LB_ADDSTRING, 0, (LPARAM)token);
    GetTextExtentPoint32(dc, token, wcslen(token), &s);
    maxWidth = max(s.cx, maxWidth);
    token = wcstok(NULL, m_DlgStrDelim);
  }
  SendMessage(hwndCtrl, LB_SETHORIZONTALEXTENT, maxWidth + 2 * edgeWidth, 0);
  ReleaseDC(hwndCtrl, dc);
  delete [] entries_list;
  entries_list = NULL;

  selections = new wchar_t[startEntries];
  if (selections == NULL) {
    return;                                // out of memory!
  }
  wcsncpy(selections, values, startEntries-1);
  selections[startEntries-1] = 0;

  set_list_box_selections(hwndCtrl, selections, pcontrol);
  delete [] selections;
  selections = NULL;
}


/*****************************************************************************
* void parse_text_box_values (HWND hwndCtrl, wchar_t *value, int updateType,
*                             CONTROLITEM *pcontrol)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: LIMIT_TEXT_BOXES
*
*     -----
*   Modifications:
*****************************************************************************/
static void parse_text_box_values (HWND hwndCtrl, wchar_t *value, int updateType,
                                   CONTROLITEM *pcontrol)
{
  TCHAR *pSubToken;
  TCHAR *pSelection;
  TCHAR *pText;
  TCHAR *pBackground;
  int red;
  int blue;
  int green;
  TCHAR *pDelim;
  EXTRA_TEXTBX_DATA *pTBData;

  if (!(pcontrol->_pExtraTypeData))
  {
    g2pvt_gprintf(G2PVT_ERROR, "parse_text_box_values: _pExtraTypeData not set\n");
    return;
  }

  if (!(pcontrol->_pExtraTypeData->_pData))
  {
    g2pvt_gprintf(G2PVT_ERROR, "parse_text_box_values: _pData not set\n");
    return;
  }

  pTBData = (EXTRA_TEXTBX_DATA*)(pcontrol->_pExtraTypeData)->_pData;
  // jv, 3/09/06: comment out the following line, to fix Bug HQ-5237074
  // g2pvt_clear_text_box_extra_data(pTBData);

  pDelim = _tcschr(value, m_DlgStrDelim[0]);
  pText = pDelim+1;

  if (!pText)
  {
     // we got crap, zero everything out
     g2pvt_clear_text_box_extra_data(pTBData);
     return;
  }

  pSelection = _tcstok(value, m_DlgStrDelim); // this will NULL out the delimiter
  if (!pSelection)
  {
     // we got crap, zero everything out
     g2pvt_clear_text_box_extra_data(pTBData);
     return;
  }

  if (m_DlgStrDelim2[0] != *pSelection)  // if we don't hit this delim, we have a selection
  {
     int chars_to_skip;

     pSubToken = _tcstok(value, m_DlgStrDelim2);
     if (!pSubToken)
     {
         g2pvt_clear_text_box_extra_data(pTBData);
         return;
     }
     pTBData->start = _wtoi(pSubToken);

     chars_to_skip = 1 + _tcslen(pSubToken);

     pSubToken = _tcstok(pSubToken+chars_to_skip, m_DlgStrDelim);
     if (!pSubToken)
     {
         g2pvt_clear_text_box_extra_data(pTBData);
         return;
     }
     pTBData->end = _wtoi(pSubToken);
     pTBData->bSelectionValuesSetByUser = TRUE;
  }

  //  convert from g2 rgb format to windows rgb format ie. widestring "RRGGBB" to COLORREF
  if (m_DlgStrDelim[0] != *pText) // if we don't hit this delim, we have a text color
  {
     pTBData->bTxColorValueSetByUser = TRUE;

     swscanf(pText, _T("%2x%2x%2x"), &red, &green, &blue);
     pTBData->textColor = RGB(red, green, blue);
  }
  pDelim = _tcschr(pText, m_DlgStrDelim[0]);
  pBackground = pDelim+1;

  if (!pBackground)
  {
     // we got crap, zero everything out
     g2pvt_clear_text_box_extra_data(pTBData);
     return;
  }

  if (0 != *pBackground)
  {
    // if we don't hit the end of text, we have a background color
     pTBData->bBGColorValueSetByUser = TRUE;

     swscanf(pBackground, _T("%2x%2x%2x"), &red, &green, &blue);
     pTBData->backgroundColor = RGB(red, green, blue);
  }
}


/*****************************************************************************
* void new_update_text_box_ex (HWND hwndCtrl, wchar_t *value, int updateType)
*
*   Description: when we are not "limiting" text-box controls, does an update
*      which can include setting the colors and the current selection/cursor.
*      Should not be called if we ARE limiting text-boxes; it's a no-op in that
*      case
*   Input Arguments: the text-box's HWND and the replacement data, serialized
*      into a text
*   Returns: nothing
*   Notes: LIMIT_TEXT_BOXES
*
*     -----
*   Modifications:
*****************************************************************************/
static void new_update_text_box_ex (HWND hwndCtrl, wchar_t *value, int updateType)
{
  int pos = -1;
  LPARAM new_text;
  wchar_t *combined_string = NULL;
  int id;
  CONTROLITEM *pcontrol;
  TCHAR *pToken;
  TCHAR *pszWork;
  TCHAR *new_text_for_replace = NULL;
  size_t len = 0, i = 0;
  EXTRA_TYPE_DATA *pETData;
  EXTRA_TEXTBX_DATA *pTBData;
  BOOL bSetText;

  if (updateType == REPLACE)
  {
    id = GetDlgCtrlID(hwndCtrl);
    pcontrol = g2pvt_lookup_control_by_hwnd(id, GetParent(hwndCtrl));
    if (!pcontrol)
    {
      DLGERROR("No control found. new_update_text_box_ex \n");
      return;
    }

    len = _tcslen((TCHAR*)value);
    if (!len)
    {
       DLGERROR("Empty token string found assuming nothing is set. new_update_text_box_ex \n");
       return;
    }
    pszWork = new TCHAR [len+1];

    _tcscpy(pszWork, value);

    if (m_DlgStrDelim2[0] != *pszWork) // if we have this delimiter, do not set text
    {
        pToken = _tcsstr(pszWork, m_DlgStrDelim);
        if (!pToken)
        {
            DLGERROR("Empty token string found assuming nothing is set. new_update_text_box_ex \n");
	    delete [] pszWork;
            return;
        }
        pToken += 1;
        // In addition to the auxiliary data, we still need to find the new text
        // itself.  This is the portion of the new value which precedes the first
        // instance of \001.
        while (len > i) {
          // when we find an instance of \001, modify the value of local variable
          // len, which causes us to jump out of the loop
          if (value[i] == 1) len = i;
          i++;
        }

        new_text_for_replace = new TCHAR [len+1];
        _tcsncpy(new_text_for_replace, value, len);
        new_text_for_replace[len] = 0;


        bSetText = TRUE;
    }
    else
    {
        pToken = pszWork + 2; // skip over to the good stuff
        bSetText = FALSE;
    }
    parse_text_box_values(hwndCtrl, pToken, updateType, pcontrol);
    delete [] pszWork;

    pETData = pcontrol->_pExtraTypeData;
    if (pETData)
    {
      pTBData = (EXTRA_TEXTBX_DATA*)pETData->_pData;
      if (bSetText) //set the text only if the user wants it set
         SendMessage(hwndCtrl, WM_SETTEXT, 0, (LPARAM) new_text_for_replace);
      SendMessage(hwndCtrl, WM_GENSYM_UPDATE_TEXT_BOX, (WPARAM) pTBData, 0);
    }
    if (new_text_for_replace)
      delete [] new_text_for_replace;
  }

  if (updateType == ADD)
  {
    wchar_t *old_value, *combined_string;
    size_t new_len;

    old_value = g2pvt_contents_of_edit_control(hwndCtrl);
    new_len = wcslen(old_value) + wcslen(value) + 1;
    combined_string = (wchar_t *)malloc(new_len * sizeof(wchar_t));
    if (combined_string == NULL) {
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: new_update_text_box_ex\n");
      new_text = (LPARAM) old_value;
    } else {
      combined_string[0] = 0;
      wcscat(combined_string, old_value);
      wcscat(combined_string, value);
      new_text = (LPARAM) combined_string;
    }
    free(old_value);

    SendMessage(hwndCtrl, WM_SETTEXT, 0, new_text);

    if (combined_string != NULL) {
      free(combined_string);
    }

    if (pos > -1) {
      g2pvt_set_g2_selection(hwndCtrl, pos, pos);
    }
  }
}

/*****************************************************************************
* wchar_t *g2pvt_parse_date_time_value (SYSTEMTIME *systime, wchar_t *pszText)
*
*   Description:
*   Input Arguments:
*   Returns: additional_style if possible, or NULL (GENSYMCID-210)
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
wchar_t *g2pvt_parse_date_time_value (SYSTEMTIME *systime, wchar_t *pszText)
{
  wchar_t *token;
  wchar_t seps[] = L":";
  wchar_t *pszTemp;
  int len;

  // GENSYMCID-210: International format for native date/time controls
  // extract additional style string and return
  wchar_t *additional_style = NULL;
  pszTemp = wcschr(pszText, L'|');
  if (pszTemp)
    additional_style = pszTemp + 1;

  // make temp copy of incoming string to mangle with wcstok
  len = wcslen(pszText) + 1;
  pszTemp = new wchar_t[len];
  if (pszTemp == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2pvt_parse_date_time_value\n");
    return NULL;                // out of memory!
  }
  ZeroMemory((PVOID)pszTemp, sizeof(wchar_t) * len);
  wcsncpy(pszTemp, pszText, len);

  // extract selected year
  token = wcstok(pszTemp, seps);
  if (token) {
    systime->wYear = (WORD) wcstol(token, NULL, 10);
  } else {
    delete [] pszTemp;
    pszTemp = NULL;
    return additional_style;
  }

  // extract selected month
  token = wcstok(NULL, seps);
  if (token) {
    systime->wMonth = (WORD) wcstol(token, NULL, 10);
  } else {
    delete [] pszTemp;
    pszTemp = NULL;
    return additional_style;
  }

  // extract selected day
  token = wcstok(NULL, seps);
  if (token) {
    systime->wDay = (WORD) wcstol(token, NULL, 10);
  } else {
    delete [] pszTemp;
    pszTemp = NULL;
    return additional_style;
  }

  // extract selected hour
  token = wcstok(NULL, seps);
  if (token) {
    systime->wHour = (WORD) wcstol(token, NULL, 10);
  } else {
    delete [] pszTemp;
    pszTemp = NULL;
    return additional_style;
  }

  // extract selected minute
  token = wcstok(NULL, seps);
  if (token) {
    systime->wMinute = (WORD) wcstol(token, NULL, 10);
  } else {
    delete [] pszTemp;
    pszTemp = NULL;
    return additional_style;
  }

  // extract selected second
  token = wcstok(NULL, seps);
  if (token) {
    systime->wSecond = (WORD) wcstol(token, NULL, 10);
  } else {
    delete [] pszTemp;
    pszTemp = NULL;
    return additional_style;
  }

  delete [] pszTemp;
  pszTemp = NULL;
  return additional_style;
}


/*****************************************************************************
* void set_calendar (HWND hwndCtrl, HWND hwndParent, CONTROLITEM *pcontrol)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void set_calendar (HWND hwndCtrl, HWND hwndParent, CONTROLITEM *pcontrol)
{
  SYSTEMTIME new_time;
  LRESULT lr;

  ZeroMemory((PVOID)&new_time, sizeof(SYSTEMTIME));
  // default values: the current time and date
  GetSystemTime(&new_time);

  wchar_t *additional_style = g2pvt_parse_date_time_value(&new_time, pcontrol->_mText);

  lr = SendMessage(hwndCtrl, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM) &new_time);

  if (lr == 0) {
    g2pvt_gprintf(G2PVT_ERROR, "error: failed to set calendar to %S\n",
      pcontrol->_mText);
  }

  // GENSYMCID-210: International format for native date/time controls
  if (additional_style) {
    lr = SendMessage(hwndCtrl, DTM_SETFORMAT, 0, (LPARAM) additional_style);

    if (lr == 0) {
      g2pvt_gprintf(G2PVT_ERROR, "error: failed to set custom format \"%S\" to calendar",
          additional_style);
    }
  }

  return;
}


/*****************************************************************************
* void set_time_of_day_picker (HWND hwndCtrl, HWND hwndParent, CONTROLITEM *pcontrol)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: either G2_DTS_SHOW_TIME or G2_DTS_SHOW_DATE must be set; if neither
*     neither are, we assume G2_DTS_SHOW_TIME.  G2_DTS_24_HOUR is only valid
*     if G2_DTS_SHOW_TIME is set.  So, although in theory there are eight
*     combinations, we only support five of them.
*
*     -----
*   Modifications:
*****************************************************************************/
static void set_time_of_day_picker (HWND hwndCtrl, HWND hwndParent, CONTROLITEM *pcontrol)
{
  SYSTEMTIME new_time;
  LRESULT lr = 1;

  ZeroMemory((PVOID)&new_time, sizeof(SYSTEMTIME));
  // default values: the current time and date
  GetSystemTime(&new_time);

  wchar_t *additional_style = g2pvt_parse_date_time_value(&new_time, pcontrol->_mText);
  
  // GENSYMCID-210: International format for native date/time controls
  if (additional_style) {
    lr = SendMessage(hwndCtrl, DTM_SETFORMAT, 0, (LPARAM) additional_style);

    if (lr == 0) {
      g2pvt_gprintf(G2PVT_ERROR, "error: failed to set custom format \"%S\" to time-of-day",
          additional_style);
    }
  }
  else
  if ((pcontrol->_g2styles & G2_DTS_SHOW_DATE) == G2_DTS_SHOW_DATE) {
    if ((pcontrol->_g2styles & G2_DTS_SHOW_TIME) == G2_DTS_SHOW_TIME) {
      if ((pcontrol->_g2styles & G2_DTS_24_HOUR) == G2_DTS_24_HOUR) {
        // G2_DTS_SHOW_DATE, G2_DTS_SHOW_TIME, G2_DTS_24_HOUR
        lr = SendMessage(hwndCtrl, DTM_SETFORMAT, 0,
          (LPARAM) L"M'/'d'/'yyyy', 'H':'mm':'ss");
      } else {
        // G2_DTS_SHOW_DATE, G2_DTS_SHOW_TIME, but not G2_DTS_24_HOUR
        lr = SendMessage(hwndCtrl, DTM_SETFORMAT, 0,
          (LPARAM) L"M'/'d'/'yyyy', 'h':'mm':'ss' 'tt");
      }
    } else {
      // G2_DTS_SHOW_DATE, but not G2_DTS_SHOW_TIME
      lr = SendMessage(hwndCtrl, DTM_SETFORMAT, 0, (LPARAM) L"M'/'d'/'yyyy");
    }
  } else {
    if ((pcontrol->_g2styles & G2_DTS_24_HOUR) == G2_DTS_24_HOUR) {
      // G2_DTS_SHOW_TIME, G2_DTS_24_HOUR, but not G2_DTS_SHOW_DATE
      lr = SendMessage(hwndCtrl, DTM_SETFORMAT, 0,
        (LPARAM) L"H':'mm':'ss");
    } else {
      // not G2_DTS_SHOW_DATE, and not G2_DTS_24_HOUR; we will just show the
      // time in the normal format.  But in debug mode, we'll check and complain
      // if no flags are set.  We must show either the date, the time, or both;
      // it can't be none of the above.  -jv, 3/16/05
#ifdef _DEBUG
      if ((pcontrol->_g2styles & G2_DTS_SHOW_TIME) != G2_DTS_SHOW_TIME) {
        g2pvt_gprintf(G2PVT_ERROR, "error: either show-time or show-date %s\n",
          "must be present in the time-of-day control");
      }
#endif
      // DTS_TIMEFORMAT
    }
  }
  if (lr == 0) {
    g2pvt_gprintf(G2PVT_ERROR, "error: failed to set time-of-day format\n");
  }

  lr = SendMessage(hwndCtrl, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM) &new_time);
  if (lr == 0) {
    g2pvt_gprintf(G2PVT_ERROR, "error: failed to set time-of-day to %S\n",
      pcontrol->_mText);
  }
  return;
}

//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
static void set_short_duration (HWND hwndCtrl, HWND hwndParent, CONTROLITEM *pcontrol)
{
	SYSTEMTIME new_time;
	LRESULT lr = 1;

	ZeroMemory((PVOID)&new_time, sizeof(SYSTEMTIME));
	// default values: the current time and date
	GetSystemTime(&new_time);

	g2pvt_parse_date_time_value(&new_time, pcontrol->_mText);

	lr = SendMessage(hwndCtrl, DTM_SETFORMAT, 0,(LPARAM) L"HH':'mm':'ss");

	lr = SendMessage(hwndCtrl, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM) &new_time);
	if (lr == 0) {
		g2pvt_gprintf(G2PVT_ERROR, "error: failed to set short-duration to %S\n",
			pcontrol->_mText);
	}
	return;
}
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls


/*****************************************************************************
* void set_push_button_tooltip (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
#ifndef CPP_UNIT_DEFINED
static
#endif
void set_push_button_tooltip (CONTROLITEM *pcontrol, HWND hwndCtrl,
                              const wchar_t *tooltip_text, HINSTANCE hInst)
{
  EXTRA_PUSH_BUTTON_DATA *pbdata = NULL;
  RECT rect;
  TOOLINFO tinfo;

  // Need to use "extra-type-data" to stash the tooltip's HWND.  Ensure it exists.
  if (pcontrol->_pExtraTypeData == NULL) {
    EXTRA_TYPE_DATA *xdata;

    xdata = (EXTRA_TYPE_DATA *)malloc(sizeof(EXTRA_TYPE_DATA));
    if (xdata == NULL) {
      return;
    }
    xdata->_type = ctPushBtn;
    xdata->_pData = NULL;
    pcontrol->_pExtraTypeData = xdata;
  }

  // Ensure the sub-attribute of the extra-type-data.
  if (pcontrol->_pExtraTypeData->_pData == NULL) {
    pbdata = (EXTRA_PUSH_BUTTON_DATA *)malloc(sizeof(EXTRA_PUSH_BUTTON_DATA));
    if (pbdata == NULL) {
      return;
    }
    pbdata->m_hwndTip = NULL;
    pbdata->m_tInfo_uId = 0;
    pbdata->isDefault = 0;
    pcontrol->_pExtraTypeData->_pData = pbdata;
  } else {
    pbdata = (EXTRA_PUSH_BUTTON_DATA *)pcontrol->_pExtraTypeData->_pData;
  }

  // Set the data members which are necessary for deleting the old tooltip,
  // if any.  These will stay the same whether or not we are deleting an old
  // one.  The rest of the tinfo slots will be set below.
  tinfo.cbSize = sizeof(TOOLINFO);
  tinfo.hwnd   = hwndCtrl;

  // If there's an old hwndTip, use it.  If there's an old tooltip id, (which
  // there should be, if there's an old hwndTip), delete it.  If there's no
  // hwndTip, create a new window.
  if (pbdata->m_hwndTip) {
    if (pbdata->m_tInfo_uId != 0) {
      tinfo.uId = pbdata->m_tInfo_uId;
      SendMessage(pbdata->m_hwndTip, TTM_DELTOOL, 0, (LPARAM) &tinfo);
      pbdata->m_tInfo_uId = 0;
    }
  } else {
    HWND hwndTip;

    hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
                             WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             hwndCtrl, NULL, hInst, NULL);
	//Gensym-160 BugFix
    SetWindowPos(hwndTip, HWND_TOP,0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    pbdata->m_hwndTip = hwndTip;
  }

  GetClientRect(hwndCtrl, &rect);
  // Finish filling in the tinfo structure for adding the new tooltip
  tinfo.uId         = 1;
  tinfo.uFlags      = TTF_SUBCLASS;
  tinfo.hinst       = hInst;
  tinfo.rect.left   = rect.left;
  tinfo.rect.top    = rect.top;
  tinfo.rect.right  = rect.right;
  tinfo.rect.bottom = rect.bottom;
  tinfo.lpszText    = const_cast<wchar_t *>(tooltip_text);

  // Add and activate the tooltip, and stash away the id in the control structure.
  SendMessage(pbdata->m_hwndTip, TTM_ADDTOOL, 0, (LPARAM) &tinfo);
  SendMessage(pbdata->m_hwndTip, TTM_ACTIVATE, (WPARAM) TRUE, 0);

  pbdata->m_tInfo_uId = tinfo.uId;
}


/*****************************************************************************
* void set_push_button (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/

static void extract_one_value(wstring &full_text, wstring &value)
{
  wstring::size_type pos = full_text.find(m_DlgStrDelim[0]);
  value.assign(full_text, 0, pos);
  full_text.erase(0, pos == string::npos ? pos : pos + 1);
}

static void set_push_button (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
{
  HICON the_icon = (HICON) NULL;
  wstring full_text(pcontrol->_mText), text_value;
  int icon_id = -1;

  wstring::size_type pos = full_text.find(m_DlgStrDelim2);
  if (pos != string::npos) {
    full_text.erase(pos, string::npos);
  }

  extract_one_value(full_text, text_value);
  if (full_text.length() > 0) {
    wstring icon_handle;
    extract_one_value(full_text, icon_handle);
    if (icon_handle.size() > 0) {
      swscanf(icon_handle.c_str(), L"%d", &icon_id);
      // If we got an id greater than zero, then the text is numeric and we
      // are happy.  If it is zero, we're not sure; zero may be indicative
      // of a failure.  So, we only accept zero if the text exactly matches
      // "0"; otherwise, we don't send the "set icon" message.  -jv, 1/30/05
      if ((icon_id > 0) || (icon_handle.compare(L"0") == 0)) {
        the_icon = g2pvt_get_native_icon(icon_id);
      }
    }
  }

  if (full_text.length() > 0) {
      wstring bgcolor;
      RGBDEFINITION* rgb;
      extract_one_value(full_text, bgcolor);
      if (bgcolor.length() > 0) {
        try {
          rgb = g2pvt_get_color_from_color_name(bgcolor.c_str());
          if(rgb == NULL) {
            pcontrol->_font->_setBackgroundColor = false;
          } else {
            if (pcontrol->_font->_setBackgroundColor)
              free(pcontrol->_font->_backgroundColor);
            pcontrol->_font->_backgroundColor = rgb;
            pcontrol->_font->_setBackgroundColor=true;
          }
        } catch (int e) {
        }
      }
  }

  if (full_text.length() > 0) {
      wstring fontcolor;
      RGBDEFINITION* rgb;
      extract_one_value(full_text, fontcolor);
      if (fontcolor.length() > 0) {
        try {
          rgb = g2pvt_get_color_from_color_name(fontcolor.c_str());
          if(rgb == NULL) {
            pcontrol->_font->_setFontColor = false;
          } else {
            if (pcontrol->_font->_setFontColor)
              free(pcontrol->_font->_fontColor);
            pcontrol->_font->_fontColor = rgb;
            pcontrol->_font->_setFontColor=true;
          }
        } catch (int e) {
        }
      }
  }

  if (the_icon == (HICON) NULL)
  {
    if (0 != (pcontrol->_styles & BS_ICON)) {
      // If this button was originally specified to have an icon, remove that
      // style.  Apparently, we cannot locate an appropriate icon.  Set the
      // button's text, instead.
      pcontrol->_styles = pcontrol->_styles & ~BS_ICON;
      SetWindowLong(hwndCtrl, GWL_STYLE, pcontrol->_styles);
    }
    SendMessage(hwndCtrl, WM_SETTEXT, 0, (LPARAM)text_value.c_str());
  } else {
    if (0 == (pcontrol->_styles & BS_ICON)) {
      // If this button was originally specified to NOT have an icon, add that
      // style.  A valid icon has been spedified, so use it.  Use the text as
      // the tooltip; do not send a WM_SETTEXT message with it.
      pcontrol->_styles = pcontrol->_styles | BS_ICON;
      SetWindowLong(hwndCtrl, GWL_STYLE, pcontrol->_styles);
    }
    HICON prev_icon = (HICON)SendMessage(hwndCtrl, BM_SETIMAGE, IMAGE_ICON, (LPARAM)the_icon);
    if (prev_icon && prev_icon != the_icon)
    {
        DestroyIcon(prev_icon);
    }
    set_push_button_tooltip(pcontrol, hwndCtrl, text_value.c_str(),
                           (HINSTANCE) GetWindowLong(hwndDlg, GWLP_HINSTANCE));
  }
}


/*****************************************************************************
* void update_button_control (CONTROLITEM *pcontrol, wchar_t *value,
*                             HWND hwndControl, int updateType, HWND hwndDlg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     format of button control:
*     value of pushbutton         \002           state                 NULL
*
*     -----
*   Modifications:
*****************************************************************************/
static void update_button_control (CONTROLITEM *pcontrol, wchar_t *value,
                                   HWND hwndControl, int updateType, HWND hwndDlg)
{
  const wchar_t szTrue[] = L"True";
  const wchar_t szFalse[] = L"False";
  int idx;
  wchar_t *pUpdateValue;

  if (ctToggleButton == pcontrol->_type) {
    pUpdateValue = (wchar_t*)malloc((wcslen(value) + 1)* sizeof(wchar_t));
    if (pUpdateValue == NULL) {
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: update_button_control\n");
      return;            // out of memory!
    }
    _tcscpy(pUpdateValue, value);

    // The toggle button is a button control which is actually a 2 state
    // checkbox.  We use the BS_PUSHLIKE style to make the checkbox look like
    // a PUSH button. We process CHECKED and UNCHECKED messages.
    idx = wcscspn(pUpdateValue, m_DlgStrDelim2);
    if (0 == wcscmp(pUpdateValue+idx+1, szTrue)) {
      // set state to pressed
      pcontrol->checked = 1;
    } else {
      if (0 == wcscmp(pUpdateValue+idx+1, szFalse)) {
        // set state to depressed
        pcontrol->checked = 0;
      }
    }
    free(pUpdateValue);
  }

  set_push_button(pcontrol, hwndControl, hwndDlg);
}


void update_static_control(CONTROLITEM *pcontrol, wchar_t *value, HWND hwndCtrl) {
  wchar_t *bgStart;
  
  assert(pcontrol);
  assert(value);

  bgStart = wcschr(value, m_DlgStrDelim2[0]);
  if (bgStart) {
    wstring bgColorStr(bgStart + 1);
    if (bgColorStr.length() > 0) {
      RGBDEFINITION* rgb = g2pvt_get_color_from_color_name(bgColorStr.c_str());
      if (rgb == NULL) {
        pcontrol->_font->_setBackgroundColor = false;
      } else {
        if (pcontrol->_font->_setBackgroundColor) {
          free(pcontrol->_font->_backgroundColor);
        }
        pcontrol->_font->_backgroundColor = rgb;
        pcontrol->_font->_setBackgroundColor = true;
      } 
    }
  }
  InvalidateRect(hwndCtrl, NULL, TRUE);
}

/*****************************************************************************
* long modify_control_value (GENSYMDIALOG *pdialog, long controlId,
*                                   wchar_t *value, int updateType)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static long modify_control_value (CONTROLITEM *pcontrol, HWND hwndCtrl,
                                  HWND hwndDlg, wchar_t *value, int updateType)
{
  // now we have everything we need to make updates...
  switch (pcontrol->_type) {

#ifdef CODEJOCK
  case ctColor:
    return g2pvt_modify_twng_color_picker(hwndCtrl, pcontrol, value, updateType);
  break;

  case ctComboTreeView:
  case ctIcon:
  case ctCheckListBox:
  case ctAdvancedColor:
  case ctMaskEdit:
  case ctSpin:
  case ctDuration:
  case ctGridView:
  case ctTabs:
    return g2pvt_modify_mfc_control(pcontrol, hwndCtrl, hwndDlg, value, updateType);// TWNG tabs
    break;
#endif

  case ctProgressBar:
    set_progress_bar(hwndDlg, hwndCtrl, value);
    break;

  case ctTrackBar:
  case ctSlider:
    set_track_bar(hwndDlg, hwndCtrl, value);
    break;

  case ctComboBox:
#ifndef CODEJOCK
  case ctColor:
#endif
    {
      if (updateType == DROPDOWN_WIDTH) {
        set_dropdown_width(pcontrol, hwndCtrl, value);
      } else {
        int cb_update_code = COMBO_BOX_IGNORE_SELECTION;

        if (updateType == REPLACE) {
          SendMessage(hwndCtrl, CB_RESETCONTENT, 0, 0);
          cb_update_code = COMBO_BOX_SET_SELECTION;
        } else {
          cb_update_code = COMBO_BOX_IGNORE_SELECTION;
        }
        if (ctColor == pcontrol->_type) {
          cb_update_code |= COLOR_PICKER;
        } else {
          cb_update_code |= STD_COMBO_BOX;
        }
        set_combo_list(hwndDlg, hwndCtrl, value, cb_update_code);
      }
    }
    break;

  case ctListBox:
    switch (updateType) {
    case REPLACE:
      // clear out current entries
      SendMessage(hwndCtrl, LB_RESETCONTENT, 0, 0);
      SendMessage(hwndCtrl, LB_SETHORIZONTALEXTENT, 0, 0);

      // fall through
    case ADD:
      g2pvt_set_up_list_box(hwndCtrl, value, COMBO_BOX_IGNORE_SELECTION,
                            pcontrol);
      break;
    }
    break;

  case ctTextBx:
    new_update_text_box_ex(hwndCtrl, value, updateType);
    break;

  case ctPushBtn:
  case ctToggleButton:
    update_button_control (pcontrol, value, hwndCtrl, updateType, hwndDlg);
    break;

  case ctStatic:
    update_static_control(pcontrol, value, hwndCtrl);
    break;
  case ctGroup:
    SendMessage(hwndCtrl, WM_SETTEXT, 0, (LPARAM)value);
    break;

  case ctCalendar:
    set_calendar(hwndCtrl, hwndDlg, pcontrol);
    break;

  case ctTimeOfDay:
    set_time_of_day_picker(hwndCtrl, hwndDlg, pcontrol);
    break;

//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctShortDuration:
    set_short_duration(hwndCtrl, hwndDlg, pcontrol);
	break;
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls

  case ctWorkspace:
    // Not good enough; still need more support on the G2 side
    // show_workspace(hwndDlg, hwndCtrl, pcontrol);
    break;

  case ctRadio:
  case ctCheck:
  case ctTabularView:
    break;

  default:
    break;
  }
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* void hide_dialog_control (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void hide_dialog_control (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
{
  long ctype;

  ctype = pcontrol->_type;
  ShowWindow(hwndCtrl, SW_HIDE);
}


/*****************************************************************************
* void show_dialog_control (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
*
*   Description: Called only from G2, I believe.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void show_dialog_control (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
{
  long ctype;

  ctype = pcontrol->_type;
  ShowWindow(hwndCtrl, SW_SHOW);
}


/*****************************************************************************
* long update_dialog_control (GENSYMDIALOG *pdialog, long controlId,
*                                    wchar_t *value, int updateType)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static long update_dialog_control (GENSYMDIALOG *pdialog, long controlId,
                                   wchar_t *new_control_value, int updateType)
{
  HWND hwndDlg, hwndCtrl;
  CONTROLITEM *found_control;

  if (pdialog == NULL) {
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  // given the GENSYMDIALOG, retrieve the hwnd
  hwndDlg = pdialog->hwnd;

  // lookup control's hwnd given id
  hwndCtrl = g2pvt_get_dlg_item_hwnd(hwndDlg, controlId);

  // we need the control's type so we know how to update it
  found_control = g2pvt_lookup_control_by_id(controlId, pdialog);

  if (found_control == NULL) {
    // TODO: define error to return??
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  switch (updateType) {
  case HIDE:
    hide_dialog_control(found_control, hwndCtrl, hwndDlg);
    break;

  case SHOW:
    show_dialog_control(found_control, hwndCtrl, hwndDlg);
    break;

  case ENABLE:
    EnableWindow(hwndCtrl, TRUE);
    break;

  case DISABLE:
    EnableWindow(hwndCtrl, FALSE);
    break;

  case CHECK:
    if (found_control->_type == ctToggleButton) {
      found_control->checked = 1;
      InvalidateRect(hwndCtrl, 0, true);
    } else {
      SendMessage(hwndCtrl, BM_SETCHECK, BST_CHECKED, 0);
    }
    break;

  case UNCHECK:
    if (found_control->_type == ctToggleButton) {
      found_control->checked = 0;
      InvalidateRect(hwndCtrl, 0, true);
    } else {
      SendMessage(hwndCtrl, BM_SETCHECK, BST_UNCHECKED, 0);
    }
    break;

  default:
    return modify_control_value(found_control, hwndCtrl, hwndDlg,
      new_control_value, updateType);
  }
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* long g2pvt_update_dialog (GENSYMDIALOG *pdialog,
*                           CONTROLITEM *pcontrol,
*                           int updateType)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" long g2pvt_update_dialog (GENSYMDIALOG *pdialog,
                                     CONTROLITEM *pcontrol,
                                     int updateType)
{
  if (pcontrol == NULL) {
    return 0L;
  }

  if (pdialog == NULL) {
    return 0L;
  }

  return update_dialog_control(pdialog, pcontrol->_controlId, pcontrol->_mText, updateType);
}


/*****************************************************************************
* BOOL g2pvt_init_control (HWND hwndCtrl, HWND hwndDlg, CONTROLITEM *pcontrol)
*
*   Description: control-specific processing
*   Input Arguments:
*   Returns:
*   Notes: nothing to be done for ctTextBx, ctStatic, or ctGroup
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL g2pvt_init_control (HWND hwndCtrl, HWND hwndDlg, CONTROLITEM *pcontrol)
{
  int combo_update_type = COMBO_BOX_SET_SELECTION;

  switch (pcontrol->_type) {
  case ctTabs:
    break;

  case ctProgressBar:
    set_progress_bar(hwndDlg, hwndCtrl, pcontrol->_mText);
    break;

  case ctTrackBar:
  case ctSlider:
    set_track_bar(hwndDlg, hwndCtrl, pcontrol->_mText);
    break;

  case ctComboBox:
  case ctColor:
    if (ctColor == pcontrol->_type) {
      combo_update_type |= COLOR_PICKER;
    } else {
      combo_update_type |= STD_COMBO_BOX;
    }
    set_combo_list(hwndDlg, hwndCtrl, pcontrol->_mText, combo_update_type);
    break;

  case ctListBox:
    g2pvt_set_up_list_box(hwndCtrl, pcontrol->_mText, COMBO_BOX_SET_SELECTION,
                          pcontrol);
    break;

#ifdef CODEJOCK
 case ctSpin:
    g2pvt_set_twng_spin(pcontrol, hwndCtrl, hwndDlg);
    break;
#endif

#ifdef CODEJOCK
  case ctDuration:
    g2pvt_set_duration_value(pcontrol, hwndCtrl, hwndDlg);
    break;
#endif

  case ctCalendar:
    set_calendar(hwndCtrl, hwndDlg, pcontrol);
    break;

  case ctTimeOfDay:
    set_time_of_day_picker(hwndCtrl, hwndDlg, pcontrol);
    break;

//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctShortDuration:
	 set_short_duration(hwndCtrl, hwndDlg, pcontrol);
	 break;
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls

  case ctWorkspace:
    SetWindowLong(hwndCtrl, GWL_STYLE, GetWindowLong(hwndCtrl, GWL_STYLE) | WS_TABSTOP);
    SetWindowLong(hwndCtrl, GWL_EXSTYLE, WS_EX_CONTROLPARENT);
    g2pvt_send_wsv_hwnd_to_g2(hwndDlg, pcontrol, hwndCtrl);
    break;

  case ctRadio:
  case ctCheck:
    if (pcontrol->_g2styles & G2_BS_SELECT) {
      SendMessage(hwndCtrl, BM_SETCHECK, BST_CHECKED, 0);
    }
    break;

  case ctPushBtn:
  case ctToggleButton:
     update_button_control(pcontrol, pcontrol->_mText, hwndCtrl, REPLACE, hwndDlg);
    break;

  case ctTextBx:
   if (!use_simple_text_boxes_p)
       new_update_text_box_ex (hwndCtrl, pcontrol->_mText, REPLACE);
  break;

  default:
    break;
  }

  return TRUE;
}


/*****************************************************************************
* void create_win32_control_1 (HWND hwndParent, CONTROLITEM *pcontrol,
*                                     wchar_t *szClassName, RECT *rect)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void create_win32_control_1 (HWND hwndParent, CONTROLITEM *pcontrol,
                                    wchar_t *szClassName, RECT *rect)
{
  HWND hwndControl;
  int extendedStyle = 0;
  wchar_t szLocClassName[21];
  LPWSTR szWindowName = pcontrol->_mText;

  switch (pcontrol->_type)
  {
  case ctTabularView:
    pcontrol->_styles |= LVS_OWNERDRAWFIXED;
    // note, no break!  Tabular views get WS_EX_CLIENTEDGE too.
  case ctListBox:
    extendedStyle = WS_EX_CLIENTEDGE;
    pcontrol->_styles |= WS_HSCROLL;
    break;
  case ctTextBx:
    if (!use_simple_text_boxes_p)
    {
      // Don't do this, it makes it very difficult to determine which edit
      // control has the focus, besides being highly nonstandard. If a user
      // really wants the ES_NOHIDESEL bit, then it can be set from G2. -fmw,
      // 10/3/06

      // pcontrol->_styles |= ES_NOHIDESEL;
      // this allows a selection to display up even when we don't have focus
    }
    extendedStyle = WS_EX_CLIENTEDGE;
    szWindowName = L"";		// Use WM_SETTEXT instead
    break;

  case ctWorkspace:
    pcontrol->_styles |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
    break;

  case ctProgressBar:
  case ctTrackBar:
  case ctSlider:
  case ctComboBox:
  case ctColor:  // note, ctColor has a separate MFC implementation, but IS
    // supported in our Win32 code, as well.
    break;
  case ctStatic:
    pcontrol->alignment = pcontrol->_styles & SS_TYPEMASK;
    pcontrol->_styles &= ~SS_TYPEMASK;
    pcontrol->_styles |= SS_OWNERDRAW;
    break;
  case ctSpin:
  case ctCalendar:
  case ctTimeOfDay:
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctShortDuration:
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctGroup:
  case ctRadio:
  case ctCheck:
    break;
  case ctToggleButton:
  case ctPushBtn:
    pcontrol->_styles |= BS_OWNERDRAW;
    break;

  default:
    break;
  }

  // relative to the main dialog window
  hwndControl = CreateWindowExW(extendedStyle,
    szClassName,
    szWindowName,
    pcontrol->_styles,
    rect->left,
    rect->top,
    rect->right - rect->left,
    rect->bottom - rect->top,
    hwndParent,
    (HMENU)pcontrol->_controlId,
    (HINSTANCE) GetWindowLong(hwndParent, GWLP_HINSTANCE),
    0);

  if (hwndControl) {
    // Increase the default text limit for EDIT controls to 1 million (wide)
    // characters, which matches what G2 can handle. Set the initial text after
    // adjusting it, otherwise CreateWindowExW() fails. For HQ-5273492.
    if (pcontrol->_type == ctTextBx) {
      SendMessage(hwndControl, EM_LIMITTEXT, 2000000, 0);
      SendMessage(hwndControl, WM_SETTEXT, 0, (LPARAM)pcontrol->_mText);
    }

    if ((ctTextBx == pcontrol->_type) && !use_simple_text_boxes_p)
    {
      // the user can get/set text box attributes (colors, selection and caret
      // positions) so, we need to subclass the window to accomplish all this
      // - hjg 02-10-2006
      lpfnOldTextBxProc = (FARPROC)SetWindowLong(hwndControl, GWLP_WNDPROC,
                                                 (DWORD) SubClassTextBxFunc);
    }
    else if (ctComboBox == pcontrol->_type)
    {
      // CBS_DROPDOWN and CBS_SIMPLE have an Edit window which is a child of the ComboBox.
      // CBS_DROPDOWNLIST has no child window
      // We need to sublcass the Edit part of the combobox. Look for it in the children.
      // We want to monitor WM_KEYDOWN and WM_LBUTTONUP
      HWND hwndEdit = GetWindow(hwndControl, GW_CHILD); // gets the window at the top of the z order,
                                                        // which is Edit for CBS_DROPDOWN.
      if (hwndEdit)
      {
         GetClassName(hwndEdit, szLocClassName, sizeof(szLocClassName)-1);
         if (0 == (wcscmp(szLocClassName, _T("Edit")))) // CBS_DROPDOWN
         {
           lpfnOldComboBoxProc = (FARPROC)SetWindowLong(hwndEdit, GWLP_WNDPROC, (DWORD) SubClassComboBoxFunc);
         }
         else
         {
            hwndEdit = GetWindow(hwndEdit, GW_HWNDNEXT); // gets the next child window in the z order,
                                                         // which is Edit for CBS_SIMPLE

            GetClassName(hwndEdit, szLocClassName, sizeof(szLocClassName)-1);
            if (0 == (wcscmp(szLocClassName, _T("Edit"))))
            {
                lpfnOldComboBoxProc = (FARPROC)SetWindowLong(hwndEdit, GWLP_WNDPROC, (DWORD) SubClassComboBoxFunc);
            }
         }
      }
    }


	//Set FontName as well as font Family
	HFONT hFont;
	hFont=(HFONT)SendMessage(hwndParent, WM_GETFONT, 0, 0);
	LOGFONT lf;
	GetObject(hFont, sizeof(lf), &lf);
	int fontSize;
	wchar_t* fontName;
	if(pcontrol->_font == 0 || pcontrol->_font->_fontSize==0){
		fontSize=lf.lfHeight;
	}
	else{
		fontSize=pcontrol->_font->_fontSize;
	}
	if(pcontrol->_font == 0 || _wcsicmp(pcontrol->_font->_fontName , ((wchar_t*) ""))==0){
		fontName=(wchar_t*)(lf.lfFaceName);
		
	}
	else{
		fontName=pcontrol->_font->_fontName;
	}
	hFont = CreateFont (fontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, \
		  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, \
		  DEFAULT_PITCH | FF_SWISS, fontName);
	SendMessage(hwndControl,WM_SETFONT,WPARAM(hFont),0);



    // add to list of created control id's
    CONTROLHWND *pcontrolhwnd = new CONTROLHWND;
    if (pcontrolhwnd == NULL) {
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: create_win32_control_1\n");
      return;
    }
    pcontrolhwnd->controlId = pcontrol->_controlId;
    pcontrolhwnd->hwndControl = hwndControl;
    pcontrolhwnd->pObj = NULL;
    pcontrolhwnd->next = NULL;
    // The return value of the following call is being ignored.  It's
    // FALSE if the corresponding DIALOGINFO structure was not found.
    g2pvt_add_control_hwnd(pcontrolhwnd, hwndParent);

    // further control-specific processing
    g2pvt_init_control(hwndControl, hwndParent, pcontrol);

    // should we be visible?
    if (pcontrol->_styles & WS_VISIBLE) {
      ShowWindow(hwndControl, SW_SHOW);
    }
  }
}


/*****************************************************************************
* BOOL create_win32_control (HWND hwndParent, CONTROLITEM *pcontrol,
*                                   TABITEM *ptabitem)
*
*   Description: creates a non-MFC dialog control
*   Input Arguments: the HWND of the dialog, our internal data structure
*     encapsulating the control, and a pointer to the "tab" frame which
*     this control is on (which is NULL if this control is not on a tab).
*
*   Returns: always returns TRUE.  That could be improved.
*
*   Notes:
*     Generally, we will take whatever coordinates (x, y, width, height) the
*     user supplied, call MapDialogRect on it, and go ahead and create the
*     control with those coordinates, without doing any sort of sanity checking.
*     But there is one case where we don't want the height to indicate dialog
*     units to begin with, and if we do let it do so, it does weird things.
*     This happens only in TWNG, not TW, even though at this point in the code,
*     we are not making any distinction between them.  It must have something to
*     do with the MFC DLLs that get loaded.  Maybe.
*
*     Anyway, the problem concerns dropdown combo boxes.  Like any other
*     window, combo boxes take a "height" specification when they are created.
*     However, this specification never seems to have anything to do with the
*     size of the edit control which is created to show the current selection
*     (i.e., what you see even when the dropdown box is not in use).  With
*     standard TW, the height seems to serve absolutely no purpose whatsoever.
*     You can supply zero or -1 or 1000, and it doesn't matter.
*
*     However, in TWNG, the supplied height seems to control the size of the
*     dropdown box.  And if we supply a value which is too small, then no
*     dropdown box at all is created.  A combo box in such a state acts quite
*     strangely.  It responds to keyboard input (up- and down-arrow keys), but
*     does not properly "select" what is supposed to be the "selection", which
*     prevents the correct messages from being sent, and all sorts of things
*     to appear messed up.
*
*     So, the solution is, when we are in TWNG, make sure we always create the
*     combo box with the necessary height to create a dropdown box.  "Height" is
*     expressed in 1/8 of a character unit, so every eight units of "height" is
*     one extra row.  Except, two rows seem to go into the ether.  Why are these
*     extra two rows necessary?  I really have no idea.  But it works.
*
*     We're already going ahead, performing a calculation on the user-supplied
*     number.  Given that, we may as well do a sanity check, as well.  If the
*     user supplied a value less then 1, we will use 1, instead.  -jv, 2/18/05
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL create_win32_control (HWND hwndParent, CONTROLITEM *pcontrol,
                                  TABITEM *ptabitem)
{
  int dialog_unit_height;
  RECT rectAdj;
  wchar_t szClassName[MAX_CLASSNAME_LEN] = {0};

  dialog_unit_height = pcontrol->_height;

  switch (pcontrol->_type)
  {
    // Dialog controls which have no Win32 implementation (i.e., only have an
    // MFC implementation.)  Do not attempt to create them.  Note Suggestion
    // HQ-4968263 "throw stack-error if dialog spec has controls which window
    // doesn't support" remains open.  To implement that, we would probably
    // "bubble" this FALSE value up to a level where we could get it to G2.  I
    // have decreed that solving that problem is officially "hard".  This is a
    // good start.  -jv, 4/22/05
  case ctComboTreeView:
  case ctMaskEdit:
  case ctDuration:
  case ctGridView:
  case ctIcon:
  case ctSpin:
    return FALSE;

  case ctComboBox:
    if (dialog_unit_height < 1) {
      // constant value, 24, but show how we obtain it
      dialog_unit_height = ADDITIONAL_HEIGHT_FOR_COMBO_BOX_ROWS +
        (DIALOG_UNITS_PER_ROW * 1);
    } else {
      dialog_unit_height = ADDITIONAL_HEIGHT_FOR_COMBO_BOX_ROWS +
        (DIALOG_UNITS_PER_ROW * pcontrol->_height);
    }
  }

  // need to put coordinates into a rectangle to call MapDialogRect
  SetRectEmpty(&rectAdj);
  rectAdj.left = pcontrol->_x;
  rectAdj.top = pcontrol->_y;
  rectAdj.right = pcontrol->_x + pcontrol->_width;
  rectAdj.bottom = pcontrol->_y + dialog_unit_height;
  MapDialogRect(hwndParent, &rectAdj);

  // The control coordinates are, by G2 dialog API's convention, always relative
  // to the overall dialog, and NOT relative to the control's immediate parent.
  if (ptabitem != NULL) {
    rectAdj.left = rectAdj.left - ptabitem->displayRect.left;
    rectAdj.right = rectAdj.right - ptabitem->displayRect.left;
    rectAdj.top = rectAdj.top - ptabitem->displayRect.top;
    rectAdj.bottom = rectAdj.bottom - ptabitem->displayRect.top;
  }

  g2pvt_get_name_of_control_type(pcontrol->_type, szClassName);
  create_win32_control_1(hwndParent, pcontrol, szClassName, &rectAdj);

  return TRUE;
}


/*****************************************************************************
* BOOL g2pvt_create_child_control (HWND hwndParent, CONTROLITEM *pcontrol,
*                                   TABITEM *ptabitem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL g2pvt_create_child_control (HWND hwndParent, CONTROLITEM *pcontrol,
                                 TABITEM *ptabitem)
{
  BOOL bRet;

  register_gensym_controls_if_needed();

#ifdef CODEJOCK
  if ((ctComboTreeView == pcontrol->_type)
    || (ctIcon == pcontrol->_type)
    || (ctCheckListBox == pcontrol->_type)
    || (ctColor == pcontrol->_type)
    || (ctAdvancedColor == pcontrol->_type)
    || (ctMaskEdit == pcontrol->_type)
    || (ctSpin == pcontrol->_type)
    || (ctDuration == pcontrol->_type)
    || (ctTabs == pcontrol->_type) // TWNG tabs
    || (ctGridView == pcontrol->_type)
    || (ctTabularView == pcontrol->_type))
  {
    bRet = g2pvt_create_mfc_control(hwndParent, pcontrol, ptabitem);
  }
  else
#endif
  {
    bRet = create_win32_control(hwndParent, pcontrol, ptabitem);
  }

#ifdef CODEJOCK
  // This special hook call, and the above huge if statement on the control type
  // can both be eliminated. But I'm doing it this way to minimize changes for
  // 82r1 -fmw, 2/17/06
  if (bRet)
    g2pvt_mfc_control_created_hook(hwndParent, pcontrol, ptabitem);
#endif

  return bRet;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Resizable Dialogs
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* void g2pvt_init_resizable_child_dialog (DIALOGINFO *dlgInfo, TABITEM *pTabItem,
*                                         HWND hwndChildDlg)
*
*   Description: Called when a tab child dialog is created, and during
*      initialization, from g2pvt_init_resizable_child_dialogs.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C"
void g2pvt_init_resizable_child_dialog (DIALOGINFO *dlgInfo, TABITEM *pTabItem, HWND hwndChildDlg)
{
  CONTROLITEM *pItem;
  long g2style;
  int i;
  int n = dlgInfo->_pdialog->control_count;

  if (pTabItem->resizer)
    return;

  pTabItem->resizer = g2pvt_resizer_create(hwndChildDlg, n); // An upper bound.

  // Loop over all controls to find those which belong to this tab.
  for (i=0; i<n; i++) {
    pItem = dlgInfo->_pdialog->pcontrols[i];
    g2style = pItem->_g2styles;
    if ((g2style & G2_ANCHOR_P) &&
        (pItem->_parentControlId == (long)pTabItem->tabControlId) &&
        (wcscmp(pItem->_parentControlText, pTabItem->szTabName) == 0)) {
      g2pvt_resizer_add(pTabItem->resizer, pItem->_controlId, (g2style & G2_ANCHOR_MASK) >> 4);
    }
  }

  g2pvt_resizer_lock(pTabItem->resizer);
}


/*****************************************************************************
* void g2pvt_init_resizable_child_dialogs (HWND hwndDlg, DIALOGINFO *dlgInfo)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C"
void g2pvt_init_resizable_child_dialogs (HWND hwndDlg, DIALOGINFO *dlgInfo)
{
  int i;
  CONTROLITEM *pItem;

  for (i=0; i < dlgInfo->_pdialog->control_count; i++) {
    pItem = dlgInfo->_pdialog->pcontrols[i];
    if (pItem->_type == ctTabs)
    {
#ifdef CODEJOCK
      HWND hwndTabCtrl = g2pvt_get_dlg_item_hwnd(hwndDlg, pItem->_controlId);
      /* This simply turns around and calls g2pvt_init_resizable_child_dialog,
         above. */
      if (hwndTabCtrl)
	g2pvt_init_G2TabWidget_resizable_child_dialog(hwndTabCtrl, dlgInfo);
#endif
    }
  }
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Dialog Responses
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* long init_set_dialog_responses (GENSYMDIALOG *dialog, int respcode)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static long init_set_dialog_responses (GENSYMDIALOG *dialog, int respcode)
{
  GENSYMDLGRESPONSE *found_response;

  // for now we will just use a global array of structures containing dialog
  // responses...

  found_response = dialog->mResponse;
  // 1. if previous dialog response record exists, use that one and clear out
  // the control item responses, etc.; otherwise, allocate a new dialog response

  if (found_response == NULL) {
    // create our dialog response and add to linked list
    found_response = new GENSYMDLGRESPONSE;
    if (found_response == NULL) {
      return -1L;                                // out of memory!
    }
    dialog->mResponse = found_response;

    ZeroMemory((PVOID)found_response, sizeof(GENSYMDLGRESPONSE));

    // init
    found_response->dialog_id = dialog->dialog_id;
  } else {
    // reuse
    cleanup_dialog_control_responses(found_response);
    found_response->presponses = NULL;
  }

  // common init
  found_response->response_count = 0;

  if (respcode & DLG_SEND_ALL_DATA) {
    found_response->array_size = dialog->control_count;
    // at most, this many
  } else {
    found_response->array_size = 1;
    // just one control
  }

  // init
  found_response->presponses =
    new CONTROLITEMRESPONSE*[found_response->array_size *
                             sizeof(CONTROLITEMRESPONSE)];
  if (found_response->presponses == NULL) {
    return -1L;                        // out of memory!
  }
  ZeroMemory((PVOID)found_response->presponses,
    sizeof(CONTROLITEMRESPONSE)*found_response->array_size);

  return 0L;
}


/*****************************************************************************
* long fill_in_response_structure (GENSYMDIALOG *dialog,
*                                         int controlId, int respcode)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static long fill_in_response_structure (GENSYMDIALOG *dialog,
                                        int controlId, int respcode)
{
  CONTROLITEM *pItem;
  GENSYMDLGRESPONSE *found_response = dialog->mResponse;
  wchar_t *this_response = NULL;

  found_response->initiating_control_id = controlId;

  // 2. package up the current control state
  if (respcode & DLG_SEND_ALL_DATA) {
    // we want current state of all controls in the dialog
    for (int i=0, j=0; i < dialog->control_count; i++) {
      pItem = dialog->pcontrols[i];
      this_response = get_control_value(dialog, pItem);

      if (this_response != NULL) {
        found_response->presponses[j] = new CONTROLITEMRESPONSE;
        if (found_response->presponses[j] == NULL) {
          return -1L;                        // out of memory!
        }
        // can't we use "i" instead of "pItem->_controlId"?
        found_response->presponses[j]->_controlId = pItem->_controlId;
        found_response->presponses[j]->_mResponseString = this_response;
        found_response->response_count++;
        j++;
      }
    }
  } else {
    // we only want current state of control that triggered the response
    found_response->presponses[0] = new CONTROLITEMRESPONSE;
    if (found_response->presponses[0] == NULL) {
      return -1L;                        // out of memory!
    }
    pItem = g2pvt_lookup_control_by_id(controlId, dialog);
    found_response->presponses[0]->_controlId = controlId;
    found_response->presponses[0]->_mResponseString =
      get_control_value(dialog, pItem);
    found_response->response_count = 1;
  }
  return 0L;
}


/*****************************************************************************
* long g2pvt_set_dialog_responses (GENSYMDIALOG *dialog,
*                                    int controlId, int respcode)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" long g2pvt_set_dialog_responses (GENSYMDIALOG *dialog,
                                            int controlId, int respcode)
{
  long status;

  if (dialog == NULL) {
    return -1L;
  }

  status = init_set_dialog_responses(dialog, respcode);
  if (status == 0L) {
    status = fill_in_response_structure(dialog, controlId, respcode);
  }
  return status;
}


/*****************************************************************************
* void g2pvt_ddlg_respond (HWND hwndDlg, int controlId, int respcode)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_ddlg_respond (HWND hwndDlg, int controlId, int respcode)
{
  DIALOGINFO *dlgInfo = NULL;
  GENSYMDIALOG *dialog = NULL;

  dlgInfo = (DIALOGINFO*)GetWindowLong(hwndDlg, GWLP_USERDATA);
  dialog = dlgInfo->_pdialog;

  // if the control requires any kind of response,
  // we need to set it
  switch (respcode) {
  case DLG_JUST_RESPOND:
  case DLG_RESPOND_OK:
  case DLG_RESPOND_ALL:
  case DLG_RESPOND_ALL_OK:
    g2pvt_set_dialog_responses(dialog, controlId, respcode);
    if (respcode & DLG_SEND_ALL_DATA) {
      g2pvt_send_dynamic_dialog_data_to_g2(dialog,
        TW_INITIATED_UPDATE);
    }
    g2pvt_send_tw_dialog_control_update(dialog, controlId);
    break;

  default:
    break;
  }

  // we have a response type that triggers a close
  switch (respcode) {
  case DLG_CANCEL:
  case DLG_OK:
  case DLG_RESPOND_OK:
  case DLG_RESPOND_ALL_OK:
    g2pvt_dismiss_dialog(dialog, respcode);
    break;

  default:
    break;
  }
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- WndProcs and event handling/dispatching
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* LRESULT on_combobox_command (CONTROLITEM *pcontrol, int notifyCode,
*                              HWND hwndDlg, HWND hwndOther, int controlId)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static LRESULT on_combobox_command (CONTROLITEM *pcontrol, int notifyCode,
                                    HWND hwndDlg, HWND hwndOther, int controlId)
{
  int nCurSel = 0;
  int nTextLen = 0;
  DWORD dwStyle = 0;
  wchar_t *szBuf = NULL;

  if ((notifyCode == CBN_SELENDOK) || (notifyCode == CBN_EDITCHANGE)) {
    if (notifyCode == CBN_SELENDOK) {

      // if we don't do this, and the user selected an item from the dropdown list
      // in a dropdown combobox, then we still get the text in the edit box when
      // we go to retrieve its contents
      dwStyle = GetWindowLong(hwndOther, GWL_STYLE);
      if ((dwStyle & CBS_DROPDOWN) == CBS_DROPDOWN) {
        // copy the selected text to the associated edit control
        nCurSel = SendMessage(hwndOther, CB_GETCURSEL, 0, 0);
        if (nCurSel != CB_ERR) {
          nTextLen = SendMessage(hwndOther, CB_GETLBTEXTLEN, nCurSel, 0);
          if (nTextLen != CB_ERR) {
            szBuf = new wchar_t[nTextLen+1];
            if (szBuf == NULL) {
              g2pvt_gprintf(G2PVT_ERROR, "out of memory: on_combobox_command\n");
              return FALSE;                                // out of memory!
            }
            ZeroMemory((PVOID)szBuf, sizeof(wchar_t) * (nTextLen + 1));
            if (SendMessage(hwndOther, CB_GETLBTEXT, nCurSel, (LPARAM)szBuf) != CB_ERR) {
              SendMessage(hwndOther, WM_SETTEXT, 0, (LPARAM)szBuf);
              delete [] szBuf;
              szBuf = NULL;
            }
          }
        }
      }
    }

    if (pcontrol->_respcode == DLG_NO_RESPONSE) {
      return FALSE;
    }
    g2pvt_ddlg_respond(hwndDlg, controlId, pcontrol->_respcode);
  }
  return TRUE;
}


/*****************************************************************************
* LRESULT text_box_on_wm_command (int notifyCode, HWND hwndParent,
*                                        LPARAM lParam, CONTROLITEM *pcontrol,
*                                        long controlId)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static LRESULT text_box_on_wm_command (int notifyCode, HWND hwndParent, LPARAM lParam,
                                       CONTROLITEM *pcontrol, long controlId)
{
  HWND hwnd = (HWND)lParam;
  DIALOGINFO *dlgInfo = NULL;
  GENSYMDIALOG *dialog = NULL;

  dlgInfo = (DIALOGINFO*)GetWindowLong(hwndParent, GWLP_USERDATA);
  dialog = dlgInfo->_pdialog;

  if((pcontrol->_respcode != DLG_NO_RESPONSE) && (notifyCode == EN_CHANGE) &&
     (GetFocus() == hwnd)) {
    // we only want a response if the edit is due
    // to an update via the UI and not programmatically
    g2pvt_ddlg_respond(hwndParent, controlId, pcontrol->_respcode);
  }
  return 0;
}

static long g2pvt_get_default_button(HWND hwndDlg)
{
  DIALOGINFO *dlgInfo = NULL;
  GENSYMDIALOG *dialog = NULL;
  CONTROLITEM *pItem = NULL;
  EXTRA_PUSH_BUTTON_DATA *pPBData = NULL;

  dlgInfo = (DIALOGINFO*)GetWindowLong(hwndDlg, GWLP_USERDATA);
  dialog = dlgInfo->_pdialog;

  for (int i = 0; i < dialog->control_count; ++i) {
    pItem = dialog->pcontrols[i];
    if (pItem->_type == ctPushBtn &&
        pItem->_pExtraTypeData != NULL &&
        pItem->_pExtraTypeData->_type == ctPushBtn) {

      pPBData = (EXTRA_PUSH_BUTTON_DATA *)pItem->_pExtraTypeData->_pData;
      if (pPBData != NULL && pPBData->isDefault)
        return pItem->_controlId;
    }
  }

  return -1;
}

/*****************************************************************************
* LRESULT on_wm_command (HWND hwndDlg, WPARAM wParam, LPARAM lParam)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static LRESULT on_wm_command (HWND hwndDlg, WPARAM wParam, LPARAM lParam)
{
  long controlId = 0;
  CONTROLITEM *pcontrol = NULL;
  HWND hwndOther;
  int notifyCode = 0;

  controlId = LOWORD(wParam);
  if (controlId == IDCANCEL) {
    g2pvt_ddlg_respond(hwndDlg, -1, DLG_CANCEL); // Eventually calls DestroyWindow.
    return TRUE;
  }

  if (controlId == IDOK) {
    controlId = g2pvt_get_default_button(hwndDlg);
    if (controlId == -1)
      return TRUE;
    wParam = controlId;
  }

  pcontrol = g2pvt_lookup_control_by_hwnd(controlId, hwndDlg);
  if (pcontrol == NULL) {
    return TRUE;
  }

  hwndOther = g2pvt_get_dlg_item_hwnd(hwndDlg, controlId);
  notifyCode = HIWORD(wParam);

  if (pcontrol->_type == ctToggleButton && notifyCode == BN_CLICKED) {
    pcontrol->checked = pcontrol->checked ? 0 : 1;
    InvalidateRect(hwndOther, NULL, true);
  }

  if (pcontrol->_respcode == DLG_NO_RESPONSE) {
    return FALSE;
  }

  switch (pcontrol->_type) {
  case ctTabs:
    break;

  case ctComboBox:
  case ctColor:
    return on_combobox_command(pcontrol, notifyCode, hwndDlg, hwndOther, controlId);
    break;

  case ctListBox:
    if (notifyCode == LBN_SELCHANGE) {
      g2pvt_ddlg_respond(hwndDlg, controlId, pcontrol->_respcode);
      return TRUE;
    }
    break;

  case ctCheckListBox:
#ifdef CODEJOCK
    if (g2pvt_check_list_box_wm_command(hwndDlg, controlId, pcontrol, notifyCode)) {
      return TRUE;
    }
#endif
    break;

  case ctTextBx:
  case ctMaskEdit:
    return text_box_on_wm_command(notifyCode, hwndDlg, lParam, pcontrol, controlId);
    break;

  case ctRadio:
  case ctCheck:
  case ctIcon:
    if (notifyCode == STN_CLICKED) {
      g2pvt_ddlg_respond(hwndDlg, controlId, pcontrol->_respcode);
      return TRUE;
    }
    break;

  case ctToggleButton:
  case ctPushBtn:
    if (notifyCode == BN_CLICKED) {
      g2pvt_ddlg_respond(hwndDlg, controlId, pcontrol->_respcode);
      return TRUE;
    }
    break;

  case ctComboTreeView:
        // HQ-5196766 "tree-view-combo-box fires callback upon expanding the tree"
  if (notifyCode == CBN_EDITCHANGE)
  {
     g2pvt_ddlg_respond(hwndDlg, controlId, pcontrol->_respcode);
     return TRUE;
  }
  break;

  case ctTrackBar:
  case ctSlider:
  case ctCalendar:
  case ctTimeOfDay:
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctShortDuration:
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctWorkspace:
    g2pvt_gprintf(G2PVT_ERROR, "wm_command to be handled soon by type %d\n",
      pcontrol->_type);
    break;

    // Controls which don't take user input directly.  We get WM_COMMAND messages
    // from the GridView, but they are uninteresting.  We need to find another way
    // to get update events, probably a la the TabularView.
  case ctProgressBar:
  case ctTabularView:
  case ctGridView:
    break;

  case ctAdvancedColor:
#ifdef CODEJOCK
    g2pvt_process_advanced_color(wParam, hwndDlg, pcontrol);
#endif
    break;

  case ctStatic:
    break;

  default:
    g2pvt_gprintf(G2PVT_ERROR, "unrecognized control type for wm_command: %d\n",
      pcontrol->_type);
    break;
  }
  return FALSE;
}


/*****************************************************************************
* LRESULT DynamicDlg_OnNotify (HWND hwndDlg, int idFrom, NMHDR *pnmhdr)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
LRESULT DynamicDlg_OnNotify (HWND hwndDlg, long control_id, NMHDR *pnmhdr)
{
  CONTROLITEM *pcontrol = g2pvt_lookup_control_by_hwnd(control_id, hwndDlg);

  if (pcontrol == NULL) {
    return FALSE;
  }

  switch (pcontrol->_type) {

  case ctTabs:
    break;

  case ctTrackBar:
  case ctSlider:
    if (NM_RELEASEDCAPTURE == pnmhdr->code) {
      g2pvt_ddlg_respond(hwndDlg, control_id, pcontrol->_respcode);
    }
    break;

  case ctSpin:
    break;

  case ctDuration:
  case ctCalendar:
  case ctTimeOfDay:
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
  case ctShortDuration:
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
    if (DTN_DATETIMECHANGE == pnmhdr->code) {
      g2pvt_ddlg_respond(hwndDlg, control_id, pcontrol->_respcode);
      return TRUE;
    }
    break;

#ifdef CODEJOCK
  case ctGridView:
    return g2pvt_grid_view_on_wm_notify(pnmhdr, hwndDlg, pcontrol);
    break;
#endif

  case ctProgressBar:
  case ctComboTreeView:
  case ctComboBox:
  case ctColor:
  case ctListBox:
  case ctCheckListBox:
  case ctTextBx:
  case ctMaskEdit:
  case ctStatic:
  case ctWorkspace:
  case ctGroup:
  case ctRadio:
  case ctCheck:
  case ctPushBtn:
  case ctToggleButton:
  case ctAdvancedColor:
  default:
#ifdef _DEBUG
    g2pvt_gprintf(G2PVT_DUMP, "wm_notify on control %s\n",
                  string_of_control_type(pcontrol->_type));
#endif
    break;
  }

  return FALSE;
}


/*****************************************************************************
* BOOL DynamicDlg_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL DynamicDlg_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
  GENSYMDIALOG *dialog;
  int i = 0;

  // stashing our dialog structure pointer
  SetWindowLong(hwnd, GWLP_USERDATA, (LONG)lParam);

  dialog = ((DIALOGINFO *)lParam)->_pdialog;

  // create outermost tab control(s) first
  for (i = 0; i < dialog->control_count; i++) {
    if (dialog->pcontrols[i]->_type == ctTabs) {// use the same code for TW and TWNG tabs
      if (dialog->pcontrols[i]->_parentControlId == PARENT_IS_ENTIRE_DIALOG) {
        g2pvt_create_child_control(hwnd, dialog->pcontrols[i], NULL);
      }
    }
  }

  // create all the child controls; in the case of tabs, also create
  // their containing child dialog windows
  for (i = 0; i < dialog->control_count; i++) {

    // only create directly if control has not already been created because it
    // belonged to a tab AND it does not have a parent
    HWND hwndControl = g2pvt_get_dlg_item_hwnd(hwnd, dialog->pcontrols[i]->_controlId);
    if ((hwndControl == NULL) &&
      (dialog->pcontrols[i]->_parentControlId == PARENT_IS_ENTIRE_DIALOG)) {
      g2pvt_create_child_control(hwnd, dialog->pcontrols[i], NULL);
    }
  }

  return TRUE;
}


/*****************************************************************************
 * BOOL DynamicDlg_OnSize (DIALOGINFO *dlgInfo, HWND hwndDlg, UINT message,
 *                         WPARAM wParam, LPARAM lParam)
 *
 *   Description: Called after top-level resizer, if any, has run. Propagate resizes of
 *                tab controls to their child dialogs.
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
static BOOL DynamicDlg_OnSize (DIALOGINFO *dlgInfo, HWND hwndDlg, WPARAM wParam, LPARAM lParam)
{
  int handle = (dlgInfo && dlgInfo->_pdialog) ? dlgInfo->_pdialog->g2_id : -1;

  // FIXME: window state is incorrect if MDI child.
  if ((handle > 0) && (dlgInfo->_pdialog->inShowDialog == 0))
    g2pvt_send_window_sized(hwndDlg, handle, wParam, LOWORD(lParam), HIWORD(lParam));
  return TRUE;
}


/*****************************************************************************
* LRESULT on_wm_ctlcoloredit (HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: processing this message is the only way I found to dynamically change
*      the color or an edit control - hjg.  LIMIT_TEXT_BOXES
*
*     -----
*   Modifications:
*****************************************************************************/
static LRESULT on_wm_ctlcoloredit (HWND hwndDlg, UINT message, WPARAM wParam,
                                   LPARAM lParam)
{
  int id;
  CONTROLITEM *pcontrol = NULL;
  HBRUSH hReturnBrush = NULL;
  BOOL bRet;
  COLORREF ans;
  RGBDEFINITION *rgbColor;

  id = GetDlgCtrlID((HWND)lParam);
  pcontrol = g2pvt_lookup_control_by_hwnd(id, hwndDlg);

  if (!pcontrol)
      return (LRESULT) hReturnBrush;

  // dig the colors out of the extra data
  if (pcontrol->_pExtraTypeData)
  {
    if (pcontrol->_pExtraTypeData->_pData)
    {
      COLORREF ans;
      EXTRA_TYPE_DATA *pETData;
      EXTRA_TEXTBX_DATA *pTBData;

      if (pETData = pcontrol->_pExtraTypeData)
      {
        pTBData = (EXTRA_TEXTBX_DATA*)pETData->_pData;

        if (pTBData->bBGColorValueSetByUser)
        {
          ans = SetBkColor((HDC)wParam,pTBData->backgroundColor);
          if (gv_hbrEditBG)
            bRet =  DeleteObject(gv_hbrEditBG); // delete the old brush from the last time around

          gv_hbrEditBG = CreateSolidBrush(pTBData->backgroundColor);
          hReturnBrush = gv_hbrEditBG;
        }

        if (pTBData->bTxColorValueSetByUser)
        {
          ans = SetTextColor((HDC)wParam, pTBData->textColor);
          if (gv_hbrEditBG)
            bRet =  DeleteObject(gv_hbrEditBG); // delete the old brush from the last time around

          // return the background color we have - this will force the text to paint
          ans = GetBkColor((HDC)wParam);
          gv_hbrEditBG = CreateSolidBrush(ans);
          hReturnBrush = gv_hbrEditBG;
        }
      }
    }
  }

  // override the earlier with 
  if (pcontrol->_font && (pcontrol->_font->_setFontColor || pcontrol->_font->_setBackgroundColor))
  {
    if(pcontrol->_font->_setFontColor)
    {
      ans = SetTextColor((HDC)wParam, RGB(pcontrol->_font->_fontColor->_red,pcontrol->_font->_fontColor->_green,pcontrol->_font->_fontColor->_blue));
      if (gv_hbrEditBG)
        bRet =  DeleteObject(gv_hbrEditBG); // delete the old brush from the last time around
    }
    if(pcontrol->_font->_setBackgroundColor)
      rgbColor=pcontrol->_font->_backgroundColor;
    else
      rgbColor=g2pvt_get_default_background_color_for_control(pcontrol);
    ans=RGB(rgbColor->_red,rgbColor->_green,rgbColor->_blue);
    SetBkColor((HDC)wParam,ans);
    gv_hbrEditBG = (HBRUSH)CreateSolidBrush(ans);
    hReturnBrush = gv_hbrEditBG;
  }

  return (LRESULT)hReturnBrush;
}

COLORREF get_background_color_for_label(CONTROLITEM *pcontrol) {
  COLORREF bgColor = NULL;
  RGBDEFINITION *rgbColor;
  assert(pcontrol != 0);
  // dig the background color out of the extra data
  if (EXTRA_TYPE_DATA *pETData = pcontrol->_pExtraTypeData) {
    if (EXTRA_TEXTBX_DATA *pTBData = (EXTRA_TEXTBX_DATA*)pETData->_pData) {
      if (pTBData->bBGColorValueSetByUser) {
        bgColor = pTBData->backgroundColor;
      }
    }
  }
  // override the earlier color with background color from FONT settings 
  if(pcontrol->_font && pcontrol->_font->_setFontColor && pcontrol->_font->_setBackgroundColor) {
    rgbColor = pcontrol->_font->_backgroundColor;
    bgColor = RGB(rgbColor->_red, rgbColor->_green, rgbColor->_blue);
  }
  return bgColor;
}

COLORREF get_foreground_color_for_label(CONTROLITEM *pcontrol) {
  COLORREF fgColor = NULL;
  RGBDEFINITION *rgbColor;
  assert(pcontrol != 0);
  // dig the foreground color out of the extra data
  if (EXTRA_TYPE_DATA *pETData = pcontrol->_pExtraTypeData) {
    if (EXTRA_TEXTBX_DATA *pTBData = (EXTRA_TEXTBX_DATA*)pETData->_pData) {
      if (pTBData->bTxColorValueSetByUser) {
        fgColor = pTBData->textColor;
      }
    }
  }
  // override the earlier with foreground color from FONT settings
  if(pcontrol->_font && pcontrol->_font->_setFontColor && pcontrol->_font->_setBackgroundColor) {
    rgbColor = pcontrol->_font->_fontColor;
    fgColor = RGB(rgbColor->_red, rgbColor->_green, rgbColor->_blue);
  }
  return fgColor;
}



/*****************************************************************************
* BOOL IsCommandLocked(ULONG cmd)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/

extern "C"
{
	BOOL IsCommandLocked(ULONG cmd)
	{
		return cmd == SC_SIZE || cmd == SC_MOVE || cmd == SC_MINIMIZE ||
			cmd == SC_MAXIMIZE || cmd == SC_NEXTWINDOW || cmd == SC_PREVWINDOW ||
			cmd == SC_CLOSE || cmd == SC_MOUSEMENU || cmd == SC_KEYMENU || cmd == SC_RESTORE;
	}
}

static LRESULT drawCustomPushButtonControl(HWND hwndDlg, WPARAM wParam, LPARAM lParam)
{
    LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;
    RECT itemRect = lpdis->rcItem;
    HDC dc = lpdis->hDC;
    // Get button's state
    BOOL bIsPressed = (lpdis->itemState & ODS_SELECTED);
    BOOL bIsFocused  = (lpdis->itemState & ODS_FOCUS);
    BOOL bIsDisabled = (lpdis->itemState & ODS_DISABLED);

    if (bIsFocused) {
        HBRUSH br = CreateSolidBrush(GetSysColor(COLOR_BTNSHADOW));  
        FrameRect(dc, &itemRect, br);
        InflateRect(&itemRect, -1, -1);
        DeleteObject(br);
    }

    CONTROLITEM *pcontrol = g2pvt_lookup_control_by_hwnd((int)wParam, hwndDlg);

    UINT uState = DFCS_BUTTONPUSH;
    if (pcontrol->_type == ctPushBtn && bIsPressed) {
        uState |= DFCS_PUSHED;
    }
    if (pcontrol->_type == ctToggleButton && pcontrol->checked) {
        uState |= DFCS_CHECKED;
    }
    DrawFrameControl(dc, &itemRect, DFC_BUTTON, uState);

    if (pcontrol->_font->_setBackgroundColor) {
        itemRect.bottom -= 2;
        itemRect.top += 1;
        itemRect.right -= 2;
        itemRect.left += 1;
        RGBDEFINITION* rgbColor = pcontrol->_font->_backgroundColor;
        COLORREF crColor = RGB(rgbColor->_red, rgbColor->_green, rgbColor->_blue);
        HBRUSH brBackground = CreateSolidBrush(crColor);
        FillRect(dc, &itemRect, brBackground);
        DeleteObject(brBackground);
    }

    // Draw icon
    HICON the_hicon = (HICON) SendMessage(GetDlgItem(hwndDlg, (int)wParam), BM_GETIMAGE, IMAGE_ICON, NULL);
    RECT captionRect = lpdis->rcItem;
    if (the_hicon == NULL) {
        COLORREF fgColor = GetSysColor(COLOR_BTNTEXT);
        if (pcontrol->_font->_setFontColor)
            fgColor = RGB(pcontrol->_font->_fontColor->_red, pcontrol->_font->_fontColor->_green, pcontrol->_font->_fontColor->_blue);
        SetTextColor(dc, fgColor);
        SetBkMode(dc, TRANSPARENT);
        wstring full_text(pcontrol->_mText);
        wstring label_text;
        extract_one_value(full_text, label_text);
        SIZE labelSize;
        GetTextExtentPoint32(dc, label_text.c_str(), label_text.length(), &labelSize);
        DrawState(
            dc,
            NULL,
            NULL,
            (LPARAM)label_text.c_str(),
            (WPARAM)label_text.length(),
            (int) (0.5 * (captionRect.right - captionRect.left - labelSize.cx)),
            (int) (0.5 * (captionRect.bottom - captionRect.top - labelSize.cy)),
            labelSize.cx,
            labelSize.cy,   
            DST_TEXT | (bIsDisabled ? DSS_DISABLED : DSS_NORMAL));
    } else {
        int icon_width = 16;
        int icon_height = 16;
        // Get icon's width and height info, use to compute the position.
        ICONINFO ii;
        BOOL fResult = GetIconInfo(the_hicon, &ii);
        if (fResult && ii.hbmMask) {
            BITMAP bm;
            fResult = GetObject(ii.hbmMask, sizeof(bm), &bm) == sizeof(bm);
            if (fResult) {
                icon_width = bm.bmWidth;
                icon_height = ii.hbmColor ? bm.bmHeight : bm.bmHeight / 2;
            }
            if (ii.hbmMask) DeleteObject(ii.hbmMask);
            if (ii.hbmColor) DeleteObject(ii.hbmColor);
        }
        // Draw icon in the push button
        DrawState(
            dc,
            NULL,
            NULL,
            (LPARAM)the_hicon,
            (WPARAM)NULL,
            (int) (0.5 * (captionRect.right - captionRect.left - icon_width)),
            (int) (0.5 * (captionRect.bottom - captionRect.top - icon_height)),
            icon_width,
            icon_height,
            DST_ICON | (bIsDisabled ? DSS_DISABLED : DSS_NORMAL));
    }
    return TRUE;
}

static LRESULT drawCustomStaticControl(HWND hwndDlg, WPARAM wParam, LPARAM lParam)
{
    LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;
    CONTROLITEM *pcontrol = g2pvt_lookup_control_by_hwnd((int)wParam, hwndDlg);
    wstring full_text = wstring(pcontrol->_mText);
    wstring label_text;
    extract_one_value(full_text, label_text);
    // get border color
    COLORREF borderColor = -1;
    if (full_text.length() > 0) {
        wstring borderColorStr;
        extract_one_value(full_text, borderColorStr);
        if (borderColorStr.length() > 0) {
            try {
                RGBDEFINITION *rgb = g2pvt_get_color_from_color_name(borderColorStr.c_str());
                if(rgb != NULL) {
                    borderColor = RGB(rgb->_red, rgb->_green, rgb->_blue);
                }
            } catch (int e) {
            }
        }
    }
    // get border width
    int borderWidth = -1;
    if (borderColor != -1) {
        if (full_text.length() > 0) {
            wstring borderWidthStr;
            extract_one_value(full_text, borderWidthStr);
            if (borderWidthStr.length() > 0) {
                swscanf(borderWidthStr.c_str(), L"%d", &borderWidth);
            }
        }
    }
    RECT itemRect = lpdis->rcItem;
    assert(itemRect.bottom - itemRect.top >= 2 * borderWidth);
    assert(itemRect.right - itemRect.left >= 2 * borderWidth);
    HDC dc = lpdis->hDC;
    // draw border
    if ((borderColor != -1) && (borderWidth > 0)) {
        HBRUSH br = CreateSolidBrush(borderColor);
        FillRect(dc, &itemRect, br);
        DeleteObject(br);
    }
    COLORREF bgColor = get_background_color_for_label(pcontrol);
    COLORREF fgColor = get_foreground_color_for_label(pcontrol);
    if (bgColor != NULL) {
        SetBkColor(dc, bgColor);
    } else {
        bgColor = GetBkColor(dc);
    }
    if (fgColor != NULL) {
        SetTextColor(dc, fgColor);
    } else {
        fgColor = GetTextColor(dc);
    }
    // draw background inside the border
    if (borderWidth > 0) {
        itemRect.left += borderWidth;
        itemRect.right -= borderWidth;
        itemRect.top += borderWidth;
        itemRect.bottom -= borderWidth;
    }
    HBRUSH br = CreateSolidBrush(bgColor);
    FillRect(dc, &itemRect, br);
    DeleteObject(br);
    // draw text
    DrawTextEx(dc, (LPWSTR)label_text.c_str(), -1, &itemRect, pcontrol->alignment | DT_VCENTER, NULL);
    return TRUE;
}

/*****************************************************************************
* LRESULT CALLBACK DynamicDlgProc (HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
LRESULT CALLBACK DynamicDlgProc (HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  CONTROLITEM *pcontrol = NULL;
  LPMEASUREITEMSTRUCT lpmis = NULL;
  LPDRAWITEMSTRUCT lpdis = NULL;
  DIALOGINFO *dlgInfo = (DIALOGINFO*)GetWindowLong(hwndDlg, GWLP_USERDATA);
  DWORD rc;
  int handle = (dlgInfo && dlgInfo->_pdialog) ? dlgInfo->_pdialog->g2_id : -1;

  if (dlgInfo && g2pvt_resizer_dlgproc(dlgInfo->resizer, &rc, hwndDlg, message, wParam, lParam)) {
    if (message == WM_SIZE)
      DynamicDlg_OnSize(dlgInfo, hwndDlg, wParam, lParam);
    return rc;
  }

  switch (message) {
  case WM_INITDIALOG:
    return (LRESULT)HANDLE_WM_INITDIALOG(hwndDlg, wParam, lParam,
      DynamicDlg_OnInitDialog);
    break;

  case WM_DESTROY:

    if (gv_hbrEditBG)
    {
       DeleteObject(gv_hbrEditBG); // delete the old brush; the brush is not in use
                                   // by any dlgs after the textbox is done painting.
       gv_hbrEditBG = 0;
    }
    cleanup_dialog_structures(hwndDlg);
    break;

  case WM_SETFOCUS:
    if (handle>0 && g2pvt_parent_window(hwndDlg) == NULL)
      g2pvt_send_window_activated(hwndDlg, handle);
    break;

  case WM_MOVE:
    if (handle>0 && g2pvt_parent_window(hwndDlg) == NULL) // Only for top-level dialog windows.
      g2pvt_send_window_moved(hwndDlg, handle, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    break;

  case WM_SIZE:
    return (LRESULT) DynamicDlg_OnSize(dlgInfo, hwndDlg, wParam, lParam);

  // LIMIT_TEXT_BOXES
  case WM_CTLCOLOREDIT:
  case WM_CTLCOLORSTATIC:
  case WM_CTLCOLORLISTBOX:
    return on_wm_ctlcoloredit(hwndDlg, message, wParam, lParam);
    break;
  case WM_DRAWITEM:
    lpdis = (LPDRAWITEMSTRUCT) lParam;
    switch(lpdis->CtlType) {
      case ODT_BUTTON:
        return drawCustomPushButtonControl(hwndDlg, wParam, lParam);
      case ODT_STATIC:
        return drawCustomStaticControl(hwndDlg, wParam, lParam);
      default:
        break;
    }
    return FALSE;
  case WM_GENSYM_SEND_INFO_TO_G2:
    HWND hwnd;
    int id;

    hwnd = (HWND)wParam;
    id = GetDlgCtrlID(hwnd);

    pcontrol = g2pvt_lookup_control_by_hwnd(id, hwndDlg);
    if (!pcontrol)
        break;

    g2pvt_ddlg_respond(hwndDlg, id, pcontrol->_respcode);
    break;

  case WM_COMMAND:
    return on_wm_command(hwndDlg, wParam, lParam);
    break;

  case WM_SYSCOMMAND:
    if (((wParam & 0xFFF0) == SC_CLOSE) && !g2pvt_syscommand_enabled_p(hwndDlg,SC_CLOSE))
      return 1;
    else if (dlgInfo != NULL && dlgInfo->_pdialog != NULL && dlgInfo->_pdialog->is_locked &&
          IsCommandLocked(wParam & 0xFFF0))
      return 1;
    break;

  case WM_NOTIFY:
    return (LRESULT)HANDLE_WM_NOTIFY(hwndDlg, wParam, lParam, DynamicDlg_OnNotify);
    break;

  case WM_CTLCOLORDLG:
  {
      if (dlgInfo->useBackgroundColor) 
      {
          assert(dlgInfo->hbrBackground != NULL);
          return (LRESULT) dlgInfo->hbrBackground;
      }
      break;
  }
  default:
    break;
  }

  return FALSE;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- "About Box" stuff
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* NTTYPE getNTVersion ()
*
*   Description:
*     Determine the specific variant of Windows NT on which we're running.
*   Input Arguments:
*   Returns:
*   Notes:
*     Windows NT 4.0 does not follow the documentation in the knowledge base.
*     Specifically, both versions set the appropriate registry key to
*     "LANMANNT" rather than "SERVERNT".
*
*     -----
*   Modifications:
*****************************************************************************/
static NTTYPE getNTVersion ()
{
  wchar_t Value [256];
  DWORD dwType = 0;
  DWORD dwSize = sizeof (Value); // sizeof, not DIM
  HKEY  hKey   = NULL;
  LONG  lStatus;

  lStatus = RegOpenKeyExW(HKEY_LOCAL_MACHINE,ProductOptions, 0,
    KEY_QUERY_VALUE, &hKey);
  if (ERROR_SUCCESS != lStatus) {
    return typeDefault;            // Windows NT
  }

  lStatus = RegQueryValueExW(hKey, ProductType, NULL, &dwType,
    (LPBYTE) Value, &dwSize);
  RegCloseKey(hKey);
  if (ERROR_SUCCESS != lStatus) {
    return typeDefault;            // Windows NT
  }

  if (0 == _wcsicmp(WinNT, Value)) {
    return typeWorkstation;        // Windows NT Workstation
  } else if (0 == _wcsicmp(ServerNT, Value)) {
    return typeServer;             // Windows NT Server
  } else if (0 == _wcsicmp(AdvancedServerNT, Value)) {
    return typeServer;             // Windows NT Advanced Server (3.1)
  }
  return typeDefault;              // Windows NT
}


/*****************************************************************************
* void g2pvt_display_OS_version_info (HWND hwnd)
*
*   Description:
*     Displays the operating system's version
*   Input Arguments:
*     hwnd: Window handle for the dialog box window
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_display_OS_version_info (HWND hwnd)
{
  BOOL           Result;
  HINSTANCE      hinst;
  NTTYPE         NtOsType;
  wchar_t        osver_string [256];
  wchar_t        format_string [256];
  OSVERSIONINFO  osver;

  // Get OS version information
  osver.dwOSVersionInfoSize = sizeof(osver);// Must initialize size member!

  Result = GetVersionEx(&osver);      // Retrieve version info
  assert(FALSE != Result);
  if (FALSE == Result)
    return;

  hinst = GetWindowInstance(hwnd);    // Get instance for LoadString

  switch (osver.dwPlatformId) {
  case VER_PLATFORM_WIN32_NT:         // Windows NT
    NtOsType = getNTVersion();
    wcscpy(format_string, IDS_PLATFORM_WIN32_NT_STRING);
    break;
  case VER_PLATFORM_WIN32s:           // Win32s on Windows 3.1
    wcscpy(format_string, IDS_PLATFORM_WIN32s_STRING);
    break;
  case VER_PLATFORM_WIN32_WINDOWS:    // Windows 95
    wcscpy(format_string, IDS_PLATFORM_WIN32_WINDOWS_STRING);
    // Windows 95 encodes extra info in HIWORD(dwBuildNumber)
    // Remove unwanted junk
    osver.dwBuildNumber = LOWORD(osver.dwBuildNumber);
    break;
  default:                            // Unknown operating system
    wcscpy(format_string, IDS_PLATFORM_UNKNOWN_STRING);
    break;
  }

  wsprintfW(osver_string, format_string,
    osver.dwMajorVersion,
    osver.dwMinorVersion,
    osver.dwBuildNumber);
  SetDlgItemTextW(hwnd, IDC_ABOUT_OSVERSION, osver_string);
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Functions for External Usage
%
% Description: functions not used by this file nor particularly associated with
%   the other functional groups of this file.
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* void g2pvt_set_component_parent_text (CONTROLITEM *new_item,
*                                         wchar_t *parent_text)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_set_component_parent_text (CONTROLITEM *new_item,
                                                 wchar_t *parent_text)
{
  new_item->_parentControlText = g2pvt_g2_to_windows_text(parent_text);
}


/*****************************************************************************
* void g2pvt_set_component_text (CONTROLITEM *new_item, wchar_t *text)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: I created this function basically because _mText was defined as
*     a TCHAR, and this file is UNICODE, but dialogs.c isn't, and, well, that's
*     just asking for trouble.  Therefore, made dialogs.c not directly access
*     any of the TCHAR member variables, but use functions instead. -jv, 2/08/05
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_set_component_text (CONTROLITEM *new_item, wchar_t *text)
{
  new_item->_mText = g2pvt_g2_to_windows_text(text);
}




//Function Start
/*****************************************************************************
void g2pvt_set_component_font (CONTROLITEM* new_item, wchar_t * font_name, long font_size, 
	wchar_t * font_color,wchar_t * control_background_color, long is_bold, long is_italic)
*
*   Description:
*   Input Arguments:
*   Returns: returns 1 if succesfully alloted the font components to CONTROLITEM. Returns 0 if memory is not allocated anywhere.
*   Notes: It sets the font attributes into the CONTROLITEM. Added in March 2015
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" int g2pvt_set_component_font (CONTROLITEM* new_item, wchar_t * font_name, long font_size, 
	wchar_t * font_color,wchar_t * control_background_color, long is_bold, long is_italic)
{
	new_item->_font->_fontName = g2pvt_g2_to_windows_text(font_name);
	new_item->_font->_fontSize = font_size;
	long r=0,g=0,b=0;
	bool valid_color=false;
	RGBDEFINITION *rgb;
	//Set if font is bold
	switch(is_bold){
	case 1:new_item->_font->_isBold=true;
		break;
	default:new_item->_font->_isBold=false;
	}

	//Set if font is italic
	switch(is_italic){
	case 1:new_item->_font->_isItalic=true;
		break;
	default:new_item->_font->_isItalic=false;
	}

	//set font colors
	if(font_color==NULL){
		new_item->_font->_setFontColor=false;
	}
	else{
		try{
			rgb=g2pvt_get_color_from_color_name(font_color);
			if(rgb==NULL){
				new_item->_font->_setFontColor=false;
			}
			else{
				new_item->_font->_fontColor=rgb;
			new_item->_font->_setFontColor=true;
			}
		}
		catch(int e)
		{
			return 0;
		}
	}


	//set control background colors
	if(control_background_color==NULL){
		new_item->_font->_setBackgroundColor=false;
	}
	else{
		try{
			rgb=g2pvt_get_color_from_color_name(control_background_color);
			if(rgb==NULL){
				new_item->_font->_setBackgroundColor=false;
			}
			else{
				new_item->_font->_backgroundColor=rgb;
				new_item->_font->_setBackgroundColor=true;
			}
		}
		catch(int e)
		{
			return 0;
		}
		
	}
	return 1;
}
//Function End

/*****************************************************************************
* void g2pvt_set_dialog_structure_title (GENSYMDIALOG *dialog,
*                                          wchar_t *title)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_set_dialog_structure_title (GENSYMDIALOG *dialog,
                                                  wchar_t *title)
{
  dialog->_mTitle = g2pvt_g2_to_windows_text(title);
}


/*****************************************************************************
* void g2pvt_set_dialog_title (GENSYMDIALOG *dialog)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_set_dialog_title (GENSYMDIALOG *dialog)
{
  SendMessage(dialog->hwnd, WM_SETTEXT, 0, (LPARAM)dialog->_mTitle);
}


/*****************************************************************************
* void g2pvt_set_dialog_structure_backgroundColor (GENSYMDIALOG *dialog, DIALOGINFO *dialogInfo, wchar_t *color)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_set_dialog_structure_backgroundColor (GENSYMDIALOG *dialog, DIALOGINFO *dialogInfo, wchar_t *color)
{
    if (dialogInfo->hbrBackground)
    {
        DeleteObject(dialogInfo->hbrBackground);
	dialogInfo->hbrBackground = NULL;
    }

    if (wcslen(color) > 0) 
    {
        dialogInfo->useBackgroundColor = TRUE;
        COLORREF rgb = g2pvt_get_color_ref_from_color_name(color);
        dialogInfo->hbrBackground = CreateSolidBrush(rgb);
        dialogInfo->backgroundColor = rgb;
    }
    else
    {
        dialogInfo->useBackgroundColor = FALSE;
    }
}

/*****************************************************************************
* void g2pvt_set_dialog_background (GENSYMDIALOG *dialog)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_set_dialog_background (GENSYMDIALOG *dialog)
{
  SendMessage(dialog->hwnd, WM_CTLCOLORDLG, 0, 0);
}


/*****************************************************************************
* void g2ext_specify_text_box_extensions (long dlgId)
*
*   Description:
*   Input Arguments:
*   Returns:
*
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2ext_specify_text_box_extensions (long dlgId)
{
  use_simple_text_boxes_p = FALSE;
}


/*****************************************************************************
* wchar_t *g2pvt_get_component_parent_text (CONTROLITEM *new_item)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" wchar_t *g2pvt_get_component_parent_text (CONTROLITEM *pItem)
{
  wchar_t *component_text;

  component_text = pItem->_parentControlText;
  if (component_text == NULL) {
    return (wchar_t *) NULL;
  }
  return wcsdup(component_text);
}


/*****************************************************************************
* wchar_t *g2pvt_get_component_text (CONTROLITEM *new_item)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" wchar_t *g2pvt_get_component_text (CONTROLITEM *pItem)
{
  wchar_t *component_text;

  component_text = pItem->_mText;
  if (component_text == NULL) {
    return (wchar_t *) NULL;
  }
  return wcsdup(component_text);
}


static void clamp_within_monitor(POINT *pt, int nWndWidth, int nWndHeight)
{
    HMONITOR hmon = MonitorFromPoint(*pt, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX info;

    info.cbSize = sizeof info;
    if (GetMonitorInfo(hmon, &info) == 0) {
        // should never happen
        return;
    }

    pt->x = max(info.rcMonitor.left, min(pt->x, info.rcMonitor.right - nWndWidth));
    pt->y = max(info.rcMonitor.top, min(pt->y, info.rcMonitor.bottom - nWndHeight));
}


/*****************************************************************************
* void g2pvt_position_dialog (HWND hwndDlg, long xPos, long yPos, BOOL mdi_child,
                              POINT *pPos, G2DialogMonitorPreference g2DlgMonPref)
*
*   Description:
*      g2pvt_position_dialog() positions hwndDlg according to the position
*      specified by xPos and yPos.  Certain special constant values for (xPos,
*      yPos) are reserved as special flags with special meanings for position in
*      certain logical positions, e.g., in the center of the parent window, in
*      the center of the desktop, etc. (See dyndlgs.h for the constants and
*      their meanings.)  If a position is not one of these special values, it is
*      a coordinate relative to the top left of the desktop.
*
*      Note: Windows distinguishes "work area" from "desktop", so we will stick
*      with those distinctions, i.e., "desktop" as the entire screen, and "work
*      area" the area of the desktop not obscured by the system task bar or any
*      application tool bars.
*
*      If the mdi_child boolean argument is true, the interpretation of xPos and
*      yPos for desktop and working-area symbolic positions are overridden and
*      made relative to the MDI frame's client area.  Also, in this case
*      absolute x/y positions are made relative to the MDI frame's client area.
*      Thus, in this case desktop, working-area, and parent-window symbolic
*      positions are all interpreted in the same way, i.e. relative to the
*      parent of the dialog.
*
*   Input Arguments:
*   Returns: nothing
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
extern "C" void g2pvt_position_dialog (HWND hwndDlg, long xPos, long yPos, BOOL mdi_child,
                                       POINT *pPos, G2DialogMonitorPreference g2DlgMonPref)
{
  RECT rectWnd;
  RECT rectClient;
  RECT rectDesktop;
  RECT rectWorkarea;
  HWND hwndParent;
  HWND hwndDesktop;
  int nX, nY;
  int nParentWidth, nParentHeight, nWndWidth, nWndHeight;
  int nDesktopWidth, nDesktopHeight;
  int nWorkareaWidth, nWorkareaHeight;
  int client_left, client_top, client_right, client_bottom;
  int desktop_left, desktop_top, desktop_right, desktop_bottom;
  int workarea_left, workarea_top, workarea_right, workarea_bottom;
  POINT pt;

  // Get the parent (i.e., client area) and desktop windows
  hwndDesktop = GetDesktopWindow();
  hwndParent = hwndMain;

  // Get the bounding rectangles for the windows (client area for parent
  // window).
  GetClientRect(hwndParent, &rectClient);

  // Get work area for current monitor
  HMONITOR hMonitor;
  MONITORINFOEX mix;
  // Get monitor for window position
  switch (g2DlgMonPref) {
    case g2dlgPrimaryMonitor:
      pt.x = pt.y = 0;
      hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
      break;
    case g2dlgNearestMonitor:
      hMonitor = MonitorFromWindow(hwndDlg, MONITOR_DEFAULTTONEAREST);
      break;
  }

  mix.cbSize = sizeof(mix);
  if( GetMonitorInfo(hMonitor, &mix) == 0 )
  {
	GetWindowRect(hwndDesktop, &rectWorkarea);  // if error (unlikely)
  }
  else
  {
	rectWorkarea.left	= mix.rcWork.left;
	rectWorkarea.right	= mix.rcWork.right;
	rectWorkarea.top	= mix.rcWork.top;
	rectWorkarea.bottom	= mix.rcWork.bottom;
  }

  // Get the bounding rectangles for the windows (client area for parent
  // window).
  rectDesktop.left   = mix.rcMonitor.left;
  rectDesktop.right  = mix.rcMonitor.right;
  rectDesktop.top    = mix.rcMonitor.top;
  rectDesktop.bottom = mix.rcMonitor.bottom;

  GetWindowRect(hwndDlg, &rectWnd);

  // Get window, parent, desktop, and working area width/height, and
  // client edges. In mdi_child case, override the desktop and working
  // area edges and width/height with those of the client:
  pt.x = rectClient.left; pt.y = rectClient.top;
  ClientToScreen(hwndParent, &pt);
  client_left = pt.x;  client_top = pt.y;

  pt.x = rectClient.right; pt.y = rectClient.bottom;
  ClientToScreen(hwndParent, &pt);


  client_right = pt.x;  client_bottom = pt.y;

  desktop_left = (mdi_child ? client_left : rectDesktop.left);
  desktop_top = (mdi_child ? client_top : rectDesktop.top);
  desktop_right = (mdi_child ? client_right : rectDesktop.right);
  desktop_bottom = (mdi_child ? client_bottom : rectDesktop.bottom);

  workarea_left = (mdi_child ? client_left : rectWorkarea.left);
  workarea_top = (mdi_child ? client_top : rectWorkarea.top);
  workarea_right = (mdi_child ? client_right : rectWorkarea.right);
  workarea_bottom = (mdi_child ? client_bottom : rectWorkarea.bottom);

  nParentWidth = client_right - client_left;
  nParentHeight = client_bottom - client_top;
  nDesktopWidth = rectDesktop.right - rectDesktop.left;
  nDesktopHeight = rectDesktop.bottom - rectDesktop.top;
  nWorkareaWidth = rectWorkarea.right - rectWorkarea.left;
  nWorkareaHeight = rectWorkarea.bottom - rectWorkarea.top;
  nWndWidth = rectWnd.right - rectWnd.left;
  nWndHeight = rectWnd.bottom - rectWnd.top;

  // Compute the new location of the window
  nX = ((xPos == GPD_CENTER)
    ? client_left + ((nParentWidth - nWndWidth) / 2)
    : ((xPos == GPD_DESKTOP_CTR)
    ? rectDesktop.left + ((nDesktopWidth - nWndWidth) / 2)
    : ((xPos == GPD_WORKAREA_CTR)
    ? rectWorkarea.left + ((nWorkareaWidth - nWndWidth) / 2)

    // 2 parent-window horiz. edges X exact vs. near:
    : ((xPos == GPD_LEFT)
    ? client_left
    : ((xPos == GPD_NEAR_LEFT)
    ? client_left + GPD_NEAR_DISTANCE
    : ((xPos == GPD_RIGHT)
    ? client_right - nWndWidth
    : ((xPos == GPD_NEAR_RIGHT)
    ? client_right - nWndWidth - GPD_NEAR_DISTANCE

    // 2 desktop horiz. edges X exact vs. near:
    : ((xPos == GPD_DESKTOP_LEFT)
    ? desktop_left
    : ((xPos == GPD_NEAR_DESKTOP_LEFT)
    ? desktop_left + GPD_NEAR_DISTANCE
    : ((xPos == GPD_DESKTOP_RIGHT)
    ? desktop_right - nWndWidth
    : ((xPos == GPD_NEAR_DESKTOP_RIGHT)
    ? desktop_right - nWndWidth - GPD_NEAR_DISTANCE

    // 2 workarea horiz. edges X exact vs. near:
    : ((xPos == GPD_WORKAREA_LEFT)
    ? workarea_left
    : ((xPos == GPD_NEAR_WORKAREA_LEFT)
    ? workarea_left + GPD_NEAR_DISTANCE
    : ((xPos == GPD_WORKAREA_RIGHT)
    ? workarea_right - nWndWidth
    : ((xPos == GPD_NEAR_WORKAREA_RIGHT)
    ? workarea_right - nWndWidth - GPD_NEAR_DISTANCE
    // straight x position (relative to working
    // area):
    : xPos + workarea_left)))))))))))))));
  nY = ((yPos == GPD_CENTER)
    ? client_top + ((nParentHeight - nWndHeight) / 2)
    : ((yPos == GPD_DESKTOP_CTR)
    ? rectDesktop.top + ((nDesktopHeight - nWndHeight) / 2)
    : ((yPos == GPD_WORKAREA_CTR)
    ? rectWorkarea.top + ((nWorkareaHeight - nWndHeight) / 2)

    // 2 parent-window vert. edges X exact vs. near:
    : ((yPos == GPD_TOP)
    ? client_top
    : ((yPos == GPD_NEAR_TOP)
    ? client_top + GPD_NEAR_DISTANCE
    : ((yPos == GPD_BOTTOM)
    ? client_bottom - nWndHeight
    : ((yPos == GPD_NEAR_BOTTOM)
    ? client_bottom - nWndHeight - GPD_NEAR_DISTANCE

    // 2 desktop vert. edges X exact vs. near:
    : ((yPos == GPD_DESKTOP_TOP)
    ? desktop_top
    : ((yPos == GPD_NEAR_DESKTOP_TOP)
    ? desktop_top + GPD_NEAR_DISTANCE
    : ((yPos == GPD_DESKTOP_BOTTOM)
    ? desktop_bottom - nWndHeight
    : ((yPos == GPD_NEAR_DESKTOP_BOTTOM)
    ? desktop_bottom - nWndHeight - GPD_NEAR_DISTANCE

    // 2 workarea vert. edges X exact vs. near:
    : ((yPos == GPD_WORKAREA_TOP)
    ? workarea_top
    : ((yPos == GPD_NEAR_WORKAREA_TOP)
    ? workarea_top + GPD_NEAR_DISTANCE
    : ((yPos == GPD_WORKAREA_BOTTOM)
    ? workarea_bottom - nWndHeight
    : ((yPos == GPD_NEAR_WORKAREA_BOTTOM)
    ? workarea_bottom - nWndHeight - GPD_NEAR_DISTANCE

    // straight y position (relative to working
    // area):
    : yPos + workarea_top)))))))))))))));

  // restrict to range so that it fits within the desktop, at least on top left
  pt.x = nX;
  pt.y = nY;
  clamp_within_monitor(&pt, nWndWidth, nWndHeight);
  ClientToScreen(hwndDesktop, &pt);

  // Move the window to its new location
  SetWindowPos(hwndDlg, HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
  if (pPos)
    *pPos = pt;
}
