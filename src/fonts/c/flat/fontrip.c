/* -*- Mode: C -*-
 *
 * Module FONTRIP
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Mark H. David
 *
 * This module, FONTRIP, contains the primitives used to interface G2's FONTS 
 * module, G2's XWINDOWS module, and the Bitstream 4in1 Font Raster Image 
 * Processor (RIP).
 *
 * This module currently exists in two places.  It is developed in
 * /bt/mhd/sun4/fonts/c/flat/fontrip.c, which is compiled using make
 * in that directory, and it is copied occasionally to /bt/mhd/ext/c/fontrip.c,
 * where it is compiled using "makecpp cprim opt".
 *
 * Included Fonts
 *
 * A limited number of included fonts are supported.  They are in h files whose
 * names are of the form <spdfontname>.h.  At present, the following built-in
 * fonts are supported:
 *
 *   font3004.h, corresponding to font3004.spd,
 *   which is the font SWISS-721-SWA, or Bitstream's
 *   version of Helvetica, set-width adjusted to Adobe's
 *   set widths.
 *
 *   slavic.h, corresponding to slavic.ttf, which is
 *   Exceller Corporation's Slavic (Cyrillic) version of
 *   Helvetica.  It is set-width adjusted to Microsoft's
 *   Windows Helvetica (Ariel), which is presumably the
 *   industry standard
 *
 * Included font files are generated from (.spd) font files by the development
 * utility function convert-binary-file-to-c-program on the Lisp module FONTS.
 *
 *
 * Definitions
 *
  Character ID, char_id
   - Previous Bitstream processors used the argument char_index
   or charname for the make_char, get_char_width, and get_char_bbox
   functions.    The Unifified Front End uses the argument char_id for
   these functions; char_id is based on the current mapping protocol
   passed to fi_reset(). [p. xv]

   - functions that use char_id:
     fi_make_char(char_id)
     fi_get_char_width(char_id)


   */

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

/* 
 * jh, 7/8/94.  Will need explicit externs for the following functions if we *
   ever decide to do ANSI-style argument prototypes, and they can do no harm *
   until then.  See my note this date in /bt/ab/rtl/c/gensym.h for details on *
   why I am visiting this file. */
extern void p_draw_point(/* long, long, long, long */);
extern void p_draw_line(/* long, long, long, long, long, long */);

/* Built-in Fonts (Included Fonts) */
/* - NOTE: keep entries and IDs in synch with */
/*   FONTS module. */
/* - #define'ing a FONTxxx_ID enables the code to handle */
/*   the built-in font. */
/* - To disable, simple comment out (= undefine) the */
/*   line with "#define FONTxxx_ID ..." */

#define FONT3004_ID 1
#ifdef FONT3004_ID
/* SWISS-721-SWA */
#include "font3004.h"
#endif

/* #define FONT3008_ID 2 */  /* Hold off enabling Courier for now. */
#ifdef FONT3008_ID
/* COURIER-SWA */
#include "font3008.h"
#endif

#define SLAVIC_ID 3
#ifdef SLAVIC_ID
/* Slavic Swiss TT (from slavic.ttf), a Helvetica-like Cyrillic Font */
/* NOTE: This file should ideally only contain Cyrillic characters; G2
   will never use the Roman characters included with it.  Removing the
   roman characters is tricky, and should best be done by the
   manufacturer.  This should save about 20K.  When possible, get a
   revised roman-stripped master version from them (Exceller
   Software)! -- MHD, 5/25/95

   Note: Eric Fikri, Exceller Software's president, informed us today
   (telephone message) that according to his engineer/subcontractor
   this font's widths are 100% compatible with the Windows95
   Helvetica-compatible font's widths. However, this has not been
   tested.  -- MHD, 5/25/95

   This is being introduced for use with G2 4.0 Rev. 1, which introduces
   Russian/Cyrillic support.

   Note that this is a truetype font, unlike the other two at present,
   which are speedo.
   */
#include "slavic.h"
#endif

#ifndef SEEK_SET
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0
#endif


/***** STATIC FUNCTIONS *****/
static fix15 read_2b ();

static boolean do_setup_for_isw_make_char();
static boolean do_setup_for_make_char();
static boolean do_setup_1_for_make_char();
static boolean fontrip_fill_font_buffer();
static fix15 load_outline_font_into_memory();
static boolean set_up_font_in_memory();


/***** STATIC VARIABLES *****/

#define MAX_BITS  256		/* Max line length of generated bitmap */


#if REENTRANT_ALLOC
static SPEEDO_GLOBALS *current_sp_global_ptr = NULL; /* Gensym-defined */
#endif

static fix15 width_of_current_raster;
static fix15 height_of_current_raster;
static fix31 x_set_width_of_current_raster; /* in Em units (16 fraction bits) */
static fix15 horizontal_textx_offset_of_current_raster;
static fix15 horizontal_offset_of_current_raster;
static fix15 vertical_offset_of_current_raster;
static fix15 x_in_current_raster;
static fix15 y_in_current_raster;

static int vertical_lines_per_em, horizontal_lines_per_em, rotation, oblique, mode_id;
static int default_mode_id = 3;	/* 1 = screen writer */
				/* 3 = 2D writer -- looks bad (buggy) in demo mode
				   --mhd, 7/28/93 */
static int fractional_vertical_lines_per_em = 0;   /* 8 fraction bits */
static int fractional_horizontal_lines_per_em = 0;

static fix31 cur_txtwdth_horiz_lines_per_em = -1;
static fix31 cur_txtwdth_vert_lines_per_em = -1;

static double pi = 3.1415926535;
static double r_rotation, r_oblique;

static ufix16 char_index;
static void *character;		/* can either be a charname for type1 */
				/* or a char index for speedo and tt */

static CHARACTERNAME **font_encoding;
static ufix16  no_font_chars; /* number of characters to output */
     /* initialized in setup_font_in_memory function */
static ufix8  *tt_font_buffer = NULL; /* allocated only for TrueType */
static ufix32  fontbuf_size; /* size of font buffer */






#define UNINITIALIZED_FONTRIP_OUTPUT_MODE 0 /* Used when specs need setting. */
#define GF_FILE_OUTPUT_MODE 1  		/* outputting GF Font Files (Obsolete) */
#define DEMO_OUTPUT_MODE 2		/* terminal output demo */
#define FONT_CHAR_RASTER_OUTPUT 3	/* production raster output use */
#define BBOX_GETTING_MODE 4		/* just for getting bounding box
					 note: this is needed due to lack
					 of functioning fi_get_char_bbox.
					 --mhd, 7/12/93
					 */

static int current_fontrip_output_mode = DEMO_OUTPUT_MODE;





/* Mapping to and from Pointers to Font Memory:

   assign_index_to_font_memory is the only interface to be used for assigning an
   index for a speedo font memory pointer.  It sets the next element of the
   mapping array, and returns the index.

   map_index_to_font_memory is the only interface to be used for mapping from an
   index to speedo font memory pointer.  It returns the font memory pointer assigned
   to index.

   The array font_memory_array is an array of pointers to font memory arrays, which
   are arbitrary-length arrays of ufix8's.  Its length, 250, is arbitrary -- but
   it's a lot more than we currently need.  In any case, it is not to be
   accessed directly: retrieve elements only through map_index_to_font_memory,
   q.v., below, and set elements only through assign_index_to_font_memory, q.v.,
   below.

   next_unassigned_font_memory_index points to the next element of
   font_memory_array available for setting.  It begins at 0. */


#define FONT_MEMORY_ARRAY_SIZE 250


/* current_font_memory_index is either negative, or is the current position in
   font_memory_array that has been initialized for use.

   If this is returned as a negative value to G2, it is taken to indicate a
   failure to allocate or obtain a font.  Furthermore, it is assumed that the
   value of FALSE is negative -- that's the value that gets returned instead of
   current_font_memory_index in the failure case; see set_up_font_in_memory.  */

static fix15 current_font_memory_index = -1;


/* next_unassigned_font_memory_index is the next available index.  When this is
   0, then there are not indexes available.  This may never go as high as or
   higher than FONT_MEMORY_ARRAY_SIZE. It is always incremented, never decremented.
   This should only set by the function assign_index_to_font_memory, below.
   */

static ufix16 next_unassigned_font_memory_index = 0;




/* speedo_global_pointer_array parallels font_memory_array with a
   speedo_global_pointer.  Whether the speedo global pointer may be
   used directly or has to be reinitialized depends on whether we've
   compiled with REENTRANT_ALLOC enabled.
   */
static SPEEDO_GLOBALS *speedo_global_pointer_array[FONT_MEMORY_ARRAY_SIZE];
static SPEEDO_GLOBALS *map_index_to_speedo_global_pointer(index)
     ufix16 index;
{
  return(speedo_global_pointer_array[index]);
}



/* FontMemory is the type compatible with the type for the built in fonts; e.g.,
   static ufix8 font3004_array[] = {...}

   font_memory_array is an array (FONT_MEMORY_ARRAY_SIZE long) of pointers to
   font memory (arrays of ufix8's) */

typedef ufix8 *FontMemory;
static FontMemory font_memory_array[FONT_MEMORY_ARRAY_SIZE]; 
static FontMemory map_index_to_font_memory(index)
     ufix16 index;
{
  return(font_memory_array[index]);
}


/* font_memory_length_array parallels font_memory_array and gives their lengths */

static ufix32 font_memory_length_array[FONT_MEMORY_ARRAY_SIZE]; 
static ufix32 map_index_to_length_of_font_memory(index)
     ufix16 index;
{
  return(font_memory_length_array[index]);
}


/* char_map_protocol_array parallels font_memory_array and gives their character
   mapping protocols (protBCID or protoDirectIndex).  */

static eFontProtocol char_map_protocol_array[FONT_MEMORY_ARRAY_SIZE]; 
static eFontProtocol map_index_to_char_map_protocol(index)
     ufix16 index;
{
  return(char_map_protocol_array[index]);
}



/* proc_type_protocol_array parallels font_memory_array and gives their
   processor type protocols (e.g., for truetype, speedo, type1, etc.)
   */

static eFontProcessor proc_type_protocol_array[FONT_MEMORY_ARRAY_SIZE]; 
static eFontProcessor map_index_to_proc_type_protocol(index)
     ufix16 index;
{
  return(proc_type_protocol_array[index]);
}


/* horizontal_lpm_array parallels font_memory_array and gives the horizontal
   lines per em as a text width for each font memory.  It's initialized to 0, in
   which case fi_set_specs needs to be called on the processor.

   set_horizontal_lpm_for_current_font_memory is the operation that should be
   used for setting this array.
   */

static fix31 horizontal_lpm_array[FONT_MEMORY_ARRAY_SIZE]; 
static fix31 map_index_to_horizontal_lpm(index)
     ufix16 index;
{
  return(horizontal_lpm_array[index]);
}

static fix31 set_horizontal_lpm_for_current_font_memory(horizontal_lpm)
  fix31 horizontal_lpm;
{
  return(horizontal_lpm_array[current_font_memory_index] = horizontal_lpm);
}


/* vertical_lpm_array parallels font_memory_array and gives the vertical
   lines per em as a text width for each font memory.  It's initialized to 0, in
   which case fi_set_specs needs to be called on the processor.

   set_vertical_lpm_for_current_font_memory is the operation that should be
   used for setting this array.
   */

static fix31 vertical_lpm_array[FONT_MEMORY_ARRAY_SIZE]; 
static fix31 map_index_to_vertical_lpm(index)
     ufix16 index;
{
  return(vertical_lpm_array[index]);
}

static fix31 set_vertical_lpm_for_current_font_memory(vertical_lpm)
  fix31 vertical_lpm;
{
  return(vertical_lpm_array[current_font_memory_index] = vertical_lpm);
}





/* assign_index_to_font_memory ... should be called after using fi_set_specs.
   This returns the index just assigned after setting current_font_memory_index
   to that index.
   */

static ufix16 assign_index_to_font_memory
(PARAMS2 font_memory, font_memory_length, character_mapping_protocol, processor_type)

GDECL
FontMemory 		font_memory;
ufix32 			font_memory_length;
eFontProtocol 		character_mapping_protocol;
eFontProcessor          processor_type;

{
  ufix16 i;

  i = next_unassigned_font_memory_index;
  next_unassigned_font_memory_index++;
  
#if REENTRANT_ALLOC
  speedo_global_pointer_array[i]	= sp_global_ptr;
#endif
  font_memory_array[i] 			= font_memory;
  font_memory_length_array[i] 		= font_memory_length;
  char_map_protocol_array[i] 		= character_mapping_protocol;
  proc_type_protocol_array[i]           = processor_type;
  
  current_font_memory_index = i;
  
  set_horizontal_lpm_for_current_font_memory(0);
  set_vertical_lpm_for_current_font_memory(0);
  
  return(i);
}



static ufix16 set_current_font_memory(index)
     ufix16 index;
{
  if (index != current_font_memory_index)
    {
#if REENTRANT_ALLOC
      current_sp_global_ptr = map_index_to_speedo_global_pointer(index);
#endif
#if DYNAMIC_ALLOC
      sp_global_ptr = map_index_to_speedo_global_pointer(index);
#endif
      current_font_memory_index = index;
    }
  return (index);
}




/* When REENTRANT_ALLOC is enabled, the font handle is the index in the speedo
   globals pointer array.  Then, when switching the current font, you just have
   to change pointers.  When REENTRANT_ALLOC is disabled, the font handle is the
   index to the font memory array.  Then, when switching the current font, you
   have to do an fi_reset, but the file doesn't have to be reloaded as we have
   its memory.

   */

#if DYNAMIC_ALLOC || REENTRANT_ALLOC

#if REENTRANT_ALLOC
#define ASSIGN_SP_LOCAL_TO_GLOBAL current_sp_global_ptr = sp_global_ptr;
#else
#define ASSIGN_SP_LOCAL_TO_GLOBAL
#endif

#define ALLOCATE_SP_GLOBALS_IF_NECESSARY \
  if (sp_global_ptr = (SPEEDO_GLOBALS *)malloc(sizeof(SPEEDO_GLOBALS))) \
    {\
      memset(sp_global_ptr, (ufix8)0, sizeof(SPEEDO_GLOBALS)); \
      ASSIGN_SP_LOCAL_TO_GLOBAL \
    }\
  else \
    { \
      printf("Unable to allocate sp_global_ptr!\n"); \
      exit(1); \
    }
#define SET_LOCAL_SPEEDO_GLOBALS_PTR sp_global_ptr = current_sp_global_ptr;
#else
#define ALLOCATE_SP_GLOBALS_IF_NECESSARY
#define SET_LOCAL_SPEEDO_GLOBALS_PTR
#endif /* REENTRANT_ALLOC or DYNAMIC_ALLOC */










/* ... */

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
      return(NULL);
    }
  else
    {
      return(result);
    }
}
      

/* get_processor_type_of_font takes "first_string", which should be a string
   containing at least the first 20 characters of a font file file.  It returns
   a heuristically determined processor type of the font. Note that if it cannot
   guess its type as being one of procType1, procSpeedo, or procPCL, it just
   guesses that it's procTrueType without even looking at the data in the
   file. */

eFontProcessor get_processor_type_of_font (first_string)
  char *first_string;
{
  int first_byte;
  
  first_byte = first_string[0];
  if ((strncmp(first_string, "%!", 2) == 0) || (first_byte  == 0x80))
    return(procType1);
  else if (strncmp(first_string, "D1.0", 4) == 0)
    return(procSpeedo);
  else if (strncmp(first_string, ")s", 3) == 0)
    return(procPCL);
  else
    return(procTrueType);
}



/* seek_processor_type_of_font_file takes a file pointer (fp), which is assumed
 reset to the beginning, and a string of at least length 20 (first_string) and
 reads enough of the file into first_string to guess its type, using the
 function above. This leaves the position for the next input on fp at 0, the first
 byte.  */

/* Note: no longer used. (MHD 2/16/95) */

eFontProcessor seek_processor_type_of_font_file (fp, first_string)
  FILE *fp;
  char *first_string;
{
  int first_byte;
  
  fread(first_string, 1, 20, fp);
  fseek(fp, 0L, SEEK_SET);
  return(get_processor_type_of_font(first_string));
}



/*
  open_font_file opens the file designated by pathname.

  If there is an error opening the file, this return NULL, after issuing an
  error message to the user.  

  If all goes well, this returns a pointer to the file just opened.

  */

FILE *open_font_file(pathname)
     char *pathname;
{
  FILE *fp;
  
  fp = fopen(pathname, "rb");
  if (fp == NULL)
    {
      fprintf(stderr,"Unable to open font file %s\n",pathname);
      return(NULL);
    }
  return(fp);
}

  






/* fontrip_get_char_bbox is a replacement for the system function
   fi_get_char_bbox.  The latter is not functioning yet.  When it
   is, we should replace this code with a call to that, or have callers
   use it directly.

   This works by setting current_fontrip_output_mode temporarily
   to a special value, BBOX_GETTING_MODE, in which the character
   is "made", but the user-defined output functions just collect
   the bounding box information.  (The old mode is restored on
   exit.)
   */

boolean fontrip_get_char_bbox(PARAMS2 char_id, bbox)
     GDECL
     void *char_id;
     bbox_t *bbox;
{
  int old_mode = current_fontrip_output_mode;
  boolean result;
  
  current_fontrip_output_mode = BBOX_GETTING_MODE;
  result = fi_make_char(PARAMS2 char_id);
  current_fontrip_output_mode = old_mode;
  if (result == TRUE)
    {
      /* NOTE: the casts to fix31 are done to agree with the actual code
	 that declares the bbox structure, not with the documentation of
	 it on page 7-62 of the 4-in-1 manual!  --MHD, 7/12/93
	 */
      bbox->xmin = (fix31)horizontal_offset_of_current_raster;
      bbox->xmax = (fix31)horizontal_offset_of_current_raster + (fix31)width_of_current_raster;
      bbox->ymin = (fix31)vertical_offset_of_current_raster;
      bbox->ymax = (fix31)vertical_offset_of_current_raster + (fix31)height_of_current_raster;
      return(TRUE);
    }
  else
    return(FALSE);
}





/* set_fontrip_globals ... used to set up the following globals:


   cur_txtwdth_horiz_lines_per_em
   cur_txtwdth_vert_lines_per_em

   vertical_lines_per_em
   horizontal_lines_per_em
   fractional_vertical_lines_per_em
   fractional_horizontal_lines_per_em

   mode_id

   rotation
   oblique
   r_rotation
   r_oblique

   Note that not all of these are parameterized at present; some are
   hardwared.
   
   */
   
static void set_fontrip_globals (text_width_horizontal_lines_per_em,
				 text_width_vertical_lines_per_em)
  fix31 text_width_horizontal_lines_per_em, text_width_vertical_lines_per_em;  
{

  /* used to keep track of and cache the current settings */
  cur_txtwdth_horiz_lines_per_em = text_width_horizontal_lines_per_em;
  cur_txtwdth_vert_lines_per_em = text_width_vertical_lines_per_em;
      
  /* scaling globals -- used by xxmult, et al */
  horizontal_lines_per_em = (int)(text_width_horizontal_lines_per_em >> 8);
  fractional_horizontal_lines_per_em = (int)(text_width_horizontal_lines_per_em & 0xff);
  vertical_lines_per_em = (int)(text_width_vertical_lines_per_em >> 8); 
  fractional_vertical_lines_per_em = (int)(text_width_vertical_lines_per_em & 0xff);


  /* No need to paramaterize these at present, but they could be. */
  /* Paramerization of mode_id will be necessary, e.g., to support downloading */
  /* outlines to printers. */
  mode_id = default_mode_id;
  rotation = 0; oblique = 0;
  r_rotation = pi*rotation/180; r_oblique = pi*oblique/180;
}



/* load_outline_font is called from G2's FONTS module.  It reads in the font in
   the file named by pathname.  It does various one-time initializations,
   including the call to fi_reset.  If all goes well, it returns a font memory
   index, a positive fixnum int that can be used to refer to the font in the
   future; if it fails, it returns a negative fixnum int.

   If zero_for_DirectIndex is 0, this uses protoDirectIndex as the character mapping
   protocol.  Otherwise, this uses protoBCID.  protoDirectIndex is used in G2 for
   Speedo Kanji fonts.  protoBCID is used for all other (i.e., Latin-based) fonts.
   */

/*
 * jh, 7/8/94.  Modified the argument and return types of the following function
 * as part of the project to ensure that foreign functions get the correct
 * argument and return types.  For further details, see my note this date in
 * /bt/ab/rtl/c/gensym.h.
 */

long load_outline_font(pathname, zero_for_DirectIndex_long)
     char *pathname;
     long zero_for_DirectIndex_long;
     
{
 int zero_for_DirectIndex = (int) zero_for_DirectIndex_long;
 {
  GDECL
  
  ALLOCATE_SP_GLOBALS_IF_NECESSARY
  return((long)load_outline_font_into_memory
	 (PARAMS2 pathname,
	  ((zero_for_DirectIndex==0) ? 0 : 1)));
 }
}



boolean fontrip_make_char (bcid, font_memory_index,
		   text_width_horizontal_lines_per_em,
		   text_width_vertical_lines_per_em,
		   imported_set_width_or_zero_for_none)
  fix15 font_memory_index;
 int bcid, text_width_horizontal_lines_per_em,
 text_width_vertical_lines_per_em, imported_set_width_or_zero_for_none;
{
  GDECL
    ufix16 bcid16;

  if (imported_set_width_or_zero_for_none == 0)
    {
      if (!do_setup_for_make_char
	  ((fix15)font_memory_index,
	   (fix31)text_width_horizontal_lines_per_em,
	   (fix31)text_width_vertical_lines_per_em)) {
	return(FALSE);
      }
    }
  else
    {
      if (!do_setup_for_isw_make_char
	  ((fix15)font_memory_index,
	   (fix31)bcid,
	   (fix31)text_width_horizontal_lines_per_em,
	   (fix31)text_width_vertical_lines_per_em,
	   (fix31)imported_set_width_or_zero_for_none))
	return(FALSE);
    }
	     
  SET_LOCAL_SPEEDO_GLOBALS_PTR
    bcid16 = (ufix16)bcid;
  character = (void *)&bcid16;
  return(fi_make_char(PARAMS2 character));
}



  


/* run_font_demo shows all of the characters in the font at pathname
   at the size specified by v, h, fractional_v, and fractional_h.
   */

/*
 * jh, 7/8/94.  Modified the argument and return types of the following function
 * as part of the project to ensure that foreign functions get the correct
 * argument and return types.  For further details, see my note this date in
 * /bt/ab/rtl/c/gensym.h.
 */
   
long run_font_demo(pathname, h_long, v_long, fractional_h_long, fractional_v_long)
     char *pathname;
     long h_long, v_long, fractional_h_long, fractional_v_long;
{
  int h = (int) h_long; 
  int v = (int) v_long;
  int fractional_h = (int) fractional_h_long;
  int fractional_v = (int) fractional_v_long;
    fix15 font_memory_index;

  /* Inserted ProcSpeedo into load_outline_font call below as temporary hack.  PGA */
  if ((font_memory_index = (fix15)load_outline_font(pathname, 0)) < 0) 
    return(-1);			/* negative => failure */

  current_fontrip_output_mode = DEMO_OUTPUT_MODE;
  
  for (char_index = 0; char_index < no_font_chars; char_index++)
    {
      fontrip_make_char(char_index, font_memory_index,
			(fix31)text_x_to_text_width(h_long, fractional_h_long),
			(fix31)text_x_to_text_width(v_long, fractional_v_long),
			0);
    } 
}


long run_bcid_char_demo
  (pathname, h_long, v_long, fractional_h_long, fractional_v_long)
     char *pathname;
     long h_long, v_long, fractional_h_long, fractional_v_long;
{
  int h = (int) h_long; 
  int v = (int) v_long;
  int fractional_h = (int) fractional_h_long;
  int fractional_v = (int) fractional_v_long;
    fix15 font_memory_index;

  int input_bcid;

  if ((font_memory_index = (fix15)load_outline_font(pathname, 1)) < 0)
    return(-1);			/* negative => failure */

  current_fontrip_output_mode = DEMO_OUTPUT_MODE;

  printf("\nPlease type a BCID: ");
  scanf ("%d", &input_bcid);
  printf("\nOK, %d ...\n", input_bcid);

  fontrip_make_char(input_bcid, font_memory_index,
		    (fix31)text_x_to_text_width(h_long, fractional_h_long),
		    (fix31)text_x_to_text_width(v_long, fractional_v_long),
		    0);
}








/*
;;; `Text-x-to-text-width' converts the text x represented by text-x-a and text-x-b
;;; to a text width.  The magnitude of the text x must be such that it can be
;;; converted to a text width that is within fixnum range.

(defmacro text-x-to-text-width (text-x-a text-x-b)
  `(+f (ashf ,text-x-a 8) ,text-x-b -128))
*/

int text_x_to_text_width (text_x_a, text_x_b)
   long text_x_a, text_x_b;
{
  return(((text_x_a << 8) + text_x_b) - 128);
}
 


static fix31 convert_to_text_width(x)
     fix31 x;
{
  return(x << 8);
}



/* load_outline_font_into_memory either returns a positive integer, the pointer */
/* or index to the font in memory, or FALSE, a negative integer. */

static fix15 load_outline_font_into_memory(PARAMS2 pathname, zero_for_DirectIndex)
     GDECL
     char *pathname;
     int zero_for_DirectIndex;

{
  eFontProtocol char_map_protocol;
  ufe_struct tspecs;
  ufix16 i;
  ufix8 *font_memory;
  FILE *fp;
  eFontProcessor processor_type;
  
  printf("\nOpening %s ... ", pathname);
  if ((fp = open_font_file(pathname)) == NULL)
    return(-1);
  if (!fontrip_fill_font_buffer(&font_memory, fp))
    {
      fprintf(stderr, "\nOutline Font %s Memory Buffer Setup Failed!\n", pathname);
      return(-1);
    }
  fclose(fp);
  printf("\nDONE.\n");
  
  if (zero_for_DirectIndex == 0)
    char_map_protocol = protoDirectIndex;
  else
    char_map_protocol = protoBCID;

  processor_type = get_processor_type_of_font(font_memory);
  
  if (set_up_font_in_memory
      (PARAMS2 font_memory, fontbuf_size, char_map_protocol, processor_type)
      == FALSE)
    return(FALSE);

  /* initialize */
  current_fontrip_output_mode == UNINITIALIZED_FONTRIP_OUTPUT_MODE;
      
  return(current_font_memory_index);
}



/* An `em-unit width' has 16 fraction bits.
   A `text width' has 8 fraction bits.

   Note: consider using em-units up in Lisp, and not having this module know
   about text widths, except perhaps the part concerned with writing GF files
   (which are obsolete).  */

fix31 convert_em_to_text_width(em_unit_width)
     fix31 em_unit_width;
{
  return(em_unit_width >> 8);
}

fix31 convert_text_to_em_unit_width(text_width)
     fix31 text_width;
{
  return(text_width << 8);
}




/* Subfunctions of the setup functions below: xxmult, xymult, yxmult, yymult.
   These depend on the global variables lines_per_em, r_rotation, and r_oblique.
   --UPDATE: Currently these do not handle rotation -- that can easily be
   enabled.  Refer to the documentation, or the original 4demo.c example, and
   adjust for the way we're handling the fractional part. (MHD 5/18/93)
   */

static long xxmult()
{
  return((long)((fractional_horizontal_lines_per_em << 8) + (horizontal_lines_per_em << 16)));
}

static long xymult()
{
  return((long) 0);
}
  
static long yxmult()
{
  return((long) 0);
}

static long yymult()
{
  return((long)((fractional_vertical_lines_per_em << 8) + (vertical_lines_per_em << 16)));
}





/* do_setup_1_for_make_char ... does the setup after setting the globals that
   control x/y scale.  

   This is only to be called from inside this module.

   Note: this currently handles only the speedo and truetype processor.  We
   anticipate adding support for the Type1 processor, and that should not be
   difficult.  we probably will never add support for back for PCLeo.
*/

static boolean do_setup_1_for_make_char (font_memory_index)
  fix15 font_memory_index;
{
  GDECL
  buff_t gbuff;
  specs_t gspecs;
  ufe_struct tspecs;

  set_current_font_memory(font_memory_index);
  SET_LOCAL_SPEEDO_GLOBALS_PTR
  set_horizontal_lpm_for_current_font_memory(cur_txtwdth_horiz_lines_per_em);
  set_vertical_lpm_for_current_font_memory(cur_txtwdth_vert_lines_per_em);
  switch (map_index_to_proc_type_protocol(font_memory_index))
    {
    case procTrueType:
    case procSpeedo:
      
      gbuff.org = map_index_to_font_memory(font_memory_index);
      gbuff.no_bytes = map_index_to_length_of_font_memory(font_memory_index);
      
      gspecs.pfont = &gbuff;
      gspecs.xxmult = xxmult();
      gspecs.xymult = xymult();
      gspecs.yxmult = yxmult();
      gspecs.yymult = yymult();
      gspecs.xoffset = 0l << 16; /* position of x origin */
      gspecs.yoffset = 0l << 16; /* position of y origin */
      gspecs.flags = mode_id;
      gspecs.out_info = 0;
      
      tspecs.Gen_specs = &gspecs;
      
      return(fi_set_specs(PARAMS2 &tspecs));
    }
}


static boolean do_setup_for_make_char
  (font_memory_index,
   text_width_horizontal_lines_per_em, text_width_vertical_lines_per_em)
  fix15 font_memory_index;
  fix31 text_width_horizontal_lines_per_em, text_width_vertical_lines_per_em;
{
  set_current_font_memory(font_memory_index);
  if ((font_memory_index != current_font_memory_index)
      || (cur_txtwdth_horiz_lines_per_em != text_width_horizontal_lines_per_em)
      || (cur_txtwdth_vert_lines_per_em != text_width_vertical_lines_per_em)
      || (map_index_to_horizontal_lpm(font_memory_index)
	  != text_width_horizontal_lines_per_em)
      || (map_index_to_vertical_lpm(font_memory_index)
	  != text_width_vertical_lines_per_em))
    {
      set_fontrip_globals
	(text_width_horizontal_lines_per_em, text_width_vertical_lines_per_em);
      return(do_setup_1_for_make_char(font_memory_index));
    }
  else
    return(TRUE);
}







int pixmap_for_current_character;


/* do_setup_for_isw_make_char -- do not use -- may not yet be working */
static boolean do_setup_for_isw_make_char (font_memory_index, char_id,
				    text_width_horizontal_lines_per_em,
				    text_width_vertical_lines_per_em,
				    imported_set_width_or_zero_for_none)
     fix15 font_memory_index;
     fix31 char_id,
       text_width_horizontal_lines_per_em,
       text_width_vertical_lines_per_em;
     fix31 imported_set_width_or_zero_for_none;
{
  GDECL
  fix31 em_unit_set_width;
  fix31 text_width_set_width;
  fix31 new_text_width_horizontal_lpm;

  /* We handle imported set widths as follows: 
     [1] Get the set width sw of the char_id at the current point 
     size.
     [2] Compute the ratio of the imported set width isw to sw, as isw/sw. 
     [3] Change the horizontal lines_per_em to lines_per_em * (isw/sw).
     */

  set_current_font_memory(font_memory_index);
  SET_LOCAL_SPEEDO_GLOBALS_PTR

  em_unit_set_width
    = fi_get_char_width(PARAMS2 char_id);

  text_width_set_width
    =  convert_em_to_text_width(em_unit_set_width);

  if (text_width_set_width != imported_set_width_or_zero_for_none)
    new_text_width_horizontal_lpm
      = ((text_width_horizontal_lines_per_em
	  * imported_set_width_or_zero_for_none)
	 / text_width_set_width);

  return(do_setup_for_make_char
	 (font_memory_index,
	  new_text_width_horizontal_lpm,
	  text_width_vertical_lines_per_em));
}

  

  

     

/* make_outline_character_raster returns TRUE (1) or FALSE (0). ...

   If imported_set_width_or_zero_for_none is 0, this makes characters
with the set width specified in the font.  Otherwise, it should be a
set width, as a text width, with the set width to impose.  In that
case, it calls sp_make_char_isw, which is a function that is compiler
switched based on INCL_ISW being 1 -- see useropt.h.  

   Note: we are using the imported set widths on a trial basis so that
we may use our Adobe Helvetica set widths with the Bistream Swiss 721
fonts.  We are also going to look at Bitstream's Swiss-721-SWA, which
has Adobe set widths build in.  This is still a good capability. -mhd

char_id should be a BCID, a Bitstream International Character Set ID.  
*/

/*
 * jh, 7/8/94.  Modified the argument and return types of the following function
 * as part of the project to ensure that foreign functions get the correct
 * argument and return types.  For further details, see my note this date in
 * /bt/ab/rtl/c/gensym.h.
 */

long make_outline_character_raster (font_memory_index_long,
				    pixmap_struct_index_long,
				    bcid_long,
				    text_width_horizontal_lines_per_em_long,
				    text_width_vertical_lines_per_em_long,
				    imported_set_width_or_zero_for_none_long)
     long font_memory_index_long;
     long pixmap_struct_index_long;
     long bcid_long;
     long text_width_horizontal_lines_per_em_long;
     long text_width_vertical_lines_per_em_long;
     long imported_set_width_or_zero_for_none_long;
{
  int font_memory_index = (int) font_memory_index_long;
  int pixmap_struct_index = (int) pixmap_struct_index_long;
  int bcid = (int) bcid_long;
  int text_width_horizontal_lines_per_em
    = (int) text_width_horizontal_lines_per_em_long;
  int text_width_vertical_lines_per_em
    = (int) text_width_vertical_lines_per_em_long;
  int imported_set_width_or_zero_for_none
    = (int) imported_set_width_or_zero_for_none_long;
  {
    pixmap_for_current_character = pixmap_struct_index;
    current_fontrip_output_mode = FONT_CHAR_RASTER_OUTPUT;

    if (fontrip_make_char
	(bcid, (fix15)font_memory_index,
	 text_width_horizontal_lines_per_em,
	 text_width_vertical_lines_per_em,
	 imported_set_width_or_zero_for_none))
      return((long)1);
    else
      return((long)0);
  }
}


  
  
/* get_bbox_width_and_height returns the width in the rightmost 12 bits, and
   the height in the second rightmost 12 bits.  Failure is indicated by a
   return of 0.
   */

/*
 * jh, 7/8/94.  Modified the argument and return types of the following function
 * as part of the project to ensure that foreign functions get the correct
 * argument and return types.  For further details, see my note this date in
 * /bt/ab/rtl/c/gensym.h.
 */

long get_bbox_width_and_height (font_memory_index_long, bcid_long,
				 text_width_horizontal_lines_per_em_long,
				 text_width_vertical_lines_per_em_long,
				 imported_set_width_or_zero_for_none_long)
 long font_memory_index_long;
 long bcid_long;
 long text_width_horizontal_lines_per_em_long;
 long text_width_vertical_lines_per_em_long;
 long imported_set_width_or_zero_for_none_long;
{
 int font_memory_index = (int) font_memory_index_long;
 int bcid = (int) bcid_long;
 int text_width_horizontal_lines_per_em 
     = (int) text_width_horizontal_lines_per_em_long;
 int text_width_vertical_lines_per_em
     = (int) text_width_vertical_lines_per_em_long;
 int imported_set_width_or_zero_for_none 
     = (int) imported_set_width_or_zero_for_none_long;
 {
  GDECL
  bbox_t bbox;
  ufix16 bcid16;

  if (imported_set_width_or_zero_for_none == 0)
    {
      if (do_setup_for_make_char
	  ((fix15)font_memory_index,
	   (fix31)text_width_horizontal_lines_per_em,
	   (fix31)text_width_vertical_lines_per_em)
	  == FALSE)
	return(NULL);
    }
  else
    {
      if (do_setup_for_isw_make_char
	  ((fix15)font_memory_index,
	   (fix31)bcid,
	   (fix31)text_width_horizontal_lines_per_em,
	   (fix31)text_width_vertical_lines_per_em,
	   (fix31)imported_set_width_or_zero_for_none)
	  == FALSE)
	return(NULL);
    }
	     
  SET_LOCAL_SPEEDO_GLOBALS_PTR
  bcid16 = (ufix16)bcid;
  character = (void *)&bcid16;
  if (fontrip_get_char_bbox (PARAMS2 character, &bbox))
    return(((bbox.ymax - bbox.ymin) << 12) + (bbox.xmax - bbox.xmin));
  else
    return(0);
 }
}



/*
 * jh, 7/8/94.  Modified the return types of the following 6 functions as part
 * of the project to ensure that foreign functions get the correct argument and
 * return types.  For further details, see my note this date in
 * /bt/ab/rtl/c/gensym.h.
 */

long get_textx_offset_for_cur_raster()
{
  return horizontal_textx_offset_of_current_raster;
}
/* above replaces following in actual use  -- MHD, 9/13/93 */

long get_x_offset_for_cur_raster()
{
  return horizontal_offset_of_current_raster;
}

long get_y_offset_for_cur_raster()
{
  return vertical_offset_of_current_raster;
}

long get_width_for_current_raster()
{
  return width_of_current_raster;
}
    

long get_height_for_current_raster()
{
  return height_of_current_raster;
}

long get_current_raster_text_width()
{
  return convert_em_to_text_width(x_set_width_of_current_raster);
}



fix31 convert_real_to_text_width(x)
     real x;
{
  double temp;
  temp = (double)(x * 256.0);
  if ((temp - (double)floor(temp)) < (double)0.5)	/* round */
    temp = (double)floor(temp);
  else
    temp = (double)ceil(temp);
  return((fix31)temp);
}


fix31 convert_real_to_em_unit_width(x)
     real x;
{
  double temp;
  temp = (double)(x * 0xffff);
  if ((temp - (double)floor(temp)) < (double)0.5)	/* round */
    temp = (double)floor(temp);
  else
    temp = (double)ceil(temp);
  return((fix31)temp);
}

fix31 fractional_em_unit_width(em_unit_width)
     fix31 em_unit_width;
{
  return(em_unit_width & 0xffff);
}


fix31 integer_em_unit_width(em_unit_width)
     fix31 em_unit_width;
{
  return(em_unit_width >> 16); /* <=> "em_unit_width / 65536.0" */
}

  
  

/****************************************************************************
  fontrip_fill_font_buffer()
  Allocate a font buffer and load the whole font into that buffer.
  Sets the global variable fontbuf_size appropriately.
  This exits the program with value FALSE if it can't malloc; otherwise, it
  returns:
    TRUE if buffer loaded successfully
    FALSE if load buffer failed 
  *****************************************************************************/
static boolean fontrip_fill_font_buffer(ptr, fp)
     ufix8 **ptr;
     FILE *fp;
{
  ufix32 bytes_read, tmp;
  ufix16 bytes;
  
  fseek(fp, 0L, SEEK_END);
  fontbuf_size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  if ((*ptr = (ufix8 *)malloc_or_quit(fontbuf_size, "font buffer"))
      == (ufix8 *)NULL) {
    return(FALSE);
  }

  bytes_read = fread(*ptr, 1, fontbuf_size, fp);
  if (bytes_read != fontbuf_size)
    {
      fprintf(stderr,"Error reading font file.\n");
      return(FALSE);
    }
  return(TRUE);
}





/****************************************************************************
  fill_font_buffer()
      Allocate a font buffer and load the whole font into that buffer.
  RETURNS:
      TRUE if buffer loaded successfully
      FALSE if load buffer failed
  NOTE: this is only to be used by load_pcl.c at this point -- see
  fontrip_fill_font_buffer, which has a different number of args.
*****************************************************************************/
boolean fill_font_buffer (ptr, size, fp)
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












/* set_up_font_in_memory makes the current font be the one corresponding to
   font_memory, which should be an array of ufix8's.  The first arg should be
   the conditionally compiled PARAMS2, i.e., the speedo globals pointer if using
   dynamic allocation of reentrant allocation.  The second and third arguments
   are font_memory and font_memory_size, the array of fix8's and its length,
   respectively.  The fourth argument is the character mapping protocol.  This
   can be one of the enumerated types, e.g., protoBCID or protoDirectIndex.

   For Gensym software, at present, we use protoBCID for all roman fonts, and we
   use protoDirectIndex for all Kanji fonts.

   This sets font_type to procSpeedo.  (At present, this is only set up to work
   with the the Speedo Processor.  Later, that restriction can and should be
   lifted.  An processor_type argument may then be needed.)
   UPDATE: This is now being fixed to work with parameterized processor_type.
   More later!

   */

static boolean set_up_font_in_memory
(PARAMS2 font_memory, font_memory_size, character_mapping_protocol, processor_type)
GDECL
ufix8 *font_memory;
ufix32 font_memory_size;
eFontProtocol character_mapping_protocol;
eFontProcessor processor_type;
{
  ufe_struct tspecs;
  ufix16 first_char_index;
  ufix16 index;
  boolean loaded_p;
      
  assign_index_to_font_memory
    (PARAMS2 font_memory,
     font_memory_size, character_mapping_protocol, processor_type);
  
  fi_reset(PARAMS2 character_mapping_protocol, processor_type);
  
  switch(processor_type)
    {
    case procSpeedo:
      first_char_index = read_2b(font_memory + FH_FCHRF);
      no_font_chars = read_2b(font_memory + FH_NCHRL);
      break;
    case procTrueType:
      /* this is one of the confusing parts of the truetype rasterizer/loader -- the way
	 you load it affects the way character mapping works. Unfortunately, Bitstream
	 only supplies "sample code" (tt_iface) and little or no documentation about
	 what should happen here.  */
      if (character_mapping_protocol == protoDirectIndex)
	loaded_p = tt_load_font(PARAMS2 current_font_memory_index);
      else
	loaded_p = tt_load_font_params(PARAMS2 current_font_memory_index, 3, 1);
      if (loaded_p == FALSE)
	{
	  fprintf(stderr, "cannot load truetype font\n");	
	  return(FALSE);
	}
      first_char_index = 0;
      no_font_chars = 256;
      break;
    }
  return(TRUE);
}



/*
 * jh, 7/8/94.  Modified the argument and return types of the following function
 * as part of the project to ensure that foreign functions get the correct
 * argument and return types.  For further details, see my note this date in
 * /bt/ab/rtl/c/gensym.h.
 */

long load_built_in_outline_font(built_in_font_id_long)
     long built_in_font_id_long;
{
 int built_in_font_id = (int) built_in_font_id_long;
 {
  GDECL

  ALLOCATE_SP_GLOBALS_IF_NECESSARY

  switch(built_in_font_id)
    {
#ifdef FONT3004_ID
    case FONT3004_ID:
      if (set_up_font_in_memory(PARAMS2 font3004_array, font3004_size, protoBCID, procSpeedo)
	  == FALSE)
	return(-1);
      break;
#endif
#ifdef FONT3008_ID
    case FONT3008_ID:
      if (set_up_font_in_memory(PARAMS2 font3008_array, font3008_size, protoBCID, procSpeedo)
	  == FALSE)
	return(-1);
      break;
#endif
#ifdef SLAVIC_ID
    case SLAVIC_ID:
      if (set_up_font_in_memory(PARAMS2 slavic_array, slavic_size, protoDirectIndex, procTrueType)
	  == FALSE)
	return(-1);
      break;
#endif
    default:
      return(-1);		/* returns negative to indicate failure */
    }

  /* At present, we "initialize" by simply by setting current_fontrip_output_mode
   to UNINITIALIZED_FONTRIP_OUTPUT_MODE, which will later be interpreted by
   do_setup_for_make_char to mean that specs need to be set appropriately. The
   same thing is also done in set_current_font_memory, and load_outline_font.
   */  
  current_fontrip_output_mode == UNINITIALIZED_FONTRIP_OUTPUT_MODE;

  return(current_font_memory_index); /* non-negative */
 }
}



int run_built_in_demo(font_name, h, v, fractional_h, fractional_v, char_to_do)
     char *font_name;
     int h, v, fractional_h, fractional_v;
     ufix16 char_to_do;
{
  GDECL
    int i;
  fix31 horizontal_lpm, vertical_lpm;
  long built_in_font_id_long;

#ifdef FONT3004_ID
  if (!strcmp(font_name, "SWISS721-SWA") || !strcmp(font_name, "ALL")) {
      built_in_font_id_long = (long)FONT3004_ID;
      load_built_in_outline_font(built_in_font_id_long);
  }
#endif
#ifdef FONT3008_ID
  if (!strcmp(font_name, "COURIER-SWA") || !strcmp(font_name, "ALL")) {
    built_in_font_id_long = (long)FONT3008_ID;
    load_built_in_outline_font(built_in_font_id_long);
  }
#endif  
#ifdef SLAVIC_ID
  if (!strcmp(font_name, "SLAVIC") || !strcmp(font_name, "ALL")) {
      built_in_font_id_long = (long)SLAVIC_ID;
      load_built_in_outline_font(built_in_font_id_long);
  }
#endif
  
  horizontal_lpm = (fix31)text_x_to_text_width((long)h, (long)fractional_h);
  vertical_lpm = (fix31)text_x_to_text_width((long)v, (long)fractional_v);
  for (i = 0; i < next_unassigned_font_memory_index; i++) {
    /* output all of the characters in the encoding array if char_to_do is
       zero; otherwise, just do char_to_do */	
    for (char_index = 0; char_index < no_font_chars; char_index++) {
      if ((char_to_do == 0) || (char_to_do == char_index))
	fontrip_make_char
	  (char_index, (fix15)i, horizontal_lpm, vertical_lpm, 0);
    }
  }
}


/*
 * sp_report_error is called by the character generator to report an error.
 *
 *  Since character data not available is one of those errors
 *  that happens many times, don't report it to user
 */

#define REPORT(tag, string) case tag: \
          fprintf (stderr, "\nError #%d: ", tag); \
          fprintf (stderr, (string)); break

void sp_report_error(PARAMS2 n)
          GDECL
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
      
    case 12:
#if DEBUG
      /* debugging?  This comes up far too often to be useable, since we got swiss-swa!
	 Bitstream recommends this be ignored, too.  -- mhd, 6/1/93
	 */
      fprintf(stderr, "\nUnknown error case (12) [Report character data not avail %c/%d]\n",
	      char_index, character);
      /* mhd added stuff at end in []'s */
#endif
      break;
      
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

void sp_open_bitmap(PARAMS2 x_set_width, y_set_width, xorg, yorg, xsize, ysize)
     GDECL
     fix31 x_set_width;		/* x component of the escapement vector (1/65536 pixels) */
     fix31 y_set_width;		/* y component of the escapement vector (1/65536 pixels) */
     fix31 xorg;		/* Coordinate at left edge of the bitmap (1/65536 pixels) */
     fix31 yorg;		/* Coordinate at top edge of the bitmap (1/65536 pixels) */
     fix15 xsize;		/* Width of the bitmap (whole pixels) */
     fix15 ysize;		/* Height of the bitmap (whole pixels) */
{
  width_of_current_raster = xsize;
  height_of_current_raster = ysize;
  horizontal_textx_offset_of_current_raster
    = (fix15)(xorg >> 8);	/* UNABSTACTED KNOWLEDGE OF TEXT X REPRESENTATION HERE! */
  horizontal_offset_of_current_raster
    = (fix15)(xorg >> 16);
  vertical_offset_of_current_raster
    = (fix15)(yorg >> 16);
  x_set_width_of_current_raster
    = x_set_width;
  /* WHY DO THIS -- ARE THERE BUGS? IS SLOP PART OF THE SPEC?! */
  /*
  if (width_of_current_raster > MAX_BITS)
    width_of_current_raster = MAX_BITS;
    */
  x_in_current_raster = 0;
  y_in_current_raster = 0;
  
  switch (current_fontrip_output_mode)
    {

    case BBOX_GETTING_MODE:
      return;

    case FONT_CHAR_RASTER_OUTPUT:
      break;


    case DEMO_OUTPUT_MODE:

      printf("\nlines-per-em: h=%d|%d; v=%d|%d",
	     horizontal_lines_per_em, fractional_horizontal_lines_per_em,
	     vertical_lines_per_em, fractional_vertical_lines_per_em);
      printf("\nraster width X height: %d X %d",
	     width_of_current_raster, height_of_current_raster);
      printf("\nxorg: %d; yorg: %d (shifted: %d, %d)",
	     xorg, yorg,
	     horizontal_offset_of_current_raster,
	     vertical_offset_of_current_raster);
      printf("\nraster width X height: %d X %d",
	     width_of_current_raster, height_of_current_raster);
	     
      printf("\nCharacter index = %d", char_index);  
      if (map_index_to_proc_type_protocol(current_font_memory_index) == procType1)
	printf(", Name = %s", character);
      printf("\n");
      printf("set width = %d (%3.1f)\n",
	     fi_get_char_width(PARAMS2 character),
	     (real)fi_get_char_width(PARAMS2 character) / 65536.0);	     
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
      break;
    }
}





    
     

void sp_set_bitmap_bits (PARAMS2 y, xbit1, xbit2)
     GDECL
     fix15     y;     /* Scan line (0 = first row above baseline) */
     fix15     xbit1; /* Pixel boundary where run starts */
     fix15     xbit2; /* Pixel boundary where run ends */
{ 
  /* clip to limits */
  /* This apparent bug is unfortunately a fact of life at certain
     rare scales, i.e., ones where things can't look good anyway.
     Since it will take time to fix, can probably best be done by
     Bitstream, and is of questionable value, we don't inflict this
     message on our users. I believe switching to the 2D writer,
     which was done recently, somewhat exacerbated this problem.
     -mhd, 7/26/95
     */
  if (current_fontrip_output_mode == DEMO_OUTPUT_MODE) {
    if (xbit2 > width_of_current_raster)
      printf("\n!!FONTRIP BUG: xbit2 = %d; width of raster is %d!!",
	     xbit2, width_of_current_raster);
  }


  /* WHY DO THIS -- ARE THERE BUGS? IS SLOP PART OF THE SPEC?! -mhd, 5/93 */
  /*
  if (xbit1 < 0) xbit1 = 0;
  if (xbit2 < 0) xbit2 = 0;
  if (xbit1 > MAX_BITS) xbit1 = MAX_BITS;
  if (xbit2 > MAX_BITS) xbit2 = MAX_BITS;
  if (xbit1 > width_of_current_raster) xbit1 = width_of_current_raster;
  if (xbit2 > width_of_current_raster) xbit2 = width_of_current_raster;
  */

  
  switch (current_fontrip_output_mode)
    {
    case BBOX_GETTING_MODE:
      return;
    case FONT_CHAR_RASTER_OUTPUT:
#ifndef NO_GENSYM_WINDOWS
      /* Draw the actual bits.  Handle the case of a one-long (trivial) line */
      /* by calling the p_draw_point routine.  Otherwise, call the general */
      /* line drawing routine.  This is the only direct interface to the */
      /* xwindows module in this file, and in the whole fontrip library. */
      if (xbit1 == (xbit2 - 1))
	p_draw_point(pixmap_for_current_character, xbit1, y, 1);
      else
	p_draw_line(pixmap_for_current_character, xbit1, y, xbit2-1, y, 1);
#endif /* ifdef CHESTNUT */
      break;
    default:
      /* Output backlog of off bits, if any */
#if 0 /* DEBUG */
	printf("set_bitmap_bits(%d, %d, %d)\n", (int)y, (int)xbit1, (int)xbit2);
#endif
      while (y_in_current_raster < y)
	{
	  while (x_in_current_raster < width_of_current_raster)
	    {
	      switch (current_fontrip_output_mode)
		{
		case DEMO_OUTPUT_MODE:
		  printf(". ");
		  break;
		}

	      x_in_current_raster++;

	      switch (current_fontrip_output_mode)
		{
		case DEMO_OUTPUT_MODE:
		  break;
		}
	    }

	  x_in_current_raster = 0;
	  y_in_current_raster++;

	  switch (current_fontrip_output_mode)
	    {
	    case DEMO_OUTPUT_MODE:
	      printf("\n   ");
	      break;
	    }
	}
  
      /* Add bits to current line */
      while (x_in_current_raster < xbit2)
	{
	  if (x_in_current_raster < xbit1)
	    {
	      switch (current_fontrip_output_mode)
		{
		case DEMO_OUTPUT_MODE:
		  printf(". ");
		  break;
		}
	    }
	  else
	    {
	      switch (current_fontrip_output_mode)
		{
		case DEMO_OUTPUT_MODE:
		  printf("X ");
		  break;
		}
	    }
	  x_in_current_raster++;
	  switch (current_fontrip_output_mode)
	    {
	    case DEMO_OUTPUT_MODE:
	      break;
	    }
	}  
      return;
    }
}


/* 
 * sp_close_bitmap is called by the character generator to indicate all
 * bitmap data that has been generated.
 */
void sp_close_bitmap (PARAMS1)
     GDECL
{
  fix15 no_chunks_needed, total_no_chunks_needed, no_chunks_out;
  switch (current_fontrip_output_mode)
    {
    case BBOX_GETTING_MODE:
      return;
    case DEMO_OUTPUT_MODE:
      printf("\n");
      break;
    }
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





/* tt_get_font_fragment is the client-defined function called by the truetype
   rasterizer ("server").  Its job is to return a pointer to memory containing
   the TrueType font data.  This is called from tt_load_font after the font data
   has been stored in the font_memory_array by set_up_font_in_memory.
   

   clientID will be the index in font_memory_array at which the particular font
   data is stored.

   offset is the number of bytes into the data to read.

   length is the number of bytes past offset the stops.

   In our scheme, the entire font is loaded into memory, and that memory is
   never reclaimed. That's why this is so simple.  It simply returns the pointer
   to the font memory offset by offset.  Note that we can just ignore length,
   since its only use is to tell you how much memory to allocate if you're
   allocating memory, and we're not allocating any.

   */

GetSFNTFunc  tt_get_font_fragment (clientID, offset, length)
     fix31  clientID, offset, length;
{
  ufix8 *ptr;
  
  ptr = (ufix8 *)map_index_to_font_memory(clientID);
  return ((GetSFNTFunc)(ptr+offset));
}



/* tt_release_font_fragment is the client-defined function called by the
truetype rasterizer after a fragment of font memory is no longer needed.  This
doesn't do anything because we load all of the font into memory, not segment by
segment, and never reclaim any of it.  */

void tt_release_font_fragment (ptr)
     ufix8 *ptr;
{
  return;
}







/*
 * Called by Speedo character generator to request that character data be loaded
 * from the font file into a character data buffer.  The character buffer offset
 * is zero for all characters except elements of compound characters. If a
 * single buffer is allocated for character data, cb_offset ensures that
 * sub-character data is loaded after the top-level compound character.  Returns
 * a pointer to a buffer descriptor.
 *
 * For the purposes of fontrip, this is just defined as a dummy function. */

buff_t * sp_load_char_data(PARAMS2 file_offset, no_bytes, cb_offset)
     GDECL
     fix31    file_offset;  /* Offset in bytes from the start of the font file */
     fix15    no_bytes;     /* Number of bytes to be loaded */
     fix15    cb_offset;    /* Offset in bytes from start of char buffer */
{
  /* DUMMY FUNCTION */
  buff_t *it;
  return(it);
}



/* get_byte is a dummy function we don't use.  It's not easily flushable because
   it has callers defined in other (core) modules. */

static FILE *font_fp = NULL;

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




/* Stubs for outline output modules follow.  These are needed to work around the
   bug in the 2d writer -- it produces bogus output when we compile with
   INCL_OUTLINE = 0; so we now compile with INCL_OUTLINE = 1, and this means we
   are required to stub out these functions.

   NOTE: We will probably ultimately use the outline output functions anyway: in
   order to generate outlines in our printed output, rather than bitmaps.

   --mhd, 7/28/93 */



void sp_line_to(PARAMS2 x, y)
     GDECL
     fix31 x; fix31 y;
{
}

void sp_close_contour(PARAMS1)
     GDECL
{
}

void sp_curve_to(PARAMS2 x1, y1, x2, y2, x3, y3)
     GDECL
     fix31 x1;
     fix31 y1;
     fix31 x2;
     fix31 y2;
     fix31 x3;
     fix31 y3;
{
}

void sp_open_outline(PARAMS2 x_set_width, y_set_width, xmin, xmax, ymin, ymax)
     GDECL
     fix31 x_set_width;
     fix31 y_set_width;
     fix31  xmin;
     fix31  xmax;
     fix31  ymin;
     fix31  ymax;
{
}

void sp_close_outline(PARAMS1)
     GDECL
{
}

void sp_start_contour(PARAMS2 x, y, outside)
     GDECL
     fix31    x;
     fix31    y;
     boolean outside;
{
}

void sp_start_new_char(PARAMS1)
     GDECL
{
}




