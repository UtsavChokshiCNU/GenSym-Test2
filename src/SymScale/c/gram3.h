/* gram3.h -- Header File for gram3.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qnum_ne;
extern Object Qnum_lt;
extern Object Qnum_le;
extern Object Qnum_eq;
extern Object Qnum_gt;
extern Object Qnum_ge;
extern Object Qfirst;
extern Object Qgentemp;
extern Object Qnot;
extern Object Qprint;
extern Object Qquote;
extern Object Qsecond;
extern Object Qset;
extern Object Qthe;

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

extern Object activate_g2_cell_array(Object);
extern Object add_generic_rule_grammar(void);
extern Object add_grammar_rules_function(Object);
extern Object add_layering_preservation_to_show_details(Object);
extern Object button_frame_status(Object);
extern Object change_slot_value(int,...);
extern Object clear_optimized_constants(void);
extern Object compile_expression(Object,Object,Object);
extern Object compile_unique_logical_expression_for_slot(int,...);
extern Object compile_user_menu_choice_expression_for_slot(int,...);
extern Object compile_user_menu_choice_expression_initialization_for_slot(int,...);
extern Object convert_history_interval(Object);
extern Object deactivate_g2_cell_array(Object);
extern Object do_deferred_updates_to_representations_in_tables(void);
extern Object enter_part_description(Object);
extern Object extend_action_grammar(void);
extern Object get_default_computation_style_of_class(void);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object make_empty_expression_cell(Object);
extern Object make_frame(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object phrase_cons(Object,Object);
extern Object phrase_list_3(Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object reclaim_stack_change_tree_1(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object register_expression_cell_during_compilation(int,...);
extern Object reject_if_float_interval(Object);
extern Object replenish_part_stack_cons_pool(void);
extern Object replenish_stack_change_cons_pool(void);
extern Object stack_change_cons_1(Object,Object);
extern Object stack_change_list_2(Object,Object);
extern Object update_all_representations_of_slot(Object,Object,Object,Object);
extern Object update_frame_name_references(Object);
extern Object update_frame_status(Object,Object,Object);

#else

extern Object activate_g2_cell_array();
extern Object add_generic_rule_grammar();
extern Object add_grammar_rules_function();
extern Object add_layering_preservation_to_show_details();
extern Object button_frame_status();
extern Object change_slot_value();
extern Object clear_optimized_constants();
extern Object compile_expression();
extern Object compile_unique_logical_expression_for_slot();
extern Object compile_user_menu_choice_expression_for_slot();
extern Object compile_user_menu_choice_expression_initialization_for_slot();
extern Object convert_history_interval();
extern Object deactivate_g2_cell_array();
extern Object do_deferred_updates_to_representations_in_tables();
extern Object enter_part_description();
extern Object extend_action_grammar();
extern Object get_default_computation_style_of_class();
extern Object get_lookup_slot_value_given_default();
extern Object get_slot_description_of_class_description_function();
extern Object make_empty_expression_cell();
extern Object make_frame();
extern Object mutate_global_property();
extern Object phrase_cons();
extern Object phrase_list_3();
extern Object push_optimized_constant();
extern Object reclaim_stack_change_tree_1();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object register_expression_cell_during_compilation();
extern Object reject_if_float_interval();
extern Object replenish_part_stack_cons_pool();
extern Object replenish_stack_change_cons_pool();
extern Object stack_change_cons_1();
extern Object stack_change_list_2();
extern Object update_all_representations_of_slot();
extern Object update_frame_name_references();
extern Object update_frame_status();

#endif

/* variables/constants */
extern Object Available_part_stack_conses_tail_vector;
extern Object Available_part_stack_conses_vector;
extern Object Available_stack_change_conses_tail_vector;
extern Object Available_stack_change_conses_vector;
extern Object Bad_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Current_block_of_dependent_frame, Qcurrent_block_of_dependent_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_component_particulars, Qcurrent_computation_component_particulars);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_style, Qcurrent_computation_style);
DECLARE_VARIABLE_WITH_SYMBOL(Current_part_description, Qcurrent_part_description);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
extern Object Evaluation_true_value;
DECLARE_VARIABLE_WITH_SYMBOL(Fake_attribute, Qfake_attribute);
DECLARE_VARIABLE_WITH_SYMBOL(Inside_breakpoint_p, Qinside_breakpoint_p);
DECLARE_VARIABLE_WITH_SYMBOL(Maintain_stack_of_current_part_descriptions_p, Qmaintain_stack_of_current_part_descriptions_p);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
DECLARE_VARIABLE_WITH_SYMBOL(Part_feature_exit_methods, Qpart_feature_exit_methods);
DECLARE_VARIABLE_WITH_SYMBOL(Part_feature_recall_stack, Qpart_feature_recall_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Stack_of_current_part_descriptions, Qstack_of_current_part_descriptions);
DECLARE_VARIABLE_WITH_SYMBOL(Stack_of_slot_value_changes, Qstack_of_slot_value_changes);
DECLARE_VARIABLE_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm, Qsuppress_updating_of_slot_value_representations_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Suppress_use_of_stack_of_slot_value_changes_p, Qsuppress_use_of_stack_of_slot_value_changes_p);
DECLARE_VARIABLE_WITH_SYMBOL(The_only_dynamic_computation_style, Qthe_only_dynamic_computation_style);
