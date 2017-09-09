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

extern Object g2int_machine_model(void);
extern Object g2int_set_system_version(Object,Object);

#else

extern Object g2int_machine_model();
extern Object g2int_set_system_version();

#endif

/* variables/constants */
#define G2int_beta_release_quality FIX((SI_Long)2L)
extern Object G2int_build_comment_string;
extern Object G2int_build_identification_string;
#define G2int_external_version FIX((SI_Long)2015L)
#define G2int_major_version_number_of_current_gensym_product_line FIX((SI_Long)12L)
#define G2int_minor_version_number_of_current_gensym_product_line FIX((SI_Long)0L)
#define G2int_patch_number_of_current_gensym_product_lineqm Qnil
#define G2int_release_quality_of_current_gensym_product_line FIX((SI_Long)2L)
#define G2int_revision_number_of_current_gensym_product_line FIX((SI_Long)20L)
extern Object G2int_system_version_of_current_gensym_product_line;
extern Object G2int_systems_in_gensym_product_line;
