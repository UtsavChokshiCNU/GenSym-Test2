/* g2fnl.h -- Header File for g2fnl.c
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

extern Object ensure_expanded_instruction_macros(void);
extern Object initialize_or_update_method_tables_of_class_descriptions(Object);
extern Object validate_static_evaulate_role_dispatcher(void);

#else

extern Object ensure_expanded_instruction_macros();
extern Object initialize_or_update_method_tables_of_class_descriptions();
extern Object validate_static_evaulate_role_dispatcher();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Ensure_expanded_instruction_macros_has_run_p, Qensure_expanded_instruction_macros_has_run_p);
DECLARE_VARIABLE_WITH_SYMBOL(System_class_method_tables_processed_qm, Qsystem_class_method_tables_processed_qm);
