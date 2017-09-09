/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      graphics.c
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
 +              ??/??/?? - 07/01/93   Richard Haggard, Kamal Bijlani
 +              07-08-93 - 08/30/96   mpc
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
 +   Section:      FUNCTION GROUP - Pixmap Graphics Functions
 +      g2pvt_get_pix_gc                       1111111 Conditionally Defined
 +      get_gc                           1111111 Conditionally Defined
 +      x11_handle_create_pixmap_error   1111111 Conditionally Defined
 +      g2ext_create_pixmap                    0000000 Multiply Defined
 +      g2ext_reclaim_pixmap                   0000000 Mixed ifdefs
 +      g2ext_get_pixel                        0000000 Multiply Defined
 +      g2ext_copy_bitmap_to_bitmap            0000000 Multiply Defined
 +      g2ext_x11_draw_pixmap                  0000000 Multiply Defined
 +      x11_ensure_pixmap_color          1111111 Conditionally Defined
 +      g2ext_p_draw_point                     0000000 Multiply Defined
 +      g2ext_p_draw_line                      0000000 Multiply Defined
 +      g2ext_p_draw_wide_line                 0000000 Multiply Defined
 +      g2ext_p_fill_rect                      0000000 Multiply Defined
 +      g2ext_p_draw_arc                       0000000 Multiply Defined
 +      g2ext_p_fill_arc                       0000000 Multiply Defined
 +      g2ext_p_fill_triangle                  0000000 Multiply Defined
 +      g2ext_copy_pixmap_to_window            0000000 Multiply Defined
 +      g2ext_copy_polychrome_pixmap_to_window 0000000 Mixed ifdefs
 +   Section:      FUNCTION GROUP - Window Graphics Functions
 +      g2ext_w_draw_line_with_clipping        0000000 Multiply Defined
 +      g2ext_w_fill_rect                      0000000 Multiply Defined
 +      g2ext_w_draw_tiles                     0000000 Multiply Defined
 +      g2ext_w_draw_wide_polyline             0000000 Multiply Defined
 +      g2ext_w_draw_wide_string               0000000 Multiply Defined (stubbed for X11)
 +      g2ext_w_draw_string_with_clipping      1111111 Mixed ifdefs
 +      g2ext_copy_pixmap_to_window            0000000 Multiply Defined
 +   Section:      FUNCTION GROUP - Image Functions
 +      g2ext_free_extended_colors             0000000 Multiply Defined
 +      g2ext_x11_put_image                    0000000 Multiply Defined
 +   Section:      FUNCTION GROUP - Text Functions
 +      g2ext_w_draw_string_with_clipping      1111111 Mixed ifdefs
 +      g2ext_draw_string_in_font_with_clipping 1111111 Mixed ifdefs
 +      g2ext_draw_string_in_font              1111111 Mixed ifdefs
 +      g2ext_allocate_x_font                  1111111 Mixed ifdefs
 +      g2ext_get_character_set_width          1111111 Mixed ifdefs
 +   Section:      FUNCTION GROUP - Miscellaneous Functions
 +      g2ext_scroll_rectangle                 0000000 Multiply Defined
 +      g2ext_x11_get_mouse_x_position         0000000 Multiply Defined
 +      g2ext_x11_move_pointer                 0000000 Multiply Defined
 +      g2ext_x11_preinitialize                0000000
 +      g2ext_x11_parse_geometry               0000000 Mixed ifdefs
 +      g2ext_x11_parse_geometry_x             0000000
 +      g2ext_x11_parse_geometry_y             0000000
 +      g2ext_x11_parse_geometry_width         0000000
 +      g2ext_x11_parse_geometry_height        0000000
 +      g2ext_x11_bell                         0000000 Multiply Defined
 +      x11_compute_tiling_gc            1111111 Conditionally Defined
 +      g2ext_x11_initialize_tile              0000000 Multiply Defined
 +      g2ext_x11_tile                         0000000 Multiply Defined
 +      g2ext_x11_read_cut_buffer              0000000 Mixed ifdefs
 +      g2ext_x11_write_cut_buffer             0000000 Mixed ifdefs
 +      AngleTo4096RadiusXYCoords        2222222 Conditionally Defined
 +      XlatArcCoords                    1111111 Conditionally Defined
 +   Section:      FUNCTION GROUP - Debugging Functions
 +      x11_handle_error_as_signal       1111111 Conditionally Defined
 +      g2ext_x11_set_debug_mode               0000000 Mixed ifdefs
 +      x11_debug_mode                   ??????? Conditionally Defined
 +      g2ext_x11_clear_debug_mode             0000000 Mixed ifdefs
 +      
 +      
 + External Interface:
 +      int      g2ext_create_pixmap(window_index, width, height, depth)
 +                 Create a bitmap using the specified width and height
 +                 Return: Pixmap ID on success, -1 on failure
 +
 +      void     g2ext_reclaim_pixmap( pixmap_index )
 +                 Reclaim a bitmap
 +                 Return: None
 +
 +      long     g2ext_get_pixel(window_index, color_name, extended_color_p)
 +                 Returns a pixel value corresponding to the color 
 +                 Return:-1 on error or color value
 +
 +      void     g2ext_copy_bitmap_to_bitmap(pixmap_struct1_index, 
 +                                     pixmap_struct2_index, x_offset,
 +                                     y_offset, x, y, width, height,
 +                                     foreground_color)
 +                 Stamp a bitmap into another bitmap
 +                 Returns: None
 +
 +      void     g2ext_x11_draw_pixmap (pixmap_index, window_index, mask_pixmap_index, src_x, src_y, width, height,
 +                                dst_x, dst_y, foreground, background)
 +                 Bitblt workspace background images onto the G2 window
 +                 Returns: None
 +
 +      void     g2ext_p_draw_point(pixmap_index, x, y, xcolor)
 +                 Draws a single pixel at x,y coordinates of given pixmap
 +                 Returns: None
 +
 +      void     g2ext_p_draw_line(pixmap_index, x1, y1, x2, y2, xcolor)
 +                 Draws a line on given pixmap
 +                 Returns: None
 +
 +      void     g2ext_p_draw_line(pixmap_index, x1, y1, x2, y2, xcolor, line_width)
 +                 Draws a wide line on given pixmap
 +                 Returns: None
 +
 +      void     g2ext_p_fill_rect(pixmap_index, x, y, width, height, xcolor)
 +                 Draws a filled rectangle on given pixmap
 +                 Returns: None
 +
 +      void     g2ext_p_draw_arc(pixmap_index, x, y, width, height, start_angle,
 +                          displacement_angle, xcolor)
 +                 Draws an arc on given pixmap
 +                 Returns: None
 +
 +      void     g2ext_p_fill_arc(pixmap_index, x, y, width, height, start_angle,
 +                          displacement_angle, xcolor)
 +                 Draws a filled arc on given pixmap
 +                 Returns: None
 +
 +      void     g2ext_p_fill_triangle(pixmap_index, x1, y1, x2, y2, x3, y3, xcolor)
 +                 Draws a filled triangle on given pixmap
 +                 Returns: None
 +
 +      void     g2ext_copy_pixmap_to_window(pixmap_index, window_index, x_offset, y_offset, x, y,
 +                                     width, height, foreground_xcolor,
 +                                     background_xcolor, function_index)
 +                 Copy an existing bitmap to the screen using specified colors.
 +                 Returns: None
 +
 +      void     g2ext_copy_polychrome_pixmap_to_window(pixmap_index, x_offset, y_offset,
 +                                     x, y, width, height, function_index)
 +                 Copy a bitmap to the screen.
 +                 Returns: None
 +
 +      void     g2ext_w_draw_line_with_clipping(window_index, x1, y1, x2, y2,
 +                                   left_edge, top_edge, right_edge,
 +                                   bottom_edge, xcolor, function_index)
 +                 Draws a line on a window
 +                 Returns: None
 +
 +      void     g2ext_w_fill_rect(window_index, x, y, width, height,
 +                           xcolor,function_index)
 +                 Draws a filled rectangle on the window
 +                 Returns: None
 +
 +      int      g2ext_free_extended_colors (window_index)
 +                 Free all of the pixels allocated for extended colors
 +                 Returns: 1 if G2 is running without a local window, 0 otherwise
 +
 +      void     g2ext_x11_put_image (pixmap_index, dest_x, dest_y, width, height,
 +                     depth, gc_function, bytes_per_scan_line, data)
 +                 Paint image data onto an X pixmap
 +                 Returns: None
 +
 +      void     g2ext_scroll_rectangle(window_index, source_left, source_top, width,
 +                                height, destination_left, destination_top)
 +                 Moves one portion of the x window to another
 +                 Returns: None
 +
 +      long     g2ext_x11_get_mouse_x_position (window_index)
 +                 Get the X position of the mouse when in the app window.
 +                 Returns: mouse X position
 +
 +      void     g2ext_x11_move_pointer(window_index, dest_x, dest_y)
 +                 Moves the pointer to the specified destination.
 +                 Returns: None
 +
 +      void     g2ext_x11_preinitialize(run_without_local_window, windowhandle)
 +                 Perform preinitialization action
 +                 Returns: None
 +
 +      void     g2ext_x11_parse_geometry (char *parsestring)
 +                 Parses the -geometry command line argument
 +                 Returns: None
 +
 +      int      g2ext_x11_parse_geometry_x()
 +                 Return x component of the parsed -geometry cmdline arg
 +                 Returns: x geometry component
 +
 +      int      g2ext_x11_parse_geometry_y()
 +                 Return y component of the parsed -geometry cmdline arg
 +                 Returns: y geometry component
 +
 +      int      g2ext_x11_parse_geometry_width()
 +                 Return width component of the parsed -geometry cmdline arg
 +                 Returns: width geometry component
 +
 +      int      g2ext_x11_parse_geometry_height()
 +                 Return height component of the parsed -geometry cmdline arg
 +                 Returns: height geometry component
 +
 +      long     g2ext_x11_bell(window_index, percent)
 +                 Ring the bell
 +                 Returns: -1 on error, 0 otherwise
 +
 +      void     g2ext_x11_initialize_tile(window_index, pixmap_index,
 +                                   foreground_xcolor, background_xcolor)
 +                 Initialize window background tile pattern
 +                 Returns: None
 +
 +      void     g2ext_x11_tile(window_index, left, top, width, height)
 +                 Fills a portion of the window with its tiling pattern
 +                 Returns: None
 +
 +      long     g2ext_x11_read_cut_buffer(window_index, buffer, size)
 +                 Copy the current contents of the cut buffer into the buffer
 +                 Returns: number of characters copied
 +
 +      long     g2ext_x11_write_cut_buffer(window_index, string)
 +                 Copy the given string into the cut buffer for the display
 +                 Returns: number of characters copied
 +
 +      void     g2ext_x11_set_debug_mode(window_index)
 +                 Sets debugging mode
 +                 Returns: None
 +
 +      void     g2ext_x11_clear_debug_mode(window_index)
 +                 Clears debugging mode
 +                 Returns: None
 +
 + Dependencies:
 +      This file has no external dependencies.
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
 +   04/07/97, lgibson: Added ability to read/write MS windows clipboard 
 +		  (in the now misnamed "g2ext_x11_read_cut_buffer" and 
 +		  "g2ext_x11_write_cut_buffer"). 
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
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#if defined(WIN32)
#    include <string.h>
#    include <math.h>
#    include <windows.h>
#    include "msincls.h"
#else
#    include <signal.h>
#    include <stdarg.h>
#    include <stdlib.h>
#endif

#include "cprim.h"
#include "graphics.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section. 
 %
 % Notes:
 %   CLIP_FOR_DRAWING was used to work around a bug in Ultrix.  The conditional
 %   CLIP_FOR_DRAWING code should probably be removed.  -jv, 5/19/05
 %     Things known:
 %       When enabled, this slows the IBM RS6000 with Graphics Accelerator board
 %       down by about 250%, at least.
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#if defined(MSWINDOWS)
#    define TWO_PI (2*3.141592)
#else
#    define Illegal -1
#endif

#define GTRACE G2TRACE


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

/* Private_colormap_p enables the allocation of a private color map. */
int Private_colormap_p = 0;

int draw_to_printer = 0;	/* If TRUE, graphics go to printer instead of screen. */

extern int No_window;		/* defined in networks.c */
extern long g2pvt_modifier_bits ();

/* Keep in sync with LISP transparent-color-value */
#define TRANSPARENT_COLOR_VALUE (1<<24)

#if defined(MSWINDOWS) 
    extern LPG2INFO GetlpG2Info(HWND);

    extern long g2ext_x11_screen_depth(long);
    extern long g2ext_reverse_bits_in_byte(long);
    extern void error_info(char *format, ...); /* Prints windows error code. */

    /* These are standard Brushes/Pens that are used consistently
     * enough to justify hanging on to them. 
     */
    extern HBRUSH   GhbrWhite;       /* the global white brush */
    extern HBRUSH   GhbrBlack;       /* the global black brush */
    extern HPEN	 GhpenWhite;	    /* the global white pen */
    extern HPEN	 GhpenBlack;	    /* the global black pen */

    extern HBRUSH stipple_light;     /* Brushes for stipple patterns used to */
    extern HBRUSH stipple_medium;    /* implement icon stipple feature.      */
    extern HBRUSH stipple_dark;

    extern HBITMAP GhbmDummy;
    extern HDC printer_dc;

#   define COLORVAL(nColor) (nColor)

#else /* not MSWindows, must be XWindows */
    extern int g2int_x_error();		/* Lives in lisp */
    extern long g2_modifier_bits();
    extern long g2ext_sys_sleep();
    static GC get_gc();		/* Fwd ref */

    extern long parent_XWindow_address;

    static XErrorHandler last_x11_error_handler = NULL;
    static int last_x11_error_code = 0;

    static XErrorHandler last_non_debug_error_handler = NULL;
#endif /* MSWindows or XWindows */

/* No_drawing is a variable unrelated to No_window which only turns off drawing
 * to the screen (as opposed to pixmaps) by routines in this file. It is set
 * when G2 attempts to redirect drawing to a window which has already been
 * deleted, but due to queueing and network delays G2 doesn't know that yet. */
static int No_drawing = 0;

extern int screen_depth_global;

static int parse_geometry_result[4];

extern long g2ext_write_string_to_console(char * string);




/*
 * Win32 Bitmap Utilities
 */

#ifdef WIN32

static void bitmap_clear(HBITMAP hbm, int width, int height)
{
  HBITMAP hOldBitmap = SelectObject(GhdcMem, hbm);
  PatBlt(GhdcMem, 0, 0, width, height, BLACKNESS);
  SelectObject(GhdcMem, hOldBitmap);
  /* or just call:
     bitmap_clear_ex(hbm, 0, 0, width, height); */
}

/* extended version of bitmap_clear() with offset supports */
static void bitmap_clear_ex(HBITMAP hbm, int x_offset, int y_offset, int width, int height)
{
    HBITMAP hOldBitmap = SelectObject(GhdcMem, hbm);
    PatBlt(GhdcMem, x_offset, y_offset, width, height, BLACKNESS);
    SelectObject(GhdcMem, hOldBitmap);
}

static void bitmap_copy(HBITMAP hbmSrc, HBITMAP hbmDst, int srcX, int srcY, int width, int height)
{
  HDC hdcSrc = CreateCompatibleDC(Ghdc);
  HDC hdcDst = CreateCompatibleDC(Ghdc);
  HBITMAP oldSrc = SelectObject(hdcSrc, hbmSrc);
  HBITMAP oldDst = SelectObject(hdcDst, hbmDst);

  BitBlt(hdcDst, 0, 0, width, height, hdcSrc, srcX, srcY, SRCCOPY);

  SelectObject(hdcDst, oldDst);
  SelectObject(hdcSrc, oldSrc);
  DeleteDC(hdcDst);
  DeleteDC(hdcSrc);
}

#endif




/*
 * ImageCluster Facility (Win32 Only)
 */

#ifdef WIN32

/* GENSYMCID-1193: TWNG Icon Problems
   We try to increase (4x) the hard limit of image clusters, from 256 to 1024.
   Also see NOTES for macro ImageCluster_PackHandle below.

   -- Chun Tian (binghe), June 19, 2014. */
#define ImageCluster_Hash(w,h) ((((w)<<4) + ((h)>>2)) & 0x3FF)  /* old: 0xFF */
#define MAX_IMAGECLUSTERS 1024                                  /* old: 256  */

typedef struct _FreeCell {
  struct _FreeCell *next;
  int cell;
} FreeCell;

typedef struct {
  int cluster;			/* Index in array */
  int cellWidth, cellHeight;
  int nextFreeCell;
  FreeCell *freeCells;		/* List of free cells */
  int ncells;			/* Total number in current bitmap */
  int grow;			/* Number of cells to add at once (increases to span) */
  int span;			/* Number of cells per row (a power of 2) */
  int spanBits;			/* log2(span) */
  HBITMAP hbm;
  int width, height;		/* Total size of hbm */
} ImageCluster;

static ImageCluster *g_imageClusters[MAX_IMAGECLUSTERS];

static int ImageCluster_FindEmptySlot(int cellWidth, int cellHeight)
{
  int i, hash = ImageCluster_Hash(cellWidth,cellHeight);

  for(i=hash; i<MAX_IMAGECLUSTERS; i++)
    if(!g_imageClusters[i])
      return i;

  for(i=0; i<hash; i++)
    if(!g_imageClusters[i])
      return i;
  return -1;
}

static ImageCluster *ImageCluster_Create(int cellWidth, int cellHeight)
{
  int ncells = 0;		 /* Initial allocation */
  int width = cellWidth * ncells;
  int height = cellHeight;
  ImageCluster *pic;
  int index = ImageCluster_FindEmptySlot(cellWidth, cellHeight);

  if(index<0)
    return NULL;

  pic = calloc(1, sizeof(ImageCluster));
  pic->cluster = index;
  pic->hbm = NULL;
  pic->cellWidth = cellWidth;
  pic->cellHeight = cellHeight;
  pic->ncells = ncells;
  if(cellWidth >= 256) {	/* Guess reasonable span/grow sizes */
    pic->span = 32;
    pic->spanBits = 5;
  } else {
    pic->span = 128;
    pic->spanBits = 7;
  }
  pic->grow = pic->span / 2;
  pic->width = width;
  pic->height = height;

  g_imageClusters[index] = pic;

  return pic;
}

static ImageCluster *ImageCluster_Find(int cellWidth, int cellHeight)
{
  int i, hash = ImageCluster_Hash(cellWidth,cellHeight);
  ImageCluster *pic;

  for(i=hash; i<MAX_IMAGECLUSTERS; i++) {
    pic = g_imageClusters[i];
    if(!pic)
      return NULL;
    else if(pic->cellWidth == cellWidth && pic->cellHeight == cellHeight)
      return pic;
  }

  for(i=0; i<hash; i++) {
    pic = g_imageClusters[i];
    if(!pic)
      return NULL;
    else if(pic && pic->cellWidth == cellWidth && pic->cellHeight == cellHeight)
      return pic;
  }
  return NULL;
}

static BOOL ImageCluster_Grow(ImageCluster *pic)
{
  int ncells, width, height;
  HBITMAP hbm;

  if(pic->ncells < pic->span) {
    ncells = pic->ncells + pic->grow;
    width = pic->cellWidth * ncells;
    height = pic->cellHeight;
  } else {
    ncells = pic->ncells + pic->span;
    width = pic->width;
    height = pic->height + pic->cellHeight;
  }

  hbm = CreateBitmap(width, height, 1, 1, NULL);

  if(hbm == NULL)
    return FALSE;

  bitmap_clear(hbm, width, height);

  if(pic->hbm) {
    bitmap_copy(pic->hbm, hbm, 0, 0, pic->width, pic->height);
    DeleteObject(pic->hbm);
  }

  pic->hbm = hbm;
  pic->width = width;
  pic->height = height;
  pic->ncells = ncells;

  return TRUE;
}

static int ImageCluster_AllocateCell(ImageCluster *pic)
{
  int freeCell = -1;
  int cell;
  int span, width, height, row, column, x_offset, y_offset;

  /* 1. Quickly use next available cells without considering available cells
     freed previously. */
  if(pic->nextFreeCell < pic->ncells) {
    /* clean the bitmap area first ! */
    freeCell = pic->nextFreeCell++;
  }
  /* 2. In case all cells were used at least once, re-use the head of
     freeCells linked-list */
  else if(pic->freeCells) {
    FreeCell *list = pic->freeCells;
    cell = list->cell;
    pic->freeCells = list->next;
    free(list);
    /* clean the bitmap area first ! */
    freeCell = cell;
  }
  /* 3. In case there's really no available cell, we have to grow the whole
     image cluster and pick the next free cell again. */
  else if(ImageCluster_Grow(pic))
    freeCell = pic->nextFreeCell++;

  /* GENSYMCID-1663: Issues with workspace printing of charts
     4. Clear the bitmap area corresponded to the freeCell, otherwise exist
     drawing in the bitmap will cause unexpected issues.
     -- Chun Tian (binghe), Mar 26, 2015. */
  if (freeCell >= 0) {
      span = pic->span;
      row = freeCell / span;
      column = freeCell % span;
      width = pic->cellWidth;
      height = pic->cellHeight;
      x_offset = column * width;
      y_offset = row * height;
      bitmap_clear_ex(pic->hbm, x_offset, y_offset, width, height);
  }

  return freeCell;
}

static ImageCluster *ImageCluster_Get(int cluster)
{
  return (0 <= cluster && cluster < MAX_IMAGECLUSTERS) ? g_imageClusters[cluster] : NULL;
}

static void ImageCluster_ReclaimCell(ImageCluster *pic, int cell)
{
  if(cell == pic->nextFreeCell - 1)
    pic->nextFreeCell--;
  else {
    FreeCell *node = (FreeCell *) malloc(sizeof(FreeCell));
    node->next = pic->freeCells;
    node->cell = cell;
    pic->freeCells = node;
  }
}

static void ImageCluster_Reclaim(ImageCluster *pic)
{
  if(pic->hbm)
    DeleteObject(pic->hbm);

  ZeroMemory(pic, sizeof(ImageCluster));
  free(pic);
}

#ifdef _DEBUG
static void ImageCluster_DescribeCell(ImageCluster *pic, int xoff, int yoff)
{
  int x, y, n;
  HDC hdc = GhdcMem;
  HBITMAP old = SelectObject(hdc, pic->hbm);
/*   g2pvt_printf("ImageCluster %dx%d\n", pic->cellWidth, pic->cellHeight); */
  for(y=yoff; y<yoff+pic->cellHeight; y++) {
    n=0;
    for(x=xoff; x<xoff+pic->cellWidth; x++)
      n += GetPixel(hdc, x, y);
    if(n>0) {
      g2pvt_printf("(%03d) ", y);
      for(x=xoff; x<xoff+pic->cellWidth; x++)
	g2pvt_printf("%s", (GetPixel(hdc, x, y) == 0) ? "-" : "*");
      g2pvt_printf("\n");
    }
  }
  SelectObject(hdc, old);
}

static void ImageCluster_DescribeAll()
{
  ImageCluster *pic;
  int i, n;

  g2pvt_printf("\nImageClusters ...\n");
  n=0;
  for(i=0; i<MAX_IMAGECLUSTERS; i++) {
    pic = g_imageClusters[i];
    if(pic) {
      g2pvt_printf(" (%03d) %dx%d cells %d/%d bitmap %dx%d\n",
		   pic->cluster, pic->cellWidth, pic->cellHeight, pic->nextFreeCell, pic->ncells,
		   pic->width, pic->height);
      n++;
    }
  }
  g2pvt_printf("Total of %d clusters\n", n);
}
#endif




/*
 * External API (really a pixmap API)
 */

/* GENSYMCID-1193: TWNG Icon Problems

   In 32-bit Chestnut, MOST-POSITIVE-FIXNUM is 536870911 (0x1FFFFFFF, 2^29-1),
   any value bigger than that will be cut off in Lisp (or generated C) code.
   A "ImageClusterHandle" is a special handle value that is designed for Lisp,
   it's always smaller than MOST-POSITIVE-FIXNUM, by logicall OR 0x10000000,
   0xFFFFF (20 bit width) and 0xFF (8 bit width). Here, the value 0xFF must be
   (MAX_IMAGECLUSTERS - 1), or (cluster) will exceed 8 bit width.

   If this image cluster is full, TWNG have to give up to use this facility and
   have to directly return raw HANDLE values to Lisp side, but if the value is
   bigger than MOST-POSITIVE-FIXNUM (after allocated too many pixmaps, maybe),
   the higher bits of the value will be cut off, the from customer's view, they
   see WRONG ICONs: a group of DIFFERENT icons now looks like the SAME.

   Long term solution is to use 64-bit build of TWNG instead. But for now, it's
   possible to extend the size of image cluster hash table size, from 256 to 4x
   (1024), and this means we need to re-part the 28 bits, instead of 20 + 8, we
   use 18 + 10 now, therefore the hex values used in ImageCluster_PackHandle is
   (0x3FFFF << 10 | 0x3FF) instead of (0xFFFFF << 8 | 0xFF), they're equal.

   -- Chun Tian (binghe), June 20, 2014. */
#define IsImageClusterHandle(handle) (((handle)&0xF0000000) == 0x10000000)
#define ImageCluster_PackHandle(cluster, cell) (0x10000000 | (((cell)&0x3FFFF)<<10) | ((cluster)&0x3FF))
#define ImageClusterHandle_Cluster(handle) ((handle) & 0x3FF)
#define ImageClusterHandle_Cell(handle) (((handle)>>10) & 0x3FFFF)

int ImageCluster_CreatePixmap(int width, int height, int depth, BOOL irregular)
{
  HBITMAP hbm;

  if(depth == 1 && !irregular) {
    ImageCluster *pic = ImageCluster_Find(width, height);
    int cell;

    if(!pic)
      pic = ImageCluster_Create(width, height);

    if(!pic)
      goto L;

    cell = ImageCluster_AllocateCell(pic);
    if(cell < 0)
      return -1;
    return ImageCluster_PackHandle(pic->cluster, cell);
  }

L:
  if(depth == 1)
    hbm = CreateBitmap(width, height, 1, 1, NULL);
  else
    hbm = CreateCompatibleBitmap(Ghdc, width, height);
  if(!hbm)
    return -1;
  bitmap_clear(hbm, width, height);
  return g2ext_cache_cpointer((long)hbm);
}

HBITMAP ImageCluster_GetBitmap(int handle, int *pX, int *pY, int *pWidth, int *pHeight)
{
  if(IsImageClusterHandle(handle)) {
    int cluster = ImageClusterHandle_Cluster(handle);
    int cell = ImageClusterHandle_Cell(handle);
    ImageCluster *pic = ImageCluster_Get(cluster);

    if(!pic)
      return NULL;

    if(cell > pic->ncells)
      return NULL;

    if(pX) *pX = (cell & (pic->span-1)) * pic->cellWidth;
    if(pY) *pY = (cell >> pic->spanBits) * pic->cellHeight;
    if(pWidth) *pWidth = pic->cellWidth;
    if(pHeight) *pHeight = pic->cellHeight;

    return pic->hbm;

  } else {
    if(pX) *pX = 0;
    if(pY) *pY = 0;
    if(pWidth) *pWidth = 0;
    if(pHeight) *pHeight = 0;
    return (HBITMAP) g2ext_map_g2pointer_to_cpointer(handle);
  }
}

HBITMAP ImageCluster_ExtractBitmap(int handle)
{
  if(IsImageClusterHandle(handle)) {
    HBITMAP hbmSrc, hbm;
    int xoff, yoff, width, height;

    hbmSrc = ImageCluster_GetBitmap(handle, &xoff, &yoff, &width, &height);
    if(hbmSrc == NULL)
      return NULL;

    hbm = CreateBitmap(width, height, 1, 1, NULL);
    if(hbm == NULL)
      return NULL;

    bitmap_copy(hbmSrc, hbm, xoff, yoff, width, height);
    return hbm;

  } else {
    return (HBITMAP) g2ext_map_g2pointer_to_cpointer(handle);
  }
}

void ImageCluster_ReclaimExtractedBitmap(int handle, HBITMAP hbm)
{
  if(IsImageClusterHandle(handle))
    if(hbm)
      DeleteObject(hbm);
}

void ImageCluster_ReclaimBitmap(int handle)
{
  if(IsImageClusterHandle(handle)) {
    int cluster = ImageClusterHandle_Cluster(handle);
    int cell = ImageClusterHandle_Cell(handle);
    ImageCluster *pic = ImageCluster_Get(cluster);
    ImageCluster_ReclaimCell(pic, cell);
  } else {
    HBITMAP hbm = (HBITMAP) g2ext_map_g2pointer_to_cpointer(handle);
    if(hbm != NULL)
      DeleteObject(hbm);
    g2ext_decache_g2pointer(handle);
  }
}

HBRUSH ImageCluster_CreatePatternBrush(int handle)
{
  HBITMAP hbm = ImageCluster_ExtractBitmap(handle);
  HBRUSH hbr = CreatePatternBrush(hbm);
  ImageCluster_ReclaimExtractedBitmap(handle, hbm);
  return hbr;
}

#ifdef _DEBUG
void ImageCluster_DescribeHandle(int handle)
{
  if(IsImageClusterHandle(handle)) {
    int cluster = ImageClusterHandle_Cluster(handle);
    int cell = ImageClusterHandle_Cell(handle);
    ImageCluster *pic = ImageCluster_Get(cluster);
    int x, y, w, h;

    ImageCluster_GetBitmap(handle, &x, &y, &w, &h);
    g2pvt_printf("ImageCluster %08x %dx%d cell %d\n", handle, w, h, cell);
    ImageCluster_DescribeCell(pic, x, y);
  } else {
    g2pvt_printf("Handle %08x is a g2pointer\n", handle);
  }
}
#endif

#endif




/*****************************************************************************
 * int g2ext_offscreen(int window_index, int pixmap_index, int enable)
 *
 *   Description: 
 *     Begins or ends offscreen drawing to given pixmap.
 *****************************************************************************/
#if defined(XWINDOWS)

long g2ext_offscreen(long window_index, long pixmap_index, long enable)
{
  GensymXWindow *gwindow;
  PixmapStruct *gpixmap;

  if (No_window) return 0;

  gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

  if(enable) {
    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
    if(gpixmap != NULL) {	/* Should never happen. */
      gwindow->offscreen = 1;
      gwindow->xpixmap = gpixmap->pixmap;
    }
  } else {
    gwindow->offscreen = 0;
  }

  return 1;
}

#else

/* Win32 version. */
long g2ext_offscreen(long window_index, long pixmap_index, long enable)
{
  HWND hwnd;
  LPG2INFO winfo;
  HBITMAP   hbm;

  GTRACE("g2ext_offscreen(%d, %d, %d)\n",  window_index,  pixmap_index,  enable);

  hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  winfo = GetlpG2Info(hwnd);

  if(enable && winfo->offscreen == 0) {
    winfo->offscreen = 1;

    hbm = ImageCluster_GetBitmap(pixmap_index, NULL, NULL, NULL, NULL);
    if(hbm == NULL) {
      printf("Cannot get offscreen bitmap.\n");
      winfo->offscreen = 0;	
      return 0;
    }

    winfo->offscreen_bitmap = hbm;
  }

  if(!enable && winfo->offscreen == 1) {
    /* In order to bitblt our offscreen bitmap to the screen, it must
     * be selected out of offscreen_hdc, because a bitmap is allowed
     * to be selected into at most one HDC at a time (quoth MSDN).
     * Currently, we select it in and out for each drawing operation. If we
     * don't need to support Win98, we could leave it selected until here.
     * (I think). -fmw, 6/11/02 */
/*     if(SelectObject(winfo->offscreen_hdc, winfo->offscreen_old_hbm) == NULL) */
/*       printf("SelectObject to old bitmap failed\n"); */
    winfo->offscreen = 0;
  }
  return 1;
}
    
#endif


static int icon_offset_left, icon_offset_top;
static int icon_clip_left, icon_clip_top, icon_clip_right, icon_clip_bottom;

/* Used only when drawing to printer on Windows. */
long g2ext_set_icon_offsets(long left, long top,
			    long clip_left, long clip_top, long clip_right, long clip_bottom)
{
  GTRACE(" g2ext_set_icon_offsets %d,%d  %d %d %d %d\n", 
	  left, top, clip_left, clip_top, clip_right, clip_bottom);

  icon_offset_left = left;
  icon_offset_top = top;
  icon_clip_left = clip_left;
  icon_clip_top = clip_top;
  icon_clip_right = clip_right;
  icon_clip_bottom = clip_bottom;
  return 0;
}


#if defined(XWINDOWS)

static Drawable x11_get_destination_drawable(GensymXWindow *gwindow)
{
  Drawable drawable;

  if(gwindow->offscreen)
    drawable = gwindow->xpixmap;
  else
    drawable = gwindow->xwindow;

  return drawable;
}

/* Redirect all drawing to given window at given offset.
 * On Windows, we can do this with SetWindowOrgEx */
long g2ext_redirect_window(long window_index, long dx, long dy)
{
  /*ARGSUSED*/
  return 0;
}

static GC gc_push(GensymXWindow *gwindow, int left, int top, int right, int bottom,
		  int thick, int color, int nFunc)
{
  Display *display = gwindow->display_ptr;
  GC gc;
  XRectangle rect;

  gc = get_gc(gwindow, color, 0, nFunc);

  XSetLineAttributes(display, gc, thick, LineSolid, CapRound, JoinRound);

  rect.x = (short)left;
  rect.y = (short)top;
  rect.width = (unsigned short)(right - left);
  rect.height = (unsigned short)(bottom - top);
  XSetClipMask(display, gc, None);
  XSetClipRectangles(display, gc, 0, 0, &rect, 1, Unsorted);

  return gc;
}

static void gc_pop(GensymXWindow *gwindow, GC gc)
{
  Display *display = gwindow->display_ptr;
  XSetLineAttributes(display, gc, 0, LineSolid, CapButt, JoinMiter);
  XSetClipMask(display, gc, None);
}

#else

static HBITMAP old_bitmap_handle;
static POINT old_window_org;
static RECT old_clip_box;

static LPG2INFO draw_to_window;	/* Check for deletion? */
static int draw_to_window_index;
static int window_dx, window_dy;

/* A better name might be redirect_to_window. */
long g2ext_redirect_window(long window_index, long dx, long dy)
{
  HWND hwnd = NULL;

  GTRACE("g2ext_redirect_window:index=%d dx=%d dy=%d)\n", window_index, dx, dy);

  if(No_window) return -1;

  if(window_index < 0) {
    No_drawing = FALSE;
    draw_to_window = NULL;
    draw_to_window_index = 0;
    window_dx = 0;
    window_dy = 0;
  } else {
    /* This happens, eg, when scrolling the classic editor. */
    /*     if(draw_to_window && (draw_to_window_index != window_index)) */
    /*       printf("Warning: nested redirect to window %d from window %d.\n", */
    /* 	     window_index, draw_to_window_index); */

    draw_to_window_index = window_index;
    hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
    draw_to_window = GetlpG2Info(hwnd);

    if(hwnd == NULL || draw_to_window == NULL)
      No_drawing = TRUE;

    window_dx = dx;
    window_dy = dy;
  }

  GTRACE("  g2ext_redirect_window(%d, %d, %d) hwnd=%x info=%x [%d] DestHwnd=%x HDC=%x\n",
	 window_index, dx, dy, 
	 hwnd,
	 draw_to_window,
	 draw_to_window ? draw_to_window->window_handle : 0,
	 draw_to_window ? draw_to_window->hwnd : 0,
	 draw_to_window ? draw_to_window->hdc : 0);

  return 1;
}

/* Calls to get_destination_hdc must have a matching free_destination_hdc */
static HDC get_destination_hdc(LPG2INFO winfo)
{
  HDC hdc;
  HBITMAP hbm;

  if(draw_to_printer)		/* Currently printing. */
    return printer_dc;

  if(winfo->offscreen) {	/* Drawing to offscreen bitmap. */
    if((hbm = winfo->offscreen_bitmap) == NULL) {
      printf("Cannot allocate offscreen bitmap.\n");
      return winfo->hdc;
    }

    hdc = GhdcOffscreen;
    winfo->offscreen_old_hbm = SelectObject(hdc,hbm);
    if(winfo->offscreen_old_hbm == NULL) {
      printf("Cannot select offscreen bitmap.\n");
      return winfo->hdc;
    }
    return hdc;
  }

  if(draw_to_window) {		/* Drawing to alternate window. */
    hdc = draw_to_window->hdc;
    SetWindowOrgEx(hdc, -window_dx, -window_dy, &old_window_org);

    GTRACE("  get_destination_hdc: hdc 0x%0x hwnd(hdc) 0x%0x\n",
 	   hdc, WindowFromDC(hdc));
    return hdc;
  }

  return winfo->hdc;
}

/* This routine doesn't actually free the DC, but rather selects the
 * bitmap out of the DC, which we must do because the W98 GDI memory
 * managment routines in msgdimm (GetBitmapHandle) may reclaim the HBITMAP
 * at any time, and it must be out of any HDC then. */
static int free_destination_hdc(LPG2INFO winfo, HDC hdc)
{
  if(draw_to_printer)		/* Currently printing -- keep DC around. */
    return 0;

  if(hdc == winfo->hdc)
    return 0;

  if(winfo->offscreen) {
    if(hdc != GhdcOffscreen) {
      g2pvt_notify_user("Problem in free_destination_hdc hdc: %x, offscreen_hdc: %x\n",
			hdc, GhdcOffscreen);
      return 0;
    }
    SelectObject(GhdcOffscreen, winfo->offscreen_old_hbm);
    return 1;
  }

  if(draw_to_window) {
    SetWindowOrgEx(hdc, old_window_org.x, old_window_org.y, NULL);
    GTRACE("  free_destination_hdc: hdc 0x%0x hwnd(hdc) 0x%0x\n",
	    hdc, WindowFromDC(hdc));
    return 1;
  }

  return 0;
}

/* Clip to given rectangle, and optionally return old logical clip box.. */
static void clip_to_logical_rect(HDC hdc, int left, int top, int right, int bottom, RECT *old)
{
  GTRACE("  clip_to_logical_rect %d %d %d %d\n", left, top, right, bottom);
  if(old != NULL) {
    if(GetClipBox(hdc,old) == ERROR)
      printf("Error: GetClipBox failed.\n");
  }
  IntersectClipRect(hdc, left, top, right, bottom);
}

static restore_clip_box(HDC hdc, RECT *r)
{
  HRGN hrgn;

  GTRACE("  restore_clip_box %d %d %d %d\n", r->left, r->top, r->right, r->bottom);

  LPtoDP(hdc,(POINT *)r,2);
  hrgn = CreateRectRgnIndirect(r);
  SelectClipRgn(hdc,hrgn);
  DeleteObject(hrgn);
}

static HDC get_pixmap_hdc(int pixmap_index, long *color)
{
  HDC hdc;

  if(draw_to_printer) {
    hdc = printer_dc;
    clip_to_logical_rect(hdc, icon_clip_left, icon_clip_top, icon_clip_right, icon_clip_bottom,
			 &old_clip_box);
    SetWindowOrgEx(hdc, -icon_offset_left, -icon_offset_top, &old_window_org);

  } else {
    int xoff, yoff, width, height;
    HBITMAP hbm = ImageCluster_GetBitmap(pixmap_index, &xoff, &yoff, &width, &height);

    if (hbm == NULL)
      return NULL;

    hdc = GhdcMem;
    /* Select bitmap into the memory DC */
    old_bitmap_handle = SelectObject(hdc, hbm);

    /* Offset to bitmap within cluster */
    SetWindowOrgEx(hdc, -xoff, -yoff, &old_window_org);
    SelectClipRgn(hdc, NULL);
    if(width>0)
      IntersectClipRect(hdc, 0, 0, width, height);

    /* Convert the color (when drawing to bitmaps, color is
     * either 1 (white) or 0 (black). */
    if(color) {
      GTRACE(" get_pixmap_hdc: color=%06x\n", *color);
      *color = (*color == 1) ? RGB(255,255,255) : RGB(0,0,0);
    }
  }
  return hdc;
}

static void free_pixmap_hdc(HDC hdc)
{
  if(draw_to_printer) {
    SetWindowOrgEx(hdc, old_window_org.x, old_window_org.y, NULL);
    restore_clip_box(hdc, &old_clip_box);
  }
  else {
    SelectClipRgn(hdc, NULL);
    SetWindowOrgEx(hdc, old_window_org.x, old_window_org.y, NULL);
    SelectObject(hdc, old_bitmap_handle);
  }
}

static HPEN select_pen(HDC hdc, long color, int width)
{
  HPEN hpen;
  LOGBRUSH lb;

  if(width != 0) {
    lb.lbStyle = BS_SOLID;
    lb.lbColor = (COLORREF)color;
    lb.lbHatch = 0;
    hpen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID | PS_JOIN_MITER | PS_ENDCAP_SQUARE,
			width, &lb, 0, NULL);
  }
  else if(color == RGB(0,0,0))
    hpen = GhpenBlack;
  else if(color == RGB(255,255,255))
    hpen = GhpenWhite;
  else
    hpen = CreatePen(PS_SOLID, 0, (COLORREF) color);

  return SelectObject(hdc,hpen);
}

static HBRUSH select_brush(HDC hdc, DWORD color)
{
  HBRUSH hbr;

  if(color == RGB(0,0,0))
    hbr = GhbrBlack;
  else if(color == RGB(255,255,255))
    hbr = GhbrWhite;
  else
    hbr = CreateSolidBrush((COLORREF) color);

  return SelectObject(hdc, hbr);
}

/* Set Windows rop code from G2's function_index. Return old rop code. */
/* Copied from draw line ... check this or define a get_hdc like get_gc */
static int set_rop2(HDC hdc, int function_index)
{
  switch (function_index) {
   case X11_OR: return  SetROP2(hdc, R2_MERGEPEN);
   case X11_XOR: return SetROP2(hdc, R2_XORPEN);
   case X11_COPY: return SetROP2(hdc, R2_COPYPEN);
   default: return SetROP2(hdc, R2_COPYPEN);
  }
}

typedef struct {
  HDC hdc;
  HBRUSH hbr, hOldBrush;
  HPEN hpen, hOldPen;
  int nOldROP2;
  RECT oldClip;
} HDCSTATE;

static void hdc_push(LPG2INFO info, HDCSTATE *s, 
		     int left, int top, int right, int bottom, /* Clip rect */
		     int line_color, int line_width, int fill_color,
		     int nFunc)
{
  s->hdc = get_destination_hdc(info);

  if(fill_color != TRANSPARENT_COLOR_VALUE)
    s->hbr = CreateSolidBrush(COLORVAL(fill_color));
  else
    s->hbr = (HBRUSH) GetStockObject(NULL_BRUSH);
  s->hOldBrush = SelectObject(s->hdc, s->hbr);

  if(line_color != TRANSPARENT_COLOR_VALUE)
    s->hpen = CreatePen(PS_SOLID, MAX(line_width,1), COLORVAL(line_color));
  else
    s->hpen = CreatePen(PS_NULL, 1, COLORVAL(0));
  s->hOldPen = SelectObject(s->hdc, s->hpen);

  s->nOldROP2 = set_rop2(s->hdc, nFunc);

  clip_to_logical_rect(s->hdc, left, top, right, bottom, &s->oldClip);
}

static void hdc_pop(LPG2INFO info, HDCSTATE *s)
{
  if(draw_to_printer) restore_clip_box(s->hdc, &s->oldClip);
  else SelectClipRgn(s->hdc,NULL);

  SetROP2(s->hdc, s->nOldROP2);
  SelectObject(s->hdc, s->hOldPen);
  DeleteObject(s->hpen);
  SelectObject(s->hdc, s->hOldBrush);
  DeleteObject(s->hbr);
  free_destination_hdc(info,s->hdc);
}

#endif





/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Pixmap Graphics Functions
 %
 % Description:
 %   These functions perform graphical operations in offscreen pixmaps
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
 * GC g2pvt_get_pix_gc( gwindow, pixmap, width, height, depth)
 *
 *   Description: 
 *     
 *   Input Arguments:
 *     gwindow
 *     pixmap
 *     width
 *     height
 *     depth
 *   Returns:
 *     return value: 
 *   Notes:
 *       If the call to XCreateGC changes to set line attributes to other than
 *     their default values, then g2ext_p_draw_wide_line, which calls 
 *     XSetLineAttributes must also be modified.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

GC g2pvt_get_pix_gc( gwindow, pixmap, width, height, depth)
     GensymXWindow	*gwindow;
     Pixmap	pixmap;
     int		width;
     int		height;
     int		depth;
{
    Display *display;
    XGCValues values;

    display = gwindow->display_ptr;
    values.plane_mask = AllPlanes;
    values.background = 0;
    values.foreground = 0;

    return( XCreateGC(display, pixmap,
		      GCPlaneMask|GCBackground|GCForeground,
		      &values) );
}
#endif /* XWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
 

/*****************************************************************************
 * GC get_gc(gwindow, foreground_color, background_color, function_index)
 *
 *   Description: 
 *     retrieves or creates a GC
 *   Input Arguments:
 *     gwindow
 *     foreground_color
 *     background_color
 *     function_index    0 =IOR, 1 =copy, 2 = XOR,
 *                       3 = AndInverted, 4 = TransparentCopy
 *   Returns:
 *     return value: 
 *   Notes:
 *       When a new graphics context is needed the following routine creates
 *     it and stores it in a table for later use.  This routine was written
 *     to enhance the performance of X in graphic requests.
 *     -----
 *       Note that this routine has been modified to use and cache only 2 GCs
 *     for the two functions, GCXcopy and GCXor.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

static GC get_gc(gwindow, foreground_color, background_color, function_index)
     GensymXWindow *gwindow;
     int foreground_color, background_color;
     int function_index;
{
    GC the_gc;
    XGCValues		gc_values;
    
    if (gwindow->global_gctable[function_index] == NULL) {

	/* Setup the desired values for this GC */
	gc_values.foreground = foreground_color;
	gc_values.background = background_color;
	gc_values.plane_mask = AllPlanes;
	gc_values.fill_style = FillSolid;
	gc_values.graphics_exposures = False;
	if      (function_index == X11_COPY) gc_values.function = GXcopy;
	else if (function_index == X11_XOR)  gc_values.function = GXxor;
        else if (function_index == X11_OR)   gc_values.function = GXor;
        else if (function_index == X11_AND)  gc_values.function = GXand;
        else if (function_index == X11_STIPPLED) { 
	    gc_values.function = GXcopy;
	    gc_values.fill_style = FillStippled;
	} else
	    gc_values.function = GXor;

	/* Make it */
	the_gc = XCreateGC(gwindow->display_ptr, gwindow->xwindow,
			   GCFillStyle|GCBackground|GCForeground|
			   GCFunction|GCGraphicsExposures,
			   &gc_values);

	/* Cache it */
	gwindow->global_gctable_foreground_color[function_index]
	    = foreground_color;
	gwindow->global_gctable_background_color[function_index]
	    = background_color;
	gwindow->global_gctable[function_index] = the_gc;
    } else {
	/* Used the cached GC */
	the_gc = gwindow->global_gctable[function_index];

	/* but synch up the colors, if necessary */
	if (background_color
 	    != gwindow->global_gctable_background_color[function_index]) {   
	    XSetBackground(gwindow->display_ptr, the_gc, background_color);
	    gwindow->global_gctable_background_color[function_index]
		= background_color;
	}
	if (foreground_color
	    != gwindow->global_gctable_foreground_color[function_index]) {
	    XSetForeground(gwindow->display_ptr, the_gc, foreground_color);
	    gwindow->global_gctable_foreground_color[function_index]
		= foreground_color;
	}
    }
    return(the_gc);
}

#  ifdef TEST_CPRIM
GC g2ext_x11_get_gc(gwindow, foreground_color, background_color, function_index)
     GensymXWindow *gwindow;
     int foreground_color, background_color;
     int function_index;
{
  return get_gc(gwindow, foreground_color, background_color, function_index);
}
#  endif

#endif /* XWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * void x11_handle_create_pixmap_error (display, event)
 *
 *   Description: 
 *     
 *   Input Arguments:
 *     
 *   Returns:
 *     return value: 
 *   Notes:
 *       We bind x11_handle_create_pixmap_error to be the X error handler
 *     while creating a pixmap, in order to catch BadAlloc errors.  Any
 *     other type of error is passed on to the default handler.
 *
 *     Including, unfortunately, BadValue, which is what we get when we
 *     try to create an 8bit pixmap on a 1bit server.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

static void x11_handle_create_pixmap_error (display, event)
     Display *display;
     XErrorEvent *event;
{
    last_x11_error_code = event->error_code;

    if (last_x11_error_handler && event->error_code != BadAlloc &&
	event->error_code != BadValue)
	(*last_x11_error_handler) (display, event);
}
#endif /* XWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * int g2ext_create_pixmap(window_index, width, height, depth)
 *
 *   Description: 
 *     Create a bitmap using the specified width and height
 *   Input Arguments:
 *     
 *   Returns:
 *     return value: -1 if the allocation failed.
 *   Notes:
 *       This is the only routine currently to do anything about exhausting
 *     storage!  Amazing isn't it?
 *     -----
 *       This code used to check the return value of XCreatePixmap for BadAlloc,
 *     XCreatePixmap does not return BadAlloc as a value, it signals an X error
 *     of that type.
 *     -----
 *       MS-Windows not only permits a bitmap creation to specify the number
 *     of planes but the number of bits per pixel as well.  There are no
 *     provisions for such from the caller. However, we are only supporting
 *     monochrome bitmaps in this release anyway so the whole issue of how to
 *     create a polychrome bitmap will wait for the future.
 *     -----
 *   Modifications:
 *       06/27/94, mpc:  Removing the restriction of only creating monochrome
 *     bitmaps. This is to support the addition of image data (gif files.)
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

int g2ext_create_pixmap(window_index, width, height, depth, irregular)
     int window_index;
     int width, height, depth, irregular;
{
    Display *display;
    PixmapStruct	*gpixmap;
    GensymXWindow *gwindow;
    int pwidth;
    long x11_depth;

    if (No_window)
	return (1);

    pwidth = width;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;
    gpixmap = MakeInstance(PixmapStruct);
    
    if (gpixmap == NULL)  /* Presumably this indicates space exausted. */
	return(-1);
    

    /* Allocate an X pixmap while checking for errors.  */
    last_x11_error_handler =
	XSetErrorHandler((XErrorHandler)x11_handle_create_pixmap_error);
    last_x11_error_code = Success;

    gpixmap->gensym_x_window_ptr = gwindow;
    gpixmap->display_ptr = display;
    x11_depth = g2ext_x11_screen_depth(window_index);
    gpixmap->pixmap = XCreatePixmap(display, gwindow->xwindow,
				    pwidth, height,
				    (x11_depth < depth) ? x11_depth : depth);
    /* NOTE: This dynamic binding of the error handler is completely bogus. Unless we call
       XSync before resetting it, then we won't get the error while it is bound. And we
       can't call XSync because it would be much too slow. -fmw, 6/2/04 */
    XSetErrorHandler(last_x11_error_handler);

    if (last_x11_error_code == BadAlloc || last_x11_error_code == BadValue) {
        free(gpixmap);
	return -1;
    }

    gpixmap->gc = g2pvt_get_pix_gc(gwindow, gpixmap->pixmap, width, height, depth);
    
    /* This is wrong, too. */
    if(gpixmap->gc == (GC)BadAlloc) {
        free(gpixmap);
	return(-1);
    }
    
    gpixmap->xcolor	= 0;	/* foreground set by g2pvt_get_pix_gc */
    gpixmap->width	= width;
    gpixmap->height	= height;
    gpixmap->depth	= depth;

    /* clear the pixmap */
    XFillRectangle(display, gpixmap->pixmap, gpixmap->gc, 0, 0, width, height);
    
    return(g2ext_cache_cpointer((long)gpixmap));
}

#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_create_pixmap(long window_index, long width, long height, long depth, long irregular)
{
  GTRACE(" g2ext_create_pixmap %dx%dx%d\n", width, height, depth);

  return ImageCluster_CreatePixmap(width, height, depth, irregular==1);
}

#endif /* MSWindows */

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_reclaim_pixmap( pixmap_index )
 *
 *   Description: 
 *     Reclaim a bitmap
 *   Input Arguments:
 *     pixmap_index
 *   Returns:
 *     return value: None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/
  
void g2ext_reclaim_pixmap(long pixmap_index)
{
#ifdef WIN32
  ImageCluster_ReclaimBitmap(pixmap_index);
#else /* XWindows */
  if (No_window)
    return;
  {
    Display *display;
    PixmapStruct	*gpixmap;

    gpixmap =  (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
    
    display = gpixmap->display_ptr;
    XFreePixmap(display, gpixmap->pixmap);
    XFreeGC(display, gpixmap->gc);
    g2ext_decache_g2pointer(pixmap_index);
    free((void *) gpixmap);	/* Never called */
  }
#endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*****************************************************************************
 * long g2ext_get_pixel(window_index, color_name, extended_color_p)
 *
 *   Description: 
 *     returns a pixel value corresponding to the color 
 *   Input Arguments:
 *     window_index
 *     color_name        X color string or rgb
 *     extended_color_p  1 = new color for images, 0 = G2 basic color
 *   Returns:
 *     return value: -1 on error or color value
 *   Notes:
 *       The function `g2ext_get_pixel' receives as input a color name string, which
 *     should be either a standard X11 color database color name string or an
 *     X11 rgb specification string.
 *     -----
 *       1/29/98 lgibson: COLORS, COLORMAPS and MAX_COLORS. 
 *     Displays or screens can have a number of
 *     color planes, which is the same as the number of 
 *     bits per pixel, or screen depth. Depth one is monochrome
 *     (no longer supported). Depth 8 gives you 2^8 = 256 colors
 *     which is usually enough for most work, unless some colors
 *     are being used by other processes. In that case its handy
 *     to be able to create your own private colormap
 *     (G2 has a -private-colormap command line option). The next
 *     most common depth is 24, which is the entirely adequate 16
 *     million colors. With depth 24, there is no reason
 *     I see to create your own colormap or do extended
 *     colors. Therefore, there is some code here and in windows.c
 *     that avoids doing anything with private colormaps when
 *     depth > 8. 
 *
 *     Note that MAX_COLORS is the max number of colors
 *     when depth 8 (256), so computations involving MAX_COLORS
 *     should not be happening when depth > 8. 
 *
 *     References: Xlib programming manual, Chapter 7, Color. 
 *     -----
 *       Note: when mapping fails, one might use a black (or white) pixel, as 
 *     given by the following code fragment:
 *
 *       parsed_color.pixel = BlackPixel(display, DefaultScreen(display));
 *
 *       The callers of the above function in G2 do not want this done
 *     automatically, since they will typically retry if a color name fails
 *     with an rgb spec.
 *     -----
 *       Note: consider special casing "black" to call BlackPixel and "white"
 *     to call WhitePixel if that is significantly faster.  But see next note
 *     first. Perhaps consider also guaranteeing that color names Black and
 *     White may never fail.
 *     -----
 *       Note: this does not need to be particularly fast at present because it
 *     is used just once (for each Gensym Color) at the time a G2 or Telewindows
 *     window is started up.  Since the list of Gensym colors is a system
 *     constant, more of the work done at initialization time in G2 could be
 *     done here and made more efficient if speed were an issue.
 *     -----
 *       Note: consider replacing this function with two new ones: map_color_
 *     name_to_pixel_value and map_rgb_to_pixel_value.  The former would take a
 *     color name string argument and the latter would take r, g, and b integer 
 *     arguments.
 *     -----
 *       12/1/93, mpc: This is called during startup, before anything is
 *     displayed. G2 first passes this a color name, which is fine on X based
 *     systems, and since MS Windows does not name its colors we pass back -1.
 *     G2 maintains a list of "factory defaults" for its colors, so it passes
 *     next an encoded RGB value. When parsed, this is passed to a Windows
 *     macro which will give us a "color value." Most importantly we put this
 *     value into our logical palette (for MS Windows). We also pass this value
 *     "back up" to the G2 code.
 *     -----
 *   Modifications:
 *       5/16/98, jv: More than half of the code in the X version of this
 *     function was never executed, because it depended on Private_colormap_p
 *     being true, and there was no way to set it to be true.  Now that we
 *     have introduced a command line switch to use a private color map, this
 *     code was actually run, and it turns out it didn't work.  The problem
 *     was in a part of the code where we were trying to minimize the 
 *     differences between our private color map and the default color map.
 *     I think that's fine if it comes relatively cheap, but not necessary,
 *     and just using the code to install the color in our own color map
 *     seems to work fine.  I'll leave as an optimization for someone else
 *     (yeah, right) to minimize the differences between the color maps.
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)
long g2ext_get_pixel(window_index, color_name, extended_color_p)
     long window_index;
     char *color_name;
     long extended_color_p;
{
    GensymXWindow *gwindow;
    Display *display;
    unsigned char *color_flags;
    Colormap default_colormap, colormap;
    XColor color;
    int i;
    static int colors_fit_into_flags_array = 1;

    if (No_window)
	return 1;

    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;
    colormap = gwindow->colormap;
    color_flags = gwindow->color_flags;

    default_colormap = DefaultColormap(display, DefaultScreen(display));
    if (!XParseColor(display, colormap, color_name, &color)) {
#  ifdef WARN_ABOUT_COLOR_NAME_PARSING_FAILURES
        fprintf(stderr, "Warning: unable to parse color name \"%s\"\n", color_name);
	fflush(stderr);
#  endif
	return -1;
    }

    if (Private_colormap_p) {
      /* Extended colors -- simply allocate in our private colormap. */
      for(i=0; i<MAX_COLORS; i++) {
	if (color_flags[i] == COLOR_FREE) {
	  color.pixel = i;
	  XStoreColor(display, colormap, &color);
	  break;
	}
      }
      if (i == MAX_COLORS) {
	/* No free colors in the private map! */
	fprintf(stderr, "Warning: unable to allocate color \"%s\" in private color map\n",
		color_name);
	fflush(stderr);
	return -1;
      }
    } else {
      /* No private color map.  Allocate all colors the same way. */
      if (!XAllocColor(display, default_colormap, &color)) {
	return -1;
      }
    }

    /*
     * Computations involving MAX_COLORS
     * are only appropriate when depth <= 8, see note above.
     */
    if (screen_depth_global <= DEPTH_EIGHT) {
      /* Note the allocation. */
      if (color.pixel < MAX_COLORS) {
	color_flags[color.pixel] = (extended_color_p ? COLOR_EXTENDED : COLOR_ALLOCATED);
      } else if (colors_fit_into_flags_array) {
	colors_fit_into_flags_array = 0;
	fprintf(stderr, "Warning: too many colors for Gensym internal data structure.\n");
	fflush(stderr);
      }
    }

    return color.pixel;
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_get_pixel(window_index, lpszColor, extended_color_p)
     long window_index;
     char *lpszColor;
     long extended_color_p;	/* An extended color for images. */
{
    int	         i=0;
    COLORREF	 nColorValue;
    int           red, green, blue;
    HWND           hwndServer;

    hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

    /* If this is an invalid window handle then can do nothing. */
    if ( IsWindow(hwndServer) ) {

	/* Parse the input color (X value or name.) */
	if (lpszColor[0] == '#') {
	    /* The color is an X color spec: #rrggbb */

	    if (sscanf(lpszColor, "#%02x%02x%02x", &red, &green, &blue) != 3)
		return(-1);
	    nColorValue = RGB(red, green, blue);
	} else {
	    /* The color is an X color NAME. We have a static map of
	     *  NAME to RGB value. Find this color's RGB value.
	     */
	    for (i=0; i<DEFAULT_COLORS; i++) {
		if ( strcmp(lpszColor, XColorArray[i].szColor)==0 ) {
		    nColorValue = XColorArray[i].rgbColor;
		    break;
		}
	    }
	}

	return (nColorValue);

    }

    /* Otherwise, if we couldn't find the NAME of the color, or if
     * the corresponding RGB isn't in our logical palette.
     */
    return (-1);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_copy_bitmap_to_bitmap(pixmap_struct1_index, pixmap_struct2_index,
 *                            x_offset, y_offset, x, y, width, height,
 *                            foreground_color)
 *
 *   Description: 
 *     stamp a bitmap into another bitmap.
 *   Input Arguments:
 *     pixmap_struct1_index   Source
 *     pixmap_struct2_index   Destination
 *     x_offset
 *     y_offset
 *     x
 *     y
 *     width
 *     height
 *     foreground_color
 *   Returns:
 *     return value: None
 *   Notes:
 *       The last arg "foreground_color" (sic) is used to control how the
 *     source is stamped into the destination.  This is used to "burn" holes
 *     in bitmaps so that when N bitmaps are XOR'd together onto the
 *     screen they won't interact with each other by virtue of having
 *     no "one" bits that overlap.
 *
 *       When the foreground_color is 1 this reduces to ORing the bitmaps
 *     together.  When the foreground_color is 0, this reduces to "andInvert"
 *     or (please turn all the bits in the destination to zero where there
 *     are ones in the source (i.e. burn a hole thru the destination).
 *     Both bitmaps must be only one bit deep.  The foreground_color
 *     had better be only zero or one.
 *
 *       This is used to create colorful graphs and icons by creating
 *     one bitmap for each color and then piling those onto the screen using
 *     XORing.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_copy_bitmap_to_bitmap(pixmap_struct1_index, pixmap_struct2_index,
			   x_offset, y_offset, x, y,
			   width, height, foreground_color)
     long pixmap_struct1_index, pixmap_struct2_index,
     x_offset, y_offset,
     x, y,
     width, height, foreground_color;
{
    GensymXWindow	*gwindow;
    Display *display;
    PixmapStruct	*gpixmap1;
    PixmapStruct	*gpixmap2;
    GC gc;

    if (No_window)
	return;

    gpixmap1 =  (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_struct1_index);
    gpixmap2 =  (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_struct2_index);
    gwindow = gpixmap1->gensym_x_window_ptr;
    /* assume that both pixmaps are from the window. */
    
    display = gwindow->display_ptr;
    gc = gpixmap1->gc;
    
    if(foreground_color==1)
	XSetFunction(display, gc, GXor);
    else
	XSetFunction(display, gc, GXandInverted);

    XCopyPlane(display, gpixmap1->pixmap, gpixmap2->pixmap,
	       gc, (int)x_offset, (int)y_offset, (int)width , (int)height,
	       (int)x, (int)y, 1);

    XSetFunction(display, gc, GXcopy);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_copy_bitmap_to_bitmap(long nBMSource_index, long nBMDest_index, 
				 long nSourceX, long nSourceY,
				 long nDestX, long nDestY,
				 long nWidth, long nHeight, long nColor)
{
  HBITMAP	hbmDest, hbmSource;
  HBITMAP	hOldDestBitmap, hOldSourceBitmap;
  HDC hdc, hdcDest, hdcSource;
  DWORD       dwRop;
  int xoff, yoff, w, h;

  GTRACE (" g2ext_copy_bitmap_to_bitmap %08x %d,%d to %08x %d,%d %dx%d\n",
	  nBMSource_index, nSourceX, nSourceY,
	  nBMDest_index, nDestX, nDestY, nWidth, nHeight);

  hbmSource = ImageCluster_GetBitmap(nBMSource_index, &xoff, &yoff, &w, &h);
  if (hbmSource == NULL)
    return;
  nSourceX += xoff;
  nSourceY += yoff;

  hbmDest = ImageCluster_GetBitmap(nBMDest_index, &xoff, &yoff, &w, &h);
  if (hbmDest == NULL)
    return;
  nDestX += xoff;
  nDestY += yoff;

  /* Setup the colors and copy mode. */
  if(nColor == 1) {
    dwRop = SRCPAINT;  /* This should be the equiv of X's GXor */
  } else {
    dwRop = 0x00220326; /* This should be the equiv of X's GXandInvert */
  }

  if(hbmSource == hbmDest) {
    hdc = CreateCompatibleDC(Ghdc);
    hOldSourceBitmap = SelectObject(hdc, hbmSource);

    if(w>0)
      IntersectClipRect(hdc, xoff, yoff, xoff+w, yoff+h);

    BitBlt(hdc, nDestX, nDestY, nWidth, nHeight, hdc, nSourceX, nSourceY, dwRop);

    SelectObject(hdc, hOldSourceBitmap);
    DeleteDC(hdc);

  } else {
    hdcSource = CreateCompatibleDC(Ghdc);
    hdcDest = CreateCompatibleDC(hdcSource);

    /* Load out bitmaps into their respective memory DC's */
    hOldSourceBitmap = SelectObject( hdcSource, hbmSource );
    hOldDestBitmap   = SelectObject( hdcDest, hbmDest );

    if(w>0)
      IntersectClipRect(hdcDest, xoff, yoff, xoff+w, yoff+h);

    /* Combine the source and dest bitmaps, leaving result in dest */
    BitBlt( hdcDest, nDestX, nDestY, nWidth, nHeight,
	    hdcSource, nSourceX, nSourceY, dwRop );

    /* Get our bitmaps OUT of their respective memory DC's */
    SelectObject( hdcDest, hOldDestBitmap );
    SelectObject( hdcSource, hOldSourceBitmap );

    DeleteDC( hdcDest );
    DeleteDC( hdcSource );
  }
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_x11_draw_pixmap (pixmap_index, window_index, mask_pixmap_index, src_x, src_y, width, height,
 *                       dst_x, dst_y, foreground, background)
 *
 *   Description: 
 *     bitblt workspace background images onto the G2 window
 *   Input Arguments:
 *     pixmap_index
 *     window_index
 *     src_x
 *     src_y
 *     width
 *     height
 *     dst_x
 *     dst_y
 *     foreground
 *     background
 *   Returns:
 *     return value: 
 *   Notes:
 *       Assuming the image has already been cached into the given pixmap
 *     (by g2ext_x11_put_image), we bitblt the given region of the pixmap. If the
 *     pixmap is actually a bitmap, then we draw it with the given foreground
 *     and background colors; otherwise, it shouldn't matter what values
 *     are supplied for fg and bg.
 *
 *       mhd, 11/20/01: added second arg; see g2ext_copy_pixmap_to_window
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_x11_draw_pixmap (pixmap_index, window_index, mask_pixmap_index,
		      src_x, src_y, width, height,
		      dst_x, dst_y, foreground, background)
     long pixmap_index, window_index, mask_pixmap_index,
     src_x, src_y,
     width, height,
     dst_x, dst_y,
     foreground, background; /* X colors. */
{
    Display *display;
    PixmapStruct *gpixmap;
    PixmapStruct *mask_gpixmap;
    GensymXWindow *gwindow;
    Pixmap pixmap, mask;
    Drawable drawable;
    GC gc;
    int src_depth;

    if (No_window || No_drawing)
	return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);

    /* gwindow = gpixmap->gensym_x_window_ptr; OBS.! -mhd, 11/20/01 */
    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

    display = gpixmap->display_ptr;
    pixmap = gpixmap->pixmap;
    src_depth = gpixmap->depth;

    if (mask_pixmap_index != -1)
      {
	mask_gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(mask_pixmap_index);
	mask = mask_gpixmap->pixmap;
      }
    else
      {
	mask = None;
      }
    
    gc = gwindow->images_gc;
    XSetForeground(display,gc,foreground);
    XSetBackground(display,gc,background);

    drawable = x11_get_destination_drawable(gwindow);

    if (mask != None)
      {
	XSetClipMask(display, gc, mask);
	XSetClipOrigin(display, gc, dst_x-src_x, dst_y-src_y);
      }
    if (src_depth == 1)
	XCopyPlane(display, pixmap, drawable, gc, (int)src_x, (int)src_y,
		   (int)width, (int)height, (int)dst_x, (int)dst_y,  1);
    else if (src_depth == screen_depth_global)
      XCopyArea(display, pixmap, drawable, gc, (int)src_x, (int)src_y,
		(int)width, (int)height, (int)dst_x, (int)dst_y);
    else
	printf("Internal error: source depth %d, dest depth %d not handled.\n",
	       src_depth, screen_depth_global);
    if (mask != None)
      {
	XSetClipOrigin(display, gc, 0, 0);
	XSetClipMask(display, gc, None);
      }
}

void g2ext_x11_draw_mask_pixmap (long pixmap_index, long window_index, long mask_pixmap_index, 
		    long src_x, long src_y, 
		    long width, long height,
		    long dst_x, long dst_y, long foreground, long background)
{
	g2ext_x11_draw_pixmap(pixmap_index, window_index, mask_pixmap_index, src_x, src_y, width, height,
		dst_x, dst_y, foreground, background);
}

#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

// CopyMaskBitmap() copies src bitmap to dst and replaces all light pixels to by RGB(0x77, 0x77, 0x77)
void CopyMaskBitmap(HBITMAP src, HBITMAP dst)
{
	HDC hdc_src, hdc_dst;
	HBRUSH brush;
	HBITMAP old_bitmap_src, old_bitmap_dst;
	RECT rect;
	BITMAP bm;

	GetObject(src, sizeof(BITMAP), (BITMAP*) &bm);
	rect.top = rect.left = 0;
	rect.right = bm.bmWidth;
	rect.bottom = bm.bmHeight;

	hdc_src = CreateCompatibleDC(NULL);
	old_bitmap_src = SelectObject(hdc_src, src);

	hdc_dst = CreateCompatibleDC(NULL);
	old_bitmap_dst = SelectObject(hdc_dst, dst);

	// Create mask image.
	// Use RGB(0x77, 0x77, 0x77) for mask instead light colors
	brush = CreateSolidBrush(RGB(0x77, 0x77, 0x77));
	FillRect(hdc_dst, &rect, brush);
	DeleteObject(brush);

	// Copy image
	BitBlt(hdc_dst, 0, 0, bm.bmWidth, bm.bmHeight, hdc_src, 0, 0, SRCAND);

	// Destroy data
	SelectObject(hdc_src, old_bitmap_src);
	SelectObject(hdc_dst, old_bitmap_dst);
	DeleteDC(hdc_src);
	DeleteDC(hdc_dst);
}

void DrawBitmapTransparent(HDC hdc, HDC hdcImage,
			   long dst_x, long dst_y,
			   long width, long height,
			   long src_x, long src_y,
			   HBITMAP hMask,
			   int depth,
			   long foreground, long background)
{
   HBITMAP    hbmOldMask, hbmOldWork, hbmOldImageC, hbmWork, hbmImageC;
   HDC        hdcWork, hdcMask, hdcImageC;

   /* Create the Device contexts */
   hdcImageC = CreateCompatibleDC(hdc);
   hdcWork   = CreateCompatibleDC(hdc);
   hdcMask   = CreateCompatibleDC(hdc);

   /* Create the bitmaps */
   hbmImageC = CreateCompatibleBitmap(hdc, width, height);
   hbmWork   = CreateCompatibleBitmap(hdc, width, height);

   /* Select the bitmaps into the corresponding device contexts */
   hbmOldImageC = SelectObject(hdcImageC, hbmImageC);
   hbmOldWork = SelectObject(hdcWork, hbmWork);
   hbmOldMask = SelectObject(hdcMask, hMask);

   /* Make a working copy of the image device context */
   if (depth == 1) {
     SetBkColor(hdcImageC, COLORVAL(foreground));   /* Color of "1" bits */
     SetTextColor(hdcImageC, COLORVAL(background)); /* Color of "0" bits */
   }
   BitBlt(hdcImageC, 0, 0, width, height, hdcImage, src_x, src_y, SRCCOPY);
   if (depth == 1) {
     SetBkColor(hdcImageC, COLORVAL(background));   /* Color of "1" bits */
     SetTextColor(hdcImageC, COLORVAL(foreground)); /* Color of "0" bits */
   }

   /* invert the mask into the working buffer*/
   BitBlt(hdcWork, 0, 0, width, height, hdcMask, src_x, src_y, NOTSRCCOPY);

   /* get the screen background into the working buffer
      creating a second mask */
   BitBlt(hdcWork, 0, 0, width, height, hdc, dst_x, dst_y, SRCAND);

   /* combine the original mask with the image copy */
   BitBlt(hdcImageC, 0, 0, width, height, hdcMask, src_x, src_y, SRCAND);

   /* combine the working buffer(a second mask) and the image-copy/mask */
   BitBlt(hdcWork, 0, 0, width, height, hdcImageC, 0, 0, SRCPAINT);

   /* put the working buffer onto the screen*/
   BitBlt(hdc, dst_x, dst_y, width, height, hdcWork, 0, 0, SRCCOPY);

   /* must select old bitmaps back in so new ones can be deleted */
   SelectObject(hdcImageC, hbmOldImageC);
   SelectObject(hdcWork, hbmOldWork);
   SelectObject(hdcMask, hbmOldMask);

   /* delete the bitmaps */
   DeleteObject(hbmImageC);
   DeleteObject(hbmWork);
   
   /* delete the Device contexts */
   DeleteDC(hdcImageC);
   DeleteDC(hdcWork);
   DeleteDC(hdcMask);
}

void g2ext_x11_draw_pixmap (long pixmap_index, long window_index, long mask_pixmap_index, 
			    long src_x, long src_y, 
			    long width, long height,
			    long dst_x, long dst_y, long foreground, long background)
{
    HBITMAP   hbm, hbmMask=NULL, hOldBM;
    BITMAP    bm;
    int       src_depth, dst_depth, savedDC;
    HWND hwndServer;
    LPG2INFO window_info;
    HDC hdc;
    int xoff, yoff;

    GTRACE(" g2ext_x11_draw_pixmap: %d,%d %dx%d fg=%06x bg=%06x pixmap=%d mask=%d\n",
	   dst_x, dst_y, width, height, foreground, background,
	   pixmap_index, mask_pixmap_index);


    if (No_drawing)
      return;

    hbm = ImageCluster_GetBitmap(pixmap_index, &xoff, &yoff, NULL, NULL);
    src_x += xoff;
    src_y += yoff;

    hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
    window_info = GetlpG2Info(hwndServer);

    if (hbm != NULL) {
        hdc = get_destination_hdc(window_info);

	GetObject( hbm, sizeof(BITMAP), (BITMAP *)&bm);
	src_depth = bm.bmBitsPixel;
	dst_depth = GetDeviceCaps(hdc, BITSPIXEL);

	hOldBM = SelectObject(GhdcMem, (HBITMAP)hbm);

	/* Get the Mask bitmap*/
	if (mask_pixmap_index != -1)
	  hbmMask = ImageCluster_ExtractBitmap(mask_pixmap_index);
	
	if (src_depth == 1) {
	    savedDC = SaveDC(hdc);	    

	    if (mask_pixmap_index != -1) {
	      DrawBitmapTransparent(hdc, GhdcMem, dst_x, dst_y, width, height,
				    src_x, src_y, hbmMask, 1,
				    foreground, background);
	    } else {
	      SetBkColor(hdc, COLORVAL(foreground));   /* Color of "1" bits */
	      SetTextColor(hdc, COLORVAL(background)); /* Color of "0" bits */
	      BitBlt( hdc, dst_x, dst_y, width, height,
		      GhdcMem, src_x, src_y, SRCCOPY );
	    }
	    RestoreDC(hdc, savedDC);
	} else if (src_depth == dst_depth) {
	  if (mask_pixmap_index != -1) {
	    DrawBitmapTransparent(hdc, GhdcMem, dst_x, dst_y, width, height,
				  src_x, src_y, hbmMask, src_depth,
				  foreground, background);
	  } else { 
	    BitBlt( hdc, dst_x, dst_y, width, height,
		    GhdcMem, src_x, src_y, SRCCOPY );
	  }
	} else {
	    printf("Internal error: source depth %d, dest depth %d not handled.\n", 
		   src_depth, dst_depth);
	}

	/* Select bitmap OUT of the memory DC */
	SelectObject(GhdcMem, hOldBM);

	/* Select offscreen bitmap (if any) out of its DC */
	free_destination_hdc(window_info, hdc);
	if(hbmMask)
	  ImageCluster_ReclaimExtractedBitmap(mask_pixmap_index, hbmMask);
    }
}

// g2ext_x11_draw_mask_pixmap() does the same as g2ext_x11_draw_pixmap(), but also
// creates a copy of pixmap to avoid using light colors as a mask transparent color
void g2ext_x11_draw_mask_pixmap (long pixmap_index, long window_index, long mask_pixmap_index, 
			    long src_x, long src_y, 
			    long width, long height,
			    long dst_x, long dst_y, long foreground, long background)
{
	HBITMAP hbm;
	HBITMAP newbm;
	BITMAP bm;
	long new_pixmap = -1;

	if (No_window || No_drawing)
		return;

	hbm = ImageCluster_GetBitmap(pixmap_index, NULL, NULL, NULL, NULL);
	GetObject(hbm, sizeof(BITMAP), (BITMAP*) &bm);

	if (bm.bmBitsPixel != 1 && mask_pixmap_index == -1)
	{
		// Create new pixmap
		new_pixmap = g2ext_create_pixmap(window_index, bm.bmWidth, bm.bmHeight, bm.bmBitsPixel, 1);
		newbm = ImageCluster_GetBitmap(new_pixmap, NULL, NULL, NULL, NULL);

		CopyMaskBitmap(hbm, newbm);

		pixmap_index = new_pixmap;
	}

	// draw pixmap
	g2ext_x11_draw_pixmap(pixmap_index, window_index, mask_pixmap_index, src_x, src_y, width, height,
		dst_x, dst_y, foreground, background);

	// destroy new pixmap
	if (new_pixmap != -1)
	{
		g2ext_reclaim_pixmap(new_pixmap);
	}
}

#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * static void x11_ensure_pixmap_color (gpixmap, xcolor)
 *
 *   Description: 
 *     Sets the color into the pixmap's GC, if needed
 *   Input Arguments:
 *     gpixmap
 *     xcolor
 *   Returns:
 *     return value: 
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

static void x11_ensure_pixmap_color (gpixmap, xcolor)
     PixmapStruct *gpixmap;
     int xcolor;
{
    if (xcolor != gpixmap->xcolor) {
	if ((xcolor != 0) && (gpixmap->depth >= 1))
	    xcolor = 1;
	XSetForeground(gpixmap->display_ptr, gpixmap->gc, xcolor);
	gpixmap->xcolor = xcolor;
    }
}
#endif /* XWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * void g2ext_p_draw_point(pixmap_index, x, y, xcolor)
 *
 *   Description: 
 *     Draws a single pixel at x,y coordinates of given pixmap
 *   Input Arguments:
 *     pixmap_index
 *     x,y
 *     xcolor
 *   Returns:
 *     return value: None
 *   Notes:
 *     Used extensively for drawing font rasters. See sp_set_bitmap_bits in fnt/c/fontrip.c
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_p_draw_point(pixmap_index, x, y, xcolor)
     long pixmap_index, x, y, xcolor;
{
    PixmapStruct	*gpixmap;

    if (No_window)
	return;
    if(draw_to_printer)
      return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
    
    x11_ensure_pixmap_color(gpixmap, (int)xcolor);
    
    XDrawPoint(gpixmap->display_ptr, gpixmap->pixmap, gpixmap->gc, (int)x, (int)y);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_draw_point(long pixmap_index, long nX, long nY, long nColor)
{
  HDC hdc;
  long old = nColor;

  GTRACE(" g2ext_p_draw_point(%d, %d) color = 0x%0x\n", nX, nY, nColor);

  hdc = get_pixmap_hdc(pixmap_index, &nColor);
  if(hdc == NULL)
    return;

  SetPixelV(hdc, nX, nY, nColor);

  free_pixmap_hdc(hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_p_draw_line(pixmap_index, x1, y1, x2, y2, xcolor)
 *
 *   Description: 
 *     Draws a line on given pixmap
 *   Input Arguments:
 *     pixmap_index
 *     x1,y1,x2,y2
 *     xcolor
 *   Returns:
 *     return value: None
 *   Notes:
 *       This routine is the same as the one used for drawing wide lines
 *     except that we assume that lines are a single pixel wide so we
 *     may as well just pass the args on.
 *     -----
 *       MSWindows does not draw the final point of a line.  To compensate,
 *     SetPixel() is called to draw it.  To improve efficiency and avoid
 *     two system calls for the most prevalent cases, vertical and
 *     horizontal lines are treated as special cases by adding 1 to
 *     the line length.
 *     -----
 *     Used extensively for drawing font rasters. See sp_set_bitmap_bits in fnt/c/fontrip.c
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_p_draw_line(pixmap_index, x1, y1, x2, y2, xcolor)
     long pixmap_index, x1, y1, x2, y2, xcolor;
{
    PixmapStruct *gpixmap;

    if (No_window)
      return;
    if(draw_to_printer)
      return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
    
    x11_ensure_pixmap_color(gpixmap, (int)xcolor);
    
    XDrawLine(gpixmap->display_ptr, gpixmap->pixmap,
	      gpixmap->gc, (int)x1, (int)y1, (int)x2, (int)y2);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_draw_line(long pixmap_index, long nX1, long nY1, long nX2, long nY2, long nColor)
{
  HDC hdc;
  HPEN hOldPen;
  long old = nColor;

  GTRACE(" g2ext_p_draw_line(%d,%d, %d,%d) color=0x%0x\n", nX1, nY1, nX2, nY2, nColor);

  hdc = get_pixmap_hdc(pixmap_index, &nColor);
  if(hdc == NULL)
    return;

  hOldPen = select_pen(hdc, nColor, 0);	/* Width? */

  /* Draw the line. */
  if(draw_to_printer) {		    /* Special case when printing, avoid the SetPixel.  */
    MoveToEx(hdc, nX1, nY1, NULL);
    LineTo(hdc, nX2, nY2);

  } else if (nY1 == nY2) {          /* if vertical or a single point */
    if (nX1 <= nX2) {
      MoveToEx(hdc, nX1, nY1, NULL);
      LineTo(hdc, nX2 + 1 , nY1);
    } else {
      MoveToEx(hdc, nX2, nY1, NULL);
      LineTo(hdc, nX1 + 1, nY1);
    }
  } else if (nX1 == nX2) {   /* if horizontal */
    if (nY1 <= nY2) {
      MoveToEx(hdc, nX1, nY1, NULL);
      LineTo(hdc, nX1, nY2 + 1);
    } else {
      MoveToEx(hdc, nX1, nY2, NULL);
      LineTo(hdc, nX1, nY1 + 1);
    }
  } else {                   /* must be diagonal */
    MoveToEx(hdc, nX1 , nY1, NULL);
    LineTo(hdc, nX2 , nY2);
    /* Draw the final point */
    SetPixelV(hdc, nX2, nY2, nColor);
  }
  DeleteObject(SelectObject(hdc, hOldPen));

  free_pixmap_hdc(hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_p_draw_wide_line(pixmap_index, x1, y1, x2, y2, xcolor, line_width)
 *
 *   Description: 
 *     Draws a wide line on given pixmap
 *   Input Arguments:
 *     pixmap_index
 *     x1,y1,x2,y2
 *     xcolor
 *     line_width
 *   Returns:
 *     return value: None
 *   Notes:
 *      Only used by graphs as of 1/11/02. 
 *      See paint-graph-line-in-current-scratchpad-raster
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_p_draw_wide_line(pixmap_index, x1, y1, x2, y2, xcolor, line_width)
     long pixmap_index, x1, y1, x2, y2, xcolor, line_width;
{
    PixmapStruct	*gpixmap;

    if (No_window)
	return;
    if(draw_to_printer)
      return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
    
    x11_ensure_pixmap_color(gpixmap, (int)xcolor);

    XSetLineAttributes (gpixmap->display_ptr, gpixmap->gc,
			(int)line_width, LineSolid, CapButt, JoinMiter);

    XDrawLine(gpixmap->display_ptr, gpixmap->pixmap,
	      gpixmap->gc, (int)x1, (int)y1, (int)x2, (int)y2);
    

    /* Set line attributes back to default. */
    XSetLineAttributes (gpixmap->display_ptr, gpixmap->gc,
			0, LineSolid, CapButt, JoinMiter);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_draw_wide_line(long pixmap_index, long nX1, long nY1, long nX2, long nY2,
			    long nColor, long nWidth )
{
  HDC hdc;
  HPEN hOldPen;

  GTRACE(" g2ext_p_draw_wide_line\n");

  hdc = get_pixmap_hdc(pixmap_index, &nColor);
  if(hdc == NULL)
    return;

  hOldPen = select_pen(hdc, nColor, nWidth);

  MoveToEx(hdc, nX1 , nY1, NULL);
  LineTo(hdc, nX2 , nY2);

  DeleteObject(SelectObject(hdc, hOldPen));
  free_pixmap_hdc(hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/






/*****************************************************************************
 * g2ext_w_draw_wide_polyline
 *
 *   Description: 
 *     Draws a polyline on window with given color, thickness, and dot pattern.
 *   Input Arguments:
 *     window_index
 *     packed_points, npoints Short array of alternating x and y values.
 *                            On Win32, this is a signed int32 array.
 *     left,top,right,bottom  Clipping rectangle. Open on the right and bottom.
 *     xcolor                 Color value
 *     line_width             Line width in pixels.  0 means use fast (cosmetic) lines.
 *     pattern                dot/dash pattern. 0 means solid.
 *     function_index
 *   Returns:
 *     return value: None
 *   Notes:
 *     Used for wide diagonal and patterned connections.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

//added in Gensym-320
static long lastWindowIndex = -1;
static GensymXWindow *lastWindow = 0;
void g2ext_w_draw_wide_polyline(long window_index,
				short *points,
				long npoints,
				long left, long top, long right, long bottom,
				long xcolor,
				long width, long style,
				short *dashes, long ndashes,
				long function_index)
{
  GensymXWindow *gwindow;
  Display *display;
  Drawable drawable;
  GC gc;
  XRectangle rect;
  char dash_list[MAX_DASH_COUNT];
  int line_style, cap_style, join_style;
  int i, ndash, w;

  if (No_window || No_drawing) return;


  if(window_index == lastWindowIndex) {
	gwindow = lastWindow;	  
  } else {
	gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
	lastWindow = gwindow;
	lastWindowIndex = window_index;
  }

  //end of changes
  /* If background != transparent, then we want LineDoubleDash */
  //gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
  gc = get_gc(gwindow, xcolor, 0, function_index);

  display = gwindow->display_ptr;
  drawable = x11_get_destination_drawable(gwindow);
    
  XSetClipMask(display, gc, None); /* Needed? */

  /* This should be done once by on-window, not for each graphics call! */
  /* Rumor has it that changing the clip region is expensive under X. */
  rect.x = (short)left;
  rect.y = (short)top;
  rect.width = (unsigned short)(right - left);
  rect.height = (unsigned short)(bottom - top);
  XSetClipRectangles(display, gc, 0, 0, &rect, 1, Unsorted);

  /* The canned patterns are designed to match Win32. In particular,
   * the dash lengths scale with the width of the line. We go to the
   * trouble of doing this in hopes that the canned Win32 patterns
   * have, eg, hardware support. */

  if(ndashes>MAX_DASH_COUNT) ndashes=MAX_DASH_COUNT;

  w=width;
  if(w == 0) w=1;
  switch(style & PS_STYLE_MASK)
    {
    case PS_DASH:
      dash_list[0] = MIN(3*w,127);
      dash_list[1] = MIN(1*w,127);
      line_style = LineOnOffDash;
      ndash=2; break;
    case PS_DOT:
      dash_list[0] = MIN(1*w,127);
      dash_list[1] = MIN(1*w,127);
      line_style = LineOnOffDash;
      ndash=2; break;
    case PS_DASHDOT:
      dash_list[0] = MIN(3*w,127);
      dash_list[1] = MIN(1*w,127);
      dash_list[2] = MIN(1*w,127);
      dash_list[3] = MIN(1*w,127);
      line_style = LineOnOffDash;
      ndash=4; break;
    case PS_DASHDOTDOT:
      dash_list[0] = MIN(3*w,127);
      dash_list[1] = MIN(1*w,127);
      dash_list[2] = MIN(1*w,127);
      dash_list[3] = MIN(1*w,127);
      dash_list[4] = MIN(1*w,127);
      dash_list[5] = MIN(1*w,127);
      line_style = LineOnOffDash;
      ndash=6; break;
    case PS_USERSTYLE:
      ndash = 0;
      for(i=0; i<ndashes; i++)
		//Gensym-320	
        dash_list[ndash++] = 1 | (127 & dashes[i]); /* Dashes are already scaled here. */
      line_style = LineOnOffDash;
      width = w;                /* If patterned, don't use cosmetic lines. */
      break;
    case PS_SOLID:
    default:
      line_style = LineSolid;
      ndash = 0;
      break;
    }

  switch(style & PS_ENDCAP_MASK)
    {
    case PS_ENDCAP_SQUARE:
      cap_style = CapProjecting;
      break;
    case PS_ENDCAP_FLAT:
      cap_style = CapButt;
      break;
    case PS_ENDCAP_ROUND:
    default:
      cap_style = CapRound;
      break;
    }

  switch(style & PS_JOIN_MASK)
    {
    case PS_JOIN_BEVEL:
      join_style = JoinBevel;
      break;
    case PS_JOIN_MITER:
      join_style = JoinMiter;
      break;
    case PS_JOIN_ROUND:
    default:
      join_style = JoinRound;
      break;
    }

  if(ndash>0)
    XSetDashes(display, gc, 0, dash_list, ndash);

  /* Note: we are using hardware (width=0) lines here.
   * On the sparc, they look much better than geometric width==1 lines. */
  XSetLineAttributes (display, gc, (int)width, line_style, cap_style, join_style);
  XDrawLines(display, drawable, gc, (XPoint*)points, (int)npoints, CoordModeOrigin);

  /* Set line attributes back to default. */
  /* No need to reset the dashes since we set the style to LineSolid */
  XSetLineAttributes (display, gc, 0, LineSolid, CapButt, JoinMiter);
  XSetClipMask(display, gc, None);
}
#endif /* XWindows */

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

//added in Gensym-320
static HWND last_window_ptr = 0;
static long last_window_index = -1;
static LPG2INFO last_window_info = 0;
static LOGBRUSH lb;
// end of changes;
void g2ext_w_draw_wide_polyline(long window_index,
                                LONG *points, /* LONG is a 32bit signed integer. */
                                long npoints,
                                long left, long top, long right, long bottom,
                                long xcolor,
                                long width, long style,
                                short *dashes, long ndashes,
                                long function_index)
{
  HWND   hwnd;
  HPEN   hpen, hOldPen;
  int         nOldROP2;
  LPG2INFO window_info;
  HDC hdc;
  //LOGBRUSH lb;
  DWORD i, ndash, dash_list[MAX_DASH_COUNT];
  DWORD line_style;
  POINT *wpoints = (POINT *)points;
  RECT oldClip;

  GTRACE(" g2ext_w_draw_wide_polyline\n");

  if (No_drawing) return;

  //added in Gensym-320: handles reusing
  if (window_index == last_window_index) {
	 hwnd = last_window_ptr;
	 window_info = last_window_info;
  } else {		 
	hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
	last_window_index = window_index;
	last_window_ptr = hwnd;
	window_info = GetlpG2Info(hwnd);
	last_window_info = window_info;
	lb.lbStyle = BS_SOLID;
	lb.lbHatch = 0;
  }	


  //end of changes

  //Gensym-320: checked in the below procedure
  //if (!IsWindow(hwnd)) return;

  //window_info = GetlpG2Info(hwnd);

  if(window_info == NULL) return;

  /* Initialize the pen's brush. */
  /* Use SetBkMode and SetBkColor for the background color */

  lb.lbColor = xcolor;


  /* Here we use the fact that our style bits match those of Win32. */
  line_style = style & (PS_STYLE_MASK | PS_JOIN_MASK | PS_ENDCAP_MASK);

  /* Cosmetic lines are fast, but they differ too much from geometric
   * lines when the line is dashed.  So use them only when solid.
   * However, we really want to use cosmetic lines for the selection rectangle,
   * to make it fast, and since we don't care how it looks exactly. */
  if(width == 0)                /* && ((line_style&PS_STYLE_MASK) == PS_SOLID) */
    line_style |= PS_COSMETIC;
  else
    line_style |= PS_GEOMETRIC;

  if(width == 0) width = 1;        /* Width==0 never allowed in Win32. */

  /* Although Win32 allows dashes longer than 127, be consistent with X here. */
  ndash = ndashes > MAX_DASH_COUNT ? MAX_DASH_COUNT : ndashes;
  for(i=0; i<ndash; i++)
    //dash_list[i] = MAX(1,MIN(127,dashes[i])); /* Dashes are already scaled here. */
    dash_list[i] = 1 | (127 & dashes[i]); //Gensym-320: faster then above

  hpen = ExtCreatePen(line_style, width, &lb, ndash, (ndash>0) ? dash_list : NULL);

  if(hpen == NULL) {
    fprintf(stderr, "ERROR: Cannot create pen: %d %d", width, ndash);
    return;
  }

  hdc = get_destination_hdc(window_info);
  hOldPen = SelectObject(hdc, hpen);
  nOldROP2 = set_rop2(hdc, function_index);

  /* Assert the clipping region. */
  clip_to_logical_rect(hdc, left, top, right, bottom, &oldClip);

  Polyline(hdc, wpoints, npoints);

  /* TODO: Assuming clipping region was a rectangle. */
  if(draw_to_printer) restore_clip_box(hdc, &oldClip);
  else SelectClipRgn(hdc,NULL);

  SetROP2(hdc, nOldROP2);
  SelectObject(hdc, hOldPen);
  DeleteObject(hpen);

  /* Select offscreen bitmap (if any) out of its DC */
  free_destination_hdc(window_info,hdc);
}
#endif /* MSWindows */

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/





/*****************************************************************************
 * void g2ext_p_fill_rect(pixmap_index, x, y, width, height, xcolor)
 *
 *   Description:
 *     Draws a filled rectangle on given pixmap
 *   Input Arguments:
 *     pixmap_index
 *     x, y
 *     width, height
 *     xcolor
 *   Returns:
 *     return value: None
 *   Notes:
 *       Unused
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_p_fill_rect(pixmap_index, x, y, width, height, xcolor)
     long pixmap_index, x, y, width, height, xcolor;
{
  PixmapStruct *gpixmap;

  if (No_window)
    return;
  if(draw_to_printer)
    return;

  gpixmap =(PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);

  x11_ensure_pixmap_color(gpixmap, (int)xcolor);

  XFillRectangle(gpixmap->display_ptr, gpixmap->pixmap,
      gpixmap->gc, (int)x, (int)y, (int)width, (int)height);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_fill_rect(long pixmap_index, long nX, long nY, long nWidth, long nHeight, long nColor)
{
  HDC hdc;
  HBRUSH hbr;
  RECT r;

  GTRACE(" g2ext_p_fill_rect(%d,%d %dx%d) color=0x%0x\n", nX, nY, nWidth, nHeight, nColor);

  hdc = get_pixmap_hdc(pixmap_index, &nColor);
  if(hdc == NULL)
    return;

  hbr = CreateSolidBrush((COLORREF)nColor);

  r.left = nX;
  r.top = nY;
  r.right = nX + nWidth;
  r.bottom = nY + nHeight;
  FillRect(hdc, &r, hbr);

  DeleteObject(hbr);
  free_pixmap_hdc(hdc);
}

#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_p_stipple_rect(pixmap_index, stipple, x, y, width, height)
 *
 *   Description:
 *     stipples the rectangle, for a stippled effect
 *   Input Arguments:
 *     pixmap_index
 *     stipple,  0 (NOP), 1 (light), 2 (medium), 3 (dark)
 *     x, y
 *     width, height
 *   Returns:
 *     return value: None
 *   Notes:
 *       Unused
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)
void g2ext_p_stipple_rect (long pixmap_index, long stipple, long x, long y, long width, long height)
{
  if (No_window) return;
  if (stipple == no_stipple_stipple) return;
  {
    PixmapStruct *gpixmap =(PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
    GensymXWindow *gwindow  = gpixmap->gensym_x_window_ptr;
    Display *display = gwindow->display_ptr;
    long mask = GCStipple | GCFillStyle | GCFunction;
    XGCValues values;
    GC gc;

    values.stipple
      = ((stipple == stipple_25_percent_gray_stipple)
         ? gwindow->stipple_light
         : ((stipple == stipple_75_percent_gray_stipple)
            ? gwindow->stipple_dark : gwindow->stipple_medium));
    values.fill_style = FillStippled;
    values.function = GXand;
    gc = XCreateGC(display, gpixmap->pixmap, mask, &values);
    XFillRectangle(gpixmap->display_ptr, gpixmap->pixmap, gc,
                   (int)x, (int)y, (int)width, (int)height);
    XFreeGC(display, gc);
  }
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_stipple_rect (long pixmap_index, long stipple, long x, long y, long width, long height)
{
  HBRUSH brush
    = ((stipple == stipple_25_percent_gray_stipple)
       ? stipple_light
       : ((stipple == stipple_75_percent_gray_stipple)
          ? stipple_dark : stipple_medium));
  HDC hdc, temp_dc;
  HBITMAP temp_bitmap, old_temp_bitmap;
  HBRUSH old_brush;

  GTRACE(" g2ext_p_stipple_rect\n");

  if (No_window) return;
  if(draw_to_printer) return;        /* TODO: Stippling on printer DC's */

  hdc = get_pixmap_hdc(pixmap_index, NULL);
  if(hdc == NULL)
    return;

  temp_dc = CreateCompatibleDC(Ghdc);
  temp_bitmap = CreateBitmap(width, height, 1, 1, NULL);
  old_temp_bitmap = SelectObject(temp_dc, temp_bitmap);
  old_brush = SelectObject(temp_dc, brush);

  /* Fill temporary bitmap with the pattern. */
  PatBlt(temp_dc, 0, 0, width, height, PATCOPY);

  /* Combine (source) temporary bitmap with the (destination)
     bitmap, so that the bits on in the source AND the destination
     remain on. */
  BitBlt(hdc, x, y, width, height, temp_dc, 0, 0, SRCAND);

  SelectObject(temp_dc, old_brush);
  SelectObject(temp_dc, old_temp_bitmap);
  DeleteObject(temp_bitmap);
  DeleteDC(temp_dc);
  free_pixmap_hdc(hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_p_draw_arc(pixmap_index, x, y, width, height,
 *                 start_angle, displacement_angle, xcolor)
 *
 *   Description:
 *     Draws an arc on given pixmap
 *   Input Arguments:
 *     pixmap_index
 *     x,y
 *     width, height
 *     start_angle
 *     displacement_angle
 *     xcolor
 *   Returns:
 *     return value: None
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_p_draw_arc(pixmap_index, x, y, width, height,
                start_angle, displacement_angle, xcolor)
     long pixmap_index, x, y, width, height,
     start_angle, displacement_angle, xcolor;
{
    PixmapStruct *gpixmap;

    if (No_window)
        return;
    if(draw_to_printer)
      return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);

    x11_ensure_pixmap_color(gpixmap, (int)xcolor);

    XDrawArc(gpixmap->display_ptr, gpixmap->pixmap, gpixmap->gc,
             (int)x, (int)y, (int)width, (int)height,
             (int)start_angle, (int)displacement_angle);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_draw_arc(long pixmap_index, long nX, long nY, long nWidth, long nHeight,
                      long nSA, long nDA, long nColor)
{
  HDC hdc;
  HPEN hOldPen;
  int nX1, nX2, nY1, nY2;
  static void XlatArcCoords(long nX, long nY, long nWidth, long nHeight, long nSA, long nDA,
                            int *pnX1, int *pnY1, int *pnX2, int *pnY2);

  GTRACE(" g2ext_p_draw_arc() color=0x%0x\n", nColor);

  hdc = get_pixmap_hdc(pixmap_index, &nColor);
  if(hdc == NULL)
    return;

  hOldPen = select_pen(hdc, nColor, 0);        /* Width? */

  /* Calculate the arc. */
  XlatArcCoords(nX, nY, nWidth, nHeight, nSA, nDA, &nX1, &nY1, &nX2, &nY2);

  /* Draw the arc. */
  Arc(hdc, nX, nY, nX+nWidth, nY+nHeight, nX1, nY1, nX2, nY2);

  DeleteObject(SelectObject(hdc, hOldPen));
  free_pixmap_hdc(hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_p_fill_arc(pixmap_index, x, y, width, height,
 *                 start_angle, displacement_angle, xcolor)
 *
 *   Description:
 *     Draws a filled arc on given pixmap
 *   Input Arguments:
 *     pixmap_index
 *     x,y
 *     width, height
 *     start_angle
 *     displacement_angle
 *     xcolor
 *   Returns:
 *     return value: None
 *   Notes:
 *     Angles are relative to the 3 oclock position.
 *     Positive numbers move counter clockwise.
 *     Negative numbers move clockwise.
 *     MS-Windows uses x,y points on the arc for the start-stop.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_p_fill_arc(pixmap_index, x, y, width, height,
                start_angle, displacement_angle, xcolor)
     long pixmap_index, x, y, width, height,
     start_angle, displacement_angle, xcolor;
{
    PixmapStruct *gpixmap;

    if (No_window)
        return;
    if(draw_to_printer)
      return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
    x11_ensure_pixmap_color(gpixmap, (int)xcolor);

    XFillArc(gpixmap->display_ptr, gpixmap->pixmap, gpixmap->gc,
             (int)x, (int)y, (int)width, (int)height,
             (int)start_angle, (int)displacement_angle);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_fill_arc(long pixmap_index, long nX, long nY, long nWidth, long nHeight,
                      long nSA, long nDA, long nColor)
{
  HDC hdc;
  HBRUSH hOldBrush;
  HPEN hOldPen;

  GTRACE(" g2ext_p_fill_arc() color=0x%0x\n", nColor);

  hdc = get_pixmap_hdc(pixmap_index, &nColor);
  if(hdc == NULL)
    return;

  hOldBrush = select_brush(hdc, nColor);
  hOldPen = SelectObject(hdc, GetStockObject(NULL_PEN));

  /* Draw the arc. */
  Ellipse(hdc, nX, nY, nX+nWidth, nY+nHeight);

  SelectObject(hdc, hOldPen);
  DeleteObject(SelectObject(hdc, hOldBrush));

  free_pixmap_hdc(hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_p_fill_triangle(pixmap_index, x1, y1, x2, y2, x3, y3, xcolor)
 *
 *   Description:
 *     Draws a filled triangle on given pixmap
 *   Input Arguments:
 *     pixmap_index
 *     x1, y1, x2,y2, x3, y3
 *     xcolor
 *   Returns:
 *     return value: None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_p_fill_triangle(pixmap_index, x1, y1, x2, y2, x3, y3, xcolor)
     long pixmap_index, x1, y1, x2, y2, x3, y3, xcolor;
{
    XPoint points[3];
    PixmapStruct *gpixmap;

    if (No_window)
        return;
    if(draw_to_printer)
      return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);

    points[0].x = x1;
    points[0].y = y1;
    points[1].x = x2;
    points[1].y = y2;
    points[2].x = x3;
    points[2].y = y3;

    x11_ensure_pixmap_color(gpixmap, (int)xcolor);

    XFillPolygon(gpixmap->display_ptr, gpixmap->pixmap, gpixmap->gc,
                 points, 3, Convex, CoordModeOrigin);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_fill_triangle(long pixmap_index, long nX1, long nY1, long nX2, long nY2, long nX3,
                           long nY3, long nColor)
{
  HDC hdc;
  HBRUSH hOldBrush;
  HPEN        hOldPen;
  POINT        Points[3];

  GTRACE(" g2ext_p_fill_triangle(%d,%d %d,%d %d,%d color=0x%0x\n", nX1,nY1, nX2,nY2, nX3,nY3, nColor);

  hdc = get_pixmap_hdc(pixmap_index, &nColor);
  if(hdc == NULL)
    return;

  hOldBrush = select_brush(hdc, nColor);
  hOldPen = SelectObject(hdc, GetStockObject(NULL_PEN));
  /* SetROP2(hdc, R2_COPYPEN); */

  Points[0].x = nX1;
  Points[0].y = nY1;
  Points[1].x = nX2;
  Points[1].y = nY2;
  Points[2].x = nX3;
  Points[2].y = nY3;

  /* Draw the triangle. */
  Polygon(hdc, (LPPOINT)&(Points[0]), 3);

  SelectObject(hdc, hOldPen);
  DeleteObject(SelectObject(hdc, hOldBrush));
  free_pixmap_hdc(hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_copy_pixmap_to_window(pixmap_index, window_index, x_offset, y_offset, x, y,
 *                            width, height, foreground_xcolor, background_xcolor,
 *                            function_index)
 *
 *   Description:
 *     Copy an existing bitmap to the screen using the specified colors.
 *   Input Arguments:
 *     pixmap_index
 *     x_offset, y_offset
 *     x, y
 *     width, height
 *     foreground_xcolor, background_xcolor
 *     function_index
 *   Returns:
 *     return value: None
 *   Notes:
 *       This function is used by G2 for drawing icon layers and text; in
 *     other words, it is the most extensively used function in this file. The
 *     corresponding LISP function is c-x11-copy-pixmap.
 *     -----
 *   Modifications:
 *       7/13/94,jh:  Backed out of the changes outlined in my 7/8/94 note (q.v.)
 *     in /bt/ab/rtl/c/gensym.h for the last two arguments of
 *     g2ext_copy_pixmap_to_window(). This was not compiling on the AlphaOSF for
 *     reasons as yet unknown.  Mark S will send this as a small example to DEC,
 *     but until we get a fix, this superstitous rewrite will have to do.  Note
 *     that this doesn't make things any worse than before 7/8/94, when functions
 *     declared to take ints as args were being passed longs all over the place.
 *
 *       11/20/01, mhd: added second arg, window_index. Previously we were relying
 *     in the X case on a backpointer from the bitmap structure to the window,
 *     and in the Windows case on a global pointer to the window, and also
 *     on having just one window, which we want to now move beyond.
 *     -----
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_copy_pixmap_to_window(pixmap_index, window_index, x_offset, y_offset, x, y, width, height,
                           foreground_xcolor, background_xcolor, function_index)
     long pixmap_index, window_index, x_offset, y_offset, x, y,
          width, height, foreground_xcolor;
     int  background_xcolor,        /* was long (see 7/13/94 note above) */
     function_index;                /* was long (see 7/13/94 note above) */
{
    GC gc;
    GensymXWindow *gwindow;
    Display *display;
    Drawable drawable;
    PixmapStruct *gpixmap;
#   ifdef CLIP_FOR_DRAWING
    XRectangle clip_rect[1];
#   endif

    if (No_window || No_drawing)
        return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);

    /* gwindow = gpixmap->gensym_x_window_ptr; OBS.! -mhd, 11/20/01 */
    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

    display = gwindow->display_ptr;
    drawable = x11_get_destination_drawable(gwindow);

    /* function_index is always X11_STIPPLED in paint mode.
     * See current-transfer-mode-for-bitmaps-in-x11-windows -fmw, 12/29/01 */

    if (function_index == X11_STIPPLED) {
      gc = gwindow->stippled_gc;
      if (gwindow->stippled_gc_foreground_color != foreground_xcolor) {
        XSetForeground(display, gc, foreground_xcolor);
        gwindow->stippled_gc_foreground_color = foreground_xcolor;
      }

      if (gwindow->stippled_gc_clip_p == TRUE) {
        /* Clipping in general adds overhead, especially where network
           speed is an issue (non-local X Window).  But on a graphics card
           like the Powerstorm (running on Alpha Systems), this is needed
           to prevent a copy of n * w * h bits (n=n planes, w=window width,
           h=window height), typically over 4.5 Megabytes, per call! */
        XRectangle clip_rect[1];

        clip_rect[0].x = (short)x;
        clip_rect[0].y = (short)y;
        clip_rect[0].width = (unsigned short)width;
        clip_rect[0].height = (unsigned short)height;
        XSetClipRectangles(display, gc, 0, 0, clip_rect, 1, YXBanded);
      }

      XSetStipple(display, gc, gpixmap->pixmap);
      XSetTSOrigin(display, gc, (int)(x - x_offset), (int)(y - y_offset));
      XFillRectangle(display, drawable, gc, (int)x, (int)y,
                     (int)width, (int)height);
    }
    else                        /* not X11_STIPPLED case */
      {
        gc = get_gc(gwindow, foreground_xcolor, background_xcolor, function_index);
        if (function_index == X11_XOR || function_index == X11_COPY ||
            function_index == X11_OR || function_index == X11_AND) {
#       ifdef CLIP_FOR_DRAWING
          clip_rect[0].x = (short)x;
          clip_rect[0].y = (short)y;
          clip_rect[0].width = (unsigned short)width;
          clip_rect[0].height = (unsigned short)height;
          XSetClipRectangles(display, gc, 0, 0, clip_rect, 1, Unsorted);

          XCopyPlane( display, gpixmap->pixmap, drawable,
                      gc, 0, 0, gpixmap->width, gpixmap->height,
                      (int) (x - x_offset), (int)(y - y_offset), 1);
#       else
          XCopyPlane( display, gpixmap->pixmap, drawable,
                      gc, (int)x_offset, (int)y_offset,
                      (int)width, (int)height, (int)x, (int)y, 1);
#       endif
        } else if (function_index == X11_TRANSPARENT_COPY) {
          /* G2 no longer uses this case. 12/14/94 */
          g2ext_copy_pixmap_to_window(pixmap_index, window_index, (int)x_offset, (int)y_offset,
                                      (int)x, (int)y, (int)width, (int)height,
                                      0,0xFFFF,X11_AND);
          g2ext_copy_pixmap_to_window(pixmap_index, window_index, (int)x_offset, (int)y_offset,
                                       (int)x, (int)y, (int)width, (int)height,
                                       foreground_xcolor,0,X11_OR);
        }
      }
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

/* The following raster op uses the source bitmap as a mask for the
 * pattern.  This is used to draw in a foreground color but leave the
 * background color transparent.
 */
#define ROP_MASKPAT 0x00E20746        /* dest = (src & pat) | (!src & dst) */
#define ROP_XOR 0x006A01E9        /* ?? */

void g2ext_copy_pixmap_to_window(long pixmap_index, long window_index,
                                 long nSourceX, long nSourceY,
                                 long nDestX, long nDestY, long nWidth, long nHeight,
                                 long nFG, long nBG, long nFunction)
{
  HBITMAP hbm, hOldBitmap;
  HBRUSH  hbr = 0;
  HBRUSH  hOldBrush = 0;
  HWND hwndServer;
  LPG2INFO window_info;
  HDC hdc;
  int xoff, yoff;

  GTRACE(" g2ext_copy_pixmap_to_window: %d,%d %dx%d fg=%06x bg=%06x func=%d\n",
         nDestX, nDestY, nWidth, nHeight, nFG, nBG, nFunction);

  if (No_drawing)
    return;

  if(nFunction == X11_COPY) {
    g2ext_x11_draw_pixmap(pixmap_index, window_index, -1,
                          nSourceX, nSourceY, nWidth, nHeight, nDestX, nDestY, nFG, nBG);
    return;
  }

  hbm = ImageCluster_GetBitmap(pixmap_index, &xoff, &yoff, NULL, NULL);
  nSourceX += xoff;
  nSourceY += yoff;

  hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  window_info = GetlpG2Info(hwndServer);

  /* Get the bitmap into the memory DC. */
  if (hbm != NULL) {
    hdc = get_destination_hdc(window_info);

    /* Select bitmap into the memory DC */
    hOldBitmap = SelectObject(GhdcMem, hbm);

    switch (nFunction)
      {
      case X11_XOR:
        hbr = CreateSolidBrush(COLORVAL(nFG));
        hOldBrush= SelectObject(hdc, hbr);
        BitBlt(hdc, nDestX, nDestY, nWidth, nHeight,
               GhdcMem, nSourceX, nSourceY, ROP_XOR);
        break;

      case X11_STIPPLED:
        hbr = CreateSolidBrush(COLORVAL(nFG));
        hOldBrush = SelectObject(hdc, hbr);
        BitBlt(hdc, nDestX, nDestY, nWidth, nHeight,
               GhdcMem, nSourceX, nSourceY, draw_to_printer ? SRCCOPY : ROP_MASKPAT); /* HACK. */
        break;

      case X11_OR:
        printf("Unsupported function 0x%0x\n", nFunction);
        break;

      case X11_COPY:
      default:
        printf("Unknown function 0x%0x\n", nFunction);
        break;
      }

    /* Select bitmap OUT of the memory DC */
    SelectObject(GhdcMem, hOldBitmap);

    if (hbr) {
      SelectObject(hdc, hOldBrush);
      DeleteObject(hbr);
    }

    /* Select offscreen bitmap (if any) out of its DC */
    free_destination_hdc(window_info,hdc);
  }
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_copy_polychrome_pixmap_to_window(pixmap_index, window_index,
 *   x_offset, y_offset, x, y, width, height, function_index)
 *
 *   Description:
 *     Copy a bitmap to the screen
 *   Input Arguments:
 *     pixmap_index
 *     x_offset, y_offset
 *     x, y
 *     width, heigh
 *     function_index
 *   Returns:
 *     return value: None
 *   Notes:
 *     Combine with g2ext_copy_pixmap_to_window?!
 *     -----
 *   Modifications:
 *    mhd, 11/20/01: added second arg; see g2ext_copy_pixmap_to_window
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_copy_polychrome_pixmap_to_window(pixmap_index, window_index, x_offset, y_offset,
                                      x, y, width, height, function_index)
     long pixmap_index, window_index, x_offset, y_offset, x, y, width, height, function_index;
{
    if (No_drawing)
        return;

#   if defined(XWINDOWS)
    {
        GensymXWindow *gwindow;
        PixmapStruct *gpixmap;
        GC gc;

        gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);

        /* gwindow = gpixmap->gensym_x_window_ptr; OBS.! -mhd, 11/20/01 */
        gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

        gc = get_gc(gwindow, 1, 0, (int)function_index);

        XSetPlaneMask(gwindow->display_ptr, gc, AllPlanes);
        /* temporary - move to get_gc, initialize when creating gc! */

        XCopyArea(gwindow->display_ptr, gpixmap->pixmap,
                  x11_get_destination_drawable(gwindow),
                  gc, (int)x_offset, (int)y_offset, (int)width,
                  (int)height, (int)x, (int)y);
    }
#endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_p_fill_clipped_polygon(pixmap_index, points, npoints, xcolor)
 *
 *   Description:
 *     Draws a filled polygon on given pixmap
 *   Input Arguments:
 *     pixmap_index
 *     points
 *     npoints
 *     xcolor
 *   Returns:
 *     return value: None
 *   Notes:
 *       Unused
 *     -----
 *   Modifications:
 *****************************************************************************/

/*???????????????????????????????????????????????????????????????????????????*/

#define MAXIMUM_POLYGON_POINTS 500


/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_p_fill_clipped_polygon (long pixmap_index,
                                   unsigned char *point_data, long point_count_long,
                                   long left_edge_long, long top_edge_long,
                                   long right_edge_long, long bottom_edge_long,
                                   long xcolor_long)
{
  int point_count = (int) point_count_long;
  XPoint polygon_points[MAXIMUM_POLYGON_POINTS];
  int left_edge = (int) left_edge_long;
  int top_edge = (int) top_edge_long;
  int right_edge = (int) right_edge_long;
  int bottom_edge = (int) bottom_edge_long;
  int xcolor = (int) xcolor_long;
  int i;
  int point_x;
  int point_y;
  PixmapStruct        *gpixmap;
  register Display *display;
  GC gc;
  XRectangle clip_rect[1];

  if (No_window)
    return;
  if (point_count > MAXIMUM_POLYGON_POINTS)
    return;

  gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer((int)pixmap_index);

  display = gpixmap->display_ptr;
  gc = gpixmap->gc;
  for (i=0 ;i<point_count ; i++) {
    /* Regarding the 8192, see LISP point-list-to-unsigned-point-list */
#define reconstruct_point(buffer,idx) \
    (((int)buffer[idx] + (int)(buffer[idx+1] << NBITS_IN_BYTE)) - 8192)

      point_x = reconstruct_point(point_data,4*i);
    point_y = reconstruct_point(point_data,4*i+2);
    polygon_points[i].x = point_x;
    polygon_points[i].y = point_y;

#undef reconstruct_point
  }
  clip_rect[0].x = (short)left_edge;
  clip_rect[0].y = (short)top_edge;
  clip_rect[0].width = (unsigned short)(right_edge - left_edge);
  clip_rect[0].height = (unsigned short)(bottom_edge - top_edge);

  /* clip_rect is unused! -fmw, 1/11/02 */

  x11_ensure_pixmap_color(gpixmap, xcolor);
  XFillPolygon(display, gpixmap->pixmap, gc,
               polygon_points,
               point_count, Complex, CoordModeOrigin);
}

#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_p_fill_clipped_polygon(long pixmap_index,
                                  unsigned char *point_data, long point_count_long,
                                  long left_edge_long, long top_edge_long,
                                  long right_edge_long, long bottom_edge_long,
                                  long nColor)
{
  HDC hdc;
  int point_count = (int) point_count_long;
  POINT Polygon_points[MAXIMUM_POLYGON_POINTS];
  HBRUSH hOldBrush;
  HPEN hOldPen;
  int i;

  GTRACE(" g2ext_p_fill_clipped_polygon\n");

  if (point_count > MAXIMUM_POLYGON_POINTS)
    return;

  hdc = get_pixmap_hdc(pixmap_index, &nColor);
  if(hdc == NULL)
    return;

  for (i=0 ;i<point_count ; i++) {
    /* Regarding the 8192, see LISP point-list-to-unsigned-point-list */
#define reconstruct_point(buffer,idx) \
      (((int)buffer[idx] + (int)(buffer[idx+1] << NBITS_IN_BYTE)) - 8192)

      Polygon_points[i].x = reconstruct_point(point_data,4*i);
      Polygon_points[i].y = reconstruct_point(point_data,4*i+2);
#undef reconstruct_point
    }

  hOldBrush = select_brush(hdc, nColor);
  hOldPen = SelectObject(hdc, GetStockObject(NULL_PEN));
  /* SetROP2(hdc, R2_COPYPEN); */

  /* Draw the polygon. */
  Polygon(hdc, (LPPOINT)&(Polygon_points[0]), point_count);

  SelectObject (hdc, hOldPen);
  DeleteObject(SelectObject(hdc, hOldBrush));
  free_pixmap_hdc(hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Window Graphics Functions
 %
 % Description:
 %   These functions perform graphical operations in the onscreen app window
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
 * void g2ext_w_draw_line_with_clipping (window_index, x1, y1, x2, y2,
 *                                 left_edge, top_edge, right_edge, bottom_edge
 *                                 xcolor, function_index)
 *
 *   Description:
 *     Draws a line on a window
 *   Input Arguments:
 *     window_index
 *     x1, y1, x2, y2
 *     left_edge, top_edge
 *     right_edge, bottom_edge
 *     xcolor
 *     function_index
 *   Returns:
 *     return value: None
 *   Notes:
 *       End point is modified by the XWindows capping style (include last
 *     point, draw up to but not include, wrap around, etc)
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_w_draw_line_with_clipping (window_index, x1, y1, x2, y2,
                                left_edge, top_edge, right_edge, bottom_edge,
                                xcolor, function_index)
     long window_index, x1, y1, x2, y2,
     left_edge, top_edge, right_edge, bottom_edge,
     xcolor, function_index;
{
    GensymXWindow *gwindow;
    GC gc;
    XRectangle clip_rect[1];

    if (No_window || No_drawing)
        return;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
    gc = get_gc( gwindow, xcolor, 0, function_index );

#   ifdef CLIP_FOR_DRAWING
        XSetClipMask(gwindow->display_ptr, gc, None);
#   endif

    clip_rect[0].x = (short)left_edge;
    clip_rect[0].y = (short)top_edge;
    clip_rect[0].width = (unsigned short)(right_edge - left_edge);
    clip_rect[0].height = (unsigned short)(bottom_edge - top_edge);
    XSetClipRectangles(gwindow->display_ptr, gc, 0, 0, clip_rect, 1, Unsorted);

    /* XSetClipOrigin(gwindow->display_ptr, gc, left_edge, top_edge); */

    XDrawLine(gwindow->display_ptr, x11_get_destination_drawable(gwindow),
              gc,
              (int)x1, (int)y1, (int)x2, (int)y2);

    XSetClipMask(gwindow->display_ptr, gc, None);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_w_draw_line_with_clipping(long window_index,
                                     long nX1, long nY1, long nX2, long nY2,
                                     long nClipX1, long nClipY1,
                                     long nClipX2, long nClipY2,
                                     long nColor, long function_index)
{
  HWND hwnd;
  LPG2INFO info;
  HDCSTATE hs;

  GTRACE(" g2ext_w_draw_line_with_clipping(line=%d %d %d %d, clip=%d %d %d %d clr=0x%0x f=%d\n",
          nX1, nY1, nX2, nY2,
          nClipX1, nClipY1, nClipX2, nClipY2, nColor, function_index);

  if (No_drawing)
    return;

  hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  if (!IsWindow(hwnd)) return;
  info = GetlpG2Info(hwnd);

  hdc_push(info, &hs, nClipX1, nClipY1, nClipX2, nClipY2, nColor, 1,
           TRANSPARENT_COLOR_VALUE, function_index);

  MoveToEx(hs.hdc, nX1, nY1, NULL);
  LineTo(hs.hdc, nX2, nY2);

  hdc_pop(info, &hs);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/






/*****************************************************************************
 * void g2ext_w_fill_rect(window_index, x, y, width, height, xcolor, function_index)
 *
 *   Description:
 *     Draws a filled rectangle on the window
 *   Input Arguments:
 *     window_index
 *     x, y
 *     width, height
 *     xcolor
 *     function_index
 *   Returns:
 *     return value: None
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_w_fill_rect(window_index, x, y, width, height, xcolor, function_index)
     long window_index, x, y, width, height,  xcolor, function_index;
{
    GensymXWindow *gwindow;
    Display *display;
    GC gc;
#   ifdef CLIP_FOR_DRAWING
        XRectangle clip_rect[1];
#   endif

    if (No_window || No_drawing)
        return;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;
    gc = get_gc(gwindow, xcolor, 0, function_index);

    /* The CLIP_FOR_DRAWING 2.0 Beta X11 has problems with clip-and-copy plane */
#   ifdef CLIP_FOR_DRAWING
        clip_rect[0].x = (short)x;
        clip_rect[0].y = (short)y;
        clip_rect[0].width = (unsigned short)width;
        clip_rect[0].height = (unsigned short)height;
        XSetClipRectangles(display, gc, 0, 0, clip_rect, 1, Unsorted);
#   endif

    XFillRectangle(display, x11_get_destination_drawable(gwindow),
                   gc, (int)x, (int)y,
                   (int)width, (int)height);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_w_fill_rect(window_index, nX, nY, nWidth, nHeight, nColor, nFunction)
long window_index;
long nX, nY, nWidth, nHeight, nColor, nFunction;
{
  HBRUSH hbr, hOldBrush;
  HWND   hwndServer;
  LPG2INFO window_info;
  HDC hdc;

  GTRACE(" g2ext_w_fill_rect: %x %d,%d %dx%d color %06x func:%x\n",
         draw_to_window ? WindowFromDC(draw_to_window->hdc) :
         (HWND) g2ext_map_g2pointer_to_cpointer(window_index),
         nX, nY, nWidth, nHeight, nColor, nFunction);

  if (No_drawing)
    return;

  hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  window_info = GetlpG2Info(hwndServer);
  hdc = get_destination_hdc(window_info);

  hbr = CreateSolidBrush(COLORVAL(nColor));

  if(nFunction == X11_XOR) {
    hOldBrush = SelectObject(hdc, hbr);
    PatBlt(hdc, nX, nY, nWidth, nHeight, (nFunction == X11_XOR) ? PATINVERT : PATCOPY);
    SelectObject(hdc, hOldBrush);
  } else {
    RECT r;
    r.left = nX;
    r.top = nY;
    r.right = nX + nWidth;
    r.bottom = nY + nHeight;
    FillRect(hdc, &r, hbr);
  }

  if (hbr)
    DeleteObject(hbr);
  free_destination_hdc(window_info,hdc);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/




/*
 * Polygon Drawing
 */

#ifdef XWINDOWS

void g2ext_w_draw_polygon(long window_index,
                          long left, long top, long right, long bottom,        /* Clip rgn */
                          long line_color, long line_width,           /* GC */
                          long fill_color, long fill_pat, long nFunc, /* GC */
                          short *points, long npoints)                      /* Data */
{
  GensymXWindow *gwindow;
  Display *display;
  Drawable drawable;
  XPoint *xpoints = (XPoint*)points;
  GC gc;

  if (No_window || No_drawing)
    return;

  gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
  display = gwindow->display_ptr;
  drawable = x11_get_destination_drawable(gwindow);

  if(fill_color != TRANSPARENT_COLOR_VALUE) {
    gc = gc_push(gwindow, left, top, right, bottom, line_width, fill_color, nFunc);
    XFillPolygon(display, drawable, gc, (XPoint*)points, (int)npoints, Complex, CoordModeOrigin);
    gc_pop(gwindow, gc);
  }

  if(line_color != TRANSPARENT_COLOR_VALUE) {
    gc = gc_push(gwindow, left, top, right, bottom, line_width, line_color, nFunc);
    XDrawLines(display, drawable, gc, (XPoint*)points, (int)npoints, CoordModeOrigin);
    gc_pop(gwindow, gc);
  }

}
#endif

#ifdef MSWINDOWS
void g2ext_w_draw_polygon(long window_index,
                          long left, long top, long right, long bottom,        /* Clip rgn */
                          long line_color, long line_width,           /* GC */
                          long fill_color, long fill_pat, long nFunc, /* GC */
                          short *points, long npoints)                      /* Data */
{
  HWND hwnd;
  LPG2INFO info;
  HDCSTATE hs;
  POINT *wpoints = (POINT *)points;

  if (No_drawing)
    return;

  hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  if (!IsWindow(hwnd)) return;
  info = GetlpG2Info(hwnd);

  hdc_push(info, &hs, left, top, right, bottom, line_color, line_width, fill_color, nFunc);
  Polygon(hs.hdc, wpoints, npoints);
  hdc_pop(info, &hs);
}
#endif




/*
 * Circle/Ellipse drawing
 */

#if defined(XWINDOWS)

void g2ext_w_draw_ellipse(long window_index,
                          long left, long top, long right, long bottom, /* Clip rgn */
                          long line_color, long line_width,                /* GC */
                          long fill_color, long fill_pat, long nFunc,        /* GC */
                          long x1, long y1, long x2, long y2)                /* Bounding rect */
{
  GensymXWindow *gwindow;
  Display *display;
  Drawable drawable;
  GC gc;

  if (No_window || No_drawing)
    return;

  gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
  drawable = x11_get_destination_drawable(gwindow);
  display = gwindow->display_ptr;

  if(fill_color != TRANSPARENT_COLOR_VALUE) {
    gc = gc_push(gwindow, left, top, right, bottom, line_width, fill_color, nFunc);
    XFillArc(display, drawable, gc, x1, y1, x2-x1, y2-y1, 0, 360*64);
    gc_pop(gwindow, gc);
  }

  if(line_color != TRANSPARENT_COLOR_VALUE) {
    gc = gc_push(gwindow, left, top, right, bottom, line_width, line_color, nFunc);
    XDrawArc(display, drawable, gc, x1, y1, x2-x1, y2-y1, 0, 360*64);
    gc_pop(gwindow, gc);
  }
}

#endif

#if defined(MSWINDOWS)

void g2ext_w_draw_ellipse(long window_index,
                          long left, long top, long right, long bottom, /* Clip rgn */
                          long line_color, long line_width,                /* GC */
                          long fill_color, long fill_pat, long nFunc,        /* GC */
                          long x1, long y1, long x2, long y2)                /* Bounding rect */
{
  LPG2INFO info;
  HWND hwnd;
  HDCSTATE hs;

  if (No_drawing)
    return;

  hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  if (!IsWindow(hwnd)) return;
  info = GetlpG2Info(hwnd);

  hdc_push(info, &hs, left, top, right, bottom, line_color, line_width, fill_color, nFunc);
  Ellipse(hs.hdc, x1, y1, x2, y2);
  hdc_pop(info, &hs);
}
#endif





/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_w_draw_tiles
 *
 *   Description:
 *     Fills rectangle on window with a tiled pixmap..
 *   Input Arguments:
 *     window_index, pixmap_index
 *     x, y
 *     left, top, width, height
 *   Returns:
 *     return value: None
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
#if defined(XWINDOWS)
void g2ext_w_draw_tiles (long window_index, long pixmap_index,
                         long x, long y,
                         long left, long top, long width, long height,
                         long foreground, long background)
{
  GensymXWindow *gwindow;
  PixmapStruct *gpixmap;
  Display *display;
  Drawable drawable;
  Pixmap pixmap;
  XGCValues gcv;
  long gcmask;
  GC gc;

  if (No_window || No_drawing) return;

  gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
  display = gwindow->display_ptr;
  drawable = x11_get_destination_drawable(gwindow);

  gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
  pixmap = gpixmap->pixmap;

  gcmask = GCForeground | GCBackground | GCFillStyle |
    GCTileStipXOrigin | GCTileStipYOrigin | GCFunction;
  gcv.foreground  = foreground;
  gcv.background  = background;
  gcv.ts_x_origin = x;
  gcv.ts_y_origin = y;
  gcv.function    = GXcopy;
  if(gpixmap->depth <= 1) {
    gcv.stipple     = pixmap;
    gcv.fill_style  = FillOpaqueStippled;
    gcmask |= GCStipple;
  } else {
    gcv.tile        = pixmap;
    gcv.fill_style  = FillTiled;
    gcmask |= GCTile;
  }
  gc = XCreateGC(display, drawable, gcmask, &gcv);

  XFillRectangle(display, drawable, gc, (int)left, (int)top, (int)width, (int)height);
  XFreeGC(display,gc);
}
#endif


#if defined(MSWINDOWS)
void g2ext_w_draw_tiles (long window_index, long pixmap_index,
                         long x, long y,
                         long left, long top, long width, long height,
                         long foreground, long background)
{
  HWND hwnd, hwndDraw;
  LPG2INFO window_info;
  HDC hdc;
  HBRUSH hbr, hOldBrush;
  POINT oldOrg;
  COLORREF oldBK, oldTX;

  GTRACE(" g2ext_w_draw_tiles\n");

  if (No_drawing) return;

  hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  if(!IsWindow(hwnd)) return;
  window_info = GetlpG2Info(hwnd);

  hbr = ImageCluster_CreatePatternBrush(pixmap_index);
  if (hbr != NULL) {
    hdc = get_destination_hdc(window_info);

    if((hwndDraw = WindowFromDC(hdc)) != hwnd) { /* Adjust brush origin. */
      POINT p = {x, y};
      MapWindowPoints(hwnd, hwndDraw, &p, 1);
      x = p.x;
      y = p.y;
    }

    SetBrushOrgEx(hdc, (int)x, (int)y, &oldOrg);
    hOldBrush = SelectObject(hdc,hbr);

    /* Surprisingly, Windows draws "1" bits in the bk color, so this is correct. */
    oldBK = SetBkColor(hdc, foreground);
    oldTX = SetTextColor(hdc, background);
    PatBlt(hdc, left, top, width, height, PATCOPY);
    SetTextColor(hdc, oldTX);
    SetBkColor(hdc, oldBK);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hbr);
    SetBrushOrgEx(hdc, (int)oldOrg.x, (int)oldOrg.y, NULL);

    free_destination_hdc(window_info,hdc);
  }
}
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Image Functions
 %
 % Description:
 %   These functions perform image (gif, xbm) operations
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
 * int g2ext_free_extended_colors (window_index)
 *
 *   Description:
 *     Free all of the pixels allocated for extended colors
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return value: 0
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

int g2ext_free_extended_colors (window_index)
     int window_index;
{
    GensymXWindow *gwindow;
    Display *display;
    Colormap colormap;
    unsigned char *color_flags;
    unsigned long pixels[MAX_COLORS];
    int i,n;

    if (No_window || (screen_depth_global > DEPTH_EIGHT))
        return 1;

    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;

    colormap = gwindow->colormap;
    color_flags = gwindow->color_flags;

    /* Collect an array of just the extended colors. */
    n = 0;
    for(i=0; i<MAX_COLORS; i++)
        if (color_flags[i] == COLOR_EXTENDED) {
            pixels[n++] = i;
            color_flags[i] = COLOR_FREE;
        }

    /* If not a private color map, we have to actually free the pixels. */
    if (!Private_colormap_p)
        XFreeColors(display, colormap, pixels, n, 0);

    return 0;
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

int g2ext_free_extended_colors (window_index)
     long window_index;
{
    HWND hwndServer;
    LPG2INFO window_info;
    HDC hdc;

    GTRACE(" g2ext_free_extended_colors\n");

    hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
    window_info = GetlpG2Info(hwndServer);
    hdc = window_info->hdc;

    if (!IsWindow(hwndServer))
        return 1;

    /*   Resize the palette down to what it was before we
     *  allocated the first extended color.
     */
    if (iNumColors > iNumStandardColors)
    {
        if (ResizePalette(GensymPalette, iNumStandardColors))
        {
            /* From the "Logical Palettes" section of the WIN32 manual,
             * and I quote:
             *   In some cases, the application may need to deselect,
             *   unrealize, select, and realize the logical palette to
             *   ensure that the colors are updated exactly as requested.
             */
            UnrealizeObject(GensymPalette);
            SelectPalette(hdc, GensymPalette, FALSE);
            RealizePalette(hdc);

            iNumColors = iNumStandardColors;
        }
    }
    return(0);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void fill_in_pixmap_for_win95 (width, height, bminfo, DibData, hbm)
 *
 *   Description:
 *
 *   Input Arguments:
 *
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(MSWINDOWS)
static void fill_in_pixmap_for_win95 (width, height, bminfo, DibData, hbm)
    UINT          width, height;              /* Size of source image. */
    LPBITMAPINFO  bminfo;
    CONST BYTE   *DibData;
    HBITMAP          hbm;
{
    HBITMAP            hDdbTmp, hOldBM1;
    HDC                hdcTmp;

    /* SetDIBits(Ghdc, hbm, 0, height, DibData, bminfo, DIB_RGB_COLORS); */

    /* Create a temporary bitmap */
    hDdbTmp = CreateDIBitmap(Ghdc, &(bminfo->bmiHeader), CBM_INIT, DibData,
                             bminfo, DIB_RGB_COLORS);

    if (hDdbTmp) {
        hOldBM1 = SelectObject(GhdcMem, hbm);
        hdcTmp = CreateCompatibleDC(Ghdc);
        SelectObject(hdcTmp, hDdbTmp);
        BitBlt(GhdcMem, 0, 0, width, height, hdcTmp, 0, 0, SRCCOPY);
        SelectObject(hdcTmp, NULL);
        DeleteDC(hdcTmp);
        DeleteObject(hDdbTmp);
        SelectObject(GhdcMem, hOldBM1);
    }
}

#endif /* MSWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * void x11_put_bitmap (dest_x, dest_y, width, height, depth, gc_function,
 *                      bytes_per_scan_line, data, hbm)
 *
 *   Description:
 *
 *   Input Arguments:
 *
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(MSWINDOWS)
static void x11_put_bitmap(int dest_x, int dest_y,
                           int width, int height,
                           int depth, int gc_function,
                           int bytes_per_scan_line,
                           unsigned char *data, /* Pixels in ZPixmap format. */
                           HBITMAP hbm)
{
    HBITMAP	hbmSrc, hOldBM1, hOldBM2;
    HDC         hdcSrc;
    DWORD       dwRop;
    long        buflen;

    /* Select the target bitmap into memory */
    hOldBM1 = SelectObject(GhdcMem, hbm);

    /* (depth == 1) = XBM image (black & white image). Set Raster
     * Op code based on input parameter.
     */
    if (gc_function == 1)
        dwRop = SRCCOPY;  /* equiv of X windows GXcopy */
    else
        dwRop = 0x00220326; /* equiv of X windows GXandInvert */


    /* It seems that the bit ordering of XBM images is reversed
     * in X windows, so we must reverse bit order.
     */
    for(buflen = bytes_per_scan_line*height; buflen > 0; buflen--)
        data[buflen-1] = (unsigned char) g2ext_reverse_bits_in_byte((long) data[buflen-1]);

    /* create another memory DC in which to create the source bitmap. */
    hdcSrc = CreateCompatibleDC(Ghdc);

    /* Create the source bitmap from the given data buffer and
     * move it into memory.
     * Requires WORD alignment of each scan-line.
     */
    hbmSrc = CreateBitmap(width, height, 1, depth, data);
    hOldBM2 = SelectObject(hdcSrc, hbmSrc);

    /* Combine the source and dest bitmaps, leaving result in dest */
    BitBlt(GhdcMem, dest_x, dest_y, width, height, hdcSrc, 0, 0, dwRop);

    /* Get our bitmaps OUT of their respective memory DC's */
    SelectObject(hdcSrc, hOldBM2);
    SelectObject(GhdcMem, hOldBM1);

    if (hdcSrc)  DeleteDC(hdcSrc);
    if (hbmSrc)  DeleteObject(hbmSrc);
}
#endif /* MSWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/



/*****************************************************************************
 * void x11_put_8_bit_pixmap(width, height, bytes_per_scan_line, hbm, data)
 *
 *   Description:
 *
 *   Input Arguments:
 *
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(MSWINDOWS)
static void x11_put_8_bit_pixmap(width, height, bytes_per_scan_line, hbm, data)
    long width, height;              /* Size of source image. */
    long bytes_per_scan_line;              /* Bytes per scan line. */
    HBITMAP hbm;
    unsigned char *data;
{
    BITMAPINFO    *bminfo;
    WORD          *pw, x;
    unsigned char *DibData;

    bminfo = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) +
                                  (sizeof(WORD) * iNumColors));

    bminfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bminfo->bmiHeader.biWidth = width;
    bminfo->bmiHeader.biPlanes = 1;
    bminfo->bmiHeader.biBitCount = NBITS_IN_BYTE;
    bminfo->bmiHeader.biCompression = BI_RGB;
    bminfo->bmiHeader.biClrUsed = iNumColors;
    bminfo->bmiHeader.biClrImportant = 0;

    bminfo->bmiHeader.biHeight = -height;
    DibData = data;

    pw = (WORD *) bminfo->bmiColors;
    for(x=0; x < iNumColors; x++)
        *pw++ = (WORD)x;

    /* Requires DWORD alignment of each scan-line. */
    x = SetDIBits(Ghdc, hbm, 0, height, DibData, bminfo, DIB_PAL_COLORS);

    free(bminfo);
}

#endif /* MSWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * void x11_put_truecolor_pixmap(width, height, bytes_per_scan_line, hbm, data)
 *
 *   Description:
 *
 *   Input Arguments:
 *
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(MSWINDOWS)
void x11_put_truecolor_pixmap(long width, long height, /* Size of source image. */
                              long bytes_per_scan_line,
                              HBITMAP hbm,
                              unsigned char *data)
{
  BITMAPINFO bmi;

  ZeroMemory(&bmi, sizeof(BITMAPINFO));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = bytes_per_scan_line / 3;
  bmi.bmiHeader.biHeight = -height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biClrUsed = 0;
  bmi.bmiHeader.biClrImportant = 0;

  SetDIBits(Ghdc, hbm, 0, height, data, &bmi, DIB_RGB_COLORS);
}
#endif /* MSWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * void g2ext_x11_put_image (pixmap_index, dest_x, dest_y, width, height, depth,
 *                     gc_function, bytes_per_scan_line, data)
 *
 *   Description:
 *     paint image data onto an X pixmap
 *   Input Arguments:
 *     pixmap_index     The index of the X pixmap
 *     dest_x           Destination coor in pixmap
 *     dest_y           Destination coor in pixmap
 *     width            Size of source image data, in pixels.
 *     height           Size of source image data, in pixels.
 *     depth            Will be either 1, 8, or 24 (bits)
 *     gc_function      1 to draw, 0 to burn. Burning is only for 1bit images.
 *     bytes_per_scan_line   Number of bytes per scan line. May differ from
 *                      width for alignment.
 *     data             Pixels in ZPixmap format.
 *   Returns:
 *     return value:
 *   Notes:
 *       This routine is used by the new background images facility in G2 to
 *     paint image data, in the form of a buffer full of pixel values, onto an
 *     X pixmap. The pixmap is then what G2 finally bitblts to the screen, using
 *     another routine.
 *
 *       The depth of the image data must match the depth of the pixmap.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

#include <X11/Xlibint.h>

static XImage *GCreateImage (
                      register Display *dpy,
                      register Visual *visual,
                      unsigned int depth,
                      int format,
                      int offset, /*How many pixels from the start of the data does the
                                   picture to be transmitted start?*/
                      
                      char *data,
                      unsigned int width,
                      unsigned int height,
                      int xpad,
                      int image_bytes_per_line)
{
    register XImage *image;
    int bits_per_pixel = 1;
    int min_bytes_per_line;
    
    if (depth == 0 || depth > 32 ||
        (format != XYBitmap && format != XYPixmap && format != ZPixmap) ||
        (format == XYBitmap && depth != 1) ||
        (xpad != 8 && xpad != 16 && xpad != 32) ||
        offset < 0)
        return (XImage *) NULL;
    if ((image = (XImage *) Xcalloc(1, (unsigned) sizeof(XImage))) == NULL)
        return (XImage *) NULL;
    
    image->width = width;
    image->height = height;
    image->format = format;
    image->byte_order = dpy->byte_order;
    image->bitmap_unit = dpy->bitmap_unit;
    image->bitmap_bit_order = dpy->bitmap_bit_order;
    if (visual != NULL) {
        image->red_mask = visual->red_mask;
        image->green_mask = visual->green_mask;
        image->blue_mask = visual->blue_mask;
    }
    else {
        image->red_mask = image->green_mask = image->blue_mask = 0;
    }
    if (format == ZPixmap)
    {
        /* GENSYMCID-606: Linux Enterprise: background images are showing up as black squares.
           necessary for 24 bits/pixel, but this is hacked by original Gensym developers.
           -- Chun Tian (binghe), Jan 30, 2012 */
        bits_per_pixel = depth; /* _XGetBitsPerPixel(dpy, (int) depth); */
    }
    
    image->xoffset = offset;
    image->bitmap_pad = xpad;
    image->depth = depth;
    image->data = data;
    image->bits_per_pixel = bits_per_pixel;
    image->obdata = NULL;

    /* Cannot use _XInitImagePtrs here */
    XInitImage (image);
    
    return image;
}

void g2ext_x11_put_image (pixmap_index, dest_x, dest_y, width, height, image_depth,
                    gc_function, bytes_per_scan_line, data)
     long pixmap_index, dest_x, dest_y, width, height, image_depth;
     long gc_function, bytes_per_scan_line;
     unsigned char *data;
{
    PixmapStruct *gpixmap;
    Display *display;
    int screen;
    Pixmap pixmap;
    XImage *image;
    Visual *visual;
    GC gc;
    XGCValues gcvalues;
    long x11_depth;
    static XImage ximage;

    if (No_window)
        return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);

    display = gpixmap->display_ptr;
    pixmap = gpixmap->pixmap;

    if(gc_function == 1)
        gcvalues.function = GXcopy;
    else
        gcvalues.function = GXandInverted;

    if (image_depth == 1) {
        /* Code copied from XCreateBitmapFromData(), in XCrBFData.c  */
        ximage.width = width;
        ximage.height = height;
        ximage.xoffset = 0;
        ximage.format = ZPixmap;
        ximage.data = (char *)data;
        ximage.byte_order = LSBFirst;
        ximage.bitmap_unit = LISP_SCANLINE;
        ximage.bitmap_bit_order = LSBFirst;
        ximage.bitmap_pad = LISP_BITMAP_PAD;
        ximage.depth = 1;
        ximage.bytes_per_line = bytes_per_scan_line;
        /* The HP required this field in addition to depth! */
        ximage.bits_per_pixel = 1;
        ximage.red_mask = 1;
        ximage.green_mask = 1;
        ximage.blue_mask = 1;

        gc = XCreateGC(display, pixmap, (unsigned long) GCFunction, &gcvalues);
        XPutImage(display, pixmap, gc, &ximage, 0, 0, (int)dest_x, (int)dest_y,
                  (int)width, (int)height);
        XFreeGC(display, gc);        /* Naughty */
    } else {
        screen = DefaultScreen(display);
        visual = DefaultVisual(display, screen);
        x11_depth = DefaultDepth(display, screen);
        image = GCreateImage(display, visual,
                             (unsigned int) (x11_depth < image_depth) ? x11_depth : image_depth,
                             ZPixmap, 0, (char *)data, (unsigned int)width,
                             (unsigned int)height,
                             LISP_BITMAP_PAD,
                             (int)bytes_per_scan_line);
        if (!image)
            return;

        gc = XCreateGC(display, pixmap, (unsigned long) GCFunction, &gcvalues);
        XPutImage(display, pixmap, gc, image, 0, 0, (int)dest_x, (int)dest_y,
                  (int)width, (int)height);
        XFreeGC(display, gc);        /* Naughty */
        image->data = NULL;        /* Don't free the data! */
        XDestroyImage(image);
    }
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_x11_put_image (pixmap_index, dest_x, dest_y, width, height,
                          image_depth, gc_function, bytes_per_scan_line, data)
long pixmap_index;                /* The pixmap onto which we draw. */
long dest_x, dest_y;                /* Destination coor in pixmap */
long width, height;                /* Size of source image. */
long image_depth;                /* Will be either 1, 8, or 24 bits. */
long gc_function;                /* 1 to draw, 0 to burn. Burning is only
                                    for 1bit images.*/
long bytes_per_scan_line;        /* Bytes per scan line. */
unsigned char *data;                /* Pixels in ZPixmap format. */
{
  HBITMAP hbm;
  int xoff, yoff;

  /* Alignment requirements for Windows:
   * CreateBitmap() requires WORD (16bit) alignment of each scan-line.
   * SetDIBits() requires DWORD (32bit) alignment of each scan-line.
   *
   * The LISP code arranges for word alignment when image_depth==1,
   * and dword alignment when image_depth==8.  The bytes_per_scan_line
   * passed in reflects this. -fmw, 2/22/95
   */

  GTRACE(" g2ext_x11_put_image %dx%dx%d to %d,%d\n", width, height, image_depth, dest_x, dest_y);

  hbm = ImageCluster_GetBitmap(pixmap_index, &xoff, &yoff, NULL, NULL);
  dest_x += xoff;
  dest_y += yoff;

  if (hbm == NULL)
    return;

  switch(image_depth) {
   case 8:
     x11_put_8_bit_pixmap(width, height, bytes_per_scan_line, hbm, data);
     break;
   case 1:
     x11_put_bitmap(dest_x, dest_y, width, height, 1, gc_function, bytes_per_scan_line, data, hbm);
     break;
   case 24:
     x11_put_truecolor_pixmap(width, height, bytes_per_scan_line, hbm, data);
     break;
   default:
     printf("Internal error: cannot handle %d-bit deep pixmap\n", image_depth);
  }
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_stretch_bits
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)
void g2ext_stretch_bits(long window_index,
                        long xsrc, long ysrc, long srcWidth, long srcHeight, long srcDepth,
                        long xdst, long ydst, long dstWidth, long dstHeight,
                        long stride,
                        long fg, long bg,
                        unsigned char *data, long nbytes)
{
}
#endif
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)
void g2ext_stretch_bits(long window_index,
                        long xsrc, long ysrc, long srcWidth, long srcHeight, long srcDepth,
                        long xdst, long ydst, long dstWidth, long dstHeight,
                        long stride,
                        RGBQUAD *colormap, long ncolors,
                        unsigned char *data, long nbytes)
{
  HWND hwnd;
  LPG2INFO window_info;
  HDC hdc;
  BITMAPINFO *bmi;
  int i, rc;

  GTRACE(" g2ext_stretch_bits depth=%d ncolors=%d %dx%d stride=%d, nbytes=%d\n",
          srcDepth, ncolors, srcWidth, srcHeight, stride, nbytes);

  if (No_drawing)
    return;

  hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  window_info = GetlpG2Info(hwnd);
  hdc = get_destination_hdc(window_info);

  bmi = calloc(sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * ncolors, 1);
  bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi->bmiHeader.biWidth = stride;
  bmi->bmiHeader.biHeight = -srcHeight;
  bmi->bmiHeader.biPlanes = 1;
  bmi->bmiHeader.biBitCount = (WORD) srcDepth;
  bmi->bmiHeader.biCompression = BI_RGB;
  bmi->bmiHeader.biClrUsed = ncolors;
  bmi->bmiHeader.biClrImportant = 0;
  for(i=0; i<ncolors; i++)
    bmi->bmiColors[i] = colormap[i];

  if(srcDepth == 1)
    for(i=0; i<nbytes; i++)
      data[i] = (unsigned char) g2ext_reverse_bits_in_byte((long) data[i]);

  rc = StretchDIBits(hdc,
                     xdst, ydst, dstWidth, dstHeight,
                     xsrc, ysrc, srcWidth, srcHeight,
                     data,
                     bmi,
                     DIB_RGB_COLORS,
                     SRCCOPY);
  if(rc == GDI_ERROR)
    printf("Error: StretchDIBits failed.\n");
  free_destination_hdc(window_info,hdc);
  free(bmi);
}
#endif

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Text Functions
 %
 % Description:
 %   These functions perform text rendering functions
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
 * int g2ext_w_draw_string_with_clipping(window_index, x, y, left_edge, top_edge,
 *                                  right_edge, bottom_edge, xcolor,
 *                                  function_index, fontname, text, length)
 *
 *   Description:
 *     Draws text in fontname with its left edge and baseline at x and y,
 *     respectively
 *   Input Arguments:
 *     window_index
 *     x, y,
 *     left_edge, top_edge
 *     right_edge, bottom_edge
 *     xcolor
 *     function_index
 *     fontname
 *     text
 *     length
 *   Returns:
 *     return value: Negative on error, non-negative on success
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/

int g2ext_w_draw_string_with_clipping (gensym_x_window_index, x, y,
                                  left_edge, top_edge, right_edge, bottom_edge,
                                  xcolor, function_index,
                                  fontname, text, length)
     long gensym_x_window_index;
     long x, y, left_edge, top_edge, right_edge, bottom_edge;
     long xcolor, function_index;
     char *fontname;                /* fontname must be interned. */
     char *text;
     long length;
{
#if defined(MSWINDOWS)
  return 0;
#else /* XWindows */
    GensymXWindow *gwindow;
    Display *display;
    Drawable drawable;
    XFontStruct *font;
    Font fid;
    GC gc;
    XRectangle clip_rect[1];
    static Font last_fid;
    static char *last_fontname;

    if (No_window || No_drawing)
        return 0;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(gensym_x_window_index);
    display = gwindow->display_ptr;
    drawable = x11_get_destination_drawable(gwindow),

    gc = get_gc(gwindow, xcolor, 0, function_index);

#   ifdef CLIP_FOR_DRAWING
        XSetClipMask(gwindow->display_ptr, gc, None);
#   endif

    clip_rect[0].x = (short)left_edge;
    clip_rect[0].y = (short)top_edge;
    clip_rect[0].width = (unsigned short)(right_edge - left_edge);
    clip_rect[0].height = (unsigned short)(bottom_edge - top_edge);
    XSetClipRectangles(gwindow->display_ptr, gc, 0, 0, clip_rect, 1, Unsorted);

    if (fontname != last_fontname) {
        font = XLoadQueryFont(display,fontname);
        if (font == NULL)
            return(-1);
        fid = font->fid;

        last_fontname = fontname;
        last_fid= fid;

        XSetFont(display, gc, fid);
    }

    XDrawString(display, drawable, gc, (int)x, (int)y, text, (int)length);
    XSetClipMask(gwindow->display_ptr, gc, None);

    return 0;
#endif /* XWindows */
}
/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/


/*****************************************************************************
 * int g2ext_draw_string_in_font_with_clipping (gensym_x_window_index, x, y,
 *                                        left_edge, top_edge, right_edge,
 *                                        bottom_edge, xcolor, function_index,
 *                                        gensym_font_index, text,  length)
 *
 *   Description:
 *     Draws text in fontname with its left edge and baseline at x and y,
 *     respectively
 *   Input Arguments:
 *     window_index
 *     x, y,
 *     left_edge, top_edge
 *     right_edge, bottom_edge
 *     xcolor
 *     function_index
 *     gensym_font_index
 *     text
 *     length
 *   Returns:
 *     return value: Negative on error, non-negative on success
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/

int g2ext_draw_string_in_font_with_clipping (gensym_x_window_index, x, y, left_edge,
                                       top_edge, right_edge, bottom_edge,
                                       xcolor, function_index,
                                       gensym_font_index, text, length)
     long gensym_x_window_index;
     long x, y, left_edge, top_edge, right_edge, bottom_edge;
     long xcolor, function_index;
     long gensym_font_index;
     char *text;
     long length;
{
#if defined(MSWINDOWS)
  return 0;
#else /* XWindows */
    GensymXWindow *gwindow;
    Display *display;
    Drawable drawable;
    XFontStruct *font;
    Font fid;
    GC gc;
    XRectangle clip_rect[1];
    static Font last_fid;

    if (No_window || No_drawing)
        return 0;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(gensym_x_window_index);
    display = gwindow->display_ptr;
    drawable = x11_get_destination_drawable(gwindow),

    gc = get_gc(gwindow, xcolor, 0, function_index);

#   ifdef CLIP_FOR_DRAWING
        XSetClipMask(gwindow->display_ptr, gc, None);
#   endif

    clip_rect[0].x = (short)left_edge;
    clip_rect[0].y = (short)top_edge;
    clip_rect[0].width = (unsigned short)(right_edge - left_edge);
    clip_rect[0].height = (unsigned short)(bottom_edge - top_edge);
    XSetClipRectangles(gwindow->display_ptr, gc, 0, 0, clip_rect, 1, Unsorted);

    font = (XFontStruct *)g2ext_map_g2pointer_to_cpointer(gensym_font_index);
    fid = font->fid;
    if (fid != last_fid) {
        last_fid= fid;
        XSetFont(display, gc, fid);
    }

    XDrawString(display, drawable, gc, (int)x, (int)y, text, (int)length);
    XSetClipMask(gwindow->display_ptr, gc, None);
    return 1;
#endif /* XWindows */
}
/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/


/*****************************************************************************
 * int g2ext_draw_string_in_font(gensym_x_window_index, x, y,
 *                         xcolor, function_index,
 *                         gensym_font_index, text, length)
 *
 *   Description:
 *     Draws text in fontname with its left edge and baseline at x and y,
 *     respectively
 *   Input Arguments:
 *     window_index
 *     x, y,
 *     xcolor
 *     function_index
 *     gensym_font_index
 *     text
 *     length
 *   Returns:
 *     return value: Negative on error, non-negative on success
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/

int g2ext_draw_string_in_font (gensym_x_window_index, x, y, xcolor, function_index,
                         gensym_font_index, text, length)
     long gensym_x_window_index;
     long x, y;
     long xcolor, function_index;
     long gensym_font_index;
     char *text;
     long length;
{
#if defined(MSWINDOWS)
  return 0;
#else /* XWindows */
    GensymXWindow *gwindow;
    Display *display;
    Drawable drawable;
    XFontStruct *font;
    Font fid;
    GC gc;
    static Font last_fid;

    if (No_window || No_drawing)
        return 0;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(gensym_x_window_index);
    display = gwindow->display_ptr;
    drawable = x11_get_destination_drawable(gwindow),

    gc = get_gc(gwindow, xcolor, 0, function_index);

    font = (XFontStruct *)g2ext_map_g2pointer_to_cpointer(gensym_font_index);
    fid = font->fid;
    if (fid != last_fid) {
        last_fid= fid;
        XSetFont(display, gc, fid);
    }

    XDrawString(display, drawable, gc, (int)x, (int)y, text, (int)length);

    return 1;
#endif /* XWindows */
}
/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/


/*****************************************************************************
 * int g2ext_allocate_x_font (gensym_x_window_index, fontname)
 *
 *   Description:
 *     Draws text in fontname with its left edge and baseline at x and y,
 *     respectively
 *   Input Arguments:
 *     window_index
 *     fontname
 *   Returns:
 *     return value: -1 for failure; a cached cpointer for success (nonnegative)
 *   Notes:
 *     This is the only one of the functions in this suite that should ever
 *     be executed on a non-XWINDOWS platforms, i.e., for MSWINDOWS.  The
 *     -1 return value should result in G2 not calling any of the other associated
 *     function.
 *   Modifications:
 *****************************************************************************/

/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/

int g2ext_allocate_x_font (gensym_x_window_index, fontname)
     long gensym_x_window_index;
     char *fontname;                /* fontname must be interned. */
{
#if defined(MSWINDOWS)
  return -1;
#else /* XWindows */
    GensymXWindow *gwindow;
    Display *display;
    Window window;
    XFontStruct *font;

    if (No_window)
        return -1;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(gensym_x_window_index);
    display = gwindow->display_ptr;
    window = gwindow->xwindow;

    font = XLoadQueryFont(display, fontname);
    if (font == NULL)
        return(-1);

    return(g2ext_cache_cpointer((long)font));
#endif /* XWindows */
}
/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/


/*****************************************************************************
 * int g2ext_get_character_set_width (character_code, gensym_font_index)
 *
 *   Description:
 *
 *   Input Arguments:
 *     character_code
 *     gensym_font_index
 *   Returns:
 *     return value:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*1111111111111111111111111111 Mixed ifdefs 111111111111111111111111111111111*/

int g2ext_get_character_set_width (character_code, gensym_font_index)
     int character_code, gensym_font_index;
{
#if defined(MSWINDOWS)
        return 0;
#else /* XWindows */
    XFontStruct *font;
    char str[1];

    if (No_window)
        return 0;

    font = (XFontStruct *)g2ext_map_g2pointer_to_cpointer(gensym_font_index);
    str[0] = (char)character_code;

    return XTextWidth(font, str, 1);
#endif /* XWindows */
}




/*****************************************************************************
 * long g2ext_w_draw_string()
 *
 *   Description:
 *     Native text drawing, used for native printing.
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
#if defined(XWINDOWS)
void g2ext_w_draw_string (long window_index,
                          long left, long top, long right, long bottom, /* Clip rect */
                          long x, long y,
                          long color, long pointSize, long angle, long font,
                          long xscale, long yscale, long word_spacing,
                          unsigned short *string, long len)
{}
#endif


#if defined(MSWINDOWS)

static int CALLBACK find_g2_font_1(LPLOGFONT lf, LPNEWTEXTMETRIC lpntm, DWORD FontType, long *result)
{
  if((FontType&TRUETYPE_FONTTYPE) != 0 &&
     lf->lfFaceName != NULL &&
     strcmp(lf->lfFaceName, FULL_UNICODE_FONT) == 0) {
    *result = 1;
    return 0;
  } else
    return 1;
}

/* Looks for a TrueType font named by G2_DESIRED_FONT */
static BOOL g2_font_installed_p(HDC hdc)
{
  int result = 0;
  EnumFontFamilies(hdc, FULL_UNICODE_FONT, (FONTENUMPROC)find_g2_font_1, (LPARAM)&result);
  return result;
}

HFONT g2pvt_get_unicode_font(HDC hdc, int pointSize, int angle, int flags)
{
  LOGFONT lf;
  HFONT hfont;
  static int once = 1;

  /* Just check once for font installed. */
  if(once) {
    once = 0;
    if(!g2_font_installed_p(hdc))
      printf("Warning: Cannot find full Unicode font \"%s\"\n", FULL_UNICODE_FONT);
  }

  ZeroMemory(&lf, sizeof(lf));
  strcpy(lf.lfFaceName, FULL_UNICODE_FONT);
  lf.lfHeight = -pointSize;
  if(pointSize == 72)                /* Hack for HB72, request max possible weight. */
    lf.lfWeight = 1000;
  lf.lfEscapement = angle;        /* Angle is already in tenths of a degree. */
  lf.lfOrientation = angle;
  lf.lfCharSet = SHIFTJIS_CHARSET; /* Needed on NT 4.0, I think. */
  hfont = CreateFontIndirect(&lf);
  if(hfont == NULL)
    printf("Error: can't find suitable font for native printing.\n");
  return hfont;
}

void g2ext_w_draw_string(long window_index,
                         long left, long top, long right, long bottom, /* Clip rect */
                         long x, long y,
                         long color, long pointSize,
                         long angle, /* In tenths of a degree. */
                         long flags, /* Bit-0 = reflect-left-right-p */
                         long xscale, long yscale,
                         long width, /* Exact width of string as drawn with G2's fonts. */
                         LPCWSTR string, long len)
{
  HWND hwnd;
  LPG2INFO window_info;
  HDC hdc;
  HFONT hfont, oldFont;
  RECT r;
  POINT p;
  SIZE size, oldExt;
  int i, n, reflect, oldColor, oldMode, oldAlign;
  const int unicode_line_separator = 8232; /* G2 sometimes leaves these at start of string. */

  GTRACE(" g2ext_draw_string(clip=%d,%d %d,%d xy=%d,%d color=0x%0x ang=%d scale=%d,%d,%d size=%d) \"%ls\"[%d]\n",
          left, top, right, bottom, x, y, color, angle,
          xscale, yscale, flags, pointSize, string, len);

  if (No_drawing)
    return;

  /* Strip line separators from beginning. */
  while(len>0 && string[0] == unicode_line_separator) {
    string++;
    len--;
  }
  if(len<=0)
    return;

  hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  window_info = GetlpG2Info(hwnd);
  hdc = get_destination_hdc(window_info);
  oldColor = SetTextColor(hdc, color);
  oldAlign = SetTextAlign(hdc, TA_BASELINE);
  oldMode = SetBkMode(hdc,TRANSPARENT);

  reflect = flags&1;

  /* Only GM_ADVANCED mode obeys reflection. */
  if(reflect) {
    SetGraphicsMode(hdc,GM_ADVANCED); /* Not available on Win 9x */
    xscale = -xscale;
  }
  p.x = x;                        /* Preserve logical coordinates around the scale change, */
  p.y = y;                        /* which we are doing just to get a scaled font. */
  r.left = left;
  r.top = top;
  r.right = right;
  r.bottom = bottom;
  LPtoDP(hdc, &p, 1);
  LPtoDP(hdc, (LPPOINT)&r, 2);
  ScaleViewportExtEx(hdc, xscale, 4096, yscale, 4096, &oldExt);
  DPtoLP(hdc, (LPPOINT)&r, 2);
  DPtoLP(hdc, &p, 1);

  /* TODO: Cache the hfont. */
  hfont = g2pvt_get_unicode_font(hdc, pointSize, angle, flags);
  if(hfont != NULL)
    oldFont = SelectObject(hdc,hfont);

  n=0;                                /* Compute number of spaces. */
  for(i=0; i<len; i++)
    if(string[i] == L' ')
      n++;

  /* Modify word spacing to match widths, if string contains spaces.
   * TODO: modify character spacings, too. */
  if(n>0) {
    SetTextJustification(hdc, 0, 0);
    GetTextExtentPoint32W(hdc, string, len, &size);
    if(width != size.cx) {
      SetTextJustification(hdc, width-size.cx, n);
    }
  }

  ExtTextOutW(hdc, p.x, p.y, ETO_CLIPPED, &r, string, len, NULL);

  SetTextJustification(hdc, 0, 0);
  if(hfont != NULL) {
    SelectObject(hdc,oldFont);
    DeleteObject(hfont);
  }
  SetViewportExtEx(hdc, oldExt.cx, oldExt.cy, NULL);
  SetBkMode(hdc,oldMode);
  SetTextAlign(hdc,oldAlign);
  SetTextColor(hdc,oldColor);
  if(reflect)
    SetGraphicsMode(hdc,GM_COMPATIBLE);
  free_destination_hdc(window_info, hdc);
}

#endif



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Miscellaneous Functions
 %
 % Description:
 %   Miscellaneous functions.
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * void g2ext_scroll_rectangle(window_index, source_left, source_top, width, height,
 *                       destination_left, destination_top)
 *
 *   Description:
 *     Moves one portion of the x window to another
 *   Input Arguments:
 *     window_index
 *     source_left, source_top
 *     width, height
 *     destination_left, destination_top
 *   Returns:
 *     return value: None
 *   Notes:
 *       Either the source or the destination may be obscured by other entities
 *     in the host window system.  The source and destination may overlap in
 *     any manner.  GraphicExpose events are generated for those portions of
 *     the destination that are visible in the window, but for which the
 *     corresponding portion of the source was obscured.  GraphicExpose events
 *     are not generated for those portions of the source that are that are
 *     both visible and which do not overlap the destination, i.e. those
 *     portions that were "vacated."
 *     -----
 *       In X this is implemented with one calls on XCopyArea, to do the bitblit.
 *     This calls may generate GraphicsExpose events as a side effect.
 *     -----
 *       Currently this is the only user of XCopyArea, Graphics Expose events
 *     and the scrolling_gc slot in GensymXWindow.
 *     -----
 *       When using this to implement scrolling in G2 it two or three significant
 *     problems arise upstream.  You must take care to shape the rectangles so
 *     that you don't slam image-planes that might be overlapping the one you are
 *     working in.  The rectangles that together make up the region you want to
 *     scroll must be copied in the approprate order to avoid destroying info
 *     in the source before you have used it to fill in the destination. Finally
 *     the vacated source must be infered and back filled.
 *     -----
 *       12/8/93, mpc:  The Petzold book, "Windows Programming 3.1" page 593
 *     gives hints and info on using the ScrollWindow() function. It warns that
 *     this function does not bother to check for overlapping child windows.
 *     Since we don't use any local window types we shouldn't worry. If this does
 *     start to act improperly we may want to check out ScrollDC().
 *     -----
 *       7/24/95, fmw:   Using ScrollDC() instead of ScrollWindow seems to fix
 *     HQ-385497, as well as reduce screen flashing.
 *     -----
 *     4/13/99, lgibson: Added code to fix bug HQ-2824437
 *     "Unnecessary refresh occurs when moving workspaces"
 *     on MS Windows. Instead of always refreshing the
 *     entire scrolled rectangle, selective updates of
 *     smaller regions are now done. Experiments show the
 *     best results come from ScrollDC when giving it NULL
 *     for the 3 possible update results, and then
 *     selectively refreshing any sections scrolled in from
 *     off-screen (off the desktop) or from underneath a
 *     topmost window (ScrollDC does not update these
 *     regions when sent NULL for its 3 update regions). If
 *     ScrollDC is given update arguments, other problems
 *     result, either not updating the normal unobscured
 *     area, or updating the entire rectangle
 *     unnecessarily.
 *
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_scroll_rectangle(window_index, source_left, source_top,
                            width, height, destination_left, destination_top)
     int window_index;
     int source_left, source_top;
     int width, height;
     int destination_left, destination_top;
{
    GensymXWindow *gwindow;
    Display *display;
    Window  xwindow;

    if (No_window || No_drawing)
        return;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;
    xwindow = gwindow->xwindow;

    /******
    * Copy exposed portions of source to destinations, generating
    * expose events for those portions of destination that couldn't
    * be filled because the source was obscured.
    ******/
    XCopyArea(display, xwindow, xwindow, gwindow->scrolling_gc,
              source_left, source_top,
              (unsigned int)width, (unsigned int)height,
              destination_left, destination_top);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_scroll_rectangle(window_index, source_left, source_top,
                            width, height, destination_left, destination_top)
     long window_index;
     int source_left, source_top;
     int width, height;
     int destination_left, destination_top;
{
    HWND hwndServer, hwndTest1, hwnd;
    LPG2INFO window_info;
    HMONITOR hMonitor;
    MONITORINFOEX mix;
    HDC hdc;
    RECT rectScroll; /* rect to scroll, in client coordinates */
    RECT rectTest, rectDesktop;
    RECT rectUpdateLeftOrRight; /* in client coordinates */
    RECT rectUpdateTopOrBottom; /* in client coordinates */
    RECT rectIntersect, rectIntersectNew;
    BOOL UpdateLeftOrRight = FALSE;
    BOOL UpdateTopOrBottom = FALSE;
    BOOL UpdateForTopmostWindow = FALSE;
    int  destination_right = destination_left + width;
    int  destination_bottom = destination_top + height;

    GTRACE(" g2ext_scroll_rectangle\n");

    if (No_drawing)
        return;

    hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
    window_info = GetlpG2Info(hwndServer);
    hdc = window_info->hdc;

    rectScroll.left = source_left;
    rectScroll.top  = source_top;
    rectScroll.right = source_left+width;
    rectScroll.bottom = source_top+height;

    mix.cbSize = sizeof(mix);
    hMonitor = MonitorFromWindow(hwndServer, MONITOR_DEFAULTTONEAREST);
    if (GetMonitorInfo(hMonitor, &mix) == 0) {
      GetWindowRect(GetDesktopWindow(), &rectDesktop);
    } else {
      rectDesktop.left = mix.rcMonitor.left;
      rectDesktop.right = mix.rcMonitor.right;
      rectDesktop.top = mix.rcMonitor.top;
      rectDesktop.bottom = mix.rcMonitor.bottom;
    }
    /* Map desktop into client coordinates relative to our window */
    MapWindowPoints (NULL, hwndServer, (LPPOINT)&rectDesktop, 2);

    /* Now get our true "desktop" by intersecting with the interior of all of
     * our parent windows. */
    for(hwnd=g2pvt_parent_window(hwndServer); hwnd!=NULL; hwnd=g2pvt_parent_window(hwnd)) {
      GetClientRect(hwnd, &rectTest);
      MapWindowPoints(hwnd, hwndServer, (LPPOINT)&rectTest, 2);
      IntersectRect(&rectDesktop, &rectDesktop, &rectTest);
    }

    /* If dragging out from under a window that is on top */
    /* of us (e.g. a topmost window), must do special */
    /* update.  Algo: get rect of topmost window, intersect */
    /* with moving workspace, compute new location of */
    /* intersection, update that. */

    /* Get the windows higher than us in the Z order */
    for(hwnd = hwndServer; hwnd!=NULL; hwnd = g2pvt_parent_window(hwnd)) {
      hwndTest1 = hwnd;
      while (hwndTest1 = GetNextWindow(hwndTest1, GW_HWNDPREV)) {
        if (IsWindowVisible (hwndTest1)) {
          GetWindowRect (hwndTest1, &rectTest);
          /* Get this window's coordinates relative to our window */
          MapWindowPoints (NULL, hwndServer, (LPPOINT)&rectTest, 2);
          if (IntersectRect(&rectIntersectNew, &rectTest, &rectScroll)) {
            /* move the intersection to find the area to update */
            OffsetRect(&rectIntersectNew,
                       destination_left - source_left,
                       destination_top - source_top);
            if (UpdateForTopmostWindow) /* note 1 */
              UnionRect (&rectIntersect, &rectIntersect, &rectIntersectNew);
            else { /* first time thru loop */
              UpdateForTopmostWindow = TRUE;
              CopyRect (&rectIntersect, &rectIntersectNew);
            }
          }
        }
      }
    }

    /* Note 1: There are further optimizations. After we */
    /* move the intersection (with OffsetRect), we could do */
    /* another intersection with rectScroll, to see if the */
    /* moved rect is still intersecting our rect. We have */
    /* to inspect all the windows lying above us. If there */
    /* is more than one intersecting our rectangle, it */
    /* would be ideal to make a list or complex region of */
    /* all the updates, to save time updating. Union is a */
    /* compromise. */

    /* If our new rect extends beyond Desktop (the screen), */
    /* need special updating (Windows bug). Must update */
    /* the portion that was off the screen. */

    rectUpdateLeftOrRight.top = destination_top;
    rectUpdateLeftOrRight.bottom = destination_bottom;
    rectUpdateTopOrBottom.left = destination_left;
    rectUpdateTopOrBottom.right = destination_right;

    if ((rectScroll.left < rectDesktop.left) && /* off screen */
        (rectScroll.left < destination_left)) { /* moving in */
      /* we have some updating to do */
      UpdateLeftOrRight = TRUE;
      rectUpdateLeftOrRight.left = destination_left;
      if (destination_left < rectDesktop.left)
        rectUpdateLeftOrRight.right = rectDesktop.left +
          destination_left - rectScroll.left;
      else
        rectUpdateLeftOrRight.right = destination_left +
          rectDesktop.left - rectScroll.left;
      /* optimization */
      rectUpdateTopOrBottom.left = rectUpdateLeftOrRight.right;
    }

    /* don't know how this could ever happen */
    if ((rectScroll.top < rectDesktop.top) && /* off screen */
        (rectScroll.top < destination_top)) { /* moving in */
      UpdateTopOrBottom = TRUE;
      rectUpdateTopOrBottom.top = destination_top;
      if (destination_top < rectDesktop.top)
        rectUpdateTopOrBottom.bottom = rectDesktop.top +
          destination_top - rectScroll.top;
      else
        rectUpdateTopOrBottom.bottom = destination_top +
          rectDesktop.top - rectScroll.top;
    }

    if ((rectScroll.right > rectDesktop.right) && /* off screen */
        (rectScroll.right > destination_right)) { /* moving in */
      UpdateLeftOrRight = TRUE;
      rectUpdateLeftOrRight.right = destination_right;
      if (destination_right > rectDesktop.right)
        rectUpdateLeftOrRight.left = rectDesktop.right -
          (rectScroll.right - destination_right);
      else
        rectUpdateLeftOrRight.left = destination_right -
          (rectScroll.right - rectDesktop.right);
      /* optimization */
      rectUpdateTopOrBottom.right = rectUpdateLeftOrRight.left;
    }

    if ((rectScroll.bottom > rectDesktop.bottom) && /* off screen */
        (rectScroll.bottom > destination_bottom)) { /* moving in */
      UpdateTopOrBottom = TRUE;
      rectUpdateTopOrBottom.bottom = destination_bottom;
      if (destination_bottom > rectDesktop.bottom)
        rectUpdateTopOrBottom.top = rectDesktop.bottom -
          (rectScroll.bottom - destination_bottom);
      else /* dest inside desktop */
        rectUpdateTopOrBottom.top = destination_bottom -
          (rectScroll.bottom - rectDesktop.bottom);
    }

    /* Move the region based on differences in top/left info given. */
    /*  Note that positive values mean right/down and negative      */
    /*  values mean left/up.                                        */

    ScrollDC(hdc, destination_left - source_left,
             destination_top - source_top,
             &rectScroll, NULL, NULL, NULL);

    if (UpdateLeftOrRight)
      InvalidateRect(hwndServer, &rectUpdateLeftOrRight, FALSE);
    if (UpdateTopOrBottom)
      InvalidateRect(hwndServer, &rectUpdateTopOrBottom, FALSE);
    if (UpdateForTopmostWindow)
      InvalidateRect(hwndServer, &rectIntersect, FALSE);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * long g2ext_x11_get_mouse_x_position (window_index)
 *
 *   Description:
 *     Get the X position of the mouse if it is in the Gensym window.
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return value: mouse X position
 *   Notes:
 *       To get the y value, call g2ext_x11_last_mouse_y_position.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

long g2ext_x11_get_mouse_x_position (window_index)
  long window_index;
{
    GensymXWindow *gwindow;
    Display *display;
    Window window;
    Window root, child;
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask;

    if (No_window)
        return 1;

    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;
    window = gwindow->xwindow;

    if (XQueryPointer(display, window, &root, &child, &root_x, &root_y,
                      &win_x, &win_y, &mask)) {
        gwindow->last_mouse_x = win_x;
        gwindow->last_mouse_y = win_y;
        gwindow->last_event_bits = g2pvt_modifier_bits(mask);
    }

    return gwindow->last_mouse_x;
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_x11_get_mouse_x_position( window_index )
     long window_index;
{
    POINT        pt;
    HWND        hwndServer;
    LPG2INFO lpG2Info;

    if (No_window)
        return (1);

    hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
    lpG2Info = GetlpG2Info(hwndServer);

    if ( IsWindow(hwndServer) ) {
        GetCursorPos( &pt );
        ScreenToClient( hwndCoor, &pt );
        lpG2Info->last_event_mouse_x = (long) pt.x;
        lpG2Info->last_event_mouse_y = (long) pt.y;
        /* Don't know how to query the following, but it seems to
           not be needed in practice. (!) (MHD 9/21/99) */
        /* lpG2Info->last_event_bits = ??? */
        lpG2Info->last_event_time = GetTickCount() & (unsigned long)EVENT_TIME_MASK;

    } else
        pt.x = -1;

    return (pt.x);
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_x11_move_pointer(long window_index, long dest_x, long dest_y)
 *
 *   Description:
 *     moves the pointer to the specified destination.
 *   Input Arguments:
 *     window_index
 *     dest_x:         Desired pointer x position
 *     dest_y:         Desired pointer y position
 *   Returns:
 *     return value: None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_x11_move_pointer(window_index, dest_x, dest_y)
     long window_index;
     long dest_x;
     long dest_y;
{
    GensymXWindow        *gwindow;
    Display *display;
    Window window;

    if (No_window)
        return;

    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;
    window = gwindow->xwindow;

    XWarpPointer(display, window, window,  0, 0,
                 None, None,        /* defaults to width and height */
                 (int)dest_x, (int)dest_y);
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void  g2ext_x11_move_pointer( window_index, nX, nY )
     long window_index;
     long nX;
     long nY;
{
    POINT        pt;
    HWND        hwndServer;

    if (!No_window) {

        hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

        if ( IsWindow(hwndServer) ) {
            pt.x = nX;
            pt.y = nY;
            ClientToScreen( hwndCoor, &pt );
            SetCursorPos( pt.x, pt.y );
        }
    }
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_x11_preinitialize(long run_without_local_window, char *windowhandle)
 *
 *   Description:
 *     Perform preinitialization actions
 *   Input Arguments:
 *     run_without_local_window: When non-zero, indicates no window desired
 *     windowhandle: When non-zero, indicates parent window
 *   Returns:
 *     None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

void g2ext_x11_preinitialize(run_without_local_window, windowhandle)
     long run_without_local_window;
     char *windowhandle;
{
  unsigned int parent_window_handle;
  No_window = (run_without_local_window) ? TRUE : FALSE;

  /* MDG - Changes for plugin.  Look for -WINDOWHANDLE command line option.
   * TW will parent to this window handle if specified.
   */
  if (strlen(windowhandle) > 0) {
    sscanf(windowhandle, "%xl", &parent_window_handle);
#ifdef WIN32
    parent_GhwndWin = (HWND) parent_window_handle;
#else
    parent_XWindow_address = parent_window_handle;
#endif
  }
}
/*000000000000000000000000000000000000000000000000000000000000000000000000000*/


/*****************************************************************************
 * void g2ext_x11_parse_geometry (char *parsestring)
 *
 *   Description:
 *     Parses the -geometry command line argument
 *   Input Arguments:
 *     parsestring:  a string received with the -geometry cmdline argument
 *   Returns:
 *       None
 *   Notes:
 *       We mung the return values into the form desired by g2ext_x11_initialize:
 *    Unspecified values are returned as -1.  Negative x and y offsets
 *    are returned as the actual value - 2.  This curious convention ensures
 *    that +0 and -0 can be distinguished, as required by X conventions.
 *    -----
 *   Modifications:
 *   jh, 2/1/97.  Implemented g2ext_x11_parse_geometry() for Windows/NT.
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_x11_parse_geometry (parsestring)
     char *parsestring;
{
    int i;

    for(i=0; i<4; parse_geometry_result[i++] = -1 );


    {
        int x, y;
        unsigned int width, height;
        int flags;

        flags = XParseGeometry(parsestring,&x,&y,&width,&height);
        if (XValue & flags)
            parse_geometry_result[0] = (XNegative & flags) ? (x-2) : x;

        if (YValue & flags)
            parse_geometry_result[1] = (YNegative & flags) ? (y-2) : y;

        if (WidthValue & flags)
            parse_geometry_result[2] = width;

        if (HeightValue & flags)
            parse_geometry_result[3] = height;
    }
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

static void parse_geometry_into_array(geometry, geometry_values)
char    *geometry;
int     *geometry_values; /* width, height, x-offset, y-offset */
{
  char   this_char, *this_ptr, *start = geometry;
  long   index_offset, scan_offset, at_final_char = 0;
  long   got_width = 0, got_height = 0, got_x_offset = 0;

  for (this_ptr = geometry;;this_ptr++) {
    scan_offset = -1; index_offset = 1;
    switch (this_char = *this_ptr) {
    case 'x':
    case 'X':
      if (got_width) {
        at_final_char = 1; break;
      }
      scan_offset = 1; got_width = 1; break;

    case '+':
    case '-':
      scan_offset = 0;
      if (!got_width) {
        got_width = 1; index_offset = 2; break;
      }
      if (got_height) {
        got_x_offset = 1; break;
      }
      if (got_x_offset) {
        at_final_char = 1; break;
      }
      got_height = 1; break;

    case '\0': at_final_char = 1; break;
    }
    if (at_final_char) {
      sscanf(start, "%d", geometry_values); return;
    }
    if (scan_offset >= 0) {
      *this_ptr = '\0';
      if (1 != sscanf(start, "%d", geometry_values)) return;
      *this_ptr = this_char;
      geometry_values += index_offset;
      start = this_ptr + scan_offset;
    }
  }
}

void g2ext_x11_parse_geometry (parsestring)
     char *parsestring;
{
    int   temp, geometry_values[] = {-1, -1, -1, -1};

    parse_geometry_into_array(parsestring, geometry_values);

    temp = geometry_values[2]; /* cf. x-2 in XWindows, rationale unknown */
    parse_geometry_result[0] = temp < 0 ? temp-2 : temp;

    temp = geometry_values[3]; /* cf. x-2 in XWindows, rationale unknown */
    parse_geometry_result[1] = temp < 0 ? temp-2 : temp;

    parse_geometry_result[2] = geometry_values[0];

    parse_geometry_result[3] = geometry_values[1];
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/



/*****************************************************************************
 * int g2ext_x11_parse_geometry_x()
 * int g2ext_x11_parse_geometry_y()
 * int g2ext_x11_parse_geometry_width()
 * int g2ext_x11_parse_geometry_height()
 *
 *   Description:
 *     Return components of the parsed -geometry cmdline arg
 *   Input Arguments:
 *     None
 *   Returns:
 *       return value: desired geometry component
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

int g2ext_x11_parse_geometry_x()
{
    return parse_geometry_result[0];
}

int g2ext_x11_parse_geometry_y()
{
    return parse_geometry_result[1];
}

int g2ext_x11_parse_geometry_width()
{
    return parse_geometry_result[2];
}

int g2ext_x11_parse_geometry_height()
{
    return parse_geometry_result[3];
}

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/


/*****************************************************************************
 * long g2ext_x11_bell(long window_index, long percent)
 *
 *   Description:
 *     Ring the bell
 *   Input Arguments:
 *     window_index
 *     percent
 *   Returns:
 *     return value: 0 on success, -1 on failure
 *   Notes:
 *       Beeping is not server specific. There's only a single speaker that
 *     is shared amoung all of the windows. In order to make the server window
 *     that is requesting the user's attention stand out we will bring that
 *     window to the top and flash it as well. Also, since the host thinks
 *     that there is something that requires the user's attention then
 *     we put the focus into that window as well.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

long g2ext_x11_bell(window_index, percent)
     long window_index;
     long percent;
{
    GensymXWindow *gwindow;

    if (No_window)
        return 0;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);

    if (XBell((gwindow->display_ptr), (int)percent) == BadValue)
        return -1;
    else
        return 0;
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

long g2ext_x11_bell( window_index, nPercent)
long window_index;
long nPercent;
{
  HWND hwnd;

  if (No_window)
    return(0);

  hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

  /* Don't mess with the main window unless we own it and we're in classic or
   * SDI mode.  This fixes HQ-4954403 "Native Editor: Setting invalid breakpoint
   * causes editor titlebar to go grey" -fmw, 3/12/05 */

  if (IsWindow(hwnd) && !Frame_is_MDI && !Frame_is_embedded) {
      BringWindowToTop(hwnd);
      SetFocus(hwnd);
      FlashWindow(hwnd, FALSE);
  }

  MessageBeep(MB_ICONEXCLAMATION);
  return 1;
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * GC x11_compute_tiling_gc (display, window, pixmap, depth,
 *                           foreground, background)
 *
 *   Description:
 *     Creates a GC which will tile the given pixmap.
 *   Input Arguments:
 *     display
 *     window
 *     pixmap
 *     depth
 *     foreground
 *     background
 *   Returns:
 *     return value: a GC
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

static GC x11_compute_tiling_gc (display, window, pixmap, depth,
                                 foreground, background)
     Display *display;
     Window window;
     Pixmap pixmap;
     int depth;
     int foreground, background;
{
    XGCValues values;
    int mask;

    values.foreground = foreground;
    values.background = background;
    mask = GCForeground | GCBackground;

    if (depth <= 1) {
        values.stipple = pixmap;
        values.fill_style = FillOpaqueStippled;
        mask |= GCStipple | GCFillStyle;
    } else {
        values.tile = pixmap;
        values.fill_style = FillTiled;
        mask |= GCTile | GCFillStyle;
    }

    return XCreateGC(display, window, mask, &values);
}
#endif /* XWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * void g2ext_x11_initialize_tile(window_index, pixmap_index,
 *                          foreground_xcolor, background_xcolor)
 *
 *   Description:
 *     Stores into the window a "tiling_gc", which will tile the given
 *     bitmap into the a window, using the fg and bg colors.
 *   Input Arguments:
 *     window_index
 *     pixmap_index
 *     foreground_xcolor
 *     background_xcolor
 *   Returns:
 *     return value: None
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_x11_initialize_tile(window_index, pixmap_index,
                         foreground_xcolor, background_xcolor)
     long window_index, pixmap_index, foreground_xcolor, background_xcolor;
{
    GensymXWindow *gwindow;
    PixmapStruct        *gpixmap;

    if (No_window)
        return;

    gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pixmap_index);
    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

    gwindow->the_tiling_gc = x11_compute_tiling_gc (gwindow->display_ptr,
                                                    gwindow->xwindow,
                                                    gpixmap->pixmap,
                                                    gpixmap->depth,
                                                    (int)foreground_xcolor,
                                                    (int)background_xcolor);

    /* Should store fg and bg with the pixmap. */
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_x11_initialize_tile(long window_index, long pixmap_index, long nFG, long nBG)
{
  LPG2INFO        lpG2Info        = NULL;
  HWND        hwndServer;

  if (No_window)
    return;

  hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);

  /* If this is not a legal server window then can't do much. */
  if ( IsWindow( hwndServer) && (lpG2Info=GetlpG2Info(hwndServer)) ) {

    /* 6/7/94, mpc: Notice we swap BG/FG colors here because
     *    pattern bitmaps color assignment is reverse that
     *    of X windows.
     */
    lpG2Info->nTileFG           = COLORVAL(nBG);
    lpG2Info->nTileBG           = COLORVAL(nFG);

    /* 5/19/95, mpc:  Only NT supports pattern bitmaps bigger than
     *    8x8. On Windows 3.1 and 95 the gensym background ends up
     *    looking real bad, so we use a solid gray brush instead.
     * 7/9/02, fmw: Windows 98 also supports pattern bitmaps of any size.
     */
    lpG2Info->Tilehbr = ImageCluster_CreatePatternBrush(pixmap_index);

    /* At startup the MDI client background is refreshed before we have the
       correct tiling pattern. Once we get the tiling pattern, refresh again. */
    if(hwndClient != NULL)
      InvalidateRect(hwndClient, NULL, TRUE);
  }
}
#endif /* MSWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * void g2ext_x11_tile(window_index, left, top, width, height)
 *
 *   Description:
 *     Fills a portion of the window with its tiling pattern, stored in
 *     its tiling_gc
 *   Input Arguments:
 *     window_index
 *     left,top
 *     width, height
 *   Returns:
 *     return value: None
 *   Notes:
 *       Pattern is either -1, being the default gensym tiling pattern, or is
 *     the handle for a pixmap.
 *     -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(XWINDOWS)

void g2ext_x11_tile(window_index, left, top, width, height)
     long window_index, left, top, width, height;
{
    GensymXWindow *gwindow;
    Display *display;
    Drawable drawable;
    PixmapStruct *gpixmap;
    GC gc;
    int pattern = -1;                /* Later, the pattern to draw. */
    int fg = 1;
    int bg = 0;

    if (No_window || No_drawing)
        return;

    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;
    drawable = x11_get_destination_drawable(gwindow);

    if (pattern == -1) {
        gc = gwindow->the_tiling_gc;
        XFillRectangle(display, drawable, gc, (int)left, (int)top,
                       (int)width, (int)height);
    } else {
        gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(pattern);
        gc = x11_compute_tiling_gc (gwindow->display_ptr, drawable,
                                    gpixmap->pixmap, gpixmap->depth, fg, bg);

        XFillRectangle(display, drawable, gc, (int)left, (int)top,
                       (int)width, (int)height);

        XFreeGC(display,gc);        /* Naughty */
    }
}
#endif /* XWindows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(MSWINDOWS)

void g2ext_x11_tile( window_index, nX, nY, nWidth, nHeight )
     long window_index;
     long nX, nY, nWidth, nHeight;
{
  int savedDC;
  HWND hwndServer;
  LPG2INFO window_info;
  HDC hdc;

  GTRACE(" g2ext_x11_tile\n");

  if (No_drawing)
    return;

  hwndServer = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  window_info = GetlpG2Info(hwndServer);

  if ( IsWindow( hwndServer) && window_info) {
    hdc = get_destination_hdc(window_info);

    savedDC = SaveDC(hdc);

    SetBkColor(hdc, window_info->nTileBG);
    SetTextColor(hdc, window_info->nTileFG);

    UnrealizeObject(window_info->Tilehbr);
    SelectObject(hdc, window_info->Tilehbr);
    PatBlt(hdc, nX, nY, nWidth, nHeight, PATCOPY);

    RestoreDC(hdc, savedDC);
    free_destination_hdc(window_info,hdc);
  }
}
#endif /* MSWindows */


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - More Miscellaneous Functions
 %
 % Description:
 %   Miscellaneous functions.
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*****************************************************************************
 * void AngleTo4096RadiusXYCoords(angle,Xptr,Yptr)
 *
 *   Description:
 *     Represents an angle by vector coordinates on a circle.
 *   Input Arguments:
 *     angle  - an angle expressed in positive or negative degrees
 *     Xptr   - returns the X coordinate
 *     Yptr   - returns the Y coordinate
 *   Returns:
 *     return value:
 *   Notes:
 *       This takes as input an angle expressed in degrees and returns the
 *     corresponding coordinates of X and Y on the circumference of a circle
 *     of radius 4096 centered at the origin.
 *
 *       Angles are relative to 3 o'clock, positive angles are counterclockwise
 *     in degrees, X increases from left to right, and Y increases from top to
 *     bottom.
 *
 *       The radius 4096 was chosen because it is large enough to provide
 *     distinctive values for each degree yet small enough so that it won't
 *     be likely to cause troubles if 16-bit ints are used.
 *   Modifications:
 *****************************************************************************/

/*222222222222222222222222 Conditionally Defined 2222222222222222222222222222*/
#if defined(MSWINDOWS)

static void AngleTo4096RadiusXYCoords(angle,Xptr,Yptr)
     int angle, *Xptr, *Yptr;

{
    static int SinTable[91] = /* rounded values 4096.0*sin(0, ... ,90) */
       {   0,   71,  143,  214,  286,  357,  428,  499,  570,  641,
         711,  782,  852,  921,  991, 1060, 1129, 1198, 1266, 1334,
        1401, 1468, 1534, 1600, 1666, 1731, 1796, 1860, 1923, 1986,
        2048, 2110, 2171, 2231, 2290, 2349, 2408, 2465, 2522, 2578,
        2633, 2687, 2741, 2793, 2845, 2896, 2946, 2996, 3044, 3091,
        3138, 3183, 3228, 3271, 3314, 3355, 3396, 3435, 3474, 3511,
        3547, 3582, 3617, 3650, 3681, 3712, 3742, 3770, 3798, 3824,
        3849, 3873, 3896, 3917, 3937, 3956, 3974, 3991, 4006, 4021,
        4034, 4046, 4056, 4065, 4074, 4080, 4086, 4090, 4093, 4095,
        4096 };
    int angle90, coord1, coord2;

      /* Express the angle as a positive angle in the range 0..359.
       * Because % is unpredictable for negative arguments, we must be
       * careful to operate only on positive arguments.
       */
    if (angle >= 0) {         /* angle is unchanged when in range 0..90 */
        if (angle >= 360)
            angle = angle % 360;
    } else {
        if (angle > -360)
            angle = 360 + angle;
        else
            angle = 360 - (-angle % 360);
    }

      /* Find the angle's counterpart in the first quadrant
       */
    angle90 = angle % 90;

      /* Look up the X and Y displacement in the sin table.  Note that
       * we don't yet know which is X and which is Y
       */
    coord1 = SinTable[angle90];
    coord2 = SinTable[90 - angle90];

      /* Finally associate the coordinates with appropriate signed values
       * of X and Y in the corresponding quadrant.  Quadrants are as follows.
       *                   -y
       *                 II | I
       *             -x ----|--- +x
       *                III | IV
       *                   +y
       */
    switch (angle/90) {
       case 0:  /* quadrant I   */
           *Xptr =  coord2;
           *Yptr = -coord1;
           break;
       case 1:  /* quadrant II  */
           *Xptr = -coord1;
           *Yptr = -coord2;
           break;
       case 2:  /* quadrant III */
           *Xptr = -coord2;
           *Yptr =  coord1;
           break;
       case 3:  /* quadrant IV  */
           *Xptr =  coord1;
           *Yptr =  coord2;
           break;
    }
}
#endif /* MSWindows */
/*222222222222222222222222 Conditionally Defined 2222222222222222222222222222*/


/*****************************************************************************
 * static void XlatArcCoords( nX, nY, nWidth, nHeight, nSA, nDA,
 *                            pnX1, pnY1, pnX2, pnY2)
 *
 *   Description:
 *     Translates between XWindow arc coords and MS-Windows coords.
 *   Input Arguments:
 *     nX        - Upper left corner of the rect
 *     nY        -
 *     nWidth        - extents of the rect.
 *     nHeight        -
 *     nSA        - Starting angle in units of 64*degrees.
 *     nDA        - Stopping angle in units of 64*degrees
 *                relative to start.
 *     pX1        - MS-WIndows Start coords of the arc.
 *     pY1        -
 *     pX1        - MS-WIndows Stop coords of the arc.
 *     nY1        -
 *   Returns:
 *     return value:
 *   Notes:
 *     Angles are relative to 3 o'clock.
 *     Positive angles are counterclockwise.
 *
 *       XWindows uses a starting angle and a displacement angle to
 *     indicate where on an ellipse to begin and end drawing an arc.
 *       Windows uses (x,y) pairs to indicate the angle at which to
 *     begin and end drawing.  This function converts angles given
 *     by nDA and NSA to pairs (npX1,npY1) and (npX2,npY2).
 *     Note that the pairs need only specify direction; they need
 *     not represent the exact points on the ellipse.
 *
 *       We use AngleTo4096RadiusXYCoords() to calculate the direction.
 *     The function represents the coordinate pairs as points on a circle
 *     of radius 4096 centered at the origin.  These are then translated
 *     (in the true graphics sense) with respect to the center of the
 *     ellipse's bounding box.
 *
 *       If in the future there is a need to find the exact coordinates
 *     on the ellipse, SolveForArcCoord()* can instead be used, but be
 *     aware that it expects as input only positive angles in 64ths of
 *     a degree.  This was used in the past.
 *
 *   * SolveForArcCoord removed in rev 1.108 -fmw, 1/4/05
 *
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(MSWINDOWS)

static void XlatArcCoords(long nX, long nY, long nWidth, long nHeight, long nSA, long nDA,
                          int *pnX1, int *pnY1, int *pnX2, int *pnY2)
{
    int start_angle, end_angle;
    int Xcenter, Ycenter;

      /* We first represent the starting and ending angles as absolute
       * angles.
       *    In MSWindows, an arc is always drawn clockwise from vector
       * (pnX1,pnY1) to (pnX2,pnY2).  A positive nDA indicates a clockwise
       * arc and a negative nDA indicates a counterclockwise arc. Therefore,
       * if nDA is negative, we must compensate by reversing the starting
       * and ending angles.
       */
    if (nDA >= 0) {
        start_angle = nSA;
        end_angle = nSA + nDA;
    } else {  /* reverse the angles */
        start_angle = nSA + nDA;
        end_angle = nSA;
    }

      /* We now represent the starting and ending angles by (vector)
       * coordinate pairs relative to origin (0,0).
       * Note that the angles are in 64ths of degrees, so we must compensate
       * by dividing them.
       */
    AngleTo4096RadiusXYCoords(start_angle/64, pnX1, pnY1);
    AngleTo4096RadiusXYCoords(end_angle/64, pnX2, pnY2);

      /* The vectors are relative to origin (0,0).  We must make them
       * relative to the center of the arc's bounding box by translating them.
       * We don't need to calculate the center exactly because the vectors
       * have sufficient length to hide round-off error.
       */
    Xcenter = nX + nWidth/2;
    Ycenter = nY + nHeight/2;

    *pnX1 = *pnX1 + Xcenter;   /* Translate the vectors the new origin */
    *pnY1 = *pnY1 + Ycenter;
    *pnX2 = *pnX2 + Xcenter;
    *pnY2 = *pnY2 + Ycenter;
}
#endif /* MSWindows */


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Debugging Functions
 %
 % Description:
 %   These are debugging support functions.
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
 * void x11_handle_error_as_signal (display, event)
 *
 *   Description:
 *     An error handler to toss out an interrupt in LISP
 *   Input Arguments:
 *     display
 *     event
 *   Returns:
 *     return value:
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

static void x11_handle_error_as_signal (display, event)
     Display *display;
     XErrorEvent *event;
{
    last_x11_error_code = event->error_code;
    g2int_x_error(last_x11_error_code);
    return;
}
#endif /* XWindows */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/


/*****************************************************************************
 * void g2ext_x11_set_debug_mode(window_index)
 *
 *   Description:
 *
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return value: None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_x11_set_debug_mode(window_index)
     int window_index;
{
#if defined(MSWINDOWS)
    return;
#else /* XWindows */
    GensymXWindow *gwindow;

    if (No_window)
        return;
    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

    if(last_non_debug_error_handler != (XErrorHandler)x11_handle_error_as_signal) {
        last_non_debug_error_handler =
            XSetErrorHandler((XErrorHandler)x11_handle_error_as_signal);

        XSynchronize(gwindow->display_ptr, True);
  }
#endif /* XWindows */
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*****************************************************************************
 * int g2ext_x11_debug_mode ()
 *
 *   Description:
 *
 *   Input Arguments:
 *     None
 *   Returns:
 *     return value: None
 *   Notes: Not called by C code nor by Lisp code.  I assume the intent is that
 *     it might be called from Lisp while G2 is running, so I'm adding a g2ext_
 *     prefix. -jv, 12/17/07
 *   Modifications:
 *****************************************************************************/

/*???????????????????????????????????????????????????????????????????????????*/
#if defined(XWINDOWS)

int g2ext_x11_debug_mode ()
{
    if(last_non_debug_error_handler
       != (XErrorHandler)x11_handle_error_as_signal) {
        last_non_debug_error_handler =
            XSetErrorHandler((XErrorHandler)x11_handle_error_as_signal);
    }
    return 0;
}
#endif /* XWindows */
/*???????????????????????????????????????????????????????????????????????????*/


/*****************************************************************************
 * void g2ext_x11_clear_debug_mode(window_index)
 *
 *   Description:
 *
 *   Input Arguments:
 *     window_index
 *   Returns:
 *     return value: None
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

void g2ext_x11_clear_debug_mode(window_index)
     int window_index;
{
#if defined(MSWINDOWS)
    return;
#else /* XWindows */
    GensymXWindow *gwindow;

    if (No_window)
        return;
    gwindow = (GensymXWindow *) g2ext_map_g2pointer_to_cpointer(window_index);

    if(last_non_debug_error_handler != NULL) {
        XSetErrorHandler((XErrorHandler)last_non_debug_error_handler);
        last_non_debug_error_handler = NULL;
        XSynchronize(gwindow->display_ptr, False);
    }
#endif
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/


/*****************************************************************************
 * BOOL g2ext_x11_address_is_window (display, address)
 *
 *   Description:
 *     A predicate to determine if the address specified as a window is,
 *     in fact, a Window in X's eyes.
 *   Input Arguments:
 *     display
 *     window
 *   Returns:
 *     1 if the address is a Window, 0 otherwise.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#if defined(XWINDOWS)

static void x11_ignore_error (display, event)
     Display *display;
     XErrorEvent *event;
{
    last_x11_error_code = event->error_code;
    return;
}


int g2ext_parent_window_size (display, address, dwidth, dheight)
     Display *display;
     long address;
     int *dwidth, *dheight;
{
  Status winstatus;
  XWindowAttributes returned_attributes;

  last_non_debug_error_handler = XSetErrorHandler((XErrorHandler)x11_ignore_error);
  winstatus = XGetWindowAttributes(display, (Window)address, &returned_attributes);
  *dwidth = returned_attributes.width;
  *dheight = returned_attributes.height;
  XSetErrorHandler((XErrorHandler)last_non_debug_error_handler);
  if (winstatus == 0) {
    return 0;
  }
  return 1;
}
#endif /* XWindows */

#if defined(MSWINDOWS)
int g2ext_get_hbu ()
{
  return LOWORD(GetDialogBaseUnits());
}
int g2ext_get_vbu ()
{
  return HIWORD(GetDialogBaseUnits());
}
#else
int g2ext_get_hbu ()
{
  //Todo
  return 0;
}

int g2ext_get_vbu ()
{
  //Todo
  return 0;
}
#endif
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
