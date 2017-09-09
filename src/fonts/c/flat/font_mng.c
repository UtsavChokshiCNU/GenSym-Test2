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

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "speedo.h"                 /* General definition for make_bmap */
#include "ufe.h"							/* Unified front end */
#include "keys.h"                  /* Font decryption keys */

#define DEBUG  0

#if DEBUG
#define SHOW(X) printf("X = %d\n", X)
#else
#define SHOW(X)
#endif

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
static  FILE  *fdescr;             		/* Speedo outline file descriptor */
static  ufix16 minchrsz;           		/* minimum character buffer size */
static  ufix8 FONTFAR *font_buffer;    /* Pointer to allocated Font buffer */
static  buff_t font;               		/* Buffer descriptor for font data */
static  specs_t gspecs;               	/* Bundle of character generation specs  */

#if INCL_LCD
static  ufix8 FONTFAR *char_buffer;       /* Pointer to allocate Character buffer */
static  buff_t char_data;     		     	/* Buffer descriptor for character data */
#endif

#define MAPPING_ENTRIES 64

static	char  *kanji_font_mapping[MAPPING_ENTRIES] ;   	/* shift-JIS font mapping table */
static	ufix8	last_font_id = 255 ;						   	/* current loaded font id, 255 is none */

/* Kanji font manager */

FUNCTION int kj_set_font_mapping(index,font_name)
ufix8 index;
char* font_name;
/*
 * allocate memery to set font mapping table entry at index
 * to be the font_name
 */
{
	ufix8 	font_id ;

	/* calculate shift-JIS font_id: 0 - 63 */
	/* font_id > 42 is Gaiji or undefined	*/
	if ( index == 0 )
		font_id = 0 ;
	else if ( index > 0x80 && index < 0xA0 )
		font_id = index - 0x80 ;
	else if ( index >= 0xE0 && index < 0xFC )
		font_id = index - 0xC0 ;
	else 
   {
   	printf("****** Invalid font id number\n");
		return(1);
   }
	/* font_id is JIS ward / 2 */
	if (kanji_font_mapping[font_id])
		free(kanji_font_mapping[font_id]);
	if (( kanji_font_mapping[font_id] = (char*)malloc (strlen(font_name)+1)) == NULL )
   {
   	printf("****** Cannot allocate memory for font mapping table\n");
		return(1);
   }
	sprintf(kanji_font_mapping[font_id],font_name);
	return(0);
}

FUNCTION ufix8 kj_convert_hexstring(string)
char *string;
/*
 * Convert ASCII hexstring in font mapping file 
 * to hexdigit
 */
{
	ufix8 value = 0 ;
	int i ;

	for ( i = 0 ; i < 2 ; i++ )
	{
	   value = value << 4 ;
		if ( string[i]	>= '0' && string[i] <= '9' )
			value += string[i] - 0x30 ;
		else if ( string[i]	>= 'A' && string[i] <= 'F' )
			value += string[i] - 0x37 ;
		else if ( string[i]	>= 'a' && string[i] <= 'f' )
			value += string[i] - 0x57 ;
	}
	return value ;
}

FUNCTION int kj_read_font_mapping(filename)
char *filename;
/*
 * Read font mapping file and set up a font mapping table.
 *	It also initializes the 4-in-1 processor 
 */
{
	ufix8 index ;
	char font_name[32];
   char font_index[32] ;
	FILE *map_file ;
	int i = 0 ;

	for ( i=0 ; i < MAPPING_ENTRIES ; i++ )
		kanji_font_mapping[i] = NULL ;

	map_file= fopen(filename,"r");
	if (map_file == NULL)
   {
   	printf("****** Cannot open mapping file %s\n", filename);
	   return(1);                  
   }

	while ( fscanf(map_file,"%s %s",font_index,font_name) != EOF )
	{
		if ( strlen(font_index) > 2 )
		{
	   	printf("****** It is not a font mapping file %s\n", filename);
			return(1);
		}
		index = kj_convert_hexstring(font_index);
		if (kj_set_font_mapping(index,font_name))
			return(1);
	}
#if DEBUG
	printf("\n end font mapping");
	for ( i=0 ; i < MAPPING_ENTRIES ; i++ )
		if ( kanji_font_mapping[i] != NULL)
			printf("\n %X map font: %s",i,kanji_font_mapping[i]);
   getchar();
#endif 
	fclose(map_file);
	return(0);
}

FUNCTION int kj_SJ_font_manager (sj_lead_byte, font_name, count)
     ufix8 sj_lead_byte; char *font_name; int *count;
/*
 * Speedo Kanji font decoder and font loader
 * sj_lead_byte (input) : shift-JIS lead byte to be decoded
 * font_name	 (output) : a string pointer returns the decoded font name
 *	count			 (output) : an integer pointer returns shift-JIS code
 *									is a one byte or two bytes SJ character code
 */
{
	ufix8		font_id ;
	int i ;
	ufix16	bytes_read;           /* Number of bytes read from font file */
	ufix32	minbufsz;             /* minimum font buffer size to allocate */
	ufix8		FONTFAR *byte_ptr;
	ufix8    temp[16];             /* temp buffer for first 16 bytes of font */
	ufe_struct tspecs;

	*count=2;
	/* decode font id */
	if ( sj_lead_byte > 0x80 && sj_lead_byte < 0xA0 )
		font_id = sj_lead_byte - 0x80 ;
	else if ( sj_lead_byte >= 0xE0 && sj_lead_byte < 0xFC )
		font_id = sj_lead_byte - 0xC0 ;
	else 
	{
		font_id = 0 ;
		*count=1;
	}
	/* check if font has been loaded */
	if ( font_id == last_font_id )
		return(0);

	/* get font name from mapping table */
	font_name = kanji_font_mapping[font_id];
   
	if ( font_name == NULL )
		return(1);
		
	if (last_font_id != 255 )
	{
		fclose(fdescr);
		free(font_buffer);
#if INCL_LCD
		free(char_buffer);
#endif 
	}

	last_font_id = font_id ;

	/* open font file */
	fdescr = fopen (font_name, "rb");
	if (fdescr == NULL)
   {
		last_font_id = 255 ;  /* file open fail */
   	printf("****** Cannot open file %s\n", font_name);
	   return(1);                  
   }

	/* get minimum font buffer size - read first 16 bytes to get the minimum
   size field from the header, then allocate buffer dynamically  */
	bytes_read = fread(temp, sizeof(ufix8), 16, fdescr);
	if (bytes_read != 16)
	{
		printf("****** Error on reading %s: %x\n", font_name, bytes_read);
		fclose(fdescr);
		return(1);                  
	}
#if INCL_LCD
	minbufsz = (ufix32)read_4b(temp+FH_FBFSZ);
#else
	minbufsz = (ufix32)read_4b(temp+FH_FNTSZ);
	if (minbufsz >= 0x10000)
	{
		printf("****** Cannot process fonts greater than 64K - use dynamic character loading configuration option\n");
		fclose(fdescr);
		return(1);                  
	}
#endif

	if (strcmp("FONTFAR","far") == 0)
	  font_buffer = (ufix8 FONTFAR *)_fmalloc((ufix16)minbufsz);
	else
	  font_buffer = (ufix8 *)malloc((ufix16)minbufsz);
      
	if (font_buffer == NULL)
	{
		printf("****** Unable to allocate memory for font buffer\n");
	   fclose(fdescr);
		return(1);                  
	}

#if DEBUG
	printf("Loading font file %s\n", font_name);
#endif

	fseek(fdescr, (ufix32)0, 0);
	if (strcmp("FONTFAR","far") ==0)
	{
   	byte_ptr = (ufix8*)font_buffer;
	   for (i=0; i < minbufsz; i++)
		{
      	 int ch;
	       ch = getc(fdescr);
   	    if (ch == EOF)
          {		printf ("Premature EOF in reading font buffer, %ld bytes read\n",i);
           		exit(2);
			 }
	       *byte_ptr=(ufix8)ch;
   	    byte_ptr++;
      }
	   bytes_read = i;
   }
	else
   {
   	bytes_read = fread((ufix8 *)font_buffer, sizeof(ufix8), (ufix16)minbufsz, fdescr);
	   if (bytes_read == 0)
   	{
	   	printf("****** Error on reading %s: %x\n", font_name, bytes_read);
   		fclose(fdescr);     
			return(1);                  
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
		printf("****** Unable to allocate memory for character buffer\n");
   	fclose(fdescr);     
	   return(1);
	}
#endif

	/* DO ENCRYPTION HERE */

	font.org = font_buffer;
	font.no_bytes = bytes_read;

	/* Set specifications for character to be generated */
	gspecs.pfont = &font;          /* Pointer to Speedo outline structure */
	gspecs.out_info = NULL;   
	tspecs.Gen_specs = &gspecs;

	if (!fi_set_specs(&tspecs))
  	{
  		fprintf(stderr,"Unable to set requested specs.\n");
	   return (FALSE);
  	}
	return 0 ;
}

FUNCTION int kj_SJ2_font_manager(code,font_name,count)
     ufix16 code; char *font_name; int *count;
/*
 * Speedo Kanji font decoder and font loader
 * code      (input)  : 2 bytes shift-JIS code which is converted from JIS or EUC
 * font_name (output) : a string pointer returns the decoded font name
 *	count		 (output) : an integer pointer returns shift-JIS code
 *									is a one byte or two bytes SJ character code
 */
{
	ufix8 sj_lead_byte = (ufix8) (code >> 8) ;
	return(kj_SJ_font_manager(sj_lead_byte,font_name, count));
}

FUNCTION int kj_set_kanji_specs(flags,matrix)
     ufix16 flags; real *matrix;
/*
 *  pass specs parameters to Kanji font manager as a local copy.
 *  Note: Kanji font manager need to call fi_set_specs every time
 *  when it opens an new base font.  
 */
{
	ufe_struct tspecs;
	
   gspecs.xxmult= (fix31) matrix[0] ;
   gspecs.xymult= (fix31) matrix[1] ;
   gspecs.yxmult= (fix31) matrix[2] ;
   gspecs.yymult= (fix31) matrix[3] ;
   gspecs.xoffset = (fix31) matrix[4] ;
   gspecs.yoffset = (fix31) matrix[5] ;
	gspecs.flags = flags ;

	gspecs.out_info = 0;           /* output module information  */

	tspecs.Gen_specs = &gspecs;
	/* set specs if font has been loaded */
	if ( gspecs.pfont != NULL )
	{
		if (!fi_set_specs(&tspecs))
   	{
   		fprintf(stderr,"Unable to set requested specs.\n");
		   return (FALSE);
   	}
	}
	return(0);
}

#if INCL_LCD
#if REENTRANT_ALLOC
FUNCTION buff_t *sp_load_char_data(sp_global_ptr, file_offset, no_bytes, cb_offset)
SPEEDO_GLOBALS *sp_global_ptr;
#else
FUNCTION buff_t *sp_load_char_data(file_offset, no_bytes, cb_offset)
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

	if (strcmp("FONTFAR","far") ==0)
	{
   	byte_ptr = (ufix8*) char_buffer+cb_offset;
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
