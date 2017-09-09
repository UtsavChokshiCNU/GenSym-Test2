/*-*- Mode: C++ -*-*/
// dyndlgs.h

#pragma once

#ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x400
#endif

#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <objbase.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>

#include "resizer.h"
#include "lispicp.h"

#ifdef _DEBUG
/* Note, g2ext_puts already has its own "#ifdef GPRINTF" bifurcation, but we
 * don't want to even make a no-op function call, if we're not GPRINTF.
 */
#  ifdef __cplusplus
extern "C" void g2ext_puts (char *pMessage);
#  else
extern void g2ext_puts (char *pMessage);
#  endif

#  define DLGERROR(msg) g2ext_puts(msg)
#else
#  define DLGERROR(msg)
#endif




///////////////////////////////////////////////////////////////////
//        This header describes the layout of a user interface control
//  used in building dynamic dialog boxes.
///////////////////////////////////////////////////////////////////
//
#define MAX_TEXT               100       // TODO: use realistic maximum
#define MAX_RESPONSE           256
#define MAX_RESPONSES_LEN      512
#define MAX_CLASSNAME_LEN       50       // maximum length of window class name
#define MAX_INDEX_LENGTH        10

// When we need to resize the pcontrols member of the GENSYMDIALOG structure,
// this constant is used as the multiplier.  A value of 1.10 means, increase the
// size of the array by 10%.  -jv, 4/11/04
#define DYNAMIC_DIALOGS_COMPONENT_MULTIPLIER  1.10

#define DYNAMIC_DIALOG_SUCCEEDED 0
#define DYNAMIC_DIALOG_FAILED   -1

#define DYNAMIC_DIALOG_UPDATE_SUCCEEDED 0
#define DYNAMIC_DIALOG_UPDATE_FAILED -1

#define DYNAMIC_DIALOG_QUERY_SUCCEEDED 0L
#define DYNAMIC_DIALOG_QUERY_FAILED   -1L

#define ID_FOR_NO_COMPONENT -1L

#define PARENT_IS_ENTIRE_DIALOG -1

#define TVIEW_DEFAULT_COL_WIDTH_HEADER -1
#define TVIEW_DEFAULT_COL_WIDTH_TEXT   -2

#define TVIEW_DEFAULT_ROW_HEIGHT       -1


#define TW_INITIATED_UPDATE    1L
#define G2_INITIATED_UPDATE    2L

#define MULTI_UPDATE_BEGIN     4L
#define MULTI_UPDATE_CONTINUE  8L
#define MULTI_UPDATE_FINISH   16L
#define FOCUS_CHANGED_UPDATE   32L

#define TW_MULTI_UPDATE_BEGIN     5L
#define TW_MULTI_UPDATE_CONTINUE  9L
#define TW_MULTI_UPDATE_FINISH   17L

#define G2_MULTI_UPDATE_BEGIN     6L
#define G2_MULTI_UPDATE_CONTINUE 10L
#define G2_MULTI_UPDATE_FINISH   18L


// miscellaneous messages
#define G2PVT_USER_GESTURE        1L
#define G2PVT_SEND_WSV_ADDRESS    8L

// special control styles
// #define G2_LVS_GRIDLINES       0x0001L
// #define G2_LVS_SORT            0x0002L

#define G2_BS_SELECT           0x0004L

#define G2_CTV_SEL_ONLY_LEAVES 0x0008L

#define G2_UDS_INTEGERS        0x0001L

#define G2_DTS_SHOW_TIME       0x0001L
#define G2_DTS_SHOW_DATE       0x0002L
#define G2_DTS_24_HOUR         0x0004L

// defines for CGridCellFormattedDate in richeditgrid/newcelltypes
#define G2_DTS_US_FORMAT       0x0000L // mm/dd/yyyy  - default
#define G2_DTS_EU_FORMAT       0x0010L // dd/mm/yyyy
#define G2_DTS_GOV_FORMAT      0x0020L // yyyy/mm/dd

#define G2_ANCHOR_TOP    0x0010	   // Agrees with ANCHOR_xxx, left-shifted 4 bits.
#define G2_ANCHOR_BOTTOM 0x0020
#define G2_ANCHOR_LEFT   0x0040
#define G2_ANCHOR_RIGHT  0x0080
#define G2_ANCHOR_MASK   0x00F0
#define G2_ANCHOR_P      0x0100	   // Set if anchor bits are valid.

#define G2_CONTAINER_CLASS L"GensymContainer" // Generic container window

// window class names
#define GDD_BUTTON          L"Button"
#define GDD_GROUPBOX        GDD_BUTTON   // type of button with BS_GROUPBOX style
#define GDD_PUSHBUTTON      GDD_BUTTON   // type of button with BS_PUSHBUTTON style
#define GDD_RADIOBUTTON     GDD_BUTTON   // type of button with BS_RADIOBUTTON style
#define GDD_CHECKBOX        GDD_BUTTON   // type of button with BS_CHECKBOX style
#define GDD_STATIC          L"Static"
#define GDD_TEXT            L"Edit"
#define GDD_SPIN            L"msctls_updown32"
#define GDD_TABS            L"SysTabControl32"
#define GDD_COMBO           L"COMBOBOX"
#define GDD_COMBOTREE       L"COMBOBOX"
#define GDD_COLOR           L"COMBOBOX"  // special kind of combo-box
#define GDD_LIST            L"LISTBOX"
#define GDD_GRID            L"SysListView32"
#define GDD_LISTVIEW        L"SysListView32"
#define GDD_MASKEDIT        L"CXTMaskEdit"
#define GDD_WORKSPACE       G2_CONTAINER_CLASS // L"GensymWorkspaceViewClass" goes inside
#define GDD_DURATION        DATETIMEPICK_CLASS
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
#define GDD_SHORTDURATION     DATETIMEPICK_CLASS
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
#define GDD_CALENDAR        DATETIMEPICK_CLASS
#define GDD_TIMEOFDAY       DATETIMEPICK_CLASS
#define GDD_PROGRESS        PROGRESS_CLASS
#define GDD_TRACKBAR        TRACKBAR_CLASS
#define GDD_SLIDER          TRACKBAR_CLASS
#define GDD_RICHGRID        L"MFCGridCtrl"
#define GDD_ADVANCEDCOLOR   L"CAdvancedColorPicker"
#define GDD_CHECKLISTBOX    L"CCheckListBox"
#define GDD_TOGGLEBUTTON    GDD_BUTTON
#define GDD_TWNG_SPIN       L"CSpinButtonCtrlTwng"

// g2pvt_get_name_of_control_type
// create_win32_control_1
// g2pvt_init_control
// get_control_value
// on_wm_command
// (maybe) DynamicDlg_OnNotify
// modify_control_value

// At some point, I hoped these numbers might mean something at a bitwise level,
// but they're not going to (and we never assumed they did).  -jv, 3/05/05
#define ctTabs             32
#define ctProgressBar      40
#define ctTrackBar         50
#define ctSlider           51
#define ctComboTreeView    65  /* TWNG only */
#define ctComboBox         67
#define ctIcon             68  /* TWNG only */
#define ctColor            80  /* different implementation in TWNG */
#define ctAdvancedColor    81  /* Advanced color picker, TWNG only */
#define ctListBox          70  
#define ctCheckListBox     71  /* list box with checks implemented in TWNG */
#define ctTextBx          128
#define ctMaskEdit        129  /* TWNG only */
#define ctStatic          130  /* This is label in Lisp */
#define ctSpin            133  /* different implementation in TWNG */
#define ctDuration        134  /* TWNG only */
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
#define ctShortDuration     135
//Gensym-184-HQ-5684960-UCI-Add the GDU Duration Controls
#define ctCalendar        136
#define ctTimeOfDay       137
#define ctWorkspace       146  /* multiwindow only */
#define ctGroup           256
#define ctRadio           258
#define ctCheck           260
#define ctPushBtn         262
#define ctToggleButton    263
#define ctTabularView     512  /* TWNG only */
#define ctGridView        641  /* TWNG only */

// dialog types
#define MODAL               1
#define MODELESS            2
#define MDI_CHILD           4

// dynamic update types
#define ADD                   1
#define REPLACE               2
#define HIDE                  3
#define SHOW                  4
#define ENABLE                5
#define DISABLE               6
#define CHECK                 7
#define UNCHECK               8
#define DROPDOWN_WIDTH        9
#define DROPDOWN_HEIGHT       10
#define SELECTED_TAB          11

// callback types
#define DLG_NO_RESPONSE      0   // no response required
#define DLG_CLOSE            1   // dismiss the dialog
#define DLG_APPLY_CHANGES    2
#define DLG_RESPOND          4   // response required with responding control's state
#define DLG_SEND_ALL_DATA    8
#define DLG_NO_CALLBACK     16

#define DLG_CANCEL           1 //  DLG_CLOSE
#define DLG_OK               3 // (DLG_CLOSE & DLG_APPLY_CHANGES)
#define DLG_JUST_RESPOND     4 //  DLG_RESPOND

#define DLG_RESPOND_OK       7 // (DLG_OK & DLG_RESPOND)
#define DLG_RESPOND_ALL     12 // (DLG_SEND_ALL_DATA & DLG_RESPOND)
#define DLG_RESPOND_ALL_OK  15 // (DLG_OK & DLG_SEND_ALL_DATA)

#define DLG_CANCEL_NO_CALLBACK 17 //  (DLG_CLOSE & DLG_NO_CALLBACK)

#define DLG_CLIENT_SIDE_PROBLEM  32


// monitor preference constants. should be synchronized with monitor-preference-settings
// definitions in dialogs.lisp
enum G2DialogMonitorPreference {
  g2dlgPrimaryMonitor,
  g2dlgNearestMonitor
};

// Dialog positioning constants. These are used by g2pvt_position_dialog(),
// hence the prefix "GPD".  Where "parent window" is used below, this should be
// taken to mean the client area of the parent window.
// Must be kept in synch with dialog-symbol-to-code-map in controls.lisp.

#define GPD_CENTER -10000       // center of the parent window
#define GPD_DESKTOP_CTR -10001  // center of the desktop
#define GPD_LEFT -10002         // left edge of the parent window
#define GPD_TOP -10003          // top edge of the parent window
#define GPD_RIGHT -10004        // right edge of the parent window
#define GPD_BOTTOM -10005       // bottom edge of the parent window
#define GPD_NEAR_LEFT -10006    // near the left edge of the parent window
#define GPD_NEAR_TOP -10007     // near the top edge of the parent window
#define GPD_NEAR_RIGHT -10008   // near the right edge of the parent window
#define GPD_NEAR_BOTTOM -10009  // near the bottom edge of the parent window
#define GPD_DESKTOP_LEFT -10010         // left edge of the desktop
#define GPD_DESKTOP_TOP -10011          // top edge of the desktop
#define GPD_DESKTOP_RIGHT -10012        // right edge of the desktop
#define GPD_DESKTOP_BOTTOM -10013       // bottom edge of the desktop
#define GPD_NEAR_DESKTOP_LEFT -10014    // near the left edge of the desktop
#define GPD_NEAR_DESKTOP_TOP -10015     // near the top edge of the desktop
#define GPD_NEAR_DESKTOP_RIGHT -10016   // near the right edge of the desktop
#define GPD_NEAR_DESKTOP_BOTTOM -10017  // near the bottom edge of the desktop

#define GPD_WORKAREA_CTR -10018          // center of the working area
#define GPD_WORKAREA_LEFT -10019         // left edge of the working area
#define GPD_WORKAREA_TOP -10020          // top edge of the working area
#define GPD_WORKAREA_RIGHT -10021        // right edge of the working area
#define GPD_WORKAREA_BOTTOM -10022       // bottom edge of the working area
#define GPD_NEAR_WORKAREA_LEFT -10023    // near the left edge of the working area
#define GPD_NEAR_WORKAREA_TOP -10024     // near the top edge of the working area
#define GPD_NEAR_WORKAREA_RIGHT -10025   // near the right edge of the working area
#define GPD_NEAR_WORKAREA_BOTTOM -10026  // near the bottom edge of the working area


// The above GPD_NEAR_... constants result in positions that are offset from the
// designated position by a small number of units. This number is 11, and is
// defined by the constant GPD_NEAR_DISTANCE.

// The reason we use 11 is that it's the default value for margin-in-pane in the
// function put-workspace-on-pane in G2's PANE module, so most classic G2
// "dialogs" (e.g., icon editor, text editor, inspect) tend to be put up that
// distance from the top left corner.  This makes it easiest to match G2's popup
// behavior, and it's not too bad.

#define GPD_NEAR_DISTANCE 11

/****************************************************************************************
* Some controls require extra information. pControl->_pExtraTypeData was added
* for this purpose.  For any control that needs the extra information, _pExtraTypeData 
* is allocated. Based on the type of control, pExtraTypeData->_pData, points to the
* specific information needed. In the case of ctComboTreeView the extra data is the
* structure
* EXTRA_COMBO_TREE_VIEW_DATA
*
*
****************************************************************************************/
#define TREE_VIEW_COMBO_BOX_USE_DEF -1 //use this constant to maintain original behavior


// this structure is used when G2 calls gw-ui-modify-custom-dialog on a ctTextBx with the REPLACE option 
typedef struct
{
  BOOL bSelectionValuesSetByUser; // TRUE if the user set the Selection values
  BOOL bTxColorValueSetByUser;    // TRUE if the user set the Text color
  BOOL bBGColorValueSetByUser;    // TRUE if the user set the BG color
  int start; // start position for selection or caret
  int end;   // end position for selection or caret
  COLORREF textColor;
  COLORREF backgroundColor;
} EXTRA_TEXTBX_DATA;


typedef struct
{
  long DroppedHeight;
  long DroppedWidth;
} EXTRA_COMBO_TREE_VIEW_DATA;

#define BIT_OF_PUSH_BUTTON_IS_DEFAULT 1024

typedef struct
{
  HWND m_hwndTip;
  UINT m_tInfo_uId;
  int isDefault;
} EXTRA_PUSH_BUTTON_DATA;

typedef struct GV_DATA_LINKED_LIST
{
  wchar_t *spec;
  struct GV_DATA_LINKED_LIST *next;
} EXTRA_GRID_VIEW_DATA;

typedef struct
{
  int  _type;
  void *_pData;
} EXTRA_TYPE_DATA;

//FontDefinition defining fontsize,font family,font color

typedef struct
{
	long _red;
	long _green;
	long _blue;
} RGBDEFINITION;


typedef struct
{
	long _fontSize;
	wchar_t * _fontName;
	BOOL _isBold;
	BOOL _isItalic;
	BOOL _setFontColor;
	RGBDEFINITION *_fontColor;
	BOOL _setBackgroundColor;
	RGBDEFINITION *_backgroundColor;
} FONTDEFINITION;



//Changes End Sushrut
  // _mText means different things for different controls:
  // listbox & combobox - a delimited list of values
  // textbox - text value
  // static - caption
  // button - button text
  // group - caption
  // radio & check - text
  // spinner - formatted string: "defaultvalue,minvalue,maxvalue"
  // tabs - formatted string e.g. "Role//Financial//Assets//Cost"

typedef struct
{
  long _dialogId;               // unique dialog identifier
  int _type;
  long _controlId;
  long _parentControlId;        // id of immediate containing control
  wchar_t *_parentControlText;  // e.g. text of containing tab
  long _x;
  long _y;
  long _width;
  long _height;
  long _styles;                 // use the ones directly defined by Windows??
  long _g2styles;               // G2-specific styles
  wchar_t *_mText;              // meaning depends on control-type
  int _respcode;                // see "callback types" above
  EXTRA_TYPE_DATA *_pExtraTypeData; // any extra data for a specific control type
  HWND _pendingReplacementWnd;	// Used by g2pvt_replace_control_in_dialog()
  int view_handle;		// G2 handle of native view, if any, corres. to this item.
  //Font addition feb 2015
  FONTDEFINITION *_font;
  //alignment of static control
  int alignment;
  //check status of toggle-button control
  int checked;
} CONTROLITEM;



typedef struct
{
  long _controlId;
  wchar_t *_mResponseString;
} CONTROLITEMRESPONSE;

typedef struct tag_GensymDialogResponse
{
  long dialog_id;
  long initiating_control_id;   // id of the control that triggered the response
  CONTROLITEMRESPONSE **presponses;
  long response_count;          // number of responses
  long array_size;              // maximum number of responses
} GENSYMDLGRESPONSE;

typedef struct tag_GensymDialog
{
  long g2_id;			// G2-assigned integer handle
  long dialog_id;		// TW-assigned cpointer

  //Gensym-683-TAM1-CN-BF-JIRA-224-More TWNG leaks involving native dialogs
  //add dialog_g2pointer to save g2pointer which is cached in g2ext_show_dialog
  //when dismissing this dialog, use it to decache g2pointer
  long dialog_g2pointer;

  CONTROLITEM **pcontrols;
  // control_count is how many controls have actually been added to the
  // dialog so far
  long control_count;
  // array_size is how big the array is, i.e., how many controls we COULD add
  long array_size;
  // title
  wchar_t *_mTitle;
  // width
  int width;
  // height
  int height;
  // type - modal or modeless
  int _iDlgType;
  // HWND of created dialog; only used on the windows side
  HWND hwnd;
  // the response structure
  GENSYMDLGRESPONSE *mResponse;
  int *enabledWindows;      // Zero-terminated array of IDs for windows which were enabled
                            // at the time this dialog was posted (if modal).
  int is_locked;
  // for maintaining a linked list of dialog specs
  struct tag_GensymDialog *next;

  int need_new_group;
  // used to determine whether it's during initially show dialog or not
  int inShowDialog;
} GENSYMDIALOG;

// used to pass to the function that creates child dialog windows for each tab
// in a tab control
typedef struct
{
  long _tabControlId;
  int _selectedTab;
  wchar_t *_pszTabText;
} DLGPARAMS;

// used to keep track of a child dialog window associated with a tab
typedef struct _TABITEM
{
  HWND hwndChildDlg;            // hwnd of containing child dialog
  UINT tabControlId;            // control id
  UINT tabIndex;                // nth tab - zero-based index
  wchar_t *szTabName;           // tab text
  RECT displayRect;             // enclosing display rectangle
  struct _TABITEM *next;        // next tab
  Resizer *resizer;		// Resize manager, if any.
} TABITEM;

// Helps us keep track of created controls without having to know what child
// dialog hwnd they belong to.  (GetDlgItem() wasn't reliable since you had to
// know what hwnd the child control belonged to)
typedef struct _CONTROLHWND
{
  long controlId;
  HWND hwndControl;
  // pObj is void * because only twng uses this (MFC), but dyndlgs.h
  // is included in G2 and TW
  void *pObj; /* if the control is an MFC object, save the object instead of the handle */
  struct _CONTROLHWND *next;
} CONTROLHWND;

// private per-dialog data
typedef struct
{
  GENSYMDIALOG *_pdialog;
  TABITEM *_tabPages;
  CONTROLHWND *_controlHwndList;
  long _numControlHwnds;
  int icon;			// Native icon handle
  BOOL resizable;
  Resizer *resizer;		// Resize manager, if specified.
  COLORREF backgroundColor;
  HBRUSH hbrBackground;
  BOOL useBackgroundColor;
} DIALOGINFO;

