#include "TestWindowClose.h"
#include "windows.h"
#include "msincls.h"

#define USE_PROTOTYPES

CPPUNIT_TEST_SUITE_REGISTRATION(TestWindowClose);

extern "C" HICON g2pvt_get_native_iconEx(int icon, int size);
extern "C" long int  g2ext_cache_cpointer(long);

void TestWindowClose::test()
{
	HWND hwnd = CreateWindow("BUTTON", "Dummy", WS_BORDER, 0,0,0,0, NULL, NULL, NULL, NULL);

	LPG2INFO info = (LPG2INFO)malloc(sizeof(G2INFO));
	memset(info, 0, sizeof(G2INFO));
	info->window_index = g2ext_cache_cpointer((long)hwnd);
	info->window_handle = -1;
	info->window_icon = -1;
	info->mdi_menu_index = -1;
	info->mdi_menu_nms_handle = -1;
	SetProp(hwnd,"G2_S_INFO",(HANDLE)info);

	HICON newSmallIcon = CreateIcon(NULL, 0, 0, 0, 0, NULL, NULL);
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)newSmallIcon);

	HICON newBigIcon = CreateIcon(NULL, 0, 0, 0, 0, NULL, NULL);
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)newBigIcon);

	g2pvt_free_window_info(hwnd);

	HICON hIcon = (HICON)SendMessage(hwnd, WM_SETICON, ICON_SMALL, NULL);
	CPPUNIT_ASSERT(!hIcon);

	hIcon = (HICON)SendMessage(hwnd, WM_SETICON, ICON_BIG, NULL);
	CPPUNIT_ASSERT(!hIcon);

	DestroyWindow(hwnd);
}

void TestWindowClose::setUp()
{
}

void TestWindowClose::tearDown()
{
}
