/* intrp.h -- Header File for intrp.c
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

extern Object c_load_dynamic_library(Object);
extern Object g2_load_dynamic_library(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object reclaim_text_string(Object);

#else

extern Object c_load_dynamic_library();
extern Object g2_load_dynamic_library();
extern Object mutate_global_property();
extern Object reclaim_text_string();

#endif

/* variables/constants */
