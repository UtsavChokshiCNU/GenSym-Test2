/* sqncs3.h -- Header File for sqncs3.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Qunsigned_byte;

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
extern Object clean_out_annotation_lookup_structure(Object);
extern Object collect_subclasses(Object);
extern Object constant_queue_next(Object,Object);
extern Object convert_text_string_to_text(Object);
extern Object copy_constant_wide_string_given_length(Object,Object);
extern Object enter_package_preparation_mode(void);
extern Object equalw(Object,Object);
extern Object g2_equiv(Object,Object);
extern Object get_property_value_function(int,...);
extern Object get_slot_description_value(Object,Object);
extern Object get_slot_value_function(Object,Object,Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object inform_ui_client_interfaces_of_general_update(Object,Object);
extern Object leave_package_preparation_mode(void);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_new_stripped_text(void);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object notify_user(int,...);
extern Object reclaim_text(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object reformat_text_box_in_place(int,...);
extern Object scope_cons(Object,Object);
extern Object set_package_preparation_mode(Object);
extern Object set_stripping_flags_as_specified(Object,Object,Object);
extern Object strip_all_texts(void);
extern Object strip_choice_obtains_p(Object,Object);
extern Object strip_text_for_block(Object,Object);
extern Object strip_texts_from_item(Object);
extern Object stripped_text_p(Object);
extern Object stripping_inherited_p(Object);
extern Object superior_frame(Object);
extern Object text_slots_in_frame_have_been_stripped_p(Object);
extern Object type_of_slot_if_editable(int,...);
extern Object update_images_of_block(Object,Object,Object);
extern Object update_representations_of_slot_value(int,...);
extern Object update_subscriptions_from_virtual_attribute_change(Object,Object,Object);

#else

extern Object assq_function();
extern Object clean_out_annotation_lookup_structure();
extern Object collect_subclasses();
extern Object constant_queue_next();
extern Object convert_text_string_to_text();
extern Object copy_constant_wide_string_given_length();
extern Object enter_package_preparation_mode();
extern Object equalw();
extern Object g2_equiv();
extern Object get_property_value_function();
extern Object get_slot_description_value();
extern Object get_slot_value_function();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object inform_ui_client_interfaces_of_general_update();
extern Object leave_package_preparation_mode();
extern Object lookup_kb_specific_property_value();
extern Object make_new_stripped_text();
extern Object memq_function();
extern Object mutate_global_property();
extern Object note_change_to_block_1();
extern Object notify_user();
extern Object reclaim_text();
extern Object record_system_variable();
extern Object reformat_text_box_in_place();
extern Object scope_cons();
extern Object set_package_preparation_mode();
extern Object set_stripping_flags_as_specified();
extern Object strip_all_texts();
extern Object strip_choice_obtains_p();
extern Object strip_text_for_block();
extern Object strip_texts_from_item();
extern Object stripped_text_p();
extern Object stripping_inherited_p();
extern Object superior_frame();
extern Object text_slots_in_frame_have_been_stripped_p();
extern Object type_of_slot_if_editable();
extern Object update_images_of_block();
extern Object update_representations_of_slot_value();
extern Object update_subscriptions_from_virtual_attribute_change();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Archtypal_stripped_text, Qarchtypal_stripped_text);
DECLARE_VARIABLE_WITH_SYMBOL(Current_drawing_priority, Qcurrent_drawing_priority);
DECLARE_VARIABLE_WITH_SYMBOL(Entity_class_description, Qentity_class_description);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
extern Object Instances_specific_to_this_class_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Kb_workspace_class_description, Qkb_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Package_preparation_mode, Qpackage_preparation_mode);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Suppress_updating_of_self_representations_qm, Qsuppress_updating_of_self_representations_qm);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_class_description, Qvariable_class_description);
