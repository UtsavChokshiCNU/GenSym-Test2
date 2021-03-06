/* sqncs1.h -- Header File for sqncs1.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qcons;
extern Object Kdirectory;
extern Object Kelement_type;
extern Object Qfixnum;
extern Object Kinitial_contents;
extern Object Knewest;
extern Object Qsequence;
extern Object Ktest;
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

extern Object abort_telewindows_for_protocol_out_of_synch_case_6(void);
extern Object abort_telewindows_top_level(Object);
extern Object allocate_byte_vector_16(Object);
extern Object assemble_uncached_compound_method_flags(Object,Object,Object,Object);
extern Object assq_function(Object,Object);
extern Object c_nsleep(Object);
extern Object c_nsleep_next(Object);
extern Object cache_deferred_rule_invocation_indices_function(void);
extern Object cache_icon_in_system_table(void);
extern Object change_login_box_size(void);
extern Object check_small_workspace(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object chestnut_modf_function(Object,Object);
extern Object choose_chaining_refresh_list(void);
extern Object clear_optimized_constants(void);
extern Object convert_input_to_universal_date(Object);
extern Object convert_md5_result_string_to_hex_string(Object,Object);
extern Object convert_uuid_string_to_hex_string(Object,Object);
extern Object copy_foreign_string_arg_if_appropriate(Object);
extern Object copy_list_using_gensym_conses_1(Object);
extern Object copy_list_using_sequence_conses_1(Object);
extern Object copy_list_using_timestamp_conses_1(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object copy_tree_using_sequence_conses_1(Object);
extern Object copy_tree_using_timestamp_conses_1(Object);
extern Object decode_universal_date(Object);
extern Object decrease_raster_dimension(Object,Object,Object);
extern Object delete_gensym_element_1(Object,Object);
extern Object delete_sequence_cons_1(Object,Object);
extern Object delete_sequence_element_1(Object,Object);
extern Object delete_timestamp_cons_1(Object,Object);
extern Object delete_timestamp_element_1(Object,Object);
extern Object digit_char_pw_function(Object,Object);
extern Object encode_password_via_md5(Object,Object,Object);
extern Object encode_universal_date(Object,Object,Object);
extern Object encode_user_password_string_function(Object);
extern Object enhance_graphics_colors(void);
extern Object enlarge_telewindows_memory(Object,Object,Object,Object,Object);
extern Object finalize_indexed_md5_context(Object,Object);
extern Object find_machine_id_in_telewindows_ok_file(void);
extern Object frequently_typed_characters(Object,Object);
extern Object g2_stream_close(Object);
extern Object g2_stream_open_for_input(Object);
extern Object g2_stream_probe_file_for_read(Object);
extern Object g2_stream_read_line(Object);
extern Object generate_large_random(void);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_decode_unix_time(Object);
extern Object gensym_enough_namestring(int,...);
extern Object gensym_list_2(Object,Object);
extern Object gensym_list_3(Object,Object,Object);
extern Object gensym_list_4(Object,Object,Object,Object);
extern Object gensym_make_pathname_with_copied_components(Object,Object,Object,Object,Object,Object,Object);
extern Object gensym_namestring(int,...);
extern Object gensym_symbol_hash(Object);
extern Object gensym_symbol_hash_with_modulus(Object,Object);
extern Object gensym_truename(Object);
extern Object get_appropriate_ok_pathname(int,...);
extern Object get_decoded_real_time(void);
extern Object get_local_machine_id_function(void);
extern Object get_local_machine_ids_as_gensym_list(void);
extern Object get_next_local_machine_id_as_text_string(void);
extern Object get_or_use_g2_ok_pathname(int,...);
extern Object get_or_use_g2v11_ok_pathname(int,...);
extern Object get_or_use_g2v12_ok_pathname(int,...);
extern Object get_or_use_g2v51_ok_pathname(int,...);
extern Object get_or_use_g2v5_ok_pathname(int,...);
extern Object get_or_use_g2v6_ok_pathname(int,...);
extern Object get_or_use_g2v7_ok_pathname(int,...);
extern Object get_or_use_g2v83_ok_pathname(int,...);
extern Object get_or_use_g2v8_ok_pathname(int,...);
extern Object get_or_use_g2v9_ok_pathname(int,...);
extern Object get_or_use_tw_ok_pathname(int,...);
extern Object get_or_use_twv11_ok_pathname(int,...);
extern Object get_or_use_twv12_ok_pathname(int,...);
extern Object get_or_use_twv5_ok_pathname(int,...);
extern Object get_or_use_twv6_ok_pathname(int,...);
extern Object get_or_use_twv7_ok_pathname(int,...);
extern Object get_or_use_twv8_ok_pathname(int,...);
extern Object get_or_use_twv9_ok_pathname(int,...);
extern Object get_telewindows_authorization_state(Object);
extern Object get_telewindows_product_from_level(Object);
extern Object get_telewindows_product_name_from_level(Object);
extern Object get_tw_dates_from_remaining_fields(Object);
extern Object get_tw_modules_from_remaining_fields(Object);
extern Object get_tw_ok_info_from_stream(Object,Object);
extern Object get_tw_ok_info_from_string(Object,Object);
extern Object get_tw_process_limit_from_remaining_fields(Object);
extern Object get_tw_universal_date(void);
extern Object guess_year_from_two_digit_year(Object);
extern Object initialize_class_instance_delta_masks(void);
extern Object initialize_consistency_tree_focus_shifts(void);
extern Object initialize_default_g2_ok_pathname(void);
extern Object initialize_default_g2v11_ok_pathname(void);
extern Object initialize_default_g2v12_ok_pathname(void);
extern Object initialize_default_g2v51_ok_pathname(void);
extern Object initialize_default_g2v5_ok_pathname(void);
extern Object initialize_default_g2v6_ok_pathname(void);
extern Object initialize_default_g2v7_ok_pathname(void);
extern Object initialize_default_g2v83_ok_pathname(void);
extern Object initialize_default_g2v8_ok_pathname(void);
extern Object initialize_default_g2v9_ok_pathname(void);
extern Object initialize_default_tw_ok_pathname(void);
extern Object initialize_default_twv11_ok_pathname(void);
extern Object initialize_default_twv12_ok_pathname(void);
extern Object initialize_default_twv5_ok_pathname(void);
extern Object initialize_default_twv6_ok_pathname(void);
extern Object initialize_default_twv7_ok_pathname(void);
extern Object initialize_default_twv8_ok_pathname(void);
extern Object initialize_default_twv9_ok_pathname(void);
extern Object initialize_embedded_fuzzy_conditionals_list(void);
extern Object initialize_master_hierarchy_reconciliation_switches(void);
extern Object initialize_minimal_fragmentation_seeds(void);
extern Object initialize_network_scheduler_interweave_matrix(Object);
extern Object initialize_verbosity_level(void);
extern Object initializer_for_pathname_for_disabling_g2_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v11_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v12_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v51_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v5_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v6_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v7_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v83_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v8_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_g2v9_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_tw_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_twv11_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_twv12_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_twv5_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_twv6_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_twv7_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_twv8_ok_command_line(void);
extern Object initializer_for_pathname_for_disabling_twv9_ok_command_line(void);
extern Object inner_multiply(Object,Object);
extern Object leap_year_p(Object);
extern Object lengthw(Object);
extern Object make_array_from_strings(Object,Object);
extern Object make_authorization_file_status_string(Object,Object);
extern Object make_gensym_list_1(Object);
extern Object make_sequence_list_1(Object);
extern Object make_small_workspace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_timestamp_list_1(Object);
extern Object memq_function(Object,Object);
extern Object normalized_string_equal(int,...);
extern Object normalized_string_length(Object);
extern Object notify_user(int,...);
extern Object nstring_downcasew(Object);
extern Object obtain_simple_gensym_string(Object);
extern Object obtain_text_string(Object);
extern Object outstanding_sequence_conses(void);
extern Object outstanding_timestamp_conses(void);
extern Object parse_text_line_into_list_of_text_strings_function(Object,Object,Object,Object,Object,Object);
extern Object pointer_to_first_string_in_pool_group(void);
extern Object print_first_string_in_pool_group(void);
extern Object provide_pathname_for_launch_time_load(Object,Object,Object,Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object read_positive_fixnum_from_string(Object,Object,Object);
extern Object read_symbol_from_string(Object,Object,Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_gensym_tree_with_text_strings(Object);
extern Object reclaim_sequence_cons_1(Object);
extern Object reclaim_sequence_list_1(Object);
extern Object reclaim_sequence_list_star_1(Object);
extern Object reclaim_sequence_tree_1(Object);
extern Object reclaim_simple_gensym_string(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_timestamp_cons_1(Object);
extern Object reclaim_timestamp_list_1(Object);
extern Object reclaim_timestamp_list_star_1(Object);
extern Object reclaim_timestamp_tree_1(Object);
extern Object reclaim_wide_string(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object record_telewindows_authorized_products(Object);
extern Object regenerate_optimized_constant(Object);
extern Object replenish_sequence_cons_pool(void);
extern Object replenish_sequence_list_pool(Object);
extern Object replenish_timestamp_cons_pool(void);
extern Object replenish_timestamp_list_pool(Object);
extern Object sequence_cons_1(Object,Object);
extern Object sequence_cons_memory_usage(void);
extern Object sequence_list_2(Object,Object);
extern Object sequence_list_3(Object,Object,Object);
extern Object sequence_list_4(Object,Object,Object,Object);
extern Object sequence_list_trace_hook(Object);
extern Object set_first_string_in_pool_group(Object);
extern Object shrink_telewindows_memory(Object,Object,Object,Object,Object);
extern Object shunned_machine_id_string_p(Object);
extern Object sort_scheduled_priorities(Object);
extern Object string_downcasew(Object);
extern Object symbol_name_text_string(Object);
extern Object telewindows_license_level(Object);
extern Object telewindows_license_level_from_product(Object);
extern Object telewindows_licensed_for_product_p(Object);
extern Object telewindows_screen_list_too_big(void);
extern Object text_string_hash(Object);
extern Object text_string_hash_with_modulus(Object,Object);
extern Object text_string_length(Object);
extern Object text_string_p(Object);
extern Object text_string_substring(Object,Object,Object);
extern Object tformat(int,...);
extern Object tformat_text_string(int,...);
extern Object tformat_tw_decoded_date(Object,Object,Object);
extern Object timestamp_cons_1(Object,Object);
extern Object timestamp_cons_memory_usage(void);
extern Object timestamp_list_2(Object,Object);
extern Object timestamp_list_3(Object,Object,Object);
extern Object timestamp_list_4(Object,Object,Object,Object);
extern Object timestamp_list_trace_hook(Object);
extern Object transform_type_specification_2(Object,Object,Object);
extern Object unicode_lowercase_if_uppercase(Object);
extern Object update_frames_needing_icp_callback(Object,Object);
extern Object update_indexed_md5_context(Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object valid_universal_date_elements_p(Object,Object,Object);
extern Object warn_of_tw_expiration_if_necessary_1(void);
extern Object warp_login_box_1(void);
extern Object wide_character_member(Object,Object);

#else

extern Object abort_telewindows_for_protocol_out_of_synch_case_6();
extern Object abort_telewindows_top_level();
extern Object allocate_byte_vector_16();
extern Object assemble_uncached_compound_method_flags();
extern Object assq_function();
extern Object c_nsleep();
extern Object c_nsleep_next();
extern Object cache_deferred_rule_invocation_indices_function();
extern Object cache_icon_in_system_table();
extern Object change_login_box_size();
extern Object check_small_workspace();
extern Object chestnut_modf_function();
extern Object choose_chaining_refresh_list();
extern Object clear_optimized_constants();
extern Object convert_input_to_universal_date();
extern Object convert_md5_result_string_to_hex_string();
extern Object convert_uuid_string_to_hex_string();
extern Object copy_foreign_string_arg_if_appropriate();
extern Object copy_list_using_gensym_conses_1();
extern Object copy_list_using_sequence_conses_1();
extern Object copy_list_using_timestamp_conses_1();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object copy_tree_using_sequence_conses_1();
extern Object copy_tree_using_timestamp_conses_1();
extern Object decode_universal_date();
extern Object decrease_raster_dimension();
extern Object delete_gensym_element_1();
extern Object delete_sequence_cons_1();
extern Object delete_sequence_element_1();
extern Object delete_timestamp_cons_1();
extern Object delete_timestamp_element_1();
extern Object digit_char_pw_function();
extern Object encode_password_via_md5();
extern Object encode_universal_date();
extern Object encode_user_password_string_function();
extern Object enhance_graphics_colors();
extern Object enlarge_telewindows_memory();
extern Object finalize_indexed_md5_context();
extern Object find_machine_id_in_telewindows_ok_file();
extern Object frequently_typed_characters();
extern Object g2_stream_close();
extern Object g2_stream_open_for_input();
extern Object g2_stream_probe_file_for_read();
extern Object g2_stream_read_line();
extern Object generate_large_random();
extern Object gensym_cons_1();
extern Object gensym_decode_unix_time();
extern Object gensym_enough_namestring();
extern Object gensym_list_2();
extern Object gensym_list_3();
extern Object gensym_list_4();
extern Object gensym_make_pathname_with_copied_components();
extern Object gensym_namestring();
extern Object gensym_symbol_hash();
extern Object gensym_symbol_hash_with_modulus();
extern Object gensym_truename();
extern Object get_appropriate_ok_pathname();
extern Object get_decoded_real_time();
extern Object get_local_machine_id_function();
extern Object get_local_machine_ids_as_gensym_list();
extern Object get_next_local_machine_id_as_text_string();
extern Object get_or_use_g2_ok_pathname();
extern Object get_or_use_g2v11_ok_pathname();
extern Object get_or_use_g2v12_ok_pathname();
extern Object get_or_use_g2v51_ok_pathname();
extern Object get_or_use_g2v5_ok_pathname();
extern Object get_or_use_g2v6_ok_pathname();
extern Object get_or_use_g2v7_ok_pathname();
extern Object get_or_use_g2v83_ok_pathname();
extern Object get_or_use_g2v8_ok_pathname();
extern Object get_or_use_g2v9_ok_pathname();
extern Object get_or_use_tw_ok_pathname();
extern Object get_or_use_twv11_ok_pathname();
extern Object get_or_use_twv12_ok_pathname();
extern Object get_or_use_twv5_ok_pathname();
extern Object get_or_use_twv6_ok_pathname();
extern Object get_or_use_twv7_ok_pathname();
extern Object get_or_use_twv8_ok_pathname();
extern Object get_or_use_twv9_ok_pathname();
extern Object get_telewindows_authorization_state();
extern Object get_telewindows_product_from_level();
extern Object get_telewindows_product_name_from_level();
extern Object get_tw_dates_from_remaining_fields();
extern Object get_tw_modules_from_remaining_fields();
extern Object get_tw_ok_info_from_stream();
extern Object get_tw_ok_info_from_string();
extern Object get_tw_process_limit_from_remaining_fields();
extern Object get_tw_universal_date();
extern Object guess_year_from_two_digit_year();
extern Object initialize_class_instance_delta_masks();
extern Object initialize_consistency_tree_focus_shifts();
extern Object initialize_default_g2_ok_pathname();
extern Object initialize_default_g2v11_ok_pathname();
extern Object initialize_default_g2v12_ok_pathname();
extern Object initialize_default_g2v51_ok_pathname();
extern Object initialize_default_g2v5_ok_pathname();
extern Object initialize_default_g2v6_ok_pathname();
extern Object initialize_default_g2v7_ok_pathname();
extern Object initialize_default_g2v83_ok_pathname();
extern Object initialize_default_g2v8_ok_pathname();
extern Object initialize_default_g2v9_ok_pathname();
extern Object initialize_default_tw_ok_pathname();
extern Object initialize_default_twv11_ok_pathname();
extern Object initialize_default_twv12_ok_pathname();
extern Object initialize_default_twv5_ok_pathname();
extern Object initialize_default_twv6_ok_pathname();
extern Object initialize_default_twv7_ok_pathname();
extern Object initialize_default_twv8_ok_pathname();
extern Object initialize_default_twv9_ok_pathname();
extern Object initialize_embedded_fuzzy_conditionals_list();
extern Object initialize_master_hierarchy_reconciliation_switches();
extern Object initialize_minimal_fragmentation_seeds();
extern Object initialize_network_scheduler_interweave_matrix();
extern Object initialize_verbosity_level();
extern Object initializer_for_pathname_for_disabling_g2_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v11_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v12_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v51_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v5_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v6_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v7_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v83_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v8_ok_command_line();
extern Object initializer_for_pathname_for_disabling_g2v9_ok_command_line();
extern Object initializer_for_pathname_for_disabling_tw_ok_command_line();
extern Object initializer_for_pathname_for_disabling_twv11_ok_command_line();
extern Object initializer_for_pathname_for_disabling_twv12_ok_command_line();
extern Object initializer_for_pathname_for_disabling_twv5_ok_command_line();
extern Object initializer_for_pathname_for_disabling_twv6_ok_command_line();
extern Object initializer_for_pathname_for_disabling_twv7_ok_command_line();
extern Object initializer_for_pathname_for_disabling_twv8_ok_command_line();
extern Object initializer_for_pathname_for_disabling_twv9_ok_command_line();
extern Object inner_multiply();
extern Object leap_year_p();
extern Object lengthw();
extern Object make_array_from_strings();
extern Object make_authorization_file_status_string();
extern Object make_gensym_list_1();
extern Object make_sequence_list_1();
extern Object make_small_workspace();
extern Object make_timestamp_list_1();
extern Object memq_function();
extern Object normalized_string_equal();
extern Object normalized_string_length();
extern Object notify_user();
extern Object nstring_downcasew();
extern Object obtain_simple_gensym_string();
extern Object obtain_text_string();
extern Object outstanding_sequence_conses();
extern Object outstanding_timestamp_conses();
extern Object parse_text_line_into_list_of_text_strings_function();
extern Object pointer_to_first_string_in_pool_group();
extern Object print_first_string_in_pool_group();
extern Object provide_pathname_for_launch_time_load();
extern Object push_optimized_constant();
extern Object read_positive_fixnum_from_string();
extern Object read_symbol_from_string();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_string();
extern Object reclaim_gensym_tree_with_text_strings();
extern Object reclaim_sequence_cons_1();
extern Object reclaim_sequence_list_1();
extern Object reclaim_sequence_list_star_1();
extern Object reclaim_sequence_tree_1();
extern Object reclaim_simple_gensym_string();
extern Object reclaim_text_string();
extern Object reclaim_timestamp_cons_1();
extern Object reclaim_timestamp_list_1();
extern Object reclaim_timestamp_list_star_1();
extern Object reclaim_timestamp_tree_1();
extern Object reclaim_wide_string();
extern Object record_system_variable();
extern Object record_telewindows_authorized_products();
extern Object regenerate_optimized_constant();
extern Object replenish_sequence_cons_pool();
extern Object replenish_sequence_list_pool();
extern Object replenish_timestamp_cons_pool();
extern Object replenish_timestamp_list_pool();
extern Object sequence_cons_1();
extern Object sequence_cons_memory_usage();
extern Object sequence_list_2();
extern Object sequence_list_3();
extern Object sequence_list_4();
extern Object sequence_list_trace_hook();
extern Object set_first_string_in_pool_group();
extern Object shrink_telewindows_memory();
extern Object shunned_machine_id_string_p();
extern Object sort_scheduled_priorities();
extern Object string_downcasew();
extern Object symbol_name_text_string();
extern Object telewindows_license_level();
extern Object telewindows_license_level_from_product();
extern Object telewindows_licensed_for_product_p();
extern Object telewindows_screen_list_too_big();
extern Object text_string_hash();
extern Object text_string_hash_with_modulus();
extern Object text_string_length();
extern Object text_string_p();
extern Object text_string_substring();
extern Object tformat();
extern Object tformat_text_string();
extern Object tformat_tw_decoded_date();
extern Object timestamp_cons_1();
extern Object timestamp_cons_memory_usage();
extern Object timestamp_list_2();
extern Object timestamp_list_3();
extern Object timestamp_list_4();
extern Object timestamp_list_trace_hook();
extern Object transform_type_specification_2();
extern Object unicode_lowercase_if_uppercase();
extern Object update_frames_needing_icp_callback();
extern Object update_indexed_md5_context();
extern Object update_object_pool_meters_list();
extern Object valid_universal_date_elements_p();
extern Object warn_of_tw_expiration_if_necessary_1();
extern Object warp_login_box_1();
extern Object wide_character_member();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Available_sequence_conses, Qavailable_sequence_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_sequence_conses_tail, Qavailable_sequence_conses_tail);
extern Object Available_sequence_conses_tail_vector;
extern Object Available_sequence_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Available_timestamp_conses, Qavailable_timestamp_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_timestamp_conses_tail, Qavailable_timestamp_conses_tail);
extern Object Available_timestamp_conses_tail_vector;
extern Object Available_timestamp_conses_vector;
#define Beta_release_quality FIX((SI_Long)2L)
extern Object Bytes_per_rtl_ptr;
DECLARE_VARIABLE_WITH_SYMBOL(Cached_machine_id_qm, Qcached_machine_id_qm);
extern Object Cannot_open_telewindows_ok_file_message;
DECLARE_VARIABLE_WITH_SYMBOL(Chaining_refresh_list, Qchaining_refresh_list);
DECLARE_VARIABLE_WITH_SYMBOL(Chaining_refresh_version, Qchaining_refresh_version);
extern Object Class_instance_delta_masks;
DECLARE_VARIABLE_WITH_SYMBOL(Clogged_count, Qclogged_count);
extern Object Command_line_arguments;
extern Object Cons_pool_conses_to_make_at_a_time;
DECLARE_VARIABLE_WITH_SYMBOL(Consistency_tree_focus_shifts, Qconsistency_tree_focus_shifts);
extern Object Counter_for_sleep_management_adjustment;
extern Object Current_inner_procedure_loop_cache_index;
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2_ok_pathname, Qdefault_g2_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v11_ok_pathname, Qdefault_g2v11_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v12_ok_pathname, Qdefault_g2v12_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v51_ok_pathname, Qdefault_g2v51_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v5_ok_pathname, Qdefault_g2v5_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v6_ok_pathname, Qdefault_g2v6_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v7_ok_pathname, Qdefault_g2v7_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v83_ok_pathname, Qdefault_g2v83_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v8_ok_pathname, Qdefault_g2v8_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_g2v9_ok_pathname, Qdefault_g2v9_ok_pathname);
extern Object Default_text_string_hash_modulus;
DECLARE_VARIABLE_WITH_SYMBOL(Default_tw_ok_pathname, Qdefault_tw_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_twv11_ok_pathname, Qdefault_twv11_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_twv12_ok_pathname, Qdefault_twv12_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_twv5_ok_pathname, Qdefault_twv5_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_twv6_ok_pathname, Qdefault_twv6_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_twv7_ok_pathname, Qdefault_twv7_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_twv8_ok_pathname, Qdefault_twv8_ok_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Default_twv9_ok_pathname, Qdefault_twv9_ok_pathname);
extern Object Drawing_task_tuning_info;
DECLARE_VARIABLE_WITH_SYMBOL(Embedded_fuzzy_conditionals_list, Qembedded_fuzzy_conditionals_list);
extern Object Embedded_g2_with_windows_goodbye_message;
extern Object Engage_context_pipelining_p;
extern Object Evaluator_tradeoff_info;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(First_string_in_pool_group, Qfirst_string_in_pool_group);
extern Object G2_development_option;
extern Object G2_embedded_option;
extern Object G2_process_count_exceeded_goodbye_message;
extern Object G2_product;
extern Object G2_restricted_use_option;
extern Object G2_runtime_option;
extern Object G2_system_time_too_early_goodbye_message;
DECLARE_VARIABLE_WITH_SYMBOL(Graph_allocation_factor, Qgraph_allocation_factor);
DECLARE_VARIABLE_WITH_SYMBOL(Icon_list_notes, Qicon_list_notes);
DECLARE_VARIABLE_WITH_SYMBOL(Installation_code_in_ok_file, Qinstallation_code_in_ok_file);
DECLARE_VARIABLE_WITH_SYMBOL(Legacy_subsecond_heartbeat_adjustment_interval, Qlegacy_subsecond_heartbeat_adjustment_interval);
extern Object Limit_bignum_inner_loop_cache_p;
#define Major_version_number_of_current_gensym_product_line FIX((SI_Long)12L)
extern Object Map_month_to_number_code;
extern Object Mask12;
DECLARE_VARIABLE_WITH_SYMBOL(Master_hierarchy_reconciliation_switches, Qmaster_hierarchy_reconciliation_switches);
DECLARE_VARIABLE_WITH_SYMBOL(Minimal_fragmentation_seeds, Qminimal_fragmentation_seeds);
#define Minor_version_number_of_current_gensym_product_line FIX((SI_Long)0L)
DECLARE_VARIABLE_WITH_SYMBOL(Name_of_customer_in_ok_file, Qname_of_customer_in_ok_file);
extern Object New_modulus;
extern Object No_valid_telewindows_ok_entry_message;
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_raster_oddspaces, Qnumber_of_raster_oddspaces);
DECLARE_VARIABLE_WITH_SYMBOL(Optional_modules_map, Qoptional_modules_map);
extern Object Original_site_license_title_block_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2_ok_command_line, Qpathname_for_disabling_g2_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v11_ok_command_line, Qpathname_for_disabling_g2v11_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v12_ok_command_line, Qpathname_for_disabling_g2v12_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v51_ok_command_line, Qpathname_for_disabling_g2v51_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v5_ok_command_line, Qpathname_for_disabling_g2v5_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v6_ok_command_line, Qpathname_for_disabling_g2v6_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v7_ok_command_line, Qpathname_for_disabling_g2v7_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v83_ok_command_line, Qpathname_for_disabling_g2v83_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v8_ok_command_line, Qpathname_for_disabling_g2v8_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v9_ok_command_line, Qpathname_for_disabling_g2v9_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_tw_ok_command_line, Qpathname_for_disabling_tw_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv11_ok_command_line, Qpathname_for_disabling_twv11_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv12_ok_command_line, Qpathname_for_disabling_twv12_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv5_ok_command_line, Qpathname_for_disabling_twv5_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv6_ok_command_line, Qpathname_for_disabling_twv6_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv7_ok_command_line, Qpathname_for_disabling_twv7_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv8_ok_command_line, Qpathname_for_disabling_twv8_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv9_ok_command_line, Qpathname_for_disabling_twv9_ok_command_line);
DECLARE_VARIABLE_WITH_SYMBOL(Process_specific_system_pathname, Qprocess_specific_system_pathname);
DECLARE_VARIABLE_WITH_SYMBOL(Random_state_array, Qrandom_state_array);
DECLARE_VARIABLE_WITH_SYMBOL(Random_state_array_24_pointer, Qrandom_state_array_24_pointer);
DECLARE_VARIABLE_WITH_SYMBOL(Random_state_array_current_pointer, Qrandom_state_array_current_pointer);
DECLARE_VARIABLE_WITH_SYMBOL(Reclaimed_telewindows_boxes, Qreclaimed_telewindows_boxes);
extern Object Refuse_load_at_discrepancy_with_system_clock_message;
extern Object Refuse_save_after_system_clock_tampering_message;
#define Release_quality_of_current_gensym_product_line FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Separate_imminent_actions_p, Qseparate_imminent_actions_p);
DECLARE_VARIABLE_WITH_SYMBOL(Sequence_cons_counter, Qsequence_cons_counter);
extern Object Sequence_cons_counter_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Serial_number_in_ok_file, Qserial_number_in_ok_file);
extern Object Serial_number_title_block_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Shunned_machine_ids_list, Qshunned_machine_ids_list);
extern Object Site_license_title_block_phrase;
#define Size_of_local_machine_id FIX((SI_Long)256L)
DECLARE_VARIABLE_WITH_SYMBOL(Telewindows_authorized_products, Qtelewindows_authorized_products);
DECLARE_VARIABLE_WITH_SYMBOL(Telewindows_license_level, Qtelewindows_license_level);
extern Object Telewindows_product_modules_to_select;
DECLARE_VARIABLE_WITH_SYMBOL(Telewindows_screen_utilization, Qtelewindows_screen_utilization);
DECLARE_VARIABLE_WITH_SYMBOL(Time_of_last_expiration_check, Qtime_of_last_expiration_check);
DECLARE_VARIABLE_WITH_SYMBOL(Timestamp_cons_counter, Qtimestamp_cons_counter);
extern Object Timestamp_cons_counter_vector;
extern Object Too_early_telewindows_authorization_message;
extern Object Too_late_telewindows_authorization_message;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
extern Object Tw_cannot_register_process_license_goodbye_message;
extern Object Tw_development_option;
extern Object Tw_embedded_option;
DECLARE_VARIABLE_WITH_SYMBOL(Tw_expiration_check_interval, Qtw_expiration_check_interval);
extern Object Tw_months_of_the_year;
extern Object Tw_process_count_exceeded_goodbye_message;
extern Object Tw_product;
extern Object Tw_restricted_use_option;
extern Object Tw_runtime_option;
extern Object Tw_system_time_too_early_goodbye_message;
extern Object Unlimited_backtracking_in_internal_truth_maintenance_p;
DECLARE_VARIABLE_WITH_SYMBOL(Verbosity_level, Qverbosity_level);
