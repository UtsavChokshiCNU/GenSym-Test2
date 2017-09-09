/* kfep3.h -- Header File for kfep3.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qchar_downcase;
extern Object Qchar_upcase;
extern Object Kend1;

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
extern Object convert_jis_string_to_text_string(Object,Object);
extern Object convert_n_bytes_to_jis_string(Object,Object);
extern Object convert_to_ascii_roman_if_possible(Object,Object);
extern Object convert_to_hiragana_if_possible(Object);
extern Object convert_to_hiragana_in_jis_string_if_possible(Object);
extern Object convert_to_jis_string_if_possible(Object);
extern Object convert_to_katakana_if_possible(Object);
extern Object copy_managed_lisp_string(Object,Object,Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_text_string_as_managed_lisp_string(Object,Object,Object);
extern Object extend_current_gensym_string(int,...);
extern Object gensym_jis_code_to_contiguous(Object);
extern Object gensym_string_substring(Object,Object,Object);
extern Object get_list_of_choices_of_kanji_translation(Object,Object);
extern Object kfep_kka_p_update_kojin(Object);
extern Object kka_p_batkanakan(Object,Object,Object,Object);
extern Object legal_gensym_jis_character_code_p(Object);
extern Object lower_case_pw(Object);
extern Object map_longest_possible_substring_using_jis_map(Object,Object,Object,Object,Object);
extern Object note_kfep_conversion_choice(Object,Object,Object);
extern Object number_of_characters_untranslated(Object,Object);
extern Object obtain_simple_gensym_string(Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_text_string(Object);
extern Object regenerate_optimized_constant(Object);
extern Object roman_kana_g2(Object,Object,Object,Object,Object);
extern Object roman_kata_g2(Object,Object,Object,Object,Object);
extern Object search_for_longest_prefix_with_kfep_word_choices(int,...);
extern Object slot_value_cons_1(Object,Object);
extern Object text_string_length(Object);
extern Object tflush_stripped_kana_buffer_if_necessary(Object,Object);
extern Object twrite_character(Object);
extern Object twrite_general_string(Object);
extern Object twrite_wide_character(Object);
extern Object unicode_lowercase_if_uppercase(Object);
extern Object unicode_uppercase_if_lowercase(Object);
extern Object wide_character_member(Object,Object);

#else

extern Object allocate_byte_vector_16();
extern Object convert_jis_string_to_text_string();
extern Object convert_n_bytes_to_jis_string();
extern Object convert_to_ascii_roman_if_possible();
extern Object convert_to_hiragana_if_possible();
extern Object convert_to_hiragana_in_jis_string_if_possible();
extern Object convert_to_jis_string_if_possible();
extern Object convert_to_katakana_if_possible();
extern Object copy_managed_lisp_string();
extern Object copy_out_current_wide_string();
extern Object copy_text_string_as_managed_lisp_string();
extern Object extend_current_gensym_string();
extern Object gensym_jis_code_to_contiguous();
extern Object gensym_string_substring();
extern Object get_list_of_choices_of_kanji_translation();
extern Object kfep_kka_p_update_kojin();
extern Object kka_p_batkanakan();
extern Object legal_gensym_jis_character_code_p();
extern Object lower_case_pw();
extern Object map_longest_possible_substring_using_jis_map();
extern Object note_kfep_conversion_choice();
extern Object number_of_characters_untranslated();
extern Object obtain_simple_gensym_string();
extern Object reclaim_gensym_string();
extern Object reclaim_slot_value();
extern Object reclaim_text_string();
extern Object regenerate_optimized_constant();
extern Object roman_kana_g2();
extern Object roman_kata_g2();
extern Object search_for_longest_prefix_with_kfep_word_choices();
extern Object slot_value_cons_1();
extern Object text_string_length();
extern Object tflush_stripped_kana_buffer_if_necessary();
extern Object twrite_character();
extern Object twrite_general_string();
extern Object twrite_wide_character();
extern Object unicode_lowercase_if_uppercase();
extern Object unicode_uppercase_if_lowercase();
extern Object wide_character_member();

#endif

/* variables/constants */
extern Object Allowable_non_alpha_characters_in_kfep_conversions;
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
extern Object Jis_kana_to_ascii;
extern Object Jis_offsets_for_y_kana_characters;
extern Object Jis_offsets_for_y_prefix_kana_characters;
extern Object Jis_x_0208_to_unicode_map;
DECLARE_VARIABLE_WITH_SYMBOL(Kana_to_ascii_map, Qkana_to_ascii_map);
extern Object Kfep_learning_capability_qm;
DECLARE_VARIABLE_WITH_SYMBOL(Maximum_length_of_kana_string, Qmaximum_length_of_kana_string);
extern Object Maximum_number_of_hiragana_bytes_to_translate;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_to_jis_x_0208_map, Qunicode_to_jis_x_0208_map);
