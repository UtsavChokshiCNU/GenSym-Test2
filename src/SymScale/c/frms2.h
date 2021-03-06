/* frms2.h -- Header File for frms2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Qeq;
extern Object Kinitial_element;
extern Object Qquote;
extern Object Qsatisfies;
extern Object Qsequence;
extern Object Ktest;
extern Object Qtype;
extern Object Qvariable;

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

extern Object add_class_to_environment(int,...);
extern Object add_inherited_features_and_indexes_to_system_slot_description(Object,Object,Object);
extern Object alias_slot_name(int,...);
extern Object allocate_byte_vector(Object);
extern Object allocate_frame_lookup_structure_vector(Object,Object);
extern Object allocate_managed_long_box(void);
extern Object allocate_managed_simple_vector(Object);
extern Object assign_class_bit_numbers_and_vectors_to_system_classes(void);
extern Object assq_function(Object,Object);
extern Object atomic_slot_value_p(Object);
extern Object buffer_size_for_partial_buffer(Object,Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object car_eq(Object,Object);
extern Object car_equal(Object,Object);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object class_description_cons_1(Object,Object);
extern Object class_function(Object);
extern Object classes_intersect_p(Object,Object);
extern Object clear_all_evaluator_slot_info(void);
extern Object collect_subclasses(Object);
extern Object collect_superclasses(Object);
extern Object collect_user_defined_slot_descriptions_for_defining_class(Object,Object);
extern Object compiled_resource_p_function(Object);
extern Object copy_kb_specific_property_from_global_if_necessary(Object,Object);
extern Object copy_list_using_class_description_conses_1(Object);
extern Object copy_list_using_gensym_conses_1(Object);
extern Object copy_methods(Object,Object);
extern Object copy_slot_descriptions_evaluating_initialization_if_eval_once(Object);
extern Object copy_tree_using_class_description_conses_1(Object);
extern Object decache_cached_class_data(Object);
extern Object define_root_class(void);
extern Object delete_class_description_element_1(Object,Object);
extern Object delete_frame(Object);
extern Object equivalent_method_table_on_path_p(Object,Object);
extern Object error_message_for_dependent_frame_saving(Object);
extern Object eval_slot_init_forms_of_slot_descriptions_defined_for_class(Object,Object);
extern Object frame_cons_1(Object,Object);
extern Object frame_list_2(Object,Object);
extern Object generate_float_vector(Object);
extern Object get_alias_for_slot_name_if_any(Object,Object);
extern Object get_appropriate_slot_descriptions_cons(Object,Object);
extern Object get_foundation_class_for_class(Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_most_specific_direct_superior_for_class(Object);
extern Object get_new_default_slot_description_with_pretty_name(Object,Object);
extern Object get_next_class_bit_number(void);
extern Object get_property_value_function(int,...);
extern Object get_slot_description(int,...);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object get_slot_description_value(Object,Object);
extern Object get_slot_init_form(int,...);
extern Object get_slot_name_for_alias_if_any(Object,Object);
extern Object get_slot_value_function(Object,Object,Object);
extern Object get_slot_value_if_any_function(Object,Object,Object);
extern Object get_slot_value_number_value_or_string_from_slot_constant(Object);
extern Object get_slot_value_or_no_slot_function(Object,Object,Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object initialize_classes_visited_byte_vector(void);
extern Object initialize_method_table_of_class_description(Object,Object,Object);
extern Object initialize_or_update_method_table_for_user_class(Object,Object,Object);
extern Object initialize_or_update_method_tables_of_class_descriptions(Object);
extern Object initialize_slot_description_value(Object,Object,Object);
extern Object install_generic_method_id(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object make_and_change_class_description(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_class_bit_vector(Object,Object);
extern Object make_class_description(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_class_inheritance_path_for_system_defined_class(Object,Object);
extern Object make_full_slot_descriptions_hash_table(Object,Object);
extern Object make_list_of_unaliased_user_overridable_system_slots_for_class(Object);
extern Object make_method_table_for_system_class(void);
extern Object make_partial_buffer_info(Object,Object,Object,Object);
extern Object make_permanent_list(Object);
extern Object make_slot_constant(Object,Object,Object);
extern Object make_slot_constant_using_phrase_conses(Object,Object);
extern Object make_slot_description(int,...);
extern Object make_slot_descriptions_hash_table(Object,Object,Object,Object,Object);
extern Object make_slot_value_float(Object);
extern Object make_slot_value_long(Object);
extern Object make_sparse_slot_descriptions_hash_table(Object,Object,Object);
extern Object make_symbol_properties_hash_table_skip_list_sentinel(Object,Object);
extern Object memq_function(Object,Object);
extern Object merge_slot_descriptions_for_system_defined_class(Object,Object,Object);
extern Object merge_slot_descriptions_for_user_defined_class(Object,Object,Object,Object);
extern Object method_tables_are_equivalent_p(Object,Object);
extern Object most_refined_foundation_class_of_direct_superiors(int,...);
extern Object most_specific_superior_that_refines_slot(Object,Object);
extern Object mutate_global_or_kb_specific_property_value(Object,Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_change_to_dependent_frame_1(void);
extern Object phrase_cons(Object,Object);
extern Object propagate_method(int,...);
extern Object propagate_methods(int,...);
extern Object put_attribute_description_value(Object,Object,Object,Object);
extern Object reclaim_byte_code_body_1(Object);
extern Object reclaim_byte_vector(Object);
extern Object reclaim_class_description_list_1(Object);
extern Object reclaim_class_description_slot_value(Object,Object);
extern Object reclaim_compiled_resource_function(Object);
extern Object reclaim_frame_cons_1(Object);
extern Object reclaim_frame_list_1(Object);
extern Object reclaim_frame_tree_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_initial_slot_value(Object);
extern Object reclaim_lookup_structure_value(Object,Object);
extern Object reclaim_managed_array(Object);
extern Object reclaim_managed_float_array(Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object reclaim_managed_simple_long_array_of_length_1(Object);
extern Object reclaim_managed_simple_vector(Object);
extern Object reclaim_method_table_of_class_description(Object);
extern Object reclaim_relation_instances(Object);
extern Object reclaim_slot_constant(Object);
extern Object reclaim_slot_hash_leaves(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_slot_value_cons_1(Object);
extern Object reclaim_slot_value_cons_function(Object);
extern Object reclaim_slot_value_list_star_1(Object);
extern Object reclaim_slot_value_tree_1(Object);
extern Object reclaim_slot_value_tree_function(Object);
extern Object reclaim_text_string(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object replenish_lookup_cons_pool(void);
extern Object scope_cons(Object,Object);
extern Object set_lookup_slot_value_1(Object,Object,Object);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object set_owner_class_of_method_table(Object,Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object set_slot_description_value_without_noting(Object,Object,Object);
extern Object set_slot_value_function(Object,Object,Object,Object);
extern Object slot_description_of_most_specific_superior_refining_slot(Object,Object);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_cons_function(Object,Object);
extern Object slot_value_equal_p(Object,Object);
extern Object slot_value_float_p_function(Object);
extern Object slot_value_list_2(Object,Object);
extern Object slot_value_long_p_function(Object);
extern Object slot_value_number_p(Object);
extern Object string_eq_w(Object,Object);
extern Object system_class_p(Object);
extern Object system_vector_slots_in_conflict(Object);
extern Object text_string_p(Object);
extern Object unpropagate_methods(int,...);
extern Object update_change_timestamps(Object);
extern Object validate_item_or_evaluation_value(Object,Object,Object);
extern Object well_instantiated_or_subclassed_class_p(Object);

#else

extern Object add_class_to_environment();
extern Object add_inherited_features_and_indexes_to_system_slot_description();
extern Object alias_slot_name();
extern Object allocate_byte_vector();
extern Object allocate_frame_lookup_structure_vector();
extern Object allocate_managed_long_box();
extern Object allocate_managed_simple_vector();
extern Object assign_class_bit_numbers_and_vectors_to_system_classes();
extern Object assq_function();
extern Object atomic_slot_value_p();
extern Object buffer_size_for_partial_buffer();
extern Object bytes_per_double_float_simple_array();
extern Object car_eq();
extern Object car_equal();
extern Object check_if_superior_classes_are_defined();
extern Object class_description_cons_1();
extern Object class_function();
extern Object classes_intersect_p();
extern Object clear_all_evaluator_slot_info();
extern Object collect_subclasses();
extern Object collect_superclasses();
extern Object collect_user_defined_slot_descriptions_for_defining_class();
extern Object compiled_resource_p_function();
extern Object copy_kb_specific_property_from_global_if_necessary();
extern Object copy_list_using_class_description_conses_1();
extern Object copy_list_using_gensym_conses_1();
extern Object copy_methods();
extern Object copy_slot_descriptions_evaluating_initialization_if_eval_once();
extern Object copy_tree_using_class_description_conses_1();
extern Object decache_cached_class_data();
extern Object define_root_class();
extern Object delete_class_description_element_1();
extern Object delete_frame();
extern Object equivalent_method_table_on_path_p();
extern Object error_message_for_dependent_frame_saving();
extern Object eval_slot_init_forms_of_slot_descriptions_defined_for_class();
extern Object frame_cons_1();
extern Object frame_list_2();
extern Object generate_float_vector();
extern Object get_alias_for_slot_name_if_any();
extern Object get_appropriate_slot_descriptions_cons();
extern Object get_foundation_class_for_class();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_most_specific_direct_superior_for_class();
extern Object get_new_default_slot_description_with_pretty_name();
extern Object get_next_class_bit_number();
extern Object get_property_value_function();
extern Object get_slot_description();
extern Object get_slot_description_of_class_description_function();
extern Object get_slot_description_value();
extern Object get_slot_init_form();
extern Object get_slot_name_for_alias_if_any();
extern Object get_slot_value_function();
extern Object get_slot_value_if_any_function();
extern Object get_slot_value_number_value_or_string_from_slot_constant();
extern Object get_slot_value_or_no_slot_function();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object initialize_classes_visited_byte_vector();
extern Object initialize_method_table_of_class_description();
extern Object initialize_or_update_method_table_for_user_class();
extern Object initialize_or_update_method_tables_of_class_descriptions();
extern Object initialize_slot_description_value();
extern Object install_generic_method_id();
extern Object lookup_global_or_kb_specific_property_value();
extern Object make_and_change_class_description();
extern Object make_class_bit_vector();
extern Object make_class_description();
extern Object make_class_inheritance_path_for_system_defined_class();
extern Object make_full_slot_descriptions_hash_table();
extern Object make_list_of_unaliased_user_overridable_system_slots_for_class();
extern Object make_method_table_for_system_class();
extern Object make_partial_buffer_info();
extern Object make_permanent_list();
extern Object make_slot_constant();
extern Object make_slot_constant_using_phrase_conses();
extern Object make_slot_description();
extern Object make_slot_descriptions_hash_table();
extern Object make_slot_value_float();
extern Object make_slot_value_long();
extern Object make_sparse_slot_descriptions_hash_table();
extern Object make_symbol_properties_hash_table_skip_list_sentinel();
extern Object memq_function();
extern Object merge_slot_descriptions_for_system_defined_class();
extern Object merge_slot_descriptions_for_user_defined_class();
extern Object method_tables_are_equivalent_p();
extern Object most_refined_foundation_class_of_direct_superiors();
extern Object most_specific_superior_that_refines_slot();
extern Object mutate_global_or_kb_specific_property_value();
extern Object mutate_global_property();
extern Object note_change_to_block_1();
extern Object note_change_to_dependent_frame_1();
extern Object phrase_cons();
extern Object propagate_method();
extern Object propagate_methods();
extern Object put_attribute_description_value();
extern Object reclaim_byte_code_body_1();
extern Object reclaim_byte_vector();
extern Object reclaim_class_description_list_1();
extern Object reclaim_class_description_slot_value();
extern Object reclaim_compiled_resource_function();
extern Object reclaim_frame_cons_1();
extern Object reclaim_frame_list_1();
extern Object reclaim_frame_tree_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_initial_slot_value();
extern Object reclaim_lookup_structure_value();
extern Object reclaim_managed_array();
extern Object reclaim_managed_float_array();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object reclaim_managed_simple_long_array_of_length_1();
extern Object reclaim_managed_simple_vector();
extern Object reclaim_method_table_of_class_description();
extern Object reclaim_relation_instances();
extern Object reclaim_slot_constant();
extern Object reclaim_slot_hash_leaves();
extern Object reclaim_slot_value();
extern Object reclaim_slot_value_cons_1();
extern Object reclaim_slot_value_cons_function();
extern Object reclaim_slot_value_list_star_1();
extern Object reclaim_slot_value_tree_1();
extern Object reclaim_slot_value_tree_function();
extern Object reclaim_text_string();
extern Object record_system_variable();
extern Object replenish_lookup_cons_pool();
extern Object scope_cons();
extern Object set_lookup_slot_value_1();
extern Object set_non_savable_lookup_slot_value();
extern Object set_owner_class_of_method_table();
extern Object set_skip_list_entry();
extern Object set_slot_description_value_without_noting();
extern Object set_slot_value_function();
extern Object slot_description_of_most_specific_superior_refining_slot();
extern Object slot_value_cons_1();
extern Object slot_value_cons_function();
extern Object slot_value_equal_p();
extern Object slot_value_float_p_function();
extern Object slot_value_list_2();
extern Object slot_value_long_p_function();
extern Object slot_value_number_p();
extern Object string_eq_w();
extern Object system_class_p();
extern Object system_vector_slots_in_conflict();
extern Object text_string_p();
extern Object unpropagate_methods();
extern Object update_change_timestamps();
extern Object validate_item_or_evaluation_value();
extern Object well_instantiated_or_subclassed_class_p();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Action_button_class_description, Qaction_button_class_description);
extern Object Aliases_for_slot_name_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Any_cached_evaluator_slot_info_p, Qany_cached_evaluator_slot_info_p);
DECLARE_VARIABLE_WITH_SYMBOL(Arrow_button_class_description, Qarrow_button_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Authorized_user_class_description, Qauthorized_user_class_description);
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
extern Object Available_frame_conses_tail_vector;
extern Object Available_frame_conses_vector;
extern Object Available_lookup_conses_tail_vector;
extern Object Available_lookup_conses_vector;
extern Object Available_slot_value_conses_tail_vector;
extern Object Available_slot_value_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backward_chaining_link_class_description, Qbackward_chaining_link_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Block_class_description, Qblock_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Bounding_box_class_description, Qbounding_box_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Button_class_description, Qbutton_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Button_label_class_description, Qbutton_label_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Category_instance_menu_workspace_class_description, Qcategory_instance_menu_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Category_menu_class_description, Qcategory_menu_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Chart, Qchart);
DECLARE_VARIABLE_WITH_SYMBOL(Chart_class_description, Qchart_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Class_bit_numbers_pool, Qclass_bit_numbers_pool);
DECLARE_VARIABLE_WITH_SYMBOL(Class_change_timestamp, Qclass_change_timestamp);
DECLARE_VARIABLE_WITH_SYMBOL(Class_definition_class_description, Qclass_definition_class_description);
extern Object Class_definition_gkbprop;
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Classes_visited_byte_vector, Qclasses_visited_byte_vector);
DECLARE_VARIABLE_WITH_SYMBOL(Connection_class_description, Qconnection_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Connection_definition_class_description, Qconnection_definition_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Connection_post_class_description, Qconnection_post_class_description);
extern Object Constant_queue_marker;
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_block_of_dependent_frame, Qcurrent_block_of_dependent_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_specific_property_list_property_name, Qcurrent_kb_specific_property_list_property_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Data_series, Qdata_series);
DECLARE_VARIABLE_WITH_SYMBOL(Decache_attribute_description_lists_of_interned_lists_function, Qdecache_attribute_description_lists_of_interned_lists_function);
DECLARE_VARIABLE_WITH_SYMBOL(Default_junction_class_description, Qdefault_junction_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Defined_evaluation_value_types, Qdefined_evaluation_value_types);
DECLARE_VARIABLE_WITH_SYMBOL(Definition_class_description, Qdefinition_class_description);
extern Object Definition_state_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Dependent_frame_class_description, Qdependent_frame_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Dial_class_description, Qdial_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Dialog_button_class_description, Qdialog_button_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Digital_clock_class_description, Qdigital_clock_class_description);
extern Object Direct_superior_classes_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Do_not_note_permanent_changes_p, Qdo_not_note_permanent_changes_p);
DECLARE_VARIABLE_WITH_SYMBOL(Edit_box_class_description, Qedit_box_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Entity_class_description, Qentity_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Explanation_table_class_description, Qexplanation_table_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(External_simulation_definition_class_description, Qexternal_simulation_definition_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Float_array_class_description, Qfloat_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Float_list_class_description, Qfloat_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Float_parameter_class_description, Qfloat_parameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Float_variable_class_description, Qfloat_variable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Foreign_function_declaration_class_description, Qforeign_function_declaration_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Format_frame_class_description, Qformat_frame_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Forward_chaining_link_class_description, Qforward_chaining_link_class_description);
extern Object Frame_lookup_structure_vector_allocation_schemes;
DECLARE_VARIABLE_WITH_SYMBOL(Function_definition_class_description, Qfunction_definition_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_array_class_description, Qg2_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_cell_array_cell_class_description, Qg2_cell_array_cell_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_cell_array_class_description, Qg2_cell_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_designation_cell_class_description, Qg2_designation_cell_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_expression_cell_class_description, Qg2_expression_cell_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_list_class_description, Qg2_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_login_class_description, Qg2_login_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_query_cell_class_description, Qg2_query_cell_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_window_class_description, Qg2_window_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Generic_action_button_class_description, Qgeneric_action_button_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Generic_formula_class_description, Qgeneric_formula_class_description);
extern Object Generic_method_lambda_list_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Generic_simulation_formula_class_description, Qgeneric_simulation_formula_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Graph_class_description, Qgraph_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Graph_grid_class_description, Qgraph_grid_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Icon_cell_class_description, Qicon_cell_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Icon_editor_table_info_frame_class_description, Qicon_editor_table_info_frame_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Icon_editor_workspace_class_description, Qicon_editor_workspace_class_description);
extern Object Inferior_classes_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Inspect_command_class_description, Qinspect_command_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Integer_array_class_description, Qinteger_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Integer_list_class_description, Qinteger_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Integer_parameter_class_description, Qinteger_parameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Integer_variable_class_description, Qinteger_variable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Invisible_entity_class_description, Qinvisible_entity_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Item_array_class_description, Qitem_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Item_class_description, Qitem_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Item_list_class_description, Qitem_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Kb_frame_class_description, Qkb_frame_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Kb_workspace_class_description, Qkb_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Kfep_conversion_choice_menu_class_description, Qkfep_conversion_choice_menu_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Language_translation_class_description, Qlanguage_translation_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Last_system_class_bit_number, Qlast_system_class_bit_number);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_user_overridable_system_slots, Qlist_of_user_overridable_system_slots);
DECLARE_VARIABLE_WITH_SYMBOL(Logbook_page_class_description, Qlogbook_page_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Logical_parameter_class_description, Qlogical_parameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Logical_variable_class_description, Qlogical_variable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Long_variable_class_description, Qlong_variable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Loose_end_class_description, Qloose_end_class_description);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Managed_array_unique_marker;
extern Object Managed_float_array_unique_marker;
DECLARE_VARIABLE_WITH_SYMBOL(Marker_for_meter_class_description, Qmarker_for_meter_class_description);
extern Object Maximum_in_place_array_size;
#define Maximum_number_of_generic_methods FIX((SI_Long)57L)
DECLARE_VARIABLE_WITH_SYMBOL(Menu_class_description, Qmenu_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Menu_workspace_class_description, Qmenu_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Message_board_class_description, Qmessage_board_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Message_class_description, Qmessage_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Message_definition_class_description, Qmessage_definition_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Meter_class_description, Qmeter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Method_class_description, Qmethod_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Method_declaration_class_description, Qmethod_declaration_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Model_definition_class_description, Qmodel_definition_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Name_box_class_description, Qname_box_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Next_class_bit_number, Qnext_class_bit_number);
extern Object No_slot;
extern Object No_specific_property_value;
DECLARE_VARIABLE_WITH_SYMBOL(No_value, Qno_value);
DECLARE_VARIABLE_WITH_SYMBOL(Non_kb_workspace_class_description, Qnon_kb_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Object_class_description, Qobject_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Object_definition_class_description, Qobject_definition_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Ok_class_description, Qok_class_description);
extern Object Old_slot_name_assignment_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Page_class_description, Qpage_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Parameter_class_description, Qparameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Plot_class_description, Qplot_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Pointer_for_dial_class_description, Qpointer_for_dial_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Procedure_class_description, Qprocedure_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Procedure_invocation_class_description, Qprocedure_invocation_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Quantitative_parameter_class_description, Qquantitative_parameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Quantitative_variable_class_description, Qquantitative_variable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Quantity_array_class_description, Qquantity_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Quantity_list_class_description, Qquantity_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Question_mark_box_class_description, Qquestion_mark_box_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Readout_table_class_description, Qreadout_table_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Relation_class_description, Qrelation_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Remote_procedure_declaration_class_description, Qremote_procedure_declaration_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Rule_class_description, Qrule_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Ruling_for_dial_class_description, Qruling_for_dial_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Ruling_for_meter_class_description, Qruling_for_meter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Scrap_class_description, Qscrap_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_subtable_class_description, Qsimulation_subtable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Slider_minimum_value_label_class_description, Qslider_minimum_value_label_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Slider_needle_class_description, Qslider_needle_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Slider_readout_class_description, Qslider_readout_class_description);
extern Object Slot_name_assignment_gkbprop;
extern Object Slot_names_for_alias_prop;
extern Object Slot_value_reclaimer_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Statement_class_description, Qstatement_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Subordinate_text_box_class_description, Qsubordinate_text_box_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Symbol_array_class_description, Qsymbol_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Symbol_list_class_description, Qsymbol_list_class_description);
extern Object Symbol_properties_table;
DECLARE_VARIABLE_WITH_SYMBOL(Symbolic_parameter_class_description, Qsymbolic_parameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Symbolic_variable_class_description, Qsymbolic_variable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(System_class_method_tables_processed_qm, Qsystem_class_method_tables_processed_qm);
DECLARE_VARIABLE_WITH_SYMBOL(System_item_class_description, Qsystem_item_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Table_class_description, Qtable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Table_to_map_generic_method_id_to_generic_method_name, Qtable_to_map_generic_method_id_to_generic_method_name);
DECLARE_VARIABLE_WITH_SYMBOL(Tabular_function_class_description, Qtabular_function_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Tabular_function_of_1_arg_class_description, Qtabular_function_of_1_arg_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Temporary_workspace_class_description, Qtemporary_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Text_array_class_description, Qtext_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Text_box_class_description, Qtext_box_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Text_list_class_description, Qtext_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Text_parameter_class_description, Qtext_parameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Text_region_class_description, Qtext_region_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Text_variable_class_description, Qtext_variable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(True_value_update_recipient_class_description, Qtrue_value_update_recipient_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Truth_value_array_class_description, Qtruth_value_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Truth_value_list_class_description, Qtruth_value_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Type_in_box_class_description, Qtype_in_box_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Type_in_text_box_class_description, Qtype_in_text_box_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Units_of_measure_declaration_class_description, Qunits_of_measure_declaration_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(User_menu_choice_class_description, Quser_menu_choice_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(User_overridable_connection_slots, Quser_overridable_connection_slots);
DECLARE_VARIABLE_WITH_SYMBOL(User_overridable_g2_array_slots, Quser_overridable_g2_array_slots);
DECLARE_VARIABLE_WITH_SYMBOL(User_overridable_g2_list_slots, Quser_overridable_g2_list_slots);
DECLARE_VARIABLE_WITH_SYMBOL(User_overridable_message_slots, Quser_overridable_message_slots);
DECLARE_VARIABLE_WITH_SYMBOL(User_overridable_object_slots, Quser_overridable_object_slots);
DECLARE_VARIABLE_WITH_SYMBOL(User_overridable_parameter_slots, Quser_overridable_parameter_slots);
DECLARE_VARIABLE_WITH_SYMBOL(User_overridable_variable_slots, Quser_overridable_variable_slots);
DECLARE_VARIABLE_WITH_SYMBOL(Value_array_class_description, Qvalue_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Value_list_class_description, Qvalue_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_class_description, Qvariable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_or_parameter_class_description, Qvariable_or_parameter_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
DECLARE_VARIABLE_WITH_SYMBOL(Workspace_class_description, Qworkspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Workspace_name_box_class_description, Qworkspace_name_box_class_description);
