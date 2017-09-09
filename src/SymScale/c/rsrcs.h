/* rsrcs.h -- Header File for rsrcs.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qtype;

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

extern Object add_resource_property_to_structure(Object,Object,Object,Object);
extern Object allocate_evaluation_sequence(Object);
extern Object allocate_managed_array(int,...);
extern Object bytes_per_double_float_simple_array(Object);
extern Object bytes_per_simple_vector(Object);
extern Object clear_optimized_constants(void);
extern Object compiled_resource_p_function(Object);
extern Object compiled_resource_structure_memory_usage(void);
extern Object compiled_resource_to_component(Object);
extern Object copy_as_wide_string(Object);
extern Object copy_if_evaluation_value_1(Object);
extern Object copy_list_using_eval_conses_1(Object);
extern Object copy_managed_float(Object);
extern Object copy_managed_long(Object);
extern Object decode_resource_from_list(Object);
extern Object direct_structure_method(Object,Object);
extern Object encode_resource_as_list(Object);
extern Object eval_cons_1(Object,Object);
extern Object generate_float_vector(Object);
extern Object get_reference_to_item(Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_compiled_resource_1(Object,Object,Object,Object);
extern Object make_evaluation_long(Object);
extern Object make_gensym_list_1(Object);
extern Object make_permanent_compiled_resource_structure_internal(void);
extern Object make_thread_array(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object outstanding_compiled_resource_count(void);
extern Object push_optimized_constant(Object);
extern Object reclaim_compiled_resource_1(Object);
extern Object reclaim_compiled_resource_function(Object);
extern Object reclaim_compiled_resource_slot(Object);
extern Object reclaim_slot_value(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object safe_and_stupid_getf(Object,Object);
extern Object set_evaluation_structure_slot(Object,Object,Object);
extern Object text_string_p(Object);
extern Object update_object_pool_meters_list(Object);

#else

extern Object add_resource_property_to_structure();
extern Object allocate_evaluation_sequence();
extern Object allocate_managed_array();
extern Object bytes_per_double_float_simple_array();
extern Object bytes_per_simple_vector();
extern Object clear_optimized_constants();
extern Object compiled_resource_p_function();
extern Object compiled_resource_structure_memory_usage();
extern Object compiled_resource_to_component();
extern Object copy_as_wide_string();
extern Object copy_if_evaluation_value_1();
extern Object copy_list_using_eval_conses_1();
extern Object copy_managed_float();
extern Object copy_managed_long();
extern Object decode_resource_from_list();
extern Object direct_structure_method();
extern Object encode_resource_as_list();
extern Object eval_cons_1();
extern Object generate_float_vector();
extern Object get_reference_to_item();
extern Object load_and_initialize_type_description();
extern Object make_compiled_resource_1();
extern Object make_evaluation_long();
extern Object make_gensym_list_1();
extern Object make_permanent_compiled_resource_structure_internal();
extern Object make_thread_array();
extern Object mutate_global_property();
extern Object outstanding_compiled_resource_count();
extern Object push_optimized_constant();
extern Object reclaim_compiled_resource_1();
extern Object reclaim_compiled_resource_function();
extern Object reclaim_compiled_resource_slot();
extern Object reclaim_slot_value();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object safe_and_stupid_getf();
extern Object set_evaluation_structure_slot();
extern Object text_string_p();
extern Object update_object_pool_meters_list();

#endif

/* variables/constants */
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
extern Object Available_gensym_conses_tail_vector;
extern Object Available_gensym_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_compiled_resources, Qchain_of_available_compiled_resources);
extern Object Chain_of_available_compiled_resources_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Compiled_resource_count, Qcompiled_resource_count);
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
#define Falsity FIX((SI_Long)-1000L)
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
extern Object The_type_description_of_compiled_resource;
#define Truth FIX((SI_Long)1000L)
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
