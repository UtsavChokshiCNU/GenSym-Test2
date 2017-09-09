/* stktls.h -- Header File for stktls.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;
extern Object Qunsigned_byte;

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

extern Object abort_to_break_deadlock(Object);
extern Object activity_and_text_position_information(Object);
extern Object add_text_to_string_with_align(Object,Object,Object,Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_evaluation_sequence(Object);
extern Object break_one_deadlock(Object);
extern Object byte_code_body_contains_backward_branch_p(Object,Object);
extern Object byte_code_body_contains_instruction_that_should_not_be_compiled_p(Object,Object);
extern Object byte_code_body_is_too_long_to_compile_p(Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object calling_procedure_invocation(Object);
extern Object calling_process_of_g2gl_call_invocation(Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object check_stack_evaluator_arguments(Object,Object,Object,Object);
extern Object check_stack_evaluator_result(Object,Object,Object,Object);
extern Object clear_computation_context_variables(void);
extern Object collect_subclasses(Object);
extern Object compiler_bug(int,...);
extern Object computation_instance_byte_code_body(Object);
extern Object concatenate_text_strings(Object,Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object denote_component_of_block(int,...);
extern Object detect_and_break_deadlocks(void);
extern Object detect_and_break_deadlocks_for_ui(void);
extern Object detect_deadlocks(Object);
extern Object detect_deadlocks_for_ui(void);
extern Object emit_long_code_constant_to_stream(Object,Object);
extern Object emit_relative_code_constant_to_stream(Object,Object);
extern Object enter_or_reclaim_computation_instance_context(Object);
extern Object entry_point_number(Object,Object);
extern Object eq_gethash(Object,Object,Object);
extern Object eq_puthash(Object,Object,Object);
extern Object eval_cons_1(Object,Object);
extern Object execute_computation_instance(Object);
extern Object extend_current_gensym_string(int,...);
extern Object find_cycle_in_invocation_entry_list(Object);
extern Object find_cycle_or_extend_path_in_invocation_entry_list(Object);
extern Object find_error_handler_for_code_body_invocation(Object,Object);
extern Object float_contagion_stack_operator_p(Object);
extern Object future_task_schedule_2(Object);
extern Object g2_detect_and_break_deadlocks(void);
extern Object g2_detect_deadlocks(void);
extern Object g2gl_call_invocation_p_function(Object);
extern Object generate_standard_error_message(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object get_call_sequence(Object,Object,Object,Object);
extern Object get_computation_instance_for_block(Object,Object,Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object handle_extend_current_text_string_error(void);
extern Object in_order_p(Object);
extern Object instruction_address_for_tag(Object,Object);
extern Object instruction_description_for_op_code(Object);
extern Object instruction_should_not_be_compiled(Object);
extern Object long_code_constant_in_byte_vector(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_and_register_funcalled_instruction_description(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_and_register_stack_instruction_description(Object,Object,Object,Object,Object,Object,Object);
extern Object make_eq_hash_table(Object,Object,Object);
extern Object make_error_text(Object,Object);
extern Object make_evaluator_description(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_global_stack(void);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_stringw_function(Object,Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object need_to_stack_eval_to_get_initial_value_for_state_variable_qm(Object,Object);
extern Object notify_user(int,...);
extern Object notify_user_at_console(int,...);
extern Object op_code_for_stack_instruction(Object);
extern Object phrase_cons(Object,Object);
extern Object pprint_functional_evaluator(Object,Object,Object,Object,Object,Object);
extern Object pprint_infix_evaluator(Object,Object,Object,Object,Object,Object);
extern Object pprint_stack_instruction(Object,Object,Object,Object,Object);
extern Object pprinter_for_funcalled_instruction_p(Object);
extern Object pprinter_for_stack_instruction_p(Object,Object);
extern Object proc_cons_1(Object,Object);
extern Object proc_list_3(Object,Object,Object);
extern Object queue_invocation_for_lock_if_necessary(Object);
extern Object raw_stack_error_named_error(Object,Object);
extern Object read_byte_code_stream_vector(Object);
extern Object reclaim_eq_hash_table(Object);
extern Object reclaim_if_evaluation_value_1(Object);
extern Object reclaim_list_of_block_snapshots(Object);
extern Object reclaim_proc_list_1(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_top_of_stack(void);
extern Object reclaim_wide_string(Object);
extern Object record_block_for_tformat(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object register_dummy_evaluator(Object);
extern Object register_funcalled_evaluator(Object,Object,Object);
extern Object register_in_line_evaluator(Object,Object);
extern Object relative_code_constant_in_byte_vector(Object,Object);
extern Object relative_code_constant_p(Object);
extern Object resolve_procedure_byte_code_addresses(int,...);
extern Object schedule_computation_instance_execution_for_breakpoint(Object);
extern Object scope_cons(Object,Object);
extern Object set_deadlock_detection_frequency(Object,Object);
extern Object setf_long_code_constant(Object,Object,Object);
extern Object setf_relative_code_constant_in_byte_vector(Object,Object,Object);
extern Object signal_code_body_invocation_error(int,...);
extern Object stack_eval_for_execute_computation_instance(Object,Object,Object,Object,Object,Object);
extern Object stack_instruction_description_p(Object);
extern Object state_variable_p(Object);
extern Object tformat(int,...);
extern Object tformat_stack_error_text_string(int,...);
extern Object true_base_of_procedure_invocation_stack_p(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_character(Object);
extern Object twrite_general_string(Object);
extern Object twrite_positive_fixnum(Object);
extern Object twrite_right_justified_unsigned_short(Object,Object);
extern Object twrite_symbol(int,...);
extern Object twrite_wide_character(Object);
extern Object type_specification_type_p(Object,Object);
extern Object waiting_for_do_in_parallel_until_one_completes(Object);
extern Object within_stack_eval_p(void);
extern Object write_activity_given_index(Object,Object,Object);
extern Object write_activity_given_pc_and_byte_code_body(Object,Object);
extern Object write_byte_code_body(Object,Object);
extern Object write_byte_code_body_free_references(Object);
extern Object write_byte_code_to_stream(Object,Object);
extern Object write_called_function_and_arguments(int,...);
extern Object write_code_body_environment(Object,Object);
extern Object write_code_body_invocation_environment(Object,Object,Object);
extern Object write_computation_context(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object write_computation_context_to_console(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object write_procedure_invocation_instance_from_slot(Object,Object);
extern Object write_rule_purpose(Object);
extern Object write_stack_argument(Object,Object,Object,Object);
extern Object write_stack_contents(int,...);
extern Object write_stack_evaluator_backtrace(Object,Object,Object,Object,Object,Object);
extern Object write_stack_evaluator_top_frame(Object,Object,Object,Object,Object);
extern Object write_stack_instruction(Object,Object,Object);
extern Object write_stored_value(Object);

#else

extern Object abort_to_break_deadlock();
extern Object activity_and_text_position_information();
extern Object add_text_to_string_with_align();
extern Object allocate_byte_vector_16();
extern Object allocate_evaluation_sequence();
extern Object break_one_deadlock();
extern Object byte_code_body_contains_backward_branch_p();
extern Object byte_code_body_contains_instruction_that_should_not_be_compiled_p();
extern Object byte_code_body_is_too_long_to_compile_p();
extern Object c_native_clock_ticks_or_cache();
extern Object calling_procedure_invocation();
extern Object calling_process_of_g2gl_call_invocation();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object check_stack_evaluator_arguments();
extern Object check_stack_evaluator_result();
extern Object clear_computation_context_variables();
extern Object collect_subclasses();
extern Object compiler_bug();
extern Object computation_instance_byte_code_body();
extern Object concatenate_text_strings();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object denote_component_of_block();
extern Object detect_and_break_deadlocks();
extern Object detect_and_break_deadlocks_for_ui();
extern Object detect_deadlocks();
extern Object detect_deadlocks_for_ui();
extern Object emit_long_code_constant_to_stream();
extern Object emit_relative_code_constant_to_stream();
extern Object enter_or_reclaim_computation_instance_context();
extern Object entry_point_number();
extern Object eq_gethash();
extern Object eq_puthash();
extern Object eval_cons_1();
extern Object execute_computation_instance();
extern Object extend_current_gensym_string();
extern Object find_cycle_in_invocation_entry_list();
extern Object find_cycle_or_extend_path_in_invocation_entry_list();
extern Object find_error_handler_for_code_body_invocation();
extern Object float_contagion_stack_operator_p();
extern Object future_task_schedule_2();
extern Object g2_detect_and_break_deadlocks();
extern Object g2_detect_deadlocks();
extern Object g2gl_call_invocation_p_function();
extern Object generate_standard_error_message();
extern Object get_call_sequence();
extern Object get_computation_instance_for_block();
extern Object getfq_function_no_default();
extern Object handle_extend_current_text_string_error();
extern Object in_order_p();
extern Object instruction_address_for_tag();
extern Object instruction_description_for_op_code();
extern Object instruction_should_not_be_compiled();
extern Object long_code_constant_in_byte_vector();
extern Object lookup_kb_specific_property_value();
extern Object make_and_register_funcalled_instruction_description();
extern Object make_and_register_stack_instruction_description();
extern Object make_eq_hash_table();
extern Object make_error_text();
extern Object make_evaluator_description();
extern Object make_global_stack();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_stringw_function();
extern Object memq_function();
extern Object mutate_global_property();
extern Object need_to_stack_eval_to_get_initial_value_for_state_variable_qm();
extern Object notify_user();
extern Object notify_user_at_console();
extern Object op_code_for_stack_instruction();
extern Object phrase_cons();
extern Object pprint_functional_evaluator();
extern Object pprint_infix_evaluator();
extern Object pprint_stack_instruction();
extern Object pprinter_for_funcalled_instruction_p();
extern Object pprinter_for_stack_instruction_p();
extern Object proc_cons_1();
extern Object proc_list_3();
extern Object queue_invocation_for_lock_if_necessary();
extern Object raw_stack_error_named_error();
extern Object read_byte_code_stream_vector();
extern Object reclaim_eq_hash_table();
extern Object reclaim_if_evaluation_value_1();
extern Object reclaim_list_of_block_snapshots();
extern Object reclaim_proc_list_1();
extern Object reclaim_schedule_task_args();
extern Object reclaim_text_string();
extern Object reclaim_top_of_stack();
extern Object reclaim_wide_string();
extern Object record_block_for_tformat();
extern Object record_system_variable();
extern Object register_dummy_evaluator();
extern Object register_funcalled_evaluator();
extern Object register_in_line_evaluator();
extern Object relative_code_constant_in_byte_vector();
extern Object relative_code_constant_p();
extern Object resolve_procedure_byte_code_addresses();
extern Object schedule_computation_instance_execution_for_breakpoint();
extern Object scope_cons();
extern Object set_deadlock_detection_frequency();
extern Object setf_long_code_constant();
extern Object setf_relative_code_constant_in_byte_vector();
extern Object signal_code_body_invocation_error();
extern Object stack_eval_for_execute_computation_instance();
extern Object stack_instruction_description_p();
extern Object state_variable_p();
extern Object tformat();
extern Object tformat_stack_error_text_string();
extern Object true_base_of_procedure_invocation_stack_p();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_character();
extern Object twrite_general_string();
extern Object twrite_positive_fixnum();
extern Object twrite_right_justified_unsigned_short();
extern Object twrite_symbol();
extern Object twrite_wide_character();
extern Object type_specification_type_p();
extern Object waiting_for_do_in_parallel_until_one_completes();
extern Object within_stack_eval_p();
extern Object write_activity_given_index();
extern Object write_activity_given_pc_and_byte_code_body();
extern Object write_byte_code_body();
extern Object write_byte_code_body_free_references();
extern Object write_byte_code_to_stream();
extern Object write_called_function_and_arguments();
extern Object write_code_body_environment();
extern Object write_code_body_invocation_environment();
extern Object write_computation_context();
extern Object write_computation_context_to_console();
extern Object write_procedure_invocation_instance_from_slot();
extern Object write_rule_purpose();
extern Object write_stack_argument();
extern Object write_stack_contents();
extern Object write_stack_evaluator_backtrace();
extern Object write_stack_evaluator_top_frame();
extern Object write_stack_instruction();
extern Object write_stored_value();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Automatic_deadlock_detection_frequency, Qautomatic_deadlock_detection_frequency);
DECLARE_VARIABLE_WITH_SYMBOL(Automatic_deadlock_detection_task, Qautomatic_deadlock_detection_task);
extern Object Available_proc_conses_tail_vector;
extern Object Available_proc_conses_vector;
extern Object Backtrace_depth_limit;
#define Base_in_line_evaluator_number FIX((SI_Long)150L)
extern Object Byte_code_resolver_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Cached_byte_code_body, Qcached_byte_code_body);
DECLARE_VARIABLE_WITH_SYMBOL(Cached_fixnum_start_time, Qcached_fixnum_start_time);
DECLARE_VARIABLE_WITH_SYMBOL(Cached_stack_frame_base, Qcached_stack_frame_base);
DECLARE_VARIABLE_WITH_SYMBOL(Cached_stack_program_counter, Qcached_stack_program_counter);
DECLARE_VARIABLE_WITH_SYMBOL(Cached_top_of_stack, Qcached_top_of_stack);
extern Object Chain_of_available_schedule_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Code_body_entries_in_compilation, Qcode_body_entries_in_compilation);
DECLARE_VARIABLE_WITH_SYMBOL(Current_code_body_entry, Qcurrent_code_body_entry);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_activity, Qcurrent_computation_activity);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_instance, Qcurrent_computation_instance);
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_schedule_task, Qcurrent_schedule_task);
DECLARE_VARIABLE_WITH_SYMBOL(Current_simulation_runtime_structure, Qcurrent_simulation_runtime_structure);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Disassemble_enabled_qm, Qdisassemble_enabled_qm);
#define Dispatch_instruction_number FIX((SI_Long)255L)
DECLARE_VARIABLE_WITH_SYMBOL(Dummy_evaluators_list, Qdummy_evaluators_list);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Float_contagion_stack_operators, Qfloat_contagion_stack_operators);
DECLARE_VARIABLE_WITH_SYMBOL(Free_global_stacks, Qfree_global_stacks);
#define Funcall_eval_type_0_arg FIX((SI_Long)0L)
#define Funcall_eval_type_1_arg FIX((SI_Long)1L)
#define Funcall_eval_type_2_arg FIX((SI_Long)2L)
#define Funcall_eval_type_3_arg FIX((SI_Long)3L)
#define Funcall_eval_type_4_arg FIX((SI_Long)4L)
#define Funcall_eval_type_5_arg FIX((SI_Long)5L)
#define Funcall_eval_type_6_arg FIX((SI_Long)6L)
#define Funcall_eval_type_7_arg FIX((SI_Long)7L)
#define Funcall_eval_type_8_arg FIX((SI_Long)8L)
DECLARE_VARIABLE_WITH_SYMBOL(Funcalled_evaluator_array, Qfuncalled_evaluator_array);
DECLARE_VARIABLE_WITH_SYMBOL(Funcalled_evaluator_dispatch_type, Qfuncalled_evaluator_dispatch_type);
DECLARE_VARIABLE_WITH_SYMBOL(Funcalled_evaluator_functions, Qfuncalled_evaluator_functions);
extern Object Funcalled_instruction_description_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Funcalled_instruction_functions, Qfuncalled_instruction_functions);
DECLARE_VARIABLE_WITH_SYMBOL(Funcalled_instructions, Qfuncalled_instructions);
DECLARE_VARIABLE_WITH_SYMBOL(Function_definition_class_description, Qfunction_definition_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_expression_cell_class_description, Qg2_expression_cell_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Generic_simulation_formula_class_description, Qgeneric_simulation_formula_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Global_stack, Qglobal_stack);
#define Global_stack_size FIX((SI_Long)8192L)
#define Higher_than_any_priority FIX((SI_Long)-1L)
DECLARE_VARIABLE_WITH_SYMBOL(In_line_evaluator_array, Qin_line_evaluator_array);
DECLARE_VARIABLE_WITH_SYMBOL(Inference_engine_parameters, Qinference_engine_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Initializing_state_variables_qm, Qinitializing_state_variables_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Inside_breakpoint_p, Qinside_breakpoint_p);
extern Object Instances_specific_to_this_class_kbprop;
extern Object Instruction_description_prop;
extern Object Maximum_byte_code_body_length_to_compile;
#define Maximum_number_of_extended_inline_evaluators FIX((SI_Long)250L)
#define Maximum_number_of_funcalled_evaluators FIX((SI_Long)200L)
#define Maximum_number_of_funcalled_instructions FIX((SI_Long)100L)
#define Maximum_number_of_in_line_evaluators FIX((SI_Long)106L)
#define Maximum_stack_frame_size FIX((SI_Long)350L)
DECLARE_VARIABLE_WITH_SYMBOL(Note_blocks_in_tformat, Qnote_blocks_in_tformat);
#define Number_of_extra_stack_frame_values FIX((SI_Long)6L)
DECLARE_VARIABLE_WITH_SYMBOL(Procedure_class_description, Qprocedure_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Rule_class_description, Qrule_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Show_stack_bytes_qm, Qshow_stack_bytes_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_subtable_class_description, Qsimulation_subtable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Snapshots_of_related_blocks, Qsnapshots_of_related_blocks);
extern Object Stack_eval_locals_bindings;
DECLARE_VARIABLE_WITH_SYMBOL(Stack_instructions, Qstack_instructions);
#define Stack_instructions_count_in_g2 FIX((SI_Long)300L)
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_or_parameter_class_description, Qvariable_or_parameter_class_description);
