/* f-keys.h -- Header File for f-keys.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Kcapitalize;
extern Object Kdowncase;
extern Object Qotherwise;
extern Object Qunsigned_byte;
extern Object Kupcase;

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
extern Object canonicalize_gensym_key_code(Object);
extern Object convert_key_code_to_key_symbol(Object);
extern Object convert_key_symbol_to_key_code(int,...);
extern Object convert_mouse_code_to_mouse_drag(Object);
extern Object convert_mouse_code_to_mouse_select(Object);
extern Object copy_out_current_wide_string(void);
extern Object extend_current_gensym_string(int,...);
extern Object find_in_text_string(Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object intern_text_string(int,...);
extern Object key_code_from_character(Object);
extern Object key_code_from_list(Object);
extern Object key_code_from_symbol(Object);
extern Object key_code_function(Object,Object,Object);
extern Object key_code_matches_key_pattern_p_function(Object,Object);
extern Object key_code_mouse_button_name(Object);
extern Object lengthw(Object);
extern Object lt_alphabetic_gt_key_pattern(Object);
extern Object lt_any_keyboard_event_gt_key_pattern(Object);
extern Object lt_delete_backward_keys_gt_key_pattern(Object);
extern Object lt_delete_forward_keys_gt_key_pattern(Object);
extern Object lt_mouse_down_gt_key_pattern(Object);
extern Object lt_mouse_drag_gt_key_pattern(Object);
extern Object lt_mouse_gesture_gt_key_pattern(Object);
extern Object lt_mouse_hover_gt_key_pattern(Object);
extern Object lt_mouse_left_down_gt_key_pattern(Object);
extern Object lt_mouse_left_drag_gt_key_pattern(Object);
extern Object lt_mouse_left_select_gt_key_pattern(Object);
extern Object lt_mouse_middle_down_gt_key_pattern(Object);
extern Object lt_mouse_middle_select_gt_key_pattern(Object);
extern Object lt_mouse_motion_gt_key_pattern(Object);
extern Object lt_mouse_right_down_gt_key_pattern(Object);
extern Object lt_mouse_right_drag_gt_key_pattern(Object);
extern Object lt_mouse_right_select_gt_key_pattern(Object);
extern Object lt_mouse_select_gt_key_pattern(Object);
extern Object lt_mouse_up_gt_key_pattern(Object);
extern Object lt_native_menu_choice_gt_key_pattern(Object);
extern Object lt_printing_character_gt_key_pattern(Object);
extern Object lt_pseudo_keycode_gt_key_pattern(Object);
extern Object lt_standard_abort_keys_gt_key_pattern(Object);
extern Object lt_standard_enter_keys_gt_key_pattern(Object);
extern Object lt_standard_help_keys_gt_key_pattern(Object);
extern Object lt_standard_newline_keys_gt_key_pattern(Object);
extern Object lt_unicode_character_gt_key_pattern(Object);
extern Object mouse_motion_key_code(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object nstring_upcasew(Object);
extern Object otherwise_key_pattern(Object);
extern Object parseable_symbol_from_key_code(Object);
extern Object printable_character_key_code_p(Object);
extern Object pseudo_key_code_p(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object split_symbol(Object,Object);
extern Object string_upcasew(Object);
extern Object symbol_from_key_code(Object);
extern Object symbol_name_text_string(Object);
extern Object text_string_p(Object);
extern Object tformat(int,...);
extern Object twrite(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_character_of_keysym(Object,Object,Object);
extern Object twrite_general_string(Object);
extern Object twrite_key_code(Object);
extern Object twrite_key_modifier_bits(Object,Object);
extern Object twrite_key_pattern(Object);
extern Object twrite_key_patterns(Object);
extern Object twrite_key_patterns_and_classes(Object);
extern Object twrite_list_function(Object,Object,Object,Object,Object);
extern Object twrite_shortcut_key(Object);
extern Object twrite_symbol(int,...);
extern Object twrite_symbol_simply(Object);
extern Object twrite_wide_character(Object);
extern Object unicode_lowercase_if_uppercase(Object);
extern Object unicode_uppercase_if_lowercase(Object);

#else

extern Object allocate_byte_vector_16();
extern Object canonicalize_gensym_key_code();
extern Object convert_key_code_to_key_symbol();
extern Object convert_key_symbol_to_key_code();
extern Object convert_mouse_code_to_mouse_drag();
extern Object convert_mouse_code_to_mouse_select();
extern Object copy_out_current_wide_string();
extern Object extend_current_gensym_string();
extern Object find_in_text_string();
extern Object getfq_function_no_default();
extern Object intern_text_string();
extern Object key_code_from_character();
extern Object key_code_from_list();
extern Object key_code_from_symbol();
extern Object key_code_function();
extern Object key_code_matches_key_pattern_p_function();
extern Object key_code_mouse_button_name();
extern Object lengthw();
extern Object lt_alphabetic_gt_key_pattern();
extern Object lt_any_keyboard_event_gt_key_pattern();
extern Object lt_delete_backward_keys_gt_key_pattern();
extern Object lt_delete_forward_keys_gt_key_pattern();
extern Object lt_mouse_down_gt_key_pattern();
extern Object lt_mouse_drag_gt_key_pattern();
extern Object lt_mouse_gesture_gt_key_pattern();
extern Object lt_mouse_hover_gt_key_pattern();
extern Object lt_mouse_left_down_gt_key_pattern();
extern Object lt_mouse_left_drag_gt_key_pattern();
extern Object lt_mouse_left_select_gt_key_pattern();
extern Object lt_mouse_middle_down_gt_key_pattern();
extern Object lt_mouse_middle_select_gt_key_pattern();
extern Object lt_mouse_motion_gt_key_pattern();
extern Object lt_mouse_right_down_gt_key_pattern();
extern Object lt_mouse_right_drag_gt_key_pattern();
extern Object lt_mouse_right_select_gt_key_pattern();
extern Object lt_mouse_select_gt_key_pattern();
extern Object lt_mouse_up_gt_key_pattern();
extern Object lt_native_menu_choice_gt_key_pattern();
extern Object lt_printing_character_gt_key_pattern();
extern Object lt_pseudo_keycode_gt_key_pattern();
extern Object lt_standard_abort_keys_gt_key_pattern();
extern Object lt_standard_enter_keys_gt_key_pattern();
extern Object lt_standard_help_keys_gt_key_pattern();
extern Object lt_standard_newline_keys_gt_key_pattern();
extern Object lt_unicode_character_gt_key_pattern();
extern Object mouse_motion_key_code();
extern Object mutate_global_property();
extern Object nstring_upcasew();
extern Object otherwise_key_pattern();
extern Object parseable_symbol_from_key_code();
extern Object printable_character_key_code_p();
extern Object pseudo_key_code_p();
extern Object reclaim_gensym_list_1();
extern Object split_symbol();
extern Object string_upcasew();
extern Object symbol_from_key_code();
extern Object symbol_name_text_string();
extern Object text_string_p();
extern Object tformat();
extern Object twrite();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_character_of_keysym();
extern Object twrite_general_string();
extern Object twrite_key_code();
extern Object twrite_key_modifier_bits();
extern Object twrite_key_pattern();
extern Object twrite_key_patterns();
extern Object twrite_key_patterns_and_classes();
extern Object twrite_list_function();
extern Object twrite_shortcut_key();
extern Object twrite_symbol();
extern Object twrite_symbol_simply();
extern Object twrite_wide_character();
extern Object unicode_lowercase_if_uppercase();
extern Object unicode_uppercase_if_lowercase();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Ab_package_1, Qab_package_1);
#define Alternate_bit FIX((SI_Long)524288L)
#define Caps_lock_bit FIX((SI_Long)131072L)
extern Object Characters_requiring_quotation_in_key_symbols;
#define Control_bit FIX((SI_Long)8388608L)
DECLARE_VARIABLE_WITH_SYMBOL(Current_gensym_string, Qcurrent_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
#define Double_bit FIX((SI_Long)65536L)
extern Object Double_mask;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_gensym_string, Qfill_pointer_for_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
#define Illegal_key_code FIX((SI_Long)-1L)
extern Object Illegal_key_index;
extern Object Key_index_bits;
extern Object Key_modifier_bits;
extern Object Key_pattern_abbreviation_prop;
extern Object Key_pattern_named_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Keyword_package_1, Qkeyword_package_1);
#define Menu_bit FIX((SI_Long)33554432L)
#define Meta_bit FIX((SI_Long)4194304L)
#define Shift_bit FIX((SI_Long)262144L)
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_gensym_string, Qtotal_length_of_current_gensym_string);
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Twrite_control_as_ctrl, Qtwrite_control_as_ctrl);
#define Unicode_bit FIX((SI_Long)16777216L)
extern Object Unicode_character_bits;
extern Object Unicode_mask;
DECLARE_VARIABLE_WITH_SYMBOL(Write_symbols_parsably_qm, Qwrite_symbols_parsably_qm);
