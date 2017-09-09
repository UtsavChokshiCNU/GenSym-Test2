/* chars2.c
 * Input file:  characters2.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "chars2.h"


Object G2int_han_interpretation_mode = UNBOUND;

/* UNICODE-HAN-CHARACTER-P */
Object g2int_unicode_han_character_p(unicode)
    Object unicode;
{
    x_note_fn_call(19,0);
    return VALUES_1(unicode);
}

static Object Qg2int_korean;       /* korean */

/* MAP-UNICODE-TO-GENSYM-HAN-CHARACTER-CODE */
Object g2int_map_unicode_to_gensym_han_character_code(unicode)
    Object unicode;
{
    Object cjk_code, cjk_code_mapping_vector, l, temp_1;
    SI_Long temp;

    x_note_fn_call(19,1);
    if (EQ(G2int_han_interpretation_mode,Qg2int_korean)) {
	cjk_code = unicode;
	cjk_code_mapping_vector = G2int_unicode_to_ks_c_5601_map;
	temp = IFIX(cjk_code) % (SI_Long)307L;
	l = ISVREF(cjk_code_mapping_vector,temp);
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (FIXNUM_EQ(CAR(l),cjk_code)) {
	    temp_1 = CADR(l);
	    goto end;
	}
	l = CDDR(l);
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end:;
	if (temp_1);
	else {
	    cjk_code = unicode;
	    cjk_code_mapping_vector = G2int_unicode_to_jis_x_0208_map;
	    temp = IFIX(cjk_code) % (SI_Long)307L;
	    l = ISVREF(cjk_code_mapping_vector,temp);
	  next_loop_1:
	    if ( !TRUEP(l))
		goto end_loop_1;
	    if (FIXNUM_EQ(CAR(l),cjk_code)) {
		temp_1 = CADR(l);
		goto end_1;
	    }
	    l = CDDR(l);
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = Qnil;
	  end_1:;
	}
    }
    else {
	cjk_code = unicode;
	cjk_code_mapping_vector = G2int_unicode_to_jis_x_0208_map;
	temp = IFIX(cjk_code) % (SI_Long)307L;
	l = ISVREF(cjk_code_mapping_vector,temp);
      next_loop_2:
	if ( !TRUEP(l))
	    goto end_loop_2;
	if (FIXNUM_EQ(CAR(l),cjk_code)) {
	    temp_1 = CADR(l);
	    goto end_2;
	}
	l = CDDR(l);
	goto next_loop_2;
      end_loop_2:
	temp_1 = Qnil;
      end_2:;
	if (temp_1);
	else {
	    cjk_code = unicode;
	    cjk_code_mapping_vector = G2int_unicode_to_ks_c_5601_map;
	    temp = IFIX(cjk_code) % (SI_Long)307L;
	    l = ISVREF(cjk_code_mapping_vector,temp);
	  next_loop_3:
	    if ( !TRUEP(l))
		goto end_loop_3;
	    if (FIXNUM_EQ(CAR(l),cjk_code)) {
		temp_1 = CADR(l);
		goto end_3;
	    }
	    l = CDDR(l);
	    goto next_loop_3;
	  end_loop_3:
	    temp_1 = Qnil;
	  end_3:;
	}
    }
    return VALUES_1(temp_1);
}

/* MAP-GENSYM-HAN-CHARACTER-CODE-TO-UNICODE */
Object g2int_map_gensym_han_character_code_to_unicode(gensym_character_code)
    Object gensym_character_code;
{
    Object contiguous_code_qm, temp;

    x_note_fn_call(19,2);
    if (EQ(G2int_han_interpretation_mode,Qg2int_korean)) {
	if (g2int_legal_gensym_ksc_character_code_p(gensym_character_code)) {
	    contiguous_code_qm = 
		    g2int_gensym_ksc_code_to_contiguous(gensym_character_code);
	    temp = contiguous_code_qm ? 
		    FIX(UBYTE_16_ISAREF_1(G2int_ks_c_5601_to_unicode_map,
		    IFIX(contiguous_code_qm))) : Nil;
	}
	else
	    temp = Nil;
	if (temp);
	else if (g2int_legal_gensym_jis_character_code_p(gensym_character_code)) 
		    {
	    contiguous_code_qm = 
		    g2int_gensym_jis_code_to_contiguous(gensym_character_code);
	    temp = contiguous_code_qm ? 
		    FIX(UBYTE_16_ISAREF_1(G2int_jis_x_0208_to_unicode_map,
		    IFIX(contiguous_code_qm))) : Nil;
	}
	else
	    temp = Nil;
    }
    else {
	if (g2int_legal_gensym_jis_character_code_p(gensym_character_code)) {
	    contiguous_code_qm = 
		    g2int_gensym_jis_code_to_contiguous(gensym_character_code);
	    temp = contiguous_code_qm ? 
		    FIX(UBYTE_16_ISAREF_1(G2int_jis_x_0208_to_unicode_map,
		    IFIX(contiguous_code_qm))) : Nil;
	}
	else
	    temp = Nil;
	if (temp);
	else if (g2int_legal_gensym_ksc_character_code_p(gensym_character_code)) 
		    {
	    contiguous_code_qm = 
		    g2int_gensym_ksc_code_to_contiguous(gensym_character_code);
	    temp = contiguous_code_qm ? 
		    FIX(UBYTE_16_ISAREF_1(G2int_ks_c_5601_to_unicode_map,
		    IFIX(contiguous_code_qm))) : Nil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_gensym_code_for_linebreak = UNBOUND;

Object G2int_gensym_char_or_code_for_linebreak = UNBOUND;

Object G2int_gensym_esc_for_linebreakqm = UNBOUND;

Object G2int_gensym_code_for_paragraph_break = UNBOUND;

Object G2int_gensym_char_or_code_for_paragraph_break = UNBOUND;

Object G2int_gensym_esc_for_paragraph_breakqm = UNBOUND;

Object G2int_gensym_code_for_capital_ligature_oe = UNBOUND;

Object G2int_gensym_char_or_code_for_capital_ligature_oe = UNBOUND;

Object G2int_gensym_esc_for_capital_ligature_oeqm = UNBOUND;

Object G2int_gensym_code_for_small_ligature_oe = UNBOUND;

Object G2int_gensym_char_or_code_for_small_ligature_oe = UNBOUND;

Object G2int_gensym_esc_for_small_ligature_oeqm = UNBOUND;

Object G2int_gensym_code_for_bullet = UNBOUND;

Object G2int_gensym_char_or_code_for_bullet = UNBOUND;

Object G2int_gensym_esc_for_bulletqm = UNBOUND;

Object G2int_gensym_code_for_small_letter_f_with_hook = UNBOUND;

Object G2int_gensym_char_or_code_for_small_letter_f_with_hook = UNBOUND;

Object G2int_gensym_esc_for_small_letter_f_with_hookqm = UNBOUND;

Object G2int_gensym_code_for_trade_mark_sign = UNBOUND;

Object G2int_gensym_char_or_code_for_trade_mark_sign = UNBOUND;

Object G2int_gensym_esc_for_trade_mark_signqm = UNBOUND;

Object G2int_current_extended_utf_g_low_half_characterqm = UNBOUND;

/* WIDE-CHARACTER-IS-SIMPLE-GENSYM-CHARACTER-P */
Object g2int_wide_character_is_simple_gensym_character_p(wide_character)
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
Object g2int_map_unicode_to_gensym_character_code_with_cjk_neutrality(unicode)
    Object unicode;
{
    Object code, temp;
    SI_Long row, gensym_full_row, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(19,4);
    code = unicode;
    if (IFIX(code) < (SI_Long)127L &&  !((SI_Long)64L == IFIX(code) || 
	    (SI_Long)126L == IFIX(code) || (SI_Long)92L == IFIX(code)))
	return VALUES_1(unicode);
    else {
	row = IFIX(unicode) >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
	    temp = FIX(gensymed_symbol + gensymed_symbol_1);
	}
	else
	    temp = Nil;
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
Object g2int_wide_character_p_function(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(19,5);
    temp = FIXNUMP(thing) ? T : Nil;
    return VALUES_1(temp);
}

void characters2_INIT()
{
    SI_Long unicode, row, gensym_full_row, gensymed_symbol, gensymed_symbol_1;
    Object Qg2int_pcttl, AB_package, Qg2int_pctcb, Qg2int_pctor, Qg2int_pctob;
    Object Qab_g2int_pctz, Qab_g2int_pcty, Qab_g2int_pctx, Qab_g2int_pctw;
    Object Qab_g2int_pctv, Qab_g2int_pctu, Qab_g2int_pctt, Qab_g2int_pcts;
    Object Qab_g2int_pctr, Qab_g2int_pctq, Qab_g2int_pctp, Qab_g2int_pcto;
    Object Qab_g2int_pctn, Qab_g2int_pctm, Qab_g2int_pctl, Qab_g2int_pctk;
    Object Qab_g2int_pctj, Qab_g2int_pcti, Qab_g2int_pcth, Qab_g2int_pctg;
    Object Qab_g2int_pctf, Qab_g2int_pcte, Qab_g2int_pctd, Qab_g2int_pctc;
    Object Qab_g2int_pctb, Qab_g2int_pcta, Qg2int_pctbq, Qab_g2int_pct_;
    Object Qg2int_pctct, Qg2int_pctcbt, Qg2int_pctbs, Qg2int_pctobt;
    Object Qg2int_pctz, Qg2int_pcty, Qg2int_pctx, Qg2int_pctw, Qg2int_pctv;
    Object Qg2int_pctu, Qg2int_pctt, Qg2int_pcts, Qg2int_pctr, Qg2int_pctq;
    Object Qg2int_pctp, Qg2int_pcto, Qg2int_pctn, Qg2int_pctm, Qg2int_pctl;
    Object Qg2int_pctk, Qg2int_pctj, Qg2int_pcti, Qg2int_pcth, Qg2int_pctg;
    Object Qg2int_pctf, Qg2int_pcte, Qg2int_pctd, Qg2int_pctc, Qg2int_pctb;
    Object Qg2int_pcta, Qg2int_pctat, Qg2int_pctqm, Qg2int_pctgt, Qg2int_pcteq;
    Object Qg2int_pctlt, Qg2int_pctsc, Qg2int_pctcol, Qg2int_pct9, Qg2int_pct8;
    Object Qg2int_pct7, Qg2int_pct6, Qg2int_pct5, Qg2int_pct4, Qg2int_pct3;
    Object Qg2int_pct2, Qg2int_pct1, Qg2int_pct0, Qg2int_pctsl, Qg2int_pctdot;
    Object Qg2int_pct_, Qg2int_pctcm, Qg2int_pctplus, Qg2int_pctstar;
    Object Qg2int_pctcp, Qg2int_pctop, Qg2int_pctqu, Qg2int_pctand;
    Object Qg2int_pctpct, Qg2int_pctdol, Qg2int_pctno, Qg2int_pctdq;
    Object Qg2int_pctex, Qab_g2int_pctsp, Qg2int_pcteuro_sign;
    Object Qg2int_pctinverted_question_mark;
    Object Qg2int_pctleft_pointing_double_angle_quotation_mark;
    Object Qg2int_pctright_pointing_double_angle_quotation_mark;
    Object Qg2int_pctyen_sign, Qg2int_pctpound_sign, Qg2int_pctcent_sign;
    Object Qg2int_pctinverted_exclamation_point, Qg2int_pctzero_width_joiner;
    Object Qg2int_pctzero_width_space, Qg2int_pctem_space, Qg2int_pcten_space;
    Object Qg2int_pctthin_space, Qg2int_pcthair_space;
    Object Qg2int_pctlatin_small_letter_f_with_hook, Qg2int_pctbullet;
    Object Qg2int_pctsmall_ligature_oe, Qg2int_pctcapital_ligature_oe;
    Object Qg2int_pcttrade_mark_sign, Qg2int_pctregistered_sign;
    Object Qg2int_pctcopyright_sign, Qg2int_pctsoft_hyphen;
    Object Qg2int_pctzero_width_no_break_space, Qg2int_pctno_break_space;
    Object Qg2int_pctfixed_width_space, Qg2int_pctordinary_space;
    Object Qg2int_pctparagraph_separator, Qg2int_pctline_separator;
    Object Qg2int_pctesc, Qg2int_pctescape, Qg2int_pctnull, Qg2int_pctpage;
    Object Qg2int_pcttab, Qg2int_pctreturn, Qg2int_pctlinefeed;
    Object Qg2int_pctnewline, Qg2int_pctsp, Qg2int_pctspace, Qg2int_japanese;

    x_note_fn_call(19,6);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_japanese = STATIC_SYMBOL("JAPANESE",AB_package);
    if (G2int_han_interpretation_mode == UNBOUND)
	G2int_han_interpretation_mode = Qg2int_japanese;
    Qg2int_korean = STATIC_SYMBOL("KOREAN",AB_package);
    if (G2int_gensym_code_for_linebreak == UNBOUND) {
	unicode = (SI_Long)8232L;
	row = unicode >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & unicode;
	    G2int_gensym_code_for_linebreak = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	}
	else
	    G2int_gensym_code_for_linebreak = Nil;
    }
    if (G2int_gensym_char_or_code_for_linebreak == UNBOUND)
	G2int_gensym_char_or_code_for_linebreak = CHR('L');
    if (G2int_gensym_esc_for_linebreakqm == UNBOUND)
	G2int_gensym_esc_for_linebreakqm = CHR('@');
    if (G2int_gensym_code_for_paragraph_break == UNBOUND) {
	unicode = (SI_Long)8233L;
	row = unicode >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & unicode;
	    G2int_gensym_code_for_paragraph_break = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	}
	else
	    G2int_gensym_code_for_paragraph_break = Nil;
    }
    if (G2int_gensym_char_or_code_for_paragraph_break == UNBOUND)
	G2int_gensym_char_or_code_for_paragraph_break = CHR('P');
    if (G2int_gensym_esc_for_paragraph_breakqm == UNBOUND)
	G2int_gensym_esc_for_paragraph_breakqm = CHR('@');
    if (G2int_gensym_code_for_capital_ligature_oe == UNBOUND) {
	unicode = (SI_Long)338L;
	row = unicode >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & unicode;
	    G2int_gensym_code_for_capital_ligature_oe = 
		    FIX(gensymed_symbol + gensymed_symbol_1);
	}
	else
	    G2int_gensym_code_for_capital_ligature_oe = Nil;
    }
    if (G2int_gensym_char_or_code_for_capital_ligature_oe == UNBOUND)
	G2int_gensym_char_or_code_for_capital_ligature_oe = CHR('W');
    if (G2int_gensym_esc_for_capital_ligature_oeqm == UNBOUND)
	G2int_gensym_esc_for_capital_ligature_oeqm = CHR('~');
    if (G2int_gensym_code_for_small_ligature_oe == UNBOUND) {
	unicode = (SI_Long)339L;
	row = unicode >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & unicode;
	    G2int_gensym_code_for_small_ligature_oe = FIX(gensymed_symbol 
		    + gensymed_symbol_1);
	}
	else
	    G2int_gensym_code_for_small_ligature_oe = Nil;
    }
    if (G2int_gensym_char_or_code_for_small_ligature_oe == UNBOUND)
	G2int_gensym_char_or_code_for_small_ligature_oe = CHR('w');
    if (G2int_gensym_esc_for_small_ligature_oeqm == UNBOUND)
	G2int_gensym_esc_for_small_ligature_oeqm = CHR('~');
    if (G2int_gensym_code_for_bullet == UNBOUND) {
	unicode = (SI_Long)8226L;
	row = unicode >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & unicode;
	    G2int_gensym_code_for_bullet = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	}
	else
	    G2int_gensym_code_for_bullet = Nil;
    }
    if (G2int_gensym_char_or_code_for_bullet == UNBOUND)
	G2int_gensym_char_or_code_for_bullet = CHR('*');
    if (G2int_gensym_esc_for_bulletqm == UNBOUND)
	G2int_gensym_esc_for_bulletqm = CHR('~');
    if (G2int_gensym_code_for_small_letter_f_with_hook == UNBOUND) {
	unicode = (SI_Long)402L;
	row = unicode >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & unicode;
	    G2int_gensym_code_for_small_letter_f_with_hook = 
		    FIX(gensymed_symbol + gensymed_symbol_1);
	}
	else
	    G2int_gensym_code_for_small_letter_f_with_hook = Nil;
    }
    if (G2int_gensym_char_or_code_for_small_letter_f_with_hook == UNBOUND)
	G2int_gensym_char_or_code_for_small_letter_f_with_hook = CHR('&');
    if (G2int_gensym_esc_for_small_letter_f_with_hookqm == UNBOUND)
	G2int_gensym_esc_for_small_letter_f_with_hookqm = CHR('~');
    if (G2int_gensym_code_for_trade_mark_sign == UNBOUND) {
	unicode = (SI_Long)8482L;
	row = unicode >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & unicode;
	    G2int_gensym_code_for_trade_mark_sign = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	}
	else
	    G2int_gensym_code_for_trade_mark_sign = Nil;
    }
    if (G2int_gensym_char_or_code_for_trade_mark_sign == UNBOUND)
	G2int_gensym_char_or_code_for_trade_mark_sign = CHR(':');
    if (G2int_gensym_esc_for_trade_mark_signqm == UNBOUND)
	G2int_gensym_esc_for_trade_mark_signqm = CHR('~');
    if (G2int_current_extended_utf_g_low_half_characterqm == UNBOUND)
	G2int_current_extended_utf_g_low_half_characterqm = Nil;
    Qg2int_pctspace = STATIC_SYMBOL("%SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctspace,FIX((SI_Long)32L));
    Qg2int_pctsp = STATIC_SYMBOL("%SP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctsp,FIX((SI_Long)32L));
    Qg2int_pctnewline = STATIC_SYMBOL("%NEWLINE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctnewline,FIX((SI_Long)10L));
    Qg2int_pctlinefeed = STATIC_SYMBOL("%LINEFEED",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctlinefeed,FIX((SI_Long)10L));
    Qg2int_pctreturn = STATIC_SYMBOL("%RETURN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctreturn,FIX((SI_Long)13L));
    Qg2int_pcttab = STATIC_SYMBOL("%TAB",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcttab,FIX((SI_Long)9L));
    Qg2int_pctpage = STATIC_SYMBOL("%PAGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctpage,FIX((SI_Long)12L));
    Qg2int_pctnull = STATIC_SYMBOL("%NULL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctnull,FIX((SI_Long)0L));
    Qg2int_pctescape = STATIC_SYMBOL("%ESCAPE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctescape,FIX((SI_Long)27L));
    Qg2int_pctesc = STATIC_SYMBOL("%ESC",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctesc,FIX((SI_Long)27L));
    Qg2int_pctline_separator = STATIC_SYMBOL("%LINE-SEPARATOR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctline_separator,FIX((SI_Long)8232L));
    Qg2int_pctparagraph_separator = STATIC_SYMBOL("%PARAGRAPH-SEPARATOR",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctparagraph_separator,FIX((SI_Long)8233L));
    Qg2int_pctordinary_space = STATIC_SYMBOL("%ORDINARY-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctordinary_space,FIX((SI_Long)32L));
    Qg2int_pctfixed_width_space = STATIC_SYMBOL("%FIXED-WIDTH-SPACE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctfixed_width_space,FIX((SI_Long)8199L));
    Qg2int_pctno_break_space = STATIC_SYMBOL("%NO-BREAK-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctno_break_space,FIX((SI_Long)160L));
    Qg2int_pctzero_width_no_break_space = 
	    STATIC_SYMBOL("%ZERO-WIDTH-NO-BREAK-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctzero_width_no_break_space,FIX((SI_Long)65279L));
    Qg2int_pctsoft_hyphen = STATIC_SYMBOL("%SOFT-HYPHEN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctsoft_hyphen,FIX((SI_Long)173L));
    Qg2int_pctcopyright_sign = STATIC_SYMBOL("%COPYRIGHT-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctcopyright_sign,FIX((SI_Long)169L));
    Qg2int_pctregistered_sign = STATIC_SYMBOL("%REGISTERED-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctregistered_sign,FIX((SI_Long)174L));
    Qg2int_pcttrade_mark_sign = STATIC_SYMBOL("%TRADE-MARK-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcttrade_mark_sign,FIX((SI_Long)8482L));
    Qg2int_pctcapital_ligature_oe = STATIC_SYMBOL("%CAPITAL-LIGATURE-OE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctcapital_ligature_oe,FIX((SI_Long)338L));
    Qg2int_pctsmall_ligature_oe = STATIC_SYMBOL("%SMALL-LIGATURE-OE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctsmall_ligature_oe,FIX((SI_Long)339L));
    Qg2int_pctbullet = STATIC_SYMBOL("%BULLET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctbullet,FIX((SI_Long)8226L));
    Qg2int_pctlatin_small_letter_f_with_hook = 
	    STATIC_SYMBOL("%LATIN-SMALL-LETTER-F-WITH-HOOK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctlatin_small_letter_f_with_hook,
	    FIX((SI_Long)402L));
    Qg2int_pcthair_space = STATIC_SYMBOL("%HAIR-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcthair_space,FIX((SI_Long)8202L));
    Qg2int_pctthin_space = STATIC_SYMBOL("%THIN-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctthin_space,FIX((SI_Long)8201L));
    Qg2int_pcten_space = STATIC_SYMBOL("%EN-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcten_space,FIX((SI_Long)8194L));
    Qg2int_pctem_space = STATIC_SYMBOL("%EM-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctem_space,FIX((SI_Long)8193L));
    Qg2int_pctzero_width_space = STATIC_SYMBOL("%ZERO-WIDTH-SPACE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctzero_width_space,FIX((SI_Long)8203L));
    Qg2int_pctzero_width_joiner = STATIC_SYMBOL("%ZERO-WIDTH-JOINER",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctzero_width_joiner,FIX((SI_Long)8205L));
    Qg2int_pctinverted_exclamation_point = 
	    STATIC_SYMBOL("%INVERTED-EXCLAMATION-POINT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctinverted_exclamation_point,FIX((SI_Long)161L));
    Qg2int_pctcent_sign = STATIC_SYMBOL("%CENT-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctcent_sign,FIX((SI_Long)162L));
    Qg2int_pctpound_sign = STATIC_SYMBOL("%POUND-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctpound_sign,FIX((SI_Long)163L));
    Qg2int_pctyen_sign = STATIC_SYMBOL("%YEN-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctyen_sign,FIX((SI_Long)165L));
    Qg2int_pctright_pointing_double_angle_quotation_mark = 
	    STATIC_SYMBOL("%RIGHT-POINTING-DOUBLE-ANGLE-QUOTATION-MARK",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctright_pointing_double_angle_quotation_mark,
	    FIX((SI_Long)187L));
    Qg2int_pctleft_pointing_double_angle_quotation_mark = 
	    STATIC_SYMBOL("%LEFT-POINTING-DOUBLE-ANGLE-QUOTATION-MARK",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctleft_pointing_double_angle_quotation_mark,
	    FIX((SI_Long)171L));
    Qg2int_pctinverted_question_mark = 
	    STATIC_SYMBOL("%INVERTED-QUESTION-MARK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctinverted_question_mark,FIX((SI_Long)191L));
    Qg2int_pcteuro_sign = STATIC_SYMBOL("%EURO-SIGN",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcteuro_sign,FIX((SI_Long)8364L));
    Qab_g2int_pctsp = STATIC_SYMBOL("% ",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctsp,FIX((SI_Long)32L));
    Qg2int_pctex = STATIC_SYMBOL("%!",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctex,FIX((SI_Long)33L));
    Qg2int_pctdq = STATIC_SYMBOL("%\"",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctdq,FIX((SI_Long)34L));
    Qg2int_pctno = STATIC_SYMBOL("%#",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctno,FIX((SI_Long)35L));
    Qg2int_pctdol = STATIC_SYMBOL("%$",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctdol,FIX((SI_Long)36L));
    Qg2int_pctpct = STATIC_SYMBOL("%%",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctpct,FIX((SI_Long)37L));
    Qg2int_pctand = STATIC_SYMBOL("%&",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctand,FIX((SI_Long)38L));
    Qg2int_pctqu = STATIC_SYMBOL("%\'",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctqu,FIX((SI_Long)39L));
    Qg2int_pctop = STATIC_SYMBOL("%(",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctop,FIX((SI_Long)40L));
    Qg2int_pctcp = STATIC_SYMBOL("%)",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctcp,FIX((SI_Long)41L));
    Qg2int_pctstar = STATIC_SYMBOL("%*",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctstar,FIX((SI_Long)42L));
    Qg2int_pctplus = STATIC_SYMBOL("%+",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctplus,FIX((SI_Long)43L));
    Qg2int_pctcm = STATIC_SYMBOL("%,",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctcm,FIX((SI_Long)44L));
    Qg2int_pct_ = STATIC_SYMBOL("%-",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct_,FIX((SI_Long)45L));
    Qg2int_pctdot = STATIC_SYMBOL("%.",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctdot,FIX((SI_Long)46L));
    Qg2int_pctsl = STATIC_SYMBOL("%/",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctsl,FIX((SI_Long)47L));
    Qg2int_pct0 = STATIC_SYMBOL("%0",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct0,FIX((SI_Long)48L));
    Qg2int_pct1 = STATIC_SYMBOL("%1",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct1,FIX((SI_Long)49L));
    Qg2int_pct2 = STATIC_SYMBOL("%2",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct2,FIX((SI_Long)50L));
    Qg2int_pct3 = STATIC_SYMBOL("%3",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct3,FIX((SI_Long)51L));
    Qg2int_pct4 = STATIC_SYMBOL("%4",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct4,FIX((SI_Long)52L));
    Qg2int_pct5 = STATIC_SYMBOL("%5",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct5,FIX((SI_Long)53L));
    Qg2int_pct6 = STATIC_SYMBOL("%6",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct6,FIX((SI_Long)54L));
    Qg2int_pct7 = STATIC_SYMBOL("%7",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct7,FIX((SI_Long)55L));
    Qg2int_pct8 = STATIC_SYMBOL("%8",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct8,FIX((SI_Long)56L));
    Qg2int_pct9 = STATIC_SYMBOL("%9",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pct9,FIX((SI_Long)57L));
    Qg2int_pctcol = STATIC_SYMBOL("%:",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctcol,FIX((SI_Long)58L));
    Qg2int_pctsc = STATIC_SYMBOL("%;",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctsc,FIX((SI_Long)59L));
    Qg2int_pctlt = STATIC_SYMBOL("%<",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctlt,FIX((SI_Long)60L));
    Qg2int_pcteq = STATIC_SYMBOL("%=",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcteq,FIX((SI_Long)61L));
    Qg2int_pctgt = STATIC_SYMBOL("%>",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctgt,FIX((SI_Long)62L));
    Qg2int_pctqm = STATIC_SYMBOL("%\?",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctqm,FIX((SI_Long)63L));
    Qg2int_pctat = STATIC_SYMBOL("%@",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctat,FIX((SI_Long)64L));
    Qg2int_pcta = STATIC_SYMBOL("%A",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcta,FIX((SI_Long)65L));
    Qg2int_pctb = STATIC_SYMBOL("%B",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctb,FIX((SI_Long)66L));
    Qg2int_pctc = STATIC_SYMBOL("%C",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctc,FIX((SI_Long)67L));
    Qg2int_pctd = STATIC_SYMBOL("%D",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctd,FIX((SI_Long)68L));
    Qg2int_pcte = STATIC_SYMBOL("%E",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcte,FIX((SI_Long)69L));
    Qg2int_pctf = STATIC_SYMBOL("%F",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctf,FIX((SI_Long)70L));
    Qg2int_pctg = STATIC_SYMBOL("%G",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctg,FIX((SI_Long)71L));
    Qg2int_pcth = STATIC_SYMBOL("%H",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcth,FIX((SI_Long)72L));
    Qg2int_pcti = STATIC_SYMBOL("%I",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcti,FIX((SI_Long)73L));
    Qg2int_pctj = STATIC_SYMBOL("%J",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctj,FIX((SI_Long)74L));
    Qg2int_pctk = STATIC_SYMBOL("%K",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctk,FIX((SI_Long)75L));
    Qg2int_pctl = STATIC_SYMBOL("%L",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctl,FIX((SI_Long)76L));
    Qg2int_pctm = STATIC_SYMBOL("%M",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctm,FIX((SI_Long)77L));
    Qg2int_pctn = STATIC_SYMBOL("%N",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctn,FIX((SI_Long)78L));
    Qg2int_pcto = STATIC_SYMBOL("%O",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcto,FIX((SI_Long)79L));
    Qg2int_pctp = STATIC_SYMBOL("%P",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctp,FIX((SI_Long)80L));
    Qg2int_pctq = STATIC_SYMBOL("%Q",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctq,FIX((SI_Long)81L));
    Qg2int_pctr = STATIC_SYMBOL("%R",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctr,FIX((SI_Long)82L));
    Qg2int_pcts = STATIC_SYMBOL("%S",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcts,FIX((SI_Long)83L));
    Qg2int_pctt = STATIC_SYMBOL("%T",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctt,FIX((SI_Long)84L));
    Qg2int_pctu = STATIC_SYMBOL("%U",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctu,FIX((SI_Long)85L));
    Qg2int_pctv = STATIC_SYMBOL("%V",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctv,FIX((SI_Long)86L));
    Qg2int_pctw = STATIC_SYMBOL("%W",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctw,FIX((SI_Long)87L));
    Qg2int_pctx = STATIC_SYMBOL("%X",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctx,FIX((SI_Long)88L));
    Qg2int_pcty = STATIC_SYMBOL("%Y",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcty,FIX((SI_Long)89L));
    Qg2int_pctz = STATIC_SYMBOL("%Z",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctz,FIX((SI_Long)90L));
    Qg2int_pctobt = STATIC_SYMBOL("%[",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctobt,FIX((SI_Long)91L));
    Qg2int_pctbs = STATIC_SYMBOL("%\\",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctbs,FIX((SI_Long)92L));
    Qg2int_pctcbt = STATIC_SYMBOL("%]",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctcbt,FIX((SI_Long)93L));
    Qg2int_pctct = STATIC_SYMBOL("%^",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctct,FIX((SI_Long)94L));
    Qab_g2int_pct_ = STATIC_SYMBOL("%_",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pct_,FIX((SI_Long)95L));
    Qg2int_pctbq = STATIC_SYMBOL("%`",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctbq,FIX((SI_Long)96L));
    Qab_g2int_pcta = STATIC_SYMBOL("%a",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pcta,FIX((SI_Long)97L));
    Qab_g2int_pctb = STATIC_SYMBOL("%b",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctb,FIX((SI_Long)98L));
    Qab_g2int_pctc = STATIC_SYMBOL("%c",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctc,FIX((SI_Long)99L));
    Qab_g2int_pctd = STATIC_SYMBOL("%d",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctd,FIX((SI_Long)100L));
    Qab_g2int_pcte = STATIC_SYMBOL("%e",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pcte,FIX((SI_Long)101L));
    Qab_g2int_pctf = STATIC_SYMBOL("%f",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctf,FIX((SI_Long)102L));
    Qab_g2int_pctg = STATIC_SYMBOL("%g",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctg,FIX((SI_Long)103L));
    Qab_g2int_pcth = STATIC_SYMBOL("%h",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pcth,FIX((SI_Long)104L));
    Qab_g2int_pcti = STATIC_SYMBOL("%i",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pcti,FIX((SI_Long)105L));
    Qab_g2int_pctj = STATIC_SYMBOL("%j",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctj,FIX((SI_Long)106L));
    Qab_g2int_pctk = STATIC_SYMBOL("%k",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctk,FIX((SI_Long)107L));
    Qab_g2int_pctl = STATIC_SYMBOL("%l",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctl,FIX((SI_Long)108L));
    Qab_g2int_pctm = STATIC_SYMBOL("%m",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctm,FIX((SI_Long)109L));
    Qab_g2int_pctn = STATIC_SYMBOL("%n",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctn,FIX((SI_Long)110L));
    Qab_g2int_pcto = STATIC_SYMBOL("%o",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pcto,FIX((SI_Long)111L));
    Qab_g2int_pctp = STATIC_SYMBOL("%p",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctp,FIX((SI_Long)112L));
    Qab_g2int_pctq = STATIC_SYMBOL("%q",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctq,FIX((SI_Long)113L));
    Qab_g2int_pctr = STATIC_SYMBOL("%r",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctr,FIX((SI_Long)114L));
    Qab_g2int_pcts = STATIC_SYMBOL("%s",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pcts,FIX((SI_Long)115L));
    Qab_g2int_pctt = STATIC_SYMBOL("%t",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctt,FIX((SI_Long)116L));
    Qab_g2int_pctu = STATIC_SYMBOL("%u",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctu,FIX((SI_Long)117L));
    Qab_g2int_pctv = STATIC_SYMBOL("%v",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctv,FIX((SI_Long)118L));
    Qab_g2int_pctw = STATIC_SYMBOL("%w",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctw,FIX((SI_Long)119L));
    Qab_g2int_pctx = STATIC_SYMBOL("%x",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctx,FIX((SI_Long)120L));
    Qab_g2int_pcty = STATIC_SYMBOL("%y",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pcty,FIX((SI_Long)121L));
    Qab_g2int_pctz = STATIC_SYMBOL("%z",AB_package);
    SET_SYMBOL_VALUE(Qab_g2int_pctz,FIX((SI_Long)122L));
    Qg2int_pctob = STATIC_SYMBOL("%{",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctob,FIX((SI_Long)123L));
    Qg2int_pctor = STATIC_SYMBOL("%|",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctor,FIX((SI_Long)124L));
    Qg2int_pctcb = STATIC_SYMBOL("%}",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pctcb,FIX((SI_Long)125L));
    Qg2int_pcttl = STATIC_SYMBOL("%~",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pcttl,FIX((SI_Long)126L));
}
