/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      DynamicTabsDlg.cpp
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):
+   MS Windows portions:
+              2005 -      hgoddard, jv
+
+ Description:  Implementation of MFC-based tabbed dialogs
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
#include "DynamicTabsDlg.h"
#include "dyndlgs.h"
#include "cprim.h"
#include "msincls.h"

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

#define delim _T('\001')

extern "C"
{
HICON g2pvt_get_native_icon(int icon);
GENSYMDIALOG *g2pvt_find_dialog_by_id (long dlgId);
HWND g2pvt_get_dlg_item_hwnd (HWND hwndDlg, long controlId);
CONTROLITEM *g2pvt_lookup_control_by_hwnd (int id, HWND hwndDlg);
LPDLGTEMPLATE g2pvt_dialog_template (LPDLGITEMTEMPLATE *item, UINT size,
                                     int x, int y, int cx, int cy,
                                     DWORD style, DWORD exstyle,
                                     LPCWSTR menu, LPCWSTR className,
                                     LPCWSTR caption, LPCWSTR font,
                                     int height);
void g2pvt_init_resizable_child_dialog (DIALOGINFO *pDialogInfo,
                                        TABITEM *pTabItem, HWND hwndChildDlg);
HFONT GetDefaultGuiFont(LPWSTR*,int*);
}

extern wchar_t *g2pvt_windows_to_g2_text (wchar_t *pText);
extern void g2pvt_ddlg_respond (HWND hwndDlg, int controlId, int respcode);
extern CONTROLHWND *g2pvt_get_control_hwnd_by_controlId (DIALOGINFO *pdlgInfo,
                                                         long controlId);
extern BOOL g2pvt_create_child_control (HWND hwndParent, CONTROLITEM *pcontrol,
                                        TABITEM *ptabitem);
extern LRESULT CALLBACK DynamicDlgProc (HWND hwndDlg, UINT message,
                                        WPARAM wParam, LPARAM lParam);
extern LRESULT DynamicDlg_OnNotify (HWND hwndDlg, long control_id, NMHDR *pnmhdr);



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Tabbed Dialogs
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

/////////////////////////////////////////////////////////////////////////////
// CDynamicTabsDlg dialog


CDynamicTabsDlg::CDynamicTabsDlg(CWnd* pParent /*=NULL*/)
: CDynamicBaseDlg(pParent)
{
  //{{AFX_DATA_INIT(CDynamicTabsDlg)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}


/*****************************************************************************
* TABITEM *get_tab_dialog (HWND hwnd, UINT controlId, UINT nTabNum)
*
*   Description: Returns the TABITEM structure for the n-th tab of
*                the tab frame with given controlID, living in the given
*                dialog HWND. A better name for this function would be 
*                find_tab_by_index.
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/      
static TABITEM *get_tab_dialog (HWND hwnd, UINT controlId, UINT nTabNum)
{
  DIALOGINFO *pDialogInfo = (DIALOGINFO *)GetWindowLong(hwnd, GWL_USERDATA);
  TABITEM *next_tab;

  next_tab = pDialogInfo->_tabPages;
  while (next_tab != NULL)
  {
    if ((next_tab->tabControlId == controlId) && (next_tab->tabIndex == nTabNum))
    {
      return next_tab;
    }
    next_tab = next_tab->next;
  }

  return NULL;
}


/*****************************************************************************
* TABITEM *find_tab_by_name (HWND hwnd, UINT controlId, UINT nTabNum)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static TABITEM *find_tab_by_name (HWND hwndDlg, UINT controlId, wchar_t *tab_name)
{
  DIALOGINFO *pDialogInfo = (DIALOGINFO *)GetWindowLong(hwndDlg, GWL_USERDATA);
  TABITEM *next_tab;

  next_tab = pDialogInfo->_tabPages;
  while (next_tab != NULL)
  {
    if ((next_tab->tabControlId == controlId) &&
        (0 == wcscmp(tab_name, next_tab->szTabName)))
    {
      return next_tab;
    }
    next_tab = next_tab->next;
  }

  return NULL;
}


/*****************************************************************************
* void create_tab_child_controls (HWND hwndParent, DLGPARAMS *pdlgparams,
*                                 TABITEM *ptabitem)
*
*   Description: Called lazily from create_mfc_tab_dialog to create the
*                controls within a tab frame.
*   Input Arguments:
*     hwndParent  -- The HWND of the child dialog for the tab (redundant: also in ptabitem)
*     pdlgparams  -- Info about this (selected) tab: id, text.
*     ptabitem    -- Info about child dialog for the tab.
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void create_tab_child_controls (HWND hwndParent, DLGPARAMS *pdlgparams,
                                       TABITEM *ptabitem)
{
  int i = 0;
  CONTROLITEM *pitem;
  DIALOGINFO *pDialogInfo;

  pDialogInfo = (DIALOGINFO *)GetWindowLong(hwndParent, GWL_USERDATA);
  if (pDialogInfo == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "unable to locate dialog info in window 0x%x\n",
                  hwndParent);
    return;
  }

  // look for all child controls and create
  for (i=0; i < pDialogInfo->_pdialog->control_count; i++)
  {
    pitem = pDialogInfo->_pdialog->pcontrols[i];

    if ((wcscmp(pitem->_parentControlText, pdlgparams->_pszTabText) == 0) &&
        (pitem->_parentControlId == pdlgparams->_tabControlId))
    {
      g2pvt_create_child_control(hwndParent, pitem, ptabitem);
    }
  }
}


/*****************************************************************************
* BOOL create_mfc_tab_dialog (HWND hwndParent, TABITEM *ptabitem, int nTabCtrlId,
*                                   int nSelectedTab, wchar_t *pszTabText)
*
*   Description:      Creates the inner dialog window for the currently visible tab.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL create_mfc_tab_dialog (HWND hwndParent, TABITEM *ptabitem, int nTabCtrlId,
                                  int nSelectedTab, wchar_t *pszTabText)
{
  //GENSYMDIALOG *p_dialog;
  // p_dialog = dlgInfo->_pdialog;
  CWnd *pParent;
  HWND hwndChildDlg;
  pParent = CWnd::FromHandle ( hwndParent ) ;
  CDynamicTabsDlg *pDialog = new CDynamicTabsDlg();
  //  pDialog->pParent = pParent;


  DLGPARAMS dlgparams;
  TCHAR szBuf[MAX_TEXT] = {0};
  DIALOGINFO *pDialogInfo = (DIALOGINFO *)GetWindowLong(hwndParent, GWL_USERDATA);
  LPDLGTEMPLATE pDlgTemplate;
  HINSTANCE hInst;
  hInst = (HINSTANCE) GetWindowLong(hwndParent, GWL_HINSTANCE);

  // prepare our dialog parameters
  dlgparams._selectedTab = nSelectedTab;
  dlgparams._tabControlId = nTabCtrlId;
  dlgparams._pszTabText = new TCHAR[MAX_TEXT+1];
  ZeroMemory(dlgparams._pszTabText, sizeof(TCHAR) * (MAX_TEXT + 1));
  _tcscpy(dlgparams._pszTabText, pszTabText);

  LPWSTR faceName;
  int pointSize;
  GetDefaultGuiFont(&faceName, &pointSize);

  pDlgTemplate =
    g2pvt_dialog_template(NULL, 0 /*size*/, 0, 0, 252, 264,
			  DS_3DLOOK | DS_CONTROL | WS_CHILD | WS_VISIBLE |
			  WS_CLIPSIBLINGS | WS_BORDER, NULL, NULL, NULL,
			  _T(""), faceName, pointSize);

  if (pDlgTemplate == NULL) {
    return FALSE;
  }

  pDialog->CreateIndirect(pDlgTemplate, pParent, (void *)pDialogInfo);
  hwndChildDlg = pDialog->m_hWnd;

  if (hwndChildDlg == NULL)
  {
    return FALSE;
  }
  free(pDlgTemplate); // hjg 02-24-2006 fix memory problems

  // Resize the child dialog to its original design size, cached in displayRect.
  // For child dialogs in tabs, the "original design size" is the size of the
  // display area rectangle of the tab frame when the overall dialog is at its
  // original design size. We must be at this size when we initialize the
  // resizer.
  SetWindowPos(hwndChildDlg,
    HWND_TOP,
    ptabitem->displayRect.left,
    ptabitem->displayRect.top,
    ptabitem->displayRect.right - ptabitem->displayRect.left,
    ptabitem->displayRect.bottom - ptabitem->displayRect.top,
    0);

  // save off our newly created child dialog hwnd
  ptabitem->hwndChildDlg = hwndChildDlg;

  // create all controls belonging to this tab child dialog
  create_tab_child_controls(hwndChildDlg, &dlgparams, ptabitem);

  if(pDialogInfo->resizable)
    g2pvt_init_resizable_child_dialog(pDialogInfo, ptabitem, hwndChildDlg);

  // clean up
  delete [] dlgparams._pszTabText;

  return TRUE;
}

/*****************************************************************************
* void add_tab_dialog (HWND hwnd, TABITEM *ptabitem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void add_tab_dialog (HWND hwndParent, TABITEM *ptabitem)
{
  DIALOGINFO *pDialogInfo;
  TABITEM *next_tab;

  pDialogInfo = (DIALOGINFO *)GetWindowLong(hwndParent, GWL_USERDATA);
  if (pDialogInfo->_tabPages == NULL) {
    pDialogInfo->_tabPages = ptabitem;
    return;
  }

  // find the end of the list
  next_tab = pDialogInfo->_tabPages;
  while (next_tab->next != NULL)
  {
    next_tab = next_tab->next;
  }

  next_tab->next = ptabitem;
}


/*****************************************************************************
* void create_tab_container (HWND hwndTabCtrl, int tabCtrlId, int index,
*                                  wchar_t *pszText, HWND hwndParent, RECT *rectDisplay)
*
*   Description: Records info about this tab in a TABITEM structure.
*                No windows are created.
*   Input Arguments:
*        RectDisplay  -- The rect of the available display area, below the tabs themselves.
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void create_tab_container (HWND hwndTabCtrl, int tabCtrlId, int index,
                                 wchar_t *pszText, HWND hwndParent, RECT *rectDisplay)
{
  TABITEM *ptabitem;
  wchar_t *szTabName = NULL;
  int len;

  ptabitem = new TABITEM;
  if (ptabitem == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: create_tab_container #1\n");
    return;                // out of memory!
  }
  ZeroMemory((PVOID)ptabitem, sizeof(TABITEM));

  len = 1 + wcslen(pszText);
  szTabName = new wchar_t [len];
  if (szTabName == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: create_tab_container #2\n");
    return;                // out of memory!
  }
  ZeroMemory((PVOID)szTabName, len * sizeof(wchar_t));
  wcsncpy(szTabName, pszText, len);


  ptabitem->hwndChildDlg = NULL;   // NOTE: gets created later in create_mfc_tab_dialog
  ptabitem->tabControlId = tabCtrlId;
  ptabitem->tabIndex = index;
  ptabitem->szTabName = szTabName;
  CopyRect(&ptabitem->displayRect, rectDisplay);
  ptabitem->next = NULL;

  // add to global array
  add_tab_dialog(hwndParent, ptabitem);
}


/*****************************************************************************
* void g2pvt_cleanup_tab_pages (DIALOGINFO *pDialogInfo)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_cleanup_tab_pages (DIALOGINFO *pDialogInfo)
{
  TABITEM *tab, *next_tab;

  if (pDialogInfo == NULL) {
    return;
  }

  for(tab=pDialogInfo->_tabPages; tab; tab=next_tab) {
    if(tab->hwndChildDlg)	// Clear dlgInfo pointer in subdialog
      ::SetWindowLong(tab->hwndChildDlg, GWL_USERDATA, 0);

    next_tab = tab->next;
    if (tab->resizer)
      g2pvt_resizer_free(tab->resizer);
    tab->resizer = NULL;
    delete[] tab->szTabName;
    tab->szTabName = NULL;
    delete tab;
  }
  pDialogInfo->_tabPages = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CDynamicTabsDlg message handlers

BEGIN_MESSAGE_MAP(CDynamicTabsDlg, CDynamicBaseDlg)
END_MESSAGE_MAP()


/*****************************************************************************
* void on_tab_dialog_size (HWND hwndChildDlg, UINT message,
*                          WPARAM wParam, LPARAM lParam)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void on_tab_dialog_size (HWND hwndChildDlg, UINT message,
                                WPARAM wParam, LPARAM lParam)
{
  DIALOGINFO *pDialogInfo = NULL;
  TABITEM *tab = NULL;
  DWORD rc;

  pDialogInfo = (DIALOGINFO *)GetWindowLong(hwndChildDlg, GWL_USERDATA);
  if (pDialogInfo)
    for (tab=pDialogInfo->_tabPages; tab; tab=tab->next)
      if (tab->hwndChildDlg == hwndChildDlg)
        break;

  if (tab && tab->resizer)
    g2pvt_resizer_dlgproc(tab->resizer, &rc, hwndChildDlg, message, wParam, lParam);
}


/*****************************************************************************
* LRESULT WindowProc (UINT message, WPARAM wParam, LPARAM lParam)
*
*   Description: DlgProc for the inner child dialog associated with a tab.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
LRESULT CDynamicTabsDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  DIALOGINFO *pDialogInfo = NULL;
  LRESULT NonMFCResult = FALSE;

  switch (message)
  {
  case WM_INITDIALOG:
    m_ToolTipControl.Create(this);
    ::SetWindowLong(m_hWnd, GWL_USERDATA, (LONG) m_lpDialogInit);
    // return true to indicate init done because called by another dialog proc
    return TRUE;
    break;

  case WM_SIZE:
    on_tab_dialog_size(m_hWnd, message, wParam, lParam);
    return TRUE;
    break;

  case WM_NOTIFY:
    NonMFCResult = (BOOL)HANDLE_WM_NOTIFY(m_hWnd, wParam, lParam, DynamicDlg_OnNotify);
    break;

  case WM_CLOSE:
    pDialogInfo = (DIALOGINFO *)::GetWindowLong(m_hWnd, GWL_USERDATA);
    if(pDialogInfo)
      ::SendMessage(pDialogInfo->_pdialog->hwnd, WM_CLOSE, 0, 0);
    break;

  case WM_COMMAND:
  case WM_DRAWITEM:
  case WM_MEASUREITEM:
  case WM_CTLCOLOREDIT:
  case WM_CTLCOLORSTATIC:
  //GENSYM-1817:: Add g2 callback message if the textbox is tab-base.
  case WM_GENSYM_SEND_INFO_TO_G2:
    NonMFCResult = DynamicDlgProc(m_hWnd, message, wParam, lParam);
    break;

  default:
    break;
  }

  if (NonMFCResult)
    return NonMFCResult;

  return CDynamicBaseDlg::WindowProc(message, wParam, lParam);
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Tab Widget
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*****************************************************************************
* enum decode_tab_position (LPCTSTR str)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static enum XTPTabPosition
decode_tab_position (LPCTSTR str)
{
  // Keep values in sync with LISP tabs-extract-text-for-control-value
  switch(_ttoi(str)) {
  case 0: return xtpTabPositionTop;
  case 1: return xtpTabPositionLeft;
  case 2: return xtpTabPositionBottom;
  case 3: return xtpTabPositionRight;
  default: return xtpTabPositionTop;
  }
}


/*****************************************************************************
* TABITEM *get_tab_from_tab_handle (CG2TabWidget *pGTW, HWND hwndTabCtrl, HWND hWndDlg)
*
*   Description: Returns the TABITEM for the currently selected tab. Really poor name.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static TABITEM *get_tab_from_tab_handle (CG2TabWidget *pGTW, HWND hwndTabCtrl, HWND hWndDlg)
{
  TABITEM *p_cur_tabitem;
  int iSel;
  CXTPTabManager *pTManager;

  pTManager = pGTW->GetSelectedItem()->GetTabManager(); // get the tab manager
  if (!pTManager) return NULL;

  iSel = pTManager->GetCurSel(); // find the current selection
  // get the bookkeeping info for the selected tab
  p_cur_tabitem = get_tab_dialog(hWndDlg, pGTW->m_nControlId, iSel);

  return (p_cur_tabitem);
}


/*****************************************************************************
* CG2TabWidget constructor
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CG2TabWidget::CG2TabWidget ()
{
  m_nControlId = -1;
  m_bTabInitComplete = FALSE;

  m_bLabelsSet = FALSE;
  m_bSelectedSet = FALSE;
  m_bIconsSet = FALSE;
  m_bPositionSet= FALSE;
}


/*****************************************************************************
* void ResizeTabChildDialog (HWND hwndDlg, HWND hwndTabCtrl, TABITEM *pTabItem)
*
*   Description: Resize the child dialog, if exists, for given tab and update
*                the cached displayRect.  Note that pTabItem needn't be the
*                "current" (selected) tab.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2TabWidget::ResizeTabChildDialog (HWND hwndDlg, HWND hwndTabCtrl, TABITEM *pTabItem)
{
  HWND hwndChildDlg;
  RECT r;

  GetWindowRect(&r);
  ::MapWindowPoints(NULL, hwndDlg, (LPPOINT)&r, 2);
  AdjustRect(FALSE, &r);
  hwndChildDlg = pTabItem->hwndChildDlg;

  // displayRect holds the "original design size" of the child dialog, which we
  // need when the child dialog is first created.  So don't clobber it if the
  // child dialog has not been created.

  if (hwndChildDlg) {
    ::MoveWindow(hwndChildDlg, r.left, r.top, r.right-r.left, r.bottom-r.top, TRUE);
    CopyRect(&pTabItem->displayRect, &r);
  }
}


/*****************************************************************************
* void PopulateSelectedTab (CWnd *pParent, CONTROLITEM *pcontrol, TABITEM *p_cur_tabitem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2TabWidget::PopulateSelectedTab (CWnd *pParent, CONTROLITEM *pcontrol,
                                        TABITEM *p_cur_tabitem)
{
  BOOL bRet;

  if (!(p_cur_tabitem->hwndChildDlg)) {
    bRet = create_mfc_tab_dialog(pParent->m_hWnd, p_cur_tabitem, pcontrol->_controlId,
      0, p_cur_tabitem->szTabName); // create our special extra dialog
  }

  // Resize to fill tab, since it may have changed while we were hidden.
  if (p_cur_tabitem->resizer)
    ResizeTabChildDialog(pParent->m_hWnd, m_hWnd, p_cur_tabitem);

  // Lift the child dialog to top
  // This is needed for dynamic enable/disable (?)
  ::SetWindowPos(p_cur_tabitem->hwndChildDlg, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  m_bTabInitComplete = TRUE;
}


/*****************************************************************************
* void ParseString (TCHAR *pText)
*
*   Description: parses input string into 4 separate sections:
*      m_strLabels, m_strSelected, m_strIcons, m_strPosition
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2TabWidget::ParseString (TCHAR *pText)
{
  int idx;
  m_strToParse = pText;

  // extract and check m_strLabels
  idx = m_strToParse.Find(delim);
  if (-1 == idx) {
    m_strLabels = m_strToParse;
    if (!(m_strLabels.IsEmpty()))
      m_bLabelsSet = TRUE;
    return;
  }
  m_strLabels = m_strToParse.Left(idx);
  if (!(m_strLabels.IsEmpty()))
    m_bLabelsSet = TRUE;
  m_strToParse = m_strToParse.Right(m_strToParse.GetLength() - (idx+1));

  // extract and check m_strSelected
  idx = m_strToParse.Find(delim);
  if (-1 == idx) {
    m_strSelected = m_strToParse;
    if (!(m_strSelected.IsEmpty()))
      m_bSelectedSet = TRUE;
    return;
  }
  m_strSelected = m_strToParse.Left(idx);
  if (!(m_strSelected.IsEmpty()))
    m_bSelectedSet = TRUE;
  m_strToParse = m_strToParse.Right(m_strToParse.GetLength() - (idx+1));

  // extract and check m_strIcons
  idx = m_strToParse.Find(delim);
  if (-1 == idx) {
    m_strIcons = m_strToParse;
    if (!(m_strIcons.IsEmpty()))
      m_bIconsSet = TRUE;
    return;
  }
  m_strIcons = m_strToParse.Left(idx);
  if (!(m_strIcons.IsEmpty()))
    m_bIconsSet = TRUE;
  // don't need to "parse" the remainder, it is automatically m_strPosition
  m_strPosition = m_strToParse.Right(m_strToParse.GetLength() - (idx+1));

  // check m_strPosition
  if (!(m_strPosition.IsEmpty()))
    m_bPositionSet = TRUE;
}


/*****************************************************************************
* BOOL CG2TabWidget::SetSelectedTab (long selected)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL CG2TabWidget::SetSelectedTab (long selected)
{
  // set control to selected tab
  CXTPTabControl::SetCurSel(selected);
  return TRUE;
}


/*****************************************************************************
* void CreateTabs (CWnd *pParent, CONTROLITEM *pcontrol, RECT *rectAdj)
*
*   Description: Completes the initialization of this tab frame control,
*                creating the HWND and the tabs by parsing the string spec
*                in pcontrol, etc. Called only by g2pvt_create_mfc_control()
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2TabWidget::CreateTabs (CWnd *pParent, CONTROLITEM *pcontrol, RECT *rectAdj)
{
  int len, idx, nIcon, i = 0, nNumTabs = 0, nRet = 0, tabNum = 0, selected = 0;
  CString strIcon, strItemText;
  RECT rcDisplay;
  TABITEM *p_cur_tabitem;
  wchar_t *szTemp, *token = NULL, seps[] = L"\\";

  m_nControlId = pcontrol->_controlId;

  // need to put coordinates into a rectangle to call MapDialogRect
  SetRectEmpty(rectAdj);
  rectAdj->left = pcontrol->_x;
  rectAdj->top = pcontrol->_y;
  rectAdj->right = pcontrol->_x + pcontrol->_width;
  rectAdj->bottom = pcontrol->_y + pcontrol->_height;
  MapDialogRect(pParent->m_hWnd, rectAdj);

  if (!m_hWnd)
    Create(pcontrol->_styles, *rectAdj, pParent, pcontrol->_controlId);

  if (m_hWnd) {
    ParseString(pcontrol->_mText);
  }

  if (!m_bLabelsSet) {
    // No tabs; this is not an error, per fmw.  Don't do any further setup.  
    return;
  }

  CImageList tempImageList;
  tempImageList.Create(16, 16, ILC_COLOR24 | ILC_MASK, 10, 1);

  SetPosition(decode_tab_position(m_strPosition)); // position of the tabs

  szTemp = wcsdup(m_strLabels);

  len = m_strLabels.GetLength()+1;
  token = wcstok(szTemp, seps);

  while (token != NULL) {
    nIcon = -1;
    if (m_bIconsSet) {
      // we have icons
      idx = m_strIcons.Find(seps);
      if (-1 != idx) {
        strIcon = m_strIcons.Left(idx);
        nIcon = _ttoi(strIcon);
        m_strIcons = m_strIcons.Right(m_strIcons.GetLength() - (idx+1));
      } else {
        strIcon = m_strIcons;
        if (!strIcon.IsEmpty())
          nIcon = _ttoi(strIcon);
      }
    }

    // Convert G2 icon handle to index in our private imagelist.
    if(nIcon >= 0) {
      HICON hIcon = g2pvt_get_native_icon(nIcon);
      nIcon = tempImageList.Add(hIcon);
      DestroyIcon(hIcon);      
    }

    InsertItem(tabNum, token, NULL, nIcon); // add the tab

    if (m_bSelectedSet && (0 == wcscmp(token, m_strSelected))) {
      selected = tabNum;
    }

    // calculate display rectangle
    SetRectEmpty(&rcDisplay);
    GetWindowRect(&rcDisplay);
    pParent->ScreenToClient((LPPOINT)&rcDisplay.left);
    pParent->ScreenToClient((LPPOINT)&rcDisplay.right);

    AdjustRect(FALSE, &rcDisplay); // adjust everything to fit on a tab

    // fill in the Gensym bookkeeping tab data structure
    create_tab_container(m_hWnd, pcontrol->_controlId, tabNum, token,
                         pParent->m_hWnd, &rcDisplay); // creates *ptabitem
    token = wcstok(NULL, seps);
    tabNum++;
  }
  free(szTemp);

  SetImageList(&tempImageList);	// Contents are copied

  for (tabNum--;tabNum>=0;tabNum--)
  {
	  p_cur_tabitem = get_tab_dialog(pParent->m_hWnd, pcontrol->_controlId, tabNum);
	  create_mfc_tab_dialog(pParent->m_hWnd, p_cur_tabitem, pcontrol->_controlId,
		  0, p_cur_tabitem->szTabName);
  }
  // set control to selected tab
  p_cur_tabitem = get_tab_dialog(pParent->m_hWnd, pcontrol->_controlId, selected);
  SetSelectedTab(selected);

  if (p_cur_tabitem->resizer)
    ResizeTabChildDialog(pParent->m_hWnd, m_hWnd, p_cur_tabitem);

  // Lift to top
  SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

  PopulateSelectedTab(pParent, pcontrol, p_cur_tabitem);

  m_bTabInitComplete = TRUE;
}


/*****************************************************************************
* TCHAR *GetControlValue ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
TCHAR *CG2TabWidget::GetControlValue ()
{
  int nCurSel;
  CXTPTabManagerItem *pItem;
  CString strText;
  //TCHAR *pText;
  wchar_t *converted_text;

  if ((!m_bLabelsSet) || (!m_bTabInitComplete)) return NULL;

  nCurSel = GetCurSel();
  pItem = GetItem(nCurSel);

  strText= pItem->GetCaption();

  //pText = new TCHAR[strText.GetLength()+1];

  //_tcscpy(pText, strText);
  //converted_text = g2pvt_windows_to_g2_text(pText);
  converted_text = g2pvt_windows_to_g2_text((LPTSTR) (LPCTSTR) strText);

  //delete pText;

  return converted_text;

}



BEGIN_MESSAGE_MAP(CG2TabWidget, CXTPTabControl)
//{{AFX_MSG_MAP(testtab)
ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
ON_NOTIFY_REFLECT(TCN_SELCHANGING, OnSelchanging)
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*****************************************************************************
* void OnSelchange (NMHDR *pNMHDR, LRESULT *pResult)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2TabWidget::OnSelchange (NMHDR *pNMHDR, LRESULT *pResult)
{
  CXTPTabManager *pTManager;
  int iSel;
  TABITEM *p_cur_tabitem;
  CWnd *pParent;
  CONTROLITEM *pcontrol;

  if (FALSE == m_bTabInitComplete)
    return;

  pTManager = m_pSelected->GetTabManager();
  iSel = pTManager->GetCurSel();

  pParent = GetParent();
  p_cur_tabitem = get_tab_dialog(pParent->m_hWnd, pNMHDR->idFrom, iSel);

  if (p_cur_tabitem == NULL)
    return;                        // doh!

  pcontrol = g2pvt_lookup_control_by_hwnd(pNMHDR->idFrom, pParent->m_hWnd);
  PopulateSelectedTab(pParent, pcontrol, p_cur_tabitem);
  g2pvt_ddlg_respond(pParent->m_hWnd, pcontrol->_controlId, pcontrol->_respcode);

  *pResult = 0;
}


/*****************************************************************************
* void OnSelchanging (NMHDR *pNMHDR, LRESULT *pResult)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2TabWidget::OnSelchanging (NMHDR *pNMHDR, LRESULT *pResult)
{
  *pResult = 0;
}


/*****************************************************************************
* void OnSize (UINT nType, int cx, int cy)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2TabWidget::OnSize (UINT nType, int cx, int cy)
{
  CXTPTabControl::OnSize(nType, cx, cy);

  if (! m_bTabInitComplete)
    return;

  HWND hwndDlg = GetParent()->GetSafeHwnd();
  if (!hwndDlg) return;

  // Resize the child dialog of each tab which has one.
  for (int i = 0; i < GetItemCount(); i++) {
    TABITEM *pTabItem = get_tab_dialog(hwndDlg, m_nControlId, i);
    if(pTabItem && pTabItem->hwndChildDlg)
      ResizeTabChildDialog(hwndDlg, m_hWnd, pTabItem);
  }
}

/*****************************************************************************
* void PostNcDestroy ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2TabWidget::PostNcDestroy ()
{
  // - this auto delete done according to my reading of MSDN TN017 - 'Destroying
  // Window Objects' if funny aborts happen, this might be a good place to look
  // for problems. hjg -06-16-2006
  CXTPTabControl::PostNcDestroy();
  delete this;
}

/*****************************************************************************
* void g2pvt_init_G2TabWidget_resizable_child_dialog (HWND hwndTabCtrl, DIALOGINFO *dlgInfo)
*
*   Description: Called only when overall dialog is first created.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_init_G2TabWidget_resizable_child_dialog (HWND hwndTabCtrl, DIALOGINFO *dlgInfo)
{
  CG2TabWidget *pGTW;
  TABITEM *p_cur_tabitem;
  HWND hwndDlg;

  pGTW = (CG2TabWidget*)CWnd::FromHandle(hwndTabCtrl);
  if (!pGTW) return;

  hwndDlg = GetParent(hwndTabCtrl);
  if (!hwndDlg) return;

  p_cur_tabitem = get_tab_from_tab_handle(pGTW, hwndTabCtrl, hwndDlg);

  if (p_cur_tabitem) {
    if (p_cur_tabitem->hwndChildDlg) {
      g2pvt_init_resizable_child_dialog(dlgInfo, p_cur_tabitem, p_cur_tabitem->hwndChildDlg);
    }
  }
}


/*****************************************************************************
* wchar_t *g2pvt_get_contents_of_G2TabWidget_control (HWND hwndControl, CONTROLITEM *pitem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
wchar_t *g2pvt_get_contents_of_G2TabWidget_control (HWND hwndControl, CONTROLITEM *pitem)
{
  HWND hwndDlg;
  DIALOGINFO *dialog_info = NULL;
  CONTROLHWND *ctrl_hwnd = NULL;
  CG2TabWidget *p;

  hwndDlg = GetParent(hwndControl);
  if (hwndDlg == NULL) return NULL;

  dialog_info = (DIALOGINFO *)::GetWindowLong(hwndDlg, GWL_USERDATA);
  if (dialog_info == NULL) return NULL;

  ctrl_hwnd = g2pvt_get_control_hwnd_by_controlId(dialog_info, pitem->_controlId);
  if (ctrl_hwnd == NULL) return NULL;

  p = (CG2TabWidget *)(ctrl_hwnd->pObj);

  return p->GetControlValue();
}


/*****************************************************************************
* long g2pvt_modify_tab_frame_control (CWnd *pObj, int updateType, HWND hwndDlg,
*                                      CONTROLITEM *pcontrol, wchar_t *value)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2pvt_modify_tab_frame_control (CWnd *pObj, int updateType, HWND hwndDlg,
                                     CONTROLITEM *pcontrol, wchar_t *value)
{
  CG2TabWidget *pTab;
  TABITEM *the_tab;
 
  if (updateType != SELECTED_TAB) {
    g2pvt_gprintf(G2PVT_ERROR, "unrecognized modify action for tab-frame: %d\n",
                  updateType);
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }
  the_tab = find_tab_by_name(hwndDlg, pcontrol->_controlId, value);
  if (the_tab == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "unrecognized tab: %S\n", value);
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }
  pTab = (CG2TabWidget *)pObj;
  if (pTab->SetSelectedTab(the_tab->tabIndex)) {
    return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
  }
  return DYNAMIC_DIALOG_UPDATE_FAILED;
}
