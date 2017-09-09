/* glbscs.h -- Header File for glbscs.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Kelement_type;
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

extern Object g2int_assoc_equal(Object,Object);
extern Object g2int_assq_function(Object,Object);
extern Object g2int_clear_optimized_constants(void);
extern Object g2int_coerce_to_gensym_float_function(Object);
extern Object g2int_exit_lisp_process(int,...);
extern Object g2int_getfq_function(Object,Object,Object);
extern Object g2int_getfq_function_no_default(Object,Object);
extern Object g2int_memq_function(Object,Object);
extern Object g2int_pctpointer(Object);
extern Object g2int_print_random_object_prefix_for_gsi(Object,Object);
extern Object g2int_print_random_object_suffix_for_gsi(Object,Object);
extern Object g2int_push_optimized_constant(Object);
extern Object g2int_read_optimized_constant(void);
extern Object g2int_regenerate_optimized_constant(Object);
extern Object g2int_regenerate_standard_symbols(Object);
extern Object g2int_starf_safe(Object,Object);

#else

extern Object g2int_assoc_equal();
extern Object g2int_assq_function();
extern Object g2int_clear_optimized_constants();
extern Object g2int_coerce_to_gensym_float_function();
extern Object g2int_exit_lisp_process();
extern Object g2int_getfq_function();
extern Object g2int_getfq_function_no_default();
extern Object g2int_memq_function();
extern Object g2int_pctpointer();
extern Object g2int_print_random_object_prefix_for_gsi();
extern Object g2int_print_random_object_suffix_for_gsi();
extern Object g2int_push_optimized_constant();
extern Object g2int_read_optimized_constant();
extern Object g2int_regenerate_optimized_constant();
extern Object g2int_regenerate_standard_symbols();
extern Object g2int_starf_safe();

#endif

/* variables/constants */
extern Object G2int_available_reusable_gensyms;
extern Object G2int_debug_1;
extern Object G2int_debug_10;
extern Object G2int_debug_11;
extern Object G2int_debug_12;
extern Object G2int_debug_2;
extern Object G2int_debug_3;
extern Object G2int_debug_4;
extern Object G2int_debug_5;
extern Object G2int_debug_6;
extern Object G2int_debug_7;
extern Object G2int_debug_8;
extern Object G2int_debug_9;
extern Object G2int_destination_for_symbol_with_preserved_cells;
extern Object G2int_keyword_package_1;
extern Object G2int_lisp_package_1;
#define G2int_most_negative_fixnum32 FIX((SI_Long)-536870912L)
extern Object G2int_most_negative_fixnum_as_float;
extern Object G2int_most_negative_int64;
#define G2int_most_positive_fixnum32 FIX((SI_Long)536870911L)
extern Object G2int_most_positive_fixnum32_as_float;
extern Object G2int_most_positive_fixnum32_plus_one;
extern Object G2int_most_positive_fixnum32_plus_one_as_float;
extern Object G2int_most_positive_fixnum_as_float;
extern Object G2int_most_positive_int64;
extern Object G2int_negative_fifty_million;
extern Object G2int_optimized_constant_op_codes;
extern Object G2int_optimized_constant_pc;
extern Object G2int_optimized_constant_vector;
extern Object G2int_optimized_constant_vector_index;
#define G2int_optimized_constant_vector_length FIX((SI_Long)1300L)
extern Object G2int_rational_float_epsilon;
extern Object G2int_reusable_gensyms;
extern Object G2int_special_variable_for_use_value_macro;
extern Object G2int_standard_symbols_for_optimized_constantqm;
extern Object G2int_starlist_of_funcalled_functionsstar;
extern Object G2int_starlist_of_symbols_for_symbol_valuestar;
extern Object G2int_within_managed_object_scope;
