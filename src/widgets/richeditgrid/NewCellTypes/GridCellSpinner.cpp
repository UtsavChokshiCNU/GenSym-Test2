///////////////////////////////////////////////////////////////////////////
//
// GridCellSpinner.cpp: implementation of the CGridCellSpinner class.
// Provides the implementation for a Spinner cell type of the
// grid control.
// Written by Heidi Goddard using GridCellDateTime.cpp as a prototype. 
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCtrl.h"
#include "GridCell.h"
#include "InPlaceEdit.h"
#include "dyndlgs.h"
#include "GridCellSpinner.h"

extern "C" void g2pvt_trace(char *fmt, ...);
#define PRINTF g2pvt_trace

extern "C" CONTROLITEM *g2pvt_lookup_control_by_hwnd (int controlId, HWND hwndDlg);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//
// CGridCellSpinner -- the grid cell subclass
//

IMPLEMENT_DYNCREATE(CGridCellSpinner, CGridCell)

CGridCellSpinner::CGridCellSpinner():CGridCell()
{
}

CGridCellSpinner::~CGridCellSpinner()
{
}

CSize CGridCellSpinner::GetCellExtent(CDC* pDC)
{    
  CSize sizeScroll (GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYHSCROLL));	
  CSize sizeCell (CGridCell::GetCellExtent(pDC));	
  sizeCell.cx += sizeScroll.cx;	
  sizeCell.cy = max(sizeCell.cy,sizeScroll.cy);	
  return sizeCell;
}

CWnd *CGridCellSpinner::CreateInPlaceEditor(CWnd* pParent, CRect& rect, DWORD dwEditStyle, UINT nID,
											int nRow, int nColumn, CString sInitText, 
											UINT nFirstChar)
{
  return new CInPlaceSpinner(pParent, rect, dwEditStyle, nID, nRow, nColumn, sInitText, nFirstChar);
}


//
// CInPlaceSpinner -- the editor subclass
//

BEGIN_MESSAGE_MAP(CInPlaceSpinner, CSpinnerTwng)
 ON_EN_KILLFOCUS(ID_EDIT, OnEditLostFocus)
 ON_MESSAGE(WM_END_EDIT,OnEndEditMsg)
END_MESSAGE_MAP()

CInPlaceSpinner::CInPlaceSpinner(CWnd* pParent, CRect& rect, DWORD dwEditStyle, UINT nID,
								 int nRow, int nColumn, 
								 LPCTSTR curText,
								 UINT nFirstChar)
{
  m_sInitText     = curText;
  m_nRow          = nRow;
  m_nCol          = nColumn;
  m_nLastChar     = 0; 
  
  // Force some style bits. These UDS_xxx bits used to be hard wired in CSpinnerTwng itself.
  // All the grid-view gets to specify is the editor style.
  DWORD dwStyle = WS_VISIBLE | WS_CHILD | UDS_WRAP | UDS_ARROWKEYS | UDS_NOTHOUSANDS | UDS_ALIGNRIGHT;

  if (!Create(dwStyle, dwEditStyle, rect, pParent, nID))
	return;

  DWORD dwG2Style = G2_UDS_INTEGERS; // assume integers unless the user passed decimal data
  CGridCtrl *pGrid = (CGridCtrl*)pParent;
  CGridCellSpinner *pCell = (CGridCellSpinner*) pGrid->GetCell(nRow, nColumn);
  CString strSpec;
  int index;

  // Now initialize the spinner from a combination of the current value as text
  // (in curText), and the specification of min, max, and increment, as saved in
  // the item data, as a packed string of the form "value|min|max|increment".

  strSpec = pCell->m_strSpec;

  // always use the most recently entered text as the current value
  index = strSpec.Find(_T("|"));
  if (index)
	{
	  // strip off the initial value
	  strSpec = strSpec.Right(strSpec.GetLength() - index);
	  //concatenate the most recently entered text
	  strSpec = curText + strSpec;
	}

  // FIXME: This code is duplicated in DoSpinnerCell()

  // the spinners are considered to be in in decimal or scientific notation if any of the input values
  // (min, max, increment or default) are in decimal or scientific notation.  Otherwise, we assume
  // we have integers.
  index = strSpec.FindOneOf(_T(".e")); // look for decimals
  if (-1 != index)
	dwG2Style = 0; // Houston, we have decimals

  // pass all values to the spinner
  m_pSpinButtonCtrl->set_spin(strSpec, dwG2Style, NULL);
  
  SetFocus();

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
	 case VK_SPACE:	  // Agrees with CInPlaceEdit()  Gensym -fmw, 10/4/06
	 case VK_END:    return;
	 default:        break;
	}
  GetEditCtrl()->SendMessage(WM_CHAR, nFirstChar);
}

CInPlaceSpinner::~CInPlaceSpinner()
{
}

// FIXME: What about text length?
void CInPlaceSpinner::GetWindowText(CString& rString) const
{
  m_pSpinButtonCtrl->m_pSpinEditTwng->GetWindowText(rString);
}

LRESULT CInPlaceSpinner::OnEndEditMsg(WPARAM,LPARAM)
{
  EndEdit();
  return 1;
}

void CInPlaceSpinner::EndEdit()
{
	CString str;
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
	if (IsWindow(pOwner->GetSafeHwnd())) {
		pOwner->SendMessage(WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&dispinfo);
	}

	// Close this window (PostNcDestroy will delete this)
	if (::IsWindow(m_hWnd)) {
		PostMessage(WM_CLOSE, 0, 0);
	}
}

void CInPlaceSpinner::OnEditLostFocus()
{
  CWnd *pNewWnd = GetFocus();

  if(pNewWnd && (pNewWnd->GetParent() == this))
	return;
  EndEdit();
}

BOOL CInPlaceSpinner::PreTranslateMessage(MSG* pMsg)
{
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
	   GetEditCtrl()->SetWindowText(m_sInitText); // restore original text
	   m_nLastChar = nChar;
	   GetParent()->SetFocus();
	   return TRUE;

	 case VK_TAB:
	 case VK_RETURN:
	   m_nLastChar = nChar;
	   GetParent()->SetFocus();
	   return TRUE;
	}
  }
  return CSpinnerTwng::PreTranslateMessage(pMsg);
}
