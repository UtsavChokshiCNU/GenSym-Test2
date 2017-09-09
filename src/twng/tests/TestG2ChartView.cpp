#include "stdafx.h"
#include "TestG2ChartView.h"
#include "TWNG.h"
#include "ChartView.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestG2ChartView);

class ArrowKeysParentWindow: public CWnd
{
  DECLARE_MESSAGE_MAP();
  
public:
  ArrowKeysParentWindow()
    : keyUp(0) 
    , keyDown(0)
    , keyLeft(0)
    , keyRight(0)
  {}
  
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
  {
    if (VK_UP == nChar) ++keyUp;
    else if (VK_DOWN == nChar)  ++keyDown;
    else if (VK_LEFT == nChar)  ++keyLeft;
    else if (VK_RIGHT == nChar)  ++keyRight;
  }
  
  int getKeyUp()  { return keyUp; }
  int getKeyDown()  { return keyDown; }
  int getKeyLeft()  { return keyLeft; }
  int getKeyRight() { return keyRight; }
  
private:
  int keyUp;
  int keyDown;
  int keyLeft;
  int keyRight;
};


BEGIN_MESSAGE_MAP(ArrowKeysParentWindow, CWnd)
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void DoKeyEvents()
{
  MSG dispatch;
  while (::PeekMessage( &dispatch, NULL, 0, 0, PM_NOREMOVE))
  {
    GetMessage(&dispatch, 0, 0, 0);
    DispatchMessage(&dispatch);
  }
}

void TestG2ChartView::testArrowKeys()
{
  ArrowKeysParentWindow parentWindow;
  parentWindow.CreateEx(0, AfxRegisterWndClass(NULL),
    _T("ArrowKeysParentWindow"), WS_VISIBLE, CRect(0, 0, 200, 200), NULL, 0);
  DoKeyEvents();
  CPPUNIT_ASSERT(IsWindow(parentWindow.m_hWnd));
 
  G2ChartView view;
  view.CreateEx(0, AfxRegisterWndClass(0), _T("G2ChartView"), WS_VISIBLE,
    CRect(10, 10, 100, 100), &parentWindow, 0);

  ::SendMessage(view.m_hWnd, WM_KEYDOWN, VK_RIGHT, 0);
  ::SendMessage(view.m_hWnd, WM_KEYDOWN, VK_DOWN, 0);
  ::SendMessage(view.m_hWnd, WM_KEYDOWN, VK_UP, 0);
  ::SendMessage(view.m_hWnd, WM_KEYDOWN, VK_LEFT, 0);
  DoKeyEvents();

  CPPUNIT_ASSERT(0 == parentWindow.getKeyDown());
  CPPUNIT_ASSERT(0 == parentWindow.getKeyUp());
  CPPUNIT_ASSERT(0 == parentWindow.getKeyLeft());
  CPPUNIT_ASSERT(0 == parentWindow.getKeyRight());

  ::SendMessage(parentWindow.m_hWnd, WM_KEYDOWN, VK_RIGHT, 0);
  ::SendMessage(parentWindow.m_hWnd, WM_KEYDOWN, VK_DOWN, 0);
  ::SendMessage(parentWindow.m_hWnd, WM_KEYDOWN, VK_UP, 0);
  ::SendMessage(parentWindow.m_hWnd, WM_KEYDOWN, VK_LEFT, 0);
  DoKeyEvents();

  CPPUNIT_ASSERT(1 == parentWindow.getKeyDown());
  CPPUNIT_ASSERT(1 == parentWindow.getKeyUp());
  CPPUNIT_ASSERT(1 == parentWindow.getKeyLeft());
  CPPUNIT_ASSERT(1 == parentWindow.getKeyRight());
}

void TestG2ChartView::setUp()
{
}

void TestG2ChartView::tearDown()
{
}
