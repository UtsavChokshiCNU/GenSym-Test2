// ChildFrm -- Container for non-workspace-views

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "ChildFrm.h"

/*
 * CChildFrm is the MDI child container for all views other than workspace
 * views.  As such, it needs to handle all the windows notifications that they
 * do: OnMove, OnSize, etc. It contains exactly one child view, with the G2
 * handle as saved in the slot.
 */

IMPLEMENT_DYNCREATE(CChildFrm, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrm, CMDIChildWnd)
  ON_MESSAGE(WM_XTP_GETTABICON,GetTabIcon)
  ON_MESSAGE(WM_SET_NATIVE_ICON,OnSetNativeIcon)
  ON_MESSAGE(WM_ICON_CHANGED, OnIconChanged)
  ON_MESSAGE(WM_ENTERSIZEMOVE, OnEnterSizeMove)
  ON_MESSAGE(WM_EXITSIZEMOVE, OnExitSizeMove)
  ON_MESSAGE(WM_ENTERMENULOOP, OnEnterMenuLoop)
  ON_MESSAGE(WM_EXITMENULOOP, OnExitMenuLoop)
  ON_WM_SYSCOMMAND()
  ON_WM_SETFOCUS()
  ON_WM_WINDOWPOSCHANGING()
  ON_WM_MOUSEACTIVATE()
  ON_WM_MOVE()
  ON_WM_SIZE()
  ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL g2pvt_is_cchildfrm(CWnd *pWnd)
{
  return pWnd->IsKindOf(RUNTIME_CLASS(CChildFrm));
}

CChildFrm::CChildFrm(int handle)
{
  m_handle = handle>0 ? handle : 0;
  m_icon = -1;
  SAVE_WND();
  VTRACE("CChildFrm Construct [%d] %08X\n", m_handle, this);
}
CChildFrm::~CChildFrm() {
  VTRACE("CChildFrm Destruct  [%d] %08X\n", m_handle, this);
  FORGET_WND();
  m_handle=0;
}

LRESULT CChildFrm::GetTabIcon(WPARAM wParam, LPARAM lParam)
{
  return (LRESULT) GetIcon(FALSE);
}

LRESULT CChildFrm::OnSetNativeIcon(WPARAM wParam, LPARAM lParam)
{
  m_icon = wParam;
  GetMainWnd()->RefreshChildIcon(this, m_icon);
  return 1;
}

LRESULT CChildFrm::OnIconChanged(WPARAM changed_icon, LPARAM iconID)
{
  if(m_icon == (int)changed_icon)
    GetMainWnd()->RefreshChildIcon(this, m_icon);
  return 0;
}

BOOL CChildFrm::PreCreateWindow(CREATESTRUCT& cs)
{
  VTRACE("CChildFrm::PreCreateWindow [%d] %08X\n", m_handle, this);
  cs.lpszClass = AfxRegisterWndClass(0); // Turn off CS_V/HREDRAW
  if(!CMDIChildWnd::PreCreateWindow(cs))
    return FALSE;
  cs.dwExStyle &= ~WS_EX_CLIENTEDGE;     // Turn off the extra-thick borders.
  return TRUE;
}

void CChildFrm::OnSysCommand(UINT nID, LONG lParam)
{
  if((nID & 0xFFF0) == SC_CLOSE && !g2pvt_syscommand_enabled_p(m_hWnd,SC_CLOSE))
    return;
  else
    CMDIChildWnd::OnSysCommand(nID, lParam);
} 

void CChildFrm::OnWindowPosChanging(WINDOWPOS *pos)
{
  VTRACE("CChildFrm::OnWindowPosChanging inhibit=%d\n", g_InhibitZorderChanges);
  CMDIChildWnd::OnWindowPosChanging(pos);
  if(g_InhibitZorderChanges > 0)
    pos->flags |= SWP_NOZORDER;
}

int CChildFrm::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT nMsg)
{
  VTRACE("CChildFrm::OnMouseActivate [%d] msg:%04x\n", m_handle, nMsg);

  if(nHitTest == HTCLIENT)	// NOTE Near-duplicate code in GensymMDIChildWndProc.
    switch(nMsg) {
     case WM_LBUTTONDOWN:
       if(GetMDIFrame()->MDIGetActive() == this)
	 BringWindowToTop();
       break;
     case WM_RBUTTONDOWN:
       if(g_NoRaiseOnRightClick) {
	 g_InhibitZorderChanges++;
	 MDIActivate();
	 g_InhibitZorderChanges--;
	 return MA_NOACTIVATE;
       }
       break;
    }

  return CMDIChildWnd::OnMouseActivate(pDesktopWnd, nHitTest, nMsg);
}

void CChildFrm::OnSetFocus(CWnd* pOldWnd)
{
  VTRACE("CChildFrm::OnSetFocus [%d]\n", m_handle);
  CMDIChildWnd::OnSetFocus(pOldWnd);

  CWnd *pChild = GetWindow(GW_CHILD);
  if(pChild) pChild->SetFocus();

  if(m_handle > 0)
    g2pvt_send_window_activated(m_hWnd, m_handle);
}

void CChildFrm::OnMove(int x, int y)
{
  //  VTRACE("CChildFrm::OnMove [%d] %d,%d\n", m_handle, x, y);
  CMDIChildWnd::OnMove(x, y);
  if(m_handle > 0)
    g2pvt_send_window_moved(m_hWnd, m_handle, x, y);
}

void CChildFrm::OnSize(UINT nType, int cx, int cy) 
{
  VTRACE("CChildFrm::OnSize [%d] type:%d %dx%d\n", m_handle, nType, cx, cy);
  CMDIChildWnd::OnSize(nType, cx, cy);

  // Resize child window, if any.
  CWnd *pChild = GetWindow(GW_CHILD);
  if(pChild) {
    CRect r;
    GetClientRect(r);
    pChild->MoveWindow(r);
  }
  g2pvt_view_sized(this, m_handle, nType);
}

LRESULT CChildFrm::OnEnterSizeMove(WPARAM, LPARAM)
{
  LRESULT rc = Default();
  CWnd *pChild = GetWindow(GW_CHILD);
  if(pChild)
    pChild->SendMessage(WM_PARENT_IS_MOVING);
  g2pvt_enter_modal_loop();
  return rc;
}

LRESULT CChildFrm::OnExitSizeMove(WPARAM, LPARAM)
{
  g2pvt_exit_modal_loop();
  return Default();
}

LRESULT CChildFrm::OnEnterMenuLoop(WPARAM, LPARAM)
{
  LRESULT rc = Default();
  g2pvt_enter_modal_loop();
  return rc;
}

LRESULT CChildFrm::OnExitMenuLoop(WPARAM, LPARAM)
{
  g2pvt_exit_modal_loop();
  return Default();
}

void CChildFrm::OnDestroy()
{
  VTRACE("CChildFrm::OnDestroy [%d] %08X\n", m_handle, this);
  CMDIChildWnd::OnDestroy();
  if(m_handle > 0)
    g2pvt_send_window_closed(m_hWnd, m_handle);
}
