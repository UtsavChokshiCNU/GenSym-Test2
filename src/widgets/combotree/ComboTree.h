/* Standard Disclaimer: 
Copyright (C) 2000  Dennis Howard
This file is free software; you can redistribute it and/or
modify it without any conditions. There is no warranty,
implied or expressed, as to validity or fitness for a particular purpose.
*/

#if !defined(AFX_COMBOTREE_H__7A73B177_AC87_41F0_BAE5_734A041659EE__INCLUDED_)
#define AFX_COMBOTREE_H__7A73B177_AC87_41F0_BAE5_734A041659EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ComboTree window
#include "ComboTreeDropList.h"
#include "ComboTreeEdit.h"
#include "ComboTreeButton.h"
#include "ComboTreeHook.h"

#define NOTIFY_TREECOMBO_CHECK WM_APP + 2291
 
class ComboTree : public CWnd
{
  friend class ComboTreeDropList;
  friend class ComboTreeEdit;
  friend class ComboTreeHook;

// Construction
public:
	ComboTree();

// Attributes
public:
//Child control access functions
	ComboTreeDropList& GetTree ()           { return m_Tree; }
	ComboTreeEdit& GetEdit ()              { return m_Edit; }
	ComboTreeButton& GetDropDownButton () { return m_DropDownButton; }

//Tree specific extensions 
	CString GetTreePath (HTREEITEM hItem);
	CString GetCurrentTreePath ();
	int  SetDroppedHeight (UINT nHeight);
	int  GetDroppedHeight ();
	TCHAR GetPathDelimiter ();
	void SetPathDelimiter (TCHAR Delimiter);
	HTREEITEM FindChildItemData(DWORD SearchData, HTREEITEM hItem = NULL) ;
	HTREEITEM FindChildItem (LPCTSTR Label, HTREEITEM hItem = NULL) ;
	HTREEITEM GetLastItem( HTREEITEM hItem ) ;
	HTREEITEM GetNextItem( HTREEITEM hItem ) ;
	HTREEITEM GetPrevItem( HTREEITEM hItem ) ;
	HTREEITEM GetLastSibling( HTREEITEM hItem ) ;
	void CollapseBranch( HTREEITEM hItem) ;
	void ExpandBranch( HTREEITEM hItem ) ;
	void CollapseAllSiblings( HTREEITEM hNode );

//Checked tree extensions	
	BOOL SetHasCheckboxes (BOOL bHasCheckboxes);
	BOOL GetHasCheckboxes ();
	BOOL SetCheck( HTREEITEM hItem, BOOL bChecked = TRUE );
	BOOL IsItemChecked(HTREEITEM hItem);
	HTREEITEM GetFirstCheckedItem();
	HTREEITEM GetNextCheckedItem( HTREEITEM hItem );
	HTREEITEM GetPrevCheckedItem( HTREEITEM hItem );

//CComboBox emulation functions
	void SetWindowText (LPCTSTR Text);
	CString GetWindowText ();
    int GetLBText (HTREEITEM hItem, CString& rText);
	HTREEITEM AddString ( LPCTSTR lpszString);
	HTREEITEM FindString ( LPCTSTR lpszString, HTREEITEM hParent = NULL);
	HTREEITEM SelectString( LPCTSTR lpszString, HTREEITEM hParent = NULL);
	HTREEITEM GetCurSel ();
	int   SetItemData (HTREEITEM hItem, DWORD dwItemData);
	DWORD GetItemData (HTREEITEM hItem);
	void ShowDropDown( BOOL bShowIt = TRUE );
    void ResetContent ();
	int  SetDroppedWidth( UINT nWidth );
	int  GetDroppedWidth( );
	BOOL GetDroppedState( );
	int  DeleteString( HTREEITEM hItem );
	void GetDroppedControlRect (LPRECT pRect);
  
	void ShowTree ();
	void HideTree ();

	// Gensym modification
	CString GetControlValue();

	// Gensym modification
	void SelectOnlyLeaves (BOOL bFlag)
	{
	  m_bSelectOnlyLeaves = bFlag;
	}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ComboTree)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	public:
	BOOL SubclassDlgItem (UINT nID, CWnd* pParent);
	BOOL Create( const RECT& rect, int DroppedWidth, int DroppedHeight, CWnd* pParentWnd, UINT nID );

// Implementation
public:
	virtual ~ComboTree();

protected:

	void DisplayTree();
	BOOL CreateTree ();
	BOOL CreateButton ();
	BOOL CreateEdit ();
	void SetDroppedState (BOOL bState)
	{
		m_bDroppedState = bState;
	}

	LRESULT SendParentComboMessage ( UINT Action);
	void CalculateDroppedRect(LPRECT lpDroppedRect);
    void OnCancel ();
	void OnSelection ();
	BOOL OnKeyDropdownActive(UINT message, UINT nChar);
	BOOL OnKeyDropdownInactive(UINT message, UINT nChar);

	BOOL IsMouseOnEdit(); 
	BOOL IsMouseOnButton(); 

	BOOL IsEditHighlightOn ();

	// Gensym modification
	HTREEITEM GetDefaultSelection ();

	// Gensym modification
	HTREEITEM PreSelectString (LPCTSTR lpszString, HTREEITEM hParent = NULL);

	// Gensym modification
	void OnPreSelection();

	// Gensym modification: retrieve the current selection
	void GetSelection();

	// Gensym modification
	virtual void PostNcDestroy();

	// Gensym modification
	void MyOutputDebugString(TCHAR *pMyLabel, CString MyString);

	// Gensym modification
	BOOL m_bSelectOnlyLeaves;


	// Generated message map functions
protected:
	//{{AFX_MSG(ComboTree)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
	void OnDropdownButton ();

	DECLARE_MESSAGE_MAP()

protected:
	ComboTreeDropList m_Tree;
	ComboTreeEdit    m_Edit;
	ComboTreeButton  m_DropDownButton;
	CString       m_BeginPath;
	int           m_ComboWidth;
	int           m_ComboHeight;
	BOOL          m_bDroppedState;
	BOOL		  m_bCreateWithCheckboxes;

	ComboTreeHook m_ComboTreeHook;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOTREE_H__7A73B177_AC87_41F0_BAE5_734A041659EE__INCLUDED_)
