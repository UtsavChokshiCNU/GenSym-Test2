/* vwmsg1.c
 * Input file:  view-msg1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "vwmsg1.h"


Object View_message_receiver_prop = UNBOUND;

Object View_message_sender_prop = UNBOUND;

Object Object_definition_message_receiver_prop = UNBOUND;

Object Object_definition_message_sender_prop = UNBOUND;

Object Ws_representation_type_prop = UNBOUND;

Object The_type_description_of_ws_representation_type = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_ws_representation_types, Qchain_of_available_ws_representation_types);

DEFINE_VARIABLE_WITH_SYMBOL(Ws_representation_type_count, Qws_representation_type_count);

Object Chain_of_available_ws_representation_types_vector = UNBOUND;

/* WS-REPRESENTATION-TYPE-STRUCTURE-MEMORY-USAGE */
Object ws_representation_type_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(227,0);
    temp = Ws_representation_type_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-WS-REPRESENTATION-TYPE-COUNT */
Object outstanding_ws_representation_type_count()
{
    Object def_structure_ws_representation_type_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(227,1);
    gensymed_symbol = IFIX(Ws_representation_type_count);
    def_structure_ws_representation_type_variable = 
	    Chain_of_available_ws_representation_types;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_ws_representation_type_variable))
	goto end_loop;
    def_structure_ws_representation_type_variable = 
	    ISVREF(def_structure_ws_representation_type_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-WS-REPRESENTATION-TYPE-1 */
Object reclaim_ws_representation_type_1(ws_representation_type)
    Object ws_representation_type;
{
    Object temp, svref_arg_2;

    x_note_fn_call(227,2);
    inline_note_reclaim_cons(ws_representation_type,Nil);
    temp = ISVREF(Chain_of_available_ws_representation_types_vector,
	    IFIX(Current_thread_index));
    SVREF(ws_representation_type,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_ws_representation_types_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = ws_representation_type;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WS-REPRESENTATION-TYPE */
Object reclaim_structure_for_ws_representation_type(ws_representation_type)
    Object ws_representation_type;
{
    x_note_fn_call(227,3);
    return reclaim_ws_representation_type_1(ws_representation_type);
}

static Object Qg2_defstruct_structure_name_ws_representation_type_g2_struct;  /* g2-defstruct-structure-name::ws-representation-type-g2-struct */

/* MAKE-PERMANENT-WS-REPRESENTATION-TYPE-STRUCTURE-INTERNAL */
Object make_permanent_ws_representation_type_structure_internal()
{
    Object def_structure_ws_representation_type_variable;
    Object defstruct_g2_ws_representation_type_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(227,4);
    def_structure_ws_representation_type_variable = Nil;
    atomic_incff_symval(Qws_representation_type_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_ws_representation_type_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_ws_representation_type_variable = the_array;
	SVREF(defstruct_g2_ws_representation_type_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ws_representation_type_g2_struct;
	def_structure_ws_representation_type_variable = 
		defstruct_g2_ws_representation_type_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_ws_representation_type_variable);
}

/* MAKE-WS-REPRESENTATION-TYPE-1 */
Object make_ws_representation_type_1()
{
    Object def_structure_ws_representation_type_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(227,5);
    def_structure_ws_representation_type_variable = 
	    ISVREF(Chain_of_available_ws_representation_types_vector,
	    IFIX(Current_thread_index));
    if (def_structure_ws_representation_type_variable) {
	svref_arg_1 = Chain_of_available_ws_representation_types_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_ws_representation_type_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_ws_representation_type_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ws_representation_type_g2_struct;
    }
    else
	def_structure_ws_representation_type_variable = 
		make_permanent_ws_representation_type_structure_internal();
    inline_note_allocate_cons(def_structure_ws_representation_type_variable,
	    Nil);
    return VALUES_1(def_structure_ws_representation_type_variable);
}

void view_msg1_INIT()
{
    Object temp, reclaim_structure_for_ws_representation_type_1, ws_rep_type;
    Object Qtable_property_getter, list_constant_5;
    Object Qattribute_table_with_header, Qws_representation_type, AB_package;
    Object Qclassic_attribute_table, Qshort_representation, Qattribute_table;
    Object Qattribute_display, Qtype_in_box_property_getter, list_constant_8;
    Object Qtype_in_box, Qlast_value_displayed, Qlabel;
    Object Qslider_property_getter, list_constant_7, Qslider, Qreadout_value;
    Object Qcheck_box_property_getter, list_constant_6, Qcheck_box;
    Object Qradio_button_property_getter, Qradio_button;
    Object Qaction_button_property_getter, Qaction_button, Qbutton_state;
    Object Qfreeform_table, list_constant_3, list_constant_2;
    Object Qchart_property_getter, Qchart_property_spec, Qgraph;
    Object Qtrend_chart_property_getter, Qtrend_chart_property_spec;
    Object Qtrend_chart, Qmeter_property_getter, list_constant_4, Qmeter;
    Object Qdial_property_getter, Qdial, Qincrement, Qhigh_value, Qlow_value;
    Object Qreadout_table, Qrow_info, Qrow_label, Qtext_box_property_getter;
    Object list_constant_1, Qtext_box, Qab_structure, Qtext_box_format;
    Object Qtext_lines, Qconnection_property_getter, list_constant;
    Object Qconnection, Qstub_length, Qstyle, Qloose_end;
    Object Qicon_without_connections, Qicon_with_connections;
    Object Qreclaim_structure, Qoutstanding_ws_representation_type_count;
    Object Qws_representation_type_structure_memory_usage, Qutilities2;
    Object string_constant_1, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qobject_definition_message_sender;
    Object Qobject_definition_message_receiver, Qview_message_sender;
    Object Qview_message_receiver;

    x_note_fn_call(227,6);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qview_message_receiver = STATIC_SYMBOL("VIEW-MESSAGE-RECEIVER",AB_package);
    View_message_receiver_prop = Qview_message_receiver;
    Qview_message_sender = STATIC_SYMBOL("VIEW-MESSAGE-SENDER",AB_package);
    View_message_sender_prop = Qview_message_sender;
    Qobject_definition_message_receiver = 
	    STATIC_SYMBOL("OBJECT-DEFINITION-MESSAGE-RECEIVER",AB_package);
    Object_definition_message_receiver_prop = 
	    Qobject_definition_message_receiver;
    Qobject_definition_message_sender = 
	    STATIC_SYMBOL("OBJECT-DEFINITION-MESSAGE-SENDER",AB_package);
    Object_definition_message_sender_prop = Qobject_definition_message_sender;
    Qws_representation_type = STATIC_SYMBOL("WS-REPRESENTATION-TYPE",
	    AB_package);
    Ws_representation_type_prop = Qws_representation_type;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_ws_representation_type_g2_struct = 
	    STATIC_SYMBOL("WS-REPRESENTATION-TYPE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_ws_representation_type_g2_struct,
	    Qws_representation_type,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qws_representation_type,
	    Qg2_defstruct_structure_name_ws_representation_type_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_ws_representation_type == UNBOUND)
	The_type_description_of_ws_representation_type = Nil;
    string_constant = STATIC_STRING("43Dy8m83ohy1n83ohy8n8k1l8n0000000kpk0k0");
    temp = The_type_description_of_ws_representation_type;
    The_type_description_of_ws_representation_type = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_ws_representation_type_g2_struct,
	    The_type_description_of_ws_representation_type,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qws_representation_type,
	    The_type_description_of_ws_representation_type,
	    Qtype_description_of_type);
    Qoutstanding_ws_representation_type_count = 
	    STATIC_SYMBOL("OUTSTANDING-WS-REPRESENTATION-TYPE-COUNT",
	    AB_package);
    Qws_representation_type_structure_memory_usage = 
	    STATIC_SYMBOL("WS-REPRESENTATION-TYPE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_1 = STATIC_STRING("1q83ohy8s83-xiy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_ws_representation_type_count);
    push_optimized_constant(Qws_representation_type_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_ws_representation_types = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WS-REPRESENTATION-TYPES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_ws_representation_types,
	    Chain_of_available_ws_representation_types);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_ws_representation_types,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qws_representation_type_count = 
	    STATIC_SYMBOL("WS-REPRESENTATION-TYPE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qws_representation_type_count,
	    Ws_representation_type_count);
    record_system_variable(Qws_representation_type_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_ws_representation_types_vector == UNBOUND)
	Chain_of_available_ws_representation_types_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qws_representation_type_structure_memory_usage,
	    STATIC_FUNCTION(ws_representation_type_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_ws_representation_type_count,
	    STATIC_FUNCTION(outstanding_ws_representation_type_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_ws_representation_type_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_ws_representation_type,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qws_representation_type,
	    reclaim_structure_for_ws_representation_type_1);
    Qicon_with_connections = STATIC_SYMBOL("ICON-WITH-CONNECTIONS",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qicon_with_connections,ws_rep_type,
	    Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qicon_with_connections;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = Qnil;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qnil;
    Qicon_without_connections = STATIC_SYMBOL("ICON-WITHOUT-CONNECTIONS",
	    AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qicon_without_connections,ws_rep_type,
	    Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qicon_without_connections;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = Qnil;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qnil;
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qloose_end,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qloose_end;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = Qnil;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qnil;
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qstyle = STATIC_SYMBOL("STYLE",AB_package);
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    list_constant = STATIC_LIST((SI_Long)5L,Qab_structure,Qstyle,Qsymbol,
	    Qstub_length,Qinteger);
    Qconnection_property_getter = 
	    STATIC_SYMBOL("CONNECTION-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qconnection,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qconnection;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qconnection_property_getter;
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    Qtext_lines = STATIC_SYMBOL("TEXT-LINES",AB_package);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qab_structure,Qtext_lines,
	    Qsequence,Qtext_box_format,Qab_structure);
    Qtext_box_property_getter = STATIC_SYMBOL("TEXT-BOX-PROPERTY-GETTER",
	    AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qtext_box,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qtext_box;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_1;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtext_box_property_getter;
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    Qrow_label = STATIC_SYMBOL("ROW-LABEL",AB_package);
    Qrow_info = STATIC_SYMBOL("ROW-INFO",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qrow_label,Qrow_info);
    list_constant_3 = STATIC_CONS(list_constant_2,Qnil);
    Qtable_property_getter = STATIC_SYMBOL("TABLE-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qreadout_table,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qreadout_table;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_3;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtable_property_getter;
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    Qlow_value = STATIC_SYMBOL("LOW-VALUE",AB_package);
    Qhigh_value = STATIC_SYMBOL("HIGH-VALUE",AB_package);
    Qincrement = STATIC_SYMBOL("INCREMENT",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qlow_value,Qhigh_value,
	    Qincrement);
    Qdial_property_getter = STATIC_SYMBOL("DIAL-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qdial,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qdial;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_4;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qdial_property_getter;
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    Qmeter_property_getter = STATIC_SYMBOL("METER-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qmeter,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qmeter;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_4;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qmeter_property_getter;
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qtrend_chart_property_spec = STATIC_SYMBOL("TREND-CHART-PROPERTY-SPEC",
	    AB_package);
    Qtrend_chart_property_getter = 
	    STATIC_SYMBOL("TREND-CHART-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qtrend_chart,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qtrend_chart;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = T;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = Qtrend_chart_property_spec;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtrend_chart_property_getter;
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qgraph,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qgraph;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = Qnil;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qnil;
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    Qchart_property_spec = STATIC_SYMBOL("CHART-PROPERTY-SPEC",AB_package);
    Qchart_property_getter = STATIC_SYMBOL("CHART-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qchart,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qchart;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = Qchart_property_spec;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qchart_property_getter;
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    list_constant_5 = STATIC_CONS(list_constant_2,list_constant_3);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qfreeform_table,ws_rep_type,
	    Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qfreeform_table;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_5;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtable_property_getter;
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    Qlabel = STATIC_SYMBOL("LABEL",AB_package);
    Qbutton_state = STATIC_SYMBOL("BUTTON-STATE",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qlabel,Qbutton_state);
    Qaction_button_property_getter = 
	    STATIC_SYMBOL("ACTION-BUTTON-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qaction_button,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qaction_button;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_6;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qaction_button_property_getter;
    Qradio_button = STATIC_SYMBOL("RADIO-BUTTON",AB_package);
    Qradio_button_property_getter = 
	    STATIC_SYMBOL("RADIO-BUTTON-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qradio_button,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qradio_button;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_6;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qradio_button_property_getter;
    Qcheck_box = STATIC_SYMBOL("CHECK-BOX",AB_package);
    Qcheck_box_property_getter = STATIC_SYMBOL("CHECK-BOX-PROPERTY-GETTER",
	    AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qcheck_box,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qcheck_box;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_6;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qcheck_box_property_getter;
    Qslider = STATIC_SYMBOL("SLIDER",AB_package);
    Qreadout_value = STATIC_SYMBOL("READOUT-VALUE",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)4L,Qlabel,Qreadout_value,Qmin,Qmax);
    Qslider_property_getter = STATIC_SYMBOL("SLIDER-PROPERTY-GETTER",
	    AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qslider,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qslider;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_7;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qslider_property_getter;
    Qtype_in_box = STATIC_SYMBOL("TYPE-IN-BOX",AB_package);
    Qlast_value_displayed = STATIC_SYMBOL("LAST-VALUE-DISPLAYED",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qlabel,Qlast_value_displayed);
    Qtype_in_box_property_getter = 
	    STATIC_SYMBOL("TYPE-IN-BOX-PROPERTY-GETTER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qtype_in_box,ws_rep_type,Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qtype_in_box;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_8;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtype_in_box_property_getter;
    Qattribute_display = STATIC_SYMBOL("ATTRIBUTE-DISPLAY",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qattribute_display,ws_rep_type,
	    Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qattribute_display;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_5;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtable_property_getter;
    Qattribute_table = STATIC_SYMBOL("ATTRIBUTE-TABLE",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qattribute_table,ws_rep_type,
	    Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qattribute_table;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_5;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtable_property_getter;
    Qshort_representation = STATIC_SYMBOL("SHORT-REPRESENTATION",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qshort_representation,ws_rep_type,
	    Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qshort_representation;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_5;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtable_property_getter;
    Qclassic_attribute_table = STATIC_SYMBOL("CLASSIC-ATTRIBUTE-TABLE",
	    AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qclassic_attribute_table,ws_rep_type,
	    Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qclassic_attribute_table;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_5;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtable_property_getter;
    Qattribute_table_with_header = 
	    STATIC_SYMBOL("ATTRIBUTE-TABLE-WITH-HEADER",AB_package);
    ws_rep_type = make_ws_representation_type_1();
    mutate_global_property(Qattribute_table_with_header,ws_rep_type,
	    Qws_representation_type);
    SVREF(ws_rep_type,FIX((SI_Long)1L)) = Qattribute_table_with_header;
    SVREF(ws_rep_type,FIX((SI_Long)2L)) = Nil;
    SVREF(ws_rep_type,FIX((SI_Long)3L)) = list_constant_5;
    SVREF(ws_rep_type,FIX((SI_Long)4L)) = Qtable_property_getter;
}
