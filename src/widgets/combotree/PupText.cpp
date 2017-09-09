////////////////////////////////////////////////////////////////
// MSDN -- September 2000
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
// Modified from MSDN Magazine -- September 2000 PupText.cpp

#include "stdafx.h"
#include "puptext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPopupText,CWnd)
BEGIN_MESSAGE_MAP(CPopupText,CWnd)
	ON_WM_PAINT()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

CPopupText::CPopupText()
{
	m_szMargins = CSize(4,4);
	// create font -- use system tooltip font
	CNonClientMetrics ncm;
	m_font.CreateFontIndirect(&ncm.lfStatusFont);

	m_DelayTimer = 0;
	m_MoveOutsideTimer = 0;
	m_bMovedOutside = FALSE;
}

CPopupText::~CPopupText()
{
}

//////////////////
// Create window. pt is upper left or upper right corner depending on nStyle.
//
BOOL CPopupText::Create(CPoint pt, CWnd* pParentWnd, UINT nStyle, UINT nID)
{
	m_nStyle = nStyle;
	return CreateEx(WS_EX_TOPMOST,
		NULL,
		NULL,
		WS_POPUP | WS_VISIBLE,
		CRect(pt,CSize(0,0)),
		pParentWnd,
		nID);
}

//////////////////
// text changed: resize window to fit
//
LRESULT CPopupText::OnSetText(WPARAM wp, LPARAM lp)
{
	UNREFERENCED_PARAMETER (wp);
	#if defined(_MFC_VER)&&_MFC_VER>=0x0900//VS2008 MFC and more
	CClientDC dc(this);
	#else
	CClientDC dc = this;
	#endif
	CFont* pOldFont = dc.SelectObject(&m_font);
	CRect rc;
	GetWindowRect(&rc);
	int x = (m_nStyle & JUSTIFYRIGHT) ? rc.right : rc.left;
	int y = rc.top;
	dc.DrawText(CString((LPCTSTR)lp), &rc, DT_CALCRECT);
	rc.InflateRect(m_szMargins);
	if (m_nStyle & JUSTIFYRIGHT)
		x -= rc.Width();
	SetWindowPos(NULL,x,y,rc.Width(),rc.Height(), SWP_NOZORDER|SWP_NOACTIVATE);
	dc.SelectObject (pOldFont);

	return Default();
}

//////////////////
// Paint text using system colors
//
void CPopupText::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	CString s;
	GetWindowText(s);
	CBrush b(GetSysColor(COLOR_INFOBK)); // use tooltip bg color
	dc.FillRect(&rc, &b);

	// draw text
	dc.SetBkMode(TRANSPARENT);
	CFont* pOldFont = dc.SelectObject(&m_font);
	dc.SetTextColor(GetSysColor(COLOR_INFOTEXT)); // tooltip text color
	dc.DrawText(s, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	dc.SelectObject(pOldFont);
}

//////////////////
// Register class if needed
//
BOOL CPopupText::PreCreateWindow(CREATESTRUCT& cs) 
{
	static CString sClassName;
	if (sClassName.IsEmpty())
		sClassName = AfxRegisterWndClass(0);
	cs.lpszClass = sClassName;
	cs.style = WS_POPUP|WS_BORDER;
	cs.dwExStyle |= WS_EX_TOOLWINDOW;
	return CWnd::PreCreateWindow(cs);
}

//////////////////
// CPopupText is intended to be used on the stack,
// not heap, so don't auto-delete.
//
void CPopupText::PostNcDestroy()
{
	// don't delete this
}

//////////////////
// Show window with delay. No delay means show now.
//
void CPopupText::ShowDelayed(UINT msec)
{
	StopMoveOutsideTimer();

	//Start mouve outside of window timer
	m_MoveOutsideTimer = SetTimer (OUTOFWINDOWTIMER, 200, NULL);
	m_bMovedOutside = FALSE;

	if (msec==0) {
		// no delay: show it now 
		ShowPopup ();
	}
	else
	{
		// delay: set time
		m_DelayTimer = SetTimer(DELAYTIMER, msec, NULL);
	}
}

//////////////////
// Cancel text: kill timers and hide window
//
void CPopupText::Cancel()
{
	
	StopDelayTimer();
	StopMoveOutsideTimer();
	ShowWindow(SW_HIDE);
}


//////////////////
// Timer popped: display myself and kill timer. 
// If Mouse moved outside of parent window, cancel and set flag
void CPopupText::OnTimer(UINT nIDEvent)
{
	CWnd::OnTimer (nIDEvent);


	if (nIDEvent == m_DelayTimer)
	{
		ShowPopup ();
		StopDelayTimer();
	}
	else if (nIDEvent == m_MoveOutsideTimer)
	{
		CWnd* pParent = GetParent ();
		if (pParent)
		{
			CPoint Pos;
			GetCursorPos (&Pos);
			CWnd* pOverWindow = WindowFromPoint  (Pos);
			if (pOverWindow)
			{
				if (!((pOverWindow->m_hWnd == m_hWnd) || (pOverWindow->m_hWnd == pParent->m_hWnd)))
				{
					m_bMovedOutside = TRUE;
					Cancel ();
				}
			}
		}
	}

}

//////////////////
// Show popup, called when delay timer expires
//
void CPopupText::ShowPopup()
{
	ShowWindow(SW_SHOWNA);
	Invalidate();
	UpdateWindow();
}


void CPopupText::StopMoveOutsideTimer()
{
	if (m_MoveOutsideTimer != 0)
	{
		KillTimer (m_MoveOutsideTimer);
		m_MoveOutsideTimer = 0;
	}
}


void CPopupText::StopDelayTimer()
{
	if (m_DelayTimer != 0)
	{
		KillTimer (m_DelayTimer);
		m_DelayTimer = 0;
	}
}

void CPopupText::OnLButtonDown(UINT nFlags, CPoint point)
{
	Cancel ();
	CWnd::OnLButtonDown(nFlags, point);
}

void CPopupText::OnRButtonDown(UINT nFlags, CPoint point)
{
	Cancel ();
	CWnd::OnRButtonDown(nFlags, point);
}

void CPopupText::OnMButtonDown(UINT nFlags, CPoint point)
{
	Cancel ();
	CWnd::OnMButtonDown(nFlags, point);
}

int CPopupText::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	UNREFERENCED_PARAMETER(pDesktopWnd);
	UNREFERENCED_PARAMETER(nHitTest);
	UNREFERENCED_PARAMETER(message);

	//Don't activate to prevent window position changes
	return MA_NOACTIVATE;
}

