/* chars2.h -- Header File for chars2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */

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

extern Object gensym_jis_code_to_contiguous(Object);
extern Object gensym_ksc_code_to_contiguous(Object);
extern Object legal_gensym_jis_character_code_p(Object);
extern Object legal_gensym_ksc_character_code_p(Object);
extern Object map_gensym_han_character_code_to_unicode(Object);
extern Object map_unicode_to_gensym_character_code_with_cjk_neutrality(Object);
extern Object map_unicode_to_gensym_han_character_code(Object);
extern Object unicode_han_character_p(Object);
extern Object wide_character_is_simple_gensym_character_p(Object);
extern Object wide_character_p_function(Object);

#else

extern Object gensym_jis_code_to_contiguous();
extern Object gensym_ksc_code_to_contiguous();
extern Object legal_gensym_jis_character_code_p();
extern Object legal_gensym_ksc_character_code_p();
extern Object map_gensym_han_character_code_to_unicode();
extern Object map_unicode_to_gensym_character_code_with_cjk_neutrality();
extern Object map_unicode_to_gensym_han_character_code();
extern Object unicode_han_character_p();
extern Object wide_character_is_simple_gensym_character_p();
extern Object wide_character_p_function();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Current_extended_utf_g_low_half_character_qm, Qcurrent_extended_utf_g_low_half_character_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_bullet, Qgensym_char_or_code_for_bullet);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_capital_ligature_oe, Qgensym_char_or_code_for_capital_ligature_oe);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_linebreak, Qgensym_char_or_code_for_linebreak);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_paragraph_break, Qgensym_char_or_code_for_paragraph_break);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_small_letter_f_with_hook, Qgensym_char_or_code_for_small_letter_f_with_hook);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_small_ligature_oe, Qgensym_char_or_code_for_small_ligature_oe);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_trade_mark_sign, Qgensym_char_or_code_for_trade_mark_sign);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_bullet, Qgensym_code_for_bullet);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_capital_ligature_oe, Qgensym_code_for_capital_ligature_oe);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_linebreak, Qgensym_code_for_linebreak);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_paragraph_break, Qgensym_code_for_paragraph_break);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_small_letter_f_with_hook, Qgensym_code_for_small_letter_f_with_hook);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_small_ligature_oe, Qgensym_code_for_small_ligature_oe);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_code_for_trade_mark_sign, Qgensym_code_for_trade_mark_sign);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_bullet_qm, Qgensym_esc_for_bullet_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_capital_ligature_oe_qm, Qgensym_esc_for_capital_ligature_oe_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_linebreak_qm, Qgensym_esc_for_linebreak_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_paragraph_break_qm, Qgensym_esc_for_paragraph_break_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_small_letter_f_with_hook_qm, Qgensym_esc_for_small_letter_f_with_hook_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_small_ligature_oe_qm, Qgensym_esc_for_small_ligature_oe_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_trade_mark_sign_qm, Qgensym_esc_for_trade_mark_sign_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Han_interpretation_mode, Qhan_interpretation_mode);
#define Invalid_gensym_full_row FIX((SI_Long)246L)
extern Object Jis_x_0208_to_unicode_map;
extern Object Ks_c_5601_to_unicode_map;
#define Pct_ FIX((SI_Long)45L)
#define Pct_0 FIX((SI_Long)48L)
#define Pct_1 FIX((SI_Long)49L)
#define Pct_2 FIX((SI_Long)50L)
#define Pct_3 FIX((SI_Long)51L)
#define Pct_4 FIX((SI_Long)52L)
#define Pct_5 FIX((SI_Long)53L)
#define Pct_6 FIX((SI_Long)54L)
#define Pct_7 FIX((SI_Long)55L)
#define Pct_8 FIX((SI_Long)56L)
#define Pct_9 FIX((SI_Long)57L)
#define Pct_a FIX((SI_Long)65L)
#define Pct_and FIX((SI_Long)38L)
#define Pct_at FIX((SI_Long)64L)
#define Pct_b FIX((SI_Long)66L)
#define Pct_bq FIX((SI_Long)96L)
#define Pct_bs FIX((SI_Long)92L)
#define Pct_bullet FIX((SI_Long)8226L)
#define Pct_c FIX((SI_Long)67L)
#define Pct_capital_ligature_oe FIX((SI_Long)338L)
#define Pct_cb FIX((SI_Long)125L)
#define Pct_cbt FIX((SI_Long)93L)
#define Pct_cent_sign FIX((SI_Long)162L)
#define Pct_cm FIX((SI_Long)44L)
#define Pct_col FIX((SI_Long)58L)
#define Pct_copyright_sign FIX((SI_Long)169L)
#define Pct_cp FIX((SI_Long)41L)
#define Pct_ct FIX((SI_Long)94L)
#define Pct_d FIX((SI_Long)68L)
#define Pct_dol FIX((SI_Long)36L)
#define Pct_dot FIX((SI_Long)46L)
#define Pct_dq FIX((SI_Long)34L)
#define Pct_e FIX((SI_Long)69L)
#define Pct_em_space FIX((SI_Long)8193L)
#define Pct_en_space FIX((SI_Long)8194L)
#define Pct_eq FIX((SI_Long)61L)
#define Pct_esc FIX((SI_Long)27L)
#define Pct_escape FIX((SI_Long)27L)
#define Pct_euro_sign FIX((SI_Long)8364L)
#define Pct_ex FIX((SI_Long)33L)
#define Pct_f FIX((SI_Long)70L)
#define Pct_fixed_width_space FIX((SI_Long)8199L)
#define Pct_g FIX((SI_Long)71L)
#define Pct_gt FIX((SI_Long)62L)
#define Pct_h FIX((SI_Long)72L)
#define Pct_hair_space FIX((SI_Long)8202L)
#define Pct_i FIX((SI_Long)73L)
#define Pct_inverted_exclamation_point FIX((SI_Long)161L)
#define Pct_inverted_question_mark FIX((SI_Long)191L)
#define Pct_j FIX((SI_Long)74L)
#define Pct_k FIX((SI_Long)75L)
#define Pct_l FIX((SI_Long)76L)
#define Pct_latin_small_letter_f_with_hook FIX((SI_Long)402L)
#define Pct_left_pointing_double_angle_quotation_mark FIX((SI_Long)171L)
#define Pct_line_separator FIX((SI_Long)8232L)
#define Pct_linefeed FIX((SI_Long)10L)
#define Pct_lt FIX((SI_Long)60L)
#define Pct_m FIX((SI_Long)77L)
#define Pct_n FIX((SI_Long)78L)
#define Pct_newline FIX((SI_Long)10L)
#define Pct_no FIX((SI_Long)35L)
#define Pct_no_break_space FIX((SI_Long)160L)
#define Pct_null FIX((SI_Long)0L)
#define Pct_o FIX((SI_Long)79L)
#define Pct_ob FIX((SI_Long)123L)
#define Pct_obt FIX((SI_Long)91L)
#define Pct_op FIX((SI_Long)40L)
#define Pct_or FIX((SI_Long)124L)
#define Pct_ordinary_space FIX((SI_Long)32L)
#define Pct_p FIX((SI_Long)80L)
#define Pct_page FIX((SI_Long)12L)
#define Pct_paragraph_separator FIX((SI_Long)8233L)
#define Pct_pct FIX((SI_Long)37L)
#define Pct_plus FIX((SI_Long)43L)
#define Pct_pound_sign FIX((SI_Long)163L)
#define Pct_q FIX((SI_Long)81L)
#define Pct_qm FIX((SI_Long)63L)
#define Pct_qu FIX((SI_Long)39L)
#define Pct_r FIX((SI_Long)82L)
#define Pct_registered_sign FIX((SI_Long)174L)
#define Pct_return FIX((SI_Long)13L)
#define Pct_right_pointing_double_angle_quotation_mark FIX((SI_Long)187L)
#define Pct_s FIX((SI_Long)83L)
#define Pct_sc FIX((SI_Long)59L)
#define Pct_sl FIX((SI_Long)47L)
#define Pct_small_ligature_oe FIX((SI_Long)339L)
#define Pct_soft_hyphen FIX((SI_Long)173L)
#define Pct_sp FIX((SI_Long)32L)
#define Pct_space FIX((SI_Long)32L)
#define Pct_star FIX((SI_Long)42L)
#define Pct_t FIX((SI_Long)84L)
#define Pct_tab FIX((SI_Long)9L)
#define Pct_thin_space FIX((SI_Long)8201L)
#define Pct_tl FIX((SI_Long)126L)
#define Pct_trade_mark_sign FIX((SI_Long)8482L)
#define Pct_u FIX((SI_Long)85L)
#define Pct_v FIX((SI_Long)86L)
#define Pct_w FIX((SI_Long)87L)
#define Pct_x FIX((SI_Long)88L)
#define Pct_y FIX((SI_Long)89L)
#define Pct_yen_sign FIX((SI_Long)165L)
#define Pct_z FIX((SI_Long)90L)
#define Pct_zero_width_joiner FIX((SI_Long)8205L)
#define Pct_zero_width_no_break_space FIX((SI_Long)65279L)
#define Pct_zero_width_space FIX((SI_Long)8203L)
DECLARE_VARIABLE_WITH_SYMBOL(Row, Qrow);
extern Object Unicode_to_gensym_full_row_map;
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_to_jis_x_0208_map, Qunicode_to_jis_x_0208_map);
DECLARE_VARIABLE_WITH_SYMBOL(Unicode_to_ks_c_5601_map, Qunicode_to_ks_c_5601_map);
#define ab_Pct_ FIX((SI_Long)95L)
#define ab_Pct_a FIX((SI_Long)97L)
#define ab_Pct_b FIX((SI_Long)98L)
#define ab_Pct_c FIX((SI_Long)99L)
#define ab_Pct_d FIX((SI_Long)100L)
#define ab_Pct_e FIX((SI_Long)101L)
#define ab_Pct_f FIX((SI_Long)102L)
#define ab_Pct_g FIX((SI_Long)103L)
#define ab_Pct_h FIX((SI_Long)104L)
#define ab_Pct_i FIX((SI_Long)105L)
#define ab_Pct_j FIX((SI_Long)106L)
#define ab_Pct_k FIX((SI_Long)107L)
#define ab_Pct_l FIX((SI_Long)108L)
#define ab_Pct_m FIX((SI_Long)109L)
#define ab_Pct_n FIX((SI_Long)110L)
#define ab_Pct_o FIX((SI_Long)111L)
#define ab_Pct_p FIX((SI_Long)112L)
#define ab_Pct_q FIX((SI_Long)113L)
#define ab_Pct_r FIX((SI_Long)114L)
#define ab_Pct_s FIX((SI_Long)115L)
#define ab_Pct_sp FIX((SI_Long)32L)
#define ab_Pct_t FIX((SI_Long)116L)
#define ab_Pct_u FIX((SI_Long)117L)
#define ab_Pct_v FIX((SI_Long)118L)
#define ab_Pct_w FIX((SI_Long)119L)
#define ab_Pct_x FIX((SI_Long)120L)
#define ab_Pct_y FIX((SI_Long)121L)
#define ab_Pct_z FIX((SI_Long)122L)
