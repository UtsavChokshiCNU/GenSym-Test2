/* trvs.h -- Header File for trvs.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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
extern Object copy_list_using_gensym_conses_1(Object);
extern Object decrement_frame_reference_balance(Object,Object);
extern Object definition_is_dependent_on_uncollected_definitions_p(Object);
extern Object funcall_function_to_inferior_blocks(Object,Object);
extern Object gensym_cons_1(Object,Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_module_block_is_in(Object);
extern Object get_slot_represented_by_text_cell_if_any(Object);
extern Object get_specific_method(Object,Object,Object,Object,Object,Object);
extern Object has_slot_values_to_save_p(int,...);
extern Object instantiated_class_p(Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object permanence_of_block_represented(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object remove_as_inferior_block(Object,Object);
extern Object remove_as_inferior_block_1(Object,Object);
extern Object remove_block_from_module(Object);
extern Object replenish_gensym_cons_pool(void);
extern Object savable_definition_p(Object);
extern Object scope_cons(Object,Object);
extern Object set_balanced_binary_tree_entry(Object,Object,Object,Object,Object,Object,Object);
extern Object set_block_written_in_current_save(Object,Object);
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
extern Object copy_list_using_gensym_conses_1();
extern Object decrement_frame_reference_balance();
extern Object definition_is_dependent_on_uncollected_definitions_p();
extern Object funcall_function_to_inferior_blocks();
extern Object gensym_cons_1();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_module_block_is_in();
extern Object get_slot_represented_by_text_cell_if_any();
extern Object get_specific_method();
extern Object has_slot_values_to_save_p();
extern Object instantiated_class_p();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object note_change_to_block_1();
extern Object permanence_of_block_represented();
extern Object reclaim_gensym_list_1();
extern Object remove_as_inferior_block();
extern Object remove_as_inferior_block_1();
extern Object remove_block_from_module();
extern Object replenish_gensym_cons_pool();
extern Object savable_definition_p();
extern Object scope_cons();
extern Object set_balanced_binary_tree_entry();
extern Object set_block_written_in_current_save();
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
extern Object Attributes_collector;
extern Object Attributes_collector_tail;
extern Object Available_gensym_conses;
extern Object Blocks_with_specialized_method_qm;
extern Object Class_definition_class_description;
extern Object Class_definition_gkbprop;
extern Object Class_description_gkbprop;
extern Object Current_kb_save;
extern Object Current_kb_specific_property_list_property_name;
extern Object Current_saving_context;
extern Object Definitions_for_saving;
extern Object Entity_class_description;
extern Object Generic_action_button_class_description;
extern Object Inferior_classes_gkbprop;
extern Object Instances_specific_to_this_class_kbprop;
extern Object Interesting_blocks_found_in_search;
extern Object Kb_workspace_class_description;
extern Object No_specific_property_value;
extern Object No_value;
extern Object Noting_changes_to_kb_p;
extern Object Remove_as_inferior_block_1;
extern Object Scope_conses;
extern Object Simulation_subtable_class_description;
extern Object Symbol_properties_table;
extern Object Table_class_description;
extern Object Top_level_kb_elements_for_saving;
extern Object User_menu_choice_class_description;
extern Object Variable_class_description;
