#include "stdafx.h"
#include "TestG2TreeView.h"
#include "twng.h"
#include "MainFrm.h"
#include "NativeView.h"
#include "TreeView.h"
#include "MockDestroyListener.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestG2TreeView);

const int numberOfNodes = 13000;
const int allowedTimeInMs = 5000;

void TestG2TreeView::setUp()
{
  	mainWindow = new CWnd();
	mainWindow->CreateEx(0, AfxRegisterWndClass(0), _T(""),
		WS_VISIBLE | WS_POPUP,	CRect(0, 0, 100, 100), NULL, 0);
	view = new G2TreeView();
	view->Create(TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS
		| TVS_SHOWSELALWAYS | TVS_EDITLABELS, WinSize(100, 100), mainWindow, 0);
}

void TestG2TreeView::tearDown() {
	delete mainWindow;
}

void TestG2TreeView::testDestroyTime()
{
  view->SetRedraw(FALSE);
  for (int i = 0; i < numberOfNodes; ++i) 
  {
    view->AddItem(0, 0);
  }
  view->SetRedraw(TRUE);

  DWORD t1 = GetTickCount();
  view->DestroyWindow();
  view = 0;
  DWORD t2 = GetTickCount();
  DWORD t = t2 - t1;
  char str[100];
  sprintf(str, "TreeCtrl destroy took %ldms, which is above of the limit in %ldms", t, allowedTimeInMs);
  CPPUNIT_ASSERT_MESSAGE(str, t <= allowedTimeInMs);
}

void TestG2TreeView::testOnDestroyOfBaseClassIsCalled()
{
  MockDestroyListener listener;
  G2NativeView<TREE_CTRL>* nativeView = view;
  nativeView->setDestroyListener(&listener);
  view->DestroyWindow();
  view = 0;
  CPPUNIT_ASSERT(listener.wasCalled());
}

void TestG2TreeView::testPostDestroyMessageOnAddItem()
{
  PostMessage(view->m_hWnd, WM_CLOSE, 0, 0);
  MSG msg;
  while (PeekMessage(&msg, view->m_hWnd, 0, 0, PM_NOREMOVE))
  {
    if (!view->AddItem(0, 0)) break;
  }
}

void TestG2TreeView::testShowToolTip()
{
  HTREEITEM hItem,hSubItem; 
  
  view->InsertTreeNodesToControl(0, _T("Test Tree Control"), 11, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 1"), 1, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 2"), 2, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 3"), 3, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 4"), 4, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 5"), 5, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 6"), 6, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 7"), 7, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 8"), 8, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 9"), 9, 0, -1, -1);
  view->InsertTreeNodesToControl(11, _T("Test Tree note 10"), 10, 0, -1, -1);
  
  HTREEITEM hRootItem = view->GetRootItem();
  view->Expand(hRootItem, TVE_EXPAND);
  int nTreeNodeNum = 1;
  if (view->ItemHasChildren(hRootItem))
  {
	  HTREEITEM hNextItem;
	  HTREEITEM hChildItem = view->GetChildItem(hRootItem);

	  while (hChildItem != NULL)
	  {
		  char strToolTip[100];
          sprintf(strToolTip, "This is tooltip of tree node %d", nTreeNodeNum);
		  CRect rc;
		  view->GetItemRect(hChildItem, &rc, TRUE);
		  view->ClientToScreen(&rc);
		  SetCursorPos(rc.left + 1, rc.top + 1);
		  view->ShowToolTip(hChildItem, CString(strToolTip));
		  nTreeNodeNum ++;
		  
		  hNextItem = view->GetNextItem(hChildItem, TVGN_NEXT);
		  hChildItem = hNextItem;
	  }
  }
}

void TestG2TreeView::testPaint()
{
	//Try to paint a empty tree
	PostMessage(view->m_hWnd, WM_PAINT, 0, 0);
	COLORREF color = view->GetBkColor();
	CPPUNIT_ASSERT(color);
}
