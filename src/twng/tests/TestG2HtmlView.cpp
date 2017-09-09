#include "stdafx.h"
#include "TestG2HtmlView.h"
#include "TWNG.h"
#include "HtmlView.h"

//CPPUNIT_TEST_SUITE_REGISTRATION(TestG2HtmlView);

class MouseWheelParentWindow: public CWnd
{
  DECLARE_MESSAGE_MAP();

public:
  MouseWheelParentWindow(): wheelMessageCount(0) {}

  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
  {
    ++wheelMessageCount;
    return TRUE;
  }

  int getWheelMessageCount() {return wheelMessageCount;}

private:
  int wheelMessageCount;
};


BEGIN_MESSAGE_MAP(MouseWheelParentWindow, CWnd)
  ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

void DoEvents()
{
  MSG dispatch;
  while (::PeekMessage( &dispatch, NULL, 0, 0, PM_NOREMOVE))
  {
    GetMessage(&dispatch, 0, 0, 0);
    DispatchMessage(&dispatch);
  }
}

void TestG2HtmlView::testMouseWheel()
{
  MouseWheelParentWindow parentWindow;
  parentWindow.CreateEx(0, AfxRegisterWndClass(NULL),
      _T("MouseWheelParentWindow"), WS_VISIBLE, CRect(0, 0, 200, 200),
      NULL, 0);
  DoEvents();
  CPPUNIT_ASSERT(IsWindow(parentWindow.m_hWnd));

  CWnd containerWindow;
  containerWindow.CreateEx(0, AfxRegisterWndClass(0), _T("Container"), WS_VISIBLE,
      CRect(100, 100, 300, 300), &parentWindow, 0);
  DoEvents();
  CPPUNIT_ASSERT(IsWindow(containerWindow.m_hWnd));

  G2HtmlView* view = new G2HtmlView();
  view->Create(0, _T("G2HtmlView"), WS_VISIBLE,
      CRect(0, 0, 100, 100), &parentWindow, 0);

  DoEvents();
  CPPUNIT_ASSERT(IsWindow(view->m_hWnd));
  PostMessage(view->m_hWnd, WM_MOUSEWHEEL, 120 << 8, 0);
  DoEvents(); 

  CPPUNIT_ASSERT(parentWindow.getWheelMessageCount() == 0);
}
