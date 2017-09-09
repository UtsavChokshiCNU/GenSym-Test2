/* os-set.h -- Header File for os-set.c
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

extern Object c_environment_var_strlen(Object);
extern Object c_return_argv_n(Object,Object);
extern Object c_return_environment_var(Object,Object);
extern Object cache_command_line_if_necessary(void);
extern Object copy_foreign_string_arg_if_appropriate(Object);
extern Object copy_null_terminated_string_as_text_string(Object);
extern Object copy_unix_line_arguments_as_text_strings(void);
extern Object foreign_get_command_line_argument(Object);
extern Object foreign_get_environment_variable(Object);
extern Object gensym_cons_function(Object,Object);
extern Object get_gensym_command_line_argument(Object);
extern Object get_gensym_command_line_argument_as_text_string(Object);
extern Object import_text_string(int,...);
extern Object obtain_simple_gensym_string(Object);
extern Object reclaim_gensym_string(Object);
extern Object windows_platform_p(void);

#else

extern Object c_environment_var_strlen();
extern Object c_return_argv_n();
extern Object c_return_environment_var();
extern Object cache_command_line_if_necessary();
extern Object copy_foreign_string_arg_if_appropriate();
extern Object copy_null_terminated_string_as_text_string();
extern Object copy_unix_line_arguments_as_text_strings();
extern Object foreign_get_command_line_argument();
extern Object foreign_get_environment_variable();
extern Object gensym_cons_function();
extern Object get_gensym_command_line_argument();
extern Object get_gensym_command_line_argument_as_text_string();
extern Object import_text_string();
extern Object obtain_simple_gensym_string();
extern Object reclaim_gensym_string();
extern Object windows_platform_p();

#endif

/* variables/constants */
#define C_argv_n_strlen_failure FIX((SI_Long)-1L)
#define C_environment_var_strlen_failure FIX((SI_Long)-1L)
DECLARE_VARIABLE_WITH_SYMBOL(G2_machine_type, Qg2_machine_type);
extern Object Gensym_environment_variable_success;
DECLARE_VARIABLE_WITH_SYMBOL(Unix_command_line_argument_count, Qunix_command_line_argument_count);
DECLARE_VARIABLE_WITH_SYMBOL(Unix_command_line_arguments, Qunix_command_line_arguments);
DECLARE_VARIABLE_WITH_SYMBOL(Unix_command_line_arguments_as_text_strings, Qunix_command_line_arguments_as_text_strings);
