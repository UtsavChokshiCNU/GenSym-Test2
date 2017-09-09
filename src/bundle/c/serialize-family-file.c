/***************************************************************************
 * Module: serialize-family-file.c
 * Copyright (C) 1986-2017 Gensym Corporation.
 *           All Rights Reserved
 *
 * Author(s): David McDonald
 *
 * Description: Top level driver to serialize family descriptor files.
 *
 * Intended to be used on the command line or via a shell script.
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tag-value-parser.h"
#include "family-descriptor.h"
#include "codes.h"

/* gcc -ggdb family-file-reader.c tag-value-parser.c serialize-family-file.c */

#define TRUE 1
#define FALSE 0

/* All of these are in family-file-reader. */
extern int parse_family_file(FAMILY_DESCRIPTOR* family);
extern FAMILY_DESCRIPTOR* new_family();
extern int trace;
extern int readout;
extern int debug_family_files;

FILE *fp;


/* Available_on_os_bundle_level is a variant of available_on_os, which is
   defined in family-file-reader that operates over bundles rather than
   parts. Wouldn't it be nice to have real objects? */
int available_on_os_bundle_level (bundle, os_mask)
BUNDLE *bundle;
unsigned int os_mask;
{
  if ( ! check_bit(bundle->bdl_os_availability, os_mask) )
    return TRUE;
  else
    return FALSE;
}

/* Print_available_platforms is a subroutine of emit_family_data. */
void print_available_platforms (bundle)
BUNDLE *bundle;
{
  if ( available_on_os_bundle_level(bundle, INTELNT_CODE) )
      printf("intelnt ");
    if ( available_on_os_bundle_level(bundle, SPARCSOL_CODE) )
      printf("sparcsol ");
    if ( available_on_os_bundle_level(bundle, RS6000_CODE) )
      printf("aix ");
    if ( available_on_os_bundle_level(bundle, HPUX_CODE) )
      printf("hpux ");
    if ( available_on_os_bundle_level(bundle, LINUX_CODE) )
      printf("linux ");
    if ( available_on_os_bundle_level(bundle, LINUX64_CODE) )
      printf("linux64 ");
    if ( available_on_os_bundle_level(bundle, ALPHAOSF_CODE) )
      printf("alphaosf ");
    if ( available_on_os_bundle_level(bundle, HPIA64_CODE) )
      printf("hpia64 ");
}


/* Emit_family_data is effectively a Java-stype serializer for family files.
   It emits a compact description of the bundles and components that is used
   to populate the code in <sandbox>/bundle/java/com/gensym/bundle/ so that
   it can programmatically determine what options are available, provide
   that information in a user-friendly way to Order Services, and drive
   the code that creates keys. 
      N.b. the format emitted here has to exactly synchronize with the reader
   code in <sandbox>/bundle/java/com/gensym/bundle/ReadFamilyFileData.java. */
int emit_family_data (family)
FAMILY_DESCRIPTOR *family;
{
  BUNDLE            *bundle;
  COMPONENT         *component;

  printf("\n\n%d ", family->fd_id);
  printf("\"%s\" ", family->fd_name);
  printf("%d ", family->fd_installer_version);
  
  bundle = family->fd_first_bundle;
  if (bundle==NULL)
    return 1;

  for (;;) {
    if (bundle==NULL)
      return 0;
    printf("\n( \"%s\" ", bundle->bdl_name);
    printf("\"%s\" ", bundle->bdl_version);
    printf("%d  ", bundle->bdl_id);

    printf("( ");
    print_available_platforms(bundle);
    printf(")");

    component = bundle->bdl_first_component;
    if (component==NULL)
      return 2;
    for (;;) {
      if (component==NULL)
	break;
      printf("\n  ( \"%s\" ", component->cp_name);
      printf("%d", component->cp_index);
      if ( component->cp_optional == TRUE )
	printf(" optional");
      if ( component->cp_button_group != 0 )
	printf(" %d", component->cp_button_group);
      printf(")");
      component = component->cp_next_component;
    }
    printf(")\n");
    bundle = bundle->bdl_next_bundle;
  }
}



/* get_line is used by the tag-value parser to go through the input file.
 * it returns either a positive integer which is the length of the string
 * that went into the buffer, or 0 to represent the end-of-file condition,
 * or a negative integer to represent an undifferentiated error condition.
 * */

int get_line (buffer, max_length)
char* buffer;
int max_length;
{
  if ( fgets( buffer, max_length, fp) )
    return 2; /* punt on proper implementation */
  else
    return 0;
}

void usage ()
{
  /*  printf("Usage: [{-trace} {(-check|-just-check)} family-file]\n"); */
  printf("Usage: [{-trace} {-check} family-file]\n");
  printf("Serialize-family-file takes a family descriptor file as input\n");
  printf("and emits a serialized form of the data in the file to stdout.\n");
  printf("  The -trace flag will echo what is being seen, line by line, as\n");
  printf("the family-file is being read.\n");
  printf("  You can use the -check flag to have the resulting data structures\n");
  printf("echoed to stdout after the parse is finished.\n");
/*  printf("Using the -just-check flag instead of -check will inhibit XXXX\n" */
}


main (argc, argv)
int argc;
char *argv[];
{
  char path[500];
  int status;
  FAMILY_DESCRIPTOR *family;

  switch (argc) {
  case 2:
    {
      strcpy(path, argv[1]);
      break;
    }
  case 3:
    {
      if ( !strcmp(argv[1], "-trace") )
	trace = TRUE;
      else if ( !strcmp(argv[1], "-check") )
	readout = TRUE;
      else {
	usage();
	exit(1);
      }
      strcpy(path, argv[2]);
      break;
    }
  case 4:
    {
      if ( !strcmp(argv[1], "-trace") )
	trace = TRUE;
      else if ( !strcmp(argv[1], "-check") )
	readout = TRUE;
      else {
	usage();
	exit(1);
      }
      if ( !strcmp(argv[2], "-trace") )
	trace = TRUE;
      else if ( !strcmp(argv[2], "-check") )
	readout = TRUE;
      else {
	usage();
	exit(1);
      }
      strcpy(path, argv[3]);
      break;
    }
  default:
    {
      usage();
      exit(1);
    }
  }

  fp = fopen(path, "r");
  if (fp==NULL) {
    fprintf( stderr, "Error opening %s\n", path);
    exit(1);
  }

  debug_family_files = TRUE;

  family = new_family();

  status = scan_family_file(family);

  if (status != 0)
    printf("\nSyntactic problem detected. Aborting serialization.\n");
  else {
    status = vet_family_descriptor(family);
    if (status != 0)
      printf("\nObvious semantic problem detected. Aborting serialization.\n");
    else {
      status = emit_family_data(family);
      if (status != 0)
	printf("\nProblem (%d) during emitting phase.\n", status);
    }
  }
  
  fclose(fp);
  exit(0);
}
