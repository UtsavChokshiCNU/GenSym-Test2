/* kydfs.h -- Header File for kydfs.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qstar;
extern Object Qplus;
extern Object Qminus;
extern Object Qslash;
extern Object Qnum_lt;
extern Object Qnum_eq;
extern Object Qnum_gt;
extern Object Qbreak;
extern Object Qclear_input;
extern Object Qdelete;
extern Object Qfind;
extern Object Qfunction;
extern Object Qprint;
extern Object Qreturn;
extern Object Qspace;

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

extern Object abort_g2(int,...);
extern Object classify_character_for_text_line_drawing_function(Object);
extern Object convert_key_code_to_gensym_character(Object);
extern Object convert_key_code_to_gensym_cyrillic_character_code(Object);
extern Object convert_key_code_to_key_symbol(Object);
extern Object convert_key_code_to_unicode(Object);
extern Object define_key_symbol_1(Object,Object,Object,Object,Object,Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object map_extended_utf_g_characters_to_unicode(Object,Object);
extern Object map_gensym_han_character_code_to_unicode(Object);
extern Object map_unicode_to_gensym_han_character_code(Object);
extern Object memq_function(Object,Object);
extern Object mouse_key_code_button_name_symbol(Object);
extern Object printable_character_key_code_p(Object);
extern Object pseudo_key_code_p(Object);

#else

extern Object abort_g2();
extern Object classify_character_for_text_line_drawing_function();
extern Object convert_key_code_to_gensym_character();
extern Object convert_key_code_to_gensym_cyrillic_character_code();
extern Object convert_key_code_to_key_symbol();
extern Object convert_key_code_to_unicode();
extern Object define_key_symbol_1();
extern Object getfq_function_no_default();
extern Object map_extended_utf_g_characters_to_unicode();
extern Object map_gensym_han_character_code_to_unicode();
extern Object map_unicode_to_gensym_han_character_code();
extern Object memq_function();
extern Object mouse_key_code_button_name_symbol();
extern Object printable_character_key_code_p();
extern Object pseudo_key_code_p();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Current_extended_utf_g_low_half_character_qm, Qcurrent_extended_utf_g_low_half_character_qm);
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
extern Object Gensym_to_unicode_full_row_map;
#define Invalid_gensym_full_row FIX((SI_Long)246L)
#define Invalid_unicode_full_row FIX((SI_Long)7L)
DECLARE_VARIABLE_WITH_SYMBOL(Iso_latin1_special_character_code_map, Qiso_latin1_special_character_code_map);
DECLARE_VARIABLE_WITH_SYMBOL(Key_index_to_key_symbol_array, Qkey_index_to_key_symbol_array);
DECLARE_VARIABLE_WITH_SYMBOL(Pseudo_keysyms, Qpseudo_keysyms);
DECLARE_VARIABLE_WITH_SYMBOL(Reverse_iso_latin1_special_character_code_map, Qreverse_iso_latin1_special_character_code_map);
DECLARE_VARIABLE_WITH_SYMBOL(Row, Qrow);
#define Unicode_bit FIX((SI_Long)16777216L)
extern Object Unicode_character_bits;
extern Object Unicode_to_gensym_full_row_map;
