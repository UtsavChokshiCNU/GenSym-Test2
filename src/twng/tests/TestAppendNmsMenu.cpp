#include "stdafx.h"
#include "TestAppendNmsMenu.h"

#include "Twng.h"
#include "MainFrm.h"

extern "C" long g2ext_nms_create_menu(long popup_p, unsigned short *result);
extern "C" long g2ext_nms_append_menu(long menu_index, long flags, long nId, long submenu_index,
									  long wide, LPWSTR label, long fg, long bg);
extern long nLastMenuId;


CPPUNIT_TEST_SUITE_REGISTRATION(TestAppendNmsMenu);

void TestAppendNmsMenu::test()
{
	unsigned short result[2];
	long menu_index = g2ext_nms_create_menu(1, result);
	long sub_menu_index = g2ext_nms_create_menu(1, result);

	g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_CLOSE, sub_menu_index, 0, L"Close", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_CLOSEALL, sub_menu_index, 0, L"CloseAll", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, 1800, sub_menu_index, 0, L"aaa", -1, -1);

	CPPUNIT_ASSERT(nLastMenuId == TWPRO_CLOSEALL);

	g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_CASCADE, sub_menu_index, 0, L"Close", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_TILE_VERTICALLY, sub_menu_index, 0, L"CloseAll", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, 1800, sub_menu_index, 0, L"bbb", -1, -1);

	CPPUNIT_ASSERT(nLastMenuId == TWPRO_TILE_VERTICALLY);

	g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_CLOSE, sub_menu_index, 0, L"Close", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_TILE_HORIZONTALLY, sub_menu_index, 0, L"CloseAll", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, 1800, sub_menu_index, 0, L"bbb", -1, -1);

	CPPUNIT_ASSERT(nLastMenuId == TWPRO_TILE_HORIZONTALLY);
}

void TestAppendNmsMenu::setUp()
{
}

void TestAppendNmsMenu::tearDown()
{
}
