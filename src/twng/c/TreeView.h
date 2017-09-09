// -*- Mode: C++ -*-

#pragma once

// Operations
#define TREE_VIEW_DESTROY 6
#define TREE_VIEW_INSERT_ITEM 10
#define TREE_VIEW_CLEAR 11
#define TREE_VIEW_SET_INDENT 12
#define TREE_VIEW_SET_ITEM_HEIGHT 13
#define TREE_VIEW_SET_BGCOLOR 14
#define TREE_VIEW_SET_TEXT_COLOR 15
#define TREE_VIEW_SET_INSERT_MARK_COLOR 16
#define TREE_VIEW_SELECT_ITEM_BY_NAME 17
#define TREE_VIEW_ENSURE_VISIBLE 18
#define TREE_VIEW_SCROLL_TO 19
#define TREE_VIEW_SET_INSERT_MARK 20
#define TREE_VIEW_EDIT_ITEM 21
#define TREE_VIEW_EXPAND_ITEM 22
#define TREE_VIEW_COLLAPSE_ITEM 23
#define TREE_VIEW_SELECT_ITEM 24
#define TREE_VIEW_SET_ITEM_TOOLTIP 25
#define TREE_VIEW_SET_ITEM_BOLD 26
#define TREE_VIEW_SET_ITEM_LABEL 27
#define TREE_VIEW_SET_ITEM_ICONS 28
#define TREE_VIEW_SET_ITEM_CHECK 29
#define TREE_VIEW_DELETE_ITEM 30
#define TREE_VIEW_TOGGLE_ITEM 31
#define TREE_VIEW_SET_RIGHT_CLICK_SELECTS_NODE 32
#define TV_EXPAND_ALL 33
#define TV_COLLAPSE_ALL 34
#define TREE_VIEW_REDRAW 35 //added

// Events
#define TVEVENT_SELECT 1
#define TVEVENT_RCLICK 2
#define TVEVENT_KEYDOWN 3
#define TVEVENT_CLOSED 4    // Unused
#define TVEVENT_EXPANDED 5
#define TVEVENT_COLLAPSED 6
#define TVEVENT_EDITED 7    // Label edited
#define TVEVENT_LCLICK 8
#define TVEVENT_MCLICK 9

// Flags
#define TVF_CHILDREN 1
#define TVF_BOLD 2
#define TVF_EXPAND 4
#define TVF_CHECK 8
#define TVF_FIRST 16        // Used for positioning insert-node
#define TVF_AFTER 32
#define TVF_INSERT_MARK 64
#define MAX_LOADNODE_COUNT 100
#define MAX_PARTITION_COUNT 200
#include "RGTreeCtrl.h"

class G2TreeView;

//===========================================================================
// Summary:
//     CG2TreeToolTip is a CWnd derived class.
//     It is an internal class used by tree control
//===========================================================================
class CG2TreeToolTip : public CWnd
{
public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CG2TreeToolTip object
	//-----------------------------------------------------------------------
	CG2TreeToolTip();
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Activate Tooltip control.
	// Parameters:
	//     bActive - TRUE to activate.
	//     hItem   - Item which tooltip to show
	//     bValuePart - TRUE if tooltip of value part will be visible
	//-----------------------------------------------------------------------
	void Activate(BOOL bActive, HTREEITEM hItem);
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Creates Tooltip control.
	// Parameters:
	//     pParentWnd - Points to a G2TreeView object.
	//-----------------------------------------------------------------------
	void Create(G2TreeView* pParentWnd);
	
protected:
	
	//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()	
	//{{AFX_MSG(G2TreeView)
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg void OnPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	//}}AFX_CODEJOCK_PRIVATE
	
private:
	BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	
protected:
	G2TreeView* m_pTree;      // Parent window.
	CFont m_fnt;                        // Font used to display the tool tip
	
	friend class G2TreeView;
};

AFX_INLINE BOOL CG2TreeToolTip::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) {
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
typedef struct _TreeNodeItem
{
	int nParent;
	int nFlags;
	int nIcon;
	int nSelectdIcon;
	bool nExpanded;
	bool nAdded;
	LPARAM lParam;
	WCHAR szLabel[MAX_PATH];
	CArray<int> nChild;
}TreeNodeItem, *TreeNodeItemPtr;
// We need such an usage as typedef isn't compatible with MFC macros 
// (IMPLEMENT_DYNCREATE, etc.)
#define TREE_CTRL CRGTreeCtrl

class G2TreeView : public G2NativeView<TREE_CTRL>
{
public:
  CMap<int,int,HTREEITEM,HTREEITEM> m_items;    // Node handle -> HTREEITEM
  CMap<int,int,CString,CString> m_tooltips;     // Node handle -> tooltip
  BOOL m_rightClickSelectsNode;
  BOOL m_leftClickSelectsNode;
  BOOL m_deletingAllItems;
  CG2TreeToolTip       m_wndTip;             // Tooltip control.

public:
  DECLARE_DYNCREATE(G2TreeView)

  G2TreeView(int handle = 0) : G2NativeView<TREE_CTRL>(handle),
      beingDestroyed(false) {
    m_rightClickSelectsNode = TRUE;
    m_leftClickSelectsNode = FALSE;
    m_deletingAllItems = FALSE;
    m_hToolTipItem = NULL;
    m_nLoadedNodesCount = 0;
    m_nBufferedNodesCount = 0;
  }

public:
  afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnInfoTip(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnCheckAndLoadNodes(WPARAM wParam, LPARAM lParam);
public:
  virtual BOOL G2WantsKey(UINT vKey, UINT scanCode);
  virtual BOOL MouseClick(UINT msg, UINT flags, CPoint p);
  virtual BOOL KeyPress(UINT vKey, UINT scanCode);
  virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
  void SendEvent(int eventCode, HTREEITEM hItem, int g2key = 0);
  void Clear();
  void OnDestroy();
  HTREEITEM AddItem(int parent, LPWSTR label, LPARAM lParam=0,
            int flags = 0, int icon = -1, int selicon = -1);
  BOOL SetItemInfoTip(HTREEITEM hItem, LPCTSTR tip);
  HTREEITEM FindItemByName(HTREEITEM hRoot, LPCWSTR label);
  HTREEITEM FindItem(LPARAM lParam);
  HTREEITEM FindItem(LPCWSTR label);
  LRESULT OnIconChanged(WPARAM changed_icon, LPARAM iconID);
  void DoCollapseExpand(BOOL expand, HTREEITEM hItem = NULL);
  void ShowToolTip(HTREEITEM hItem, CString tip);
  void RelayToolTipEvent(UINT message);
  void InsertTreeNodesToControl(int parent, LPWSTR label, LPARAM lParam, int flags,
 	   int icon, int selicon);
  UINT GetLoadedNodesCount() { return m_nLoadedNodesCount; }
protected:
	virtual void PostNcDestroy() {G2NativeView<TREE_CTRL>::PostNcDestroy();}

protected:
  DECLARE_MESSAGE_MAP()

private:
	void BufferItem(int parent, LPWSTR label, LPARAM lParam, int flags,
	   int icon, int selicon);
  bool NeedAddToControl(LPARAM lParam);
private:
  bool beingDestroyed;
  HTREEITEM m_hToolTipItem;
  
  CArray<TreeNodeItemPtr> m_aryAllTreeNodes;
  UINT m_nLoadedNodesCount;
  UINT m_nBufferedNodesCount;
};
