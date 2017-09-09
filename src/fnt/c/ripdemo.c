/* -*- Mode: C -*-
 *
 * Module RIPDEMO.C
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Mark H. David
 * 
 * This file contains a main() function, and is intended for testing
 * the 4in1 font rasterizer, by calling the front end defined in
 * the module fontrip.c.
 *
 */

#include <stdio.h>
#include "speedo.h"
static char pathname[100];	/* Name of font file to be output */
int main(argc,argv)
     int argc;
     char *argv[];
{
  /* run_built_in_demo("SWISS721-SWA", 25, 25, 0, 0, 0); */
  if (argc != 2)
    {
      exit(1);
    }
  sprintf(pathname, argv[1]);
  
  g2fnt_run_font_demo(pathname, 25, 25, 0, 0, protoUnicode); 

  /*
 run_bcid_char_demo(pathname, 25, 25, 0, 0);
 */
}

