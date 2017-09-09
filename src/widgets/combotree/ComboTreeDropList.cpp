/* Standard Disclaimer: 
Copyright (C) 2000  Dennis Howard
This file is free software; you can redistribute it and/or
modify it without any conditions. There is no warranty,
implied or expressed, as to validity or fitness for a particular purpose.
*/

// ComboTreeDropList.cpp : implementation file
//

//Tree traversal, search and expand collapse extensions modified from
//http://www.codeguru.com/treeview/index.shtml
// Three state checkbox implementation modified from "Adding Advanced Checkbox"
//http://www.codeguru.com/treeview/advanced_checkbox.shtml

#include "stdafx.h"
#include "ComboTreeDropList.h"
#include "ComboTree.h"
// Gensym modification: we don't need "resource.h"
// #include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ComboTreeDropList

ComboTreeDropList::ComboTreeDropList()  : m_pCombo (NULL)
{
	m_Delimiter = _T('/');
}

ComboTreeDropList::~ComboTreeDropList()
{
}


BEGIN_MESSAGE_MAP(ComboTreeDropList, CTreeCtrl)
	//{{AFX_MSG_MAP(ComboTreeDropList)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ACTIVATEAPP()
	ON_WM_GETDLGCODE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ComboTreeDropList message handlers


void ComboTreeDropList::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CTreeCtrl::OnLButtonDblClk(nFlags, point);

	if (m_pCombo)
	{
		m_pCombo->SendParentComboMessage (CBN_DBLCLK);
		m_pCombo->OnSelection ();
	}
}

HTREEITEM ComboTreeDropList::AddString ( LPCTSTR lpszString)
{
	HTREEITEM hRoot = NULL;
	if (!lpszString ||  (_tcsclen (lpszString) == 0) )
	{
		return NULL;
	}

	CString strTreeBranch = lpszString;
	HTREEITEM hEndNode = DropListAddItem (hRoot, strTreeBranch);

	return hEndNode;
}


void ComboTreeDropList::SplitPath (const CString& strTreeBranch, CString& strRoot, CString& strRemainder)
{ 
    int DelimiterPos = strTreeBranch.Find (m_Delimiter);

	strRoot      = _T("");
	strRemainder = _T("");

	if (DelimiterPos == -1)
	{
		strRoot = strTreeBranch;
		return;
	}

	//Separate root substring
	if (DelimiterPos > 0)
	{
		strRoot = strTreeBranch.Mid (0, DelimiterPos);
	}

	//Separate remainder substring
	if (DelimiterPos < strTreeBranch.GetLength ())
	{
	   strRemainder = strTreeBranch.Mid (DelimiterPos + 1);
	}

}

HTREEITEM ComboTreeDropList::MatchSibling (HTREEITEM hItem, CString& strMatch)
{
	CString NodeText;
	HTREEITEM hSibling = NULL;
	if (hItem)
	{
		hSibling = hItem;
		while (hSibling)
		{
			NodeText = GetItemText (hSibling);
			if (NodeText == strMatch)
			{
				break;
			}
			else
			{
				hSibling = GetNextSiblingItem (hSibling);
			}
		}
	}
	return hSibling;
}

HTREEITEM ComboTreeDropList::SelectString( LPCTSTR lpszString, HTREEITEM hParent /*= NULL*/)
{
//	TRACE ("ComboTreeDropList::SelectString()\n");
	HTREEITEM hMatch = FindString (lpszString, hParent);
	if (hMatch)
	{
		SelectItem (hMatch);
	}
	return hMatch;
}


HTREEITEM ComboTreeDropList::FindString (CString strTreeBranch, HTREEITEM hParent /*=NULL*/ )
{
	HTREEITEM hPreviousMatch;
	HTREEITEM hMatch;
	CString strRoot;
	CString strRemainder;

	hMatch = FindString (hParent, strTreeBranch, hPreviousMatch, strRoot, strRemainder);

	if (!strRemainder.IsEmpty ())
	{
		hMatch = NULL;
	}

	return hMatch;
}

HTREEITEM ComboTreeDropList::FindString (HTREEITEM hParent, CString strTreeBranch,
								   HTREEITEM& hPreviousMatch, CString& strRoot, CString& strRemainder )
{
	HTREEITEM hItem = hParent;
	HTREEITEM hMatch = NULL;

	hPreviousMatch = hParent;


	SplitPath (strTreeBranch, strRoot, strRemainder);
	if (strRoot.IsEmpty ())
	{
		//Nothing to search for
		return NULL;
	}

	 //special case when the tree is empty
	 if (hParent == NULL)
	 {
		 hItem = GetChildItem (hParent);
	 }

	 //try to find a child item that matches the substring text
	 //at the corresponding level

	 //Match tree nodes until a node is encountered that doesn't match
	 hMatch = MatchSibling (hItem, strRoot);
	 while (hMatch && !strRemainder.IsEmpty())
	 {
 		hPreviousMatch = hMatch;
		strTreeBranch = strRemainder;
		SplitPath (strTreeBranch, strRoot, strRemainder);
		hItem = GetChildItem (hMatch);
		hMatch = MatchSibling (hItem, strRoot);
	 }

    return hMatch;
}



HTREEITEM ComboTreeDropList::DropListAddItem (HTREEITEM hParent, CString strTreeBranch)
{
 	HTREEITEM hAddedItem = NULL;
	HTREEITEM hPreviousMatch = hParent;
	HTREEITEM hMatch = NULL;

	CString strRemainder;
	CString strRoot;

	if (!m_pCombo)
	{
		return NULL;
	}

	BOOL bHasChecks = m_pCombo->GetHasCheckboxes ();

	hMatch = FindString (hParent, strTreeBranch, hPreviousMatch, strRoot, strRemainder);

	//Add nodes until the remainder is gone
	while (!strRemainder.IsEmpty())
	{
		hPreviousMatch = InsertItem (strRoot, hPreviousMatch);
		if (bHasChecks && hPreviousMatch)
		{
			SetItemState( hPreviousMatch, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
		}

		strTreeBranch = strRemainder;
		SplitPath (strTreeBranch, strRoot, strRemainder);
	}
	
	//add only if the node doesn't match an existing node
	if (!hMatch)
	{
		hAddedItem = InsertItem (strRoot, hPreviousMatch);
	}

	if (bHasChecks && hAddedItem)
	{
		SetItemState( hAddedItem, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
	}

	return hAddedItem;
}



CString ComboTreeDropList::GetTreePath (HTREEITEM hItem)
{
	CString ItemText;
	CString PathText;
	if (hItem)
	{
		PathText = GetItemText (hItem);
		HTREEITEM hParent = GetParentItem (hItem);
		while (hParent)
		{
			ItemText = GetItemText (hParent);
			PathText = ItemText + m_Delimiter + PathText;
			hParent = GetParentItem (hParent);
		}
	}
	return PathText;
}

CString ComboTreeDropList::GetCurrentTreePath ()
{
	HTREEITEM hItem = GetSelectedItem ();
	
	return GetTreePath (hItem);
}

HTREEITEM ComboTreeDropList::FindChildItemData(DWORD SearchData, HTREEITEM hItem) 
{

	
	if (GetCount () < 1)
	{
		return NULL;
	}

	
	HTREEITEM hCurrent = hItem ? hItem : GetRootItem() ;
	HTREEITEM hChild = NULL;

	DWORD ItemData;

	if ( hItem == NULL)
	{
		hChild = hCurrent;
	}
	else if ( ItemHasChildren( hCurrent ) )
	{
		hChild = GetChildItem( hCurrent );
	}

	while( hChild )
	{
		ItemData = GetItemData( hChild );
		if ( ItemData == SearchData )
		{
			return hChild;
		}
		
		hChild = GetNextSiblingItem( hChild );

	}
	return NULL;
}


HTREEITEM ComboTreeDropList::FindChildItem (LPCTSTR Label, HTREEITEM hItem ) 
{
	if (GetCount () < 1)
	{
		return NULL;
	}
	
	HTREEITEM hCurrent = hItem ? hItem : GetRootItem() ;
	HTREEITEM hChild = NULL;

	CString NodeText;

	if ( hItem == NULL)
	{
		hChild = hCurrent;
	}
	else if ( ItemHasChildren( hCurrent ) )
	{
		hChild = GetChildItem( hCurrent );
	}

	while( hChild )
	{
		NodeText = GetItemText ( hChild );
		if ( NodeText == Label )
		{
			return hChild;
		}
		
		hChild = GetNextSiblingItem( hChild );

	}
	return NULL;
}


// GetLastItem  - Gets last item in the branch
// Returns      - Last item
// hItem        - Node identifying the branch. NULL will 
//                return the last item in outine

HTREEITEM ComboTreeDropList::GetLastItem( HTREEITEM hItem ) 
{
	// Last child of the last child of the last child ...
	HTREEITEM htiNext;
	
	if( hItem == NULL ){
		// Get the last item at the top level
		htiNext = GetRootItem();
		while( htiNext ){
			hItem = htiNext;
			htiNext = GetNextSiblingItem( htiNext );
		}
	}
	
	while( ItemHasChildren( hItem ) ){
		htiNext = GetChildItem( hItem );
		while( htiNext ){
			hItem = htiNext;
			htiNext = GetNextSiblingItem( htiNext );
		}
	}
	
	return hItem;
	
}


HTREEITEM ComboTreeDropList::GetNextItem( HTREEITEM hItem ) 
{
	HTREEITEM hCurrent;
	
	if( ItemHasChildren( hItem ) )
	{
		return GetChildItem( hItem ); // return first child
	}
	else
	{
		// return next sibling item
		// Go up the tree to find a parent's sibling if needed.
		while( (hCurrent = GetNextSiblingItem( hItem )) == NULL )
		{
			if( (hItem = GetParentItem( hItem ) ) == NULL )
			{
				return NULL;
			}
		}
	}
	return hCurrent;
}


HTREEITEM ComboTreeDropList::GetPrevItem( HTREEITEM hItem ) 
{
	 HTREEITEM hCurrent;
	
	 hCurrent = GetPrevSiblingItem(hItem);
	 if( hCurrent == NULL )
	 {
		 hCurrent = GetParentItem(hItem);
	 }
	 else
	 {
		 hCurrent = GetLastItem(hCurrent);
	 }
	 return hCurrent;
}


// ExpandBranch - Expands a branch completely
// hItem - Handle of the tree item to expand
void ComboTreeDropList::ExpandBranch( HTREEITEM hItem ) 
{
	if( ItemHasChildren( hItem ) )
	{
		Expand( hItem, TVE_EXPAND );
		hItem = GetChildItem( hItem );
		do
		{
			ExpandBranch( hItem );
		}while( (hItem = GetNextSiblingItem( hItem )) != NULL );
	}
	EnsureVisible( GetSelectedItem() );
}


// CollapseBranch - Collapses a branch completely
// hItem - Handle of the tree item to collapse
void ComboTreeDropList::CollapseBranch( HTREEITEM hItem) 
{
	if( ItemHasChildren( hItem ) )
	{
		Expand( hItem, TVE_COLLAPSE );
		hItem = GetChildItem( hItem );
		do
		{
			CollapseBranch( hItem );
		} while( (hItem = GetNextSiblingItem( hItem )) != NULL );
	}
}

// GetLastSibling - return last sibling of node
// hItem - Handle of the tree item
HTREEITEM ComboTreeDropList::GetLastSibling( HTREEITEM hItem ) 
{

	ASSERT (hItem != NULL);

	HTREEITEM hLastSibling = hItem;	
	// return next sibling item
	while( (hItem = GetNextSiblingItem( hItem )) == NULL )
	{
		hLastSibling = hItem;

	}
	return hItem;
}

// CollapseAllSiblings - collapses all sibling nodes of the tree
// hItem - Handle of the tree item
void ComboTreeDropList::CollapseAllSiblings( HTREEITEM hNode )
{

	HTREEITEM hSiblingItem;
	HTREEITEM hItem = hNode;
	if( hItem)
	{
		hSiblingItem = GetNextSiblingItem (hItem);
		while (hSiblingItem != NULL)
		{
			Expand (hSiblingItem, TVE_COLLAPSE);
			hSiblingItem = GetNextSiblingItem (hSiblingItem);
		}

		hSiblingItem = GetPrevSiblingItem (hItem);
		while (hSiblingItem != NULL)
		{
			Expand (hSiblingItem, TVE_COLLAPSE);
			hSiblingItem = GetPrevSiblingItem (hSiblingItem);
		}

	}

}



// SetCheck	- Check, uncheck, toggle or refresh an item
// hItem	- Item that is to be updated
// nCheck	- CHECK, UNCHECK, TOGGLE OR REFRESH 
BOOL ComboTreeDropList::SetCheck( HTREEITEM hItem, CheckType nCheck )
{

	//can't call this tree has no checkboxes
	if (!(m_pCombo && m_pCombo->GetHasCheckboxes ()))
	{
		_ASSERTE(("Tree does not have checkboxes enabled!", FALSE));
		return FALSE;
	}

	
	if( hItem == NULL ) 
		return FALSE;

	BOOL bNotify = FALSE;

	UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;

	if( nCheck == TOGGLE )
	{
		bNotify = TRUE;
		switch( nState )
		{
		case UNCHECKED:	
			nState = CHECKED;
			break;
		case CHECKED:
		case CHILD_CHECKED:
			nState = UNCHECKED;
			break;
		}
	}
	else if( nCheck == REFRESH )
	{
		// Match child state to current state
		if (((nState == CHECKED) || (nState == UNCHECKED)) && ItemHasChildren (hItem))
		{
			SetChildState( hItem, nState );
		}
		
		//Match Parent state to current state
		if ( GetParentItem( hItem ) != NULL )
		{
			SetParentState (hItem);
		}

	}
	else if (nCheck == CHECK)
	{
		bNotify = TRUE;
		nState = CHECKED;
	}
	else if (nCheck == UNCHECK)
	{
		bNotify = TRUE;
		nState = UNCHECKED;
	}

	SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), 
					TVIS_STATEIMAGEMASK );

	if (( nState == CHECKED) || ( REFRESH && (nState == CHILD_CHECKED)))
	{	

		// Mark the child notes to match if state is checked
		if (ItemHasChildren (hItem) && (nState == CHECKED) )
		{
			SetChildState( hItem, CHECKED );
		}
		
		// Mark the parents to indicate that a child item is selected.
		// Use checkbox with red border.
		if ( GetParentItem( hItem ) != NULL )
		{
			SetParentState (hItem);
		}
	}
	else if( nState == UNCHECKED )
	{
		// Mark the child notes to match
		if (ItemHasChildren (hItem))
		{
			SetChildState( hItem, UNCHECKED );
		}

		// Maybe the parent ( ancestors ) state needs to be adjusted if
		// no more children selected.
		if ( GetParentItem( hItem ) != NULL )
		{
			SetParentState (hItem);
		}
	}

	if (m_pCombo && bNotify)
	{
		m_pCombo->SendParentComboMessage (NOTIFY_TREECOMBO_CHECK);
	}


	return TRUE;
}

// SetChildState - Sets the state of all items in a branch
// hItem - Handle of the tree item to set state
void ComboTreeDropList::SetChildState( HTREEITEM hItem, UINT nState )
{
	if( ItemHasChildren( hItem ) )
	{
		SetItemState( hItem,
			INDEXTOSTATEIMAGEMASK(nState), 
			TVIS_STATEIMAGEMASK );
		hItem = GetChildItem( hItem );
		do
		{
			SetChildState( hItem, nState );
		}while( (hItem = GetNextSiblingItem( hItem )) != NULL );
	}
	else
	{
		SetItemState( hItem,
			INDEXTOSTATEIMAGEMASK(nState), 
			TVIS_STATEIMAGEMASK );
	}
}

// Set state of higher node state to reflect new state of child node
void ComboTreeDropList::SetParentState(HTREEITEM hItem) 
{
		while( (hItem = GetParentItem( hItem )) != NULL )
		{
			BOOL bChildSelected = FALSE;
			BOOL bAllChildrenSelected = TRUE;

			HTREEITEM hChild = GetChildItem( hItem );

			while( hChild )
			{
				UINT nChildState = GetItemState( hChild, TVIS_STATEIMAGEMASK ) >> 12;
		
				if( nChildState == CHECKED || nChildState == CHILD_CHECKED )
				{
					bChildSelected = TRUE;
				}

				if (nChildState != CHECKED )
				{
					bAllChildrenSelected = FALSE;
				}
				
				hChild = CTreeCtrl::GetNextItem( hChild, TVGN_NEXT );
			}

			
			if (bAllChildrenSelected)
			{
				//All children are selected, set check to normal check
				SetItemState( hItem, INDEXTOSTATEIMAGEMASK(CHECKED), 
						TVIS_STATEIMAGEMASK );

			}
			else if ( bChildSelected ) 
			{
				//Some child nodes are selected, set state to mixed check state
				SetItemState( hItem, INDEXTOSTATEIMAGEMASK(CHILD_CHECKED), 
						TVIS_STATEIMAGEMASK );

			}
			else
			{
				SetItemState( hItem, 
						INDEXTOSTATEIMAGEMASK(UNCHECKED), 
						TVIS_STATEIMAGEMASK );
			}
		}
}

BOOL ComboTreeDropList::IsItemChecked(HTREEITEM hItem)
{
	//can't call this tree if has no checkboxes
	if (!(m_pCombo && m_pCombo->GetHasCheckboxes ()))
	{
		_ASSERTE(("Tree does not have checkboxes enabled!", FALSE));
		return FALSE;
	}

	int iImage = GetItemState( hItem, TVIS_STATEIMAGEMASK )>>12;
	return iImage == CHECKED;
}

HTREEITEM ComboTreeDropList::GetFirstCheckedItem()
{
	//can't call this tree if has no checkboxes
	if (!(m_pCombo && m_pCombo->GetHasCheckboxes ()))
	{
		_ASSERTE(("Tree does not have checkboxes enabled!", FALSE));
		return FALSE;
	}

	for ( HTREEITEM hItem = GetRootItem(); hItem!=NULL;  )
	{
		int iImage = GetItemState( hItem, TVIS_STATEIMAGEMASK )>>12;
		if ( iImage == CHECKED)
			return hItem;
		
		if( iImage != CHILD_CHECKED )
		{
			HTREEITEM hti = CTreeCtrl::GetNextItem( hItem, TVGN_NEXT );
			if( hti == NULL )
				hItem = GetNextItem( hItem );
			else 
				hItem = hti;
		}
		else
			hItem = GetNextItem( hItem );
	}

	return NULL;
}

HTREEITEM ComboTreeDropList::GetNextCheckedItem( HTREEITEM hItem )
{
	//can't call this tree if has no checkboxes
	if (!(m_pCombo && m_pCombo->GetHasCheckboxes ()))
	{
		_ASSERTE(("Tree does not have checkboxes enabled!", FALSE));
		return NULL;
	}

	hItem = GetNextItem( hItem );
	while( hItem!=NULL )
	{
		int iImage = GetItemState( hItem, TVIS_STATEIMAGEMASK )>>12;
		if ( iImage == CHECKED )
			return hItem;
		
		if( iImage != CHILD_CHECKED )
		{
			HTREEITEM hti = CTreeCtrl::GetNextItem( hItem, TVGN_NEXT );
			if( hti == NULL )
				hItem = GetNextItem( hItem );
			else 
				hItem = hti;
		}
		else
			hItem = GetNextItem( hItem );
	}

	return NULL;
}

HTREEITEM ComboTreeDropList::GetPrevCheckedItem( HTREEITEM hItem )
{
	//can't call this tree if has no checkboxes
	if (!(m_pCombo && m_pCombo->GetHasCheckboxes ()))
	{
		_ASSERTE(("Tree does not have checkboxes enabled!", FALSE));
		return NULL;
	}

	for ( hItem = GetPrevItem( hItem ); hItem!=NULL; hItem = GetPrevItem( hItem ) )
		if ( IsItemChecked(hItem) )
			return hItem;

	return NULL;
}

#if defined(_MFC_VER)&&_MFC_VER>=0x0900//VS2008 MFC and more
void ComboTreeDropList::OnActivateApp(BOOL bActive, DWORD hTask) 
#else
void ComboTreeDropList::OnActivateApp(BOOL bActive, HTASK hTask) 
#endif
{
	CTreeCtrl::OnActivateApp(bActive, hTask);
	
	if (m_pCombo && m_pCombo->GetDroppedState ())
	{
//		TRACE("ComboTreeDropList::OnActivateApp(): bActive: %d\n", bActive);
		m_pCombo->SendParentComboMessage (CBN_KILLFOCUS);
		m_pCombo->OnCancel();
	}
	
}



UINT ComboTreeDropList::OnGetDlgCode() 
{
	UINT result = CTreeCtrl::OnGetDlgCode();
	result = DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTCHARS ;
	return result;
}


int ComboTreeDropList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_pCombo)
	{
		return -1;
	}

	m_ToolTip.Init (this);


	if (m_pCombo && m_pCombo->GetHasCheckboxes ())
	{
		BOOL bCreate = m_imageState.Create( _T("COMBOTREECHECKS"), 13, 1, RGB(255,255,255) );
		if (bCreate)
		{
			SetImageList( &m_imageState, TVSIL_STATE );
		}
		else
		{
			TCHAR* errMsg = _T("Can't create tree check image list! Make sure bitmap with \"COMBOTREECHECKS\" (note quotes) was added as resource");
			MessageBox (errMsg);
			return -1;
		}
	}

	return 0;
}



void ComboTreeDropList::OnLButtonDown(UINT nFlags, CPoint point) 
{

	UINT uFlags=0;
	HTREEITEM hItem = HitTest(point,&uFlags);

	if( uFlags & TVHT_ONITEMSTATEICON )
	{
		SetCheck( hItem, TOGGLE );

		return;
	}
	else if (uFlags & TVHT_ONITEM) 
	{
		HTREEITEM hCurSelItem = GetSelectedItem ();
		if (m_pCombo && (hItem != hCurSelItem))
		{
			m_pCombo->SendParentComboMessage (CBN_SELCHANGE);
		}
	}

	CTreeCtrl::OnLButtonDown(nFlags, point);
	// Gensym modification: (hjg)
	m_pCombo->OnPreSelection();
}

void ComboTreeDropList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	HTREEITEM hCurSelItem = GetSelectedItem ();

	if( nChar == VK_SPACE )
	{
		HTREEITEM hItem = GetSelectedItem();
		SetCheck( hItem, TOGGLE );
		return;
	}

	CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);

	HTREEITEM hNewSelItem = GetSelectedItem ();
	if (m_pCombo && (hNewSelItem != hCurSelItem))
	{
		m_pCombo->SendParentComboMessage (CBN_SELCHANGE);
	}


}
