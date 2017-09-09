#include "stdafx.h"
#include "TestG2TreeViewScroll.h"
#include "twng.h"
#include "MainFrm.h"
#include "NativeView.h"
#include "TreeView.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestG2TreeViewScroll);


void TestG2TreeViewScroll::test()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetResourceHandle();

	wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc      = ::DefWindowProc;
	wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
	wndcls.hInstance        = hInst;
	wndcls.hIcon            = NULL;
	wndcls.hCursor          = 0;
	wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
	wndcls.lpszMenuName     = NULL;
	wndcls.lpszClassName    = L"TestTree";

	AfxRegisterClass(&wndcls);

	HWND hwnd = CreateWindow(L"TestTree", L"Test Tree View", WS_OVERLAPPEDWINDOW, 0,0,400,300, NULL, NULL, NULL, NULL);

	G2TreeView* pTreeView = new G2TreeView(1);
	pTreeView->Create(TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_EDITLABELS,
		WinSize(200,100), CWnd::FromHandle(hwnd), 1);

	pTreeView->SetRedraw(FALSE);
	for (int i=0; i<131000; i++)
	{
		pTreeView->AddItem(0, 0);
	}
	pTreeView->SetRedraw(TRUE);

	pTreeView->SendMessage(WM_KEYDOWN, VK_HOME, 0);

	SCROLLINFO info;
	pTreeView->GetScrollInfo(SB_VERT, &info);
	CPPUNIT_ASSERT(info.nPos == 0);

	pTreeView->SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
	pTreeView->GetScrollInfo(SB_VERT, &info);
	CPPUNIT_ASSERT(info.nPos == 1);

	pTreeView->SendMessage(WM_VSCROLL, SB_LINEUP, 0);
	pTreeView->GetScrollInfo(SB_VERT, &info);
	CPPUNIT_ASSERT(info.nPos == 0);

	pTreeView->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_THUMBPOSITION, 70000), 0);
	pTreeView->GetScrollInfo(SB_VERT, &info);
	CPPUNIT_ASSERT(info.nPos == info.nTrackPos);

	pTreeView->DestroyWindow();
	//TreeView handle has been deleted
	//delete treeView;

	DestroyWindow(hwnd);
}

void TestG2TreeViewScroll::setUp()
{
}

void TestG2TreeViewScroll::tearDown()
{
}
