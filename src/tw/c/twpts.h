/* twpts.h -- Header File for twpts.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */

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

extern Object absorb_local_event_ab_side(Object);
extern Object absorb_local_event_ab_side_1(Object,Object,Object,Object,Object,Object);
extern Object block_p_function(Object);
extern Object copy_gensym_window_attributes_into_g2_window(Object);
extern Object equal_rule_context(Object,Object);
extern Object framep_function(Object);
extern Object g2_global_paint_mode_p(void);
extern Object g2_handle_kill_remote_process_reply(Object,Object);
extern Object g2_handle_remote_process_exists_p_reply(Object,Object);
extern Object g2_handle_spawn_remote_process_reply(Object,Object);
extern Object g2_identification_for_write_locks(void);
extern Object get_g2_license_level(void);
extern Object get_g2_window_given_icp_socket(Object);
extern Object get_gensym_window_for_g2_window(Object);
extern Object get_or_make_up_designation_for_block(Object);
extern Object handle_paste_availability_event_in_g2(Object,Object,Object);
extern Object handle_paste_event_in_g2(Object,Object,Object,Object);
extern Object kill_possibly_leftover_spawned_process(Object);
extern Object lay_out_window(Object);
extern Object make_call_hash_function(void);
extern Object notify_engineer(int,...);
extern Object notify_user(int,...);
extern Object pause_for_internal_error(Object);
extern Object poll_player(void);
extern Object print_constant(Object,Object);
extern Object print_designation(Object);
extern Object reclaim_if_evaluation_item_reference(Object);
extern Object reclaim_sysproc_list_function(Object);
extern Object refresh_window(Object);
extern Object remove_graph_rendering_from_graph_grid(Object,Object);
extern Object replace_format_using_equivalent_font(Object);
extern Object report_simple_string_allocation(Object);
extern Object report_simple_string_reclamation(Object,Object);
extern Object run_al_for_recursive_descent(Object,Object);
extern Object run_chinese_for_recursive_descent(Object,Object);
extern Object run_embedded_option_for_recursive_descent(Object,Object);
extern Object run_ent_for_recursive_descent(Object,Object);
extern Object run_g1_for_recursive_descent(Object,Object);
extern Object run_gfi_for_recursive_descent(Object,Object);
extern Object run_gsi_for_recursive_descent(Object,Object);
extern Object run_gspan_for_recursive_descent(Object,Object);
extern Object run_icp_for_recursive_descent(Object,Object);
extern Object run_japanese_for_recursive_descent(Object,Object);
extern Object run_jl_for_recursive_descent(Object,Object);
extern Object run_jp_for_recursive_descent(Object,Object);
extern Object run_kfep_for_recursive_descent(Object,Object);
extern Object run_korean_for_recursive_descent(Object,Object);
extern Object run_nupec_for_recursive_descent(Object,Object);
extern Object run_restricted_use_option_for_recursive_descent(Object,Object);
extern Object run_runtime_option_for_recursive_descent(Object,Object);
extern Object signal_error_for_undefined_function_called_from_telewindows(void);
extern Object signal_floating_point_exception_stack_error(void);
extern Object twrite_designation_for_item(Object);
extern Object warn_of_big_bignum(Object);
extern Object write_error_text(Object);
extern Object write_evaluation_value(Object);
extern Object write_expression(Object);
extern Object write_name_denotation(Object);
extern Object write_name_denotation_components(Object,Object);

#else

extern Object absorb_local_event_ab_side();
extern Object absorb_local_event_ab_side_1();
extern Object block_p_function();
extern Object copy_gensym_window_attributes_into_g2_window();
extern Object equal_rule_context();
extern Object framep_function();
extern Object g2_global_paint_mode_p();
extern Object g2_handle_kill_remote_process_reply();
extern Object g2_handle_remote_process_exists_p_reply();
extern Object g2_handle_spawn_remote_process_reply();
extern Object g2_identification_for_write_locks();
extern Object get_g2_license_level();
extern Object get_g2_window_given_icp_socket();
extern Object get_gensym_window_for_g2_window();
extern Object get_or_make_up_designation_for_block();
extern Object handle_paste_availability_event_in_g2();
extern Object handle_paste_event_in_g2();
extern Object kill_possibly_leftover_spawned_process();
extern Object lay_out_window();
extern Object make_call_hash_function();
extern Object notify_engineer();
extern Object notify_user();
extern Object pause_for_internal_error();
extern Object poll_player();
extern Object print_constant();
extern Object print_designation();
extern Object reclaim_if_evaluation_item_reference();
extern Object reclaim_sysproc_list_function();
extern Object refresh_window();
extern Object remove_graph_rendering_from_graph_grid();
extern Object replace_format_using_equivalent_font();
extern Object report_simple_string_allocation();
extern Object report_simple_string_reclamation();
extern Object run_al_for_recursive_descent();
extern Object run_chinese_for_recursive_descent();
extern Object run_embedded_option_for_recursive_descent();
extern Object run_ent_for_recursive_descent();
extern Object run_g1_for_recursive_descent();
extern Object run_gfi_for_recursive_descent();
extern Object run_gsi_for_recursive_descent();
extern Object run_gspan_for_recursive_descent();
extern Object run_icp_for_recursive_descent();
extern Object run_japanese_for_recursive_descent();
extern Object run_jl_for_recursive_descent();
extern Object run_jp_for_recursive_descent();
extern Object run_kfep_for_recursive_descent();
extern Object run_korean_for_recursive_descent();
extern Object run_nupec_for_recursive_descent();
extern Object run_restricted_use_option_for_recursive_descent();
extern Object run_runtime_option_for_recursive_descent();
extern Object signal_error_for_undefined_function_called_from_telewindows();
extern Object signal_floating_point_exception_stack_error();
extern Object twrite_designation_for_item();
extern Object warn_of_big_bignum();
extern Object write_error_text();
extern Object write_evaluation_value();
extern Object write_expression();
extern Object write_name_denotation();
extern Object write_name_denotation_components();

#endif

/* variables/constants */
extern Object All_foreign_function_images;
extern Object Bad_phrase;
extern Object Current_kb_pathname_qm;
extern Object Default_workspace_frame_description;
extern Object Dequeuing_time;
extern Object Global_grammar;
extern Object Gsi_suppress_output;
extern Object Known_process_ids;
extern Object Log_file_outputting_qm;
extern Object Noting_changes_to_kb_p;
extern Object Player_state;
extern Object Saved_initial_status;
extern Object Timing_parameters;
extern Object Value_undefined_in_telewindows;
extern Object Warmboot_current_time;
extern Object Warmboot_simulated_time;
extern Object Warmbooting_qm;
extern Object Warmbooting_with_catch_up_qm;
