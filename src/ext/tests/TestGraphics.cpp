#include "TestGraphics.h"
#include <stdio.h>
#include <windows.h>


CPPUNIT_TEST_SUITE_REGISTRATION(TestGraphics);

extern "C" {
	#include "msincls.h"

	long g2ext_get_pixel(long window_index, char *lpszColor, long extended_color_p);
	long int g2ext_cache_cpointer(long ptr);
	void g2ext_decache_g2pointer(long int);
	long g2ext_map_g2pointer_to_cpointer(long int g2ptr);

	extern int No_window;
}

// defined in TestModalLoop
extern void CreateTestWindow();


void TestGraphics::testGetPixel()
{
	HWND hWnd = (HWND) g2ext_map_g2pointer_to_cpointer(nWindowIndex);
	CPPUNIT_ASSERT(IsWindow(hWnd));

	testTextRGB(RGB(0, 0, 0));
	testTextRGB(RGB(0xff, 0xff, 0xff));
	testTextRGB(RGB(0xff, 0x00, 0xff));

	testTextRGB(g2ext_get_pixel(nWindowIndex, "red", 0));
	testTextRGB(g2ext_get_pixel(nWindowIndex, "green", 0));
	testTextRGB(g2ext_get_pixel(nWindowIndex, "blue", 0));
}

void TestGraphics::setUp()
{
	hwndFrame = NULL;
	CreateTestWindow();

	nWindowIndex = g2ext_cache_cpointer((long) hwndFrame);

	nNoWindow = No_window;
	No_window = FALSE;
}

void TestGraphics::tearDown()
{
	DestroyWindow(hwndFrame);
	hwndFrame = NULL;
	g2ext_decache_g2pointer(nWindowIndex);

	No_window = nNoWindow;
}

void TestGraphics::testTextRGB(long rgb)
{
	char color[0x100];

	sprintf(color, "#%2x%2x%2x", GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));

	for (int i = 0; i < strlen(color); i++)
	{
		if (color[i] == ' ')
			color[i] = '0';
	}

	int newColor = g2ext_get_pixel(nWindowIndex, color, 0);

	CPPUNIT_ASSERT(newColor == rgb);
}
