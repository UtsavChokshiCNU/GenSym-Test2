/* gram4.h -- Header File for gram4.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qplus;
extern Object Qnum_ne;
extern Object Qnum_lt;
extern Object Qnum_eq;
extern Object Qnum_gt;
extern Object Qand;
extern Object Qcdr;
extern Object Qdelete;
extern Object Qevery;
extern Object Qfirst;
extern Object Qlast;
extern Object Qlist;
extern Object Qnot;
extern Object Qposition;
extern Object Qquote;
extern Object Qremove;
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
extern Object assq_function(Object,Object);
extern Object car_2_1(Object);
extern Object category_hack(Object);
extern Object check_ddd_dddd_format(Object);
extern Object choose_is_or_eq(Object);
extern Object clear_optimized_constants(void);
extern Object color_or_metacolor_p(Object);
extern Object connection_vertices_are_constant_list_qm(Object);
extern Object convert_connection_details_specifiers_to_canonical_form(Object);
extern Object decode_format(Object);
extern Object designation_operator_or_giver_of_value_p(Object);
extern Object filter_out_illegal_color_names(Object);
extern Object filter_out_illegal_region_names(Object);
extern Object fix_action_list(Object);
extern Object fix_in_order_action_list(Object);
extern Object fix_iqe(Object,Object);
extern Object fix_nupec_synchronize(Object);
extern Object fix_start_action(Object);
extern Object fuzzy_comparator_reparser(Object);
extern Object g2_list_remove(Object,Object,Object);
extern Object illegal_region_name_p(Object);
extern Object make_phrase_list(Object);
extern Object memq_function(Object,Object);
extern Object phrase_cons(Object,Object);
extern Object phrase_list_2(Object,Object);
extern Object phrase_list_3(Object,Object,Object);
extern Object phrase_list_4(Object,Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object put_connection_details_specifier_into_canonical_form(Object,Object);
extern Object put_designation_in_qualifier(Object);
extern Object regenerate_optimized_constant(Object);
extern Object reject_transfer_to_the_mouse_of(Object);
extern Object rgb_color_p(Object);
extern Object semi_open_category_p(int,...);
extern Object set_grammar_transform_can_return_bad_phrase_p(Object);
extern Object symbol_cannot_be_true_false_or_not(Object);
extern Object symbol_name_text_string(Object);
extern Object text_string_length(Object);
extern Object unlist_1(Object);
extern Object unlist_1_2(Object);
extern Object validate_change_nth_element_parse(Object);
extern Object validate_change_nth_element_parse_1(Object);
extern Object wide_character_member(Object,Object);

#else

extern Object add_grammar_rules_function();
extern Object assq_function();
extern Object car_2_1();
extern Object category_hack();
extern Object check_ddd_dddd_format();
extern Object choose_is_or_eq();
extern Object clear_optimized_constants();
extern Object color_or_metacolor_p();
extern Object connection_vertices_are_constant_list_qm();
extern Object convert_connection_details_specifiers_to_canonical_form();
extern Object decode_format();
extern Object designation_operator_or_giver_of_value_p();
extern Object filter_out_illegal_color_names();
extern Object filter_out_illegal_region_names();
extern Object fix_action_list();
extern Object fix_in_order_action_list();
extern Object fix_iqe();
extern Object fix_nupec_synchronize();
extern Object fix_start_action();
extern Object fuzzy_comparator_reparser();
extern Object g2_list_remove();
extern Object illegal_region_name_p();
extern Object make_phrase_list();
extern Object memq_function();
extern Object phrase_cons();
extern Object phrase_list_2();
extern Object phrase_list_3();
extern Object phrase_list_4();
extern Object push_optimized_constant();
extern Object put_connection_details_specifier_into_canonical_form();
extern Object put_designation_in_qualifier();
extern Object regenerate_optimized_constant();
extern Object reject_transfer_to_the_mouse_of();
extern Object rgb_color_p();
extern Object semi_open_category_p();
extern Object set_grammar_transform_can_return_bad_phrase_p();
extern Object symbol_cannot_be_true_false_or_not();
extern Object symbol_name_text_string();
extern Object text_string_length();
extern Object unlist_1();
extern Object unlist_1_2();
extern Object validate_change_nth_element_parse();
extern Object validate_change_nth_element_parse_1();
extern Object wide_character_member();

#endif

/* variables/constants */
extern Object Bad_phrase;
