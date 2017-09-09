/* osfrgn.h -- Header File for osfrgn.c
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

extern Object g2int_g2_enterprise_p(void);
extern Object g2int_load_foreign_libraries(Object);

#else

extern Object g2int_g2_enterprise_p();
extern Object g2int_load_foreign_libraries();

#endif

/* variables/constants */
extern Object G2int_gensym_environment_variable_buffer;
extern Object G2int_gensym_environment_variable_failure;
extern Object G2int_gensym_environment_variable_success;
extern Object G2int_maximum_gensym_environment_variable_length;
extern Object G2int_null_character_for_c_strings;
extern Object G2int_staris_g2_enterpriseqmstar;
