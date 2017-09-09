/* pcnst2.h -- Header File for pcnst2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qassert;

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

extern Object compiler_error(int,...);
extern Object emit_add_to_action_cache_byte_codes(Object,Object,Object);
extern Object emit_begin_activity_byte_codes(Object,Object,Object);
extern Object emit_branch_long_byte_codes(Object,Object);
extern Object emit_branch_long_if_known_byte_codes(Object,Object);
extern Object emit_branch_long_if_not_false_byte_codes(Object,Object);
extern Object emit_branch_long_if_not_true_byte_codes(Object,Object);
extern Object emit_branch_long_if_true_byte_codes(Object,Object);
extern Object emit_call_code_body_byte_codes(Object,Object,Object);
extern Object emit_call_scheduled_code_body_byte_codes(Object,Object,Object);
extern Object emit_case_dispatch_byte_codes(Object,Object,Object,Object,Object);
extern Object emit_close_iteration_byte_codes(Object,Object);
extern Object emit_funcall_instruction_byte_codes(int,...);
extern Object emit_jump_byte_codes(Object,Object,Object);
extern Object emit_long_code_constant_to_stream(Object,Object);
extern Object emit_open_role_iteration_byte_codes(Object,Object,Object,Object);
extern Object emit_open_role_iteration_no_domain_byte_codes(Object,Object,Object);
extern Object emit_pop_into_surrounding_local_var_byte_codes(Object,Object);
extern Object emit_pop_values_byte_codes(Object,Object);
extern Object emit_push_constant_byte_codes(Object,Object);
extern Object emit_push_from_surrounding_local_var_byte_codes(Object,Object);
extern Object emit_push_nones_byte_codes(Object,Object);
extern Object emit_push_value_or_none_from_surrounding_local_var_byte_codes(Object,Object);
extern Object emit_restore_from_action_cache_or_branch_byte_codes(Object,Object,Object,Object);
extern Object emit_return_values_byte_codes(Object,Object);
extern Object emit_serve_next_iteration_value_byte_codes(Object,Object,Object);
extern Object emit_stack_node_tree(Object,Object);
extern Object emit_type_check_byte_codes(Object,Object);
extern Object generate_new_goto_tag(void);
extern Object mutate_global_property(Object,Object,Object);
extern Object op_code_for_stack_instruction(Object);
extern Object phrase_cons(Object,Object);
extern Object phrase_cons_with_args_reversed(Object,Object);
extern Object phrase_list_3(Object,Object,Object);
extern Object record_free_reference(Object,Object);
extern Object record_free_references_of_role(int,...);
extern Object register_tag_in_byte_code_stream(int,...);
extern Object type_specification_subtype_p(Object,Object);
extern Object write_byte_code_to_stream(Object,Object);

#else

extern Object compiler_error();
extern Object emit_add_to_action_cache_byte_codes();
extern Object emit_begin_activity_byte_codes();
extern Object emit_branch_long_byte_codes();
extern Object emit_branch_long_if_known_byte_codes();
extern Object emit_branch_long_if_not_false_byte_codes();
extern Object emit_branch_long_if_not_true_byte_codes();
extern Object emit_branch_long_if_true_byte_codes();
extern Object emit_call_code_body_byte_codes();
extern Object emit_call_scheduled_code_body_byte_codes();
extern Object emit_case_dispatch_byte_codes();
extern Object emit_close_iteration_byte_codes();
extern Object emit_funcall_instruction_byte_codes();
extern Object emit_jump_byte_codes();
extern Object emit_long_code_constant_to_stream();
extern Object emit_open_role_iteration_byte_codes();
extern Object emit_open_role_iteration_no_domain_byte_codes();
extern Object emit_pop_into_surrounding_local_var_byte_codes();
extern Object emit_pop_values_byte_codes();
extern Object emit_push_constant_byte_codes();
extern Object emit_push_from_surrounding_local_var_byte_codes();
extern Object emit_push_nones_byte_codes();
extern Object emit_push_value_or_none_from_surrounding_local_var_byte_codes();
extern Object emit_restore_from_action_cache_or_branch_byte_codes();
extern Object emit_return_values_byte_codes();
extern Object emit_serve_next_iteration_value_byte_codes();
extern Object emit_stack_node_tree();
extern Object emit_type_check_byte_codes();
extern Object generate_new_goto_tag();
extern Object mutate_global_property();
extern Object op_code_for_stack_instruction();
extern Object phrase_cons();
extern Object phrase_cons_with_args_reversed();
extern Object phrase_list_3();
extern Object record_free_reference();
extern Object record_free_references_of_role();
extern Object register_tag_in_byte_code_stream();
extern Object type_specification_subtype_p();
extern Object write_byte_code_to_stream();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Current_return_values_position, Qcurrent_return_values_position);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
