/* places.h -- Header File for places.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Qeq;
extern Object Qeval;
extern Object Qunsigned_byte;
extern Object Qvector;

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
extern Object copy_evaluation_place_reference(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_frame_serial_number(Object);
extern Object copy_place_reference_internals(Object);
extern Object denote_cell_array_element_for_root(Object,Object,Object);
extern Object denote_component_of_block(int,...);
extern Object denote_component_of_block_1(Object,Object);
extern Object denote_component_of_block_1_for_procedure_invocation(void);
extern Object denote_slot_component_group(Object,Object,Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object eval_cons_1(Object,Object);
extern Object evaluation_place_reference_eql(Object,Object);
extern Object evaluation_place_reference_valid_p(Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_evaluation_place_reference_to_place(Object,Object);
extern Object make_permanent_place_reference_internals_structure_internal(void);
extern Object make_place_reference_internals_1(Object,Object,Object);
extern Object make_thread_array(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object outstanding_place_reference_internals_count(void);
extern Object place_reference_internals_structure_memory_usage(void);
extern Object push_optimized_constant(Object);
extern Object reclaim_evaluation_place_reference(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_place_reference_internals_1(Object);
extern Object reclaim_slot_value(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object set_property_value_function(Object,Object,Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object tformat(int,...);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_general_string(Object);
extern Object type_specification_type_p(Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object validate_evaluation_place_reference(Object,Object);
extern Object write_evaluation_place_reference(Object);
extern Object write_procedure_statement(Object);
extern Object write_status_of_component_particulars(Object,Object);

#else

extern Object bytes_per_simple_vector();
extern Object clear_optimized_constants();
extern Object copy_evaluation_place_reference();
extern Object copy_for_slot_value();
extern Object copy_frame_serial_number();
extern Object copy_place_reference_internals();
extern Object denote_cell_array_element_for_root();
extern Object denote_component_of_block();
extern Object denote_component_of_block_1();
extern Object denote_component_of_block_1_for_procedure_invocation();
extern Object denote_slot_component_group();
extern Object direct_structure_method();
extern Object eval_cons_1();
extern Object evaluation_place_reference_eql();
extern Object evaluation_place_reference_valid_p();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object load_and_initialize_type_description();
extern Object make_evaluation_place_reference_to_place();
extern Object make_permanent_place_reference_internals_structure_internal();
extern Object make_place_reference_internals_1();
extern Object make_thread_array();
extern Object mutate_global_property();
extern Object outstanding_place_reference_internals_count();
extern Object place_reference_internals_structure_memory_usage();
extern Object push_optimized_constant();
extern Object reclaim_evaluation_place_reference();
extern Object reclaim_frame_serial_number();
extern Object reclaim_place_reference_internals_1();
extern Object reclaim_slot_value();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object set_property_value_function();
extern Object set_skip_list_entry();
extern Object tformat();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_general_string();
extern Object type_specification_type_p();
extern Object update_object_pool_meters_list();
extern Object validate_evaluation_place_reference();
extern Object write_evaluation_place_reference();
extern Object write_procedure_statement();
extern Object write_status_of_component_particulars();

#endif

/* variables/constants */
extern Object Available_eval_conses_tail_vector;
extern Object Available_eval_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_place_reference_internalss, Qchain_of_available_place_reference_internalss);
extern Object Chain_of_available_place_reference_internalss_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_component_particulars, Qcurrent_computation_component_particulars);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_include_denotation_for_block_flag, Qcurrent_include_denotation_for_block_flag);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Data_series, Qdata_series);
DECLARE_VARIABLE_WITH_SYMBOL(Defined_evaluation_value_types, Qdefined_evaluation_value_types);
DECLARE_VARIABLE_WITH_SYMBOL(Place_reference_internals_count, Qplace_reference_internals_count);
DECLARE_VARIABLE_WITH_SYMBOL(Set_of_all_component_kinds, Qset_of_all_component_kinds);
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
extern Object The_type_description_of_place_reference_internals;
