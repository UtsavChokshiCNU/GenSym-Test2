/* vwmsg1.h -- Header File for vwmsg1.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qinteger;
extern Object Qmax;
extern Object Qmin;
extern Object Qsequence;
extern Object Qsymbol;

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

extern Object bytes_per_simple_vector(Object);
extern Object clear_optimized_constants(void);
extern Object direct_structure_method(Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_permanent_ws_representation_type_structure_internal(void);
extern Object make_thread_array(Object);
extern Object make_ws_representation_type_1(void);
extern Object mutate_global_property(Object,Object,Object);
extern Object outstanding_ws_representation_type_count(void);
extern Object push_optimized_constant(Object);
extern Object reclaim_ws_representation_type_1(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object update_object_pool_meters_list(Object);
extern Object ws_representation_type_structure_memory_usage(void);

#else

extern Object bytes_per_simple_vector();
extern Object clear_optimized_constants();
extern Object direct_structure_method();
extern Object load_and_initialize_type_description();
extern Object make_permanent_ws_representation_type_structure_internal();
extern Object make_thread_array();
extern Object make_ws_representation_type_1();
extern Object mutate_global_property();
extern Object outstanding_ws_representation_type_count();
extern Object push_optimized_constant();
extern Object reclaim_ws_representation_type_1();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object update_object_pool_meters_list();
extern Object ws_representation_type_structure_memory_usage();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_ws_representation_types, Qchain_of_available_ws_representation_types);
extern Object Chain_of_available_ws_representation_types_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chart, Qchart);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
extern Object Object_definition_message_receiver_prop;
extern Object Object_definition_message_sender_prop;
extern Object The_type_description_of_ws_representation_type;
extern Object View_message_receiver_prop;
extern Object View_message_sender_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Ws_representation_type_count, Qws_representation_type_count);
extern Object Ws_representation_type_prop;
