/* gram1a.h -- Header File for gram1a.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qcdr;
extern Object Qfirst;
extern Object Qfloat;
extern Object Qlast;
extern Object Qnumber;
extern Object Qquote;
extern Object Qsecond;
extern Object Qsequence;
extern Object Qstring;
extern Object Qthe;
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

extern Object add_grammar_rules_for_list(int,...);
extern Object add_grammar_rules_function(Object);
extern Object attribute_definition_type_modifications(Object);
extern Object attribute_definition_type_specification(Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object clear_optimized_constants(void);
extern Object coerce_phrase_number_to_float(Object);
extern Object coerce_quantity_interval_to_float_interval(Object);
extern Object compile_element_type_for_slot(int,...);
extern Object convert_binary_string_for_parsing(Object);
extern Object convert_binary_string_representation_to_internal(Object,Object,Object);
extern Object decode_ddd_dot_dddd_format_in_format_override(Object);
extern Object decode_format(Object);
extern Object decode_normalized_time_of_day(Object);
extern Object decode_normalized_time_of_day_with_subseconds(Object);
extern Object decode_universal_date(Object);
extern Object encode_unix_time_after_failure(Object,Object,Object,Object,Object,Object);
extern Object fix_up_attribute_type_and_modifications_phrase(Object);
extern Object generate_float_vector(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object make_empty_phrase_sequence_kludge(Object);
extern Object make_empty_phrase_structure_kludge(Object);
extern Object make_phrase_item_denotation_from_parse(Object);
extern Object make_phrase_sequence_from_sequence_component_list(Object);
extern Object make_phrase_structure_from_structure_component_list(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object no_change_while_running(void);
extern Object note_use_of_managed_float_in_phrase(Object);
extern Object note_use_of_text_string_in_phrase(Object);
extern Object phrase_cons(Object,Object);
extern Object phrase_list_3(Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object regenerate_optimized_constant(Object);
extern Object remove_noise_at_head_of_list_phrase(Object);
extern Object set_grammar_transform_can_return_bad_phrase_p(Object);
extern Object tformat(int,...);
extern Object tformat_text_string(int,...);
extern Object transform_date_phrase_and_time_of_day_into_g2_time_stamp(Object);
extern Object twrite(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object write_attribute_type_modifications(Object);
extern Object write_element_type_from_slot(Object,Object);
extern Object write_one_attribute_type_modification(Object);

#else

extern Object add_grammar_rules_for_list();
extern Object add_grammar_rules_function();
extern Object attribute_definition_type_modifications();
extern Object attribute_definition_type_specification();
extern Object bytes_per_double_float_simple_array();
extern Object clear_optimized_constants();
extern Object coerce_phrase_number_to_float();
extern Object coerce_quantity_interval_to_float_interval();
extern Object compile_element_type_for_slot();
extern Object convert_binary_string_for_parsing();
extern Object convert_binary_string_representation_to_internal();
extern Object decode_ddd_dot_dddd_format_in_format_override();
extern Object decode_format();
extern Object decode_normalized_time_of_day();
extern Object decode_normalized_time_of_day_with_subseconds();
extern Object decode_universal_date();
extern Object encode_unix_time_after_failure();
extern Object fix_up_attribute_type_and_modifications_phrase();
extern Object generate_float_vector();
extern Object getfq_function_no_default();
extern Object make_empty_phrase_sequence_kludge();
extern Object make_empty_phrase_structure_kludge();
extern Object make_phrase_item_denotation_from_parse();
extern Object make_phrase_sequence_from_sequence_component_list();
extern Object make_phrase_structure_from_structure_component_list();
extern Object mutate_global_property();
extern Object no_change_while_running();
extern Object note_use_of_managed_float_in_phrase();
extern Object note_use_of_text_string_in_phrase();
extern Object phrase_cons();
extern Object phrase_list_3();
extern Object push_optimized_constant();
extern Object regenerate_optimized_constant();
extern Object remove_noise_at_head_of_list_phrase();
extern Object set_grammar_transform_can_return_bad_phrase_p();
extern Object tformat();
extern Object tformat_text_string();
extern Object transform_date_phrase_and_time_of_day_into_g2_time_stamp();
extern Object twrite();
extern Object twrite_beginning_of_wide_string();
extern Object write_attribute_type_modifications();
extern Object write_element_type_from_slot();
extern Object write_one_attribute_type_modification();

#endif

/* variables/constants */
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
extern Object Bad_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(G2_time_at_start, Qg2_time_at_start);
extern Object Global_daylight_saving_time_adjustment;
extern Object Phrase_item_denotation_marker;
extern Object Phrase_sequence_marker;
extern Object Phrase_structure_marker;
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
DECLARE_VARIABLE_WITH_SYMBOL(System_has_paused, Qsystem_has_paused);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
extern Object Type_and_modifications_tag;
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
DECLARE_VARIABLE_WITH_SYMBOL(Write_symbols_in_lower_case_qm, Qwrite_symbols_in_lower_case_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Write_symbols_parsably_qm, Qwrite_symbols_parsably_qm);
