/* gbmap.h -- Header File for gbmap.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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

extern Object g2int_regenerate_optimized_constant(Object);

#else

extern Object g2int_regenerate_optimized_constant();

#endif

/* variables/constants */
extern Object G2int_gb_2312_to_unicode_map;
