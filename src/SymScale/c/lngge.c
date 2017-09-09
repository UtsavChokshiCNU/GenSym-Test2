/* lngge.c
 * Input file:  language.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "lngge.h"


DEFINE_VARIABLE_WITH_SYMBOL(Default_language, Qdefault_language);

static Object Qenglish;            /* english */

/* INITIALIZE-DEFAULT-LANGUAGE */
Object initialize_default_language()
{
    Object temp;

    x_note_fn_call(110,0);
    temp = get_g2_default_language_via_environment();
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(Qenglish);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object Qdefault_language_spec_via_environment;  /* default-language-spec-via-environment */

static Object array_constant_2;    /* # */

/* GET-G2-DEFAULT-LANGUAGE-VIA-ENVIRONMENT */
Object get_g2_default_language_via_environment()
{
    Object thing, raw_text_string_qm, temp, imported_text_string_qm;

    x_note_fn_call(110,1);
    thing = get_command_line_keyword_argument(1,array_constant);
    raw_text_string_qm = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != 
	    (SI_Long)0L ? copy_text_string(thing) : thing;
    if (raw_text_string_qm);
    else
	raw_text_string_qm = get_gensym_environment_variable(array_constant_1);
    if (raw_text_string_qm) {
	temp = import_text_string(2,raw_text_string_qm,
		Qdefault_language_spec_via_environment);
	reclaim_text_string(raw_text_string_qm);
	imported_text_string_qm = temp;
    }
    else
	imported_text_string_qm = Nil;
    if ( !( !TRUEP(imported_text_string_qm) || 
	    string_eq_w(imported_text_string_qm,array_constant_2)))
	return read_symbol_from_text_string(1,imported_text_string_qm);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Language_parameters, Qlanguage_parameters);

/* CURRENT-NATURAL-LANGUAGE-FOR-EDITOR */
Object current_natural_language_for_editor()
{
    Object temp;

    x_note_fn_call(110,2);
    temp = get_language_for_current_workstation_if_any();
    if (temp);
    else
	temp = Language_parameters ? ISVREF(Language_parameters,
		(SI_Long)22L) : Qnil;
    if (temp);
    else
	temp = Default_language;
    return get_natural_language_for_editor(temp);
}

static Object Qjapanese;           /* japanese */

static Object Qkorean;             /* korean */

static Object Qrussian;            /* russian */

/* GET-NATURAL-LANGUAGE-FOR-EDITOR */
Object get_natural_language_for_editor(language)
    Object language;
{
    x_note_fn_call(110,3);
    if (EQ(language,Qjapanese) || EQ(language,Qkorean) || EQ(language,
	    Qrussian))
	return VALUES_1(language);
    else
	return VALUES_1(Nil);
}

/* GET-LANGUAGE-FOR-CURRENT-WORKSTATION-IF-ANY */
Object get_language_for_current_workstation_if_any()
{
    Object temp;

    x_note_fn_call(110,4);
    temp = Servicing_workstation_qm ? ISVREF(Current_workstation,
	    (SI_Long)27L) : Nil;
    return VALUES_1(temp);
}

static Object Qcurrent_language_if_other_than_default_qm;  /* current-language-if-other-than-default? */

/* PUT-CURRENT-LANGUAGE-IF-OTHER-THAN-ENGLISH?-WHERE-SLOT-IS-ABSENT */
Object put_current_language_if_other_than_english_qm_where_slot_is_absent(language_parameters,
	    value)
    Object language_parameters, value;
{
    Object svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(110,5);
    PUSH_SPECIAL_WITH_SYMBOL(Language_parameters,Qlanguage_parameters,language_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Language_parameters,
		  Qcurrent_language_if_other_than_default_qm);
      svref_arg_1 = Language_parameters;
      SVREF(svref_arg_1,FIX((SI_Long)22L)) = value;
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* WRITE-CURRENT-LANGUAGE-FROM-SLOT */
Object write_current_language_from_slot(current_language_if_other_than_default_qm,
	    gensymed_symbol)
    Object current_language_if_other_than_default_qm, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(110,6);
    temp = current_language_if_other_than_default_qm;
    if (temp);
    else
	temp = Default_language;
    return twrite(temp);
}

/* COMPILE-CURRENT-LANGUAGE-FOR-SLOT */
Object compile_current_language_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(110,7);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Default_language))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* RECLAIM-CURRENT-LANGUAGE-IF-OTHER-THAN-DEFAULT?-VALUE */
Object reclaim_current_language_if_other_than_default_qm_value(old_language_qm,
	    language_parameters)
    Object old_language_qm, language_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(110,8);
    PUSH_SPECIAL_WITH_SYMBOL(Language_parameters,Qlanguage_parameters,language_parameters,
	    0);
      add_or_delete_as_language_contributor(Language_parameters,
	      old_language_qm,T);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qlanguage;           /* language */

/* PUT-CURRENT-LANGUAGE-IF-OTHER-THAN-DEFAULT? */
Object put_current_language_if_other_than_default_qm(language_parameters_instance,
	    language_qm,initializing_qm)
    Object language_parameters_instance, language_qm, initializing_qm;
{
    char changed;

    x_note_fn_call(110,9);
    if (initializing_qm && EQ(language_qm,Default_language))
	language_qm = Nil;
    add_or_delete_as_language_contributor(language_parameters_instance,
	    ISVREF(language_parameters_instance,(SI_Long)22L),T);
    add_or_delete_as_language_contributor(language_parameters_instance,
	    language_qm,Nil);
    changed =  !EQ(ISVREF(language_parameters_instance,(SI_Long)22L),
	    language_qm);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(language_parameters_instance,
		Qcurrent_language_if_other_than_default_qm);
    SVREF(language_parameters_instance,FIX((SI_Long)22L)) = language_qm;
    if (changed)
	return decache_dynamic_menus(1,Qlanguage);
    else
	return VALUES_1(Nil);
}

Object Translation_contributors_kbprop = UNBOUND;

static Object list_constant;       /* # */

/* ADD-OR-DELETE-AS-LANGUAGE-CONTRIBUTOR */
Object add_or_delete_as_language_contributor(frame,language_qm,delete_case_qm)
    Object frame, language_qm, delete_case_qm;
{
    Object translation_contributors, temp;

    x_note_fn_call(110,10);
    if ( !TRUEP(memq_function(language_qm,list_constant))) {
	translation_contributors = 
		lookup_kb_specific_property_value(language_qm,
		Translation_contributors_kbprop);
	if (delete_case_qm) {
	    if (memq_function(frame,translation_contributors)) {
		temp = delete_kb_property_element_1(frame,
			translation_contributors);
		mutate_kb_specific_property_value(language_qm,temp,
			Translation_contributors_kbprop);
		if ( !TRUEP(lookup_kb_specific_property_value(language_qm,
			Translation_contributors_kbprop)))
		    return delete_from_directory_of_names(language_qm,
			    Qlanguage);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if ( !TRUEP(memq_function(frame,translation_contributors))) {
	    mutate_kb_specific_property_value(language_qm,
		    kb_property_cons_1(frame,translation_contributors),
		    Translation_contributors_kbprop);
	    if ( !TRUEP(translation_contributors))
		return add_to_directory_of_names(language_qm,Qlanguage);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Localization_context, Qlocalization_context);

DEFINE_VARIABLE_WITH_SYMBOL(Current_localization_purpose_qm, Qcurrent_localization_purpose_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_localization_domains_qm, Qcurrent_localization_domains_qm);

/* PUSH-ITEM-TO-END-OF-CURRENT-LOCALIZATION-DOMAINS */
Object push_item_to_end_of_current_localization_domains(additional_domain)
    Object additional_domain;
{
    Object cdr_arg, cdr_new_value;

    x_note_fn_call(110,11);
    if ( !TRUEP(Current_localization_domains_qm)) {
	Current_localization_domains_qm = 
		kb_property_cons_1(additional_domain,Nil);
	return VALUES_1(Current_localization_domains_qm);
    }
    else if (CONSP(Current_localization_domains_qm)) {
	if ( !TRUEP(CDR(Current_localization_domains_qm))) {
	    cdr_arg = Current_localization_domains_qm;
	    cdr_new_value = kb_property_cons_1(additional_domain,Nil);
	    return VALUES_1(M_CDR(cdr_arg) = cdr_new_value);
	}
	else
	    return push_item_to_end_of_kb_property_list(Current_localization_domains_qm,
		    additional_domain);
    }
    else
	return VALUES_1(Nil);
}

/* PUSH-ITEM-TO-END-OF-KB-PROPERTY-LIST */
Object push_item_to_end_of_kb_property_list(list_1,item)
    Object list_1, item;
{
    Object tail_of_list, cdr_new_value;

    x_note_fn_call(110,12);
    tail_of_list = list_1;
  next_loop:
    if ( !TRUEP(tail_of_list))
	goto end_loop;
    if ( !TRUEP(CDR(tail_of_list))) {
	cdr_new_value = kb_property_cons_1(item,Nil);
	M_CDR(tail_of_list) = cdr_new_value;
	return VALUES_1(Nil);
    }
    tail_of_list = M_CDR(tail_of_list);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REMOVE-LAST-ITEM-IN-CURRENT-LOCALIZATION-DOMAINS */
Object remove_last_item_in_current_localization_domains()
{
    Object penultimate_cons_cell, cons_cell, remainder_1, tail;

    x_note_fn_call(110,13);
    if (Current_localization_domains_qm) {
	if ( !TRUEP(CDR(Current_localization_domains_qm))) {
	    reclaim_kb_property_cons_1(Current_localization_domains_qm);
	    Current_localization_domains_qm = Nil;
	    return VALUES_1(Current_localization_domains_qm);
	}
	else {
	    penultimate_cons_cell = Nil;
	    cons_cell = Nil;
	    remainder_1 = Nil;
	    tail = Current_localization_domains_qm;
	  next_loop:
	    if ( !TRUEP(tail))
		goto end_loop;
	    penultimate_cons_cell = tail;
	    cons_cell = CDR(tail);
	    remainder_1 = CDDR(tail);
	    if ( !TRUEP(remainder_1)) {
		reclaim_kb_property_cons_1(cons_cell);
		M_CDR(penultimate_cons_cell) = Nil;
		return VALUES_1(Nil);
	    }
	    tail = M_CDR(tail);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Known_localizations, Qknown_localizations);

/* POPULATE-THE-FIXED-LOCALIZATION-CATEGORIES */
Object populate_the_fixed_localization_categories(alist_by_category)
    Object alist_by_category;
{
    Object category_symbol, terminals, ab_loop_list_, ab_loop_desetq_, temp;
    Object terminal_symbol, ab_loop_list__1;

    x_note_fn_call(110,14);
    category_symbol = Nil;
    terminals = Nil;
    ab_loop_list_ = alist_by_category;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    category_symbol = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    terminals = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    terminal_symbol = Nil;
    ab_loop_list__1 = terminals;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    terminal_symbol = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    add_grammar_rules_function(LIST_1(LIST_2(category_symbol,LIST_2(Qquote,
	    terminal_symbol))));
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    Known_localizations = alist_by_category;
    return VALUES_1(Known_localizations);
}

static Object Qeditor;             /* editor */

static Object Qmenu;               /* menu */

static Object Qtable;              /* table */

static Object Qmain_menu;          /* main-menu */

static Object Qeditor_operations_menu;  /* editor-operations-menu */

static Object Qtext_editor;        /* text-editor */

static Object Qicon_editor;        /* icon-editor */

static Object Qg2_login_dialog;    /* g2-login-dialog */

static Object Qpassword_change_dialog;  /* password-change-dialog */

/* UNIQUE-LOCALIZATION-DOMAIN-P */
Object unique_localization_domain_p(symbol)
    Object symbol;
{
    x_note_fn_call(110,15);
    if (EQ(symbol,Qeditor) || EQ(symbol,Qmenu) || EQ(symbol,Qtable))
	return VALUES_1(Nil);
    else if (EQ(symbol,Qmain_menu) || EQ(symbol,Qeditor_operations_menu))
	return VALUES_1(T);
    else if (EQ(symbol,Qtext_editor) || EQ(symbol,Qicon_editor) || 
	    EQ(symbol,Qg2_login_dialog) || EQ(symbol,Qpassword_change_dialog))
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

Object Domains_consistent_with_localization_purpose_prop = UNBOUND;

/* DEFINE-CONSISTENT-LOCALIZATION-DOMAINS */
Object define_consistent_localization_domains(default_localization_domain,
	    localization_domain_includes_classes_p,
	    category_of_localization_domain)
    Object default_localization_domain, localization_domain_includes_classes_p;
    Object category_of_localization_domain;
{
    Object temp;

    x_note_fn_call(110,16);
    temp = CONS(category_of_localization_domain,Nil);
    temp = CONS(localization_domain_includes_classes_p,temp);
    return VALUES_1(CONS(default_localization_domain,temp));
}

static Object Kaccepts_classes_qm;  /* :accepts-classes? */

static Object Kfixed_domain;       /* :fixed-domain */

static Object Qdomains_consistent_with_localization_purpose;  /* domains-consistent-with-localization-purpose */

/* DEFINE-DOMAINS-CONSISTENT-WITH-LOCALIZATION-PURPOSE */
Object define_domains_consistent_with_localization_purpose varargs_1(int, n)
{
    Object purpose;
    Object default_p, default_1, accepts_classes_qm_p, accepts_classes_qm;
    Object fixed_domain_p, fixed_domain, struct_1;
    Declare_varargs;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(110,17);
    SAVE_STACK();
    INIT_ARGS();
    purpose = REQUIRED_ARG();
    SAVE_ARGS();
    default_p = KEYWORD_ARG_P(Kdefault);
    default_1 = default_p ? KEYWORD_ARG(default_p) : Nil;
    accepts_classes_qm_p = KEYWORD_ARG_P(Kaccepts_classes_qm);
    accepts_classes_qm = accepts_classes_qm_p ? 
	    KEYWORD_ARG(accepts_classes_qm_p) : Nil;
    fixed_domain_p = KEYWORD_ARG_P(Kfixed_domain);
    fixed_domain = fixed_domain_p ? KEYWORD_ARG(fixed_domain_p) : Nil;
    struct_1 = define_consistent_localization_domains(default_1,
	    accepts_classes_qm,fixed_domain);
    result = mutate_global_property(purpose,struct_1,
	    Qdomains_consistent_with_localization_purpose);
    RESTORE_STACK();
    return result;
}

static Object Qno_fixed_localization_domains;  /* no-fixed-localization-domains */

/* KNOWN-LOCALIZATION-DOMAINS-FOR-PURPOSE */
Object known_localization_domains_for_purpose(symbol_naming_purpose)
    Object symbol_naming_purpose;
{
    Object consistency_data, temp, category_qm;

    x_note_fn_call(110,18);
    consistency_data = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol_naming_purpose),
	    Qdomains_consistent_with_localization_purpose);
    temp = CDDR(consistency_data);
    category_qm = CAR(temp);
    if (category_qm) {
	if (EQ(category_qm,Qno_fixed_localization_domains))
	    return VALUES_1(Qno_fixed_localization_domains);
	else {
	    temp = assq_function(category_qm,Known_localizations);
	    return VALUES_1(SECOND(temp));
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qlocalization_purpose;  /* localization-purpose */

/* KNOWN-LOCALIZATION-PURPOSE-P */
Object known_localization_purpose_p(symbol)
    Object symbol;
{
    Object temp, purposes;

    x_note_fn_call(110,19);
    temp = assq_function(Qlocalization_purpose,Known_localizations);
    purposes = SECOND(temp);
    return memq_function(symbol,purposes);
}

/* MAKE-LANGUAGE-TRANSLATION-DATA */
Object make_language_translation_data(localization_data_language,
	    localization_data_purpose,localization_data_domain,
	    localization_data_term_translation_pairs)
    Object localization_data_language, localization_data_purpose;
    Object localization_data_domain, localization_data_term_translation_pairs;
{
    x_note_fn_call(110,20);
    return phrase_cons(localization_data_language,
	    phrase_cons(phrase_cons(localization_data_purpose,
	    localization_data_domain),
	    localization_data_term_translation_pairs));
}

/* DATA-OF-LANGUAGE-TRANSLATION */
Object data_of_language_translation(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(110,21);
    temp = ISVREF(frame,(SI_Long)16L);
    return VALUES_1(CAR(temp));
}

/* LANGUAGE-OF-LANGUAGE-TRANSLATION */
Object language_of_language_translation(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(110,22);
    temp = ISVREF(frame,(SI_Long)16L);
    temp = CAR(temp);
    return VALUES_1(CAR(temp));
}

/* PURPOSE-OF-LANGUAGE-TRANSLATION */
Object purpose_of_language_translation(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(110,23);
    temp = ISVREF(frame,(SI_Long)16L);
    temp = CAR(temp);
    temp = CDR(temp);
    return VALUES_1(CAAR(temp));
}

/* DOMAIN-OF-LANGUAGE-TRANSLATION */
Object domain_of_language_translation(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(110,24);
    temp = ISVREF(frame,(SI_Long)16L);
    temp = CAR(temp);
    temp = CDR(temp);
    temp = CAR(temp);
    return VALUES_1(CDR(temp));
}

/* TERM-TRANSLATION-PAIRS */
Object term_translation_pairs(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(110,25);
    temp = ISVREF(frame,(SI_Long)16L);
    temp = CAR(temp);
    return VALUES_1(CDDR(temp));
}

static Object Qlanguage_translation;  /* language-translation */

/* CLEANUP-FOR-LANGUAGE-TRANSLATION */
Object cleanup_for_language_translation(language_translation)
    Object language_translation;
{
    Object frame, sub_vector_qm, method_function_qm, frame_1, temp, data;
    Object terms_removed, symbol, translation_string, ab_loop_list_;
    Object ab_loop_desetq_;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(110,26);
    frame = language_translation;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qlanguage_translation)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    frame_1 = language_translation;
    temp = ISVREF(frame_1,(SI_Long)16L);
    data = CAR(temp);
    if ( !( !TRUEP(data) || EQ(data,No_value))) {
	add_or_delete_as_language_contributor(frame_1,CAR(data),T);
	terms_removed = Nil;
	symbol = Nil;
	translation_string = Nil;
	ab_loop_list_ = CDDR(data);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	symbol = CAR(ab_loop_desetq_);
	translation_string = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(symbol,terms_removed))) {
	    remove_translation_statement_from_term(symbol,frame_1);
	    terms_removed = gensym_cons_1(symbol,terms_removed);
	}
	goto next_loop_1;
      end_loop_1:
	reclaim_gensym_list_1(terms_removed);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-AFTER-READING-FOR-LANGUAGE-TRANSLATION */
Object initialize_after_reading_for_language_translation(language_translation)
    Object language_translation;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(110,27);
    frame = language_translation;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qlanguage_translation)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-LANGUAGE-TRANSLATION */
Object put_box_translation_and_text_slot_value_for_language_translation(language_translation,
	    box_translation_and_text,initializing_qm)
    Object language_translation, box_translation_and_text, initializing_qm;
{
    Object frame, value_field, value_qm, temp, prior_value_field;
    Object prior_value_qm;

    x_note_fn_call(110,28);
    frame = language_translation;
    value_field = CAR(box_translation_and_text);
    value_qm =  !( !TRUEP(value_field) || EQ(value_field,No_value)) ? 
	    value_field : Nil;
    temp = ISVREF(frame,(SI_Long)16L);
    prior_value_field = CAR(temp);
    prior_value_qm = prior_value_field &&  !( !TRUEP(prior_value_field) || 
	    EQ(prior_value_field,No_value)) ? prior_value_field : Nil;
    if ( !TRUEP(initializing_qm))
	update_frame_status(frame,Nil,Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qbox_translation_and_text);
    SVREF(frame,FIX((SI_Long)16L)) = box_translation_and_text;
    if (value_qm) {
	if (old_style_language_translation_p(value_qm))
	    process_old_style_menu_translation_slot_value(value_qm,frame,
		    initializing_qm);
	else
	    process_new_style_translation_slot_value(value_qm,
		    prior_value_qm,frame);
    }
    return VALUES_2(box_translation_and_text,Nil);
}

/* PROCESS-NEW-STYLE-TRANSLATION-SLOT-VALUE */
Object process_new_style_translation_slot_value(value,prior_value_qm,frame)
    Object value, prior_value_qm, frame;
{
    Object language, prior_language, term_translation_pairs_1;
    Object prior_term_translation_pairs, symbol, translation_string;
    Object ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(110,29);
    language = CAR(value);
    prior_language = prior_value_qm ? CAR(prior_value_qm) : Nil;
    term_translation_pairs_1 = CDDR(value);
    prior_term_translation_pairs = prior_value_qm ? CDDR(prior_value_qm) : Nil;
    if (prior_value_qm) {
	if ( !EQ(language,prior_language))
	    add_or_delete_as_language_contributor(frame,prior_language,T);
	symbol = Nil;
	translation_string = Nil;
	ab_loop_list_ = prior_term_translation_pairs;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	symbol = CAR(ab_loop_desetq_);
	translation_string = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(assq_function(symbol,term_translation_pairs_1)))
	    remove_translation_statement_from_term(symbol,frame);
	goto next_loop;
      end_loop:;
	symbol = Nil;
	translation_string = Nil;
	ab_loop_list_ = term_translation_pairs_1;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	symbol = CAR(ab_loop_desetq_);
	translation_string = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(assq_function(symbol,prior_term_translation_pairs)))
	    add_translation_statement_to_term(symbol,frame);
	if (assq_function(symbol,prior_term_translation_pairs))
	    check_for_duplicate_instances_in_language_translation(symbol,
		    frame);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return extend_localization_data(language,term_translation_pairs_1,
		frame);
}

/* EXTEND-LOCALIZATION-DATA */
Object extend_localization_data(language,term_translation_pairs_1,frame)
    Object language, term_translation_pairs_1, frame;
{
    Object symbol, translation_string, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(110,30);
    symbol = Nil;
    translation_string = Nil;
    ab_loop_list_ = term_translation_pairs_1;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    symbol = CAR(ab_loop_desetq_);
    translation_string = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_translation_statement_to_term(symbol,frame);
    goto next_loop;
  end_loop:;
    return add_or_delete_as_language_contributor(frame,language,Nil);
}

/* OLD-STYLE-LANGUAGE-TRANSLATION-P */
Object old_style_language_translation_p(value)
    Object value;
{
    Object temp, possible_localization_purpose;

    x_note_fn_call(110,31);
    temp = CDR(value);
    possible_localization_purpose = CAAR(temp);
    return VALUES_1( 
	    !TRUEP(known_localization_purpose_p(possible_localization_purpose)) 
	    ? T : Nil);
}

static Object Qmenu_item;          /* menu-item */

/* PROCESS-OLD-STYLE-MENU-TRANSLATION-SLOT-VALUE */
Object process_old_style_menu_translation_slot_value(value,frame,
	    initializing_qm)
    Object value, frame, initializing_qm;
{
    Object language, term_translation_pairs_1, cdr_new_value;

    x_note_fn_call(110,32);
    if (initializing_qm) {
	language = CAR(value);
	term_translation_pairs_1 = CDR(value);
	cdr_new_value = slot_value_cons_1(slot_value_cons_1(Qmenu_item,
		Qmenu),CDR(value));
	M_CDR(value) = cdr_new_value;
	extend_localization_data(language,term_translation_pairs_1,frame);
	return VALUES_1(value);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object string_constant;     /* "~%  " */

static Object array_constant_5;    /* # */

static Object string_constant_1;   /* "~s" */

static Object Qcm;                 /* \, */

/* WRITE-LANGUAGE-TRANSLATION-FROM-SLOT */
Object write_language_translation_from_slot(language_translation,
	    gensymed_symbol)
    Object language_translation, gensymed_symbol;
{
    Object frame, language, term_translation_pairs_1, term, translation;
    Object more_qm, ab_loop_list_, temp;

    x_note_fn_call(110,33);
    frame = language_translation;
    language = language_of_language_translation(frame);
    term_translation_pairs_1 = term_translation_pairs(frame);
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)3L));
    twrite_symbol(1,language);
    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)3L));
    term = Nil;
    translation = Nil;
    more_qm = Nil;
    ab_loop_list_ = term_translation_pairs_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    temp = CAR(ab_loop_list_);
    term = CAR(temp);
    temp = CAR(ab_loop_list_);
    translation = CDR(temp);
    more_qm = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(1,string_constant);
    twrite_symbol(1,term);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)3L));
    tformat(2,string_constant_1,translation);
    if (more_qm)
	tformat(2,string_constant_1,Qcm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qab_simple_condition;  /* simple-condition */

/* REGISTER-SYMBOL-AS-SIMPLE-CONDITION */
Object register_symbol_as_simple_condition(symbol)
    Object symbol;
{
    x_note_fn_call(110,34);
    return add_grammar_rules_function(LIST_1(LIST_2(Qab_simple_condition,
	    LIST_2(Qquote,symbol))));
}

static Object Qbutton_label;       /* button-label */

/* REGISTER-BUTTON-LABEL-FOR-INTERNATIONALIZATION */
Object register_button_label_for_internationalization(symbol)
    Object symbol;
{
    x_note_fn_call(110,35);
    return add_grammar_rules_function(LIST_1(LIST_2(Qbutton_label,
	    LIST_2(Qquote,symbol))));
}

/* REGISTER-BUTTON-LABELS-FOR-INTERNATIONALIZATION */
Object register_button_labels_for_internationalization(list_of_symbols)
    Object list_of_symbols;
{
    Object symbol, ab_loop_list_;

    x_note_fn_call(110,36);
    symbol = Nil;
    ab_loop_list_ = list_of_symbols;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    register_button_label_for_internationalization(symbol);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Translations_for_symbol_kbprop = UNBOUND;

/* RECLAIM-TRANSLATIONS-FOR-SYMBOL */
Object reclaim_translations_for_symbol(translations_for_symbol)
    Object translations_for_symbol;
{
    x_note_fn_call(110,37);
    return reclaim_kb_property_list_1(translations_for_symbol);
}

/* ADD-TRANSLATION-STATEMENT-TO-TERM */
Object add_translation_statement_to_term(symbol,frame)
    Object symbol, frame;
{
    Object entry;

    x_note_fn_call(110,38);
    entry = lookup_kb_specific_property_value(symbol,
	    Translations_for_symbol_kbprop);
    if ( !TRUEP(entry))
	return mutate_kb_specific_property_value(symbol,
		kb_property_cons_1(frame,Nil),Translations_for_symbol_kbprop);
    else if (memq_function(frame,entry)) {
	check_for_duplicate_instances_in_language_translation(symbol,frame);
	return check_for_other_language_translations(2,symbol,frame);
    }
    else {
	check_for_other_language_translations(2,symbol,frame);
	return mutate_kb_specific_property_value(symbol,
		kb_property_cons_1(frame,entry),
		Translations_for_symbol_kbprop);
    }
}

/* REMOVE-TRANSLATION-STATEMENT-FROM-TERM */
Object remove_translation_statement_from_term(symbol,frame)
    Object symbol, frame;
{
    Object entry, temp;

    x_note_fn_call(110,39);
    if ( !TRUEP(Releasing_kb_qm)) {
	entry = lookup_kb_specific_property_value(symbol,
		Translations_for_symbol_kbprop);
	if ( !TRUEP(entry))
	    return VALUES_1(Nil);
	else if (memq_function(frame,entry)) {
	    check_for_other_language_translations(3,symbol,frame,T);
	    temp = delete_kb_property_element_1(frame,entry);
	    return mutate_kb_specific_property_value(symbol,temp,
		    Translations_for_symbol_kbprop);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object English_localization_prop = UNBOUND;

static Object Qenglish_localization;  /* english-localization */

/* DEFINE-INTERNATIONALIZED-SYMBOL */
Object define_internationalized_symbol(symbol_or_cons)
    Object symbol_or_cons;
{
    Object symbol, english_text, temp;

    x_note_fn_call(110,40);
    symbol = SYMBOLP(symbol_or_cons) ? symbol_or_cons : CAR(symbol_or_cons);
    english_text = CONSP(symbol_or_cons) ? CDR(symbol_or_cons) : Nil;
    register_symbol_as_simple_condition(symbol);
    temp = mutate_global_property(symbol,english_text,Qenglish_localization);
    return VALUES_1(temp);
}

static Object Kfirst;              /* :first */

/* STRING-FOR-LOCALIZED-SYMBOL */
Object string_for_localized_symbol(symbol)
    Object symbol;
{
    Object translation_qm, english_qm, temp;

    x_note_fn_call(110,41);
    translation_qm = translation_for_symbol_qm(1,symbol);
    english_qm = getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qenglish_localization);
    temp = translation_qm ? copy_text_string(translation_qm) : Nil;
    if (temp);
    else
	temp = english_qm ? copy_text_string(english_qm) : Nil;
    if (temp);
    else
	temp = copy_symbol_name(3,symbol,Kfirst,T);
    return VALUES_1(temp);
}

/* TRANSLATION-FOR-SYMBOL? */
Object translation_for_symbol_qm varargs_1(int, n)
{
    Object symbol;
    Object overriding_language_qm, current_language;
    Declare_varargs_nonrelocating;

    x_note_fn_call(110,42);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    overriding_language_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    current_language = overriding_language_qm;
    if (current_language);
    else {
	current_language = get_language_for_current_workstation_if_any();
	if (current_language);
	else
	    current_language = Language_parameters ? 
		    ISVREF(Language_parameters,(SI_Long)22L) : Qnil;
	if (current_language);
	else
	    current_language = Default_language;
    }
    if ( !EQ(current_language,Qenglish))
	return contextually_appropriate_translation_of_symbol_qm(symbol,
		current_language);
    else
	return VALUES_1(Nil);
}

/* CONTEXTUALLY-APPROPRIATE-TRANSLATION-OF-SYMBOL? */
Object contextually_appropriate_translation_of_symbol_qm(symbol,language)
    Object symbol, language;
{
    Object localization_entry_qm, purpose, domains;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(110,43);
    SAVE_STACK();
    LOCK(Localization_context);
    if (PUSH_UNWIND_PROTECT(0)) {
	localization_entry_qm = lookup_kb_specific_property_value(symbol,
		Translations_for_symbol_kbprop);
	if (localization_entry_qm) {
	    purpose = Current_localization_purpose_qm;
	    domains = Current_localization_domains_qm;
	    if ( !TRUEP(purpose) &&  !TRUEP(domains))
		SAVE_VALUES(VALUES_1(Nil));
	    else if ( !TRUEP(domains))
		SAVE_VALUES(VALUES_1(Nil));
	    else if ( !TRUEP(purpose))
		SAVE_VALUES(VALUES_1(Nil));
	    else
		SAVE_VALUES(find_translation_for_symbol_in_contextually_appropriate_frame(symbol,
			localization_entry_qm,language,purpose,domains));
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Localization_context);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* FIND-TRANSLATION-FOR-SYMBOL-IN-CONTEXTUALLY-APPROPRIATE-FRAME */
Object find_translation_for_symbol_in_contextually_appropriate_frame(symbol,
	    frames,language,purpose,domains)
    Object symbol, frames, language, purpose, domains;
{
    Object frame_to_use_qm;

    x_note_fn_call(110,44);
    frame_to_use_qm = search_language_translation_frames(frames,language,
	    purpose,domains);
    if (frame_to_use_qm)
	return extract_translation_from_language_translation_frame(symbol,
		frame_to_use_qm);
    else
	return VALUES_1(Nil);
}

static Object Qattribute;          /* attribute */

/* SEARCH-LANGUAGE-TRANSLATION-FRAMES */
Object search_language_translation_frames(frames,language,purpose,domains)
    Object frames, language, purpose, domains;
{
    Object best_so_far_qm, frame, ab_loop_list_, temp, gensymed_symbol;
    char temp_1;

    x_note_fn_call(110,45);
    best_so_far_qm = Nil;
    frame = Nil;
    ab_loop_list_ = frames;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (frame_matches_localization_context_p(frame,language,purpose,domains)) {
	if (EQ(purpose,Qattribute)) {
	    if (best_so_far_qm) {
		temp = domain_of_language_translation(frame);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(temp,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    temp = domain_of_language_translation(best_so_far_qm);
		    temp_1 = TRUEP(memq_function(temp,
			    ISVREF(gensymed_symbol,(SI_Long)2L)));
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    best_so_far_qm = frame;
	    }
	    else
		best_so_far_qm = frame;
	}
	else
	    return VALUES_1(frame);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(best_so_far_qm);
    return VALUES_1(Qnil);
}

/* FRAME-MATCHES-LOCALIZATION-CONTEXT-P */
Object frame_matches_localization_context_p(frame,language,purpose,domains)
    Object frame, language, purpose, domains;
{
    Object temp, data;

    x_note_fn_call(110,46);
    temp = ISVREF(frame,(SI_Long)16L);
    data = CAR(temp);
    if (EQ(CAR(data),language)) {
	temp = CDR(data);
	if (EQ(CAAR(temp),purpose)) {
	    temp = CDR(data);
	    temp = CAR(temp);
	    if (one_of_the_localization_domains_subsumes_domain_p(domains,
		    CDR(temp),purpose))
		return VALUES_1(T);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* ONE-OF-THE-LOCALIZATION-DOMAINS-SUBSUMES-DOMAIN-P */
Object one_of_the_localization_domains_subsumes_domain_p(list_of_domains,
	    domain,purpose)
    Object list_of_domains, domain, purpose;
{
    Object possible_governing_domain, ab_loop_list_, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Object result;

    x_note_fn_call(110,47);
    possible_governing_domain = Nil;
    ab_loop_list_ = list_of_domains;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    possible_governing_domain = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SYMBOLP(possible_governing_domain))
	temp = EQ(domain,possible_governing_domain);
    else if (EQ(purpose,Qattribute)) {
	if (SYMBOLP(domain)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = domain;
	    key_hash_value = SXHASH_SYMBOL_1(domain) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_1:
	    if (level < ab_loop_bind_)
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_2:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_3:
	    if ( !TRUEP(marked))
		goto end_loop_2;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_3;
	  end_loop_2:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_1;
	    goto next_loop_2;
	  end_loop_3:
	  end_1:
	    level = level - (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = domain;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
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
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_4:
	    if (level < ab_loop_bind_)
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_5:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_6:
	    if ( !TRUEP(marked))
		goto end_loop_5;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_6;
	  end_loop_5:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_2;
	    goto next_loop_5;
	  end_loop_6:
	  end_2:
	    level = level - (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_7:
		if (level < ab_loop_bind_)
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_8:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_9:
		if ( !TRUEP(marked))
		    goto end_loop_8;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_9;
	      end_loop_8:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_3;
		goto next_loop_8;
	      end_loop_9:
	      end_3:
		level = level - (SI_Long)1L;
		goto next_loop_7;
	      end_loop_7:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_10:
		if (level < ab_loop_bind_)
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_11:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_12:
		if ( !TRUEP(marked))
		    goto end_loop_11;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_12;
	      end_loop_11:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_4;
		goto next_loop_11;
	      end_loop_12:
	      end_4:
		level = level - (SI_Long)1L;
		goto next_loop_10;
	      end_loop_10:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    temp = TRUEP(resulting_value);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(domain,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = 
			ISVREF(ISVREF(possible_governing_domain,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(T);
    goto next_loop;
  end_loop:
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* EXTRACT-TRANSLATION-FROM-LANGUAGE-TRANSLATION-FRAME */
Object extract_translation_from_language_translation_frame(symbol,frame)
    Object symbol, frame;
{
    Object term_translation_pairs_1, temp;

    x_note_fn_call(110,48);
    term_translation_pairs_1 = term_translation_pairs(frame);
    temp = assq_function(symbol,term_translation_pairs_1);
    return VALUES_1(CDR(temp));
}

/* COMPILE-LANGUAGE-TRANSLATION-FOR-SLOT */
Object compile_language_translation_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object language, temp, term_translation_pairs_1, context_qm;
    Object error_message_qm;
    char includes_context_qm;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(110,49);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    language = FIRST(parse_result);
    includes_context_qm =  !EQ(SECOND(parse_result),Qcm);
    if (includes_context_qm) {
	temp = THIRD(parse_result);
	term_translation_pairs_1 = CDR(temp);
    }
    else
	term_translation_pairs_1 = CDDR(parse_result);
    replace_symbol_translations_with_strings(term_translation_pairs_1);
    if (includes_context_qm)
	result = compile_localizing_context(SECOND(parse_result));
    else
	result = VALUES_1(Nil);
    MVS_2(result,context_qm,error_message_qm);
    if (error_message_qm)
	return VALUES_2(Bad_phrase,error_message_qm);
    else if (context_qm)
	return make_language_translation_data(language,CAR(context_qm),
		CDR(context_qm),term_translation_pairs_1);
    else
	return make_language_translation_data(language,Qmenu_item,Qmenu,
		term_translation_pairs_1);
}

/* REPLACE-SYMBOL-TRANSLATIONS-WITH-STRINGS */
Object replace_symbol_translations_with_strings(term_translation_pairs_1)
    Object term_translation_pairs_1;
{
    Object pair, ab_loop_list_, temp, cdr_new_value;

    x_note_fn_call(110,50);
    pair = Nil;
    ab_loop_list_ = term_translation_pairs_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = M_CDR(pair);
    if (SYMBOLP(temp)) {
	cdr_new_value = copy_symbol_name(2,CDR(pair),Nil);
	M_CDR(pair) = cdr_new_value;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_2;   /* "~a is not a known localization purpose" */

static Object string_constant_3;   /* "The localization purpose ~a cannot be defaulted. ~
				    *                     An explicit domain must be provided."
				    */

static Object string_constant_4;   /* "The class name ~a is not a valid domain for the localization ~
				    *                 purpose ~a because that purpose does not apply to items."
				    */

static Object string_constant_5;   /* "No domain information is available for the ~
				    *                    localization purpose ~a."
				    */

static Object Qpassword_change;    /* password-change */

static Object string_constant_6;   /* "~a is not a legal domain for the localization purpose ~a" */

static Object string_constant_7;   /* "~a is not one of the legal specific domains for the ~
				    *                       localization purpose ~a, i.e. ~a"
				    */

/* COMPILE-LOCALIZING-CONTEXT */
Object compile_localizing_context(parse_result)
    Object parse_result;
{
    Object purpose, domain_qm, error_message_qm, consistency_data_qm;
    Object default_qm, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, legal_domains_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(110,51);
    purpose = CAR(parse_result);
    domain_qm = CDR(parse_result);
    error_message_qm = Nil;
    consistency_data_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(purpose),
	    Qdomains_consistent_with_localization_purpose);
    if ( !TRUEP(consistency_data_qm))
	error_message_qm = tformat_text_string(6,string_constant_2,purpose,
		Nil,Nil,Nil,Nil);
    else if ( !TRUEP(domain_qm)) {
	default_qm = CAR(consistency_data_qm);
	if ( !TRUEP(default_qm))
	    error_message_qm = tformat_text_string(6,string_constant_3,
		    purpose,Nil,Nil,Nil,Nil);
	domain_qm = default_qm;
    }
    else {
	if (SYMBOLP(domain_qm)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = domain_qm;
	    key_hash_value = SXHASH_SYMBOL_1(domain_qm) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop:
	    if (level < ab_loop_bind_)
		goto end_loop;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_1:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_2;
	  end_loop_1:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_1;
	    goto next_loop_1;
	  end_loop_2:
	  end_1:
	    level = level - (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = domain_qm;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
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
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_3:
	    if (level < ab_loop_bind_)
		goto end_loop_3;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_4:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_5;
	  end_loop_4:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_2;
	    goto next_loop_4;
	  end_loop_5:
	  end_2:
	    level = level - (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_6:
		if (level < ab_loop_bind_)
		    goto end_loop_6;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_7:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_8;
	      end_loop_7:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_3;
		goto next_loop_7;
	      end_loop_8:
	      end_3:
		level = level - (SI_Long)1L;
		goto next_loop_6;
	      end_loop_6:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_9:
		if (level < ab_loop_bind_)
		    goto end_loop_9;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_10:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_11;
	      end_loop_10:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_4;
		goto next_loop_10;
	      end_loop_11:
	      end_4:
		level = level - (SI_Long)1L;
		goto next_loop_9;
	      end_loop_9:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    temp_2 = TRUEP(resulting_value);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_1 = CDR(consistency_data_qm);
	    if ( !TRUEP(CAR(temp_1)))
		error_message_qm = tformat_text_string(6,string_constant_4,
			domain_qm,purpose,Nil,Nil,Nil);
	}
	else {
	    legal_domains_qm = known_localization_domains_for_purpose(purpose);
	    if ( !TRUEP(legal_domains_qm))
		error_message_qm = tformat_text_string(6,string_constant_5,
			purpose,Nil,Nil,Nil,Nil);
	    else if (EQ(legal_domains_qm,Qno_fixed_localization_domains)) {
		if ( !EQ(domain_qm,Qpassword_change))
		    error_message_qm = tformat_text_string(6,
			    string_constant_6,domain_qm,purpose,Nil,Nil,Nil);
	    }
	    else {
		temp_1 = CDR(consistency_data_qm);
		if ( !TRUEP(CAR(temp_1))) {
		    if ( !TRUEP(memq_function(domain_qm,legal_domains_qm)))
			error_message_qm = tformat_text_string(6,
				string_constant_7,domain_qm,purpose,
				legal_domains_qm,Nil,Nil);
		}
	    }
	}
    }
    if (error_message_qm)
	return VALUES_2(Nil,error_message_qm);
    else {
	temp_1 = phrase_cons(purpose,domain_qm);
	return VALUES_2(temp_1,Nil);
    }
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* SYMBOL-OR-STRING-EVALUATION-SETTER */
Object symbol_or_string_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(110,52);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_1))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_2,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_symbol_or_string_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = copy_for_phrase(evaluation_value);
  end_symbol_or_string_evaluation_setter:
    return result;
}

/* SYMBOL-OR-STRING-EVALUATION-GETTER */
Object symbol_or_string_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(110,53);
    GENSYM_RETURN_ONE(FIXNUMP(slot_value) || slot_value && 
	    SYMBOLP(slot_value) ? slot_value : 
	    copy_evaluation_value_1(slot_value));
    return VALUES_1(Nil);
}

static Object list_constant_3;     /* # */

/* LOCALIZABLE-TERM-EVALUATION-SETTER */
Object localizable_term_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(110,54);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qsymbol,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_localizable_term_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_localizable_term_evaluation_setter:
    return result;
}

/* LOCALIZABLE-TERM-EVALUATION-GETTER */
Object localizable_term_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(110,55);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object Qlocalizable_term;   /* localizable-term */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qsymbol_or_string;   /* symbol-or-string */

static Object Qvalue;              /* value */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_8;   /* "~NT " */

static Object string_constant_9;   /* "~NV must be one of the following types: ~a" */

/* TERM-TRANSLATION-PAIR-EVALUATION-SETTER */
Object term_translation_pair_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(110,56);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_4))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_5,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_term_translation_pair_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_6)) {
	gensymed_symbol = evaluation_value;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlocalizable_term),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		    Qlocalizable_term,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp = parse_result_or_bad_phrase;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsymbol_or_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qvalue,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	result = phrase_cons(temp,temp_1);
      end_safe_category_setter_calling_block:;
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
		  tformat(2,string_constant_8,list_constant_6);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_9,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_term_translation_pair_evaluation_setter:
    return result;
}

/* TERM-TRANSLATION-PAIR-EVALUATION-GETTER */
Object term_translation_pair_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(110,57);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlocalizable_term),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CAR(slot_value);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qlocalizable_term,temp);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsymbol_or_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CDR(slot_value);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qvalue,temp);
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object Qterm_translation_pair;  /* term-translation-pair */

/* TERM-TRANSLATION-PAIRS-EVALUATION-SETTER */
Object term_translation_pairs_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object term_translation_pair, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object elt_1, validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(110,58);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_7))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_8,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_term_translation_pairs_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_9)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	term_translation_pair = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	term_translation_pair = validated_elt;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qterm_translation_pair),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = term_translation_pair;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	result = VALUES_1(ab_loopvar_);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
      end_safe_category_setter_calling_block:;
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
	      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_8,list_constant_9);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_9,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_term_translation_pairs_evaluation_setter:
    return result;
}

/* TERM-TRANSLATION-PAIRS-EVALUATION-GETTER */
Object term_translation_pairs_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object term_translation_pair, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(110,59);
    if (slot_value) {
	term_translation_pair = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	term_translation_pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qterm_translation_pair),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = term_translation_pair;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	ab_loopvar__1 = eval_cons_1(temp,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qmultiple_translations_in_frame;  /* multiple-translations-in-frame */

/* CHECK-FOR-DUPLICATE-INSTANCES-IN-LANGUAGE-TRANSLATION */
Object check_for_duplicate_instances_in_language_translation(target_symbol,
	    frame)
    Object target_symbol, frame;
{
    Object symbol, translation, ab_loop_list_, ab_loop_desetq_, count_1, temp;
    SI_Long ab_loopvar_;

    x_note_fn_call(110,60);
    symbol = Nil;
    translation = Nil;
    ab_loop_list_ = term_translation_pairs(frame);
    ab_loopvar_ = (SI_Long)0L;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    symbol = CAR(ab_loop_desetq_);
    translation = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(symbol,target_symbol))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    goto next_loop;
  end_loop:
    count_1 = FIX(ab_loopvar_);
    goto end_1;
    count_1 = Qnil;
  end_1:;
    temp = FIX((SI_Long)1L);
    if (NUM_GT(count_1,temp))
	return add_to_frame_note_particulars_list_if_necessary(target_symbol,
		Qmultiple_translations_in_frame,frame);
    else
	return VALUES_1(Nil);
}

static Object string_constant_10;  /* "there are ~d translations of ~a in this statement" */

static Object array_constant_6;    /* # */

/* WRITE-MULTIPLE-TRANSLATIONS-IN-FRAME-NOTE */
Object write_multiple_translations_in_frame_note(duplicated_symbols,frame)
    Object duplicated_symbols, frame;
{
    Object number_of_subnotes, target_symbol, ab_loop_list_;
    Object ab_loop_iter_flag_, symbol, ab_loop_list__1, ab_loop_desetq_, temp;
    SI_Long i, ab_loop_bind_, ab_loopvar_, incff_1_arg;
    SI_Long frame_note_index_skip_new_value;

    x_note_fn_call(110,61);
    number_of_subnotes = length(duplicated_symbols);
    target_symbol = Nil;
    ab_loop_list_ = duplicated_symbols;
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(number_of_subnotes);
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    target_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    if (i > ab_loop_bind_)
	goto end_loop;
    symbol = Nil;
    ab_loop_list__1 = term_translation_pairs(frame);
    ab_loopvar_ = (SI_Long)0L;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    symbol = CAR(ab_loop_desetq_);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(symbol,target_symbol))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    temp = FIX(ab_loopvar_);
    goto end_1;
    temp = Qnil;
  end_1:;
    tformat(3,string_constant_10,temp,target_symbol);
    if ( !(i == IFIX(number_of_subnotes)))
	twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)2L));
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    incff_1_arg = i - (SI_Long)1L;
    frame_note_index_skip_new_value = IFIX(Frame_note_index_skip) + 
	    incff_1_arg;
    Frame_note_index_skip = FIX(frame_note_index_skip_new_value);
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

/* CHECK-FOR-OTHER-LANGUAGE-TRANSLATIONS */
Object check_for_other_language_translations varargs_1(int, n)
{
    Object symbol, frame_being_checked;
    Object remove_qm, data, language, temp, purpose, domain, domains, frame;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, frames;
    Object number_of_frames, other_frame, ab_loop_it_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(110,62);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    frame_being_checked = REQUIRED_ARG_nonrelocating();
    remove_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    data = data_of_language_translation(frame_being_checked);
    language = CAR(data);
    temp = CDR(data);
    purpose = CAAR(temp);
    temp = CDR(data);
    temp = CAR(temp);
    domain = CDR(temp);
    domains = kb_property_cons_1(domain,Nil);
    frame = Nil;
    ab_loop_list_ = lookup_kb_specific_property_value(symbol,
	    Translations_for_symbol_kbprop);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (frame_matches_localization_context_p(frame,language,purpose,domains)) {
	ab_loopvar__2 = kb_property_cons_1(frame,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    reclaim_kb_property_list_1(domains);
    frames = ab_loopvar_;
    goto end_1;
    frames = Qnil;
  end_1:;
    number_of_frames = length(frames);
    if (remove_qm) {
	if (IFIX(number_of_frames) == (SI_Long)0L);
	else if (IFIX(number_of_frames) == (SI_Long)1L);
	else if (IFIX(number_of_frames) == (SI_Long)2L) {
	    other_frame = EQ(FIRST(frames),frame_being_checked) ? 
		    SECOND(frames) : FIRST(frames);
	    delete_other_translation_note(other_frame,symbol);
	}
	else {
	    frame = Nil;
	    ab_loop_list_ = frames;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    frame = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    decf_other_translation_note(frame,symbol);
	    goto next_loop_1;
	  end_loop_1:;
	}
    }
    else if (IFIX(number_of_frames) == (SI_Long)0L);
    else if (IFIX(number_of_frames) == (SI_Long)1L) {
	create_other_translation_note(FIRST(frames),symbol,
		FIX((SI_Long)1L),language,purpose,domain);
	create_other_translation_note(frame_being_checked,symbol,
		FIX((SI_Long)1L),language,purpose,domain);
    }
    else {
	frame = Nil;
	ab_loop_list_ = frames;
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = find_other_translation_particular(frame,symbol);
	if (ab_loop_it_)
	    goto end_2;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Nil);
      end_2:;
	frame = Nil;
	ab_loop_list_ = frames;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	incf_other_translation_note(frame,symbol);
	goto next_loop_3;
      end_loop_3:;
	create_other_translation_note(frame_being_checked,symbol,
		number_of_frames,language,purpose,domain);
    }
    return reclaim_kb_property_list_1(frames);
}

/* MAKE-OTHER-TRANSLATION-PARTICULAR */
Object make_other_translation_particular(other_translation_symbol,
	    other_translation_count,other_translation_language,
	    other_translation_purpose,other_translation_domain)
    Object other_translation_symbol, other_translation_count;
    Object other_translation_language, other_translation_purpose;
    Object other_translation_domain;
{
    x_note_fn_call(110,63);
    return kb_property_cons_1(other_translation_symbol,
	    kb_property_cons_1(other_translation_count,
	    kb_property_cons_1(other_translation_language,
	    kb_property_cons_1(other_translation_purpose,
	    kb_property_cons_1(other_translation_domain,Nil)))));
}

static Object Qduplicated_translation;  /* duplicated-translation */

/* FIND-OTHER-TRANSLATION-PARTICULAR */
Object find_other_translation_particular(frame,symbol)
    Object frame, symbol;
{
    Object existing_particulars, temp, particular, ab_loop_list_;

    x_note_fn_call(110,64);
    if (Current_computation_component_particulars)
	existing_particulars = 
		get_particulars_of_frame_note_from_component_particulars(Qduplicated_translation,
		frame,Current_computation_component_particulars);
    else {
	temp = ISVREF(frame,(SI_Long)8L);
	existing_particulars = getfq_function_no_default(CDR(temp),
		Qduplicated_translation);
    }
    if (existing_particulars) {
	particular = Nil;
	ab_loop_list_ = existing_particulars;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	particular = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(particular),symbol))
	    return VALUES_1(particular);
	goto next_loop;
      end_loop:
      nil:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CREATE-OTHER-TRANSLATION-NOTE */
Object create_other_translation_note(frame,symbol,count_1,language,purpose,
	    domain)
    Object frame, symbol, count_1, language, purpose, domain;
{
    Object particular;

    x_note_fn_call(110,65);
    particular = make_other_translation_particular(symbol,count_1,language,
	    purpose,domain);
    return add_to_frame_note_particulars_list_if_necessary(particular,
	    Qduplicated_translation,frame);
}

/* DELETE-OTHER-TRANSLATION-NOTE */
Object delete_other_translation_note(frame,symbol)
    Object frame, symbol;
{
    Object particular;

    x_note_fn_call(110,66);
    particular = find_other_translation_particular(frame,symbol);
    return delete_from_frame_note_particulars_list(particular,
	    Qduplicated_translation,frame);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

/* INCF-OTHER-TRANSLATION-NOTE */
Object incf_other_translation_note(frame,symbol)
    Object frame, symbol;
{
    Object particular, car_arg, car_new_value;

    x_note_fn_call(110,67);
    particular = find_other_translation_particular(frame,symbol);
    car_arg = CDR(particular);
    car_new_value = add1(CAR(car_arg));
    M_CAR(car_arg) = car_new_value;
    return update_representations_of_slot_value(2,frame,
	    Qframe_status_and_notes);
}

/* DECF-OTHER-TRANSLATION-NOTE */
Object decf_other_translation_note(frame,symbol)
    Object frame, symbol;
{
    Object particular, car_arg, car_new_value;

    x_note_fn_call(110,68);
    particular = find_other_translation_particular(frame,symbol);
    car_arg = CDR(particular);
    car_new_value = sub1(CAR(car_arg));
    M_CAR(car_arg) = car_new_value;
    return update_representations_of_slot_value(2,frame,
	    Qframe_status_and_notes);
}

static Object string_constant_11;  /* " (~d) " */

static Object string_constant_12;  /* "the ~a translation of ~a " */

static Object string_constant_13;  /* "as a ~a of " */

static Object string_constant_14;  /* "the" */

static Object string_constant_15;  /* "~a ~a " */

static Object string_constant_16;  /* "is duplicated in " */

static Object string_constant_17;  /* "~a other language-translation items" */

static Object string_constant_18;  /* "another language-translation item" */

/* WRITE-DUPLICATED-TRANSLATION-NOTE */
Object write_duplicated_translation_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    Object number_of_particulars, particular, ab_loop_list_;
    Object ab_loop_iter_flag_, temp, temp_1, count_1;
    SI_Long i, incff_1_arg, frame_note_index_skip_new_value;

    x_note_fn_call(110,69);
    number_of_particulars = length(particulars);
    particular = Nil;
    ab_loop_list_ = particulars;
    i = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    particular = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    if (IFIX(length(particulars)) > (SI_Long)1L)
	tformat(2,string_constant_11,FIX(i));
    temp = CDDR(particular);
    tformat(3,string_constant_12,CAR(temp),CAR(particular));
    temp = CDDDR(particular);
    tformat(2,string_constant_13,CAR(temp));
    temp = CDDDDR(particular);
    if (unique_localization_domain_p(CAR(temp)))
	temp = string_constant_14;
    else {
	temp = CDDDDR(particular);
	temp = supply_a_or_an(CAR(temp));
    }
    temp_1 = CDDDDR(particular);
    tformat(3,string_constant_15,temp,CAR(temp_1));
    tformat(1,string_constant_16);
    temp = CDR(particular);
    count_1 = CAR(temp);
    if (IFIX(count_1) > (SI_Long)1L)
	tformat(2,string_constant_17,count_1);
    else
	tformat(2,string_constant_18,count_1);
    if ( !(i == IFIX(number_of_particulars)))
	twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)2L));
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    if (IFIX(length(particulars)) > (SI_Long)1L) {
	incff_1_arg = i - (SI_Long)1L;
	frame_note_index_skip_new_value = IFIX(Frame_note_index_skip) + 
		incff_1_arg;
	Frame_note_index_skip = FIX(frame_note_index_skip_new_value);
    }
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

static Object list_constant_10;    /* # */

/* CLEAR-TRANSLATION-FRAME-NOTES-IF-ANY */
Object clear_translation_frame_notes_if_any(frame)
    Object frame;
{
    x_note_fn_call(110,70);
    return delete_frame_notes_of_types_in_list(frame,list_constant_10,Nil);
}

void language_INIT()
{
    Object temp, temp_1, named_dynamic_extent_description, temp_2;
    Object symbol_or_string_evaluation_setter_1;
    Object symbol_or_string_evaluation_getter_1;
    Object localizable_term_evaluation_setter_1;
    Object localizable_term_evaluation_getter_1;
    Object term_translation_pair_evaluation_setter_1;
    Object term_translation_pair_evaluation_getter_1;
    Object term_translation_pairs_evaluation_setter_1;
    Object term_translation_pairs_evaluation_getter_1;
    Object write_multiple_translations_in_frame_note_1;
    Object write_duplicated_translation_note_1;
    Object Qmultiply_translated_menu_choices;
    Object Qnon_disjointness_among_language_translations, AB_package;
    Object Qframe_note_writer_1, list_constant_12, Qterm_translation_pairs;
    Object Qnamed, Qtype_specification_simple_expansion, list_constant_25;
    Object list_constant_24, Qab_structure, list_constant_23, list_constant_22;
    Object Qtext, Qab_or, string_constant_41, Qmenu_item_translation_pair;
    Object Qmenu_item_translation_pairs, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_language_translation_for_slot;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, Qreclaim_translations_for_symbol;
    Object Qtranslations_for_symbol;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qdo_not_carry_global_property_value_into_kbs_qm, Qslot_value_writer;
    Object Qwrite_language_translation_from_slot, Qclasses_which_define;
    Object Qput_box_translation_and_text_slot_value;
    Object Qput_box_translation_and_text_slot_value_for_language_translation;
    Object Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_language_translation, Qcleanup;
    Object Qcleanup_for_language_translation, string_constant_31;
    Object string_constant_30, string_constant_29, list_constant_21;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object string_constant_25, string_constant_24, Qstatement, Qsimple_message;
    Object Qnamed_menu, list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_16, list_constant_15;
    Object list_constant_14, Qdefault_localization_domain;
    Object Qnamed_dynamic_extent_description, string_constant_23;
    Object Qtranslation_contributors, Qreclaim_kb_property_list_function;
    Object Qslot_putter, Qput_current_language_if_other_than_default_qm;
    Object Qslot_value_reclaimer;
    Object Qreclaim_current_language_if_other_than_default_qm_value;
    Object Qcurrent_language, Qcompile_current_language_for_slot;
    Object string_constant_22, Qwrite_current_language_from_slot;
    Object Qabsent_slot_putter;
    Object Qput_current_language_if_other_than_english_qm_where_slot_is_absent;
    Object Qcurrent_language_if_other_than_english_qm, Ksystem_frame;
    Object string_constant_21, list_constant_13, string_constant_20;
    Object string_constant_19, Qsystem_table, Qinitialize_default_language;
    Object list_constant_11, Kfuncall;

    x_note_fn_call(110,71);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qdefault_language = STATIC_SYMBOL("DEFAULT-LANGUAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_language,Default_language);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_default_language = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-LANGUAGE",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_language);
    record_system_variable(Qdefault_language,Qlanguage,list_constant_11,
	    Qnil,Qnil,Qnil,Qt);
    Qenglish = STATIC_SYMBOL("ENGLISH",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_language,
	    STATIC_FUNCTION(initialize_default_language,NIL,FALSE,0,0));
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    Qdefault_language_spec_via_environment = 
	    STATIC_SYMBOL("DEFAULT-LANGUAGE-SPEC-VIA-ENVIRONMENT",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qlanguage_parameters = STATIC_SYMBOL("LANGUAGE-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_13 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qlanguage_parameters,
	    list_constant_13);
    string_constant_19 = STATIC_STRING("1l1l83ey");
    string_constant_20 = 
	    STATIC_STRING("1m4z8r83Ixy83Ixy83Tcy83Tcy00001n1l8o1l8l1m8p83BRy000004z8r83=ly83=ly83Tcy83Tcy00001n1m8p830Uy1l83Ey1l8l00000");
    string_constant_21 = 
	    STATIC_STRING("1o8q1n83Tcy1l83-sy83ey1p83Ixy08o8l1m8p83BRy1p83=ly01m8p830Uy83Ey8l");
    temp = regenerate_optimized_constant(string_constant_19);
    temp_1 = regenerate_optimized_constant(string_constant_20);
    add_class_to_environment(9,Qlanguage_parameters,list_constant_13,Nil,
	    temp,Nil,temp_1,list_constant_13,
	    regenerate_optimized_constant(string_constant_21),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qlanguage_parameters,Language_parameters);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qlanguage_parameters,Qlanguage,Ksystem_frame,
	    Qnil,Qnil,Qnil,Qt);
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    Qrussian = STATIC_SYMBOL("RUSSIAN",AB_package);
    Qcurrent_language_if_other_than_default_qm = 
	    STATIC_SYMBOL("CURRENT-LANGUAGE-IF-OTHER-THAN-DEFAULT\?",
	    AB_package);
    Qcurrent_language_if_other_than_english_qm = 
	    STATIC_SYMBOL("CURRENT-LANGUAGE-IF-OTHER-THAN-ENGLISH\?",
	    AB_package);
    Qput_current_language_if_other_than_english_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CURRENT-LANGUAGE-IF-OTHER-THAN-ENGLISH\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_current_language_if_other_than_english_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_current_language_if_other_than_english_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qcurrent_language_if_other_than_english_qm,
	    SYMBOL_FUNCTION(Qput_current_language_if_other_than_english_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcurrent_language = STATIC_SYMBOL("CURRENT-LANGUAGE",AB_package);
    alias_slot_name(3,Qcurrent_language_if_other_than_default_qm,
	    Qcurrent_language,Qlanguage_parameters);
    Qwrite_current_language_from_slot = 
	    STATIC_SYMBOL("WRITE-CURRENT-LANGUAGE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_current_language_from_slot,
	    STATIC_FUNCTION(write_current_language_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qcurrent_language,
	    SYMBOL_FUNCTION(Qwrite_current_language_from_slot),
	    Qslot_value_writer);
    string_constant_22 = 
	    STATIC_STRING("1q1m83BRy83Tby1m83BRy1m9k83vYy1m83Tby1m9k8378y1m83Tby1m9k83kDy1m83Tby1m9k83-C8y1m83Tby83-6y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_22));
    Qcompile_current_language_for_slot = 
	    STATIC_SYMBOL("COMPILE-CURRENT-LANGUAGE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_current_language_for_slot,
	    STATIC_FUNCTION(compile_current_language_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qcurrent_language,
	    SYMBOL_FUNCTION(Qcompile_current_language_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qcurrent_language,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qreclaim_current_language_if_other_than_default_qm_value = 
	    STATIC_SYMBOL("RECLAIM-CURRENT-LANGUAGE-IF-OTHER-THAN-DEFAULT\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_current_language_if_other_than_default_qm_value,
	    STATIC_FUNCTION(reclaim_current_language_if_other_than_default_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qcurrent_language_if_other_than_default_qm,
	    SYMBOL_FUNCTION(Qreclaim_current_language_if_other_than_default_qm_value),
	    Qslot_value_reclaimer);
    Qput_current_language_if_other_than_default_qm = 
	    STATIC_SYMBOL("PUT-CURRENT-LANGUAGE-IF-OTHER-THAN-DEFAULT\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_current_language_if_other_than_default_qm,
	    STATIC_FUNCTION(put_current_language_if_other_than_default_qm,
	    NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qcurrent_language_if_other_than_default_qm,
	    SYMBOL_FUNCTION(Qput_current_language_if_other_than_default_qm),
	    Qslot_putter);
    Qtranslation_contributors = STATIC_SYMBOL("TRANSLATION-CONTRIBUTORS",
	    AB_package);
    Kb_specific_property_names = CONS(Qtranslation_contributors,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qtranslation_contributors,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_kb_property_list_function = 
	    STATIC_SYMBOL("RECLAIM-KB-PROPERTY-LIST-FUNCTION",AB_package);
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qtranslation_contributors,
	    Qreclaim_kb_property_list_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Translation_contributors_kbprop = Qtranslation_contributors;
    list_constant = STATIC_LIST((SI_Long)4L,Qenglish,Qjapanese,Qkorean,Qnil);
    string_constant_23 = STATIC_STRING("LOCALIZATION-CONTEXT");
    if (Localization_context == UNBOUND)
	Localization_context = make_recursive_lock(2,Kname,string_constant_23);
    Qlocalization_context = STATIC_SYMBOL("LOCALIZATION-CONTEXT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocalization_context,Localization_context);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qlocalization_context,
	    Qlanguage,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qlocalization_context,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_localization_purpose_qm == UNBOUND)
	Current_localization_purpose_qm = Nil;
    if (Current_localization_domains_qm == UNBOUND)
	Current_localization_domains_qm = Nil;
    if (Known_localizations == UNBOUND)
	Known_localizations = Nil;
    Qdefault_localization_domain = 
	    STATIC_SYMBOL("DEFAULT-LOCALIZATION-DOMAIN",AB_package);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qmenu,Qtable);
    list_constant_17 = STATIC_LIST((SI_Long)2L,
	    Qdefault_localization_domain,list_constant_14);
    Qeditor = STATIC_SYMBOL("EDITOR",AB_package);
    Qtext_editor = STATIC_SYMBOL("TEXT-EDITOR",AB_package);
    Qicon_editor = STATIC_SYMBOL("ICON-EDITOR",AB_package);
    Qg2_login_dialog = STATIC_SYMBOL("G2-LOGIN-DIALOG",AB_package);
    Qpassword_change_dialog = STATIC_SYMBOL("PASSWORD-CHANGE-DIALOG",
	    AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)4L,Qtext_editor,Qicon_editor,
	    Qg2_login_dialog,Qpassword_change_dialog);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qeditor,list_constant_15);
    Qlocalization_purpose = STATIC_SYMBOL("LOCALIZATION-PURPOSE",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qbutton_label = STATIC_SYMBOL("BUTTON-LABEL",AB_package);
    Qmenu_item = STATIC_SYMBOL("MENU-ITEM",AB_package);
    Qsimple_message = STATIC_SYMBOL("SIMPLE-MESSAGE",AB_package);
    Qab_simple_condition = STATIC_SYMBOL("SIMPLE-CONDITION",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)5L,Qattribute,Qbutton_label,
	    Qmenu_item,Qsimple_message,Qab_simple_condition);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qlocalization_purpose,
	    list_constant_16);
    list_constant_20 = STATIC_LIST((SI_Long)3L,list_constant_17,
	    list_constant_18,list_constant_19);
    populate_the_fixed_localization_categories(list_constant_20);
    Qmain_menu = STATIC_SYMBOL("MAIN-MENU",AB_package);
    Qeditor_operations_menu = STATIC_SYMBOL("EDITOR-OPERATIONS-MENU",
	    AB_package);
    Qdomains_consistent_with_localization_purpose = 
	    STATIC_SYMBOL("DOMAINS-CONSISTENT-WITH-LOCALIZATION-PURPOSE",
	    AB_package);
    Domains_consistent_with_localization_purpose_prop = 
	    Qdomains_consistent_with_localization_purpose;
    Kaccepts_classes_qm = STATIC_SYMBOL("ACCEPTS-CLASSES\?",Pkeyword);
    Kfixed_domain = STATIC_SYMBOL("FIXED-DOMAIN",Pkeyword);
    Qno_fixed_localization_domains = 
	    STATIC_SYMBOL("NO-FIXED-LOCALIZATION-DOMAINS",AB_package);
    define_domains_consistent_with_localization_purpose(7,Qbutton_label,
	    Kdefault,Qeditor,Kaccepts_classes_qm,Nil,Kfixed_domain,Qeditor);
    define_domains_consistent_with_localization_purpose(7,Qattribute,
	    Kdefault,Qtable,Kaccepts_classes_qm,T,Kfixed_domain,
	    Qno_fixed_localization_domains);
    Qnamed_menu = STATIC_SYMBOL("NAMED-MENU",AB_package);
    define_domains_consistent_with_localization_purpose(7,Qmenu_item,
	    Kdefault,Qmenu,Kaccepts_classes_qm,T,Kfixed_domain,Qnamed_menu);
    define_domains_consistent_with_localization_purpose(7,Qsimple_message,
	    Kdefault,Qeditor,Kaccepts_classes_qm,T,Kfixed_domain,Qeditor);
    define_domains_consistent_with_localization_purpose(7,
	    Qab_simple_condition,Kdefault,Qeditor,Kaccepts_classes_qm,T,
	    Kfixed_domain,Qeditor);
    Qlanguage_translation = STATIC_SYMBOL("LANGUAGE-TRANSLATION",AB_package);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    list_constant_21 = STATIC_CONS(Qstatement,Qnil);
    check_if_superior_classes_are_defined(Qlanguage_translation,
	    list_constant_21);
    string_constant_24 = STATIC_STRING("1m1m8v835dy1l8t");
    string_constant_25 = 
	    STATIC_STRING("1n4z8r83--y83--y835dy835dy00001p1l8l1m8p83-*y1m83Dy53=5yWill allow 0 or more author entries. each author entry may have ~\n      ");
    string_constant_26 = 
	    STATIC_STRING(" a date. authors: ([ name: symbol, date: gensym-time ] * ), ~\n       editor-grammar: struct, defining-class: item, writable: tru");
    string_constant_27 = 
	    STATIC_STRING("e1l83Ey1l83Uy000004z8r83-0y83-0y835dy835dy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however");
    string_constant_28 = 
	    STATIC_STRING(", no documentation is available at this time)000004z8r83ry83ry835dy835dy00001p1l8l1n8p835dy83Gy1l83-5y1l8o1l83-3y00000");
    string_constant_29 = 
	    STATIC_STRING("1p8q1o835dy1l83*ry1m8v835dy8t1o83--y01m8p83-*y1m83Dy53=5yWill allow 0 or more author entries. each author entry may have ~\n     ");
    string_constant_30 = 
	    STATIC_STRING("  a date. authors: ([ name: symbol, date: gensym-time ] * ), ~\n       editor-grammar: struct, defining-class: item, writable: tr");
    string_constant_31 = 
	    STATIC_STRING("ue1n83-0y01m8p83-0y1o83ry01n8p835dy83Gy83-5y");
    temp = regenerate_optimized_constant(string_constant_24);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_25,
	    string_constant_26,string_constant_27,string_constant_28));
    add_class_to_environment(9,Qlanguage_translation,list_constant_21,Nil,
	    temp,Nil,temp_1,list_constant_21,
	    regenerate_optimized_constant(LIST_3(string_constant_29,
	    string_constant_30,string_constant_31)),Nil);
    Language_translation_class_description = 
	    lookup_global_or_kb_specific_property_value(Qlanguage_translation,
	    Class_description_gkbprop);
    Qcleanup_for_language_translation = 
	    STATIC_SYMBOL("CLEANUP-FOR-LANGUAGE-TRANSLATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_language_translation,
	    STATIC_FUNCTION(cleanup_for_language_translation,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_language_translation);
    set_get(Qlanguage_translation,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qlanguage_translation,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qinitialize_after_reading_for_language_translation = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-LANGUAGE-TRANSLATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_language_translation,
	    STATIC_FUNCTION(initialize_after_reading_for_language_translation,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qinitialize_after_reading_for_language_translation);
    set_get(Qlanguage_translation,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qlanguage_translation,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qput_box_translation_and_text_slot_value_for_language_translation = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-LANGUAGE-TRANSLATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_language_translation,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_language_translation,
	    NIL,FALSE,3,3));
    Qput_box_translation_and_text_slot_value = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_language_translation);
    set_get(Qlanguage_translation,Qput_box_translation_and_text_slot_value,
	    temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp_2 = CONS(Qlanguage_translation,temp);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp_2,
	    Qclasses_which_define);
    array_constant_3 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    string_constant = STATIC_STRING("~%  ");
    array_constant_5 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    string_constant_1 = STATIC_STRING("~s");
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qwrite_language_translation_from_slot = 
	    STATIC_SYMBOL("WRITE-LANGUAGE-TRANSLATION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_language_translation_from_slot,
	    STATIC_FUNCTION(write_language_translation_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qlanguage_translation,
	    SYMBOL_FUNCTION(Qwrite_language_translation_from_slot),
	    Qslot_value_writer);
    Qtranslations_for_symbol = STATIC_SYMBOL("TRANSLATIONS-FOR-SYMBOL",
	    AB_package);
    Kb_specific_property_names = CONS(Qtranslations_for_symbol,
	    Kb_specific_property_names);
    mutate_global_property(Qtranslations_for_symbol,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_translations_for_symbol = 
	    STATIC_SYMBOL("RECLAIM-TRANSLATIONS-FOR-SYMBOL",AB_package);
    mutate_global_property(Qtranslations_for_symbol,
	    Qreclaim_translations_for_symbol,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Translations_for_symbol_kbprop = Qtranslations_for_symbol;
    SET_SYMBOL_FUNCTION(Qreclaim_translations_for_symbol,
	    STATIC_FUNCTION(reclaim_translations_for_symbol,NIL,FALSE,1,1));
    Qenglish_localization = STATIC_SYMBOL("ENGLISH-LOCALIZATION",AB_package);
    English_localization_prop = Qenglish_localization;
    Kfirst = STATIC_SYMBOL("FIRST",Pkeyword);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qterm_translation_pairs = STATIC_SYMBOL("TERM-TRANSLATION-PAIRS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qterm_translation_pairs,
	    STATIC_FUNCTION(term_translation_pairs,NIL,FALSE,1,1));
    string_constant_32 = 
	    STATIC_STRING("1l1n835dy1q1m9k83*Xy83Tby1m9k83vy83-2Sy1m9k83-Py9l1nmoq");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qterm_translation_pairs);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_32));
    string_constant_33 = 
	    STATIC_STRING("1l1n835dy1o1m9k83*Xy83Tby1m9k83-Py83-eLy2lmo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_33));
    string_constant_34 = 
	    STATIC_STRING("1o1n83-2Sy1q1m9k83*5y83=Zy83-d7y1m9k83-Ty83=Zy83-Gy2lnq1n83-2Sy1n1m9k83*5y83=Zy83-d7y1ln1n83-2Sy1q1m9k83*5y83=Zy83-d7y1m9k83*Xy1");
    string_constant_35 = 
	    STATIC_STRING("m9k9l83-g2y2lnq1n83-2Sy1q1m9k83*5y83=Zy83-d7y1m9k83*Xy1m9k9l83-SQy2lnq");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_34,
	    string_constant_35)));
    Qcompile_language_translation_for_slot = 
	    STATIC_SYMBOL("COMPILE-LANGUAGE-TRANSLATION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_language_translation_for_slot,
	    STATIC_FUNCTION(compile_language_translation_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qlanguage_translation,
	    SYMBOL_FUNCTION(Qcompile_language_translation_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlanguage_translation,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_2 = 
	    STATIC_STRING("~a is not a known localization purpose");
    string_constant_3 = 
	    STATIC_STRING("The localization purpose ~a cannot be defaulted. ~\n                    An explicit domain must be provided.");
    string_constant_4 = 
	    STATIC_STRING("The class name ~a is not a valid domain for the localization ~\n                purpose ~a because that purpose does not apply to items.");
    string_constant_5 = 
	    STATIC_STRING("No domain information is available for the ~\n                   localization purpose ~a.");
    Qpassword_change = STATIC_SYMBOL("PASSWORD-CHANGE",AB_package);
    string_constant_6 = 
	    STATIC_STRING("~a is not a legal domain for the localization purpose ~a");
    string_constant_7 = 
	    STATIC_STRING("~a is not one of the legal specific domains for the ~\n                      localization purpose ~a, i.e. ~a");
    string_constant_36 = STATIC_STRING("1l1n83-sPy1n83-2Ry1m9k9l83nWy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_36));
    Qterm_translation_pair = STATIC_SYMBOL("TERM-TRANSLATION-PAIR",AB_package);
    add_grammar_rules_for_list(5,Qterm_translation_pairs,
	    Qterm_translation_pair,Qcm,Nil,Nil);
    string_constant_37 = 
	    STATIC_STRING("1p1m83-2Ry83kgy1m83-2Ry83q+y1m83-2Ry83B2y1m83-2Ry83a3y1m83-2Ry83-pNy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_37));
    string_constant_38 = 
	    STATIC_STRING("1p1m83kgy83jPy1m83kgy83-2hy1m83kgy83oby1m83jPy83-2y1m83-2hy83-2y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_38));
    string_constant_39 = STATIC_STRING("1m1m83q+y83*my1m83q+y83FJy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_39));
    string_constant_40 = STATIC_STRING("1m1m83nWy83-2y1m83nWy83-Uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_40));
    Qmenu_item_translation_pairs = 
	    STATIC_SYMBOL("MENU-ITEM-TRANSLATION-PAIRS",AB_package);
    Qmenu_item_translation_pair = 
	    STATIC_SYMBOL("MENU-ITEM-TRANSLATION-PAIR",AB_package);
    add_grammar_rules_for_list(5,Qmenu_item_translation_pairs,
	    Qmenu_item_translation_pair,Qcm,Nil,Nil);
    string_constant_41 = STATIC_STRING("1l1n83-eKy1n83kgy1m9k9l83nWy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_41));
    Qsymbol_or_string = STATIC_SYMBOL("SYMBOL-OR-STRING",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,Qtext);
    set_property_value_function(get_symbol_properties_function(Qsymbol_or_string),
	    Qtype_specification_simple_expansion,list_constant_2);
    define_type_specification_explicit_complex_type(Qsymbol_or_string,
	    list_constant_2);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,Qsymbol_or_string);
    symbol_or_string_evaluation_setter_1 = 
	    STATIC_FUNCTION(symbol_or_string_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qsymbol_or_string,
	    symbol_or_string_evaluation_setter_1);
    symbol_or_string_evaluation_getter_1 = 
	    STATIC_FUNCTION(symbol_or_string_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsymbol_or_string,
	    symbol_or_string_evaluation_getter_1);
    Qlocalizable_term = STATIC_SYMBOL("LOCALIZABLE-TERM",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlocalizable_term),
	    Qtype_specification_simple_expansion,Qsymbol);
    define_type_specification_explicit_complex_type(Qlocalizable_term,Qsymbol);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,Qlocalizable_term);
    localizable_term_evaluation_setter_1 = 
	    STATIC_FUNCTION(localizable_term_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlocalizable_term,
	    localizable_term_evaluation_setter_1);
    localizable_term_evaluation_getter_1 = 
	    STATIC_FUNCTION(localizable_term_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlocalizable_term,
	    localizable_term_evaluation_getter_1);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_6 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qterm_translation_pair),
	    Qtype_specification_simple_expansion,list_constant_6);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qlocalizable_term,
	    list_constant_3);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qvalue,list_constant_1);
    list_constant_24 = STATIC_LIST((SI_Long)2L,list_constant_22,
	    list_constant_23);
    list_constant_25 = STATIC_LIST((SI_Long)3L,Qand,Qlocalizable_term,Qvalue);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_24,list_constant_25);
    define_type_specification_explicit_complex_type(Qterm_translation_pair,
	    list_constant_5);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qnamed,Qterm_translation_pair);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_8 = STATIC_STRING("~NT ");
    string_constant_9 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    term_translation_pair_evaluation_setter_1 = 
	    STATIC_FUNCTION(term_translation_pair_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qterm_translation_pair,
	    term_translation_pair_evaluation_setter_1);
    term_translation_pair_evaluation_getter_1 = 
	    STATIC_FUNCTION(term_translation_pair_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qterm_translation_pair,
	    term_translation_pair_evaluation_getter_1);
    list_constant_9 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qterm_translation_pairs),
	    Qtype_specification_simple_expansion,list_constant_9);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_4,
	    FIX((SI_Long)1L));
    define_type_specification_explicit_complex_type(Qterm_translation_pairs,
	    list_constant_8);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,Qterm_translation_pairs);
    term_translation_pairs_evaluation_setter_1 = 
	    STATIC_FUNCTION(term_translation_pairs_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qterm_translation_pairs,
	    term_translation_pairs_evaluation_setter_1);
    term_translation_pairs_evaluation_getter_1 = 
	    STATIC_FUNCTION(term_translation_pairs_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qterm_translation_pairs,
	    term_translation_pairs_evaluation_getter_1);
    Qmultiple_translations_in_frame = 
	    STATIC_SYMBOL("MULTIPLE-TRANSLATIONS-IN-FRAME",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_10 = 
	    STATIC_STRING("there are ~d translations of ~a in this statement");
    array_constant_6 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    write_multiple_translations_in_frame_note_1 = 
	    STATIC_FUNCTION(write_multiple_translations_in_frame_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qmultiple_translations_in_frame,
	    write_multiple_translations_in_frame_note_1,Qframe_note_writer_1);
    Qduplicated_translation = STATIC_SYMBOL("DUPLICATED-TRANSLATION",
	    AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    string_constant_11 = STATIC_STRING(" (~d) ");
    string_constant_12 = STATIC_STRING("the ~a translation of ~a ");
    string_constant_13 = STATIC_STRING("as a ~a of ");
    string_constant_14 = STATIC_STRING("the");
    string_constant_15 = STATIC_STRING("~a ~a ");
    string_constant_16 = STATIC_STRING("is duplicated in ");
    string_constant_17 = STATIC_STRING("~a other language-translation items");
    string_constant_18 = STATIC_STRING("another language-translation item");
    write_duplicated_translation_note_1 = 
	    STATIC_FUNCTION(write_duplicated_translation_note,NIL,FALSE,2,2);
    mutate_global_property(Qduplicated_translation,
	    write_duplicated_translation_note_1,Qframe_note_writer_1);
    Qnon_disjointness_among_language_translations = 
	    STATIC_SYMBOL("NON-DISJOINTNESS-AMONG-LANGUAGE-TRANSLATIONS",
	    AB_package);
    Qmultiply_translated_menu_choices = 
	    STATIC_SYMBOL("MULTIPLY-TRANSLATED-MENU-CHOICES",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)4L,Qduplicated_translation,
	    Qmultiple_translations_in_frame,
	    Qnon_disjointness_among_language_translations,
	    Qmultiply_translated_menu_choices);
}
