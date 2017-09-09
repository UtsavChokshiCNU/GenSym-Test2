#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "WorkspaceView.h"

#define COLOR_DEFAULT ((COLORREF)-1)

IMPLEMENT_DYNCREATE(G2WorkspaceView, CMDIChildWnd)

BEGIN_MESSAGE_MAP(G2WorkspaceView, CMDIChildWnd)
 ON_WM_ERASEBKGND()
 ON_MESSAGE(WM_XTP_GETTABICON,GetTabIcon)
 ON_MESSAGE(WM_SET_NATIVE_ICON,OnSetNativeIcon)
 ON_MESSAGE(WM_ICON_CHANGED, OnIconChanged)
 ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

G2WorkspaceView::G2WorkspaceView(int handle)
{
  m_handle = handle;
  m_icon = -1;
  m_bgColor = COLOR_DEFAULT;
}

G2WorkspaceView::~G2WorkspaceView()
{
}

BOOL G2WorkspaceView::OnEraseBkgnd(CDC *pDC)
{
  if(G2_inflate_in_progress)
    return TRUE;

  if(m_bgColor == COLOR_DEFAULT)
    return Default();

  CRect r;
  pDC->GetClipBox(&r);
  pDC->FillSolidRect(&r, m_bgColor);
  return TRUE;
}

void G2WorkspaceView::SetBackgroundColor(COLORREF color)
{
  m_bgColor = color;
}

LRESULT G2WorkspaceView::GetTabIcon(WPARAM wParam, LPARAM lParam)
{
  return (LRESULT) GetIcon(FALSE);
}

LRESULT G2WorkspaceView::OnSetNativeIcon(WPARAM wParam, LPARAM lParam)
{
  m_icon = wParam;
  GetMainWnd()->RefreshChildIcon(this, m_icon);
  return 1;
}

LRESULT G2WorkspaceView::OnIconChanged(WPARAM changed_icon, LPARAM iconID)
{
  if(m_icon == (int)changed_icon)
    GetMainWnd()->RefreshChildIcon(this, m_icon);
  return 0;
}

int G2WorkspaceView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
  if(message == WM_RBUTTONDOWN && g_NoRaiseOnRightClick)
    return MA_NOACTIVATE;
  else
    return CMDIChildWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

// Bug egg: workspace views are not always MDI children, so basing this class on
// CMDIChildWnd is not always correct. In TW, the window class can be flexible
// about which default wndproc it calls. -fmw, 3/28/05
LRESULT G2WorkspaceView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT value = 0;

  if(g2pvt_swv_wndproc(m_hWnd, message, wParam, lParam, &value))
    return CMDIChildWnd::WindowProc(message, wParam, lParam);
  else
    return value;
}

// TW uses a different wndclass for MDI child workspace views, so this function
// has to be generic.
BOOL g2pvt_workspace_view_p (HWND hwnd)
{
  if(g2pvt_tw_workspace_view_p(hwnd))
    return TRUE;

  CWnd *pWnd = CWnd::FromHandle(hwnd);
  return pWnd->IsKindOf(RUNTIME_CLASS(G2WorkspaceView));
}



/*
 * Lisp Interface
 */

// NOTE: For historical reasons, this is called via g2ext_x11_create_window().
HWND g2pvt_create_workspace_view(long handle, HWND client, LPWSTR title,
                                 DWORD style, RECT* rp)
{
  CMainFrame *pFrame = GetMainWnd();
  G2WorkspaceView* pWSV = new G2WorkspaceView(handle);
  static CString wsvClass;

  // Window class for workspace-view windows. Copied from ext/c/msinits.c
  if(wsvClass.IsEmpty()) {
    HICON iconHandle = 0;
    std::wstring iconPath = Twng_GetWorkspaceViewIconPath();
    if (iconPath.length() > 0)
      iconHandle = (HICON) LoadImage(NULL, iconPath.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if (iconHandle == 0)
      iconHandle = AfxGetApp()->LoadIcon(IDR_TwngTYPE);
    wsvClass = AfxRegisterWndClass(CS_BYTEALIGNWINDOW | CS_BYTEALIGNCLIENT | CS_DBLCLKS,
                                   AfxGetApp()->LoadStandardCursor(IDC_ARROW),
                                   (HBRUSH)GetStockObject(LTGRAY_BRUSH), iconHandle);
  }

  // Tried passing GensymWorkspaceViewClass directly here, but had refresh
  // problems. TODO: Worth trying again.

  pWSV->Create(wsvClass, title, style, CRect(rp), pFrame);
  pWSV->InitialUpdateFrame(NULL, TRUE);

  // MFC insists on thick edges. Turn them off here.
  pWSV->ModifyStyleEx(WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);

  return pWSV->m_hWnd;
}

void g2pvt_set_workspace_view_background_color(HWND hwnd, COLORREF color)
{
  G2WorkspaceView *pWS = DYNAMIC_DOWNCAST(G2WorkspaceView,CWnd::FromHandlePermanent(hwnd));
  if(pWS)
    pWS->SetBackgroundColor(color);
}
