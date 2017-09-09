/* cnct5.h -- Header File for cnct5.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Qeq;
extern Object Qeval;

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

extern Object add_bend_to_connection_1(Object,Object);
extern Object add_stub(int,...);
extern Object add_subworkspace_connection_post_if_appropriate(Object,Object);
extern Object collect_subclasses(Object);
extern Object connect_loose_end_to_block(int,...);
extern Object connection_arrows_of_connection(Object);
extern Object connection_is_straight_qm(Object);
extern Object connection_line_pattern(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_frame_serial_number(Object);
extern Object decache_roles_for_entities_related_to_this_connection(Object);
extern Object delete_connection(int,...);
extern Object delete_connection_leaving_stubs_if_appropriate(Object);
extern Object delete_connection_to_stub(Object);
extern Object delete_frame(Object);
extern Object delete_item(Object);
extern Object delete_last_bend_from_connection_1(Object,Object);
extern Object delete_skip_list_entry(Object,Object,Object,Object,Object);
extern Object eval_cons_1(Object,Object);
extern Object frame_serial_number_setf_helper_1(Object,Object);
extern Object g2_clear_floating_connection_structures(void);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object gensym_list_3(Object,Object,Object);
extern Object get_block_at_other_end_of_connection(Object,Object);
extern Object get_connection_given_stub_designation(Object,Object);
extern Object get_port_name_given_block_and_connection(int,...);
extern Object get_position_at_this_end_of_connection(Object,Object);
extern Object install_vertices_in_connection(Object,Object,Object,Object,Object);
extern Object join_two_connections(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_connection_item_1(Object);
extern Object make_connection_item_table_skip_list_sentinel(Object,Object);
extern Object make_icon_slot_group_1(void);
extern Object make_new_transient_stub(Object,Object,Object,Object,Object,Object,Object);
extern Object make_transient_connection(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object make_transient_stub_to_replace_existing_one(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_change_to_connection_1(Object);
extern Object notify_user_at_console_and_on_logbook(int,...);
extern Object reclaim_bad_connections_of_blocks(Object,Object);
extern Object reclaim_connection_1(Object);
extern Object reclaim_connection_item_1(Object);
extern Object reclaim_connection_item_table_nodes(Object,Object);
extern Object reclaim_eval_list_1(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_skip_list_element(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_slot_value_list_1(Object);
extern Object replenish_lookup_cons_pool(void);
extern Object scope_cons(Object,Object);
extern Object send_ws_representations_connection_moved(Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object shift_blocks_with_their_external_connections(int,...);
extern Object toggle_side_for_loose_end(Object,Object);
extern Object update_connection_images(Object,Object,Object);

#else

extern Object add_bend_to_connection_1();
extern Object add_stub();
extern Object add_subworkspace_connection_post_if_appropriate();
extern Object collect_subclasses();
extern Object connect_loose_end_to_block();
extern Object connection_arrows_of_connection();
extern Object connection_is_straight_qm();
extern Object connection_line_pattern();
extern Object copy_for_slot_value();
extern Object copy_frame_serial_number();
extern Object decache_roles_for_entities_related_to_this_connection();
extern Object delete_connection();
extern Object delete_connection_leaving_stubs_if_appropriate();
extern Object delete_connection_to_stub();
extern Object delete_frame();
extern Object delete_item();
extern Object delete_last_bend_from_connection_1();
extern Object delete_skip_list_entry();
extern Object eval_cons_1();
extern Object frame_serial_number_setf_helper_1();
extern Object g2_clear_floating_connection_structures();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object gensym_list_3();
extern Object get_block_at_other_end_of_connection();
extern Object get_connection_given_stub_designation();
extern Object get_port_name_given_block_and_connection();
extern Object get_position_at_this_end_of_connection();
extern Object install_vertices_in_connection();
extern Object join_two_connections();
extern Object lookup_kb_specific_property_value();
extern Object make_connection_item_1();
extern Object make_connection_item_table_skip_list_sentinel();
extern Object make_icon_slot_group_1();
extern Object make_new_transient_stub();
extern Object make_transient_connection();
extern Object make_transient_stub_to_replace_existing_one();
extern Object memq_function();
extern Object mutate_global_property();
extern Object note_change_to_block_1();
extern Object note_change_to_connection_1();
extern Object notify_user_at_console_and_on_logbook();
extern Object reclaim_bad_connections_of_blocks();
extern Object reclaim_connection_1();
extern Object reclaim_connection_item_1();
extern Object reclaim_connection_item_table_nodes();
extern Object reclaim_eval_list_1();
extern Object reclaim_frame_serial_number();
extern Object reclaim_gensym_list_1();
extern Object reclaim_skip_list_element();
extern Object reclaim_slot_value();
extern Object reclaim_slot_value_list_1();
extern Object replenish_lookup_cons_pool();
extern Object scope_cons();
extern Object send_ws_representations_connection_moved();
extern Object set_skip_list_entry();
extern Object shift_blocks_with_their_external_connections();
extern Object toggle_side_for_loose_end();
extern Object update_connection_images();

#endif

/* variables/constants */
extern Object Available_eval_conses_tail_vector;
extern Object Available_eval_conses_vector;
extern Object Available_lookup_conses_tail_vector;
extern Object Available_lookup_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Called_within_clear_text_loading, Qcalled_within_clear_text_loading);
DECLARE_VARIABLE_WITH_SYMBOL(Connection_class_description, Qconnection_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Current_drawing_priority, Qcurrent_drawing_priority);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Default_stub_length, Qdefault_stub_length);
DECLARE_VARIABLE_WITH_SYMBOL(Delete_connections_without_leaving_stubs_qm, Qdelete_connections_without_leaving_stubs_qm);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
DECLARE_VARIABLE_WITH_SYMBOL(G2_has_v5_mode_windows_p, Qg2_has_v5_mode_windows_p);
DECLARE_VARIABLE_WITH_SYMBOL(Geometric_change_to_connection_is_temporary_p, Qgeometric_change_to_connection_is_temporary_p);
extern Object Instances_specific_to_this_class_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Loose_end_class_description, Qloose_end_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Orientation_horizontal_p, Qorientation_horizontal_p);
DECLARE_VARIABLE_WITH_SYMBOL(Permit_transfer_of_permanent_items_p, Qpermit_transfer_of_permanent_items_p);
DECLARE_VARIABLE_WITH_SYMBOL(Region_invalidation_is_preferred, Qregion_invalidation_is_preferred);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Stub_length_to_use_qm, Qstub_length_to_use_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Transient_connection_error_qm, Qtransient_connection_error_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Workspace_class_description, Qworkspace_class_description);
