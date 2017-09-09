/* int0.h -- Header File for int0.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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
extern Object Bignum_overflow_count;
extern Object Cache_al_semantics_graph;
extern Object Cache_chinese_semantics_graph;
extern Object Cache_embedded_option_semantics_graph;
extern Object Cache_ent_semantics_graph;
extern Object Cache_g1_semantics_graph;
extern Object Cache_gfi_semantics_graph;
extern Object Cache_gsi_semantics_graph;
extern Object Cache_gspan_semantics_graph;
extern Object Cache_icp_semantics_graph;
extern Object Cache_japanese_semantics_graph;
extern Object Cache_jl_semantics_graph;
extern Object Cache_jp_semantics_graph;
extern Object Cache_kfep_semantics_graph;
extern Object Cache_korean_semantics_graph;
extern Object Cache_nupec_semantics_graph;
extern Object Cache_restricted_use_option_semantics_graph;
extern Object Cache_runtime_option_semantics_graph;
extern Object Control_sequence_record;
extern Object Destination_for_symbol_with_preserved_cells;
extern Object Edit_type_alias_mapping;
extern Object End_of_recovery_list;
extern Object Format_redefinition_list;
extern Object Format_structure_description;
extern Object G2_has_been_started_qm;
extern Object Get_object_on_kb_workspace_for_item;
extern Object Gfi_list_of_converters;
extern Object Index_of_open_windows;
extern Object Journal_shutout_scan_p;
extern Object Learned_list_to_expedite_ui;
extern Object Left_recursion_limit_list;
extern Object Listed_continuation_servers;
extern Object Local_recovery_list;
extern Object Old_eval_cons_list;
extern Object Optional_modules_map;
extern Object Overflow_byte_count;
extern Object Pop_fonts_stack;
extern Object Popup_frames_available;
extern Object Proce_eval_invoked_list;
extern Object Radio_button_status_flags;
extern Object Radio_button_status_flags_1;
extern Object Reclaim_fonts_stack;
extern Object Redo_saved_changes;
extern Object Right_recursion_limit_list;
extern Object Ring_buffer_queue_for_kfep;
extern Object Sparse_known_pathnames_list;
extern Object Unevaluated_expression;
extern Object Within_side_limits;
