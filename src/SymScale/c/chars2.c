/* chars2.c
 * Input file:  characters2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "chars2.h"


DEFINE_VARIABLE_WITH_SYMBOL(Han_interpretation_mode, Qhan_interpretation_mode);

/* UNICODE-HAN-CHARACTER-P */
Object unicode_han_character_p(unicode)
    Object unicode;
{
    x_note_fn_call(19,0);
    return VALUES_1(unicode);
}

static Object Qkorean;             /* korean */

/* MAP-UNICODE-TO-GENSYM-HAN-CHARACTER-CODE */
Object map_unicode_to_gensym_han_character_code(unicode)
    Object unicode;
{
    Object cjk_code, cjk_code_mapping_vector, l, temp_1;
    SI_Long temp;

    x_note_fn_call(19,1);
    if (EQ(Han_interpretation_mode,Qkorean)) {
	cjk_code = unicode;
	cjk_code_mapping_vector = Unicode_to_ks_c_5601_map;
	temp = IFIX(cjk_code) % (SI_Long)307L;
	l = ISVREF(cjk_code_mapping_vector,temp);
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (FIXNUM_EQ(CAR(l),cjk_code)) {
	    temp_1 = CADR(l);
	    goto end_1;
	}
	l = CDDR(l);
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_1:;
	if (temp_1);
	else {
	    cjk_code = unicode;
	    cjk_code_mapping_vector = Unicode_to_jis_x_0208_map;
	    temp = IFIX(cjk_code) % (SI_Long)307L;
	    l = ISVREF(cjk_code_mapping_vector,temp);
	  next_loop_1:
	    if ( !TRUEP(l))
		goto end_loop_1;
	    if (FIXNUM_EQ(CAR(l),cjk_code)) {
		temp_1 = CADR(l);
		goto end_2;
	    }
	    l = CDDR(l);
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = Qnil;
	  end_2:;
	}
    }
    else {
	cjk_code = unicode;
	cjk_code_mapping_vector = Unicode_to_jis_x_0208_map;
	temp = IFIX(cjk_code) % (SI_Long)307L;
	l = ISVREF(cjk_code_mapping_vector,temp);
      next_loop_2:
	if ( !TRUEP(l))
	    goto end_loop_2;
	if (FIXNUM_EQ(CAR(l),cjk_code)) {
	    temp_1 = CADR(l);
	    goto end_3;
	}
	l = CDDR(l);
	goto next_loop_2;
      end_loop_2:
	temp_1 = Qnil;
      end_3:;
	if (temp_1);
	else {
	    cjk_code = unicode;
	    cjk_code_mapping_vector = Unicode_to_ks_c_5601_map;
	    temp = IFIX(cjk_code) % (SI_Long)307L;
	    l = ISVREF(cjk_code_mapping_vector,temp);
	  next_loop_3:
	    if ( !TRUEP(l))
		goto end_loop_3;
	    if (FIXNUM_EQ(CAR(l),cjk_code)) {
		temp_1 = CADR(l);
		goto end_4;
	    }
	    l = CDDR(l);
	    goto next_loop_3;
	  end_loop_3:
	    temp_1 = Qnil;
	  end_4:;
	}
    }
    return VALUES_1(temp_1);
}

/* MAP-GENSYM-HAN-CHARACTER-CODE-TO-UNICODE */
Object map_gensym_han_character_code_to_unicode(gensym_character_code)
    Object gensym_character_code;
{
    Object contiguous_code_qm, temp;

    x_note_fn_call(19,2);
    if (EQ(Han_interpretation_mode,Qkorean)) {
	if (legal_gensym_ksc_character_code_p(gensym_character_code)) {
	    contiguous_code_qm = 
		    gensym_ksc_code_to_contiguous(gensym_character_code);
	    temp = contiguous_code_qm ? 
		    FIX(UBYTE_16_ISAREF_1(Ks_c_5601_to_unicode_map,
		    IFIX(contiguous_code_qm))) : Nil;
	}
	else
	    temp = Nil;
	if (temp);
	else if (legal_gensym_jis_character_code_p(gensym_character_code)) {
	    contiguous_code_qm = 
		    gensym_jis_code_to_contiguous(gensym_character_code);
	    temp = contiguous_code_qm ? 
		    FIX(UBYTE_16_ISAREF_1(Jis_x_0208_to_unicode_map,
		    IFIX(contiguous_code_qm))) : Nil;
	}
	else
	    temp = Nil;
    }
    else {
	if (legal_gensym_jis_character_code_p(gensym_character_code)) {
	    contiguous_code_qm = 
		    gensym_jis_code_to_contiguous(gensym_character_code);
	    temp = contiguous_code_qm ? 
		    FIX(UBYTE_16_ISAREF_1(Jis_x_0208_to_unicode_map,
		    IFIX(contiguous_code_qm))) : Nil;
	}
	else
	    temp = Nil;
	if (temp);
	else if (legal_gensym_ksc_character_code_p(gensym_character_code)) {
	    contiguous_code_qm = 
		    gensym_ksc_code_to_contiguous(gensym_character_code);
	    temp = contiguous_code_qm ? 
		    FIX(UBYTE_16_ISAREF_1(Ks_c_5601_to_unicode_map,
		    IFIX(contiguous_code_qm))) : Nil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_code_for_linebreak, Qgensym_code_for_linebreak);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_linebreak, Qgensym_char_or_code_for_linebreak);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_linebreak_qm, Qgensym_esc_for_linebreak_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_code_for_paragraph_break, Qgensym_code_for_paragraph_break);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_paragraph_break, Qgensym_char_or_code_for_paragraph_break);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_paragraph_break_qm, Qgensym_esc_for_paragraph_break_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_code_for_capital_ligature_oe, Qgensym_code_for_capital_ligature_oe);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_capital_ligature_oe, Qgensym_char_or_code_for_capital_ligature_oe);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_capital_ligature_oe_qm, Qgensym_esc_for_capital_ligature_oe_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_code_for_small_ligature_oe, Qgensym_code_for_small_ligature_oe);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_small_ligature_oe, Qgensym_char_or_code_for_small_ligature_oe);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_small_ligature_oe_qm, Qgensym_esc_for_small_ligature_oe_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_code_for_bullet, Qgensym_code_for_bullet);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_bullet, Qgensym_char_or_code_for_bullet);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_bullet_qm, Qgensym_esc_for_bullet_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_code_for_small_letter_f_with_hook, Qgensym_code_for_small_letter_f_with_hook);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_small_letter_f_with_hook, Qgensym_char_or_code_for_small_letter_f_with_hook);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_small_letter_f_with_hook_qm, Qgensym_esc_for_small_letter_f_with_hook_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_code_for_trade_mark_sign, Qgensym_code_for_trade_mark_sign);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_char_or_code_for_trade_mark_sign, Qgensym_char_or_code_for_trade_mark_sign);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_esc_for_trade_mark_sign_qm, Qgensym_esc_for_trade_mark_sign_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_extended_utf_g_low_half_character_qm, Qcurrent_extended_utf_g_low_half_character_qm);

/* WIDE-CHARACTER-IS-SIMPLE-GENSYM-CHARACTER-P */
Object wide_character_is_simple_gensym_character_p(wide_character)
    Object wide_character;
{
    Object code;

    x_note_fn_call(19,3);
    code = wide_character;
    return VALUES_1(IFIX(code) < (SI_Long)127L ? ( !((SI_Long)64L == 
	    IFIX(code) || (SI_Long)126L == IFIX(code) || (SI_Long)92L == 
	    IFIX(code)) ? T : Nil) : Qnil);
}

/* MAP-UNICODE-TO-GENSYM-CHARACTER-CODE-WITH-CJK-NEUTRALITY */
Object map_unicode_to_gensym_character_code_with_cjk_neutrality(unicode)
    Object unicode;
{
    Object code, row, temp;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1;
    Declare_special(1);

    x_note_fn_call(19,4);
    code = unicode;
    if (IFIX(code) < (SI_Long)127L &&  !((SI_Long)64L == IFIX(code) || 
	    (SI_Long)126L == IFIX(code) || (SI_Long)92L == IFIX(code)))
	return VALUES_1(unicode);
    else {
	row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
	      temp = FIX(gensymed_symbol + gensymed_symbol_1);
	  }
	  else
	      temp = Nil;
	POP_SPECIAL();
	if (temp)
	    return VALUES_1(temp);
	else {
	    gensymed_symbol = (SI_Long)63488L;
	    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
	    return VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
		    FIX((SI_Long)63232L + (IFIX(unicode) >>  -  - 
		    (SI_Long)8L)));
	}
    }
}

/* WIDE-CHARACTER-P-FUNCTION */
Object wide_character_p_function(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(19,5);
    temp = FIXNUMP(thing) ? T : Nil;
    return VALUES_1(temp);
}

void characters2_INIT()
{
    Object row;
    SI_Long unicode, gensym_full_row, gensymed_symbol, gensymed_symbol_1;
    Object Qpct_tl, AB_package, Qpct_cb, Qpct_or, Qpct_ob, QPCT_Z, QPCT_Y;
    Object QPCT_X, QPCT_W, QPCT_V, QPCT_U, QPCT_T, QPCT_S, QPCT_R, QPCT_Q;
    Object QPCT_P, QPCT_O, QPCT_N, QPCT_M, QPCT_L, QPCT_K, QPCT_J, QPCT_I;
    Object QPCT_H, QPCT_G, QPCT_F, QPCT_E, QPCT_D, QPCT_C, QPCT_B, QPCT_A;
    Object Qpct_bq, Qab_pct_, Qpct_ct, Qpct_cbt, Qpct_bs, Qpct_obt, Qpct_z;
    Object Qpct_y, Qpct_x, Qpct_w, Qpct_v, Qpct_u, Qpct_t, Qpct_s, Qpct_r;
    Object Qpct_q, Qpct_p, Qpct_o, Qpct_n, Qpct_m, Qpct_l, Qpct_k, Qpct_j;
    Object Qpct_i, Qpct_h, Qpct_g, Qpct_f, Qpct_e, Qpct_d, Qpct_c, Qpct_b;
    Object Qpct_a, Qpct_at, Qpct_qm, Qpct_gt, Qpct_eq, Qpct_lt, Qpct_sc;
    Object Qpct_col, Qpct_9, Qpct_8, Qpct_7, Qpct_6, Qpct_5, Qpct_4, Qpct_3;
    Object Qpct_2, Qpct_1, Qpct_0, Qpct_sl, Qpct_dot, Qpct_, Qpct_cm;
    Object Qpct_plus, Qpct_star, Qpct_cp, Qpct_op, Qpct_qu, Qpct_and, Qpct_pct;
    Object Qpct_dol, Qpct_no, Qpct_dq, Qpct_ex, Qab_pct_sp, Qpct_euro_sign;
    Object Qpct_inverted_question_mark;
    Object Qpct_left_pointing_double_angle_quotation_mark;
    Object Qpct_right_pointing_double_angle_quotation_mark, Qpct_yen_sign;
    Object Qpct_pound_sign, Qpct_cent_sign, Qpct_inverted_exclamation_point;
    Object Qpct_zero_width_joiner, Qpct_zero_width_space, Qpct_em_space;
    Object Qpct_en_space, Qpct_thin_space, Qpct_hair_space;
    Object Qpct_latin_small_letter_f_with_hook, Qpct_bullet;
    Object Qpct_small_ligature_oe, Qpct_capital_ligature_oe;
    Object Qpct_trade_mark_sign, Qpct_registered_sign, Qpct_copyright_sign;
    Object Qpct_soft_hyphen, Qpct_zero_width_no_break_space;
    Object Qpct_no_break_space, Qpct_fixed_width_space, Qpct_ordinary_space;
    Object Qpct_paragraph_separator, Qpct_line_separator, Qpct_esc;
    Object Qpct_escape, Qpct_null, Qpct_page, Qpct_tab, Qpct_return;
    Object Qpct_linefeed, Qpct_newline, Qpct_sp, Qpct_space, Qjapanese;
    Declare_special(1);

    x_note_fn_call(19,6);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    if (Han_interpretation_mode == UNBOUND)
	Han_interpretation_mode = Qjapanese;
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    if (Gensym_code_for_linebreak == UNBOUND) {
	unicode = (SI_Long)8232L;
	row = FIX(unicode >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & unicode;
	      Gensym_code_for_linebreak = FIX(gensymed_symbol + 
		      gensymed_symbol_1);
	  }
	  else
	      Gensym_code_for_linebreak = Nil;
	POP_SPECIAL();
    }
    if (Gensym_char_or_code_for_linebreak == UNBOUND)
	Gensym_char_or_code_for_linebreak = CHR('L');
    if (Gensym_esc_for_linebreak_qm == UNBOUND)
	Gensym_esc_for_linebreak_qm = CHR('@');
    if (Gensym_code_for_paragraph_break == UNBOUND) {
	unicode = (SI_Long)8233L;
	row = FIX(unicode >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & unicode;
	      Gensym_code_for_paragraph_break = FIX(gensymed_symbol + 
		      gensymed_symbol_1);
	  }
	  else
	      Gensym_code_for_paragraph_break = Nil;
	POP_SPECIAL();
    }
    if (Gensym_char_or_code_for_paragraph_break == UNBOUND)
	Gensym_char_or_code_for_paragraph_break = CHR('P');
    if (Gensym_esc_for_paragraph_break_qm == UNBOUND)
	Gensym_esc_for_paragraph_break_qm = CHR('@');
    if (Gensym_code_for_capital_ligature_oe == UNBOUND) {
	unicode = (SI_Long)338L;
	row = FIX(unicode >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & unicode;
	      Gensym_code_for_capital_ligature_oe = FIX(gensymed_symbol + 
		      gensymed_symbol_1);
	  }
	  else
	      Gensym_code_for_capital_ligature_oe = Nil;
	POP_SPECIAL();
    }
    if (Gensym_char_or_code_for_capital_ligature_oe == UNBOUND)
	Gensym_char_or_code_for_capital_ligature_oe = CHR('W');
    if (Gensym_esc_for_capital_ligature_oe_qm == UNBOUND)
	Gensym_esc_for_capital_ligature_oe_qm = CHR('~');
    if (Gensym_code_for_small_ligature_oe == UNBOUND) {
	unicode = (SI_Long)339L;
	row = FIX(unicode >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & unicode;
	      Gensym_code_for_small_ligature_oe = FIX(gensymed_symbol + 
		      gensymed_symbol_1);
	  }
	  else
	      Gensym_code_for_small_ligature_oe = Nil;
	POP_SPECIAL();
    }
    if (Gensym_char_or_code_for_small_ligature_oe == UNBOUND)
	Gensym_char_or_code_for_small_ligature_oe = CHR('w');
    if (Gensym_esc_for_small_ligature_oe_qm == UNBOUND)
	Gensym_esc_for_small_ligature_oe_qm = CHR('~');
    if (Gensym_code_for_bullet == UNBOUND) {
	unicode = (SI_Long)8226L;
	row = FIX(unicode >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & unicode;
	      Gensym_code_for_bullet = FIX(gensymed_symbol + 
		      gensymed_symbol_1);
	  }
	  else
	      Gensym_code_for_bullet = Nil;
	POP_SPECIAL();
    }
    if (Gensym_char_or_code_for_bullet == UNBOUND)
	Gensym_char_or_code_for_bullet = CHR('*');
    if (Gensym_esc_for_bullet_qm == UNBOUND)
	Gensym_esc_for_bullet_qm = CHR('~');
    if (Gensym_code_for_small_letter_f_with_hook == UNBOUND) {
	unicode = (SI_Long)402L;
	row = FIX(unicode >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & unicode;
	      Gensym_code_for_small_letter_f_with_hook = 
		      FIX(gensymed_symbol + gensymed_symbol_1);
	  }
	  else
	      Gensym_code_for_small_letter_f_with_hook = Nil;
	POP_SPECIAL();
    }
    if (Gensym_char_or_code_for_small_letter_f_with_hook == UNBOUND)
	Gensym_char_or_code_for_small_letter_f_with_hook = CHR('&');
    if (Gensym_esc_for_small_letter_f_with_hook_qm == UNBOUND)
	Gensym_esc_for_small_letter_f_with_hook_qm = CHR('~');
    if (Gensym_code_for_trade_mark_sign == UNBOUND) {
	unicode = (SI_Long)8482L;
	row = FIX(unicode >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & unicode;
	      Gensym_code_for_trade_mark_sign = FIX(gensymed_symbol + 
		      gensymed_symbol_1);
	  }
	  else
	      Gensym_code_for_trade_mark_sign = Nil;
	POP_SPECIAL();
    }
    if (Gensym_char_or_code_for_trade_mark_sign == UNBOUND)
	Gensym_char_or_code_for_trade_mark_sign = CHR(':');
    if (Gensym_esc_for_trade_mark_sign_qm == UNBOUND)
	Gensym_esc_for_trade_mark_sign_qm = CHR('~');
    if (Current_extended_utf_g_low_half_character_qm == UNBOUND)
	Current_extended_utf_g_low_half_character_qm = Nil;
    Qpct_space = STATIC_SYMBOL("%SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_space,FIX((SI_Long)32L));
    Qpct_sp = STATIC_SYMBOL("%SP",AB_package);
    SET_SYMBOL_VALUE(Qpct_sp,FIX((SI_Long)32L));
    Qpct_newline = STATIC_SYMBOL("%NEWLINE",AB_package);
    SET_SYMBOL_VALUE(Qpct_newline,FIX((SI_Long)10L));
    Qpct_linefeed = STATIC_SYMBOL("%LINEFEED",AB_package);
    SET_SYMBOL_VALUE(Qpct_linefeed,FIX((SI_Long)10L));
    Qpct_return = STATIC_SYMBOL("%RETURN",AB_package);
    SET_SYMBOL_VALUE(Qpct_return,FIX((SI_Long)13L));
    Qpct_tab = STATIC_SYMBOL("%TAB",AB_package);
    SET_SYMBOL_VALUE(Qpct_tab,FIX((SI_Long)9L));
    Qpct_page = STATIC_SYMBOL("%PAGE",AB_package);
    SET_SYMBOL_VALUE(Qpct_page,FIX((SI_Long)12L));
    Qpct_null = STATIC_SYMBOL("%NULL",AB_package);
    SET_SYMBOL_VALUE(Qpct_null,FIX((SI_Long)0L));
    Qpct_escape = STATIC_SYMBOL("%ESCAPE",AB_package);
    SET_SYMBOL_VALUE(Qpct_escape,FIX((SI_Long)27L));
    Qpct_esc = STATIC_SYMBOL("%ESC",AB_package);
    SET_SYMBOL_VALUE(Qpct_esc,FIX((SI_Long)27L));
    Qpct_line_separator = STATIC_SYMBOL("%LINE-SEPARATOR",AB_package);
    SET_SYMBOL_VALUE(Qpct_line_separator,FIX((SI_Long)8232L));
    Qpct_paragraph_separator = STATIC_SYMBOL("%PARAGRAPH-SEPARATOR",
	    AB_package);
    SET_SYMBOL_VALUE(Qpct_paragraph_separator,FIX((SI_Long)8233L));
    Qpct_ordinary_space = STATIC_SYMBOL("%ORDINARY-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_ordinary_space,FIX((SI_Long)32L));
    Qpct_fixed_width_space = STATIC_SYMBOL("%FIXED-WIDTH-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_fixed_width_space,FIX((SI_Long)8199L));
    Qpct_no_break_space = STATIC_SYMBOL("%NO-BREAK-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_no_break_space,FIX((SI_Long)160L));
    Qpct_zero_width_no_break_space = 
	    STATIC_SYMBOL("%ZERO-WIDTH-NO-BREAK-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_zero_width_no_break_space,FIX((SI_Long)65279L));
    Qpct_soft_hyphen = STATIC_SYMBOL("%SOFT-HYPHEN",AB_package);
    SET_SYMBOL_VALUE(Qpct_soft_hyphen,FIX((SI_Long)173L));
    Qpct_copyright_sign = STATIC_SYMBOL("%COPYRIGHT-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qpct_copyright_sign,FIX((SI_Long)169L));
    Qpct_registered_sign = STATIC_SYMBOL("%REGISTERED-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qpct_registered_sign,FIX((SI_Long)174L));
    Qpct_trade_mark_sign = STATIC_SYMBOL("%TRADE-MARK-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qpct_trade_mark_sign,FIX((SI_Long)8482L));
    Qpct_capital_ligature_oe = STATIC_SYMBOL("%CAPITAL-LIGATURE-OE",
	    AB_package);
    SET_SYMBOL_VALUE(Qpct_capital_ligature_oe,FIX((SI_Long)338L));
    Qpct_small_ligature_oe = STATIC_SYMBOL("%SMALL-LIGATURE-OE",AB_package);
    SET_SYMBOL_VALUE(Qpct_small_ligature_oe,FIX((SI_Long)339L));
    Qpct_bullet = STATIC_SYMBOL("%BULLET",AB_package);
    SET_SYMBOL_VALUE(Qpct_bullet,FIX((SI_Long)8226L));
    Qpct_latin_small_letter_f_with_hook = 
	    STATIC_SYMBOL("%LATIN-SMALL-LETTER-F-WITH-HOOK",AB_package);
    SET_SYMBOL_VALUE(Qpct_latin_small_letter_f_with_hook,FIX((SI_Long)402L));
    Qpct_hair_space = STATIC_SYMBOL("%HAIR-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_hair_space,FIX((SI_Long)8202L));
    Qpct_thin_space = STATIC_SYMBOL("%THIN-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_thin_space,FIX((SI_Long)8201L));
    Qpct_en_space = STATIC_SYMBOL("%EN-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_en_space,FIX((SI_Long)8194L));
    Qpct_em_space = STATIC_SYMBOL("%EM-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_em_space,FIX((SI_Long)8193L));
    Qpct_zero_width_space = STATIC_SYMBOL("%ZERO-WIDTH-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qpct_zero_width_space,FIX((SI_Long)8203L));
    Qpct_zero_width_joiner = STATIC_SYMBOL("%ZERO-WIDTH-JOINER",AB_package);
    SET_SYMBOL_VALUE(Qpct_zero_width_joiner,FIX((SI_Long)8205L));
    Qpct_inverted_exclamation_point = 
	    STATIC_SYMBOL("%INVERTED-EXCLAMATION-POINT",AB_package);
    SET_SYMBOL_VALUE(Qpct_inverted_exclamation_point,FIX((SI_Long)161L));
    Qpct_cent_sign = STATIC_SYMBOL("%CENT-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qpct_cent_sign,FIX((SI_Long)162L));
    Qpct_pound_sign = STATIC_SYMBOL("%POUND-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qpct_pound_sign,FIX((SI_Long)163L));
    Qpct_yen_sign = STATIC_SYMBOL("%YEN-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qpct_yen_sign,FIX((SI_Long)165L));
    Qpct_right_pointing_double_angle_quotation_mark = 
	    STATIC_SYMBOL("%RIGHT-POINTING-DOUBLE-ANGLE-QUOTATION-MARK",
	    AB_package);
    SET_SYMBOL_VALUE(Qpct_right_pointing_double_angle_quotation_mark,
	    FIX((SI_Long)187L));
    Qpct_left_pointing_double_angle_quotation_mark = 
	    STATIC_SYMBOL("%LEFT-POINTING-DOUBLE-ANGLE-QUOTATION-MARK",
	    AB_package);
    SET_SYMBOL_VALUE(Qpct_left_pointing_double_angle_quotation_mark,
	    FIX((SI_Long)171L));
    Qpct_inverted_question_mark = STATIC_SYMBOL("%INVERTED-QUESTION-MARK",
	    AB_package);
    SET_SYMBOL_VALUE(Qpct_inverted_question_mark,FIX((SI_Long)191L));
    Qpct_euro_sign = STATIC_SYMBOL("%EURO-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qpct_euro_sign,FIX((SI_Long)8364L));
    Qab_pct_sp = STATIC_SYMBOL("% ",AB_package);
    SET_SYMBOL_VALUE(Qab_pct_sp,FIX((SI_Long)32L));
    Qpct_ex = STATIC_SYMBOL("%!",AB_package);
    SET_SYMBOL_VALUE(Qpct_ex,FIX((SI_Long)33L));
    Qpct_dq = STATIC_SYMBOL("%\"",AB_package);
    SET_SYMBOL_VALUE(Qpct_dq,FIX((SI_Long)34L));
    Qpct_no = STATIC_SYMBOL("%#",AB_package);
    SET_SYMBOL_VALUE(Qpct_no,FIX((SI_Long)35L));
    Qpct_dol = STATIC_SYMBOL("%$",AB_package);
    SET_SYMBOL_VALUE(Qpct_dol,FIX((SI_Long)36L));
    Qpct_pct = STATIC_SYMBOL("%%",AB_package);
    SET_SYMBOL_VALUE(Qpct_pct,FIX((SI_Long)37L));
    Qpct_and = STATIC_SYMBOL("%&",AB_package);
    SET_SYMBOL_VALUE(Qpct_and,FIX((SI_Long)38L));
    Qpct_qu = STATIC_SYMBOL("%\'",AB_package);
    SET_SYMBOL_VALUE(Qpct_qu,FIX((SI_Long)39L));
    Qpct_op = STATIC_SYMBOL("%(",AB_package);
    SET_SYMBOL_VALUE(Qpct_op,FIX((SI_Long)40L));
    Qpct_cp = STATIC_SYMBOL("%)",AB_package);
    SET_SYMBOL_VALUE(Qpct_cp,FIX((SI_Long)41L));
    Qpct_star = STATIC_SYMBOL("%*",AB_package);
    SET_SYMBOL_VALUE(Qpct_star,FIX((SI_Long)42L));
    Qpct_plus = STATIC_SYMBOL("%+",AB_package);
    SET_SYMBOL_VALUE(Qpct_plus,FIX((SI_Long)43L));
    Qpct_cm = STATIC_SYMBOL("%,",AB_package);
    SET_SYMBOL_VALUE(Qpct_cm,FIX((SI_Long)44L));
    Qpct_ = STATIC_SYMBOL("%-",AB_package);
    SET_SYMBOL_VALUE(Qpct_,FIX((SI_Long)45L));
    Qpct_dot = STATIC_SYMBOL("%.",AB_package);
    SET_SYMBOL_VALUE(Qpct_dot,FIX((SI_Long)46L));
    Qpct_sl = STATIC_SYMBOL("%/",AB_package);
    SET_SYMBOL_VALUE(Qpct_sl,FIX((SI_Long)47L));
    Qpct_0 = STATIC_SYMBOL("%0",AB_package);
    SET_SYMBOL_VALUE(Qpct_0,FIX((SI_Long)48L));
    Qpct_1 = STATIC_SYMBOL("%1",AB_package);
    SET_SYMBOL_VALUE(Qpct_1,FIX((SI_Long)49L));
    Qpct_2 = STATIC_SYMBOL("%2",AB_package);
    SET_SYMBOL_VALUE(Qpct_2,FIX((SI_Long)50L));
    Qpct_3 = STATIC_SYMBOL("%3",AB_package);
    SET_SYMBOL_VALUE(Qpct_3,FIX((SI_Long)51L));
    Qpct_4 = STATIC_SYMBOL("%4",AB_package);
    SET_SYMBOL_VALUE(Qpct_4,FIX((SI_Long)52L));
    Qpct_5 = STATIC_SYMBOL("%5",AB_package);
    SET_SYMBOL_VALUE(Qpct_5,FIX((SI_Long)53L));
    Qpct_6 = STATIC_SYMBOL("%6",AB_package);
    SET_SYMBOL_VALUE(Qpct_6,FIX((SI_Long)54L));
    Qpct_7 = STATIC_SYMBOL("%7",AB_package);
    SET_SYMBOL_VALUE(Qpct_7,FIX((SI_Long)55L));
    Qpct_8 = STATIC_SYMBOL("%8",AB_package);
    SET_SYMBOL_VALUE(Qpct_8,FIX((SI_Long)56L));
    Qpct_9 = STATIC_SYMBOL("%9",AB_package);
    SET_SYMBOL_VALUE(Qpct_9,FIX((SI_Long)57L));
    Qpct_col = STATIC_SYMBOL("%:",AB_package);
    SET_SYMBOL_VALUE(Qpct_col,FIX((SI_Long)58L));
    Qpct_sc = STATIC_SYMBOL("%;",AB_package);
    SET_SYMBOL_VALUE(Qpct_sc,FIX((SI_Long)59L));
    Qpct_lt = STATIC_SYMBOL("%<",AB_package);
    SET_SYMBOL_VALUE(Qpct_lt,FIX((SI_Long)60L));
    Qpct_eq = STATIC_SYMBOL("%=",AB_package);
    SET_SYMBOL_VALUE(Qpct_eq,FIX((SI_Long)61L));
    Qpct_gt = STATIC_SYMBOL("%>",AB_package);
    SET_SYMBOL_VALUE(Qpct_gt,FIX((SI_Long)62L));
    Qpct_qm = STATIC_SYMBOL("%\?",AB_package);
    SET_SYMBOL_VALUE(Qpct_qm,FIX((SI_Long)63L));
    Qpct_at = STATIC_SYMBOL("%@",AB_package);
    SET_SYMBOL_VALUE(Qpct_at,FIX((SI_Long)64L));
    Qpct_a = STATIC_SYMBOL("%A",AB_package);
    SET_SYMBOL_VALUE(Qpct_a,FIX((SI_Long)65L));
    Qpct_b = STATIC_SYMBOL("%B",AB_package);
    SET_SYMBOL_VALUE(Qpct_b,FIX((SI_Long)66L));
    Qpct_c = STATIC_SYMBOL("%C",AB_package);
    SET_SYMBOL_VALUE(Qpct_c,FIX((SI_Long)67L));
    Qpct_d = STATIC_SYMBOL("%D",AB_package);
    SET_SYMBOL_VALUE(Qpct_d,FIX((SI_Long)68L));
    Qpct_e = STATIC_SYMBOL("%E",AB_package);
    SET_SYMBOL_VALUE(Qpct_e,FIX((SI_Long)69L));
    Qpct_f = STATIC_SYMBOL("%F",AB_package);
    SET_SYMBOL_VALUE(Qpct_f,FIX((SI_Long)70L));
    Qpct_g = STATIC_SYMBOL("%G",AB_package);
    SET_SYMBOL_VALUE(Qpct_g,FIX((SI_Long)71L));
    Qpct_h = STATIC_SYMBOL("%H",AB_package);
    SET_SYMBOL_VALUE(Qpct_h,FIX((SI_Long)72L));
    Qpct_i = STATIC_SYMBOL("%I",AB_package);
    SET_SYMBOL_VALUE(Qpct_i,FIX((SI_Long)73L));
    Qpct_j = STATIC_SYMBOL("%J",AB_package);
    SET_SYMBOL_VALUE(Qpct_j,FIX((SI_Long)74L));
    Qpct_k = STATIC_SYMBOL("%K",AB_package);
    SET_SYMBOL_VALUE(Qpct_k,FIX((SI_Long)75L));
    Qpct_l = STATIC_SYMBOL("%L",AB_package);
    SET_SYMBOL_VALUE(Qpct_l,FIX((SI_Long)76L));
    Qpct_m = STATIC_SYMBOL("%M",AB_package);
    SET_SYMBOL_VALUE(Qpct_m,FIX((SI_Long)77L));
    Qpct_n = STATIC_SYMBOL("%N",AB_package);
    SET_SYMBOL_VALUE(Qpct_n,FIX((SI_Long)78L));
    Qpct_o = STATIC_SYMBOL("%O",AB_package);
    SET_SYMBOL_VALUE(Qpct_o,FIX((SI_Long)79L));
    Qpct_p = STATIC_SYMBOL("%P",AB_package);
    SET_SYMBOL_VALUE(Qpct_p,FIX((SI_Long)80L));
    Qpct_q = STATIC_SYMBOL("%Q",AB_package);
    SET_SYMBOL_VALUE(Qpct_q,FIX((SI_Long)81L));
    Qpct_r = STATIC_SYMBOL("%R",AB_package);
    SET_SYMBOL_VALUE(Qpct_r,FIX((SI_Long)82L));
    Qpct_s = STATIC_SYMBOL("%S",AB_package);
    SET_SYMBOL_VALUE(Qpct_s,FIX((SI_Long)83L));
    Qpct_t = STATIC_SYMBOL("%T",AB_package);
    SET_SYMBOL_VALUE(Qpct_t,FIX((SI_Long)84L));
    Qpct_u = STATIC_SYMBOL("%U",AB_package);
    SET_SYMBOL_VALUE(Qpct_u,FIX((SI_Long)85L));
    Qpct_v = STATIC_SYMBOL("%V",AB_package);
    SET_SYMBOL_VALUE(Qpct_v,FIX((SI_Long)86L));
    Qpct_w = STATIC_SYMBOL("%W",AB_package);
    SET_SYMBOL_VALUE(Qpct_w,FIX((SI_Long)87L));
    Qpct_x = STATIC_SYMBOL("%X",AB_package);
    SET_SYMBOL_VALUE(Qpct_x,FIX((SI_Long)88L));
    Qpct_y = STATIC_SYMBOL("%Y",AB_package);
    SET_SYMBOL_VALUE(Qpct_y,FIX((SI_Long)89L));
    Qpct_z = STATIC_SYMBOL("%Z",AB_package);
    SET_SYMBOL_VALUE(Qpct_z,FIX((SI_Long)90L));
    Qpct_obt = STATIC_SYMBOL("%[",AB_package);
    SET_SYMBOL_VALUE(Qpct_obt,FIX((SI_Long)91L));
    Qpct_bs = STATIC_SYMBOL("%\\",AB_package);
    SET_SYMBOL_VALUE(Qpct_bs,FIX((SI_Long)92L));
    Qpct_cbt = STATIC_SYMBOL("%]",AB_package);
    SET_SYMBOL_VALUE(Qpct_cbt,FIX((SI_Long)93L));
    Qpct_ct = STATIC_SYMBOL("%^",AB_package);
    SET_SYMBOL_VALUE(Qpct_ct,FIX((SI_Long)94L));
    Qab_pct_ = STATIC_SYMBOL("%_",AB_package);
    SET_SYMBOL_VALUE(Qab_pct_,FIX((SI_Long)95L));
    Qpct_bq = STATIC_SYMBOL("%`",AB_package);
    SET_SYMBOL_VALUE(Qpct_bq,FIX((SI_Long)96L));
    QPCT_A = STATIC_SYMBOL("%a",AB_package);
    SET_SYMBOL_VALUE(QPCT_A,FIX((SI_Long)97L));
    QPCT_B = STATIC_SYMBOL("%b",AB_package);
    SET_SYMBOL_VALUE(QPCT_B,FIX((SI_Long)98L));
    QPCT_C = STATIC_SYMBOL("%c",AB_package);
    SET_SYMBOL_VALUE(QPCT_C,FIX((SI_Long)99L));
    QPCT_D = STATIC_SYMBOL("%d",AB_package);
    SET_SYMBOL_VALUE(QPCT_D,FIX((SI_Long)100L));
    QPCT_E = STATIC_SYMBOL("%e",AB_package);
    SET_SYMBOL_VALUE(QPCT_E,FIX((SI_Long)101L));
    QPCT_F = STATIC_SYMBOL("%f",AB_package);
    SET_SYMBOL_VALUE(QPCT_F,FIX((SI_Long)102L));
    QPCT_G = STATIC_SYMBOL("%g",AB_package);
    SET_SYMBOL_VALUE(QPCT_G,FIX((SI_Long)103L));
    QPCT_H = STATIC_SYMBOL("%h",AB_package);
    SET_SYMBOL_VALUE(QPCT_H,FIX((SI_Long)104L));
    QPCT_I = STATIC_SYMBOL("%i",AB_package);
    SET_SYMBOL_VALUE(QPCT_I,FIX((SI_Long)105L));
    QPCT_J = STATIC_SYMBOL("%j",AB_package);
    SET_SYMBOL_VALUE(QPCT_J,FIX((SI_Long)106L));
    QPCT_K = STATIC_SYMBOL("%k",AB_package);
    SET_SYMBOL_VALUE(QPCT_K,FIX((SI_Long)107L));
    QPCT_L = STATIC_SYMBOL("%l",AB_package);
    SET_SYMBOL_VALUE(QPCT_L,FIX((SI_Long)108L));
    QPCT_M = STATIC_SYMBOL("%m",AB_package);
    SET_SYMBOL_VALUE(QPCT_M,FIX((SI_Long)109L));
    QPCT_N = STATIC_SYMBOL("%n",AB_package);
    SET_SYMBOL_VALUE(QPCT_N,FIX((SI_Long)110L));
    QPCT_O = STATIC_SYMBOL("%o",AB_package);
    SET_SYMBOL_VALUE(QPCT_O,FIX((SI_Long)111L));
    QPCT_P = STATIC_SYMBOL("%p",AB_package);
    SET_SYMBOL_VALUE(QPCT_P,FIX((SI_Long)112L));
    QPCT_Q = STATIC_SYMBOL("%q",AB_package);
    SET_SYMBOL_VALUE(QPCT_Q,FIX((SI_Long)113L));
    QPCT_R = STATIC_SYMBOL("%r",AB_package);
    SET_SYMBOL_VALUE(QPCT_R,FIX((SI_Long)114L));
    QPCT_S = STATIC_SYMBOL("%s",AB_package);
    SET_SYMBOL_VALUE(QPCT_S,FIX((SI_Long)115L));
    QPCT_T = STATIC_SYMBOL("%t",AB_package);
    SET_SYMBOL_VALUE(QPCT_T,FIX((SI_Long)116L));
    QPCT_U = STATIC_SYMBOL("%u",AB_package);
    SET_SYMBOL_VALUE(QPCT_U,FIX((SI_Long)117L));
    QPCT_V = STATIC_SYMBOL("%v",AB_package);
    SET_SYMBOL_VALUE(QPCT_V,FIX((SI_Long)118L));
    QPCT_W = STATIC_SYMBOL("%w",AB_package);
    SET_SYMBOL_VALUE(QPCT_W,FIX((SI_Long)119L));
    QPCT_X = STATIC_SYMBOL("%x",AB_package);
    SET_SYMBOL_VALUE(QPCT_X,FIX((SI_Long)120L));
    QPCT_Y = STATIC_SYMBOL("%y",AB_package);
    SET_SYMBOL_VALUE(QPCT_Y,FIX((SI_Long)121L));
    QPCT_Z = STATIC_SYMBOL("%z",AB_package);
    SET_SYMBOL_VALUE(QPCT_Z,FIX((SI_Long)122L));
    Qpct_ob = STATIC_SYMBOL("%{",AB_package);
    SET_SYMBOL_VALUE(Qpct_ob,FIX((SI_Long)123L));
    Qpct_or = STATIC_SYMBOL("%|",AB_package);
    SET_SYMBOL_VALUE(Qpct_or,FIX((SI_Long)124L));
    Qpct_cb = STATIC_SYMBOL("%}",AB_package);
    SET_SYMBOL_VALUE(Qpct_cb,FIX((SI_Long)125L));
    Qpct_tl = STATIC_SYMBOL("%~",AB_package);
    SET_SYMBOL_VALUE(Qpct_tl,FIX((SI_Long)126L));
}
