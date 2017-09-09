/* osfrgn.h -- Header File for osfrgn.c
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

extern Object g2_enterprise_p(void);
extern Object load_foreign_libraries(Object);

#else

extern Object g2_enterprise_p();
extern Object load_foreign_libraries();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_environment_variable_buffer, Qgensym_environment_variable_buffer);
extern Object Gensym_environment_variable_failure;
extern Object Gensym_environment_variable_success;
DECLARE_VARIABLE_WITH_SYMBOL(Is_g2_enterprise_qm, Qis_g2_enterprise_qm);
extern Object Maximum_gensym_environment_variable_length;
extern Object Null_character_for_c_strings;
