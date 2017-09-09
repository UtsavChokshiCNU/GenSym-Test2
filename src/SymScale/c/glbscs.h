/* glbscs.h -- Header File for glbscs.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Kelement_type;
extern Object Qformat;
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

extern Object ab_assoc_eql(Object,Object);
extern Object ab_assoc_equal(Object,Object);
extern Object ab_gensym(int,...);
extern Object ab_member_equal(Object,Object);
extern Object assq_function(Object,Object);
extern Object clear_optimized_constants(void);
extern Object coerce_to_gensym_float_function(Object);
extern Object eq_or_memq(Object,Object);
extern Object format_symbol(int,...);
extern Object ftruncatee_up(Object);
extern Object g_logf(Object);
extern Object gensym_gensym(void);
extern Object getfq_function(Object,Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object inline_access_once(Object);
extern Object inline_barrier(void);
extern Object memq_function(Object,Object);
extern Object pct_pointer(Object);
extern Object print_random_object_prefix(Object,Object);
extern Object print_random_object_prefix_for_gsi(Object,Object);
extern Object print_random_object_suffix(Object,Object);
extern Object print_random_object_suffix_for_gsi(Object,Object);
extern Object push_optimized_constant(Object);
extern Object read_optimized_constant(void);
extern Object regenerate_optimized_constant(Object);
extern Object regenerate_standard_symbols(Object);
extern Object rem_fixnums(Object,Object);
extern Object reusable_gensyms(void);
extern Object star_f_safe(Object,Object);
extern Object truncatef_first(Object,Object);
extern Object two_arg_gcdf(Object,Object);
extern Object two_arg_lcmf(Object,Object);

#else

extern Object ab_assoc_eql();
extern Object ab_assoc_equal();
extern Object ab_gensym();
extern Object ab_member_equal();
extern Object assq_function();
extern Object clear_optimized_constants();
extern Object coerce_to_gensym_float_function();
extern Object eq_or_memq();
extern Object format_symbol();
extern Object ftruncatee_up();
extern Object g_logf();
extern Object gensym_gensym();
extern Object getfq_function();
extern Object getfq_function_no_default();
extern Object inline_access_once();
extern Object inline_barrier();
extern Object memq_function();
extern Object pct_pointer();
extern Object print_random_object_prefix();
extern Object print_random_object_prefix_for_gsi();
extern Object print_random_object_suffix();
extern Object print_random_object_suffix_for_gsi();
extern Object push_optimized_constant();
extern Object read_optimized_constant();
extern Object regenerate_optimized_constant();
extern Object regenerate_standard_symbols();
extern Object rem_fixnums();
extern Object reusable_gensyms();
extern Object star_f_safe();
extern Object truncatef_first();
extern Object two_arg_gcdf();
extern Object two_arg_lcmf();

#endif

/* variables/constants */
extern Object Atomic_stamp;
DECLARE_VARIABLE_WITH_SYMBOL(Available_reusable_gensyms, Qavailable_reusable_gensyms);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_1, Qdebug_1);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_10, Qdebug_10);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_11, Qdebug_11);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_12, Qdebug_12);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_2, Qdebug_2);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_3, Qdebug_3);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_4, Qdebug_4);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_5, Qdebug_5);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_6, Qdebug_6);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_7, Qdebug_7);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_8, Qdebug_8);
DECLARE_VARIABLE_WITH_SYMBOL(Debug_9, Qdebug_9);
DECLARE_VARIABLE_WITH_SYMBOL(Destination_for_symbol_with_preserved_cells, Qdestination_for_symbol_with_preserved_cells);
DECLARE_VARIABLE_WITH_SYMBOL(Keyword_package_1, Qkeyword_package_1);
DECLARE_VARIABLE_WITH_SYMBOL(Lisp_package_1, Qlisp_package_1);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_funcalled_functions, Qlist_of_funcalled_functions);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_symbols_for_symbol_value, Qlist_of_symbols_for_symbol_value);
#define Most_negative_fixnum32 FIX((SI_Long)-536870912L)
extern Object Most_negative_fixnum_as_float;
extern Object Most_negative_int64;
#define Most_positive_fixnum32 FIX((SI_Long)536870911L)
extern Object Most_positive_fixnum32_as_float;
extern Object Most_positive_fixnum32_plus_one;
extern Object Most_positive_fixnum32_plus_one_as_float;
extern Object Most_positive_fixnum_as_float;
extern Object Most_positive_int64;
extern Object Negative_fifty_million;
DECLARE_VARIABLE_WITH_SYMBOL(Optimized_constant_op_codes, Qoptimized_constant_op_codes);
DECLARE_VARIABLE_WITH_SYMBOL(Optimized_constant_pc, Qoptimized_constant_pc);
DECLARE_VARIABLE_WITH_SYMBOL(Optimized_constant_vector, Qoptimized_constant_vector);
DECLARE_VARIABLE_WITH_SYMBOL(Optimized_constant_vector_index, Qoptimized_constant_vector_index);
#define Optimized_constant_vector_length FIX((SI_Long)1300L)
extern Object Rational_float_epsilon;
DECLARE_VARIABLE_WITH_SYMBOL(Reusable_gensyms, Qreusable_gensyms);
DECLARE_VARIABLE_WITH_SYMBOL(Special_variable_for_use_value_macro, Qspecial_variable_for_use_value_macro);
extern Object Standard_symbols_for_optimized_constant_qm;
DECLARE_VARIABLE_WITH_SYMBOL(Within_managed_object_scope, Qwithin_managed_object_scope);
