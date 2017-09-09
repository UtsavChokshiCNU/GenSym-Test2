/* priqus.h -- Header File for priqus.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qinteger;
extern Object Qsequence;

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
extern Object add_virtual_attribute(Object,Object,Object,Object,Object,Object,Object);
extern Object adjust_managed_array(int,...);
extern Object allocate_evaluation_sequence(Object);
extern Object allocate_managed_array(int,...);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object clear_optimized_constants(void);
extern Object clear_priority_queue(Object);
extern Object copy_managed_float(Object);
extern Object deactivate_for_priority_queue(Object);
extern Object eq_gethash(Object,Object,Object);
extern Object eq_puthash(Object,Object,Object);
extern Object eq_remhash(Object,Object);
extern Object eval_cons_1(Object,Object);
extern Object g2_priority_queue_change_priority(Object,Object,Object);
extern Object g2_priority_queue_clear(Object);
extern Object g2_priority_queue_get_priority(Object,Object);
extern Object g2_priority_queue_is_empty(Object);
extern Object g2_priority_queue_length(Object);
extern Object g2_priority_queue_pop(Object);
extern Object g2_priority_queue_push(Object,Object,Object);
extern Object g2_priority_queue_remove_element(Object,Object);
extern Object g2_priority_queue_top(Object);
extern Object get_and_remove_highest_priority(Object);
extern Object get_g2_priority_queue_number_of_entries(Object);
extern Object get_g2_priority_queue_sequence(Object);
extern Object get_highest_priority(Object);
extern Object get_property_value_function(int,...);
extern Object get_reference_to_item(Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object initial_g2_priority_queue_number_of_entries(Object);
extern Object initial_g2_priority_queue_sequence(Object);
extern Object make_eq_hash_table(Object,Object,Object);
extern Object make_priority_queue_initial_object_array(void);
extern Object make_priority_queue_initial_object_table(void);
extern Object make_priority_queue_initial_priority_array(void);
extern Object mutate_global_property(Object,Object,Object);
extern Object priority_queue_add(Object,Object,Object);
extern Object priority_queue_change_priority(Object,Object,Object);
extern Object priority_queue_rehash(Object);
extern Object priority_queue_remove(Object,Object);
extern Object priority_queue_remove_by_index(Object,Object);
extern Object push_optimized_constant(Object);
extern Object queue_contents(Object);
extern Object rebuild_priority_queue(Object,Object);
extern Object reclaim_eq_hash_table(Object);
extern Object reclaim_eval_cons_1(Object);
extern Object reclaim_eval_list_1(Object);
extern Object reclaim_evaluation_item_reference(Object);
extern Object reclaim_managed_array(Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object reclaim_priority_queue_object_array_value(Object,Object);
extern Object reclaim_priority_queue_object_table_value(Object,Object);
extern Object reclaim_priority_queue_priority_array_value(Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object set_property_value_function(Object,Object,Object);

#else

extern Object add_class_to_environment();
extern Object add_virtual_attribute();
extern Object adjust_managed_array();
extern Object allocate_evaluation_sequence();
extern Object allocate_managed_array();
extern Object check_if_superior_classes_are_defined();
extern Object clear_optimized_constants();
extern Object clear_priority_queue();
extern Object copy_managed_float();
extern Object deactivate_for_priority_queue();
extern Object eq_gethash();
extern Object eq_puthash();
extern Object eq_remhash();
extern Object eval_cons_1();
extern Object g2_priority_queue_change_priority();
extern Object g2_priority_queue_clear();
extern Object g2_priority_queue_get_priority();
extern Object g2_priority_queue_is_empty();
extern Object g2_priority_queue_length();
extern Object g2_priority_queue_pop();
extern Object g2_priority_queue_push();
extern Object g2_priority_queue_remove_element();
extern Object g2_priority_queue_top();
extern Object get_and_remove_highest_priority();
extern Object get_g2_priority_queue_number_of_entries();
extern Object get_g2_priority_queue_sequence();
extern Object get_highest_priority();
extern Object get_property_value_function();
extern Object get_reference_to_item();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object initial_g2_priority_queue_number_of_entries();
extern Object initial_g2_priority_queue_sequence();
extern Object make_eq_hash_table();
extern Object make_priority_queue_initial_object_array();
extern Object make_priority_queue_initial_object_table();
extern Object make_priority_queue_initial_priority_array();
extern Object mutate_global_property();
extern Object priority_queue_add();
extern Object priority_queue_change_priority();
extern Object priority_queue_rehash();
extern Object priority_queue_remove();
extern Object priority_queue_remove_by_index();
extern Object push_optimized_constant();
extern Object queue_contents();
extern Object rebuild_priority_queue();
extern Object reclaim_eq_hash_table();
extern Object reclaim_eval_cons_1();
extern Object reclaim_eval_list_1();
extern Object reclaim_evaluation_item_reference();
extern Object reclaim_managed_array();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object reclaim_priority_queue_object_array_value();
extern Object reclaim_priority_queue_object_table_value();
extern Object reclaim_priority_queue_priority_array_value();
extern Object regenerate_optimized_constant();
extern Object set_property_value_function();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(All_virtual_attributes, Qall_virtual_attributes);
DECLARE_VARIABLE_WITH_SYMBOL(Current_index, Qcurrent_index);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
extern Object Priority_queue_initial_size;
