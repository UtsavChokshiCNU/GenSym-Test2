// HtmlView.cpp : Subclassed CHtmlView with G2 interface.

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "HtmlView.h"

/*
 * Although this is derived from CView, it has been modified to behave like a plain CWnd.
 */

IMPLEMENT_DYNCREATE(G2HtmlView, CHtmlView)

BEGIN_MESSAGE_MAP(G2HtmlView, CHtmlView)
  ON_WM_SIZE()
  ON_WM_MOUSEACTIVATE()
  ON_WM_DESTROY()
  ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

G2HtmlView::G2HtmlView(int handle) {
  m_handle = handle;
  m_g2pointer = -1;
  SAVE_WND();
  VTRACE("G2HtmlView Construct [%d] %08X\n", m_handle, this);
}

G2HtmlView::~G2HtmlView() {
  VTRACE("G2HtmlView  Destruct [%d] %08X\n", m_handle, this);
  FORGET_WND();
  if(m_g2pointer>=0)
    g2ext_decache_g2pointer(m_g2pointer);
  m_handle=0;
  m_g2pointer=-1;
}

BOOL G2HtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
  cs.lpszClass = AfxRegisterWndClass(0); // Turn off CS_V/HREDRAW
  return CHtmlView::PreCreateWindow(cs);
}

void G2HtmlView::OnInitialUpdate()
{
  CHtmlView::OnInitialUpdate();
  GoHome();
}

void G2HtmlView::OnTitleChange(LPCTSTR lpszText)
{
  VTRACE("G2HtmlView::OnTitleChange %ls\n", lpszText);
  CXTPDockingPane *pPane = g2pvt_find_pane(m_handle);
  CFrameWnd *pFrame = GetParentFrame();
  if(pPane) {
    pPane->SetTitle(lpszText);
    g2pvt_refresh_pane_tabs(pPane);
  } else if(pFrame && pFrame != AfxGetMainWnd()) {
    pFrame->SetWindowText(lpszText);
  }
}

void G2HtmlView::OnSize(UINT nType, int cx, int cy)
{
  VTRACE("OnSize [%d] type:%d %dx%d ", m_handle, nType, cx, cy); POB(this);
  CHtmlView::OnSize(nType, cx, cy);
  g2pvt_view_sized(this, m_handle);
}

void G2HtmlView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
  CHtmlView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if(bActivate) {
    VTRACE("G2HtmlView activated [%d]\n", m_handle);
    if(m_handle > 0)
      g2pvt_send_window_activated(m_hWnd, m_handle);
  }
}

int G2HtmlView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg)
{
  // bypass CView doc/frame stuff
  return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, msg);
}

void G2HtmlView::OnDestroy()
{
  VTRACE("G2HtmlView OnDestroy [%d] %08X\n", m_handle, this);
  if(m_handle > 0)
    g2pvt_send_window_closed(m_hWnd, m_handle);
  //Changed 27/11/2009 VS2008 ATL::CComPtr must release memory automatically 
  #if defined(_ATL_VER)&&_ATL_VER<0x0900
  if (m_pBrowserApp) {		// From CHtmlView::OnDestroy.
	  m_pBrowserApp->Release();
    m_pBrowserApp = NULL;	
  }
  CWnd::OnDestroy();		// bypass CView doc/frame stuff
  #else
  CHtmlView::OnDestroy();
  #endif
}

/*
 * G2 Interface
 */

#define HTML_VIEW_DESTROY 2	// Opcodes
#define HTML_VIEW_BACK 3
#define HTML_VIEW_FORWARD 4
#define HTML_VIEW_HOME 5
#define HTML_VIEW_STOP 6
#define HTML_VIEW_REFRESH 7
#define HTML_VIEW_GOTO 8
#define HTML_VIEW_PRINT 9

void G2HtmlView::FireEvent(int event)
{
  CMainFrame *pFrame = GetMainWnd();

  POINT p;
  ::GetCursorPos(&p);
  ::ScreenToClient(pFrame->CoorHwnd(), &p);

  g2pvt_fire_control_event(GENSYM_HTML_VIEW, m_handle, p.x, p.y, m_handle, event, NULL);
}

long g2ext_create_html_view(long handle, LPWSTR title, LPWSTR url,
			    long x, long y, long width, long height,
			    long dock, long neighbor, long min_width, long min_height)
{
  CMainFrame *pFrame = GetMainWnd();
  G2HtmlView *pH = new G2HtmlView(handle);

  pH->Create(NULL, NULL, WS_CHILD, WinSize(width,height), pFrame, handle);
  pH->m_g2pointer = SavePtr(pH->m_hWnd);
  pFrame->WrapWnd(pH, handle, x, y, width, height, dock, neighbor, CSize(min_width, min_height), title);
  // GENSYMCID-911: Error shown when trying to use integrated g2 web browser control.
  pH->SetSilent(TRUE);
  pH->Navigate2(url, 0, NULL);

  return pH->m_g2pointer;
}


long g2ext_manage_html_view(long opcode, long handle, LPWSTR url)
{
  G2HtmlView *pH = FIND_WND(handle,G2HtmlView);

  if(!pH) return -1;

  switch(opcode) {
   case HTML_VIEW_DESTROY: DESTROY_WND(handle); break;
   case HTML_VIEW_BACK: pH->GoBack(); break;
   case HTML_VIEW_FORWARD: pH->GoForward(); break;
   case HTML_VIEW_HOME: pH->GoHome(); break;
   case HTML_VIEW_STOP: pH->Stop(); break;
   case HTML_VIEW_REFRESH: pH->Refresh(); break;
   case HTML_VIEW_GOTO: pH->Navigate2(url, 0, NULL); break;
   case HTML_VIEW_PRINT: pH->OnFilePrint(); break;
   default: return -1;
  }
  return 1;
}




// Patch from BUG: "CHtmlView Leaks Memory by Not Releasing BSTRs in Several
// Methods" at http://support.microsoft.com/default.aspx?scid=kb;EN-US;Q241750

CString G2HtmlView::GetFullName() const
{
  ASSERT(m_pBrowserApp != NULL);

  BSTR bstr;
  m_pBrowserApp->get_FullName(&bstr);
  CString retVal(bstr);

  SysFreeString(bstr); // Added this line to prevent leak.
  return retVal;
}

CString G2HtmlView::GetType() const
{
  ASSERT(m_pBrowserApp != NULL);

  BSTR bstr;
  m_pBrowserApp->get_Type(&bstr);

  CString retVal(bstr);

  SysFreeString(bstr); // Added this line to prevent leak.
  return retVal;
}

CString G2HtmlView::GetLocationName() const
{
  ASSERT(m_pBrowserApp != NULL);

  BSTR bstr;
  m_pBrowserApp->get_LocationName(&bstr);
  CString retVal(bstr);

  SysFreeString(bstr); // Added this line to prevent leak.
  return retVal;
}

CString G2HtmlView::GetLocationURL() const
{
  ASSERT(m_pBrowserApp != NULL);

  BSTR bstr;
  m_pBrowserApp->get_LocationURL(&bstr);
  CString retVal(bstr);

  SysFreeString(bstr); // Added this line to prevent leak.
  return retVal;
}

void G2HtmlView::Navigate(LPCTSTR lpszURL, DWORD dwFlags /* = 0 */,
			  LPCTSTR lpszTargetFrameName /* = NULL */ ,
			  LPCTSTR lpszHeaders /* = NULL */,
			  LPVOID lpvPostData /* = NULL */,
			  DWORD dwPostDataLen /* = 0 */)
{
  CString strURL(lpszURL);
  BSTR bstrURL = strURL.AllocSysString();

  COleSafeArray vPostData;
  if (lpvPostData != NULL)
    {
      if (dwPostDataLen == 0)
	dwPostDataLen = lstrlen((LPCTSTR) lpvPostData);

      vPostData.CreateOneDim(VT_UI1, dwPostDataLen, lpvPostData);
    }

  m_pBrowserApp->Navigate(bstrURL,
			  COleVariant((long) dwFlags, VT_I4),
			  COleVariant(lpszTargetFrameName, VT_BSTR),
			  vPostData,
			  COleVariant(lpszHeaders, VT_BSTR));

  SysFreeString(bstrURL); // Added this line to prevent leak.
}


BOOL G2HtmlView::LoadFromResource(LPCTSTR lpszResource)
{
  HINSTANCE hInstance = AfxGetResourceHandle();
  ASSERT(hInstance != NULL);

  CString strResourceURL;
  BOOL bRetVal = TRUE;
  LPTSTR lpszModule = new TCHAR[_MAX_PATH];

  if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
    {
      strResourceURL.Format(_T("res://%s/%s"), lpszModule, lpszResource);
      Navigate(strResourceURL, 0, 0, 0);
    }
  else
    bRetVal = FALSE;

  delete [] lpszModule;
  return bRetVal;
}

BOOL G2HtmlView::LoadFromResource(UINT nRes)
{
  HINSTANCE hInstance = AfxGetResourceHandle();
  ASSERT(hInstance != NULL);

  CString strResourceURL;
  BOOL bRetVal = TRUE;
  LPTSTR lpszModule = new TCHAR[_MAX_PATH];

  if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
    {
      strResourceURL.Format(_T("res://%s/%d"), lpszModule, nRes);
      Navigate(strResourceURL, 0, 0, 0);
    }
  else
    bRetVal = FALSE;

  delete [] lpszModule;
  return bRetVal;
}
// End of patch

BOOL G2HtmlView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
  return TRUE;
}
