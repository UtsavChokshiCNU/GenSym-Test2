/* places.h -- Header File for places.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Qeq;
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
extern Object evaluation_place_reference_eql(Object,Object);
extern Object evaluation_place_reference_valid_p(Object);
extern Object gensym_cons_1(Object,Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_evaluation_place_reference_to_place(Object,Object);
extern Object make_permanent_place_reference_internals_structure_internal(void);
extern Object make_place_reference_internals_1(Object,Object,Object);
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
extern Object set_balanced_binary_tree_entry(Object,Object,Object,Object,Object,Object,Object);
extern Object set_property_value_function(Object,Object,Object);
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
extern Object evaluation_place_reference_eql();
extern Object evaluation_place_reference_valid_p();
extern Object gensym_cons_1();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object load_and_initialize_type_description();
extern Object make_evaluation_place_reference_to_place();
extern Object make_permanent_place_reference_internals_structure_internal();
extern Object make_place_reference_internals_1();
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
extern Object set_balanced_binary_tree_entry();
extern Object set_property_value_function();
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
extern Object Available_gensym_conses;
extern Object Chain_of_available_place_reference_internalss;
extern Object Current_computation_component_particulars;
extern Object Current_computation_frame;
extern Object Current_frame_serial_number;
extern Object Current_include_denotation_for_block_flag;
extern Object Defined_evaluation_value_types;
extern Object Place_reference_internals_count;
extern Object Set_of_all_component_kinds;
extern Object Structure_being_reclaimed;
extern Object The_type_description_of_place_reference_internals;
