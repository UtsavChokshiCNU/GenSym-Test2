#include "stdafx.h"

#include <windows.h>
#include "TestNativeDialogs.h"

#include <multimon.h>

extern "C" BOOL GetMonitorRect(LPRECT prc, LPRECT rcWork);


CPPUNIT_TEST_SUITE_REGISTRATION(TestNativeDialogs);

BOOL CALLBACK CallbackScreen( HMONITOR hMonitor, HDC hdc, LPRECT prc, LPARAM lParam)
{
    MONITORINFO mi;
	RECT WindowRect, WorkArea;

	BOOL Result;
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hMonitor, &mi);

	WindowRect.bottom = mi.rcWork.bottom;
	WindowRect.left = mi.rcWork.left;
	WindowRect.right = mi.rcWork.right;
	WindowRect.top = mi.rcWork.top;

	CPPUNIT_ASSERT( GetMonitorRect(&WindowRect, &WorkArea) );

	Result = ( ( WindowRect.bottom <= WorkArea.bottom ) && ( WindowRect.left >= WorkArea.left ) && ( WindowRect.right <= WorkArea.right ) && ( WindowRect.top >= WorkArea.top ) );

	CPPUNIT_ASSERT( Result );

    return Result;
}


void TestNativeDialogs::testGetMonitorRect()
{
	HDC hdc;
    hdc = GetDC(NULL);
    EnumDisplayMonitors(hdc, NULL, CallbackScreen, 42);
    ReleaseDC(NULL,hdc);
}

void TestNativeDialogs::setUp()
{

}

void TestNativeDialogs::tearDown()
{

}
