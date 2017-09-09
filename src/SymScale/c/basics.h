/* basics.h -- Header File for basics.c
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

extern Object chestnut_floorf_function(Object,Object);
extern Object chestnut_modf_function(Object,Object);

#else

extern Object chestnut_floorf_function();
extern Object chestnut_modf_function();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Hfep_capability_qm, Qhfep_capability_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Kfep_capability_qm, Qkfep_capability_qm);
