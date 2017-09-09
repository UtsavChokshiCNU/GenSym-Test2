/* basics.h -- Header File for basics.c
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

extern Object chestnut_floorf_function(Object,Object);
extern Object chestnut_modf_function(Object,Object);

#else

extern Object chestnut_floorf_function();
extern Object chestnut_modf_function();

#endif

/* variables/constants */
extern Object Hfep_capability_qm;
extern Object Kfep_capability_qm;
