/* sax.c
 * Input file:  sax.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "sax.h"


/* C-XML-FILL-ELEMENT-NAME-BUFFER */
Object c_xml_fill_element_name_buffer(callback_data_index,buffer,length_1,
	    start)
    Object callback_data_index, buffer, length_1, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(189,0);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2xml_fill_element_name_buffer(IFIX(callback_data_index),
	    ISTRING(temp),IFIX(length_1),IFIX(start)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-XML-FILL-START-ELEMENT-ATT-BUFFER */
Object c_xml_fill_start_element_att_buffer(callback_data_index,buffer,
	    length_1,att_num)
    Object callback_data_index, buffer, length_1, att_num;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(189,1);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2xml_fill_start_element_att_buffer(IFIX(callback_data_index),
	    ISTRING(temp),IFIX(length_1),IFIX(att_num));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* C-XML-FILL-CHARACTERS-OR-COMMENT-BUFFER */
Object c_xml_fill_characters_or_comment_buffer(callback_data_index,buffer,
	    length_1,start)
    Object callback_data_index, buffer, length_1, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(189,2);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = 
	    FIX(g2xml_fill_characters_or_comment_buffer(IFIX(callback_data_index),
	    ISTRING(temp),IFIX(length_1),IFIX(start)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-XML-FILL-ERROR-BUFFER */
Object c_xml_fill_error_buffer(callback_data_index,buffer,length_1)
    Object callback_data_index, buffer, length_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(189,3);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2xml_fill_error_buffer(IFIX(callback_data_index),
	    ISTRING(temp),IFIX(length_1)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-XML-PARSE-CHUNK */
Object c_xml_parse_chunk(sax_parser_index,buffer,size,terminate)
    Object sax_parser_index, buffer, size, terminate;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(189,4);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2xml_parse_chunk(IFIX(sax_parser_index),ISTRING(temp),
	    IFIX(size),IFIX(terminate)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-XML-PARSE-FILE */
Object c_xml_parse_file(sax_parser_index,path)
    Object sax_parser_index, path;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(189,5);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(path);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = path;
    temp = FIX(g2xml_parse_file(IFIX(sax_parser_index),ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* LISP-XML-SIZE-START-ELEMENT-ATT */
Object lisp_xml_size_start_element_att(callback_data,att_num)
    Object callback_data, att_num;
{
    x_note_fn_call(189,6);
    return VALUES_1(FIX(g2xml_start_element_att_size(IFIX(callback_data),
	    IFIX(att_num))));
}

/* LISP-XML-SIZE-ELEMENT-NAME */
Object lisp_xml_size_element_name(callback_data,ignorable)
    Object callback_data, ignorable;
{
    x_note_fn_call(189,7);
    return VALUES_1(FIX(g2xml_element_name_size(IFIX(callback_data))));
}

/* LISP-XML-SIZE-CHARACTERS-OR-COMMENT */
Object lisp_xml_size_characters_or_comment(callback_data,ignorable)
    Object callback_data, ignorable;
{
    x_note_fn_call(189,8);
    return VALUES_1(FIX(g2xml_characters_or_comment_size(IFIX(callback_data))));
}

/* LISP-XML-SIZE-WARNING-OR-ERROR */
Object lisp_xml_size_warning_or_error(callback_data,ignorable)
    Object callback_data, ignorable;
{
    x_note_fn_call(189,9);
    return VALUES_1(FIX(g2xml_error_size(IFIX(callback_data))));
}

/* LISP-XML-FILL-START-ELEMENT-ATT-BUFFER */
Object lisp_xml_fill_start_element_att_buffer(callback_data,buffer,
	    length_1,att_num)
    Object callback_data, buffer, length_1, att_num;
{
    x_note_fn_call(189,10);
    return c_xml_fill_start_element_att_buffer(callback_data,buffer,
	    length_1,att_num);
}

/* LISP-XML-FILL-ELEMENT-NAME-BUFFER */
Object lisp_xml_fill_element_name_buffer(callback_data,buffer,length_1,
	    ignorable)
    Object callback_data, buffer, length_1, ignorable;
{
    x_note_fn_call(189,11);
    return c_xml_fill_element_name_buffer(callback_data,buffer,length_1,
	    FIX((SI_Long)0L));
}

/* LISP-XML-FILL-CHARACTERS-OR-COMMENT-BUFFER */
Object lisp_xml_fill_characters_or_comment_buffer(callback_data,buffer,
	    length_1,ignorable)
    Object callback_data, buffer, length_1, ignorable;
{
    x_note_fn_call(189,12);
    return c_xml_fill_characters_or_comment_buffer(callback_data,buffer,
	    length_1,FIX((SI_Long)0L));
}

/* LISP-XML-FILL-ERROR-BUFFER */
Object lisp_xml_fill_error_buffer(callback_data,buffer,length_1,ignorable)
    Object callback_data, buffer, length_1, ignorable;
{
    x_note_fn_call(189,13);
    return c_xml_fill_error_buffer(callback_data,buffer,length_1);
}

static Object Qnone;               /* none */

static Object Qstart_document_procedure;  /* start-document-procedure */

static Object Qend_document_procedure;  /* end-document-procedure */

static Object Qstart_element_procedure;  /* start-element-procedure */

static Object Qend_element_procedure;  /* end-element-procedure */

static Object Qcharacters_procedure;  /* characters-procedure */

static Object Qcomment_procedure;  /* comment-procedure */

static Object Qwarning_procedure;  /* warning-procedure */

static Object Qerror_procedure;    /* error-procedure */

static Object Qfatal_error_procedure;  /* fatal-error-procedure */

/* SAX-CALLBACK-TYPE */
Object sax_callback_type(event)
    Object event;
{
    SI_Long callback_type;

    x_note_fn_call(189,14);
    callback_type = g2xml_get_event_callback_type(IFIX(event));
    if ( !((SI_Long)-128L <= callback_type && callback_type <= (SI_Long)127L))
	return VALUES_1(Qnone);
    else
	switch ((char)callback_type) {
	  case 12:
	    return VALUES_1(Qstart_document_procedure);
	  case 13:
	    return VALUES_1(Qend_document_procedure);
	  case 14:
	    return VALUES_1(Qstart_element_procedure);
	  case 15:
	    return VALUES_1(Qend_element_procedure);
	  case 17:
	    return VALUES_1(Qcharacters_procedure);
	  case 20:
	    return VALUES_1(Qcomment_procedure);
	  case 21:
	    return VALUES_1(Qwarning_procedure);
	  case 22:
	    return VALUES_1(Qerror_procedure);
	  case 23:
	    return VALUES_1(Qfatal_error_procedure);
	  default:
	    return VALUES_1(Qnone);
	}
}

static Object Qparser_context_handle;  /* parser-context-handle */

static Object Qlast_parser_event;  /* last-parser-event */

static Object Qnumber_of_pending_callbacks;  /* number-of-pending-callbacks */

/* RESET-SAX-PARSER */
Object reset_sax_parser(the_parser)
    Object the_parser;
{
    Object parsing_context;

    x_note_fn_call(189,15);
    parsing_context = get_lookup_slot_value_given_default(the_parser,
	    Qparser_context_handle,Nil);
    if (parsing_context)
	g2xml_cleanup_parser(IFIX(parsing_context));
    set_non_savable_lookup_slot_value(the_parser,Qparser_context_handle,Nil);
    set_non_savable_lookup_slot_value(the_parser,Qlast_parser_event,Nil);
    return change_slot_value(3,the_parser,Qnumber_of_pending_callbacks,
	    FIX((SI_Long)0L));
}

static Object Qsax_parser;         /* sax-parser */

/* CLEANUP-FOR-SAX-PARSER */
Object cleanup_for_sax_parser(sax_parser)
    Object sax_parser;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(189,16);
    frame = sax_parser;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qsax_parser)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    return reset_sax_parser(sax_parser);
}

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-SAX-PARSER */
Object deactivate_subclass_of_entity_for_sax_parser(sax_parser)
    Object sax_parser;
{
    x_note_fn_call(189,17);
    return reset_sax_parser(sax_parser);
}

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_length_for_sax_strings, Qmaximum_length_for_sax_strings);

static Object Qutf_8_string;       /* utf-8-string */

/* SAX-FILL-IN-STRING-BUFFER */
Object sax_fill_in_string_buffer(size_function,fill_in_function,
	    callback_data,attribute_number_qm)
    Object size_function, fill_in_function, callback_data, attribute_number_qm;
{
    Object true_size_required, size_to_use, string_buffer, wide_string_value;
    Object translated_string, temp, temp_1;

    x_note_fn_call(189,18);
    true_size_required = FUNCALL_2(size_function,callback_data,
	    attribute_number_qm);
    size_to_use = FIXNUM_MIN(true_size_required,
	    Maximum_length_for_sax_strings);
    string_buffer = obtain_simple_gensym_string(size_to_use);
    wide_string_value = Nil;
    FUNCALL_4(fill_in_function,callback_data,string_buffer,size_to_use,
	    attribute_number_qm);
    translated_string = import_text_string(2,string_buffer,Qutf_8_string);
    wide_string_value = copy_as_wide_string(translated_string);
    reclaim_gensym_string_or_wide_string(translated_string);
    reclaim_simple_gensym_string(string_buffer);
    temp = wide_string_value;
    temp_1 = FIXNUM_GT(true_size_required,Maximum_length_for_sax_strings) ?
	     T : Nil;
    return VALUES_2(temp,temp_1);
}

Object Sax_id_callback_type = UNBOUND;

Object Sax_id_element_name = UNBOUND;

Object Sax_id_attributes = UNBOUND;

Object Sax_id_attribute_name = UNBOUND;

Object Sax_id_attribute_value = UNBOUND;

Object Sax_id_comment = UNBOUND;

Object Sax_id_error_message = UNBOUND;

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qab_structure;       /* structure */

/* SAX-START-OR-END-DOCUMENT-DATA */
Object sax_start_or_end_document_data(callback_type)
    Object callback_type;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(189,19);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Sax_id_callback_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Sax_id_callback_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = callback_type;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = callback_type;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qlisp_xml_size_element_name;  /* lisp-xml-size-element-name */

static Object Qlisp_xml_fill_element_name_buffer;  /* lisp-xml-fill-element-name-buffer */

static Object string_constant;     /* "Warning: Sax-parser ~NF read an element name longer than ~
				    *            the maximum allowed length of ~a bytes. ~
				    *            The string beginning ~s will be truncated to the maximum ~
				    *            allowed length."
				    */

/* SAX-GET-ELEMENT-NAME */
Object sax_get_element_name(callback_data,sax_parser)
    Object callback_data, sax_parser;
{
    Object element_name, oversize_element_name_p;
    Object beginning_of_truncated_string;
    Object result;

    x_note_fn_call(189,20);
    result = sax_fill_in_string_buffer(SYMBOL_FUNCTION(Qlisp_xml_size_element_name),
	    SYMBOL_FUNCTION(Qlisp_xml_fill_element_name_buffer),
	    callback_data,Nil);
    MVS_2(result,element_name,oversize_element_name_p);
    if (oversize_element_name_p) {
	beginning_of_truncated_string = text_string_substring(element_name,
		FIX((SI_Long)0L),FIX((SI_Long)20L));
	notify_user(4,string_constant,sax_parser,
		Maximum_length_for_sax_strings,beginning_of_truncated_string);
	reclaim_text_string(beginning_of_truncated_string);
    }
    return VALUES_1(element_name);
}

static Object Qlisp_xml_size_start_element_att;  /* lisp-xml-size-start-element-att */

static Object Qlisp_xml_fill_start_element_att_buffer;  /* lisp-xml-fill-start-element-att-buffer */

static Object string_constant_1;   /* "Warning: Sax-parser ~NF read an attribute name (number ~NA) ~
				    *            longer than the maximum allowed length of ~a bytes. ~
				    *            The string beginning ~s will be truncated to the maximum ~
				    *            allowed length."
				    */

/* SAX-GET-NEXT-START-ELEMENT-ATTRIBUTE */
Object sax_get_next_start_element_attribute(callback_data,att_num,sax_parser)
    Object callback_data, att_num, sax_parser;
{
    Object attribute_string, oversize_attribute_p;
    Object beginning_of_truncated_string;
    Object result;

    x_note_fn_call(189,21);
    result = sax_fill_in_string_buffer(SYMBOL_FUNCTION(Qlisp_xml_size_start_element_att),
	    SYMBOL_FUNCTION(Qlisp_xml_fill_start_element_att_buffer),
	    callback_data,att_num);
    MVS_2(result,attribute_string,oversize_attribute_p);
    if (oversize_attribute_p) {
	beginning_of_truncated_string = 
		text_string_substring(attribute_string,FIX((SI_Long)0L),
		FIX((SI_Long)20L));
	notify_user(5,string_constant_1,sax_parser,att_num,
		Maximum_length_for_sax_strings,beginning_of_truncated_string);
	reclaim_text_string(beginning_of_truncated_string);
    }
    return VALUES_1(attribute_string);
}

static Object Qstart_element;      /* start-element */

/* SAX-START-ELEMENT-DATA */
Object sax_start_element_data(callback_data,sax_parser)
    Object callback_data, sax_parser;
{
    Object gensymed_symbol, temp_1, item_or_value, x2, temp_3, fill_in_value_p;
    Object j, result_1, gensymed_symbol_2, wide_string_bv16, temp_4;
    Object svref_new_value;
    SI_Long gensymed_symbol_1, temp, num_atts, bv16_length, aref_new_value;
    char temp_2;

    x_note_fn_call(189,22);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,temp) = FIX((SI_Long)1L);
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_1,temp) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Sax_id_callback_type;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)1L)) = Sax_id_callback_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qstart_element;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qstart_element;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_3 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp_1,FIX((SI_Long)2L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Sax_id_element_name;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)3L)) = Sax_id_element_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = sax_get_element_name(callback_data,sax_parser);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = sax_get_element_name(callback_data,sax_parser);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_3 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp_1,FIX((SI_Long)4L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Sax_id_attributes;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)5L)) = Sax_id_attributes;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	num_atts = g2xml_start_element_atts_num(IFIX(callback_data));
	fill_in_value_p = (SI_Long)1L == ((SI_Long)1L & num_atts) ? T : Nil;
	j = FIX(num_atts - (SI_Long)1L);
	result_1 = Qnil;
      next_loop:
	if ( !(IFIX(j) >= (SI_Long)0L))
	    goto end_loop;
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,temp) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,temp) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Sax_id_attribute_name;
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Sax_id_attribute_name;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    sax_get_next_start_element_attribute(callback_data,
		    FIXNUM_SUB1(j),sax_parser);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = 
		    sax_get_next_start_element_attribute(callback_data,
		    FIXNUM_SUB1(j),sax_parser);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = temp_3;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Sax_id_attribute_value;
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Sax_id_attribute_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    if (fill_in_value_p) {
		fill_in_value_p = Nil;
		wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L 
			+ (SI_Long)3L));
		bv16_length = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		temp = bv16_length - (SI_Long)2L;
		aref_new_value = (SI_Long)0L & (SI_Long)65535L;
		UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		temp = bv16_length - (SI_Long)1L;
		aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
		item_or_value = wide_string_bv16;
	    }
	    else
		item_or_value = 
			sax_get_next_start_element_attribute(callback_data,
			j,sax_parser);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    if (fill_in_value_p) {
		fill_in_value_p = Nil;
		wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L 
			+ (SI_Long)3L));
		bv16_length = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		temp = bv16_length - (SI_Long)2L;
		aref_new_value = (SI_Long)0L & (SI_Long)65535L;
		UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		temp = bv16_length - (SI_Long)1L;
		aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
		item_or_value = wide_string_bv16;
	    }
	    else
		item_or_value = 
			sax_get_next_start_element_attribute(callback_data,
			j,sax_parser);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = temp_3;
	}
	result_1 = eval_cons_1(eval_cons_1(gensymed_symbol_2,
		Qab_structure),result_1);
	j = FIX(IFIX(j) - (SI_Long)2L);
	goto next_loop;
      end_loop:
	temp_4 = result_1;
	goto end_1;
	temp_4 = Qnil;
      end_1:;
	item_or_value = allocate_evaluation_sequence(temp_4);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	num_atts = g2xml_start_element_atts_num(IFIX(callback_data));
	fill_in_value_p = (SI_Long)1L == ((SI_Long)1L & num_atts) ? T : Nil;
	j = FIX(num_atts - (SI_Long)1L);
	result_1 = Qnil;
      next_loop_1:
	if ( !(IFIX(j) >= (SI_Long)0L))
	    goto end_loop_1;
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,temp) = FIX((SI_Long)1L);
	}
	else {
	    temp_3 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_3,temp) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Sax_id_attribute_name;
	else {
	    temp_3 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_3,FIX((SI_Long)1L)) = Sax_id_attribute_name;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    sax_get_next_start_element_attribute(callback_data,
		    FIXNUM_SUB1(j),sax_parser);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_3;
	}
	else {
	    temp_3 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = 
		    sax_get_next_start_element_attribute(callback_data,
		    FIXNUM_SUB1(j),sax_parser);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_3,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Sax_id_attribute_value;
	else {
	    temp_3 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_3,FIX((SI_Long)3L)) = Sax_id_attribute_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    if (fill_in_value_p) {
		fill_in_value_p = Nil;
		wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L 
			+ (SI_Long)3L));
		bv16_length = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		temp = bv16_length - (SI_Long)2L;
		aref_new_value = (SI_Long)0L & (SI_Long)65535L;
		UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		temp = bv16_length - (SI_Long)1L;
		aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
		item_or_value = wide_string_bv16;
	    }
	    else
		item_or_value = 
			sax_get_next_start_element_attribute(callback_data,
			j,sax_parser);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp_3;
	}
	else {
	    temp_3 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    if (fill_in_value_p) {
		fill_in_value_p = Nil;
		wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L 
			+ (SI_Long)3L));
		bv16_length = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		temp = bv16_length - (SI_Long)2L;
		aref_new_value = (SI_Long)0L & (SI_Long)65535L;
		UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		temp = bv16_length - (SI_Long)1L;
		aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
		item_or_value = wide_string_bv16;
	    }
	    else
		item_or_value = 
			sax_get_next_start_element_attribute(callback_data,
			j,sax_parser);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_3,FIX((SI_Long)4L)) = svref_new_value;
	}
	result_1 = eval_cons_1(eval_cons_1(gensymed_symbol_2,
		Qab_structure),result_1);
	j = FIX(IFIX(j) - (SI_Long)2L);
	goto next_loop_1;
      end_loop_1:
	temp_4 = result_1;
	goto end_2;
	temp_4 = Qnil;
      end_2:;
	item_or_value = allocate_evaluation_sequence(temp_4);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_3 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp_1,FIX((SI_Long)6L)) = temp_3;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qend_element;        /* end-element */

/* SAX-END-ELEMENT-DATA */
Object sax_end_element_data(callback_data,sax_parser)
    Object callback_data, sax_parser;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(189,23);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Sax_id_callback_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Sax_id_callback_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qend_element;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qend_element;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Sax_id_element_name;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Sax_id_element_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = sax_get_element_name(callback_data,sax_parser);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = sax_get_element_name(callback_data,sax_parser);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qlisp_xml_size_characters_or_comment;  /* lisp-xml-size-characters-or-comment */

static Object Qlisp_xml_fill_characters_or_comment_buffer;  /* lisp-xml-fill-characters-or-comment-buffer */

static Object string_constant_2;   /* "Warning: Sax-parser ~NF truncated ~NA: ~NA" */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* SAX-CHARACTERS-OR-COMMENT-DATA */
Object sax_characters_or_comment_data(callback_data,callback_type,sax_parser)
    Object callback_data, callback_type, sax_parser;
{
    Object text_to_return, oversize_comment_p, gensymed_symbol, temp;
    Object item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Object result;

    x_note_fn_call(189,24);
    result = sax_fill_in_string_buffer(SYMBOL_FUNCTION(Qlisp_xml_size_characters_or_comment),
	    SYMBOL_FUNCTION(Qlisp_xml_fill_characters_or_comment_buffer),
	    callback_data,Nil);
    MVS_2(result,text_to_return,oversize_comment_p);
    if (oversize_comment_p)
	notify_user(4,string_constant_2,sax_parser,EQ(callback_type,
		Sax_id_comment) ? array_constant : array_constant_1,
		text_to_return);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Sax_id_callback_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Sax_id_callback_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = callback_type;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = callback_type;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = EQ(callback_type,Sax_id_comment) ? Sax_id_comment : 
		Sax_id_characters;
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	svref_new_value = EQ(callback_type,Sax_id_comment) ? 
		Sax_id_comment : Sax_id_characters;
	SVREF(temp,FIX((SI_Long)3L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = text_to_return;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = text_to_return;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qlisp_xml_size_warning_or_error;  /* lisp-xml-size-warning-or-error */

static Object Qlisp_xml_fill_error_buffer;  /* lisp-xml-fill-error-buffer */

static Object Qab_warning;         /* warning */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object Qfatal_error;        /* fatal-error */

static Object array_constant_4;    /* # */

static Object string_constant_3;   /* "Warning: Sax-parser ~NF truncated the ~NA being reported: ~NA" */

/* SAX-WARNING-OR-ERROR-DATA */
Object sax_warning_or_error_data(callback_data,callback_type,sax_parser)
    Object callback_data, callback_type, sax_parser;
{
    Object text_to_return, oversize_error_message_p, temp, gensymed_symbol;
    Object temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;
    Object result;

    x_note_fn_call(189,25);
    result = sax_fill_in_string_buffer(SYMBOL_FUNCTION(Qlisp_xml_size_warning_or_error),
	    SYMBOL_FUNCTION(Qlisp_xml_fill_error_buffer),callback_data,Nil);
    MVS_2(result,text_to_return,oversize_error_message_p);
    if (oversize_error_message_p) {
	if (EQ(callback_type,Qab_warning))
	    temp = array_constant_2;
	else if (EQ(callback_type,Qerror))
	    temp = array_constant_3;
	else if (EQ(callback_type,Qfatal_error))
	    temp = array_constant_4;
	else
	    temp = Qnil;
	notify_user(4,string_constant_3,sax_parser,temp,text_to_return);
    }
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Sax_id_callback_type;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)1L)) = Sax_id_callback_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = callback_type;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = callback_type;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Sax_id_error_message;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)3L)) = Sax_id_error_message;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = text_to_return;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = text_to_return;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qcharacters;         /* characters */

static Object Qcomment;            /* comment */

static Object Qunsupported;        /* unsupported */

/* GET-SAX-CALLBACK-DATA */
Object get_sax_callback_data(callback_type,callback_data,sax_parser)
    Object callback_type, callback_data, sax_parser;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(189,26);
    if (EQ(callback_type,Qstart_document_procedure) || EQ(callback_type,
	    Qend_document_procedure))
	return sax_start_or_end_document_data(callback_type);
    else if (EQ(callback_type,Qstart_element_procedure))
	return sax_start_element_data(callback_data,sax_parser);
    else if (EQ(callback_type,Qend_element_procedure))
	return sax_end_element_data(callback_data,sax_parser);
    else if (EQ(callback_type,Qcharacters_procedure))
	return sax_characters_or_comment_data(callback_data,Qcharacters,
		sax_parser);
    else if (EQ(callback_type,Qcomment_procedure))
	return sax_characters_or_comment_data(callback_data,Qcomment,
		sax_parser);
    else if (EQ(callback_type,Qwarning_procedure))
	return sax_warning_or_error_data(callback_data,Qab_warning,sax_parser);
    else if (EQ(callback_type,Qerror_procedure))
	return sax_warning_or_error_data(callback_data,Qerror,sax_parser);
    else if (EQ(callback_type,Qfatal_error_procedure))
	return sax_warning_or_error_data(callback_data,Qfatal_error,
		sax_parser);
    else {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Sax_id_callback_type;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Sax_id_callback_type;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qunsupported;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qunsupported;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	return eval_cons_1(gensymed_symbol,Qab_structure);
    }
}

/* G2-SAX-EVENTS-READY */
Object g2_sax_events_ready(sax_parser_as_evaluation_value)
    Object sax_parser_as_evaluation_value;
{
    Object sax_parser, value_1, parser_context;
    SI_Long number_of_events;

    x_note_fn_call(189,27);
    sax_parser = IDENTITY(sax_parser_as_evaluation_value);
    value_1 = Nil;
    parser_context = get_lookup_slot_value_given_default(sax_parser,
	    Qparser_context_handle,Nil);
    number_of_events =  !TRUEP(parser_context) ? (SI_Long)0L : 
	    g2xml_events_ready(IFIX(parser_context));
    change_slot_value(3,sax_parser,Qnumber_of_pending_callbacks,
	    FIX(number_of_events));
    value_1 = FIX(number_of_events);
    IDENTITY(sax_parser_as_evaluation_value);
    return VALUES_1(value_1);
}

/* G2-SAX-PARSE-FILE */
Object g2_sax_parse_file(sax_parser_as_evaluation_value,
	    path_as_evaluation_value)
    Object sax_parser_as_evaluation_value, path_as_evaluation_value;
{
    Object sax_parser, path, value_1, parser_context;

    x_note_fn_call(189,28);
    sax_parser = IDENTITY(sax_parser_as_evaluation_value);
    path = path_as_evaluation_value;
    value_1 = Nil;
    parser_context = get_lookup_slot_value_given_default(sax_parser,
	    Qparser_context_handle,Nil);
    if ( !TRUEP(parser_context)) {
	parser_context = LONG_TO_FIXNUM(g2xml_make_parser_context());
	set_non_savable_lookup_slot_value(sax_parser,Qlast_parser_event,Nil);
	set_non_savable_lookup_slot_value(sax_parser,
		Qparser_context_handle,parser_context);
    }
    c_xml_parse_file(parser_context,path);
    value_1 = g2_sax_events_ready(sax_parser);
    IDENTITY(sax_parser_as_evaluation_value);
    reclaim_text_string(path_as_evaluation_value);
    return VALUES_1(value_1);
}

/* G2-SAX-PARSE-CHUNK-INTERNAL */
Object g2_sax_parse_chunk_internal(sax_parser,text_chunk,length_1)
    Object sax_parser, text_chunk, length_1;
{
    Object parser_context, checked_encoding_this_call, wide_string;
    Object wide_string_bv16, result_1, gensymed_symbol, gensymed_symbol_2;
    Object encoding_piece, length_of_rest, rest_of_chunk;
    SI_Long part_length, bv16_length, aref_arg_2, aref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(189,29);
    parser_context = get_lookup_slot_value_given_default(sax_parser,
	    Qparser_context_handle,Nil);
    checked_encoding_this_call = Nil;
    if ( !TRUEP(parser_context)) {
	parser_context = LONG_TO_FIXNUM(g2xml_make_parser_context());
	set_non_savable_lookup_slot_value(sax_parser,Qlast_parser_event,Nil);
	set_non_savable_lookup_slot_value(sax_parser,
		Qparser_context_handle,parser_context);
	if (FIXNUM_GE(length_1,Xml_encoding_length)) {
	    wide_string = text_chunk;
	    part_length = IFIX(Xml_encoding_length) - (SI_Long)0L;
	    wide_string_bv16 = allocate_byte_vector_16(FIX(part_length + 
		    (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = part_length & (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | part_length >>  -  - 
		    (SI_Long)16L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,part_length,(SI_Long)0L);
	    result_1 = wide_string_bv16;
	    gensymed_symbol = wide_string;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = result_1;
	    gensymed_symbol_3 = (SI_Long)0L;
	    gensymed_symbol_4 = part_length;
	    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		    gensymed_symbol_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		    gensymed_symbol_3,gensymed_symbol_4);
	    encoding_piece = result_1;
	    c_xml_parse_chunk(parser_context,encoding_piece,
		    Xml_encoding_length,FIX((SI_Long)0L));
	    checked_encoding_this_call = T;
	    reclaim_wide_string(encoding_piece);
	}
    }
    if (checked_encoding_this_call) {
	length_of_rest = FIXNUM_MINUS(length_1,Xml_encoding_length);
	wide_string = text_chunk;
	part_length = IFIX(FIXNUM_MINUS(length_1,Xml_encoding_length));
	wide_string_bv16 = allocate_byte_vector_16(FIX(part_length + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = part_length & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | part_length >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,part_length,(SI_Long)0L);
	result_1 = wide_string_bv16;
	gensymed_symbol = wide_string;
	gensymed_symbol_1 = IFIX(Xml_encoding_length);
	gensymed_symbol_2 = result_1;
	gensymed_symbol_3 = (SI_Long)0L;
	gensymed_symbol_4 = part_length;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
	rest_of_chunk = result_1;
	c_xml_parse_chunk(parser_context,rest_of_chunk,length_of_rest,
		FIX((SI_Long)0L));
	reclaim_wide_string(rest_of_chunk);
    }
    else
	c_xml_parse_chunk(parser_context,text_chunk,length_1,FIX((SI_Long)0L));
    return VALUES_1(Nil);
}

static Object Qg2_sax_parse_chunk;  /* g2-sax-parse-chunk */

/* G2-SAX-PARSE-CHUNK */
Object g2_sax_parse_chunk(sax_parser_as_evaluation_value,
	    input_text_as_evaluation_value,start_index_as_evaluation_value,
	    end_index_as_evaluation_value)
    Object sax_parser_as_evaluation_value, input_text_as_evaluation_value;
    Object start_index_as_evaluation_value, end_index_as_evaluation_value;
{
    Object sax_parser, input_text, start_index, end_index, g2_text_start_index;
    Object g2_text_end_index, chunk_to_parse, text_length;
    Object result;

    x_note_fn_call(189,30);
    sax_parser = IDENTITY(sax_parser_as_evaluation_value);
    input_text = input_text_as_evaluation_value;
    start_index = start_index_as_evaluation_value;
    end_index = end_index_as_evaluation_value;
    result = convert_user_g2_text_indices_to_internal_indices(input_text,
	    start_index,end_index);
    MVS_2(result,g2_text_start_index,g2_text_end_index);
    if ( !TRUEP(g2_text_start_index))
	report_text_indices_error(input_text,start_index,end_index,
		Qg2_sax_parse_chunk);
    else {
	chunk_to_parse = export_text_string(4,input_text,Qutf_8_string,
		g2_text_start_index,g2_text_end_index);
	text_length = STRINGP(chunk_to_parse) ? 
		gensym_string_length(chunk_to_parse) : 
		text_string_length(chunk_to_parse);
	g2_sax_parse_chunk_internal(sax_parser,chunk_to_parse,text_length);
	reclaim_gensym_string_or_wide_string(chunk_to_parse);
    }
    IDENTITY(sax_parser_as_evaluation_value);
    reclaim_text_string(input_text_as_evaluation_value);
    return VALUES_0();
}

static Object string_constant_4;   /* "Attempted to execute the next SAX callback on ~NF, but it ~
				    *                   has no callbacks pending."
				    */

/* G2-SAX-NEXT-CALLBACK-TYPE */
Object g2_sax_next_callback_type(sax_parser_as_evaluation_value)
    Object sax_parser_as_evaluation_value;
{
    Object sax_parser, value_1, value_2, top_of_stack, message_1;
    Object parser_context, next_event, type, temp;
    Object result;

    x_note_fn_call(189,31);
    sax_parser = IDENTITY(sax_parser_as_evaluation_value);
    value_1 = Nil;
    value_2 = Nil;
    if ( !(IFIX(get_lookup_slot_value_given_default(sax_parser,
	    Qnumber_of_pending_callbacks,FIX((SI_Long)0L))) > (SI_Long)0L)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_4,
		sax_parser);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    parser_context = get_lookup_slot_value_given_default(sax_parser,
	    Qparser_context_handle,Nil);
    next_event = Nil;
    if ( !TRUEP(parser_context))
	result = VALUES_2(Qnone,Qnone);
    else {
	next_event = 
		LONG_TO_FIXNUM(g2xml_first_sax_event(IFIX(parser_context)));
	set_non_savable_lookup_slot_value(sax_parser,Qlast_parser_event,
		next_event);
	type = sax_callback_type(next_event);
	temp = get_slot_value_if_any_function(sax_parser,type,Nil);
	if (temp);
	else
	    temp = Qnone;
	result = VALUES_2(type,temp);
    }
    MVS_2(result,value_1,value_2);
    IDENTITY(sax_parser_as_evaluation_value);
    return VALUES_2(value_1,value_2);
}

/* G2-SAX-CALLBACK-DATA */
Object g2_sax_callback_data(sax_parser_as_evaluation_value,
	    callback_type_as_evaluation_value)
    Object sax_parser_as_evaluation_value, callback_type_as_evaluation_value;
{
    Object sax_parser, callback_type, value_1, last_event;
    Object callback_data_handle, real_callback_data, temp;

    x_note_fn_call(189,32);
    sax_parser = IDENTITY(sax_parser_as_evaluation_value);
    callback_type = callback_type_as_evaluation_value;
    value_1 = Nil;
    last_event = get_lookup_slot_value_given_default(sax_parser,
	    Qlast_parser_event,Nil);
    callback_data_handle = Nil;
    real_callback_data = Nil;
    callback_data_handle = 
	    LONG_TO_FIXNUM(g2xml_get_event_callback_data(IFIX(last_event)));
    real_callback_data = get_sax_callback_data(callback_type,
	    callback_data_handle,sax_parser);
    g2xml_dispose_event_callback_data(IFIX(callback_data_handle));
    value_1 = real_callback_data;
    IDENTITY(sax_parser_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* G2-EXECUTED-SAX-CALLBACK */
Object g2_executed_sax_callback(sax_parser_as_evaluation_value)
    Object sax_parser_as_evaluation_value;
{
    Object sax_parser, last_event;

    x_note_fn_call(189,33);
    sax_parser = IDENTITY(sax_parser_as_evaluation_value);
    last_event = get_lookup_slot_value_given_default(sax_parser,
	    Qlast_parser_event,Nil);
    if (last_event) {
	g2xml_dispose_event(IFIX(last_event));
	set_non_savable_lookup_slot_value(sax_parser,Qlast_parser_event,Nil);
    }
    if (IFIX(get_lookup_slot_value_given_default(sax_parser,
	    Qnumber_of_pending_callbacks,FIX((SI_Long)0L))) > (SI_Long)0L)
	change_slot_value(3,sax_parser,Qnumber_of_pending_callbacks,
		FIXNUM_SUB1(get_lookup_slot_value_given_default(sax_parser,
		Qnumber_of_pending_callbacks,FIX((SI_Long)0L))));
    IDENTITY(sax_parser_as_evaluation_value);
    return VALUES_0();
}

/* G2-RESET-SAX-PARSER */
Object g2_reset_sax_parser(sax_parser_as_evaluation_value)
    Object sax_parser_as_evaluation_value;
{
    Object sax_parser;

    x_note_fn_call(189,34);
    sax_parser = IDENTITY(sax_parser_as_evaluation_value);
    reset_sax_parser(sax_parser);
    IDENTITY(sax_parser_as_evaluation_value);
    return VALUES_0();
}

/* G2-FINISH-SAX-PARSING */
Object g2_finish_sax_parsing(sax_parser_as_evaluation_value)
    Object sax_parser_as_evaluation_value;
{
    Object sax_parser, parser_context, wide_string_bv16, empty_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(189,35);
    sax_parser = IDENTITY(sax_parser_as_evaluation_value);
    parser_context = get_lookup_slot_value_given_default(sax_parser,
	    Qparser_context_handle,Nil);
    if ( !TRUEP(parser_context));
    else {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)0L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
	empty_string = wide_string_bv16;
	c_xml_parse_chunk(parser_context,empty_string,FIX((SI_Long)0L),
		FIX((SI_Long)1L));
	reclaim_wide_string(empty_string);
    }
    IDENTITY(sax_parser_as_evaluation_value);
    return VALUES_0();
}

void sax_INIT()
{
    Object temp, temp_1, temp_2, gensymed_symbol;
    Object Qg2_finish_sax_parsing;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qg2_reset_sax_parser, Qg2_executed_sax_callback;
    Object Qg2_sax_callback_data, Qg2_sax_next_callback_type;
    Object Qg2_sax_parse_file, Qg2_sax_events_ready, list_constant_1;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qerror_message;
    Object Qsax_id_error_message, Qsax_id_characters, Qsax_id_comment;
    Object Qattribute_value, Qsax_id_attribute_value, Qattribute_name;
    Object Qsax_id_attribute_name, Qattributes, Qsax_id_attributes;
    Object Qelement_name, Qsax_id_element_name, Qcallback_type;
    Object Qsax_id_callback_type, Qclasses_which_define;
    Object Qdeactivate_subclass_of_entity;
    Object Qdeactivate_subclass_of_entity_for_sax_parser, Qcleanup;
    Object Qcleanup_for_sax_parser, string_constant_29, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, list_constant, Qcreate_icon_description;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5, Qobject;

    x_note_fn_call(189,36);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qstart_document_procedure = STATIC_SYMBOL("START-DOCUMENT-PROCEDURE",
	    AB_package);
    Qend_document_procedure = STATIC_SYMBOL("END-DOCUMENT-PROCEDURE",
	    AB_package);
    Qstart_element_procedure = STATIC_SYMBOL("START-ELEMENT-PROCEDURE",
	    AB_package);
    Qend_element_procedure = STATIC_SYMBOL("END-ELEMENT-PROCEDURE",AB_package);
    Qcharacters_procedure = STATIC_SYMBOL("CHARACTERS-PROCEDURE",AB_package);
    Qcomment_procedure = STATIC_SYMBOL("COMMENT-PROCEDURE",AB_package);
    Qwarning_procedure = STATIC_SYMBOL("WARNING-PROCEDURE",AB_package);
    Qerror_procedure = STATIC_SYMBOL("ERROR-PROCEDURE",AB_package);
    Qfatal_error_procedure = STATIC_SYMBOL("FATAL-ERROR-PROCEDURE",AB_package);
    Qsax_parser = STATIC_SYMBOL("SAX-PARSER",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qsax_parser,list_constant);
    string_constant_5 = 
	    STATIC_STRING("1m1m8v839uy1m83-Cy53dySAX parsers provide an interface to libxml2");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_6 = 
	    STATIC_STRING("1z4z8r83--y83--y839uy839uy00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_7 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_8 = 
	    STATIC_STRING("0004z8r83-0y83-0y839uy839uy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_9 = 
	    STATIC_STRING("ion is available at this time)000004z8r8u8u839uy839uy01v8w9k3ky3ky13Gy1q83-1y2l83*Ny83Ty2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l83");
    string_constant_10 = 
	    STATIC_STRING("*Uy83Ty1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1");
    string_constant_11 = 
	    STATIC_STRING("mkk1m3hyn1mnn1n1mnn1mk3ky1mkk1o83Oy1mp3fy1m3ey3fy1m3eyp83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3");
    string_constant_12 = 
	    STATIC_STRING("ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp");
    string_constant_13 = 
	    STATIC_STRING("1mp3fy83*Uy1o83Gy+s3-Kykkkkkl3A++y1m3Qy3dy83=Ay83*Uy1o83Gy+s3--ykkkkkl3A++y1m3Ey3Sy83=Ay83*Uy1o83Gy+s3-Fykkkkkl3A++y1ms3Hy83=Ay0");
    string_constant_14 = 
	    STATIC_STRING("00001q1p83*Ny3Ny3My3dy3cy1p83-Lykk3ky3ky1p83-nykk3ky3ky1p83-mykk3ky3ky1p83*Nykk3ky3ky1p83*Uysq3Gy3My001o1l8l1l8o1l8z1m83Dy53YySe");
    string_constant_15 = 
	    STATIC_STRING("e comment on ENTITY class definition000004z8r83Xey83Xey839uy839uy00001n1l83Hy1l83Uy1l8l000004z8r83Tey83Tey839uy839uy00001n1l83Hy");
    string_constant_16 = 
	    STATIC_STRING("1l83Uy1l8l000004z8r83Wry83Wry839uy839uy0k001p1m8p83Sy1l83Hy1l83Uy1l8l1l83Fy000004z8r83ary83ary839uy839uy00001n1m8p8306y1l8o1l8l0");
    string_constant_17 = 
	    STATIC_STRING("00004z8r83KXy83KXy839uy839uy00001n1m8p8306y1l8o1l8l000004z8r83asy83asy839uy839uy00001n1m8p8306y1l8o1l8l000004z8r83KYy83KYy839uy8");
    string_constant_18 = 
	    STATIC_STRING("39uy00001n1m8p8306y1l8o1l8l000004z8r83Hry83Hry839uy839uy00001n1m8p8306y1l8o1l8l000004z8r83IMy83IMy839uy839uy00001n1m8p8306y1l8o1");
    string_constant_19 = 
	    STATIC_STRING("l8l000004z8r83e3y83e3y839uy839uy00001n1m8p8306y1l8o1l8l000004z8r83Kfy83Kfy839uy839uy00001n1m8p8306y1l8o1l8l000004z8r83LBy83LBy83");
    string_constant_20 = STATIC_STRING("9uy839uy00001n1m8p8306y1l8o1l8l00000");
    string_constant_21 = 
	    STATIC_STRING("13Dy8q1o839uy1l83-Oy1m8v839uy1m83-Cy53dySAX parsers provide an interface to libxml21n83--y01m8p83-*y1n83-0y01m8p83-0y1m8u1v8w9k3");
    string_constant_22 = 
	    STATIC_STRING("ky3ky13Gy1q83-1y2l83*Ny83Ty2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l83*Uy83Ty1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk");
    string_constant_23 = 
	    STATIC_STRING("1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk1o83Oy1mp3fy1m3ey3fy1m3eyp83-my1");
    string_constant_24 = 
	    STATIC_STRING("q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn");
    string_constant_25 = 
	    STATIC_STRING("3hy1m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp1mp3fy83*Uy1o83Gy+s3-Kykkkkkl3A++y1m3Qy3dy83=Ay83*Uy1o83Gy+s3");
    string_constant_26 = 
	    STATIC_STRING("--ykkkkkl3A++y1m3Ey3Sy83=Ay83*Uy1o83Gy+s3-Fykkkkkl3A++y1ms3Hy83=Ay000001q1p83*Ny3Ny3My3dy3cy1p83-Lykk3ky3ky1p83-nykk3ky3ky1p83-m");
    string_constant_27 = 
	    STATIC_STRING("ykk3ky3ky1p83*Nykk3ky3ky1p83*Uysq3Gy3My1p83Xey083Hy83Uy8l1p83Tey083Hy83Uy8l1r83Wryk1m8p83Sy83Hy83Uy8l83Fy1p83ary01m8p8306y8o8l1p");
    string_constant_28 = 
	    STATIC_STRING("83KXy01m8p8306y8o8l1p83asy01m8p8306y8o8l1p83KYy01m8p8306y8o8l1p83Hry01m8p8306y8o8l1p83IMy01m8p8306y8o8l1p83e3y01m8p8306y8o8l1p83");
    string_constant_29 = 
	    STATIC_STRING("Kfy01m8p8306y8o8l1p83LBy01m8p8306y8o8l");
    temp = regenerate_optimized_constant(string_constant_5);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(15,string_constant_6,
	    string_constant_7,string_constant_8,string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qsax_parser,list_constant,Nil,temp,Nil,
	    temp_1,list_constant,regenerate_optimized_constant(list(9,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24,string_constant_25,string_constant_26,
	    string_constant_27,string_constant_28,string_constant_29)),Nil);
    Qparser_context_handle = STATIC_SYMBOL("PARSER-CONTEXT-HANDLE",AB_package);
    Qlast_parser_event = STATIC_SYMBOL("LAST-PARSER-EVENT",AB_package);
    Qnumber_of_pending_callbacks = 
	    STATIC_SYMBOL("NUMBER-OF-PENDING-CALLBACKS",AB_package);
    Qcleanup_for_sax_parser = STATIC_SYMBOL("CLEANUP-FOR-SAX-PARSER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_sax_parser,
	    STATIC_FUNCTION(cleanup_for_sax_parser,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_sax_parser);
    set_get(Qsax_parser,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qsax_parser,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qdeactivate_subclass_of_entity_for_sax_parser = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-SAX-PARSER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_sax_parser,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_sax_parser,
	    NIL,FALSE,1,1));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_sax_parser);
    set_get(Qsax_parser,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qsax_parser,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    if (Maximum_length_for_sax_strings == UNBOUND)
	Maximum_length_for_sax_strings = Maximum_length_for_user_text_strings;
    Qutf_8_string = STATIC_SYMBOL("UTF-8-STRING",AB_package);
    Qsax_id_callback_type = STATIC_SYMBOL("SAX-ID-CALLBACK-TYPE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsax_id_callback_type,Sax_id_callback_type);
    Qcallback_type = STATIC_SYMBOL("CALLBACK-TYPE",AB_package);
    SET_SYMBOL_VALUE(Qsax_id_callback_type,Qcallback_type);
    Qsax_id_element_name = STATIC_SYMBOL("SAX-ID-ELEMENT-NAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsax_id_element_name,Sax_id_element_name);
    Qelement_name = STATIC_SYMBOL("ELEMENT-NAME",AB_package);
    SET_SYMBOL_VALUE(Qsax_id_element_name,Qelement_name);
    Qsax_id_attributes = STATIC_SYMBOL("SAX-ID-ATTRIBUTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsax_id_attributes,Sax_id_attributes);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    SET_SYMBOL_VALUE(Qsax_id_attributes,Qattributes);
    Qsax_id_attribute_name = STATIC_SYMBOL("SAX-ID-ATTRIBUTE-NAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsax_id_attribute_name,Sax_id_attribute_name);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    SET_SYMBOL_VALUE(Qsax_id_attribute_name,Qattribute_name);
    Qsax_id_attribute_value = STATIC_SYMBOL("SAX-ID-ATTRIBUTE-VALUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsax_id_attribute_value,Sax_id_attribute_value);
    Qattribute_value = STATIC_SYMBOL("ATTRIBUTE-VALUE",AB_package);
    SET_SYMBOL_VALUE(Qsax_id_attribute_value,Qattribute_value);
    Qsax_id_comment = STATIC_SYMBOL("SAX-ID-COMMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsax_id_comment,Sax_id_comment);
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    SET_SYMBOL_VALUE(Qsax_id_comment,Qcomment);
    Qsax_id_characters = STATIC_SYMBOL("SAX-ID-CHARACTERS",AB_package);
    SET_SYMBOL_VALUE(Qsax_id_characters,Qstring);
    Qsax_id_error_message = STATIC_SYMBOL("SAX-ID-ERROR-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsax_id_error_message,Sax_id_error_message);
    Qerror_message = STATIC_SYMBOL("ERROR-MESSAGE",AB_package);
    SET_SYMBOL_VALUE(Qsax_id_error_message,Qerror_message);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qlisp_xml_size_element_name = 
	    STATIC_SYMBOL("LISP-XML-SIZE-ELEMENT-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_xml_size_element_name,
	    STATIC_FUNCTION(lisp_xml_size_element_name,NIL,FALSE,2,2));
    Qlisp_xml_fill_element_name_buffer = 
	    STATIC_SYMBOL("LISP-XML-FILL-ELEMENT-NAME-BUFFER",AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_xml_fill_element_name_buffer,
	    STATIC_FUNCTION(lisp_xml_fill_element_name_buffer,NIL,FALSE,4,4));
    string_constant = 
	    string_append2(STATIC_STRING("Warning: Sax-parser ~NF read an element name longer than ~\n           the maximum allowed length of ~a bytes. ~\n           The string beginning ~s will be truncated to the max"),
	    STATIC_STRING("imum ~\n           allowed length."));
    Qlisp_xml_size_start_element_att = 
	    STATIC_SYMBOL("LISP-XML-SIZE-START-ELEMENT-ATT",AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_xml_size_start_element_att,
	    STATIC_FUNCTION(lisp_xml_size_start_element_att,NIL,FALSE,2,2));
    Qlisp_xml_fill_start_element_att_buffer = 
	    STATIC_SYMBOL("LISP-XML-FILL-START-ELEMENT-ATT-BUFFER",AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_xml_fill_start_element_att_buffer,
	    STATIC_FUNCTION(lisp_xml_fill_start_element_att_buffer,NIL,
	    FALSE,4,4));
    string_constant_1 = 
	    string_append2(STATIC_STRING("Warning: Sax-parser ~NF read an attribute name (number ~NA) ~\n           longer than the maximum allowed length of ~a bytes. ~\n           The string beginning ~s will be trunc"),
	    STATIC_STRING("ated to the maximum ~\n           allowed length."));
    Qstart_element = STATIC_SYMBOL("START-ELEMENT",AB_package);
    Qend_element = STATIC_SYMBOL("END-ELEMENT",AB_package);
    Qlisp_xml_size_characters_or_comment = 
	    STATIC_SYMBOL("LISP-XML-SIZE-CHARACTERS-OR-COMMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_xml_size_characters_or_comment,
	    STATIC_FUNCTION(lisp_xml_size_characters_or_comment,NIL,FALSE,
	    2,2));
    Qlisp_xml_fill_characters_or_comment_buffer = 
	    STATIC_SYMBOL("LISP-XML-FILL-CHARACTERS-OR-COMMENT-BUFFER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_xml_fill_characters_or_comment_buffer,
	    STATIC_FUNCTION(lisp_xml_fill_characters_or_comment_buffer,NIL,
	    FALSE,4,4));
    string_constant_2 = 
	    STATIC_STRING("Warning: Sax-parser ~NF truncated ~NA: ~NA");
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qlisp_xml_size_warning_or_error = 
	    STATIC_SYMBOL("LISP-XML-SIZE-WARNING-OR-ERROR",AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_xml_size_warning_or_error,
	    STATIC_FUNCTION(lisp_xml_size_warning_or_error,NIL,FALSE,2,2));
    Qlisp_xml_fill_error_buffer = 
	    STATIC_SYMBOL("LISP-XML-FILL-ERROR-BUFFER",AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_xml_fill_error_buffer,
	    STATIC_FUNCTION(lisp_xml_fill_error_buffer,NIL,FALSE,4,4));
    Qab_warning = STATIC_SYMBOL("WARNING",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qfatal_error = STATIC_SYMBOL("FATAL-ERROR",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    string_constant_3 = 
	    STATIC_STRING("Warning: Sax-parser ~NF truncated the ~NA being reported: ~NA");
    Qcharacters = STATIC_SYMBOL("CHARACTERS",AB_package);
    Qunsupported = STATIC_SYMBOL("UNSUPPORTED",AB_package);
    Qg2_sax_events_ready = STATIC_SYMBOL("G2-SAX-EVENTS-READY",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sax_events_ready,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_sax_events_ready,
	    STATIC_FUNCTION(g2_sax_events_ready,NIL,FALSE,1,1));
    Qg2_sax_parse_file = STATIC_SYMBOL("G2-SAX-PARSE-FILE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_sax_parse_file,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_sax_parse_file,
	    STATIC_FUNCTION(g2_sax_parse_file,NIL,FALSE,2,2));
    Qg2_sax_parse_chunk = STATIC_SYMBOL("G2-SAX-PARSE-CHUNK",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_sax_parse_chunk,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_sax_parse_chunk,
	    STATIC_FUNCTION(g2_sax_parse_chunk,NIL,FALSE,4,4));
    Qg2_sax_next_callback_type = STATIC_SYMBOL("G2-SAX-NEXT-CALLBACK-TYPE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sax_next_callback_type,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_4 = 
	    STATIC_STRING("Attempted to execute the next SAX callback on ~NF, but it ~\n                  has no callbacks pending.");
    SET_SYMBOL_FUNCTION(Qg2_sax_next_callback_type,
	    STATIC_FUNCTION(g2_sax_next_callback_type,NIL,FALSE,1,1));
    Qg2_sax_callback_data = STATIC_SYMBOL("G2-SAX-CALLBACK-DATA",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sax_callback_data,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_sax_callback_data,
	    STATIC_FUNCTION(g2_sax_callback_data,NIL,FALSE,2,2));
    Qg2_executed_sax_callback = STATIC_SYMBOL("G2-EXECUTED-SAX-CALLBACK",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_executed_sax_callback,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_executed_sax_callback,
	    STATIC_FUNCTION(g2_executed_sax_callback,NIL,FALSE,1,1));
    Qg2_reset_sax_parser = STATIC_SYMBOL("G2-RESET-SAX-PARSER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_reset_sax_parser,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_reset_sax_parser,
	    STATIC_FUNCTION(g2_reset_sax_parser,NIL,FALSE,1,1));
    Qg2_finish_sax_parsing = STATIC_SYMBOL("G2-FINISH-SAX-PARSING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_finish_sax_parsing,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_finish_sax_parsing,
	    STATIC_FUNCTION(g2_finish_sax_parsing,NIL,FALSE,1,1));
}
