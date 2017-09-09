/* Standard Disclaimer: 
Copyright (C) 2000  Dennis Howard
This file is free software; you can redistribute it and/or
modify it without any conditions. There is no warranty,
implied or expressed, as to validity or fitness for a particular purpose.
*/

#if !defined(AFX_COMBOTREEEDIT_H__5273668B_7E0B_40C2_B902_6D246A74A217__INCLUDED_)
#define AFX_COMBOTREEEDIT_H__5273668B_7E0B_40C2_B902_6D246A74A217__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboTreeEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ComboTreeEdit window
class ComboTree;

class ComboTreeEdit : public CEdit
{
   friend class ComboTree;

// Construction
public:
	ComboTreeEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ComboTreeEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ComboTreeEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(ComboTreeEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSetfocus();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillfocus();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnChange();
	//}}AFX_MSG
	LRESULT OnIgnoreMessage (WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOTREEEDIT_H__5273668B_7E0B_40C2_B902_6D246A74A217__INCLUDED_)
