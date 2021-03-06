/* player.h -- Header File for player.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qgo;
extern Object Kinitial_element;
extern Object Qprint;
extern Object Qprogn;
extern Object Qquote;
extern Object Qrandom;
extern Object Qstring;
extern Object Qtagbody;
extern Object Qtype;

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

extern Object assq_function(Object,Object);
extern Object attribute_table_p(Object);
extern Object bounds_and_component_in_window(Object,Object,Object,Object,Object,Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object char_equalw_function(Object,Object);
extern Object clear_player(void);
extern Object close_icp_connection_for_player(void);
extern Object collect_subclasses(Object);
extern Object convert_text_to_text_string(int,...);
extern Object copy_as_wide_string(Object);
extern Object copy_managed_float(Object);
extern Object copy_managed_long(Object);
extern Object copy_text_string(Object);
extern Object copy_tree_and_atoms_using_player_conses(Object);
extern Object current_player_event_time(void);
extern Object default_player_handler_for_icp_messages(int,...);
extern Object do_player_funcall(Object);
extern Object drawing_for_eyes_of_player_p(void);
extern Object end_icp_message_group(void);
extern Object enqueue_local_event(int,...);
extern Object execute_player(void);
extern Object find_string_in_text(int,...);
extern Object first_subblock(Object);
extern Object flush_and_shutdown_icp_socket(Object);
extern Object force_window_drawing(Object);
extern Object generate_float_vector(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object gensym_list_4(Object,Object,Object,Object);
extern Object get_current_icp_contact_port_number_or_name_if_any(void);
extern Object get_local_host_name(void);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_position_of_mouse(void);
extern Object get_table_cell_edges(Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object guardian(void);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_open_p(Object);
extern Object key_code_from_character(Object);
extern Object key_code_from_symbol(Object);
extern Object lengthw(Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_evaluation_long(Object);
extern Object make_icp_connection(int,...);
extern Object maybe_schedule_service_workstation(Object,Object);
extern Object menu_heading_text_cell_p(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object notify_user_at_console(int,...);
extern Object open_icp_connection_for_player(Object,Object,Object);
extern Object pause_player(void);
extern Object play_test(int,...);
extern Object player_center_of_rectangle(Object,Object,Object,Object);
extern Object player_do_call_finally(Object,Object);
extern Object player_error(int,...);
extern Object player_eval(Object);
extern Object player_eval_server(Object);
extern Object player_find_action_button(Object);
extern Object player_find_attribute_table_value_cell(Object);
extern Object player_find_instance(Object);
extern Object player_find_menu_item_containing_string(Object);
extern Object player_generate_event(Object);
extern Object player_generate_event_and_suspend(Object);
extern Object player_handler_for_add_from_line_of_text_to_current_window(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object player_instruction_do_call(Object);
extern Object player_instruction_go(Object);
extern Object player_instruction_if(Object);
extern Object player_instruction_if_1(Object);
extern Object player_instruction_let_star(Object);
extern Object player_instruction_let_star_bind(Object);
extern Object player_instruction_player_tagbody_1(Object);
extern Object player_instruction_progn(Object);
extern Object player_instruction_progn_1(Object);
extern Object player_instruction_quote(Object);
extern Object player_instruction_reclaim_player_tree(Object);
extern Object player_instruction_tagbody(Object);
extern Object player_instruction_type_1(Object);
extern Object player_instruction_unbind(Object);
extern Object player_instruction_wait_until(Object);
extern Object player_look_for_text_on_screen(Object);
extern Object player_mark_definitions(Object);
extern Object player_move(Object,Object);
extern Object player_move_to(Object,Object);
extern Object player_move_to_action_button(Object);
extern Object player_move_to_attribute_table_slot(Object);
extern Object player_move_to_instance(Object);
extern Object player_move_to_location(Object);
extern Object player_move_to_menu_item(Object);
extern Object player_move_to_text(Object);
extern Object player_name_location(Object);
extern Object player_parse_arguments(Object,Object);
extern Object player_pop_location(void);
extern Object player_push_location(void);
extern Object player_record_definition(Object,Object);
extern Object player_release_definitions(Object);
extern Object player_server_push_control_stack(Object);
extern Object player_symbol_value(Object);
extern Object player_text_visible_p(Object);
extern Object player_translate_character_code_to_event_code(Object);
extern Object player_type(Object);
extern Object player_type_character(Object);
extern Object player_wait(Object);
extern Object pm_action_button_visible_p(Object);
extern Object pm_best_text(void);
extern Object pm_generate_event(Object,Object,Object,Object);
extern Object pm_get_current_location(void);
extern Object pm_key_code_from_symbol(Object);
extern Object pm_menu_item_visible_p(Object);
extern Object pm_move(Object,Object);
extern Object pm_move_to_action_button(Object);
extern Object pm_move_to_menu_item(Object);
extern Object pm_move_to_table_slot(Object);
extern Object pm_move_to_text(Object);
extern Object pm_pop_location(void);
extern Object pm_push_location(void);
extern Object pm_reset(void);
extern Object pm_table_slot_visible_p(Object);
extern Object pm_text_visible_p(Object);
extern Object pm_translate_character_code_to_event_code(Object,Object);
extern Object pm_type_control_x(void);
extern Object poll_player(void);
extern Object printing_p(void);
extern Object printing_window_p(Object);
extern Object reclaim_atoms_in_tree(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_tree_1(Object);
extern Object reclaim_player_tree_and_atoms(Object);
extern Object reclaim_player_tree_function(Object);
extern Object reclaim_text_string(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object refresh_window(Object);
extern Object remote_eval(Object);
extern Object remote_eval_once(Object,Object,Object,Object);
extern Object resume_player(void);
extern Object scalef_function(Object,Object);
extern Object send_icp_remote_eval(Object);
extern Object set_best_text_matched_by_player(Object);
extern Object set_player_symbol_function(Object,Object);
extern Object set_position_of_mouse_1(Object,Object);
extern Object setup_network_connection_for_connect(int,...);
extern Object suspend_player(void);
extern Object text_string_p(Object);
extern Object text_string_search_complex(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object text_string_search_simple(Object,Object);
extern Object text_visible_p(Object,Object,Object,Object);
extern Object tformat_text_string(int,...);
extern Object trace_events(void);
extern Object undefine_player_symbol_function(Object);

#else

extern Object assq_function();
extern Object attribute_table_p();
extern Object bounds_and_component_in_window();
extern Object bytes_per_double_float_simple_array();
extern Object c_native_clock_ticks_or_cache();
extern Object char_equalw_function();
extern Object clear_player();
extern Object close_icp_connection_for_player();
extern Object collect_subclasses();
extern Object convert_text_to_text_string();
extern Object copy_as_wide_string();
extern Object copy_managed_float();
extern Object copy_managed_long();
extern Object copy_text_string();
extern Object copy_tree_and_atoms_using_player_conses();
extern Object current_player_event_time();
extern Object default_player_handler_for_icp_messages();
extern Object do_player_funcall();
extern Object drawing_for_eyes_of_player_p();
extern Object end_icp_message_group();
extern Object enqueue_local_event();
extern Object execute_player();
extern Object find_string_in_text();
extern Object first_subblock();
extern Object flush_and_shutdown_icp_socket();
extern Object force_window_drawing();
extern Object generate_float_vector();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object gensym_list_4();
extern Object get_current_icp_contact_port_number_or_name_if_any();
extern Object get_local_host_name();
extern Object get_lookup_slot_value_given_default();
extern Object get_position_of_mouse();
extern Object get_table_cell_edges();
extern Object getfq_function_no_default();
extern Object guardian();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_open_p();
extern Object key_code_from_character();
extern Object key_code_from_symbol();
extern Object lengthw();
extern Object lookup_kb_specific_property_value();
extern Object make_evaluation_long();
extern Object make_icp_connection();
extern Object maybe_schedule_service_workstation();
extern Object menu_heading_text_cell_p();
extern Object mutate_global_property();
extern Object notify_user_at_console();
extern Object open_icp_connection_for_player();
extern Object pause_player();
extern Object play_test();
extern Object player_center_of_rectangle();
extern Object player_do_call_finally();
extern Object player_error();
extern Object player_eval();
extern Object player_eval_server();
extern Object player_find_action_button();
extern Object player_find_attribute_table_value_cell();
extern Object player_find_instance();
extern Object player_find_menu_item_containing_string();
extern Object player_generate_event();
extern Object player_generate_event_and_suspend();
extern Object player_handler_for_add_from_line_of_text_to_current_window();
extern Object player_instruction_do_call();
extern Object player_instruction_go();
extern Object player_instruction_if();
extern Object player_instruction_if_1();
extern Object player_instruction_let_star();
extern Object player_instruction_let_star_bind();
extern Object player_instruction_player_tagbody_1();
extern Object player_instruction_progn();
extern Object player_instruction_progn_1();
extern Object player_instruction_quote();
extern Object player_instruction_reclaim_player_tree();
extern Object player_instruction_tagbody();
extern Object player_instruction_type_1();
extern Object player_instruction_unbind();
extern Object player_instruction_wait_until();
extern Object player_look_for_text_on_screen();
extern Object player_mark_definitions();
extern Object player_move();
extern Object player_move_to();
extern Object player_move_to_action_button();
extern Object player_move_to_attribute_table_slot();
extern Object player_move_to_instance();
extern Object player_move_to_location();
extern Object player_move_to_menu_item();
extern Object player_move_to_text();
extern Object player_name_location();
extern Object player_parse_arguments();
extern Object player_pop_location();
extern Object player_push_location();
extern Object player_record_definition();
extern Object player_release_definitions();
extern Object player_server_push_control_stack();
extern Object player_symbol_value();
extern Object player_text_visible_p();
extern Object player_translate_character_code_to_event_code();
extern Object player_type();
extern Object player_type_character();
extern Object player_wait();
extern Object pm_action_button_visible_p();
extern Object pm_best_text();
extern Object pm_generate_event();
extern Object pm_get_current_location();
extern Object pm_key_code_from_symbol();
extern Object pm_menu_item_visible_p();
extern Object pm_move();
extern Object pm_move_to_action_button();
extern Object pm_move_to_menu_item();
extern Object pm_move_to_table_slot();
extern Object pm_move_to_text();
extern Object pm_pop_location();
extern Object pm_push_location();
extern Object pm_reset();
extern Object pm_table_slot_visible_p();
extern Object pm_text_visible_p();
extern Object pm_translate_character_code_to_event_code();
extern Object pm_type_control_x();
extern Object poll_player();
extern Object printing_p();
extern Object printing_window_p();
extern Object reclaim_atoms_in_tree();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_tree_1();
extern Object reclaim_player_tree_and_atoms();
extern Object reclaim_player_tree_function();
extern Object reclaim_text_string();
extern Object record_system_variable();
extern Object refresh_window();
extern Object remote_eval();
extern Object remote_eval_once();
extern Object resume_player();
extern Object scalef_function();
extern Object send_icp_remote_eval();
extern Object set_best_text_matched_by_player();
extern Object set_player_symbol_function();
extern Object set_position_of_mouse_1();
extern Object setup_network_connection_for_connect();
extern Object suspend_player();
extern Object text_string_p();
extern Object text_string_search_complex();
extern Object text_string_search_simple();
extern Object text_visible_p();
extern Object tformat_text_string();
extern Object trace_events();
extern Object undefine_player_symbol_function();

#endif

/* variables/constants */
extern Object Allow_invalidate_on_printing_window_p;
extern Object Available_gensym_conses;
extern Object Best_text_matched_by_player;
extern Object C_boolean_false;
extern Object C_boolean_true;
extern Object Created_simple_float_array_pool_arrays;
extern Object Current_best_match_for_eyes;
extern Object Current_drawing_priority;
extern Object Current_frame_transform_qm;
extern Object Current_icp_buffer;
extern Object Current_icp_port;
extern Object Current_icp_socket;
extern Object Current_image_x_scale;
extern Object Current_image_y_scale;
extern Object Current_score_of_best_match_for_eyes;
extern Object Current_text_focus_for_eyes_qm;
extern Object Current_workstation_native_window_qm;
extern Object Current_write_icp_byte_position;
extern Object Current_x_for_eyes_qm;
extern Object Current_x_origin_of_drawing;
extern Object Current_y_for_eyes_qm;
extern Object Current_y_origin_of_drawing;
extern Object Disable_resumability;
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
#define Falsity FIX((SI_Long)-1000L)
extern Object Icp_buffer_of_start_of_message_series_qm;
extern Object Icp_buffers_for_message_group;
extern Object Icp_byte_position_of_start_of_message_series_qm;
extern Object Icp_player_message_handler_array;
extern Object Icp_printing_message_handler_array;
extern Object Instances_specific_to_this_class_kbprop;
extern Object Isqrt_of_most_positive_fixnum;
extern Object Last_player_event_time;
extern Object Last_player_mouse_x;
extern Object Last_player_mouse_y;
extern Object Lower_match_rank_for_player_eyes_p;
extern Object Maximum_time_slice_size;
extern Object Minus_of_isqrt_of_most_positive_fixnum;
extern Object Number_of_icp_bytes_for_message_series;
extern Object Number_of_icp_bytes_in_message_group;
extern Object Number_of_icp_bytes_to_fill_buffer;
extern Object Player_control_stack;
extern Object Player_current_instruction;
extern Object Player_definition_stack;
extern Object Player_icp_connection;
extern Object Player_lexical_binding_stack;
extern Object Player_location_stack;
extern Object Player_mouse_x;
extern Object Player_mouse_y;
extern Object Player_named_locations;
extern Object Player_pace;
extern Object Player_require_modules_already_sent;
extern Object Player_state;
extern Object Player_target_gensym_window_g2_struct_qm;
extern Object Player_value_stack;
extern Object Priority_of_next_task;
extern Object Profiling_enabled_qm;
extern Object Scope_conses;
extern Object Simple_float_array_pool_memory_usage;
extern Object System_window;
extern Object There_is_a_current_kb_qm;
extern Object Trace_system_calls_p;
#define Truth FIX((SI_Long)1000L)
extern Object Type_of_current_workstation_window;
extern Object Vector_of_simple_float_array_pools;
extern Object Writing_icp_message_group;
