/* chars.h -- Header File for chars.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Kelement_type;
extern Object Kinitial_contents;
extern Object Kinitial_element;
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

extern Object alphabetic_gensym_character_p(Object,Object);
extern Object alphanumeric_gensym_character_p(Object,Object);
extern Object chestnut_floorf_function(Object,Object);
extern Object convert_2_byte_to_gensym_ksc5601(Object,Object);
extern Object gensym_jis_code_to_contiguous(Object);
extern Object gensym_ksc_code_to_contiguous(Object);
extern Object gensym_ksc_to_ksc(Object);
extern Object iso_8859_5_to_gensym_cyrillic(Object);
extern Object jis_to_shift_jis(Object);
extern Object ks2_bytes_to_ksc5601(Object,Object);
extern Object ksc_to_gensym_ksc(Object);
extern Object legal_gensym_jis_character_code_p(Object);
extern Object legal_gensym_ksc_character_code_p(Object);
extern Object legal_gensym_string_p(int,...);
extern Object make_cjk_code_mapping_vector(void);
extern Object make_gensym_character_string(Object,Object);
extern Object map_extended_utf_g_characters_to_unicode(Object,Object);
extern Object map_unicode_to_extended_utf_g_characters(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object numeric_gensym_character_p(Object,Object);
extern Object obtain_simple_gensym_string(Object);
extern Object regenerate_optimized_constant(Object);
extern Object set_cjk_code_mapping(Object,Object,Object);
extern Object unicode_general_punctuation_character_p(Object);
extern Object unicode_letterlike_symbol_p(Object);
extern Object unicode_line_separator_function(void);
extern Object unicode_tab_function(void);
extern Object utilize_cyrillic_character_a_list(void);
extern Object utilize_cyrillic_character_a_list_1(Object,Object,Object,Object,Object,Object);

#else

extern Object alphabetic_gensym_character_p();
extern Object alphanumeric_gensym_character_p();
extern Object chestnut_floorf_function();
extern Object convert_2_byte_to_gensym_ksc5601();
extern Object gensym_jis_code_to_contiguous();
extern Object gensym_ksc_code_to_contiguous();
extern Object gensym_ksc_to_ksc();
extern Object iso_8859_5_to_gensym_cyrillic();
extern Object jis_to_shift_jis();
extern Object ks2_bytes_to_ksc5601();
extern Object ksc_to_gensym_ksc();
extern Object legal_gensym_jis_character_code_p();
extern Object legal_gensym_ksc_character_code_p();
extern Object legal_gensym_string_p();
extern Object make_cjk_code_mapping_vector();
extern Object make_gensym_character_string();
extern Object map_extended_utf_g_characters_to_unicode();
extern Object map_unicode_to_extended_utf_g_characters();
extern Object mutate_global_property();
extern Object numeric_gensym_character_p();
extern Object obtain_simple_gensym_string();
extern Object regenerate_optimized_constant();
extern Object set_cjk_code_mapping();
extern Object unicode_general_punctuation_character_p();
extern Object unicode_letterlike_symbol_p();
extern Object unicode_line_separator_function();
extern Object unicode_tab_function();
extern Object utilize_cyrillic_character_a_list();
extern Object utilize_cyrillic_character_a_list_1();

#endif

/* variables/constants */
extern Object Char_backspace;
extern Object Char_control__;
extern Object Char_control_a;
extern Object Char_control_at;
extern Object Char_control_b;
extern Object Char_control_backslash;
extern Object Char_control_c;
extern Object Char_control_cbt;
extern Object Char_control_ct;
extern Object Char_control_d;
extern Object Char_control_e;
extern Object Char_control_f;
extern Object Char_control_g;
extern Object Char_control_h;
extern Object Char_control_i;
extern Object Char_control_j;
extern Object Char_control_k;
extern Object Char_control_l;
extern Object Char_control_m;
extern Object Char_control_n;
extern Object Char_control_o;
extern Object Char_control_obt;
extern Object Char_control_p;
extern Object Char_control_q;
extern Object Char_control_r;
extern Object Char_control_s;
extern Object Char_control_t;
extern Object Char_control_u;
extern Object Char_control_v;
extern Object Char_control_w;
extern Object Char_control_x;
extern Object Char_control_y;
extern Object Char_control_z;
extern Object Char_escape;
extern Object Char_linefeed;
extern Object Char_page;
extern Object Char_return;
extern Object Char_rubout;
extern Object Char_tab;
extern Object Cyrillic_character_a_list;
extern Object Cyrillic_gensym_character_code_for_key_name_prop;
#define Gb_high_byte_max FIX((SI_Long)119L)
#define Gb_high_byte_min FIX((SI_Long)33L)
#define Gb_low_byte_max FIX((SI_Long)126L)
#define Gb_low_byte_min FIX((SI_Long)33L)
#define Gensym_cyrillic_character_block_start FIX((SI_Long)8192L)
#define Gensym_general_punctuation_character_block_start FIX((SI_Long)4096L)
#define Gensym_letterlike_symbol_block_start FIX((SI_Long)4352L)
extern Object Gensym_to_unicode_full_row_map;
extern Object Gensym_unicode_row_correspondences;
#define Invalid_gensym_full_row FIX((SI_Long)246L)
#define Invalid_unicode_full_row FIX((SI_Long)7L)
#define Iso_8859_5_offset_within_cyrillic_character_block FIX((SI_Long)0L)
DECLARE_VARIABLE_WITH_SYMBOL(Iso_latin1_special_character_code_map, Qiso_latin1_special_character_code_map);
#define Jis_cyrillic_high_byte FIX((SI_Long)39L)
#define Jis_greek_high_byte FIX((SI_Long)38L)
#define Jis_high_byte_max FIX((SI_Long)116L)
#define Jis_high_byte_min FIX((SI_Long)33L)
#define Jis_hiragana_high_byte FIX((SI_Long)36L)
#define Jis_hiragana_start FIX((SI_Long)209L)
#define Jis_katakana_high_byte FIX((SI_Long)37L)
#define Jis_katakana_start FIX((SI_Long)292L)
extern Object Jis_last_contiguous_code;
#define Jis_level_1_kanji_high_byte FIX((SI_Long)48L)
#define Jis_level_1_kanji_start FIX((SI_Long)524L)
#define Jis_level_2_kanji_high_byte FIX((SI_Long)80L)
#define Jis_level_2_kanji_start FIX((SI_Long)3489L)
#define Jis_low_byte_max FIX((SI_Long)126L)
#define Jis_low_byte_min FIX((SI_Long)33L)
#define Jis_low_byte_offset FIX((SI_Long)0L)
#define Jis_lower_case_cyrillic_offset FIX((SI_Long)48L)
#define Jis_lower_case_cyrillic_start FIX((SI_Long)459L)
#define Jis_lower_case_greek_offset FIX((SI_Long)32L)
#define Jis_lower_case_greek_start FIX((SI_Long)402L)
#define Jis_lower_case_roman_offset FIX((SI_Long)64L)
#define Jis_lower_case_roman_start FIX((SI_Long)183L)
#define Jis_numbers_offset FIX((SI_Long)15L)
#define Jis_numbers_start FIX((SI_Long)147L)
#define Jis_roman_high_byte FIX((SI_Long)35L)
#define Jis_ruled_line_elements_high_byte FIX((SI_Long)40L)
#define Jis_ruled_line_elements_start FIX((SI_Long)492L)
#define Jis_symbols_1_high_byte FIX((SI_Long)33L)
#define Jis_symbols_1_start FIX((SI_Long)0L)
#define Jis_symbols_2_high_byte FIX((SI_Long)34L)
#define Jis_symbols_2_start FIX((SI_Long)94L)
#define Jis_symbols_90_1_offset FIX((SI_Long)25L)
#define Jis_symbols_90_1_start FIX((SI_Long)108L)
#define Jis_symbols_90_2_offset FIX((SI_Long)41L)
#define Jis_symbols_90_2_start FIX((SI_Long)116L)
#define Jis_symbols_90_3_offset FIX((SI_Long)59L)
#define Jis_symbols_90_3_start FIX((SI_Long)123L)
#define Jis_symbols_90_4_offset FIX((SI_Long)81L)
#define Jis_symbols_90_4_start FIX((SI_Long)138L)
#define Jis_symbols_90_5_offset FIX((SI_Long)93L)
#define Jis_symbols_90_5_start FIX((SI_Long)146L)
#define Jis_undefined_byte FIX((SI_Long)117L)
#define Jis_undefined_start FIX((SI_Long)6879L)
#define Jis_upper_case_cyrillic_start FIX((SI_Long)426L)
#define Jis_upper_case_greek_start FIX((SI_Long)378L)
#define Jis_upper_case_roman_offset FIX((SI_Long)32L)
#define Jis_upper_case_roman_start FIX((SI_Long)157L)
DECLARE_VARIABLE_WITH_SYMBOL(Key_cap_to_gensym_cyrillic_character_code_map, Qkey_cap_to_gensym_cyrillic_character_code_map);
DECLARE_VARIABLE_WITH_SYMBOL(Ksc_contiguous_character_group_lengths, Qksc_contiguous_character_group_lengths);
#define Ksc_hangul_start FIX((SI_Long)986L)
#define Ksc_hanja_start FIX((SI_Long)3336L)
#define Ksc_high_byte_max FIX((SI_Long)125L)
#define Ksc_high_byte_min FIX((SI_Long)33L)
extern Object Ksc_last_contiguous_code;
#define Ksc_low_byte_max FIX((SI_Long)126L)
#define Ksc_low_byte_min FIX((SI_Long)33L)
#define Ksc_low_byte_offset FIX((SI_Long)94L)
#define Ksc_symbols_1_start FIX((SI_Long)0L)
#define Ksc_undefined_start FIX((SI_Long)8224L)
extern Object Maximum_suggested_length_for_simple_gensym_strings;
DECLARE_VARIABLE_WITH_SYMBOL(Msw_cyrillic_code_map, Qmsw_cyrillic_code_map);
#define Number_of_contiguous_gb2312_codes FIX((SI_Long)8178L)
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_ksc_codes, Qnumber_of_ksc_codes);
DECLARE_VARIABLE_WITH_SYMBOL(Reverse_iso_latin1_special_character_code_map, Qreverse_iso_latin1_special_character_code_map);
DECLARE_VARIABLE_WITH_SYMBOL(Roman_font_special_character_code_map, Qroman_font_special_character_code_map);
#define Unicode_cyrillic_character_block_start FIX((SI_Long)1024L)
#define Unicode_general_punctuation_character_block_start FIX((SI_Long)8192L)
#define Unicode_hebrew_character_block_end FIX((SI_Long)1524L)
#define Unicode_hebrew_character_block_start FIX((SI_Long)1456L)
#define Unicode_hebrew_precomposed_character_block_end FIX((SI_Long)64335L)
#define Unicode_hebrew_precomposed_character_block_start FIX((SI_Long)64285L)
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_index_to_slavic_font_direct_index_map, Qunicode_index_to_slavic_font_direct_index_map);
extern Object Unicode_jis_x_0208_mapping_hand_edits;
#define Unicode_letterlike_symbol_block_start FIX((SI_Long)8448L)
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_offset_for_gensym_cyrillic, Qunicode_offset_for_gensym_cyrillic);
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_offset_for_gensym_general_punctuation, Qunicode_offset_for_gensym_general_punctuation);
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_offset_for_gensym_letterlike_symbol, Qunicode_offset_for_gensym_letterlike_symbol);
#define Unicode_thai_character_block_end FIX((SI_Long)3711L)
#define Unicode_thai_character_block_start FIX((SI_Long)3584L)
#define Unicode_thai_glyph_variants_end FIX((SI_Long)63247L)
#define Unicode_thai_glyph_variants_start FIX((SI_Long)63232L)
extern Object Unicode_to_gensym_full_row_map;
DECLARE_VARIABLE_WITH_SYMBOL(Whitespace_characters, Qwhitespace_characters);
DECLARE_VARIABLE_WITH_SYMBOL(Whitespace_wide_characters, Qwhitespace_wide_characters);
