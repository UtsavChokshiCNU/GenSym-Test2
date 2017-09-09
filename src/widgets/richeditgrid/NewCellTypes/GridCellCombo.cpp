// GridCellCombo.cpp : implementation file
//
// MFC Grid Control - Main grid cell class
//
// Provides the implementation for a combobox cell type of the
// grid control.
//
// Written by Chris Maunder <cmaunder@mail.com>
// Copyright (c) 1998-2001. All Rights Reserved.
//
// Parts of the code contained in this file are based on the original
// CInPlaceList from http://www.codeguru.com/listview
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. 
//
// An email letting me know how you are using it would be nice as well. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// For use with CGridCtrl v2.22+
//
// History:
// 6 Aug 1998 - Added CComboEdit to subclass the edit control - code 
//              provided by Roelf Werkman <rdw@inn.nl>. Added nID to 
//              the constructor param list.
// 29 Nov 1998 - bug fix in onkeydown (Markus Irtenkauf)
// 13 Mar 2004 - GetCellExtent fixed by Yogurt
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCell.h"
#include "GridCtrl.h"

#include "GridCellCombo.h"
#include "msincls.h"			// For color array.

extern "C" void g2pvt_trace(char *fmt, ...);
#define PRINTF g2pvt_trace

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COLOR_SWATCH_SIZE 15
#define COLOR_TEXT_INDENT 5

// Gensym color names and values.
extern "C" XCOLOR XMetaColorArray[TOTAL_NUMBER_OF_COLORS];

static COLORREF LookupColor(LPCTSTR colorName)
{
  static CMapStringToPtr hash;

  if(hash.IsEmpty()) {
	for(int i=0; i<TOTAL_NUMBER_OF_COLORS; i++) {
	  CString str = XMetaColorArray[i].szColor;
	  str.MakeLower();
	  hash[str] = (void*)XMetaColorArray[i].rgbColor;
	}
  }
  CString tmp = colorName;
  tmp.MakeLower();
  return (COLORREF)hash[tmp];
}

static void DrawColorSwatch(CDC *pDC, LPCTSTR colorName, CRect& r, int xMargin, int yMargin)
{
  COLORREF color = LookupColor(colorName);
  CBrush brush(color);
  CPen pen(PS_SOLID, 1, pDC->GetTextColor());
  CBrush* pOldBrush = pDC->SelectObject(&brush);
  CPen* pOldPen = pDC->SelectObject(&pen);
  r.DeflateRect(xMargin, yMargin);
  r.right = min(r.right, r.left + COLOR_SWATCH_SIZE);
  r.bottom = min(r.bottom, r.top + COLOR_SWATCH_SIZE);
  pDC->Rectangle(r);
  pDC->SelectObject(pOldBrush);
  pDC->SelectObject(pOldPen);
}


/////////////////////////////////////////////////////////////////////////////
// CComboEdit

CComboEdit::CComboEdit()
{
  focusKilled = FALSE;
}

CComboEdit::~CComboEdit()
{
}

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CComboEdit::PreTranslateMessage(MSG* pMsg) 
{
  // Gensym change -fmw, 9/21/06
  // Do keystroke testing here instead of in OnKeyDown and OnKeyUp
  if(pMsg->message == WM_KEYDOWN) {
	CWnd* pOwner = GetOwner();
	if(pOwner)
	  switch(pMsg->wParam) {
	   case VK_PRIOR: case VK_NEXT:
	   case VK_DOWN: case VK_UP:
	   case VK_RIGHT: case VK_LEFT:
		 if(GetKeyState(VK_CONTROL) < 0 && GetDlgCtrlID() == IDC_COMBOEDIT) {
		   pOwner->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
		   return TRUE;
		 }
		 break;

	   case VK_ESCAPE:
	   case VK_TAB:
	   case VK_RETURN:
		 pOwner->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
		 return TRUE;
	  }
  }

  // Catch the Alt key so we don't choke if focus is going to an owner drawn button
  if (pMsg->message == WM_SYSCHAR)
	return TRUE;

  return CEdit::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CComboEdit, CEdit)
 ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

void CComboEdit::OnKillFocus(CWnd* pNewWnd) 
{
  if (!focusKilled) {
    CEdit::OnKillFocus(pNewWnd);

    CInPlaceList* pOwner = (CInPlaceList*) GetOwner();  // This MUST be a CInPlaceList
    if (pOwner)
        pOwner->EndEdit(TRUE);

    focusKilled = TRUE;
  }
}


/////////////////////////////////////////////////////////////////////////////
// CInPlaceList

CInPlaceList::CInPlaceList(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                           int nRow, int nColumn, 
                           COLORREF crFore, COLORREF crBack,
						   CStringArray& Items, CString sInitText, 
						   UINT nFirstChar, int nLines)
{
    m_crForeClr = crFore;
    m_crBackClr = crBack;

	m_nNumLines = nLines;
	m_sInitText = sInitText;
 	m_nRow		= nRow;
 	m_nCol      = nColumn;
 	m_nLastChar = 0; 
	m_bExitOnArrows = FALSE; //(nFirstChar != VK_LBUTTON);	// If mouse click brought us here,

	// Create the combobox
 	DWORD dwComboStyle = WS_BORDER|WS_CHILD|WS_VISIBLE|WS_VSCROLL|
 					     CBS_AUTOHSCROLL | dwStyle;
	int nHeight = rect.Height();
	rect.bottom = rect.bottom + m_nNumLines*nHeight + ::GetSystemMetrics(SM_CYHSCROLL);
	if (!Create(dwComboStyle, rect, pParent, nID)) return;

	// Add the strings
	for (int i = 0; i < Items.GetSize(); i++)
		AddString(Items[i]);

	SetFont(pParent->GetFont());
	SetItemHeight(-1, nHeight);

    int nMaxLength = GetCorrectDropWidth();
    /*
    if (nMaxLength > rect.Width())
	    rect.right = rect.left + nMaxLength;
	// Resize the edit window and the drop down window
	MoveWindow(rect);
    */

	SetDroppedWidth(nMaxLength);

	SetHorizontalExtent(0); // no horz scrolling

	// Set the initial text to m_sInitText
    if (::IsWindow(m_hWnd) && SelectString(-1, m_sInitText) == CB_ERR) 
		SetWindowText(m_sInitText);		// No text selected, so restore what was there before

    ShowDropDown();

	// This is a workaround for HQ-5398544 "GRID-VIEW: cell editing vaporizes
	// cursor".  For some reason, tabbing from an edit control which has
	// temporarily hidden the cursor into a combo box doesn't restore the
	// cursor. Tabbing into other cell types works OK. So, just for combo cells,
	// explicitly put back the mouse cursor here. -fmw, 3/16/07
	::SetCursor(::LoadCursor(NULL,IDC_ARROW));

    // Subclass the combobox edit control if style includes CBS_DROPDOWN
    if ((dwStyle & CBS_DROPDOWNLIST) != CBS_DROPDOWNLIST)
    {
	    m_edit.SubclassDlgItem(IDC_COMBOEDIT, this);
 	    SetFocus();
        switch (nFirstChar)
        {
            case VK_LBUTTON: 
            case VK_RETURN:   m_edit.SetSel((int)_tcslen(m_sInitText), -1); return;
            case VK_BACK:     m_edit.SetSel((int)_tcslen(m_sInitText), -1); break;
		    case VK_TAB:	  // Agrees with CInPlaceEdit()  Gensym -fmw, 9/20/06
            case VK_DOWN: 
            case VK_UP:   
            case VK_RIGHT:
            case VK_LEFT:  
            case VK_NEXT:  
            case VK_PRIOR: 
            case VK_HOME:  
            case VK_END:      m_edit.SetSel(0,-1); return;
            default:          m_edit.SetSel(0,-1);
        }
		SendMessage(WM_CHAR, nFirstChar);
    }
    else
 	    SetFocus();
}

CInPlaceList::~CInPlaceList()
{
}

void CInPlaceList::EndEdit(BOOL sendEvent)
{
    CString str;

  if (sendEvent) {
    if (::IsWindow(m_hWnd))
        GetWindowText(str);
 
    // Send Notification to parent
    GV_DISPINFO dispinfo;

    dispinfo.hdr.hwndFrom = GetSafeHwnd();
    dispinfo.hdr.idFrom   = GetDlgCtrlID();
    dispinfo.hdr.code     = GVN_ENDLABELEDIT;
 
    dispinfo.item.mask    = LVIF_TEXT|LVIF_PARAM;
    dispinfo.item.row     = m_nRow;
    dispinfo.item.col     = m_nCol;
    dispinfo.item.strText = str;
    dispinfo.item.lParam  = (LPARAM) m_nLastChar; 
 
    CWnd* pOwner = GetOwner();
    if (IsWindow(pOwner->GetSafeHwnd()))
        pOwner->SendMessage(WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&dispinfo );
  }

    // Close this window (PostNcDestroy will delete this)
    if (::IsWindow(m_hWnd))
        PostMessage(WM_CLOSE, 0, 0);
}

int CInPlaceList::GetCorrectDropWidth()
{
    const int nMaxWidth = 200;  // don't let the box be bigger than this

    // Reset the dropped width
    int nNumEntries = GetCount();
    int nWidth = 0;
    CString str;

    CClientDC dc(this);
    int nSave = dc.SaveDC();
    dc.SelectObject(GetFont());

    int nScrollWidth = ::GetSystemMetrics(SM_CXVSCROLL);
    for (int i = 0; i < nNumEntries; i++)
    {
        GetLBText(i, str);
        int nLength = dc.GetTextExtent(str).cx + nScrollWidth;
        nWidth = max(nWidth, nLength);
    }
    
    // Add margin space to the calculations
    nWidth += dc.GetTextExtent(_T("0")).cx;

    dc.RestoreDC(nSave);

    nWidth = min(nWidth, nMaxWidth);

	if(IsColorCombo())
	  nWidth += COLOR_SWATCH_SIZE + COLOR_TEXT_INDENT;

    return nWidth;
}

void CInPlaceList::PostNcDestroy() 
{
	CComboBox::PostNcDestroy();
	delete this;
}

BEGIN_MESSAGE_MAP(CInPlaceList, CComboBox)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
	// Added by SoftServe
	ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelEndOk)
	// End of SoftServe changes
	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()



UINT CInPlaceList::OnGetDlgCode() 
{
    return DLGC_WANTALLKEYS;
}

void CInPlaceList::OnDropdown() 
{
	SetDroppedWidth(GetCorrectDropWidth());
}

// Added by SoftServe
void CInPlaceList::OnSelEndOk() 
{
    EndEdit(FALSE);
}
// End of SoftServe changes

void CInPlaceList::OnKillFocus(CWnd* pNewWnd) 
{
	CComboBox::OnKillFocus(pNewWnd);

	if (GetSafeHwnd() == pNewWnd->GetSafeHwnd())
        return;

    // Only end editing on change of focus if we're using the CBS_DROPDOWNLIST style
    if ((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST)
        EndEdit(TRUE);
}

// If an arrow key (or associated) is pressed, then exit if
//  a) The Ctrl key was down, or
//  b) m_bExitOnArrows == TRUE
void CInPlaceList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar == VK_PRIOR || nChar == VK_NEXT ||
		 nChar == VK_DOWN  || nChar == VK_UP   ||
		 nChar == VK_RIGHT || nChar == VK_LEFT) &&
		(m_bExitOnArrows || GetKeyState(VK_CONTROL) < 0))
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();
		return;
	}

	// Moved here from OnKeyUp Gensym -fmw, 9/21/06 ---------------
	if (nChar == VK_ESCAPE) 
		SetWindowText(m_sInitText);	// restore previous text

	if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();	// This will destroy this window
		return;
	}
	// Moved here from OnKeyUp Gensym -fmw, 9/21/06 ---------------

	CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Only used if we are a color combo box.
void CInPlaceList::DrawItem(LPDRAWITEMSTRUCT pDis) 
{
  CRect r(pDis->rcItem);
  CDC dc;

  dc.Attach(pDis->hDC);

  COLORREF crOldTextColor = dc.GetTextColor();
  COLORREF crOldBkColor = dc.GetBkColor();

  if (pDis->itemState & ODS_SELECTED) {
	dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
	dc.FillSolidRect(r, ::GetSysColor(COLOR_HIGHLIGHT));
  }
  else
	dc.FillSolidRect(r, crOldBkColor);

  if(pDis->itemID != -1) {
	CString str;
	CRect rcText = r;

	GetLBText(pDis->itemID, str);

	rcText.left += 2 + COLOR_SWATCH_SIZE + COLOR_TEXT_INDENT;
	dc.DrawText(str, rcText, 0);

	CRect rcColor = r;			// TODO: Maybe center the swatch if the text is.
	rcColor.left += 2;
	DrawColorSwatch(&dc, str, rcColor, 0, 1);
  }

  dc.SetTextColor(crOldTextColor);
  dc.SetBkColor(crOldBkColor);

  dc.Detach();
}

void CInPlaceList::MeasureItem(LPMEASUREITEMSTRUCT pMis)
{
  pMis->itemHeight = ::GetSystemMetrics(SM_CYMENU)-2; // Bugegg if allow SetFont()
}

int CInPlaceList::CompareItem(LPCOMPAREITEMSTRUCT)
{
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGridCellCombo 

IMPLEMENT_DYNCREATE(CGridCellCombo, CGridCell)

CGridCellCombo::CGridCellCombo() : CGridCell()
{
    SetStyle(CBS_DROPDOWN);  // CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE, CBS_SORT
	m_colorCombo = FALSE;
}

// Create a control to do the editing
BOOL CGridCellCombo::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, UINT nID, UINT nChar)
{
  DWORD style = GetStyle();
  int nLines = 4;

  m_bEditing = TRUE;
  
  if(m_colorCombo) {
	style |= CBS_OWNERDRAWFIXED | CBS_HASSTRINGS;
	rect.bottom = max(rect.top, rect.bottom - 4); // Tweak the size
	nLines = 10;
  }

 // CInPlaceList auto-deletes itself
  m_pEditWnd = new CInPlaceList(GetGrid(), rect, style, nID, nRow, nCol, 
								GetTextClr(), GetBackClr(), m_Strings, GetText(), nChar, nLines);

  return TRUE;
}

CWnd* CGridCellCombo::GetEditWnd() const
{
	if (m_pEditWnd && (m_pEditWnd->GetStyle() & CBS_DROPDOWNLIST) != CBS_DROPDOWNLIST )
		return &(((CInPlaceList*)m_pEditWnd)->m_edit);

	return NULL;
}


CSize CGridCellCombo::GetCellExtent(CDC* pDC)
{    
    CSize sizeScroll (GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYHSCROLL));    
    CSize sizeCell (CGridCell::GetCellExtent(pDC));    
    sizeCell.cx += sizeScroll.cx;    
    sizeCell.cy = max(sizeCell.cy,sizeScroll.cy);    
    return sizeCell;
}

// Cancel the editing.
void CGridCellCombo::EndEdit()
{
    if (m_pEditWnd)
        ((CInPlaceList*)m_pEditWnd)->EndEdit(TRUE);
}

// Override draw so that when the cell is selected, a drop arrow is shown in the RHS.
BOOL CGridCellCombo::Draw(CDC* pDC, int nRow, int nCol, CRect rect,  BOOL bEraseBkgnd /*=TRUE*/)
{
#ifdef _WIN32_WCE
    return CGridCell::Draw(pDC, nRow, nCol, rect,  bEraseBkgnd);
#else
    // Cell selected?
    //if ( !IsFixed() && IsFocused())
    if (!IsEditing())			// Gensym change -fmw, 3/26/07
    {
        // Get the size of the scroll box
        CSize sizeScroll(GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYHSCROLL));

        // enough room to draw?
        if (sizeScroll.cy < rect.Width() && sizeScroll.cy < rect.Height())
        {
            // Draw control at RHS of cell
            CRect ScrollRect = rect;
            ScrollRect.left   = rect.right - sizeScroll.cx;
            ScrollRect.bottom = rect.top + sizeScroll.cy;

            // Do the draw 
			// Gensym change: draw readonly cell as inactive -fmw, 3/26/07
			if (GetGrid()->IsCellEditable(nRow, nCol))
			  pDC->DrawFrameControl(ScrollRect, DFC_SCROLL, DFCS_SCROLLDOWN);
			else
			  pDC->DrawFrameControl(ScrollRect, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_INACTIVE);

            // Adjust the remaining space in the cell
            rect.right = ScrollRect.left;
        }
    }

    CString strTempText = GetText();

    if (IsEditing())
        SetText(_T(""));

    // drop through and complete the cell drawing using the base class' method
    BOOL bResult = CGridCell::Draw(pDC, nRow, nCol, rect,  bEraseBkgnd);

	if(m_colorCombo)			// Draw color swatch where cell image would go.
	  DrawColorSwatch(pDC, strTempText, rect, GetMargin(), 1);

    if (IsEditing())
        SetText(strTempText);

	return bResult;
#endif
}

BOOL CGridCellCombo::GetTextRect(LPRECT pRect)
{
  if(m_colorCombo)
	pRect->left += COLOR_SWATCH_SIZE + COLOR_TEXT_INDENT; // If color-picker
  else
	CGridCell::GetTextRect(pRect);
  return TRUE;
}

// For setting the strings that will be displayed in the drop list
void CGridCellCombo::SetOptions(const CStringArray& ar)
{ 
    m_Strings.RemoveAll();
    for (int i = 0; i < ar.GetSize(); i++)
        m_Strings.Add(ar[i]);
}
