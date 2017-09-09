/* gbmapr.h -- Header File for gbmapr.c
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
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_to_gb_2312_map, Qunicode_to_gb_2312_map);
