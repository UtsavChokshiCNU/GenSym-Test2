#ifndef _TAG_VALUE_PARSER_H_INCLUDED_
#define _TAG_VALUE_PARSER_H_INCLUDED_

#include <stdio.h>

#define MAX_LINE_LENGTH 1024
#define MAX_TAG_LENGTH 50
#define MAX_VALUE_LENGTH MAX_LINE_LENGTH - (MAX_TAG_LENGTH + 1)

typedef enum {ok, 
	      no_tag, no_value, 
	      comment_before_colon, content_line_without_colon,
	      end_of_file
} SYNTAX_ERROR;


SYNTAX_ERROR parse_line (char* tag, char* value);

#endif
