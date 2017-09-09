/* gram2.h -- Header File for gram2.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qstar;
extern Object Qslash;
extern Object Qnum_eq;
extern Object Qcount;
extern Object Qevery;
extern Object Qfirst;
extern Object Kkey;
extern Object Qlist;
extern Object Qmember;
extern Object Qnot;
extern Object Qnumber;
extern Object Qquote;
extern Object Qsecond;
extern Object Qthe;

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

extern Object add_grammar_rules_function(Object);
extern Object check_number_of_args(Object);
extern Object clear_optimized_constants(void);
extern Object convert_class_qualified_list_to_keyword_symbol(Object);
extern Object convert_history_interval(Object);
extern Object convert_history_interval_maybe_cdr(Object);
extern Object flatten_is_of_class_type_spec(Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object make_unique_slot_name_symbol(Object,Object);
extern Object memq_function(Object,Object);
extern Object patch_aggregator_scope(Object);
extern Object phrase_cons(Object,Object);
extern Object phrase_list_2(Object,Object);
extern Object phrase_list_3(Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object regenerate_optimized_constant(Object);
extern Object reject_text_of_attribute_reference(Object);
extern Object role_of_designation(Object);
extern Object set_grammar_transform_can_return_bad_phrase_p(Object);
extern Object simple_role_of_role(Object);
extern Object simplify_star_and_sl(Object);
extern Object translate_role_and_preposition(Object);
extern Object translate_role_local_name_and_preposition(Object);

#else

extern Object add_grammar_rules_function();
extern Object check_number_of_args();
extern Object clear_optimized_constants();
extern Object convert_class_qualified_list_to_keyword_symbol();
extern Object convert_history_interval();
extern Object convert_history_interval_maybe_cdr();
extern Object flatten_is_of_class_type_spec();
extern Object lookup_global_or_kb_specific_property_value();
extern Object make_unique_slot_name_symbol();
extern Object memq_function();
extern Object patch_aggregator_scope();
extern Object phrase_cons();
extern Object phrase_list_2();
extern Object phrase_list_3();
extern Object push_optimized_constant();
extern Object regenerate_optimized_constant();
extern Object reject_text_of_attribute_reference();
extern Object role_of_designation();
extern Object set_grammar_transform_can_return_bad_phrase_p();
extern Object simple_role_of_role();
extern Object simplify_star_and_sl();
extern Object translate_role_and_preposition();
extern Object translate_role_local_name_and_preposition();

#endif

/* variables/constants */
extern Object Argument_range_gkbprop;
extern Object Bad_phrase;
extern Object Built_in_functions;
