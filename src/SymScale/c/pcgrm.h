/* pcgrm.h -- Header File for pcgrm.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qnum_eq;
extern Object Qcdr;
extern Object Qerror;
extern Object Qevery;
extern Object Qfloat;
extern Object Qgo;
extern Object Qmember;
extern Object Qotherwise;
extern Object Qquote;
extern Object Qsymbol;
extern Object Qunsigned_byte;

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

extern Object add_grammar_rules_for_list(int,...);
extern Object add_grammar_rules_function(Object);
extern Object clear_optimized_constants(void);
extern Object compile_class_of_procedure_invocation_qm_for_slot(int,...);
extern Object compile_procedure_name_qm_for_slot(int,...);
extern Object convert_to_true_list(Object);
extern Object def_procedure_function_template(Object);
extern Object define_type_specification_explicit_complex_type(Object,Object);
extern Object extend_procedure_grammar(void);
extern Object fix_case_choice(Object);
extern Object fix_procedure_definition(Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object make_phrase_list(Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object nil_function(Object);
extern Object phrase_cons(Object,Object);
extern Object phrase_list_2(Object,Object);
extern Object push_optimized_constant(Object);
extern Object regenerate_optimized_constant(Object);
extern Object set_evaluation_value_to_category_function(Object,Object);
extern Object set_grammar_transform_can_return_bad_phrase_p(Object);
extern Object set_property_value_function(Object,Object,Object);
extern Object set_slot_value_to_evaluation_value_function(Object,Object);
extern Object test_call_next_method_parse(Object);
extern Object twrite(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_symbol(int,...);
extern Object type_error_in_setter(Object,Object,Object,Object,Object,Object,Object);
extern Object type_specification_type_p__with_explanation(Object,Object);
extern Object write_class_of_procedure_invocation_qm_from_slot(Object,Object);
extern Object write_procedure_name_qm_from_slot(Object,Object);
extern Object write_read_only_procedure_name_qm_from_slot(Object,Object);

#else

extern Object add_grammar_rules_for_list();
extern Object add_grammar_rules_function();
extern Object clear_optimized_constants();
extern Object compile_class_of_procedure_invocation_qm_for_slot();
extern Object compile_procedure_name_qm_for_slot();
extern Object convert_to_true_list();
extern Object def_procedure_function_template();
extern Object define_type_specification_explicit_complex_type();
extern Object extend_procedure_grammar();
extern Object fix_case_choice();
extern Object fix_procedure_definition();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object make_phrase_list();
extern Object memq_function();
extern Object mutate_global_property();
extern Object nil_function();
extern Object phrase_cons();
extern Object phrase_list_2();
extern Object push_optimized_constant();
extern Object regenerate_optimized_constant();
extern Object set_evaluation_value_to_category_function();
extern Object set_grammar_transform_can_return_bad_phrase_p();
extern Object set_property_value_function();
extern Object set_slot_value_to_evaluation_value_function();
extern Object test_call_next_method_parse();
extern Object twrite();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_symbol();
extern Object type_error_in_setter();
extern Object type_specification_type_p__with_explanation();
extern Object write_class_of_procedure_invocation_qm_from_slot();
extern Object write_procedure_name_qm_from_slot();
extern Object write_read_only_procedure_name_qm_from_slot();

#endif

/* variables/constants */
extern Object Bad_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Context_of_type_failure, Qcontext_of_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Current_edit_state, Qcurrent_edit_state);
extern Object Evaluation_true_value;
DECLARE_VARIABLE_WITH_SYMBOL(Last_slot_checked_of_type_failure, Qlast_slot_checked_of_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Method_class_description, Qmethod_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Procedure_function_template_alist, Qprocedure_function_template_alist);
DECLARE_VARIABLE_WITH_SYMBOL(Reason_for_type_failure, Qreason_for_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Type_at_type_failure, Qtype_at_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Value_at_type_failure, Qvalue_at_type_failure);
