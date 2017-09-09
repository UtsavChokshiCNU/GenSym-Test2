/* attrs.h -- Header File for attrs.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
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

extern Object add_class_to_environment(int,...);
extern Object allocate_byte_vector_16(Object);
extern Object attribute_input_can_not_open_file_error(void);
extern Object attribute_input_end_of_file_warning(void);
extern Object attribute_input_error_recovery_ignore_warning(Object);
extern Object attribute_input_find_non_white_space(int,...);
extern Object attribute_input_invalid_slot_name_warning(Object);
extern Object attribute_input_invalid_slot_value_warning(Object);
extern Object attribute_input_no_attribute_data_warning(Object);
extern Object attribute_input_no_item_data_warning(Object);
extern Object attribute_input_no_label_warning(Object);
extern Object attribute_input_no_value_data_warning(Object);
extern Object attribute_input_non_existent_frame_warning(void);
extern Object attribute_input_read_error(void);
extern Object attribute_input_temporary_constant_frame_warning(Object);
extern Object attribute_input_text_bad_char_error(Object);
extern Object attribute_input_text_parsing_error(Object);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object clear_optimized_constants(void);
extern Object convert_text_string_to_text(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object delete_frame(Object);
extern Object evaluate_designation(Object,Object);
extern Object extend_current_gensym_string(int,...);
extern Object g2_stream_close(Object);
extern Object g2_stream_open_for_input(Object);
extern Object g2_stream_read_line(Object);
extern Object g2_stream_read_line_for_attribute_file(Object);
extern Object gensym_namestring(int,...);
extern Object gensym_string_length(Object);
extern Object gensym_string_substring(Object,Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_slot_description_if_editable_attribute(Object,Object,Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object give_warning_1(int,...);
extern Object import_text_string(int,...);
extern Object legal_gensym_string_p(int,...);
extern Object load_attribute_file(Object);
extern Object locate_attribute_input_label(Object,Object);
extern Object make_frame(Object);
extern Object most_recent_file_operation_status_as_text(void);
extern Object newline_p(Object);
extern Object parse_text_for_slot(int,...);
extern Object process_attribute_input_item(Object,Object);
extern Object process_attribute_input_value(Object,Object,Object,Object,Object);
extern Object process_attribute_name_for_attribute_input_if_legal(Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object read_attribute_name_from_text_string_1(Object,Object,Object);
extern Object read_complete_attribute_input_value(Object,Object);
extern Object read_ignore_and_display_complete_attribute_input_value(Object,Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_temporary_constant_1(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_wide_string(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object text_string_length(Object);
extern Object text_string_p(Object);
extern Object text_string_substring(Object,Object,Object);
extern Object twrite_string_as_input_line(int,...);
extern Object twrite_wide_character(Object);
extern Object unicode_lowercase_if_uppercase(Object);
extern Object wide_character_member(Object,Object);
extern Object wide_string_to_string(Object);

#else

extern Object add_class_to_environment();
extern Object allocate_byte_vector_16();
extern Object attribute_input_can_not_open_file_error();
extern Object attribute_input_end_of_file_warning();
extern Object attribute_input_error_recovery_ignore_warning();
extern Object attribute_input_find_non_white_space();
extern Object attribute_input_invalid_slot_name_warning();
extern Object attribute_input_invalid_slot_value_warning();
extern Object attribute_input_no_attribute_data_warning();
extern Object attribute_input_no_item_data_warning();
extern Object attribute_input_no_label_warning();
extern Object attribute_input_no_value_data_warning();
extern Object attribute_input_non_existent_frame_warning();
extern Object attribute_input_read_error();
extern Object attribute_input_temporary_constant_frame_warning();
extern Object attribute_input_text_bad_char_error();
extern Object attribute_input_text_parsing_error();
extern Object check_if_superior_classes_are_defined();
extern Object clear_optimized_constants();
extern Object convert_text_string_to_text();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object delete_frame();
extern Object evaluate_designation();
extern Object extend_current_gensym_string();
extern Object g2_stream_close();
extern Object g2_stream_open_for_input();
extern Object g2_stream_read_line();
extern Object g2_stream_read_line_for_attribute_file();
extern Object gensym_namestring();
extern Object gensym_string_length();
extern Object gensym_string_substring();
extern Object get_lookup_slot_value_given_default();
extern Object get_slot_description_if_editable_attribute();
extern Object get_slot_description_of_class_description_function();
extern Object give_warning_1();
extern Object import_text_string();
extern Object legal_gensym_string_p();
extern Object load_attribute_file();
extern Object locate_attribute_input_label();
extern Object make_frame();
extern Object most_recent_file_operation_status_as_text();
extern Object newline_p();
extern Object parse_text_for_slot();
extern Object process_attribute_input_item();
extern Object process_attribute_input_value();
extern Object process_attribute_name_for_attribute_input_if_legal();
extern Object push_optimized_constant();
extern Object read_attribute_name_from_text_string_1();
extern Object read_complete_attribute_input_value();
extern Object read_ignore_and_display_complete_attribute_input_value();
extern Object reclaim_gensym_string();
extern Object reclaim_slot_value();
extern Object reclaim_temporary_constant_1();
extern Object reclaim_text_string();
extern Object reclaim_wide_string();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object set_non_savable_lookup_slot_value();
extern Object text_string_length();
extern Object text_string_p();
extern Object text_string_substring();
extern Object twrite_string_as_input_line();
extern Object twrite_wide_character();
extern Object unicode_lowercase_if_uppercase();
extern Object wide_character_member();
extern Object wide_string_to_string();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Attribute_file_input_frame, Qattribute_file_input_frame);
extern Object Attribute_input_attribute_label;
extern Object Attribute_input_item_label;
extern Object Attribute_input_value_label;
extern Object Attribute_input_white_space;
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_flags, Qcurrent_computation_flags);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Editor_parameters, Qeditor_parameters);
extern Object End_of_file_reached_code;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Internal_status_of_most_recent_file_operation, Qinternal_status_of_most_recent_file_operation);
DECLARE_VARIABLE_WITH_SYMBOL(Suppress_warning_message_header_qm, Qsuppress_warning_message_header_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Warning_message_level, Qwarning_message_level);
