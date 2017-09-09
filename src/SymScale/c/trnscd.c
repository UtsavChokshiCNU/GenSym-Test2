/* trnscd.c
 * Input file:  transcode.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "trnscd.h"


Object The_type_description_of_transcode_text_conversion_style = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_transcode_text_conversion_styles, Qchain_of_available_transcode_text_conversion_styles);

DEFINE_VARIABLE_WITH_SYMBOL(Transcode_text_conversion_style_count, Qtranscode_text_conversion_style_count);

Object Chain_of_available_transcode_text_conversion_styles_vector = UNBOUND;

/* TRANSCODE-TEXT-CONVERSION-STYLE-STRUCTURE-MEMORY-USAGE */
Object transcode_text_conversion_style_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,0);
    temp = Transcode_text_conversion_style_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TRANSCODE-TEXT-CONVERSION-STYLE-COUNT */
Object outstanding_transcode_text_conversion_style_count()
{
    Object def_structure_transcode_text_conversion_style_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,1);
    gensymed_symbol = IFIX(Transcode_text_conversion_style_count);
    def_structure_transcode_text_conversion_style_variable = 
	    Chain_of_available_transcode_text_conversion_styles;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_transcode_text_conversion_style_variable))
	goto end_loop;
    def_structure_transcode_text_conversion_style_variable = 
	    ISVREF(def_structure_transcode_text_conversion_style_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TRANSCODE-TEXT-CONVERSION-STYLE-1 */
Object reclaim_transcode_text_conversion_style_1(transcode_text_conversion_style)
    Object transcode_text_conversion_style;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,2);
    inline_note_reclaim_cons(transcode_text_conversion_style,Nil);
    temp = 
	    ISVREF(Chain_of_available_transcode_text_conversion_styles_vector,
	    IFIX(Current_thread_index));
    SVREF(transcode_text_conversion_style,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_transcode_text_conversion_styles_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = transcode_text_conversion_style;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TRANSCODE-TEXT-CONVERSION-STYLE */
Object reclaim_structure_for_transcode_text_conversion_style(transcode_text_conversion_style)
    Object transcode_text_conversion_style;
{
    x_note_fn_call(28,3);
    return reclaim_transcode_text_conversion_style_1(transcode_text_conversion_style);
}

static Object Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct;  /* g2-defstruct-structure-name::transcode-text-conversion-style-g2-struct */

/* MAKE-PERMANENT-TRANSCODE-TEXT-CONVERSION-STYLE-STRUCTURE-INTERNAL */
Object make_permanent_transcode_text_conversion_style_structure_internal()
{
    Object def_structure_transcode_text_conversion_style_variable;
    Object defstruct_g2_transcode_text_conversion_style_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,4);
    def_structure_transcode_text_conversion_style_variable = Nil;
    atomic_incff_symval(Qtranscode_text_conversion_style_count,
	    FIX((SI_Long)1L));
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

static Object Qper_platform;       /* per-platform */

static Object Qwide_string;        /* wide-string */

/* MAKE-TRANSCODE-TEXT-CONVERSION-STYLE-1 */
Object make_transcode_text_conversion_style_1()
{
    Object def_structure_transcode_text_conversion_style_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(28,5);
    def_structure_transcode_text_conversion_style_variable = 
	    ISVREF(Chain_of_available_transcode_text_conversion_styles_vector,
	    IFIX(Current_thread_index));
    if (def_structure_transcode_text_conversion_style_variable) {
	svref_arg_1 = 
		Chain_of_available_transcode_text_conversion_styles_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_transcode_text_conversion_style_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_transcode_text_conversion_style_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct;
    }
    else
	def_structure_transcode_text_conversion_style_variable = 
		make_permanent_transcode_text_conversion_style_structure_internal();
    inline_note_allocate_cons(def_structure_transcode_text_conversion_style_variable,
	    Nil);
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)4L)) = Qper_platform;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_transcode_text_conversion_style_variable,
	    FIX((SI_Long)6L)) = Qwide_string;
    return VALUES_1(def_structure_transcode_text_conversion_style_variable);
}

Object Text_conversion_style_for_purpose_prop = UNBOUND;

/* CREATE-TRANSCODE-TEXT-CONVERSION-STYLE */
Object create_transcode_text_conversion_style(parent_style_qm,
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

    x_note_fn_call(28,6);
    style = make_transcode_text_conversion_style_1();
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

static Object Qtext_conversion_style_for_purpose;  /* text-conversion-style-for-purpose */

/* INSTALL-TEXT-TRANSCODE-PURPOSE */
Object install_text_transcode_purpose(purpose,parent_purpose,
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

    x_note_fn_call(28,7);
    style = create_transcode_text_conversion_style(parent_purpose ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(parent_purpose),
	    Qtext_conversion_style_for_purpose) : Nil,
	    conversion_style_name,external_character_set,
	    unconvertible_character_spec,
	    unicode_line_separator_export_translation,han_unification_mode,
	    string_type_for_export);
    mutate_global_property(purpose,style,Qtext_conversion_style_for_purpose);
    return VALUES_1(purpose);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_text_conversion_style, Qdefault_text_conversion_style);

DEFINE_VARIABLE_WITH_SYMBOL(Utf_g_ascii_as_much_as_possible_conversion_style, Qutf_g_ascii_as_much_as_possible_conversion_style);

/* TWRITE-SPACES-FOR-TABS */
Object twrite_spaces_for_tabs(spaces_for_tabs_qm)
    Object spaces_for_tabs_qm;
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long ab_loop_repeat_, simple_or_wide_character, thing;

    x_note_fn_call(28,8);
    ab_loop_repeat_ = spaces_for_tabs_qm ? (FIXNUMP(spaces_for_tabs_qm) ? 
	    IFIX(spaces_for_tabs_qm) : (SI_Long)1L) : (SI_Long)1L;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    simple_or_wide_character = spaces_for_tabs_qm ? (SI_Long)32L : (SI_Long)9L;
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = simple_or_wide_character;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

Object The_type_description_of_text_sequence = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_text_sequences, Qchain_of_available_text_sequences);

DEFINE_VARIABLE_WITH_SYMBOL(Text_sequence_count, Qtext_sequence_count);

Object Chain_of_available_text_sequences_vector = UNBOUND;

/* TEXT-SEQUENCE-STRUCTURE-MEMORY-USAGE */
Object text_sequence_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,9);
    temp = Text_sequence_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TEXT-SEQUENCE-COUNT */
Object outstanding_text_sequence_count()
{
    Object def_structure_text_sequence_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,10);
    gensymed_symbol = IFIX(Text_sequence_count);
    def_structure_text_sequence_variable = Chain_of_available_text_sequences;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_text_sequence_variable))
	goto end_loop;
    def_structure_text_sequence_variable = 
	    ISVREF(def_structure_text_sequence_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TEXT-SEQUENCE-INTERNAL-1 */
Object reclaim_text_sequence_internal_1(text_sequence)
    Object text_sequence;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,11);
    inline_note_reclaim_cons(text_sequence,Nil);
    temp = ISVREF(Chain_of_available_text_sequences_vector,
	    IFIX(Current_thread_index));
    SVREF(text_sequence,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_text_sequences_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = text_sequence;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TEXT-SEQUENCE */
Object reclaim_structure_for_text_sequence(text_sequence)
    Object text_sequence;
{
    x_note_fn_call(28,12);
    return reclaim_text_sequence_internal_1(text_sequence);
}

static Object Qg2_defstruct_structure_name_text_sequence_g2_struct;  /* g2-defstruct-structure-name::text-sequence-g2-struct */

/* MAKE-PERMANENT-TEXT-SEQUENCE-STRUCTURE-INTERNAL */
Object make_permanent_text_sequence_structure_internal()
{
    Object def_structure_text_sequence_variable;
    Object defstruct_g2_text_sequence_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,13);
    def_structure_text_sequence_variable = Nil;
    atomic_incff_symval(Qtext_sequence_count,FIX((SI_Long)1L));
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
Object make_text_sequence_internal_1()
{
    Object def_structure_text_sequence_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,14);
    def_structure_text_sequence_variable = 
	    ISVREF(Chain_of_available_text_sequences_vector,
	    IFIX(Current_thread_index));
    if (def_structure_text_sequence_variable) {
	svref_arg_1 = Chain_of_available_text_sequences_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_text_sequence_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_text_sequence_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_sequence_g2_struct;
    }
    else
	def_structure_text_sequence_variable = 
		make_permanent_text_sequence_structure_internal();
    inline_note_allocate_cons(def_structure_text_sequence_variable,Nil);
    ISVREF(def_structure_text_sequence_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_text_sequence_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_text_sequence_variable);
}

Object The_type_description_of_gensym_string_text_sequence = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gensym_string_text_sequences, Qchain_of_available_gensym_string_text_sequences);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_string_text_sequence_count, Qgensym_string_text_sequence_count);

Object Chain_of_available_gensym_string_text_sequences_vector = UNBOUND;

/* GENSYM-STRING-TEXT-SEQUENCE-STRUCTURE-MEMORY-USAGE */
Object gensym_string_text_sequence_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,15);
    temp = Gensym_string_text_sequence_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GENSYM-STRING-TEXT-SEQUENCE-COUNT */
Object outstanding_gensym_string_text_sequence_count()
{
    Object def_structure_gensym_string_text_sequence_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,16);
    gensymed_symbol = IFIX(Gensym_string_text_sequence_count);
    def_structure_gensym_string_text_sequence_variable = 
	    Chain_of_available_gensym_string_text_sequences;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gensym_string_text_sequence_variable))
	goto end_loop;
    def_structure_gensym_string_text_sequence_variable = 
	    ISVREF(def_structure_gensym_string_text_sequence_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GENSYM-STRING-TEXT-SEQUENCE-1 */
Object reclaim_gensym_string_text_sequence_1(gensym_string_text_sequence)
    Object gensym_string_text_sequence;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,17);
    inline_note_reclaim_cons(gensym_string_text_sequence,Nil);
    temp = ISVREF(Chain_of_available_gensym_string_text_sequences_vector,
	    IFIX(Current_thread_index));
    SVREF(gensym_string_text_sequence,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gensym_string_text_sequences_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gensym_string_text_sequence;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GENSYM-STRING-TEXT-SEQUENCE */
Object reclaim_structure_for_gensym_string_text_sequence(gensym_string_text_sequence)
    Object gensym_string_text_sequence;
{
    x_note_fn_call(28,18);
    return reclaim_gensym_string_text_sequence_1(gensym_string_text_sequence);
}

static Object Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct;  /* g2-defstruct-structure-name::gensym-string-text-sequence-g2-struct */

/* MAKE-PERMANENT-GENSYM-STRING-TEXT-SEQUENCE-STRUCTURE-INTERNAL */
Object make_permanent_gensym_string_text_sequence_structure_internal()
{
    Object def_structure_gensym_string_text_sequence_variable;
    Object defstruct_g2_gensym_string_text_sequence_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,19);
    def_structure_gensym_string_text_sequence_variable = Nil;
    atomic_incff_symval(Qgensym_string_text_sequence_count,FIX((SI_Long)1L));
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
	temp = 
		ISVREF(Chain_of_available_gensym_string_text_sequences_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_gensym_string_text_sequence_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_gensym_string_text_sequences_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_gensym_string_text_sequence_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gensym_string_text_sequence_variable);
}

static Object Qgensym_string;      /* gensym-string */

/* MAKE-GENSYM-STRING-TEXT-SEQUENCE-1 */
Object make_gensym_string_text_sequence_1()
{
    Object def_structure_gensym_string_text_sequence_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(28,20);
    def_structure_gensym_string_text_sequence_variable = 
	    ISVREF(Chain_of_available_gensym_string_text_sequences_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gensym_string_text_sequence_variable) {
	svref_arg_1 = Chain_of_available_gensym_string_text_sequences_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_gensym_string_text_sequence_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gensym_string_text_sequence_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct;
    }
    else
	def_structure_gensym_string_text_sequence_variable = 
		make_permanent_gensym_string_text_sequence_structure_internal();
    inline_note_allocate_cons(def_structure_gensym_string_text_sequence_variable,
	    Nil);
    ISVREF(def_structure_gensym_string_text_sequence_variable,(SI_Long)2L) 
	    = FIX((SI_Long)0L);
    SVREF(def_structure_gensym_string_text_sequence_variable,
	    FIX((SI_Long)4L)) = Qgensym_string;
    SVREF(def_structure_gensym_string_text_sequence_variable,
	    FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_gensym_string_text_sequence_variable);
}

Object The_type_description_of_wide_string_text_sequence = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_wide_string_text_sequences, Qchain_of_available_wide_string_text_sequences);

DEFINE_VARIABLE_WITH_SYMBOL(Wide_string_text_sequence_count, Qwide_string_text_sequence_count);

Object Chain_of_available_wide_string_text_sequences_vector = UNBOUND;

/* WIDE-STRING-TEXT-SEQUENCE-STRUCTURE-MEMORY-USAGE */
Object wide_string_text_sequence_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,21);
    temp = Wide_string_text_sequence_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-WIDE-STRING-TEXT-SEQUENCE-COUNT */
Object outstanding_wide_string_text_sequence_count()
{
    Object def_structure_wide_string_text_sequence_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,22);
    gensymed_symbol = IFIX(Wide_string_text_sequence_count);
    def_structure_wide_string_text_sequence_variable = 
	    Chain_of_available_wide_string_text_sequences;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_wide_string_text_sequence_variable))
	goto end_loop;
    def_structure_wide_string_text_sequence_variable = 
	    ISVREF(def_structure_wide_string_text_sequence_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-WIDE-STRING-TEXT-SEQUENCE-1 */
Object reclaim_wide_string_text_sequence_1(wide_string_text_sequence)
    Object wide_string_text_sequence;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,23);
    inline_note_reclaim_cons(wide_string_text_sequence,Nil);
    temp = ISVREF(Chain_of_available_wide_string_text_sequences_vector,
	    IFIX(Current_thread_index));
    SVREF(wide_string_text_sequence,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_wide_string_text_sequences_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = wide_string_text_sequence;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WIDE-STRING-TEXT-SEQUENCE */
Object reclaim_structure_for_wide_string_text_sequence(wide_string_text_sequence)
    Object wide_string_text_sequence;
{
    x_note_fn_call(28,24);
    return reclaim_wide_string_text_sequence_1(wide_string_text_sequence);
}

static Object Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct;  /* g2-defstruct-structure-name::wide-string-text-sequence-g2-struct */

/* MAKE-PERMANENT-WIDE-STRING-TEXT-SEQUENCE-STRUCTURE-INTERNAL */
Object make_permanent_wide_string_text_sequence_structure_internal()
{
    Object def_structure_wide_string_text_sequence_variable;
    Object defstruct_g2_wide_string_text_sequence_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,25);
    def_structure_wide_string_text_sequence_variable = Nil;
    atomic_incff_symval(Qwide_string_text_sequence_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_wide_string_text_sequences_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_wide_string_text_sequence_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_wide_string_text_sequences_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_wide_string_text_sequence_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_wide_string_text_sequence_variable);
}

/* MAKE-WIDE-STRING-TEXT-SEQUENCE-1 */
Object make_wide_string_text_sequence_1()
{
    Object def_structure_wide_string_text_sequence_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(28,26);
    def_structure_wide_string_text_sequence_variable = 
	    ISVREF(Chain_of_available_wide_string_text_sequences_vector,
	    IFIX(Current_thread_index));
    if (def_structure_wide_string_text_sequence_variable) {
	svref_arg_1 = Chain_of_available_wide_string_text_sequences_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_wide_string_text_sequence_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_wide_string_text_sequence_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct;
    }
    else
	def_structure_wide_string_text_sequence_variable = 
		make_permanent_wide_string_text_sequence_structure_internal();
    inline_note_allocate_cons(def_structure_wide_string_text_sequence_variable,
	    Nil);
    ISVREF(def_structure_wide_string_text_sequence_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_wide_string_text_sequence_variable,
	    FIX((SI_Long)4L)) = Qwide_string;
    SVREF(def_structure_wide_string_text_sequence_variable,
	    FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_wide_string_text_sequence_variable);
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* INITIALIZE-TEXT-SEQUENCE-STRING-FUNCTION */
Object initialize_text_sequence_string_function(text_sequence,string_1,
	    start_qm,end_qm)
    Object text_sequence, string_1, start_qm, end_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(28,27);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)10L);
    gensymed_symbol_1 = text_sequence;
    gensymed_symbol_2 = string_1;
    gensymed_symbol_3 = start_qm;
    gensymed_symbol_4 = end_qm;
    return VALUES_1(inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4));
}

/* INITIALIZE-TEXT-SEQUENCE-STRING-FOR-TEXT-SEQUENCE */
Object initialize_text_sequence_string_for_text_sequence(text_sequence,
	    string_1,start_qm,end_qm)
    Object text_sequence, string_1, start_qm, end_qm;
{
    Object svref_new_value;

    x_note_fn_call(28,28);
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
Object initialize_text_sequence_string_for_gensym_string_text_sequence(gensym_string_text_sequence,
	    string_1,start_qm,end_qm)
    Object gensym_string_text_sequence, string_1, start_qm, end_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, svref_new_value;
    char simple_p;

    x_note_fn_call(28,29);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_gensym_string_text_sequence,
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
Object initialize_text_sequence_string_for_wide_string_text_sequence(wide_string_text_sequence,
	    string_1,start_qm,end_qm)
    Object wide_string_text_sequence, string_1, start_qm, end_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, svref_new_value;
    SI_Long length_1;

    x_note_fn_call(28,30);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_wide_string_text_sequence,
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
Object read_character_from_text_sequence_function(text_sequence)
    Object text_sequence;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,31);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)11L);
    gensymed_symbol_1 = text_sequence;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* READ-CHARACTER-FROM-TEXT-SEQUENCE-FOR-GENSYM-STRING-TEXT-SEQUENCE */
Object read_character_from_text_sequence_for_gensym_string_text_sequence(gensym_string_text_sequence)
    Object gensym_string_text_sequence;
{
    Object text_sequence, svref_new_value, gensym_string, index_1;
    Object string_is_simple_qm;
    char temp;

    x_note_fn_call(28,32);
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
Object read_character_from_text_sequence_for_wide_string_text_sequence(wide_string_text_sequence)
    Object wide_string_text_sequence;
{
    Object text_sequence, svref_new_value, temp;

    x_note_fn_call(28,33);
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
Object make_text_sequence(string_1,start_qm,end_qm)
    Object string_1, start_qm, end_qm;
{
    Object text_sequence, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(28,34);
    text_sequence = STRINGP(string_1) ? 
	    make_gensym_string_text_sequence_1() : 
	    make_wide_string_text_sequence_1();
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)10L);
    gensymed_symbol_1 = text_sequence;
    gensymed_symbol_2 = string_1;
    gensymed_symbol_3 = start_qm;
    gensymed_symbol_4 = end_qm;
    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3,gensymed_symbol_4);
    return VALUES_1(text_sequence);
}

Object The_type_description_of_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_transcoders, Qchain_of_available_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Transcoder_count, Qtranscoder_count);

Object Chain_of_available_transcoders_vector = UNBOUND;

/* TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,35);
    temp = Transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TRANSCODER-COUNT */
Object outstanding_transcoder_count()
{
    Object def_structure_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,36);
    gensymed_symbol = IFIX(Transcoder_count);
    def_structure_transcoder_variable = Chain_of_available_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_transcoder_variable))
	goto end_loop;
    def_structure_transcoder_variable = 
	    ISVREF(def_structure_transcoder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TRANSCODER-1 */
Object reclaim_transcoder_1(transcoder)
    Object transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,37);
    inline_note_reclaim_cons(transcoder,Nil);
    temp = ISVREF(Chain_of_available_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TRANSCODER */
Object reclaim_structure_for_transcoder(transcoder)
    Object transcoder;
{
    x_note_fn_call(28,38);
    return reclaim_transcoder_1(transcoder);
}

static Object Qg2_defstruct_structure_name_transcoder_g2_struct;  /* g2-defstruct-structure-name::transcoder-g2-struct */

/* MAKE-PERMANENT-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_transcoder_structure_internal()
{
    Object def_structure_transcoder_variable, defstruct_g2_transcoder_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,39);
    def_structure_transcoder_variable = Nil;
    atomic_incff_symval(Qtranscoder_count,FIX((SI_Long)1L));
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
Object make_transcoder_1()
{
    Object def_structure_transcoder_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,40);
    def_structure_transcoder_variable = 
	    ISVREF(Chain_of_available_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_transcoder_variable) {
	svref_arg_1 = Chain_of_available_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_transcoder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_transcoder_g2_struct;
    }
    else
	def_structure_transcoder_variable = 
		make_permanent_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_transcoder_variable,Nil);
    ISVREF(def_structure_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_transcoder_variable);
}

/* GET-TRANSCODER-CHARACTER */
Object get_transcoder_character(transcoder)
    Object transcoder;
{
    Object text_sequence, svref_new_value, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,41);
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    svref_new_value = ISVREF(transcoder,(SI_Long)2L);
    SVREF(transcoder,FIX((SI_Long)3L)) = svref_new_value;
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)11L);
    gensymed_symbol_1 = text_sequence;
    svref_new_value = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(SVREF(transcoder,FIX((SI_Long)2L)) = svref_new_value);
}

/* GET-TRANSCODER-CHARACTER-IF-ANY */
Object get_transcoder_character_if_any(transcoder)
    Object transcoder;
{
    Object text_sequence, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object temp;

    x_note_fn_call(28,42);
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    if (FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L))) {
	svref_new_value = ISVREF(transcoder,(SI_Long)2L);
	SVREF(transcoder,FIX((SI_Long)3L)) = svref_new_value;
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
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
Object transcode_character_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,43);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)12L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* EXPORT-CHARACTER-FUNCTION */
Object export_character_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,44);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)15L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* TRANSCODE-CHARACTER-FOR-TRANSCODER */
Object transcode_character_for_transcoder(transcoder)
    Object transcoder;
{
    x_note_fn_call(28,45);
    return get_transcoder_character(transcoder);
}

/* EXPORT-CHARACTER-FOR-TRANSCODER */
Object export_character_for_transcoder(transcoder)
    Object transcoder;
{
    x_note_fn_call(28,46);
    return get_transcoder_character(transcoder);
}

/* TRANSCODE-AS-TEXT-STRING-FUNCTION */
Object transcode_as_text_string_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,47);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)14L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* TWRITE-UNICODE-FROM-TRANSCODER-FUNCTION */
Object twrite_unicode_from_transcoder_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,48);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)13L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* EXPORT-AS-STRING-FUNCTION */
Object export_as_string_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,49);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)16L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* TWRITE-FOR-EXPORT-FROM-TRANSCODER-FUNCTION */
Object twrite_for_export_from_transcoder_function(transcoder)
    Object transcoder;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,50);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)17L);
    gensymed_symbol_1 = transcoder;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object Qdo_not_use;         /* do-not-use */

/* TRANSCODE-AS-TEXT-STRING-FOR-TRANSCODER */
Object transcode_as_text_string_for_transcoder(transcoder)
    Object transcoder;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, gensymed_symbol_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(28,51);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
	      gensymed_symbol = 
		      ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		      Qtype_description_of_unique_type_name_of_gensym_structure),
		      (SI_Long)9L),(SI_Long)13L);
	      gensymed_symbol_1 = transcoder;
	      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qab_gensym;          /* gensym */

/* TWRITE-UNICODE-FROM-TRANSCODER-FOR-TRANSCODER */
Object twrite_unicode_from_transcoder_for_transcoder(transcoder)
    Object transcoder;
{
    Object text_sequence, gensymed_symbol, gensymed_symbol_1, temp, temp_1;
    Object schar_new_value, character_1, gensym_pop_store, cons_1, next_cons;
    Object thing_1;
    SI_Long translated_character, thing;

    x_note_fn_call(28,52);
    translated_character = (SI_Long)65535L;
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
  next_loop:
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	goto end_loop;
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)12L);
    gensymed_symbol_1 = transcoder;
    translated_character = IFIX(inline_funcall_1(gensymed_symbol,
	    gensymed_symbol_1));
    if ( !(translated_character == (SI_Long)65535L)) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = translated_character;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    temp_1 = Fill_pointer_for_current_gensym_string;
	    thing = translated_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,temp_1,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	if (ISVREF(transcoder,(SI_Long)5L)) {
	    character_1 = Nil;
	  next_loop_1:
	    gensym_pop_store = Nil;
	    cons_1 = ISVREF(transcoder,(SI_Long)5L);
	    if (cons_1) {
		gensym_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_gensym);
		if (ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_gensym_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = cons_1;
		}
		else {
		    temp = Available_gensym_conses_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = cons_1;
		    temp = Available_gensym_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    SVREF(transcoder,FIX((SI_Long)5L)) = next_cons;
	    character_1 = gensym_pop_store;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = character_1;
		twrite_wide_character(CHARACTERP(thing_1) ? 
			CHAR_CODE(thing_1) : thing_1);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		temp_1 = Fill_pointer_for_current_gensym_string;
		thing_1 = character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
			CHAR_CODE(thing_1) : thing_1);
		SET_SCHAR(temp,temp_1,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
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
Object export_as_string_for_transcoder(transcoder)
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

    x_note_fn_call(28,53);
    if (EQ(ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)6L),
		Qgensym_string)) {
	current_gensym_string = 
		obtain_simple_gensym_string(FIX((SI_Long)2048L));
	PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
		3);
	  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		  2);
	    total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		    1);
	      current_twriting_output_type = Qgensym_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
		gensymed_symbol = 
			ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			Qtype_description_of_unique_type_name_of_gensym_structure),
			(SI_Long)9L),(SI_Long)17L);
		gensymed_symbol_1 = transcoder;
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		result = copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		  3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
		  gensymed_symbol = 
			  ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qtype_description_of_unique_type_name_of_gensym_structure),
			  (SI_Long)9L),(SI_Long)17L);
		  gensymed_symbol_1 = transcoder;
		  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		  result = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

/* TWRITE-FOR-EXPORT-FROM-TRANSCODER-FOR-TRANSCODER */
Object twrite_for_export_from_transcoder_for_transcoder(transcoder)
    Object transcoder;
{
    Object text_sequence, gensymed_symbol, gensymed_symbol_1, temp, temp_1;
    Object schar_new_value, gensym_pop_store, cons_1, next_cons;
    Object simple_or_wide_character, thing_1;
    SI_Long translated_character, thing;

    x_note_fn_call(28,54);
    translated_character = (SI_Long)65535L;
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
  next_loop:
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	goto end_loop;
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)15L);
    gensymed_symbol_1 = transcoder;
    translated_character = IFIX(inline_funcall_1(gensymed_symbol,
	    gensymed_symbol_1));
    if ( !(translated_character == (SI_Long)65535L)) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = translated_character;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    temp_1 = Fill_pointer_for_current_gensym_string;
	    thing = translated_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,temp_1,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
    }
    if (ISVREF(transcoder,(SI_Long)5L)) {
      next_loop_1:
	gensym_pop_store = Nil;
	cons_1 = ISVREF(transcoder,(SI_Long)5L);
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = cons_1;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	SVREF(transcoder,FIX((SI_Long)5L)) = next_cons;
	simple_or_wide_character = gensym_pop_store;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = simple_or_wide_character;
	    twrite_wide_character(CHARACTERP(thing_1) ? CHAR_CODE(thing_1) 
		    : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    temp_1 = Fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp,temp_1,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
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
Object transcode_unhandled_character(character_1,transcoder)
    Object character_1, transcoder;
{
    Object spec;

    x_note_fn_call(28,55);
    spec = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)3L);
    if (EQ(Qnil,spec))
	return VALUES_1(FIX((SI_Long)65535L));
    else if (FIXNUMP(spec))
	return VALUES_1(spec);
    else
	return VALUES_1(FIX((SI_Long)65535L));
}

Object The_type_description_of_graphic_character_set = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_graphic_character_sets, Qchain_of_available_graphic_character_sets);

DEFINE_VARIABLE_WITH_SYMBOL(Graphic_character_set_count, Qgraphic_character_set_count);

Object Chain_of_available_graphic_character_sets_vector = UNBOUND;

/* GRAPHIC-CHARACTER-SET-STRUCTURE-MEMORY-USAGE */
Object graphic_character_set_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,56);
    temp = Graphic_character_set_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GRAPHIC-CHARACTER-SET-COUNT */
Object outstanding_graphic_character_set_count()
{
    Object def_structure_graphic_character_set_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,57);
    gensymed_symbol = IFIX(Graphic_character_set_count);
    def_structure_graphic_character_set_variable = 
	    Chain_of_available_graphic_character_sets;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_graphic_character_set_variable))
	goto end_loop;
    def_structure_graphic_character_set_variable = 
	    ISVREF(def_structure_graphic_character_set_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GRAPHIC-CHARACTER-SET-1 */
Object reclaim_graphic_character_set_1(graphic_character_set)
    Object graphic_character_set;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,58);
    inline_note_reclaim_cons(graphic_character_set,Nil);
    temp = ISVREF(Chain_of_available_graphic_character_sets_vector,
	    IFIX(Current_thread_index));
    SVREF(graphic_character_set,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_graphic_character_sets_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = graphic_character_set;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GRAPHIC-CHARACTER-SET */
Object reclaim_structure_for_graphic_character_set(graphic_character_set)
    Object graphic_character_set;
{
    x_note_fn_call(28,59);
    return reclaim_graphic_character_set_1(graphic_character_set);
}

static Object Qg2_defstruct_structure_name_graphic_character_set_g2_struct;  /* g2-defstruct-structure-name::graphic-character-set-g2-struct */

/* MAKE-PERMANENT-GRAPHIC-CHARACTER-SET-STRUCTURE-INTERNAL */
Object make_permanent_graphic_character_set_structure_internal()
{
    Object def_structure_graphic_character_set_variable;
    Object defstruct_g2_graphic_character_set_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,60);
    def_structure_graphic_character_set_variable = Nil;
    atomic_incff_symval(Qgraphic_character_set_count,FIX((SI_Long)1L));
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

static Object Qiso_646;            /* iso-646 */

static Object list_constant;       /* # */

static Object array_constant;      /* # */

/* MAKE-GRAPHIC-CHARACTER-SET-1 */
Object make_graphic_character_set_1()
{
    Object def_structure_graphic_character_set_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(28,61);
    def_structure_graphic_character_set_variable = 
	    ISVREF(Chain_of_available_graphic_character_sets_vector,
	    IFIX(Current_thread_index));
    if (def_structure_graphic_character_set_variable) {
	svref_arg_1 = Chain_of_available_graphic_character_sets_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_graphic_character_set_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_graphic_character_set_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graphic_character_set_g2_struct;
    }
    else
	def_structure_graphic_character_set_variable = 
		make_permanent_graphic_character_set_structure_internal();
    inline_note_allocate_cons(def_structure_graphic_character_set_variable,
	    Nil);
    SVREF(def_structure_graphic_character_set_variable,FIX((SI_Long)1L)) = 
	    Qiso_646;
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

Object Graphic_character_set_prop = UNBOUND;

/* MAP-CODE-TO-UNICODE-FUNCTION */
Object map_code_to_unicode_function(graphic_character_set,code)
    Object graphic_character_set, code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(28,62);
    gensymed_symbol = ISVREF(graphic_character_set,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)18L);
    gensymed_symbol_1 = graphic_character_set;
    gensymed_symbol_2 = code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FUNCTION */
Object map_unicode_to_code_if_any_function(graphic_character_set,
	    unicode_wide_character)
    Object graphic_character_set, unicode_wide_character;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(28,63);
    gensymed_symbol = ISVREF(graphic_character_set,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)19L);
    gensymed_symbol_1 = graphic_character_set;
    gensymed_symbol_2 = unicode_wide_character;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

Object Transcoder_creation_function_prop = UNBOUND;

Object The_type_description_of_iso_646 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_646s, Qchain_of_available_iso_646s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_646_count, Qiso_646_count);

Object Chain_of_available_iso_646s_vector = UNBOUND;

/* ISO-646-STRUCTURE-MEMORY-USAGE */
Object iso_646_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,64);
    temp = Iso_646_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-646-COUNT */
Object outstanding_iso_646_count()
{
    Object def_structure_iso_646_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,65);
    gensymed_symbol = IFIX(Iso_646_count);
    def_structure_iso_646_variable = Chain_of_available_iso_646s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_646_variable))
	goto end_loop;
    def_structure_iso_646_variable = ISVREF(def_structure_iso_646_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-646-1 */
Object reclaim_iso_646_1(iso_646)
    Object iso_646;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,66);
    inline_note_reclaim_cons(iso_646,Nil);
    temp = ISVREF(Chain_of_available_iso_646s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_646,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_646s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_646;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-646 */
Object reclaim_structure_for_iso_646(iso_646)
    Object iso_646;
{
    x_note_fn_call(28,67);
    return reclaim_iso_646_1(iso_646);
}

static Object Qg2_defstruct_structure_name_iso_646_g2_struct;  /* g2-defstruct-structure-name::iso-646-g2-struct */

/* MAKE-PERMANENT-ISO-646-STRUCTURE-INTERNAL */
Object make_permanent_iso_646_structure_internal()
{
    Object def_structure_iso_646_variable, defstruct_g2_iso_646_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,68);
    def_structure_iso_646_variable = Nil;
    atomic_incff_symval(Qiso_646_count,FIX((SI_Long)1L));
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
Object make_iso_646_1()
{
    Object def_structure_iso_646_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,69);
    def_structure_iso_646_variable = 
	    ISVREF(Chain_of_available_iso_646s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_646_variable) {
	svref_arg_1 = Chain_of_available_iso_646s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_646_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_646_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_646_g2_struct;
    }
    else
	def_structure_iso_646_variable = 
		make_permanent_iso_646_structure_internal();
    inline_note_allocate_cons(def_structure_iso_646_variable,Nil);
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)1L)) = Qiso_646;
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)2L)) = list_constant_1;
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)3L)) = FIX((SI_Long)1L);
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)4L)) = FIX((SI_Long)94L);
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)5L)) = array_constant_1;
    SVREF(def_structure_iso_646_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_iso_646_variable);
}

/* MAP-CODE-TO-UNICODE-FOR-ISO-646 */
Object map_code_to_unicode_for_iso_646(iso_646,code)
    Object iso_646, code;
{
    x_note_fn_call(28,70);
    return VALUES_1(code);
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-ISO-646 */
Object map_unicode_to_code_if_any_for_iso_646(iso_646,unicode_wide_character)
    Object iso_646, unicode_wide_character;
{
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(28,71);
    arg = (SI_Long)32L;
    arg_1 = IFIX(unicode_wide_character);
    arg_2 = (SI_Long)127L;
    if (arg <= arg_1 && arg_1 <= arg_2)
	return VALUES_1(unicode_wide_character);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_iso_8859_abstract = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_abstracts, Qchain_of_available_iso_8859_abstracts);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_abstract_count, Qiso_8859_abstract_count);

Object Chain_of_available_iso_8859_abstracts_vector = UNBOUND;

/* ISO-8859-ABSTRACT-STRUCTURE-MEMORY-USAGE */
Object iso_8859_abstract_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,72);
    temp = Iso_8859_abstract_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-ABSTRACT-COUNT */
Object outstanding_iso_8859_abstract_count()
{
    Object def_structure_iso_8859_abstract_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,73);
    gensymed_symbol = IFIX(Iso_8859_abstract_count);
    def_structure_iso_8859_abstract_variable = 
	    Chain_of_available_iso_8859_abstracts;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_abstract_variable))
	goto end_loop;
    def_structure_iso_8859_abstract_variable = 
	    ISVREF(def_structure_iso_8859_abstract_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-ABSTRACT-1 */
Object reclaim_iso_8859_abstract_1(iso_8859_abstract)
    Object iso_8859_abstract;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,74);
    inline_note_reclaim_cons(iso_8859_abstract,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_abstracts_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_abstract,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_abstracts_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_abstract;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-ABSTRACT */
Object reclaim_structure_for_iso_8859_abstract(iso_8859_abstract)
    Object iso_8859_abstract;
{
    x_note_fn_call(28,75);
    return reclaim_iso_8859_abstract_1(iso_8859_abstract);
}

static Object Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct;  /* g2-defstruct-structure-name::iso-8859-abstract-g2-struct */

/* MAKE-PERMANENT-ISO-8859-ABSTRACT-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_abstract_structure_internal()
{
    Object def_structure_iso_8859_abstract_variable;
    Object defstruct_g2_iso_8859_abstract_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,76);
    def_structure_iso_8859_abstract_variable = Nil;
    atomic_incff_symval(Qiso_8859_abstract_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_abstract;  /* iso-8859-abstract */

/* MAKE-ISO-8859-ABSTRACT-1 */
Object make_iso_8859_abstract_1()
{
    Object def_structure_iso_8859_abstract_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,77);
    def_structure_iso_8859_abstract_variable = 
	    ISVREF(Chain_of_available_iso_8859_abstracts_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_abstract_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_abstracts_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_abstract_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct;
    }
    else
	def_structure_iso_8859_abstract_variable = 
		make_permanent_iso_8859_abstract_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_abstract_variable,Nil);
    SVREF(def_structure_iso_8859_abstract_variable,FIX((SI_Long)1L)) = 
	    Qiso_8859_abstract;
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
Object map_code_to_unicode_for_iso_8859_abstract(iso_8859_abstract,code)
    Object iso_8859_abstract, code;
{
    x_note_fn_call(28,78);
    return VALUES_1(FIX(UBYTE_16_ISAREF_1(ISVREF(iso_8859_abstract,
	    (SI_Long)8L),IFIX(code))));
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_8859_reverse_unicode_map_hash_vector_43_vectors, Qavailable_8859_reverse_unicode_map_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_8859_reverse_unicode_map_hash_vector_43_vectors, Qcount_of_8859_reverse_unicode_map_hash_vector_43_vectors);

Object Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector = UNBOUND;

/* 8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object n_8859_reverse_unicode_map_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(28,79);
    temp = Count_of_8859_reverse_unicode_map_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS */
Object out_8859_reverse_unicode_map_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(28,80);
    temp = 
	    FIXNUM_MINUS(Count_of_8859_reverse_unicode_map_hash_vector_43_vectors,
	    length(Available_8859_reverse_unicode_map_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_8859_reverse_unicode_map_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(28,81);
    atomic_incff_symval(Qcount_of_8859_reverse_unicode_map_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-8859-REVERSE-UNICODE-MAP-HASH-VECTOR */
Object make_8859_reverse_unicode_map_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(28,82);
    if (ISVREF(Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = 
		make_permanent_8859_reverse_unicode_map_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-8859-REVERSE-UNICODE-MAP-HASH-VECTOR */
Object reclaim_8859_reverse_unicode_map_hash_vector(n_8859_reverse_unicode_map_hash_vector_43_vector)
    Object n_8859_reverse_unicode_map_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(28,83);
    svref_arg_1 = 
	    Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = n_8859_reverse_unicode_map_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qlookup;             /* lookup */

/* RECLAIM-8859-REVERSE-UNICODE-MAP-TREE-FOR-HASH-LEAVES */
Object reclaim_8859_reverse_unicode_map_tree_for_hash_leaves(n_8859_reverse_unicode_map_tree_for_hash_binary_tree)
    Object n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, temp, svref_arg_2, last_1, next_qm, temp_1;

    x_note_fn_call(28,84);
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
    reclaim_binary_tree_element_1(n_8859_reverse_unicode_map_tree_for_hash_binary_tree);
    alist_entry = Nil;
    ab_loop_list_ = alist;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    inline_note_reclaim_cons(alist_entry,Qlookup);
    if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = alist_entry;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
    }
    else {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
    }
    M_CDR(alist_entry) = Nil;
    goto next_loop_1;
  end_loop_1:;
    if (alist) {
	last_1 = alist;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = alist;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = alist;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    if (less_than_branch_qm && greater_than_branch_qm) {
	reclaim_8859_reverse_unicode_map_tree_for_hash_leaves(less_than_branch_qm);
	n_8859_reverse_unicode_map_tree_for_hash_binary_tree = 
		greater_than_branch_qm;
    }
    else {
	temp_1 = less_than_branch_qm;
	if (temp_1);
	else
	    temp_1 = greater_than_branch_qm;
	n_8859_reverse_unicode_map_tree_for_hash_binary_tree = temp_1;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-8859-REVERSE-UNICODE-MAP-TREE */
Object clear_8859_reverse_unicode_map_tree(n_8859_reverse_unicode_map_tree_for_hash_binary_tree)
    Object n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(28,85);
    element_qm = CDR(n_8859_reverse_unicode_map_tree_for_hash_binary_tree);
    if (element_qm) {
	reclaim_8859_reverse_unicode_map_tree_for_hash_leaves(element_qm);
	M_CDR(n_8859_reverse_unicode_map_tree_for_hash_binary_tree) = Nil;
    }
    return VALUES_1(n_8859_reverse_unicode_map_tree_for_hash_binary_tree);
}

static Object Q8859_reverse_unicode_map_tree_for_hash;  /* 8859-reverse-unicode-map-tree-for-hash */

/* MAKE-8859-REVERSE-UNICODE-MAP */
Object make_8859_reverse_unicode_map()
{
    Object new_vector, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(28,86);
    new_vector = make_8859_reverse_unicode_map_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    new_cons = ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Q8859_reverse_unicode_map_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-8859-REVERSE-UNICODE-MAP */
Object flatten_8859_reverse_unicode_map(n_8859_reverse_unicode_map_hash_table)
    Object n_8859_reverse_unicode_map_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(28,87);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(n_8859_reverse_unicode_map_hash_table,index_1);
    if (subtree) {
	temp = flatten_binary_tree(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-8859-REVERSE-UNICODE-MAP */
Object clear_8859_reverse_unicode_map(n_8859_reverse_unicode_map_hash_table)
    Object n_8859_reverse_unicode_map_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(28,88);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_8859_reverse_unicode_map_tree(ISVREF(n_8859_reverse_unicode_map_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-8859-REVERSE-UNICODE-MAP */
Object reclaim_8859_reverse_unicode_map(n_8859_reverse_unicode_map_hash_table)
    Object n_8859_reverse_unicode_map_hash_table;
{
    Object n_8859_reverse_unicode_map_tree_for_hash_binary_tree, element_qm;
    Object temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(28,89);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    n_8859_reverse_unicode_map_tree_for_hash_binary_tree = 
	    ISVREF(n_8859_reverse_unicode_map_hash_table,index_1);
    element_qm = M_CDR(n_8859_reverse_unicode_map_tree_for_hash_binary_tree);
    if (element_qm)
	reclaim_8859_reverse_unicode_map_tree_for_hash_leaves(element_qm);
    inline_note_reclaim_cons(n_8859_reverse_unicode_map_tree_for_hash_binary_tree,
	    Qlookup);
    if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
    }
    else {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		n_8859_reverse_unicode_map_tree_for_hash_binary_tree;
    }
    M_CDR(n_8859_reverse_unicode_map_tree_for_hash_binary_tree) = Nil;
    ISVREF(n_8859_reverse_unicode_map_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_8859_reverse_unicode_map_hash_vector(n_8859_reverse_unicode_map_hash_table);
    return VALUES_1(temp_1);
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-ISO-8859-ABSTRACT */
Object map_unicode_to_code_if_any_for_iso_8859_abstract(iso_8859_abstract,
	    unicode_wide_character)
    Object iso_8859_abstract, unicode_wide_character;
{
    Object temp, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(28,90);
    gensymed_symbol = IFIX(sxhashw(unicode_wide_character));
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

Object The_type_description_of_iso_8859_1 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_1s, Qchain_of_available_iso_8859_1s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_1_count, Qiso_8859_1_count);

Object Chain_of_available_iso_8859_1s_vector = UNBOUND;

/* ISO-8859-1-STRUCTURE-MEMORY-USAGE */
Object iso_8859_1_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,91);
    temp = Iso_8859_1_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-1-COUNT */
Object outstanding_iso_8859_1_count()
{
    Object def_structure_iso_8859_1_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,92);
    gensymed_symbol = IFIX(Iso_8859_1_count);
    def_structure_iso_8859_1_variable = Chain_of_available_iso_8859_1s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_1_variable))
	goto end_loop;
    def_structure_iso_8859_1_variable = 
	    ISVREF(def_structure_iso_8859_1_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-1-1 */
Object reclaim_iso_8859_1_1(iso_8859_1)
    Object iso_8859_1;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,93);
    inline_note_reclaim_cons(iso_8859_1,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_1s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_1,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_1s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_1;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-1 */
Object reclaim_structure_for_iso_8859_1(iso_8859_1)
    Object iso_8859_1;
{
    x_note_fn_call(28,94);
    return reclaim_iso_8859_1_1(iso_8859_1);
}

static Object Qg2_defstruct_structure_name_iso_8859_1_g2_struct;  /* g2-defstruct-structure-name::iso-8859-1-g2-struct */

/* MAKE-PERMANENT-ISO-8859-1-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_1_structure_internal()
{
    Object def_structure_iso_8859_1_variable, defstruct_g2_iso_8859_1_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,95);
    def_structure_iso_8859_1_variable = Nil;
    atomic_incff_symval(Qiso_8859_1_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_1;         /* iso-8859-1 */

static Object list_constant_2;     /* # */

/* MAKE-ISO-8859-1-1 */
Object make_iso_8859_1_1()
{
    Object def_structure_iso_8859_1_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,96);
    def_structure_iso_8859_1_variable = 
	    ISVREF(Chain_of_available_iso_8859_1s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_1_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_1s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_1_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_1_g2_struct;
    }
    else
	def_structure_iso_8859_1_variable = 
		make_permanent_iso_8859_1_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_1_variable,Nil);
    SVREF(def_structure_iso_8859_1_variable,FIX((SI_Long)1L)) = Qiso_8859_1;
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

Object The_type_description_of_iso_8859_2 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_2s, Qchain_of_available_iso_8859_2s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_2_count, Qiso_8859_2_count);

Object Chain_of_available_iso_8859_2s_vector = UNBOUND;

/* ISO-8859-2-STRUCTURE-MEMORY-USAGE */
Object iso_8859_2_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,97);
    temp = Iso_8859_2_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-2-COUNT */
Object outstanding_iso_8859_2_count()
{
    Object def_structure_iso_8859_2_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,98);
    gensymed_symbol = IFIX(Iso_8859_2_count);
    def_structure_iso_8859_2_variable = Chain_of_available_iso_8859_2s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_2_variable))
	goto end_loop;
    def_structure_iso_8859_2_variable = 
	    ISVREF(def_structure_iso_8859_2_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-2-1 */
Object reclaim_iso_8859_2_1(iso_8859_2)
    Object iso_8859_2;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,99);
    inline_note_reclaim_cons(iso_8859_2,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_2s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_2,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_2s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_2;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-2 */
Object reclaim_structure_for_iso_8859_2(iso_8859_2)
    Object iso_8859_2;
{
    x_note_fn_call(28,100);
    return reclaim_iso_8859_2_1(iso_8859_2);
}

static Object Qg2_defstruct_structure_name_iso_8859_2_g2_struct;  /* g2-defstruct-structure-name::iso-8859-2-g2-struct */

/* MAKE-PERMANENT-ISO-8859-2-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_2_structure_internal()
{
    Object def_structure_iso_8859_2_variable, defstruct_g2_iso_8859_2_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,101);
    def_structure_iso_8859_2_variable = Nil;
    atomic_incff_symval(Qiso_8859_2_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_2;         /* iso-8859-2 */

static Object list_constant_3;     /* # */

/* MAKE-ISO-8859-2-1 */
Object make_iso_8859_2_1()
{
    Object def_structure_iso_8859_2_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,102);
    def_structure_iso_8859_2_variable = 
	    ISVREF(Chain_of_available_iso_8859_2s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_2_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_2s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_2_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_2_g2_struct;
    }
    else
	def_structure_iso_8859_2_variable = 
		make_permanent_iso_8859_2_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_2_variable,Nil);
    SVREF(def_structure_iso_8859_2_variable,FIX((SI_Long)1L)) = Qiso_8859_2;
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

Object The_type_description_of_iso_8859_3 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_3s, Qchain_of_available_iso_8859_3s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_3_count, Qiso_8859_3_count);

Object Chain_of_available_iso_8859_3s_vector = UNBOUND;

/* ISO-8859-3-STRUCTURE-MEMORY-USAGE */
Object iso_8859_3_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,103);
    temp = Iso_8859_3_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-3-COUNT */
Object outstanding_iso_8859_3_count()
{
    Object def_structure_iso_8859_3_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,104);
    gensymed_symbol = IFIX(Iso_8859_3_count);
    def_structure_iso_8859_3_variable = Chain_of_available_iso_8859_3s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_3_variable))
	goto end_loop;
    def_structure_iso_8859_3_variable = 
	    ISVREF(def_structure_iso_8859_3_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-3-1 */
Object reclaim_iso_8859_3_1(iso_8859_3)
    Object iso_8859_3;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,105);
    inline_note_reclaim_cons(iso_8859_3,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_3s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_3,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_3s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_3;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-3 */
Object reclaim_structure_for_iso_8859_3(iso_8859_3)
    Object iso_8859_3;
{
    x_note_fn_call(28,106);
    return reclaim_iso_8859_3_1(iso_8859_3);
}

static Object Qg2_defstruct_structure_name_iso_8859_3_g2_struct;  /* g2-defstruct-structure-name::iso-8859-3-g2-struct */

/* MAKE-PERMANENT-ISO-8859-3-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_3_structure_internal()
{
    Object def_structure_iso_8859_3_variable, defstruct_g2_iso_8859_3_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,107);
    def_structure_iso_8859_3_variable = Nil;
    atomic_incff_symval(Qiso_8859_3_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_3;         /* iso-8859-3 */

static Object list_constant_4;     /* # */

static Object array_constant_2;    /* # */

/* MAKE-ISO-8859-3-1 */
Object make_iso_8859_3_1()
{
    Object def_structure_iso_8859_3_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,108);
    def_structure_iso_8859_3_variable = 
	    ISVREF(Chain_of_available_iso_8859_3s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_3_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_3s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_3_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_3_g2_struct;
    }
    else
	def_structure_iso_8859_3_variable = 
		make_permanent_iso_8859_3_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_3_variable,Nil);
    SVREF(def_structure_iso_8859_3_variable,FIX((SI_Long)1L)) = Qiso_8859_3;
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

Object The_type_description_of_iso_8859_4 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_4s, Qchain_of_available_iso_8859_4s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_4_count, Qiso_8859_4_count);

Object Chain_of_available_iso_8859_4s_vector = UNBOUND;

/* ISO-8859-4-STRUCTURE-MEMORY-USAGE */
Object iso_8859_4_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,109);
    temp = Iso_8859_4_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-4-COUNT */
Object outstanding_iso_8859_4_count()
{
    Object def_structure_iso_8859_4_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,110);
    gensymed_symbol = IFIX(Iso_8859_4_count);
    def_structure_iso_8859_4_variable = Chain_of_available_iso_8859_4s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_4_variable))
	goto end_loop;
    def_structure_iso_8859_4_variable = 
	    ISVREF(def_structure_iso_8859_4_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-4-1 */
Object reclaim_iso_8859_4_1(iso_8859_4)
    Object iso_8859_4;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,111);
    inline_note_reclaim_cons(iso_8859_4,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_4s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_4,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_4s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_4;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-4 */
Object reclaim_structure_for_iso_8859_4(iso_8859_4)
    Object iso_8859_4;
{
    x_note_fn_call(28,112);
    return reclaim_iso_8859_4_1(iso_8859_4);
}

static Object Qg2_defstruct_structure_name_iso_8859_4_g2_struct;  /* g2-defstruct-structure-name::iso-8859-4-g2-struct */

/* MAKE-PERMANENT-ISO-8859-4-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_4_structure_internal()
{
    Object def_structure_iso_8859_4_variable, defstruct_g2_iso_8859_4_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,113);
    def_structure_iso_8859_4_variable = Nil;
    atomic_incff_symval(Qiso_8859_4_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_4;         /* iso-8859-4 */

static Object list_constant_5;     /* # */

static Object array_constant_3;    /* # */

/* MAKE-ISO-8859-4-1 */
Object make_iso_8859_4_1()
{
    Object def_structure_iso_8859_4_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,114);
    def_structure_iso_8859_4_variable = 
	    ISVREF(Chain_of_available_iso_8859_4s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_4_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_4s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_4_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_4_g2_struct;
    }
    else
	def_structure_iso_8859_4_variable = 
		make_permanent_iso_8859_4_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_4_variable,Nil);
    SVREF(def_structure_iso_8859_4_variable,FIX((SI_Long)1L)) = Qiso_8859_4;
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

Object The_type_description_of_iso_8859_5 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_5s, Qchain_of_available_iso_8859_5s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_5_count, Qiso_8859_5_count);

Object Chain_of_available_iso_8859_5s_vector = UNBOUND;

/* ISO-8859-5-STRUCTURE-MEMORY-USAGE */
Object iso_8859_5_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,115);
    temp = Iso_8859_5_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-5-COUNT */
Object outstanding_iso_8859_5_count()
{
    Object def_structure_iso_8859_5_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,116);
    gensymed_symbol = IFIX(Iso_8859_5_count);
    def_structure_iso_8859_5_variable = Chain_of_available_iso_8859_5s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_5_variable))
	goto end_loop;
    def_structure_iso_8859_5_variable = 
	    ISVREF(def_structure_iso_8859_5_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-5-1 */
Object reclaim_iso_8859_5_1(iso_8859_5)
    Object iso_8859_5;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,117);
    inline_note_reclaim_cons(iso_8859_5,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_5s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_5,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_5s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_5;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-5 */
Object reclaim_structure_for_iso_8859_5(iso_8859_5)
    Object iso_8859_5;
{
    x_note_fn_call(28,118);
    return reclaim_iso_8859_5_1(iso_8859_5);
}

static Object Qg2_defstruct_structure_name_iso_8859_5_g2_struct;  /* g2-defstruct-structure-name::iso-8859-5-g2-struct */

/* MAKE-PERMANENT-ISO-8859-5-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_5_structure_internal()
{
    Object def_structure_iso_8859_5_variable, defstruct_g2_iso_8859_5_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,119);
    def_structure_iso_8859_5_variable = Nil;
    atomic_incff_symval(Qiso_8859_5_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_5;         /* iso-8859-5 */

static Object list_constant_6;     /* # */

static Object array_constant_4;    /* # */

/* MAKE-ISO-8859-5-1 */
Object make_iso_8859_5_1()
{
    Object def_structure_iso_8859_5_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,120);
    def_structure_iso_8859_5_variable = 
	    ISVREF(Chain_of_available_iso_8859_5s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_5_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_5s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_5_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_5_g2_struct;
    }
    else
	def_structure_iso_8859_5_variable = 
		make_permanent_iso_8859_5_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_5_variable,Nil);
    SVREF(def_structure_iso_8859_5_variable,FIX((SI_Long)1L)) = Qiso_8859_5;
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

Object The_type_description_of_iso_8859_6 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_6s, Qchain_of_available_iso_8859_6s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_6_count, Qiso_8859_6_count);

Object Chain_of_available_iso_8859_6s_vector = UNBOUND;

/* ISO-8859-6-STRUCTURE-MEMORY-USAGE */
Object iso_8859_6_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,121);
    temp = Iso_8859_6_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-6-COUNT */
Object outstanding_iso_8859_6_count()
{
    Object def_structure_iso_8859_6_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,122);
    gensymed_symbol = IFIX(Iso_8859_6_count);
    def_structure_iso_8859_6_variable = Chain_of_available_iso_8859_6s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_6_variable))
	goto end_loop;
    def_structure_iso_8859_6_variable = 
	    ISVREF(def_structure_iso_8859_6_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-6-1 */
Object reclaim_iso_8859_6_1(iso_8859_6)
    Object iso_8859_6;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,123);
    inline_note_reclaim_cons(iso_8859_6,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_6s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_6,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_6s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_6;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-6 */
Object reclaim_structure_for_iso_8859_6(iso_8859_6)
    Object iso_8859_6;
{
    x_note_fn_call(28,124);
    return reclaim_iso_8859_6_1(iso_8859_6);
}

static Object Qg2_defstruct_structure_name_iso_8859_6_g2_struct;  /* g2-defstruct-structure-name::iso-8859-6-g2-struct */

/* MAKE-PERMANENT-ISO-8859-6-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_6_structure_internal()
{
    Object def_structure_iso_8859_6_variable, defstruct_g2_iso_8859_6_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,125);
    def_structure_iso_8859_6_variable = Nil;
    atomic_incff_symval(Qiso_8859_6_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_6;         /* iso-8859-6 */

static Object list_constant_7;     /* # */

static Object array_constant_5;    /* # */

/* MAKE-ISO-8859-6-1 */
Object make_iso_8859_6_1()
{
    Object def_structure_iso_8859_6_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,126);
    def_structure_iso_8859_6_variable = 
	    ISVREF(Chain_of_available_iso_8859_6s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_6_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_6s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_6_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_6_g2_struct;
    }
    else
	def_structure_iso_8859_6_variable = 
		make_permanent_iso_8859_6_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_6_variable,Nil);
    SVREF(def_structure_iso_8859_6_variable,FIX((SI_Long)1L)) = Qiso_8859_6;
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

Object The_type_description_of_iso_8859_7 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_7s, Qchain_of_available_iso_8859_7s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_7_count, Qiso_8859_7_count);

Object Chain_of_available_iso_8859_7s_vector = UNBOUND;

/* ISO-8859-7-STRUCTURE-MEMORY-USAGE */
Object iso_8859_7_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,127);
    temp = Iso_8859_7_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-7-COUNT */
Object outstanding_iso_8859_7_count()
{
    Object def_structure_iso_8859_7_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,128);
    gensymed_symbol = IFIX(Iso_8859_7_count);
    def_structure_iso_8859_7_variable = Chain_of_available_iso_8859_7s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_7_variable))
	goto end_loop;
    def_structure_iso_8859_7_variable = 
	    ISVREF(def_structure_iso_8859_7_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-7-1 */
Object reclaim_iso_8859_7_1(iso_8859_7)
    Object iso_8859_7;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,129);
    inline_note_reclaim_cons(iso_8859_7,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_7s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_7,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_7s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_7;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-7 */
Object reclaim_structure_for_iso_8859_7(iso_8859_7)
    Object iso_8859_7;
{
    x_note_fn_call(28,130);
    return reclaim_iso_8859_7_1(iso_8859_7);
}

static Object Qg2_defstruct_structure_name_iso_8859_7_g2_struct;  /* g2-defstruct-structure-name::iso-8859-7-g2-struct */

/* MAKE-PERMANENT-ISO-8859-7-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_7_structure_internal()
{
    Object def_structure_iso_8859_7_variable, defstruct_g2_iso_8859_7_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,131);
    def_structure_iso_8859_7_variable = Nil;
    atomic_incff_symval(Qiso_8859_7_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_7;         /* iso-8859-7 */

static Object list_constant_8;     /* # */

static Object array_constant_6;    /* # */

/* MAKE-ISO-8859-7-1 */
Object make_iso_8859_7_1()
{
    Object def_structure_iso_8859_7_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,132);
    def_structure_iso_8859_7_variable = 
	    ISVREF(Chain_of_available_iso_8859_7s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_7_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_7s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_7_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_7_g2_struct;
    }
    else
	def_structure_iso_8859_7_variable = 
		make_permanent_iso_8859_7_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_7_variable,Nil);
    SVREF(def_structure_iso_8859_7_variable,FIX((SI_Long)1L)) = Qiso_8859_7;
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

Object The_type_description_of_iso_8859_8 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_8s, Qchain_of_available_iso_8859_8s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_8_count, Qiso_8859_8_count);

Object Chain_of_available_iso_8859_8s_vector = UNBOUND;

/* ISO-8859-8-STRUCTURE-MEMORY-USAGE */
Object iso_8859_8_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,133);
    temp = Iso_8859_8_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-8-COUNT */
Object outstanding_iso_8859_8_count()
{
    Object def_structure_iso_8859_8_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,134);
    gensymed_symbol = IFIX(Iso_8859_8_count);
    def_structure_iso_8859_8_variable = Chain_of_available_iso_8859_8s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_8_variable))
	goto end_loop;
    def_structure_iso_8859_8_variable = 
	    ISVREF(def_structure_iso_8859_8_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-8-1 */
Object reclaim_iso_8859_8_1(iso_8859_8)
    Object iso_8859_8;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,135);
    inline_note_reclaim_cons(iso_8859_8,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_8s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_8,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_8s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_8;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-8 */
Object reclaim_structure_for_iso_8859_8(iso_8859_8)
    Object iso_8859_8;
{
    x_note_fn_call(28,136);
    return reclaim_iso_8859_8_1(iso_8859_8);
}

static Object Qg2_defstruct_structure_name_iso_8859_8_g2_struct;  /* g2-defstruct-structure-name::iso-8859-8-g2-struct */

/* MAKE-PERMANENT-ISO-8859-8-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_8_structure_internal()
{
    Object def_structure_iso_8859_8_variable, defstruct_g2_iso_8859_8_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,137);
    def_structure_iso_8859_8_variable = Nil;
    atomic_incff_symval(Qiso_8859_8_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_8;         /* iso-8859-8 */

static Object list_constant_9;     /* # */

static Object array_constant_7;    /* # */

/* MAKE-ISO-8859-8-1 */
Object make_iso_8859_8_1()
{
    Object def_structure_iso_8859_8_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,138);
    def_structure_iso_8859_8_variable = 
	    ISVREF(Chain_of_available_iso_8859_8s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_8_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_8s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_8_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_8_g2_struct;
    }
    else
	def_structure_iso_8859_8_variable = 
		make_permanent_iso_8859_8_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_8_variable,Nil);
    SVREF(def_structure_iso_8859_8_variable,FIX((SI_Long)1L)) = Qiso_8859_8;
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

Object The_type_description_of_iso_8859_9 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_9s, Qchain_of_available_iso_8859_9s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_9_count, Qiso_8859_9_count);

Object Chain_of_available_iso_8859_9s_vector = UNBOUND;

/* ISO-8859-9-STRUCTURE-MEMORY-USAGE */
Object iso_8859_9_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,139);
    temp = Iso_8859_9_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-9-COUNT */
Object outstanding_iso_8859_9_count()
{
    Object def_structure_iso_8859_9_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,140);
    gensymed_symbol = IFIX(Iso_8859_9_count);
    def_structure_iso_8859_9_variable = Chain_of_available_iso_8859_9s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_9_variable))
	goto end_loop;
    def_structure_iso_8859_9_variable = 
	    ISVREF(def_structure_iso_8859_9_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-9-1 */
Object reclaim_iso_8859_9_1(iso_8859_9)
    Object iso_8859_9;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,141);
    inline_note_reclaim_cons(iso_8859_9,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_9s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_9,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_9s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_9;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-9 */
Object reclaim_structure_for_iso_8859_9(iso_8859_9)
    Object iso_8859_9;
{
    x_note_fn_call(28,142);
    return reclaim_iso_8859_9_1(iso_8859_9);
}

static Object Qg2_defstruct_structure_name_iso_8859_9_g2_struct;  /* g2-defstruct-structure-name::iso-8859-9-g2-struct */

/* MAKE-PERMANENT-ISO-8859-9-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_9_structure_internal()
{
    Object def_structure_iso_8859_9_variable, defstruct_g2_iso_8859_9_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,143);
    def_structure_iso_8859_9_variable = Nil;
    atomic_incff_symval(Qiso_8859_9_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_9;         /* iso-8859-9 */

static Object list_constant_10;    /* # */

static Object array_constant_8;    /* # */

/* MAKE-ISO-8859-9-1 */
Object make_iso_8859_9_1()
{
    Object def_structure_iso_8859_9_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,144);
    def_structure_iso_8859_9_variable = 
	    ISVREF(Chain_of_available_iso_8859_9s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_9_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_9s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_9_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_9_g2_struct;
    }
    else
	def_structure_iso_8859_9_variable = 
		make_permanent_iso_8859_9_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_9_variable,Nil);
    SVREF(def_structure_iso_8859_9_variable,FIX((SI_Long)1L)) = Qiso_8859_9;
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

Object The_type_description_of_iso_8859_10 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_10s, Qchain_of_available_iso_8859_10s);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_10_count, Qiso_8859_10_count);

Object Chain_of_available_iso_8859_10s_vector = UNBOUND;

/* ISO-8859-10-STRUCTURE-MEMORY-USAGE */
Object iso_8859_10_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,145);
    temp = Iso_8859_10_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-10-COUNT */
Object outstanding_iso_8859_10_count()
{
    Object def_structure_iso_8859_10_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,146);
    gensymed_symbol = IFIX(Iso_8859_10_count);
    def_structure_iso_8859_10_variable = Chain_of_available_iso_8859_10s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_10_variable))
	goto end_loop;
    def_structure_iso_8859_10_variable = 
	    ISVREF(def_structure_iso_8859_10_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-10-1 */
Object reclaim_iso_8859_10_1(iso_8859_10)
    Object iso_8859_10;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,147);
    inline_note_reclaim_cons(iso_8859_10,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_10s_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_10,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_10s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_10;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-10 */
Object reclaim_structure_for_iso_8859_10(iso_8859_10)
    Object iso_8859_10;
{
    x_note_fn_call(28,148);
    return reclaim_iso_8859_10_1(iso_8859_10);
}

static Object Qg2_defstruct_structure_name_iso_8859_10_g2_struct;  /* g2-defstruct-structure-name::iso-8859-10-g2-struct */

/* MAKE-PERMANENT-ISO-8859-10-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_10_structure_internal()
{
    Object def_structure_iso_8859_10_variable;
    Object defstruct_g2_iso_8859_10_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,149);
    def_structure_iso_8859_10_variable = Nil;
    atomic_incff_symval(Qiso_8859_10_count,FIX((SI_Long)1L));
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

static Object Qiso_8859_10;        /* iso-8859-10 */

static Object list_constant_11;    /* # */

/* MAKE-ISO-8859-10-1 */
Object make_iso_8859_10_1()
{
    Object def_structure_iso_8859_10_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,150);
    def_structure_iso_8859_10_variable = 
	    ISVREF(Chain_of_available_iso_8859_10s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_10_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_10s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_iso_8859_10_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_iso_8859_10_g2_struct;
    }
    else
	def_structure_iso_8859_10_variable = 
		make_permanent_iso_8859_10_structure_internal();
    inline_note_allocate_cons(def_structure_iso_8859_10_variable,Nil);
    SVREF(def_structure_iso_8859_10_variable,FIX((SI_Long)1L)) = Qiso_8859_10;
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

Object The_type_description_of_asian_double_byte = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_asian_double_bytes, Qchain_of_available_asian_double_bytes);

DEFINE_VARIABLE_WITH_SYMBOL(Asian_double_byte_count, Qasian_double_byte_count);

Object Chain_of_available_asian_double_bytes_vector = UNBOUND;

/* ASIAN-DOUBLE-BYTE-STRUCTURE-MEMORY-USAGE */
Object asian_double_byte_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,151);
    temp = Asian_double_byte_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ASIAN-DOUBLE-BYTE-COUNT */
Object outstanding_asian_double_byte_count()
{
    Object def_structure_asian_double_byte_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,152);
    gensymed_symbol = IFIX(Asian_double_byte_count);
    def_structure_asian_double_byte_variable = 
	    Chain_of_available_asian_double_bytes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_asian_double_byte_variable))
	goto end_loop;
    def_structure_asian_double_byte_variable = 
	    ISVREF(def_structure_asian_double_byte_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ASIAN-DOUBLE-BYTE-1 */
Object reclaim_asian_double_byte_1(asian_double_byte)
    Object asian_double_byte;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,153);
    inline_note_reclaim_cons(asian_double_byte,Nil);
    temp = ISVREF(Chain_of_available_asian_double_bytes_vector,
	    IFIX(Current_thread_index));
    SVREF(asian_double_byte,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_asian_double_bytes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = asian_double_byte;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ASIAN-DOUBLE-BYTE */
Object reclaim_structure_for_asian_double_byte(asian_double_byte)
    Object asian_double_byte;
{
    x_note_fn_call(28,154);
    return reclaim_asian_double_byte_1(asian_double_byte);
}

static Object Qg2_defstruct_structure_name_asian_double_byte_g2_struct;  /* g2-defstruct-structure-name::asian-double-byte-g2-struct */

/* MAKE-PERMANENT-ASIAN-DOUBLE-BYTE-STRUCTURE-INTERNAL */
Object make_permanent_asian_double_byte_structure_internal()
{
    Object def_structure_asian_double_byte_variable;
    Object defstruct_g2_asian_double_byte_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,155);
    def_structure_asian_double_byte_variable = Nil;
    atomic_incff_symval(Qasian_double_byte_count,FIX((SI_Long)1L));
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

static Object Qasian_double_byte;  /* asian-double-byte */

/* MAKE-ASIAN-DOUBLE-BYTE-1 */
Object make_asian_double_byte_1()
{
    Object def_structure_asian_double_byte_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,156);
    def_structure_asian_double_byte_variable = 
	    ISVREF(Chain_of_available_asian_double_bytes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_asian_double_byte_variable) {
	svref_arg_1 = Chain_of_available_asian_double_bytes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_asian_double_byte_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_asian_double_byte_g2_struct;
    }
    else
	def_structure_asian_double_byte_variable = 
		make_permanent_asian_double_byte_structure_internal();
    inline_note_allocate_cons(def_structure_asian_double_byte_variable,Nil);
    SVREF(def_structure_asian_double_byte_variable,FIX((SI_Long)1L)) = 
	    Qasian_double_byte;
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
Object map_code_to_unicode_for_asian_double_byte(asian_double_byte,code)
    Object asian_double_byte, code;
{
    Object row, column, row_map_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(28,157);
    row = FIX((IFIX(code) >>  -  - (SI_Long)8L & (SI_Long)127L) - 
	    (SI_Long)32L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,1);
      column = FIX((IFIX(code) & (SI_Long)127L) - (SI_Long)32L);
      PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,0);
	row_map_qm = ISVREF(ISVREF(asian_double_byte,(SI_Long)7L),IFIX(Row));
	if (row_map_qm)
	    result = VALUES_1(FIX(UBYTE_16_ISAREF_1(row_map_qm,IFIX(Column))));
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object The_type_description_of_jis_x_0208 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_jis_x_0208s, Qchain_of_available_jis_x_0208s);

DEFINE_VARIABLE_WITH_SYMBOL(Jis_x_0208_count, Qjis_x_0208_count);

Object Chain_of_available_jis_x_0208s_vector = UNBOUND;

/* JIS-X-0208-STRUCTURE-MEMORY-USAGE */
Object jis_x_0208_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,158);
    temp = Jis_x_0208_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JIS-X-0208-COUNT */
Object outstanding_jis_x_0208_count()
{
    Object def_structure_jis_x_0208_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,159);
    gensymed_symbol = IFIX(Jis_x_0208_count);
    def_structure_jis_x_0208_variable = Chain_of_available_jis_x_0208s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_jis_x_0208_variable))
	goto end_loop;
    def_structure_jis_x_0208_variable = 
	    ISVREF(def_structure_jis_x_0208_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-JIS-X-0208-1 */
Object reclaim_jis_x_0208_1(jis_x_0208)
    Object jis_x_0208;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,160);
    inline_note_reclaim_cons(jis_x_0208,Nil);
    temp = ISVREF(Chain_of_available_jis_x_0208s_vector,
	    IFIX(Current_thread_index));
    SVREF(jis_x_0208,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_jis_x_0208s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = jis_x_0208;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JIS-X-0208 */
Object reclaim_structure_for_jis_x_0208(jis_x_0208)
    Object jis_x_0208;
{
    x_note_fn_call(28,161);
    return reclaim_jis_x_0208_1(jis_x_0208);
}

static Object Qg2_defstruct_structure_name_jis_x_0208_g2_struct;  /* g2-defstruct-structure-name::jis-x-0208-g2-struct */

/* MAKE-PERMANENT-JIS-X-0208-STRUCTURE-INTERNAL */
Object make_permanent_jis_x_0208_structure_internal()
{
    Object def_structure_jis_x_0208_variable, defstruct_g2_jis_x_0208_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,162);
    def_structure_jis_x_0208_variable = Nil;
    atomic_incff_symval(Qjis_x_0208_count,FIX((SI_Long)1L));
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

static Object Qjis_x_0208;         /* jis-x-0208 */

static Object list_constant_12;    /* # */

/* MAKE-JIS-X-0208-1 */
Object make_jis_x_0208_1()
{
    Object def_structure_jis_x_0208_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,163);
    def_structure_jis_x_0208_variable = 
	    ISVREF(Chain_of_available_jis_x_0208s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_jis_x_0208_variable) {
	svref_arg_1 = Chain_of_available_jis_x_0208s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_jis_x_0208_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_jis_x_0208_g2_struct;
    }
    else
	def_structure_jis_x_0208_variable = 
		make_permanent_jis_x_0208_structure_internal();
    inline_note_allocate_cons(def_structure_jis_x_0208_variable,Nil);
    SVREF(def_structure_jis_x_0208_variable,FIX((SI_Long)1L)) = Qjis_x_0208;
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
Object map_code_to_unicode_for_jis_x_0208(jis_x_0208,code)
    Object jis_x_0208, code;
{
    Object contiguous_code_qm, temp;

    x_note_fn_call(28,164);
    contiguous_code_qm = gensym_jis_code_to_contiguous(code);
    temp = contiguous_code_qm ? 
	    FIX(UBYTE_16_ISAREF_1(Jis_x_0208_to_unicode_map,
	    IFIX(contiguous_code_qm))) : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)65535L));
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-JIS-X-0208 */
Object map_unicode_to_code_if_any_for_jis_x_0208(jis_x_0208,
	    unicode_wide_character)
    Object jis_x_0208, unicode_wide_character;
{
    Object unicode, cjk_code, cjk_code_mapping_vector, l;
    SI_Long temp;

    x_note_fn_call(28,165);
    unicode = unicode_wide_character;
    cjk_code = unicode;
    cjk_code_mapping_vector = Unicode_to_jis_x_0208_map;
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

Object The_type_description_of_ks_c_5601 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_ks_c_5601s, Qchain_of_available_ks_c_5601s);

DEFINE_VARIABLE_WITH_SYMBOL(Ks_c_5601_count, Qks_c_5601_count);

Object Chain_of_available_ks_c_5601s_vector = UNBOUND;

/* KS-C-5601-STRUCTURE-MEMORY-USAGE */
Object ks_c_5601_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,166);
    temp = Ks_c_5601_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-KS-C-5601-COUNT */
Object outstanding_ks_c_5601_count()
{
    Object def_structure_ks_c_5601_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,167);
    gensymed_symbol = IFIX(Ks_c_5601_count);
    def_structure_ks_c_5601_variable = Chain_of_available_ks_c_5601s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_ks_c_5601_variable))
	goto end_loop;
    def_structure_ks_c_5601_variable = 
	    ISVREF(def_structure_ks_c_5601_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-KS-C-5601-1 */
Object reclaim_ks_c_5601_1(ks_c_5601)
    Object ks_c_5601;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,168);
    inline_note_reclaim_cons(ks_c_5601,Nil);
    temp = ISVREF(Chain_of_available_ks_c_5601s_vector,
	    IFIX(Current_thread_index));
    SVREF(ks_c_5601,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_ks_c_5601s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = ks_c_5601;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-KS-C-5601 */
Object reclaim_structure_for_ks_c_5601(ks_c_5601)
    Object ks_c_5601;
{
    x_note_fn_call(28,169);
    return reclaim_ks_c_5601_1(ks_c_5601);
}

static Object Qg2_defstruct_structure_name_ks_c_5601_g2_struct;  /* g2-defstruct-structure-name::ks-c-5601-g2-struct */

/* MAKE-PERMANENT-KS-C-5601-STRUCTURE-INTERNAL */
Object make_permanent_ks_c_5601_structure_internal()
{
    Object def_structure_ks_c_5601_variable, defstruct_g2_ks_c_5601_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,170);
    def_structure_ks_c_5601_variable = Nil;
    atomic_incff_symval(Qks_c_5601_count,FIX((SI_Long)1L));
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

static Object Qks_c_5601;          /* ks-c-5601 */

static Object list_constant_13;    /* # */

/* MAKE-KS-C-5601-1 */
Object make_ks_c_5601_1()
{
    Object def_structure_ks_c_5601_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,171);
    def_structure_ks_c_5601_variable = 
	    ISVREF(Chain_of_available_ks_c_5601s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_ks_c_5601_variable) {
	svref_arg_1 = Chain_of_available_ks_c_5601s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_ks_c_5601_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ks_c_5601_g2_struct;
    }
    else
	def_structure_ks_c_5601_variable = 
		make_permanent_ks_c_5601_structure_internal();
    inline_note_allocate_cons(def_structure_ks_c_5601_variable,Nil);
    SVREF(def_structure_ks_c_5601_variable,FIX((SI_Long)1L)) = Qks_c_5601;
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
Object map_code_to_unicode_for_ks_c_5601(ks_c_5601,code)
    Object ks_c_5601, code;
{
    Object gensym_ks_c_5601, contiguous_code_qm, temp;

    x_note_fn_call(28,172);
    gensym_ks_c_5601 = ksc_to_gensym_ksc(code);
    contiguous_code_qm = gensym_ksc_code_to_contiguous(gensym_ks_c_5601);
    temp = contiguous_code_qm ? 
	    FIX(UBYTE_16_ISAREF_1(Ks_c_5601_to_unicode_map,
	    IFIX(contiguous_code_qm))) : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)65535L));
}

/* MAP-UNICODE-TO-CODE-IF-ANY-FOR-KS-C-5601 */
Object map_unicode_to_code_if_any_for_ks_c_5601(ks_c_5601,
	    unicode_wide_character)
    Object ks_c_5601, unicode_wide_character;
{
    Object unicode, cjk_code, cjk_code_mapping_vector, l, gensym_ksc_code_qm;
    SI_Long temp;

    x_note_fn_call(28,173);
    unicode = unicode_wide_character;
    cjk_code = unicode;
    cjk_code_mapping_vector = Unicode_to_ks_c_5601_map;
    temp = IFIX(cjk_code) % (SI_Long)307L;
    l = ISVREF(cjk_code_mapping_vector,temp);
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    if (FIXNUM_EQ(CAR(l),cjk_code)) {
	gensym_ksc_code_qm = CADR(l);
	goto end_1;
    }
    l = CDDR(l);
    goto next_loop;
  end_loop:
    gensym_ksc_code_qm = Qnil;
  end_1:;
    if (gensym_ksc_code_qm)
	return gensym_ksc_to_ksc(gensym_ksc_code_qm);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_gb_2312 = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gb_2312s, Qchain_of_available_gb_2312s);

DEFINE_VARIABLE_WITH_SYMBOL(Gb_2312_count, Qgb_2312_count);

Object Chain_of_available_gb_2312s_vector = UNBOUND;

/* GB-2312-STRUCTURE-MEMORY-USAGE */
Object gb_2312_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,174);
    temp = Gb_2312_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GB-2312-COUNT */
Object outstanding_gb_2312_count()
{
    Object def_structure_gb_2312_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,175);
    gensymed_symbol = IFIX(Gb_2312_count);
    def_structure_gb_2312_variable = Chain_of_available_gb_2312s;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gb_2312_variable))
	goto end_loop;
    def_structure_gb_2312_variable = ISVREF(def_structure_gb_2312_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GB-2312-1 */
Object reclaim_gb_2312_1(gb_2312)
    Object gb_2312;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,176);
    inline_note_reclaim_cons(gb_2312,Nil);
    temp = ISVREF(Chain_of_available_gb_2312s_vector,
	    IFIX(Current_thread_index));
    SVREF(gb_2312,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gb_2312s_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gb_2312;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GB-2312 */
Object reclaim_structure_for_gb_2312(gb_2312)
    Object gb_2312;
{
    x_note_fn_call(28,177);
    return reclaim_gb_2312_1(gb_2312);
}

static Object Qg2_defstruct_structure_name_gb_2312_g2_struct;  /* g2-defstruct-structure-name::gb-2312-g2-struct */

/* MAKE-PERMANENT-GB-2312-STRUCTURE-INTERNAL */
Object make_permanent_gb_2312_structure_internal()
{
    Object def_structure_gb_2312_variable, defstruct_g2_gb_2312_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,178);
    def_structure_gb_2312_variable = Nil;
    atomic_incff_symval(Qgb_2312_count,FIX((SI_Long)1L));
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

static Object Qgb_2312;            /* gb-2312 */

static Object list_constant_14;    /* # */

/* MAKE-GB-2312-1 */
Object make_gb_2312_1()
{
    Object def_structure_gb_2312_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,179);
    def_structure_gb_2312_variable = 
	    ISVREF(Chain_of_available_gb_2312s_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gb_2312_variable) {
	svref_arg_1 = Chain_of_available_gb_2312s_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gb_2312_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gb_2312_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gb_2312_g2_struct;
    }
    else
	def_structure_gb_2312_variable = 
		make_permanent_gb_2312_structure_internal();
    inline_note_allocate_cons(def_structure_gb_2312_variable,Nil);
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)1L)) = Qgb_2312;
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)2L)) = list_constant_14;
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)3L)) = FIX((SI_Long)2L);
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)4L)) = FIX((SI_Long)94L);
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)5L)) = array_constant_2;
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_gb_2312_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_gb_2312_variable);
}

/* MAP-CODE-TO-UNICODE-FOR-GB-2312 */
Object map_code_to_unicode_for_gb_2312(gb_2312,code)
    Object gb_2312, code;
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, index_1;
    SI_Long code_1;

    x_note_fn_call(28,180);
    gensymed_symbol = ((IFIX(code) >>  -  - (SI_Long)8L) - (SI_Long)33L) * 
	    (SI_Long)94L;
    gensymed_symbol_1 = (SI_Long)255L & IFIX(code);
    gensymed_symbol_2 = (SI_Long)33L;
    gensymed_symbol_2 = gensymed_symbol_1 - gensymed_symbol_2;
    index_1 = gensymed_symbol + gensymed_symbol_2;
    code_1 = (SI_Long)0L;
    if ((SI_Long)0L <= index_1 && index_1 <= (SI_Long)8177L) {
	code_1 = UBYTE_16_ISAREF_1(Gb_2312_to_unicode_map,index_1);
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
Object map_unicode_to_code_if_any_for_gb_2312(gb_2312,unicode_wide_character)
    Object gb_2312, unicode_wide_character;
{
    Object unicode, cjk_code, cjk_code_mapping_vector, vector_1;
    SI_Long temp, length_1, i, ab_loop_bind_, code;

    x_note_fn_call(28,181);
    unicode = unicode_wide_character;
    cjk_code = unicode;
    cjk_code_mapping_vector = Unicode_to_gb_2312_map;
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

Object The_type_description_of_iso_8859_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_8859_transcoders, Qchain_of_available_iso_8859_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_8859_transcoder_count, Qiso_8859_transcoder_count);

Object Chain_of_available_iso_8859_transcoders_vector = UNBOUND;

/* ISO-8859-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object iso_8859_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,182);
    temp = Iso_8859_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-8859-TRANSCODER-COUNT */
Object outstanding_iso_8859_transcoder_count()
{
    Object def_structure_iso_8859_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,183);
    gensymed_symbol = IFIX(Iso_8859_transcoder_count);
    def_structure_iso_8859_transcoder_variable = 
	    Chain_of_available_iso_8859_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_8859_transcoder_variable))
	goto end_loop;
    def_structure_iso_8859_transcoder_variable = 
	    ISVREF(def_structure_iso_8859_transcoder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-8859-TRANSCODER-1 */
Object reclaim_iso_8859_transcoder_1(iso_8859_transcoder)
    Object iso_8859_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,184);
    inline_note_reclaim_cons(iso_8859_transcoder,Nil);
    temp = ISVREF(Chain_of_available_iso_8859_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_8859_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_8859_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_8859_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-8859-TRANSCODER */
Object reclaim_structure_for_iso_8859_transcoder(iso_8859_transcoder)
    Object iso_8859_transcoder;
{
    x_note_fn_call(28,185);
    return reclaim_iso_8859_transcoder_1(iso_8859_transcoder);
}

static Object Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct;  /* g2-defstruct-structure-name::iso-8859-transcoder-g2-struct */

/* MAKE-PERMANENT-ISO-8859-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_iso_8859_transcoder_structure_internal()
{
    Object def_structure_iso_8859_transcoder_variable;
    Object defstruct_g2_iso_8859_transcoder_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,186);
    def_structure_iso_8859_transcoder_variable = Nil;
    atomic_incff_symval(Qiso_8859_transcoder_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_iso_8859_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)0L)) 
		= temp;
	temp = Chain_of_available_iso_8859_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_iso_8859_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_8859_transcoder_variable);
}

/* MAKE-ISO-8859-TRANSCODER-1 */
Object make_iso_8859_transcoder_1(iso_8859_part_number,
	    iso_8859_graphic_character_set)
    Object iso_8859_part_number, iso_8859_graphic_character_set;
{
    Object def_structure_iso_8859_transcoder_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(28,187);
    def_structure_iso_8859_transcoder_variable = 
	    ISVREF(Chain_of_available_iso_8859_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_8859_transcoder_variable) {
	svref_arg_1 = Chain_of_available_iso_8859_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_iso_8859_transcoder_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_8859_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct;
    }
    else
	def_structure_iso_8859_transcoder_variable = 
		make_permanent_iso_8859_transcoder_structure_internal();
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
Object transcode_character_for_iso_8859_transcoder(iso_8859_transcoder)
    Object iso_8859_transcoder;
{
    Object transcoder, structure, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long character_1, arg, arg_1, arg_2, gensymed_symbol_2;

    x_note_fn_call(28,188);
    transcoder = iso_8859_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)18L);
	    gensymed_symbol_1 = structure;
	    gensymed_symbol_2 = character_1 - (SI_Long)128L;
	    temp = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    FIX(gensymed_symbol_2));
	    if (temp)
		return VALUES_1(temp);
	    else
		return transcode_unhandled_character(FIX(character_1),
			transcoder);
	}
	else
	    return transcode_unhandled_character(FIX(character_1),transcoder);
    }
}

static Object Qdos;                /* dos */

static Object Qvms;                /* vms */

static Object Qwin32;              /* win32 */

static Object Qunix;               /* unix */

static Object Qcr;                 /* cr */

static Object Qlf;                 /* lf */

static Object Qcrlf;               /* crlf */

static Object Qunicode_line_separator;  /* unicode-line-separator */

static Object Qunicode_paragraph_separator;  /* unicode-paragraph-separator */

/* EXPORT-CHARACTER-FOR-ISO-8859-TRANSCODER */
Object export_character_for_iso_8859_transcoder(iso_8859_transcoder)
    Object iso_8859_transcoder;
{
    Object transcoder, temp, svref_new_value, structure, gensymed_symbol;
    Object gensymed_symbol_1, code_qm;
    SI_Long character_1, gensymed_symbol_2;

    x_note_fn_call(28,189);
    transcoder = iso_8859_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
    if (character_1 < (SI_Long)32L || character_1 == (SI_Long)8232L || 
	    character_1 == (SI_Long)8233L) {
	if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	    temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	    if (EQ(temp,Qper_platform)) {
		if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
			Qvms) || EQ(G2_operating_system,Qwin32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2_operating_system,Qunix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp,Qcr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp,Qlf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp,Qcrlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp,Qunicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp,Qunicode_paragraph_separator))
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
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)19L);
	gensymed_symbol_1 = structure;
	gensymed_symbol_2 = character_1;
	code_qm = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		FIX(gensymed_symbol_2));
	temp = code_qm ? FIX((SI_Long)128L + IFIX(code_qm)) : Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return transcode_unhandled_character(FIX(character_1),transcoder);
    }
}

Object The_type_description_of_iso_2022_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_iso_2022_transcoders, Qchain_of_available_iso_2022_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Iso_2022_transcoder_count, Qiso_2022_transcoder_count);

Object Chain_of_available_iso_2022_transcoders_vector = UNBOUND;

/* ISO-2022-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object iso_2022_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,190);
    temp = Iso_2022_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)14L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ISO-2022-TRANSCODER-COUNT */
Object outstanding_iso_2022_transcoder_count()
{
    Object def_structure_iso_2022_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,191);
    gensymed_symbol = IFIX(Iso_2022_transcoder_count);
    def_structure_iso_2022_transcoder_variable = 
	    Chain_of_available_iso_2022_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_iso_2022_transcoder_variable))
	goto end_loop;
    def_structure_iso_2022_transcoder_variable = 
	    ISVREF(def_structure_iso_2022_transcoder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ISO-2022-TRANSCODER-1 */
Object reclaim_iso_2022_transcoder_1(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,192);
    inline_note_reclaim_cons(iso_2022_transcoder,Nil);
    temp = ISVREF(Chain_of_available_iso_2022_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(iso_2022_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_iso_2022_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = iso_2022_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ISO-2022-TRANSCODER */
Object reclaim_structure_for_iso_2022_transcoder(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    x_note_fn_call(28,193);
    return reclaim_iso_2022_transcoder_1(iso_2022_transcoder);
}

static Object Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct;  /* g2-defstruct-structure-name::iso-2022-transcoder-g2-struct */

/* MAKE-PERMANENT-ISO-2022-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_iso_2022_transcoder_structure_internal()
{
    Object def_structure_iso_2022_transcoder_variable;
    Object defstruct_g2_iso_2022_transcoder_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,194);
    def_structure_iso_2022_transcoder_variable = Nil;
    atomic_incff_symval(Qiso_2022_transcoder_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_iso_2022_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)0L)) 
		= temp;
	temp = Chain_of_available_iso_2022_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_iso_2022_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_iso_2022_transcoder_variable);
}

static Object Qgraphic_character_set;  /* graphic-character-set */

/* MAKE-ISO-2022-TRANSCODER-1 */
Object make_iso_2022_transcoder_1()
{
    Object def_structure_iso_2022_transcoder_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,195);
    def_structure_iso_2022_transcoder_variable = 
	    ISVREF(Chain_of_available_iso_2022_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_iso_2022_transcoder_variable) {
	temp = Chain_of_available_iso_2022_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_iso_2022_transcoder_variable,(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct;
    }
    else
	def_structure_iso_2022_transcoder_variable = 
		make_permanent_iso_2022_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_iso_2022_transcoder_variable,Nil);
    ISVREF(def_structure_iso_2022_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_iso_2022_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)6L)) = T;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)7L)) = temp;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_1),
	    Qgraphic_character_set);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)8L)) = temp;
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)10L)) = Nil;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)11L)) = temp;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_1),
	    Qgraphic_character_set);
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)12L)) = temp;
    SVREF(def_structure_iso_2022_transcoder_variable,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(def_structure_iso_2022_transcoder_variable);
}

/* CREATE-TRANSCODER-FOR-ISO-646 */
Object create_transcoder_for_iso_646()
{
    Object tc;

    x_note_fn_call(28,196);
    tc = make_iso_2022_transcoder_1();
    set_up_iso_2022_transcoder_for_us_ascii(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-ISO-2022 */
Object create_transcoder_for_iso_2022()
{
    Object tc;

    x_note_fn_call(28,197);
    tc = make_iso_2022_transcoder_1();
    set_up_iso_2022_transcoder_for_x_compound_text(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-JIS-X-0208 */
Object create_transcoder_for_jis_x_0208()
{
    Object tc;

    x_note_fn_call(28,198);
    tc = make_iso_2022_transcoder_1();
    set_up_iso_2022_transcoder_for_jis_x_0208(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-JIS-X-0208-EUC */
Object create_transcoder_for_jis_x_0208_euc()
{
    Object tc;

    x_note_fn_call(28,199);
    tc = make_iso_2022_transcoder_1();
    set_up_iso_2022_transcoder_for_jis_x_0208_euc(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-SHIFT-JIS-X-0208 */
Object create_transcoder_for_shift_jis_x_0208()
{
    Object tc;

    x_note_fn_call(28,200);
    tc = make_shift_jis_transcoder_function();
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-KS-C-5601 */
Object create_transcoder_for_ks_c_5601()
{
    Object tc;

    x_note_fn_call(28,201);
    tc = make_iso_2022_transcoder_1();
    set_up_iso_2022_transcoder_for_ks_c_5601(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-KS-C-5601-EUC */
Object create_transcoder_for_ks_c_5601_euc()
{
    Object tc;

    x_note_fn_call(28,202);
    tc = make_iso_2022_transcoder_1();
    set_up_iso_2022_transcoder_for_ks_c_5601_euc(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-GB-2312 */
Object create_transcoder_for_gb_2312()
{
    Object tc;

    x_note_fn_call(28,203);
    tc = make_iso_2022_transcoder_1();
    set_up_iso_2022_transcoder_for_gb_2312(tc);
    return VALUES_1(tc);
}

/* CREATE-TRANSCODER-FOR-GB-2312-EUC */
Object create_transcoder_for_gb_2312_euc()
{
    Object tc;

    x_note_fn_call(28,204);
    tc = make_iso_2022_transcoder_1();
    set_up_iso_2022_transcoder_for_gb_2312_euc(tc);
    return VALUES_1(tc);
}

static Object array_constant_9;    /* # */

static Object Qleft;               /* left */

static Object array_constant_10;   /* # */

static Object Qright;              /* right */

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
Object read_iso_2022_escape_from_wide_string(string_1,index_1)
    Object string_1, index_1;
{
    Object forward_index;
    SI_Long length_1, escape_end_index, string_end_index, i, j, c1, c2, temp;
    char wide_string_p, temp_1;
    char temp_2;

    x_note_fn_call(28,205);
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
	string_end_index = IFIX(gensym_string_length(string_1));
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
    goto next_loop;
  end_loop:
    forward_index = FIX(j);
    temp_1 = TRUEP(T);
    goto end_1;
    temp_1 = TRUEP(Qnil);
  end_1:;
    if (temp_1)
	return VALUES_3(Qjis_x_0208,forward_index,Qleft);
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
	    string_end_index = IFIX(gensym_string_length(string_1));
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
	goto next_loop_1;
      end_loop_1:
	forward_index = FIX(j);
	temp_1 = TRUEP(T);
	goto end_2;
	temp_1 = TRUEP(Qnil);
      end_2:;
	if (temp_1)
	    return VALUES_3(Qks_c_5601,forward_index,Qright);
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
		string_end_index = IFIX(gensym_string_length(string_1));
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
	    goto next_loop_2;
	  end_loop_2:
	    forward_index = FIX(j);
	    temp_1 = TRUEP(T);
	    goto end_3;
	    temp_1 = TRUEP(Qnil);
	  end_3:;
	    if (temp_1)
		return VALUES_3(Qjis_x_0208,forward_index,Qright);
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
		    string_end_index = IFIX(gensym_string_length(string_1));
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
		goto next_loop_3;
	      end_loop_3:
		forward_index = FIX(j);
		temp_1 = TRUEP(T);
		goto end_4;
		temp_1 = TRUEP(Qnil);
	      end_4:;
		if (temp_1)
		    return VALUES_3(Qgb_2312,forward_index,Qright);
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
				IFIX(gensym_string_length(string_1));
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
		    goto next_loop_4;
		  end_loop_4:
		    forward_index = FIX(j);
		    temp_1 = TRUEP(T);
		    goto end_5;
		    temp_1 = TRUEP(Qnil);
		  end_5:;
		    if (temp_1)
			return VALUES_3(Qks_c_5601,forward_index,Qleft);
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
				    IFIX(gensym_string_length(string_1));
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
			    c2 = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
			}
			if (c1 != c2) {
			    temp_1 = TRUEP(Nil);
			    goto end_6;
			}
			goto next_loop_5;
		      end_loop_5:
			forward_index = FIX(j);
			temp_1 = TRUEP(T);
			goto end_6;
			temp_1 = TRUEP(Qnil);
		      end_6:;
			if (temp_1)
			    return VALUES_3(Qjis_x_0208,forward_index,Qleft);
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
					IFIX(gensym_string_length(string_1));
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
			    goto next_loop_6;
			  end_loop_6:
			    forward_index = FIX(j);
			    temp_1 = TRUEP(T);
			    goto end_7;
			    temp_1 = TRUEP(Qnil);
			  end_7:;
			    if (temp_1)
				return VALUES_3(Qgb_2312,forward_index,Qleft);
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
					    IFIX(gensym_string_length(string_1));
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
				goto next_loop_7;
			      end_loop_7:
				forward_index = FIX(j);
				temp_1 = TRUEP(T);
				goto end_8;
				temp_1 = TRUEP(Qnil);
			      end_8:;
				if (temp_1)
				    return VALUES_3(Qjis_x_0208,
					    forward_index,Qleft);
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
						IFIX(gensym_string_length(string_1));
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
					goto end_9;
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
					goto end_9;
				    }
				    goto next_loop_8;
				  end_loop_8:
				    forward_index = FIX(j);
				    temp_1 = TRUEP(T);
				    goto end_9;
				    temp_1 = TRUEP(Qnil);
				  end_9:;
				    if (temp_1)
					return VALUES_3(Qjis_x_0208,
						forward_index,Qleft);
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
						    IFIX(gensym_string_length(string_1));
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
					goto next_loop_9;
				      end_loop_9:
					forward_index = FIX(j);
					temp_1 = TRUEP(T);
					goto end_10;
					temp_1 = TRUEP(Qnil);
				      end_10:;
					if (temp_1)
					    return VALUES_3(Qgb_2312,
						    forward_index,Qleft);
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
							IFIX(gensym_string_length(string_1));
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
					    goto next_loop_10;
					  end_loop_10:
					    forward_index = FIX(j);
					    temp_1 = TRUEP(T);
					    goto end_11;
					    temp_1 = TRUEP(Qnil);
					  end_11:;
					    if (temp_1)
						return VALUES_3(Qiso_8859_9,
							forward_index,Qright);
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
							    IFIX(gensym_string_length(string_1));
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
						    temp_2 = ICHAR(string_1,j);
						    j = j + (SI_Long)1L;
						    c2 = 
							    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(temp_2)));
						}
						if (c1 != c2) {
						    temp_1 = TRUEP(Nil);
						    goto end_12;
						}
						goto next_loop_11;
					      end_loop_11:
						forward_index = FIX(j);
						temp_1 = TRUEP(T);
						goto end_12;
						temp_1 = TRUEP(Qnil);
					      end_12:;
						if (temp_1)
						    return VALUES_3(Qiso_8859_8,
							    forward_index,
							    Qright);
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
								IFIX(gensym_string_length(string_1));
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
							goto end_13;
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
							goto end_13;
						    }
						    goto next_loop_12;
						  end_loop_12:
						    forward_index = FIX(j);
						    temp_1 = TRUEP(T);
						    goto end_13;
						    temp_1 = TRUEP(Qnil);
						  end_13:;
						    if (temp_1)
							return VALUES_3(Qiso_8859_7,
								forward_index,
								Qright);
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
								    IFIX(gensym_string_length(string_1));
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
							    goto end_14;
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
							    goto end_14;
							}
							goto next_loop_13;
						      end_loop_13:
							forward_index = FIX(j);
							temp_1 = TRUEP(T);
							goto end_14;
							temp_1 = TRUEP(Qnil);
						      end_14:;
							if (temp_1)
							    return VALUES_3(Qiso_8859_6,
								    forward_index,
								    Qright);
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
									IFIX(gensym_string_length(string_1));
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
								goto end_15;
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
								goto end_15;
							    }
							    goto next_loop_14;
							  end_loop_14:
							    forward_index 
								    = FIX(j);
							    temp_1 = TRUEP(T);
							    goto end_15;
							    temp_1 = 
								    TRUEP(Qnil);
							  end_15:;
							    if (temp_1)
								return VALUES_3(Qiso_8859_5,
									forward_index,
									Qright);
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
									    IFIX(gensym_string_length(string_1));
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
								    goto end_16;
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
								    goto end_16;
								}
								goto next_loop_15;
							      end_loop_15:
								forward_index 
									= 
									FIX(j);
								temp_1 = 
									TRUEP(T);
								goto end_16;
								temp_1 = 
									TRUEP(Qnil);
							      end_16:;
								if (temp_1)
								    return VALUES_3(Qiso_8859_4,
									    forward_index,
									    Qright);
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
										IFIX(gensym_string_length(string_1));
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
								    goto next_loop_16;
								  end_loop_16:
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
									return VALUES_3(Qiso_8859_3,
										forward_index,
										Qright);
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
										    IFIX(gensym_string_length(string_1));
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
									goto next_loop_17;
								      end_loop_17:
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
									    return VALUES_3(Qiso_8859_2,
										    forward_index,
										    Qright);
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
											IFIX(gensym_string_length(string_1));
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
									    goto next_loop_18;
									  end_loop_18:
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
										return VALUES_3(Qiso_8859_1,
											forward_index,
											Qright);
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
											    IFIX(gensym_string_length(string_1));
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
										goto next_loop_19;
									      end_loop_19:
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
										    return VALUES_3(Qiso_646,
											    forward_index,
											    Qleft);
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
												IFIX(gensym_string_length(string_1));
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
										    goto next_loop_20;
										  end_loop_20:
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
											return VALUES_3(Qiso_646,
												forward_index,
												Qleft);
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
												    IFIX(gensym_string_length(string_1));
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
											goto next_loop_21;
										      end_loop_21:
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
											    return VALUES_3(Qiso_646,
												    forward_index,
												    Qleft);
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
													IFIX(gensym_string_length(string_1));
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
												goto end_23;
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
												goto end_23;
											    }
											    goto next_loop_22;
											  end_loop_22:
											    forward_index 
												    = 
												    FIX(j);
											    temp_1 
												    = 
												    TRUEP(T);
											    goto end_23;
											    temp_1 
												    = 
												    TRUEP(Qnil);
											  end_23:;
											    if (temp_1)
												return VALUES_3(Qiso_646,
													forward_index,
													Qleft);
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
Object handle_iso_2022_escape(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    Object transcoder, text_sequence, graphic_character_set_name;
    Object forward_index, invocation_side, graphic_character_set_qm;
    SI_Long ab_loop_repeat_;
    Object result;

    x_note_fn_call(28,206);
    transcoder = iso_2022_transcoder;
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    result = read_iso_2022_escape_from_wide_string(ISVREF(text_sequence,
	    (SI_Long)1L),ISVREF(text_sequence,(SI_Long)6L));
    MVS_3(result,graphic_character_set_name,forward_index,invocation_side);
    ab_loop_repeat_ = IFIX(FIXNUM_MINUS(forward_index,ISVREF(text_sequence,
	    (SI_Long)6L)));
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    get_transcoder_character(transcoder);
    goto next_loop;
  end_loop:;
    graphic_character_set_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(graphic_character_set_name),
	    Qgraphic_character_set);
    if (graphic_character_set_qm) {
	if (EQ(invocation_side,Qleft))
	    SVREF(transcoder,FIX((SI_Long)11L)) = graphic_character_set_qm;
	else if (EQ(invocation_side,Qright))
	    SVREF(transcoder,FIX((SI_Long)12L)) = graphic_character_set_qm;
    }
    ISVREF(transcoder,(SI_Long)3L) = FIX((SI_Long)65535L);
    ISVREF(transcoder,(SI_Long)2L) = FIX((SI_Long)65535L);
    return VALUES_1(Nil);
}

Object No_han_x_compound_text_character_set_selection_list = UNBOUND;

Object Japanese_han_x_compound_text_character_set_selection_list = UNBOUND;

Object Korean_han_x_compound_text_character_set_selection_list = UNBOUND;

Object Chinese_han_x_compound_text_character_set_selection_list = UNBOUND;

Object Default_han_x_compound_text_character_set_selection_list = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Text_conversion_style_for_transcoder_being_created, Qtext_conversion_style_for_transcoder_being_created);

static Object Qjapanese;           /* japanese */

static Object Qkorean;             /* korean */

static Object Qchinese;            /* chinese */

/* SET-UP-ISO-2022-TRANSCODER-FOR-X-COMPOUND-TEXT */
Object set_up_iso_2022_transcoder_for_x_compound_text(transcoder)
    Object transcoder;
{
    Object temp, svref_new_value;

    x_note_fn_call(28,207);
    temp = ISVREF(Text_conversion_style_for_transcoder_being_created,
	    (SI_Long)5L);
    if (EQ(temp,Qjapanese))
	svref_new_value = 
		Japanese_han_x_compound_text_character_set_selection_list;
    else if (EQ(temp,Qkorean))
	svref_new_value = 
		Korean_han_x_compound_text_character_set_selection_list;
    else if (EQ(temp,Qchinese))
	svref_new_value = 
		Chinese_han_x_compound_text_character_set_selection_list;
    else
	svref_new_value = 
		Default_han_x_compound_text_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object Us_ascii_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-US-ASCII */
Object set_up_iso_2022_transcoder_for_us_ascii(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(28,208);
    svref_new_value = Us_ascii_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)11L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object Ks_c_5601_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-KS-C-5601 */
Object set_up_iso_2022_transcoder_for_ks_c_5601(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(28,209);
    svref_new_value = Ks_c_5601_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object Ks_c_5601_euc_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-KS-C-5601-EUC */
Object set_up_iso_2022_transcoder_for_ks_c_5601_euc(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(28,210);
    svref_new_value = Ks_c_5601_euc_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = T;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)8L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object Gb_2312_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-GB-2312 */
Object set_up_iso_2022_transcoder_for_gb_2312(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(28,211);
    svref_new_value = Gb_2312_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object Gb_2312_euc_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-GB-2312-EUC */
Object set_up_iso_2022_transcoder_for_gb_2312_euc(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(28,212);
    svref_new_value = Gb_2312_euc_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = T;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)8L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object Jis_x_0208_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-JIS-X-0208 */
Object set_up_iso_2022_transcoder_for_jis_x_0208(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(28,213);
    svref_new_value = Jis_x_0208_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = Nil;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

Object Jis_x_0208_euc_character_set_selection_list = UNBOUND;

/* SET-UP-ISO-2022-TRANSCODER-FOR-JIS-X-0208-EUC */
Object set_up_iso_2022_transcoder_for_jis_x_0208_euc(transcoder)
    Object transcoder;
{
    Object svref_new_value;

    x_note_fn_call(28,214);
    svref_new_value = Jis_x_0208_euc_character_set_selection_list;
    SVREF(transcoder,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(transcoder,FIX((SI_Long)6L)) = T;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    SVREF(transcoder,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)7L);
    SVREF(transcoder,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = ISVREF(transcoder,(SI_Long)8L);
    SVREF(transcoder,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* TRANSCODE-ISO-2022-C1-CHARACTER */
Object transcode_iso_2022_c1_character(character_1,transcoder)
    Object character_1, transcoder;
{
    x_note_fn_call(28,215);
    return transcode_unhandled_character(character_1,transcoder);
}

static Object Qgl;                 /* gl */

/* TRANSCODE-ISO-2022-GRAPHIC-CHARACTER */
Object transcode_iso_2022_graphic_character(character_init,transcoder,zone)
    Object character_init, transcoder, zone;
{
    Object graphic_character_set, text_sequence, gensymed_symbol;
    Object gensymed_symbol_1, temp, svref_new_value;
    SI_Long character_1, gensymed_symbol_2, trail_character, arg, arg_1, arg_2;
    SI_Long lead_octet, trail_octet, lead_7_bit_octet, trail_7_bit_octet;

    x_note_fn_call(28,216);
    character_1 = IFIX(character_init);
    graphic_character_set = EQ(zone,Qgl) ? ISVREF(transcoder,(SI_Long)11L) 
	    : ISVREF(transcoder,(SI_Long)12L);
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    if (IFIX(ISVREF(graphic_character_set,(SI_Long)3L)) == (SI_Long)1L) {
	gensymed_symbol = ISVREF(graphic_character_set,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
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
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
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
			ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			Qtype_description_of_unique_type_name_of_gensym_structure),
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
	temp = transcode_unhandled_character(FIX(character_1),transcoder);
    return VALUES_1(temp);
}

static Object Qgr;                 /* gr */

/* TRANSCODE-CHARACTER-FOR-ISO-2022-TRANSCODER */
Object transcode_character_for_iso_2022_transcoder(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    Object transcoder, result_character, temp;
    SI_Long character_1;

    x_note_fn_call(28,217);
    transcoder = iso_2022_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
		handle_iso_2022_escape(transcoder);
		return VALUES_1(FIX((SI_Long)65535L));
	      default:
		return VALUES_1(result_character);
	    }
    }
    else if (character_1 < (SI_Long)128L)
	return transcode_iso_2022_graphic_character(FIX(character_1),
		transcoder,Qgl);
    else {
	if (ISVREF(transcoder,(SI_Long)6L)) {
	    if (character_1 < (SI_Long)160L)
		temp = transcode_iso_2022_c1_character(FIX(character_1),
			transcoder);
	    else if (character_1 < (SI_Long)256L)
		temp = 
			transcode_iso_2022_graphic_character(FIX(character_1),
			transcoder,Qgr);
	    else
		temp = Qnil;
	}
	else
	    temp = Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return transcode_unhandled_character(FIX(character_1),transcoder);
    }
}

/* EXPORT-CHARACTER-FOR-ISO-2022-TRANSCODER */
Object export_character_for_iso_2022_transcoder(iso_2022_transcoder)
    Object iso_2022_transcoder;
{
    Object transcoder, set_1, invocation_side, svref_new_value, i, string_1;
    Object temp_1, set_selection_list, code, side, ab_loop_list_;
    Object ab_loop_desetq_, gensymed_symbol, gensymed_symbol_1, character_3;
    SI_Long character_1, arg, arg_1, arg_2, character_2, length_1;
    SI_Long gensymed_symbol_2;
    char temp;

    x_note_fn_call(28,218);
    transcoder = iso_2022_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
	if (newline_p(FIX(character_1))) {
	    set_1 = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
		    Qgraphic_character_set);
	    iso_2022_transcoder = transcoder;
	    invocation_side = Qleft;
	    if (EQ(invocation_side,Qleft)) {
		if ( !EQ(set_1,ISVREF(iso_2022_transcoder,(SI_Long)11L))) {
		    SVREF(iso_2022_transcoder,FIX((SI_Long)11L)) = set_1;
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)27L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    if (IFIX(ISVREF(set_1,(SI_Long)3L)) > (SI_Long)1L) {
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX((SI_Long)36L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)40L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    i = FIX((SI_Long)0L);
		    string_1 = ISVREF(set_1,(SI_Long)5L);
		  next_loop:
		    character_2 = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_2),Nil));
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
	    else if (EQ(invocation_side,Qright)) {
		if ( !EQ(set_1,ISVREF(iso_2022_transcoder,(SI_Long)12L))) {
		    SVREF(iso_2022_transcoder,FIX((SI_Long)12L)) = set_1;
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)27L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    if (IFIX(ISVREF(set_1,(SI_Long)4L)) == (SI_Long)94L) {
			if (IFIX(ISVREF(set_1,(SI_Long)3L)) > (SI_Long)1L) {
			    svref_new_value = 
				    nconc2(ISVREF(iso_2022_transcoder,
				    (SI_Long)5L),
				    gensym_cons_1(FIX((SI_Long)36L),Nil));
			    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				    svref_new_value;
			}
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX((SI_Long)41L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    else {
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX((SI_Long)45L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    i = FIX((SI_Long)0L);
		    string_1 = ISVREF(set_1,(SI_Long)5L);
		  next_loop_1:
		    character_2 = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_2),Nil));
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
	    if (EQ(temp_1,Qper_platform)) {
		if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
			Qvms) || EQ(G2_operating_system,Qwin32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2_operating_system,Qunix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp_1,Qcr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp_1,Qlf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp_1,Qcrlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp_1,Qunicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp_1,Qunicode_paragraph_separator))
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
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)19L);
	gensymed_symbol_1 = set_1;
	gensymed_symbol_2 = character_1;
	code = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		FIX(gensymed_symbol_2));
	if (code) {
	    if (EQ(side,Qleft)) {
		if ( !EQ(set_1,ISVREF(transcoder,(SI_Long)11L))) {
		    SVREF(transcoder,FIX((SI_Long)11L)) = set_1;
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)27L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    if (IFIX(ISVREF(set_1,(SI_Long)3L)) > (SI_Long)1L) {
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX((SI_Long)36L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)40L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    i = FIX((SI_Long)0L);
		    string_1 = ISVREF(set_1,(SI_Long)5L);
		  next_loop_3:
		    character_2 = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_2),Nil));
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
	    else if (EQ(side,Qright)) {
		if ( !EQ(set_1,ISVREF(transcoder,(SI_Long)12L))) {
		    SVREF(transcoder,FIX((SI_Long)12L)) = set_1;
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)27L),Nil));
		    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
			    svref_new_value;
		    if (IFIX(ISVREF(set_1,(SI_Long)4L)) == (SI_Long)94L) {
			if (IFIX(ISVREF(set_1,(SI_Long)3L)) > (SI_Long)1L) {
			    svref_new_value = 
				    nconc2(ISVREF(iso_2022_transcoder,
				    (SI_Long)5L),
				    gensym_cons_1(FIX((SI_Long)36L),Nil));
			    SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				    svref_new_value;
			}
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX((SI_Long)41L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    else {
			svref_new_value = 
				nconc2(ISVREF(iso_2022_transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX((SI_Long)45L),Nil));
			SVREF(iso_2022_transcoder,FIX((SI_Long)5L)) = 
				svref_new_value;
		    }
		    i = FIX((SI_Long)0L);
		    string_1 = ISVREF(set_1,(SI_Long)5L);
		  next_loop_4:
		    character_2 = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		    svref_new_value = nconc2(ISVREF(iso_2022_transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_2),Nil));
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
		character_3 = EQ(side,Qleft) ? code : FIX(IFIX(code) | 
			(SI_Long)128L);
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(character_3,Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    }
	    else {
		character_2 = EQ(side,Qleft) ? IFIX(code) >>  -  - 
			(SI_Long)8L & (SI_Long)127L : IFIX(code) >>  -  - 
			(SI_Long)8L & (SI_Long)127L | (SI_Long)128L;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX(character_2),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = EQ(side,Qleft) ? IFIX(code) & (SI_Long)127L :
			 IFIX(code) & (SI_Long)127L | (SI_Long)128L;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX(character_2),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    }
	    return VALUES_1(FIX((SI_Long)65535L));
	}
	goto next_loop_2;
      end_loop_2:
	return transcode_unhandled_character(FIX(character_1),transcoder);
	return VALUES_1(Qnil);
    }
}

Object The_type_description_of_shift_jis_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_shift_jis_transcoders, Qchain_of_available_shift_jis_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Shift_jis_transcoder_count, Qshift_jis_transcoder_count);

Object Chain_of_available_shift_jis_transcoders_vector = UNBOUND;

/* SHIFT-JIS-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object shift_jis_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,219);
    temp = Shift_jis_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SHIFT-JIS-TRANSCODER-COUNT */
Object outstanding_shift_jis_transcoder_count()
{
    Object def_structure_shift_jis_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,220);
    gensymed_symbol = IFIX(Shift_jis_transcoder_count);
    def_structure_shift_jis_transcoder_variable = 
	    Chain_of_available_shift_jis_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_shift_jis_transcoder_variable))
	goto end_loop;
    def_structure_shift_jis_transcoder_variable = 
	    ISVREF(def_structure_shift_jis_transcoder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SHIFT-JIS-TRANSCODER-1 */
Object reclaim_shift_jis_transcoder_1(shift_jis_transcoder)
    Object shift_jis_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,221);
    inline_note_reclaim_cons(shift_jis_transcoder,Nil);
    temp = ISVREF(Chain_of_available_shift_jis_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(shift_jis_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_shift_jis_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = shift_jis_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SHIFT-JIS-TRANSCODER */
Object reclaim_structure_for_shift_jis_transcoder(shift_jis_transcoder)
    Object shift_jis_transcoder;
{
    x_note_fn_call(28,222);
    return reclaim_shift_jis_transcoder_1(shift_jis_transcoder);
}

static Object Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct;  /* g2-defstruct-structure-name::shift-jis-transcoder-g2-struct */

/* MAKE-PERMANENT-SHIFT-JIS-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_shift_jis_transcoder_structure_internal()
{
    Object def_structure_shift_jis_transcoder_variable;
    Object defstruct_g2_shift_jis_transcoder_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,223);
    def_structure_shift_jis_transcoder_variable = Nil;
    atomic_incff_symval(Qshift_jis_transcoder_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_shift_jis_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_shift_jis_transcoder_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_shift_jis_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_shift_jis_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_shift_jis_transcoder_variable);
}

/* MAKE-SHIFT-JIS-TRANSCODER-1 */
Object make_shift_jis_transcoder_1()
{
    Object def_structure_shift_jis_transcoder_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,224);
    def_structure_shift_jis_transcoder_variable = 
	    ISVREF(Chain_of_available_shift_jis_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_shift_jis_transcoder_variable) {
	temp = Chain_of_available_shift_jis_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_shift_jis_transcoder_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_shift_jis_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct;
    }
    else
	def_structure_shift_jis_transcoder_variable = 
		make_permanent_shift_jis_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_shift_jis_transcoder_variable,Nil);
    ISVREF(def_structure_shift_jis_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_shift_jis_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_shift_jis_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    SVREF(def_structure_shift_jis_transcoder_variable,FIX((SI_Long)6L)) = temp;
    return VALUES_1(def_structure_shift_jis_transcoder_variable);
}

/* MAKE-SHIFT-JIS-TRANSCODER-FUNCTION */
Object make_shift_jis_transcoder_function()
{
    x_note_fn_call(28,225);
    return make_shift_jis_transcoder_1();
}

/* TRANSCODE-CHARACTER-FOR-SHIFT-JIS-TRANSCODER */
Object transcode_character_for_shift_jis_transcoder(shift_jis_transcoder)
    Object shift_jis_transcoder;
{
    Object transcoder, result_character, temp, trail_character, lead_octet;
    Object trail_octet, c1, c2, structure, gensymed_symbol_2;
    Object gensymed_symbol_3;
    SI_Long character_1, arg, arg_1, arg_2, lead_character, row_offset;
    SI_Long cell_offset, gensymed_symbol, gensymed_symbol_1, double_byte_code;
    char temp_1, adjust_p;

    x_note_fn_call(28,226);
    transcoder = shift_jis_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
		handle_iso_2022_escape(transcoder);
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
		trail_character = get_transcoder_character_if_any(transcoder);
		if (trail_character);
		else
		    return transcode_unhandled_character(FIX(character_1),
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
			ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol_2),
			Qtype_description_of_unique_type_name_of_gensym_structure),
			(SI_Long)9L),(SI_Long)18L);
		gensymed_symbol_3 = structure;
		gensymed_symbol = double_byte_code;
		return VALUES_1(inline_funcall_2(gensymed_symbol_2,
			gensymed_symbol_3,FIX(gensymed_symbol)));
	    }
	    else
		return transcode_unhandled_character(FIX(character_1),
			transcoder);
	}
    }
}

/* EXPORT-CHARACTER-FOR-SHIFT-JIS-TRANSCODER */
Object export_character_for_shift_jis_transcoder(shift_jis_transcoder)
    Object shift_jis_transcoder;
{
    Object transcoder, temp_1, svref_new_value, cjk_code_mapping_vector, l;
    Object jis_code_qm, jis_code, lead_octet, trail_octet, c1, c2, character_2;
    SI_Long character_1, arg, arg_1, arg_2, unicode, cjk_code, temp_2;
    SI_Long row_offset, cell_offset;
    char temp;

    x_note_fn_call(28,227);
    transcoder = shift_jis_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
	    if (EQ(temp_1,Qper_platform)) {
		if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
			Qvms) || EQ(G2_operating_system,Qwin32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2_operating_system,Qunix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp_1,Qcr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp_1,Qlf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp_1,Qcrlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp_1,Qunicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp_1,Qunicode_paragraph_separator))
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
	cjk_code_mapping_vector = Unicode_to_jis_x_0208_map;
	temp_2 = cjk_code % (SI_Long)307L;
	l = ISVREF(cjk_code_mapping_vector,temp_2);
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (IFIX(CAR(l)) == cjk_code) {
	    jis_code_qm = CADR(l);
	    goto end_1;
	}
	l = CDDR(l);
	goto next_loop;
      end_loop:
	jis_code_qm = Qnil;
      end_1:;
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
		    gensym_cons_1(character_2,Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    return VALUES_1(lead_octet);
	}
	else
	    return transcode_unhandled_character(FIX(character_1),transcoder);
    }
}

Object The_type_description_of_utf_g_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_utf_g_transcoders, Qchain_of_available_utf_g_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Utf_g_transcoder_count, Qutf_g_transcoder_count);

Object Chain_of_available_utf_g_transcoders_vector = UNBOUND;

/* UTF-G-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object utf_g_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,228);
    temp = Utf_g_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UTF-G-TRANSCODER-COUNT */
Object outstanding_utf_g_transcoder_count()
{
    Object def_structure_utf_g_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,229);
    gensymed_symbol = IFIX(Utf_g_transcoder_count);
    def_structure_utf_g_transcoder_variable = 
	    Chain_of_available_utf_g_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_utf_g_transcoder_variable))
	goto end_loop;
    def_structure_utf_g_transcoder_variable = 
	    ISVREF(def_structure_utf_g_transcoder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UTF-G-TRANSCODER-1 */
Object reclaim_utf_g_transcoder_1(utf_g_transcoder)
    Object utf_g_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,230);
    inline_note_reclaim_cons(utf_g_transcoder,Nil);
    temp = ISVREF(Chain_of_available_utf_g_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(utf_g_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_utf_g_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = utf_g_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UTF-G-TRANSCODER */
Object reclaim_structure_for_utf_g_transcoder(utf_g_transcoder)
    Object utf_g_transcoder;
{
    x_note_fn_call(28,231);
    return reclaim_utf_g_transcoder_1(utf_g_transcoder);
}

static Object Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct;  /* g2-defstruct-structure-name::utf-g-transcoder-g2-struct */

/* MAKE-PERMANENT-UTF-G-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_utf_g_transcoder_structure_internal()
{
    Object def_structure_utf_g_transcoder_variable;
    Object defstruct_g2_utf_g_transcoder_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,232);
    def_structure_utf_g_transcoder_variable = Nil;
    atomic_incff_symval(Qutf_g_transcoder_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_utf_g_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_utf_g_transcoder_variable,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_utf_g_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_utf_g_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_utf_g_transcoder_variable);
}

/* MAKE-UTF-G-TRANSCODER-1 */
Object make_utf_g_transcoder_1()
{
    Object def_structure_utf_g_transcoder_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,233);
    def_structure_utf_g_transcoder_variable = 
	    ISVREF(Chain_of_available_utf_g_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_utf_g_transcoder_variable) {
	svref_arg_1 = Chain_of_available_utf_g_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_utf_g_transcoder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_utf_g_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct;
    }
    else
	def_structure_utf_g_transcoder_variable = 
		make_permanent_utf_g_transcoder_structure_internal();
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
Object get_utf_g_transcoder_code(character_init,transcoder)
    Object character_init, transcoder;
{
    Object character_or_character_code, escape_character_qm, temp_1;
    Object first_code, second_code;
    SI_Long character_1, temp, code, result_1, character_or_character_code_1;

    x_note_fn_call(28,234);
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
			ISVREF(Reverse_iso_latin1_special_character_code_map,
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
			    temp_1 = Gensym_code_for_capital_ligature_oe;
			    break;
			  case 119:
			    temp_1 = Gensym_code_for_small_ligature_oe;
			    break;
			  case 42:
			    temp_1 = Gensym_code_for_bullet;
			    break;
			  case 38:
			    temp_1 = Gensym_code_for_small_letter_f_with_hook;
			    break;
			  case 58:
			    temp_1 = Gensym_code_for_trade_mark_sign;
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
		    !TRUEP(Gensym_esc_for_linebreak_qm) ? 
		    CHAR_EQ(character_or_character_code,
		    Gensym_char_or_code_for_linebreak) : 
		    EQ(character_or_character_code,
		    Gensym_char_or_code_for_linebreak) && 
		    EQ(escape_character_qm,Gensym_esc_for_linebreak_qm))
		temp_1 = Gensym_code_for_linebreak;
	    else if ( !TRUEP(escape_character_qm) &&  
		    !TRUEP(Gensym_esc_for_paragraph_break_qm) ? 
		    CHAR_EQ(character_or_character_code,
		    Gensym_char_or_code_for_paragraph_break) : 
		    EQ(character_or_character_code,
		    Gensym_char_or_code_for_paragraph_break) && 
		    EQ(escape_character_qm,Gensym_esc_for_paragraph_break_qm))
		temp_1 = Gensym_code_for_paragraph_break;
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
	    temp_1 = get_transcoder_character_if_any(transcoder);
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
			    ISVREF(Reverse_iso_latin1_special_character_code_map,
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
				temp_1 = Gensym_code_for_capital_ligature_oe;
				break;
			      case 119:
				temp_1 = Gensym_code_for_small_ligature_oe;
				break;
			      case 42:
				temp_1 = Gensym_code_for_bullet;
				break;
			      case 38:
				temp_1 = 
					Gensym_code_for_small_letter_f_with_hook;
				break;
			      case 58:
				temp_1 = Gensym_code_for_trade_mark_sign;
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
			!TRUEP(Gensym_esc_for_linebreak_qm) ? 
			CHAR_EQ(character_or_character_code,
			Gensym_char_or_code_for_linebreak) : 
			EQ(character_or_character_code,
			Gensym_char_or_code_for_linebreak) && 
			EQ(escape_character_qm,Gensym_esc_for_linebreak_qm))
		    temp_1 = Gensym_code_for_linebreak;
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(Gensym_esc_for_paragraph_break_qm) ? 
			CHAR_EQ(character_or_character_code,
			Gensym_char_or_code_for_paragraph_break) : 
			EQ(character_or_character_code,
			Gensym_char_or_code_for_paragraph_break) && 
			EQ(escape_character_qm,
			Gensym_esc_for_paragraph_break_qm))
		    temp_1 = Gensym_code_for_paragraph_break;
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
	    temp_1 = get_transcoder_character_if_any(transcoder);
	    if (temp_1);
	    else {
		temp_1 = FIX((SI_Long)65535L);
		goto end_exhausted;
	    }
	    code = IFIX(temp_1);
	    if (code < (SI_Long)40L) {
		first_code = get_transcoder_character_if_any(transcoder);
		if (first_code);
		else {
		    temp_1 = FIX((SI_Long)65535L);
		    goto end_exhausted;
		}
		second_code = get_transcoder_character_if_any(transcoder);
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
		first_code = get_transcoder_character_if_any(transcoder);
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
			    ISVREF(Reverse_iso_latin1_special_character_code_map,
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
				temp_1 = Gensym_code_for_capital_ligature_oe;
				break;
			      case 119:
				temp_1 = Gensym_code_for_small_ligature_oe;
				break;
			      case 42:
				temp_1 = Gensym_code_for_bullet;
				break;
			      case 38:
				temp_1 = 
					Gensym_code_for_small_letter_f_with_hook;
				break;
			      case 58:
				temp_1 = Gensym_code_for_trade_mark_sign;
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
			!TRUEP(Gensym_esc_for_linebreak_qm) ? 
			CHAR_EQ(FIX(character_or_character_code_1),
			Gensym_char_or_code_for_linebreak) : 
			EQ(FIX(character_or_character_code_1),
			Gensym_char_or_code_for_linebreak) && 
			EQ(escape_character_qm,Gensym_esc_for_linebreak_qm))
		    temp_1 = Gensym_code_for_linebreak;
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(Gensym_esc_for_paragraph_break_qm) ? 
			CHAR_EQ(FIX(character_or_character_code_1),
			Gensym_char_or_code_for_paragraph_break) : 
			EQ(FIX(character_or_character_code_1),
			Gensym_char_or_code_for_paragraph_break) && 
			EQ(escape_character_qm,
			Gensym_esc_for_paragraph_break_qm))
		    temp_1 = Gensym_code_for_paragraph_break;
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
			    ISVREF(Reverse_iso_latin1_special_character_code_map,
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
				temp_1 = Gensym_code_for_capital_ligature_oe;
				break;
			      case 119:
				temp_1 = Gensym_code_for_small_ligature_oe;
				break;
			      case 42:
				temp_1 = Gensym_code_for_bullet;
				break;
			      case 38:
				temp_1 = 
					Gensym_code_for_small_letter_f_with_hook;
				break;
			      case 58:
				temp_1 = Gensym_code_for_trade_mark_sign;
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
			!TRUEP(Gensym_esc_for_linebreak_qm) ? 
			CHAR_EQ(character_or_character_code,
			Gensym_char_or_code_for_linebreak) : 
			EQ(character_or_character_code,
			Gensym_char_or_code_for_linebreak) && 
			EQ(escape_character_qm,Gensym_esc_for_linebreak_qm))
		    temp_1 = Gensym_code_for_linebreak;
		else if ( !TRUEP(escape_character_qm) &&  
			!TRUEP(Gensym_esc_for_paragraph_break_qm) ? 
			CHAR_EQ(character_or_character_code,
			Gensym_char_or_code_for_paragraph_break) : 
			EQ(character_or_character_code,
			Gensym_char_or_code_for_paragraph_break) && 
			EQ(escape_character_qm,
			Gensym_esc_for_paragraph_break_qm))
		    temp_1 = Gensym_code_for_paragraph_break;
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
Object transcode_character_for_utf_g_transcoder(utf_g_transcoder)
    Object utf_g_transcoder;
{
    Object transcoder, svref_new_value;
    Object current_extended_utf_g_low_half_character_qm, gensym_character_code;
    Object row, temp_1, code;
    SI_Long character_1, unicode_full_row, gensymed_symbol, gensymed_symbol_1;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(28,235);
    transcoder = utf_g_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
	svref_new_value = get_utf_g_transcoder_code(FIX(character_1),
		transcoder);
	SVREF(transcoder,FIX((SI_Long)7L)) = svref_new_value;
	if (IFIX(ISVREF(transcoder,(SI_Long)7L)) == (SI_Long)65535L)
	    return transcode_unhandled_character(FIX(character_1),transcoder);
	else if (IFIX(ISVREF(transcoder,(SI_Long)6L)) >>  -  - (SI_Long)8L 
		== (SI_Long)247L) {
	    if (IFIX(ISVREF(transcoder,(SI_Long)7L)) >>  -  - (SI_Long)8L 
		    == (SI_Long)248L) {
		current_extended_utf_g_low_half_character_qm = 
			ISVREF(transcoder,(SI_Long)6L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_extended_utf_g_low_half_character_qm,Qcurrent_extended_utf_g_low_half_character_qm,current_extended_utf_g_low_half_character_qm,
			1);
		  gensym_character_code = ISVREF(transcoder,(SI_Long)7L);
		  temp = IFIX(gensym_character_code) < (SI_Long)256L ? 
			  TRUEP(ISVREF(Iso_latin1_special_character_code_map,
			  IFIX(gensym_character_code))) : TRUEP(Nil);
		  if (temp);
		  else if (FIXNUM_EQ(gensym_character_code,
			  Gensym_code_for_capital_ligature_oe))
		      temp = 'W';
		  else if (FIXNUM_EQ(gensym_character_code,
			  Gensym_code_for_small_ligature_oe))
		      temp = 'w';
		  else if (FIXNUM_EQ(gensym_character_code,
			  Gensym_code_for_bullet))
		      temp = '*';
		  else if (FIXNUM_EQ(gensym_character_code,
			  Gensym_code_for_small_letter_f_with_hook))
		      temp = '&';
		  else if (FIXNUM_EQ(gensym_character_code,
			  Gensym_code_for_trade_mark_sign))
		      temp = ':';
		  else
		      temp = TRUEP(Qnil);
		  if (temp) {
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
			    result = VALUES_1(FIX(gensymed_symbol + 
				    gensymed_symbol_1));
			}
			else
			    result = VALUES_1(Nil);
		      POP_SPECIAL();
		  }
		  else if ((SI_Long)8192L <= IFIX(gensym_character_code) 
			  && IFIX(gensym_character_code) <= (SI_Long)8447L) {
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
			    result = VALUES_1(FIX(gensymed_symbol + 
				    gensymed_symbol_1));
			}
			else
			    result = VALUES_1(Nil);
		      POP_SPECIAL();
		  }
		  else {
		      temp_1 = 
			      map_gensym_han_character_code_to_unicode(gensym_character_code);
		      if (temp_1)
			  result = VALUES_1(temp_1);
		      else {
			  row = FIX(IFIX(gensym_character_code) >>  -  - 
				  (SI_Long)8L);
			  PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			    unicode_full_row = 
				    UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
				    IFIX(Row));
			    if ( !(unicode_full_row == 
				    IFIX(Invalid_unicode_full_row))) {
				gensymed_symbol = unicode_full_row << 
					(SI_Long)8L;
				gensymed_symbol_1 = (SI_Long)255L & 
					IFIX(gensym_character_code);
				temp_1 = FIX(gensymed_symbol + 
					gensymed_symbol_1);
			    }
			    else
				temp_1 = Nil;
			  POP_SPECIAL();
			  if (temp_1)
			      result = VALUES_1(temp_1);
			  else if (Current_extended_utf_g_low_half_character_qm)
			      result = map_extended_utf_g_characters_to_unicode(Current_extended_utf_g_low_half_character_qm,
				      gensym_character_code);
			  else
			      result = VALUES_1(FIX((SI_Long)65535L));
		      }
		  }
		POP_SPECIAL();
		return result;
	    }
	    else
		return transcode_unhandled_character(FIX(character_1),
			transcoder);
	}
	else if (IFIX(ISVREF(transcoder,(SI_Long)7L)) >>  -  - (SI_Long)8L 
		== (SI_Long)247L)
	    return VALUES_1(FIX((SI_Long)65535L));
	else {
	    gensym_character_code = ISVREF(transcoder,(SI_Long)7L);
	    temp = IFIX(gensym_character_code) < (SI_Long)256L ? 
		    TRUEP(ISVREF(Iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code))) : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_capital_ligature_oe))
		temp = 'W';
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_small_ligature_oe))
		temp = 'w';
	    else if (FIXNUM_EQ(gensym_character_code,Gensym_code_for_bullet))
		temp = '*';
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_small_letter_f_with_hook))
		temp = '&';
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_trade_mark_sign))
		temp = ':';
	    else
		temp = TRUEP(Qnil);
	    if (temp) {
		row = FIX(IFIX(gensym_character_code) >>  -  - (SI_Long)8L);
		PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		  unicode_full_row = 
			  UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
			  IFIX(Row));
		  if ( !(unicode_full_row == IFIX(Invalid_unicode_full_row))) {
		      gensymed_symbol = unicode_full_row << (SI_Long)8L;
		      gensymed_symbol_1 = (SI_Long)255L & 
			      IFIX(gensym_character_code);
		      code = FIX(gensymed_symbol + gensymed_symbol_1);
		  }
		  else
		      code = Nil;
		POP_SPECIAL();
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
		      code = FIX(gensymed_symbol + gensymed_symbol_1);
		  }
		  else
		      code = Nil;
		POP_SPECIAL();
	    }
	    else {
		code = 
			map_gensym_han_character_code_to_unicode(gensym_character_code);
		if (code);
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
			  code = FIX(gensymed_symbol + gensymed_symbol_1);
		      }
		      else
			  code = Nil;
		    POP_SPECIAL();
		    if (code);
		    else if (Current_extended_utf_g_low_half_character_qm)
			code = 
				map_extended_utf_g_characters_to_unicode(Current_extended_utf_g_low_half_character_qm,
				gensym_character_code);
		    else
			code = FIX((SI_Long)65535L);
		}
	    }
	    if (IFIX(code) == (SI_Long)65535L)
		return transcode_unhandled_character(FIX(character_1),
			transcoder);
	    else
		return VALUES_1(code);
	}
    }
    else {
	ISVREF(transcoder,(SI_Long)7L) = FIX((SI_Long)65535L);
	return transcode_unhandled_character(FIX(character_1),transcoder);
    }
}

/* EXPORT-CHARACTER-FOR-UTF-G-TRANSCODER */
Object export_character_for_utf_g_transcoder(utf_g_transcoder)
    Object utf_g_transcoder;
{
    Object transcoder, temp, svref_new_value, escape_character_qm;
    Object character_or_character_code, extended_escape_character_qm;
    Object extended_character_or_character_code_qm, row, octet_1_qm, code_1;
    Object quotient, remainder_1, character_3;
    SI_Long character_1, character_2, unicode, code, arg, arg_1, arg_2;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1, octet_2;
    SI_Long octet_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(28,236);
    transcoder = utf_g_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
    if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L || 
	    character_1 == (SI_Long)9L) {
	if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	    temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	    if (EQ(temp,Qper_platform)) {
		if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
			Qvms) || EQ(G2_operating_system,Qwin32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2_operating_system,Qunix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp,Qcr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp,Qlf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp,Qcrlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp,Qunicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp,Qunicode_paragraph_separator))
		return VALUES_1(FIX((SI_Long)8233L));
	    else
		return VALUES_1(FIX(character_1));
	}
	else
	    return VALUES_1(FIX(character_1));
    }
    else if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		gensym_cons_1(FIX((SI_Long)64L),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	character_2 = character_1 == (SI_Long)8232L ? (SI_Long)76L : 
		(SI_Long)80L;
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		gensym_cons_1(FIX(character_2),Nil));
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
		    ISVREF(Iso_latin1_special_character_code_map,unicode) :
		     Nil;
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
		escape_character_qm = Pct_tl;
	    }
	    else {
		escape_character_qm = Pct_bs;
		arg = (SI_Long)8192L;
		arg_1 = unicode + IFIX(Unicode_offset_for_gensym_cyrillic);
		arg_2 = (SI_Long)8447L;
		character_or_character_code = arg <= arg_1 && arg_1 <= 
			arg_2 ? FIX(unicode + 
			IFIX(Unicode_offset_for_gensym_cyrillic)) : Nil;
		if (character_or_character_code);
		else {
		    character_or_character_code = 
			    map_unicode_to_gensym_han_character_code(FIX(unicode));
		    if (character_or_character_code);
		    else {
			row = FIX(unicode >>  -  - (SI_Long)8L);
			PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			  gensym_full_row = 
				  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
				  IFIX(Row));
			  if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			      gensymed_symbol = gensym_full_row << (SI_Long)8L;
			      gensymed_symbol_1 = (SI_Long)255L & unicode;
			      character_or_character_code = 
				      FIX(gensymed_symbol + gensymed_symbol_1);
			  }
			  else
			      character_or_character_code = Nil;
			POP_SPECIAL();
			if (character_or_character_code);
			else {
			    extended_escape_character_qm = Pct_bs;
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
		    gensym_cons_1(escape_character_qm,Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    temp = escape_character_qm;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L)))) {
		octet_1_qm = Nil;
		octet_2 = (SI_Long)0L;
		octet_3 = (SI_Long)0L;
		code_1 = character_or_character_code;
		result = chestnut_floorf_function(FIX(IFIX(code_1) & 
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
			    (SI_Long)5L),gensym_cons_1(character_3,Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		}
		character_2 = octet_2;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX(character_2),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = octet_3;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX(character_2),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		if (extended_escape_character_qm) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    gensym_cons_1(extended_escape_character_qm,Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    code_1 = extended_character_or_character_code_qm;
		    result = chestnut_floorf_function(FIX(IFIX(code_1) & 
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
				(SI_Long)5L),gensym_cons_1(character_3,Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    character_2 = octet_2;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_2),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    character_2 = octet_3;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_2),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		}
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 64:
		  case 126:
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    gensym_cons_1(character_or_character_code,Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    break;
		  default:
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    code_1 = character_or_character_code;
		    result = chestnut_floorf_function(FIX(IFIX(code_1) & 
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
				(SI_Long)5L),gensym_cons_1(character_3,Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    character_2 = octet_2;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_2),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    character_2 = octet_3;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_2),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    if (extended_escape_character_qm) {
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				gensym_cons_1(extended_escape_character_qm,
				Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			code_1 = extended_character_or_character_code_qm;
			result = chestnut_floorf_function(FIX(IFIX(code_1) 
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
				    (SI_Long)5L),gensym_cons_1(character_3,
				    Nil));
			    SVREF(transcoder,FIX((SI_Long)5L)) = 
				    svref_new_value;
			}
			character_2 = octet_2;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX(character_2),Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
			character_2 = octet_3;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX(character_2),Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    break;
		}
	    return VALUES_1(FIX((SI_Long)65535L));
	}
    }
}

Object The_type_description_of_utf_g_ascii_as_much_as_possible_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders, Qchain_of_available_utf_g_ascii_as_much_as_possible_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Utf_g_ascii_as_much_as_possible_transcoder_count, Qutf_g_ascii_as_much_as_possible_transcoder_count);

Object Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector = UNBOUND;

/* UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object utf_g_ascii_as_much_as_possible_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,237);
    temp = Utf_g_ascii_as_much_as_possible_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-COUNT */
Object outstanding_utf_g_ascii_as_much_as_possible_transcoder_count()
{
    Object def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,238);
    gensymed_symbol = IFIX(Utf_g_ascii_as_much_as_possible_transcoder_count);
    def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable = 
	    Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable))
	goto end_loop;
    def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable = 
	    ISVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-1 */
Object reclaim_utf_g_ascii_as_much_as_possible_transcoder_1(utf_g_ascii_as_much_as_possible_transcoder)
    Object utf_g_ascii_as_much_as_possible_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,239);
    inline_note_reclaim_cons(utf_g_ascii_as_much_as_possible_transcoder,Nil);
    temp = 
	    ISVREF(Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(utf_g_ascii_as_much_as_possible_transcoder,FIX((SI_Long)0L)) = temp;
    temp = 
	    Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = utf_g_ascii_as_much_as_possible_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER */
Object reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder(utf_g_ascii_as_much_as_possible_transcoder)
    Object utf_g_ascii_as_much_as_possible_transcoder;
{
    x_note_fn_call(28,240);
    return reclaim_utf_g_ascii_as_much_as_possible_transcoder_1(utf_g_ascii_as_much_as_possible_transcoder);
}

static Object Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct;  /* g2-defstruct-structure-name::utf-g-ascii-as-much-as-possible-transcoder-g2-struct */

/* MAKE-PERMANENT-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_utf_g_ascii_as_much_as_possible_transcoder_structure_internal()
{
    Object def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable;
    Object defstruct_g2_utf_g_ascii_as_much_as_possible_transcoder_variable;
    Object the_array, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,241);
    def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable = Nil;
    atomic_incff_symval(Qutf_g_ascii_as_much_as_possible_transcoder_count,
	    FIX((SI_Long)1L));
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
		ISVREF(Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)0L)) = temp;
	temp = 
		Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable);
}

/* MAKE-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-1 */
Object make_utf_g_ascii_as_much_as_possible_transcoder_1()
{
    Object def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(28,242);
    def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable = 
	    ISVREF(Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable) {
	svref_arg_1 = 
		Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct;
    }
    else
	def_structure_utf_g_ascii_as_much_as_possible_transcoder_variable 
		= 
		make_permanent_utf_g_ascii_as_much_as_possible_transcoder_structure_internal();
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
Object export_character_for_utf_g_ascii_as_much_as_possible_transcoder(utf_g_ascii_as_much_as_possible_transcoder)
    Object utf_g_ascii_as_much_as_possible_transcoder;
{
    Object transcoder, temp, svref_new_value, escape_character_qm;
    Object character_or_character_code, extended_escape_character_qm;
    Object extended_character_or_character_code_qm, row, octet_1_qm, code_1;
    Object quotient, remainder_1, character_2;
    SI_Long character_1, unicode, code, arg, arg_1, arg_2, gensym_full_row;
    SI_Long gensymed_symbol, gensymed_symbol_1, octet_2, octet_3, character_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(28,243);
    transcoder = utf_g_ascii_as_much_as_possible_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
    if (character_1 == (SI_Long)10L || character_1 == (SI_Long)13L || 
	    character_1 == (SI_Long)9L || character_1 == (SI_Long)8232L || 
	    character_1 == (SI_Long)8233L) {
	if (character_1 == (SI_Long)8232L || character_1 == (SI_Long)8233L) {
	    temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	    if (EQ(temp,Qper_platform)) {
		if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
			Qvms) || EQ(G2_operating_system,Qwin32)) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX((SI_Long)10L),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    return VALUES_1(FIX((SI_Long)13L));
		}
		else if (EQ(G2_operating_system,Qunix))
		    return VALUES_1(FIX((SI_Long)10L));
		else
		    return VALUES_1(FIX((SI_Long)10L));
	    }
	    else if (EQ(temp,Qcr))
		return VALUES_1(FIX((SI_Long)13L));
	    else if (EQ(temp,Qlf))
		return VALUES_1(FIX((SI_Long)10L));
	    else if (EQ(temp,Qcrlf)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(temp,Qunicode_line_separator))
		return VALUES_1(FIX((SI_Long)8232L));
	    else if (EQ(temp,Qunicode_paragraph_separator))
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
		    ISVREF(Iso_latin1_special_character_code_map,unicode) :
		     Nil;
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
		escape_character_qm = Pct_tl;
	    }
	    else {
		escape_character_qm = Pct_bs;
		arg = (SI_Long)8192L;
		arg_1 = unicode + IFIX(Unicode_offset_for_gensym_cyrillic);
		arg_2 = (SI_Long)8447L;
		character_or_character_code = arg <= arg_1 && arg_1 <= 
			arg_2 ? FIX(unicode + 
			IFIX(Unicode_offset_for_gensym_cyrillic)) : Nil;
		if (character_or_character_code);
		else {
		    character_or_character_code = 
			    map_unicode_to_gensym_han_character_code(FIX(unicode));
		    if (character_or_character_code);
		    else {
			row = FIX(unicode >>  -  - (SI_Long)8L);
			PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			  gensym_full_row = 
				  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
				  IFIX(Row));
			  if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			      gensymed_symbol = gensym_full_row << (SI_Long)8L;
			      gensymed_symbol_1 = (SI_Long)255L & unicode;
			      character_or_character_code = 
				      FIX(gensymed_symbol + gensymed_symbol_1);
			  }
			  else
			      character_or_character_code = Nil;
			POP_SPECIAL();
			if (character_or_character_code);
			else {
			    extended_escape_character_qm = Pct_bs;
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
		    gensym_cons_1(escape_character_qm,Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    temp = escape_character_qm;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L)))) {
		octet_1_qm = Nil;
		octet_2 = (SI_Long)0L;
		octet_3 = (SI_Long)0L;
		code_1 = character_or_character_code;
		result = chestnut_floorf_function(FIX(IFIX(code_1) & 
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
			    (SI_Long)5L),gensym_cons_1(character_2,Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		}
		character_3 = octet_2;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX(character_3),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_3 = octet_3;
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX(character_3),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		if (extended_escape_character_qm) {
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    gensym_cons_1(extended_escape_character_qm,Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    code_1 = extended_character_or_character_code_qm;
		    result = chestnut_floorf_function(FIX(IFIX(code_1) & 
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
				(SI_Long)5L),gensym_cons_1(character_2,Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    character_3 = octet_2;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_3),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    character_3 = octet_3;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_3),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		}
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 64:
		  case 126:
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),
			    gensym_cons_1(character_or_character_code,Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    break;
		  default:
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    code_1 = character_or_character_code;
		    result = chestnut_floorf_function(FIX(IFIX(code_1) & 
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
				(SI_Long)5L),gensym_cons_1(character_2,Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    character_3 = octet_2;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_3),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    character_3 = octet_3;
		    svref_new_value = nconc2(ISVREF(transcoder,
			    (SI_Long)5L),gensym_cons_1(FIX(character_3),Nil));
		    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    if (extended_escape_character_qm) {
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				gensym_cons_1(extended_escape_character_qm,
				Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			code_1 = extended_character_or_character_code_qm;
			result = chestnut_floorf_function(FIX(IFIX(code_1) 
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
				    (SI_Long)5L),gensym_cons_1(character_2,
				    Nil));
			    SVREF(transcoder,FIX((SI_Long)5L)) = 
				    svref_new_value;
			}
			character_3 = octet_2;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX(character_3),Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
			character_3 = octet_3;
			svref_new_value = nconc2(ISVREF(transcoder,
				(SI_Long)5L),
				gensym_cons_1(FIX(character_3),Nil));
			SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		    }
		    break;
		}
	    return VALUES_1(FIX((SI_Long)65535L));
	}
    }
}

Object The_type_description_of_unicode_ucs_2_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_unicode_ucs_2_transcoders, Qchain_of_available_unicode_ucs_2_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Unicode_ucs_2_transcoder_count, Qunicode_ucs_2_transcoder_count);

Object Chain_of_available_unicode_ucs_2_transcoders_vector = UNBOUND;

/* UNICODE-UCS-2-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object unicode_ucs_2_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,244);
    temp = Unicode_ucs_2_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UNICODE-UCS-2-TRANSCODER-COUNT */
Object outstanding_unicode_ucs_2_transcoder_count()
{
    Object def_structure_unicode_ucs_2_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,245);
    gensymed_symbol = IFIX(Unicode_ucs_2_transcoder_count);
    def_structure_unicode_ucs_2_transcoder_variable = 
	    Chain_of_available_unicode_ucs_2_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_unicode_ucs_2_transcoder_variable))
	goto end_loop;
    def_structure_unicode_ucs_2_transcoder_variable = 
	    ISVREF(def_structure_unicode_ucs_2_transcoder_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UNICODE-UCS-2-TRANSCODER-1 */
Object reclaim_unicode_ucs_2_transcoder_1(unicode_ucs_2_transcoder)
    Object unicode_ucs_2_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,246);
    inline_note_reclaim_cons(unicode_ucs_2_transcoder,Nil);
    temp = ISVREF(Chain_of_available_unicode_ucs_2_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(unicode_ucs_2_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_unicode_ucs_2_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = unicode_ucs_2_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNICODE-UCS-2-TRANSCODER */
Object reclaim_structure_for_unicode_ucs_2_transcoder(unicode_ucs_2_transcoder)
    Object unicode_ucs_2_transcoder;
{
    x_note_fn_call(28,247);
    return reclaim_unicode_ucs_2_transcoder_1(unicode_ucs_2_transcoder);
}

static Object Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct;  /* g2-defstruct-structure-name::unicode-ucs-2-transcoder-g2-struct */

/* MAKE-PERMANENT-UNICODE-UCS-2-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_unicode_ucs_2_transcoder_structure_internal()
{
    Object def_structure_unicode_ucs_2_transcoder_variable;
    Object defstruct_g2_unicode_ucs_2_transcoder_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,248);
    def_structure_unicode_ucs_2_transcoder_variable = Nil;
    atomic_incff_symval(Qunicode_ucs_2_transcoder_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_unicode_ucs_2_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_unicode_ucs_2_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_unicode_ucs_2_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_unicode_ucs_2_transcoder_variable);
}

/* MAKE-UNICODE-UCS-2-TRANSCODER-1 */
Object make_unicode_ucs_2_transcoder_1()
{
    Object def_structure_unicode_ucs_2_transcoder_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(28,249);
    def_structure_unicode_ucs_2_transcoder_variable = 
	    ISVREF(Chain_of_available_unicode_ucs_2_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_unicode_ucs_2_transcoder_variable) {
	svref_arg_1 = Chain_of_available_unicode_ucs_2_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_unicode_ucs_2_transcoder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_unicode_ucs_2_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct;
    }
    else
	def_structure_unicode_ucs_2_transcoder_variable = 
		make_permanent_unicode_ucs_2_transcoder_structure_internal();
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
Object transcode_character_for_unicode_ucs_2_transcoder(unicode_ucs_2_transcoder)
    Object unicode_ucs_2_transcoder;
{
    Object transcoder, text_sequence, temp;
    SI_Long lead_character, trail_character, lead_octet, trail_octet;
    SI_Long gensymed_symbol, gensymed_symbol_1, character_1;

    x_note_fn_call(28,250);
    transcoder = unicode_ucs_2_transcoder;
    lead_character = IFIX(get_transcoder_character(transcoder));
    trail_character = (SI_Long)0L;
    text_sequence = ISVREF(transcoder,(SI_Long)1L);
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	return transcode_unhandled_character(FIX(lead_character),transcoder);
    else if ( !(lead_character < (SI_Long)256L && trail_character < 
	    (SI_Long)256L))
	return transcode_unhandled_character(FIX(lead_character),transcoder);
    else {
	trail_character = IFIX(get_transcoder_character(transcoder));
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
Object export_character_for_unicode_ucs_2_transcoder(unicode_ucs_2_transcoder)
    Object unicode_ucs_2_transcoder;
{
    Object transcoder, character_1, temp, svref_new_value;
    SI_Long character_2, character_3;

    x_note_fn_call(28,251);
    transcoder = unicode_ucs_2_transcoder;
    character_1 = get_transcoder_character(transcoder);
    if (IFIX(character_1) == (SI_Long)8232L || IFIX(character_1) == 
	    (SI_Long)8233L) {
	temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	if (EQ(temp,Qper_platform)) {
	    if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
		    Qvms) || EQ(G2_operating_system,Qwin32)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = (SI_Long)13L;
	    }
	    else if (EQ(G2_operating_system,Qunix))
		character_2 = (SI_Long)10L;
	    else
		character_2 = (SI_Long)10L;
	}
	else if (EQ(temp,Qcr))
	    character_2 = (SI_Long)13L;
	else if (EQ(temp,Qlf))
	    character_2 = (SI_Long)10L;
	else if (EQ(temp,Qcrlf)) {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    gensym_cons_1(FIX((SI_Long)10L),Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    character_2 = (SI_Long)13L;
	}
	else if (EQ(temp,Qunicode_line_separator))
	    character_2 = (SI_Long)8232L;
	else if (EQ(temp,Qunicode_paragraph_separator))
	    character_2 = (SI_Long)8233L;
	else
	    character_2 = IFIX(character_1);
    }
    else
	character_2 = IFIX(character_1);
    if (ISVREF(transcoder,(SI_Long)7L)) {
	character_3 = character_2 >>  -  - (SI_Long)8L;
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		gensym_cons_1(FIX(character_3),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	return VALUES_1(FIX(character_2 & (SI_Long)255L));
    }
    else {
	character_3 = character_2 & (SI_Long)255L;
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		gensym_cons_1(FIX(character_3),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	return VALUES_1(FIX(character_2 >>  -  - (SI_Long)8L));
    }
}

Object The_type_description_of_unicode_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_unicode_transcoders, Qchain_of_available_unicode_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Unicode_transcoder_count, Qunicode_transcoder_count);

Object Chain_of_available_unicode_transcoders_vector = UNBOUND;

/* UNICODE-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object unicode_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,252);
    temp = Unicode_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UNICODE-TRANSCODER-COUNT */
Object outstanding_unicode_transcoder_count()
{
    Object def_structure_unicode_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,253);
    gensymed_symbol = IFIX(Unicode_transcoder_count);
    def_structure_unicode_transcoder_variable = 
	    Chain_of_available_unicode_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_unicode_transcoder_variable))
	goto end_loop;
    def_structure_unicode_transcoder_variable = 
	    ISVREF(def_structure_unicode_transcoder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UNICODE-TRANSCODER-1 */
Object reclaim_unicode_transcoder_1(unicode_transcoder)
    Object unicode_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,254);
    inline_note_reclaim_cons(unicode_transcoder,Nil);
    temp = ISVREF(Chain_of_available_unicode_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(unicode_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_unicode_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = unicode_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNICODE-TRANSCODER */
Object reclaim_structure_for_unicode_transcoder(unicode_transcoder)
    Object unicode_transcoder;
{
    x_note_fn_call(28,255);
    return reclaim_unicode_transcoder_1(unicode_transcoder);
}

static Object Qg2_defstruct_structure_name_unicode_transcoder_g2_struct;  /* g2-defstruct-structure-name::unicode-transcoder-g2-struct */

/* MAKE-PERMANENT-UNICODE-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_unicode_transcoder_structure_internal()
{
    Object def_structure_unicode_transcoder_variable;
    Object defstruct_g2_unicode_transcoder_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,256);
    def_structure_unicode_transcoder_variable = Nil;
    atomic_incff_symval(Qunicode_transcoder_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_unicode_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_unicode_transcoder_variable,FIX((SI_Long)0L)) 
		= temp;
	temp = Chain_of_available_unicode_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_unicode_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_unicode_transcoder_variable);
}

/* MAKE-UNICODE-TRANSCODER-1 */
Object make_unicode_transcoder_1()
{
    Object def_structure_unicode_transcoder_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,257);
    def_structure_unicode_transcoder_variable = 
	    ISVREF(Chain_of_available_unicode_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_unicode_transcoder_variable) {
	svref_arg_1 = Chain_of_available_unicode_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_unicode_transcoder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_unicode_transcoder_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_unicode_transcoder_g2_struct;
    }
    else
	def_structure_unicode_transcoder_variable = 
		make_permanent_unicode_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_unicode_transcoder_variable,Nil);
    ISVREF(def_structure_unicode_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_unicode_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_unicode_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_unicode_transcoder_variable);
}

/* TRANSCODE-CHARACTER-FOR-UNICODE-TRANSCODER */
Object transcode_character_for_unicode_transcoder(unicode_transcoder)
    Object unicode_transcoder;
{
    Object character_1, transcoder;

    x_note_fn_call(28,258);
    character_1 = get_transcoder_character(unicode_transcoder);
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
Object export_character_for_unicode_transcoder(unicode_transcoder)
    Object unicode_transcoder;
{
    Object character_1, transcoder, temp, svref_new_value;

    x_note_fn_call(28,259);
    character_1 = get_transcoder_character(unicode_transcoder);
    transcoder = unicode_transcoder;
    if (IFIX(character_1) == (SI_Long)8232L || IFIX(character_1) == 
	    (SI_Long)8233L) {
	temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	if (EQ(temp,Qper_platform)) {
	    if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
		    Qvms) || EQ(G2_operating_system,Qwin32)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		return VALUES_1(FIX((SI_Long)13L));
	    }
	    else if (EQ(G2_operating_system,Qunix))
		return VALUES_1(FIX((SI_Long)10L));
	    else
		return VALUES_1(FIX((SI_Long)10L));
	}
	else if (EQ(temp,Qcr))
	    return VALUES_1(FIX((SI_Long)13L));
	else if (EQ(temp,Qlf))
	    return VALUES_1(FIX((SI_Long)10L));
	else if (EQ(temp,Qcrlf)) {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    gensym_cons_1(FIX((SI_Long)10L),Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    return VALUES_1(FIX((SI_Long)13L));
	}
	else if (EQ(temp,Qunicode_line_separator))
	    return VALUES_1(FIX((SI_Long)8232L));
	else if (EQ(temp,Qunicode_paragraph_separator))
	    return VALUES_1(FIX((SI_Long)8233L));
	else
	    return VALUES_1(character_1);
    }
    else
	return VALUES_1(character_1);
}

Object The_type_description_of_unicode_byte_swapped_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_unicode_byte_swapped_transcoders, Qchain_of_available_unicode_byte_swapped_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Unicode_byte_swapped_transcoder_count, Qunicode_byte_swapped_transcoder_count);

Object Chain_of_available_unicode_byte_swapped_transcoders_vector = UNBOUND;

/* UNICODE-BYTE-SWAPPED-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object unicode_byte_swapped_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,260);
    temp = Unicode_byte_swapped_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UNICODE-BYTE-SWAPPED-TRANSCODER-COUNT */
Object outstanding_unicode_byte_swapped_transcoder_count()
{
    Object def_structure_unicode_byte_swapped_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,261);
    gensymed_symbol = IFIX(Unicode_byte_swapped_transcoder_count);
    def_structure_unicode_byte_swapped_transcoder_variable = 
	    Chain_of_available_unicode_byte_swapped_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_unicode_byte_swapped_transcoder_variable))
	goto end_loop;
    def_structure_unicode_byte_swapped_transcoder_variable = 
	    ISVREF(def_structure_unicode_byte_swapped_transcoder_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UNICODE-BYTE-SWAPPED-TRANSCODER-1 */
Object reclaim_unicode_byte_swapped_transcoder_1(unicode_byte_swapped_transcoder)
    Object unicode_byte_swapped_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,262);
    inline_note_reclaim_cons(unicode_byte_swapped_transcoder,Nil);
    temp = 
	    ISVREF(Chain_of_available_unicode_byte_swapped_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(unicode_byte_swapped_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_unicode_byte_swapped_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = unicode_byte_swapped_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNICODE-BYTE-SWAPPED-TRANSCODER */
Object reclaim_structure_for_unicode_byte_swapped_transcoder(unicode_byte_swapped_transcoder)
    Object unicode_byte_swapped_transcoder;
{
    x_note_fn_call(28,263);
    return reclaim_unicode_byte_swapped_transcoder_1(unicode_byte_swapped_transcoder);
}

static Object Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct;  /* g2-defstruct-structure-name::unicode-byte-swapped-transcoder-g2-struct */

/* MAKE-PERMANENT-UNICODE-BYTE-SWAPPED-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_unicode_byte_swapped_transcoder_structure_internal()
{
    Object def_structure_unicode_byte_swapped_transcoder_variable;
    Object defstruct_g2_unicode_byte_swapped_transcoder_variable, the_array;
    Object temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,264);
    def_structure_unicode_byte_swapped_transcoder_variable = Nil;
    atomic_incff_symval(Qunicode_byte_swapped_transcoder_count,
	    FIX((SI_Long)1L));
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
	temp = 
		ISVREF(Chain_of_available_unicode_byte_swapped_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_unicode_byte_swapped_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_unicode_byte_swapped_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_unicode_byte_swapped_transcoder_variable);
}

/* MAKE-UNICODE-BYTE-SWAPPED-TRANSCODER-1 */
Object make_unicode_byte_swapped_transcoder_1()
{
    Object def_structure_unicode_byte_swapped_transcoder_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(28,265);
    def_structure_unicode_byte_swapped_transcoder_variable = 
	    ISVREF(Chain_of_available_unicode_byte_swapped_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_unicode_byte_swapped_transcoder_variable) {
	svref_arg_1 = 
		Chain_of_available_unicode_byte_swapped_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_unicode_byte_swapped_transcoder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_unicode_byte_swapped_transcoder_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct;
    }
    else
	def_structure_unicode_byte_swapped_transcoder_variable = 
		make_permanent_unicode_byte_swapped_transcoder_structure_internal();
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
Object transcode_character_for_unicode_byte_swapped_transcoder(unicode_byte_swapped_transcoder)
    Object unicode_byte_swapped_transcoder;
{
    Object transcoder;
    SI_Long character_1, lead_character, trail_character, lead_octet;
    SI_Long trail_octet, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,266);
    transcoder = unicode_byte_swapped_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
Object export_character_for_unicode_byte_swapped_transcoder(unicode_byte_swapped_transcoder)
    Object unicode_byte_swapped_transcoder;
{
    Object transcoder, character_1, temp, svref_new_value;
    SI_Long character_2, lead_character, trail_character, lead_octet;
    SI_Long trail_octet, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,267);
    transcoder = unicode_byte_swapped_transcoder;
    character_1 = get_transcoder_character(transcoder);
    if (IFIX(character_1) == (SI_Long)8232L || IFIX(character_1) == 
	    (SI_Long)8233L) {
	temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	if (EQ(temp,Qper_platform)) {
	    if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
		    Qvms) || EQ(G2_operating_system,Qwin32)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = (SI_Long)13L;
	    }
	    else if (EQ(G2_operating_system,Qunix))
		character_2 = (SI_Long)10L;
	    else
		character_2 = (SI_Long)10L;
	}
	else if (EQ(temp,Qcr))
	    character_2 = (SI_Long)13L;
	else if (EQ(temp,Qlf))
	    character_2 = (SI_Long)10L;
	else if (EQ(temp,Qcrlf)) {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    gensym_cons_1(FIX((SI_Long)10L),Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    character_2 = (SI_Long)13L;
	}
	else if (EQ(temp,Qunicode_line_separator))
	    character_2 = (SI_Long)8232L;
	else if (EQ(temp,Qunicode_paragraph_separator))
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
Object create_transcoder_for_iso_8859_1()
{
    x_note_fn_call(28,268);
    return make_iso_8859_transcoder_1(FIX((SI_Long)1L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_1),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-2 */
Object create_transcoder_for_iso_8859_2()
{
    x_note_fn_call(28,269);
    return make_iso_8859_transcoder_1(FIX((SI_Long)2L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_2),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-3 */
Object create_transcoder_for_iso_8859_3()
{
    x_note_fn_call(28,270);
    return make_iso_8859_transcoder_1(FIX((SI_Long)4L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_3),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-4 */
Object create_transcoder_for_iso_8859_4()
{
    x_note_fn_call(28,271);
    return make_iso_8859_transcoder_1(FIX((SI_Long)4L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_4),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-5 */
Object create_transcoder_for_iso_8859_5()
{
    x_note_fn_call(28,272);
    return make_iso_8859_transcoder_1(FIX((SI_Long)5L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_5),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-6 */
Object create_transcoder_for_iso_8859_6()
{
    x_note_fn_call(28,273);
    return make_iso_8859_transcoder_1(FIX((SI_Long)6L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_6),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-7 */
Object create_transcoder_for_iso_8859_7()
{
    x_note_fn_call(28,274);
    return make_iso_8859_transcoder_1(FIX((SI_Long)7L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_7),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-8 */
Object create_transcoder_for_iso_8859_8()
{
    x_note_fn_call(28,275);
    return make_iso_8859_transcoder_1(FIX((SI_Long)8L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_8),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-9 */
Object create_transcoder_for_iso_8859_9()
{
    x_note_fn_call(28,276);
    return make_iso_8859_transcoder_1(FIX((SI_Long)9L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_9),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-ISO-8859-10 */
Object create_transcoder_for_iso_8859_10()
{
    x_note_fn_call(28,277);
    return make_iso_8859_transcoder_1(FIX((SI_Long)10L),
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_10),
	    Qgraphic_character_set));
}

/* CREATE-TRANSCODER-FOR-GENSYM */
Object create_transcoder_for_gensym()
{
    x_note_fn_call(28,278);
    return make_utf_g_transcoder_1();
}

/* CREATE-TRANSCODER-FOR-GENSYM-WITH-ASCII-AS-MUCH-AS-POSSIBLE */
Object create_transcoder_for_gensym_with_ascii_as_much_as_possible()
{
    x_note_fn_call(28,279);
    return make_utf_g_ascii_as_much_as_possible_transcoder_1();
}

/* CREATE-TRANSCODER-FOR-UNICODE-UCS-2 */
Object create_transcoder_for_unicode_ucs_2()
{
    x_note_fn_call(28,280);
    return make_unicode_ucs_2_transcoder_1();
}

/* CREATE-TRANSCODER-FOR-UNICODE-UCS-2-BYTE-SWAPPED */
Object create_transcoder_for_unicode_ucs_2_byte_swapped()
{
    Object transcoder;

    x_note_fn_call(28,281);
    transcoder = make_unicode_ucs_2_transcoder_1();
    SVREF(transcoder,FIX((SI_Long)7L)) = T;
    return VALUES_1(transcoder);
}

/* CREATE-TRANSCODER-FOR-UNICODE */
Object create_transcoder_for_unicode()
{
    x_note_fn_call(28,282);
    return make_unicode_transcoder_1();
}

/* CREATE-TRANSCODER-FOR-UNICODE-BYTE-SWAPPED */
Object create_transcoder_for_unicode_byte_swapped()
{
    x_note_fn_call(28,283);
    return make_unicode_byte_swapped_transcoder_1();
}

static Object Qtranscoder_creation_function;  /* transcoder-creation-function */

/* MAKE-TRANSCODER-PER-TEXT-CONVERSION-STYLE */
Object make_transcoder_per_text_conversion_style(text_conversion_style,
	    text_sequence)
    Object text_conversion_style, text_sequence;
{
    Object gensymed_symbol, funcallable_creator;
    Object text_conversion_style_for_transcoder_being_created, transcoder;
    Declare_special(1);
    Object result;

    x_note_fn_call(28,284);
    gensymed_symbol = ISVREF(text_conversion_style,(SI_Long)2L);
    funcallable_creator = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtranscoder_creation_function);
    text_conversion_style_for_transcoder_being_created = text_conversion_style;
    PUSH_SPECIAL_WITH_SYMBOL(Text_conversion_style_for_transcoder_being_created,Qtext_conversion_style_for_transcoder_being_created,text_conversion_style_for_transcoder_being_created,
	    0);
      transcoder = FUNCALL_0(funcallable_creator);
      SVREF(transcoder,FIX((SI_Long)1L)) = text_sequence;
      SVREF(transcoder,FIX((SI_Long)4L)) = text_conversion_style;
      result = VALUES_1(transcoder);
    POP_SPECIAL();
    return result;
}

/* TWRITE-ASCII-FROM-WIDE-STRING */
Object twrite_ascii_from_wide_string(wide_string)
    Object wide_string;
{
    Object wide_character, temp, schar_arg_2, schar_new_value, thing_1;
    SI_Long length_of_string, i, ab_loop_bind_, thing;

    x_note_fn_call(28,285);
    length_of_string = IFIX(lengthw(wide_string));
    i = (SI_Long)0L;
    ab_loop_bind_ = length_of_string;
    wide_character = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character = FIX(UBYTE_16_ISAREF_1(wide_string,i));
    if (newline_p(wide_character)) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)10L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)10L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
    }
    else if (IFIX(wide_character) < (SI_Long)256L) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = wide_character;
	    twrite_wide_character(CHARACTERP(thing_1) ? CHAR_CODE(thing_1) 
		    : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
    }
    else;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* MAP-JIS-X-0208-BYTES-TO-UNICODE-CHARACTER */
Object map_jis_x_0208_bytes_to_unicode_character(lead_byte,trail_byte)
    Object lead_byte, trail_byte;
{
    Object contiguous_code_qm, temp;
    SI_Long jis_x_0208;

    x_note_fn_call(28,286);
    if ((SI_Long)33L <= IFIX(lead_byte) && IFIX(lead_byte) <= 
	    (SI_Long)116L && (SI_Long)33L <= IFIX(trail_byte) && 
	    IFIX(trail_byte) <= (SI_Long)126L) {
	jis_x_0208 = (IFIX(lead_byte) << (SI_Long)8L) + IFIX(trail_byte);
	contiguous_code_qm = gensym_jis_code_to_contiguous(FIX(jis_x_0208));
	temp = contiguous_code_qm ? 
		FIX(UBYTE_16_ISAREF_1(Jis_x_0208_to_unicode_map,
		IFIX(contiguous_code_qm))) : Nil;
    }
    else
	temp = Unicode_replacement_character;
    return VALUES_1(temp);
}

/* MAP-KS-C-5601-BYTES-TO-UNICODE-CHARACTER */
Object map_ks_c_5601_bytes_to_unicode_character(lead_byte,trail_byte)
    Object lead_byte, trail_byte;
{
    Object gensym_ks_c_5601, contiguous_code_qm, temp;
    SI_Long ks_c_5601;

    x_note_fn_call(28,287);
    if ((SI_Long)33L <= IFIX(lead_byte) && IFIX(lead_byte) <= 
	    (SI_Long)125L && (SI_Long)33L <= IFIX(trail_byte) && 
	    IFIX(trail_byte) <= (SI_Long)126L) {
	ks_c_5601 = (IFIX(lead_byte) << (SI_Long)8L) + IFIX(trail_byte);
	gensym_ks_c_5601 = ksc_to_gensym_ksc(FIX(ks_c_5601));
	contiguous_code_qm = gensym_ksc_code_to_contiguous(gensym_ks_c_5601);
	temp = contiguous_code_qm ? 
		FIX(UBYTE_16_ISAREF_1(Ks_c_5601_to_unicode_map,
		IFIX(contiguous_code_qm))) : Nil;
    }
    else
	temp = Unicode_replacement_character;
    return VALUES_1(temp);
}

/* MAP-GB-2312-BYTES-TO-UNICODE-CHARACTER */
Object map_gb_2312_bytes_to_unicode_character(lead_byte,trail_byte)
    Object lead_byte, trail_byte;
{
    Object temp;
    SI_Long gb_2312, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long index_1, code;

    x_note_fn_call(28,288);
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
	    code = UBYTE_16_ISAREF_1(Gb_2312_to_unicode_map,index_1);
	    temp = code == (SI_Long)65535L ? Nil : FIX(code);
	}
	else
	    temp = Nil;
    }
    else
	temp = Unicode_replacement_character;
    return VALUES_1(temp);
}

/* MAP-SHIFT-JIS-BYTES-TO-UNICODE-CHARACTER */
Object map_shift_jis_bytes_to_unicode_character(lead_byte_init,trail_byte_init)
    Object lead_byte_init, trail_byte_init;
{
    SI_Long lead_byte, trail_byte, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,289);
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
Object map_shift_jis_half_width_katakana_to_unicode(shift_jis_half_width_katakana_character)
    Object shift_jis_half_width_katakana_character;
{
    Object code;

    x_note_fn_call(28,290);
    code = shift_jis_half_width_katakana_character;
    return VALUES_1(FIX(IFIX(code) - (SI_Long)160L + (SI_Long)65376L));
}

/* SHIFT-JIS-X-0208-IN-TEXT-SEQUENCE-TO-UNICODE */
Object shift_jis_x_0208_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    SI_Long arg, arg_1, arg_2;
    char temp_1;

    x_note_fn_call(28,291);
    if (IFIX(character_1) < (SI_Long)128L)
	temp = character_1;
    else {
	arg = (SI_Long)161L;
	arg_1 = IFIX(character_1);
	arg_2 = (SI_Long)223L;
	if (arg <= arg_1 && arg_1 <= arg_2)
	    temp = map_shift_jis_half_width_katakana_to_unicode(character_1);
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
		    temp = Unicode_replacement_character;
		else {
		    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
		    gensymed_symbol = 
			    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			    Qtype_description_of_unique_type_name_of_gensym_structure),
			    (SI_Long)9L),(SI_Long)11L);
		    gensymed_symbol_1 = text_sequence;
		    temp = 
			    map_shift_jis_bytes_to_unicode_character(character_1,
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
Object jis_x_0208_euc_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(28,292);
    if (IFIX(character_1) < (SI_Long)160L)
	temp = character_1;
    else if (IFIX(character_1) < (SI_Long)128L)
	temp = Unicode_replacement_character;
    else if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
	    ISVREF(text_sequence,(SI_Long)3L)))
	temp = Unicode_replacement_character;
    else {
	temp = FIX(IFIX(character_1) >>  -  - (SI_Long)1L);
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	gensymed_symbol_2 = IFIX(inline_funcall_1(gensymed_symbol,
		gensymed_symbol_1));
	gensymed_symbol_3 = (SI_Long)1L;
	temp = map_jis_x_0208_bytes_to_unicode_character(temp,
		FIX(gensymed_symbol_2 >>  -  - gensymed_symbol_3));
    }
    return VALUES_1(temp);
}

/* KS-C-5601-EUC-IN-TEXT-SEQUENCE-TO-UNICODE */
Object ks_c_5601_euc_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(28,293);
    if (IFIX(character_1) < (SI_Long)160L)
	temp = character_1;
    else if (IFIX(character_1) < (SI_Long)128L)
	temp = Unicode_replacement_character;
    else if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
	    ISVREF(text_sequence,(SI_Long)3L)))
	temp = Unicode_replacement_character;
    else {
	temp = FIX(IFIX(character_1) >>  -  - (SI_Long)1L);
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	gensymed_symbol_2 = IFIX(inline_funcall_1(gensymed_symbol,
		gensymed_symbol_1));
	gensymed_symbol_3 = (SI_Long)1L;
	temp = map_ks_c_5601_bytes_to_unicode_character(temp,
		FIX(gensymed_symbol_2 >>  -  - gensymed_symbol_3));
    }
    return VALUES_1(temp);
}

/* GB-2312-EUC-IN-TEXT-SEQUENCE-TO-UNICODE */
Object gb_2312_euc_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(28,294);
    if (IFIX(character_1) < (SI_Long)160L)
	temp = character_1;
    else if (IFIX(character_1) < (SI_Long)128L)
	temp = Unicode_replacement_character;
    else if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),
	    ISVREF(text_sequence,(SI_Long)3L)))
	temp = Unicode_replacement_character;
    else {
	temp = FIX(IFIX(character_1) >>  -  - (SI_Long)1L);
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	gensymed_symbol_2 = IFIX(inline_funcall_1(gensymed_symbol,
		gensymed_symbol_1));
	gensymed_symbol_3 = (SI_Long)1L;
	temp = map_gb_2312_bytes_to_unicode_character(temp,
		FIX(gensymed_symbol_2 >>  -  - gensymed_symbol_3));
    }
    return VALUES_1(temp);
}

/* JIS-X-0208-IN-TEXT-SEQUENCE-TO-UNICODE */
Object jis_x_0208_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,295);
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	temp = Unicode_replacement_character;
    else {
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	temp = map_jis_x_0208_bytes_to_unicode_character(character_1,
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
    return VALUES_1(temp);
}

/* KS-C-5601-IN-TEXT-SEQUENCE-TO-UNICODE */
Object ks_c_5601_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,296);
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	temp = Unicode_replacement_character;
    else {
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	temp = map_ks_c_5601_bytes_to_unicode_character(character_1,
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
    return VALUES_1(temp);
}

/* GB-2312-IN-TEXT-SEQUENCE-TO-UNICODE */
Object gb_2312_in_text_sequence_to_unicode(text_sequence,character_1)
    Object text_sequence, character_1;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,297);
    if ( !FIXNUM_LT(ISVREF(text_sequence,(SI_Long)6L),ISVREF(text_sequence,
	    (SI_Long)3L)))
	temp = Unicode_replacement_character;
    else {
	gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)11L);
	gensymed_symbol_1 = text_sequence;
	temp = map_gb_2312_bytes_to_unicode_character(character_1,
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
    return VALUES_1(temp);
}

/* IMPORT-TEXT-STRING */
Object import_text_string varargs_1(int, n)
{
    Object string_1;
    Object purpose, start_qm, end_qm, style;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,298);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    purpose = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    style = getfq_function_no_default(INLINE_SYMBOL_PLIST(purpose),
	    Qtext_conversion_style_for_purpose);
    if (style);
    else
	style = Default_text_conversion_style;
    return import_text_string_per_text_conversion_style(4,string_1,style,
	    start_qm,end_qm);
}

/* IMPORT-TEXT-STRING-PER-TEXT-CONVERSION-STYLE */
Object import_text_string_per_text_conversion_style varargs_1(int, n)
{
    Object string_1, text_conversion_style;
    Object start_qm, end_qm, text_sequence, transcoder, gensymed_symbol;
    Object gensymed_symbol_1, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,299);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    text_conversion_style = REQUIRED_ARG_nonrelocating();
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    text_sequence = make_text_sequence(string_1,start_qm,end_qm);
    transcoder = 
	    make_transcoder_per_text_conversion_style(text_conversion_style,
	    text_sequence);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)14L);
    gensymed_symbol_1 = transcoder;
    temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = transcoder;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = text_sequence;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(temp);
}

/* EXPORT-TEXT-STRING-PER-TEXT-CONVERSION-STYLE */
Object export_text_string_per_text_conversion_style varargs_1(int, n)
{
    Object text_string, text_conversion_style;
    Object start_qm, end_qm, text_sequence, transcoder, gensymed_symbol;
    Object gensymed_symbol_1, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,300);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    text_conversion_style = REQUIRED_ARG_nonrelocating();
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    text_sequence = make_text_sequence(text_string,start_qm,end_qm);
    transcoder = 
	    make_transcoder_per_text_conversion_style(text_conversion_style,
	    text_sequence);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)16L);
    gensymed_symbol_1 = transcoder;
    temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(transcoder,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = transcoder;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = text_sequence;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(temp);
}

/* EXPORT-TEXT-STRING */
Object export_text_string varargs_1(int, n)
{
    Object text_string;
    Object purpose, start_qm, end_qm, style;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,301);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    purpose = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    start_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_qm = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    style = getfq_function_no_default(INLINE_SYMBOL_PLIST(purpose),
	    Qtext_conversion_style_for_purpose);
    if (style);
    else
	style = Default_text_conversion_style;
    return export_text_string_per_text_conversion_style(4,text_string,
	    style,start_qm,end_qm);
}

/* UNICODE-KNOWN-ISO-LATIN1-TO-GENSYM-STRING */
Object unicode_known_iso_latin1_to_gensym_string(text_string)
    Object text_string;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object character_1, temp, schar_arg_2, schar_new_value, temp_1;
    SI_Long i, ab_loop_bind_, gensymed_symbol, simple_or_wide_character, thing;
    Declare_special(4);

    x_note_fn_call(28,302);
    current_gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(text_string_length(text_string));
	    character_1 = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    character_1 = FIX(UBYTE_16_ISAREF_1(text_string,i));
	    gensymed_symbol = (SI_Long)255L & IFIX(character_1);
	    simple_or_wide_character = gensymed_symbol;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = simple_or_wide_character;
		twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    temp_1 = copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

Object Utf_7_modified_base64_characters = UNBOUND;

/* UTF-7-BASE64-DIGIT-CHAR-P */
Object utf_7_base64_digit_char_p(wide_character)
    Object wide_character;
{
    Object unicode, temp;

    x_note_fn_call(28,303);
    unicode = wide_character;
    temp = utf_7_base64_digit_char_code_p(unicode);
    return VALUES_1(temp);
}

/* UTF-7-BASE64-DIGIT-CHAR-CODE-P */
Object utf_7_base64_digit_char_code_p(unicode)
    Object unicode;
{
    Object temp;

    x_note_fn_call(28,304);
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

Object Utf_7_ultraconservative_p = UNBOUND;

Object Utf_7_delimit_encoded_sequences_p = UNBOUND;

Object The_type_description_of_utf_7_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_utf_7_transcoders, Qchain_of_available_utf_7_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Utf_7_transcoder_count, Qutf_7_transcoder_count);

Object Chain_of_available_utf_7_transcoders_vector = UNBOUND;

/* UTF-7-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object utf_7_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,305);
    temp = Utf_7_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UTF-7-TRANSCODER-COUNT */
Object outstanding_utf_7_transcoder_count()
{
    Object def_structure_utf_7_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,306);
    gensymed_symbol = IFIX(Utf_7_transcoder_count);
    def_structure_utf_7_transcoder_variable = 
	    Chain_of_available_utf_7_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_utf_7_transcoder_variable))
	goto end_loop;
    def_structure_utf_7_transcoder_variable = 
	    ISVREF(def_structure_utf_7_transcoder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UTF-7-TRANSCODER-1 */
Object reclaim_utf_7_transcoder_1(utf_7_transcoder)
    Object utf_7_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,307);
    inline_note_reclaim_cons(utf_7_transcoder,Nil);
    temp = ISVREF(Chain_of_available_utf_7_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(utf_7_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_utf_7_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = utf_7_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UTF-7-TRANSCODER */
Object reclaim_structure_for_utf_7_transcoder(utf_7_transcoder)
    Object utf_7_transcoder;
{
    x_note_fn_call(28,308);
    return reclaim_utf_7_transcoder_1(utf_7_transcoder);
}

static Object Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct;  /* g2-defstruct-structure-name::utf-7-transcoder-g2-struct */

/* MAKE-PERMANENT-UTF-7-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_utf_7_transcoder_structure_internal()
{
    Object def_structure_utf_7_transcoder_variable;
    Object defstruct_g2_utf_7_transcoder_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,309);
    def_structure_utf_7_transcoder_variable = Nil;
    atomic_incff_symval(Qutf_7_transcoder_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_utf_7_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_utf_7_transcoder_variable,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_utf_7_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_utf_7_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_utf_7_transcoder_variable);
}

/* MAKE-UTF-7-TRANSCODER-1 */
Object make_utf_7_transcoder_1()
{
    Object def_structure_utf_7_transcoder_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,310);
    def_structure_utf_7_transcoder_variable = 
	    ISVREF(Chain_of_available_utf_7_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_utf_7_transcoder_variable) {
	svref_arg_1 = Chain_of_available_utf_7_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_utf_7_transcoder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_utf_7_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct;
    }
    else
	def_structure_utf_7_transcoder_variable = 
		make_permanent_utf_7_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_utf_7_transcoder_variable,Nil);
    ISVREF(def_structure_utf_7_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_utf_7_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_utf_7_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_utf_7_transcoder_variable);
}

/* CREATE-TRANSCODER-FOR-UNICODE-UTF-7 */
Object create_transcoder_for_unicode_utf_7()
{
    x_note_fn_call(28,311);
    return make_utf_7_transcoder_1();
}

/* TRANSCODE-CHARACTER-FOR-UTF-7-TRANSCODER */
Object transcode_character_for_utf_7_transcoder(utf_7_transcoder)
    Object utf_7_transcoder;
{
    Object transcoder;
    SI_Long character_1, unicode;

    x_note_fn_call(28,312);
    transcoder = utf_7_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
	    return transcode_utf_7_base64(transcoder);
	else {
	    unicode = character_1;
	    if (unicode < (SI_Long)127L && (unicode < (SI_Long)32L ? 
		    unicode == (SI_Long)9L || unicode == (SI_Long)13L || 
		    unicode == (SI_Long)10L : Utf_7_ultraconservative_p ? 
		    (SI_Long)65L <= unicode && unicode <= (SI_Long)90L || 
		    (SI_Long)97L <= unicode && unicode <= (SI_Long)122L || 
		    (SI_Long)39L <= unicode && unicode <= (SI_Long)41L || 
		    (SI_Long)44L <= unicode && unicode <= (SI_Long)47L || 
		    unicode == (SI_Long)32L || unicode == (SI_Long)58L || 
		    unicode == (SI_Long)63L :  !(unicode == (SI_Long)61L) 
		    &&  !(unicode == (SI_Long)43L)))
		return VALUES_1(FIX(character_1));
	    else
		return transcode_unhandled_character(FIX(character_1),
			transcoder);
	}
    }
    else
	return transcode_unhandled_character(FIX(character_1),transcoder);
}

/* TRANSCODE-UTF-7-BASE64 */
Object transcode_utf_7_base64(transcoder)
    Object transcoder;
{
    Object buffered_sextets_in_reverse_order, first_time_qm;
    Object post_base64_character_qm, character_1, sextet, temp;
    Object gensym_pop_store, cons_1, next_cons, svref_arg_2;

    x_note_fn_call(28,313);
    buffered_sextets_in_reverse_order = Qnil;
    first_time_qm = T;
    post_base64_character_qm = Nil;
    character_1 = Nil;
    sextet = Nil;
  next_loop:
    character_1 = get_transcoder_character_if_any(transcoder);
    if ( !TRUEP(character_1))
	goto end_loop;
    sextet = utf_7_base64_digit_char_p(character_1);
    if (sextet)
	buffered_sextets_in_reverse_order = gensym_cons_1(sextet,
		buffered_sextets_in_reverse_order);
    else if (first_time_qm) {
	if (IFIX(character_1) == (SI_Long)45L)
	    return VALUES_1(FIX((SI_Long)43L));
	else
	    return transcode_unhandled_character(character_1,transcoder);
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
    if (emit_buffered_utf_7_base64_sextets_as_unicodes(transcoder,
	    buffered_sextets_in_reverse_order))
	return transcode_unhandled_character(character_1,transcoder);
    else {
	if (post_base64_character_qm) {
	    temp = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    gensym_cons_1(post_base64_character_qm,Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = temp;
	}
	gensym_pop_store = Nil;
	cons_1 = ISVREF(transcoder,(SI_Long)5L);
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	SVREF(transcoder,FIX((SI_Long)5L)) = next_cons;
	return VALUES_1(gensym_pop_store);
    }
    return VALUES_1(Qnil);
}

/* EMIT-BUFFERED-UNICODES-AS-UTF-7-BASE64-TO-TRANSCODER */
Object emit_buffered_unicodes_as_utf_7_base64_to_transcoder(buffered_unicodes_in_reverse_order,
	    transcoder)
    Object buffered_unicodes_in_reverse_order, transcoder;
{
    Object buffered_unicodes, unicode, ab_loop_list_, octets, ab_loopvar_;
    Object ab_loopvar__1;
    SI_Long gensymed_symbol;

    x_note_fn_call(28,314);
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
    ab_loopvar__1 = gensym_cons_1(FIX(IFIX(unicode) >>  -  - (SI_Long)8L),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	octets = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    gensymed_symbol = IFIX(unicode) & (SI_Long)255L;
    ab_loopvar__1 = gensym_cons_1(FIX(gensymed_symbol),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	octets = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(buffered_unicodes);
    emit_buffered_octets_as_utf_7_base64_to_transcoder(octets,transcoder);
    return VALUES_1(Qnil);
}

/* EMIT-BUFFERED-OCTETS-AS-UTF-7-BASE64-TO-TRANSCODER */
Object emit_buffered_octets_as_utf_7_base64_to_transcoder(buffered_octets,
	    transcoder)
    Object buffered_octets, transcoder;
{
    Object octet_1, octet_2_qm, octet_3_qm, ab_loop_list_, temp, sextet_3_qm;
    Object sextet_4_qm, svref_new_value;
    SI_Long sextet_1, gensymed_symbol, gensymed_symbol_1, sextet_2;
    SI_Long character_1;

    x_note_fn_call(28,315);
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
    character_1 = UBYTE_16_ISAREF_1(Utf_7_modified_base64_characters,sextet_1);
    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
	    gensym_cons_1(FIX(character_1),Nil));
    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    character_1 = UBYTE_16_ISAREF_1(Utf_7_modified_base64_characters,sextet_2);
    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
	    gensym_cons_1(FIX(character_1),Nil));
    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    if (sextet_3_qm) {
	character_1 = UBYTE_16_ISAREF_1(Utf_7_modified_base64_characters,
		IFIX(sextet_3_qm));
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		gensym_cons_1(FIX(character_1),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    }
    if (sextet_4_qm) {
	character_1 = UBYTE_16_ISAREF_1(Utf_7_modified_base64_characters,
		IFIX(sextet_4_qm));
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		gensym_cons_1(FIX(character_1),Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    }
    ab_loop_list_ = CDDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(buffered_octets);
}

static Object Qillegal_utf_7_base64_character;  /* illegal-utf-7-base64-character */

/* EMIT-BUFFERED-UTF-7-BASE64-SEXTETS-AS-UNICODES */
Object emit_buffered_utf_7_base64_sextets_as_unicodes(transcoder,
	    buffered_sextets_in_reverse_order)
    Object transcoder, buffered_sextets_in_reverse_order;
{
    Object buffered_sextets, octet_1, octet_2_qm, octet_3_qm, sextet_1;
    Object sextet_2_qm, sextet_3_qm, sextet_4_qm, ab_loop_list_;
    Object buffered_octets, ab_loopvar_, ab_loopvar__1, temp;
    SI_Long j, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(28,316);
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
	reclaim_gensym_list_1(buffered_sextets_in_reverse_order);
	return VALUES_1(Qillegal_utf_7_base64_character);
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
    ab_loopvar__1 = gensym_cons_1(octet_1,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	buffered_octets = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    if (octet_2_qm) {
	ab_loopvar__1 = gensym_cons_1(octet_2_qm,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    buffered_octets = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    if (octet_3_qm) {
	ab_loopvar__1 = gensym_cons_1(octet_3_qm,Nil);
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
    reclaim_gensym_list_1(buffered_sextets);
    return emit_buffered_octets_as_unicodes(transcoder,buffered_octets);
    return VALUES_1(Qnil);
}

static Object Qill_formed_octet_stream_odd_number;  /* ill-formed-octet-stream-odd-number */

/* EMIT-BUFFERED-OCTETS-AS-UNICODES */
Object emit_buffered_octets_as_unicodes(transcoder,buffered_octets)
    Object transcoder, buffered_octets;
{
    Object octet_1, octet_2_qm, ab_loop_list_, temp, svref_new_value;
    SI_Long j, character_1;

    x_note_fn_call(28,317);
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
	reclaim_gensym_list_1(buffered_octets);
	return VALUES_1(Qill_formed_octet_stream_odd_number);
    }
    if (octet_2_qm) {
	character_1 = (IFIX(octet_1) << (SI_Long)8L) + IFIX(octet_2_qm);
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		gensym_cons_1(FIX(character_1),Nil));
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
    reclaim_gensym_list_1(buffered_octets);
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* EXPORT-CHARACTER-FOR-UTF-7-TRANSCODER */
Object export_character_for_utf_7_transcoder(utf_7_transcoder)
    Object utf_7_transcoder;
{
    Object transcoder;
    SI_Long character_1, unicode;

    x_note_fn_call(28,318);
    transcoder = utf_7_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
    unicode = character_1;
    if (unicode < (SI_Long)127L && (unicode < (SI_Long)32L ? unicode == 
	    (SI_Long)9L || unicode == (SI_Long)13L || unicode == 
	    (SI_Long)10L : Utf_7_ultraconservative_p ? (SI_Long)65L <= 
	    unicode && unicode <= (SI_Long)90L || (SI_Long)97L <= unicode 
	    && unicode <= (SI_Long)122L || (SI_Long)39L <= unicode && 
	    unicode <= (SI_Long)41L || (SI_Long)44L <= unicode && unicode 
	    <= (SI_Long)47L || unicode == (SI_Long)32L || unicode == 
	    (SI_Long)58L || unicode == (SI_Long)63L :  !(unicode == 
	    (SI_Long)61L) &&  !(unicode == (SI_Long)43L)))
	return VALUES_1(FIX(character_1));
    else
	return export_utf_7_base64(FIX(character_1),transcoder);
}

/* EXPORT-UTF-7-BASE64 */
Object export_utf_7_base64(first_non_direct_character_init,transcoder)
    Object first_non_direct_character_init, transcoder;
{
    Object reversed_buffered_unicodes, character_qm, unicode, svref_new_value;
    Object temp;
    SI_Long first_non_direct_character;

    x_note_fn_call(28,319);
    first_non_direct_character = IFIX(first_non_direct_character_init);
    reversed_buffered_unicodes = 
	    gensym_cons_1(FIX(first_non_direct_character),Nil);
    character_qm = Nil;
  next_loop:
    character_qm = get_transcoder_character_if_any(transcoder);
    if ( !TRUEP(character_qm))
	goto end_loop;
    unicode = character_qm;
    if (IFIX(unicode) < (SI_Long)127L && (IFIX(unicode) < (SI_Long)32L ? 
	    IFIX(unicode) == (SI_Long)9L || IFIX(unicode) == (SI_Long)13L 
	    || IFIX(unicode) == (SI_Long)10L : Utf_7_ultraconservative_p ? 
	    (SI_Long)65L <= IFIX(unicode) && IFIX(unicode) <= (SI_Long)90L 
	    || (SI_Long)97L <= IFIX(unicode) && IFIX(unicode) <= 
	    (SI_Long)122L || (SI_Long)39L <= IFIX(unicode) && 
	    IFIX(unicode) <= (SI_Long)41L || (SI_Long)44L <= IFIX(unicode) 
	    && IFIX(unicode) <= (SI_Long)47L || IFIX(unicode) == 
	    (SI_Long)32L || IFIX(unicode) == (SI_Long)58L || IFIX(unicode) 
	    == (SI_Long)63L :  !(IFIX(unicode) == (SI_Long)61L) &&  
	    !(IFIX(unicode) == (SI_Long)43L)))
	goto end_loop;
    reversed_buffered_unicodes = gensym_cons_1(character_qm,
	    reversed_buffered_unicodes);
    goto next_loop;
  end_loop:
    emit_buffered_unicodes_as_utf_7_base64_to_transcoder(reversed_buffered_unicodes,
	    transcoder);
    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
	    gensym_cons_1(FIX((SI_Long)45L),Nil));
    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    if (character_qm) {
	svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		gensym_cons_1(character_qm,Nil));
	SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
    }
    temp = FIX((SI_Long)43L);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ucs_4_to_utf_8_1st_octet_table, Qucs_4_to_utf_8_1st_octet_table);

/* TWRITE-UTF-8-OCTETS */
Object twrite_utf_8_octets(unicode,n_octets,binary,use_bits,bits_free)
    Object unicode, n_octets, binary, use_bits, bits_free;
{
    Object octet, simple_or_wide_character, thing, temp, schar_arg_2;
    Object schar_new_value;
    SI_Long binary_2, use_bits_2, bits_free_2, octet_index;

    x_note_fn_call(28,320);
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
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = simple_or_wide_character;
	twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : thing);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		thing);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
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
Object twrite_unicode_as_utf_8(unicode)
    Object unicode;
{
    Object simple_or_wide_character, thing, temp, schar_arg_2, schar_new_value;

    x_note_fn_call(28,321);
    if (IFIX(unicode) <= (SI_Long)127L) {
	simple_or_wide_character = unicode;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = simple_or_wide_character;
	    return twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
    else if (IFIX(unicode) <= (SI_Long)2047L)
	return twrite_utf_8_octets(unicode,FIX((SI_Long)2L),
		FIX((SI_Long)192L),FIX((SI_Long)31L),FIX((SI_Long)5L));
    else if (IFIX(unicode) <= (SI_Long)65535L)
	return twrite_utf_8_octets(unicode,FIX((SI_Long)3L),
		FIX((SI_Long)224L),FIX((SI_Long)15L),FIX((SI_Long)4L));
    else
	return VALUES_1(Qnil);
}

/* TRANSFORM-UTF-8-TO-UCS-4 */
Object transform_utf_8_to_ucs_4 varargs_1(int, n)
{
    Object z;
    Object y, x, w, v, u_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,322);
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
Object twrite_utf_8_from_text_string(text_string)
    Object text_string;
{
    Object wide_character, temp, unicode, simple_or_wide_character, thing;
    Object temp_1, schar_arg_2, schar_new_value;
    SI_Long length_1, i, wide_string_index;

    x_note_fn_call(28,323);
    length_1 = IFIX(text_string_length(text_string));
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
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = simple_or_wide_character;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    else if (IFIX(unicode) <= (SI_Long)2047L)
	twrite_utf_8_octets(unicode,FIX((SI_Long)2L),FIX((SI_Long)192L),
		FIX((SI_Long)31L),FIX((SI_Long)5L));
    else if (IFIX(unicode) <= (SI_Long)65535L)
	twrite_utf_8_octets(unicode,FIX((SI_Long)3L),FIX((SI_Long)224L),
		FIX((SI_Long)15L),FIX((SI_Long)4L));
    wide_string_index = wide_string_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* UNICODE-TO-UTF-8-WIDE-STRING */
Object unicode_to_utf_8_wide_string(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(28,324);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      twrite_utf_8_from_text_string(text_string);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* UNICODE-TO-UTF-8-GENSYM-STRING */
Object unicode_to_utf_8_gensym_string(text_string)
    Object text_string;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(28,325);
    current_gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    twrite_utf_8_from_text_string(text_string);
	    result = copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GET-UTF-8-AS-UNICODE-FROM-TEXT-SEQUENCE */
Object get_utf_8_as_unicode_from_text_sequence(text_sequence)
    Object text_sequence;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long z, y, x, w, v, u_1, octet_count;
    char temp_1;

    x_note_fn_call(28,326);
    gensymed_symbol = ISVREF(text_sequence,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
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
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
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
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
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
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
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
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
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
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)11L);
	    gensymed_symbol_1 = text_sequence;
	    u_1 = IFIX(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
	}
	else {
	    temp = Nil;
	    goto end_exhausted;
	}
    }
    temp = transform_utf_8_to_ucs_4(6,FIX(z),FIX(y),FIX(x),FIX(w),FIX(v),
	    FIX(u_1));
  end_exhausted:
    return VALUES_1(temp);
}

Object The_type_description_of_utf_8_transcoder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_utf_8_transcoders, Qchain_of_available_utf_8_transcoders);

DEFINE_VARIABLE_WITH_SYMBOL(Utf_8_transcoder_count, Qutf_8_transcoder_count);

Object Chain_of_available_utf_8_transcoders_vector = UNBOUND;

/* UTF-8-TRANSCODER-STRUCTURE-MEMORY-USAGE */
Object utf_8_transcoder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(28,327);
    temp = Utf_8_transcoder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UTF-8-TRANSCODER-COUNT */
Object outstanding_utf_8_transcoder_count()
{
    Object def_structure_utf_8_transcoder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(28,328);
    gensymed_symbol = IFIX(Utf_8_transcoder_count);
    def_structure_utf_8_transcoder_variable = 
	    Chain_of_available_utf_8_transcoders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_utf_8_transcoder_variable))
	goto end_loop;
    def_structure_utf_8_transcoder_variable = 
	    ISVREF(def_structure_utf_8_transcoder_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UTF-8-TRANSCODER-1 */
Object reclaim_utf_8_transcoder_1(utf_8_transcoder)
    Object utf_8_transcoder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(28,329);
    inline_note_reclaim_cons(utf_8_transcoder,Nil);
    temp = ISVREF(Chain_of_available_utf_8_transcoders_vector,
	    IFIX(Current_thread_index));
    SVREF(utf_8_transcoder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_utf_8_transcoders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = utf_8_transcoder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UTF-8-TRANSCODER */
Object reclaim_structure_for_utf_8_transcoder(utf_8_transcoder)
    Object utf_8_transcoder;
{
    x_note_fn_call(28,330);
    return reclaim_utf_8_transcoder_1(utf_8_transcoder);
}

static Object Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct;  /* g2-defstruct-structure-name::utf-8-transcoder-g2-struct */

/* MAKE-PERMANENT-UTF-8-TRANSCODER-STRUCTURE-INTERNAL */
Object make_permanent_utf_8_transcoder_structure_internal()
{
    Object def_structure_utf_8_transcoder_variable;
    Object defstruct_g2_utf_8_transcoder_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,331);
    def_structure_utf_8_transcoder_variable = Nil;
    atomic_incff_symval(Qutf_8_transcoder_count,FIX((SI_Long)1L));
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
	temp = ISVREF(Chain_of_available_utf_8_transcoders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_utf_8_transcoder_variable,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_utf_8_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_utf_8_transcoder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_utf_8_transcoder_variable);
}

/* MAKE-UTF-8-TRANSCODER-1 */
Object make_utf_8_transcoder_1()
{
    Object def_structure_utf_8_transcoder_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(28,332);
    def_structure_utf_8_transcoder_variable = 
	    ISVREF(Chain_of_available_utf_8_transcoders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_utf_8_transcoder_variable) {
	svref_arg_1 = Chain_of_available_utf_8_transcoders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_utf_8_transcoder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_utf_8_transcoder_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct;
    }
    else
	def_structure_utf_8_transcoder_variable = 
		make_permanent_utf_8_transcoder_structure_internal();
    inline_note_allocate_cons(def_structure_utf_8_transcoder_variable,Nil);
    ISVREF(def_structure_utf_8_transcoder_variable,(SI_Long)2L) = 
	    FIX((SI_Long)65535L);
    ISVREF(def_structure_utf_8_transcoder_variable,(SI_Long)3L) = 
	    FIX((SI_Long)65535L);
    SVREF(def_structure_utf_8_transcoder_variable,FIX((SI_Long)5L)) = Qnil;
    return VALUES_1(def_structure_utf_8_transcoder_variable);
}

/* CREATE-TRANSCODER-FOR-UNICODE-UTF-8 */
Object create_transcoder_for_unicode_utf_8()
{
    x_note_fn_call(28,333);
    return make_utf_8_transcoder_1();
}

/* TRANSCODE-CHARACTER-FOR-UTF-8-TRANSCODER */
Object transcode_character_for_utf_8_transcoder(utf_8_transcoder)
    Object utf_8_transcoder;
{
    Object transcoder, temp, c;
    SI_Long character_1, z, y, x, octet_count;

    x_note_fn_call(28,334);
    transcoder = utf_8_transcoder;
    character_1 = IFIX(get_transcoder_character(transcoder));
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
	    return transcode_unhandled_character(FIX(character_1),transcoder);
	else {
	    if (octet_count > (SI_Long)1L) {
		c = get_transcoder_character_if_any(transcoder);
		if ( !TRUEP(c))
		    y = (SI_Long)-1L;
		else {
		    y = IFIX(c);
		    if (octet_count > (SI_Long)2L) {
			c = get_transcoder_character_if_any(transcoder);
			if ( !TRUEP(c))
			    x = (SI_Long)-1L;
			else
			    x = IFIX(c);
		    }
		}
	    }
	    if (y < (SI_Long)0L || x < (SI_Long)0L)
		return transcode_unhandled_character(FIX(character_1),
			transcoder);
	    else
		return transform_utf_8_to_ucs_4(3,FIX(z),FIX(y),FIX(x));
	}
    }
    else
	return transcode_unhandled_character(FIX(character_1),transcoder);
}

/* EXPORT-CHARACTER-FOR-UTF-8-TRANSCODER */
Object export_character_for_utf_8_transcoder(utf_8_transcoder)
    Object utf_8_transcoder;
{
    Object transcoder, character_1, temp, svref_new_value;
    SI_Long character_2;

    x_note_fn_call(28,335);
    transcoder = utf_8_transcoder;
    character_1 = get_transcoder_character(transcoder);
    if (IFIX(character_1) == (SI_Long)8232L || IFIX(character_1) == 
	    (SI_Long)8233L) {
	temp = ISVREF(ISVREF(transcoder,(SI_Long)4L),(SI_Long)4L);
	if (EQ(temp,Qper_platform)) {
	    if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,
		    Qvms) || EQ(G2_operating_system,Qwin32)) {
		svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
			gensym_cons_1(FIX((SI_Long)10L),Nil));
		SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
		character_2 = (SI_Long)13L;
	    }
	    else if (EQ(G2_operating_system,Qunix))
		character_2 = (SI_Long)10L;
	    else
		character_2 = (SI_Long)10L;
	}
	else if (EQ(temp,Qcr))
	    character_2 = (SI_Long)13L;
	else if (EQ(temp,Qlf))
	    character_2 = (SI_Long)10L;
	else if (EQ(temp,Qcrlf)) {
	    svref_new_value = nconc2(ISVREF(transcoder,(SI_Long)5L),
		    gensym_cons_1(FIX((SI_Long)10L),Nil));
	    SVREF(transcoder,FIX((SI_Long)5L)) = svref_new_value;
	    character_2 = (SI_Long)13L;
	}
	else if (EQ(temp,Qunicode_line_separator))
	    character_2 = (SI_Long)8232L;
	else if (EQ(temp,Qunicode_paragraph_separator))
	    character_2 = (SI_Long)8233L;
	else
	    character_2 = IFIX(character_1);
    }
    else
	character_2 = IFIX(character_1);
    if (character_2 <= (SI_Long)127L)
	return VALUES_1(FIX(character_2));
    else if (character_2 <= (SI_Long)2047L)
	return encode_utf_8_octets_for_transcoder(transcoder,
		FIX(character_2),FIX((SI_Long)2L),FIX((SI_Long)192L),
		FIX((SI_Long)31L),FIX((SI_Long)5L));
    else if (character_2 <= (SI_Long)65535L)
	return encode_utf_8_octets_for_transcoder(transcoder,
		FIX(character_2),FIX((SI_Long)3L),FIX((SI_Long)224L),
		FIX((SI_Long)15L),FIX((SI_Long)4L));
    else
	return VALUES_1(Qnil);
}

/* ENCODE-UTF-8-OCTETS-FOR-TRANSCODER */
Object encode_utf_8_octets_for_transcoder(transcoder,character_1,n_octets,
	    binary,use_bits,bits_free)
    Object transcoder, character_1, n_octets, binary, use_bits, bits_free;
{
    Object octet, octet_character, svref_new_value;
    SI_Long binary_2, use_bits_2, bits_free_2, octet_index;

    x_note_fn_call(28,336);
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
	    gensym_cons_1(octet_character,Nil));
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
Object gensym_string_to_wide_string(gensym_string)
    Object gensym_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, character_or_character_code, escape_character_qm;
    Object gensymed_symbol, current_extended_utf_g_low_half_character_qm, row;
    Object simple_or_wide_character, thing, temp_4, schar_arg_2;
    Object schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, end_1, i;
    SI_Long gensym_character_code, ascii_code, temp_2, unicode_full_row;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char simple_qm, gensym_string_is_simple_qm;
    char temp_1, character_1;
    char gensymed_symbol_1, temp_3;
    Declare_special(7);

    x_note_fn_call(28,337);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      simple_qm =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
	      temp = Nil;
	      if (temp);
	      else
		  temp = simple_qm ? 
			  SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string) : 
			  length(gensym_string);
	      end_1 = IFIX(temp);
	      i = (SI_Long)0L;
	      character_or_character_code = Nil;
	      escape_character_qm = Nil;
	      gensym_character_code = (SI_Long)0L;
	    next_loop:
	      if ( !(i < end_1))
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
			      ISVREF(Reverse_iso_latin1_special_character_code_map,
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
				  temp = Gensym_code_for_capital_ligature_oe;
				  break;
				case 119:
				  temp = Gensym_code_for_small_ligature_oe;
				  break;
				case 42:
				  temp = Gensym_code_for_bullet;
				  break;
				case 38:
				  temp = 
					  Gensym_code_for_small_letter_f_with_hook;
				  break;
				case 58:
				  temp = Gensym_code_for_trade_mark_sign;
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
			  !TRUEP(Gensym_esc_for_linebreak_qm) ? 
			  CHAR_EQ(character_or_character_code,
			  Gensym_char_or_code_for_linebreak) : 
			  EQL(character_or_character_code,
			  Gensym_char_or_code_for_linebreak) && 
			  EQL(escape_character_qm,Gensym_esc_for_linebreak_qm))
		      gensym_character_code = IFIX(Gensym_code_for_linebreak);
		  else if ( !TRUEP(escape_character_qm) &&  
			  !TRUEP(Gensym_esc_for_paragraph_break_qm) ? 
			  CHAR_EQ(character_or_character_code,
			  Gensym_char_or_code_for_paragraph_break) : 
			  EQL(character_or_character_code,
			  Gensym_char_or_code_for_paragraph_break) && 
			  EQL(escape_character_qm,
			  Gensym_esc_for_paragraph_break_qm))
		      gensym_character_code = 
			      IFIX(Gensym_code_for_paragraph_break);
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
		  PUSH_SPECIAL_WITH_SYMBOL(Current_extended_utf_g_low_half_character_qm,Qcurrent_extended_utf_g_low_half_character_qm,current_extended_utf_g_low_half_character_qm,
			  1);
		    if (i < end_1) {
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
					ISVREF(Reverse_iso_latin1_special_character_code_map,
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
						    Gensym_code_for_capital_ligature_oe;
					    break;
					  case 119:
					    temp = 
						    Gensym_code_for_small_ligature_oe;
					    break;
					  case 42:
					    temp = Gensym_code_for_bullet;
					    break;
					  case 38:
					    temp = 
						    Gensym_code_for_small_letter_f_with_hook;
					    break;
					  case 58:
					    temp = 
						    Gensym_code_for_trade_mark_sign;
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
				    !TRUEP(Gensym_esc_for_linebreak_qm) ? 
				    CHAR_EQ(character_or_character_code,
				    Gensym_char_or_code_for_linebreak) : 
				    EQL(character_or_character_code,
				    Gensym_char_or_code_for_linebreak) && 
				    EQL(escape_character_qm,
				    Gensym_esc_for_linebreak_qm))
				gensym_character_code = 
					IFIX(Gensym_code_for_linebreak);
			    else if ( !TRUEP(escape_character_qm) &&  
				    !TRUEP(Gensym_esc_for_paragraph_break_qm) 
				    ? CHAR_EQ(character_or_character_code,
				    Gensym_char_or_code_for_paragraph_break) 
				    : EQL(character_or_character_code,
				    Gensym_char_or_code_for_paragraph_break) 
				    && EQL(escape_character_qm,
				    Gensym_esc_for_paragraph_break_qm))
				gensym_character_code = 
					IFIX(Gensym_code_for_paragraph_break);
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
				    TRUEP(ISVREF(Iso_latin1_special_character_code_map,
				    gensym_character_code)) : TRUEP(Nil);
			    if (temp_3);
			    else if (gensym_character_code == 
				    IFIX(Gensym_code_for_capital_ligature_oe))
				temp_3 = 'W';
			    else if (gensym_character_code == 
				    IFIX(Gensym_code_for_small_ligature_oe))
				temp_3 = 'w';
			    else if (gensym_character_code == 
				    IFIX(Gensym_code_for_bullet))
				temp_3 = '*';
			    else if (gensym_character_code == 
				    IFIX(Gensym_code_for_small_letter_f_with_hook))
				temp_3 = '&';
			    else if (gensym_character_code == 
				    IFIX(Gensym_code_for_trade_mark_sign))
				temp_3 = ':';
			    else
				temp_3 = TRUEP(Qnil);
			    if (temp_3) {
				row = FIX(gensym_character_code >>  -  - 
					(SI_Long)8L);
				PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				  unicode_full_row = 
					  UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
					  IFIX(Row));
				  if ( !(unicode_full_row == 
					  IFIX(Invalid_unicode_full_row))) {
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
				POP_SPECIAL();
			    }
			    else if ((SI_Long)8192L <= 
				    gensym_character_code && 
				    gensym_character_code <= (SI_Long)8447L) {
				row = FIX(gensym_character_code >>  -  - 
					(SI_Long)8L);
				PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				  unicode_full_row = 
					  UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
					  IFIX(Row));
				  if ( !(unicode_full_row == 
					  IFIX(Invalid_unicode_full_row))) {
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
				POP_SPECIAL();
			    }
			    else {
				simple_or_wide_character = 
					map_gensym_han_character_code_to_unicode(FIX(gensym_character_code));
				if (simple_or_wide_character);
				else {
				    row = FIX(gensym_character_code >>  -  
					    - (SI_Long)8L);
				    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				      unicode_full_row = 
					      UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
					      IFIX(Row));
				      if ( !(unicode_full_row == 
					      IFIX(Invalid_unicode_full_row))) 
						  {
					  gensymed_symbol_2 = 
						  unicode_full_row << 
						  (SI_Long)8L;
					  gensymed_symbol_3 = 
						  (SI_Long)255L & 
						  gensym_character_code;
					  simple_or_wide_character = 
						  FIX(gensymed_symbol_2 + 
						  gensymed_symbol_3);
				      }
				      else
					  simple_or_wide_character = Nil;
				    POP_SPECIAL();
				    if (simple_or_wide_character);
				    else if (Current_extended_utf_g_low_half_character_qm)
					simple_or_wide_character = 
						map_extended_utf_g_characters_to_unicode(Current_extended_utf_g_low_half_character_qm,
						FIX(gensym_character_code));
				    else
					simple_or_wide_character = 
						FIX((SI_Long)65535L);
				}
			    }
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = simple_or_wide_character;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_4 = Current_gensym_string;
				schar_arg_2 = 
					Fill_pointer_for_current_gensym_string;
				thing = simple_or_wide_character;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_4,schar_arg_2,schar_new_value);
				temp_4 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_4;
			    }
			}
		    }
		  POP_SPECIAL();
	      }
	      else {
		  temp_3 = gensym_character_code < (SI_Long)256L ? 
			  TRUEP(ISVREF(Iso_latin1_special_character_code_map,
			  gensym_character_code)) : TRUEP(Nil);
		  if (temp_3);
		  else if (gensym_character_code == 
			  IFIX(Gensym_code_for_capital_ligature_oe))
		      temp_3 = 'W';
		  else if (gensym_character_code == 
			  IFIX(Gensym_code_for_small_ligature_oe))
		      temp_3 = 'w';
		  else if (gensym_character_code == 
			  IFIX(Gensym_code_for_bullet))
		      temp_3 = '*';
		  else if (gensym_character_code == 
			  IFIX(Gensym_code_for_small_letter_f_with_hook))
		      temp_3 = '&';
		  else if (gensym_character_code == 
			  IFIX(Gensym_code_for_trade_mark_sign))
		      temp_3 = ':';
		  else
		      temp_3 = TRUEP(Qnil);
		  if (temp_3) {
		      row = FIX(gensym_character_code >>  -  - (SI_Long)8L);
		      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			unicode_full_row = 
				UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
				IFIX(Row));
			if ( !(unicode_full_row == 
				IFIX(Invalid_unicode_full_row))) {
			    gensymed_symbol_2 = unicode_full_row << 
				    (SI_Long)8L;
			    gensymed_symbol_3 = (SI_Long)255L & 
				    gensym_character_code;
			    simple_or_wide_character = 
				    FIX(gensymed_symbol_2 + gensymed_symbol_3);
			}
			else
			    simple_or_wide_character = Nil;
		      POP_SPECIAL();
		  }
		  else if ((SI_Long)8192L <= gensym_character_code && 
			  gensym_character_code <= (SI_Long)8447L) {
		      row = FIX(gensym_character_code >>  -  - (SI_Long)8L);
		      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			unicode_full_row = 
				UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
				IFIX(Row));
			if ( !(unicode_full_row == 
				IFIX(Invalid_unicode_full_row))) {
			    gensymed_symbol_2 = unicode_full_row << 
				    (SI_Long)8L;
			    gensymed_symbol_3 = (SI_Long)255L & 
				    gensym_character_code;
			    simple_or_wide_character = 
				    FIX(gensymed_symbol_2 + gensymed_symbol_3);
			}
			else
			    simple_or_wide_character = Nil;
		      POP_SPECIAL();
		  }
		  else {
		      simple_or_wide_character = 
			      map_gensym_han_character_code_to_unicode(FIX(gensym_character_code));
		      if (simple_or_wide_character);
		      else {
			  row = FIX(gensym_character_code >>  -  - 
				  (SI_Long)8L);
			  PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			    unicode_full_row = 
				    UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
				    IFIX(Row));
			    if ( !(unicode_full_row == 
				    IFIX(Invalid_unicode_full_row))) {
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
			  POP_SPECIAL();
			  if (simple_or_wide_character);
			  else if (Current_extended_utf_g_low_half_character_qm)
			      simple_or_wide_character = 
				      map_extended_utf_g_characters_to_unicode(Current_extended_utf_g_low_half_character_qm,
				      FIX(gensym_character_code));
			  else
			      simple_or_wide_character = FIX((SI_Long)65535L);
		      }
		  }
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = simple_or_wide_character;
		      twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp_4 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_4,schar_arg_2,schar_new_value);
		      temp_4 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_4;
		  }
	      }
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* TWRITE-UTF-G-FROM-TEXT-STRING */
Object twrite_utf_g_from_text_string(text_string)
    Object text_string;
{
    Object wide_character, extended_code_qm, temp, unicode, code;
    Object extended_code, unicode_1, code_1, row, gensym_character_code_qm;
    Object char_1, character_or_character_code, escape_character_qm, thing;
    Object temp_2, schar_arg_2, schar_new_value, kanji_code, octet_1_qm;
    Object quotient, remainder_1, simple_or_wide_character;
    Object simple_gensym_character_code_1;
    SI_Long length_1, i, gensym_character_code, wide_string_index;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1;
    SI_Long simple_gensym_character_code, octet_2, octet_3, thing_1;
    SI_Long simple_or_wide_character_1;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(28,338);
    length_1 = IFIX(text_string_length(text_string));
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
	row = FIX(IFIX(unicode_1) >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
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
	    code = map_unicode_to_gensym_han_character_code(unicode_1);
	    temp = code;
	    if (temp);
	    else {
		row = FIX(IFIX(unicode_1) >>  -  - (SI_Long)8L);
		PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		  gensym_full_row = 
			  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
			  IFIX(Row));
		  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
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
    if (gensym_character_code == IFIX(Gensym_code_for_linebreak))
	result = VALUES_2(Gensym_char_or_code_for_linebreak,
		Gensym_esc_for_linebreak_qm);
    else if (gensym_character_code == IFIX(Gensym_code_for_paragraph_break))
	result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
		Gensym_esc_for_paragraph_break_qm);
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
		    ISVREF(Iso_latin1_special_character_code_map,
		    gensym_character_code) : Nil;
	    if (temp);
	    else if (gensym_character_code == 
		    IFIX(Gensym_code_for_capital_ligature_oe))
		temp = CHR('W');
	    else if (gensym_character_code == 
		    IFIX(Gensym_code_for_small_ligature_oe))
		temp = CHR('w');
	    else if (gensym_character_code == IFIX(Gensym_code_for_bullet))
		temp = CHR('*');
	    else if (gensym_character_code == 
		    IFIX(Gensym_code_for_small_letter_f_with_hook))
		temp = CHR('&');
	    else if (gensym_character_code == 
		    IFIX(Gensym_code_for_trade_mark_sign))
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
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = character_or_character_code;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	kanji_code = character_or_character_code;
	octet_1_qm = Nil;
	octet_2 = (SI_Long)0L;
	octet_3 = (SI_Long)0L;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = (SI_Long)92L;
	    twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = (SI_Long)92L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
	code_1 = kanji_code;
	result = chestnut_floorf_function(FIX(IFIX(code_1) & 
		(SI_Long)8191L),FIX((SI_Long)95L));
	MVS_2(result,quotient,remainder_1);
	octet_2 = IFIX(quotient) + (SI_Long)40L;
	octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == (SI_Long)1L) 
		? FIX((IFIX(code_1) >>  -  - (SI_Long)13L) + (SI_Long)32L) 
		: Nil;
	if (octet_1_qm) {
	    simple_or_wide_character = octet_1_qm;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = simple_or_wide_character;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	simple_or_wide_character_1 = octet_2;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = simple_or_wide_character_1;
	    twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
	simple_or_wide_character_1 = octet_3;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = simple_or_wide_character_1;
	    twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    else {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = escape_character_qm;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = escape_character_qm;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = character_or_character_code;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    if (extended_code_qm) {
	char_1 = Nil;
	if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_linebreak))
	    result = VALUES_2(Gensym_char_or_code_for_linebreak,
		    Gensym_esc_for_linebreak_qm);
	else if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_paragraph_break))
	    result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
		    Gensym_esc_for_paragraph_break_qm);
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
			ISVREF(Iso_latin1_special_character_code_map,
			IFIX(extended_code_qm)) : Nil;
		if (temp);
		else if (FIXNUM_EQ(extended_code_qm,
			Gensym_code_for_capital_ligature_oe))
		    temp = CHR('W');
		else if (FIXNUM_EQ(extended_code_qm,
			Gensym_code_for_small_ligature_oe))
		    temp = CHR('w');
		else if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_bullet))
		    temp = CHR('*');
		else if (FIXNUM_EQ(extended_code_qm,
			Gensym_code_for_small_letter_f_with_hook))
		    temp = CHR('&');
		else if (FIXNUM_EQ(extended_code_qm,
			Gensym_code_for_trade_mark_sign))
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
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = character_or_character_code;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	    kanji_code = character_or_character_code;
	    octet_1_qm = Nil;
	    octet_2 = (SI_Long)0L;
	    octet_3 = (SI_Long)0L;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = (SI_Long)92L;
		twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = (SI_Long)92L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	    code_1 = kanji_code;
	    result = chestnut_floorf_function(FIX(IFIX(code_1) & 
		    (SI_Long)8191L),FIX((SI_Long)95L));
	    MVS_2(result,quotient,remainder_1);
	    octet_2 = IFIX(quotient) + (SI_Long)40L;
	    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	    octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
		    (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
		    (SI_Long)13L) + (SI_Long)32L) : Nil;
	    if (octet_1_qm) {
		simple_or_wide_character = octet_1_qm;
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing = simple_or_wide_character;
		    twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_2 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing = simple_or_wide_character;
		    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		    temp_2 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_2;
		}
	    }
	    simple_or_wide_character_1 = octet_2;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = simple_or_wide_character_1;
		twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = simple_or_wide_character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	    simple_or_wide_character_1 = octet_3;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = simple_or_wide_character_1;
		twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = simple_or_wide_character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	else {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = escape_character_qm;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = escape_character_qm;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = character_or_character_code;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
    }
    wide_string_index = wide_string_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* UNICODE-TO-UTF-G-WIDE-STRING */
Object unicode_to_utf_g_wide_string(text_string)
    Object text_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(28,339);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      twrite_utf_g_from_text_string(text_string);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* UNICODE-TO-UTF-G-GENSYM-STRING */
Object unicode_to_utf_g_gensym_string(text_string)
    Object text_string;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object temp;
    Declare_special(4);

    x_note_fn_call(28,340);
    current_gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    twrite_utf_g_from_text_string(text_string);
	    temp = copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Intern_string_buffer, Qintern_string_buffer);

/* TWRITE-INTERN-STRING-BUFFER-AS-GENSYM-CHARACTERS */
Object twrite_intern_string_buffer_as_gensym_characters(size)
    Object size;
{
    Object wide_character_code, code, extended_code, unicode, code_1, temp;
    Object row, gensym_character_code_qm, gensym_character_code;
    Object extended_code_qm, char_1, simple_gensym_character_code;
    Object character_or_character_code, escape_character_qm, thing, temp_2;
    Object schar_arg_2, schar_new_value, kanji_code, octet_1_qm, quotient;
    Object remainder_1, simple_or_wide_character;
    SI_Long i, ab_loop_bind_, gensym_full_row, gensymed_symbol;
    SI_Long gensymed_symbol_1, octet_2, octet_3, thing_1;
    SI_Long simple_or_wide_character_1;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(28,341);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(size);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wide_character_code = CHAR_CODE(CHR(ICHAR(Intern_string_buffer,i)));
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
	row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	  gensym_full_row = 
		  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,IFIX(Row));
	  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
	      gensymed_symbol = gensym_full_row << (SI_Long)8L;
	      gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
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
	    code = map_unicode_to_gensym_han_character_code(unicode);
	    temp = code;
	    if (temp);
	    else {
		row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
		PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		  gensym_full_row = 
			  UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
			  IFIX(Row));
		  if ( !(gensym_full_row == IFIX(Invalid_gensym_full_row))) {
		      gensymed_symbol = gensym_full_row << (SI_Long)8L;
		      gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
		      code = FIX(gensymed_symbol + gensymed_symbol_1);
		  }
		  else
		      code = Nil;
		POP_SPECIAL();
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
    if (FIXNUM_EQ(gensym_character_code,Gensym_code_for_linebreak))
	result = VALUES_2(Gensym_char_or_code_for_linebreak,
		Gensym_esc_for_linebreak_qm);
    else if (FIXNUM_EQ(gensym_character_code,Gensym_code_for_paragraph_break))
	result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
		Gensym_esc_for_paragraph_break_qm);
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
		    ISVREF(Iso_latin1_special_character_code_map,
		    IFIX(gensym_character_code)) : Nil;
	    if (temp);
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_capital_ligature_oe))
		temp = CHR('W');
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_small_ligature_oe))
		temp = CHR('w');
	    else if (FIXNUM_EQ(gensym_character_code,Gensym_code_for_bullet))
		temp = CHR('*');
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_small_letter_f_with_hook))
		temp = CHR('&');
	    else if (FIXNUM_EQ(gensym_character_code,
		    Gensym_code_for_trade_mark_sign))
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
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = character_or_character_code;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	kanji_code = character_or_character_code;
	octet_1_qm = Nil;
	octet_2 = (SI_Long)0L;
	octet_3 = (SI_Long)0L;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = (SI_Long)92L;
	    twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = (SI_Long)92L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
	code_1 = kanji_code;
	result = chestnut_floorf_function(FIX(IFIX(code_1) & 
		(SI_Long)8191L),FIX((SI_Long)95L));
	MVS_2(result,quotient,remainder_1);
	octet_2 = IFIX(quotient) + (SI_Long)40L;
	octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == (SI_Long)1L) 
		? FIX((IFIX(code_1) >>  -  - (SI_Long)13L) + (SI_Long)32L) 
		: Nil;
	if (octet_1_qm) {
	    simple_or_wide_character = octet_1_qm;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = simple_or_wide_character;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	simple_or_wide_character_1 = octet_2;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = simple_or_wide_character_1;
	    twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
	simple_or_wide_character_1 = octet_3;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = simple_or_wide_character_1;
	    twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    else {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = escape_character_qm;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = escape_character_qm;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = character_or_character_code;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_2 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
	    temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_2;
	}
    }
    if (extended_code_qm) {
	char_1 = Nil;
	if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_linebreak))
	    result = VALUES_2(Gensym_char_or_code_for_linebreak,
		    Gensym_esc_for_linebreak_qm);
	else if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_paragraph_break))
	    result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
		    Gensym_esc_for_paragraph_break_qm);
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
			ISVREF(Iso_latin1_special_character_code_map,
			IFIX(extended_code_qm)) : Nil;
		if (temp);
		else if (FIXNUM_EQ(extended_code_qm,
			Gensym_code_for_capital_ligature_oe))
		    temp = CHR('W');
		else if (FIXNUM_EQ(extended_code_qm,
			Gensym_code_for_small_ligature_oe))
		    temp = CHR('w');
		else if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_bullet))
		    temp = CHR('*');
		else if (FIXNUM_EQ(extended_code_qm,
			Gensym_code_for_small_letter_f_with_hook))
		    temp = CHR('&');
		else if (FIXNUM_EQ(extended_code_qm,
			Gensym_code_for_trade_mark_sign))
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
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = character_or_character_code;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	    kanji_code = character_or_character_code;
	    octet_1_qm = Nil;
	    octet_2 = (SI_Long)0L;
	    octet_3 = (SI_Long)0L;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = (SI_Long)92L;
		twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = (SI_Long)92L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	    code_1 = kanji_code;
	    result = chestnut_floorf_function(FIX(IFIX(code_1) & 
		    (SI_Long)8191L),FIX((SI_Long)95L));
	    MVS_2(result,quotient,remainder_1);
	    octet_2 = IFIX(quotient) + (SI_Long)40L;
	    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	    octet_1_qm =  !(IFIX(code_1) >>  -  - (SI_Long)13L == 
		    (SI_Long)1L) ? FIX((IFIX(code_1) >>  -  - 
		    (SI_Long)13L) + (SI_Long)32L) : Nil;
	    if (octet_1_qm) {
		simple_or_wide_character = octet_1_qm;
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing = simple_or_wide_character;
		    twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_2 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing = simple_or_wide_character;
		    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		    SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		    temp_2 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_2;
		}
	    }
	    simple_or_wide_character_1 = octet_2;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = simple_or_wide_character_1;
		twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = simple_or_wide_character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	    simple_or_wide_character_1 = octet_3;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = simple_or_wide_character_1;
		twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = simple_or_wide_character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
			CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
	else {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = escape_character_qm;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = escape_character_qm;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = character_or_character_code;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_2 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_2,schar_arg_2,schar_new_value);
		temp_2 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_2;
	    }
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* INTERN-WIDE-STRING */
Object intern_wide_string varargs_1(int, n)
{
    Object wide_string;
    Object package_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,342);
    INIT_ARGS_nonrelocating();
    wide_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = intern_wide_string_no_reclaim(2,wide_string,package_qm);
    reclaim_wide_string(wide_string);
    return VALUES_1(temp);
}

/* INTERN-WIDE-STRING-NO-RECLAIM */
Object intern_wide_string_no_reclaim varargs_1(int, n)
{
    Object wide_string;
    Object package_qm, index_1, next_char, using_string_buffer_p;
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object code, temp_1, temp_2, wide_character_code, code_1, extended_code;
    Object unicode, temp_3, row, gensym_character_code_qm;
    Object gensym_character_code, extended_code_qm, char_1;
    Object simple_gensym_character_code, character_or_character_code;
    Object escape_character_qm, thing, schar_new_value, kanji_code, octet_1_qm;
    Object quotient, remainder_1, simple_or_wide_character;
    SI_Long index_2, length_1, ab_loop_bind_, gensym_full_row, gensymed_symbol;
    SI_Long gensymed_symbol_1, octet_2, octet_3, thing_1;
    SI_Long simple_or_wide_character_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(28,343);
    INIT_ARGS_nonrelocating();
    wide_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    index_1 = FIX((SI_Long)0L);
    next_char = Nil;
    using_string_buffer_p = T;
    current_gensym_string = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    4);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      3);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		2);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  1);
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
		    Intern_string_buffer_length)) {
		code = next_char;
		temp = IFIX(code) < (SI_Long)127L ?  !((SI_Long)64L == 
			IFIX(code) || (SI_Long)126L == IFIX(code) || 
			(SI_Long)92L == IFIX(code)) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = Intern_string_buffer;
		temp_2 = CODE_CHAR(next_char);
		SET_CHAR(temp_1,index_1,temp_2);
	    }
	    else {
		if (using_string_buffer_p) {
		    using_string_buffer_p = Nil;
		    Current_gensym_string = 
			    obtain_simple_gensym_string(FIX((SI_Long)2048L));
		    twrite_intern_string_buffer_as_gensym_characters(index_1);
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
		    row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
		    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		      gensym_full_row = 
			      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
			      IFIX(Row));
		      if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			  gensymed_symbol = gensym_full_row << (SI_Long)8L;
			  gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
			  gensym_character_code_qm = FIX(gensymed_symbol + 
				  gensymed_symbol_1);
		      }
		      else
			  gensym_character_code_qm = Nil;
		    POP_SPECIAL();
		    if (gensym_character_code_qm) {
			temp = IFIX(gensym_character_code_qm) < 
				(SI_Long)256L ? 
				TRUEP(ISVREF(Iso_latin1_special_character_code_map,
				IFIX(gensym_character_code_qm))) : TRUEP(Nil);
			if (temp);
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_capital_ligature_oe))
			    temp = 'W';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_small_ligature_oe))
			    temp = 'w';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_bullet))
			    temp = '*';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_small_letter_f_with_hook))
			    temp = '&';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_trade_mark_sign))
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
				map_unicode_to_gensym_han_character_code(unicode);
			temp_3 = code_1;
			if (temp_3);
			else {
			    row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
			    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			      gensym_full_row = 
				      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
				      IFIX(Row));
			      if ( !(gensym_full_row == 
				      IFIX(Invalid_gensym_full_row))) {
				  gensymed_symbol = gensym_full_row << 
					  (SI_Long)8L;
				  gensymed_symbol_1 = (SI_Long)255L & 
					  IFIX(unicode);
				  code_1 = FIX(gensymed_symbol + 
					  gensymed_symbol_1);
			      }
			      else
				  code_1 = Nil;
			    POP_SPECIAL();
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
		if (FIXNUM_EQ(gensym_character_code,Gensym_code_for_linebreak))
		    result = VALUES_2(Gensym_char_or_code_for_linebreak,
			    Gensym_esc_for_linebreak_qm);
		else if (FIXNUM_EQ(gensym_character_code,
			Gensym_code_for_paragraph_break))
		    result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
			    Gensym_esc_for_paragraph_break_qm);
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
				ISVREF(Iso_latin1_special_character_code_map,
				IFIX(gensym_character_code)) : Nil;
			if (temp_3);
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_capital_ligature_oe))
			    temp_3 = CHR('W');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_small_ligature_oe))
			    temp_3 = CHR('w');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_bullet))
			    temp_3 = CHR('*');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_small_letter_f_with_hook))
			    temp_3 = CHR('&');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_trade_mark_sign))
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
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_or_character_code;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_1 = Current_gensym_string;
			temp_2 = Fill_pointer_for_current_gensym_string;
			thing = character_or_character_code;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_1;
		    }
		}
		else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
		    kanji_code = character_or_character_code;
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = (SI_Long)92L;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_1 = Current_gensym_string;
			temp_2 = Fill_pointer_for_current_gensym_string;
			thing_1 = (SI_Long)92L;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_1;
		    }
		    code = kanji_code;
		    result = chestnut_floorf_function(FIX(IFIX(code) & 
			    (SI_Long)8191L),FIX((SI_Long)95L));
		    MVS_2(result,quotient,remainder_1);
		    octet_2 = IFIX(quotient) + (SI_Long)40L;
		    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		    octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L == 
			    (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
			    (SI_Long)13L) + (SI_Long)32L) : Nil;
		    if (octet_1_qm) {
			simple_or_wide_character = octet_1_qm;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = simple_or_wide_character;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_1 = Current_gensym_string;
			    temp_2 = Fill_pointer_for_current_gensym_string;
			    thing = simple_or_wide_character;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_1;
			}
		    }
		    simple_or_wide_character_1 = octet_2;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = simple_or_wide_character_1;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_1 = Current_gensym_string;
			temp_2 = Fill_pointer_for_current_gensym_string;
			thing_1 = simple_or_wide_character_1;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_1;
		    }
		    simple_or_wide_character_1 = octet_3;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = simple_or_wide_character_1;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_1 = Current_gensym_string;
			temp_2 = Fill_pointer_for_current_gensym_string;
			thing_1 = simple_or_wide_character_1;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_1;
		    }
		}
		else {
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = escape_character_qm;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_1 = Current_gensym_string;
			temp_2 = Fill_pointer_for_current_gensym_string;
			thing = escape_character_qm;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_1;
		    }
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_or_character_code;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_1 = Current_gensym_string;
			temp_2 = Fill_pointer_for_current_gensym_string;
			thing = character_or_character_code;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_1,temp_2,schar_new_value);
			temp_1 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_1;
		    }
		}
		if (extended_code_qm) {
		    char_1 = Nil;
		    if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_linebreak))
			result = VALUES_2(Gensym_char_or_code_for_linebreak,
				Gensym_esc_for_linebreak_qm);
		    else if (FIXNUM_EQ(extended_code_qm,
			    Gensym_code_for_paragraph_break))
			result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
				Gensym_esc_for_paragraph_break_qm);
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
				    ISVREF(Iso_latin1_special_character_code_map,
				    IFIX(extended_code_qm)) : Nil;
			    if (temp_3);
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_capital_ligature_oe))
				temp_3 = CHR('W');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_small_ligature_oe))
				temp_3 = CHR('w');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_bullet))
				temp_3 = CHR('*');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_small_letter_f_with_hook))
				temp_3 = CHR('&');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_trade_mark_sign))
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
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_1 = Current_gensym_string;
			    temp_2 = Fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_1;
			}
		    }
		    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
			kanji_code = character_or_character_code;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = (SI_Long)92L;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_1 = Current_gensym_string;
			    temp_2 = Fill_pointer_for_current_gensym_string;
			    thing_1 = (SI_Long)92L;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_1;
			}
			code = kanji_code;
			result = chestnut_floorf_function(FIX(IFIX(code) & 
				(SI_Long)8191L),FIX((SI_Long)95L));
			MVS_2(result,quotient,remainder_1);
			octet_2 = IFIX(quotient) + (SI_Long)40L;
			octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L 
				== (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
				(SI_Long)13L) + (SI_Long)32L) : Nil;
			if (octet_1_qm) {
			    simple_or_wide_character = octet_1_qm;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = simple_or_wide_character;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_1 = Current_gensym_string;
				temp_2 = 
					Fill_pointer_for_current_gensym_string;
				thing = simple_or_wide_character;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_1,temp_2,schar_new_value);
				temp_1 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_1;
			    }
			}
			simple_or_wide_character_1 = octet_2;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_1 = Current_gensym_string;
			    temp_2 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_1;
			}
			simple_or_wide_character_1 = octet_3;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_1 = Current_gensym_string;
			    temp_2 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_1;
			}
		    }
		    else {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = escape_character_qm;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_1 = Current_gensym_string;
			    temp_2 = Fill_pointer_for_current_gensym_string;
			    thing = escape_character_qm;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_1;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_1 = Current_gensym_string;
			    temp_2 = Fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_1,temp_2,schar_new_value);
			    temp_1 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_1;
			}
		    }
		}
	    }
	    index_1 = FIXNUM_ADD1(index_1);
	    index_2 = index_2 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    if (using_string_buffer_p)
		result = intern_using_string_buffer(Intern_string_buffer,
			index_1,package_qm);
	    else
		result = intern_gensym_string(2,
			copy_out_current_gensym_string(),package_qm);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INTERN-SIMPLE-SYMBOL-PORTION-OF-WIDE-STRING */
Object intern_simple_symbol_portion_of_wide_string(wide_string,start_init,
	    end_init,package_qm)
    Object wide_string, start_init, end_init, package_qm;
{
    Object s, ab_loop_iter_flag_, schar_new_value, temp;
    SI_Long start, end_1, i, ab_loop_bind_, j;

    x_note_fn_call(28,344);
    start = IFIX(start_init);
    end_1 = IFIX(end_init);
    s = obtain_simple_gensym_string(FIX(end_1 - start));
    i = start;
    ab_loop_bind_ = end_1;
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
    goto end_2;
    temp = Qnil;
  end_2:;
    temp = intern_gensym_string(2,temp,package_qm);
    return VALUES_1(temp);
}

/* INTERN-AND-UPCASE-SIMPLE-SYMBOL-PORTION-OF-WIDE-STRING */
Object intern_and_upcase_simple_symbol_portion_of_wide_string(wide_string,
	    start_init,end_init,package_qm)
    Object wide_string, start_init, end_init, package_qm;
{
    Object s, ab_loop_iter_flag_, schar_new_value, temp;
    SI_Long start, end_1, char_1, case_delta, i, ab_loop_bind_, j, arg, arg_1;
    SI_Long arg_2;

    x_note_fn_call(28,345);
    start = IFIX(start_init);
    end_1 = IFIX(end_init);
    char_1 = (SI_Long)0L;
    s = obtain_simple_gensym_string(FIX(end_1 - start));
    case_delta = (SI_Long)-32L;
    i = start;
    ab_loop_bind_ = end_1;
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
    goto end_2;
    temp = Qnil;
  end_2:;
    temp = intern_gensym_string(2,temp,package_qm);
    return VALUES_1(temp);
}

/* WIDE-STRING-TO-GENSYM-STRING */
Object wide_string_to_gensym_string(wide_string)
    Object wide_string;
{
    Object temp;

    x_note_fn_call(28,346);
    temp = unicode_to_utf_g_gensym_string(wide_string);
    return VALUES_1(temp);
}

static Object list_constant_15;    /* # */

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object list_constant_18;    /* # */

static Object list_constant_19;    /* # */

/* GET-LINE-END-SEQUENCE-FROM-STYLE */
Object get_line_end_sequence_from_style(transcode_text_conversion_style)
    Object transcode_text_conversion_style;
{
    Object temp;

    x_note_fn_call(28,347);
    temp = ISVREF(transcode_text_conversion_style,(SI_Long)4L);
    if (EQ(temp,Qper_platform)) {
	if (EQ(G2_operating_system,Qdos) || EQ(G2_operating_system,Qvms) 
		|| EQ(G2_operating_system,Qwin32))
	    temp = list_constant_15;
	else if (EQ(G2_operating_system,Qunix))
	    temp = list_constant_16;
	else
	    temp = list_constant_16;
    }
    else if (EQ(temp,Qcr))
	temp = list_constant_17;
    else if (EQ(temp,Qlf))
	temp = list_constant_16;
    else if (EQ(temp,Qcrlf))
	temp = list_constant_15;
    else if (EQ(temp,Qunicode_line_separator))
	temp = list_constant_18;
    else if (EQ(temp,Qunicode_paragraph_separator))
	temp = list_constant_19;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* G2-STREAM-WRITE-LINE-WITH-END-CHARACTER-SEQUENCE */
Object g2_stream_write_line_with_end_character_sequence(line,
	    line_end_character_sequence,g2_stream)
    Object line, line_end_character_sequence, g2_stream;
{
    Object character_1, ab_loop_list_, temp;

    x_note_fn_call(28,348);
    if (g2_stream_write_string(line,g2_stream)) {
	character_1 = Nil;
	ab_loop_list_ = line_end_character_sequence;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	character_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(g2_stream_write_char(character_1,g2_stream))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* G2-STREAM-WRITE-UNICODE-UCS-2-LINE */
Object g2_stream_write_unicode_ucs_2_line(line,line_end_character_sequence,
	    byte_swapped_p,g2_stream)
    Object line, line_end_character_sequence, byte_swapped_p, g2_stream;
{
    Object character_1, ab_loop_list_, temp;

    x_note_fn_call(28,349);
    g2_stream_write_unicode_ucs_2_string(line,byte_swapped_p,g2_stream);
    character_1 = Nil;
    ab_loop_list_ = line_end_character_sequence;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    character_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(g2_stream_write_ucs_2_character(character_1,byte_swapped_p,
	    g2_stream))) {
	temp = Nil;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = T;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* G2-STREAM-WRITE-UNICODE-UCS-2-STRING */
Object g2_stream_write_unicode_ucs_2_string(line,byte_swapped_p,g2_stream)
    Object line, byte_swapped_p, g2_stream;
{
    Object character_1, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(28,350);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(line));
    character_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(line,i));
    if ( !TRUEP(g2_stream_write_ucs_2_character(character_1,byte_swapped_p,
	    g2_stream))) {
	temp = Nil;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = T;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* G2-STREAM-WRITE-UCS-2-CHARACTER */
Object g2_stream_write_ucs_2_character(character_1,byte_swapped_p,g2_stream)
    Object character_1, byte_swapped_p, g2_stream;
{
    Object temp;

    x_note_fn_call(28,351);
    temp = g2_stream_write_char(byte_swapped_p ? FIX(IFIX(character_1) & 
	    (SI_Long)255L) : FIX(IFIX(character_1) >>  -  - (SI_Long)8L),
	    g2_stream) ? g2_stream_write_char(byte_swapped_p ? 
	    FIX(IFIX(character_1) >>  -  - (SI_Long)8L) : 
	    FIX(IFIX(character_1) & (SI_Long)255L),g2_stream) : Nil;
    return VALUES_1(temp);
}

/* G2-STREAM-WRITE-TRAILING-BYTES-OF-WIDE-STRING */
Object g2_stream_write_trailing_bytes_of_wide_string(string_1,g2_stream)
    Object string_1, g2_stream;
{
    Object character_1, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(28,352);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(string_1));
    character_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(string_1,i));
    if ( !TRUEP(g2_stream_write_char(FIX(IFIX(character_1) & 
	    (SI_Long)255L),g2_stream))) {
	temp = Nil;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = T;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* EXPORT-AND-EMIT-TEXT-LINE */
Object export_and_emit_text_line(string_1,transcode_text_conversion_style,
	    g2_stream)
    Object string_1, transcode_text_conversion_style, g2_stream;
{
    Object encoded_string, temp;

    x_note_fn_call(28,353);
    encoded_string = export_text_string_per_text_conversion_style(2,
	    string_1,transcode_text_conversion_style);
    temp = 
	    g2_stream_write_wide_string_using_text_conversion_style(transcode_text_conversion_style,
	    encoded_string,g2_stream) ? 
	    g2_stream_write_line_terminator_using_text_conversion_style(transcode_text_conversion_style,
	    g2_stream) : Qnil;
    if (STRINGP(encoded_string))
	reclaim_gensym_string(encoded_string);
    else
	reclaim_text_string(encoded_string);
    return VALUES_1(temp);
}

/* EXPORT-AND-EMIT-TEXT-STRING */
Object export_and_emit_text_string(string_1,
	    transcode_text_conversion_style,g2_stream)
    Object string_1, transcode_text_conversion_style, g2_stream;
{
    Object encoded_string, temp;

    x_note_fn_call(28,354);
    encoded_string = export_text_string_per_text_conversion_style(2,
	    string_1,transcode_text_conversion_style);
    temp = 
	    g2_stream_write_wide_string_using_text_conversion_style(transcode_text_conversion_style,
	    encoded_string,g2_stream);
    reclaim_text_string(encoded_string);
    return VALUES_1(temp);
}

/* EXPORT-AND-EMIT-CHARACTER */
Object export_and_emit_character(character_1,
	    transcode_text_conversion_style,g2_stream)
    Object character_1, transcode_text_conversion_style, g2_stream;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object thing, temp, schar_arg_2, schar_new_value, string_1, encoded_string;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(28,355);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = character_1;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = character_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      string_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    encoded_string = export_text_string_per_text_conversion_style(2,
	    string_1,transcode_text_conversion_style);
    temp_1 = 
	    g2_stream_write_wide_string_using_text_conversion_style(transcode_text_conversion_style,
	    encoded_string,g2_stream);
    reclaim_text_string(string_1);
    reclaim_text_string(encoded_string);
    return VALUES_1(temp_1);
}

static Object Qunicode;            /* unicode */

static Object Qunicode_byte_swapped;  /* unicode-byte-swapped */

static Object Qunicode_ucs_2;      /* unicode-ucs-2 */

static Object Qunicode_ucs_2_byte_swapped;  /* unicode-ucs-2-byte-swapped */

/* G2-STREAM-WRITE-WIDE-STRING-USING-TEXT-CONVERSION-STYLE */
Object g2_stream_write_wide_string_using_text_conversion_style(transcode_text_conversion_style,
	    wide_string,g2_stream)
    Object transcode_text_conversion_style, wide_string, g2_stream;
{
    Object gensymed_symbol, temp;
    SI_Long length_1;

    x_note_fn_call(28,356);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    length_1 = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    gensymed_symbol = ISVREF(transcode_text_conversion_style,(SI_Long)2L);
    if ((EQ(gensymed_symbol,Qunicode) || EQ(gensymed_symbol,
	    Qunicode_byte_swapped) || EQ(gensymed_symbol,Qunicode_ucs_2) 
	    || EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? 
	    (SI_Long)2L : (SI_Long)1L) == (SI_Long)2L) {
	gensymed_symbol = ISVREF(transcode_text_conversion_style,(SI_Long)2L);
	temp = EQ(gensymed_symbol,Qunicode) || EQ(gensymed_symbol,
		Qunicode_byte_swapped) ? 
		g2_stream_write_from_wide_string_buffer(wide_string,
		FIX(length_1),g2_stream) : 
		g2_stream_write_from_buffer(wide_string,FIX(length_1),
		g2_stream);
    }
    else
	temp = g2_stream_write_from_buffer(wide_string,FIX(length_1),
		g2_stream);
    return VALUES_1(temp);
}

/* G2-STREAM-WRITE-LINE-TERMINATOR-USING-TEXT-CONVERSION-STYLE */
Object g2_stream_write_line_terminator_using_text_conversion_style(transcode_text_conversion_style,
	    g2_stream)
    Object transcode_text_conversion_style, g2_stream;
{
    Object line_end_character_sequence, gensymed_symbol, character_1;
    Object ab_loop_list_, temp;

    x_note_fn_call(28,357);
    line_end_character_sequence = 
	    get_line_end_sequence_from_style(transcode_text_conversion_style);
    gensymed_symbol = ISVREF(transcode_text_conversion_style,(SI_Long)2L);
    if ((SI_Long)2L == (EQ(gensymed_symbol,Qunicode) || EQ(gensymed_symbol,
	    Qunicode_byte_swapped) || EQ(gensymed_symbol,Qunicode_ucs_2) 
	    || EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? 
	    (SI_Long)2L : (SI_Long)1L)) {
	character_1 = Nil;
	ab_loop_list_ = line_end_character_sequence;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	character_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = character_1;
	gensymed_symbol = ISVREF(transcode_text_conversion_style,(SI_Long)2L);
	if ( !TRUEP(g2_stream_write_ucs_2_character(temp,
		EQ(gensymed_symbol,Qunicode_byte_swapped) || 
		EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? T : Nil,
		g2_stream))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else {
	character_1 = Nil;
	ab_loop_list_ = line_end_character_sequence;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	character_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(g2_stream_write_char(character_1,g2_stream))) {
	    temp = Nil;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp = T;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Standard_8_bit_non_graphic_characters_skip_spec, Qstandard_8_bit_non_graphic_characters_skip_spec);

void transcode_INIT()
{
    Object temp, reclaim_structure_for_transcode_text_conversion_style_1;
    Object reclaim_structure_for_text_sequence_1;
    Object reclaim_structure_for_gensym_string_text_sequence_1;
    Object reclaim_structure_for_wide_string_text_sequence_1;
    Object initialize_text_sequence_string_for_text_sequence_1;
    Object initialize_text_sequence_string_for_gensym_string_text_sequence_1;
    Object initialize_text_sequence_string_for_wide_string_text_sequence_1;
    Object read_character_from_text_sequence_for_gensym_string_text_sequence_1;
    Object read_character_from_text_sequence_for_wide_string_text_sequence_1;
    Object reclaim_structure_for_transcoder_1;
    Object transcode_character_for_transcoder_1;
    Object export_character_for_transcoder_1;
    Object transcode_as_text_string_for_transcoder_1;
    Object twrite_unicode_from_transcoder_for_transcoder_1;
    Object export_as_string_for_transcoder_1;
    Object twrite_for_export_from_transcoder_for_transcoder_1;
    Object reclaim_structure_for_graphic_character_set_1;
    Object reclaim_structure_for_iso_646_1, synonym, ab_loop_list_;
    Object map_code_to_unicode_for_iso_646_1;
    Object map_unicode_to_code_if_any_for_iso_646_1;
    Object reclaim_structure_for_iso_8859_abstract_1;
    Object map_code_to_unicode_for_iso_8859_abstract_1;
    Object map_unicode_to_code_if_any_for_iso_8859_abstract_1;
    Object reclaim_structure_for_iso_8859_1_1;
    Object reclaim_structure_for_iso_8859_2_1;
    Object reclaim_structure_for_iso_8859_3_1;
    Object reclaim_structure_for_iso_8859_4_1;
    Object reclaim_structure_for_iso_8859_5_1;
    Object reclaim_structure_for_iso_8859_6_1;
    Object reclaim_structure_for_iso_8859_7_1;
    Object reclaim_structure_for_iso_8859_8_1;
    Object reclaim_structure_for_iso_8859_9_1;
    Object reclaim_structure_for_iso_8859_10_1;
    Object reclaim_structure_for_asian_double_byte_1;
    Object map_code_to_unicode_for_asian_double_byte_1;
    Object reclaim_structure_for_jis_x_0208_1;
    Object map_code_to_unicode_for_jis_x_0208_1;
    Object map_unicode_to_code_if_any_for_jis_x_0208_1;
    Object reclaim_structure_for_ks_c_5601_1;
    Object map_code_to_unicode_for_ks_c_5601_1;
    Object map_unicode_to_code_if_any_for_ks_c_5601_1;
    Object reclaim_structure_for_gb_2312_1, map_code_to_unicode_for_gb_2312_1;
    Object map_unicode_to_code_if_any_for_gb_2312_1;
    Object reclaim_structure_for_iso_8859_transcoder_1;
    Object transcode_character_for_iso_8859_transcoder_1;
    Object export_character_for_iso_8859_transcoder_1;
    Object reclaim_structure_for_iso_2022_transcoder_1, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, temp_7, temp_8, temp_9, temp_10, temp_11;
    Object temp_12, transcode_character_for_iso_2022_transcoder_1;
    Object export_character_for_iso_2022_transcoder_1;
    Object reclaim_structure_for_shift_jis_transcoder_1;
    Object transcode_character_for_shift_jis_transcoder_1;
    Object export_character_for_shift_jis_transcoder_1;
    Object reclaim_structure_for_utf_g_transcoder_1;
    Object transcode_character_for_utf_g_transcoder_1;
    Object export_character_for_utf_g_transcoder_1;
    Object reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder_1;
    Object export_character_for_utf_g_ascii_as_much_as_possible_transcoder_1;
    Object reclaim_structure_for_unicode_ucs_2_transcoder_1;
    Object transcode_character_for_unicode_ucs_2_transcoder_1;
    Object export_character_for_unicode_ucs_2_transcoder_1;
    Object reclaim_structure_for_unicode_transcoder_1;
    Object transcode_character_for_unicode_transcoder_1;
    Object export_character_for_unicode_transcoder_1;
    Object reclaim_structure_for_unicode_byte_swapped_transcoder_1;
    Object transcode_character_for_unicode_byte_swapped_transcoder_1;
    Object export_character_for_unicode_byte_swapped_transcoder_1;
    Object reclaim_structure_for_utf_7_transcoder_1;
    Object transcode_character_for_utf_7_transcoder_1;
    Object export_character_for_utf_7_transcoder_1;
    Object reclaim_structure_for_utf_8_transcoder_1;
    Object transcode_character_for_utf_8_transcoder_1;
    Object export_character_for_utf_8_transcoder_1;
    Object list_constant_42, list_constant_41, Qutf_8_transcoder;
    Object Qexport_character, Qtranscode_character;
    Object Qcreate_transcoder_for_unicode_utf_8, list_constant_40, Qutf_8;
    Object AB_package, Qunicode_utf_8, Qreclaim_structure;
    Object Qoutstanding_utf_8_transcoder_count;
    Object Qutf_8_transcoder_structure_memory_usage, Qutilities2;
    Object string_constant_79, Qtype_description_of_type, string_constant_78;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_39;
    Object list_constant_38, list_constant_37, list_constant_36;
    Object Qutf_7_transcoder, Qcreate_transcoder_for_unicode_utf_7;
    Object list_constant_35, Qutf_7, Qunicode_utf_7;
    Object Qoutstanding_utf_7_transcoder_count;
    Object Qutf_7_transcoder_structure_memory_usage, string_constant_77;
    Object string_constant_76, string_constant_75;
    Object Qcreate_transcoder_for_unicode_byte_swapped, list_constant_34;
    Object Qiso_10646_byte_swapped, Qcreate_transcoder_for_unicode;
    Object list_constant_33, Qiso_10646;
    Object Qcreate_transcoder_for_unicode_ucs_2_byte_swapped;
    Object Qcreate_transcoder_for_unicode_ucs_2, list_constant_32;
    Object Qiso_10646_ucs_2;
    Object Qcreate_transcoder_for_gensym_with_ascii_as_much_as_possible;
    Object list_constant_31, Qutf_g_ascii_as_much_as_possible;
    Object Qgensym_with_ascii_as_much_as_possible;
    Object Qcreate_transcoder_for_gensym, list_constant_30, Qutf_g;
    Object Qcreate_transcoder_for_iso_8859_10;
    Object Qcreate_transcoder_for_iso_8859_9;
    Object Qcreate_transcoder_for_iso_8859_8;
    Object Qcreate_transcoder_for_iso_8859_7;
    Object Qcreate_transcoder_for_iso_8859_6;
    Object Qcreate_transcoder_for_iso_8859_5;
    Object Qcreate_transcoder_for_iso_8859_4;
    Object Qcreate_transcoder_for_iso_8859_3;
    Object Qcreate_transcoder_for_iso_8859_2;
    Object Qcreate_transcoder_for_iso_8859_1, Qunicode_byte_swapped_transcoder;
    Object Qoutstanding_unicode_byte_swapped_transcoder_count;
    Object Qunicode_byte_swapped_transcoder_structure_memory_usage;
    Object string_constant_74, string_constant_73, Qunicode_transcoder;
    Object Qoutstanding_unicode_transcoder_count;
    Object Qunicode_transcoder_structure_memory_usage, string_constant_72;
    Object string_constant_71, Qunicode_ucs_2_transcoder;
    Object Qoutstanding_unicode_ucs_2_transcoder_count;
    Object Qunicode_ucs_2_transcoder_structure_memory_usage;
    Object string_constant_70, string_constant_69;
    Object Qutf_g_ascii_as_much_as_possible_transcoder;
    Object Qoutstanding_utf_g_ascii_as_much_as_possible_transcoder_count;
    Object Qutf_g_ascii_as_much_as_possible_transcoder_structure_memory_usage;
    Object string_constant_68, string_constant_67, Qutf_g_transcoder;
    Object Qoutstanding_utf_g_transcoder_count;
    Object Qutf_g_transcoder_structure_memory_usage, string_constant_66;
    Object string_constant_65, Qshift_jis_transcoder;
    Object Qoutstanding_shift_jis_transcoder_count;
    Object Qshift_jis_transcoder_structure_memory_usage, string_constant_64;
    Object string_constant_63, Qiso_2022_transcoder, list_constant_29;
    Object list_constant_28, list_constant_20;
    Object Qcreate_transcoder_for_gb_2312_euc, list_constant_27, Qgb2312_euc;
    Object Qgb_euc, Qgb_2312_euc, Qcreate_transcoder_for_gb_2312;
    Object Qcreate_transcoder_for_ks_c_5601_euc, list_constant_26, Qksc_euc;
    Object Qks_euc, Qks_c_5601_euc, Qcreate_transcoder_for_ks_c_5601;
    Object Qcreate_transcoder_for_shift_jis_x_0208, list_constant_25;
    Object Qshift_jis, Qms_kanji, Qshift_jis_x_0208;
    Object Qcreate_transcoder_for_jis_x_0208_euc, list_constant_24, Qjis_euc;
    Object Qjis_x_0208_euc, Qcreate_transcoder_for_jis_x_0208;
    Object Qcreate_transcoder_for_iso_2022, list_constant_23, Qx_compound_text;
    Object Qiso_2022, Qcreate_transcoder_for_iso_646, list_constant_22;
    Object list_constant_21, Qascii, Qiso_646_irv, Qus_ascii, Qansi3_dot_4;
    Object Qoutstanding_iso_2022_transcoder_count;
    Object Qiso_2022_transcoder_structure_memory_usage, string_constant_62;
    Object string_constant_61, Qiso_8859_transcoder;
    Object Qoutstanding_iso_8859_transcoder_count;
    Object Qiso_8859_transcoder_structure_memory_usage, string_constant_60;
    Object string_constant_59, Qmap_unicode_to_code_if_any;
    Object Qmap_code_to_unicode, Qgb2312, Qgb, Qoutstanding_gb_2312_count;
    Object Qgb_2312_structure_memory_usage, string_constant_58;
    Object string_constant_57, string_constant_56, Qksc, Qks;
    Object Qoutstanding_ks_c_5601_count, Qks_c_5601_structure_memory_usage;
    Object string_constant_55, string_constant_54, string_constant_53, Qjis;
    Object Qoutstanding_jis_x_0208_count, Qjis_x_0208_structure_memory_usage;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object Qoutstanding_asian_double_byte_count;
    Object Qasian_double_byte_structure_memory_usage, string_constant_49;
    Object string_constant_48, Qlatin_6, Qoutstanding_iso_8859_10_count;
    Object Qiso_8859_10_structure_memory_usage, string_constant_47;
    Object string_constant_46, string_constant_45, Qlatin_5;
    Object Qoutstanding_iso_8859_9_count, Qiso_8859_9_structure_memory_usage;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object Qlatin_hebrew, Qoutstanding_iso_8859_8_count;
    Object Qiso_8859_8_structure_memory_usage, string_constant_41;
    Object string_constant_40, string_constant_39, Qlatin_greek;
    Object Qoutstanding_iso_8859_7_count, Qiso_8859_7_structure_memory_usage;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object Qlatin_arabic, Qoutstanding_iso_8859_6_count;
    Object Qiso_8859_6_structure_memory_usage, string_constant_35;
    Object string_constant_34, string_constant_33, Qlatin_cyrillic;
    Object Qoutstanding_iso_8859_5_count, Qiso_8859_5_structure_memory_usage;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object Qlatin_4, Qoutstanding_iso_8859_4_count;
    Object Qiso_8859_4_structure_memory_usage, string_constant_29;
    Object string_constant_28, string_constant_27, Qlatin_3;
    Object Qoutstanding_iso_8859_3_count, Qiso_8859_3_structure_memory_usage;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object Qlatin_2, Qoutstanding_iso_8859_2_count;
    Object Qiso_8859_2_structure_memory_usage, string_constant_23;
    Object string_constant_22, string_constant_21, Qlatin_1;
    Object Qoutstanding_iso_8859_1_count, Qiso_8859_1_structure_memory_usage;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object Qout_8859_reverse_unicode_map_hash_vector_43_vectors;
    Object Q8859_reverse_unicode_map_hash_vector_43_vector_memory_usage;
    Object string_constant_17, Qoutstanding_iso_8859_abstract_count;
    Object Qiso_8859_abstract_structure_memory_usage, string_constant_16;
    Object string_constant_15, Qoutstanding_iso_646_count;
    Object Qiso_646_structure_memory_usage, string_constant_14;
    Object string_constant_13, string_constant_12;
    Object Qoutstanding_graphic_character_set_count;
    Object Qgraphic_character_set_structure_memory_usage, string_constant_11;
    Object string_constant_10, Qtranscoder, Qtwrite_for_export_from_transcoder;
    Object Qexport_as_string, Qtwrite_unicode_from_transcoder;
    Object Qtranscode_as_text_string, Qoutstanding_transcoder_count;
    Object Qtranscoder_structure_memory_usage, string_constant_9;
    Object string_constant_8, Qwide_string_text_sequence;
    Object Qread_character_from_text_sequence, Qgensym_string_text_sequence;
    Object Qinitialize_text_sequence_string, Qtext_sequence;
    Object Qoutstanding_wide_string_text_sequence_count;
    Object Qwide_string_text_sequence_structure_memory_usage;
    Object string_constant_7, string_constant_6;
    Object Qoutstanding_gensym_string_text_sequence_count;
    Object Qgensym_string_text_sequence_structure_memory_usage;
    Object string_constant_5, string_constant_4;
    Object Qoutstanding_text_sequence_count;
    Object Qtext_sequence_structure_memory_usage, string_constant_3;
    Object string_constant_2, Qutf_g_gensym_string, Qutf_g_wide_string;
    Object Qutf_8_gensym_string_with_crlf, Qutf_8_gensym_string_with_newline;
    Object Qutf_8_gensym_string, Qutf_8_wide_string, Qutf_7_gensym_string;
    Object Qutf_7_wide_string, Qiso_8859_10_gensym_string_with_crlf;
    Object Qiso_8859_10_gensym_string, Qiso_8859_10_wide_string;
    Object Qiso_8859_9_gensym_string_with_crlf, Qiso_8859_9_gensym_string;
    Object Qiso_8859_9_wide_string, Qiso_8859_8_gensym_string_with_crlf;
    Object Qiso_8859_8_gensym_string, Qiso_8859_8_wide_string;
    Object Qiso_8859_7_gensym_string_with_crlf, Qiso_8859_7_gensym_string;
    Object Qiso_8859_7_wide_string, Qiso_8859_6_gensym_string_with_crlf;
    Object Qiso_8859_6_gensym_string, Qiso_8859_6_wide_string;
    Object Qiso_8859_5_gensym_string_with_crlf, Qiso_8859_5_gensym_string;
    Object Qiso_8859_5_wide_string, Qiso_8859_4_gensym_string_with_crlf;
    Object Qiso_8859_4_gensym_string, Qiso_8859_4_wide_string;
    Object Qiso_8859_3_gensym_string_with_crlf, Qiso_8859_3_gensym_string;
    Object Qiso_8859_3_wide_string, Qiso_8859_2_gensym_string_with_crlf;
    Object Qiso_8859_2_gensym_string, Qiso_8859_2_wide_string;
    Object Qiso_8859_1_gensym_string_with_crlf, Qiso_8859_1_gensym_string;
    Object Qiso_8859_1_wide_string, Qfilter_text_for_gsi;
    Object Qidl_source_file_pathname, Qiso_latin1_gensym_string;
    Object Qicp_filtered_text_string_reader, Qkb_error;
    Object Qnotify_user_if_possible_via_console;
    Object Qinstantiate_file_template_for_printing, Qpformat;
    Object Qgensym_pathname_namestring, Qg2_directory_pathname;
    Object Qus_ascii_gensym_string_with_crlf, Qknown_ascii_to_ascii;
    Object Qknown_iso_latin1_to_iso_latin1;
    Object Qutf_g_ascii_as_much_as_possible_string, Qutf_g_string;
    Object Qcf_unicode_text, Qcf_text, Qx_string, Qx_compound_text_string;
    Object Qgb_2312_euc_gensym_string_with_crlf, Qgb_2312_euc_string;
    Object Qgb_2312_gensym_string_with_crlf, Qgb_2312_string;
    Object Qks_euc_gensym_string_with_crlf, Qks_euc_string;
    Object Qks_gensym_string_with_crlf, Qks_string;
    Object Qshift_jis_gensym_string_with_crlf, Qshift_jis_string;
    Object Qjis_euc_gensym_string_with_crlf, Qjis_euc_string;
    Object Qjis_gensym_string_with_crlf, Qjis_string, Q8859_10_string;
    Object Q8859_9_string, Q8859_8_string, Q8859_7_string, Q8859_6_string;
    Object Q8859_5_string, Q8859_4_string, Q8859_3_string, Q8859_2_string;
    Object Q8859_1_string, Qutf_8_string, Qutf_7_string, Qirrelevant;
    Object Quser_command_line_argument, Qattribute_file_line, Qgfi_input_line;
    Object Qkb_file_comment, Qole_text_of_single_byte_chars, Qidl_file_input;
    Object Qicp_filtered_text_string_writer, Qx_cut_buffer;
    Object Qnamestring_as_gensym_string, Qwin32_message;
    Object Qg2_directory_pathname_w, Qkfep_filename, Qinit_file_command_line;
    Object Qg2_stream_error_string, Qcommand_line_argument;
    Object Qtranscode_text_conversion_style;
    Object Qoutstanding_transcode_text_conversion_style_count;
    Object Qtranscode_text_conversion_style_structure_memory_usage;
    Object string_constant_1, string_constant, Qunicode_replacement_character;
    Object Qascii_replacement_character;

    x_note_fn_call(28,358);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qascii_replacement_character = 
	    STATIC_SYMBOL("ASCII-REPLACEMENT-CHARACTER",AB_package);
    SET_SYMBOL_VALUE(Qascii_replacement_character,FIX((SI_Long)63L));
    Qunicode_replacement_character = 
	    STATIC_SYMBOL("UNICODE-REPLACEMENT-CHARACTER",AB_package);
    SET_SYMBOL_VALUE(Qunicode_replacement_character,FIX((SI_Long)65533L));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct 
	    = STATIC_SYMBOL("TRANSCODE-TEXT-CONVERSION-STYLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtranscode_text_conversion_style = 
	    STATIC_SYMBOL("TRANSCODE-TEXT-CONVERSION-STYLE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct,
	    Qtranscode_text_conversion_style,
	    Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qtranscode_text_conversion_style,
	    Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_transcode_text_conversion_style == UNBOUND)
	The_type_description_of_transcode_text_conversion_style = Nil;
    string_constant = STATIC_STRING("43Dy8m83cKy1n83cKy8n8k1l8n0000000krk0k0");
    temp = The_type_description_of_transcode_text_conversion_style;
    The_type_description_of_transcode_text_conversion_style = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_transcode_text_conversion_style_g2_struct,
	    The_type_description_of_transcode_text_conversion_style,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qtranscode_text_conversion_style,
	    The_type_description_of_transcode_text_conversion_style,
	    Qtype_description_of_type);
    Qoutstanding_transcode_text_conversion_style_count = 
	    STATIC_SYMBOL("OUTSTANDING-TRANSCODE-TEXT-CONVERSION-STYLE-COUNT",
	    AB_package);
    Qtranscode_text_conversion_style_structure_memory_usage = 
	    STATIC_SYMBOL("TRANSCODE-TEXT-CONVERSION-STYLE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_1 = STATIC_STRING("1q83cKy8s83-FDy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_transcode_text_conversion_style_count);
    push_optimized_constant(Qtranscode_text_conversion_style_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_transcode_text_conversion_styles = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TRANSCODE-TEXT-CONVERSION-STYLES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_transcode_text_conversion_styles,
	    Chain_of_available_transcode_text_conversion_styles);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_transcode_text_conversion_styles,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtranscode_text_conversion_style_count = 
	    STATIC_SYMBOL("TRANSCODE-TEXT-CONVERSION-STYLE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtranscode_text_conversion_style_count,
	    Transcode_text_conversion_style_count);
    record_system_variable(Qtranscode_text_conversion_style_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_transcode_text_conversion_styles_vector == UNBOUND)
	Chain_of_available_transcode_text_conversion_styles_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtranscode_text_conversion_style_structure_memory_usage,
	    STATIC_FUNCTION(transcode_text_conversion_style_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_transcode_text_conversion_style_count,
	    STATIC_FUNCTION(outstanding_transcode_text_conversion_style_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_transcode_text_conversion_style_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_transcode_text_conversion_style,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qtranscode_text_conversion_style,
	    reclaim_structure_for_transcode_text_conversion_style_1);
    Qper_platform = STATIC_SYMBOL("PER-PLATFORM",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qtext_conversion_style_for_purpose = 
	    STATIC_SYMBOL("TEXT-CONVERSION-STYLE-FOR-PURPOSE",AB_package);
    Text_conversion_style_for_purpose_prop = 
	    Qtext_conversion_style_for_purpose;
    Qcommand_line_argument = STATIC_SYMBOL("COMMAND-LINE-ARGUMENT",AB_package);
    Qiso_8859_1 = STATIC_SYMBOL("ISO-8859-1",AB_package);
    Qirrelevant = STATIC_SYMBOL("IRRELEVANT",AB_package);
    install_text_transcode_purpose(Qcommand_line_argument,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qirrelevant,Qnil,Qnil);
    Qg2_stream_error_string = STATIC_SYMBOL("G2-STREAM-ERROR-STRING",
	    AB_package);
    install_text_transcode_purpose(Qg2_stream_error_string,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qirrelevant,Qnil,Qnil);
    Qinit_file_command_line = STATIC_SYMBOL("INIT-FILE-COMMAND-LINE",
	    AB_package);
    install_text_transcode_purpose(Qinit_file_command_line,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qirrelevant,Qnil,Qnil);
    Qkfep_filename = STATIC_SYMBOL("KFEP-FILENAME",AB_package);
    install_text_transcode_purpose(Qkfep_filename,Qnil,Qnil,Qiso_8859_1,
	    Qnil,Qirrelevant,Qnil,Qnil);
    Qg2_directory_pathname = STATIC_SYMBOL("G2-DIRECTORY-PATHNAME",AB_package);
    install_text_transcode_purpose(Qg2_directory_pathname,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qirrelevant,Qnil,Qnil);
    Qg2_directory_pathname_w = STATIC_SYMBOL("G2-DIRECTORY-PATHNAME-W",
	    AB_package);
    Qunicode = STATIC_SYMBOL("UNICODE",AB_package);
    install_text_transcode_purpose(Qg2_directory_pathname_w,Qnil,Qnil,
	    Qunicode,Qnil,Qirrelevant,Qnil,Qnil);
    Qwin32_message = STATIC_SYMBOL("WIN32-MESSAGE",AB_package);
    install_text_transcode_purpose(Qwin32_message,Qnil,Qnil,Qiso_8859_1,
	    Qnil,Qnil,Qnil,Qnil);
    Qicp_filtered_text_string_writer = 
	    STATIC_SYMBOL("ICP-FILTERED-TEXT-STRING-WRITER",AB_package);
    install_text_transcode_purpose(Qicp_filtered_text_string_writer,Qnil,
	    Qnil,Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qgensym_pathname_namestring = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-NAMESTRING",AB_package);
    install_text_transcode_purpose(Qgensym_pathname_namestring,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qnamestring_as_gensym_string = 
	    STATIC_SYMBOL("NAMESTRING-AS-GENSYM-STRING",AB_package);
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    install_text_transcode_purpose(Qnamestring_as_gensym_string,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qgensym_string);
    Qx_cut_buffer = STATIC_SYMBOL("X-CUT-BUFFER",AB_package);
    Qlf = STATIC_SYMBOL("LF",AB_package);
    install_text_transcode_purpose(Qx_cut_buffer,Qnil,Qnil,Qiso_8859_1,
	    Qnil,Qlf,Qnil,Qgensym_string);
    install_text_transcode_purpose(Qicp_filtered_text_string_writer,Qnil,
	    Qnil,Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qidl_file_input = STATIC_SYMBOL("IDL-FILE-INPUT",AB_package);
    install_text_transcode_purpose(Qidl_file_input,Qnil,Qnil,Qiso_8859_1,
	    Qnil,Qnil,Qnil,Qnil);
    Qole_text_of_single_byte_chars = 
	    STATIC_SYMBOL("OLE-TEXT-OF-SINGLE-BYTE-CHARS",AB_package);
    install_text_transcode_purpose(Qole_text_of_single_byte_chars,Qnil,
	    Qnil,Qiso_8859_1,Qnil,Qnil,Qnil,Qgensym_string);
    Qfilter_text_for_gsi = STATIC_SYMBOL("FILTER-TEXT-FOR-GSI",AB_package);
    install_text_transcode_purpose(Qfilter_text_for_gsi,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qkb_file_comment = STATIC_SYMBOL("KB-FILE-COMMENT",AB_package);
    install_text_transcode_purpose(Qkb_file_comment,Qnil,Qnil,Qiso_8859_1,
	    Qnil,Qnil,Qnil,Qgensym_string);
    Qgfi_input_line = STATIC_SYMBOL("GFI-INPUT-LINE",AB_package);
    Qutf_g = STATIC_SYMBOL("UTF-G",AB_package);
    install_text_transcode_purpose(Qgfi_input_line,Qnil,Qnil,Qutf_g,Qnil,
	    Qnil,Qnil,Qnil);
    Qattribute_file_line = STATIC_SYMBOL("ATTRIBUTE-FILE-LINE",AB_package);
    install_text_transcode_purpose(Qattribute_file_line,Qnil,Qnil,Qutf_g,
	    Qnil,Qnil,Qnil,Qnil);
    Quser_command_line_argument = 
	    STATIC_SYMBOL("USER-COMMAND-LINE-ARGUMENT",AB_package);
    install_text_transcode_purpose(Quser_command_line_argument,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qirrelevant,Qnil,Qnil);
    Qutf_7_string = STATIC_SYMBOL("UTF-7-STRING",AB_package);
    Qunicode_utf_7 = STATIC_SYMBOL("UNICODE-UTF-7",AB_package);
    install_text_transcode_purpose(Qutf_7_string,Qnil,Qnil,Qunicode_utf_7,
	    Qnil,Qnil,Qnil,Qnil);
    Qutf_8_string = STATIC_SYMBOL("UTF-8-STRING",AB_package);
    Qunicode_utf_8 = STATIC_SYMBOL("UNICODE-UTF-8",AB_package);
    install_text_transcode_purpose(Qutf_8_string,Qnil,Qnil,Qunicode_utf_8,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_1_string = STATIC_SYMBOL("8859-1-STRING",AB_package);
    install_text_transcode_purpose(Q8859_1_string,Qnil,Qnil,Qiso_8859_1,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_2_string = STATIC_SYMBOL("8859-2-STRING",AB_package);
    Qiso_8859_2 = STATIC_SYMBOL("ISO-8859-2",AB_package);
    install_text_transcode_purpose(Q8859_2_string,Qnil,Qnil,Qiso_8859_2,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_3_string = STATIC_SYMBOL("8859-3-STRING",AB_package);
    Qiso_8859_3 = STATIC_SYMBOL("ISO-8859-3",AB_package);
    install_text_transcode_purpose(Q8859_3_string,Qnil,Qnil,Qiso_8859_3,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_4_string = STATIC_SYMBOL("8859-4-STRING",AB_package);
    Qiso_8859_4 = STATIC_SYMBOL("ISO-8859-4",AB_package);
    install_text_transcode_purpose(Q8859_4_string,Qnil,Qnil,Qiso_8859_4,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_5_string = STATIC_SYMBOL("8859-5-STRING",AB_package);
    Qiso_8859_5 = STATIC_SYMBOL("ISO-8859-5",AB_package);
    install_text_transcode_purpose(Q8859_5_string,Qnil,Qnil,Qiso_8859_5,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_6_string = STATIC_SYMBOL("8859-6-STRING",AB_package);
    Qiso_8859_6 = STATIC_SYMBOL("ISO-8859-6",AB_package);
    install_text_transcode_purpose(Q8859_6_string,Qnil,Qnil,Qiso_8859_6,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_7_string = STATIC_SYMBOL("8859-7-STRING",AB_package);
    Qiso_8859_7 = STATIC_SYMBOL("ISO-8859-7",AB_package);
    install_text_transcode_purpose(Q8859_7_string,Qnil,Qnil,Qiso_8859_7,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_8_string = STATIC_SYMBOL("8859-8-STRING",AB_package);
    Qiso_8859_8 = STATIC_SYMBOL("ISO-8859-8",AB_package);
    install_text_transcode_purpose(Q8859_8_string,Qnil,Qnil,Qiso_8859_8,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_9_string = STATIC_SYMBOL("8859-9-STRING",AB_package);
    Qiso_8859_9 = STATIC_SYMBOL("ISO-8859-9",AB_package);
    install_text_transcode_purpose(Q8859_9_string,Qnil,Qnil,Qiso_8859_9,
	    Qnil,Qnil,Qnil,Qnil);
    Q8859_10_string = STATIC_SYMBOL("8859-10-STRING",AB_package);
    Qiso_8859_10 = STATIC_SYMBOL("ISO-8859-10",AB_package);
    install_text_transcode_purpose(Q8859_10_string,Qnil,Qnil,Qiso_8859_10,
	    Qnil,Qnil,Qnil,Qnil);
    Qjis_string = STATIC_SYMBOL("JIS-STRING",AB_package);
    Qjis_x_0208 = STATIC_SYMBOL("JIS-X-0208",AB_package);
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    install_text_transcode_purpose(Qjis_string,Qnil,Qnil,Qjis_x_0208,Qnil,
	    Qnil,Qjapanese,Qnil);
    Qjis_gensym_string_with_crlf = 
	    STATIC_SYMBOL("JIS-GENSYM-STRING-WITH-CRLF",AB_package);
    Qcrlf = STATIC_SYMBOL("CRLF",AB_package);
    install_text_transcode_purpose(Qjis_gensym_string_with_crlf,Qnil,Qnil,
	    Qjis_x_0208,Qnil,Qcrlf,Qjapanese,Qgensym_string);
    Qjis_euc_string = STATIC_SYMBOL("JIS-EUC-STRING",AB_package);
    Qjis_x_0208_euc = STATIC_SYMBOL("JIS-X-0208-EUC",AB_package);
    install_text_transcode_purpose(Qjis_euc_string,Qnil,Qnil,
	    Qjis_x_0208_euc,Qnil,Qnil,Qjapanese,Qnil);
    Qjis_euc_gensym_string_with_crlf = 
	    STATIC_SYMBOL("JIS-EUC-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qjis_euc_gensym_string_with_crlf,Qnil,
	    Qnil,Qjis_x_0208_euc,Qnil,Qcrlf,Qjapanese,Qgensym_string);
    Qshift_jis_string = STATIC_SYMBOL("SHIFT-JIS-STRING",AB_package);
    Qshift_jis_x_0208 = STATIC_SYMBOL("SHIFT-JIS-X-0208",AB_package);
    install_text_transcode_purpose(Qshift_jis_string,Qnil,Qnil,
	    Qshift_jis_x_0208,Qnil,Qnil,Qjapanese,Qnil);
    Qshift_jis_gensym_string_with_crlf = 
	    STATIC_SYMBOL("SHIFT-JIS-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qshift_jis_gensym_string_with_crlf,Qnil,
	    Qnil,Qshift_jis_x_0208,Qnil,Qcrlf,Qjapanese,Qgensym_string);
    Qks_string = STATIC_SYMBOL("KS-STRING",AB_package);
    Qks_c_5601 = STATIC_SYMBOL("KS-C-5601",AB_package);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    install_text_transcode_purpose(Qks_string,Qnil,Qnil,Qks_c_5601,Qnil,
	    Qnil,Qkorean,Qnil);
    Qks_gensym_string_with_crlf = 
	    STATIC_SYMBOL("KS-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qks_gensym_string_with_crlf,Qnil,Qnil,
	    Qks_c_5601,Qnil,Qcrlf,Qkorean,Qgensym_string);
    Qks_euc_string = STATIC_SYMBOL("KS-EUC-STRING",AB_package);
    Qks_c_5601_euc = STATIC_SYMBOL("KS-C-5601-EUC",AB_package);
    install_text_transcode_purpose(Qks_euc_string,Qnil,Qnil,Qks_c_5601_euc,
	    Qnil,Qnil,Qkorean,Qnil);
    Qks_euc_gensym_string_with_crlf = 
	    STATIC_SYMBOL("KS-EUC-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qks_euc_gensym_string_with_crlf,Qnil,
	    Qnil,Qks_c_5601_euc,Qnil,Qcrlf,Qkorean,Qgensym_string);
    Qgb_2312_string = STATIC_SYMBOL("GB-2312-STRING",AB_package);
    Qgb_2312 = STATIC_SYMBOL("GB-2312",AB_package);
    Qchinese = STATIC_SYMBOL("CHINESE",AB_package);
    install_text_transcode_purpose(Qgb_2312_string,Qnil,Qnil,Qgb_2312,Qnil,
	    Qnil,Qchinese,Qnil);
    Qgb_2312_gensym_string_with_crlf = 
	    STATIC_SYMBOL("GB-2312-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qgb_2312_gensym_string_with_crlf,Qnil,
	    Qnil,Qgb_2312,Qnil,Qcrlf,Qchinese,Qgensym_string);
    Qgb_2312_euc_string = STATIC_SYMBOL("GB-2312-EUC-STRING",AB_package);
    Qgb_2312_euc = STATIC_SYMBOL("GB-2312-EUC",AB_package);
    install_text_transcode_purpose(Qgb_2312_euc_string,Qnil,Qnil,
	    Qgb_2312_euc,Qnil,Qnil,Qchinese,Qnil);
    Qgb_2312_euc_gensym_string_with_crlf = 
	    STATIC_SYMBOL("GB-2312-EUC-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qgb_2312_euc_gensym_string_with_crlf,
	    Qnil,Qnil,Qgb_2312_euc,Qnil,Qcrlf,Qchinese,Qgensym_string);
    Qx_compound_text_string = STATIC_SYMBOL("X-COMPOUND-TEXT-STRING",
	    AB_package);
    Qx_compound_text = STATIC_SYMBOL("X-COMPOUND-TEXT",AB_package);
    install_text_transcode_purpose(Qx_compound_text_string,Qnil,Qnil,
	    Qx_compound_text,Qnil,Qlf,Qjapanese,Qgensym_string);
    Qx_string = STATIC_SYMBOL("X-STRING",AB_package);
    install_text_transcode_purpose(Qx_string,Qnil,Qnil,Qiso_8859_1,Qnil,
	    Qlf,Qnil,Qgensym_string);
    Qcf_text = STATIC_SYMBOL("CF-TEXT",AB_package);
    install_text_transcode_purpose(Qcf_text,Qnil,Qnil,Qiso_8859_1,Qnil,
	    Qcrlf,Qnil,Qgensym_string);
    Qcf_unicode_text = STATIC_SYMBOL("CF-UNICODE-TEXT",AB_package);
    install_text_transcode_purpose(Qcf_unicode_text,Qnil,Qnil,Qunicode,
	    Qnil,Qcrlf,Qnil,Qnil);
    Qutf_g_string = STATIC_SYMBOL("UTF-G-STRING",AB_package);
    install_text_transcode_purpose(Qutf_g_string,Qnil,Qnil,Qutf_g,Qnil,
	    Qnil,Qnil,Qnil);
    Qutf_g_ascii_as_much_as_possible_string = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-STRING",AB_package);
    Qutf_g_ascii_as_much_as_possible = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE",AB_package);
    install_text_transcode_purpose(Qutf_g_ascii_as_much_as_possible_string,
	    Qnil,Qnil,Qutf_g_ascii_as_much_as_possible,Qnil,Qnil,Qnil,Qnil);
    if (Default_text_conversion_style == UNBOUND)
	Default_text_conversion_style = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qutf_g_string),
		Qtext_conversion_style_for_purpose);
    if (Utf_g_ascii_as_much_as_possible_conversion_style == UNBOUND)
	Utf_g_ascii_as_much_as_possible_conversion_style = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qutf_g_ascii_as_much_as_possible_string),
		Qtext_conversion_style_for_purpose);
    install_text_transcode_purpose(Qunicode,Qnil,Qnil,Qunicode,Qnil,Qnil,
	    Qnil,Qnil);
    Qknown_iso_latin1_to_iso_latin1 = 
	    STATIC_SYMBOL("KNOWN-ISO-LATIN1-TO-ISO-LATIN1",AB_package);
    install_text_transcode_purpose(Qknown_iso_latin1_to_iso_latin1,Qnil,
	    Qnil,Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qknown_ascii_to_ascii = STATIC_SYMBOL("KNOWN-ASCII-TO-ASCII",AB_package);
    Qus_ascii = STATIC_SYMBOL("US-ASCII",AB_package);
    install_text_transcode_purpose(Qknown_ascii_to_ascii,Qnil,Qnil,
	    Qus_ascii,Qnil,Qnil,Qnil,Qnil);
    Qus_ascii_gensym_string_with_crlf = 
	    STATIC_SYMBOL("US-ASCII-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qus_ascii_gensym_string_with_crlf,Qnil,
	    Qnil,Qus_ascii,Qnil,Qcrlf,Qnil,Qgensym_string);
    install_text_transcode_purpose(Qg2_directory_pathname,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    install_text_transcode_purpose(Qgensym_pathname_namestring,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qpformat = STATIC_SYMBOL("PFORMAT",AB_package);
    install_text_transcode_purpose(Qpformat,Qnil,Qnil,Qiso_8859_1,Qnil,
	    Qnil,Qnil,Qnil);
    Qinstantiate_file_template_for_printing = 
	    STATIC_SYMBOL("INSTANTIATE-FILE-TEMPLATE-FOR-PRINTING",AB_package);
    install_text_transcode_purpose(Qinstantiate_file_template_for_printing,
	    Qnil,Qnil,Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qnotify_user_if_possible_via_console = 
	    STATIC_SYMBOL("NOTIFY-USER-IF-POSSIBLE-VIA-CONSOLE",AB_package);
    install_text_transcode_purpose(Qnotify_user_if_possible_via_console,
	    Qnil,Qnil,Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qkb_error = STATIC_SYMBOL("KB-ERROR",AB_package);
    install_text_transcode_purpose(Qkb_error,Qnil,Qnil,Qiso_8859_1,Qnil,
	    Qnil,Qnil,Qnil);
    Qicp_filtered_text_string_reader = 
	    STATIC_SYMBOL("ICP-FILTERED-TEXT-STRING-READER",AB_package);
    install_text_transcode_purpose(Qicp_filtered_text_string_reader,Qnil,
	    Qnil,Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qiso_latin1_gensym_string = STATIC_SYMBOL("ISO-LATIN1-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_latin1_gensym_string,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qidl_source_file_pathname = STATIC_SYMBOL("IDL-SOURCE-FILE-PATHNAME",
	    AB_package);
    install_text_transcode_purpose(Qidl_source_file_pathname,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    install_text_transcode_purpose(Qfilter_text_for_gsi,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_1_wide_string = STATIC_SYMBOL("ISO-8859-1-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_1_wide_string,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_1_gensym_string = STATIC_SYMBOL("ISO-8859-1-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_1_gensym_string,Qnil,Qnil,
	    Qiso_8859_1,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_1_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-1-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_1_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_1,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qascii = STATIC_SYMBOL("ASCII",AB_package);
    install_text_transcode_purpose(Qascii,Qnil,Qnil,Qiso_8859_1,Qnil,Qnil,
	    Qnil,Qgensym_string);
    Qiso_8859_2_wide_string = STATIC_SYMBOL("ISO-8859-2-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_2_wide_string,Qnil,Qnil,
	    Qiso_8859_2,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_2_gensym_string = STATIC_SYMBOL("ISO-8859-2-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_2_gensym_string,Qnil,Qnil,
	    Qiso_8859_2,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_2_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-2-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_2_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_2,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qiso_8859_3_wide_string = STATIC_SYMBOL("ISO-8859-3-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_3_wide_string,Qnil,Qnil,
	    Qiso_8859_3,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_3_gensym_string = STATIC_SYMBOL("ISO-8859-3-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_3_gensym_string,Qnil,Qnil,
	    Qiso_8859_3,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_3_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-3-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_3_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_3,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qiso_8859_4_wide_string = STATIC_SYMBOL("ISO-8859-4-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_4_wide_string,Qnil,Qnil,
	    Qiso_8859_4,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_4_gensym_string = STATIC_SYMBOL("ISO-8859-4-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_4_gensym_string,Qnil,Qnil,
	    Qiso_8859_4,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_4_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-4-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_4_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_4,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qiso_8859_5_wide_string = STATIC_SYMBOL("ISO-8859-5-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_5_wide_string,Qnil,Qnil,
	    Qiso_8859_5,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_5_gensym_string = STATIC_SYMBOL("ISO-8859-5-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_5_gensym_string,Qnil,Qnil,
	    Qiso_8859_5,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_5_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-5-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_5_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_5,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qiso_8859_6_wide_string = STATIC_SYMBOL("ISO-8859-6-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_6_wide_string,Qnil,Qnil,
	    Qiso_8859_6,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_6_gensym_string = STATIC_SYMBOL("ISO-8859-6-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_6_gensym_string,Qnil,Qnil,
	    Qiso_8859_6,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_6_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-6-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_6_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_6,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qiso_8859_7_wide_string = STATIC_SYMBOL("ISO-8859-7-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_7_wide_string,Qnil,Qnil,
	    Qiso_8859_7,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_7_gensym_string = STATIC_SYMBOL("ISO-8859-7-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_7_gensym_string,Qnil,Qnil,
	    Qiso_8859_7,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_7_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-7-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_7_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_7,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qiso_8859_8_wide_string = STATIC_SYMBOL("ISO-8859-8-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_8_wide_string,Qnil,Qnil,
	    Qiso_8859_8,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_8_gensym_string = STATIC_SYMBOL("ISO-8859-8-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_8_gensym_string,Qnil,Qnil,
	    Qiso_8859_8,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_8_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-8-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_8_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_8,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qiso_8859_9_wide_string = STATIC_SYMBOL("ISO-8859-9-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_9_wide_string,Qnil,Qnil,
	    Qiso_8859_9,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_9_gensym_string = STATIC_SYMBOL("ISO-8859-9-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_9_gensym_string,Qnil,Qnil,
	    Qiso_8859_9,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_9_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-9-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_9_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_9,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qiso_8859_10_wide_string = STATIC_SYMBOL("ISO-8859-10-WIDE-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_10_wide_string,Qnil,Qnil,
	    Qiso_8859_10,Qnil,Qnil,Qnil,Qnil);
    Qiso_8859_10_gensym_string = STATIC_SYMBOL("ISO-8859-10-GENSYM-STRING",
	    AB_package);
    install_text_transcode_purpose(Qiso_8859_10_gensym_string,Qnil,Qnil,
	    Qiso_8859_10,Qnil,Qnil,Qnil,Qgensym_string);
    Qiso_8859_10_gensym_string_with_crlf = 
	    STATIC_SYMBOL("ISO-8859-10-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qiso_8859_10_gensym_string_with_crlf,
	    Qnil,Qnil,Qiso_8859_10,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qutf_7_wide_string = STATIC_SYMBOL("UTF-7-WIDE-STRING",AB_package);
    install_text_transcode_purpose(Qutf_7_wide_string,Qnil,Qnil,
	    Qunicode_utf_7,Qnil,Qnil,Qnil,Qnil);
    Qutf_7_gensym_string = STATIC_SYMBOL("UTF-7-GENSYM-STRING",AB_package);
    install_text_transcode_purpose(Qutf_7_gensym_string,Qnil,Qnil,
	    Qunicode_utf_7,Qnil,Qnil,Qnil,Qgensym_string);
    Qutf_8_wide_string = STATIC_SYMBOL("UTF-8-WIDE-STRING",AB_package);
    install_text_transcode_purpose(Qutf_8_wide_string,Qnil,Qnil,
	    Qunicode_utf_8,Qnil,Qnil,Qnil,Qnil);
    Qutf_8_gensym_string = STATIC_SYMBOL("UTF-8-GENSYM-STRING",AB_package);
    install_text_transcode_purpose(Qutf_8_gensym_string,Qnil,Qnil,
	    Qunicode_utf_8,Qnil,Qnil,Qnil,Qgensym_string);
    Qutf_8_gensym_string_with_newline = 
	    STATIC_SYMBOL("UTF-8-GENSYM-STRING-WITH-NEWLINE",AB_package);
    install_text_transcode_purpose(Qutf_8_gensym_string_with_newline,Qnil,
	    Qnil,Qunicode_utf_8,Qnil,Qlf,Qnil,Qgensym_string);
    Qutf_8_gensym_string_with_crlf = 
	    STATIC_SYMBOL("UTF-8-GENSYM-STRING-WITH-CRLF",AB_package);
    install_text_transcode_purpose(Qutf_8_gensym_string_with_crlf,Qnil,
	    Qnil,Qunicode_utf_8,Qnil,Qcrlf,Qnil,Qgensym_string);
    Qutf_g_wide_string = STATIC_SYMBOL("UTF-G-WIDE-STRING",AB_package);
    install_text_transcode_purpose(Qutf_g_wide_string,Qnil,Qnil,Qutf_g,
	    Qnil,Qnil,Qnil,Qnil);
    Qutf_g_gensym_string = STATIC_SYMBOL("UTF-G-GENSYM-STRING",AB_package);
    install_text_transcode_purpose(Qutf_g_gensym_string,Qnil,Qnil,Qutf_g,
	    Qnil,Qnil,Qnil,Qgensym_string);
    Qg2_defstruct_structure_name_text_sequence_g2_struct = 
	    STATIC_SYMBOL("TEXT-SEQUENCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtext_sequence = STATIC_SYMBOL("TEXT-SEQUENCE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_text_sequence_g2_struct,
	    Qtext_sequence,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtext_sequence,
	    Qg2_defstruct_structure_name_text_sequence_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_text_sequence == UNBOUND)
	The_type_description_of_text_sequence = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8m837Yy1n837Yy8n8k1l8n0000001m1n8y83-66y01m83My83-BAyksk0k0");
    temp = The_type_description_of_text_sequence;
    The_type_description_of_text_sequence = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_2));
    mutate_global_property(Qg2_defstruct_structure_name_text_sequence_g2_struct,
	    The_type_description_of_text_sequence,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtext_sequence,
	    The_type_description_of_text_sequence,Qtype_description_of_type);
    Qoutstanding_text_sequence_count = 
	    STATIC_SYMBOL("OUTSTANDING-TEXT-SEQUENCE-COUNT",AB_package);
    Qtext_sequence_structure_memory_usage = 
	    STATIC_SYMBOL("TEXT-SEQUENCE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_3 = STATIC_STRING("1q837Yy8s83-sZy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_text_sequence_count);
    push_optimized_constant(Qtext_sequence_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qchain_of_available_text_sequences = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TEXT-SEQUENCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_text_sequences,
	    Chain_of_available_text_sequences);
    record_system_variable(Qchain_of_available_text_sequences,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qtext_sequence_count = STATIC_SYMBOL("TEXT-SEQUENCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtext_sequence_count,Text_sequence_count);
    record_system_variable(Qtext_sequence_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_text_sequences_vector == UNBOUND)
	Chain_of_available_text_sequences_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtext_sequence_structure_memory_usage,
	    STATIC_FUNCTION(text_sequence_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_text_sequence_count,
	    STATIC_FUNCTION(outstanding_text_sequence_count,NIL,FALSE,0,0));
    reclaim_structure_for_text_sequence_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_text_sequence,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtext_sequence,
	    reclaim_structure_for_text_sequence_1);
    Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct = 
	    STATIC_SYMBOL("GENSYM-STRING-TEXT-SEQUENCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgensym_string_text_sequence = 
	    STATIC_SYMBOL("GENSYM-STRING-TEXT-SEQUENCE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct,
	    Qgensym_string_text_sequence,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgensym_string_text_sequence,
	    Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gensym_string_text_sequence == UNBOUND)
	The_type_description_of_gensym_string_text_sequence = Nil;
    string_constant_4 = 
	    STATIC_STRING("43Dy8m83hwy1o83hwy837Yy8n8k1l837Yy0000001l1n8x837Yy1m83bky1m9k83-+ryksk0k0");
    temp = The_type_description_of_gensym_string_text_sequence;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_gensym_string_text_sequence = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_4));
    mutate_global_property(Qg2_defstruct_structure_name_gensym_string_text_sequence_g2_struct,
	    The_type_description_of_gensym_string_text_sequence,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgensym_string_text_sequence,
	    The_type_description_of_gensym_string_text_sequence,
	    Qtype_description_of_type);
    Qoutstanding_gensym_string_text_sequence_count = 
	    STATIC_SYMBOL("OUTSTANDING-GENSYM-STRING-TEXT-SEQUENCE-COUNT",
	    AB_package);
    Qgensym_string_text_sequence_structure_memory_usage = 
	    STATIC_SYMBOL("GENSYM-STRING-TEXT-SEQUENCE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_5 = STATIC_STRING("1q83hwy8s83-WJy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gensym_string_text_sequence_count);
    push_optimized_constant(Qgensym_string_text_sequence_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_5));
    Qchain_of_available_gensym_string_text_sequences = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GENSYM-STRING-TEXT-SEQUENCES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gensym_string_text_sequences,
	    Chain_of_available_gensym_string_text_sequences);
    record_system_variable(Qchain_of_available_gensym_string_text_sequences,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgensym_string_text_sequence_count = 
	    STATIC_SYMBOL("GENSYM-STRING-TEXT-SEQUENCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_string_text_sequence_count,
	    Gensym_string_text_sequence_count);
    record_system_variable(Qgensym_string_text_sequence_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gensym_string_text_sequences_vector == UNBOUND)
	Chain_of_available_gensym_string_text_sequences_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgensym_string_text_sequence_structure_memory_usage,
	    STATIC_FUNCTION(gensym_string_text_sequence_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gensym_string_text_sequence_count,
	    STATIC_FUNCTION(outstanding_gensym_string_text_sequence_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_gensym_string_text_sequence_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gensym_string_text_sequence,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qgensym_string_text_sequence,
	    reclaim_structure_for_gensym_string_text_sequence_1);
    Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct = 
	    STATIC_SYMBOL("WIDE-STRING-TEXT-SEQUENCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qwide_string_text_sequence = STATIC_SYMBOL("WIDE-STRING-TEXT-SEQUENCE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct,
	    Qwide_string_text_sequence,Qab_name_of_unique_structure_type);
    mutate_global_property(Qwide_string_text_sequence,
	    Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_wide_string_text_sequence == UNBOUND)
	The_type_description_of_wide_string_text_sequence = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8m83oXy1o83oXy837Yy8n8k1l837Yy0000001l1n8x837Yy1m83bky1m9k83-Gjyksk0k0");
    temp = The_type_description_of_wide_string_text_sequence;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_wide_string_text_sequence = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_6));
    mutate_global_property(Qg2_defstruct_structure_name_wide_string_text_sequence_g2_struct,
	    The_type_description_of_wide_string_text_sequence,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qwide_string_text_sequence,
	    The_type_description_of_wide_string_text_sequence,
	    Qtype_description_of_type);
    Qoutstanding_wide_string_text_sequence_count = 
	    STATIC_SYMBOL("OUTSTANDING-WIDE-STRING-TEXT-SEQUENCE-COUNT",
	    AB_package);
    Qwide_string_text_sequence_structure_memory_usage = 
	    STATIC_SYMBOL("WIDE-STRING-TEXT-SEQUENCE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_7 = STATIC_STRING("1q83oXy8s83-x7y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_wide_string_text_sequence_count);
    push_optimized_constant(Qwide_string_text_sequence_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_7));
    Qchain_of_available_wide_string_text_sequences = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WIDE-STRING-TEXT-SEQUENCES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_wide_string_text_sequences,
	    Chain_of_available_wide_string_text_sequences);
    record_system_variable(Qchain_of_available_wide_string_text_sequences,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qwide_string_text_sequence_count = 
	    STATIC_SYMBOL("WIDE-STRING-TEXT-SEQUENCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwide_string_text_sequence_count,
	    Wide_string_text_sequence_count);
    record_system_variable(Qwide_string_text_sequence_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_wide_string_text_sequences_vector == UNBOUND)
	Chain_of_available_wide_string_text_sequences_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qwide_string_text_sequence_structure_memory_usage,
	    STATIC_FUNCTION(wide_string_text_sequence_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_wide_string_text_sequence_count,
	    STATIC_FUNCTION(outstanding_wide_string_text_sequence_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_wide_string_text_sequence_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_wide_string_text_sequence,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qwide_string_text_sequence,
	    reclaim_structure_for_wide_string_text_sequence_1);
    Qinitialize_text_sequence_string = 
	    STATIC_SYMBOL("INITIALIZE-TEXT-SEQUENCE-STRING",AB_package);
    initialize_text_sequence_string_for_text_sequence_1 = 
	    STATIC_FUNCTION(initialize_text_sequence_string_for_text_sequence,
	    NIL,FALSE,4,4);
    record_direct_structure_method(Qinitialize_text_sequence_string,
	    Qtext_sequence,
	    initialize_text_sequence_string_for_text_sequence_1);
    initialize_text_sequence_string_for_gensym_string_text_sequence_1 = 
	    STATIC_FUNCTION(initialize_text_sequence_string_for_gensym_string_text_sequence,
	    NIL,FALSE,4,4);
    record_direct_structure_method(Qinitialize_text_sequence_string,
	    Qgensym_string_text_sequence,
	    initialize_text_sequence_string_for_gensym_string_text_sequence_1);
    initialize_text_sequence_string_for_wide_string_text_sequence_1 = 
	    STATIC_FUNCTION(initialize_text_sequence_string_for_wide_string_text_sequence,
	    NIL,FALSE,4,4);
    record_direct_structure_method(Qinitialize_text_sequence_string,
	    Qwide_string_text_sequence,
	    initialize_text_sequence_string_for_wide_string_text_sequence_1);
    Qread_character_from_text_sequence = 
	    STATIC_SYMBOL("READ-CHARACTER-FROM-TEXT-SEQUENCE",AB_package);
    read_character_from_text_sequence_for_gensym_string_text_sequence_1 = 
	    STATIC_FUNCTION(read_character_from_text_sequence_for_gensym_string_text_sequence,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qread_character_from_text_sequence,
	    Qgensym_string_text_sequence,
	    read_character_from_text_sequence_for_gensym_string_text_sequence_1);
    read_character_from_text_sequence_for_wide_string_text_sequence_1 = 
	    STATIC_FUNCTION(read_character_from_text_sequence_for_wide_string_text_sequence,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qread_character_from_text_sequence,
	    Qwide_string_text_sequence,
	    read_character_from_text_sequence_for_wide_string_text_sequence_1);
    Qg2_defstruct_structure_name_transcoder_g2_struct = 
	    STATIC_SYMBOL("TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtranscoder = STATIC_SYMBOL("TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_transcoder_g2_struct,
	    Qtranscoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtranscoder,
	    Qg2_defstruct_structure_name_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_transcoder == UNBOUND)
	The_type_description_of_transcoder = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8m83=Ey1n83=Ey8n8k1l8n0000000kqk0k0");
    temp = The_type_description_of_transcoder;
    The_type_description_of_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    mutate_global_property(Qg2_defstruct_structure_name_transcoder_g2_struct,
	    The_type_description_of_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtranscoder,The_type_description_of_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-TRANSCODER-COUNT",AB_package);
    Qtranscoder_structure_memory_usage = 
	    STATIC_SYMBOL("TRANSCODER-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_9 = STATIC_STRING("1q83=Ey8s83-tky09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_transcoder_count);
    push_optimized_constant(Qtranscoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_transcoders,
	    Chain_of_available_transcoders);
    record_system_variable(Qchain_of_available_transcoders,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qtranscoder_count = STATIC_SYMBOL("TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtranscoder_count,Transcoder_count);
    record_system_variable(Qtranscoder_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_transcoders_vector == UNBOUND)
	Chain_of_available_transcoders_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtranscoder_structure_memory_usage,
	    STATIC_FUNCTION(transcoder_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_transcoder_count,
	    STATIC_FUNCTION(outstanding_transcoder_count,NIL,FALSE,0,0));
    reclaim_structure_for_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_transcoder,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtranscoder,
	    reclaim_structure_for_transcoder_1);
    Qtranscode_character = STATIC_SYMBOL("TRANSCODE-CHARACTER",AB_package);
    transcode_character_for_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_transcoder,NIL,FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,Qtranscoder,
	    transcode_character_for_transcoder_1);
    Qexport_character = STATIC_SYMBOL("EXPORT-CHARACTER",AB_package);
    export_character_for_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_transcoder,NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_character,Qtranscoder,
	    export_character_for_transcoder_1);
    Qtranscode_as_text_string = STATIC_SYMBOL("TRANSCODE-AS-TEXT-STRING",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    transcode_as_text_string_for_transcoder_1 = 
	    STATIC_FUNCTION(transcode_as_text_string_for_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qtranscode_as_text_string,Qtranscoder,
	    transcode_as_text_string_for_transcoder_1);
    Qtwrite_unicode_from_transcoder = 
	    STATIC_SYMBOL("TWRITE-UNICODE-FROM-TRANSCODER",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    twrite_unicode_from_transcoder_for_transcoder_1 = 
	    STATIC_FUNCTION(twrite_unicode_from_transcoder_for_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qtwrite_unicode_from_transcoder,
	    Qtranscoder,twrite_unicode_from_transcoder_for_transcoder_1);
    Qexport_as_string = STATIC_SYMBOL("EXPORT-AS-STRING",AB_package);
    export_as_string_for_transcoder_1 = 
	    STATIC_FUNCTION(export_as_string_for_transcoder,NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_as_string,Qtranscoder,
	    export_as_string_for_transcoder_1);
    Qtwrite_for_export_from_transcoder = 
	    STATIC_SYMBOL("TWRITE-FOR-EXPORT-FROM-TRANSCODER",AB_package);
    twrite_for_export_from_transcoder_for_transcoder_1 = 
	    STATIC_FUNCTION(twrite_for_export_from_transcoder_for_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qtwrite_for_export_from_transcoder,
	    Qtranscoder,twrite_for_export_from_transcoder_for_transcoder_1);
    Qg2_defstruct_structure_name_graphic_character_set_g2_struct = 
	    STATIC_SYMBOL("GRAPHIC-CHARACTER-SET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgraphic_character_set = STATIC_SYMBOL("GRAPHIC-CHARACTER-SET",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_graphic_character_set_g2_struct,
	    Qgraphic_character_set,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgraphic_character_set,
	    Qg2_defstruct_structure_name_graphic_character_set_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_graphic_character_set == UNBOUND)
	The_type_description_of_graphic_character_set = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83*Fy1n83*Fy8n8k1l8n0000000krk0k0");
    temp = The_type_description_of_graphic_character_set;
    The_type_description_of_graphic_character_set = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_graphic_character_set_g2_struct,
	    The_type_description_of_graphic_character_set,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgraphic_character_set,
	    The_type_description_of_graphic_character_set,
	    Qtype_description_of_type);
    Qoutstanding_graphic_character_set_count = 
	    STATIC_SYMBOL("OUTSTANDING-GRAPHIC-CHARACTER-SET-COUNT",
	    AB_package);
    Qgraphic_character_set_structure_memory_usage = 
	    STATIC_SYMBOL("GRAPHIC-CHARACTER-SET-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_11 = STATIC_STRING("1q83*Fy8s83-XAy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_graphic_character_set_count);
    push_optimized_constant(Qgraphic_character_set_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_graphic_character_sets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GRAPHIC-CHARACTER-SETS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_graphic_character_sets,
	    Chain_of_available_graphic_character_sets);
    record_system_variable(Qchain_of_available_graphic_character_sets,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgraphic_character_set_count = 
	    STATIC_SYMBOL("GRAPHIC-CHARACTER-SET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraphic_character_set_count,
	    Graphic_character_set_count);
    record_system_variable(Qgraphic_character_set_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_graphic_character_sets_vector == UNBOUND)
	Chain_of_available_graphic_character_sets_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgraphic_character_set_structure_memory_usage,
	    STATIC_FUNCTION(graphic_character_set_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_graphic_character_set_count,
	    STATIC_FUNCTION(outstanding_graphic_character_set_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_graphic_character_set_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_graphic_character_set,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qgraphic_character_set,
	    reclaim_structure_for_graphic_character_set_1);
    Qiso_646 = STATIC_SYMBOL("ISO-646",AB_package);
    Qiso_646_irv = STATIC_SYMBOL("ISO-646-IRV",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qiso_646_irv,Qascii,Qus_ascii);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Graphic_character_set_prop = Qgraphic_character_set;
    Qtranscoder_creation_function = 
	    STATIC_SYMBOL("TRANSCODER-CREATION-FUNCTION",AB_package);
    Transcoder_creation_function_prop = Qtranscoder_creation_function;
    Qg2_defstruct_structure_name_iso_646_g2_struct = 
	    STATIC_SYMBOL("ISO-646-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_646_g2_struct,
	    Qiso_646,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_646,
	    Qg2_defstruct_structure_name_iso_646_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_646 == UNBOUND)
	The_type_description_of_iso_646 = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8m83jAy1o83jAy83*Fy8n8k1l83*Fy0000001l1r8x83*Fy1m83*Qy1m9k83jAy1m83*Sy1m9k1o83-=sy83Gfy83oHy83pgy1m83*Py1m9kl1m83*Oy1m9k3-Qy");
    string_constant_13 = STATIC_STRING("1m83*Ry1m9k+s3-*ykkkkkl3A++ykrk0k0");
    temp = The_type_description_of_iso_646;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_646 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_12,
	    string_constant_13)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_646_g2_struct,
	    The_type_description_of_iso_646,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_646,The_type_description_of_iso_646,
	    Qtype_description_of_type);
    Qoutstanding_iso_646_count = STATIC_SYMBOL("OUTSTANDING-ISO-646-COUNT",
	    AB_package);
    Qiso_646_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-646-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_14 = STATIC_STRING("1q83jAy8s83-awy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_646_count);
    push_optimized_constant(Qiso_646_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_iso_646s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-646S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_646s,
	    Chain_of_available_iso_646s);
    record_system_variable(Qchain_of_available_iso_646s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_646_count = STATIC_SYMBOL("ISO-646-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_646_count,Iso_646_count);
    record_system_variable(Qiso_646_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_646s_vector == UNBOUND)
	Chain_of_available_iso_646s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_646_structure_memory_usage,
	    STATIC_FUNCTION(iso_646_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_646_count,
	    STATIC_FUNCTION(outstanding_iso_646_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_646_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_646,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_646,
	    reclaim_structure_for_iso_646_1);
    Qansi3_dot_4 = STATIC_SYMBOL("ANSI3.4",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qiso_646_irv,Qascii,
	    Qus_ascii,Qansi3_dot_4);
    array_constant_1 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qiso_646,make_iso_646_1(),Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop;
  end_loop:;
    Qmap_code_to_unicode = STATIC_SYMBOL("MAP-CODE-TO-UNICODE",AB_package);
    map_code_to_unicode_for_iso_646_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_iso_646,NIL,FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qiso_646,
	    map_code_to_unicode_for_iso_646_1);
    Qmap_unicode_to_code_if_any = 
	    STATIC_SYMBOL("MAP-UNICODE-TO-CODE-IF-ANY",AB_package);
    map_unicode_to_code_if_any_for_iso_646_1 = 
	    STATIC_FUNCTION(map_unicode_to_code_if_any_for_iso_646,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qmap_unicode_to_code_if_any,Qiso_646,
	    map_unicode_to_code_if_any_for_iso_646_1);
    Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-ABSTRACT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qiso_8859_abstract = STATIC_SYMBOL("ISO-8859-ABSTRACT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct,
	    Qiso_8859_abstract,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_abstract,
	    Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_abstract == UNBOUND)
	The_type_description_of_iso_8859_abstract = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83=9y1o83=9y83*Fy8n8k1l83*Fy0000001l1r8x83*Fy1m83*Qy1m9k83=9y1m83*Sy1m9k01m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k0kuk0k0");
    temp = The_type_description_of_iso_8859_abstract;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_abstract = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_abstract_g2_struct,
	    The_type_description_of_iso_8859_abstract,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_abstract,
	    The_type_description_of_iso_8859_abstract,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_abstract_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-ABSTRACT-COUNT",AB_package);
    Qiso_8859_abstract_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-ABSTRACT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_16 = STATIC_STRING("1q83=9y8s83-b5y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_abstract_count);
    push_optimized_constant(Qiso_8859_abstract_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_iso_8859_abstracts = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-ABSTRACTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_abstracts,
	    Chain_of_available_iso_8859_abstracts);
    record_system_variable(Qchain_of_available_iso_8859_abstracts,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qiso_8859_abstract_count = STATIC_SYMBOL("ISO-8859-ABSTRACT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_abstract_count,
	    Iso_8859_abstract_count);
    record_system_variable(Qiso_8859_abstract_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_abstracts_vector == UNBOUND)
	Chain_of_available_iso_8859_abstracts_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_abstract_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_abstract_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_abstract_count,
	    STATIC_FUNCTION(outstanding_iso_8859_abstract_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_iso_8859_abstract_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_abstract,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_abstract,
	    reclaim_structure_for_iso_8859_abstract_1);
    mutate_global_property(Qiso_8859_abstract,make_iso_8859_abstract_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = Qnil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_abstract),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_1;
  end_loop_1:;
    map_code_to_unicode_for_iso_8859_abstract_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_iso_8859_abstract,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qiso_8859_abstract,
	    map_code_to_unicode_for_iso_8859_abstract_1);
    Qavailable_8859_reverse_unicode_map_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_8859_reverse_unicode_map_hash_vector_43_vectors,
	    Available_8859_reverse_unicode_map_hash_vector_43_vectors);
    record_system_variable(Qavailable_8859_reverse_unicode_map_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_8859_reverse_unicode_map_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_8859_reverse_unicode_map_hash_vector_43_vectors,
	    Count_of_8859_reverse_unicode_map_hash_vector_43_vectors);
    record_system_variable(Qcount_of_8859_reverse_unicode_map_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector 
	    == UNBOUND)
	Available_8859_reverse_unicode_map_hash_vector_43_vectors_vector = 
		make_thread_array(Nil);
    Qout_8859_reverse_unicode_map_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Q8859_reverse_unicode_map_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_17 = STATIC_STRING("1q83-IZy83*9y83-Oly09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_8859_reverse_unicode_map_hash_vector_43_vectors);
    push_optimized_constant(Q8859_reverse_unicode_map_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    SET_SYMBOL_FUNCTION(Q8859_reverse_unicode_map_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(n_8859_reverse_unicode_map_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_8859_reverse_unicode_map_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_8859_reverse_unicode_map_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Q8859_reverse_unicode_map_tree_for_hash = 
	    STATIC_SYMBOL("8859-REVERSE-UNICODE-MAP-TREE-FOR-HASH",AB_package);
    map_unicode_to_code_if_any_for_iso_8859_abstract_1 = 
	    STATIC_FUNCTION(map_unicode_to_code_if_any_for_iso_8859_abstract,
	    NIL,FALSE,2,2);
    record_direct_structure_method(Qmap_unicode_to_code_if_any,
	    Qiso_8859_abstract,
	    map_unicode_to_code_if_any_for_iso_8859_abstract_1);
    Qg2_defstruct_structure_name_iso_8859_1_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-1-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_1_g2_struct,
	    Qiso_8859_1,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_1,
	    Qg2_defstruct_structure_name_iso_8859_1_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_1 == UNBOUND)
	The_type_description_of_iso_8859_1 = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m83jBy1p83jBy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jBy1m83*Sy1m9k1l83kIy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_19 = STATIC_STRING("+s3--ykkkkkl3A++y1m83=Xylkuk0k0");
    temp = The_type_description_of_iso_8859_1;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_1 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_18,
	    string_constant_19)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_1_g2_struct,
	    The_type_description_of_iso_8859_1,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_1,The_type_description_of_iso_8859_1,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_1_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-1-COUNT",AB_package);
    Qiso_8859_1_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-1-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_20 = STATIC_STRING("1q83jBy8s83-axy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_1_count);
    push_optimized_constant(Qiso_8859_1_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_20));
    Qchain_of_available_iso_8859_1s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-1S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_1s,
	    Chain_of_available_iso_8859_1s);
    record_system_variable(Qchain_of_available_iso_8859_1s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_1_count = STATIC_SYMBOL("ISO-8859-1-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_1_count,Iso_8859_1_count);
    record_system_variable(Qiso_8859_1_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_1s_vector == UNBOUND)
	Chain_of_available_iso_8859_1s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_1_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_1_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_1_count,
	    STATIC_FUNCTION(outstanding_iso_8859_1_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_1_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_1,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_1,
	    reclaim_structure_for_iso_8859_1_1);
    Qlatin_1 = STATIC_SYMBOL("LATIN-1",AB_package);
    list_constant_2 = STATIC_CONS(Qlatin_1,Qnil);
    mutate_global_property(Qiso_8859_1,make_iso_8859_1_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_2;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_1),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_2;
  end_loop_2:;
    Qg2_defstruct_structure_name_iso_8859_2_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-2-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_2_g2_struct,
	    Qiso_8859_2,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_2,
	    Qg2_defstruct_structure_name_iso_8859_2_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_2 == UNBOUND)
	The_type_description_of_iso_8859_2 = Nil;
    string_constant_21 = 
	    STATIC_STRING("43Dy8m83jDy1p83jDy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jDy1m83*Sy1m9k1l83kJy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_22 = STATIC_STRING("+s3-*ykkkkkl3A++y1m83=Xymkuk0k0");
    temp = The_type_description_of_iso_8859_2;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_2 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_21,
	    string_constant_22)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_2_g2_struct,
	    The_type_description_of_iso_8859_2,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_2,The_type_description_of_iso_8859_2,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_2_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-2-COUNT",AB_package);
    Qiso_8859_2_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-2-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_23 = STATIC_STRING("1q83jDy8s83-b-y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_2_count);
    push_optimized_constant(Qiso_8859_2_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    Qchain_of_available_iso_8859_2s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-2S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_2s,
	    Chain_of_available_iso_8859_2s);
    record_system_variable(Qchain_of_available_iso_8859_2s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_2_count = STATIC_SYMBOL("ISO-8859-2-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_2_count,Iso_8859_2_count);
    record_system_variable(Qiso_8859_2_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_2s_vector == UNBOUND)
	Chain_of_available_iso_8859_2s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_2_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_2_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_2_count,
	    STATIC_FUNCTION(outstanding_iso_8859_2_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_2_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_2,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_2,
	    reclaim_structure_for_iso_8859_2_1);
    Qlatin_2 = STATIC_SYMBOL("LATIN-2",AB_package);
    list_constant_3 = STATIC_CONS(Qlatin_2,Qnil);
    mutate_global_property(Qiso_8859_2,make_iso_8859_2_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_3;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_2),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_3;
  end_loop_3:;
    Qg2_defstruct_structure_name_iso_8859_3_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-3-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_3_g2_struct,
	    Qiso_8859_3,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_3,
	    Qg2_defstruct_structure_name_iso_8859_3_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_3 == UNBOUND)
	The_type_description_of_iso_8859_3 = Nil;
    string_constant_24 = 
	    STATIC_STRING("43Dy8m83jEy1p83jEy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jEy1m83*Sy1m9k1l83kKy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_25 = STATIC_STRING("+s3-=ykkkkkl3A++y1m83=Xynkuk0k0");
    temp = The_type_description_of_iso_8859_3;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_3 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_24,
	    string_constant_25)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_3_g2_struct,
	    The_type_description_of_iso_8859_3,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_3,The_type_description_of_iso_8859_3,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_3_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-3-COUNT",AB_package);
    Qiso_8859_3_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-3-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_26 = STATIC_STRING("1q83jEy8s83-b*y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_3_count);
    push_optimized_constant(Qiso_8859_3_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_26));
    Qchain_of_available_iso_8859_3s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-3S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_3s,
	    Chain_of_available_iso_8859_3s);
    record_system_variable(Qchain_of_available_iso_8859_3s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_3_count = STATIC_SYMBOL("ISO-8859-3-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_3_count,Iso_8859_3_count);
    record_system_variable(Qiso_8859_3_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_3s_vector == UNBOUND)
	Chain_of_available_iso_8859_3s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_3_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_3_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_3_count,
	    STATIC_FUNCTION(outstanding_iso_8859_3_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_3_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_3,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_3,
	    reclaim_structure_for_iso_8859_3_1);
    Qlatin_3 = STATIC_SYMBOL("LATIN-3",AB_package);
    list_constant_4 = STATIC_CONS(Qlatin_3,Qnil);
    array_constant_2 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qiso_8859_3,make_iso_8859_3_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_4;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_3),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_4;
  end_loop_4:;
    Qg2_defstruct_structure_name_iso_8859_4_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-4-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_4_g2_struct,
	    Qiso_8859_4,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_4,
	    Qg2_defstruct_structure_name_iso_8859_4_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_4 == UNBOUND)
	The_type_description_of_iso_8859_4 = Nil;
    string_constant_27 = 
	    STATIC_STRING("43Dy8m83jFy1p83jFy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jFy1m83*Sy1m9k1l83kLy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_28 = STATIC_STRING("+s3-0ykkkkkl3A++y1m83=Xyokuk0k0");
    temp = The_type_description_of_iso_8859_4;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_4 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_27,
	    string_constant_28)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_4_g2_struct,
	    The_type_description_of_iso_8859_4,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_4,The_type_description_of_iso_8859_4,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_4_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-4-COUNT",AB_package);
    Qiso_8859_4_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-4-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_29 = STATIC_STRING("1q83jFy8s83-b=y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_4_count);
    push_optimized_constant(Qiso_8859_4_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_29));
    Qchain_of_available_iso_8859_4s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-4S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_4s,
	    Chain_of_available_iso_8859_4s);
    record_system_variable(Qchain_of_available_iso_8859_4s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_4_count = STATIC_SYMBOL("ISO-8859-4-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_4_count,Iso_8859_4_count);
    record_system_variable(Qiso_8859_4_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_4s_vector == UNBOUND)
	Chain_of_available_iso_8859_4s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_4_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_4_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_4_count,
	    STATIC_FUNCTION(outstanding_iso_8859_4_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_4_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_4,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_4,
	    reclaim_structure_for_iso_8859_4_1);
    Qlatin_4 = STATIC_SYMBOL("LATIN-4",AB_package);
    list_constant_5 = STATIC_CONS(Qlatin_4,Qnil);
    array_constant_3 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qiso_8859_4,make_iso_8859_4_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_5;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_4),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_5;
  end_loop_5:;
    Qg2_defstruct_structure_name_iso_8859_5_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-5-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_5_g2_struct,
	    Qiso_8859_5,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_5,
	    Qg2_defstruct_structure_name_iso_8859_5_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_5 == UNBOUND)
	The_type_description_of_iso_8859_5 = Nil;
    string_constant_30 = 
	    STATIC_STRING("43Dy8m83jGy1p83jGy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jGy1m83*Sy1m9k1l83kPy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_31 = STATIC_STRING("+s3-8ykkkkkl3A++y1m83=Xypkuk0k0");
    temp = The_type_description_of_iso_8859_5;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_5 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_30,
	    string_constant_31)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_5_g2_struct,
	    The_type_description_of_iso_8859_5,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_5,The_type_description_of_iso_8859_5,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_5_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-5-COUNT",AB_package);
    Qiso_8859_5_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-5-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_32 = STATIC_STRING("1q83jGy8s83-b0y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_5_count);
    push_optimized_constant(Qiso_8859_5_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_32));
    Qchain_of_available_iso_8859_5s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-5S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_5s,
	    Chain_of_available_iso_8859_5s);
    record_system_variable(Qchain_of_available_iso_8859_5s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_5_count = STATIC_SYMBOL("ISO-8859-5-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_5_count,Iso_8859_5_count);
    record_system_variable(Qiso_8859_5_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_5s_vector == UNBOUND)
	Chain_of_available_iso_8859_5s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_5_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_5_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_5_count,
	    STATIC_FUNCTION(outstanding_iso_8859_5_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_5_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_5,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_5,
	    reclaim_structure_for_iso_8859_5_1);
    Qlatin_cyrillic = STATIC_SYMBOL("LATIN-CYRILLIC",AB_package);
    list_constant_6 = STATIC_CONS(Qlatin_cyrillic,Qnil);
    array_constant_4 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qiso_8859_5,make_iso_8859_5_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_6;
  next_loop_6:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_6;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_5),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_6;
  end_loop_6:;
    Qg2_defstruct_structure_name_iso_8859_6_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-6-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_6_g2_struct,
	    Qiso_8859_6,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_6,
	    Qg2_defstruct_structure_name_iso_8859_6_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_6 == UNBOUND)
	The_type_description_of_iso_8859_6 = Nil;
    string_constant_33 = 
	    STATIC_STRING("43Dy8m83jHy1p83jHy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jHy1m83*Sy1m9k1l83kOy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_34 = STATIC_STRING("+s3-3ykkkkkl3A++y1m83=Xyqkuk0k0");
    temp = The_type_description_of_iso_8859_6;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_6 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_33,
	    string_constant_34)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_6_g2_struct,
	    The_type_description_of_iso_8859_6,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_6,The_type_description_of_iso_8859_6,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_6_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-6-COUNT",AB_package);
    Qiso_8859_6_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-6-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_35 = STATIC_STRING("1q83jHy8s83-b1y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_6_count);
    push_optimized_constant(Qiso_8859_6_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_35));
    Qchain_of_available_iso_8859_6s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-6S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_6s,
	    Chain_of_available_iso_8859_6s);
    record_system_variable(Qchain_of_available_iso_8859_6s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_6_count = STATIC_SYMBOL("ISO-8859-6-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_6_count,Iso_8859_6_count);
    record_system_variable(Qiso_8859_6_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_6s_vector == UNBOUND)
	Chain_of_available_iso_8859_6s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_6_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_6_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_6_count,
	    STATIC_FUNCTION(outstanding_iso_8859_6_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_6_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_6,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_6,
	    reclaim_structure_for_iso_8859_6_1);
    Qlatin_arabic = STATIC_SYMBOL("LATIN-ARABIC",AB_package);
    list_constant_7 = STATIC_CONS(Qlatin_arabic,Qnil);
    array_constant_5 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qiso_8859_6,make_iso_8859_6_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_7;
  next_loop_7:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_7;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_6),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_7;
  end_loop_7:;
    Qg2_defstruct_structure_name_iso_8859_7_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-7-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_7_g2_struct,
	    Qiso_8859_7,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_7,
	    Qg2_defstruct_structure_name_iso_8859_7_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_7 == UNBOUND)
	The_type_description_of_iso_8859_7 = Nil;
    string_constant_36 = 
	    STATIC_STRING("43Dy8m83jIy1p83jIy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jIy1m83*Sy1m9k1l83kQy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_37 = STATIC_STRING("+s3-2ykkkkkl3A++y1m83=Xyrkuk0k0");
    temp = The_type_description_of_iso_8859_7;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_7 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_36,
	    string_constant_37)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_7_g2_struct,
	    The_type_description_of_iso_8859_7,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_7,The_type_description_of_iso_8859_7,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_7_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-7-COUNT",AB_package);
    Qiso_8859_7_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-7-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_38 = STATIC_STRING("1q83jIy8s83-b2y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_7_count);
    push_optimized_constant(Qiso_8859_7_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_38));
    Qchain_of_available_iso_8859_7s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-7S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_7s,
	    Chain_of_available_iso_8859_7s);
    record_system_variable(Qchain_of_available_iso_8859_7s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_7_count = STATIC_SYMBOL("ISO-8859-7-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_7_count,Iso_8859_7_count);
    record_system_variable(Qiso_8859_7_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_7s_vector == UNBOUND)
	Chain_of_available_iso_8859_7s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_7_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_7_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_7_count,
	    STATIC_FUNCTION(outstanding_iso_8859_7_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_7_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_7,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_7,
	    reclaim_structure_for_iso_8859_7_1);
    Qlatin_greek = STATIC_SYMBOL("LATIN-GREEK",AB_package);
    list_constant_8 = STATIC_CONS(Qlatin_greek,Qnil);
    array_constant_6 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qiso_8859_7,make_iso_8859_7_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_8;
  next_loop_8:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_8;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_7),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_8;
  end_loop_8:;
    Qg2_defstruct_structure_name_iso_8859_8_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-8-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_8_g2_struct,
	    Qiso_8859_8,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_8,
	    Qg2_defstruct_structure_name_iso_8859_8_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_8 == UNBOUND)
	The_type_description_of_iso_8859_8 = Nil;
    string_constant_39 = 
	    STATIC_STRING("43Dy8m83jJy1p83jJy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jJy1m83*Sy1m9k1l83kRy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_40 = STATIC_STRING("+s3-4ykkkkkl3A++y1m83=Xyskuk0k0");
    temp = The_type_description_of_iso_8859_8;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_8 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_39,
	    string_constant_40)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_8_g2_struct,
	    The_type_description_of_iso_8859_8,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_8,The_type_description_of_iso_8859_8,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_8_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-8-COUNT",AB_package);
    Qiso_8859_8_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-8-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_41 = STATIC_STRING("1q83jJy8s83-b3y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_8_count);
    push_optimized_constant(Qiso_8859_8_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_41));
    Qchain_of_available_iso_8859_8s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-8S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_8s,
	    Chain_of_available_iso_8859_8s);
    record_system_variable(Qchain_of_available_iso_8859_8s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_8_count = STATIC_SYMBOL("ISO-8859-8-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_8_count,Iso_8859_8_count);
    record_system_variable(Qiso_8859_8_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_8s_vector == UNBOUND)
	Chain_of_available_iso_8859_8s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_8_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_8_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_8_count,
	    STATIC_FUNCTION(outstanding_iso_8859_8_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_8_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_8,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_8,
	    reclaim_structure_for_iso_8859_8_1);
    Qlatin_hebrew = STATIC_SYMBOL("LATIN-HEBREW",AB_package);
    list_constant_9 = STATIC_CONS(Qlatin_hebrew,Qnil);
    array_constant_7 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qiso_8859_8,make_iso_8859_8_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_9;
  next_loop_9:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_9;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_8),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_9;
  end_loop_9:;
    Qg2_defstruct_structure_name_iso_8859_9_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-9-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_9_g2_struct,
	    Qiso_8859_9,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_9,
	    Qg2_defstruct_structure_name_iso_8859_9_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_9 == UNBOUND)
	The_type_description_of_iso_8859_9 = Nil;
    string_constant_42 = 
	    STATIC_STRING("43Dy8m83jKy1p83jKy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jKy1m83*Sy1m9k1l83kMy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_43 = STATIC_STRING("+s3-9ykkkkkl3A++y1m83=Xytkuk0k0");
    temp = The_type_description_of_iso_8859_9;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_9 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_42,
	    string_constant_43)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_9_g2_struct,
	    The_type_description_of_iso_8859_9,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_9,The_type_description_of_iso_8859_9,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_9_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-9-COUNT",AB_package);
    Qiso_8859_9_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-9-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_44 = STATIC_STRING("1q83jKy8s83-b4y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_9_count);
    push_optimized_constant(Qiso_8859_9_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_44));
    Qchain_of_available_iso_8859_9s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-9S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_9s,
	    Chain_of_available_iso_8859_9s);
    record_system_variable(Qchain_of_available_iso_8859_9s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qiso_8859_9_count = STATIC_SYMBOL("ISO-8859-9-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_9_count,Iso_8859_9_count);
    record_system_variable(Qiso_8859_9_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_9s_vector == UNBOUND)
	Chain_of_available_iso_8859_9s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_9_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_9_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_9_count,
	    STATIC_FUNCTION(outstanding_iso_8859_9_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_9_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_9,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_9,
	    reclaim_structure_for_iso_8859_9_1);
    Qlatin_5 = STATIC_SYMBOL("LATIN-5",AB_package);
    list_constant_10 = STATIC_CONS(Qlatin_5,Qnil);
    array_constant_8 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qiso_8859_9,make_iso_8859_9_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_10;
  next_loop_10:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_10;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_9),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_10;
  end_loop_10:;
    Qg2_defstruct_structure_name_iso_8859_10_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-10-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_10_g2_struct,
	    Qiso_8859_10,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_10,
	    Qg2_defstruct_structure_name_iso_8859_10_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_10 == UNBOUND)
	The_type_description_of_iso_8859_10 = Nil;
    string_constant_45 = 
	    STATIC_STRING("43Dy8m83jCy1p83jCy83=9y83*Fy8n8k1l83=9y0000001l1s8x83=9y1m83*Qy1m9k83jCy1m83*Sy1m9k1l83kNy1m83*Py1m9kl1m83*Oy1m9k3-Sy1m83*Ry1m9k");
    string_constant_46 = STATIC_STRING("+s3-0ykkkkkl3A++y1m83=Xyukuk0k0");
    temp = The_type_description_of_iso_8859_10;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_iso_8859_10 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_45,
	    string_constant_46)));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_10_g2_struct,
	    The_type_description_of_iso_8859_10,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_10,
	    The_type_description_of_iso_8859_10,Qtype_description_of_type);
    Qoutstanding_iso_8859_10_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-10-COUNT",AB_package);
    Qiso_8859_10_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-10-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_47 = STATIC_STRING("1q83jCy8s83-b+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_10_count);
    push_optimized_constant(Qiso_8859_10_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_47));
    Qchain_of_available_iso_8859_10s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-10S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_10s,
	    Chain_of_available_iso_8859_10s);
    record_system_variable(Qchain_of_available_iso_8859_10s,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qiso_8859_10_count = STATIC_SYMBOL("ISO-8859-10-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_10_count,Iso_8859_10_count);
    record_system_variable(Qiso_8859_10_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_10s_vector == UNBOUND)
	Chain_of_available_iso_8859_10s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_10_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_10_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_10_count,
	    STATIC_FUNCTION(outstanding_iso_8859_10_count,NIL,FALSE,0,0));
    reclaim_structure_for_iso_8859_10_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_10,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_10,
	    reclaim_structure_for_iso_8859_10_1);
    Qlatin_6 = STATIC_SYMBOL("LATIN-6",AB_package);
    list_constant_11 = STATIC_CONS(Qlatin_6,Qnil);
    mutate_global_property(Qiso_8859_10,make_iso_8859_10_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_11;
  next_loop_11:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_11;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_10),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_11;
  end_loop_11:;
    Qg2_defstruct_structure_name_asian_double_byte_g2_struct = 
	    STATIC_SYMBOL("ASIAN-DOUBLE-BYTE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qasian_double_byte = STATIC_SYMBOL("ASIAN-DOUBLE-BYTE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_asian_double_byte_g2_struct,
	    Qasian_double_byte,Qab_name_of_unique_structure_type);
    mutate_global_property(Qasian_double_byte,
	    Qg2_defstruct_structure_name_asian_double_byte_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_asian_double_byte == UNBOUND)
	The_type_description_of_asian_double_byte = Nil;
    string_constant_48 = 
	    STATIC_STRING("43Dy8m833fy1o833fy83*Fy8n8k1l83*Fy0000001l1r8x83*Fy1m83*Qy1m9k833fy1m83*Sy1m9k01m83*Py1m9km1m83*Oy1m9k3-Qy1m83*Ry1m9k0ksk0k0");
    temp = The_type_description_of_asian_double_byte;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_asian_double_byte = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_48));
    mutate_global_property(Qg2_defstruct_structure_name_asian_double_byte_g2_struct,
	    The_type_description_of_asian_double_byte,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qasian_double_byte,
	    The_type_description_of_asian_double_byte,
	    Qtype_description_of_type);
    Qoutstanding_asian_double_byte_count = 
	    STATIC_SYMBOL("OUTSTANDING-ASIAN-DOUBLE-BYTE-COUNT",AB_package);
    Qasian_double_byte_structure_memory_usage = 
	    STATIC_SYMBOL("ASIAN-DOUBLE-BYTE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_49 = STATIC_STRING("1q833fy8s83-Jqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_asian_double_byte_count);
    push_optimized_constant(Qasian_double_byte_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_49));
    Qchain_of_available_asian_double_bytes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ASIAN-DOUBLE-BYTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_asian_double_bytes,
	    Chain_of_available_asian_double_bytes);
    record_system_variable(Qchain_of_available_asian_double_bytes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qasian_double_byte_count = STATIC_SYMBOL("ASIAN-DOUBLE-BYTE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qasian_double_byte_count,
	    Asian_double_byte_count);
    record_system_variable(Qasian_double_byte_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_asian_double_bytes_vector == UNBOUND)
	Chain_of_available_asian_double_bytes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qasian_double_byte_structure_memory_usage,
	    STATIC_FUNCTION(asian_double_byte_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_asian_double_byte_count,
	    STATIC_FUNCTION(outstanding_asian_double_byte_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_asian_double_byte_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_asian_double_byte,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qasian_double_byte,
	    reclaim_structure_for_asian_double_byte_1);
    mutate_global_property(Qasian_double_byte,make_asian_double_byte_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = Qnil;
  next_loop_12:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_12;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qasian_double_byte),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_12;
  end_loop_12:;
    map_code_to_unicode_for_asian_double_byte_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_asian_double_byte,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qasian_double_byte,
	    map_code_to_unicode_for_asian_double_byte_1);
    Qg2_defstruct_structure_name_jis_x_0208_g2_struct = 
	    STATIC_SYMBOL("JIS-X-0208-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_jis_x_0208_g2_struct,
	    Qjis_x_0208,Qab_name_of_unique_structure_type);
    mutate_global_property(Qjis_x_0208,
	    Qg2_defstruct_structure_name_jis_x_0208_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_jis_x_0208 == UNBOUND)
	The_type_description_of_jis_x_0208 = Nil;
    string_constant_50 = 
	    STATIC_STRING("43Dy8m83k7y1p83k7y833fy83*Fy8n8k1l833fy0000001l1r8x833fy1m83*Qy1m9k83k7y1m83*Sy1m9k1l83k6y1m83*Py1m9km1m83*Oy1m9k3-Qy1m83*Ry1m9k");
    string_constant_51 = STATIC_STRING("+s3-*ykkkkkl3A++yksk0k0");
    temp = The_type_description_of_jis_x_0208;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_jis_x_0208 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_50,
	    string_constant_51)));
    mutate_global_property(Qg2_defstruct_structure_name_jis_x_0208_g2_struct,
	    The_type_description_of_jis_x_0208,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qjis_x_0208,The_type_description_of_jis_x_0208,
	    Qtype_description_of_type);
    Qoutstanding_jis_x_0208_count = 
	    STATIC_SYMBOL("OUTSTANDING-JIS-X-0208-COUNT",AB_package);
    Qjis_x_0208_structure_memory_usage = 
	    STATIC_SYMBOL("JIS-X-0208-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_52 = STATIC_STRING("1q83k7y8s83-bby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_jis_x_0208_count);
    push_optimized_constant(Qjis_x_0208_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_52));
    Qchain_of_available_jis_x_0208s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JIS-X-0208S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_jis_x_0208s,
	    Chain_of_available_jis_x_0208s);
    record_system_variable(Qchain_of_available_jis_x_0208s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qjis_x_0208_count = STATIC_SYMBOL("JIS-X-0208-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjis_x_0208_count,Jis_x_0208_count);
    record_system_variable(Qjis_x_0208_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_jis_x_0208s_vector == UNBOUND)
	Chain_of_available_jis_x_0208s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjis_x_0208_structure_memory_usage,
	    STATIC_FUNCTION(jis_x_0208_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_jis_x_0208_count,
	    STATIC_FUNCTION(outstanding_jis_x_0208_count,NIL,FALSE,0,0));
    reclaim_structure_for_jis_x_0208_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_jis_x_0208,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qjis_x_0208,
	    reclaim_structure_for_jis_x_0208_1);
    Qjis = STATIC_SYMBOL("JIS",AB_package);
    list_constant_12 = STATIC_CONS(Qjis,Qnil);
    mutate_global_property(Qjis_x_0208,make_jis_x_0208_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_12;
  next_loop_13:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_13;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_13;
  end_loop_13:;
    map_code_to_unicode_for_jis_x_0208_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_jis_x_0208,NIL,FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qjis_x_0208,
	    map_code_to_unicode_for_jis_x_0208_1);
    map_unicode_to_code_if_any_for_jis_x_0208_1 = 
	    STATIC_FUNCTION(map_unicode_to_code_if_any_for_jis_x_0208,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qmap_unicode_to_code_if_any,Qjis_x_0208,
	    map_unicode_to_code_if_any_for_jis_x_0208_1);
    Qg2_defstruct_structure_name_ks_c_5601_g2_struct = 
	    STATIC_SYMBOL("KS-C-5601-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_ks_c_5601_g2_struct,
	    Qks_c_5601,Qab_name_of_unique_structure_type);
    mutate_global_property(Qks_c_5601,
	    Qg2_defstruct_structure_name_ks_c_5601_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_ks_c_5601 == UNBOUND)
	The_type_description_of_ks_c_5601 = Nil;
    string_constant_53 = 
	    STATIC_STRING("43Dy8m83kEy1p83kEy833fy83*Fy8n8k1l833fy0000001l1r8x833fy1m83*Qy1m9k83kEy1m83*Sy1m9k1m83-1ky83kFy1m83*Py1m9km1m83*Oy1m9k3-Qy1m83*");
    string_constant_54 = STATIC_STRING("Ry1m9k+s3-=ykkkkkl3A++yksk0k0");
    temp = The_type_description_of_ks_c_5601;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_ks_c_5601 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_53,
	    string_constant_54)));
    mutate_global_property(Qg2_defstruct_structure_name_ks_c_5601_g2_struct,
	    The_type_description_of_ks_c_5601,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qks_c_5601,The_type_description_of_ks_c_5601,
	    Qtype_description_of_type);
    Qoutstanding_ks_c_5601_count = 
	    STATIC_SYMBOL("OUTSTANDING-KS-C-5601-COUNT",AB_package);
    Qks_c_5601_structure_memory_usage = 
	    STATIC_SYMBOL("KS-C-5601-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_55 = STATIC_STRING("1q83kEy8s83-c7y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_ks_c_5601_count);
    push_optimized_constant(Qks_c_5601_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_55));
    Qchain_of_available_ks_c_5601s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-KS-C-5601S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_ks_c_5601s,
	    Chain_of_available_ks_c_5601s);
    record_system_variable(Qchain_of_available_ks_c_5601s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qks_c_5601_count = STATIC_SYMBOL("KS-C-5601-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qks_c_5601_count,Ks_c_5601_count);
    record_system_variable(Qks_c_5601_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_ks_c_5601s_vector == UNBOUND)
	Chain_of_available_ks_c_5601s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qks_c_5601_structure_memory_usage,
	    STATIC_FUNCTION(ks_c_5601_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_ks_c_5601_count,
	    STATIC_FUNCTION(outstanding_ks_c_5601_count,NIL,FALSE,0,0));
    reclaim_structure_for_ks_c_5601_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_ks_c_5601,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qks_c_5601,
	    reclaim_structure_for_ks_c_5601_1);
    Qks = STATIC_SYMBOL("KS",AB_package);
    Qksc = STATIC_SYMBOL("KSC",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qks,Qksc);
    mutate_global_property(Qks_c_5601,make_ks_c_5601_1(),
	    Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_13;
  next_loop_14:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_14;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_14;
  end_loop_14:;
    map_code_to_unicode_for_ks_c_5601_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_ks_c_5601,NIL,FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qks_c_5601,
	    map_code_to_unicode_for_ks_c_5601_1);
    map_unicode_to_code_if_any_for_ks_c_5601_1 = 
	    STATIC_FUNCTION(map_unicode_to_code_if_any_for_ks_c_5601,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qmap_unicode_to_code_if_any,Qks_c_5601,
	    map_unicode_to_code_if_any_for_ks_c_5601_1);
    Qg2_defstruct_structure_name_gb_2312_g2_struct = 
	    STATIC_SYMBOL("GB-2312-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_gb_2312_g2_struct,
	    Qgb_2312,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgb_2312,
	    Qg2_defstruct_structure_name_gb_2312_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gb_2312 == UNBOUND)
	The_type_description_of_gb_2312 = Nil;
    string_constant_56 = 
	    STATIC_STRING("43Dy8m83Pry1p83Pry833fy83*Fy8n8k1l833fy0000001l1r8x833fy1m83*Qy1m9k83Pry1m83*Sy1m9k1m83-+fy83-+gy1m83*Py1m9km1m83*Oy1m9k3-Qy1m83");
    string_constant_57 = STATIC_STRING("*Ry1m9k+s3-=ykkkkkl3A++yksk0k0");
    temp = The_type_description_of_gb_2312;
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    The_type_description_of_gb_2312 = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_56,
	    string_constant_57)));
    mutate_global_property(Qg2_defstruct_structure_name_gb_2312_g2_struct,
	    The_type_description_of_gb_2312,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgb_2312,The_type_description_of_gb_2312,
	    Qtype_description_of_type);
    Qoutstanding_gb_2312_count = STATIC_SYMBOL("OUTSTANDING-GB-2312-COUNT",
	    AB_package);
    Qgb_2312_structure_memory_usage = 
	    STATIC_SYMBOL("GB-2312-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_58 = STATIC_STRING("1q83Pry8s83-W2y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gb_2312_count);
    push_optimized_constant(Qgb_2312_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_58));
    Qchain_of_available_gb_2312s = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GB-2312S",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gb_2312s,
	    Chain_of_available_gb_2312s);
    record_system_variable(Qchain_of_available_gb_2312s,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qgb_2312_count = STATIC_SYMBOL("GB-2312-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgb_2312_count,Gb_2312_count);
    record_system_variable(Qgb_2312_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gb_2312s_vector == UNBOUND)
	Chain_of_available_gb_2312s_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgb_2312_structure_memory_usage,
	    STATIC_FUNCTION(gb_2312_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gb_2312_count,
	    STATIC_FUNCTION(outstanding_gb_2312_count,NIL,FALSE,0,0));
    reclaim_structure_for_gb_2312_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gb_2312,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgb_2312,
	    reclaim_structure_for_gb_2312_1);
    Qgb = STATIC_SYMBOL("GB",AB_package);
    Qgb2312 = STATIC_SYMBOL("GB2312",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qgb,Qgb2312);
    mutate_global_property(Qgb_2312,make_gb_2312_1(),Qgraphic_character_set);
    synonym = Nil;
    ab_loop_list_ = list_constant_14;
  next_loop_15:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_15;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = synonym;
    mutate_global_property(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set),Qgraphic_character_set);
    goto next_loop_15;
  end_loop_15:;
    map_code_to_unicode_for_gb_2312_1 = 
	    STATIC_FUNCTION(map_code_to_unicode_for_gb_2312,NIL,FALSE,2,2);
    record_direct_structure_method(Qmap_code_to_unicode,Qgb_2312,
	    map_code_to_unicode_for_gb_2312_1);
    map_unicode_to_code_if_any_for_gb_2312_1 = 
	    STATIC_FUNCTION(map_unicode_to_code_if_any_for_gb_2312,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qmap_unicode_to_code_if_any,Qgb_2312,
	    map_unicode_to_code_if_any_for_gb_2312_1);
    Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct = 
	    STATIC_SYMBOL("ISO-8859-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qiso_8859_transcoder = STATIC_SYMBOL("ISO-8859-TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct,
	    Qiso_8859_transcoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_8859_transcoder,
	    Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_8859_transcoder == UNBOUND)
	The_type_description_of_iso_8859_transcoder = Nil;
    string_constant_59 = 
	    STATIC_STRING("43Dy8m83jLy1o83jLy83=Ey8n8k1l83=Ey0000001m1m8x83=Ey1n8y83-4fy1m83-=uy83-=tyksk0k0");
    temp = The_type_description_of_iso_8859_transcoder;
    The_type_description_of_iso_8859_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_59));
    mutate_global_property(Qg2_defstruct_structure_name_iso_8859_transcoder_g2_struct,
	    The_type_description_of_iso_8859_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_8859_transcoder,
	    The_type_description_of_iso_8859_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_iso_8859_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-8859-TRANSCODER-COUNT",AB_package);
    Qiso_8859_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-8859-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_60 = STATIC_STRING("1q83jLy8s83-b6y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_8859_transcoder_count);
    push_optimized_constant(Qiso_8859_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_60));
    Qchain_of_available_iso_8859_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-8859-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_8859_transcoders,
	    Chain_of_available_iso_8859_transcoders);
    record_system_variable(Qchain_of_available_iso_8859_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qiso_8859_transcoder_count = STATIC_SYMBOL("ISO-8859-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_8859_transcoder_count,
	    Iso_8859_transcoder_count);
    record_system_variable(Qiso_8859_transcoder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_8859_transcoders_vector == UNBOUND)
	Chain_of_available_iso_8859_transcoders_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_8859_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(iso_8859_transcoder_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_8859_transcoder_count,
	    STATIC_FUNCTION(outstanding_iso_8859_transcoder_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_iso_8859_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_8859_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_8859_transcoder,
	    reclaim_structure_for_iso_8859_transcoder_1);
    transcode_character_for_iso_8859_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_iso_8859_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,
	    Qiso_8859_transcoder,
	    transcode_character_for_iso_8859_transcoder_1);
    Qdos = STATIC_SYMBOL("DOS",AB_package);
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    Qcr = STATIC_SYMBOL("CR",AB_package);
    Qunicode_line_separator = STATIC_SYMBOL("UNICODE-LINE-SEPARATOR",
	    AB_package);
    Qunicode_paragraph_separator = 
	    STATIC_SYMBOL("UNICODE-PARAGRAPH-SEPARATOR",AB_package);
    export_character_for_iso_8859_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_iso_8859_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qexport_character,Qiso_8859_transcoder,
	    export_character_for_iso_8859_transcoder_1);
    Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct = 
	    STATIC_SYMBOL("ISO-2022-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qiso_2022_transcoder = STATIC_SYMBOL("ISO-2022-TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct,
	    Qiso_2022_transcoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qiso_2022_transcoder,
	    Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_iso_2022_transcoder == UNBOUND)
	The_type_description_of_iso_2022_transcoder = Nil;
    string_constant_61 = 
	    STATIC_STRING("43Dy8m83j9y1o83j9y83=Ey8n8k1l83=Ey0000001l1m8x83=Eykyk0k0");
    temp = The_type_description_of_iso_2022_transcoder;
    The_type_description_of_iso_2022_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_61));
    mutate_global_property(Qg2_defstruct_structure_name_iso_2022_transcoder_g2_struct,
	    The_type_description_of_iso_2022_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qiso_2022_transcoder,
	    The_type_description_of_iso_2022_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_iso_2022_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-ISO-2022-TRANSCODER-COUNT",AB_package);
    Qiso_2022_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("ISO-2022-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_62 = STATIC_STRING("1q83j9y8s83-avy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_iso_2022_transcoder_count);
    push_optimized_constant(Qiso_2022_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_62));
    Qchain_of_available_iso_2022_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ISO-2022-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_iso_2022_transcoders,
	    Chain_of_available_iso_2022_transcoders);
    record_system_variable(Qchain_of_available_iso_2022_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qiso_2022_transcoder_count = STATIC_SYMBOL("ISO-2022-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qiso_2022_transcoder_count,
	    Iso_2022_transcoder_count);
    record_system_variable(Qiso_2022_transcoder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_iso_2022_transcoders_vector == UNBOUND)
	Chain_of_available_iso_2022_transcoders_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qiso_2022_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(iso_2022_transcoder_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_iso_2022_transcoder_count,
	    STATIC_FUNCTION(outstanding_iso_2022_transcoder_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_iso_2022_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_iso_2022_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qiso_2022_transcoder,
	    reclaim_structure_for_iso_2022_transcoder_1);
    Qcreate_transcoder_for_iso_646 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-646",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_646,
	    STATIC_FUNCTION(create_transcoder_for_iso_646,NIL,FALSE,0,0));
    mutate_global_property(Qiso_646,Qcreate_transcoder_for_iso_646,
	    Qtranscoder_creation_function);
    list_constant_21 = STATIC_CONS(Qansi3_dot_4,Qnil);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)4L,Qus_ascii,Qiso_646_irv,
	    Qascii,list_constant_21);
    synonym = Nil;
    ab_loop_list_ = list_constant_22;
  next_loop_16:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_16;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_646,
	    Qtranscoder_creation_function);
    goto next_loop_16;
  end_loop_16:;
    Qiso_2022 = STATIC_SYMBOL("ISO-2022",AB_package);
    Qcreate_transcoder_for_iso_2022 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-2022",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_2022,
	    STATIC_FUNCTION(create_transcoder_for_iso_2022,NIL,FALSE,0,0));
    mutate_global_property(Qiso_2022,Qcreate_transcoder_for_iso_2022,
	    Qtranscoder_creation_function);
    list_constant_23 = STATIC_CONS(Qx_compound_text,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_23;
  next_loop_17:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_17;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_2022,
	    Qtranscoder_creation_function);
    goto next_loop_17;
  end_loop_17:;
    Qcreate_transcoder_for_jis_x_0208 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-JIS-X-0208",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_jis_x_0208,
	    STATIC_FUNCTION(create_transcoder_for_jis_x_0208,NIL,FALSE,0,0));
    mutate_global_property(Qjis_x_0208,Qcreate_transcoder_for_jis_x_0208,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_12;
  next_loop_18:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_18;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_jis_x_0208,
	    Qtranscoder_creation_function);
    goto next_loop_18;
  end_loop_18:;
    Qcreate_transcoder_for_jis_x_0208_euc = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-JIS-X-0208-EUC",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_jis_x_0208_euc,
	    STATIC_FUNCTION(create_transcoder_for_jis_x_0208_euc,NIL,FALSE,
	    0,0));
    mutate_global_property(Qjis_x_0208_euc,
	    Qcreate_transcoder_for_jis_x_0208_euc,
	    Qtranscoder_creation_function);
    Qjis_euc = STATIC_SYMBOL("JIS-EUC",AB_package);
    list_constant_24 = STATIC_CONS(Qjis_euc,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_24;
  next_loop_19:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_19;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_jis_x_0208_euc,
	    Qtranscoder_creation_function);
    goto next_loop_19;
  end_loop_19:;
    Qcreate_transcoder_for_shift_jis_x_0208 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-SHIFT-JIS-X-0208",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_shift_jis_x_0208,
	    STATIC_FUNCTION(create_transcoder_for_shift_jis_x_0208,NIL,
	    FALSE,0,0));
    mutate_global_property(Qshift_jis_x_0208,
	    Qcreate_transcoder_for_shift_jis_x_0208,
	    Qtranscoder_creation_function);
    Qms_kanji = STATIC_SYMBOL("MS-KANJI",AB_package);
    Qshift_jis = STATIC_SYMBOL("SHIFT-JIS",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qms_kanji,Qshift_jis);
    synonym = Nil;
    ab_loop_list_ = list_constant_25;
  next_loop_20:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_20;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_shift_jis_x_0208,
	    Qtranscoder_creation_function);
    goto next_loop_20;
  end_loop_20:;
    Qcreate_transcoder_for_ks_c_5601 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-KS-C-5601",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_ks_c_5601,
	    STATIC_FUNCTION(create_transcoder_for_ks_c_5601,NIL,FALSE,0,0));
    mutate_global_property(Qks_c_5601,Qcreate_transcoder_for_ks_c_5601,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_13;
  next_loop_21:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_21;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_ks_c_5601,
	    Qtranscoder_creation_function);
    goto next_loop_21;
  end_loop_21:;
    Qcreate_transcoder_for_ks_c_5601_euc = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-KS-C-5601-EUC",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_ks_c_5601_euc,
	    STATIC_FUNCTION(create_transcoder_for_ks_c_5601_euc,NIL,FALSE,
	    0,0));
    mutate_global_property(Qks_c_5601_euc,
	    Qcreate_transcoder_for_ks_c_5601_euc,
	    Qtranscoder_creation_function);
    Qks_euc = STATIC_SYMBOL("KS-EUC",AB_package);
    Qksc_euc = STATIC_SYMBOL("KSC-EUC",AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qks_euc,Qksc_euc);
    synonym = Nil;
    ab_loop_list_ = list_constant_26;
  next_loop_22:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_22;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_ks_c_5601_euc,
	    Qtranscoder_creation_function);
    goto next_loop_22;
  end_loop_22:;
    Qcreate_transcoder_for_gb_2312 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-GB-2312",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_gb_2312,
	    STATIC_FUNCTION(create_transcoder_for_gb_2312,NIL,FALSE,0,0));
    mutate_global_property(Qgb_2312,Qcreate_transcoder_for_gb_2312,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_14;
  next_loop_23:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_23;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_gb_2312,
	    Qtranscoder_creation_function);
    goto next_loop_23;
  end_loop_23:;
    Qcreate_transcoder_for_gb_2312_euc = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-GB-2312-EUC",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_gb_2312_euc,
	    STATIC_FUNCTION(create_transcoder_for_gb_2312_euc,NIL,FALSE,0,0));
    mutate_global_property(Qgb_2312_euc,Qcreate_transcoder_for_gb_2312_euc,
	    Qtranscoder_creation_function);
    Qgb_euc = STATIC_SYMBOL("GB-EUC",AB_package);
    Qgb2312_euc = STATIC_SYMBOL("GB2312-EUC",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qgb_euc,Qgb2312_euc);
    synonym = Nil;
    ab_loop_list_ = list_constant_27;
  next_loop_24:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_24;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_gb_2312_euc,
	    Qtranscoder_creation_function);
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
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
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
    list_constant_28 = STATIC_CONS(Qleft,Qnil);
    list_constant_29 = STATIC_CONS(Qright,Qnil);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    temp_2 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_1),
	    Qgraphic_character_set);
    temp_3 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_2),
	    Qgraphic_character_set);
    temp_4 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_3),
	    Qgraphic_character_set);
    temp_5 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_4),
	    Qgraphic_character_set);
    temp_6 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_5),
	    Qgraphic_character_set);
    temp_7 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_6),
	    Qgraphic_character_set);
    temp_8 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_7),
	    Qgraphic_character_set);
    temp_9 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_8),
	    Qgraphic_character_set);
    temp_10 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_8859_9),
	    Qgraphic_character_set);
    temp_11 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set);
    No_han_x_compound_text_character_set_selection_list = list(13,
	    CONS(temp_1,list_constant_28),CONS(temp_2,list_constant_29),
	    CONS(temp_3,list_constant_29),CONS(temp_4,list_constant_29),
	    CONS(temp_5,list_constant_29),CONS(temp_6,list_constant_29),
	    CONS(temp_7,list_constant_29),CONS(temp_8,list_constant_29),
	    CONS(temp_9,list_constant_29),CONS(temp_10,list_constant_29),
	    CONS(temp_11,list_constant_28),CONS(temp_12,list_constant_28),
	    CONS(temp,list_constant_28));
    temp_10 = No_han_x_compound_text_character_set_selection_list;
    temp_11 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set);
    Japanese_han_x_compound_text_character_set_selection_list = 
	    append2(temp_10,LIST_3(CONS(temp_11,list_constant_28),
	    CONS(temp_12,list_constant_28),CONS(temp,list_constant_28)));
    temp_10 = No_han_x_compound_text_character_set_selection_list;
    temp_11 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set);
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set);
    Korean_han_x_compound_text_character_set_selection_list = 
	    append2(temp_10,LIST_3(CONS(temp_11,list_constant_28),
	    CONS(temp_12,list_constant_28),CONS(temp,list_constant_28)));
    temp_10 = No_han_x_compound_text_character_set_selection_list;
    temp_11 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set);
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set);
    Chinese_han_x_compound_text_character_set_selection_list = 
	    append2(temp_10,LIST_3(CONS(temp_11,list_constant_28),
	    CONS(temp_12,list_constant_28),CONS(temp,list_constant_28)));
    Default_han_x_compound_text_character_set_selection_list = 
	    Japanese_han_x_compound_text_character_set_selection_list;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    Us_ascii_character_set_selection_list = LIST_1(CONS(temp,
	    list_constant_28));
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set);
    Ks_c_5601_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_28));
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qks_c_5601),
	    Qgraphic_character_set);
    Ks_c_5601_euc_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_29));
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set);
    Gb_2312_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_28));
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgb_2312),
	    Qgraphic_character_set);
    Gb_2312_euc_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_29));
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    Jis_x_0208_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_28));
    temp_12 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qiso_646),
	    Qgraphic_character_set);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjis_x_0208),
	    Qgraphic_character_set);
    Jis_x_0208_euc_character_set_selection_list = LIST_2(CONS(temp_12,
	    list_constant_28),CONS(temp,list_constant_29));
    Qgl = STATIC_SYMBOL("GL",AB_package);
    Qgr = STATIC_SYMBOL("GR",AB_package);
    transcode_character_for_iso_2022_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_iso_2022_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,
	    Qiso_2022_transcoder,
	    transcode_character_for_iso_2022_transcoder_1);
    export_character_for_iso_2022_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_iso_2022_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qexport_character,Qiso_2022_transcoder,
	    export_character_for_iso_2022_transcoder_1);
    Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct = 
	    STATIC_SYMBOL("SHIFT-JIS-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qshift_jis_transcoder = STATIC_SYMBOL("SHIFT-JIS-TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct,
	    Qshift_jis_transcoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qshift_jis_transcoder,
	    Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_shift_jis_transcoder == UNBOUND)
	The_type_description_of_shift_jis_transcoder = Nil;
    string_constant_63 = 
	    STATIC_STRING("43Dy8m83mpy1o83mpy83=Ey8n8k1l83=Ey0000001l1m8x83=Eykrk0k0");
    temp = The_type_description_of_shift_jis_transcoder;
    The_type_description_of_shift_jis_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_63));
    mutate_global_property(Qg2_defstruct_structure_name_shift_jis_transcoder_g2_struct,
	    The_type_description_of_shift_jis_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qshift_jis_transcoder,
	    The_type_description_of_shift_jis_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_shift_jis_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-SHIFT-JIS-TRANSCODER-COUNT",AB_package);
    Qshift_jis_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("SHIFT-JIS-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_64 = STATIC_STRING("1q83mpy8s83-oZy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_shift_jis_transcoder_count);
    push_optimized_constant(Qshift_jis_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_64));
    Qchain_of_available_shift_jis_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SHIFT-JIS-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_shift_jis_transcoders,
	    Chain_of_available_shift_jis_transcoders);
    record_system_variable(Qchain_of_available_shift_jis_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qshift_jis_transcoder_count = 
	    STATIC_SYMBOL("SHIFT-JIS-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshift_jis_transcoder_count,
	    Shift_jis_transcoder_count);
    record_system_variable(Qshift_jis_transcoder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_shift_jis_transcoders_vector == UNBOUND)
	Chain_of_available_shift_jis_transcoders_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qshift_jis_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(shift_jis_transcoder_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_shift_jis_transcoder_count,
	    STATIC_FUNCTION(outstanding_shift_jis_transcoder_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_shift_jis_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_shift_jis_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qshift_jis_transcoder,
	    reclaim_structure_for_shift_jis_transcoder_1);
    transcode_character_for_shift_jis_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_shift_jis_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,
	    Qshift_jis_transcoder,
	    transcode_character_for_shift_jis_transcoder_1);
    export_character_for_shift_jis_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_shift_jis_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qexport_character,Qshift_jis_transcoder,
	    export_character_for_shift_jis_transcoder_1);
    Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct = 
	    STATIC_SYMBOL("UTF-G-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qutf_g_transcoder = STATIC_SYMBOL("UTF-G-TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct,
	    Qutf_g_transcoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qutf_g_transcoder,
	    Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_utf_g_transcoder == UNBOUND)
	The_type_description_of_utf_g_transcoder = Nil;
    string_constant_65 = 
	    STATIC_STRING("43Dy8m83Fny1o83Fny83=Ey8n8k1l83=Ey0000001l1m8x83=Eyksk0k0");
    temp = The_type_description_of_utf_g_transcoder;
    The_type_description_of_utf_g_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_65));
    mutate_global_property(Qg2_defstruct_structure_name_utf_g_transcoder_g2_struct,
	    The_type_description_of_utf_g_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qutf_g_transcoder,
	    The_type_description_of_utf_g_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_utf_g_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-UTF-G-TRANSCODER-COUNT",AB_package);
    Qutf_g_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("UTF-G-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_66 = STATIC_STRING("1q83Fny8s83-vxy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_utf_g_transcoder_count);
    push_optimized_constant(Qutf_g_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_66));
    Qchain_of_available_utf_g_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UTF-G-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_utf_g_transcoders,
	    Chain_of_available_utf_g_transcoders);
    record_system_variable(Qchain_of_available_utf_g_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qutf_g_transcoder_count = STATIC_SYMBOL("UTF-G-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qutf_g_transcoder_count,Utf_g_transcoder_count);
    record_system_variable(Qutf_g_transcoder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_utf_g_transcoders_vector == UNBOUND)
	Chain_of_available_utf_g_transcoders_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qutf_g_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(utf_g_transcoder_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_utf_g_transcoder_count,
	    STATIC_FUNCTION(outstanding_utf_g_transcoder_count,NIL,FALSE,0,0));
    reclaim_structure_for_utf_g_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_utf_g_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qutf_g_transcoder,
	    reclaim_structure_for_utf_g_transcoder_1);
    transcode_character_for_utf_g_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_utf_g_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,Qutf_g_transcoder,
	    transcode_character_for_utf_g_transcoder_1);
    export_character_for_utf_g_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_utf_g_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qexport_character,Qutf_g_transcoder,
	    export_character_for_utf_g_transcoder_1);
    Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct 
	    = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qutf_g_ascii_as_much_as_possible_transcoder = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct,
	    Qutf_g_ascii_as_much_as_possible_transcoder,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qutf_g_ascii_as_much_as_possible_transcoder,
	    Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_utf_g_ascii_as_much_as_possible_transcoder 
	    == UNBOUND)
	The_type_description_of_utf_g_ascii_as_much_as_possible_transcoder 
		= Nil;
    string_constant_67 = 
	    STATIC_STRING("43Dy8m83oPy1p83oPy83Fny83=Ey8n8k1l83Fny0000001l1m8x83Fnyksk0k0");
    temp = The_type_description_of_utf_g_ascii_as_much_as_possible_transcoder;
    The_type_description_of_utf_g_ascii_as_much_as_possible_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_67));
    mutate_global_property(Qg2_defstruct_structure_name_utf_g_ascii_as_much_as_possible_transcoder_g2_struct,
	    The_type_description_of_utf_g_ascii_as_much_as_possible_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qutf_g_ascii_as_much_as_possible_transcoder,
	    The_type_description_of_utf_g_ascii_as_much_as_possible_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_utf_g_ascii_as_much_as_possible_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-COUNT",
	    AB_package);
    Qutf_g_ascii_as_much_as_possible_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_68 = STATIC_STRING("1q83oPy8s83-vwy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_utf_g_ascii_as_much_as_possible_transcoder_count);
    push_optimized_constant(Qutf_g_ascii_as_much_as_possible_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_68));
    Qchain_of_available_utf_g_ascii_as_much_as_possible_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_utf_g_ascii_as_much_as_possible_transcoders,
	    Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders);
    record_system_variable(Qchain_of_available_utf_g_ascii_as_much_as_possible_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qutf_g_ascii_as_much_as_possible_transcoder_count = 
	    STATIC_SYMBOL("UTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qutf_g_ascii_as_much_as_possible_transcoder_count,
	    Utf_g_ascii_as_much_as_possible_transcoder_count);
    record_system_variable(Qutf_g_ascii_as_much_as_possible_transcoder_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector 
	    == UNBOUND)
	Chain_of_available_utf_g_ascii_as_much_as_possible_transcoders_vector 
		= make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qutf_g_ascii_as_much_as_possible_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(utf_g_ascii_as_much_as_possible_transcoder_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_utf_g_ascii_as_much_as_possible_transcoder_count,
	    STATIC_FUNCTION(outstanding_utf_g_ascii_as_much_as_possible_transcoder_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qutf_g_ascii_as_much_as_possible_transcoder,
	    reclaim_structure_for_utf_g_ascii_as_much_as_possible_transcoder_1);
    export_character_for_utf_g_ascii_as_much_as_possible_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_utf_g_ascii_as_much_as_possible_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_character,
	    Qutf_g_ascii_as_much_as_possible_transcoder,
	    export_character_for_utf_g_ascii_as_much_as_possible_transcoder_1);
    Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct = 
	    STATIC_SYMBOL("UNICODE-UCS-2-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qunicode_ucs_2_transcoder = STATIC_SYMBOL("UNICODE-UCS-2-TRANSCODER",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct,
	    Qunicode_ucs_2_transcoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qunicode_ucs_2_transcoder,
	    Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_unicode_ucs_2_transcoder == UNBOUND)
	The_type_description_of_unicode_ucs_2_transcoder = Nil;
    string_constant_69 = 
	    STATIC_STRING("43Dy8m83oAy1o83oAy83=Ey8n8k1l83=Ey0000001l1m8x83=Eyksk0k0");
    temp = The_type_description_of_unicode_ucs_2_transcoder;
    The_type_description_of_unicode_ucs_2_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_69));
    mutate_global_property(Qg2_defstruct_structure_name_unicode_ucs_2_transcoder_g2_struct,
	    The_type_description_of_unicode_ucs_2_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qunicode_ucs_2_transcoder,
	    The_type_description_of_unicode_ucs_2_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_unicode_ucs_2_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-UNICODE-UCS-2-TRANSCODER-COUNT",
	    AB_package);
    Qunicode_ucs_2_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("UNICODE-UCS-2-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_70 = STATIC_STRING("1q83oAy8s83-uwy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_unicode_ucs_2_transcoder_count);
    push_optimized_constant(Qunicode_ucs_2_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_70));
    Qchain_of_available_unicode_ucs_2_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNICODE-UCS-2-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_unicode_ucs_2_transcoders,
	    Chain_of_available_unicode_ucs_2_transcoders);
    record_system_variable(Qchain_of_available_unicode_ucs_2_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qunicode_ucs_2_transcoder_count = 
	    STATIC_SYMBOL("UNICODE-UCS-2-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qunicode_ucs_2_transcoder_count,
	    Unicode_ucs_2_transcoder_count);
    record_system_variable(Qunicode_ucs_2_transcoder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_unicode_ucs_2_transcoders_vector == UNBOUND)
	Chain_of_available_unicode_ucs_2_transcoders_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qunicode_ucs_2_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(unicode_ucs_2_transcoder_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_unicode_ucs_2_transcoder_count,
	    STATIC_FUNCTION(outstanding_unicode_ucs_2_transcoder_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_unicode_ucs_2_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_unicode_ucs_2_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qunicode_ucs_2_transcoder,
	    reclaim_structure_for_unicode_ucs_2_transcoder_1);
    transcode_character_for_unicode_ucs_2_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_unicode_ucs_2_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,
	    Qunicode_ucs_2_transcoder,
	    transcode_character_for_unicode_ucs_2_transcoder_1);
    export_character_for_unicode_ucs_2_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_unicode_ucs_2_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_character,
	    Qunicode_ucs_2_transcoder,
	    export_character_for_unicode_ucs_2_transcoder_1);
    Qg2_defstruct_structure_name_unicode_transcoder_g2_struct = 
	    STATIC_SYMBOL("UNICODE-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qunicode_transcoder = STATIC_SYMBOL("UNICODE-TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_unicode_transcoder_g2_struct,
	    Qunicode_transcoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qunicode_transcoder,
	    Qg2_defstruct_structure_name_unicode_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_unicode_transcoder == UNBOUND)
	The_type_description_of_unicode_transcoder = Nil;
    string_constant_71 = 
	    STATIC_STRING("43Dy8m83o9y1o83o9y83=Ey8n8k1l83=Ey0000001l1m8x83=Eykqk0k0");
    temp = The_type_description_of_unicode_transcoder;
    The_type_description_of_unicode_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_71));
    mutate_global_property(Qg2_defstruct_structure_name_unicode_transcoder_g2_struct,
	    The_type_description_of_unicode_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qunicode_transcoder,
	    The_type_description_of_unicode_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_unicode_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-UNICODE-TRANSCODER-COUNT",AB_package);
    Qunicode_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("UNICODE-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_72 = STATIC_STRING("1q83o9y8s83-uty09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_unicode_transcoder_count);
    push_optimized_constant(Qunicode_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_72));
    Qchain_of_available_unicode_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNICODE-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_unicode_transcoders,
	    Chain_of_available_unicode_transcoders);
    record_system_variable(Qchain_of_available_unicode_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qunicode_transcoder_count = STATIC_SYMBOL("UNICODE-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qunicode_transcoder_count,
	    Unicode_transcoder_count);
    record_system_variable(Qunicode_transcoder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_unicode_transcoders_vector == UNBOUND)
	Chain_of_available_unicode_transcoders_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qunicode_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(unicode_transcoder_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_unicode_transcoder_count,
	    STATIC_FUNCTION(outstanding_unicode_transcoder_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_unicode_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_unicode_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qunicode_transcoder,
	    reclaim_structure_for_unicode_transcoder_1);
    transcode_character_for_unicode_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_unicode_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,
	    Qunicode_transcoder,transcode_character_for_unicode_transcoder_1);
    export_character_for_unicode_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_unicode_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qexport_character,Qunicode_transcoder,
	    export_character_for_unicode_transcoder_1);
    Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct 
	    = STATIC_SYMBOL("UNICODE-BYTE-SWAPPED-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qunicode_byte_swapped_transcoder = 
	    STATIC_SYMBOL("UNICODE-BYTE-SWAPPED-TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct,
	    Qunicode_byte_swapped_transcoder,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qunicode_byte_swapped_transcoder,
	    Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_unicode_byte_swapped_transcoder == UNBOUND)
	The_type_description_of_unicode_byte_swapped_transcoder = Nil;
    string_constant_73 = 
	    STATIC_STRING("43Dy8m83o8y1o83o8y83=Ey8n8k1l83=Ey0000001l1m8x83=Eykqk0k0");
    temp = The_type_description_of_unicode_byte_swapped_transcoder;
    The_type_description_of_unicode_byte_swapped_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_73));
    mutate_global_property(Qg2_defstruct_structure_name_unicode_byte_swapped_transcoder_g2_struct,
	    The_type_description_of_unicode_byte_swapped_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qunicode_byte_swapped_transcoder,
	    The_type_description_of_unicode_byte_swapped_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_unicode_byte_swapped_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-UNICODE-BYTE-SWAPPED-TRANSCODER-COUNT",
	    AB_package);
    Qunicode_byte_swapped_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("UNICODE-BYTE-SWAPPED-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_74 = STATIC_STRING("1q83o8y8s83-uqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_unicode_byte_swapped_transcoder_count);
    push_optimized_constant(Qunicode_byte_swapped_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_74));
    Qchain_of_available_unicode_byte_swapped_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNICODE-BYTE-SWAPPED-TRANSCODERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_unicode_byte_swapped_transcoders,
	    Chain_of_available_unicode_byte_swapped_transcoders);
    record_system_variable(Qchain_of_available_unicode_byte_swapped_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qunicode_byte_swapped_transcoder_count = 
	    STATIC_SYMBOL("UNICODE-BYTE-SWAPPED-TRANSCODER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qunicode_byte_swapped_transcoder_count,
	    Unicode_byte_swapped_transcoder_count);
    record_system_variable(Qunicode_byte_swapped_transcoder_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_unicode_byte_swapped_transcoders_vector == UNBOUND)
	Chain_of_available_unicode_byte_swapped_transcoders_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qunicode_byte_swapped_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(unicode_byte_swapped_transcoder_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_unicode_byte_swapped_transcoder_count,
	    STATIC_FUNCTION(outstanding_unicode_byte_swapped_transcoder_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_unicode_byte_swapped_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_unicode_byte_swapped_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qunicode_byte_swapped_transcoder,
	    reclaim_structure_for_unicode_byte_swapped_transcoder_1);
    transcode_character_for_unicode_byte_swapped_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_unicode_byte_swapped_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,
	    Qunicode_byte_swapped_transcoder,
	    transcode_character_for_unicode_byte_swapped_transcoder_1);
    export_character_for_unicode_byte_swapped_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_unicode_byte_swapped_transcoder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_character,
	    Qunicode_byte_swapped_transcoder,
	    export_character_for_unicode_byte_swapped_transcoder_1);
    Qcreate_transcoder_for_iso_8859_1 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-1",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_1,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_1,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_1,Qcreate_transcoder_for_iso_8859_1,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_2;
  next_loop_25:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_25;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_1,
	    Qtranscoder_creation_function);
    goto next_loop_25;
  end_loop_25:;
    Qcreate_transcoder_for_iso_8859_2 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-2",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_2,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_2,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_2,Qcreate_transcoder_for_iso_8859_2,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_3;
  next_loop_26:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_26;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_2,
	    Qtranscoder_creation_function);
    goto next_loop_26;
  end_loop_26:;
    Qcreate_transcoder_for_iso_8859_3 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-3",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_3,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_3,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_3,Qcreate_transcoder_for_iso_8859_3,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_4;
  next_loop_27:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_27;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_3,
	    Qtranscoder_creation_function);
    goto next_loop_27;
  end_loop_27:;
    Qcreate_transcoder_for_iso_8859_4 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-4",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_4,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_4,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_4,Qcreate_transcoder_for_iso_8859_4,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_5;
  next_loop_28:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_28;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_4,
	    Qtranscoder_creation_function);
    goto next_loop_28;
  end_loop_28:;
    Qcreate_transcoder_for_iso_8859_5 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-5",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_5,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_5,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_5,Qcreate_transcoder_for_iso_8859_5,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_6;
  next_loop_29:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_29;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_5,
	    Qtranscoder_creation_function);
    goto next_loop_29;
  end_loop_29:;
    Qcreate_transcoder_for_iso_8859_6 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-6",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_6,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_6,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_6,Qcreate_transcoder_for_iso_8859_6,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_7;
  next_loop_30:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_30;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_6,
	    Qtranscoder_creation_function);
    goto next_loop_30;
  end_loop_30:;
    Qcreate_transcoder_for_iso_8859_7 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-7",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_7,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_7,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_7,Qcreate_transcoder_for_iso_8859_7,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_8;
  next_loop_31:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_31;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_7,
	    Qtranscoder_creation_function);
    goto next_loop_31;
  end_loop_31:;
    Qcreate_transcoder_for_iso_8859_8 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-8",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_8,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_8,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_8,Qcreate_transcoder_for_iso_8859_8,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_9;
  next_loop_32:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_32;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_8,
	    Qtranscoder_creation_function);
    goto next_loop_32;
  end_loop_32:;
    Qcreate_transcoder_for_iso_8859_9 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-9",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_9,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_9,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_9,Qcreate_transcoder_for_iso_8859_9,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_10;
  next_loop_33:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_33;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_9,
	    Qtranscoder_creation_function);
    goto next_loop_33;
  end_loop_33:;
    Qcreate_transcoder_for_iso_8859_10 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-ISO-8859-10",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_iso_8859_10,
	    STATIC_FUNCTION(create_transcoder_for_iso_8859_10,NIL,FALSE,0,0));
    mutate_global_property(Qiso_8859_10,Qcreate_transcoder_for_iso_8859_10,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = list_constant_11;
  next_loop_34:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_34;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_iso_8859_10,
	    Qtranscoder_creation_function);
    goto next_loop_34;
  end_loop_34:;
    Qcreate_transcoder_for_gensym = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-GENSYM",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_gensym,
	    STATIC_FUNCTION(create_transcoder_for_gensym,NIL,FALSE,0,0));
    mutate_global_property(Qab_gensym,Qcreate_transcoder_for_gensym,
	    Qtranscoder_creation_function);
    list_constant_30 = STATIC_CONS(Qutf_g,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_30;
  next_loop_35:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_35;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_gensym,
	    Qtranscoder_creation_function);
    goto next_loop_35;
  end_loop_35:;
    Qgensym_with_ascii_as_much_as_possible = 
	    STATIC_SYMBOL("GENSYM-WITH-ASCII-AS-MUCH-AS-POSSIBLE",AB_package);
    Qcreate_transcoder_for_gensym_with_ascii_as_much_as_possible = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-GENSYM-WITH-ASCII-AS-MUCH-AS-POSSIBLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_gensym_with_ascii_as_much_as_possible,
	    STATIC_FUNCTION(create_transcoder_for_gensym_with_ascii_as_much_as_possible,
	    NIL,FALSE,0,0));
    mutate_global_property(Qgensym_with_ascii_as_much_as_possible,
	    Qcreate_transcoder_for_gensym_with_ascii_as_much_as_possible,
	    Qtranscoder_creation_function);
    list_constant_31 = STATIC_CONS(Qutf_g_ascii_as_much_as_possible,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_31;
  next_loop_36:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_36;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,
	    Qcreate_transcoder_for_gensym_with_ascii_as_much_as_possible,
	    Qtranscoder_creation_function);
    goto next_loop_36;
  end_loop_36:;
    Qunicode_ucs_2 = STATIC_SYMBOL("UNICODE-UCS-2",AB_package);
    Qcreate_transcoder_for_unicode_ucs_2 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-UCS-2",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_unicode_ucs_2,
	    STATIC_FUNCTION(create_transcoder_for_unicode_ucs_2,NIL,FALSE,
	    0,0));
    mutate_global_property(Qunicode_ucs_2,
	    Qcreate_transcoder_for_unicode_ucs_2,
	    Qtranscoder_creation_function);
    Qiso_10646_ucs_2 = STATIC_SYMBOL("ISO-10646-UCS-2",AB_package);
    list_constant_32 = STATIC_CONS(Qiso_10646_ucs_2,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_32;
  next_loop_37:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_37;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_unicode_ucs_2,
	    Qtranscoder_creation_function);
    goto next_loop_37;
  end_loop_37:;
    Qunicode_ucs_2_byte_swapped = 
	    STATIC_SYMBOL("UNICODE-UCS-2-BYTE-SWAPPED",AB_package);
    Qcreate_transcoder_for_unicode_ucs_2_byte_swapped = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-UCS-2-BYTE-SWAPPED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_unicode_ucs_2_byte_swapped,
	    STATIC_FUNCTION(create_transcoder_for_unicode_ucs_2_byte_swapped,
	    NIL,FALSE,0,0));
    mutate_global_property(Qunicode_ucs_2_byte_swapped,
	    Qcreate_transcoder_for_unicode_ucs_2_byte_swapped,
	    Qtranscoder_creation_function);
    synonym = Nil;
    ab_loop_list_ = Qnil;
  next_loop_38:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_38;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,
	    Qcreate_transcoder_for_unicode_ucs_2_byte_swapped,
	    Qtranscoder_creation_function);
    goto next_loop_38;
  end_loop_38:;
    Qcreate_transcoder_for_unicode = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_unicode,
	    STATIC_FUNCTION(create_transcoder_for_unicode,NIL,FALSE,0,0));
    mutate_global_property(Qunicode,Qcreate_transcoder_for_unicode,
	    Qtranscoder_creation_function);
    Qiso_10646 = STATIC_SYMBOL("ISO-10646",AB_package);
    list_constant_33 = STATIC_CONS(Qiso_10646,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_33;
  next_loop_39:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_39;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_unicode,
	    Qtranscoder_creation_function);
    goto next_loop_39;
  end_loop_39:;
    Qunicode_byte_swapped = STATIC_SYMBOL("UNICODE-BYTE-SWAPPED",AB_package);
    Qcreate_transcoder_for_unicode_byte_swapped = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-BYTE-SWAPPED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_unicode_byte_swapped,
	    STATIC_FUNCTION(create_transcoder_for_unicode_byte_swapped,NIL,
	    FALSE,0,0));
    mutate_global_property(Qunicode_byte_swapped,
	    Qcreate_transcoder_for_unicode_byte_swapped,
	    Qtranscoder_creation_function);
    Qiso_10646_byte_swapped = STATIC_SYMBOL("ISO-10646-BYTE-SWAPPED",
	    AB_package);
    list_constant_34 = STATIC_CONS(Qiso_10646_byte_swapped,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_34;
  next_loop_40:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_40;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,
	    Qcreate_transcoder_for_unicode_byte_swapped,
	    Qtranscoder_creation_function);
    goto next_loop_40;
  end_loop_40:;
    string_constant_75 = 
	    STATIC_STRING("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    Utf_7_modified_base64_characters = stringw(string_constant_75);
    Utf_7_ultraconservative_p = Nil;
    Utf_7_delimit_encoded_sequences_p = T;
    Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct = 
	    STATIC_SYMBOL("UTF-7-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qutf_7_transcoder = STATIC_SYMBOL("UTF-7-TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct,
	    Qutf_7_transcoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qutf_7_transcoder,
	    Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_utf_7_transcoder == UNBOUND)
	The_type_description_of_utf_7_transcoder = Nil;
    string_constant_76 = 
	    STATIC_STRING("43Dy8m83oNy1o83oNy83=Ey8n8k1l83=Ey0000001l1m8x83=Eykqk0k0");
    temp = The_type_description_of_utf_7_transcoder;
    The_type_description_of_utf_7_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_76));
    mutate_global_property(Qg2_defstruct_structure_name_utf_7_transcoder_g2_struct,
	    The_type_description_of_utf_7_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qutf_7_transcoder,
	    The_type_description_of_utf_7_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_utf_7_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-UTF-7-TRANSCODER-COUNT",AB_package);
    Qutf_7_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("UTF-7-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_77 = STATIC_STRING("1q83oNy8s83-vuy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_utf_7_transcoder_count);
    push_optimized_constant(Qutf_7_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_77));
    Qchain_of_available_utf_7_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UTF-7-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_utf_7_transcoders,
	    Chain_of_available_utf_7_transcoders);
    record_system_variable(Qchain_of_available_utf_7_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qutf_7_transcoder_count = STATIC_SYMBOL("UTF-7-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qutf_7_transcoder_count,Utf_7_transcoder_count);
    record_system_variable(Qutf_7_transcoder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_utf_7_transcoders_vector == UNBOUND)
	Chain_of_available_utf_7_transcoders_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qutf_7_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(utf_7_transcoder_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_utf_7_transcoder_count,
	    STATIC_FUNCTION(outstanding_utf_7_transcoder_count,NIL,FALSE,0,0));
    reclaim_structure_for_utf_7_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_utf_7_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qutf_7_transcoder,
	    reclaim_structure_for_utf_7_transcoder_1);
    Qcreate_transcoder_for_unicode_utf_7 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-UTF-7",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_unicode_utf_7,
	    STATIC_FUNCTION(create_transcoder_for_unicode_utf_7,NIL,FALSE,
	    0,0));
    mutate_global_property(Qunicode_utf_7,
	    Qcreate_transcoder_for_unicode_utf_7,
	    Qtranscoder_creation_function);
    Qutf_7 = STATIC_SYMBOL("UTF-7",AB_package);
    list_constant_35 = STATIC_CONS(Qutf_7,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_35;
  next_loop_41:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_41;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_unicode_utf_7,
	    Qtranscoder_creation_function);
    goto next_loop_41;
  end_loop_41:;
    transcode_character_for_utf_7_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_utf_7_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,Qutf_7_transcoder,
	    transcode_character_for_utf_7_transcoder_1);
    Qillegal_utf_7_base64_character = 
	    STATIC_SYMBOL("ILLEGAL-UTF-7-BASE64-CHARACTER",AB_package);
    Qill_formed_octet_stream_odd_number = 
	    STATIC_SYMBOL("ILL-FORMED-OCTET-STREAM-ODD-NUMBER",AB_package);
    export_character_for_utf_7_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_utf_7_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qexport_character,Qutf_7_transcoder,
	    export_character_for_utf_7_transcoder_1);
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
    if (Ucs_4_to_utf_8_1st_octet_table == UNBOUND)
	Ucs_4_to_utf_8_1st_octet_table = list_constant_39;
    Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct = 
	    STATIC_SYMBOL("UTF-8-TRANSCODER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qutf_8_transcoder = STATIC_SYMBOL("UTF-8-TRANSCODER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct,
	    Qutf_8_transcoder,Qab_name_of_unique_structure_type);
    mutate_global_property(Qutf_8_transcoder,
	    Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_utf_8_transcoder == UNBOUND)
	The_type_description_of_utf_8_transcoder = Nil;
    string_constant_78 = 
	    STATIC_STRING("43Dy8m83oOy1o83oOy83=Ey8n8k1l83=Ey0000001l1m8x83=Eykqk0k0");
    temp = The_type_description_of_utf_8_transcoder;
    The_type_description_of_utf_8_transcoder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_78));
    mutate_global_property(Qg2_defstruct_structure_name_utf_8_transcoder_g2_struct,
	    The_type_description_of_utf_8_transcoder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qutf_8_transcoder,
	    The_type_description_of_utf_8_transcoder,
	    Qtype_description_of_type);
    Qoutstanding_utf_8_transcoder_count = 
	    STATIC_SYMBOL("OUTSTANDING-UTF-8-TRANSCODER-COUNT",AB_package);
    Qutf_8_transcoder_structure_memory_usage = 
	    STATIC_SYMBOL("UTF-8-TRANSCODER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_79 = STATIC_STRING("1q83oOy8s83-vvy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_utf_8_transcoder_count);
    push_optimized_constant(Qutf_8_transcoder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_79));
    Qchain_of_available_utf_8_transcoders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UTF-8-TRANSCODERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_utf_8_transcoders,
	    Chain_of_available_utf_8_transcoders);
    record_system_variable(Qchain_of_available_utf_8_transcoders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qutf_8_transcoder_count = STATIC_SYMBOL("UTF-8-TRANSCODER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qutf_8_transcoder_count,Utf_8_transcoder_count);
    record_system_variable(Qutf_8_transcoder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_utf_8_transcoders_vector == UNBOUND)
	Chain_of_available_utf_8_transcoders_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qutf_8_transcoder_structure_memory_usage,
	    STATIC_FUNCTION(utf_8_transcoder_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_utf_8_transcoder_count,
	    STATIC_FUNCTION(outstanding_utf_8_transcoder_count,NIL,FALSE,0,0));
    reclaim_structure_for_utf_8_transcoder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_utf_8_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qutf_8_transcoder,
	    reclaim_structure_for_utf_8_transcoder_1);
    Qcreate_transcoder_for_unicode_utf_8 = 
	    STATIC_SYMBOL("CREATE-TRANSCODER-FOR-UNICODE-UTF-8",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_transcoder_for_unicode_utf_8,
	    STATIC_FUNCTION(create_transcoder_for_unicode_utf_8,NIL,FALSE,
	    0,0));
    mutate_global_property(Qunicode_utf_8,
	    Qcreate_transcoder_for_unicode_utf_8,
	    Qtranscoder_creation_function);
    Qutf_8 = STATIC_SYMBOL("UTF-8",AB_package);
    list_constant_40 = STATIC_CONS(Qutf_8,Qnil);
    synonym = Nil;
    ab_loop_list_ = list_constant_40;
  next_loop_42:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_42;
    synonym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(synonym,Qcreate_transcoder_for_unicode_utf_8,
	    Qtranscoder_creation_function);
    goto next_loop_42;
  end_loop_42:;
    transcode_character_for_utf_8_transcoder_1 = 
	    STATIC_FUNCTION(transcode_character_for_utf_8_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qtranscode_character,Qutf_8_transcoder,
	    transcode_character_for_utf_8_transcoder_1);
    export_character_for_utf_8_transcoder_1 = 
	    STATIC_FUNCTION(export_character_for_utf_8_transcoder,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qexport_character,Qutf_8_transcoder,
	    export_character_for_utf_8_transcoder_1);
    if (Intern_string_buffer == UNBOUND)
	Intern_string_buffer = make_array(5,
		FIXNUM_ADD1(Intern_string_buffer_length),Kelement_type,
		Qstring_char,Kfill_pointer,FIX((SI_Long)0L));
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
    if (Standard_8_bit_non_graphic_characters_skip_spec == UNBOUND)
	Standard_8_bit_non_graphic_characters_skip_spec = list_constant_42;
}
