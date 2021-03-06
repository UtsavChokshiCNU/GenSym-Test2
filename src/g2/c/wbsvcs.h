/* wbsvcs.h -- Header File for wbsvcs.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qget;
extern Object Qimport;
extern Object Qinteger;
extern Object Qmember;
extern Object Qquote;
extern Object Qsequence;
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
extern Object add_grammar_rules_function(Object);
extern Object add_items_to_web_service_subworkspace(Object,Object);
extern Object add_subworkspace(Object,Object);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_evaluation_sequence(Object);
extern Object allocate_evaluation_structure(Object);
extern Object allocate_managed_array(int,...);
extern Object bytes_per_simple_vector(Object);
extern Object change_slot_value(int,...);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object check_type_or_stack_error(int,...);
extern Object chestnut_floorf_function(Object,Object);
extern Object clear_optimized_constants(void);
extern Object collect_subclasses(Object);
extern Object concatenate_text_strings(Object,Object);
extern Object convert_symbol_to_xml_name(Object);
extern Object convert_text_string_to_text(Object);
extern Object convert_xml_name_to_symbol(Object);
extern Object convert_xml_name_to_symbol_and_reclaim(Object);
extern Object copy_as_wide_string(Object);
extern Object copy_evaluation_value_1(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string(Object);
extern Object copy_wide_string(Object);
extern Object define_type_specification_explicit_complex_type(Object,Object);
extern Object digit_char_pw_function(Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object equalw(Object,Object);
extern Object estructure_slot(Object,Object,Object);
extern Object evaluation_sequence_aref(Object,Object);
extern Object evaluation_sequence_of_xml_element_evaluation_values_p(Object);
extern Object evaluation_sequence_of_xml_evaluation_values_p(Object);
extern Object extend_current_gensym_string(int,...);
extern Object format_http_request(Object,Object);
extern Object g2_format_http_response(Object);
extern Object g2_format_web_request(Object,Object);
extern Object g2_get_message_from_web_service_operation_response(Object,Object);
extern Object g2_http_listen(Object,Object,Object,Object);
extern Object g2_import_web_service_description_from_xml_text(Object);
extern Object g2_make_http_response_from_soap_message(Object);
extern Object g2_make_soap_message_from_http_request(Object);
extern Object g2_make_soap_message_from_web_response(Object);
extern Object g2_make_web_request_from_soap_message(Object);
extern Object g2_make_web_service_operation_invocation(Object,Object,Object);
extern Object g2_parse_http_chunk_header(Object);
extern Object g2_parse_http_request(Object,Object);
extern Object g2_parse_http_response(Object,Object);
extern Object g2_shutdown_http_server(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_decode_unix_time(Object);
extern Object gensym_list_2(Object,Object);
extern Object gensym_list_4(Object,Object,Object,Object);
extern Object get_endpoint_from_web_service_endpoint_reference(Object);
extern Object get_instance_with_slot_value_if_any(Object,Object,Object);
extern Object get_instance_with_slot_value_on_subworkspace_if_any(Object,Object,Object,Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_message_from_http_web_service_operation_response(Object);
extern Object get_message_from_soap_web_service_operation_response(Object);
extern Object get_reference_to_item(Object);
extern Object get_service_from_web_service_endpoint_reference(Object);
extern Object get_slot_value_function(Object,Object,Object);
extern Object get_symbol_properties_function(Object);
extern Object http_message_length(Object);
extern Object import_web_service(Object);
extern Object import_web_service_binding(Object);
extern Object import_web_service_binding_operation(Object,Object);
extern Object import_web_service_binding_type(Object);
extern Object import_web_service_description(Object);
extern Object import_web_service_description_child(Object);
extern Object import_web_service_description_from_document(Object);
extern Object import_web_service_endpoint(Object);
extern Object import_web_service_http_binding_attributes(Object,Object);
extern Object import_web_service_http_operation(Object);
extern Object import_web_service_interface(Object);
extern Object import_web_service_interface_message_reference(Object);
extern Object import_web_service_interface_operation(Object);
extern Object import_web_service_message(Object,Object);
extern Object import_web_service_soap12_binding_attributes(Object,Object);
extern Object import_web_service_soap_binding_attributes(Object,Object);
extern Object import_web_service_soap_operation(Object);
extern Object intern_text_string(int,...);
extern Object load_and_initialize_type_description(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_entity(int,...);
extern Object make_error_text(Object,Object);
extern Object make_evaluation_structure_from_soap_message(Object);
extern Object make_free_text_box_with_text(int,...);
extern Object make_gensym_list_1(Object);
extern Object make_http_web_service_operation_invocation(Object,Object,Object,Object);
extern Object make_permanent_uri_reference_structure_internal(void);
extern Object make_soap_message(Object,Object,Object);
extern Object make_soap_message_from_evaluation_structure(Object);
extern Object make_soap_web_service_operation_invocation(Object,Object,Object,Object);
extern Object make_uri_reference_1(Object,Object,Object,Object,Object,Object,Object);
extern Object make_urlencoded_http_entity_from_web_service_message(Object);
extern Object make_web_service_message_from_xml_element_evaluation_value(Object);
extern Object make_web_service_message_from_xml_http_entity(Object);
extern Object make_web_service_message_part_from_xml_element_evaluation_value(Object);
extern Object make_workspace(int,...);
extern Object make_xml_document_from_xml_element_evaluation_value(Object);
extern Object make_xml_document_from_xml_element_evaluation_value_and_reclaim(Object);
extern Object make_xml_element_evaluation_value(Object,Object,Object,Object,Object);
extern Object make_xml_element_evaluation_value_from_web_service_message(Object,Object,Object);
extern Object make_xml_element_evaluation_value_from_web_service_message_part(Object,Object,Object,Object);
extern Object make_xml_element_evaluation_value_from_xml_element(Object);
extern Object make_xml_evaluation_value_from_xml_node(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object notify_http_servers_of_g2_reset(void);
extern Object notify_user_1(Object);
extern Object outstanding_uri_reference_count(void);
extern Object parse_http_message_header(Object,Object);
extern Object parse_http_message_headers(Object);
extern Object parse_http_request_line(Object);
extern Object parse_http_status_line(Object);
extern Object parse_uri(Object);
extern Object position_in_text_string(Object,Object);
extern Object position_in_text_string_tail(Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object raw_stack_error_named_error(Object,Object);
extern Object read_positive_fixnum_from_string(Object,Object,Object);
extern Object read_positive_hexadecimal_fixnum_from_string(Object,Object,Object);
extern Object reason_phrase_for_http_status_code(Object);
extern Object reclaim_evaluation_sequence(Object);
extern Object reclaim_evaluation_structure(Object);
extern Object reclaim_evaluation_value(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_tree_with_text_strings(Object);
extern Object reclaim_list_of_block_snapshots(Object);
extern Object reclaim_text_string(Object);
extern Object reclaim_uri_reference_1(Object);
extern Object reclaim_wide_string(Object);
extern Object reclaim_xml_structures(int,...);
extern Object record_block_for_tformat(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object select_day_of_week_string(Object);
extern Object select_month_string(Object);
extern Object set_evaluation_structure_slot(Object,Object,Object);
extern Object set_frame_name_from_xml_element(Object,Object);
extern Object set_property_value_function(Object,Object,Object);
extern Object set_slot_value_to_evaluation_value_function(Object,Object);
extern Object set_transient_and_propagate(Object,Object);
extern Object slot_value_equal_p(Object,Object);
extern Object soap12_message_get_body(Object);
extern Object soap12_message_get_envelope(Object);
extern Object soap12_message_get_header(Object);
extern Object soap_message_evaluation_structure_p(Object);
extern Object soap_message_get_body(Object);
extern Object soap_message_get_envelope(Object);
extern Object soap_message_get_header(Object);
extern Object symbol_name_text_string(Object);
extern Object text_string_length(Object);
extern Object text_string_substring(Object,Object,Object);
extern Object text_string_trim(Object,Object);
extern Object tformat(int,...);
extern Object tformat_stack_error_text_string(int,...);
extern Object tformat_text_string(int,...);
extern Object time_zone_in_hours(void);
extern Object transfer_item(int,...);
extern Object twrite(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_crlf(void);
extern Object twrite_general_string(Object);
extern Object twrite_http_date(void);
extern Object twrite_percent_encoded_wide_character(Object);
extern Object twrite_two_digit_fixnum(Object);
extern Object twrite_uri(Object);
extern Object twrite_uri_path(Object);
extern Object twrite_urlencoded_text_string(Object);
extern Object twrite_wide_character(Object);
extern Object upcase_text_string_in_place(Object);
extern Object update_object_pool_meters_list(Object);
extern Object uri_path_is_empty_p(Object);
extern Object uri_reference_structure_memory_usage(void);
extern Object urlencode_www_form(Object);
extern Object validate_item_or_evaluation_value(Object,Object,Object);
extern Object web_service_binding_interface(Object);
extern Object web_service_binding_operation(Object,Object);
extern Object web_service_interface_operation(Object,Object);
extern Object web_service_message_p(Object);
extern Object web_service_message_part_value_p(Object);
extern Object write_http_method_from_slot(Object,Object);
extern Object write_http_server_port_from_slot(Object,Object);
extern Object write_uri_from_slot(Object,Object);
extern Object write_web_service_binding_name_from_slot(Object,Object);
extern Object write_web_service_interface_message_reference_from_slot(Object,Object);
extern Object write_web_service_interface_name_from_slot(Object,Object);
extern Object write_xml_ncname_from_slot(Object,Object);
extern Object xml_attributes_evaluation_value_p(Object);
extern Object xml_create_document(void);
extern Object xml_document_root_element(Object);
extern Object xml_element_evaluation_value_attributes(Object);
extern Object xml_element_evaluation_value_children(Object);
extern Object xml_element_evaluation_value_name(Object);
extern Object xml_element_evaluation_value_ns_prefix(Object);
extern Object xml_element_evaluation_value_ns_uri(Object);
extern Object xml_element_evaluation_value_p(Object);
extern Object xml_element_get_attribute(int,...);
extern Object xml_element_get_attribute_qname(int,...);
extern Object xml_element_get_namespace_list(Object,Object);
extern Object xml_element_new_namespace(int,...);
extern Object xml_element_p(Object);
extern Object xml_element_set_attribute(int,...);
extern Object xml_evaluation_value_get_content(Object);
extern Object xml_evaluation_value_is_element_p(Object);
extern Object xml_evaluation_value_p(Object);
extern Object xml_get_errors(void);
extern Object xml_namespace_get_prefix(Object);
extern Object xml_namespace_get_uri(Object);
extern Object xml_namespace_list_item(Object,Object);
extern Object xml_namespace_list_length(Object);
extern Object xml_node_add_content(Object,Object);
extern Object xml_node_attributes(Object);
extern Object xml_node_child_nodes(Object);
extern Object xml_node_get_child_by_name(int,...);
extern Object xml_node_get_content(Object);
extern Object xml_node_list_item(Object,Object);
extern Object xml_node_lookup_namespace(Object,Object);
extern Object xml_node_name(Object);
extern Object xml_node_name_equals_p(int,...);
extern Object xml_node_name_symbols(Object);
extern Object xml_node_namespace_uri_equals_p(Object,Object);
extern Object xml_node_new_child(int,...);
extern Object xml_node_new_child_from_xml_element_evaluation_value(Object,Object);
extern Object xml_node_next_sibling(Object);
extern Object xml_node_parent_node(Object);
extern Object xml_node_qname(Object);
extern Object xml_node_set_namespace(Object,Object);
extern Object xml_node_type_symbol(Object);
extern Object xml_qname_expand(Object);
extern Object xml_read_string(Object);
extern Object xml_read_string_or_stack_error(Object);
extern Object xml_write_text_string(Object);

#else

extern Object add_class_to_environment();
extern Object add_grammar_rules_function();
extern Object add_items_to_web_service_subworkspace();
extern Object add_subworkspace();
extern Object allocate_byte_vector_16();
extern Object allocate_evaluation_sequence();
extern Object allocate_evaluation_structure();
extern Object allocate_managed_array();
extern Object bytes_per_simple_vector();
extern Object change_slot_value();
extern Object check_if_superior_classes_are_defined();
extern Object check_type_or_stack_error();
extern Object chestnut_floorf_function();
extern Object clear_optimized_constants();
extern Object collect_subclasses();
extern Object concatenate_text_strings();
extern Object convert_symbol_to_xml_name();
extern Object convert_text_string_to_text();
extern Object convert_xml_name_to_symbol();
extern Object convert_xml_name_to_symbol_and_reclaim();
extern Object copy_as_wide_string();
extern Object copy_evaluation_value_1();
extern Object copy_out_current_wide_string();
extern Object copy_text_string();
extern Object copy_wide_string();
extern Object define_type_specification_explicit_complex_type();
extern Object digit_char_pw_function();
extern Object direct_structure_method();
extern Object equalw();
extern Object estructure_slot();
extern Object evaluation_sequence_aref();
extern Object evaluation_sequence_of_xml_element_evaluation_values_p();
extern Object evaluation_sequence_of_xml_evaluation_values_p();
extern Object extend_current_gensym_string();
extern Object format_http_request();
extern Object g2_format_http_response();
extern Object g2_format_web_request();
extern Object g2_get_message_from_web_service_operation_response();
extern Object g2_http_listen();
extern Object g2_import_web_service_description_from_xml_text();
extern Object g2_make_http_response_from_soap_message();
extern Object g2_make_soap_message_from_http_request();
extern Object g2_make_soap_message_from_web_response();
extern Object g2_make_web_request_from_soap_message();
extern Object g2_make_web_service_operation_invocation();
extern Object g2_parse_http_chunk_header();
extern Object g2_parse_http_request();
extern Object g2_parse_http_response();
extern Object g2_shutdown_http_server();
extern Object gensym_cons_1();
extern Object gensym_decode_unix_time();
extern Object gensym_list_2();
extern Object gensym_list_4();
extern Object get_endpoint_from_web_service_endpoint_reference();
extern Object get_instance_with_slot_value_if_any();
extern Object get_instance_with_slot_value_on_subworkspace_if_any();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_message_from_http_web_service_operation_response();
extern Object get_message_from_soap_web_service_operation_response();
extern Object get_reference_to_item();
extern Object get_service_from_web_service_endpoint_reference();
extern Object get_slot_value_function();
extern Object get_symbol_properties_function();
extern Object http_message_length();
extern Object import_web_service();
extern Object import_web_service_binding();
extern Object import_web_service_binding_operation();
extern Object import_web_service_binding_type();
extern Object import_web_service_description();
extern Object import_web_service_description_child();
extern Object import_web_service_description_from_document();
extern Object import_web_service_endpoint();
extern Object import_web_service_http_binding_attributes();
extern Object import_web_service_http_operation();
extern Object import_web_service_interface();
extern Object import_web_service_interface_message_reference();
extern Object import_web_service_interface_operation();
extern Object import_web_service_message();
extern Object import_web_service_soap12_binding_attributes();
extern Object import_web_service_soap_binding_attributes();
extern Object import_web_service_soap_operation();
extern Object intern_text_string();
extern Object load_and_initialize_type_description();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_entity();
extern Object make_error_text();
extern Object make_evaluation_structure_from_soap_message();
extern Object make_free_text_box_with_text();
extern Object make_gensym_list_1();
extern Object make_http_web_service_operation_invocation();
extern Object make_permanent_uri_reference_structure_internal();
extern Object make_soap_message();
extern Object make_soap_message_from_evaluation_structure();
extern Object make_soap_web_service_operation_invocation();
extern Object make_uri_reference_1();
extern Object make_urlencoded_http_entity_from_web_service_message();
extern Object make_web_service_message_from_xml_element_evaluation_value();
extern Object make_web_service_message_from_xml_http_entity();
extern Object make_web_service_message_part_from_xml_element_evaluation_value();
extern Object make_workspace();
extern Object make_xml_document_from_xml_element_evaluation_value();
extern Object make_xml_document_from_xml_element_evaluation_value_and_reclaim();
extern Object make_xml_element_evaluation_value();
extern Object make_xml_element_evaluation_value_from_web_service_message();
extern Object make_xml_element_evaluation_value_from_web_service_message_part();
extern Object make_xml_element_evaluation_value_from_xml_element();
extern Object make_xml_evaluation_value_from_xml_node();
extern Object mutate_global_property();
extern Object notify_http_servers_of_g2_reset();
extern Object notify_user_1();
extern Object outstanding_uri_reference_count();
extern Object parse_http_message_header();
extern Object parse_http_message_headers();
extern Object parse_http_request_line();
extern Object parse_http_status_line();
extern Object parse_uri();
extern Object position_in_text_string();
extern Object position_in_text_string_tail();
extern Object push_optimized_constant();
extern Object raw_stack_error_named_error();
extern Object read_positive_fixnum_from_string();
extern Object read_positive_hexadecimal_fixnum_from_string();
extern Object reason_phrase_for_http_status_code();
extern Object reclaim_evaluation_sequence();
extern Object reclaim_evaluation_structure();
extern Object reclaim_evaluation_value();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_tree_with_text_strings();
extern Object reclaim_list_of_block_snapshots();
extern Object reclaim_text_string();
extern Object reclaim_uri_reference_1();
extern Object reclaim_wide_string();
extern Object reclaim_xml_structures();
extern Object record_block_for_tformat();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object select_day_of_week_string();
extern Object select_month_string();
extern Object set_evaluation_structure_slot();
extern Object set_frame_name_from_xml_element();
extern Object set_property_value_function();
extern Object set_slot_value_to_evaluation_value_function();
extern Object set_transient_and_propagate();
extern Object slot_value_equal_p();
extern Object soap12_message_get_body();
extern Object soap12_message_get_envelope();
extern Object soap12_message_get_header();
extern Object soap_message_evaluation_structure_p();
extern Object soap_message_get_body();
extern Object soap_message_get_envelope();
extern Object soap_message_get_header();
extern Object symbol_name_text_string();
extern Object text_string_length();
extern Object text_string_substring();
extern Object text_string_trim();
extern Object tformat();
extern Object tformat_stack_error_text_string();
extern Object tformat_text_string();
extern Object time_zone_in_hours();
extern Object transfer_item();
extern Object twrite();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_crlf();
extern Object twrite_general_string();
extern Object twrite_http_date();
extern Object twrite_percent_encoded_wide_character();
extern Object twrite_two_digit_fixnum();
extern Object twrite_uri();
extern Object twrite_uri_path();
extern Object twrite_urlencoded_text_string();
extern Object twrite_wide_character();
extern Object upcase_text_string_in_place();
extern Object update_object_pool_meters_list();
extern Object uri_path_is_empty_p();
extern Object uri_reference_structure_memory_usage();
extern Object urlencode_www_form();
extern Object validate_item_or_evaluation_value();
extern Object web_service_binding_interface();
extern Object web_service_binding_operation();
extern Object web_service_interface_operation();
extern Object web_service_message_p();
extern Object web_service_message_part_value_p();
extern Object write_http_method_from_slot();
extern Object write_http_server_port_from_slot();
extern Object write_uri_from_slot();
extern Object write_web_service_binding_name_from_slot();
extern Object write_web_service_interface_message_reference_from_slot();
extern Object write_web_service_interface_name_from_slot();
extern Object write_xml_ncname_from_slot();
extern Object xml_attributes_evaluation_value_p();
extern Object xml_create_document();
extern Object xml_document_root_element();
extern Object xml_element_evaluation_value_attributes();
extern Object xml_element_evaluation_value_children();
extern Object xml_element_evaluation_value_name();
extern Object xml_element_evaluation_value_ns_prefix();
extern Object xml_element_evaluation_value_ns_uri();
extern Object xml_element_evaluation_value_p();
extern Object xml_element_get_attribute();
extern Object xml_element_get_attribute_qname();
extern Object xml_element_get_namespace_list();
extern Object xml_element_new_namespace();
extern Object xml_element_p();
extern Object xml_element_set_attribute();
extern Object xml_evaluation_value_get_content();
extern Object xml_evaluation_value_is_element_p();
extern Object xml_evaluation_value_p();
extern Object xml_get_errors();
extern Object xml_namespace_get_prefix();
extern Object xml_namespace_get_uri();
extern Object xml_namespace_list_item();
extern Object xml_namespace_list_length();
extern Object xml_node_add_content();
extern Object xml_node_attributes();
extern Object xml_node_child_nodes();
extern Object xml_node_get_child_by_name();
extern Object xml_node_get_content();
extern Object xml_node_list_item();
extern Object xml_node_lookup_namespace();
extern Object xml_node_name();
extern Object xml_node_name_equals_p();
extern Object xml_node_name_symbols();
extern Object xml_node_namespace_uri_equals_p();
extern Object xml_node_new_child();
extern Object xml_node_new_child_from_xml_element_evaluation_value();
extern Object xml_node_next_sibling();
extern Object xml_node_parent_node();
extern Object xml_node_qname();
extern Object xml_node_set_namespace();
extern Object xml_node_type_symbol();
extern Object xml_qname_expand();
extern Object xml_read_string();
extern Object xml_read_string_or_stack_error();
extern Object xml_write_text_string();

#endif

/* variables/constants */
extern Object Cached_top_of_stack;
extern Object Chain_of_available_uri_references;
extern Object Class_description_gkbprop;
extern Object Current_gensym_string;
extern Object Current_twriting_output_type;
extern Object Current_wide_string;
extern Object Current_wide_string_list;
extern Object Current_xml_structures;
extern Object Fill_pointer_for_current_gensym_string;
extern Object Fill_pointer_for_current_wide_string;
extern Object Http_request_type;
extern Object Http_response_type;
extern Object Instances_specific_to_this_class_kbprop;
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
extern Object Most_positive_fixnum_floor_16;
extern Object Note_blocks_in_tformat;
extern Object Scope_conses;
extern Object Snapshots_of_related_blocks;
extern Object Soap12_xml_namespace_prefix;
extern Object Soap12_xml_namespace_uri;
extern Object Soap_request_type;
extern Object Soap_response_type;
extern Object Soap_xml_namespace_prefix;
extern Object Soap_xml_namespace_uri;
extern Object Structure_being_reclaimed;
extern Object The_type_description_of_uri_reference;
extern Object Total_length_of_current_gensym_string;
extern Object Total_length_of_current_wide_string;
extern Object Uri_reference_count;
extern Object Write_strings_parsably_qm;
extern Object Wsdl_http_xml_namespace_uri;
extern Object Wsdl_soap12_xml_namespace_uri;
extern Object Wsdl_soap_xml_namespace_uri;
extern Object Wsdl_xml_namespace_uri;
extern Object Xsd_xml_namespace_prefix;
extern Object Xsd_xml_namespace_uri;
extern Object Xsi_xml_namespace_prefix;
extern Object Xsi_xml_namespace_uri;
