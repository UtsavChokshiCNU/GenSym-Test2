/* Standard Disclaimer: 
Copyright (C) 2000  Dennis Howard
This file is free software; you can redistribute it and/or
modify it without any conditions. There is no warranty,
implied or expressed, as to validity or fitness for a particular purpose.
*/


#if !defined(AFX_TREEDROPLIST_H__0F2E2150_2342_4F38_AC2F_92A6C718C28F__INCLUDED_)
#define AFX_TREEDROPLIST_H__0F2E2150_2342_4F38_AC2F_92A6C718C28F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TreeDropList.h : header file
//

#include "ComboTreeTip.h"

/////////////////////////////////////////////////////////////////////////////
// ComboTreeDropList window
class ComboTree;

class ComboTreeDropList : public CTreeCtrl
{

friend class ComboTree;

// Construction
public:
	ComboTreeDropList();

// Attributes
protected:
	enum CheckState{ NOSTATE = 0, UNCHECKED, CHECKED, CHILD_CHECKED};
	enum CheckType{ CHECK, UNCHECK, TOGGLE, REFRESH };



// Attributes
protected:
	void SetCombo (ComboTree* pCombo)
	{
		m_pCombo = pCombo;
	}

	ComboTree* GetCombo ()
	{
		return m_pCombo;
	}

	void SplitPath (const CString& strTreeBranch, CString& strRoot, CString& strRemainder);

	HTREEITEM MatchSibling (HTREEITEM hItem, CString& strMatch);

	HTREEITEM FindString (HTREEITEM hParent, CString strTreeBranch,
			 		     HTREEITEM& hPreviousMatch, CString& strRoot, CString& strRemainder );

	HTREEITEM DropListAddItem (HTREEITEM hParent, CString strTreeBranch);


	HTREEITEM AddString ( LPCTSTR lpszString);

	HTREEITEM FindString (CString strTreeBranch, HTREEITEM hParent = NULL );

	HTREEITEM SelectString( LPCTSTR lpszString, HTREEITEM hParent = NULL);

	CString GetTreePath (HTREEITEM hItem);

	CString GetCurrentTreePath ();

	TCHAR GetPathDelimiter () { return m_Delimiter; }

	void SetPathDelimiter (TCHAR Delimiter) { m_Delimiter = Delimiter; }

	void SetChildState( HTREEITEM hItem, UINT nState );

	void SetParentState(HTREEITEM hItem);


	HTREEITEM FindChildItemData(DWORD SearchData, HTREEITEM hItem = NULL) ;

	HTREEITEM FindChildItem (LPCTSTR Label, HTREEITEM hItem = NULL) ;

	HTREEITEM GetLastItem( HTREEITEM hItem ) ;

	HTREEITEM GetNextItem( HTREEITEM hItem ) ;

	HTREEITEM GetPrevItem( HTREEITEM hItem ) ;

	HTREEITEM GetLastSibling( HTREEITEM hItem ) ;

	void CollapseBranch( HTREEITEM hItem) ;

	void ExpandBranch( HTREEITEM hItem ) ;

	void CollapseAllSiblings( HTREEITEM hNode );

	BOOL SetCheck( HTREEITEM hItem, CheckType nCheck );

	BOOL IsItemChecked(HTREEITEM hItem);

	HTREEITEM GetFirstCheckedItem();

	HTREEITEM GetNextCheckedItem( HTREEITEM hItem );

	HTREEITEM GetPrevCheckedItem( HTREEITEM hItem );


protected:
	ComboTree* m_pCombo;
	TCHAR       m_Delimiter;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ComboTreeDropList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ComboTreeDropList();

	// Generated message map functions
protected:
	//{{AFX_MSG(ComboTreeDropList)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	#if defined(_MFC_VER)&&_MFC_VER>=0x0900//VS2008 MFC and more
	afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
	#else
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	#endif
	afx_msg UINT OnGetDlgCode();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	ComboTreeTip m_ToolTip;
	CImageList m_imageState;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEDROPLIST_H__0F2E2150_2342_4F38_AC2F_92A6C718C28F__INCLUDED_)
