/* int0.h -- Header File for int0.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qequal;
extern Object Ktest;

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

extern Object assq_function(Object,Object);
extern Object initialize_optional_modules(void);
extern Object invisible_optional_module_p(Object);
extern Object parse_al_schedule_tree(void);
extern Object parse_chinese_schedule_tree(void);
extern Object parse_embedded_option_schedule_tree(void);
extern Object parse_ent_schedule_tree(void);
extern Object parse_g1_schedule_tree(void);
extern Object parse_gfi_schedule_tree(void);
extern Object parse_gsi_schedule_tree(void);
extern Object parse_gspan_schedule_tree(void);
extern Object parse_icp_schedule_tree(void);
extern Object parse_japanese_schedule_tree(void);
extern Object parse_jl_schedule_tree(void);
extern Object parse_jp_schedule_tree(void);
extern Object parse_kfep_schedule_tree(void);
extern Object parse_korean_schedule_tree(void);
extern Object parse_nupec_schedule_tree(void);
extern Object parse_restricted_use_option_schedule_tree(void);
extern Object parse_runtime_option_schedule_tree(void);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object run_al_for_recursive_descent(Object,Object);
extern Object run_chinese_for_recursive_descent(Object,Object);
extern Object run_embedded_option_for_recursive_descent(Object,Object);
extern Object run_ent_for_recursive_descent(Object,Object);
extern Object run_g1_for_recursive_descent(Object,Object);
extern Object run_g2_initializations(void);
extern Object run_gfi_for_recursive_descent(Object,Object);
extern Object run_gsi_for_recursive_descent(Object,Object);
extern Object run_gspan_for_recursive_descent(Object,Object);
extern Object run_icp_for_recursive_descent(Object,Object);
extern Object run_japanese_for_recursive_descent(Object,Object);
extern Object run_jl_for_recursive_descent(Object,Object);
extern Object run_jp_for_recursive_descent(Object,Object);
extern Object run_kfep_for_recursive_descent(Object,Object);
extern Object run_korean_for_recursive_descent(Object,Object);
extern Object run_nupec_for_recursive_descent(Object,Object);
extern Object run_restricted_use_option_for_recursive_descent(Object,Object);
extern Object run_runtime_option_for_recursive_descent(Object,Object);

#else

extern Object assq_function();
extern Object initialize_optional_modules();
extern Object invisible_optional_module_p();
extern Object parse_al_schedule_tree();
extern Object parse_chinese_schedule_tree();
extern Object parse_embedded_option_schedule_tree();
extern Object parse_ent_schedule_tree();
extern Object parse_g1_schedule_tree();
extern Object parse_gfi_schedule_tree();
extern Object parse_gsi_schedule_tree();
extern Object parse_gspan_schedule_tree();
extern Object parse_icp_schedule_tree();
extern Object parse_japanese_schedule_tree();
extern Object parse_jl_schedule_tree();
extern Object parse_jp_schedule_tree();
extern Object parse_kfep_schedule_tree();
extern Object parse_korean_schedule_tree();
extern Object parse_nupec_schedule_tree();
extern Object parse_restricted_use_option_schedule_tree();
extern Object parse_runtime_option_schedule_tree();
extern Object record_system_variable();
extern Object run_al_for_recursive_descent();
extern Object run_chinese_for_recursive_descent();
extern Object run_embedded_option_for_recursive_descent();
extern Object run_ent_for_recursive_descent();
extern Object run_g1_for_recursive_descent();
extern Object run_g2_initializations();
extern Object run_gfi_for_recursive_descent();
extern Object run_gsi_for_recursive_descent();
extern Object run_gspan_for_recursive_descent();
extern Object run_icp_for_recursive_descent();
extern Object run_japanese_for_recursive_descent();
extern Object run_jl_for_recursive_descent();
extern Object run_jp_for_recursive_descent();
extern Object run_kfep_for_recursive_descent();
extern Object run_korean_for_recursive_descent();
extern Object run_nupec_for_recursive_descent();
extern Object run_restricted_use_option_for_recursive_descent();
extern Object run_runtime_option_for_recursive_descent();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Bignum_overflow_count, Qbignum_overflow_count);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_al_semantics_graph, Qcache_al_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_chinese_semantics_graph, Qcache_chinese_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_embedded_option_semantics_graph, Qcache_embedded_option_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_ent_semantics_graph, Qcache_ent_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_g1_semantics_graph, Qcache_g1_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_gfi_semantics_graph, Qcache_gfi_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_gsi_semantics_graph, Qcache_gsi_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_gspan_semantics_graph, Qcache_gspan_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_icp_semantics_graph, Qcache_icp_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_japanese_semantics_graph, Qcache_japanese_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_jl_semantics_graph, Qcache_jl_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_jp_semantics_graph, Qcache_jp_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_kfep_semantics_graph, Qcache_kfep_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_korean_semantics_graph, Qcache_korean_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_nupec_semantics_graph, Qcache_nupec_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_restricted_use_option_semantics_graph, Qcache_restricted_use_option_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Cache_runtime_option_semantics_graph, Qcache_runtime_option_semantics_graph);
DECLARE_VARIABLE_WITH_SYMBOL(Control_sequence_record, Qcontrol_sequence_record);
DECLARE_VARIABLE_WITH_SYMBOL(Destination_for_symbol_with_preserved_cells, Qdestination_for_symbol_with_preserved_cells);
DECLARE_VARIABLE_WITH_SYMBOL(Edit_type_alias_mapping, Qedit_type_alias_mapping);
extern Object End_of_recovery_list;
extern Object Format_redefinition_list;
extern Object Format_structure_description;
DECLARE_VARIABLE_WITH_SYMBOL(G2_has_been_started_qm, Qg2_has_been_started_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Get_object_on_kb_workspace_for_item, Qget_object_on_kb_workspace_for_item);
DECLARE_VARIABLE_WITH_SYMBOL(Gfi_list_of_converters, Qgfi_list_of_converters);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_open_windows, Qindex_of_open_windows);
DECLARE_VARIABLE_WITH_SYMBOL(Journal_shutout_scan_p, Qjournal_shutout_scan_p);
DECLARE_VARIABLE_WITH_SYMBOL(Learned_list_to_expedite_ui, Qlearned_list_to_expedite_ui);
extern Object Left_recursion_limit_list;
DECLARE_VARIABLE_WITH_SYMBOL(Listed_continuation_servers, Qlisted_continuation_servers);
extern Object Local_recovery_list;
extern Object Old_eval_cons_list;
DECLARE_VARIABLE_WITH_SYMBOL(Optional_modules_map, Qoptional_modules_map);
DECLARE_VARIABLE_WITH_SYMBOL(Overflow_byte_count, Qoverflow_byte_count);
DECLARE_VARIABLE_WITH_SYMBOL(Pop_fonts_stack, Qpop_fonts_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Popup_frames_available, Qpopup_frames_available);
extern Object Proce_eval_invoked_list;
DECLARE_VARIABLE_WITH_SYMBOL(Radio_button_status_flags, Qradio_button_status_flags);
DECLARE_VARIABLE_WITH_SYMBOL(Radio_button_status_flags_1, Qradio_button_status_flags_1);
DECLARE_VARIABLE_WITH_SYMBOL(Reclaim_fonts_stack, Qreclaim_fonts_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Redo_saved_changes, Qredo_saved_changes);
DECLARE_VARIABLE_WITH_SYMBOL(Right_recursion_limit_list, Qright_recursion_limit_list);
DECLARE_VARIABLE_WITH_SYMBOL(Ring_buffer_queue_for_kfep, Qring_buffer_queue_for_kfep);
DECLARE_VARIABLE_WITH_SYMBOL(Sparse_known_pathnames_list, Qsparse_known_pathnames_list);
DECLARE_VARIABLE_WITH_SYMBOL(Unevaluated_expression, Qunevaluated_expression);
extern Object Within_side_limits;
