/* tlsrvr.h -- Header File for tlsrvr.c
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

extern Object add_class_to_environment(int,...);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object clear_optimized_constants(void);
extern Object push_optimized_constant(Object);
extern Object regenerate_optimized_constant(Object);

#else

extern Object add_class_to_environment();
extern Object check_if_superior_classes_are_defined();
extern Object clear_optimized_constants();
extern Object push_optimized_constant();
extern Object regenerate_optimized_constant();

#endif

/* variables/constants */
