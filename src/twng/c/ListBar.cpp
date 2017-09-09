/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      ListBar.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   -fmw, 10/11/05
 +
 + Description:  List Bar (aka Outlook 2003 Bar) for TWNG.
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

IMPLEMENT_DYNCREATE(G2ListBar, CXTPShortcutBar)

BEGIN_MESSAGE_MAP(G2ListBar, CXTPShortcutBar)
  ON_WM_SETFOCUS()
  ON_WM_SIZE()
  ON_WM_DESTROY()
  ON_WM_LBUTTONDOWN()
  ON_MESSAGE(XTPWM_SHORTCUTBAR_NOTIFY, OnListBarNotify)
  ON_MESSAGE(WM_ICON_CHANGED, OnIconChanged)
END_MESSAGE_MAP()

G2ListBar::G2ListBar(int handle)
{
  m_handle = handle;
  m_g2pointer = -1;
  m_clrBack = ::GetSysColor(COLOR_APPWORKSPACE);
  m_clrText = RGB(255,255,255);
  SAVE_WND();
  VTRACE("Construct G2ListBar[%d] %08X\n", m_handle, this);
}

G2ListBar::~G2ListBar() {
  VTRACE("Destruct G2ListBar[%d] %08X\n", m_handle, this);
  FORGET_WND();
  if(m_g2pointer>=0)
    g2ext_decache_g2pointer(m_g2pointer);
  m_handle=0;
  m_g2pointer=-1;
}

void G2ListBar::PostNcDestroy()
{
  CXTPShortcutBar::PostNcDestroy();
  delete this;
}

void G2ListBar::OnSetFocus(CWnd* pOldWnd)
{
  CXTPShortcutBar::OnSetFocus(pOldWnd);
  VTRACE("OnSetFocus "); POB(this);
  if(m_handle > 0)
    g2pvt_send_window_activated(m_hWnd, m_handle);
}

void G2ListBar::OnSize(UINT nType, int cx, int cy) 
{
  CXTPShortcutBar::OnSize(nType, cx, cy);
  g2pvt_view_sized(this, m_handle);
}

void G2ListBar::OnDestroy()
{
  VTRACE("OnDestroy list bar %08X\n", this);
  if(m_handle > 0)
    g2pvt_send_window_closed(m_hWnd, m_handle);
  CXTPShortcutBar::OnDestroy();
}

#ifdef _DEBUG
static char *lvnCode(UINT code)
{
  switch(code) {
   case NM_OUTOFMEMORY: return "NM_OUTOFMEMORY";
   case NM_CLICK: return "NM_CLICK";
   case NM_DBLCLK: return "NM_DBLCLK";
   case NM_RETURN: return "NM_RETURN";
   case NM_RCLICK: return "NM_RCLICK";
   case NM_RDBLCLK: return "NM_RDBLCLK";
   case NM_SETFOCUS: return "NM_SETFOCUS";
   case NM_KILLFOCUS: return "NM_KILLFOCUS";
   case NM_CUSTOMDRAW: return "NM_CUSTOMDRAW";
   case NM_HOVER: return "NM_HOVER";
   case NM_NCHITTEST: return "NM_NCHITTEST";
   case NM_KEYDOWN: return "NM_KEYDOWN";
   case NM_RELEASEDCAPTURE: return "NM_RELEASEDCAPTURE";
   case NM_SETCURSOR: return "NM_SETCURSOR";
   case NM_CHAR: return "NM_CHAR";

   case LVN_ITEMCHANGING: return "LVN_ITEMCHANGING";
   case LVN_ITEMCHANGED: return "LVN_ITEMCHANGED";
   case LVN_INSERTITEM: return "LVN_INSERTITEM";
   case LVN_DELETEITEM: return "LVN_DELETEITEM";
   case LVN_DELETEALLITEMS: return "LVN_DELETEALLITEMS";
   case LVN_COLUMNCLICK: return "LVN_COLUMNCLICK";
   case LVN_BEGINDRAG: return "LVN_BEGINDRAG";
   case LVN_BEGINRDRAG: return "LVN_BEGINRDRAG";
   case LVN_ODCACHEHINT: return "LVN_ODCACHEHINT";
   case LVN_ODFINDITEMA: return "LVN_ODFINDITEMA";
   case LVN_ODFINDITEMW: return "LVN_ODFINDITEMW";
   case LVN_ITEMACTIVATE: return "LVN_ITEMACTIVATE";
   case LVN_ODSTATECHANGED: return "LVN_ODSTATECHANGED";
   case LVN_HOTTRACK: return "LVN_HOTTRACK";
   case LVN_BEGINLABELEDIT: return "LVN_BEGINLABELEDIT";
   case LVN_ENDLABELEDIT: return "LVN_ENDLABELEDIT";
   case LVN_GETDISPINFO: return "LVN_GETDISPINFO";
   case LVN_SETDISPINFO: return "LVN_SETDISPINFO";
   default: return "?";
  }
}
#endif

G2ListBarPane *G2ListBar::GetPane(int nFolder)
{
  CXTPShortcutBarItem *pFolder = nFolder>=0 ? GetItem(nFolder) : GetSelectedItem();
  return pFolder ? (G2ListBarPane *)pFolder->GetItemData() : NULL; // Yuck.
}

CListCtrl *G2ListBar::GetListCtrl(int nFolder)
{
  G2ListBarPane *pPane = GetPane(nFolder);
  return pPane ? pPane->GetListCtrl() : NULL;
}

void G2ListBar::SetColors(COLORREF bg, COLORREF fg)
{
  CListCtrl *pList;

  m_clrBack = bg;
  m_clrText = fg;
  for(int i=0; i<GetItemCount(); i++)
    if((pList = GetListCtrl(i))) {
      pList->SetBkColor(m_clrBack);
      pList->SetTextBkColor(m_clrBack);
      pList->SetTextColor(m_clrText);
      pList->Invalidate();
    }
}

void G2ListBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
  g2pvt_enter_modal_loop();
  CXTPShortcutBar::OnLButtonDown(nFlags, point); // Modal loop during drag, etc.
  g2pvt_exit_modal_loop();
}

LRESULT G2ListBar::OnIconChanged(WPARAM native_icon, LPARAM iconID)
{
  CListCtrl *pList = GetListCtrl(); // The currently selected one.
  CXTPShortcutBarItem* pFolder;
  int image = g2pvt_icon_index(native_icon);
  int i;
  LVITEM lvi;
  RECT r;

  // Update folder icons.
  for(i=1; i<GetItemCount(); i++) {
    pFolder = GetItem(i);
    if(pFolder->IsVisible() && pFolder->GetID() == iconID)
      InvalidateRect(pFolder->GetItemRect());
  }

  // Update folder icons in expand bar.
  pFolder = GetItem(0);
  if(pFolder->IsVisible())
    InvalidateRect(pFolder->GetItemRect());

  if(!pList) return 0;

  // Update item icons (in currently visible CListCtrl)
  ZeroMemory(&lvi,sizeof(lvi));
  lvi.mask = LVIF_IMAGE;
  for(i=pList->GetTopIndex(); i< pList->GetTopIndex() + pList->GetCountPerPage(); i++) {
    lvi.iItem = i;
    pList->GetItem(&lvi);
    if(lvi.iImage == image && pList->GetItemRect(i, &r, LVIR_ICON))
      pList->InvalidateRect(&r);
  }
  return 0;
}

LRESULT G2ListBar::OnListBarNotify(WPARAM wParam, LPARAM lParam)
{
  CXTPShortcutBarItem* pFolder;
  G2ListBarPane *pPane;

  switch(wParam) {
   case XTP_SBN_SELECTION_CHANGING:
     pFolder = (CXTPShortcutBarItem *)lParam;
     pPane = (G2ListBarPane *)pFolder->GetItemData();
     pPane->FireEvent(OBN_XT_FOLDERCHANGE);
     break;
  }
  return 1;
}

int G2ListBar::AddFolder(LPCTSTR caption, int icon, LPCTSTR tooltip)
{
  int nFolder = GetItemCount() - 1; // The "expand bar" at the bottom counts as one item.
  int nID;
  G2ListBarPane *pPane;
  CXTPShortcutBarItem *pFolder;

  if(icon < 0)
    icon = STOCK_ICON_FLAG | GMS_TOOLBOX_ICON;
  nID = GetMainWnd()->StoreNativeIcon(icon);

  pPane = new G2ListBarPane(nFolder);
  pPane->Create(caption, this, m_clrBack, m_clrText);

  pFolder = AddItem(nID, pPane);
  pFolder->SetCaption(caption);
  pFolder->SetTooltip(tooltip);
  pFolder->SetItemData((DWORD)pPane); // Yuck.
  if(nFolder==0) SelectItem(pFolder);
  return nFolder;
}

// Add a text-based item to given folder. This requires that we have a list control in there.
void G2ListBar::AddTextItem(LPCTSTR label, int nFolder, int icon, LPCTSTR tooltip)
{
  G2ListBarPane *pPane = GetPane(nFolder);
  if(!pPane)
    return;

  CListCtrl *pList = pPane->EnsureListCtrl();

  pList->InsertItem(LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM,
		    pList->GetItemCount(), label, 0, 0,
		    g2pvt_icon_index(icon),
		    (tooltip[0] != L'\0') ? (LPARAM)wcsdup(tooltip) : NULL); // FIXME: leaks
}

// Add a window-based item to given folder.
void G2ListBar::AddWindowItem(LPCTSTR caption, int nFolder, CWnd *pWnd)
{
  G2ListBarPane *pPane = GetPane(nFolder);
  CXTPShortcutBarPaneItem *pItem;
  CRect r;

  if(!pPane)
    return;

  pWnd->ShowWindow(SW_HIDE);
  pWnd->SetParent(pPane);
  pWnd->GetClientRect(&r);
  pItem = pPane->AddItem(caption, pWnd, r.Height());

  // WS_CAPTION has already been clobbered by the time we get here, eg, by
  // g2pvt_show_dialog_in_pane.
  //  pItem->ShowCaption((pWnd->GetStyle() & WS_CAPTION) != 0);
  pItem->ShowCaption(TRUE);

  pWnd->ShowWindow(SW_SHOW);
  pPane->Reposition();
  Reposition();
}

void G2ListBar::SelectItemInFolder(int nFolder, int nIndex)
{
  G2ListBarPane *pPane = GetPane(nFolder);
  CXTPShortcutBarPaneItem *pItem;
  CListCtrl *pList;

  if(!pPane)
    return;

  pList = pPane->GetListCtrl();

  if(pList) {
    pList->SetSelectionMark(nIndex);
    pList->EnsureVisible(nIndex, FALSE);
    return;
  }

  pItem = pPane->GetItem(nIndex);
  if(!pItem)
    return;
  // TODO when m_pWndClient is accessable.
  // pItem->m_pWndClient->SetFocus();
}

void G2ListBar::SetLargeIcons(BOOL large)
{
  int i;
  CListCtrl *pList;

  for(i=0; i<GetItemCount()-1; i++)
    if((pList = GetListCtrl(i)))
      pList->ModifyStyle(LVS_TYPEMASK, large ? LVS_ICON : LVS_LIST);
}




/*
 * The content of each folder is a G2ListBarPane, which in turn contains a list
 * control showing a set of items or else a bunch of native views.
 */

BEGIN_MESSAGE_MAP(G2ListBarPane, CXTPShortcutBarPane)
 ON_WM_PARENTNOTIFY()
END_MESSAGE_MAP()

G2ListBarPane::G2ListBarPane(int nFolder) {
  m_nFolder = nFolder;
  m_bg = RGB(255,255,255);
  m_fg = RGB(0,0,0);
}

G2ListBarPane::~G2ListBarPane() {
}

void G2ListBarPane::OnParentNotify(UINT message, LPARAM lParam)
{
  CXTPShortcutBarPane::OnParentNotify(message, lParam);
  if(message == WM_DESTROY) {
    HWND hwnd = (HWND)lParam;
    // TODO: Here we should remove the pane item, but Codejock doesn't provide a
    // method for that yet.
  }
}

BOOL G2ListBarPane::Create(LPCTSTR lpszCaption, CXTPShortcutBar* pParent, COLORREF bg, COLORREF fg)
{
  if (!CXTPShortcutBarPane::Create(lpszCaption, pParent))
    return FALSE;

  SetIndent(0,0,0,0);		// Default is (0, 5, 0, 5)

  m_bg = bg;
  m_fg = fg;
  return TRUE;
}

CListCtrl *G2ListBarPane::GetListCtrl()
{
  return m_listCtrl.GetSafeHwnd() ? &m_listCtrl : NULL;
}

void G2ListBarPane::Reposition()
{
  CRect r;
  GetClientRect(&r);
  OnSize(SIZE_RESTORED, r.Width(), r.Height());	// Hack to get child windows repositioned
}

CListCtrl *G2ListBarPane::EnsureListCtrl()
{
  if(GetListCtrl())
    return GetListCtrl();

  CMainFrame *pFrame = GetMainWnd();

  CRect r;
  GetClientRect(&r);

  m_listCtrl.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | 
		    LVS_ALIGNTOP | LVS_AUTOARRANGE | LVS_ICON | LVS_NOCOLUMNHEADER | LVS_SHAREIMAGELISTS |
		    LVS_SHOWSELALWAYS | LVS_SINGLESEL,
		    r, this, 100+m_nFolder);

  // Default fg/bg to look like classic shbar. TODO: Depends on theme!
  m_listCtrl.SetBkColor(m_bg);
  m_listCtrl.SetTextBkColor(m_bg);
  m_listCtrl.SetTextColor(m_fg);

  // Use shared native-icons imagelists.
  m_listCtrl.SetImageList(&pFrame->m_smallImageList, LVSIL_SMALL);
  m_listCtrl.SetImageList(&pFrame->m_largeImageList, LVSIL_NORMAL);

  CXTPShortcutBarPaneItem *pItem = AddItem(L"ListView", &m_listCtrl, 350);
  pItem->ShowCaption(FALSE);
  return &m_listCtrl;
}

int G2ListBarPane::GetHandle()
{
  return ((G2ListBar*)m_pShortcutBar)->GetHandle();
}

void G2ListBarPane::FireEvent(UINT nType, int nItem)
{
  CString label;
  if(GetListCtrl())
    label = m_listCtrl.GetItemText(nItem, 0);
  g2pvt_fire_control_event(GENSYM_SHORTCUT_BAR, GetHandle(), nType, -1, m_nFolder, nItem, label);
}

int G2ListBarPane::SelectedItem()
{
  if(!GetListCtrl())
    return -1;

  POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
  if(pos != NULL)
    return m_listCtrl.GetNextSelectedItem(pos);
  return -1;
}

BOOL G2ListBarPane::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
  NMLISTVIEW *pLV = (NMLISTVIEW*)lParam;

  switch(pLV->hdr.code) {
   case NM_CLICK:
     FireEvent(OBN_XT_ITEMCLICK, ((NMITEMACTIVATE*)pLV)->iItem);
     break;

   case NM_RCLICK:
     FireEvent(OBN_XT_ITEMRCLICK, ((NMITEMACTIVATE*)pLV)->iItem);
     break;

   case LVN_BEGINDRAG:
     FireEvent(OBN_XT_BEGINDRAG, pLV->iItem);
     break;

   case LVN_HOTTRACK:
     break;
  }
  return CXTPShortcutBarPane::OnNotify(wParam, lParam, pResult);
}




/*
 * Internal Interface
 */

// toolbox == CXTPTaskPanel
int g2pvt_create_list_bar(int handle, LPWSTR title,
			  int x, int y, int width, int height,
			  int dock, int neighborID, int min_width, int min_height)
{
  CMainFrame *pFrame = GetMainWnd();
  G2ListBar *pBar = new G2ListBar(handle);

  pBar->Create(WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, WinSize(width,height), pFrame, handle);
  pBar->SetOwner(pFrame);
  pBar->SetMinimumClientHeight(50);                          // TODO: Configurable
  pBar->m_g2pointer = SavePtr(pBar->m_hWnd);
  // pBar->SetTheme(xtpShortcutThemeOffice2003);                // Theme was managed by CXTPShortcutBarThemeManager
  // xtpShortcutThemeOffice2000, xtpShortcutThemeOfficeXP, xtpShortcutThemeOffice2003
  // pBar->SetExpandedLinesCount(int nCount);

  CSize min_size(min_width, min_height);
  pFrame->WrapWnd(pBar, handle, x, y, width, height, dock, neighborID, min_size, title);
  return pBar->m_g2pointer;
}

BOOL g2pvt_is_listbar(CWnd *pWnd)
{
  return pWnd->IsKindOf(RUNTIME_CLASS(G2ListBar));
}

void g2pvt_add_view_to_listbar(G2ListBar *pBar, LPCTSTR caption, int nFolder, CWnd *pWnd)
{
  pBar->AddWindowItem(caption, nFolder, pWnd);
}

int g2pvt_manage_list_bar(int opcode, int handle, LPWSTR string, 
			  int nFolder, int icon, LPWSTR tooltip)
{
  G2ListBar *pBar = FIND_WND(handle,G2ListBar);
  CXTPShortcutBarItem *pFolder = pBar ? pBar->GetItem(nFolder) : NULL;

  if(!pBar)
    return -1;

  switch(opcode) {
   case SHORTCUT_BAR_DESTROY:
     DESTROY_WND(handle);
     break;

   case SHORTCUT_BAR_ADD_FOLDER:
     return pBar->AddFolder(string, icon, tooltip);

   case SHORTCUT_BAR_ADD_ITEM:
     pBar->AddTextItem(string, nFolder, icon, tooltip);
     break;

//    case SHORTCUT_BAR_ADD_WINDOW_ITEM:
//      pBar->AddWindowItem(string, nFolder, pWnd);
//      break;

   case SHORTCUT_BAR_CLEAR:
     pBar->RemoveAllItems();
     break;

   case SHORTCUT_BAR_SELECT_FOLDER:
     if(pFolder)
       pBar->SelectItem(pFolder);
     break;

   case SHORTCUT_BAR_ENABLE_FOLDER:
   case SHORTCUT_BAR_DISABLE_FOLDER:
     if(pFolder)
       pFolder->SetVisible(opcode == SHORTCUT_BAR_ENABLE_FOLDER);
     break;

   case SHORTCUT_BAR_SELECT_ITEM:
     pBar->SelectItemInFolder(nFolder, icon); // icon==item number here.
     break;

   case SHORTCUT_BAR_ENABLE_ITEM:
   case SHORTCUT_BAR_DISABLE_ITEM:
//      pBar->EnableItem(nFolder, icon, opcode == SHORTCUT_BAR_ENABLE_ITEM);
//      if(nFolder == pBar->GetSelFolder())
//        pBar->Invalidate();
     break;

   case SHORTCUT_BAR_SMALL_ICONS:
     pBar->SetLargeIcons(FALSE);
     break;

   case SHORTCUT_BAR_LARGE_ICONS:
     pBar->SetLargeIcons(TRUE);
     break;
     
   case SHORTCUT_BAR_BACKGROUND_COLOR:
     pBar->SetColors((COLORREF)nFolder, pBar->m_clrText);
     break;

   case SHORTCUT_BAR_FOREGROUND_COLOR:
     pBar->SetColors(pBar->m_clrBack, (COLORREF)nFolder);
     break;

   default:
     return -1;
  }
  return 1;
}
