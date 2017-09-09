#include "TestMaskBitmap.h"
#include <windows.h>

#define USE_PROTOTYPES

CPPUNIT_TEST_SUITE_REGISTRATION(TestMaskBitmap);

extern "C" void CopyMaskBitmap(HBITMAP src, HBITMAP dst);

void TestPixel(HBITMAP hbm, int x, int y, COLORREF color, bool eq)
{
	HDC dc = CreateCompatibleDC(NULL);

	CPPUNIT_ASSERT(dc != NULL);

	HBITMAP old_bitmap = (HBITMAP) SelectObject(dc, hbm);

	COLORREF col = GetPixel(dc, x, y);
	CPPUNIT_ASSERT(col != CLR_INVALID);

	CPPUNIT_ASSERT(eq ? col == color : col != color);

	SelectObject(dc, old_bitmap);
	DeleteDC(dc);
}

void TestMaskBitmap::test()
{
	const int width = 100;
	const int height = 100;

	COLORREF white = RGB(0xFF, 0xFF, 0xFF);
	RECT rect = {0, 0, width, height};

	HDC mainDC = GetDC(GetDesktopWindow());

	// Create test bitmap
	HBITMAP hbm = CreateCompatibleBitmap(mainDC, width, height);
	CPPUNIT_ASSERT(hbm != NULL);

	HDC dc = CreateCompatibleDC(mainDC);
	CPPUNIT_ASSERT(dc != NULL);

	HBITMAP old_bitmap = (HBITMAP) SelectObject(dc, hbm);

	HBRUSH brush = CreateSolidBrush(white);
	CPPUNIT_ASSERT(brush != NULL);
	FillRect(dc, &rect, brush);
	DeleteObject(brush);

	SelectObject(dc, old_bitmap);
	DeleteDC(dc);

	// Test pixel
	TestPixel(hbm, width / 2, height / 2, white, true);

	// Create new bitmap
	HBITMAP hbm_new = CreateCompatibleBitmap(mainDC, width, height);
	CPPUNIT_ASSERT(hbm_new != NULL);

	ReleaseDC(GetDesktopWindow(), mainDC);

	// Test
	CopyMaskBitmap(hbm, hbm_new);

	// Test pixel
	TestPixel(hbm_new, width / 2, height / 2, white, false);

	// Destroy
	DeleteObject(hbm);
	DeleteObject(hbm_new);
}
