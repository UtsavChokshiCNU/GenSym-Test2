// TreeView.cpp -- Subclassed TreeCtrl with G2 interface.

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "NativeView.h"
#include "TreeView.h"

/////////////////////////////////////////////////////////////////////////////
// CG2TreeToolTip

CG2TreeToolTip::CG2TreeToolTip()
{
	
}

BEGIN_MESSAGE_MAP(CG2TreeToolTip, CWnd)
//{{AFX_MSG_MAP(G2TreeView)
ON_WM_ERASEBKGND()
ON_WM_PAINT()
ON_WM_NCHITTEST_EX()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LRESULT CG2TreeToolTip::OnNcHitTest(CPoint /*point*/)
{
	return (LRESULT)HTTRANSPARENT;
}

void CG2TreeToolTip::Create(G2TreeView* pParentWnd)
{
	CWnd::CreateEx(0, AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)), 
		_T(""), WS_POPUP,0,0,0,0, pParentWnd->GetSafeHwnd(), 0);
	m_pTree = pParentWnd;
	
}

static LONG GetLongestTextExtent(CWindowDC& dc, CString& str)
{
    LONG current, maxLength = 0;
    CString line;
    for (int i = 0, n = 0; n != -1; i = n + 1) {
	n = str.Find('\n', i);
	if (n != -1)
	    line = str.Mid(i, n - i);
	else
	    line = str.Mid(i);
	if ((current = dc.GetTextExtent(line).cx) > maxLength)
	    maxLength = current;
    }
    return maxLength;
}

void CG2TreeToolTip::Activate(BOOL bActive, HTREEITEM hItem)
{
	if (bActive)
	{
		CString strText;
		GetWindowText(strText);
		CWindowDC dc(this);
		CRect rc;
		GetWindowRect(&rc);
		rc.right = rc.left + GetLongestTextExtent(dc, strText);

		MoveWindow(rc);
	}
	ShowWindow(bActive ? SW_SHOWNOACTIVATE : SW_HIDE);
}

BOOL CG2TreeToolTip::OnEraseBkgnd(CDC*)
{
	return TRUE; 
}

void CG2TreeToolTip::OnPaint()
{
	CFont cf;
	LOGFONT lf;	
	memset( &lf, 0, sizeof(LOGFONT) );
	lf.lfHeight = 15;
	strcpy((char*)lf.lfFaceName,"Arial" );
	cf.CreateFontIndirect( &lf );	
	
	CPaintDC dc(this);
	CFont* old = dc.SelectObject( &cf );
	CRect  rc;
	GetClientRect(&rc); 
	
	COLORREF clrText = GetXtremeColor(COLOR_INFOTEXT);
	dc.FillSolidRect(rc, GetXtremeColor(COLOR_INFOBK));
	dc.Draw3dRect(rc, clrText, clrText);
	
	CString strText;
	GetWindowText(strText);
	dc.SetTextColor(clrText);
	dc.SetBkMode(TRANSPARENT);

	CRect rcText(rc);
	rcText.left += 4;
	
	dc.DrawText(strText, rcText, DT_VCENTER | DT_NOPREFIX);
	dc.SelectObject( old );
	
}

/////////////////////////////////////////////////////////////////////////////
// G2TreeView

IMPLEMENT_DYNCREATE(G2TreeView, TREE_CTRL)

BEGIN_MESSAGE_MAP(G2TreeView, TREE_CTRL)
 ON_NATIVE_VIEW_MESSAGES()
 ON_MESSAGE(WM_TREECTRL_CHECKANDLOADNODES, OnCheckAndLoadNodes)
 ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
 ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
 ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteItem)
 ON_NOTIFY_REFLECT(TVN_GETINFOTIP, OnInfoTip)
 ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginLabelEdit)
 ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
END_MESSAGE_MAP()
/* WM_TREECTRL_CHECKANDLOADNODES event handler.
   Load next block of nodes if the last of X is visible.
   wParam: Visible nodes count
   lParam: Current position of VScroll

   static variable bInProcess is used to avoid reentering issue in WM_MOUSEWHEEL event.
   Windows'll generate several WM_MOUSEWHEEL events when scrolling mouse wheel,
   the event handler should be called several times. AddItem() method called PeekMessage()
   to process unhandled messages in windows queue, so other WM_MOUSEWHEEL event could be 
   processed at same time.
*/
LRESULT G2TreeView::OnCheckAndLoadNodes(WPARAM wParam, LPARAM lParam)
{
	static bool bInProcess = false;
	if (bInProcess) return 0;

	bInProcess = true;
	int nVCount = (int)wParam;
	int nVPos = (int)lParam;
	if ( nVPos+nVCount > m_nLoadedNodesCount-MAX_LOADNODE_COUNT )
	{
		int nCount = 0;
		for (UINT i=0; i<MAX_LOADNODE_COUNT; ++i)
		{
			if (i+m_nLoadedNodesCount >= (UINT)m_aryAllTreeNodes.GetSize())
				break;
			TreeNodeItemPtr pItem = m_aryAllTreeNodes[i+m_nLoadedNodesCount];
			if (pItem->nAdded == true)
				break;
			AddItem(pItem->nParent, pItem->szLabel, pItem->lParam, pItem->nFlags,
				pItem->nIcon, pItem->nSelectdIcon);	
			pItem->nAdded = true;
			++nCount;
		}
		m_nLoadedNodesCount+=nCount;
		SetFocus();
	}
	bInProcess = false;
	return 0;
}

void G2TreeView::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
  // do not process when Clear() is called
  if(m_deletingAllItems || m_leftClickSelectsNode)
	  return;

  NMTREEVIEW *ntv = (NMTREEVIEW*)pNMHDR;
  HTREEITEM hItem = ntv->itemNew.hItem;
  LPARAM lParam = ntv->itemNew.lParam;
  SendEvent(TVEVENT_SELECT, hItem);
  *pResult = 0;
}

void G2TreeView::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult)
{
  if(m_deletingAllItems) return;
  NMTREEVIEW *ntv = (NMTREEVIEW*)pNMHDR;
  LPARAM lParam = ntv->itemOld.lParam;

  m_items.RemoveKey(lParam);
  m_tooltips.RemoveKey(lParam);

  *pResult = 0;
}

void G2TreeView::OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult)
{
  NMTREEVIEW *ntv = (NMTREEVIEW*)pNMHDR;
  HTREEITEM hItem = ntv->itemNew.hItem;
  UINT lParam = hItem ? GetItemData(hItem) : -1;
  TreeNodeItemPtr pItem = m_aryAllTreeNodes[lParam-1];
  if (pItem->nExpanded == false)
  {
	for(UINT i = 0; i<(pItem->nChild).GetSize(); i++)
	{
		UINT child = pItem->nChild[i];
		TreeNodeItemPtr pItemChild = m_aryAllTreeNodes[child];
		if (pItemChild->nAdded == false)
		{
			AddItem(pItemChild->nParent, pItemChild->szLabel, pItemChild->lParam, pItemChild->nFlags,
				pItemChild->nIcon, pItemChild->nSelectdIcon);
			m_nLoadedNodesCount++;
			pItemChild->nAdded = true;
		}
		// GENSYMCID-725: g2-ui-insert-node does not work with position LAST
		// If the tree item has the child tree items that are not inserted,
		// the child tree items need to be added to the tree item.
		if (pItemChild->nChild.GetSize() !=0 && pItemChild->nFlags & TVF_CHILDREN)
		{
			UINT grandChild = pItemChild->nChild[0];
			TreeNodeItemPtr pItemGrandChild = m_aryAllTreeNodes[grandChild];
			if (pItemGrandChild->nAdded == false){
				AddItem(pItemGrandChild->nParent, pItemGrandChild->szLabel, pItemGrandChild->lParam, pItemGrandChild->nFlags,
					pItemGrandChild->nIcon, pItemGrandChild->nSelectdIcon);
				m_nLoadedNodesCount++;
				pItemGrandChild->nAdded = true;
			}
		}
	}
	pItem->nExpanded = true;
	SetFocus();
	
  }
  if(ntv->action == TVE_EXPAND || ntv->action == TVE_EXPANDPARTIAL)
    SendEvent(TVEVENT_EXPANDED, hItem);
  else
    SendEvent(TVEVENT_COLLAPSED, hItem);
  // GENSYMCID-700: TWNG TREE-VIEW: Erroneous selection events after manual expand / collapse of node
  // In this case we only expand the item but not select the node.
  m_leftClickSelectsNode = FALSE;
  *pResult = 0;
}

void G2TreeView::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
  NMTVDISPINFO *ntv = (NMTVDISPINFO*)pNMHDR;
  HTREEITEM hItem = ntv->item.hItem;
  *pResult = TRUE;			 // Return TRUE to disable editing.
}

void G2TreeView::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
  NMTVDISPINFO *ntv = (NMTVDISPINFO*)pNMHDR;
  HTREEITEM hItem = ntv->item.hItem;
//   if(ntv->item.pszText)
//     SendEvent(TVEVENT_EDITED, hItem, ntv->item.pszText);
  *pResult = 0;
}

void G2TreeView::OnInfoTip(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
  NMTVGETINFOTIP *git = (NMTVGETINFOTIP*)pNMHDR;
  HTREEITEM hItem = git->hItem;
  //{{Suzsoft Added for Gensym-452
  if (!hItem)
  {
	  m_hToolTipItem = NULL;
	  return ;
  }
  //}}
  //LPARAM lParam = git->lParam;
  int lParam = GetItemData(hItem);
  CString tip = m_tooltips[lParam];
  CRect cr, ir, r;

  if(tip.IsEmpty()) {			 // Show default tip only if label is obscured.
    GetClientRect(&cr);
    GetItemRect(hItem, &ir, TRUE);
    r.IntersectRect(cr, ir);
    if(! r.EqualRect(ir))
      tip = GetItemText(hItem);
  }

  //{{Suzsoft Modified to Show Tooltip for Gensym-452
  if (m_hToolTipItem != hItem)
  {
	  m_hToolTipItem = hItem;
	  ShowToolTip(hItem, tip);
  }
   //wcsncpy(git->pszText, tip, git->cchTextMax-1);
   //git->pszText[git->cchTextMax-1] = L'\0';
  //}}Suzsoft
}

BOOL G2TreeView::SetItemInfoTip(HTREEITEM hItem, LPCTSTR tip)
{
  int lParam = GetItemData(hItem);

  if(m_tooltips.IsEmpty()) {
    m_tooltips.InitHashTable(257);
    ModifyStyle(0, TVS_INFOTIP);	 // Delay setting infotip style.
  }
  if(tip)
    m_tooltips[lParam] = tip;	// FIXME: Copy???
  else
    m_tooltips.RemoveKey(lParam);
  return TRUE;
}

BOOL G2TreeView::MouseClick(UINT msg, UINT flags, CPoint p)
{
  UINT htflags;
  HTREEITEM hItem = HitTest(p, &htflags);
  int g2key = g2pvt_compute_gensym_mouse_keycode(msg);

  int eventCode = 0;
  switch(msg) {
   case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK: eventCode = TVEVENT_LCLICK; break;
   case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK: eventCode = TVEVENT_MCLICK; break;
   case WM_RBUTTONUP  : case WM_RBUTTONDBLCLK: eventCode = TVEVENT_RCLICK; break;
  }

  SendEvent(eventCode, hItem, g2key);
  if(m_leftClickSelectsNode && hItem && msg == WM_LBUTTONUP)
	  SendEvent(TVEVENT_SELECT, hItem);


  if (hItem && msg == WM_LBUTTONDOWN)
  {
	  m_leftClickSelectsNode = TRUE;
  }
  else
  {
	  m_leftClickSelectsNode = FALSE;
  }

  if(m_rightClickSelectsNode && hItem && msg == WM_RBUTTONUP)
    SelectItem(hItem);

  return TRUE;
}

BOOL G2TreeView::G2WantsKey(UINT vKey, UINT scanCode)
{
  BOOL tvKey = (vKey==VK_UP || vKey==VK_DOWN || vKey==VK_LEFT || vKey==VK_RIGHT ||
		vKey==VK_HOME || vKey==VK_END || vKey==VK_ADD || vKey==VK_SUBTRACT ||
		vKey==VK_MULTIPLY || vKey==VK_PRIOR || vKey==VK_NEXT || vKey==VK_BACK);
  BOOL shift = (GetKeyState(VK_SHIFT) < 0);
  BOOL ctrl = (GetKeyState(VK_CONTROL) < 0);
  BOOL alt = (GetKeyState(VK_MENU) < 0);

  if(tvKey)				       // Special treeview function keys, if shifted or alted.
    return shift | alt;

  if((0 <= vKey && vKey <= VK_HELP) ||         // All other function keys
     (VK_NUMPAD0 <= vKey && vKey <= VK_F24) ||
     (VK_ATTN <= vKey))
    return TRUE;

  return ctrl;				       // Printing chars only if control modifier.
}

BOOL G2TreeView::KeyPress(UINT vKey, UINT scanCode)
{
  UINT g2key;

  if(G2WantsKey(vKey, scanCode) &&
     (g2key = g2pvt_compute_gensym_keycode(vKey, scanCode))) {
    m_consumedKey = TRUE;
    SendEvent(TVEVENT_KEYDOWN, GetSelectedItem(), g2key);
    return FALSE;
  }
  return TRUE;
}

void G2TreeView::SendEvent(int eventCode, HTREEITEM hItem, int g2key /*= 0*/)
{
  int lParam = hItem ? GetItemData(hItem) : -1;
  CString label = hItem ? WStr(GetItemText(hItem)) : NULL;
  g2pvt_fire_control_event(GENSYM_TREE_VIEW, m_handle, lParam, g2key, m_handle, eventCode, label);
}

void G2TreeView::OnDestroy()
{
  beingDestroyed = true;
  SetRedraw(FALSE);
  Clear();
  G2NativeView<TREE_CTRL>::OnDestroy();
}

void G2TreeView::Clear()
{
  m_deletingAllItems = TRUE;
  m_items.RemoveAll();
  m_tooltips.RemoveAll();
  DeleteAllItems();
  m_deletingAllItems = FALSE;
  
  for (int i=(int)m_aryAllTreeNodes.GetSize(); i>0; i--)
	delete m_aryAllTreeNodes[i-1];
  m_aryAllTreeNodes.RemoveAll();
}

HTREEITEM G2TreeView::AddItem(int parent, LPWSTR label, LPARAM lParam,
			      int flags, int icon, int selected_icon)
{
  BOOL hasChildren = flags & TVF_CHILDREN;
  BOOL bold = flags & TVF_BOLD;
  BOOL expand = flags & TVF_EXPAND;
  BOOL check = flags & TVF_CHECK;
  BOOL first = flags & TVF_FIRST;
  BOOL after = flags & TVF_AFTER;
  BOOL firstChild = FALSE;
  HTREEITEM hItem, hParent, hInsertAfter;
  TVINSERTSTRUCT tvi;

  if(icon<0)
    icon = hasChildren ? GMS_CLOSED_FOLDER_ICON : GMS_DOCUMENT_ICON;
  if(selected_icon<0)
    selected_icon = hasChildren ? GMS_OPEN_FOLDER_ICON : GMS_DOCUMENT_ICON;

  hParent = (parent==0) ? TVI_ROOT : m_items[parent];
  hInsertAfter = first ? TVI_FIRST : TVI_LAST;
  if(after) {
    hInsertAfter = hParent;		       // "Parent" is the after item in this case.
    hParent = (hInsertAfter==TVI_ROOT) ? TVI_ROOT : GetParentItem(hInsertAfter);
  }

  firstChild = hParent != TVI_ROOT && !ItemHasChildren(hParent);

  ZeroMemory(&tvi,sizeof(tvi));
  tvi.hParent = hParent;
  tvi.hInsertAfter = hInsertAfter;
  tvi.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE;
  tvi.item.pszText = label;
  tvi.item.iImage = icon;
  tvi.item.iSelectedImage = selected_icon;
  tvi.item.lParam = lParam;
  tvi.item.state = (bold ? TVIS_BOLD : 0) | (expand ? TVIS_EXPANDED : 0);
  tvi.item.stateMask = TVIS_BOLD | TVIS_EXPANDED;
  hItem = InsertItem(&tvi);

  // process events
  MSG msg;
  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  if (beingDestroyed) return 0;

  if(check)
    SetCheck(hItem,TRUE);

  if(m_items.IsEmpty())
    m_items.InitHashTable(257);
  m_items[lParam] = hItem;

  // If we're adding the first child of parent, and parent is not expanded, then
  // we seem to need to refresh it ourselves.
  if(hParent && hParent != TVI_ROOT &&
     (GetItemState(hParent,TVIS_EXPANDED)&TVIS_EXPANDED)==0 && firstChild) {
    RECT r;
    GetItemRect(hParent, &r, FALSE);
    InvalidateRect(&r);
  }
  return hItem;
}

HTREEITEM G2TreeView::FindItemByName(HTREEITEM hRoot, LPCWSTR label)
{
  HTREEITEM hChild, hItem;

  if(hRoot == NULL) return NULL;

  if(wcscmp(GetItemText(hRoot), label) == 0)
    return hRoot;

  for(hChild = GetChildItem(hRoot); hChild; hChild = GetNextSiblingItem(hChild))
    if((hItem = FindItemByName(hChild, label)))
      return hItem;

  return NULL;
}

HTREEITEM G2TreeView::FindItem(LPARAM lParam) // By Handle
{
  HTREEITEM hItem;

  if(lParam == 0)
    return GetRootItem();

  if(m_items.Lookup(lParam,hItem))
    return hItem;

  return NULL;
}

HTREEITEM G2TreeView::FindItem(LPCWSTR label) // By Label
{
  HTREEITEM hRoot, hItem;

  for(hRoot = GetRootItem(); hRoot; hRoot = GetNextItem(hRoot,TVGN_NEXT)) {
    hItem = FindItemByName(hRoot, label);
    if(hItem) return hItem;
  }
  return NULL;
}

LRESULT G2TreeView::OnIconChanged(WPARAM changed_icon, LPARAM iconID)
{
  UINT i;
  RECT r;
  int icon, selicon;
  HTREEITEM hItem = GetFirstVisibleItem();
  int icon_index = g2pvt_icon_index(changed_icon);

  for (i=0; hItem && i<=GetVisibleCount(); i++) {
    if(GetItemImage(hItem, icon, selicon) && 
       (icon == icon_index || selicon == icon_index) &&
       GetItemRect(hItem, &r, FALSE))
      InvalidateRect(&r);
    hItem = GetNextVisibleItem(hItem);
  }
  return 0;
}

// TODO: Option to suppress notifications?
void G2TreeView::DoCollapseExpand(BOOL expand, HTREEITEM hItem)
{
  if(hItem == NULL)
    hItem = GetRootItem();

  for(; hItem; hItem=GetNextSiblingItem(hItem)) {
    if(ItemHasChildren(hItem)) {
      Expand(hItem, expand ? TVE_EXPAND : TVE_COLLAPSE);
      DoCollapseExpand(expand, GetChildItem(hItem));
    }
  }
}
void G2TreeView::InsertTreeNodesToControl(int parent, LPWSTR label, LPARAM lParam, int flags,
	   int icon, int selicon)
{
	BufferItem(parent, label, lParam, flags, icon, selicon);
	if (NeedAddToControl(lParam))
	{
		// GENSYMCID-706: TWNG TREE-VIEW: Crash closing the tree view dialog before
		//                the end of G2-UI-CREATE-TREE-VIEW or G2-UI-INSERT-NODE
		// Ensure the item add successfully before access to its attribute.
		if (AddItem(parent, label, lParam, flags, icon, selicon))
		  m_aryAllTreeNodes[lParam-1]->nAdded = true;
		m_nLoadedNodesCount++;
	}
}

void G2TreeView::BufferItem(int parent, LPWSTR label, LPARAM lParam, int flags,
							int icon, int selicon)
{
	TreeNodeItemPtr pItem = new TreeNodeItem();
	// GENSYMCID-870: Re: g2-ui-insert-node problem on collapsed nodes
	// For "insert after" mode, we need to change the parent to parent's parent!
	BOOL after = flags & TVF_AFTER;
	if (after && parent > 0) {
	    int nPParent = m_aryAllTreeNodes[parent-1]->nParent;
	    pItem->nParent = (nPParent==0) ? parent : nPParent;
	} else {
	    pItem->nParent = parent;
	}
	// GENSYMCID-956: TWNG - tree view - some node appears without contents
	// If we add a item to a "parent", the parent should have a TVF_CHILDREN flag.
	if (pItem->nParent != 0) {
	    TreeNodeItemPtr pItemParent = m_aryAllTreeNodes.GetAt(pItem->nParent - 1);
	    pItemParent->nFlags |= TVF_CHILDREN;
	}

	pItem->nFlags = flags;
	pItem->nIcon = icon;
	pItem->nSelectdIcon = selicon;
	pItem->lParam = lParam;
	pItem->nExpanded = false;
	pItem->nAdded = false;
	wcscpy_s(pItem->szLabel, MAX_PATH, label);
	if (parent > 0)
		m_aryAllTreeNodes[parent-1]->nChild.Add(lParam-1);
	if (lParam > m_aryAllTreeNodes.GetSize())
		m_aryAllTreeNodes.SetSize(lParam);
	// Delete the previous buffer tree nodes to prevent memory leaks.
	if (m_aryAllTreeNodes[lParam-1] != NULL)
	{
		delete m_aryAllTreeNodes[lParam-1];
	}
	m_aryAllTreeNodes[lParam-1] = pItem;
	m_nBufferedNodesCount++;
	InsertItem((TVINSERTSTRUCT *)NULL);
}

 bool G2TreeView::NeedAddToControl(LPARAM lParam)
{
	TreeNodeItemPtr pItem = m_aryAllTreeNodes.GetAt(lParam-1);
	if (pItem->nParent == 0 || pItem->nFlags != 0)
		return true;
	TreeNodeItemPtr pParent = m_aryAllTreeNodes.GetAt(pItem->nParent-1);
	// GENSYMCID-725: g2-ui-insert-node does not work with position LAST
	// If the parent of the tree item has expanded, the tree item need to be added the tree control.
	// And furthermore its child items need to be added to the tree control yet.
	if (pParent != NULL && (pParent->nParent == 0 || pParent->nFlags & TVF_EXPAND) || 
		m_nBufferedNodesCount <= MAX_PARTITION_COUNT)
	{
		return true;
	}
	else
	{
		TreeNodeItemPtr pParentParent = m_aryAllTreeNodes.GetAt(pParent->nParent-1);
		return (pParentParent != NULL && (pParentParent->nParent == 0 || pParentParent->nFlags !=0));
	}
}



/*
 * Lisp Interface
 */

long g2ext_create_tree_view(int handle, LPWSTR title,
			    long x, long y, long width, long height,
			    long dock, long neighbor, long min_width, long min_height)
{
  CMainFrame *pFrame = GetMainWnd();
  G2TreeView *pTV = new G2TreeView(handle);

  pTV->Create(TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_EDITLABELS,
	      WinSize(width,height), pFrame, handle);

  // Use shared native-icons imagelist.
  pTV->SetImageList(&pFrame->m_smallImageList, TVSIL_NORMAL);
  pTV->m_g2pointer = SavePtr(pTV->m_hWnd);

  pFrame->WrapWnd(pTV, handle, x, y, width, height, dock, neighbor, CSize(min_width, min_height), title);
  return pTV->m_g2pointer;
}

long g2ext_manage_tree_view(long opcode,
			    long handle,       // Treeview handle
			    long lParam,       // Node handle
			    LPWSTR string, 
			    long flags,
			    long iconHandle, long iconHandleSel,
			    long parent)       // Parent item handle (for insert)
{
  G2TreeView *pTV = FIND_WND(handle,G2TreeView);
  HTREEITEM hItem;

  if(!pTV || pTV->m_hWnd == 0) return 0;

  switch(opcode) {
   case TREE_VIEW_REDRAW:
     pTV->SetRedraw(flags);
     break;

   case TREE_VIEW_DESTROY:
     DESTROY_WND(handle);
     break;

   case TREE_VIEW_INSERT_ITEM:
     // Buffer all nodes for lazy load later
	   pTV->InsertTreeNodesToControl(parent, string, lParam, flags,
 		   g2pvt_icon_index(iconHandle),
		   g2pvt_icon_index(iconHandleSel));
    
     break;

   case TREE_VIEW_CLEAR:
     pTV->Clear();
     break;

   case TREE_VIEW_SET_INDENT:
     pTV->SetIndent(lParam);
     break;

   case TREE_VIEW_SET_ITEM_HEIGHT:
     pTV->SetItemHeight((short)lParam);
     break;

   case TREE_VIEW_SET_BGCOLOR:
     pTV->SetBkColor((COLORREF)lParam);
     break;

   case TREE_VIEW_SET_TEXT_COLOR:
     pTV->SetTextColor((COLORREF)lParam);
     break;

   case TREE_VIEW_SET_INSERT_MARK_COLOR:
     pTV->SetInsertMarkColor((COLORREF)lParam);
     break;

   case TREE_VIEW_SELECT_ITEM_BY_NAME:
     if((hItem = pTV->FindItem(string)))
       pTV->SelectItem(hItem);
     break;

   case TREE_VIEW_SET_RIGHT_CLICK_SELECTS_NODE:
     pTV->m_rightClickSelectsNode = (lParam != 0);
     break;

   default:					     // Opcodes needing hItem
     if(!(hItem = pTV->FindItem(lParam)))
       return 0;

     switch(opcode) {
      case TREE_VIEW_SELECT_ITEM:		     // By node handle (lParam)
	pTV->SelectItem(hItem);
	break;

      case TREE_VIEW_DELETE_ITEM:
	pTV->DeleteItem(hItem);
	break;

      case TREE_VIEW_ENSURE_VISIBLE:
	pTV->EnsureVisible(hItem);
	break;

      case TREE_VIEW_SCROLL_TO:
	pTV->Select(hItem, TVGN_FIRSTVISIBLE);	     // pTV->SelectSetFirstVisible(hItem);
	break;

      case TREE_VIEW_SET_INSERT_MARK:
	pTV->SetInsertMark(hItem, flags != 0);
	break;

      case TREE_VIEW_EDIT_ITEM:
	pTV->EditLabel(hItem);
	break;

      case TREE_VIEW_EXPAND_ITEM:
	pTV->Expand(hItem, TVE_EXPAND);
	break;

      case TREE_VIEW_COLLAPSE_ITEM:
	pTV->Expand(hItem, TVE_COLLAPSE);
	break;

      case TREE_VIEW_TOGGLE_ITEM:
	pTV->Expand(hItem, TVE_TOGGLE);
	break;

      case TV_EXPAND_ALL:
	pTV->DoCollapseExpand(TRUE, hItem);
	break;

      case TV_COLLAPSE_ALL:
	pTV->DoCollapseExpand(FALSE, hItem);
	break;

      case TREE_VIEW_SET_ITEM_TOOLTIP:
	pTV->SetItemInfoTip(hItem, g2pvt_to_native_linebreaks(string));
	break;

      case TREE_VIEW_SET_ITEM_BOLD:
	pTV->SetItemState(hItem, flags ? TVIS_BOLD : 0, TVIS_BOLD);
	break;

      case TREE_VIEW_SET_ITEM_LABEL:
	pTV->SetItemText(hItem, string);
	break;

      case TREE_VIEW_SET_ITEM_ICONS: { // Sets one or both icons
	int nImage, nSelectedImage;
	pTV->GetItemImage(hItem, nImage, nSelectedImage);
	if(iconHandle >= 0)
	  nImage = g2pvt_icon_index(iconHandle);
	if(iconHandleSel >= 0)
	  nSelectedImage = g2pvt_icon_index(iconHandleSel);
	pTV->SetItemImage(hItem, nImage, nSelectedImage);
      }
      break;
      
      case TREE_VIEW_SET_ITEM_CHECK:
	pTV->SetCheck(hItem, flags != 0);
	break;

      default:
	return 0;
     }
  }
  return 1;
}

//{{Suzsoft Added for Gensym-452
void G2TreeView::ShowToolTip(HTREEITEM hItem, CString tip)
{
// 	if (CXTPMouseMonitor::IsMouseHooked())
// 		return;
	
	if (!m_wndTip.GetSafeHwnd())
	{
		m_wndTip.Create(this);
	}
	
	CRect rcCaption;
	GetItemRect(hItem, &rcCaption, TRUE);
	CPoint pt;
	GetCursorPos(&pt);
	ClientToScreen(&rcCaption);
	
  	if (rcCaption.PtInRect(pt))
  	{
		CWindowDC dc(this);
		int nTextExtent = dc.GetTextExtent(tip).cx;
		
 		if (nTextExtent + 3 > rcCaption.Width())
 		{
			m_wndTip.SetWindowText(tip);
			// GENSYMCID-1017: Tree View Multiline Tooltip
			int sum = 0;
			const wchar_t *lineEnd;
			lineEnd = wcschr(tip, L'\n');
			if (lineEnd) sum ++;
			while (lineEnd)
			{
			    lineEnd ++;
			    lineEnd = wcschr(lineEnd, L'\n');
			    if (lineEnd)
				sum ++;
			}
			rcCaption.SetRect(rcCaption.left, rcCaption.top, rcCaption.right, rcCaption.bottom + sum * rcCaption.Height());
			m_wndTip.MoveWindow(rcCaption);
			m_wndTip.Activate(TRUE, hItem);
			
			TRACKMOUSEEVENT tme =
			{
				sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd, 0
			};
			_TrackMouseEvent (&tme);
		}
  	}
}

BOOL G2TreeView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	static BOOL bRelay = FALSE;
	if (m_wndTip.GetSafeHwnd() && m_wndTip.IsWindowVisible() && !bRelay)
	{
		bRelay = TRUE;
		RelayToolTipEvent(message);
		bRelay = FALSE;
	}
	
	
	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}

void G2TreeView::RelayToolTipEvent(UINT message)
{
	if (m_wndTip.GetSafeHwnd() && m_wndTip.IsWindowVisible())
	{
		CRect rc;
		m_wndTip.GetWindowRect(rc);
		
		CPoint pt;
		GetCursorPos(&pt);

		if (!rc.PtInRect(pt) || m_hToolTipItem == NULL)
		{
			m_hToolTipItem = NULL;
			m_wndTip.Activate(FALSE, 0);
		}
		
		switch (message)
		{
		case WM_MOUSEWHEEL:
			m_hToolTipItem = NULL;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_MOUSELEAVE:
			m_wndTip.Activate(FALSE, 0);
		}
	}
}
//}}suzsoft

