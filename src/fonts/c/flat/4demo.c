/*****************************************************************************
*                                                                            *
*  Copyright 1989, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                         U.S. Patent No 4,785,391                           *
*                           Other Patent Pending                             *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
*  $Log: not supported by cvs2svn $
*  Revision 1.6  1995/03/16 15:28:19  mhd
*  Get 4demo to work for truetype fonts -- use non-memory-bound font storage
*  scheme.  Add coded character display variation for ripdemo/fontrip.
*
 * Revision 1.5  1995/03/15  22:38:34  mhd
 * Fixed bogus handling of memory fragments for truetype fonts -- switch
 * completely to use of non-memory-bound approach, reading entire font
 * into memory, and making the fragment getter and fragment disposer act
 * accordingly.
 *
 * Revision 1.4  1995/03/14  00:29:36  mhd
 * Have this be up to date with my sandbox.  This is for me just an offline
 * version of the font files in /bt/.../ext/c, for offline testing and
 * development.
 *
 * Revision 1.3  1993/07/28  21:53:04  mhd
 * More work on getting 2d writer to work.  Bug with interference with
 * incl_outline discovered.  Documentation of improper hinting
 * of swiss721swa in problems.text.  Some more work on getting Kanji.  No
 * luck yet.
 *
 * Revision 1.2  1993/07/27  22:57:54  mhd
 * Latest series of changes around getting Kanji to work.  Some work maybe
 * on font bounding box issues, also.  See problems.text for latest issues
 * in detail.
 *
 * Revision 2.26  93/06/15  13:38:13  roberte
 * Added PROC_?? conditionals to isolate processors.
 * 
 * Revision 2.25  93/05/27  15:58:57  roberte
 * Added function prototype for read_4b() for PC happiness.
 * 
 * Revision 2.24  93/05/27  15:10:53  roberte
 * Added some mysteriously missing local variables to setup_speedo_font()
 * 
 * Revision 2.23  93/05/21  10:00:08  roberte
 *  Rounded out MSDOS specific code for SPEEDO_GLOBALS GLOBALFAR implementation. This was
 * not supported properly in this module.  Removed some OLDWAY blocks.
 * 
 * Revision 2.22  93/04/23  17:59:55  roberte
 * Added support for > 64K TrueType fonts.
 * Correct cast for malloc of tspecs.Gen_specs. Added some casts for strncmp's
 * Also Reverted some functions to standard K&R style.
 * 
 * Revision 2.21  93/04/21  15:47:41  roberte
 * Eliminated two left-handed casts in function get_char_encodinf().
 * Also returned MSDOS specific code block for size_t casts to malloc and _fmalloc.
 * 
 * Revision 2.20  93/04/01  14:39:46  roberte
 * Really implemented FONTFAR and added code for INCL_LCD option so speedo fonts > 64K can be used. 
 * 
 * Revision 2.19  93/03/17  12:52:10  roberte
 * Added tracking of BCID if the user input type is keyboard or BCID code.
 * 
 * Revision 2.18  93/03/15  13:45:29  roberte
 * Added comments. 
 * 
 * Revision 2.17  93/03/12  00:21:07  roberte
 * Added code to release/unload TrueType and PCL font memory. 
 * 
 * Revision 2.16  93/03/10  19:58:13  weili
 * added log header
 *                                                   *
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
#include <math.h>
#include <time.h>

#define SET_SPCS
#include "spdo_prv.h"
#include "stdef.h"
#include "type1.h"
#include "fnt_a.h"
#include "tr_fdata.h"
#include "errcodes.h"
#include "hp_readr.h"
#include "finfotbl.h"
#include "ufe.h"		/* Unified front end */


#ifndef SEEK_SET
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0
#endif


/***** STATIC FUNCTIONS *****/
static	boolean	open_font PROTO((char *pathname));
static 	void 		close_font_file PROTO((void));
static	boolean	setup_type1_font PROTO((PROTO_DECL1));
static	boolean	setup_speedo_font PROTO((PROTO_DECL1));
static	boolean	setup_tt_font PROTO((PROTO_DECL1));
static	boolean	setup_eo_font PROTO((PROTO_DECL1));
static	void		close_type1 PROTO((void));
static	void *get_char_encoding PROTO((ufix16 char_index));
static	fix15 	read_2b PROTO((ufix8 *pointer));
fix31 read_4b PROTO((ufix8 *pointer));

int main PROTO((int argc, char *argv[]));

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

static	char	pathname[100];      /* Name of font file to be output */

static   char  input_str[80];
static   fix15 input_type, ascii_type = 1, bcid_type = 2, all_type =3;
static   int   input_bcid;

static  	fix15  raswid;             /* raster width  */
static  	fix15  rashgt;             /* raster height */
static  	fix15  offhor;             /* horizontal offset from left edge of emsquare */
static  	fix15  offver;             /* vertical offset from baseline */
static  	fix15  y_cur;              /* Current y value being generated and printed */
static  	char   line_of_bits[2 * MAX_BITS + 1]; /* Buffer for row of generated bits */
static  	int  scan_lines, rotation, oblique, mode_id;
static	double pi = 3.1415926535;
static	double	r_rotation, r_oblique;
static   char   mode_option;

#if INCL_LCD
static  buff_t char_data;          /* Buffer descriptor for character data */
#endif
static  ufix16 minchrsz;              /* minimum character buffer size */
static	ufix16 char_index;
static	void		  *character; /* can either be a charname for type1 */
							/* or a char index for speedo and tt */

static	CHARACTERNAME **font_encoding;
static	eFontProcessor	font_type;
static	eFontProtocol	font_protocol;
static	ufix16			no_font_chars; /* number of characters to output */
										/* initialized in setup_?_font functions */
static	ufix16			*font_table = NULL;  /* allocate as much space as you need */
static	ufix8			FONTFAR *font_buffer = NULL; /* allocate only if needed */
static  ufix8 			FONTFAR *char_buffer;       /* Pointer to allocate Character buffer */
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
static boolean gKeyboardInput;
static gTheBCID;

static	FILE *font_fp = NULL;

/****************************************************************************
   FILE:       4demo.c
   This module demonstrates how to display and print characters from a sample
   font.
*****************************************************************************/

#if (defined (M_I86CM) || defined (M_I86LM) || defined (M_I86HM) || defined (M_I86SM) || defined (M_I86MM))
  /* then have we are using a microsoft compiler */
#else
  /* need to have a dummy _fmalloc for unix */
void *_fmalloc()
{
}
  /* need to have a dummy _fmemset for unix */
void *_fmemset()
{
}
  /* need to have a dummy _ffree for unix */
void _ffree()
{
}
#endif

int	main(argc,argv)
int argc;
char *argv[];
{
	boolean  		 	setup, getoutchar;
	unsigned char 	*buf, ch;
   int i;
   ufix16 tmp;
#if REENTRANT_ALLOC
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
#endif


	/* check for proper usage */
	if (argc != 2) 
   {
   	fprintf(stderr,"Usage: 4demo {fontfile}\n\n"); 
	   exit (1);
   }

#if DYNAMIC_ALLOC || REENTRANT_ALLOC
if (sizeof(SPEEDO_GLOBALS GLOBALFAR *) > sizeof(char *))
	sp_global_ptr = (SPEEDO_GLOBALS GLOBALFAR *)_fmalloc(sizeof(SPEEDO_GLOBALS));
else
	sp_global_ptr = (SPEEDO_GLOBALS GLOBALFAR *)malloc(sizeof(SPEEDO_GLOBALS));
if (sp_global_ptr)
	{
	if (sizeof(SPEEDO_GLOBALS GLOBALFAR *) > sizeof(char *))
		_fmemset(sp_global_ptr, (ufix8)0, sizeof(SPEEDO_GLOBALS));
	else
		memset(sp_global_ptr, (ufix8)0, sizeof(SPEEDO_GLOBALS));
	}
else
	{
	printf("Unable to allocate sp_global_ptr!\n");
	exit(1);
	}
#endif
	sprintf(pathname, argv[1]);

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
   
   fprintf(stderr, "3 ways to select your characters: \n");
   fprintf(stderr, "            1. type from keyboard\n");
   fprintf(stderr, "            2. BCID\n");
   fprintf(stderr, "            3. Show all characters\n\n");
   fprintf(stderr, "please select a way now: ");
   if ( (ch = getchar()) == '1' )
   {
      fprintf(stderr, "\nplease input the characters:\n");
      scanf("%s", input_str);
      input_type = ascii_type;
   }
   else if ( ch == '2' )
   {
      fprintf(stderr, "\nplease input the bcid: ");
      scanf("%d", &input_bcid);
      input_type = bcid_type;
   }
   else if ( ch == '3' )
   {
      fprintf(stderr, "\nyou selected to show all characters\n");
      input_type = all_type;
   }
   else 
   {
      fprintf(stderr, "invalid selection\n");
      exit(1);
   }

   gKeyboardInput = ( (input_type == ascii_type) || (input_type == bcid_type) );

	fprintf(stderr, "\nlines per em: ");
	scanf("%d", &scan_lines);
   fprintf(stderr, "\nchoose one of the following output module:\n");
   fprintf(stderr, "options are b: black writer\n");
   fprintf(stderr, "            s: screen writer\n");
   fprintf(stderr, "            o: outline writer\n");
   fprintf(stderr, "            2: 2D writer\n");
   fprintf(stderr, "            w: white writer\n");
   fprintf(stderr, "output module: ");
   scanf("%1s", &mode_option);
   switch (mode_option)
   {
      case 'b' : mode_id = 0; break;
      case 's' : mode_id = 1; break;
      case 'o' : mode_id = 2; break;
      case '2' : mode_id = 3; break;
      case 'w' : mode_id = 4; break;
      default  : printf("invalid selection\n");
                 exit(0);
   }
	fprintf(stderr, "\nrotation degree: ");
	scanf("%d", &rotation);
	fprintf(stderr, "\noblique degree: ");
	scanf("%d", &oblique);
	r_rotation = pi*rotation/180;
	r_oblique  = pi*oblique/180;

	fread(buf, 1, 10, font_fp);
	fseek(font_fp, 0L, SEEK_SET);

    /* determine type of font */
	if ( strncmp((char *)buf, "%!", 2) == 0 )
		/* set up for Type 1 font */
		setup = setup_type1_font(PARAMS1);        
   else if (buf[0]  == 0x80)
		/* check for pfb type1 font */
		setup  = setup_type1_font(PARAMS1);   
   else if (strncmp((char *)buf, "D1.0", 4) == 0)
		/* set up for Speedo font */
		setup = setup_speedo_font(PARAMS1);       
	else if (strncmp((char *)buf, ")s", 3) == 0)
		setup = setup_eo_font(PARAMS1);
   else
      setup = setup_tt_font(PARAMS1);
	free(buf);

	if (!setup)	exit(setup);			/* error in setup */

   if (input_type == all_type)
   {
   	/* output all of the characters in the encoding array */
   	for (char_index = 0; char_index < no_font_chars; char_index++)   /* For each character in encoding */
        {
   		character = get_char_encoding(char_index);
		getoutchar = (character != (void *)0);
	   	if (getoutchar)
       			fi_make_char(PARAMS2 character);
   	}
   }
   else if (input_type == ascii_type)
   {
      no_font_chars = strlen(input_str);
      for (i=0; i < no_font_chars; i++)
      {
         tmp = input_str[i];
		 gTheBCID = tmp;
        	fi_make_char(PARAMS2 &tmp );
   	 	/* press key to continue */
   		fprintf(stderr, "\n Press any key to continue, 'Q' to exit - ");
	    ch=getchar();
  		if ( ch =='Q' || ch == 'q' )
   	 		break ;
      }
   }
   else
   {
	  tmp = gTheBCID = input_bcid;
      fi_make_char(PARAMS2 &tmp );
   }

	switch(font_type)
	{
		case procType1:
			close_type1();
			break;
		case procTrueType:
#if PROC_TRUETYPE
			tt_release_font(PARAMS1);
#endif
			break;
		case procPCL:
#if PROC_PCL
			pf_unload_font();
#endif
			break;
	}
	close_font_file();

	if (font_table)
		free(font_table);
	if (font_buffer)
	{
#if INCL_LCD
	if (font_type == procSpeedo)
		if (sizeof(ufix8 FONTFAR *) > sizeof(ufix8 *))
			_ffree(char_buffer);
		else
			free(char_buffer);
#endif
	if (sizeof(ufix8 FONTFAR *) > sizeof(ufix8 *))
		_ffree(font_buffer);
	else
		free(font_buffer);
	}
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
static void close_font_file()
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
boolean		fill_font_buffer(ptr, size, fp)
ufix8 **ptr;
ufix32 size;
FILE *fp;
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
        if (sizeof(ufix8 FONTFAR *) > sizeof(ufix8 *))
#ifdef MSDOS
		    *ptr = (ufix8 FONTFAR *)_fmalloc((size_t)size);
#else
		    *ptr = (ufix8 FONTFAR *)_fmalloc(size);
#endif
        else
#ifdef MSDOS
		    *ptr = (ufix8 *)malloc((size_t)size);
#else
		    *ptr = (ufix8 *)malloc(size);
#endif
        if (*ptr == NULL)
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
	   .  load font indecis into font_table if users chose to show all characters 
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean setup_type1_font(PARAMS1)
GDECL
{
#if PROC_TYPE1
	ufe_struct tspecs;

   if (input_type == ascii_type || input_type == bcid_type)
      font_protocol = protoBCID;
   else
     	font_protocol = protoPSName;
	font_type = procType1;
	fi_reset(PARAMS2 font_protocol, font_type);  /* initialize processor */
	/* load font */
	if ( !tr_load_font(PARAMS2 &font_ptr) )
	{
      fprintf(stderr, "cannot load type 1 font\n");
		return(FALSE);
	}

	/* Initialization - set specs */  
	tspecs.Matrix[0] = (real) (scan_lines * cos(r_rotation));
	tspecs.Matrix[1] = (real) (scan_lines * (-1*sin(r_rotation)));
	tspecs.Matrix[2] = (real) (scan_lines * (sin(r_rotation)+tan(r_oblique)*cos(r_rotation)) );
	tspecs.Matrix[3] = (real) (scan_lines * (cos(r_rotation)-tan(r_oblique)*sin(r_rotation)) );
	tspecs.Matrix[4] = (real) 0.0;
	tspecs.Matrix[5] = (real) 0.0;
	if (sizeof(specs_t STACKFAR *) > sizeof(specs_t *))
		tspecs.Gen_specs = (specs_t STACKFAR *)_fmalloc(sizeof(specs_t));
	else
		tspecs.Gen_specs = (specs_t *)malloc(sizeof(specs_t));
	if (tspecs.Gen_specs == NULL)
	{
		fprintf(stderr,"Can not allocate structure.\n");
		return(FALSE);
	}
	tspecs.Gen_specs->flags =  mode_id;
	tspecs.Font.org = (unsigned char *)font_ptr;
	if (!fi_set_specs(PARAMS2 &tspecs))
   {
   	fprintf(stderr,"Unable to set requested specs.\n");
	   return (FALSE);
   }
#if RESTRICTED_ENVIRON
	font_encoding = tr_get_encode(PARAMS2 font_ptr);
#else
	font_encoding = tr_get_encode(PARAMS1);
#endif
	no_font_chars = 256;

	return(TRUE);
#else
   	fprintf(stderr,"Not set up for TYPE1 fonts!\n");
	return(FALSE);
#endif
}


/****************************************************************************
  setup_speedo_font()
      This function handles all the initializations for the Speedo font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling fill_font_buffer()
      .  setup the values for transformation metrics and call fi_set_specs()
	   .  load font indecis into font_table if users chose to show all characters 
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean	setup_speedo_font(PARAMS1)
GDECL
{
	ufe_struct	tspecs;
	ufix16	first_char_index, i;
	ufix32		bytes_read;
ufix8   temp[16];             /* temp buffer for first 16 bytes of font */
   ufix32      minbufsz;             /* minimum font buffer size to allocate */
   ufix8       FONTFAR *byte_ptr;

   if (input_type == ascii_type || input_type == bcid_type)
      font_protocol = protoBCID;
   else if (input_type == all_type)
      font_protocol = protoDirectIndex;
   font_type = procSpeedo;
   fi_reset(PARAMS2 font_protocol, font_type);

/* get minimum font buffer size - read first 16 bytes to get the minimum
   size field from the header, then allocate buffer dynamically  */

   bytes_read = fread(temp, sizeof(ufix8), 16, font_fp);

   if (bytes_read != 16)
	{
	   fprintf(stderr,"****** Error on reading %s: %x\n", pathname, bytes_read);
   	fclose(font_fp);
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
   	fclose(font_fp);
      exit(1);
	}
#endif
   if (sizeof(ufix8 FONTFAR *) > sizeof(ufix8 *))
      font_buffer = (ufix8 FONTFAR *)_fmalloc((ufix16)minbufsz);
   else
      font_buffer = (ufix8 *)malloc((ufix16)minbufsz);
      
   if (font_buffer == NULL)
	{
	   fprintf(stderr,"****** Unable to allocate memory for font buffer\n");
      fclose(font_fp);
      exit(1);
	}
#if DEBUG
   printf("Loading font file %s\n", pathname);
#endif

   fseek(font_fp, (ufix32)0, 0);
   if (sizeof(ufix8 FONTFAR *) > sizeof(ufix8 *))
   {
      byte_ptr = font_buffer;
      for (i=0; i< minbufsz; i++)
      {
         int ch;
         ch = getc(font_fp);
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
      bytes_read = fread((ufix8 *)font_buffer, sizeof(ufix8), (ufix16)minbufsz, font_fp);
      if (bytes_read == 0)
      {
         fprintf(stderr,"****** Error on reading %s: %x\n", pathname, bytes_read);
         fclose(font_fp);
         exit(1);
      }
   }

#if INCL_LCD
/* now allocate minimum character buffer */

   minchrsz = read_2b(font_buffer+FH_CBFSZ);

   if (sizeof(ufix8 FONTFAR *) > sizeof(ufix8 *))
      char_buffer = (ufix8 FONTFAR *)_fmalloc(minchrsz);
   else
      char_buffer = (ufix8*)malloc(minchrsz);

   if (char_buffer == NULL)
	{
	   fprintf(stderr,"****** Unable to allocate memory for character buffer\n");
      fclose(font_fp);
      exit(1);
	}
#endif

	/* DO ENCRYPTION HERE */

	gbuff.org = font_buffer;
    gbuff.no_bytes = bytes_read;
	gspecs.xxmult = (long)(scan_lines * cos(r_rotation)) << 16;     /* coeff of x to calculate x pixels */
	gspecs.xymult = (long)(scan_lines * ( sin(r_rotation)+tan(r_oblique)*cos(r_rotation) )) << 16;      /* coeff of y to calculate x pixels */
	gspecs.yxmult = (long)(scan_lines * (-1*sin(r_rotation))) << 16;      /* coeff of x to calculate y pixels */
	gspecs.yymult = (long)(scan_lines * ( cos(r_rotation)-tan(r_oblique)*sin(r_rotation) )) << 16;     /* coeff of y to calculate y pixels */
	gspecs.xoffset = 0l << 16;     /* position of x origin */
	gspecs.yoffset = 0l << 16;     /* position of y origin */
	gspecs.flags = mode_id;
	gspecs.out_info = 0;           /* output module information  */

	gspecs.pfont = &gbuff;
	tspecs.Gen_specs = &gspecs;

	if (!fi_set_specs(PARAMS2 &tspecs))
	{
		fprintf(stderr, "cannot set requested specs\n");    
		return(FALSE);
	}

	/* loading font indecis into font_table. */
	/* allocate font_table */

   if (input_type == all_type)
   {
      first_char_index = read_2b(font_buffer + FH_FCHRF);
      printf("\nFirst Character Index = %d (hex: %x)\n", (int)first_char_index, (int)first_char_index);
      no_font_chars = read_2b(font_buffer + FH_NCHRL);
   	if ( (font_table = (ufix16 *)malloc(no_font_chars*sizeof(ufix16))) == NULL)
   	{
   		fprintf(stderr,"Can't allocate font_table.\n");
   		return(FALSE);
   	}
   	for (i=0; i < no_font_chars; i++)
   		font_table[i] = i + first_char_index;
   }
	return(TRUE);
}


/****************************************************************************
  setup_tt_font()
      This function handles all the initializations for the TrueTyp font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling tt_load_font()
      .  setup the values for transformation metrics and call fi_set_specs()
	   .  load font indecis into font_table if users chose to show all characters 
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean setup_tt_font(PARAMS1)
GDECL
{
#if PROC_TRUETYPE
	ufe_struct	tspecs;
	ufix16 i;
	boolean goodLoad;

   if ( input_type == ascii_type || input_type == bcid_type)
   	font_protocol = protoBCID;
   else      
   	font_protocol = protoDirectIndex;
	font_type = procTrueType;
	fi_reset(PARAMS2 font_protocol, font_type);

	fseek(font_fp, 0L, SEEK_END);
	fontbuf_size = ftell(font_fp);
	fseek(font_fp, 0L, SEEK_SET);
	/* need buffer for tt_get_font_fragment() */
	/* for non-memory-bound systems, read font into memory,
	   point to it using global font_buffer, and offset into
	   this memory to obtain individual fragments
	   */
	if (!fill_font_buffer(&font_buffer, fontbuf_size, font_fp))
		return(FALSE);

	if (input_type != all_type)
	  goodLoad = tt_load_font_params(PARAMS2 (ufix32)font_fp, 3, 1);
	else
	  goodLoad = tt_load_font(PARAMS2 (ufix32)font_fp);

	if (!goodLoad)
	{
			fprintf(stderr, "cannot load truetype font\n");
			return(FALSE);
	}
	gspecs.xxmult = (long)(scan_lines * cos(r_rotation)) << 16;     /* coeff of x to calculate x pixels */
	gspecs.xymult = (long)(scan_lines * ( sin(r_rotation)+tan(r_oblique)*cos(r_rotation) )) << 16;      /* coeff of y to calculate x pixels */
	gspecs.yxmult = (long)(scan_lines * (-1*sin(r_rotation))) << 16;      /* coeff of x to calculate y pixels */
	gspecs.yymult = (long)(scan_lines * ( cos(r_rotation)-tan(r_oblique)*sin(r_rotation) )) << 16;     /* coeff of y to calculate y pixels */
	gspecs.xoffset = 0l << 16;     /* position of x origin */
	gspecs.yoffset = 0l << 16;     /* position of y origin */

	gspecs.flags = mode_id;

	tspecs.Gen_specs = &gspecs;

	if (!fi_set_specs(PARAMS2 &tspecs))
	{
		fprintf(stderr,"Cannot set requested specs.\n");
		return(FALSE);
	}
   if (input_type == all_type)
   {
   	no_font_chars = 256;
	   if ( (font_table = (ufix16 *)malloc(no_font_chars * sizeof (ufix16)) )
   			== NULL)
   	{
	   	fprintf(stderr,"Cannot allocate font encoding table.\n");
   		return(FALSE);
   	}
   	for (i=0; i < no_font_chars; i++)
   		font_table[i] = i;
   }
	return(TRUE);
#else
   	fprintf(stderr,"Not set up for TRUETYPE fonts!\n");
	return(FALSE);
#endif
}


/****************************************************************************
  setup_eo_font()
      This function handles all the initializations for the PCLeo font:
      .  setup the font protocol type and font type by calling fi_reset()
      .  load the font buffer by calling pf_load_pcl_font()
      .  setup the values for transformation metrics and call fi_set_specs()
	   .  load font indecis into font_table if users chose to show all characters 
  RETURNS:
      TRUE if successful
      FALSE if failed
*****************************************************************************/
static	boolean	setup_eo_font(PARAMS1)
GDECL
{
#if PROC_PCL
	ufix16 i;
	ufe_struct tspecs;

   if ( input_type == ascii_type || input_type == bcid_type)
   	font_protocol = protoBCID;
   else      
   	font_protocol = protoDirectIndex;

	font_type = procPCL;
	fi_reset(PARAMS2 font_protocol, font_type);
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
   gspecs.flags = mode_id;
   gspecs.pfont = (buff_t STACKFAR *)&eo_font;

	tspecs.Gen_specs = &gspecs;	/* setup intermediary structure */
	   /* Set character generation specifications */
   if (!fi_set_specs(PARAMS2 &tspecs))
	{
      fprintf(stderr, "Cannot set requested specs\n");
		return (FALSE);
   }

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
#else
   	fprintf(stderr,"Not set up for PCL fonts!\n");
	return(FALSE);
#endif
}


/****************************************************************************
  close_type1()
      close type1 font
*****************************************************************************/
static	void	close_type1()
{
#if PROC_TYPE1
	tr_unload_font(font_ptr);
#endif
	return;
}


/****************************************************************************
   get_char_encoding()  
      get the pointer into the font table based on character index
   RETURNS:
      A pointer to a void.  It can either be a pointer to a character
      name for type1 or a pointer to a character index for other fonts
*****************************************************************************/
static	void *get_char_encoding(char_index)
     ufix16 char_index;
/* ch is a pter to a void, because it will either be a pter to */
/* a ufix16 for a char depending on font type. If the character was not */
/* retrieved successfully, then function returns (void *)0 else it returns */
/* the pointer. */
{
	void *ch = (void *)0; /* assume failure */

	switch(font_type)
	{
		case procType1:
			ch = (void *)font_encoding[char_index];
			if (strcmp((char *)ch,".notdef") == 0)
				ch = (void *)0;
			break;

		case procTrueType:
		case procSpeedo:
		case procPCL:
			ch = (void *)&font_table[char_index];
			break;
	}
	return(ch);
}



#if REENTRANT_ALLOC
 void WDECL sp_report_error(sp_global_ptr,n)
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
#else
 void WDECL sp_report_error(n)
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
    		fprintf(stderr, "Insufficient font data loaded\n");
    		break;

		case 3:
    		fprintf(stderr, "Transformation matrix out of range\n");
    		break;

		case 4:
    		fprintf(stderr, "Font format error\n");
    		break;
                 
		case 5:
    		fprintf(stderr, "Requested specs not compatible with output module\n");
    		break;

		case 7:
    		fprintf(stderr, "Intelligent transformation requested but not supported\n");
    		break;

		case 8:
    		fprintf(stderr, "Unsupported output mode requested\n");
    		break;

		case 9:
    		fprintf(stderr, "Extended font loaded but only compact fonts supported\n");
    		break;

		case 10:
    		fprintf(stderr, "Font specs not set prior to use of font\n");
    		break;

		case 12:
    		break;

		case 13:
    		fprintf(stderr, "Track kerning data not available()\n");
    		break;

		case 14:
    		fprintf(stderr, "Pair kerning data not available()\n");
    		break;

		case TR_NO_ALLOC_FONT:
    		break;

		case TR_NO_SPC_STRINGS:
     		fprintf(stderr, "*** Cannot malloc space for charstrings \n");
     		break;

		case TR_NO_SPC_SUBRS:
     		fprintf(stderr, "*** Cannot malloc space for subrs\n");
     		break;

		case TR_NO_READ_SLASH:
     		fprintf(stderr, "*** Cannot read / before charactername in Encoding\n");
     		break;

		case TR_NO_READ_STRING:
     		fprintf(stderr, "*** Cannot read / or end token for CharString\n");
     		break;

		case TR_NO_READ_FUZZ:
     		fprintf(stderr, "*** Cannot read BlueFuzz value\n");
     		break;

		case TR_NO_READ_SCALE:
     		fprintf(stderr, "*** Cannot read BlueScale value\n");
     		break;

		case TR_NO_READ_SHIFT:
     		fprintf(stderr, "*** Cannot read BlueShift value\n");
     		break;

		case TR_NO_READ_VALUES:
     		fprintf(stderr, "*** Cannot read BlueValues array\n");
     		break;

		case TR_NO_READ_ENCODE:
     		fprintf(stderr, "*** Cannot read Encoding index\n");
     		break;

		case TR_NO_READ_FAMILY:
     		fprintf(stderr, "*** Cannot read FamilyBlues array\n");
     		break;

		case TR_NO_READ_FAMOTHER:
     		fprintf(stderr, "*** Cannot read FamilyOtherBlues array\n");
     		break;

		case TR_NO_READ_BBOX0:
     		fprintf(stderr, "*** Cannot read FontBBox element 0\n");
     		break;

		case TR_NO_READ_BBOX1:
     		fprintf(stderr, "*** Cannot read FontBBox element 1\n");
     		break;

		case TR_NO_READ_BBOX2:
     		fprintf(stderr, "*** Cannot read FontBBox element 2\n");
     		break;

		case TR_NO_READ_BBOX3:
     		fprintf(stderr, "*** Cannot read FontBBox element 3\n");
     		break;

		case TR_NO_READ_MATRIX:
     		fprintf(stderr, "*** Cannot read FontMatrix\n");
     		break;

		case TR_NO_READ_NAMTOK:
     		fprintf(stderr, "*** Cannot read FontName / token\n");
     		break;

		case TR_NO_READ_NAME:
     		fprintf(stderr, "*** Cannot read FontName\n");
     		break;

		case TR_NO_READ_BOLD:
     		fprintf(stderr, "*** Cannot read ForceBold value\n");
     		break;

		case TR_NO_READ_FULLNAME:
     		fprintf(stderr, "*** Cannot read FullName value\n");
     		break;

		case TR_NO_READ_LANGGRP:
     		fprintf(stderr, "*** Cannot read LanguageGroup value\n");
     		break;

		case TR_NO_READ_OTHERBL:
     		fprintf(stderr, "*** Cannot read OtherBlues array\n");
     		break;

		case TR_NO_READ_SUBRTOK:
     		fprintf(stderr, "*** Cannot read RD token for subr\n");
     		break;

		case TR_NO_READ_STRINGTOK:
     		fprintf(stderr, "*** Cannot read RD token in charstring\n");
     		break;

		case TR_NO_READ_STDHW:
     		fprintf(stderr, "*** Cannot read StdHW value\n");
     		break;

		case TR_NO_READ_STDVW:
     		fprintf(stderr, "*** Cannot read StdVW value\n");
     		break;

		case TR_NO_READ_SNAPH:
     		fprintf(stderr, "*** Cannot read StemSnapH array\n");
     		break;

		case TR_NO_READ_SNAPV:
     		fprintf(stderr, "*** Cannot read StemSnapV array\n");
     		break;

		case TR_NO_READ_BINARY:
     		fprintf(stderr, "*** Cannot read binary data size for Subr\n");
     		break;

		case TR_NO_READ_EXECBYTE:
     		fprintf(stderr, "*** Cannot read a byte after eexec\n");
     		break;

		case TR_NO_READ_CHARNAME:
     		fprintf(stderr, "*** Cannot read charactername\n");
     		break;

		case TR_NO_READ_STRINGBIN:
     		fprintf(stderr, "*** Cannot read charstring binary data\n");
     		break;

		case TR_NO_READ_STRINGSIZE:
     		fprintf(stderr, "*** Cannot read charstring size\n");
     		break;

		case TR_NO_READ_DUPTOK:
     		fprintf(stderr, "*** Cannot read dup token for subr\n");
     		break;

		case TR_NO_READ_ENCODETOK:
     		fprintf(stderr, "*** Cannot read dup, def or readonly token for Encoding\n");
     		break;

		case TR_NO_READ_EXEC1BYTE:
     		fprintf(stderr, "*** Cannot read first byte after eexec\n");
     		break;

		case TR_NO_READ_LENIV:
     		fprintf(stderr, "*** Cannot read lenIV value\n");
     		break;

		case TR_NO_READ_LITNAME:
     		fprintf(stderr, "*** Cannot read literal name after /\n");
     		break;

		case TR_NO_READ_STRINGNUM:
     		fprintf(stderr, "*** Cannot read number of CharStrings\n");
     		break;

		case TR_NO_READ_NUMSUBRS:
     		fprintf(stderr, "*** Cannot read number of Subrs\n");
     		break;

		case TR_NO_READ_SUBRBIN:
     		fprintf(stderr, "*** Cannot read subr binary data\n");
     		break;

		case TR_NO_READ_SUBRINDEX:
     		fprintf(stderr, "*** Cannot read subr index\n");
     		break;

		case TR_NO_READ_TOKAFTERENC:
     		fprintf(stderr, "*** Cannot read token after Encoding\n");
     		break;

		case TR_NO_READ_OPENBRACKET:
     		fprintf(stderr, "*** Cannot read { or [ in FontBBox\n");
     		break;

		case TR_EOF_READ:
     		fprintf(stderr, "*** End of file read\n");
     		break;

		case TR_MATRIX_SIZE:
     		fprintf(stderr, "*** FontMatrix has wrong number of elements\n");
     		break;

		case TR_PARSE_ERR:
     		fprintf(stderr, "*** Parsing error in Character program string\n");
     		break;

		case TR_TOKEN_LARGE:
     		fprintf(stderr, "*** Token too large\n");
     		break;

		case TR_TOO_MANY_SUBRS:
     		fprintf(stderr, "*** Too many subrs\n");
     		break;

		case TR_NO_SPC_ENC_ARR:
     		fprintf(stderr, "*** Unable to allocate storage for encoding array \n");
     		break;

		case TR_NO_SPC_ENC_ENT:
     		fprintf(stderr, "*** Unable to malloc space for encoding entry\n");
     		break;

		case TR_NO_FIND_CHARNAME:
     		fprintf(stderr, "*** get_chardef: Cannot find char name\n");
     		break;

		case TR_INV_FILE:
     		fprintf(stderr, "*** Not a valid Type1 font file\n");
     		break;

		case TR_BUFFER_TOO_SMALL:
     		fprintf(stderr, "*** Buffer provided too small to store essential data for type1 fonts \n");
     		break;

		case TR_BAD_RFB_TAG:
     		fprintf(stderr, "*** Invalid Tag found in charactaer data\n");
     		break;

		default:
    		fprintf(stderr, "report_error(%d)\n", n);
    		break;
	}
	return ;
} /* end of sp_report_error */


#if REENTRANT_ALLOC
 void WDECL sp_open_bitmap(sp_global_ptr, x_set_width, y_set_width, xorg, yorg, xsize, ysize)
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
#else
 void WDECL sp_open_bitmap(x_set_width, y_set_width, xorg, yorg, xsize, ysize)
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
	boolean negative;

#if DEBUG
	printf("open_bitmap(%3.1f, %3.1f, %3.1f, %3.1f, %d, %d)\n",
   	 (real)x_set_width / 65536.0, (real)y_set_width / 65536.0,
	    (real)xorg / 65536.0, (real)yorg / 65536.0, (int)xsize, (int)ysize);
#endif
	raswid = xsize;
	rashgt = ysize;
	negative = (xorg < 0);
	if (negative)
		xorg = -xorg;
	offhor = (fix15)(xorg >> 16);
	if (negative)
		offhor = -offhor;
	negative = (yorg < 0);
	if (negative)
		yorg = -yorg;
	offver = (fix15)(yorg >> 16);
	if (negative)
		offver = -offver;

	if (raswid > MAX_BITS)
   	 raswid = MAX_BITS;


	if (gKeyboardInput)
		{
		printf("\nCharacter BCID = %d\n", gTheBCID);
		}
	else
		{
		if (font_type == procType1)
			{
#if NAME_STRUCT
			printf("\nCharacter index = %d, NAME = %s\n", char_index, char_name->char_name);
#else
			printf("\nCharacter index = %d, NAME = %s\n", char_index, character);
#endif
			}
		else
			printf("\nCharacter index = %d\n", char_index);
		}
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

} /* end of sp_open_bitmap */


#if REENTRANT_ALLOC
 void WDECL sp_set_bitmap_bits (sp_global_ptr, y, xbit1, xbit2)
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
#else
 void WDECL sp_set_bitmap_bits (y, xbit1, xbit2)
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

#if 0 /* DEBUG */
	printf("set_bitmap_bits(%d, %d, %d)\n", (int)y, (int)xbit1, (int)xbit2);
#endif

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

	return ;
} /* sp_set_bitmap_bits */


#if REENTRANT_ALLOC
 void WDECL sp_close_bitmap(sp_global_ptr)
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
#else
 void WDECL sp_close_bitmap()
#endif
/* 
 * Called by character generator to indicate all bitmap data
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
 void sp_open_outline(sp_global_ptr, x_set_width, y_set_width, xmin, xmax, ymin, ymax)
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
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
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
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
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
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
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
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
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
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
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
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
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
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


static fix15 read_2b(pointer)
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


FUNCTION  GetSFNTFunc  tt_get_font_fragment (clientID, offset, length)
  int32  clientID, offset, length;

/* (Bitstream says: tt_get_font_fragment must be initialized in the
   fs_GlyphInputType record before fs_NewSfnt is called.)

   This uses the global font_buffer, which should have been initialized be an
   array of all the bytes in the truetype font file.  It returns a pointer to
   specified portion of that file.  Since we're keeping all of that file in
   memory, and since this is just a demo capable of having one and only one font
   file open at a time, we don't need clientID, which is the file pointer for
   the truetype -- we ignore it.  This simply offsets the pointer into the
   specified part of the font file. */
  
{
  return ((GetSFNTFunc)((ufix8 *)font_buffer+offset));
}

FUNCTION void tt_release_font_fragment (ptr)
  void *ptr;

/* Returns the memory at pointer to the heap.  Since we're not using the
   non-memory-bound-system model, i.e., not allocating fragments in little
   pieces that get swapped in and out, this does nothing. */
{
}


#if INCL_LCD
#if REENTRANT_ALLOC
FUNCTION buff_t STACKFAR * WDECL sp_load_char_data(sp_global_ptr, file_offset, no_bytes, cb_offset)
SPEEDO_GLOBALS GLOBALFAR *sp_global_ptr;
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
if (fseek(font_fp, (long)file_offset, (int)0) != 0)
    {
    printf("****** Error in seeking character\n");
    fclose(font_fp);     
    exit(1);
    }

if ((no_bytes + cb_offset) > minchrsz)
    {
    printf("****** Character buffer overflow\n");
    fclose(font_fp);     
    exit(3);
    }

if (sizeof(ufix8 FONTFAR *) > sizeof(ufix8 *))
	{
    byte_ptr = char_buffer+cb_offset;
    bytes_read = 0;
    for (i=0; i<no_bytes; i++)
        {
        *byte_ptr = (ufix8)getc(font_fp);
        byte_ptr++;
        bytes_read++;
       }
    }
else
    bytes_read = fread((char_buffer + cb_offset), sizeof(ufix8), no_bytes, font_fp);

if (bytes_read != no_bytes)
    {
    printf("****** Error on reading character data\n");
    fclose(font_fp);     
    exit(2);
    }

#if DEBUG
printf("Character data loaded\n");
#endif

char_data.org = (ufix8 FONTFAR *)char_buffer + cb_offset;
char_data.no_bytes = no_bytes;
return &char_data;
}
#else
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
#endif


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

/* EOF 4demo.c */

