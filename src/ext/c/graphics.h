
#ifndef _CPRIM_H
#  error "You must include cprim.h before graphics.h"
#endif

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#if !defined(WIN32)
#  include <X11/X.h>
#  include <X11/Xlib.h>
#  include <X11/keysym.h>
#  include <X11/Intrinsic.h>
#  include <X11/Shell.h>
#  include <X11/IntrinsicP.h>
#  include <X11/Xatom.h>
#  include <X11/cursorfont.h>
#endif

/*
 * X11 Key Press Modifier Bits
 * These constants have to be maintained in parallel with those in
 * the lisp module KEYBOARDS.
 */
#define X11_UNICODE_BIT		(1 << 24) /* New (MHD 5/17/99) */
#define X11_CONTROL_BIT		(1 << 23)
#define X11_META_BIT       	(1 << 22)
#define X11_EXTEND_CHAR_BIT	(1 << 21)
#define X11_COMPOSE_CHAR_BIT	(1 << 20)
#define X11_ALTERNATE_BIT	(1 << 19)
#define X11_SHIFT_BIT           (1 << 18)
#define X11_CAPS_LOCK_BIT       (1 << 17)
#define X11_DOUBLE_BIT          (1 << 16) /* For double mouse clicks. */


/*
 * G2 Keyboard Constants
 * These constants have to be maintained in parallel with those in
 * the lisp module KEYBOARDS.
 */
#define NUMBER_OF_KEY_INDEX_BITS	11 /* number-of-key-index-bits in G2 */
#define KEY_INDEX_BITS			( (1 << NUMBER_OF_KEY_INDEX_BITS) - 1 )

#define X11_OR			 0
#define X11_COPY		 1
#define X11_XOR			 2
#define X11_AND                  3
#define X11_STIPPLED             4
#define X11_TRANSPARENT_COPY     5


/*
 * Special Key Definitions
 * These constants have to be maintained in parallel with those in
 * the lisp module KEYDEFS.
 */

/* Keyboard */
#define GENSYM_SPACE 32
#define GENSYM_BACKSPACE 278
#define GENSYM_TAB 279
#define GENSYM_LINEFEED 280		/* Next line in editor. */
#define GENSYM_CLEAR 396
#define GENSYM_RETURN 281		/* End editing */
#define GENSYM_PAUSE 486
#define GENSYM_ESCAPE 282
#define GENSYM_DELETE 127		/* Rubout in the editor. */

#define GENSYM_ASTERISK 42
#define GENSYM_SLASH 47
#define GENSYM_MINUS 45
#define GENSYM_PLUS 43
#define GENSYM_EQUALS 61

#define GENSYM_UP_ARROW 274		/* Arrow keys */
#define GENSYM_DOWN_ARROW 275
#define GENSYM_LEFT_ARROW 276
#define GENSYM_RIGHT_ARROW 277

#define GENSYM_HOME 484
#define GENSYM_PRIOR 387
#define GENSYM_NEXT 389
#define GENSYM_END 404
#define GENSYM_BEGIN 485
#define GENSYM_ENTER 660

#define GENSYM_SELECT 487
#define GENSYM_PRINT 488
#define GENSYM_EXECUTE 489
#define GENSYM_INSERT 480

#define GENSYM_UNDO 415
#define GENSYM_REDO 481
#define GENSYM_MENU 482
#define GENSYM_FIND 483
#define GENSYM_CANCEL 401		/* A synonym for Abort (c-a) in the editor. */
#define GENSYM_HELP 390
#define GENSYM_BREAK 385

/* The numeric keypad. */
#define GENSYM_KP_Space 453
#define GENSYM_KP_Tab 454
#define GENSYM_KP_Enter 455
#define GENSYM_KP_F1 456
#define GENSYM_KP_F2 457
#define GENSYM_KP_F3 458
#define GENSYM_KP_F4 459
#define GENSYM_KP_Multiply 461
#define GENSYM_KP_Add 462
#define GENSYM_KP_Separator 463
#define GENSYM_KP_Subtract 464
#define GENSYM_KP_Decimal 465
#define GENSYM_KP_Divide 466
#define GENSYM_KP_0 470
#define GENSYM_KP_1 471
#define GENSYM_KP_2 472
#define GENSYM_KP_3 473
#define GENSYM_KP_4 474
#define GENSYM_KP_5 475
#define GENSYM_KP_6 476
#define GENSYM_KP_7 477
#define GENSYM_KP_8 478
#define GENSYM_KP_9 479
#define GENSYM_KP_Equal 460

/* G2 only uses the first 6 function keys,
   but defines keycodes for all of them. */
#define GENSYM_F1 405
#define GENSYM_F2 406
#define GENSYM_F3 407
#define GENSYM_F4 408
#define GENSYM_F5 420
#define GENSYM_F6 421

#define GENSYM_F7 422
#define GENSYM_F8 423
#define GENSYM_F9 424
#define GENSYM_F10 425
#define GENSYM_F11 426
#define GENSYM_F12 427
#define GENSYM_F13 428
#define GENSYM_F14 429
#define GENSYM_F15 430
#define GENSYM_F16 431
#define GENSYM_F17 432
#define GENSYM_F18 433
#define GENSYM_F19 434
#define GENSYM_F20 435
#define GENSYM_F21 436
#define GENSYM_F22 437
#define GENSYM_F23 438
#define GENSYM_F24 439
#define GENSYM_F25 440
#define GENSYM_F26 441
#define GENSYM_F27 442
#define GENSYM_F28 443
#define GENSYM_F29 444
#define GENSYM_F30 445
#define GENSYM_F31 446
#define GENSYM_F32 447
#define GENSYM_F33 448
#define GENSYM_F34 449
#define GENSYM_F35 450


/* Mouse buttons, both up and down. */
#define GENSYM_MOUSE_MOTION      771
#define GENSYM_MOUSE_HOVER       782
#define GENSYM_MOUSE_LEFT_DOWN   772
#define GENSYM_MOUSE_LEFT_UP     773
#define GENSYM_MOUSE_MIDDLE_DOWN 774
#define GENSYM_MOUSE_MIDDLE_UP   775
#define GENSYM_MOUSE_RIGHT_DOWN  776
#define GENSYM_MOUSE_RIGHT_UP    777

/* Forward is defined to be rolling away from the user. */
#define GENSYM_MOUSE_WHEEL_FORWARD 780
#define GENSYM_MOUSE_WHEEL_BACKWARD 781

/* Special keycodes indicating messages from Win32 controls
 * Keep in sync with keydefs.lisp. */

#define GENSYM_WINDOW_REFRESH 784    /* New for native image planes */
#define GENSYM_WINDOW_ACTIVATED 788
#define GENSYM_WINDOW_CLOSED 789
#define GENSYM_WINDOW_MOVED 792
#define GENSYM_WINDOW_SIZED 793
#define GENSYM_WINDOW_SCROLLED 794

#define GENSYM_MENU_CHOICE 804	/* Choice from native menu (popup or menubar) */
#define GENSYM_HSCROLL 810	/* Event from a horizontal scroll bar */
#define GENSYM_VSCROLL 811	/* Event from a vertical scroll bar */
#define GENSYM_MENUBAR 818	/* Click on menubar -- request for updates. */
#define GENSYM_STATUSBAR 820	/* Click on statusbar */
#define GENSYM_PRINTWINDOW 822	/* Request to print window locally */
#define GENSYM_ABOUTBOX 823
#define GENSYM_MENU_POSTED 825	/* Native menu posted. */
#define GENSYM_BASIC_DIALOG 826
#define GENSYM_NMS_CONTROL 827
#define GENSYM_DIALOG_UPDATE 828
#define GENSYM_DIALOG_DISMISSED 829
#define GENSYM_LIST_DIRECTORY 830     /* Request directory listing from G2 */
#define GENSYM_DIALOG_MISCELLANY 831
#define GENSYM_MENU_ITEM_SELECTED 832 /* Native menu selection callbacks */
#define GENSYM_TREE_VIEW 833	      /* Tree view notification */
#define GENSYM_HTML_VIEW 834
#define GENSYM_DEBUGGER_DIALOG 835
#define GENSYM_EDITOR 836	      /* Native editor notification */
#define GENSYM_MENU_UNPOSTED 837      /* Native menu unposted. */
#define GENSYM_SHORTCUT_BAR 838
#define GENSYM_CHART 839	      /* Charting control notification */
#define GENSYM_USER_GESTURE 843
#define GENSYM_GRID_VIEW 844	      /* Grid view, in a dialog or standalone */

/*
 * Gensym X Windows Event Codes
 * These constants have to be maintained in parallel with those in
 * the module PLATFORMS.
 */
#define X11_NUMBER_OF_BITS_IN_EVENT_CODES	4
#define X11_NO_MORE_EVENTS	-1		/* ... made up ... */
#define X11_NULLEVENT		0		/* ... made up ... */
#define X11_KEYPRESS		1		/* KeyPress */
#define X11_BUTTON_PRESS	2		/* ButtonPress */
#define X11_BUTTON_RELEASE	3		/* ButtonRelease */
#define X11_POINTER_MOTION	4		/* MotionNotity */
#define X11_EXPOSURE		5		/* Expose */
#define X11_RESHAPE		6		/* ConfiqureNotify */
#define X11_ENTER		7		/* EnterNotify */
#define X11_LEAVE		8		/* LeaveNotify */
#define X11_FOCUS_IN		9		/* FocusIn */
#define X11_FOCUS_OUT	       10		/* FocusOut (unused) */
#define X11_CONTROL	       11		/* Message from some native control */


/*
 * Constants for graphics, including
 * colormaps, displays, screens, GIFs, XImage, etc.
 */
/* GC = Graphics Context */
#define MAXIMUM_NUMBER_OF_GCFUNCTIONS	6
/* Max colors for an eight bit display: 2^8 = 256 colors */
#define MAX_COLORS 256
/* For screen depth, (= bits per pixel) */
#define DEPTH_EIGHT 8
/* Scanline of a GIF file */
#define LISP_SCANLINE 8
/* Quantum of a XImage scan line (see XCreateImage) */
#define LISP_BITMAP_PAD 8
#define EIGHT_BIT_FORMAT 8
/* Number of bits in a byte */
#define NBITS_IN_BYTE 8


/* stipple opcodes */
#define no_stipple_stipple 0
#define stipple_25_percent_gray_stipple 1
#define stipple_50_percent_gray_stipple 2
#define stipple_75_percent_gray_stipple 3

/* 5.5%-GRAY */
#define stipple_5_5_percent_gray_height 18
#define stipple_5_5_percent_gray_width 288

/* 6%-GRAY */
#define stipple_6_percent_gray_height 8
#define stipple_6_percent_gray_width 32

/* 7%-GRAY */
#define stipple_7_percent_gray_height 7
#define stipple_7_percent_gray_width 224

/* 8%-GRAY */
#define stipple_8_percent_gray_height 3
#define stipple_8_percent_gray_width 96

/* 9%-GRAY */
#define stipple_9_percent_gray_height 11
#define stipple_9_percent_gray_width 352

/* 10%-GRAY */
#define stipple_10_percent_gray_height 10
#define stipple_10_percent_gray_width 160

/* 12%-GRAY */
#define stipple_12_percent_gray_height 8
#define stipple_12_percent_gray_width 32

/* 25%-GRAY */
#define stipple_25_percent_gray_height 32
#define stipple_25_percent_gray_width 32

/* 33%-GRAY */
#define stipple_33_percent_gray_height 3
#define stipple_33_percent_gray_width 96

/* 50%-GRAY */
#define stipple_50_percent_gray_height 2
#define stipple_50_percent_gray_width 32

/* 75%-GRAY */
#define stipple_75_percent_gray_height 4
#define stipple_75_percent_gray_width 32


/* Some handy macros */

#define MakeInstance(type) ((type *)calloc(1,sizeof(type)))

#if !defined(WIN32)

typedef unsigned long XColor_pixel;

#define COLOR_FREE 0
#define COLOR_ALLOCATED 1
#define COLOR_EXTENDED 2

struct GensymXWindowStruct
{
  Display       *display_ptr;
  Screen        *screen_ptr;
  Window        xwindow;
  Colormap      colormap;
  unsigned char color_flags[MAX_COLORS]; /* COLOR_FREE, COLOR_ALLOCATED, COLOR_EXTENDED */

  int           offscreen;	/* Boolean: offscreen drawing enabled. */
  Pixmap        xpixmap;	/* Off-screen pixmap, compatable with xwindow. */

  long		last_mouse_x;
  long		last_mouse_y;
  Time		last_event_time; /* From the X server. In ms. */
  long		last_event_bits; /* Modifier bits */

  long		last_window_x;
  long		last_window_y;
  long		last_window_width;
  long		last_window_height;

  long		last_expose_x;
  long		last_expose_y;
  long		last_expose_width;
  long		last_expose_height;
  Atom            cut_and_paste;
  GC		the_tiling_gc;

  GC		global_gctable[MAXIMUM_NUMBER_OF_GCFUNCTIONS];
  GC		scrolling_gc;	/* graphics_exposures is true for both these. */
  GC            images_gc;	/* GC used to bitblt background images. */

  GC            stippled_gc;	/* GC used bitblt bitmap to window with transparency. */
  XColor_pixel  stippled_gc_foreground_color; /* kept in synch/paired with above GC */
  int           stippled_gc_clip_p; /* if TRUE, use clip rectangles in the GC; otherwise,
				       use no clipping (saves on protocol calls); set
				       once at initialization only, then never changes
				       */

  Pixmap stipple_light;  /* 25, 50, and 75 percent gray patterns, initially NULL */
  Pixmap stipple_medium;
  Pixmap stipple_dark;

  XColor_pixel	global_gctable_foreground_color[MAXIMUM_NUMBER_OF_GCFUNCTIONS];
  XColor_pixel	global_gctable_background_color[MAXIMUM_NUMBER_OF_GCFUNCTIONS];

  /* Time of last button event, for each of the possible X buttons, in milliseconds. */
  Time            last_button_press_time[10];
  Time            last_button_release_time[10];
  long            last_button_press_time_valid_p;   /* Bit set if last_time's are valid. */
  long            last_button_release_time_valid_p;

  long            network_interface_handle;
  int is_connected;     /* initially false, set true by g2ext_x11_set_window_is_connected */
  int tracking_mouse;		/* True if G2 wants in mouse motion events */

  int hover_timer_active_p;	/* Mouse-hover implementation for X11 */
  int hover_x;
  int hover_y;
  int hover_event;
};

typedef struct GensymXWindowStruct GensymXWindow;


/*
 * The struct `PixmapStruct' ...
 */
struct aPixmapStruct
  {
   GensymXWindow	*gensym_x_window_ptr;
   Display		*display_ptr;
   			/* cache; also available in gensym_x_window */
   Pixmap		pixmap;
   GC			gc;
   int			width;
   int			height;
   int			depth;
   XColor_pixel 	xcolor;
  } ;

typedef struct aPixmapStruct PixmapStruct;

#endif /* Not Windows or NT. X-specific defines */


/*
 * G2 Event Constants
 * This section defines the special G2 keycodes, ie, those
 * which differ from plain ASCII, as well as some masks
 * and modifier bits.
 */
/* Event times are 28 bits of non-negative milliseconds */
#define EVENT_TIME_MASK 0xFFFFFFF


/* Keep in sync with maximum-connection-dash-count in grammar6a.lisp */
#define MAX_DASH_COUNT 256	/* Maximum number of elements in dashes[] */
#define MAX_VERTICES_WIN9X 1000 /* Maximum number of vertices in a polyline
				 * MSDN says "approximately" 1360 */


#ifndef WIN32

/* Line styles, matching the Win32 values. */
#define PS_SOLID         0x0000
#define PS_DASH          0x0001
#define PS_DOT           0x0002
#define PS_DASHDOT       0x0003
#define PS_DASHDOTDOT    0x0004
#define PS_USERSTYLE     0x0007
#define PS_STYLE_MASK    0x000F

#define PS_ENDCAP_ROUND  0x0000
#define PS_ENDCAP_SQUARE 0x0100
#define PS_ENDCAP_FLAT   0x0200
#define PS_ENDCAP_MASK   0x0F00

#define PS_JOIN_ROUND    0x0000
#define PS_JOIN_BEVEL    0x1000
#define PS_JOIN_MITER    0x2000
#define PS_JOIN_MASK     0xF000
#endif

/*
 * Native Menu System
 */

#define MF_DYNAMIC      0x10000	/* Keep in sync with lisp mf-dynamic, etc. */
#define MF_MENUSELECT   0x40000
#define MF_UNPOST       0x80000

/* 
 * Native Image Planes
 */

#define NIP_WINTYPE_CLASSIC  0	/* Window types for g2ext_x11_create_window */
#define NIP_WINTYPE_MDICHILD 1	/* Keep in sync with nip-wintype-xxx in WINDOWS4 */
#define NIP_WINTYPE_EMBEDDED 2
#define NIP_WINTYPE_TOPLEVEL 3
#define NIP_WINTYPE_EXTERNAL 4	/* A window owned by another process. */

#define NIP_SHOW_WINDOW 1	/* Opcodes for g2ext_x11_manage_window */
#define NIP_MOVE_WINDOW 2
#define NIP_RESHAPE_WINDOW 3
#define NIP_RAISE_WINDOW 4
#define NIP_LOWER_WINDOW 5
#define NIP_DESTROY_WINDOW 6
#define NIP_CAPTION_WINDOW 7
#define NIP_INFLATE_WINDOW 8
#define NIP_SCROLL_WINDOW 9
#define NIP_CERASE_WINDOW 10
#define NIP_SET_MAX_SIZE 11
#define NIP_RESTYLE_WINDOW 12
#define NIP_ZORDER_WINDOW 13
#define NIP_SET_ICON 14
#define NIP_SET_CLOSEABLE 15
#define NIP_RESCALE_WINDOW 16
#define NIP_SET_BACKGROUND_COLOR 17
#define NIP_SIZE_WINDOW 18
/*
 * UI Properties
 */

#define UIPROP_MOUSE_CURSOR 0		/* Keep in sync with LISP ui-property-id */
#define UIPROP_THEME 1
#define UIPROP_ENABLED 2
#define UIPROP_NO_RAISE 3	       /* No raise on right click.  */

extern int g2pvt_set_mouse_cursor(int window_index, int cursorID);
extern long g2ext_nms_set_theme(long theme);

/* 
 * Yet Another Tracing Facility, now actually defined in trace.c
 */

#ifdef __cplusplus
extern "C" {
#endif
extern void g2pvt_notify_user(const char *fmt, ...);
extern void g2pvt_trace(const char *fmt, ...);
extern void g2pvt_printf(const char *fmt, ...);
extern void g2pvt_puts(const char *str);
#ifdef __cplusplus
}
#endif

#define G2TRACE_ON g2pvt_trace
#define G2TRACE_OFF 1 ? (void)0 : g2pvt_trace

/* Unconditional print */
#define PRINTF G2TRACE_ON

/* Define EXTDEBUG and recompile to enable tracing */
/* TODO: trace categories and levels. */

#ifdef EXTDEBUG
#define G2TRACE G2TRACE_ON
#else
#define G2TRACE G2TRACE_OFF
#endif

#endif /* _GRAPHICS_H */
