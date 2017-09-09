/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      test-cprim.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +           John Valente, et. al.
 +
 + Description:  This file contains testing functions and is not normally
 +               part of the optimized libcprim.
 +               
 + 
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
 +   ??????? Function existence is questionable.
 +
 +   A function banner may contain the following: 
 +      Multiply Defined       Function appears multiple times, each definition
 +                             for an #ifdef specified platform.
 +      Conditionally Defined  Defined for some but not all platforms
 +      Mixed Ifdefs           Single definition for function containing
 +                             platform specific code #ifdef's.
 +
 + File Organization:
 +   Section:      TESTING FUNCTIONS - not documented
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <signal.h>
#include "cprim.h"
#include "graphics.h"


static int private_p = 0;
static char *xserver = NULL;
static long window_handle;
static int screen_depth;

KeySym last_event_keysym = NULL;


extern void ne_initialize_event_handling();

extern void g2ext_initialize_g2pointers();
extern long g2ext_map_g2pointer_to_cpointer ();
extern long g2ext_get_event ();

#ifdef XWINDOWS
/* get_gc is static to graphics.c */
extern GC g2ext_x11_get_gc (/* GensymXWindow *, int, int, int */);
#endif

extern long g2ext_x11_initialize(/* char *, char *, char *, long, long, long, long, long, long */);
extern long g2ext_x11_last_event_bits ();
extern long g2ext_x11_last_event_time ();
extern long g2ext_x11_last_expose_height ();
extern long g2ext_x11_last_expose_width ();
extern long g2ext_x11_last_expose_x_position ();
extern long g2ext_x11_last_expose_y_position ();
extern long g2ext_x11_last_mouse_x_position ();
extern long g2ext_x11_last_mouse_y_position ();
extern void g2ext_x11_make_xwindow_visible(/* long */);
extern long g2ext_x11_screen_depth (/* long */);


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
long g2int_open_fd_callback(fd)
    long fd;
{
    return 0L;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long g2int_close_fd_callback(fd)
    long fd;
{
    return 0L;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
long g2int_network_event_handler()
{
    return -1L;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
long g2int_not_writing_fd_callback()
{
    return -1L;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
long g2int_signal_handler_for_launch()
{
    return -1L;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
long g2int_writing_fd_callback()
{
    return -1L;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
long g2int_signal_handler()
{
    fprintf(stderr, "G2 internal signal handler called.\n");
    fflush(stderr);
    return -1L;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
long g2int_service_sigalrm_signal()
{
    return -1L;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long dlclose (h)
  void *h;
{
    return 0;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
long g2int_lisp_server_loop(msgsock, type)
  int msgsock;
  int type;
{
    return -1;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long g2int_run_trace_function()
{
    return 0;
}

long g2int_unix_command_callback()
{
    return 0;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Perhaps should make this stub closer to the actual implementation.
 *   Modifications:
 *****************************************************************************/
int g2int_x_error (error_code) 
  int error_code;
{
  fprintf(stderr, "Error %d from X server.\n", error_code);
  fflush(stderr);
  return -1;
}



/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void my_segv_handler (signo)
  int signo;
{
  fprintf(stderr, "Caught signal %d\n", signo);
  fflush(stderr);
  if ((signo == SIGBUS) || (signo == SIGSEGV)) {
    g2_print_backtrace();
    fflush(stdout);
    exit(-1);
  }
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void establish_signal_handlers ()
{
  int signo;

  for (signo=1; signo<32; signo++) {
    if ((signo != SIGKILL) && (signo != SIGSTOP)) {
      if (signal(signo, my_segv_handler) == SIG_ERR)
	fprintf(stderr, "Could not establish signal handler for signal %d.\n", signo);
    }
  }
  fflush(stderr);
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long cprim_test_initialize (argc, argv)
  int argc;
  char **argv;
{
  xserver = (char *) getenv("DISPLAY");
  if (!xserver) xserver = ":0.0";

  g2ext_verify_operating_system();
  g2ext_initialize_g2pointers();
  ne_initialize_event_handling();
  window_handle = g2ext_x11_initialize(xserver, "Test", "test", 200, 200, 800, 0, 1, private_p);
  if (window_handle) {
    fprintf(stderr, "X server connection established.  handle = %d\n", window_handle);
  } else {
    fprintf(stderr, "Could not connect to X server %s\n", xserver);
  }

  establish_signal_handlers();
  g2ext_x11_set_debug_mode(window_handle);
  return window_handle;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
int event_handling_loop ()
{ 
    long event;
    int code, detail, dump;
    int shift = X11_NUMBER_OF_BITS_IN_EVENT_CODES;
    int mask = (1<<shift) - 1;
    int keep_running = 1;

    while(keep_running) {
      event = g2ext_get_event(window_handle);
      code = event & mask;
      detail = event>>shift;
      dump = 0;

      if (event == X11_NO_MORE_EVENTS)
	;
      else
	{
	  switch (code)
	    {
	    case X11_NULLEVENT:
	      /* Null events are usually dead key presses. */
	      printf("NullEvent");

	    case X11_KEYPRESS:
	      printf("Keypress");
	      printf(" %d (", detail&KEY_INDEX_BITS);
	      if (detail&X11_CONTROL_BIT)
		printf("control+");
	      if (detail&X11_META_BIT)
		printf("meta+");
	      if (detail&X11_ALTERNATE_BIT)
		printf("alt+");
	      if (detail&X11_SHIFT_BIT)
		printf("shift+");
	      if (detail&X11_CAPS_LOCK_BIT)
		printf("caps+");
	      if (detail&X11_DOUBLE_BIT)
		printf("double+");
	      printf(")");
	      printf(" keysym %s,  ", XKeysymToString(last_event_keysym));
	      if (detail == 113) {
		printf("\nThat's a q all right\n");
		keep_running = 0;
	      }
	      dump=1;
	      break;

	    case X11_BUTTON_PRESS:
	      printf("ButtonPress");
	      dump=1;
	      break;

	    case X11_BUTTON_RELEASE:
	      printf("ButtonRelease");
	      dump=1;
	      break;

	    case X11_POINTER_MOTION:
	      printf("ButtonMotion");
	      dump=1;
	      break;

	    case X11_EXPOSURE:
	      printf("Expose");
	      printf(" x %d, y %d, width %d, height %d",
		     g2ext_x11_last_expose_x_position(window_handle),
		     g2ext_x11_last_expose_y_position(window_handle),
		     g2ext_x11_last_expose_width(window_handle),
		     g2ext_x11_last_expose_height(window_handle));
	      break;

	    case X11_RESHAPE:
	      printf("Reshape");
	      printf(" width %d, height %d",
		     g2ext_x11_last_expose_width(window_handle),
		     g2ext_x11_last_expose_height(window_handle));
	      break;

	    case X11_ENTER:
	      printf("Enter");
	      break;

	    case X11_LEAVE:
	      printf("Leave");
	      break;

	    default:
	      printf("??? %d", event);
	    }

	  if (dump)
	    printf(" x %d, y %d, bits %d, time %d",
		   g2ext_x11_last_mouse_x_position(window_handle),
		   g2ext_x11_last_mouse_y_position(window_handle),
		   g2ext_x11_last_event_bits(window_handle),
		   g2ext_x11_last_event_time(window_handle));
	  printf("\n");
	  fflush(stdout);
	}
    }
}



#ifdef TESTMAIN

#include "gensym-tile.xbm"
#include "phone.xbm"


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
int main(argc, argv)
  int argc;
  char **argv;
{
  GensymXWindow *gwindow;
  Display *display;
  Window window;
  GC gc;
  Pixmap bitmap, pixmap;
  Cursor cursor;
  int depth;
  int white, gray;

  window_handle = cprim_test_initialize(argc, argv);

  gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_handle);
  display = gwindow->display_ptr;
  window =  gwindow->xwindow;

  /* display = NULL; */
  XSetWindowBackground(display, window, 4);
  XSetWindowBorderWidth(display, window, 10);

  /* Give it the gensym tiling pattern */
  depth = g2ext_x11_screen_depth(window_handle);
  bitmap = XCreateBitmapFromData (display, window, gensym_bits, gensym_width, gensym_height);
  if (depth == 1)
    XSetWindowBackgroundPixmap(display, window, bitmap);
  else
    {
      white = g2ext_get_pixel(window_handle, "white", 0);
      gray = g2ext_get_pixel(window_handle, "gray", 0);

      gc = g2ext_x11_get_gc(gwindow, white, gray, X11_COPY);

      pixmap = XCreatePixmap(display, window, gensym_width, gensym_height, depth);
      XCopyPlane(display, bitmap, pixmap,
	       gc, 0, 0, gensym_width, gensym_height, 0, 0, 1);
      XSetWindowBackgroundPixmap(display, window, pixmap);
    }


  /* Extended color */
  {
    int p1, p2;

    p1 = g2ext_get_pixel(window_handle, "#323232", 1);
    p2 = g2ext_get_pixel(window_handle, "#505050", 1);
    printf("Extended pixels %d and %d\n", p1, p2);

#ifdef MSWINDOWS
    free_pixel(window_handle, p1);
#endif

    p1 = g2ext_get_pixel(window_handle, "#323232", 1);
    p2 = g2ext_get_pixel(window_handle, "#505050", 1);
    printf("Extended pixels %d and %d\n", p1, p2);

  }

  {
    static XColor fg, bg;
    int w, h;

    bitmap = XCreateBitmapFromData (display, window, phone_bits, phone_width, phone_height);

    /* The limit appears to be 32x32 pixels for a cursor. */

    XQueryBestCursor(display, window, phone_width, phone_height, &w, &h);
    printf("W = %d, H = %d\n", w, h);
    fflush(stdout);

    fg.red = 255;
    cursor = XCreatePixmapCursor(display, bitmap, bitmap, &fg, &bg, 0, 0);
    if (cursor != (Cursor) NULL)
      XDefineCursor(display, window, cursor);
  }

  g2ext_x11_make_xwindow_visible(window_handle);


}

#endif



/*****************************************************************************
 * Orangeball Test
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
#ifdef ORANGEBALL
#  define DEPTH_BIT_COUNT   24
#  define LAME_COLORMAP_SIZE 256
#  define RGB_SHIFT_FOR_HANDLE 12
/* Shift the rgb value 12 bits to get some fairly random lower bits.
   I don't want to just use the red value, for instance. */

#  define MAP_RGB_TO_COLORMAP_HANDLE(rgb) \
    ((unsigned char) (rgb >> RGB_SHIFT_FOR_HANDLE) & (LAME_COLORMAP_SIZE - 1))

/* The following array describes a gif of a little orange ball.  The numbers
   are packed bytes of red, green, and blue values.  The gif is 14x14 pixels,
   but the width is padded with two extra pixels, because the number of bytes
   in a scan line must be a multiple of four. */
unsigned char orangeball_truecolor[] =
{
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x7b, 0xa7, 0xc6, 0x42,
    0x94, 0xce, 0x10, 0x7c, 0xce, 0x10, 0x7c, 0xce, 0x42, 0x94, 0xce, 0x7b, 0xa7, 0xc6, 0xbf, 0xbf,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x63, 0xa1, 0xce, 0x00, 0x79, 0xd6, 0x00,
    0x91, 0xff, 0x00, 0x91, 0xff, 0x00, 0x95, 0xff, 0x00, 0x8b, 0xef, 0x00, 0x74, 0xc6, 0x63, 0xa1,
    0xce, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x7b, 0xa6, 0xc6, 0x00, 0x78, 0xce, 0x00, 0x91, 0xff, 0x10,
    0x97, 0xff, 0x31, 0xa6, 0xff, 0x08, 0x98, 0xff, 0x00, 0x87, 0xe7, 0x00, 0x74, 0xc6, 0x00, 0x5b,
    0x9c, 0x7b, 0xa6, 0xc6, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x42, 0x94, 0xce, 0x00, 0x91, 0xff, 0x08, 0x98, 0xff, 0x8c,
    0xc7, 0xff, 0xa5, 0xd1, 0xff, 0x10, 0x9b, 0xff, 0x00, 0x79, 0xd6, 0x00, 0x6b, 0xbd, 0x00, 0x56,
    0x94, 0x10, 0x54, 0x84, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x10, 0x7c, 0xce, 0x00, 0x95, 0xff, 0x08, 0x98, 0xff, 0x31,
    0xa6, 0xff, 0x21, 0xa3, 0xff, 0x08, 0x80, 0xd6, 0x00, 0x6b, 0xbd, 0x00, 0x5b, 0x9c, 0x00, 0x4b,
    0x84, 0x00, 0x35, 0x5a, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x10, 0x7c, 0xce, 0x00, 0x82, 0xde, 0x00, 0x87, 0xe7, 0x00,
    0x82, 0xde, 0x00, 0x78, 0xce, 0x00, 0x6a, 0xb5, 0x00, 0x5b, 0x9c, 0x00, 0x4b, 0x84, 0x00, 0x3a,
    0x63, 0x00, 0x35, 0x5a, 0xbf, 0xbf, 0xbf, 0xbd, 0xc3, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x42, 0x94, 0xce, 0x00, 0x6b, 0xbd, 0x00, 0x6b, 0xbd, 0x00,
    0x6e, 0xbd, 0x00, 0x65, 0xad, 0x00, 0x5b, 0x9c, 0x00, 0x4b, 0x84, 0x00, 0x33, 0x5a, 0x00, 0x2a,
    0x4a, 0x10, 0x48, 0x73, 0xbd, 0xc3, 0xc6, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x7b, 0xa6, 0xc6, 0x00, 0x56, 0x94, 0x00, 0x5b, 0x9c, 0x00,
    0x56, 0x94, 0x00, 0x4b, 0x84, 0x00, 0x43, 0x73, 0x00, 0x3a, 0x63, 0x00, 0x2b, 0x4a, 0x00, 0x2a,
    0x4a, 0x4a, 0x78, 0x9c, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x63, 0xa0, 0xce, 0x00, 0x3d, 0x6b, 0x00,
    0x3d, 0x6b, 0x00, 0x35, 0x5a, 0x00, 0x2a, 0x4a, 0x00, 0x2a, 0x4a, 0x00, 0x2a, 0x4a, 0x31, 0x66,
    0x8c, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbd, 0xc3, 0xc6, 0xbf, 0xbf, 0xbf, 0x7b, 0xa6, 0xc6, 0x10,
    0x48, 0x73, 0x00, 0x35, 0x5a, 0x00, 0x35, 0x5a, 0x10, 0x48, 0x73, 0x4a, 0x78, 0x9c, 0xbd, 0xc3,
    0xc6, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbd, 0xc3, 0xc6, 0xbf,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbd, 0xc3, 0xc6, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf,
    0xbf, 0xbd, 0xc3, 0xc6, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbd,
    0xc3, 0xc6, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbf, 0xbd, 0xc3, 0xc6, 0xbf, 0xbf,
    0xbf, 0xbf, 0xbf, 0xbf, 0xbd, 0xc3, 0xc6, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void output_info_about_pixmap(data, data_size, height, width, pixels_per_line)
  unsigned char *data;
  int data_size;
  int height;
  int width;
  int pixels_per_line;
{
    int line, over, npixel, clor, bytes;
    char mapping=' ';
    char my_lame_color_map[LAME_COLORMAP_SIZE];
    long pixval;
    unsigned char pixval_handle;

    /* Assume sizeof(unsigned char) == 1 */

    printf("\nOIAP: data = 0x%x; Data size = %d\n", 
	   (long) data, data_size);
    printf("height = %d, width = %d, pix_per_line = %d\n", 
	   height, width, pixels_per_line);

    /* Initialize lame color map to all zeros */
    for (clor=0; clor<LAME_COLORMAP_SIZE; clor++) my_lame_color_map[clor] = (char) 0;

    /* Spit out the data in hex bytes, and also set entries in lame color map
       to nonzero if the color is used */
    printf("bytes\n");
    for(line=0; line<height; line++) {
	for (over=0; over<pixels_per_line; over++) {
	    printf("0x%02x,", *(data+(line*pixels_per_line)+over));
	    putchar(((over % 16) == 15) ? '\n' : ' ');
	}
    }

    /* Show the data in pixel values */
    printf("\n\ncolor values:\n");
    for(line=0; line<height; line++) {
	for (over=0; over<(pixels_per_line/data_size); over++) {
	    npixel = ((pixels_per_line*line)+(over*data_size));
	    for (bytes=(data_size-1), pixval=0; bytes>=0; bytes--) {
		pixval = (pixval << 8) + *(data+npixel+bytes);
	    }
	    printf("0x%06x,", pixval);
	    pixval_handle = MAP_RGB_TO_COLORMAP_HANDLE(pixval);
	    if (my_lame_color_map[pixval_handle] == (char) 0) {
		my_lame_color_map[pixval_handle] = ++mapping;
	    }

	    putchar(((over % 8) == 7) ? '\n' : ' ');
	}
    }

    /* Spit out the data in a lame (random) ascii encoding */
    printf("\n\nstart\n");
    for(line=0; line<height; line++) {
	for (over=0; over<pixels_per_line; over+=data_size) {
	    npixel = ((pixels_per_line*line)+over);
	    for (bytes=(data_size-1), pixval=0; bytes>=0; bytes--)
		pixval = (pixval << 8) + *(data+npixel+bytes);
	    pixval_handle = MAP_RGB_TO_COLORMAP_HANDLE(pixval);
	    printf("%c", my_lame_color_map[pixval_handle]);
	}
	printf("\n");
    }
    printf("\n\n\n");
    fflush(stdout);
}



/*****************************************************************************
 * long compute_bytes_per_scan_line (width, depth)
 *
 *   Description: 
 *     
 *   Input Arguments:
 *     
 *   Returns:
 *   Notes:
	for (nbits=32; nbits%depth; nbits+=32) ;
	n = nbits / depth;
	modn = nbytes % n;
        return (modn ? (width + (n - modn)) : width);
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
long compute_bytes_per_scan_line (width, depth)
    long width, depth;
{
    long nbytes, modn;

    nbytes = ((width * depth) + 7) / 8;
    if (depth == 1) {
	/* only requires word alignment */
	return (nbytes + (nbytes & 1));
    } else if (depth == 24) {
	/* requires 12 byte alignment, and there are three bytes per pixel */
	modn = nbytes % 12;
	if (modn == 0)
	    return nbytes;
	else
	    return (nbytes + (12 - modn));
    } else {
	/* requires dword alignment */
	modn = nbytes % 4;
	if (modn == 0)
	    return nbytes;
	else
	    return (nbytes + (4 - modn));
    }
}
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void show_pixmap (data, width, height, image_depth, x, y)
  unsigned char *data;
  int width;
  int height;
  int image_depth;
  int x;
  int y;
{
    int pixmap_handle, gray, white;
    int bytes_per_scan_line;

    white = g2ext_get_pixel(window_handle, "white", 0);
    gray = g2ext_get_pixel(window_handle, "gray", 0);
    printf("white = %d; gray = %d\n", white, gray);

    bytes_per_scan_line = compute_bytes_per_scan_line(width, image_depth);

    pixmap_handle = g2ext_create_pixmap(window_handle, 32, 32, image_depth);
    /* pixmap_handle = g2ext_create_pixmap(window_handle, width, height, image_depth);  */
    printf("Before calling put_image\n");
    output_info_about_pixmap(data, 3, height, width, bytes_per_scan_line);
    printf("About to call put_image\n");
    g2ext_x11_put_image(pixmap_handle, x, y, width, height, image_depth,
		  1, bytes_per_scan_line, data);
    g2ext_x11_draw_pixmap(pixmap_handle, -1, 0, 0, width, height,
		    x, y, white, gray);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void do_some_pixmap_stuff ()
{
    printf("NEW STUFF\n");
    show_pixmap(orangeball_truecolor, 14, 14, DEPTH_BIT_COUNT, 107, 92);
    show_pixmap(orangeball_truecolor, 14, 14, DEPTH_BIT_COUNT, 100, 85);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
int main(argc, argv)
  int argc;
  char **argv;
{
    char *xserver;

    window_handle = cprim_test_initialize(argc, argv);

    screen_depth = g2ext_x11_screen_depth(window_handle);
    g2ext_x11_make_xwindow_visible(window_handle);
    do_some_pixmap_stuff();
    fflush(stdout);
    return -1;
}
#endif  /* ORANGEBALL */

#ifdef __JV_WIN95__
/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long g2ext_g2_clock_ticks(long num) 
{
	return num;
}
#endif



#ifdef PRINT_EVENT
/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
int print_event(event_type)
  int event_type;
{
  if (No_window)
    return 0;

  switch (event_type)
    {
    case KeyPress: printf("KeyPress\n"); break;
    case KeyRelease: printf("KeyRelease\n"); break;
    case ButtonPress: printf("ButtonPress\n"); break;
    case ButtonRelease: printf("ButtonRelease\n"); break;
    case MotionNotify: printf("MotionNotify\n"); break;
    case EnterNotify: printf("EnterNotify\n"); break;
    case LeaveNotify: printf("LeaveNotify\n"); break;
    case FocusIn: printf("FocusIn\n"); break;
    case FocusOut: printf("FocusOut\n"); break;
    case KeymapNotify: printf("KeymapNotify\n"); break;
    case Expose: printf("Expose\n"); break;
    case GraphicsExpose: printf("GraphicsExpose\n"); break;
    case NoExpose: printf("NoExpose\n"); break;
    case VisibilityNotify: printf("VisibilityNotify\n"); break;
    case CreateNotify: printf("CreateNotify\n"); break;
    case DestroyNotify: printf("DestroyNotify\n"); break;
    case UnmapNotify: printf("UnmapNotify\n"); break;
    case MapNotify: printf("MapNotify\n"); break;
    case MapRequest: printf("MapRequest\n"); break;
    case ReparentNotify: printf("ReparentNotify\n"); break;
    case ConfigureNotify: printf("ConfigureNotify\n"); break;
    case ConfigureRequest: printf("ConfigureRequest\n"); break;
    case GravityNotify: printf("GravityNotify\n"); break;
    case ResizeRequest: printf("ResizeRequest\n"); break;
    case CirculateNotify: printf("CirculateNotify\n"); break;
    case CirculateRequest: printf("CirculateRequest\n"); break;
    case PropertyNotify: printf("PropertyNotify\n"); break;
    case SelectionClear: printf("SelectionClear\n"); break;
    case SelectionRequest: printf("SelectionRequest\n"); break;
    case SelectionNotify: printf("SelectionNotify\n"); break;
    case ColormapNotify: printf("ColormapNotify\n"); break;
    case ClientMessage: printf("ClientMessage\n"); break;
    case MappingNotify: printf("MappingNotify\n"); break;
    default:
      printf("Event Type = %d\n", event_type);
    }
  fflush(stdout);
  return 0;
}
#endif



#if defined(MSWINDOWS)
/* For reference: our NT makefiles are a bit tricky to read, what with all the
 * variables and whatnot.  Here, as of 2/28/02, are all the options generated
 * for a "normal" ext/c compile.  The preprocessor options are identical for
 * optimized and debuggable.  That's a bit odd, in that normally one would
 * do something like -D_DEBUG for debuggable.  However, we don't.  The only
 * differences are the optimization flags.

// optimized
cl -Gs -Ob1 -Oi -Ot ...

// debuggable
cl -Z7 -Od ...

// rest of the options
 -c -W3 -DCRTAPI1=_cdecl -DCRTAPI2=_cdecl -nologo -D_X86_=1 -D_WIN95 
 -D_WIN32_WINDOWS=0x0400 -D_WIN32_IE=0x0300 -DWINVER=0x0400 -DWIN32
 -D_WIN32 -D_MT -MT -MT filename.c

// Doc, from Visual C++ Programmer's Guide, "Compiler Reference"
  /Gs<size>   Controls stack probes
          (It takes a <size>, but we don't supply one.)
          (More doc: The /Gs option with a size of 0 has the same result
                     as the /Ge option.
        /Ge   Activates stack probes)
  /Ob         Controls inline expansion
        /Ob1  Expands only functions marked as inline or __inline or,
              in a C++ member function, defined within a class declaration
  /Oi         Generates intrinsic functions
  /Ot         Favors fast code
        (as opposed to small code)

  /Z7         Generates C 7.0-compatible debugging information
  /Od         Disables optimization

  /c         Compiles without linking
  /W<level>  Sets warning level
  /nologo    Suppresses display of sign-on banner
  /MT        Creates a multithreaded executable file, using LIBCMT.LIB

 * If you want to see the results of the preprocessor, all you need to do is
 * give the -E flag to cl, and the preprocessor results will be dumped to
 * stdout.  I would think all of the compiler flags would be irrelevant in
 * this case, but it's kind of hard to say which flags change only the actual
 * compilation into object code, and which affect things more globally... 
 * /MT, for example.  I would think it might need to change the include path.
 * In any case, compiler flags certainly don't hurt the preprocessor output.
 * I'd say give at least all of our options common to both optimized and
 * debuggable, and maybe just for fun use the additional flags for whichever
 * type of compile you were wondering about:

cl -E -c -W3 -DCRTAPI1=_cdecl -DCRTAPI2=_cdecl -nologo -D_X86_=1 -D_WIN95 \
 -D_WIN32_WINDOWS=0x0400 -D_WIN32_IE=0x0300 -DWINVER=0x0400 -DWIN32 \
 -D_WIN32 -D_MT -MT filename.c > filename.i

 * Now, here's what we use in the Visual Studio project workspace I checked
 * in.  I believe I added /MT explicitly, as well as the include paths, of
 * course, but I think the rest is what you get by default.  I've reordered
 * the options to highlight differences between Release and Debug, and to
 * separate preprocessor directives from compiler flags.  I don't think that
 * matters.  I'm not quite sure why there is BASE CPP and plain CPP.

// Release
   /O2 /D "NDEBUG"
        
// Debug
   /Gm /ZI /Od /GZ  /D "_DEBUG"

// Common options
   /nologo /c /W3 /MT /GX /YX /FD
   /D "WIN32" /D "_MBCS" /D "_LIB" /D "_MT" /I "..\.." /I "..\..\..\..\jpeg\c"

  /O2         Creates fast code

  /Gm         Enables minimal rebuild
  /ZI         Includes debug information in a program database
              compatible with Edit and Continue.
  /Od         Disables optimization
  /GZ         Catch release-build errors in debug build

  /GX[-]      Enables synchronous exception handling
  /YX         Automates precompiled header
  /FD         Generate file dependencies
  
*/
/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *      Debugging output routines, since stdout does not work.
 *   Modifications:
 *****************************************************************************/
void G2Message (Message)
     char * Message;
{
    MessageBox (NULL, Message, NULL, MB_OK);   
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void DebugText (Message, x, y)
     char * Message;
     int x,y;
{
    TextOut (Ghdc, x, y, Message, strlen(Message) );
}
#endif /* MSWindows */


/****
* A tiny research tool.
* #define AllEventsMask ((Mask)((1<<25)-1))
****/

#ifdef FMW_IS_WORKING_ON_THIS
/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *      The function `x11_set_background_pixmap' sets the bg for a G2 X window.
 *      -fmw, 9/17/93
 *   Modifications:
 *****************************************************************************/
void x11_set_background_pixmap(window_index, pixmap)
  int window_index;
  Pixmap pixmap;
{
  GensymXWindow *gw; 
  Display *display;
  Window window;

  if (No_window)
    return;

  gw = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
  display = gw->display_ptr;
  window = gw->xwindow;

  XSetWindowBackgroundPixmap(display,window,pixmap);
  XSync(display,False);
}
#endif



/* test main */

#ifdef IMAGES_MAIN

#include <stdio.h>
#include <math.h>

int demo_tiled = 0;

/* For Windows, just read and dump the image in hex, if small. */

#ifdef __unix__

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/IntrinsicP.h>
#include <X11/ObjectP.h>
#include <X11/StringDefs.h>

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void print_drawable (display, window, name)
Display *display;
Drawable window;
char *name;
{
  Window root;
  int x,y,w,h,b,d;
  
  XGetGeometry(display, window, &root, &x, &y, &w, &h, &b, &d);
  printf("%s: drawable 0x%x, root 0x%x, x %d y %d width %d height %d border %d depth %d\n",
	 name, window, root, x, y, w, h, b, d);
  fflush(stdout);
}




/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long describe_image_stream(istream)
G2pointer istream;
{
  static char *formats[] = {"Any", "xbm", "gif", "pbm", "ppm"};

  printf("Width %d, height %d, depth %d, bytes %d, format %s\n",
	 g2ext_image_stream_width(istream),
	 g2ext_image_stream_height(istream),
	 g2ext_image_stream_depth(istream),
	 g2ext_image_stream_size(istream),
	 formats[g2ext_image_stream_format(istream)]);
  return 0;
}



/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void display_image(data, width, height, depth)
unsigned char *data;
int width, height, depth;
{
  Display *display;
  Window window;
  int ww, hh;
  XImage *image, ximage;
  XEvent event;
  GC gc, gc2;
  Pixmap bitmap;
  Visual *visual;
  XGCValues values;
  XGCValues gcvalues;
  
  ww = width;
  hh = height;
  if (demo_tiled)
    {
      printf("Tiled\n");
      ww *= 10;
      hh *= 10;
    }

  display = XOpenDisplay("");
  visual = DefaultVisual(display,DefaultScreen(display));
  window = XCreateWindow (display,
			  RootWindow(display,DefaultScreen(display)),
			  100, 100,
			  ww, hh,
			  0,
			  DefaultDepth(display,DefaultScreen(display)),
			  InputOutput,
			  visual,
			  0,
			  NULL);
  XSelectInput(display, window, ButtonPressMask|ExposureMask|KeyPressMask|
	       ButtonReleaseMask|StructureNotifyMask |SubstructureNotifyMask);

  XSetWindowBackground(display, window, 3);
  printf("Visual class = %d\n", visual->class);
  printf("ImageByteOrder %d, BitmapBitOrder %d, bitmapPad %d, bitmapUnit %d\n",
	 ImageByteOrder(display), BitmapBitOrder(display),
	 BitmapPad(display), BitmapUnit(display));

  
  XMapWindow(display, window);
  XClearWindow(display,window);
  XSync(display,False);
  
  gc = DefaultGC(display, 0);
  
  print_drawable(display, window, "window");
  
  if (depth == 1) {
      bitmap = XCreatePixmap(display, window, width, height, 1);

      print_drawable(display, bitmap, "bitmap");
      
      /* Code copied from XCreateBitmapFromData(), in XCrBFData.c  */
      ximage.height = height;
      ximage.width = width;
      ximage.depth = 1;
      ximage.xoffset = 0;
      ximage.format = ZPixmap;
      ximage.data = (char *)data;
      ximage.byte_order = LSBFirst;
      ximage.bitmap_unit = 8;
      ximage.bitmap_bit_order = LSBFirst;
      ximage.bitmap_pad = 8;
      ximage.bytes_per_line = (width+7)/8;
      ximage.bits_per_pixel = 1;
      image = &ximage;
      
      if (demo_tiled)
	{
	  values.foreground = 0;
	  values.background = 1;
	  values.stipple = bitmap;
	  values.fill_style = FillOpaqueStippled;
	  gc = XCreateGC(display, window,
			  GCStipple|GCFillStyle|GCForeground|GCBackground,
			  &values);
	}
      else
	gc = XCreateGC(display, window, (unsigned long) 0, (XGCValues *) 0);

      gcvalues.foreground = 1;
      gcvalues.background = 0;
      gcvalues.plane_mask = AllPlanes;
      gcvalues.fill_style = FillSolid;
      gcvalues.graphics_exposures = FALSE;
      gcvalues.function = GXcopy;
      gc2 = XCreateGC(display,bitmap,
		      GCFillStyle|GCBackground|GCForeground
		      |GCFunction|GCGraphicsExposures,
		      &gcvalues);

/*      gc2 = XCreateGC(display, bitmap, (unsigned long) GCFunction, &gcvalues); */
      XPutImage(display, bitmap, gc2, image, 0, 0, 0, 0, width, height);
      XSync(display,False);
    } else {
      /* Need to allocate and map colors. */
      fprintf(stderr, "Need to allocate and map colors for depth %d\n", depth);
      fflush(stderr);
      image = XCreateImage(display,
			   visual,
			   depth, ZPixmap, 0, 
			   data, width, height,
			   8, 0);
    }
  
  while (XNextEvent(display, &event)) {
    if (demo_tiled)
      XFillRectangle(display, window, gc, 0, 0, ww, hh);
    else if (depth == 1)
      XCopyPlane(display, bitmap, window, gc, 0, 0, ww, hh, 0, 0, 1);
    else
      XPutImage(display, window, gc, image, 0, 0, 0, 0, ww, hh);
    XSync(display,False);
    if (event.type == KeyPress) {
      static char buf[3];

      XLookupString((XKeyEvent *)&event, buf, 2, NULL, NULL);
      if (buf[0] == 'q') return;
    }
  }
  
}


#endif /* __unix__ */


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Images test program.
 *   Modifications:
 *****************************************************************************/
void main(argc, argv)
int argc;
char **argv;
{
  G2pointer istream;
  unsigned char *buffer, *cp;
  int i,j,n,m;
  int width, height, depth;
  char *filename;
  
  if (argc <= 1) {
    /* printf("Usage: %s [-tile] [-trace] image-filename\n", argv[0]);
       exit(1);
     */
    filename = "/home/jv/images/gifs/poker-dogs.gif";
  } else {
    int k=1;

    if (!strcmp(argv[k],"-tile")) {
      demo_tiled = 1;
      k++;
    }

    if (!strcmp(argv[k],"-trace")) {
      g2ext_set_trace_image_reads(1);
      k++;
    }

    filename = argv[k];
  }

  cprim_test_initialize(argc, argv);

  istream = g2ext_open_image_stream(filename, 0);
  if (istream == -1)
    {
      printf("Cannot open or cannot read image file.\n");
      exit(1);
    }

  describe_image_stream(istream);
  width = g2ext_image_stream_width(istream);
  height = g2ext_image_stream_height(istream);
  depth = g2ext_image_stream_depth(istream);
  
  
  cp = buffer = (unsigned char *)malloc(g2ext_image_stream_size(istream)+100);
  
  m=0;
  while ((n = g2ext_read_image_row(istream,cp)) > 0)
    {
      cp += n;
      m++;
    }

  if (m<height)
    printf("Error: read only %d rows out of %d\n", m, height);

  if (height < 32 && width < 32)
    {
      cp = buffer;
      for (i=0; i<height; i++)
	{
	  for (j=0; j< (width + 7) /8; j++)
	    printf("0x%02x ", *cp++);
	  printf("\n");
	}
    }
  
#ifdef __unix__
  display_image(buffer, width, height, depth);
#endif

  g2ext_close_image_stream(istream);
}

#endif /* IMAGES_MAIN */


#ifdef STUB_G2POINTERS
/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void g2ext_decache_g2pointer(something)
int something;
{
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
G2pointer g2ext_cache_cpointer(it)
int it;
{
  return((G2pointer) it);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long g2ext_map_g2pointer_to_cpointer(a_pointer)
unsigned char *a_pointer;
{
  return((long)a_pointer);
}
#endif


#ifdef XCONNECT
/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
int main(argc, argv)
  int argc;
  char **argv;
{
    char *xserver;
    char c;

    window_handle = cprim_test_initialize(argc, argv);

    g2ext_x11_make_xwindow_visible(window_handle);
    fflush(stdout);
    event_handling_loop();
    return -1;
}
#endif /* XCONNECT */
