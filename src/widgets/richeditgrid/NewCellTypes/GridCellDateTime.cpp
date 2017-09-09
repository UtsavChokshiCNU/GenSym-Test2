///////////////////////////////////////////////////////////////////////////
//
// GridCellDateTime.cpp: implementation of the CGridCellDateTime class.
//
// Provides the implementation for a datetime picker cell type of the
// grid control.
//
// Written by Podsypalnikov Eugen 15 Mar 2001
// Modified:
//    31 May 2001  Fixed m_cTime bug (Chris Maunder)
//
// For use with CGridCtrl v2.22+
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCtrl.h"
#include "GridCell.h"
#include "GridCellDateTime.h"
#include "dyndlgs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CGridCellDateTime

IMPLEMENT_DYNCREATE(CGridCellDateTime, CGridCell)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridCellDateTime::CGridCellDateTime() : CGridCell()
{
	m_dwStyle = 0;
	m_cTime   = CTime::GetCurrentTime();
}

CGridCellDateTime::CGridCellDateTime(DWORD dwStyle) : CGridCell()
{
	Init(dwStyle, 0);
}

CGridCellDateTime::~CGridCellDateTime()
{
}

CSize CGridCellDateTime::GetCellExtent(CDC* pDC)
{    
    CSize sizeScroll (GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYHSCROLL));	
    CSize sizeCell (CGridCell::GetCellExtent(pDC));	
    sizeCell.cx += sizeScroll.cx;	
    sizeCell.cy = max(sizeCell.cy,sizeScroll.cy);	
    return sizeCell;
}

BOOL CGridCellDateTime::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, 
							 UINT nID, UINT nChar)
{
	m_bEditing = TRUE;

	// CInPlaceDateTime auto-deletes itself
	m_pEditWnd = new CInPlaceDateTime(GetGrid(), rect,
		m_dwStyle|DTS_UPDOWN, m_dwG2Style, nID, nRow, nCol, 
		GetTextClr(), GetBackClr(), GetTime(), nChar);
	return TRUE;
}

CWnd* CGridCellDateTime::GetEditWnd() const
{
	return m_pEditWnd;
}

void CGridCellDateTime::EndEdit()
{
	if (m_pEditWnd) ((CInPlaceDateTime*)m_pEditWnd)->EndEdit();
}

void CGridCellDateTime::Init(DWORD dwStyle, long dwG2Style)
{
	m_dwStyle = dwStyle;

    m_dwG2Style = dwG2Style;
	SetTime(CTime::GetCurrentTime());

	SetFormat(DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX
#ifndef _WIN32_WCE
		|DT_END_ELLIPSIS
#endif
	);
}

// Should be changed to use locale settings
void CGridCellDateTime::SetTime(CTime time)
{
	m_cTime = time;
    CString strTemp;

	if (DTS_TIMEFORMAT == m_dwStyle) 
	{
#ifdef _WIN32_WCE
		CString strTemp;
		strTemp.Format(_T("%02d:%02d:%02d"), 
			           m_cTime.GetHour(), m_cTime.GetMinute(), m_cTime.GetSecond());
		SetText(strTemp);

#else
        SetText(m_cTime.Format(_T("%H:%M:%S")));
//    	SetText(m_cTime.Format(_T("%X")));

        if (G2_DTS_24_HOUR & m_dwG2Style)
        {
        	strTemp.Format(_T("%02d:%02d:%02d"), 
			           m_cTime.GetHour(), m_cTime.GetMinute(), m_cTime.GetSecond());
		    SetText(strTemp);
        }
        else 
        {
            if (G2_DTS_SHOW_TIME & m_dwG2Style)
            {
               int nHours = m_cTime.GetHour();
               bool bPM = FALSE;
               if  ( 0 < (nHours/12))
                   bPM = TRUE;

               nHours = nHours%12;
               if (bPM)
	              strTemp.Format(_T("%02d:%02d:%02d PM"), 
			           nHours, m_cTime.GetMinute(), m_cTime.GetSecond());
               else
                  strTemp.Format(_T("%02d:%02d:%02d AM"), 
			           nHours, m_cTime.GetMinute(), m_cTime.GetSecond());
	     	   SetText(strTemp);
            }
          
        }
#endif
	}
	else if (DTS_SHORTDATEFORMAT == m_dwStyle) 
	{
#ifdef _WIN32_WCE
		CString strTemp;
		strTemp.Format(_T("%02d/%02d/%02d"), 
			           m_cTime.GetMonth(), m_cTime.GetDay(), m_cTime.GetYear());
		SetText(strTemp);
#else
		SetText(m_cTime.Format(("%m/%d/%Y")));
//		SetText(m_cTime.Format(("%x")));
#endif
	}

}


// Gensym addition -jv, 5/03/05
DWORD CGridCellDateTime::GetExStyle()
{
  return m_dwStyle;
}


/////////////////////////////////////////////////////////////////////////////
// CInPlaceDateTime

CInPlaceDateTime::CInPlaceDateTime(CWnd* pParent, CRect& rect, DWORD dwStyle, DWORD dwG2Style, UINT nID,
								   int nRow, int nColumn, 
								   COLORREF crFore, COLORREF crBack,
								   CTime* pcTime,
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
	SetFormat(dwStyle, dwG2Style);

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

CInPlaceDateTime::~CInPlaceDateTime()
{
}

// Should be changed to use locale settings
void CInPlaceDateTime::SetFormat(DWORD dwStyle, DWORD dwG2Style)
{
  
    if (DTS_TIMEFORMAT == (dwStyle & DTS_TIMEFORMAT)) 
	{
		CDateTimeCtrl::SetFormat(_T("HH':'mm':'ss"));
	}
	else // if (DTS_SHORTDATEFORMAT & dwStyle) 
	{
		CDateTimeCtrl::SetFormat(_T("MM'/'dd'/'yyyy"));
	}

    if (dwG2Style & G2_DTS_SHOW_TIME) 
    {
      	CDateTimeCtrl::SetFormat(_T("h:mm:ss"));
    } 
    else
    if ( dwG2Style & G2_DTS_24_HOUR)
    {
      	CDateTimeCtrl::SetFormat(_T("H:mm:ss"));
    }

}	

void CInPlaceDateTime::EndEdit()
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

void CInPlaceDateTime::PostNcDestroy() 
{
	CDateTimeCtrl::PostNcDestroy();
	delete this;
}

BEGIN_MESSAGE_MAP(CInPlaceDateTime, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CInPlaceDateTime)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
//	ON_WM_KEYUP()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInPlaceDateTime message handlers

void CInPlaceDateTime::OnKillFocus(CWnd* pNewWnd) 
{
	CDateTimeCtrl::OnKillFocus(pNewWnd);

	if (GetSafeHwnd() == pNewWnd->GetSafeHwnd()) {
		return;
	}
	EndEdit();
}

UINT CInPlaceDateTime::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}

void CInPlaceDateTime::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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

// void CInPlaceDateTime::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
// {
// 	if (nChar == VK_TAB || nChar == VK_RETURN || nChar == VK_ESCAPE)
// 	{
// 		m_nLastChar = nChar;
// 		GetParent()->SetFocus();    // This will destroy this window
// 		return;
// 	}

// 	CDateTimeCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
// }
