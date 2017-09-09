/* bridge.h -- Header File for bridge.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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

extern Object g2int_apply_rpc_imported_g2(Object,Object);
extern Object g2int_assq_function(Object,Object);
extern Object g2int_contour_wrapper_for_rpc_threads(void);
extern Object g2int_direct_structure_method(Object,Object);
extern Object g2int_eval_feature(Object);
extern Object g2int_generate_thread_number(void);
extern Object g2int_gensym_cons_1(Object,Object);
extern Object g2int_get_value_of_any_simple_type(Object);
extern Object g2int_getfq_function_no_default(Object,Object);
extern Object g2int_gsi_current_context_number(void);
extern Object g2int_gsi_error(int,...);
extern Object g2int_install_gsi_rpc_info(Object,Object,Object);
extern Object g2int_lgsi_attr_by_name(Object,Object);
extern Object g2int_lgsi_get_attribute_value(Object,Object);
extern Object g2int_lgsi_int_of(Object);
extern Object g2int_lgsi_reclaim_items(Object);
extern Object g2int_lgsi_rpc_declare_remote(Object,Object,Object);
extern Object g2int_lgsi_set_int(Object,Object);
extern Object g2int_lgsi_set_str(Object,Object);
extern Object g2int_lgsi_set_sym(Object,Object);
extern Object g2int_lgsi_str_of(Object);
extern Object g2int_lgsi_sym_of(Object);
extern Object g2int_load_and_initialize_type_description(Object,Object);
extern Object g2int_lookup_gsi_rpc_info(Object,Object);
extern Object g2int_make_permanent_rpc_thread_structure_internal(void);
extern Object g2int_make_rpc_thread_1(void);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_notify_user_at_console(int,...);
extern Object g2int_null_thread_contour_wrapper(void);
extern Object g2int_reclaim_event_tree(Object);
extern Object g2int_reclaim_rpc_thread_1(Object);
extern Object g2int_reclaim_sockets(Object);
extern Object g2int_record_direct_structure_method(Object,Object,Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_regenerate_optimized_constant(Object);
extern Object g2int_set_simple_value_in_item(Object,Object);
extern Object g2int_signal_from_rpc(Object,Object);
extern Object g2int_thread_kill(Object);

#else

extern Object g2int_apply_rpc_imported_g2();
extern Object g2int_assq_function();
extern Object g2int_contour_wrapper_for_rpc_threads();
extern Object g2int_direct_structure_method();
extern Object g2int_eval_feature();
extern Object g2int_generate_thread_number();
extern Object g2int_gensym_cons_1();
extern Object g2int_get_value_of_any_simple_type();
extern Object g2int_getfq_function_no_default();
extern Object g2int_gsi_current_context_number();
extern Object g2int_gsi_error();
extern Object g2int_install_gsi_rpc_info();
extern Object g2int_lgsi_attr_by_name();
extern Object g2int_lgsi_get_attribute_value();
extern Object g2int_lgsi_int_of();
extern Object g2int_lgsi_reclaim_items();
extern Object g2int_lgsi_rpc_declare_remote();
extern Object g2int_lgsi_set_int();
extern Object g2int_lgsi_set_str();
extern Object g2int_lgsi_set_sym();
extern Object g2int_lgsi_str_of();
extern Object g2int_lgsi_sym_of();
extern Object g2int_load_and_initialize_type_description();
extern Object g2int_lookup_gsi_rpc_info();
extern Object g2int_make_permanent_rpc_thread_structure_internal();
extern Object g2int_make_rpc_thread_1();
extern Object g2int_mutate_global_property();
extern Object g2int_notify_user_at_console();
extern Object g2int_null_thread_contour_wrapper();
extern Object g2int_reclaim_event_tree();
extern Object g2int_reclaim_rpc_thread_1();
extern Object g2int_reclaim_sockets();
extern Object g2int_record_direct_structure_method();
extern Object g2int_record_system_variable();
extern Object g2int_regenerate_optimized_constant();
extern Object g2int_set_simple_value_in_item();
extern Object g2int_signal_from_rpc();
extern Object g2int_thread_kill();

#endif

/* Externally callable routines */

#ifdef USE_PROTOTYPES

extern Object g2int_shared_gsi_attr_by_name(Object,Object,Object);
extern void g2int_shared_gsi_clear_item(Object);
extern SI_Long g2int_shared_gsi_int_of(Object);
extern SI_Long g2int_shared_gsi_log_of(Object);
extern void g2int_shared_gsi_reclaim_items(Object);
extern void g2int_shared_gsi_rpc_declare_remote_plain(Object,Object,Object,Object,SI_Long,SI_Long,SI_Long);
extern void g2int_shared_gsi_rpc_start(Object,Object,SI_Long);
extern void g2int_shared_gsi_set_int(Object,SI_Long);
extern void g2int_shared_gsi_set_log(Object,SI_Long);
extern void g2int_shared_gsi_set_str(Object,Object,Object);
extern void g2int_shared_gsi_set_sym(Object,Object,Object);
extern Object g2int_shared_gsi_str_of(Object,Object);
extern Object g2int_shared_gsi_sym_of(Object,Object);
extern SI_Long g2int_shared_gsi_type_of(Object);
DLLEXPORT extern Object gsi_make_items(SI_Long);

#else

extern Object g2int_shared_gsi_attr_by_name();
extern void g2int_shared_gsi_clear_item();
extern SI_Long g2int_shared_gsi_int_of();
extern SI_Long g2int_shared_gsi_log_of();
extern void g2int_shared_gsi_reclaim_items();
extern void g2int_shared_gsi_rpc_declare_remote_plain();
extern void g2int_shared_gsi_rpc_start();
extern void g2int_shared_gsi_set_int();
extern void g2int_shared_gsi_set_log();
extern void g2int_shared_gsi_set_str();
extern void g2int_shared_gsi_set_sym();
extern Object g2int_shared_gsi_str_of();
extern Object g2int_shared_gsi_sym_of();
extern SI_Long g2int_shared_gsi_type_of();
DLLEXPORT extern Object gsi_make_items();

#endif

/* variables/constants */
extern Object G2int_ab_package_1;
extern Object G2int_alist_for_rpc_into_g2_prop;
extern Object G2int_chain_of_available_rpc_threads;
extern Object G2int_current_icp_socket;
extern Object G2int_current_rpc_call_handle;
extern Object G2int_current_thread;
#define G2int_gsi_bad_magic_number FIX((SI_Long)23L)
#define G2int_gsi_magic_offset FIX((SI_Long)1L)
extern Object G2int_ignored_return_values_for_signals_prop;
extern Object G2int_return_function_of_rpc_prop;
extern Object G2int_rpc_thread_count;
extern Object G2int_structure_being_reclaimed;
extern Object G2int_temp_array_for_declare_remote;
extern Object G2int_temp_for_declare_remote;
extern Object G2int_the_type_description_of_rpc_thread;
