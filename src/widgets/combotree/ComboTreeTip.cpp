// Based on example from September 2000 MSDN Magazine
// in C++ Q&A Tooltip article by Paul DiLascia (p155)
//

#include "stdafx.h"
#include "Windowsx.h"
#include "PupText.h"
#include "ComboTreeTip.h"

// THE popup tip window
CPopupText ComboTreeTip::g_wndTip;

// Timeout before showing long tree control tip -- you can change
UINT ComboTreeTip::g_nTipTimeMsec = 200; // .2 sec

ComboTreeTip::ComboTreeTip()
{
	m_hCurItem=NULL;
	m_bCapture = FALSE;
}

ComboTreeTip::~ComboTreeTip()
{
}

//////////////////
// Install hook. Initialize control ID from tree control and create
// (invisible) tip window.
//
void ComboTreeTip::Init(CWnd* pTreeCtl)
{
	CSubclassWnd::HookWindow(pTreeCtl);
	m_idMyControl = pTreeCtl->GetDlgCtrlID();
	if (!g_wndTip) {
		// create scroll tip window
		g_wndTip.Create(CPoint(0,0), pTreeCtl, 0);
	}
}

//////////////////
// "Hook" function traps messages sent to tree control. 
//
LRESULT ComboTreeTip::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_MOUSEMOVE:
		OnMouseMove(CPoint(GET_X_LPARAM(lp),GET_Y_LPARAM(lp)));
		break;
	case WM_LBUTTONDOWN:
		g_wndTip.Cancel ();
		break;
	}
	return CSubclassWnd::WindowProc(msg, wp, lp);
}

/////////////////
// User moved the mouse.
// Get info for tree control item under mouse:
// If text is too wide to fit in tree control, prepare tip window and start
// timer to display it.
//
void ComboTreeTip::OnMouseMove(CPoint pt)
{
	CTreeCtrl* pTreeCtrl = (CTreeCtrl*)CWnd::FromHandle(m_hWnd);

	// Get text and text rectangle for item under mouse
	CString sText;	// item text
	CRect rcText;	// item text rect
	HTREEITEM hItem = OnGetItemInfo(pt, rcText, sText);

	if (hItem==NULL || hItem!=m_hCurItem || g_wndTip.MovedOutside())
	{
		g_wndTip.Cancel(); // new item, or no item: cancel popup text

		// Gensym modification: it used to say, (hItem>=0), which meant
		// that we did the following even if hItem was NULL (i.e., 0).
		// That causes strange behavior, because rcText actually has
		// garbage in it, unless hItem is non-NULL.  It was never
		// initialized in this function (nor is it clear what default
		// values it could possibly have), and if OnGetItemInfo returned
		// NULL, then we never tried to fill in the rectangle's values.
		// I think it's correct to still do the g_wndTip.Cancel() above,
		// and the m_hCurItem assignment below, but this section, which
		// puts up the tooltip, should not be done if we don't have an
		// hItem.  - jv, 1/20/06
		if ((hItem != NULL) && !IsRectCompletelyVisible(rcText)) {
			// new item, and not wholly visible: prepare popup tip
			CRect rc = rcText;
			pTreeCtrl->ClientToScreen(&rc);	// text rect in screen coords
			g_wndTip.SetWindowText(sText);	// set tip text to that of item

//			TRACE ("Preparing to display tooltip.\n");
			// move tip window over tree control text
			g_wndTip.SetWindowPos(NULL, rc.left-3, rc.top, rc.Width()+6,
				rc.Height(), SWP_NOZORDER|SWP_NOACTIVATE);

			g_wndTip.ShowDelayed(g_nTipTimeMsec); // show popup text delayed
		}
	}
	m_hCurItem = hItem;

}

//////////////////
// Determine if given rectangle is completely visible withing tree control
//
BOOL ComboTreeTip::IsRectCompletelyVisible(const CRect& rc)
{
	CTreeCtrl* pTreeCtrl = (CTreeCtrl*)CWnd::FromHandle(m_hWnd);
	CRect rcClient;
	pTreeCtrl->GetClientRect(&rcClient);
	return (rcClient.right > rc.right);
}

//////////////////
// Get info (rectangle and text) for item under point
//
HTREEITEM ComboTreeTip::OnGetItemInfo(CPoint p, CRect& rc, CString& s)
{
	CTreeCtrl* pTreeCtrl = (CTreeCtrl*)CWnd::FromHandle(m_hWnd);
	ASSERT_VALID(pTreeCtrl);
	UINT flags = 0;
	HTREEITEM hItem = pTreeCtrl->HitTest (p, &flags);
	s.Empty();
	if (hItem && (TVHT_ONITEM & flags))
	{
		s = pTreeCtrl->GetItemText (hItem);
		pTreeCtrl->GetItemRect (hItem, rc, TRUE);
		CFont *pFont = pTreeCtrl->GetFont();
		CClientDC dc(pTreeCtrl);
		CFont* pOldFont = dc.SelectObject(pFont);
		dc.DrawText(s,&rc,DT_CALCRECT);
		dc.SelectObject(pOldFont);
		return hItem;
	}
	return NULL;
}
