///////////////////////////////////////////////////////////////////////////
//
// CGridCellFormattedDate.cpp: implementation of the CGridCellFormattedDate class.
//
// Provides the implementation for a formatted date picker cell type of the
// grid control.
//
// Written by Heidi Goddard
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCtrl.h"
#include "GridCell.h"
#include "GridCellFormattedDate.h"
#include "dyndlgs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CGridCellFormattedDate

IMPLEMENT_DYNCREATE(CGridCellFormattedDate, CGridCell)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCellFormattedDate::CGridCellFormattedDate() : CGridCell()
{
	m_dwStyle = 0;
	m_cTime   = CTime::GetCurrentTime();
}

CGridCellFormattedDate::~CGridCellFormattedDate()
{
}
// hjg Gensym addition
//G2_DTS_US_FORMAT       0x0000L // mm/dd/yyyy  - default
//G2_DTS_EU_FORMAT       0x0001L // dd/mm/yyyy
//G2_DTS_GOV_FORMAT      0x0002L // yyyy/mm/dd

void CGridCellFormattedDate::SetFormattedDate(CTime time, DWORD dwFormat)
{
  m_dwTimeFormat = dwFormat; 
  m_cTime = time;
  if (G2_DTS_EU_FORMAT == dwFormat) 
	{
		SetText(m_cTime.Format(("%d/%m/%Y")));

	}
	else if (G2_DTS_GOV_FORMAT == dwFormat) 
	{
		SetText(m_cTime.Format(("%Y/%m/%d")));

	}

	else 
	{

		SetText(m_cTime.Format(("%m/%d/%Y")));
	}
}


CSize CGridCellFormattedDate::GetCellExtent(CDC* pDC)
{    
    CSize sizeScroll (GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYHSCROLL));	
    CSize sizeCell (CGridCell::GetCellExtent(pDC));	
    sizeCell.cx += sizeScroll.cx;	
    sizeCell.cy = max(sizeCell.cy,sizeScroll.cy);	
    return sizeCell;
}

BOOL CGridCellFormattedDate::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, 
							 UINT nID, UINT nChar)
{
	m_bEditing = TRUE;

	// CInPlaceFormattedDate auto-deletes itself
	m_pEditWnd = new CInPlaceFormattedDate(GetGrid(), rect,
		m_dwStyle|DTS_UPDOWN, nID, nRow, nCol, 
		GetTextClr(), GetBackClr(), GetTime(), m_dwTimeFormat, nChar);
	return TRUE;
}

CWnd* CGridCellFormattedDate::GetEditWnd() const
{
	return m_pEditWnd;
}

void CGridCellFormattedDate::EndEdit()
{
	if (m_pEditWnd) ((CInPlaceFormattedDate*)m_pEditWnd)->EndEdit();
}


/////////////////////////////////////////////////////////////////////////////
// CInPlaceFormattedDate

CInPlaceFormattedDate::CInPlaceFormattedDate(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
								   int nRow, int nColumn, 
								   COLORREF crFore, COLORREF crBack,
								   CTime* pcTime,
								   DWORD dwDateTimeFormat,
								   UINT nFirstChar)
{
	m_crForeClr     = crFore;
	m_crBackClr     = crBack;
	m_nRow          = nRow;
	m_nCol          = nColumn;
	m_nLastChar     = 0; 
	m_bExitOnArrows = FALSE;
	m_pcTime        = pcTime;
    
	// DWORD dwStl = WS_BORDER|WS_VISIBLE|WS_CHILD|dwStyle;

	// WS_BORDER was forcing it mostly underneath
	DWORD dwStl = WS_VISIBLE|WS_CHILD|dwStyle;

	if (!Create(dwStl, rect, pParent, nID)) {
		return;
	}

	SetTime(m_pcTime);
	SetDateFormat(dwStyle, dwDateTimeFormat);

	SetFont(pParent->GetFont());
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
		case VK_END:    return;
		default:        break;
	}
	SendMessage(WM_CHAR, nFirstChar);
}

CInPlaceFormattedDate::~CInPlaceFormattedDate()
{
}

void CInPlaceFormattedDate::SetDateFormat(DWORD dwStyle, DWORD dwTimeFormat)
{
	// check if we have one of our new formats first
    if (G2_DTS_EU_FORMAT == dwTimeFormat) 
	{
		CDateTimeCtrl::SetFormat(_T("dd'/'MM'/'yyyy"));

	}
	else if (G2_DTS_GOV_FORMAT == dwTimeFormat) 
	{
		CDateTimeCtrl::SetFormat(_T("yyyy'/'MM'/'dd"));

	}
	else 
	{
		CDateTimeCtrl::SetFormat(_T("MM'/'dd'/'yyyy"));
	}
}


void CInPlaceFormattedDate::EndEdit()
{
	CString str;
	if (::IsWindow(m_hWnd)) 
	{
		GetWindowText(str);
		// I don't understand what the purpose of the
		// following is, since we just care about the text now
		// and are about to destroy ourselves.  -dkuznick 05/05/2005
		GetTime(*m_pcTime);
	}

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

void CInPlaceFormattedDate::PostNcDestroy() 
{
	CDateTimeCtrl::PostNcDestroy();
	delete this;
}

BEGIN_MESSAGE_MAP(CInPlaceFormattedDate, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CInPlaceFormattedDate)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
//	ON_WM_KEYUP()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInPlaceFormattedDate message handlers

void CInPlaceFormattedDate::OnKillFocus(CWnd* pNewWnd) 
{
	CDateTimeCtrl::OnKillFocus(pNewWnd);

	if (GetSafeHwnd() == pNewWnd->GetSafeHwnd()) {
		return;
	}
	EndEdit();
}

UINT CInPlaceFormattedDate::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}

void CInPlaceFormattedDate::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (( nChar == VK_PRIOR || nChar == VK_NEXT ||
		nChar == VK_DOWN  || nChar == VK_UP   ||
		nChar == VK_RIGHT || nChar == VK_LEFT) &&
		(m_bExitOnArrows  || GetKeyState(VK_CONTROL) < 0))
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();
		return;
	}

	// Moved here from OnKeyUp Gensym -fmw, 9/21/06 -----------------
	if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
	{
		m_nLastChar = nChar;
		GetParent()->SetFocus();    // This will destroy this window
		return;
	}
	// Moved here from OnKeyUp Gensym -fmw, 9/21/06 -----------------

	CDateTimeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

// void CInPlaceFormattedDate::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
// {
// 	if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
// 	{
// 		m_nLastChar = nChar;
// 		GetParent()->SetFocus();    // This will destroy this window
// 		return;
// 	}

// 	CDateTimeCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
// }
