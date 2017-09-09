#include "stdafx.h"
#include "TestMoreWindowsMenu.h"

#include "Twng.h"
#include "MainFrm.h"

extern "C" long g2ext_nms_create_menu(long popup_p, unsigned short *result);
extern "C" long g2ext_nms_append_menu(long menu_index, long flags, long nId, long submenu_index,
									  long wide, LPWSTR label, long fg, long bg);


CPPUNIT_TEST_SUITE_REGISTRATION(TestMoreWindowsMenu);

void TestMoreWindowsMenu::test()
{
	unsigned short result[2];
	long menu_index = g2ext_nms_create_menu(1, result);
	long sub_menu_index = g2ext_nms_create_menu(1, result);

	g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_CLOSE, sub_menu_index, 0, L"Close", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_CLOSEALL, sub_menu_index, 0, L"CloseAll", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, 1800, sub_menu_index, 0, L"aaa", -1, -1);
	long initResult = g2ext_nms_append_menu(menu_index, 0, TWPRO_MORE_WINDOWS, sub_menu_index, 0, L"More Window...", -1, -1);
	CPPUNIT_ASSERT_EQUAL(5L, initResult);

	CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
	CXTPControl* pControl = pMenu->GetControls()->FindControl(TWPRO_MORE_WINDOWS); //"More Windows..." menu item has been appended
	CPPUNIT_ASSERT(pControl != NULL);

	initResult = g2ext_nms_append_menu(menu_index, MF_POPUP, TWPRO_TILE_VERTICALLY, sub_menu_index, 0, L"Tile Vertically", -1, -1);
	CPPUNIT_ASSERT_EQUAL(6L, initResult);

	pControl = pMenu->GetControls()->FindControl(XTP_ID_WINDOWLIST); //XTP_ID_WINDOWLIST menu item has been appended
	CPPUNIT_ASSERT(pControl != NULL);

	g2ext_nms_append_menu(menu_index, MF_POPUP, 1900, sub_menu_index, 0, L"bbb", -1, -1);
	g2ext_nms_append_menu(menu_index, MF_POPUP, 2000, sub_menu_index, 0, L"bbb", -1, -1);
	pControl = pMenu->GetControls()->FindControl(2000); 
	CPPUNIT_ASSERT(pControl != NULL);
}

void TestMoreWindowsMenu::setUp()
{
}

void TestMoreWindowsMenu::tearDown()
{
}
