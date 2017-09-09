/*****************************************************************************
*                                                                            *
*  DERIVED FROM ... -mhd@gensym, 4/28/93
*  Copyright 1989, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                         U.S. Patent No 4,785,391                           *
*                           Other Patent Pending                             *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
*  $Log: not supported by cvs2svn $
*  Revision 1.7  1993/05/03 19:34:22  mhd
*  forgot to reset horizontal/vertical scan lines to be both equal, and both 25.
*
 * Revision 1.6  1993/05/03  19:31:11  mhd
 * break scan_lines out into horizontal and vertical
 * neaten up line breaking in makefile
 *
 * Revision 1.5  1993/05/03  14:48:31  mhd
 * more mhddemo cleanup
 *
 * Revision 1.4  1993/05/03  14:33:18  mhd
 * More mhddemo simplification.
 *
 * Revision 1.3  1993/04/30  18:41:52  mhd
 * More minor improvements to mhddemo.c
 *
 * Revision 1.2  1993/04/29  18:02:58  mhd
 * More cleanup/tweaking of mhddemo.
 *
 * Revision 1.1  1993/04/28  22:52:27  mhd
 * Added mhddemo.c, a simplified version of 4demo, which makes simplifying
 * assumptions about the flags to be used.  In makefile, added support for
 * making mhddemo, as well as defining a new simpler set of flags to be used.
 * The new set of flags will continue to work with 4demo.  But, if the old
 * set of flags are used, mhddemo will no longer work.  To make mhddemo, you
 * type
 *
 * 	make mhddemo
 *
 * You run it the same as 4demo, e.g.,
 *
 * 	mhddemo f.pcl
 * .....
*****************************************************************************/

#include <stdio.h>
#include <setjmp.h>
#include <string.h>
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
#include "ufe.h"


#ifndef SEEK_SET
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0
#endif


/***** STATIC FUNCTIONS *****/
static boolean setup_type1_font ();
static boolean setup_speedo_font ();
static boolean setup_tt_font ();
static boolean setup_eo_font ();
static void *get_char_encoding ();
static fix15 read_2b ();


/***** STATIC VARIABLES *****/

#define MAX_BITS  256		/* Max line length of generated bitmap */

static char pathname[100];	/* Name of font file to be output */

static fix15 width_of_current_raster;
static fix15 height_of_current_raster;
static fix15 horizontal_offset_of_current_raster;
static fix15 vertical_offset_of_current_raster;
static fix15 x_in_current_raster;
static fix15 y_in_current_raster;

static int vertical_scan_lines, horizontal_scan_lines, rotation, oblique, mode_id;
static double pi = 3.1415926535;
static double r_rotation, r_oblique;
static char mode_option;

static ufix16 char_index;
static void *character;		/* can either be a charname for type1 */
				/* or a char index for speedo and tt */

static CHARACTERNAME **font_encoding;
static eFontProcessor font_type;
static ufix16  no_font_chars; /* number of characters to output */
     /* initialized in setup_?_font functions */
static ufix16  *font_table = NULL;  /* allocate as much space as you need */
static ufix8  *tt_font_buffer = NULL; /* allocated only for TrueType */
static ufix32  fontbuf_size; /* size of font buffer */
static specs_t  gspecs;
static buff_t  gbuff;
static eofont_t  eo_font;

static font_data *font_ptr;

static FILE *font_fp = NULL;



void *malloc_or_quit(size, purpose_message)
     int size;
     char *purpose_message;
{
  void *result;
  if ((result = (void *)malloc(size)) == NULL)
    /* Cast above is necessary because in some C's malloc returns (char *);
     in ANSI C it would be redundant.
     */
    {
      fprintf(stderr,"Cannot allocate memory for %s\n", purpose_message);
      exit(FALSE);
    }
  else
    {
      return(result);
    }
}
      




/*
  open_font_file_and_initialize_processor_per_type opens the file designated by pathname
  (a global variable to have been set up by the caller), sets the variable
  font_fp to the file stream, examines the beginning of the file to determine
  its type, and sets font_type to one of the four possible types: proc_Type1,
  procSpeedo, procPCL, or procTrueType.  Then it initializes the particular
  processor with a call to fi_reset.

  If there is an error opening the file, the program is exited with value
  FALSE, and an error message to the user.

  If there is an error allocating a small amount of memory used for temporary
  storage, the program is exited with an error message to the user.
  */

void open_font_file_and_initialize_processor_per_type()
{
  char *first_string;
  int first_byte;
  font_fp = fopen(pathname, "rb");
  if (font_fp == NULL)
    {
      fprintf(stderr,"Unable to open font file %s\n",pathname);
      exit (FALSE);
    }
  first_string = (char *)malloc_or_quit(20, "temporary buffer");
  fread(first_string, 1, 10, font_fp);
  fseek(font_fp, 0L, SEEK_SET);
  first_byte = fgetc(font_fp);
  fseek(font_fp, 0L, SEEK_SET);
  if ((strncmp(first_string, "%!", 2) == 0) || (first_byte  == 0x80))
    font_type = procType1;
  else if (strncmp(first_string, "D1.0", 4) == 0)
    font_type = procSpeedo;
  else if (strncmp(first_string, ")s", 3) == 0)
    font_type = procPCL;
  else
    font_type = procTrueType;
  free(first_string);
  
  if (font_type == procType1)
    fi_reset(protoPSName, font_type);
  else
    fi_reset(protoDirectIndex, font_type);

  return;
}


/****************************************************************************
   FILE:       mhddemo.c
   This module demonstrates how to display and print characters from a sample
   font.
*****************************************************************************/
int main(argc,argv)
     int argc;
     char *argv[];
{
  boolean setup;

  if (argc != 2)
    {
      fprintf(stderr,"Usage: 4demo {fontfile}\n\n");
      exit (1);
    }

  sprintf(pathname, argv[1]);
  open_font_file_and_initialize_processor_per_type(pathname);

  vertical_scan_lines = 25;
  horizontal_scan_lines = 25;
  mode_id = 1;			/* <=> s ("screen") mode option */
  rotation = 0;
  oblique = 0;
  r_rotation = pi*rotation/180;
  r_oblique  = pi*oblique/180;

  
  switch(font_type)
    {
    case procType1:
      setup = setup_type1_font();
      break;
    case procPCL:
      setup = setup_eo_font();
      break;
    case procTrueType:
      setup = setup_tt_font();
      break;
    case procSpeedo:
      setup = setup_speedo_font();
      break;
    }

  if (!setup) exit(setup);	/* exit if error in setup */
  
  /* output all of the characters in the encoding array */
  for (char_index = 0; char_index < no_font_chars; char_index++)
    {
      character = get_char_encoding(char_index);
      if (character != (void *)0)
	fi_make_char(character);
    }
  
  switch(font_type)
    {
    case procType1:
      tr_unload_font(font_ptr);
      break;
    case procPCL:
      pf_unload_font();
      break;
    case procTrueType:
      if (tt_font_buffer) free(tt_font_buffer);
      break;
    case procSpeedo:
      if (gbuff.org) free(gbuff.org);
      break;
    }
  
  if (font_fp) fclose(font_fp);
  if (font_table) free(font_table);
  
  exit(TRUE);
}



/****************************************************************************
  fill_font_buffer()
  Allocate a font buffer and load the whole font into that buffer.
  Sets the global variable fontbuf_size appropriately.
  This exits the program with value FALSE if it can't malloc; otherwise, it
  returns:
    TRUE if buffer loaded successfully
    FALSE if load buffer failed 
  *****************************************************************************/
boolean fill_font_buffer(ptr, fp)
     ufix8 **ptr;
     FILE *fp;
{
  ufix32 bytes_read, tmp;
  ufix16 bytes;
  
  fseek(fp, 0L, SEEK_END);
  fontbuf_size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  *ptr = (ufix8 *)malloc_or_quit(fontbuf_size, "font buffer");
  bytes_read = fread(*ptr, 1, fontbuf_size, fp);
  if (bytes_read != fontbuf_size)
    {
      fprintf(stderr,"Error reading font file.\n");
      return(FALSE);
    }
  return(TRUE);
}



/* Subfunctions of the setup functions below: xxmult, xymult, yxmult, yymult.
   These depend on the global variables scan_lines, r_rotation, and r_oblique.
   */

int xxmult()
{
  return(vertical_scan_lines*cos(r_rotation));
}

int xymult()
{
  return(vertical_scan_lines*(sin(r_rotation)+tan(r_oblique)*cos(r_rotation)));
}
  
int yxmult()
{
  return(horizontal_scan_lines*(-1*sin(r_rotation)));
}

int yymult()
{
  return(horizontal_scan_lines*(cos(r_rotation)-tan(r_oblique)*sin(r_rotation)));
}




/* set_up_gspecs ...
   */

void set_up_gspecs ()
{
  gspecs.xxmult = (long) xxmult() << 16;
  gspecs.xymult = (long) xymult() << 16;
  gspecs.yxmult = (long) yxmult() << 16;
  gspecs.yymult = (long) yymult() << 16;     
  gspecs.xoffset = 0l << 16;	/* position of x origin */
  gspecs.yoffset = 0l << 16;	/* position of y origin */
  gspecs.flags = mode_id;
}




/* set_up_font_table allocates a new font table, assigns it to font_table, and
   fills its elements beginning with 0, and on up to no_font_chars'th element
   with the integers beginning with first_char_index.  That is, font_table[0]
   is first_char_index, font_table[1] is first_char_index+1, etc.
   

   If allocation of the tspecs.Gen_specs structure fails, or if the call to
   fi_set_specs fails, this exits the program with value FALSE.  Otherwise,
   this returns this returns TRUE, if successful; FALSE, otherwise.
   
   This depends on the global variable no_font_chars, and sets the global
   variable font_table.
   
   This is a subfunction of the all of the setup functions below, except for
   the type1 setup function.
   */

int set_up_font_table(first_char_index)
     ufix16 first_char_index;
{
  ufix16 i;
  
  font_table = (ufix16 *)malloc_or_quit(no_font_chars*sizeof(ufix16), "font_table");
  for (i=0; i < no_font_chars; i++)
    font_table[i] = i + first_char_index;
  return(TRUE);
}



/* set_specs_or_quit either sets specs with a call to fi_set_specs, or else
   exits with the value FALSE after printing an error message.
   */

void set_specs_or_quit (specs)
     ufe_struct *specs;
{
  if (fi_set_specs(specs) == NULL)
    {
      fprintf(stderr,"Cannot set requested specs.\n");
      exit(FALSE);
    }
}






/****************************************************************************
  setup_type1_font()
  This function handles all the initializations for the Type1 font:
  .  load the font buffer by calling tr_load_font()
  .  setup the values for transformation metrics and call fi_set_specs()
  .  load font indecis into font_table if users chose to show all characters
  If allocation of the tspecs.Gen_specs structure fails, or if the call to
  fi_set_specs fails, this exits the program with value FALSE.  Otherwise,
  this returns:
    TRUE if successful
    FALSE if failed
  *****************************************************************************/
static boolean setup_type1_font()
{
  ufe_struct tspecs;
  
  if (tr_load_font(&font_ptr) == NULL)
    {
      fprintf(stderr, "cannot load type 1 font\n");
      return(FALSE);
    }
  
  /* Initialization - set specs */  
  tspecs.Matrix[0] = (real) xxmult();
  tspecs.Matrix[1] = (real) yxmult();
  tspecs.Matrix[2] = (real) xymult();
  tspecs.Matrix[3] = (real) yymult();
  tspecs.Matrix[4] = (real) 0.0;
  tspecs.Matrix[5] = (real) 0.0;
  tspecs.Gen_specs = (specs_t *)malloc_or_quit(sizeof(specs_t), "structure");
  tspecs.Gen_specs->flags =  mode_id;
  tspecs.Font.org = (unsigned char *)font_ptr;
  set_specs_or_quit(&tspecs);
  font_encoding = tr_get_encode();
  no_font_chars = 256;  
  return(TRUE);
}


/****************************************************************************
  setup_speedo_font()
  This function handles all the initializations for the Speedo font:
  .  load the font buffer by calling fill_font_buffer()
  .  setup the values for transformation metrics and call fi_set_specs()
  .  load font indecis into font_table if users chose to show all characters 

  If allocation of the tspecs.Gen_specs structure fails, or if the call to
  fi_set_specs fails, this exits the program with value FALSE.  Otherwise,
  this returns:
  TRUE if successful
  FALSE if failed
  *****************************************************************************/
static boolean setup_speedo_font()
{
  ufe_struct tspecs;
  ufix16 first_char_index;
  if (!fill_font_buffer(&gbuff.org, font_fp))
    return(FALSE);
  
  /* DO ENCRYPTION HERE */
  
  gbuff.no_bytes = fontbuf_size;
  set_up_gspecs();
  gspecs.out_info = 0; /* output module information  */
  
  gspecs.pfont = &gbuff;
  tspecs.Gen_specs = &gspecs;
  
  set_specs_or_quit(&tspecs);
  
  first_char_index = read_2b(gbuff.org + FH_FCHRF);
  no_font_chars = read_2b(gbuff.org + FH_NCHRL);
  return(set_up_font_table(first_char_index));
}


/****************************************************************************
  setup_tt_font()
  This function handles all the initializations for the TrueTyp font:
  .  load the font buffer by calling tt_load_font()
  .  setup the values for transformation metrics and call fi_set_specs()
  .  load font indecis into font_table if users chose to show all characters 

  If allocation of the tspecs.Gen_specs structure fails, or if the call to
  fi_set_specs fails, this exits the program with value FALSE.  Otherwise,
  this returns:
    TRUE if successful
    FALSE if failed
  *****************************************************************************/
static boolean setup_tt_font()
{
  ufe_struct tspecs;

  /* need buffer for tt_get_font_fragment() */
  if (!fill_font_buffer(&tt_font_buffer, font_fp))  /* tt_font_buffer communicates with
						    definition of tt_get_font_fragment,
						    q.v., below. -mhd
						    */
    return(FALSE);
  
  if (!tt_load_font(0)) /* if loop font files, then put number of font */
    /* file here, i.e first, second, third, ...  == 0,1,2,...*/
    {
      fprintf(stderr, "Cannot load truetype font\n");
      return(FALSE);
    }
  
  set_up_gspecs();
  
  tspecs.Gen_specs = &gspecs;
  
  set_specs_or_quit(&tspecs);

  no_font_chars = 256;
  return(set_up_font_table(0));
}


/****************************************************************************
  setup_eo_font()
  This function handles all the initializations for the PCLeo font:
  .  load the font buffer by calling pf_load_pcl_font()
  .  setup the values for transformation metrics and call fi_set_specs()
  .  load font indecis into font_table if users chose to show all characters

  If allocation of the tspecs.Gen_specs structure fails, or if the call to
  fi_set_specs fails, this exits the program with value FALSE.  Otherwise,
  this returns:
    TRUE if successful
    FALSE if failed
  *****************************************************************************/
static boolean setup_eo_font()
{
  ufe_struct tspecs;
  if (font_fp)
    fclose(font_fp);
  font_fp = NULL;
  if ( !pf_load_pcl_font(pathname, &eo_font) )
    {
      fprintf(stderr,"Can not load PCL font\n");
      return(FALSE);
    }

  

  /* sorry, we don't handle rotation for PCL; we slam it off */
  rotation = 0; oblique = 0; r_rotation = 0; r_oblique  = 0;

  set_up_gspecs ();
  gspecs.pfont = (buff_t *)&eo_font;
  tspecs.Gen_specs = &gspecs;	/* setup intermediary structure */

  set_specs_or_quit(&tspecs);

  no_font_chars = 256;
  return(set_up_font_table(0));
}





/****************************************************************************
  get_char_encoding()  
  get the pointer into the font table based on character index
  RETURNS:
  A pointer to a void.  It can either be a pointer to a character
  name for type1 or a pointer to a character index for other fonts
  *****************************************************************************/
static void *get_char_encoding(char_index)
 ufix16 char_index;
{
  if (font_type == procType1)
    {
      if (strcmp((char *)font_encoding[char_index], ".notdef") == 0)
	{
	  return((void *)0);
	}
      else
	{
	  return((void *)font_encoding[char_index]);
	}
    }
  else
    {
      return((void *)&font_table[char_index]);
    }
}



/*
 * sp_report_error is called by the character generator to report an error.
 *
 *  Since character data not available is one of those errors
 *  that happens many times, don't report it to user
 */

#define REPORT(tag, string) case tag: fprintf (stderr, (string)); break

void sp_report_error(n)     
     fix15 n;        /* Error identification number */
{  
  switch(n)
    {
      REPORT(1, "Insufficient font data loaded\n");
      REPORT(3, "Transformation matrix out of range\n");
      REPORT(4, "Font format error\n");
      REPORT(5, "Requested specs not compatible with output module\n");
      REPORT(7, "Intelligent transformation requested but not supported\n");
      REPORT(8, "Unsupported output mode requested\n");
      REPORT(9, "Extended font loaded but only compact fonts supported\n");
      REPORT(10, "Font specs not set prior to use of font\n");
      REPORT(12, "Unknown error case (12)");
      REPORT(13, "Track kerning data not available");
      REPORT(14, "Pair kerning data not available");
      REPORT(TR_NO_ALLOC_FONT, "Unknown error case (TR_NO_ALLOC_FONT)");
      REPORT(TR_NO_SPC_STRINGS, "*** Cannot malloc space for charstrings \n");
      REPORT(TR_NO_SPC_SUBRS, "*** Cannot malloc space for subrs\n");
      REPORT(TR_NO_READ_SLASH, "*** Cannot read / before charactername in Encoding\n");
      REPORT(TR_NO_READ_STRING, "*** Cannot read / or end token for CharString\n");
      REPORT(TR_NO_READ_FUZZ, "*** Cannot read BlueFuzz value\n");
      REPORT(TR_NO_READ_SCALE, "*** Cannot read BlueScale value\n");
      REPORT(TR_NO_READ_SHIFT, "*** Cannot read BlueShift value\n");
      REPORT(TR_NO_READ_VALUES, "*** Cannot read BlueValues array\n");
      REPORT(TR_NO_READ_ENCODE, "*** Cannot read Encoding index\n");
      REPORT(TR_NO_READ_FAMILY, "*** Cannot read FamilyBlues array\n");
      REPORT(TR_NO_READ_FAMOTHER, "*** Cannot read FamilyOtherBlues array\n");
      REPORT(TR_NO_READ_BBOX0, "*** Cannot read FontBBox element 0\n");
      REPORT(TR_NO_READ_BBOX1, "*** Cannot read FontBBox element 1\n");
      REPORT(TR_NO_READ_BBOX2, "*** Cannot read FontBBox element 2\n");
      REPORT(TR_NO_READ_BBOX3, "*** Cannot read FontBBox element 3\n");
      REPORT(TR_NO_READ_MATRIX, "*** Cannot read FontMatrix\n");
      REPORT(TR_NO_READ_NAMTOK, "*** Cannot read FontName / token\n");
      REPORT(TR_NO_READ_NAME, "*** Cannot read FontName\n");
      REPORT(TR_NO_READ_BOLD, "*** Cannot read ForceBold value\n");
      REPORT(TR_NO_READ_FULLNAME, "*** Cannot read FullName value\n");
      REPORT(TR_NO_READ_LANGGRP, "*** Cannot read LanguageGroup value\n");
      REPORT(TR_NO_READ_OTHERBL, "*** Cannot read OtherBlues array\n");
      REPORT(TR_NO_READ_SUBRTOK, "*** Cannot read RD token for subr\n");
      REPORT(TR_NO_READ_STRINGTOK, "*** Cannot read RD token in charstring\n");
      REPORT(TR_NO_READ_STDHW, "*** Cannot read StdHW value\n");
      REPORT(TR_NO_READ_STDVW, "*** Cannot read StdVW value\n");
      REPORT(TR_NO_READ_SNAPH, "*** Cannot read StemSnapH array\n");
      REPORT(TR_NO_READ_SNAPV, "*** Cannot read StemSnapV array\n");
      REPORT(TR_NO_READ_BINARY, "*** Cannot read binary data size for Subr\n");
      REPORT(TR_NO_READ_EXECBYTE, "*** Cannot read a byte after eexec\n");
      REPORT(TR_NO_READ_CHARNAME, "*** Cannot read charactername\n");
      REPORT(TR_NO_READ_STRINGBIN, "*** Cannot read charstring binary data\n");
      REPORT(TR_NO_READ_STRINGSIZE, "*** Cannot read charstring size\n");
      REPORT(TR_NO_READ_DUPTOK, "*** Cannot read dup token for subr\n");
      REPORT(TR_NO_READ_ENCODETOK, "*** Cannot read dup, def or readonly token for Encoding\n");
      REPORT(TR_NO_READ_EXEC1BYTE, "*** Cannot read first byte after eexec\n");
      REPORT(TR_NO_READ_LENIV, "*** Cannot read lenIV value\n");
      REPORT(TR_NO_READ_LITNAME, "*** Cannot read literal name after /\n");
      REPORT(TR_NO_READ_STRINGNUM, "*** Cannot read number of CharStrings\n");
      REPORT(TR_NO_READ_NUMSUBRS, "*** Cannot read number of Subrs\n");
      REPORT(TR_NO_READ_SUBRBIN, "*** Cannot read subr binary data\n");
      REPORT(TR_NO_READ_SUBRINDEX, "*** Cannot read subr index\n");
      REPORT(TR_NO_READ_TOKAFTERENC, "*** Cannot read token after Encoding\n");
      REPORT(TR_NO_READ_OPENBRACKET, "*** Cannot read { or [ in FontBBox\n");
      REPORT(TR_EOF_READ, "*** End of file read\n");
      REPORT(TR_MATRIX_SIZE, "*** FontMatrix has wrong number of elements\n");
      REPORT(TR_PARSE_ERR, "*** Parsing error in Character program string\n");
      REPORT(TR_TOKEN_LARGE, "*** Token too large\n");
      REPORT(TR_TOO_MANY_SUBRS, "*** Too many subrs\n");
      REPORT(TR_NO_SPC_ENC_ARR, "*** Unable to allocate storage for encoding array \n");
      REPORT(TR_NO_SPC_ENC_ENT, "*** Unable to malloc space for encoding entry\n");
      REPORT(TR_NO_FIND_CHARNAME, "*** get_chardef: Cannot find char name\n");
      REPORT(TR_INV_FILE, "*** Not a valid Type1 font file\n");
      REPORT(TR_BUFFER_TOO_SMALL, "*** Buffer provided too small to store essential data for type1 fonts \n");
      REPORT(TR_BAD_RFB_TAG, "*** Invalid Tag found in charactaer data\n");
    default: fprintf(stderr, "report_error(%d)\n", n); break;
    }
  return;
}
#undef REPORT  




/* 
 * sp_open_bitmap is called by the character generator to initialize a buffer 
 * prior to receiving bitmap data.
 */

void sp_open_bitmap(x_set_width, y_set_width, xorg, yorg, xsize, ysize)
     fix31 x_set_width;
     fix31 y_set_width;   	/* Set width vector */
     fix31 xorg;    		/* Pixel boundary at left extent of bitmap character */
     fix31 yorg;    		/* Pixel boundary at right extent of bitmap character */
     fix15 xsize;   		/* Pixel boundary of bottom extent of bitmap character */
     fix15 ysize;   		/* Pixel boundary of top extent of bitmap character */
{
  width_of_current_raster = xsize;
  height_of_current_raster = ysize;
  horizontal_offset_of_current_raster
    = (fix15)(xorg >> 16); vertical_offset_of_current_raster = (fix15)(yorg >> 16);
  if (width_of_current_raster > MAX_BITS)
    width_of_current_raster = MAX_BITS;
  x_in_current_raster = 0;
  y_in_current_raster = 0;
  
  printf("\nCharacter index = %d", char_index);  
  if (font_type == procType1) printf(", Name = %s", character);
  printf("\n");
  
  printf("set width = %3.1f, %3.1f\n\
open bitmap hex setwidth = %x\n\
X offset  = %d\n\
Y offset  = %d\n",
	 (real)x_set_width / 65536.0,
	 (real)y_set_width / 65536.0,
	 x_set_width,
	 horizontal_offset_of_current_raster,
	 vertical_offset_of_current_raster);
  printf("\n   ");
}





/* sp_set_bitmap_bits is called by the character generator to write
 * one row of pixels into the generated bitmap character.
 */

void sp_set_bitmap_bits (y, xbit1, xbit2)
     fix15     y;     /* Scan line (0 = first row above baseline) */
     fix15     xbit1; /* Pixel boundary where run starts */
     fix15     xbit2; /* Pixel boundary where run ends */
{ 
  /* clip to limits */
  if (xbit1 < 0) xbit1 = 0;  
  if (xbit2 < 0) xbit2 = 0;
  if (xbit1 > MAX_BITS) xbit1 = MAX_BITS;
  if (xbit2 > MAX_BITS) xbit2 = MAX_BITS;
  
  /* Output backlog of off bits, if any */
  while (y_in_current_raster < y)
    {
      while (x_in_current_raster < width_of_current_raster)
	{
	  printf(". ");
	  x_in_current_raster++;
	}
      x_in_current_raster = 0;
      printf("\n   ");
      y_in_current_raster++;
    }
  
  /* Add bits to current line */
  while (x_in_current_raster < xbit2)
    {
      if (x_in_current_raster < xbit1)
	{
	  printf(". ");
	}
      else
	{
	  printf("X ");
	}
      x_in_current_raster++;
    }
  
  return;
}




/* 
 * sp_close_bitmap is called by the character generator to indicate all
 * bitmap data that has been generated.
 */
void sp_close_bitmap()
{
  printf("\n");
}

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



/* This isn't called from this module, and a function of the same
   name is defined in truetype.   What's going on?

   Notice that only the offset argument is used in this definition.

   And notice that this uses the tt_font_buffer global variable.

   I think that this is redefining the "official" definition as
   a way to get it to use the file we've opened.

   Is this a hack?!

   --mhd@gensym

   */

GetSFNTFunc  tt_get_font_fragment (clientID, offset, length)
     fix31  clientID, offset, length;
     
     /* Returns a pointer to data extracted from the sfnt.
	tt_get_font_fragment must be initialized in the fs_GlyphInputType
	record before fs_NewSfnt is called.  */
{
  return ((GetSFNTFunc)((ufix8 *)tt_font_buffer+offset));
}



/* This is apparently needed.  What's it for?  Note that I'm
   explicitly releasing tt_font_buffer (previously known as
   font_buffer) in the main function, where it used to call
   this function.  But some other source file refers to this!
   -mhd@gensym, 5/3/93
   */

void tt_release_font_fragment (ptr)
     ufix8 *ptr;
     
     /* Returns the memory at pointer to the heap
      */
{
  return;
}

buff_t * sp_load_char_data(file_offset, no_bytes, cb_offset)
     fix31    file_offset;  /* Offset in bytes from the start of the font file */
     fix15    no_bytes;     /* Number of bytes to be loaded */
     fix15    cb_offset;    /* Offset in bytes from start of char buffer */
{
  /* DUMMY FUNCTION */
  buff_t *it;
  return(it);
}

