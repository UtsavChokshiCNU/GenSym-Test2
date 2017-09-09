#include "testAppExit.h"
#include "windows.h"
#include "msincls.h"

#define USE_PROTOTYPES

//CPPUNIT_TEST_SUITE_REGISTRATION(TestAppExit);

typedef long int G2pointer;

extern "C" long g2ext_create_argument_list(int argc, char* argv[]);
extern "C" void g2ext_initialize_g2pointers();
extern "C" long g2ext_x11_initialize(LPSTR display_spec_string, LPSTR window_name, LPSTR icon_name,
								long desired_width, long desired_height,
								long desired_x0_in_display, long desired_y0_in_display,
								long backing_store_p,  
								long private_colormap_p, 
								long frame_type);
extern "C" void g2ext_exit_from_lisp(long exit_status);
extern "C" void ne_initialize_event_handling();
extern "C" void g2pvt_send_event (HWND hwnd, int handle, int eventtype, long x, long y, long width, long height, long key_code, long key_bits, LPWSTR value);
extern "C" long g2ext_cache_cpointer(long);
extern "C" void g2ext_uninitialize_g2pointers ();
extern "C" G2pointer ne_unmap_fd(int fd);
extern "C" int g2ext_lookup_socket_index (unsigned);
extern "C" void g2ext_deallocate_socket_index(unsigned);

void TestAppExit::test()
{
	BOOL runned = FALSE;
	int i = 0;
	long l_tmp, l_index = 0;

	for(; i<10; i++)
	{
		l_index = g2ext_cache_cpointer(i);
	}

	char* argv[] = {"TWNG.EXE"};
	g2ext_create_argument_list(1, argv);
	g2ext_initialize_g2pointers();
	ne_initialize_event_handling();

	long window_index = g2ext_x11_initialize(":0", "Telewindows Client", "TW", -1, -1, -1, -1, 1, 0, 4);
	CPPUNIT_ASSERT(window_index > 0);

	for(i=0; i< 10; i++)
		g2pvt_send_event(hwndMain, window_index, 9, 0, 0, 0, 0, 0, 0, NULL);

	g2ext_window_destroyed = TRUE;
	g2ext_exit_from_lisp(0);

	l_tmp = ne_unmap_fd(l_index);
	CPPUNIT_ASSERT(l_tmp == -1);

	l_tmp = g2ext_lookup_socket_index(l_index);
	CPPUNIT_ASSERT(l_tmp == -1);

	g2ext_deallocate_socket_index(l_index);

	runned = TRUE;

	CPPUNIT_ASSERT(runned);
}

void TestAppExit::setUp()
{
}

void TestAppExit::tearDown()
{
}
