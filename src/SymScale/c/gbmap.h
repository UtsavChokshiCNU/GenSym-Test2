/* gbmap.h -- Header File for gbmap.c
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

extern Object regenerate_optimized_constant(Object);

#else

extern Object regenerate_optimized_constant();

#endif

/* variables/constants */
extern Object Gb_2312_to_unicode_map;
