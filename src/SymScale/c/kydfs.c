/* kydfs.c
 * Input file:  keydefs.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kydfs.h"


static Object Qcyrillic_gensym_character_code_for_key_name;  /* cyrillic-gensym-character-code-for-key-name */

/* CONVERT-KEY-CODE-TO-GENSYM-CYRILLIC-CHARACTER-CODE */
Object convert_key_code_to_gensym_cyrillic_character_code(key_code)
    Object key_code;
{
    Object key_name_qm, temp;

    x_note_fn_call(21,0);
    key_name_qm = (SI_Long)1697L <= IFIX(key_code) && IFIX(key_code) <= 
	    (SI_Long)1791L ? ISVREF(Key_index_to_key_symbol_array,
	    IFIX(key_code)) : Nil;
    temp = key_name_qm ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(key_name_qm),
	    Qcyrillic_gensym_character_code_for_key_name) : Nil;
    return VALUES_1(temp);
}

/* CONVERT-KEY-CODE-TO-GENSYM-CHARACTER */
Object convert_key_code_to_gensym_character(key_code)
    Object key_code;
{
    Object unicode, code, extended_code, unicode_1, code_1, temp, row;
    Object gensym_character_code_qm;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(21,1);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	code = Nil;
	extended_code = Nil;
	unicode_1 = unicode;
	extended_code = Nil;
	code_1 = unicode_1;
	if (IFIX(code_1) < (SI_Long)127L &&  !((SI_Long)64L == 
		IFIX(code_1) || (SI_Long)126L == IFIX(code_1) || 
		(SI_Long)92L == IFIX(code_1))) {
	    code = unicode_1;
	    temp = code;
	}
	else {
	    row = FIX(IFIX(unicode_1) >>  -  - (SI_Long)8L);
	    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	      gensym_full_row = 
		      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
		      IFIX(Row));
	      if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
		  gensymed_symbol = gensym_full_row << (SI_Long)8L;
		  gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
		  gensym_character_code_qm = FIX(gensymed_symbol + 
			  gensymed_symbol_1);
	      }
	      else
		  gensym_character_code_qm = Nil;
	    POP_SPECIAL();
	    if (gensym_character_code_qm) {
		temp_1 = IFIX(gensym_character_code_qm) < (SI_Long)256L ? 
			TRUEP(ISVREF(Iso_latin1_special_character_code_map,
			IFIX(gensym_character_code_qm))) : TRUEP(Nil);
		if (temp_1);
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_capital_ligature_oe))
		    temp_1 = 'W';
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_small_ligature_oe))
		    temp_1 = 'w';
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_bullet))
		    temp_1 = '*';
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_small_letter_f_with_hook))
		    temp_1 = '&';
		else if (FIXNUM_EQ(gensym_character_code_qm,
			Gensym_code_for_trade_mark_sign))
		    temp_1 = ':';
		else
		    temp_1 = TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = (SI_Long)8192L <= 
			    IFIX(gensym_character_code_qm) ? 
			    IFIX(gensym_character_code_qm) <= 
			    (SI_Long)8447L : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		code = gensym_character_code_qm;
		temp = code;
	    }
	    else
		temp = Nil;
	    if (temp);
	    else {
		code = map_unicode_to_gensym_han_character_code(unicode_1);
		temp = code;
		if (temp);
		else {
		    row = FIX(IFIX(unicode_1) >>  -  - (SI_Long)8L);
		    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		      gensym_full_row = 
			      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
			      IFIX(Row));
		      if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			  gensymed_symbol = gensym_full_row << (SI_Long)8L;
			  gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
			  code = FIX(gensymed_symbol + gensymed_symbol_1);
		      }
		      else
			  code = Nil;
		    POP_SPECIAL();
		    temp = code;
		    if (temp);
		    else {
			gensymed_symbol = (SI_Long)63488L;
			gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
			extended_code = FIX(gensymed_symbol + 
				gensymed_symbol_1);
			code = FIX((SI_Long)63232L + (IFIX(unicode_1) >>  
				-  - (SI_Long)8L));
			temp = code;
		    }
		}
	    }
	}
	return VALUES_2(temp,extended_code);
    }
    else {
	if ((SI_Long)32L <= IFIX(key_code) && IFIX(key_code) <= 
		(SI_Long)126L &&  !(IFIX(key_code) == (SI_Long)64L) &&  
		!(IFIX(key_code) == (SI_Long)126L) &&  !(IFIX(key_code) == 
		(SI_Long)92L)) {
	    temp = CODE_CHAR(key_code);
	    return VALUES_2(temp,Nil);
	}
	else {
	    if ((SI_Long)32L <= IFIX(key_code) && IFIX(key_code) <= 
		    (SI_Long)255L ? 
		    TRUEP(ISVREF(Iso_latin1_special_character_code_map,
		    IFIX(key_code))) : TRUEP(Nil)) {
		temp = ISVREF(Iso_latin1_special_character_code_map,
			IFIX(key_code));
		return VALUES_2(temp,CHR('~'));
	    }
	    else if ((SI_Long)1697L <= IFIX(key_code) && IFIX(key_code) <= 
		    (SI_Long)1791L) {
		temp = 
			convert_key_code_to_gensym_cyrillic_character_code(key_code);
		return VALUES_2(temp,CHR('\\'));
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
}

/* CONVERT-KEY-CODE-TO-UNICODE */
Object convert_key_code_to_unicode(key_code)
    Object key_code;
{
    Object character_or_character_code_qm, escape_character_qm;
    Object gensym_character_code, temp, row;
    SI_Long unicode_full_row, gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(21,2);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L)
	return VALUES_1(FIXNUM_LOGAND(Unicode_character_bits,key_code));
    else {
	result = convert_key_code_to_gensym_character(key_code);
	MVS_2(result,character_or_character_code_qm,escape_character_qm);
	if (character_or_character_code_qm) {
	    if ( !TRUEP(escape_character_qm))
		gensym_character_code = 
			CHAR_CODE(character_or_character_code_qm);
	    else {
		if (CHAR_EQ(escape_character_qm,CHR('~'))) {
		    gensym_character_code = 
			    ISVREF(Reverse_iso_latin1_special_character_code_map,
			    IFIX(CHAR_CODE(character_or_character_code_qm)));
		    if (gensym_character_code);
		    else {
			temp = CHAR_CODE(character_or_character_code_qm);
			if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    gensym_character_code = Nil;
			else
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 87:
				gensym_character_code = 
					Gensym_code_for_capital_ligature_oe;
				break;
			      case 119:
				gensym_character_code = 
					Gensym_code_for_small_ligature_oe;
				break;
			      case 42:
				gensym_character_code = Gensym_code_for_bullet;
				break;
			      case 38:
				gensym_character_code = 
					Gensym_code_for_small_letter_f_with_hook;
				break;
			      case 58:
				gensym_character_code = 
					Gensym_code_for_trade_mark_sign;
				break;
			      default:
				gensym_character_code = Nil;
				break;
			    }
		    }
		}
		else
		    gensym_character_code = Nil;
		if (gensym_character_code);
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(Gensym_esc_for_linebreak_qm) ? 
			CHAR_EQ(character_or_character_code_qm,
			Gensym_char_or_code_for_linebreak) : 
			EQL(character_or_character_code_qm,
			Gensym_char_or_code_for_linebreak) && 
			EQL(escape_character_qm,Gensym_esc_for_linebreak_qm))
		    gensym_character_code = Gensym_code_for_linebreak;
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(Gensym_esc_for_paragraph_break_qm) ? 
			CHAR_EQ(character_or_character_code_qm,
			Gensym_char_or_code_for_paragraph_break) : 
			EQL(character_or_character_code_qm,
			Gensym_char_or_code_for_paragraph_break) && 
			EQL(escape_character_qm,
			Gensym_esc_for_paragraph_break_qm))
		    gensym_character_code = Gensym_code_for_paragraph_break;
		else {
		    gensym_character_code =  !EQ(escape_character_qm,
			    CHR('\\')) ? FIX((SI_Long)65535L) : Nil;
		    if (gensym_character_code);
		    else
			gensym_character_code = character_or_character_code_qm;
		}
	    }
	    temp_1 = IFIX(gensym_character_code) < (SI_Long)256L ? 
		    TRUEP(ISVREF(Iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code))) : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_capital_ligature_oe))
		temp_1 = 'W';
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_small_ligature_oe))
		temp_1 = 'w';
	    else if (FIXNUM_EQ(gensym_character_code,Gensym_code_for_bullet))
		temp_1 = '*';
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_small_letter_f_with_hook))
		temp_1 = '&';
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_trade_mark_sign))
		temp_1 = ':';
	    else
		temp_1 = TRUEP(Qnil);
	    if (temp_1) {
		row = FIX(IFIX(gensym_character_code) >>  -  - (SI_Long)8L);
		PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		  unicode_full_row = 
			  UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
			  IFIX(Row));
		  if ( !(unicode_full_row == IFIX(Invalid_unicode_full_row))) {
		      gensymed_symbol = unicode_full_row << (SI_Long)8L;
		      gensymed_symbol_1 = (SI_Long)255L & 
			      IFIX(gensym_character_code);
		      result = VALUES_1(FIX(gensymed_symbol + 
			      gensymed_symbol_1));
		  }
		  else
		      result = VALUES_1(Nil);
		POP_SPECIAL();
		return result;
	    }
	    else if ((SI_Long)8192L <= IFIX(gensym_character_code) && 
		    IFIX(gensym_character_code) <= (SI_Long)8447L) {
		row = FIX(IFIX(gensym_character_code) >>  -  - (SI_Long)8L);
		PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		  unicode_full_row = 
			  UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
			  IFIX(Row));
		  if ( !(unicode_full_row == IFIX(Invalid_unicode_full_row))) {
		      gensymed_symbol = unicode_full_row << (SI_Long)8L;
		      gensymed_symbol_1 = (SI_Long)255L & 
			      IFIX(gensym_character_code);
		      result = VALUES_1(FIX(gensymed_symbol + 
			      gensymed_symbol_1));
		  }
		  else
		      result = VALUES_1(Nil);
		POP_SPECIAL();
		return result;
	    }
	    else {
		temp = 
			map_gensym_han_character_code_to_unicode(gensym_character_code);
		if (temp)
		    return VALUES_1(temp);
		else {
		    row = FIX(IFIX(gensym_character_code) >>  -  - 
			    (SI_Long)8L);
		    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		      unicode_full_row = 
			      UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
			      IFIX(Row));
		      if ( !(unicode_full_row == 
			      IFIX(Invalid_unicode_full_row))) {
			  gensymed_symbol = unicode_full_row << (SI_Long)8L;
			  gensymed_symbol_1 = (SI_Long)255L & 
				  IFIX(gensym_character_code);
			  temp = FIX(gensymed_symbol + gensymed_symbol_1);
		      }
		      else
			  temp = Nil;
		    POP_SPECIAL();
		    if (temp)
			return VALUES_1(temp);
		    else if (Current_extended_utf_g_low_half_character_qm)
			return map_extended_utf_g_characters_to_unicode(Current_extended_utf_g_low_half_character_qm,
				gensym_character_code);
		    else
			return VALUES_1(FIX((SI_Long)65535L));
		}
	    }
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object list_constant;       /* # */

/* PRINTABLE-CHARACTER-KEY-CODE-P */
Object printable_character_key_code_p(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(21,3);
    temp = IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L ? 
	    memq_function(classify_character_for_text_line_drawing_function(FIXNUM_LOGAND(Unicode_character_bits,
	    key_code)),list_constant) : 
	    convert_key_code_to_gensym_character(key_code);
    return VALUES_1(temp);
}

static Object Qleft;               /* left */

static Object Qmiddle;             /* middle */

static Object Qright;              /* right */

static Object Qany;                /* any */

/* MOUSE-KEY-CODE-BUTTON-NAME-SYMBOL */
Object mouse_key_code_button_name_symbol(mouse_key_code)
    Object mouse_key_code;
{
    SI_Long temp;

    x_note_fn_call(21,4);
    temp = IFIX(mouse_key_code) | (SI_Long)1L;
    if ( !((SI_Long)-32768L <= temp && temp <= (SI_Long)32767L))
	return VALUES_1(Nil);
    else
	switch ((short)temp) {
	  case 773:
	    return VALUES_1(Qleft);
	  case 775:
	    return VALUES_1(Qmiddle);
	  case 777:
	    return VALUES_1(Qright);
	  case 769:
	    return VALUES_1(Qany);
	  default:
	    return VALUES_1(Nil);
	}
}

/* PSEUDO-KEY-CODE-P */
Object pseudo_key_code_p(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(21,5);
    temp = convert_key_code_to_key_symbol(key_code);
    return VALUES_1( ! !TRUEP(memq_function(temp,Pseudo_keysyms)) ? T : Nil);
}

void keydefs_INIT()
{
    Object Qundo, AB_package, Qterm, Qstatus, Qsystem, Qscroll, Qline;
    Object Qcomplete, Qpage, Qsuspend, Qtriangle, Qcircle, Qsquare, Qrefresh;
    Object Qresume, Qnetwork, Qnext_screen, Qprevious_screen, Qright_arrow;
    Object Qleft_arrow, Qdown_arrow, Qup_arrow, Qpage_down, Qpage_up;
    Object Qforward_delete, Qclear_screen, Qabort_g2, Qexecute, Qselect;
    Object Qpause, Qend, Qbegin, Qhome, Qmenu, Qredo, Qinsert, Qhelp, Qkp_9;
    Object Qkp_8, Qkp_7, Qkp_6, Qkp_5, Qkp_4, Qkp_3, Qkp_2, Qkp_1, Qkp_0;
    Object Qkp_divide, Qkp_decimal, Qkp_subtract, Qkp_separator, Qkp_add;
    Object Qkp_multiply, Qkp_equal, Qkp_f4, Qkp_f3, Qkp_f2, Qkp_f1, Qkp_enter;
    Object Qkp_tab, Qkp_space, Qenter, Qlist_sys_drives, Qtabular_view;
    Object Qgrid_view, Qdialog_user_gesture, Qprop_grid, Qlogin_dialog;
    Object Qlogbook_view, Qchart_view, Qshortcut_bar, Qnms_menu_unposted;
    Object Qeditor, Qdebugger_dialog, Qhtml_view, Qtree_view;
    Object Qnms_menu_item_selected, Qdialog_miscellaneous_communication;
    Object Qlist_directory, Qdialog_dismissed, Qdialog_update, Qnms_control;
    Object Qbasic_dialog, Qnms_menu_posted, Qprint_dialog, Qabout_box;
    Object Qprint_window, Qpre_nms_menu_choice, Qstatus_bar, Qfile_dialog;
    Object Qmenu_bar, Qmouse_right_drag, Qmouse_middle_drag, Qmouse_left_drag;
    Object Qmouse_right_select, Qmouse_middle_select, Qmouse_left_select;
    Object Qvscroll, Qhscroll, Qfile_save_as, Qfile_open, Qmenu_choice;
    Object Qsimple_dialog_additional, Qsimple_dialog_cancel, Qsimple_dialog_ok;
    Object Qdouble_escape, Qwindow_scrolled, Qwindow_sized, Qwindow_moved;
    Object Qleave_window, Qenter_window, Qwindow_closed, Qwindow_activated;
    Object Qpaste_availability_request, Qpaste_request, Qwindow_reshape;
    Object Qwindow_refresh, Qmouse_hover, Qmouse_wheel_backward;
    Object Qmouse_wheel_forward, Qmouse_select, Qmouse_drag, Qmouse_right_up;
    Object Qmouse_right_down, Qmouse_middle_up, Qmouse_middle_down;
    Object Qmouse_left_up, Qmouse_left_down, Qmouse_motion, Qmouse_down;
    Object Qmouse_up, Qnon_event, Qrubout, Qdel, Qordinary_space;
    Object Qnon_spacing_mark, Qmark, QCyrillic_HARDSIGN, QCyrillic_CHE;
    Object QCyrillic_SHCHA, QCyrillic_E, QCyrillic_SHA, QCyrillic_ZE;
    Object QCyrillic_YERU, QCyrillic_SOFTSIGN, QCyrillic_VE, QCyrillic_ZHE;
    Object QCyrillic_U, QCyrillic_TE, QCyrillic_ES, QCyrillic_ER, QCyrillic_YA;
    Object QCyrillic_PE, QCyrillic_O, QCyrillic_EN, QCyrillic_EM, QCyrillic_EL;
    Object QCyrillic_KA, QCyrillic_SHORTI, QCyrillic_I, QCyrillic_HA;
    Object QCyrillic_GHE, QCyrillic_EF, QCyrillic_IE, QCyrillic_DE;
    Object QCyrillic_TSE, QCyrillic_BE, QCyrillic_A, QCyrillic_YU;
    Object QCyrillic_hardsign, QCyrillic_che, QCyrillic_shcha, QCyrillic_e;
    Object QCyrillic_sha, QCyrillic_ze, QCyrillic_yeru, QCyrillic_softsign;
    Object QCyrillic_ve, QCyrillic_zhe, QCyrillic_u, QCyrillic_te;
    Object QCyrillic_es, QCyrillic_er, QCyrillic_ya, QCyrillic_pe, QCyrillic_o;
    Object QCyrillic_en, QCyrillic_em, QCyrillic_el, QCyrillic_ka;
    Object QCyrillic_shorti, QCyrillic_i, QCyrillic_ha, QCyrillic_ghe;
    Object QCyrillic_ef, QCyrillic_ie, QCyrillic_de, QCyrillic_tse;
    Object QCyrillic_be, QCyrillic_a, QCyrillic_yu, QCyrillic_DZHE;
    Object QByelorussian_SHORTU, QMacedonia_KJE, QSerbian_TSHE, QCyrillic_NJE;
    Object QCyrillic_LJE, QCyrillic_JE, QUkrainian_YI, QUkrainian_I;
    Object QMacedonia_DSE, QUkrainian_IE, QCyrillic_IO, QMacedonia_GJE;
    Object QSerbian_DJE, QNUMEROSIGN, QCyrillic_dzhe, QByelorussian_shortu;
    Object QMacedonia_kje, QSerbian_tshe, QCyrillic_nje, QCyrillic_lje;
    Object QCyrillic_je, QUkrainian_yi, QUkrainian_i, QMacedonia_dse;
    Object QUkrainian_ie, QCyrillic_io, QMacedonia_gje, QSerbian_dje;
    Object QYDIAERESIS, QTHORN, QYACUTE, QUDIAERESIS, QUCIRCUMFLEX, QUACUTE;
    Object QUGRAVE, QOSLASH, QDIVISION, QODIAERESIS, QOTILDE, QOCIRCUMFLEX;
    Object QOACUTE, QOGRAVE, QNTILDE, QETH, QIDIAERESIS, QICIRCUMFLEX, QIACUTE;
    Object QIGRAVE, QEDIAERESIS, QECIRCUMFLEX, QEACUTE, QEGRAVE, QCCEDILLA;
    Object QAE, QARING, QADIAERESIS, QATILDE, QACIRCUMFLEX, QAACUTE, QAGRAVE;
    Object QSSHARP, Qthorn, QYacute, QUdiaeresis, QUcircumflex, QUacute;
    Object QUgrave, QOoblique, QMULTIPLY, QOdiaeresis, QOtilde, QOcircumflex;
    Object QOacute, QOgrave, QNtilde, Qeth, QIdiaeresis, QIcircumflex, QIacute;
    Object QIgrave, QEdiaeresis, QEcircumflex, QEacute, QEgrave, QCcedilla;
    Object Qae, QAring, QAdiaeresis, QAtilde, QAcircumflex, QAacute, QAgrave;
    Object QQUESTIONDOWN, QTHREEQUARTERS, QONEHALF, QONEQUARTER;
    Object QGUILLEMOTRIGHT, QMASCULINE, QONESUPERIOR, QCEDILLA;
    Object QPERIODCENTERED, QPARAGRAPH, QMU, QACUTE, QTHREESUPERIOR;
    Object QTWOSUPERIOR, QPLUSMINUS, QDEGREE, QMACRON, QREGISTERED, QHYPHEN;
    Object QNOTSIGN, QGUILLEMOTLEFT, QORDFEMININE, QCOPYRIGHT, QDIAERESIS;
    Object QSECTION, QBROKENBAR, QYEN, QCURRENCY, QSTERLING, QCENT;
    Object QEXCLAMDOWN, QNOBREAKSPACE, Qdot, Qcm, Qcp, Qop, Qqu, Qab_and, Qpct;
    Object Qdol, Qno, Qdq, Qex, Qtl_tl, Qcb, Qab_or_1, Qob, QZ, QY, QX, QW, QV;
    Object QU, QT, QS, QR, QQ, QP, QO, QN, QM, QL, QK, QJ, QI, QH, QG, QF, QE;
    Object QD, QC, QB, QA, Qbq, Q_, Qct, Qcbt, Qtl_bs, Qobt, Qz, Qy, Qx, Qw;
    Object Qv, Qu, Qs, Qr, Qq, Qp, Qo, Qn, Qm, Ql, Qk, Qj, Qi, Qh, Qg, Qf, Qe;
    Object Qd, Qc, Qb, Qa, Qtl_at, Qqm, Qsc, Qcol, Q9, Q8, Q7, Q6, Q5, Q4, Q3;
    Object Q2, Q1, Q0, Qescape, Qlinefeed, Qtab, Qbackspace, Qf35, Qf34, Qf33;
    Object Qf32, Qf31, Qf30, Qf29, Qf28, Qf27, Qf26, Qf25, Qf24, Qf23, Qf22;
    Object Qf21, Qf20, Qf19, Qf18, Qf17, Qf16, Qf15, Qf14, Qf13, Qf12, Qf11;
    Object Qf10, Qf9, Qf8, Qf7, Qf6, Qf5, Qf4, Qf3, Qf2, Qf1, QControl_plus_;
    Object QControl_plus_ct, QControl_plus_cbt, QControl_plus_tl_bs;
    Object QControl_plus_obt, QControl_plus_z, QControl_plus_y;
    Object QControl_plus_x, QControl_plus_w, QControl_plus_v, QControl_plus_u;
    Object QControl_plus_t, QControl_plus_s, QControl_plus_r, QControl_plus_q;
    Object QControl_plus_p, QControl_plus_o, QControl_plus_n, QControl_plus_m;
    Object QControl_plus_l, QControl_plus_k, QControl_plus_j, QControl_plus_i;
    Object QControl_plus_h, QControl_plus_g, QControl_plus_f, QControl_plus_e;
    Object QControl_plus_d, QControl_plus_c, QControl_plus_b, QControl_plus_a;
    Object QControl_plus_tl_at, QIllegal_Key, Qillegal_key;

    x_note_fn_call(21,6);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qillegal_key = STATIC_SYMBOL("ILLEGAL-KEY",AB_package);
    QIllegal_Key = STATIC_SYMBOL("Illegal-Key",AB_package);
    define_key_symbol_1(Qillegal_key,FIX((SI_Long)2047L),QIllegal_Key,Qnil,
	    Qnil,Qnil,Qnil);
    QControl_plus_tl_at = STATIC_SYMBOL("Control+~@",AB_package);
    define_key_symbol_1(QControl_plus_tl_at,FIX((SI_Long)0L),
	    QControl_plus_tl_at,CHR('\000'),FIX((SI_Long)0L),Qnil,Qnil);
    QControl_plus_a = STATIC_SYMBOL("Control+a",AB_package);
    define_key_symbol_1(QControl_plus_a,FIX((SI_Long)1L),QControl_plus_a,
	    CHR('\001'),FIX((SI_Long)1L),Qnil,Qnil);
    QControl_plus_b = STATIC_SYMBOL("Control+b",AB_package);
    define_key_symbol_1(QControl_plus_b,FIX((SI_Long)2L),QControl_plus_b,
	    CHR('\002'),FIX((SI_Long)2L),Qnil,Qnil);
    QControl_plus_c = STATIC_SYMBOL("Control+c",AB_package);
    define_key_symbol_1(QControl_plus_c,FIX((SI_Long)3L),QControl_plus_c,
	    CHR('\003'),FIX((SI_Long)3L),Qnil,Qnil);
    QControl_plus_d = STATIC_SYMBOL("Control+d",AB_package);
    define_key_symbol_1(QControl_plus_d,FIX((SI_Long)4L),QControl_plus_d,
	    CHR('\004'),FIX((SI_Long)4L),Qnil,Qnil);
    QControl_plus_e = STATIC_SYMBOL("Control+e",AB_package);
    define_key_symbol_1(QControl_plus_e,FIX((SI_Long)5L),QControl_plus_e,
	    CHR('\005'),FIX((SI_Long)5L),Qnil,Qnil);
    QControl_plus_f = STATIC_SYMBOL("Control+f",AB_package);
    define_key_symbol_1(QControl_plus_f,FIX((SI_Long)6L),QControl_plus_f,
	    CHR('\006'),FIX((SI_Long)6L),Qnil,Qnil);
    QControl_plus_g = STATIC_SYMBOL("Control+g",AB_package);
    define_key_symbol_1(QControl_plus_g,FIX((SI_Long)7L),QControl_plus_g,
	    CHR('\007'),FIX((SI_Long)7L),Qnil,Qnil);
    QControl_plus_h = STATIC_SYMBOL("Control+h",AB_package);
    define_key_symbol_1(QControl_plus_h,FIX((SI_Long)8L),QControl_plus_h,
	    CHR('\b'),FIX((SI_Long)8L),Qnil,Qnil);
    QControl_plus_i = STATIC_SYMBOL("Control+i",AB_package);
    define_key_symbol_1(QControl_plus_i,FIX((SI_Long)9L),QControl_plus_i,
	    CHR('\t'),FIX((SI_Long)9L),Qnil,Qnil);
    QControl_plus_j = STATIC_SYMBOL("Control+j",AB_package);
    define_key_symbol_1(QControl_plus_j,FIX((SI_Long)10L),QControl_plus_j,
	    CHR('\n'),FIX((SI_Long)10L),Qnil,Qnil);
    QControl_plus_k = STATIC_SYMBOL("Control+k",AB_package);
    define_key_symbol_1(QControl_plus_k,FIX((SI_Long)11L),QControl_plus_k,
	    CHR('\013'),FIX((SI_Long)11L),Qnil,Qnil);
    QControl_plus_l = STATIC_SYMBOL("Control+l",AB_package);
    define_key_symbol_1(QControl_plus_l,FIX((SI_Long)12L),QControl_plus_l,
	    CHR('\f'),FIX((SI_Long)12L),Qnil,Qnil);
    QControl_plus_m = STATIC_SYMBOL("Control+m",AB_package);
    define_key_symbol_1(QControl_plus_m,FIX((SI_Long)13L),QControl_plus_m,
	    CHR('\r'),FIX((SI_Long)13L),Qnil,Qnil);
    QControl_plus_n = STATIC_SYMBOL("Control+n",AB_package);
    define_key_symbol_1(QControl_plus_n,FIX((SI_Long)14L),QControl_plus_n,
	    CHR('\016'),FIX((SI_Long)14L),Qnil,Qnil);
    QControl_plus_o = STATIC_SYMBOL("Control+o",AB_package);
    define_key_symbol_1(QControl_plus_o,FIX((SI_Long)15L),QControl_plus_o,
	    CHR('\017'),FIX((SI_Long)15L),Qnil,Qnil);
    QControl_plus_p = STATIC_SYMBOL("Control+p",AB_package);
    define_key_symbol_1(QControl_plus_p,FIX((SI_Long)16L),QControl_plus_p,
	    CHR('\020'),FIX((SI_Long)16L),Qnil,Qnil);
    QControl_plus_q = STATIC_SYMBOL("Control+q",AB_package);
    define_key_symbol_1(QControl_plus_q,FIX((SI_Long)17L),QControl_plus_q,
	    CHR('\021'),FIX((SI_Long)17L),Qnil,Qnil);
    QControl_plus_r = STATIC_SYMBOL("Control+r",AB_package);
    define_key_symbol_1(QControl_plus_r,FIX((SI_Long)18L),QControl_plus_r,
	    CHR('\022'),FIX((SI_Long)18L),Qnil,Qnil);
    QControl_plus_s = STATIC_SYMBOL("Control+s",AB_package);
    define_key_symbol_1(QControl_plus_s,FIX((SI_Long)19L),QControl_plus_s,
	    CHR('\023'),FIX((SI_Long)19L),Qnil,Qnil);
    QControl_plus_t = STATIC_SYMBOL("Control+t",AB_package);
    define_key_symbol_1(QControl_plus_t,FIX((SI_Long)20L),QControl_plus_t,
	    CHR('\024'),FIX((SI_Long)20L),Qnil,Qnil);
    QControl_plus_u = STATIC_SYMBOL("Control+u",AB_package);
    define_key_symbol_1(QControl_plus_u,FIX((SI_Long)21L),QControl_plus_u,
	    CHR('\025'),FIX((SI_Long)21L),Qnil,Qnil);
    QControl_plus_v = STATIC_SYMBOL("Control+v",AB_package);
    define_key_symbol_1(QControl_plus_v,FIX((SI_Long)22L),QControl_plus_v,
	    CHR('\026'),FIX((SI_Long)22L),Qnil,Qnil);
    QControl_plus_w = STATIC_SYMBOL("Control+w",AB_package);
    define_key_symbol_1(QControl_plus_w,FIX((SI_Long)23L),QControl_plus_w,
	    CHR('\027'),FIX((SI_Long)23L),Qnil,Qnil);
    QControl_plus_x = STATIC_SYMBOL("Control+x",AB_package);
    define_key_symbol_1(QControl_plus_x,FIX((SI_Long)24L),QControl_plus_x,
	    CHR('\030'),FIX((SI_Long)24L),Qnil,Qnil);
    QControl_plus_y = STATIC_SYMBOL("Control+y",AB_package);
    define_key_symbol_1(QControl_plus_y,FIX((SI_Long)25L),QControl_plus_y,
	    CHR('\031'),FIX((SI_Long)25L),Qnil,Qnil);
    QControl_plus_z = STATIC_SYMBOL("Control+z",AB_package);
    define_key_symbol_1(QControl_plus_z,FIX((SI_Long)26L),QControl_plus_z,
	    CHR('\032'),FIX((SI_Long)26L),Qnil,Qnil);
    QControl_plus_obt = STATIC_SYMBOL("Control+[",AB_package);
    define_key_symbol_1(QControl_plus_obt,FIX((SI_Long)27L),
	    QControl_plus_obt,CHR('\033'),FIX((SI_Long)27L),Qnil,Qnil);
    QControl_plus_tl_bs = STATIC_SYMBOL("Control+~\\",AB_package);
    define_key_symbol_1(QControl_plus_tl_bs,FIX((SI_Long)28L),
	    QControl_plus_tl_bs,CHR('\034'),FIX((SI_Long)28L),Qnil,Qnil);
    QControl_plus_cbt = STATIC_SYMBOL("Control+]",AB_package);
    define_key_symbol_1(QControl_plus_cbt,FIX((SI_Long)29L),
	    QControl_plus_cbt,CHR('\035'),FIX((SI_Long)29L),Qnil,Qnil);
    QControl_plus_ct = STATIC_SYMBOL("Control+^",AB_package);
    define_key_symbol_1(QControl_plus_ct,FIX((SI_Long)30L),
	    QControl_plus_ct,CHR('\036'),FIX((SI_Long)30L),Qnil,Qnil);
    QControl_plus_ = STATIC_SYMBOL("Control+_",AB_package);
    define_key_symbol_1(QControl_plus_,FIX((SI_Long)31L),QControl_plus_,
	    CHR('\037'),FIX((SI_Long)31L),Qnil,Qnil);
    Qf1 = STATIC_SYMBOL("F1",AB_package);
    define_key_symbol_1(Qf1,FIX((SI_Long)405L),Qf1,Qnil,Qnil,Qt,Qnil);
    Qf2 = STATIC_SYMBOL("F2",AB_package);
    define_key_symbol_1(Qf2,FIX((SI_Long)406L),Qf2,Qnil,Qnil,Qt,Qnil);
    Qf3 = STATIC_SYMBOL("F3",AB_package);
    define_key_symbol_1(Qf3,FIX((SI_Long)407L),Qf3,Qnil,Qnil,Qt,Qnil);
    Qf4 = STATIC_SYMBOL("F4",AB_package);
    define_key_symbol_1(Qf4,FIX((SI_Long)408L),Qf4,Qnil,Qnil,Qt,Qnil);
    Qf5 = STATIC_SYMBOL("F5",AB_package);
    define_key_symbol_1(Qf5,FIX((SI_Long)420L),Qf5,Qnil,Qnil,Qt,Qnil);
    Qf6 = STATIC_SYMBOL("F6",AB_package);
    define_key_symbol_1(Qf6,FIX((SI_Long)421L),Qf6,Qnil,Qnil,Qt,Qnil);
    Qf7 = STATIC_SYMBOL("F7",AB_package);
    define_key_symbol_1(Qf7,FIX((SI_Long)422L),Qf7,Qnil,Qnil,Qt,Qnil);
    Qf8 = STATIC_SYMBOL("F8",AB_package);
    define_key_symbol_1(Qf8,FIX((SI_Long)423L),Qf8,Qnil,Qnil,Qt,Qnil);
    Qf9 = STATIC_SYMBOL("F9",AB_package);
    define_key_symbol_1(Qf9,FIX((SI_Long)424L),Qf9,Qnil,Qnil,Qt,Qnil);
    Qf10 = STATIC_SYMBOL("F10",AB_package);
    define_key_symbol_1(Qf10,FIX((SI_Long)425L),Qf10,Qnil,Qnil,Qt,Qnil);
    Qf11 = STATIC_SYMBOL("F11",AB_package);
    define_key_symbol_1(Qf11,FIX((SI_Long)426L),Qf11,Qnil,Qnil,Qt,Qnil);
    Qf12 = STATIC_SYMBOL("F12",AB_package);
    define_key_symbol_1(Qf12,FIX((SI_Long)427L),Qf12,Qnil,Qnil,Qt,Qnil);
    Qf13 = STATIC_SYMBOL("F13",AB_package);
    define_key_symbol_1(Qf13,FIX((SI_Long)428L),Qf13,Qnil,Qnil,Qnil,Qnil);
    Qf14 = STATIC_SYMBOL("F14",AB_package);
    define_key_symbol_1(Qf14,FIX((SI_Long)429L),Qf14,Qnil,Qnil,Qnil,Qnil);
    Qf15 = STATIC_SYMBOL("F15",AB_package);
    define_key_symbol_1(Qf15,FIX((SI_Long)430L),Qf15,Qnil,Qnil,Qnil,Qnil);
    Qf16 = STATIC_SYMBOL("F16",AB_package);
    define_key_symbol_1(Qf16,FIX((SI_Long)431L),Qf16,Qnil,Qnil,Qnil,Qnil);
    Qf17 = STATIC_SYMBOL("F17",AB_package);
    define_key_symbol_1(Qf17,FIX((SI_Long)432L),Qf17,Qnil,Qnil,Qnil,Qnil);
    Qf18 = STATIC_SYMBOL("F18",AB_package);
    define_key_symbol_1(Qf18,FIX((SI_Long)433L),Qf18,Qnil,Qnil,Qnil,Qnil);
    Qf19 = STATIC_SYMBOL("F19",AB_package);
    define_key_symbol_1(Qf19,FIX((SI_Long)434L),Qf19,Qnil,Qnil,Qnil,Qnil);
    Qf20 = STATIC_SYMBOL("F20",AB_package);
    define_key_symbol_1(Qf20,FIX((SI_Long)435L),Qf20,Qnil,Qnil,Qnil,Qnil);
    Qf21 = STATIC_SYMBOL("F21",AB_package);
    define_key_symbol_1(Qf21,FIX((SI_Long)436L),Qf21,Qnil,Qnil,Qnil,Qnil);
    Qf22 = STATIC_SYMBOL("F22",AB_package);
    define_key_symbol_1(Qf22,FIX((SI_Long)437L),Qf22,Qnil,Qnil,Qnil,Qnil);
    Qf23 = STATIC_SYMBOL("F23",AB_package);
    define_key_symbol_1(Qf23,FIX((SI_Long)438L),Qf23,Qnil,Qnil,Qnil,Qnil);
    Qf24 = STATIC_SYMBOL("F24",AB_package);
    define_key_symbol_1(Qf24,FIX((SI_Long)439L),Qf24,Qnil,Qnil,Qnil,Qnil);
    Qf25 = STATIC_SYMBOL("F25",AB_package);
    define_key_symbol_1(Qf25,FIX((SI_Long)440L),Qf25,Qnil,Qnil,Qnil,Qnil);
    Qf26 = STATIC_SYMBOL("F26",AB_package);
    define_key_symbol_1(Qf26,FIX((SI_Long)441L),Qf26,Qnil,Qnil,Qnil,Qnil);
    Qf27 = STATIC_SYMBOL("F27",AB_package);
    define_key_symbol_1(Qf27,FIX((SI_Long)442L),Qf27,Qnil,Qnil,Qnil,Qnil);
    Qf28 = STATIC_SYMBOL("F28",AB_package);
    define_key_symbol_1(Qf28,FIX((SI_Long)443L),Qf28,Qnil,Qnil,Qnil,Qnil);
    Qf29 = STATIC_SYMBOL("F29",AB_package);
    define_key_symbol_1(Qf29,FIX((SI_Long)444L),Qf29,Qnil,Qnil,Qnil,Qnil);
    Qf30 = STATIC_SYMBOL("F30",AB_package);
    define_key_symbol_1(Qf30,FIX((SI_Long)445L),Qf30,Qnil,Qnil,Qnil,Qnil);
    Qf31 = STATIC_SYMBOL("F31",AB_package);
    define_key_symbol_1(Qf31,FIX((SI_Long)446L),Qf31,Qnil,Qnil,Qnil,Qnil);
    Qf32 = STATIC_SYMBOL("F32",AB_package);
    define_key_symbol_1(Qf32,FIX((SI_Long)447L),Qf32,Qnil,Qnil,Qnil,Qnil);
    Qf33 = STATIC_SYMBOL("F33",AB_package);
    define_key_symbol_1(Qf33,FIX((SI_Long)448L),Qf33,Qnil,Qnil,Qnil,Qnil);
    Qf34 = STATIC_SYMBOL("F34",AB_package);
    define_key_symbol_1(Qf34,FIX((SI_Long)449L),Qf34,Qnil,Qnil,Qnil,Qnil);
    Qf35 = STATIC_SYMBOL("F35",AB_package);
    define_key_symbol_1(Qf35,FIX((SI_Long)450L),Qf35,Qnil,Qnil,Qnil,Qnil);
    Qbackspace = STATIC_SYMBOL("BACKSPACE",AB_package);
    define_key_symbol_1(Qbackspace,FIX((SI_Long)278L),Qbackspace,CHR('\b'),
	    FIX((SI_Long)8L),Qt,Qnil);
    Qtab = STATIC_SYMBOL("TAB",AB_package);
    define_key_symbol_1(Qtab,FIX((SI_Long)279L),Qtab,CHR('\t'),
	    FIX((SI_Long)9L),Qt,Qnil);
    Qlinefeed = STATIC_SYMBOL("LINEFEED",AB_package);
    define_key_symbol_1(Qlinefeed,FIX((SI_Long)280L),Qlinefeed,CHR('\n'),
	    FIX((SI_Long)10L),Qt,Qnil);
    define_key_symbol_1(Qreturn,FIX((SI_Long)281L),Qreturn,CHR('\r'),
	    FIX((SI_Long)13L),Qt,Qnil);
    Qescape = STATIC_SYMBOL("ESCAPE",AB_package);
    define_key_symbol_1(Qescape,FIX((SI_Long)282L),Qescape,CHR('\033'),
	    FIX((SI_Long)27L),Qt,Qnil);
    Q0 = STATIC_SYMBOL("0",AB_package);
    define_key_symbol_1(Q0,FIX((SI_Long)48L),Q0,CHR('0'),FIX((SI_Long)48L),
	    Qt,Qnil);
    Q1 = STATIC_SYMBOL("1",AB_package);
    define_key_symbol_1(Q1,FIX((SI_Long)49L),Q1,CHR('1'),FIX((SI_Long)49L),
	    Qt,Qnil);
    Q2 = STATIC_SYMBOL("2",AB_package);
    define_key_symbol_1(Q2,FIX((SI_Long)50L),Q2,CHR('2'),FIX((SI_Long)50L),
	    Qt,Qnil);
    Q3 = STATIC_SYMBOL("3",AB_package);
    define_key_symbol_1(Q3,FIX((SI_Long)51L),Q3,CHR('3'),FIX((SI_Long)51L),
	    Qt,Qnil);
    Q4 = STATIC_SYMBOL("4",AB_package);
    define_key_symbol_1(Q4,FIX((SI_Long)52L),Q4,CHR('4'),FIX((SI_Long)52L),
	    Qt,Qnil);
    Q5 = STATIC_SYMBOL("5",AB_package);
    define_key_symbol_1(Q5,FIX((SI_Long)53L),Q5,CHR('5'),FIX((SI_Long)53L),
	    Qt,Qnil);
    Q6 = STATIC_SYMBOL("6",AB_package);
    define_key_symbol_1(Q6,FIX((SI_Long)54L),Q6,CHR('6'),FIX((SI_Long)54L),
	    Qt,Qnil);
    Q7 = STATIC_SYMBOL("7",AB_package);
    define_key_symbol_1(Q7,FIX((SI_Long)55L),Q7,CHR('7'),FIX((SI_Long)55L),
	    Qt,Qnil);
    Q8 = STATIC_SYMBOL("8",AB_package);
    define_key_symbol_1(Q8,FIX((SI_Long)56L),Q8,CHR('8'),FIX((SI_Long)56L),
	    Qt,Qnil);
    Q9 = STATIC_SYMBOL("9",AB_package);
    define_key_symbol_1(Q9,FIX((SI_Long)57L),Q9,CHR('9'),FIX((SI_Long)57L),
	    Qt,Qnil);
    Qcol = STATIC_SYMBOL(":",AB_package);
    define_key_symbol_1(Qcol,FIX((SI_Long)58L),Qcol,CHR(':'),
	    FIX((SI_Long)58L),Qt,Qnil);
    Qsc = STATIC_SYMBOL(";",AB_package);
    define_key_symbol_1(Qsc,FIX((SI_Long)59L),Qsc,CHR(';'),
	    FIX((SI_Long)59L),Qt,Qnil);
    define_key_symbol_1(Qnum_lt,FIX((SI_Long)60L),Qnum_lt,CHR('<'),
	    FIX((SI_Long)60L),Qt,Qnil);
    define_key_symbol_1(Qnum_eq,FIX((SI_Long)61L),Qnum_eq,CHR('='),
	    FIX((SI_Long)61L),Qt,Qnil);
    define_key_symbol_1(Qnum_gt,FIX((SI_Long)62L),Qnum_gt,CHR('>'),
	    FIX((SI_Long)62L),Qt,Qnil);
    Qqm = STATIC_SYMBOL("\?",AB_package);
    define_key_symbol_1(Qqm,FIX((SI_Long)63L),Qqm,CHR('\?'),
	    FIX((SI_Long)63L),Qt,Qnil);
    Qtl_at = STATIC_SYMBOL("~@",AB_package);
    define_key_symbol_1(Qtl_at,FIX((SI_Long)64L),Qtl_at,CHR('@'),
	    FIX((SI_Long)64L),Qnil,Qnil);
    Qa = STATIC_SYMBOL("A",AB_package);
    define_key_symbol_1(Qa,FIX((SI_Long)65L),Qa,CHR('A'),FIX((SI_Long)65L),
	    Qt,Qnil);
    Qb = STATIC_SYMBOL("B",AB_package);
    define_key_symbol_1(Qb,FIX((SI_Long)66L),Qb,CHR('B'),FIX((SI_Long)66L),
	    Qt,Qnil);
    Qc = STATIC_SYMBOL("C",AB_package);
    define_key_symbol_1(Qc,FIX((SI_Long)67L),Qc,CHR('C'),FIX((SI_Long)67L),
	    Qt,Qnil);
    Qd = STATIC_SYMBOL("D",AB_package);
    define_key_symbol_1(Qd,FIX((SI_Long)68L),Qd,CHR('D'),FIX((SI_Long)68L),
	    Qt,Qnil);
    Qe = STATIC_SYMBOL("E",AB_package);
    define_key_symbol_1(Qe,FIX((SI_Long)69L),Qe,CHR('E'),FIX((SI_Long)69L),
	    Qt,Qnil);
    Qf = STATIC_SYMBOL("F",AB_package);
    define_key_symbol_1(Qf,FIX((SI_Long)70L),Qf,CHR('F'),FIX((SI_Long)70L),
	    Qt,Qnil);
    Qg = STATIC_SYMBOL("G",AB_package);
    define_key_symbol_1(Qg,FIX((SI_Long)71L),Qg,CHR('G'),FIX((SI_Long)71L),
	    Qt,Qnil);
    Qh = STATIC_SYMBOL("H",AB_package);
    define_key_symbol_1(Qh,FIX((SI_Long)72L),Qh,CHR('H'),FIX((SI_Long)72L),
	    Qt,Qnil);
    Qi = STATIC_SYMBOL("I",AB_package);
    define_key_symbol_1(Qi,FIX((SI_Long)73L),Qi,CHR('I'),FIX((SI_Long)73L),
	    Qt,Qnil);
    Qj = STATIC_SYMBOL("J",AB_package);
    define_key_symbol_1(Qj,FIX((SI_Long)74L),Qj,CHR('J'),FIX((SI_Long)74L),
	    Qt,Qnil);
    Qk = STATIC_SYMBOL("K",AB_package);
    define_key_symbol_1(Qk,FIX((SI_Long)75L),Qk,CHR('K'),FIX((SI_Long)75L),
	    Qt,Qnil);
    Ql = STATIC_SYMBOL("L",AB_package);
    define_key_symbol_1(Ql,FIX((SI_Long)76L),Ql,CHR('L'),FIX((SI_Long)76L),
	    Qt,Qnil);
    Qm = STATIC_SYMBOL("M",AB_package);
    define_key_symbol_1(Qm,FIX((SI_Long)77L),Qm,CHR('M'),FIX((SI_Long)77L),
	    Qt,Qnil);
    Qn = STATIC_SYMBOL("N",AB_package);
    define_key_symbol_1(Qn,FIX((SI_Long)78L),Qn,CHR('N'),FIX((SI_Long)78L),
	    Qt,Qnil);
    Qo = STATIC_SYMBOL("O",AB_package);
    define_key_symbol_1(Qo,FIX((SI_Long)79L),Qo,CHR('O'),FIX((SI_Long)79L),
	    Qt,Qnil);
    Qp = STATIC_SYMBOL("P",AB_package);
    define_key_symbol_1(Qp,FIX((SI_Long)80L),Qp,CHR('P'),FIX((SI_Long)80L),
	    Qt,Qnil);
    Qq = STATIC_SYMBOL("Q",AB_package);
    define_key_symbol_1(Qq,FIX((SI_Long)81L),Qq,CHR('Q'),FIX((SI_Long)81L),
	    Qt,Qnil);
    Qr = STATIC_SYMBOL("R",AB_package);
    define_key_symbol_1(Qr,FIX((SI_Long)82L),Qr,CHR('R'),FIX((SI_Long)82L),
	    Qt,Qnil);
    Qs = STATIC_SYMBOL("S",AB_package);
    define_key_symbol_1(Qs,FIX((SI_Long)83L),Qs,CHR('S'),FIX((SI_Long)83L),
	    Qt,Qnil);
    define_key_symbol_1(Qt,FIX((SI_Long)84L),Qt,CHR('T'),FIX((SI_Long)84L),
	    Qt,Qnil);
    Qu = STATIC_SYMBOL("U",AB_package);
    define_key_symbol_1(Qu,FIX((SI_Long)85L),Qu,CHR('U'),FIX((SI_Long)85L),
	    Qt,Qnil);
    Qv = STATIC_SYMBOL("V",AB_package);
    define_key_symbol_1(Qv,FIX((SI_Long)86L),Qv,CHR('V'),FIX((SI_Long)86L),
	    Qt,Qnil);
    Qw = STATIC_SYMBOL("W",AB_package);
    define_key_symbol_1(Qw,FIX((SI_Long)87L),Qw,CHR('W'),FIX((SI_Long)87L),
	    Qt,Qnil);
    Qx = STATIC_SYMBOL("X",AB_package);
    define_key_symbol_1(Qx,FIX((SI_Long)88L),Qx,CHR('X'),FIX((SI_Long)88L),
	    Qt,Qnil);
    Qy = STATIC_SYMBOL("Y",AB_package);
    define_key_symbol_1(Qy,FIX((SI_Long)89L),Qy,CHR('Y'),FIX((SI_Long)89L),
	    Qt,Qnil);
    Qz = STATIC_SYMBOL("Z",AB_package);
    define_key_symbol_1(Qz,FIX((SI_Long)90L),Qz,CHR('Z'),FIX((SI_Long)90L),
	    Qt,Qnil);
    Qobt = STATIC_SYMBOL("[",AB_package);
    define_key_symbol_1(Qobt,FIX((SI_Long)91L),Qobt,CHR('['),
	    FIX((SI_Long)91L),Qt,Qnil);
    Qtl_bs = STATIC_SYMBOL("~\\",AB_package);
    define_key_symbol_1(Qtl_bs,FIX((SI_Long)92L),Qtl_bs,CHR('\\'),
	    FIX((SI_Long)92L),Qnil,Qnil);
    Qcbt = STATIC_SYMBOL("]",AB_package);
    define_key_symbol_1(Qcbt,FIX((SI_Long)93L),Qcbt,CHR(']'),
	    FIX((SI_Long)93L),Qt,Qnil);
    Qct = STATIC_SYMBOL("^",AB_package);
    define_key_symbol_1(Qct,FIX((SI_Long)94L),Qct,CHR('^'),
	    FIX((SI_Long)94L),Qt,Qnil);
    Q_ = STATIC_SYMBOL("_",AB_package);
    define_key_symbol_1(Q_,FIX((SI_Long)95L),Q_,CHR('_'),FIX((SI_Long)95L),
	    Qt,Qnil);
    Qbq = STATIC_SYMBOL("`",AB_package);
    define_key_symbol_1(Qbq,FIX((SI_Long)96L),Qbq,CHR('`'),
	    FIX((SI_Long)96L),Qt,Qnil);
    QA = STATIC_SYMBOL("a",AB_package);
    define_key_symbol_1(QA,FIX((SI_Long)97L),QA,CHR('a'),FIX((SI_Long)97L),
	    Qnil,Qnil);
    QB = STATIC_SYMBOL("b",AB_package);
    define_key_symbol_1(QB,FIX((SI_Long)98L),QB,CHR('b'),FIX((SI_Long)98L),
	    Qnil,Qnil);
    QC = STATIC_SYMBOL("c",AB_package);
    define_key_symbol_1(QC,FIX((SI_Long)99L),QC,CHR('c'),FIX((SI_Long)99L),
	    Qnil,Qnil);
    QD = STATIC_SYMBOL("d",AB_package);
    define_key_symbol_1(QD,FIX((SI_Long)100L),QD,CHR('d'),
	    FIX((SI_Long)100L),Qnil,Qnil);
    QE = STATIC_SYMBOL("e",AB_package);
    define_key_symbol_1(QE,FIX((SI_Long)101L),QE,CHR('e'),
	    FIX((SI_Long)101L),Qnil,Qnil);
    QF = STATIC_SYMBOL("f",AB_package);
    define_key_symbol_1(QF,FIX((SI_Long)102L),QF,CHR('f'),
	    FIX((SI_Long)102L),Qnil,Qnil);
    QG = STATIC_SYMBOL("g",AB_package);
    define_key_symbol_1(QG,FIX((SI_Long)103L),QG,CHR('g'),
	    FIX((SI_Long)103L),Qnil,Qnil);
    QH = STATIC_SYMBOL("h",AB_package);
    define_key_symbol_1(QH,FIX((SI_Long)104L),QH,CHR('h'),
	    FIX((SI_Long)104L),Qnil,Qnil);
    QI = STATIC_SYMBOL("i",AB_package);
    define_key_symbol_1(QI,FIX((SI_Long)105L),QI,CHR('i'),
	    FIX((SI_Long)105L),Qnil,Qnil);
    QJ = STATIC_SYMBOL("j",AB_package);
    define_key_symbol_1(QJ,FIX((SI_Long)106L),QJ,CHR('j'),
	    FIX((SI_Long)106L),Qnil,Qnil);
    QK = STATIC_SYMBOL("k",AB_package);
    define_key_symbol_1(QK,FIX((SI_Long)107L),QK,CHR('k'),
	    FIX((SI_Long)107L),Qnil,Qnil);
    QL = STATIC_SYMBOL("l",AB_package);
    define_key_symbol_1(QL,FIX((SI_Long)108L),QL,CHR('l'),
	    FIX((SI_Long)108L),Qnil,Qnil);
    QM = STATIC_SYMBOL("m",AB_package);
    define_key_symbol_1(QM,FIX((SI_Long)109L),QM,CHR('m'),
	    FIX((SI_Long)109L),Qnil,Qnil);
    QN = STATIC_SYMBOL("n",AB_package);
    define_key_symbol_1(QN,FIX((SI_Long)110L),QN,CHR('n'),
	    FIX((SI_Long)110L),Qnil,Qnil);
    QO = STATIC_SYMBOL("o",AB_package);
    define_key_symbol_1(QO,FIX((SI_Long)111L),QO,CHR('o'),
	    FIX((SI_Long)111L),Qnil,Qnil);
    QP = STATIC_SYMBOL("p",AB_package);
    define_key_symbol_1(QP,FIX((SI_Long)112L),QP,CHR('p'),
	    FIX((SI_Long)112L),Qnil,Qnil);
    QQ = STATIC_SYMBOL("q",AB_package);
    define_key_symbol_1(QQ,FIX((SI_Long)113L),QQ,CHR('q'),
	    FIX((SI_Long)113L),Qnil,Qnil);
    QR = STATIC_SYMBOL("r",AB_package);
    define_key_symbol_1(QR,FIX((SI_Long)114L),QR,CHR('r'),
	    FIX((SI_Long)114L),Qnil,Qnil);
    QS = STATIC_SYMBOL("s",AB_package);
    define_key_symbol_1(QS,FIX((SI_Long)115L),QS,CHR('s'),
	    FIX((SI_Long)115L),Qnil,Qnil);
    QT = STATIC_SYMBOL("t",AB_package);
    define_key_symbol_1(QT,FIX((SI_Long)116L),QT,CHR('t'),
	    FIX((SI_Long)116L),Qnil,Qnil);
    QU = STATIC_SYMBOL("u",AB_package);
    define_key_symbol_1(QU,FIX((SI_Long)117L),QU,CHR('u'),
	    FIX((SI_Long)117L),Qnil,Qnil);
    QV = STATIC_SYMBOL("v",AB_package);
    define_key_symbol_1(QV,FIX((SI_Long)118L),QV,CHR('v'),
	    FIX((SI_Long)118L),Qnil,Qnil);
    QW = STATIC_SYMBOL("w",AB_package);
    define_key_symbol_1(QW,FIX((SI_Long)119L),QW,CHR('w'),
	    FIX((SI_Long)119L),Qnil,Qnil);
    QX = STATIC_SYMBOL("x",AB_package);
    define_key_symbol_1(QX,FIX((SI_Long)120L),QX,CHR('x'),
	    FIX((SI_Long)120L),Qnil,Qnil);
    QY = STATIC_SYMBOL("y",AB_package);
    define_key_symbol_1(QY,FIX((SI_Long)121L),QY,CHR('y'),
	    FIX((SI_Long)121L),Qnil,Qnil);
    QZ = STATIC_SYMBOL("z",AB_package);
    define_key_symbol_1(QZ,FIX((SI_Long)122L),QZ,CHR('z'),
	    FIX((SI_Long)122L),Qnil,Qnil);
    Qob = STATIC_SYMBOL("{",AB_package);
    define_key_symbol_1(Qob,FIX((SI_Long)123L),Qob,CHR('{'),
	    FIX((SI_Long)123L),Qt,Qnil);
    Qab_or_1 = STATIC_SYMBOL("|",AB_package);
    define_key_symbol_1(Qab_or_1,FIX((SI_Long)124L),Qab_or_1,CHR('|'),
	    FIX((SI_Long)124L),Qt,Qnil);
    Qcb = STATIC_SYMBOL("}",AB_package);
    define_key_symbol_1(Qcb,FIX((SI_Long)125L),Qcb,CHR('}'),
	    FIX((SI_Long)125L),Qt,Qnil);
    Qtl_tl = STATIC_SYMBOL("~~",AB_package);
    define_key_symbol_1(Qtl_tl,FIX((SI_Long)126L),Qtl_tl,CHR('~'),
	    FIX((SI_Long)126L),Qnil,Qnil);
    define_key_symbol_1(Qspace,FIX((SI_Long)32L),Qspace,CHR(' '),
	    FIX((SI_Long)32L),Qt,Qnil);
    Qex = STATIC_SYMBOL("!",AB_package);
    define_key_symbol_1(Qex,FIX((SI_Long)33L),Qex,CHR('!'),
	    FIX((SI_Long)33L),Qt,Qnil);
    Qdq = STATIC_SYMBOL("\"",AB_package);
    define_key_symbol_1(Qdq,FIX((SI_Long)34L),Qdq,CHR('\"'),
	    FIX((SI_Long)34L),Qt,Qnil);
    Qno = STATIC_SYMBOL("#",AB_package);
    define_key_symbol_1(Qno,FIX((SI_Long)35L),Qno,CHR('#'),
	    FIX((SI_Long)35L),Qt,Qnil);
    Qdol = STATIC_SYMBOL("$",AB_package);
    define_key_symbol_1(Qdol,FIX((SI_Long)36L),Qdol,CHR('$'),
	    FIX((SI_Long)36L),Qt,Qnil);
    Qpct = STATIC_SYMBOL("%",AB_package);
    define_key_symbol_1(Qpct,FIX((SI_Long)37L),Qpct,CHR('%'),
	    FIX((SI_Long)37L),Qt,Qnil);
    Qab_and = STATIC_SYMBOL("&",AB_package);
    define_key_symbol_1(Qab_and,FIX((SI_Long)38L),Qab_and,CHR('&'),
	    FIX((SI_Long)38L),Qt,Qnil);
    Qqu = STATIC_SYMBOL("\'",AB_package);
    define_key_symbol_1(Qqu,FIX((SI_Long)39L),Qqu,CHR('\''),
	    FIX((SI_Long)39L),Qt,Qnil);
    Qop = STATIC_SYMBOL("(",AB_package);
    define_key_symbol_1(Qop,FIX((SI_Long)40L),Qop,CHR('('),
	    FIX((SI_Long)40L),Qt,Qnil);
    Qcp = STATIC_SYMBOL(")",AB_package);
    define_key_symbol_1(Qcp,FIX((SI_Long)41L),Qcp,CHR(')'),
	    FIX((SI_Long)41L),Qt,Qnil);
    define_key_symbol_1(Qstar,FIX((SI_Long)42L),Qstar,CHR('*'),
	    FIX((SI_Long)42L),Qt,Qnil);
    define_key_symbol_1(Qplus,FIX((SI_Long)43L),Qplus,CHR('+'),
	    FIX((SI_Long)43L),Qt,Qnil);
    Qcm = STATIC_SYMBOL(",",AB_package);
    define_key_symbol_1(Qcm,FIX((SI_Long)44L),Qcm,CHR(','),
	    FIX((SI_Long)44L),Qt,Qnil);
    define_key_symbol_1(Qminus,FIX((SI_Long)45L),Qminus,CHR('-'),
	    FIX((SI_Long)45L),Qt,Qnil);
    Qdot = STATIC_SYMBOL(".",AB_package);
    define_key_symbol_1(Qdot,FIX((SI_Long)46L),Qdot,CHR('.'),
	    FIX((SI_Long)46L),Qt,Qnil);
    define_key_symbol_1(Qslash,FIX((SI_Long)47L),Qslash,CHR('/'),
	    FIX((SI_Long)47L),Qt,Qnil);
    QNOBREAKSPACE = STATIC_SYMBOL("nobreakspace",AB_package);
    define_key_symbol_1(QNOBREAKSPACE,FIX((SI_Long)160L),QNOBREAKSPACE,
	    Qnil,Qnil,Qnil,Qnil);
    QEXCLAMDOWN = STATIC_SYMBOL("exclamdown",AB_package);
    define_key_symbol_1(QEXCLAMDOWN,FIX((SI_Long)161L),QEXCLAMDOWN,Qnil,
	    Qnil,Qnil,Qnil);
    QCENT = STATIC_SYMBOL("cent",AB_package);
    define_key_symbol_1(QCENT,FIX((SI_Long)162L),QCENT,Qnil,Qnil,Qnil,Qnil);
    QSTERLING = STATIC_SYMBOL("sterling",AB_package);
    define_key_symbol_1(QSTERLING,FIX((SI_Long)163L),QSTERLING,Qnil,Qnil,
	    Qnil,Qnil);
    QCURRENCY = STATIC_SYMBOL("currency",AB_package);
    define_key_symbol_1(QCURRENCY,FIX((SI_Long)164L),QCURRENCY,Qnil,Qnil,
	    Qnil,Qnil);
    QYEN = STATIC_SYMBOL("yen",AB_package);
    define_key_symbol_1(QYEN,FIX((SI_Long)165L),QYEN,Qnil,Qnil,Qnil,Qnil);
    QBROKENBAR = STATIC_SYMBOL("brokenbar",AB_package);
    define_key_symbol_1(QBROKENBAR,FIX((SI_Long)166L),QBROKENBAR,Qnil,Qnil,
	    Qnil,Qnil);
    QSECTION = STATIC_SYMBOL("section",AB_package);
    define_key_symbol_1(QSECTION,FIX((SI_Long)167L),QSECTION,Qnil,Qnil,
	    Qnil,Qnil);
    QDIAERESIS = STATIC_SYMBOL("diaeresis",AB_package);
    define_key_symbol_1(QDIAERESIS,FIX((SI_Long)168L),QDIAERESIS,Qnil,Qnil,
	    Qnil,Qnil);
    QCOPYRIGHT = STATIC_SYMBOL("copyright",AB_package);
    define_key_symbol_1(QCOPYRIGHT,FIX((SI_Long)169L),QCOPYRIGHT,Qnil,Qnil,
	    Qnil,Qnil);
    QORDFEMININE = STATIC_SYMBOL("ordfeminine",AB_package);
    define_key_symbol_1(QORDFEMININE,FIX((SI_Long)170L),QORDFEMININE,Qnil,
	    Qnil,Qnil,Qnil);
    QGUILLEMOTLEFT = STATIC_SYMBOL("guillemotleft",AB_package);
    define_key_symbol_1(QGUILLEMOTLEFT,FIX((SI_Long)171L),QGUILLEMOTLEFT,
	    Qnil,Qnil,Qnil,Qnil);
    QNOTSIGN = STATIC_SYMBOL("notsign",AB_package);
    define_key_symbol_1(QNOTSIGN,FIX((SI_Long)172L),QNOTSIGN,Qnil,Qnil,
	    Qnil,Qnil);
    QHYPHEN = STATIC_SYMBOL("hyphen",AB_package);
    define_key_symbol_1(QHYPHEN,FIX((SI_Long)173L),QHYPHEN,Qnil,Qnil,Qnil,
	    Qnil);
    QREGISTERED = STATIC_SYMBOL("registered",AB_package);
    define_key_symbol_1(QREGISTERED,FIX((SI_Long)174L),QREGISTERED,Qnil,
	    Qnil,Qnil,Qnil);
    QMACRON = STATIC_SYMBOL("macron",AB_package);
    define_key_symbol_1(QMACRON,FIX((SI_Long)175L),QMACRON,Qnil,Qnil,Qnil,
	    Qnil);
    QDEGREE = STATIC_SYMBOL("degree",AB_package);
    define_key_symbol_1(QDEGREE,FIX((SI_Long)176L),QDEGREE,Qnil,Qnil,Qnil,
	    Qnil);
    QPLUSMINUS = STATIC_SYMBOL("plusminus",AB_package);
    define_key_symbol_1(QPLUSMINUS,FIX((SI_Long)177L),QPLUSMINUS,Qnil,Qnil,
	    Qnil,Qnil);
    QTWOSUPERIOR = STATIC_SYMBOL("twosuperior",AB_package);
    define_key_symbol_1(QTWOSUPERIOR,FIX((SI_Long)178L),QTWOSUPERIOR,Qnil,
	    Qnil,Qnil,Qnil);
    QTHREESUPERIOR = STATIC_SYMBOL("threesuperior",AB_package);
    define_key_symbol_1(QTHREESUPERIOR,FIX((SI_Long)179L),QTHREESUPERIOR,
	    Qnil,Qnil,Qnil,Qnil);
    QACUTE = STATIC_SYMBOL("acute",AB_package);
    define_key_symbol_1(QACUTE,FIX((SI_Long)180L),QACUTE,Qnil,Qnil,Qnil,Qnil);
    QMU = STATIC_SYMBOL("mu",AB_package);
    define_key_symbol_1(QMU,FIX((SI_Long)181L),QMU,Qnil,Qnil,Qnil,Qnil);
    QPARAGRAPH = STATIC_SYMBOL("paragraph",AB_package);
    define_key_symbol_1(QPARAGRAPH,FIX((SI_Long)182L),QPARAGRAPH,Qnil,Qnil,
	    Qnil,Qnil);
    QPERIODCENTERED = STATIC_SYMBOL("periodcentered",AB_package);
    define_key_symbol_1(QPERIODCENTERED,FIX((SI_Long)183L),QPERIODCENTERED,
	    Qnil,Qnil,Qnil,Qnil);
    QCEDILLA = STATIC_SYMBOL("cedilla",AB_package);
    define_key_symbol_1(QCEDILLA,FIX((SI_Long)184L),QCEDILLA,Qnil,Qnil,
	    Qnil,Qnil);
    QONESUPERIOR = STATIC_SYMBOL("onesuperior",AB_package);
    define_key_symbol_1(QONESUPERIOR,FIX((SI_Long)185L),QONESUPERIOR,Qnil,
	    Qnil,Qnil,Qnil);
    QMASCULINE = STATIC_SYMBOL("masculine",AB_package);
    define_key_symbol_1(QMASCULINE,FIX((SI_Long)186L),QMASCULINE,Qnil,Qnil,
	    Qnil,Qnil);
    QGUILLEMOTRIGHT = STATIC_SYMBOL("guillemotright",AB_package);
    define_key_symbol_1(QGUILLEMOTRIGHT,FIX((SI_Long)187L),QGUILLEMOTRIGHT,
	    Qnil,Qnil,Qnil,Qnil);
    QONEQUARTER = STATIC_SYMBOL("onequarter",AB_package);
    define_key_symbol_1(QONEQUARTER,FIX((SI_Long)188L),QONEQUARTER,Qnil,
	    Qnil,Qnil,Qnil);
    QONEHALF = STATIC_SYMBOL("onehalf",AB_package);
    define_key_symbol_1(QONEHALF,FIX((SI_Long)189L),QONEHALF,Qnil,Qnil,
	    Qnil,Qnil);
    QTHREEQUARTERS = STATIC_SYMBOL("threequarters",AB_package);
    define_key_symbol_1(QTHREEQUARTERS,FIX((SI_Long)190L),QTHREEQUARTERS,
	    Qnil,Qnil,Qnil,Qnil);
    QQUESTIONDOWN = STATIC_SYMBOL("questiondown",AB_package);
    define_key_symbol_1(QQUESTIONDOWN,FIX((SI_Long)191L),QQUESTIONDOWN,
	    Qnil,Qnil,Qnil,Qnil);
    QAgrave = STATIC_SYMBOL("Agrave",AB_package);
    define_key_symbol_1(QAgrave,FIX((SI_Long)192L),QAgrave,Qnil,Qnil,Qnil,
	    Qnil);
    QAacute = STATIC_SYMBOL("Aacute",AB_package);
    define_key_symbol_1(QAacute,FIX((SI_Long)193L),QAacute,Qnil,Qnil,Qnil,
	    Qnil);
    QAcircumflex = STATIC_SYMBOL("Acircumflex",AB_package);
    define_key_symbol_1(QAcircumflex,FIX((SI_Long)194L),QAcircumflex,Qnil,
	    Qnil,Qnil,Qnil);
    QAtilde = STATIC_SYMBOL("Atilde",AB_package);
    define_key_symbol_1(QAtilde,FIX((SI_Long)195L),QAtilde,Qnil,Qnil,Qnil,
	    Qnil);
    QAdiaeresis = STATIC_SYMBOL("Adiaeresis",AB_package);
    define_key_symbol_1(QAdiaeresis,FIX((SI_Long)196L),QAdiaeresis,Qnil,
	    Qnil,Qnil,Qnil);
    QAring = STATIC_SYMBOL("Aring",AB_package);
    define_key_symbol_1(QAring,FIX((SI_Long)197L),QAring,Qnil,Qnil,Qnil,Qnil);
    Qae = STATIC_SYMBOL("AE",AB_package);
    define_key_symbol_1(Qae,FIX((SI_Long)198L),Qae,Qnil,Qnil,Qnil,Qnil);
    QCcedilla = STATIC_SYMBOL("Ccedilla",AB_package);
    define_key_symbol_1(QCcedilla,FIX((SI_Long)199L),QCcedilla,Qnil,Qnil,
	    Qnil,Qnil);
    QEgrave = STATIC_SYMBOL("Egrave",AB_package);
    define_key_symbol_1(QEgrave,FIX((SI_Long)200L),QEgrave,Qnil,Qnil,Qnil,
	    Qnil);
    QEacute = STATIC_SYMBOL("Eacute",AB_package);
    define_key_symbol_1(QEacute,FIX((SI_Long)201L),QEacute,Qnil,Qnil,Qnil,
	    Qnil);
    QEcircumflex = STATIC_SYMBOL("Ecircumflex",AB_package);
    define_key_symbol_1(QEcircumflex,FIX((SI_Long)202L),QEcircumflex,Qnil,
	    Qnil,Qnil,Qnil);
    QEdiaeresis = STATIC_SYMBOL("Ediaeresis",AB_package);
    define_key_symbol_1(QEdiaeresis,FIX((SI_Long)203L),QEdiaeresis,Qnil,
	    Qnil,Qnil,Qnil);
    QIgrave = STATIC_SYMBOL("Igrave",AB_package);
    define_key_symbol_1(QIgrave,FIX((SI_Long)204L),QIgrave,Qnil,Qnil,Qnil,
	    Qnil);
    QIacute = STATIC_SYMBOL("Iacute",AB_package);
    define_key_symbol_1(QIacute,FIX((SI_Long)205L),QIacute,Qnil,Qnil,Qnil,
	    Qnil);
    QIcircumflex = STATIC_SYMBOL("Icircumflex",AB_package);
    define_key_symbol_1(QIcircumflex,FIX((SI_Long)206L),QIcircumflex,Qnil,
	    Qnil,Qnil,Qnil);
    QIdiaeresis = STATIC_SYMBOL("Idiaeresis",AB_package);
    define_key_symbol_1(QIdiaeresis,FIX((SI_Long)207L),QIdiaeresis,Qnil,
	    Qnil,Qnil,Qnil);
    Qeth = STATIC_SYMBOL("ETH",AB_package);
    define_key_symbol_1(Qeth,FIX((SI_Long)208L),Qeth,Qnil,Qnil,Qnil,Qnil);
    QNtilde = STATIC_SYMBOL("Ntilde",AB_package);
    define_key_symbol_1(QNtilde,FIX((SI_Long)209L),QNtilde,Qnil,Qnil,Qnil,
	    Qnil);
    QOgrave = STATIC_SYMBOL("Ograve",AB_package);
    define_key_symbol_1(QOgrave,FIX((SI_Long)210L),QOgrave,Qnil,Qnil,Qnil,
	    Qnil);
    QOacute = STATIC_SYMBOL("Oacute",AB_package);
    define_key_symbol_1(QOacute,FIX((SI_Long)211L),QOacute,Qnil,Qnil,Qnil,
	    Qnil);
    QOcircumflex = STATIC_SYMBOL("Ocircumflex",AB_package);
    define_key_symbol_1(QOcircumflex,FIX((SI_Long)212L),QOcircumflex,Qnil,
	    Qnil,Qnil,Qnil);
    QOtilde = STATIC_SYMBOL("Otilde",AB_package);
    define_key_symbol_1(QOtilde,FIX((SI_Long)213L),QOtilde,Qnil,Qnil,Qnil,
	    Qnil);
    QOdiaeresis = STATIC_SYMBOL("Odiaeresis",AB_package);
    define_key_symbol_1(QOdiaeresis,FIX((SI_Long)214L),QOdiaeresis,Qnil,
	    Qnil,Qnil,Qnil);
    QMULTIPLY = STATIC_SYMBOL("multiply",AB_package);
    define_key_symbol_1(QMULTIPLY,FIX((SI_Long)215L),QMULTIPLY,Qnil,Qnil,
	    Qnil,Qnil);
    QOoblique = STATIC_SYMBOL("Ooblique",AB_package);
    define_key_symbol_1(QOoblique,FIX((SI_Long)216L),QOoblique,Qnil,Qnil,
	    Qnil,Qnil);
    QUgrave = STATIC_SYMBOL("Ugrave",AB_package);
    define_key_symbol_1(QUgrave,FIX((SI_Long)217L),QUgrave,Qnil,Qnil,Qnil,
	    Qnil);
    QUacute = STATIC_SYMBOL("Uacute",AB_package);
    define_key_symbol_1(QUacute,FIX((SI_Long)218L),QUacute,Qnil,Qnil,Qnil,
	    Qnil);
    QUcircumflex = STATIC_SYMBOL("Ucircumflex",AB_package);
    define_key_symbol_1(QUcircumflex,FIX((SI_Long)219L),QUcircumflex,Qnil,
	    Qnil,Qnil,Qnil);
    QUdiaeresis = STATIC_SYMBOL("Udiaeresis",AB_package);
    define_key_symbol_1(QUdiaeresis,FIX((SI_Long)220L),QUdiaeresis,Qnil,
	    Qnil,Qnil,Qnil);
    QYacute = STATIC_SYMBOL("Yacute",AB_package);
    define_key_symbol_1(QYacute,FIX((SI_Long)221L),QYacute,Qnil,Qnil,Qnil,
	    Qnil);
    Qthorn = STATIC_SYMBOL("THORN",AB_package);
    define_key_symbol_1(Qthorn,FIX((SI_Long)222L),Qthorn,Qnil,Qnil,Qnil,Qnil);
    QSSHARP = STATIC_SYMBOL("ssharp",AB_package);
    define_key_symbol_1(QSSHARP,FIX((SI_Long)223L),QSSHARP,Qnil,Qnil,Qnil,
	    Qnil);
    QAGRAVE = STATIC_SYMBOL("agrave",AB_package);
    define_key_symbol_1(QAGRAVE,FIX((SI_Long)224L),QAGRAVE,Qnil,Qnil,Qnil,
	    Qnil);
    QAACUTE = STATIC_SYMBOL("aacute",AB_package);
    define_key_symbol_1(QAACUTE,FIX((SI_Long)225L),QAACUTE,Qnil,Qnil,Qnil,
	    Qnil);
    QACIRCUMFLEX = STATIC_SYMBOL("acircumflex",AB_package);
    define_key_symbol_1(QACIRCUMFLEX,FIX((SI_Long)226L),QACIRCUMFLEX,Qnil,
	    Qnil,Qnil,Qnil);
    QATILDE = STATIC_SYMBOL("atilde",AB_package);
    define_key_symbol_1(QATILDE,FIX((SI_Long)227L),QATILDE,Qnil,Qnil,Qnil,
	    Qnil);
    QADIAERESIS = STATIC_SYMBOL("adiaeresis",AB_package);
    define_key_symbol_1(QADIAERESIS,FIX((SI_Long)228L),QADIAERESIS,Qnil,
	    Qnil,Qnil,Qnil);
    QARING = STATIC_SYMBOL("aring",AB_package);
    define_key_symbol_1(QARING,FIX((SI_Long)229L),QARING,Qnil,Qnil,Qnil,Qnil);
    QAE = STATIC_SYMBOL("ae",AB_package);
    define_key_symbol_1(QAE,FIX((SI_Long)230L),QAE,Qnil,Qnil,Qnil,Qnil);
    QCCEDILLA = STATIC_SYMBOL("ccedilla",AB_package);
    define_key_symbol_1(QCCEDILLA,FIX((SI_Long)231L),QCCEDILLA,Qnil,Qnil,
	    Qnil,Qnil);
    QEGRAVE = STATIC_SYMBOL("egrave",AB_package);
    define_key_symbol_1(QEGRAVE,FIX((SI_Long)232L),QEGRAVE,Qnil,Qnil,Qnil,
	    Qnil);
    QEACUTE = STATIC_SYMBOL("eacute",AB_package);
    define_key_symbol_1(QEACUTE,FIX((SI_Long)233L),QEACUTE,Qnil,Qnil,Qnil,
	    Qnil);
    QECIRCUMFLEX = STATIC_SYMBOL("ecircumflex",AB_package);
    define_key_symbol_1(QECIRCUMFLEX,FIX((SI_Long)234L),QECIRCUMFLEX,Qnil,
	    Qnil,Qnil,Qnil);
    QEDIAERESIS = STATIC_SYMBOL("ediaeresis",AB_package);
    define_key_symbol_1(QEDIAERESIS,FIX((SI_Long)235L),QEDIAERESIS,Qnil,
	    Qnil,Qnil,Qnil);
    QIGRAVE = STATIC_SYMBOL("igrave",AB_package);
    define_key_symbol_1(QIGRAVE,FIX((SI_Long)236L),QIGRAVE,Qnil,Qnil,Qnil,
	    Qnil);
    QIACUTE = STATIC_SYMBOL("iacute",AB_package);
    define_key_symbol_1(QIACUTE,FIX((SI_Long)237L),QIACUTE,Qnil,Qnil,Qnil,
	    Qnil);
    QICIRCUMFLEX = STATIC_SYMBOL("icircumflex",AB_package);
    define_key_symbol_1(QICIRCUMFLEX,FIX((SI_Long)238L),QICIRCUMFLEX,Qnil,
	    Qnil,Qnil,Qnil);
    QIDIAERESIS = STATIC_SYMBOL("idiaeresis",AB_package);
    define_key_symbol_1(QIDIAERESIS,FIX((SI_Long)239L),QIDIAERESIS,Qnil,
	    Qnil,Qnil,Qnil);
    QETH = STATIC_SYMBOL("eth",AB_package);
    define_key_symbol_1(QETH,FIX((SI_Long)240L),QETH,Qnil,Qnil,Qnil,Qnil);
    QNTILDE = STATIC_SYMBOL("ntilde",AB_package);
    define_key_symbol_1(QNTILDE,FIX((SI_Long)241L),QNTILDE,Qnil,Qnil,Qnil,
	    Qnil);
    QOGRAVE = STATIC_SYMBOL("ograve",AB_package);
    define_key_symbol_1(QOGRAVE,FIX((SI_Long)242L),QOGRAVE,Qnil,Qnil,Qnil,
	    Qnil);
    QOACUTE = STATIC_SYMBOL("oacute",AB_package);
    define_key_symbol_1(QOACUTE,FIX((SI_Long)243L),QOACUTE,Qnil,Qnil,Qnil,
	    Qnil);
    QOCIRCUMFLEX = STATIC_SYMBOL("ocircumflex",AB_package);
    define_key_symbol_1(QOCIRCUMFLEX,FIX((SI_Long)244L),QOCIRCUMFLEX,Qnil,
	    Qnil,Qnil,Qnil);
    QOTILDE = STATIC_SYMBOL("otilde",AB_package);
    define_key_symbol_1(QOTILDE,FIX((SI_Long)245L),QOTILDE,Qnil,Qnil,Qnil,
	    Qnil);
    QODIAERESIS = STATIC_SYMBOL("odiaeresis",AB_package);
    define_key_symbol_1(QODIAERESIS,FIX((SI_Long)246L),QODIAERESIS,Qnil,
	    Qnil,Qnil,Qnil);
    QDIVISION = STATIC_SYMBOL("division",AB_package);
    define_key_symbol_1(QDIVISION,FIX((SI_Long)247L),QDIVISION,Qnil,Qnil,
	    Qnil,Qnil);
    QOSLASH = STATIC_SYMBOL("oslash",AB_package);
    define_key_symbol_1(QOSLASH,FIX((SI_Long)248L),QOSLASH,Qnil,Qnil,Qnil,
	    Qnil);
    QUGRAVE = STATIC_SYMBOL("ugrave",AB_package);
    define_key_symbol_1(QUGRAVE,FIX((SI_Long)249L),QUGRAVE,Qnil,Qnil,Qnil,
	    Qnil);
    QUACUTE = STATIC_SYMBOL("uacute",AB_package);
    define_key_symbol_1(QUACUTE,FIX((SI_Long)250L),QUACUTE,Qnil,Qnil,Qnil,
	    Qnil);
    QUCIRCUMFLEX = STATIC_SYMBOL("ucircumflex",AB_package);
    define_key_symbol_1(QUCIRCUMFLEX,FIX((SI_Long)251L),QUCIRCUMFLEX,Qnil,
	    Qnil,Qnil,Qnil);
    QUDIAERESIS = STATIC_SYMBOL("udiaeresis",AB_package);
    define_key_symbol_1(QUDIAERESIS,FIX((SI_Long)252L),QUDIAERESIS,Qnil,
	    Qnil,Qnil,Qnil);
    QYACUTE = STATIC_SYMBOL("yacute",AB_package);
    define_key_symbol_1(QYACUTE,FIX((SI_Long)253L),QYACUTE,Qnil,Qnil,Qnil,
	    Qnil);
    QTHORN = STATIC_SYMBOL("thorn",AB_package);
    define_key_symbol_1(QTHORN,FIX((SI_Long)254L),QTHORN,Qnil,Qnil,Qnil,Qnil);
    QYDIAERESIS = STATIC_SYMBOL("ydiaeresis",AB_package);
    define_key_symbol_1(QYDIAERESIS,FIX((SI_Long)255L),QYDIAERESIS,Qnil,
	    Qnil,Qnil,Qnil);
    QSerbian_dje = STATIC_SYMBOL("Serbian_dje",AB_package);
    define_key_symbol_1(QSerbian_dje,FIX((SI_Long)1697L),QSerbian_dje,Qnil,
	    Qnil,Qnil,Qnil);
    QMacedonia_gje = STATIC_SYMBOL("Macedonia_gje",AB_package);
    define_key_symbol_1(QMacedonia_gje,FIX((SI_Long)1698L),QMacedonia_gje,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_io = STATIC_SYMBOL("Cyrillic_io",AB_package);
    define_key_symbol_1(QCyrillic_io,FIX((SI_Long)1699L),QCyrillic_io,Qnil,
	    Qnil,Qnil,Qnil);
    QUkrainian_ie = STATIC_SYMBOL("Ukrainian_ie",AB_package);
    define_key_symbol_1(QUkrainian_ie,FIX((SI_Long)1700L),QUkrainian_ie,
	    Qnil,Qnil,Qnil,Qnil);
    QMacedonia_dse = STATIC_SYMBOL("Macedonia_dse",AB_package);
    define_key_symbol_1(QMacedonia_dse,FIX((SI_Long)1701L),QMacedonia_dse,
	    Qnil,Qnil,Qnil,Qnil);
    QUkrainian_i = STATIC_SYMBOL("Ukrainian_i",AB_package);
    define_key_symbol_1(QUkrainian_i,FIX((SI_Long)1702L),QUkrainian_i,Qnil,
	    Qnil,Qnil,Qnil);
    QUkrainian_yi = STATIC_SYMBOL("Ukrainian_yi",AB_package);
    define_key_symbol_1(QUkrainian_yi,FIX((SI_Long)1703L),QUkrainian_yi,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_je = STATIC_SYMBOL("Cyrillic_je",AB_package);
    define_key_symbol_1(QCyrillic_je,FIX((SI_Long)1704L),QCyrillic_je,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_lje = STATIC_SYMBOL("Cyrillic_lje",AB_package);
    define_key_symbol_1(QCyrillic_lje,FIX((SI_Long)1705L),QCyrillic_lje,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_nje = STATIC_SYMBOL("Cyrillic_nje",AB_package);
    define_key_symbol_1(QCyrillic_nje,FIX((SI_Long)1706L),QCyrillic_nje,
	    Qnil,Qnil,Qnil,Qnil);
    QSerbian_tshe = STATIC_SYMBOL("Serbian_tshe",AB_package);
    define_key_symbol_1(QSerbian_tshe,FIX((SI_Long)1707L),QSerbian_tshe,
	    Qnil,Qnil,Qnil,Qnil);
    QMacedonia_kje = STATIC_SYMBOL("Macedonia_kje",AB_package);
    define_key_symbol_1(QMacedonia_kje,FIX((SI_Long)1708L),QMacedonia_kje,
	    Qnil,Qnil,Qnil,Qnil);
    QByelorussian_shortu = STATIC_SYMBOL("Byelorussian_shortu",AB_package);
    define_key_symbol_1(QByelorussian_shortu,FIX((SI_Long)1710L),
	    QByelorussian_shortu,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_dzhe = STATIC_SYMBOL("Cyrillic_dzhe",AB_package);
    define_key_symbol_1(QCyrillic_dzhe,FIX((SI_Long)1711L),QCyrillic_dzhe,
	    Qnil,Qnil,Qnil,Qnil);
    QNUMEROSIGN = STATIC_SYMBOL("numerosign",AB_package);
    define_key_symbol_1(QNUMEROSIGN,FIX((SI_Long)1712L),QNUMEROSIGN,Qnil,
	    Qnil,Qnil,Qnil);
    QSerbian_DJE = STATIC_SYMBOL("Serbian_DJE",AB_package);
    define_key_symbol_1(QSerbian_DJE,FIX((SI_Long)1713L),QSerbian_DJE,Qnil,
	    Qnil,Qnil,Qnil);
    QMacedonia_GJE = STATIC_SYMBOL("Macedonia_GJE",AB_package);
    define_key_symbol_1(QMacedonia_GJE,FIX((SI_Long)1714L),QMacedonia_GJE,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_IO = STATIC_SYMBOL("Cyrillic_IO",AB_package);
    define_key_symbol_1(QCyrillic_IO,FIX((SI_Long)1715L),QCyrillic_IO,Qnil,
	    Qnil,Qnil,Qnil);
    QUkrainian_IE = STATIC_SYMBOL("Ukrainian_IE",AB_package);
    define_key_symbol_1(QUkrainian_IE,FIX((SI_Long)1716L),QUkrainian_IE,
	    Qnil,Qnil,Qnil,Qnil);
    QMacedonia_DSE = STATIC_SYMBOL("Macedonia_DSE",AB_package);
    define_key_symbol_1(QMacedonia_DSE,FIX((SI_Long)1717L),QMacedonia_DSE,
	    Qnil,Qnil,Qnil,Qnil);
    QUkrainian_I = STATIC_SYMBOL("Ukrainian_I",AB_package);
    define_key_symbol_1(QUkrainian_I,FIX((SI_Long)1718L),QUkrainian_I,Qnil,
	    Qnil,Qnil,Qnil);
    QUkrainian_YI = STATIC_SYMBOL("Ukrainian_YI",AB_package);
    define_key_symbol_1(QUkrainian_YI,FIX((SI_Long)1719L),QUkrainian_YI,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_JE = STATIC_SYMBOL("Cyrillic_JE",AB_package);
    define_key_symbol_1(QCyrillic_JE,FIX((SI_Long)1720L),QCyrillic_JE,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_LJE = STATIC_SYMBOL("Cyrillic_LJE",AB_package);
    define_key_symbol_1(QCyrillic_LJE,FIX((SI_Long)1721L),QCyrillic_LJE,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_NJE = STATIC_SYMBOL("Cyrillic_NJE",AB_package);
    define_key_symbol_1(QCyrillic_NJE,FIX((SI_Long)1722L),QCyrillic_NJE,
	    Qnil,Qnil,Qnil,Qnil);
    QSerbian_TSHE = STATIC_SYMBOL("Serbian_TSHE",AB_package);
    define_key_symbol_1(QSerbian_TSHE,FIX((SI_Long)1723L),QSerbian_TSHE,
	    Qnil,Qnil,Qnil,Qnil);
    QMacedonia_KJE = STATIC_SYMBOL("Macedonia_KJE",AB_package);
    define_key_symbol_1(QMacedonia_KJE,FIX((SI_Long)1724L),QMacedonia_KJE,
	    Qnil,Qnil,Qnil,Qnil);
    QByelorussian_SHORTU = STATIC_SYMBOL("Byelorussian_SHORTU",AB_package);
    define_key_symbol_1(QByelorussian_SHORTU,FIX((SI_Long)1726L),
	    QByelorussian_SHORTU,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_DZHE = STATIC_SYMBOL("Cyrillic_DZHE",AB_package);
    define_key_symbol_1(QCyrillic_DZHE,FIX((SI_Long)1727L),QCyrillic_DZHE,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_yu = STATIC_SYMBOL("Cyrillic_yu",AB_package);
    define_key_symbol_1(QCyrillic_yu,FIX((SI_Long)1728L),QCyrillic_yu,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_a = STATIC_SYMBOL("Cyrillic_a",AB_package);
    define_key_symbol_1(QCyrillic_a,FIX((SI_Long)1729L),QCyrillic_a,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_be = STATIC_SYMBOL("Cyrillic_be",AB_package);
    define_key_symbol_1(QCyrillic_be,FIX((SI_Long)1730L),QCyrillic_be,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_tse = STATIC_SYMBOL("Cyrillic_tse",AB_package);
    define_key_symbol_1(QCyrillic_tse,FIX((SI_Long)1731L),QCyrillic_tse,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_de = STATIC_SYMBOL("Cyrillic_de",AB_package);
    define_key_symbol_1(QCyrillic_de,FIX((SI_Long)1732L),QCyrillic_de,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_ie = STATIC_SYMBOL("Cyrillic_ie",AB_package);
    define_key_symbol_1(QCyrillic_ie,FIX((SI_Long)1733L),QCyrillic_ie,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_ef = STATIC_SYMBOL("Cyrillic_ef",AB_package);
    define_key_symbol_1(QCyrillic_ef,FIX((SI_Long)1734L),QCyrillic_ef,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_ghe = STATIC_SYMBOL("Cyrillic_ghe",AB_package);
    define_key_symbol_1(QCyrillic_ghe,FIX((SI_Long)1735L),QCyrillic_ghe,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_ha = STATIC_SYMBOL("Cyrillic_ha",AB_package);
    define_key_symbol_1(QCyrillic_ha,FIX((SI_Long)1736L),QCyrillic_ha,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_i = STATIC_SYMBOL("Cyrillic_i",AB_package);
    define_key_symbol_1(QCyrillic_i,FIX((SI_Long)1737L),QCyrillic_i,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_shorti = STATIC_SYMBOL("Cyrillic_shorti",AB_package);
    define_key_symbol_1(QCyrillic_shorti,FIX((SI_Long)1738L),
	    QCyrillic_shorti,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_ka = STATIC_SYMBOL("Cyrillic_ka",AB_package);
    define_key_symbol_1(QCyrillic_ka,FIX((SI_Long)1739L),QCyrillic_ka,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_el = STATIC_SYMBOL("Cyrillic_el",AB_package);
    define_key_symbol_1(QCyrillic_el,FIX((SI_Long)1740L),QCyrillic_el,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_em = STATIC_SYMBOL("Cyrillic_em",AB_package);
    define_key_symbol_1(QCyrillic_em,FIX((SI_Long)1741L),QCyrillic_em,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_en = STATIC_SYMBOL("Cyrillic_en",AB_package);
    define_key_symbol_1(QCyrillic_en,FIX((SI_Long)1742L),QCyrillic_en,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_o = STATIC_SYMBOL("Cyrillic_o",AB_package);
    define_key_symbol_1(QCyrillic_o,FIX((SI_Long)1743L),QCyrillic_o,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_pe = STATIC_SYMBOL("Cyrillic_pe",AB_package);
    define_key_symbol_1(QCyrillic_pe,FIX((SI_Long)1744L),QCyrillic_pe,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_ya = STATIC_SYMBOL("Cyrillic_ya",AB_package);
    define_key_symbol_1(QCyrillic_ya,FIX((SI_Long)1745L),QCyrillic_ya,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_er = STATIC_SYMBOL("Cyrillic_er",AB_package);
    define_key_symbol_1(QCyrillic_er,FIX((SI_Long)1746L),QCyrillic_er,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_es = STATIC_SYMBOL("Cyrillic_es",AB_package);
    define_key_symbol_1(QCyrillic_es,FIX((SI_Long)1747L),QCyrillic_es,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_te = STATIC_SYMBOL("Cyrillic_te",AB_package);
    define_key_symbol_1(QCyrillic_te,FIX((SI_Long)1748L),QCyrillic_te,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_u = STATIC_SYMBOL("Cyrillic_u",AB_package);
    define_key_symbol_1(QCyrillic_u,FIX((SI_Long)1749L),QCyrillic_u,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_zhe = STATIC_SYMBOL("Cyrillic_zhe",AB_package);
    define_key_symbol_1(QCyrillic_zhe,FIX((SI_Long)1750L),QCyrillic_zhe,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_ve = STATIC_SYMBOL("Cyrillic_ve",AB_package);
    define_key_symbol_1(QCyrillic_ve,FIX((SI_Long)1751L),QCyrillic_ve,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_softsign = STATIC_SYMBOL("Cyrillic_softsign",AB_package);
    define_key_symbol_1(QCyrillic_softsign,FIX((SI_Long)1752L),
	    QCyrillic_softsign,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_yeru = STATIC_SYMBOL("Cyrillic_yeru",AB_package);
    define_key_symbol_1(QCyrillic_yeru,FIX((SI_Long)1753L),QCyrillic_yeru,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_ze = STATIC_SYMBOL("Cyrillic_ze",AB_package);
    define_key_symbol_1(QCyrillic_ze,FIX((SI_Long)1754L),QCyrillic_ze,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_sha = STATIC_SYMBOL("Cyrillic_sha",AB_package);
    define_key_symbol_1(QCyrillic_sha,FIX((SI_Long)1755L),QCyrillic_sha,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_e = STATIC_SYMBOL("Cyrillic_e",AB_package);
    define_key_symbol_1(QCyrillic_e,FIX((SI_Long)1756L),QCyrillic_e,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_shcha = STATIC_SYMBOL("Cyrillic_shcha",AB_package);
    define_key_symbol_1(QCyrillic_shcha,FIX((SI_Long)1757L),
	    QCyrillic_shcha,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_che = STATIC_SYMBOL("Cyrillic_che",AB_package);
    define_key_symbol_1(QCyrillic_che,FIX((SI_Long)1758L),QCyrillic_che,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_hardsign = STATIC_SYMBOL("Cyrillic_hardsign",AB_package);
    define_key_symbol_1(QCyrillic_hardsign,FIX((SI_Long)1759L),
	    QCyrillic_hardsign,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_YU = STATIC_SYMBOL("Cyrillic_YU",AB_package);
    define_key_symbol_1(QCyrillic_YU,FIX((SI_Long)1760L),QCyrillic_YU,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_A = STATIC_SYMBOL("Cyrillic_A",AB_package);
    define_key_symbol_1(QCyrillic_A,FIX((SI_Long)1761L),QCyrillic_A,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_BE = STATIC_SYMBOL("Cyrillic_BE",AB_package);
    define_key_symbol_1(QCyrillic_BE,FIX((SI_Long)1762L),QCyrillic_BE,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_TSE = STATIC_SYMBOL("Cyrillic_TSE",AB_package);
    define_key_symbol_1(QCyrillic_TSE,FIX((SI_Long)1763L),QCyrillic_TSE,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_DE = STATIC_SYMBOL("Cyrillic_DE",AB_package);
    define_key_symbol_1(QCyrillic_DE,FIX((SI_Long)1764L),QCyrillic_DE,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_IE = STATIC_SYMBOL("Cyrillic_IE",AB_package);
    define_key_symbol_1(QCyrillic_IE,FIX((SI_Long)1765L),QCyrillic_IE,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_EF = STATIC_SYMBOL("Cyrillic_EF",AB_package);
    define_key_symbol_1(QCyrillic_EF,FIX((SI_Long)1766L),QCyrillic_EF,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_GHE = STATIC_SYMBOL("Cyrillic_GHE",AB_package);
    define_key_symbol_1(QCyrillic_GHE,FIX((SI_Long)1767L),QCyrillic_GHE,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_HA = STATIC_SYMBOL("Cyrillic_HA",AB_package);
    define_key_symbol_1(QCyrillic_HA,FIX((SI_Long)1768L),QCyrillic_HA,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_I = STATIC_SYMBOL("Cyrillic_I",AB_package);
    define_key_symbol_1(QCyrillic_I,FIX((SI_Long)1769L),QCyrillic_I,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_SHORTI = STATIC_SYMBOL("Cyrillic_SHORTI",AB_package);
    define_key_symbol_1(QCyrillic_SHORTI,FIX((SI_Long)1770L),
	    QCyrillic_SHORTI,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_KA = STATIC_SYMBOL("Cyrillic_KA",AB_package);
    define_key_symbol_1(QCyrillic_KA,FIX((SI_Long)1771L),QCyrillic_KA,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_EL = STATIC_SYMBOL("Cyrillic_EL",AB_package);
    define_key_symbol_1(QCyrillic_EL,FIX((SI_Long)1772L),QCyrillic_EL,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_EM = STATIC_SYMBOL("Cyrillic_EM",AB_package);
    define_key_symbol_1(QCyrillic_EM,FIX((SI_Long)1773L),QCyrillic_EM,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_EN = STATIC_SYMBOL("Cyrillic_EN",AB_package);
    define_key_symbol_1(QCyrillic_EN,FIX((SI_Long)1774L),QCyrillic_EN,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_O = STATIC_SYMBOL("Cyrillic_O",AB_package);
    define_key_symbol_1(QCyrillic_O,FIX((SI_Long)1775L),QCyrillic_O,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_PE = STATIC_SYMBOL("Cyrillic_PE",AB_package);
    define_key_symbol_1(QCyrillic_PE,FIX((SI_Long)1776L),QCyrillic_PE,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_YA = STATIC_SYMBOL("Cyrillic_YA",AB_package);
    define_key_symbol_1(QCyrillic_YA,FIX((SI_Long)1777L),QCyrillic_YA,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_ER = STATIC_SYMBOL("Cyrillic_ER",AB_package);
    define_key_symbol_1(QCyrillic_ER,FIX((SI_Long)1778L),QCyrillic_ER,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_ES = STATIC_SYMBOL("Cyrillic_ES",AB_package);
    define_key_symbol_1(QCyrillic_ES,FIX((SI_Long)1779L),QCyrillic_ES,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_TE = STATIC_SYMBOL("Cyrillic_TE",AB_package);
    define_key_symbol_1(QCyrillic_TE,FIX((SI_Long)1780L),QCyrillic_TE,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_U = STATIC_SYMBOL("Cyrillic_U",AB_package);
    define_key_symbol_1(QCyrillic_U,FIX((SI_Long)1781L),QCyrillic_U,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_ZHE = STATIC_SYMBOL("Cyrillic_ZHE",AB_package);
    define_key_symbol_1(QCyrillic_ZHE,FIX((SI_Long)1782L),QCyrillic_ZHE,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_VE = STATIC_SYMBOL("Cyrillic_VE",AB_package);
    define_key_symbol_1(QCyrillic_VE,FIX((SI_Long)1783L),QCyrillic_VE,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_SOFTSIGN = STATIC_SYMBOL("Cyrillic_SOFTSIGN",AB_package);
    define_key_symbol_1(QCyrillic_SOFTSIGN,FIX((SI_Long)1784L),
	    QCyrillic_SOFTSIGN,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_YERU = STATIC_SYMBOL("Cyrillic_YERU",AB_package);
    define_key_symbol_1(QCyrillic_YERU,FIX((SI_Long)1785L),QCyrillic_YERU,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_ZE = STATIC_SYMBOL("Cyrillic_ZE",AB_package);
    define_key_symbol_1(QCyrillic_ZE,FIX((SI_Long)1786L),QCyrillic_ZE,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_SHA = STATIC_SYMBOL("Cyrillic_SHA",AB_package);
    define_key_symbol_1(QCyrillic_SHA,FIX((SI_Long)1787L),QCyrillic_SHA,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_E = STATIC_SYMBOL("Cyrillic_E",AB_package);
    define_key_symbol_1(QCyrillic_E,FIX((SI_Long)1788L),QCyrillic_E,Qnil,
	    Qnil,Qnil,Qnil);
    QCyrillic_SHCHA = STATIC_SYMBOL("Cyrillic_SHCHA",AB_package);
    define_key_symbol_1(QCyrillic_SHCHA,FIX((SI_Long)1789L),
	    QCyrillic_SHCHA,Qnil,Qnil,Qnil,Qnil);
    QCyrillic_CHE = STATIC_SYMBOL("Cyrillic_CHE",AB_package);
    define_key_symbol_1(QCyrillic_CHE,FIX((SI_Long)1790L),QCyrillic_CHE,
	    Qnil,Qnil,Qnil,Qnil);
    QCyrillic_HARDSIGN = STATIC_SYMBOL("Cyrillic_HARDSIGN",AB_package);
    define_key_symbol_1(QCyrillic_HARDSIGN,FIX((SI_Long)1791L),
	    QCyrillic_HARDSIGN,Qnil,Qnil,Qnil,Qnil);
    Qcyrillic_gensym_character_code_for_key_name = 
	    STATIC_SYMBOL("CYRILLIC-GENSYM-CHARACTER-CODE-FOR-KEY-NAME",
	    AB_package);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    Qnon_spacing_mark = STATIC_SYMBOL("NON-SPACING-MARK",AB_package);
    Qordinary_space = STATIC_SYMBOL("ORDINARY-SPACE",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qmark,Qnon_spacing_mark,
	    Qordinary_space);
    define_key_symbol_1(Qdelete,FIX((SI_Long)127L),Qdelete,CHR('\177'),
	    FIX((SI_Long)127L),Qt,Qnil);
    Qdel = STATIC_SYMBOL("DEL",AB_package);
    define_key_symbol_1(Qdel,FIX((SI_Long)128L),Qdel,Qnil,Qnil,Qnil,Qnil);
    Qrubout = STATIC_SYMBOL("RUBOUT",AB_package);
    define_key_symbol_1(Qrubout,FIX((SI_Long)135L),Qrubout,Qnil,Qnil,Qnil,
	    Qnil);
    Qnon_event = STATIC_SYMBOL("NON-EVENT",AB_package);
    define_key_symbol_1(Qnon_event,FIX((SI_Long)768L),Qnon_event,Qnil,Qnil,
	    Qnil,Qnil);
    Qmouse_up = STATIC_SYMBOL("MOUSE-UP",AB_package);
    define_key_symbol_1(Qmouse_up,FIX((SI_Long)769L),Qmouse_up,Qnil,Qnil,
	    Qnil,Qnil);
    Qmouse_down = STATIC_SYMBOL("MOUSE-DOWN",AB_package);
    define_key_symbol_1(Qmouse_down,FIX((SI_Long)770L),Qmouse_down,Qnil,
	    Qnil,Qnil,Qnil);
    Qmouse_motion = STATIC_SYMBOL("MOUSE-MOTION",AB_package);
    define_key_symbol_1(Qmouse_motion,FIX((SI_Long)771L),Qmouse_motion,
	    Qnil,Qnil,Qnil,Qnil);
    Qmouse_left_down = STATIC_SYMBOL("MOUSE-LEFT-DOWN",AB_package);
    define_key_symbol_1(Qmouse_left_down,FIX((SI_Long)772L),
	    Qmouse_left_down,Qnil,Qnil,Qnil,Qnil);
    Qmouse_left_up = STATIC_SYMBOL("MOUSE-LEFT-UP",AB_package);
    define_key_symbol_1(Qmouse_left_up,FIX((SI_Long)773L),Qmouse_left_up,
	    Qnil,Qnil,Qnil,Qnil);
    Qmouse_middle_down = STATIC_SYMBOL("MOUSE-MIDDLE-DOWN",AB_package);
    define_key_symbol_1(Qmouse_middle_down,FIX((SI_Long)774L),
	    Qmouse_middle_down,Qnil,Qnil,Qnil,Qnil);
    Qmouse_middle_up = STATIC_SYMBOL("MOUSE-MIDDLE-UP",AB_package);
    define_key_symbol_1(Qmouse_middle_up,FIX((SI_Long)775L),
	    Qmouse_middle_up,Qnil,Qnil,Qnil,Qnil);
    Qmouse_right_down = STATIC_SYMBOL("MOUSE-RIGHT-DOWN",AB_package);
    define_key_symbol_1(Qmouse_right_down,FIX((SI_Long)776L),
	    Qmouse_right_down,Qnil,Qnil,Qnil,Qnil);
    Qmouse_right_up = STATIC_SYMBOL("MOUSE-RIGHT-UP",AB_package);
    define_key_symbol_1(Qmouse_right_up,FIX((SI_Long)777L),Qmouse_right_up,
	    Qnil,Qnil,Qnil,Qnil);
    Qmouse_drag = STATIC_SYMBOL("MOUSE-DRAG",AB_package);
    define_key_symbol_1(Qmouse_drag,FIX((SI_Long)778L),Qmouse_drag,Qnil,
	    Qnil,Qnil,Qnil);
    Qmouse_select = STATIC_SYMBOL("MOUSE-SELECT",AB_package);
    define_key_symbol_1(Qmouse_select,FIX((SI_Long)779L),Qmouse_select,
	    Qnil,Qnil,Qnil,Qnil);
    Qmouse_wheel_forward = STATIC_SYMBOL("MOUSE-WHEEL-FORWARD",AB_package);
    define_key_symbol_1(Qmouse_wheel_forward,FIX((SI_Long)780L),
	    Qmouse_wheel_forward,Qnil,Qnil,Qt,Qnil);
    Qmouse_wheel_backward = STATIC_SYMBOL("MOUSE-WHEEL-BACKWARD",AB_package);
    define_key_symbol_1(Qmouse_wheel_backward,FIX((SI_Long)781L),
	    Qmouse_wheel_backward,Qnil,Qnil,Qt,Qnil);
    Qmouse_hover = STATIC_SYMBOL("MOUSE-HOVER",AB_package);
    define_key_symbol_1(Qmouse_hover,FIX((SI_Long)782L),Qmouse_hover,Qnil,
	    Qnil,Qt,Qnil);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qmiddle = STATIC_SYMBOL("MIDDLE",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qwindow_refresh = STATIC_SYMBOL("WINDOW-REFRESH",AB_package);
    define_key_symbol_1(Qwindow_refresh,FIX((SI_Long)784L),Qwindow_refresh,
	    Qnil,Qnil,Qnil,Qt);
    Qwindow_reshape = STATIC_SYMBOL("WINDOW-RESHAPE",AB_package);
    define_key_symbol_1(Qwindow_reshape,FIX((SI_Long)785L),Qwindow_reshape,
	    Qnil,Qnil,Qnil,Qt);
    Qpaste_request = STATIC_SYMBOL("PASTE-REQUEST",AB_package);
    define_key_symbol_1(Qpaste_request,FIX((SI_Long)786L),Qpaste_request,
	    Qnil,Qnil,Qnil,Qt);
    Qpaste_availability_request = 
	    STATIC_SYMBOL("PASTE-AVAILABILITY-REQUEST",AB_package);
    define_key_symbol_1(Qpaste_availability_request,FIX((SI_Long)787L),
	    Qpaste_availability_request,Qnil,Qnil,Qnil,Qt);
    Qwindow_activated = STATIC_SYMBOL("WINDOW-ACTIVATED",AB_package);
    define_key_symbol_1(Qwindow_activated,FIX((SI_Long)788L),
	    Qwindow_activated,Qnil,Qnil,Qnil,Qt);
    Qwindow_closed = STATIC_SYMBOL("WINDOW-CLOSED",AB_package);
    define_key_symbol_1(Qwindow_closed,FIX((SI_Long)789L),Qwindow_closed,
	    Qnil,Qnil,Qnil,Qt);
    Qenter_window = STATIC_SYMBOL("ENTER-WINDOW",AB_package);
    define_key_symbol_1(Qenter_window,FIX((SI_Long)790L),Qenter_window,
	    Qnil,Qnil,Qnil,Qt);
    Qleave_window = STATIC_SYMBOL("LEAVE-WINDOW",AB_package);
    define_key_symbol_1(Qleave_window,FIX((SI_Long)791L),Qleave_window,
	    Qnil,Qnil,Qnil,Qt);
    Qwindow_moved = STATIC_SYMBOL("WINDOW-MOVED",AB_package);
    define_key_symbol_1(Qwindow_moved,FIX((SI_Long)792L),Qwindow_moved,
	    Qnil,Qnil,Qnil,Qt);
    Qwindow_sized = STATIC_SYMBOL("WINDOW-SIZED",AB_package);
    define_key_symbol_1(Qwindow_sized,FIX((SI_Long)793L),Qwindow_sized,
	    Qnil,Qnil,Qnil,Qt);
    Qwindow_scrolled = STATIC_SYMBOL("WINDOW-SCROLLED",AB_package);
    define_key_symbol_1(Qwindow_scrolled,FIX((SI_Long)794L),
	    Qwindow_scrolled,Qnil,Qnil,Qnil,Qt);
    Qdouble_escape = STATIC_SYMBOL("DOUBLE-ESCAPE",AB_package);
    define_key_symbol_1(Qdouble_escape,FIX((SI_Long)800L),Qdouble_escape,
	    Qnil,Qnil,Qnil,Qnil);
    Qsimple_dialog_ok = STATIC_SYMBOL("SIMPLE-DIALOG-OK",AB_package);
    define_key_symbol_1(Qsimple_dialog_ok,FIX((SI_Long)801L),
	    Qsimple_dialog_ok,Qnil,Qnil,Qnil,Qt);
    Qsimple_dialog_cancel = STATIC_SYMBOL("SIMPLE-DIALOG-CANCEL",AB_package);
    define_key_symbol_1(Qsimple_dialog_cancel,FIX((SI_Long)802L),
	    Qsimple_dialog_cancel,Qnil,Qnil,Qnil,Qt);
    Qsimple_dialog_additional = STATIC_SYMBOL("SIMPLE-DIALOG-ADDITIONAL",
	    AB_package);
    define_key_symbol_1(Qsimple_dialog_additional,FIX((SI_Long)803L),
	    Qsimple_dialog_additional,Qnil,Qnil,Qnil,Qt);
    Qmenu_choice = STATIC_SYMBOL("MENU-CHOICE",AB_package);
    define_key_symbol_1(Qmenu_choice,FIX((SI_Long)804L),Qmenu_choice,Qnil,
	    Qnil,Qnil,Qt);
    Qfile_open = STATIC_SYMBOL("FILE-OPEN",AB_package);
    define_key_symbol_1(Qfile_open,FIX((SI_Long)805L),Qfile_open,Qnil,Qnil,
	    Qnil,Qt);
    Qfile_save_as = STATIC_SYMBOL("FILE-SAVE-AS",AB_package);
    define_key_symbol_1(Qfile_save_as,FIX((SI_Long)806L),Qfile_save_as,
	    Qnil,Qnil,Qnil,Qt);
    Qhscroll = STATIC_SYMBOL("HSCROLL",AB_package);
    define_key_symbol_1(Qhscroll,FIX((SI_Long)810L),Qhscroll,Qnil,Qnil,
	    Qnil,Qt);
    Qvscroll = STATIC_SYMBOL("VSCROLL",AB_package);
    define_key_symbol_1(Qvscroll,FIX((SI_Long)811L),Qvscroll,Qnil,Qnil,
	    Qnil,Qt);
    Qmouse_left_select = STATIC_SYMBOL("MOUSE-LEFT-SELECT",AB_package);
    define_key_symbol_1(Qmouse_left_select,FIX((SI_Long)812L),
	    Qmouse_left_select,Qnil,Qnil,Qnil,Qnil);
    Qmouse_middle_select = STATIC_SYMBOL("MOUSE-MIDDLE-SELECT",AB_package);
    define_key_symbol_1(Qmouse_middle_select,FIX((SI_Long)813L),
	    Qmouse_middle_select,Qnil,Qnil,Qnil,Qnil);
    Qmouse_right_select = STATIC_SYMBOL("MOUSE-RIGHT-SELECT",AB_package);
    define_key_symbol_1(Qmouse_right_select,FIX((SI_Long)814L),
	    Qmouse_right_select,Qnil,Qnil,Qnil,Qnil);
    Qmouse_left_drag = STATIC_SYMBOL("MOUSE-LEFT-DRAG",AB_package);
    define_key_symbol_1(Qmouse_left_drag,FIX((SI_Long)815L),
	    Qmouse_left_drag,Qnil,Qnil,Qnil,Qnil);
    Qmouse_middle_drag = STATIC_SYMBOL("MOUSE-MIDDLE-DRAG",AB_package);
    define_key_symbol_1(Qmouse_middle_drag,FIX((SI_Long)816L),
	    Qmouse_middle_drag,Qnil,Qnil,Qnil,Qnil);
    Qmouse_right_drag = STATIC_SYMBOL("MOUSE-RIGHT-DRAG",AB_package);
    define_key_symbol_1(Qmouse_right_drag,FIX((SI_Long)817L),
	    Qmouse_right_drag,Qnil,Qnil,Qnil,Qnil);
    Qmenu_bar = STATIC_SYMBOL("MENU-BAR",AB_package);
    define_key_symbol_1(Qmenu_bar,FIX((SI_Long)818L),Qmenu_bar,Qnil,Qnil,
	    Qnil,Qt);
    Qfile_dialog = STATIC_SYMBOL("FILE-DIALOG",AB_package);
    define_key_symbol_1(Qfile_dialog,FIX((SI_Long)819L),Qfile_dialog,Qnil,
	    Qnil,Qnil,Qt);
    Qstatus_bar = STATIC_SYMBOL("STATUS-BAR",AB_package);
    define_key_symbol_1(Qstatus_bar,FIX((SI_Long)820L),Qstatus_bar,Qnil,
	    Qnil,Qnil,Qt);
    Qpre_nms_menu_choice = STATIC_SYMBOL("PRE-NMS-MENU-CHOICE",AB_package);
    define_key_symbol_1(Qpre_nms_menu_choice,FIX((SI_Long)821L),
	    Qpre_nms_menu_choice,Qnil,Qnil,Qnil,Qt);
    Qprint_window = STATIC_SYMBOL("PRINT-WINDOW",AB_package);
    define_key_symbol_1(Qprint_window,FIX((SI_Long)822L),Qprint_window,
	    Qnil,Qnil,Qnil,Qt);
    Qabout_box = STATIC_SYMBOL("ABOUT-BOX",AB_package);
    define_key_symbol_1(Qabout_box,FIX((SI_Long)823L),Qabout_box,Qnil,Qnil,
	    Qnil,Qt);
    Qprint_dialog = STATIC_SYMBOL("PRINT-DIALOG",AB_package);
    define_key_symbol_1(Qprint_dialog,FIX((SI_Long)824L),Qprint_dialog,
	    Qnil,Qnil,Qnil,Qt);
    Qnms_menu_posted = STATIC_SYMBOL("NMS-MENU-POSTED",AB_package);
    define_key_symbol_1(Qnms_menu_posted,FIX((SI_Long)825L),
	    Qnms_menu_posted,Qnil,Qnil,Qnil,Qt);
    Qbasic_dialog = STATIC_SYMBOL("BASIC-DIALOG",AB_package);
    define_key_symbol_1(Qbasic_dialog,FIX((SI_Long)826L),Qbasic_dialog,
	    Qnil,Qnil,Qnil,Qt);
    Qnms_control = STATIC_SYMBOL("NMS-CONTROL",AB_package);
    define_key_symbol_1(Qnms_control,FIX((SI_Long)827L),Qnms_control,Qnil,
	    Qnil,Qnil,Qt);
    Qdialog_update = STATIC_SYMBOL("DIALOG-UPDATE",AB_package);
    define_key_symbol_1(Qdialog_update,FIX((SI_Long)828L),Qdialog_update,
	    Qnil,Qnil,Qnil,Qt);
    Qdialog_dismissed = STATIC_SYMBOL("DIALOG-DISMISSED",AB_package);
    define_key_symbol_1(Qdialog_dismissed,FIX((SI_Long)829L),
	    Qdialog_dismissed,Qnil,Qnil,Qnil,Qt);
    Qlist_directory = STATIC_SYMBOL("LIST-DIRECTORY",AB_package);
    define_key_symbol_1(Qlist_directory,FIX((SI_Long)830L),Qlist_directory,
	    Qnil,Qnil,Qnil,Qt);
    Qdialog_miscellaneous_communication = 
	    STATIC_SYMBOL("DIALOG-MISCELLANEOUS-COMMUNICATION",AB_package);
    define_key_symbol_1(Qdialog_miscellaneous_communication,
	    FIX((SI_Long)831L),Qdialog_miscellaneous_communication,Qnil,
	    Qnil,Qnil,Qt);
    Qnms_menu_item_selected = STATIC_SYMBOL("NMS-MENU-ITEM-SELECTED",
	    AB_package);
    define_key_symbol_1(Qnms_menu_item_selected,FIX((SI_Long)832L),
	    Qnms_menu_item_selected,Qnil,Qnil,Qnil,Qt);
    Qtree_view = STATIC_SYMBOL("TREE-VIEW",AB_package);
    define_key_symbol_1(Qtree_view,FIX((SI_Long)833L),Qtree_view,Qnil,Qnil,
	    Qnil,Qt);
    Qhtml_view = STATIC_SYMBOL("HTML-VIEW",AB_package);
    define_key_symbol_1(Qhtml_view,FIX((SI_Long)834L),Qhtml_view,Qnil,Qnil,
	    Qnil,Qt);
    Qdebugger_dialog = STATIC_SYMBOL("DEBUGGER-DIALOG",AB_package);
    define_key_symbol_1(Qdebugger_dialog,FIX((SI_Long)835L),
	    Qdebugger_dialog,Qnil,Qnil,Qnil,Qt);
    Qeditor = STATIC_SYMBOL("EDITOR",AB_package);
    define_key_symbol_1(Qeditor,FIX((SI_Long)836L),Qeditor,Qnil,Qnil,Qnil,Qt);
    Qnms_menu_unposted = STATIC_SYMBOL("NMS-MENU-UNPOSTED",AB_package);
    define_key_symbol_1(Qnms_menu_unposted,FIX((SI_Long)837L),
	    Qnms_menu_unposted,Qnil,Qnil,Qnil,Qt);
    Qshortcut_bar = STATIC_SYMBOL("SHORTCUT-BAR",AB_package);
    define_key_symbol_1(Qshortcut_bar,FIX((SI_Long)838L),Qshortcut_bar,
	    Qnil,Qnil,Qnil,Qt);
    Qchart_view = STATIC_SYMBOL("CHART-VIEW",AB_package);
    define_key_symbol_1(Qchart_view,FIX((SI_Long)839L),Qchart_view,Qnil,
	    Qnil,Qnil,Qt);
    Qlogbook_view = STATIC_SYMBOL("LOGBOOK-VIEW",AB_package);
    define_key_symbol_1(Qlogbook_view,FIX((SI_Long)840L),Qlogbook_view,
	    Qnil,Qnil,Qnil,Qt);
    Qlogin_dialog = STATIC_SYMBOL("LOGIN-DIALOG",AB_package);
    define_key_symbol_1(Qlogin_dialog,FIX((SI_Long)841L),Qlogin_dialog,
	    Qnil,Qnil,Qnil,Qt);
    Qprop_grid = STATIC_SYMBOL("PROP-GRID",AB_package);
    define_key_symbol_1(Qprop_grid,FIX((SI_Long)842L),Qprop_grid,Qnil,Qnil,
	    Qnil,Qt);
    Qdialog_user_gesture = STATIC_SYMBOL("DIALOG-USER-GESTURE",AB_package);
    define_key_symbol_1(Qdialog_user_gesture,FIX((SI_Long)843L),
	    Qdialog_user_gesture,Qnil,Qnil,Qnil,Qt);
    Qgrid_view = STATIC_SYMBOL("GRID-VIEW",AB_package);
    define_key_symbol_1(Qgrid_view,FIX((SI_Long)844L),Qgrid_view,Qnil,Qnil,
	    Qnil,Qt);
    Qtabular_view = STATIC_SYMBOL("TABULAR-VIEW",AB_package);
    define_key_symbol_1(Qtabular_view,FIX((SI_Long)845L),Qtabular_view,
	    Qnil,Qnil,Qnil,Qt);
    Qlist_sys_drives = STATIC_SYMBOL("LIST-SYS-DRIVES",AB_package);
    define_key_symbol_1(Qlist_sys_drives,FIX((SI_Long)846L),
	    Qlist_sys_drives,Qnil,Qnil,Qnil,Qt);
    define_key_symbol_1(Qbreak,FIX((SI_Long)385L),Qbreak,Qnil,Qnil,Qt,Qnil);
    Qenter = STATIC_SYMBOL("ENTER",AB_package);
    define_key_symbol_1(Qenter,FIX((SI_Long)660L),Qenter,Qnil,Qnil,Qt,Qnil);
    Qkp_space = STATIC_SYMBOL("KP-SPACE",AB_package);
    define_key_symbol_1(Qkp_space,FIX((SI_Long)453L),Qkp_space,Qnil,Qnil,
	    Qnil,Qnil);
    Qkp_tab = STATIC_SYMBOL("KP-TAB",AB_package);
    define_key_symbol_1(Qkp_tab,FIX((SI_Long)454L),Qkp_tab,Qnil,Qnil,Qnil,
	    Qnil);
    Qkp_enter = STATIC_SYMBOL("KP-ENTER",AB_package);
    define_key_symbol_1(Qkp_enter,FIX((SI_Long)455L),Qkp_enter,Qnil,Qnil,
	    Qnil,Qnil);
    Qkp_f1 = STATIC_SYMBOL("KP-F1",AB_package);
    define_key_symbol_1(Qkp_f1,FIX((SI_Long)456L),Qkp_f1,Qnil,Qnil,Qnil,Qnil);
    Qkp_f2 = STATIC_SYMBOL("KP-F2",AB_package);
    define_key_symbol_1(Qkp_f2,FIX((SI_Long)457L),Qkp_f2,Qnil,Qnil,Qnil,Qnil);
    Qkp_f3 = STATIC_SYMBOL("KP-F3",AB_package);
    define_key_symbol_1(Qkp_f3,FIX((SI_Long)458L),Qkp_f3,Qnil,Qnil,Qnil,Qnil);
    Qkp_f4 = STATIC_SYMBOL("KP-F4",AB_package);
    define_key_symbol_1(Qkp_f4,FIX((SI_Long)459L),Qkp_f4,Qnil,Qnil,Qnil,Qnil);
    Qkp_equal = STATIC_SYMBOL("KP-EQUAL",AB_package);
    define_key_symbol_1(Qkp_equal,FIX((SI_Long)460L),Qkp_equal,Qnil,Qnil,
	    Qnil,Qnil);
    Qkp_multiply = STATIC_SYMBOL("KP-MULTIPLY",AB_package);
    define_key_symbol_1(Qkp_multiply,FIX((SI_Long)461L),Qkp_multiply,Qnil,
	    Qnil,Qnil,Qnil);
    Qkp_add = STATIC_SYMBOL("KP-ADD",AB_package);
    define_key_symbol_1(Qkp_add,FIX((SI_Long)462L),Qkp_add,Qnil,Qnil,Qnil,
	    Qnil);
    Qkp_separator = STATIC_SYMBOL("KP-SEPARATOR",AB_package);
    define_key_symbol_1(Qkp_separator,FIX((SI_Long)463L),Qkp_separator,
	    Qnil,Qnil,Qnil,Qnil);
    Qkp_subtract = STATIC_SYMBOL("KP-SUBTRACT",AB_package);
    define_key_symbol_1(Qkp_subtract,FIX((SI_Long)464L),Qkp_subtract,Qnil,
	    Qnil,Qnil,Qnil);
    Qkp_decimal = STATIC_SYMBOL("KP-DECIMAL",AB_package);
    define_key_symbol_1(Qkp_decimal,FIX((SI_Long)465L),Qkp_decimal,Qnil,
	    Qnil,Qnil,Qnil);
    Qkp_divide = STATIC_SYMBOL("KP-DIVIDE",AB_package);
    define_key_symbol_1(Qkp_divide,FIX((SI_Long)466L),Qkp_divide,Qnil,Qnil,
	    Qnil,Qnil);
    Qkp_0 = STATIC_SYMBOL("KP-0",AB_package);
    define_key_symbol_1(Qkp_0,FIX((SI_Long)470L),Qkp_0,Qnil,Qnil,Qnil,Qnil);
    Qkp_1 = STATIC_SYMBOL("KP-1",AB_package);
    define_key_symbol_1(Qkp_1,FIX((SI_Long)471L),Qkp_1,Qnil,Qnil,Qnil,Qnil);
    Qkp_2 = STATIC_SYMBOL("KP-2",AB_package);
    define_key_symbol_1(Qkp_2,FIX((SI_Long)472L),Qkp_2,Qnil,Qnil,Qnil,Qnil);
    Qkp_3 = STATIC_SYMBOL("KP-3",AB_package);
    define_key_symbol_1(Qkp_3,FIX((SI_Long)473L),Qkp_3,Qnil,Qnil,Qnil,Qnil);
    Qkp_4 = STATIC_SYMBOL("KP-4",AB_package);
    define_key_symbol_1(Qkp_4,FIX((SI_Long)474L),Qkp_4,Qnil,Qnil,Qnil,Qnil);
    Qkp_5 = STATIC_SYMBOL("KP-5",AB_package);
    define_key_symbol_1(Qkp_5,FIX((SI_Long)475L),Qkp_5,Qnil,Qnil,Qnil,Qnil);
    Qkp_6 = STATIC_SYMBOL("KP-6",AB_package);
    define_key_symbol_1(Qkp_6,FIX((SI_Long)476L),Qkp_6,Qnil,Qnil,Qnil,Qnil);
    Qkp_7 = STATIC_SYMBOL("KP-7",AB_package);
    define_key_symbol_1(Qkp_7,FIX((SI_Long)477L),Qkp_7,Qnil,Qnil,Qnil,Qnil);
    Qkp_8 = STATIC_SYMBOL("KP-8",AB_package);
    define_key_symbol_1(Qkp_8,FIX((SI_Long)478L),Qkp_8,Qnil,Qnil,Qnil,Qnil);
    Qkp_9 = STATIC_SYMBOL("KP-9",AB_package);
    define_key_symbol_1(Qkp_9,FIX((SI_Long)479L),Qkp_9,Qnil,Qnil,Qnil,Qnil);
    Qhelp = STATIC_SYMBOL("HELP",AB_package);
    define_key_symbol_1(Qhelp,FIX((SI_Long)390L),Qhelp,Qnil,Qnil,Qt,Qnil);
    Qinsert = STATIC_SYMBOL("INSERT",AB_package);
    define_key_symbol_1(Qinsert,FIX((SI_Long)480L),Qinsert,Qnil,Qnil,Qt,Qnil);
    Qredo = STATIC_SYMBOL("REDO",AB_package);
    define_key_symbol_1(Qredo,FIX((SI_Long)481L),Qredo,Qnil,Qnil,Qt,Qnil);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    define_key_symbol_1(Qmenu,FIX((SI_Long)482L),Qmenu,Qnil,Qnil,Qt,Qnil);
    define_key_symbol_1(Qfind,FIX((SI_Long)483L),Qfind,Qnil,Qnil,Qt,Qnil);
    Qhome = STATIC_SYMBOL("HOME",AB_package);
    define_key_symbol_1(Qhome,FIX((SI_Long)484L),Qhome,Qnil,Qnil,Qt,Qnil);
    Qbegin = STATIC_SYMBOL("BEGIN",AB_package);
    define_key_symbol_1(Qbegin,FIX((SI_Long)485L),Qbegin,Qnil,Qnil,Qt,Qnil);
    Qend = STATIC_SYMBOL("END",AB_package);
    define_key_symbol_1(Qend,FIX((SI_Long)404L),Qend,Qnil,Qnil,Qt,Qnil);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    define_key_symbol_1(Qpause,FIX((SI_Long)486L),Qpause,Qnil,Qnil,Qt,Qnil);
    Qselect = STATIC_SYMBOL("SELECT",AB_package);
    define_key_symbol_1(Qselect,FIX((SI_Long)487L),Qselect,Qnil,Qnil,Qt,Qnil);
    define_key_symbol_1(Qprint,FIX((SI_Long)488L),Qprint,Qnil,Qnil,Qt,Qnil);
    Qexecute = STATIC_SYMBOL("EXECUTE",AB_package);
    define_key_symbol_1(Qexecute,FIX((SI_Long)489L),Qexecute,Qnil,Qnil,Qt,
	    Qnil);
    Qabort_g2 = STATIC_SYMBOL("ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qabort_g2,STATIC_FUNCTION(abort_g2,NIL,TRUE,0,1));
    define_key_symbol_1(Qabort_g2,FIX((SI_Long)401L),Qabort_g2,Qnil,Qnil,
	    Qt,Qnil);
    Qclear_screen = STATIC_SYMBOL("CLEAR-SCREEN",AB_package);
    define_key_symbol_1(Qclear_screen,FIX((SI_Long)396L),Qclear_screen,
	    Qnil,Qnil,Qt,Qnil);
    Qforward_delete = STATIC_SYMBOL("FORWARD-DELETE",AB_package);
    define_key_symbol_1(Qforward_delete,FIX((SI_Long)384L),Qforward_delete,
	    Qnil,Qnil,Qnil,Qnil);
    Qpage_up = STATIC_SYMBOL("PAGE-UP",AB_package);
    define_key_symbol_1(Qpage_up,FIX((SI_Long)387L),Qpage_up,Qnil,Qnil,
	    Qnil,Qnil);
    Qpage_down = STATIC_SYMBOL("PAGE-DOWN",AB_package);
    define_key_symbol_1(Qpage_down,FIX((SI_Long)389L),Qpage_down,Qnil,Qnil,
	    Qnil,Qnil);
    Qup_arrow = STATIC_SYMBOL("UP-ARROW",AB_package);
    define_key_symbol_1(Qup_arrow,FIX((SI_Long)274L),Qup_arrow,Qnil,Qnil,
	    Qt,Qnil);
    Qdown_arrow = STATIC_SYMBOL("DOWN-ARROW",AB_package);
    define_key_symbol_1(Qdown_arrow,FIX((SI_Long)275L),Qdown_arrow,Qnil,
	    Qnil,Qt,Qnil);
    Qleft_arrow = STATIC_SYMBOL("LEFT-ARROW",AB_package);
    define_key_symbol_1(Qleft_arrow,FIX((SI_Long)276L),Qleft_arrow,Qnil,
	    Qnil,Qt,Qnil);
    Qright_arrow = STATIC_SYMBOL("RIGHT-ARROW",AB_package);
    define_key_symbol_1(Qright_arrow,FIX((SI_Long)277L),Qright_arrow,Qnil,
	    Qnil,Qt,Qnil);
    Qprevious_screen = STATIC_SYMBOL("PREVIOUS-SCREEN",AB_package);
    define_key_symbol_1(Qprevious_screen,FIX((SI_Long)315L),
	    Qprevious_screen,Qnil,Qnil,Qt,Qnil);
    Qnext_screen = STATIC_SYMBOL("NEXT-SCREEN",AB_package);
    define_key_symbol_1(Qnext_screen,FIX((SI_Long)316L),Qnext_screen,Qnil,
	    Qnil,Qt,Qnil);
    Qnetwork = STATIC_SYMBOL("NETWORK",AB_package);
    define_key_symbol_1(Qnetwork,FIX((SI_Long)414L),Qnetwork,Qnil,Qnil,
	    Qnil,Qnil);
    define_key_symbol_1(Qclear_input,FIX((SI_Long)386L),Qclear_input,Qnil,
	    Qnil,Qnil,Qnil);
    Qresume = STATIC_SYMBOL("RESUME",AB_package);
    define_key_symbol_1(Qresume,FIX((SI_Long)402L),Qresume,Qnil,Qnil,Qnil,
	    Qnil);
    define_key_symbol_1(Qfunction,FIX((SI_Long)644L),Qfunction,Qnil,Qnil,
	    Qnil,Qnil);
    Qrefresh = STATIC_SYMBOL("REFRESH",AB_package);
    define_key_symbol_1(Qrefresh,FIX((SI_Long)395L),Qrefresh,Qnil,Qnil,
	    Qnil,Qnil);
    Qsquare = STATIC_SYMBOL("SQUARE",AB_package);
    define_key_symbol_1(Qsquare,FIX((SI_Long)661L),Qsquare,Qnil,Qnil,Qnil,
	    Qnil);
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    define_key_symbol_1(Qcircle,FIX((SI_Long)662L),Qcircle,Qnil,Qnil,Qnil,
	    Qnil);
    Qtriangle = STATIC_SYMBOL("TRIANGLE",AB_package);
    define_key_symbol_1(Qtriangle,FIX((SI_Long)663L),Qtriangle,Qnil,Qnil,
	    Qnil,Qnil);
    Qsuspend = STATIC_SYMBOL("SUSPEND",AB_package);
    define_key_symbol_1(Qsuspend,FIX((SI_Long)641L),Qsuspend,Qnil,Qnil,
	    Qnil,Qnil);
    Qpage = STATIC_SYMBOL("PAGE",AB_package);
    define_key_symbol_1(Qpage,FIX((SI_Long)652L),Qpage,Qnil,Qnil,Qnil,Qnil);
    Qcomplete = STATIC_SYMBOL("COMPLETE",AB_package);
    define_key_symbol_1(Qcomplete,FIX((SI_Long)416L),Qcomplete,Qnil,Qnil,
	    Qnil,Qnil);
    Qline = STATIC_SYMBOL("LINE",AB_package);
    define_key_symbol_1(Qline,FIX((SI_Long)394L),Qline,Qnil,Qnil,Qnil,Qnil);
    Qscroll = STATIC_SYMBOL("SCROLL",AB_package);
    define_key_symbol_1(Qscroll,FIX((SI_Long)666L),Qscroll,Qnil,Qnil,Qnil,
	    Qnil);
    Qsystem = STATIC_SYMBOL("SYSTEM",AB_package);
    define_key_symbol_1(Qsystem,FIX((SI_Long)413L),Qsystem,Qnil,Qnil,Qnil,
	    Qnil);
    Qstatus = STATIC_SYMBOL("STATUS",AB_package);
    define_key_symbol_1(Qstatus,FIX((SI_Long)403L),Qstatus,Qnil,Qnil,Qnil,
	    Qnil);
    Qterm = STATIC_SYMBOL("TERM",AB_package);
    define_key_symbol_1(Qterm,FIX((SI_Long)388L),Qterm,Qnil,Qnil,Qnil,Qnil);
    Qundo = STATIC_SYMBOL("UNDO",AB_package);
    define_key_symbol_1(Qundo,FIX((SI_Long)415L),Qundo,Qnil,Qnil,Qnil,Qnil);
    define_key_symbol_1(Qleft,FIX((SI_Long)409L),Qleft,Qnil,Qnil,Qnil,Qnil);
    define_key_symbol_1(Qmiddle,FIX((SI_Long)410L),Qmiddle,Qnil,Qnil,Qnil,
	    Qnil);
    define_key_symbol_1(Qright,FIX((SI_Long)411L),Qright,Qnil,Qnil,Qnil,Qnil);
}
