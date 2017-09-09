#include "TestG2extInitialize.h"
#include "windows.h"
#include "msincls.h"

#define USE_PROTOTYPES

CPPUNIT_TEST_SUITE_REGISTRATION(TestG2extInitialize);

typedef long int G2pointer;

extern "C" long g2ext_x11_initialize(LPSTR display_spec_string, LPSTR window_name, LPSTR icon_name,
								long desired_width, long desired_height,
								long desired_x0_in_display, long desired_y0_in_display,
								long backing_store_p,  
								long private_colormap_p, 
								long frame_type);

extern "C" int ne_use_sck;

void TestG2extInitialize::testWindowClassCreation()
{
	WNDCLASSW wndstr;
	BOOL result = 0;

	g2ext_x11_initialize(":0", "G2", "G2", -1, -1, -1, -1, 1, 0, 4);
	HMODULE handle = GetModuleHandle(NULL);
	result = GetClassInfoW(handle, GensymWindowClass, &wndstr);
	CPPUNIT_ASSERT(result != 0);
}

void TestG2extInitialize::testNtEventsAreUsed()
{
	CPPUNIT_ASSERT(ne_use_sck);
	g2ext_x11_initialize(":0", "G2", "G2", -1, -1, -1, -1, 1, 0, 4);
	CPPUNIT_ASSERT(!ne_use_sck);
}

void TestG2extInitialize::setUp()
{
	ne_use_sck = TRUE;
}

void TestG2extInitialize::tearDown()
{
}
