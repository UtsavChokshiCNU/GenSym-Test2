/* jismap.h -- Header File for jismap.c
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

extern Object g2int_gensym_jis_code_to_contiguous(Object);
extern Object g2int_make_cjk_code_mapping_vector(void);
extern Object g2int_regenerate_optimized_constant(Object);
extern Object g2int_set_cjk_code_mapping(Object,Object,Object);

#else

extern Object g2int_gensym_jis_code_to_contiguous();
extern Object g2int_make_cjk_code_mapping_vector();
extern Object g2int_regenerate_optimized_constant();
extern Object g2int_set_cjk_code_mapping();

#endif

/* variables/constants */
extern Object G2int_jis_x_0208_to_unicode_map;
extern Object G2int_unicode_to_jis_x_0208_map;
