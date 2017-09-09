/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      windows.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +   XWindows portions:
 +              ??/??/?? - 07/15/88   Antony (Antony is not Jon Anthony)
 +              07/15/88 - ??/??/??   Brian Matthews, Mark H. David,
 +                                    Peng Tsin Ong
 +              ??/??/?? - 09/20/95   Ben Hyde, Fred White
 +              1999 - 2000           mhd
 +              2001 - 2005           fmw
 +   MS Windows portions:
 +              ??/??/?? - 07/01/93   Richard Haggard, Kamal Bijlani
 +              07-08-93 - 08/30/96   mpc
 +              1999 - 2000           mhd
 +              2001 - 2005           fmw
 +
 + Description:  This file contains the primitives used to perform graphics
 +               functions.
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
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - Window Management Functions
 +      x11_create_colormap              1111111 Conditionally Defined
 +      g2ext_x11_initialize                   0000000 Multiply Defined
 +      g2ext_x11_initialize_after_connection  0000000 Mixed ifdefs
 +      g2ext_x11_set_window_title             0000000 Multiply Defined
 +      g2ext_x11_file_descriptor_for_window   0000000 Mixed ifdefs
 +      g2ext_x11_make_xwindow_visible         0000000 Mixed ifdefs
 +      g2ext_x11_raise_window                 0000000 Mixed ifdefs
 +      g2ext_x11_close                        0000000 Mixed ifdefs
 +      g2ext_x11_screen_depth                 0000000 Multiply Defined
 +      g2ext_window_width                     0000000 Multiply Defined
 +      g2ext_window_height                    0000000 Multiply Defined
 +      pixels_per_horizontal_inch       ???????
 +      pixels_per_vertical_inch         ???????
 +      set_window_area
 +
 + External Interface:
 +      long     g2ext_x11_initialize(display_spec_string, window_name, icon_name,
 +                              desired_width, desired_height,
 +                              desired_x0_in_display, desired_y0_in_display,
 +                              backing_store_p)
 +                 Initializes the toolkit and load resources
 +                 Returns: a window id on success
 +                          -1 on error
 +                          1 if G2 is running without a local window
 +      void     g2ext_x11_initialize_after_connection(window_index,
 +                   unicode_character_events_ok_p)
 +                 Initializes the window for the currently connected G2, after
 +                 the connection is established, including after each successful
 +                 reroute.
 +
 +      long     g2ext_x11_set_window_title(window, unicode_string)
 +                 Sets the title bar text of window.
 +                 Returns: 0 for success, -1 for failure
 +
 +      long     g2ext_x11_file_descriptor_for_window(window_index)
 +                 Gets file descriptor of the given Gensym window
 +                 Returns: a file descriptor
 +
 +      void     g2ext_x11_make_xwindow_visible (window_index)
 +                 Displays the given window
 +                 Returns: None
 +
 +      long     g2ext_x11_raise_window(window_index)
 +                 Makes the given window the topmost on the screen
 +                 Returns: 1
 +
 +      void     g2ext_x11_close(window_index)
 +                 Closes the given window
 +                 Returns: None
 +
 +      long     g2ext_x11_screen_depth(window_index)
 +                 Gets screen depth (bits per pixel) of screen
 +                 Returns: screen depth
 +
 +      long     g2ext_window_width(window_index)
 +                 get current window width
 +                 Returns: window width
 +
 +      long     g2ext_window_height(window_index)
 +                 get current window height
 +                 Returns: window height
 +
 + Dependencies:
 +      g2ext_map_g2pointer_to_cpointer
 +      g2ext_decache_g2pointer
 +      g2pvt_select_events
 +      g2ext_cache_cpointer
 +      g2pvt_initialize_event_handling
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   07/12/96, mpc: Added calls to Windows code to perform translations
 +                between 32bit Handles and 30bit Lisp ints.
 +   09/28/95, mpc: Major structural reorganization to improve code legibility
 +                and maintainability.
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications: mhd, 11/25/01 - #include <stdio.h> for WIN32 to get _vsnprintf
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include "cprim.h"

#if defined(WIN32)
#    include <string.h>
#    include <math.h>
#    include <windows.h>
#    include <winreg.h>
#    include "msincls.h"
#	 include <windowsx.h>          

#else /* Not WIN32 */
#    include <signal.h>
#    include <stdlib.h>
#endif

#include "graphics.h"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define DEFAULT_SCREEN_DEPTH_FOR_WINDOWS 16
#define DUMMY_BITMAP_WIDTH  8
#define DUMMY_BITMAP_HEIGHT 8

#if defined(MSWINDOWS)
#   ifndef QUERYDIBSUPPORT
#       define QUERYDIBSUPPORT 3073
#   endif
#   ifndef QDI_DIBTOSCREEN
#       define QDI_DIBTOSCREEN 4
#   endif
#else
#   define DEFAULT_X_DISPLAY "localhost:0.0"
#endif /* MSWINDOWS */



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes: unicode_is_handled_by_g2 is set each time the window connects
 %  to a new G2.  If true, on MSWINDOWS, we send Unicode character events.
 %  Otherwise, and on XWINDOWS in all cases, we send traditional, mostly
 %  ASCII, events only.  It is only set in the code in this file, and it
 %  is only referred to by the code in msmain.c.  Added 12/3/99. -mhd
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

static unsigned char stipple_25_percent_gray_bits[] = {
  0x88, 0x88, 0x88, 0x88, 0x22, 0x22, 0x22, 0x22, 0x44, 0x44,
  0x44, 0x44, 0x11, 0x11, 0x11, 0x11, 0x88, 0x88, 0x88, 0x88,
  0x22, 0x22, 0x22, 0x22, 0x44, 0x44, 0x44, 0x44, 0x11, 0x11,
  0x11, 0x11, 0x88, 0x88, 0x88, 0x88, 0x22, 0x22, 0x22, 0x22,
  0x44, 0x44, 0x44, 0x44, 0x11, 0x11, 0x11, 0x11, 0x88, 0x88,
  0x88, 0x88, 0x22, 0x22, 0x22, 0x22, 0x44, 0x44, 0x44, 0x44,
  0x11, 0x11, 0x11, 0x11, 0x88, 0x88, 0x88, 0x88, 0x22, 0x22,
  0x22, 0x22, 0x44, 0x44, 0x44, 0x44, 0x11, 0x11, 0x11, 0x11,
  0x88, 0x88, 0x88, 0x88, 0x22, 0x22, 0x22, 0x22, 0x44, 0x44,
  0x44, 0x44, 0x11, 0x11, 0x11, 0x11, 0x88, 0x88, 0x88, 0x88,
  0x22, 0x22, 0x22, 0x22, 0x44, 0x44, 0x44, 0x44, 0x11, 0x11,
  0x11, 0x11, 0x88, 0x88, 0x88, 0x88, 0x22, 0x22, 0x22, 0x22,
  0x44, 0x44, 0x44, 0x44, 0x11, 0x11, 0x11, 0x11
};

static unsigned char stipple_50_percent_gray_bits[] = {
  0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA
};

static unsigned char stipple_75_percent_gray_bits[] = {
  0x77, 0x77, 0x77, 0x77, 0xDD, 0xDD, 0xDD, 0xDD, 0xBB, 0xBB,
  0xBB, 0xBB, 0xEE, 0xEE, 0xEE, 0xEE
};

#ifdef INCLUDE_UNUSED_STIPPLES
static unsigned char stipple_5_5_percent_gray_bits[] = {
  0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80,
  0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00,
  0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20,
  0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00,
  0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00,
  0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40,
  0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00,
  0x10, 0x00, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00,
  0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80,
  0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00,
  0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x01,
  0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00,
  0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00,
  0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40,
  0x00, 0x10, 0x00, 0x04, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00,
  0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00,
  0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80,
  0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00,
  0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01,
  0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00,
  0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00,
  0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x02,
  0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00,
  0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00,
  0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80,
  0x00, 0x20, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00,
  0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01,
  0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00,
  0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x08, 0x00,
  0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02,
  0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00,
  0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00,
  0x80, 0x00, 0x20, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04,
  0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00,
  0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01,
  0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00,
  0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00,
  0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02,
  0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02, 0x00,
  0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x40, 0x00, 0x10, 0x00,
  0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04,
  0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00,
  0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01,
  0x00, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08,
  0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00,
  0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02,
  0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x00, 0x10,
  0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00,
  0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04,
  0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00,
  0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00,
  0x08, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08,
  0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00,
  0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00, 0x02,
  0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10,
  0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00,
  0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x04,
  0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0x00, 0x20,
  0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00,
  0x08, 0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08,
  0x00, 0x02, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x08, 0x00,
  0x02, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00,
  0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10,
  0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00,
  0x04, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x10
};
#endif /* INCLUDE_UNUSED_STIPPLES */

#ifdef INCLUDE_UNUSED_STIPPLES
static unsigned char stipple_6_percent_gray_bits[] = {
  0x80, 0x00, 0x80, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x08,
  0x00, 0x08, 0x20, 0x00, 0x20, 0x00, 0x00, 0x80, 0x00, 0x80,
  0x00, 0x02, 0x00, 0x02, 0x08, 0x00, 0x08, 0x00, 0x00, 0x20,
  0x00, 0x20
};
#endif /* INCLUDE_UNUSED_STIPPLSE */

#ifdef INCLUDE_UNUSED_STIPPLES
static unsigned char stipple_7_percent_gray_bits[] = {
  0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00,
  0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20,
  0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x08, 0x00,
  0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80,
  0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08,
  0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x00, 0x80, 0x02, 0x00,
  0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20,
  0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02,
  0x00, 0x08, 0x00, 0x20, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80,
  0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08,
  0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00,
  0x80, 0x02, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20,
  0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02,
  0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00,
  0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08,
  0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00,
  0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x20,
  0x00, 0x80, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02,
  0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x08, 0x00,
  0x20, 0x00, 0x80, 0x02, 0x00, 0x08
};
#endif /* INCLUDE_UNUSED_STIPPLES */

#ifdef INCLUDE_UNUSED_STIPPLES
static unsigned char stipple_8_percent_gray_bits[] = {
  0x80, 0x08, 0x00, 0x80, 0x08, 0x00, 0x80, 0x08, 0x00, 0x80,
  0x08, 0x00, 0x08, 0x00, 0x80, 0x08, 0x00, 0x80, 0x08, 0x00,
  0x80, 0x08, 0x00, 0x80, 0x00, 0x80, 0x08, 0x00, 0x80, 0x08,
  0x00, 0x80, 0x08, 0x00, 0x80, 0x08
};
#endif /* INCLUDE_UNUSED_STIPPLES */

#ifdef INCLUDE_UNUSED_STIPPLES
static unsigned char stipple_9_percent_gray_bits[] = {
  0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04,
  0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20,
  0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00,
  0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01,
  0x00, 0x20, 0x04, 0x00, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80,
  0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00,
  0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04,
  0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20,
  0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x10, 0x02,
  0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10,
  0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80,
  0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00,
  0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04,
  0x00, 0x80, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00,
  0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02,
  0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10,
  0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80,
  0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x02, 0x00, 0x40, 0x08,
  0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40,
  0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00,
  0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02,
  0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10,
  0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01,
  0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08,
  0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40,
  0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00,
  0x40, 0x08, 0x01, 0x00, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20,
  0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00,
  0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01,
  0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08,
  0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x04, 0x00,
  0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04,
  0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20,
  0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00,
  0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01,
  0x00, 0x20, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80,
  0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00,
  0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04,
  0x00, 0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20,
  0x04, 0x00, 0x80, 0x10, 0x02, 0x00, 0x00, 0x80, 0x10, 0x02,
  0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10,
  0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80,
  0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00,
  0x80, 0x10, 0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04,
  0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02, 0x00,
  0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10, 0x02,
  0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80, 0x10,
  0x02, 0x00, 0x40, 0x08, 0x01, 0x00, 0x20, 0x04, 0x00, 0x80,
  0x10, 0x02, 0x00, 0x40
};
#endif /* INCLUDE_UNUSED_STIPPLES */

#ifdef INCLUDE_UNUSED_STIPPLES
static unsigned char stipple_10_percent_gray_bits[] = {
  0x80, 0x20, 0x08, 0x02, 0x00, 0x80, 0x20, 0x08, 0x02, 0x00,
  0x80, 0x20, 0x08, 0x02, 0x00, 0x80, 0x20, 0x08, 0x02, 0x00,
  0x10, 0x04, 0x01, 0x00, 0x40, 0x10, 0x04, 0x01, 0x00, 0x40,
  0x10, 0x04, 0x01, 0x00, 0x40, 0x10, 0x04, 0x01, 0x00, 0x40,
  0x02, 0x00, 0x80, 0x20, 0x08, 0x02, 0x00, 0x80, 0x20, 0x08,
  0x02, 0x00, 0x80, 0x20, 0x08, 0x02, 0x00, 0x80, 0x20, 0x08,
  0x00, 0x40, 0x10, 0x04, 0x01, 0x00, 0x40, 0x10, 0x04, 0x01,
  0x00, 0x40, 0x10, 0x04, 0x01, 0x00, 0x40, 0x10, 0x04, 0x01,
  0x20, 0x08, 0x02, 0x00, 0x80, 0x20, 0x08, 0x02, 0x00, 0x80,
  0x20, 0x08, 0x02, 0x00, 0x80, 0x20, 0x08, 0x02, 0x00, 0x80,
  0x04, 0x01, 0x00, 0x40, 0x10, 0x04, 0x01, 0x00, 0x40, 0x10,
  0x04, 0x01, 0x00, 0x40, 0x10, 0x04, 0x01, 0x00, 0x40, 0x10,
  0x00, 0x80, 0x20, 0x08, 0x02, 0x00, 0x80, 0x20, 0x08, 0x02,
  0x00, 0x80, 0x20, 0x08, 0x02, 0x00, 0x80, 0x20, 0x08, 0x02,
  0x40, 0x10, 0x04, 0x01, 0x00, 0x40, 0x10, 0x04, 0x01, 0x00,
  0x40, 0x10, 0x04, 0x01, 0x00, 0x40, 0x10, 0x04, 0x01, 0x00,
  0x08, 0x02, 0x00, 0x80, 0x20, 0x08, 0x02, 0x00, 0x80, 0x20,
  0x08, 0x02, 0x00, 0x80, 0x20, 0x08, 0x02, 0x00, 0x80, 0x20,
  0x01, 0x00, 0x40, 0x10, 0x04, 0x01, 0x00, 0x40, 0x10, 0x04,
  0x01, 0x00, 0x40, 0x10, 0x04, 0x01, 0x00, 0x40, 0x10, 0x04
};
#endif /* INCLUDE_UNUSED_STIPPLES */

#ifdef INCLUDE_UNUSED_STIPPLES
static unsigned char stipple_12_percent_gray_bits[] = {
  0x80, 0x80, 0x80, 0x80, 0x10, 0x10, 0x10, 0x10, 0x02, 0x02,
  0x02, 0x02, 0x40, 0x40, 0x40, 0x40, 0x08, 0x08, 0x08, 0x08,
  0x01, 0x01, 0x01, 0x01, 0x20, 0x20, 0x20, 0x20, 0x04, 0x04,
  0x04, 0x04
};
#endif /* INCLUDE_UNUSED_STIPPLES */


#ifdef INCLUDE_UNUSED_STIPPLES
static unsigned char stipple_33_percent_gray_bits[] = {
  0x92, 0x49, 0x24, 0x92, 0x49, 0x24, 0x92, 0x49, 0x24, 0x92,
  0x49, 0x24, 0x49, 0x24, 0x92, 0x49, 0x24, 0x92, 0x49, 0x24,
  0x92, 0x49, 0x24, 0x92, 0x24, 0x92, 0x49, 0x24, 0x92, 0x49,
  0x24, 0x92, 0x49, 0x24, 0x92, 0x49
};
#endif /* INCLUDE_UNUSED_STIPPLES */


/* A WINAREA structure encapsulates the x, y, width, and height of a window. */

typedef struct { long x; long y; long width; long height; } WINAREA;

static void set_window_area(long, long, long, long, WINAREA *);

int unicode_is_handled_by_g2 = 0;
int ICP_window_protocol_version = 0;

int screen_depth_global = DEFAULT_SCREEN_DEPTH_FOR_WINDOWS;
int screen_max_width_global = 0;
int screen_max_height_global = 0;

extern int get_events_called_yet;
extern int Private_colormap_p;
extern int No_window;                /* defined in networks.c */

#if defined(MSWINDOWS)
    /* These are standard Brushes/Pens that are used consistently enough */
    /*  to justify hanging on to them.                                   */
    HBRUSH   GhbrWhite;       /* the global white brush */
    HBRUSH   GhbrBlack;       /* the global black brush */
    HPEN     GhpenWhite;      /* the global white pen */
    HPEN     GhpenBlack;      /* the global black pen */

    HANDLE   hInst = NULL;    /* Handle to instance's data selector/segment. */
    HDC      Ghdc;            /* the Global Handle to Device Context */
    HDC      GhdcMem;         /* the Global Handle to Memory Device Context */
    HDC      GhdcOffscreen;   /* Memory DC used for offscreen (buffered) drawing. */
    HBITMAP  GhbmDummy;

    /* Brushes for stipple patterns uses to implement icon stipple feature. */
    HBRUSH stipple_light;
    HBRUSH stipple_medium;
    HBRUSH stipple_dark;

    BOOL msh_MouseWheelPresent;
    UINT msh_MouseWheelLines;      /* Number of lines wheel should scroll */
    BOOL msh_MouseWheelAutoScroll; /* TRUE if wheel automatically sends scroll msgs. */
    UINT msh_MouseWheelMsg;        /* Alternate mouse wheel message. */

    extern LPG2INFO GetlpG2Info(HWND);
    extern void g2ext_exit_from_lisp (long exit_status);
    extern BOOL g2pvt_win32_init (HANDLE);

#else /* not MSWindows, must be XWindows */

    /* the_x_display contains a pointer to the X display, if we are connected.*/
    static Display *the_x_display = (Display *)0;

    /* The G2 main window under X. */
    static Window g2_main_window = (Window)0;

    /* The parent window handle -- not static */
    long parent_XWindow_address = 0L;

    extern int g2pvt_select_events();                       /* events.c */
    extern void g2pvt_initialize_event_handling();        /* keypress.c */
    extern int g2ext_parent_window_size (/* Display *, long, int *, int * */);
                                                          /* graphics.c */
    extern long g2ext_network_close(/* long */);          /* networks.c */
    extern void ne_initialize_display_events(/* int */);  /* sckevent.c */

    extern G2pointer g2ext_window_network_interface_handle;

#endif /* MSWindows or XWindows */


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Window Management Functions
 %
 % Description:
 %   These functions are for setup, initialization, creation, and management
 &   of application windows.
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * static Colormap x11_create_colormap (GensymXWindow *gwindow,
 *                                      Display *display,
 *                                      Window window)
 *   Description:
 *     Creates a private colormap as compatible as possible with the
 *     default colormap of the screen.
 *   Input Arguments:
 *     gwindow:   A Gensym Window handle
 *     display:   A Display handle
 *     window:    A Window
 *   Returns:
 *     an X colormap
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

static Colormap x11_create_colormap (gwindow, display, window)
     GensymXWindow *gwindow;
     Display *display;
     Window window;
{
    XWindowAttributes xwa;
    Colormap dmap, cmap;
    XColor colors[MAX_COLORS];
    int i;
    int ncolors = 32;                /* Number in common with the default map. */
    unsigned char *flags = gwindow->color_flags;

    dmap = DefaultColormap(display, DefaultScreen(display));
    if (!Private_colormap_p) {
      return dmap;
    }

    XGetWindowAttributes(display, window, &xwa);
    cmap = XCreateColormap(display, window, xwa.visual, AllocAll);

    /* Some X servers have immutable (unwritable) colormaps, in
    ** which case they return the default colormap.
    */
    if (cmap == dmap) {
      printf("\nWarning:  Private Colormap command line option ignored: immutable colormap. \n");
      Private_colormap_p = 0;
      return dmap;
    }

    for(i=0; i< ncolors; i++)
        colors[i].pixel = i;

    /* Get existing colors from the default colormap. */
    XQueryColors(display, dmap, colors, ncolors);

    for(i=0; i< MAX_COLORS; i++)
        flags[i] = COLOR_FREE;

    /* Copy the first 32 over to our color map. */
    for(i=0; i< ncolors; i++) {
        colors[i].flags = DoRed|DoBlue|DoGreen;
        flags[i] = COLOR_ALLOCATED; /* Not an extended color. */
    }
    XStoreColors(display, cmap, colors, ncolors);

    XSetWindowColormap(display, window, cmap);

    return cmap;
}
#endif /* XWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * long g2ext_select_event_loop_mode(long mode)
 *
 *   Description:
 *     decides whether the event loop will process messages from only
 *     the current window or from the entire system.
 *   Input Arguments:
 *     mode  long             0 means just this window, 1 means all windows.
 *   Returns:
 *     return value:  -1 on error, 0 for success.
 *   Notes: This function exists so that JGSI won't get confused (mode 0),
 *   but G2/TW will be able to use OLE (mode 1).
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)
long g2ext_select_event_loop_mode(mode)
 long      mode;
{
  return -1;
}
#endif /* MSWINDOWS */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)
long g2ext_select_event_loop_mode(mode)
 long      mode;
{
 return 0;
}
#endif /* XWINDOWS */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * long g2ext_x11_initialize(char *display_spec_string, char *window_name,
 *                     char *icon_name, long desired_width, long desired_height,
 *                     long desired_x0_in_display, long desired_y0_in_display,
 *                     long backing_store_p, long private_colormap_p)
 *
 *   Description:
 *     initializes the toolkit and loads resources.
 *   Input Arguments:
 *     display_spec_string:
 *     window_name:           Name of window on titlebar
 *     icon_name:             Name of window when iconized
 *     desired_width:         -2 full screen,-1 default size, else given size.
 *     desired_heigh:         -2 full screen,-1 default size, else given size.
 *     desired_x0_in_display: >=0 absolute position, -1 default position,
 *                            <0 offset from max screen dimension, minus 1.
 *     desired_y0_in_display: >=0 absolute position, -1 default position,
 *                            <0 offset from max screen dimension, minus 1.
 *     backing_store_p:       Boolean, indicated a backing store desired.
 *     private_colormap_p:    Boolean, cm is desired, for 8-bit color systems only
 *   Returns:
 *     return value:  -1 on error, 1 if no local window, otherwise a window handle
 *   Notes:
 *   Modifications:
 *       5/19/92, jh:  Added extra arg, icon_name, to g2ext_x11_initialize so we can
 *     differentiate icon names from window names.  Telewindows needs a
 *     smaller icon name.
 *     -----
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

/** Disables the close button of the @p window on the @display.  This
    being X11, it actually just gives a non-ICCM compliant hint (a
    "leftover" from the Motif window manager), so there are no
    guarantees, but, with most window managers, it works.
 */
static void x11_disable_close(Display *display, Window window)
{
    /* These definitons are from the Motif Window Manager. Most modern
       window managers implement these, but, there is no official place
       for these definitions, so, everybody just copies this around...
    */
    struct MwmHints {
        unsigned long flags;
        unsigned long functions;
        unsigned long decorations;
        long input_mode;
        unsigned long status;
    };
    enum {
        MWM_HINTS_FUNCTIONS = (1L << 0),
        MWM_HINTS_DECORATIONS =  (1L << 1),

        MWM_FUNC_ALL = (1L << 0),
        MWM_FUNC_RESIZE = (1L << 1),
        MWM_FUNC_MOVE = (1L << 2),
        MWM_FUNC_MINIMIZE = (1L << 3),
        MWM_FUNC_MAXIMIZE = (1L << 4),
        MWM_FUNC_CLOSE = (1L << 5)
    };

    struct MwmHints hints;
    Atom wm = XInternAtom(display, "_MOTIF_WM_HINTS", False);
    hints.functions = MWM_FUNC_RESIZE | MWM_FUNC_MOVE | MWM_FUNC_MINIMIZE | MWM_FUNC_MAXIMIZE;
    hints.flags = MWM_HINTS_FUNCTIONS;
    XChangeProperty(display, window, wm, XA_ATOM, 32, PropModeReplace, (unsigned char*)&hints, 5);

    /* The ICCM-compliant `_NET_WM_ACTIONS_ALLOWED` _can't_ be used
       for these purposes. It is managed by the Window Manager, not by
       the X11 application, designed to be used by third-party
       applications ("pagers", etc - i.e. "the desktop") for them to
       see if they are allowed to close, resize, etc. ICCM doesn't
       provide a standard way for the application itself to influence
       this, so, the only thing left is this Motif compatibility.

       Most Window Managers have some kind of configuration "system"
       in which one could define that for some application you decide
       that you want to disable close (or min/max...), but again,
       there is no standard for this. So, this Motif property is the
       (much) lesser of two evils.
    */
}

long g2ext_x11_initialize(char *display_spec_string, char *window_name, char *icon_name,
                          long desired_width, long desired_height, long desired_x0_in_display,
                          long desired_y0_in_display, long backing_store_p, long private_colormap_p,
                          long frame_type)
{
    GensymXWindow *gwindow;
    int local_argc = 1;
    char *local_argv[3];
    Cursor cursor;
    int x0 = 0;
    int y0 = 0;
    int window_connection_number;

    Display *display;
    Window window;
    Window parent_XWindow = (Window) NULL;
    int width = 0, height = 0;
    Screen *default_screen;
    Visual *default_visual;
    XSetWindowAttributes attr;
    int attr_mask = 0;
    XSizeHints size_hints;
    XSizeHints zoom_size_hints;
    XWMHints wmhints;
    XGCValues gc_values;
    int i;
    char *display_to_use = display_spec_string;
    Atom wm_protocols, data[1]; /* used by XChangeProperty */

    if (No_window)
      return (1);

    get_events_called_yet = FALSE;

    if ((display_spec_string == NULL)
#ifdef _IBMR2
        || (strcmp(display_spec_string, ":0.0") == 0)
#endif
        ) {
      display_to_use = DEFAULT_X_DISPLAY;
    }

    display = the_x_display = XOpenDisplay (display_to_use);

    if (!display) {
        printf("\nCould not open X11 window display %s. ", display_to_use);
        printf("\nAborting startup. \n");
        exit(-1);
    }

    g2pvt_initialize_event_handling(display);

    default_screen = DefaultScreenOfDisplay (display);
    screen_max_width_global = WidthOfScreen (default_screen);
    screen_max_height_global = HeightOfScreen (default_screen);
    default_visual = DefaultVisualOfScreen (default_screen);
    screen_depth_global = DefaultDepthOfScreen (default_screen);
    Private_colormap_p = private_colormap_p;
    if (private_colormap_p && (screen_depth_global > DEPTH_EIGHT)) {
      Private_colormap_p = 0;
      printf("\nWarning: Private Colormap command line option ignored: display has %d bits per pixel. \n",
             screen_depth_global);
    }

    attr_mask = 0;

    /* Keep more bits around on a resize */
    /* Since this causes smaller expose events to be sent to G2,
     * a telewindow with bit gravity on turds on resize when talking
     * to an old G2.  So this must wait for the great breakaway
     * (or else some ugly hacking in telewindows).
     */
#   ifdef BIT_GRAVITY
        attr.bit_gravity = NorthWestGravity;
        attr_mask |= CWBitGravity;
#   endif

    if (backing_store_p) {
      attr.backing_store = Always;
      attr_mask |= CWBackingStore;
    }

    if (parent_XWindow_address != 0L) {
      int wheight, wwidth;

      if (g2ext_parent_window_size(display, parent_XWindow_address,
                                   &wwidth, &wheight)) {
        x0 = 0; y0 = 0;
        /* if the user tried to specify a height or width that was different
         * from the parent window size, we should issue a warning here that
         * we are going to default to the window size instead. */
        width  = wwidth;
        height = wheight;
        parent_XWindow = (Window) parent_XWindow_address;
      } else {
        /* insert error message here */
        /* reset and ignore from here on */
        parent_XWindow_address = 0L;
      }
    }

    if (parent_XWindow_address == 0L) {
      WINAREA area;
      set_window_area(desired_width, desired_height, desired_x0_in_display,
                      desired_y0_in_display, &area);
      x0 = area.x; y0 = area.y; width = area.width; height = area.height;
      parent_XWindow = XRootWindowOfScreen(default_screen);
    }
    window = XCreateWindow(display,
                           parent_XWindow,
                           x0,
                           y0,
                           width,
                           height,
                           0,
                           screen_depth_global,
                           InputOutput,
                           default_visual,
                           attr_mask,
                           &attr);
    g2_main_window = window;

    /* GensymXWindow */
    gwindow = MakeInstance(GensymXWindow);
    if (gwindow == NULL) {
        printf("Out of memory during initialization.\n");
        return -1;
    }
    gwindow->xwindow = window;
    gwindow->screen_ptr = default_screen;
    gwindow->display_ptr = display;
    gwindow->offscreen = FALSE;
    gwindow->last_window_x = x0;
    gwindow->last_window_y = y0;
    gwindow->last_window_width = width;
    gwindow->last_window_height = height;
    gwindow->cut_and_paste = XInternAtom(display,"G2PASTE",False);


    /* Create color map */
    gwindow->colormap = x11_create_colormap(gwindow,display,window);


    /* Define cursor. */
    cursor = XCreateFontCursor(display, XC_top_left_arrow);
    if (cursor != (Cursor) NULL)
        XDefineCursor(display, window, cursor);


    window_connection_number = ConnectionNumber(display);

    ne_initialize_display_events (window_connection_number);
    gwindow->network_interface_handle = g2ext_window_network_interface_handle;


    /* set properties */
    local_argv[0] = window_name;
    size_hints.flags = PMinSize;
    size_hints.x = x0;
    size_hints.y = y0;
    size_hints.width = width;
    size_hints.height = height;

    if (desired_x0_in_display != -1  ||  desired_y0_in_display != -1)
        size_hints.flags |= USPosition;
    else
        size_hints.flags |= PPosition;

    if (desired_height != -1  ||  desired_width != -1)
        size_hints.flags |= USSize;
    else
        size_hints.flags |= PSize;


    /* The minimum size is implicitly specified by the window parameters
       plist, in PLATFORMS.  Right now, that specifies
       default-minimum-width-for-pane (10),
       default-minimum-height-for-pane (10),
       pane-layout ('(detail-pane)),
       width-of-window-border (6),
       and width-of-space-between-panes (6, but irrelevant with this pane layout).

       Therefore, both the minimum width and height are 22 (= 10 + 6 + 6).
       Note that G2 will abort if it is resized to less than this amount.

       This information should be computed and passed down here!!

       (MHD 7/16/90)
     */
    size_hints.min_width = 22;
    size_hints.min_height = 22;

    /* size_hints.max_width = 000; */
    /* size_hints.max_height = 000; */
    /* size_hints.width_inc = 1; */
    /* size_hints.height_inc = 1; */
    /* size_hints.min_aspect.x = 000; */
    /* size_hints.min_aspect.y = 000; */
    /* size_hints.max_aspect.x = 000; */
    /* size_hints.max_aspect.y = 000; */
    XSetStandardProperties(display, window,
                           window_name, icon_name,
                           None, local_argv, local_argc, &size_hints);

    /* GENSYMCID-1207: Disable the window close button of G2 server on Linux
       also see Inter-Client Communication Conventions Manual (ICCCM), Version 2.0 */
    wm_protocols = XInternAtom(display, "WM_PROTOCOLS", False);
    data[0] = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XChangeProperty(display, window,
            wm_protocols, XA_ATOM, 32, PropModeReplace,
            (unsigned char *)data, 1);

    x11_disable_close(display, window);

    /* Here we set zoom hints so that zooming makes the
       window fill the entire screen.
     */
    zoom_size_hints.flags = PPosition | PSize;
    zoom_size_hints.x = 0;
    zoom_size_hints.y = 0;
    zoom_size_hints.width = screen_max_width_global;
    zoom_size_hints.height = screen_max_height_global;
    XSetZoomHints (display, window, &zoom_size_hints);

    /* Here we set window manager hints so that (1) the window
       manager knows that we use the so-called "passive" keyboard
       focus model, meaning just that we need to receive keyboard
       input when we are selected, and (2) the window manager knows
       we want to come up in the so-called "normal" state, i.e.
       with our window visible, not iconified.
     */
    wmhints.flags = InputHint | StateHint;
    wmhints.input = True;        /* We use "Passive keyboard focus model". */
    wmhints.initial_state = NormalState; /* Want our top-level window visible.*/
                                         /* Soon, pass in an icon pixmap! */
    XSetWMHints(display, window, &wmhints);


    /* Initialize global_gctable[] here.  */
    for(i=0; i<MAXIMUM_NUMBER_OF_GCFUNCTIONS ; i++)
        gwindow->global_gctable[i] = (GC)NULL;


    /*****
     * Setup the scrolling_gc slot.
     *****/
    gc_values.foreground = 1;
    gc_values.background = 0;
    gc_values.plane_mask = AllPlanes;
    gc_values.fill_style = FillSolid;
    gc_values.graphics_exposures = TRUE;
    gc_values.function = GXcopy;
    gwindow->scrolling_gc = XCreateGC(display,window,
                                      GCFillStyle|GCBackground|GCForeground
                                      |GCFunction|GCGraphicsExposures,
                                      &gc_values);

    /*****
     * Setup the images_gc slot.
     *****/
    gc_values.foreground = 1; /* These are changed for 1bit images. */
    gc_values.background = 0;
    gc_values.plane_mask = AllPlanes;
    gc_values.fill_style = FillSolid;
    gc_values.graphics_exposures = FALSE;
    gc_values.function = GXcopy;
    gwindow->images_gc = XCreateGC(display,window,
                                   GCFillStyle|GCBackground|GCForeground
                                   |GCFunction|GCGraphicsExposures,
                                   &gc_values);

    /*****
     * Setup the stippled_gc slot.
     *****/
    gc_values.fill_style = FillStippled;
    gc_values.graphics_exposures = FALSE;
    gwindow->stippled_gc = XCreateGC(display,window, GCFillStyle|GCGraphicsExposures, &gc_values);
    gwindow->stippled_gc_foreground_color = 0; /* 0 = X's default GC foreground */

    /*****
     * Set up the stippleXX slots (stipples), initially NULL.
     *
     * Note that the "light" and "dark" are reversed on Windows, and the names
     * perhaps reflect that.  But here, on X Windows, "75% gray" is the light
     * one, and "25% gray" is the dark one.  -jv, 4/24/05
     *****/
    if (!((gwindow->stipple_light = XCreateBitmapFromData
           (display, window, (char *)stipple_75_percent_gray_bits,
            stipple_75_percent_gray_width, stipple_75_percent_gray_height))
          && (gwindow->stipple_medium = XCreateBitmapFromData
              (display, window, (char *)stipple_50_percent_gray_bits,
               stipple_50_percent_gray_width, stipple_50_percent_gray_height))
          && (gwindow->stipple_dark = XCreateBitmapFromData
              (display, window, (char *)stipple_25_percent_gray_bits,
               stipple_25_percent_gray_width, stipple_25_percent_gray_height)))) {
      perror("XCreateBitmapFromData creating stipples");
      exit(-1);
    }

    return(g2ext_cache_cpointer ((long)gwindow));
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

/* Grab information about the mouse wheel, if any, from the OS.
   TODO: This should be reexcuted on WM_SETTINGCHANGE. */
static void get_mouse_wheel_info(void)
{
  HKEY hkey = NULL;
  char value[16];
  DWORD len = sizeof(value);

  msh_MouseWheelPresent = GetSystemMetrics(SM_MOUSEWHEELPRESENT);

  msh_MouseWheelLines = 0;
  SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &msh_MouseWheelLines, 0);

  /* Determine whether IntelliMouse "smart" [sic] scrolling is enabled. */
  ZeroMemory(value,sizeof(value));
  RegOpenKeyEx(HKEY_CURRENT_USER,
               "Control Panel\\Microsoft Input Devices\\Mouse",
               0, KEY_QUERY_VALUE, &hkey);
  RegQueryValueEx(hkey, "MSW_SmartUniversal", NULL, NULL, (LPBYTE)value, &len);
  RegCloseKey(hkey);
  msh_MouseWheelAutoScroll = (strcmp(value,"ON") == 0);

  /* Old wheel message used only on W95 and NT 3.51 */
  msh_MouseWheelMsg = RegisterWindowMessage(MSH_MOUSEWHEEL);
}

static void get_work_area(RECT *r)
{
  if(!SystemParametersInfo (SPI_GETWORKAREA, sizeof(RECT), r, 0))
    GetWindowRect(GetDesktopWindow(),r);
}


/* The function init_window_globals initializes window-system
   globals if necessary by setting the following:

   Ghdc
   GhdcMem
   GhbrWhite
   GhbrBlack
   GhpenWhite
   GhpenBlack
   GhbmDummy
   stipple_light
   stipple_medium
   stipple_dark

   screen_depth_global

   If it is successful, it returns TRUE. Note that GhwndWin is set to
   a non-null value in this case. Otherwise, it returns FALSE.

   init_window_globals_if_necessary() calls init_window_globals, and
   returns its value, iff GhwndWin is non-null; otherwise, it just
   returns TRUE. */


BOOL init_window_globals()
{
  RECT r;
  void get_mouse_wheel_info(void);

  get_work_area(&r);

  /* Consider making this a message-only window (parent = HWND_MESSAGE) */
  GhwndWin
    = CreateWindowW(GensymWindowClass,
                    L"G2EventWindow", WS_OVERLAPPEDWINDOW,
                    r.left, r.top, r.right, r.bottom, NULL, NULL, hInst, NULL);
  if (GhwndWin == NULL)
    return(FALSE);
  Ghdc = GetDC(GhwndWin);
  if (Ghdc == NULL)
    return(FALSE);
  GhdcMem = CreateCompatibleDC(Ghdc);
  GhdcOffscreen = CreateCompatibleDC(Ghdc);
  g2pvt_make_new_window_info(GhwndWin, -1);

  GhbrWhite  = GetStockObject (WHITE_BRUSH);
  GhbrBlack  = GetStockObject (BLACK_BRUSH);
  GhpenWhite = GetStockObject (WHITE_PEN);
  GhpenBlack = GetStockObject (BLACK_PEN);
  GhbmDummy = CreateBitmap(DUMMY_BITMAP_WIDTH, DUMMY_BITMAP_HEIGHT, 1, 1, NULL);
  if ((GhdcMem == NULL) || (GhbrWhite == NULL) || (GhbrBlack == NULL)
      || (GhpenWhite == NULL) || (GhpenBlack == NULL) || (GhbmDummy == NULL))
    return(FALSE);

  /* set up brushes for stippling, implementing stippled icons */
  stipple_light
    = CreatePatternBrush
    (CreateBitmap
     (stipple_25_percent_gray_width, stipple_25_percent_gray_height,
      1, 1, &stipple_25_percent_gray_bits));
  stipple_medium
    = CreatePatternBrush
    (CreateBitmap
     (stipple_50_percent_gray_width, stipple_50_percent_gray_height,
      1, 1, &stipple_50_percent_gray_bits));
  stipple_dark
    = CreatePatternBrush
    (CreateBitmap
     (stipple_75_percent_gray_width, stipple_75_percent_gray_height,
      1, 1, &stipple_75_percent_gray_bits));
  if ((stipple_light == NULL) || (stipple_medium == NULL) || (stipple_dark == NULL))
    return(FALSE);

  /*
   * Set up screen_depth_global variable.
   */
  {
    int planes, bitspixel;

    bitspixel = GetDeviceCaps(Ghdc, BITSPIXEL);
    planes = GetDeviceCaps(Ghdc, PLANES);
    screen_depth_global = bitspixel * planes;
  }

  /*
   * Set up screen_max_height_global and screen_max_width_global.
   */
  screen_max_height_global = (WORD)GetDeviceCaps(Ghdc, VERTRES);
  screen_max_width_global = (WORD)GetDeviceCaps(Ghdc, HORZRES);

  /* Alternative mouse wheel message, sent sometimes. */
  get_mouse_wheel_info();

  return(TRUE);
}

BOOL init_window_globals_if_necessary()
{
  BOOL need_init = (GhwndWin == NULL);

  if (need_init)
    return(init_window_globals());
  else
    return(TRUE);
}


/* g2ext_x11_initialize specifics for Windows:

   The resulting window is created as a child window of
   parent_GhwndWin if that's non-null; otherwise, the window
   style is WS_OVERLAPPEDWINDOW.

   If the "-screenlock" flag was passed on the commandline, we want to
   make it so the user cannot switch to another app by system menu
   choices, window resizing, or clicking a visible application.

   In that case, the style will be WS_OVERLAPPED, and the extended
   style will be WS_EX_TOPMOST.

   Style WS_OVERLAPPED is a window with a titlebar and frame.

   Style WS_OVERLAPPEDWINDOW is a window with a titlebar, frame,
   system menu, resizable border, and min/max buttons.

   Extended style WS_EX_TOPMOST makes a window stay on top.
   */

#define FRAME_TYPE_NONE 0        /* Keep in sync with frame-type-xxx in windows4 */
#define FRAME_TYPE_CLASSIC 1
#define FRAME_TYPE_CHILD 2
#define FRAME_TYPE_SDI 3
#define FRAME_TYPE_MDI 4

long g2ext_x11_initialize(LPSTR display_spec_string, LPSTR window_name, LPSTR icon_name,
                          long desired_width, long desired_height,
                          long desired_x0_in_display, long desired_y0_in_display,
                          long backing_store_p,               /* unused */
                          long private_colormap_p,     /* unused */
                          long frame_type)
{
  DWORD window_style = (parent_GhwndWin ? WS_CHILD : WS_OVERLAPPEDWINDOW);
  DWORD extended_style = 0;
  extern int screenlock;
  WINAREA area;
  LPG2INFO info;
  HMENU menu = NULL;
  LPCWSTR class_name = NULL;
  extern HMENU g2pvt_make_initial_menubar();

  init_window_globals_if_necessary();           /* Creates the event window (GhwndWin). */
  if (hInst == NULL) {
      hInst = GetWindowInstance(GhwndWin);
      g2pvt_win32_init(hInst);
  }

  if (No_window)
    return GetlpG2Info(GhwndWin)->window_index;

  if (screen_depth_global < DEFAULT_SCREEN_DEPTH_FOR_WINDOWS) {
    MessageBox(NULL, "At least 16-bit color is required.",
               "Display Depth Error", MB_OK);
    exit(-1);
  }

  Private_colormap_p = private_colormap_p;

  if (screenlock) {
    window_style = WS_OVERLAPPED;
    extended_style = WS_EX_TOPMOST;
  }

  switch(frame_type) {
   case FRAME_TYPE_NONE:                   /* Embedded workspaceview case */
     Frame_is_MDI = FALSE;
     Frame_has_client = FALSE;
     Frame_is_embedded = TRUE;                   /* This enables all the hacks for SWV. */
     hwndFrame = GhwndWin;                   /* Acts like our frame, but always hidden. */
     class_name = NULL;
     break;

   case FRAME_TYPE_CLASSIC:                   /* Just a frame window */
     Frame_is_MDI = FALSE;
     Frame_has_client = FALSE;
     class_name = GensymTelewindowClass;
     break;

   case FRAME_TYPE_CHILD:                   /* Classic plugin case */
     Frame_is_MDI = FALSE;
     Frame_has_client = FALSE;
     class_name = GensymTelewindowClass;
     /* SWV TODO: Should we declare ourselves embedded here? If there are, say,
        two SWV controls on a web page sharing a TW, then we want to declare
        outselves embedded, and make the G2 Window be either the browser window
        or the desktop. */
     break;

   case FRAME_TYPE_SDI:                           /* menubar, window, statusbar */
     Frame_is_MDI = FALSE;
     Frame_has_client = TRUE;
     class_name = GensymFrameClass;
     window_style = window_style | WS_CLIPCHILDREN;
     menu = g2pvt_make_initial_menubar();
     break;

   case FRAME_TYPE_MDI:                           /* menubar, MDIClient, statusbar */
     Frame_is_MDI = TRUE;
     Frame_has_client = TRUE;
     class_name = GensymFrameClass;
     window_style = window_style | WS_CLIPCHILDREN;
     menu = g2pvt_make_initial_menubar();
     break;

  }

  if (class_name != NULL && parent_GhwndWin) { /* Classic plugin case. */
    RECT rect;

    Frame_is_MDI = FALSE;        /* For now, until we support SWV. */
    Frame_has_client = FALSE;

    GetClientRect(parent_GhwndWin, &rect);
    area.x = 0; area.y = 0;
    /* If we're a plugin, we probably shouldn't allow user-specified area;
     * however, we will, for backwards compatibility on Windows.  At least
     * now it will no longer be required. - jv, 6/24/02 */
    area.width = (desired_width < 0) ? rect.right : desired_width;
    area.height = (desired_height < 0) ? rect.bottom : desired_height;
  } else {
    set_window_area(desired_width, desired_height,
                    desired_x0_in_display, desired_y0_in_display,
                    &area);
  }

  if(class_name && hwndFrame == NULL)
    hwndFrame = CreateWindowExW(extended_style, class_name,
                                L"Gensym", window_style,
                                area.x, area.y, area.width, area.height,
                                parent_GhwndWin, menu, hInst, NULL);
  else {
    G2TRACE("Using existing frame window %x\n", hwndFrame);
    if(screenlock) {
      SetWindowLong(hwndFrame, GWL_STYLE, window_style | WS_CAPTION);
      SetWindowLong(hwndFrame, GWL_EXSTYLE, extended_style);
      SetWindowPos(hwndFrame, HWND_TOPMOST, area.x, area.y, area.width, area.height, SWP_FRAMECHANGED);
    } else {
      SetWindowPos(hwndFrame, 0, area.x, area.y, area.width, area.height,
                   SWP_NOZORDER | SWP_NOACTIVATE);
    }
  }

  if (hwndFrame == NULL) {
    g2pvt_notify_user("Unable to create frame window: %s", g2pvt_get_last_error_string());
    g2ext_exit_from_lisp(-1);
  }

  /* TODO: Allow unicode for the initial window name.
     This requires unicode command line arguments. */
  SetWindowText(hwndFrame, window_name);

  info = g2pvt_make_new_window_info(hwndFrame, -1);

  if(Frame_is_MFC)                /* Normally called from our frame's WM_CREATE handler. */
    g2pvt_designate_mdi_client(hwndClient);

  /* This is the window which is declared to be the G2-WINDOW. It is where
   * events should be sent, and where pane bg drawing goes. */
  hwndMain = Frame_has_client ? hwndClient : hwndFrame;

  /* Show the window for the first time, the normal way. */


#ifndef GENFLEX // Victor Kazarinov 2008/10/02: When using GenFlex, TW window must not be visible.
  if(!Frame_is_embedded)
    ShowWindow(hwndFrame, SW_SHOWNORMAL);
#endif

  G2TRACE("g2ext_x11_initialize hwndFrame %x hwndClient %x hwndMain %x\n",
          hwndFrame, hwndClient, hwndMain);

  /* Return index for the G2 Window, hwndMain. */
  return GetlpG2Info(hwndMain)->window_index;
}

#endif /* MSWindows */


/** Returns the "root" window (rather than the "main" window). 
    Currently makes sense only on Windows.
*/
long g2ext_get_root_window(/*void*/)
{
#if defined(MSWINDOWS)
    return GetlpG2Info(GhwndWin)->window_index;
#else
    return 1;
#endif
}


/*****************************************************************************
 + long     g2ext_x11_initialize_after_connection(window_index,
 +                   unicode_character_events_ok_p, xclip_p)
 *   Description:
 *     Initializes the window for the currently connected G2, after
 +     the connection is established, including after each successful
 +     reroute.  Returns -1 on error, 1 otherwise.
 +     The first parameter says if we're talking to a G2 that
 +     handles unicode character events (i.e., G2 6.0), in which case
 +     unicode_is_handled_by_g2 is set true.
 *     The second parameter is used for the X Window System only. It
 *     says if we're setting a clipping rectangle
 *     for each bitmap draw.  This affects performance; it may be slower,
 *     and it may be faster.  On most platforms it's thought to be faster,
 *     and it is definitely untested.  It's faster on Powerstorm 300 (DEC).
 *   Input Arguments:
 *     window_index:  A window index
 *     protocol_version:   Negotiated ICP window protocol version number
 *     unicode_character_events_ok_p
 *                            Boolean, 1 if true, 0 if false.
 *      xclip_p
 *                            Boolean, 1 if true, 0 if false.
 *****************************************************************************/

void g2ext_x11_initialize_after_connection(window_index, protocol_version, unicode_character_events_ok_p, xclip_p)
     long window_index;
     long protocol_version;
     long unicode_character_events_ok_p, xclip_p;  /* boolean, actually */
{
#if defined(XWINDOWS)
  GensymXWindow *gwindow;
#endif

  if (No_window)
    return;

  ICP_window_protocol_version = protocol_version;

  unicode_is_handled_by_g2 = (int)unicode_character_events_ok_p;

#if defined(XWINDOWS)
  gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
  if ((gwindow->stippled_gc_clip_p = (xclip_p?TRUE:FALSE)) == TRUE)
    printf("`X Clipping' feature enabled, which may affect performance.\n");
#endif

  /* The following code is redundant. At this point, is_connected has already
   * been set by g2ext_x11_set_window_is_connected. More leftovers from 70r0
   * multiwindow mode. -fmw, 7/21/04 */
#if defined(MSWINDOWS)
  {
    HWND hwndServer = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
    LPG2INFO window_info = GetlpG2Info(hwndServer);
    window_info->is_connected = TRUE;
  }
#endif
}



/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/* The function g2ext_x11_set_window_title() sets the title bar text. */


#if defined(XWINDOWS)
/*   (Here we have the X Window System implementation; see below for the Windows
implementation.)  */

/* The constant MAX_XWIN_TITLE_LENGTH (defined as 255) sets a maximum reasonable
length for the title bar text -- includes all text, requiring one extra byte to
be allocated for the NUL termination character. */

/* The function crude_unicode_2_latin_1_duplicate() mallocs a string ("char *")
and copies the contents of the Unicode wide string title ("unsigned short *") to
the new string. However, only the least significant 8 bits of each character
code is put in the resulting string.  Since Unicode and the common
English/European character sets (ASCII/ISO Latin 1) encode characters their
common repertoire the same, this makes for a crude but effective transcoding.

Title should be terminated with a NUL character (0). The resulting string is
similarly NUL-terminated.

This uses malloc() to allocate the resulting string.  The resulting memory
should be freed by the caller using free().

The max argument gives the maximum number of characters to process, beginning
from the first character, from unicode_string. Unicode_string should be
NUL-terminated, and processing normally stops at the NUL, so this should
normally be an upper extreme limit. If greater than the length of
unicode_string, the resulting string will be just the length needed to contain
all the text in unicode_string, which is usually the same length, but may vary
somewhat due to character set translation. */

static char *crude_unicode_2_latin_1_duplicate (unsigned short *unicode_string, int max)
{
  int i, len = 0;
  char *char_string;
  const unsigned short unicode_NUL = (unsigned short)0;

  for (i = 0; ((i <= max) && (unicode_string[i] != unicode_NUL)); i++)
    len = i + 1;

  char_string = (char *)malloc((len + 1) * sizeof(char));

  for (i = 0; i < len; i++) {
    unsigned short unicode;
    char c;
    const char subst_char = '\?',
      space = ' ';

    unicode = unicode_string[i];

    if ((unicode == '\n') || (unicode == '\r') || (unicode == '\t')
        || (unicode == '\v') || (unicode == '\f'))
                                /* wierd whitespace (LF, CR, HT, VT, FF) =>
                                   Space. Assume NB space is OK as is. */
      c = space;
    else if (((unicode >= 32) && (unicode <= 126))
             || ((unicode >= 160) && (unicode <= 255))
             || (unicode == '\t'))
      /* printable ASCII/Latin-1 => pass straight through */
      c = (char)unicode;
    else
      c = subst_char;

    char_string[i] = c;
  }

  char_string[len] = '\0';

  return char_string;
}

/* NOTE: X just wants the string to be in the X host portable encoding. We
should use our Unicode -> X encoding translator, which gets defined by
TRANSCODE. Work on hooking this up later. It's low priority, since there is not
likely to be significant use of non-ASCII characters in host names at present!
(MHD 6/4/03) */



#define MAX_XWIN_TITLE_LENGTH 255

long g2ext_x11_set_window_title(long window_index, unsigned short *title)
{
  Display *display;
  Window window;
  GensymXWindow *gwindow;
  char *name;

  if (No_window)
    return -1;

  gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
  display = gwindow->display_ptr;
  window = gwindow->xwindow;
  name = crude_unicode_2_latin_1_duplicate(title, MAX_XWIN_TITLE_LENGTH);
  XStoreName(display, window, name);
  free(name);
  return 0;
}
#endif

#if defined(MSWINDOWS)
long g2ext_x11_set_window_title(long window_index, LPCWSTR title)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  /* hwndMain is the G2-Window, but hwndFrame has the title */
  SetWindowTextW(hwnd==hwndMain ? hwndFrame : hwnd, title);
  return 0;
}
#endif


/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_x11_set_window_is_connected(long window_index)
 *
 *   Description:
 *     tells us Telewindows is connected to G2
 *   Input Arguments:
 *     window_index:  A window index
 *   Returns:
 *     return value:  none (void)
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void g2ext_x11_set_window_is_connected(long window_index)
{
  if (No_window)
    return;
#if defined(XWINDOWS)
  {
    GensymXWindow *gwindow;
    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
    gwindow->is_connected = TRUE;
  }
#endif
#if defined(MSWINDOWS)
  {
    HWND hwndServer = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
    LPG2INFO window_info = GetlpG2Info(hwndServer);
    window_info->is_connected = TRUE;
  }
#endif
}



/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_x11_file_descriptor_for_window(long window_index)
 *
 *   Description:
 *     returns file descriptor of the given Gensym window
 *   Input Arguments:
 *     window_index:  A window index
 *   Returns:
 *     return value:  file descriptor of the stream on which incoming events
 *                    for the window index arrive. If no file descriptor which
 *                    satisfies this property can be found, then -1 is returned.
 *   Notes:
 *       11/3/93, fmw: The function g2ext_x11_file_descriptor_for_window returns the
 *     file descriptor of the stream on which incoming events for the given
 *     Gensym window index arrive. G2 assumes that a select() on the returned
 *     file descriptor will return whenever there is a pending event on the
 *     window. If no file descriptor which satisfies this property can be found,
 *     then -1 is returned.
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_file_descriptor_for_window (window_index)
     long window_index;
{
#   if defined(MSWINDOWS)
        return -1;
#   else /* XWindows */
        Display *display;
        GensymXWindow *gwindow;

        if (No_window)
            return -1;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        display = gwindow->display_ptr;
        return XConnectionNumber(display);
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_x11_make_xwindow_visible (long window_index)
 *
 *   Description:
 *     Displays the given window
 *   Input Arguments:
 *     window_index:  A window index
 *   Returns:
 *     None.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_x11_make_xwindow_visible (window_index)
     long window_index;
{
#   if defined(MSWINDOWS)
        HWND gwindow = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

        if (!No_window && IsWindow(gwindow) && !IsIconic(gwindow))
            ShowWindow(gwindow, SW_SHOWNORMAL);
#   else /* XWindows */
        Display *display;
        Window window;
        GensymXWindow *gwindow;

        if (No_window)
            return;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        display = gwindow->display_ptr;
        window = gwindow->xwindow;
        /* G2 is interested in the following X events */
        g2pvt_select_events(display, window, 0);

        /* Display the window  */
        XMapWindow (display, window);
        XSync(display, False);
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_x11_raise_window(long window_index)
 *
 *   Description:
 *     Makes the given window the topmost on the screen.
 *   Input Arguments:
 *     window_index:
 *   Returns:
 *     return value: 1
 *   Notes:
 *       10/6/93, mpc:  What's the difference between ShowWindow and
 *     the win32 API call SetForegroundWindow()?
 *     -----
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_raise_window(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)
        HWND gwindow = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

        if (!No_window) {
            if ( IsWindow( gwindow ) )
                if ( !IsIconic(gwindow) )
                    ShowWindow(gwindow, SW_SHOWNORMAL);
        }
#   else /* XWindows */
        GensymXWindow *gw;
        Display *display;
        Window window;

        if (No_window)
            return 1;

        gw = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        display = gw->display_ptr;
        window = gw->xwindow;

        XRaiseWindow(display,window);
        XSync(display,False);
#   endif

    return 1;
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_x11_close(long window_index)
 *
 *   Description:
 *     Closes the given window
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     None
 *   Notes:
 *       12/3/93, mpc:  For both TW and G2 this function is called exactly once:
 *     at shutdown. This is where we should perform cleanup (free system
 *     resources, etc) and kill our window.
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_x11_close(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)
        extern void CleanUpAll();
        HWND gwindow;

        if (No_window)
            return;

        gwindow = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

        /* If the window does not exist then can't find it in the  */
        /* server/host list. */
        if ( IsWindow(gwindow) ) {
            CleanUpAll();
            if(IsWindow(gwindow))      /* CleanUpAll probably already destroyed this. */
              DestroyWindow(gwindow);
            g2ext_decache_g2pointer (window_index);
        }
#   else /* XWindows */
        GensymXWindow *gwindow;
        Display *display;

        if (No_window)
            return;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        display = gwindow->display_ptr;

        XSync(display, False);

        XCloseDisplay(display);

        the_x_display = (Display *) 0;

        if (g2ext_window_network_interface_handle > -1) {
           g2ext_network_close(gwindow->network_interface_handle);
           gwindow->network_interface_handle = -1;
        }

        g2ext_decache_g2pointer (window_index);
        free((void *)gwindow);
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_x11_screen_depth(long window_index)
 *
 *   Description:
 *     gets screen depth (bits per pixel) of screen
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: number of bits per pixel for the screen
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

long g2ext_x11_screen_depth(window_index)
     long window_index;
{
    GensymXWindow *gwindow;

    if (No_window)
        return 1;

    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    return(DefaultDepthOfScreen(gwindow->screen_ptr));
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_x11_screen_depth( window_index )
     long window_index;
{
    HDC        hDC         = 0;
    long nReturn = 0;
    int        bitspixel, planes;
    HWND hwndServer;

    if (No_window) {
        return screen_depth_global;
    }

    hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

   /* If this is a valid window and we can get a valid */
    /*  Device Context, get the device info needed.     */
    if ( IsWindow(hwndServer) )
        if ( hDC = GetDC(NULL) ) {

            bitspixel = GetDeviceCaps( hDC, BITSPIXEL );
            planes    = GetDeviceCaps( hDC, PLANES );
            ReleaseDC( NULL, hDC );

            nReturn = bitspixel * planes;
        }

    return (nReturn);
}
#endif /* MSWINDOWS */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/





/*****************************************************************************
 * int g2ext_is_XPendingp()
 *
 *   Description:
 *     return non-zero if there are pending X events
 *   Input Arguments:
 *     None.
 *   Returns:
 *     return value: return non-zero if there are pending X events
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

int g_SyntheticDisplayEvents = 0;

int g2ext_is_XPendingp()
{
#if defined(MSWINDOWS)
    return 0;
#else /* XWindows */
  int event_count_after_flush;
  /* int event_count_before_flush; */

  if (No_window)
    return 0;

  if (the_x_display == NULL)
    return 0;

  /* event_count_before_flush = XEventsQueued(the_x_display,QueuedAlready);
   */
  event_count_after_flush = XEventsQueued(the_x_display,QueuedAfterFlush);

  return event_count_after_flush || g_SyntheticDisplayEvents;
#endif
}

int g2ext_countXEventsQueuedAlready()
{
#if defined(MSWINDOWS)
    return 0;
#else /* XWindows */
  int event_count_before_flush;

  if (No_window)
    return 0;

  if (the_x_display == NULL)
    return 0;

  event_count_before_flush = XEventsQueued(the_x_display,QueuedAlready);

  return event_count_before_flush;
#endif
}

/* g2ext_events_pending_p is just a little debugging thing -
   no one should worry about it */

int g2ext_events_pending_p(window_index)
  long window_index;
{
#if defined(MSWINDOWS)
    return 0;
#else /* XWindows */
  if (No_window)
    return 0;
  else
  {
    GensymXWindow *gw;
    Display *display;

    gw = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    display = gw->display_ptr;

    return XPending(display);
  }
#endif
}




/* Function set_window_area is defined both for Windows and for the X Window
   System. It determines the origin, width, and height for a Windows window, and
   sets the members of the supplied WINAREA structure.

   The width, height, x0, and y0 arguments express certain desired
   values for the area.  Negative values have special meanings. The
   final values for the members are calculated as follows:

     width or height == -1: CW_USEDEFAULT -- lets Windows determine
     the appropriate/default width.

     width or height == -2: fullscreen -- note: this means the entire
     screen, i.e., it covers the taskbar and everything

     width or height == -3: origin at (0, 0) in the parent window,
     width and height are 90% of the screen width and height

     otherwise: width and height arguments should be positive, and
     then they are used directly, though substitutions are made for
     unreasonable values.  If x0/y0 are -1, they are defaulted to (0,
     0) */

static void set_window_area(long width, long height, long x0, long y0, WINAREA *area)
{
  area->width
    = ((width == -2)
       ? screen_max_width_global
       : ((width == -1)
          ? ((screen_max_width_global * 90 ) / 100)
          : width));
  area->height
    = ((height == -2)
       ? screen_max_height_global
       : ((height == -1)
          ? ((screen_max_height_global * 90 ) / 100)
          : height));
  area->x
    = ((x0 == -1)           /* See Note 3, below */
       ? ((screen_max_width_global - area->width) / 2)
       : ((x0 >= 0)
          ? x0              /* See Note 4, below */
          : (screen_max_width_global - area->width + (x0 + 2))));
  area->y
    = ((y0 == -1)
       ? ((screen_max_height_global - area->height) / 2)
       : ((y0 >= 0)
          ? y0
          : (screen_max_height_global - area->height + (y0 + 2))));
}


/*
 Note 1: one important difference between Windows and X Windows is that the
 width and height args refer to the inside area in the X, but to the outside
 area in the Windows case.

 Note 2: width and height used to be limited to the screen max width/height on
 Windows only. That restriction was not common to X Windows, was unnecessary,
 and has been lifted.

 Note 3: x and y used to be set on Windows to (0, 0) in the default/90% case,
 but now it is set to a position such that the window is centered in the screen,
 as it has always been in the X Windows case.

 Note 4: this now handles negative x0/y0 as offsets from the bottom, right
 corner of the screen for both Windows and X Windows. Previously, Windows turned
 such values into (0, 0) relative to top, left corner of the screen.
 (MHD 11/24/01)

 ajs (4/10/96) Allow negative x0 and y0 except in default case see HQ-660734.
 -- update: now allow for Windows, too. (MHD 11/24/01) */


/*
 * UI Properties: Mouse Cursor, etc.
 */

int g_NoRaiseOnRightClick = 0;        /* Set to true only by newer G2s */

long g2ext_set_ui_property(long window_index, long property, long value)
{
  if(No_window)
    return 0;

  switch(property) {
   case UIPROP_MOUSE_CURSOR:
     return g2pvt_set_mouse_cursor(window_index, value);
   case UIPROP_THEME:
     return g2ext_nms_set_theme(value);
   case UIPROP_ENABLED:
#ifdef WIN32
     EnableWindow(hwndFrame, (value==0) ? FALSE : TRUE);
#endif                              /* TODO: For X11 */
     return 1;
   case UIPROP_NO_RAISE:            /* 82r1 */
     g_NoRaiseOnRightClick = value;
     break;
  }
  return 0;
}
