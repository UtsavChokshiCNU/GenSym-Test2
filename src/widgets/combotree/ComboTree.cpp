/* Standard Disclaimer: 
Copyright (C) 2000  Dennis Howard
This file is free software; you can redistribute it and/or
modify it without any conditions. There is no warranty,
implied or expressed, as to validity or fitness for a particular purpose.
*/

/* Gensym comment:
 *
 * Downloaded from:
 *  http://www.codeguru.com/Cpp/controls/combobox/dropdown/article.php/c1791/
 *
 * All Gensym modifications should be indicated with a comment starting with
 * "Gensym".  -jv, 1/20/06
 *
 */

// ComboTree.cpp : implementation file
//

#include "stdafx.h"
#include "ComboTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//non top level child control ids
#define IDC_COMBOTREE_BUTTON 4317         
#define IDC_COMBOTREE_EDIT   4318 
#define IDC_COMBOTREE_DROPDOWN   4319         




/////////////////////////////////////////////////////////////////////////////
// ComboTree

ComboTree::ComboTree()
{
	m_Tree.SetCombo (this);
	m_ComboWidth = 200;
	m_ComboHeight = 200;
	m_bDroppedState = FALSE;
	m_bCreateWithCheckboxes = FALSE;
	// Gensym modification:
	m_bSelectOnlyLeaves = FALSE;
}

ComboTree::~ComboTree()
{
}


BEGIN_MESSAGE_MAP(ComboTree, CWnd)
	//{{AFX_MSG_MAP(ComboTree)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED (IDC_COMBOTREE_BUTTON, OnDropdownButton )
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ComboTree message handlers

LRESULT ComboTree::SendParentComboMessage (UINT Action)
{
	// Gensym modification: if we don't have a valid hwnd, don't attempt to
	// get the parent - hjg, 1/14/2005
	if (NULL == ((CWnd *)this)->m_hWnd)
	{
	  return 0L;
	}

	CWnd* pParent = GetParent ();
	if (pParent && pParent->GetSafeHwnd ())
	{
		return pParent->SendMessage (WM_COMMAND, MAKEWPARAM( GetDlgCtrlID(), Action),(LPARAM) GetSafeHwnd());
	}

	return 0L;
}

void ComboTree::SetWindowText (LPCTSTR Text)
{
	m_Edit.SetWindowText (Text);
	Invalidate ();
}


CString ComboTree::GetWindowText ()
{
	CString Text;
	m_Edit.GetWindowText(Text);
	return Text;
}

int ComboTree::GetLBText (HTREEITEM hItem, CString& rText)
{
  rText = _T("");
  int retval = CB_ERR;
  rText = m_Tree.GetItemText (hItem);
  if (rText.GetLength () > 0)
  {
	retval = 0;
  }
  return retval;
}

TCHAR ComboTree::GetPathDelimiter ()
{
	return m_Tree.GetPathDelimiter ();
}

void ComboTree::SetPathDelimiter (TCHAR Delimiter)
{
	m_Tree.SetPathDelimiter (Delimiter);
}

HTREEITEM ComboTree::FindChildItemData(DWORD SearchData, HTREEITEM hItem)
{
	return m_Tree.FindChildItemData(SearchData, hItem);
}

HTREEITEM ComboTree::FindChildItem (LPCTSTR Label, HTREEITEM hItem)
{
	return m_Tree.FindChildItem (Label, hItem);
}


HTREEITEM ComboTree::GetLastItem( HTREEITEM hItem )
{
	return m_Tree.GetLastItem(hItem );
}

HTREEITEM ComboTree::GetNextItem( HTREEITEM hItem )
{
	return m_Tree.GetNextItem( hItem);
}

HTREEITEM ComboTree::GetPrevItem( HTREEITEM hItem ) 
{
	return m_Tree.GetPrevItem( hItem );
}

HTREEITEM ComboTree::GetLastSibling( HTREEITEM hItem )
{
	return m_Tree.GetLastSibling( hItem );
}

void ComboTree::CollapseBranch( HTREEITEM hItem)
{
	 m_Tree.CollapseBranch( hItem);
}

void ComboTree::ExpandBranch( HTREEITEM hItem )
{
	 m_Tree.ExpandBranch( hItem );
}

void ComboTree::CollapseAllSiblings( HTREEITEM hNode )
{
	m_Tree.CollapseAllSiblings( hNode );
}

BOOL ComboTree::SetCheck( HTREEITEM hItem, BOOL bChecked)
{
	if (m_Tree.IsItemChecked(hItem))
	{
		if (bChecked)
		{
			//already checked
			return m_Tree.SetCheck( hItem, ComboTreeDropList::REFRESH);
		}
		else
		{
			//uncheck
			return m_Tree.SetCheck( hItem, ComboTreeDropList::UNCHECK);
		}
	}
	else
	{
		if (bChecked)
		{
			return m_Tree.SetCheck( hItem, ComboTreeDropList::CHECK);
		}
		else
		{
			//already unchecked
			return m_Tree.SetCheck( hItem, ComboTreeDropList::REFRESH);
		}

	}
}

BOOL ComboTree::IsItemChecked(HTREEITEM hItem)
{
	return m_Tree.IsItemChecked(hItem);
}

HTREEITEM ComboTree::GetFirstCheckedItem()
{
	return m_Tree.GetFirstCheckedItem();
}

HTREEITEM ComboTree::GetNextCheckedItem( HTREEITEM hItem )
{
	return m_Tree.GetNextCheckedItem(hItem );
}

HTREEITEM ComboTree::GetPrevCheckedItem( HTREEITEM hItem )
{
	return m_Tree.GetPrevCheckedItem(hItem );
}

void ComboTree::HideTree ()
{
	SetDroppedState (FALSE);
	m_Tree.ShowWindow( SW_HIDE );

	//Tree is no longer displayed, stop message interception
	m_ComboTreeHook.UnhookParent();

	m_Edit.Invalidate ();
	m_DropDownButton.Invalidate();
	Invalidate();
}

void ComboTree::ShowTree ()
{
	//Must set focus to edit here or dropdown will still have it and act on
	//arrow key messages
		
	m_Edit.SetFocus();	
	DisplayTree ();
	SendParentComboMessage (CBN_DROPDOWN);

	//Must call this to intercept parent window messsages
	m_ComboTreeHook.HookParent();


	m_Edit.Invalidate ();
	m_DropDownButton.Invalidate();
	Invalidate();
}


void ComboTree::OnDropdownButton ()
{
	
    if (GetDroppedState())
	{
		OnSelection ();
	}
	else
	{
		ShowTree();
	}
}


void ComboTree::CalculateDroppedRect(LPRECT lpDroppedRect)
{
	_ASSERTE (lpDroppedRect);

	if (!lpDroppedRect)
	{
		return;
	}

	CRect rectCombo;
	GetWindowRect(&rectCombo);

	//adjust to either the top or bottom
	int DropTop = rectCombo.bottom;
	int ScreenHeight = GetSystemMetrics (SM_CYSCREEN);
	if ((DropTop + m_ComboHeight) > ScreenHeight)
	{
		DropTop = rectCombo.top - m_ComboHeight;
	}

	//adjust to either the right or left
	int DropLeft = rectCombo.left;
	int ScreenWidth = GetSystemMetrics (SM_CXSCREEN);
	if ((DropLeft + m_ComboWidth) > ScreenWidth)
	{
		DropLeft = rectCombo.right - m_ComboWidth;
	}

	lpDroppedRect->left  = DropLeft;
	lpDroppedRect->top   = DropTop;
	lpDroppedRect->bottom = DropTop + m_ComboHeight;
	lpDroppedRect->right  = DropLeft + m_ComboWidth;

}

void ComboTree::DisplayTree()
{
	CRect rect(0,0,200,200);

	CalculateDroppedRect (&rect);


	m_Tree.SetWindowPos (&wndTopMost, rect.left, rect.top,
		                 rect.Width (), rect.Height (), SWP_SHOWWINDOW );

	m_BeginPath = m_Tree.GetCurrentTreePath ();

	SetDroppedState (TRUE);

	
	m_Tree.PostMessage (WM_SETFOCUS);
	m_Tree.SetActiveWindow ();
	m_Tree.SetForegroundWindow();
}


BOOL ComboTree::SetHasCheckboxes (BOOL bHasCheckboxes)
{
	//can't call this tree has no checkboxes
	if (m_bCreateWithCheckboxes == bHasCheckboxes)
	{
		//already set to this value
		return TRUE;
	}

	
	if (m_Tree.GetSafeHwnd())
	{
		_ASSERTE(("Checkbox style must be set before tree is created!", FALSE));
		return FALSE;
	}

	m_bCreateWithCheckboxes = bHasCheckboxes;


	return TRUE;
}

BOOL ComboTree::GetHasCheckboxes ()
{
	return m_bCreateWithCheckboxes;
}

/* Gensym comment
 *   from Microsoft Visual Studio 8/VC/atlmfc/src/mfc/wincore.cpp:
 *   BOOL CWnd::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
 *  		LPCTSTR lpszWindowName, DWORD dwStyle,
 *  		const RECT& rect, CWnd* pParentWnd, UINT nID,
 *  		LPVOID lpParam { = NULL } )
 *   but apparently this doesn't exist with whatever configuration we
 *   get in Visual Studio 2005.  -jv, 10/01/06
 */

BOOL ComboTree::CreateTree ()
{	
	CWnd* pParent = GetParent ();
	if (!pParent && pParent->GetSafeHwnd ())
	{
		return FALSE;
	}

	/* Gensym modification: purely code reorganization/clarification */
	DWORD dwExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_TOOLWINDOW;
	LPCTSTR lpszClassName = WC_TREEVIEW;
	LPCTSTR lpszWindowName = NULL;
	DWORD dwStyle = WS_CHILD | WS_BORDER | TVS_SINGLEEXPAND | TVS_HASLINES |
	  TVS_LINESATROOT | TVS_HASBUTTONS | TVS_NOTOOLTIPS;
	CRect treeRect (0,0, m_ComboWidth, m_ComboHeight);
	//can't have a control Id with WS_POPUP style
	CWnd* pParentWnd = GetDesktopWindow ();
	UINT nID = IDC_COMBOTREE_DROPDOWN;
	LPVOID lpParam = NULL;
	#if defined(_MFC_VER)&&_MFC_VER>=0x0900//VS2008 MFC and more
	if (! m_Tree.CreateEx(dwExStyle, dwStyle, treeRect, pParentWnd, nID))
	#else
	if (! m_Tree.CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle,
			      treeRect, pParentWnd, nID, lpParam))
	#endif
	/* end Gensym modification */
	{
		return FALSE;
	}

	m_ComboTreeHook.Init(::GetParent(m_hWnd), this);	 // initialize


	return TRUE;
}


BOOL ComboTree::CreateButton ()
{	
	CRect btnRect;
	GetClientRect (&btnRect);

	int width = GetSystemMetrics (SM_CXVSCROLL);
	btnRect.left = 	btnRect.right - width;
	
     m_DropDownButton.CreateEx( 0, 
      _T("BUTTON"), NULL,
      WS_TABSTOP | BS_PUSHBUTTON | BS_NOTIFY | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
      btnRect, this, IDC_COMBOTREE_BUTTON);

	m_DropDownButton.MoveWindow (&btnRect);

	return TRUE;
}


//Requires that dropdown button be created first, to size it properly
BOOL ComboTree::CreateEdit ()
{	
	if (!m_DropDownButton.GetSafeHwnd ())
	{
		return FALSE;
	}

	CRect clientRect;
	GetClientRect (&clientRect);

	CRect btnRect;
	m_DropDownButton.GetWindowRect (&btnRect);
	ScreenToClient (&btnRect);

	CRect editRect;
	editRect.left = clientRect.left;
	editRect.top = clientRect.top;
	editRect.bottom = clientRect.bottom;
	editRect.right = btnRect.left;

	BOOL bCreate = m_Edit.Create(WS_CHILD |  WS_TABSTOP | WS_VISIBLE ,  editRect, this, IDC_COMBOTREE_EDIT);


	if (bCreate)
	{
		CWnd* pParent = GetParent ();
		CFont* pFont = pParent->GetFont ();
		m_Edit.SetFont (pFont);
	}

	return bCreate;
}


//Creates ComboTree window, used by SubclassDlgItem

BOOL ComboTree::Create( const RECT& rect, int DroppedWidth, int DroppedHeight, CWnd* pParentWnd, UINT nID )
{
	ASSERT (pParentWnd != NULL);
	if (!pParentWnd)
	{
		return FALSE;
	}

	m_ComboWidth = DroppedWidth;
	m_ComboHeight = DroppedHeight;


   CString className = AfxRegisterWndClass(   CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS,
						::LoadCursor(NULL, IDC_ARROW),
						(HBRUSH) ::GetStockObject(WHITE_BRUSH));


   BOOL bCreate =  CreateEx( WS_EX_CLIENTEDGE, // 3D  client edge 
		 className, NULL,
		 WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		 rect, pParentWnd, nID);

	_ASSERTE (bCreate);

	if (!bCreate)
	{
		return FALSE;
	}

	UpdateWindow ();

	return TRUE;
}

//Removes the original ComboBox control instead of subclassing it
BOOL ComboTree::SubclassDlgItem (UINT nID, CWnd* pParent)
{
	CComboBox* pCombo = static_cast<CComboBox*>(pParent->GetDlgItem (nID));
	if (!pCombo)
	{
		return FALSE;
	}

	CRect DroppedRect;
	// Gensym modification: comment out the following line of code;
	// for some reason this does not work on dynamic combo - hjg, 1/7/05
	// pCombo->GetDroppedControlRect (&DroppedRect);

 	CRect rect;
	pCombo->GetWindowRect (&rect);
	pParent->ScreenToClient (&rect);

	// Gensym modification:
	// because GetDroppedControlRect doesn't work - multiply height by 4 - hjg, 1/7/05
	if (!Create (rect, rect.Width(), 4*rect.Height(), pParent, nID))
	{
		return FALSE;
	}

	//Set Z Order to follow after original combo
	SetWindowPos (pCombo, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

	pCombo->DestroyWindow (); //remove original window

	return TRUE; 
}

int ComboTree::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!CreateTree())
	{
		return -1;
	}

	if (!CreateButton())
	{
		return -1;
	}

	if (!CreateEdit())
	{
		return -1;
	}

	return 0;
}


CString ComboTree::GetTreePath (HTREEITEM hItem)
{
	return m_Tree.GetTreePath (hItem);
}

CString ComboTree::GetCurrentTreePath ()
{
	return m_Tree.GetCurrentTreePath ();
}


HTREEITEM ComboTree::AddString ( LPCTSTR lpszString)
{
	return m_Tree.AddString (lpszString);
}

HTREEITEM ComboTree::FindString ( LPCTSTR lpszString, HTREEITEM hParent /*=NULL*/)
{
	return m_Tree.FindString (lpszString, hParent);
}


int ComboTree::DeleteString( HTREEITEM hItem )
{
	HTREEITEM hSelected = m_Tree.GetSelectedItem ();
	if (m_Tree.DeleteItem (hItem))
	{
		if (hItem == hSelected)
		{
			//get the new item
			hItem = m_Tree.GetSelectedItem ();
			if (hItem)
			{
				CString NodeText = m_Tree.GetItemText (hItem);
				SetWindowText (NodeText);
				SendParentComboMessage (CBN_SELCHANGE);
			}
			else
			{
				SetWindowText (_T(""));
			}
		}

		return 0;
	}
	else
	{
		return CB_ERR;
	}
}


HTREEITEM ComboTree::SelectString( LPCTSTR lpszString, HTREEITEM hParent /*=NULL*/)
{
	// Gensym comment: what string do they want?
	HTREEITEM hMatch = m_Tree.SelectString (lpszString, hParent);
	CString NodeText = m_Tree.GetItemText (hMatch);

	// begin Gensym modification
	if (NodeText.IsEmpty()) // the user gave us something bogus
	{
	  hMatch = GetDefaultSelection();
	  NodeText = m_Tree.GetTreePath(hMatch);

	  hMatch = SelectString(NodeText, hParent);
	}
	else
	{
	  MyOutputDebugString(_T("SelectString :  "), NodeText);

	  if (m_bSelectOnlyLeaves)
	  {
	    if (m_Tree.ItemHasChildren(hMatch))
	    {
	      hMatch = m_Tree.GetChildItem(hMatch);
	      NodeText = m_Tree.GetTreePath(hMatch);
	      hMatch = SelectString(NodeText,  hParent);
	    }
	  }
	}

	NodeText = m_Tree.GetItemText(hMatch);
	// end Gensym modification

	SetWindowText (NodeText);

	SendParentComboMessage (CBN_SELCHANGE);

	return hMatch;
}

HTREEITEM ComboTree::GetCurSel ()
{
	return m_Tree.GetSelectedItem ();
}

int ComboTree::SetItemData (HTREEITEM hItem, DWORD dwItemData)
{
	if (!m_Tree.SetItemData (hItem, dwItemData))
	{
		return CB_ERR;
	}
	else 
	{
		return 0;
	}
}

DWORD ComboTree::GetItemData (HTREEITEM hItem)
{
	return m_Tree.GetItemData (hItem);
}

void ComboTree::ShowDropDown( BOOL bShowIt)
{
	if (bShowIt)
	{
		if (!GetDroppedState ())
		{
			ShowTree ();
		}
	}
	else 
	{
		if (!GetDroppedState())
		{
			return; //there is no active dropdown, can't hide
		}
	
		HideTree ();
	}
}

void ComboTree::ResetContent ()
{
	m_Tree.DeleteAllItems( );
}


int ComboTree::SetDroppedWidth( UINT nWidth )
{
	int retval = 0;
	if (nWidth >= 0)
	{
		m_ComboWidth = nWidth;
		if (GetDroppedState ())
		{
			DisplayTree ();
		}
	}
	else
	{
		retval = CB_ERR;
	}
	return retval;
}

int ComboTree::GetDroppedWidth( )
{
	return m_ComboWidth;
}

int ComboTree::SetDroppedHeight (UINT nHeight)
{
	int retval = 0;
	if (nHeight >= 0)
	{
		m_ComboHeight = nHeight;
		if (GetDroppedState ())
		{
			DisplayTree ();
		}
	}
	else
	{
		retval = CB_ERR;
	}
	return retval;
}

int ComboTree::GetDroppedHeight ()
{
	return m_ComboHeight;
}

BOOL ComboTree::GetDroppedState( )
{
	return m_bDroppedState;
}

void ComboTree::GetDroppedControlRect (LPRECT pRect)
{
	_ASSERTE (pRect);
	if (pRect)
	{
		CalculateDroppedRect (pRect);
	}
}

void ComboTree::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	if (::GetFocus() != m_DropDownButton.GetSafeHwnd())
	{
		m_Edit.Invalidate ();
	}
}

BOOL ComboTree::IsMouseOnButton() 
{
	BOOL bMouseOn = FALSE;
	CPoint point;
	if (GetCursorPos (&point))
	{
		CRect rect;
		m_DropDownButton.GetWindowRect (&rect);
		if (rect.PtInRect (point))
		{
			bMouseOn = TRUE;
		}
	}
	return bMouseOn;
}

BOOL ComboTree::IsMouseOnEdit() 
{
	BOOL bMouseOn = FALSE;
	CPoint point;
	if (GetCursorPos (&point))
	{
		CRect rect;
		m_Edit.GetWindowRect (&rect);
		if (rect.PtInRect (point))
		{
			bMouseOn = TRUE;
		}
	}
	return bMouseOn;
}

BOOL ComboTree::IsEditHighlightOn () 
{
	BOOL bHighlightOn = FALSE;
	HWND hFocus = ::GetFocus ();

	if (hFocus == GetSafeHwnd () || 
		hFocus == m_Edit.GetSafeHwnd  () ||
		hFocus == m_DropDownButton.GetSafeHwnd  ())
	{
		bHighlightOn = TRUE;
	}

	return bHighlightOn;
}


void ComboTree::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	
	m_Edit.Invalidate ();	
}


BOOL ComboTree::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (HIWORD(wParam) == BN_KILLFOCUS	)
	{
		m_Edit.Invalidate ();
	}

	return CWnd::OnCommand(wParam, lParam);
}

BOOL ComboTree::OnKeyDropdownInactive(UINT message, UINT nChar) 
{
	if(GetDroppedState())
	{
		return FALSE;
	}

	if ((message == WM_SYSKEYDOWN) )
	{
		if ((nChar == VK_DOWN))
		{
			ShowTree ();
			return FALSE;
		}
	}
	else if ((message == WM_KEYDOWN) && (nChar == VK_F4))
	{
		ShowTree ();
		return FALSE;
	}
	else if ((message == WM_KEYDOWN) && (nChar == VK_TAB))
	{
		
		BOOL bShift = (GetKeyState(VK_SHIFT) < 0);
		
		CWnd* pComboParent = GetParent ();
		if (pComboParent && pComboParent->GetSafeHwnd ())
		{
			CWnd* pNext = pComboParent->GetNextDlgTabItem (this, bShift);
			if (pNext && pNext->GetSafeHwnd ())
			{
//				TRACE ("ComboTree::OnKeyDropdownInactive() -Moving focus\n");
				pNext->SetFocus ();
			}
		}
		return FALSE;
	}

	return TRUE;
}

BOOL ComboTree::OnKeyDropdownActive(UINT message, UINT nChar) 
{
	if(!GetDroppedState())
	{
		return FALSE;
	}

	if (message == WM_SYSKEYDOWN)
	{
		if ((nChar == VK_UP))
		{
			OnSelection ();
			return FALSE;
		}
	}
	else if ((message == WM_KEYDOWN) && (nChar == VK_F4))
	{
		OnSelection ();
		return FALSE;
	}
	else if (nChar == VK_RETURN)
	{
		OnSelection ();
		return FALSE;
	}
	else if (nChar == VK_ESCAPE)
	{
		OnCancel ();
		return FALSE;
	}
	else if ((message == WM_KEYDOWN) && (nChar == VK_TAB))
	{
		OnSelection ();
		
		BOOL bShift = (GetKeyState(VK_SHIFT) < 0);
		
		CWnd* pComboParent = GetParent ();
		if (pComboParent && pComboParent->GetSafeHwnd ())
		{
			CWnd* pNext = pComboParent->GetNextDlgTabItem (this, bShift);
			if (pNext && pNext->GetSafeHwnd ())
			{
//				TRACE ("ComboTree::OnKeyDropdownActive(() Moving Focus\n");
				pNext->SetFocus ();
			}
		}
		return FALSE;
	}

	return TRUE;
}

BOOL ComboTree::PreTranslateMessage(MSG* pMsg) 
{
	if(GetDroppedState())
	{

		BOOL bContinue = TRUE;
		if ((pMsg->message >= WM_KEYFIRST) && (pMsg->message <= WM_KEYLAST))
		{
			bContinue = OnKeyDropdownActive(pMsg->message, pMsg->wParam);
			if (bContinue)
			{
				bContinue = m_Tree.SendMessage( pMsg->message, pMsg->wParam, pMsg->lParam);
			}
			if (!bContinue)
			{
				return FALSE;
			}
		}
	}
	else //not dropped down
	{
		BOOL bContinue = TRUE;
		if ((pMsg->message >= WM_KEYFIRST) && (pMsg->message <= WM_KEYLAST))
		{
			bContinue = OnKeyDropdownInactive(pMsg->message, pMsg->wParam);
			if (!bContinue)
			{
				return FALSE;
			}
		}
	}


	return CWnd::PreTranslateMessage(pMsg);
}

UINT ComboTree::OnGetDlgCode() 
{
	UINT result = CWnd::OnGetDlgCode();
	result |= DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTCHARS ;
	
	return result;
}


// Gensym modification: this was an existing function, but has been
//  significantly re-worked
void ComboTree::OnSelection ()
{
  CString NodeText;
  if (m_Tree.GetSafeHwnd ())
  {
    HTREEITEM hItem = m_Tree.GetSelectedItem ();
    if (hItem)
    {
      NodeText = m_Tree.GetTreePath(hItem);
      MyOutputDebugString(_T("OnSelection :  "), NodeText);
      SelectString(NodeText, NULL);

  //    SendParentComboMessage (CBN_SELENDOK);
      // TRACE ("ComboTree::OnSelection()\n");
    }
  }

	HideTree();
}

// Gensym modification: this was an existing function, but has been
//  significantly re-worked
void ComboTree::OnCancel ()
{
  
  // making sure the tree is dropped before trying to select a string will stop
  // the assert problem.  The real question is why OnCancel is called twice, and
  // that I'm not sure of, yet.

  if (GetDroppedState())
  {
    OnSelection();
  }
	SendParentComboMessage (CBN_SELENDCANCEL);

}


// Gensym modifications follow below

void ComboTree::MyOutputDebugString(TCHAR *pMyLabel, CString MyString)
{
#ifdef HGDEBUG
   TCHAR BigBuffer[1000];
  
  _tcscpy(BigBuffer, pMyLabel);
  _tcscat(BigBuffer, MyString.GetBuffer(500));
  _tcscat(BigBuffer,_T("\001\n"));
  OutputDebugString(BigBuffer);
#endif
}


/*****************************************************************************
* HTREEITEM ComboTree::GetDefaultSelection ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: 
*
*     -----
*   Modifications:
*****************************************************************************/
HTREEITEM ComboTree::GetDefaultSelection ()
{
  CString szText;
  HTREEITEM hItem;
  HTREEITEM hChildItem;
  hItem = m_Tree.GetFirstVisibleItem();
  hChildItem = hItem;

  if (m_bSelectOnlyLeaves)
  {
    while(hChildItem)
    {
      if (m_Tree.ItemHasChildren(hChildItem))
      {
        hChildItem = m_Tree.GetChildItem(hItem);
        hItem = hChildItem;
      }
      else
        break;
    }
  }
  return(hItem);
}


/*****************************************************************************
* HTREEITEM ComboTree::PreSelectString(LPCTSTR lpszString, HTREEITEM hParent)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: 
*
*     -----
*   Modifications:
*****************************************************************************/
HTREEITEM ComboTree::PreSelectString(LPCTSTR lpszString, HTREEITEM hParent /*=NULL*/)
{
  // what string do they want?
  HTREEITEM hMatch = m_Tree.SelectString(lpszString, hParent);

  CString NodeText = m_Tree.GetItemText(hMatch);
  if (NodeText.IsEmpty()) // the user gave us something bogus
  {
    hMatch = GetDefaultSelection();
    NodeText = m_Tree.GetTreePath(hMatch);
    hMatch = PreSelectString(NodeText, hParent);
  }
  MyOutputDebugString(_T("PreSelectString :  "), NodeText);

  SetWindowText(m_Tree.GetItemText(hMatch));
  SendParentComboMessage(CBN_SELCHANGE);
  return hMatch;
}


/*****************************************************************************
* void ComboTree::OnPreSelection()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: 
*
*     -----
*   Modifications:
*****************************************************************************/
void ComboTree::OnPreSelection()
{
  CString NodeText;
  if (m_Tree.GetSafeHwnd ())
  {
    HTREEITEM hItem = m_Tree.GetSelectedItem ();
    if (hItem)
    {
      NodeText = m_Tree.GetTreePath(hItem);
      MyOutputDebugString(_T("OnPreSelection :  "), NodeText);
      PreSelectString(NodeText, NULL);
      SendParentComboMessage (CBN_SELENDOK);
      // TRACE ("ComboTree::OnPreSelection()\n");
    }
  }
 
}


/*****************************************************************************
* void ComboTree::GetSelection ()
*
*   Description: retrieve the current selection
*   Input Arguments:
*   Returns:
*   Notes: 
*
*     -----
*   Modifications:
*****************************************************************************/
void ComboTree::GetSelection ()
{
  CString NodeText;
  if (m_Tree.GetSafeHwnd ())
  {
    HTREEITEM hItem = m_Tree.GetSelectedItem ();
    if (hItem)
    {
      NodeText = m_Tree.GetTreePath(hItem);
    }
  }

}


/*****************************************************************************
* CString ComboTree::GetControlValue()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: 
*
*     -----
*   Modifications:
*****************************************************************************/
CString ComboTree::GetControlValue()
{
  // If the drop-down box is still open, select the current preselection.
  if (GetDroppedState()) GetSelection();
  return GetCurrentTreePath();
}


/*****************************************************************************
* TCHAR *g2pvt_control_value_of_combo_tree_view (HWND hwndControl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: deals with TCHARs, like the rest of this file, but really must return
*     a wide string.  If it doesn't, things will be bad.
*
*     -----
*   Modifications:
*****************************************************************************/
TCHAR *g2pvt_control_value_of_combo_tree_view (HWND hwndControl)
{
  int nCbCurSel = 0, nCbLen = 0;
  TCHAR *cbSelectedRowValue = NULL;
  ComboTree *pParent;
  CString stBuf;

  pParent = (ComboTree *) CWnd::FromHandle(hwndControl);

  stBuf = pParent->GetControlValue();

  nCbLen = stBuf.GetLength();
  cbSelectedRowValue = new TCHAR[nCbLen+1];

  if (cbSelectedRowValue == NULL)
  {
    return NULL;            // out of memory!
  }
  ZeroMemory(cbSelectedRowValue, sizeof(TCHAR) * (nCbLen + 1));
  _tcscpy(cbSelectedRowValue, stBuf.GetBuffer(nCbLen));

  return cbSelectedRowValue;
}


/*****************************************************************************
* PostNcDestroy
*
*   Description:
*   This method is called as a result of a call to DestroyWindow.
*   This is the last message received, so delete ourselves
*
*   Input Arguments: none
*   Returns: nothing
*   Notes: Cleans up memory leaks. Caller no longer has to delete this object
*
*     -----
*   Modifications:
*****************************************************************************/
void ComboTree::PostNcDestroy() 
{
	// to be implemented when code is redesigned
	//Gensym-170-HQ-5699700-TWNG GDI leak
	CWnd::PostNcDestroy();
	delete this;
	//Gensym-170-HQ-5699700-TWNG GDI leak
}
