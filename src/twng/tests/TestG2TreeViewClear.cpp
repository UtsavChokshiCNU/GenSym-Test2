#include "stdafx.h"
#include "TestG2TreeViewClear.h"
#include "twng.h"
#include "MainFrm.h"
#include "NativeView.h"
#include "TreeView.h"
#include "Psapi.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestG2TreeViewClear);


void TestG2TreeViewClear::test()
{
	long lBefore = 0;
	long lAfter = 0;

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

	PROCESS_MEMORY_COUNTERS pmc;
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);

	if ( ::GetProcessMemoryInfo( ::GetCurrentProcess(), &pmc, sizeof(pmc)) )
	{
		lBefore = pmc.WorkingSetSize;
	}

	G2TreeView* pTreeView = new G2TreeView(1);
	pTreeView->Create(TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_EDITLABELS,
		WinSize(200,100), CWnd::FromHandle(hwnd), 1);

	pTreeView->DestroyWindow();

	if ( ::GetProcessMemoryInfo( ::GetCurrentProcess(), &pmc, sizeof(pmc)) )
	{
		lAfter = pmc.WorkingSetSize;
	}
	CPPUNIT_ASSERT(lBefore == lAfter);

	DestroyWindow(hwnd);
}

void TestG2TreeViewClear::setUp()
{

}

void TestG2TreeViewClear::tearDown()
{
}
