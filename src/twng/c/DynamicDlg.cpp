/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      DynamicDlg.cpp
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):
+   MS Windows portions:
+              2005 -      hgoddard, jv
+
+ Description:  Implementation of MFC-based dialogs
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
+   01/03/05,  jv: adding these comments.  Heidi created this file.
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
#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"

#include "AdvancedColorPicker/Advancedcolorpicker.h"
#include "combotree/ComboTree.h"
#include "ImageWidget/G2ImageWidget.h"
#include "colorpicker/ColorCombo.h"
#include "duration/NewDuration1.h"
#include "richeditgrid/GridExtras.h"
#include "G2CheckListBox/G2CheckListBox.h"
#include "SpinWidget/SpinnerTwng.h"
#include "GensymEditBox/GensymEditBox.h"
#include "DynamicTabsDlg.h"
#include "dyndlgs.h"
#include "DynamicDlg.h"
#include "cprim.h"

#ifdef _DEBUG
#  define new DEBUG_NEW
#  undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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


// See comments in comment-header of function mfc_control_rectangle for an
// explanation of these values.  -jv, 3/05/05
#define DIALOG_UNITS_PER_COLOR_ROW            10
#define ADDITIONAL_HEIGHT_FOR_TWNG_COLOR_PK   20
#define COMBO_BOX_SET_SELECTION     1

extern "C" XCOLOR XMetaColorArray[];
extern "C" CONTROLITEM *g2pvt_lookup_control_by_hwnd (int controlId, HWND hwnd);
extern "C" CONTROLITEM *g2pvt_lookup_control_by_id(int controlId, GENSYMDIALOG *dialog);
extern "C" GENSYMDIALOG *g2pvt_find_dialog_by_id (long dlgId);
extern "C" LPDLGTEMPLATE g2pvt_dialog_template (LPDLGITEMTEMPLATE *item, UINT size,
                                                int x, int y, int cx, int cy,
                                                DWORD style, DWORD exstyle,
                                                LPCWSTR menu, LPCWSTR className,
                                                LPCWSTR caption, LPCWSTR font,
                                                int height);
extern "C" HFONT GetDefaultGuiFont(LPWSTR*,int*);

extern BOOL g2pvt_add_control_hwnd (CONTROLHWND *pcontrolhwnd, HWND hwnd);
extern BOOL g2pvt_init_control (HWND hwndCtrl, HWND hwndDlg, CONTROLITEM *pcontrol);
extern BOOL g2pvt_get_name_of_control_type (int type, TCHAR *szClassName);
extern void g2pvt_ddlg_respond (HWND hwndDlg, int controlId, int respcode);
extern char *g2pvt_simple_unicode_to_multibyte (LPWSTR pText);
extern CONTROLHWND *g2pvt_get_control_hwnd_by_controlId (DIALOGINFO *pdlgInfo, long controlId);
extern CGensymGridCtrl *g2pvt_create_rich_edit_grid (CONTROLITEM *pcontrol,
                                                     CWnd *pParent, RECT *pRect);
extern LRESULT CALLBACK DynamicDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern long g2pvt_modify_gensym_edit (HWND hwndDlg, CONTROLITEM *pControl, wchar_t *value, HWND hWnd, int updateType);
extern long g2pvt_modify_tab_frame_control (CWnd *pObj, int updateType, HWND hwndDlg,
                                            CONTROLITEM *pcontrol, wchar_t *value);
extern UINT wm_get_tool_tip; 
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

/*****************************************************************************
* RECT *mfc_control_rectangle (HWND hDlg, CONTROLITEM *pcontrol,
*                             TABITEM *ptabitem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     Generally, we will take whatever coordinates (x, y, width, height) the
*     user supplied, call MapDialogRect on it, and go ahead and create the
*     control with those coordinates, without doing any sort of sanity checking.
*     But there is one case where we don't want the height to indicate dialog
*     units to begin with, and if we do let it do so, it does weird things.
*
*     The problem the color picker, which is a kind of dropdown combo box.  Like
*     any other window, combo boxes take a "height" specification when they are
*     created.  However, this specification never seems to have anything to do
*     with the size of the edit control which is created to show the current
*     selection (i.e., what you see even when the dropdown box is not in use).
*
*     The supplied height seems to control the size of the dropdown box.  And if
*     we supply a value which is too small, then no dropdown box at all is
*     created.  A combo box in such a state acts quite strangely.  It responds
*     to keyboard input (up- and down-arrow keys), but does not properly
*     "select" what is supposed to be the "selection", which prevents the
*     correct messages from being sent, and all sorts of things to appear messed
*     up.
*
*     So, the solution is, make sure we always create the combo box with the
*     necessary height to create a dropdown box.  Due to the little squares of
*     color, the "height" of each entry in the color picker 10 units, so every
*     ten units of "height" is one extra row.  Except, two rows seem to go into
*     the ether.  Why are these extra two rows necessary?  I really have no
*     idea.  But it works.
*
*     We're already going ahead, performing a calculation on the user-supplied
*     number.  Given that, we may as well do a sanity check, as well.  If the
*     user supplied a value less then 1, we will use 1, instead.  -jv, 3/05/05
*
*     -----
*   Modifications:
*****************************************************************************/
RECT *mfc_control_rectangle (HWND hDlg, CONTROLITEM *pcontrol,
                             TABITEM *ptabitem)
{
  RECT *rectAdj;
  RECT rectControl;
  int dialog_unit_height;

  dialog_unit_height = pcontrol->_height;
  if (pcontrol->_type == ctColor) {
    if (dialog_unit_height < 1) {
      // constant value, 30, but show how we obtain it
      dialog_unit_height = ADDITIONAL_HEIGHT_FOR_TWNG_COLOR_PK +
        (DIALOG_UNITS_PER_COLOR_ROW * 1);
    } else {
      dialog_unit_height = ADDITIONAL_HEIGHT_FOR_TWNG_COLOR_PK +
        (DIALOG_UNITS_PER_COLOR_ROW * pcontrol->_height);
    }
  }

  rectAdj = (RECT *)malloc(sizeof(RECT));
  SetRectEmpty(rectAdj);

  // holds the control coordinates
  SetRectEmpty(&rectControl);
  rectControl.left = pcontrol->_x;
  rectControl.top = pcontrol->_y;
  rectControl.right = rectControl.left + pcontrol->_width;
  rectControl.bottom = rectControl.top + dialog_unit_height;

  // is control the child of a tab?
  if (ptabitem != NULL)
  {
    RECT rectTab;

    // we need all coordinates to be in the same space
    MapDialogRect(hDlg, &rectControl);

    SetRectEmpty(&rectTab);
    CopyRect(&rectTab, &(ptabitem->displayRect));
    MapDialogRect(hDlg, &rectTab);

    rectAdj->left = rectControl.left - ptabitem->displayRect.left;
    rectAdj->top = rectControl.top - ptabitem->displayRect.top;
    rectAdj->right = rectAdj->left + rectControl.right - rectControl.left;
    rectAdj->bottom = rectAdj->top + rectControl.bottom - rectControl.top;
  }
  else
  {
    CopyRect(rectAdj, &rectControl);
    MapDialogRect(hDlg, rectAdj);
  }

  return rectAdj;
}
/*****************************************************************************
* long modify_twng_color_picker (HWND hwndCtrl, CONTROLITEM *pcontrol,
*                                wchar_t *new_value, int updateType)
*
*   Description: support dynamic add and replace of color picker items
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2pvt_modify_twng_color_picker (HWND hwndCtrl, CONTROLITEM *pcontrol,
                               wchar_t *new_value, int updateType)
{
  CColorCombo *pPicker;
  TCHAR *szTemp;
  TCHAR *token = NULL;
  TCHAR seps[] = _T("\001");
  int i, color_in_list, selected = -1;
  char *token_as_mb;
  COLORREF rgbcolor;
  int token_idx[TOTAL_NUMBER_OF_COLORS];

  pPicker = (CColorCombo *)CWnd::FromHandle(hwndCtrl);
  if (!pPicker)
      return DYNAMIC_DIALOG_UPDATE_FAILED;

  memset(token_idx, 0, sizeof(token_idx));

  // copy off the text so we can mangle it
  szTemp = new TCHAR[_tcslen(pcontrol->_mText)+1];
  if (szTemp == NULL) {
    return FALSE;                                // out of memory!
  }
  ZeroMemory((LPVOID)szTemp, sizeof(TCHAR) * (_tcslen(pcontrol->_mText) + 1));
  _tcscpy(szTemp, pcontrol->_mText);

  token = _tcstok(szTemp, seps);
  color_in_list = 1;
  while (token != NULL)
  {
    rgbcolor = 0;
    token_as_mb = g2pvt_simple_unicode_to_multibyte(token);
    for (i=0; i<TOTAL_NUMBER_OF_COLORS; i++) {
      if (strcmp(token_as_mb, XMetaColorArray[i].szColor) == 0)
      {
        if (1 == token_idx[i]) {
          selected = color_in_list - 2;  // See Note B, above
        }
        rgbcolor = XMetaColorArray[i].rgbColor;
        token_idx[i] = color_in_list;
        break;
      }
    }
    free(token_as_mb);
    token = _tcstok(NULL, seps);
    color_in_list++;
  }

  delete [] szTemp;
  szTemp = NULL;


  pPicker->InitializeDefaultColors(token_idx);
  pPicker->SetCurSel(selected);

  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}




/*****************************************************************************
* CColorCombo *create_color_combo_box (CONTROLITEM *pcontrol, CWnd *pParent,
*                                      RECT *pRect)
*
*   Description: builds up a special combo box, based on the CColorCombo class
*     defined in widgets/colorpicker/ColorCombo.cpp, and returns a pointer to
*     the caller.
*   Input Arguments:
*     pcontrol: a pointer to the Gensym CONTROLITEM structure
*     pParent:  the MFC instance of the parent window
*     pRect:    the rectangle into which the combo box should be drawn
*   Returns: pointer to the caller
*   Notes:
*     We get the RGB values associated with each color, take these values,
*     and turn them into a little square of color.  For the array, zero
*     indicates that the color should not be present in the combo box; any
*     other value indicates the order in which the color name should appear
*     in the combo box.
*
*     Note B: the color which is supposed to be selected initially is sent
*     as the first color in the string; if the selected color is not supposed
*     to be at the top, then it will appear twice in the list: once at the
*     beginning of the list, and again in its requested spot in the list.
*     After all the items have been added to the combo box, we will set the
*     current selection.  The one we want to set it to is the last entry of
*     the color which appeared first in the list.
*        So, we need to know the index of the color which also appeared first.
*     We'll detect that by seeing, the second time the color comes around, that
*     its spot in the array is already set to 1.
*        Then we need to find out the index of the other row.  At the time we
*     find the duplicate, we know that we want "this" row to be selected.  So,
*     it may seem that we should set "selected = color_in_list".  But (a) our
*     token_idx array is 1-based, whereas the real combo box is zero-based,
*     because we use zero as a sentinel to indicate that the color should not
*     be included in the list at all; and (b) once we've found a duplicate,
*     we overwrite the "1" value, so everything moves up one slot.  Therefore,
*     the color with its token_idx entry == 2 will be the first color in the
*     list, index zero... and so on.  So, we have to take "this" index, and
*     subtract 2 from it to get the corresponding index in the actual combo
*     box.  -jv, 2/07/05
*
*     -----
*   Modifications:
*****************************************************************************/
CColorCombo *create_color_combo_box (CONTROLITEM *pcontrol, CWnd *pParent,
                                     RECT *pRect)
{
  CColorCombo *pPicker;
 
  long ret_code;

  pPicker = new CColorCombo;
  if (!pPicker)
    return NULL;
  
  if (!(pPicker->Create(CBS_HASSTRINGS | CBS_OWNERDRAWFIXED | WS_VISIBLE | WS_TABSTOP
    | WS_VSCROLL | CBS_DROPDOWNLIST,   *pRect, pParent, pcontrol->_controlId)))
  {
    delete pPicker;
    return NULL;
  }
  ret_code = g2pvt_modify_twng_color_picker (pPicker->m_hWnd, pcontrol, pcontrol->_mText, REPLACE);

  if (DYNAMIC_DIALOG_UPDATE_SUCCEEDED != ret_code) 
  {
    delete pPicker;
    return NULL;
  } 
  return pPicker;

}

/*****************************************************************************
* CGensymEditBox *create_masked_edit (CONTROLITEM *pcontrol, CWnd *pParent,
*                                     RECT *pRect)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CGensymEditBox *create_masked_edit (CONTROLITEM *pcontrol, CWnd *pParent,
                                    RECT *pRect)
{
  CGensymEditBox *p_MaskEdit;
    
  p_MaskEdit = new CGensymEditBox(pcontrol);
  p_MaskEdit->Create(pcontrol->_styles, pRect, pParent, pcontrol->_controlId);
  
  p_MaskEdit->SetControlId(pcontrol->_controlId);
  p_MaskEdit->Initialize(pParent);

  g2pvt_modify_gensym_edit (pParent->m_hWnd, pcontrol, pcontrol->_mText, p_MaskEdit->m_hWnd, REPLACE);

  return p_MaskEdit;
}
void add_strings_to_tree_view_combo_box (TCHAR *pText, CTVData *pCTVData)
{
  HTREEITEM hNode = NULL;
  TCHAR seps[] = _T("|");
  TCHAR szComboTreeEntry[MAX_PATH];
  TCHAR *token, *pTemp, *pWorkingString, *pSelected = NULL;
  int len;

// make temp copy of incoming string to mangle with _tcstok
  len = _tcslen(pText) + 1;
  pTemp = new TCHAR[len];
  ZeroMemory((PVOID)pTemp, len * sizeof(TCHAR));
  _tcsncpy(pTemp, pText, len);

  // A pointer, where we may modify what it is that it points to, initially points to
  // our temp copy.  We need to save the original pointer to make sure to delete the
  // temp copy when we are done.
  pWorkingString = pTemp;

  while (TRUE)
  {
    ZeroMemory((PVOID) szComboTreeEntry, MAX_PATH * sizeof(TCHAR));
    token = _tcstok(pWorkingString, seps);
    if (token == NULL)
      break;
    _tcsncpy(szComboTreeEntry, token, MAX_PATH);

    if (pWorkingString != NULL) {
      // The first node is the initially selected node, save it for later.
      len = _tcslen(szComboTreeEntry) + 1;
      if (len > 1) {
        pSelected = new TCHAR[len];
        _tcsncpy(pSelected, szComboTreeEntry, len);
      }
    } else
      hNode = pCTVData->p_ComboTree->AddString(szComboTreeEntry);

    pWorkingString = NULL;
  }
  if (pSelected) {
    // Select the initially selected node after all the nodes have been
    // added.  If SelectOnlyLeaves is set and this node is not a leaf,
    // this will select its first leaf, which is why we had to add them
    // first.
    pCTVData->p_ComboTree->SelectString(pSelected);
    delete[] pSelected;
  }

  delete[] pTemp;
 
}
/*****************************************************************************
* CTVData *create_tree_view_combo_box (CONTROLITEM *pcontrol, CWnd *pParent,
*                                      RECT *pRect)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CTVData *create_tree_view_combo_box (CONTROLITEM *pcontrol, CWnd *pParent, RECT *pRect)
{
  CTVData *pCTVData;

/* This control needs to be redesigned to not need subclassing.  Because of the     */
/* way it is now, there is a memory leak of the objects in pCTVData.                */
/* At the moment there is no easy way to delete them without causing an             */
/* address exception. hjg 01/12/2005                                                */

  pCTVData = new CTVData;

  pCTVData->p_ComboToSubclass = new CComboBox();
  pCTVData->p_ComboToSubclass->Create(pcontrol->_styles, *pRect,
    pParent, pcontrol->_controlId);
  pCTVData->p_ComboTree = new ComboTree;
  pCTVData->p_ComboTree->SetHasCheckboxes(FALSE); //Must set before tree is created
  pCTVData->p_ComboTree->SubclassDlgItem(pcontrol->_controlId,  pParent);
  if (pcontrol->_g2styles & G2_CTV_SEL_ONLY_LEAVES)
    pCTVData->p_ComboTree->SelectOnlyLeaves(TRUE);
  else
    pCTVData->p_ComboTree->SelectOnlyLeaves(FALSE);

  EXTRA_COMBO_TREE_VIEW_DATA *p_extra_ctv_data;


  // see if the extra data was allocated
  p_extra_ctv_data = (EXTRA_COMBO_TREE_VIEW_DATA *)pcontrol->_pExtraTypeData->_pData;

  if (p_extra_ctv_data)
  {
    if (p_extra_ctv_data->DroppedHeight != TREE_VIEW_COMBO_BOX_USE_DEF)
      pCTVData->p_ComboTree->SetDroppedHeight(p_extra_ctv_data->DroppedHeight);
    else // do the old behavior
      pCTVData->p_ComboTree->SetDroppedHeight((pRect->bottom - pRect->top)*4);

    if (p_extra_ctv_data->DroppedWidth != TREE_VIEW_COMBO_BOX_USE_DEF)
      pCTVData->p_ComboTree->SetDroppedWidth(p_extra_ctv_data->DroppedWidth);
  }
  else
    pCTVData->p_ComboTree->SetDroppedHeight((pRect->bottom - pRect->top)*4);

  add_strings_to_tree_view_combo_box (pcontrol->_mText, pCTVData);

  /* save our allocated memory on the window handle for cleanup later */
  SetWindowLong((pCTVData->p_ComboTree)->m_hWnd, GWL_USERDATA, (long)pCTVData);

  return pCTVData;
}


/*****************************************************************************
* CDateTimeCtrl *g2pvt_create_duration_control(CONTROLITEM *pcontrol, CWnd *pParent,
*                                              RECT *pRect)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: perhaps we should use DTS_APPCANPARSE style:
*      Allows the owner to parse user input and take necessary action. It
*      enables users to edit within the client area of the control when they
*      press the F2 key. The control sends DTN_USERSTRING notification messages
*      when users are finished.
*
*     -----
*   Modifications:
*****************************************************************************/
CNewDuration *g2pvt_create_duration_control(CONTROLITEM *pcontrol, CWnd *pParent,
                                            RECT *pRect)
{
  CNewDuration *pDuration;

  pDuration = new CNewDuration();
  pDuration->Create(pcontrol->_styles, *pRect, pParent,  pcontrol->_controlId);

  return pDuration;
}


/*****************************************************************************
*  CG2ImageWidget *g2pvt_create_image_widget_icon (CONTROLITEM *pctrl,
*                                                  CWnd *pParent, RECT *lpRect)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CG2ImageWidget *g2pvt_create_image_widget_icon (CONTROLITEM *pctrl, CWnd *pParent, RECT *lpRect)
{
  CG2ImageWidget *pImage;
  HICON hIcon;
  int index;

  pImage = new CG2ImageWidget();
  if(!pImage)
    return NULL;

  //// HQ-5156881 "problems with creating new dialog controls invisible"
  if(!pImage->Create(_T("Static"), WS_CHILD | SS_ICON | pctrl->_styles,
		     *lpRect, pParent, pctrl->_controlId)) {
    delete pImage;
    return NULL;
  }

  index = _ttoi(pctrl->_mText);
  hIcon = g2pvt_get_native_icon(index);
  pImage->SetIcon(hIcon);
  return pImage;
}

/*****************************************************************************
* void g2pvt_clear_image_widget_icon (CONTROLITEM *pcontrol)
*
*   Description: clears icon used by image widget
*   Input Arguments:
*   Returns:
*   Notes:
*   Modifications:
*****************************************************************************/

static void g2pvt_clear_image_widget_icon(CONTROLITEM *pctrl)
{
  int index = _ttoi(pctrl->_mText);
  HICON hIcon = g2pvt_get_native_icon(index);

  if (hIcon != NULL)
  {
    DestroyIcon(hIcon);
  }
}

/*****************************************************************************
* HWND create_default_mfc_control (CONTROLITEM *pcontrol, CWnd *pParent,
*                                  RECT *pRect)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: can't we just call create_win32_control in w32_dyndlg.cpp instead?
*
*     -----
*   Modifications:
*****************************************************************************/
static HWND create_default_mfc_control (CONTROLITEM *pcontrol, HWND hwndParent,
					RECT *pRect)
{
  HWND hwnd;
  TCHAR szClassName[MAX_CLASSNAME_LEN] = {0};

  g2pvt_get_name_of_control_type(pcontrol->_type, szClassName);

  // relative to the main dialog window
  //MapDialogRect(hwndParent, &rect);
  hwnd = CreateWindowEx(0, // extendedStyle
    szClassName,
    pcontrol->_mText,
    pcontrol->_styles,
    pRect->left,
    pRect->top,
    pRect->right - pRect->left,
    pRect->bottom - pRect->top,
    hwndParent,
    (HMENU)pcontrol->_controlId,
    (HINSTANCE) GetWindowLong(hwndParent, GWL_HINSTANCE),
    0);
  return hwnd;
}

// Reparent and reposition an existing native view into given control in a
// dialog window.
static CWnd *put_view_into_dialog(CWnd *pDlg, CONTROLITEM *pControl, RECT *pRect)
{
  CWnd *pWnd = FIND_WND(pControl->view_handle, CWnd);
  if(!pWnd)
    return NULL;
  pWnd->ShowWindow(SW_HIDE);
  pWnd->SetParent(pDlg);
  pWnd->SetDlgCtrlID(pControl->_controlId);
  pWnd->MoveWindow(pRect);
  pWnd->ModifyStyle(0, pControl->_styles, SWP_FRAMECHANGED);
  pWnd->SendMessage(WM_PARENT_CHANGED, (WPARAM)TRUE, (LPARAM)pDlg->GetSafeHwnd());
  return pWnd;
}

/*****************************************************************************
* BOOL g2pvt_create_mfc_control (HWND, CONTROLITEM *, TABITEM *)
*
*   Description:
*   Input Arguments: hwndParent = the top-level dialog HWND
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL g2pvt_create_mfc_control (HWND hwndParent, CONTROLITEM *pcontrol,
                               TABITEM *ptabitem)
{
  CWnd *pParent;
  CWnd *pWnd = NULL;
  RECT *rectAdj;

  pParent = CWnd::FromHandle(hwndParent);
  rectAdj = mfc_control_rectangle(hwndParent, pcontrol, ptabitem);
  switch(pcontrol->_type)
  {

  case ctTabs://TWNG tabs
    {
      CG2TabWidget *pTab;
 
      pTab =new CG2TabWidget;
      pTab->CreateTabs(pParent, pcontrol, rectAdj);
      pWnd =  pTab;
    }
  break;
  case ctComboTreeView:
    {
      CTVData *pCVTData;

      pCVTData = create_tree_view_combo_box(pcontrol, pParent, rectAdj);
      pWnd = pCVTData->p_ComboTree;
    }
    break;

  case ctIcon:
    {
      CG2ImageWidget *pImage;
      pImage = g2pvt_create_image_widget_icon(pcontrol, pParent, rectAdj);
      pWnd = pImage;
    }
    break;

  case ctCheckListBox:
    {
      CG2CheckListBox *pListBox;
      pListBox = new CG2CheckListBox;
      pListBox->Create(LBS_OWNERDRAWFIXED|LBS_HASSTRINGS|pcontrol->_styles|WS_VISIBLE|WS_CHILD,
        *rectAdj, pParent, pcontrol->_controlId);
      pListBox->set_up_check_listbox(pListBox, pcontrol, COMBO_BOX_SET_SELECTION);
      pWnd = pListBox;
    }
    break;

  case ctColor:
    {
      CColorCombo *pPicker;

      pPicker = create_color_combo_box(pcontrol, pParent, rectAdj);
      pWnd = pPicker;
    }
    break;

  case ctAdvancedColor:
    {
      CAdvancedColorPicker *pCP;
      pCP = new CAdvancedColorPicker;
      //// HQ-5156881 "problems with creating new dialog controls invisible"
      pCP->Create(pcontrol->_mText, WS_CHILD, rectAdj, pParent, pcontrol->_controlId);
      pWnd = pCP;
    }
    break;

  case ctMaskEdit:
    {
      CGensymEditBox *p_MaskEdit;

      p_MaskEdit = create_masked_edit(pcontrol, pParent, rectAdj);
      pWnd = p_MaskEdit;
    }
    break;

   case ctSpin:
    {
      CSpinnerTwng *pSpin;
      pSpin = new CSpinnerTwng();
      pSpin->Create(pcontrol->_styles, *rectAdj, pParent, pcontrol->_controlId);
      pWnd = pSpin;
    }
    break;

  case ctDuration:
    {
      CNewDuration *pDuration;

      pDuration = g2pvt_create_duration_control(pcontrol, pParent, rectAdj);
      pWnd = pDuration;
    }
    break;

  case ctGridView:
    {
      CGensymGridCtrl *pCGridCtrl;

      pCGridCtrl = g2pvt_create_rich_edit_grid(pcontrol, pParent, rectAdj);
      pWnd = pCGridCtrl;
    }
    break;

   case ctTabularView:
     pWnd = put_view_into_dialog(pParent, pcontrol, rectAdj);
     break;

  default:
    {
      HWND hwndControl;

      hwndControl = create_default_mfc_control(pcontrol, hwndParent, rectAdj);
      pWnd = CWnd::FromHandle(hwndControl);
    }
    break;
  }
  free(rectAdj);

  if (pWnd->GetSafeHwnd()) {
    CONTROLHWND *pcontrolhwnd;

    pWnd->SetFont(pParent->GetFont());

    // add to list of created control id's
    pcontrolhwnd = new CONTROLHWND;
    pcontrolhwnd->controlId = pcontrol->_controlId;
    pcontrolhwnd->hwndControl = pWnd->m_hWnd;
    pcontrolhwnd->pObj = pWnd;
    pcontrolhwnd->next = NULL;

    g2pvt_add_control_hwnd(pcontrolhwnd, hwndParent);

    // further control-specific processing
    g2pvt_init_control(pWnd->m_hWnd, hwndParent, pcontrol);

    // should we be visible?
    if (pcontrol->_styles & WS_VISIBLE)
      pWnd->ShowWindow(TRUE);
  }

  return TRUE;
}

/*****************************************************************************
* void g2pvt_clear_mfc_control_data(CONTROLITEM *pcontrol)
*   Description: Function clears allocated data of control
*   Input Arguments:
*   Returns:
*   Notes:
*   Modifications:
*****************************************************************************/

void g2pvt_clear_mfc_control_data (CONTROLITEM *pcontrol)
{
  switch(pcontrol->_type)
  {
  case ctIcon:
    {
      g2pvt_clear_image_widget_icon(pcontrol);
    }
    break;
  }
}

/*****************************************************************************
* CWnd g2pvt_get_control_cwnd (long controlId, HWND hwnd)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*     jv, 2/02/05: this functions seems weird, perhaps misguided, to me.
*     Maybe it should use g2pvt_lookup_control_by_hwnd to get the control,
*     and then get the HWND from there.
*
*     dbk, 3/15/05:  See my comments by g2pvt_get_control_hwnd.
*
*     -----
*   Modifications:
*****************************************************************************/
CWnd *g2pvt_get_control_cwnd (long controlId, HWND hwndDlg)
{
  DIALOGINFO *pDialogInfo;
  CONTROLHWND *pControlHwnd;

  pDialogInfo = (DIALOGINFO *)GetWindowLong(hwndDlg, GWL_USERDATA);

  if (pDialogInfo == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "g2pvt_get_control_cwnd: dialogInfo is NULL\n");
    return NULL;
  }

  pControlHwnd = g2pvt_get_control_hwnd_by_controlId(pDialogInfo, controlId);

  return (pControlHwnd ? (CWnd *) pControlHwnd->pObj : NULL);
}


/*****************************************************************************
* long modify_tree_view_combo_box (CONTROLITEM *pControl, HWND hwndCtrl,
*                                  wchar_t *update_text, int updateType)
*
*   Description: sets the "DroppedWidth" or "DroppedHeight" of a tree-view
*     combo-box
*   Input Arguments:
*   Returns: DYNAMIC_DIALOG_UPDATE_SUCCEEDED on success,
*            DYNAMIC_DIALOG_UPDATE_FAILED otherwise
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long modify_tree_view_combo_box (CONTROLITEM *pControl, HWND hwndCtrl,
                                 wchar_t *update_text, int updateType)
{
  CTVData *pCTVData = NULL;
  ComboTree *pCT;
  long new_size;

  if ((updateType != DROPDOWN_WIDTH)  &&
      (updateType != DROPDOWN_HEIGHT) &&
      (updateType != REPLACE)
      )
  {
    g2pvt_gprintf(G2PVT_ERROR, "tree-view-combo-box %s type %d\n",
                  "does not support modification", updateType);
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  if (hwndCtrl != NULL)
  {
    pCTVData = (CTVData *)GetWindowLong(hwndCtrl, GWL_USERDATA);
  }

  if (pCTVData == NULL)
  {
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }
  if (updateType == REPLACE)
  {
    
    pCT =  pCTVData->p_ComboTree;
    ComboTreeDropList& Tree = pCT->GetTree();

    if (Tree.DeleteAllItems())
    {
       add_strings_to_tree_view_combo_box (update_text, pCTVData);
       return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
    }
  }
  new_size = wcstol(update_text, NULL, 10);

  if (updateType == DROPDOWN_WIDTH)
  {
    if (new_size < pControl->_width)
    {
      return DYNAMIC_DIALOG_UPDATE_FAILED;
    }
    if (CB_ERR != pCTVData->p_ComboTree->SetDroppedWidth(new_size))
    {
      return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
    }
  }

  if (updateType == DROPDOWN_HEIGHT)
  {
    if (new_size < pControl->_height)
    {
      return DYNAMIC_DIALOG_UPDATE_FAILED;
    }
    if (CB_ERR != pCTVData->p_ComboTree->SetDroppedHeight(new_size))
    {
      return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
    }
  }

  return DYNAMIC_DIALOG_UPDATE_FAILED;
}


/*****************************************************************************
* long modify_image_widget_icon (CWnd *pObj, wchar_t *new_value)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long modify_image_widget_icon (CWnd *pObj, wchar_t *new_value)
{
  CG2ImageWidget *pImage = NULL;
  HICON hIcon, hOldIcon;
  int index = -1;

  index = _ttoi(new_value);

  pImage = (CG2ImageWidget *) pObj;
  
  hIcon = g2pvt_get_native_icon(index);
  hOldIcon = pImage->SetIcon(hIcon);
  if(hOldIcon)
    DestroyIcon(hOldIcon);

  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* long modify_check_list_box (HWND hwndCtrl, CONTROLITEM *pcontrol, int updateType)
*
*   Description: support dynamic add and replace of check box list items
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long modify_check_list_box (HWND hwndCtrl, CONTROLITEM *pcontrol, int updateType)
{
  switch (updateType)
  {
  case REPLACE:
    // clear out current entries
    SendMessage(hwndCtrl, LB_RESETCONTENT, 0, 0);

    // fall through
  case ADD:
    CG2CheckListBox *pCLB;
    pCLB = (CG2CheckListBox *)CWnd::FromHandle(hwndCtrl);

    if (pCLB)
      pCLB->set_up_check_listbox(pCLB, pcontrol, updateType);
    break;
  }

  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* void g2pvt_process_advanced_color (WPARAM wParam, HWND hWndDlg, CONTROLITEM *pControl)
*
*   Description: Process Messages from the Advanced Color Picker
*   Input Arguments: WPARAM wParam - from WM_COMMAND message
*                    HWND hWndDlg - the window handle to the dialog
*                     CONTROLITEM *pControl - pointer to the control item
*   Returns: nothing
*   Notes:
*   This routine processes messages sent to the parent dialog, from the
*   ctAdvancedColor control.  At the moment, we care only about CPN_XT_SELENDOK
*   which indicates a color has been chosen. We then respond with the info
*   back to G2 via g2_pvt_ddlg_respond.  This routine is in DynamicDlg.cpp
*   because it is a TWNG control and it must be aware of CODEJOCK defines.
*
*
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_process_advanced_color (WPARAM wParam, HWND hWndDlg, CONTROLITEM *pControl)
{
  // we're resonding to the message indicating a color has been selected
  if (CPN_XT_SELENDOK == HIWORD(wParam))
  {
    g2pvt_ddlg_respond(hWndDlg, pControl->_controlId, pControl->_respcode);
  }
}


/*****************************************************************************
* long modify_advanced_color (HWND hwndDlg, CONTROLITEM *pcontrol,
*                                wchar_t *value)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long modify_advanced_color (HWND hwndDlg, CONTROLITEM *pcontrol, wchar_t *value)
{
  g2pvt_gprintf(0, "modify_advanced_color: value = \"%S\" (\"%S\")",
                value, pcontrol->_mText);
  g2pvt_gprintf(0, "\n");

  return DYNAMIC_DIALOG_UPDATE_FAILED;
}


/*****************************************************************************
* long modify_twng_spinner (CONTROLITEM *pctrl, HWND hwndDlg,  wchar_t *value)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static long modify_twng_spinner (CONTROLITEM *pctrl, HWND hwndDlg, wchar_t *value)
{
  CWnd *pWnd;
  CSpinnerTwng *pSpin;

  pWnd = g2pvt_get_control_cwnd(pctrl->_controlId, hwndDlg);
  ASSERT(pWnd);
  pSpin = (CSpinnerTwng *)pWnd;
  if (pSpin != NULL)
  {
     pSpin->m_pSpinButtonCtrl->set_spin(value, pctrl->_g2styles, NULL);
  }
  else
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* void g2pvt_set_duration_value (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_set_duration_value (CONTROLITEM *pctrl, HWND hwndCtrl, HWND hwndDlg)
{
  CWnd *pObj;
  CNewDuration *pDuration;

  pObj = g2pvt_get_control_cwnd(pctrl->_controlId, hwndDlg);
  ASSERT(pObj);
  pDuration = (CNewDuration *)pObj;
  if (pDuration != NULL)
  {
    pDuration->SetCurrentDurationValue(pctrl->_mText);
  }
}


/*****************************************************************************
* long modify_duration (CONTROLITEM *pcontrol, HWND hwndDlg, wchar_t *value)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long modify_duration (CONTROLITEM *pcontrol, HWND hwndDlg, wchar_t *value)
{

  CWnd *pObj;
  CNewDuration *pDuration;

  pObj = g2pvt_get_control_cwnd(pcontrol->_controlId, hwndDlg);
  ASSERT(pObj);
  pDuration = (CNewDuration *)pObj;
  if (pDuration != NULL)
  {
    pDuration->SetCurrentDurationValue(value);
  }
 
  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}


/*****************************************************************************
* long g2pvt_modify_mfc_control (CONTROLITEM *pcontrol, HWND hwndCtrl,
*                                HWND hwndDlg, wchar_t *value, int updateType)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2pvt_modify_mfc_control (CONTROLITEM *pcontrol, HWND hwndCtrl,
                               HWND hwndDlg, wchar_t *value, int updateType)
{
  CWnd *pObj = NULL;

  if (hwndDlg == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "g2pvt_modify_mfc_control: hwndDlg is NULL\n");
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  pObj = g2pvt_get_control_cwnd(pcontrol->_controlId, hwndDlg);
  if (pObj == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "g2pvt_modify_mfc_control: pObj is NULL\n");
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  switch (pcontrol->_type) {

  case ctTabs:
    return g2pvt_modify_tab_frame_control(pObj, updateType, hwndDlg, pcontrol, value);
    break;

  case ctComboTreeView:
    return modify_tree_view_combo_box(pcontrol, hwndCtrl, value, updateType);
    break;

  case ctIcon:
    return modify_image_widget_icon(pObj, value);
    break;

  case ctCheckListBox:
    return modify_check_list_box(hwndCtrl, pcontrol, updateType);
    break;

  case ctColor:
    return g2pvt_modify_twng_color_picker(hwndCtrl, pcontrol, value, updateType);
    break;

  case ctAdvancedColor:
    return modify_advanced_color(hwndDlg, pcontrol, value);
    break;

  case ctMaskEdit:
    return g2pvt_modify_gensym_edit(hwndDlg, pcontrol, value, hwndCtrl, updateType);
    break;

  case ctSpin:
    return modify_twng_spinner(pcontrol, hwndDlg, value);
    break;

  case ctDuration:
    return modify_duration(pcontrol, hwndDlg, value);
    break;

  case ctGridView:
    g2pvt_gprintf(G2PVT_ERROR, "control value cannot be modified on type %d\n",
                  pcontrol->_type);
    return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
    break;
  }

  return DYNAMIC_DIALOG_UPDATE_FAILED;
}


/*****************************************************************************
* HWND g2pvt_create_dialogMFC (DIALOGINFO *dlgInfo, int handle)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*    -- Added "handle" argument, the G2-assigned dialog handle.
*****************************************************************************/
extern "C" 
HWND g2pvt_create_dialogMFC (DIALOGINFO *dlgInfo, int handle)
{
  LPDLGTEMPLATE pDlgTemplate;
  DWORD style = (dlgInfo->resizable ? WS_THICKFRAME : 0) | DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU;
  LPWSTR faceName;
  int pointSize;

  GetDefaultGuiFont(&faceName, &pointSize);

  pDlgTemplate =
    g2pvt_dialog_template(NULL, 0 /*size*/, 0, 0, 304, 347,
			  style,
			  NULL, NULL, NULL, _T("Dialog"),
			  faceName, pointSize);

  if (pDlgTemplate == NULL) {
    return NULL;
  }

  /* assume modeless - call the other Init... function if it's modal */
  CDynamicDlg *pDialog = new CDynamicDlg(handle);

  pDialog->CreateIndirect(pDlgTemplate, AfxGetMainWnd(), (void *)dlgInfo);
  free(pDlgTemplate);
  return pDialog->m_hWnd;
}


/////////////////////////////////////////////////////////////////////////////
// CDynamicDlg dialog

BEGIN_MESSAGE_MAP(CDynamicDlg, CDynamicBaseDlg)
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CDynamicDlg, CDynamicBaseDlg)

BOOL g2pvt_is_dynamic_dialog(CWnd *pWnd)
{
  return pWnd->IsKindOf(RUNTIME_CLASS(CDynamicDlg));
}

CDynamicDlg::CDynamicDlg(int handle)
{
  m_handle = handle;
  SAVE_WND();
  VTRACE("Construct [%d] ", m_handle); POB(this);
}

CDynamicDlg::~CDynamicDlg()
{
  VTRACE("Destruct  [%d] ", m_handle); POB(this);
  FORGET_WND();
  m_handle = 0;

}

// Derived from CFormView::PreTranslateMessage, in order to pick up the handling
// of frame window accelerators. We would simply use CFormView, except that we
// aren't using CView's or CDocument's.
BOOL CDynamicDlg::PreTranslateMessage (MSG *pMsg)
{
  // allow tooltip messages to be filtered
  if (CDynamicBaseDlg::PreTranslateMessage(pMsg))
    return TRUE;

  // Only if not in Shift+F1 help mode
  if ((GetTopLevelFrame() == NULL) || (!GetTopLevelFrame()->m_bHelpMode)) {
    // since 'IsDialogMessage' will eat frame window accelerators,
    //   we call all frame windows' PreTranslateMessage first
    CFrameWnd *pFrameWnd = GetParentFrame();   // start with first parent frame
    while (pFrameWnd != NULL) {
      // allow owner & frames to translate before IsDialogMessage does
      if (pFrameWnd->PreTranslateMessage(pMsg))
        return TRUE;

      // try parent frames until there are no parent frames
      pFrameWnd = pFrameWnd->GetParentFrame();
    }
  }
  return CDynamicBaseDlg::PreTranslateMessage(pMsg);
}

LRESULT CDynamicDlg::WindowProc (UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT NonMFCResult;

  if (message == WM_DESTROY)
    g2pvt_destroy_containing_pane_if_any(m_hWnd, m_handle);

  if (WM_INITDIALOG == message)
  {   
      m_ToolTipControl.Create(this);
      NonMFCResult = DynamicDlgProc(this->m_hWnd, message, wParam, (long) m_lpDialogInit);
  }
  else 
  if (wm_get_tool_tip == message)
  {
     return OnDurationHelp(0,0);
  }
  else
    NonMFCResult = DynamicDlgProc(this->m_hWnd, message, wParam, lParam);
  if (0==NonMFCResult)
    return CDynamicBaseDlg::WindowProc(message, wParam, lParam);
  else
    return WM_SYSCOMMAND == message ? 0 : NonMFCResult;
}

/*
 * Replaces control ctrlID in dialog with pWnd, and destroys the
 * original control. Complicated by the existance of cached structures
 * pointing to the old HWND (eg, CONTROLHWND objects).
 */
BOOL g2pvt_replace_control_in_dialog (int dlgID, int ctrlID, CWnd *pWnd)
{
  HWND hwndDlg = g2pvt_find_dialog_hwnd_by_handle(dlgID);
  DIALOGINFO *pDialogInfo;
  CONTROLITEM *pControl;
  CONTROLHWND *pControlHwnd;

  if (hwndDlg == NULL)
    return FALSE;

  pDialogInfo = (DIALOGINFO *)::GetWindowLong(hwndDlg, GWL_USERDATA);
  if (pDialogInfo == NULL)
    return FALSE;

  pControl = g2pvt_lookup_control_by_id(ctrlID, pDialogInfo->_pdialog);
  if (pControl == NULL)
    return FALSE;

  pControlHwnd = g2pvt_get_control_hwnd_by_controlId(pDialogInfo, ctrlID);
  if (pControlHwnd == NULL) {
    // The control has not yet been created, so must defer reparenting until
    // g2pvt_mfc_control_created_hook is called.
    pControl->_pendingReplacementWnd = pWnd->GetSafeHwnd();
    return FALSE;
  }

  HWND hwndCtrl = g2pvt_get_dlg_item_hwnd(hwndDlg, ctrlID);
  if (hwndCtrl == NULL)
    return FALSE;

  CWnd *pCtrl = CWnd::FromHandle(hwndCtrl);
  if (pCtrl == NULL)                // Should never happen.
    return FALSE;

  // Hide them both
  BOOL wasVisible = (pCtrl->GetStyle() & WS_VISIBLE) != 0;
  pCtrl->ShowWindow(SW_HIDE);
  pWnd->ShowWindow(SW_HIDE);

  // Update the CONTROLHWND structure.
  pControlHwnd->hwndControl = pWnd->GetSafeHwnd();
  pControlHwnd->pObj = pWnd;

  // Reparent
  pWnd->SetParent(pCtrl->GetParent());

  // Copy DlgCtrlID
  pWnd->SetDlgCtrlID(pCtrl->GetDlgCtrlID());

  // Copy some style bits
  pWnd->ModifyStyle(0, WS_TABSTOP | (pCtrl->GetStyle() & (WS_BORDER|WS_DLGFRAME)));
  pWnd->ModifyStyleEx(0, pCtrl->GetExStyle() & (WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_STATICEDGE));

  // Copy size and position
  RECT r;
  pCtrl->GetWindowRect(&r);
  pWnd->GetParent()->ScreenToClient(&r);
  pWnd->MoveWindow(&r);

  // TODO: Copy layer position

  // Destroy the old window
  pCtrl->DestroyWindow();

  // Show the new window
  if (wasVisible)
    pWnd->ShowWindow(SW_SHOW);
  return TRUE;
}

/* Called after a control has been created for a custom dialog. For controls in
 * tabs, this can happen an arbitrarily long time after the dialog was
 * created. */
void g2pvt_mfc_control_created_hook (HWND hwndParent, CONTROLITEM *pControl, TABITEM *ptabitem)
{
  GENSYMDIALOG *pDialog = g2pvt_find_dialog_by_id(pControl->_dialogId);
  HWND hwnd = pControl->_pendingReplacementWnd;
  CWnd *pWnd = IsWindow(hwnd) ? CWnd::FromHandlePermanent(hwnd) : NULL;

  if (pDialog == NULL || pWnd == NULL)
    return;

  pControl->_pendingReplacementWnd = NULL;
  g2pvt_replace_control_in_dialog(pDialog->g2_id, pControl->_controlId, pWnd);
}
