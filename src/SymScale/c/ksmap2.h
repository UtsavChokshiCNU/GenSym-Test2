/* ksmap2.h -- Header File for ksmap2.c
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

extern Object gensym_ksc_code_to_contiguous(Object);
extern Object make_cjk_code_mapping_vector(void);
extern Object regenerate_optimized_constant(Object);
extern Object set_cjk_code_mapping(Object,Object,Object);

#else

extern Object gensym_ksc_code_to_contiguous();
extern Object make_cjk_code_mapping_vector();
extern Object regenerate_optimized_constant();
extern Object set_cjk_code_mapping();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Column, Qcolumn);
extern Object Ks_c_5601_to_unicode_map;
DECLARE_VARIABLE_WITH_SYMBOL(Row, Qrow);
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_to_ks_c_5601_map, Qunicode_to_ks_c_5601_map);
