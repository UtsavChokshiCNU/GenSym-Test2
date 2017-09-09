/* slots.h -- Header File for slots.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */

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

extern Object allocate_evaluation_sequence(Object);
extern Object allocate_evaluation_structure(Object);
extern Object allocate_managed_array(int,...);
extern Object allocate_managed_long_box(void);
extern Object bytes_per_double_float_simple_array(Object);
extern Object copy_byte_code_body(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_managed_float(Object);
extern Object copy_managed_float_array(Object);
extern Object copy_managed_long(Object);
extern Object copy_text_string(Object);
extern Object eval_cons_1(Object,Object);
extern Object find_frame_for_denotation(int,...);
extern Object generate_float_vector(Object);
extern Object get_property_value_function(int,...);
extern Object get_symbol_properties_function(Object);
extern Object make_slot_value_list_1(Object);
extern Object slot_value_cons_1(Object,Object);
extern Object text_string_p(Object);

#else

extern Object allocate_evaluation_sequence();
extern Object allocate_evaluation_structure();
extern Object allocate_managed_array();
extern Object allocate_managed_long_box();
extern Object bytes_per_double_float_simple_array();
extern Object copy_byte_code_body();
extern Object copy_for_slot_value();
extern Object copy_managed_float();
extern Object copy_managed_float_array();
extern Object copy_managed_long();
extern Object copy_text_string();
extern Object eval_cons_1();
extern Object find_frame_for_denotation();
extern Object generate_float_vector();
extern Object get_property_value_function();
extern Object get_symbol_properties_function();
extern Object make_slot_value_list_1();
extern Object slot_value_cons_1();
extern Object text_string_p();

#endif

/* variables/constants */
extern Object Available_float_array_conses_tail_vector;
extern Object Available_float_array_conses_vector;
extern Object Constant_queue_marker;
DECLARE_VARIABLE_WITH_SYMBOL(Created_simple_float_array_pool_arrays, Qcreated_simple_float_array_pool_arrays);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Defined_evaluation_value_types, Qdefined_evaluation_value_types);
DECLARE_VARIABLE_WITH_SYMBOL(Dependent_frame_class_description, Qdependent_frame_class_description);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Managed_array_unique_marker;
extern Object Managed_float_array_unique_marker;
extern Object Maximum_in_place_array_size;
DECLARE_VARIABLE_WITH_SYMBOL(No_value, Qno_value);
extern Object Phrase_item_denotation_marker;
extern Object Phrase_item_marker;
extern Object Phrase_sequence_marker;
extern Object Phrase_structure_marker;
DECLARE_VARIABLE_WITH_SYMBOL(Simple_float_array_pool_memory_usage, Qsimple_float_array_pool_memory_usage);
DECLARE_VARIABLE_WITH_SYMBOL(Vector_of_simple_float_array_pools, Qvector_of_simple_float_array_pools);
