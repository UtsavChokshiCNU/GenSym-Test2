/* cnct4.h -- Header File for cnct4.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qeq;

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

extern Object add_or_delete_subworkspace_connection_post(Object,Object,Object);
extern Object add_or_delete_subworkspace_connection_post_from_connection(Object,Object,Object,Object,Object);
extern Object add_subworkspace_connection_post(Object,Object,Object,Object);
extern Object add_subworkspace_connection_post_to_connection(Object,Object,Object);
extern Object add_subworkspace_connection_posts(Object,Object);
extern Object change_connection_attribute(Object,Object,Object);
extern Object change_connection_post_connection_cache(Object,Object,Object,Object);
extern Object change_slot_value(int,...);
extern Object clone_connections_for_block(Object,Object,Object);
extern Object clone_connections_slot(Object,Object,Object,Object);
extern Object clone_stub_for_connection(Object,Object,Object,Object);
extern Object connection_post_x_and_y_given_position_and_side(Object,Object,Object);
extern Object copy_list_using_gensym_conses_1(Object);
extern Object decache_roles_for_connection_post(Object);
extern Object decache_roles_for_entities_related_to_this_connection(Object);
extern Object delete_balanced_binary_tree_entry(Object,Object,Object,Object);
extern Object delete_connection(int,...);
extern Object delete_connection_in_block(Object,Object,Object);
extern Object delete_frame(Object);
extern Object delete_subworkspace_connection_post_if_superfluous(Object);
extern Object determine_subworkspace_connection_posts(Object);
extern Object determine_subworkspace_connection_posts_for_object(Object,Object);
extern Object flush_all_subworkspace_connection_posts_for_object(Object,Object);
extern Object flush_subworkspace_connection_post_set(Object,Object,Object,Object);
extern Object flush_subworkspace_connection_posts(Object,Object,Object);
extern Object flush_subworkspace_connection_posts_for_object(Object,Object,Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object get_block_at_other_end_of_connection(Object,Object);
extern Object get_connection_given_stub_designation(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_savable_connection_attributes_plist(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object handle_connection_post_addition_or_removal_as_subblock(Object,Object);
extern Object handle_connection_post_addition_or_removal_as_subblock_1(Object,Object);
extern Object make_cloned_connection_stub_be_copy_of_connection(Object,Object,Object,Object,Object);
extern Object make_connection_item_1(Object);
extern Object make_entity(int,...);
extern Object make_icon_slot_group_1(void);
extern Object mutate_global_property(Object,Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_change_to_connection_1(Object);
extern Object put_superior_connection(Object,Object,Object);
extern Object reclaim_connection_item_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object remove_subworkspace_connection_post_from_connection(Object,Object,Object,Object);
extern Object replenish_gensym_cons_pool(void);
extern Object scale_subworkspace_connection_post_position(Object,Object,Object,Object);
extern Object scope_cons(Object,Object);
extern Object set_balanced_binary_tree_entry(Object,Object,Object,Object,Object,Object,Object);
extern Object set_lookup_slot_value_1(Object,Object,Object);
extern Object transfer_blocks_with_their_external_connections(Object,Object,Object,Object,Object);

#else

extern Object add_or_delete_subworkspace_connection_post();
extern Object add_or_delete_subworkspace_connection_post_from_connection();
extern Object add_subworkspace_connection_post();
extern Object add_subworkspace_connection_post_to_connection();
extern Object add_subworkspace_connection_posts();
extern Object change_connection_attribute();
extern Object change_connection_post_connection_cache();
extern Object change_slot_value();
extern Object clone_connections_for_block();
extern Object clone_connections_slot();
extern Object clone_stub_for_connection();
extern Object connection_post_x_and_y_given_position_and_side();
extern Object copy_list_using_gensym_conses_1();
extern Object decache_roles_for_connection_post();
extern Object decache_roles_for_entities_related_to_this_connection();
extern Object delete_balanced_binary_tree_entry();
extern Object delete_connection();
extern Object delete_connection_in_block();
extern Object delete_frame();
extern Object delete_subworkspace_connection_post_if_superfluous();
extern Object determine_subworkspace_connection_posts();
extern Object determine_subworkspace_connection_posts_for_object();
extern Object flush_all_subworkspace_connection_posts_for_object();
extern Object flush_subworkspace_connection_post_set();
extern Object flush_subworkspace_connection_posts();
extern Object flush_subworkspace_connection_posts_for_object();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object get_block_at_other_end_of_connection();
extern Object get_connection_given_stub_designation();
extern Object get_lookup_slot_value_given_default();
extern Object get_savable_connection_attributes_plist();
extern Object getfq_function_no_default();
extern Object handle_connection_post_addition_or_removal_as_subblock();
extern Object handle_connection_post_addition_or_removal_as_subblock_1();
extern Object make_cloned_connection_stub_be_copy_of_connection();
extern Object make_connection_item_1();
extern Object make_entity();
extern Object make_icon_slot_group_1();
extern Object mutate_global_property();
extern Object note_change_to_block_1();
extern Object note_change_to_connection_1();
extern Object put_superior_connection();
extern Object reclaim_connection_item_1();
extern Object reclaim_gensym_list_1();
extern Object remove_subworkspace_connection_post_from_connection();
extern Object replenish_gensym_cons_pool();
extern Object scale_subworkspace_connection_post_position();
extern Object scope_cons();
extern Object set_balanced_binary_tree_entry();
extern Object set_lookup_slot_value_1();
extern Object transfer_blocks_with_their_external_connections();

#endif

/* variables/constants */
extern Object Available_gensym_conses;
extern Object Connection_post_class_description;
extern Object Connection_post_indentation;
extern Object Disable_stack_error;
extern Object Geometric_change_to_connection_is_temporary_p;
extern Object Kb_workspace_class_description;
extern Object Loading_kb_p;
extern Object Noting_changes_to_kb_p;
extern Object Object_class_description;
extern Object Savable_connection_attributes;
extern Object Scope_conses;
