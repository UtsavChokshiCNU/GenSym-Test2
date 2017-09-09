/* gram2.c
 * Input file:  grammar2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram2.h"


/* SIMPLIFY-*-AND-/ */
Object simplify_star_and_sl(term)
    Object term;
{
    Object temp, item, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, item1, ab_loop_list__1, ab_loopvar__3, ab_loopvar__4;

    x_note_fn_call(195,0);
    if (ATOM(term))
	return VALUES_1(term);
    else {
	temp = CAR(term);
	if (EQ(temp,Qstar)) {
	    item = Nil;
	    ab_loop_list_ = CDR(term);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (CONSP(item) && EQ(CAR(item),Qstar)) {
		item1 = Nil;
		ab_loop_list__1 = CDR(item);
		ab_loopvar__2 = Nil;
		ab_loopvar__3 = Nil;
		ab_loopvar__4 = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		item1 = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		ab_loopvar__4 = phrase_cons(simplify_star_and_sl(item1),Nil);
		if (ab_loopvar__3)
		    M_CDR(ab_loopvar__3) = ab_loopvar__4;
		else
		    ab_loopvar__2 = ab_loopvar__4;
		ab_loopvar__3 = ab_loopvar__4;
		goto next_loop_1;
	      end_loop_1:
		goto end_1;
		ab_loopvar__2 = Qnil;
	      end_1:;
	    }
	    else if (CONSP(item) && EQ(CAR(item),Qslash))
		ab_loopvar__2 = phrase_cons(simplify_star_and_sl(item),Nil);
	    else
		ab_loopvar__2 = phrase_cons(item,Nil);
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	    goto next_loop;
	  end_loop:
	    temp = ab_loopvar_;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	    return phrase_cons(Qstar,temp);
	}
	else if (EQ(temp,Qslash)) {
	    temp = simplify_star_and_sl(SECOND(term));
	    return phrase_list_3(Qslash,temp,
		    simplify_star_and_sl(THIRD(term)));
	}
	else
	    return VALUES_1(term);
    }
}

static Object Qtoo_few_arguments;  /* too-few-arguments */

static Object Qtoo_many_arguments;  /* too-many-arguments */

static Object Qwrong_number_of_arguments;  /* wrong-number-of-arguments */

static Object Qab_structure;       /* structure */

static Object Qcall_function;      /* call-function */

/* CHECK-NUMBER-OF-ARGS */
Object check_number_of_args(function_form)
    Object function_form;
{
    Object function_name, built_in_qm, argument_range_qm, number_of_args;
    Object minimum_number_of_args_permitted, maximum_number_of_args_permitted;

    x_note_fn_call(195,1);
    function_name = CAR(function_form);
    built_in_qm = memq_function(function_name,Built_in_functions);
    argument_range_qm = 
	    lookup_global_or_kb_specific_property_value(function_name,
	    Argument_range_gkbprop);
    if (built_in_qm) {
	if (argument_range_qm) {
	    number_of_args = length(CDR(function_form));
	    minimum_number_of_args_permitted = CONSP(argument_range_qm) ? 
		    CAR(argument_range_qm) : argument_range_qm;
	    maximum_number_of_args_permitted = CONSP(argument_range_qm) ? 
		    CDR(argument_range_qm) : argument_range_qm;
	    if (FIXNUM_LT(number_of_args,minimum_number_of_args_permitted))
		return VALUES_2(Bad_phrase,Qtoo_few_arguments);
	    else if (FIXNUM_GT(number_of_args,
		    maximum_number_of_args_permitted))
		return VALUES_2(Bad_phrase,Qtoo_many_arguments);
	    else if ( !(FIXNUM_LE(minimum_number_of_args_permitted,
		    number_of_args) && FIXNUM_LE(number_of_args,
		    maximum_number_of_args_permitted)))
		return VALUES_2(Bad_phrase,Qwrong_number_of_arguments);
	    else
		return VALUES_1(function_form);
	}
	else
	    return VALUES_1(function_form);
    }
    else if (EQ(function_name,Qab_structure))
	return VALUES_1(Bad_phrase);
    else
	return phrase_cons(Qcall_function,function_form);
}

static Object Qof;                 /* of */

static Object Qat_port;            /* at-port */

static Object Qrelated;            /* related */

/* TRANSLATE-ROLE-AND-PREPOSITION */
Object translate_role_and_preposition(phrase)
    Object phrase;
{
    Object role, preposition, temp;

    x_note_fn_call(195,2);
    role = FIRST(phrase);
    preposition = SECOND(phrase);
    if (EQ(preposition,Qof))
	return VALUES_1(role);
    else if (CONSP(preposition)) {
	temp = CAR(preposition);
	if (EQ(temp,Qat_port) || EQ(temp,Qrelated))
	    return phrase_list_3(CAR(preposition),SECOND(preposition),role);
	else
	    return VALUES_1(Nil);
    }
    else
	return phrase_list_2(preposition,role);
}

/* TRANSLATE-ROLE-LOCAL-NAME-AND-PREPOSITION */
Object translate_role_local_name_and_preposition(phrase)
    Object phrase;
{
    Object role, local_name, preposition, temp;

    x_note_fn_call(195,3);
    role = FIRST(phrase);
    local_name = SECOND(phrase);
    preposition = THIRD(phrase);
    if (EQ(preposition,Qof))
	temp = role;
    else if (CONSP(preposition)) {
	temp = CAR(preposition);
	temp = EQ(temp,Qat_port) || EQ(temp,Qrelated) ? 
		phrase_list_3(CAR(preposition),SECOND(preposition),role) : Nil;
    }
    else
	temp = phrase_list_2(preposition,role);
    return phrase_cons(temp,local_name);
}

/* CONVERT-HISTORY-INTERVAL-MAYBE-CDR */
Object convert_history_interval_maybe_cdr(x)
    Object x;
{
    x_note_fn_call(195,4);
    return VALUES_1(CONSP(x) ? CDR(x) : Nil);
}

static Object Qseconds;            /* seconds */

static Object Qminute;             /* minute */

static Object Qminutes;            /* minutes */

static Object Qhour;               /* hour */

static Object Qhours;              /* hours */

static Object Qday;                /* day */

static Object Qdays;               /* days */

static Object Qweek;               /* week */

static Object Qweeks;              /* weeks */

static Object Qconvert_history_interval_maybe_cdr;  /* convert-history-interval-maybe-cdr */

/* CONVERT-HISTORY-INTERVAL */
Object convert_history_interval(form)
    Object form;
{
    Object expression, unit, gensymed_symbol, temp;

    x_note_fn_call(195,5);
    expression = FIRST(form);
    unit = SECOND(form);
    if (INTEGERP(expression)) {
	gensymed_symbol = unit;
	if (EQ(gensymed_symbol,Qnumber))
	    temp = FIX((SI_Long)1L);
	else if (EQ(gensymed_symbol,Qsecond) || EQ(gensymed_symbol,Qseconds))
	    temp = FIX((SI_Long)1L);
	else if (EQ(gensymed_symbol,Qminute) || EQ(gensymed_symbol,Qminutes))
	    temp = FIX((SI_Long)60L);
	else if (EQ(gensymed_symbol,Qhour) || EQ(gensymed_symbol,Qhours))
	    temp = FIX((SI_Long)3600L);
	else if (EQ(gensymed_symbol,Qday) || EQ(gensymed_symbol,Qdays))
	    temp = FIX((SI_Long)86400L);
	else if (EQ(gensymed_symbol,Qweek) || EQ(gensymed_symbol,Qweeks))
	    temp = FIX((SI_Long)604800L);
	else
	    temp = FIX((SI_Long)1L);
	return phrase_cons(ltimes(expression,temp),Qseconds);
    }
    else if (CONSP(expression) && find(4,Qseconds,expression,Kkey,
	    SYMBOL_FUNCTION(Qconvert_history_interval_maybe_cdr)))
	return VALUES_1(Bad_phrase);
    else if (EQ(unit,Qseconds))
	return VALUES_1(expression);
    else {
	gensymed_symbol = unit;
	if (EQ(gensymed_symbol,Qnumber))
	    temp = FIX((SI_Long)1L);
	else if (EQ(gensymed_symbol,Qsecond) || EQ(gensymed_symbol,Qseconds))
	    temp = FIX((SI_Long)1L);
	else if (EQ(gensymed_symbol,Qminute) || EQ(gensymed_symbol,Qminutes))
	    temp = FIX((SI_Long)60L);
	else if (EQ(gensymed_symbol,Qhour) || EQ(gensymed_symbol,Qhours))
	    temp = FIX((SI_Long)3600L);
	else if (EQ(gensymed_symbol,Qday) || EQ(gensymed_symbol,Qdays))
	    temp = FIX((SI_Long)86400L);
	else if (EQ(gensymed_symbol,Qweek) || EQ(gensymed_symbol,Qweeks))
	    temp = FIX((SI_Long)604800L);
	else
	    temp = FIX((SI_Long)1L);
	return phrase_list_3(Qstar,temp,expression);
    }
}

static Object Qclass_qualified_name;  /* class-qualified-name */

/* REJECT-TEXT-OF-ATTRIBUTE-REFERENCE */
Object reject_text_of_attribute_reference(form)
    Object form;
{
    Object nested_designation, nested_simple_role_qm;

    x_note_fn_call(195,6);
    nested_designation = THIRD(form);
    nested_simple_role_qm = CONSP(nested_designation) ? 
	    simple_role_of_role(role_of_designation(nested_designation)) : Nil;
    if (nested_simple_role_qm && (SYMBOLP(nested_simple_role_qm) || 
	    CONSP(nested_simple_role_qm) && 
	    EQ(M_CAR(nested_simple_role_qm),Qclass_qualified_name)) && 
	    THIRD(nested_designation))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(form);
}

/* CONVERT-CLASS-QUALIFIED-LIST-TO-KEYWORD-SYMBOL */
Object convert_class_qualified_list_to_keyword_symbol(parse_result)
    Object parse_result;
{
    x_note_fn_call(195,7);
    return make_unique_slot_name_symbol(CONSP(parse_result) ? 
	    M_CAR(M_CDR(parse_result)) : Nil,CONSP(parse_result) ? 
	    M_CAR(M_CDR(M_CDR(parse_result))) : parse_result);
}

static Object Qis_of_class;        /* is-of-class */

/* FLATTEN-IS-OF-CLASS-TYPE-SPEC */
Object flatten_is_of_class_type_spec(is_of_class_expr)
    Object is_of_class_expr;
{
    Object type_expr, temp;
    char temp_1;

    x_note_fn_call(195,8);
    if (CONSP(is_of_class_expr) && EQ(M_CAR(is_of_class_expr),Qnot))
	return phrase_list_2(Qnot,
		flatten_is_of_class_type_spec(SECOND(is_of_class_expr)));
    else if (CONSP(is_of_class_expr) && EQ(M_CAR(is_of_class_expr),
	    Qis_of_class)) {
	type_expr = THIRD(is_of_class_expr);
	if (CONSP(type_expr) && EQ(M_CAR(type_expr),Qquote)) {
	    temp = M_CAR(M_CDR(type_expr));
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = M_CAR(M_CAR(M_CDR(type_expr)));
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ?  !TRUEP(M_CDR(M_CAR(M_CDR(type_expr)))) : TRUEP(Nil))
	    return phrase_list_3(Qis_of_class,
		    M_CAR(M_CDR(is_of_class_expr)),phrase_list_2(Qquote,
		    M_CAR(M_CAR(M_CDR(type_expr)))));
	else
	    return VALUES_1(is_of_class_expr);
    }
    else
	return VALUES_1(is_of_class_expr);
}

static Object Qaverage;            /* average */

static Object Qaggregated_average;  /* aggregated-average */

/* PATCH-AGGREGATOR-SCOPE */
Object patch_aggregator_scope(form)
    Object form;
{
    Object temp;

    x_note_fn_call(195,9);
    if (EQ(CAR(form),Qaverage))
	M_CAR(form) = Qaggregated_average;
    temp = SECOND(form);
    if (SYMBOLP(temp))
	return phrase_list_3(FIRST(form),phrase_cons(SECOND(form),Nil),
		THIRD(form));
    else
	return VALUES_1(form);
}

void grammar2_INIT()
{
    Object Qpatch_aggregator_scope, AB_package, string_constant_127;
    Object string_constant_126, string_constant_125, string_constant_124;
    Object string_constant_123, string_constant_122, string_constant_121;
    Object string_constant_120, string_constant_119, string_constant_118;
    Object string_constant_117, string_constant_116, string_constant_115;
    Object string_constant_114, string_constant_113, string_constant_112;
    Object Qflatten_is_of_class_type_spec, string_constant_111;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object string_constant_101, string_constant_100, string_constant_99;
    Object string_constant_98, string_constant_97, string_constant_96;
    Object string_constant_95, string_constant_94, string_constant_93;
    Object string_constant_92, Qfilter_out_the_text_of_and_region_icon_color;
    Object Qfilter_out_the_text_of_as_a_special_case;
    Object Qreject_if_sequence_constant, Qcheck_number_of_args;
    Object Qfix_action_list, string_constant_91, string_constant_90;
    Object string_constant_89, string_constant_88, string_constant_87;
    Object string_constant_86, string_constant_85, string_constant_84;
    Object string_constant_83, Qtranslate_role_and_preposition;
    Object Qrestrict_if_not_slot_edit_feature, Qrestrict_if_slot_edit_feature;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, string_constant_75, string_constant_74;
    Object string_constant_73, string_constant_72, string_constant_71;
    Object string_constant_70, string_constant_69, string_constant_68;
    Object string_constant_67, string_constant_66, string_constant_65;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object string_constant_58, string_constant_57, string_constant_56;
    Object string_constant_55, string_constant_54, string_constant_53;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object string_constant_40, string_constant_39, string_constant_38;
    Object string_constant_37, string_constant_36, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object string_constant_25, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12, string_constant_11;
    Object string_constant_10, string_constant_9, string_constant_8;
    Object string_constant_7, string_constant_6, string_constant_5;
    Object string_constant_4, string_constant_3, string_constant_2;
    Object string_constant_1, string_constant;
    Object Qreject_text_of_attribute_reference, Qitem_color;
    Object Qfilter_out_region_icon_color, Qchoose_is_or_eq;
    Object Qsymbol_cannot_be_true_false_or_not, Qfuzzy_comparator_reparser;
    Object Qconvert_class_qualified_list_to_keyword_symbol;
    Object Qtranslate_role_local_name_and_preposition;

    x_note_fn_call(195,10);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qtoo_few_arguments = STATIC_SYMBOL("TOO-FEW-ARGUMENTS",AB_package);
    Qtoo_many_arguments = STATIC_SYMBOL("TOO-MANY-ARGUMENTS",AB_package);
    Qwrong_number_of_arguments = STATIC_SYMBOL("WRONG-NUMBER-OF-ARGUMENTS",
	    AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qcall_function = STATIC_SYMBOL("CALL-FUNCTION",AB_package);
    Qcheck_number_of_args = STATIC_SYMBOL("CHECK-NUMBER-OF-ARGS",AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_number_of_args,
	    STATIC_FUNCTION(check_number_of_args,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qcheck_number_of_args);
    Qof = STATIC_SYMBOL("OF",AB_package);
    Qat_port = STATIC_SYMBOL("AT-PORT",AB_package);
    Qrelated = STATIC_SYMBOL("RELATED",AB_package);
    Qtranslate_role_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-AND-PREPOSITION",AB_package);
    SET_SYMBOL_FUNCTION(Qtranslate_role_and_preposition,
	    STATIC_FUNCTION(translate_role_and_preposition,NIL,FALSE,1,1));
    Qtranslate_role_local_name_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-LOCAL-NAME-AND-PREPOSITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qtranslate_role_local_name_and_preposition,
	    STATIC_FUNCTION(translate_role_local_name_and_preposition,NIL,
	    FALSE,1,1));
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    Qminutes = STATIC_SYMBOL("MINUTES",AB_package);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    Qhours = STATIC_SYMBOL("HOURS",AB_package);
    Qday = STATIC_SYMBOL("DAY",AB_package);
    Qdays = STATIC_SYMBOL("DAYS",AB_package);
    Qweek = STATIC_SYMBOL("WEEK",AB_package);
    Qweeks = STATIC_SYMBOL("WEEKS",AB_package);
    Qconvert_history_interval_maybe_cdr = 
	    STATIC_SYMBOL("CONVERT-HISTORY-INTERVAL-MAYBE-CDR",AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_history_interval_maybe_cdr,
	    STATIC_FUNCTION(convert_history_interval_maybe_cdr,NIL,FALSE,1,1));
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qreject_text_of_attribute_reference = 
	    STATIC_SYMBOL("REJECT-TEXT-OF-ATTRIBUTE-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qreject_text_of_attribute_reference,
	    STATIC_FUNCTION(reject_text_of_attribute_reference,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qreject_text_of_attribute_reference);
    Qconvert_class_qualified_list_to_keyword_symbol = 
	    STATIC_SYMBOL("CONVERT-CLASS-QUALIFIED-LIST-TO-KEYWORD-SYMBOL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_class_qualified_list_to_keyword_symbol,
	    STATIC_FUNCTION(convert_class_qualified_list_to_keyword_symbol,
	    NIL,FALSE,1,1));
    Qfuzzy_comparator_reparser = STATIC_SYMBOL("FUZZY-COMPARATOR-REPARSER",
	    AB_package);
    Qsymbol_cannot_be_true_false_or_not = 
	    STATIC_SYMBOL("SYMBOL-CANNOT-BE-TRUE-FALSE-OR-NOT",AB_package);
    Qchoose_is_or_eq = STATIC_SYMBOL("CHOOSE-IS-OR-=",AB_package);
    Qflatten_is_of_class_type_spec = 
	    STATIC_SYMBOL("FLATTEN-IS-OF-CLASS-TYPE-SPEC",AB_package);
    Qfilter_out_region_icon_color = 
	    STATIC_SYMBOL("FILTER-OUT-REGION-ICON-COLOR",AB_package);
    Qitem_color = STATIC_SYMBOL("ITEM-COLOR",AB_package);
    string_constant = 
	    STATIC_STRING("13*Vy1o83kXy1r83=py838Ry83=py1m9k83-9y1m9k83-IUy83=py1m9k83-Ay1omlnq9l1o83dPy1r83=xy838Ry83=xy1m9k83-9y1m9k83-IUy83=xy1m9k83-Ay1");
    string_constant_1 = 
	    STATIC_STRING("omlnq9l1m83kXy834my1m83dPy834my1m83kXy833*y1m83dPy830By1n83kXy1o833*y1m9k831by1m9k83=Yy1m9k83=hy1m83-*-yl1n83dPy1o830By1m9k831by");
    string_constant_2 = 
	    STATIC_STRING("1m9k83=Yy1m9k83=hy1m83-*-yl1n83kXy1o833*y1m9k831by1m9k83=Ty1m9k83=hy1m9m1m83-*-yl1n83dPy1o830By1m9k831by1m9k83=Ty1m9k83=hy1m9m1m");
    string_constant_3 = 
	    STATIC_STRING("83-*-yl1p83kXy1n83=py1m9k83*Iy83-2y1n83*Iyl1m9kn9n9o1p83dPy1n83=xy1m9k83*Iy83-2y1n83*Iyl1m9kn9n9o1n83kXy1o833*y1m9k83*Iy834Uy833");
    string_constant_4 = 
	    STATIC_STRING("*y1o83-=ry1m9knlo1n83dPy1o830By1m9k83*Iy834Uy830By1o83-=ry1m9knlo1n83kXy1p833*y1m9k83*Iy1m9k9m834Uy833*y1o83-=py1m9kolp1n83dPy1p");
    string_constant_5 = 
	    STATIC_STRING("830By1m9k83*Iy1m9k9m834Uy830By1o83-=py1m9kolp1n83kXy1n833*y1m9k83*Iy1m9k832Zy1m832Zyl1n83dPy1n830By1m9k83*Iy1m9k832Zy1m832Zyl1n8");
    string_constant_6 = 
	    STATIC_STRING("3kXy1q1m9k9p1m9k83*ly1m9k83-Ty833*y1m9k83*Iy1m9k832Zy1m832Zy1m83-w9yo1n83dPy1q1m9k9p1m9k83*ly1m9k83-Ty830By1m9k83*Iy1m9k832Zy1m8");
    string_constant_7 = 
	    STATIC_STRING("32Zy1m83-w9yo1n83kXy1r1m9k9p1m9k831Sy1m9k83*ly1m9k83-Ty833*y1m9k83*Iy1m9k832Zy1m832Zy1m83-PWyp1n83dPy1r1m9k9p1m9k831Sy1m9k83*ly1");
    string_constant_8 = 
	    STATIC_STRING("m9k83-Ty830By1m9k83*Iy1m9k832Zy1m832Zy1m83-PWyp1n83kXy1r1m9k9p1m9k83-Cpy1m9k83*ly1m9k83-Ty833*y1m9k83*Iy1m9k832Zy1m832Zy1m83-pZy");
    string_constant_9 = 
	    STATIC_STRING("p1n83dPy1r1m9k9p1m9k83-Cpy1m9k83*ly1m9k83-Ty830By1m9k83*Iy1m9k832Zy1m832Zy1m83-pZyp1n83kXy1s1m9k9p1m9k83*ly1m9k83-Ty833*y1m9k83*");
    string_constant_10 = 
	    STATIC_STRING("5y1m9k83-Ty83f2y1m9k83pZy1n83-*Iyor1n83dPy1s1m9k9p1m9k83*ly1m9k83-Ty830By1m9k83*5y1m9k83-Ty83f2y1m9k83pZy1n83-*Iyor1n83kXy1u1m9k");
    string_constant_11 = 
	    STATIC_STRING("9p1m9k83*ly1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83f2y1m9k83pZy1m9k83*Iy1m9k83=Oy1n83-*Iyor1n83dPy1u1m9k9p1m9k83*ly1m9k83-Ty830By1m9k8");
    string_constant_12 = 
	    STATIC_STRING("3*5y1m9k83-Ty83f2y1m9k83pZy1m9k83*Iy1m9k83=Oy1n83-*Iyor1n83kXy1u1m9k9p1m9k83*ly1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83f2y1m9k83pZy1m9");
    string_constant_13 = 
	    STATIC_STRING("k83*Iy1m9k832Zy1m832Zy1n83-*Iyor1n83dPy1u1m9k9p1m9k83*ly1m9k83-Ty830By1m9k83*5y1m9k83-Ty83f2y1m9k83pZy1m9k83*Iy1m9k832Zy1m832Zy1");
    string_constant_14 = 
	    STATIC_STRING("n83-*Iyor1n83kXy1t1m9k9p1m9k83*ly1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83lgy83gTy1m9k83pZy1n83-GPyor1n83dPy1t1m9k9p1m9k83*ly1m9k83-Ty8");
    string_constant_15 = 
	    STATIC_STRING("30By1m9k83*5y1m9k83-Ty83-Fhy83gTy1m9k83pZy1n83-GPyor1n83kXy1v1m9k9p1m9k83*ly1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83lgy83gTy1m9k83pZy1");
    string_constant_16 = 
	    STATIC_STRING("m9k83*Iy1m9k83=Oy1n83-GPyor1n83dPy1v1m9k9p1m9k83*ly1m9k83-Ty830By1m9k83*5y1m9k83-Ty83-Fhy83gTy1m9k83pZy1m9k83*Iy1m9k83=Oy1n83-GP");
    string_constant_17 = 
	    STATIC_STRING("yor1n83kXy1v1m9k9p1m9k83*ly1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83lgy83gTy1m9k83pZy1m9k83*Iy1m9k832Zy1m832Zy1n83-GPyor1n83dPy1v1m9k9p");
    string_constant_18 = 
	    STATIC_STRING("1m9k83*ly1m9k83-Ty830By1m9k83*5y1m9k83-Ty83-Fhy83gTy1m9k83pZy1m9k83*Iy1m9k832Zy1m832Zy1n83-GPyor1n83kXy1n833*y1m9k83*Iy1m9k83=Oy");
    string_constant_19 = 
	    STATIC_STRING("l1n83dPy1n830By1m9k83*Iy1m9k83=Oyl1n83kXy1q1m9k9p1m9k83*ly1m9k83-Ty833*y1m9k83*Iy1m9k83=Oy1m83-w9yo1n83dPy1q1m9k9p1m9k83*ly1m9k8");
    string_constant_20 = 
	    STATIC_STRING("3-Ty830By1m9k83*Iy1m9k83=Oy1m83-w9yo1n83kXy1r1m9k9p1m9k831Sy1m9k83*ly1m9k83-Ty833*y1m9k83*Iy1m9k83=Oy1m83-PWyp1n83dPy1r1m9k9p1m9");
    string_constant_21 = 
	    STATIC_STRING("k831Sy1m9k83*ly1m9k83-Ty830By1m9k83*Iy1m9k83=Oy1m83-PWyp1n83kXy1r1m9k9p1m9k83-Cpy1m9k83*ly1m9k83-Ty833*y1m9k83*Iy1m9k83=Oy1m83-p");
    string_constant_22 = 
	    STATIC_STRING("Zyp1n83dPy1r1m9k9p1m9k83-Cpy1m9k83*ly1m9k83-Ty830By1m9k83*Iy1m9k83=Oy1m83-pZyp1p83kXy1o83=py1m9k83*Iy1m9k9m83-2y1n83-aryl1m9ko9n");
    string_constant_23 = 
	    STATIC_STRING("9o1p83dPy1o83=xy1m9k83*Iy1m9k9m83-2y1n83-aryl1m9ko9n9o1o83kXy1o833*y1m9k83*Iy83=Zy83BEy1n83-=qyl1m9ko9q1o83dPy1o830By1m9k83*Iy83");
    string_constant_24 = 
	    STATIC_STRING("=Zy83BEy1n83-=qyl1m9ko9q1o83kXy1p833*y1m9k83*Iy1m9k9m83=Zy83BEy1m9m1n83-=qyl1m9kp9q1o83dPy1p830By1m9k83*Iy1m9k9m83=Zy83BEy1m9m1n");
    string_constant_25 = 
	    STATIC_STRING("83-=qyl1m9kp9q1n83kXy1w833*y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty1m9k9p1m9k83-Gy1m9k832dy1m9k83*ty1m9k83-9y83=py1m9k83-Ay1n83-=qy");
    string_constant_26 = 
	    STATIC_STRING("lv1n83dPy1w830By1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty1m9k9p1m9k83-Gy1m9k832dy1m9k83*ty1m9k83-9y83=xy1m9k83-Ay1n83-=qylv1n83kXy1x8");
    string_constant_27 = 
	    STATIC_STRING("33*y1m9k83*Iy1m9k9m1m9k83=ay1m9k831Ly1m9k83-Ty1m9k9p1m9k83-Gy1m9k832dy1m9k83*ty1m9k83-9y83=py1m9k83-Ay1m9m1n83-=qylw1n83dPy1x830");
    string_constant_28 = 
	    STATIC_STRING("By1m9k83*Iy1m9k9m1m9k83=ay1m9k831Ly1m9k83-Ty1m9k9p1m9k83-Gy1m9k832dy1m9k83*ty1m9k83-9y83=xy1m9k83-Ay1m9m1n83-=qylw1n83kXy1r833*y");
    string_constant_29 = 
	    STATIC_STRING("1m9k83*Iy1m9k9p1m9k83Euy1m9k83-Oy1m9k83*5y833*y1n83maylr1n83dPy1r830By1m9k83*Iy1m9k9p1m9k83Euy1m9k83-Oy1m9k83*5y830By1n83maylr1n");
    string_constant_30 = 
	    STATIC_STRING("83kXy1s833*y1m9k83*Iy1m9k9m1m9k9p1m9k83Euy1m9k83-Oy1m9k83*5y833*y1m9m1n83mayls1n83dPy1s830By1m9k83*Iy1m9k9m1m9k9p1m9k83Euy1m9k83");
    string_constant_31 = 
	    STATIC_STRING("-Oy1m9k83*5y830By1m9m1n83mayls1n83kXy1o833*y1m9k831by1m9k83-Kgy1m9k83GSy1m83-ahyl1n83dPy1o830By1m9k831by1m9k83-Kgy1m9k83GSy1m83-");
    string_constant_32 = 
	    STATIC_STRING("ahyl1n83kXy1p833*y1m9k831by1m9k9m1m9k83-Kgy1m9k83GSy1m9m1m83-ahyl1n83dPy1p830By1m9k831by1m9k9m1m9k83-Kgy1m9k83GSy1m9m1m83-ahyl1n");
    string_constant_33 = 
	    STATIC_STRING("83kXy1m833*y1m9k83Koy1m83Koyl1n83dPy1m830By1m9k83Koy1m83Koyl1n83kXy1m83sEy1m9k83Koy1m83Koyl1n83dPy1m83sEy1m9k83Koy1m83Koyl1n83kX");
    string_constant_34 = 
	    STATIC_STRING("y1o833*y1m9k838By1m9k9m1m9k83vpy1m9m1m83Koyl1n83dPy1o830By1m9k838By1m9k9m1m9k83vpy1m9m1m83Koyl1n83kXy1o83sEy1m9k838By1m9k9m1m9k8");
    string_constant_35 = 
	    STATIC_STRING("3vpy1m9m1m83Koyl1n83dPy1o83sEy1m9k838By1m9k9m1m9k83vpy1m9m1m83Koyl1n83kXy1o1m9k9p1m9k83*ly1m9k83-Ty833*y1m83-w9yo1n83dPy1o1m9k9p");
    string_constant_36 = 
	    STATIC_STRING("1m9k83*ly1m9k83-Ty830By1m83-w9yo1n83kXy1o1m9k9p1m9k83*ly1m9k83-Ty83-8iy1m83-w9yo1n83dPy1o1m9k9p1m9k83*ly1m9k83-Ty83-Ffy1m83-w9yo");
    string_constant_37 = 
	    STATIC_STRING("1n83kXy1p1m9k9p1m9k831Sy1m9k83*ly1m9k83-Ty83-8iy1m83-PWyp1n83dPy1p1m9k9p1m9k831Sy1m9k83*ly1m9k83-Ty83-Ffy1m83-PWyp1n83kXy1p1m9k9");
    string_constant_38 = 
	    STATIC_STRING("p1m9k831Sy1m9k83*ly1m9k83-Ty833*y1m83-PWyp1n83dPy1p1m9k9p1m9k831Sy1m9k83*ly1m9k83-Ty830By1m83-PWyp1n83kXy1p1m9k9p1m9k83-Cpy1m9k8");
    string_constant_39 = 
	    STATIC_STRING("3*ly1m9k83-Ty83-8iy1m83-pZyp1n83dPy1p1m9k9p1m9k83-Cpy1m9k83*ly1m9k83-Ty83-Ffy1m83-pZyp1n83kXy1p1m9k9p1m9k83-Cpy1m9k83*ly1m9k83-T");
    string_constant_40 = 
	    STATIC_STRING("y833*y1m83-pZyp1n83dPy1p1m9k9p1m9k83-Cpy1m9k83*ly1m9k83-Ty830By1m83-pZyp1n83kXy1t1m9k9p1m9k9r1m9k83-Ty1m9k9p1m9k83C4y83C-y1m9k83");
    string_constant_41 = 
	    STATIC_STRING("1Sy1m9k83*ly83-2Xy2l83-U9yt1n83dPy1t1m9k9p1m9k9r1m9k83-Ty1m9k9p1m9k83C4y83C-y1m9k831Sy1m9k83*ly83-2Xy2l83-U9yt1m83L9y8382y1m83oD");
    string_constant_42 = 
	    STATIC_STRING("y8382y1n83L9y1o1m9k9p1m9k83*ly1m9k83-Ty833*y1m83-w9yo1n83oDy1o1m9k9p1m9k83*ly1m9k83-Ty830By1m83-w9yo1n83L9y1o1m9k9p1m9k83*ly1m9k");
    string_constant_43 = 
	    STATIC_STRING("83-Ty83-iJy1m83-w9yo1n83oDy1o1m9k9p1m9k83*ly1m9k83-Ty83-v9y1m83-w9yo1n83L9y1p1m9k9p1m9k831Sy1m9k83*ly1m9k83-Ty833*y1m83-PWyp1n83");
    string_constant_44 = 
	    STATIC_STRING("oDy1p1m9k9p1m9k831Sy1m9k83*ly1m9k83-Ty830By1m83-PWyp1n83L9y1p1m9k9p1m9k831Sy1m9k83*ly1m9k83-Ty83-iJy1m83-PWyp1n83oDy1p1m9k9p1m9k");
    string_constant_45 = 
	    STATIC_STRING("831Sy1m9k83*ly1m9k83-Ty83-v9y1m83-PWyp1n83L9y1p1m9k9p1m9k83-Cpy1m9k83*ly1m9k83-Ty833*y1m83-pZyp1n83oDy1p1m9k9p1m9k83-Cpy1m9k83*l");
    string_constant_46 = 
	    STATIC_STRING("y1m9k83-Ty830By1m83-pZyp1n83L9y1p1m9k9p1m9k83vry1m9k831Ay1m9k83-Ty833*y1m83-TKyp1n83oDy1p1m9k9p1m9k83vry1m9k831Ay1m9k83-Ty830By1");
    string_constant_47 = 
	    STATIC_STRING("m83-TKyp1n83L9y1p1m9k9p1m9k83g-y1m9k831Ay1m9k83-Ty833*y1m83-Muyp1n83oDy1p1m9k9p1m9k83g-y1m9k831Ay1m9k83-Ty830By1m83-Muyp1n83sEy1");
    string_constant_48 = 
	    STATIC_STRING("o1m9k9p83g*y1m9k83-Ty833*y1n9pmo1n83sEy1o1m9k9p83g*y1m9k83-Ty830By1n9pmo1o83sEy1p1m9k9p83g*y83*Zy1m9k83-Ty833*y1n9p2lmnp1l9s1o83");
    string_constant_49 = 
	    STATIC_STRING("sEy1p1m9k9p83g*y83*Zy1m9k83-Ty830By1n9p2lmnp1l9s1n83sEy1p1m9k9p83Yky83-*sy1m9k83-Ty833*y1n9p1n9tm83-2yp1n83sEy1p1m9k9p83Yky83-*s");
    string_constant_50 = 
	    STATIC_STRING("y1m9k83-Ty830By1n9p1n9tm83-2yp1n83sEy1q1m9k9p83Yky83-*sy83*Zy1m9k83-Ty833*y1n9p2l1n9tm83-2yoq1n83sEy1q1m9k9p83Yky83-*sy83*Zy1m9k");
    string_constant_51 = 
	    STATIC_STRING("83-Ty830By1n9p2l1n9tm83-2yoq1n83L9y1o1m9k9p83-rmy1m9k83-Ty833*y1n9pmo1n83oDy1o1m9k9p83-rmy1m9k83-Ty830By1n9pmo1n83L9y1o1m9k9p83-");
    string_constant_52 = 
	    STATIC_STRING("rny1m9k83-Ty833*y1n9pmo1n83oDy1o1m9k9p83-rny1m9k83-Ty830By1n9pmo1m83-rny1m9k83-=fy1n83L9y1r1m9k9p1m9k83Gy1m9k83-Ty1m9k9p836Iy1m9");
    string_constant_53 = 
	    STATIC_STRING("k83-Ty833*y1n9p1n83-sYyp83Gyr1n83oDy1r1m9k9p1m9k83Gy1m9k83-Ty1m9k9p836Iy1m9k83-Ty830By1n9p1n83-sYyp83Gyr1n83L9y1r1m9k9p1m9k83Gy1");
    string_constant_54 = 
	    STATIC_STRING("m9k83-Ty1m9k9p1m9k831ay1m9k83-Ty833*y1n9p1n83-sYy831ay83Gyr1n83oDy1r1m9k9p1m9k83Gy1m9k83-Ty1m9k9p1m9k831ay1m9k83-Ty830By1n9p1n83");
    string_constant_55 = 
	    STATIC_STRING("-sYy831ay83Gyr1n83L9y1r1m9k9p1m9k83Gy1m9k83-Ty1m9k9p1m9k837iy1m9k83-Ty833*y1n9p1n83-sYy837iy83Gyr1n83oDy1r1m9k9p1m9k83Gy1m9k83-T");
    string_constant_56 = 
	    STATIC_STRING("y1m9k9p1m9k837iy1m9k83-Ty830By1n9p1n83-sYy837iy83Gyr1o83L9y1o1m9k9p1m9k83Gy1m9k83-Ty833*y1n9p1n83-sYy83Gy83Gyo9u1o83oDy1o1m9k9p1");
    string_constant_57 = 
	    STATIC_STRING("m9k83Gy1m9k83-Ty830By1n9p1n83-sYy83Gy83Gyo9u1n83-iJy1n1m9k83-9y83=py1m9k83-Aym1n83-v9y1n1m9k83-9y83=xy1m9k83-Aym1n83L9y1p1m9k9p1");
    string_constant_58 = 
	    STATIC_STRING("m9k83-qy1m9k83=hy1m9k83-Ty833*y1m83*myp1n83oDy1p1m9k9p1m9k83-qy1m9k83=hy1m9k83-Ty830By1m83*myp1n83L9y1t1m9k9p1m9k9r1m9k83-Ty1m9k");
    string_constant_59 = 
	    STATIC_STRING("9p1m9k83C4y83C-y1m9k831Sy1m9k83*ly836ay2l83-U9yt1n83oDy1t1m9k9p1m9k9r1m9k83-Ty1m9k9p1m9k83C4y83C-y1m9k831Sy1m9k83*ly83oCy2l83-U9");
    string_constant_60 = 
	    STATIC_STRING("yt1n83L9y1q1m9k9p1m9k83-RZy1m9k837my833*y1m9k83-ty833*y1n83-Rayoq1n83oDy1q1m9k9p1m9k83-RZy1m9k837my830By1m9k83-ty830By1n83-Rayoq");
    string_constant_61 = 
	    STATIC_STRING("1n83L9y1s1m9k9p1m9k83-RZy1m9k837my833*y1m9k83-ty1m9k9p1m9k83-7Fy83-Gy1n83-Rbyo1m9ks1n83oDy1s1m9k9p1m9k83-RZy1m9k837my830By1m9k83");
    string_constant_62 = 
	    STATIC_STRING("-ty1m9k9p1m9k83-7Fy83-Gy1n83-Rbyo1m9ks1n83L9y1n1m9k9p1m9k83-2y830Ty1m9kn1n83oDy1n1m9k9p1m9k83-2y830Ty1m9kn1n83Y3y1m1m9k832dy1m9k");
    string_constant_63 = 
	    STATIC_STRING("83*ty83-7Dy1n83-Fgy1m1m9k832dy1m9k83*ty83-7Dy1n83Y3y1m1m9k832dy1m9k83*ty83-7Dy1n83-Fgy1m1m9k832dy1m9k83*ty83-7Dy1n83Y3y1r1m9k831");
    string_constant_64 = 
	    STATIC_STRING("9y1m9k83*Iy1m9k83-Ty1m9k9p1m9k83-Gy1m9k832dy1m9k83*ty83-May1n83-Fgy1r1m9k8319y1m9k83*Iy1m9k83-Ty1m9k9p1m9k83-Gy1m9k832dy1m9k83*t");
    string_constant_65 = 
	    STATIC_STRING("y83-May1n83kXy1t83=xy1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83C7y1m9k9w833*y1n83xWytl1n83dPy1t83=xy1m9k83*Iy1m9k83=Yy1m9k9v1m9k8");
    string_constant_66 = 
	    STATIC_STRING("3-Ty1m9k9p83C7y1m9k9w830By1n83xWytl1n83kXy1u83=xy1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83C7y1m9k9w833*y1m9m1n83xWyul1n83d");
    string_constant_67 = 
	    STATIC_STRING("Py1u83=xy1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83C7y1m9k9w830By1m9m1n83xWyul1n83kXy1t83dPy1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-");
    string_constant_68 = 
	    STATIC_STRING("Ty1m9k9p83C7y1m9k9w833*y1n83xWytl1n83dPy1t83dPy1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83C7y1m9k9w830By1n83xWytl1n83kXy1u83dPy1m9");
    string_constant_69 = 
	    STATIC_STRING("k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83C7y1m9k9w833*y1m9m1n83xWyul1n83dPy1u83dPy1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty1m9k");
    string_constant_70 = 
	    STATIC_STRING("9p83C7y1m9k9w830By1m9m1n83xWyul1n83kXy1t833*y1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83-Gy1m9k9w833*y1n83xWytl1n83dPy1t830By1m9k8");
    string_constant_71 = 
	    STATIC_STRING("3*Iy1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83-Gy1m9k9w830By1n83xWytl1n83kXy1u833*y1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83-Gy1m9k9");
    string_constant_72 = 
	    STATIC_STRING("w833*y1m9m1n83xWyul1n83dPy1u830By1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty1m9k9p83-Gy1m9k9w830By1m9m1n83xWyul1n83kXy1q83=xy1m9k83*");
    string_constant_73 = 
	    STATIC_STRING("Iy1m9k83=Yy1m9k9v1m9k83-Ty833*y1n83xWyql1n83dPy1q83=xy1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-Ty830By1n83xWyql1n83kXy1r83=xy1m9k83*Iy1m9k");
    string_constant_74 = 
	    STATIC_STRING("9m1m9k83=Yy1m9k9v1m9k83-Ty833*y1m9m1n83xWyrl1n83dPy1r83=xy1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty830By1m9m1n83xWyrl1n83kXy1q83dP");
    string_constant_75 = 
	    STATIC_STRING("y1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-Ty833*y1n83xWyql1n83dPy1q83dPy1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-Ty830By1n83xWyql1n83kXy1r83dPy1m9k8");
    string_constant_76 = 
	    STATIC_STRING("3*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty833*y1m9m1n83xWyrl1n83dPy1r83dPy1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty830By1m9m1n83xWyrl1n83k");
    string_constant_77 = 
	    STATIC_STRING("Xy1q833*y1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-Ty833*y1n83xWyql1n83dPy1q830By1m9k83*Iy1m9k83=Yy1m9k9v1m9k83-Ty830By1n83xWyql1n83kXy1r83");
    string_constant_78 = 
	    STATIC_STRING("3*y1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty833*y1m9m1n83xWyrl1n83dPy1r830By1m9k83*Iy1m9k9m1m9k83=Yy1m9k9v1m9k83-Ty830By1m9m1n83xW");
    string_constant_79 = STATIC_STRING("yrl");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfuzzy_comparator_reparser);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qsymbol_cannot_be_true_false_or_not);
    push_optimized_constant(Qchoose_is_or_eq);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qflatten_is_of_class_type_spec);
    push_optimized_constant(Qfirst);
    push_optimized_constant(Qfilter_out_region_icon_color);
    push_optimized_constant(Qitem_color);
    push_optimized_constant(Qreject_text_of_attribute_reference);
    push_optimized_constant(Qmember);
    push_optimized_constant(Qlist);
    add_grammar_rules_function(regenerate_optimized_constant(nconc2(list(50,
	    string_constant,string_constant_1,string_constant_2,
	    string_constant_3,string_constant_4,string_constant_5,
	    string_constant_6,string_constant_7,string_constant_8,
	    string_constant_9,string_constant_10,string_constant_11,
	    string_constant_12,string_constant_13,string_constant_14,
	    string_constant_15,string_constant_16,string_constant_17,
	    string_constant_18,string_constant_19,string_constant_20,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24,string_constant_25,string_constant_26,
	    string_constant_27,string_constant_28,string_constant_29,
	    string_constant_30,string_constant_31,string_constant_32,
	    string_constant_33,string_constant_34,string_constant_35,
	    string_constant_36,string_constant_37,string_constant_38,
	    string_constant_39,string_constant_40,string_constant_41,
	    string_constant_42,string_constant_43,string_constant_44,
	    string_constant_45,string_constant_46,string_constant_47,
	    string_constant_48,string_constant_49),list(30,
	    string_constant_50,string_constant_51,string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56,string_constant_57,string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64,
	    string_constant_65,string_constant_66,string_constant_67,
	    string_constant_68,string_constant_69,string_constant_70,
	    string_constant_71,string_constant_72,string_constant_73,
	    string_constant_74,string_constant_75,string_constant_76,
	    string_constant_77,string_constant_78,string_constant_79))));
    Qis_of_class = STATIC_SYMBOL("IS-OF-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qflatten_is_of_class_type_spec,
	    STATIC_FUNCTION(flatten_is_of_class_type_spec,NIL,FALSE,1,1));
    Qrestrict_if_slot_edit_feature = 
	    STATIC_SYMBOL("RESTRICT-IF-SLOT-EDIT-FEATURE",AB_package);
    string_constant_80 = 
	    STATIC_STRING("1p1m83gAy83=py1m83gAy83-FZy1m83-FZy83=xy1n83-FZy1q1m9k8312y831Py1m9k832Sy83=xy1m9k8332y83-FZy1o8348ymoq1o83-FZy1o1m9k8312y831Py1");
    string_constant_81 = STATIC_STRING("m9k832Sy83=xy1n8348ymo1n9l83=Vy83gAy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qrestrict_if_slot_edit_feature);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_80,
	    string_constant_81)));
    string_constant_82 = 
	    STATIC_STRING("1m1n83nLy1o1m9k9l1m9k837iy1m9k83-Ty8330y1n9l837iyo1n83nLy1o1m9k9l1m9k831ay1m9k83-Ty8330y1n9l831ayo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_82));
    Qfilter_out_the_text_of_as_a_special_case = 
	    STATIC_SYMBOL("FILTER-OUT-THE-TEXT-OF-AS-A-SPECIAL-CASE",
	    AB_package);
    Qfilter_out_the_text_of_and_region_icon_color = 
	    STATIC_SYMBOL("FILTER-OUT-THE-TEXT-OF-AND-REGION-ICON-COLOR",
	    AB_package);
    Qrestrict_if_not_slot_edit_feature = 
	    STATIC_SYMBOL("RESTRICT-IF-NOT-SLOT-EDIT-FEATURE",AB_package);
    string_constant_83 = 
	    STATIC_STRING("13Ky1m8330y834Hy1m8330y83BFy1m8330y1m1m9k9l83-Gy1o8330y1m1m9k9m83-Gy1mlm1n9n83=Vy8330y1o8330y1n1m9k9m83-Gy83*Zy1ml2lmn1n9n83=Vy8");
    string_constant_84 = 
	    STATIC_STRING("330y1o8330y1o1m9k9l83nay1m9k83-Ty8330y1n9lmo9o1o8330y1p1m9k9l83nay83*Zy1m9k83-Ty8330y1n9l2lmnp9p1n8330y1v1m9k9l83BEy1m9k8319y1m9");
    string_constant_85 = 
	    STATIC_STRING("k83*Iy1m9k83=ay1m9k83-qy1m9k83-Ty8330y1m9k832dy1m9k83*ty8330y1o9l1m83q*ymsv1n8330y1w1m9k9l83BEy83*Zy1m9k8319y1m9k83*Iy1m9k83=ay1");
    string_constant_86 = 
	    STATIC_STRING("m9k83-qy1m9k83-Ty8330y1m9k832dy1m9k83*ty833*y1o9l2l1m83q*ymntw1m8330y1n83-S9y83Hwy8330y1m8330y1n83-S9y83Hwy83nLy1n8330y1r1m9k9l8");
    string_constant_87 = 
	    STATIC_STRING("3-Gy1m9k83CWy1m9k9l83nay1m9k83-Ty8330y1n83CVym1nopr1n8330y1m1m9k837Zy1m9k83*qy1m9l1n834Zy83noy83=uy1n8330y1m1m9k837Zy1m9k834ry1m");
    string_constant_88 = 
	    STATIC_STRING("9l1n834Zy83-Esy836Py1o8330y1m1m9k837Zy1m9k832Jy1m9l1n834Zy83-Ery832Jy1n9q832Jy83-Ery1o8330y1m1m9k837Zy1m9k83=Vy1m9l1n834Zy83-Epy");
    string_constant_89 = 
	    STATIC_STRING("83=Vy1n9q83=Vy83-Epy1o8330y1m1m9k837Zy1m9k831jy1m9l1n834Zy83-Eqy831jy1n9q83=Vy83-Eqy1n8330y1p1m9k9l83U7y83-Xy1m9k83*Xy8330y1n9l1");
    string_constant_90 = 
	    STATIC_STRING("mmnp1n8330y1q1m9k9l83U7y83-Xy83*Zy1m9k83*Xy8330y1n9l2l1mmnoq1n8330y1o83-S9y83-Xy1m9k83*Xy8330y1nl1m838Eymo1n8330y1p83-S9y83-Xy83");
    string_constant_91 = 
	    STATIC_STRING("*Zy1m9k83*Xy8330y1nl2l1m838Eymnp1m83-S9y1m9k9l1o83-S9y1m9k9ml1n9n83=Vy8330y1o83-S8y1m83-Gy83Y3y1mlm9r");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qrestrict_if_slot_edit_feature);
    push_optimized_constant(Qfilter_out_the_text_of_as_a_special_case);
    push_optimized_constant(Qfilter_out_the_text_of_and_region_icon_color);
    push_optimized_constant(Qrestrict_if_not_slot_edit_feature);
    push_optimized_constant(Qtranslate_role_and_preposition);
    add_grammar_rules_function(regenerate_optimized_constant(list(9,
	    string_constant_83,string_constant_84,string_constant_85,
	    string_constant_86,string_constant_87,string_constant_88,
	    string_constant_89,string_constant_90,string_constant_91)));
    Qfix_action_list = STATIC_SYMBOL("FIX-ACTION-LIST",AB_package);
    Qreject_if_sequence_constant = 
	    STATIC_SYMBOL("REJECT-IF-SEQUENCE-CONSTANT",AB_package);
    Qpatch_aggregator_scope = STATIC_SYMBOL("PATCH-AGGREGATOR-SCOPE",
	    AB_package);
    string_constant_92 = 
	    STATIC_STRING("13wy1m832Jy83-UWy1m832Jy83-pSy1m832Jy83-Zxy1o83-Zxy1m1m9k8396y83pNy1n8396y83=Oym9l1o83-Zxy1p1m9k8396y1m9k8312y83-Jiy1m9k832Sy83p");
    string_constant_93 = 
	    STATIC_STRING("Ny1n8396ynp9l1m83-Zxy1o1m9k8396y1m9k83=Iy83-UUy83-a+y1m83-a+y1n1m9k83=Iy83-UUy83-a+y1m83-a+y83-Z+y1m83-a+y83-uiy1m83-UWy1n1m9k83");
    string_constant_94 = 
	    STATIC_STRING("=Iy83-UUy83-UWy1m83-UWy83-pSy1m83-pSy83-Z+y1m83-pSy83-wxy1m83-pSy83-x-y1m83-pSy83-uiy1m832Jy1m83-Jty83-Zxy1m83-pSy1m83-Jty83-Z+y");
    string_constant_95 = 
	    STATIC_STRING("1m83-pSy1m83-Jty83-wxy1m83-pSy1m83-Jty83-x-y1o83-Z+y1o1m9k8312y83-Jiy1m9k832Sy83pNy1n8312ymo9l1o83-wxy1o1m9k837ey83-Jiy1m9k832Sy");
    string_constant_96 = 
	    STATIC_STRING("83pNy1n837eymo9l1o83-x-y1o1m9k83-x+y83vhy1m9k832Sy83pNy1n83-x+ymo9l1o83-uiy1m1m9k83-ujy83pNy1n8312y83=Oym9l1o8333y1o1m9k837ey83-");
    string_constant_97 = 
	    STATIC_STRING("Jiy1m9k832Sy83pNy1n837eymo9l1m8333y83pNy1m8333y1n1m9k83=Iy83-UUy83-SXy1m83-SXy1n1m9k83=Iy83-UUy83-SXy1m83-SXy83-wxy1m83-SXy83-ui");
    string_constant_98 = 
	    STATIC_STRING("y1m83-Jiy83UQy1p83-W5y1p83-6y1m9k9m832ay1m9k83-9y1m9k83-Ay1mnl9n9o1p83-W5y1o83-6y1m9k9m832ay836ay1nnol9n9o1m83-Jty1m1m9k83Fmy83-");
    string_constant_99 = 
	    STATIC_STRING("Juy1m83-Juy83-W5y1n83-Juy1n83-W5y1m9k83vy83-Jvy1mln1m83-Jvy83-W5y1n83-Jvy1n83-W5y1m9k83vy83-Jvy1mln1m83Ecy1m9k83-Ay1n83-UUy1m1m9");
    string_constant_100 = 
	    STATIC_STRING("k83=by83-Gy1mlm1n83-UUy1n1m9k83=by83-Gy83*Zy1m83=by2lmn1n83-UUy1n1m9k83=by83Hwy833*y1nlmn1n83-UUy1n1m9k9p83Hwy833*y1nlmn1o83-UUy");
    string_constant_101 = 
	    STATIC_STRING("1o1m9k9p83nay1m9k83-Ty833*y1n9pmo9q1o83-UUy1p1m9k9p83nay83*Zy1m9k83-Ty833*y1n9p2lmnp9r1n83-UUy1o83lsy83-Xy1m9k83*Xy833*y1nl1m838");
    string_constant_102 = 
	    STATIC_STRING("Eymo1n83-UUy1p83lsy83-Xy83*Zy1m9k83*Xy833*y1nl2l1m838Eymnp1n83-UUy1p1m9k9p83U7y83-Xy1m9k83*Xy833*y1n9p1mmnp1n83-UUy1q1m9k9p83U7y");
    string_constant_103 = 
	    STATIC_STRING("83-Xy83*Zy1m9k83*Xy833*y1n9p2l1mmnoq1m83kXy83-Emy1m83kXy83wVy1m83dPy83-Emy1m83dPy83wVy1o83-Emy1t1m9k83-Ely1m9k83Koy83=Zy83pYy1m9");
    string_constant_104 = 
	    STATIC_STRING("k83FHy1m9k8319y1m9k83-9y831Py1m9k83-Ay1n83-Emyos9s1o83-Emy1o1m9k83-Ely1m9k83Koy83=Zy83pYy1n83-Emyo83=Oy9s1o83wVy1q1m9k83=Iy1m9k9");
    string_constant_105 = 
	    STATIC_STRING("t83pYy1m9k83-9y831Py1m9k83-Ay1n83wVynp9s1m83pYy83-Gy1n83pYy1m83-Gy83*Zy1l2llm1m83pYy1m83Hwy83-=Gy1m83-=Gy834Hy1m83-=Gy1m1m9k9p83");
    string_constant_106 = 
	    STATIC_STRING("-Gy1m83-=Gy1m1m9k9p83*Zy1m83-=Gy1m1m9k9p83*my");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_action_list);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qcheck_number_of_args);
    push_optimized_constant(Qreject_if_sequence_constant);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qfilter_out_the_text_of_as_a_special_case);
    push_optimized_constant(Qfilter_out_the_text_of_and_region_icon_color);
    push_optimized_constant(Qpatch_aggregator_scope);
    push_optimized_constant(Qevery);
    add_grammar_rules_function(regenerate_optimized_constant(list(15,
	    string_constant_92,string_constant_93,string_constant_94,
	    string_constant_95,string_constant_96,string_constant_97,
	    string_constant_98,string_constant_99,string_constant_100,
	    string_constant_101,string_constant_102,string_constant_103,
	    string_constant_104,string_constant_105,string_constant_106)));
    string_constant_107 = 
	    STATIC_STRING("1v1o83L9y1t1m9k9l83pXy1m9k83lHy1m9k838Dy83pYy1m9k83-Ty1m9k83-9y83=xy1m9k83-Ay1nmps9m1o83oDy1t1m9k9l83pXy1m9k83lHy1m9k838Dy83pYy1");
    string_constant_108 = 
	    STATIC_STRING("m9k83-Ty1m9k83-9y83=xy1m9k83-Ay1nmps9m1m83pXy1m9k83-E2y1m83pXy1m9k83-9Sy1m83pXy1m9k83kby1m83pXy1m9k83Dmy1m83pXy1m9k83fFy1o83L9y1");
    string_constant_109 = 
	    STATIC_STRING("p1m9k9l1m9k9n1m9k83-Ty1m9k838Dy83pYy1nmp83=Oy9m1o83oDy1p1m9k9l1m9k9n1m9k83-Ty1m9k838Dy83pYy1nmp83=Oy9m1o83L9y1u1m9k9l1m9k9n1m9k8");
    string_constant_110 = 
	    STATIC_STRING("3-Ty1m9k838Dy83pYy1m9k83FHy1m9k8319y1m9k83-9y831Py1m9k83-Ay1nmpt9m1o83oDy1u1m9k9l1m9k9n1m9k83-Ty1m9k838Dy83pYy1m9k83FHy1m9k8319y");
    string_constant_111 = STATIC_STRING("1m9k83-9y831Py1m9k83-Ay1nmpt9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qpatch_aggregator_scope);
    push_optimized_constant(Qcount);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_107,
	    string_constant_108,string_constant_109,string_constant_110,
	    string_constant_111)));
    string_constant_112 = 
	    STATIC_STRING("13Oy1o83n6y1t1m9k9l83pXy1m9k83lHy1m9k838Dy83-pay1m9k83-Ty1m9k83-9y836Ey1m9k83-Ay1nmps9m1o83n6y1p1m9k9l1m9k9n1m9k83-Ty1m9k838Dy83");
    string_constant_113 = 
	    STATIC_STRING("-pay1nmp83=Oy9m1o83L9y1u1m9k9l1m9k9n1m9k83-Ty1m9k838Dy83-pay1m9k83FHy1m9k8319y1m9k83-9y83aBy1m9k83-Ay1nmpt9m1o83n8y1t1m9k83-Ely1");
    string_constant_114 = 
	    STATIC_STRING("m9k83Koy83=Zy83-pay1m9k83FHy1m9k8319y1m9k83-9y83aBy1m9k83-Ay1n83-Emyos9m1o83n8y1o1m9k83-Ely1m9k83Koy83=Zy83-pay1n83-Emyo83=Oy9m1");
    string_constant_115 = 
	    STATIC_STRING("o83n8y1q1m9k83=Iy1m9k9o83-pay1m9k83-9y83aBy1m9k83-Ay1n83wVynp9m1n83n8y1r83F2y1m9k83*Iy1m9k9l1m9k83Euy1m9k83-Oy1m9k83*5y83F2y1n83");
    string_constant_116 = 
	    STATIC_STRING("maylr1n83n8y1s83F2y1m9k83*Iy1m9k9p1m9k9l1m9k83Euy1m9k83-Oy1m9k83*5y83F2y1m9p1n83mayls1n83n8y1m83F2y1m9k83Koy1m83Koyl1o83n8y1o83F");
    string_constant_117 = 
	    STATIC_STRING("2y1m9k83*Iy83=Zy83BEy1n83-=qyl1m9ko9q1o83n8y1p83F2y1m9k83*Iy1m9k9p83=Zy83BEy1m9p1n83-=qyl1m9kp9q1n83n8y1w83F2y1m9k83*Iy1m9k83=ay");
    string_constant_118 = 
	    STATIC_STRING("1m9k831Ly1m9k83-Ty1m9k9l1m9k83-Gy1m9k832dy1m9k83*ty1m9k83-9y836Ey1m9k83-Ay1n83-=qylv1n83n8y1x83F2y1m9k83*Iy1m9k9p1m9k83=ay1m9k83");
    string_constant_119 = 
	    STATIC_STRING("1Ly1m9k83-Ty1m9k9l1m9k83-Gy1m9k832dy1m9k83*ty1m9k83-9y836Ey1m9k83-Ay1m9p1n83-=qylw1m83-pay83-Gy1n83-pay1m83-Gy83*Zy1l2llm1m83-pa");
    string_constant_120 = 
	    STATIC_STRING("y1m83n5y83-=Gy1n83n8y1t836Ey1m9k83*Iy1m9k83=Yy1m9k9r1m9k83-Ty1m9k9l83C7y1m9k9s83F2y1n83xWytl1n83n8y1u836Ey1m9k83*Iy1m9k9p1m9k83=");
    string_constant_121 = 
	    STATIC_STRING("Yy1m9k9r1m9k83-Ty1m9k9l83C7y1m9k9s83F2y1m9p1n83xWyul1n83n8y1t83F2y1m9k83*Iy1m9k83=Yy1m9k9r1m9k83-Ty1m9k9l83-Gy1m9k9s83F2y1n83xWy");
    string_constant_122 = 
	    STATIC_STRING("tl1n83n8y1u83F2y1m9k83*Iy1m9k9p1m9k83=Yy1m9k9r1m9k83-Ty1m9k9l83-Gy1m9k9s83F2y1m9p1n83xWyul1n83n8y1t83n8y1m9k83*Iy1m9k83=Yy1m9k9r");
    string_constant_123 = 
	    STATIC_STRING("1m9k83-Ty1m9k9l83C7y1m9k9s83F2y1n83xWytl1n83n8y1u83n8y1m9k83*Iy1m9k9p1m9k83=Yy1m9k9r1m9k83-Ty1m9k9l83C7y1m9k9s83F2y1m9p1n83xWyul");
    string_constant_124 = 
	    STATIC_STRING("1n83n8y1q836Ey1m9k83*Iy1m9k83=Yy1m9k9r1m9k83-Ty83F2y1n83xWyql1n83n8y1r836Ey1m9k83*Iy1m9k9p1m9k83=Yy1m9k9r1m9k83-Ty83F2y1m9p1n83x");
    string_constant_125 = 
	    STATIC_STRING("Wyrl1n83n8y1q83F2y1m9k83*Iy1m9k83=Yy1m9k9r1m9k83-Ty83F2y1n83xWyql1n83n8y1r83F2y1m9k83*Iy1m9k9p1m9k83=Yy1m9k9r1m9k83-Ty83F2y1m9p1");
    string_constant_126 = 
	    STATIC_STRING("n83-VLyrl1n83n8y1q83n8y1m9k83*Iy1m9k83=Yy1m9k9r1m9k83-Ty83F2y1n83xWyql1n83n8y1r83n8y1m9k83*Iy1m9k9p1m9k83=Yy1m9k9r1m9k83-Ty83F2y");
    string_constant_127 = STATIC_STRING("1m9p1n83xWyrl");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qpatch_aggregator_scope);
    push_optimized_constant(Qcount);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qflatten_is_of_class_type_spec);
    push_optimized_constant(Qmember);
    push_optimized_constant(Qlist);
    add_grammar_rules_function(regenerate_optimized_constant(list(16,
	    string_constant_112,string_constant_113,string_constant_114,
	    string_constant_115,string_constant_116,string_constant_117,
	    string_constant_118,string_constant_119,string_constant_120,
	    string_constant_121,string_constant_122,string_constant_123,
	    string_constant_124,string_constant_125,string_constant_126,
	    string_constant_127)));
    Qaverage = STATIC_SYMBOL("AVERAGE",AB_package);
    Qaggregated_average = STATIC_SYMBOL("AGGREGATED-AVERAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qpatch_aggregator_scope,
	    STATIC_FUNCTION(patch_aggregator_scope,NIL,FALSE,1,1));
}
