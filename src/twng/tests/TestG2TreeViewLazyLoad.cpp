#include "stdafx.h"
#include "TestG2TreeViewLazyLoad.h"
#include "twng.h"
#include "MainFrm.h"
#include "NativeView.h"
#include "TreeView.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestG2TreeViewLazyLoad);


void TestG2TreeViewLazyLoad::test()
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

	HWND hwnd = CreateWindow(L"TestTree", L"Test Tree View", WS_OVERLAPPEDWINDOW, 0,0,800,600, NULL, NULL, NULL, NULL);

	G2TreeView* pTreeView = new G2TreeView(1);
	pTreeView->Create(TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_EDITLABELS,
		WinSize(300,500), CWnd::FromHandle(hwnd), 1);

	pTreeView->SetRedraw(FALSE);
	WCHAR szLabel[64];
	for (int i=0; i<20000; i++)
	{
		_stprintf(szLabel, _T("Test tree node%d."), i);
		pTreeView->InsertTreeNodesToControl(0, szLabel, 0, 0, -1, -1);
		pTreeView->AddItem(0, szLabel);
	}
	pTreeView->SetRedraw(TRUE);

	// nodes count should be MAX_PARTITION_COUNT at initializtion phase
	pTreeView->SendMessage(WM_KEYDOWN, VK_HOME, 0);
	CPPUNIT_ASSERT(pTreeView->GetLoadedNodesCount() == MAX_PARTITION_COUNT);

	// don't load next block nodes
	UINT nVisibleCount = pTreeView->GetVisibleCount();
	for (int i=0; i<MAX_LOADNODE_COUNT-nVisibleCount; ++i)
		pTreeView->SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
	CPPUNIT_ASSERT(pTreeView->GetLoadedNodesCount() == MAX_PARTITION_COUNT);

	// should load next block nodes
	UINT nBeforeCount = pTreeView->GetLoadedNodesCount();
	pTreeView->SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
	CPPUNIT_ASSERT(pTreeView->GetLoadedNodesCount() == nBeforeCount + MAX_LOADNODE_COUNT);

	// don't load next block nodes
	for (int i=0; i<MAX_LOADNODE_COUNT-nVisibleCount; ++i)
		pTreeView->SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
	CPPUNIT_ASSERT(pTreeView->GetLoadedNodesCount() == nBeforeCount + MAX_LOADNODE_COUNT);

	// should load next block nodes
	nBeforeCount = pTreeView->GetLoadedNodesCount();
	SCROLLINFO si = {0};
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_POS;
	si.nPos = nBeforeCount - MAX_LOADNODE_COUNT - nVisibleCount + 1;
	SetScrollInfo( pTreeView->m_hWnd, SB_VERT, &si, TRUE);
	DWORD dwPara = MAKELONG(SB_THUMBPOSITION, 0);
	pTreeView->SendMessage(WM_VSCROLL, (WPARAM)dwPara, 0);
	CPPUNIT_ASSERT(pTreeView->GetLoadedNodesCount() == nBeforeCount + MAX_LOADNODE_COUNT);


	pTreeView->DestroyWindow();
	//TreeView handle has been deleted
	//delete treeView;

	DestroyWindow(hwnd);
}

void TestG2TreeViewLazyLoad::setUp()
{
}

void TestG2TreeViewLazyLoad::tearDown()
{
}
