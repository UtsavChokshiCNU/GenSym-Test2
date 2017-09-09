/* trnscd.c
 * Input file:  transcode.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "trnscd.h"


Object G2int_the_type_description_of_transcode_text_conversion_style = UNBOUND;

Object G2int_chain_of_available_transcode_text_conversion_styles = UNBOUND;

Object G2int_transcode_text_conversion_style_count = UNBOUND;

/* RECLAIM-TRANSCODE-TEXT-CONVERSION-STYLE-1 */
Object g2int_reclaim_transcode_text_conversion_style_1(transcode_text_conversion_style)
    Object transcode_text_conversion_style;
{
    Object svref_new_value;

    x_note_fn_call(26,0);
    inline_note_reclaim_cons(transcode_text_conversion_style,Nil);
    svref_new_value = 
	    G2int_chain_of_available_transcode_text_conversion_styles;
    SVREF(transcode_text_conversion_style,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_transcode_text_conversion_styles = 
	    transcode_text_conversion_style;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TRANSCODE-TEXT-CONVERSION-STYLE */
Object g2int_reclaim_structure_for_transcode_text_conversion_style(transcode_text_conversion_style)
    Object transcode_text_conversion_style;
{
    x_note_fn_call(26,1);
    return g2int_reclaim_transcode_text_conversion_style_1(transcode_text_conversion_style);
}

static Object Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct;  /* g2-defstruct-structure-name::transcode-text-conversion-style-g2-struct */

/* MAKE-PERMANENT-TRANSCODE-TEXT-CONVERSION-STYLE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_transcode_text_conversion_style_structure_internal()
{
    Object def_structure_transcode_text_conversion_style_variable;
    Object transcode_text_conversion_style_count_new_value;
    Object defstruct_g2_transcode_text_conversion_style_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,2);
    def_structure_transcode_text_conversion_style_variable = Nil;
    transcode_text_conversion_style_count_new_value = 
	    FIXNUM_ADD1(G2int_transcode_text_conversion_style_count);
    G2int_transcode_text_conversion_style_count = 
	    transcode_text_conversion_style_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_transcode_text_conversion_style_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_transcode_text_conversion_style_variable = the_array;
	SVREF(defstruct_g2_transcode_text_conversion_style_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct;
	def_structure_transcode_text_conversion_style_variable = 
		defstruct_g2_transcode_text_conversion_style_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_transcode_text_conversion_style_variable);
}

static Object Qg2int_per_platform;  /* per-platform */

static Object Qg2int_wide_string;  /* wide-string */

/* MAKE-TRANSCODE-TEXT-CONVERSION-STYLE-1 */
Object g2int_make_transcode_text_conversion_style_1()
{
    Object def_structure_transcode_text_conversion_style_variable;

    x_note_fn_call(26,3);
    def_structure_transcode_text_conversion_style_variable = 
	    G2int_chain_of_available_transcode_text_conversion_styles;
    if (def_structure_transcode_text_conversion_style_variable) {
	G2int_chain_of_available_transcode_text_conversion_styles = 
		ISVREF(def_structure_transcode_text_conversion_style_variable,
		(SI_Long)0L);
	SVREF(def_structure_transcode_text_conversion_style_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct;
    }
    else
	def_structure_transcode_text_conversion_style_variable = 
		g2int_make_permanent_transcode_text_conversion_style_structure_internal();
    inline_note_allocate_cons(def_structure_transcode_text_conversion_style_variable,
	    Nil);
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)4L)) = Qg2int_per_platform;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)6L)) = Qg2int_wide_string;
    return VALUES_1(def_structure_transcode_text_conversion_style_variable);
}

Object G2int_text_conversion_style_for_purpose_prop = UNBOUND;

/* CREATE-TRANSCODE-TEXT-CONVERSION-STYLE */
Object g2int_create_transcode_text_conversion_style(parent_style_qm,
	    conversion_style_name,external_character_set,
	    unconvertible_character_spec,
	    unicode_line_separator_export_translation,han_unification_mode,
	    string_type_for_export)
    Object parent_style_qm, conversion_style_name, external_character_set;
    Object unconvertible_character_spec;
    Object unicode_line_separator_export_translation, han_unification_mode;
    Object string_type_for_export;
{
    Object style, svref_new_value;

    x_note_fn_call(26,4);
    style = g2int_make_transcode_text_conversion_style_1();
    if (parent_style_qm) {
	svref_new_value = ISVREF(parent_style_qm,(SI_Long)1L);
	SVREF(style,FIX((SI_Long)1L)) = svref_new_value;
	svref_new_value = ISVREF(parent_style_qm,(SI_Long)2L);
	SVREF(style,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = ISVREF(parent_style_qm,(SI_Long)3L);
	SVREF(style,FIX((SI_Long)3L)) = svref_new_value;
	svref_new_value = ISVREF(parent_style_qm,(SI_Long)4L);
	SVREF(style,FIX((SI_Long)4L)) = svref_new_value;
	svref_new_value = ISVREF(parent_style_qm,(SI_Long)5L);
	SVREF(style,FIX((SI_Long)5L)) = svref_new_value;
	svref_new_value = ISVREF(parent_style_qm,(SI_Long)6L);
	SVREF(style,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (conversion_style_name)
	SVREF(style,FIX((SI_Long)1L)) = conversion_style_name;
    if (external_character_set)
	SVREF(style,FIX((SI_Long)2L)) = external_character_set;
    if (unconvertible_character_spec)
	SVREF(style,FIX((SI_Long)3L)) = unconvertible_character_spec;
    if (unicode_line_separator_export_translation)
	SVREF(style,FIX((SI_Long)4L)) = 
		unicode_line_separator_export_translation;
    if (han_unification_mode)
	SVREF(style,FIX((SI_Long)5L)) = han_unification_mode;
    if (string_type_for_export)
	SVREF(style,FIX((SI_Long)6L)) = string_type_for_export;
    return VALUES_1(style);
}

static Object Qg2int_text_conversion_style_for_purpose;  /* text-conversion-style-for-purpose */

/* INSTALL-TEXT-TRANSCODE-PURPOSE */
Object g2int_install_text_transcode_purpose(purpose,parent_purpose,
	    conversion_style_name,external_character_set,
	    unconvertible_character_spec,
	    unicode_line_separator_export_translation,han_unification_mode,
	    string_type_for_export)
    Object purpose, parent_purpose, conversion_style_name;
    Object external_character_set, unconvertible_character_spec;
    Object unicode_line_separator_export_translation, han_unification_mode;
    Object string_type_for_export;
{
    Object style;

    x_note_fn_call(26,5);
    style = g2int_create_transcode_text_conversion_style(parent_purpose ? 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(parent_purpose),
	    Qg2int_text_conversion_style_for_purpose) : Nil,
	    conversion_style_name,external_character_set,
	    unconvertible_character_spec,
	    unicode_line_separator_export_translation,han_unification_mode,
	    string_type_for_export);
    g2int_mutate_global_property(purpose,style,
	    Qg2int_text_conversion_style_for_purpose);
    return VALUES_1(purpose);
}

Object G2int_default_text_conversion_style = UNBOUND;

Object G2int_utf_g_ascii_as_much_as_possible_conversion_style = UNBOUND;

/* TWRITE-SPACES-FOR-TABS */
Object g2int_twrite_spaces_for_tabs(spaces_for_tabs_qm)
    Object spaces_for_tabs_qm;
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long ab_loop_repeat_, simple_or_wide_character, thing;

    x_note_fn_call(26,6);
    ab_loop_repeat_ = spaces_for_tabs_qm ? (FIXNUMP(spaces_for_tabs_qm) ? 
	    IFIX(spaces_for_tabs_qm) : (SI_Long)1L) : (SI_Long)1L;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    simple_or_wide_character = spaces_for_tabs_qm ? (SI_Long)32L : (SI_Long)9L;
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = simple_or_wide_character;
	g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

Object G2int_the_type_description_of_text_sequence = UNBOUND;

Object G2int_chain_of_available_text_sequences = UNBOUND;

Object G2int_text_sequence_count = UNBOUND;

/* RECLAIM-TEXT-SEQUENCE-INTERNAL-1 */
Object g2int_reclaim_text_sequence_internal_1(text_sequence)
    Object text_sequence;
{
    Object svref_new_value;

    x_note_fn_call(26,7);
    inline_note_reclaim_cons(text_sequence,Nil);
    svref_new_value = G2int_chain_of_available_text_sequences;
    SVREF(text_sequence,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_text_sequences = text_sequence;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TEXT-SEQUENCE */
Object g2int_reclaim_structure_for_text_sequence(text_sequence)
    Object text_sequence;
{
    x_note_fn_call(26,8);
    return g2int_reclaim_text_sequence_internal_1(text_sequence);
}

static Object Qg2_defstruct_structure_name_text_sequence_g2_struct;  /* g2-defstruct-structure-name::text-sequence-g2-struct */

/* MAKE-PERMANENT-TEXT-SEQUENCE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_text_sequence_structure_internal()
{
    Object def_structure_text_sequence_variable, text_sequence_count_new_value;
    Object defstruct_g2_text_sequence_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,9);
    def_structure_text_sequence_variable = Nil;
    text_sequence_count_new_value = FIXNUM_ADD1(G2int_text_sequence_count);
    G2int_text_sequence_count = text_sequence_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_text_sequence_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_text_sequence_variable = the_array;
	SVREF(defstruct_g2_text_sequence_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_sequence_g2_struct;
	def_structure_text_sequence_variable = 
		defstruct_g2_text_sequence_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_text_sequence_variable);
}

/* MAKE-TEXT-SEQUENCE-INTERNAL-1 */
Object g2int_make_text_sequence_internal_1()
{
    Object def_structure_text_sequence_variable;

    x_note_fn_call(26,10);
    def_structure_text_sequence_variable = 
	    G2int_chain_of_available_text_sequences;
    if (def_structure_text_sequence_variable) {
	G2int_chain_of_available_text_sequences = 
		ISVREF(def_structure_text_sequence_variable,(SI_Long)0L);
	SVREF(def_structure_text_sequence_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_sequence_g2_struct;
    }
    else
	def_structure_text_sequence_variable = 
		g2int_make_permanent_text_sequence_structure_internal();
    inline_note_allocate_cons(def_structure_text_sequence_variable,Nil);
    ISVREF(def_structure_text_sequence_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_text_sequence_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_text_sequence_variable);
}

Object G2int_the_type_description_of_gensym_string_text_sequence = UNBOUND;

Object G2int_chain_of_available_gensym_string_text_sequences = UNBOUND;

Object G2int_gensym_string_text_sequence_count = UNBOUND;

/* RECLAIM-GENSYM-STRING-TEXT-SEQUENCE-1 */
Object g2int_reclaim_gensym_string_text_sequence_1(gensym_string_text_sequence)
    Object gensym_string_text_sequence;
{
    Object svref_new_value;

    x_note_fn_call(26,11);
    inline_note_reclaim_cons(gensym_string_text_sequence,Nil);
    svref_new_value = G2int_chain_of_available_gensym_string_text_sequences;
    SVREF(gensym_string_text_sequence,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gensym_string_text_sequences = 
	    gensym_string_text_sequence;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GENSYM-STRING-TEXT-SEQUENCE */
Object g2int_reclaim_structure_for_gensym_string_text_sequence(gensym_string_text_sequence)
    Object gensym_string_text_sequence;
{
    x_note_fn_call(26,12);
    return g2int_reclaim_gensym_string_text_sequence_1(gensym_string_text_sequence);
}

static Object Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct;  /* g2-defstruct-structure-name::gensym-string-text-sequence-g2-struct */

/* MAKE-PERMANENT-GENSYM-STRING-TEXT-SEQUENCE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gensym_string_text_sequence_structure_internal()
{
    Object def_structure_gensym_string_text_sequence_variable, temp;
    Object defstruct_g2_gensym_string_text_sequence_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,13);
    def_structure_gensym_string_text_sequence_variable = Nil;
    temp = FIXNUM_ADD1(G2int_gensym_string_text_sequence_count);
    G2int_gensym_string_text_sequence_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_gensym_string_text_sequence_variable = Nil;
	gensymed_symbol_1 = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_gensym_string_text_sequence_variable = the_array;
	SVREF(defstruct_g2_gensym_string_text_sequence_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct;
	SVREF(defstruct_g2_gensym_string_text_sequence_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_gensym_string_text_sequence_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_gensym_string_text_sequence_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_gensym_string_text_sequence_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_gensym_string_text_sequence_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_gensym_string_text_sequence_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_gensym_string_text_sequence_variable,
		FIX((SI_Long)7L)) = Nil;
	def_structure_gensym_string_text_sequence_variable = 
		defstruct_g2_gensym_string_text_sequence_variable;
	SVREF(def_structure_gensym_string_text_sequence_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_gensym_string_text_sequence_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(def_structure_gensym_string_text_sequence_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(def_structure_gensym_string_text_sequence_variable,
		FIX((SI_Long)7L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_gensym_string_text_sequences;
	SVREF(def_structure_gensym_string_text_sequence_variable,
		FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_gensym_string_text_sequences = 
		def_structure_gensym_string_text_sequence_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gensym_string_text_sequence_variable);
}

static Object Qg2int_gensym_string;  /* gensym-string */

/* MAKE-GENSYM-STRING-TEXT-SEQUENCE-1 */
Object g2int_make_gensym_string_text_sequence_1()
{
    Object def_structure_gensym_string_text_sequence_variable;

    x_note_fn_call(26,14);
    def_structure_gensym_string_text_sequence_variable = 
	    G2int_chain_of_available_gensym_string_text_sequences;
    if (def_structure_gensym_string_text_sequence_variable) {
	G2int_chain_of_available_gensym_string_text_sequences = 
		ISVREF(def_structure_gensym_string_text_sequence_variable,
		(SI_Long)0L);
	SVREF(def_structure_gensym_string_text_sequence_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct;
    }
    else
	def_structure_gensym_string_text_sequence_variable = 
		g2int_make_permanent_gensym_string_text_sequence_structure_internal();
    inline_note_allocate_cons(def_structure_gensym_string_text_sequence_variable,
	    Nil);
    ISVREF(def_structure_gensym_string_text_sequence_variable,(SI_Long)2L) 
	    = FIX((SI_Long)0L);
    SVREF(def_structure_gensym_string_text_sequence_variable,
	    FIX((SI_Long)4L)) = Qg2int_gensym_string;
    SVREF(def_structure_gensym_string_text_sequence_variable,
	    FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_gensym_string_text_sequence_variable);
}

Object G2int_the_type_description_of_wide_string_text_sequence = UNBOUND;

Object G2int_chain_of_available_wide_string_text_sequences = UNBOUND;

Object G2int_wide_string_text_sequence_count = UNBOUND;

/* RECLAIM-WIDE-STRING-TEXT-SEQUENCE-1 */
Object g2int_reclaim_wide_string_text_sequence_1(wide_string_text_sequence)
    Object wide_string_text_sequence;
{
    Object svref_new_value;

    x_note_fn_call(26,15);
    inline_note_reclaim_cons(wide_string_text_sequence,Nil);
    svref_new_value = G2int_chain_of_available_wide_string_text_sequences;
    SVREF(wide_string_text_sequence,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_wide_string_text_sequences = 
	    wide_string_text_sequence;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WIDE-STRING-TEXT-SEQUENCE */
Object g2int_reclaim_structure_for_wide_string_text_sequence(wide_string_text_sequence)
    Object wide_string_text_sequence;
{
    x_note_fn_call(26,16);
    return g2int_reclaim_wide_string_text_sequence_1(wide_string_text_sequence);
}

static Object Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct;  /* g2-defstruct-structure-name::wide-string-text-sequence-g2-struct */

/* MAKE-PERMANENT-WIDE-STRING-TEXT-SEQUENCE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_wide_string_text_sequence_structure_internal()
{
    Object def_structure_wide_string_text_sequence_variable, temp;
    Object defstruct_g2_wide_string_text_sequence_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,17);
    def_structure_wide_string_text_sequence_variable = Nil;
    temp = FIXNUM_ADD1(G2int_wide_string_text_sequence_count);
    G2int_wide_string_text_sequence_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_wide_string_text_sequence_variable = Nil;
	gensymed_symbol_1 = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_wide_string_text_sequence_variable = the_array;
	SVREF(defstruct_g2_wide_string_text_sequence_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct;
	SVREF(defstruct_g2_wide_string_text_sequence_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_wide_string_text_sequence_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_wide_string_text_sequence_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_wide_string_text_sequence_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_wide_string_text_sequence_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_wide_string_text_sequence_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_wide_string_text_sequence_variable,
		FIX((SI_Long)7L)) = Nil;
	def_structure_wide_string_text_sequence_variable = 
		defstruct_g2_wide_string_text_sequence_variable;
	SVREF(def_structure_wide_string_text_sequence_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_wide_string_text_sequence_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(def_structure_wide_string_text_sequence_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(def_structure_wide_string_text_sequence_variable,
		FIX((SI_Long)7L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_wide_string_text_sequences;
	SVREF(def_structure_wide_string_text_sequence_variable,
		FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_wide_string_text_sequences = 
		def_structure_wide_string_text_sequence_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_wide_string_text_sequence_variable);
}

/* MAKE-WIDE-STRING-TEXT-SEQUENCE-1 */
Object g2int_make_wide_string_text_sequence_1()
{
    Object def_structure_wide_string_text_sequence_variable;

    x_note_fn_call(26,18);
    def_structure_wide_string_text_sequence_variable = 
	    G2int_chain_of_available_wide_string_text_sequences;
    if (def_structure_wide_string_text_sequence_variable) {
	G2int_chain_of_available_wide_string_text_sequences = 
		ISVREF(def_structure_wide_string_text_sequence_variable,
		(SI_Long)0L);
	SVREF(def_structure_wide_string_text_sequence_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct;
    }
    else
	def_structure_wide_string_text_sequence_variable = 
		g2int_make_permanent_wide_string_text_sequence_structure_internal();
    inline_note_allocate_cons(def_structure_wide_string_text_sequence_variable,
	    Nil);
    ISVREF(def_structure_wide_string_text_sequence_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_wide_string_text_sequence_variable,
	    FIX((SI_Long)4L)) = Qg2int_wide_string;
    SVREF(def_structure_wide_string_text_sequence_variable,
	    FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_wide_string_text_sequence_variable);
}

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* INITIALIZE-TEXT-SEQUENCE-STRING-FUNCTION */
Object g2int_initialize_text_sequence_string_function(text_sequence,
	    string_1,start_qm,end_qm)
    Object text_sequence, string_1, start_qm, end_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(26,19);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)10L);
    gensymed_symbol_1 = text_sequence;
    gensymed_symbol_2 = string_1;
    gensymed_symbol_3 = start_qm;
    gensymed_symbol_4 = end_qm;
    return VALUES_1(inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4));
}

/* INITIALIZE-TEXT-SEQUENCE-STRING-FOR-TEXT-SEQUENCE */
Object g2int_initialize_text_sequence_string_for_text_sequence(text_sequence,
	    string_1,start_qm,end_qm)
    Object text_sequence, string_1, start_qm, end_qm;
{
    Object svref_new_value;

    x_note_fn_call(26,20);
    SVREF(text_sequence,FIX((SI_Long)1L)) = string_1;
    svref_new_value = start_qm;
    if (svref_new_value);
    else
	svref_new_value = FIX((SI_Long)0L);
    SVREF(text_sequence,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = ISVREF(text_sequence,(SI_Long)2L);
    return VALUES_1(SVREF(text_sequence,FIX((SI_Long)6L)) = svref_new_value);
}

/* INITIALIZE-TEXT-SEQUENCE-STRING-FOR-GENSYM-STRING-TEXT-SEQUENCE */
Object g2int_initialize_text_sequence_string_for_gensym_string_text_sequence(gensym_string_text_sequence,
	    string_1,start_qm,end_qm)
    Object gensym_string_text_sequence, string_1, start_qm, end_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, svref_new_value;
    char simple_p;

    x_note_fn_call(26,21);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(G2int_the_type_description_of_gensym_string_text_sequence,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)10L);
    gensymed_symbol_1 = gensym_string_text_sequence;
    gensymed_symbol_2 = string_1;
    gensymed_symbol_3 = start_qm;
    gensymed_symbol_4 = end_qm;
    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3,gensymed_symbol_4);
    simple_p =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    SVREF(gensym_string_text_sequence,FIX((SI_Long)5L)) = simple_p ? T : Nil;
    svref_new_value = end_qm;
    if (svref_new_value);
    else
	svref_new_value = simple_p ? SIMPLE_ARRAY_ANY_1_LENGTH(string_1) : 
		length(string_1);
    return VALUES_1(SVREF(gensym_string_text_sequence,FIX((SI_Long)3L)) = 
	    svref_new_value);
}

/* INITIALIZE-TEXT-SEQUENCE-STRING-FOR-WIDE-STRING-TEXT-SEQUENCE */
Object g2int_initialize_text_sequence_string_for_wide_string_text_sequence(wide_string_text_sequence,
	    string_1,start_qm,end_qm)
    Object wide_string_text_sequence, string_1, start_qm, end_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, svref_new_value;
    SI_Long length_1;

    x_note_fn_call(26,22);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(G2int_the_type_description_of_wide_string_text_sequence,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)10L);
    gensymed_symbol_1 = wide_string_text_sequence;
    gensymed_symbol_2 = string_1;
    gensymed_symbol_3 = start_qm;
    gensymed_symbol_4 = end_qm;
    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3,gensymed_symbol_4);
    svref_new_value = end_qm;
    if (svref_new_value);
    else {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	svref_new_value = FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
    }
    SVREF(wide_string_text_sequence,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* READ-CHARACTER-FROM-TEXT-SEQUENCE-FUNCTION */
Object g2int_read_character_from_text_sequence_function(text_sequence)
    Object text_sequence;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,23);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)11L);
    gensymed_symbol_1 = text_sequence;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* READ-CHARACTER-FROM-TEXT-SEQUENCE-FOR-GENSYM-STRING-TEXT-SEQUENCE */
Object g2int_read_character_from_text_sequence_for_gensym_string_text_sequence(gensym_string_text_sequence)
    Object gensym_string_text_sequence;
{
    Object text_sequence, svref_new_value, gensym_string, index_1;
    Object string_is_simple_qm;
    char temp;

    x_note_fn_call(26,24);
    text_sequence = gensym_string_text_sequence;
    svref_new_value = ISVREF(text_sequence,(SI_Long)6L);
    SVREF(text_sequence,FIX((SI_Long)7L)) = svref_new_value;
    gensym_string = ISVREF(text_sequence,(SI_Long)1L);
    index_1 = ISVREF(text_sequence,(SI_Long)6L);
    string_is_simple_qm = ISVREF(text_sequence,(SI_Long)5L);
    temp = string_is_simple_qm ? CHARACTER_TO_CHAR(SCHAR(gensym_string,
	    index_1)) : CHARACTER_TO_CHAR(CHAR(gensym_string,index_1));
    svref_new_value = FIXNUM_ADD1(ISVREF(text_sequence,(SI_Long)6L));
    SVREF(text_sequence,FIX((SI_Long)6L)) = svref_new_value;
    return VALUES_1(CHAR_CODE(CHAR_TO_CHARACTER(temp)));
}

/* READ-CHARACTER-FROM-TEXT-SEQUENCE-FOR-WIDE-STRING-TEXT-SEQUENCE */
Object g2int_read_character_from_text_sequence_for_wide_string_text_sequence(wide_string_text_sequence)
    Object wide_string_text_sequence;
{
    Object text_sequence, svref_new_value, temp;

    x_note_fn_call(26,25);
    text_sequence = wide_string_text_sequence;
    svref_new_value = ISVREF(text_sequence,(SI_Long)6L);
    SVREF(text_sequence,FIX((SI_Long)7L)) = svref_new_value;
    temp = FIX(UBYTE_16_ISAREF_1(ISVREF(text_sequence,(SI_Long)1L),
	    IFIX(ISVREF(text_sequence,(SI_Long)6L))));
    svref_new_value = FIXNUM_ADD1(ISVREF(text_sequence,(SI_Long)6L));
    SVREF(text_sequence,FIX((SI_Long)6L)) = svref_new_value;
    return VALUES_1(temp);
}

/* MAKE-TEXT-SEQUENCE */
Object g2int_make_text_sequence(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    Object text_sequence, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(26,26);
    text_sequence = STRINGP(string_1) ? 
	    g2int_make_gensym_string_text_sequence_1() : 
	    g2int_make_wide_string_text_sequence_1();
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)10L);
    gensymed_symbol_1 = text_sequence;
    gensymed_symbol_2 = string_1;
    gensymed_symbol_3 = start_qm;
    gensymed_symbol_4 = end_qm;
    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3,gensymed_symbol_4);
    return VALUES_1(text_sequence);
}

Object G2int_the_type_description_of_transcoder = UNBOUND;

Object G2int_chain_of_available_transcoders = UNBOUND;

Object G2int_transcoder_count = UNBOUND;

/* RECLAIM-TRANSCODER-1 */
Object g2int_reclaim_transcoder_1(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,27);
    inline_note_reclaim_cons(transcoder,Nil);
    svref_new_value = G2int_chain_of_available_transcoders;
    SVREF(transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_transcoders = transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TRANSCODER */
Object g2int_reclaim_structure_for_transcoder(transcoder)
    Object transcoder;
{
    x_note_fn_call(26,28);
    return g2int_reclaim_transcoder_1(transcoder);
}

static Object Qg2_defstruct_structure_name_transcoder_g2_struct;  /* g2-defstruct-structure-name::transcoder-g2-struct */

/* MAKE-PERMANENT-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_transcoder_structure_internal()
{
    Object def_structure_transcoder_variable, transcoder_count_new_value;
    Object defstruct_g2_transcoder_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,29);
    def_structure_transcoder_variable = Nil;
    transcoder_count_new_value = FIXNUM_ADD1(G2int_transcoder_count);
    G2int_transcoder_count = transcoder_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_transcoder_variable = Nil;
	gensymed_symbol = (SI_Long)6L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_transcoder_variable = the_array;
	SVREF(defstruct_g2_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_transcoder_g2_struct;
	def_structure_transcoder_variable = defstruct_g2_transcoder_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_transcoder_variable);
}

/* MAKE-TRANSCODER-1 */
Object g2int_make_transcoder_1()
{
    Object def_structure_transcoder_variable;

    x_note_fn_call(26,30);
    def_structure_transcoder_variable = G2int_chain_of_available_transcoders;
    if (def_structure_transcoder_variable) {
	G2int_chain_of_available_transcoders = 
		ISVREF(def_structure_transcoder_variable,(SI_Long)0L);
	SVREF(def_structure_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_transcoder_g2_struct;
    }
    else
	def_structure_transcoder_variable = 
		g2int_make_permanent_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_transcoder_variable,Nil);
    ISVREF(def_structure_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_transcoder_variable);
}

/* GET-TRANSCODER-CHARACTER */
Object g2int_get_transcoder_character(transcoder)
    Object transcoder;
{
    Object text_sequence, svref_new_value, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,31);
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    svref_new_value = ISVREF(transcoder,(SI_Long)2L);
    SVREF(transcoder,FIX((SI_Long)3L)) = svref_new_value;
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)11L);
    gensymed_symbol_1 = text_sequence;
    svref_new_value = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(SVREF(transcoder,FIX((SI_Long)2L)) = svref_new_value);
}

/* GET-TRANSCODER-CHARACTER-IF-ANY */
Object g2int_get_transcoder_character_if_any(transcoder)
    Object transcoder;
{
    Object text_sequence, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object temp;

    x_note_fn_call(26,32);
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    if (FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L))) {
	svref_new_value = ISVREF(transcoder,(SI_Long)2L);
	SVREF(transcoder,FIX((SI_Long)3L)) = svref_new_value;
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	SVREF(transcoder,FIX((SI_Long)2L)) = temp;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TRANSCODE-CHARACTER-FUNCTION */
Object g2int_transcode_character_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,33);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)12L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* EXPORT-CHARACTER-FUNCTION */
Object g2int_export_character_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,34);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)15L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* TRANSCODE-CHARACTER-FOR-TRANSCODER */
Object g2int_transcode_character_for_transcoder(transcoder)
    Object transcoder;
{
    x_note_fn_call(26,35);
    return g2int_get_transcoder_character(transcoder);
}

/* EXPORT-CHARACTER-FOR-TRANSCODER */
Object g2int_export_character_for_transcoder(transcoder)
    Object transcoder;
{
    x_note_fn_call(26,36);
    return g2int_get_transcoder_character(transcoder);
}

/* TRANSCODE-AS-TEXT-STRING-FUNCTION */
Object g2int_transcode_as_text_string_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,37);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)14L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* TWRITE-UNICODE-FROM-TRANSCODER-FUNCTION */
Object g2int_twrite_unicode_from_transcoder_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,38);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)13L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* EXPORT-AS-STRING-FUNCTION */
Object g2int_export_as_string_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,39);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)16L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* TWRITE-FOR-EXPORT-FROM-TRANSCODER-FUNCTION */
Object g2int_twrite_for_export_from_transcoder_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,40);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)17L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object Qg2int_do_not_use;   /* do-not-use */

/* TRANSCODE-AS-TEXT-STRING-FOR-TRANSCODER */
Object g2int_transcode_as_text_string_for_transcoder(transcoder)
    Object transcoder;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, gensymed_symbol_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,41);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
	      gensymed_symbol = 
		      ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		      Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		      (SI_Long)9L),(SI_Long)13L);
	      gensymed_symbol_1 = transcoder;
	      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qg2int_gensym;       /* gensym */

/* TWRITE-UNICODE-FROM-TRANSCODER-FOR-TRANSCODER */
Object g2int_twrite_unicode_from_transcoder_for_transcoder(transcoder)
    Object transcoder;
{
    Object text_sequence, gensymed_symbol, gensymed_symbol_1, temp;
    Object schar_arg_2, schar_new_value, character_1, gensym_pop_store, cons_1;
    Object next_cons, thing_1;
    SI_Long translated_character, thing;

    x_note_fn_call(26,42);
    translated_character = (SI_Long)65535L;
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
  next_loop:
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	goto end_loop;
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)12L);
    gensymed_symbol_1 = transcoder;
    translated_character = IFIX(inline_funcall_1(gensymed_symbol,
	    gensymed_symbol_1));
    if ( !(translated_character == (SI_Long)65535L)) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = translated_character;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = translated_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
	if (ISVREF(transcoder,(SI_Long)5L)) {
	    character_1 = Nil;
	  next_loop_1:
	    gensym_pop_store = Nil;
	    cons_1 = ISVREF(transcoder,(SI_Long)5L);
	    if (cons_1) {
		gensym_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(cons_1) = temp;
		G2int_available_gensym_conses = cons_1;
	    }
	    else
		next_cons = Nil;
	    SVREF(transcoder,FIX((SI_Long)5L)) = next_cons;
	    character_1 = gensym_pop_store;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = character_1;
		g2int_twrite_wide_character(CHARACTERP(thing_1) ? 
			CHAR_CODE(thing_1) : thing_1);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
			CHAR_CODE(thing_1) : thing_1);
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    if ( !TRUEP(ISVREF(transcoder,(SI_Long)5L)))
		goto end_loop_1;
	    goto next_loop_1;
	  end_loop_1:;
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* EXPORT-AS-STRING-FOR-TRANSCODER */
Object g2int_export_as_string_for_transcoder(transcoder)
    Object transcoder;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object gensymed_symbol, gensymed_symbol_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,43);
    if (EQ(ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)6L),
	    Qg2int_gensym_string)) {
	current_gensym_string = 
		g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
	PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
	  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		  2);
	    total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	    PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		    1);
	      current_twriting_output_type = Qg2int_gensym_string;
	      PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		      0);
		gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
		gensymed_symbol = 
			ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			Qg2int_type_description_of_unique_type_name_of_gensym_structure),
			(SI_Long)9L),(SI_Long)17L);
		gensymed_symbol_1 = transcoder;
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		result = g2int_copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else {
	current_wide_string_list = Qg2int_do_not_use;
	PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = 
		  g2int_allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  aref_arg_2 = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	  aref_arg_2 = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	  current_wide_string = wide_string_bv16;
	  PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		      (SI_Long)16L));
	      PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qg2int_wide_string;
		PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
			0);
		  gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
		  gensymed_symbol = 
			  ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qg2int_type_description_of_unique_type_name_of_gensym_structure),
			  (SI_Long)9L),(SI_Long)17L);
		  gensymed_symbol_1 = transcoder;
		  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		  result = g2int_copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

/* TWRITE-FOR-EXPORT-FROM-TRANSCODER-FOR-TRANSCODER */
Object g2int_twrite_for_export_from_transcoder_for_transcoder(transcoder)
    Object transcoder;
{
    Object text_sequence, gensymed_symbol, gensymed_symbol_1, temp;
    Object schar_arg_2, schar_new_value, gensym_pop_store, cons_1, next_cons;
    Object simple_or_wide_character, thing_1;
    SI_Long translated_character, thing;

    x_note_fn_call(26,44);
    translated_character = (SI_Long)65535L;
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
  next_loop:
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	goto end_loop;
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)15L);
    gensymed_symbol_1 = transcoder;
    translated_character = IFIX(inline_funcall_1(gensymed_symbol,
	    gensymed_symbol_1));
    if ( !(translated_character == (SI_Long)65535L)) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = translated_character;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = translated_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
    }
    if (ISVREF(transcoder,(SI_Long)5L)) {
      next_loop_1:
	gensym_pop_store = Nil;
	cons_1 = ISVREF(transcoder,(SI_Long)5L);
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(cons_1) = temp;
	    G2int_available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	SVREF(transcoder,FIX((SI_Long)5L)) = next_cons;
	simple_or_wide_character = gensym_pop_store;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = simple_or_wide_character;
	    g2int_twrite_wide_character(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
	if ( !TRUEP(ISVREF(transcoder,(SI_Long)5L)))
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TRANSCODE-UNHANDLED-CHARACTER */
Object g2int_transcode_unhandled_character(character_1,transcoder)
    Object character_1, transcoder;
{
    Object spec;

    x_note_fn_call(26,45);
    spec = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)3L);
    if (EQ(Qnil,spec))
	return VALUES_1(FIX((SI_Long)65535L));
    else if (FIXNUMP(spec))
	return VALUES_1(spec);
    else
	return VALUES_1(FIX((SI_Long)65535L));
}

Object G2int_the_type_description_of_graphic_character_set = UNBOUND;

Object G2int_chain_of_available_graphic_character_sets = UNBOUND;

Object G2int_graphic_character_set_count = UNBOUND;

/* RECLAIM-GRAPHIC-CHARACTER-SET-1 */
Object g2int_reclaim_graphic_character_set_1(graphic_character_set)
    Object graphic_character_set;
{
    Object svref_new_value;

    x_note_fn_call(26,46);
    inline_note_reclaim_cons(graphic_character_set,Nil);
    svref_new_value = G2int_chain_of_available_graphic_character_sets;
    SVREF(graphic_character_set,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_graphic_character_sets = graphic_character_set;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GRAPHIC-CHARACTER-SET */
Object g2int_reclaim_structure_for_graphic_character_set(graphic_character_set)
    Object graphic_character_set;
{
    x_note_fn_call(26,47);
    return g2int_reclaim_graphic_character_set_1(graphic_character_set);
}

static Object Qg2_defstruct_structure_name_graphic_character_set_g2_struct;  /* g2-defstruct-structure-name::graphic-character-set-g2-struct */

/* MAKE-PERMANENT-GRAPHIC-CHARACTER-SET-STRUCTURE-INTERNAL */
Object g2int_make_permanent_graphic_character_set_structure_internal()
{
    Object def_structure_graphic_character_set_variable;
    Object graphic_character_set_count_new_value;
    Object defstruct_g2_graphic_character_set_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,48);
    def_structure_graphic_character_set_variable = Nil;
    graphic_character_set_count_new_value = 
	    FIXNUM_ADD1(G2int_graphic_character_set_count);
    G2int_graphic_character_set_count = graphic_character_set_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_graphic_character_set_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_graphic_character_set_variable = the_array;
	SVREF(defstruct_g2_graphic_character_set_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graphic_character_set_g2_struct;
	def_structure_graphic_character_set_variable = 
		defstruct_g2_graphic_character_set_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_graphic_character_set_variable);
}

static Object Qg2int_iso_646;      /* iso-646 */

static Object list_constant;       /* # */

static Object array_constant;      /* # */

/* MAKE-GRAPHIC-CHARACTER-SET-1 */
Object g2int_make_graphic_character_set_1()
{
    Object def_structure_graphic_character_set_variable;

    x_note_fn_call(26,49);
    def_structure_graphic_character_set_variable = 
	    G2int_chain_of_available_graphic_character_sets;
    if (def_structure_graphic_character_set_variable) {
	G2int_chain_of_available_graphic_character_sets = 
		ISVREF(def_structure_graphic_character_set_variable,
		(SI_Long)0L);
	SVREF(def_structure_graphic_character_set_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graphic_character_set_g2_struct;
    }
    else
	def_structure_graphic_character_set_variable = 
		g2int_make_permanent_graphic_character_set_structure_internal();
    inline_note_allocate_cons(def_structure_graphic_character_set_variable,
	    Nil);
    SVREF(def_structure_graphic_character_set_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_646;
    SVREF(def_structure_graphic_character_set_variable,FIX((SI_Long)2L)) = 
	    list_constant;
    ISVREF(def_structure_graphic_character_set_variable,(SI_Long)3L) = 
	    FIX((SI_Long)1L);
    ISVREF(def_structure_graphic_character_set_variable,(SI_Long)4L) = 
	    FIX((SI_Long)94L);
    SVREF(def_structure_graphic_character_set_variable,FIX((SI_Long)5L)) = 
	    array_constant;
    SVREF(def_structure_graphic_character_set_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_graphic_character_set_variable);
}

Object G2int_graphic_character_set_prop = UNBOUND;

/* MAP-CODE-TO-UNICODE-FUNCTION */
Object g2int_map_code_to_unicode_function(graphic_character_set,code)
    Object graphic_character_set, code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(26,50);
    gensymed_symbol = ISVREF(graphic_character_set,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)18L);
    gensymed_symbol_1 = graphic_character_set;
    gensymed_symbol_2 = code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FUNCTION */
Object g2int_map_unicode_to_code_if_any_function(graphic_character_set,
	    unicode_wide_character)
    Object graphic_character_set, unicode_wide_character;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(26,51);
    gensymed_symbol = ISVREF(graphic_character_set,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)19L);
    gensymed_symbol_1 = graphic_character_set;
    gensymed_symbol_2 = unicode_wide_character;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

Object G2int_transcoder_creation_function_prop = UNBOUND;

Object G2int_the_type_description_of_iso_646 = UNBOUND;

Object G2int_chain_of_available_iso_646s = UNBOUND;

Object G2int_iso_646_count = UNBOUND;

/* RECLAIM-ISO-646-1 */
Object g2int_reclaim_iso_646_1(iso_646)
    Object iso_646;
{
    Object svref_new_value;

    x_note_fn_call(26,52);
    inline_note_reclaim_cons(iso_646,Nil);
    svref_new_value = G2int_chain_of_available_iso_646s;
    SVREF(iso_646,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_646s = iso_646;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-646 */
Object g2int_reclaim_structure_for_iso_646(iso_646)
    Object iso_646;
{
    x_note_fn_call(26,53);
    return g2int_reclaim_iso_646_1(iso_646);
}

static Object Qg2_defstruct_structure_name_iso_646_g2_struct;  /* g2-defstruct-structure-name::iso-646-g2-struct */

/* MAKE-PERMANENT-ISO-646-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_646_structure_internal()
{
    Object def_structure_iso_646_variable, iso_646_count_new_value;
    Object defstruct_g2_iso_646_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,54);
    def_structure_iso_646_variable = Nil;
    iso_646_count_new_value = FIXNUM_ADD1(G2int_iso_646_count);
    G2int_iso_646_count = iso_646_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_646_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_646_variable = the_array;
	SVREF(defstruct_g2_iso_646_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_646_g2_struct;
	SVREF(defstruct_g2_iso_646_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_646_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_646_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_646_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_646_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_646_variable,FIX((SI_Long)6L)) = Nil;
	def_structure_iso_646_variable = defstruct_g2_iso_646_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_646_variable);
}

static Object list_constant_1;     /* # */

static Object array_constant_1;    /* # */

/* MAKE-ISO-646-1 */
Object g2int_make_iso_646_1()
{
    Object def_structure_iso_646_variable;

    x_note_fn_call(26,55);
    def_structure_iso_646_variable = G2int_chain_of_available_iso_646s;
    if (def_structure_iso_646_variable) {
	G2int_chain_of_available_iso_646s = 
		ISVREF(def_structure_iso_646_variable,(SI_Long)0L);
	SVREF(def_structure_iso_646_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_646_g2_struct;
    }
    else
	def_structure_iso_646_variable = 
		g2int_make_permanent_iso_646_structure_internal();
    inline_note_allocate_cons(def_structure_iso_646_variable,Nil);
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)1L)) = Qg2int_iso_646;
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)2L)) = list_constant_1;
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)3L)) = FIX((SI_Long)1L);
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)4L)) = FIX((SI_Long)94L);
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)5L)) = array_constant_1;
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_iso_646_variable);
}

/* MAP-CODE-TO-UNICODE-FOR-ISO-646 */
Object g2int_map_code_to_unicode_for_iso_646(iso_646,code)
    Object iso_646, code;
{
    x_note_fn_call(26,56);
    return VALUES_1(code);
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-ISO-646 */
Object g2int_map_unicode_to_code_if_any_for_iso_646(iso_646,
	    unicode_wide_character)
    Object iso_646, unicode_wide_character;
{
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(26,57);
    arg = (SI_Long)32L;
    arg_1 = IFIX(unicode_wide_character);
    arg_2 = (SI_Long)127L;
    if (arg <= arg_1 && arg_1 <= arg_2)
	return VALUES_1(unicode_wide_character);
    else
	return VALUES_1(Nil);
}

Object G2int_the_type_description_of_iso_8859_abstract = UNBOUND;

Object G2int_chain_of_available_iso_8859_abstracts = UNBOUND;

Object G2int_iso_8859_abstract_count = UNBOUND;

/* RECLAIM-ISO-8859-ABSTRACT-1 */
Object g2int_reclaim_iso_8859_abstract_1(iso_8859_abstract)
    Object iso_8859_abstract;
{
    Object svref_new_value;

    x_note_fn_call(26,58);
    inline_note_reclaim_cons(iso_8859_abstract,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_abstracts;
    SVREF(iso_8859_abstract,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_abstracts = iso_8859_abstract;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-ABSTRACT */
Object g2int_reclaim_structure_for_iso_8859_abstract(iso_8859_abstract)
    Object iso_8859_abstract;
{
    x_note_fn_call(26,59);
    return g2int_reclaim_iso_8859_abstract_1(iso_8859_abstract);
}

static Object Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct;  /* g2-defstruct-structure-name::iso-8859-abstract-g2-struct */

/* MAKE-PERMANENT-ISO-8859-ABSTRACT-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_abstract_structure_internal()
{
    Object def_structure_iso_8859_abstract_variable;
    Object iso_8859_abstract_count_new_value;
    Object defstruct_g2_iso_8859_abstract_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,60);
    def_structure_iso_8859_abstract_variable = Nil;
    iso_8859_abstract_count_new_value = 
	    FIXNUM_ADD1(G2int_iso_8859_abstract_count);
    G2int_iso_8859_abstract_count = iso_8859_abstract_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_abstract_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_abstract_variable = the_array;
	SVREF(defstruct_g2_iso_8859_abstract_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct;
	SVREF(defstruct_g2_iso_8859_abstract_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_abstract_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_abstract_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_abstract_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_abstract_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_abstract_variable,FIX((SI_Long)6L)) = Nil;
	def_structure_iso_8859_abstract_variable = 
		defstruct_g2_iso_8859_abstract_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_abstract_variable);
}

static Object Qg2int_iso_8859_abstract;  /* iso-8859-abstract */

/* MAKE-ISO-8859-ABSTRACT-1 */
Object g2int_make_iso_8859_abstract_1()
{
    Object def_structure_iso_8859_abstract_variable;

    x_note_fn_call(26,61);
    def_structure_iso_8859_abstract_variable = 
	    G2int_chain_of_available_iso_8859_abstracts;
    if (def_structure_iso_8859_abstract_variable) {
	G2int_chain_of_available_iso_8859_abstracts = 
		ISVREF(def_structure_iso_8859_abstract_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct;
    }
    else
	def_structure_iso_8859_abstract_variable = 
		g2int_make_permanent_iso_8859_abstract_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_abstract_variable,Nil);
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_abstract;
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)2L)) = Qnil;
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)5L)) = Qnil;
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_abstract_variable);
}

/* MAP-CODE-TO-UNICODE-FOR-ISO-8859-ABSTRACT */
Object g2int_map_code_to_unicode_for_iso_8859_abstract(iso_8859_abstract,code)
    Object iso_8859_abstract, code;
{
    x_note_fn_call(26,62);
    return VALUES_1(FIX(UBYTE_16_ISAREF_1(ISVREF(iso_8859_abstract,
	    (SI_Long)8L),IFIX(code))));
}

Object G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors = UNBOUND;

Object G2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors = UNBOUND;

/* 8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object g2int_8859_reverse_unicode_map_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(26,63);
    temp = G2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,g2int_bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS */
Object g2int_out_8859_reverse_unicode_map_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(26,64);
    temp = 
	    FIXNUM_MINUS(G2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors,
	    length(G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTOR-INTERNAL */
Object g2int_make_permanent_8859_reverse_unicode_map_hash_vector_43_vector_internal()
{
    Object count_of_8859_reverse_unicode_map_hash_vector_43_vectors_new_value;
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(26,65);
    count_of_8859_reverse_unicode_map_hash_vector_43_vectors_new_value = 
	    FIXNUM_ADD1(G2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors);
    G2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors = 
	    count_of_8859_reverse_unicode_map_hash_vector_43_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

/* MAKE-8859-REVERSE-UNICODE-MAP-HASH-VECTOR */
Object g2int_make_8859_reverse_unicode_map_hash_vector()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(26,66);
    if (G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors) {
	temp = 
		M_CAR(G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors);
	temp_1 = 
		M_CDR(G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors);
	inline_note_reclaim_cons(G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors,
		Qg2int_gensym);
	cdr_arg = 
		G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors;
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	G2int_available_gensym_conses = 
		G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors;
	G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors = 
		temp_1;
    }
    else
	temp = 
		g2int_make_permanent_8859_reverse_unicode_map_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-8859-REVERSE-UNICODE-MAP-HASH-VECTOR */
Object g2int_reclaim_8859_reverse_unicode_map_hash_vector(n_8859_reverse_unicode_map_hash_vector_43_vector)
    Object n_8859_reverse_unicode_map_hash_vector_43_vector;
{
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(26,67);
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = n_8859_reverse_unicode_map_hash_vector_43_vector;
    cdr_new_value = 
	    G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors = 
	    gensymed_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-8859-REVERSE-UNICODE-MAP-TREE-FOR-HASH-LEAVES */
Object g2int_reclaim_8859_reverse_unicode_map_tree_for_hash_leaves(n_8859_reverse_unicode_map_tree_for_hash_binary_tree)
    Object n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, cdr_new_value, last_1, next_qm, temp;

    x_note_fn_call(26,68);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(n_8859_reverse_unicode_map_tree_for_hash_binary_tree))
	goto end_loop;
    less_than_branch_qm = 
	    ISVREF(n_8859_reverse_unicode_map_tree_for_hash_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = 
	    ISVREF(n_8859_reverse_unicode_map_tree_for_hash_binary_tree,
	    (SI_Long)2L);
    alist = ISVREF(n_8859_reverse_unicode_map_tree_for_hash_binary_tree,
	    (SI_Long)3L);
    g2int_reclaim_binary_tree_element_1(n_8859_reverse_unicode_map_tree_for_hash_binary_tree);
    alist_entry = Nil;
    ab_loop_list_ = alist;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    inline_note_reclaim_cons(alist_entry,Qg2int_gensym);
    cdr_new_value = G2int_available_gensym_conses;
    M_CDR(alist_entry) = cdr_new_value;
    G2int_available_gensym_conses = alist_entry;
    goto next_loop_1;
  end_loop_1:;
    if (alist) {
	last_1 = alist;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qg2int_gensym);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(last_1) = cdr_new_value;
	G2int_available_gensym_conses = alist;
    }
    if (less_than_branch_qm && greater_than_branch_qm) {
	g2int_reclaim_8859_reverse_unicode_map_tree_for_hash_leaves(less_than_branch_qm);
	n_8859_reverse_unicode_map_tree_for_hash_binary_tree = 
		greater_than_branch_qm;
    }
    else {
	temp = less_than_branch_qm;
	if (temp);
	else
	    temp = greater_than_branch_qm;
	n_8859_reverse_unicode_map_tree_for_hash_binary_tree = temp;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-8859-REVERSE-UNICODE-MAP-TREE */
Object g2int_clear_8859_reverse_unicode_map_tree(n_8859_reverse_unicode_map_tree_for_hash_binary_tree)
    Object n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(26,69);
    element_qm = CDR(n_8859_reverse_unicode_map_tree_for_hash_binary_tree);
    if (element_qm) {
	g2int_reclaim_8859_reverse_unicode_map_tree_for_hash_leaves(element_qm);
	M_CDR(n_8859_reverse_unicode_map_tree_for_hash_binary_tree) = Nil;
    }
    return VALUES_1(n_8859_reverse_unicode_map_tree_for_hash_binary_tree);
}

static Object Qg2int_8859_reverse_unicode_map_tree_for_hash;  /* 8859-reverse-unicode-map-tree-for-hash */

/* MAKE-8859-REVERSE-UNICODE-MAP */
Object g2int_make_8859_reverse_unicode_map()
{
    Object new_vector, new_cons, gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(26,70);
    new_vector = g2int_make_8859_reverse_unicode_map_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qg2int_8859_reverse_unicode_map_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* FLATTEN-8859-REVERSE-UNICODE-MAP */
Object g2int_flatten_8859_reverse_unicode_map(n_8859_reverse_unicode_map_hash_table)
    Object n_8859_reverse_unicode_map_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(26,71);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(n_8859_reverse_unicode_map_hash_table,index_1);
    if (subtree) {
	temp = g2int_flatten_binary_tree(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-8859-REVERSE-UNICODE-MAP */
Object g2int_clear_8859_reverse_unicode_map(n_8859_reverse_unicode_map_hash_table)
    Object n_8859_reverse_unicode_map_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(26,72);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    g2int_clear_8859_reverse_unicode_map_tree(ISVREF(n_8859_reverse_unicode_map_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-8859-REVERSE-UNICODE-MAP */
Object g2int_reclaim_8859_reverse_unicode_map(n_8859_reverse_unicode_map_hash_table)
    Object n_8859_reverse_unicode_map_hash_table;
{
    Object n_8859_reverse_unicode_map_tree_for_hash_binary_tree, element_qm;
    Object cdr_new_value, temp;
    SI_Long index_1;

    x_note_fn_call(26,73);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    n_8859_reverse_unicode_map_tree_for_hash_binary_tree = 
	    ISVREF(n_8859_reverse_unicode_map_hash_table,index_1);
    element_qm = M_CDR(n_8859_reverse_unicode_map_tree_for_hash_binary_tree);
    if (element_qm)
	g2int_reclaim_8859_reverse_unicode_map_tree_for_hash_leaves(element_qm);
    inline_note_reclaim_cons(n_8859_reverse_unicode_map_tree_for_hash_binary_tree,
	    Qg2int_gensym);
    cdr_new_value = G2int_available_gensym_conses;
    M_CDR(n_8859_reverse_unicode_map_tree_for_hash_binary_tree) = 
	    cdr_new_value;
    G2int_available_gensym_conses = 
	    n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
    ISVREF(n_8859_reverse_unicode_map_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    g2int_reclaim_8859_reverse_unicode_map_hash_vector(n_8859_reverse_unicode_map_hash_table);
    return VALUES_1(temp);
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-ISO-8859-ABSTRACT */
Object g2int_map_unicode_to_code_if_any_for_iso_8859_abstract(iso_8859_abstract,
	    unicode_wide_character)
    Object iso_8859_abstract, unicode_wide_character;
{
    Object temp, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(26,74);
    gensymed_symbol = IFIX(g2int_sxhashw(unicode_wide_character));
    temp = ISVREF(iso_8859_abstract,(SI_Long)9L);
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = SVREF(temp,FIX(temp_1));
    gensymed_symbol_1 = CDR(temp);
    gensymed_symbol_2 = unicode_wide_character;
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol_1))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
    if (gensymed_symbol < gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    else if (gensymed_symbol > gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    else {
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	if (EQ(gensymed_symbol_2,gensymed_symbol_4))
	    return VALUES_1(M_CDR(M_CAR(gensymed_symbol_1)));
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_the_type_description_of_iso_8859_1 = UNBOUND;

Object G2int_chain_of_available_iso_8859_1s = UNBOUND;

Object G2int_iso_8859_1_count = UNBOUND;

/* RECLAIM-ISO-8859-1-1 */
Object g2int_reclaim_iso_8859_1_1(iso_8859_1)
    Object iso_8859_1;
{
    Object svref_new_value;

    x_note_fn_call(26,75);
    inline_note_reclaim_cons(iso_8859_1,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_1s;
    SVREF(iso_8859_1,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_1s = iso_8859_1;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-1 */
Object g2int_reclaim_structure_for_iso_8859_1(iso_8859_1)
    Object iso_8859_1;
{
    x_note_fn_call(26,76);
    return g2int_reclaim_iso_8859_1_1(iso_8859_1);
}

static Object Qg2_defstruct_structure_name_iso_8859_1_g2_struct;  /* g2-defstruct-structure-name::iso-8859-1-g2-struct */

/* MAKE-PERMANENT-ISO-8859-1-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_1_structure_internal()
{
    Object def_structure_iso_8859_1_variable, iso_8859_1_count_new_value;
    Object defstruct_g2_iso_8859_1_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,77);
    def_structure_iso_8859_1_variable = Nil;
    iso_8859_1_count_new_value = FIXNUM_ADD1(G2int_iso_8859_1_count);
    G2int_iso_8859_1_count = iso_8859_1_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_1_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_1_variable = the_array;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_1_g2_struct;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_1_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_1_variable = defstruct_g2_iso_8859_1_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_1_variable);
}

static Object Qg2int_iso_8859_1;   /* iso-8859-1 */

static Object list_constant_2;     /* # */

/* MAKE-ISO-8859-1-1 */
Object g2int_make_iso_8859_1_1()
{
    Object def_structure_iso_8859_1_variable;

    x_note_fn_call(26,78);
    def_structure_iso_8859_1_variable = G2int_chain_of_available_iso_8859_1s;
    if (def_structure_iso_8859_1_variable) {
	G2int_chain_of_available_iso_8859_1s = 
		ISVREF(def_structure_iso_8859_1_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_1_g2_struct;
    }
    else
	def_structure_iso_8859_1_variable = 
		g2int_make_permanent_iso_8859_1_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_1_variable,Nil);
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_1;
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)2L)) = 
	    list_constant_2;
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)5L)) = array_constant;
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_1_variable,(SI_Long)7L) = FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_1_variable);
}

Object G2int_the_type_description_of_iso_8859_2 = UNBOUND;

Object G2int_chain_of_available_iso_8859_2s = UNBOUND;

Object G2int_iso_8859_2_count = UNBOUND;

/* RECLAIM-ISO-8859-2-1 */
Object g2int_reclaim_iso_8859_2_1(iso_8859_2)
    Object iso_8859_2;
{
    Object svref_new_value;

    x_note_fn_call(26,79);
    inline_note_reclaim_cons(iso_8859_2,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_2s;
    SVREF(iso_8859_2,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_2s = iso_8859_2;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-2 */
Object g2int_reclaim_structure_for_iso_8859_2(iso_8859_2)
    Object iso_8859_2;
{
    x_note_fn_call(26,80);
    return g2int_reclaim_iso_8859_2_1(iso_8859_2);
}

static Object Qg2_defstruct_structure_name_iso_8859_2_g2_struct;  /* g2-defstruct-structure-name::iso-8859-2-g2-struct */

/* MAKE-PERMANENT-ISO-8859-2-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_2_structure_internal()
{
    Object def_structure_iso_8859_2_variable, iso_8859_2_count_new_value;
    Object defstruct_g2_iso_8859_2_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,81);
    def_structure_iso_8859_2_variable = Nil;
    iso_8859_2_count_new_value = FIXNUM_ADD1(G2int_iso_8859_2_count);
    G2int_iso_8859_2_count = iso_8859_2_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_2_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_2_variable = the_array;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_2_g2_struct;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_2_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_2_variable = defstruct_g2_iso_8859_2_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_2_variable);
}

static Object Qg2int_iso_8859_2;   /* iso-8859-2 */

static Object list_constant_3;     /* # */

/* MAKE-ISO-8859-2-1 */
Object g2int_make_iso_8859_2_1()
{
    Object def_structure_iso_8859_2_variable;

    x_note_fn_call(26,82);
    def_structure_iso_8859_2_variable = G2int_chain_of_available_iso_8859_2s;
    if (def_structure_iso_8859_2_variable) {
	G2int_chain_of_available_iso_8859_2s = 
		ISVREF(def_structure_iso_8859_2_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_2_g2_struct;
    }
    else
	def_structure_iso_8859_2_variable = 
		g2int_make_permanent_iso_8859_2_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_2_variable,Nil);
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_2;
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)2L)) = 
	    list_constant_3;
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)5L)) = 
	    array_constant_1;
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_2_variable,(SI_Long)7L) = FIX((SI_Long)2L);
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_2_variable);
}

Object G2int_the_type_description_of_iso_8859_3 = UNBOUND;

Object G2int_chain_of_available_iso_8859_3s = UNBOUND;

Object G2int_iso_8859_3_count = UNBOUND;

/* RECLAIM-ISO-8859-3-1 */
Object g2int_reclaim_iso_8859_3_1(iso_8859_3)
    Object iso_8859_3;
{
    Object svref_new_value;

    x_note_fn_call(26,83);
    inline_note_reclaim_cons(iso_8859_3,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_3s;
    SVREF(iso_8859_3,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_3s = iso_8859_3;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-3 */
Object g2int_reclaim_structure_for_iso_8859_3(iso_8859_3)
    Object iso_8859_3;
{
    x_note_fn_call(26,84);
    return g2int_reclaim_iso_8859_3_1(iso_8859_3);
}

static Object Qg2_defstruct_structure_name_iso_8859_3_g2_struct;  /* g2-defstruct-structure-name::iso-8859-3-g2-struct */

/* MAKE-PERMANENT-ISO-8859-3-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_3_structure_internal()
{
    Object def_structure_iso_8859_3_variable, iso_8859_3_count_new_value;
    Object defstruct_g2_iso_8859_3_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,85);
    def_structure_iso_8859_3_variable = Nil;
    iso_8859_3_count_new_value = FIXNUM_ADD1(G2int_iso_8859_3_count);
    G2int_iso_8859_3_count = iso_8859_3_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_3_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_3_variable = the_array;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_3_g2_struct;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_3_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_3_variable = defstruct_g2_iso_8859_3_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_3_variable);
}

static Object Qg2int_iso_8859_3;   /* iso-8859-3 */

static Object list_constant_4;     /* # */

static Object array_constant_2;    /* # */

/* MAKE-ISO-8859-3-1 */
Object g2int_make_iso_8859_3_1()
{
    Object def_structure_iso_8859_3_variable;

    x_note_fn_call(26,86);
    def_structure_iso_8859_3_variable = G2int_chain_of_available_iso_8859_3s;
    if (def_structure_iso_8859_3_variable) {
	G2int_chain_of_available_iso_8859_3s = 
		ISVREF(def_structure_iso_8859_3_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_3_g2_struct;
    }
    else
	def_structure_iso_8859_3_variable = 
		g2int_make_permanent_iso_8859_3_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_3_variable,Nil);
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_3;
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)2L)) = 
	    list_constant_4;
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)5L)) = 
	    array_constant_2;
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_3_variable,(SI_Long)7L) = FIX((SI_Long)3L);
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_3_variable);
}

Object G2int_the_type_description_of_iso_8859_4 = UNBOUND;

Object G2int_chain_of_available_iso_8859_4s = UNBOUND;

Object G2int_iso_8859_4_count = UNBOUND;

/* RECLAIM-ISO-8859-4-1 */
Object g2int_reclaim_iso_8859_4_1(iso_8859_4)
    Object iso_8859_4;
{
    Object svref_new_value;

    x_note_fn_call(26,87);
    inline_note_reclaim_cons(iso_8859_4,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_4s;
    SVREF(iso_8859_4,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_4s = iso_8859_4;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-4 */
Object g2int_reclaim_structure_for_iso_8859_4(iso_8859_4)
    Object iso_8859_4;
{
    x_note_fn_call(26,88);
    return g2int_reclaim_iso_8859_4_1(iso_8859_4);
}

static Object Qg2_defstruct_structure_name_iso_8859_4_g2_struct;  /* g2-defstruct-structure-name::iso-8859-4-g2-struct */

/* MAKE-PERMANENT-ISO-8859-4-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_4_structure_internal()
{
    Object def_structure_iso_8859_4_variable, iso_8859_4_count_new_value;
    Object defstruct_g2_iso_8859_4_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,89);
    def_structure_iso_8859_4_variable = Nil;
    iso_8859_4_count_new_value = FIXNUM_ADD1(G2int_iso_8859_4_count);
    G2int_iso_8859_4_count = iso_8859_4_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_4_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_4_variable = the_array;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_4_g2_struct;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_4_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_4_variable = defstruct_g2_iso_8859_4_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_4_variable);
}

static Object Qg2int_iso_8859_4;   /* iso-8859-4 */

static Object list_constant_5;     /* # */

static Object array_constant_3;    /* # */

/* MAKE-ISO-8859-4-1 */
Object g2int_make_iso_8859_4_1()
{
    Object def_structure_iso_8859_4_variable;

    x_note_fn_call(26,90);
    def_structure_iso_8859_4_variable = G2int_chain_of_available_iso_8859_4s;
    if (def_structure_iso_8859_4_variable) {
	G2int_chain_of_available_iso_8859_4s = 
		ISVREF(def_structure_iso_8859_4_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_4_g2_struct;
    }
    else
	def_structure_iso_8859_4_variable = 
		g2int_make_permanent_iso_8859_4_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_4_variable,Nil);
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_4;
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)2L)) = 
	    list_constant_5;
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)5L)) = 
	    array_constant_3;
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_4_variable,(SI_Long)7L) = FIX((SI_Long)4L);
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_4_variable);
}

Object G2int_the_type_description_of_iso_8859_5 = UNBOUND;

Object G2int_chain_of_available_iso_8859_5s = UNBOUND;

Object G2int_iso_8859_5_count = UNBOUND;

/* RECLAIM-ISO-8859-5-1 */
Object g2int_reclaim_iso_8859_5_1(iso_8859_5)
    Object iso_8859_5;
{
    Object svref_new_value;

    x_note_fn_call(26,91);
    inline_note_reclaim_cons(iso_8859_5,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_5s;
    SVREF(iso_8859_5,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_5s = iso_8859_5;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-5 */
Object g2int_reclaim_structure_for_iso_8859_5(iso_8859_5)
    Object iso_8859_5;
{
    x_note_fn_call(26,92);
    return g2int_reclaim_iso_8859_5_1(iso_8859_5);
}

static Object Qg2_defstruct_structure_name_iso_8859_5_g2_struct;  /* g2-defstruct-structure-name::iso-8859-5-g2-struct */

/* MAKE-PERMANENT-ISO-8859-5-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_5_structure_internal()
{
    Object def_structure_iso_8859_5_variable, iso_8859_5_count_new_value;
    Object defstruct_g2_iso_8859_5_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,93);
    def_structure_iso_8859_5_variable = Nil;
    iso_8859_5_count_new_value = FIXNUM_ADD1(G2int_iso_8859_5_count);
    G2int_iso_8859_5_count = iso_8859_5_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_5_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_5_variable = the_array;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_5_g2_struct;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_5_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_5_variable = defstruct_g2_iso_8859_5_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_5_variable);
}

static Object Qg2int_iso_8859_5;   /* iso-8859-5 */

static Object list_constant_6;     /* # */

static Object array_constant_4;    /* # */

/* MAKE-ISO-8859-5-1 */
Object g2int_make_iso_8859_5_1()
{
    Object def_structure_iso_8859_5_variable;

    x_note_fn_call(26,94);
    def_structure_iso_8859_5_variable = G2int_chain_of_available_iso_8859_5s;
    if (def_structure_iso_8859_5_variable) {
	G2int_chain_of_available_iso_8859_5s = 
		ISVREF(def_structure_iso_8859_5_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_5_g2_struct;
    }
    else
	def_structure_iso_8859_5_variable = 
		g2int_make_permanent_iso_8859_5_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_5_variable,Nil);
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_5;
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)2L)) = 
	    list_constant_6;
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)5L)) = 
	    array_constant_4;
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_5_variable,(SI_Long)7L) = FIX((SI_Long)5L);
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_5_variable);
}

Object G2int_the_type_description_of_iso_8859_6 = UNBOUND;

Object G2int_chain_of_available_iso_8859_6s = UNBOUND;

Object G2int_iso_8859_6_count = UNBOUND;

/* RECLAIM-ISO-8859-6-1 */
Object g2int_reclaim_iso_8859_6_1(iso_8859_6)
    Object iso_8859_6;
{
    Object svref_new_value;

    x_note_fn_call(26,95);
    inline_note_reclaim_cons(iso_8859_6,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_6s;
    SVREF(iso_8859_6,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_6s = iso_8859_6;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-6 */
Object g2int_reclaim_structure_for_iso_8859_6(iso_8859_6)
    Object iso_8859_6;
{
    x_note_fn_call(26,96);
    return g2int_reclaim_iso_8859_6_1(iso_8859_6);
}

static Object Qg2_defstruct_structure_name_iso_8859_6_g2_struct;  /* g2-defstruct-structure-name::iso-8859-6-g2-struct */

/* MAKE-PERMANENT-ISO-8859-6-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_6_structure_internal()
{
    Object def_structure_iso_8859_6_variable, iso_8859_6_count_new_value;
    Object defstruct_g2_iso_8859_6_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,97);
    def_structure_iso_8859_6_variable = Nil;
    iso_8859_6_count_new_value = FIXNUM_ADD1(G2int_iso_8859_6_count);
    G2int_iso_8859_6_count = iso_8859_6_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_6_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_6_variable = the_array;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_6_g2_struct;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_6_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_6_variable = defstruct_g2_iso_8859_6_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_6_variable);
}

static Object Qg2int_iso_8859_6;   /* iso-8859-6 */

static Object list_constant_7;     /* # */

static Object array_constant_5;    /* # */

/* MAKE-ISO-8859-6-1 */
Object g2int_make_iso_8859_6_1()
{
    Object def_structure_iso_8859_6_variable;

    x_note_fn_call(26,98);
    def_structure_iso_8859_6_variable = G2int_chain_of_available_iso_8859_6s;
    if (def_structure_iso_8859_6_variable) {
	G2int_chain_of_available_iso_8859_6s = 
		ISVREF(def_structure_iso_8859_6_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_6_g2_struct;
    }
    else
	def_structure_iso_8859_6_variable = 
		g2int_make_permanent_iso_8859_6_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_6_variable,Nil);
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_6;
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)2L)) = 
	    list_constant_7;
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)5L)) = 
	    array_constant_5;
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_6_variable,(SI_Long)7L) = FIX((SI_Long)6L);
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_6_variable);
}

Object G2int_the_type_description_of_iso_8859_7 = UNBOUND;

Object G2int_chain_of_available_iso_8859_7s = UNBOUND;

Object G2int_iso_8859_7_count = UNBOUND;

/* RECLAIM-ISO-8859-7-1 */
Object g2int_reclaim_iso_8859_7_1(iso_8859_7)
    Object iso_8859_7;
{
    Object svref_new_value;

    x_note_fn_call(26,99);
    inline_note_reclaim_cons(iso_8859_7,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_7s;
    SVREF(iso_8859_7,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_7s = iso_8859_7;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-7 */
Object g2int_reclaim_structure_for_iso_8859_7(iso_8859_7)
    Object iso_8859_7;
{
    x_note_fn_call(26,100);
    return g2int_reclaim_iso_8859_7_1(iso_8859_7);
}

static Object Qg2_defstruct_structure_name_iso_8859_7_g2_struct;  /* g2-defstruct-structure-name::iso-8859-7-g2-struct */

/* MAKE-PERMANENT-ISO-8859-7-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_7_structure_internal()
{
    Object def_structure_iso_8859_7_variable, iso_8859_7_count_new_value;
    Object defstruct_g2_iso_8859_7_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,101);
    def_structure_iso_8859_7_variable = Nil;
    iso_8859_7_count_new_value = FIXNUM_ADD1(G2int_iso_8859_7_count);
    G2int_iso_8859_7_count = iso_8859_7_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_7_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_7_variable = the_array;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_7_g2_struct;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_7_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_7_variable = defstruct_g2_iso_8859_7_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_7_variable);
}

static Object Qg2int_iso_8859_7;   /* iso-8859-7 */

static Object list_constant_8;     /* # */

static Object array_constant_6;    /* # */

/* MAKE-ISO-8859-7-1 */
Object g2int_make_iso_8859_7_1()
{
    Object def_structure_iso_8859_7_variable;

    x_note_fn_call(26,102);
    def_structure_iso_8859_7_variable = G2int_chain_of_available_iso_8859_7s;
    if (def_structure_iso_8859_7_variable) {
	G2int_chain_of_available_iso_8859_7s = 
		ISVREF(def_structure_iso_8859_7_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_7_g2_struct;
    }
    else
	def_structure_iso_8859_7_variable = 
		g2int_make_permanent_iso_8859_7_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_7_variable,Nil);
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_7;
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)2L)) = 
	    list_constant_8;
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)5L)) = 
	    array_constant_6;
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_7_variable,(SI_Long)7L) = FIX((SI_Long)7L);
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_7_variable);
}

Object G2int_the_type_description_of_iso_8859_8 = UNBOUND;

Object G2int_chain_of_available_iso_8859_8s = UNBOUND;

Object G2int_iso_8859_8_count = UNBOUND;

/* RECLAIM-ISO-8859-8-1 */
Object g2int_reclaim_iso_8859_8_1(iso_8859_8)
    Object iso_8859_8;
{
    Object svref_new_value;

    x_note_fn_call(26,103);
    inline_note_reclaim_cons(iso_8859_8,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_8s;
    SVREF(iso_8859_8,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_8s = iso_8859_8;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-8 */
Object g2int_reclaim_structure_for_iso_8859_8(iso_8859_8)
    Object iso_8859_8;
{
    x_note_fn_call(26,104);
    return g2int_reclaim_iso_8859_8_1(iso_8859_8);
}

static Object Qg2_defstruct_structure_name_iso_8859_8_g2_struct;  /* g2-defstruct-structure-name::iso-8859-8-g2-struct */

/* MAKE-PERMANENT-ISO-8859-8-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_8_structure_internal()
{
    Object def_structure_iso_8859_8_variable, iso_8859_8_count_new_value;
    Object defstruct_g2_iso_8859_8_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,105);
    def_structure_iso_8859_8_variable = Nil;
    iso_8859_8_count_new_value = FIXNUM_ADD1(G2int_iso_8859_8_count);
    G2int_iso_8859_8_count = iso_8859_8_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_8_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_8_variable = the_array;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_8_g2_struct;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_8_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_8_variable = defstruct_g2_iso_8859_8_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_8_variable);
}

static Object Qg2int_iso_8859_8;   /* iso-8859-8 */

static Object list_constant_9;     /* # */

static Object array_constant_7;    /* # */

/* MAKE-ISO-8859-8-1 */
Object g2int_make_iso_8859_8_1()
{
    Object def_structure_iso_8859_8_variable;

    x_note_fn_call(26,106);
    def_structure_iso_8859_8_variable = G2int_chain_of_available_iso_8859_8s;
    if (def_structure_iso_8859_8_variable) {
	G2int_chain_of_available_iso_8859_8s = 
		ISVREF(def_structure_iso_8859_8_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_8_g2_struct;
    }
    else
	def_structure_iso_8859_8_variable = 
		g2int_make_permanent_iso_8859_8_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_8_variable,Nil);
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_8;
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)2L)) = 
	    list_constant_9;
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)5L)) = 
	    array_constant_7;
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_8_variable,(SI_Long)7L) = FIX((SI_Long)8L);
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_8_variable);
}

Object G2int_the_type_description_of_iso_8859_9 = UNBOUND;

Object G2int_chain_of_available_iso_8859_9s = UNBOUND;

Object G2int_iso_8859_9_count = UNBOUND;

/* RECLAIM-ISO-8859-9-1 */
Object g2int_reclaim_iso_8859_9_1(iso_8859_9)
    Object iso_8859_9;
{
    Object svref_new_value;

    x_note_fn_call(26,107);
    inline_note_reclaim_cons(iso_8859_9,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_9s;
    SVREF(iso_8859_9,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_9s = iso_8859_9;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-9 */
Object g2int_reclaim_structure_for_iso_8859_9(iso_8859_9)
    Object iso_8859_9;
{
    x_note_fn_call(26,108);
    return g2int_reclaim_iso_8859_9_1(iso_8859_9);
}

static Object Qg2_defstruct_structure_name_iso_8859_9_g2_struct;  /* g2-defstruct-structure-name::iso-8859-9-g2-struct */

/* MAKE-PERMANENT-ISO-8859-9-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_9_structure_internal()
{
    Object def_structure_iso_8859_9_variable, iso_8859_9_count_new_value;
    Object defstruct_g2_iso_8859_9_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,109);
    def_structure_iso_8859_9_variable = Nil;
    iso_8859_9_count_new_value = FIXNUM_ADD1(G2int_iso_8859_9_count);
    G2int_iso_8859_9_count = iso_8859_9_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_9_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_9_variable = the_array;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_9_g2_struct;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_9_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_9_variable = defstruct_g2_iso_8859_9_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_9_variable);
}

static Object Qg2int_iso_8859_9;   /* iso-8859-9 */

static Object list_constant_10;    /* # */

static Object array_constant_8;    /* # */

/* MAKE-ISO-8859-9-1 */
Object g2int_make_iso_8859_9_1()
{
    Object def_structure_iso_8859_9_variable;

    x_note_fn_call(26,110);
    def_structure_iso_8859_9_variable = G2int_chain_of_available_iso_8859_9s;
    if (def_structure_iso_8859_9_variable) {
	G2int_chain_of_available_iso_8859_9s = 
		ISVREF(def_structure_iso_8859_9_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_9_g2_struct;
    }
    else
	def_structure_iso_8859_9_variable = 
		g2int_make_permanent_iso_8859_9_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_9_variable,Nil);
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_9;
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)2L)) = 
	    list_constant_10;
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)5L)) = 
	    array_constant_8;
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_9_variable,(SI_Long)7L) = FIX((SI_Long)9L);
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_9_variable);
}

Object G2int_the_type_description_of_iso_8859_10 = UNBOUND;

Object G2int_chain_of_available_iso_8859_10s = UNBOUND;

Object G2int_iso_8859_10_count = UNBOUND;

/* RECLAIM-ISO-8859-10-1 */
Object g2int_reclaim_iso_8859_10_1(iso_8859_10)
    Object iso_8859_10;
{
    Object svref_new_value;

    x_note_fn_call(26,111);
    inline_note_reclaim_cons(iso_8859_10,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_10s;
    SVREF(iso_8859_10,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_10s = iso_8859_10;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-10 */
Object g2int_reclaim_structure_for_iso_8859_10(iso_8859_10)
    Object iso_8859_10;
{
    x_note_fn_call(26,112);
    return g2int_reclaim_iso_8859_10_1(iso_8859_10);
}

static Object Qg2_defstruct_structure_name_iso_8859_10_g2_struct;  /* g2-defstruct-structure-name::iso-8859-10-g2-struct */

/* MAKE-PERMANENT-ISO-8859-10-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_10_structure_internal()
{
    Object def_structure_iso_8859_10_variable, iso_8859_10_count_new_value;
    Object defstruct_g2_iso_8859_10_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,113);
    def_structure_iso_8859_10_variable = Nil;
    iso_8859_10_count_new_value = FIXNUM_ADD1(G2int_iso_8859_10_count);
    G2int_iso_8859_10_count = iso_8859_10_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_iso_8859_10_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_iso_8859_10_variable = the_array;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_10_g2_struct;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_iso_8859_10_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_iso_8859_10_variable = defstruct_g2_iso_8859_10_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_10_variable);
}

static Object Qg2int_iso_8859_10;  /* iso-8859-10 */

static Object list_constant_11;    /* # */

/* MAKE-ISO-8859-10-1 */
Object g2int_make_iso_8859_10_1()
{
    Object def_structure_iso_8859_10_variable;

    x_note_fn_call(26,114);
    def_structure_iso_8859_10_variable = G2int_chain_of_available_iso_8859_10s;
    if (def_structure_iso_8859_10_variable) {
	G2int_chain_of_available_iso_8859_10s = 
		ISVREF(def_structure_iso_8859_10_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_10_g2_struct;
    }
    else
	def_structure_iso_8859_10_variable = 
		g2int_make_permanent_iso_8859_10_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_10_variable,Nil);
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)1L)) = 
	    Qg2int_iso_8859_10;
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)2L)) = 
	    list_constant_11;
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)96L);
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)5L)) = 
	    array_constant_3;
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_iso_8859_10_variable,(SI_Long)7L) = FIX((SI_Long)10L);
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_iso_8859_10_variable);
}

Object G2int_the_type_description_of_asian_double_byte = UNBOUND;

Object G2int_chain_of_available_asian_double_bytes = UNBOUND;

Object G2int_asian_double_byte_count = UNBOUND;

/* RECLAIM-ASIAN-DOUBLE-BYTE-1 */
Object g2int_reclaim_asian_double_byte_1(asian_double_byte)
    Object asian_double_byte;
{
    Object svref_new_value;

    x_note_fn_call(26,115);
    inline_note_reclaim_cons(asian_double_byte,Nil);
    svref_new_value = G2int_chain_of_available_asian_double_bytes;
    SVREF(asian_double_byte,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_asian_double_bytes = asian_double_byte;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ASIAN-DOUBLE-BYTE */
Object g2int_reclaim_structure_for_asian_double_byte(asian_double_byte)
    Object asian_double_byte;
{
    x_note_fn_call(26,116);
    return g2int_reclaim_asian_double_byte_1(asian_double_byte);
}

static Object Qg2_defstruct_structure_name_asian_double_byte_g2_struct;  /* g2-defstruct-structure-name::asian-double-byte-g2-struct */

/* MAKE-PERMANENT-ASIAN-DOUBLE-BYTE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_asian_double_byte_structure_internal()
{
    Object def_structure_asian_double_byte_variable;
    Object asian_double_byte_count_new_value;
    Object defstruct_g2_asian_double_byte_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,117);
    def_structure_asian_double_byte_variable = Nil;
    asian_double_byte_count_new_value = 
	    FIXNUM_ADD1(G2int_asian_double_byte_count);
    G2int_asian_double_byte_count = asian_double_byte_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_asian_double_byte_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_asian_double_byte_variable = the_array;
	SVREF(defstruct_g2_asian_double_byte_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_asian_double_byte_g2_struct;
	SVREF(defstruct_g2_asian_double_byte_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_asian_double_byte_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_asian_double_byte_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_asian_double_byte_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_asian_double_byte_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_asian_double_byte_variable,FIX((SI_Long)6L)) = Nil;
	def_structure_asian_double_byte_variable = 
		defstruct_g2_asian_double_byte_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_asian_double_byte_variable);
}

static Object Qg2int_asian_double_byte;  /* asian-double-byte */

/* MAKE-ASIAN-DOUBLE-BYTE-1 */
Object g2int_make_asian_double_byte_1()
{
    Object def_structure_asian_double_byte_variable;

    x_note_fn_call(26,118);
    def_structure_asian_double_byte_variable = 
	    G2int_chain_of_available_asian_double_bytes;
    if (def_structure_asian_double_byte_variable) {
	G2int_chain_of_available_asian_double_bytes = 
		ISVREF(def_structure_asian_double_byte_variable,(SI_Long)0L);
	SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_asian_double_byte_g2_struct;
    }
    else
	def_structure_asian_double_byte_variable = 
		g2int_make_permanent_asian_double_byte_structure_internal();
    inline_note_allocate_cons(def_structure_asian_double_byte_variable,Nil);
    SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)1L)) = 
	    Qg2int_asian_double_byte;
    SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)2L)) = Qnil;
    SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)2L);
    SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)94L);
    SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)5L)) = Qnil;
    SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_asian_double_byte_variable);
}

/* MAP-CODE-TO-UNICODE-FOR-ASIAN-DOUBLE-BYTE */
Object g2int_map_code_to_unicode_for_asian_double_byte(asian_double_byte,code)
    Object asian_double_byte, code;
{
    Object row_map_qm;
    SI_Long row, column;

    x_note_fn_call(26,119);
    row = (IFIX(code) >>  -  - (SI_Long)8L & (SI_Long)127L) - (SI_Long)32L;
    column = (IFIX(code) & (SI_Long)127L) - (SI_Long)32L;
    row_map_qm = ISVREF(ISVREF(asian_double_byte,(SI_Long)7L),row);
    if (row_map_qm)
	return VALUES_1(FIX(UBYTE_16_ISAREF_1(row_map_qm,column)));
    else
	return VALUES_1(Nil);
}

Object G2int_the_type_description_of_jis_x_0208 = UNBOUND;

Object G2int_chain_of_available_jis_x_0208s = UNBOUND;

Object G2int_jis_x_0208_count = UNBOUND;

/* RECLAIM-JIS-X-0208-1 */
Object g2int_reclaim_jis_x_0208_1(jis_x_0208)
    Object jis_x_0208;
{
    Object svref_new_value;

    x_note_fn_call(26,120);
    inline_note_reclaim_cons(jis_x_0208,Nil);
    svref_new_value = G2int_chain_of_available_jis_x_0208s;
    SVREF(jis_x_0208,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_jis_x_0208s = jis_x_0208;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JIS-X-0208 */
Object g2int_reclaim_structure_for_jis_x_0208(jis_x_0208)
    Object jis_x_0208;
{
    x_note_fn_call(26,121);
    return g2int_reclaim_jis_x_0208_1(jis_x_0208);
}

static Object Qg2_defstruct_structure_name_jis_x_0208_g2_struct;  /* g2-defstruct-structure-name::jis-x-0208-g2-struct */

/* MAKE-PERMANENT-JIS-X-0208-STRUCTURE-INTERNAL */
Object g2int_make_permanent_jis_x_0208_structure_internal()
{
    Object def_structure_jis_x_0208_variable, jis_x_0208_count_new_value;
    Object defstruct_g2_jis_x_0208_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,122);
    def_structure_jis_x_0208_variable = Nil;
    jis_x_0208_count_new_value = FIXNUM_ADD1(G2int_jis_x_0208_count);
    G2int_jis_x_0208_count = jis_x_0208_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_jis_x_0208_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_jis_x_0208_variable = the_array;
	SVREF(defstruct_g2_jis_x_0208_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_jis_x_0208_g2_struct;
	SVREF(defstruct_g2_jis_x_0208_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_jis_x_0208_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_jis_x_0208_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_jis_x_0208_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_jis_x_0208_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_jis_x_0208_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_jis_x_0208_variable,FIX((SI_Long)7L)) = Nil;
	def_structure_jis_x_0208_variable = defstruct_g2_jis_x_0208_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_jis_x_0208_variable);
}

static Object Qg2int_jis_x_0208;   /* jis-x-0208 */

static Object list_constant_12;    /* # */

/* MAKE-JIS-X-0208-1 */
Object g2int_make_jis_x_0208_1()
{
    Object def_structure_jis_x_0208_variable;

    x_note_fn_call(26,123);
    def_structure_jis_x_0208_variable = G2int_chain_of_available_jis_x_0208s;
    if (def_structure_jis_x_0208_variable) {
	G2int_chain_of_available_jis_x_0208s = 
		ISVREF(def_structure_jis_x_0208_variable,(SI_Long)0L);
	SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_jis_x_0208_g2_struct;
    }
    else
	def_structure_jis_x_0208_variable = 
		g2int_make_permanent_jis_x_0208_structure_internal();
    inline_note_allocate_cons(def_structure_jis_x_0208_variable,Nil);
    SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)1L)) = 
	    Qg2int_jis_x_0208;
    SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)2L)) = 
	    list_constant_12;
    SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)2L);
    SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)94L);
    SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)5L)) = 
	    array_constant_1;
    SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_jis_x_0208_variable);
}

/* MAP-CODE-TO-UNICODE-FOR-JIS-X-0208 */
Object g2int_map_code_to_unicode_for_jis_x_0208(jis_x_0208,code)
    Object jis_x_0208, code;
{
    Object contiguous_code_qm, temp;

    x_note_fn_call(26,124);
    contiguous_code_qm = g2int_gensym_jis_code_to_contiguous(code);
    temp = contiguous_code_qm ? 
	    FIX(UBYTE_16_ISAREF_1(G2int_jis_x_0208_to_unicode_map,
	    IFIX(contiguous_code_qm))) : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)65535L));
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-JIS-X-0208 */
Object g2int_map_unicode_to_code_if_any_for_jis_x_0208(jis_x_0208,
	    unicode_wide_character)
    Object jis_x_0208, unicode_wide_character;
{
    Object unicode, cjk_code, cjk_code_mapping_vector, l;
    SI_Long temp;

    x_note_fn_call(26,125);
    unicode = unicode_wide_character;
    cjk_code = unicode;
    cjk_code_mapping_vector = G2int_unicode_to_jis_x_0208_map;
    temp = IFIX(cjk_code) % (SI_Long)307L;
    l = ISVREF(cjk_code_mapping_vector,temp);
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    if (FIXNUM_EQ(CAR(l),cjk_code))
	return VALUES_1(CADR(l));
    l = CDDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_the_type_description_of_ks_c_5601 = UNBOUND;

Object G2int_chain_of_available_ks_c_5601s = UNBOUND;

Object G2int_ks_c_5601_count = UNBOUND;

/* RECLAIM-KS-C-5601-1 */
Object g2int_reclaim_ks_c_5601_1(ks_c_5601)
    Object ks_c_5601;
{
    Object svref_new_value;

    x_note_fn_call(26,126);
    inline_note_reclaim_cons(ks_c_5601,Nil);
    svref_new_value = G2int_chain_of_available_ks_c_5601s;
    SVREF(ks_c_5601,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_ks_c_5601s = ks_c_5601;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-KS-C-5601 */
Object g2int_reclaim_structure_for_ks_c_5601(ks_c_5601)
    Object ks_c_5601;
{
    x_note_fn_call(26,127);
    return g2int_reclaim_ks_c_5601_1(ks_c_5601);
}

static Object Qg2_defstruct_structure_name_ks_c_5601_g2_struct;  /* g2-defstruct-structure-name::ks-c-5601-g2-struct */

/* MAKE-PERMANENT-KS-C-5601-STRUCTURE-INTERNAL */
Object g2int_make_permanent_ks_c_5601_structure_internal()
{
    Object def_structure_ks_c_5601_variable, ks_c_5601_count_new_value;
    Object defstruct_g2_ks_c_5601_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,128);
    def_structure_ks_c_5601_variable = Nil;
    ks_c_5601_count_new_value = FIXNUM_ADD1(G2int_ks_c_5601_count);
    G2int_ks_c_5601_count = ks_c_5601_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_ks_c_5601_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_ks_c_5601_variable = the_array;
	SVREF(defstruct_g2_ks_c_5601_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ks_c_5601_g2_struct;
	SVREF(defstruct_g2_ks_c_5601_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_ks_c_5601_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_ks_c_5601_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_ks_c_5601_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_ks_c_5601_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_ks_c_5601_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_ks_c_5601_variable,FIX((SI_Long)7L)) = Nil;
	def_structure_ks_c_5601_variable = defstruct_g2_ks_c_5601_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_ks_c_5601_variable);
}

static Object Qg2int_ks_c_5601;    /* ks-c-5601 */

static Object list_constant_13;    /* # */

/* MAKE-KS-C-5601-1 */
Object g2int_make_ks_c_5601_1()
{
    Object def_structure_ks_c_5601_variable;

    x_note_fn_call(26,129);
    def_structure_ks_c_5601_variable = G2int_chain_of_available_ks_c_5601s;
    if (def_structure_ks_c_5601_variable) {
	G2int_chain_of_available_ks_c_5601s = 
		ISVREF(def_structure_ks_c_5601_variable,(SI_Long)0L);
	SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ks_c_5601_g2_struct;
    }
    else
	def_structure_ks_c_5601_variable = 
		g2int_make_permanent_ks_c_5601_structure_internal();
    inline_note_allocate_cons(def_structure_ks_c_5601_variable,Nil);
    SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)1L)) = 
	    Qg2int_ks_c_5601;
    SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)2L)) = 
	    list_constant_13;
    SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)3L)) = 
	    FIX((SI_Long)2L);
    SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)4L)) = 
	    FIX((SI_Long)94L);
    SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)5L)) = 
	    array_constant_2;
    SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_ks_c_5601_variable);
}

/* MAP-CODE-TO-UNICODE-FOR-KS-C-5601 */
Object g2int_map_code_to_unicode_for_ks_c_5601(ks_c_5601,code)
    Object ks_c_5601, code;
{
    Object gensym_ks_c_5601, contiguous_code_qm, temp;

    x_note_fn_call(26,130);
    gensym_ks_c_5601 = g2int_ksc_to_gensym_ksc(code);
    contiguous_code_qm = g2int_gensym_ksc_code_to_contiguous(gensym_ks_c_5601);
    temp = contiguous_code_qm ? 
	    FIX(UBYTE_16_ISAREF_1(G2int_ks_c_5601_to_unicode_map,
	    IFIX(contiguous_code_qm))) : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)65535L));
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-KS-C-5601 */
Object g2int_map_unicode_to_code_if_any_for_ks_c_5601(ks_c_5601,
	    unicode_wide_character)
    Object ks_c_5601, unicode_wide_character;
{
    Object unicode, cjk_code, cjk_code_mapping_vector, l, gensym_ksc_code_qm;
    SI_Long temp;

    x_note_fn_call(26,131);
    unicode = unicode_wide_character;
    cjk_code = unicode;
    cjk_code_mapping_vector = G2int_unicode_to_ks_c_5601_map;
    temp = IFIX(cjk_code) % (SI_Long)307L;
    l = ISVREF(cjk_code_mapping_vector,temp);
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    if (FIXNUM_EQ(CAR(l),cjk_code)) {
	gensym_ksc_code_qm = CADR(l);
	goto end;
    }
    l = CDDR(l);
    goto next_loop;
  end_loop:
    gensym_ksc_code_qm = Qnil;
  end:;
    if (gensym_ksc_code_qm)
	return g2int_gensym_ksc_to_ksc(gensym_ksc_code_qm);
    else
	return VALUES_1(Nil);
}

Object G2int_the_type_description_of_gb_2312 = UNBOUND;

Object G2int_chain_of_available_gb_2312s = UNBOUND;

Object G2int_gb_2312_count = UNBOUND;

/* RECLAIM-GB-2312-1 */
Object g2int_reclaim_gb_2312_1(gb_2312)
    Object gb_2312;
{
    Object svref_new_value;

    x_note_fn_call(26,132);
    inline_note_reclaim_cons(gb_2312,Nil);
    svref_new_value = G2int_chain_of_available_gb_2312s;
    SVREF(gb_2312,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gb_2312s = gb_2312;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GB-2312 */
Object g2int_reclaim_structure_for_gb_2312(gb_2312)
    Object gb_2312;
{
    x_note_fn_call(26,133);
    return g2int_reclaim_gb_2312_1(gb_2312);
}

static Object Qg2_defstruct_structure_name_gb_2312_g2_struct;  /* g2-defstruct-structure-name::gb-2312-g2-struct */

/* MAKE-PERMANENT-GB-2312-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gb_2312_structure_internal()
{
    Object def_structure_gb_2312_variable, gb_2312_count_new_value;
    Object defstruct_g2_gb_2312_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,134);
    def_structure_gb_2312_variable = Nil;
    gb_2312_count_new_value = FIXNUM_ADD1(G2int_gb_2312_count);
    G2int_gb_2312_count = gb_2312_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gb_2312_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_gb_2312_variable = the_array;
	SVREF(defstruct_g2_gb_2312_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gb_2312_g2_struct;
	SVREF(defstruct_g2_gb_2312_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_gb_2312_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_gb_2312_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_gb_2312_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_gb_2312_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_gb_2312_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_gb_2312_variable,FIX((SI_Long)7L)) = Nil;
	def_structure_gb_2312_variable = defstruct_g2_gb_2312_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gb_2312_variable);
}

static Object Qg2int_gb_2312;      /* gb-2312 */

static Object list_constant_14;    /* # */

/* MAKE-GB-2312-1 */
Object g2int_make_gb_2312_1()
{
    Object def_structure_gb_2312_variable;

    x_note_fn_call(26,135);
    def_structure_gb_2312_variable = G2int_chain_of_available_gb_2312s;
    if (def_structure_gb_2312_variable) {
	G2int_chain_of_available_gb_2312s = 
		ISVREF(def_structure_gb_2312_variable,(SI_Long)0L);
	SVREF(def_structure_gb_2312_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gb_2312_g2_struct;
    }
    else
	def_structure_gb_2312_variable = 
		g2int_make_permanent_gb_2312_structure_internal();
    inline_note_allocate_cons(def_structure_gb_2312_variable,Nil);
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)1L)) = Qg2int_gb_2312;
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)2L)) = list_constant_14;
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)3L)) = FIX((SI_Long)2L);
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)4L)) = FIX((SI_Long)94L);
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)5L)) = array_constant_2;
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_gb_2312_variable);
}

/* MAP-CODE-TO-UNICODE-FOR-GB-2312 */
Object g2int_map_code_to_unicode_for_gb_2312(gb_2312,code)
    Object gb_2312, code;
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, index_1;
    SI_Long code_1;

    x_note_fn_call(26,136);
    gensymed_symbol = ((IFIX(code) >>  -  - (SI_Long)8L) - (SI_Long)33L) * 
	    (SI_Long)94L;
    gensymed_symbol_1 = (SI_Long)255L & IFIX(code);
    gensymed_symbol_2 = (SI_Long)33L;
    gensymed_symbol_2 = gensymed_symbol_1 - gensymed_symbol_2;
    index_1 = gensymed_symbol + gensymed_symbol_2;
    code_1 = (SI_Long)0L;
    if ((SI_Long)0L <= index_1 && index_1 <= (SI_Long)8177L) {
	code_1 = UBYTE_16_ISAREF_1(G2int_gb_2312_to_unicode_map,index_1);
	temp = code_1 == (SI_Long)65535L ? Nil : FIX(code_1);
    }
    else
	temp = Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)65535L));
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-GB-2312 */
Object g2int_map_unicode_to_code_if_any_for_gb_2312(gb_2312,
	    unicode_wide_character)
    Object gb_2312, unicode_wide_character;
{
    Object unicode, cjk_code, cjk_code_mapping_vector, vector_1;
    SI_Long temp, length_1, i, ab_loop_bind_, code;

    x_note_fn_call(26,137);
    unicode = unicode_wide_character;
    cjk_code = unicode;
    cjk_code_mapping_vector = G2int_unicode_to_gb_2312_map;
    temp = IFIX(cjk_code) % (SI_Long)307L;
    vector_1 = ISVREF(cjk_code_mapping_vector,temp);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1));
    i = (SI_Long)0L;
    ab_loop_bind_ = length_1;
    code = (SI_Long)0L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    code = UBYTE_16_ISAREF_1(vector_1,i);
    if (code == IFIX(cjk_code))
	return VALUES_1(FIX(UBYTE_16_ISAREF_1(vector_1,i + (SI_Long)1L)));
    if ( !(code < IFIX(cjk_code)))
	goto end_loop;
    i = i + (SI_Long)2L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_the_type_description_of_iso_8859_transcoder = UNBOUND;

Object G2int_chain_of_available_iso_8859_transcoders = UNBOUND;

Object G2int_iso_8859_transcoder_count = UNBOUND;

/* RECLAIM-ISO-8859-TRANSCODER-1 */
Object g2int_reclaim_iso_8859_transcoder_1(iso_8859_transcoder)
    Object iso_8859_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,138);
    inline_note_reclaim_cons(iso_8859_transcoder,Nil);
    svref_new_value = G2int_chain_of_available_iso_8859_transcoders;
    SVREF(iso_8859_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_8859_transcoders = iso_8859_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-TRANSCODER */
Object g2int_reclaim_structure_for_iso_8859_transcoder(iso_8859_transcoder)
    Object iso_8859_transcoder;
{
    x_note_fn_call(26,139);
    return g2int_reclaim_iso_8859_transcoder_1(iso_8859_transcoder);
}

static Object Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct;  /* g2-defstruct-structure-name::iso-8859-transcoder-g2-struct */

/* MAKE-PERMANENT-ISO-8859-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_8859_transcoder_structure_internal()
{
    Object def_structure_iso_8859_transcoder_variable, temp;
    Object defstruct_g2_iso_8859_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,140);
    def_structure_iso_8859_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_iso_8859_transcoder_count);
    G2int_iso_8859_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_iso_8859_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_iso_8859_transcoder_variable = the_array;
	SVREF(defstruct_g2_iso_8859_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct;
	SVREF(defstruct_g2_iso_8859_transcoder_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_iso_8859_transcoder_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_iso_8859_transcoder_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_iso_8859_transcoder_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_iso_8859_transcoder_variable,FIX((SI_Long)5L)) 
		= Nil;
	def_structure_iso_8859_transcoder_variable = 
		defstruct_g2_iso_8859_transcoder_variable;
	SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)4L)) 
		= Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_iso_8859_transcoders;
	SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)0L)) 
		= temp;
	G2int_chain_of_available_iso_8859_transcoders = 
		def_structure_iso_8859_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_transcoder_variable);
}

/* MAKE-ISO-8859-TRANSCODER-1 */
Object g2int_make_iso_8859_transcoder_1(iso_8859_part_number,
	    iso_8859_graphic_character_set)
    Object iso_8859_part_number, iso_8859_graphic_character_set;
{
    Object def_structure_iso_8859_transcoder_variable;

    x_note_fn_call(26,141);
    def_structure_iso_8859_transcoder_variable = 
	    G2int_chain_of_available_iso_8859_transcoders;
    if (def_structure_iso_8859_transcoder_variable) {
	G2int_chain_of_available_iso_8859_transcoders = 
		ISVREF(def_structure_iso_8859_transcoder_variable,(SI_Long)0L);
	SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct;
    }
    else
	def_structure_iso_8859_transcoder_variable = 
		g2int_make_permanent_iso_8859_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_transcoder_variable,Nil);
    SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)6L)) = 
	    iso_8859_part_number;
    SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)7L)) = 
	    iso_8859_graphic_character_set;
    ISVREF(def_structure_iso_8859_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_iso_8859_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_iso_8859_transcoder_variable);
}

/* TRANSCODE-CHARACTER-FOR-ISO-8859-TRANSCODER */
Object g2int_transcode_character_for_iso_8859_transcoder(iso_8859_transcoder)
    Object iso_8859_transcoder;
{
    Object transcoder, structure, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long character_1, arg, arg_1, arg_2, gensymed_symbol_2;

    x_note_fn_call(26,142);
    transcoder = iso_8859_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    if (character_1 < (SI_Long)32L) {
	if (character_1 == (SI_Long)10L && IFIX(ISVREF(transcoder,
		(SI_Long)3L)) == (SI_Long)13L)
	    return VALUES_1(FIX((SI_Long)65535L));
	else if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L)
	    return VALUES_1(FIX((SI_Long)8232L));
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 < (SI_Long)128L)
	return VALUES_1(FIX(character_1));
    else {
	arg = (SI_Long)160L;
	arg_1 = character_1;
	arg_2 = (SI_Long)255L;
	if (arg <= arg_1 && arg_1 <= arg_2) {
	    structure = ISVREF(transcoder,(SI_Long)7L);
	    gensymed_symbol = ISVREF(structure,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)18L);
	    gensymed_symbol_1 = structure;
	    gensymed_symbol_2 = character_1 - (SI_Long)128L;
	    temp = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    FIX(gensymed_symbol_2));
	    if (temp)
		return VALUES_1(temp);
	    else
		return g2int_transcode_unhandled_character(FIX(character_1),
			transcoder);
	}
	else
	    return g2int_transcode_unhandled_character(FIX(character_1),
		    transcoder);
    }
}

static Object Qg2int_dos;          /* dos */

static Object Qg2int_vms;          /* vms */

static Object Qg2int_win32;        /* win32 */

static Object Qg2int_unix;         /* unix */

static Object Qg2int_cr;           /* cr */

static Object Qg2int_lf;           /* lf */

static Object Qg2int_crlf;         /* crlf */

static Object Qg2int_unicode_line_separator;  /* unicode-line-separator */

static Object Qg2int_unicode_paragraph_separator;  /* unicode-paragraph-separator */

/* EXPORT-CHARACTER-FOR-ISO-8859-TRANSCODER */
Object g2int_export_character_for_iso_8859_transcoder(iso_8859_transcoder)
    Object iso_8859_transcoder;
{
    Object transcoder, temp, svref_new_value, structure, gensymed_symbol;
    Object gensymed_symbol_1, code_qm;
    SI_Long character_1, gensymed_symbol_2;

    x_note_fn_call(26,143);
    transcoder = iso_8859_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    if (character_1 < (SI_Long)32L || character_1 == (SI_Long)8232L || 
	    character_1 == (SI_Long)8233L) {
	if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	    temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	    if (EQ(temp,Qg2int_per_platform)) {
		if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
			EQ(G2int_g2_operating_system,Qg2int_vms) || 
			EQ(G2int_g2_operating_system,Qg2int_win32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp,Qg2int_cr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp,Qg2int_lf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp,Qg2int_crlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp,Qg2int_unicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp,Qg2int_unicode_paragraph_separator))
		return VALUES_1(FIX((SI_Long)8233L));
	    else
		return VALUES_1(FIX(character_1));
	}
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 < (SI_Long)160L)
	return VALUES_1(FIX(character_1));
    else {
	structure = ISVREF(transcoder,(SI_Long)7L);
	gensymed_symbol = ISVREF(structure,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)19L);
	gensymed_symbol_1 = structure;
	gensymed_symbol_2 = character_1;
	code_qm = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		FIX(gensymed_symbol_2));
	temp = code_qm ? FIX((SI_Long)128L + IFIX(code_qm)) : Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return g2int_transcode_unhandled_character(FIX(character_1),
		    transcoder);
    }
}

Object G2int_the_type_description_of_iso_2022_transcoder = UNBOUND;

Object G2int_chain_of_available_iso_2022_transcoders = UNBOUND;

Object G2int_iso_2022_transcoder_count = UNBOUND;

/* RECLAIM-ISO-2022-TRANSCODER-1 */
Object g2int_reclaim_iso_2022_transcoder_1(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,144);
    inline_note_reclaim_cons(iso_2022_transcoder,Nil);
    svref_new_value = G2int_chain_of_available_iso_2022_transcoders;
    SVREF(iso_2022_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_iso_2022_transcoders = iso_2022_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-2022-TRANSCODER */
Object g2int_reclaim_structure_for_iso_2022_transcoder(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    x_note_fn_call(26,145);
    return g2int_reclaim_iso_2022_transcoder_1(iso_2022_transcoder);
}

static Object Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct;  /* g2-defstruct-structure-name::iso-2022-transcoder-g2-struct */

/* MAKE-PERMANENT-ISO-2022-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_iso_2022_transcoder_structure_internal()
{
    Object def_structure_iso_2022_transcoder_variable, temp;
    Object defstruct_g2_iso_2022_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,146);
    def_structure_iso_2022_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_iso_2022_transcoder_count);
    G2int_iso_2022_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_iso_2022_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)14L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_iso_2022_transcoder_variable = the_array;
	SVREF(defstruct_g2_iso_2022_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct;
	SVREF(defstruct_g2_iso_2022_transcoder_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_iso_2022_transcoder_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_iso_2022_transcoder_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_iso_2022_transcoder_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_iso_2022_transcoder_variable,FIX((SI_Long)5L)) 
		= Nil;
	def_structure_iso_2022_transcoder_variable = 
		defstruct_g2_iso_2022_transcoder_variable;
	SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)4L)) 
		= Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_iso_2022_transcoders;
	SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)0L)) 
		= temp;
	G2int_chain_of_available_iso_2022_transcoders = 
		def_structure_iso_2022_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_2022_transcoder_variable);
}

static Object Qg2int_graphic_character_set;  /* graphic-character-set */

/* MAKE-ISO-2022-TRANSCODER-1 */
Object g2int_make_iso_2022_transcoder_1()
{
    Object def_structure_iso_2022_transcoder_variable, svref_new_value;

    x_note_fn_call(26,147);
    def_structure_iso_2022_transcoder_variable = 
	    G2int_chain_of_available_iso_2022_transcoders;
    if (def_structure_iso_2022_transcoder_variable) {
	G2int_chain_of_available_iso_2022_transcoders = 
		ISVREF(def_structure_iso_2022_transcoder_variable,(SI_Long)0L);
	SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct;
    }
    else
	def_structure_iso_2022_transcoder_variable = 
		g2int_make_permanent_iso_2022_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_iso_2022_transcoder_variable,Nil);
    ISVREF(def_structure_iso_2022_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_iso_2022_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)6L)) = T;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)7L)) = 
	    svref_new_value;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_1),
	    Qg2int_graphic_character_set);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)8L)) = 
	    svref_new_value;
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)10L)) = Nil;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)11L)) = 
	    svref_new_value;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_1),
	    Qg2int_graphic_character_set);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)12L)) = 
	    svref_new_value;
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(def_structure_iso_2022_transcoder_variable);
}

/* CREATE-TRANSCODER-FOR-ISO-646 */
Object g2int_create_transcoder_for_iso_646()
{
    Object tc;

    x_note_fn_call(26,148);
    tc = g2int_make_iso_2022_transcoder_1();
    g2int_set_up_iso_2022_transcoder_for_us_ascii(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-ISO-2022 */
Object g2int_create_transcoder_for_iso_2022()
{
    Object tc;

    x_note_fn_call(26,149);
    tc = g2int_make_iso_2022_transcoder_1();
    g2int_set_up_iso_2022_transcoder_for_x_compound_text(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-JIS-X-0208 */
Object g2int_create_transcoder_for_jis_x_0208()
{
    Object tc;

    x_note_fn_call(26,150);
    tc = g2int_make_iso_2022_transcoder_1();
    g2int_set_up_iso_2022_transcoder_for_jis_x_0208(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-JIS-X-0208-EUC */
Object g2int_create_transcoder_for_jis_x_0208_euc()
{
    Object tc;

    x_note_fn_call(26,151);
    tc = g2int_make_iso_2022_transcoder_1();
    g2int_set_up_iso_2022_transcoder_for_jis_x_0208_euc(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-SHIFT-JIS-X-0208 */
Object g2int_create_transcoder_for_shift_jis_x_0208()
{
    Object tc;

    x_note_fn_call(26,152);
    tc = g2int_make_shift_jis_transcoder_function();
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-KS-C-5601 */
Object g2int_create_transcoder_for_ks_c_5601()
{
    Object tc;

    x_note_fn_call(26,153);
    tc = g2int_make_iso_2022_transcoder_1();
    g2int_set_up_iso_2022_transcoder_for_ks_c_5601(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-KS-C-5601-EUC */
Object g2int_create_transcoder_for_ks_c_5601_euc()
{
    Object tc;

    x_note_fn_call(26,154);
    tc = g2int_make_iso_2022_transcoder_1();
    g2int_set_up_iso_2022_transcoder_for_ks_c_5601_euc(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-GB-2312 */
Object g2int_create_transcoder_for_gb_2312()
{
    Object tc;

    x_note_fn_call(26,155);
    tc = g2int_make_iso_2022_transcoder_1();
    g2int_set_up_iso_2022_transcoder_for_gb_2312(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-GB-2312-EUC */
Object g2int_create_transcoder_for_gb_2312_euc()
{
    Object tc;

    x_note_fn_call(26,156);
    tc = g2int_make_iso_2022_transcoder_1();
    g2int_set_up_iso_2022_transcoder_for_gb_2312_euc(tc);
    return VALUES_1(tc);
}

static Object array_constant_9;    /* # */

static Object Qg2int_left;         /* left */

static Object array_constant_10;   /* # */

static Object Qg2int_right;        /* right */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

static Object array_constant_20;   /* # */

static Object array_constant_21;   /* # */

static Object array_constant_22;   /* # */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

static Object array_constant_25;   /* # */

static Object array_constant_26;   /* # */

static Object array_constant_27;   /* # */

static Object array_constant_28;   /* # */

static Object array_constant_29;   /* # */

static Object array_constant_30;   /* # */

static Object array_constant_31;   /* # */

/* READ-ISO-2022-ESCAPE-FROM-WIDE-STRING */
Object g2int_read_iso_2022_escape_from_wide_string(string_1,index_1)
    Object string_1, index_1;
{
    Object forward_index;
    SI_Long length_1, escape_end_index, string_end_index, i, j, c1, c2, temp;
    char wide_string_p, temp_1;
    char temp_2;

    x_note_fn_call(26,157);
    forward_index = Nil;
    forward_index = index_1;
    wide_string_p = INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_9));
    escape_end_index = UBYTE_16_ISAREF_1(array_constant_9,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(array_constant_9,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    if (wide_string_p) {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	string_end_index = UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    }
    else
	string_end_index = IFIX(g2int_gensym_string_length(string_1));
    i = (SI_Long)0L;
    j = IFIX(forward_index);
    c1 = (SI_Long)0L;
    c2 = (SI_Long)0L;
  next_loop:
    if ( !(i < escape_end_index))
	goto end_loop;
    temp = UBYTE_16_ISAREF_1(array_constant_9,i);
    i = i + (SI_Long)1L;
    c1 = temp;
    if ( !(j < string_end_index)) {
	temp_1 = TRUEP(Nil);
	goto end;
    }
    if (wide_string_p) {
	temp = UBYTE_16_ISAREF_1(string_1,j);
	j = j + (SI_Long)1L;
	c2 = temp;
    }
    else {
	temp_2 = ICHAR(string_1,j);
	j = j + (SI_Long)1L;
	c2 = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
    }
    if (c1 != c2) {
	temp_1 = TRUEP(Nil);
	goto end;
    }
    goto next_loop;
  end_loop:
    forward_index = FIX(j);
    temp_1 = TRUEP(T);
    goto end;
    temp_1 = TRUEP(Qnil);
  end:;
    if (temp_1)
	return VALUES_3(Qg2int_jis_x_0208,forward_index,Qg2int_left);
    else {
	forward_index = index_1;
	wide_string_p = INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != 
		(SI_Long)0L;
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_10));
	escape_end_index = UBYTE_16_ISAREF_1(array_constant_10,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(array_constant_10,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	if (wide_string_p) {
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	    string_end_index = UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	}
	else
	    string_end_index = IFIX(g2int_gensym_string_length(string_1));
	i = (SI_Long)0L;
	j = IFIX(forward_index);
	c1 = (SI_Long)0L;
	c2 = (SI_Long)0L;
      next_loop_1:
	if ( !(i < escape_end_index))
	    goto end_loop_1;
	temp = UBYTE_16_ISAREF_1(array_constant_10,i);
	i = i + (SI_Long)1L;
	c1 = temp;
	if ( !(j < string_end_index)) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	if (wide_string_p) {
	    temp = UBYTE_16_ISAREF_1(string_1,j);
	    j = j + (SI_Long)1L;
	    c2 = temp;
	}
	else {
	    temp_2 = ICHAR(string_1,j);
	    j = j + (SI_Long)1L;
	    c2 = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
	}
	if (c1 != c2) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	forward_index = FIX(j);
	temp_1 = TRUEP(T);
	goto end_1;
	temp_1 = TRUEP(Qnil);
      end_1:;
	if (temp_1)
	    return VALUES_3(Qg2int_ks_c_5601,forward_index,Qg2int_right);
	else {
	    forward_index = index_1;
	    wide_string_p = INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != 
		    (SI_Long)0L;
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_11));
	    escape_end_index = UBYTE_16_ISAREF_1(array_constant_11,
		    length_1 - (SI_Long)2L) + 
		    ((UBYTE_16_ISAREF_1(array_constant_11,length_1 - 
		    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	    if (wide_string_p) {
		length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
		string_end_index = UBYTE_16_ISAREF_1(string_1,length_1 - 
			(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,
			length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			(SI_Long)16L);
	    }
	    else
		string_end_index = IFIX(g2int_gensym_string_length(string_1));
	    i = (SI_Long)0L;
	    j = IFIX(forward_index);
	    c1 = (SI_Long)0L;
	    c2 = (SI_Long)0L;
	  next_loop_2:
	    if ( !(i < escape_end_index))
		goto end_loop_2;
	    temp = UBYTE_16_ISAREF_1(array_constant_11,i);
	    i = i + (SI_Long)1L;
	    c1 = temp;
	    if ( !(j < string_end_index)) {
		temp_1 = TRUEP(Nil);
		goto end_2;
	    }
	    if (wide_string_p) {
		temp = UBYTE_16_ISAREF_1(string_1,j);
		j = j + (SI_Long)1L;
		c2 = temp;
	    }
	    else {
		temp_2 = ICHAR(string_1,j);
		j = j + (SI_Long)1L;
		c2 = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
	    }
	    if (c1 != c2) {
		temp_1 = TRUEP(Nil);
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    forward_index = FIX(j);
	    temp_1 = TRUEP(T);
	    goto end_2;
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	    if (temp_1)
		return VALUES_3(Qg2int_jis_x_0208,forward_index,Qg2int_right);
	    else {
		forward_index = index_1;
		wide_string_p = INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
			!= (SI_Long)0L;
		length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_12));
		escape_end_index = UBYTE_16_ISAREF_1(array_constant_12,
			length_1 - (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(array_constant_12,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
		if (wide_string_p) {
		    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
		    string_end_index = UBYTE_16_ISAREF_1(string_1,length_1 
			    - (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,
			    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L);
		}
		else
		    string_end_index = 
			    IFIX(g2int_gensym_string_length(string_1));
		i = (SI_Long)0L;
		j = IFIX(forward_index);
		c1 = (SI_Long)0L;
		c2 = (SI_Long)0L;
	      next_loop_3:
		if ( !(i < escape_end_index))
		    goto end_loop_3;
		temp = UBYTE_16_ISAREF_1(array_constant_12,i);
		i = i + (SI_Long)1L;
		c1 = temp;
		if ( !(j < string_end_index)) {
		    temp_1 = TRUEP(Nil);
		    goto end_3;
		}
		if (wide_string_p) {
		    temp = UBYTE_16_ISAREF_1(string_1,j);
		    j = j + (SI_Long)1L;
		    c2 = temp;
		}
		else {
		    temp_2 = ICHAR(string_1,j);
		    j = j + (SI_Long)1L;
		    c2 = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
		}
		if (c1 != c2) {
		    temp_1 = TRUEP(Nil);
		    goto end_3;
		}
		goto next_loop_3;
	      end_loop_3:
		forward_index = FIX(j);
		temp_1 = TRUEP(T);
		goto end_3;
		temp_1 = TRUEP(Qnil);
	      end_3:;
		if (temp_1)
		    return VALUES_3(Qg2int_gb_2312,forward_index,Qg2int_right);
		else {
		    forward_index = index_1;
		    wide_string_p = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != 
			    (SI_Long)0L;
		    length_1 = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_13));
		    escape_end_index = UBYTE_16_ISAREF_1(array_constant_13,
			    length_1 - (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(array_constant_13,length_1 
			    - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
		    if (wide_string_p) {
			length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
			string_end_index = UBYTE_16_ISAREF_1(string_1,
				length_1 - (SI_Long)2L) + 
				((UBYTE_16_ISAREF_1(string_1,length_1 - 
				(SI_Long)1L) & (SI_Long)8191L) << 
				(SI_Long)16L);
		    }
		    else
			string_end_index = 
				IFIX(g2int_gensym_string_length(string_1));
		    i = (SI_Long)0L;
		    j = IFIX(forward_index);
		    c1 = (SI_Long)0L;
		    c2 = (SI_Long)0L;
		  next_loop_4:
		    if ( !(i < escape_end_index))
			goto end_loop_4;
		    temp = UBYTE_16_ISAREF_1(array_constant_13,i);
		    i = i + (SI_Long)1L;
		    c1 = temp;
		    if ( !(j < string_end_index)) {
			temp_1 = TRUEP(Nil);
			goto end_4;
		    }
		    if (wide_string_p) {
			temp = UBYTE_16_ISAREF_1(string_1,j);
			j = j + (SI_Long)1L;
			c2 = temp;
		    }
		    else {
			temp_2 = ICHAR(string_1,j);
			j = j + (SI_Long)1L;
			c2 = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
		    }
		    if (c1 != c2) {
			temp_1 = TRUEP(Nil);
			goto end_4;
		    }
		    goto next_loop_4;
		  end_loop_4:
		    forward_index = FIX(j);
		    temp_1 = TRUEP(T);
		    goto end_4;
		    temp_1 = TRUEP(Qnil);
		  end_4:;
		    if (temp_1)
			return VALUES_3(Qg2int_ks_c_5601,forward_index,
				Qg2int_left);
		    else {
			forward_index = index_1;
			wide_string_p = 
				INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
				!= (SI_Long)0L;
			length_1 = 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_14));
			escape_end_index = 
				UBYTE_16_ISAREF_1(array_constant_14,
				length_1 - (SI_Long)2L) + 
				((UBYTE_16_ISAREF_1(array_constant_14,
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L);
			if (wide_string_p) {
			    length_1 = 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
			    string_end_index = UBYTE_16_ISAREF_1(string_1,
				    length_1 - (SI_Long)2L) + 
				    ((UBYTE_16_ISAREF_1(string_1,length_1 
				    - (SI_Long)1L) & (SI_Long)8191L) << 
				    (SI_Long)16L);
			}
			else
			    string_end_index = 
				    IFIX(g2int_gensym_string_length(string_1));
			i = (SI_Long)0L;
			j = IFIX(forward_index);
			c1 = (SI_Long)0L;
			c2 = (SI_Long)0L;
		      next_loop_5:
			if ( !(i < escape_end_index))
			    goto end_loop_5;
			temp = UBYTE_16_ISAREF_1(array_constant_14,i);
			i = i + (SI_Long)1L;
			c1 = temp;
			if ( !(j < string_end_index)) {
			    temp_1 = TRUEP(Nil);
			    goto end_5;
			}
			if (wide_string_p) {
			    temp = UBYTE_16_ISAREF_1(string_1,j);
			    j = j + (SI_Long)1L;
			    c2 = temp;
			}
			else {
			    temp_2 = ICHAR(string_1,j);
			    j = j + (SI_Long)1L;
			    c2 = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
			}
			if (c1 != c2) {
			    temp_1 = TRUEP(Nil);
			    goto end_5;
			}
			goto next_loop_5;
		      end_loop_5:
			forward_index = FIX(j);
			temp_1 = TRUEP(T);
			goto end_5;
			temp_1 = TRUEP(Qnil);
		      end_5:;
			if (temp_1)
			    return VALUES_3(Qg2int_jis_x_0208,
				    forward_index,Qg2int_left);
			else {
			    forward_index = index_1;
			    wide_string_p = 
				    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
				    != (SI_Long)0L;
			    length_1 = 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_15));
			    escape_end_index = 
				    UBYTE_16_ISAREF_1(array_constant_15,
				    length_1 - (SI_Long)2L) + 
				    ((UBYTE_16_ISAREF_1(array_constant_15,
				    length_1 - (SI_Long)1L) & 
				    (SI_Long)8191L) << (SI_Long)16L);
			    if (wide_string_p) {
				length_1 = 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
				string_end_index = 
					UBYTE_16_ISAREF_1(string_1,
					length_1 - (SI_Long)2L) + 
					((UBYTE_16_ISAREF_1(string_1,
					length_1 - (SI_Long)1L) & 
					(SI_Long)8191L) << (SI_Long)16L);
			    }
			    else
				string_end_index = 
					IFIX(g2int_gensym_string_length(string_1));
			    i = (SI_Long)0L;
			    j = IFIX(forward_index);
			    c1 = (SI_Long)0L;
			    c2 = (SI_Long)0L;
			  next_loop_6:
			    if ( !(i < escape_end_index))
				goto end_loop_6;
			    temp = UBYTE_16_ISAREF_1(array_constant_15,i);
			    i = i + (SI_Long)1L;
			    c1 = temp;
			    if ( !(j < string_end_index)) {
				temp_1 = TRUEP(Nil);
				goto end_6;
			    }
			    if (wide_string_p) {
				temp = UBYTE_16_ISAREF_1(string_1,j);
				j = j + (SI_Long)1L;
				c2 = temp;
			    }
			    else {
				temp_2 = ICHAR(string_1,j);
				j = j + (SI_Long)1L;
				c2 = 
					IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
			    }
			    if (c1 != c2) {
				temp_1 = TRUEP(Nil);
				goto end_6;
			    }
			    goto next_loop_6;
			  end_loop_6:
			    forward_index = FIX(j);
			    temp_1 = TRUEP(T);
			    goto end_6;
			    temp_1 = TRUEP(Qnil);
			  end_6:;
			    if (temp_1)
				return VALUES_3(Qg2int_gb_2312,
					forward_index,Qg2int_left);
			    else {
				forward_index = index_1;
				wide_string_p = 
					INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
					!= (SI_Long)0L;
				length_1 = 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_16));
				escape_end_index = 
					UBYTE_16_ISAREF_1(array_constant_16,
					length_1 - (SI_Long)2L) + 
					((UBYTE_16_ISAREF_1(array_constant_16,
					length_1 - (SI_Long)1L) & 
					(SI_Long)8191L) << (SI_Long)16L);
				if (wide_string_p) {
				    length_1 = 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
				    string_end_index = 
					    UBYTE_16_ISAREF_1(string_1,
					    length_1 - (SI_Long)2L) + 
					    ((UBYTE_16_ISAREF_1(string_1,
					    length_1 - (SI_Long)1L) & 
					    (SI_Long)8191L) << (SI_Long)16L);
				}
				else
				    string_end_index = 
					    IFIX(g2int_gensym_string_length(string_1));
				i = (SI_Long)0L;
				j = IFIX(forward_index);
				c1 = (SI_Long)0L;
				c2 = (SI_Long)0L;
			      next_loop_7:
				if ( !(i < escape_end_index))
				    goto end_loop_7;
				temp = UBYTE_16_ISAREF_1(array_constant_16,i);
				i = i + (SI_Long)1L;
				c1 = temp;
				if ( !(j < string_end_index)) {
				    temp_1 = TRUEP(Nil);
				    goto end_7;
				}
				if (wide_string_p) {
				    temp = UBYTE_16_ISAREF_1(string_1,j);
				    j = j + (SI_Long)1L;
				    c2 = temp;
				}
				else {
				    temp_2 = ICHAR(string_1,j);
				    j = j + (SI_Long)1L;
				    c2 = 
					    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
				}
				if (c1 != c2) {
				    temp_1 = TRUEP(Nil);
				    goto end_7;
				}
				goto next_loop_7;
			      end_loop_7:
				forward_index = FIX(j);
				temp_1 = TRUEP(T);
				goto end_7;
				temp_1 = TRUEP(Qnil);
			      end_7:;
				if (temp_1)
				    return VALUES_3(Qg2int_jis_x_0208,
					    forward_index,Qg2int_left);
				else {
				    forward_index = index_1;
				    wide_string_p = 
					    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
					    != (SI_Long)0L;
				    length_1 = 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_17));
				    escape_end_index = 
					    UBYTE_16_ISAREF_1(array_constant_17,
					    length_1 - (SI_Long)2L) + 
					    ((UBYTE_16_ISAREF_1(array_constant_17,
					    length_1 - (SI_Long)1L) & 
					    (SI_Long)8191L) << (SI_Long)16L);
				    if (wide_string_p) {
					length_1 = 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
					string_end_index = 
						UBYTE_16_ISAREF_1(string_1,
						length_1 - (SI_Long)2L) + 
						((UBYTE_16_ISAREF_1(string_1,
						length_1 - (SI_Long)1L) & 
						(SI_Long)8191L) << 
						(SI_Long)16L);
				    }
				    else
					string_end_index = 
						IFIX(g2int_gensym_string_length(string_1));
				    i = (SI_Long)0L;
				    j = IFIX(forward_index);
				    c1 = (SI_Long)0L;
				    c2 = (SI_Long)0L;
				  next_loop_8:
				    if ( !(i < escape_end_index))
					goto end_loop_8;
				    temp = 
					    UBYTE_16_ISAREF_1(array_constant_17,
					    i);
				    i = i + (SI_Long)1L;
				    c1 = temp;
				    if ( !(j < string_end_index)) {
					temp_1 = TRUEP(Nil);
					goto end_8;
				    }
				    if (wide_string_p) {
					temp = UBYTE_16_ISAREF_1(string_1,j);
					j = j + (SI_Long)1L;
					c2 = temp;
				    }
				    else {
					temp_2 = ICHAR(string_1,j);
					j = j + (SI_Long)1L;
					c2 = 
						IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
				    }
				    if (c1 != c2) {
					temp_1 = TRUEP(Nil);
					goto end_8;
				    }
				    goto next_loop_8;
				  end_loop_8:
				    forward_index = FIX(j);
				    temp_1 = TRUEP(T);
				    goto end_8;
				    temp_1 = TRUEP(Qnil);
				  end_8:;
				    if (temp_1)
					return VALUES_3(Qg2int_jis_x_0208,
						forward_index,Qg2int_left);
				    else {
					forward_index = index_1;
					wide_string_p = 
						INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
						!= (SI_Long)0L;
					length_1 = 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_18));
					escape_end_index = 
						UBYTE_16_ISAREF_1(array_constant_18,
						length_1 - (SI_Long)2L) + 
						((UBYTE_16_ISAREF_1(array_constant_18,
						length_1 - (SI_Long)1L) & 
						(SI_Long)8191L) << 
						(SI_Long)16L);
					if (wide_string_p) {
					    length_1 = 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
					    string_end_index = 
						    UBYTE_16_ISAREF_1(string_1,
						    length_1 - 
						    (SI_Long)2L) + 
						    ((UBYTE_16_ISAREF_1(string_1,
						    length_1 - 
						    (SI_Long)1L) & 
						    (SI_Long)8191L) << 
						    (SI_Long)16L);
					}
					else
					    string_end_index = 
						    IFIX(g2int_gensym_string_length(string_1));
					i = (SI_Long)0L;
					j = IFIX(forward_index);
					c1 = (SI_Long)0L;
					c2 = (SI_Long)0L;
				      next_loop_9:
					if ( !(i < escape_end_index))
					    goto end_loop_9;
					temp = 
						UBYTE_16_ISAREF_1(array_constant_18,
						i);
					i = i + (SI_Long)1L;
					c1 = temp;
					if ( !(j < string_end_index)) {
					    temp_1 = TRUEP(Nil);
					    goto end_9;
					}
					if (wide_string_p) {
					    temp = 
						    UBYTE_16_ISAREF_1(string_1,
						    j);
					    j = j + (SI_Long)1L;
					    c2 = temp;
					}
					else {
					    temp_2 = ICHAR(string_1,j);
					    j = j + (SI_Long)1L;
					    c2 = 
						    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
					}
					if (c1 != c2) {
					    temp_1 = TRUEP(Nil);
					    goto end_9;
					}
					goto next_loop_9;
				      end_loop_9:
					forward_index = FIX(j);
					temp_1 = TRUEP(T);
					goto end_9;
					temp_1 = TRUEP(Qnil);
				      end_9:;
					if (temp_1)
					    return VALUES_3(Qg2int_gb_2312,
						    forward_index,Qg2int_left);
					else {
					    forward_index = index_1;
					    wide_string_p = 
						    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
						    != (SI_Long)0L;
					    length_1 = 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_19));
					    escape_end_index = 
						    UBYTE_16_ISAREF_1(array_constant_19,
						    length_1 - 
						    (SI_Long)2L) + 
						    ((UBYTE_16_ISAREF_1(array_constant_19,
						    length_1 - 
						    (SI_Long)1L) & 
						    (SI_Long)8191L) << 
						    (SI_Long)16L);
					    if (wide_string_p) {
						length_1 = 
							IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
						string_end_index = 
							UBYTE_16_ISAREF_1(string_1,
							length_1 - 
							(SI_Long)2L) + 
							((UBYTE_16_ISAREF_1(string_1,
							length_1 - 
							(SI_Long)1L) & 
							(SI_Long)8191L) << 
							(SI_Long)16L);
					    }
					    else
						string_end_index = 
							IFIX(g2int_gensym_string_length(string_1));
					    i = (SI_Long)0L;
					    j = IFIX(forward_index);
					    c1 = (SI_Long)0L;
					    c2 = (SI_Long)0L;
					  next_loop_10:
					    if ( !(i < escape_end_index))
						goto end_loop_10;
					    temp = 
						    UBYTE_16_ISAREF_1(array_constant_19,
						    i);
					    i = i + (SI_Long)1L;
					    c1 = temp;
					    if ( !(j < string_end_index)) {
						temp_1 = TRUEP(Nil);
						goto end_10;
					    }
					    if (wide_string_p) {
						temp = 
							UBYTE_16_ISAREF_1(string_1,
							j);
						j = j + (SI_Long)1L;
						c2 = temp;
					    }
					    else {
						temp_2 = ICHAR(string_1,j);
						j = j + (SI_Long)1L;
						c2 = 
							IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
					    }
					    if (c1 != c2) {
						temp_1 = TRUEP(Nil);
						goto end_10;
					    }
					    goto next_loop_10;
					  end_loop_10:
					    forward_index = FIX(j);
					    temp_1 = TRUEP(T);
					    goto end_10;
					    temp_1 = TRUEP(Qnil);
					  end_10:;
					    if (temp_1)
						return VALUES_3(Qg2int_iso_8859_9,
							forward_index,
							Qg2int_right);
					    else {
						forward_index = index_1;
						wide_string_p = 
							INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
							!= (SI_Long)0L;
						length_1 = 
							IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_20));
						escape_end_index = 
							UBYTE_16_ISAREF_1(array_constant_20,
							length_1 - 
							(SI_Long)2L) + 
							((UBYTE_16_ISAREF_1(array_constant_20,
							length_1 - 
							(SI_Long)1L) & 
							(SI_Long)8191L) << 
							(SI_Long)16L);
						if (wide_string_p) {
						    length_1 = 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
						    string_end_index = 
							    UBYTE_16_ISAREF_1(string_1,
							    length_1 - 
							    (SI_Long)2L) + 
							    ((UBYTE_16_ISAREF_1(string_1,
							    length_1 - 
							    (SI_Long)1L) & 
							    (SI_Long)8191L) 
							    << (SI_Long)16L);
						}
						else
						    string_end_index = 
							    IFIX(g2int_gensym_string_length(string_1));
						i = (SI_Long)0L;
						j = IFIX(forward_index);
						c1 = (SI_Long)0L;
						c2 = (SI_Long)0L;
					      next_loop_11:
						if ( !(i < escape_end_index))
						    goto end_loop_11;
						temp = 
							UBYTE_16_ISAREF_1(array_constant_20,
							i);
						i = i + (SI_Long)1L;
						c1 = temp;
						if ( !(j < string_end_index)) {
						    temp_1 = TRUEP(Nil);
						    goto end_11;
						}
						if (wide_string_p) {
						    temp = 
							    UBYTE_16_ISAREF_1(string_1,
							    j);
						    j = j + (SI_Long)1L;
						    c2 = temp;
						}
						else {
						    temp_2 = ICHAR(string_1,j);
						    j = j + (SI_Long)1L;
						    c2 = 
							    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
						}
						if (c1 != c2) {
						    temp_1 = TRUEP(Nil);
						    goto end_11;
						}
						goto next_loop_11;
					      end_loop_11:
						forward_index = FIX(j);
						temp_1 = TRUEP(T);
						goto end_11;
						temp_1 = TRUEP(Qnil);
					      end_11:;
						if (temp_1)
						    return VALUES_3(Qg2int_iso_8859_8,
							    forward_index,
							    Qg2int_right);
						else {
						    forward_index = index_1;
						    wide_string_p = 
							    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
							    != (SI_Long)0L;
						    length_1 = 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_21));
						    escape_end_index = 
							    UBYTE_16_ISAREF_1(array_constant_21,
							    length_1 - 
							    (SI_Long)2L) + 
							    ((UBYTE_16_ISAREF_1(array_constant_21,
							    length_1 - 
							    (SI_Long)1L) & 
							    (SI_Long)8191L) 
							    << (SI_Long)16L);
						    if (wide_string_p) {
							length_1 = 
								IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
							string_end_index = 
								UBYTE_16_ISAREF_1(string_1,
								length_1 - 
								(SI_Long)2L) 
								+ 
								((UBYTE_16_ISAREF_1(string_1,
								length_1 - 
								(SI_Long)1L) 
								& 
								(SI_Long)8191L) 
								<< 
								(SI_Long)16L);
						    }
						    else
							string_end_index = 
								IFIX(g2int_gensym_string_length(string_1));
						    i = (SI_Long)0L;
						    j = IFIX(forward_index);
						    c1 = (SI_Long)0L;
						    c2 = (SI_Long)0L;
						  next_loop_12:
						    if ( !(i < 
							    escape_end_index))
							goto end_loop_12;
						    temp = 
							    UBYTE_16_ISAREF_1(array_constant_21,
							    i);
						    i = i + (SI_Long)1L;
						    c1 = temp;
						    if ( !(j < 
							    string_end_index)) 
								{
							temp_1 = TRUEP(Nil);
							goto end_12;
						    }
						    if (wide_string_p) {
							temp = 
								UBYTE_16_ISAREF_1(string_1,
								j);
							j = j + (SI_Long)1L;
							c2 = temp;
						    }
						    else {
							temp_2 = 
								ICHAR(string_1,
								j);
							j = j + (SI_Long)1L;
							c2 = 
								IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
						    }
						    if (c1 != c2) {
							temp_1 = TRUEP(Nil);
							goto end_12;
						    }
						    goto next_loop_12;
						  end_loop_12:
						    forward_index = FIX(j);
						    temp_1 = TRUEP(T);
						    goto end_12;
						    temp_1 = TRUEP(Qnil);
						  end_12:;
						    if (temp_1)
							return VALUES_3(Qg2int_iso_8859_7,
								forward_index,
								Qg2int_right);
						    else {
							forward_index = 
								index_1;
							wide_string_p = 
								INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
								!= (SI_Long)0L;
							length_1 = 
								IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_22));
							escape_end_index = 
								UBYTE_16_ISAREF_1(array_constant_22,
								length_1 - 
								(SI_Long)2L) 
								+ 
								((UBYTE_16_ISAREF_1(array_constant_22,
								length_1 - 
								(SI_Long)1L) 
								& 
								(SI_Long)8191L) 
								<< 
								(SI_Long)16L);
							if (wide_string_p) {
							    length_1 = 
								    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
							    string_end_index 
								    = 
								    UBYTE_16_ISAREF_1(string_1,
								    length_1 
								    - 
								    (SI_Long)2L) 
								    + 
								    ((UBYTE_16_ISAREF_1(string_1,
								    length_1 
								    - 
								    (SI_Long)1L) 
								    & 
								    (SI_Long)8191L) 
								    << 
								    (SI_Long)16L);
							}
							else
							    string_end_index 
								    = 
								    IFIX(g2int_gensym_string_length(string_1));
							i = (SI_Long)0L;
							j = 
								IFIX(forward_index);
							c1 = (SI_Long)0L;
							c2 = (SI_Long)0L;
						      next_loop_13:
							if ( !(i < 
								escape_end_index))
							    goto end_loop_13;
							temp = 
								UBYTE_16_ISAREF_1(array_constant_22,
								i);
							i = i + (SI_Long)1L;
							c1 = temp;
							if ( !(j < 
								string_end_index)) 
								    {
							    temp_1 = 
								    TRUEP(Nil);
							    goto end_13;
							}
							if (wide_string_p) {
							    temp = 
								    UBYTE_16_ISAREF_1(string_1,
								    j);
							    j = j + 
								    (SI_Long)1L;
							    c2 = temp;
							}
							else {
							    temp_2 = 
								    ICHAR(string_1,
								    j);
							    j = j + 
								    (SI_Long)1L;
							    c2 = 
								    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
							}
							if (c1 != c2) {
							    temp_1 = 
								    TRUEP(Nil);
							    goto end_13;
							}
							goto next_loop_13;
						      end_loop_13:
							forward_index = FIX(j);
							temp_1 = TRUEP(T);
							goto end_13;
							temp_1 = TRUEP(Qnil);
						      end_13:;
							if (temp_1)
							    return VALUES_3(Qg2int_iso_8859_6,
								    forward_index,
								    Qg2int_right);
							else {
							    forward_index 
								    = index_1;
							    wide_string_p 
								    = 
								    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
								    != 
								    (SI_Long)0L;
							    length_1 = 
								    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_23));
							    escape_end_index 
								    = 
								    UBYTE_16_ISAREF_1(array_constant_23,
								    length_1 
								    - 
								    (SI_Long)2L) 
								    + 
								    ((UBYTE_16_ISAREF_1(array_constant_23,
								    length_1 
								    - 
								    (SI_Long)1L) 
								    & 
								    (SI_Long)8191L) 
								    << 
								    (SI_Long)16L);
							    if (wide_string_p) 
									{
								length_1 = 
									IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
								string_end_index 
									= 
									UBYTE_16_ISAREF_1(string_1,
									length_1 
									- 
									(SI_Long)2L) 
									+ 
									((UBYTE_16_ISAREF_1(string_1,
									length_1 
									- 
									(SI_Long)1L) 
									& 
									(SI_Long)8191L) 
									<< 
									(SI_Long)16L);
							    }
							    else
								string_end_index 
									= 
									IFIX(g2int_gensym_string_length(string_1));
							    i = (SI_Long)0L;
							    j = 
								    IFIX(forward_index);
							    c1 = (SI_Long)0L;
							    c2 = (SI_Long)0L;
							  next_loop_14:
							    if ( !(i < 
								    escape_end_index))
								goto end_loop_14;
							    temp = 
								    UBYTE_16_ISAREF_1(array_constant_23,
								    i);
							    i = i + 
								    (SI_Long)1L;
							    c1 = temp;
							    if ( !(j < 
								    string_end_index)) 
									{
								temp_1 = 
									TRUEP(Nil);
								goto end_14;
							    }
							    if (wide_string_p) 
									{
								temp = 
									UBYTE_16_ISAREF_1(string_1,
									j);
								j = j + 
									(SI_Long)1L;
								c2 = temp;
							    }
							    else {
								temp_2 = 
									ICHAR(string_1,
									j);
								j = j + 
									(SI_Long)1L;
								c2 = 
									IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
							    }
							    if (c1 != c2) {
								temp_1 = 
									TRUEP(Nil);
								goto end_14;
							    }
							    goto next_loop_14;
							  end_loop_14:
							    forward_index 
								    = FIX(j);
							    temp_1 = TRUEP(T);
							    goto end_14;
							    temp_1 = 
								    TRUEP(Qnil);
							  end_14:;
							    if (temp_1)
								return VALUES_3(Qg2int_iso_8859_5,
									forward_index,
									Qg2int_right);
							    else {
								forward_index 
									= 
									index_1;
								wide_string_p 
									= 
									INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
									!= 
									(SI_Long)0L;
								length_1 = 
									IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_24));
								escape_end_index 
									= 
									UBYTE_16_ISAREF_1(array_constant_24,
									length_1 
									- 
									(SI_Long)2L) 
									+ 
									((UBYTE_16_ISAREF_1(array_constant_24,
									length_1 
									- 
									(SI_Long)1L) 
									& 
									(SI_Long)8191L) 
									<< 
									(SI_Long)16L);
								if (wide_string_p) 
									    {
								    length_1 
									    = 
									    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
								    string_end_index 
									    = 
									    UBYTE_16_ISAREF_1(string_1,
									    length_1 
									    - 
									    (SI_Long)2L) 
									    + 
									    ((UBYTE_16_ISAREF_1(string_1,
									    length_1 
									    - 
									    (SI_Long)1L) 
									    & 
									    (SI_Long)8191L) 
									    << 
									    (SI_Long)16L);
								}
								else
								    string_end_index 
									    = 
									    IFIX(g2int_gensym_string_length(string_1));
								i = 
									(SI_Long)0L;
								j = 
									IFIX(forward_index);
								c1 = 
									(SI_Long)0L;
								c2 = 
									(SI_Long)0L;
							      next_loop_15:
								if ( !(i < 
									escape_end_index))
								    goto end_loop_15;
								temp = 
									UBYTE_16_ISAREF_1(array_constant_24,
									i);
								i = i + 
									(SI_Long)1L;
								c1 = temp;
								if ( !(j < 
									string_end_index)) 
									    {
								    temp_1 
									    = 
									    TRUEP(Nil);
								    goto end_15;
								}
								if (wide_string_p) 
									    {
								    temp = 
									    UBYTE_16_ISAREF_1(string_1,
									    j);
								    j = j 
									    + 
									    (SI_Long)1L;
								    c2 = temp;
								}
								else {
								    temp_2 
									    = 
									    ICHAR(string_1,
									    j);
								    j = j 
									    + 
									    (SI_Long)1L;
								    c2 = 
									    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
								}
								if (c1 != c2) {
								    temp_1 
									    = 
									    TRUEP(Nil);
								    goto end_15;
								}
								goto next_loop_15;
							      end_loop_15:
								forward_index 
									= 
									FIX(j);
								temp_1 = 
									TRUEP(T);
								goto end_15;
								temp_1 = 
									TRUEP(Qnil);
							      end_15:;
								if (temp_1)
								    return VALUES_3(Qg2int_iso_8859_4,
									    forward_index,
									    Qg2int_right);
								else {
								    forward_index 
									    = 
									    index_1;
								    wide_string_p 
									    = 
									    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
									    != 
									    (SI_Long)0L;
								    length_1 
									    = 
									    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_25));
								    escape_end_index 
									    = 
									    UBYTE_16_ISAREF_1(array_constant_25,
									    length_1 
									    - 
									    (SI_Long)2L) 
									    + 
									    ((UBYTE_16_ISAREF_1(array_constant_25,
									    length_1 
									    - 
									    (SI_Long)1L) 
									    & 
									    (SI_Long)8191L) 
									    << 
									    (SI_Long)16L);
								    if (wide_string_p) 
										{
									length_1 
										= 
										IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
									string_end_index 
										= 
										UBYTE_16_ISAREF_1(string_1,
										length_1 
										- 
										(SI_Long)2L) 
										+ 
										((UBYTE_16_ISAREF_1(string_1,
										length_1 
										- 
										(SI_Long)1L) 
										& 
										(SI_Long)8191L) 
										<< 
										(SI_Long)16L);
								    }
								    else
									string_end_index 
										= 
										IFIX(g2int_gensym_string_length(string_1));
								    i = 
									    (SI_Long)0L;
								    j = 
									    IFIX(forward_index);
								    c1 = 
									    (SI_Long)0L;
								    c2 = 
									    (SI_Long)0L;
								  next_loop_16:
								    if ( 
									    !(i 
									    < 
									    escape_end_index))
									goto end_loop_16;
								    temp = 
									    UBYTE_16_ISAREF_1(array_constant_25,
									    i);
								    i = i 
									    + 
									    (SI_Long)1L;
								    c1 = temp;
								    if ( 
									    !(j 
									    < 
									    string_end_index)) 
										{
									temp_1 
										= 
										TRUEP(Nil);
									goto end_16;
								    }
								    if (wide_string_p) 
										{
									temp 
										= 
										UBYTE_16_ISAREF_1(string_1,
										j);
									j 
										= 
										j 
										+ 
										(SI_Long)1L;
									c2 
										= 
										temp;
								    }
								    else {
									temp_2 
										= 
										ICHAR(string_1,
										j);
									j 
										= 
										j 
										+ 
										(SI_Long)1L;
									c2 
										= 
										IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
								    }
								    if (c1 
									    != 
									    c2) 
										{
									temp_1 
										= 
										TRUEP(Nil);
									goto end_16;
								    }
								    goto next_loop_16;
								  end_loop_16:
								    forward_index 
									    = 
									    FIX(j);
								    temp_1 
									    = 
									    TRUEP(T);
								    goto end_16;
								    temp_1 
									    = 
									    TRUEP(Qnil);
								  end_16:;
								    if (temp_1)
									return VALUES_3(Qg2int_iso_8859_3,
										forward_index,
										Qg2int_right);
								    else {
									forward_index 
										= 
										index_1;
									wide_string_p 
										= 
										INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
										!= 
										(SI_Long)0L;
									length_1 
										= 
										IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_26));
									escape_end_index 
										= 
										UBYTE_16_ISAREF_1(array_constant_26,
										length_1 
										- 
										(SI_Long)2L) 
										+ 
										((UBYTE_16_ISAREF_1(array_constant_26,
										length_1 
										- 
										(SI_Long)1L) 
										& 
										(SI_Long)8191L) 
										<< 
										(SI_Long)16L);
									if (wide_string_p) 
										    {
									    length_1 
										    = 
										    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
									    string_end_index 
										    = 
										    UBYTE_16_ISAREF_1(string_1,
										    length_1 
										    - 
										    (SI_Long)2L) 
										    + 
										    ((UBYTE_16_ISAREF_1(string_1,
										    length_1 
										    - 
										    (SI_Long)1L) 
										    & 
										    (SI_Long)8191L) 
										    << 
										    (SI_Long)16L);
									}
									else
									    string_end_index 
										    = 
										    IFIX(g2int_gensym_string_length(string_1));
									i 
										= 
										(SI_Long)0L;
									j 
										= 
										IFIX(forward_index);
									c1 
										= 
										(SI_Long)0L;
									c2 
										= 
										(SI_Long)0L;
								      next_loop_17:
									if ( 
										!(i 
										< 
										escape_end_index))
									    goto end_loop_17;
									temp 
										= 
										UBYTE_16_ISAREF_1(array_constant_26,
										i);
									i 
										= 
										i 
										+ 
										(SI_Long)1L;
									c1 
										= 
										temp;
									if ( 
										!(j 
										< 
										string_end_index)) 
										    {
									    temp_1 
										    = 
										    TRUEP(Nil);
									    goto end_17;
									}
									if (wide_string_p) 
										    {
									    temp 
										    = 
										    UBYTE_16_ISAREF_1(string_1,
										    j);
									    j 
										    = 
										    j 
										    + 
										    (SI_Long)1L;
									    c2 
										    = 
										    temp;
									}
									else {
									    temp_2 
										    = 
										    ICHAR(string_1,
										    j);
									    j 
										    = 
										    j 
										    + 
										    (SI_Long)1L;
									    c2 
										    = 
										    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
									}
									if (c1 
										!= 
										c2) 
										    {
									    temp_1 
										    = 
										    TRUEP(Nil);
									    goto end_17;
									}
									goto next_loop_17;
								      end_loop_17:
									forward_index 
										= 
										FIX(j);
									temp_1 
										= 
										TRUEP(T);
									goto end_17;
									temp_1 
										= 
										TRUEP(Qnil);
								      end_17:;
									if (temp_1)
									    return VALUES_3(Qg2int_iso_8859_2,
										    forward_index,
										    Qg2int_right);
									else {
									    forward_index 
										    = 
										    index_1;
									    wide_string_p 
										    = 
										    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
										    != 
										    (SI_Long)0L;
									    length_1 
										    = 
										    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_27));
									    escape_end_index 
										    = 
										    UBYTE_16_ISAREF_1(array_constant_27,
										    length_1 
										    - 
										    (SI_Long)2L) 
										    + 
										    ((UBYTE_16_ISAREF_1(array_constant_27,
										    length_1 
										    - 
										    (SI_Long)1L) 
										    & 
										    (SI_Long)8191L) 
										    << 
										    (SI_Long)16L);
									    if (wide_string_p) 
											{
										length_1 
											= 
											IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
										string_end_index 
											= 
											UBYTE_16_ISAREF_1(string_1,
											length_1 
											- 
											(SI_Long)2L) 
											+ 
											((UBYTE_16_ISAREF_1(string_1,
											length_1 
											- 
											(SI_Long)1L) 
											& 
											(SI_Long)8191L) 
											<< 
											(SI_Long)16L);
									    }
									    else
										string_end_index 
											= 
											IFIX(g2int_gensym_string_length(string_1));
									    i 
										    = 
										    (SI_Long)0L;
									    j 
										    = 
										    IFIX(forward_index);
									    c1 
										    = 
										    (SI_Long)0L;
									    c2 
										    = 
										    (SI_Long)0L;
									  next_loop_18:
									    if ( 
										    !(i 
										    < 
										    escape_end_index))
										goto end_loop_18;
									    temp 
										    = 
										    UBYTE_16_ISAREF_1(array_constant_27,
										    i);
									    i 
										    = 
										    i 
										    + 
										    (SI_Long)1L;
									    c1 
										    = 
										    temp;
									    if ( 
										    !(j 
										    < 
										    string_end_index)) 
											{
										temp_1 
											= 
											TRUEP(Nil);
										goto end_18;
									    }
									    if (wide_string_p) 
											{
										temp 
											= 
											UBYTE_16_ISAREF_1(string_1,
											j);
										j 
											= 
											j 
											+ 
											(SI_Long)1L;
										c2 
											= 
											temp;
									    }
									    else {
										temp_2 
											= 
											ICHAR(string_1,
											j);
										j 
											= 
											j 
											+ 
											(SI_Long)1L;
										c2 
											= 
											IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
									    }
									    if (c1 
										    != 
										    c2) 
											{
										temp_1 
											= 
											TRUEP(Nil);
										goto end_18;
									    }
									    goto next_loop_18;
									  end_loop_18:
									    forward_index 
										    = 
										    FIX(j);
									    temp_1 
										    = 
										    TRUEP(T);
									    goto end_18;
									    temp_1 
										    = 
										    TRUEP(Qnil);
									  end_18:;
									    if (temp_1)
										return VALUES_3(Qg2int_iso_8859_1,
											forward_index,
											Qg2int_right);
									    else {
										forward_index 
											= 
											index_1;
										wide_string_p 
											= 
											INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
											!= 
											(SI_Long)0L;
										length_1 
											= 
											IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_28));
										escape_end_index 
											= 
											UBYTE_16_ISAREF_1(array_constant_28,
											length_1 
											- 
											(SI_Long)2L) 
											+ 
											((UBYTE_16_ISAREF_1(array_constant_28,
											length_1 
											- 
											(SI_Long)1L) 
											& 
											(SI_Long)8191L) 
											<< 
											(SI_Long)16L);
										if (wide_string_p) 
											    {
										    length_1 
											    = 
											    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
										    string_end_index 
											    = 
											    UBYTE_16_ISAREF_1(string_1,
											    length_1 
											    - 
											    (SI_Long)2L) 
											    + 
											    ((UBYTE_16_ISAREF_1(string_1,
											    length_1 
											    - 
											    (SI_Long)1L) 
											    & 
											    (SI_Long)8191L) 
											    << 
											    (SI_Long)16L);
										}
										else
										    string_end_index 
											    = 
											    IFIX(g2int_gensym_string_length(string_1));
										i 
											= 
											(SI_Long)0L;
										j 
											= 
											IFIX(forward_index);
										c1 
											= 
											(SI_Long)0L;
										c2 
											= 
											(SI_Long)0L;
									      next_loop_19:
										if ( 
											!(i 
											< 
											escape_end_index))
										    goto end_loop_19;
										temp 
											= 
											UBYTE_16_ISAREF_1(array_constant_28,
											i);
										i 
											= 
											i 
											+ 
											(SI_Long)1L;
										c1 
											= 
											temp;
										if ( 
											!(j 
											< 
											string_end_index)) 
											    {
										    temp_1 
											    = 
											    TRUEP(Nil);
										    goto end_19;
										}
										if (wide_string_p) 
											    {
										    temp 
											    = 
											    UBYTE_16_ISAREF_1(string_1,
											    j);
										    j 
											    = 
											    j 
											    + 
											    (SI_Long)1L;
										    c2 
											    = 
											    temp;
										}
										else {
										    temp_2 
											    = 
											    ICHAR(string_1,
											    j);
										    j 
											    = 
											    j 
											    + 
											    (SI_Long)1L;
										    c2 
											    = 
											    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
										}
										if (c1 
											!= 
											c2) 
											    {
										    temp_1 
											    = 
											    TRUEP(Nil);
										    goto end_19;
										}
										goto next_loop_19;
									      end_loop_19:
										forward_index 
											= 
											FIX(j);
										temp_1 
											= 
											TRUEP(T);
										goto end_19;
										temp_1 
											= 
											TRUEP(Qnil);
									      end_19:;
										if (temp_1)
										    return VALUES_3(Qg2int_iso_646,
											    forward_index,
											    Qg2int_left);
										else {
										    forward_index 
											    = 
											    index_1;
										    wide_string_p 
											    = 
											    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
											    != 
											    (SI_Long)0L;
										    length_1 
											    = 
											    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_29));
										    escape_end_index 
											    = 
											    UBYTE_16_ISAREF_1(array_constant_29,
											    length_1 
											    - 
											    (SI_Long)2L) 
											    + 
											    ((UBYTE_16_ISAREF_1(array_constant_29,
											    length_1 
											    - 
											    (SI_Long)1L) 
											    & 
											    (SI_Long)8191L) 
											    << 
											    (SI_Long)16L);
										    if (wide_string_p) 
												{
											length_1 
												= 
												IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
											string_end_index 
												= 
												UBYTE_16_ISAREF_1(string_1,
												length_1 
												- 
												(SI_Long)2L) 
												+ 
												((UBYTE_16_ISAREF_1(string_1,
												length_1 
												- 
												(SI_Long)1L) 
												& 
												(SI_Long)8191L) 
												<< 
												(SI_Long)16L);
										    }
										    else
											string_end_index 
												= 
												IFIX(g2int_gensym_string_length(string_1));
										    i 
											    = 
											    (SI_Long)0L;
										    j 
											    = 
											    IFIX(forward_index);
										    c1 
											    = 
											    (SI_Long)0L;
										    c2 
											    = 
											    (SI_Long)0L;
										  next_loop_20:
										    if ( 
											    !(i 
											    < 
											    escape_end_index))
											goto end_loop_20;
										    temp 
											    = 
											    UBYTE_16_ISAREF_1(array_constant_29,
											    i);
										    i 
											    = 
											    i 
											    + 
											    (SI_Long)1L;
										    c1 
											    = 
											    temp;
										    if ( 
											    !(j 
											    < 
											    string_end_index)) 
												{
											temp_1 
												= 
												TRUEP(Nil);
											goto end_20;
										    }
										    if (wide_string_p) 
												{
											temp 
												= 
												UBYTE_16_ISAREF_1(string_1,
												j);
											j 
												= 
												j 
												+ 
												(SI_Long)1L;
											c2 
												= 
												temp;
										    }
										    else {
											temp_2 
												= 
												ICHAR(string_1,
												j);
											j 
												= 
												j 
												+ 
												(SI_Long)1L;
											c2 
												= 
												IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
										    }
										    if (c1 
											    != 
											    c2) 
												{
											temp_1 
												= 
												TRUEP(Nil);
											goto end_20;
										    }
										    goto next_loop_20;
										  end_loop_20:
										    forward_index 
											    = 
											    FIX(j);
										    temp_1 
											    = 
											    TRUEP(T);
										    goto end_20;
										    temp_1 
											    = 
											    TRUEP(Qnil);
										  end_20:;
										    if (temp_1)
											return VALUES_3(Qg2int_iso_646,
												forward_index,
												Qg2int_left);
										    else {
											forward_index 
												= 
												index_1;
											wide_string_p 
												= 
												INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
												!= 
												(SI_Long)0L;
											length_1 
												= 
												IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_30));
											escape_end_index 
												= 
												UBYTE_16_ISAREF_1(array_constant_30,
												length_1 
												- 
												(SI_Long)2L) 
												+ 
												((UBYTE_16_ISAREF_1(array_constant_30,
												length_1 
												- 
												(SI_Long)1L) 
												& 
												(SI_Long)8191L) 
												<< 
												(SI_Long)16L);
											if (wide_string_p) 
												    {
											    length_1 
												    = 
												    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
											    string_end_index 
												    = 
												    UBYTE_16_ISAREF_1(string_1,
												    length_1 
												    - 
												    (SI_Long)2L) 
												    + 
												    ((UBYTE_16_ISAREF_1(string_1,
												    length_1 
												    - 
												    (SI_Long)1L) 
												    & 
												    (SI_Long)8191L) 
												    << 
												    (SI_Long)16L);
											}
											else
											    string_end_index 
												    = 
												    IFIX(g2int_gensym_string_length(string_1));
											i 
												= 
												(SI_Long)0L;
											j 
												= 
												IFIX(forward_index);
											c1 
												= 
												(SI_Long)0L;
											c2 
												= 
												(SI_Long)0L;
										      next_loop_21:
											if ( 
												!(i 
												< 
												escape_end_index))
											    goto end_loop_21;
											temp 
												= 
												UBYTE_16_ISAREF_1(array_constant_30,
												i);
											i 
												= 
												i 
												+ 
												(SI_Long)1L;
											c1 
												= 
												temp;
											if ( 
												!(j 
												< 
												string_end_index)) 
												    {
											    temp_1 
												    = 
												    TRUEP(Nil);
											    goto end_21;
											}
											if (wide_string_p) 
												    {
											    temp 
												    = 
												    UBYTE_16_ISAREF_1(string_1,
												    j);
											    j 
												    = 
												    j 
												    + 
												    (SI_Long)1L;
											    c2 
												    = 
												    temp;
											}
											else {
											    temp_2 
												    = 
												    ICHAR(string_1,
												    j);
											    j 
												    = 
												    j 
												    + 
												    (SI_Long)1L;
											    c2 
												    = 
												    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
											}
											if (c1 
												!= 
												c2) 
												    {
											    temp_1 
												    = 
												    TRUEP(Nil);
											    goto end_21;
											}
											goto next_loop_21;
										      end_loop_21:
											forward_index 
												= 
												FIX(j);
											temp_1 
												= 
												TRUEP(T);
											goto end_21;
											temp_1 
												= 
												TRUEP(Qnil);
										      end_21:;
											if (temp_1)
											    return VALUES_3(Qg2int_iso_646,
												    forward_index,
												    Qg2int_left);
											else {
											    forward_index 
												    = 
												    index_1;
											    wide_string_p 
												    = 
												    INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) 
												    != 
												    (SI_Long)0L;
											    length_1 
												    = 
												    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_constant_31));
											    escape_end_index 
												    = 
												    UBYTE_16_ISAREF_1(array_constant_31,
												    length_1 
												    - 
												    (SI_Long)2L) 
												    + 
												    ((UBYTE_16_ISAREF_1(array_constant_31,
												    length_1 
												    - 
												    (SI_Long)1L) 
												    & 
												    (SI_Long)8191L) 
												    << 
												    (SI_Long)16L);
											    if (wide_string_p) 
													{
												length_1 
													= 
													IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
												string_end_index 
													= 
													UBYTE_16_ISAREF_1(string_1,
													length_1 
													- 
													(SI_Long)2L) 
													+ 
													((UBYTE_16_ISAREF_1(string_1,
													length_1 
													- 
													(SI_Long)1L) 
													& 
													(SI_Long)8191L) 
													<< 
													(SI_Long)16L);
											    }
											    else
												string_end_index 
													= 
													IFIX(g2int_gensym_string_length(string_1));
											    i 
												    = 
												    (SI_Long)0L;
											    j 
												    = 
												    IFIX(forward_index);
											    c1 
												    = 
												    (SI_Long)0L;
											    c2 
												    = 
												    (SI_Long)0L;
											  next_loop_22:
											    if ( 
												    !(i 
												    < 
												    escape_end_index))
												goto end_loop_22;
											    temp 
												    = 
												    UBYTE_16_ISAREF_1(array_constant_31,
												    i);
											    i 
												    = 
												    i 
												    + 
												    (SI_Long)1L;
											    c1 
												    = 
												    temp;
											    if ( 
												    !(j 
												    < 
												    string_end_index)) 
													{
												temp_1 
													= 
													TRUEP(Nil);
												goto end_22;
											    }
											    if (wide_string_p) 
													{
												temp 
													= 
													UBYTE_16_ISAREF_1(string_1,
													j);
												j 
													= 
													j 
													+ 
													(SI_Long)1L;
												c2 
													= 
													temp;
											    }
											    else {
												temp_2 
													= 
													ICHAR(string_1,
													j);
												j 
													= 
													j 
													+ 
													(SI_Long)1L;
												c2 
													= 
													IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
											    }
											    if (c1 
												    != 
												    c2) 
													{
												temp_1 
													= 
													TRUEP(Nil);
												goto end_22;
											    }
											    goto next_loop_22;
											  end_loop_22:
											    forward_index 
												    = 
												    FIX(j);
											    temp_1 
												    = 
												    TRUEP(T);
											    goto end_22;
											    temp_1 
												    = 
												    TRUEP(Qnil);
											  end_22:;
											    if (temp_1)
												return VALUES_3(Qg2int_iso_646,
													forward_index,
													Qg2int_left);
											    else
												return VALUES_2(Nil,
													index_1);
											}
										    }
										}
									    }
									}
								    }
								}
							    }
							}
						    }
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
}

/* HANDLE-ISO-2022-ESCAPE */
Object g2int_handle_iso_2022_escape(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    Object transcoder, text_sequence, graphic_character_set_name;
    Object forward_index, invocation_side, graphic_character_set_qm;
    SI_Long ab_loop_repeat_;
    Object result;

    x_note_fn_call(26,158);
    transcoder = iso_2022_transcoder;
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    result = g2int_read_iso_2022_escape_from_wide_string(ISVREF(text_sequence,
	    (SI_Long)1L),ISVREF(text_sequence,(SI_Long)6L));
    MVS_3(result,graphic_character_set_name,forward_index,invocation_side);
    ab_loop_repeat_ = IFIX(FIXNUM_MINUS(forward_index,ISVREF(text_sequence,
	    (SI_Long)6L)));
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    g2int_get_transcoder_character(transcoder);
    goto next_loop;
  end_loop:;
    graphic_character_set_qm = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(graphic_character_set_name),
	    Qg2int_graphic_character_set);
    if (graphic_character_set_qm) {
	if (EQ(invocation_side,Qg2int_left))
	    SVREF(transcoder,FIX((SI_Long)11L)) = graphic_character_set_qm;
	else if (EQ(invocation_side,Qg2int_right))
	    SVREF(transcoder,FIX((SI_Long)12L)) = graphic_character_set_qm;
    }
    ISVREF(transcoder,(SI_Long)3L) = FIX((SI_Long)65535L);
    ISVREF(transcoder,(SI_Long)2L) = FIX((SI_Long)65535L);
    return VALUES_1(Nil);
}

Object G2int_no_han_x_compound_text_character_set_selection_list = UNBOUND;

Object G2int_japanese_han_x_compound_text_character_set_selection_list = UNBOUND;

Object G2int_korean_han_x_compound_text_character_set_selection_list = UNBOUND;

Object G2int_chinese_han_x_compound_text_character_set_selection_list = UNBOUND;

Object G2int_default_han_x_compound_text_character_set_selection_list = UNBOUND;

Object G2int_text_conversion_style_for_transcoder_being_created = UNBOUND;

static Object Qg2int_japanese;     /* japanese */

static Object Qg2int_korean;       /* korean */

static Object Qg2int_chinese;      /* chinese */

/* SET-UP-ISO-2022-TRANSCODER-FOR-X-COMPOUND-TEXT */
Object g2int_set_up_iso_2022_transcoder_for_x_compound_text(transcoder)
    Object transcoder;
{
    Object temp, svref_new_value;

    x_note_fn_call(26,159);
    temp = ISVREF(G2int_text_conversion_style_for_transcoder_being_created,
	    (SI_Long)5L);
    if (EQ(temp,Qg2int_japanese))
	svref_new_value = 
		G2int_japanese_han_x_compound_text_character_set_selection_list;
    else if (EQ(temp,Qg2int_korean))
	svref_new_value = 
		G2int_korean_han_x_compound_text_character_set_selection_list;
    else if (EQ(temp,Qg2int_chinese))
	svref_new_value = 
		G2int_chinese_han_x_compound_text_character_set_selection_list;
    else
	svref_new_value = 
		G2int_default_han_x_compound_text_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object G2int_us_ascii_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-US-ASCII */
Object g2int_set_up_iso_2022_transcoder_for_us_ascii(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,160);
    svref_new_value = G2int_us_ascii_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)11L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object G2int_ks_c_5601_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-KS-C-5601 */
Object g2int_set_up_iso_2022_transcoder_for_ks_c_5601(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,161);
    svref_new_value = G2int_ks_c_5601_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object G2int_ks_c_5601_euc_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-KS-C-5601-EUC */
Object g2int_set_up_iso_2022_transcoder_for_ks_c_5601_euc(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,162);
    svref_new_value = G2int_ks_c_5601_euc_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = T;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)8L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object G2int_gb_2312_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-GB-2312 */
Object g2int_set_up_iso_2022_transcoder_for_gb_2312(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,163);
    svref_new_value = G2int_gb_2312_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object G2int_gb_2312_euc_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-GB-2312-EUC */
Object g2int_set_up_iso_2022_transcoder_for_gb_2312_euc(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,164);
    svref_new_value = G2int_gb_2312_euc_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = T;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)8L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object G2int_jis_x_0208_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-JIS-X-0208 */
Object g2int_set_up_iso_2022_transcoder_for_jis_x_0208(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,165);
    svref_new_value = G2int_jis_x_0208_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object G2int_jis_x_0208_euc_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-JIS-X-0208-EUC */
Object g2int_set_up_iso_2022_transcoder_for_jis_x_0208_euc(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,166);
    svref_new_value = G2int_jis_x_0208_euc_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = T;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)8L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* TRANSCODE-ISO-2022-C1-CHARACTER */
Object g2int_transcode_iso_2022_c1_character(character_1,transcoder)
    Object character_1, transcoder;
{
    x_note_fn_call(26,167);
    return g2int_transcode_unhandled_character(character_1,transcoder);
}

static Object Qg2int_gl;           /* gl */

/* TRANSCODE-ISO-2022-GRAPHIC-CHARACTER */
Object g2int_transcode_iso_2022_graphic_character(character_init,
	    transcoder,zone)
    Object character_init, transcoder, zone;
{
    Object graphic_character_set, text_sequence, gensymed_symbol;
    Object gensymed_symbol_1, temp, svref_new_value;
    SI_Long character_1, gensymed_symbol_2, trail_character, arg, arg_1, arg_2;
    SI_Long lead_octet, trail_octet, lead_7_bit_octet, trail_7_bit_octet;

    x_note_fn_call(26,168);
    character_1 = IFIX(character_init);
    graphic_character_set = EQ(zone,Qg2int_gl) ? ISVREF(transcoder,
	    (SI_Long)11L) : ISVREF(transcoder,(SI_Long)12L);
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    if (IFIX(ISVREF(graphic_character_set,(SI_Long)3L)) == (SI_Long)1L) {
	gensymed_symbol = ISVREF(graphic_character_set,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)18L);
	gensymed_symbol_1 = graphic_character_set;
	gensymed_symbol_2 = character_1 & (SI_Long)127L;
	temp = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		FIX(gensymed_symbol_2));
    }
    else if (IFIX(ISVREF(graphic_character_set,(SI_Long)3L)) == (SI_Long)2L) {
	if (FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
		ISVREF(text_sequence,(SI_Long)3L))) {
	    ISVREF(transcoder,(SI_Long)3L) = FIX(character_1);
	    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)11L);
	    gensymed_symbol_1 = text_sequence;
	    svref_new_value = inline_funcall_1(gensymed_symbol,
		    gensymed_symbol_1);
	    SVREF(transcoder,FIX((SI_Long)2L)) = svref_new_value;
	    trail_character = IFIX(ISVREF(transcoder,(SI_Long)2L)) & 
		    (SI_Long)127L;
	    arg = (SI_Long)32L;
	    arg_1 = trail_character;
	    arg_2 = (SI_Long)128L;
	    if (arg <= arg_1 && arg_1 <= arg_2) {
		gensymed_symbol = ISVREF(graphic_character_set,(SI_Long)0L);
		gensymed_symbol = 
			ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			Qg2int_type_description_of_unique_type_name_of_gensym_structure),
			(SI_Long)9L),(SI_Long)18L);
		gensymed_symbol_1 = graphic_character_set;
		lead_octet = character_1;
		trail_octet = trail_character;
		lead_7_bit_octet = lead_octet & (SI_Long)127L;
		trail_7_bit_octet = trail_octet & (SI_Long)127L;
		gensymed_symbol_2 = (lead_7_bit_octet << (SI_Long)8L) + 
			trail_7_bit_octet;
		temp = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			FIX(gensymed_symbol_2));
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    else
	temp = Qnil;
    if (temp);
    else
	temp = g2int_transcode_unhandled_character(FIX(character_1),
		transcoder);
    return VALUES_1(temp);
}

static Object Qg2int_gr;           /* gr */

/* TRANSCODE-CHARACTER-FOR-ISO-2022-TRANSCODER */
Object g2int_transcode_character_for_iso_2022_transcoder(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    Object transcoder, result_character, temp;
    SI_Long character_1;

    x_note_fn_call(26,169);
    transcoder = iso_2022_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    if (character_1 < (SI_Long)32L) {
	if (character_1 == (SI_Long)10L && IFIX(ISVREF(transcoder,
		(SI_Long)3L)) == (SI_Long)13L)
	    result_character = FIX((SI_Long)65535L);
	else if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L)
	    result_character = FIX((SI_Long)8232L);
	else
	    result_character = FIX(character_1);
	temp = result_character;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    return VALUES_1(result_character);
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 27:
		g2int_handle_iso_2022_escape(transcoder);
		return VALUES_1(FIX((SI_Long)65535L));
	      default:
		return VALUES_1(result_character);
	    }
    }
    else if (character_1 < (SI_Long)128L)
	return g2int_transcode_iso_2022_graphic_character(FIX(character_1),
		transcoder,Qg2int_gl);
    else {
	if (ISVREF(transcoder,(SI_Long)6L)) {
	    if (character_1 < (SI_Long)160L)
		temp = 
			g2int_transcode_iso_2022_c1_character(FIX(character_1),
			transcoder);
	    else if (character_1 < (SI_Long)256L)
		temp = 
			g2int_transcode_iso_2022_graphic_character(FIX(character_1),
			transcoder,Qg2int_gr);
	    else
		temp = Qnil;
	}
	else
	    temp = Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return g2int_transcode_unhandled_character(FIX(character_1),
		    transcoder);
    }
}

/* EXPORT-CHARACTER-FOR-ISO-2022-TRANSCODER */
Object g2int_export_character_for_iso_2022_transcoder(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    Object transcoder, set_1, invocation_side, svref_new_value, i, string_1;
    Object temp_1, set_selection_list, code, side, ab_loop_list_;
    Object ab_loop_desetq_, gensymed_symbol, gensymed_symbol_1, character_3;
    SI_Long character_1, arg, arg_1, arg_2, character_2, length_1;
    SI_Long gensymed_symbol_2;
    char temp;

    x_note_fn_call(26,170);
    transcoder = iso_2022_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    temp = character_1 < (SI_Long)32L;
    if (temp);
    else
	temp = character_1 == (SI_Long)8232L;
    if (temp);
    else
	temp = character_1 == (SI_Long)8233L;
    if (temp);
    else
	temp = character_1 == (SI_Long)127L;
    if (temp);
    else {
	arg = (SI_Long)127L;
	arg_1 = character_1;
	arg_2 = (SI_Long)160L;
	temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
    }
    if (temp) {
	if (g2int_newline_p(FIX(character_1))) {
	    set_1 = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
		    Qg2int_graphic_character_set);
	    iso_2022_transcoder = transcoder;
	    invocation_side = Qg2int_left;
	    if (EQ(invocation_side,Qg2int_left)) {
		if ( !EQ(set_1,ISVREF(iso_2022_transcoder,(SI_Long)11L))) {
		    SVREF(iso_2022_transcoder,FIX((SI_Long)11L)) = set_1;
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)27L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    if (IFIX(ISVREF(set_1,(SI_Long)3L)) > (SI_Long)1L) {
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX((SI_Long)36L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)40L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    i = FIX((SI_Long)0L);
		    string_1 = ISVREF(set_1,(SI_Long)5L);
		  next_loop:
		    character_2 = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_2),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    i = FIXNUM_ADD1(i);
		    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
		    if ( !FIXNUM_LT(i,FIX(UBYTE_16_ISAREF_1(string_1,
			    length_1 - (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(string_1,length_1 - 
			    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L))))
			goto end_loop;
		    goto next_loop;
		  end_loop:;
		}
	    }
	    else if (EQ(invocation_side,Qg2int_right)) {
		if ( !EQ(set_1,ISVREF(iso_2022_transcoder,(SI_Long)12L))) {
		    SVREF(iso_2022_transcoder,FIX((SI_Long)12L)) = set_1;
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)27L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    if (IFIX(ISVREF(set_1,(SI_Long)4L)) == (SI_Long)94L) {
			if (IFIX(ISVREF(set_1,(SI_Long)3L)) > (SI_Long)1L) {
			    svref_new_value = 
				    nconc2(ISVREF(iso_2022_transcoder,
				    (SI_Long)5L),
				    g2int_gensym_cons_1(FIX((SI_Long)36L),
				    Nil));
			    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				    svref_new_value;
			}
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX((SI_Long)41L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    else {
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX((SI_Long)45L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    i = FIX((SI_Long)0L);
		    string_1 = ISVREF(set_1,(SI_Long)5L);
		  next_loop_1:
		    character_2 = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_2),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    i = FIXNUM_ADD1(i);
		    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
		    if ( !FIXNUM_LT(i,FIX(UBYTE_16_ISAREF_1(string_1,
			    length_1 - (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(string_1,length_1 - 
			    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L))))
			goto end_loop_1;
		    goto next_loop_1;
		  end_loop_1:;
		}
	    }
	}
	if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	    temp_1 = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	    if (EQ(temp_1,Qg2int_per_platform)) {
		if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
			EQ(G2int_g2_operating_system,Qg2int_vms) || 
			EQ(G2int_g2_operating_system,Qg2int_win32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp_1,Qg2int_cr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp_1,Qg2int_lf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp_1,Qg2int_crlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp_1,Qg2int_unicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp_1,Qg2int_unicode_paragraph_separator))
		return VALUES_1(FIX((SI_Long)8233L));
	    else
		return VALUES_1(FIX(character_1));
	}
	else
	    return VALUES_1(FIX(character_1));
    }
    else {
	set_selection_list = ISVREF(transcoder,(SI_Long)13L);
	code = Nil;
	set_1 = Nil;
	side = Nil;
	ab_loop_list_ = set_selection_list;
	ab_loop_desetq_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	set_1 = CAR(ab_loop_desetq_);
	temp_1 = CDR(ab_loop_desetq_);
	side = CAR(temp_1);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(set_1,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)19L);
	gensymed_symbol_1 = set_1;
	gensymed_symbol_2 = character_1;
	code = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		FIX(gensymed_symbol_2));
	if (code) {
	    if (EQ(side,Qg2int_left)) {
		if ( !EQ(set_1,ISVREF(transcoder,(SI_Long)11L))) {
		    SVREF(transcoder,FIX((SI_Long)11L)) = set_1;
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)27L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    if (IFIX(ISVREF(set_1,(SI_Long)3L)) > (SI_Long)1L) {
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX((SI_Long)36L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)40L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    i = FIX((SI_Long)0L);
		    string_1 = ISVREF(set_1,(SI_Long)5L);
		  next_loop_3:
		    character_2 = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_2),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    i = FIXNUM_ADD1(i);
		    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
		    if ( !FIXNUM_LT(i,FIX(UBYTE_16_ISAREF_1(string_1,
			    length_1 - (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(string_1,length_1 - 
			    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L))))
			goto end_loop_3;
		    goto next_loop_3;
		  end_loop_3:;
		}
	    }
	    else if (EQ(side,Qg2int_right)) {
		if ( !EQ(set_1,ISVREF(transcoder,(SI_Long)12L))) {
		    SVREF(transcoder,FIX((SI_Long)12L)) = set_1;
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)27L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    if (IFIX(ISVREF(set_1,(SI_Long)4L)) == (SI_Long)94L) {
			if (IFIX(ISVREF(set_1,(SI_Long)3L)) > (SI_Long)1L) {
			    svref_new_value = 
				    nconc2(ISVREF(iso_2022_transcoder,
				    (SI_Long)5L),
				    g2int_gensym_cons_1(FIX((SI_Long)36L),
				    Nil));
			    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				    svref_new_value;
			}
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX((SI_Long)41L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    else {
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX((SI_Long)45L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    i = FIX((SI_Long)0L);
		    string_1 = ISVREF(set_1,(SI_Long)5L);
		  next_loop_4:
		    character_2 = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_2),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    i = FIXNUM_ADD1(i);
		    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
		    if ( !FIXNUM_LT(i,FIX(UBYTE_16_ISAREF_1(string_1,
			    length_1 - (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(string_1,length_1 - 
			    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L))))
			goto end_loop_4;
		    goto next_loop_4;
		  end_loop_4:;
		}
	    }
	    if (IFIX(ISVREF(set_1,(SI_Long)3L)) == (SI_Long)1L) {
		character_3 = EQ(side,Qg2int_left) ? code : FIX(IFIX(code) 
			| (SI_Long)128L);
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(character_3,Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    }
	    else {
		character_2 = EQ(side,Qg2int_left) ? IFIX(code) >>  -  - 
			(SI_Long)8L & (SI_Long)127L : IFIX(code) >>  -  - 
			(SI_Long)8L & (SI_Long)127L | (SI_Long)128L;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX(character_2),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = EQ(side,Qg2int_left) ? IFIX(code) & 
			(SI_Long)127L : IFIX(code) & (SI_Long)127L | 
			(SI_Long)128L;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX(character_2),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    }
	    return VALUES_1(FIX((SI_Long)65535L));
	}
	goto next_loop_2;
      end_loop_2:
	return g2int_transcode_unhandled_character(FIX(character_1),
		transcoder);
	return VALUES_1(Qnil);
    }
}

Object G2int_the_type_description_of_shift_jis_transcoder = UNBOUND;

Object G2int_chain_of_available_shift_jis_transcoders = UNBOUND;

Object G2int_shift_jis_transcoder_count = UNBOUND;

/* RECLAIM-SHIFT-JIS-TRANSCODER-1 */
Object g2int_reclaim_shift_jis_transcoder_1(shift_jis_transcoder)
    Object shift_jis_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,171);
    inline_note_reclaim_cons(shift_jis_transcoder,Nil);
    svref_new_value = G2int_chain_of_available_shift_jis_transcoders;
    SVREF(shift_jis_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_shift_jis_transcoders = shift_jis_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SHIFT-JIS-TRANSCODER */
Object g2int_reclaim_structure_for_shift_jis_transcoder(shift_jis_transcoder)
    Object shift_jis_transcoder;
{
    x_note_fn_call(26,172);
    return g2int_reclaim_shift_jis_transcoder_1(shift_jis_transcoder);
}

static Object Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct;  /* g2-defstruct-structure-name::shift-jis-transcoder-g2-struct */

/* MAKE-PERMANENT-SHIFT-JIS-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_shift_jis_transcoder_structure_internal()
{
    Object def_structure_shift_jis_transcoder_variable, temp;
    Object defstruct_g2_shift_jis_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,173);
    def_structure_shift_jis_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_shift_jis_transcoder_count);
    G2int_shift_jis_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_shift_jis_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)7L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_shift_jis_transcoder_variable = the_array;
	SVREF(defstruct_g2_shift_jis_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct;
	SVREF(defstruct_g2_shift_jis_transcoder_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_shift_jis_transcoder_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_shift_jis_transcoder_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_shift_jis_transcoder_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_shift_jis_transcoder_variable,FIX((SI_Long)5L)) 
		= Nil;
	def_structure_shift_jis_transcoder_variable = 
		defstruct_g2_shift_jis_transcoder_variable;
	SVREF(def_structure_shift_jis_transcoder_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_shift_jis_transcoder_variable,
		FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_shift_jis_transcoders;
	SVREF(def_structure_shift_jis_transcoder_variable,
		FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_shift_jis_transcoders = 
		def_structure_shift_jis_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_shift_jis_transcoder_variable);
}

/* MAKE-SHIFT-JIS-TRANSCODER-1 */
Object g2int_make_shift_jis_transcoder_1()
{
    Object def_structure_shift_jis_transcoder_variable, svref_new_value;

    x_note_fn_call(26,174);
    def_structure_shift_jis_transcoder_variable = 
	    G2int_chain_of_available_shift_jis_transcoders;
    if (def_structure_shift_jis_transcoder_variable) {
	G2int_chain_of_available_shift_jis_transcoders = 
		ISVREF(def_structure_shift_jis_transcoder_variable,
		(SI_Long)0L);
	SVREF(def_structure_shift_jis_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct;
    }
    else
	def_structure_shift_jis_transcoder_variable = 
		g2int_make_permanent_shift_jis_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_shift_jis_transcoder_variable,Nil);
    ISVREF(def_structure_shift_jis_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_shift_jis_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_shift_jis_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    svref_new_value = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    SVREF(def_structure_shift_jis_transcoder_variable,FIX((SI_Long)6L)) = 
	    svref_new_value;
    return VALUES_1(def_structure_shift_jis_transcoder_variable);
}

/* MAKE-SHIFT-JIS-TRANSCODER-FUNCTION */
Object g2int_make_shift_jis_transcoder_function()
{
    x_note_fn_call(26,175);
    return g2int_make_shift_jis_transcoder_1();
}

/* TRANSCODE-CHARACTER-FOR-SHIFT-JIS-TRANSCODER */
Object g2int_transcode_character_for_shift_jis_transcoder(shift_jis_transcoder)
    Object shift_jis_transcoder;
{
    Object transcoder, result_character, temp, trail_character, lead_octet;
    Object trail_octet, c1, c2, structure, gensymed_symbol_2;
    Object gensymed_symbol_3;
    SI_Long character_1, arg, arg_1, arg_2, lead_character, row_offset;
    SI_Long cell_offset, gensymed_symbol, gensymed_symbol_1, double_byte_code;
    char temp_1, adjust_p;

    x_note_fn_call(26,176);
    transcoder = shift_jis_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    if (character_1 < (SI_Long)32L) {
	if (character_1 == (SI_Long)10L && IFIX(ISVREF(transcoder,
		(SI_Long)3L)) == (SI_Long)13L)
	    result_character = FIX((SI_Long)65535L);
	else if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L)
	    result_character = FIX((SI_Long)8232L);
	else
	    result_character = FIX(character_1);
	temp = result_character;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    return VALUES_1(result_character);
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 27:
		g2int_handle_iso_2022_escape(transcoder);
		return VALUES_1(FIX((SI_Long)65535L));
	      default:
		return VALUES_1(result_character);
	    }
    }
    else if (character_1 < (SI_Long)128L)
	return VALUES_1(FIX(character_1));
    else {
	arg = (SI_Long)161L;
	arg_1 = character_1;
	arg_2 = (SI_Long)223L;
	if (arg <= arg_1 && arg_1 <= arg_2)
	    return VALUES_1(FIX((SI_Long)65377L + (character_1 - 
		    (SI_Long)161L)));
	else {
	    arg = (SI_Long)129L;
	    arg_1 = character_1;
	    arg_2 = (SI_Long)159L;
	    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	    if (temp_1);
	    else {
		arg = (SI_Long)224L;
		arg_1 = character_1;
		arg_2 = (SI_Long)239L;
		temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	    }
	    if (temp_1);
	    else {
		arg = (SI_Long)240L;
		arg_1 = character_1;
		arg_2 = (SI_Long)252L;
		temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	    }
	    if (temp_1) {
		lead_character = character_1;
		trail_character = 
			g2int_get_transcoder_character_if_any(transcoder);
		if (trail_character);
		else
		    return g2int_transcode_unhandled_character(FIX(character_1),
			    transcoder);
		lead_octet = FIX(lead_character & (SI_Long)255L);
		trail_octet = FIX(IFIX(trail_character) & (SI_Long)255L);
		c1 = lead_octet;
		c2 = trail_octet;
		adjust_p = IFIX(c2) < (SI_Long)159L;
		row_offset = IFIX(c1) < (SI_Long)160L ? (SI_Long)112L : 
			(SI_Long)176L;
		cell_offset = adjust_p ? (IFIX(c2) > (SI_Long)127L ? 
			(SI_Long)32L : (SI_Long)31L) : (SI_Long)126L;
		gensymed_symbol = IFIX(c1) - row_offset << (SI_Long)1L;
		gensymed_symbol_1 = adjust_p ? (SI_Long)1L : (SI_Long)0L;
		lead_octet = FIX(gensymed_symbol - gensymed_symbol_1);
		trail_octet = FIX(IFIX(trail_octet) - cell_offset);
		double_byte_code = (IFIX(lead_octet) << (SI_Long)8L) + 
			IFIX(trail_octet);
		structure = ISVREF(transcoder,(SI_Long)6L);
		gensymed_symbol_2 = ISVREF(structure,(SI_Long)0L);
		gensymed_symbol_2 = 
			ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol_2),
			Qg2int_type_description_of_unique_type_name_of_gensym_structure),
			(SI_Long)9L),(SI_Long)18L);
		gensymed_symbol_3 = structure;
		gensymed_symbol = double_byte_code;
		return VALUES_1(inline_funcall_2(gensymed_symbol_2,
			gensymed_symbol_3,FIX(gensymed_symbol)));
	    }
	    else
		return g2int_transcode_unhandled_character(FIX(character_1),
			transcoder);
	}
    }
}

/* EXPORT-CHARACTER-FOR-SHIFT-JIS-TRANSCODER */
Object g2int_export_character_for_shift_jis_transcoder(shift_jis_transcoder)
    Object shift_jis_transcoder;
{
    Object transcoder, temp_1, svref_new_value, cjk_code_mapping_vector, l;
    Object jis_code_qm, jis_code, lead_octet, trail_octet, c1, c2, character_2;
    SI_Long character_1, arg, arg_1, arg_2, unicode, cjk_code, temp_2;
    SI_Long row_offset, cell_offset;
    char temp;

    x_note_fn_call(26,177);
    transcoder = shift_jis_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    temp = character_1 < (SI_Long)32L;
    if (temp);
    else
	temp = character_1 == (SI_Long)8232L;
    if (temp);
    else
	temp = character_1 == (SI_Long)8233L;
    if (temp);
    else
	temp = character_1 == (SI_Long)127L;
    if (temp);
    else {
	arg = (SI_Long)127L;
	arg_1 = character_1;
	arg_2 = (SI_Long)160L;
	temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
    }
    if (temp) {
	if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	    temp_1 = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	    if (EQ(temp_1,Qg2int_per_platform)) {
		if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
			EQ(G2int_g2_operating_system,Qg2int_vms) || 
			EQ(G2int_g2_operating_system,Qg2int_win32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp_1,Qg2int_cr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp_1,Qg2int_lf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp_1,Qg2int_crlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp_1,Qg2int_unicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp_1,Qg2int_unicode_paragraph_separator))
		return VALUES_1(FIX((SI_Long)8233L));
	    else
		return VALUES_1(FIX(character_1));
	}
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 < (SI_Long)128L)
	return VALUES_1(FIX(character_1));
    else {
	unicode = character_1;
	cjk_code = unicode;
	cjk_code_mapping_vector = G2int_unicode_to_jis_x_0208_map;
	temp_2 = cjk_code % (SI_Long)307L;
	l = ISVREF(cjk_code_mapping_vector,temp_2);
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (IFIX(CAR(l)) == cjk_code) {
	    jis_code_qm = CADR(l);
	    goto end;
	}
	l = CDDR(l);
	goto next_loop;
      end_loop:
	jis_code_qm = Qnil;
      end:;
	if (jis_code_qm) {
	    jis_code = jis_code_qm;
	    lead_octet = FIX(IFIX(jis_code) >>  -  - (SI_Long)8L & 
		    (SI_Long)127L);
	    trail_octet = FIX(IFIX(jis_code) & (SI_Long)127L);
	    c1 = lead_octet;
	    c2 = trail_octet;
	    row_offset = IFIX(c1) < (SI_Long)95L ? (SI_Long)112L : 
		    (SI_Long)176L;
	    cell_offset = FIXNUM_ODDP(c1) ? (IFIX(c2) > (SI_Long)95L ? 
		    (SI_Long)32L : (SI_Long)31L) : (SI_Long)126L;
	    lead_octet = FIX((IFIX(FIXNUM_ADD1(c1)) >>  -  - (SI_Long)1L) 
		    + row_offset);
	    trail_octet = FIX(IFIX(trail_octet) + cell_offset);
	    character_2 = trail_octet;
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    g2int_gensym_cons_1(character_2,Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    return VALUES_1(lead_octet);
	}
	else
	    return g2int_transcode_unhandled_character(FIX(character_1),
		    transcoder);
    }
}

Object G2int_the_type_description_of_utf_g_transcoder = UNBOUND;

Object G2int_chain_of_available_utf_g_transcoders = UNBOUND;

Object G2int_utf_g_transcoder_count = UNBOUND;

/* RECLAIM-UTF-G-TRANSCODER-1 */
Object g2int_reclaim_utf_g_transcoder_1(utf_g_transcoder)
    Object utf_g_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,178);
    inline_note_reclaim_cons(utf_g_transcoder,Nil);
    svref_new_value = G2int_chain_of_available_utf_g_transcoders;
    SVREF(utf_g_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_utf_g_transcoders = utf_g_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UTF-G-TRANSCODER */
Object g2int_reclaim_structure_for_utf_g_transcoder(utf_g_transcoder)
    Object utf_g_transcoder;
{
    x_note_fn_call(26,179);
    return g2int_reclaim_utf_g_transcoder_1(utf_g_transcoder);
}

static Object Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct;  /* g2-defstruct-structure-name::utf-g-transcoder-g2-struct */

/* MAKE-PERMANENT-UTF-G-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_utf_g_transcoder_structure_internal()
{
    Object def_structure_utf_g_transcoder_variable, temp;
    Object defstruct_g2_utf_g_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,180);
    def_structure_utf_g_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_utf_g_transcoder_count);
    G2int_utf_g_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_utf_g_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_utf_g_transcoder_variable = the_array;
	SVREF(defstruct_g2_utf_g_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct;
	SVREF(defstruct_g2_utf_g_transcoder_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_utf_g_transcoder_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_utf_g_transcoder_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_utf_g_transcoder_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_utf_g_transcoder_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_utf_g_transcoder_variable = 
		defstruct_g2_utf_g_transcoder_variable;
	SVREF(def_structure_utf_g_transcoder_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_utf_g_transcoder_variable,FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_utf_g_transcoders;
	SVREF(def_structure_utf_g_transcoder_variable,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_utf_g_transcoders = 
		def_structure_utf_g_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_utf_g_transcoder_variable);
}

/* MAKE-UTF-G-TRANSCODER-1 */
Object g2int_make_utf_g_transcoder_1()
{
    Object def_structure_utf_g_transcoder_variable;

    x_note_fn_call(26,181);
    def_structure_utf_g_transcoder_variable = 
	    G2int_chain_of_available_utf_g_transcoders;
    if (def_structure_utf_g_transcoder_variable) {
	G2int_chain_of_available_utf_g_transcoders = 
		ISVREF(def_structure_utf_g_transcoder_variable,(SI_Long)0L);
	SVREF(def_structure_utf_g_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct;
    }
    else
	def_structure_utf_g_transcoder_variable = 
		g2int_make_permanent_utf_g_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_utf_g_transcoder_variable,Nil);
    ISVREF(def_structure_utf_g_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_utf_g_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_utf_g_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    ISVREF(def_structure_utf_g_transcoder_variable,(SI_Long)6L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_utf_g_transcoder_variable,(SI_Long)7L) = 
	    FIX((SI_Long)65535L);
    return VALUES_1(def_structure_utf_g_transcoder_variable);
}

/* GET-UTF-G-TRANSCODER-CODE */
Object g2int_get_utf_g_transcoder_code(character_init,transcoder)
    Object character_init, transcoder;
{
    Object character_or_character_code, escape_character_qm, temp_1;
    Object first_code, second_code;
    SI_Long character_1, temp, code, result_1, character_or_character_code_1;

    x_note_fn_call(26,182);
    character_1 = IFIX(character_init);
    temp = character_1;
    if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L)) {
	character_or_character_code = CODE_CHAR(FIX(character_1));
	escape_character_qm = Nil;
	if ( !TRUEP(escape_character_qm))
	    temp_1 = CHAR_CODE(character_or_character_code);
	else {
	    if (CHAR_EQ(escape_character_qm,CHR('~'))) {
		temp_1 = 
			ISVREF(G2int_reverse_iso_latin1_special_character_code_map,
			IFIX(CHAR_CODE(character_or_character_code)));
		if (temp_1);
		else {
		    temp_1 = CHAR_CODE(character_or_character_code);
		    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			temp_1 = Nil;
		    else
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 87:
			    temp_1 = G2int_gensym_code_for_capital_ligature_oe;
			    break;
			  case 119:
			    temp_1 = G2int_gensym_code_for_small_ligature_oe;
			    break;
			  case 42:
			    temp_1 = G2int_gensym_code_for_bullet;
			    break;
			  case 38:
			    temp_1 = 
				    G2int_gensym_code_for_small_letter_f_with_hook;
			    break;
			  case 58:
			    temp_1 = G2int_gensym_code_for_trade_mark_sign;
			    break;
			  default:
			    temp_1 = Nil;
			    break;
			}
		}
	    }
	    else
		temp_1 = Nil;
	    if (temp_1);
	    else if ( !TRUEP(escape_character_qm) &&  
		    !TRUEP(G2int_gensym_esc_for_linebreakqm) ? 
		    CHAR_EQ(character_or_character_code,
		    G2int_gensym_char_or_code_for_linebreak) : 
		    EQ(character_or_character_code,
		    G2int_gensym_char_or_code_for_linebreak) && 
		    EQ(escape_character_qm,G2int_gensym_esc_for_linebreakqm))
		temp_1 = G2int_gensym_code_for_linebreak;
	    else if ( !TRUEP(escape_character_qm) &&  
		    !TRUEP(G2int_gensym_esc_for_paragraph_breakqm) ? 
		    CHAR_EQ(character_or_character_code,
		    G2int_gensym_char_or_code_for_paragraph_break) : 
		    EQ(character_or_character_code,
		    G2int_gensym_char_or_code_for_paragraph_break) && 
		    EQ(escape_character_qm,
		    G2int_gensym_esc_for_paragraph_breakqm))
		temp_1 = G2int_gensym_code_for_paragraph_break;
	    else {
		temp_1 =  !EQ(escape_character_qm,CHR('\\')) ? 
			FIX((SI_Long)65535L) : Nil;
		if (temp_1);
		else
		    temp_1 = character_or_character_code;
	    }
	}
    }
    else
	switch ((char)temp) {
	  case 64:
	  case 126:
	    temp_1 = g2int_get_transcoder_character_if_any(transcoder);
	    if (temp_1);
	    else {
		temp_1 = FIX((SI_Long)65535L);
		goto end_exhausted;
	    }
	    character_or_character_code = CODE_CHAR(temp_1);
	    escape_character_qm = CODE_CHAR(FIX(character_1));
	    if ( !TRUEP(escape_character_qm))
		temp_1 = CHAR_CODE(character_or_character_code);
	    else {
		if (CHAR_EQ(escape_character_qm,CHR('~'))) {
		    temp_1 = 
			    ISVREF(G2int_reverse_iso_latin1_special_character_code_map,
			    IFIX(CHAR_CODE(character_or_character_code)));
		    if (temp_1);
		    else {
			temp_1 = CHAR_CODE(character_or_character_code);
			if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    temp_1 = Nil;
			else
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 87:
				temp_1 = 
					G2int_gensym_code_for_capital_ligature_oe;
				break;
			      case 119:
				temp_1 = 
					G2int_gensym_code_for_small_ligature_oe;
				break;
			      case 42:
				temp_1 = G2int_gensym_code_for_bullet;
				break;
			      case 38:
				temp_1 = 
					G2int_gensym_code_for_small_letter_f_with_hook;
				break;
			      case 58:
				temp_1 = G2int_gensym_code_for_trade_mark_sign;
				break;
			      default:
				temp_1 = Nil;
				break;
			    }
		    }
		}
		else
		    temp_1 = Nil;
		if (temp_1);
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(G2int_gensym_esc_for_linebreakqm) ? 
			CHAR_EQ(character_or_character_code,
			G2int_gensym_char_or_code_for_linebreak) : 
			EQ(character_or_character_code,
			G2int_gensym_char_or_code_for_linebreak) && 
			EQ(escape_character_qm,
			G2int_gensym_esc_for_linebreakqm))
		    temp_1 = G2int_gensym_code_for_linebreak;
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(G2int_gensym_esc_for_paragraph_breakqm) ? 
			CHAR_EQ(character_or_character_code,
			G2int_gensym_char_or_code_for_paragraph_break) : 
			EQ(character_or_character_code,
			G2int_gensym_char_or_code_for_paragraph_break) && 
			EQ(escape_character_qm,
			G2int_gensym_esc_for_paragraph_breakqm))
		    temp_1 = G2int_gensym_code_for_paragraph_break;
		else {
		    temp_1 =  !EQ(escape_character_qm,CHR('\\')) ? 
			    FIX((SI_Long)65535L) : Nil;
		    if (temp_1);
		    else
			temp_1 = character_or_character_code;
		}
	    }
	    break;
	  case 92:
	    temp_1 = g2int_get_transcoder_character_if_any(transcoder);
	    if (temp_1);
	    else {
		temp_1 = FIX((SI_Long)65535L);
		goto end_exhausted;
	    }
	    code = IFIX(temp_1);
	    if (code < (SI_Long)40L) {
		first_code = g2int_get_transcoder_character_if_any(transcoder);
		if (first_code);
		else {
		    temp_1 = FIX((SI_Long)65535L);
		    goto end_exhausted;
		}
		second_code = 
			g2int_get_transcoder_character_if_any(transcoder);
		if (second_code);
		else {
		    temp_1 = FIX((SI_Long)65535L);
		    goto end_exhausted;
		}
		result_1 = (code << (SI_Long)13L) + (SI_Long)95L * 
			IFIX(first_code) + IFIX(second_code) + 
			(SI_Long)-265976L;
		if ( !((SI_Long)0L <= result_1 && result_1 <= 
			    (SI_Long)65535L)) {
		    temp_1 = FIX((SI_Long)65535L);
		    goto end_exhausted;
		}
		else
		    character_or_character_code_1 = result_1;
	    }
	    else {
		first_code = g2int_get_transcoder_character_if_any(transcoder);
		if (first_code);
		else {
		    temp_1 = FIX((SI_Long)65535L);
		    goto end_exhausted;
		}
		character_or_character_code_1 = (SI_Long)95L * code + 
			IFIX(first_code) + (SI_Long)4360L;
	    }
	    escape_character_qm = CODE_CHAR(FIX(character_1));
	    if ( !TRUEP(escape_character_qm))
		temp_1 = CHAR_CODE(FIX(character_or_character_code_1));
	    else {
		if (CHAR_EQ(escape_character_qm,CHR('~'))) {
		    temp_1 = 
			    ISVREF(G2int_reverse_iso_latin1_special_character_code_map,
			    IFIX(CHAR_CODE(FIX(character_or_character_code_1))));
		    if (temp_1);
		    else {
			temp_1 = CHAR_CODE(FIX(character_or_character_code_1));
			if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    temp_1 = Nil;
			else
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 87:
				temp_1 = 
					G2int_gensym_code_for_capital_ligature_oe;
				break;
			      case 119:
				temp_1 = 
					G2int_gensym_code_for_small_ligature_oe;
				break;
			      case 42:
				temp_1 = G2int_gensym_code_for_bullet;
				break;
			      case 38:
				temp_1 = 
					G2int_gensym_code_for_small_letter_f_with_hook;
				break;
			      case 58:
				temp_1 = G2int_gensym_code_for_trade_mark_sign;
				break;
			      default:
				temp_1 = Nil;
				break;
			    }
		    }
		}
		else
		    temp_1 = Nil;
		if (temp_1);
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(G2int_gensym_esc_for_linebreakqm) ? 
			CHAR_EQ(FIX(character_or_character_code_1),
			G2int_gensym_char_or_code_for_linebreak) : 
			EQ(FIX(character_or_character_code_1),
			G2int_gensym_char_or_code_for_linebreak) && 
			EQ(escape_character_qm,
			G2int_gensym_esc_for_linebreakqm))
		    temp_1 = G2int_gensym_code_for_linebreak;
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(G2int_gensym_esc_for_paragraph_breakqm) ? 
			CHAR_EQ(FIX(character_or_character_code_1),
			G2int_gensym_char_or_code_for_paragraph_break) : 
			EQ(FIX(character_or_character_code_1),
			G2int_gensym_char_or_code_for_paragraph_break) && 
			EQ(escape_character_qm,
			G2int_gensym_esc_for_paragraph_breakqm))
		    temp_1 = G2int_gensym_code_for_paragraph_break;
		else {
		    temp_1 =  !EQ(escape_character_qm,CHR('\\')) ? 
			    FIX((SI_Long)65535L) : Nil;
		    if (temp_1);
		    else
			temp_1 = FIX(character_or_character_code_1);
		}
	    }
	    break;
	  default:
	    character_or_character_code = CODE_CHAR(FIX(character_1));
	    escape_character_qm = Nil;
	    if ( !TRUEP(escape_character_qm))
		temp_1 = CHAR_CODE(character_or_character_code);
	    else {
		if (CHAR_EQ(escape_character_qm,CHR('~'))) {
		    temp_1 = 
			    ISVREF(G2int_reverse_iso_latin1_special_character_code_map,
			    IFIX(CHAR_CODE(character_or_character_code)));
		    if (temp_1);
		    else {
			temp_1 = CHAR_CODE(character_or_character_code);
			if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    temp_1 = Nil;
			else
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 87:
				temp_1 = 
					G2int_gensym_code_for_capital_ligature_oe;
				break;
			      case 119:
				temp_1 = 
					G2int_gensym_code_for_small_ligature_oe;
				break;
			      case 42:
				temp_1 = G2int_gensym_code_for_bullet;
				break;
			      case 38:
				temp_1 = 
					G2int_gensym_code_for_small_letter_f_with_hook;
				break;
			      case 58:
				temp_1 = G2int_gensym_code_for_trade_mark_sign;
				break;
			      default:
				temp_1 = Nil;
				break;
			    }
		    }
		}
		else
		    temp_1 = Nil;
		if (temp_1);
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(G2int_gensym_esc_for_linebreakqm) ? 
			CHAR_EQ(character_or_character_code,
			G2int_gensym_char_or_code_for_linebreak) : 
			EQ(character_or_character_code,
			G2int_gensym_char_or_code_for_linebreak) && 
			EQ(escape_character_qm,
			G2int_gensym_esc_for_linebreakqm))
		    temp_1 = G2int_gensym_code_for_linebreak;
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(G2int_gensym_esc_for_paragraph_breakqm) ? 
			CHAR_EQ(character_or_character_code,
			G2int_gensym_char_or_code_for_paragraph_break) : 
			EQ(character_or_character_code,
			G2int_gensym_char_or_code_for_paragraph_break) && 
			EQ(escape_character_qm,
			G2int_gensym_esc_for_paragraph_breakqm))
		    temp_1 = G2int_gensym_code_for_paragraph_break;
		else {
		    temp_1 =  !EQ(escape_character_qm,CHR('\\')) ? 
			    FIX((SI_Long)65535L) : Nil;
		    if (temp_1);
		    else
			temp_1 = character_or_character_code;
		}
	    }
	    break;
	}
  end_exhausted:
    return VALUES_1(temp_1);
}

/* TRANSCODE-CHARACTER-FOR-UTF-G-TRANSCODER */
Object g2int_transcode_character_for_utf_g_transcoder(utf_g_transcoder)
    Object utf_g_transcoder;
{
    Object transcoder, svref_new_value;
    Object current_extended_utf_g_low_half_character_qm, gensym_character_code;
    Object temp_1, code;
    SI_Long character_1, row, unicode_full_row, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(26,183);
    transcoder = utf_g_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)6L)) = svref_new_value;
    if (character_1 < (SI_Long)32L) {
	ISVREF(transcoder,(SI_Long)7L) = FIX((SI_Long)65535L);
	if (character_1 == (SI_Long)10L && IFIX(ISVREF(transcoder,
		(SI_Long)3L)) == (SI_Long)13L)
	    return VALUES_1(FIX((SI_Long)65535L));
	else if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L)
	    return VALUES_1(FIX((SI_Long)8232L));
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 < (SI_Long)128L) {
	svref_new_value = g2int_get_utf_g_transcoder_code(FIX(character_1),
		transcoder);
	SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
	if (IFIX(ISVREF(transcoder,(SI_Long)7L)) == (SI_Long)65535L)
	    return g2int_transcode_unhandled_character(FIX(character_1),
		    transcoder);
	else if (IFIX(ISVREF(transcoder,(SI_Long)6L)) >>  -  - (SI_Long)8L 
		== (SI_Long)247L) {
	    if (IFIX(ISVREF(transcoder,(SI_Long)7L)) >>  -  - (SI_Long)8L 
		    == (SI_Long)248L) {
		current_extended_utf_g_low_half_character_qm = 
			ISVREF(transcoder,(SI_Long)6L);
		PUSH_SPECIAL(G2int_current_extended_utf_g_low_half_characterqm,current_extended_utf_g_low_half_character_qm,
			0);
		  gensym_character_code = ISVREF(transcoder,(SI_Long)7L);
		  temp = IFIX(gensym_character_code) < (SI_Long)256L ? 
			  TRUEP(ISVREF(G2int_iso_latin1_special_character_code_map,
			  IFIX(gensym_character_code))) : TRUEP(Nil);
		  if (temp);
		  else if (FIXNUM_EQ(gensym_character_code,
			  G2int_gensym_code_for_capital_ligature_oe))
		      temp = 'W';
		  else if (FIXNUM_EQ(gensym_character_code,
			  G2int_gensym_code_for_small_ligature_oe))
		      temp = 'w';
		  else if (FIXNUM_EQ(gensym_character_code,
			  G2int_gensym_code_for_bullet))
		      temp = '*';
		  else if (FIXNUM_EQ(gensym_character_code,
			  G2int_gensym_code_for_small_letter_f_with_hook))
		      temp = '&';
		  else if (FIXNUM_EQ(gensym_character_code,
			  G2int_gensym_code_for_trade_mark_sign))
		      temp = ':';
		  else
		      temp = TRUEP(Qnil);
		  if (temp) {
		      row = IFIX(gensym_character_code) >>  -  - (SI_Long)8L;
		      unicode_full_row = 
			      UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
			      row);
		      if ( !(unicode_full_row == 
			      IFIX(G2int_invalid_unicode_full_row))) {
			  gensymed_symbol = unicode_full_row << (SI_Long)8L;
			  gensymed_symbol_1 = (SI_Long)255L & 
				  IFIX(gensym_character_code);
			  result = VALUES_1(FIX(gensymed_symbol + 
				  gensymed_symbol_1));
		      }
		      else
			  result = VALUES_1(Nil);
		  }
		  else if ((SI_Long)8192L <= IFIX(gensym_character_code) 
			  && IFIX(gensym_character_code) <= (SI_Long)8447L) {
		      row = IFIX(gensym_character_code) >>  -  - (SI_Long)8L;
		      unicode_full_row = 
			      UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
			      row);
		      if ( !(unicode_full_row == 
			      IFIX(G2int_invalid_unicode_full_row))) {
			  gensymed_symbol = unicode_full_row << (SI_Long)8L;
			  gensymed_symbol_1 = (SI_Long)255L & 
				  IFIX(gensym_character_code);
			  result = VALUES_1(FIX(gensymed_symbol + 
				  gensymed_symbol_1));
		      }
		      else
			  result = VALUES_1(Nil);
		  }
		  else {
		      temp_1 = 
			      g2int_map_gensym_han_character_code_to_unicode(gensym_character_code);
		      if (temp_1)
			  result = VALUES_1(temp_1);
		      else {
			  row = IFIX(gensym_character_code) >>  -  - 
				  (SI_Long)8L;
			  unicode_full_row = 
				  UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
				  row);
			  if ( !(unicode_full_row == 
				  IFIX(G2int_invalid_unicode_full_row))) {
			      gensymed_symbol = unicode_full_row << 
				      (SI_Long)8L;
			      gensymed_symbol_1 = (SI_Long)255L & 
				      IFIX(gensym_character_code);
			      temp_1 = FIX(gensymed_symbol + 
				      gensymed_symbol_1);
			  }
			  else
			      temp_1 = Nil;
			  if (temp_1)
			      result = VALUES_1(temp_1);
			  else if (G2int_current_extended_utf_g_low_half_characterqm)
			      result = g2int_map_extended_utf_g_characters_to_unicode(G2int_current_extended_utf_g_low_half_characterqm,
				      gensym_character_code);
			  else
			      result = VALUES_1(FIX((SI_Long)65535L));
		      }
		  }
		POP_SPECIAL();
		return result;
	    }
	    else
		return g2int_transcode_unhandled_character(FIX(character_1),
			transcoder);
	}
	else if (IFIX(ISVREF(transcoder,(SI_Long)7L)) >>  -  - (SI_Long)8L 
		== (SI_Long)247L)
	    return VALUES_1(FIX((SI_Long)65535L));
	else {
	    gensym_character_code = ISVREF(transcoder,(SI_Long)7L);
	    temp = IFIX(gensym_character_code) < (SI_Long)256L ? 
		    TRUEP(ISVREF(G2int_iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code))) : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_capital_ligature_oe))
		temp = 'W';
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_small_ligature_oe))
		temp = 'w';
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_bullet))
		temp = '*';
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_small_letter_f_with_hook))
		temp = '&';
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_trade_mark_sign))
		temp = ':';
	    else
		temp = TRUEP(Qnil);
	    if (temp) {
		row = IFIX(gensym_character_code) >>  -  - (SI_Long)8L;
		unicode_full_row = 
			UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
			row);
		if ( !(unicode_full_row == 
			IFIX(G2int_invalid_unicode_full_row))) {
		    gensymed_symbol = unicode_full_row << (SI_Long)8L;
		    gensymed_symbol_1 = (SI_Long)255L & 
			    IFIX(gensym_character_code);
		    code = FIX(gensymed_symbol + gensymed_symbol_1);
		}
		else
		    code = Nil;
	    }
	    else if ((SI_Long)8192L <= IFIX(gensym_character_code) && 
		    IFIX(gensym_character_code) <= (SI_Long)8447L) {
		row = IFIX(gensym_character_code) >>  -  - (SI_Long)8L;
		unicode_full_row = 
			UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
			row);
		if ( !(unicode_full_row == 
			IFIX(G2int_invalid_unicode_full_row))) {
		    gensymed_symbol = unicode_full_row << (SI_Long)8L;
		    gensymed_symbol_1 = (SI_Long)255L & 
			    IFIX(gensym_character_code);
		    code = FIX(gensymed_symbol + gensymed_symbol_1);
		}
		else
		    code = Nil;
	    }
	    else {
		code = 
			g2int_map_gensym_han_character_code_to_unicode(gensym_character_code);
		if (code);
		else {
		    row = IFIX(gensym_character_code) >>  -  - (SI_Long)8L;
		    unicode_full_row = 
			    UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
			    row);
		    if ( !(unicode_full_row == 
			    IFIX(G2int_invalid_unicode_full_row))) {
			gensymed_symbol = unicode_full_row << (SI_Long)8L;
			gensymed_symbol_1 = (SI_Long)255L & 
				IFIX(gensym_character_code);
			code = FIX(gensymed_symbol + gensymed_symbol_1);
		    }
		    else
			code = Nil;
		    if (code);
		    else if (G2int_current_extended_utf_g_low_half_characterqm)
			code = 
				g2int_map_extended_utf_g_characters_to_unicode(G2int_current_extended_utf_g_low_half_characterqm,
				gensym_character_code);
		    else
			code = FIX((SI_Long)65535L);
		}
	    }
	    if (IFIX(code) == (SI_Long)65535L)
		return g2int_transcode_unhandled_character(FIX(character_1),
			transcoder);
	    else
		return VALUES_1(code);
	}
    }
    else {
	ISVREF(transcoder,(SI_Long)7L) = FIX((SI_Long)65535L);
	return g2int_transcode_unhandled_character(FIX(character_1),
		transcoder);
    }
}

/* EXPORT-CHARACTER-FOR-UTF-G-TRANSCODER */
Object g2int_export_character_for_utf_g_transcoder(utf_g_transcoder)
    Object utf_g_transcoder;
{
    Object transcoder, temp, svref_new_value, escape_character_qm;
    Object character_or_character_code, extended_escape_character_qm;
    Object extended_character_or_character_code_qm, octet_1_qm, code_1;
    Object quotient, remainder_1, character_3;
    SI_Long character_1, character_2, unicode, code, arg, arg_1, arg_2, row;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1, octet_2;
    SI_Long octet_3;
    Object result;

    x_note_fn_call(26,184);
    transcoder = utf_g_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L || 
	    character_1 == (SI_Long)9L) {
	if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	    temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	    if (EQ(temp,Qg2int_per_platform)) {
		if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
			EQ(G2int_g2_operating_system,Qg2int_vms) || 
			EQ(G2int_g2_operating_system,Qg2int_win32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp,Qg2int_cr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp,Qg2int_lf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp,Qg2int_crlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp,Qg2int_unicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp,Qg2int_unicode_paragraph_separator))
		return VALUES_1(FIX((SI_Long)8233L));
	    else
		return VALUES_1(FIX(character_1));
	}
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		g2int_gensym_cons_1(FIX((SI_Long)64L),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	character_2 = character_1 == (SI_Long)8232L ? (SI_Long)76L : 
		(SI_Long)80L;
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		g2int_gensym_cons_1(FIX(character_2),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	return VALUES_1(FIX((SI_Long)65535L));
    }
    else {
	escape_character_qm = Nil;
	character_or_character_code = Nil;
	extended_escape_character_qm = Nil;
	extended_character_or_character_code_qm = Nil;
	unicode = character_1;
	escape_character_qm = Nil;
	extended_escape_character_qm = Nil;
	extended_character_or_character_code_qm = Nil;
	code = unicode;
	if (code < (SI_Long)127L &&  !((SI_Long)64L == code || 
		(SI_Long)126L == code || (SI_Long)92L == code))
	    character_or_character_code = FIX(unicode);
	else {
	    temp = unicode < (SI_Long)256L ? 
		    ISVREF(G2int_iso_latin1_special_character_code_map,
		    unicode) : Nil;
	    if (temp);
	    else if (unicode == (SI_Long)338L)
		temp = CHR('W');
	    else if (unicode == (SI_Long)339L)
		temp = CHR('w');
	    else if (unicode == (SI_Long)8226L)
		temp = CHR('*');
	    else if (unicode == (SI_Long)402L)
		temp = CHR('&');
	    else if (unicode == (SI_Long)8482L)
		temp = CHR(':');
	    else
		temp = Qnil;
	    character_or_character_code = temp;
	    if (character_or_character_code) {
		character_or_character_code = 
			CHAR_CODE(character_or_character_code);
		escape_character_qm = G2int_pcttl;
	    }
	    else {
		escape_character_qm = G2int_pctbs;
		arg = (SI_Long)8192L;
		arg_1 = unicode + 
			IFIX(G2int_unicode_offset_for_gensym_cyrillic);
		arg_2 = (SI_Long)8447L;
		character_or_character_code = arg <= arg_1 && arg_1 <= 
			arg_2 ? FIX(unicode + 
			IFIX(G2int_unicode_offset_for_gensym_cyrillic)) : Nil;
		if (character_or_character_code);
		else {
		    character_or_character_code = 
			    g2int_map_unicode_to_gensym_han_character_code(FIX(unicode));
		    if (character_or_character_code);
		    else {
			row = unicode >>  -  - (SI_Long)8L;
			gensym_full_row = 
				UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,
				row);
			if ( !(gensym_full_row == 
				IFIX(G2int_invalid_gensym_full_row))) {
			    gensymed_symbol = gensym_full_row << (SI_Long)8L;
			    gensymed_symbol_1 = (SI_Long)255L & unicode;
			    character_or_character_code = 
				    FIX(gensymed_symbol + gensymed_symbol_1);
			}
			else
			    character_or_character_code = Nil;
			if (character_or_character_code);
			else {
			    extended_escape_character_qm = G2int_pctbs;
			    gensymed_symbol = (SI_Long)63488L;
			    gensymed_symbol_1 = (SI_Long)255L & unicode;
			    extended_character_or_character_code_qm = 
				    FIX(gensymed_symbol + gensymed_symbol_1);
			    character_or_character_code = 
				    FIX((SI_Long)63232L + (unicode >>  -  
				    - (SI_Long)8L));
			}
		    }
		}
	    }
	}
	if ( !TRUEP(escape_character_qm))
	    return VALUES_1(character_or_character_code);
	else {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    g2int_gensym_cons_1(escape_character_qm,Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    temp = escape_character_qm;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L)))) {
		octet_1_qm = Nil;
		octet_2 = (SI_Long)0L;
		octet_3 = (SI_Long)0L;
		code_1 = character_or_character_code;
		result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) & 
			(SI_Long)8191L),FIX((SI_Long)95L));
		MVS_2(result,quotient,remainder_1);
		octet_2 = IFIX(quotient) + (SI_Long)40L;
		octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
			(SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
			(SI_Long)13L) + (SI_Long)32L) : Nil;
		if (octet_1_qm) {
		    character_3 = octet_1_qm;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),g2int_gensym_cons_1(character_3,Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		}
		character_2 = octet_2;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX(character_2),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = octet_3;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX(character_2),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		if (extended_escape_character_qm) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(extended_escape_character_qm,
			    Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    code_1 = extended_character_or_character_code_qm;
		    result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) 
			    & (SI_Long)8191L),FIX((SI_Long)95L));
		    MVS_2(result,quotient,remainder_1);
		    octet_2 = IFIX(quotient) + (SI_Long)40L;
		    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		    octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
			    (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
			    (SI_Long)13L) + (SI_Long)32L) : Nil;
		    if (octet_1_qm) {
			character_3 = octet_1_qm;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(character_3,Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    character_2 = octet_2;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_2),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    character_2 = octet_3;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_2),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		}
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 64:
		  case 126:
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(character_or_character_code,
			    Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    break;
		  default:
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    code_1 = character_or_character_code;
		    result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) 
			    & (SI_Long)8191L),FIX((SI_Long)95L));
		    MVS_2(result,quotient,remainder_1);
		    octet_2 = IFIX(quotient) + (SI_Long)40L;
		    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		    octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
			    (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
			    (SI_Long)13L) + (SI_Long)32L) : Nil;
		    if (octet_1_qm) {
			character_3 = octet_1_qm;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(character_3,Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    character_2 = octet_2;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_2),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    character_2 = octet_3;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_2),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    if (extended_escape_character_qm) {
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(extended_escape_character_qm,
				Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			code_1 = extended_character_or_character_code_qm;
			result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) 
				& (SI_Long)8191L),FIX((SI_Long)95L));
			MVS_2(result,quotient,remainder_1);
			octet_2 = IFIX(quotient) + (SI_Long)40L;
			octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L 
				== (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  
				- (SI_Long)13L) + (SI_Long)32L) : Nil;
			if (octet_1_qm) {
			    character_3 = octet_1_qm;
			    svref_new_value = nconc2(ISVREF(transcoder,
				    (SI_Long)5L),
				    g2int_gensym_cons_1(character_3,Nil));
			    SVREF(transcoder,FIX((SI_Long)5L)) = 
				    svref_new_value;
			}
			character_2 = octet_2;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX(character_2),Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
			character_2 = octet_3;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX(character_2),Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    break;
		}
	    return VALUES_1(FIX((SI_Long)65535L));
	}
    }
}

Object G2int_the_type_description_of_utf_g_ascii_as_much_as_possible_transcoder = UNBOUND;

Object G2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders = UNBOUND;

Object G2int_utf_g_ascii_as_much_as_possible_transcoder_count = UNBOUND;

/* RECLAIM-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-1 */
Object g2int_reclaim_utf_g_ascii_as_much_as_possible_transcoder_1(utf_g_ascii_as_much_as_possible_transcoder)
    Object utf_g_ascii_as_much_as_possible_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,185);
    inline_note_reclaim_cons(utf_g_ascii_as_much_as_possible_transcoder,Nil);
    svref_new_value = 
	    G2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders;
    SVREF(utf_g_ascii_as_much_as_possible_transcoder,FIX((SI_Long)0L)) = 
	    svref_new_value;
    G2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders = 
	    utf_g_ascii_as_much_as_possible_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER */
Object g2int_reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder(utf_g_ascii_as_much_as_possible_transcoder)
    Object utf_g_ascii_as_much_as_possible_transcoder;
{
    x_note_fn_call(26,186);
    return g2int_reclaim_utf_g_ascii_as_much_as_possible_transcoder_1(utf_g_ascii_as_much_as_possible_transcoder);
}

static Object Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct;  /* g2-defstruct-structure-name::utf-g-ascii-as-much-as-possible-transcoder-g2-struct */

/* MAKE-PERMANENT-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_utf_g_ascii_as_much_as_possible_transcoder_structure_internal()
{
    Object def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable;
    Object temp;
    Object defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable;
    Object the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,187);
    def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_utf_g_ascii_as_much_as_possible_transcoder_count);
    G2int_utf_g_ascii_as_much_as_possible_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable = 
		the_array;
	SVREF(defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct;
	SVREF(defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)7L)) = Nil;
	def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable 
		= 
		defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable;
	SVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		G2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders;
	SVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders 
		= 
		def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable);
}

/* MAKE-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-1 */
Object g2int_make_utf_g_ascii_as_much_as_possible_transcoder_1()
{
    Object def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable;

    x_note_fn_call(26,188);
    def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable = 
	    G2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders;
    if (def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable) {
	G2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders 
		= 
		ISVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
		(SI_Long)0L);
	SVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct;
    }
    else
	def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable 
		= 
		g2int_make_permanent_utf_g_ascii_as_much_as_possible_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
	    Nil);
    ISVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
	    (SI_Long)2L) = FIX((SI_Long)65535L);
    ISVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
	    (SI_Long)3L) = FIX((SI_Long)65535L);
    SVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
	    FIX((SI_Long)5L)) = Qnil;
    ISVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
	    (SI_Long)6L) = FIX((SI_Long)65535L);
    ISVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
	    (SI_Long)7L) = FIX((SI_Long)65535L);
    return VALUES_1(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable);
}

/* EXPORT-CHARACTER-FOR-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER */
Object g2int_export_character_for_utf_g_ascii_as_much_as_possible_transcoder(utf_g_ascii_as_much_as_possible_transcoder)
    Object utf_g_ascii_as_much_as_possible_transcoder;
{
    Object transcoder, temp, svref_new_value, escape_character_qm;
    Object character_or_character_code, extended_escape_character_qm;
    Object extended_character_or_character_code_qm, octet_1_qm, code_1;
    Object quotient, remainder_1, character_2;
    SI_Long character_1, unicode, code, arg, arg_1, arg_2, row;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1, octet_2;
    SI_Long octet_3, character_3;
    Object result;

    x_note_fn_call(26,189);
    transcoder = utf_g_ascii_as_much_as_possible_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L || 
	    character_1 == (SI_Long)9L || character_1 == (SI_Long)8232L || 
	    character_1 == (SI_Long)8233L) {
	if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	    temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	    if (EQ(temp,Qg2int_per_platform)) {
		if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
			EQ(G2int_g2_operating_system,Qg2int_vms) || 
			EQ(G2int_g2_operating_system,Qg2int_win32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp,Qg2int_cr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp,Qg2int_lf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp,Qg2int_crlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp,Qg2int_unicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp,Qg2int_unicode_paragraph_separator))
		return VALUES_1(FIX((SI_Long)8233L));
	    else
		return VALUES_1(FIX(character_1));
	}
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 == (SI_Long)64L || character_1 == (SI_Long)92L || 
	    character_1 == (SI_Long)126L)
	return VALUES_1(FIX(character_1));
    else {
	escape_character_qm = Nil;
	character_or_character_code = Nil;
	extended_escape_character_qm = Nil;
	extended_character_or_character_code_qm = Nil;
	unicode = character_1;
	escape_character_qm = Nil;
	extended_escape_character_qm = Nil;
	extended_character_or_character_code_qm = Nil;
	code = unicode;
	if (code < (SI_Long)127L &&  !((SI_Long)64L == code || 
		(SI_Long)126L == code || (SI_Long)92L == code))
	    character_or_character_code = FIX(unicode);
	else {
	    temp = unicode < (SI_Long)256L ? 
		    ISVREF(G2int_iso_latin1_special_character_code_map,
		    unicode) : Nil;
	    if (temp);
	    else if (unicode == (SI_Long)338L)
		temp = CHR('W');
	    else if (unicode == (SI_Long)339L)
		temp = CHR('w');
	    else if (unicode == (SI_Long)8226L)
		temp = CHR('*');
	    else if (unicode == (SI_Long)402L)
		temp = CHR('&');
	    else if (unicode == (SI_Long)8482L)
		temp = CHR(':');
	    else
		temp = Qnil;
	    character_or_character_code = temp;
	    if (character_or_character_code) {
		character_or_character_code = 
			CHAR_CODE(character_or_character_code);
		escape_character_qm = G2int_pcttl;
	    }
	    else {
		escape_character_qm = G2int_pctbs;
		arg = (SI_Long)8192L;
		arg_1 = unicode + 
			IFIX(G2int_unicode_offset_for_gensym_cyrillic);
		arg_2 = (SI_Long)8447L;
		character_or_character_code = arg <= arg_1 && arg_1 <= 
			arg_2 ? FIX(unicode + 
			IFIX(G2int_unicode_offset_for_gensym_cyrillic)) : Nil;
		if (character_or_character_code);
		else {
		    character_or_character_code = 
			    g2int_map_unicode_to_gensym_han_character_code(FIX(unicode));
		    if (character_or_character_code);
		    else {
			row = unicode >>  -  - (SI_Long)8L;
			gensym_full_row = 
				UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,
				row);
			if ( !(gensym_full_row == 
				IFIX(G2int_invalid_gensym_full_row))) {
			    gensymed_symbol = gensym_full_row << (SI_Long)8L;
			    gensymed_symbol_1 = (SI_Long)255L & unicode;
			    character_or_character_code = 
				    FIX(gensymed_symbol + gensymed_symbol_1);
			}
			else
			    character_or_character_code = Nil;
			if (character_or_character_code);
			else {
			    extended_escape_character_qm = G2int_pctbs;
			    gensymed_symbol = (SI_Long)63488L;
			    gensymed_symbol_1 = (SI_Long)255L & unicode;
			    extended_character_or_character_code_qm = 
				    FIX(gensymed_symbol + gensymed_symbol_1);
			    character_or_character_code = 
				    FIX((SI_Long)63232L + (unicode >>  -  
				    - (SI_Long)8L));
			}
		    }
		}
	    }
	}
	if ( !TRUEP(escape_character_qm))
	    return VALUES_1(character_or_character_code);
	else {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    g2int_gensym_cons_1(escape_character_qm,Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    temp = escape_character_qm;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L)))) {
		octet_1_qm = Nil;
		octet_2 = (SI_Long)0L;
		octet_3 = (SI_Long)0L;
		code_1 = character_or_character_code;
		result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) & 
			(SI_Long)8191L),FIX((SI_Long)95L));
		MVS_2(result,quotient,remainder_1);
		octet_2 = IFIX(quotient) + (SI_Long)40L;
		octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
			(SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
			(SI_Long)13L) + (SI_Long)32L) : Nil;
		if (octet_1_qm) {
		    character_2 = octet_1_qm;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),g2int_gensym_cons_1(character_2,Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		}
		character_3 = octet_2;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX(character_3),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_3 = octet_3;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX(character_3),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		if (extended_escape_character_qm) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(extended_escape_character_qm,
			    Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    code_1 = extended_character_or_character_code_qm;
		    result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) 
			    & (SI_Long)8191L),FIX((SI_Long)95L));
		    MVS_2(result,quotient,remainder_1);
		    octet_2 = IFIX(quotient) + (SI_Long)40L;
		    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		    octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
			    (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
			    (SI_Long)13L) + (SI_Long)32L) : Nil;
		    if (octet_1_qm) {
			character_2 = octet_1_qm;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(character_2,Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    character_3 = octet_2;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_3),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    character_3 = octet_3;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_3),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		}
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 64:
		  case 126:
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(character_or_character_code,
			    Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    break;
		  default:
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    code_1 = character_or_character_code;
		    result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) 
			    & (SI_Long)8191L),FIX((SI_Long)95L));
		    MVS_2(result,quotient,remainder_1);
		    octet_2 = IFIX(quotient) + (SI_Long)40L;
		    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		    octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
			    (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
			    (SI_Long)13L) + (SI_Long)32L) : Nil;
		    if (octet_1_qm) {
			character_2 = octet_1_qm;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(character_2,Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    character_3 = octet_2;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_3),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    character_3 = octet_3;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    g2int_gensym_cons_1(FIX(character_3),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    if (extended_escape_character_qm) {
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(extended_escape_character_qm,
				Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			code_1 = extended_character_or_character_code_qm;
			result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) 
				& (SI_Long)8191L),FIX((SI_Long)95L));
			MVS_2(result,quotient,remainder_1);
			octet_2 = IFIX(quotient) + (SI_Long)40L;
			octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L 
				== (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  
				- (SI_Long)13L) + (SI_Long)32L) : Nil;
			if (octet_1_qm) {
			    character_2 = octet_1_qm;
			    svref_new_value = nconc2(ISVREF(transcoder,
				    (SI_Long)5L),
				    g2int_gensym_cons_1(character_2,Nil));
			    SVREF(transcoder,FIX((SI_Long)5L)) = 
				    svref_new_value;
			}
			character_3 = octet_2;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX(character_3),Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
			character_3 = octet_3;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				g2int_gensym_cons_1(FIX(character_3),Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    break;
		}
	    return VALUES_1(FIX((SI_Long)65535L));
	}
    }
}

Object G2int_the_type_description_of_unicode_ucs_2_transcoder = UNBOUND;

Object G2int_chain_of_available_unicode_ucs_2_transcoders = UNBOUND;

Object G2int_unicode_ucs_2_transcoder_count = UNBOUND;

/* RECLAIM-UNICODE-UCS-2-TRANSCODER-1 */
Object g2int_reclaim_unicode_ucs_2_transcoder_1(unicode_ucs_2_transcoder)
    Object unicode_ucs_2_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,190);
    inline_note_reclaim_cons(unicode_ucs_2_transcoder,Nil);
    svref_new_value = G2int_chain_of_available_unicode_ucs_2_transcoders;
    SVREF(unicode_ucs_2_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_unicode_ucs_2_transcoders = 
	    unicode_ucs_2_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNICODE-UCS-2-TRANSCODER */
Object g2int_reclaim_structure_for_unicode_ucs_2_transcoder(unicode_ucs_2_transcoder)
    Object unicode_ucs_2_transcoder;
{
    x_note_fn_call(26,191);
    return g2int_reclaim_unicode_ucs_2_transcoder_1(unicode_ucs_2_transcoder);
}

static Object Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct;  /* g2-defstruct-structure-name::unicode-ucs-2-transcoder-g2-struct */

/* MAKE-PERMANENT-UNICODE-UCS-2-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_unicode_ucs_2_transcoder_structure_internal()
{
    Object def_structure_unicode_ucs_2_transcoder_variable, temp;
    Object defstruct_g2_unicode_ucs_2_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,192);
    def_structure_unicode_ucs_2_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_unicode_ucs_2_transcoder_count);
    G2int_unicode_ucs_2_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_unicode_ucs_2_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_unicode_ucs_2_transcoder_variable = the_array;
	SVREF(defstruct_g2_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct;
	SVREF(defstruct_g2_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_unicode_ucs_2_transcoder_variable = 
		defstruct_g2_unicode_ucs_2_transcoder_variable;
	SVREF(def_structure_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_unicode_ucs_2_transcoders;
	SVREF(def_structure_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_unicode_ucs_2_transcoders = 
		def_structure_unicode_ucs_2_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_unicode_ucs_2_transcoder_variable);
}

/* MAKE-UNICODE-UCS-2-TRANSCODER-1 */
Object g2int_make_unicode_ucs_2_transcoder_1()
{
    Object def_structure_unicode_ucs_2_transcoder_variable;

    x_note_fn_call(26,193);
    def_structure_unicode_ucs_2_transcoder_variable = 
	    G2int_chain_of_available_unicode_ucs_2_transcoders;
    if (def_structure_unicode_ucs_2_transcoder_variable) {
	G2int_chain_of_available_unicode_ucs_2_transcoders = 
		ISVREF(def_structure_unicode_ucs_2_transcoder_variable,
		(SI_Long)0L);
	SVREF(def_structure_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct;
    }
    else
	def_structure_unicode_ucs_2_transcoder_variable = 
		g2int_make_permanent_unicode_ucs_2_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_unicode_ucs_2_transcoder_variable,
	    Nil);
    ISVREF(def_structure_unicode_ucs_2_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_unicode_ucs_2_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_unicode_ucs_2_transcoder_variable,
	    FIX((SI_Long)5L)) = Qnil;
    SVREF(def_structure_unicode_ucs_2_transcoder_variable,
	    FIX((SI_Long)6L)) = T;
    SVREF(def_structure_unicode_ucs_2_transcoder_variable,
	    FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_unicode_ucs_2_transcoder_variable);
}

/* TRANSCODE-CHARACTER-FOR-UNICODE-UCS-2-TRANSCODER */
Object g2int_transcode_character_for_unicode_ucs_2_transcoder(unicode_ucs_2_transcoder)
    Object unicode_ucs_2_transcoder;
{
    Object transcoder, text_sequence, temp;
    SI_Long lead_character, trail_character, lead_octet, trail_octet;
    SI_Long gensymed_symbol, gensymed_symbol_1, character_1;

    x_note_fn_call(26,194);
    transcoder = unicode_ucs_2_transcoder;
    lead_character = IFIX(g2int_get_transcoder_character(transcoder));
    trail_character = (SI_Long)0L;
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	return g2int_transcode_unhandled_character(FIX(lead_character),
		transcoder);
    else if ( !(lead_character < (SI_Long)256L && trail_character < 
	    (SI_Long)256L))
	return g2int_transcode_unhandled_character(FIX(lead_character),
		transcoder);
    else {
	trail_character = IFIX(g2int_get_transcoder_character(transcoder));
	if (ISVREF(transcoder,(SI_Long)6L)) {
	    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
	    if (lead_character == (SI_Long)254L && trail_character == 
		    (SI_Long)255L) {
		SVREF(transcoder,FIX((SI_Long)7L)) = Nil;
		temp = FIX((SI_Long)65535L);
	    }
	    else if (lead_character == (SI_Long)255L && trail_character == 
		    (SI_Long)254L) {
		SVREF(transcoder,FIX((SI_Long)7L)) = T;
		temp = FIX((SI_Long)65535L);
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
	if (temp)
	    return VALUES_1(temp);
	else {
	    if (ISVREF(transcoder,(SI_Long)7L)) {
		lead_octet = trail_character;
		trail_octet = lead_character;
		gensymed_symbol = lead_octet & (SI_Long)255L;
		gensymed_symbol_1 = (SI_Long)8L;
		gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
		gensymed_symbol = trail_octet & (SI_Long)255L;
		character_1 = gensymed_symbol_1 | gensymed_symbol;
	    }
	    else {
		lead_octet = lead_character;
		trail_octet = trail_character;
		gensymed_symbol = lead_octet & (SI_Long)255L;
		gensymed_symbol_1 = (SI_Long)8L;
		gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
		gensymed_symbol = trail_octet & (SI_Long)255L;
		character_1 = gensymed_symbol_1 | gensymed_symbol;
	    }
	    if (character_1 == (SI_Long)10L && IFIX(ISVREF(transcoder,
		    (SI_Long)3L)) == (SI_Long)13L)
		return VALUES_1(FIX((SI_Long)65535L));
	    else if (character_1 == (SI_Long)10L || character_1 == 
		    (SI_Long)13L)
		return VALUES_1(FIX((SI_Long)8232L));
	    else
		return VALUES_1(FIX(character_1));
	}
    }
}

/* EXPORT-CHARACTER-FOR-UNICODE-UCS-2-TRANSCODER */
Object g2int_export_character_for_unicode_ucs_2_transcoder(unicode_ucs_2_transcoder)
    Object unicode_ucs_2_transcoder;
{
    Object transcoder, character_1, temp, svref_new_value;
    SI_Long character_2, character_3;

    x_note_fn_call(26,195);
    transcoder = unicode_ucs_2_transcoder;
    character_1 = g2int_get_transcoder_character(transcoder);
    if (IFIX(character_1) == (SI_Long)8232L || IFIX(character_1) == 
	    (SI_Long)8233L) {
	temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	if (EQ(temp,Qg2int_per_platform)) {
	    if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
		    EQ(G2int_g2_operating_system,Qg2int_vms) || 
		    EQ(G2int_g2_operating_system,Qg2int_win32)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = (SI_Long)13L;
	    }
	    else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		character_2 = (SI_Long)10L;
	    else
		character_2 = (SI_Long)10L;
	}
	else if (EQ(temp,Qg2int_cr))
	    character_2 = (SI_Long)13L;
	else if (EQ(temp,Qg2int_lf))
	    character_2 = (SI_Long)10L;
	else if (EQ(temp,Qg2int_crlf)) {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    character_2 = (SI_Long)13L;
	}
	else if (EQ(temp,Qg2int_unicode_line_separator))
	    character_2 = (SI_Long)8232L;
	else if (EQ(temp,Qg2int_unicode_paragraph_separator))
	    character_2 = (SI_Long)8233L;
	else
	    character_2 = IFIX(character_1);
    }
    else
	character_2 = IFIX(character_1);
    if (ISVREF(transcoder,(SI_Long)7L)) {
	character_3 = character_2 >>  -  - (SI_Long)8L;
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		g2int_gensym_cons_1(FIX(character_3),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	return VALUES_1(FIX(character_2 & (SI_Long)255L));
    }
    else {
	character_3 = character_2 & (SI_Long)255L;
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		g2int_gensym_cons_1(FIX(character_3),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	return VALUES_1(FIX(character_2 >>  -  - (SI_Long)8L));
    }
}

Object G2int_the_type_description_of_unicode_transcoder = UNBOUND;

Object G2int_chain_of_available_unicode_transcoders = UNBOUND;

Object G2int_unicode_transcoder_count = UNBOUND;

/* RECLAIM-UNICODE-TRANSCODER-1 */
Object g2int_reclaim_unicode_transcoder_1(unicode_transcoder)
    Object unicode_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,196);
    inline_note_reclaim_cons(unicode_transcoder,Nil);
    svref_new_value = G2int_chain_of_available_unicode_transcoders;
    SVREF(unicode_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_unicode_transcoders = unicode_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNICODE-TRANSCODER */
Object g2int_reclaim_structure_for_unicode_transcoder(unicode_transcoder)
    Object unicode_transcoder;
{
    x_note_fn_call(26,197);
    return g2int_reclaim_unicode_transcoder_1(unicode_transcoder);
}

static Object Qg2_defstruct_structure_name_unicode_transcoder_g2_struct;  /* g2-defstruct-structure-name::unicode-transcoder-g2-struct */

/* MAKE-PERMANENT-UNICODE-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_unicode_transcoder_structure_internal()
{
    Object def_structure_unicode_transcoder_variable, temp;
    Object defstruct_g2_unicode_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,198);
    def_structure_unicode_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_unicode_transcoder_count);
    G2int_unicode_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_unicode_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)6L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_unicode_transcoder_variable = the_array;
	SVREF(defstruct_g2_unicode_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_transcoder_g2_struct;
	SVREF(defstruct_g2_unicode_transcoder_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_unicode_transcoder_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_unicode_transcoder_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_unicode_transcoder_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_unicode_transcoder_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_unicode_transcoder_variable = 
		defstruct_g2_unicode_transcoder_variable;
	SVREF(def_structure_unicode_transcoder_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(def_structure_unicode_transcoder_variable,FIX((SI_Long)4L)) 
		= Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_unicode_transcoders;
	SVREF(def_structure_unicode_transcoder_variable,FIX((SI_Long)0L)) 
		= temp;
	G2int_chain_of_available_unicode_transcoders = 
		def_structure_unicode_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_unicode_transcoder_variable);
}

/* MAKE-UNICODE-TRANSCODER-1 */
Object g2int_make_unicode_transcoder_1()
{
    Object def_structure_unicode_transcoder_variable;

    x_note_fn_call(26,199);
    def_structure_unicode_transcoder_variable = 
	    G2int_chain_of_available_unicode_transcoders;
    if (def_structure_unicode_transcoder_variable) {
	G2int_chain_of_available_unicode_transcoders = 
		ISVREF(def_structure_unicode_transcoder_variable,(SI_Long)0L);
	SVREF(def_structure_unicode_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_unicode_transcoder_g2_struct;
    }
    else
	def_structure_unicode_transcoder_variable = 
		g2int_make_permanent_unicode_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_unicode_transcoder_variable,Nil);
    ISVREF(def_structure_unicode_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_unicode_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_unicode_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_unicode_transcoder_variable);
}

/* TRANSCODE-CHARACTER-FOR-UNICODE-TRANSCODER */
Object g2int_transcode_character_for_unicode_transcoder(unicode_transcoder)
    Object unicode_transcoder;
{
    Object character_1, transcoder;

    x_note_fn_call(26,200);
    character_1 = g2int_get_transcoder_character(unicode_transcoder);
    transcoder = unicode_transcoder;
    if (IFIX(character_1) == (SI_Long)10L && IFIX(ISVREF(transcoder,
	    (SI_Long)3L)) == (SI_Long)13L)
	return VALUES_1(FIX((SI_Long)65535L));
    else if (IFIX(character_1) == (SI_Long)10L || IFIX(character_1) == 
	    (SI_Long)13L)
	return VALUES_1(FIX((SI_Long)8232L));
    else
	return VALUES_1(character_1);
}

/* EXPORT-CHARACTER-FOR-UNICODE-TRANSCODER */
Object g2int_export_character_for_unicode_transcoder(unicode_transcoder)
    Object unicode_transcoder;
{
    Object character_1, transcoder, temp, svref_new_value;

    x_note_fn_call(26,201);
    character_1 = g2int_get_transcoder_character(unicode_transcoder);
    transcoder = unicode_transcoder;
    if (IFIX(character_1) == (SI_Long)8232L || IFIX(character_1) == 
	    (SI_Long)8233L) {
	temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	if (EQ(temp,Qg2int_per_platform)) {
	    if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
		    EQ(G2int_g2_operating_system,Qg2int_vms) || 
		    EQ(G2int_g2_operating_system,Qg2int_win32)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		return VALUES_1(FIX((SI_Long)10L));
	    else
		return VALUES_1(FIX((SI_Long)10L));
	}
	else if (EQ(temp,Qg2int_cr))
	    return VALUES_1(FIX((SI_Long)13L));
	else if (EQ(temp,Qg2int_lf))
	    return VALUES_1(FIX((SI_Long)10L));
	else if (EQ(temp,Qg2int_crlf)) {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    return VALUES_1(FIX((SI_Long)13L));
	}
	else if (EQ(temp,Qg2int_unicode_line_separator))
	    return VALUES_1(FIX((SI_Long)8232L));
	else if (EQ(temp,Qg2int_unicode_paragraph_separator))
	    return VALUES_1(FIX((SI_Long)8233L));
	else
	    return VALUES_1(character_1);
    }
    else
	return VALUES_1(character_1);
}

Object G2int_the_type_description_of_unicode_byte_swapped_transcoder = UNBOUND;

Object G2int_chain_of_available_unicode_byte_swapped_transcoders = UNBOUND;

Object G2int_unicode_byte_swapped_transcoder_count = UNBOUND;

/* RECLAIM-UNICODE-BYTE-SWAPPED-TRANSCODER-1 */
Object g2int_reclaim_unicode_byte_swapped_transcoder_1(unicode_byte_swapped_transcoder)
    Object unicode_byte_swapped_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,202);
    inline_note_reclaim_cons(unicode_byte_swapped_transcoder,Nil);
    svref_new_value = 
	    G2int_chain_of_available_unicode_byte_swapped_transcoders;
    SVREF(unicode_byte_swapped_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_unicode_byte_swapped_transcoders = 
	    unicode_byte_swapped_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNICODE-BYTE-SWAPPED-TRANSCODER */
Object g2int_reclaim_structure_for_unicode_byte_swapped_transcoder(unicode_byte_swapped_transcoder)
    Object unicode_byte_swapped_transcoder;
{
    x_note_fn_call(26,203);
    return g2int_reclaim_unicode_byte_swapped_transcoder_1(unicode_byte_swapped_transcoder);
}

static Object Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct;  /* g2-defstruct-structure-name::unicode-byte-swapped-transcoder-g2-struct */

/* MAKE-PERMANENT-UNICODE-BYTE-SWAPPED-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_unicode_byte_swapped_transcoder_structure_internal()
{
    Object def_structure_unicode_byte_swapped_transcoder_variable, temp;
    Object defstruct_g2_unicode_byte_swapped_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,204);
    def_structure_unicode_byte_swapped_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_unicode_byte_swapped_transcoder_count);
    G2int_unicode_byte_swapped_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_unicode_byte_swapped_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)6L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_unicode_byte_swapped_transcoder_variable = the_array;
	SVREF(defstruct_g2_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct;
	SVREF(defstruct_g2_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_unicode_byte_swapped_transcoder_variable = 
		defstruct_g2_unicode_byte_swapped_transcoder_variable;
	SVREF(def_structure_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_unicode_byte_swapped_transcoders;
	SVREF(def_structure_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_unicode_byte_swapped_transcoders = 
		def_structure_unicode_byte_swapped_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_unicode_byte_swapped_transcoder_variable);
}

/* MAKE-UNICODE-BYTE-SWAPPED-TRANSCODER-1 */
Object g2int_make_unicode_byte_swapped_transcoder_1()
{
    Object def_structure_unicode_byte_swapped_transcoder_variable;

    x_note_fn_call(26,205);
    def_structure_unicode_byte_swapped_transcoder_variable = 
	    G2int_chain_of_available_unicode_byte_swapped_transcoders;
    if (def_structure_unicode_byte_swapped_transcoder_variable) {
	G2int_chain_of_available_unicode_byte_swapped_transcoders = 
		ISVREF(def_structure_unicode_byte_swapped_transcoder_variable,
		(SI_Long)0L);
	SVREF(def_structure_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct;
    }
    else
	def_structure_unicode_byte_swapped_transcoder_variable = 
		g2int_make_permanent_unicode_byte_swapped_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_unicode_byte_swapped_transcoder_variable,
	    Nil);
    ISVREF(def_structure_unicode_byte_swapped_transcoder_variable,
	    (SI_Long)2L) = FIX((SI_Long)65535L);
    ISVREF(def_structure_unicode_byte_swapped_transcoder_variable,
	    (SI_Long)3L) = FIX((SI_Long)65535L);
    SVREF(def_structure_unicode_byte_swapped_transcoder_variable,
	    FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_unicode_byte_swapped_transcoder_variable);
}

/* TRANSCODE-CHARACTER-FOR-UNICODE-BYTE-SWAPPED-TRANSCODER */
Object g2int_transcode_character_for_unicode_byte_swapped_transcoder(unicode_byte_swapped_transcoder)
    Object unicode_byte_swapped_transcoder;
{
    Object transcoder;
    SI_Long character_1, lead_character, trail_character, lead_octet;
    SI_Long trail_octet, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,206);
    transcoder = unicode_byte_swapped_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    lead_character = character_1 & (SI_Long)255L;
    trail_character = character_1 >>  -  - (SI_Long)8L;
    lead_octet = lead_character;
    trail_octet = trail_character;
    gensymed_symbol = lead_octet & (SI_Long)255L;
    gensymed_symbol_1 = (SI_Long)8L;
    gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
    gensymed_symbol = trail_octet & (SI_Long)255L;
    character_1 = gensymed_symbol_1 | gensymed_symbol;
    if (character_1 == (SI_Long)10L && IFIX(ISVREF(transcoder,
	    (SI_Long)3L)) == (SI_Long)13L)
	return VALUES_1(FIX((SI_Long)65535L));
    else if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L)
	return VALUES_1(FIX((SI_Long)8232L));
    else
	return VALUES_1(FIX(character_1));
}

/* EXPORT-CHARACTER-FOR-UNICODE-BYTE-SWAPPED-TRANSCODER */
Object g2int_export_character_for_unicode_byte_swapped_transcoder(unicode_byte_swapped_transcoder)
    Object unicode_byte_swapped_transcoder;
{
    Object transcoder, character_1, temp, svref_new_value;
    SI_Long character_2, lead_character, trail_character, lead_octet;
    SI_Long trail_octet, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,207);
    transcoder = unicode_byte_swapped_transcoder;
    character_1 = g2int_get_transcoder_character(transcoder);
    if (IFIX(character_1) == (SI_Long)8232L || IFIX(character_1) == 
	    (SI_Long)8233L) {
	temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	if (EQ(temp,Qg2int_per_platform)) {
	    if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
		    EQ(G2int_g2_operating_system,Qg2int_vms) || 
		    EQ(G2int_g2_operating_system,Qg2int_win32)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = (SI_Long)13L;
	    }
	    else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		character_2 = (SI_Long)10L;
	    else
		character_2 = (SI_Long)10L;
	}
	else if (EQ(temp,Qg2int_cr))
	    character_2 = (SI_Long)13L;
	else if (EQ(temp,Qg2int_lf))
	    character_2 = (SI_Long)10L;
	else if (EQ(temp,Qg2int_crlf)) {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    character_2 = (SI_Long)13L;
	}
	else if (EQ(temp,Qg2int_unicode_line_separator))
	    character_2 = (SI_Long)8232L;
	else if (EQ(temp,Qg2int_unicode_paragraph_separator))
	    character_2 = (SI_Long)8233L;
	else
	    character_2 = IFIX(character_1);
    }
    else
	character_2 = IFIX(character_1);
    lead_character = character_2 & (SI_Long)255L;
    trail_character = character_2 >>  -  - (SI_Long)8L;
    lead_octet = lead_character;
    trail_octet = trail_character;
    gensymed_symbol = lead_octet & (SI_Long)255L;
    gensymed_symbol_1 = (SI_Long)8L;
    gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
    gensymed_symbol = trail_octet & (SI_Long)255L;
    return VALUES_1(FIX(gensymed_symbol_1 | gensymed_symbol));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-1 */
Object g2int_create_transcoder_for_iso_8859_1()
{
    x_note_fn_call(26,208);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)1L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_1),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-2 */
Object g2int_create_transcoder_for_iso_8859_2()
{
    x_note_fn_call(26,209);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)2L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_2),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-3 */
Object g2int_create_transcoder_for_iso_8859_3()
{
    x_note_fn_call(26,210);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)4L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_3),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-4 */
Object g2int_create_transcoder_for_iso_8859_4()
{
    x_note_fn_call(26,211);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)4L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_4),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-5 */
Object g2int_create_transcoder_for_iso_8859_5()
{
    x_note_fn_call(26,212);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)5L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_5),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-6 */
Object g2int_create_transcoder_for_iso_8859_6()
{
    x_note_fn_call(26,213);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)6L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_6),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-7 */
Object g2int_create_transcoder_for_iso_8859_7()
{
    x_note_fn_call(26,214);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)7L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_7),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-8 */
Object g2int_create_transcoder_for_iso_8859_8()
{
    x_note_fn_call(26,215);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)8L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_8),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-9 */
Object g2int_create_transcoder_for_iso_8859_9()
{
    x_note_fn_call(26,216);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)9L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_9),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-10 */
Object g2int_create_transcoder_for_iso_8859_10()
{
    x_note_fn_call(26,217);
    return g2int_make_iso_8859_transcoder_1(FIX((SI_Long)10L),
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_10),
	    Qg2int_graphic_character_set));
}

/* CREATE-TRANSCODER-FOR-GENSYM */
Object g2int_create_transcoder_for_gensym()
{
    x_note_fn_call(26,218);
    return g2int_make_utf_g_transcoder_1();
}

/* CREATE-TRANSCODER-FOR-GENSYM-WITH-ASCII-AS-MUCH-AS-POSSIBLE */
Object g2int_create_transcoder_for_gensym_with_ascii_as_much_as_possible()
{
    x_note_fn_call(26,219);
    return g2int_make_utf_g_ascii_as_much_as_possible_transcoder_1();
}

/* CREATE-TRANSCODER-FOR-UNICODE-UCS-2 */
Object g2int_create_transcoder_for_unicode_ucs_2()
{
    x_note_fn_call(26,220);
    return g2int_make_unicode_ucs_2_transcoder_1();
}

/* CREATE-TRANSCODER-FOR-UNICODE-UCS-2-BYTE-SWAPPED */
Object g2int_create_transcoder_for_unicode_ucs_2_byte_swapped()
{
    Object transcoder;

    x_note_fn_call(26,221);
    transcoder = g2int_make_unicode_ucs_2_transcoder_1();
    SVREF(transcoder,FIX((SI_Long)7L)) = T;
    return VALUES_1(transcoder);
}

/* CREATE-TRANSCODER-FOR-UNICODE */
Object g2int_create_transcoder_for_unicode()
{
    x_note_fn_call(26,222);
    return g2int_make_unicode_transcoder_1();
}

/* CREATE-TRANSCODER-FOR-UNICODE-BYTE-SWAPPED */
Object g2int_create_transcoder_for_unicode_byte_swapped()
{
    x_note_fn_call(26,223);
    return g2int_make_unicode_byte_swapped_transcoder_1();
}

static Object Qg2int_transcoder_creation_function;  /* transcoder-creation-function */

/* MAKE-TRANSCODER-PER-TEXT-CONVERSION-STYLE */
Object g2int_make_transcoder_per_text_conversion_style(text_conversion_style,
	    text_sequence)
    Object text_conversion_style, text_sequence;
{
    Object gensymed_symbol, funcallable_creator;
    Object text_conversion_style_for_transcoder_being_created, transcoder;
    Declare_special(1);
    Object result;

    x_note_fn_call(26,224);
    gensymed_symbol = ISVREF(text_conversion_style,(SI_Long)2L);
    funcallable_creator = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_transcoder_creation_function);
    text_conversion_style_for_transcoder_being_created = text_conversion_style;
    PUSH_SPECIAL(G2int_text_conversion_style_for_transcoder_being_created,text_conversion_style_for_transcoder_being_created,
	    0);
      transcoder = FUNCALL_0(funcallable_creator);
      SVREF(transcoder,FIX((SI_Long)1L)) = text_sequence;
      SVREF(transcoder,FIX((SI_Long)4L)) = text_conversion_style;
      result = VALUES_1(transcoder);
    POP_SPECIAL();
    return result;
}

/* TWRITE-ASCII-FROM-WIDE-STRING */
Object g2int_twrite_ascii_from_wide_string(wide_string)
    Object wide_string;
{
    Object wide_character, temp, schar_arg_2, schar_new_value, thing_1;
    SI_Long length_of_string, i, ab_loop_bind_, thing;

    x_note_fn_call(26,225);
    length_of_string = IFIX(g2int_lengthw(wide_string));
    i = (SI_Long)0L;
    ab_loop_bind_ = length_of_string;
    wide_character = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = FIX(UBYTE_16_ISAREF_1(wide_string,i));
    if (g2int_newline_p(wide_character)) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = (SI_Long)10L;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)10L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
    }
    else if (IFIX(wide_character) < (SI_Long)256L) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = wide_character;
	    g2int_twrite_wide_character(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
    }
    else;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* MAP-JIS-X-0208-BYTES-TO-UNICODE-CHARACTER */
Object g2int_map_jis_x_0208_bytes_to_unicode_character(lead_byte,trail_byte)
    Object lead_byte, trail_byte;
{
    Object contiguous_code_qm, temp;
    SI_Long jis_x_0208;

    x_note_fn_call(26,226);
    if ((SI_Long)33L <= IFIX(lead_byte) && IFIX(lead_byte) <= 
	    (SI_Long)116L && (SI_Long)33L <= IFIX(trail_byte) && 
	    IFIX(trail_byte) <= (SI_Long)126L) {
	jis_x_0208 = (IFIX(lead_byte) << (SI_Long)8L) + IFIX(trail_byte);
	contiguous_code_qm = 
		g2int_gensym_jis_code_to_contiguous(FIX(jis_x_0208));
	temp = contiguous_code_qm ? 
		FIX(UBYTE_16_ISAREF_1(G2int_jis_x_0208_to_unicode_map,
		IFIX(contiguous_code_qm))) : Nil;
    }
    else
	temp = G2int_unicode_replacement_character;
    return VALUES_1(temp);
}

/* MAP-KS-C-5601-BYTES-TO-UNICODE-CHARACTER */
Object g2int_map_ks_c_5601_bytes_to_unicode_character(lead_byte,trail_byte)
    Object lead_byte, trail_byte;
{
    Object gensym_ks_c_5601, contiguous_code_qm, temp;
    SI_Long ks_c_5601;

    x_note_fn_call(26,227);
    if ((SI_Long)33L <= IFIX(lead_byte) && IFIX(lead_byte) <= 
	    (SI_Long)125L && (SI_Long)33L <= IFIX(trail_byte) && 
	    IFIX(trail_byte) <= (SI_Long)126L) {
	ks_c_5601 = (IFIX(lead_byte) << (SI_Long)8L) + IFIX(trail_byte);
	gensym_ks_c_5601 = g2int_ksc_to_gensym_ksc(FIX(ks_c_5601));
	contiguous_code_qm = 
		g2int_gensym_ksc_code_to_contiguous(gensym_ks_c_5601);
	temp = contiguous_code_qm ? 
		FIX(UBYTE_16_ISAREF_1(G2int_ks_c_5601_to_unicode_map,
		IFIX(contiguous_code_qm))) : Nil;
    }
    else
	temp = G2int_unicode_replacement_character;
    return VALUES_1(temp);
}

/* MAP-GB-2312-BYTES-TO-UNICODE-CHARACTER */
Object g2int_map_gb_2312_bytes_to_unicode_character(lead_byte,trail_byte)
    Object lead_byte, trail_byte;
{
    Object temp;
    SI_Long gb_2312, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long index_1, code;

    x_note_fn_call(26,228);
    if ((SI_Long)33L <= IFIX(lead_byte) && IFIX(lead_byte) <= 
	    (SI_Long)125L && (SI_Long)33L <= IFIX(trail_byte) && 
	    IFIX(trail_byte) <= (SI_Long)126L) {
	gb_2312 = (IFIX(lead_byte) << (SI_Long)8L) + IFIX(trail_byte);
	gensymed_symbol = ((gb_2312 >>  -  - (SI_Long)8L) - (SI_Long)33L) 
		* (SI_Long)94L;
	gensymed_symbol_1 = (SI_Long)255L & gb_2312;
	gensymed_symbol_2 = (SI_Long)33L;
	gensymed_symbol_2 = gensymed_symbol_1 - gensymed_symbol_2;
	index_1 = gensymed_symbol + gensymed_symbol_2;
	code = (SI_Long)0L;
	if ((SI_Long)0L <= index_1 && index_1 <= (SI_Long)8177L) {
	    code = UBYTE_16_ISAREF_1(G2int_gb_2312_to_unicode_map,index_1);
	    temp = code == (SI_Long)65535L ? Nil : FIX(code);
	}
	else
	    temp = Nil;
    }
    else
	temp = G2int_unicode_replacement_character;
    return VALUES_1(temp);
}

/* MAP-SHIFT-JIS-BYTES-TO-UNICODE-CHARACTER */
Object g2int_map_shift_jis_bytes_to_unicode_character(lead_byte_init,
	    trail_byte_init)
    Object lead_byte_init, trail_byte_init;
{
    SI_Long lead_byte, trail_byte, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,229);
    lead_byte = IFIX(lead_byte_init);
    trail_byte = IFIX(trail_byte_init);
    gensymed_symbol = lead_byte;
    gensymed_symbol_1 = lead_byte < (SI_Long)208L ? (SI_Long)113L : 
	    (SI_Long)177L;
    lead_byte = gensymed_symbol - gensymed_symbol_1;
    if (trail_byte > (SI_Long)127L)
	trail_byte = trail_byte - (SI_Long)1L;
    lead_byte = lead_byte >>  -  - (SI_Long)1L;
    if (trail_byte > (SI_Long)157L) {
	lead_byte = lead_byte + (SI_Long)1L;
	trail_byte = trail_byte - (SI_Long)94L;
    }
    trail_byte = trail_byte - (SI_Long)31L;
    lead_byte = lead_byte + (SI_Long)1L;
    return VALUES_1(FIX((lead_byte << (SI_Long)8L) + trail_byte));
}

/* MAP-SHIFT-JIS-HALF-WIDTH-KATAKANA-TO-UNICODE */
Object g2int_map_shift_jis_half_width_katakana_to_unicode(shift_jis_half_width_katakana_character)
    Object shift_jis_half_width_katakana_character;
{
    Object code;

    x_note_fn_call(26,230);
    code = shift_jis_half_width_katakana_character;
    return VALUES_1(FIX(IFIX(code) - (SI_Long)160L + (SI_Long)65376L));
}

/* SHIFT-JIS-X-0208-IN-TEXT-SEQUENCE-TO-UNICODE */
Object g2int_shift_jis_x_0208_in_text_sequence_to_unicode(text_sequence,
	    character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    SI_Long arg, arg_1, arg_2;
    char temp_1;

    x_note_fn_call(26,231);
    if (IFIX(character_1) < (SI_Long)128L)
	temp = character_1;
    else {
	arg = (SI_Long)161L;
	arg_1 = IFIX(character_1);
	arg_2 = (SI_Long)223L;
	if (arg <= arg_1 && arg_1 <= arg_2)
	    temp = 
		    g2int_map_shift_jis_half_width_katakana_to_unicode(character_1);
	else {
	    arg = (SI_Long)129L;
	    arg_1 = IFIX(character_1);
	    arg_2 = (SI_Long)159L;
	    temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	    if (temp_1);
	    else {
		arg = (SI_Long)224L;
		arg_1 = IFIX(character_1);
		arg_2 = (SI_Long)239L;
		temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	    }
	    if (temp_1) {
		if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
			ISVREF(text_sequence,(SI_Long)3L)))
		    temp = G2int_unicode_replacement_character;
		else {
		    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
		    gensymed_symbol = 
			    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
			    (SI_Long)9L),(SI_Long)11L);
		    gensymed_symbol_1 = text_sequence;
		    temp = 
			    g2int_map_shift_jis_bytes_to_unicode_character(character_1,
			    inline_funcall_1(gensymed_symbol,
			    gensymed_symbol_1));
		}
	    }
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

/* JIS-X-0208-EUC-IN-TEXT-SEQUENCE-TO-UNICODE */
Object g2int_jis_x_0208_euc_in_text_sequence_to_unicode(text_sequence,
	    character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(26,232);
    if (IFIX(character_1) < (SI_Long)160L)
	temp = character_1;
    else if (IFIX(character_1) < (SI_Long)128L)
	temp = G2int_unicode_replacement_character;
    else if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
	    ISVREF(text_sequence,(SI_Long)3L)))
	temp = G2int_unicode_replacement_character;
    else {
	temp = FIX(IFIX(character_1) >>  -  - (SI_Long)1L);
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	gensymed_symbol_2 = IFIX(inline_funcall_1(gensymed_symbol,
		gensymed_symbol_1));
	gensymed_symbol_3 = (SI_Long)1L;
	temp = g2int_map_jis_x_0208_bytes_to_unicode_character(temp,
		FIX(gensymed_symbol_2 >>  -  - gensymed_symbol_3));
    }
    return VALUES_1(temp);
}

/* KS-C-5601-EUC-IN-TEXT-SEQUENCE-TO-UNICODE */
Object g2int_ks_c_5601_euc_in_text_sequence_to_unicode(text_sequence,
	    character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(26,233);
    if (IFIX(character_1) < (SI_Long)160L)
	temp = character_1;
    else if (IFIX(character_1) < (SI_Long)128L)
	temp = G2int_unicode_replacement_character;
    else if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
	    ISVREF(text_sequence,(SI_Long)3L)))
	temp = G2int_unicode_replacement_character;
    else {
	temp = FIX(IFIX(character_1) >>  -  - (SI_Long)1L);
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	gensymed_symbol_2 = IFIX(inline_funcall_1(gensymed_symbol,
		gensymed_symbol_1));
	gensymed_symbol_3 = (SI_Long)1L;
	temp = g2int_map_ks_c_5601_bytes_to_unicode_character(temp,
		FIX(gensymed_symbol_2 >>  -  - gensymed_symbol_3));
    }
    return VALUES_1(temp);
}

/* GB-2312-EUC-IN-TEXT-SEQUENCE-TO-UNICODE */
Object g2int_gb_2312_euc_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(26,234);
    if (IFIX(character_1) < (SI_Long)160L)
	temp = character_1;
    else if (IFIX(character_1) < (SI_Long)128L)
	temp = G2int_unicode_replacement_character;
    else if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
	    ISVREF(text_sequence,(SI_Long)3L)))
	temp = G2int_unicode_replacement_character;
    else {
	temp = FIX(IFIX(character_1) >>  -  - (SI_Long)1L);
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	gensymed_symbol_2 = IFIX(inline_funcall_1(gensymed_symbol,
		gensymed_symbol_1));
	gensymed_symbol_3 = (SI_Long)1L;
	temp = g2int_map_gb_2312_bytes_to_unicode_character(temp,
		FIX(gensymed_symbol_2 >>  -  - gensymed_symbol_3));
    }
    return VALUES_1(temp);
}

/* JIS-X-0208-IN-TEXT-SEQUENCE-TO-UNICODE */
Object g2int_jis_x_0208_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,235);
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	temp = G2int_unicode_replacement_character;
    else {
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	temp = g2int_map_jis_x_0208_bytes_to_unicode_character(character_1,
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
    return VALUES_1(temp);
}

/* KS-C-5601-IN-TEXT-SEQUENCE-TO-UNICODE */
Object g2int_ks_c_5601_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,236);
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	temp = G2int_unicode_replacement_character;
    else {
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	temp = g2int_map_ks_c_5601_bytes_to_unicode_character(character_1,
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
    return VALUES_1(temp);
}

/* GB-2312-IN-TEXT-SEQUENCE-TO-UNICODE */
Object g2int_gb_2312_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(26,237);
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	temp = G2int_unicode_replacement_character;
    else {
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	temp = g2int_map_gb_2312_bytes_to_unicode_character(character_1,
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
    return VALUES_1(temp);
}

/* IMPORT-TEXT-STRING */
Object g2int_import_text_string varargs_1(int, n)
{
    Object string_1;
    Object purpose, start_qm, end_qm, style;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,238);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    purpose = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    style = g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(purpose),
	    Qg2int_text_conversion_style_for_purpose);
    if (style);
    else
	style = G2int_default_text_conversion_style;
    return g2int_import_text_string_per_text_conversion_style(4,string_1,
	    style,start_qm,end_qm);
}

/* IMPORT-TEXT-STRING-PER-TEXT-CONVERSION-STYLE */
Object g2int_import_text_string_per_text_conversion_style varargs_1(int, n)
{
    Object string_1, text_conversion_style;
    Object start_qm, end_qm, text_sequence, transcoder, gensymed_symbol;
    Object gensymed_symbol_1, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,239);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    text_conversion_style = REQUIRED_ARG_nonrelocating();
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    text_sequence = g2int_make_text_sequence(string_1,start_qm,end_qm);
    transcoder = 
	    g2int_make_transcoder_per_text_conversion_style(text_conversion_style,
	    text_sequence);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)14L);
    gensymed_symbol_1 = transcoder;
    temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = transcoder;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = text_sequence;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(temp);
}

/* EXPORT-TEXT-STRING-PER-TEXT-CONVERSION-STYLE */
Object g2int_export_text_string_per_text_conversion_style varargs_1(int, n)
{
    Object text_string, text_conversion_style;
    Object start_qm, end_qm, text_sequence, transcoder, gensymed_symbol;
    Object gensymed_symbol_1, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,240);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    text_conversion_style = REQUIRED_ARG_nonrelocating();
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    text_sequence = g2int_make_text_sequence(text_string,start_qm,end_qm);
    transcoder = 
	    g2int_make_transcoder_per_text_conversion_style(text_conversion_style,
	    text_sequence);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)16L);
    gensymed_symbol_1 = transcoder;
    temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = transcoder;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = text_sequence;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(temp);
}

/* EXPORT-TEXT-STRING */
Object g2int_export_text_string varargs_1(int, n)
{
    Object text_string;
    Object purpose, start_qm, end_qm, style;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,241);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    purpose = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    style = g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(purpose),
	    Qg2int_text_conversion_style_for_purpose);
    if (style);
    else
	style = G2int_default_text_conversion_style;
    return g2int_export_text_string_per_text_conversion_style(4,
	    text_string,style,start_qm,end_qm);
}

/* UNICODE-KNOWN-ISO-LATIN1-TO-GENSYM-STRING */
Object g2int_unicode_known_iso_latin1_to_gensym_string(text_string)
    Object text_string;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object character_1, temp, schar_arg_2, schar_new_value, temp_1;
    SI_Long i, ab_loop_bind_, gensymed_symbol, simple_or_wide_character, thing;
    Declare_special(4);

    x_note_fn_call(26,242);
    current_gensym_string = 
	    g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qg2int_gensym_string;
	  PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		  0);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(g2int_text_string_length(text_string));
	    character_1 = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    character_1 = FIX(UBYTE_16_ISAREF_1(text_string,i));
	    gensymed_symbol = (SI_Long)255L & IFIX(character_1);
	    simple_or_wide_character = gensymed_symbol;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = simple_or_wide_character;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    temp_1 = g2int_copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

Object G2int_utf_7_modified_base64_characters = UNBOUND;

/* UTF-7-BASE64-DIGIT-CHAR-P */
Object g2int_utf_7_base64_digit_char_p(wide_character)
    Object wide_character;
{
    Object unicode, temp;

    x_note_fn_call(26,243);
    unicode = wide_character;
    temp = g2int_utf_7_base64_digit_char_code_p(unicode);
    return VALUES_1(temp);
}

/* UTF-7-BASE64-DIGIT-CHAR-CODE-P */
Object g2int_utf_7_base64_digit_char_code_p(unicode)
    Object unicode;
{
    Object temp;

    x_note_fn_call(26,244);
    if ((SI_Long)65L <= IFIX(unicode) && IFIX(unicode) <= (SI_Long)90L)
	temp = FIX(IFIX(unicode) - (SI_Long)65L);
    else if ((SI_Long)97L <= IFIX(unicode) && IFIX(unicode) <= (SI_Long)122L)
	temp = FIX((SI_Long)26L + (IFIX(unicode) - (SI_Long)97L));
    else if ((SI_Long)48L <= IFIX(unicode) && IFIX(unicode) <= (SI_Long)57L)
	temp = FIX((SI_Long)52L + (IFIX(unicode) - (SI_Long)48L));
    else if (IFIX(unicode) == (SI_Long)43L)
	temp = FIX((SI_Long)62L);
    else if (IFIX(unicode) == (SI_Long)47L)
	temp = FIX((SI_Long)63L);
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object G2int_utf_7_ultraconservative_p = UNBOUND;

Object G2int_utf_7_delimit_encoded_sequences_p = UNBOUND;

Object G2int_the_type_description_of_utf_7_transcoder = UNBOUND;

Object G2int_chain_of_available_utf_7_transcoders = UNBOUND;

Object G2int_utf_7_transcoder_count = UNBOUND;

/* RECLAIM-UTF-7-TRANSCODER-1 */
Object g2int_reclaim_utf_7_transcoder_1(utf_7_transcoder)
    Object utf_7_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,245);
    inline_note_reclaim_cons(utf_7_transcoder,Nil);
    svref_new_value = G2int_chain_of_available_utf_7_transcoders;
    SVREF(utf_7_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_utf_7_transcoders = utf_7_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UTF-7-TRANSCODER */
Object g2int_reclaim_structure_for_utf_7_transcoder(utf_7_transcoder)
    Object utf_7_transcoder;
{
    x_note_fn_call(26,246);
    return g2int_reclaim_utf_7_transcoder_1(utf_7_transcoder);
}

static Object Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct;  /* g2-defstruct-structure-name::utf-7-transcoder-g2-struct */

/* MAKE-PERMANENT-UTF-7-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_utf_7_transcoder_structure_internal()
{
    Object def_structure_utf_7_transcoder_variable, temp;
    Object defstruct_g2_utf_7_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,247);
    def_structure_utf_7_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_utf_7_transcoder_count);
    G2int_utf_7_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_utf_7_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)6L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_utf_7_transcoder_variable = the_array;
	SVREF(defstruct_g2_utf_7_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct;
	SVREF(defstruct_g2_utf_7_transcoder_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_utf_7_transcoder_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_utf_7_transcoder_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_utf_7_transcoder_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_utf_7_transcoder_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_utf_7_transcoder_variable = 
		defstruct_g2_utf_7_transcoder_variable;
	SVREF(def_structure_utf_7_transcoder_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_utf_7_transcoder_variable,FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_utf_7_transcoders;
	SVREF(def_structure_utf_7_transcoder_variable,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_utf_7_transcoders = 
		def_structure_utf_7_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_utf_7_transcoder_variable);
}

/* MAKE-UTF-7-TRANSCODER-1 */
Object g2int_make_utf_7_transcoder_1()
{
    Object def_structure_utf_7_transcoder_variable;

    x_note_fn_call(26,248);
    def_structure_utf_7_transcoder_variable = 
	    G2int_chain_of_available_utf_7_transcoders;
    if (def_structure_utf_7_transcoder_variable) {
	G2int_chain_of_available_utf_7_transcoders = 
		ISVREF(def_structure_utf_7_transcoder_variable,(SI_Long)0L);
	SVREF(def_structure_utf_7_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct;
    }
    else
	def_structure_utf_7_transcoder_variable = 
		g2int_make_permanent_utf_7_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_utf_7_transcoder_variable,Nil);
    ISVREF(def_structure_utf_7_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_utf_7_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_utf_7_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_utf_7_transcoder_variable);
}

/* CREATE-TRANSCODER-FOR-UNICODE-UTF-7 */
Object g2int_create_transcoder_for_unicode_utf_7()
{
    x_note_fn_call(26,249);
    return g2int_make_utf_7_transcoder_1();
}

/* TRANSCODE-CHARACTER-FOR-UTF-7-TRANSCODER */
Object g2int_transcode_character_for_utf_7_transcoder(utf_7_transcoder)
    Object utf_7_transcoder;
{
    Object transcoder;
    SI_Long character_1, unicode;

    x_note_fn_call(26,250);
    transcoder = utf_7_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    if (character_1 < (SI_Long)32L) {
	if (character_1 == (SI_Long)10L && IFIX(ISVREF(transcoder,
		(SI_Long)3L)) == (SI_Long)13L)
	    return VALUES_1(FIX((SI_Long)65535L));
	else if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L)
	    return VALUES_1(FIX((SI_Long)8232L));
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 < (SI_Long)128L) {
	if (character_1 == (SI_Long)43L)
	    return g2int_transcode_utf_7_base64(transcoder);
	else {
	    unicode = character_1;
	    if (unicode < (SI_Long)127L && (unicode < (SI_Long)32L ? 
		    unicode == (SI_Long)9L || unicode == (SI_Long)13L || 
		    unicode == (SI_Long)10L : 
		    G2int_utf_7_ultraconservative_p ? (SI_Long)65L <= 
		    unicode && unicode <= (SI_Long)90L || (SI_Long)97L <= 
		    unicode && unicode <= (SI_Long)122L || (SI_Long)39L <= 
		    unicode && unicode <= (SI_Long)41L || (SI_Long)44L <= 
		    unicode && unicode <= (SI_Long)47L || unicode == 
		    (SI_Long)32L || unicode == (SI_Long)58L || unicode == 
		    (SI_Long)63L :  !(unicode == (SI_Long)61L) &&  
		    !(unicode == (SI_Long)43L)))
		return VALUES_1(FIX(character_1));
	    else
		return g2int_transcode_unhandled_character(FIX(character_1),
			transcoder);
	}
    }
    else
	return g2int_transcode_unhandled_character(FIX(character_1),
		transcoder);
}

/* TRANSCODE-UTF-7-BASE64 */
Object g2int_transcode_utf_7_base64(transcoder)
    Object transcoder;
{
    Object buffered_sextets_in_reverse_order, first_time_qm;
    Object post_base64_character_qm, character_1, sextet, temp;
    Object gensym_pop_store, cons_1, next_cons;

    x_note_fn_call(26,251);
    buffered_sextets_in_reverse_order = Qnil;
    first_time_qm = T;
    post_base64_character_qm = Nil;
    character_1 = Nil;
    sextet = Nil;
  next_loop:
    character_1 = g2int_get_transcoder_character_if_any(transcoder);
    if ( !TRUEP(character_1))
	goto end_loop;
    sextet = g2int_utf_7_base64_digit_char_p(character_1);
    if (sextet)
	buffered_sextets_in_reverse_order = g2int_gensym_cons_1(sextet,
		buffered_sextets_in_reverse_order);
    else if (first_time_qm) {
	if (IFIX(character_1) == (SI_Long)45L)
	    return VALUES_1(FIX((SI_Long)43L));
	else
	    return g2int_transcode_unhandled_character(character_1,transcoder);
    }
    else if (IFIX(character_1) == (SI_Long)45L)
	goto end_loop;
    else {
	post_base64_character_qm = character_1;
	goto end_loop;
    }
    first_time_qm = Nil;
    goto next_loop;
  end_loop:
    if (g2int_emit_buffered_utf_7_base64_sextets_as_unicodes(transcoder,
	    buffered_sextets_in_reverse_order))
	return g2int_transcode_unhandled_character(character_1,transcoder);
    else {
	if (post_base64_character_qm) {
	    temp = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    g2int_gensym_cons_1(post_base64_character_qm,Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = temp;
	}
	gensym_pop_store = Nil;
	cons_1 = ISVREF(transcoder,(SI_Long)5L);
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(cons_1) = temp;
	    G2int_available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	SVREF(transcoder,FIX((SI_Long)5L)) = next_cons;
	return VALUES_1(gensym_pop_store);
    }
    return VALUES_1(Qnil);
}

/* EMIT-BUFFERED-UNICODES-AS-UTF-7-BASE64-TO-TRANSCODER */
Object g2int_emit_buffered_unicodes_as_utf_7_base64_to_transcoder(buffered_unicodes_in_reverse_order,
	    transcoder)
    Object buffered_unicodes_in_reverse_order, transcoder;
{
    Object buffered_unicodes, unicode, ab_loop_list_, octets, ab_loopvar_;
    Object ab_loopvar__1;
    SI_Long gensymed_symbol;

    x_note_fn_call(26,252);
    buffered_unicodes = nreverse(buffered_unicodes_in_reverse_order);
    unicode = Nil;
    ab_loop_list_ = buffered_unicodes;
    octets = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    unicode = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = g2int_gensym_cons_1(FIX(IFIX(unicode) >>  -  - 
	    (SI_Long)8L),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	octets = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    gensymed_symbol = IFIX(unicode) & (SI_Long)255L;
    ab_loopvar__1 = g2int_gensym_cons_1(FIX(gensymed_symbol),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	octets = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    g2int_reclaim_gensym_list_1(buffered_unicodes);
    g2int_emit_buffered_octets_as_utf_7_base64_to_transcoder(octets,
	    transcoder);
    return VALUES_1(Qnil);
}

/* EMIT-BUFFERED-OCTETS-AS-UTF-7-BASE64-TO-TRANSCODER */
Object g2int_emit_buffered_octets_as_utf_7_base64_to_transcoder(buffered_octets,
	    transcoder)
    Object buffered_octets, transcoder;
{
    Object octet_1, octet_2_qm, octet_3_qm, ab_loop_list_, temp, sextet_3_qm;
    Object sextet_4_qm, svref_new_value;
    SI_Long sextet_1, gensymed_symbol, gensymed_symbol_1, sextet_2;
    SI_Long character_1;

    x_note_fn_call(26,253);
    octet_1 = Nil;
    octet_2_qm = Nil;
    octet_3_qm = Nil;
    ab_loop_list_ = buffered_octets;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    octet_1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    octet_2_qm = CAR(temp);
    temp = CDR(ab_loop_list_);
    temp = CDR(temp);
    octet_3_qm = CAR(temp);
    sextet_1 = IFIX(octet_1) >>  -  - (SI_Long)2L;
    gensymed_symbol = (IFIX(octet_1) & (SI_Long)3L) << (SI_Long)4L;
    gensymed_symbol_1 = octet_2_qm ? IFIX(octet_2_qm) >>  -  - (SI_Long)4L 
	    : (SI_Long)0L;
    sextet_2 = gensymed_symbol + gensymed_symbol_1;
    if (octet_2_qm) {
	gensymed_symbol = (IFIX(octet_2_qm) & (SI_Long)15L) << (SI_Long)2L;
	gensymed_symbol_1 = octet_3_qm ? IFIX(octet_3_qm) >>  -  - 
		(SI_Long)6L : (SI_Long)0L;
	sextet_3_qm = FIX(gensymed_symbol + gensymed_symbol_1);
    }
    else
	sextet_3_qm = Nil;
    sextet_4_qm = octet_3_qm ? FIX(IFIX(octet_3_qm) & (SI_Long)63L) : Nil;
    character_1 = UBYTE_16_ISAREF_1(G2int_utf_7_modified_base64_characters,
	    sextet_1);
    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
	    g2int_gensym_cons_1(FIX(character_1),Nil));
    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    character_1 = UBYTE_16_ISAREF_1(G2int_utf_7_modified_base64_characters,
	    sextet_2);
    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
	    g2int_gensym_cons_1(FIX(character_1),Nil));
    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    if (sextet_3_qm) {
	character_1 = 
		UBYTE_16_ISAREF_1(G2int_utf_7_modified_base64_characters,
		IFIX(sextet_3_qm));
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		g2int_gensym_cons_1(FIX(character_1),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    }
    if (sextet_4_qm) {
	character_1 = 
		UBYTE_16_ISAREF_1(G2int_utf_7_modified_base64_characters,
		IFIX(sextet_4_qm));
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		g2int_gensym_cons_1(FIX(character_1),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    }
    ab_loop_list_ = CDDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    return g2int_reclaim_gensym_list_1(buffered_octets);
}

static Object Qg2int_illegal_utf_7_base64_character;  /* illegal-utf-7-base64-character */

/* EMIT-BUFFERED-UTF-7-BASE64-SEXTETS-AS-UNICODES */
Object g2int_emit_buffered_utf_7_base64_sextets_as_unicodes(transcoder,
	    buffered_sextets_in_reverse_order)
    Object transcoder, buffered_sextets_in_reverse_order;
{
    Object buffered_sextets, octet_1, octet_2_qm, octet_3_qm, sextet_1;
    Object sextet_2_qm, sextet_3_qm, sextet_4_qm, ab_loop_list_;
    Object buffered_octets, ab_loopvar_, ab_loopvar__1, temp;
    SI_Long j, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(26,254);
    buffered_sextets = nreverse(buffered_sextets_in_reverse_order);
    octet_1 = Nil;
    octet_2_qm = Nil;
    octet_3_qm = Nil;
    j = (SI_Long)0L;
    sextet_1 = Nil;
    sextet_2_qm = Nil;
    sextet_3_qm = Nil;
    sextet_4_qm = Nil;
    ab_loop_list_ = buffered_sextets;
    buffered_octets = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    octet_2_qm = Nil;
    octet_3_qm = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    sextet_1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    sextet_2_qm = CAR(temp);
    temp = CDR(ab_loop_list_);
    temp = CDR(temp);
    sextet_3_qm = CAR(temp);
    temp = CDR(ab_loop_list_);
    temp = CDR(temp);
    temp = CDR(temp);
    sextet_4_qm = CAR(temp);
    if ( !TRUEP(sextet_2_qm)) {
	g2int_reclaim_gensym_list_1(buffered_sextets_in_reverse_order);
	return VALUES_1(Qg2int_illegal_utf_7_base64_character);
    }
    else {
	octet_1 = FIX((IFIX(sextet_1) << (SI_Long)2L) + (IFIX(sextet_2_qm) 
		>>  -  - (SI_Long)4L));
	if (sextet_3_qm) {
	    gensymed_symbol = (IFIX(sextet_2_qm) & (SI_Long)15L) << 
		    (SI_Long)4L;
	    temp = sextet_3_qm;
	    if (temp);
	    else
		temp = FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(temp);
	    gensymed_symbol_2 = (SI_Long)2L;
	    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	    octet_2_qm = FIX(gensymed_symbol + gensymed_symbol_1);
	    gensymed_symbol = (IFIX(sextet_3_qm) & (SI_Long)3L) << (SI_Long)6L;
	    temp = sextet_4_qm;
	    if (temp);
	    else
		temp = FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(temp);
	    octet_3_qm = FIX(gensymed_symbol + gensymed_symbol_1);
	}
    }
    ab_loopvar__1 = g2int_gensym_cons_1(octet_1,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	buffered_octets = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    if (octet_2_qm) {
	ab_loopvar__1 = g2int_gensym_cons_1(octet_2_qm,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    buffered_octets = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    if (octet_3_qm) {
	ab_loopvar__1 = g2int_gensym_cons_1(octet_3_qm,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    buffered_octets = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    octet_2_qm = Nil;
    octet_3_qm = Nil;
    j = j + (SI_Long)4L;
    ab_loop_list_ = CDDDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    g2int_reclaim_gensym_list_1(buffered_sextets);
    return g2int_emit_buffered_octets_as_unicodes(transcoder,buffered_octets);
    return VALUES_1(Qnil);
}

static Object Qg2int_ill_formed_octet_stream_odd_number;  /* ill-formed-octet-stream-odd-number */

/* EMIT-BUFFERED-OCTETS-AS-UNICODES */
Object g2int_emit_buffered_octets_as_unicodes(transcoder,buffered_octets)
    Object transcoder, buffered_octets;
{
    Object octet_1, octet_2_qm, ab_loop_list_, temp, svref_new_value;
    SI_Long j, character_1;

    x_note_fn_call(26,255);
    octet_1 = Nil;
    octet_2_qm = Nil;
    ab_loop_list_ = buffered_octets;
    j = (SI_Long)0L;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    octet_1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    octet_2_qm = CAR(temp);
  next_loop:
    if ( !TRUEP(octet_2_qm) &&  !(IFIX(octet_1) == (SI_Long)0L)) {
	g2int_reclaim_gensym_list_1(buffered_octets);
	return VALUES_1(Qg2int_ill_formed_octet_stream_odd_number);
    }
    if (octet_2_qm) {
	character_1 = (IFIX(octet_1) << (SI_Long)8L) + IFIX(octet_2_qm);
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		g2int_gensym_cons_1(FIX(character_1),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    octet_1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    octet_2_qm = CAR(temp);
    j = j + (SI_Long)3L;
    goto next_loop;
  end_loop:
    g2int_reclaim_gensym_list_1(buffered_octets);
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* EXPORT-CHARACTER-FOR-UTF-7-TRANSCODER */
Object g2int_export_character_for_utf_7_transcoder(utf_7_transcoder)
    Object utf_7_transcoder;
{
    Object transcoder;
    SI_Long character_1, unicode;

    x_note_fn_call(26,256);
    transcoder = utf_7_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    unicode = character_1;
    if (unicode < (SI_Long)127L && (unicode < (SI_Long)32L ? unicode == 
	    (SI_Long)9L || unicode == (SI_Long)13L || unicode == 
	    (SI_Long)10L : G2int_utf_7_ultraconservative_p ? (SI_Long)65L 
	    <= unicode && unicode <= (SI_Long)90L || (SI_Long)97L <= 
	    unicode && unicode <= (SI_Long)122L || (SI_Long)39L <= unicode 
	    && unicode <= (SI_Long)41L || (SI_Long)44L <= unicode && 
	    unicode <= (SI_Long)47L || unicode == (SI_Long)32L || unicode 
	    == (SI_Long)58L || unicode == (SI_Long)63L :  !(unicode == 
	    (SI_Long)61L) &&  !(unicode == (SI_Long)43L)))
	return VALUES_1(FIX(character_1));
    else
	return g2int_export_utf_7_base64(FIX(character_1),transcoder);
}

/* EXPORT-UTF-7-BASE64 */
Object g2int_export_utf_7_base64(first_non_direct_character_init,transcoder)
    Object first_non_direct_character_init, transcoder;
{
    Object reversed_buffered_unicodes, character_qm, unicode, svref_new_value;
    Object temp;
    SI_Long first_non_direct_character;

    x_note_fn_call(26,257);
    first_non_direct_character = IFIX(first_non_direct_character_init);
    reversed_buffered_unicodes = 
	    g2int_gensym_cons_1(FIX(first_non_direct_character),Nil);
    character_qm = Nil;
  next_loop:
    character_qm = g2int_get_transcoder_character_if_any(transcoder);
    if ( !TRUEP(character_qm))
	goto end_loop;
    unicode = character_qm;
    if (IFIX(unicode) < (SI_Long)127L && (IFIX(unicode) < (SI_Long)32L ? 
	    IFIX(unicode) == (SI_Long)9L || IFIX(unicode) == (SI_Long)13L 
	    || IFIX(unicode) == (SI_Long)10L : 
	    G2int_utf_7_ultraconservative_p ? (SI_Long)65L <= 
	    IFIX(unicode) && IFIX(unicode) <= (SI_Long)90L || (SI_Long)97L 
	    <= IFIX(unicode) && IFIX(unicode) <= (SI_Long)122L || 
	    (SI_Long)39L <= IFIX(unicode) && IFIX(unicode) <= (SI_Long)41L 
	    || (SI_Long)44L <= IFIX(unicode) && IFIX(unicode) <= 
	    (SI_Long)47L || IFIX(unicode) == (SI_Long)32L || IFIX(unicode) 
	    == (SI_Long)58L || IFIX(unicode) == (SI_Long)63L :  
	    !(IFIX(unicode) == (SI_Long)61L) &&  !(IFIX(unicode) == 
	    (SI_Long)43L)))
	goto end_loop;
    reversed_buffered_unicodes = g2int_gensym_cons_1(character_qm,
	    reversed_buffered_unicodes);
    goto next_loop;
  end_loop:
    g2int_emit_buffered_unicodes_as_utf_7_base64_to_transcoder(reversed_buffered_unicodes,
	    transcoder);
    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
	    g2int_gensym_cons_1(FIX((SI_Long)45L),Nil));
    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    if (character_qm) {
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		g2int_gensym_cons_1(character_qm,Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    }
    temp = FIX((SI_Long)43L);
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

Object G2int_ucs_4_to_utf_8_1st_octet_table = UNBOUND;

/* TWRITE-UTF-8-OCTETS */
Object g2int_twrite_utf_8_octets(unicode,n_octets,binary,use_bits,bits_free)
    Object unicode, n_octets, binary, use_bits, bits_free;
{
    Object octet, simple_or_wide_character, thing, temp, schar_arg_2;
    Object schar_new_value;
    SI_Long binary_2, use_bits_2, bits_free_2, octet_index;

    x_note_fn_call(26,258);
    binary_2 = (SI_Long)128L;
    use_bits_2 = (SI_Long)63L;
    bits_free_2 = (SI_Long)6L;
    octet_index = IFIX(n_octets);
    octet = Nil;
  next_loop:
    if (octet_index < (SI_Long)1L)
	goto end_loop;
    octet = FIX(IFIX(binary) | IFIX(use_bits) & IFIX(unicode) >>  -  - 
	    (bits_free_2 * (octet_index - (SI_Long)1L)));
    simple_or_wide_character = octet;
    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	thing = simple_or_wide_character;
	g2int_twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
    }
    else {
	if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		G2int_total_length_of_current_gensym_string))
	    g2int_extend_current_gensym_string(0);
	temp = G2int_current_gensym_string;
	schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	G2int_fill_pointer_for_current_gensym_string = temp;
    }
    binary = FIX(binary_2);
    bits_free = FIX(bits_free_2);
    use_bits = FIX(use_bits_2);
    octet_index = octet_index - (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TWRITE-UNICODE-AS-UTF-8 */
Object g2int_twrite_unicode_as_utf_8(unicode)
    Object unicode;
{
    Object simple_or_wide_character, thing, temp, schar_arg_2, schar_new_value;

    x_note_fn_call(26,259);
    if (IFIX(unicode) <= (SI_Long)127L) {
	simple_or_wide_character = unicode;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = simple_or_wide_character;
	    return g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(G2int_fill_pointer_for_current_gensym_string);
	}
    }
    else if (IFIX(unicode) <= (SI_Long)2047L)
	return g2int_twrite_utf_8_octets(unicode,FIX((SI_Long)2L),
		FIX((SI_Long)192L),FIX((SI_Long)31L),FIX((SI_Long)5L));
    else if (IFIX(unicode) <= (SI_Long)65535L)
	return g2int_twrite_utf_8_octets(unicode,FIX((SI_Long)3L),
		FIX((SI_Long)224L),FIX((SI_Long)15L),FIX((SI_Long)4L));
    else
	return VALUES_1(Qnil);
}

/* TRANSFORM-UTF-8-TO-UCS-4 */
Object g2int_transform_utf_8_to_ucs_4 varargs_1(int, n)
{
    Object z;
    Object y, x, w, v, u_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,260);
    INIT_ARGS_nonrelocating();
    z = REQUIRED_ARG_nonrelocating();
    y = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    x = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    w = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    v = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    u_1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (IFIX(z) < (SI_Long)192L)
	return VALUES_1(z);
    else if (IFIX(z) < (SI_Long)224L)
	return VALUES_1(FIX((IFIX(z) - (SI_Long)192L) * (SI_Long)64L + 
		(IFIX(y) - (SI_Long)128L)));
    else if (IFIX(z) < (SI_Long)240L)
	return VALUES_1(FIX((IFIX(z) - (SI_Long)224L) * (SI_Long)4096L + 
		(IFIX(y) - (SI_Long)128L) * (SI_Long)64L + (IFIX(x) - 
		(SI_Long)128L)));
    else if (IFIX(z) < (SI_Long)248L)
	return VALUES_1(FIX((IFIX(z) - (SI_Long)240L) * (SI_Long)262144L + 
		(IFIX(y) - (SI_Long)128L) * (SI_Long)4096L + (IFIX(x) - 
		(SI_Long)128L) * (SI_Long)64L + (IFIX(w) - (SI_Long)128L)));
    else if (IFIX(z) < (SI_Long)252L)
	return VALUES_1(FIX((IFIX(z) - (SI_Long)248L) * (SI_Long)16777216L 
		+ (IFIX(y) - (SI_Long)128L) * (SI_Long)262144L + (IFIX(x) 
		- (SI_Long)128L) * (SI_Long)4096L + (IFIX(w) - 
		(SI_Long)128L) * (SI_Long)64L + (IFIX(v) - (SI_Long)128L)));
    else
	return VALUES_1(FIX((IFIX(z) - (SI_Long)252L) * (SI_Long)16777216L 
		* (SI_Long)64L + (IFIX(y) - (SI_Long)128L) * 
		(SI_Long)16777216L + (IFIX(x) - (SI_Long)128L) * 
		(SI_Long)262144L + (IFIX(w) - (SI_Long)128L) * 
		(SI_Long)4096L + (IFIX(v) - (SI_Long)128L) * (SI_Long)64L 
		+ (IFIX(u_1) - (SI_Long)128L)));
}

/* TWRITE-UTF-8-FROM-TEXT-STRING */
Object g2int_twrite_utf_8_from_text_string(text_string)
    Object text_string;
{
    Object wide_character, temp, unicode, simple_or_wide_character, thing;
    Object temp_1, schar_arg_2, schar_new_value;
    SI_Long length_1, i, wide_string_index;

    x_note_fn_call(26,261);
    length_1 = IFIX(g2int_text_string_length(text_string));
    i = (SI_Long)0L;
    wide_character = Nil;
    wide_string_index = (SI_Long)0L;
  next_loop:
    if ( !(i < length_1))
	goto end_loop;
    temp = FIX(UBYTE_16_ISAREF_1(text_string,i));
    i = i + (SI_Long)1L;
    wide_character = temp;
    unicode = wide_character;
    if (IFIX(unicode) <= (SI_Long)127L) {
	simple_or_wide_character = unicode;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = simple_or_wide_character;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_1 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    else if (IFIX(unicode) <= (SI_Long)2047L)
	g2int_twrite_utf_8_octets(unicode,FIX((SI_Long)2L),
		FIX((SI_Long)192L),FIX((SI_Long)31L),FIX((SI_Long)5L));
    else if (IFIX(unicode) <= (SI_Long)65535L)
	g2int_twrite_utf_8_octets(unicode,FIX((SI_Long)3L),
		FIX((SI_Long)224L),FIX((SI_Long)15L),FIX((SI_Long)4L));
    wide_string_index = wide_string_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* UNICODE-TO-UTF-8-WIDE-STRING */
Object g2int_unicode_to_utf_8_wide_string(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(26,262);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      g2int_twrite_utf_8_from_text_string(text_string);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* UNICODE-TO-UTF-8-GENSYM-STRING */
Object g2int_unicode_to_utf_8_gensym_string(text_string)
    Object text_string;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(26,263);
    current_gensym_string = 
	    g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qg2int_gensym_string;
	  PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		  0);
	    g2int_twrite_utf_8_from_text_string(text_string);
	    result = g2int_copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GET-UTF-8-AS-UNICODE-FROM-TEXT-SEQUENCE */
Object g2int_get_utf_8_as_unicode_from_text_sequence(text_sequence)
    Object text_sequence;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long z, y, x, w, v, u_1, octet_count;
    char temp_1;

    x_note_fn_call(26,264);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)11L);
    gensymed_symbol_1 = text_sequence;
    z = IFIX(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    y = (SI_Long)0L;
    x = (SI_Long)0L;
    w = (SI_Long)0L;
    v = (SI_Long)0L;
    u_1 = (SI_Long)0L;
    if (z < (SI_Long)192L)
	temp = FIX((SI_Long)1L);
    else if (z < (SI_Long)224L)
	temp = FIX((SI_Long)2L);
    else if (z < (SI_Long)240L)
	temp = FIX((SI_Long)3L);
    else if (z < (SI_Long)248L)
	temp = FIX((SI_Long)4L);
    else if (z < (SI_Long)252L)
	temp = FIX((SI_Long)5L);
    else
	temp = FIX((SI_Long)6L);
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    octet_count = IFIX(temp);
    if (octet_count > (SI_Long)1L) {
	if (FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
		ISVREF(text_sequence,(SI_Long)3L))) {
	    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)11L);
	    gensymed_symbol_1 = text_sequence;
	    y = IFIX(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
	}
	else {
	    temp = Nil;
	    goto end_exhausted;
	}
	temp_1 = TRUEP(FIX(y));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? octet_count > (SI_Long)2L : TRUEP(Nil)) {
	if (FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
		ISVREF(text_sequence,(SI_Long)3L))) {
	    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)11L);
	    gensymed_symbol_1 = text_sequence;
	    x = IFIX(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
	}
	else {
	    temp = Nil;
	    goto end_exhausted;
	}
	temp_1 = TRUEP(FIX(x));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? octet_count > (SI_Long)3L : TRUEP(Nil)) {
	if (FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
		ISVREF(text_sequence,(SI_Long)3L))) {
	    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)11L);
	    gensymed_symbol_1 = text_sequence;
	    w = IFIX(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
	}
	else {
	    temp = Nil;
	    goto end_exhausted;
	}
	temp_1 = TRUEP(FIX(w));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? octet_count > (SI_Long)4L : TRUEP(Nil)) {
	if (FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
		ISVREF(text_sequence,(SI_Long)3L))) {
	    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)11L);
	    gensymed_symbol_1 = text_sequence;
	    v = IFIX(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
	}
	else {
	    temp = Nil;
	    goto end_exhausted;
	}
	temp_1 = TRUEP(FIX(v));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? octet_count > (SI_Long)5L : TRUEP(Nil)) {
	if (FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
		ISVREF(text_sequence,(SI_Long)3L))) {
	    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)11L);
	    gensymed_symbol_1 = text_sequence;
	    u_1 = IFIX(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
	}
	else {
	    temp = Nil;
	    goto end_exhausted;
	}
    }
    temp = g2int_transform_utf_8_to_ucs_4(6,FIX(z),FIX(y),FIX(x),FIX(w),
	    FIX(v),FIX(u_1));
  end_exhausted:
    return VALUES_1(temp);
}

Object G2int_the_type_description_of_utf_8_transcoder = UNBOUND;

Object G2int_chain_of_available_utf_8_transcoders = UNBOUND;

Object G2int_utf_8_transcoder_count = UNBOUND;

/* RECLAIM-UTF-8-TRANSCODER-1 */
Object g2int_reclaim_utf_8_transcoder_1(utf_8_transcoder)
    Object utf_8_transcoder;
{
    Object svref_new_value;

    x_note_fn_call(26,265);
    inline_note_reclaim_cons(utf_8_transcoder,Nil);
    svref_new_value = G2int_chain_of_available_utf_8_transcoders;
    SVREF(utf_8_transcoder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_utf_8_transcoders = utf_8_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UTF-8-TRANSCODER */
Object g2int_reclaim_structure_for_utf_8_transcoder(utf_8_transcoder)
    Object utf_8_transcoder;
{
    x_note_fn_call(26,266);
    return g2int_reclaim_utf_8_transcoder_1(utf_8_transcoder);
}

static Object Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct;  /* g2-defstruct-structure-name::utf-8-transcoder-g2-struct */

/* MAKE-PERMANENT-UTF-8-TRANSCODER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_utf_8_transcoder_structure_internal()
{
    Object def_structure_utf_8_transcoder_variable, temp;
    Object defstruct_g2_utf_8_transcoder_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(26,267);
    def_structure_utf_8_transcoder_variable = Nil;
    temp = FIXNUM_ADD1(G2int_utf_8_transcoder_count);
    G2int_utf_8_transcoder_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_utf_8_transcoder_variable = Nil;
	gensymed_symbol_1 = (SI_Long)6L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_utf_8_transcoder_variable = the_array;
	SVREF(defstruct_g2_utf_8_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct;
	SVREF(defstruct_g2_utf_8_transcoder_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_utf_8_transcoder_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_utf_8_transcoder_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_utf_8_transcoder_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_utf_8_transcoder_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_utf_8_transcoder_variable = 
		defstruct_g2_utf_8_transcoder_variable;
	SVREF(def_structure_utf_8_transcoder_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_utf_8_transcoder_variable,FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_utf_8_transcoders;
	SVREF(def_structure_utf_8_transcoder_variable,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_utf_8_transcoders = 
		def_structure_utf_8_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_utf_8_transcoder_variable);
}

/* MAKE-UTF-8-TRANSCODER-1 */
Object g2int_make_utf_8_transcoder_1()
{
    Object def_structure_utf_8_transcoder_variable;

    x_note_fn_call(26,268);
    def_structure_utf_8_transcoder_variable = 
	    G2int_chain_of_available_utf_8_transcoders;
    if (def_structure_utf_8_transcoder_variable) {
	G2int_chain_of_available_utf_8_transcoders = 
		ISVREF(def_structure_utf_8_transcoder_variable,(SI_Long)0L);
	SVREF(def_structure_utf_8_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct;
    }
    else
	def_structure_utf_8_transcoder_variable = 
		g2int_make_permanent_utf_8_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_utf_8_transcoder_variable,Nil);
    ISVREF(def_structure_utf_8_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_utf_8_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_utf_8_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_utf_8_transcoder_variable);
}

/* CREATE-TRANSCODER-FOR-UNICODE-UTF-8 */
Object g2int_create_transcoder_for_unicode_utf_8()
{
    x_note_fn_call(26,269);
    return g2int_make_utf_8_transcoder_1();
}

/* TRANSCODE-CHARACTER-FOR-UTF-8-TRANSCODER */
Object g2int_transcode_character_for_utf_8_transcoder(utf_8_transcoder)
    Object utf_8_transcoder;
{
    Object transcoder, temp, c;
    SI_Long character_1, z, y, x, octet_count;

    x_note_fn_call(26,270);
    transcoder = utf_8_transcoder;
    character_1 = IFIX(g2int_get_transcoder_character(transcoder));
    if (character_1 < (SI_Long)32L) {
	if (character_1 == (SI_Long)10L && IFIX(ISVREF(transcoder,
		(SI_Long)3L)) == (SI_Long)13L)
	    return VALUES_1(FIX((SI_Long)65535L));
	else if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L)
	    return VALUES_1(FIX((SI_Long)8232L));
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 < (SI_Long)128L)
	return VALUES_1(FIX(character_1));
    else if (character_1 < (SI_Long)256L) {
	z = character_1;
	y = (SI_Long)0L;
	x = (SI_Long)0L;
	if (z < (SI_Long)192L)
	    temp = FIX((SI_Long)1L);
	else if (z < (SI_Long)224L)
	    temp = FIX((SI_Long)2L);
	else if (z < (SI_Long)240L)
	    temp = FIX((SI_Long)3L);
	else if (z < (SI_Long)248L)
	    temp = FIX((SI_Long)4L);
	else if (z < (SI_Long)252L)
	    temp = FIX((SI_Long)5L);
	else
	    temp = FIX((SI_Long)6L);
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
	octet_count = IFIX(temp);
	if (octet_count > (SI_Long)3L)
	    return g2int_transcode_unhandled_character(FIX(character_1),
		    transcoder);
	else {
	    if (octet_count > (SI_Long)1L) {
		c = g2int_get_transcoder_character_if_any(transcoder);
		if ( !TRUEP(c))
		    y = (SI_Long)-1L;
		else {
		    y = IFIX(c);
		    if (octet_count > (SI_Long)2L) {
			c = g2int_get_transcoder_character_if_any(transcoder);
			if ( !TRUEP(c))
			    x = (SI_Long)-1L;
			else
			    x = IFIX(c);
		    }
		}
	    }
	    if (y < (SI_Long)0L || x < (SI_Long)0L)
		return g2int_transcode_unhandled_character(FIX(character_1),
			transcoder);
	    else
		return g2int_transform_utf_8_to_ucs_4(3,FIX(z),FIX(y),FIX(x));
	}
    }
    else
	return g2int_transcode_unhandled_character(FIX(character_1),
		transcoder);
}

/* EXPORT-CHARACTER-FOR-UTF-8-TRANSCODER */
Object g2int_export_character_for_utf_8_transcoder(utf_8_transcoder)
    Object utf_8_transcoder;
{
    Object transcoder, character_1, temp, svref_new_value;
    SI_Long character_2;

    x_note_fn_call(26,271);
    transcoder = utf_8_transcoder;
    character_1 = g2int_get_transcoder_character(transcoder);
    if (IFIX(character_1) == (SI_Long)8232L || IFIX(character_1) == 
	    (SI_Long)8233L) {
	temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	if (EQ(temp,Qg2int_per_platform)) {
	    if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
		    EQ(G2int_g2_operating_system,Qg2int_vms) || 
		    EQ(G2int_g2_operating_system,Qg2int_win32)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = (SI_Long)13L;
	    }
	    else if (EQ(G2int_g2_operating_system,Qg2int_unix))
		character_2 = (SI_Long)10L;
	    else
		character_2 = (SI_Long)10L;
	}
	else if (EQ(temp,Qg2int_cr))
	    character_2 = (SI_Long)13L;
	else if (EQ(temp,Qg2int_lf))
	    character_2 = (SI_Long)10L;
	else if (EQ(temp,Qg2int_crlf)) {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    g2int_gensym_cons_1(FIX((SI_Long)10L),Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    character_2 = (SI_Long)13L;
	}
	else if (EQ(temp,Qg2int_unicode_line_separator))
	    character_2 = (SI_Long)8232L;
	else if (EQ(temp,Qg2int_unicode_paragraph_separator))
	    character_2 = (SI_Long)8233L;
	else
	    character_2 = IFIX(character_1);
    }
    else
	character_2 = IFIX(character_1);
    if (character_2 <= (SI_Long)127L)
	return VALUES_1(FIX(character_2));
    else if (character_2 <= (SI_Long)2047L)
	return g2int_encode_utf_8_octets_for_transcoder(transcoder,
		FIX(character_2),FIX((SI_Long)2L),FIX((SI_Long)192L),
		FIX((SI_Long)31L),FIX((SI_Long)5L));
    else if (character_2 <= (SI_Long)65535L)
	return g2int_encode_utf_8_octets_for_transcoder(transcoder,
		FIX(character_2),FIX((SI_Long)3L),FIX((SI_Long)224L),
		FIX((SI_Long)15L),FIX((SI_Long)4L));
    else
	return VALUES_1(Qnil);
}

/* ENCODE-UTF-8-OCTETS-FOR-TRANSCODER */
Object g2int_encode_utf_8_octets_for_transcoder(transcoder,character_1,
	    n_octets,binary,use_bits,bits_free)
    Object transcoder, character_1, n_octets, binary, use_bits, bits_free;
{
    Object octet, octet_character, svref_new_value;
    SI_Long binary_2, use_bits_2, bits_free_2, octet_index;

    x_note_fn_call(26,272);
    binary_2 = (SI_Long)128L;
    use_bits_2 = (SI_Long)63L;
    bits_free_2 = (SI_Long)6L;
    octet_index = IFIX(n_octets);
    octet = Nil;
    octet_character = Nil;
  next_loop:
    if (octet_index < (SI_Long)1L)
	goto end_loop;
    octet = FIX(IFIX(binary) | IFIX(use_bits) & IFIX(character_1) >>  -  - 
	    (bits_free_2 * (octet_index - (SI_Long)1L)));
    octet_character = octet;
    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
	    g2int_gensym_cons_1(octet_character,Nil));
    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    binary = FIX(binary_2);
    bits_free = FIX(bits_free_2);
    use_bits = FIX(use_bits_2);
    octet_index = octet_index - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(FIX((SI_Long)65535L));
}

/* GENSYM-STRING-TO-WIDE-STRING */
Object g2int_gensym_string_to_wide_string(gensym_string)
    Object gensym_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, character_or_character_code, escape_character_qm;
    Object gensymed_symbol, current_extended_utf_g_low_half_character_qm;
    Object simple_or_wide_character, thing, temp_4, schar_arg_2;
    Object schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, end, i;
    SI_Long gensym_character_code, ascii_code, temp_2, row, unicode_full_row;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char simple_qm, gensym_string_is_simple_qm;
    char temp_1, character_1;
    char gensymed_symbol_1, temp_3;
    Declare_special(6);

    x_note_fn_call(26,273);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,5);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,4);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		3);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  2);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    1);
	      simple_qm =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
	      temp = Nil;
	      if (temp);
	      else
		  temp = simple_qm ? 
			  SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string) : 
			  length(gensym_string);
	      end = IFIX(temp);
	      i = (SI_Long)0L;
	      character_or_character_code = Nil;
	      escape_character_qm = Nil;
	      gensym_character_code = (SI_Long)0L;
	    next_loop:
	      if ( !(i < end))
		  goto end_loop;
	      gensym_string_is_simple_qm = simple_qm;
	      temp_1 = gensym_string_is_simple_qm ? ISCHAR(gensym_string,
		      i) : ICHAR(gensym_string,i);
	      i = i + (SI_Long)1L;
	      character_1 = temp_1;
	      temp = CHAR_CODE(CHAR_TO_CHARACTER(character_1));
	      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		      FIX((SI_Long)127L)))) {
		  escape_character_qm = Nil;
		  character_or_character_code = CHAR_TO_CHARACTER(character_1);
	      }
	      else
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 64:
		    case 126:
		      escape_character_qm = CHAR_TO_CHARACTER(character_1);
		      temp = gensym_string_is_simple_qm ? 
			      CHR(ISCHAR(gensym_string,i)) : 
			      CHR(ICHAR(gensym_string,i));
		      i = i + (SI_Long)1L;
		      character_or_character_code = temp;
		      break;
		    case 92:
		      escape_character_qm = CHAR_TO_CHARACTER(character_1);
		      gensymed_symbol = gensym_string;
		      gensymed_symbol_1 = gensym_string_is_simple_qm;
		      temp_1 = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,
			      i) : ICHAR(gensymed_symbol,i);
		      i = i + (SI_Long)1L;
		      ascii_code = IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1)));
		      if (ascii_code < (SI_Long)40L) {
			  temp_2 = ascii_code << (SI_Long)13L;
			  temp_1 = gensymed_symbol_1 ? 
				  ISCHAR(gensymed_symbol,i) : 
				  ICHAR(gensymed_symbol,i);
			  i = i + (SI_Long)1L;
			  temp_2 = temp_2 + (SI_Long)95L * 
				  IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1)));
			  temp_1 = gensymed_symbol_1 ? 
				  ISCHAR(gensymed_symbol,i) : 
				  ICHAR(gensymed_symbol,i);
			  i = i + (SI_Long)1L;
			  character_or_character_code = FIX(temp_2 + 
				  IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1))) 
				  + (SI_Long)-265976L);
		      }
		      else {
			  temp_2 = (SI_Long)95L * ascii_code;
			  temp_1 = gensymed_symbol_1 ? 
				  ISCHAR(gensymed_symbol,i) : 
				  ICHAR(gensymed_symbol,i);
			  i = i + (SI_Long)1L;
			  character_or_character_code = FIX(temp_2 + 
				  IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1))) 
				  + (SI_Long)4360L);
		      }
		      break;
		    default:
		      escape_character_qm = Nil;
		      character_or_character_code = 
			      CHAR_TO_CHARACTER(character_1);
		      break;
		  }
	      if ( !TRUEP(escape_character_qm))
		  gensym_character_code = 
			  IFIX(CHAR_CODE(character_or_character_code));
	      else {
		  if (CHAR_EQ(escape_character_qm,CHR('~'))) {
		      temp = 
			      ISVREF(G2int_reverse_iso_latin1_special_character_code_map,
			      IFIX(CHAR_CODE(character_or_character_code)));
		      if (temp);
		      else {
			  temp = CHAR_CODE(character_or_character_code);
			  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				  FIXNUM_LE(temp,FIX((SI_Long)127L))))
			      temp = Nil;
			  else
			      switch (INTEGER_TO_CHAR(temp)) {
				case 87:
				  temp = 
					  G2int_gensym_code_for_capital_ligature_oe;
				  break;
				case 119:
				  temp = 
					  G2int_gensym_code_for_small_ligature_oe;
				  break;
				case 42:
				  temp = G2int_gensym_code_for_bullet;
				  break;
				case 38:
				  temp = 
					  G2int_gensym_code_for_small_letter_f_with_hook;
				  break;
				case 58:
				  temp = G2int_gensym_code_for_trade_mark_sign;
				  break;
				default:
				  temp = Nil;
				  break;
			      }
		      }
		      gensym_character_code = IFIX(temp);
		  }
		  else
		      gensym_character_code = IFIX(Nil);
		  if (gensym_character_code);
		  else if ( !TRUEP(escape_character_qm) &&  
			  !TRUEP(G2int_gensym_esc_for_linebreakqm) ? 
			  CHAR_EQ(character_or_character_code,
			  G2int_gensym_char_or_code_for_linebreak) : 
			  EQL(character_or_character_code,
			  G2int_gensym_char_or_code_for_linebreak) && 
			  EQL(escape_character_qm,
			  G2int_gensym_esc_for_linebreakqm))
		      gensym_character_code = 
			      IFIX(G2int_gensym_code_for_linebreak);
		  else if ( !TRUEP(escape_character_qm) &&  
			  !TRUEP(G2int_gensym_esc_for_paragraph_breakqm) ? 
			  CHAR_EQ(character_or_character_code,
			  G2int_gensym_char_or_code_for_paragraph_break) : 
			  EQL(character_or_character_code,
			  G2int_gensym_char_or_code_for_paragraph_break) 
			  && EQL(escape_character_qm,
			  G2int_gensym_esc_for_paragraph_breakqm))
		      gensym_character_code = 
			      IFIX(G2int_gensym_code_for_paragraph_break);
		  else {
		      gensym_character_code =  !EQ(escape_character_qm,
			      CHR('\\')) ? (SI_Long)65535L : IFIX(Nil);
		      if (gensym_character_code);
		      else
			  gensym_character_code = 
				  IFIX(character_or_character_code);
		  }
	      }
	      if (gensym_character_code >>  -  - (SI_Long)8L == 
			  (SI_Long)247L) {
		  current_extended_utf_g_low_half_character_qm = 
			  FIX(gensym_character_code);
		  PUSH_SPECIAL(G2int_current_extended_utf_g_low_half_characterqm,current_extended_utf_g_low_half_character_qm,
			  0);
		    if (i < end) {
			gensym_string_is_simple_qm = simple_qm;
			temp_1 = gensym_string_is_simple_qm ? 
				ISCHAR(gensym_string,i) : 
				ICHAR(gensym_string,i);
			i = i + (SI_Long)1L;
			character_1 = temp_1;
			temp = CHAR_CODE(CHAR_TO_CHARACTER(character_1));
			if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L)))) {
			    escape_character_qm = Nil;
			    character_or_character_code = 
				    CHAR_TO_CHARACTER(character_1);
			}
			else
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 64:
			      case 126:
				escape_character_qm = 
					CHAR_TO_CHARACTER(character_1);
				temp = gensym_string_is_simple_qm ? 
					CHR(ISCHAR(gensym_string,i)) : 
					CHR(ICHAR(gensym_string,i));
				i = i + (SI_Long)1L;
				character_or_character_code = temp;
				break;
			      case 92:
				escape_character_qm = 
					CHAR_TO_CHARACTER(character_1);
				gensymed_symbol = gensym_string;
				gensymed_symbol_1 = gensym_string_is_simple_qm;
				temp_1 = gensymed_symbol_1 ? 
					ISCHAR(gensymed_symbol,i) : 
					ICHAR(gensymed_symbol,i);
				i = i + (SI_Long)1L;
				ascii_code = 
					IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1)));
				if (ascii_code < (SI_Long)40L) {
				    temp_2 = ascii_code << (SI_Long)13L;
				    temp_1 = gensymed_symbol_1 ? 
					    ISCHAR(gensymed_symbol,i) : 
					    ICHAR(gensymed_symbol,i);
				    i = i + (SI_Long)1L;
				    temp_2 = temp_2 + (SI_Long)95L * 
					    IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1)));
				    temp_1 = gensymed_symbol_1 ? 
					    ISCHAR(gensymed_symbol,i) : 
					    ICHAR(gensymed_symbol,i);
				    i = i + (SI_Long)1L;
				    character_or_character_code = 
					    FIX(temp_2 + 
					    IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1))) 
					    + (SI_Long)-265976L);
				}
				else {
				    temp_2 = (SI_Long)95L * ascii_code;
				    temp_1 = gensymed_symbol_1 ? 
					    ISCHAR(gensymed_symbol,i) : 
					    ICHAR(gensymed_symbol,i);
				    i = i + (SI_Long)1L;
				    character_or_character_code = 
					    FIX(temp_2 + 
					    IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp_1))) 
					    + (SI_Long)4360L);
				}
				break;
			      default:
				escape_character_qm = Nil;
				character_or_character_code = 
					CHAR_TO_CHARACTER(character_1);
				break;
			    }
			if ( !TRUEP(escape_character_qm))
			    gensym_character_code = 
				    IFIX(CHAR_CODE(character_or_character_code));
			else {
			    if (CHAR_EQ(escape_character_qm,CHR('~'))) {
				temp = 
					ISVREF(G2int_reverse_iso_latin1_special_character_code_map,
					IFIX(CHAR_CODE(character_or_character_code)));
				if (temp);
				else {
				    temp = 
					    CHAR_CODE(character_or_character_code);
				    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),
					    temp) && FIXNUM_LE(temp,
					    FIX((SI_Long)127L))))
					temp = Nil;
				    else
					switch (INTEGER_TO_CHAR(temp)) {
					  case 87:
					    temp = 
						    G2int_gensym_code_for_capital_ligature_oe;
					    break;
					  case 119:
					    temp = 
						    G2int_gensym_code_for_small_ligature_oe;
					    break;
					  case 42:
					    temp = 
						    G2int_gensym_code_for_bullet;
					    break;
					  case 38:
					    temp = 
						    G2int_gensym_code_for_small_letter_f_with_hook;
					    break;
					  case 58:
					    temp = 
						    G2int_gensym_code_for_trade_mark_sign;
					    break;
					  default:
					    temp = Nil;
					    break;
					}
				}
				gensym_character_code = IFIX(temp);
			    }
			    else
				gensym_character_code = IFIX(Nil);
			    if (gensym_character_code);
			    else if ( !TRUEP(escape_character_qm) &&  
				    !TRUEP(G2int_gensym_esc_for_linebreakqm) 
				    ? CHAR_EQ(character_or_character_code,
				    G2int_gensym_char_or_code_for_linebreak) 
				    : EQL(character_or_character_code,
				    G2int_gensym_char_or_code_for_linebreak) 
				    && EQL(escape_character_qm,
				    G2int_gensym_esc_for_linebreakqm))
				gensym_character_code = 
					IFIX(G2int_gensym_code_for_linebreak);
			    else if ( !TRUEP(escape_character_qm) &&  
				    !TRUEP(G2int_gensym_esc_for_paragraph_breakqm) 
				    ? CHAR_EQ(character_or_character_code,
				    G2int_gensym_char_or_code_for_paragraph_break) 
				    : EQL(character_or_character_code,
				    G2int_gensym_char_or_code_for_paragraph_break) 
				    && EQL(escape_character_qm,
				    G2int_gensym_esc_for_paragraph_breakqm))
				gensym_character_code = 
					IFIX(G2int_gensym_code_for_paragraph_break);
			    else {
				gensym_character_code =  
					!EQ(escape_character_qm,CHR('\\')) 
					? (SI_Long)65535L : IFIX(Nil);
				if (gensym_character_code);
				else
				    gensym_character_code = 
					    IFIX(character_or_character_code);
			    }
			}
			if (gensym_character_code >>  -  - (SI_Long)8L == 
				(SI_Long)248L) {
			    temp_3 = gensym_character_code < (SI_Long)256L 
				    ? 
				    TRUEP(ISVREF(G2int_iso_latin1_special_character_code_map,
				    gensym_character_code)) : TRUEP(Nil);
			    if (temp_3);
			    else if (gensym_character_code == 
				    IFIX(G2int_gensym_code_for_capital_ligature_oe))
				temp_3 = 'W';
			    else if (gensym_character_code == 
				    IFIX(G2int_gensym_code_for_small_ligature_oe))
				temp_3 = 'w';
			    else if (gensym_character_code == 
				    IFIX(G2int_gensym_code_for_bullet))
				temp_3 = '*';
			    else if (gensym_character_code == 
				    IFIX(G2int_gensym_code_for_small_letter_f_with_hook))
				temp_3 = '&';
			    else if (gensym_character_code == 
				    IFIX(G2int_gensym_code_for_trade_mark_sign))
				temp_3 = ':';
			    else
				temp_3 = TRUEP(Qnil);
			    if (temp_3) {
				row = gensym_character_code >>  -  - 
					(SI_Long)8L;
				unicode_full_row = 
					UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
					row);
				if ( !(unicode_full_row == 
					IFIX(G2int_invalid_unicode_full_row))) 
					    {
				    gensymed_symbol_2 = unicode_full_row 
					    << (SI_Long)8L;
				    gensymed_symbol_3 = (SI_Long)255L & 
					    gensym_character_code;
				    simple_or_wide_character = 
					    FIX(gensymed_symbol_2 + 
					    gensymed_symbol_3);
				}
				else
				    simple_or_wide_character = Nil;
			    }
			    else if ((SI_Long)8192L <= 
				    gensym_character_code && 
				    gensym_character_code <= (SI_Long)8447L) {
				row = gensym_character_code >>  -  - 
					(SI_Long)8L;
				unicode_full_row = 
					UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
					row);
				if ( !(unicode_full_row == 
					IFIX(G2int_invalid_unicode_full_row))) 
					    {
				    gensymed_symbol_2 = unicode_full_row 
					    << (SI_Long)8L;
				    gensymed_symbol_3 = (SI_Long)255L & 
					    gensym_character_code;
				    simple_or_wide_character = 
					    FIX(gensymed_symbol_2 + 
					    gensymed_symbol_3);
				}
				else
				    simple_or_wide_character = Nil;
			    }
			    else {
				simple_or_wide_character = 
					g2int_map_gensym_han_character_code_to_unicode(FIX(gensym_character_code));
				if (simple_or_wide_character);
				else {
				    row = gensym_character_code >>  -  - 
					    (SI_Long)8L;
				    unicode_full_row = 
					    UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
					    row);
				    if ( !(unicode_full_row == 
					    IFIX(G2int_invalid_unicode_full_row))) 
						{
					gensymed_symbol_2 = 
						unicode_full_row << 
						(SI_Long)8L;
					gensymed_symbol_3 = (SI_Long)255L 
						& gensym_character_code;
					simple_or_wide_character = 
						FIX(gensymed_symbol_2 + 
						gensymed_symbol_3);
				    }
				    else
					simple_or_wide_character = Nil;
				    if (simple_or_wide_character);
				    else if (G2int_current_extended_utf_g_low_half_characterqm)
					simple_or_wide_character = 
						g2int_map_extended_utf_g_characters_to_unicode(G2int_current_extended_utf_g_low_half_characterqm,
						FIX(gensym_character_code));
				    else
					simple_or_wide_character = 
						FIX((SI_Long)65535L);
				}
			    }
			    if (EQ(G2int_current_twriting_output_type,
				    Qg2int_wide_string)) {
				thing = simple_or_wide_character;
				g2int_twrite_wide_character(CHARACTERP(thing) 
					? CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
					G2int_total_length_of_current_gensym_string))
				    g2int_extend_current_gensym_string(0);
				temp_4 = G2int_current_gensym_string;
				schar_arg_2 = 
					G2int_fill_pointer_for_current_gensym_string;
				thing = simple_or_wide_character;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_4,schar_arg_2,schar_new_value);
				temp_4 = 
					FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
				G2int_fill_pointer_for_current_gensym_string 
					= temp_4;
			    }
			}
		    }
		  POP_SPECIAL();
	      }
	      else {
		  temp_3 = gensym_character_code < (SI_Long)256L ? 
			  TRUEP(ISVREF(G2int_iso_latin1_special_character_code_map,
			  gensym_character_code)) : TRUEP(Nil);
		  if (temp_3);
		  else if (gensym_character_code == 
			  IFIX(G2int_gensym_code_for_capital_ligature_oe))
		      temp_3 = 'W';
		  else if (gensym_character_code == 
			  IFIX(G2int_gensym_code_for_small_ligature_oe))
		      temp_3 = 'w';
		  else if (gensym_character_code == 
			  IFIX(G2int_gensym_code_for_bullet))
		      temp_3 = '*';
		  else if (gensym_character_code == 
			  IFIX(G2int_gensym_code_for_small_letter_f_with_hook))
		      temp_3 = '&';
		  else if (gensym_character_code == 
			  IFIX(G2int_gensym_code_for_trade_mark_sign))
		      temp_3 = ':';
		  else
		      temp_3 = TRUEP(Qnil);
		  if (temp_3) {
		      row = gensym_character_code >>  -  - (SI_Long)8L;
		      unicode_full_row = 
			      UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
			      row);
		      if ( !(unicode_full_row == 
			      IFIX(G2int_invalid_unicode_full_row))) {
			  gensymed_symbol_2 = unicode_full_row << (SI_Long)8L;
			  gensymed_symbol_3 = (SI_Long)255L & 
				  gensym_character_code;
			  simple_or_wide_character = FIX(gensymed_symbol_2 
				  + gensymed_symbol_3);
		      }
		      else
			  simple_or_wide_character = Nil;
		  }
		  else if ((SI_Long)8192L <= gensym_character_code && 
			  gensym_character_code <= (SI_Long)8447L) {
		      row = gensym_character_code >>  -  - (SI_Long)8L;
		      unicode_full_row = 
			      UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
			      row);
		      if ( !(unicode_full_row == 
			      IFIX(G2int_invalid_unicode_full_row))) {
			  gensymed_symbol_2 = unicode_full_row << (SI_Long)8L;
			  gensymed_symbol_3 = (SI_Long)255L & 
				  gensym_character_code;
			  simple_or_wide_character = FIX(gensymed_symbol_2 
				  + gensymed_symbol_3);
		      }
		      else
			  simple_or_wide_character = Nil;
		  }
		  else {
		      simple_or_wide_character = 
			      g2int_map_gensym_han_character_code_to_unicode(FIX(gensym_character_code));
		      if (simple_or_wide_character);
		      else {
			  row = gensym_character_code >>  -  - (SI_Long)8L;
			  unicode_full_row = 
				  UBYTE_8_ISAREF_1(G2int_gensym_to_unicode_full_row_map,
				  row);
			  if ( !(unicode_full_row == 
				  IFIX(G2int_invalid_unicode_full_row))) {
			      gensymed_symbol_2 = unicode_full_row << 
				      (SI_Long)8L;
			      gensymed_symbol_3 = (SI_Long)255L & 
				      gensym_character_code;
			      simple_or_wide_character = 
				      FIX(gensymed_symbol_2 + 
				      gensymed_symbol_3);
			  }
			  else
			      simple_or_wide_character = Nil;
			  if (simple_or_wide_character);
			  else if (G2int_current_extended_utf_g_low_half_characterqm)
			      simple_or_wide_character = 
				      g2int_map_extended_utf_g_characters_to_unicode(G2int_current_extended_utf_g_low_half_characterqm,
				      FIX(gensym_character_code));
			  else
			      simple_or_wide_character = FIX((SI_Long)65535L);
		      }
		  }
		  if (EQ(G2int_current_twriting_output_type,
			  Qg2int_wide_string)) {
		      thing = simple_or_wide_character;
		      g2int_twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			      G2int_total_length_of_current_gensym_string))
			  g2int_extend_current_gensym_string(0);
		      temp_4 = G2int_current_gensym_string;
		      schar_arg_2 = 
			      G2int_fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_4,schar_arg_2,schar_new_value);
		      temp_4 = 
			      FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		      G2int_fill_pointer_for_current_gensym_string = temp_4;
		  }
	      }
	      goto next_loop;
	    end_loop:;
	      temp = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* TWRITE-UTF-G-FROM-TEXT-STRING */
Object g2int_twrite_utf_g_from_text_string(text_string)
    Object text_string;
{
    Object wide_character, extended_code_qm, temp, unicode, code;
    Object extended_code, unicode_1, code_1, gensym_character_code_qm, char_1;
    Object character_or_character_code, escape_character_qm, thing, temp_2;
    Object schar_arg_2, schar_new_value, kanji_code, octet_1_qm, quotient;
    Object remainder_1, simple_or_wide_character;
    Object simple_gensym_character_code_1;
    SI_Long length_1, i, gensym_character_code, wide_string_index, row;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1;
    SI_Long simple_gensym_character_code, octet_2, octet_3, thing_1;
    SI_Long simple_or_wide_character_1;
    char temp_1;
    Object result;

    x_note_fn_call(26,274);
    length_1 = IFIX(g2int_text_string_length(text_string));
    i = (SI_Long)0L;
    wide_character = Nil;
    gensym_character_code = (SI_Long)0L;
    extended_code_qm = Nil;
    wide_string_index = (SI_Long)0L;
  next_loop:
    if ( !(i < length_1))
	goto end_loop;
    temp = FIX(UBYTE_16_ISAREF_1(text_string,i));
    i = i + (SI_Long)1L;
    wide_character = temp;
    unicode = wide_character;
    code = Nil;
    extended_code = Nil;
    unicode_1 = unicode;
    extended_code = Nil;
    code_1 = unicode_1;
    if (IFIX(code_1) < (SI_Long)127L &&  !((SI_Long)64L == IFIX(code_1) || 
	    (SI_Long)126L == IFIX(code_1) || (SI_Long)92L == IFIX(code_1))) {
	code = unicode_1;
	temp = code;
    }
    else {
	row = IFIX(unicode_1) >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
	    gensym_character_code_qm = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	}
	else
	    gensym_character_code_qm = Nil;
	if (gensym_character_code_qm) {
	    temp_1 = IFIX(gensym_character_code_qm) < (SI_Long)256L ? 
		    TRUEP(ISVREF(G2int_iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code_qm))) : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_capital_ligature_oe))
		temp_1 = 'W';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_small_ligature_oe))
		temp_1 = 'w';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_bullet))
		temp_1 = '*';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_small_letter_f_with_hook))
		temp_1 = '&';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_trade_mark_sign))
		temp_1 = ':';
	    else
		temp_1 = TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = (SI_Long)8192L <= IFIX(gensym_character_code_qm) ?
			 IFIX(gensym_character_code_qm) <= (SI_Long)8447L :
			 TRUEP(Qnil);
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
	    code = g2int_map_unicode_to_gensym_han_character_code(unicode_1);
	    temp = code;
	    if (temp);
	    else {
		row = IFIX(unicode_1) >>  -  - (SI_Long)8L;
		gensym_full_row = 
			UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,
			row);
		if ( !(gensym_full_row == 
			    IFIX(G2int_invalid_gensym_full_row))) {
		    gensymed_symbol = gensym_full_row << (SI_Long)8L;
		    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
		    code = FIX(gensymed_symbol + gensymed_symbol_1);
		}
		else
		    code = Nil;
		temp = code;
		if (temp);
		else {
		    gensymed_symbol = (SI_Long)63488L;
		    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode_1);
		    extended_code = FIX(gensymed_symbol + gensymed_symbol_1);
		    code = FIX((SI_Long)63232L + (IFIX(unicode_1) >>  -  - 
			    (SI_Long)8L));
		    temp = code;
		}
	    }
	}
    }
    result = VALUES_2(temp,extended_code);
    MVS_2(result,temp,extended_code_qm);
    gensym_character_code = IFIX(temp);
    char_1 = Nil;
    if (gensym_character_code == IFIX(G2int_gensym_code_for_linebreak))
	result = VALUES_2(G2int_gensym_char_or_code_for_linebreak,
		G2int_gensym_esc_for_linebreakqm);
    else if (gensym_character_code == 
	    IFIX(G2int_gensym_code_for_paragraph_break))
	result = VALUES_2(G2int_gensym_char_or_code_for_paragraph_break,
		G2int_gensym_esc_for_paragraph_breakqm);
    else {
	if ((SI_Long)32L <= gensym_character_code && gensym_character_code 
		<= (SI_Long)126L) {
	    simple_gensym_character_code = gensym_character_code;
	    temp_1 =  !(simple_gensym_character_code == (SI_Long)64L || 
		    simple_gensym_character_code == (SI_Long)126L || 
		    simple_gensym_character_code == (SI_Long)92L);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = CODE_CHAR(FIX(gensym_character_code));
	    result = VALUES_2(temp,Nil);
	}
	else {
	    temp = gensym_character_code < (SI_Long)256L ? 
		    ISVREF(G2int_iso_latin1_special_character_code_map,
		    gensym_character_code) : Nil;
	    if (temp);
	    else if (gensym_character_code == 
		    IFIX(G2int_gensym_code_for_capital_ligature_oe))
		temp = CHR('W');
	    else if (gensym_character_code == 
		    IFIX(G2int_gensym_code_for_small_ligature_oe))
		temp = CHR('w');
	    else if (gensym_character_code == 
		    IFIX(G2int_gensym_code_for_bullet))
		temp = CHR('*');
	    else if (gensym_character_code == 
		    IFIX(G2int_gensym_code_for_small_letter_f_with_hook))
		temp = CHR('&');
	    else if (gensym_character_code == 
		    IFIX(G2int_gensym_code_for_trade_mark_sign))
		temp = CHR(':');
	    else
		temp = Qnil;
	    char_1 = temp;
	    if (char_1)
		result = VALUES_2(char_1,CHR('~'));
	    else
		result = VALUES_2(FIX(gensym_character_code),CHR('\\'));
	}
    }
    MVS_2(result,character_or_character_code,escape_character_qm);
    if ( !TRUEP(escape_character_qm)) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = character_or_character_code;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	kanji_code = character_or_character_code;
	octet_1_qm = Nil;
	octet_2 = (SI_Long)0L;
	octet_3 = (SI_Long)0L;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = (SI_Long)92L;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = (SI_Long)92L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
	code_1 = kanji_code;
	result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) & 
		(SI_Long)8191L),FIX((SI_Long)95L));
	MVS_2(result,quotient,remainder_1);
	octet_2 = IFIX(quotient) + (SI_Long)40L;
	octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == (SI_Long)1L) 
		? FIX((IFIX(code_1) >>  -  - (SI_Long)13L) + (SI_Long)32L) 
		: Nil;
	if (octet_1_qm) {
	    simple_or_wide_character = octet_1_qm;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = simple_or_wide_character;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	simple_or_wide_character_1 = octet_2;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = simple_or_wide_character_1;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
	simple_or_wide_character_1 = octet_3;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = simple_or_wide_character_1;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    else {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = escape_character_qm;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = escape_character_qm;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = character_or_character_code;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    if (extended_code_qm) {
	char_1 = Nil;
	if (FIXNUM_EQ(extended_code_qm,G2int_gensym_code_for_linebreak))
	    result = VALUES_2(G2int_gensym_char_or_code_for_linebreak,
		    G2int_gensym_esc_for_linebreakqm);
	else if (FIXNUM_EQ(extended_code_qm,
		G2int_gensym_code_for_paragraph_break))
	    result = VALUES_2(G2int_gensym_char_or_code_for_paragraph_break,
		    G2int_gensym_esc_for_paragraph_breakqm);
	else {
	    if ((SI_Long)32L <= IFIX(extended_code_qm) && 
		    IFIX(extended_code_qm) <= (SI_Long)126L) {
		simple_gensym_character_code_1 = extended_code_qm;
		temp_1 =  !(FIXNUM_EQ(simple_gensym_character_code_1,
			FIX((SI_Long)64L)) || 
			FIXNUM_EQ(simple_gensym_character_code_1,
			FIX((SI_Long)126L)) || 
			FIXNUM_EQ(simple_gensym_character_code_1,
			FIX((SI_Long)92L)));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = CODE_CHAR(extended_code_qm);
		result = VALUES_2(temp,Nil);
	    }
	    else {
		temp = IFIX(extended_code_qm) < (SI_Long)256L ? 
			ISVREF(G2int_iso_latin1_special_character_code_map,
			IFIX(extended_code_qm)) : Nil;
		if (temp);
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_capital_ligature_oe))
		    temp = CHR('W');
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_small_ligature_oe))
		    temp = CHR('w');
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_bullet))
		    temp = CHR('*');
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_small_letter_f_with_hook))
		    temp = CHR('&');
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_trade_mark_sign))
		    temp = CHR(':');
		else
		    temp = Qnil;
		char_1 = temp;
		if (char_1)
		    result = VALUES_2(char_1,CHR('~'));
		else
		    result = VALUES_2(extended_code_qm,CHR('\\'));
	    }
	}
	MVS_2(result,character_or_character_code,escape_character_qm);
	if ( !TRUEP(escape_character_qm)) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = character_or_character_code;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	    kanji_code = character_or_character_code;
	    octet_1_qm = Nil;
	    octet_2 = (SI_Long)0L;
	    octet_3 = (SI_Long)0L;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = (SI_Long)92L;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = (SI_Long)92L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	    code_1 = kanji_code;
	    result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) & 
		    (SI_Long)8191L),FIX((SI_Long)95L));
	    MVS_2(result,quotient,remainder_1);
	    octet_2 = IFIX(quotient) + (SI_Long)40L;
	    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	    octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
		    (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
		    (SI_Long)13L) + (SI_Long)32L) : Nil;
	    if (octet_1_qm) {
		simple_or_wide_character = octet_1_qm;
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing = simple_or_wide_character;
		    g2int_twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_2 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing = simple_or_wide_character;
		    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		    temp_2 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_2;
		}
	    }
	    simple_or_wide_character_1 = octet_2;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = simple_or_wide_character_1;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = simple_or_wide_character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	    simple_or_wide_character_1 = octet_3;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = simple_or_wide_character_1;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = simple_or_wide_character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	else {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = escape_character_qm;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = escape_character_qm;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = character_or_character_code;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
    }
    wide_string_index = wide_string_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* UNICODE-TO-UTF-G-WIDE-STRING */
Object g2int_unicode_to_utf_g_wide_string(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(26,275);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      g2int_twrite_utf_g_from_text_string(text_string);
	      temp = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* UNICODE-TO-UTF-G-GENSYM-STRING */
Object g2int_unicode_to_utf_g_gensym_string(text_string)
    Object text_string;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object temp;
    Declare_special(4);

    x_note_fn_call(26,276);
    current_gensym_string = 
	    g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qg2int_gensym_string;
	  PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		  0);
	    g2int_twrite_utf_g_from_text_string(text_string);
	    temp = g2int_copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

Object G2int_intern_string_buffer = UNBOUND;

/* TWRITE-INTERN-STRING-BUFFER-AS-GENSYM-CHARACTERS */
Object g2int_twrite_intern_string_buffer_as_gensym_characters(size)
    Object size;
{
    Object wide_character_code, code, extended_code, unicode, code_1, temp;
    Object gensym_character_code_qm, gensym_character_code, extended_code_qm;
    Object char_1, simple_gensym_character_code, character_or_character_code;
    Object escape_character_qm, thing, temp_2, schar_arg_2, schar_new_value;
    Object kanji_code, octet_1_qm, quotient, remainder_1;
    Object simple_or_wide_character;
    SI_Long i, ab_loop_bind_, row, gensym_full_row, gensymed_symbol;
    SI_Long gensymed_symbol_1, octet_2, octet_3, thing_1;
    SI_Long simple_or_wide_character_1;
    char temp_1;
    Object result;

    x_note_fn_call(26,277);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(size);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character_code = CHAR_CODE(CHR(ICHAR(G2int_intern_string_buffer,i)));
    code = Nil;
    extended_code = Nil;
    unicode = wide_character_code;
    extended_code = Nil;
    code_1 = unicode;
    if (IFIX(code_1) < (SI_Long)127L &&  !((SI_Long)64L == IFIX(code_1) || 
	    (SI_Long)126L == IFIX(code_1) || (SI_Long)92L == IFIX(code_1))) {
	code = unicode;
	temp = code;
    }
    else {
	row = IFIX(unicode) >>  -  - (SI_Long)8L;
	gensym_full_row = 
		UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,row);
	if ( !(gensym_full_row == IFIX(G2int_invalid_gensym_full_row))) {
	    gensymed_symbol = gensym_full_row << (SI_Long)8L;
	    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
	    gensym_character_code_qm = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	}
	else
	    gensym_character_code_qm = Nil;
	if (gensym_character_code_qm) {
	    temp_1 = IFIX(gensym_character_code_qm) < (SI_Long)256L ? 
		    TRUEP(ISVREF(G2int_iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code_qm))) : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_capital_ligature_oe))
		temp_1 = 'W';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_small_ligature_oe))
		temp_1 = 'w';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_bullet))
		temp_1 = '*';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_small_letter_f_with_hook))
		temp_1 = '&';
	    else if (FIXNUM_EQ(gensym_character_code_qm,
		    G2int_gensym_code_for_trade_mark_sign))
		temp_1 = ':';
	    else
		temp_1 = TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = (SI_Long)8192L <= IFIX(gensym_character_code_qm) ?
			 IFIX(gensym_character_code_qm) <= (SI_Long)8447L :
			 TRUEP(Qnil);
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
	    code = g2int_map_unicode_to_gensym_han_character_code(unicode);
	    temp = code;
	    if (temp);
	    else {
		row = IFIX(unicode) >>  -  - (SI_Long)8L;
		gensym_full_row = 
			UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,
			row);
		if ( !(gensym_full_row == 
			    IFIX(G2int_invalid_gensym_full_row))) {
		    gensymed_symbol = gensym_full_row << (SI_Long)8L;
		    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
		    code = FIX(gensymed_symbol + gensymed_symbol_1);
		}
		else
		    code = Nil;
		temp = code;
		if (temp);
		else {
		    gensymed_symbol = (SI_Long)63488L;
		    gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
		    extended_code = FIX(gensymed_symbol + gensymed_symbol_1);
		    code = FIX((SI_Long)63232L + (IFIX(unicode) >>  -  - 
			    (SI_Long)8L));
		    temp = code;
		}
	    }
	}
    }
    result = VALUES_2(temp,extended_code);
    MVS_2(result,gensym_character_code,extended_code_qm);
    char_1 = Nil;
    if (FIXNUM_EQ(gensym_character_code,G2int_gensym_code_for_linebreak))
	result = VALUES_2(G2int_gensym_char_or_code_for_linebreak,
		G2int_gensym_esc_for_linebreakqm);
    else if (FIXNUM_EQ(gensym_character_code,
	    G2int_gensym_code_for_paragraph_break))
	result = VALUES_2(G2int_gensym_char_or_code_for_paragraph_break,
		G2int_gensym_esc_for_paragraph_breakqm);
    else {
	if ((SI_Long)32L <= IFIX(gensym_character_code) && 
		IFIX(gensym_character_code) <= (SI_Long)126L) {
	    simple_gensym_character_code = gensym_character_code;
	    temp_1 =  !(FIXNUM_EQ(simple_gensym_character_code,
		    FIX((SI_Long)64L)) || 
		    FIXNUM_EQ(simple_gensym_character_code,
		    FIX((SI_Long)126L)) || 
		    FIXNUM_EQ(simple_gensym_character_code,FIX((SI_Long)92L)));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = CODE_CHAR(gensym_character_code);
	    result = VALUES_2(temp,Nil);
	}
	else {
	    temp = IFIX(gensym_character_code) < (SI_Long)256L ? 
		    ISVREF(G2int_iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code)) : Nil;
	    if (temp);
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_capital_ligature_oe))
		temp = CHR('W');
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_small_ligature_oe))
		temp = CHR('w');
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_bullet))
		temp = CHR('*');
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_small_letter_f_with_hook))
		temp = CHR('&');
	    else if (FIXNUM_EQ(gensym_character_code,
		    G2int_gensym_code_for_trade_mark_sign))
		temp = CHR(':');
	    else
		temp = Qnil;
	    char_1 = temp;
	    if (char_1)
		result = VALUES_2(char_1,CHR('~'));
	    else
		result = VALUES_2(gensym_character_code,CHR('\\'));
	}
    }
    MVS_2(result,character_or_character_code,escape_character_qm);
    if ( !TRUEP(escape_character_qm)) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = character_or_character_code;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	kanji_code = character_or_character_code;
	octet_1_qm = Nil;
	octet_2 = (SI_Long)0L;
	octet_3 = (SI_Long)0L;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = (SI_Long)92L;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = (SI_Long)92L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
	code_1 = kanji_code;
	result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) & 
		(SI_Long)8191L),FIX((SI_Long)95L));
	MVS_2(result,quotient,remainder_1);
	octet_2 = IFIX(quotient) + (SI_Long)40L;
	octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == (SI_Long)1L) 
		? FIX((IFIX(code_1) >>  -  - (SI_Long)13L) + (SI_Long)32L) 
		: Nil;
	if (octet_1_qm) {
	    simple_or_wide_character = octet_1_qm;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = simple_or_wide_character;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	simple_or_wide_character_1 = octet_2;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = simple_or_wide_character_1;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
	simple_or_wide_character_1 = octet_3;
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = simple_or_wide_character_1;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    else {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = escape_character_qm;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = escape_character_qm;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = character_or_character_code;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_2 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    if (extended_code_qm) {
	char_1 = Nil;
	if (FIXNUM_EQ(extended_code_qm,G2int_gensym_code_for_linebreak))
	    result = VALUES_2(G2int_gensym_char_or_code_for_linebreak,
		    G2int_gensym_esc_for_linebreakqm);
	else if (FIXNUM_EQ(extended_code_qm,
		G2int_gensym_code_for_paragraph_break))
	    result = VALUES_2(G2int_gensym_char_or_code_for_paragraph_break,
		    G2int_gensym_esc_for_paragraph_breakqm);
	else {
	    if ((SI_Long)32L <= IFIX(extended_code_qm) && 
		    IFIX(extended_code_qm) <= (SI_Long)126L) {
		simple_gensym_character_code = extended_code_qm;
		temp_1 =  !(FIXNUM_EQ(simple_gensym_character_code,
			FIX((SI_Long)64L)) || 
			FIXNUM_EQ(simple_gensym_character_code,
			FIX((SI_Long)126L)) || 
			FIXNUM_EQ(simple_gensym_character_code,
			FIX((SI_Long)92L)));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = CODE_CHAR(extended_code_qm);
		result = VALUES_2(temp,Nil);
	    }
	    else {
		temp = IFIX(extended_code_qm) < (SI_Long)256L ? 
			ISVREF(G2int_iso_latin1_special_character_code_map,
			IFIX(extended_code_qm)) : Nil;
		if (temp);
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_capital_ligature_oe))
		    temp = CHR('W');
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_small_ligature_oe))
		    temp = CHR('w');
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_bullet))
		    temp = CHR('*');
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_small_letter_f_with_hook))
		    temp = CHR('&');
		else if (FIXNUM_EQ(extended_code_qm,
			G2int_gensym_code_for_trade_mark_sign))
		    temp = CHR(':');
		else
		    temp = Qnil;
		char_1 = temp;
		if (char_1)
		    result = VALUES_2(char_1,CHR('~'));
		else
		    result = VALUES_2(extended_code_qm,CHR('\\'));
	    }
	}
	MVS_2(result,character_or_character_code,escape_character_qm);
	if ( !TRUEP(escape_character_qm)) {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = character_or_character_code;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	    kanji_code = character_or_character_code;
	    octet_1_qm = Nil;
	    octet_2 = (SI_Long)0L;
	    octet_3 = (SI_Long)0L;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = (SI_Long)92L;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = (SI_Long)92L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	    code_1 = kanji_code;
	    result = g2int_chestnut_floorf_function(FIX(IFIX(code_1) & 
		    (SI_Long)8191L),FIX((SI_Long)95L));
	    MVS_2(result,quotient,remainder_1);
	    octet_2 = IFIX(quotient) + (SI_Long)40L;
	    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	    octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
		    (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
		    (SI_Long)13L) + (SI_Long)32L) : Nil;
	    if (octet_1_qm) {
		simple_or_wide_character = octet_1_qm;
		if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
		    thing = simple_or_wide_character;
		    g2int_twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( 
			    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			    G2int_total_length_of_current_gensym_string))
			g2int_extend_current_gensym_string(0);
		    temp_2 = G2int_current_gensym_string;
		    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		    thing = simple_or_wide_character;
		    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		    temp_2 = 
			    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		    G2int_fill_pointer_for_current_gensym_string = temp_2;
		}
	    }
	    simple_or_wide_character_1 = octet_2;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = simple_or_wide_character_1;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = simple_or_wide_character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	    simple_or_wide_character_1 = octet_3;
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing_1 = simple_or_wide_character_1;
		g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing_1 = simple_or_wide_character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	else {
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = escape_character_qm;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = escape_character_qm;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	    if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		thing = character_or_character_code;
		g2int_twrite_wide_character(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
	    }
	    else {
		if ( 
			!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			G2int_total_length_of_current_gensym_string))
		    g2int_extend_current_gensym_string(0);
		temp_2 = G2int_current_gensym_string;
		schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = 
			FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		G2int_fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* INTERN-WIDE-STRING */
Object g2int_intern_wide_string varargs_1(int, n)
{
    Object wide_string;
    Object package_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(26,278);
    INIT_ARGS_nonrelocating();
    wide_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = g2int_intern_wide_string_no_reclaim(2,wide_string,package_qm);
    g2int_reclaim_wide_string(wide_string);
    return VALUES_1(temp);
}

/* INTERN-WIDE-STRING-NO-RECLAIM */
Object g2int_intern_wide_string_no_reclaim varargs_1(int, n)
{
    Object wide_string;
    Object package_qm, index_1, next_char, using_string_buffer_p;
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object code, temp_1, temp_2, wide_character_code, code_1, extended_code;
    Object unicode, temp_3, gensym_character_code_qm, gensym_character_code;
    Object extended_code_qm, char_1, simple_gensym_character_code;
    Object character_or_character_code, escape_character_qm, thing;
    Object schar_new_value, kanji_code, octet_1_qm, quotient, remainder_1;
    Object simple_or_wide_character;
    SI_Long index_2, length_1, ab_loop_bind_, row, gensym_full_row;
    SI_Long gensymed_symbol, gensymed_symbol_1, octet_2, octet_3, thing_1;
    SI_Long simple_or_wide_character_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(4);
    Object result;

    x_note_fn_call(26,279);
    INIT_ARGS_nonrelocating();
    wide_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    index_1 = FIX((SI_Long)0L);
    next_char = Nil;
    using_string_buffer_p = T;
    current_gensym_string = Nil;
    PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qg2int_gensym_string;
	  PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		  0);
	    index_2 = (SI_Long)0L;
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
	    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string,
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	  next_loop:
	    if (index_2 >= ab_loop_bind_)
		goto end_loop;
	    next_char = FIX(UBYTE_16_ISAREF_1(wide_string,index_2));
	    if (using_string_buffer_p && FIXNUM_LT(index_1,
		    G2int_intern_string_buffer_length)) {
		code = next_char;
		temp = IFIX(code) < (SI_Long)127L ?  !((SI_Long)64L == 
			IFIX(code) || (SI_Long)126L == IFIX(code) || 
			(SI_Long)92L == IFIX(code)) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = G2int_intern_string_buffer;
		temp_2 = CODE_CHAR(next_char);
		SET_CHAR(temp_1,index_1,temp_2);
	    }
	    else {
		if (using_string_buffer_p) {
		    using_string_buffer_p = Nil;
		    G2int_current_gensym_string = 
			    g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
		    g2int_twrite_intern_string_buffer_as_gensym_characters(index_1);
		}
		wide_character_code = next_char;
		code_1 = Nil;
		extended_code = Nil;
		unicode = wide_character_code;
		extended_code = Nil;
		code = unicode;
		if (IFIX(code) < (SI_Long)127L &&  !((SI_Long)64L == 
			IFIX(code) || (SI_Long)126L == IFIX(code) || 
			(SI_Long)92L == IFIX(code))) {
		    code_1 = unicode;
		    temp_3 = code_1;
		}
		else {
		    row = IFIX(unicode) >>  -  - (SI_Long)8L;
		    gensym_full_row = 
			    UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,
			    row);
		    if ( !(gensym_full_row == 
			    IFIX(G2int_invalid_gensym_full_row))) {
			gensymed_symbol = gensym_full_row << (SI_Long)8L;
			gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
			gensym_character_code_qm = FIX(gensymed_symbol + 
				gensymed_symbol_1);
		    }
		    else
			gensym_character_code_qm = Nil;
		    if (gensym_character_code_qm) {
			temp = IFIX(gensym_character_code_qm) < 
				(SI_Long)256L ? 
				TRUEP(ISVREF(G2int_iso_latin1_special_character_code_map,
				IFIX(gensym_character_code_qm))) : TRUEP(Nil);
			if (temp);
			else if (FIXNUM_EQ(gensym_character_code_qm,
				G2int_gensym_code_for_capital_ligature_oe))
			    temp = 'W';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				G2int_gensym_code_for_small_ligature_oe))
			    temp = 'w';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				G2int_gensym_code_for_bullet))
			    temp = '*';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				G2int_gensym_code_for_small_letter_f_with_hook))
			    temp = '&';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				G2int_gensym_code_for_trade_mark_sign))
			    temp = ':';
			else
			    temp = TRUEP(Qnil);
			if (temp);
			else
			    temp = (SI_Long)8192L <= 
				    IFIX(gensym_character_code_qm) ? 
				    IFIX(gensym_character_code_qm) <= 
				    (SI_Long)8447L : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			code_1 = gensym_character_code_qm;
			temp_3 = code_1;
		    }
		    else
			temp_3 = Nil;
		    if (temp_3);
		    else {
			code_1 = 
				g2int_map_unicode_to_gensym_han_character_code(unicode);
			temp_3 = code_1;
			if (temp_3);
			else {
			    row = IFIX(unicode) >>  -  - (SI_Long)8L;
			    gensym_full_row = 
				    UBYTE_8_ISAREF_1(G2int_unicode_to_gensym_full_row_map,
				    row);
			    if ( !(gensym_full_row == 
				    IFIX(G2int_invalid_gensym_full_row))) {
				gensymed_symbol = gensym_full_row << 
					(SI_Long)8L;
				gensymed_symbol_1 = (SI_Long)255L & 
					IFIX(unicode);
				code_1 = FIX(gensymed_symbol + 
					gensymed_symbol_1);
			    }
			    else
				code_1 = Nil;
			    temp_3 = code_1;
			    if (temp_3);
			    else {
				gensymed_symbol = (SI_Long)63488L;
				gensymed_symbol_1 = (SI_Long)255L & 
					IFIX(unicode);
				extended_code = FIX(gensymed_symbol + 
					gensymed_symbol_1);
				code_1 = FIX((SI_Long)63232L + 
					(IFIX(unicode) >>  -  - (SI_Long)8L));
				temp_3 = code_1;
			    }
			}
		    }
		}
		result = VALUES_2(temp_3,extended_code);
		MVS_2(result,gensym_character_code,extended_code_qm);
		char_1 = Nil;
		if (FIXNUM_EQ(gensym_character_code,
			G2int_gensym_code_for_linebreak))
		    result = VALUES_2(G2int_gensym_char_or_code_for_linebreak,
			    G2int_gensym_esc_for_linebreakqm);
		else if (FIXNUM_EQ(gensym_character_code,
			G2int_gensym_code_for_paragraph_break))
		    result = VALUES_2(G2int_gensym_char_or_code_for_paragraph_break,
			    G2int_gensym_esc_for_paragraph_breakqm);
		else {
		    if ((SI_Long)32L <= IFIX(gensym_character_code) && 
			    IFIX(gensym_character_code) <= (SI_Long)126L) {
			simple_gensym_character_code = gensym_character_code;
			temp =  !(FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)64L)) || 
				FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)126L)) || 
				FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)92L)));
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			temp_3 = CODE_CHAR(gensym_character_code);
			result = VALUES_2(temp_3,Nil);
		    }
		    else {
			temp_3 = IFIX(gensym_character_code) < 
				(SI_Long)256L ? 
				ISVREF(G2int_iso_latin1_special_character_code_map,
				IFIX(gensym_character_code)) : Nil;
			if (temp_3);
			else if (FIXNUM_EQ(gensym_character_code,
				G2int_gensym_code_for_capital_ligature_oe))
			    temp_3 = CHR('W');
			else if (FIXNUM_EQ(gensym_character_code,
				G2int_gensym_code_for_small_ligature_oe))
			    temp_3 = CHR('w');
			else if (FIXNUM_EQ(gensym_character_code,
				G2int_gensym_code_for_bullet))
			    temp_3 = CHR('*');
			else if (FIXNUM_EQ(gensym_character_code,
				G2int_gensym_code_for_small_letter_f_with_hook))
			    temp_3 = CHR('&');
			else if (FIXNUM_EQ(gensym_character_code,
				G2int_gensym_code_for_trade_mark_sign))
			    temp_3 = CHR(':');
			else
			    temp_3 = Qnil;
			char_1 = temp_3;
			if (char_1)
			    result = VALUES_2(char_1,CHR('~'));
			else
			    result = VALUES_2(gensym_character_code,CHR('\\'));
		    }
		}
		MVS_2(result,character_or_character_code,escape_character_qm);
		if ( !TRUEP(escape_character_qm)) {
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = character_or_character_code;
			g2int_twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp_1 = G2int_current_gensym_string;
			temp_2 = G2int_fill_pointer_for_current_gensym_string;
			thing = character_or_character_code;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp_1;
		    }
		}
		else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
		    kanji_code = character_or_character_code;
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing_1 = (SI_Long)92L;
			g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp_1 = G2int_current_gensym_string;
			temp_2 = G2int_fill_pointer_for_current_gensym_string;
			thing_1 = (SI_Long)92L;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp_1;
		    }
		    code = kanji_code;
		    result = g2int_chestnut_floorf_function(FIX(IFIX(code) 
			    & (SI_Long)8191L),FIX((SI_Long)95L));
		    MVS_2(result,quotient,remainder_1);
		    octet_2 = IFIX(quotient) + (SI_Long)40L;
		    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		    octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L == 
			    (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
			    (SI_Long)13L) + (SI_Long)32L) : Nil;
		    if (octet_1_qm) {
			simple_or_wide_character = octet_1_qm;
			if (EQ(G2int_current_twriting_output_type,
				Qg2int_wide_string)) {
			    thing = simple_or_wide_character;
			    g2int_twrite_wide_character(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				    G2int_total_length_of_current_gensym_string))
				g2int_extend_current_gensym_string(0);
			    temp_1 = G2int_current_gensym_string;
			    temp_2 = 
				    G2int_fill_pointer_for_current_gensym_string;
			    thing = simple_or_wide_character;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			    G2int_fill_pointer_for_current_gensym_string = 
				    temp_1;
			}
		    }
		    simple_or_wide_character_1 = octet_2;
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing_1 = simple_or_wide_character_1;
			g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp_1 = G2int_current_gensym_string;
			temp_2 = G2int_fill_pointer_for_current_gensym_string;
			thing_1 = simple_or_wide_character_1;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp_1;
		    }
		    simple_or_wide_character_1 = octet_3;
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing_1 = simple_or_wide_character_1;
			g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp_1 = G2int_current_gensym_string;
			temp_2 = G2int_fill_pointer_for_current_gensym_string;
			thing_1 = simple_or_wide_character_1;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp_1;
		    }
		}
		else {
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = escape_character_qm;
			g2int_twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp_1 = G2int_current_gensym_string;
			temp_2 = G2int_fill_pointer_for_current_gensym_string;
			thing = escape_character_qm;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp_1;
		    }
		    if (EQ(G2int_current_twriting_output_type,
			    Qg2int_wide_string)) {
			thing = character_or_character_code;
			g2int_twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				G2int_total_length_of_current_gensym_string))
			    g2int_extend_current_gensym_string(0);
			temp_1 = G2int_current_gensym_string;
			temp_2 = G2int_fill_pointer_for_current_gensym_string;
			thing = character_or_character_code;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			G2int_fill_pointer_for_current_gensym_string = temp_1;
		    }
		}
		if (extended_code_qm) {
		    char_1 = Nil;
		    if (FIXNUM_EQ(extended_code_qm,
			    G2int_gensym_code_for_linebreak))
			result = VALUES_2(G2int_gensym_char_or_code_for_linebreak,
				G2int_gensym_esc_for_linebreakqm);
		    else if (FIXNUM_EQ(extended_code_qm,
			    G2int_gensym_code_for_paragraph_break))
			result = VALUES_2(G2int_gensym_char_or_code_for_paragraph_break,
				G2int_gensym_esc_for_paragraph_breakqm);
		    else {
			if ((SI_Long)32L <= IFIX(extended_code_qm) && 
				IFIX(extended_code_qm) <= (SI_Long)126L) {
			    simple_gensym_character_code = extended_code_qm;
			    temp =  
				    !(FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)64L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)126L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)92L)));
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    temp_3 = CODE_CHAR(extended_code_qm);
			    result = VALUES_2(temp_3,Nil);
			}
			else {
			    temp_3 = IFIX(extended_code_qm) < 
				    (SI_Long)256L ? 
				    ISVREF(G2int_iso_latin1_special_character_code_map,
				    IFIX(extended_code_qm)) : Nil;
			    if (temp_3);
			    else if (FIXNUM_EQ(extended_code_qm,
				    G2int_gensym_code_for_capital_ligature_oe))
				temp_3 = CHR('W');
			    else if (FIXNUM_EQ(extended_code_qm,
				    G2int_gensym_code_for_small_ligature_oe))
				temp_3 = CHR('w');
			    else if (FIXNUM_EQ(extended_code_qm,
				    G2int_gensym_code_for_bullet))
				temp_3 = CHR('*');
			    else if (FIXNUM_EQ(extended_code_qm,
				    G2int_gensym_code_for_small_letter_f_with_hook))
				temp_3 = CHR('&');
			    else if (FIXNUM_EQ(extended_code_qm,
				    G2int_gensym_code_for_trade_mark_sign))
				temp_3 = CHR(':');
			    else
				temp_3 = Qnil;
			    char_1 = temp_3;
			    if (char_1)
				result = VALUES_2(char_1,CHR('~'));
			    else
				result = VALUES_2(extended_code_qm,CHR('\\'));
			}
		    }
		    MVS_2(result,character_or_character_code,
			    escape_character_qm);
		    if ( !TRUEP(escape_character_qm)) {
			if (EQ(G2int_current_twriting_output_type,
				Qg2int_wide_string)) {
			    thing = character_or_character_code;
			    g2int_twrite_wide_character(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				    G2int_total_length_of_current_gensym_string))
				g2int_extend_current_gensym_string(0);
			    temp_1 = G2int_current_gensym_string;
			    temp_2 = 
				    G2int_fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			    G2int_fill_pointer_for_current_gensym_string = 
				    temp_1;
			}
		    }
		    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
			kanji_code = character_or_character_code;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			if (EQ(G2int_current_twriting_output_type,
				Qg2int_wide_string)) {
			    thing_1 = (SI_Long)92L;
			    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				    G2int_total_length_of_current_gensym_string))
				g2int_extend_current_gensym_string(0);
			    temp_1 = G2int_current_gensym_string;
			    temp_2 = 
				    G2int_fill_pointer_for_current_gensym_string;
			    thing_1 = (SI_Long)92L;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			    G2int_fill_pointer_for_current_gensym_string = 
				    temp_1;
			}
			code = kanji_code;
			result = g2int_chestnut_floorf_function(FIX(IFIX(code) 
				& (SI_Long)8191L),FIX((SI_Long)95L));
			MVS_2(result,quotient,remainder_1);
			octet_2 = IFIX(quotient) + (SI_Long)40L;
			octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L 
				== (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
				(SI_Long)13L) + (SI_Long)32L) : Nil;
			if (octet_1_qm) {
			    simple_or_wide_character = octet_1_qm;
			    if (EQ(G2int_current_twriting_output_type,
				    Qg2int_wide_string)) {
				thing = simple_or_wide_character;
				g2int_twrite_wide_character(CHARACTERP(thing) 
					? CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
					G2int_total_length_of_current_gensym_string))
				    g2int_extend_current_gensym_string(0);
				temp_1 = G2int_current_gensym_string;
				temp_2 = 
					G2int_fill_pointer_for_current_gensym_string;
				thing = simple_or_wide_character;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_1,temp_2,schar_new_value);
				temp_1 = 
					FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
				G2int_fill_pointer_for_current_gensym_string 
					= temp_1;
			    }
			}
			simple_or_wide_character_1 = octet_2;
			if (EQ(G2int_current_twriting_output_type,
				Qg2int_wide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				    G2int_total_length_of_current_gensym_string))
				g2int_extend_current_gensym_string(0);
			    temp_1 = G2int_current_gensym_string;
			    temp_2 = 
				    G2int_fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			    G2int_fill_pointer_for_current_gensym_string = 
				    temp_1;
			}
			simple_or_wide_character_1 = octet_3;
			if (EQ(G2int_current_twriting_output_type,
				Qg2int_wide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				    G2int_total_length_of_current_gensym_string))
				g2int_extend_current_gensym_string(0);
			    temp_1 = G2int_current_gensym_string;
			    temp_2 = 
				    G2int_fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			    G2int_fill_pointer_for_current_gensym_string = 
				    temp_1;
			}
		    }
		    else {
			if (EQ(G2int_current_twriting_output_type,
				Qg2int_wide_string)) {
			    thing = escape_character_qm;
			    g2int_twrite_wide_character(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				    G2int_total_length_of_current_gensym_string))
				g2int_extend_current_gensym_string(0);
			    temp_1 = G2int_current_gensym_string;
			    temp_2 = 
				    G2int_fill_pointer_for_current_gensym_string;
			    thing = escape_character_qm;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			    G2int_fill_pointer_for_current_gensym_string = 
				    temp_1;
			}
			if (EQ(G2int_current_twriting_output_type,
				Qg2int_wide_string)) {
			    thing = character_or_character_code;
			    g2int_twrite_wide_character(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				    G2int_total_length_of_current_gensym_string))
				g2int_extend_current_gensym_string(0);
			    temp_1 = G2int_current_gensym_string;
			    temp_2 = 
				    G2int_fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			    G2int_fill_pointer_for_current_gensym_string = 
				    temp_1;
			}
		    }
		}
	    }
	    index_1 = FIXNUM_ADD1(index_1);
	    index_2 = index_2 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    if (using_string_buffer_p)
		result = g2int_intern_using_string_buffer(G2int_intern_string_buffer,
			index_1,package_qm);
	    else
		result = g2int_intern_gensym_string(2,
			g2int_copy_out_current_gensym_string(),package_qm);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INTERN-SIMPLE-SYMBOL-PORTION-OF-WIDE-STRING */
Object g2int_intern_simple_symbol_portion_of_wide_string(wide_string,
	    start_init,end_init,package_qm)
    Object wide_string, start_init, end_init, package_qm;
{
    Object s, ab_loop_iter_flag_, schar_new_value, temp;
    SI_Long start, end, i, ab_loop_bind_, j;

    x_note_fn_call(26,280);
    start = IFIX(start_init);
    end = IFIX(end_init);
    s = g2int_obtain_simple_gensym_string(FIX(end - start));
    i = start;
    ab_loop_bind_ = end;
    j = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	j = j + (SI_Long)1L;
    schar_new_value = CODE_CHAR(FIX(UBYTE_16_ISAREF_1(wide_string,i)));
    SET_ISCHAR(s,j,ICHAR_CODE(schar_new_value));
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = s;
    goto end_1;
    temp = Qnil;
  end_1:;
    temp = g2int_intern_gensym_string(2,temp,package_qm);
    return VALUES_1(temp);
}

/* INTERN-AND-UPCASE-SIMPLE-SYMBOL-PORTION-OF-WIDE-STRING */
Object g2int_intern_and_upcase_simple_symbol_portion_of_wide_string(wide_string,
	    start_init,end_init,package_qm)
    Object wide_string, start_init, end_init, package_qm;
{
    Object s, ab_loop_iter_flag_, schar_new_value, temp;
    SI_Long start, end, char_1, case_delta, i, ab_loop_bind_, j, arg, arg_1;
    SI_Long arg_2;

    x_note_fn_call(26,281);
    start = IFIX(start_init);
    end = IFIX(end_init);
    char_1 = (SI_Long)0L;
    s = g2int_obtain_simple_gensym_string(FIX(end - start));
    case_delta = (SI_Long)-32L;
    i = start;
    ab_loop_bind_ = end;
    j = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	j = j + (SI_Long)1L;
    char_1 = UBYTE_16_ISAREF_1(wide_string,i);
    arg = (SI_Long)97L;
    arg_1 = char_1;
    arg_2 = (SI_Long)122L;
    schar_new_value = CODE_CHAR(arg <= arg_1 && arg_1 <= arg_2 ? 
	    FIX(char_1 + case_delta) : FIX(char_1));
    SET_ISCHAR(s,j,ICHAR_CODE(schar_new_value));
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = s;
    goto end_1;
    temp = Qnil;
  end_1:;
    temp = g2int_intern_gensym_string(2,temp,package_qm);
    return VALUES_1(temp);
}

/* WIDE-STRING-TO-GENSYM-STRING */
Object g2int_wide_string_to_gensym_string(wide_string)
    Object wide_string;
{
    Object temp;

    x_note_fn_call(26,282);
    temp = g2int_unicode_to_utf_g_gensym_string(wide_string);
    return VALUES_1(temp);
}

static Object list_constant_15;    /* # */

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object list_constant_18;    /* # */

static Object list_constant_19;    /* # */

/* GET-LINE-END-SEQUENCE-FROM-STYLE */
Object g2int_get_line_end_sequence_from_style(transcode_text_conversion_style)
    Object transcode_text_conversion_style;
{
    Object temp;

    x_note_fn_call(26,283);
    temp = ISVREF(transcode_text_conversion_style,(SI_Long)4L);
    if (EQ(temp,Qg2int_per_platform)) {
	if (EQ(G2int_g2_operating_system,Qg2int_dos) || 
		EQ(G2int_g2_operating_system,Qg2int_vms) || 
		EQ(G2int_g2_operating_system,Qg2int_win32))
	    temp = list_constant_15;
	else if (EQ(G2int_g2_operating_system,Qg2int_unix))
	    temp = list_constant_16;
	else
	    temp = list_constant_16;
    }
    else if (EQ(temp,Qg2int_cr))
	temp = list_constant_17;
    else if (EQ(temp,Qg2int_lf))
	temp = list_constant_16;
    else if (EQ(temp,Qg2int_crlf))
	temp = list_constant_15;
    else if (EQ(temp,Qg2int_unicode_line_separator))
	temp = list_constant_18;
    else if (EQ(temp,Qg2int_unicode_paragraph_separator))
	temp = list_constant_19;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* G2-STREAM-WRITE-UCS-2-CHARACTER */
Object g2int_g2_stream_write_ucs_2_character(character_1,byte_swapped_p,
	    g2_stream)
    Object character_1, byte_swapped_p, g2_stream;
{
    Object temp;

    x_note_fn_call(26,284);
    temp = g2int_g2_stream_write_char(byte_swapped_p ? 
	    FIX(IFIX(character_1) & (SI_Long)255L) : FIX(IFIX(character_1) 
	    >>  -  - (SI_Long)8L),g2_stream) ? 
	    g2int_g2_stream_write_char(byte_swapped_p ? 
	    FIX(IFIX(character_1) >>  -  - (SI_Long)8L) : 
	    FIX(IFIX(character_1) & (SI_Long)255L),g2_stream) : Nil;
    return VALUES_1(temp);
}

/* G2-STREAM-WRITE-TRAILING-BYTES-OF-WIDE-STRING */
Object g2int_g2_stream_write_trailing_bytes_of_wide_string(string_1,g2_stream)
    Object string_1, g2_stream;
{
    Object character_1, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(26,285);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(g2int_lengthw(string_1));
    character_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
    if ( !TRUEP(g2int_g2_stream_write_char(FIX(IFIX(character_1) & 
	    (SI_Long)255L),g2_stream))) {
	temp = Nil;
	goto end;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = T;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

static Object Qg2int_unicode;      /* unicode */

static Object Qg2int_unicode_byte_swapped;  /* unicode-byte-swapped */

static Object Qg2int_unicode_ucs_2;  /* unicode-ucs-2 */

static Object Qg2int_unicode_ucs_2_byte_swapped;  /* unicode-ucs-2-byte-swapped */

/* G2-STREAM-WRITE-LINE-TERMINATOR-USING-TEXT-CONVERSION-STYLE */
Object g2int_g2_stream_write_line_terminator_using_text_conversion_style(transcode_text_conversion_style,
	    g2_stream)
    Object transcode_text_conversion_style, g2_stream;
{
    Object line_end_character_sequence, gensymed_symbol, character_1;
    Object ab_loop_list_, temp;

    x_note_fn_call(26,286);
    line_end_character_sequence = 
	    g2int_get_line_end_sequence_from_style(transcode_text_conversion_style);
    gensymed_symbol = ISVREF(transcode_text_conversion_style,(SI_Long)2L);
    if ((SI_Long)2L == (EQ(gensymed_symbol,Qg2int_unicode) || 
	    EQ(gensymed_symbol,Qg2int_unicode_byte_swapped) || 
	    EQ(gensymed_symbol,Qg2int_unicode_ucs_2) || EQ(gensymed_symbol,
	    Qg2int_unicode_ucs_2_byte_swapped) ? (SI_Long)2L : (SI_Long)1L)) {
	character_1 = Nil;
	ab_loop_list_ = line_end_character_sequence;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	character_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = character_1;
	gensymed_symbol = ISVREF(transcode_text_conversion_style,(SI_Long)2L);
	if ( !TRUEP(g2int_g2_stream_write_ucs_2_character(temp,
		EQ(gensymed_symbol,Qg2int_unicode_byte_swapped) || 
		EQ(gensymed_symbol,Qg2int_unicode_ucs_2_byte_swapped) ? T :
		 Nil,g2_stream))) {
	    temp = Nil;
	    goto end;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end;
	temp = Qnil;
      end:;
    }
    else {
	character_1 = Nil;
	ab_loop_list_ = line_end_character_sequence;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	character_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(g2int_g2_stream_write_char(character_1,g2_stream))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

Object G2int_standard_8_bit_non_graphic_characters_skip_spec = UNBOUND;

void transcode_INIT()
{
    Object temp, reclaim_structure_for_transcode_text_conversion_style;
    Object reclaim_structure_for_text_sequence;
    Object reclaim_structure_for_gensym_string_text_sequence;
    Object reclaim_structure_for_wide_string_text_sequence;
    Object initialize_text_sequence_string_for_text_sequence;
    Object initialize_text_sequence_string_for_gensym_string_text_sequence;
    Object initialize_text_sequence_string_for_wide_string_text_sequence;
    Object read_character_from_text_sequence_for_gensym_string_text_sequence;
    Object read_character_from_text_sequence_for_wide_string_text_sequence;
    Object reclaim_structure_for_transcoder;
    Object transcode_character_for_transcoder, export_character_for_transcoder;
    Object transcode_as_text_string_for_transcoder;
    Object twrite_unicode_from_transcoder_for_transcoder;
    Object export_as_string_for_transcoder;
    Object twrite_for_export_from_transcoder_for_transcoder;
    Object reclaim_structure_for_graphic_character_set;
    Object reclaim_structure_for_iso_646, synonym, ab_loop_list_;
    Object map_code_to_unicode_for_iso_646;
    Object map_unicode_to_code_if_any_for_iso_646;
    Object reclaim_structure_for_iso_8859_abstract;
    Object map_code_to_unicode_for_iso_8859_abstract;
    Object map_unicode_to_code_if_any_for_iso_8859_abstract;
    Object reclaim_structure_for_iso_8859_1, reclaim_structure_for_iso_8859_2;
    Object reclaim_structure_for_iso_8859_3, reclaim_structure_for_iso_8859_4;
    Object reclaim_structure_for_iso_8859_5, reclaim_structure_for_iso_8859_6;
    Object reclaim_structure_for_iso_8859_7, reclaim_structure_for_iso_8859_8;
    Object reclaim_structure_for_iso_8859_9, reclaim_structure_for_iso_8859_10;
    Object reclaim_structure_for_asian_double_byte;
    Object map_code_to_unicode_for_asian_double_byte;
    Object reclaim_structure_for_jis_x_0208;
    Object map_code_to_unicode_for_jis_x_0208;
    Object map_unicode_to_code_if_any_for_jis_x_0208;
    Object reclaim_structure_for_ks_c_5601, map_code_to_unicode_for_ks_c_5601;
    Object map_unicode_to_code_if_any_for_ks_c_5601;
    Object reclaim_structure_for_gb_2312, map_code_to_unicode_for_gb_2312;
    Object map_unicode_to_code_if_any_for_gb_2312;
    Object reclaim_structure_for_iso_8859_transcoder;
    Object transcode_character_for_iso_8859_transcoder;
    Object export_character_for_iso_8859_transcoder;
    Object reclaim_structure_for_iso_2022_transcoder, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, temp_7, temp_8, temp_9, temp_10, temp_11;
    Object temp_12, transcode_character_for_iso_2022_transcoder;
    Object export_character_for_iso_2022_transcoder;
    Object reclaim_structure_for_shift_jis_transcoder;
    Object transcode_character_for_shift_jis_transcoder;
    Object export_character_for_shift_jis_transcoder;
    Object reclaim_structure_for_utf_g_transcoder;
    Object transcode_character_for_utf_g_transcoder;
    Object export_character_for_utf_g_transcoder;
    Object reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder;
    Object export_character_for_utf_g_ascii_as_much_as_possible_transcoder;
    Object reclaim_structure_for_unicode_ucs_2_transcoder;
    Object transcode_character_for_unicode_ucs_2_transcoder;
    Object export_character_for_unicode_ucs_2_transcoder;
    Object reclaim_structure_for_unicode_transcoder;
    Object transcode_character_for_unicode_transcoder;
    Object export_character_for_unicode_transcoder;
    Object reclaim_structure_for_unicode_byte_swapped_transcoder;
    Object transcode_character_for_unicode_byte_swapped_transcoder;
    Object export_character_for_unicode_byte_swapped_transcoder;
    Object reclaim_structure_for_utf_7_transcoder;
    Object transcode_character_for_utf_7_transcoder;
    Object export_character_for_utf_7_transcoder;
    Object reclaim_structure_for_utf_8_transcoder;
    Object transcode_character_for_utf_8_transcoder;
    Object export_character_for_utf_8_transcoder;
    Object list_constant_42, list_constant_41, Qg2int_utf_8_transcoder;
    Object Qg2int_export_character, Qg2int_transcode_character;
    Object Qg2int_create_transcoder_for_unicode_utf_8, list_constant_40;
    Object Qg2int_utf_8, AB_package, Qg2int_unicode_utf_8;
    Object Qg2int_reclaim_structure, Qg2int_utilities2;
    Object Qg2int_utf_8_transcoder_count;
    Object Qg2int_chain_of_available_utf_8_transcoders;
    Object Qg2int_type_description_of_type, string_constant_34;
    Object Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_39;
    Object list_constant_38, list_constant_37, list_constant_36;
    Object Qg2int_utf_7_transcoder, Qg2int_create_transcoder_for_unicode_utf_7;
    Object list_constant_35, Qg2int_utf_7, Qg2int_unicode_utf_7;
    Object Qg2int_utf_7_transcoder_count;
    Object Qg2int_chain_of_available_utf_7_transcoders, string_constant_33;
    Object string_constant_32;
    Object Qg2int_create_transcoder_for_unicode_byte_swapped, list_constant_34;
    Object Qg2int_iso_10646_byte_swapped, Qg2int_create_transcoder_for_unicode;
    Object list_constant_33, Qg2int_iso_10646;
    Object Qg2int_create_transcoder_for_unicode_ucs_2_byte_swapped;
    Object Qg2int_create_transcoder_for_unicode_ucs_2, list_constant_32;
    Object Qg2int_iso_10646_ucs_2;
    Object Qg2int_create_transcoder_for_gensym_with_ascii_as_much_as_possible;
    Object list_constant_31, Qg2int_utf_g_ascii_as_much_as_possible;
    Object Qg2int_gensym_with_ascii_as_much_as_possible;
    Object Qg2int_create_transcoder_for_gensym, list_constant_30, Qg2int_utf_g;
    Object Qg2int_create_transcoder_for_iso_8859_10;
    Object Qg2int_create_transcoder_for_iso_8859_9;
    Object Qg2int_create_transcoder_for_iso_8859_8;
    Object Qg2int_create_transcoder_for_iso_8859_7;
    Object Qg2int_create_transcoder_for_iso_8859_6;
    Object Qg2int_create_transcoder_for_iso_8859_5;
    Object Qg2int_create_transcoder_for_iso_8859_4;
    Object Qg2int_create_transcoder_for_iso_8859_3;
    Object Qg2int_create_transcoder_for_iso_8859_2;
    Object Qg2int_create_transcoder_for_iso_8859_1;
    Object Qg2int_unicode_byte_swapped_transcoder;
    Object Qg2int_unicode_byte_swapped_transcoder_count;
    Object Qg2int_chain_of_available_unicode_byte_swapped_transcoders;
    Object string_constant_31, Qg2int_unicode_transcoder;
    Object Qg2int_unicode_transcoder_count;
    Object Qg2int_chain_of_available_unicode_transcoders, string_constant_30;
    Object Qg2int_unicode_ucs_2_transcoder;
    Object Qg2int_unicode_ucs_2_transcoder_count;
    Object Qg2int_chain_of_available_unicode_ucs_2_transcoders;
    Object string_constant_29;
    Object Qg2int_utf_g_ascii_as_much_as_possible_transcoder;
    Object Qg2int_utf_g_ascii_as_much_as_possible_transcoder_count;
    Object Qg2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders;
    Object string_constant_28, Qg2int_utf_g_transcoder;
    Object Qg2int_utf_g_transcoder_count;
    Object Qg2int_chain_of_available_utf_g_transcoders, string_constant_27;
    Object Qg2int_shift_jis_transcoder, Qg2int_shift_jis_transcoder_count;
    Object Qg2int_chain_of_available_shift_jis_transcoders, string_constant_26;
    Object Qg2int_iso_2022_transcoder, list_constant_29, list_constant_28;
    Object list_constant_20, Qg2int_create_transcoder_for_gb_2312_euc;
    Object list_constant_27, Qg2int_gb2312_euc, Qg2int_gb_euc;
    Object Qg2int_gb_2312_euc, Qg2int_create_transcoder_for_gb_2312;
    Object Qg2int_create_transcoder_for_ks_c_5601_euc, list_constant_26;
    Object Qg2int_ksc_euc, Qg2int_ks_euc, Qg2int_ks_c_5601_euc;
    Object Qg2int_create_transcoder_for_ks_c_5601;
    Object Qg2int_create_transcoder_for_shift_jis_x_0208, list_constant_25;
    Object Qg2int_shift_jis, Qg2int_ms_kanji, Qg2int_shift_jis_x_0208;
    Object Qg2int_create_transcoder_for_jis_x_0208_euc, list_constant_24;
    Object Qg2int_jis_euc, Qg2int_jis_x_0208_euc;
    Object Qg2int_create_transcoder_for_jis_x_0208;
    Object Qg2int_create_transcoder_for_iso_2022, list_constant_23;
    Object Qg2int_x_compound_text, Qg2int_iso_2022;
    Object Qg2int_create_transcoder_for_iso_646, list_constant_22;
    Object list_constant_21, Qg2int_ascii, Qg2int_iso_646_irv, Qg2int_us_ascii;
    Object Qg2int_ansi3dot4, Qg2int_iso_2022_transcoder_count;
    Object Qg2int_chain_of_available_iso_2022_transcoders, string_constant_25;
    Object Qg2int_iso_8859_transcoder, Qg2int_iso_8859_transcoder_count;
    Object Qg2int_chain_of_available_iso_8859_transcoders, string_constant_24;
    Object Qg2int_map_unicode_to_code_if_any, Qg2int_map_code_to_unicode;
    Object Qg2int_gb2312, Qg2int_gb, Qg2int_gb_2312_count;
    Object Qg2int_chain_of_available_gb_2312s, string_constant_23, Qg2int_ksc;
    Object Qg2int_ks, Qg2int_ks_c_5601_count;
    Object Qg2int_chain_of_available_ks_c_5601s, string_constant_10;
    Object string_constant_22, Qg2int_jis, Qg2int_jis_x_0208_count;
    Object Qg2int_chain_of_available_jis_x_0208s, string_constant_21;
    Object Qg2int_asian_double_byte_count;
    Object Qg2int_chain_of_available_asian_double_bytes, string_constant_20;
    Object Qg2int_latin_6, Qg2int_iso_8859_10_count;
    Object Qg2int_chain_of_available_iso_8859_10s, string_constant_19;
    Object Qg2int_latin_5, Qg2int_iso_8859_9_count;
    Object Qg2int_chain_of_available_iso_8859_9s, string_constant_18;
    Object Qg2int_latin_hebrew, Qg2int_iso_8859_8_count;
    Object Qg2int_chain_of_available_iso_8859_8s, string_constant_17;
    Object Qg2int_latin_greek, Qg2int_iso_8859_7_count;
    Object Qg2int_chain_of_available_iso_8859_7s, string_constant_16;
    Object Qg2int_latin_arabic, Qg2int_iso_8859_6_count;
    Object Qg2int_chain_of_available_iso_8859_6s, string_constant_15;
    Object Qg2int_latin_cyrillic, Qg2int_iso_8859_5_count;
    Object Qg2int_chain_of_available_iso_8859_5s, string_constant_14;
    Object Qg2int_latin_4, Qg2int_iso_8859_4_count;
    Object Qg2int_chain_of_available_iso_8859_4s, string_constant_13;
    Object Qg2int_latin_3, Qg2int_iso_8859_3_count;
    Object Qg2int_chain_of_available_iso_8859_3s, string_constant_12;
    Object Qg2int_latin_2, Qg2int_iso_8859_2_count;
    Object Qg2int_chain_of_available_iso_8859_2s, string_constant_11;
    Object Qg2int_latin_1, Qg2int_iso_8859_1_count;
    Object Qg2int_chain_of_available_iso_8859_1s, string_constant_9;
    Object Qg2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors;
    Object Qg2int_available_8859_reverse_unicode_map_hash_vector_43_vectors;
    Object Qg2int_iso_8859_abstract_count;
    Object Qg2int_chain_of_available_iso_8859_abstracts, string_constant_8;
    Object Qg2int_iso_646_count, Qg2int_chain_of_available_iso_646s;
    Object string_constant_7, string_constant_6;
    Object Qg2int_graphic_character_set_count;
    Object Qg2int_chain_of_available_graphic_character_sets, string_constant_5;
    Object Qg2int_transcoder, Qg2int_twrite_for_export_from_transcoder;
    Object Qg2int_export_as_string, Qg2int_twrite_unicode_from_transcoder;
    Object Qg2int_transcode_as_text_string, Qg2int_transcoder_count;
    Object Qg2int_chain_of_available_transcoders, string_constant_4;
    Object Qg2int_wide_string_text_sequence;
    Object Qg2int_read_character_from_text_sequence;
    Object Qg2int_gensym_string_text_sequence;
    Object Qg2int_initialize_text_sequence_string, Qg2int_text_sequence;
    Object Qg2int_wide_string_text_sequence_count;
    Object Qg2int_chain_of_available_wide_string_text_sequences;
    Object string_constant_3, Qg2int_gensym_string_text_sequence_count;
    Object Qg2int_chain_of_available_gensym_string_text_sequences;
    Object string_constant_2, Qg2int_text_sequence_count;
    Object Qg2int_chain_of_available_text_sequences, string_constant_1;
    Object Qg2int_utf_g_gensym_string, Qg2int_utf_g_wide_string;
    Object Qg2int_utf_8_gensym_string_with_crlf;
    Object Qg2int_utf_8_gensym_string_with_newline, Qg2int_utf_8_gensym_string;
    Object Qg2int_utf_8_wide_string, Qg2int_utf_7_gensym_string;
    Object Qg2int_utf_7_wide_string;
    Object Qg2int_iso_8859_10_gensym_string_with_crlf;
    Object Qg2int_iso_8859_10_gensym_string, Qg2int_iso_8859_10_wide_string;
    Object Qg2int_iso_8859_9_gensym_string_with_crlf;
    Object Qg2int_iso_8859_9_gensym_string, Qg2int_iso_8859_9_wide_string;
    Object Qg2int_iso_8859_8_gensym_string_with_crlf;
    Object Qg2int_iso_8859_8_gensym_string, Qg2int_iso_8859_8_wide_string;
    Object Qg2int_iso_8859_7_gensym_string_with_crlf;
    Object Qg2int_iso_8859_7_gensym_string, Qg2int_iso_8859_7_wide_string;
    Object Qg2int_iso_8859_6_gensym_string_with_crlf;
    Object Qg2int_iso_8859_6_gensym_string, Qg2int_iso_8859_6_wide_string;
    Object Qg2int_iso_8859_5_gensym_string_with_crlf;
    Object Qg2int_iso_8859_5_gensym_string, Qg2int_iso_8859_5_wide_string;
    Object Qg2int_iso_8859_4_gensym_string_with_crlf;
    Object Qg2int_iso_8859_4_gensym_string, Qg2int_iso_8859_4_wide_string;
    Object Qg2int_iso_8859_3_gensym_string_with_crlf;
    Object Qg2int_iso_8859_3_gensym_string, Qg2int_iso_8859_3_wide_string;
    Object Qg2int_iso_8859_2_gensym_string_with_crlf;
    Object Qg2int_iso_8859_2_gensym_string, Qg2int_iso_8859_2_wide_string;
    Object Qg2int_iso_8859_1_gensym_string_with_crlf;
    Object Qg2int_iso_8859_1_gensym_string, Qg2int_iso_8859_1_wide_string;
    Object Qg2int_filter_text_for_gsi, Qg2int_idl_source_file_pathname;
    Object Qg2int_iso_latin1_gensym_string;
    Object Qg2int_icp_filtered_text_string_reader, Qg2int_kb_error;
    Object Qg2int_notify_user_if_possible_via_console;
    Object Qg2int_instantiate_file_template_for_printing, Qg2int_pformat;
    Object Qg2int_gensym_pathname_namestring, Qg2int_g2_directory_pathname;
    Object Qg2int_us_ascii_gensym_string_with_crlf;
    Object Qg2int_known_ascii_to_ascii, Qg2int_known_iso_latin1_to_iso_latin1;
    Object Qg2int_utf_g_ascii_as_much_as_possible_string, Qg2int_utf_g_string;
    Object Qg2int_cf_unicode_text, Qg2int_cf_text, Qg2int_x_string;
    Object Qg2int_x_compound_text_string;
    Object Qg2int_gb_2312_euc_gensym_string_with_crlf;
    Object Qg2int_gb_2312_euc_string, Qg2int_gb_2312_gensym_string_with_crlf;
    Object Qg2int_gb_2312_string, Qg2int_ks_euc_gensym_string_with_crlf;
    Object Qg2int_ks_euc_string, Qg2int_ks_gensym_string_with_crlf;
    Object Qg2int_ks_string, Qg2int_shift_jis_gensym_string_with_crlf;
    Object Qg2int_shift_jis_string, Qg2int_jis_euc_gensym_string_with_crlf;
    Object Qg2int_jis_euc_string, Qg2int_jis_gensym_string_with_crlf;
    Object Qg2int_jis_string, Qg2int_8859_10_string, Qg2int_8859_9_string;
    Object Qg2int_8859_8_string, Qg2int_8859_7_string, Qg2int_8859_6_string;
    Object Qg2int_8859_5_string, Qg2int_8859_4_string, Qg2int_8859_3_string;
    Object Qg2int_8859_2_string, Qg2int_8859_1_string, Qg2int_utf_8_string;
    Object Qg2int_utf_7_string, Qg2int_irrelevant;
    Object Qg2int_user_command_line_argument, Qg2int_attribute_file_line;
    Object Qg2int_gfi_input_line, Qg2int_kb_file_comment;
    Object Qg2int_ole_text_of_single_byte_chars, Qg2int_idl_file_input;
    Object Qg2int_icp_filtered_text_string_writer, Qg2int_x_cut_buffer;
    Object Qg2int_namestring_as_gensym_string, Qg2int_win32_message;
    Object Qg2int_g2_directory_pathname_w, Qg2int_kfep_filename;
    Object Qg2int_init_file_command_line, Qg2int_g2_stream_error_string;
    Object Qg2int_command_line_argument;
    Object Qg2int_transcode_text_conversion_style;
    Object Qg2int_transcode_text_conversion_style_count;
    Object Qg2int_chain_of_available_transcode_text_conversion_styles;
    Object string_constant, Qg2int_unicode_replacement_character;
    Object Qg2int_ascii_replacement_character;

    x_note_fn_call(26,287);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_ascii_replacement_character = 
	    STATIC_SYMBOL("ASCII-REPLACEMENT-CHARACTER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ascii_replacement_character,FIX((SI_Long)63L));
    Qg2int_unicode_replacement_character = 
	    STATIC_SYMBOL("UNICODE-REPLACEMENT-CHARACTER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unicode_replacement_character,
	    FIX((SI_Long)65533L));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct 
	    = STATIC_SYMBOL("TRANSCODE-TEXT-CONVERSION-STYLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_transcode_text_conversion_style = 
	    STATIC_SYMBOL("TRANSCODE-TEXT-CONVERSION-STYLE",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct,
	    Qg2int_transcode_text_conversion_style,
	    Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_transcode_text_conversion_style,
	    Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_transcode_text_conversion_style == 
	    UNBOUND)
	G2int_the_type_description_of_transcode_text_conversion_style = Nil;
    string_constant = STATIC_STRING("43Dy8l8303y1n8303y8m8k1l8m0000000krk0k0");
    temp = G2int_the_type_description_of_transcode_text_conversion_style;
    G2int_the_type_description_of_transcode_text_conversion_style = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct,
	    G2int_the_type_description_of_transcode_text_conversion_style,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_transcode_text_conversion_style,
	    G2int_the_type_description_of_transcode_text_conversion_style,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_transcode_text_conversion_styles = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TRANSCODE-TEXT-CONVERSION-STYLES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_transcode_text_conversion_styles,
	    G2int_chain_of_available_transcode_text_conversion_styles);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_transcode_text_conversion_styles,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_transcode_text_conversion_style_count = 
	    STATIC_SYMBOL("TRANSCODE-TEXT-CONVERSION-STYLE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_transcode_text_conversion_style_count,
	    G2int_transcode_text_conversion_style_count);
    g2int_record_system_variable(Qg2int_transcode_text_conversion_style_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_transcode_text_conversion_style = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_transcode_text_conversion_style,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_transcode_text_conversion_style,
	    reclaim_structure_for_transcode_text_conversion_style);
    Qg2int_per_platform = STATIC_SYMBOL("PER-PLATFORM",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qg2int_text_conversion_style_for_purpose = 
	    STATIC_SYMBOL("TEXT-CONVERSION-STYLE-FOR-PURPOSE",AB_package);
    G2int_text_conversion_style_for_purpose_prop = 
	    Qg2int_text_conversion_style_for_purpose;
    Qg2int_command_line_argument = STATIC_SYMBOL("COMMAND-LINE-ARGUMENT",
	    AB_package);
    Qg2int_iso_8859_1 = STATIC_SYMBOL("ISO-8859-1",AB_package);
    Qg2int_irrelevant = STATIC_SYMBOL("IRRELEVANT",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_command_line_argument,Qnil,
	    Qnil,Qg2int_iso_8859_1,Qnil,Qg2int_irrelevant,Qnil,Qnil);
    Qg2int_g2_stream_error_string = STATIC_SYMBOL("G2-STREAM-ERROR-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_g2_stream_error_string,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qg2int_irrelevant,Qnil,Qnil);
    Qg2int_init_file_command_line = STATIC_SYMBOL("INIT-FILE-COMMAND-LINE",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_init_file_command_line,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qg2int_irrelevant,Qnil,Qnil);
    Qg2int_kfep_filename = STATIC_SYMBOL("KFEP-FILENAME",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_kfep_filename,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qg2int_irrelevant,Qnil,Qnil);
    Qg2int_g2_directory_pathname = STATIC_SYMBOL("G2-DIRECTORY-PATHNAME",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_g2_directory_pathname,Qnil,
	    Qnil,Qg2int_iso_8859_1,Qnil,Qg2int_irrelevant,Qnil,Qnil);
    Qg2int_g2_directory_pathname_w = 
	    STATIC_SYMBOL("G2-DIRECTORY-PATHNAME-W",AB_package);
    Qg2int_unicode = STATIC_SYMBOL("UNICODE",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_g2_directory_pathname_w,
	    Qnil,Qnil,Qg2int_unicode,Qnil,Qg2int_irrelevant,Qnil,Qnil);
    Qg2int_win32_message = STATIC_SYMBOL("WIN32-MESSAGE",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_win32_message,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_icp_filtered_text_string_writer = 
	    STATIC_SYMBOL("ICP-FILTERED-TEXT-STRING-WRITER",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_icp_filtered_text_string_writer,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_gensym_pathname_namestring = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-NAMESTRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_gensym_pathname_namestring,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_namestring_as_gensym_string = 
	    STATIC_SYMBOL("NAMESTRING-AS-GENSYM-STRING",AB_package);
    Qg2int_gensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_namestring_as_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_x_cut_buffer = STATIC_SYMBOL("X-CUT-BUFFER",AB_package);
    Qg2int_lf = STATIC_SYMBOL("LF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_x_cut_buffer,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qg2int_lf,Qnil,Qg2int_gensym_string);
    g2int_install_text_transcode_purpose(Qg2int_icp_filtered_text_string_writer,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_idl_file_input = STATIC_SYMBOL("IDL-FILE-INPUT",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_idl_file_input,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_ole_text_of_single_byte_chars = 
	    STATIC_SYMBOL("OLE-TEXT-OF-SINGLE-BYTE-CHARS",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_ole_text_of_single_byte_chars,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_filter_text_for_gsi = STATIC_SYMBOL("FILTER-TEXT-FOR-GSI",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_filter_text_for_gsi,Qnil,
	    Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_kb_file_comment = STATIC_SYMBOL("KB-FILE-COMMENT",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_kb_file_comment,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_gfi_input_line = STATIC_SYMBOL("GFI-INPUT-LINE",AB_package);
    Qg2int_utf_g = STATIC_SYMBOL("UTF-G",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_gfi_input_line,Qnil,Qnil,
	    Qg2int_utf_g,Qnil,Qnil,Qnil,Qnil);
    Qg2int_attribute_file_line = STATIC_SYMBOL("ATTRIBUTE-FILE-LINE",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_attribute_file_line,Qnil,
	    Qnil,Qg2int_utf_g,Qnil,Qnil,Qnil,Qnil);
    Qg2int_user_command_line_argument = 
	    STATIC_SYMBOL("USER-COMMAND-LINE-ARGUMENT",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_user_command_line_argument,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qg2int_irrelevant,Qnil,Qnil);
    Qg2int_utf_7_string = STATIC_SYMBOL("UTF-7-STRING",AB_package);
    Qg2int_unicode_utf_7 = STATIC_SYMBOL("UNICODE-UTF-7",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_7_string,Qnil,Qnil,
	    Qg2int_unicode_utf_7,Qnil,Qnil,Qnil,Qnil);
    Qg2int_utf_8_string = STATIC_SYMBOL("UTF-8-STRING",AB_package);
    Qg2int_unicode_utf_8 = STATIC_SYMBOL("UNICODE-UTF-8",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_8_string,Qnil,Qnil,
	    Qg2int_unicode_utf_8,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_1_string = STATIC_SYMBOL("8859-1-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_1_string,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_2_string = STATIC_SYMBOL("8859-2-STRING",AB_package);
    Qg2int_iso_8859_2 = STATIC_SYMBOL("ISO-8859-2",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_2_string,Qnil,Qnil,
	    Qg2int_iso_8859_2,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_3_string = STATIC_SYMBOL("8859-3-STRING",AB_package);
    Qg2int_iso_8859_3 = STATIC_SYMBOL("ISO-8859-3",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_3_string,Qnil,Qnil,
	    Qg2int_iso_8859_3,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_4_string = STATIC_SYMBOL("8859-4-STRING",AB_package);
    Qg2int_iso_8859_4 = STATIC_SYMBOL("ISO-8859-4",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_4_string,Qnil,Qnil,
	    Qg2int_iso_8859_4,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_5_string = STATIC_SYMBOL("8859-5-STRING",AB_package);
    Qg2int_iso_8859_5 = STATIC_SYMBOL("ISO-8859-5",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_5_string,Qnil,Qnil,
	    Qg2int_iso_8859_5,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_6_string = STATIC_SYMBOL("8859-6-STRING",AB_package);
    Qg2int_iso_8859_6 = STATIC_SYMBOL("ISO-8859-6",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_6_string,Qnil,Qnil,
	    Qg2int_iso_8859_6,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_7_string = STATIC_SYMBOL("8859-7-STRING",AB_package);
    Qg2int_iso_8859_7 = STATIC_SYMBOL("ISO-8859-7",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_7_string,Qnil,Qnil,
	    Qg2int_iso_8859_7,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_8_string = STATIC_SYMBOL("8859-8-STRING",AB_package);
    Qg2int_iso_8859_8 = STATIC_SYMBOL("ISO-8859-8",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_8_string,Qnil,Qnil,
	    Qg2int_iso_8859_8,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_9_string = STATIC_SYMBOL("8859-9-STRING",AB_package);
    Qg2int_iso_8859_9 = STATIC_SYMBOL("ISO-8859-9",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_9_string,Qnil,Qnil,
	    Qg2int_iso_8859_9,Qnil,Qnil,Qnil,Qnil);
    Qg2int_8859_10_string = STATIC_SYMBOL("8859-10-STRING",AB_package);
    Qg2int_iso_8859_10 = STATIC_SYMBOL("ISO-8859-10",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_8859_10_string,Qnil,Qnil,
	    Qg2int_iso_8859_10,Qnil,Qnil,Qnil,Qnil);
    Qg2int_jis_string = STATIC_SYMBOL("JIS-STRING",AB_package);
    Qg2int_jis_x_0208 = STATIC_SYMBOL("JIS-X-0208",AB_package);
    Qg2int_japanese = STATIC_SYMBOL("JAPANESE",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_jis_string,Qnil,Qnil,
	    Qg2int_jis_x_0208,Qnil,Qnil,Qg2int_japanese,Qnil);
    Qg2int_jis_gensym_string_with_crlf = 
	    STATIC_SYMBOL("JIS-GENSYM-STRING-WITH-CRLF",AB_package);
    Qg2int_crlf = STATIC_SYMBOL("CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_jis_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_jis_x_0208,Qnil,Qg2int_crlf,Qg2int_japanese,
	    Qg2int_gensym_string);
    Qg2int_jis_euc_string = STATIC_SYMBOL("JIS-EUC-STRING",AB_package);
    Qg2int_jis_x_0208_euc = STATIC_SYMBOL("JIS-X-0208-EUC",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_jis_euc_string,Qnil,Qnil,
	    Qg2int_jis_x_0208_euc,Qnil,Qnil,Qg2int_japanese,Qnil);
    Qg2int_jis_euc_gensym_string_with_crlf = 
	    STATIC_SYMBOL("JIS-EUC-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_jis_euc_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_jis_x_0208_euc,Qnil,Qg2int_crlf,
	    Qg2int_japanese,Qg2int_gensym_string);
    Qg2int_shift_jis_string = STATIC_SYMBOL("SHIFT-JIS-STRING",AB_package);
    Qg2int_shift_jis_x_0208 = STATIC_SYMBOL("SHIFT-JIS-X-0208",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_shift_jis_string,Qnil,Qnil,
	    Qg2int_shift_jis_x_0208,Qnil,Qnil,Qg2int_japanese,Qnil);
    Qg2int_shift_jis_gensym_string_with_crlf = 
	    STATIC_SYMBOL("SHIFT-JIS-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_shift_jis_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_shift_jis_x_0208,Qnil,Qg2int_crlf,
	    Qg2int_japanese,Qg2int_gensym_string);
    Qg2int_ks_string = STATIC_SYMBOL("KS-STRING",AB_package);
    Qg2int_ks_c_5601 = STATIC_SYMBOL("KS-C-5601",AB_package);
    Qg2int_korean = STATIC_SYMBOL("KOREAN",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_ks_string,Qnil,Qnil,
	    Qg2int_ks_c_5601,Qnil,Qnil,Qg2int_korean,Qnil);
    Qg2int_ks_gensym_string_with_crlf = 
	    STATIC_SYMBOL("KS-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_ks_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_ks_c_5601,Qnil,Qg2int_crlf,Qg2int_korean,
	    Qg2int_gensym_string);
    Qg2int_ks_euc_string = STATIC_SYMBOL("KS-EUC-STRING",AB_package);
    Qg2int_ks_c_5601_euc = STATIC_SYMBOL("KS-C-5601-EUC",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_ks_euc_string,Qnil,Qnil,
	    Qg2int_ks_c_5601_euc,Qnil,Qnil,Qg2int_korean,Qnil);
    Qg2int_ks_euc_gensym_string_with_crlf = 
	    STATIC_SYMBOL("KS-EUC-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_ks_euc_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_ks_c_5601_euc,Qnil,Qg2int_crlf,Qg2int_korean,
	    Qg2int_gensym_string);
    Qg2int_gb_2312_string = STATIC_SYMBOL("GB-2312-STRING",AB_package);
    Qg2int_gb_2312 = STATIC_SYMBOL("GB-2312",AB_package);
    Qg2int_chinese = STATIC_SYMBOL("CHINESE",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_gb_2312_string,Qnil,Qnil,
	    Qg2int_gb_2312,Qnil,Qnil,Qg2int_chinese,Qnil);
    Qg2int_gb_2312_gensym_string_with_crlf = 
	    STATIC_SYMBOL("GB-2312-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_gb_2312_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_gb_2312,Qnil,Qg2int_crlf,Qg2int_chinese,
	    Qg2int_gensym_string);
    Qg2int_gb_2312_euc_string = STATIC_SYMBOL("GB-2312-EUC-STRING",AB_package);
    Qg2int_gb_2312_euc = STATIC_SYMBOL("GB-2312-EUC",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_gb_2312_euc_string,Qnil,
	    Qnil,Qg2int_gb_2312_euc,Qnil,Qnil,Qg2int_chinese,Qnil);
    Qg2int_gb_2312_euc_gensym_string_with_crlf = 
	    STATIC_SYMBOL("GB-2312-EUC-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_gb_2312_euc_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_gb_2312_euc,Qnil,Qg2int_crlf,Qg2int_chinese,
	    Qg2int_gensym_string);
    Qg2int_x_compound_text_string = STATIC_SYMBOL("X-COMPOUND-TEXT-STRING",
	    AB_package);
    Qg2int_x_compound_text = STATIC_SYMBOL("X-COMPOUND-TEXT",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_x_compound_text_string,
	    Qnil,Qnil,Qg2int_x_compound_text,Qnil,Qg2int_lf,
	    Qg2int_japanese,Qg2int_gensym_string);
    Qg2int_x_string = STATIC_SYMBOL("X-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_x_string,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qg2int_lf,Qnil,Qg2int_gensym_string);
    Qg2int_cf_text = STATIC_SYMBOL("CF-TEXT",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_cf_text,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qg2int_crlf,Qnil,Qg2int_gensym_string);
    Qg2int_cf_unicode_text = STATIC_SYMBOL("CF-UNICODE-TEXT",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_cf_unicode_text,Qnil,Qnil,
	    Qg2int_unicode,Qnil,Qg2int_crlf,Qnil,Qnil);
    Qg2int_utf_g_string = STATIC_SYMBOL("UTF-G-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_g_string,Qnil,Qnil,
	    Qg2int_utf_g,Qnil,Qnil,Qnil,Qnil);
    Qg2int_utf_g_ascii_as_much_as_possible_string = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-STRING",AB_package);
    Qg2int_utf_g_ascii_as_much_as_possible = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_g_ascii_as_much_as_possible_string,
	    Qnil,Qnil,Qg2int_utf_g_ascii_as_much_as_possible,Qnil,Qnil,
	    Qnil,Qnil);
    if (G2int_default_text_conversion_style == UNBOUND)
	G2int_default_text_conversion_style = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_utf_g_string),
		Qg2int_text_conversion_style_for_purpose);
    if (G2int_utf_g_ascii_as_much_as_possible_conversion_style == UNBOUND)
	G2int_utf_g_ascii_as_much_as_possible_conversion_style = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_utf_g_ascii_as_much_as_possible_string),
		Qg2int_text_conversion_style_for_purpose);
    g2int_install_text_transcode_purpose(Qg2int_unicode,Qnil,Qnil,
	    Qg2int_unicode,Qnil,Qnil,Qnil,Qnil);
    Qg2int_known_iso_latin1_to_iso_latin1 = 
	    STATIC_SYMBOL("KNOWN-ISO-LATIN1-TO-ISO-LATIN1",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_known_iso_latin1_to_iso_latin1,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_known_ascii_to_ascii = STATIC_SYMBOL("KNOWN-ASCII-TO-ASCII",
	    AB_package);
    Qg2int_us_ascii = STATIC_SYMBOL("US-ASCII",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_known_ascii_to_ascii,Qnil,
	    Qnil,Qg2int_us_ascii,Qnil,Qnil,Qnil,Qnil);
    Qg2int_us_ascii_gensym_string_with_crlf = 
	    STATIC_SYMBOL("US-ASCII-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_us_ascii_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_us_ascii,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    g2int_install_text_transcode_purpose(Qg2int_g2_directory_pathname,Qnil,
	    Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    g2int_install_text_transcode_purpose(Qg2int_gensym_pathname_namestring,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_pformat = STATIC_SYMBOL("PFORMAT",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_pformat,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_instantiate_file_template_for_printing = 
	    STATIC_SYMBOL("INSTANTIATE-FILE-TEMPLATE-FOR-PRINTING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_instantiate_file_template_for_printing,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_notify_user_if_possible_via_console = 
	    STATIC_SYMBOL("NOTIFY-USER-IF-POSSIBLE-VIA-CONSOLE",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_notify_user_if_possible_via_console,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_kb_error = STATIC_SYMBOL("KB-ERROR",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_kb_error,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_icp_filtered_text_string_reader = 
	    STATIC_SYMBOL("ICP-FILTERED-TEXT-STRING-READER",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_icp_filtered_text_string_reader,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_latin1_gensym_string = 
	    STATIC_SYMBOL("ISO-LATIN1-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_latin1_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_idl_source_file_pathname = 
	    STATIC_SYMBOL("IDL-SOURCE-FILE-PATHNAME",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_idl_source_file_pathname,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    g2int_install_text_transcode_purpose(Qg2int_filter_text_for_gsi,Qnil,
	    Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_1_wide_string = STATIC_SYMBOL("ISO-8859-1-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_1_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_1_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-1-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_1_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_1_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-1-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_1_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_1,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_ascii = STATIC_SYMBOL("ASCII",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_ascii,Qnil,Qnil,
	    Qg2int_iso_8859_1,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_2_wide_string = STATIC_SYMBOL("ISO-8859-2-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_2_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_2,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_2_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-2-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_2_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_2,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_2_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-2-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_2_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_2,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_iso_8859_3_wide_string = STATIC_SYMBOL("ISO-8859-3-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_3_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_3,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_3_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-3-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_3_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_3,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_3_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-3-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_3_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_3,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_iso_8859_4_wide_string = STATIC_SYMBOL("ISO-8859-4-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_4_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_4,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_4_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-4-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_4_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_4,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_4_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-4-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_4_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_4,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_iso_8859_5_wide_string = STATIC_SYMBOL("ISO-8859-5-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_5_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_5,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_5_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-5-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_5_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_5,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_5_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-5-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_5_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_5,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_iso_8859_6_wide_string = STATIC_SYMBOL("ISO-8859-6-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_6_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_6,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_6_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-6-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_6_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_6,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_6_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-6-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_6_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_6,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_iso_8859_7_wide_string = STATIC_SYMBOL("ISO-8859-7-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_7_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_7,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_7_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-7-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_7_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_7,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_7_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-7-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_7_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_7,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_iso_8859_8_wide_string = STATIC_SYMBOL("ISO-8859-8-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_8_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_8,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_8_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-8-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_8_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_8,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_8_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-8-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_8_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_8,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_iso_8859_9_wide_string = STATIC_SYMBOL("ISO-8859-9-WIDE-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_9_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_9,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_9_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-9-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_9_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_9,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_9_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-9-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_9_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_9,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_iso_8859_10_wide_string = 
	    STATIC_SYMBOL("ISO-8859-10-WIDE-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_10_wide_string,
	    Qnil,Qnil,Qg2int_iso_8859_10,Qnil,Qnil,Qnil,Qnil);
    Qg2int_iso_8859_10_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-10-GENSYM-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_10_gensym_string,
	    Qnil,Qnil,Qg2int_iso_8859_10,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_iso_8859_10_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-10-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_iso_8859_10_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_iso_8859_10,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_utf_7_wide_string = STATIC_SYMBOL("UTF-7-WIDE-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_7_wide_string,Qnil,
	    Qnil,Qg2int_unicode_utf_7,Qnil,Qnil,Qnil,Qnil);
    Qg2int_utf_7_gensym_string = STATIC_SYMBOL("UTF-7-GENSYM-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_7_gensym_string,Qnil,
	    Qnil,Qg2int_unicode_utf_7,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_utf_8_wide_string = STATIC_SYMBOL("UTF-8-WIDE-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_8_wide_string,Qnil,
	    Qnil,Qg2int_unicode_utf_8,Qnil,Qnil,Qnil,Qnil);
    Qg2int_utf_8_gensym_string = STATIC_SYMBOL("UTF-8-GENSYM-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_8_gensym_string,Qnil,
	    Qnil,Qg2int_unicode_utf_8,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2int_utf_8_gensym_string_with_newline = 
	    STATIC_SYMBOL("UTF-8-GENSYM-STRING-WITH-NEWLINE",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_8_gensym_string_with_newline,
	    Qnil,Qnil,Qg2int_unicode_utf_8,Qnil,Qg2int_lf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_utf_8_gensym_string_with_crlf = 
	    STATIC_SYMBOL("UTF-8-GENSYM-STRING-WITH-CRLF",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_8_gensym_string_with_crlf,
	    Qnil,Qnil,Qg2int_unicode_utf_8,Qnil,Qg2int_crlf,Qnil,
	    Qg2int_gensym_string);
    Qg2int_utf_g_wide_string = STATIC_SYMBOL("UTF-G-WIDE-STRING",AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_g_wide_string,Qnil,
	    Qnil,Qg2int_utf_g,Qnil,Qnil,Qnil,Qnil);
    Qg2int_utf_g_gensym_string = STATIC_SYMBOL("UTF-G-GENSYM-STRING",
	    AB_package);
    g2int_install_text_transcode_purpose(Qg2int_utf_g_gensym_string,Qnil,
	    Qnil,Qg2int_utf_g,Qnil,Qnil,Qnil,Qg2int_gensym_string);
    Qg2_defstruct_structure_name_text_sequence_g2_struct = 
	    STATIC_SYMBOL("TEXT-SEQUENCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_text_sequence = STATIC_SYMBOL("TEXT-SEQUENCE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_text_sequence_g2_struct,
	    Qg2int_text_sequence,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_text_sequence,
	    Qg2_defstruct_structure_name_text_sequence_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_text_sequence == UNBOUND)
	G2int_the_type_description_of_text_sequence = Nil;
    string_constant_1 = 
	    STATIC_STRING("43Dy8l83Gy1n83Gy8m8k1l8m0000001m1n8n83=+y01m8p83=lyksk0k0");
    temp = G2int_the_type_description_of_text_sequence;
    G2int_the_type_description_of_text_sequence = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_1));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_text_sequence_g2_struct,
	    G2int_the_type_description_of_text_sequence,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_text_sequence,
	    G2int_the_type_description_of_text_sequence,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_text_sequences = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TEXT-SEQUENCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_text_sequences,
	    G2int_chain_of_available_text_sequences);
    g2int_record_system_variable(Qg2int_chain_of_available_text_sequences,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_text_sequence_count = STATIC_SYMBOL("TEXT-SEQUENCE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_text_sequence_count,
	    G2int_text_sequence_count);
    g2int_record_system_variable(Qg2int_text_sequence_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_text_sequence = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_text_sequence,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_text_sequence,reclaim_structure_for_text_sequence);
    Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct = 
	    STATIC_SYMBOL("GENSYM-STRING-TEXT-SEQUENCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gensym_string_text_sequence = 
	    STATIC_SYMBOL("GENSYM-STRING-TEXT-SEQUENCE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct,
	    Qg2int_gensym_string_text_sequence,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gensym_string_text_sequence,
	    Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gensym_string_text_sequence == UNBOUND)
	G2int_the_type_description_of_gensym_string_text_sequence = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8l83-=y1o83-=y83Gy8m8k1l83Gy0000001l1n8o83Gy1m83Ky1m9k83--yksk0k0");
    temp = G2int_the_type_description_of_gensym_string_text_sequence;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_gensym_string_text_sequence = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_2));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct,
	    G2int_the_type_description_of_gensym_string_text_sequence,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gensym_string_text_sequence,
	    G2int_the_type_description_of_gensym_string_text_sequence,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gensym_string_text_sequences = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GENSYM-STRING-TEXT-SEQUENCES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gensym_string_text_sequences,
	    G2int_chain_of_available_gensym_string_text_sequences);
    g2int_record_system_variable(Qg2int_chain_of_available_gensym_string_text_sequences,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gensym_string_text_sequence_count = 
	    STATIC_SYMBOL("GENSYM-STRING-TEXT-SEQUENCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gensym_string_text_sequence_count,
	    G2int_gensym_string_text_sequence_count);
    g2int_record_system_variable(Qg2int_gensym_string_text_sequence_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gensym_string_text_sequence = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gensym_string_text_sequence,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gensym_string_text_sequence,
	    reclaim_structure_for_gensym_string_text_sequence);
    Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct = 
	    STATIC_SYMBOL("WIDE-STRING-TEXT-SEQUENCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_wide_string_text_sequence = 
	    STATIC_SYMBOL("WIDE-STRING-TEXT-SEQUENCE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct,
	    Qg2int_wide_string_text_sequence,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_wide_string_text_sequence,
	    Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_wide_string_text_sequence == UNBOUND)
	G2int_the_type_description_of_wide_string_text_sequence = Nil;
    string_constant_3 = 
	    STATIC_STRING("43Dy8l830Jy1o830Jy83Gy8m8k1l83Gy0000001l1n8o83Gy1m83Ky1m9k830Iyksk0k0");
    temp = G2int_the_type_description_of_wide_string_text_sequence;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_wide_string_text_sequence = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_3));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct,
	    G2int_the_type_description_of_wide_string_text_sequence,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_wide_string_text_sequence,
	    G2int_the_type_description_of_wide_string_text_sequence,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_wide_string_text_sequences = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WIDE-STRING-TEXT-SEQUENCES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_wide_string_text_sequences,
	    G2int_chain_of_available_wide_string_text_sequences);
    g2int_record_system_variable(Qg2int_chain_of_available_wide_string_text_sequences,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_wide_string_text_sequence_count = 
	    STATIC_SYMBOL("WIDE-STRING-TEXT-SEQUENCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_wide_string_text_sequence_count,
	    G2int_wide_string_text_sequence_count);
    g2int_record_system_variable(Qg2int_wide_string_text_sequence_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_wide_string_text_sequence = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_wide_string_text_sequence,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_wide_string_text_sequence,
	    reclaim_structure_for_wide_string_text_sequence);
    Qg2int_initialize_text_sequence_string = 
	    STATIC_SYMBOL("INITIALIZE-TEXT-SEQUENCE-STRING",AB_package);
    initialize_text_sequence_string_for_text_sequence = 
	    STATIC_FUNCTION(g2int_initialize_text_sequence_string_for_text_sequence,
	    NIL,FALSE,4,4);
    g2int_record_direct_structure_method(Qg2int_initialize_text_sequence_string,
	    Qg2int_text_sequence,
	    initialize_text_sequence_string_for_text_sequence);
    initialize_text_sequence_string_for_gensym_string_text_sequence = 
	    STATIC_FUNCTION(g2int_initialize_text_sequence_string_for_gensym_string_text_sequence,
	    NIL,FALSE,4,4);
    g2int_record_direct_structure_method(Qg2int_initialize_text_sequence_string,
	    Qg2int_gensym_string_text_sequence,
	    initialize_text_sequence_string_for_gensym_string_text_sequence);
    initialize_text_sequence_string_for_wide_string_text_sequence = 
	    STATIC_FUNCTION(g2int_initialize_text_sequence_string_for_wide_string_text_sequence,
	    NIL,FALSE,4,4);
    g2int_record_direct_structure_method(Qg2int_initialize_text_sequence_string,
	    Qg2int_wide_string_text_sequence,
	    initialize_text_sequence_string_for_wide_string_text_sequence);
    Qg2int_read_character_from_text_sequence = 
	    STATIC_SYMBOL("READ-CHARACTER-FROM-TEXT-SEQUENCE",AB_package);
    read_character_from_text_sequence_for_gensym_string_text_sequence = 
	    STATIC_FUNCTION(g2int_read_character_from_text_sequence_for_gensym_string_text_sequence,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_read_character_from_text_sequence,
	    Qg2int_gensym_string_text_sequence,
	    read_character_from_text_sequence_for_gensym_string_text_sequence);
    read_character_from_text_sequence_for_wide_string_text_sequence = 
	    STATIC_FUNCTION(g2int_read_character_from_text_sequence_for_wide_string_text_sequence,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_read_character_from_text_sequence,
	    Qg2int_wide_string_text_sequence,
	    read_character_from_text_sequence_for_wide_string_text_sequence);
    Qg2_defstruct_structure_name_transcoder_g2_struct = 
	    STATIC_SYMBOL("TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_transcoder = STATIC_SYMBOL("TRANSCODER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_transcoder_g2_struct,
	    Qg2int_transcoder,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_transcoder,
	    Qg2_defstruct_structure_name_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_transcoder == UNBOUND)
	G2int_the_type_description_of_transcoder = Nil;
    string_constant_4 = STATIC_STRING("43Dy8l8x1n8x8m8k1l8m0000000kqk0k0");
    temp = G2int_the_type_description_of_transcoder;
    G2int_the_type_description_of_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_4));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_transcoder_g2_struct,
	    G2int_the_type_description_of_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_transcoder,
	    G2int_the_type_description_of_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_transcoders,
	    G2int_chain_of_available_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_transcoder_count = STATIC_SYMBOL("TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_transcoder_count,G2int_transcoder_count);
    g2int_record_system_variable(Qg2int_transcoder_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_transcoder,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_transcoder,reclaim_structure_for_transcoder);
    Qg2int_transcode_character = STATIC_SYMBOL("TRANSCODE-CHARACTER",
	    AB_package);
    transcode_character_for_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_transcoder,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_transcoder,transcode_character_for_transcoder);
    Qg2int_export_character = STATIC_SYMBOL("EXPORT-CHARACTER",AB_package);
    export_character_for_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_transcoder,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_transcoder,export_character_for_transcoder);
    Qg2int_transcode_as_text_string = 
	    STATIC_SYMBOL("TRANSCODE-AS-TEXT-STRING",AB_package);
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    transcode_as_text_string_for_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_as_text_string_for_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_as_text_string,
	    Qg2int_transcoder,transcode_as_text_string_for_transcoder);
    Qg2int_twrite_unicode_from_transcoder = 
	    STATIC_SYMBOL("TWRITE-UNICODE-FROM-TRANSCODER",AB_package);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    twrite_unicode_from_transcoder_for_transcoder = 
	    STATIC_FUNCTION(g2int_twrite_unicode_from_transcoder_for_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_twrite_unicode_from_transcoder,
	    Qg2int_transcoder,twrite_unicode_from_transcoder_for_transcoder);
    Qg2int_export_as_string = STATIC_SYMBOL("EXPORT-AS-STRING",AB_package);
    export_as_string_for_transcoder = 
	    STATIC_FUNCTION(g2int_export_as_string_for_transcoder,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_as_string,
	    Qg2int_transcoder,export_as_string_for_transcoder);
    Qg2int_twrite_for_export_from_transcoder = 
	    STATIC_SYMBOL("TWRITE-FOR-EXPORT-FROM-TRANSCODER",AB_package);
    twrite_for_export_from_transcoder_for_transcoder = 
	    STATIC_FUNCTION(g2int_twrite_for_export_from_transcoder_for_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_twrite_for_export_from_transcoder,
	    Qg2int_transcoder,
	    twrite_for_export_from_transcoder_for_transcoder);
    Qg2_defstruct_structure_name_graphic_character_set_g2_struct = 
	    STATIC_SYMBOL("GRAPHIC-CHARACTER-SET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_graphic_character_set = STATIC_SYMBOL("GRAPHIC-CHARACTER-SET",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_graphic_character_set_g2_struct,
	    Qg2int_graphic_character_set,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_graphic_character_set,
	    Qg2_defstruct_structure_name_graphic_character_set_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_graphic_character_set == UNBOUND)
	G2int_the_type_description_of_graphic_character_set = Nil;
    string_constant_5 = STATIC_STRING("43Dy8l8q1n8q8m8k1l8m0000000krk0k0");
    temp = G2int_the_type_description_of_graphic_character_set;
    G2int_the_type_description_of_graphic_character_set = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_5));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_graphic_character_set_g2_struct,
	    G2int_the_type_description_of_graphic_character_set,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_graphic_character_set,
	    G2int_the_type_description_of_graphic_character_set,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_graphic_character_sets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GRAPHIC-CHARACTER-SETS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_graphic_character_sets,
	    G2int_chain_of_available_graphic_character_sets);
    g2int_record_system_variable(Qg2int_chain_of_available_graphic_character_sets,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_graphic_character_set_count = 
	    STATIC_SYMBOL("GRAPHIC-CHARACTER-SET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_graphic_character_set_count,
	    G2int_graphic_character_set_count);
    g2int_record_system_variable(Qg2int_graphic_character_set_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_graphic_character_set = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_graphic_character_set,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_graphic_character_set,
	    reclaim_structure_for_graphic_character_set);
    Qg2int_iso_646 = STATIC_SYMBOL("ISO-646",AB_package);
    Qg2int_iso_646_irv = STATIC_SYMBOL("ISO-646-IRV",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qg2int_iso_646_irv,
	    Qg2int_ascii,Qg2int_us_ascii);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    G2int_graphic_character_set_prop = Qg2int_graphic_character_set;
    Qg2int_transcoder_creation_function = 
	    STATIC_SYMBOL("TRANSCODER-CREATION-FUNCTION",AB_package);
    G2int_transcoder_creation_function_prop = 
	    Qg2int_transcoder_creation_function;
    Qg2_defstruct_structure_name_iso_646_g2_struct = 
	    STATIC_SYMBOL("ISO-646-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_646_g2_struct,
	    Qg2int_iso_646,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_646,
	    Qg2_defstruct_structure_name_iso_646_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_646 == UNBOUND)
	G2int_the_type_description_of_iso_646 = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8l83-ry1o83-ry8q8m8k1l8q0000001l1r8o8q1m8t1m9k83-ry1m8v1m9k1o83-sy83Oy8309y83Ny1m8s1m9kl1m8r1m9k3-Qy1m8u1m9k+s3-*ykkkkkl3A++");
    string_constant_7 = STATIC_STRING("ykrk0k0");
    temp = G2int_the_type_description_of_iso_646;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_646 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_6,
	    string_constant_7)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_646_g2_struct,
	    G2int_the_type_description_of_iso_646,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_646,
	    G2int_the_type_description_of_iso_646,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_646s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-646S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_646s,
	    G2int_chain_of_available_iso_646s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_646s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_646_count = STATIC_SYMBOL("ISO-646-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_646_count,G2int_iso_646_count);
    g2int_record_system_variable(Qg2int_iso_646_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_646 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_646,NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_646,reclaim_structure_for_iso_646);
    Qg2int_ansi3dot4 = STATIC_SYMBOL("ANSI3.4",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qg2int_iso_646_irv,
	    Qg2int_ascii,Qg2int_us_ascii,Qg2int_ansi3dot4);
    array_constant_1 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    g2int_mutate_global_property(Qg2int_iso_646,g2int_make_iso_646_1(),
	    Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop;
  end_loop:;
    Qg2int_map_code_to_unicode = STATIC_SYMBOL("MAP-CODE-TO-UNICODE",
	    AB_package);
    map_code_to_unicode_for_iso_646 = 
	    STATIC_FUNCTION(g2int_map_code_to_unicode_for_iso_646,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_code_to_unicode,
	    Qg2int_iso_646,map_code_to_unicode_for_iso_646);
    Qg2int_map_unicode_to_code_if_any = 
	    STATIC_SYMBOL("MAP-UNICODE-TO-CODE-IF-ANY",AB_package);
    map_unicode_to_code_if_any_for_iso_646 = 
	    STATIC_FUNCTION(g2int_map_unicode_to_code_if_any_for_iso_646,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_unicode_to_code_if_any,
	    Qg2int_iso_646,map_unicode_to_code_if_any_for_iso_646);
    Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-ABSTRACT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_iso_8859_abstract = STATIC_SYMBOL("ISO-8859-ABSTRACT",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct,
	    Qg2int_iso_8859_abstract,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_abstract,
	    Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_abstract == UNBOUND)
	G2int_the_type_description_of_iso_8859_abstract = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8l8w1o8w8q8m8k1l8q0000001l1r8o8q1m8t1m9k8w1m8v1m9k01m8s1m9kl1m8r1m9k3-Sy1m8u1m9k0kuk0k0");
    temp = G2int_the_type_description_of_iso_8859_abstract;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_abstract = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_8));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct,
	    G2int_the_type_description_of_iso_8859_abstract,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_abstract,
	    G2int_the_type_description_of_iso_8859_abstract,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_abstracts = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-ABSTRACTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_abstracts,
	    G2int_chain_of_available_iso_8859_abstracts);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_abstracts,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_abstract_count = 
	    STATIC_SYMBOL("ISO-8859-ABSTRACT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_abstract_count,
	    G2int_iso_8859_abstract_count);
    g2int_record_system_variable(Qg2int_iso_8859_abstract_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_abstract = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_abstract,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_abstract,reclaim_structure_for_iso_8859_abstract);
    g2int_mutate_global_property(Qg2int_iso_8859_abstract,
	    g2int_make_iso_8859_abstract_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = Qnil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_abstract),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_1;
  end_loop_1:;
    map_code_to_unicode_for_iso_8859_abstract = 
	    STATIC_FUNCTION(g2int_map_code_to_unicode_for_iso_8859_abstract,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_code_to_unicode,
	    Qg2int_iso_8859_abstract,
	    map_code_to_unicode_for_iso_8859_abstract);
    Qg2int_available_8859_reverse_unicode_map_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_available_8859_reverse_unicode_map_hash_vector_43_vectors,
	    G2int_available_8859_reverse_unicode_map_hash_vector_43_vectors);
    g2int_record_system_variable(Qg2int_available_8859_reverse_unicode_map_hash_vector_43_vectors,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors,
	    G2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors);
    g2int_record_system_variable(Qg2int_count_of_8859_reverse_unicode_map_hash_vector_43_vectors,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_8859_reverse_unicode_map_tree_for_hash = 
	    STATIC_SYMBOL("8859-REVERSE-UNICODE-MAP-TREE-FOR-HASH",AB_package);
    map_unicode_to_code_if_any_for_iso_8859_abstract = 
	    STATIC_FUNCTION(g2int_map_unicode_to_code_if_any_for_iso_8859_abstract,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_unicode_to_code_if_any,
	    Qg2int_iso_8859_abstract,
	    map_unicode_to_code_if_any_for_iso_8859_abstract);
    Qg2_defstruct_structure_name_iso_8859_1_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-1-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_1_g2_struct,
	    Qg2int_iso_8859_1,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_1,
	    Qg2_defstruct_structure_name_iso_8859_1_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_1 == UNBOUND)
	G2int_the_type_description_of_iso_8859_1 = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8l83-ty1p83-ty8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83-ty1m8v1m9k1l83*Ey1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3--ykkkkkl3A++y1m8ylkuk0k");
    string_constant_10 = STATIC_STRING("0");
    temp = G2int_the_type_description_of_iso_8859_1;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_1 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_9,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_1_g2_struct,
	    G2int_the_type_description_of_iso_8859_1,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_1,
	    G2int_the_type_description_of_iso_8859_1,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_1s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-1S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_1s,
	    G2int_chain_of_available_iso_8859_1s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_1s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_1_count = STATIC_SYMBOL("ISO-8859-1-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_1_count,G2int_iso_8859_1_count);
    g2int_record_system_variable(Qg2int_iso_8859_1_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_1 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_1,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_1,reclaim_structure_for_iso_8859_1);
    Qg2int_latin_1 = STATIC_SYMBOL("LATIN-1",AB_package);
    list_constant_2 = STATIC_CONS(Qg2int_latin_1,Qnil);
    g2int_mutate_global_property(Qg2int_iso_8859_1,
	    g2int_make_iso_8859_1_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_2;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_1),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_2;
  end_loop_2:;
    Qg2_defstruct_structure_name_iso_8859_2_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-2-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_2_g2_struct,
	    Qg2int_iso_8859_2,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_2,
	    Qg2_defstruct_structure_name_iso_8859_2_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_2 == UNBOUND)
	G2int_the_type_description_of_iso_8859_2 = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8l83-vy1p83-vy8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83-vy1m8v1m9k1l83*Fy1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-*ykkkkkl3A++y1m8ymkuk0k");
    temp = G2int_the_type_description_of_iso_8859_2;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_2 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_11,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_2_g2_struct,
	    G2int_the_type_description_of_iso_8859_2,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_2,
	    G2int_the_type_description_of_iso_8859_2,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_2s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-2S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_2s,
	    G2int_chain_of_available_iso_8859_2s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_2s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_2_count = STATIC_SYMBOL("ISO-8859-2-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_2_count,G2int_iso_8859_2_count);
    g2int_record_system_variable(Qg2int_iso_8859_2_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_2 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_2,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_2,reclaim_structure_for_iso_8859_2);
    Qg2int_latin_2 = STATIC_SYMBOL("LATIN-2",AB_package);
    list_constant_3 = STATIC_CONS(Qg2int_latin_2,Qnil);
    g2int_mutate_global_property(Qg2int_iso_8859_2,
	    g2int_make_iso_8859_2_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_3;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_2),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_3;
  end_loop_3:;
    Qg2_defstruct_structure_name_iso_8859_3_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-3-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_3_g2_struct,
	    Qg2int_iso_8859_3,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_3,
	    Qg2_defstruct_structure_name_iso_8859_3_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_3 == UNBOUND)
	G2int_the_type_description_of_iso_8859_3 = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8l83-wy1p83-wy8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83-wy1m8v1m9k1l83*Gy1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-=ykkkkkl3A++y1m8ynkuk0k");
    temp = G2int_the_type_description_of_iso_8859_3;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_3 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_12,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_3_g2_struct,
	    G2int_the_type_description_of_iso_8859_3,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_3,
	    G2int_the_type_description_of_iso_8859_3,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_3s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-3S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_3s,
	    G2int_chain_of_available_iso_8859_3s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_3s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_3_count = STATIC_SYMBOL("ISO-8859-3-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_3_count,G2int_iso_8859_3_count);
    g2int_record_system_variable(Qg2int_iso_8859_3_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_3 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_3,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_3,reclaim_structure_for_iso_8859_3);
    Qg2int_latin_3 = STATIC_SYMBOL("LATIN-3",AB_package);
    list_constant_4 = STATIC_CONS(Qg2int_latin_3,Qnil);
    array_constant_2 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    g2int_mutate_global_property(Qg2int_iso_8859_3,
	    g2int_make_iso_8859_3_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_4;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_3),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_4;
  end_loop_4:;
    Qg2_defstruct_structure_name_iso_8859_4_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-4-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_4_g2_struct,
	    Qg2int_iso_8859_4,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_4,
	    Qg2_defstruct_structure_name_iso_8859_4_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_4 == UNBOUND)
	G2int_the_type_description_of_iso_8859_4 = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8l83-xy1p83-xy8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83-xy1m8v1m9k1l83*Hy1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-0ykkkkkl3A++y1m8yokuk0k");
    temp = G2int_the_type_description_of_iso_8859_4;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_4 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_13,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_4_g2_struct,
	    G2int_the_type_description_of_iso_8859_4,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_4,
	    G2int_the_type_description_of_iso_8859_4,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_4s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-4S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_4s,
	    G2int_chain_of_available_iso_8859_4s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_4s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_4_count = STATIC_SYMBOL("ISO-8859-4-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_4_count,G2int_iso_8859_4_count);
    g2int_record_system_variable(Qg2int_iso_8859_4_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_4 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_4,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_4,reclaim_structure_for_iso_8859_4);
    Qg2int_latin_4 = STATIC_SYMBOL("LATIN-4",AB_package);
    list_constant_5 = STATIC_CONS(Qg2int_latin_4,Qnil);
    array_constant_3 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    g2int_mutate_global_property(Qg2int_iso_8859_4,
	    g2int_make_iso_8859_4_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_5;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_4),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_5;
  end_loop_5:;
    Qg2_defstruct_structure_name_iso_8859_5_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-5-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_5_g2_struct,
	    Qg2int_iso_8859_5,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_5,
	    Qg2_defstruct_structure_name_iso_8859_5_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_5 == UNBOUND)
	G2int_the_type_description_of_iso_8859_5 = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8l83*+y1p83*+y8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83*+y1m8v1m9k1l83*Ly1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-8ykkkkkl3A++y1m8ypkuk0k");
    temp = G2int_the_type_description_of_iso_8859_5;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_5 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_14,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_5_g2_struct,
	    G2int_the_type_description_of_iso_8859_5,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_5,
	    G2int_the_type_description_of_iso_8859_5,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_5s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-5S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_5s,
	    G2int_chain_of_available_iso_8859_5s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_5s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_5_count = STATIC_SYMBOL("ISO-8859-5-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_5_count,G2int_iso_8859_5_count);
    g2int_record_system_variable(Qg2int_iso_8859_5_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_5 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_5,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_5,reclaim_structure_for_iso_8859_5);
    Qg2int_latin_cyrillic = STATIC_SYMBOL("LATIN-CYRILLIC",AB_package);
    list_constant_6 = STATIC_CONS(Qg2int_latin_cyrillic,Qnil);
    array_constant_4 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    g2int_mutate_global_property(Qg2int_iso_8859_5,
	    g2int_make_iso_8859_5_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_6;
  next_loop_6:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_6;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_5),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_6;
  end_loop_6:;
    Qg2_defstruct_structure_name_iso_8859_6_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-6-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_6_g2_struct,
	    Qg2int_iso_8859_6,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_6,
	    Qg2_defstruct_structure_name_iso_8859_6_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_6 == UNBOUND)
	G2int_the_type_description_of_iso_8859_6 = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8l83*-y1p83*-y8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83*-y1m8v1m9k1l83*Ky1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-3ykkkkkl3A++y1m8yqkuk0k");
    temp = G2int_the_type_description_of_iso_8859_6;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_6 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_15,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_6_g2_struct,
	    G2int_the_type_description_of_iso_8859_6,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_6,
	    G2int_the_type_description_of_iso_8859_6,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_6s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-6S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_6s,
	    G2int_chain_of_available_iso_8859_6s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_6s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_6_count = STATIC_SYMBOL("ISO-8859-6-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_6_count,G2int_iso_8859_6_count);
    g2int_record_system_variable(Qg2int_iso_8859_6_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_6 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_6,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_6,reclaim_structure_for_iso_8859_6);
    Qg2int_latin_arabic = STATIC_SYMBOL("LATIN-ARABIC",AB_package);
    list_constant_7 = STATIC_CONS(Qg2int_latin_arabic,Qnil);
    array_constant_5 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    g2int_mutate_global_property(Qg2int_iso_8859_6,
	    g2int_make_iso_8859_6_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_7;
  next_loop_7:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_7;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_6),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_7;
  end_loop_7:;
    Qg2_defstruct_structure_name_iso_8859_7_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-7-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_7_g2_struct,
	    Qg2int_iso_8859_7,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_7,
	    Qg2_defstruct_structure_name_iso_8859_7_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_7 == UNBOUND)
	G2int_the_type_description_of_iso_8859_7 = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8l83**y1p83**y8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83**y1m8v1m9k1l83*My1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-2ykkkkkl3A++y1m8yrkuk0k");
    temp = G2int_the_type_description_of_iso_8859_7;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_7 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_16,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_7_g2_struct,
	    G2int_the_type_description_of_iso_8859_7,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_7,
	    G2int_the_type_description_of_iso_8859_7,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_7s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-7S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_7s,
	    G2int_chain_of_available_iso_8859_7s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_7s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_7_count = STATIC_SYMBOL("ISO-8859-7-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_7_count,G2int_iso_8859_7_count);
    g2int_record_system_variable(Qg2int_iso_8859_7_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_7 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_7,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_7,reclaim_structure_for_iso_8859_7);
    Qg2int_latin_greek = STATIC_SYMBOL("LATIN-GREEK",AB_package);
    list_constant_8 = STATIC_CONS(Qg2int_latin_greek,Qnil);
    array_constant_6 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    g2int_mutate_global_property(Qg2int_iso_8859_7,
	    g2int_make_iso_8859_7_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_8;
  next_loop_8:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_8;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_7),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_8;
  end_loop_8:;
    Qg2_defstruct_structure_name_iso_8859_8_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-8-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_8_g2_struct,
	    Qg2int_iso_8859_8,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_8,
	    Qg2_defstruct_structure_name_iso_8859_8_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_8 == UNBOUND)
	G2int_the_type_description_of_iso_8859_8 = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8l83*=y1p83*=y8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83*=y1m8v1m9k1l83*Ny1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-4ykkkkkl3A++y1m8yskuk0k");
    temp = G2int_the_type_description_of_iso_8859_8;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_8 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_17,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_8_g2_struct,
	    G2int_the_type_description_of_iso_8859_8,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_8,
	    G2int_the_type_description_of_iso_8859_8,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_8s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-8S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_8s,
	    G2int_chain_of_available_iso_8859_8s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_8s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_8_count = STATIC_SYMBOL("ISO-8859-8-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_8_count,G2int_iso_8859_8_count);
    g2int_record_system_variable(Qg2int_iso_8859_8_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_8 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_8,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_8,reclaim_structure_for_iso_8859_8);
    Qg2int_latin_hebrew = STATIC_SYMBOL("LATIN-HEBREW",AB_package);
    list_constant_9 = STATIC_CONS(Qg2int_latin_hebrew,Qnil);
    array_constant_7 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    g2int_mutate_global_property(Qg2int_iso_8859_8,
	    g2int_make_iso_8859_8_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_9;
  next_loop_9:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_9;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_8),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_9;
  end_loop_9:;
    Qg2_defstruct_structure_name_iso_8859_9_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-9-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_9_g2_struct,
	    Qg2int_iso_8859_9,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_9,
	    Qg2_defstruct_structure_name_iso_8859_9_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_9 == UNBOUND)
	G2int_the_type_description_of_iso_8859_9 = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8l83*0y1p83*0y8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83*0y1m8v1m9k1l83*Iy1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-9ykkkkkl3A++y1m8ytkuk0k");
    temp = G2int_the_type_description_of_iso_8859_9;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_9 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_18,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_9_g2_struct,
	    G2int_the_type_description_of_iso_8859_9,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_9,
	    G2int_the_type_description_of_iso_8859_9,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_9s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-9S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_9s,
	    G2int_chain_of_available_iso_8859_9s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_9s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_9_count = STATIC_SYMBOL("ISO-8859-9-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_9_count,G2int_iso_8859_9_count);
    g2int_record_system_variable(Qg2int_iso_8859_9_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_9 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_9,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_9,reclaim_structure_for_iso_8859_9);
    Qg2int_latin_5 = STATIC_SYMBOL("LATIN-5",AB_package);
    list_constant_10 = STATIC_CONS(Qg2int_latin_5,Qnil);
    array_constant_8 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    g2int_mutate_global_property(Qg2int_iso_8859_9,
	    g2int_make_iso_8859_9_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_10;
  next_loop_10:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_10;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_9),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_10;
  end_loop_10:;
    Qg2_defstruct_structure_name_iso_8859_10_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-10-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_10_g2_struct,
	    Qg2int_iso_8859_10,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_10,
	    Qg2_defstruct_structure_name_iso_8859_10_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_10 == UNBOUND)
	G2int_the_type_description_of_iso_8859_10 = Nil;
    string_constant_19 = 
	    STATIC_STRING("43Dy8l83-uy1p83-uy8w8q8m8k1l8w0000001l1s8o8w1m8t1m9k83-uy1m8v1m9k1l83*Jy1m8s1m9kl1m8r1m9k3-Sy1m8u1m9k+s3-0ykkkkkl3A++y1m8yukuk0k");
    temp = G2int_the_type_description_of_iso_8859_10;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_iso_8859_10 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_19,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_10_g2_struct,
	    G2int_the_type_description_of_iso_8859_10,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_10,
	    G2int_the_type_description_of_iso_8859_10,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_10s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-10S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_10s,
	    G2int_chain_of_available_iso_8859_10s);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_10s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_10_count = STATIC_SYMBOL("ISO-8859-10-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_10_count,
	    G2int_iso_8859_10_count);
    g2int_record_system_variable(Qg2int_iso_8859_10_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_10 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_10,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_10,reclaim_structure_for_iso_8859_10);
    Qg2int_latin_6 = STATIC_SYMBOL("LATIN-6",AB_package);
    list_constant_11 = STATIC_CONS(Qg2int_latin_6,Qnil);
    g2int_mutate_global_property(Qg2int_iso_8859_10,
	    g2int_make_iso_8859_10_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_11;
  next_loop_11:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_11;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_10),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_11;
  end_loop_11:;
    Qg2_defstruct_structure_name_asian_double_byte_g2_struct = 
	    STATIC_SYMBOL("ASIAN-DOUBLE-BYTE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_asian_double_byte = STATIC_SYMBOL("ASIAN-DOUBLE-BYTE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_asian_double_byte_g2_struct,
	    Qg2int_asian_double_byte,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_asian_double_byte,
	    Qg2_defstruct_structure_name_asian_double_byte_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_asian_double_byte == UNBOUND)
	G2int_the_type_description_of_asian_double_byte = Nil;
    string_constant_20 = 
	    STATIC_STRING("43Dy8l8z1o8z8q8m8k1l8q0000001l1r8o8q1m8t1m9k8z1m8v1m9k01m8s1m9km1m8r1m9k3-Qy1m8u1m9k0ksk0k0");
    temp = G2int_the_type_description_of_asian_double_byte;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_asian_double_byte = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_20));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_asian_double_byte_g2_struct,
	    G2int_the_type_description_of_asian_double_byte,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_asian_double_byte,
	    G2int_the_type_description_of_asian_double_byte,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_asian_double_bytes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ASIAN-DOUBLE-BYTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_asian_double_bytes,
	    G2int_chain_of_available_asian_double_bytes);
    g2int_record_system_variable(Qg2int_chain_of_available_asian_double_bytes,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_asian_double_byte_count = 
	    STATIC_SYMBOL("ASIAN-DOUBLE-BYTE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_asian_double_byte_count,
	    G2int_asian_double_byte_count);
    g2int_record_system_variable(Qg2int_asian_double_byte_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_asian_double_byte = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_asian_double_byte,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_asian_double_byte,reclaim_structure_for_asian_double_byte);
    g2int_mutate_global_property(Qg2int_asian_double_byte,
	    g2int_make_asian_double_byte_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = Qnil;
  next_loop_12:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_12;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_asian_double_byte),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_12;
  end_loop_12:;
    map_code_to_unicode_for_asian_double_byte = 
	    STATIC_FUNCTION(g2int_map_code_to_unicode_for_asian_double_byte,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_code_to_unicode,
	    Qg2int_asian_double_byte,
	    map_code_to_unicode_for_asian_double_byte);
    Qg2_defstruct_structure_name_jis_x_0208_g2_struct = 
	    STATIC_SYMBOL("JIS-X-0208-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_jis_x_0208_g2_struct,
	    Qg2int_jis_x_0208,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_jis_x_0208,
	    Qg2_defstruct_structure_name_jis_x_0208_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_jis_x_0208 == UNBOUND)
	G2int_the_type_description_of_jis_x_0208 = Nil;
    string_constant_21 = 
	    STATIC_STRING("43Dy8l83*Ay1p83*Ay8z8q8m8k1l8z0000001l1r8o8z1m8t1m9k83*Ay1m8v1m9k1l83*9y1m8s1m9km1m8r1m9k3-Qy1m8u1m9k+s3-*ykkkkkl3A++yksk0k0");
    temp = G2int_the_type_description_of_jis_x_0208;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_jis_x_0208 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_21));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_jis_x_0208_g2_struct,
	    G2int_the_type_description_of_jis_x_0208,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_jis_x_0208,
	    G2int_the_type_description_of_jis_x_0208,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_jis_x_0208s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JIS-X-0208S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_jis_x_0208s,
	    G2int_chain_of_available_jis_x_0208s);
    g2int_record_system_variable(Qg2int_chain_of_available_jis_x_0208s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_jis_x_0208_count = STATIC_SYMBOL("JIS-X-0208-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_jis_x_0208_count,G2int_jis_x_0208_count);
    g2int_record_system_variable(Qg2int_jis_x_0208_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_jis_x_0208 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_jis_x_0208,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_jis_x_0208,reclaim_structure_for_jis_x_0208);
    Qg2int_jis = STATIC_SYMBOL("JIS",AB_package);
    list_constant_12 = STATIC_CONS(Qg2int_jis,Qnil);
    g2int_mutate_global_property(Qg2int_jis_x_0208,
	    g2int_make_jis_x_0208_1(),Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_12;
  next_loop_13:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_13;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_13;
  end_loop_13:;
    map_code_to_unicode_for_jis_x_0208 = 
	    STATIC_FUNCTION(g2int_map_code_to_unicode_for_jis_x_0208,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_code_to_unicode,
	    Qg2int_jis_x_0208,map_code_to_unicode_for_jis_x_0208);
    map_unicode_to_code_if_any_for_jis_x_0208 = 
	    STATIC_FUNCTION(g2int_map_unicode_to_code_if_any_for_jis_x_0208,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_unicode_to_code_if_any,
	    Qg2int_jis_x_0208,map_unicode_to_code_if_any_for_jis_x_0208);
    Qg2_defstruct_structure_name_ks_c_5601_g2_struct = 
	    STATIC_SYMBOL("KS-C-5601-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_ks_c_5601_g2_struct,
	    Qg2int_ks_c_5601,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_ks_c_5601,
	    Qg2_defstruct_structure_name_ks_c_5601_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_ks_c_5601 == UNBOUND)
	G2int_the_type_description_of_ks_c_5601 = Nil;
    string_constant_22 = 
	    STATIC_STRING("43Dy8l83*Cy1p83*Cy8z8q8m8k1l8z0000001l1r8o8z1m8t1m9k83*Cy1m8v1m9k1m83*By83*Dy1m8s1m9km1m8r1m9k3-Qy1m8u1m9k+s3-=ykkkkkl3A++yksk0k");
    temp = G2int_the_type_description_of_ks_c_5601;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_ks_c_5601 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(LIST_2(string_constant_22,
	    string_constant_10)));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_ks_c_5601_g2_struct,
	    G2int_the_type_description_of_ks_c_5601,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_ks_c_5601,
	    G2int_the_type_description_of_ks_c_5601,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_ks_c_5601s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-KS-C-5601S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_ks_c_5601s,
	    G2int_chain_of_available_ks_c_5601s);
    g2int_record_system_variable(Qg2int_chain_of_available_ks_c_5601s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_ks_c_5601_count = STATIC_SYMBOL("KS-C-5601-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_ks_c_5601_count,G2int_ks_c_5601_count);
    g2int_record_system_variable(Qg2int_ks_c_5601_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_ks_c_5601 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_ks_c_5601,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_ks_c_5601,reclaim_structure_for_ks_c_5601);
    Qg2int_ks = STATIC_SYMBOL("KS",AB_package);
    Qg2int_ksc = STATIC_SYMBOL("KSC",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qg2int_ks,Qg2int_ksc);
    g2int_mutate_global_property(Qg2int_ks_c_5601,g2int_make_ks_c_5601_1(),
	    Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_13;
  next_loop_14:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_14;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_14;
  end_loop_14:;
    map_code_to_unicode_for_ks_c_5601 = 
	    STATIC_FUNCTION(g2int_map_code_to_unicode_for_ks_c_5601,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_code_to_unicode,
	    Qg2int_ks_c_5601,map_code_to_unicode_for_ks_c_5601);
    map_unicode_to_code_if_any_for_ks_c_5601 = 
	    STATIC_FUNCTION(g2int_map_unicode_to_code_if_any_for_ks_c_5601,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_unicode_to_code_if_any,
	    Qg2int_ks_c_5601,map_unicode_to_code_if_any_for_ks_c_5601);
    Qg2_defstruct_structure_name_gb_2312_g2_struct = 
	    STATIC_SYMBOL("GB-2312-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gb_2312_g2_struct,
	    Qg2int_gb_2312,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gb_2312,
	    Qg2_defstruct_structure_name_gb_2312_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gb_2312 == UNBOUND)
	G2int_the_type_description_of_gb_2312 = Nil;
    string_constant_23 = 
	    STATIC_STRING("43Dy8l83ry1p83ry8z8q8m8k1l8z0000001l1r8o8z1m8t1m9k83ry1m8v1m9k1m83qy83sy1m8s1m9km1m8r1m9k3-Qy1m8u1m9k+s3-=ykkkkkl3A++yksk0k0");
    temp = G2int_the_type_description_of_gb_2312;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qquote);
    G2int_the_type_description_of_gb_2312 = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_23));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gb_2312_g2_struct,
	    G2int_the_type_description_of_gb_2312,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gb_2312,
	    G2int_the_type_description_of_gb_2312,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gb_2312s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GB-2312S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gb_2312s,
	    G2int_chain_of_available_gb_2312s);
    g2int_record_system_variable(Qg2int_chain_of_available_gb_2312s,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gb_2312_count = STATIC_SYMBOL("GB-2312-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gb_2312_count,G2int_gb_2312_count);
    g2int_record_system_variable(Qg2int_gb_2312_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gb_2312 = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gb_2312,NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gb_2312,reclaim_structure_for_gb_2312);
    Qg2int_gb = STATIC_SYMBOL("GB",AB_package);
    Qg2int_gb2312 = STATIC_SYMBOL("GB2312",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qg2int_gb,Qg2int_gb2312);
    g2int_mutate_global_property(Qg2int_gb_2312,g2int_make_gb_2312_1(),
	    Qg2int_graphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_14;
  next_loop_15:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_15;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    g2int_mutate_global_property(temp,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set),Qg2int_graphic_character_set);
    goto next_loop_15;
  end_loop_15:;
    map_code_to_unicode_for_gb_2312 = 
	    STATIC_FUNCTION(g2int_map_code_to_unicode_for_gb_2312,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_code_to_unicode,
	    Qg2int_gb_2312,map_code_to_unicode_for_gb_2312);
    map_unicode_to_code_if_any_for_gb_2312 = 
	    STATIC_FUNCTION(g2int_map_unicode_to_code_if_any_for_gb_2312,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_map_unicode_to_code_if_any,
	    Qg2int_gb_2312,map_unicode_to_code_if_any_for_gb_2312);
    Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_iso_8859_transcoder = STATIC_SYMBOL("ISO-8859-TRANSCODER",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct,
	    Qg2int_iso_8859_transcoder,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_8859_transcoder,
	    Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_8859_transcoder == UNBOUND)
	G2int_the_type_description_of_iso_8859_transcoder = Nil;
    string_constant_24 = 
	    STATIC_STRING("43Dy8l83*3y1o83*3y8x8m8k1l8x0000001m1m8o8x1n8n83*ly1m83*2y83*1yksk0k0");
    temp = G2int_the_type_description_of_iso_8859_transcoder;
    G2int_the_type_description_of_iso_8859_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_24));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct,
	    G2int_the_type_description_of_iso_8859_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_8859_transcoder,
	    G2int_the_type_description_of_iso_8859_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_8859_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_8859_transcoders,
	    G2int_chain_of_available_iso_8859_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_8859_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_8859_transcoder_count = 
	    STATIC_SYMBOL("ISO-8859-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_8859_transcoder_count,
	    G2int_iso_8859_transcoder_count);
    g2int_record_system_variable(Qg2int_iso_8859_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_8859_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_8859_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_8859_transcoder,
	    reclaim_structure_for_iso_8859_transcoder);
    transcode_character_for_iso_8859_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_iso_8859_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_iso_8859_transcoder,
	    transcode_character_for_iso_8859_transcoder);
    Qg2int_dos = STATIC_SYMBOL("DOS",AB_package);
    Qg2int_vms = STATIC_SYMBOL("VMS",AB_package);
    Qg2int_win32 = STATIC_SYMBOL("WIN32",AB_package);
    Qg2int_unix = STATIC_SYMBOL("UNIX",AB_package);
    Qg2int_cr = STATIC_SYMBOL("CR",AB_package);
    Qg2int_unicode_line_separator = STATIC_SYMBOL("UNICODE-LINE-SEPARATOR",
	    AB_package);
    Qg2int_unicode_paragraph_separator = 
	    STATIC_SYMBOL("UNICODE-PARAGRAPH-SEPARATOR",AB_package);
    export_character_for_iso_8859_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_iso_8859_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_iso_8859_transcoder,
	    export_character_for_iso_8859_transcoder);
    Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct = 
	    STATIC_SYMBOL("ISO-2022-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_iso_2022_transcoder = STATIC_SYMBOL("ISO-2022-TRANSCODER",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct,
	    Qg2int_iso_2022_transcoder,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_iso_2022_transcoder,
	    Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_iso_2022_transcoder == UNBOUND)
	G2int_the_type_description_of_iso_2022_transcoder = Nil;
    string_constant_25 = 
	    STATIC_STRING("43Dy8l83-qy1o83-qy8x8m8k1l8x0000001l1m8o8xkyk0k0");
    temp = G2int_the_type_description_of_iso_2022_transcoder;
    G2int_the_type_description_of_iso_2022_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_25));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct,
	    G2int_the_type_description_of_iso_2022_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_iso_2022_transcoder,
	    G2int_the_type_description_of_iso_2022_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_iso_2022_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-2022-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_iso_2022_transcoders,
	    G2int_chain_of_available_iso_2022_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_iso_2022_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_iso_2022_transcoder_count = 
	    STATIC_SYMBOL("ISO-2022-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_iso_2022_transcoder_count,
	    G2int_iso_2022_transcoder_count);
    g2int_record_system_variable(Qg2int_iso_2022_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_iso_2022_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_iso_2022_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_iso_2022_transcoder,
	    reclaim_structure_for_iso_2022_transcoder);
    Qg2int_create_transcoder_for_iso_646 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-646",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_646,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_646,NIL,FALSE,
	    0,0));
    g2int_mutate_global_property(Qg2int_iso_646,
	    Qg2int_create_transcoder_for_iso_646,
	    Qg2int_transcoder_creation_function);
    list_constant_21 = STATIC_CONS(Qg2int_ansi3dot4,Qnil);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)4L,Qg2int_us_ascii,
	    Qg2int_iso_646_irv,Qg2int_ascii,list_constant_21);
    synonym = Nil;
    ab_loop_list_ = list_constant_22;
  next_loop_16:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_16;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_646,
	    Qg2int_transcoder_creation_function);
    goto next_loop_16;
  end_loop_16:;
    Qg2int_iso_2022 = STATIC_SYMBOL("ISO-2022",AB_package);
    Qg2int_create_transcoder_for_iso_2022 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-2022",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_2022,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_2022,NIL,FALSE,
	    0,0));
    g2int_mutate_global_property(Qg2int_iso_2022,
	    Qg2int_create_transcoder_for_iso_2022,
	    Qg2int_transcoder_creation_function);
    list_constant_23 = STATIC_CONS(Qg2int_x_compound_text,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_23;
  next_loop_17:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_17;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_2022,
	    Qg2int_transcoder_creation_function);
    goto next_loop_17;
  end_loop_17:;
    Qg2int_create_transcoder_for_jis_x_0208 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-JIS-X-0208",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_jis_x_0208,
	    STATIC_FUNCTION(g2int_create_transcoder_for_jis_x_0208,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_jis_x_0208,
	    Qg2int_create_transcoder_for_jis_x_0208,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_12;
  next_loop_18:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_18;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_jis_x_0208,
	    Qg2int_transcoder_creation_function);
    goto next_loop_18;
  end_loop_18:;
    Qg2int_create_transcoder_for_jis_x_0208_euc = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-JIS-X-0208-EUC",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_jis_x_0208_euc,
	    STATIC_FUNCTION(g2int_create_transcoder_for_jis_x_0208_euc,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_jis_x_0208_euc,
	    Qg2int_create_transcoder_for_jis_x_0208_euc,
	    Qg2int_transcoder_creation_function);
    Qg2int_jis_euc = STATIC_SYMBOL("JIS-EUC",AB_package);
    list_constant_24 = STATIC_CONS(Qg2int_jis_euc,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_24;
  next_loop_19:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_19;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_jis_x_0208_euc,
	    Qg2int_transcoder_creation_function);
    goto next_loop_19;
  end_loop_19:;
    Qg2int_create_transcoder_for_shift_jis_x_0208 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-SHIFT-JIS-X-0208",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_shift_jis_x_0208,
	    STATIC_FUNCTION(g2int_create_transcoder_for_shift_jis_x_0208,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_shift_jis_x_0208,
	    Qg2int_create_transcoder_for_shift_jis_x_0208,
	    Qg2int_transcoder_creation_function);
    Qg2int_ms_kanji = STATIC_SYMBOL("MS-KANJI",AB_package);
    Qg2int_shift_jis = STATIC_SYMBOL("SHIFT-JIS",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qg2int_ms_kanji,
	    Qg2int_shift_jis);
    synonym = Nil;
    ab_loop_list_ = list_constant_25;
  next_loop_20:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_20;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_shift_jis_x_0208,
	    Qg2int_transcoder_creation_function);
    goto next_loop_20;
  end_loop_20:;
    Qg2int_create_transcoder_for_ks_c_5601 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-KS-C-5601",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_ks_c_5601,
	    STATIC_FUNCTION(g2int_create_transcoder_for_ks_c_5601,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_ks_c_5601,
	    Qg2int_create_transcoder_for_ks_c_5601,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_13;
  next_loop_21:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_21;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_ks_c_5601,
	    Qg2int_transcoder_creation_function);
    goto next_loop_21;
  end_loop_21:;
    Qg2int_create_transcoder_for_ks_c_5601_euc = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-KS-C-5601-EUC",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_ks_c_5601_euc,
	    STATIC_FUNCTION(g2int_create_transcoder_for_ks_c_5601_euc,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_ks_c_5601_euc,
	    Qg2int_create_transcoder_for_ks_c_5601_euc,
	    Qg2int_transcoder_creation_function);
    Qg2int_ks_euc = STATIC_SYMBOL("KS-EUC",AB_package);
    Qg2int_ksc_euc = STATIC_SYMBOL("KSC-EUC",AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qg2int_ks_euc,Qg2int_ksc_euc);
    synonym = Nil;
    ab_loop_list_ = list_constant_26;
  next_loop_22:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_22;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_ks_c_5601_euc,
	    Qg2int_transcoder_creation_function);
    goto next_loop_22;
  end_loop_22:;
    Qg2int_create_transcoder_for_gb_2312 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-GB-2312",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_gb_2312,
	    STATIC_FUNCTION(g2int_create_transcoder_for_gb_2312,NIL,FALSE,
	    0,0));
    g2int_mutate_global_property(Qg2int_gb_2312,
	    Qg2int_create_transcoder_for_gb_2312,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_14;
  next_loop_23:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_23;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_gb_2312,
	    Qg2int_transcoder_creation_function);
    goto next_loop_23;
  end_loop_23:;
    Qg2int_create_transcoder_for_gb_2312_euc = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-GB-2312-EUC",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_gb_2312_euc,
	    STATIC_FUNCTION(g2int_create_transcoder_for_gb_2312_euc,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_gb_2312_euc,
	    Qg2int_create_transcoder_for_gb_2312_euc,
	    Qg2int_transcoder_creation_function);
    Qg2int_gb_euc = STATIC_SYMBOL("GB-EUC",AB_package);
    Qg2int_gb2312_euc = STATIC_SYMBOL("GB2312-EUC",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qg2int_gb_euc,
	    Qg2int_gb2312_euc);
    synonym = Nil;
    ab_loop_list_ = list_constant_27;
  next_loop_24:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_24;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_gb_2312_euc,
	    Qg2int_transcoder_creation_function);
    goto next_loop_24;
  end_loop_24:;
    array_constant_9 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_left = STATIC_SYMBOL("LEFT",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_right = STATIC_SYMBOL("RIGHT",AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)57344L);
    array_constant_23 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)57344L);
    array_constant_28 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)74L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)57344L);
    array_constant_29 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)57344L);
    array_constant_30 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)57344L);
    array_constant_31 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)57344L);
    list_constant_28 = STATIC_CONS(Qg2int_left,Qnil);
    list_constant_29 = STATIC_CONS(Qg2int_right,Qnil);
    temp_1 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    temp_2 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_1),
	    Qg2int_graphic_character_set);
    temp_3 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_2),
	    Qg2int_graphic_character_set);
    temp_4 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_3),
	    Qg2int_graphic_character_set);
    temp_5 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_4),
	    Qg2int_graphic_character_set);
    temp_6 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_5),
	    Qg2int_graphic_character_set);
    temp_7 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_6),
	    Qg2int_graphic_character_set);
    temp_8 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_7),
	    Qg2int_graphic_character_set);
    temp_9 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_8),
	    Qg2int_graphic_character_set);
    temp_10 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_8859_9),
	    Qg2int_graphic_character_set);
    temp_11 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set);
    G2int_no_han_x_compound_text_character_set_selection_list = list(13,
	    CONS(temp_1,list_constant_28),CONS(temp_2,list_constant_29),
	    CONS(temp_3,list_constant_29),CONS(temp_4,list_constant_29),
	    CONS(temp_5,list_constant_29),CONS(temp_6,list_constant_29),
	    CONS(temp_7,list_constant_29),CONS(temp_8,list_constant_29),
	    CONS(temp_9,list_constant_29),CONS(temp_10,list_constant_29),
	    CONS(temp_11,list_constant_28),CONS(temp_12,list_constant_28),
	    CONS(temp,list_constant_28));
    temp_10 = G2int_no_han_x_compound_text_character_set_selection_list;
    temp_11 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set);
    G2int_japanese_han_x_compound_text_character_set_selection_list = 
	    append2(temp_10,LIST_3(CONS(temp_11,list_constant_28),
	    CONS(temp_12,list_constant_28),CONS(temp,list_constant_28)));
    temp_10 = G2int_no_han_x_compound_text_character_set_selection_list;
    temp_11 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set);
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set);
    G2int_korean_han_x_compound_text_character_set_selection_list = 
	    append2(temp_10,LIST_3(CONS(temp_11,list_constant_28),
	    CONS(temp_12,list_constant_28),CONS(temp,list_constant_28)));
    temp_10 = G2int_no_han_x_compound_text_character_set_selection_list;
    temp_11 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set);
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set);
    G2int_chinese_han_x_compound_text_character_set_selection_list = 
	    append2(temp_10,LIST_3(CONS(temp_11,list_constant_28),
	    CONS(temp_12,list_constant_28),CONS(temp,list_constant_28)));
    G2int_default_han_x_compound_text_character_set_selection_list = 
	    G2int_japanese_han_x_compound_text_character_set_selection_list;
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    G2int_us_ascii_character_set_selection_list = LIST_1(CONS(temp,
	    list_constant_28));
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set);
    G2int_ks_c_5601_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_28));
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_ks_c_5601),
	    Qg2int_graphic_character_set);
    G2int_ks_c_5601_euc_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_29));
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set);
    G2int_gb_2312_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_28));
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_gb_2312),
	    Qg2int_graphic_character_set);
    G2int_gb_2312_euc_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_29));
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    G2int_jis_x_0208_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_28));
    temp_12 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_iso_646),
	    Qg2int_graphic_character_set);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_jis_x_0208),
	    Qg2int_graphic_character_set);
    G2int_jis_x_0208_euc_character_set_selection_list = 
	    LIST_2(CONS(temp_12,list_constant_28),CONS(temp,list_constant_29));
    Qg2int_gl = STATIC_SYMBOL("GL",AB_package);
    Qg2int_gr = STATIC_SYMBOL("GR",AB_package);
    transcode_character_for_iso_2022_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_iso_2022_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_iso_2022_transcoder,
	    transcode_character_for_iso_2022_transcoder);
    export_character_for_iso_2022_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_iso_2022_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_iso_2022_transcoder,
	    export_character_for_iso_2022_transcoder);
    Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct = 
	    STATIC_SYMBOL("SHIFT-JIS-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_shift_jis_transcoder = STATIC_SYMBOL("SHIFT-JIS-TRANSCODER",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct,
	    Qg2int_shift_jis_transcoder,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_shift_jis_transcoder,
	    Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_shift_jis_transcoder == UNBOUND)
	G2int_the_type_description_of_shift_jis_transcoder = Nil;
    string_constant_26 = 
	    STATIC_STRING("43Dy8l83=wy1o83=wy8x8m8k1l8x0000001l1m8o8xkrk0k0");
    temp = G2int_the_type_description_of_shift_jis_transcoder;
    G2int_the_type_description_of_shift_jis_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_26));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct,
	    G2int_the_type_description_of_shift_jis_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_shift_jis_transcoder,
	    G2int_the_type_description_of_shift_jis_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_shift_jis_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SHIFT-JIS-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_shift_jis_transcoders,
	    G2int_chain_of_available_shift_jis_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_shift_jis_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_shift_jis_transcoder_count = 
	    STATIC_SYMBOL("SHIFT-JIS-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_shift_jis_transcoder_count,
	    G2int_shift_jis_transcoder_count);
    g2int_record_system_variable(Qg2int_shift_jis_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_shift_jis_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_shift_jis_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_shift_jis_transcoder,
	    reclaim_structure_for_shift_jis_transcoder);
    transcode_character_for_shift_jis_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_shift_jis_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_shift_jis_transcoder,
	    transcode_character_for_shift_jis_transcoder);
    export_character_for_shift_jis_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_shift_jis_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_shift_jis_transcoder,
	    export_character_for_shift_jis_transcoder);
    Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct = 
	    STATIC_SYMBOL("UTF-G-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_utf_g_transcoder = STATIC_SYMBOL("UTF-G-TRANSCODER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct,
	    Qg2int_utf_g_transcoder,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_utf_g_transcoder,
	    Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_utf_g_transcoder == UNBOUND)
	G2int_the_type_description_of_utf_g_transcoder = Nil;
    string_constant_27 = 
	    STATIC_STRING("43Dy8l83Ly1o83Ly8x8m8k1l8x0000001l1m8o8xksk0k0");
    temp = G2int_the_type_description_of_utf_g_transcoder;
    G2int_the_type_description_of_utf_g_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_27));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct,
	    G2int_the_type_description_of_utf_g_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_utf_g_transcoder,
	    G2int_the_type_description_of_utf_g_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_utf_g_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UTF-G-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_utf_g_transcoders,
	    G2int_chain_of_available_utf_g_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_utf_g_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_utf_g_transcoder_count = STATIC_SYMBOL("UTF-G-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_utf_g_transcoder_count,
	    G2int_utf_g_transcoder_count);
    g2int_record_system_variable(Qg2int_utf_g_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_utf_g_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_utf_g_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_utf_g_transcoder,reclaim_structure_for_utf_g_transcoder);
    transcode_character_for_utf_g_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_utf_g_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_utf_g_transcoder,transcode_character_for_utf_g_transcoder);
    export_character_for_utf_g_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_utf_g_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_utf_g_transcoder,export_character_for_utf_g_transcoder);
    Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct 
	    = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_utf_g_ascii_as_much_as_possible_transcoder = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct,
	    Qg2int_utf_g_ascii_as_much_as_possible_transcoder,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_utf_g_ascii_as_much_as_possible_transcoder,
	    Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_utf_g_ascii_as_much_as_possible_transcoder 
	    == UNBOUND)
	G2int_the_type_description_of_utf_g_ascii_as_much_as_possible_transcoder 
		= Nil;
    string_constant_28 = 
	    STATIC_STRING("43Dy8l830Cy1p830Cy83Ly8x8m8k1l83Ly0000001l1m8o83Lyksk0k0");
    temp = 
	    G2int_the_type_description_of_utf_g_ascii_as_much_as_possible_transcoder;
    G2int_the_type_description_of_utf_g_ascii_as_much_as_possible_transcoder 
	    = g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_28));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct,
	    G2int_the_type_description_of_utf_g_ascii_as_much_as_possible_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_utf_g_ascii_as_much_as_possible_transcoder,
	    G2int_the_type_description_of_utf_g_ascii_as_much_as_possible_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders 
	    = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders,
	    G2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_utf_g_ascii_as_much_as_possible_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_utf_g_ascii_as_much_as_possible_transcoder_count = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_utf_g_ascii_as_much_as_possible_transcoder_count,
	    G2int_utf_g_ascii_as_much_as_possible_transcoder_count);
    g2int_record_system_variable(Qg2int_utf_g_ascii_as_much_as_possible_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_utf_g_ascii_as_much_as_possible_transcoder,
	    reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder);
    export_character_for_utf_g_ascii_as_much_as_possible_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_utf_g_ascii_as_much_as_possible_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_utf_g_ascii_as_much_as_possible_transcoder,
	    export_character_for_utf_g_ascii_as_much_as_possible_transcoder);
    Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct = 
	    STATIC_SYMBOL("UNICODE-UCS-2-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_unicode_ucs_2_transcoder = 
	    STATIC_SYMBOL("UNICODE-UCS-2-TRANSCODER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct,
	    Qg2int_unicode_ucs_2_transcoder,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_unicode_ucs_2_transcoder,
	    Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_unicode_ucs_2_transcoder == UNBOUND)
	G2int_the_type_description_of_unicode_ucs_2_transcoder = Nil;
    string_constant_29 = 
	    STATIC_STRING("43Dy8l8308y1o8308y8x8m8k1l8x0000001l1m8o8xksk0k0");
    temp = G2int_the_type_description_of_unicode_ucs_2_transcoder;
    G2int_the_type_description_of_unicode_ucs_2_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_29));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct,
	    G2int_the_type_description_of_unicode_ucs_2_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_unicode_ucs_2_transcoder,
	    G2int_the_type_description_of_unicode_ucs_2_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_unicode_ucs_2_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNICODE-UCS-2-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_unicode_ucs_2_transcoders,
	    G2int_chain_of_available_unicode_ucs_2_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_unicode_ucs_2_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_unicode_ucs_2_transcoder_count = 
	    STATIC_SYMBOL("UNICODE-UCS-2-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_unicode_ucs_2_transcoder_count,
	    G2int_unicode_ucs_2_transcoder_count);
    g2int_record_system_variable(Qg2int_unicode_ucs_2_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_unicode_ucs_2_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_unicode_ucs_2_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_unicode_ucs_2_transcoder,
	    reclaim_structure_for_unicode_ucs_2_transcoder);
    transcode_character_for_unicode_ucs_2_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_unicode_ucs_2_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_unicode_ucs_2_transcoder,
	    transcode_character_for_unicode_ucs_2_transcoder);
    export_character_for_unicode_ucs_2_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_unicode_ucs_2_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_unicode_ucs_2_transcoder,
	    export_character_for_unicode_ucs_2_transcoder);
    Qg2_defstruct_structure_name_unicode_transcoder_g2_struct = 
	    STATIC_SYMBOL("UNICODE-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_unicode_transcoder = STATIC_SYMBOL("UNICODE-TRANSCODER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_unicode_transcoder_g2_struct,
	    Qg2int_unicode_transcoder,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_unicode_transcoder,
	    Qg2_defstruct_structure_name_unicode_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_unicode_transcoder == UNBOUND)
	G2int_the_type_description_of_unicode_transcoder = Nil;
    string_constant_30 = 
	    STATIC_STRING("43Dy8l8307y1o8307y8x8m8k1l8x0000001l1m8o8xkqk0k0");
    temp = G2int_the_type_description_of_unicode_transcoder;
    G2int_the_type_description_of_unicode_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_30));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_unicode_transcoder_g2_struct,
	    G2int_the_type_description_of_unicode_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_unicode_transcoder,
	    G2int_the_type_description_of_unicode_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_unicode_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNICODE-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_unicode_transcoders,
	    G2int_chain_of_available_unicode_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_unicode_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_unicode_transcoder_count = 
	    STATIC_SYMBOL("UNICODE-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_unicode_transcoder_count,
	    G2int_unicode_transcoder_count);
    g2int_record_system_variable(Qg2int_unicode_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_unicode_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_unicode_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_unicode_transcoder,
	    reclaim_structure_for_unicode_transcoder);
    transcode_character_for_unicode_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_unicode_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_unicode_transcoder,
	    transcode_character_for_unicode_transcoder);
    export_character_for_unicode_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_unicode_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_unicode_transcoder,export_character_for_unicode_transcoder);
    Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct 
	    = STATIC_SYMBOL("UNICODE-BYTE-SWAPPED-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_unicode_byte_swapped_transcoder = 
	    STATIC_SYMBOL("UNICODE-BYTE-SWAPPED-TRANSCODER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct,
	    Qg2int_unicode_byte_swapped_transcoder,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_unicode_byte_swapped_transcoder,
	    Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_unicode_byte_swapped_transcoder == 
	    UNBOUND)
	G2int_the_type_description_of_unicode_byte_swapped_transcoder = Nil;
    string_constant_31 = 
	    STATIC_STRING("43Dy8l8306y1o8306y8x8m8k1l8x0000001l1m8o8xkqk0k0");
    temp = G2int_the_type_description_of_unicode_byte_swapped_transcoder;
    G2int_the_type_description_of_unicode_byte_swapped_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_31));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct,
	    G2int_the_type_description_of_unicode_byte_swapped_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_unicode_byte_swapped_transcoder,
	    G2int_the_type_description_of_unicode_byte_swapped_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_unicode_byte_swapped_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNICODE-BYTE-SWAPPED-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_unicode_byte_swapped_transcoders,
	    G2int_chain_of_available_unicode_byte_swapped_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_unicode_byte_swapped_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_unicode_byte_swapped_transcoder_count = 
	    STATIC_SYMBOL("UNICODE-BYTE-SWAPPED-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_unicode_byte_swapped_transcoder_count,
	    G2int_unicode_byte_swapped_transcoder_count);
    g2int_record_system_variable(Qg2int_unicode_byte_swapped_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_unicode_byte_swapped_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_unicode_byte_swapped_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_unicode_byte_swapped_transcoder,
	    reclaim_structure_for_unicode_byte_swapped_transcoder);
    transcode_character_for_unicode_byte_swapped_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_unicode_byte_swapped_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_unicode_byte_swapped_transcoder,
	    transcode_character_for_unicode_byte_swapped_transcoder);
    export_character_for_unicode_byte_swapped_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_unicode_byte_swapped_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_unicode_byte_swapped_transcoder,
	    export_character_for_unicode_byte_swapped_transcoder);
    Qg2int_create_transcoder_for_iso_8859_1 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_1,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_1,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_1,
	    Qg2int_create_transcoder_for_iso_8859_1,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_2;
  next_loop_25:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_25;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_1,
	    Qg2int_transcoder_creation_function);
    goto next_loop_25;
  end_loop_25:;
    Qg2int_create_transcoder_for_iso_8859_2 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-2",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_2,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_2,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_2,
	    Qg2int_create_transcoder_for_iso_8859_2,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_3;
  next_loop_26:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_26;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_2,
	    Qg2int_transcoder_creation_function);
    goto next_loop_26;
  end_loop_26:;
    Qg2int_create_transcoder_for_iso_8859_3 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-3",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_3,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_3,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_3,
	    Qg2int_create_transcoder_for_iso_8859_3,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_4;
  next_loop_27:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_27;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_3,
	    Qg2int_transcoder_creation_function);
    goto next_loop_27;
  end_loop_27:;
    Qg2int_create_transcoder_for_iso_8859_4 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-4",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_4,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_4,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_4,
	    Qg2int_create_transcoder_for_iso_8859_4,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_5;
  next_loop_28:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_28;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_4,
	    Qg2int_transcoder_creation_function);
    goto next_loop_28;
  end_loop_28:;
    Qg2int_create_transcoder_for_iso_8859_5 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-5",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_5,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_5,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_5,
	    Qg2int_create_transcoder_for_iso_8859_5,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_6;
  next_loop_29:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_29;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_5,
	    Qg2int_transcoder_creation_function);
    goto next_loop_29;
  end_loop_29:;
    Qg2int_create_transcoder_for_iso_8859_6 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-6",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_6,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_6,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_6,
	    Qg2int_create_transcoder_for_iso_8859_6,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_7;
  next_loop_30:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_30;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_6,
	    Qg2int_transcoder_creation_function);
    goto next_loop_30;
  end_loop_30:;
    Qg2int_create_transcoder_for_iso_8859_7 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-7",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_7,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_7,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_7,
	    Qg2int_create_transcoder_for_iso_8859_7,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_8;
  next_loop_31:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_31;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_7,
	    Qg2int_transcoder_creation_function);
    goto next_loop_31;
  end_loop_31:;
    Qg2int_create_transcoder_for_iso_8859_8 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-8",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_8,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_8,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_8,
	    Qg2int_create_transcoder_for_iso_8859_8,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_9;
  next_loop_32:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_32;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_8,
	    Qg2int_transcoder_creation_function);
    goto next_loop_32;
  end_loop_32:;
    Qg2int_create_transcoder_for_iso_8859_9 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-9",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_9,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_9,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_9,
	    Qg2int_create_transcoder_for_iso_8859_9,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_10;
  next_loop_33:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_33;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_9,
	    Qg2int_transcoder_creation_function);
    goto next_loop_33;
  end_loop_33:;
    Qg2int_create_transcoder_for_iso_8859_10 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-10",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_iso_8859_10,
	    STATIC_FUNCTION(g2int_create_transcoder_for_iso_8859_10,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_iso_8859_10,
	    Qg2int_create_transcoder_for_iso_8859_10,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_11;
  next_loop_34:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_34;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_iso_8859_10,
	    Qg2int_transcoder_creation_function);
    goto next_loop_34;
  end_loop_34:;
    Qg2int_create_transcoder_for_gensym = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-GENSYM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_gensym,
	    STATIC_FUNCTION(g2int_create_transcoder_for_gensym,NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_gensym,
	    Qg2int_create_transcoder_for_gensym,
	    Qg2int_transcoder_creation_function);
    list_constant_30 = STATIC_CONS(Qg2int_utf_g,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_30;
  next_loop_35:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_35;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_gensym,
	    Qg2int_transcoder_creation_function);
    goto next_loop_35;
  end_loop_35:;
    Qg2int_gensym_with_ascii_as_much_as_possible = 
	    STATIC_SYMBOL("GENSYM-WITH-ASCII-AS-MUCH-AS-POSSIBLE",AB_package);
    Qg2int_create_transcoder_for_gensym_with_ascii_as_much_as_possible = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-GENSYM-WITH-ASCII-AS-MUCH-AS-POSSIBLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_gensym_with_ascii_as_much_as_possible,
	    STATIC_FUNCTION(g2int_create_transcoder_for_gensym_with_ascii_as_much_as_possible,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_gensym_with_ascii_as_much_as_possible,
	    Qg2int_create_transcoder_for_gensym_with_ascii_as_much_as_possible,
	    Qg2int_transcoder_creation_function);
    list_constant_31 = STATIC_CONS(Qg2int_utf_g_ascii_as_much_as_possible,
	    Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_31;
  next_loop_36:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_36;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_gensym_with_ascii_as_much_as_possible,
	    Qg2int_transcoder_creation_function);
    goto next_loop_36;
  end_loop_36:;
    Qg2int_unicode_ucs_2 = STATIC_SYMBOL("UNICODE-UCS-2",AB_package);
    Qg2int_create_transcoder_for_unicode_ucs_2 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-UCS-2",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_unicode_ucs_2,
	    STATIC_FUNCTION(g2int_create_transcoder_for_unicode_ucs_2,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_unicode_ucs_2,
	    Qg2int_create_transcoder_for_unicode_ucs_2,
	    Qg2int_transcoder_creation_function);
    Qg2int_iso_10646_ucs_2 = STATIC_SYMBOL("ISO-10646-UCS-2",AB_package);
    list_constant_32 = STATIC_CONS(Qg2int_iso_10646_ucs_2,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_32;
  next_loop_37:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_37;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_unicode_ucs_2,
	    Qg2int_transcoder_creation_function);
    goto next_loop_37;
  end_loop_37:;
    Qg2int_unicode_ucs_2_byte_swapped = 
	    STATIC_SYMBOL("UNICODE-UCS-2-BYTE-SWAPPED",AB_package);
    Qg2int_create_transcoder_for_unicode_ucs_2_byte_swapped = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-UCS-2-BYTE-SWAPPED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_unicode_ucs_2_byte_swapped,
	    STATIC_FUNCTION(g2int_create_transcoder_for_unicode_ucs_2_byte_swapped,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_unicode_ucs_2_byte_swapped,
	    Qg2int_create_transcoder_for_unicode_ucs_2_byte_swapped,
	    Qg2int_transcoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = Qnil;
  next_loop_38:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_38;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_unicode_ucs_2_byte_swapped,
	    Qg2int_transcoder_creation_function);
    goto next_loop_38;
  end_loop_38:;
    Qg2int_create_transcoder_for_unicode = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_unicode,
	    STATIC_FUNCTION(g2int_create_transcoder_for_unicode,NIL,FALSE,
	    0,0));
    g2int_mutate_global_property(Qg2int_unicode,
	    Qg2int_create_transcoder_for_unicode,
	    Qg2int_transcoder_creation_function);
    Qg2int_iso_10646 = STATIC_SYMBOL("ISO-10646",AB_package);
    list_constant_33 = STATIC_CONS(Qg2int_iso_10646,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_33;
  next_loop_39:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_39;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_unicode,
	    Qg2int_transcoder_creation_function);
    goto next_loop_39;
  end_loop_39:;
    Qg2int_unicode_byte_swapped = STATIC_SYMBOL("UNICODE-BYTE-SWAPPED",
	    AB_package);
    Qg2int_create_transcoder_for_unicode_byte_swapped = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-BYTE-SWAPPED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_unicode_byte_swapped,
	    STATIC_FUNCTION(g2int_create_transcoder_for_unicode_byte_swapped,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_unicode_byte_swapped,
	    Qg2int_create_transcoder_for_unicode_byte_swapped,
	    Qg2int_transcoder_creation_function);
    Qg2int_iso_10646_byte_swapped = STATIC_SYMBOL("ISO-10646-BYTE-SWAPPED",
	    AB_package);
    list_constant_34 = STATIC_CONS(Qg2int_iso_10646_byte_swapped,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_34;
  next_loop_40:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_40;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_unicode_byte_swapped,
	    Qg2int_transcoder_creation_function);
    goto next_loop_40;
  end_loop_40:;
    string_constant_32 = 
	    STATIC_STRING("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    G2int_utf_7_modified_base64_characters = g2int_stringw(string_constant_32);
    G2int_utf_7_ultraconservative_p = Nil;
    G2int_utf_7_delimit_encoded_sequences_p = T;
    Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct = 
	    STATIC_SYMBOL("UTF-7-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_utf_7_transcoder = STATIC_SYMBOL("UTF-7-TRANSCODER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct,
	    Qg2int_utf_7_transcoder,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_utf_7_transcoder,
	    Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_utf_7_transcoder == UNBOUND)
	G2int_the_type_description_of_utf_7_transcoder = Nil;
    string_constant_33 = 
	    STATIC_STRING("43Dy8l830Ay1o830Ay8x8m8k1l8x0000001l1m8o8xkqk0k0");
    temp = G2int_the_type_description_of_utf_7_transcoder;
    G2int_the_type_description_of_utf_7_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_33));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct,
	    G2int_the_type_description_of_utf_7_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_utf_7_transcoder,
	    G2int_the_type_description_of_utf_7_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_utf_7_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UTF-7-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_utf_7_transcoders,
	    G2int_chain_of_available_utf_7_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_utf_7_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_utf_7_transcoder_count = STATIC_SYMBOL("UTF-7-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_utf_7_transcoder_count,
	    G2int_utf_7_transcoder_count);
    g2int_record_system_variable(Qg2int_utf_7_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_utf_7_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_utf_7_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_utf_7_transcoder,reclaim_structure_for_utf_7_transcoder);
    Qg2int_create_transcoder_for_unicode_utf_7 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-UTF-7",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_unicode_utf_7,
	    STATIC_FUNCTION(g2int_create_transcoder_for_unicode_utf_7,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_unicode_utf_7,
	    Qg2int_create_transcoder_for_unicode_utf_7,
	    Qg2int_transcoder_creation_function);
    Qg2int_utf_7 = STATIC_SYMBOL("UTF-7",AB_package);
    list_constant_35 = STATIC_CONS(Qg2int_utf_7,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_35;
  next_loop_41:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_41;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_unicode_utf_7,
	    Qg2int_transcoder_creation_function);
    goto next_loop_41;
  end_loop_41:;
    transcode_character_for_utf_7_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_utf_7_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_utf_7_transcoder,transcode_character_for_utf_7_transcoder);
    Qg2int_illegal_utf_7_base64_character = 
	    STATIC_SYMBOL("ILLEGAL-UTF-7-BASE64-CHARACTER",AB_package);
    Qg2int_ill_formed_octet_stream_odd_number = 
	    STATIC_SYMBOL("ILL-FORMED-OCTET-STREAM-ODD-NUMBER",AB_package);
    export_character_for_utf_7_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_utf_7_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_utf_7_transcoder,export_character_for_utf_7_transcoder);
    list_constant_36 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)1L),
	    FIX((SI_Long)0L),FIX((SI_Long)127L),FIX((SI_Long)7L),
	    FIX((SI_Long)127L));
    list_constant_37 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)2L),
	    FIX((SI_Long)192L),FIX((SI_Long)31L),FIX((SI_Long)5L),
	    FIX((SI_Long)2047L));
    list_constant_38 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)3L),
	    FIX((SI_Long)224L),FIX((SI_Long)15L),FIX((SI_Long)4L),
	    FIX((SI_Long)65535L));
    list_constant_39 = STATIC_LIST((SI_Long)3L,list_constant_36,
	    list_constant_37,list_constant_38);
    if (G2int_ucs_4_to_utf_8_1st_octet_table == UNBOUND)
	G2int_ucs_4_to_utf_8_1st_octet_table = list_constant_39;
    Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct = 
	    STATIC_SYMBOL("UTF-8-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_utf_8_transcoder = STATIC_SYMBOL("UTF-8-TRANSCODER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct,
	    Qg2int_utf_8_transcoder,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_utf_8_transcoder,
	    Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_utf_8_transcoder == UNBOUND)
	G2int_the_type_description_of_utf_8_transcoder = Nil;
    string_constant_34 = 
	    STATIC_STRING("43Dy8l830By1o830By8x8m8k1l8x0000001l1m8o8xkqk0k0");
    temp = G2int_the_type_description_of_utf_8_transcoder;
    G2int_the_type_description_of_utf_8_transcoder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_34));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct,
	    G2int_the_type_description_of_utf_8_transcoder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_utf_8_transcoder,
	    G2int_the_type_description_of_utf_8_transcoder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_utf_8_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UTF-8-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_utf_8_transcoders,
	    G2int_chain_of_available_utf_8_transcoders);
    g2int_record_system_variable(Qg2int_chain_of_available_utf_8_transcoders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_utf_8_transcoder_count = STATIC_SYMBOL("UTF-8-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_utf_8_transcoder_count,
	    G2int_utf_8_transcoder_count);
    g2int_record_system_variable(Qg2int_utf_8_transcoder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_utf_8_transcoder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_utf_8_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_utf_8_transcoder,reclaim_structure_for_utf_8_transcoder);
    Qg2int_create_transcoder_for_unicode_utf_8 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-UTF-8",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_create_transcoder_for_unicode_utf_8,
	    STATIC_FUNCTION(g2int_create_transcoder_for_unicode_utf_8,NIL,
	    FALSE,0,0));
    g2int_mutate_global_property(Qg2int_unicode_utf_8,
	    Qg2int_create_transcoder_for_unicode_utf_8,
	    Qg2int_transcoder_creation_function);
    Qg2int_utf_8 = STATIC_SYMBOL("UTF-8",AB_package);
    list_constant_40 = STATIC_CONS(Qg2int_utf_8,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_40;
  next_loop_42:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_42;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_mutate_global_property(synonym,
	    Qg2int_create_transcoder_for_unicode_utf_8,
	    Qg2int_transcoder_creation_function);
    goto next_loop_42;
  end_loop_42:;
    transcode_character_for_utf_8_transcoder = 
	    STATIC_FUNCTION(g2int_transcode_character_for_utf_8_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_transcode_character,
	    Qg2int_utf_8_transcoder,transcode_character_for_utf_8_transcoder);
    export_character_for_utf_8_transcoder = 
	    STATIC_FUNCTION(g2int_export_character_for_utf_8_transcoder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_export_character,
	    Qg2int_utf_8_transcoder,export_character_for_utf_8_transcoder);
    if (G2int_intern_string_buffer == UNBOUND)
	G2int_intern_string_buffer = make_array(5,
		FIXNUM_ADD1(G2int_intern_string_buffer_length),
		Kelement_type,Qstring_char,Kfill_pointer,FIX((SI_Long)0L));
    list_constant_16 = STATIC_CONS(FIX((SI_Long)10L),Qnil);
    list_constant_15 = STATIC_CONS(FIX((SI_Long)13L),list_constant_16);
    list_constant_17 = STATIC_CONS(FIX((SI_Long)13L),Qnil);
    list_constant_18 = STATIC_CONS(FIX((SI_Long)8232L),Qnil);
    list_constant_19 = STATIC_CONS(FIX((SI_Long)8233L),Qnil);
    list_constant_41 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)7L),
	    FIX((SI_Long)15L));
    list_constant_42 = STATIC_LIST((SI_Long)5L,FIX((SI_Long)0L),
	    FIX((SI_Long)1L),list_constant_41,FIX((SI_Long)8L),
	    FIX((SI_Long)9L));
    if (G2int_standard_8_bit_non_graphic_characters_skip_spec == UNBOUND)
	G2int_standard_8_bit_non_graphic_characters_skip_spec = 
		list_constant_42;
}
