/* Standard Disclaimer: 
Copyright (C) 2000  Dennis Howard
This file is free software; you can redistribute it and/or
modify it without any conditions. There is no warranty,
implied or expressed, as to validity or fitness for a particular purpose.
*/

// ComboTreeEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ComboTreeEdit.h"
#include "ComboTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ComboTreeEdit

ComboTreeEdit::ComboTreeEdit()
{
}

ComboTreeEdit::~ComboTreeEdit()
{
}


BEGIN_MESSAGE_MAP(ComboTreeEdit, CEdit)
	//{{AFX_MSG_MAP(ComboTreeEdit)
	ON_WM_CHAR()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEACTIVATE()
	ON_WM_ACTIVATE()
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_GETDLGCODE()
	ON_WM_KILLFOCUS()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_PASTE, OnIgnoreMessage )
	ON_MESSAGE (WM_CUT, OnIgnoreMessage)
	ON_MESSAGE (WM_CLEAR, OnIgnoreMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ComboTreeEdit message handlers

void ComboTreeEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	UNREFERENCED_PARAMETER (nChar);
	UNREFERENCED_PARAMETER (nRepCnt);
	UNREFERENCED_PARAMETER (nFlags);

	//Customize this to do lookups, etc.
	return;	//make control read only
}

LRESULT ComboTreeEdit::OnIgnoreMessage (WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER (wParam);
	UNREFERENCED_PARAMETER (lParam);
	// block cut, paste and clear messages
	return 0L;
}


void ComboTreeEdit::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	UNREFERENCED_PARAMETER (pWnd);
	UNREFERENCED_PARAMETER (point);
	//no context menu	
}

void ComboTreeEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER (point);
	UNREFERENCED_PARAMETER (nFlags);

	ComboTree* pParent = static_cast<ComboTree*>(GetParent ());
	_ASSERTE (pParent);
	if (pParent)
	{
		pParent->OnSelection();
	}
	
}

void ComboTreeEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	COLORREF TextColor;
	COLORREF BkColor;

	BOOL bDrawHighlight = FALSE;


	//Draw text matching the style of a droplist ComboBox
	ComboTree* pParent = static_cast<ComboTree*>(GetParent ());
	_ASSERTE (pParent);
	if (pParent && (pParent->IsEditHighlightOn () == TRUE))
	{
		bDrawHighlight = TRUE;
	}

	if (bDrawHighlight)
	{
		TextColor = GetSysColor (COLOR_HIGHLIGHTTEXT);
		BkColor = GetSysColor (COLOR_HIGHLIGHT);
	}
	else
	{
		TextColor = GetSysColor (COLOR_WINDOWTEXT);
		BkColor = GetSysColor (COLOR_WINDOW);
	}

	CString Text;
	GetWindowText (Text);

	CRect rect;
	GetClientRect (&rect);

	CBrush BkBrush (BkColor);

	dc.FillRect (&rect, &BkBrush);

	//dashed focus line if this or the dropdown button has the focus
	if (bDrawHighlight)
	{
		dc.DrawFocusRect (&rect);
	}

	int xBorder = GetSystemMetrics (SM_CXEDGE);
	rect.left += xBorder;

	CFont* pFont = GetFont ();
	CFont* pOldFont = dc.SelectObject (pFont);
	COLORREF oldTextColor = dc.SetTextColor (TextColor);
	COLORREF oldBkColor = dc.SetBkColor (BkColor);

	dc.DrawText (Text, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	dc.SelectObject (pOldFont);
	dc.SetTextColor (oldTextColor);
	dc.SetBkColor (oldBkColor);


}

int ComboTreeEdit::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	UNREFERENCED_PARAMETER (pDesktopWnd);
	UNREFERENCED_PARAMETER (nHitTest);
	UNREFERENCED_PARAMETER (message);


	return MA_ACTIVATE;   
}

void ComboTreeEdit::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CEdit::OnActivate(nState, pWndOther, bMinimized);
	
	Invalidate ();	
}

void ComboTreeEdit::OnSetfocus() 
{
	HideCaret ();  //don't show blinking caret
	Invalidate ();	
}

void ComboTreeEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER (nFlags);
	UNREFERENCED_PARAMETER (point);
	//disregard text selection using the mouse
}

void ComboTreeEdit::OnKillfocus() 
{
	//restore caret
	ShowCaret ();
	Invalidate ();	
}

void ComboTreeEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER (nFlags);
	UNREFERENCED_PARAMETER (point);
	//disregard text selection using a double click
}

UINT ComboTreeEdit::OnGetDlgCode() 
{
	//must catch escape and other keys so that active tree can get them
	UINT result = CEdit::OnGetDlgCode();
	result |= DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTCHARS ;
	return result;
}

void ComboTreeEdit::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
   static CString PreviousText;
   CString NodeText;
   ComboTree* pParent = static_cast<ComboTree*>(GetParent ());
   _ASSERTE (pParent);
   if (pParent->GetSafeHwnd ())
   {
     HTREEITEM hItem = pParent->m_Tree.GetSelectedItem ();
     if (hItem)
     {
       NodeText = pParent->GetTreePath(hItem);
	   if (PreviousText == NodeText) // send this message only if the node has changed
		   return;
       pParent->SendParentComboMessage (CBN_EDITCHANGE);
	   PreviousText = NodeText;
     
     }
   }
	
}
