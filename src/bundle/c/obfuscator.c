/* obfucator.c

   Copyright (C) 1986-2017 Gensym Corporation.
   All Rights Reserved.

   Carl Shapiro and Mark H. David
   
   To compile:

     cc obfuscate.c obfuscator.c  -o obfuscator

   Usage: obfuscate [-d] [-F in_place_file] -k seedstring 
   Seed string's alphanumeric characters, minus case differences, seed the obfuscation.

   The -d option deobfuscates input that was obfuscated using the given seedstring.

   If -F in_place_file, then in_place_file is taken as a file that should be changed
   in place. When this is done, the file permissions are preserved as they were.  (Write
   permissions are temporarily overridden in this mode of operation.)

   Otherwise, the standard input is copied to the standard output.

   */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "obfuscate.h"

void bad_usage(int argc, char *argv[])
{
  /* Quit and give usage for argument problems: too few args, or probable bad
     base reference: atoi returned 0 but arg does not start with 0. */
  fprintf(stderr, "Usage: %s [-d]  [-F in_place_file] -k seedstring\n", argv[0]);
  exit(1);
}

int main(int argc, char *argv[])
{
  char *in_place_file_name = NULL;
  char *seedstring = NULL;
  char *key;  
  int direction = ENCRYPT_DIRECTION, arg_index = 1;

  while (argc > arg_index) {
    if (!strcmp(argv[arg_index], "-d"))
      direction = DECRYPT_DIRECTION;
    if (!strcmp(argv[arg_index], "-F")) {
      arg_index++;
      if (argc > arg_index)
	in_place_file_name = argv[arg_index];
      else
	bad_usage(argc, argv);
    }
    
    if (!strcmp(argv[arg_index], "-k")) {
      arg_index++;
      if (argc > arg_index)
	seedstring = argv[arg_index];
      else
	bad_usage(argc, argv);
    }
    arg_index++;
  }

  if (seedstring == NULL)
    bad_usage(argc, argv);

  if (in_place_file_name == NULL) {
    fprintf(stderr, "%scrypting from standard input to standard output\n",
	    ((direction == ENCRYPT_DIRECTION) ? "en" : "de"));
    init_crypt(derive_base_reference_from_seed_string(seedstring));
    crypt_copy_stream_to_eof(stdin, stdout, direction);
    if (ferror(stdin) || ferror(stdout)) {
      perror("error reading or writing");
      exit(1);
    }
  }
  else 
    crypt_file_in_place(in_place_file_name, seedstring, direction);
    
  return 0;
}
    
  
