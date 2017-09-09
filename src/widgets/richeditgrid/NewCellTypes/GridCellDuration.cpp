// GridCellDuration.cpp: implementation of the CGridCellDuration class.
//
// G2 duration control as a GridCtrl cell
//
// The code appears to have been originally copied from the downloaded
// GridCellDateTime.cpp
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCtrl.h"
#include "GridCell.h"
#include "InPlaceEdit.h"
#include "NewDuration1.h"
#include "GridCellDuration.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//
// CGridCellDuration -- the grid cell subclass
//

IMPLEMENT_DYNCREATE(CGridCellDuration, CGridCell)

CGridCellDuration::CGridCellDuration() : CGridCell()
{
}

CGridCellDuration::CGridCellDuration(DWORD dwStyle) : CGridCell()
{
  Init(dwStyle| DTS_TIMEFORMAT | DTS_RIGHTALIGN);
}

CGridCellDuration::~CGridCellDuration()
{
}

CSize CGridCellDuration::GetCellExtent(CDC* pDC)
{    
    CSize sizeScroll (GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYHSCROLL));	
    CSize sizeCell (CGridCell::GetCellExtent(pDC));	
    sizeCell.cx += sizeScroll.cx;	
    sizeCell.cy = max(sizeCell.cy,sizeScroll.cy);	
    return sizeCell;
}

void CGridCellDuration::Init(DWORD dwStyle)
{
  m_dwStyle = dwStyle;
  // format here for DurationV2.
  SetFormat(DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS);
}

CWnd *CGridCellDuration::CreateInPlaceEditor(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
											 int nRow, int nColumn, CString sInitText, 
											 UINT nFirstChar)
{
  return new CInPlaceDuration(pParent, rect, dwStyle, nID, nRow, nColumn, sInitText, nFirstChar);
}


//
// CInPlaceDuration -- the in-place editor subclass
//

BEGIN_MESSAGE_MAP(CInPlaceDuration, CNewDuration)
 ON_EN_KILLFOCUS(ID_EDIT, OnEditLostFocus)
 ON_EN_KILLFOCUS(ID_EDIT2, OnEditLostFocus)
 ON_NOTIFY(NM_KILLFOCUS, ID_EDIT3, OnDateTimeLostFocus)
 ON_MESSAGE(WM_END_EDIT,OnEndEditMsg)
END_MESSAGE_MAP()

CInPlaceDuration::CInPlaceDuration(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
								   int nRow, int nColumn, 
								   LPCTSTR pText,
								   UINT nFirstChar)
{
  m_nRow          = nRow;
  m_nCol          = nColumn;
  m_nLastChar     = 0; 
  m_sInitText     = pText;

  dwStyle |= WS_BORDER | WS_VISIBLE | WS_CHILD;
  
  if (!Create(dwStyle, rect, pParent, nID))
	return;
  
  // Turn off this bit since our parent isn't the dialog. In fact, leaving the
  // bit on causes an infinite loop when clicking away from the duration
  // control.
  ModifyStyleEx(WS_EX_CONTROLPARENT, 0);

  SetCurrentDurationValue(pText); // set the initial duration value
  SetFont(pParent->GetFont());

  if(nFirstChar == VK_TAB && (GetKeyState(VK_SHIFT)<0))
	pDateTime->SetFocus();
  else
	pEdit->SetFocus();

  switch (nFirstChar) 
	{
	 case VK_LBUTTON: 
	 case VK_RETURN: return;
	 case VK_BACK:   break;
	 case VK_TAB:	  // Agrees with CInPlaceEdit()  Gensym -fmw, 9/20/06
	 case VK_DOWN: 
	 case VK_UP:   
	 case VK_RIGHT:
	 case VK_LEFT:  
	 case VK_NEXT:  
	 case VK_PRIOR: 
	 case VK_HOME:  
	 case VK_SPACE:
	 case VK_END:    return;
	 default:        break;
	}

  if(GetFocus() == pEdit)
	pEdit->SendMessage(WM_CHAR, nFirstChar);
}

CInPlaceDuration::~CInPlaceDuration()
{
}

LRESULT CInPlaceDuration::OnEndEditMsg(WPARAM,LPARAM)
{
  EndEdit();
  return 1;
}

void CInPlaceDuration::EndEdit()
{
  CString str;
  if (::IsWindow(m_hWnd)) 
	ReComputeWindowText(str);

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
	pOwner->SendMessage(WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&dispinfo);

  // Close this window (PostNcDestroy will delete this)
  if (::IsWindow(m_hWnd))
	PostMessage(WM_CLOSE, 0, 0);
}

void CInPlaceDuration::OnEditLostFocus()
{
  CWnd *pNewWnd = GetFocus();
  if(pNewWnd && (pNewWnd->GetParent() == this))
	return;
  EndEdit();
}

void CInPlaceDuration::OnDateTimeLostFocus(NMHDR* pNMHDR, LRESULT* pResult)
{
  CWnd *pNewWnd = GetFocus();
  if(pNewWnd && (pNewWnd->GetParent() == this))
	return;
  EndEdit();
}

// Return the next sibling which is a tab stop, or NULL if none.
CWnd *g2pvt_next_tab_stop(CWnd *pWnd, BOOL backwards)
{
  UINT flags = backwards ? GW_HWNDPREV : GW_HWNDNEXT;

  while(pWnd && (pWnd = pWnd->GetNextWindow(flags)) && (pWnd->GetStyle() & WS_TABSTOP) == 0)
	;

  return pWnd;
}

BOOL CInPlaceDuration::PreTranslateMessage(MSG* pMsg)
{
  CWnd *pWndNext;
  if(pMsg->message == WM_KEYDOWN) {
	UINT nChar = pMsg->wParam;
	switch(pMsg->wParam) {
	 case VK_PRIOR: case VK_NEXT:
	 case VK_DOWN:  case VK_UP:
	 case VK_RIGHT: case VK_LEFT:
	   if(GetKeyState(VK_CONTROL) < 0) {
		 m_nLastChar = nChar;
		 GetParent()->SetFocus();		 
		 return TRUE;
	   }
	   break;

	 case VK_ESCAPE:
	   SetCurrentDurationValue(m_sInitText);  // restore original text
	   m_nLastChar = nChar;
	   GetParent()->SetFocus();
	   return TRUE;

	 case VK_TAB:				// Navigate amongst children
	   pWndNext = g2pvt_next_tab_stop(GetFocus(), GetKeyState(VK_SHIFT) < 0);
	   if(pWndNext) {
		 pWndNext->SetFocus();
	   } else {
		 m_nLastChar = nChar;
		 GetParent()->SetFocus();
	   }
	   return TRUE;

	 case VK_RETURN:
	   m_nLastChar = nChar;
	   GetParent()->SetFocus();
	   return TRUE;
	}
  }
  return CNewDuration::PreTranslateMessage(pMsg);
}
