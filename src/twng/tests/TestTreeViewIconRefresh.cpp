#include "stdafx.h"
#include "TestTreeViewIconRefresh.h"
#include "MainFrm.h"
#include "Twng.h"
#include "NativeView.h"
#include "TreeView.h"

extern "C" HIMAGELIST g2pvt_get_image_list(int);
extern "C" void g2pvt_refresh_native_icon(int native_icon, int where);

CPPUNIT_TEST_SUITE_REGISTRATION(TestTreeViewIconRefresh);

void TestTreeViewIconRefresh::test()
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

	pTV->SetImageList(CImageList::FromHandle(g2pvt_get_image_list(16)), TVSIL_NORMAL);

	pTV->m_g2pointer = SavePtr(pTV->m_hWnd);

	HTREEITEM hRoot = pTV->AddItem(0, L"root1", TVF_CHILDREN, 0, 0, 0);
	for (int i=0; i<2500; i++)
	{
		pTV->AddItem((int)hRoot, L"child", TVF_CHILDREN, 0, 0, 0);
	}

	CPPUNIT_ASSERT(pTV->GetCount()==2501);

	BOOL bPass = FALSE;

	//every 5 seconds, refresh native icons to test whether TWNG hang up.
	for (i=0; i<10; i++)
	{
		g2pvt_refresh_native_icon(0, 0xF0);
		Sleep(5000);
	}

	bPass = TRUE;

	CPPUNIT_ASSERT(bPass);

	pTV->Clear();

	//TreeView handle has been deleted
	//delete pTV;

	DestroyWindow(hwnd);
}

void TestTreeViewIconRefresh::setUp()
{
}

void TestTreeViewIconRefresh::tearDown()
{
}
