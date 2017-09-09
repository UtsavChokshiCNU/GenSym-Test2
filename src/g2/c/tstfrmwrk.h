/* tstfrmwrk.h -- Header File for tstfrmwrk.c
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

extern Object g2_are_lisp_unit_tests_included_p(void);
extern Object mutate_global_property(Object,Object,Object);

#else

extern Object g2_are_lisp_unit_tests_included_p();
extern Object mutate_global_property();

#endif

/* variables/constants */
extern Object Evaluation_false_value;
