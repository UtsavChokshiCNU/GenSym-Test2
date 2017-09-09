/*****************************************************************************
*                                                                            *
*  Copyright 1993, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                         U.S. Patent No 4,785,391                           *
*                           Other Patent Pending                             *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
*  $Log: not supported by cvs2svn $
*  Revision 1.1  1993/05/04 20:12:29  mhd
*  The flat-directory version of the Bitstream 4-in-1 software.
*
 * Revision 1.1.1.1  1993/04/15  20:14:47  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 2.19  93/03/15  13:53:52  roberte
 * Release
 * 
 * Revision 1.7  93/03/15  13:48:04  roberte
 * Added comments.
 * 
 * Revision 1.6  93/03/12  00:22:36  roberte
 * Added code to release/unload TrueType and PCL font memory.
 * 
 * Revision 1.5  93/03/11  10:49:48  weili
 * Changed type of argc to int from short.
 * 
 * Revision 1.4  93/03/10  19:54:43  weili
 * added log header
 * added "if (!set_width) in the beginning of
 * SetWidthToPixelWidth to avoid run time error
 * changed the declaration of argc from short to
 * int for portability
 * modified get_char_encoding() to fix the segmentation
 * fault.
 *                                                   *
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


/***** STATIC FUNCTIONS *****/
static	boolean	open_font(char *pathname);
static 	void 		close_font_file(void);
static	boolean	setup_type1_font(void);
static	boolean	setup_speedo_font(void);
static	boolean	setup_tt_font(void);
static	boolean	setup_eo_font(void);
static	void		close_type1(void);
static	void *get_char_encoding PROTO((ufix16 char_index));
static	fix15 	read_2b(ufix8 *pointer);
			int main(int argc, char *argv[]);

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

#define MAX_BITS  256              /* Max line length of generated bitmap */
#define VIDEO_MAX 480

static	char	pathname[100];      /* Name of font file to be output */

static  	fix15  raswid;             /* raster width  */
static  	fix15  rashgt;             /* raster height */
static  	fix15  offhor;             /* horizontal offset from left edge of emsquare */
static  	fix15  offver;             /* vertical offset from baseline */
static  	fix15  y_cur;              /* Current y value being generated and printed */
static  	char   line_of_bits[2 * MAX_BITS + 1]; /* Buffer for row of generated bits */
static  	fix15  scan_lines;
static   char   title_str[64];

static	ufix16 char_index;
static	ufix8		  *character; /* can either be a charname for type1 */
							/* or a char index for speedo and tt */
static  int		x_dev, y_dev ;

static	CHARACTERNAME **font_encoding;
static	eFontProcessor	font_type;
static	eFontProtocol	font_protocol;
static	ufix16			no_font_chars; /* number of characters to output */
										/* initialized in setup_?_font functions */
static	ufix16			*font_table = NULL;  /* allocate as much space as you need */
static	ufix8				*font_buffer = NULL; /* allocate only if needed */
static	ufix32			fontbuf_size; /* size of font buffer */
static	specs_t			gspecs;
static	buff_t			gbuff;
static	eofont_t			eo_font;
static   int   row_total=0, column_total=0, page_nr=0;


#if RESTRICTED_ENVIRON
static	ufix8 	*font_ptr;
static 	ufix16 	buffer_size;
static	unsigned char big_buffer[10240];
			/* temp buffer to store char string */
#else
static	font_data *font_ptr;
#endif

static	FILE *font_fp = NULL;

/* DKW: proofing WIP */
#define PROOF_CHAR_HEIGHT 20
#ifdef OLDWAY
#define PT_PER_INCH 72.2892
#else
#define PT_PER_INCH 72.307
#endif
#define swp16(X) X = (X << 8) | ((X >> 8)&0xFF)

#include "hpf.h"        /* hp soft font defs */

static char char_set_name[32] = "8U";
static int hp_char_id;
static int pointsize;
static HPF_HEAD hpfhd;			/* hp header struct */
static HPF_CHARDIR hpfcdir;	/* ?? */
static FILE    *hpf_fp;		/* hp soft font output file descriptor */
static boolean do_proof;
static ufe_struct	tspecs;

char transdata[] = "\33&p1X";
static  fix15  space_char;
static  fix15 _gxmin = 1000;
static  fix15 _gymin = 1000;
static  fix15 _gxmax = 1000;
static  fix15 _gymax = 1000;
static  ufix16 bitrow[MAX_BITS/16];
static fix31 gBitmapWidth;


#ifdef INTEL
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
void hp_proof_prologue(char *);
void hpwc(char *);
void layout (int total_chars);
void hp_proof_prologue_no_open();
void hp_proof_epilog_no_close(int total_chars);

fix31 SetWidthToPixelWidth(fix31 set_width);

/*** extern variables ***/
extern   eFontProtocol gCharProtocol;	/* global protocol of character selection */


/* end proofing WIP */

/****************************************************************************
   FILE:       fdump.c
   This module demonstrates how to display or print all characters in a
   sample font. "all characters" means :
      Speedo      all characters
      TrueType    whatever can find in first 640 characters
      PCLeo       whatever can find in first 256 characters      
      Type1       whatever can find in first 256 characters
*****************************************************************************/
int	main(argc,argv)
int argc;
char *argv[];
{
	boolean  		 	setup, getoutchar;
	unsigned char 	*buf, ch;
	union REGS	regs;
   ufix16   char_id;
   int i, j, k, hor_nr, ver_nr, hor_offset, ver_offset, font_nr;
   int total_chars;
   ufix16   char_per_font;

	/* check for proper usage */
	if (argc < 2) 
   {
      printf("Usage:  fdump <fontfile> [/s:lines per em] [/p:pointsize]\n"); 
      printf("        default lines per em for screen is 24 \n");
      printf("        default point size for printer is 16 \n");
	   exit (1);
   }

	sprintf(pathname, argv[1]);

   if ( strncmp(argv[2], "/p", 2) == 0)
   {   
      do_proof = TRUE;
      if (argv[2][2] == ':')
   		sscanf(&argv[2][3],"%d",&pointsize);
      else
         pointsize = 16;
      scan_lines = 300 / PT_PER_INCH * pointsize;
   }
   else if ( strncmp(argv[2], "/s", 2) == 0)
   {
      if (argv[2][2] == ':')
      {
   		sscanf(&argv[2][3],"%d",&scan_lines);
         if (scan_lines > 460)
            scan_lines = 460;
      }
      else
         scan_lines = 24;
   }
   else
   {
      printf("Usage:  fdump <fontfile> [/s:lines per em] [/p:pointsize]\n"); 
      printf("        default lines per em for screen is 24 \n");
      printf("        default point size for printer is 16 \n");
      exit(1);
   }
      
	if (!open_font(pathname))
   {
   	fprintf(stderr,"Unable to open font file %s\n",pathname);
	   exit (1);
   }

	if ( (buf = (unsigned char *)malloc(20)) == NULL)
	{
		fprintf(stderr,"Unable to allocate temporary buffer.\n");
		exit(1);
	}
	fread(buf, 1, 10, font_fp);
	fseek(font_fp, 0L, SEEK_SET);

    /* determine type of font */
	if ( strncmp(buf, "%!", 2) == 0 )
		/* set up for Type 1 font */
		setup = setup_type1_font();        
   else if (buf[0]  == 0x80)
		/* check for pfb type1 font */
		setup = setup_type1_font();   
   else if (strncmp(buf, "D1.0", 4) == 0)
		/* set up for Speedo font */
		setup = setup_speedo_font();       
	else if (strncmp(buf, ")s", 3) == 0)
		setup = setup_eo_font();
   else setup = setup_tt_font();
	free(buf);

	if (!setup)
      exit(setup);			/* error in setup */


	/* output to the printer */
   if (do_proof)
   {
   	char     command[128];


		/* open output hpf, write header */
   	hpf_fp = fopen("tmpout.bin","wb");
	   if (hpf_fp == NULL) 
      {
		   fprintf(stderr,"Error, cannot open proof file %s\n", "tmpout.bin");
   		exit(1);
	   }
   	switch(font_type)
	   {
		   case procType1:
            sprintf(title_str, "Type1 Font %s", pathname);
         	fprintf(stderr, "Processing Type1 font %s ...\n", pathname);
   			break;
		   case procSpeedo:
            sprintf(title_str, "Speedo Font %s", pathname);
         	fprintf(stderr, "Processing Speedo font %s ...\n", pathname);
   			break;
		   case procTrueType:
            sprintf(title_str, "TrueType Font %s", pathname);
         	fprintf(stderr, "Processing TrueType font %s ...\n", pathname);
   			break;
		   case procPCL:
            sprintf(title_str, "PCLeo Font %s", pathname);
         	fprintf(stderr, "Processing PCLeo font %s ...\n", pathname);
   			break;
   	}
      hpwc("\033E");
      /* delete all soft fonts */
      hpwc("\033*c0F");
      sprintf(command,"\033*p150X\033*p150Y\33(0U\33(s1p16v0s3b4101T%s", title_str);
      hpwc(command);
      sprintf(command,"\033*p1920X\033*p150Y\33(s12v0B%s", "Bitstream, Inc.");
      hpwc(command);
      hpwc("\033*p150X");		
      
      if ( no_font_chars < 256 )
      {
         font_nr = 1;
         char_per_font = no_font_chars;
      }
      else
      {
         font_nr =  no_font_chars / 256;
         if ( no_font_chars % 256 )
            font_nr++;
      }
      for ( i=0; i < font_nr; i++)
      {
         hp_proof_prologue_no_open();
         hp_char_id = 0;
         char_per_font = 256;
         if (font_nr > 1)
            if ( i == (font_nr-1) )
               char_per_font = no_font_chars % 256;
     	   for ( j=0; j < char_per_font; j++ )   /* For each character in encoding */
         {
         	character = get_char_encoding(char_index);
   		   getoutchar = (character != (void *)0);
   	   	if (getoutchar)
            {
  	   	    	gBitmapWidth = SetWidthToPixelWidth(fi_get_char_width(character));
               if (fi_make_char(PARAMS2 character))
                  hp_char_id++;
            }
            char_index++;
         }
         total_chars = hp_char_id;
  		   hp_proof_epilog_no_close(total_chars);
   		/* finished, restore order to the Shire... */
      }
      page_nr++;
      sprintf(command, "\033*p1050X\033*p3000Y\33(0U\33(s1p12v0s0b4101TPage %d", page_nr);
      hpwc(command);
      hpwc("\033&l0H");      /* print the current page */

     	hpwc("\33E");

      fclose(hpf_fp);
      return;
   }
   else /* output on the screen */
   {
		/* set vga to be graphic mode */
		regs.x.ax = 0x0012;
		int86(0x10, &regs, &regs);
      set_backgd();

   	 hor_nr = 640 / ( scan_lines + scan_lines/2 ) ;
	    ver_nr = 460 / ( scan_lines + scan_lines/2 ) ;
       hor_offset = ( 640 - hor_nr * (scan_lines+scan_lines/2) ) / 2 ;
       ver_offset = ( 460 - ver_nr * (scan_lines+scan_lines/2) ) / 2 ;
       char_index = 0;
       while  ( char_index < no_font_chars )
       {
   		y_dev = scan_lines + ver_offset ;
         i=0;
   		while ( i < ver_nr )
   		{	
            x_dev = hor_offset ;
            j=0;
   			while ( char_index < no_font_chars && j< hor_nr 	)
   			{
         		character = get_char_encoding(char_index);
         		getoutchar = (character != (void *)0);
      	   	if (getoutchar)
   	        	{
         	      if (fi_make_char(PARAMS2 character))
                  {
         				x_dev += scan_lines + scan_lines/2 ;
                     j++;
                  }
               }
               char_index++;
   		   }
            i++;
   		   y_dev += scan_lines + scan_lines/2;
   		}
  			/* set cursor position */
  			regs.x.ax = 0x0200;
  			regs.x.bx = 0;
  			regs.x.dx = (int) 0x1c00 ;
  			int86(0x10, &regs, &regs);
      	/* press key to continue */
      	printf("\n Press any key to continue");
      	ch=getch();
   		vga_CLS();
         set_backgd();
      }
		/* reset vga to be text mode */
		regs.x.ax = 0x0002;
		int86(0x10, &regs, &regs);
   }

	switch(font_type)
	{
		case procType1:
			close_type1();
			break;
		case procTrueType:
			tt_release_font(PARAMS1);
			break;
		case procPCL:
			pf_unload_font();
			break;
	}
	close_font_file();

	if (font_table)
		free(font_table);
	if (font_buffer)
		free(font_buffer);
	exit(TRUE);
}  /* end of main function */


/****************************************************************************
  open_font()
      Open the sample font.
  RETURNS:
      TRUE if open succeeded
      FALSE if open failed
*****************************************************************************/
static boolean open_font(pathname)
char *pathname;
{
	font_fp = fopen(pathname, "rb");
	if (font_fp == NULL)
    	return FALSE;
	else return TRUE;
}


/****************************************************************************
  close_font()
      close the sample font.
*****************************************************************************/
static void close_font_file(void)
{
	if (font_fp)
		fclose(font_fp);
	return;
}


/****************************************************************************
  fill_font_buffer()
      Allocate a font buffer and load the whole font into that buffer.
  RETURNS:
      TRUE if buffer loaded successfully
      FALSE if load buffer failed 
*****************************************************************************/
boolean		fill_font_buffer(ufix8 **ptr, ufix32 size, FILE *fp)
{
	ufix32		bytes_read, tmp;
	ufix16		bytes;

#ifdef INTEL
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
		if ( (*ptr = (ufix8 *)malloc((ufix16)size)) == NULL )
		{
			
			fprintf(stderr,"Couldn't allocate font buffer.\n");
			return(FALSE);
		}
		bytes_read = fread(*ptr, 1, (ufix16)size, fp);
		if (bytes_read != size)
		{
			fprintf(stderr,"Error reading font file.\n");
			return(FALSE);
		}
	}
	return(TRUE);
} /* end of fill_font_buffer */

/****************************************************************************
  setup_type1_font()
      This function handles all the initializations for the Type1 font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling tr_load_font()
      .  setup the values for transformation metrics and call fi_set_specs()
      .  setup the value: sp_globals.metric_resolution = 1000;
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean setup_type1_font(void)
{
//	ufe_struct tspecs;

	font_type = procType1;
  	font_protocol = protoPSName;
	fi_reset(font_protocol, font_type);  /* initialize processor */
	/* load font */
	if ( !tr_load_font(&font_ptr) )
	{
      fprintf(stderr, "cannot load type 1 font\n");
		return(FALSE);
	}

	/* Initialization - set specs */  
	tspecs.Matrix[0] = (real) scan_lines;
	tspecs.Matrix[1] = (real) 0.0;
	tspecs.Matrix[2] = (real) 0.0;
	tspecs.Matrix[3] = (real) scan_lines;
	tspecs.Matrix[4] = (real) 0.0;
	tspecs.Matrix[5] = (real) 0.0;
	if ((tspecs.Gen_specs = malloc(sizeof(specs_t))) == NULL)
	{
		fprintf(stderr,"Can not allocate structure.\n");
		return(FALSE);
	}
	tspecs.Gen_specs->flags =  MODE_SCREEN;
	tspecs.Font.org = (unsigned char *)font_ptr;
	if (!fi_set_specs(&tspecs))
   {
   	fprintf(stderr,"Unable to set requested specs.\n");
	   return (FALSE);
   }
   sp_globals.metric_resolution = 1000;
	font_encoding = tr_get_encode();
	no_font_chars = 256;

	return(TRUE);
}


/****************************************************************************
  setup_speedo_font()
      This function handles all the initializations for the Speedo font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling fill_font_buffer()
      .  setup the values for transformation metrics and call fi_set_specs()
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean	setup_speedo_font(void)
{
	ufix16	first_char_index, i;

	if (!do_proof)
		pointsize = 1;

   font_protocol = protoDirectIndex;
   font_type = procSpeedo;
   fi_reset(font_protocol, font_type);

	fseek(font_fp, 0L, SEEK_END);
	fontbuf_size = ftell(font_fp);
	fseek(font_fp, 0L, SEEK_SET);
	if ( !fill_font_buffer(&font_buffer, fontbuf_size, font_fp))
		return(FALSE);
   first_char_index = read_2b(font_buffer + FH_FCHRF);
   no_font_chars = read_2b(font_buffer + FH_NCHRL);
	/* allocate font_table */
	if ( (font_table = (ufix16 *)malloc(no_font_chars*sizeof(ufix16))) == NULL)
	{
		fprintf(stderr,"Can't allocate font_table.\n");
		return(FALSE);
	}
	/* DO ENCRYPTION HERE */

	gbuff.org = font_buffer;
	gbuff.no_bytes = fontbuf_size;
	gspecs.xxmult = (long)scan_lines << 16;
	gspecs.xymult = 0L << 16;      /* Coeff of Y to calculate X pixels */
	gspecs.xoffset = 0L << 16;     /* Position of X origin */
		/* Coeff of Y to calculate Y pixels */
   gspecs.yymult = (long)scan_lines << 16;
	gspecs.yxmult = 0L << 16;      /* Coeff of X to calculate Y pixels */
	gspecs.yoffset = 0L << 16;     /* Position of Y origin */
	gspecs.flags = MODE_SCREEN;
	gspecs.out_info = 0;           /* output module information  */

	gspecs.pfont = &gbuff;
	tspecs.Gen_specs = &gspecs;

	if (!fi_set_specs(&tspecs))
	{
		fprintf(stderr, "cannot set requested specs\n");    
		return(FALSE);
	}

	/* loading font indecis into font_table. */
	for (i=0; i < no_font_chars; i++)
		font_table[i] = i + first_char_index;

	return(TRUE);
}


/****************************************************************************
  setup_tt_font()
      This function handles all the initializations for the TrueTyp font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling tt_load_font()
      .  setup the values for transformation metrics and call fi_set_specs()
      .  setup the value: sp_globals.metric_resolution = 2048;
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean setup_tt_font(void)
{
	ufix16 i;

	font_protocol = protoDirectIndex;
	font_type = procTrueType;
	fi_reset(font_protocol, font_type);

	fseek(font_fp, 0L, SEEK_END);
	fontbuf_size = ftell(font_fp);
	fseek(font_fp, 0L, SEEK_SET);
	/* need buffer for tt_get_font_fragment() */
	if (!fill_font_buffer(&font_buffer, fontbuf_size, font_fp))
		return(FALSE);

   if (!tt_load_font(0)) /* if loop font files, then put number of font */
					/* file here, i.e first, second, third, ...  == 0,1,2,...*/
	{
		fprintf(stderr, "cannot load truetype font\n");
		return(FALSE);
	}

	gspecs.xxmult = (long)scan_lines << 16;
	gspecs.xymult = 0l << 16;
	gspecs.xoffset = 0l << 16;
	gspecs.yxmult = 0l << 16;
	gspecs.yymult = (long)scan_lines << 16;
	gspecs.yoffset = 0l << 16;
	gspecs.flags = MODE_SCREEN;

	tspecs.Gen_specs = &gspecs;

	if (!fi_set_specs(&tspecs))
	{
		fprintf(stderr,"Cannot set requested specs.\n");
		return(FALSE);
	}
   sp_globals.metric_resolution = 2048;
	no_font_chars = 640;
	if ( (font_table = (ufix16 *)malloc(no_font_chars * sizeof (ufix16)) )
			== NULL)
	{
		fprintf(stderr,"Cannot allocate font encoding table.\n");
		return(FALSE);
	}
	for (i=0; i < no_font_chars; i++)
		font_table[i] = i;

	return(TRUE);
}

/****************************************************************************
  setup_eo_font()
      This function handles all the initializations for the PCLeo font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling pf_load_pcl_font()
      .  setup the values for transformation metrics and call fi_set_specs()
      .  setup the value: sp_globals.metric_resolution = 8782;
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean	setup_eo_font(void)
{
	ufix16 i;
	ufe_struct tspecs;

	font_type = procPCL;
	font_protocol = protoDirectIndex;
	fi_reset(font_protocol, font_type);
	close_font_file();
	font_fp = NULL;
	if ( !pf_load_pcl_font(pathname, &eo_font) )
	{
		fprintf(stderr,"Can not load PCL font\n");
		return(FALSE);
	}

   gspecs.xxmult = (long)scan_lines << 16;
   gspecs.xymult = 0L << 16;
   gspecs.xoffset = 0L << 16;     /* Position of X origin */
   gspecs.yxmult = 0L << 16;      /* Coeff of X to calculate Y pixels */
   gspecs.yymult = (long)scan_lines << 16;         /* Coeff of Y to calculate Y pixels */
   gspecs.yoffset = 0L << 16;     /* Position of Y origin */
   gspecs.flags = MODE_SCREEN;
   gspecs.pfont = (buff_t STACKFAR *)&eo_font;

	tspecs.Gen_specs = &gspecs;	/* setup intermediary structure */
	   /* Set character generation specifications */
   if (!fi_set_specs(&tspecs))
	{
      fprintf(stderr, "Cannot set requested specs\n");
		return (FALSE);
   }

   sp_globals.metric_resolution = 8782;

	no_font_chars = 256;
	if ( (font_table = (ufix16 *)malloc(no_font_chars * sizeof (ufix16)) )
			== NULL)
	{
		fprintf(stderr,"Cannot allocate font encoding table.\n");
		return(FALSE);
	}
	for (i=0; i < no_font_chars; i++)
		font_table[i] = i;
	return(TRUE);
}

/****************************************************************************
  close_type1()
      close type1 font
*****************************************************************************/
static	void	close_type1(void)
{
	tr_unload_font(font_ptr);
	return;
}

/****************************************************************************
   get_char_encoding()  
      get the pointer into the font table based on character index
   RETURNS:
      A pointer to a void.  It can either be a pointer to a character
      name for type1 or a pointer to a character index for other fonts
*****************************************************************************/
static	void *get_char_encoding(ufix16 char_index)
/* character is a pter to a void, because it will either be a pter to */
/* a short or a char depending on font type. If the character was not */
/* retrieved successfully, then function returns false else it returns */
/* true. */
{
	void *ch = (void *)0; /* assume failure */

	switch(font_type)
	{
		case procType1:
	   	(ufix8 *)ch = (ufix8 *)font_encoding[char_index];
		   if (strcmp((char *)ch,".notdef") == 0)
				ch = (void *)0;
			break;

		case procTrueType:
		case procSpeedo:
		case procPCL:
			(ufix16 *)ch = (ufix16 *)&font_table[char_index];
			break;
	}
	return(ch);
}



#if REENTRANT_ALLOC
 void sp_report_error(sp_global_ptr,n)
SPEEDO_GLOBALS *sp_global_ptr;
#else
 void sp_report_error(n)
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
void sp_open_bitmap(sp_global_ptr, x_set_width, y_set_width, xorg, yorg, xsize, ysize)
SPEEDO_GLOBALS *sp_global_ptr;
#else
void sp_open_bitmap(x_set_width, y_set_width, xorg, yorg, xsize, ysize)
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
	fix15 i, j;
	union REGS	regs;

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
      ufix32 mult, bitmapWidth;

      raswid = xsize;
      rashgt = ysize;
      offhor = xorg >> 16;
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
   
   
#ifdef INTEL
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
      offhor = (fix15)(xorg >> 16);
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
 void sp_set_bitmap_bits (sp_global_ptr, y, xbit1, xbit2)
SPEEDO_GLOBALS *sp_global_ptr;
#else
 void sp_set_bitmap_bits (y, xbit1, xbit2)
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
//	vga_hline(x_dev+xbit1,y+y_dev,length);

   }

} /* sp_set_bitmap_bits */


#if REENTRANT_ALLOC
 void sp_close_bitmap(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
 void sp_close_bitmap()
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
 void sp_open_outline(sp_global_ptr, x_set_width, y_set_width, xmin, xmax, ymin, ymax)
SPEEDO_GLOBALS *sp_global_ptr;
#else
 void sp_open_outline(x_set_width, y_set_width, xmin, xmax, ymin, ymax)
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
 void sp_start_new_char(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
 void sp_start_new_char()
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
void sp_start_contour(sp_global_ptr, x, y, outside)
SPEEDO_GLOBALS *sp_global_ptr;
#else
void sp_start_contour(x, y, outside)
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
 void sp_curve_to(sp_global_ptr, x1, y1, x2, y2, x3, y3)
SPEEDO_GLOBALS *sp_global_ptr;
#else
 void sp_curve_to(x1, y1, x2, y2, x3, y3)
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
void sp_line_to(sp_global_ptr, x, y)
SPEEDO_GLOBALS *sp_global_ptr;
#else
void sp_line_to(x, y)
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
void sp_close_contour(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
void sp_close_contour()
#endif
/*
 * Called by character generator at the end of each contour
 * in the outline data of the character.
 */
{
	printf("close_contour()\n");
}


#if REENTRANT_ALLOC
void sp_close_outline(sp_global_ptr)
SPEEDO_GLOBALS *sp_global_ptr;
#else
void sp_close_outline()
#endif
/*
 * Called by character generator at the end of output of the
 * scaled outline of the character.
 */
{
	printf("close_outline()\n");
}
#endif


fix15 read_2b(pointer)
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

fix31 read_4b(pointer)
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


boolean get_byte(next_char)
char *next_char;
{
	short i;

	/* file_pos = ftell(font_fp); */
	if ((i = getc(font_fp))== EOF)
    	return FALSE;
	*next_char = (char)i;
	return TRUE;
}



GetSFNTFunc 	tt_get_font_fragment (clientID, offset, length)
  fix31  clientID, offset, length;

/* Returns a pointer to data extracted from the sfnt.
   tt_get_font_fragment must be initialized in the fs_GlyphInputType
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


buff_t STACKFAR * WDECL sp_load_char_data(file_offset, no_bytes, cb_offset)
fix31    file_offset;  /* Offset in bytes from the start of the font file */
fix15    no_bytes;     /* Number of bytes to be loaded */
fix15    cb_offset;    /* Offset in bytes from start of char buffer */
{
	/* DUMMY FUNCTION */
	buff_t *it;
	return(it);
}


fix31 SetWidthToPixelWidth(fix31 set_width)
{
	fix31 pixel_width = 0; /* assume no width */
	ufix32 mult;

   if (!set_width)
   	return(pixel_width); /* already 0 */
   if (font_type == procType1)
	   mult = ABS(65536 * tspecs.Matrix[0]) + ABS(65536 * tspecs.Matrix[4]);
   else   
//   	mult = ABS(sp_globals.specs.xxmult) + ABS(sp_globals.specs.yxmult);
   	mult = ABS(tspecs.Gen_specs->xxmult) + ABS(tspecs.Gen_specs->yxmult);
	/* now calculate the width from sp_get_char_width() call */
	set_width *= sp_globals.metric_resolution;
	set_width -= (sp_globals.metric_resolution >> 1);
	set_width = (set_width >> 16);
/* multiply RFB setwidth times high-order word of mult, add setwidth times low order word,
   add roundoff and divide by setwidth resolution units to get pixel width */
   pixel_width = (fix15)(fix31)(((fix31)set_width * (mult >> 16) + 
                               (((fix31)set_width * (mult & 0xffffL) ) >> 16) +
                               (sp_globals.metric_resolution >> 1)) / sp_globals.metric_resolution);

	return pixel_width;
}


/****************************************************************************
  hp_proof_prologue_no_open()
      This function handles all the initializations necessary for the 
      soft font including assign an ID for the soft font and setup
      the values for the header of the soft font by callng new_hpfhd().
*****************************************************************************/
void hp_proof_prologue_no_open()
{

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


void hp_proof_prologue(char *hpoutname)
{

		/* open output hpf, write header */
	hpf_fp = fopen(hpoutname,"wb");
	if (hpf_fp == NULL) {
		fprintf(stderr,"Error, cannot open proof file %s\n", hpoutname);
		exit(1);
	}

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


/****************************************************************************
  hp_proof_epilog_no_close()
      This function selects the soft font to use and sends the characters
      to the file by calling layout().
*****************************************************************************/
void hp_proof_epilog_no_close(total_chars)
int total_chars;
{
#if 0
		/* make the downloaded font permanent */
	hpwc (ESC_MAKE_FONT_PERM);
#endif

		/* make the downloaded font temporary */
	hpwc ("\033*c100d4F");

		/* select the downloaded font for use */
	hpwc (ESC_SELECT_FONT_100);

		/* create the proof sheet */
	layout (total_chars);
   
   /* delete all soft fonts */
   hpwc("\033*c0F");
	return;
}


/****************************************************************************
  layout()
      This function actually reads the text file and sends the characters to
      the file and does the layout.
*****************************************************************************/
void layout (total_chars)
int   total_chars;
{
	int	i, hor_nr, ver_nr;
	char command[200];


   hor_nr = (int) ( 7 * (PT_PER_INCH/(pointsize+(pointsize/2))) );
   ver_nr = (int) (8.5 * (PT_PER_INCH/(pointsize*2)) );

   sprintf(command, "\33&l%.4fC", 48/(PT_PER_INCH/(pointsize*2)) );
  	hpwc(command);

   sprintf(command, "\33&k%.4fH\n", 120/(PT_PER_INCH/(pointsize+(pointsize/2))) );
  	hpwc(command);


   hpwc("\033&f1S");    /* pop cursor position */
	for (i = 0; i < total_chars; i++) 
   {
      if (column_total % hor_nr== 0)
      {
         row_total++;
         if ( row_total > ver_nr)
         {
            page_nr++;
            sprintf(command, "\033*p1050X\033*p3000Y\33(0U\33(s1p12v0s0b4101TPage %d", page_nr);
            hpwc(command);
            hpwc("\033&l0H");      /* print the current page */
            sprintf(command,"\033*p150X\033*p150Y\33(0U\33(s1p16v0s3b4101T%s", title_str);
            hpwc(command);
            sprintf(command,"\033*p1920X\033*p150Y\33(s12v0B%s", "Bitstream, Inc.");
            hpwc(command);
            hpwc("\033*p150X");		
            hpwc("\033&a+1R");	/* move down one line */
         	hpwc (ESC_SELECT_FONT_100);
            sprintf(command, "\33&l%.4fC", 48/(PT_PER_INCH/(pointsize*2)) );
           	hpwc(command);
            sprintf(command, "\33&k%.4fH\n", 120/(PT_PER_INCH/(pointsize+(pointsize/2))) );
           	hpwc(command);
            row_total=1;
         }
         else
         {
            hpwc("\033*p150X");
            hpwc("\033&a+1R");	/* move down one line */
         }
      }
      fprintf(hpf_fp, "%s%c",transdata,i);
      column_total++;
	} 
   hpwc("\033&f0S");    /* push cursor position */
	return;
} /* end layout() */


/****************************************************************************
  hpwc()
      This function writes a hp command string to the proof file.
*****************************************************************************/
void hpwc(char *command)
{
	fprintf (hpf_fp, command);

	return;
}


/****************************************************************************
  new_hpfhd()
      This function actually composes soft font header structure.
*****************************************************************************/
void new_hpfhd(HPF_HEAD *p)
{

fix15 pixel_width;
ufix32 fixed_ratio = (ufix32)(PROOF_CHAR_HEIGHT/PT_PER_INCH * 1200);


	pixel_width = gBitmapWidth;

    p->size = 64;
    p->font_type = 2; /* 0 = ascii 1 = roman8 2 = pc8 */
    p->baseline = 0.764 * (PROOF_CHAR_HEIGHT * 300/PT_PER_INCH);
    p->cell_width = _gxmax = _gxmin;
    p->cell_height = _gymax = _gymin;
    p->orient = 0;  /* portrait */
//    p->spacing = 1; /* proportional */
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
#ifdef INTEL
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

/****************************************************************************
  swap_cdir()
      This function swaps bytes in 16 bit field in font header.
*****************************************************************************/
void swap_cdir(HPF_CHARDIR *p)
{
    swp16(p->xoff);
    swp16(p->yoff);
    swp16(p->width);
    swp16(p->height);
    swp16(p->set_width);

	return;
}





#if RESTRICTED_ENVIRON
unsigned char *dynamic_load(file_position, num_bytes)
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
	VGA 640x480 16 colors driver
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

/****************************************************************************
  vga_hline()
      This function draws horizontal from x with length with black pixels. 
*****************************************************************************/
static void vga_hline(int x, int y, int length)
{
	int i, bits, r ;
	unsigned char mask_id, mask ;
	char far *base;


	EGA_WRITE ;
	/* calculate VGA video address */
	base = (char far *)(EGABASE 
 	           + (long)y * WIDTH + (long)( x >> 3 ) );
//	OUTINDEX(0, 0x0f);  /* set to intense white*/
//	OUTINDEX(0, 0x0b);  /* set new color*/

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

/****************************************************************************
  vga_CLS()
      This function clear the screen by writing the whole block with 0(black)
*****************************************************************************/
static void vga_CLS(void)
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

/****************************************************************************
  set_backgd()
      This function changes all the pixels intense white.
*****************************************************************************/
static void set_backgd(void)
{
	int i, j ;
	char far *base ;

	EGA_WRITE ;
	base = (char far *)(EGABASE );
	OUTINDEX(0, 0x0f);  /* set background color to be white*/
	OUTINDEX(8,0xff);   /* set mask */
	for ( i = 0 ; i < 460 ; i++ )
		for ( j = 0 ; j < WIDTH ; j++ )
		{
			*base |= TRUE ;       /* force a write to the EGA */
			base++ ;
		}
	EGA_RESET ;
	return;
}
