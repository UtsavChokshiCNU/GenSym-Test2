/* trvs.h -- Header File for trvs.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qeq;

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

extern Object add_as_inferior_block(Object,Object);
extern Object add_as_inferior_block_1(Object,Object);
extern Object block_referenced_in_current_save_p(Object);
extern Object block_written_in_current_save_p(Object);
extern Object check_for_specialized_method(Object,Object,Object,Object,Object,Object);
extern Object collect_attribute_if_savable(Object);
extern Object collect_definition_for_saving(Object);
extern Object collect_subclasses(Object);
extern Object constant_queue_next(Object,Object);
extern Object copy_list_using_journal_conses_1(Object);
extern Object decrement_frame_reference_balance(Object,Object);
extern Object definition_is_dependent_on_uncollected_definitions_p(Object);
extern Object eval_cons_1(Object,Object);
extern Object funcall_function_to_inferior_blocks(Object,Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_module_block_is_in(Object);
extern Object get_slot_represented_by_text_cell_if_any(Object);
extern Object get_specific_method(Object,Object,Object,Object,Object,Object);
extern Object has_slot_values_to_save_p(int,...);
extern Object instantiated_class_p(Object);
extern Object journal_cons_1(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_symbol_properties_hash_table_skip_list_sentinel(Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object permanence_of_block_represented(Object);
extern Object reclaim_journal_list_1(Object);
extern Object remove_as_inferior_block(Object,Object);
extern Object remove_as_inferior_block_1(Object,Object);
extern Object remove_block_from_module(Object);
extern Object replenish_lookup_cons_pool(void);
extern Object savable_definition_p(Object);
extern Object scope_cons(Object,Object);
extern Object set_block_written_in_current_save(Object,Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object system_table_installed_p(Object);
extern Object traverse_block_for_saving(Object);
extern Object traverse_definitions_of_kb_for_saving(void);
extern Object traverse_kb_for_saving(Object);
extern Object traverse_system_frames_of_kb_for_saving(void);
extern Object traverse_top_level_workspaces_of_kb_for_saving(void);
extern Object traverse_transient_class_instances_of_kb_for_saving(Object);
extern Object traverse_transient_items_of_kb_for_saving(void);
extern Object within_module_being_saved_p(Object);

#else

extern Object add_as_inferior_block();
extern Object add_as_inferior_block_1();
extern Object block_referenced_in_current_save_p();
extern Object block_written_in_current_save_p();
extern Object check_for_specialized_method();
extern Object collect_attribute_if_savable();
extern Object collect_definition_for_saving();
extern Object collect_subclasses();
extern Object constant_queue_next();
extern Object copy_list_using_journal_conses_1();
extern Object decrement_frame_reference_balance();
extern Object definition_is_dependent_on_uncollected_definitions_p();
extern Object eval_cons_1();
extern Object funcall_function_to_inferior_blocks();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_module_block_is_in();
extern Object get_slot_represented_by_text_cell_if_any();
extern Object get_specific_method();
extern Object has_slot_values_to_save_p();
extern Object instantiated_class_p();
extern Object journal_cons_1();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_symbol_properties_hash_table_skip_list_sentinel();
extern Object note_change_to_block_1();
extern Object permanence_of_block_represented();
extern Object reclaim_journal_list_1();
extern Object remove_as_inferior_block();
extern Object remove_as_inferior_block_1();
extern Object remove_block_from_module();
extern Object replenish_lookup_cons_pool();
extern Object savable_definition_p();
extern Object scope_cons();
extern Object set_block_written_in_current_save();
extern Object set_skip_list_entry();
extern Object system_table_installed_p();
extern Object traverse_block_for_saving();
extern Object traverse_definitions_of_kb_for_saving();
extern Object traverse_kb_for_saving();
extern Object traverse_system_frames_of_kb_for_saving();
extern Object traverse_top_level_workspaces_of_kb_for_saving();
extern Object traverse_transient_class_instances_of_kb_for_saving();
extern Object traverse_transient_items_of_kb_for_saving();
extern Object within_module_being_saved_p();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Attributes_collector, Qattributes_collector);
DECLARE_VARIABLE_WITH_SYMBOL(Attributes_collector_tail, Qattributes_collector_tail);
extern Object Available_lookup_conses_tail_vector;
extern Object Available_lookup_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Blocks_with_specialized_method_qm, Qblocks_with_specialized_method_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Class_definition_class_description, Qclass_definition_class_description);
extern Object Class_definition_gkbprop;
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_save, Qcurrent_kb_save);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_specific_property_list_property_name, Qcurrent_kb_specific_property_list_property_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_saving_context, Qcurrent_saving_context);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Definitions_for_saving, Qdefinitions_for_saving);
DECLARE_VARIABLE_WITH_SYMBOL(Entity_class_description, Qentity_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Generic_action_button_class_description, Qgeneric_action_button_class_description);
extern Object Inferior_classes_gkbprop;
extern Object Instances_specific_to_this_class_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Interesting_blocks_found_in_search, Qinteresting_blocks_found_in_search);
DECLARE_VARIABLE_WITH_SYMBOL(Kb_workspace_class_description, Qkb_workspace_class_description);
extern Object No_specific_property_value;
DECLARE_VARIABLE_WITH_SYMBOL(No_value, Qno_value);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Remove_as_inferior_block_1, Qremove_as_inferior_block_1);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_subtable_class_description, Qsimulation_subtable_class_description);
extern Object Symbol_properties_table;
DECLARE_VARIABLE_WITH_SYMBOL(Table_class_description, Qtable_class_description);
extern Object Top_level_kb_elements_for_saving;
DECLARE_VARIABLE_WITH_SYMBOL(User_menu_choice_class_description, Quser_menu_choice_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_class_description, Qvariable_class_description);
