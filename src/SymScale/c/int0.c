/* int0.c
 * Input file:  int0.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int0.h"


Object Format_structure_description = UNBOUND;

Object Format_redefinition_list = UNBOUND;

Object End_of_recovery_list = UNBOUND;

Object Local_recovery_list = UNBOUND;

Object Within_side_limits = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Unevaluated_expression, Qunevaluated_expression);

DEFINE_VARIABLE_WITH_SYMBOL(Control_sequence_record, Qcontrol_sequence_record);

DEFINE_VARIABLE_WITH_SYMBOL(G2_has_been_started_qm, Qg2_has_been_started_qm);

/* RUN-G2-INITIALIZATIONS */
Object run_g2_initializations()
{
    x_note_fn_call(46,0);
    Unevaluated_expression = Within_side_limits;
    return VALUES_1(Unevaluated_expression);
}

Object Old_eval_cons_list = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Optional_modules_map, Qoptional_modules_map);

Object Proce_eval_invoked_list = UNBOUND;

Object Left_recursion_limit_list = UNBOUND;

/* INVISIBLE-OPTIONAL-MODULE-P */
Object invisible_optional_module_p(product_module_name)
    Object product_module_name;
{
    Object temp;

    x_note_fn_call(46,1);
    temp = assq_function(product_module_name,Optional_modules_map);
    return VALUES_1(FOURTH(temp));
}

DEFINE_VARIABLE_WITH_SYMBOL(Overflow_byte_count, Qoverflow_byte_count);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_gsi_semantics_graph, Qcache_gsi_semantics_graph);

/* PARSE-GSI-SCHEDULE-TREE */
Object parse_gsi_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,2);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_gsi_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Bignum_overflow_count, Qbignum_overflow_count);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_gspan_semantics_graph, Qcache_gspan_semantics_graph);

/* PARSE-GSPAN-SCHEDULE-TREE */
Object parse_gspan_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,3);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_gspan_for_recursive_descent(temp,
	    l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Listed_continuation_servers, Qlisted_continuation_servers);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_icp_semantics_graph, Qcache_icp_semantics_graph);

/* PARSE-ICP-SCHEDULE-TREE */
Object parse_icp_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,4);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_icp_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Gfi_list_of_converters, Qgfi_list_of_converters);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_gfi_semantics_graph, Qcache_gfi_semantics_graph);

/* PARSE-GFI-SCHEDULE-TREE */
Object parse_gfi_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,5);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_gfi_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Ring_buffer_queue_for_kfep, Qring_buffer_queue_for_kfep);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_kfep_semantics_graph, Qcache_kfep_semantics_graph);

/* PARSE-KFEP-SCHEDULE-TREE */
Object parse_kfep_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,6);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_kfep_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Reclaim_fonts_stack, Qreclaim_fonts_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_chinese_semantics_graph, Qcache_chinese_semantics_graph);

/* PARSE-CHINESE-SCHEDULE-TREE */
Object parse_chinese_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,7);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_chinese_for_recursive_descent(temp,
	    l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Redo_saved_changes, Qredo_saved_changes);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_runtime_option_semantics_graph, Qcache_runtime_option_semantics_graph);

/* PARSE-RUNTIME-OPTION-SCHEDULE-TREE */
Object parse_runtime_option_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,8);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_runtime_option_for_recursive_descent(temp,
	    l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Pop_fonts_stack, Qpop_fonts_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_japanese_semantics_graph, Qcache_japanese_semantics_graph);

/* PARSE-JAPANESE-SCHEDULE-TREE */
Object parse_japanese_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,9);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_japanese_for_recursive_descent(temp,
	    l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Journal_shutout_scan_p, Qjournal_shutout_scan_p);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_nupec_semantics_graph, Qcache_nupec_semantics_graph);

/* PARSE-NUPEC-SCHEDULE-TREE */
Object parse_nupec_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,10);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_nupec_for_recursive_descent(temp,
	    l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Sparse_known_pathnames_list, Qsparse_known_pathnames_list);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_restricted_use_option_semantics_graph, Qcache_restricted_use_option_semantics_graph);

/* PARSE-RESTRICTED-USE-OPTION-SCHEDULE-TREE */
Object parse_restricted_use_option_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,11);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_restricted_use_option_for_recursive_descent(temp,
	    l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Learned_list_to_expedite_ui, Qlearned_list_to_expedite_ui);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_embedded_option_semantics_graph, Qcache_embedded_option_semantics_graph);

/* PARSE-EMBEDDED-OPTION-SCHEDULE-TREE */
Object parse_embedded_option_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,12);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_embedded_option_for_recursive_descent(temp,
	    l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Get_object_on_kb_workspace_for_item, Qget_object_on_kb_workspace_for_item);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_korean_semantics_graph, Qcache_korean_semantics_graph);

/* PARSE-KOREAN-SCHEDULE-TREE */
Object parse_korean_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,13);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_korean_for_recursive_descent(temp,
	    l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Edit_type_alias_mapping, Qedit_type_alias_mapping);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_g1_semantics_graph, Qcache_g1_semantics_graph);

/* PARSE-G1-SCHEDULE-TREE */
Object parse_g1_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,14);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_g1_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Index_of_open_windows, Qindex_of_open_windows);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_jl_semantics_graph, Qcache_jl_semantics_graph);

/* PARSE-JL-SCHEDULE-TREE */
Object parse_jl_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,15);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_jl_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Popup_frames_available, Qpopup_frames_available);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_jp_semantics_graph, Qcache_jp_semantics_graph);

/* PARSE-JP-SCHEDULE-TREE */
Object parse_jp_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,16);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_jp_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Radio_button_status_flags, Qradio_button_status_flags);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_al_semantics_graph, Qcache_al_semantics_graph);

/* PARSE-AL-SCHEDULE-TREE */
Object parse_al_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,17);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_al_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

DEFINE_VARIABLE_WITH_SYMBOL(Radio_button_status_flags_1, Qradio_button_status_flags_1);

DEFINE_VARIABLE_WITH_SYMBOL(Cache_ent_semantics_graph, Qcache_ent_semantics_graph);

/* PARSE-ENT-SCHEDULE-TREE */
Object parse_ent_schedule_tree()
{
    Object temp;

    x_note_fn_call(46,18);
    temp = l_random(FIX((SI_Long)99L),_);
    return run_ent_for_recursive_descent(temp,l_random(FIX((SI_Long)999L),_));
}

static Object Qsimulation_state;   /* simulation-state */

/* INITIALIZE-OPTIONAL-MODULES */
Object initialize_optional_modules()
{
    Object product, ignore, ab_loop_list_, simulated_state_qm, ab_loop_desetq_;

    x_note_fn_call(46,19);
    product = Nil;
    ignore = Nil;
    ab_loop_list_ = Optional_modules_map;
    simulated_state_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    product = CAR(ab_loop_desetq_);
    ignore = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    simulated_state_qm = get(product,Qsimulation_state,_);
    if (simulated_state_qm)
	M_SECOND(simulated_state_qm) = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Right_recursion_limit_list, Qright_recursion_limit_list);

void int0_INIT()
{
    Object temp, temp_1, temp_2, xxx;
    Object list_constant_26, list_constant_22, Qembedded, AB_package;
    Object list_constant_25, Qrestricted_use, list_constant_24, Qruntime;
    Object list_constant_23, Qonline, list_constant_20, list_constant_21;
    Object Qoffline, Qent, list_constant_19, list_constant_3, Qal;
    Object list_constant_18, Qjp, list_constant_17, Qjl, list_constant_16, Qg1;
    Object list_constant_15, Qkorean, list_constant_14, Qembedded_option;
    Object list_constant_13, list_constant_6, Qrestricted_use_option;
    Object list_constant_12, Qnupec, list_constant_11, Qjapanese;
    Object list_constant_10, Qruntime_option, list_constant_9, Qchinese;
    Object list_constant_8, Qkfep, list_constant_7, Qgfi, list_constant_5;
    Object Qicp, list_constant_4, Qgspan, list_constant_2, Qgsi;
    Object list_constant_1, Qsequences2, Qformat_structure_description;
    Object list_constant, Qdescription, Qab_structure;

    x_note_fn_call(46,20);
    SET_PACKAGE("AB");
    Format_structure_description = list(16,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,
	    Nil,Nil,LIST_1(FIX((SI_Long)0L)),Nil,LIST_1(Nil),
	    FIX((SI_Long)0L),Nil,Nil);
    AB_package = STATIC_PACKAGE("AB");
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qdescription = STATIC_SYMBOL("DESCRIPTION",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qab_structure,Qdescription);
    Format_redefinition_list = list_constant;
    Qformat_structure_description = 
	    STATIC_SYMBOL("FORMAT-STRUCTURE-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qformat_structure_description,
	    Format_structure_description);
    Destination_for_symbol_with_preserved_cells = 
	    Qformat_structure_description;
    temp = nthcdr(FIX((SI_Long)10L),Format_structure_description);
    temp = CONS(Nil,temp);
    End_of_recovery_list = CONS(Nil,temp);
    temp = nthcdr(FIX((SI_Long)12L),Format_structure_description);
    temp = CONS(Nil,temp);
    Local_recovery_list = CONS(Nil,temp);
    Within_side_limits = LIST_1(FIX((SI_Long)34L));
    if (Unevaluated_expression == UNBOUND)
	Unevaluated_expression = Within_side_limits;
    Qcontrol_sequence_record = STATIC_SYMBOL("CONTROL-SEQUENCE-RECORD",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcontrol_sequence_record,
	    Control_sequence_record);
    Qsequences2 = STATIC_SYMBOL("SEQUENCES2",AB_package);
    record_system_variable(Qcontrol_sequence_record,Qsequences2,Nil,Qnil,
	    Qt,Qnil,Qnil);
    if (G2_has_been_started_qm == UNBOUND)
	G2_has_been_started_qm = Nil;
    Old_eval_cons_list = LIST_2(Nil,Nil);
    if (Optional_modules_map == UNBOUND)
	Optional_modules_map = Nil;
    Proce_eval_invoked_list = Nil;
    temp = CDR(Old_eval_cons_list);
    Left_recursion_limit_list = CONS(Nil,temp);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qgsi,FIX((SI_Long)1L),Qt,Qnil);
    temp_1 = adjoin(4,list_constant_1,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Overflow_byte_count = CONS(temp_2,temp);
    Qsimulation_state = STATIC_SYMBOL("SIMULATION-STATE",AB_package);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qgsi,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_gsi_semantics_graph = CONS(temp,xxx);
    Qgspan = STATIC_SYMBOL("GSPAN",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)4L,Qgspan,FIX((SI_Long)2L),Qt,Qt);
    temp_1 = adjoin(4,list_constant_2,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Bignum_overflow_count = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qgspan,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_gspan_semantics_graph = CONS(temp,xxx);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qt,Qnil);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)3L,Qicp,FIX((SI_Long)4L),
	    list_constant_3);
    temp_1 = adjoin(4,list_constant_4,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Listed_continuation_servers = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qicp,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_icp_semantics_graph = CONS(temp,xxx);
    Qgfi = STATIC_SYMBOL("GFI",AB_package);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)3L,Qgfi,FIX((SI_Long)8L),
	    list_constant_3);
    temp_1 = adjoin(4,list_constant_5,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Gfi_list_of_converters = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qgfi,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_gfi_semantics_graph = CONS(temp,xxx);
    Qkfep = STATIC_SYMBOL("KFEP",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qt,Qt);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)3L,Qkfep,FIX((SI_Long)16L),
	    list_constant_6);
    temp_1 = adjoin(4,list_constant_7,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Ring_buffer_queue_for_kfep = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qkfep,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_kfep_semantics_graph = CONS(temp,xxx);
    Qchinese = STATIC_SYMBOL("CHINESE",AB_package);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)3L,Qchinese,
	    FIX((SI_Long)32L),list_constant_3);
    temp_1 = adjoin(4,list_constant_8,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Reclaim_fonts_stack = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qchinese,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_chinese_semantics_graph = CONS(temp,xxx);
    Qruntime_option = STATIC_SYMBOL("RUNTIME-OPTION",AB_package);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qruntime_option,
	    FIX((SI_Long)64L),list_constant_6);
    temp_1 = adjoin(4,list_constant_9,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Redo_saved_changes = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qruntime_option,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_runtime_option_semantics_graph = CONS(temp,xxx);
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)3L,Qjapanese,
	    FIX((SI_Long)128L),list_constant_3);
    temp_1 = adjoin(4,list_constant_10,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Pop_fonts_stack = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qjapanese,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_japanese_semantics_graph = CONS(temp,xxx);
    Qnupec = STATIC_SYMBOL("NUPEC",AB_package);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,Qnupec,
	    FIX((SI_Long)256L),list_constant_3);
    temp_1 = adjoin(4,list_constant_11,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Journal_shutout_scan_p = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qnupec,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_nupec_semantics_graph = CONS(temp,xxx);
    Qrestricted_use_option = STATIC_SYMBOL("RESTRICTED-USE-OPTION",AB_package);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)3L,Qrestricted_use_option,
	    FIX((SI_Long)512L),list_constant_6);
    temp_1 = adjoin(4,list_constant_12,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Sparse_known_pathnames_list = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qrestricted_use_option,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_restricted_use_option_semantics_graph = CONS(temp,xxx);
    Qembedded_option = STATIC_SYMBOL("EMBEDDED-OPTION",AB_package);
    list_constant_13 = STATIC_LIST_STAR((SI_Long)3L,Qembedded_option,
	    FIX((SI_Long)1024L),list_constant_6);
    temp_1 = adjoin(4,list_constant_13,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Learned_list_to_expedite_ui = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qembedded_option,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_embedded_option_semantics_graph = CONS(temp,xxx);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)3L,Qkorean,
	    FIX((SI_Long)2048L),list_constant_3);
    temp_1 = adjoin(4,list_constant_14,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Get_object_on_kb_workspace_for_item = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qkorean,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_korean_semantics_graph = CONS(temp,xxx);
    Qg1 = STATIC_SYMBOL("G1",AB_package);
    list_constant_15 = STATIC_LIST_STAR((SI_Long)3L,Qg1,
	    FIX((SI_Long)4096L),list_constant_3);
    temp_1 = adjoin(4,list_constant_15,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Edit_type_alias_mapping = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qg1,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_g1_semantics_graph = CONS(temp,xxx);
    Qjl = STATIC_SYMBOL("JL",AB_package);
    list_constant_16 = STATIC_LIST_STAR((SI_Long)3L,Qjl,
	    FIX((SI_Long)8192L),list_constant_3);
    temp_1 = adjoin(4,list_constant_16,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Index_of_open_windows = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qjl,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_jl_semantics_graph = CONS(temp,xxx);
    Qjp = STATIC_SYMBOL("JP",AB_package);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,Qjp,
	    FIX((SI_Long)16384L),list_constant_3);
    temp_1 = adjoin(4,list_constant_17,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Popup_frames_available = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qjp,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_jp_semantics_graph = CONS(temp,xxx);
    Qal = STATIC_SYMBOL("AL",AB_package);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)3L,Qal,
	    FIX((SI_Long)32768L),list_constant_3);
    temp_1 = adjoin(4,list_constant_18,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Radio_button_status_flags = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qal,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_al_semantics_graph = CONS(temp,xxx);
    Qent = STATIC_SYMBOL("ENT",AB_package);
    list_constant_19 = STATIC_LIST_STAR((SI_Long)3L,Qent,
	    FIX((SI_Long)65536L),list_constant_3);
    temp_1 = adjoin(4,list_constant_19,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    temp_2 = l_random(FIX((SI_Long)20L),_);
    temp = nth(FIX((SI_Long)10L),Format_structure_description);
    Radio_button_status_flags_1 = CONS(temp_2,temp);
    temp = l_random(FIX((SI_Long)999L),_);
    xxx = CONS(temp,Nil);
    temp = l_random(FIX((SI_Long)99L),_);
    temp_1 = CONS(temp,xxx);
    set_get(Qent,Qsimulation_state,temp_1);
    temp = l_random(FIX((SI_Long)99L),_);
    Cache_ent_semantics_graph = CONS(temp,xxx);
    Qoffline = STATIC_SYMBOL("OFFLINE",AB_package);
    list_constant_20 = STATIC_CONS(Qnil,Qnil);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)4L,Qoffline,
	    FIX((SI_Long)0L),Qnil,list_constant_20);
    temp_1 = adjoin(4,list_constant_21,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    Qonline = STATIC_SYMBOL("ONLINE",AB_package);
    list_constant_22 = STATIC_CONS(Qnil,list_constant_20);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,Qonline,
	    FIX((SI_Long)13L),list_constant_22);
    temp_1 = adjoin(4,list_constant_23,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    Qruntime = STATIC_SYMBOL("RUNTIME",AB_package);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,Qruntime,
	    FIX((SI_Long)77L),list_constant_22);
    temp_1 = adjoin(4,list_constant_24,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    Qrestricted_use = STATIC_SYMBOL("RESTRICTED-USE",AB_package);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)3L,Qrestricted_use,
	    FIX((SI_Long)525L),list_constant_22);
    temp_1 = adjoin(4,list_constant_25,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    Qembedded = STATIC_SYMBOL("EMBEDDED",AB_package);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,Qembedded,
	    FIX((SI_Long)1037L),list_constant_22);
    temp_1 = adjoin(4,list_constant_26,Optional_modules_map,Ktest,Qequal);
    Optional_modules_map = temp_1;
    if (Right_recursion_limit_list == UNBOUND)
	Right_recursion_limit_list = CONS(Nil,Left_recursion_limit_list);
}
