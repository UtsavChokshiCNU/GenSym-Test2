/* cnct3a.h -- Header File for cnct3a.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qeq;
extern Object Qremove;

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

extern Object activate_connection_frame_if_appropriate(Object,Object);
extern Object add_connection_to_spacial_index(Object,Object);
extern Object add_cursors_to_current_window(Object,Object,Object,Object,Object,Object,Object);
extern Object add_missing_deltas_to_connection(Object);
extern Object add_rectangle_to_region(Object,Object,Object,Object,Object);
extern Object add_subblock(Object,Object);
extern Object add_thing_to_spacial_index(Object,Object,Object);
extern Object always_instantiate_connection_frame_for_this_class_qm(Object);
extern Object block_or_connection_less_p(Object,Object);
extern Object block_or_connection_might_overlap_p(Object);
extern Object block_or_connection_overlap_cache(Object);
extern Object block_or_connection_overlap_cache_p(Object);
extern Object block_or_connection_overlap_cache_valid_p(Object);
extern Object block_or_connection_overlaps_window_rectangle_p(Object,Object,Object,Object,Object);
extern Object block_overlaps_window_rectangle_p(Object,Object,Object,Object,Object);
extern Object blocks_potentially_touching_region(Object,Object);
extern Object blocks_touching_region_for_drawing(Object,Object,Object);
extern Object blocks_touching_region_of_image_plane(Object,Object,Object);
extern Object bounding_region_of_block_or_connection(Object);
extern Object build_spacial_index(Object);
extern Object change_connection_attribute_1(Object,Object,Object);
extern Object change_connection_deltas_for_object_being_dragged(Object,Object,Object,Object);
extern Object clone_connection_attributes_plist(Object,Object);
extern Object compute_connection_half_width_adjusted_for_fins(Object);
extern Object compute_connection_vertices(Object);
extern Object compute_dragged_connection_anchor_point(Object,Object);
extern Object compute_last_delta_anchor_point(int,...);
extern Object compute_miter_points(Object,Object);
extern Object compute_new_vertex(Object,Object,Object,Object,Object,Object);
extern Object compute_stretched_links_of_connection_being_dragged(Object,Object);
extern Object compute_user_visible_layer_position_of_item(Object);
extern Object connection_arrow_width(Object);
extern Object connection_bounding_region(Object);
extern Object connection_cross_section_patterns_compatible_qm(Object,Object);
extern Object connection_fin_length(int,...);
extern Object connection_frame_of_connection_qm(Object);
extern Object connection_has_arrows_p(Object);
extern Object connection_line_pattern(Object);
extern Object connection_overlaps_window_rectangle_p(Object,Object,Object,Object,Object);
extern Object connection_overlaps_window_rectangle_p_1(Object,Object,Object,Object,Object);
extern Object connection_vertices_in_workspace(Object);
extern Object constant_queue_next(Object,Object);
extern Object copy_frame_serial_number(Object);
extern Object copy_list_using_slot_value_conses_1(Object);
extern Object copy_list_using_tree_ordering_conses_1(Object);
extern Object create_geometry(Object,Object,Object,Object,Object);
extern Object decache_roles_for_entities_related_to_this_connection(Object);
extern Object delete_connection(int,...);
extern Object delete_frame(Object);
extern Object delete_last_bend_from_connection(Object,Object);
extern Object delete_slot_value_element_1(Object,Object);
extern Object descendents_of_block_or_connection(Object);
extern Object destroy_spacial_index(Object);
extern Object determine_connection_terminal_coordinate(Object,Object);
extern Object determine_position_of_and_insert_junction_block(Object,Object,Object);
extern Object draw_block_or_connection(Object);
extern Object draw_block_possibly_with_frame(Object,Object);
extern Object draw_blocks_overlapping_connection(Object,Object);
extern Object draw_connection(Object,Object);
extern Object draw_current_connection_overlapping_things(Object,Object,Object,Object,Object);
extern Object draw_overlapping_blocks(Object,Object,Object,Object);
extern Object draw_overlapping_xor_blocks(Object,Object);
extern Object ensure_layer_positions(Object);
extern Object ensure_spacial_index_is_up_to_date(Object);
extern Object find_vector_length_from_point_to_block_connections_if_within_limit(Object,Object,Object,Object,Object);
extern Object find_vector_length_from_point_to_connection_if_within_limit(Object,Object,Object,Object);
extern Object find_vector_length_from_point_to_connection_link(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object find_vector_length_from_point_to_diagonal_connection_link(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object find_vector_length_from_point_to_diagonal_connection_link_1(Object,Object,Object,Object,Object,Object,Object);
extern Object float_distance(Object,Object);
extern Object frame_description_reference_of_block_qm(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object geometry_delete(Object,Object,Object,Object,Object,Object);
extern Object geometry_find_in_region(Object,Object);
extern Object geometry_flush(Object,Object);
extern Object geometry_insert(Object,Object,Object,Object,Object,Object);
extern Object get_block_at_other_end_of_connection(Object,Object);
extern Object get_connection_for_loose_end(Object);
extern Object get_direction_of_connection(int,...);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_or_make_connection_frame_and_activate_if_appropriate(Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object get_workspace_if_any(Object);
extern Object get_workspace_of_block_or_connection(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object image_plane_background_images(Object);
extern Object image_plane_has_drawing_in_window_p(Object);
extern Object increment_current_frame_serial_number(void);
extern Object insert_junction_block(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object intersect_region(Object,Object);
extern Object local_edges_of_block_or_connection(Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object loose_end_connection_p(Object);
extern Object make_connection_1(void);
extern Object make_connection_item_1(Object);
extern Object make_connection_item_table_skip_list_sentinel(Object,Object);
extern Object make_empty_region(void);
extern Object make_entity(int,...);
extern Object make_icon_slot_group_1(void);
extern Object make_junction(Object,Object);
extern Object make_new_connection_frame_for_connection(Object,Object);
extern Object make_region_from_rectangle(Object,Object,Object,Object);
extern Object make_symbol_properties_hash_table_skip_list_sentinel(Object,Object);
extern Object map_over_connection_arrows(Object,Object,Object,Object);
extern Object map_over_connection_rectangles(Object,Object,Object);
extern Object map_over_diagonal_connection_rectangles(Object,Object,Object);
extern Object map_over_orthogonal_or_thin_diagonal_connection_rectangles(Object,Object,Object);
extern Object memq_function(Object,Object);
extern Object mouse_leeway_in_workspace(Object);
extern Object note_change_of_connection_for_drawing(Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_change_to_connection_1(Object);
extern Object note_change_to_workspace_geometry(Object);
extern Object note_deletion_of_connection_for_drawing(Object);
extern Object note_deletion_of_connection_for_selection(Object);
extern Object notify_user(int,...);
extern Object output_connections_of_block(Object);
extern Object overlapping_siblings(Object,Object,Object);
extern Object printing_image_plane_p(Object);
extern Object reclaim_connection_item_table_nodes(Object,Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_geometry(Object);
extern Object reclaim_region(Object);
extern Object reclaim_skip_list_element(Object);
extern Object reclaim_slot_value_list_1(Object);
extern Object reclaim_tree_ordering_list_1(Object);
extern Object recompute_layer_positions(Object);
extern Object rectangle_for_connection_segment(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object region_containing_background_images(Object);
extern Object region_covers_workspace_qm(Object,Object);
extern Object regions_intersect_p(Object,Object);
extern Object remove_block_from_drawing_queues(Object,Object);
extern Object remove_last_delta_from_connection(Object);
extern Object remove_redundant_deltas_from_connection(Object);
extern Object remove_subblocks_and_connections_from_drawing_queues(Object,Object);
extern Object remove_thing_from_image_plane_drawing_queues(Object,Object);
extern Object remove_thing_from_spacial_index(Object,Object,Object);
extern Object replace_connection_in_block(Object,Object,Object);
extern Object replenish_lookup_cons_pool(void);
extern Object scalef_function(Object,Object);
extern Object scope_cons(Object,Object);
extern Object send_ws_representations_connection_moved(Object);
extern Object send_ws_representations_item_insert_as_subblock(Object,Object,Object);
extern Object send_ws_representations_item_layer_change(Object,Object,Object);
extern Object set_block_or_connection_overlap_cache(Object,Object);
extern Object set_block_or_connection_overlap_cache_p(Object,Object);
extern Object set_block_or_connection_overlap_cache_valid_p(Object,Object);
extern Object set_input_end_of_connection_1(Object,Object,Object);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object set_output_end_of_connection_1(Object,Object,Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object shift_block(Object,Object,Object);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_list_2(Object,Object);
extern Object sort_list(Object,Object,Object);
extern Object subtract_region(Object,Object);
extern Object suppress_printing_border_p(Object);
extern Object transform_region_to_workspace_coordinates(Object);
extern Object tree_ordering_cons_1(Object,Object);
extern Object update_connection_images(Object,Object,Object);
extern Object update_extreme_edges_from_block_bounds(Object);
extern Object update_extreme_edges_from_connection(Object);
extern Object update_extreme_edges_from_connection_1(Object,Object,Object,Object,Object);
extern Object update_extreme_edges_from_connections_of_block(Object,Object);
extern Object update_images_of_block(Object,Object,Object);
extern Object update_runtime_structures_according_to_edit(int,...);
extern Object update_spacial_index(Object,Object,Object);
extern Object validate_layer_positions(Object);
extern Object validate_overlapping_cache_for_workspace(Object);
extern Object workspace_of_connection_qm(Object);

#else

extern Object activate_connection_frame_if_appropriate();
extern Object add_connection_to_spacial_index();
extern Object add_cursors_to_current_window();
extern Object add_missing_deltas_to_connection();
extern Object add_rectangle_to_region();
extern Object add_subblock();
extern Object add_thing_to_spacial_index();
extern Object always_instantiate_connection_frame_for_this_class_qm();
extern Object block_or_connection_less_p();
extern Object block_or_connection_might_overlap_p();
extern Object block_or_connection_overlap_cache();
extern Object block_or_connection_overlap_cache_p();
extern Object block_or_connection_overlap_cache_valid_p();
extern Object block_or_connection_overlaps_window_rectangle_p();
extern Object block_overlaps_window_rectangle_p();
extern Object blocks_potentially_touching_region();
extern Object blocks_touching_region_for_drawing();
extern Object blocks_touching_region_of_image_plane();
extern Object bounding_region_of_block_or_connection();
extern Object build_spacial_index();
extern Object change_connection_attribute_1();
extern Object change_connection_deltas_for_object_being_dragged();
extern Object clone_connection_attributes_plist();
extern Object compute_connection_half_width_adjusted_for_fins();
extern Object compute_connection_vertices();
extern Object compute_dragged_connection_anchor_point();
extern Object compute_last_delta_anchor_point();
extern Object compute_miter_points();
extern Object compute_new_vertex();
extern Object compute_stretched_links_of_connection_being_dragged();
extern Object compute_user_visible_layer_position_of_item();
extern Object connection_arrow_width();
extern Object connection_bounding_region();
extern Object connection_cross_section_patterns_compatible_qm();
extern Object connection_fin_length();
extern Object connection_frame_of_connection_qm();
extern Object connection_has_arrows_p();
extern Object connection_line_pattern();
extern Object connection_overlaps_window_rectangle_p();
extern Object connection_overlaps_window_rectangle_p_1();
extern Object connection_vertices_in_workspace();
extern Object constant_queue_next();
extern Object copy_frame_serial_number();
extern Object copy_list_using_slot_value_conses_1();
extern Object copy_list_using_tree_ordering_conses_1();
extern Object create_geometry();
extern Object decache_roles_for_entities_related_to_this_connection();
extern Object delete_connection();
extern Object delete_frame();
extern Object delete_last_bend_from_connection();
extern Object delete_slot_value_element_1();
extern Object descendents_of_block_or_connection();
extern Object destroy_spacial_index();
extern Object determine_connection_terminal_coordinate();
extern Object determine_position_of_and_insert_junction_block();
extern Object draw_block_or_connection();
extern Object draw_block_possibly_with_frame();
extern Object draw_blocks_overlapping_connection();
extern Object draw_connection();
extern Object draw_current_connection_overlapping_things();
extern Object draw_overlapping_blocks();
extern Object draw_overlapping_xor_blocks();
extern Object ensure_layer_positions();
extern Object ensure_spacial_index_is_up_to_date();
extern Object find_vector_length_from_point_to_block_connections_if_within_limit();
extern Object find_vector_length_from_point_to_connection_if_within_limit();
extern Object find_vector_length_from_point_to_connection_link();
extern Object find_vector_length_from_point_to_diagonal_connection_link();
extern Object find_vector_length_from_point_to_diagonal_connection_link_1();
extern Object float_distance();
extern Object frame_description_reference_of_block_qm();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object geometry_delete();
extern Object geometry_find_in_region();
extern Object geometry_flush();
extern Object geometry_insert();
extern Object get_block_at_other_end_of_connection();
extern Object get_connection_for_loose_end();
extern Object get_direction_of_connection();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_or_make_connection_frame_and_activate_if_appropriate();
extern Object get_slot_description_of_class_description_function();
extern Object get_workspace_if_any();
extern Object get_workspace_of_block_or_connection();
extern Object getfq_function_no_default();
extern Object image_plane_background_images();
extern Object image_plane_has_drawing_in_window_p();
extern Object increment_current_frame_serial_number();
extern Object insert_junction_block();
extern Object intersect_region();
extern Object local_edges_of_block_or_connection();
extern Object lookup_global_or_kb_specific_property_value();
extern Object loose_end_connection_p();
extern Object make_connection_1();
extern Object make_connection_item_1();
extern Object make_connection_item_table_skip_list_sentinel();
extern Object make_empty_region();
extern Object make_entity();
extern Object make_icon_slot_group_1();
extern Object make_junction();
extern Object make_new_connection_frame_for_connection();
extern Object make_region_from_rectangle();
extern Object make_symbol_properties_hash_table_skip_list_sentinel();
extern Object map_over_connection_arrows();
extern Object map_over_connection_rectangles();
extern Object map_over_diagonal_connection_rectangles();
extern Object map_over_orthogonal_or_thin_diagonal_connection_rectangles();
extern Object memq_function();
extern Object mouse_leeway_in_workspace();
extern Object note_change_of_connection_for_drawing();
extern Object note_change_to_block_1();
extern Object note_change_to_connection_1();
extern Object note_change_to_workspace_geometry();
extern Object note_deletion_of_connection_for_drawing();
extern Object note_deletion_of_connection_for_selection();
extern Object notify_user();
extern Object output_connections_of_block();
extern Object overlapping_siblings();
extern Object printing_image_plane_p();
extern Object reclaim_connection_item_table_nodes();
extern Object reclaim_gensym_list_1();
extern Object reclaim_geometry();
extern Object reclaim_region();
extern Object reclaim_skip_list_element();
extern Object reclaim_slot_value_list_1();
extern Object reclaim_tree_ordering_list_1();
extern Object recompute_layer_positions();
extern Object rectangle_for_connection_segment();
extern Object region_containing_background_images();
extern Object region_covers_workspace_qm();
extern Object regions_intersect_p();
extern Object remove_block_from_drawing_queues();
extern Object remove_last_delta_from_connection();
extern Object remove_redundant_deltas_from_connection();
extern Object remove_subblocks_and_connections_from_drawing_queues();
extern Object remove_thing_from_image_plane_drawing_queues();
extern Object remove_thing_from_spacial_index();
extern Object replace_connection_in_block();
extern Object replenish_lookup_cons_pool();
extern Object scalef_function();
extern Object scope_cons();
extern Object send_ws_representations_connection_moved();
extern Object send_ws_representations_item_insert_as_subblock();
extern Object send_ws_representations_item_layer_change();
extern Object set_block_or_connection_overlap_cache();
extern Object set_block_or_connection_overlap_cache_p();
extern Object set_block_or_connection_overlap_cache_valid_p();
extern Object set_input_end_of_connection_1();
extern Object set_non_savable_lookup_slot_value();
extern Object set_output_end_of_connection_1();
extern Object set_skip_list_entry();
extern Object shift_block();
extern Object slot_value_cons_1();
extern Object slot_value_list_2();
extern Object sort_list();
extern Object subtract_region();
extern Object suppress_printing_border_p();
extern Object transform_region_to_workspace_coordinates();
extern Object tree_ordering_cons_1();
extern Object update_connection_images();
extern Object update_extreme_edges_from_block_bounds();
extern Object update_extreme_edges_from_connection();
extern Object update_extreme_edges_from_connection_1();
extern Object update_extreme_edges_from_connections_of_block();
extern Object update_images_of_block();
extern Object update_runtime_structures_according_to_edit();
extern Object update_spacial_index();
extern Object validate_layer_positions();
extern Object validate_overlapping_cache_for_workspace();
extern Object workspace_of_connection_qm();

#endif

/* variables/constants */
extern Object Available_lookup_conses_tail_vector;
extern Object Available_lookup_conses_vector;
extern Object Available_tree_ordering_conses_tail_vector;
extern Object Available_tree_ordering_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Bottom_edge_of_draw_area, Qbottom_edge_of_draw_area);
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Connection_class_description, Qconnection_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Current_delta, Qcurrent_delta);
DECLARE_VARIABLE_WITH_SYMBOL(Current_drawing_transfer_mode, Qcurrent_drawing_transfer_mode);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_transform_qm, Qcurrent_frame_transform_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_x_scale, Qcurrent_image_x_scale);
DECLARE_VARIABLE_WITH_SYMBOL(Current_image_y_scale, Qcurrent_image_y_scale);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_specific_property_list_property_name, Qcurrent_kb_specific_property_list_property_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_x_origin_of_drawing, Qcurrent_x_origin_of_drawing);
DECLARE_VARIABLE_WITH_SYMBOL(Current_y_origin_of_drawing, Qcurrent_y_origin_of_drawing);
DECLARE_VARIABLE_WITH_SYMBOL(Default_junction_class_description, Qdefault_junction_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Default_size_of_spacial_index, Qdefault_size_of_spacial_index);
DECLARE_VARIABLE_WITH_SYMBOL(Dont_include_offset_for_end_position_qm, Qdont_include_offset_for_end_position_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Erase_instead_qm, Qerase_instead_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Extreme_bottom_edge_so_far, Qextreme_bottom_edge_so_far);
DECLARE_VARIABLE_WITH_SYMBOL(Extreme_left_edge_so_far, Qextreme_left_edge_so_far);
DECLARE_VARIABLE_WITH_SYMBOL(Extreme_right_edge_so_far, Qextreme_right_edge_so_far);
DECLARE_VARIABLE_WITH_SYMBOL(Extreme_top_edge_so_far, Qextreme_top_edge_so_far);
DECLARE_VARIABLE_WITH_SYMBOL(G2_has_v5_mode_windows_p, Qg2_has_v5_mode_windows_p);
DECLARE_VARIABLE_WITH_SYMBOL(Geometric_change_to_connection_is_temporary_p, Qgeometric_change_to_connection_is_temporary_p);
extern Object Isqrt_of_most_positive_fixnum;
DECLARE_VARIABLE_WITH_SYMBOL(Left_edge_of_draw_area, Qleft_edge_of_draw_area);
DECLARE_VARIABLE_WITH_SYMBOL(Loading_kb_p, Qloading_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Loose_end_class_description, Qloose_end_class_description);
extern Object Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation;
extern Object Minus_of_isqrt_of_most_positive_fixnum;
extern Object No_specific_property_value;
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Objects_to_not_consider_qm, Qobjects_to_not_consider_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Orientation_horizontal_p, Qorientation_horizontal_p);
extern Object Positive_bits_per_fixnum;
DECLARE_VARIABLE_WITH_SYMBOL(Right_edge_of_draw_area, Qright_edge_of_draw_area);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
extern Object Symbol_properties_table;
DECLARE_VARIABLE_WITH_SYMBOL(Top_edge_of_draw_area, Qtop_edge_of_draw_area);
extern Object Tree_traversal_marker;
DECLARE_VARIABLE_WITH_SYMBOL(Workspace_class_description, Qworkspace_class_description);
extern Object Workspace_geometry_tick_mask;
