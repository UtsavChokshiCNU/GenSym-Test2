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
*  Revision 1.1  1995/10/03 00:37:53  jra
*  Adding ext files from 4.0 Rev. 1 as initial commit for AB.
*
*  Revision 1.1  1993/05/19 22:04:47  mhd
*  Added Bitstream fontrip (Font Raster Image Processor) c & h files.  Not
*  all are compiles -- some are demos, or test modules.
*
 * Revision 1.1  1993/05/04  20:15:48  mhd
 * The flat-directory version of the Bitstream 4-in-1 software.
 *
 * Revision 1.1.1.1  1993/04/15  20:14:52  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 2.19  93/03/15  13:59:56  roberte
 * Release
 * 
 * Revision 1.9  93/03/15  13:47:18  roberte
 * Added comments.
 * 
 * Revision 1.8  93/03/12  00:29:46  roberte
 * Changed tt_load_font() to tt_load_font_params()
 * 
 * Revision 1.7  93/03/12  00:22:53  roberte
 * Added code to release/unload TrueType and PCL font memory.
 * Also null font_buffer when freeing.
 * 
 * Revision 1.6  93/03/11  15:57:57  roberte
 * First port to Unix. Code cleanup.
 * 
 * Revision 1.5  93/03/11  13:48:41  weili
 * Added fontfile name in the page header.
 * 
 * Revision 1.4  93/03/10  19:59:42  weili
 * added log header
 * changed the declaration of argc from short to int to avoid
 * portability problems.
 *                                                 *
*****************************************************************************/

/* !!!!!!!!!!!  RESTRICTED_ENVIRON NOT FUNCTIONING IN THIS .EXE !!!!! */

#ifdef MSDOS
#include <stddef.h>
#endif
#include <stdio.h>
#include <setjmp.h>
#ifdef MSDOS
#include <malloc.h>
#include <stdlib.h>
#endif
#include <string.h>
#ifdef MSDOS
#include <dos.h>
#endif

#define SET_SPCS
#include "spdo_prv.h"
#include "useropt.h"
#include "stdef.h"
#include "type1.h"
#include "fnt_a.h"
#include "tr_fdata.h"
#include "errcodes.h"
#include "hp_readr.h"
#include "finfotbl.h"
#include "ufe.h"		/* Unified front end */
#include "pcl5fnt.h"


extern   PC5HEAD  pcl5head;
extern   boolean  gListSorted;

/***** STATIC FUNCTIONS *****/
static	boolean	open_font PROTO((char *pathname));
static 	void 		close_font_file PROTO((void));
static	boolean	setup_type1_font PROTO((PROTO_DECL1));
static	boolean	setup_speedo_font PROTO((PROTO_DECL1));
static	boolean	setup_tt_font PROTO((PROTO_DECL1));
static	boolean	setup_eo_font PROTO((PROTO_DECL2 char *pathname));
static	fix15 	read_2b PROTO((ufix8 *pointer));
static   char           title_str[200];
int main PROTO((int argc, char *argv[]));
void txt_layout PROTO((void));

#define READTIME 0
#if READTIME
static	void dummy_loader();
#endif

/***** STATIC VARIABLES *****/
#if DEBUG
#define SHOW(X) printf("X = %d\n", X)
#else
#define SHOW(X)
#endif

#define MAX_BITS  256              /* Max line length of generated bitmap */


static  	fix15  raswid;             /* raster width  */
static  	fix15  rashgt;             /* raster height */
static  	fix15  offhor;             /* horizontal offset from left edge of emsquare */
static  	fix15  offver;             /* vertical offset from baseline */
static  	fix15  y_cur;              /* Current y value being generated and printed */
static  	char   line_of_bits[2 * MAX_BITS + 1]; /* Buffer for row of generated bits */
static  	fix15  scan_lines;

static	ufix16 char_index;
static	ufix8		  *character; /* can either be a charname for type1 */
							/* or a char index for speedo and tt */

static	CHARACTERNAME **font_encoding;
static	eFontProcessor	font_type;
static	eFontProtocol	font_protocol;
static	ufix16			no_font_chars; /* number of characters to output */
										/* initialized in setup_?_font functions */
static	ufix8				*font_buffer = NULL; /* allocate only if needed */
static	ufix32			fontbuf_size; /* size of font buffer */
static	specs_t			gspecs;
static	buff_t			gbuff;
static	eofont_t			eo_font;


#if RESTRICTED_ENVIRON
static	ufix8 	*font_ptr;
static 	ufix16 	buffer_size;
static	unsigned char big_buffer[10240];
			/* temp buffer to store char string */
#else
static	font_data *font_ptr;
#endif

static	FILE *font_fp = NULL;
static	FILE *in_fp = NULL;

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
static ufe_struct	tspecs;

char transdata[] = "\33&p1X";
static  fix15  space_char;
static  fix15 _gxmin = 1000;
static  fix15 _gymin = 1000;
static  fix15 _gxmax = 1000;
static  fix15 _gymax = 1000;
static  ufix16 bitrow[MAX_BITS/16];
static fix31 gBitmapWidth;
static char proof_string[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz. ',`~!@#$%^&*()_+-=[]\\{}|;:\"/<>?\t";

static char gSpeedoHdr[] = "SPEEDO";
static char gType1Hdr[] = "TYPE1";
static char gTrueTypeHdr[] = "TRUE TYPE";
static char gPCLHdr[] = "PCLeo";
static char gProcessing[] = "Processing ";
static char gFile[] = " file: ";

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
void hpwc(char *);
void hp_proof_prologue_no_open();
void hp_proof_epilog_no_close();

fix31 SetWidthToPixelWidth(fix31 set_width);

/*** extern variables ***/
extern   eFontProtocol gCharProtocol;	/* global protocol of character selection */


/* end proofing WIP */

/****************************************************************************
   FILE:       txtdemo.c
   This module demonstrates how to print text passages from one or more
   sample fonts.
*****************************************************************************/
int	main(argc,argv)
int argc;
char *argv[];
{
	boolean  		 	setup;
	unsigned char 	buf[20];
	char infile[32];
	int i, nFiles, no_arg;
	ufix16   char_id;
	ufix16 spaceID = 32;
   fix31  space_width;
	char command[128];
#if REENTRANT_ALLOC
	SPEEDO_GLOBALS *sp_global_ptr;
#endif

	/* output all of the characters in the encoding array */

#if DYNAMIC_ALLOC || REENTRANT_ALLOC
    sp_global_ptr = (SPEEDO_GLOBALS *)malloc(sizeof(SPEEDO_GLOBALS));
    if (sp_global_ptr)
        memset(sp_global_ptr, (ufix8)0, sizeof(SPEEDO_GLOBALS));
    else
        {
        fprintf(stderr, "Unable to allocate sp_global_ptr!\n");
        exit(1);
        }
#endif
   if ((argc < 2) || (argc > 6))
	{
	fprintf(stderr, "Usage: txtdemo font1 [font2] [font3] [font4] [-t<txtfile>]\n");
	exit(1);
	}

	no_arg = argc;
   pointsize = 12;
   nFiles = 0;
	
   if (strncmp (argv[argc-1], "-t", 2) == 0)
	{
		sscanf(argv[argc-1], "-t%s", infile);
		if ( (in_fp = fopen(infile, "rt")) == NULL )
		{
		   fprintf(stderr,"Error, cannot open input text file %s\n", infile);
   		exit(1);
		}

		no_arg = argc-1;
	}
   else
   {
		if ( (in_fp = fopen("holmes.txt", "rt")) == NULL )
		{
		   fprintf(stderr,"Error, cannot open input text file holmes.txt");
   		exit(1);
		}
   }
	/* open output hpf, write header */
  	if ( (hpf_fp = fopen("tmpout.bin","wb")) == NULL)
   {
      printf("can't open the hpf_fp\n");
      exit(1);
   }

   if (hpf_fp == NULL) 
   {
		   fprintf(stderr,"Error, cannot open proof file %s\n", "tmpout.bin");
   		exit(1);
	}

#ifdef MSDOS
   _fstrcpy(title_str, "Bitstream 4in1 Font Processor Sampler\n");
#else
   strcpy(title_str, "Bitstream 4in1 Font Processor Sampler\n");
#endif
   sprintf(command,"\33*p+120Y\33*p575X\33(0U\33(s1p16v0s3b4101T%s", title_str);
   hpwc(command);

   for (i = 0; i < no_arg-1; i++)
   {
	   if (!open_font(argv[i+1]))
      {
      	fprintf(stderr,"Unable to open font file %s\n",argv[i+1]);
   	   exit (1);
      }

   	fread(buf, 1, 10, font_fp);
   	fseek(font_fp, 0L, SEEK_SET);
   
       /* determine type of font */
   	if ( strncmp(buf, "%!", 2) == 0 )
      {
   		setup = setup_type1_font(PARAMS1);        
	sprintf(title_str, "%s %s", gType1Hdr, argv[i+1]);
      	fprintf(stderr, "%s%s%s%s\n", gProcessing, gType1Hdr, gFile, argv[i+1]);
      }
      else if (buf[0]  == 0x80)
   		/* check for pfb type1 font */
      {
   		setup = setup_type1_font(PARAMS1);   
	sprintf(title_str, "%s %s", gType1Hdr, argv[i+1]);
      	fprintf(stderr, "%s%s%s%s\n", gProcessing, gType1Hdr, gFile, argv[i+1]);
      }
      else if (strncmp(buf, "D1.0", 4) == 0)
      {
   		/* set up for Speedo font */
   		setup = setup_speedo_font(PARAMS1);       
	sprintf(title_str, "%s %s", gSpeedoHdr, argv[i+1]);
	      fprintf(stderr, "%s%s%s%s\n", gProcessing, gSpeedoHdr, gFile, argv[i+1]);
      }
   	else if (strncmp(buf, ")s", 3) == 0)
      {
   		setup = setup_eo_font(PARAMS2 argv[i+1]);
	sprintf(title_str, "%s %s", gPCLHdr, argv[i+1]);
	      fprintf(stderr, "%s%s%s%s\n", gProcessing, gPCLHdr, gFile, argv[i+1]);
      }
      else
      {
         setup = setup_tt_font(PARAMS1);
	sprintf(title_str, "%s %s", gTrueTypeHdr, argv[i+1]);
	      fprintf(stderr, "%s%s%s%s\n", gProcessing, gTrueTypeHdr, gFile, argv[i+1]);
      }
	   strcat(title_str, "\n");

   	if (!setup)
         exit(setup);			/* error in setup */
   
		space_width = fi_get_char_width(PARAMS2 &spaceID);
		if (!space_width)
			space_width = ((sp_globals.metric_resolution << 16) +
							(sp_globals.metric_resolution >> 1)) /
							sp_globals.metric_resolution;
		gBitmapWidth = SetWidthToPixelWidth(space_width);
      hp_proof_prologue_no_open();
   	for (char_index = 0; char_index < 95; char_index++)   /* For each character in encoding */
  	   {
         char_id = proof_string[char_index];   
         if (char_id == '~')
            char_id = 171; /* translate tilde to BCID for tilde */
         hp_char_id = char_id;
/*     	   gBitmapWidth = SetWidthToPixelWidth(fi_get_char_width(&char_id)); */
     	   gBitmapWidth = SetWidthToPixelWidth(fi_get_char_width(PARAMS2 &char_id));
         fi_make_char(PARAMS2 &char_id);
  	   }

 		hp_proof_epilog_no_close();
		/* finished, restore order to the Shire... */

	   switch(font_type)
   	{
		case procTrueType:
			tt_release_font(PARAMS1);
			break;
   		case procType1:
			tr_unload_font(font_ptr);
   			break;
		case procPCL:
			pf_unload_font();
			break;
   	}
   	close_font_file();

   	if (font_buffer)
		{
   		free(font_buffer);
		font_buffer = (ufix8 *)0;
		}
  }

  fclose(in_fp);
  hpwc("\33E\33*c0F");
  fclose(hpf_fp);

  exit(0);
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

#ifdef MSDOS
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


/****************************************************************************
  setup_type1_font()
      This function handles all the initializations for the Type1 font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling tr_load_font()
      .  setup the values for transformation metrics and call fi_set_specs()
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean setup_type1_font(PARAMS1)
GDECL
{

	font_type = procType1;
  	font_protocol = protoBCID;
	fi_reset(PARAMS2 font_protocol, font_type);  /* initialize processor */
	/* load font */
	if ( !tr_load_font(PARAMS2 &font_ptr) )
	{
      fprintf(stderr, "cannot load type 1 font\n");
		return(FALSE);
	}

	/* Initialization - set specs */  
	tspecs.Matrix[0] = (long)(300 / PT_PER_INCH * pointsize);
	tspecs.Matrix[1] = 0L << 16;
	tspecs.Matrix[2] = 0L << 16;
	tspecs.Matrix[3] = (long)(300 / PT_PER_INCH * pointsize);
	tspecs.Matrix[4] = 0L << 16;
	tspecs.Matrix[5] = 0L << 16;
	tspecs.Gen_specs = &gspecs;
	tspecs.Gen_specs->flags =  MODE_SCREEN;
	tspecs.Font.org = (unsigned char *)font_ptr;
	if (!fi_set_specs(PARAMS2 &tspecs))
   {
   	fprintf(stderr,"Unable to set requested specs.\n");
	   return (FALSE);
   }
   sp_globals.metric_resolution = 1000;
	font_encoding = tr_get_encode(PARAMS1);
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
static	boolean	setup_speedo_font(PARAMS1)
GDECL
{
	ufix16	first_char_index;

   font_protocol = protoBCID;
   font_type = procSpeedo;
   fi_reset(PARAMS2 font_protocol, font_type);

	fseek(font_fp, 0L, SEEK_END);
	fontbuf_size = ftell(font_fp);
	fseek(font_fp, 0L, SEEK_SET);
	if ( !fill_font_buffer(&font_buffer, fontbuf_size, font_fp))
		return(FALSE);
   first_char_index = read_2b(font_buffer + FH_FCHRF);
   no_font_chars = read_2b(font_buffer + FH_NCHRL);
	/* DO ENCRYPTION HERE */

	gbuff.org = font_buffer;
	gbuff.no_bytes = fontbuf_size;
	gspecs.xxmult = (long)(65536 * 300 / PT_PER_INCH * pointsize);
	gspecs.xymult = 0L << 16;      /* Coeff of Y to calculate X pixels */
	gspecs.xoffset = 0L << 16;     /* Position of X origin */
		/* Coeff of Y to calculate Y pixels */
   gspecs.yymult = (long)(65536 * 300 / PT_PER_INCH * pointsize);
	gspecs.yxmult = 0L << 16;      /* Coeff of X to calculate Y pixels */
	gspecs.yoffset = 0L << 16;     /* Position of Y origin */
	gspecs.flags = MODE_SCREEN;
	gspecs.out_info = 0;           /* output module information  */

	gspecs.pfont = &gbuff;
	tspecs.Gen_specs = &gspecs;

	if (!fi_set_specs(PARAMS2 &tspecs))
	{
		fprintf(stderr, "cannot set requested specs\n");    
		return(FALSE);
	}

	return(TRUE);
}

/****************************************************************************
  setup_tt_font()
      This function handles all the initializations for the TrueTyp font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling tt_load_font()
      .  setup the values for transformation metrics and call fi_set_specs()
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean setup_tt_font(PARAMS1)
GDECL
{
	font_protocol = protoBCID;
	font_type = procTrueType;
	fi_reset(PARAMS2 font_protocol, font_type);

	fseek(font_fp, 0L, SEEK_END);
	fontbuf_size = ftell(font_fp);
	fseek(font_fp, 0L, SEEK_SET);
	/* need buffer for tt_get_font_fragment() */
	if (!fill_font_buffer(&font_buffer, fontbuf_size, font_fp))
		return(FALSE);

   if (!tt_load_font_params(PARAMS2 0, 3, 1)) /* if loop font files, then put number of font */
					/* file here, i.e first, second, third, ...  == 0,1,2,...*/
	{
		fprintf(stderr, "cannot load truetype font\n");
		return(FALSE);
	}
   
	gspecs.xxmult = (long)(65536 * 300 / PT_PER_INCH * pointsize);
	gspecs.xymult = 0l << 16;
	gspecs.xoffset = 0l << 16;
	gspecs.yxmult = 0l << 16;
	gspecs.yymult = (long)(65536 * 300 / PT_PER_INCH * pointsize);
	gspecs.yoffset = 0l << 16;
	gspecs.flags = MODE_SCREEN;

	tspecs.Gen_specs = &gspecs;

	if (!fi_set_specs(PARAMS2 &tspecs))
	{
		fprintf(stderr,"Cannot set requested specs.\n");
		return(FALSE);
	}
   sp_globals.metric_resolution = 2048;
	no_font_chars = 256;
	return(TRUE);
}

/****************************************************************************
  setup_eo_font()
      This function handles all the initializations for the PCLeo font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling pf_load_pcl_font()
      .  setup the values for transformation metrics and call fi_set_specs()
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean	setup_eo_font(PARAMS2 pathname)
GDECL
char *pathname;
{
	font_type = procPCL;
	font_protocol = protoBCID;
   gListSorted = FALSE;

	fi_reset(PARAMS2 font_protocol, font_type);
	close_font_file();
	font_fp = NULL;
	if ( !pf_load_pcl_font(pathname, &eo_font) )
	{
		fprintf(stderr,"Can not load PCL font\n");
		return(FALSE);
	}

	gspecs.xxmult = (long)(65536 * 300 / PT_PER_INCH * pointsize);
	gspecs.xymult = 0l << 16;
	gspecs.xoffset = 0l << 16;
	gspecs.yxmult = 0l << 16;
	gspecs.yymult = (long)(65536 * 300 / PT_PER_INCH * pointsize);
	gspecs.yoffset = 0l << 16;
	gspecs.flags = MODE_SCREEN;

   gspecs.pfont = (buff_t STACKFAR *)&eo_font;

	tspecs.Gen_specs = &gspecs;	/* setup intermediary structure */
	   /* Set character generation specifications */
   if (!fi_set_specs(PARAMS2 &tspecs))
	{
      fprintf(stderr, "Cannot set requested specs\n");
		return (FALSE);
   }
   sp_globals.metric_resolution = 8782;
	no_font_chars = 256;
	return(TRUE);
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
    		printf("report_error(%d)\n", n);
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
fix15 i;
ufix16 size;
fix15 xmin, ymin, xmax, ymax;
ufix32 bitmapWidth;


#if DEBUG
	printf("open_bitmap(%3.1f, %3.1f, %3.1f, %3.1f, %d, %d)\n",
   	 (real)x_set_width / 65536.0, (real)y_set_width / 65536.0,
	    (real)xorg / 65536.0, (real)yorg / 65536.0, (int)xsize, (int)ysize);
#endif

	/* create a HP soft font from the speedo font */
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

		/* don't do anything else, just return */
	return;

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
	fix15 i;
	fix15 first_word, last_word;
	fix15 bytwid;


#if DEBUG
	printf("set_bitmap_bits(%d, %d, %d)\n", (int)y, (int)xbit1, (int)xbit2);
#endif


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

	return;

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



GetSFNTFunc tt_get_font_fragment (clientID, offset, length)
int32  clientID;
int32 offset;
int32 length;

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


buff_t STACKFAR * WDECL sp_load_char_data(PARAMS2 file_offset, no_bytes, cb_offset)
GDECL
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
   	mult = ABS(tspecs.Gen_specs->xxmult) + ABS(tspecs.Gen_specs->yxmult);
/*   	mult = ABS(sp_globals.specs.xxmult) + ABS(sp_globals.specs.yxmult); */
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
	char command[128];

		/* make this soft font 100 */
	hpwc (ESC_ASSIGN_FONT_100);

		/* compose soft font header struct */
	new_hpfhd(&hpfhd);

		/* write out "here comes new soft font header" in PCL'ease */
	hpwc (ESC_FONTHEAD);

		/* write out the struct stuffed in new_hpfhd() */
	fwrite((char *)&hpfhd, 1, sizeof(hpfhd), hpf_fp);

   sprintf(command, "\33&l%.4fC", 48/(PT_PER_INCH/pointsize) );
  	hpwc(command);

	return;
}




/****************************************************************************
  hp_proof_epilog_no_close()
      This function selects the soft font to use and sending the characters
      to the file by calling txt_layout().
*****************************************************************************/
void hp_proof_epilog_no_close()
{

		/* make the downloaded font permanent */
	hpwc (ESC_MAKE_FONT_PERM);
		/* select the downloaded font for use */
	hpwc (ESC_SELECT_FONT_100);

		/* create the proof sheet */
	txt_layout();

	return;
}





/****************************************************************************
  hpwc()
      This function writes a hp command string to the proof file.
*****************************************************************************/
void hpwc(char *command)
{
   fwrite(command, 1, strlen(command), hpf_fp);
   if ( ferror(hpf_fp) )
         exit(1);
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
    p->spacing = 1; /* proportional */
    p->symbol_set = 21; /* ascii */
    if (	font_type == procPCL)
         p->pitch = (SetWidthToPixelWidth(pcl5head.pitch*65536/8782)) * 4;
/*         p->pitch = (SetWidthToPixelWidth(pcl5head.pitch<<16)) * 4; */
    else
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
    /* strcpy(p->name,"Speedo Test"); */
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

#if  READTIME
void dummy_loader()
{
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
	struct timeb  ElapseBegin, ElapseEnd;
	long          CpuBegin, CpuEnd;
	long          seconds, result_seconds, result_milliseconds;
	float         real_time;
	ufix8         byte;

	/* get the system clock */
	ftime(&ElapseBegin);

	/* get the cpu clock */
	CpuBegin = clock();

	while (get_byte(&byte));

	/* get the cpu clock end time */
	CpuEnd = clock();

	/* get the system end time */
	ftime(&ElapseEnd);
	result_seconds = ElapseEnd.time - ElapseBegin.time;
	result_milliseconds = ElapseEnd.millitm - ElapseBegin.millitm;
	real_time = (float) result_seconds + (((float) result_milliseconds) / 1000.0);

	/* print out the results */
	printf("Total elapse time is  %f \n",real_time);
	printf("Total cpu time is     %f \n",(double)(CpuEnd - CpuBegin)/1000000.0);
}
#endif
										 


/****************************************************************************
  txt_layout()
      This function actually reads the text file and sends the characters to
      the file and does the layout.
*****************************************************************************/
void txt_layout()
{
   char *str, *tmp;
   int numread;
	char command[128];

   sprintf(command,"\33*p+120Y\33*p150X\33(0U\33(s1p12v0s3b4101T%s", title_str);
   hpwc(command);
   hpwc("\033&a0C");		/* move to the "0th" column */
  	hpwc("\033&a+1R");	/* move down one line */

	hpwc ("\33(100X");

   fseek(in_fp, 0L, SEEK_SET);
   str = (char *)malloc(1024);
   while ( ( numread = fread(str, sizeof( char ), 1024, in_fp) ) != 0 )
   {  
		 tmp = str;
       while (numread >0)
       {
         if (*tmp == '~')
            *tmp = 171;
         while (*tmp != '\n' && numread != 0)
         {
            if (*tmp == '~')
               *tmp = 171;
            putc(*tmp, hpf_fp);
            tmp++;
				numread--;
         }
			if ( numread != 0)
			{
		      putc('\n', hpf_fp);
				hpwc ("\33(100X");
				hpwc("\033&a0C");	
   	      tmp++;
				numread--;
			}
       }
   }
	free(str);
	return;
}
