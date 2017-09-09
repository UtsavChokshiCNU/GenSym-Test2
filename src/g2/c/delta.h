/* delta.h -- Header File for delta.c
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

extern Object machine_model(void);
extern Object set_system_version(Object,Object);

#else

extern Object machine_model();
extern Object set_system_version();

#endif

/* variables/constants */
#define Beta_release_quality FIX((SI_Long)2L)
extern Object Build_comment_string;
extern Object Build_identification_string;
#define External_version FIX((SI_Long)2015L)
#define Major_version_number_of_current_gensym_product_line FIX((SI_Long)12L)
#define Minor_version_number_of_current_gensym_product_line FIX((SI_Long)0L)
#define Patch_number_of_current_gensym_product_line_qm Qnil
#define Release_quality_of_current_gensym_product_line FIX((SI_Long)2L)
#define Revision_number_of_current_gensym_product_line FIX((SI_Long)20L)
extern Object System_version_of_current_gensym_product_line;
extern Object Systems_in_gensym_product_line;
