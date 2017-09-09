/* gram4.c
 * Input file:  grammar4.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram4.h"


static Object Qnupec_synchronize;  /* nupec-synchronize */

/* FIX-NUPEC-SYNCHRONIZE */
Object fix_nupec_synchronize(form)
    Object form;
{
    Object reference_list, fixed_reference_list, unique_designations, classes;
    Object reference, ab_loop_list_;

    x_note_fn_call(197,0);
    reference_list = THIRD(form);
    fixed_reference_list = CONSP(reference_list) && EQ(CAR(reference_list),
	    Qand) ? CDR(reference_list) : phrase_cons(reference_list,Nil);
    unique_designations = Nil;
    classes = Nil;
    reference = Nil;
    ab_loop_list_ = fixed_reference_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    reference = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(reference) && EQ(CAR(reference),Qevery))
	classes = nconc2(classes,phrase_cons(SECOND(reference),Nil));
    else
	unique_designations = nconc2(unique_designations,
		phrase_cons(reference,Nil));
    goto next_loop;
  end_loop:
    return phrase_list_4(Qnupec_synchronize,SECOND(form),
	    unique_designations,classes);
    return VALUES_1(Qnil);
}

static Object Qmouse;              /* mouse */

/* REJECT-TRANSFER-TO-THE-MOUSE-OF */
Object reject_transfer_to_the_mouse_of(phrase)
    Object phrase;
{
    Object destination;

    x_note_fn_call(197,1);
    destination = THIRD(phrase);
    if (CONSP(destination) && EQ(FIRST(destination),Qthe) && 
	    EQ(SECOND(destination),Qmouse))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(phrase);
}

static Object Qchange_nth_element_no_array_or_list;  /* change-nth-element-no-array-or-list */

/* VALIDATE-CHANGE-NTH-ELEMENT-PARSE */
Object validate_change_nth_element_parse(parse)
    Object parse;
{
    x_note_fn_call(197,2);
    if (validate_change_nth_element_parse_1(SECOND(parse)))
	return VALUES_1(parse);
    else
	return VALUES_2(Bad_phrase,Qchange_nth_element_no_array_or_list);
}

static Object Qnth_element;        /* nth-element */

/* VALIDATE-CHANGE-NTH-ELEMENT-PARSE-1 */
Object validate_change_nth_element_parse_1(designation_parse)
    Object designation_parse;
{
    Object gensymed_symbol, designation_quantifier_qm, designation_role_qm;
    Object designation_first_domain_qm, designation_second_domain_qm;

    x_note_fn_call(197,3);
    if ( !TRUEP(designation_parse) ||  !LISTP(designation_parse))
	return VALUES_1(Nil);
    else {
	gensymed_symbol = designation_parse;
	designation_quantifier_qm = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	designation_role_qm = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	designation_first_domain_qm = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	designation_second_domain_qm = CAR(gensymed_symbol);
	if (EQ(designation_quantifier_qm,Qthe) && 
		CONSP(designation_role_qm) && 
		EQ(M_CAR(designation_role_qm),Qnth_element) && 
		designation_first_domain_qm && designation_second_domain_qm)
	    return VALUES_1(T);
	else
	    return VALUES_1(Nil);
    }
}

static Object Qcm;                 /* \, */

/* CONVERT-CONNECTION-DETAILS-SPECIFIERS-TO-CANONICAL-FORM */
Object convert_connection_details_specifiers_to_canonical_form(connection_details_specifiers)
    Object connection_details_specifiers;
{
    Object canonical_form_for_details_specifiers, connection_details_specifier;
    Object ab_loop_list_;

    x_note_fn_call(197,4);
    canonical_form_for_details_specifiers = phrase_list_3(Nil,Nil,Nil);
    if (EQ(CAR(connection_details_specifiers),Qcm)) {
	connection_details_specifier = Nil;
	ab_loop_list_ = CDR(connection_details_specifiers);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	connection_details_specifier = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	put_connection_details_specifier_into_canonical_form(connection_details_specifier,
		canonical_form_for_details_specifiers);
	goto next_loop;
      end_loop:;
    }
    else
	put_connection_details_specifier_into_canonical_form(connection_details_specifiers,
		canonical_form_for_details_specifiers);
    return VALUES_1(canonical_form_for_details_specifiers);
}

/* CONNECTION-VERTICES-ARE-CONSTANT-LIST? */
Object connection_vertices_are_constant_list_qm(vertices)
    Object vertices;
{
    Object temp;

    x_note_fn_call(197,5);
    if (CONSP(vertices)) {
	temp = CAR(vertices);
	return VALUES_1(NUMBERP(temp) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qwith_style;         /* with-style */

static Object Qwith_direction;     /* with-direction */

static Object Qwith_vertices;      /* with-vertices */

/* PUT-CONNECTION-DETAILS-SPECIFIER-INTO-CANONICAL-FORM */
Object put_connection_details_specifier_into_canonical_form(connection_details_specifier,
	    canonical_form_for_details_specifiers)
    Object connection_details_specifier, canonical_form_for_details_specifiers;
{
    Object temp, temp_1;

    x_note_fn_call(197,6);
    temp = CAR(connection_details_specifier);
    if (EQ(temp,Qwith_style)) {
	temp_1 = SECOND(connection_details_specifier);
	return VALUES_1(M_FIRST(canonical_form_for_details_specifiers) = 
		temp_1);
    }
    else if (EQ(temp,Qwith_direction)) {
	temp_1 = SECOND(connection_details_specifier);
	return VALUES_1(M_SECOND(canonical_form_for_details_specifiers) = 
		temp_1);
    }
    else if (EQ(temp,Qwith_vertices)) {
	temp_1 = 
		connection_vertices_are_constant_list_qm(CDR(connection_details_specifier)) 
		? CDR(connection_details_specifier) : 
		SECOND(connection_details_specifier);
	return VALUES_1(M_THIRD(canonical_form_for_details_specifiers) = 
		temp_1);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

/* COLOR-OR-METACOLOR-P */
Object color_or_metacolor_p(candidate_color)
    Object candidate_color;
{
    Object temp;

    x_note_fn_call(197,7);
    temp = semi_open_category_p(2,candidate_color,list_constant);
    if (temp)
	return VALUES_1(temp);
    else
	return rgb_color_p(candidate_color);
}

static Object Qcopy;               /* copy */

static Object Qinherited;          /* inherited */

/* ILLEGAL-REGION-NAME-P */
Object illegal_region_name_p(candidate_region_name)
    Object candidate_region_name;
{
    Object temp;

    x_note_fn_call(197,8);
    temp = EQ(candidate_region_name,Qcopy) ? T : Nil;
    if (temp);
    else
	temp = EQ(candidate_region_name,Qinherited) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return color_or_metacolor_p(candidate_region_name);
}

static Object Qregion_cannot_be_the_symbol_copy;  /* region-cannot-be-the-symbol-copy */

static Object Qregion_cannot_be_the_symbol_inherited;  /* region-cannot-be-the-symbol-inherited */

static Object Qregion_cannot_be_a_color_or_metacolor;  /* region-cannot-be-a-color-or-metacolor */

/* FILTER-OUT-ILLEGAL-REGION-NAMES */
Object filter_out_illegal_region_names(candidate_region_name)
    Object candidate_region_name;
{
    x_note_fn_call(197,9);
    if (EQ(candidate_region_name,Qcopy))
	return VALUES_2(Bad_phrase,Qregion_cannot_be_the_symbol_copy);
    else if (EQ(candidate_region_name,Qinherited))
	return VALUES_2(Bad_phrase,Qregion_cannot_be_the_symbol_inherited);
    else if (color_or_metacolor_p(candidate_region_name))
	return VALUES_2(Bad_phrase,Qregion_cannot_be_a_color_or_metacolor);
    else
	return VALUES_1(candidate_region_name);
}

static Object Qcolor_cannot_be_the_symbol_inherited;  /* color-cannot-be-the-symbol-inherited */

/* FILTER-OUT-ILLEGAL-COLOR-NAMES */
Object filter_out_illegal_color_names(candidate_color_name)
    Object candidate_color_name;
{
    x_note_fn_call(197,10);
    if (EQ(candidate_color_name,Qinherited))
	return VALUES_2(Bad_phrase,Qcolor_cannot_be_the_symbol_inherited);
    else
	return VALUES_1(candidate_color_name);
}

static Object Qpriority;           /* priority */

static Object Qinterval;           /* interval */

static Object Qacross;             /* across */

static Object Qstart;              /* start */

static Object Qstart_thread;       /* start-thread */

/* FIX-START-ACTION */
Object fix_start_action(form)
    Object form;
{
    Object gensymed_symbol, kind, proc, args, fourth_1, fifth_1, sixth_1;
    Object priority, interval, across, gensymed_symbol_1;

    x_note_fn_call(197,11);
    gensymed_symbol = form;
    kind = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    proc = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    args = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    fourth_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    fifth_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    sixth_1 = CAR(gensymed_symbol);
    if (fourth_1 && EQ(CAR(fourth_1),Qpriority))
	priority = SECOND(fourth_1);
    else if (fifth_1 && EQ(CAR(fifth_1),Qpriority))
	priority = SECOND(fifth_1);
    else if (sixth_1 && EQ(CAR(sixth_1),Qpriority))
	priority = SECOND(sixth_1);
    else
	priority = Nil;
    if (fourth_1 && EQ(CAR(fourth_1),Qinterval))
	interval = SECOND(fourth_1);
    else if (fifth_1 && EQ(CAR(fifth_1),Qinterval))
	interval = SECOND(fifth_1);
    else if (sixth_1 && EQ(CAR(sixth_1),Qinterval))
	interval = SECOND(sixth_1);
    else
	interval = Nil;
    if (fourth_1 && EQ(CAR(fourth_1),Qacross))
	across = SECOND(fourth_1);
    else if (fifth_1 && EQ(CAR(fifth_1),Qacross))
	across = SECOND(fifth_1);
    else if (sixth_1 && EQ(CAR(sixth_1),Qacross))
	across = SECOND(sixth_1);
    else
	across = Nil;
    if (EQ(kind,Qstart)) {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qstart;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = proc;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = args;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = priority;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = interval;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = across;
	return VALUES_1(gensymed_symbol);
    }
    else {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qstart_thread;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = proc;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = args;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = priority;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = interval;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = across;
	return VALUES_1(gensymed_symbol);
    }
}

static Object Qin_order;           /* in-order */

static Object Qsimultaneously;     /* simultaneously */

/* FIX-ACTION-LIST */
Object fix_action_list(rule)
    Object rule;
{
    Object action_or_actions, action_or_symbol, third_new_value;

    x_note_fn_call(197,12);
    action_or_actions = THIRD(rule);
    action_or_symbol = FIRST(action_or_actions);
    if (EQ(action_or_symbol,Qin_order));
    else if (EQ(action_or_symbol,Qand))
	M_FIRST(action_or_actions) = Qsimultaneously;
    else {
	third_new_value = phrase_list_2(Qsimultaneously,action_or_actions);
	M_THIRD(rule) = third_new_value;
    }
    return VALUES_1(rule);
}

/* FIX-IQE */
Object fix_iqe(form,n_1)
    Object form, n_1;
{
    Object iqe, nth_new_value;

    x_note_fn_call(197,13);
    iqe = nth(n_1,form);
    if (SYMBOLP(iqe)) {
	nth_new_value = phrase_list_2(Qquote,iqe);
	M_NTH(n_1,form) = nth_new_value;
    }
    return VALUES_1(form);
}

/* UNLIST-1 */
Object unlist_1(form)
    Object form;
{
    x_note_fn_call(197,14);
    return phrase_cons(CAAR(form),CDR(form));
}

/* UNLIST-1-2 */
Object unlist_1_2(form)
    Object form;
{
    x_note_fn_call(197,15);
    return phrase_cons(CAAR(form),phrase_cons(CAADR(form),CDDR(form)));
}

/* CAR-2-1 */
Object car_2_1(form)
    Object form;
{
    x_note_fn_call(197,16);
    return phrase_cons(phrase_list_2(CAAR(form),CAADAR(form)),Nil);
}

static Object list_constant_1;     /* # */

static Object Qis;                 /* is */

/* CHOOSE-IS-OR-= */
Object choose_is_or_eq(expression)
    Object expression;
{
    Object temp, form, temp_1, first_new_value;

    x_note_fn_call(197,17);
    if (memq_function(CAR(expression),list_constant_1)) {
	temp = SECOND(expression);
	form = SECOND(temp);
	if ( !(ATOM(form) ? form && SYMBOLP(form) : 
		TRUEP(designation_operator_or_giver_of_value_p(CAR(form))))) {
	    temp_1 = SECOND(expression);
	    temp = SECOND(expression);
	    first_new_value = EQ(FIRST(temp),Qis) ? Qnum_eq : Qnum_ne;
	    M_FIRST(temp_1) = first_new_value;
	}
    }
    else {
	form = SECOND(expression);
	if ( !(ATOM(form) ? form && SYMBOLP(form) : 
		TRUEP(designation_operator_or_giver_of_value_p(CAR(form))))) {
	    temp_1 = EQ(FIRST(expression),Qis) ? Qnum_eq : Qnum_ne;
	    M_FIRST(expression) = temp_1;
	}
    }
    return VALUES_1(expression);
}

/* PUT-DESIGNATION-IN-QUALIFIER */
Object put_designation_in_qualifier(factor)
    Object factor;
{
    Object second_arg, second_new_value;

    x_note_fn_call(197,18);
    second_arg = CDR(factor);
    second_new_value = CAR(factor);
    M_SECOND(second_arg) = second_new_value;
    return VALUES_1(CDR(factor));
}

static Object list_constant_2;     /* # */

/* FUZZY-COMPARATOR-REPARSER */
Object fuzzy_comparator_reparser(parsed_fuzzy)
    Object parsed_fuzzy;
{
    Object temp, car_new_value;

    x_note_fn_call(197,19);
    temp = assq_function(CAR(parsed_fuzzy),list_constant_2);
    car_new_value = CDR(temp);
    M_CAR(parsed_fuzzy) = car_new_value;
    return VALUES_1(parsed_fuzzy);
}

static Object Qcategory;           /* category */

/* CATEGORY-HACK */
Object category_hack(invoke_action)
    Object invoke_action;
{
    Object temp, second_new_value;

    x_note_fn_call(197,20);
    temp = SECOND(invoke_action);
    if (SYMBOLP(temp))
	temp = phrase_cons(SECOND(invoke_action),Nil);
    else {
	temp = SECOND(invoke_action);
	temp = CDR(temp);
    }
    second_new_value = phrase_cons(Qcategory,temp);
    M_SECOND(invoke_action) = second_new_value;
    return VALUES_1(invoke_action);
}

static Object list_constant_3;     /* # */

/* SYMBOL-CANNOT-BE-TRUE-FALSE-OR-NOT */
Object symbol_cannot_be_true_false_or_not(form)
    Object form;
{
    Object temp;

    x_note_fn_call(197,21);
    temp = THIRD(form);
    if ( !TRUEP(memq_function(SECOND(temp),list_constant_3)))
	return VALUES_1(form);
    else
	return VALUES_1(Bad_phrase);
}

static Object list_constant_4;     /* # */

static Object Qfixed_format;       /* fixed-format */

/* CHECK-DDD-DDDD-FORMAT */
Object check_ddd_dddd_format(message_expression)
    Object message_expression;
{
    Object left, right, temp, cdddr_new_value;
    Object result;

    x_note_fn_call(197,22);
    if (memq_function(THIRD(message_expression),list_constant_4))
	return VALUES_1(message_expression);
    else {
	result = decode_format(THIRD(message_expression));
	MVS_2(result,left,right);
	if ( !TRUEP(left))
	    return VALUES_1(Bad_phrase);
	else {
	    temp = message_expression;
	    M_FIRST(message_expression) = Qfixed_format;
	    M_THIRD(message_expression) = left;
	    cdddr_new_value = phrase_cons(right,Nil);
	    M_CDDDR(message_expression) = cdddr_new_value;
	    return VALUES_1(temp);
	}
    }
}

static Object list_constant_5;     /* # */

/* DECODE-FORMAT */
Object decode_format(symbol)
    Object symbol;
{
    Object left_count, bad_char, format_1, length_1, char_1, temp;
    SI_Long index_1, ab_loop_bind_, tally;

    x_note_fn_call(197,23);
    left_count = Nil;
    bad_char = Nil;
    format_1 = symbol_name_text_string(symbol);
    length_1 = text_string_length(format_1);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    char_1 = Nil;
    tally = (SI_Long)0L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(format_1,index_1));
    if ( !TRUEP(wide_character_member(char_1,list_constant_5)))
	bad_char = T;
    if (IFIX(char_1) == (SI_Long)46L)
	tally = tally + (SI_Long)1L;
    if (IFIX(char_1) == (SI_Long)46L)
	left_count = FIX(index_1);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (bad_char || tally != (SI_Long)1L)
	return VALUES_1(Nil);
    else {
	temp = FIXNUM_SUB1(FIXNUM_MINUS(length_1,left_count));
	return VALUES_2(left_count,temp);
    }
    return VALUES_1(Qnil);
}

/* FIX-IN-ORDER-ACTION-LIST */
Object fix_in_order_action_list(form)
    Object form;
{
    Object temp;

    x_note_fn_call(197,24);
    temp = SECOND(form);
    return phrase_cons(FIRST(form),CDR(temp));
}

void grammar4_INIT()
{
    Object Qfix_in_order_action_list, AB_package, Qcheck_ddd_dddd_format;
    Object Qseconds, Qtime_stamp, Qsymbol_cannot_be_true_false_or_not, Qfalse;
    Object Qtrue, Qcategory_hack, Qfuzzy_comparator_reparser, list_constant_9;
    Object list_constant_8, list_constant_7, list_constant_6, Qfuzzy_lt;
    Object Qfuzzy_gt, Qfuzzy_not_eq, Qfuzzy_eq, Qput_designation_in_qualifier;
    Object Qchoose_is_or_eq, Qvalue_of, Qcurrent_value_of, Qcar_2_1;
    Object Qunlist_1_2, Qunlist_1, Qfix_iqe, Qfix_action_list;
    Object Qfix_start_action, Qfilter_out_illegal_color_names;
    Object Qfilter_out_illegal_region_names, Qcolor_or_metacolor_p, Qmetacolor;
    Object Qcolor, Qconvert_connection_details_specifiers_to_canonical_form;
    Object string_constant_69, string_constant_68, string_constant_67;
    Object string_constant_66, string_constant_65, string_constant_64;
    Object string_constant_63, string_constant_62, string_constant_61;
    Object string_constant_60, string_constant_59, string_constant_58;
    Object string_constant_57, string_constant_56, string_constant_55;
    Object string_constant_54, Qfix_line_list, Qsimplify_associative_operation;
    Object Qvalidate_change_nth_element_parse;
    Object Qreject_transfer_to_the_mouse_of, string_constant_53;
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
    Object string_constant_4, Qg2_list_remove, Qend;
    Object Qrestrict_if_slot_edit_feature, Qicon_color, Qnil_function;
    Object string_constant_3, string_constant_2, Qcreate_explanation;
    Object Qfix_nupec_synchronize, string_constant_1, string_constant;

    x_note_fn_call(197,25);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant = 
	    STATIC_STRING("1r1m83-rgy83-rfy1n83-rgy1n83-rfy1m9k83-ty83-rfy1n83-tyln1o83-rgy1n83-rfy1m9k83vy83-rhy1n83-tyln9l1n83-rhy1o83-rfy1m9k83vy1m9k83-");
    string_constant_1 = 
	    STATIC_STRING("ty83-rfy1n83-tylo1o83-rhy1n83-rfy1m9k83vy83-rhy1n83-tyln9l1m83-rfy830By1m83-rfy1m1m9k9m83-Gy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qevery);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant,
	    string_constant_1)));
    Qnupec_synchronize = STATIC_SYMBOL("NUPEC-SYNCHRONIZE",AB_package);
    Qfix_nupec_synchronize = STATIC_SYMBOL("FIX-NUPEC-SYNCHRONIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_nupec_synchronize,
	    STATIC_FUNCTION(fix_nupec_synchronize,NIL,FALSE,1,1));
    Qcreate_explanation = STATIC_SYMBOL("CREATE-EXPLANATION",AB_package);
    string_constant_2 = 
	    STATIC_STRING("1m1n836Yy1p1m9k83Iqy83=Zy1m9k838Hy1m9k83=Iy830By1m9lp1n836Yy1q1m9k83Iqy83=Zy1m9k838Hy83*Zy1m9k83=Iy830By1n9lqo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qcreate_explanation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_2));
    string_constant_3 = 
	    STATIC_STRING("1n1o83E5y1n836Yy1m9k83-ty83pOy1n83-tyln9l1m83E5y836Yy1n83E5y1m9k83Zy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_3));
    Qreject_transfer_to_the_mouse_of = 
	    STATIC_SYMBOL("REJECT-TRANSFER-TO-THE-MOUSE-OF",AB_package);
    Qfix_iqe = STATIC_SYMBOL("FIX-IQE",AB_package);
    Qfilter_out_illegal_color_names = 
	    STATIC_SYMBOL("FILTER-OUT-ILLEGAL-COLOR-NAMES",AB_package);
    Qnil_function = STATIC_SYMBOL("NIL-FUNCTION",AB_package);
    Qfilter_out_illegal_region_names = 
	    STATIC_SYMBOL("FILTER-OUT-ILLEGAL-REGION-NAMES",AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qvalidate_change_nth_element_parse = 
	    STATIC_SYMBOL("VALIDATE-CHANGE-NTH-ELEMENT-PARSE",AB_package);
    Qrestrict_if_slot_edit_feature = 
	    STATIC_SYMBOL("RESTRICT-IF-SLOT-EDIT-FEATURE",AB_package);
    Qfix_start_action = STATIC_SYMBOL("FIX-START-ACTION",AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    Qg2_list_remove = STATIC_SYMBOL("G2-LIST-REMOVE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_list_remove,STATIC_FUNCTION(g2_list_remove,NIL,
	    FALSE,3,3));
    string_constant_4 = 
	    STATIC_STRING("13-ky1n836Yy1s1m9k83*py8330y1m9k83*ty1m9k83-9y83=xy1m9k83vy83=xy1m9k83-Ay1o83*pympr1n836Yy1s1m9k83*py8330y1m9k83=3y1m9k83-9y83=x");
    string_constant_5 = 
	    STATIC_STRING("y1m9k83vy83=xy1m9k83-Ay1o83-oTympr1o836Yy1o1m9k832oy8330y1m9k83=3y8330y1n832oymo9l1o836Yy1u1m9k832oy8330y1m9k83=3y8330y1m9k83=Gy");
    string_constant_6 = 
	    STATIC_STRING("1m9k83-9y83=xy1m9k83vy83=xy1m9k83-Ay1p832oymort9l1n836Yy1r1m9k832oy8330y1m9k83=3y1m9k9m1m9k83E-y1m9k83-Ty8330y1n832oymr1n836Yy1n");
    string_constant_7 = 
	    STATIC_STRING("1m9k832oy8330y1m9k83-8-y1m832oym1n836Yy1p1m9k83-nFy8330y1m9k83*ty83=xy1m9k83-Qdy1n83-nFymo1n836Yy1r1m9k83-nFy8330y1m9k83=3y1m9k9");
    string_constant_8 = 
	    STATIC_STRING("m1m9k83-Xhy83=xy1m9k83-Qdy1n83-oRymq1m836Yy1m1m9k837cy8330y1m83-Eky1m9k83-nMy1m836Yy83-Mxy1o83-Mxy1r1m9k83=cy1m9k9m83g*y1m9k83-T");
    string_constant_9 = 
	    STATIC_STRING("y8330y1m9k83=3y83-v6y1o83-M*ypr1m9kn1m9nm1o83-Mxy1s1m9k83=cy1m9k9m83Yky83-*sy1m9k83-Ty8330y1m9k83=3y83-v6y1o83-M*yqs1m9kn1m9nm1n");
    string_constant_10 = 
	    STATIC_STRING("83-Mxy1s1m9k83=cy1m9k9m1m9k83-N7y1m9k83-Ty8330y1m9k83-qBy1m9k8319y83-Mwy1n83-M=yps1n83-Mxy1s1m9k83=cy1m9k9m1m9k83-N7y1m9k83-Ty83");
    string_constant_11 = 
	    STATIC_STRING("30y1m9k83-qBy1m9k8319y83-N+y2m83-M=yps1n83-Mwy1n83-lqy1m9k83*Iy83*uy1n1m9kl9kn1n83-Mwy1n83-lqy1m9k9o83=xy2l1m9kln1o83-N+y83-N-yl");
    string_constant_12 = 
	    STATIC_STRING("9p1n83-N-y1n83-Mwy1m9k83vy83-Mwy1nmln1o83-N-y1n83-Mwy1m9k83vy83-N-y1nmln9q1m83-v6y83=xy1m83-v6y83*xy1m83-v6y83-eay1m83*uy83*xy1m");
    string_constant_13 = 
	    STATIC_STRING("83*uy83-eay1o83-N=y83*uyl9r1o83-N=y1m9k83S6y09s1o83Yky83-6yl9t1n83Efy83Ykyl1o83Efy1m9k83Zy09s1m83-BSy83*uy1m83-BSy83Yky1m83-*sy1");
    string_constant_14 = 
	    STATIC_STRING("m9k9u1m83-*sy1m9k83-Dry1m83-lqy83Yky1m83-lqy83g*y1n836Yy1r1m9k83=cy1m9k9m1m9k837iy1m9k83-Ty8330y1m9k83=3y83=xy1o83-M7yp1m9knr1n8");
    string_constant_15 = 
	    STATIC_STRING("36Yy1r1m9k83=cy1m9k9m1m9k831ay1m9k83-Ty8330y1m9k83=3y83=xy1o83-M7yp1m9knr1n836Yy1r1m9k83=cy1m9k9m1m9k83nBy1m9k83-Ty8330y1m9k83=3");
    string_constant_16 = 
	    STATIC_STRING("y1m9k83Dmy1o83-M7yp1m9kn1m9kr1n836Yy1r1m9k83=cy1m9k9m1m9k83=hy1m9k83-Ty8330y1m9k83=3y83=xy1o83-M7yp1m9knr1n836Yy1r1m9k83=cy1m9k9");
    string_constant_17 = 
	    STATIC_STRING("m1m9k83Gy1m9k83-Ty8330y1m9k83=3y83=xy1n83-M8ypr1n83-Luy1o1m9k9m1m9k83=cy1m9k83-Ty8330y1n9m83=cyo1n836Yy1r1m9k83=cy1m9k9m1m9k83Gy");
    string_constant_18 = 
	    STATIC_STRING("1m9k83-Ty83-Luy1m9k83=3y83=xy1n83-M8ypr1n836Yy1r1m9k83=cy1m9k9m1m9k83Gy1m9k83-Ty83nLy1m9k83=3y83=xy1n83-M8ypr1o836Yy1o1m9k83=cy8");
    string_constant_19 = 
	    STATIC_STRING("3-7ay1m9k9o83=xy1n83-M4ymo9v1o836Yy1o1m9k83=cy83-7ay1m9k9o831Py1n83-M4ymo9v1o836Yy1q1m9k83=cy83-7ay1m9k83=3y1m9k83-*0y1m9k83=Ty1");
    string_constant_20 = 
	    STATIC_STRING("m9k83*ly1m83-M5ym9v1o836Yy1s1m9k83=cy1m9k9w83-Gy1m9k832sy83=xy1m9k832ty1m9k9o831Py1o83-M4y1mmnps1n9x83=Vy8330y1o836Yy1s1m9k83=cy");
    string_constant_21 = 
	    STATIC_STRING("1m9k9w83-Gy1m9k832sy83=xy1m9k832ty1m9k9o83=xy1o83-M4y1mmnps1n9x83=Vy8330y1o836Yy1n1m9k836Gy83YHy83-kMy1nlmn9y1o836Yy1o1m9k836Gy8");
    string_constant_22 = 
	    STATIC_STRING("3YHy1m9k83-9y1m9k83-Ay1nlm09y1o836Yy1o1m9k836Gy83YHy83-kMy83-qhy2nlmno9y1o836Yy1p1m9k836Gy83YHy1m9k83-9y1m9k83-Ay83-qhy2nlm0p9y1");
    string_constant_23 = 
	    STATIC_STRING("m83YHy8330y1m83YHy834Ry1n83-qhy1n1m9k83=Gy1m9k83-Yy83=xy1l1m83-Yyn1n83-qhy1m1m9k835+y83=xy1l1m83-oym1n83-qhy1p1m9k83=Gy1m9k83-Yy");
    string_constant_24 = 
	    STATIC_STRING("83=xy1m9k835+y83=xy1m1m83-Yyn1m83-oyp1n83-qhy1m1m9k83f0y830By1l1m83f0ym1n83-qhy1p1m9k83=Gy1m9k83-Yy83=xy1m9k83f0y830By1m1m83-Yyn");
    string_constant_25 = 
	    STATIC_STRING("1m83f0yp1n83-qhy1o1m9k835+y83=xy1m9k83f0y830By1m1m83-oym1m83f0yo1n83-qhy1r1m9k83=Gy1m9k83-Yy83=xy1m9k835+y83=xy1m9k83f0y830By1n1");
    string_constant_26 = 
	    STATIC_STRING("m83-Yyn1m83-oyp1m83f0yr1m83-kLy83=xy1m83-kLy831Py1m83-kLy8330y1n83-kMy1n1m9k83-9y83-kLy1m9k83-Ay1lm1n83-kMy1o1m9k83-9y83-kLy1m9k");
    string_constant_27 = 
	    STATIC_STRING("83vy83-kNy2lmo1n83-kNy1m83-kLy1m9k83-Ay1ll1n83-kNy1n83-kLy1m9k83vy83-kNy2lln1n836Yy1n1m9k83Iqy83=Zy83-Gy1m83Iqy1m9kn1n836Yy1o1m9");
    string_constant_28 = 
	    STATIC_STRING("k83Iqy83=Zy83-Gy83*Zy1n83Iqy1m9kno1n836Yy1t1m9k83Iqy83=Zy1m9k831Ly1m9k83-Ty1m9k9m1m9k83-Gy1m9k832dy1m9k83*ty83=xy1m83Iqyt1n836Yy");
    string_constant_29 = 
	    STATIC_STRING("1u1m9k83Iqy83=Zy1m9k831Ly83*Zy1m9k83-Ty1m9k9m1m9k83-Gy1m9k832dy1m9k83*ty83=xy1n83Iqyuo1n836Yy1q1m9k83Iqy83=Zy83-Gy1m9k83*ty1m9k8");
    string_constant_30 = 
	    STATIC_STRING("3-Mky830By1n83-PKy1m9knq1n836Yy1r1m9k83Iqy83=Zy83-Gy83*Zy1m9k83*ty1m9k83-Mky830By1o83-PKy1m9knro1m836Yy1m1m9k9z8330y1n836Yy1n1m9");
    string_constant_31 = 
	    STATIC_STRING("k83-dVy8330y1m9k83-ioy1m83-dWym1n836Yy1n1m9k83-dVy8330y1m9k83-toy1m83-dYym1n836Yy1q1m9k83-dVy830By1m9k9m1m9k83b5y1m9k83-Ty830By1");
    string_constant_32 = 
	    STATIC_STRING("n83-dXymq1n836Yy1u1m9k83-=by83=xy1m9k83=Gy1m9k9m1m9k83HBy1m9k83-Ty1m9k9m83xcy1m9k93Cy8330y1p83-VNyum083HBy1n836Yy1u1m9k83-=by831");
    string_constant_33 = 
	    STATIC_STRING("Py1m9k83=Gy1m9k9m1m9k83HBy1m9k83-Ty1m9k9m1m9k83-hy1m9k93Cy8330y1p83-VNyum083HBy1n836Yy1u1m9k83-=by8330y1m9k83=Gy1m9k9m1m9k83HBy1");
    string_constant_34 = 
	    STATIC_STRING("m9k83-Ty1m9k9m83-Gy1m9k93Cy8330y1p83-VNyum083HBy1n836Yy1r1m9k83-=by83=xy1m9k83=Gy1m9k9m1m9k83HBy1m9k83-Ty8330y1p83-VNyrm083HBy1n");
    string_constant_35 = 
	    STATIC_STRING("836Yy1r1m9k83-=by831Py1m9k83=Gy1m9k9m1m9k83HBy1m9k83-Ty8330y1p83-VNyrm083HBy1n836Yy1r1m9k83-=by8330y1m9k83=Gy1m9k9m1m9k83HBy1m9k");
    string_constant_36 = 
	    STATIC_STRING("83-Ty8330y1p83-VNyrm083HBy1n836Yy1u1m9k83-=by83=xy1m9k83=Gy1m9k9m1m9k93Dy1m9k83-Ty1m9k9m83xcy1m9k93Cy8330y1p83-VNyum093Dy1n836Yy");
    string_constant_37 = 
	    STATIC_STRING("1u1m9k83-=by831Py1m9k83=Gy1m9k9m1m9k93Dy1m9k83-Ty1m9k9m1m9k83-hy1m9k93Cy8330y1p83-VNyum093Dy1n836Yy1u1m9k83-=by8330y1m9k83=Gy1m9");
    string_constant_38 = 
	    STATIC_STRING("k9m1m9k93Dy1m9k83-Ty1m9k9m83-Gy1m9k93Cy8330y1p83-VNyum093Dy1n836Yy1r1m9k83-=by83=xy1m9k83=Gy1m9k9m1m9k93Dy1m9k83-Ty8330y1p83-VNy");
    string_constant_39 = 
	    STATIC_STRING("rm093Dy1n836Yy1r1m9k83-=by831Py1m9k83=Gy1m9k9m1m9k93Dy1m9k83-Ty8330y1p83-VNyrm093Dy1n836Yy1r1m9k83-=by8330y1m9k83=Gy1m9k9m1m9k93");
    string_constant_40 = 
	    STATIC_STRING("Dy1m9k83-Ty8330y1p83-VNyrm093Dy1n836Yy1t1m9k83-=by83=xy1m9k83HAy83=py1m9k83*Xy1m9k9m83xcy1m9k93Cy8330y1p83-VNytmo83HAy1n836Yy1t1");
    string_constant_41 = 
	    STATIC_STRING("m9k83-=by831Py1m9k83HAy831Py1m9k83*Xy1m9k9m1m9k83-hy1m9k93Cy8330y1p83-VNytmo83HAy1n836Yy1t1m9k83-=by8330y1m9k83HAy8330y1m9k83*Xy");
    string_constant_42 = 
	    STATIC_STRING("1m9k9m83-Gy1m9k93Cy8330y1p83-VNytmo83HAy1n836Yy1q1m9k83-=by83=xy1m9k83HAy83=py1m9k83*Xy8330y1p83-VNyqmo83HAy1n836Yy1q1m9k83-=by8");
    string_constant_43 = 
	    STATIC_STRING("31Py1m9k83HAy831Py1m9k83*Xy8330y1p83-VNyqmo83HAy1n836Yy1q1m9k83-=by8330y1m9k83HAy8330y1m9k83*Xy8330y1p83-VNyqmo83HAy1n836Yy1r1m9");
    string_constant_44 = 
	    STATIC_STRING("k83-=by83=xy1m9k83HAy1m9k83Buy83=py1m9k83-Ty8330y1p83-VNyrmp83-Khy1n836Yy1t1m9k83-=by83=xy1m9k835+y83=py1m9k83*Xy1m9k9m83xcy1m9k");
    string_constant_45 = 
	    STATIC_STRING("93Cy8330y1p83-VNytmo835+y1n836Yy1t1m9k83-=by831Py1m9k835+y831Py1m9k83*Xy1m9k9m1m9k83-hy1m9k93Cy8330y1p83-VNytmo835+y1n836Yy1t1m9");
    string_constant_46 = 
	    STATIC_STRING("k83-=by8330y1m9k835+y8330y1m9k83*Xy1m9k9m83-Gy1m9k93Cy8330y1p83-VNytmo835+y1n836Yy1q1m9k83-=by83=xy1m9k835+y83=py1m9k83*Xy8330y1");
    string_constant_47 = 
	    STATIC_STRING("p83-VNyqmo835+y1n836Yy1r1m9k83-=by83=xy1m9k835+y1m9k83Buy83=py1m9k83-Ty8330y1p83-VNyrmp83-JLy1n836Yy1q1m9k83-=by831Py1m9k835+y83");
    string_constant_48 = 
	    STATIC_STRING("1Py1m9k83*Xy8330y1p83-VNyqmo835+y1n836Yy1q1m9k83-=by8330y1m9k835+y8330y1m9k83*Xy8330y1p83-VNyqmo835+y1n836Yy1q1m9k93Ey1m9k9m1m9k");
    string_constant_49 = 
	    STATIC_STRING("93Fy83-Xy1m9k832+y8330y1p93Gyq0o93Fy1n836Yy1q1m9k93Ey1m9k9m1m9k93Hy83-Xy1m9k832+y8330y1p93Gyq0o93Hy1n836Yy1r1m9k93Ey83=xy1m9k832");
    string_constant_50 = 
	    STATIC_STRING("+y1m9k9m83xcy1m9k93Cy8330y1p93Gyrm083Buy1n836Yy1r1m9k93Ey831Py1m9k832+y1m9k9m1m9k83-hy1m9k93Cy8330y1p93Gyrm083Buy1n836Yy1r1m9k93");
    string_constant_51 = 
	    STATIC_STRING("Ey8330y1m9k832+y1m9k9m83-Gy1m9k93Cy8330y1p93Gyrm083Buy1n836Yy1p1m9k93Ey1m9k83Buy83=py1m9k832+y8330y1p93Gypn083-STy1n836Yy1o1m9k9");
    string_constant_52 = 
	    STATIC_STRING("3Ey83=xy1m9k832+y8330y1p93Gyom083Buy1n836Yy1o1m9k93Ey831Py1m9k832+y8330y1p93Gyom083Buy1n836Yy1o1m9k93Ey8330y1m9k832+y8330y1p93Gy");
    string_constant_53 = STATIC_STRING("om083Buy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qreject_transfer_to_the_mouse_of);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qfix_iqe);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfilter_out_illegal_color_names);
    push_optimized_constant(Qnil_function);
    push_optimized_constant(Qfilter_out_illegal_region_names);
    push_optimized_constant(Qicon_color);
    push_optimized_constant(Qvalidate_change_nth_element_parse);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qrestrict_if_slot_edit_feature);
    push_optimized_constant(Qfix_start_action);
    push_optimized_constant(Qdelete);
    push_optimized_constant(Qlist);
    push_optimized_constant(Qend);
    push_optimized_constant(Qremove);
    push_optimized_constant(Qfirst);
    push_optimized_constant(Qg2_list_remove);
    push_optimized_constant(Qlast);
    add_grammar_rules_function(regenerate_optimized_constant(list(50,
	    string_constant_4,string_constant_5,string_constant_6,
	    string_constant_7,string_constant_8,string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20,string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25,string_constant_26,string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30,
	    string_constant_31,string_constant_32,string_constant_33,
	    string_constant_34,string_constant_35,string_constant_36,
	    string_constant_37,string_constant_38,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46,string_constant_47,string_constant_48,
	    string_constant_49,string_constant_50,string_constant_51,
	    string_constant_52,string_constant_53)));
    Qmouse = STATIC_SYMBOL("MOUSE",AB_package);
    SET_SYMBOL_FUNCTION(Qreject_transfer_to_the_mouse_of,
	    STATIC_FUNCTION(reject_transfer_to_the_mouse_of,NIL,FALSE,1,1));
    Qchange_nth_element_no_array_or_list = 
	    STATIC_SYMBOL("CHANGE-NTH-ELEMENT-NO-ARRAY-OR-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qvalidate_change_nth_element_parse,
	    STATIC_FUNCTION(validate_change_nth_element_parse,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qvalidate_change_nth_element_parse);
    Qnth_element = STATIC_SYMBOL("NTH-ELEMENT",AB_package);
    Qconvert_connection_details_specifiers_to_canonical_form = 
	    STATIC_SYMBOL("CONVERT-CONNECTION-DETAILS-SPECIFIERS-TO-CANONICAL-FORM",
	    AB_package);
    Qfix_line_list = STATIC_SYMBOL("FIX-LINE-LIST",AB_package);
    string_constant_54 = 
	    STATIC_STRING("13fy1n836Yy1o1m9k83Iqy83=Zy1m9k83=+y83-Nxy1n83-PLy1m9k83=+yo1n836Yy1p1m9k83Iqy83=Zy1m9k83=+y83*Zy83-Nxy1o83-PLy1m9k83=+ypo1n836Y");
    string_constant_55 = 
	    STATIC_STRING("y1p1m9k83Iqy83=Zy1m9k83=+y83-Nty83-Nxy1n83-PLyop1n836Yy1q1m9k83Iqy83=Zy1m9k83=+y83*Zy83-Nty83-Nxy1o83-PLypqo1n836Yy1p1m9k9l8330y");
    string_constant_56 = 
	    STATIC_STRING("1m9k83-mEy1m9k83=+y1m9k83Vy1olm8k01n836Yy1p1m9k9l8330y1m9k83AUy1m9k83-iny1m9k83-MMy1olm08k1n836Yy1s1m9k9l8330y1m9k83-mEy1m9k83=+");
    string_constant_57 = 
	    STATIC_STRING("y1m9k83Vy1m9k83AUy1m9k83-iny1m9k83-MMy1olm8k8k1n836Yy1s1m9k9l8330y1m9k83AUy1m9k83-iny1m9k83-MMy1m9k83-mEy1m9k83=+y1m9k83Vy1olm8k");
    string_constant_58 = 
	    STATIC_STRING("8k1n83-Nty1n1m9k83-Ty1m9k83-Gy83BOy1m9kn1n83-Nty1q1m9k83-Ty1m9k9m1m9k83-Gy1m9k832dy1m9k83*ty83=xyq1n83-Nxy1p1m9k83Igy1m9k837my83");
    string_constant_59 = 
	    STATIC_STRING("-O0y1m9k83-ty83-O0y1n83-Nrynp1n83-Nxy1q1m9k83Igy1m9k837my83-O0y1m9k83-ty83-O0y83-O-y1o83-Nrynpq1n83-Nxy1n1m9k83Igy1m9k83=3y83-O0");
    string_constant_60 = 
	    STATIC_STRING("y1m83gByn1n83-Nxy1o1m9k83Igy1m9k83=3y83-O0y83-O-y1n83gByno1o83-O-y83-O*yl9n1m83-O*y83-O+y1o83-O*y1n83-O+y1m9k83vy83-O*y1nmln9o1m");
    string_constant_61 = 
	    STATIC_STRING("83-O+y83-O5y1m83-O+y83-O=y1m83-O+y83-O9y1n83-O5y1n1m9k83=Fy1m9k83-Dvy8380y1m83-xFy1m9kn1n83-O5y1q1m9k83=Fy1m9k9m1m9k83-Dvy1m9k83");
    string_constant_62 = 
	    STATIC_STRING("2dy1m9k83*ty83=xy1m83-xFyq1n83-O=y1n1m9k83=Fy1m9k83gjy83gjy1m83-xCy1m9kn1n83-O=y1q1m9k83=Fy1m9k9m1m9k83gjy1m9k832dy1m9k83*ty83=x");
    string_constant_63 = 
	    STATIC_STRING("y1m83-xCyq1o83-O9y1n1m9k83=Fy1m9k83-GTy83-wWy2l83-xGyn9p1n83-wWy83Sy1m9ql1o83-wWy1m83Sy83-wXy1n9qlm9o1m83-wXy83Sy1o83-wXy1m83Sy8");
    string_constant_64 = 
	    STATIC_STRING("3-wXy1n9qlm9o1n83-O9y1q1m9k83=Fy1m9k9m1m9k83-GTy1m9k8344y1m9k83*ty83=xy1m83-xGyq1m8380y1m9k833sy1m8380y1m9k83EEy1n83-O0y1m83-Sfy");
    string_constant_65 = 
	    STATIC_STRING("83-Sgy1mlm1m83-Sfy830By1n83-Sgy1m1m9k83=Gy83-O3y1o83-d9y00m1n83-Sgy1p1m9k83-dAy1m9k83-b7y1m9k83=Gy83-pFy83-jQy1n83-d9yop1n83-Sgy");
    string_constant_66 = 
	    STATIC_STRING("1r1m9k83=Gy83-O3y1m9k83-dAy1m9k83-b7y1m9k83=Gy83-pFy83-jQy1o83-d9yqrm1n83-Sgy1q1m9k83-ghy1m9k83-dAy1m9k83-b7y1m9k83=Gy83-pFy83-j");
    string_constant_67 = 
	    STATIC_STRING("Qy1n83-giypq1n83-Sgy1s1m9k83-ghy1m9k83-dAy1m9k83-b7y1m9k83=Gy83-pFy83-jQy1m9k83=Gy83-O3y1o83-giypqs1n83-O3y839jy1m9kl1n83-O3y1p1");
    string_constant_68 = 
	    STATIC_STRING("m9k9m1m9k83lby1m9k832dy1m9k83*ty83=xyp1n83-pFy83gsy1m9kl1n83-pFy1p1m9k9m1m9k83-pEy1m9k832dy1m9k83*ty83=xyp1m83-jQy83-ey1n83-jQy1");
    string_constant_69 = 
	    STATIC_STRING("q1m9k83=Gy1m9k9m1m9k9r1m9k8344y1m9k83*ty83=xyq");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qdelete);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qconvert_connection_details_specifiers_to_canonical_form);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfix_line_list);
    push_optimized_constant(Qplus);
    push_optimized_constant(Qposition);
    add_grammar_rules_function(regenerate_optimized_constant(list(16,
	    string_constant_54,string_constant_55,string_constant_56,
	    string_constant_57,string_constant_58,string_constant_59,
	    string_constant_60,string_constant_61,string_constant_62,
	    string_constant_63,string_constant_64,string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68,
	    string_constant_69)));
    Qcm = STATIC_SYMBOL(",",AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_connection_details_specifiers_to_canonical_form,
	    STATIC_FUNCTION(convert_connection_details_specifiers_to_canonical_form,
	    NIL,FALSE,1,1));
    Qwith_style = STATIC_SYMBOL("WITH-STYLE",AB_package);
    Qwith_direction = STATIC_SYMBOL("WITH-DIRECTION",AB_package);
    Qwith_vertices = STATIC_SYMBOL("WITH-VERTICES",AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    Qmetacolor = STATIC_SYMBOL("METACOLOR",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qcolor,Qmetacolor);
    Qcolor_or_metacolor_p = STATIC_SYMBOL("COLOR-OR-METACOLOR-P",AB_package);
    SET_SYMBOL_FUNCTION(Qcolor_or_metacolor_p,
	    STATIC_FUNCTION(color_or_metacolor_p,NIL,FALSE,1,1));
    Qcopy = STATIC_SYMBOL("COPY",AB_package);
    Qinherited = STATIC_SYMBOL("INHERITED",AB_package);
    Qregion_cannot_be_the_symbol_copy = 
	    STATIC_SYMBOL("REGION-CANNOT-BE-THE-SYMBOL-COPY",AB_package);
    Qregion_cannot_be_the_symbol_inherited = 
	    STATIC_SYMBOL("REGION-CANNOT-BE-THE-SYMBOL-INHERITED",AB_package);
    Qregion_cannot_be_a_color_or_metacolor = 
	    STATIC_SYMBOL("REGION-CANNOT-BE-A-COLOR-OR-METACOLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_out_illegal_region_names,
	    STATIC_FUNCTION(filter_out_illegal_region_names,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qfilter_out_illegal_region_names);
    Qcolor_cannot_be_the_symbol_inherited = 
	    STATIC_SYMBOL("COLOR-CANNOT-BE-THE-SYMBOL-INHERITED",AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_out_illegal_color_names,
	    STATIC_FUNCTION(filter_out_illegal_color_names,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qfilter_out_illegal_color_names);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    Qacross = STATIC_SYMBOL("ACROSS",AB_package);
    Qstart = STATIC_SYMBOL("START",AB_package);
    Qstart_thread = STATIC_SYMBOL("START-THREAD",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_start_action,STATIC_FUNCTION(fix_start_action,
	    NIL,FALSE,1,1));
    Qin_order = STATIC_SYMBOL("IN-ORDER",AB_package);
    Qsimultaneously = STATIC_SYMBOL("SIMULTANEOUSLY",AB_package);
    Qfix_action_list = STATIC_SYMBOL("FIX-ACTION-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_action_list,STATIC_FUNCTION(fix_action_list,
	    NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfix_iqe,STATIC_FUNCTION(fix_iqe,NIL,FALSE,2,2));
    Qunlist_1 = STATIC_SYMBOL("UNLIST-1",AB_package);
    SET_SYMBOL_FUNCTION(Qunlist_1,STATIC_FUNCTION(unlist_1,NIL,FALSE,1,1));
    Qunlist_1_2 = STATIC_SYMBOL("UNLIST-1-2",AB_package);
    SET_SYMBOL_FUNCTION(Qunlist_1_2,STATIC_FUNCTION(unlist_1_2,NIL,FALSE,1,1));
    Qcar_2_1 = STATIC_SYMBOL("CAR-2-1",AB_package);
    SET_SYMBOL_FUNCTION(Qcar_2_1,STATIC_FUNCTION(car_2_1,NIL,FALSE,1,1));
    Qcurrent_value_of = STATIC_SYMBOL("CURRENT-VALUE-OF",AB_package);
    Qvalue_of = STATIC_SYMBOL("VALUE-OF",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qcurrent_value_of,Qvalue_of);
    Qis = STATIC_SYMBOL("IS",AB_package);
    Qchoose_is_or_eq = STATIC_SYMBOL("CHOOSE-IS-OR-=",AB_package);
    SET_SYMBOL_FUNCTION(Qchoose_is_or_eq,STATIC_FUNCTION(choose_is_or_eq,
	    NIL,FALSE,1,1));
    Qput_designation_in_qualifier = 
	    STATIC_SYMBOL("PUT-DESIGNATION-IN-QUALIFIER",AB_package);
    SET_SYMBOL_FUNCTION(Qput_designation_in_qualifier,
	    STATIC_FUNCTION(put_designation_in_qualifier,NIL,FALSE,1,1));
    Qfuzzy_eq = STATIC_SYMBOL("FUZZY-=",AB_package);
    list_constant_6 = STATIC_CONS(Qnum_eq,Qfuzzy_eq);
    Qfuzzy_not_eq = STATIC_SYMBOL("FUZZY-NOT-=",AB_package);
    list_constant_7 = STATIC_CONS(Qnum_ne,Qfuzzy_not_eq);
    Qfuzzy_gt = STATIC_SYMBOL("FUZZY->",AB_package);
    list_constant_8 = STATIC_CONS(Qnum_gt,Qfuzzy_gt);
    Qfuzzy_lt = STATIC_SYMBOL("FUZZY-<",AB_package);
    list_constant_9 = STATIC_CONS(Qnum_lt,Qfuzzy_lt);
    list_constant_2 = STATIC_LIST((SI_Long)4L,list_constant_6,
	    list_constant_7,list_constant_8,list_constant_9);
    Qfuzzy_comparator_reparser = STATIC_SYMBOL("FUZZY-COMPARATOR-REPARSER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfuzzy_comparator_reparser,
	    STATIC_FUNCTION(fuzzy_comparator_reparser,NIL,FALSE,1,1));
    Qcategory = STATIC_SYMBOL("CATEGORY",AB_package);
    Qcategory_hack = STATIC_SYMBOL("CATEGORY-HACK",AB_package);
    SET_SYMBOL_FUNCTION(Qcategory_hack,STATIC_FUNCTION(category_hack,NIL,
	    FALSE,1,1));
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qtrue,Qfalse,Qnot);
    Qsymbol_cannot_be_true_false_or_not = 
	    STATIC_SYMBOL("SYMBOL-CANNOT-BE-TRUE-FALSE-OR-NOT",AB_package);
    SET_SYMBOL_FUNCTION(Qsymbol_cannot_be_true_false_or_not,
	    STATIC_FUNCTION(symbol_cannot_be_true_false_or_not,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qsymbol_cannot_be_true_false_or_not);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qtime_stamp,Qseconds);
    Qfixed_format = STATIC_SYMBOL("FIXED-FORMAT",AB_package);
    Qcheck_ddd_dddd_format = STATIC_SYMBOL("CHECK-DDD-DDDD-FORMAT",AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_ddd_dddd_format,
	    STATIC_FUNCTION(check_ddd_dddd_format,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qcheck_ddd_dddd_format);
    list_constant_5 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)100L),
	    FIX((SI_Long)68L),FIX((SI_Long)46L));
    Qfix_in_order_action_list = STATIC_SYMBOL("FIX-IN-ORDER-ACTION-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfix_in_order_action_list,
	    STATIC_FUNCTION(fix_in_order_action_list,NIL,FALSE,1,1));
}
