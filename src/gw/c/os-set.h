/* os-set.h -- Header File for os-set.c
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

extern Object g2int_c_environment_var_strlen(Object);
extern Object g2int_c_return_argv_n(Object,Object);
extern Object g2int_c_return_environment_var(Object,Object);
extern Object g2int_cache_command_line_if_necessary(void);
extern Object g2int_copy_foreign_string_arg_if_appropriate(Object);
extern Object g2int_copy_null_terminated_string_as_text_string(Object);
extern Object g2int_copy_unix_line_arguments_as_text_strings(void);
extern Object g2int_foreign_get_command_line_argument(Object);
extern Object g2int_foreign_get_environment_variable(Object);
extern Object g2int_gensym_cons_function(Object,Object);
extern Object g2int_get_gensym_command_line_argument(Object);
extern Object g2int_get_gensym_command_line_argument_as_text_string(Object);
extern Object g2int_import_text_string(int,...);
extern Object g2int_obtain_simple_gensym_string(Object);
extern Object g2int_reclaim_gensym_string(Object);
extern Object g2int_windows_platform_p(void);

#else

extern Object g2int_c_environment_var_strlen();
extern Object g2int_c_return_argv_n();
extern Object g2int_c_return_environment_var();
extern Object g2int_cache_command_line_if_necessary();
extern Object g2int_copy_foreign_string_arg_if_appropriate();
extern Object g2int_copy_null_terminated_string_as_text_string();
extern Object g2int_copy_unix_line_arguments_as_text_strings();
extern Object g2int_foreign_get_command_line_argument();
extern Object g2int_foreign_get_environment_variable();
extern Object g2int_gensym_cons_function();
extern Object g2int_get_gensym_command_line_argument();
extern Object g2int_get_gensym_command_line_argument_as_text_string();
extern Object g2int_import_text_string();
extern Object g2int_obtain_simple_gensym_string();
extern Object g2int_reclaim_gensym_string();
extern Object g2int_windows_platform_p();

#endif

/* variables/constants */
#define G2int_c_argv_n_strlen_failure FIX((SI_Long)-1L)
#define G2int_c_environment_var_strlen_failure FIX((SI_Long)-1L)
extern Object G2int_g2_machine_type;
extern Object G2int_gensym_environment_variable_success;
extern Object G2int_unix_command_line_argument_count;
extern Object G2int_unix_command_line_arguments;
extern Object G2int_unix_command_line_arguments_as_text_strings;
