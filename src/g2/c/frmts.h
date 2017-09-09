/* frmts.h -- Header File for frmts.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qquote;

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

extern Object add_class_to_environment(int,...);
extern Object add_frame_note(int,...);
extern Object add_grammar_rules_function(Object);
extern Object change_slot_value(int,...);
extern Object change_standard_format_frame_slot(Object,Object,Object);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object choose_font_format_per_font_size(Object,Object);
extern Object choose_font_format_per_fonts_table(Object,Object);
extern Object clean_frame_description_references(void);
extern Object cleanup_for_frame_style_definition(Object);
extern Object clear_optimized_constants(void);
extern Object compiled_items_referring_to_this_name_function(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_tree_using_gensym_conses_1(Object);
extern Object create_frame_description_reference(Object);
extern Object delete_frame(Object);
extern Object delete_frame_note_if_any(Object,Object);
extern Object determine_font_size_per_format(Object,Object);
extern Object do_deferred_updates_to_representations_in_tables(void);
extern Object find_differences_in_frames_if_any(int,...);
extern Object find_existing_equivalent_format_frame(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object get_instance_with_name_if_any(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_or_make_format_frame_function(Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object get_slot_value_function(Object,Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object initialize_for_frame_style_definition(Object);
extern Object initialize_slot_description_value(Object,Object,Object);
extern Object lookup_frame_description_reference_from_frame_style_definition_qm(Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_format_frame(Object);
extern Object make_frame(Object);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object parameterized_attribute_description_format(void);
extern Object parameterized_attribute_table_header_format(void);
extern Object parameterized_attribute_value_format(void);
extern Object push_optimized_constant(Object);
extern Object put_always_display_entire_item_inside_frame_where_slot_is_absent(Object,Object);
extern Object put_description_of_frame(Object,Object,Object);
extern Object put_list_of_procedure_instances_for_entity_where_slot_is_absent(Object,Object);
extern Object put_name_or_names_for_frame(Object,Object,Object);
extern Object reclaim_frame_description_reference_of_frame_style_definition_qm_value(Object,Object);
extern Object reclaim_gensym_tree_1(Object);
extern Object reclaim_slot_value(Object);
extern Object reconsider_formatting(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object release_frame_description_reference_if_any(Object);
extern Object replenish_gensym_cons_pool(void);
extern Object text_cell_first_font(Object);
extern Object tformat(int,...);
extern Object twrite(Object);
extern Object update_all_representations_of_slot(Object,Object,Object,Object);
extern Object update_frame_name_references(Object);
extern Object update_frame_status(Object,Object,Object);
extern Object update_frame_status_and_notes_for_frame_style_definition(Object);
extern Object write_font_name_from_slot(Object,Object);

#else

extern Object add_class_to_environment();
extern Object add_frame_note();
extern Object add_grammar_rules_function();
extern Object change_slot_value();
extern Object change_standard_format_frame_slot();
extern Object check_if_superior_classes_are_defined();
extern Object choose_font_format_per_font_size();
extern Object choose_font_format_per_fonts_table();
extern Object clean_frame_description_references();
extern Object cleanup_for_frame_style_definition();
extern Object clear_optimized_constants();
extern Object compiled_items_referring_to_this_name_function();
extern Object copy_for_slot_value();
extern Object copy_tree_using_gensym_conses_1();
extern Object create_frame_description_reference();
extern Object delete_frame();
extern Object delete_frame_note_if_any();
extern Object determine_font_size_per_format();
extern Object do_deferred_updates_to_representations_in_tables();
extern Object find_differences_in_frames_if_any();
extern Object find_existing_equivalent_format_frame();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object get_instance_with_name_if_any();
extern Object get_lookup_slot_value_given_default();
extern Object get_or_make_format_frame_function();
extern Object get_slot_description_of_class_description_function();
extern Object get_slot_value_function();
extern Object getfq_function_no_default();
extern Object initialize_for_frame_style_definition();
extern Object initialize_slot_description_value();
extern Object lookup_frame_description_reference_from_frame_style_definition_qm();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_format_frame();
extern Object make_frame();
extern Object memq_function();
extern Object mutate_global_property();
extern Object note_change_to_block_1();
extern Object parameterized_attribute_description_format();
extern Object parameterized_attribute_table_header_format();
extern Object parameterized_attribute_value_format();
extern Object push_optimized_constant();
extern Object put_always_display_entire_item_inside_frame_where_slot_is_absent();
extern Object put_description_of_frame();
extern Object put_list_of_procedure_instances_for_entity_where_slot_is_absent();
extern Object put_name_or_names_for_frame();
extern Object reclaim_frame_description_reference_of_frame_style_definition_qm_value();
extern Object reclaim_gensym_tree_1();
extern Object reclaim_slot_value();
extern Object reconsider_formatting();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object release_frame_description_reference_if_any();
extern Object replenish_gensym_cons_pool();
extern Object text_cell_first_font();
extern Object tformat();
extern Object twrite();
extern Object update_all_representations_of_slot();
extern Object update_frame_name_references();
extern Object update_frame_status();
extern Object update_frame_status_and_notes_for_frame_style_definition();
extern Object write_font_name_from_slot();

#endif

/* variables/constants */
extern Object Available_gensym_conses;
extern Object Blocks_to_delete_after_reading_kb;
extern Object Class_description_gkbprop;
extern Object Corresponding_extra_large_font_format_name_prop;
extern Object Corresponding_small_font_format_name_prop;
extern Object Fonts;
extern Object Format_description_prop;
extern Object Format_frame_class_description;
extern Object Instances_specific_to_this_class_kbprop;
extern Object Kb_workspace_class_description;
extern Object New_g2_classic_ui_p;
extern Object Noting_changes_to_kb_p;
extern Object Reading_kb_p;
extern Object Stack_of_slot_value_changes;
extern Object Suppress_updating_of_slot_value_representations_qm;
extern Object Suppress_use_of_stack_of_slot_value_changes_p;
