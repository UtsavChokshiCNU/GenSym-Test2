#include "ClipboardTest.h"

#if defined(MSWINDOWS)
#include <windows.h>
#else
#include <X11/Xlib.h>
#include "graphics.h"
#endif

CPPUNIT_TEST_SUITE_REGISTRATION(ClipboardTest);

void ClipboardTest::setUp()
{
    No_window = 0;
    g2ext_initialize_g2pointers();
	
#if defined(MSWINDOWS)
    HWND hwnd = CreateWindow("BUTTON", "ClipBoardTest", WS_BORDER, 0,0,0,0, NULL, NULL, NULL, NULL);
   _window_index = g2ext_cache_cpointer((long)hwnd);
#else
   Display *d;
   Window w;
   XEvent e;
   char *msg = "Hello, World!";
   int s;
 
   d = XOpenDisplay(":1");
   if (d == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(1);
   }
 
   s = DefaultScreen(d);
   w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 500, 500, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);

   GensymXWindow *gwindow = MakeInstance(GensymXWindow);
   gwindow->xwindow = w;
   gwindow->display_ptr = d;
   _window_index = g2ext_cache_cpointer ((long)gwindow);
#endif	

}

void ClipboardTest::tearDown()
{   
#if defined(MSWINDOWS)
    HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(_window_index);
    DestroyWindow(hwnd);
    g2ext_decache_g2pointer(_window_index);
#else
    GensymXWindow *gwindow = (GensymXWindow*)g2ext_map_g2pointer_to_cpointer(_window_index);
    XCloseDisplay(gwindow->display_ptr);
    g2ext_decache_g2pointer(_window_index);	
#endif
}

void ClipboardTest::test_g2ext_x11_write_read_cut_buffer()
{
    char *manipulatedText = "Copy Me !!!";
    long length = strlen(manipulatedText);
    char buffer[1024];

    long write_result = g2ext_x11_write_cut_buffer(_window_index, manipulatedText, length);
    
    long read_result = g2ext_x11_read_cut_buffer(_window_index, buffer, 1024);

    CPPUNIT_ASSERT(strcmp(buffer, manipulatedText) == 0);
}

void ClipboardTest::test_g2ext_write_read_clipboards()
{    
    char *	     latin_1_string = "Sample text to be copied";
    long             latin_1_string_length = strlen(latin_1_string);
    char *           compound_text_string = NULL;
    long             compound_text_string_length = 0;
    unsigned short  *unicode_text_string = (unsigned short *)L"ĤÈ Ƞȩθ ϐՅ لنمق ѰҨДχ ʆʛ";
    long             unicode_text_string_length = 22;

    long write_result = g2ext_write_clipboards (
				_window_index,
				latin_1_string,
				latin_1_string_length,
				compound_text_string,
				compound_text_string_length,
				unicode_text_string,
				unicode_text_string_length
			    );

    CPPUNIT_ASSERT(write_result == 24);

    char	   latin_1_buffer[1024];
    char       compound_text_buffer[1024];
    unsigned short    unicode_text_buffer[1024];
    unsigned short result_wide_buffer[3];

    long read_result = g2ext_read_clipboards (
				    _window_index,
				    latin_1_buffer,
				    1024,
				    1L,
				    compound_text_buffer,
				    1024,
				    0L,
				    unicode_text_buffer,
				    1024,
				    1L,
				    result_wide_buffer
				   );
	
    CPPUNIT_ASSERT( read_result == 1 );

    CPPUNIT_ASSERT( result_wide_buffer[0] == 24 );
    CPPUNIT_ASSERT( result_wide_buffer[2] == 22 );

    CPPUNIT_ASSERT( strcmp(latin_1_buffer, latin_1_string) == 0 );
    for(int i=0; i< unicode_text_string_length;++i)
    {
      CPPUNIT_ASSERT( unicode_text_buffer[i] == unicode_text_string[i] );
    }

}

