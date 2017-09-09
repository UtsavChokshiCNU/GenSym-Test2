/* rings.h -- Header File for rings.c
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

extern Object allocate_managed_array(int,...);
extern Object bytes_per_simple_vector(Object);
extern Object clear_optimized_constants(void);
extern Object compute_exponential_weighting_factors(Object);
extern Object compute_filtered_thrashing_ratio(Object);
extern Object compute_newest_thrashing_ratio(Object,Object);
extern Object compute_next_larger_size_for_ring_buffer_vectors(Object);
extern Object compute_weighting_factors_for_thrashing_filter(void);
extern Object copy_managed_float(Object);
extern Object copy_managed_float_array(Object);
extern Object copy_ring_buffer_shell_slots(Object,Object);
extern Object copy_ring_buffer_vector(Object);
extern Object copy_text_string(Object);
extern Object copy_thrashing_ratio_ring_buffer(int,...);
extern Object direct_structure_method(Object,Object);
extern Object fixnum_time_interval(Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_permanent_ring_buffer_state_structure_internal(void);
extern Object make_permanent_thrashing_ratio_ring_buffer_structure_internal(void);
extern Object make_ring_buffer_state_1(void);
extern Object make_thrashing_ratio_ring_buffer_1(void);
extern Object make_thread_array(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object outstanding_ring_buffer_state_count(void);
extern Object outstanding_thrashing_ratio_ring_buffer_count(void);
extern Object push_optimized_constant(Object);
extern Object reclaim_managed_array(Object);
extern Object reclaim_managed_float_array(Object);
extern Object reclaim_managed_number_or_value_function(Object);
extern Object reclaim_ring_buffer_state_1(Object);
extern Object reclaim_ring_buffer_vector(Object);
extern Object reclaim_thrashing_ratio_ring_buffer_1(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object ring_buffer_state_structure_memory_usage(void);
extern Object store_managed_number_or_value_function(Object,Object);
extern Object text_string_p(Object);
extern Object thrashing_ratio_ring_buffer_structure_memory_usage(void);
extern Object update_object_pool_meters_list(Object);

#else

extern Object allocate_managed_array();
extern Object bytes_per_simple_vector();
extern Object clear_optimized_constants();
extern Object compute_exponential_weighting_factors();
extern Object compute_filtered_thrashing_ratio();
extern Object compute_newest_thrashing_ratio();
extern Object compute_next_larger_size_for_ring_buffer_vectors();
extern Object compute_weighting_factors_for_thrashing_filter();
extern Object copy_managed_float();
extern Object copy_managed_float_array();
extern Object copy_ring_buffer_shell_slots();
extern Object copy_ring_buffer_vector();
extern Object copy_text_string();
extern Object copy_thrashing_ratio_ring_buffer();
extern Object direct_structure_method();
extern Object fixnum_time_interval();
extern Object load_and_initialize_type_description();
extern Object make_permanent_ring_buffer_state_structure_internal();
extern Object make_permanent_thrashing_ratio_ring_buffer_structure_internal();
extern Object make_ring_buffer_state_1();
extern Object make_thrashing_ratio_ring_buffer_1();
extern Object make_thread_array();
extern Object mutate_global_property();
extern Object outstanding_ring_buffer_state_count();
extern Object outstanding_thrashing_ratio_ring_buffer_count();
extern Object push_optimized_constant();
extern Object reclaim_managed_array();
extern Object reclaim_managed_float_array();
extern Object reclaim_managed_number_or_value_function();
extern Object reclaim_ring_buffer_state_1();
extern Object reclaim_ring_buffer_vector();
extern Object reclaim_thrashing_ratio_ring_buffer_1();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object ring_buffer_state_structure_memory_usage();
extern Object store_managed_number_or_value_function();
extern Object text_string_p();
extern Object thrashing_ratio_ring_buffer_structure_memory_usage();
extern Object update_object_pool_meters_list();

#endif

/* variables/constants */
extern Object Base_for_exponential_weighting;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_ring_buffer_states, Qchain_of_available_ring_buffer_states);
extern Object Chain_of_available_ring_buffer_states_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_thrashing_ratio_ring_buffers, Qchain_of_available_thrashing_ratio_ring_buffers);
extern Object Chain_of_available_thrashing_ratio_ring_buffers_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
extern Object Fixnum_time_normalization_factor;
extern Object Largest_ring_buffer_vector_size;
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Managed_array_unique_marker;
extern Object Managed_float_array_unique_marker;
extern Object Maximum_in_place_array_size;
extern Object Maximum_managed_array_size;
DECLARE_VARIABLE_WITH_SYMBOL(Ring_buffer_state_count, Qring_buffer_state_count);
extern Object Smallest_ring_buffer_vector_size;
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
extern Object The_type_description_of_ring_buffer_state;
extern Object The_type_description_of_thrashing_ratio_ring_buffer;
DECLARE_VARIABLE_WITH_SYMBOL(Thrashing_ratio_ring_buffer_count, Qthrashing_ratio_ring_buffer_count);
extern Object Thrashing_ratio_ring_buffer_length;
DECLARE_VARIABLE_WITH_SYMBOL(Weighting_factors_for_thrashing_ratio_ring_buffers, Qweighting_factors_for_thrashing_ratio_ring_buffers);
