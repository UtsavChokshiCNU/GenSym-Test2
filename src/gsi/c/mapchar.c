/***************************************************************************
:
:  mapchar.c -- Read and write various encodings of text files.
:  based on: rpc-from-g2.c  --  test rpc call from G2 to GSI
: 
:  The executable "mapchar" together with the sample knowledge base
:  "mapchar.kb", provides a demonstration of how a GSI application can
:  read and write from a standard international character set (such as
:  Korean KSC5601) and display the international characters in
:  G2. This file contains code to translate between the Gensym
:  character set (which can encode various characters such as 
:  Japanese kanji and Korean) and international character sets.  
:
:  This file contains code translating between Gensym codes and:
: 	Korean: KSC5601-EUC 
: 	Japanese: JISX0208-EUC
: 	Japanese: JISX0208-Shift-JIS
: 	Latin-1: ISO-8859-1 
: 	Latin-Cyrillic: ISO-8859-5 
: 
:  See the G2 Reference Manual, appendix D, for more information
:  about the Gensym character set and descriptions of translation
:  algorithms used in this file. 
: 
:  This file conforms to the Gensym Character Set for G2 4.0.
:    To make this file compile under 4.0, replace all occurences of 
:    gsi_char to octet. 
:
:  Created February 1997, Gensym Corporation
:
:..........................................................................*/

#include <stdio.h>
#include "gsi_main.h"

	
#define TCPIP_PORT_NUMBER  0


#ifndef NUL
#define NUL '\0'
#endif

#ifndef CR
#define CR '\15'
#endif

#ifndef LF
#define LF '\12'
#endif

#define  octet   unsigned char

/*
 * GENSYM_REPLACEMENT_CHAR can be changed to any single byte
 * character. This is used in place of Gensym characters that are
 * malformed or that have no encoding in the encoding we're
 * translating a Gensym character into. 
 */
#define GENSYM_REPLACEMENT_CHAR '?'

/*
 * MAX_OCTETS_PER_GENSYM_CHAR is the theoretical maximum number of octets
 * that may be needed to encode a Gensym character.  This is 4, and may
 * never be changed.
 */
#define MAX_OCTETS_PER_GENSYM_CHAR 4

/*
 * RETURN_BUF_SZ gives the size of the constant buffer used for returning
 * externally encoded text as Gensym=encoded text.  This is currently a
 * 64K buffer (65536 bytes), of which one byte is needed for the NUL
 * termination character, and at a minimum 1/4 as many Gensym characters
 * may be encoded.  Thus, this is guaranteed to permit at least
 * 
 *   (65536 - 1) / 4 = 16383
 *
 * characters, but typically many more.  Note that G2/GSI/ICP have
 * as 64K as their maximum string size.  So this should generally not be
 * increased. 
 */
#define RETURN_BUF_SZ 65536

/*
 * The octet array return_file_content_buffer is RETURN_BUF_SZ
 * elements long and holds null-terminated character data to be sent
 * back to via the read_file rpc function (below) as a Gensym-encoded
 * string.  This cannot be shared, saved away, or used concurrently
 * by more than one execution thread at a time, or used in reentrant
 * code.  This is a static data structure private to read_file.
 */
octet return_file_content_buffer[RETURN_BUF_SZ];


/* 
 * prototypes needed to avoid warnings on NT
 */
extern declare_gsi_rpc_local_fn(write_file);
extern declare_gsi_rpc_local_fn(read_file);


/*
 * read_gensym_code_beyond_escape returns 0 if a NUL is encountered
 * (end of data in the middle of a Gensym \ escape sequence, i.e., a
 * malformed Gensym character); otherwise, it returns the code at
 * index_ptr, and increments index_ptr by 2 or 3; see documentation
 * on the Gensym character set, characters following \, for why this
 * works as it does.  
 */
int read_gensym_code_beyond_escape (string, index_ptr)
  octet *string;
  int   *index_ptr;
{
  octet c1, c2, c3;
  int code, offset;

  offset = (- ((32 << 13) + (95 * 40) + 32));

  c1 = string[(*index_ptr)++];
  if (c1 == NUL) return(0);
  c2 = string[(*index_ptr)++];
  if (c2 == NUL) return(0);
  if (c1 < 40) {
    c3 = string[(*index_ptr)++];
    if (c3 == NUL) return(0);
    code = ((c1 << 13) + (c2 * 95) + c3 + offset);
  } else {
    code = ((c1 * 95) + c2 + (33 << 13) + offset);
  }
  return(code);
}


void write_gensym_code_into_buffer (code, octet_buffer, index_ptr)
  int    code;
  octet *octet_buffer;
  int   *index_ptr;
{
  int q, r, n, d, c1bits;
  octet c1, c2, c3;

  n = (code & ((1 << 13) - 1));
  d = 95;
  q = (n/d);
  r = (n%d);

  c1bits = (code >> 13);

  c1 = (octet)(c1bits + 32);
  c2 = (octet)(q + 40);
  c3 = (octet)(r + 32);
  
  octet_buffer[(*index_ptr)++] = '\\';
  if (c1bits != 1)
    octet_buffer[(*index_ptr)++] = c1;
  octet_buffer[(*index_ptr)++] = c2;
  octet_buffer[(*index_ptr)++] = c3;
}


/***************************************************************************
:
:  Korean KSC5601-EUC Encoding Specifics
:
:..........................................................................*/

/* 
 * KSC_low_byte_offset is the amount that gets added to the low
 * (7-bit) byte of a KSC5601 16-bit (two-byte) character code to
 * derive the corresponding Gensym character code.  This is 94, and
 * may never be changed.  
 */
#define KSC_low_byte_offset 94

/* 
 * write_gensym_code_as_ksc_euc encodes gensym_code in the Korean
 * KSC5601 character set using EUC encoding.  If gensym_code is a Korean
 * KSC5601 character, it is output as two bytes in EUC (Extended Unix Code)
 * format.  This means, that the 7-bit lead byte and 7-bit trail byte of the
 * 16-bit code have the eighth bit set.  If gensym_code happens to represent
 * an ASCII character (in the range 32-126) or control character (in the
 * range (0-31 or 127), this also outputs that character.  Otherwise,
 * gensym_code is either a from a different character set (e.g., Cyrillic
 * or Japanese), has an unknown mapping, or is an illegal code; in all
 * such cases, the octet that is the value of GENSYM_REPLACEMENT_CHAR
 * is written.
 */
void write_gensym_code_as_ksc_euc (output_file, gensym_code)
  FILE *output_file;
  int   gensym_code;
{
  int high_byte, low_byte;

  high_byte = (gensym_code >> 8);
  low_byte = (gensym_code & 0xff);

  if (((0x21 <= high_byte) && (high_byte <= 0x7e))    /* Japanese or Korean */ 
      && !((0x21 <= low_byte) && (low_byte <= 0x7e))) /* and Not Japanese */
  {
      putc((128 | high_byte), output_file);
      putc((128 | (low_byte - KSC_low_byte_offset)), output_file);
  } else {
    if (gensym_code < 128)
      /* May be used for ASCII or control characters, especially may
	 be put to use in 5.0 for the Tab character (0x9) */
      putc(gensym_code, output_file);
    else {
      /* Non-control/ASCII/KSC character (Japanese, Cyrillic, or Unknown)*/
      printf("\nUnknown Gensym character code: %d. Using replacement %c \n",
	     gensym_code, GENSYM_REPLACEMENT_CHAR);
      putc(GENSYM_REPLACEMENT_CHAR, output_file);
    }
  }
}

void write_gensym_string_as_ksc_euc (output_file, gensym_string)
  FILE  *output_file;
  octet *gensym_string;
{
  octet character, escape;
  int i = 0, gensym_code;
  while (1) {
    character = gensym_string[i++];
    if (character == NUL) return;
    switch (character) {
    case '@': case '~':
      escape = character;
      character = gensym_string[i++];
      if (character == NUL) {
	/* end of data with malformed Gensym character sequence */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
	return;
      } else if ((escape == '@')
		 && ((character == 'L') || (character == 'P'))) {
	/* line or paragraph break */
	putc ('\n', output_file);
      } else if ((escape == '~')
		 && ((character == '@')
		     || (character == '~')
		     || (character == '\\'))) {
	putc (character, output_file);
      } else {
	/* Unhandled (e.g., extended Latin), unknown, and/or illegal
	   Gensym character sequence are all covered by this case. */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
      }
      break;
    case '\\':
      gensym_code = read_gensym_code_beyond_escape (gensym_string, &i);
      if (gensym_code == 0) 
	return; /* illegal gensym character sequence case */
      write_gensym_code_as_ksc_euc (output_file, gensym_code);
      break;
    default:
      putc (character, output_file);
      break;
    }
  }
}

void read_ksc_euc_as_gensym_string(input_file, octet_buffer)
  FILE  *input_file;
  octet *octet_buffer;
{
  octet lead, trail,
    previous_lead = 'x'; /* x arbitrary, but not CR or LF */
  int getc_result;
  int code;
  int i;

  i = 0;
  
  while (1){
    getc_result = getc(input_file);
    if (getc_result == EOF) break;
    lead = (octet)getc_result;
    if (lead >= 0xA0) {
      getc_result = getc(input_file);
      if (getc_result == EOF) {
	printf("Invalid encoding: EOF after first byte");
	printf("of a double-byte sequence! \n" );
	break;
      }
      trail = (octet)getc_result;
      code = (((lead & 0x7F) << 8) + ((trail & 0x7F) + KSC_low_byte_offset));
      write_gensym_code_into_buffer (code, octet_buffer, &i);
    } else {
      switch (lead) {
      case LF: case CR:
	if ((lead == CR) || !(previous_lead == CR)) {
	  octet_buffer[i++] = '@';
	  octet_buffer[i++] = 'L';
	}
	break;
      case '@': case '\\': case '~':
	octet_buffer[i++] = '~';
	octet_buffer[i++] = lead;
	break;
      default:
	if ((lead < 32) || (lead >= 0x7F))
	  /* any control characters: */
	  write_gensym_code_into_buffer (code, octet_buffer, &i);
	else
	  /* normal, ASCII characters: */
	  octet_buffer[i++] = lead;
      } /* end switch */
    } /* end else */
    previous_lead = lead;
    if (i >= ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1)) {
      printf ("Buffer overflow; cannot handle more than ");
      printf ("%d octets; returning incomplete data \n",
	      ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1));
      break;
    }
  }
  octet_buffer[i] = NUL;
}


/***************************************************************************
:
:  Japanese JISX0208-EUC Encoding Specifics
:
:..........................................................................*/

/*
 * JIS_low_byte_offset is the amount that gets added to the low
 * (7-bit) byte of a JISX0208 16-bit (two-byte) character code to
 * derive the corresponding Gensym character code.  This is 0, and
 * may never be changed. 
 */
#define JIS_low_byte_offset 0

/*
 * write_gensym_code_as_jis_euc encodes gensym_code in the Japanese
 * JISX0208 character set using EUC encoding.  If gensym_code is a Japanese
 * JISX0208 character, it is output as two bytes in EUC (Extended Unix Code)
 * format.  This means, that the 7-bit lead byte and 7-bit trail byte of the
 * 16-bit code have the eighth bit set.  If gensym_code happens to represent
 * an ASCII character (in the range 32-126) or control character (in the
 * range (0-31 or 127), this also outputs that character.  Otherwise,
 * gensym_code is either a from a different character set (e.g., Cyrillic
 * or Japanese), has an unknown mapping, or is an illegal code; in all
 * such cases, the octet that is the value of GENSYM_REPLACEMENT_CHAR
 * is written.
 */
void write_gensym_code_as_jis_euc (output_file, gensym_code)
  FILE *output_file;
  int   gensym_code;
{
  int high_byte, low_byte;

  high_byte = (gensym_code >> 8);
  low_byte = (gensym_code & 0xff);

  if (((0x21 <= high_byte) && (high_byte <= 0x7e))    /* Japanese or Korean */
      && ((0x21 <= low_byte) && (low_byte <= 0x7e))) /* and is Japanese */
  {
    putc((128 | high_byte), output_file);
    putc((128 | (low_byte - JIS_low_byte_offset)), output_file);
  } else {
    if (gensym_code < 128)
      /* May be used for ASCII or control characters, especially may
	 be put to use in 5.0 for the Tab character (0x9) */
      putc(gensym_code, output_file);
    else {
      /*  Non-control/ASCII/JIS character (Japanese, Cyrillic, or Unknown) */
      printf("\nUnknown Gensym character code: %d. Using replacement %c \n",
	     gensym_code, GENSYM_REPLACEMENT_CHAR);
      putc(GENSYM_REPLACEMENT_CHAR, output_file);
    }
  }
}

void write_gensym_string_as_jis_euc (output_file, gensym_string)
  FILE  *output_file;
  octet *gensym_string;
{
  octet character, escape;
  int i = 0, gensym_code;
  while (1) {
    character = gensym_string[i++];
    if (character == NUL) return;
    switch (character) {
    case '@': case '~':
      escape = character;
      character = gensym_string[i++];
      if (character == NUL) {
	/* end of data with malformed Gensym character sequence */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
	return;
      } else if ((escape == '@')
	       && ((character == 'L') || (character == 'P'))) {
	/* line or paragraph break */
	putc ('\n', output_file);
      } else if ((escape == '~')
	       && ((character == '@')
		   || (character == '~')
		   || (character == '\\'))) {
	putc (character, output_file);
      } else {   
	/* Unhandled (e.g., extended Latin), unknown, and/or illegal
	   Gensym character sequence are all covered by this case. */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
      }
      break;
    case '\\':
      gensym_code = read_gensym_code_beyond_escape (gensym_string, &i);
      if (gensym_code == 0) 
	return; /* illegal gensym character sequence case */
      write_gensym_code_as_jis_euc (output_file, gensym_code);
      break;
    default:
      putc (character, output_file);
      break;
    }
  }
}

void read_jis_euc_as_gensym_string(input_file, octet_buffer)
  FILE  *input_file;
  octet *octet_buffer;
{
  octet lead, trail,
    previous_lead = 'x'; /* x arbitrary, but not CR or LF */
  int getc_result;
  int code;
  int i;

  i = 0;
  
  while (1) {
    getc_result = getc(input_file);
    if (getc_result == EOF) break;
    lead = (octet)getc_result;
    if (lead >= 0xA0) {
      getc_result = getc(input_file);
      if (getc_result == EOF) {
	printf("Invalid encoding: EOF after first byte");
	printf("of a double-byte sequence! \n" );
	break;
      }
      trail = (octet)getc_result;
      code = (((lead & 0x7F) << 8) + ((trail & 0x7F) + JIS_low_byte_offset));
      write_gensym_code_into_buffer (code, octet_buffer, &i);
    } else {
      switch (lead) {
      case LF: case CR:
	if ((lead == CR) || !(previous_lead == CR)) {
	  octet_buffer[i++] = '@';
	  octet_buffer[i++] = 'L';
	}
	break;
      case '@': case '\\': case '~':
	octet_buffer[i++] = '~';
	octet_buffer[i++] = lead;
	break;
      default:
	if ((lead < 32) || (lead >= 0x7F))
	  /* any control characters: */
	  write_gensym_code_into_buffer (code, octet_buffer, &i);
	else
	  /* normal, ASCII characters: */
	  octet_buffer[i++] = lead;
      }
    }
    previous_lead = lead;
    if (i >= ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1)) {
      printf ("Buffer overflow; cannot handle more than ");
      printf ("%d octets; returning incomplete data \n",
	      ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1));
      break;
    }
  }
  octet_buffer[i] = NUL;
}


/***************************************************************************
:
:  Japanese JISX0208-Shift-JIS Encoding Specifics
:
:..........................................................................*/

/* This encoding is rather similar to the JIS-EUC encoding, above. */


/* shiftjis_octet_to_jis_octet and jis_octet_to_shiftjis_octet based on 
** Ken Lunde's sample source code in his book 
** Understanding Japanese Information Processing.
*/

/* Note: "shiftjis" is used in this file rather than
** "shift_jis" to keep name lengths down below the 31
** character maximum for VMS.
*/

void shiftjis_octet_to_jis_octet (p1, p2)
  octet *p1;
  octet *p2;
{
  octet c1 = *p1;
  octet c2 = *p2;
  int adjust = c2 < 159;
  int rowOffset = c1 < 160 ? 112 : 176;
  int cellOffset = adjust ? (c2 > 127 ? 32 : 31) : 126;

  *p1 = ((c1 - rowOffset) << 1) - adjust;
  *p2 -= cellOffset;
}

void jis_octet_to_shiftjis_octet(p1, p2)
  octet *p1;
  octet *p2;
{
  octet c1 = *p1;
  octet c2 = *p2;
  int rowOffset = c1 < 95 ? 112 : 176;
  int cellOffset = c1 % 2 ? (c2 > 95 ? 32 : 31) : 126;

  *p1 = ((c1 + 1) >> 1) + rowOffset;
  *p2 += cellOffset;
}


/*
 * write_gensym_code_as_shiftjis encodes gensym_code in the Japanese
 * JISX0208 character set using Shift JIS encoding.  If gensym_code is a
 * Japanese JISX0208 character, it is output as two bytes in Shift JIS format.
 */
void write_gensym_code_as_shiftjis (output_file, gensym_code)
  FILE *output_file;
  int   gensym_code;
{
  octet high_byte, low_byte;

  high_byte = (gensym_code >> 8);
  low_byte = (gensym_code & 0xff);

  if (((0x21 <= high_byte) && (high_byte <= 0x7e))    /* Japanese or Korean */
      && ((0x21 <= low_byte) && (low_byte <= 0x7e))) /* and is Japanese */
  {
    low_byte = low_byte - JIS_low_byte_offset;
    jis_octet_to_shiftjis_octet (&high_byte, &low_byte);
    putc (high_byte, output_file);
    putc (low_byte, output_file);
  } else {
    if (gensym_code < 128)
      /* May be used for ASCII or control characters, especially may
	 be put to use in 5.0 for the Tab character (0x9) */
      putc(gensym_code, output_file);
    else {
      /*  Non-control/ASCII/JIS character (Japanese, Cyrillic, or Unknown) */
      printf("\nUnknown Gensym character code: %d. Using replacement %c \n",
	     gensym_code, GENSYM_REPLACEMENT_CHAR);
      putc(GENSYM_REPLACEMENT_CHAR, output_file);
    }
  }
}

void write_gensym_string_as_shiftjis (output_file, gensym_string)
  FILE  *output_file;
  octet *gensym_string;
{
  octet character, escape;
  int i = 0, gensym_code;
  while (1) {
    character = gensym_string[i++];
    if (character == NUL) return;
    switch (character) {
    case '@': case '~':
      escape = character;
      character = gensym_string[i++];
      if (character == NUL) {
	/* end of data with malformed Gensym character sequence */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
	return;
      } else if ((escape == '@')
	       && ((character == 'L') || (character == 'P'))) {
	/* line or paragraph break */
	putc ('\n', output_file);
      } else if ((escape == '~')
	       && ((character == '@')
		   || (character == '~')
		   || (character == '\\'))) {
	putc (character, output_file);
      } else {   
	/* Unhandled (e.g., extended Latin), unknown, and/or illegal
	   Gensym character sequence are all covered by this case. */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
      }
      break;
    case '\\':
      gensym_code = read_gensym_code_beyond_escape (gensym_string, &i);
      if (gensym_code == 0) 
	return; /* illegal gensym character sequence case */
      write_gensym_code_as_shiftjis (output_file, gensym_code);
      break;
    default:
      putc (character, output_file);
      break;
    }
  }
}

void read_shiftjis_as_gensym_string(input_file, octet_buffer)
  FILE  *input_file;
  octet *octet_buffer;
{
  octet lead, trail,
    previous_lead = 'x'; /* x arbitrary, but not CR or LF */
  int getc_result;
  int code;
  int i;

  i = 0;
  
  while (1) {
    getc_result = getc(input_file);
    if (getc_result == EOF) break;
    lead = (octet)getc_result;
    if (lead >= 0x80) {
      getc_result = getc(input_file);
      if (getc_result == EOF) {
	printf("Invalid encoding: EOF after first byte");
	printf("of a double-byte sequence! \n" );
	break;
      }
      trail = (octet)getc_result;
      shiftjis_octet_to_jis_octet (&lead, &trail);
      code = (((lead & 0x7F) << 8) + ((trail & 0x7F) + JIS_low_byte_offset));
      write_gensym_code_into_buffer (code, octet_buffer, &i);
    } else {
      switch (lead) {
      case LF: case CR:
	if ((lead == CR) || !(previous_lead == CR)) {
	  octet_buffer[i++] = '@';
	  octet_buffer[i++] = 'L';
	}
	break;
      case '@': case '\\': case '~':
	octet_buffer[i++] = '~';
	octet_buffer[i++] = lead;
	break;
      default:
	if ((lead < 32) || (lead >= 0x7F))
	  /* any control characters: */
	  write_gensym_code_into_buffer (code, octet_buffer, &i);
	else
	  /* normal, ASCII characters: */
	  octet_buffer[i++] = lead;
      }
    }
    previous_lead = lead;
    if (i >= ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1)) {
      printf ("Buffer overflow; cannot handle more than ");
      printf ("%d octets; returning incomplete data \n",
	      ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1));
      break;
    }
  }
  octet_buffer[i] = NUL;
}


/***************************************************************************
:
:  Latin-1 ISO-8859-1 Encoding Specifics  
:
:..........................................................................*/

/*
 * write_gensym_code_as_latin_1 encodes gensym_code in the Latin-1
 * character set.
 */
void write_gensym_code_as_latin_1 (output_file, gensym_code)
  FILE *output_file;
  int   gensym_code;
{
  if (gensym_code < 256)
    putc(gensym_code, output_file);
  else {
    printf("\nUnknown Gensym character code: %d. Using replacement %c \n",
	   gensym_code, GENSYM_REPLACEMENT_CHAR);
    putc(GENSYM_REPLACEMENT_CHAR, output_file);
  }
}

/* latin_1_tilde_map
 * Character translation.
 * This could all be in one long line, but line length on VAX is 
 * limited to approximately 200 characters, and long lines look bad
 * and are hard to print. Some compilers remove leading 
 * whitespace from continuation lines (see "C, A Reference Manual"), so 
 * no lines begin with leading whitespace here, which means some lines
 * are still over 80 characters. 
 */

octet *latin_1_tilde_map = (octet *)"                                 \
\241 \243\245\242          \353\313\357\317\343\303\365\325\373\333 \
\256\253 \273\277\100\304\301\307\302\311\312\310\314\315\316  \
\300\321\326\323\324\305 \330\334\332 \306\322\331 \134    \
\344\341\347\342\351\352\350\354\355\356  \340\361\366\363\364\345\
\337\370\374\372 \346\362\371 \251 \176                                                                                                                                 ";

void write_gensym_string_as_latin_1 (output_file, gensym_string)
  FILE  *output_file;
  octet *gensym_string;
{
  octet character, escape;
  int i = 0, gensym_code;
  while (1) {
    character = gensym_string[i++];
    if (character == NUL) return;
    switch (character) {
    case '@': case '~':
      escape = character;
      character = gensym_string[i++];
      if (character == NUL) {
	/* end of data with malformed Gensym character sequence */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
	return;
      } else if ((escape == '@')
	       && ((character == 'L') || (character == 'P'))) {
	/* line or paragraph break */
	putc ('\n', output_file);
      } else if (escape == '~') {
	putc (latin_1_tilde_map[character], output_file);
      } else {
	/* Unhandled (e.g., extended Latin), unknown, and/or illegal
	   Gensym character sequence are all covered by this case. */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
      }
      break;
    case '\\':
      gensym_code = read_gensym_code_beyond_escape (gensym_string, &i);
      if (gensym_code == 0) return; /*illegal gensym character sequence case */
      write_gensym_code_as_latin_1 (output_file, gensym_code);
      break;
    default:
      putc (character, output_file);
      break;
    }
  }
}

octet *latin_1_to_tilde_map = (octet *)"                                                                \
@                           \\                                 \
~                                  !%# $   | <  ;            >   \
?MBD5ARXCGEF1HIJ3 NYPQ7O TZV9U  smbd4arxcgef0hij2 nypq6o tzv8u   ";

void read_latin_1_as_gensym_string(input_file, octet_buffer)
  FILE  *input_file;
  octet *octet_buffer;
{
  octet character, tilde_mapping_maybe,
    previous_character = 'x'; /* x arbitrary, but not CR or LF */
  int getc_result;
  int i;

  i = 0;
  
  while (1) {
    getc_result = getc(input_file);
    if (getc_result == EOF) break;
    character = (octet)getc_result;
    switch (character) {
    case LF: case CR:
      if ((character == CR) || !(previous_character == CR)) {
	octet_buffer[i++] = '@';
	octet_buffer[i++] = 'L';
      }
      break;
    default:
      tilde_mapping_maybe = latin_1_to_tilde_map[character];
      if (tilde_mapping_maybe != ' ') {
	octet_buffer[i++] = '~';
	octet_buffer[i++] = tilde_mapping_maybe;
      } else if ((character < 32) || (character >= 0x7F))
	/* any other latin-1 or control characters, including TAB: */
	write_gensym_code_into_buffer (character, octet_buffer, &i);
      else
	/* normal, ASCII characters: */
	octet_buffer[i++] = character;
    }
    previous_character = character;
    if (i >= ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1)) {
      printf ("Buffer overflow; cannot handle more than ");
      printf ("%d octets; returning incomplete data \n",
	      ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1));
      break;
    }
  }
  octet_buffer[i] = NUL;
}


/***************************************************************************
:
: Latin-Cyrillic ISO-8859-5  Encoding Specifics
:
:..........................................................................*/

/*
 * write_gensym_code_as_cyrillic encodes gensym_code in the
 * latin-cyrillic (ISO 8859-5) character set.  Cyrillic characters
 * are as gensym codes in the range 0x2000..0x20ff, but the subset
 * that maps to ISO 8859-5 are mostly just characters the range
 * 0x2000..0x205F.  In addition, ASCII and a few odd special
 * characters are also mappable. 
 */
void write_gensym_code_as_cyrillic (output_file, gensym_code)
  FILE *output_file;
  int   gensym_code;
{
  if (gensym_code < 0xA0)	/* ASCII or Control code */
    putc(gensym_code, output_file);
  else /* ISO 8859-5 Cyrillic */
    if ((gensym_code >= 0x2000) && (gensym_code < 0x205F))
      putc((0xA0 + (gensym_code - 0x2000)), output_file);
    else if (gensym_code == 0xA0)	/* No-break space */
      putc(gensym_code, output_file);
    else if (gensym_code == 0xAD)	/* Soft hyphen */
      putc(gensym_code, output_file);
    else if (gensym_code == 0x22BE) /* Numero sign */
      putc(0xF0, output_file);
    else if (gensym_code == 0x2178) /* Section sign */
      putc(0xFD, output_file);
    else {
      printf("\nUnknown Gensym character code: %d. Using replacement %c \n",
	     gensym_code, GENSYM_REPLACEMENT_CHAR);
      putc(GENSYM_REPLACEMENT_CHAR, output_file);
    }
}

void write_gensym_string_as_cyrillic (output_file, gensym_string)
  FILE  *output_file;
  octet *gensym_string;
{
  octet character, escape;
  int i = 0, gensym_code;
  while (1) {
    character = gensym_string[i++];
    if (character == NUL) return;
    switch (character) {
    case '@': case '~':
      escape = character;
      character = gensym_string[i++];
      if (character == NUL) {
	/* end of data with malformed Gensym character sequence */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
	return;
      } else if ((escape == '@')
		 && ((character == 'L') || (character == 'P'))) {
	/* line or paragraph break */
	putc ('\n', output_file);
      } else if ((escape == '~')
		 && ((character == '@')
		     ||(character == '~')
		     ||(character == '\\'))) {
	putc (character, output_file);
      } else {
	/* Unhandled (e.g., extended Latin), unknown, and/or illegal
	   Gensym character sequence are all covered by this case. */
	putc (GENSYM_REPLACEMENT_CHAR, output_file);
      }
      break;
    case '\\':
      gensym_code = read_gensym_code_beyond_escape (gensym_string, &i);
      if (gensym_code == 0) /* illegal gensym character sequence case */
	return;
      write_gensym_code_as_cyrillic (output_file, gensym_code);
      break;
    default:
      putc (character, output_file);
      break;
    }
  }
}

void read_cyrillic_as_gensym_string(input_file, octet_buffer)
  FILE  *input_file;
  octet *octet_buffer;
{
  octet character,
    previous_character = 'x'; /* x arbitrary, but not CR or LF */
  int getc_result;
  int i;

  i = 0;
  
  while (1) {
    getc_result = getc(input_file);
    if (getc_result == EOF) break;
    character = (octet)getc_result;
    switch (character) {
    case LF: case CR:
      if ((character == CR) || !(previous_character == CR)) {
	octet_buffer[i++] = '@';
	octet_buffer[i++] = 'L';
      }
      break;
    case '@': case '\\': case '~':
      octet_buffer[i++] = '~';
      octet_buffer[i++] = character;
      break;
    default:
      if ((character < 32) || ((0x7F <= character) && (character < 0xA0)))
	write_gensym_code_into_buffer (character, octet_buffer, &i);
      else if (character == 0xA0)	/* No-break space */
	write_gensym_code_into_buffer (character, octet_buffer, &i);
      else if (character == 0xAD)	/* Soft hyphen */
	write_gensym_code_into_buffer (character, octet_buffer, &i);
      else if (character == 0xF0) /* Numero sign */
	write_gensym_code_into_buffer (0x22BE, octet_buffer, &i);
      else if (character == 0xFD) /* Section sign */
	write_gensym_code_into_buffer (0x2178, octet_buffer, &i);
      else if ((0xA0 <= character) && (character <= 0xFF))
	write_gensym_code_into_buffer
	  (((character - 0xA0) + 0x2000), octet_buffer, &i);
      else
	/* normal, ASCII characters: */
	octet_buffer[i++] = character;
    }
    previous_character = character;
    if (i >= ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1)) {
      printf ("Buffer overflow; cannot handle more than ");
      printf ("%d octets; returning incomplete data \n",
	      ((RETURN_BUF_SZ - MAX_OCTETS_PER_GENSYM_CHAR) - 1));
      break;
    }
  }
  octet_buffer[i] = NUL;
}


/***************************************************************************
:
:  write_in_charset, read_in_charset: runtime character set selection  
:
:..........................................................................*/

/*
 * One of the following values for the charset parameter will be chosen:
 * 
 * (1) KSC_EUC - 0 - for Korean KSC5601-EUC:
 *      write_gensym_string_as_ksc_euc 
 *      and read_ksc_euc_as_gensym_string;
 * (2) JIS_EUC - 1 - for Japanese JISX0208-EUC:
 *      write_gensym_string_as_jis_euc
 *      and read_jis_euc_as_gensym_string;
 * (3) LATIN_CYRILLIC - 2 - for Russian ISO8859-5:
 *      write_gensym_string_as_cyrillic 
 *      and read_cyrillic_as_gensym_string;
 * (4) LATIN_1 - 3 (DEFAULT) - for English and other
 *     Western European languages:
 *      write_gensym_string_as_latin_1 
 *      and read_latin_1_as_gensym_string;
 * (5) SHIFT_JIS - 4 - for Japanese JISX0208-Shift-JIS:
 *      write_gensym_string_as_shiftjis
 *      and read_shiftjis_as_gensym_string;
 */

#define KSC_EUC 0
#define JIS_EUC 1
#define LATIN_CYRILLIC 2
#define LATIN_1 3
#define SHIFT_JIS 4

void write_in_charset (output_file, gensym_string, charset)
  FILE  *output_file;
  octet *gensym_string;
  int    charset;
{
  switch (charset) {
  case KSC_EUC:
    write_gensym_string_as_ksc_euc(output_file, gensym_string);
    break;
  case JIS_EUC:
    write_gensym_string_as_jis_euc(output_file, gensym_string);
    break;
  case LATIN_CYRILLIC:
    write_gensym_string_as_cyrillic(output_file, gensym_string);
    break;
  case SHIFT_JIS:
    write_gensym_string_as_shiftjis(output_file, gensym_string);
    break;
  default:  /* LATIN_1 case */
    write_gensym_string_as_latin_1(output_file, gensym_string);
    break;
  }
}

void read_in_charset (input_file, gensym_string, charset)
  FILE  *input_file;
  octet *gensym_string;
  int    charset;
{
  switch (charset) {
  case KSC_EUC:
    read_ksc_euc_as_gensym_string(input_file, gensym_string);
    break;
  case JIS_EUC:
    read_jis_euc_as_gensym_string(input_file, gensym_string);
    break;
  case LATIN_CYRILLIC:
    read_cyrillic_as_gensym_string(input_file, gensym_string);
    break;
  case SHIFT_JIS:
    read_shiftjis_as_gensym_string(input_file, gensym_string);
    break;
  default:  /* LATIN_1 case */
    read_latin_1_as_gensym_string(input_file, gensym_string);
    break;
  }
}


/***************************************************************************
:
:  Remote procedure calls write_file and read_file  
:
:..........................................................................*/

/*
 * write_file is to be called with the following 3 arguments in the 
 * arguments array:
 *
 * (1) arguments[0]: pathname - a string 
 *      - the pathname of the file to be written
 * (2) arguments[1]: gensym_string - a gensym string 
 *      - the gensym string to be written
 * (3) arguments[2]: charset - an integer - output file character set:
 *       0 for Korean; 1 for Japanese; 2 for Russian; 3 for English
 *
 * This returns no useful values.  Its principle side effect is writing the
 * specified file with content corresponding to the gensym_string argument.
 */

void write_file(arguments, count, call_handle)
  gsi_item *arguments;
  gsi_int   count, call_handle;
{
  FILE     *output_file;

  output_file = fopen(gsi_str_of(arguments[0]), "w");
  write_in_charset (output_file,
		    gsi_str_of(arguments[1]),
		    gsi_int_of(arguments[2]));
  fclose(output_file);
}

/*
 * read_file is to be called with the following 3 arguments in the 
 * arguments array:
 *
 * (1) arguments[0]: pathname - a string - the pathname of the file to be read
 * (2) arguments[1]: charset - an integer - input file character set:
 *       0 for Korean; 1 for Japanese; 2 for Russian; 3 for English
 *
 * This returns no useful values.  Its principle side effect is reading the
 * specified file, and placing its content, encoded in the Gensym character
 * set, into to the buffer return_file_content_buffer.
 */

void read_file(arguments, count, call_handle)
  gsi_item *arguments;
  gsi_int   count, call_handle;
{
  FILE     *input_file;
  gsi_item *return_value_pointer;

  if ((input_file = fopen(gsi_str_of(arguments[0]), "r"))
      == NULL) {
    printf("Can't open file %s \n", gsi_str_of(arguments[0]));
    return;
  }
  read_in_charset
    (input_file,
     return_file_content_buffer,
     gsi_int_of(arguments[1]));
  fclose(input_file);
 
  /*make one gsi_item */
  return_value_pointer = gsi_make_items(1);
  gsi_set_str(return_value_pointer[0], (gsi_char *)return_file_content_buffer);
  
  /*return to G2 */
  gsi_rpc_return_values
    (return_value_pointer, 1, call_handle, gsi_current_context());
  
  gsi_reclaim_items(return_value_pointer);
}

/*
 * GSI setup function to declare the above rpc functions: 
 *   read_file and write_file.
 * Have the second arg match the name-in-remote-system of
 *   read-file and write-file, the remote-procedure-declaration
 *    items in rcp-text-test.kb 
 */

void gsi_set_up ()
{ 
  gsi_rpc_declare_local(read_file, "READ-FILE");
  gsi_rpc_declare_local(write_file, "WRITE-FILE");
}

/*
 * The rest of the file contains functions in their original "boilerplate",
 * untouched from the way they are delivered with G2/GSI 4.x.
 */

gsi_int gsi_get_tcp_port()
{
  return(TCPIP_PORT_NUMBER);
}

gsi_int gsi_initialize_context(remote_process_init_string, length)
  char    *remote_process_init_string;
  gsi_int  length;
{
  printf ("%s\n", remote_process_init_string);
  return (GSI_ACCEPT);
}

void gsi_receive_registration(item_registration)
  gsi_registration item_registration;
{
  gsi_int handle;

  handle = gsi_handle_of(item_registration);

  gsi_set_user_data(item_registration, (void *)5);
  printf ("gsi_receive_registration in context %d\n", gsi_current_context());
}

void gsi_get_data(registered_items, count)
  gsi_registered_item  registered_items[];
  gsi_int              count;
{
  printf ("gsi_get_data in context %d\n", gsi_current_context());
}

void gsi_set_data(registered_items, count)
  gsi_registered_item  registered_items[];
  gsi_int              count;
{
  printf ("gsi_set_data in context %d\n", gsi_current_context());
}

void gsi_pause_context()
{
  printf ("gsi_pause_context in context %d\n", gsi_current_context());
}

void gsi_resume_context()
{
  printf ("gsi_resume_context in context %d\n", gsi_current_context());
}

void gsi_shutdown_context()
{
  printf ("\ngsi_shutdown_context in context %d\n", gsi_current_context());
}

void gsi_g2_poll()
{
  printf ("\ngsi_g2_poll in context %d\n", gsi_current_context());
}

void gsi_receive_deregistrations(registered_items, count)
  gsi_registered_item  registered_items[];
  gsi_int              count;
{
  gsi_int handle;

  handle = gsi_handle_of(registered_items[0]);
  printf("user data (should be 5) : %d\n", 
          (int)gsi_user_data_of(gsi_registration_of(handle,current_context)));
}

void gsi_receive_message(message, length)
  char   *message;
  gsi_int length;
{
  printf ("gsi_receive_message in context %d\n", gsi_current_context());
  printf ("G2 says:%s\n",message);
}

