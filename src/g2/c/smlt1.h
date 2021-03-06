/* smlt1.h -- Header File for smlt1.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qfloat;
extern Object Qinteger;
extern Object Qnumber;
extern Object Qsymbol;
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

extern Object abort_procedure_invocation(int,...);
extern Object add_externally_simulated_entity_to_simulation_model(Object);
extern Object add_model_to_simulation(Object);
extern Object add_model_which_has_something_to_simulate(Object);
extern Object add_shortest_simulation_time_increment_for_all_models(Object);
extern Object add_to_external_set(Object,Object);
extern Object add_to_installation_set(Object,Object);
extern Object add_to_rederive_set(Object,Object);
extern Object add_to_structures_affected_by_edit_cache(Object,Object,Object);
extern Object add_variable_simulation_runtime_structure_to_runtime_info(Object);
extern Object add_variable_to_simulation_model(Object);
extern Object add_variable_to_sorted_or_unsorted_portion_of_set(Object,Object);
extern Object all_models_paused_qm(Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_managed_float_box(void);
extern Object any_models_running_function_qm(void);
extern Object anything_to_simulate_qm(Object);
extern Object begin_collecting_data_for_simulated_variable_if_appropriate(Object);
extern Object begin_collecting_data_for_simulator(int,...);
extern Object begin_collecting_data_for_simulator_1(Object,Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object bytes_per_simple_vector(Object);
extern Object calculate_new_values_for_dependent_variables(Object,Object,Object);
extern Object cancel_and_reclaim_scheduled_queue_element_1(Object);
extern Object change_slot_value(int,...);
extern Object check_for_simulation_changes(void);
extern Object clear_edit_handling_lists(void);
extern Object clear_external_set(Object);
extern Object clear_installation_set(Object);
extern Object clear_optimized_constants(void);
extern Object clear_rederive_set(Object);
extern Object clear_runtime_structures_caches(void);
extern Object clear_simulation_resumption_stack(void);
extern Object clear_tainted_variables(int,...);
extern Object clear_tainted_variables_1(int,...);
extern Object clear_variables_that_need_simulated_values(void);
extern Object clear_variables_that_need_simulated_values_1(Object);
extern Object collect_one_shot_data_for_simulator(int,...);
extern Object collect_one_shot_data_for_simulator_1(Object);
extern Object collect_subclasses(Object);
extern Object compound_fixnum_simulation_time_structure_memory_usage(void);
extern Object compute_and_initialize_state_variable(Object);
extern Object compute_g2_time_for_simulation_time(Object);
extern Object compute_initial_value_for_state_variable(Object,Object);
extern Object compute_initial_values_for_all_state_variables(void);
extern Object continue_data_server_data_acceptance(Object,Object);
extern Object continuous_state_variable_p(Object);
extern Object convert_simulation_value_to_value_and_type(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_list_using_gensym_conses_1(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object current_default_simulation_time_increment(void);
extern Object current_external_simulator_configuration(void);
extern Object current_model_is_paused_qm(void);
extern Object current_simulation_time_as_float(void);
extern Object current_simulation_time_as_managed_float(void);
extern Object def_data_server(int,...);
extern Object delete_from_external_set(Object);
extern Object delete_from_installation_set(Object);
extern Object delete_from_rederive_set(Object);
extern Object dependent_variable_p(Object);
extern Object direct_structure_method(Object,Object);
extern Object discrete_state_variable_p(Object);
extern Object dont_wait_for_model_to_finish_function_qm(Object);
extern Object evaluation_value_value(Object);
extern Object exit_last_simulation_variable_context(Object,Object);
extern Object external_set_empty_qm(Object);
extern Object external_set_pointers_structure_memory_usage(void);
extern Object for_each_element_in_external_set(Object,Object);
extern Object for_each_element_in_installation_set(Object,Object);
extern Object for_each_element_in_rederive_set(Object,Object);
extern Object for_each_variable_in_model(Object);
extern Object frame_serial_number_setf_helper_1(Object,Object);
extern Object generate_and_set_runtime_formula(Object,Object);
extern Object generate_and_set_runtime_formula_1(Object,Object);
extern Object generate_float_vector(Object);
extern Object generate_new_runtime_simulation_formula(Object);
extern Object generate_standard_error_message(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object gensym_cons_1(Object,Object);
extern Object get_current_time_in_simulation_environment(void);
extern Object get_current_time_in_simulation_environment_and_convert_to_g2_time(void);
extern Object get_external_set_pointers_qm(Object);
extern Object get_formula_focal_entity_for_variable(Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_model_queue_for_model(Object);
extern Object get_model_runtime_info_for_variable(Object);
extern Object get_non_override_variable_group_update_structure(Object);
extern Object get_or_make_edit_cache(Object);
extern Object get_or_make_edit_cache_1(Object);
extern Object get_or_make_simulation_runtime_cache(Object,Object,Object);
extern Object get_simulation_environment_gensym_time_for_variable_as_float(Object);
extern Object get_simulation_specifier_to_use(Object);
extern Object get_slot_value_function(Object,Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object give_warning_1(int,...);
extern Object group_index_structure_structure_memory_usage(void);
extern Object handle_editing_changes_effecting_simulation(void);
extern Object handle_newly_simulated_variable_if_necessary(Object);
extern Object handle_simulator_stack_error(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object initialize_compound_simulation_time(void);
extern Object initialize_current_model_queue(void);
extern Object initialize_externally_simulated_portion_of_model(void);
extern Object initialize_main_model_runtime_info(void);
extern Object initialize_minimum_simulation_time_increment(void);
extern Object initialize_model_queue(void);
extern Object initialize_model_runtime_info(int,...);
extern Object initialize_runtime_simulation_information_for_variable(Object);
extern Object initialize_simulation_environment_vector(Object,Object);
extern Object initialize_simulation_time_managed_float(void);
extern Object initialize_simulator(int,...);
extern Object initialize_simulator_1(void);
extern Object initialize_simulator_as_data_server(void);
extern Object initialize_variables_for_model(void);
extern Object insert_in_external_set(Object,Object);
extern Object insert_in_installation_set(Object,Object);
extern Object insert_in_rederive_set(Object,Object);
extern Object installation_set_empty_qm(Object);
extern Object invoke_user_defined_default_error_handler(Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_and_initialize_variable_simulation_runtime_structure(Object);
extern Object make_compound_fixnum_simulation_time_1(void);
extern Object make_edit_cache_1(void);
extern Object make_error_text(Object,Object);
extern Object make_external_set(void);
extern Object make_external_set_pointers_1(void);
extern Object make_external_set_pointers_if_necessary(Object);
extern Object make_group_index_structure_1(void);
extern Object make_installation_set(void);
extern Object make_model_queue_1(void);
extern Object make_model_runtime_info_1(void);
extern Object make_permanent_compound_fixnum_simulation_time_structure_internal(void);
extern Object make_permanent_external_set_pointers_structure_internal(void);
extern Object make_permanent_group_index_structure_structure_internal(void);
extern Object make_permanent_model_queue_structure_internal(void);
extern Object make_permanent_model_runtime_info_structure_internal(void);
extern Object make_permanent_queue_element_structure_internal(void);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_permanent_variable_group_update_structure_structure_internal(void);
extern Object make_rederive_set(void);
extern Object make_simulation_info_1(void);
extern Object make_variable_group_update_structure_1(void);
extern Object make_variable_simulation_runtime_structure_1(void);
extern Object memq_function(Object,Object);
extern Object model_paused_qm(Object);
extern Object model_queue_structure_memory_usage(void);
extern Object model_runtime_info_function_qm(Object);
extern Object model_runtime_info_structure_memory_usage(void);
extern Object mutate_global_property(Object,Object,Object);
extern Object need_calls_to_simulate_until_consistent_with_gensym_time(void);
extern Object need_to_stack_eval_to_get_initial_value_for_state_variable_qm(Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_runtime_structure_in_things_that_affect_it(Object,Object,Object);
extern Object note_supporting_variables(Object,Object);
extern Object outstanding_compound_fixnum_simulation_time_count(void);
extern Object outstanding_external_set_pointers_count(void);
extern Object outstanding_group_index_structure_count(void);
extern Object outstanding_model_queue_count(void);
extern Object outstanding_model_runtime_info_count(void);
extern Object outstanding_variable_group_update_structure_count(void);
extern Object post_on_message_board(int,...);
extern Object post_simulation_warning_for_no_value(Object);
extern Object post_simulation_warning_for_not_parameter(Object);
extern Object purge_deleted_frames_and_add_new_one(Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object put_current_value(int,...);
extern Object put_integration_algorithm(Object,Object,Object);
extern Object put_simulated_value_to_inference_engine(int,...);
extern Object put_simulation_computation_methods_where_slot_is_absent(Object,Object);
extern Object raw_stack_error_named_error(Object,Object);
extern Object re_initialize_variables_for_one_simulation_cycle(void);
extern Object real_reclaim_compound_fixnum_simulation_time_1(Object);
extern Object reclaim_compound_fixnum_simulation_time(Object);
extern Object reclaim_edit_cache(Object);
extern Object reclaim_error_text(Object);
extern Object reclaim_external_set(Object);
extern Object reclaim_external_set_pointers_1(Object);
extern Object reclaim_external_set_pointers_qm_value(Object,Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_list_star_1(Object);
extern Object reclaim_group_index_structure_1(Object);
extern Object reclaim_installation_set(Object);
extern Object reclaim_interval_at_which_to_send_value_to_inference_engine(Object);
extern Object reclaim_list_of_block_snapshots(Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object reclaim_model_queue_1(Object);
extern Object reclaim_model_queue_function(Object);
extern Object reclaim_model_runtime_info_1(Object);
extern Object reclaim_possible_variable_group_update_structure(Object);
extern Object reclaim_rederive_set(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_simulation_info_1(Object);
extern Object reclaim_simulation_update_table(void);
extern Object reclaim_variable_group_update_structure_1(Object);
extern Object reclaim_variable_group_update_structure_completely(Object);
extern Object reclaim_variable_simulation_runtime_structure(Object);
extern Object reclaim_variable_simulation_runtime_structure_internal_1(Object);
extern Object record_block_for_tformat(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object rederive_set_empty_qm(Object);
extern Object regenerate_optimized_constant(Object);
extern Object registered_and_active_default_error_handler_p(void);
extern Object remove_externally_simulated_entity_from_simulation_model(Object);
extern Object remove_model_from_simulation(Object);
extern Object remove_variable_from_simulation_model(Object);
extern Object replenish_gensym_cons_pool(void);
extern Object reset_new_value_computed_slot(Object);
extern Object reset_sort_flag(Object);
extern Object restart_simulator_after_procedure_1(Object);
extern Object resume_task(Object);
extern Object role_can_be_cached_qm(Object);
extern Object roles_in_designation_can_be_cached_qm(Object,Object);
extern Object schedule_task_to_accept_data(Object);
extern Object scope_cons(Object,Object);
extern Object set_external_variable_for_simulator(int,...);
extern Object set_last_time_value_sent_to_inference_engine(Object,Object);
extern Object set_recaching_needed_flag(Object,Object);
extern Object set_slot_value_function(Object,Object,Object,Object);
extern Object set_up_update_timing_for_variable(Object,Object);
extern Object shutdown_externally_simulated_portion_of_model(void);
extern Object shutdown_models_in_list(Object);
extern Object shutdown_simulator(int,...);
extern Object shutdown_simulator_1(void);
extern Object signal_simulation_error_after_stack_eval(void);
extern Object sim_eval_for_stack_until_value_found(Object);
extern Object sim_eval_for_stack_without_chaining(Object);
extern Object simulate_model_until_consistent(Object);
extern Object simulate_model_until_consistent_internal(void);
extern Object simulate_until_consistent_with_gensym_time(void);
extern Object simulate_until_consistent_with_gensym_time_1(Object);
extern Object simulating_externally_p(void);
extern Object simulation_changes_p(void);
extern Object simulation_procedure_and_external_simulation_finished_qm(void);
extern Object simulation_type_error(Object,Object);
extern Object simulation_type_error_from_within_or_without_stack_eval(Object,Object);
extern Object sort_dependent_variable(Object);
extern Object sort_dependent_variable_info(void);
extern Object sort_dependent_variable_info_1(void);
extern Object state_variable_p(Object);
extern Object stop_collecting_data_for_simulator(Object);
extern Object store_managed_number_or_value_function(Object,Object);
extern Object text_string_p(Object);
extern Object tformat(int,...);
extern Object time_slice_expired_p(void);
extern Object type_specification_of_variable_or_parameter_value(Object);
extern Object update_anything_to_simulate_in_model_qm(Object);
extern Object update_object_pool_meters_list(Object);
extern Object update_shortest_simulation_time_increment_for_all_models(void);
extern Object update_variables(void);
extern Object var_count(Object);
extern Object variable_group_update_structure_structure_memory_usage(void);
extern Object warn_of_undefined_data_server(Object,Object);
extern Object within_stack_eval_p(void);
extern Object work_on_suspendable_task(Object,Object,Object,Object,Object);

#else

extern Object abort_procedure_invocation();
extern Object add_externally_simulated_entity_to_simulation_model();
extern Object add_model_to_simulation();
extern Object add_model_which_has_something_to_simulate();
extern Object add_shortest_simulation_time_increment_for_all_models();
extern Object add_to_external_set();
extern Object add_to_installation_set();
extern Object add_to_rederive_set();
extern Object add_to_structures_affected_by_edit_cache();
extern Object add_variable_simulation_runtime_structure_to_runtime_info();
extern Object add_variable_to_simulation_model();
extern Object add_variable_to_sorted_or_unsorted_portion_of_set();
extern Object all_models_paused_qm();
extern Object allocate_byte_vector_16();
extern Object allocate_managed_float_box();
extern Object any_models_running_function_qm();
extern Object anything_to_simulate_qm();
extern Object begin_collecting_data_for_simulated_variable_if_appropriate();
extern Object begin_collecting_data_for_simulator();
extern Object begin_collecting_data_for_simulator_1();
extern Object bytes_per_double_float_simple_array();
extern Object bytes_per_simple_vector();
extern Object calculate_new_values_for_dependent_variables();
extern Object cancel_and_reclaim_scheduled_queue_element_1();
extern Object change_slot_value();
extern Object check_for_simulation_changes();
extern Object clear_edit_handling_lists();
extern Object clear_external_set();
extern Object clear_installation_set();
extern Object clear_optimized_constants();
extern Object clear_rederive_set();
extern Object clear_runtime_structures_caches();
extern Object clear_simulation_resumption_stack();
extern Object clear_tainted_variables();
extern Object clear_tainted_variables_1();
extern Object clear_variables_that_need_simulated_values();
extern Object clear_variables_that_need_simulated_values_1();
extern Object collect_one_shot_data_for_simulator();
extern Object collect_one_shot_data_for_simulator_1();
extern Object collect_subclasses();
extern Object compound_fixnum_simulation_time_structure_memory_usage();
extern Object compute_and_initialize_state_variable();
extern Object compute_g2_time_for_simulation_time();
extern Object compute_initial_value_for_state_variable();
extern Object compute_initial_values_for_all_state_variables();
extern Object continue_data_server_data_acceptance();
extern Object continuous_state_variable_p();
extern Object convert_simulation_value_to_value_and_type();
extern Object copy_for_slot_value();
extern Object copy_list_using_gensym_conses_1();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object current_default_simulation_time_increment();
extern Object current_external_simulator_configuration();
extern Object current_model_is_paused_qm();
extern Object current_simulation_time_as_float();
extern Object current_simulation_time_as_managed_float();
extern Object def_data_server();
extern Object delete_from_external_set();
extern Object delete_from_installation_set();
extern Object delete_from_rederive_set();
extern Object dependent_variable_p();
extern Object direct_structure_method();
extern Object discrete_state_variable_p();
extern Object dont_wait_for_model_to_finish_function_qm();
extern Object evaluation_value_value();
extern Object exit_last_simulation_variable_context();
extern Object external_set_empty_qm();
extern Object external_set_pointers_structure_memory_usage();
extern Object for_each_element_in_external_set();
extern Object for_each_element_in_installation_set();
extern Object for_each_element_in_rederive_set();
extern Object for_each_variable_in_model();
extern Object frame_serial_number_setf_helper_1();
extern Object generate_and_set_runtime_formula();
extern Object generate_and_set_runtime_formula_1();
extern Object generate_float_vector();
extern Object generate_new_runtime_simulation_formula();
extern Object generate_standard_error_message();
extern Object gensym_cons_1();
extern Object get_current_time_in_simulation_environment();
extern Object get_current_time_in_simulation_environment_and_convert_to_g2_time();
extern Object get_external_set_pointers_qm();
extern Object get_formula_focal_entity_for_variable();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_model_queue_for_model();
extern Object get_model_runtime_info_for_variable();
extern Object get_non_override_variable_group_update_structure();
extern Object get_or_make_edit_cache();
extern Object get_or_make_edit_cache_1();
extern Object get_or_make_simulation_runtime_cache();
extern Object get_simulation_environment_gensym_time_for_variable_as_float();
extern Object get_simulation_specifier_to_use();
extern Object get_slot_value_function();
extern Object getfq_function_no_default();
extern Object give_warning_1();
extern Object group_index_structure_structure_memory_usage();
extern Object handle_editing_changes_effecting_simulation();
extern Object handle_newly_simulated_variable_if_necessary();
extern Object handle_simulator_stack_error();
extern Object initialize_compound_simulation_time();
extern Object initialize_current_model_queue();
extern Object initialize_externally_simulated_portion_of_model();
extern Object initialize_main_model_runtime_info();
extern Object initialize_minimum_simulation_time_increment();
extern Object initialize_model_queue();
extern Object initialize_model_runtime_info();
extern Object initialize_runtime_simulation_information_for_variable();
extern Object initialize_simulation_environment_vector();
extern Object initialize_simulation_time_managed_float();
extern Object initialize_simulator();
extern Object initialize_simulator_1();
extern Object initialize_simulator_as_data_server();
extern Object initialize_variables_for_model();
extern Object insert_in_external_set();
extern Object insert_in_installation_set();
extern Object insert_in_rederive_set();
extern Object installation_set_empty_qm();
extern Object invoke_user_defined_default_error_handler();
extern Object load_and_initialize_type_description();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_and_initialize_variable_simulation_runtime_structure();
extern Object make_compound_fixnum_simulation_time_1();
extern Object make_edit_cache_1();
extern Object make_error_text();
extern Object make_external_set();
extern Object make_external_set_pointers_1();
extern Object make_external_set_pointers_if_necessary();
extern Object make_group_index_structure_1();
extern Object make_installation_set();
extern Object make_model_queue_1();
extern Object make_model_runtime_info_1();
extern Object make_permanent_compound_fixnum_simulation_time_structure_internal();
extern Object make_permanent_external_set_pointers_structure_internal();
extern Object make_permanent_group_index_structure_structure_internal();
extern Object make_permanent_model_queue_structure_internal();
extern Object make_permanent_model_runtime_info_structure_internal();
extern Object make_permanent_queue_element_structure_internal();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_permanent_variable_group_update_structure_structure_internal();
extern Object make_rederive_set();
extern Object make_simulation_info_1();
extern Object make_variable_group_update_structure_1();
extern Object make_variable_simulation_runtime_structure_1();
extern Object memq_function();
extern Object model_paused_qm();
extern Object model_queue_structure_memory_usage();
extern Object model_runtime_info_function_qm();
extern Object model_runtime_info_structure_memory_usage();
extern Object mutate_global_property();
extern Object need_calls_to_simulate_until_consistent_with_gensym_time();
extern Object need_to_stack_eval_to_get_initial_value_for_state_variable_qm();
extern Object note_change_to_block_1();
extern Object note_runtime_structure_in_things_that_affect_it();
extern Object note_supporting_variables();
extern Object outstanding_compound_fixnum_simulation_time_count();
extern Object outstanding_external_set_pointers_count();
extern Object outstanding_group_index_structure_count();
extern Object outstanding_model_queue_count();
extern Object outstanding_model_runtime_info_count();
extern Object outstanding_variable_group_update_structure_count();
extern Object post_on_message_board();
extern Object post_simulation_warning_for_no_value();
extern Object post_simulation_warning_for_not_parameter();
extern Object purge_deleted_frames_and_add_new_one();
extern Object push_optimized_constant();
extern Object put_current_value();
extern Object put_integration_algorithm();
extern Object put_simulated_value_to_inference_engine();
extern Object put_simulation_computation_methods_where_slot_is_absent();
extern Object raw_stack_error_named_error();
extern Object re_initialize_variables_for_one_simulation_cycle();
extern Object real_reclaim_compound_fixnum_simulation_time_1();
extern Object reclaim_compound_fixnum_simulation_time();
extern Object reclaim_edit_cache();
extern Object reclaim_error_text();
extern Object reclaim_external_set();
extern Object reclaim_external_set_pointers_1();
extern Object reclaim_external_set_pointers_qm_value();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_list_star_1();
extern Object reclaim_group_index_structure_1();
extern Object reclaim_installation_set();
extern Object reclaim_interval_at_which_to_send_value_to_inference_engine();
extern Object reclaim_list_of_block_snapshots();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object reclaim_model_queue_1();
extern Object reclaim_model_queue_function();
extern Object reclaim_model_runtime_info_1();
extern Object reclaim_possible_variable_group_update_structure();
extern Object reclaim_rederive_set();
extern Object reclaim_schedule_task_args();
extern Object reclaim_simulation_info_1();
extern Object reclaim_simulation_update_table();
extern Object reclaim_variable_group_update_structure_1();
extern Object reclaim_variable_group_update_structure_completely();
extern Object reclaim_variable_simulation_runtime_structure();
extern Object reclaim_variable_simulation_runtime_structure_internal_1();
extern Object record_block_for_tformat();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object rederive_set_empty_qm();
extern Object regenerate_optimized_constant();
extern Object registered_and_active_default_error_handler_p();
extern Object remove_externally_simulated_entity_from_simulation_model();
extern Object remove_model_from_simulation();
extern Object remove_variable_from_simulation_model();
extern Object replenish_gensym_cons_pool();
extern Object reset_new_value_computed_slot();
extern Object reset_sort_flag();
extern Object restart_simulator_after_procedure_1();
extern Object resume_task();
extern Object role_can_be_cached_qm();
extern Object roles_in_designation_can_be_cached_qm();
extern Object schedule_task_to_accept_data();
extern Object scope_cons();
extern Object set_external_variable_for_simulator();
extern Object set_last_time_value_sent_to_inference_engine();
extern Object set_recaching_needed_flag();
extern Object set_slot_value_function();
extern Object set_up_update_timing_for_variable();
extern Object shutdown_externally_simulated_portion_of_model();
extern Object shutdown_models_in_list();
extern Object shutdown_simulator();
extern Object shutdown_simulator_1();
extern Object signal_simulation_error_after_stack_eval();
extern Object sim_eval_for_stack_until_value_found();
extern Object sim_eval_for_stack_without_chaining();
extern Object simulate_model_until_consistent();
extern Object simulate_model_until_consistent_internal();
extern Object simulate_until_consistent_with_gensym_time();
extern Object simulate_until_consistent_with_gensym_time_1();
extern Object simulating_externally_p();
extern Object simulation_changes_p();
extern Object simulation_procedure_and_external_simulation_finished_qm();
extern Object simulation_type_error();
extern Object simulation_type_error_from_within_or_without_stack_eval();
extern Object sort_dependent_variable();
extern Object sort_dependent_variable_info();
extern Object sort_dependent_variable_info_1();
extern Object state_variable_p();
extern Object stop_collecting_data_for_simulator();
extern Object store_managed_number_or_value_function();
extern Object text_string_p();
extern Object tformat();
extern Object time_slice_expired_p();
extern Object type_specification_of_variable_or_parameter_value();
extern Object update_anything_to_simulate_in_model_qm();
extern Object update_object_pool_meters_list();
extern Object update_shortest_simulation_time_increment_for_all_models();
extern Object update_variables();
extern Object var_count();
extern Object variable_group_update_structure_structure_memory_usage();
extern Object warn_of_undefined_data_server();
extern Object within_stack_eval_p();
extern Object work_on_suspendable_task();

#endif

/* variables/constants */
extern Object As_fast_as_possible_model_queue;
extern Object Available_gensym_conses;
extern Object Cache_g1_semantics_graph;
extern Object Cached_top_of_stack;
extern Object Chain_of_available_compound_fixnum_simulation_times;
extern Object Chain_of_available_external_set_pointerss;
extern Object Chain_of_available_group_index_structures;
extern Object Chain_of_available_model_queues;
extern Object Chain_of_available_model_runtime_infos;
extern Object Chain_of_available_queue_elements;
extern Object Chain_of_available_schedule_tasks;
extern Object Chain_of_available_variable_group_update_structures;
extern Object Compound_fixnum_simulation_time_count;
extern Object Connection_class_description;
extern Object Created_simple_float_array_pool_arrays;
extern Object Current_computation_flags;
extern Object Current_computation_frame;
extern Object Current_computation_instance;
extern Object Current_frame_serial_number;
extern Object Current_g2_time;
extern Object Current_model_definition_qm;
extern Object Current_model_queue_qm;
extern Object Current_model_runtime_info_qm;
extern Object Current_real_time;
extern Object Current_schedule_task;
extern Object Current_simulation_runtime_structure;
extern Object Current_task_queue_vector;
extern Object Current_twriting_output_type;
extern Object Current_wide_string;
extern Object Current_wide_string_list;
extern Object Data_server_kbprop;
extern Object Data_server_or_alias_qm_kbprop;
extern Object Data_server_parameters;
extern Object Deferred_task_queue_vector;
extern Object Dont_backward_chain_in_sim_eval_qm;
extern Object Edit_type_alias_mapping;
extern Object Entity_class_description;
extern Object Evaluating_simulator_procedure_qm;
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
extern Object External_set_pointers_count;
#define Falsity FIX((SI_Long)-1000L)
extern Object Fill_pointer_for_current_wide_string;
#define Fraction_modulus_of_compound_fixnum_simulation_time FIX((SI_Long)100000L)
extern Object Frame_being_made;
extern Object G2_time_at_start;
extern Object Generic_simulation_formula_class_description;
extern Object Gensym_base_time_as_managed_float;
extern Object Gensym_time_at_start;
extern Object Group_index_structure_count;
extern Object Inhibit_non_real_time_clock_ticks_qm;
extern Object Initializing_simulator_qm;
extern Object Initializing_state_variables_qm;
extern Object Instances_specific_to_this_class_kbprop;
extern Object List_of_roles_that_can_be_cached;
extern Object Main_model_runtime_info;
extern Object Minimum_simulation_time_increment;
extern Object Model_queue_count;
extern Object Model_runtime_info_count;
extern Object Next_element_to_be_sorted_qm;
extern Object Note_blocks_in_tformat;
extern Object Note_things_encountered_during_role_service_qm;
extern Object Noting_changes_to_kb_p;
extern Object Number_of_simulated_variables_processed;
extern Object Number_of_variables_to_process_at_a_time;
extern Object Numeric_data_type_gkbprop;
extern Object Parameter_class_description;
extern Object Priority_of_next_task;
extern Object Processing_as_fast_as_possible_models_qm;
extern Object Put_current_value_called_from_simulator_p;
extern Object Ran_out_of_time_qm;
extern Object Recycled_resumption_conses;
extern Object Scope_conses;
extern Object Seconds_from_1900_to_1970;
extern Object Simple_float_array_pool_memory_usage;
extern Object Simulation_no_value;
extern Object Simulation_parameters;
extern Object Simulation_subtable_class_description;
extern Object Simulation_time_accumulator;
extern Object Simulation_time_managed_float;
extern Object Simulator_initialized_as_data_server_qm;
extern Object Snapshots_of_related_blocks;
extern Object Statement_class_description;
extern Object Structure_being_reclaimed;
extern Object Suppress_warning_message_header_qm;
extern Object Synchronous_model_queue;
extern Object System_has_paused;
extern Object System_is_running;
extern Object Task_for_display_of_simulation_time;
extern Object The_type_description_of_compound_fixnum_simulation_time;
extern Object The_type_description_of_external_set_pointers;
extern Object The_type_description_of_group_index_structure;
extern Object The_type_description_of_model_queue;
extern Object The_type_description_of_model_runtime_info;
extern Object The_type_description_of_variable_group_update_structure;
extern Object Things_that_affect_this_formula;
extern Object Total_length_of_current_wide_string;
#define Truth FIX((SI_Long)1000L)
extern Object Variable_class_description;
extern Object Variable_group_update_structure_count;
extern Object Variable_or_parameter_class_description;
extern Object Vector_of_simple_float_array_pools;
extern Object Warmbooting_qm;
extern Object Warning_message_level;
extern Object Within_simulate_until_consistent_with_gensym_time;
