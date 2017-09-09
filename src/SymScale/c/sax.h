/* sax.h -- Header File for sax.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qerror;
extern Object Qstring;
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
extern Object allocate_evaluation_sequence(Object);
extern Object allocate_managed_array(int,...);
extern Object c_xml_fill_characters_or_comment_buffer(Object,Object,Object,Object);
extern Object c_xml_fill_element_name_buffer(Object,Object,Object,Object);
extern Object c_xml_fill_error_buffer(Object,Object,Object);
extern Object c_xml_fill_start_element_att_buffer(Object,Object,Object,Object);
extern Object c_xml_parse_chunk(Object,Object,Object,Object);
extern Object c_xml_parse_file(Object,Object);
extern Object change_slot_value(int,...);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object cleanup_for_sax_parser(Object);
extern Object clear_optimized_constants(void);
extern Object convert_user_g2_text_indices_to_internal_indices(Object,Object,Object);
extern Object copy_as_wide_string(Object);
extern Object copy_foreign_string_arg_if_appropriate(Object);
extern Object deactivate_subclass_of_entity_for_sax_parser(Object);
extern Object eval_cons_1(Object,Object);
extern Object export_text_string(int,...);
extern Object g2_executed_sax_callback(Object);
extern Object g2_finish_sax_parsing(Object);
extern Object g2_reset_sax_parser(Object);
extern Object g2_sax_callback_data(Object,Object);
extern Object g2_sax_events_ready(Object);
extern Object g2_sax_next_callback_type(Object);
extern Object g2_sax_parse_chunk(Object,Object,Object,Object);
extern Object g2_sax_parse_chunk_internal(Object,Object,Object);
extern Object g2_sax_parse_file(Object,Object);
extern Object gensym_string_length(Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_reference_to_item(Object);
extern Object get_sax_callback_data(Object,Object,Object);
extern Object get_slot_value_if_any_function(Object,Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object import_text_string(int,...);
extern Object lisp_xml_fill_characters_or_comment_buffer(Object,Object,Object,Object);
extern Object lisp_xml_fill_element_name_buffer(Object,Object,Object,Object);
extern Object lisp_xml_fill_error_buffer(Object,Object,Object,Object);
extern Object lisp_xml_fill_start_element_att_buffer(Object,Object,Object,Object);
extern Object lisp_xml_size_characters_or_comment(Object,Object);
extern Object lisp_xml_size_element_name(Object,Object);
extern Object lisp_xml_size_start_element_att(Object,Object);
extern Object lisp_xml_size_warning_or_error(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object notify_user(int,...);
extern Object obtain_simple_gensym_string(Object);
extern Object push_optimized_constant(Object);
extern Object raw_stack_error_named_error(Object,Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_gensym_string_or_wide_string(Object);
extern Object reclaim_simple_gensym_string(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_wide_string(Object);
extern Object regenerate_optimized_constant(Object);
extern Object report_text_indices_error(Object,Object,Object,Object);
extern Object reset_sax_parser(Object);
extern Object sax_callback_type(Object);
extern Object sax_characters_or_comment_data(Object,Object,Object);
extern Object sax_end_element_data(Object,Object);
extern Object sax_fill_in_string_buffer(Object,Object,Object,Object);
extern Object sax_get_element_name(Object,Object);
extern Object sax_get_next_start_element_attribute(Object,Object,Object);
extern Object sax_start_element_data(Object,Object);
extern Object sax_start_or_end_document_data(Object);
extern Object sax_warning_or_error_data(Object,Object,Object);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object text_string_length(Object);
extern Object text_string_substring(Object,Object,Object);
extern Object tformat_stack_error_text_string(int,...);

#else

extern Object add_class_to_environment();
extern Object allocate_byte_vector_16();
extern Object allocate_evaluation_sequence();
extern Object allocate_managed_array();
extern Object c_xml_fill_characters_or_comment_buffer();
extern Object c_xml_fill_element_name_buffer();
extern Object c_xml_fill_error_buffer();
extern Object c_xml_fill_start_element_att_buffer();
extern Object c_xml_parse_chunk();
extern Object c_xml_parse_file();
extern Object change_slot_value();
extern Object check_if_superior_classes_are_defined();
extern Object cleanup_for_sax_parser();
extern Object clear_optimized_constants();
extern Object convert_user_g2_text_indices_to_internal_indices();
extern Object copy_as_wide_string();
extern Object copy_foreign_string_arg_if_appropriate();
extern Object deactivate_subclass_of_entity_for_sax_parser();
extern Object eval_cons_1();
extern Object export_text_string();
extern Object g2_executed_sax_callback();
extern Object g2_finish_sax_parsing();
extern Object g2_reset_sax_parser();
extern Object g2_sax_callback_data();
extern Object g2_sax_events_ready();
extern Object g2_sax_next_callback_type();
extern Object g2_sax_parse_chunk();
extern Object g2_sax_parse_chunk_internal();
extern Object g2_sax_parse_file();
extern Object gensym_string_length();
extern Object get_lookup_slot_value_given_default();
extern Object get_reference_to_item();
extern Object get_sax_callback_data();
extern Object get_slot_value_if_any_function();
extern Object getfq_function_no_default();
extern Object import_text_string();
extern Object lisp_xml_fill_characters_or_comment_buffer();
extern Object lisp_xml_fill_element_name_buffer();
extern Object lisp_xml_fill_error_buffer();
extern Object lisp_xml_fill_start_element_att_buffer();
extern Object lisp_xml_size_characters_or_comment();
extern Object lisp_xml_size_element_name();
extern Object lisp_xml_size_start_element_att();
extern Object lisp_xml_size_warning_or_error();
extern Object mutate_global_property();
extern Object notify_user();
extern Object obtain_simple_gensym_string();
extern Object push_optimized_constant();
extern Object raw_stack_error_named_error();
extern Object reclaim_gensym_string();
extern Object reclaim_gensym_string_or_wide_string();
extern Object reclaim_simple_gensym_string();
extern Object reclaim_text_string();
extern Object reclaim_wide_string();
extern Object regenerate_optimized_constant();
extern Object report_text_indices_error();
extern Object reset_sax_parser();
extern Object sax_callback_type();
extern Object sax_characters_or_comment_data();
extern Object sax_end_element_data();
extern Object sax_fill_in_string_buffer();
extern Object sax_get_element_name();
extern Object sax_get_next_start_element_attribute();
extern Object sax_start_element_data();
extern Object sax_start_or_end_document_data();
extern Object sax_warning_or_error_data();
extern Object set_non_savable_lookup_slot_value();
extern Object text_string_length();
extern Object text_string_substring();
extern Object tformat_stack_error_text_string();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Cached_top_of_stack, Qcached_top_of_stack);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
DECLARE_VARIABLE_WITH_SYMBOL(Maximum_length_for_sax_strings, Qmaximum_length_for_sax_strings);
#define Maximum_length_for_user_text_strings FIX((SI_Long)100000000L)
extern Object Sax_id_attribute_name;
extern Object Sax_id_attribute_value;
extern Object Sax_id_attributes;
extern Object Sax_id_callback_type;
#define Sax_id_characters Qstring
extern Object Sax_id_comment;
extern Object Sax_id_element_name;
extern Object Sax_id_error_message;
#define Xml_encoding_length FIX((SI_Long)4L)
