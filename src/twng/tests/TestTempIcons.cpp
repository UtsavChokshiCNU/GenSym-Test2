#include "stdafx.h"
#include "TestTempIcons.h"
#include "dyndlgs.h"

#define TEMP_ICON_FLAG (1<<21)
#define SAVE_NATIVE_ICON 3

extern "C" {
	long g2ext_create_pixmap(long window_index, long width, long height, long depth, long irregular);
	void g2ext_reclaim_pixmap(long pixmap_index);

	long g2ext_x11_manage_native_icons(long window_index, long opcode,
				   long handle, long width, long height,
				   long pixmap_index, long mask_index);

	HICON g2pvt_get_native_icon(int icon);

	extern int No_window;
}

void g2pvt_clear_mfc_control_data (CONTROLITEM *pcontrol);

CPPUNIT_TEST_SUITE_REGISTRATION(TestTempIcons);

void TestTempIcons::test(void (TestTempIcons::*func)())
{
	CPPUNIT_ASSERT(func != NULL);

	CPPUNIT_ASSERT(m_nPixmap > 1);
	CPPUNIT_ASSERT(m_nPixmapMask > 1);

	HICON hIcon = g2pvt_get_native_icon(m_nIcon);
	CPPUNIT_ASSERT(hIcon == NULL);

	g2ext_x11_manage_native_icons(0, SAVE_NATIVE_ICON, m_nIcon, 100, 100, m_nPixmap, m_nPixmapMask);

	(this->*func)();

	hIcon = g2pvt_get_native_icon(m_nIcon);
	CPPUNIT_ASSERT(hIcon == NULL);
}


void TestTempIcons::testTempIconFunc()
{
	HICON hIcon = g2pvt_get_native_icon(m_nIcon);
	CPPUNIT_ASSERT(hIcon != NULL);

	DestroyIcon(hIcon);
}

void TestTempIcons::testTempIcon()
{
	test(&TestTempIcons::testTempIconFunc);
}

void TestTempIcons::testIconControlFunc()
{
	wchar_t buffer[0x100];
	swprintf(buffer, L"%d", m_nIcon);

	CONTROLITEM item;
	memset(&item, 0, sizeof(item));

	item._type = ctIcon;
	item._mText = buffer;

	g2pvt_clear_mfc_control_data(&item);
}

void TestTempIcons::testIconControl()
{
	test(&TestTempIcons::testIconControlFunc);
}


void TestTempIcons::setUp()
{
	m_nTmpWindow = No_window;
	No_window = 0;

	m_nIcon = 0x100 | TEMP_ICON_FLAG;

	m_nPixmap = g2ext_create_pixmap(0, 100, 100, 24, 1);
	m_nPixmapMask = g2ext_create_pixmap(0, 100, 100, 24, 1);
}

void TestTempIcons::tearDown()
{
	g2ext_reclaim_pixmap(m_nPixmap);
	g2ext_reclaim_pixmap(m_nPixmapMask);

	No_window = m_nTmpWindow;
}
