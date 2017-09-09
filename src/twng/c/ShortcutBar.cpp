/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      ShortcutBar.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   -fmw, 3/8/05
 +
 + Description:  Shortcut Bar (aka Outlook Bar, Toolbox, etc) for TWNG.
 +
 + Dependencies: Codejock XTP library (http://www.codejock.com)
 +
 + Modifications:
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "ShortcutBar.h"
#include "ListBar.h"

IMPLEMENT_DYNCREATE(G2ShortcutBar, CXTOutBarCtrl)

BEGIN_MESSAGE_MAP(G2ShortcutBar, CXTOutBarCtrl)
  ON_WM_SETFOCUS()
  ON_WM_SIZE()
  ON_WM_DESTROY()
  ON_WM_LBUTTONDOWN()
  ON_MESSAGE(WM_ICON_CHANGED, OnIconChanged)
  ON_MESSAGE(XTWM_OUTBAR_NOTIFY,OnOutBarNotify)
END_MESSAGE_MAP()

G2ShortcutBar::G2ShortcutBar(int handle)
{
  m_handle = handle;
  m_g2pointer = -1;
  SAVE_WND();
  VTRACE("Construct G2ShortcutBar[%d] %08X\n", m_handle, this);
}

G2ShortcutBar::~G2ShortcutBar() {
  VTRACE("Destruct G2ShortcutBar[%d] %08X\n", m_handle, this);
  FORGET_WND();
  if(m_g2pointer>=0)
    g2ext_decache_g2pointer(m_g2pointer);
  m_handle=0;
  m_g2pointer=-1;
}

void G2ShortcutBar::PostNcDestroy()
{
  CXTOutBarCtrl::PostNcDestroy();
  delete this;
}

void G2ShortcutBar::OnSetFocus(CWnd* pOldWnd)
{
  CXTOutBarCtrl::OnSetFocus(pOldWnd);

  VTRACE("OnSetFocus "); POB(this);

  if(m_handle > 0)
    g2pvt_send_window_activated(m_hWnd, m_handle);
}

void G2ShortcutBar::OnSize(UINT nType, int cx, int cy) 
{
  VTRACE("G2ShortcutBar::OnSize [%d] type:%d %dx%d\n", m_handle, nType, cx, cy);
  CXTOutBarCtrl::OnSize(nType, cx, cy);
  g2pvt_view_sized(this, m_handle);
}

void G2ShortcutBar::OnDestroy()
{
  VTRACE("OnDestroy shortcut bar %08X\n", this);
  if(m_handle > 0)
    g2pvt_send_window_closed(m_hWnd, m_handle);
  CXTOutBarCtrl::OnDestroy();
}

void G2ShortcutBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
  g2pvt_enter_modal_loop();
  CXTOutBarCtrl::OnLButtonDown(nFlags, point); // Modal loop during drag, etc.
  g2pvt_exit_modal_loop();
}

LRESULT G2ShortcutBar::OnIconChanged(WPARAM native_icon, LPARAM iconID)
{
  int image = g2pvt_icon_index(native_icon);
  int folder = GetSelFolder();
  CRect r;
  int i;

  for(i=0; i<GetItemCount(); i++) {
    if(image == GetItemImage(i)) {
      GetIconRect(folder, i, r);
      InvalidateRect(r);
    }
  }
  return 0;
}

LRESULT G2ShortcutBar::OnOutBarNotify(WPARAM wParam, LPARAM lParam)
{
  int nBarAction = wParam;
  XT_OUTBAR_INFO* pObi = (XT_OUTBAR_INFO*)lParam;
  int folder = pObi->bFolder ? pObi->nIndex : GetSelFolder();
  int item   = pObi->bFolder ? -1 : pObi->nIndex;
  int dragTo = pObi->nDragTo;
  LPWSTR label = (LPWSTR) pObi->lpszText;

  // Keep args in sync with Lisp decode-native-control-event

  switch(nBarAction) {
   case OBN_XT_ITEMHOVER:	// TODO: Might want to send this one.
   case OBN_XT_DELETEFOLDER:
   case OBN_XT_DELETEITEM:
     break;
   default:
     g2pvt_fire_control_event(GENSYM_SHORTCUT_BAR, m_handle, nBarAction, dragTo, folder, item, label);
  }

  return TRUE;
}

void G2ShortcutBar::SetColors(COLORREF bg, COLORREF fg)
{
  if(bg != (COLORREF)-1) SetBackColor(bg);
  if(fg != (COLORREF)-1) SetTextColor(fg);
  Invalidate(FALSE);
}



/*
 * Internal Interface
 */

int g2pvt_create_shortcut_bar(int handle, LPWSTR title, int obstyle,
			       int x, int y, int width, int height,
			       int dock, int neighborID, long min_width, long min_height)
{
  CMainFrame *pFrame = GetMainWnd();
  G2ShortcutBar *pBar = new G2ShortcutBar(handle);

  // This used to specify WS_EX_STATICEDGE, but it is very strange to put framing onto
  // the inner child window. Framing belongs on the container window.
  pBar->CreateEx(0, WS_CHILD, WinSize(width,height), pFrame, handle, obstyle);

  // Use shared native-icons imagelists.
  pBar->SetImageList(&pFrame->m_smallImageList, OBS_XT_SMALLICON);
  pBar->SetImageList(&pFrame->m_largeImageList, OBS_XT_LARGEICON);

  // Config options
  pBar->SetAnimationTickCount(5);
  pBar->m_g2pointer = SavePtr(pBar->m_hWnd);

  // Create pane to contain it.
  pFrame->WrapWnd(pBar, handle, x, y, width, height, dock, neighborID, CSize(min_width, min_height), title);
  return pBar->m_g2pointer;
}

int g2pvt_manage_shortcut_bar(int opcode, int handle, LPWSTR string, 
			       int nFolder, int icon, LPWSTR tooltip)
{
  G2ShortcutBar *pBar = FIND_WND(handle,G2ShortcutBar);
  CXTOutBarFolder* pFolder = NULL;
  int i;

  MTRACE("g2ext_manage_shortcut_bar[%d] op=%d folder=%d icon=%x data=%d \"%ls\"\n",
	 handle, opcode, nFolder, icon, string);

  if(!pBar)
    return -1;

  switch(opcode) {
   case SHORTCUT_BAR_DESTROY:
     DESTROY_WND(handle);
     break;

   case SHORTCUT_BAR_ADD_FOLDER:
     nFolder = pBar->AddFolder(string, 0);
     pBar->Invalidate();
     return nFolder;

   case SHORTCUT_BAR_ADD_ITEM:
     pFolder = pBar->GetBarFolder(nFolder);
     i = pBar->InsertItem(nFolder, pFolder->GetItemCount(), string, g2pvt_icon_index(icon), 0);
     pBar->Invalidate();
     return i;

   case SHORTCUT_BAR_CLEAR:
     for(i=0; i<pBar->GetFolderCount(); i++)
       pBar->RemoveAllItems(i);

     for(i=pBar->GetFolderCount()-1; i>=0; i--)
       pBar->RemoveFolder(i);
     pBar->Invalidate();	// Needed?
     return 0;


   case SHORTCUT_BAR_SELECT_FOLDER:
     pBar->SetSelFolder(nFolder);
     return nFolder;
   case SHORTCUT_BAR_ENABLE_FOLDER:
   case SHORTCUT_BAR_DISABLE_FOLDER:
     pFolder = pBar->GetBarFolder(nFolder);
     for(i=0; i<pFolder->GetItemCount(); i++) {
       CXTOutBarItem* pItem = pFolder->GetItemAt(i);
       pItem->EnableItem(opcode == SHORTCUT_BAR_ENABLE_FOLDER);
     }
     if(nFolder == pBar->GetSelFolder())
       pBar->Invalidate();
     break;


    // icon==item number here.
   case SHORTCUT_BAR_SELECT_ITEM:
     pBar->SetSelItem(nFolder, icon);
     return nFolder;
   case SHORTCUT_BAR_ENABLE_ITEM:
   case SHORTCUT_BAR_DISABLE_ITEM:
     pBar->EnableItem(nFolder, icon, opcode == SHORTCUT_BAR_ENABLE_ITEM);
     if(nFolder == pBar->GetSelFolder())
       pBar->Invalidate();
     break;


   case SHORTCUT_BAR_SMALL_ICONS:
     pBar->SetSmallIconView(TRUE, -1); // For all folders.
     return 1;

   case SHORTCUT_BAR_LARGE_ICONS:
     pBar->SetSmallIconView(FALSE, -1); // For all folders.
     return 1;
 
   case SHORTCUT_BAR_BACKGROUND_COLOR:
     pBar->SetColors((COLORREF)nFolder, (COLORREF)-1);
     break;

   case SHORTCUT_BAR_FOREGROUND_COLOR:
     pBar->SetColors((COLORREF)-1, (COLORREF)nFolder);
     break;

   default:
     return -1;
  }
  return 1;
}



/*
 * Generic G2 Interface
 */

long g2ext_create_shortcut_bar(long handle, long style, long obstyle,
			       LPWSTR title,
			       long x, long y, long width, long height,
			       long dock, long neighborID, long min_width, long min_height)
{
  switch(style) {
   case SHORTCUT_BAR_STYLE_DEFAULT:
     return g2pvt_create_shortcut_bar(handle, title, obstyle, x, y, width, height, dock, neighborID, min_width, min_height);
   case SHORTCUT_BAR_STYLE_LISTBAR:
     return g2pvt_create_list_bar(handle, title, x, y, width, height, dock, neighborID, min_width, min_height);
   default: return -1;
  }
}

long g2ext_manage_shortcut_bar(long opcode, long handle, LPWSTR string, 
			       long nFolder, long icon, LPWSTR tooltip)
{
  CWnd *pWnd = FIND_WND(handle,CWnd);

  if(!pWnd)
    return -1;

  else if(pWnd->IsKindOf(RUNTIME_CLASS(G2ShortcutBar)))
    return g2pvt_manage_shortcut_bar(opcode, handle, string, nFolder, icon, tooltip);

  else if(pWnd->IsKindOf(RUNTIME_CLASS(G2ListBar)))
    return g2pvt_manage_list_bar(opcode, handle, string, nFolder, icon, tooltip);

  else
    return -1;
}
