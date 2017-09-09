
/****************************************************************************
*                                                                            *
*  Copyright 1989, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                         U.S. Patent No 4,785,391                           *
*                           Other Patent Pending                             *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
*****************************************************************************/
/********************* Revision Control Information **********************************
*                                                                                    
*     $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/speedo/nsample.c,v 1.1 1995-10-03 01:03:26 jra Exp $
*                                                                                    
*     $Log: not supported by cvs2svn $
*     Revision 1.4  1993/04/23 22:51:49  mhd
*     fixed comment
*
 * Revision 1.3  1993/04/23  22:43:36  mhd
 * Fixed problem in the changelog comment itself.
 *
 * Revision 1.2  1993/04/23  22:34:13  mhd
 * added the following define, moved here from speedo/set_spcs.c, per
 *    Bob Eggers@Bitstream. Changed next line to include spdo_prv.
 *    -- mhd@gensym, 4/25/93
 *    *
 * #define SET_SPCS
 *
 * Revision 1.1.1.1  1993/04/15  20:14:18  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
*       Revision 28.37  93/03/15  12:45:51  roberte
*       Release
*       
*       Revision 28.11  93/03/11  15:21:20  roberte
*       changed all #if __MSDOS to #ifdef MSDOS
*       
*       Revision 28.10  93/03/09  12:08:01  roberte
*        Replaced #if INTEL tests with #ifdef MSDOS as appropriate.
*       
*       Revision 28.8  93/01/04  11:37:15  roberte
*       Changed declaration of "lines" to an int so that sscanf will work.
*       
*       Revision 28.7  92/11/24  12:45:31  laurar
*       delete control Z.
*       
*       Revision 28.6  92/10/19  17:42:57  laurar
*       renamed ptsize to lines (for lines per em) which is more accurate.
*       
*       Revision 28.4  92/10/07  11:58:23  laurar
*       add user option for ptsize;
*       clean up compiler warnings with some casts.
*       
*       Revision 28.3  92/10/01  15:36:22  laurar
*       nothing!
*       
*       Revision 28.2  92/10/01  15:08:13  laurar
*       output entire character encoding instead of just one character.
*       
*       Revision 28.1  92/06/25  13:39:37  leeann
*       Release
*       
*       Revision 27.1  92/03/23  13:59:18  leeann
*       Release
*       
*       Revision 26.1  92/01/30  16:57:46  leeann
*       Release
*       
*       Revision 25.2  91/07/10  11:50:03  leeann
*       make a dummy _fmalloc for unix
*       
*       Revision 25.1  91/07/10  11:04:12  leeann
*       Release
*       
*       Revision 24.2  91/07/10  11:00:52  leeann
*       A better fix for font data far in small and medium memory models
*       
*       Revision 23.1  91/07/09  17:58:43  leeann
*       Release
*       
*       Revision 22.1  91/01/23  17:17:51  leeann
*       Release
*       
*       Revision 21.2  91/01/22  13:34:15  leeann
*       accomodate font far and small data model
*       
*       Revision 21.1  90/11/20  14:37:21  leeann
*       Release
*       
*       Revision 20.2  90/11/19  12:49:12  leeann
*       Fix problem with INCL_KEYS and PROTOS_AVAIL bot set to one
*       
*       Revision 20.1  90/11/12  09:29:58  leeann
*       Release
*       
*       Revision 19.1  90/11/08  10:19:37  leeann
*       Release
*       
*       Revision 18.1  90/09/24  10:08:08  mark
*       Release
*       
*       Revision 17.1  90/09/13  15:58:27  mark
*       Release name rel0913
*       
*       Revision 16.1  90/09/11  13:08:46  mark
*       Release
*       
*       Revision 15.1  90/08/29  10:03:19  mark
*       Release name rel0829
*       
*       Revision 14.1  90/07/13  10:39:14  mark
*       Release name rel071390
*       
*       Revision 13.2  90/07/13  10:20:10  mark
*       fix use of get_cust_no for compilers that support
*       function prototyping
*       
*       Revision 13.1  90/07/02  10:38:14  mark
*       Release name REL2070290
*       
*       Revision 12.2  90/05/09  15:30:03  mark
*       fix reference to sp_get_cust_no so that it compiles
*       properly under REENTRANT_ALLOC with PROTOS_AVAIL
*       
*       Revision 12.1  90/04/23  12:12:00  mark
*       Release name REL20
*       
*       Revision 11.2  90/04/23  12:09:39  mark
*       remove MODE_0 reference
*       
*       Revision 11.1  90/04/23  10:12:07  mark
*       Release name REV2
*       
*       Revision 10.4  90/04/21  10:48:18  mark
*       added samples of use of multiple device support option
*       
*       Revision 10.3  90/04/18  14:07:30  mark
*       change bytes_read to a ufix16
*       
*       Revision 10.2  90/04/12  13:44:48  mark
*       add code to check for standard customer number
*       
*       Revision 10.1  89/07/28  18:09:05  mark
*       Release name PRODUCT
*       
*       Revision 9.2  89/07/28  18:06:30  mark
*       fix argument declaration of sp_open_outline
*       
*       Revision 9.1  89/07/27  10:22:21  mark
*       Release name PRODUCT
*       
*       Revision 8.1  89/07/13  18:18:48  mark
*       Release name Product
*       
*       Revision 7.1  89/07/11  09:00:29  mark
*       Release name PRODUCT
*       
*       Revision 6.3  89/07/09  13:19:46  mark
*       changed open_bitmap to use new high resolution
*       bitmap positioning
*       
*       Revision 6.2  89/07/09  11:47:19  mark
*       added check font font size > 64k if INCL_LCD = 0
*       to give meaningful error message and abort
*       
*       Revision 6.1  89/06/19  08:34:20  mark
*       Release name prod
*       
*       Revision 5.1  89/05/01  17:53:01  mark
*       Release name Beta
*       
*       Revision 4.2  89/05/01  17:12:59  mark
*       use standard includes if prototypes are available
*       
*       Revision 4.1  89/04/27  12:13:57  mark
*       Release name Beta
*       
*       Revision 3.2  89/04/27  10:28:20  mark
*       Change handling for character indices in main loop,
*       ignore no character data error in report_error
*       Use 16 bit parameter to fread and malloc
*       
*       Revision 3.1  89/04/25  08:26:59  mark
*       Release name beta
*       
*       Revision 2.2  89/04/12  12:17:01  mark
*       added stuff for far stack and font
*       
*       Revision 2.1  89/04/04  13:33:33  mark
*       Release name EVAL
*       
*       Revision 1.14  89/04/04  13:19:41  mark
*       Update copyright text
*       
*       Revision 1.13  89/03/31  14:47:10  mark
*       recode to use public speedo.h and not using redefinition
*       of all functions (code reentrant version inline)
*       
*       Revision 1.12  89/03/30  11:33:30  john
*       Decryption keys 9, 10, 11 deleted.
*       
*       Revision 1.11  89/03/30  08:32:57  john
*       report_error() messages corrected.
*       
*       Revision 1.10  89/03/29  16:14:11  mark
*       changes for slot independence and dynamic/reentrant
*       data allocation
*       
*       Revision 1.9  89/03/28  10:50:44  john
*       Added first char index mechanism
*       Replaced NEXT_WORD_U() with read_2b().
*       
*       Revision 1.8  89/03/24  16:29:39  john
*       Import width error (6) deleted.
*       Error 12 text updated.
*       
*       Revision 1.7  89/03/24  15:14:30  mark
*       Clean up format for release
*       
*                                                                                    
*************************************************************************************/


/*************************** N S A M P L E . C *******************************
 *                                                                           *
 *                 SPEEDO CHARACTER GENERATOR TEST MODULE                    *
 *                                                                           *
 * This is an illustration of what external resources are required to        *
 * load a Speedo outline and use the Speedo character generator to generate  *
 * bitmaps or scaled outlines according to the desired specification.        *                                                    *
 *                                                                           *
 * This program loads a Speedo outline, defines a set of character           *
 * generation specifications, generates bitmap (or outline) data for each    *
 * character in the font and prints them on the standard output.             *
 *                                                                           *
 * If the font buffer is too small to hold the entire font, the first        *
 * part of the font is loaded. Character data is then loaded dynamically     *
 * as required.                                                              *
 *                                                                           *
 ****************************************************************************/

#include <stdio.h>
#ifdef MSDOS
#include <stdlib.h>
#endif
#if PROTOS_AVAIL
#ifdef MSDOS
#include <stdlib.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>
main(int argc,char *argv[]);
#else
void* malloc();
#endif
#else
void* malloc();
#endif

/* added the following define, moved here from speedo/set_spcs.c, per
   Bob Eggers@Bitstream. Changed next line to include spdo_prv.
   -- mhd@gensym, 4/25/93
   *
#define SET_SPCS

#include "spdo_prv.h"                 /* General definition for make_bmap */
#include "keys.h"                  /* Font decryption keys */

#define DEBUG  0

#if DEBUG
#define SHOW(X) printf("X = %d\n", X)
#else
#define SHOW(X)
#endif

#define MAX_BITS  256              /* Max line length of generated bitmap */

/***** GLOBAL FUNCTIONS *****/

/***** EXTERNAL FUNCTIONS *****/

/***** STATIC FUNCTIONS *****/

#if PROTOS_AVAIL
fix31 read_4b(ufix8 FONTFAR *ptr);
fix15 read_2b(ufix8 FONTFAR *ptr);
#else
fix31 read_4b();
fix15 read_2b();
#endif
/***** STATIC VARIABLES *****/
static  char   pathname[100];      /* Name of font file to be output */
static  ufix8 FONTFAR *font_buffer;       /* Pointer to allocated Font buffer */
static  ufix8 FONTFAR *char_buffer;       /* Pointer to allocate Character buffer */
static  buff_t font;               /* Buffer descriptor for font data */
static	ufix16			*font_table = NULL;  /* allocate as much space as you need */
#if INCL_LCD
static  buff_t char_data;          /* Buffer descriptor for character data */
#endif
static  FILE  *fdescr;             /* Speedo outline file descriptor */
static  ufix16 char_index;         /* Index of character to be generated */
static  ufix16 char_id;            /* Character ID */
static  ufix16 minchrsz;              /* minimum character buffer size */

static  ufix8  key[] = 
{
    KEY0, 
    KEY1, 
    KEY2, 
    KEY3, 
    KEY4, 
    KEY5, 
    KEY6, 
    KEY7, 
    KEY8
};                             /* Font decryption key */

static  fix15  raswid;             /* raster width  */
static  fix15  rashgt;             /* raster height */
static  fix15  offhor;             /* horizontal offset from left edge of emsquare */
static  fix15  offver;             /* vertical offset from baseline */
static  fix15  set_width;          /* character set width */
static  fix15  y_cur;              /* Current y value being generated and printed */
static  char   line_of_bits[2 * MAX_BITS + 1]; /* Buffer for row of generated bits */

#if INCL_MULTIDEV
#if INCL_BLACK || INCL_SCREEN || INCL_2D
bitmap_t bfuncs = { sp_open_bitmap, sp_set_bitmap_bits, sp_close_bitmap };
#endif
#if INCL_OUTLINE
outline_t ofuncs = { sp_open_outline, sp_start_new_char, sp_start_contour, sp_curve_to,
                     sp_line_to, sp_close_contour, sp_close_outline };
#endif
#endif


ufix8   temp[16];             /* temp buffer for first 16 bytes of font */

#if (defined (M_I86CM) || defined (M_I86LM) || defined (M_I86HM) || defined (M_I86SM) || defined (M_I86MM))
  /* then have we are using a microsoft compiler */
#else
  /* need to have a dummy _fmalloc for unix */
void *_fmalloc()
{
}
#endif

FUNCTION main(argc,argv)
int argc;
char *argv[];
{
   ufix16      bytes_read;           /* Number of bytes read from font file */
   specs_t     specs;                /* Bundle of character generation specs  */
   ufix32      first_char_index;     /* Index of first character in font */
   ufix32      no_layout_chars;        /* number of characters in layout */
   ufix32      i;
   ufix32      minbufsz;             /* minimum font buffer size to allocate */
   ufix16      cust_no;
   int         lines;
   ufix8       FONTFAR *byte_ptr;
   ufix8	      user;
   
#if REENTRANT_ALLOC
   SPEEDO_GLOBALS* sp_global_ptr;
#endif


   if (argc < 2) 
   {
      fprintf(stderr,"Usage: nsample {fontfile} {lines per em}\n\n");
      fprintf(stderr,"Lines per em is optional.  Default is 25.\n");
      exit (1);
   }

   sprintf(pathname, argv[1]);

/* Load Speedo outline file */
   fdescr = fopen (pathname, "rb");
   if (fdescr == NULL)
   {
      fprintf(stderr,"****** Cannot open file %s\n", pathname);
      exit(1);
   }
   if (argc > 2)
      sscanf(argv[2], "%d", &lines);
   else lines = 25;

/* get minimum font buffer size - read first 16 bytes to get the minimum
   size field from the header, then allocate buffer dynamically  */

   bytes_read = fread(temp, sizeof(ufix8), 16, fdescr);

   if (bytes_read != 16)
	{
	   fprintf(stderr,"****** Error on reading %s: %x\n", pathname, bytes_read);
   	fclose(fdescr);
      exit(1);
	}
#if INCL_LCD
   minbufsz = (ufix32)read_4b(temp+FH_FBFSZ);
#else
   minbufsz = (ufix32)read_4b(temp+FH_FNTSZ);
   if (minbufsz >= 0x10000)
	{
	   fprintf(stderr,
         "****** Cannot process fonts greater than 64K - use dynamic character loading configuration option\n");
   	fclose(fdescr);
      exit(1);
	}
#endif

   if (strcmp("FONTFAR","far") == 0)
      font_buffer = (ufix8 FONTFAR *)_fmalloc((ufix16)minbufsz);
   else
      font_buffer = (ufix8 *)malloc((ufix16)minbufsz);
      
   if (font_buffer == NULL)
	{
	   fprintf(stderr,"****** Unable to allocate memory for font buffer\n");
      fclose(fdescr);
      exit(1);
	}

#if DEBUG
   printf("Loading font file %s\n", pathname);
#endif

   fseek(fdescr, (ufix32)0, 0);
   if (strcmp("FONTFAR","far") ==0)
   {
      byte_ptr = font_buffer;
      for (i=0; i< minbufsz; i++)
      {
         int ch;
         ch = getc(fdescr);
         if (ch == EOF)
         {
            fprintf (stderr,"Premature EOF in reading font buffer, %ld bytes read\n",i);
            exit(2);
         }
         *byte_ptr=(ufix8)ch;
         byte_ptr++;
      }
      bytes_read = (ufix16)i;
   }
   else
   {
      bytes_read = fread((ufix8 *)font_buffer, sizeof(ufix8), (ufix16)minbufsz, fdescr);
      if (bytes_read == 0)
      {
         fprintf(stderr,"****** Error on reading %s: %x\n", pathname, bytes_read);
         fclose(fdescr);
         exit(1);
      }
   }

#if INCL_LCD
/* now allocate minimum character buffer */

   minchrsz = read_2b(font_buffer+FH_CBFSZ);

   if (strcmp("FONTFAR","far") ==0)
      char_buffer = (ufix8 FONTFAR *)_fmalloc(minchrsz);
   else
      char_buffer = (ufix8*)malloc(minchrsz);

   if (char_buffer == NULL)
	{
	   fprintf(stderr,"****** Unable to allocate memory for character buffer\n");
      fclose(fdescr);
      exit(1);
	}
#endif

#if DYNAMIC_ALLOC || REENTRANT_ALLOC
   sp_global_ptr = (SPEEDO_GLOBALS *)malloc(sizeof(SPEEDO_GLOBALS));
   memset(sp_global_ptr,(ufix8)0,sizeof(SPEEDO_GLOBALS));
#endif


/* Initialization */
   sp_reset(PARAMS1);                   /* Reset Speedo character generator */

   font.org = font_buffer;
   font.no_bytes = bytes_read;

   if ((cust_no=sp_get_cust_no(PARAMS2 font)) != CUS0) /* NOT STANDARD ENCRYPTION */
	{
	   fprintf(stderr,"Unable to use fonts for customer number %d\n",
         sp_get_cust_no(PARAMS2 font));
      fclose(fdescr);
      exit(1);
   }

#if INCL_KEYS
   sp_set_key(PARAMS2 key);              /* Set decryption key */
#endif

#if INCL_MULTIDEV
#if INCL_BLACK || INCL_SCREEN || INCL_2D
   sp_set_bitmap_device(PARAMS2 &bfuncs,sizeof(bfuncs));              /* Set decryption key */
#endif
#if INCL_OUTLINE
   sp_set_outline_device(PARAMS2 &ofuncs,sizeof(ofuncs));              /* Set decryption key */
#endif
#endif

   first_char_index = read_2b(font_buffer + FH_FCHRF);
   no_layout_chars = read_2b(font_buffer + FH_NCHRL);
   if ( (font_table = (ufix16 *)malloc(no_layout_chars*sizeof(ufix16))) == NULL)
   {
	   fprintf(stderr,"Can't allocate font_table.\n");
   	exit(1);
   }
   for (i=0; i < no_layout_chars; i++)
	   font_table[i] = i + first_char_index;

/* Set specifications for character to be generated */
   specs.pfont = &font;          /* Pointer to Speedo outline structure */
   specs.xxmult = (long)lines << 16;     /* Coeff of X to calculate X pixels */
   specs.xymult = 0L << 16;      /* Coeff of Y to calculate X pixels */
   specs.xoffset = 0L << 16;     /* Position of X origin */
   specs.yxmult = 0L << 16;      /* Coeff of X to calculate Y pixels */
   specs.yymult = (long)lines << 16;     /* Coeff of Y to calculate Y pixels */
   specs.yoffset = 0L << 16;     /* Position of Y origin */
   specs.flags = MODE_BLACK;         /* Mode flags */
   specs.out_info = NULL;   


   if (!sp_set_specs(PARAMS2 &specs))    /* Set character generation specifications */
   {
      fprintf(stderr,"****** Cannot set requested specs\n");
   }
   else
   {
      for(char_index=0; char_index < no_layout_chars; char_index++)
		{
		 char_id = sp_get_char_id(PARAMS2 char_index);
         if (!sp_make_char(PARAMS2 font_table[char_index]))
         fprintf(stderr,"****** Cannot generate character %d\n", char_index);
/*
         fprintf(stderr,"Type q to quit or enter to continue: ");
         user = getchar();
         if (user == 'q' || user == 'Q')
         	break;
*/
		}
   }
   fclose(fdescr);
   exit(0);
}


#if INCL_LCD
#if REENTRANT_ALLOC
FUNCTION buff_t STACKFAR * WDECL sp_load_char_data(sp_global_ptr, file_offset, no_bytes, cb_offset)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION buff_t STACKFAR * WDECL sp_load_char_data(file_offset, no_bytes, cb_offset)
#endif
fix31    file_offset;  /* Offset in bytes from the start of the font file */
fix15    no_bytes;     /* Number of bytes to be loaded */
fix15    cb_offset;    /* Offset in bytes from start of char buffer */
/*
 * Called by Speedo character generator to request that character
 * data be loaded from the font file into a character data buffer.
 * The character buffer offset is zero for all characters except elements
 * of compound characters. If a single buffer is allocated for character
 * data, cb_offset ensures that sub-character data is loaded after the
 * top-level compound character.
 * Returns a pointer to a buffer descriptor.
 */
{
int     bytes_read,i;
ufix8  FONTFAR *byte_ptr;

#if DEBUG
printf("\nCharacter data(%d, %d, %d) requested\n", file_offset, no_bytes, cb_offset);
#endif
if (fseek(fdescr, (long)file_offset, (int)0) != 0)
    {
    printf("****** Error in seeking character\n");
    fclose(fdescr);     
    exit(1);
    }

if ((no_bytes + cb_offset) > minchrsz)
    {
    printf("****** Character buffer overflow\n");
    fclose(fdescr);     
    exit(3);
    }

if (strcmp("FONTFAR","far") ==0){
    byte_ptr = char_buffer+cb_offset;
    bytes_read = 0;
    for (i=0; i<no_bytes; i++)
        {
        *byte_ptr = (ufix8)getc(fdescr);
        byte_ptr++;
        bytes_read++;
       }
    }
else
    bytes_read = fread((char_buffer + cb_offset), sizeof(ufix8), no_bytes, fdescr);

if (bytes_read != no_bytes)
    {
    printf("****** Error on reading character data\n");
    fclose(fdescr);     
    exit(2);
    }

#if DEBUG
printf("Character data loaded\n");
#endif

char_data.org = (ufix8 FONTFAR *)char_buffer + cb_offset;
char_data.no_bytes = no_bytes;
return &char_data;
}
#endif


#if REENTRANT_ALLOC
FUNCTION void sp_report_error(sp_global_ptr,n)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_report_error(n)
#endif
fix15 n;        /* Error identification number */
/*
 * Called by Speedo character generator to report an error.
 *
 *  Since character data not available is one of those errors
 *  that happens many times, don't report it to user
 */
{

switch(n)
    {
case 1:
    printf("Insufficient font data loaded\n");
    break;

case 3:
    printf("Transformation matrix out of range\n");
    break;

case 4:
    printf("Font format error\n");
    break;
                 
case 5:
    printf("Requested specs not compatible with output module\n");
    break;

case 7:
    printf("Intelligent transformation requested but not supported\n");
    break;

case 8:
    printf("Unsupported output mode requested\n");
    break;

case 9:
    printf("Extended font loaded but only compact fonts supported\n");
    break;

case 10:
    printf("Font specs not set prior to use of font\n");
    break;

case 12:
    break;

case 13:
    printf("Track kerning data not available()\n");
    break;

case 14:
    printf("Pair kerning data not available()\n");
    break;

default:
    printf("report_error(%d)\n", n);
    break;
    }
}

#if REENTRANT_ALLOC
FUNCTION void sp_open_bitmap(sp_global_ptr, x_set_width, y_set_width, xorg, yorg, xsize, ysize)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_open_bitmap(x_set_width, y_set_width, xorg, yorg, xsize, ysize)
#endif
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
offhor = (fix15)(xorg >> 16);
offver = (fix15)(yorg >> 16);

if (raswid > MAX_BITS)
    raswid = MAX_BITS;

printf("\nCharacter index = %d, ID = %d\n", char_index, char_id);
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

#if REENTRANT_ALLOC
FUNCTION void sp_set_bitmap_bits (sp_global_ptr, y, xbit1, xbit2)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_set_bitmap_bits (y, xbit1, xbit2)
#endif
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

#if REENTRANT_ALLOC
FUNCTION void sp_close_bitmap(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_close_bitmap()
#endif
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
#if REENTRANT_ALLOC
FUNCTION void sp_open_outline(sp_global_ptr, x_set_width, y_set_width, xmin, xmax, ymin, ymax)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_open_outline(x_set_width, y_set_width, xmin, xmax, ymin, ymax)
#endif
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


#if REENTRANT_ALLOC
FUNCTION void sp_start_new_char(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_start_new_char()
#endif
/*
 * Called by Speedo character generator to initialize prior to
 * outputting scaled outline data for a sub-character in a compound
 * character.
 */
{
printf("start_new_char()\n");
}

#if REENTRANT_ALLOC
FUNCTION void sp_start_contour(sp_global_ptr, x, y, outside)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_start_contour(x, y, outside)
#endif
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

#if REENTRANT_ALLOC
FUNCTION void sp_curve_to(sp_global_ptr, x1, y1, x2, y2, x3, y3)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_curve_to(x1, y1, x2, y2, x3, y3)
#endif
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

#if REENTRANT_ALLOC
FUNCTION void sp_line_to(sp_global_ptr, x, y)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_line_to(x, y)
#endif
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


#if REENTRANT_ALLOC
FUNCTION void sp_close_contour(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_close_contour()
#endif
/*
 * Called by Speedo character generator at the end of each contour
 * in the outline data of the character.
 */
{
printf("close_contour()\n");
}

#if REENTRANT_ALLOC
FUNCTION void sp_close_outline(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_close_outline()
#endif
/*
 * Called by Speedo character generator at the end of output of the
 * scaled outline of the character.
 */
{
printf("close_outline()\n");
}

#endif

FUNCTION fix15 read_2b(pointer)
ufix8 FONTFAR *pointer;
/*
 * Reads 2-byte field from font buffer 
 */
{
fix15 temp;

temp = *pointer++;
temp = (temp << 8) + *(pointer);
return temp;
}


FUNCTION fix31 read_4b(pointer)
ufix8 FONTFAR *pointer;
/*
 * Reads 4-byte field from font buffer 
 */
{
fix31 temp;

temp = *pointer++;
temp = (temp << 8) + *(pointer++);
temp = (temp << 8) + *(pointer++);
temp = (temp << 8) + *(pointer);
return temp;
}
