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
*  Revision 1.1  1995/10/03 00:35:01  jra
*  Adding ext files from 4.0 Rev. 1 as initial commit for AB.
*
*  Revision 1.1  1993/05/19 22:01:53  mhd
*  Added Bitstream fontrip (Font Raster Image Processor) c & h files.  Not
*  all are compiles -- some are demos, or test modules.
*
 * Revision 1.1  1993/05/04  20:07:39  mhd
 * The flat-directory version of the Bitstream 4-in-1 software.
 *
 * Revision 1.1.1.1  1993/04/15  20:14:44  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 2.19  93/03/15  13:52:20  roberte
 * Release
 * 
 * Revision 1.5  93/03/15  13:46:34  roberte
 * Added comments.
 * 
 * Revision 1.4  93/03/12  00:22:01  roberte
 * Added code to release/unload TrueType and PCL font memory.
 * Also null font_buffer when freeing.
 * 
 * Revision 1.3  93/03/10  20:01:37  weili
 * added log header
 * removed some unnecessary functions from the code.
 *                                                     *
*****************************************************************************/

/* !!!!!!!!!!!  RESTRICTED_ENVIRON NOT FUNCTIONING IN THIS .EXE !!!!! */

#include <stddef.h>
#include <stdio.h>
#include <setjmp.h>
#include <malloc.h>
#include <stdlib.h>
#include <dos.h>
#include <sys/timeb.h>
#include <string.h>

#ifdef MSDOS
#include <conio.h>
#include <graph.h>
#include <pgchart.h>
   float far values[24], *tmp_ptr;
	chartenv env;
   char far *processors[4];
   short no_processor;


#endif


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
#include "fino.h"

/***** STATIC FUNCTIONS *****/
static	boolean	open_font(char *pathname);
static 	void 		close_font_file(void);
static	boolean	setup_type1_font(void);
static	boolean	setup_speedo_font(void);
static	boolean	setup_tt_font(void);
static   boolean  init_specs_struct(long  lines_per_em, long mode_id);
static	boolean	setup_eo_font(void);
static	void		close_type1(void);
static	fix15 	read_2b(ufix8 *pointer);
static   void     clear_screen();
static   void     formdata(float far *data, int count);

static   float far tmp_cps[6], t1_cps[6], tt_cps[6], spd_cps[6], pcl_cps[6];                                                            


int main(int argc, char *argv[]);

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
#define BITMAP       0

#define MAX_BITS  256              /* Max line length of generated bitmap */

static	char	pathname[100];      /* Name of font file to be output */

static  	fix15  raswid;             /* raster width  */
static  	fix15  rashgt;             /* raster height */
static  	fix15  offhor;             /* horizontal offset from left edge of emsquare */
static  	fix15  offver;             /* vertical offset from baseline */
static  	fix15  y_cur;              /* Current y value being generated and printed */
static  	char   line_of_bits[2 * MAX_BITS + 1]; /* Buffer for row of generated bits */
static  	fix15  scan_lines;

static   char   mode_option;
static	ufix16 char_index;
static	ufix8		  *character; /* can either be a charname for type1 */
							/* or a char index for speedo and tt */
static   fix31    lpe[6]={10, 20, 30, 40, 50, 100};

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

#if RESTRICTED_ENVIRON
static	ufix8 	*font_ptr;
static 	ufix16 	buffer_size;
static	unsigned char big_buffer[10240];
			/* temp buffer to store char string */
#else
static	font_data *font_ptr;
#endif

static	FILE *font_fp = NULL;

char __far *cps[6] = {"10", "20", "30", "40", "50", "100"};

/****************************************************************************
   FILE:       4test.c
   This module provides a benchmark test, demonstrating how many characters
   per second each of the four processors generates, based on 62 characters
   per font (A-Z, a-z, 0-9).
*****************************************************************************/
int	main(argc,argv)
int argc;
char *argv[];
{
	boolean  setup, t1_done, tt_done, spd_done, pcl_done;
	unsigned char 	*buf;
   long     i, i2, i3;
   char     c, ch, fbuf[100];
   short    tmp, rep;
   long     seconds, result_seconds;
   long     milliseconds, result_milliseconds;
   real     real_time; 
   fix31    lines_per_em;
   short    nlpe, nparm, loop;
   fix15    mode_id;
   struct   timeb  timebuffer;
   FILE     *hdl;


	/* check for proper usage */
   if (argc < 2) 
   {
      fprintf(stderr,"Usage: 4test font1 [font2] [font3] [font4] [-m{bso2w}]\n");
      fprintf(stderr,"output module options are b: black writer\n");
      fprintf(stderr,"                          s: screen writer\n");
      fprintf(stderr,"                          o: outline writer\n");
      fprintf(stderr,"                          2: 2D writer\n");
      fprintf(stderr,"                          w: white writer\n");
      exit (1);
   }

   nlpe = 6;
   if ( strncmp(argv[argc-1], "-m", 2) == 0)
   {
    	sscanf(&argv[argc-1][2],"%1s",&mode_option);
      switch (mode_option)
      {
         case 'b' : mode_id = 0; break;
         case 's' : mode_id = 1; break;
         case 'o' : mode_id = 2; break;
         case '2' : mode_id = 3; break;
         case 'w' : mode_id = 4; break;
         default  : printf("invalid selection\n");
                    exit(1);
      }
      nparm = argc-2;
   }
   else
   {
      mode_id = MODE_SCREEN;  /* default output module */
   	nparm = argc - 1;
   }
   rep = 5;
   t1_done = tt_done = spd_done = pcl_done = FALSE;

   /* load font_table with BCID's of characters that shall be outputted, */
   /* namely, A-Z, a-z, 0-9. */
   if ( (font_table = (ufix16 *)malloc(62*sizeof(ufix16))) == NULL)
   {
      fprintf(stderr,"Can not allocate temporary buffer.\n");
      exit(FALSE);
   }
   tmp = 0;
   for (c = 'A'; c <= 'Z'; c++)
   {
      font_table[tmp] = (ufix16)c;
      tmp++;
   }
   for(c = 'a'; c <= 'z'; c++)
   {
      font_table[tmp] = (ufix16)c;
      tmp++;
  	}
   for (c = '0'; c <= '9'; c++)
   {
      font_table[tmp] = (ufix16)c;
      tmp++;
   }
   no_font_chars = tmp;

  	if ( (hdl = fopen("4bench.dat", "w")) == NULL)
   {
  	   fprintf(stderr,"Error opening output file\n");
     	exit(FALSE);
   }

	for  ( loop=1; loop <= nparm; loop++ )
	{
   	sprintf(pathname, argv[loop]);
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
	   {
			/* set up for Type 1 font */
         printf("Processing Type1 font...\n");
			setup = setup_type1_font();        
         t1_done = TRUE;
	   }
	   else if (buf[0]  == 0x80)
	   {
			/* check for pfb type1 font */
         printf("Processing Type1 font...\n");
			setup = setup_type1_font();   
         t1_done = TRUE;
	   }
	   else if (strncmp(buf, "D1.0", 4) == 0)
	   {
			/* set up for Speedo font */
         printf("Processing Speedo font...\n");
			setup = setup_speedo_font();       
         spd_done = TRUE;
	   }
		else if (strncmp(buf, ")s", 3) == 0)
	   {
			/* set up for PCL font */
         printf("Processing PCLeo font...\n");
			setup = setup_eo_font();
         pcl_done = TRUE;
	   }
	   else
	   {
         printf("Processing TrueType font...\n");
	      setup = setup_tt_font();
         tt_done = TRUE;
	   }
		free(buf);
	
		if (!setup)
	      exit(setup);			/* error in setup */

		/* output all of the characters in the encoding array */
	   for (lines_per_em = lpe[0], i3 = 0; i3 < nlpe; i3++, lines_per_em = lpe[i3])
	   {
	      if (!init_specs_struct(lines_per_em, mode_id))
	      {
	         fprintf(stderr,"Cannot set requested specs\n");
	         exit(FALSE);
	      }
         printf("lines_per_em = %d\n", lines_per_em);
	      ftime(&timebuffer);
	      for(i=0; i != rep; i++)
	      {
	         for (i2 = 0; i2 < no_font_chars; i2++)
	          	fi_make_char(&font_table[i2]);
	      }
	      seconds = timebuffer.time;
	      milliseconds = timebuffer.millitm;
	      ftime(&timebuffer);
	      result_seconds = (timebuffer.time) - seconds;
	      result_milliseconds = (timebuffer.millitm) - milliseconds;
	      real_time = (real) result_seconds + (((real) result_milliseconds) / 1000.0);
         tmp_cps[i3] = (real)rep*no_font_chars / real_time;
	   }
		switch(font_type)
		{
			case procType1:
              for (i=0; i<6; i++)
                  t1_cps[i] = tmp_cps[i];
              t1_done = TRUE;
        	     close_type1();
			     break;
			case procTrueType:
              for (i=0; i<6; i++)
                  tt_cps[i] = tmp_cps[i];
              tt_done = TRUE;
				 tt_release_font(PARAMS1);
			     break;
			case procSpeedo:
              for (i=0; i<6; i++)
                  spd_cps[i] = tmp_cps[i];
              spd_done = TRUE;
			     break;
			case procPCL:
              for (i=0; i<6; i++)
                  pcl_cps[i] = tmp_cps[i];
              pcl_done = TRUE;
				 pf_unload_font();
			     break;
		}
		close_font_file();
		if (font_buffer)
			{
			free(font_buffer);
			font_buffer = (ufix8 *)0;
			}
	} /* for */


   /* output performance result on the screen and to the file 4bench.dat */

   clear_screen();
   printf("\n\n\t\t\t    4-in-1 Performance Test\n");
   printf("\t\t\t    =======================\n\n\n\n");
	printf("\t\t   10\t   20\t   30\t   40\t   50\t  100\n");
   printf("\t\t                 (lines per em)\n");
	printf("\t\t------------------------------------------------\n\n");
   if (t1_done)
	{
      printf("Type1\t\t");
      formdata(t1_cps, 6);
      sprintf(fbuf,"Type1\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n", t1_cps[0], t1_cps[1], t1_cps[2], t1_cps[3], t1_cps[4], t1_cps[5]);
      fwrite(fbuf, 1, strlen(fbuf), hdl);
	}
   if (tt_done)
	{
      printf("TrueType\t");
      formdata(tt_cps, 6);
      sprintf(fbuf,"TrueType\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n", tt_cps[0], tt_cps[1], tt_cps[2], tt_cps[3], tt_cps[4], tt_cps[5]);
      fwrite(fbuf, 1, strlen(fbuf), hdl);
	}
   if (spd_done)
	{
      printf("Speedo\t\t");
      formdata(spd_cps, 6);
      sprintf(fbuf,"Speedo\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n", spd_cps[0], spd_cps[1], spd_cps[2], spd_cps[3], spd_cps[4], spd_cps[5]);
      fwrite(fbuf, 1, strlen(fbuf), hdl);
	}
   if (pcl_done)
	{
      printf("PCLeo\t\t");
      formdata(pcl_cps, 6);
      sprintf(fbuf,"PCL\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n", pcl_cps[0], pcl_cps[1], pcl_cps[2], pcl_cps[3], pcl_cps[4], pcl_cps[5]);
      fwrite(fbuf, 1, strlen(fbuf), hdl);
	}      
	printf("\n\t\t\t        (Char Per Second)\n");

   fclose(hdl);
	if (font_table)
		free(font_table);


#ifdef MSDOS
printf("\n\n\n\nDo you want to have line chart shown on the screen? (y or n) ");
if ( (ch = getchar()) == 'y' || ch == 'Y' )
{
   no_processor = 0;
   tmp = 0;
   tmp_ptr = values;
   if (t1_done)
   {
		processors[no_processor] = (char far *)malloc(16 * sizeof(char));
		strcpy(processors[no_processor++], "Type1");
		for (i=0; i<6; i++, tmp++)
			values[tmp] = t1_cps[i];
   }
   if (tt_done)
   {
		processors[no_processor] = (char *)malloc(20 * sizeof(char));
		strcpy(processors[no_processor++], "TrueType");
		for (i=0; i<6; i++, tmp++)
			values[tmp] = tt_cps[i];
   }
   if (spd_done)
   {
		processors[no_processor] = (char *)malloc(20 * sizeof(char));
		strcpy(processors[no_processor++], "Speedo");
		for (i=0; i<6; i++, tmp++)
			values[tmp] = spd_cps[i];
   }
   if (pcl_done)
   {
		processors[no_processor] = (char *)malloc(20 * sizeof(char));
		strcpy(processors[no_processor++], "PCL");
		for (i=0; i<6; i++, tmp++)
			values[tmp] = pcl_cps[i];
   }

   if ( !_setvideomode ( _MAXRESMODE ) )
   {
       printf("unable to set the video mode\n");
        exit (1);
   }

  	_pg_initchart();
    _pg_defaultchart ( &env, _PG_LINECHART, _PG_POINTANDLINE );
  	strcpy ( env.maintitle.title, "4in1 Performance Test");
  	env.maintitle.justify = _PG_RIGHT;
  	strcpy ( env.xaxis.axistitle.title, "lines per em");
  	strcpy ( env.yaxis.axistitle.title, "characters per second");
  	env.chartwindow.border = 0;
  	if ( _pg_chartms ( &env, cps, values, no_processor, 6, 6, processors) )
  	{
    	_setvideomode ( _DEFAULTMODE );
 	   _outtext ("Error: can't draw chart");
      exit (FALSE);
  	}
   else
   {
  		getch();
     	_setvideomode ( _DEFAULTMODE );
 		for (i=0; i<no_processor; i++)
          free(processors[i]);
      exit(TRUE);
  	}
}  
#endif
	exit(TRUE);
}  /* end of main function */


/****************************************************************************
  init_specs_struct()
      This function setup the values for transformation metrics and call
      fi_set_specs().
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static   boolean  init_specs_struct(long  lines_per_em, long mode_id)
{
	ufe_struct tspecs;

   if (font_type == procType1)
   {
   	tspecs.Matrix[0] = (real)lines_per_em;
	   tspecs.Matrix[1] = (real)0;
   	tspecs.Matrix[2] = (real)0;
	   tspecs.Matrix[3] = (real)lines_per_em;
   	tspecs.Matrix[4] = (real)0;
	   tspecs.Matrix[5] = (real)0;

   	tspecs.Font.org = (unsigned char *)font_ptr;
   }
   else
   {
   	gspecs.xxmult = (long)lines_per_em << 16;     /* coeff of x to calculate x pixels */
	   gspecs.xymult = 0l << 16;      /* coeff of y to calculate x pixels */
   	gspecs.xoffset = 0l << 16;     /* position of x origin */
	   gspecs.yxmult = 0l << 16;      /* coeff of x to calculate y pixels */
   	gspecs.yymult = (long)lines_per_em << 16;     /* coeff of y to calculate y pixels */
	   gspecs.yoffset = 0l << 16;     /* position of y origin */
	   gspecs.out_info = 0;           /* output module information  */

   	gbuff.org = font_buffer;
	   gbuff.no_bytes = fontbuf_size;
   }
	gspecs.flags = mode_id;

   if (font_type != procPCL)
   	gspecs.pfont = &gbuff;
   else
      gspecs.pfont = (buff_t STACKFAR *)&eo_font;


	tspecs.Gen_specs = &gspecs;

	if (!fi_set_specs(&tspecs))
	{
		fprintf(stderr, "cannot set requested specs\n");    
		return(FALSE);
	}
   return (TRUE);
}


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
	else
	   return TRUE;
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
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling tr_load_font()
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean setup_type1_font(void)
{
	font_type = procType1;
  	font_protocol = protoBCID;
	fi_reset(font_protocol, font_type);  /* initialize processor */
	/* load font */
	if ( !tr_load_font(&font_ptr) )
	{
      fprintf(stderr, "cannot load type 1 font\n");
		return(FALSE);
	}

	return(TRUE);
}

/****************************************************************************
  setup_speedo_font()
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling fill_font_buffer()
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean	setup_speedo_font(void)
{

   font_protocol = protoBCID;
   font_type = procSpeedo;
   fi_reset(font_protocol, font_type);

	fseek(font_fp, 0L, SEEK_END);
	fontbuf_size = ftell(font_fp);
	fseek(font_fp, 0L, SEEK_SET);
	if ( !fill_font_buffer(&font_buffer, fontbuf_size, font_fp))
		return(FALSE);

	/* DO ENCRYPTION HERE */

	return(TRUE);
}


/****************************************************************************
  setup_tt_font()
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling tt_load_font()
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean setup_tt_font(void)
{
	font_protocol = protoBCID;
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

	return(TRUE);
}


/****************************************************************************
  setup_eo_font()
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling pf_load_pcl_font()
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean	setup_eo_font(void)
{
	ufe_struct tspecs;

	font_type = procPCL;
	font_protocol = protoBCID;
	fi_reset(font_protocol, font_type);
	close_font_file();
	font_fp = NULL;
	if ( !pf_load_pcl_font(pathname, &eo_font) )
	{
		fprintf(stderr,"Can not load PCL font\n");
		return(FALSE);
	}

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

#if DEBUG
	printf("open_bitmap(%3.1f, %3.1f, %3.1f, %3.1f, %d, %d)\n",
   	 (real)x_set_width / 65536.0, (real)y_set_width / 65536.0,
	    (real)xorg / 65536.0, (real)yorg / 65536.0, (int)xsize, (int)ysize);
#endif
#if BITMAP
	fix15 i, j ;

	raswid = xsize;
	rashgt = ysize;
	offhor = (fix15)(xorg >> 16);
	offver = (fix15)(yorg >> 16);

	if (raswid > MAX_BITS)
   	 raswid = MAX_BITS;

#if NAME_STRUCT
	printf("\nCharacter index = %d, NAME = %s\n", char_index, char_name->char_name);
#else
	printf("\nCharacter index = %d, NAME = %s\n", char_index, character);
#endif
	printf("set width = %3.1f, %3.1f\n", (real)x_set_width / 65536.0, (real)y_set_width / 65536.0);
	printf("open bitmap hex setwidth = %x\n",x_set_width);
	printf("X offset  = %d\n", offhor);
	printf("Y offset  = %d\n\n", offver);


		for (i = 0; i < raswid; i++)
    	{
    		line_of_bits[i << 1] = '.';
    		line_of_bits[(i << 1) + 1] = ' ';
    	}
		line_of_bits[raswid << 1] = '\0';
		y_cur = 0;
#endif
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

#if DEBUG
	printf("set_bitmap_bits(%d, %d, %d)\n", (int)y, (int)xbit1, (int)xbit2);
#endif

#if BITMAP
	short i;

	/* If xbit1 is negative, set to zero, to keep index in range of
   	line_of_bits array */
	if (xbit1 < 0)
   	xbit1 = 0;

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
#endif
	return ;
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
#if BITMAP
	printf("    %s\n", line_of_bits);
#endif

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
#if BITMAP
	printf("\nopen_outline(%3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f)\n",
   	 (real)x_set_width / 65536.0, (real)y_set_width / 65536.0,
	    (real)xmin / 65536.0, (real)xmax / 65536.0, (real)ymin / 65536.0, (real)ymax / 65536.0);
#endif
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
#if BITMAP
	printf("start_new_char()\n");
#endif
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
#if BITMAP
	printf("start_contour(%3.1f, %3.1f, %s)\n", 
    	(real)x / 65536.0, (real)y / 65536.0, 
    	outside? "outside": "inside");
#endif
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
#if BITMAP
	printf("curve_to(%3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f)\n", 
    	(real)x1 / 65536.0, (real)y1 / 65536.0,
    	(real)x2 / 65536.0, (real)y2 / 65536.0,
    	(real)x3 / 65536.0, (real)y3 / 65536.0);
#endif
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
#if BITMAP
	printf("line_to(%3.1f, %3.1f)\n", 
    	(real)x / 65536.0, (real)y / 65536.0);
#endif
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
#if BITMAP
	printf("close_contour()\n");
#endif
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
#if BITMAP
	printf("close_outline()\n");
#endif
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
  clear_screen()
      Clear the screen by printing newline.
*****************************************************************************/
void clear_screen()
{
   int i;

   for (i=0; i<25  ; i++)
      printf("\n");
}


/****************************************************************************
  formdata()
      Put the calculated result (chars per sec) on the screen with justified
      decimal points.
*****************************************************************************/
void formdata(data, count)
int   count;
float far *data;
{
   int  i;

   for (i=0; i < count; i++)
   {
      if (*data >= 100 && *data < 1000)
         printf("%.3f\t", *data);
      else if (*data >= 10 && *data < 100)
         printf(" %.3f\t", *data);
      else
         printf("  %.3f\t", *data);
      data++;
   }
   printf("\n");
}
