/* ntrrr.h -- Header File for ntrrr.c
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

extern Object bytes_per_simple_vector(Object);
extern Object clear_optimized_constants(void);
extern Object direct_structure_method(Object,Object);
extern Object error_code_structure_memory_usage(void);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_error_code_1(Object,Object);
extern Object make_permanent_error_code_structure_internal(void);
extern Object make_thread_array(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object outstanding_error_code_count(void);
extern Object push_optimized_constant(Object);
extern Object reclaim_error_code_1(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object update_object_pool_meters_list(Object);

#else

extern Object bytes_per_simple_vector();
extern Object clear_optimized_constants();
extern Object direct_structure_method();
extern Object error_code_structure_memory_usage();
extern Object load_and_initialize_type_description();
extern Object make_error_code_1();
extern Object make_permanent_error_code_structure_internal();
extern Object make_thread_array();
extern Object mutate_global_property();
extern Object outstanding_error_code_count();
extern Object push_optimized_constant();
extern Object reclaim_error_code_1();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object update_object_pool_meters_list();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_error_codes, Qchain_of_available_error_codes);
extern Object Chain_of_available_error_codes_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Error_code_count, Qerror_code_count);
extern Object Error_severity_fatal;
extern Object Error_severity_informational;
extern Object Error_severity_success;
extern Object Error_severity_warning;
extern Object The_type_description_of_error_code;
