/*****************************************************************************
: 
:  fgntest.c -- Sample code for G2 foreign function facility
:
:  This file can be linked into a foreign image into which G2 can make foreign
:  function calls.
:
:  The associated makefile uses the executable utility overlay with the template
:  file fgntest.tpl to generate an overlay file fgnover.c.  It then compiles
:  fgntest.c and fgnover.c, and links the two files with the Gensym foreign
:  image library libforgn to form the executable file fgntest.fgn.
:
:  To call a foreign function inside the resulting executable, you may spawn the
:  foreign image from G2 using the "connect to foreign image" grammar, or you
:  may run the foreign image standalone and use the "connect to external foreign
:  image" grammar.  See the G2 Reference Manual for further information.
:
:  An additional example of calling a foreign function, smaller but more
:  detailed, appears in the G2 Reference Manual.
:
:  Although this software has been extensively tested, Gensym cannot guarantee
:  error-free performance in all applications.  Accordingly, use of the software
:  is at the customer's sole risk.
:
:..........................................................................*/

#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <stdlib.h>
#include <windows.h>
#endif

#include "cprim.h"

/* The template file fgntest.tpl should look like this: */
/*
integer cc_add_integers   add_integers   integer integer
float   cc_add_reals      add_reals      float   float
text    cc_append_text    append_text    text    text
symbol  cc_append_symbols append_symbols symbol  symbol
*/

int
cc_add_integers(addend1, addend2)
int     addend1, addend2;
{
 printf("add_integers(%d, %d)\n", addend1, addend2);
 return addend1 + addend2;
}

double
cc_add_reals(addend1, addend2)
double     addend1, addend2;
{
 printf("add_reals(%f, %f)\n", addend1, addend2);
 return addend1 + addend2;
}

char      *append_result;

/* 
 * The function append_text_shared() is not called directly as a foreign
 * function, but is used by cc_append_text() and cc_append_symbols().  It sets
 * the global append_result for subsequent use by cc_free_memory().
 */
char *
append_text_shared(appendee1, appendee2)
char *appendee1, *appendee2;
{
 int   total_len;

 total_len = 1 + strlen(appendee1) + strlen(appendee2);
 append_result = (char *) malloc(total_len);
 append_result[0] = '\0';
 strcat(append_result, appendee1);
 strcat(append_result, appendee2);
 return append_result;
}

/*
 * Note that cc_append_text() allocates memory each time it is called.  You can
 * reclaim that memory with cc_free_memory().
 */
char *
cc_append_text(appendee1, appendee2)
char *appendee1, *appendee2;
{
 printf("append_text(\"%s\", \"%s\")\n", appendee1, appendee2);
 return append_text_shared(appendee1, appendee2);
}

/*
 * Note that cc_append_symbols() allocates memory each time it is called.  You
 * can reclaim that memory with cc_free_memory().
 */
char *
cc_append_symbols(appendee1, appendee2)
char *appendee1, *appendee2;
{
 printf("append_symbols(%s, %s)\n", appendee1, appendee2);
 return append_text_shared(appendee1, appendee2);
}

/*
 * Use cc_free_memory() to reclaim the memory allocated by cc_append_text() or
 * cc_append_symbols().
 */
int
cc_free_memory()
{
 free(append_result);
 return 0;
}

