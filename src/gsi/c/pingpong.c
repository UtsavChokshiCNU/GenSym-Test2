/*******************************************************************************
:
:  pingpong.c  --  GSI regression test for G2 to GSI RPCs.
:
:  Copyright (C) 1986-2017 Gensym Corporation.
:  All Rights Reserved.
:
:  Mark H. David
:
:  This is a simple GSI test/example bridge.  When it runs, it
:  sends messages of various fixed sizes to a G2 running a
:  companion KB, gsi-pingpong.kb, via RPC, and gets the string back,
:  checking to ensure that the string contents made the round trip
:  correctly.  Note: when running in the narrow-string version, it
:  consumes a great deal of memory on the first iteration.  This is
:  not a leak, however; the memory is reused on subsequent iterations.
:
:  Usage summary:
:
:    pingpong {[-b n] | [-e n] | -i n | [-v] | [-s]} [host [port]]
:        -b n   beginning size (default: 0)
:        -e n   end size (default: 1000)
         -i n   iteration count for outer loop (default: 1)
:        -v     verbose flag  (default: off)
:        -s     shutdown flag (default: off)
:        -a     atom flag (send/receive symbols) (default: off)
:        host   host name or ip address; defaults to "localhost"
:        port   tcp/ip port to use; defaults to 1111
:
:  To build the executable, you can compile this with or without the
:  GSI_USE_WIDE_STRING_API flag.  Throughput and performance are
:  best with the flag, since GSI/G2 natively use wide strings.  You
:  can also compile with or without the GSI_USE_NEW_SYMBOL_API flag.
:  Application performance is generally better with the new API when the
:  same symbols are frequently passed back and forth, since they then 
:  can be transmitted as single objects with no need to copy the string 
:  across the wire each time the symbol is transmitted, only the first time.
:  
:  To make executables, after cd'ing to the GSI release directory and copying
:  pingpong.c to that directory.  Note: the narrow version is called
:  pingpong(.exe), and the wide version is called pingpongw(.exe), i.e., with a "w"
:  suffix.
:  
:  Sparcsol:
:    Narrow string API:
:      cc -c -I./ pingpong.c
:      cc -o pingpong pingpong.o -L./ -lgsi -ltcp -lrtl -lsocket -lintl -lm -lnsl -ldl
:    Wide string API:
:      cc -o pingpongw.o -c -DGSI_USE_WIDE_STRING_API -I./ pingpong.c
:      cc -o pingpongw pingpongw.o -L./ -lgsi -ltcp -lrtl -lsocket -lintl -lm -lnsl -ldl
:    New Symbol API, Narrow string API:
:      cc -o pingpongs.o -c -DGSI_USE_NEW_SYMBOL_API -I./ pingpong.c
:      cc -o pingpongs pingpongs.o -L./ -lgsi -ltcp -lrtl -lsocket -lintl -lm -lnsl -ldl
:    New Symbol API, Wide string API:
:      cc -o pingpongsw.o -c -DGSI_USE_NEW_SYMBOL_API -DGSI_USE_WIDE_STRING_API -I./ pingpong.c
:      cc -o pingpongsw pingpongsw.o -L./ -lgsi -ltcp -lrtl -lsocket -lintl -lm -lnsl -ldl
:  
:  Windows or others: (can be filled in adapting the above to the analogous build
:    steps in the platform-specific GSI make file)
:  
:  NB: this is built with the GSI_USE_USER_DATA_FOR_CALLBACKS compiler
:  flag on, and it does not work to specify that flag as "off" when
:  compiling.
:
:  Mark H. David, 3/10/04
:
:.............................................................................*/

#define GSI_USE_USER_DATA_FOR_CALLBACKS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gsi_main.h"



/* My Utilities for working with GSI Strings (gsi_char *) -- these have "my_"
   prefixed, since they will probably be defined in gsi_misc.c soon (without the
   "my_" prefix), but we want to be able to run this with older GSI releases for
   now. -mhd, 3/16/04*/

int my_gsi_strlen(gsi_char *str)
{
  int i = 0;
  while (*str != '\0') {
    str++;
    i++;
  }
  return i;
}



gsi_char *my_gsi_strcpy(gsi_char *dst, char *src)
{
  gsi_char *dstptr = dst;

  while (1) {
    if((*dstptr = *src) == (gsi_char)'\0')
      break;
    dstptr++;
    src++;
  }
  return dst;
}


gsi_char *my_gsi_strdup(char *str)
{
  gsi_char *copy = (gsi_char *)malloc(sizeof(gsi_char) * (strlen(str) + 1));

  return my_gsi_strcpy(copy, str);
}


int my_gsi_strcmp(gsi_char *str1, gsi_char *str2)
{
  int i;
  gsi_char c1, c2;
  gsi_char nul = (gsi_char)0;

  i = 0;
  while(1) {
    c1 = str1[i];
    c2 = str2[i];

    i++;
    
    if (c1 == nul)
      if (c2 == nul)
	return 0;
      else
	return (- i);
    else if (c2 == nul)
      return i;
    else if (c1 < c2)
      return (- i);
    else if (c1 > c2)
      return i;
  }
}


char *my_gsi_strcpy_gsi_char_to_char (char *dst, gsi_char *src)
{
  char *dstptr = dst;
  gsi_char c;

  while (1) {
    c = *src;

#ifdef GSI_USE_WIDE_STRING_API
    /* note: characters codes > 255 => '?'; Fine for Latin 1 text only, not
       great for others! */
    if (c > 0xFF)
      c = (gsi_char)'?';
#endif

    if((*dstptr = c) == (gsi_char)'\0')
      break;
    dstptr++;
    src++;
  }
  return dst;
}


char *my_gsi_strdup_gsi_char_to_char (gsi_char *str)
{
  char *copy = (char *)malloc(sizeof(char) * (my_gsi_strlen(str) + 1));

  return my_gsi_strcpy_gsi_char_to_char(copy, str);
}

/* End of My Utilities for working with GSI Strings (gsi_char *) */


gsi_function_handle_type pingpong;
gsi_function_handle_type pingpong_symbol;

extern declare_gsi_rpc_receiver_fn(pingpong_return_receiver);

int processing_pingpong_string;	/* boolean - lock awaiting return */
int pingpong_verbose = 0;	/* boolean - print string & other info */
gsi_char *the_pingpong_string;	/* string returned, while processing */
int pingpong_error_count;	/* incremented as each error encountered */
int pingpong_uses_symbols = 0;	/* use symbols instead of strings */
int connected = 0;
int my_context = -1;




/* create_gsi_string_with_alphabet() creates a sequence of 8-bit bytes of length
   given by
     
     ((count - 1) * sizeof(gsi_char)) + 1

   The 1 extra is for the NUL, which is at the position given by
       
     ((short_count * sizeof(gsi_char)) - 1):

     For wide string, will appear in memory as:

     aAbBcCdDeEfFgGhHiI...  OR
     AaBbCcDdEeFfGgHhIi...

     For narrow string, will appear in memory as:
     
     abcdefghi...

     */

gsi_char *create_gsi_string_with_alphabet(int count)
{
  int i;
  char *ss;
  int length = (count + 1) * sizeof(gsi_char); /* 1 extra for NUL */
  gsi_char *s = (gsi_char *)malloc(length);
  ss = (char *)s;
  for (i = 0; i < count; i++) {
    *ss = (char)('a' + i%26);
    ss++;
    if (sizeof(gsi_char) == 2) { /* wide string API */
      *ss = (char)('A' + i%26);
      ss++;
    }
  }
  s[count] = '\0';
  return s;
}



void exit_if_gsi_error()
{
  if (gsi_last_error() == 0)
    return;
  fprintf(stderr, "Error!");
  fflush (stderr);    
  exit(2);
}



int main(int argc, char *argv[])
{
  int i, iteration;
  char *description = (char *)malloc(1000);

  /* vars and code for args & optional args, works on Windows or Unix, based
     on <stdlib.h>'s getopt(). */
  char *s;
  char *optarg;
  int optind;
  char *host = "localhost";
  int port = 1111;
  char *port_string = "1111";
  int shutdown_at_end = 0;
  int errflg = 0;
  int beginning_size = 0;
  int end_size = 1000;
  int iteration_count = 1;

  for (optind = 1; optind < argc; optind++) {
    s = argv[optind];
    if (!strcmp(s, "-v"))
      pingpong_verbose = 1;
    else if (!strcmp(s, "-s"))
      shutdown_at_end = 1;
    else if (!strcmp(s, "-a"))
      pingpong_uses_symbols = 1;
    else if (!strcmp(s, "-b")) {
      optind++;
      if (optind < argc) {
	optarg = argv[optind];
	if (sscanf(optarg, "%d", &beginning_size) == EOF)
	  errflg++;
      }
    }
    else if (!strcmp(s, "-e")) {
      optind++;
      if (optind < argc) {
	optarg = argv[optind];
	if (sscanf(optarg, "%d", &end_size) == EOF)
	  errflg++;
      }
    }
    else if (!strcmp(s, "-i")) {
      optind++;
      if (optind < argc) {
	optarg = argv[optind];
	if (sscanf(optarg, "%d", &iteration_count) == EOF)
	  errflg++;
      }
    }
    else
      break;
  }

  if (optind < argc) {
    host = argv[optind];
    optind++;
    if (optind < argc) {
      if (sscanf(argv[optind], "%d", &port) == EOF)
	errflg++;
      port_string = (char *)strdup(argv[optind]);
      optind++;
    }
  }

  if (errflg) {
    fprintf(stderr,
	    "usage: cmd {[-b n] | [-e n] | [-i n] | [-v] | [-s] [-a]} [host [port]]\n");
    exit (2);
  }
      
  printf("\nCommand:\n  %s -b %d -e %d -i %d%s%s%s %s %s   (using %s string API)\n",
	 argv[0], beginning_size, end_size, iteration_count,
	 (pingpong_verbose ? " -v" : ""),
	 (shutdown_at_end ? " -s" : ""),
	 (pingpong_uses_symbols ? " -a" : ""),
	 host,
	 port_string,
	 ((sizeof(gsi_char) > 1) ? "wide" : "narrow"));

  gsi_set_include_file_version
    (GSI_INCLUDE_MAJ_VER_NUM, GSI_INCLUDE_MIN_VER_NUM, GSI_INCLUDE_REV_VER_NUM);
  GSI_SET_OPTIONS_FROM_COMPILE();
  gsi_start(argc, argv);
  exit_if_gsi_error();
  gsi_initiate_connection
    (NULL,NULL, FALSE, my_gsi_strdup("TCP-IP"), my_gsi_strdup(host),
     my_gsi_strdup(port_string), my_gsi_strdup("hello from GSI"));
  while (!connected) {
    exit_if_gsi_error();
    gsi_set_pause_timeout(10);	/* pause period = 10 milliseconds */
    gsi_pause();
    gsi_run_loop();
  }
  iteration = 1;
  while (iteration <= iteration_count) {
    printf("Calling RPCs. String sizes: from %d to %d. (Iteration %d/%d)\n",
	   beginning_size, end_size,
	   iteration, iteration_count);
    pingpong_error_count = 0;
    for (i = beginning_size; i <= end_size; i++) {
      gsi_item *args;
      gsi_char *string;
      gsi_symbol symbol;

      args = gsi_make_items(1);
      if (!pingpong_uses_symbols)
	gsi_set_type(args[0], GSI_STRING_TAG);
      string = create_gsi_string_with_alphabet(i);
      the_pingpong_string = string; /* used by return receiver */
      the_pingpong_string = string; /* used by return receiver */
      if (pingpong_uses_symbols) {
	symbol = gsi_make_symbol(string);
	gsi_set_sym(args[0], symbol);
	gsi_rpc_call(pingpong_symbol, args, (gsi_call_identifier_type)i, my_context);
      }
      else {
	gsi_set_str(args[0], string);
	gsi_set_type(args[0], GSI_STRING_TAG);
	gsi_rpc_call(pingpong, args, (gsi_call_identifier_type)i, my_context);
      }
      if (pingpong_verbose)
	printf("ping: gsi_char count: %d: octets: %s\n", i, (char *)string);    
      processing_pingpong_string = 1;
      while (processing_pingpong_string) {
	/* run loop runs the return receiver, which clears the flag: */
	gsi_run_loop();
	gsi_pause();
	exit_if_gsi_error();
      }
      free(string);
      gsi_reclaim_items(args);
    }
    printf("DONE. %d error%s%s\n",
	   pingpong_error_count,
	   (pingpong_error_count == 1) ? "" : "s",
	   (pingpong_error_count < 1) ? "." : "!!!");
    iteration++;
  }
  gsi_set_pause_timeout(1000); /* pause period = 1 second */
  i = 0;
  while (shutdown_at_end ? i < 10 : 1) {
    if (shutdown_at_end) {
      printf("%s", (i == 0) ? "Shutting down." : " .");
      fflush (stdout);
    }
    gsi_run_loop();
    gsi_pause();
    exit_if_gsi_error();
    i++;
  }

  printf("Bye!\n");
  fflush (stdout);
  gsi_close_listeners();
  return 0;
}
/* end main */



/* Callbacks: the function pingpong_return_receiver() should expects 1 as the
   count of args, the one arg to be a GSI string (gsi_char *), and
   call_identifier to be the expected length of the string (by coercion to
   int). It looks at the global variable the_pingpong_string, which should be
   the current string that was sent to G2's PINGPONG procedure, which returns
   that string.

   If the arg data is wrong, this can abort.  Otherwise, if there's just a
   problem with the string contents or length, it increments the global variable
   pingpong_error_count, and prints the expected vs. actual data and length.  If
   the global verbose pingpong_verbose is set, this always prints the expected
   and actual data and length. */

void pingpong_return_receiver(gsi_procedure_user_data_type data,
			      gsi_item *args,
			      gsi_int count,
			      gsi_call_identifier_type call_identifier)
{
  gsi_symbol symbol
    = (pingpong_uses_symbols ? gsi_sym_of(args[0]) : (gsi_symbol)NULL);
  gsi_char *string
    = (pingpong_uses_symbols ? gsi_symbol_name(symbol) : gsi_str_of(args[0]));
  int length = my_gsi_strlen(string);
  int expected_length = (int)call_identifier;
  int ok = ((length == expected_length)
	    && !my_gsi_strcmp(string, the_pingpong_string));

  if (!ok)
    pingpong_error_count++;

  if (!ok || pingpong_verbose)
    printf("pong: %s; length: %d; characters: %s%s\n",
	    ok ? "OK" : "BAD!", length, (char *)string,
	   pingpong_uses_symbols ? " (symbol case)" : "");

  if (!ok)
    printf("  expected: length: %d; characters: %s%s\n",
	   expected_length, (char *)the_pingpong_string,
	   pingpong_uses_symbols ? " (symbol case)" : "");

  processing_pingpong_string = 0;  
}




void gsi_set_up()
{
  gsi_set_option(GSI_ONE_CYCLE);
  gsi_clear_last_error();
}




gsi_int gsi_initialize_context(remote_process_init_string, length)
    gsi_char *remote_process_init_string;
    gsi_int  length;
{
  /* printf("Connection received: %s\n",remote_process_init_string); */
  gsi_clear_last_error();
  
  gsi_rpc_declare_remote
    (&pingpong, my_gsi_strdup("PINGPONG"), pingpong_return_receiver,
     (procedure_user_data_type)NULL, 1, 1, current_context);
  gsi_rpc_declare_remote
    (&pingpong_symbol, my_gsi_strdup("PINGPONG-SYMBOL"), pingpong_return_receiver,
     (procedure_user_data_type)NULL, 1, 1, current_context);

  my_context = gsi_current_context();
  connected = 1;
  
  return(GSI_ACCEPT);
}





/* The remaining callback functions are required by GSI, but they're for now
   defined as empty stubs.*/

gsi_int gsi_get_tcp_port()
{
  return 0;
}

void gsi_receive_registration(gsi_registration registration)
{
}

void gsi_get_data(gsi_registered_item registered_item_array[], gsi_int count)
{}

void gsi_set_data(gsi_registered_item  registered_item_array[], gsi_int count)
{}

void gsi_pause_context()
{}

void gsi_resume_context()
{}

void gsi_shutdown_context()
{}

void gsi_g2_poll()
{}

void gsi_receive_deregistrations(gsi_registered_item  registered_item_array[], gsi_int count)
{}

void gsi_receive_message(gsi_char *message, gsi_int length)
{}
