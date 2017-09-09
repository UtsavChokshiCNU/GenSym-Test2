/* smrtsgnlxtnsn.h -- Header File for smrtsgnlxtnsn.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qfloat;
extern Object Qinteger;
extern Object Qnumber;

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

extern Object bytes_per_double_float_simple_array(Object);
extern Object c2_get_history_spec(Object,Object);
extern Object c2_get_total_length_of_ring_buffer_or_cascade(Object);
extern Object cascaded_ring_buffer_empty_qm(Object);
extern Object g2_enterprise_p(void);
extern Object generate_float_vector(Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object kb_g2nke_count_history_matching_op(Object,Object,Object,Object,Object,Object);
extern Object kb_g2nke_count_history_matching_op_and_eventflag(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object lisp_g2nke_count_history_matching_op(Object,Object,Object,Object,Object,Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object raw_stack_error_named_error(Object,Object);
extern Object tformat_stack_error_text_string(int,...);

#else

extern Object bytes_per_double_float_simple_array();
extern Object c2_get_history_spec();
extern Object c2_get_total_length_of_ring_buffer_or_cascade();
extern Object cascaded_ring_buffer_empty_qm();
extern Object g2_enterprise_p();
extern Object generate_float_vector();
extern Object get_lookup_slot_value();
extern Object kb_g2nke_count_history_matching_op();
extern Object kb_g2nke_count_history_matching_op_and_eventflag();
extern Object lisp_g2nke_count_history_matching_op();
extern Object lookup_global_or_kb_specific_property_value();
extern Object mutate_global_property();
extern Object raw_stack_error_named_error();
extern Object tformat_stack_error_text_string();

#endif

/* variables/constants */
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Cached_top_of_stack, Qcached_top_of_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
extern Object Numeric_data_type_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_class_description, Qvariable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
