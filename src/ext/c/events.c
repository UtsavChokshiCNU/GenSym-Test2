/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      events.c
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
 +   MS Windows portions:
 +              ??/??/?? - 07-01-93   Richard Haggard, Kamal Bijlani
 +              07-08-93 - present    mpc
 +
 + Description:  This file contains the primitives used to get events and
 +               perform mouse and other non-keyboard event handling.
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
 +   Section:      FUNCTION GROUP - Event Functions
 +      g2pvt_select_events                 1111111 Conditionally Defined
 +      g2ext_x11_sync                          0000000 Mixed Ifdefs
 +      g2ext_x11_flush                         0000000 Mixed Ifdefs
 +      g2ext_x11_last_mouse_x_position         0000000 Mixed Ifdefs
 +      g2ext_x11_last_mouse_y_position         0000000 Mixed Ifdefs
 +      g2ext_x11_last_event_time               0000000 Mixed Ifdefs
 +      g2ext_x11_last_event_bits               0000000 Mixed Ifdefs
 +      g2ext_x11_last_window_x                 0000000 Mixed Ifdefs
 +      g2ext_x11_last_window_y                 0000000 Mixed Ifdefs
 +      g2ext_x11_last_window_width             0000000 Mixed Ifdefs
 +      g2ext_x11_last_window_height            0000000 Mixed Ifdefs
 +      g2ext_x11_last_expose_x_position        0000000 Mixed Ifdefs
 +      g2ext_x11_last_expose_y_position        0000000 Mixed Ifdefs
 +      g2ext_x11_last_expose_width             0000000 Mixed Ifdefs
 +      g2ext_x11_last_expose_height            0000000 Mixed Ifdefs
 +      g2ext_start_tracking_mouse              0000000 Mixed Ifdefs
 +      g2ext_stop_tracking_mouse               0000000 Mixed Ifdefs
 +      g2_keycode_for_mouse_button       1111111 Conditionally Defined
 +      GetG2Event                        1111111 Conditionally Defined
 *      ReclaimG2Event                    1111111 Conditionally Defined
 +      GetNextEvent                      1111111 Conditionally Defined
 +      StoreNextEvent                    0000000 Conditionally Defined
 +      g2ext_get_event                         0000000 Multiply Defined
 +
 + External Interface:
 +      void     g2ext_x11_sync(window_index)
 +                 Flushes the output buffer and waits until all requests have
 +                    been received and processed
 +                 Returns: None
 +
 +      void     g2ext_x11_flush(window_index)
 +                 Flushes the output buffer
 +                 Returns: None
 +
 +      long     g2ext_x11_last_mouse_x_position(window_index)
 +                 Return mouse position at time of last recorded event
 +                 Returns: mouse position
 +
 +      long     g2ext_x11_last_mouse_y_position(window_index)
 +                 Return mouse position at time of last recorded event
 +                 Returns: mouse position
 +
 +      long     g2ext_x11_last_event_time(window_index)
 +                 Return time of the last recorded mouse or keyboard event
 +                 Returns: time of event as non-negative integer milliseconds,
 +                          masked to 28 bits.
 +
 +      long     g2ext_x11_last_event_bits(window_index)
 +                 Returns the set of G2 modifier bits for the last event.
 +                 Returns: the set of G2 modifier bits
 +
 +      long     g2ext_x11_last_window_width(window_index)
 +                 Returns window width at time of last recorded event
 +                 Returns: window width
 +
 +      long     g2ext_x11_last_window_height(window_index)
 +                 Returns window height at time of last recorded event
 +                 Returns: window height
 +
 +      long     g2ext_x11_last_expose_x_position(window_index)
 +                 Returns window expose x at time of last recorded event
 +                 Returns: window expose x
 +
 +      long     g2ext_x11_last_expose_y_position(window_index)
 +                 Returns window expose y at time of last recorded event
 +                 Returns: window expose y
 +
 +      long     g2ext_x11_last_expose_width(window_index)
 +                 Returns window expose width at time of last recorded event
 +                 Returns: window expose width
 +
 +      long     g2ext_x11_last_expose_height(window_index)
 +                 Returns window expose height at time of last recorded event
 +                 Returns: window expose height
 +
 +      void     g2ext_start_tracking_mouse(window_index)
 +                 Enables notification of mouse tracking events
 +                 Returns: None
 +
 +      void     g2ext_stop_tracking_mouse(window_index)
 +                 Disables notification of mouse tracking events
 +                 Returns: None
 +
 +      long     g2ext_get_event(window_index)
 +                 Processes the X Events received
 +                 Returns: Event code
 +
 + Dependencies:
 +      This file has no external dependencies.
 +    extern long g2pvt_modifier_bits();
 +    extern long g2pvt_handle_keypress();
 +    extern int No_window;
 +
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
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#if defined(WIN32)
#    include <string.h>
#    include <math.h>
#    include <windows.h>
#    include "msincls.h"
#else
#    include <stdlib.h>
#    include <signal.h>
#endif
#include "cprim.h"
#include "graphics.h"
#include "networks.h"
#include "netevent.h"


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

#if defined(MSWINDOWS)
    /* This is used for event management functions. */
    static G2EVENT  *ReclaimedG2Events = (G2EVENT *) NULL;
#else
#    define ILLEGAL -1
#endif

#define ETRACE G2TRACE


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#if defined(MSWINDOWS)
    extern void ne_enqueue_next_event();
    extern long g2ext_window_width();
    extern long g2ext_window_height();

#else /* not MSWindows, must be XWindows */

#define DEFAULT_DOUBLE_CLICK_DELAY 250       /* milliseconds. */
    static int mouse_double_click_delay = 0; /* Initialized from window manager or default. */

    extern long g2pvt_modifier_bits();
    extern long g2pvt_handle_keypress();
    extern unsigned char  *latin_1_clipboard;
    extern unsigned char  *compound_text_clipboard;
    extern unsigned short *unicode_text_clipboard;
    extern long                   latin_1_clipboard_char_count;
    extern long            compound_text_clipboard_char_count;
    extern long            unicode_text_clipboard_char_count;
    extern Atom            compound_text_atom;
    extern Atom            targets_atom;
    extern Atom                   unicode_text_atom;
    extern Atom           *rep_types;

#endif /* MSWindows or XWindows */

extern int No_window;                /* defined in networks.c */
extern G2pointer g2ext_window_network_interface_handle;
extern int ne_use_sck;
int get_events_called_yet = FALSE;
extern int g2ext_product;
extern void g2ext_exit_from_lisp(long);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Event Functions
 %
 % Description:
 %   These functions are for event management
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
 * int g2pvt_select_events (Display *display, Window window, int mouse_motion_p)
 *
 *   Description:
 *     Select X events for G2.
 *   Input Arguments:
 *     display:
 *     window:
 *     mouse_motion_p:
 *   Returns:
 *     return value: 0
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

int g2pvt_select_events (display, window, mouse_motion_p)
     Display *display;
     Window window;
     int mouse_motion_p;
{
    int mask;

    /* G2 is interested in the following X events by default. */
    mask = ButtonPressMask | ExposureMask | KeyPressMask |
           ButtonMotionMask | ButtonReleaseMask |
           StructureNotifyMask | SubstructureNotifyMask |
           EnterWindowMask | LeaveWindowMask | FocusChangeMask;

    /* Sometimes G2 is interested in mouse motion, too. */

    /* We now need to enable mouse events always in order to detect the mouse
       hovering.  Although we receive the motion events from the X server, they
       still aren't passed on to G2 unless G2 requests them, so overhead should
       be low. In any case, this is no worse than using G2/TW with the icon
       editor active, which has always enabled motion events. -fmw, 11/15/06 */

/* if (mouse_motion_p) */
    mask |= PointerMotionMask;

    XSelectInput(display, window, mask);

    return 0;
}
#endif /* XWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * void g2ext_x11_sync(int window_index)
 *
 *   Description:
 *     flushes the output buffer and waits until all requests have been
 *     received and processed by the server.
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_x11_sync(window_index)
     int window_index;
{
    if (No_window)
        return;

#   if defined(MSWINDOWS)
#       if defined(WIN32)
            GdiFlush();
#       endif
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        XSync(gwindow->display_ptr, 0);
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_x11_flush(long window_index)
 *
 *   Description:
 *     flushes the output buffer
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     None
 *   Notes:
 *        08-feb-89, pto: XSync is called instead of XFlush because on
 *     the HP, XSync is able to NOT get wedged when lots of events are queued.
 *     XFlush can get wedged on some occasions.  We should get HP to fix this
 *     bug and revert to using XFlush.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_x11_flush(window_index)
     long window_index;
{
    if (No_window)
        return;

#   if defined(MSWINDOWS)
#       if defined(WIN32)
            GdiFlush();
#       endif
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        XFlush(gwindow->display_ptr);
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_x11_last_mouse_x_position(window_index)
 * long g2ext_x11_last_mouse_y_position(window_index)
 *
 *   Description:
 *     Return mouse position at time of last recorded event
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: mouse x/y position
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_last_mouse_x_position(window_index)
     long window_index;
{
    if (No_window)
        return 1;

#   if defined(MSWINDOWS)
    {
        HWND hWnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
        LPG2INFO lpG2Info = GetlpG2Info(hWnd);
        return lpG2Info->last_event_mouse_x;
    }
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_mouse_x );
    }
#   endif
}


long g2ext_x11_last_mouse_y_position(window_index)
     long window_index;
{
    if (No_window)
        return (1);

#   if defined(MSWINDOWS)
    {
        HWND hWnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
        LPG2INFO lpG2Info = GetlpG2Info(hWnd);
        return lpG2Info->last_event_mouse_y;
    }
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_mouse_y );
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_x11_last_event_time(long window_index)
 *
 *   Description:
 *     returns the time of the last recorded mouse or keyboard event
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: time of event as non-negative integer milliseconds,
 *                 masked to 28 bits.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_last_event_time(window_index)
     long window_index;
{
    if (No_window)
        return 0;

#   if defined(MSWINDOWS)
    {
        HWND hWnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
        LPG2INFO lpG2Info = GetlpG2Info(hWnd);
        return lpG2Info->last_event_time;
    }
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;
        Time time;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        time = gwindow->last_event_time;

        return((long) (time & EVENT_TIME_MASK));
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_x11_last_event_bits(long window_index)
 *
 *   Description:
 *     returns the set of G2 modifier bits for the last event.
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: the set of G2 modifier bits
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_last_event_bits(window_index)
     long window_index;
{
    if (No_window)
        return 0;

#   if defined(MSWINDOWS)
    {
        HWND hWnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
        LPG2INFO lpG2Info = GetlpG2Info(hWnd);
        return lpG2Info->last_event_bits;
    }
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return (long) gwindow->last_event_bits;
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_window_width(long window_index)
 *
 *   Description:
 *     get current window width
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: window width
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

static void get_x_window_geometry(GensymXWindow *gwindow)
{
  Window root;
  int x, y;
  unsigned int width, height, border_width, depth;

  XGetGeometry(gwindow->display_ptr, gwindow->xwindow,
               &root, &x, &y, &width, &height, &border_width, &depth);
  gwindow->last_window_x = x;
  gwindow->last_window_y = y;
  gwindow->last_window_width = width;
  gwindow->last_window_height = height;
}

long g2ext_window_width(long window_index)
{
  GensymXWindow *gwindow;

  if (No_window)
    return 1;
  gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
  get_x_window_geometry(gwindow);
  return gwindow->last_window_width;
}


#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)


static void get_ms_window_geometry(HWND hwnd, RECT *rect)
{
  if (!IsWindow(hwnd))
    return;

  /* SWV: If we are embedded, then pretend that the geometry of the G2 window
     (hwndMain) is that of the desktop window. This might change someday. */

  /* TODO: Use SM_X/YVIRTUALSCREEN SM_CX/YVIRTUALSCREEN to handle multiple
     monitors */

  if(Frame_is_embedded && hwnd == hwndMain)
    hwnd = hwndCoor;

  if (IsIconic(hwnd)) {
    WINDOWPLACEMENT  window_placement;

    window_placement.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(hwnd, &window_placement);
    CopyRect(rect, &window_placement.rcNormalPosition);
  } else {
    POINT p = {0,0};
    RECT c;

    /* The convention is that the size is of the client area of the window, and
       the position is of the upper-left corner of the client area, expressed in
       screen coordinates or in parent-client-coordinates (PCC) for MDI. */

    ClientToScreen(hwnd,&p);
    if(Frame_is_MDI && Frame_has_client)
      ScreenToClient(hwndClient,&p); /* Position in PCC, where parent is hwndClient. */
    GetClientRect(hwnd,&c);

    rect->left  = p.x;
    rect->top   = p.y;
    rect->right = rect->left + (c.right - c.left);
    rect->bottom = rect->top + (c.bottom - c.top);
  }
}


long g2ext_window_width( window_index )
     long window_index;
{
  RECT rect;
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  get_ms_window_geometry(hwnd, &rect);
  return rect.right - rect.left;
}
#endif /* MSWindows */

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

long g2ext_window_x(long window_index)
{
  GensymXWindow *gwindow;

  if (No_window)
    return 1;
  gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
  get_x_window_geometry(gwindow);
  return gwindow->last_window_x;
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_window_x (long window_index)
{
  RECT rect;
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  get_ms_window_geometry(hwnd, &rect);
  return rect.left;
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_window_height(long window_index)
 *
 *   Description:
 *     get current window height
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: window height
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

long g2ext_window_height(long window_index)
{
  GensymXWindow *gwindow;

  if (No_window)
    return 1;
  gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
  get_x_window_geometry(gwindow);
  return gwindow->last_window_height;
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_window_height (long window_index)
{
  RECT rect;
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  get_ms_window_geometry(hwnd, &rect);
  return rect.bottom - rect.top;
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_window_y(long window_index)
 *
 *   Description:
 *     get current window y
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: window y
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

long g2ext_window_y(long window_index)
{
  GensymXWindow *gwindow;

  if (No_window)
    return 1;

  gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
  get_x_window_geometry(gwindow);
  return gwindow->last_window_y;
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_window_y (long window_index)
{
  RECT rect;
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  get_ms_window_geometry(hwnd, &rect);
  return rect.top;
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_x11_last_window_x(window_index)
 * long g2ext_x11_last_window_y(window_index)
 * long g2ext_x11_last_window_width(window_index)
 * long g2ext_x11_last_window_height(window_index)
 *
 *   Description:
 *     return window x/y and width/height at time of last recorded event
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: window x/y, width/height
 *   Notes:
 *   Modifications: removed #ifdef VERBOSE code, added x/y -- mhd, 6/9/03
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_last_window_x(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)

    return (long)g2ext_window_x( window_index );

#   else /* XWINDOWS */
    if (No_window) {
        return (1);
    }
    else {
        GensymXWindow *gwindow;
        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return(gwindow->last_window_x);
    }
#   endif
}

long g2ext_x11_last_window_width(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)

    return (long)g2ext_window_width( window_index );

#   else /* XWINDOWS */
    if (No_window) {
        return (1);
    }
    else {
        GensymXWindow *gwindow;
        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_window_width );
    }
#   endif
}


long g2ext_x11_last_window_y(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)

    return (long)g2ext_window_y( window_index );

#   else /* XWINDOWS */
    if (No_window) {
        return (1);
    }
    else {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_window_y );
    }
#   endif
}

long g2ext_x11_last_window_height(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)

    return (long)g2ext_window_height( window_index );

#   else /* XWINDOWS */
    if (No_window) {
        return (1);
    }
    else {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_window_height );
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*********************************************************************
*
*  LPG2INFO        GetlpG2Info( HWND hWnd)
*
*  Purpose:
*
*     Return the address and handle of the G2Info belonging to the
*                passed in server.
*
*  Entry:
*
*     hWnd          - handle to the window.
*     lphG2Info          - pointer to where to put the handle to the G2 info memory.
*
*  Returns:
*
*     non-zero if successful.
*     Zero otherwise.
*
*  Comments:
*
*     If failure then the handle to memory is also zero'd.
*
***********************************************************************/
#if defined(MSWINDOWS)

LPG2INFO GetlpG2Info(HWND hwnd)
{
  if (!IsWindow(hwnd))
    return NULL;

  /* If the hwnd was not created by us, then it doesn't have the extra slot, so
   * we have to use window properties instead. The TW AXL control might want
   * to attach a G2INFO structure to the desktop window, for example. */

  if(g2pvt_window_has_info_slot_p(hwnd))
    return (LPG2INFO) GetWindowLong(hwnd, WW_G2_S_INFO);
  else
    return (LPG2INFO) GetProp(hwnd,"G2_S_INFO"); /* FIXME: Need unique propname per process. */
}

void SetlpG2Info(HWND hwnd, LPG2INFO info)
{
  if (!IsWindow(hwnd))
    return;

  if(g2pvt_window_has_info_slot_p(hwnd))
    SetWindowLong(hwnd, WW_G2_S_INFO, (LONG)info);
  else if(info)
    SetProp(hwnd,"G2_S_INFO",(HANDLE)info);
  else
    RemoveProp(hwnd,"G2_S_INFO");
}
#endif /* MSWindows */


/*****************************************************************************
 * long g2ext_x11_last_expose_x_position(window_index)
 * long g2ext_x11_last_expose_y_position(window_index)
 *
 *   Description:
 *     returns window expose x/y at time of last recorded event
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: window expose x/y
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_last_expose_x_position(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)
    {
        HWND hWnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
        LPG2INFO lpG2Info = GetlpG2Info(hWnd);
        return lpG2Info->last_event_expose_x;
    }
#   else /* XWINDOWS */
    if (No_window) {
        return (1);
    }
    else {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_expose_x );
    }
#   endif
}


long g2ext_x11_last_expose_y_position(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)
    {
        HWND hWnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
        LPG2INFO lpG2Info = GetlpG2Info(hWnd);
        return lpG2Info->last_event_expose_y;
    }
#   else /* XWINDOWS */
    if (No_window) {
        return (1);
    }
    else {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_expose_y );
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_x11_last_expose_width(window_index)
 * long g2ext_x11_last_expose_height(window_index)
 *
 *   Description:
 *     returns window expose width/height at time of last recorded event
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return val: window expose width/height
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_x11_last_expose_width(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)
    {
        HWND hWnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
        LPG2INFO lpG2Info = GetlpG2Info(hWnd);
        return lpG2Info->last_event_expose_width;
    }
#   else /* XWINDOWS */
    if (No_window) {
        return (1);
    }
    else {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_expose_width );
    }
#   endif
}


long g2ext_x11_last_expose_height(window_index)
     long window_index;
{
#   if defined(MSWINDOWS)
    {
        HWND hWnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
        LPG2INFO lpG2Info = GetlpG2Info(hWnd);
        return lpG2Info->last_event_expose_height;
    }
#   else /* XWINDOWS */
    if (No_window) {
        return (1);
    }
    else {
        GensymXWindow *gwindow;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        return( gwindow->last_expose_height );
    }
#   endif
}

/* Return the window_handle, if any, for given window_index. The handle is
 * assigned by G2 and if valid is always >= 1. */
long g2ext_x11_last_event_window_handle(long window_index)
{
  if (No_window)
    return -1;

#ifdef MSWINDOWS
  {
    HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
    LPG2INFO lpG2Info = GetlpG2Info(hwnd);
    return lpG2Info->last_event_window_handle;
  }
#else
  return -1;
#endif
}


/* If buflen is 0, return length of value string, or -1 if none.
   If buflen>0, fill buffer with string from last event, if any, NOT
   including a trailing NULL. */
long g2ext_x11_last_event_value(long window_index, unsigned short *buffer, long buflen)
{
  if (No_window)
    return -1;

#ifdef MSWINDOWS
  {
    HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
    LPG2INFO lpG2Info = GetlpG2Info(hwnd);
    if(lpG2Info->last_event_value == NULL)
      return -1;
    else if (buflen == 0)
      return wcslen(lpG2Info->last_event_value);
    else {
      int len = wcslen(lpG2Info->last_event_value);
      wcsncpy(buffer, lpG2Info->last_event_value, MIN(len,buflen));
      return len;
    }
  }
#else
  return -1;
#endif
}

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_start_tracking_mouse(window_index)
 *
 *   Description:
 *     Enables notification of mouse tracking events
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_start_tracking_mouse(window_index)
     long window_index;
{
    if (No_window)
        return;

#   if defined(MSWINDOWS)
    {
        HWND            gwindow;

        gwindow = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
        if (IsWindow(gwindow)) {
          LPG2INFO lpG2Info = GetlpG2Info(gwindow);
          lpG2Info->mouse_tracking = TRUE;
        }
    }
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;
        Display *display;
        Window window;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        display = gwindow->display_ptr;
        window = gwindow->xwindow,
        gwindow->tracking_mouse = TRUE;
        g2pvt_select_events(display, window, 1);
        XFlush(display);
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_stop_tracking_mouse(window_index)
 *
 *   Description:
 *     Disables notification of mouse tracking events
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_stop_tracking_mouse(window_index)
     long window_index;
{
    if (No_window)
        return;

#   if defined(MSWINDOWS)
    {
        HWND            gwindow;

        gwindow = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
        if (IsWindow(gwindow)) {
          LPG2INFO lpG2Info = GetlpG2Info(gwindow);
          lpG2Info->mouse_tracking = FALSE;
        }
    }
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;
        Display *display;
        Window window;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        display = gwindow->display_ptr;
        window = gwindow->xwindow;
        gwindow->tracking_mouse = FALSE;
        g2pvt_select_events(display, window, 0);
        XFlush(display);
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_ungrab_mouse(window_index)
 *
 *   Description:
 *     Allows other window to get mouse events
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     None
 *   Notes: jh, 1/24/96.  For OLE drag-and-drop experiments.
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_ungrab_mouse(window_index)
     long window_index;
{
    if (No_window)
        return;

#   if defined(MSWINDOWS)
        /* ReleaseCapture(); */
        return;
#   else /* XWINDOWS */
    {
        GensymXWindow *gwindow;
        Display *display;

        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
        display = gwindow->display_ptr;

        XUngrabPointer(display, CurrentTime);
    }
#   endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*****************************************************************************
* int get_mouse_double_click_delay (display)
*
*  Retrieves the double-click delay (milliseconds) from the window manager,
*  if possible, otherwise from our internal default. We ask the window manager only once,
*  and cache that value if found.
*
* It's OK that we call this only once/process, since that is what other X applications
* do (they must be restarted to get a new double-click time).
* *****************************************************************************/
#if defined(XWINDOWS)
static int get_mouse_double_click_delay (Display *display)
{
  XrmDatabase database = NULL;
  char *data;
  char *type;
  XrmValue value;

  if(mouse_double_click_delay > 0)
    return mouse_double_click_delay;

  mouse_double_click_delay = DEFAULT_DOUBLE_CLICK_DELAY;
  if (No_window)
    return mouse_double_click_delay;

  XrmInitialize();
  if(!(data=XResourceManagerString(display))) goto DONE;
  if(!(database=XrmGetStringDatabase(data)))  goto DONE;
  if(!XrmGetResource(database, "multiClickTime", "MultiClickTime", &type, &value)) goto DONE;
  if(strcmp(type,"String") != 0) goto DONE;

  mouse_double_click_delay = atoi(value.addr);
  if(mouse_double_click_delay <= 0)
    mouse_double_click_delay = DEFAULT_DOUBLE_CLICK_DELAY;

DONE:
  if(database) XrmDestroyDatabase(database);
  return mouse_double_click_delay;
}
#endif


/*****************************************************************************
 * long g2_keycode_for_mouse_button(display, event_type, button, state, dt)
 *
 *   Description:
 *     Return the G2 key code for a button press or release
 *   Input Arguments:
 *     display    X display
 *     event_type
 *     button
 *     state
 *     dt         milliseconds since last press/release of SAME button.
 *   Returns:
 *     return value: G2 key code for a button press or release
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

static long g2_keycode_for_mouse_button(Display *display,
                                        int event_type, int button, int state, int dt)
{
  int down_p = (event_type == ButtonPress);
  long modifier_bits = 0;
  int key_code = -1;

  if (event_type == MotionNotify)
    key_code = GENSYM_MOUSE_MOTION;
  else
    /* Remappable button positions? */
    switch(button) {
    case Button1:
      key_code = down_p ? GENSYM_MOUSE_LEFT_DOWN : GENSYM_MOUSE_LEFT_UP;
      break;

    case Button2:
      key_code = down_p ? GENSYM_MOUSE_MIDDLE_DOWN : GENSYM_MOUSE_MIDDLE_UP;
      break;

    case Button3:
      key_code = down_p ? GENSYM_MOUSE_RIGHT_DOWN : GENSYM_MOUSE_RIGHT_UP;
      break;

    case Button4:
      key_code = GENSYM_MOUSE_WHEEL_FORWARD;
      break;

    case Button5:
      key_code = GENSYM_MOUSE_WHEEL_BACKWARD;
      break;
    }

  /* never a caps lock bit */
  state &= ~LockMask;

  modifier_bits = g2pvt_modifier_bits(state);

  /* Note that we won't set the double bit here if user rapidly clicks left then right,
   * eg, because DT is the time since the last event on the SAME button. */
  if (down_p && event_type != MotionNotify && (0 <= dt) && (dt < get_mouse_double_click_delay(display)))
    modifier_bits |= X11_DOUBLE_BIT;

  return modifier_bits | key_code;
}
#endif /* XWindows */

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * G2EVENT *GetG2Event()
 *
 *   Description:
 *     Creates and returns a new event struct
 *   Input Arguments:
 *     None
 *   Returns:
 *     return value: an event struct pointer
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(MSWINDOWS)

static G2EVENT *GetG2Event()
{
    G2EVENT *event;

    if (ReclaimedG2Events != (G2EVENT *) NULL) {
        event = ReclaimedG2Events;
        ReclaimedG2Events = event->next;
    }
    else {
        event = (G2EVENT *) malloc(sizeof(G2EVENT));
        if (event == (G2EVENT *) NULL) {
            /* $$$$ change this to window popup message */
            /* printf("Error BAD G2EVENT memory allocate\n"); */
            return (G2EVENT *) NULL;
        }
    }
    event->value = NULL;
    event->next = (G2EVENT *) NULL;
    return (event);
}
#endif /* MSWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * void ReclaimG2Event(G2EVENT *event)
 *
 *   Description:
 *     Frees memory for a G@EVENT.  Please do not inline.
 *   Input Arguments:
 *     event
 *   Returns:
 *     None.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(MSWINDOWS)

void ReclaimG2Event(event)
    G2EVENT *event;
{
  if(event->value != NULL) {
    free(event->value);
    event->value = NULL;
  }
 event->next = ReclaimedG2Events;
 ReclaimedG2Events = event;
}
#endif /* MSWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * G2EVENT *GetNextEvent()
 *
 *   Description:
 *     Pops an event off the internal event queue
 *   Input Arguments:
 *     None
 *   Returns:
 *     return value: an event struct pointer
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(MSWINDOWS)

G2EVENT *GetNextEvent(lpG2Info)
     LPG2INFO        lpG2Info;
{
    G2EVENT *event;

    event = lpG2Info->events_head;
    if (event != (G2EVENT *) NULL) {
        lpG2Info->events_head = event->next;
        if (event->next == (G2EVENT *) NULL)
            lpG2Info->events_tail = (G2EVENT *) NULL;
    }
    return (event);
}
#endif /* MSWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * void StoreNextEvent(hWnd, eventtype, x, y, width, height, key_code, key_bits)
 *
 *   Description:
 *     Puts an event in the internal event queue
 *   Input Arguments:
 *     hWnd             -- Win32 window related to this event in some way.
 *     eventtype        -- X11_KEYPRESS, X11_CONTROL, etc.
 *                          Determines meaning of remaining args
 *     x,y,width,height -- Generally the mouse position, exposure area, etc.
 *     key_code         -- Generally a Gensym key code.
 *     key_bits         -- Generally a bitmask of shift, control, alt, etc, modifiers.
 *   Returns:
 *     return value: none
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000 Conditionally Defined 0000000000000000000000000000*/
#if defined(MSWINDOWS)

#ifdef _DEBUG
static char *event_type_names[] = {"X11_NULLEVENT", "X11_KEYPRESS", "X11_BUTTON_PRESS",
                                   "X11_BUTTON_RELEASE", "X11_POINTER_MOTION",
                                   "X11_EXPOSURE", "X11_RESHAPE",
                                   "X11_ENTER", "X11_LEAVE", "X11_FOCUS_IN", "X11_FOCUS_OUT",
                                   "X11_CONTROL"};
#endif

void StoreNextEvent(hwnd, eventtype, x, y, width, height, key_code, key_bits)
     HWND hwnd;
     long eventtype, x, y, width, height, key_code, key_bits;
{
  StoreNextEventEx(hwnd, eventtype, x, y, width, height, key_code, key_bits, NULL);
}

void StoreNextEventEx(HWND hwnd, long eventtype, long x, long y, long width, long height,
                      long key_code, long key_bits, LPWSTR value)
{
  g2pvt_send_event(hwnd, g2pvt_window_handle(hwnd), eventtype,
                   x, y, width, height, key_code, key_bits, value);
}

/*
 * Send event associated with window HWND, with G2-assigned handle HANDLE, to
 * G2. If handle is -1, assume hwnd is managed by the C code such that
 * g2pvt_window_handle will get the handle. (TWNG does this differently).
 *
 * The event is actually enqueued for the next time g2ext_get_event() is called.
 */

void g2pvt_send_event(HWND hwnd, int handle,
                      int eventtype, long x, long y, long width, long height,
                      long key_code, long key_bits, LPWSTR value)
{
  G2EVENT *event;
  LPG2INFO lpG2Info;

  event = GetG2Event ();
  if (event)
    {
      event->hwnd = hwnd;
      event->window_handle = (handle >= 0) ? handle : g2pvt_window_handle(hwnd);
      event->type = eventtype;
      event->x    = x;
      event->y    = y;
      event->width = width;
      event->height = height;
      event->key_code = key_code;
      event->key_bits = key_bits;
      event->time = GetTickCount() & (unsigned long)EVENT_TIME_MASK;
      if(value) event->value = wcsdup(value);
      event->next = (G2EVENT *) NULL;

/*       ETRACE("StoreNextEvent: hwnd:%x %s %d,%d %dx%d key=%d [%d] %ls\n", */
/*              hwnd, event_type_names[eventtype], x, y, width, height, */
/*              key_code, event->window_handle, event->value ? event->value : L""); */

      if (lpG2Info = GetlpG2Info(hwndMain)) /* Always queue on the main window. */
        {
          if (lpG2Info->events_tail == (G2EVENT *) NULL) {
            lpG2Info->events_tail = event;
            lpG2Info->events_head = event;
          } else {
            lpG2Info->events_tail->next = event;
            lpG2Info->events_tail = event;
          }
        }
      ne_enqueue_next_event(display_event, 0, 0);
    }
}

#endif /* MSWindows */
/*000000000000000000000000 Conditionally Defined 0000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_get_event(long window_index)
 *
 *   Description:
 *     processes the X Events received
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return value:
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

extern int g2pvt_ensure_timeout_callback(int timeout, void (*callback)(), void *arg);
extern int g_SyntheticDisplayEvents;  /* Set this to wakeup event loop. */

static int g_MouseHoverTimeout = 400; /* Milliseconds */
static int g_MouseHoverWidth = 4;     /* Pixels */
static int g_MouseHoverHeight = 4;    /* Pixels */
static void ensure_mouse_hover_tracking(GensymXWindow *gwindow);

/* Called when the hover timeout expires */
static void mouse_hover_callback(void *arg)
{
  GensymXWindow *gwindow = (GensymXWindow*)arg;

  gwindow->hover_timer_active_p = FALSE;

  if(abs(gwindow->last_mouse_x - gwindow->hover_x) <= g_MouseHoverWidth &&
     abs(gwindow->last_mouse_y - gwindow->hover_y) <= g_MouseHoverHeight) {
    g_SyntheticDisplayEvents = 1;
    gwindow->hover_event = TRUE;
  } else {
    ensure_mouse_hover_tracking(gwindow);
  }
}

static void ensure_mouse_hover_tracking(GensymXWindow *gwindow)
{
  if(gwindow->hover_timer_active_p)
    return;

  gwindow->hover_timer_active_p = TRUE;
  gwindow->hover_x = gwindow->last_mouse_x;
  gwindow->hover_y = gwindow->last_mouse_y;
  g2pvt_ensure_timeout_callback(g_MouseHoverTimeout, mouse_hover_callback, (void *)gwindow);
}

long g2ext_get_event(window_index)
     long window_index;
{
  XEvent event_array[2];
  XEvent *event;
  int next_event_index = 0;
  int number_of_pending_events;
  Display *display;
  GensymXWindow *gwindow;
  long g2_keycode;
  int event_count = 0;
  XMotionEvent *motion_event;
  unsigned int state;
  XButtonEvent *button_event;
  unsigned int button;
  Time last_time, this_time;
  int g2_event_type, dt, last_time_valid;
  XExposeEvent *expose_event;
  long new_x, new_y, new_width, new_height;
  Window window;
  XSelectionEvent ev_notify;

  if (No_window)
    return (-1);


  gwindow =  (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
  if (ne_use_sck)
    ne_enable_read_events(gwindow->network_interface_handle);
  display = gwindow->display_ptr;

  if (!get_events_called_yet) {
    get_events_called_yet = TRUE;
    gwindow->last_expose_x      = 0;
    gwindow->last_expose_y      = 0;
    gwindow->last_expose_width  = gwindow->last_window_width;
    gwindow->last_expose_height = gwindow->last_window_height;
    return(X11_EXPOSURE);
  }

  if(gwindow->hover_event) {
    g_SyntheticDisplayEvents = 0;
    gwindow->hover_event = FALSE;
    g2_keycode = GENSYM_MOUSE_HOVER;
    return (g2_keycode << X11_NUMBER_OF_BITS_IN_EVENT_CODES) | X11_POINTER_MOTION;
  }

  number_of_pending_events = XPending(display);
  if(number_of_pending_events == 0)
    return(X11_NO_MORE_EVENTS);

  XNextEvent(display, &(event_array[next_event_index]));
  number_of_pending_events--;


  /* Compress Mouse Motion Events
   * Keep checking for consecutive MotionNotifys and take the last one,
   * putting the first non-MotionNotify back into the event queue.
   */
  if( event_array[next_event_index].type == MotionNotify) {
    while (event_count < number_of_pending_events) {
      next_event_index = (next_event_index ? 0 : 1);
      XNextEvent(display, &(event_array[next_event_index]));
      if (event_array[next_event_index].type != MotionNotify) {
          XPutBackEvent(display, &(event_array[next_event_index]));
          next_event_index = (next_event_index ? 0 : 1);
          /* the last MotionNotify */
          break;                /* out of the while loop */
      }
      event_count++;
    }
  }

  event = &(event_array[next_event_index]);

  switch (event->type) {
  case MotionNotify:
    motion_event = (XMotionEvent *)event;
    state   = motion_event->state;
    gwindow->last_mouse_x = (long) motion_event->x;
    gwindow->last_mouse_y = (long) motion_event->y;
    gwindow->last_event_bits = g2pvt_modifier_bits(motion_event->state);
    gwindow->last_event_time = motion_event->time;

    ensure_mouse_hover_tracking(gwindow);

    if(!gwindow->tracking_mouse)
      return X11_NULLEVENT;

    g2_keycode = g2_keycode_for_mouse_button(display, event->type, 0, state, 0);

    if (g2_keycode == -1)
      return X11_NULLEVENT;

    return (g2_keycode << X11_NUMBER_OF_BITS_IN_EVENT_CODES) | X11_POINTER_MOTION;

  case SelectionClear:
    {
      XSelectionClearEvent * selection_event = (XSelectionClearEvent*)event;

      gwindow->last_event_time = selection_event->time;
      latin_1_clipboard[0] = (unsigned char)NULL;
      latin_1_clipboard_char_count = 0;
      compound_text_clipboard[0] = (unsigned char)NULL;
      compound_text_clipboard_char_count = 0;
      unicode_text_clipboard[0] = (unsigned short)NULL;
      unicode_text_clipboard_char_count = 0;
    }
    /* we don't really need to do anything here if we are writing
    ** to the scrapbook. Nothing needs clearing on the display.
    */
    return X11_NULLEVENT; /* later: return something meaningful */
    break; /* should never happen */

  case SelectionRequest:
    {
      /* provide the data to external users */
      XSelectionRequestEvent *e = (XSelectionRequestEvent*)event;

      gwindow->last_event_time = e->time;
      if (e->target == targets_atom)
        {
          /*
          ** Make a list of the values (as atoms) that we serve,
          ** e.g. STRING and COMPOUND_TEXT, and then serve that list
          */
#           define number_of_clipboard_data_types 3

          if (!rep_types)
            rep_types = (Atom *)malloc
              (number_of_clipboard_data_types*sizeof(Atom));
          if (rep_types)
            {
              ev_notify.property = e->property;
              rep_types[0] = XA_STRING;
              rep_types[1] = compound_text_atom;
              rep_types[2] = unicode_text_atom;
              XChangeProperty(display, e->requestor,
                              e->property, XA_ATOM,
                              32,
                              PropModeReplace,
                              (unsigned char *)rep_types,
                              number_of_clipboard_data_types);
            }
          /* note: rep_types is cached for use later.
          ** if we want to free it after each use,
          ** then need to watch for SelectionNotify
          ** events on the recipient as a sign of
          ** success, and then can free the
          ** memory. Not worth it for 8 bytes. Can
          ** free on program exit.
          */
        }
      else
        /* This is how we actually give the string to the
        ** requestor: by changing a property,
        ** and writing the string on that property
        */
        /* From man page for XChangeProperty:
     "format" specifies whether the data should be viewed as a list of 8-bit,
     16-bit, or 32-bit quantities.  Possible values are 8, 16, and 32.  This
     information allows the X server to correctly perform byte-swap operations
     as necessary.  If the format is 16-bit or 32-bit, you must explicitly cast
     your data pointer to a (char *) in the call to XChangeProperty.
         */
        if (e->target == XA_STRING)
          {
            ev_notify.property = e->property;
            XChangeProperty(display, e->requestor,
                            e->property, e->target,
                            EIGHT_BIT_FORMAT,
                            PropModeReplace,
                            latin_1_clipboard,
                            latin_1_clipboard_char_count);
          }
        else
          if (e->target == compound_text_atom)
            {
              ev_notify.property = e->property;
              XChangeProperty(display, e->requestor,
                              e->property, e->target,
                              EIGHT_BIT_FORMAT,
                              PropModeReplace,
                              compound_text_clipboard,
                              compound_text_clipboard_char_count);
            }
          else
            if (e->target == unicode_text_atom)
              { /* see g2ext_read_clipboards(): call to fetch_8bit_data */
                ev_notify.property = e->property;
                XChangeProperty(display, e->requestor,
                                e->property, e->target,
                                EIGHT_BIT_FORMAT,
                                PropModeReplace,
                                (unsigned char *)unicode_text_clipboard,
                                (unicode_text_clipboard_char_count *
                                 sizeof(unsigned short)));
              }
            else
              /* should handle TIMESTAMP (and MULTIPLE) here */
              {
                ev_notify.property = None;
              }
      ev_notify.type = SelectionNotify;
      ev_notify.serial = e->serial;
      ev_notify.send_event = True;
      ev_notify.display = e->display;
      ev_notify.requestor = e->requestor;
      ev_notify.selection = e->selection;
      ev_notify.target= e->target;
      ev_notify.time = e->time;
      XSendEvent(display, e->requestor,
                 False, 0, (XEvent*)&ev_notify);

      return X11_NULLEVENT; /* Later: need to return something else */
    }
    break;

  case ButtonPress:
  case ButtonRelease:
    button_event = (XButtonEvent *)event;
    state   = button_event->state;
    button  = button_event->button;
    this_time = button_event->time;

    gwindow->last_mouse_x = (long) button_event->x;
    gwindow->last_mouse_y = (long) button_event->y;
    gwindow->last_event_bits = g2pvt_modifier_bits(button_event->state);
    gwindow->last_event_time = button_event->time;

    if (event->type == ButtonPress) {
      last_time_valid = (gwindow->last_button_press_time_valid_p>>button) & 1;
      last_time = gwindow->last_button_press_time[button];
      gwindow->last_button_press_time_valid_p |= 1<<button;
      gwindow->last_button_press_time[button] = this_time;
      g2_event_type = X11_BUTTON_PRESS;
    } else {
      last_time_valid = (gwindow->last_button_release_time_valid_p>>button) & 1;
      last_time = gwindow->last_button_release_time[button];
      gwindow->last_button_release_time_valid_p |= 1<<button;
      gwindow->last_button_release_time[button] = this_time;
      g2_event_type = X11_BUTTON_RELEASE;
    }

    if(last_time_valid)
      dt = this_time - last_time;
    else
      dt = 100000;                /* Arb. to not trigger double-click: 100 seconds */

    /* Special case: convert Button[45] down events into mouse wheel
     * keystrokes in the conventional way. Perhaps this should be handled by G2
     * so that mice which really have 4 or more buttons can be supported, but
     * this will do for now. Typically those multibutton mice have drivers which
     * convert the extra buttons into various keystrokes, so we never see them.
     * -fmw, 9/11/02 */
    if(button == Button4 || button == Button5) {
      g2_event_type = X11_KEYPRESS;
      if(event->type == ButtonPress)
        g2_keycode = (button==Button4) ? GENSYM_MOUSE_WHEEL_FORWARD : GENSYM_MOUSE_WHEEL_BACKWARD;
      else
        g2_keycode = -1;        /* Ignore Button[45] up events, if any. */
    } else {
      g2_keycode = g2_keycode_for_mouse_button(display, event->type, button, state, dt);
    }

    if (g2_keycode == -1)
      return X11_NULLEVENT;

    return (g2_keycode << X11_NUMBER_OF_BITS_IN_EVENT_CODES) | g2_event_type;

  case Expose:
  case GraphicsExpose:
    expose_event = ((XExposeEvent *)event);
    gwindow->last_expose_x      = (long)(expose_event->x);
    gwindow->last_expose_y      = (long)(expose_event->y);
    gwindow->last_expose_width  = (long)(expose_event->width);
    gwindow->last_expose_height = (long)(expose_event->height);
    return(X11_EXPOSURE);

  case DestroyNotify:
    return(X11_NULLEVENT);

  case ConfigureNotify:
    new_x = ((XConfigureEvent *)event)->x;
    new_y = ((XConfigureEvent *)event)->y;
    new_width = ((XConfigureEvent *)event)->width;
    new_height = ((XConfigureEvent *)event)->height;
    window = ((XConfigureEvent *)event)->window;

    /* Not us (paranoia) */
    if (window != gwindow->xwindow)
      return(X11_NULLEVENT);

    /* No change */
    if (/* new_x == gwindow->last_window_x && */  /* We don't care about the position. */
        /* new_y == gwindow->last_window_y && */
        new_width == gwindow->last_window_width &&
        new_height == gwindow->last_window_height)
      return(X11_NULLEVENT);
    else {
      gwindow->last_window_x = new_x;
      gwindow->last_window_y = new_y;
      gwindow->last_window_width = new_width;
      gwindow->last_window_height = new_height;
      return(X11_RESHAPE);
    }

  case EnterNotify: return X11_ENTER;
  case LeaveNotify: return X11_LEAVE;

  case FocusIn:     return X11_FOCUS_IN;

  case KeyPress:
    return (g2pvt_handle_keypress(event, display, gwindow));

  case MappingNotify:
    XRefreshKeyboardMapping((XMappingEvent *)event);
    return(X11_NULLEVENT);

  /* GENSYMCID-1207: Disable the window close button of G2 server on Linux */
  case ClientMessage:
  {
    XClientMessageEvent *e = (XClientMessageEvent *)event;
    if (e->message_type == XInternAtom(display, "WM_PROTOCOLS", False) &&
        e->format == 32 &&
        e->data.l[0] == (long) XInternAtom(display, "WM_DELETE_WINDOW", False) &&
        g2ext_product != G2_CMD)
    {
        g2ext_exit_from_lisp(0);
    }
    return(X11_NULLEVENT);
  }

  default:
    return (X11_NULLEVENT);
  }
}

#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_get_event(long window_index)
{
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  LPG2INFO lpG2Info = GetlpG2Info(hwnd);
  long ret_value = X11_NO_MORE_EVENTS;
  G2EVENT *event;

  if (No_window)
    return ret_value;

  /*
   * In X Windows, each call to check for pending events (XPending())
   * implicitly flushes all graphics.  In WNT, it seems to flush only if a pending
   * event actually exists, with the result that there are still occasions when
   * G2's screen does not update immediately in WNT.  Flushing graphics here
   * makes WNT more accurately simulate X Windows and fixes bug HQ-103482.
   * -fmw, 2/24/95
   */
  if (hwnd != (HWND) NULL)
    GdiFlush();
  else
    return ret_value;                /* peek etc moved to nt-next-event.c */

  event = GetNextEvent(lpG2Info);

  if (event == (G2EVENT *) NULL)
    return ret_value;

  ret_value = (long) event->type;

  /* Record the source hwnd in all cases. */
  lpG2Info->last_event_window_handle = event->window_handle;

  /* Record the mouse position in last_event_mouse_x,y relative to
   * last_event_window_handle. This is already in the event for keyboard and
   * mouse events. Otherwise, we need to get it now. Formerly, the code simply
   * used whatever was in last_event_mouse_x,y from the last event, which worked
   * when there was no possibility of the window_handle changing. */

  if(event->type == X11_KEYPRESS || event->type == X11_BUTTON_PRESS ||
     event->type == X11_BUTTON_RELEASE || event->type == X11_POINTER_MOTION) {
    lpG2Info->last_event_mouse_x = (long) event->x;
    lpG2Info->last_event_mouse_y = (long) event->y;

  } else {
    POINT p;
    HWND hwndMouse = (event->window_handle>=0) ? event->hwnd : hwndMain;
    GetCursorPos(&p);
    ScreenToClient(hwndMouse, &p);
    lpG2Info->last_event_mouse_x = p.x;
    lpG2Info->last_event_mouse_y = p.y;
  }

/*   ETRACE("g2ext_get_event: %x %s [%d]\n", */
/*          hwnd, event_type_names[event->type], lpG2Info->last_event_window_handle); */

  switch(ret_value)
    {
     case X11_KEYPRESS:
     case X11_BUTTON_PRESS:
     case X11_BUTTON_RELEASE:
     case X11_POINTER_MOTION:
       lpG2Info->last_event_bits = (long) event->key_bits;
       lpG2Info->last_event_time = (long) event->time;
       ret_value = (((long)event->key_code | (long) event->key_bits)
                    << X11_NUMBER_OF_BITS_IN_EVENT_CODES) | ret_value;
       break;

     case X11_EXPOSURE:
       lpG2Info->last_event_expose_x = (long) event->x;
       lpG2Info->last_event_expose_y = (long) event->y;
       lpG2Info->last_event_expose_width = (long) event->width;
       lpG2Info->last_event_expose_height = (long) event->height;
       ETRACE("EXPOSE %x %d,%d %dx%d [%d]\n",
              hwnd, event->x, event->y, event->width, event->height,
              event->window_handle);
       break;

     case X11_RESHAPE:
       lpG2Info->last_event_expose_width = event->width;
       lpG2Info->last_event_expose_height = event->height;
       break;

     case X11_CONTROL:
       /* This is intended to be an arbitrary packed message from a Win32
        * control.  We overload x,y,width,height in the same way that Windows
        * overloads the lparam and wparam in messages.  The keycode is
        * intended to indicate the class of control.  So far we have
        * GENSYM_HSCROLL and GENSYM_VSCROLL defined.

        * These events wind up in the same event queue as keystrokes, but
        * with additional information in the event plist. */

       lpG2Info->last_event_expose_x = (long) event->x;
       lpG2Info->last_event_expose_y = (long) event->y;
       lpG2Info->last_event_expose_width = (long) event->width;
       lpG2Info->last_event_expose_height = (long) event->height;

       /* We take ownership of the string value, if any. */
       if(lpG2Info->last_event_value) free(lpG2Info->last_event_value);
       lpG2Info->last_event_value = event->value;
       event->value = NULL;

       ETRACE("g2ext_get_event X11_CONTROL key=%d value=\"%ls\"\n",
              event->key_code,
              lpG2Info->last_event_value ? lpG2Info->last_event_value : L"(null)");

       /* The key-code indicates the class of control. */
       ret_value = (((long)event->key_code | (long) event->key_bits)
                    << X11_NUMBER_OF_BITS_IN_EVENT_CODES) | ret_value;
       break;
    }

  ReclaimG2Event(event);

  return ret_value;
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
