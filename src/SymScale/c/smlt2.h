/* smlt2.h -- Header File for smlt2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qfloat;
extern Object Qinteger;
extern Object Qnumber;
extern Object Qsymbol;
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

extern Object allocate_byte_vector_16(Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object calculate_new_values_for_continuous_state_variables(Object,Object,Object);
extern Object calculate_new_values_for_dependent_variables(Object,Object,Object);
extern Object calculate_new_values_for_discrete_state_variables(Object,Object,Object);
extern Object calculate_new_values_for_variables(Object,Object,Object);
extern Object calculate_new_values_using_euler(Object,Object,Object);
extern Object calculate_new_values_using_rk4(Object,Object,Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object clear_tainted_variables(int,...);
extern Object compute_g2_time_for_simulation_time(Object);
extern Object constant_queue_push_right(Object,Object);
extern Object continue_data_server_data_acceptance(Object,Object);
extern Object continuous_state_variable_p(Object);
extern Object copy_evaluation_value_1(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object copy_wide_string(Object);
extern Object current_integration_algorithm(void);
extern Object current_send_all_values_at_beginning_of_cycle_qm(void);
extern Object current_simulation_procedure(void);
extern Object dependent_variable_p(Object);
extern Object determine_variable_groups_to_be_updated(void);
extern Object discrete_state_variable_p(Object);
extern Object end_external_simulation_cycle(void);
extern Object end_simulation_cycle(void);
extern Object end_simulation_procedure_or_external_simulation_cycle(void);
extern Object enter_next_simulation_variable_context(void);
extern Object eval_cons_1(Object,Object);
extern Object evaluate_designation(Object,Object);
extern Object evaluation_value_value(Object);
extern Object exit_last_simulation_variable_context(Object,Object);
extern Object externally_simulated_variable_p(Object);
extern Object for_each_element_in_installation_set(Object,Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_or_make_history_buffer(Object,Object);
extern Object get_procedure_argument_list_error_if_any(Object,Object,Object);
extern Object give_warning_1(int,...);
extern Object in_order_p(Object);
extern Object increment_profiling_calls(Object);
extern Object increment_simulation_time_for_current_model_qm(void);
extern Object invoke_simulation_procedure(Object);
extern Object issue_tracing_and_breakpoint_exit_message(Object,Object);
extern Object issue_tracing_and_breakpoints_entry_message(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_compound_fixnum_simulation_time_1(void);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object modify_tracing_and_breakpoints_context_on_entry(Object,Object);
extern Object need_to_stack_eval_to_get_initial_value_for_state_variable_qm(Object,Object);
extern Object note_change_to_runtime_data_for_block_1(Object);
extern Object posit_profiling_structure(Object);
extern Object process_n_variables_in_stack_eval(Object,Object);
extern Object put_simulated_value_to_inference_engine(int,...);
extern Object raw_stack_error_named_error(Object,Object);
extern Object reclaim_compound_fixnum_simulation_time(Object);
extern Object reclaim_interval_at_which_to_send_value_to_inference_engine(Object);
extern Object reclaim_managed_number_or_value_function(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_simulate_cons_1(Object);
extern Object reclaim_temporary_constant_1(Object);
extern Object reclaim_text_string(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object send_all_input_values_to_external_simulator(void);
extern Object set_info_for_evaluation_only(Object);
extern Object set_info_for_next_variable_to_simulate_1(Object);
extern Object set_last_time_value_sent_to_inference_engine(Object,Object);
extern Object signal_simulation_error_after_stack_eval(void);
extern Object sim_eval_calculate_new_evaluation_value_for_state_variable(Object);
extern Object sim_eval_calculate_new_evaluation_value_for_variable(Object);
extern Object sim_eval_calculate_new_value_for_state_variable(Object);
extern Object sim_eval_calculate_new_value_for_variable(Object);
extern Object sim_eval_for_stack(void);
extern Object sim_eval_for_stack_until_value_found(Object);
extern Object sim_eval_for_stack_without_chaining(Object);
extern Object sim_eval_get_evaluation_value_of_parameter(Object);
extern Object sim_eval_get_evaluation_value_of_variable(Object);
extern Object sim_eval_get_value_of_parameter(Object);
extern Object sim_eval_get_value_of_variable(Object);
extern Object simulate_cons_1(Object,Object);
extern Object simulate_one_cycle(Object,Object,Object);
extern Object simulating_externally_p(void);
extern Object simulation_enter_tracing_context_message(void);
extern Object simulation_formula_trace_exit_message(Object);
extern Object simulation_procedure_and_external_simulation_finished_qm(void);
extern Object simulation_type_error_from_within_or_without_stack_eval(Object,Object);
extern Object simulator_almost_up_to_date_qm(Object);
extern Object simulator_time_lag(void);
extern Object stack_eval(Object,Object,Object,Object,Object,Object);
extern Object start_procedure_invocation_in_place(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object state_variable_p(Object);
extern Object store_history_value(Object,Object,Object,Object,Object);
extern Object store_managed_number_or_value_function(Object,Object);
extern Object text_string_p(Object);
extern Object tformat(int,...);
extern Object tformat_stack_error_text_string(int,...);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_character(Object);
extern Object type_specification_of_variable_or_parameter_value(Object);
extern Object type_specification_type_p(Object,Object);
extern Object update_dependent_variable(Object);
extern Object update_state_variable(Object);
extern Object update_variable(Object);
extern Object update_variables(void);
extern Object work_on_external_simulator_tasks(void);
extern Object write_simulation_formula_trace_entry(Object);

#else

extern Object allocate_byte_vector_16();
extern Object c_native_clock_ticks_or_cache();
extern Object calculate_new_values_for_continuous_state_variables();
extern Object calculate_new_values_for_dependent_variables();
extern Object calculate_new_values_for_discrete_state_variables();
extern Object calculate_new_values_for_variables();
extern Object calculate_new_values_using_euler();
extern Object calculate_new_values_using_rk4();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object clear_tainted_variables();
extern Object compute_g2_time_for_simulation_time();
extern Object constant_queue_push_right();
extern Object continue_data_server_data_acceptance();
extern Object continuous_state_variable_p();
extern Object copy_evaluation_value_1();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object copy_wide_string();
extern Object current_integration_algorithm();
extern Object current_send_all_values_at_beginning_of_cycle_qm();
extern Object current_simulation_procedure();
extern Object dependent_variable_p();
extern Object determine_variable_groups_to_be_updated();
extern Object discrete_state_variable_p();
extern Object end_external_simulation_cycle();
extern Object end_simulation_cycle();
extern Object end_simulation_procedure_or_external_simulation_cycle();
extern Object enter_next_simulation_variable_context();
extern Object eval_cons_1();
extern Object evaluate_designation();
extern Object evaluation_value_value();
extern Object exit_last_simulation_variable_context();
extern Object externally_simulated_variable_p();
extern Object for_each_element_in_installation_set();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_or_make_history_buffer();
extern Object get_procedure_argument_list_error_if_any();
extern Object give_warning_1();
extern Object in_order_p();
extern Object increment_profiling_calls();
extern Object increment_simulation_time_for_current_model_qm();
extern Object invoke_simulation_procedure();
extern Object issue_tracing_and_breakpoint_exit_message();
extern Object issue_tracing_and_breakpoints_entry_message();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_compound_fixnum_simulation_time_1();
extern Object make_permanent_schedule_task_structure_internal();
extern Object modify_tracing_and_breakpoints_context_on_entry();
extern Object need_to_stack_eval_to_get_initial_value_for_state_variable_qm();
extern Object note_change_to_runtime_data_for_block_1();
extern Object posit_profiling_structure();
extern Object process_n_variables_in_stack_eval();
extern Object put_simulated_value_to_inference_engine();
extern Object raw_stack_error_named_error();
extern Object reclaim_compound_fixnum_simulation_time();
extern Object reclaim_interval_at_which_to_send_value_to_inference_engine();
extern Object reclaim_managed_number_or_value_function();
extern Object reclaim_schedule_task_args();
extern Object reclaim_simulate_cons_1();
extern Object reclaim_temporary_constant_1();
extern Object reclaim_text_string();
extern Object record_system_variable();
extern Object send_all_input_values_to_external_simulator();
extern Object set_info_for_evaluation_only();
extern Object set_info_for_next_variable_to_simulate_1();
extern Object set_last_time_value_sent_to_inference_engine();
extern Object signal_simulation_error_after_stack_eval();
extern Object sim_eval_calculate_new_evaluation_value_for_state_variable();
extern Object sim_eval_calculate_new_evaluation_value_for_variable();
extern Object sim_eval_calculate_new_value_for_state_variable();
extern Object sim_eval_calculate_new_value_for_variable();
extern Object sim_eval_for_stack();
extern Object sim_eval_for_stack_until_value_found();
extern Object sim_eval_for_stack_without_chaining();
extern Object sim_eval_get_evaluation_value_of_parameter();
extern Object sim_eval_get_evaluation_value_of_variable();
extern Object sim_eval_get_value_of_parameter();
extern Object sim_eval_get_value_of_variable();
extern Object simulate_cons_1();
extern Object simulate_one_cycle();
extern Object simulating_externally_p();
extern Object simulation_enter_tracing_context_message();
extern Object simulation_formula_trace_exit_message();
extern Object simulation_procedure_and_external_simulation_finished_qm();
extern Object simulation_type_error_from_within_or_without_stack_eval();
extern Object simulator_almost_up_to_date_qm();
extern Object simulator_time_lag();
extern Object stack_eval();
extern Object start_procedure_invocation_in_place();
extern Object state_variable_p();
extern Object store_history_value();
extern Object store_managed_number_or_value_function();
extern Object text_string_p();
extern Object tformat();
extern Object tformat_stack_error_text_string();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_character();
extern Object type_specification_of_variable_or_parameter_value();
extern Object type_specification_type_p();
extern Object update_dependent_variable();
extern Object update_state_variable();
extern Object update_variable();
extern Object update_variables();
extern Object work_on_external_simulator_tasks();
extern Object write_simulation_formula_trace_entry();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Breakpoint_level, Qbreakpoint_level);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_g1_semantics_graph, Qcache_g1_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cached_top_of_stack, Qcached_top_of_stack);
extern Object Chain_of_available_schedule_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_activity, Qcurrent_computation_activity);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_component_particulars, Qcurrent_computation_component_particulars);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_flags, Qcurrent_computation_flags);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_instance, Qcurrent_computation_instance);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_style, Qcurrent_computation_style);
DECLARE_VARIABLE_WITH_SYMBOL(Current_environment, Qcurrent_environment);
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_time, Qcurrent_g2_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_model_definition_qm, Qcurrent_model_definition_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_model_runtime_info_qm, Qcurrent_model_runtime_info_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_real_time, Qcurrent_real_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_schedule_task, Qcurrent_schedule_task);
DECLARE_VARIABLE_WITH_SYMBOL(Current_simulation_category, Qcurrent_simulation_category);
DECLARE_VARIABLE_WITH_SYMBOL(Current_simulation_runtime_structure, Qcurrent_simulation_runtime_structure);
extern Object Current_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
extern Object Data_server_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Data_server_parameters, Qdata_server_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Debugging_parameters, Qdebugging_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Debugging_reset, Qdebugging_reset);
extern Object Deferred_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Do_not_update_simulated_value_qm, Qdo_not_update_simulated_value_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Dont_backward_chain_in_sim_eval_qm, Qdont_backward_chain_in_sim_eval_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Dont_proceed_to_next_variable_qm, Qdont_proceed_to_next_variable_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Edit_type_alias_mapping, Qedit_type_alias_mapping);
DECLARE_VARIABLE_WITH_SYMBOL(Evaluating_simulator_procedure_qm, Qevaluating_simulator_procedure_qm);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
DECLARE_VARIABLE_WITH_SYMBOL(Explanation_variables, Qexplanation_variables);
#define Falsity FIX((SI_Long)-1000L)
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
#define Fraction_modulus_of_compound_fixnum_simulation_time FIX((SI_Long)100000L)
DECLARE_VARIABLE_WITH_SYMBOL(Generic_simulation_formula_class_description, Qgeneric_simulation_formula_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_base_time_as_managed_float, Qgensym_base_time_as_managed_float);
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_non_real_time_clock_ticks_qm, Qinhibit_non_real_time_clock_ticks_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Initializing_simulator_qm, Qinitializing_simulator_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Initializing_state_variables_qm, Qinitializing_state_variables_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Inside_breakpoint_p, Qinside_breakpoint_p);
DECLARE_VARIABLE_WITH_SYMBOL(Main_model_runtime_info, Qmain_model_runtime_info);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_simulated_variables_processed, Qnumber_of_simulated_variables_processed);
extern Object Numeric_data_type_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Priority_of_next_task, Qpriority_of_next_task);
DECLARE_VARIABLE_WITH_SYMBOL(Procedure_class_description, Qprocedure_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Profiling_enabled_qm, Qprofiling_enabled_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Put_current_value_called_from_simulator_p, Qput_current_value_called_from_simulator_p);
DECLARE_VARIABLE_WITH_SYMBOL(Ran_out_of_time_qm, Qran_out_of_time_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_breakpoint_level, Qsaved_breakpoint_level);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_source_stepping_level, Qsaved_source_stepping_level);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_tracing_level, Qsaved_tracing_level);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_warning_level, Qsaved_warning_level);
extern Object Seconds_from_1900_to_1970;
DECLARE_VARIABLE_WITH_SYMBOL(Set_of_variables_to_simulation_evaluate, Qset_of_variables_to_simulation_evaluate);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_no_value, Qsimulation_no_value);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_parameters, Qsimulation_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_procedure_completion_form, Qsimulation_procedure_completion_form);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_subtable_class_description, Qsimulation_subtable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_time_managed_float, Qsimulation_time_managed_float);
DECLARE_VARIABLE_WITH_SYMBOL(Source_stepping_level, Qsource_stepping_level);
DECLARE_VARIABLE_WITH_SYMBOL(Stack_expiration, Qstack_expiration);
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Tracing_message_level, Qtracing_message_level);
#define Truth FIX((SI_Long)1000L)
DECLARE_VARIABLE_WITH_SYMBOL(Variable_class_description, Qvariable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_is_at_bottom_of_stack_qm, Qvariable_is_at_bottom_of_stack_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Variables_that_did_not_have_values, Qvariables_that_did_not_have_values);
DECLARE_VARIABLE_WITH_SYMBOL(Warning_message_level, Qwarning_message_level);
DECLARE_VARIABLE_WITH_SYMBOL(Within_simulator_for_stack_error_qm, Qwithin_simulator_for_stack_error_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Working_on_variables_that_need_simulated_values_stack_qm, Qworking_on_variables_that_need_simulated_values_stack_qm);
