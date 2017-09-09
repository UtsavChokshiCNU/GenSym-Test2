/* alphbt.h -- Header File for alphbt.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qnum_lt;
extern Object Qdigit_char;
extern Object Qerror;
extern Object Qfloat;
extern Object Qinteger;
extern Object Qsymbol;
extern Object Qunsigned_byte;
extern Object Qvariable;

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

extern Object allocate_byte_vector_16(Object);
extern Object alpha_char_pw_function(Object);
extern Object alphabet_case_sensitive_symbol_from_text_string(Object,Object,Object);
extern Object alphabet_normalized_symbol_from_text_string(Object,Object,Object);
extern Object alphabet_strip_delimitors_off_string(Object,Object,Object);
extern Object alphabet_substring_for_symbol_function(Object,Object,Object,Object);
extern Object alphabet_substring_function(Object,Object,Object);
extern Object alphanumericpw_function(Object);
extern Object character_class_relationship(Object,Object);
extern Object chestnut_floorf_function(Object,Object);
extern Object copy_out_current_gensym_string(void);
extern Object copy_out_current_wide_string(void);
extern Object decimal_digit_char_pw_function(Object);
extern Object extend_current_gensym_string(int,...);
extern Object extend_current_wide_string(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_intersection_using_equal(Object,Object);
extern Object gensym_intersection_using_equal_non_empty_p(Object,Object);
extern Object gensym_set_difference_using_equal(Object,Object);
extern Object gensym_set_difference_using_equal_non_empty_p(Object,Object);
extern Object hexadecimal_digit_char_pw_function(Object);
extern Object intern_gensym_string(int,...);
extern Object intern_using_string_buffer(Object,Object,Object);
extern Object intern_wide_string(int,...);
extern Object make_runtime_float_for_tokenizer(Object);
extern Object make_runtime_long_for_tokenizer(Object);
extern Object map_unicode_to_gensym_han_character_code(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object no_value(Object,Object,Object);
extern Object numeric_return_value(Object,Object,Object);
extern Object obtain_simple_gensym_string(Object);
extern Object reclaim_wide_string(Object);
extern Object symbol_name_text_string(Object);
extern Object syntactically_numeric_p(Object);
extern Object text_string_length(Object);
extern Object tokenize_number_from_user(Object,Object,Object);
extern Object twrite_intern_string_buffer_as_gensym_characters(Object);
extern Object twrite_wide_character(Object);
extern Object unicode_uppercase_if_lowercase(Object);
extern Object wide_character_p_function(Object);

#else

extern Object allocate_byte_vector_16();
extern Object alpha_char_pw_function();
extern Object alphabet_case_sensitive_symbol_from_text_string();
extern Object alphabet_normalized_symbol_from_text_string();
extern Object alphabet_strip_delimitors_off_string();
extern Object alphabet_substring_for_symbol_function();
extern Object alphabet_substring_function();
extern Object alphanumericpw_function();
extern Object character_class_relationship();
extern Object chestnut_floorf_function();
extern Object copy_out_current_gensym_string();
extern Object copy_out_current_wide_string();
extern Object decimal_digit_char_pw_function();
extern Object extend_current_gensym_string();
extern Object extend_current_wide_string();
extern Object gensym_cons_1();
extern Object gensym_intersection_using_equal();
extern Object gensym_intersection_using_equal_non_empty_p();
extern Object gensym_set_difference_using_equal();
extern Object gensym_set_difference_using_equal_non_empty_p();
extern Object hexadecimal_digit_char_pw_function();
extern Object intern_gensym_string();
extern Object intern_using_string_buffer();
extern Object intern_wide_string();
extern Object make_runtime_float_for_tokenizer();
extern Object make_runtime_long_for_tokenizer();
extern Object map_unicode_to_gensym_han_character_code();
extern Object mutate_global_property();
extern Object no_value();
extern Object numeric_return_value();
extern Object obtain_simple_gensym_string();
extern Object reclaim_wide_string();
extern Object symbol_name_text_string();
extern Object syntactically_numeric_p();
extern Object text_string_length();
extern Object tokenize_number_from_user();
extern Object twrite_intern_string_buffer_as_gensym_characters();
extern Object twrite_wide_character();
extern Object unicode_uppercase_if_lowercase();
extern Object wide_character_p_function();

#endif

/* variables/constants */
extern Object Alphabet_alphabetic_chars;
extern Object Alphabet_alphanumeric_chars;
DECLARE_VARIABLE_WITH_SYMBOL(Alphabet_canonical_element_st_test, Qalphabet_canonical_element_st_test);
extern Object Alphabet_cardinality;
extern Object Alphabet_character_class_close;
extern Object Alphabet_character_class_open;
extern Object Alphabet_character_class_range;
DECLARE_VARIABLE_WITH_SYMBOL(Alphabet_character_class_st_test, Qalphabet_character_class_st_test);
DECLARE_VARIABLE_WITH_SYMBOL(Alphabet_count_of_standard_state_transition_tests, Qalphabet_count_of_standard_state_transition_tests);
extern Object Alphabet_dollar_sign;
extern Object Alphabet_double_quote_chars;
extern Object Alphabet_editor_legal_whitespace_chars;
DECLARE_VARIABLE_WITH_SYMBOL(Alphabet_equality_st_test, Qalphabet_equality_st_test);
extern Object Alphabet_escape_character;
extern Object Alphabet_g2symbol_chars;
extern Object Alphabet_hexadecimal_chars;
extern Object Alphabet_illegal_codes_character_class;
extern Object Alphabet_left_bracket_chars;
extern Object Alphabet_less_than_sign;
extern Object Alphabet_max_character;
extern Object Alphabet_max_code;
DECLARE_VARIABLE_WITH_SYMBOL(Alphabet_members, Qalphabet_members);
extern Object Alphabet_min_character;
extern Object Alphabet_min_code;
extern Object Alphabet_nonsymbol_character_codes_sorted_by_encoding;
extern Object Alphabet_not_character_code_error_message;
extern Object Alphabet_numeric_chars;
extern Object Alphabet_preds_with_card_gt_2;
extern Object Alphabet_punctuation_characters;
extern Object Alphabet_right_bracket_chars;
DECLARE_VARIABLE_WITH_SYMBOL(Alphabet_standard_state_transition_tests, Qalphabet_standard_state_transition_tests);
DECLARE_VARIABLE_WITH_SYMBOL(Alphabet_subset_function, Qalphabet_subset_function);
extern Object Alphabet_symbol_character_class;
extern Object Alphabet_valid_subset_responses;
extern Object Alphabet_whitespace_characters;
extern Object Alphabet_whitespace_chars;
extern Object Alphabet_zero_width_characters;
extern Object Characters_not_allowed_in_symbols_in_g2_50r0;
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
extern Object G2_comment_recognizing_tokens;
extern Object G2_simple_tokens;
extern Object G2_standard_tokens;
extern Object G2_standard_tokens_head;
extern Object G2_standard_tokens_middle_1;
extern Object G2_standard_tokens_middle_strings;
extern Object G2_standard_tokens_tail;
extern Object G2_symbol_tokens;
extern Object Generally_ambiguous_characters_in_g2_tokenization;
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_linebreak, Qgensym_char_or_code_for_linebreak);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_paragraph_break, Qgensym_char_or_code_for_paragraph_break);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_bullet, Qgensym_code_for_bullet);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_capital_ligature_oe, Qgensym_code_for_capital_ligature_oe);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_linebreak, Qgensym_code_for_linebreak);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_paragraph_break, Qgensym_code_for_paragraph_break);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_small_letter_f_with_hook, Qgensym_code_for_small_letter_f_with_hook);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_small_ligature_oe, Qgensym_code_for_small_ligature_oe);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_trade_mark_sign, Qgensym_code_for_trade_mark_sign);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_linebreak_qm, Qgensym_esc_for_linebreak_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_paragraph_break_qm, Qgensym_esc_for_paragraph_break_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Intern_string_buffer, Qintern_string_buffer);
#define Intern_string_buffer_length FIX((SI_Long)32L)
#define Invalid_gensym_full_row FIX((SI_Long)246L)
DECLARE_VARIABLE_WITH_SYMBOL(Iso_latin1_special_character_code_map, Qiso_latin1_special_character_code_map);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_already_defined_tokenizer_matching_tests, Qlist_of_already_defined_tokenizer_matching_tests);
extern Object Load_kb_tokens;
extern Object Module_search_path_tokens;
DECLARE_VARIABLE_WITH_SYMBOL(No_value, Qno_value);
#define Pct_and FIX((SI_Long)38L)
#define Pct_at FIX((SI_Long)64L)
#define Pct_bq FIX((SI_Long)96L)
#define Pct_bs FIX((SI_Long)92L)
#define Pct_bullet FIX((SI_Long)8226L)
#define Pct_cb FIX((SI_Long)125L)
#define Pct_cbt FIX((SI_Long)93L)
#define Pct_cent_sign FIX((SI_Long)162L)
#define Pct_cm FIX((SI_Long)44L)
#define Pct_col FIX((SI_Long)58L)
#define Pct_copyright_sign FIX((SI_Long)169L)
#define Pct_cp FIX((SI_Long)41L)
#define Pct_ct FIX((SI_Long)94L)
#define Pct_dol FIX((SI_Long)36L)
#define Pct_dq FIX((SI_Long)34L)
#define Pct_eq FIX((SI_Long)61L)
#define Pct_ex FIX((SI_Long)33L)
#define Pct_gt FIX((SI_Long)62L)
#define Pct_inverted_exclamation_point FIX((SI_Long)161L)
#define Pct_inverted_question_mark FIX((SI_Long)191L)
#define Pct_latin_small_letter_f_with_hook FIX((SI_Long)402L)
#define Pct_left_pointing_double_angle_quotation_mark FIX((SI_Long)171L)
#define Pct_line_separator FIX((SI_Long)8232L)
#define Pct_lt FIX((SI_Long)60L)
#define Pct_no FIX((SI_Long)35L)
#define Pct_ob FIX((SI_Long)123L)
#define Pct_obt FIX((SI_Long)91L)
#define Pct_op FIX((SI_Long)40L)
#define Pct_or FIX((SI_Long)124L)
#define Pct_paragraph_separator FIX((SI_Long)8233L)
#define Pct_pct FIX((SI_Long)37L)
#define Pct_plus FIX((SI_Long)43L)
#define Pct_pound_sign FIX((SI_Long)163L)
#define Pct_qm FIX((SI_Long)63L)
#define Pct_registered_sign FIX((SI_Long)174L)
#define Pct_right_pointing_double_angle_quotation_mark FIX((SI_Long)187L)
#define Pct_sc FIX((SI_Long)59L)
#define Pct_sl FIX((SI_Long)47L)
#define Pct_space FIX((SI_Long)32L)
#define Pct_star FIX((SI_Long)42L)
#define Pct_tab FIX((SI_Long)9L)
#define Pct_tl FIX((SI_Long)126L)
#define Pct_trade_mark_sign FIX((SI_Long)8482L)
#define Pct_yen_sign FIX((SI_Long)165L)
extern Object Regexp_macro_tokens;
extern Object Regular_expression_tokens;
DECLARE_VARIABLE_WITH_SYMBOL(Row, Qrow);
extern Object Sentence_end_punctuation_characters;
extern Object Tabular_view_row_selection_tokens;
extern Object Tokenizer_tokens;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
extern Object Unicode_to_gensym_full_row_map;
DECLARE_VARIABLE_WITH_SYMBOL(Valid_token_actions, Qvalid_token_actions);
