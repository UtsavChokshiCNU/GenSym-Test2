/* gfi-sb.h -- Header File for gfi-sb.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qevery;
extern Object Qlog;
extern Object Qquote;
extern Object Qthe;
extern Object Qunsigned_byte;
extern Object Qvalues;
extern Object Qvariable;
extern Object Qwhen;
extern Object Qwrite;

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
extern Object add_grammar_rules_for_list(int,...);
extern Object add_grammar_rules_function(Object);
extern Object alias_slot_name(int,...);
extern Object change_slot_value(int,...);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object clear_optimized_constants(void);
extern Object compile_gfi_file_format_for_slot(int,...);
extern Object compile_gfi_file_pathname_for_slot(int,...);
extern Object compile_gfi_input_variables_update_mode_for_slot(int,...);
extern Object compile_gfi_interface_object_for_slot(int,...);
extern Object compile_gfi_output_file_update_frequency_for_slot(int,...);
extern Object compile_gfi_output_values_for_slot(int,...);
extern Object def_data_server_pretty_printer(Object,Object);
extern Object designation_operator_or_giver_of_value_p(Object);
extern Object give_warning_1(int,...);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object phrase_cons(Object,Object);
extern Object print_constant(int,...);
extern Object print_designation(Object);
extern Object print_designation_list(Object);
extern Object push_optimized_constant(Object);
extern Object put_gfi_interface_object_where_slot_is_absent(Object,Object);
extern Object reclaim_gfi_input_file_buffer_value(Object,Object);
extern Object reclaim_simple_gensym_string(Object);
extern Object regenerate_optimized_constant(Object);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object simplify_associative_list_operation_all_at_once(Object);
extern Object text_string_p(Object);
extern Object tformat(int,...);
extern Object tprin(Object,Object);
extern Object twrite(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_general_string(Object);
extern Object write_gfi_file_format_from_slot(Object,Object);
extern Object write_gfi_file_pathname_from_slot(Object,Object);
extern Object write_gfi_input_variables_update_mode_from_slot(Object,Object);
extern Object write_gfi_interface_object_from_slot(Object,Object);
extern Object write_gfi_output_file_update_frequency_from_slot(Object,Object);
extern Object write_gfi_output_values_from_slot(Object,Object);
extern Object write_gfi_time_stamp_format_from_slot(Object,Object);
extern Object write_gfi_yes_or_no_qm_from_slot(Object,Object);
extern Object write_ignore_gfi_input_base_time_qm_from_slot(Object,Object);
extern Object write_renamed_gfi_output_file_pathname_from_slot(Object,Object);

#else

extern Object add_class_to_environment();
extern Object add_grammar_rules_for_list();
extern Object add_grammar_rules_function();
extern Object alias_slot_name();
extern Object change_slot_value();
extern Object check_if_superior_classes_are_defined();
extern Object clear_optimized_constants();
extern Object compile_gfi_file_format_for_slot();
extern Object compile_gfi_file_pathname_for_slot();
extern Object compile_gfi_input_variables_update_mode_for_slot();
extern Object compile_gfi_interface_object_for_slot();
extern Object compile_gfi_output_file_update_frequency_for_slot();
extern Object compile_gfi_output_values_for_slot();
extern Object def_data_server_pretty_printer();
extern Object designation_operator_or_giver_of_value_p();
extern Object give_warning_1();
extern Object lookup_global_or_kb_specific_property_value();
extern Object memq_function();
extern Object mutate_global_property();
extern Object phrase_cons();
extern Object print_constant();
extern Object print_designation();
extern Object print_designation_list();
extern Object push_optimized_constant();
extern Object put_gfi_interface_object_where_slot_is_absent();
extern Object reclaim_gfi_input_file_buffer_value();
extern Object reclaim_simple_gensym_string();
extern Object regenerate_optimized_constant();
extern Object set_non_savable_lookup_slot_value();
extern Object simplify_associative_list_operation_all_at_once();
extern Object text_string_p();
extern Object tformat();
extern Object tprin();
extern Object twrite();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_general_string();
extern Object write_gfi_file_format_from_slot();
extern Object write_gfi_file_pathname_from_slot();
extern Object write_gfi_input_variables_update_mode_from_slot();
extern Object write_gfi_interface_object_from_slot();
extern Object write_gfi_output_file_update_frequency_from_slot();
extern Object write_gfi_output_values_from_slot();
extern Object write_gfi_time_stamp_format_from_slot();
extern Object write_gfi_yes_or_no_qm_from_slot();
extern Object write_ignore_gfi_input_base_time_qm_from_slot();
extern Object write_renamed_gfi_output_file_pathname_from_slot();

#endif

/* variables/constants */
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Grammar_categories_getting_yes_no_feature, Qgrammar_categories_getting_yes_no_feature);
DECLARE_VARIABLE_WITH_SYMBOL(Suppress_warning_message_header_qm, Qsuppress_warning_message_header_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Warning_message_level, Qwarning_message_level);
