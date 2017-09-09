/* thai18.h -- Header File for thai18.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */

extern Object Pclos;
extern Object Pclos_run;
extern Object Pclosx;
extern Object Pcl;
extern Object Pcl_user;
extern Object Pkeyword;
extern Object Ptrun;
extern Object Ptx;

/* function declarations */

#ifdef USE_PROTOTYPES

extern Object add_character_description_1(int,...);
extern Object define_ab_font(int,...);
extern Object regenerate_optimized_constant(Object);

#else

extern Object add_character_description_1();
extern Object define_ab_font();
extern Object regenerate_optimized_constant();

#endif

/* variables/constants */
