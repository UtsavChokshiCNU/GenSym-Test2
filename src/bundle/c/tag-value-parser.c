/***************************************************************************
 * Module: tag-value-line-parser.c
 * Copyright (C) 1986-2017 Gensym Corporation.
 *           All Rights Reserved
 *
 * Author(s): David McDonald
 *
 * Description: 
This program examines a line of text that is assumed to consist of
   a colon-delimited tag/value (attribute/value) pair. The tag and
   value can both have embedded spaces. The hash mark ('#') is the 
   comment character. Everything from a # to the end of that line
   is ignored. 
 *
 ***************************************************************************/

#ifdef WIN32
#include "StdAfx.h"
#endif

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "tag-value-parser.h"

/* 
   You drive this tag-value parser by linking it with a program(s) that
   supplies two things. A get_line function as specified just below, and
   a symbolic_tag_to_int function. 

You
   then call parse_line to get successive lines analyzed. Each call will
   skip over any blank or comment lines.  and return a tag_value struct for
   the first line with any content. An an error symbol (int from an enum)
   will be returned instead */

extern int get_line (char* buffer, int maximum);

/* Low-level scan routines */

#define TRUE 1
#define FALSE 0
#define BOOLEAN int

int token_start;
int token_end;

char line[MAX_LINE_LENGTH];

BOOLEAN comment_started;
BOOLEAN reached_colon; 
BOOLEAN colon_missing;
BOOLEAN reached_eof;
int line_length;
int index_of_colon;

int read_and_initialize_line ()
{
  int value = get_line(line, MAX_LINE_LENGTH);
  /* printf("\nLine: \"%s\"\n", line); */
  line_length = strlen(line);
  token_start = 0;
  token_end = 0;
  comment_started = FALSE;
  index_of_colon = -1;
  colon_missing = FALSE;
  reached_colon = FALSE;
  return value;
}

char scan_char()
{
  return line[token_end++];
}

char unscan()
{
  return line[token_end--];
}

void walk_over_whitespace (index)
{
  char c;
  token_end = index;
  if ( line_length > 0 ) {
    for (;;) {
      c = scan_char();
      if (c==' ')
	continue;
      else if (c== '\t')
	continue;
      else {
	if (c=='#')
	  comment_started = TRUE;
	else if (c==':')
	  reached_colon = TRUE;
	else if (c=='\n')
	  token_end--;
	else if (c=='\r')
	  token_end--;
	unscan();
	break;
      }
    }
    token_start = token_end;
    /* printf("After walking over whitespace, token_start/end = %d\n", 
	   token_start); */
  }
}

void walk_back_over_whitespace (index)
{
  char c;
  token_end = index + 1;
  for (;;) {
    token_end--;
    c = line[token_end];
    /* printf("\nWalking back: the character at %d is '%c'\n", token_end, c); */
    if ((c==' ')
	|| (c=='\t')
	|| (c=='\r')
	|| (c=='\n'))
      continue;
    else if (c==0) /* string terminator */
      continue;
    else if (c==':') /* when walking back from the delimiter colon */
      continue;
    else
      return;
  }
  /*printf("After walking back from %d, token_end = %d\n", 
	 index, token_end);*/
}

int locate_the_colon()
{
  int i = token_start;
  while ( line[i]!=':' )
    {
      i++;
      if ( i==line_length )
	return -1;
    }
  return i;
}

int locate_trailing_comment_if_any ()
{
  char c;
  int i = index_of_colon + 1;
  c = line[i];
  do {
    if ( c=='#' ) {
      --i;
      break;
    }
  } while ( c = line[++i] );

  return i;
}


/* NB: scan_token is really quite different from the function with the same name
   in g2pwaux.  Different argument and return types.
    */

void scan_token (buffer) 
char *buffer;
{
  int p1;
  char *p2 = buffer;
  p1 = token_start;
  /* printf("Scan_token: from %d to %d\n", token_start, token_end); */
  while (p1 <= token_end)
    *p2++ = line[p1++];
  *p2 = (char)NULL;
}


void convert_to_lowercase (string)
char string[MAX_TAG_LENGTH];
{ 
  int i = -1;
  while ( string[++i] )
    string[i] = tolower(string[i]);
}




char* error_symbol (id)
int id;
{
  switch (id) {
  case ok:
    return "ok";
  case no_tag:
    return "no tag";
  case no_value:
    return "no value";
  case comment_before_colon:
    return "comment before colon";
  case content_line_without_colon:
    return "content line without colon";
  case end_of_file:
    return "end of file";
  case 20:
    return "comment starts to the left of the colon";
  case 21:
    return "content line with no colon anywhere on it";
  case 50:
    return "reached the end of the file";
  default:
    return "Unknown error number";
  }
}
  


    
/* The driver from the state machine. 
 * It reads the next line from the file and parses out the tag.
 * If the line is whitespace or a comment it loops until it
 * gets a line with content or eof.   */

SYNTAX_ERROR parse_line (tag, value)
char* tag;
char* value;
{
  int index_of_colon = -1;
  int effective_eol;
  int line_value;
  
  for (;;) {

    line_value = read_and_initialize_line();
    if (line_value==0) 
      return end_of_file;

    /* Move token_start across any initial whitespace. */
    walk_over_whitespace(0);
    if (comment_started) 
      continue;
    if (reached_colon) 
      return no_tag;

    index_of_colon = locate_the_colon();
    if (index_of_colon==-1) {
      scan_token(value); /* perhaps the consumer knows what to do */
      return content_line_without_colon;
    }

    /* Move token_end over any whitespace between the tag and the colon. */
    walk_back_over_whitespace(index_of_colon);
    if (comment_started) 
      return comment_before_colon;

    scan_token(tag);
    /* printf("Scanned tag: \"%s\"\n", tag); */

    walk_over_whitespace(index_of_colon + 1);
    if (comment_started) 
      return no_value;

    effective_eol = locate_trailing_comment_if_any();

    walk_back_over_whitespace(effective_eol);

    scan_token(value);
    /* printf("Scanned value: \"%s\"", value); */

    return(ok);
  }
}
