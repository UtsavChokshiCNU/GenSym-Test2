/* delta.h -- Header File for delta.c
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

extern Object machine_model(void);
extern Object set_system_version(Object,Object);

#else

extern Object machine_model();
extern Object set_system_version();

#endif

/* variables/constants */
extern Object Build_comment_string;
extern Object Build_identification_string;
#define External_version FIX((SI_Long)2015L)
#define Major_version_number_of_current_gensym_product_line FIX((SI_Long)12L)
#define Minor_version_number_of_current_gensym_product_line FIX((SI_Long)0L)
#define Patch_number_of_current_gensym_product_line_qm Qnil
#define Release_quality FIX((SI_Long)3L)
#define Release_quality_of_current_gensym_product_line FIX((SI_Long)3L)
#define Revision_number_of_current_gensym_product_line FIX((SI_Long)9L)
DECLARE_VARIABLE_WITH_SYMBOL(System_version_of_current_gensym_product_line, Qsystem_version_of_current_gensym_product_line);
DECLARE_VARIABLE_WITH_SYMBOL(Systems_in_gensym_product_line, Qsystems_in_gensym_product_line);
