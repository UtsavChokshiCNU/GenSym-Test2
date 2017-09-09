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

/*************************** K S A M P L E . C *******************************
 *                                                                           *
 *              KANJI SPEEDO CHARACTER GENERATOR TEST MODULE                 *
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
#include <math.h>
#if PROTOS_AVAIL
#include <stddef.h>
#include <malloc.h>
#include <string.h>
void main(int argc,char *argv[]);
#else
void* malloc();
#endif

#define SET_SPCS		/* added per bob eggers -mhd, 7/26/93
				 (We were having a problem with _sp_globals being an
				 undefined symbol.) */
				/* changed speedo => spdo_prv below, per bob eggers -mhd, 7/26/93 */
#include "spdo_prv.h"                 /* General definition for make_bmap */
				/* speedo -> spdo_prv */
#include "pre_proc.h"                  /* Font decryption keys */
#include "ufe.h"		/* Unified front end */

/* If it is on a PC with VGA dispaly card, you can set this variable to be 1 */
/* OH -- well we're not! -mhd
   #define PC_VGA		1
   */

#define MAX_BITS  256              /* Max line length of generated bitmap */

/***** GLOBAL FUNCTIONS *****/

/***** EXTERNAL FUNCTIONS *****/

/***** STATIC FUNCTIONS *****/

/***** STATIC VARIABLES *****/
static  char   pathname[100];      /* Name of font file to be output */
static  fix15  scan_lines;
static  ufix16 char_index;         /* Index of character to be generated */
static  ufix16 char_id;            /* Character ID */

static  fix15  raswid;             /* raster width  */
static  fix15  rashgt;             /* raster height */
static  fix15  offhor;             /* horizontal offset from left edge of emsquare */
static  fix15  offver;             /* vertical offset from baseline */
static  fix15  set_width;          /* character set width */
static  fix15  y_cur;              /* Current y value being generated and printed */
static  char   line_of_bits[2 * MAX_BITS + 1]; /* Buffer for row of generated bits */
static  char	test_string[374] ;
#if PC_VGA		 
#include <dos.h>
static  int		high_res ;
static  union REGS	regs ;
#endif

#if INCL_MULTIDEV
#if INCL_BLACK || INCL_SCREEN || INCL_2D
bitmap_t bfuncs = { sp_open_bitmap, sp_set_bitmap_bits, sp_close_bitmap };
#endif
#if INCL_OUTLINE
outline_t ofuncs = { sp_open_outline, sp_start_new_char, sp_start_contour, sp_curve_to,
                     sp_line_to, sp_close_contour, sp_close_outline };
#endif
#endif

#if (defined (M_I86CM) || defined (M_I86LM) || defined (M_I86HM) || defined (M_I86SM) || defined (M_I86MM))
  /* then have we are using a microsoft compiler */
#else
  /* need to have a dummy _fmalloc for unix */
void *_fmalloc()
{
}
#endif


/* generate shift-JIS test string */
static void kanji_SJ_testdata(string)
char* string;
{
	int index = 0, i ;

	for ( i = 255 ; i > 32 ; i-- )
	{
		if ( i < 0x80 || (( i >= 0xA0 ) && ( i < 0xE0 )) )
			string[index++] = (char) i ;
		else if ( ( i > 0x80 && i < 0x85 ) || ( i >= 0x88 && i < 0xA0 ) ||
				( i >= 0xE0 && i <= 0xEA ))
		{
			string[index++] = (char) i ;
			string[index++] = (char) 0x9f ; /* second ward */
			string[index++] = (char) i ;
			string[index++] = (char) 0x40 ; /* first ward */
		}
	}
	return ;	
}


FUNCTION void main(argc,argv)
int argc;
char *argv[];
{
char			ch;
ufix32  i;
char *font_name;
int count, index ;
real matrix[6];
ufix16 jis_code ;

#if REENTRANT_ALLOC
SPEEDO_GLOBALS* sp_global_ptr;
#endif


	/* check for proper usage */
	if (argc < 2) 
    {
#if PC_VGA		 
   	 fprintf(stderr,"Usage: ksample {mappingfile} {size} {V} \n\n"); 
#else
   	 fprintf(stderr,"Usage: ksample {mappingfile} {size} \n\n"); 
#endif 		 
	    exit (1);
    }

	sprintf(pathname, argv[1]);

	scan_lines = 24 ; /* default value */
	if (argc > 2 ) 
		sscanf(argv[2],"%hd",&scan_lines);
#if PC_VGA		 
	if (argc > 3) 
		high_res = 1 ;
	else 
		high_res = 0 ;
#endif 		 

	/* reset 4-in-1 to be DirectIndex and Speedo font */
   fi_reset(protoDirectIndex,procSpeedo);

	/* Load kanji font mapping file */
	if (kj_read_font_mapping(pathname))
    {
   	 printf("****** Cannot load font mapping file\n");
	    exit (1);
    }

#if DYNAMIC_ALLOC || REENTRANT_ALLOC
	sp_global_ptr = (SPEEDO_GLOBALS *)malloc(sizeof(SPEEDO_GLOBALS));
	memset(sp_global_ptr,(ufix8)0,sizeof(SPEEDO_GLOBALS));
#endif


	/* Initialization - set specs */  
	matrix[0] = ( (long) scan_lines ) <<16;
	matrix[1] = (real) 0.0;
	matrix[2] = (real) 0.0;
	matrix[3] = ( (long) scan_lines ) <<16;
	matrix[4] = (real) 0.0;
	matrix[5] = (real) 0.0;

#if PC_VGA		 
	if ( high_res )
	{
		/* set vga to be graphic mode */
		regs.x.ax = 0x0012;
		int86(0x10, &regs, &regs);
	}
#endif

	kanji_SJ_testdata(test_string);
	if (kj_set_kanji_specs(0,matrix))    /* Set character generation specifications */
    {
   	 printf("****** Cannot set requested specs\n");
    }
	else
	  {
	    index = 0 ;
	    while( test_string[index] != '\0' )
	      {
		kj_SJ_font_manager((ufix8) test_string[index],font_name,&count);
		if ( count == 2 )
		  char_index = (ufix16) ( (ufix8) test_string[index] << 8 ) + (ufix8) test_string[index+1]  ;
		else
		  char_index = (ufix8) test_string[index] ;
		index += count ;
		char_id = sp_get_char_id (char_index);
		if (char_id != 0)
		  {
		    if (!fi_make_char(&char_index))
		      {
			printf("****** Cannot generate character %d\n", char_index);
		      }
		  }
	      }
	    /* test JIS code */
	    printf("\n Press any key to continue for JIS code");
	    ch=getchar();
	    printf("%\n\n\n%c\n\n", ch);
	    /* display the fisrt character of every JIS ward */		
	    for ( i = 0 ; i < 84 ; i++)
	      {
		jis_code = 0x2121 + ( (ufix16) i << 8 ) ;
		char_index=JIS2SJ(jis_code);
		if ( kj_SJ2_font_manager(char_index,font_name,&count) == 0 )
		  {
		    char_id = sp_get_char_id (char_index);
		    if (char_id != 0)
		      {
			if (!fi_make_char(&char_index))
			  {
			    printf("****** Cannot generate character %d\n", char_index);
			  }
			printf ("jis %x : sj %x id %5d\n", jis_code, char_index, char_id);  
		      }
		  }
	      }
	  }

#if PC_VGA		 
	if ( high_res )
	{
		/* reset vga to be text mode */
		regs.x.ax = 0x0002;
		int86(0x10, &regs, &regs);
	}
#endif
}

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
fix15 i ;

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

#if PC_VGA		 
	if ( high_res )
	{
		/* set cursor position */
		regs.x.ax = 0x0200;
		regs.x.bx = 0;
		regs.x.dx = (int) ( scan_lines / 20 + 1 ) << 8 ;
		int86(0x10, &regs, &regs);
	}
#endif

printf("\nCharacter index = %x, ID = %d\n", char_index, char_id);
printf("set width = %3.1f, %3.1f\n", (real)x_set_width / 65536.0, (real)y_set_width / 65536.0);
printf("X offset  = %d\n", offhor);
printf("Y offset  = %d\n\n", offver);

#if PC_VGA		 
	if ( high_res )
	{
		fix15  j ;
		/* clear screen */
		regs.x.ax = 0x0c00;
		regs.x.bx = 0;
		for(i=0;i<scan_lines;i++)
		{
			regs.x.dx = (int) i ;
			for(j=0;j<scan_lines;j++)
			{
				regs.x.cx = (int) j ;
				int86(0x10, &regs, &regs);
			}
		}
	}
	else
#endif
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

#if PC_VGA
	if ( high_res )
	{
		regs.x.dx = (int) y ;
		regs.x.bx = 0 ;
		for(i=xbit1;i<xbit2;i++)
		{
			regs.x.ax = 0x0c0f;
			regs.x.cx = (int) i ;
			int86(0x10, &regs, &regs);
		}
	}
	else
#endif
	{
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

#if PC_VGA
	if ( !high_res )
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

#if 1 /* start of problem code! --mhd */
/* #define GetSFNTFunc ufix8* */
static	ufix8				*font_buffer = NULL; /* allocate only if needed */

GetSFNTFunc 	tt_get_font_fragment (clientID, offset, length)
  fix31  clientID, offset, length;

/* Returns a pointer to data extracted from the sfnt.
   Tt_get_font_fragment must be initialized in the fs_GlyphInputType
   record before fs_NewSfnt is called.  */
{
	return ((GetSFNTFunc)((ufix8 *)font_buffer+offset));
}

void tt_release_font_fragment (ptr)
  ufix8 *ptr;

/* Returns the memory at pointer to the heap
  */
{
	return;
}

boolean	fill_font_buffer(ptr, size, fp)
ufix8 **ptr;
ufix32 size;
FILE *fp;
{

	return FALSE;
} /* end of fill_font_buffer */

#endif /* end problem code! */


boolean get_byte(next_char)
char *next_char;
{
	short i;

	return FALSE;
}

