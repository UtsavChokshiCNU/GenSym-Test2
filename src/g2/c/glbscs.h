/* glbscs.h -- Header File for glbscs.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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
extern Object Available_reusable_gensyms;
extern Object Debug_1;
extern Object Debug_10;
extern Object Debug_11;
extern Object Debug_12;
extern Object Debug_2;
extern Object Debug_3;
extern Object Debug_4;
extern Object Debug_5;
extern Object Debug_6;
extern Object Debug_7;
extern Object Debug_8;
extern Object Debug_9;
extern Object Destination_for_symbol_with_preserved_cells;
extern Object Keyword_package_1;
extern Object Lisp_package_1;
extern Object List_of_funcalled_functions;
extern Object List_of_symbols_for_symbol_value;
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
extern Object Optimized_constant_op_codes;
extern Object Optimized_constant_pc;
extern Object Optimized_constant_vector;
extern Object Optimized_constant_vector_index;
#define Optimized_constant_vector_length FIX((SI_Long)1300L)
extern Object Rational_float_epsilon;
extern Object Reusable_gensyms;
extern Object Special_variable_for_use_value_macro;
extern Object Standard_symbols_for_optimized_constant_qm;
extern Object Within_managed_object_scope;
