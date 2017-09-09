/*
 *	truetype.c
 *                                                                           *
 *	sample mainline program for truetype rasterizer
 *
*/

/*	Revision Control Information
 *	$Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fnt/c/truetype.c,v 1.1 1995-11-13 22:32:52 mes Exp $
 *	$Log: not supported by cvs2svn $
 *	Revision 1.1  1995/10/03 00:37:50  jra
 *	Adding ext files from 4.0 Rev. 1 as initial commit for AB.
 *
 *	Revision 1.1  1993/05/19 22:04:39  mhd
 *	Added Bitstream fontrip (Font Raster Image Processor) c & h files.  Not
 *	all are compiles -- some are demos, or test modules.
 *
 * Revision 1.1  1993/05/04  20:15:36  mhd
 * The flat-directory version of the Bitstream 4-in-1 software.
 *
 * Revision 1.3  1993/04/23  22:47:34  mhd
 * Fixed embedded comments within changelog comments.
 *
 * Revision 1.2  1993/04/23  22:30:13  mhd
 * Added this per Bob Egger's @ Bitstream advice.  This is needed
 * as part of the commenting out of speedo_globals in tt_specs.c:
 *    #define SET_SPCS
 *
 * Revision 1.1.1.1  1993/04/15  20:14:41  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 6.46  93/03/18  10:30:58  roberte
 * Changed back to making characters by Apple Unicode.
 * 
 * Revision 6.45  93/03/17  11:02:12  roberte
 * Returned this sample program to making character index.
 * 
 * Revision 6.44  93/03/15  13:23:34  roberte
 * Release
 * 
 * Revision 6.15  93/03/11  20:04:12  roberte
 * changed #if __MSDOS to #ifdef MSDOS
 * 
 * Revision 6.14  93/03/10  17:11:48  roberte
 * Changed type of main() to int.
 * 
 * Revision 6.13  93/03/09  12:13:58  roberte
 *  Replaced #if INTEL tests with #if __MSDOS as appropriate.
 * Worked on include file list.
 * 
 * Revision 6.12  93/01/26  13:35:17  roberte
 * Added PARAMS1 and PARAMS2 macros to all reentrant function calls and definitions. 
 * Added conditional allocation of sp_global_ptr so DYNAMIC_ALLOC and REENTRANT_ALLOC
 * are testable in this module.
 * 
 * Revision 6.11  93/01/20  09:55:51  davidw
 * 80 column cleanup
 * 
 * Revision 6.10  93/01/20  09:25:18  davidw
 * 80 column and ANSI cleanup.
 * 
 * Revision 6.9  92/12/02  15:48:11  laurar
 * change between outline mode and black mode on command line.
 * 
 * Revision 6.7  92/11/10  10:09:49  davidw
 * made output mode switchable
 * 
 * Revision 6.6  92/11/09  17:02:42  davidw
 * changed specs.flags to reflect mode set by -DINCL_OUTLINE flag in makefile,
 * no longer hardwired to MODE_BLACK
 * 
 * Revision 6.5  92/10/28  09:53:39  davidw
 * removed control Z from EOF
 * 
 * Revision 6.4  92/10/19  17:57:27  laurar
 * change ptsize variable to lines per em.
 * 
 * Revision 6.3  92/10/08  18:31:21  laurar
 * take out SUPRESS define; add "q to quit" message;
 * add include <stdlib.h> for INTEL.
 * 
 * Revision 6.1  91/08/14  16:49:10  mark
 * Release
 * 
 * Revision 5.1  91/08/07  12:30:15  mark
 * Release
 * 
 * Revision 4.3  91/08/07  12:05:18  mark
 * remove MODE_APPLE reference
 * 
 * Revision 4.2  91/08/07  11:58:40  mark
 * add rcs control strings
 * 
*/

#ifdef RCSSTATUS
static char rcsid[] = "$Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fnt/c/truetype.c,v 1.1 1995-11-13 22:32:52 mes Exp $";
#endif

#ifdef MSDOS
#include <stdlib.h>
#endif
#include <stdio.h>
#include "spdo_prv.h"
/* Added this per Bob Egger's @ Bitstream advice.  This is needed
   as part of the commenting out of speedo_globals in tt_specs.c
   --mhd@gensym 4/25/93
   */
#define SET_SPCS
#include "fscdefs.h"
#include "fontscal.h"
#include "sfnt.h"
#include "fserror.h"
#include "truetype.h"

#if APOLLO
char *malloc();
#else
#include <malloc.h>
#endif


/*** EXTERNAL FUNCTIONS ***/
extern   boolean  tt_release_font ();

/*** STATIC VARIABLES ***/
#define FONT_BUFFER_SIZE  1000000      /* Size of font buffer */
#define GET_WORD(A)  ((ufix16)((ufix16)A[0] << 8) | ((ufix8)A[1]))
#define MAX_BITS  256	/* Max line length of generated bitmap */

static  fix15  raswid;	/* raster width  */
static  fix15  rashgt;	/* raster height */
static  fix15  offhor;	/* horizontal offset from left edge of emsquare */
static  fix15  offver;	/* vertical offset from baseline */
static  fix15  set_width;	/* character set width */
static  fix15  y_cur;		/* Current y value being generated and printed */
static  char   line_of_bits[2 * MAX_BITS + 1]; /* Buf for row of gen'd bits */

int     main(argc, argv)
fix15 argc;
char **argv;
{
   FILE     *fdes;
   ufix16   i;
   int32    handle;     /* handle to sfnt resource ==> iPtr.clientID */
   ufix32   lines;
   ufix8    user;
   specs_t  specs;
   short    outl_mode;
#if REENTRANT_ALLOC
   SPEEDO_GLOBALS* sp_global_ptr;
#endif

   if (argc < 2) {
      fprintf(stderr,
		"Usage: ttsample <font filename> <lines per em> <outline mode>\n");
      fprintf(stderr,"lines per em is optional.  Default is 25.\n");
      fprintf(stderr,
		"Type 1 for outline mode if you wish it.  If you type nothing,\n");
      fprintf(stderr,"then the default is black mode.\n");
      exit(1);
   }

   fdes = fopen ((char *)argv[1], "rb");
   if (fdes == NULL) {
      fprintf(stderr, "Cannot open file %s\n", argv[1]);
      exit(1);
   }
   if (argc >= 3) {
       sscanf(argv[2],"%ld",&lines);
	   if (lines <= 6) {
		   fprintf(stderr,"invalid pointsize\n");
		   fclose(fdes);
		   exit(1);
	   }
   }
   else
	   lines = 25;

   if (argc >= 4)
      sscanf(argv[3], "%d", &outl_mode);
   else
      outl_mode = 0;

#if DYNAMIC_ALLOC || REENTRANT_ALLOC
   sp_global_ptr = (SPEEDO_GLOBALS *)malloc(sizeof(SPEEDO_GLOBALS));
   memset(sp_global_ptr,(ufix8)0,sizeof(SPEEDO_GLOBALS));
#endif

   if (!tt_reset(PARAMS1)) {
      fprintf(stderr, "*** tt_reset fails\n\n");
      exit(1);
   }

   handle = (ufix32)fdes;
   if (!tt_load_font (PARAMS2 handle)) {
      fprintf(stderr, "*** tt_load_font fails\n\n");
      exit(1);
   }

   specs.xxmult = (long)lines << 16;
   specs.xymult = 0L;
   specs.xoffset = 0L;
   specs.yxmult = 0L;
   specs.yymult = (long)lines << 16;
   specs.yoffset = 0L;

   if (outl_mode)
      specs.flags = MODE_OUTLINE;
   else
      specs.flags = MODE_BLACK;

   if (!tt_set_specs (PARAMS2 &specs)) {
      fprintf(stderr, "*** tt_set_specs fails\n\n");
      exit(1);
   }

   for (i=33; i<256; i++) {
      fprintf (stderr,"making char code %hd at size %ld\n",i,lines);

	  if (!tt_make_char (PARAMS2 i))
	      fprintf(stderr, "*** tt_make_char fails\n\n");

/*
      fprintf(stderr,"Type Q to quit or any other key to continue: ");
      user = getchar();
      if (user == 'q' || user == 'Q')
         break;
   */
   }

   tt_release_font(PARAMS1);

   exit(0);
}	/* end main() */

FUNCTION  GetSFNTFunc  tt_get_font_fragment (clientID, offset, length)
  int32  clientID, offset, length;

/* Returns a pointer to data extracted from the sfnt.
   tt_get_font_fragment must be initialized in the fs_GlyphInputType
   record before fs_NewSfnt is called.  */
{
FILE  *fdes;
ufix8 *ptr;

fdes = (FILE *)clientID;
ptr = (ufix8 *)malloc(length);

if (ptr == NULL)
    return ((GetSFNTFunc)NULL);

if (fseek(fdes, offset, 0) != 0)
    return ((GetSFNTFunc)NULL);

if (fread(ptr,1,length,fdes) != length)
    return ((GetSFNTFunc)NULL);
    
return((GetSFNTFunc)ptr);
}


FUNCTION void tt_release_font_fragment (ptr)
  void *ptr;

/* Returns the memory at pointer to the heap
  */
{
free(ptr);
}



FUNCTION void sp_report_error(PARAMS2 n)
GDECL
fix15 n;        /* Error identification number */
/*
 * Called by Speedo character generator to report an error.
 *
 *  Since character data not available is one of those errors
 *  that happens many times, don't report it to user
 */
{

printf("*** report_error 0x%X %d\n\n", n, n);
}

FUNCTION void sp_open_bitmap(PARAMS2 x_set_width, y_set_width, xorg, yorg, xsize, ysize)
GDECL
fix31 x_set_width;
fix31 y_set_width;   /* Set width vector */
fix31 xorg;    /* Pixel boundary at left extent of bitmap character */
fix31 yorg;    /* Pixel boundary at right extent of bitmap character */
fix15 xsize;    /* Pixel boundary of bottom extent of bitmap character */
fix15 ysize;    /* Pixel boundary of top extent of bitmap character */
/* 
 * Called by Speedo character generator to initialize a buffer prior
 * to receiving bitmap data.
 */
{
fix15 i;

#if DEBUG
printf("open_bitmap(%3.1f, %3.1f, %3.1f, %3.1f, %d, %d)\n",
    (real)x_set_width / 65536.0, (real)y_set_width / 65536.0,
    (real)xorg / 65536.0, (real)yorg / 65536.0, (int)xsize, (int)ysize);
#endif
raswid = xsize;
rashgt = ysize;
offhor = (fix15)((xorg+32768L) >> 16);
offver = (fix15)(yorg >> 16);

if (raswid > MAX_BITS)
    raswid = MAX_BITS;

printf("set width = %3.1f, %3.1f\n", (real)x_set_width / 65536.0, (real)y_set_width / 65536.0);
printf("X offset  = %d\n", offhor);
printf("Y offset  = %d\n\n", offver);
for (i = 0; i < raswid; i++)
    {
    line_of_bits[i << 1] = '.';
    line_of_bits[(i << 1) + 1] = ' ';
    }
line_of_bits[raswid << 1] = '\0';
y_cur = 0;
}

FUNCTION void sp_set_bitmap_bits (PARAMS2 y, xbit1, xbit2)
  GDECL
  fix15     y;     /* Scan line (0 = first row above baseline) */
  fix15     xbit1; /* Pixel boundary where run starts */
  fix15     xbit2; /* Pixel boundary where run ends */

/* 
 * Called by Speedo character generator to write one row of pixels 
 * into the generated bitmap character.                               
 */

{
fix15 i;
#if DEBUG
printf("set_bitmap_bits(%d, %d, %d)\n", (int)y, (int)xbit1, (int)xbit2);
#endif
if (xbit1 < 0)
    {
    printf("ERROR!!! X1 < 0!!!\n");
    exit(0);
    }
/* Clip runs beyond end of buffer */
if (xbit1 > MAX_BITS)
    xbit1 = MAX_BITS;

if (xbit2 > MAX_BITS)
    xbit2 = MAX_BITS;

/* Output backlog lines if any */
while (y_cur != y)
    {
    printf("    %s\n", line_of_bits);
    for (i = 0; i < raswid; i++)
        {
        line_of_bits[i << 1] = '.';
        }
    y_cur++;
    }

/* Add bits to current line */
for (i = xbit1; i < xbit2; i++)
    {
    line_of_bits[i << 1] = 'X';
    }
}

FUNCTION void sp_close_bitmap(PARAMS1)
GDECL
/* 
 * Called by Speedo character generator to indicate all bitmap data
 * has been generated.
 */
{
#if DEBUG
printf("close_bitmap()\n");
#endif
printf("    %s\n", line_of_bits);
}

#if INCL_OUTLINE
FUNCTION void sp_open_outline(PARAMS1 x_set_width, y_set_width, xmin, xmax, ymin, ymax)
GDECL
fix31 x_set_width;
fix31 y_set_width;  /* Transformed escapement vector */
fix31  xmin;                           /* Minimum X value in outline */
fix31  xmax;                           /* Maximum X value in outline */
fix31  ymin;                           /* Minimum Y value in outline */
fix31  ymax;                           /* Maximum Y value in outline */
/*
 * Called by Speedo character generator to initialize prior to
 * outputting scaled outline data.
 */
{
printf("\nopen_outline(%3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f)\n",
    (real)x_set_width / 65536.0, (real)y_set_width / 65536.0,
    (real)xmin / 65536.0, (real)xmax / 65536.0, (real)ymin / 65536.0, (real)ymax / 65536.0);
}


FUNCTION void sp_start_new_char(PARAMS1)
GDECL
/*
 * Called by Speedo character generator to initialize prior to
 * outputting scaled outline data for a sub-character in a compound
 * character.
 */
{
printf("start_new_char()\n");
}

FUNCTION void sp_start_contour(PARAMS2 x, y, outside)
GDECL
fix31    x;       /* X coordinate of start point in 1/65536 pixels */
fix31    y;       /* Y coordinate of start point in 1/65536 pixels */
boolean outside;  /* TRUE if curve encloses ink (Counter-clockwise) */
/*
 * Called by Speedo character generator at the start of each contour
 * in the outline data of the character.
 */
{
printf("start_contour(%3.1f, %3.1f, %s)\n", 
    (real)x / 65536.0, (real)y / 65536.0, 
    outside? "outside": "inside");
}

FUNCTION void sp_curve_to(PARAMS2 x1, y1, x2, y2, x3, y3)
GDECL
fix31 x1;               /* X coordinate of first control point in 1/65536 pixels */
fix31 y1;               /* Y coordinate of first control  point in 1/65536 pixels */
fix31 x2;               /* X coordinate of second control point in 1/65536 pixels */
fix31 y2;               /* Y coordinate of second control point in 1/65536 pixels */
fix31 x3;               /* X coordinate of curve end point in 1/65536 pixels */
fix31 y3;               /* Y coordinate of curve end point in 1/65536 pixels */
/*
 * Called by Speedo character generator onece for each curve in the
 * scaled outline data of the character. This function is only called if curve
 * output is enabled in the set_specs() call.
 */
{
printf("curve_to(%3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f)\n", 
    (real)x1 / 65536.0, (real)y1 / 65536.0,
    (real)x2 / 65536.0, (real)y2 / 65536.0,
    (real)x3 / 65536.0, (real)y3 / 65536.0);
}

FUNCTION void sp_line_to(PARAMS2 x, y)
GDECL
fix31 x;               /* X coordinate of vector end point in 1/65536 pixels */
fix31 y;               /* Y coordinate of vector end point in 1/65536 pixels */
/*
 * Called by Speedo character generator onece for each vector in the
 * scaled outline data for the character. This include curve data that has
 * been sub-divided into vectors if curve output has not been enabled
 * in the set_specs() call.
 */
{
printf("line_to(%3.1f, %3.1f)\n", 
    (real)x / 65536.0, (real)y / 65536.0);
}


FUNCTION void sp_close_contour(PARAMS1)
GDECL
/*
 * Called by Speedo character generator at the end of each contour
 * in the outline data of the character.
 */
{
printf("close_contour()\n");
}

FUNCTION void sp_close_outline(PARAMS1)
GDECL
/*
 * Called by Speedo character generator at the end of output of the
 * scaled outline of the character.
 */
{
printf("close_outline()\n");
}

#endif
