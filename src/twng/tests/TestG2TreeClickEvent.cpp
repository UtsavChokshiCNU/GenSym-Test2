#include "stdafx.h"
#include "TestG2TreeClickEvent.h"
#include "MainFrm.h"
#include "Twng.h"
#include "NativeView.h"
#include "TreeView.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestG2TreeClickEvent);

void TestG2TreeClickEvent::testClickEvent()
{
	G2TreeView *pTV = NULL;

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

	pTV = new G2TreeView(1);
	pTV->Create(TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_EDITLABELS,
		WinSize(200,100), CWnd::FromHandle(hwnd), 1);

	HTREEITEM hRoot = pTV->AddItem(0, L"root1", TVF_CHILDREN, 0, 0, 0);
	for (int i=0; i<25; i++)
	{
		pTV->AddItem((int)hRoot, L"child", TVF_CHILDREN, 0, 0, 0);
	}
	
	CPPUNIT_ASSERT(pTV->GetCount()==26);

	pTV->SendMessage(WM_LBUTTONDOWN, 0, (LPARAM)hRoot);
    pTV->SendMessage(WM_LBUTTONUP, 0, (LPARAM)hRoot);
	pTV->SendMessage(WM_RBUTTONDOWN, 0, (LPARAM)hRoot);
	pTV->SendMessage(WM_RBUTTONUP, 0, (LPARAM)hRoot);
	Sleep(3000);
	pTV->SendMessage(WM_LBUTTONDOWN, 0, (LPARAM)hRoot);

	pTV->Clear();

	//TreeView handle has been deleted
	//delete pTV;

	DestroyWindow(hwnd);
}

void TestG2TreeClickEvent::setUp()
{
}

void TestG2TreeClickEvent::tearDown()
{
}
