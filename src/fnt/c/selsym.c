/*****************************************************************************
*                                                                            *
*  Copyright 1993, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                           Other Patent Pending                             *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
*  Log:		selsym.c,v $						     *
*****************************************************************************/
/***************************** SELSYM. C ***********************************
 * This program demonstrates FIT table loading and use, symbol set selection
 * and accessing Resident Font Set glyphs using the FIT table to navigate
 * among them to find the missing characters.  The MSDOS code uses colors
 * on the screen to distinguish which fonts characters come from.  Symbol sets
 * are displayed in columns from 0-15 vertically in the 1st column, 16-31
 * in the second column and etc. The display should pretty much match the
 * symbol set table displays in the LaserJet III Technical Reference Manual.
 * When the /p option is used on the command line, a print spool file, "tmpout.bin"
 * is created in the current working directory.  If this file is copied
 * in binary mode to a LaserJet printer, the output will appear!
 *
 * Yes, the program links with all the processors and is a beast, although
 * nothing of Type1, PCL or TrueType is ever used.  But disconnecting
 * it would requiring rebuilding all object modules with the proper flags
 * like PROC_PCL 0, and etc.  This poses problems for the makefile to be
 * savvy enough to always remove the objects for the significant modules using
 * those flags, since MAKE won't be smart enough to know they need to be
 * rebuilt.  So trust us for now, and build it BIG.
 *
 * NOTE BENE!!!		 PLEASE NOTE!!!		ATTENTION!!!	ACHTUNG!!!
 *	This code build and runs only on the IBM PC, and has never been
 *	ported to any other platform.  However the guts of the FIT use
 *	in a real application is demonstrated below, and is worth a good reading.
*****************************************************************************/

/* !!!!!!!!!!!  RESTRICTED_ENVIRON NOT FUNCTIONING IN THIS .EXE !!!!! */

#include <stddef.h>
#include <stdio.h>
#include <setjmp.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>

#define SET_SPCS
#include "speedo.h"
#include "useropt.h"
#include "stdef.h"
#include "type1.h"
#include "fnt_a.h"
#include "tr_fdata.h"
#include "errcodes.h"
#include "hp_readr.h"
#include "finfotbl.h"
#include "ufe.h"		/* Unified front end */



/* possible color setting (IBM PC): */
enum {black, blue, green, cyan, red, magenta, brown, white, gray, light_blue, light_green,\
      light_cyan, light_red, light_magenta, yellow, intense_white}color_list;

#define MAX_BITS  256              /* Max line length of generated bitmap */
#define VIDEO_MAX 480
#define MAX_STRING 1000
#define MAX_FONTS	13
#define CHAR_BUFFER_SIZE 2000      /* Size of character buffer */

/* change these to suit yourself! */
#define PRIMARY_COLOR   red
#define SECONDARY_COLOR gray
#define TERTIARY_COLOR  light_red

struct {
   char pathname[100];
   ufix8  *font_buffer; /* Font buffer */
   ufix32 filesize;
   buff_t font;               /* Buffer descriptor for font data */
   FILE   *fdescr;            /* Fontware outline file descriptor */
   } file_options[MAX_FONTS];

/***** STATIC FUNCTIONS *****/
static	void	setup_speedo_font(void);
static	fix15 	read_2b(ufix8 *pointer);
static   void delay ( clock_t wait );
int main(int argc, char *argv[]);
static   boolean fit_load(char *fileName);
static   char *BuildFontFileName(ufix32 fontNum);

/* vga driver */
static void vga_CLS(void);
static void set_backgd(void);
static void vga_hline(int x, int y, int length);



/***** STATIC VARIABLES *****/
#if DEBUG
#define SHOW(X) printf("X = %d\n", X)
#else
#define SHOW(X)
#endif


/* the global FIT table (big enough for N_LOGICAL_FONTS): */
FontInfoType gFontInfoTable[N_LOGICAL_FONTS];

ufix16 	fontNo, saveFontIdx, font_idx, theCharID, curIdx, nextCode;
ufix16   no_fonts, fontsFound;
boolean imagedCharacter;
int first_char_index;             /* Index of first character in font */
fix31 bytes_read;
specs_t specs;                    /* Bundle of character generation specs */
ufix16 gFitIndex, gNFitFonts;	/* the curr index and number total in FIT table */
char strBuf[128];
char fontRoot[] = "font";
static	ufix16 spaceID = 32;

static	char	ssname[10];      /* Name of font file to be output */
char 	  *fontPtr;

static  	fix15  raswid;             /* raster width  */
static  	fix15  rashgt;             /* raster height */
static  	fix15  offhor;             /* horizontal offset from left edge of emsquare */
static  	fix15  offver;             /* vertical offset from baseline */
static  	fix15  y_cur;              /* Current y value being generated and printed */
static  	char   line_of_bits[2 * MAX_BITS + 1]; /* Buffer for row of generated bits */
static  	fix15  scan_lines;
static   char   title_str[64];
static   int    color_code;
static	ufix16 char_index;
static	ufix8		  *character; /* can either be a charname for type1 */
							/* or a char index for speedo and tt */
static  int		x_dev, y_dev ;
static   short level;

static	eFontProcessor	font_type;
static	eFontProtocol	font_protocol;
static	ufix8				*font_buffer = NULL; /* allocate only if needed */
static	ufix32			fontbuf_size; /* size of font buffer */
static	specs_t			gspecs;
static	buff_t			gbuff;



#if RESTRICTED_ENVIRON
static	ufix8 	*font_ptr;
static 	ufix16 	buffer_size;
static	unsigned char big_buffer[10240];
			/* temp buffer to store char string */
#else
static	font_data *font_ptr;
#endif

static	FILE *font_fp = NULL;

#define PROOF_CHAR_HEIGHT 16
#ifdef OLDWAY
#define PT_PER_INCH 72.2892
#else
#define PT_PER_INCH 72.307
#endif
#define swp16(X) X = (X << 8) | ((X >> 8)&0xFF)

#include "hpf.h"        /* hp soft font defs */

/* the char set name, default Roman 8 */
static char char_set_name[32] = "8U";
static int hp_char_id;			/* tag for each bitmap downloaded to printer */
static int pointsize;
static HPF_HEAD hpfhd;			/* hp header struct */
static HPF_CHARDIR hpfcdir;	/* ?? */
static FILE    *hpf_fp;		/* hp soft font output file descriptor */
static boolean do_proof;
static ufe_struct	tspecs;

char transdata[] = "\33&p1X";
static  fix15  space_char;
static  fix15  space_width;
static  fix15 _gxmin = 1000;
static  fix15 _gymin = 1000;
static  fix15 _gxmax = 1000;
static  fix15 _gymax = 1000;
static  ufix16 bitrow[MAX_BITS/16];
static fix31 gBitmapWidth;


#if INTEL
ufix16 endmask[16] = {  0x0000, 0x0080, 0x00C0, 0x00E0,
0x00F0, 0x00F8, 0x00FC, 0x00FE,
0x00FF, 0x80FF, 0xc0FF, 0xE0FF,
0xF0FF, 0xF8FF, 0xFCFF, 0xFEFF};
ufix16 startmask[16] = {0xFFFF, 0xFF7F, 0xFF3F, 0xFF1F,
0xFF0F, 0xFF07, 0xFF03, 0xFF01,
0xFF00, 0x7F00, 0x3F00, 0x1F00,
0x0F00, 0x0700, 0x0300, 0x0100};
#else   /* Anything else */
ufix16 endmask[16] = {  0x0000, 0x8000, 0xC000, 0xE000,
0xF000, 0xF800, 0xFC00, 0xFE00,
0xFF00, 0xFF80, 0xFFC0, 0xFFE0,
0xFFF0, 0xFFF8, 0xFFFC, 0xFFFE};
ufix16 startmask[16] = {0xFFFF, 0x7FFF, 0x3FFF, 0x1FFF,
0x0FFF, 0x07FF, 0x03FF, 0x01FF,
0x00FF, 0x007F, 0x003F, 0x001F,
0x000F, 0x0007, 0x0003, 0x0001};
#endif /* MSDOS or Anything BUT MSDOS */

/* function prototypes for proofing utilities */
void new_hpfhd(HPF_HEAD *);
void swap_cdir(HPF_CHARDIR *);
void hp_proof_prologue();
void hpwc(char *);
void layout ();
void hp_proof_epilog();

fix31 SetWidthToPixelWidth(fix31 set_width);

/*** extern variables ***/
extern   eFontProtocol gCharProtocol;	/* global protocol of character selection */


/* end proofing WIP */

/*****************************************************************************
 * main()
 *   process command line arguments (which symbol set and 
 *   whether to printer or screen).
 *
 *	This program is bound to using these fonts, in the current working directory:
 *		font3150.spd	[Dutch 801 Roman-SWC]
 *		font3158.spd	[Serif support Supplement Medium-SWC
 *		font3162.spd	[PC Support Supplement-SWC]
 *
 *	It is also bound to using a FIT table describing the Core 13 fonts named:
 *		hplj3.bin
 *
 *	This file must first be created using the FITUTIL program built in the
 *	../fitutil sub-directory.  After running that program, select item 1
 *	on the menu, accept the default file name suggestion by hitting ENTER,
 *	then quit the fitutil by choosing the last choice on the menu.  Take the
 *	file it creates, hplj3.bin, and place it in the current working directory
 *	with the above named font files, then you're set to run this program.
 *
 *	Please note: on the IBM PC, this program and the fitutil.exe program must
 *	both be built using the same memory model for the FIT file image to be
 *	padded the same way for both!
 *
 ****************************************************************************/
FUNCTION int	main(argc,argv)
int argc;
char *argv[];
{
	boolean  		 	getoutchar;
	unsigned char ch;
	union REGS	regs;
   ufix16   char_id, ssid;
   int hor_offset;
   ufix16   char_per_font;
   int number, i;
   char letter[2];

	/* check for proper usage */
	if (argc < 2 || argc > 3) 
   {
      printf("Usage:  selsym <symbol set> [/s] [/p]\n"); 
      printf("        use /s for screen output\n");
      printf("        use /p for printer output\n");
	   exit (1);
   }

   sscanf(argv[1], "%d%c", &number, letter);
   ssid = (ufix16)(number*32+letter[0]-'@');	     
   strcpy(ssname, argv[1]);
   
   if ( strncmp(argv[2], "/p", 2) == 0)
   {
		pointsize = PROOF_CHAR_HEIGHT;
      scan_lines = 300 / PT_PER_INCH * pointsize;
      do_proof = TRUE;
   }
   else if ( strncmp(argv[2], "/s", 2) == 0)
         scan_lines = 27;
   else
   {
      printf("Usage:  selsym <symbol set> [/s] [/p]\n"); 
      printf("        use /s for screen output\n");
      printf("        use /p for printer output\n");
      exit(1);
   }

   if (!do_proof)
   {
      printf("\n\nafter viewing the symbol set on the screen,\n");
      printf("press any key to go back to text mode\n\n");
      delay((clock_t)3 * CLOCKS_PER_SEC );
   }

   font_protocol = protoBCID;
   fi_reset(font_protocol, procSpeedo);
   if ( fit_load("hplj3.bin") )
   {/* success loading up the FIT table fragment from disk: */
      if (fontPtr = gFontInfoTable[5].addr)
      {
		if (!fi_select_symbol_set(PARAMS2 ssid))
		{/* oops! */
   			fprintf(stderr, "\nCannot find symbol set %d\n", ssid);
   			exit (1);
		}
         else
         {/* OK! */
            font_idx = 5;
            setup_speedo_font();
            if (do_proof == TRUE)
            {/* output to the printer/spool file: tmpout.bin */
					space_width = fi_get_char_width(&spaceID);
					if (!space_width)
						space_width = ((sp_globals.metric_resolution << 16) +
										(sp_globals.metric_resolution >> 1)) /
										sp_globals.metric_resolution;
					gBitmapWidth = SetWidthToPixelWidth(space_width);
					hp_proof_prologue();
            }
            else
            {/* as Picard says, "On-screen!" */
      	   	/* set vga to be graphic mode */
         		regs.x.ax = 0x0012;
         		int86(0x10, &regs, &regs);
               set_backgd();
               hor_offset = 15;
               space_width = (640 - 2*hor_offset - 16*scan_lines) / 15;
         		y_dev = scan_lines ;
               x_dev = hor_offset ;
               color_code = PRIMARY_COLOR;
			}
            saveFontIdx = font_idx;
				for (i = 0; i < 256; i++)
				{  /* for each symbol set character */
					if (do_proof)
                   hp_char_id = i; /* set for download functions */
               else
               {
                  if ( i != 0 && i % 16 == 0 )
                  {
            			x_dev += scan_lines + space_width ;
               		y_dev = scan_lines ;
                  }
               }
					imagedCharacter = FALSE;
					if (sp_globals.gCurrentSymbolSet[i] != UNKNOWN)
					{
						theCharID = sp_globals.gCurrentSymbolSet[i];
						gBitmapWidth = SetWidthToPixelWidth(fi_get_char_width(&theCharID));
						imagedCharacter =
							fi_make_char(&theCharID);
					}
					if (!imagedCharacter &&
							(sp_globals.gCurrentSymbolSet[i] != UNKNOWN))
					{/* go looking for it */
						curIdx = font_idx;
						nextCode = gFontInfoTable[curIdx].nextSearchEncode;
                  level = 0;
						while(!imagedCharacter && (!(nextCode & NEXT_NONE)))
						{/* while not at end of encoded tree search: */
							if (nextCode & NEXT_ABSTARG)
							{/* next target is absolute -> core RFS */
								curIdx = (nextCode ^= NEXT_ABSTARG);
							}
							else if (nextCode & NEXT_RELTARG)
								/* next target relative to current pos */
							{
								curIdx += (char)(nextCode ^= NEXT_RELTARG);
							}
					   	font_idx = curIdx;
							setup_speedo_font();	/* sp_set_specs() */
							/*
							 *	Again, try making a char from font
							 *	[curIdx]:
							*/
							gBitmapWidth = SetWidthToPixelWidth(fi_get_char_width(&theCharID));
                     color_code = (level > 0) ? TERTIARY_COLOR : SECONDARY_COLOR;
							imagedCharacter =
								fi_make_char(&theCharID);
							nextCode =
								gFontInfoTable[curIdx].nextSearchEncode;
                     level++;
					  	}/* eo while */
						/* restore original font_idx */
						font_idx = saveFontIdx; 
                  color_code = PRIMARY_COLOR;
						setup_speedo_font();	/* sp_set_specs() */
					} /* end if */
               if (!do_proof)
            		y_dev += scan_lines + 2;
				} /* end for */
            if (do_proof)  /* create the layout, close the proof file */
               hp_proof_epilog();
            else
            {
     	   		/* set cursor position */
     	   		regs.x.ax = 0x0200;
     	   		regs.x.bx = 0;
        			regs.x.dx = (int) 0x1c00 ;
     	   		int86(0x10, &regs, &regs);

         		/* press key to go back to text mode */
          		ch=getch();
         		vga_CLS();
		         /* reset vga to be text mode */
         		regs.x.ax = 0x0002;
         		int86(0x10, &regs, &regs);
            }
            exit(0);
         }
      } /* if */
      for (i=0; i < fontsFound; i++)
      {/* goodbye files and memory */
         if (file_options[i].fdescr)
   			fclose(file_options[i].fdescr);     
		   if (file_options[i].font_buffer)
            free(file_options[i].font_buffer);
      }            
   } /* if fit_load succeeded */
   else
   {/* vociferous error message */
	  fprintf(stderr, "Unable to find FIT binary file: hplj3.bin\n");
	  fprintf(stderr, "  To create this file, run FITUTIL program,\n");
	  fprintf(stderr, "  choose menu item #1, type ENTER to accept\n");
	  fprintf(stderr, "  the default file name, then choose menu item #12\n");
	  fprintf(stderr, "  to quit.  Copy the file hplj3.bin to this directory.\n");
   }
   exit(TRUE);
}  /* end of main function */



/******************************************************************************
*	setup_speedo_font()
*	sets up transformation matrix and specs, calls fi_set_specs()
*	RETURNS:	nothing
******************************************************************************/
FUNCTION static void setup_speedo_font()
{
	fix15 i;
	ufe_struct tspecs;




#if DEBUG
   if (bytes_read == bytes_available)
      fprintf(stderr, "Font data partially loaded\n");
   else
      fprintf(stderr, "Font data loaded\n");
#endif               

   file_options[font_idx].font.org = file_options[font_idx].font_buffer;
   file_options[font_idx].font.no_bytes = bytes_read;
   first_char_index = read_2b(file_options[font_idx].font_buffer + FH_FCHRF);

   specs.pfont = &file_options[font_idx].font; 
	specs.xxmult = (long)scan_lines << 16;
	specs.xymult = 0L << 16;      /* Coeff of Y to calculate X pixels */
	specs.xoffset = 0L << 16;     /* Position of X origin */
	specs.yymult = (long)scan_lines << 16;
	specs.yxmult = 0L << 16;      /* Coeff of X to calculate Y pixels */
	specs.yoffset = 0L << 16;     /* Position of Y origin */
	specs.flags = MODE_SCREEN;     /* Mode flags */
	specs.out_info = 0;           /* Output module information  */

	tspecs.Gen_specs = &specs;	/* load intermediary struct */

		/* Set character generation specifications */
	if (!fi_set_specs(&tspecs))
   {
      	/* e.g., not a Speedo font */
		fprintf(stderr, "Cannot set requested specs\n");    
		exit(1);
	}
}



#if REENTRANT_ALLOC
FUNCTION  void sp_report_error(sp_global_ptr,n)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_report_error(n)
#endif
fix15 n;        /* Error identification number */
/*
 * Called by character generator to report an error.
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

		case TR_NO_ALLOC_FONT:
    		break;

		case TR_NO_SPC_STRINGS:
     		printf("*** Cannot malloc space for charstrings \n");
     		break;

		case TR_NO_SPC_SUBRS:
     		printf("*** Cannot malloc space for subrs\n");
     		break;

		case TR_NO_READ_SLASH:
     		printf("*** Cannot read / before charactername in Encoding\n");
     		break;

		case TR_NO_READ_STRING:
     		printf("*** Cannot read / or end token for CharString\n");
     		break;

		case TR_NO_READ_FUZZ:
     		printf("*** Cannot read BlueFuzz value\n");
     		break;

		case TR_NO_READ_SCALE:
     		printf("*** Cannot read BlueScale value\n");
     		break;

		case TR_NO_READ_SHIFT:
     		printf("*** Cannot read BlueShift value\n");
     		break;

		case TR_NO_READ_VALUES:
     		printf("*** Cannot read BlueValues array\n");
     		break;

		case TR_NO_READ_ENCODE:
     		printf("*** Cannot read Encoding index\n");
     		break;

		case TR_NO_READ_FAMILY:
     		printf("*** Cannot read FamilyBlues array\n");
     		break;

		case TR_NO_READ_FAMOTHER:
     		printf("*** Cannot read FamilyOtherBlues array\n");
     		break;

		case TR_NO_READ_BBOX0:
     		printf("*** Cannot read FontBBox element 0\n");
     		break;

		case TR_NO_READ_BBOX1:
     		printf("*** Cannot read FontBBox element 1\n");
     		break;

		case TR_NO_READ_BBOX2:
     		printf("*** Cannot read FontBBox element 2\n");
     		break;

		case TR_NO_READ_BBOX3:
     		printf("*** Cannot read FontBBox element 3\n");
     		break;

		case TR_NO_READ_MATRIX:
     		printf("*** Cannot read FontMatrix\n");
     		break;

		case TR_NO_READ_NAMTOK:
     		printf("*** Cannot read FontName / token\n");
     		break;

		case TR_NO_READ_NAME:
     		printf("*** Cannot read FontName\n");
     		break;

		case TR_NO_READ_BOLD:
     		printf("*** Cannot read ForceBold value\n");
     		break;

		case TR_NO_READ_FULLNAME:
     		printf("*** Cannot read FullName value\n");
     		break;

		case TR_NO_READ_LANGGRP:
     		printf("*** Cannot read LanguageGroup value\n");
     		break;

		case TR_NO_READ_OTHERBL:
     		printf("*** Cannot read OtherBlues array\n");
     		break;

		case TR_NO_READ_SUBRTOK:
     		printf("*** Cannot read RD token for subr\n");
     		break;

		case TR_NO_READ_STRINGTOK:
     		printf("*** Cannot read RD token in charstring\n");
     		break;

		case TR_NO_READ_STDHW:
     		printf("*** Cannot read StdHW value\n");
     		break;

		case TR_NO_READ_STDVW:
     		printf("*** Cannot read StdVW value\n");
     		break;

		case TR_NO_READ_SNAPH:
     		printf("*** Cannot read StemSnapH array\n");
     		break;

		case TR_NO_READ_SNAPV:
     		printf("*** Cannot read StemSnapV array\n");
     		break;

		case TR_NO_READ_BINARY:
     		printf("*** Cannot read binary data size for Subr\n");
     		break;

		case TR_NO_READ_EXECBYTE:
     		printf("*** Cannot read a byte after eexec\n");
     		break;

		case TR_NO_READ_CHARNAME:
     		printf("*** Cannot read charactername\n");
     		break;

		case TR_NO_READ_STRINGBIN:
     		printf("*** Cannot read charstring binary data\n");
     		break;

		case TR_NO_READ_STRINGSIZE:
     		printf("*** Cannot read charstring size\n");
     		break;

		case TR_NO_READ_DUPTOK:
     		printf("*** Cannot read dup token for subr\n");
     		break;

		case TR_NO_READ_ENCODETOK:
     		printf("*** Cannot read dup, def or readonly token for Encoding\n");
     		break;

		case TR_NO_READ_EXEC1BYTE:
     		printf("*** Cannot read first byte after eexec\n");
     		break;

		case TR_NO_READ_LENIV:
     		printf("*** Cannot read lenIV value\n");
     		break;

		case TR_NO_READ_LITNAME:
     		printf("*** Cannot read literal name after /\n");
     		break;

		case TR_NO_READ_STRINGNUM:
     		printf("*** Cannot read number of CharStrings\n");
     		break;

		case TR_NO_READ_NUMSUBRS:
     		printf("*** Cannot read number of Subrs\n");
     		break;

		case TR_NO_READ_SUBRBIN:
     		printf("*** Cannot read subr binary data\n");
     		break;

		case TR_NO_READ_SUBRINDEX:
     		printf("*** Cannot read subr index\n");
     		break;

		case TR_NO_READ_TOKAFTERENC:
     		printf("*** Cannot read token after Encoding\n");
     		break;

		case TR_NO_READ_OPENBRACKET:
     		printf("*** Cannot read { or [ in FontBBox\n");
     		break;

		case TR_EOF_READ:
     		printf("*** End of file read\n");
     		break;

		case TR_MATRIX_SIZE:
     		printf("*** FontMatrix has wrong number of elements\n");
     		break;

		case TR_PARSE_ERR:
     		printf("*** Parsing error in Character program string\n");
     		break;

		case TR_TOKEN_LARGE:
     		printf("*** Token too large\n");
     		break;

		case TR_TOO_MANY_SUBRS:
     		printf("*** Too many subrs\n");
     		break;

		case TR_NO_SPC_ENC_ARR:
     		printf("*** Unable to allocate storage for encoding array \n");
     		break;

		case TR_NO_SPC_ENC_ENT:
     		printf("*** Unable to malloc space for encoding entry\n");
     		break;

		case TR_NO_FIND_CHARNAME:
     		printf("*** get_chardef: Cannot find char name\n");
     		break;

		case TR_INV_FILE:
     		printf("*** Not a valid Type1 font file\n");
     		break;

		case TR_BUFFER_TOO_SMALL:
     		printf("*** Buffer provided too small to store essential data for type1 fonts \n");
     		break;

		case TR_BAD_RFB_TAG:
     		printf("*** Invalid Tag found in charactaer data\n");
     		break;

		default:
    		break;
	}
	return ;
} /* end of sp_report_error */


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
* Called by character generator to initialize a buffer prior
* to receiving bitmap data.
*/
{

#if DEBUG
	printf("open_bitmap(%3.1f, %3.1f, %3.1f, %3.1f, %d, %d)\n",
   	 (real)x_set_width / 65536.0, (real)y_set_width / 65536.0,
	    (real)xorg / 65536.0, (real)yorg / 65536.0, (int)xsize, (int)ysize);
#endif

   if (do_proof == TRUE)
   {
	   /* create a HP soft font from the speedo font */
      ufix16 size;
      fix15 xmin, ymin, xmax, ymax;
      ufix32 bitmapWidth;

      raswid = xsize;
      rashgt = ysize;
      offhor = (xorg + 0x8000) >> 16;  /* round it */
      offver = yorg >> 16;
   
      xmin = offhor;
      ymin = offver;
      xmax = xmin + xsize - 1;
      ymax = ymin + ysize - 1;
   
      if (raswid > MAX_BITS)
          raswid = MAX_BITS;
   
      hpfcdir.format = 4;
      hpfcdir.continuation = 0;
      hpfcdir.size = 14;
      hpfcdir.class = 1;
      hpfcdir.orientation = 0;
      hpfcdir.reserved = 0;
      hpfcdir.xoff = offhor;
      hpfcdir.yoff = offver + rashgt;
   
      bitmapWidth = gBitmapWidth;
      hpfcdir.set_width = bitmapWidth * 4;
   
      hpfcdir.width = raswid;
      hpfcdir.height = rashgt;
   
   
#if INTEL
swap_cdir(&hpfcdir);
#endif
      if (xmin < _gxmin) _gxmin = xmin;
      if (ymin < _gymin) _gymin = ymin;
      if (xmax > _gxmax) _gxmax = xmax;
      if (ymax > _gymax) _gymax = ymax;
   
      size = (((raswid + 7)/8) * rashgt);
      if (size == 0)
      {
        size = 1;
        hpfcdir.width = 8;
        hpfcdir.height = 1;
      }
   
   	/* write out character header informaton... */
      fprintf(hpf_fp, ESC_CHARID, hp_char_id);	/* character ID... */
      fprintf(hpf_fp, ESC_CHARDATA, size+sizeof(hpfcdir));	/* length of data... */
      fwrite(&hpfcdir, 1, sizeof(hpfcdir), hpf_fp);	/* ... and actual binary data */
      if (raswid <= 0)
       {
          y_cur = 0;
          fwrite(&y_cur,1,1,hpf_fp);
       }
      y_cur = 0;
   } /* end do_proof */
   else
   {
      raswid = xsize;
      rashgt = ysize;
      offhor = (fix15)((xorg + 0x8000) >> 16);  /* round it */
      offver = (fix15)(yorg >> 16);

      if (raswid > VIDEO_MAX)
          raswid = VIDEO_MAX;

#if DEBUG
printf("\nCharacter index = %x, ID = %d\n", (unsigned char) char_index, char_id);
printf("set width = %3.1f, %3.1f\n", (real)x_set_width / 65536.0, (real)y_set_width / 65536.0);
printf("X offset  = %d\n", offhor);
printf("Y offset  = %d\n\n", offver);
#endif

      y_cur = 0;
   }
} /* end of sp_open_bitmap */


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
* Called by character generator to write one row of pixels 
* into the generated bitmap character.                               
*/
{
	short i;
   fix15 length;
	union REGS	regs;

#if DEBUG
	printf("set_bitmap_bits(%d, %d, %d)\n", (int)y, (int)xbit1, (int)xbit2);
#endif


   if (do_proof == TRUE)
   {
   	fix15 first_word, last_word;
	   fix15 bytwid;

	/* Add character date to the current HP soft font */
#if DEBUG
	printf("set_bitmap_bits(%d, %d, %d)\n", (int)y, (int)xbit1, (int)xbit2);
#endif

		/* Clip runs beyond end of buffer */
   	if (xbit1 > MAX_BITS)
	       xbit1 = MAX_BITS;

   	if (xbit2 > MAX_BITS)
   	    xbit2 = MAX_BITS;

		/* Output backlog lines if any */
   	while (y_cur != y) {
			/* put out last bit row */
   		bytwid = (raswid + 7) / 8;

	   	fwrite(bitrow,1,bytwid,hpf_fp);

		   for (i = 0; i < (bytwid+1)/2; i++) {
			   bitrow[i] = 0;
   		}
	   	y_cur++;
   	}

	/* Add bits to current line */
	   first_word = xbit1>>4;
   	last_word = xbit2>>4;
   	if (first_word == last_word) {
	   	bitrow[first_word] |= (startmask[xbit1&0xF] & endmask[xbit2&0xF]);
		   return;
   	}

	   bitrow[first_word++] |= startmask[xbit1&0xF];
   	while (first_word < last_word) {
	   	bitrow[first_word++] = 0xFFFF;
   	}

	   if ((xbit2&0xF) != 0)
		   bitrow[last_word] |= endmask[xbit2&0xF];
   } /* end do_proof */
   else  /* output to screen */
   {
	/* Clip runs beyond end of buffer */
	   if (xbit1 > VIDEO_MAX)
   	    xbit1 = VIDEO_MAX;
   	if (xbit2 > VIDEO_MAX)
      	 xbit2 = VIDEO_MAX;
      
	length = xbit2-xbit1+1 ;

   if (x_dev + offhor + xbit1 + length > 640)
      length = 640 - x_dev -xbit1;

	vga_hline(x_dev+offhor+xbit1,y_dev-rashgt-offver+y,length);

   }

} /* sp_set_bitmap_bits */


#if REENTRANT_ALLOC
FUNCTION void sp_close_bitmap(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION void sp_close_bitmap()
#endif
/* 
 * Called by character generator to indicate all bitmap data
 * has been generated.
 */
{
#if DEBUG
	printf("close_bitmap()\n");
#endif

if (do_proof == TRUE)
{
	unsigned int i;
	int bytwid;

		/* close the newly created HP soft font file */
#if DEBUG
	printf("close_bitmap()\n");
#endif

	bytwid = (raswid + 7) / 8;

	fwrite(bitrow,1,bytwid,hpf_fp);

	for (i = 0;i < (bytwid+1)/2;i++)
		bitrow[i] = 0;

	while (y_cur != rashgt) {
		/* put out last bit row */
		bytwid = (raswid + 7) / 8;
		fwrite(bitrow,1,bytwid,hpf_fp);
		y_cur++;
	}

	return;
} /* end do_proof */

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
 * Called by character generator to initialize prior to
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
 * Called by character generator to initialize prior to
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
 * Called by character generator at the start of each contour
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
 * Called by character generator onece for each curve in the
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
 * Called by character generator onece for each vector in the
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
 * Called by character generator at the end of each contour
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
 * Called by character generator at the end of output of the
 * scaled outline of the character.
 */
{
	printf("close_outline()\n");
}
#endif


FUNCTION fix15 read_2b(pointer)
ufix8 *pointer;
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
ufix8 *pointer;
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


/* end of "sp_" routines */


FUNCTION boolean get_byte(next_char)
char *next_char;
{
	short i;

	/* file_pos = ftell(font_fp); */
	if ((i = getc(font_fp))== EOF)
    	return FALSE;
	*next_char = (char)i;
	return TRUE;
}




/******************************************************************************
*	tt_get_font_fragment()
*	RETURNS:	pointer to font fragment requested from TrueType processor.
******************************************************************************/
FUNCTION GetSFNTFunc 	tt_get_font_fragment (clientID, offset, length)
  fix31  clientID, offset, length;

/* Returns a pointer to data extracted from the sfnt.
   tt_get_font_fragment must be initialized in the fs_GlyphInputType
   record before fs_NewSfnt is called.  */
{
	return ((GetSFNTFunc)((ufix8 *)font_buffer+offset));
}

/******************************************************************************
*	tt_release_font_fragment()
*	RETURNS:	nothing
******************************************************************************/
FUNCTION void tt_release_font_fragment (ptr)
  ufix8 *ptr;

/* Returns the memory at pointer to the heap
  */
{
	return;
}

/******************************************************************************
*	sp_load_char_data()
*	RETURNS:	bogus pointer (this is a dymmy function)
******************************************************************************/

FUNCTION buff_t STACKFAR * WDECL sp_load_char_data(file_offset, no_bytes, cb_offset)
fix31    file_offset;  /* Offset in bytes from the start of the font file */
fix15    no_bytes;     /* Number of bytes to be loaded */
fix15    cb_offset;    /* Offset in bytes from start of char buffer */
{
	/* DUMMY FUNCTION */
	buff_t *it;
	return(it);
}


/******************************************************************************
*	SetWidthToPixelWidth()
*	given a set width in units of 64K (0..65536) calulate the pixel width
*	RETURNS:	pixel width
******************************************************************************/
FUNCTION fix31 SetWidthToPixelWidth(fix31 set_width)
{
	fix31 pixel_width = 0; /* assume no width */
	ufix32 mult;

   if (!set_width)
   	return(pixel_width); /* already 0 */
  	mult = ABS(tspecs.Gen_specs->xxmult) + ABS(tspecs.Gen_specs->yxmult);
	/* now calculate the width from sp_get_char_width() call */
	set_width *= sp_globals.metric_resolution;
	set_width -= (sp_globals.metric_resolution >> 1);
	set_width = (set_width >> 16);
/* multiply RFS setwidth times high-order word of mult, add setwidth times low order word,
   add roundoff and divide by setwidth resolution units to get pixel width */
   pixel_width = (fix15)(fix31)(((fix31)set_width * (mult >> 16) + 
                               (((fix31)set_width * (mult & 0xffffL) ) >> 16) +
                               (sp_globals.metric_resolution >> 1)) / sp_globals.metric_resolution);

	return pixel_width;
}




/******************************************************************************
*	hp_proof_prologue()
*	RETURNS:	nothing
******************************************************************************/
FUNCTION void hp_proof_prologue()
{

		/* open output hpf, write header */
	hpf_fp = fopen("tmpout.bin", "wb");
	if (hpf_fp == NULL) {
		fprintf(stderr,"Error, cannot open proof file tmpout.bin\n");
		exit(1);
	}

   hpwc("\033E");

		/* make this soft font 100 */
	hpwc (ESC_ASSIGN_FONT_100);

		/* compose soft font header struct */
	new_hpfhd(&hpfhd);

		/* write out "here comes new soft font header" in PCL'ease */
	hpwc (ESC_FONTHEAD);

		/* write out the struct stuffed in new_hpfhd() */
	fwrite((char *)&hpfhd, 1, sizeof(hpfhd), hpf_fp);

	return;
}

/******************************************************************************
*	hp_proof_epilog()
*	RETURNS:	nothing
******************************************************************************/
FUNCTION void hp_proof_epilog()
{
		/* make the downloaded font permanent */
	hpwc (ESC_MAKE_FONT_PERM);
		/* select the downloaded font for use */
	hpwc (ESC_SELECT_FONT_100);

		/* create the proof sheet */
	layout ();


   hpwc("\33E\33*c0F");

		/* finished, restore order to the Shire... */
	fclose(hpf_fp);

	return;
}



/******************************************************************************
*	layout()
*	RETURNS:	nothing
******************************************************************************/
FUNCTION void layout ()
{
	int	i, j, hor_nr;
	char command[200];

   sprintf(title_str, "Symbol Set %s", ssname);
   sprintf(command,"\033*p150X\033*p50Y\33(0U\33(s1p16v0s3b4101T%s", title_str);
   hpwc(command);
   sprintf(command,"\033*p1920X\033*p50Y\33(s12v0B%s", "Bitstream, Inc.");
   hpwc(command);

   hor_nr = 16;

   hpwc("\033*p175X\033*p275Y");
  	hpwc (ESC_SELECT_FONT_100);

   sprintf(command, "\33&k%.4fH", 120.0/(16.0/7.0) );
  	hpwc(command);

   sprintf(command, "\33&l%.4fC", (9.25/16)*48 );
  	hpwc(command);


 
   for (j=0; j < 16; j++)
   {
      for (i=0; i < 16; i++)
      {
         fprintf(hpf_fp, "%s%c",transdata,j+16*i);
      }       
      hpwc("\033*p180X");		
      hpwc("\033&a+1R");	/* move down one line */
  }   

   hpwc("\33(0U\33(s0p10h12v0s0b3T");

   sprintf(command, "\33&k%.4fH", 120.0/(16.0/7.0) );
  	hpwc(command);

   sprintf(command, "\33&l%.4fC", (9.25/16)*48 );
  	hpwc(command);

   hpwc("\033*p195X\033*p150Y");
   for (i=0; i < 10; i++)
   {
      sprintf(command,"%d",i);
      hpwc(command);
   }       
   for (i=65; i < 71; i++)
   {
      sprintf(command,"%c",i);
      hpwc(command);
   }       
   hpwc("\033*p100X\033*p275Y");
   for (i=0; i < 10; i++)
   {
      sprintf(command,"%d",i);
      hpwc(command);
      hpwc("\033*p100X");		
      hpwc("\033&a+1R");	/* move down one line */
   }       
   for (i=65; i<71; i++)
   {
      sprintf(command,"%c",i);
      hpwc(command);
      hpwc("\033*p100X");		
      hpwc("\033&a+1R");	/* move down one line */
   }       

	return;
} /* end layout() */                       


/* write a hp command string to the proof file */
FUNCTION void hpwc(char *command)
{
	fprintf (hpf_fp, command);

	return;
}


/******************************************************************************
*	new_hpfhd()
*	initialize a new PCL5 soft font header for download
*	RETURNS:	nothing
******************************************************************************/
FUNCTION void new_hpfhd(HPF_HEAD *p)
{
fix15 pixel_width;
ufix32 em_ratio = (ufix32)(space_width/65536);
ufix32 fixed_ratio = (ufix32)(PROOF_CHAR_HEIGHT/PT_PER_INCH * 1200);


	pixel_width = gBitmapWidth;

    p->size = 64;
    p->font_type = 2; /* 0 = ascii 1 = roman8 2 = pc8 */
    p->baseline = 0.764 * (PROOF_CHAR_HEIGHT * 300/PT_PER_INCH);
    p->cell_width = _gxmax = _gxmin;
    p->cell_height = _gymax = _gymin;
    p->orient = 0;  /* portrait */
    p->spacing = 0; /* fixed */
   
    p->symbol_set = 21; /* ascii */
    p->pitch = pixel_width*4; /* set as quarter-dots */
    p->height = PROOF_CHAR_HEIGHT * 1200 / PT_PER_INCH;
    p->x_height = 0;
    p->width_type = 0;
    p->style = 0;
    p->stroke_weight = 0;
    p->typeface = 0;
    p->serif_style = 0;
    p->text_height = p->height;
    p->text_width = p->pitch;
    strcpy(p->name,"Speedo Test");
#if INTEL
    swp16(p->size);
    swp16(p->baseline);
    swp16(p->cell_width);
    swp16(p->cell_height);
    swp16(p->symbol_set);
    swp16(p->pitch);
    swp16(p->height);
    swp16(p->x_height);
    swp16(p->text_height);
    swp16(p->text_width);
#endif

	return;
}

/******************************************************************************
*	swap_cdir()
*	byte swap appropriate fields of the font header
*	RETURNS:	nothing
******************************************************************************/
FUNCTION void swap_cdir(HPF_CHARDIR *p)
{
    swp16(p->xoff);
    swp16(p->yoff);
    swp16(p->width);
    swp16(p->height);
    swp16(p->set_width);

	return;
}





#if RESTRICTED_ENVIRON
FUNCTION unsigned char *dynamic_load(file_position, num_bytes)
ufix32 file_position;
fix15 num_bytes;
{
	fix15 i;

	if (fseek(font_fp, (long)file_position, 0))
  	{
    	printf("Unable to do fseek on font file\n");
    	exit(1);
  	}

	if (num_bytes > 10240)
  	{
    	printf("Number of bytes dynamically requested greater than max\n");
    	exit (1);
  	}

	for (i=0; i< num_bytes; i++)
  	big_buffer[i]=getc(font_fp);

	return big_buffer; /* return addr of big buffer */
}
#endif


/*
	IBM PC AVGA 640x480 16 colors driver:
 */

#define ENABLE 0x0F
#define INDEXREG 0x3CE
#define VALREG 0x3CF
#define OUTINDEX(index, val)  {outp(INDEXREG, index); outp(VALREG, val);}
#define EGA_WRITE 				{outp(0x3ce,1); outp(0x3cf,0x0f); }
#define EGA_RESET 				{outp(0x3ce,0); outp(0x3cf,0 ); \
						 				 outp(0x3ce,1); outp(0x3cf,0 ); \
						 				 outp(0x3ce,8); outp(0x3cf,0xff); }
#define EGABASE 0xA0000000L
#define WIDTH 80L

static char lmask[8] ={ 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01 };
static char rmask[8] ={ 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe };
static char pmask[8] ={ 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

FUNCTION static void vga_hline(int x, int y, int length)
{
	int i, bits, r ;
	unsigned char mask_id, mask ;
	char far *base;


	EGA_WRITE ;
	/* calculate VGA video address */
	base = (char far *)(EGABASE 
 	           + (long)y * WIDTH + (long)( x >> 3 ) );
   OUTINDEX(0, color_code);   

	mask = lmask[(r = x % 8)];
	bits = (length + r - 8) ;
	/* check how many bits in first byte */
	if ( bits < 0 )
	{
		/* only partial bits */
		mask_id = mask = pmask[r];
		bits = length ;
		for ( i = 1 ; i < bits ; i++ )
		{
			mask_id = mask_id >> 1 ;
			mask = mask | mask_id ;
		}
	}
	else /* partial bits in first byte and more */
		bits = 8 - r ;
	while ( length > 0 )
	{
		OUTINDEX(8,mask);   /* set mask */
		*base |= TRUE ;       /* force a write to the EGA */
		base++ ;

		length -= bits;
		if ( length < 8 )
			mask = rmask[length] ;
		else
			mask = 0xff;
		bits=8;
	}
	EGA_RESET ;
}

FUNCTION static void vga_CLS(void)
{
	int i, j ;
	char far *base ;

	EGA_WRITE ;
	base = (char far *)(EGABASE );
	OUTINDEX(0, 0);  /* set new color*/
	OUTINDEX(8,0xff);   /* set mask */
	for ( i = 0 ; i < 480 ; i++ )
		for ( j = 0 ; j < WIDTH ; j++ )
		{
			*base |= TRUE ;       /* force a write to the EGA */
			base++ ;
		}
	EGA_RESET ;
	return;
}



/******************************************************************************
*	fit_load()
*	RETURNS:	TRUE of FALSE
******************************************************************************/
FUNCTION boolean fit_load(char *fileName)
{
int fd;
ufix16 i, nFonts;
size_t sizeRead;
ufix32 fontNum;

   nFonts = 0;
	fd = open(fileName, _O_RDWR | O_BINARY, _S_IREAD);
	if (fd >= 0)
	{
		sizeRead = read(fd, &gFontInfoTable[no_fonts], (size_t)sizeof(gFontInfoTable));
		close(fd);
		nFonts = (ufix16)(sizeRead / sizeof(FontInfoType));
      font_idx = 0;
		for (i = 0, fontsFound=0; fontsFound <3 && i < nFonts; i++, gFitIndex++)
		{/* load the fonts up into memory */
			fontNum = gFontInfoTable[gFitIndex].pclHdrInfo.font_number;
         if ( fontNum == 3150 || fontNum == 3158 || fontNum == 3162 )
         {
            fontsFound++;
   			strcpy(file_options[font_idx].pathname, BuildFontFileName(fontNum));
	   		file_options[font_idx].fdescr = fopen (file_options[font_idx].pathname,
													"rb");
		   	if (file_options[font_idx].fdescr == NULL)
			   {
				   fprintf(stderr, "Cannot open file %s\n",
   						file_options[font_idx].pathname);
               return(FALSE);
				}
		   	fseek(file_options[font_idx].fdescr, 0L, 2);
   			file_options[font_idx].filesize = ftell(file_options[font_idx].fdescr);
	   		fseek(file_options[font_idx].fdescr, 0L, 0);
		   	file_options[font_idx].font_buffer =
			   	(ufix8 *)malloc(file_options[font_idx].filesize);
   			if (file_options[font_idx].font_buffer == NULL)
				{
	   			fclose(file_options[font_idx].fdescr);     
		   		fprintf(stderr,"Cannot allocate buffer for %s\n",
					file_options[font_idx].pathname);
               return(FALSE);
	   		}
		   	bytes_read = fread(	file_options[font_idx].font_buffer,
			   				1,
				   			file_options[font_idx].filesize,
					   		file_options[font_idx].fdescr);
   			if (bytes_read < 0)
	   		{
		   		fprintf(stderr, "****** Error on reading %s: %x\n",
			   		file_options[font_idx].pathname, bytes_read);
   				fclose(file_options[font_idx].fdescr);     
               return(FALSE);
		   	}
   			setup_speedo_font();       /* set up for Speedo font */
	   		gFontInfoTable[gNFitFonts].addr = (char *)file_options[font_idx].font_buffer;
         } /* end if */
		   font_idx++;
   		gNFitFonts++;
		} /* end for */
	}
	else
	{/* unable to load the fit table */
		fprintf(stderr,"Cannot load FIT table: %s\n",
				fileName);
      return(FALSE);
	}
	return(TRUE);
}

/******************************************************************************
*	BuildFontFileName()
*	RETURNS:	character pointer to space where font filename was copied
******************************************************************************/
FUNCTION char *BuildFontFileName(ufix32 fontNum)
{
char numStr[16];
	memset(strBuf, 0, sizeof(strBuf));
	strcpy(strBuf, fontRoot);
	sprintf(numStr, "%d", fontNum);
	strcat(strBuf, numStr);
	strcat(strBuf, ".spd");
	return(strBuf);
}

/******************************************************************************
*	fill_font_buffer()
*	allocate a memory buffer and fread the file pointed to by fp
*	RETURNS:	TRUE on success, FALSE on failure
******************************************************************************/
FUNCTION boolean		fill_font_buffer(ufix8 **ptr, ufix32 size, FILE *fp)
{
	ufix32		bytes_read, tmp;
	ufix16		bytes;

#if INTEL
	if (size > 65535)
	{
		if ( (*ptr = (ufix8 *)halloc(size,1)) == NULL )
		{
			
			fprintf(stderr,"Couldn't allocate font buffer.\n");
			return(FALSE);
		}
		bytes_read = 0;
		bytes = 65535;
		while (bytes > 0)
		{
			tmp = fread(*ptr + bytes_read, 1, bytes, fp);
			if ((ufix16)tmp != bytes)
			{
				fprintf(stderr,"Error reading font file.\n");
				return(FALSE);
			}
			bytes_read += tmp;
			tmp = size - bytes_read;
			bytes = (tmp > 65535) ? 65535 : (ufix16)tmp;
		}
	}
	else
#endif
	{
#ifdef MSDOS
		if ( (*ptr = (ufix8 *)malloc((ufix16)size)) == NULL )
#else
		if ( (*ptr = (ufix8 *)malloc(size)) == NULL )
#endif
		{
			
			fprintf(stderr,"Couldn't allocate font buffer.\n");
			return(FALSE);
		}
#ifdef MSDOS
		bytes_read = fread(*ptr, 1, (ufix16)size, fp);
#else
		bytes_read = fread(*ptr, 1, size, fp);
#endif
		if (bytes_read != size)
		{
			fprintf(stderr,"Error reading font file.\n");
			return(FALSE);
		}
	}
	return(TRUE);
} /* end of fill_font_buffer */


FUNCTION static void set_backgd(void)
{
	int i, j ;
	char far *base ;

	EGA_WRITE ;
	base = (char far *)(EGABASE );
	OUTINDEX(0, 0x0f);  /* set background color to be white*/
	OUTINDEX(8,0xff);   /* set mask */
	for ( i = 0 ; i < 470 ; i++ )
		for ( j = 0 ; j < WIDTH ; j++ )
		{
			*base |= TRUE ;       /* force a write to the EGA */
			base++ ;
		}
	EGA_RESET ;
	return;
}


FUNCTION static   void delay ( clock_t wait )
{
   clock_t goal;

   goal = wait + clock();
   while (goal > clock() )
      ;
}

/* EOF selsym.c */
