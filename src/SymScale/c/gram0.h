/* gram0.h -- Header File for gram0.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qfloat;
extern Object Qinteger;
extern Object Qnumber;
extern Object Qotherwise;
extern Object Qquote;
extern Object Qsecond;
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

extern Object add_grammar_rules_function(Object);
extern Object add_kb_specific_symbol_token(Object,Object);
extern Object add_units_of_measure(Object);
extern Object bytes_per_double_float_simple_array(Object);
extern Object check_and_scale_certainty_factor(Object);
extern Object clear_optimized_constants(void);
extern Object convert_compound_interval(Object);
extern Object convert_compound_quantity_interval(Object);
extern Object convert_interval_phrase(Object);
extern Object convert_quantity_interval_phrase(Object);
extern Object convert_singular_constant(Object);
extern Object def_numeric_subtype(int,...);
extern Object generate_float_vector(Object);
extern Object gensym_decode_unix_time(Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object make_message_rejecting_certainty_factor(Object);
extern Object memq_function(Object,Object);
extern Object mutate_kb_specific_property_value(Object,Object,Object);
extern Object note_use_of_managed_float_in_phrase(Object);
extern Object phrase_cons(Object,Object);
extern Object phrase_for_constant_p(Object);
extern Object phrase_for_unit_of_measure_constant_p(Object);
extern Object phrase_number_p(Object);
extern Object print_constant(int,...);
extern Object print_decoded_time(Object,Object,Object,Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object reason_for_bad_parse_as_string(Object);
extern Object regenerate_optimized_constant(Object);
extern Object reject_truth_value_as_symbol(Object);
extern Object reject_truth_value_as_unit_of_measure_constant(Object);
extern Object restrict_if_not_slot_edit_feature(Object,Object,Object);
extern Object restrict_if_slot_edit_feature(Object,Object,Object);
extern Object set_grammar_transform_can_return_bad_phrase_p(Object);
extern Object star_f_safe(Object,Object);
extern Object text_string_p(Object);
extern Object tformat_text_string(int,...);
extern Object transform_truth_value_phrase_into_slot_constant(Object);
extern Object truth_value_phrase_p(Object);
extern Object truth_value_phrase_value(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_unix_time(int,...);
extern Object write_date_and_time(Object);

#else

extern Object add_grammar_rules_function();
extern Object add_kb_specific_symbol_token();
extern Object add_units_of_measure();
extern Object bytes_per_double_float_simple_array();
extern Object check_and_scale_certainty_factor();
extern Object clear_optimized_constants();
extern Object convert_compound_interval();
extern Object convert_compound_quantity_interval();
extern Object convert_interval_phrase();
extern Object convert_quantity_interval_phrase();
extern Object convert_singular_constant();
extern Object def_numeric_subtype();
extern Object generate_float_vector();
extern Object gensym_decode_unix_time();
extern Object lookup_global_or_kb_specific_property_value();
extern Object make_message_rejecting_certainty_factor();
extern Object memq_function();
extern Object mutate_kb_specific_property_value();
extern Object note_use_of_managed_float_in_phrase();
extern Object phrase_cons();
extern Object phrase_for_constant_p();
extern Object phrase_for_unit_of_measure_constant_p();
extern Object phrase_number_p();
extern Object print_constant();
extern Object print_decoded_time();
extern Object push_optimized_constant();
extern Object reason_for_bad_parse_as_string();
extern Object regenerate_optimized_constant();
extern Object reject_truth_value_as_symbol();
extern Object reject_truth_value_as_unit_of_measure_constant();
extern Object restrict_if_not_slot_edit_feature();
extern Object restrict_if_slot_edit_feature();
extern Object set_grammar_transform_can_return_bad_phrase_p();
extern Object star_f_safe();
extern Object text_string_p();
extern Object tformat_text_string();
extern Object transform_truth_value_phrase_into_slot_constant();
extern Object truth_value_phrase_p();
extern Object truth_value_phrase_value();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_unix_time();
extern Object write_date_and_time();

#endif

/* variables/constants */
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
extern Object Bad_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_edit_state, Qcurrent_edit_state);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
#define Falsity FIX((SI_Long)-1000L)
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_time, Qgensym_time);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_time_at_start, Qgensym_time_at_start);
extern Object N_2_to_31_plus_62_years;
extern Object Numeric_data_type_gkbprop;
extern Object Phrase_sequence_marker;
extern Object Phrase_structure_marker;
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
extern Object Star_singular_of_numeric_data_type_star_kbprop;
#define Ten_years FIX((SI_Long)315360000L)
#define Truth FIX((SI_Long)1000L)
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
