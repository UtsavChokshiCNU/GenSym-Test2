/* gram1.h -- Header File for gram1.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qstar;
extern Object Qplus;
extern Object Qminus;
extern Object Qslash;
extern Object Qfirst;
extern Object Qlast;
extern Object Qquote;
extern Object Qsecond;
extern Object Qsequence;
extern Object Qthe;
extern Object Qvalues;

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
extern Object clear_optimized_constants(void);
extern Object filter_out_region_icon_color(Object);
extern Object filter_out_the_text_of_and_region_icon_color(Object);
extern Object filter_out_the_text_of_as_a_special_case(Object);
extern Object get_explicitly_specified_local_name_of_role_if_any(Object);
extern Object memq_function(Object,Object);
extern Object phrase_for_constant_p(Object);
extern Object phrase_list_3(Object,Object,Object);
extern Object push_optimized_constant(Object);
extern Object quoted_symbol_phrase_p(Object);
extern Object regenerate_optimized_constant(Object);
extern Object reject_if_sequence_constant(Object);
extern Object reject_if_structure_constant(Object);
extern Object role_of_designation(Object);
extern Object set_grammar_transform_can_return_bad_phrase_p(Object);
extern Object simple_role_of_role(Object);
extern Object simple_role_p(Object);
extern Object transpose_sum(Object);
extern Object transpose_sum_1(Object,Object,Object);
extern Object transpose_term(Object);
extern Object transpose_term_1(Object,Object,Object);

#else

extern Object add_grammar_rules_function();
extern Object clear_optimized_constants();
extern Object filter_out_region_icon_color();
extern Object filter_out_the_text_of_and_region_icon_color();
extern Object filter_out_the_text_of_as_a_special_case();
extern Object get_explicitly_specified_local_name_of_role_if_any();
extern Object memq_function();
extern Object phrase_for_constant_p();
extern Object phrase_list_3();
extern Object push_optimized_constant();
extern Object quoted_symbol_phrase_p();
extern Object regenerate_optimized_constant();
extern Object reject_if_sequence_constant();
extern Object reject_if_structure_constant();
extern Object role_of_designation();
extern Object set_grammar_transform_can_return_bad_phrase_p();
extern Object simple_role_of_role();
extern Object simple_role_p();
extern Object transpose_sum();
extern Object transpose_sum_1();
extern Object transpose_term();
extern Object transpose_term_1();

#endif

/* variables/constants */
extern Object Bad_phrase;
