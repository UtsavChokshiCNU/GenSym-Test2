/* kbsv4.c
 * Input file:  kb-save4.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kbsv4.h"


/* G2-WRITE-XML-OBJECT-TO-FILE */
Object g2_write_xml_object_to_file(xml_object,pathname_1)
    Object xml_object, pathname_1;
{
    x_note_fn_call(136,0);
    return write_xml_object_to_file(xml_object,pathname_1);
}

/* G2-READ-XML-OBJECT-FROM-FILE */
Object g2_read_xml_object_from_file(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(136,1);
    return xml_object_and_fixups_for_file(pathname_1);
}

/* G2-SAVE-MODULE-INTO-XML-OBJECT */
Object g2_save_module_into_xml_object(module)
    Object module;
{
    Object xml_object;

    x_note_fn_call(136,2);
    if ( !TRUEP(module_contains_text_stripped_frames_p(module))) {
	xml_object = xml_object_and_fixups_for_module(module);
	return add_checksums_to_xml_object(xml_object,
		compute_checksums_for_xml_object(xml_object,module));
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_g2_rdf_module, Qcurrent_g2_rdf_module);

static Object Qrestore_xml_kb;     /* restore-xml-kb */

/* G2-RESTORE-MODULE-FROM-XML-OBJECT */
Object g2_restore_module_from_xml_object(xml_object)
    Object xml_object;
{
    Object kb_load_case_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,3);
    Current_g2_rdf_module = module_name_symbol_for_xml_object(xml_object);
    kb_load_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_load_case_qm,Qkb_load_case_qm,kb_load_case_qm,
	    0);
      result = simple_kb_read_1(Nil,Nil,Qrestore_xml_kb,xml_object);
    POP_SPECIAL();
    return result;
}

/* G2-COPY-XML-OBJECT-WITH-ANNOTATIONS */
Object g2_copy_xml_object_with_annotations(xml_object)
    Object xml_object;
{
    x_note_fn_call(136,4);
    return copy_xml_object(xml_object,T);
}

/* G2-COPY-XML-OBJECT-WITHOUT-ANNOTATIONS */
Object g2_copy_xml_object_without_annotations(xml_object)
    Object xml_object;
{
    x_note_fn_call(136,5);
    return copy_xml_object(xml_object,Nil);
}

/* G2-COMPARE-XML-OBJECTS */
Object g2_compare_xml_objects(xml_object_1,xml_object_2,output_pathname)
    Object xml_object_1, xml_object_2, output_pathname;
{
    Object changes;

    x_note_fn_call(136,6);
    changes = compare_xml_object_and_fixups(xml_object_1,xml_object_2,T);
    write_xml_changes_to_file(changes,output_pathname,Nil,Nil);
    return reclaim_xml_change_list(changes);
}

DEFINE_VARIABLE_WITH_SYMBOL(Write_diffs_after_saving_clear_text_p, Qwrite_diffs_after_saving_clear_text_p);

DEFINE_VARIABLE_WITH_SYMBOL(Write_checksums_in_xml_file_p, Qwrite_checksums_in_xml_file_p);

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* WRITE-CLEAR-TEXT-KB */
Object write_clear_text_kb()
{
    Object module, binary_file, xml_object, temp, svref_arg_1;

    x_note_fn_call(136,7);
    if ( !TRUEP(Write_diffs_after_saving_clear_text_p)) {
	if (get_command_line_flag_argument(1,array_constant))
	    Write_diffs_after_saving_clear_text_p = T;
    }
    write_rdf_schema_for_module();
    module = ISVREF(Current_kb_save,(SI_Long)37L);
    binary_file = gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    Nil,array_constant_1,Nil,ISVREF(Current_kb_save,(SI_Long)5L));
    if (Write_diffs_after_saving_clear_text_p || 
		Write_checksums_in_xml_file_p) {
	xml_object = xml_object_and_fixups_for_module(module);
	if (Write_checksums_in_xml_file_p) {
	    temp = xml_object;
	    xml_object = add_checksums_to_xml_object(temp,
		    compute_checksums_for_xml_object(xml_object,module));
	}
	svref_arg_1 = Current_kb_save;
	SVREF(svref_arg_1,FIX((SI_Long)47L)) = xml_object;
	write_clear_text_from_xml_object(binary_file,xml_object);
    }
    else
	write_clear_text_from_module(binary_file,module);
    reclaim_journal_tree_1(ISVREF(Current_kb_save,(SI_Long)39L));
    svref_arg_1 = Current_kb_save;
    SVREF(svref_arg_1,FIX((SI_Long)39L)) = Nil;
    return VALUES_1(Nil);
}

static Object array_constant_2;    /* # */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object QAUTHOR;             /* |author| */

static Object QDATE;               /* |date| */

/* MAYBE-WRITE-CLEAR-TEXT-DIFFS */
Object maybe_write_clear_text_diffs()
{
    Object module, new_xml_object, kb_file, current_xml_object, changes;
    Object changes_kb_file, author_qm, author_text_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object save_date, plist, name, value, ab_loop_list_, temp, svref_arg_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(136,8);
    module = ISVREF(Current_kb_save,(SI_Long)37L);
    new_xml_object = ISVREF(Current_kb_save,(SI_Long)47L);
    if (new_xml_object) {
	if (Write_diffs_after_saving_clear_text_p) {
	    kb_file = ISVREF(Current_kb_save,(SI_Long)5L);
	    current_xml_object = gensym_probe_file(kb_file) ? 
		    xml_object_and_fixups_for_file(kb_file) : Nil;
	    changes = current_xml_object ? 
		    compare_xml_object_and_fixups(current_xml_object,
		    new_xml_object,T) : Nil;
	    changes_kb_file = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,Nil,array_constant_2,Nil,kb_file);
	    author_qm = Servicing_workstation_qm ? 
		    ISVREF(Current_workstation,(SI_Long)20L) : Nil;
	    if (author_qm);
	    else
		author_qm = get_current_user_name_if_any_case_insensitive();
	    author_text_string_qm = author_qm ? 
		    copy_text_string(symbol_name_text_string(author_qm)) : Nil;
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
		      (SI_Long)3L));
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	      current_wide_string = wide_string_bv16;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		      3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      twrite_frame_edit_timestamp(get_current_frame_edit_timestamp());
		      save_date = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    plist = nconc2(author_qm ? gensym_list_2(QAUTHOR,
		    author_text_string_qm) : Nil,gensym_list_2(QDATE,
		    save_date));
	    write_xml_changes_to_file(changes,changes_kb_file,T,plist);
	    name = Nil;
	    value = Nil;
	    ab_loop_list_ = plist;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	  next_loop:
	    name = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    value = CAR(temp);
	    reclaim_text_string(value);
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    goto next_loop;
	  end_loop:;
	    reclaim_gensym_list_1(plist);
	    reclaim_xml_object_and_fixups(current_xml_object);
	}
	svref_arg_1 = Current_kb_save;
	SVREF(svref_arg_1,FIX((SI_Long)47L)) = Nil;
	reclaim_xml_object_and_fixups(new_xml_object);
    }
    return VALUES_1(Nil);
}

/* XML-OBJECT-AND-FIXUPS-FOR-MODULE */
Object xml_object_and_fixups_for_module(module)
    Object module;
{
    x_note_fn_call(136,9);
    return write_xml_object_from_module(module);
}

static Object Qget_xml_kb;         /* get-xml-kb */

/* XML-OBJECT-AND-FIXUPS-FOR-FILE */
Object xml_object_and_fixups_for_file(gensym_pathname_to_read)
    Object gensym_pathname_to_read;
{
    x_note_fn_call(136,10);
    return simple_kb_read(gensym_pathname_to_read,Qget_xml_kb,Nil,Nil);
}

/* GET-XML-FIXUPS-PATH */
Object get_xml_fixups_path(xml_object,path)
    Object xml_object, path;
{
    Object attr, current, path_old_value, temp;

    x_note_fn_call(136,11);
    attr = Nil;
    current = xml_object;
  next_loop:
    if ( !TRUEP(path))
	goto end_loop;
    path_old_value = path;
    temp = FIRST(path_old_value);
    path = REST(path_old_value);
    attr = temp;
    current = get_xml_fixups(current,attr,Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(current);
    return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

/* MODULE-NAME-STRING-FOR-XML-OBJECT */
Object module_name_string_for_xml_object(xml_object)
    Object xml_object;
{
    x_note_fn_call(136,12);
    return symbol_name_text_string(get_xml_fixups_path(xml_object,
	    list_constant));
}

/* MODULE-NAME-SYMBOL-FOR-XML-OBJECT */
Object module_name_symbol_for_xml_object(xml_object)
    Object xml_object;
{
    x_note_fn_call(136,13);
    return get_xml_fixups_path(xml_object,list_constant);
}

/* COMPARE-MODULE-TO-XML-FILE */
Object compare_module_to_xml_file(module,gensym_pathname_to_read)
    Object module, gensym_pathname_to_read;
{
    Object module_data, file_data, temp;

    x_note_fn_call(136,14);
    module_data = xml_object_and_fixups_for_module(module);
    file_data = xml_object_and_fixups_for_file(gensym_pathname_to_read);
    temp = compare_xml_object_and_fixups(module_data,file_data,T);
    reclaim_xml_object_and_fixups(module_data);
    reclaim_xml_object_and_fixups(file_data);
    return VALUES_1(temp);
}

/* COMPARE-XML-FILES */
Object compare_xml_files(gensym_pathname_to_read_1,gensym_pathname_to_read_2)
    Object gensym_pathname_to_read_1, gensym_pathname_to_read_2;
{
    Object file1_data, file2_data, temp;

    x_note_fn_call(136,15);
    file1_data = xml_object_and_fixups_for_file(gensym_pathname_to_read_1);
    file2_data = xml_object_and_fixups_for_file(gensym_pathname_to_read_2);
    temp = compare_xml_object_and_fixups(file1_data,file2_data,T);
    reclaim_xml_object_and_fixups(file1_data);
    reclaim_xml_object_and_fixups(file2_data);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Xml_output_stream, Qxml_output_stream);

DEFINE_VARIABLE_WITH_SYMBOL(Length_of_xml_output_line, Qlength_of_xml_output_line);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_output_buffer, Qxml_output_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_output_position, Qxml_output_position);

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

/* WRITE-XML-OBJECT-TO-FILE */
Object write_xml_object_to_file(xml_object,pathname_1)
    Object xml_object, pathname_1;
{
    Object dot_file_dot, file_name, xml_output_stream, xml_output_buffer;
    Object xml_output_position, length_of_xml_output_line, binary_pathname;
    Declare_special(4);
    Object result;

    x_note_fn_call(136,16);
    dot_file_dot = pathname_1;
    file_name = SIMPLE_VECTOR_P(dot_file_dot) && EQ(ISVREF(dot_file_dot,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
	    gensym_namestring(1,dot_file_dot) : copy_text_string(dot_file_dot);
    xml_output_stream = Nil ? g2_stream_open_for_appending(file_name,T) : 
	    g2_stream_open_for_output(file_name);
    PUSH_SPECIAL_WITH_SYMBOL(Xml_output_stream,Qxml_output_stream,xml_output_stream,
	    3);
      xml_output_buffer = obtain_simple_gensym_string(Write_kb_buffer_length);
      PUSH_SPECIAL_WITH_SYMBOL(Xml_output_buffer,Qxml_output_buffer,xml_output_buffer,
	      2);
	xml_output_position = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Xml_output_position,Qxml_output_position,xml_output_position,
		1);
	  length_of_xml_output_line = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Length_of_xml_output_line,Qlength_of_xml_output_line,length_of_xml_output_line,
		  0);
	    reclaim_text_string(file_name);
	    if (Xml_output_stream) {
		binary_pathname = 
			gensym_make_pathname_with_copied_components(Nil,
			Nil,Nil,Nil,array_constant_1,Nil,pathname_1);
		write_clear_text_from_xml_object(binary_pathname,xml_object);
		if ((SI_Long)0L < IFIX(Xml_output_position))
		    g2_stream_write_from_buffer(Xml_output_buffer,
			    Xml_output_position,Xml_output_stream);
		g2_stream_close(Xml_output_stream);
		reclaim_simple_gensym_string(Xml_output_buffer);
		result = VALUES_1(T);
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Show_deletions_in_xml_changes_p, Qshow_deletions_in_xml_changes_p);

static Object string_constant;     /* "~%<kbchanges" */

static Object string_constant_1;   /* "~%  ~a=~s" */

static Object string_constant_2;   /* ">" */

static Object Qdeletion;           /* deletion */

static Object string_constant_3;   /* "~%~%<delete rdf:resource=\"#~a\"/>" */

static Object Qaddition;           /* addition */

static Object string_constant_4;   /* "~%~%<add>" */

static Object string_constant_5;   /* "~%</add>" */

static Object Qattribute_deletion;  /* attribute-deletion */

static Object Qattribute_addition;  /* attribute-addition */

static Object Qchange;             /* change */

static Object string_constant_6;   /* "~%~%</kbchanges>~%~%" */

/* WRITE-XML-CHANGES-TO-FILE */
Object write_xml_changes_to_file(changes,file,append_p,header_plist)
    Object changes, file, append_p, header_plist;
{
    Object dot_file_dot, file_name, xml_output_stream, xml_output_buffer;
    Object xml_output_position, length_of_xml_output_line, name, value;
    Object ab_loop_list_, temp, operation, path, old, new_1, ab_loop_desetq_;
    Declare_special(4);
    Object result;

    x_note_fn_call(136,17);
    dot_file_dot = file;
    file_name = SIMPLE_VECTOR_P(dot_file_dot) && EQ(ISVREF(dot_file_dot,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
	    gensym_namestring(1,dot_file_dot) : copy_text_string(dot_file_dot);
    xml_output_stream = append_p ? g2_stream_open_for_appending(file_name,
	    T) : g2_stream_open_for_output(file_name);
    PUSH_SPECIAL_WITH_SYMBOL(Xml_output_stream,Qxml_output_stream,xml_output_stream,
	    3);
      xml_output_buffer = obtain_simple_gensym_string(Write_kb_buffer_length);
      PUSH_SPECIAL_WITH_SYMBOL(Xml_output_buffer,Qxml_output_buffer,xml_output_buffer,
	      2);
	xml_output_position = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Xml_output_position,Qxml_output_position,xml_output_position,
		1);
	  length_of_xml_output_line = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Length_of_xml_output_line,Qlength_of_xml_output_line,length_of_xml_output_line,
		  0);
	    reclaim_text_string(file_name);
	    if (Xml_output_stream) {
		kb_format(1,string_constant);
		name = Nil;
		value = Nil;
		ab_loop_list_ = header_plist;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
	      next_loop:
		name = CAR(ab_loop_list_);
		temp = CDR(ab_loop_list_);
		value = CAR(temp);
		temp = symbol_name_text_string(name);
		kb_format(3,string_constant_1,temp,value);
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		goto next_loop;
	      end_loop:;
		kb_format(1,string_constant_2);
		operation = Nil;
		path = Nil;
		old = Nil;
		new_1 = Nil;
		ab_loop_list_ = changes;
		ab_loop_desetq_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		operation = CAR(ab_loop_desetq_);
		temp = CDR(ab_loop_desetq_);
		path = CAR(temp);
		temp = CDR(ab_loop_desetq_);
		temp = CDR(temp);
		old = CAR(temp);
		temp = CDR(ab_loop_desetq_);
		temp = CDR(temp);
		temp = CDR(temp);
		new_1 = CAR(temp);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (EQ(operation,Qdeletion)) {
		    temp = last(path,_);
		    kb_format(2,string_constant_3,CDAR(temp));
		}
		else if (EQ(operation,Qaddition)) {
		    kb_format(1,string_constant_4);
		    write_xml_object__item_or_evaluation_value(new_1);
		    kb_format(1,string_constant_5);
		}
		else if (EQ(operation,Qattribute_deletion))
		    write_xml_attribute_change(operation,path,old,new_1);
		else if (EQ(operation,Qattribute_addition))
		    write_xml_attribute_change(operation,path,old,new_1);
		else if (EQ(operation,Qchange))
		    write_xml_attribute_change(operation,path,old,new_1);
		goto next_loop_1;
	      end_loop_1:;
		kb_format(1,string_constant_6);
		if ((SI_Long)0L < IFIX(Xml_output_position))
		    g2_stream_write_from_buffer(Xml_output_buffer,
			    Xml_output_position,Xml_output_stream);
		g2_stream_close(Xml_output_stream);
		reclaim_simple_gensym_string(Xml_output_buffer);
		result = VALUES_1(T);
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Write_xml_attribute_change_old_value_p, Qwrite_xml_attribute_change_old_value_p);

static Object string_constant_7;   /* "deleteattribute" */

static Object string_constant_8;   /* "addattribute" */

static Object string_constant_9;   /* "changeattribute" */

static Object string_constant_10;  /* "~%~%<~a rdf:resource=\"#~a\">" */

static Object string_constant_11;  /* "<element index=\"~d\">" */

static Object string_constant_12;  /* "<~a>" */

static Object string_constant_13;  /* "~%" */

static Object string_constant_14;  /* "<OLDVALUE>" */

static Object string_constant_15;  /* "</OLDVALUE>" */

static Object string_constant_16;  /* "</element>" */

static Object string_constant_17;  /* "</~a>" */

static Object string_constant_18;  /* "~%</~a>" */

/* WRITE-XML-ATTRIBUTE-CHANGE */
Object write_xml_attribute_change(operation,path,old,new_1)
    Object operation, path, old, new_1;
{
    Object operation_name, name_list, reversed_list, element, ab_loop_list_;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(136,18);
    if (EQ(operation,Qattribute_deletion))
	operation_name = string_constant_7;
    else if (EQ(operation,Qattribute_addition))
	operation_name = string_constant_8;
    else if (EQ(operation,Qchange))
	operation_name = string_constant_9;
    else
	operation_name = Qnil;
    name_list = get_rdf_name_list_for_context(path);
    reversed_list = nreverse(copy_list_using_gensym_conses_1(name_list));
    kb_format(3,string_constant_10,operation_name,CAR(reversed_list));
    element = Nil;
    ab_loop_list_ = CDR(reversed_list);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUMP(element))
	kb_format(2,string_constant_11,element);
    else
	kb_format(2,string_constant_12,element);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(reversed_list);
    if ( !EQ(operation,Qattribute_addition)) {
	if (Write_xml_attribute_change_old_value_p) {
	    kb_format(1,string_constant_13);
	    kb_format(1,string_constant_14);
	    write_xml_object__item_or_evaluation_value(old);
	    kb_format(1,string_constant_15);
	}
    }
    if ( !EQ(operation,Qattribute_deletion)) {
	kb_format(1,string_constant_13);
	write_xml_object__item_or_evaluation_value(new_1);
    }
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_SUB1(length(name_list)));
    element = Nil;
    ab_loop_list_ = name_list;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUMP(element))
	kb_format(1,string_constant_16);
    else
	kb_format(2,string_constant_17,element);
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    kb_format(2,string_constant_18,operation_name);
    return reclaim_gensym_list_1(name_list);
}

static Object Qid;                 /* id */

static Object Qg2m;                /* g2m */

/* GET-RDF-NAME-LIST-FOR-CONTEXT */
Object get_rdf_name_list_for_context(path)
    Object path;
{
    Object type, value, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp;

    x_note_fn_call(136,19);
    type = Nil;
    value = Nil;
    ab_loop_list_ = path;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type = CAR(ab_loop_desetq_);
    value = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUMP(value))
	temp = value;
    else if (EQ(type,Qid))
	temp = value;
    else
	temp = get_rdf_attribute_name(4,Nil,type,value,Qg2m);
    ab_loopvar__2 = gensym_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Traversing_xml_object_p, Qtraversing_xml_object_p);

static Object Qprimitive_value;    /* primitive-value */

static Object Qvalue;              /* value */

static Object Qunit;               /* unit */

static Object Qnone;               /* none */

static Object Quser_attribute_count;  /* user-attribute-count */

static Object Qitem;               /* item */

static Object Qab_class;           /* class */

static Object Qelements;           /* elements */

static Object Qattributes;         /* attributes */

/* MAKE-XML-OBJECT */
Object make_xml_object varargs_1(int, n)
{
    Object object, type, fixups, include_value_slot;
    Object user_attribute_count, unit_qm, temp, temp_1, temp_2, temp_3, name;
    Object value, ab_loop_list_, temp_4, user, user_p, current, current_user_p;
    Object user_list, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, name_symbol;
    SI_Long i;
    char temp_5;
    Declare_varargs_nonrelocating;

    x_note_fn_call(136,20);
    INIT_ARGS_nonrelocating();
    object = REQUIRED_ARG_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    fixups = REQUIRED_ARG_nonrelocating();
    include_value_slot = REQUIRED_ARG_nonrelocating();
    user_attribute_count = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    unit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(type,Qprimitive_value) &&  !TRUEP(unit_qm))
	return VALUES_1(object);
    else {
	temp = object || include_value_slot ? eval_list_2(Qvalue,object) : Nil;
	temp_1 = eval_list_2(Qtype,type);
	temp_2 = unit_qm ? eval_list_2(Qunit,unit_qm) : Nil;
	if (EQ(user_attribute_count,Qnone))
	    temp_3 = Nil;
	else if (user_attribute_count)
	    temp_3 = eval_list_2(Quser_attribute_count,user_attribute_count);
	else {
	    if (EQ(type,Qitem)) {
		name = Nil;
		value = Nil;
		ab_loop_list_ = fixups;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
	      next_loop:
		name = CAR(ab_loop_list_);
		temp_4 = CDR(ab_loop_list_);
		value = CAR(temp_4);
		if (CONSP(name)) {
		    temp_5 = TRUEP(T);
		    goto end_1;
		}
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		goto next_loop;
	      end_loop:
		temp_5 = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp_5 = TRUEP(Nil);
	    if (temp_5) {
		user = Nil;
		user_p = Nil;
		current = FIX((SI_Long)0L);
		i = (SI_Long)0L;
		name = Nil;
		value = Nil;
		ab_loop_list_ = fixups;
		current_user_p = Nil;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
	      next_loop_1:
		name = CAR(ab_loop_list_);
		temp_4 = CDR(ab_loop_list_);
		value = CAR(temp_4);
		current_user_p = CONSP(name) ? T : Nil;
		if (EQ(user_p,current_user_p))
		    current = FIXNUM_ADD1(current);
		else {
		    user = eval_cons_1(current,user);
		    current = FIX((SI_Long)1L);
		    user_p = current_user_p;
		}
		i = i + (SI_Long)1L;
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		goto next_loop_1;
	      end_loop_1:
		user_list = nreverse(user);
		if (EQ(CAR(user_list),FIX((SI_Long)2L)) && EQ(CAR(fixups),
			Qab_class) && EQ(CADDR(fixups),Qid) &&  
			!TRUEP(CDDR(user_list))) {
		    temp_4 = CDR(user_list) ? CADR(user_list) : current;
		    reclaim_eval_list_1(user_list);
		}
		else
		    temp_4 = allocate_evaluation_sequence(user_list);
		goto end_2;
		temp_4 = Qnil;
	      end_2:;
		temp_3 = eval_list_2(Quser_attribute_count,temp_4);
	    }
	    else
		temp_3 = Qnil;
	}
	if (fixups) {
	    if (EQ(type,Qsequence)) {
		name = Nil;
		value = Nil;
		ab_loop_list_ = fixups;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
	      next_loop_2:
		name = CAR(ab_loop_list_);
		temp_4 = CDR(ab_loop_list_);
		value = CAR(temp_4);
		ab_loopvar__2 = eval_cons_1(value,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		goto next_loop_2;
	      end_loop_2:
		temp_4 = ab_loopvar_;
		goto end_3;
		temp_4 = Qnil;
	      end_3:;
		reclaim_eval_list_1(fixups);
		temp_4 = eval_list_2(Qelements,
			allocate_evaluation_sequence(temp_4));
	    }
	    else {
		name = Nil;
		value = Nil;
		ab_loop_list_ = fixups;
		name_symbol = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
	      next_loop_3:
		name = CAR(ab_loop_list_);
		temp_4 = CDR(ab_loop_list_);
		value = CAR(temp_4);
		if (CONSP(name)) {
		    temp_4 = CDR(name) ? 
			    make_unique_slot_name_symbol(CDR(name),
			    CAR(name)) : CAR(name);
		    reclaim_eval_cons_1(name);
		    name_symbol = temp_4;
		}
		else
		    name_symbol = name;
		ab_loopvar__2 = eval_list_2(name_symbol,value);
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		goto next_loop_3;
	      end_loop_3:
		temp_4 = ab_loopvar_;
		goto end_4;
		temp_4 = Qnil;
	      end_4:;
		reclaim_eval_list_1(fixups);
		temp_4 = eval_list_2(Qattributes,
			allocate_evaluation_structure(temp_4));
	    }
	}
	else
	    temp_4 = Nil;
	return allocate_evaluation_structure(nconc2(temp,nconc2(temp_1,
		nconc2(temp_2,nconc2(temp_3,temp_4)))));
    }
}

static Object Qab_structure;       /* structure */

static Object Qtext;               /* text */

/* XML-OBJECT-UNIT */
Object xml_object_unit(x)
    Object x;
{
    Object object_and_fixups, object_and_fixups_vector, type, unit, temp;
    Object fixups;

    x_note_fn_call(136,21);
    object_and_fixups = x;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    unit = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil) : Nil;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp = unit;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	temp = Nil;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* COLLECT-XML-LIST */
Object collect_xml_list(contents,type)
    Object contents, type;
{
    Object include_value_slot, name, value, ab_loop_list_, kept_value;
    Object value_list, ab_loopvar_, ab_loopvar__1, fixup_list, ab_loopvar__2;
    Object temp, object_and_fixups, object_and_fixups_vector, type_1, o, thing;
    Object fixups;
    SI_Long index_1;
    char sequencep_1;

    x_note_fn_call(136,22);
    include_value_slot = T;
    sequencep_1 = EQ(type,Qsequence);
    name = Nil;
    value = Nil;
    ab_loop_list_ = contents;
    index_1 = (SI_Long)0L;
    kept_value = Nil;
    value_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    fixup_list = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__1 = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
  next_loop:
    if (include_value_slot) {
	object_and_fixups = value;
	object_and_fixups_vector = CONSP(object_and_fixups) && 
		EQ(M_CDR(object_and_fixups),Qab_structure) ? 
		M_CAR(object_and_fixups) : Nil;
	type_1 = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	o = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
		object_and_fixups;
	if (EQ(type_1,Qprimitive_value) || EQ(type_1,Qtext))
	    thing = o;
	else if (EQ(type_1,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    thing = o;
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    thing = o;
	}
	kept_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing);
    }
    else
	kept_value = Nil;
    ab_loopvar__1 = include_value_slot ? (sequencep_1 ? 
	    eval_cons_1(kept_value,Nil) : eval_list_2(name,kept_value)) : Nil;
    if (ab_loopvar__1) {
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    value_list = ab_loopvar__1;
	ab_loopvar_ = last(ab_loopvar__1,_);
    }
    ab_loopvar__1 = eval_list_2(name,value);
    if (ab_loopvar__1) {
	if (ab_loopvar__2)
	    M_CDR(ab_loopvar__2) = ab_loopvar__1;
	else
	    fixup_list = ab_loopvar__1;
	ab_loopvar__2 = last(ab_loopvar__1,_);
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(contents);
    if (include_value_slot) {
	if (EQ(type,Qsequence))
	    temp = allocate_evaluation_sequence(value_list);
	else if (EQ(type,Qab_structure))
	    temp = allocate_evaluation_structure(value_list);
	else
	    temp = Qnil;
    }
    else
	temp = Nil;
    return make_xml_object(4,temp,type,fixup_list,T);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2binary_file_stream, Qg2binary_file_stream);

static Object QRDF_COL_RESOURCE;   /* |rdf:resource| */

static Object Qbinary;             /* binary */

/* MAKE-BINARY-XML-OBJECT */
Object make_binary_xml_object(fixups,include_value_slot)
    Object fixups, include_value_slot;
{
    Object resource, index_1, value, error_string, temp;
    Object result;

    x_note_fn_call(136,23);
    if (include_value_slot && G2binary_file_stream) {
	resource = getf(fixups,QRDF_COL_RESOURCE,_);
	if (resource) {
	    index_1 = get_binary_file_index_from_xml_locator(resource);
	    if (index_1) {
		result = read_data_from_g2binary_file(index_1);
		MVS_2(result,value,error_string);
		if (error_string)
		    return VALUES_2(Nil,error_string);
		temp = value;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return make_xml_object(4,temp,Qbinary,fixups,include_value_slot);
}

/* XML-OBJECT-ATTRIBUTE-IS-USER-ATTRIBUTE-P */
Object xml_object_attribute_is_user_attribute_p(object_and_fixups,attribute)
    Object object_and_fixups, attribute;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, fixups, user_p;
    Object value, dot_uac_dot, dot_uac_index_dot, dot_uac_length_dot;
    Object dot_uac_sys_p_dot, dot_current_uac_dot, gensymed_symbol;
    Object gensymed_symbol_1, held_vector, name_1, attribute_value;
    Object dot_last_user_p_dot, ab_loop_iter_flag_;
    SI_Long name, ab_loop_bind_, next_index, length_1, gensymed_symbol_2;
    char dot_only_system_attrs_p_dot;

    x_note_fn_call(136,24);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (!(EQ(type,Qprimitive_value) || EQ(type,Qtext))) {
	if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (fixups) {
		user_p = Nil;
		name = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		value = Nil;
	      next_loop:
		if (name >= ab_loop_bind_)
		    goto end_loop;
		value = evaluation_sequence_aref(fixups,FIX(name));
		if (EQ(FIX(name),attribute))
		    return VALUES_1(user_p);
		name = name + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (fixups) {
		dot_uac_dot = structure_slot_1(object_and_fixups_vector,
			Quser_attribute_count,Nil);
		dot_only_system_attrs_p_dot =  !TRUEP(dot_uac_dot);
		dot_uac_index_dot = CONSP(dot_uac_dot) && 
			EQ(M_CDR(dot_uac_dot),Qsequence) ? 
			FIX((SI_Long)0L) : Nil;
		dot_uac_length_dot = dot_uac_index_dot ? 
			FIXNUM_SUB1(ISVREF(M_CAR(dot_uac_dot),
			(SI_Long)1L)) : Nil;
		dot_uac_sys_p_dot = FIXNUMP(dot_uac_dot) ? T : Nil;
		if (dot_only_system_attrs_p_dot)
		    dot_current_uac_dot = Nil;
		else if (dot_uac_index_dot) {
		    gensymed_symbol = M_CAR(dot_uac_dot);
		    gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
		    dot_current_uac_dot = 
			    FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(M_CAR(dot_uac_dot),
			    IFIX(FIXNUM_ADD(gensymed_symbol_1,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(gensymed_symbol,
			    (IFIX(gensymed_symbol_1) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(gensymed_symbol_1) & (SI_Long)1023L);
		}
		else if (dot_uac_sys_p_dot)
		    dot_current_uac_dot = FIX((SI_Long)2L);
		else
		    dot_current_uac_dot = Qnil;
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		name_1 = Nil;
		attribute_value = Nil;
		value = Nil;
		dot_last_user_p_dot = Nil;
		user_p = Nil;
		ab_loop_iter_flag_ = T;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_2 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 
			& (SI_Long)1023L);
		value = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if ( !TRUEP(ab_loop_iter_flag_))
		    dot_last_user_p_dot = user_p;
		if (dot_only_system_attrs_p_dot)
		    user_p = Nil;
		else if ((SI_Long)0L < IFIX(dot_current_uac_dot)) {
		    dot_current_uac_dot = FIXNUM_SUB1(dot_current_uac_dot);
		    user_p = dot_last_user_p_dot;
		}
		else if (dot_uac_index_dot) {
		    dot_uac_index_dot = FIXNUM_ADD1(dot_uac_index_dot);
		    if (FIXNUM_LT(dot_uac_index_dot,dot_uac_length_dot)) {
			gensymed_symbol = M_CAR(dot_uac_dot);
			gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
			dot_current_uac_dot = 
				FIXNUM_SUB1(FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(M_CAR(dot_uac_dot),
				IFIX(FIXNUM_ADD(gensymed_symbol_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(gensymed_symbol,
				(IFIX(gensymed_symbol_1) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(gensymed_symbol_1) & (SI_Long)1023L));
		    }
		    else
			dot_current_uac_dot = Most_positive_fixnum;
		    user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		else if (dot_uac_sys_p_dot) {
		    dot_uac_sys_p_dot = Nil;
		    dot_current_uac_dot = FIXNUM_SUB1(dot_uac_dot);
		    user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		else {
		    dot_current_uac_dot = Most_positive_fixnum;
		    user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		if (EQ(name_1,attribute))
		    return VALUES_1(user_p);
		ab_loop_iter_flag_ = Nil;
		goto next_loop_1;
	      end_loop_1:;
	    }
	}
    }
    return VALUES_1(Nil);
}

/* COPY-XML-OBJECT */
Object copy_xml_object(object_and_fixups,copy_annotations_p)
    Object object_and_fixups, copy_annotations_p;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, unit, object;
    Object object_copy, temp, fixups, value_p, temp_1, fixups_reversed, value;
    Object thing, gensymed_symbol, held_vector, name_1, attribute_value;
    SI_Long name, ab_loop_bind_, next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(136,25);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    unit = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil) : Nil;
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext)) {
	object_copy = FIXNUMP(object) || object && SYMBOLP(object) || 
		SIMPLE_VECTOR_P(object) ? object : 
		copy_if_evaluation_value_1(object);
	temp = EQ(type,Qprimitive_value) &&  !TRUEP(unit) ? object_copy : 
		make_xml_object(6,object_copy,type,Nil,T,Nil,unit);
    }
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	value_p = copy_annotations_p;
	if (value_p);
	else
	    value_p = EQ(type,Qbinary) ? T : Nil;
	temp_1 = value_p ? (FIXNUMP(object) || object && SYMBOLP(object) 
		|| SIMPLE_VECTOR_P(object) ? object : 
		copy_if_evaluation_value_1(object)) : Nil;
	fixups_reversed = Nil;
	if (fixups) {
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop:
	    if (name >= ab_loop_bind_)
		goto end_loop;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    fixups_reversed = eval_cons_1(FIX(name),fixups_reversed);
	    temp = copy_xml_object(value,copy_annotations_p);
	    fixups_reversed = eval_cons_1(temp,fixups_reversed);
	    name = name + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	temp = nreverse(fixups_reversed);
	thing = estructure_slot(object_and_fixups,Quser_attribute_count,Qnone);
	temp = make_xml_object(6,temp_1,type,temp,value_p,FIXNUMP(thing) 
		|| thing && SYMBOLP(thing) || SIMPLE_VECTOR_P(thing) ? 
		thing : copy_if_evaluation_value_1(thing),unit);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	value_p = copy_annotations_p;
	if (value_p);
	else
	    value_p = EQ(type,Qbinary) ? T : Nil;
	temp_1 = value_p ? (FIXNUMP(object) || object && SYMBOLP(object) 
		|| SIMPLE_VECTOR_P(object) ? object : 
		copy_if_evaluation_value_1(object)) : Nil;
	fixups_reversed = Nil;
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    fixups_reversed = eval_cons_1(name_1,fixups_reversed);
	    temp = copy_xml_object(value,copy_annotations_p);
	    fixups_reversed = eval_cons_1(temp,fixups_reversed);
	    goto next_loop_1;
	  end_loop_1:;
	}
	temp = nreverse(fixups_reversed);
	thing = estructure_slot(object_and_fixups,Quser_attribute_count,Qnone);
	temp = make_xml_object(6,temp_1,type,temp,value_p,FIXNUMP(thing) 
		|| thing && SYMBOLP(thing) || SIMPLE_VECTOR_P(thing) ? 
		thing : copy_if_evaluation_value_1(thing),unit);
    }
    return VALUES_1(temp);
}

/* RECLAIM-XML-OBJECT-AND-FIXUPS */
Object reclaim_xml_object_and_fixups(object_and_fixups)
    Object object_and_fixups;
{
    x_note_fn_call(136,26);
    if ( !(FIXNUMP(object_and_fixups) || SYMBOLP(object_and_fixups) || 
	    SIMPLE_VECTOR_P(object_and_fixups)))
	return reclaim_if_evaluation_value_1(object_and_fixups);
    else
	return VALUES_1(Nil);
}

/* GET-XML-FIXUPS */
Object get_xml_fixups(object_and_fixups,indicator,user_attribute_p)
    Object object_and_fixups, indicator, user_attribute_p;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, temp, fixups;
    Object user_p, value, dot_uac_dot, dot_uac_index_dot, dot_uac_length_dot;
    Object dot_uac_sys_p_dot, dot_current_uac_dot, gensymed_symbol;
    Object gensymed_symbol_1, held_vector, name_1, attribute_value;
    Object dot_last_user_p_dot, ab_loop_iter_flag_;
    SI_Long name, ab_loop_bind_, next_index, length_1, gensymed_symbol_2;
    char dot_only_system_attrs_p_dot;

    x_note_fn_call(136,27);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp = Nil;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (fixups) {
	    user_p = Nil;
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop:
	    if (name >= ab_loop_bind_)
		goto end_loop;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    if (EQ(FIX(name),indicator) && EQ( ! !TRUEP(user_p) ? T : Nil, 
		    ! !TRUEP(user_attribute_p) ? T : Nil))
		return VALUES_1(value);
	    name = name + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	}
	else
	    temp = Nil;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (fixups) {
	    dot_uac_dot = structure_slot_1(object_and_fixups_vector,
		    Quser_attribute_count,Nil);
	    dot_only_system_attrs_p_dot =  !TRUEP(dot_uac_dot);
	    dot_uac_index_dot = CONSP(dot_uac_dot) && 
		    EQ(M_CDR(dot_uac_dot),Qsequence) ? FIX((SI_Long)0L) : Nil;
	    dot_uac_length_dot = dot_uac_index_dot ? 
		    FIXNUM_SUB1(ISVREF(M_CAR(dot_uac_dot),(SI_Long)1L)) : Nil;
	    dot_uac_sys_p_dot = FIXNUMP(dot_uac_dot) ? T : Nil;
	    if (dot_only_system_attrs_p_dot)
		dot_current_uac_dot = Nil;
	    else if (dot_uac_index_dot) {
		gensymed_symbol = M_CAR(dot_uac_dot);
		gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
		dot_current_uac_dot = FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(M_CAR(dot_uac_dot),
			IFIX(FIXNUM_ADD(gensymed_symbol_1,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(gensymed_symbol,
			(IFIX(gensymed_symbol_1) >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),IFIX(gensymed_symbol_1) & (SI_Long)1023L);
	    }
	    else if (dot_uac_sys_p_dot)
		dot_current_uac_dot = FIX((SI_Long)2L);
	    else
		dot_current_uac_dot = Qnil;
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    dot_last_user_p_dot = Nil;
	    user_p = Nil;
	    ab_loop_iter_flag_ = T;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_2 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_2 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		dot_last_user_p_dot = user_p;
	    if (dot_only_system_attrs_p_dot)
		user_p = Nil;
	    else if ((SI_Long)0L < IFIX(dot_current_uac_dot)) {
		dot_current_uac_dot = FIXNUM_SUB1(dot_current_uac_dot);
		user_p = dot_last_user_p_dot;
	    }
	    else if (dot_uac_index_dot) {
		dot_uac_index_dot = FIXNUM_ADD1(dot_uac_index_dot);
		if (FIXNUM_LT(dot_uac_index_dot,dot_uac_length_dot)) {
		    gensymed_symbol = M_CAR(dot_uac_dot);
		    gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
		    dot_current_uac_dot = 
			    FIXNUM_SUB1(FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(M_CAR(dot_uac_dot),
			    IFIX(FIXNUM_ADD(gensymed_symbol_1,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(gensymed_symbol,
			    (IFIX(gensymed_symbol_1) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(gensymed_symbol_1) & (SI_Long)1023L));
		}
		else
		    dot_current_uac_dot = Most_positive_fixnum;
		user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
	    }
	    else if (dot_uac_sys_p_dot) {
		dot_uac_sys_p_dot = Nil;
		dot_current_uac_dot = FIXNUM_SUB1(dot_uac_dot);
		user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
	    }
	    else {
		dot_current_uac_dot = Most_positive_fixnum;
		user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
	    }
	    if (EQ(name_1,indicator) && EQ( ! !TRUEP(user_p) ? T : Nil, ! 
		    !TRUEP(user_attribute_p) ? T : Nil))
		return VALUES_1(value);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* REPLACE-XML-FIXUPS */
Object replace_xml_fixups(object_and_fixups,indicator,new_value)
    Object object_and_fixups, indicator, new_value;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, temp, fixups;
    Object value, gensymed_symbol, svref_arg_1, item_or_value, x2;
    Object svref_new_value, held_vector, name_1, attribute_value;
    SI_Long name, ab_loop_bind_, gensymed_symbol_1, svref_arg_2, next_index;
    SI_Long length_1;
    char temp_1;

    x_note_fn_call(136,28);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp = Nil;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (fixups) {
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop:
	    if (name >= ab_loop_bind_)
		goto end_loop;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    if (EQ(FIX(name),indicator)) {
		reclaim_xml_object_and_fixups(value);
		gensymed_symbol = M_CAR(fixups);
		gensymed_symbol_1 = name + (SI_Long)1L;
		if (FIXNUM_LE(ISVREF(M_CAR(fixups),(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_1 = M_CAR(fixups);
		    svref_arg_2 = gensymed_symbol_1 + 
			    IFIX(Managed_array_index_offset);
		    item_or_value = new_value;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    svref_new_value = temp_1 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		}
		else {
		    svref_arg_1 = ISVREF(gensymed_symbol,
			    (gensymed_symbol_1 >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		    item_or_value = new_value;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    svref_new_value = temp_1 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		}
		return VALUES_1(Nil);
	    }
	    name = name + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	}
	else
	    temp = Nil;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    if (EQ(name_1,indicator)) {
		reclaim_xml_object_and_fixups(value);
		set_evaluation_structure_slot(fixups,name_1,new_value);
		return VALUES_1(Nil);
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* GET-XML-OBJECT */
Object get_xml_object(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, temp;
    Object fixups;

    x_note_fn_call(136,29);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp = object;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	temp = object;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	temp = object;
    }
    return VALUES_1(temp);
}

/* LOOKUP-XML-OBJECT */
Object lookup_xml_object(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, temp;
    Object fixups, resource;

    x_note_fn_call(136,30);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp = object;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	temp = object;
	if (temp);
	else {
	    resource = get_xml_fixups(object_and_fixups,QRDF_COL_RESOURCE,Nil);
	    if (resource) {
		object = get_instance_from_xml_locator(resource);
		if (object) {
		    set_evaluation_structure_slot(object_and_fixups_1,
			    Qvalue,object);
		    temp = object;
		}
		else
		    temp = Nil;
	    }
	    else
		temp = Nil;
	}
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	temp = object;
	if (temp);
	else {
	    resource = get_xml_fixups(object_and_fixups,QRDF_COL_RESOURCE,Nil);
	    if (resource) {
		object = get_instance_from_xml_locator(resource);
		if (object) {
		    set_evaluation_structure_slot(object_and_fixups_1,
			    Qvalue,object);
		    temp = object;
		}
		else
		    temp = Nil;
	    }
	    else
		temp = Nil;
	}
    }
    return VALUES_1(temp);
}

/* XML-OBJECT-TEXT-OF-P */
Object xml_object_text_of_p(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, vtype, temp, fixups;

    x_note_fn_call(136,31);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    vtype = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(vtype,Qprimitive_value) || EQ(vtype,Qtext))
	temp = EQ(vtype,Qtext) ? T : Nil;
    else if (EQ(vtype,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	temp = Nil;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* XML-OBJECT-AND-FIXUPS-FRAME-P */
Object xml_object_and_fixups_frame_p(x)
    Object x;
{
    Object object_and_fixups, object_and_fixups_vector, type, temp, fixups;
    Object value, gensymed_symbol, held_vector, name_1, attribute_value;
    SI_Long name, ab_loop_bind_, next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(136,32);
    object_and_fixups = x;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp = Nil;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (EQ(type,Qitem)) {
	    if (fixups) {
		name = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		value = Nil;
	      next_loop:
		if (name >= ab_loop_bind_)
		    goto end_loop;
		value = evaluation_sequence_aref(fixups,FIX(name));
		if (EQ(FIX(name),Qab_class))
		    return VALUES_1(value);
		name = name + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		temp = Qnil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (EQ(type,Qitem)) {
	    if (fixups) {
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		name_1 = Nil;
		attribute_value = Nil;
		value = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 
			& (SI_Long)1023L);
		value = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if (EQ(name_1,Qab_class))
		    return VALUES_1(value);
		goto next_loop_1;
	      end_loop_1:
		temp = Qnil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* XML-OBJECT-AND-FIXUPS-EVALUATION-TYPE */
Object xml_object_and_fixups_evaluation_type(x)
    Object x;
{
    Object object_and_fixups, object_and_fixups_vector, type, object, temp;
    Object fixups;

    x_note_fn_call(136,33);
    object_and_fixups = x;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp =  !EQ(type,Qbinary) ? (object ? 
		evaluation_value_type(object) : Nil) : Nil;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	temp = EQ(type,Qsequence) || EQ(type,Qab_structure) ? type : Nil;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	temp = EQ(type,Qsequence) || EQ(type,Qab_structure) ? type : Nil;
    }
    return VALUES_1(temp);
}

/* XML-OBJECT-AND-FIXUPS-BINARY-TYPE */
Object xml_object_and_fixups_binary_type(x)
    Object x;
{
    Object object_and_fixups, object_and_fixups_vector, type, temp, fixups;

    x_note_fn_call(136,34);
    object_and_fixups = x;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp = Nil;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	temp = EQ(type,Qbinary) ? Qbinary : Nil;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	temp = EQ(type,Qbinary) ? Qbinary : Nil;
    }
    return VALUES_1(temp);
}

/* GET-XML-OBJECT-ATTRIBUTE */
Object get_xml_object_attribute(object_and_fixups,attribute,user_p,default_1)
    Object object_and_fixups, attribute, user_p, default_1;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, fixups, u_p;
    Object val, dot_uac_dot, dot_uac_index_dot, dot_uac_length_dot;
    Object dot_uac_sys_p_dot, dot_current_uac_dot, gensymed_symbol;
    Object gensymed_symbol_1, held_vector, attr_1, attribute_value;
    Object dot_last_user_p_dot, ab_loop_iter_flag_;
    SI_Long attr, ab_loop_bind_, next_index, length_1, gensymed_symbol_2;
    char dot_only_system_attrs_p_dot;

    x_note_fn_call(136,35);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (!(EQ(type,Qprimitive_value) || EQ(type,Qtext))) {
	if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (fixups) {
		u_p = Nil;
		attr = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		val = Nil;
	      next_loop:
		if (attr >= ab_loop_bind_)
		    goto end_loop;
		val = evaluation_sequence_aref(fixups,FIX(attr));
		if (EQ(FIX(attr),attribute) && EQ(u_p,user_p))
		    return VALUES_1(val);
		attr = attr + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (fixups) {
		dot_uac_dot = structure_slot_1(object_and_fixups_vector,
			Quser_attribute_count,Nil);
		dot_only_system_attrs_p_dot =  !TRUEP(dot_uac_dot);
		dot_uac_index_dot = CONSP(dot_uac_dot) && 
			EQ(M_CDR(dot_uac_dot),Qsequence) ? 
			FIX((SI_Long)0L) : Nil;
		dot_uac_length_dot = dot_uac_index_dot ? 
			FIXNUM_SUB1(ISVREF(M_CAR(dot_uac_dot),
			(SI_Long)1L)) : Nil;
		dot_uac_sys_p_dot = FIXNUMP(dot_uac_dot) ? T : Nil;
		if (dot_only_system_attrs_p_dot)
		    dot_current_uac_dot = Nil;
		else if (dot_uac_index_dot) {
		    gensymed_symbol = M_CAR(dot_uac_dot);
		    gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
		    dot_current_uac_dot = 
			    FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(M_CAR(dot_uac_dot),
			    IFIX(FIXNUM_ADD(gensymed_symbol_1,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(gensymed_symbol,
			    (IFIX(gensymed_symbol_1) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(gensymed_symbol_1) & (SI_Long)1023L);
		}
		else if (dot_uac_sys_p_dot)
		    dot_current_uac_dot = FIX((SI_Long)2L);
		else
		    dot_current_uac_dot = Qnil;
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		attr_1 = Nil;
		attribute_value = Nil;
		val = Nil;
		dot_last_user_p_dot = Nil;
		u_p = Nil;
		ab_loop_iter_flag_ = T;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		attr_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_2 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 
			& (SI_Long)1023L);
		val = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if ( !TRUEP(ab_loop_iter_flag_))
		    dot_last_user_p_dot = u_p;
		if (dot_only_system_attrs_p_dot)
		    u_p = Nil;
		else if ((SI_Long)0L < IFIX(dot_current_uac_dot)) {
		    dot_current_uac_dot = FIXNUM_SUB1(dot_current_uac_dot);
		    u_p = dot_last_user_p_dot;
		}
		else if (dot_uac_index_dot) {
		    dot_uac_index_dot = FIXNUM_ADD1(dot_uac_index_dot);
		    if (FIXNUM_LT(dot_uac_index_dot,dot_uac_length_dot)) {
			gensymed_symbol = M_CAR(dot_uac_dot);
			gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
			dot_current_uac_dot = 
				FIXNUM_SUB1(FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(M_CAR(dot_uac_dot),
				IFIX(FIXNUM_ADD(gensymed_symbol_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(gensymed_symbol,
				(IFIX(gensymed_symbol_1) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(gensymed_symbol_1) & (SI_Long)1023L));
		    }
		    else
			dot_current_uac_dot = Most_positive_fixnum;
		    u_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		else if (dot_uac_sys_p_dot) {
		    dot_uac_sys_p_dot = Nil;
		    dot_current_uac_dot = FIXNUM_SUB1(dot_uac_dot);
		    u_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		else {
		    dot_current_uac_dot = Most_positive_fixnum;
		    u_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		if (EQ(attr_1,attribute) && EQ(u_p,user_p))
		    return VALUES_1(val);
		ab_loop_iter_flag_ = Nil;
		goto next_loop_1;
	      end_loop_1:;
	    }
	}
    }
    return VALUES_1(default_1);
}

/* XML-OBJECT-HAS-ATTRIBUTES-P */
Object xml_object_has_attributes_p(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, fixups, val;
    Object gensymed_symbol, held_vector, attr_1, attribute_value;
    SI_Long attr, ab_loop_bind_, next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(136,36);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (!(EQ(type,Qprimitive_value) || EQ(type,Qtext))) {
	if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (fixups) {
		attr = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		val = Nil;
	      next_loop:
		if (attr >= ab_loop_bind_)
		    goto end_loop;
		val = evaluation_sequence_aref(fixups,FIX(attr));
		return VALUES_1(T);
		attr = attr + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (fixups) {
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		attr_1 = Nil;
		attribute_value = Nil;
		val = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		attr_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 
			& (SI_Long)1023L);
		val = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		return VALUES_1(T);
		goto next_loop_1;
	      end_loop_1:;
	    }
	}
    }
    return VALUES_1(Nil);
}

/* GET-XML-OBJECT-FROM-ID */
Object get_xml_object_from_id(object_and_fixups,id,default_1)
    Object object_and_fixups, id, default_1;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, fixups, val;
    Object gensymed_symbol, held_vector, attr_1, attribute_value;
    SI_Long attr, ab_loop_bind_, next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(136,37);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (!(EQ(type,Qprimitive_value) || EQ(type,Qtext))) {
	if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (fixups) {
		attr = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		val = Nil;
	      next_loop:
		if (attr >= ab_loop_bind_)
		    goto end_loop;
		val = evaluation_sequence_aref(fixups,FIX(attr));
		if (matching_xml_object_id(id_of_xml_object(val),id))
		    return VALUES_1(val);
		attr = attr + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (fixups) {
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		attr_1 = Nil;
		attribute_value = Nil;
		val = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		attr_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 
			& (SI_Long)1023L);
		val = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if (matching_xml_object_id(id_of_xml_object(val),id))
		    return VALUES_1(val);
		goto next_loop_1;
	      end_loop_1:;
	    }
	}
    }
    return VALUES_1(default_1);
}

/* MATCHING-XML-OBJECT-ID */
Object matching_xml_object_id(id1,id2)
    Object id1, id2;
{
    Object temp;

    x_note_fn_call(136,38);
    temp = EQ(id1,id2) ? T : Nil;
    if (temp);
    else
	temp = text_string_p(id1) && text_string_p(id2) ? 
		string_equalw(id1,id2) : Qnil;
    return VALUES_1(temp);
}

/* ID-OF-XML-OBJECT */
Object id_of_xml_object(object_and_fixups)
    Object object_and_fixups;
{
    Object temp;

    x_note_fn_call(136,39);
    temp = get_xml_fixups(object_and_fixups,Qid,Nil);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Attr_not_found, Qattr_not_found);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_object_changes, Qxml_object_changes);

DEFINE_VARIABLE_WITH_SYMBOL(Compare_xml_collect_diffs_p, Qcompare_xml_collect_diffs_p);

static Object Qconnection_input;   /* connection-input */

static Object Qconnection_output;  /* connection-output */

/* FIND-CONNECTION-CHANGES */
Object find_connection_changes()
{
    Object d_change, ab_loop_list_, deletion_p, d_path, deletion, d_input;
    Object d_output, a_change, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_list__1, addition_p, a_path, addition, a_input, a_output;

    x_note_fn_call(136,40);
    d_change = Nil;
    ab_loop_list_ = Xml_object_changes;
    deletion_p = Nil;
    d_path = Nil;
    deletion = Nil;
    d_input = Nil;
    d_output = Nil;
    a_change = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    d_change = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    deletion_p = EQ(FIRST(d_change),Qdeletion) ? T : Nil;
    d_path = deletion_p ? SECOND(d_change) : Nil;
    deletion = deletion_p ? THIRD(d_change) : Nil;
    d_input = deletion_p ? get_xml_object_attribute(deletion,
	    Qconnection_input,Nil,Nil) : Nil;
    d_output = deletion_p ? get_xml_object_attribute(deletion,
	    Qconnection_output,Nil,Nil) : Nil;
    if (deletion_p) {
	a_change = Nil;
	ab_loop_list__1 = Xml_object_changes;
	addition_p = Nil;
	a_path = Nil;
	addition = Nil;
	a_input = Nil;
	a_output = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	a_change = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	addition_p = EQ(FIRST(a_change),Qaddition) ? T : Nil;
	a_path = addition_p ? SECOND(a_change) : Nil;
	addition = addition_p ? FOURTH(a_change) : Nil;
	a_input = addition_p ? get_xml_object_attribute(addition,
		Qconnection_input,Nil,Nil) : Nil;
	a_output = addition_p ? get_xml_object_attribute(addition,
		Qconnection_output,Nil,Nil) : Nil;
	if (addition_p && equalw(CDR(d_path),CDR(a_path)) && 
		compare_xml_object_and_fixups(d_input,a_input,Nil) && 
		compare_xml_object_and_fixups(d_output,a_output,Nil))
	    goto end_1;
	goto next_loop_1;
      end_loop_1:
	a_change = Qnil;
      end_1:;
    }
    else
	a_change = Nil;
    if (a_change) {
	ab_loopvar__2 = gensym_cons_1(gensym_cons_1(d_change,a_change),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qcompare_xml_object_and_fixups;  /* compare-xml-object-and-fixups */

/* COMPARE-XML-OBJECT-AND-FIXUPS */
Object compare_xml_object_and_fixups(object_and_fixups_1,
	    object_and_fixups_2,collect_diffs_p)
    Object object_and_fixups_1, object_and_fixups_2, collect_diffs_p;
{
    Object xml_object_changes, compare_xml_collect_diffs_p, connection_changes;
    Object d_change, a_change, ab_loop_list_, ab_loop_desetq_, temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(136,41);
    xml_object_changes = Nil;
    compare_xml_collect_diffs_p = collect_diffs_p;
    PUSH_SPECIAL_WITH_SYMBOL(Compare_xml_collect_diffs_p,Qcompare_xml_collect_diffs_p,compare_xml_collect_diffs_p,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Xml_object_changes,Qxml_object_changes,xml_object_changes,
	      0);
	if (PUSH_CATCH(Qcompare_xml_object_and_fixups,0)) {
	    compare_xml_object_and_fixups_1(object_and_fixups_1,
		    object_and_fixups_2,Nil);
	    if ( !TRUEP(Compare_xml_collect_diffs_p)) {
		result = VALUES_1(T);
		POP_SPECIAL();
		POP_SPECIAL();
		POP_CATCH(0);
		goto end_compare_xml_object_and_fixups;
	    }
	    connection_changes = find_connection_changes();
	    d_change = Nil;
	    a_change = Nil;
	    ab_loop_list_ = connection_changes;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    d_change = CAR(ab_loop_desetq_);
	    a_change = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    Xml_object_changes = delete_gensym_element_1(d_change,
		    Xml_object_changes);
	    Xml_object_changes = delete_gensym_element_1(a_change,
		    Xml_object_changes);
	    temp = SECOND(d_change);
	    compare_xml_object_and_fixups_1(THIRD(d_change),
		    FOURTH(a_change),
		    copy_list_using_gensym_conses_1(CDR(temp)));
	    reclaim_xml_change(d_change);
	    reclaim_xml_change(a_change);
	    goto next_loop;
	  end_loop:;
	    result = nreverse(Xml_object_changes);
	}
	else
	    result = CATCH_VALUES();
	POP_CATCH(0);
      POP_SPECIAL();
    POP_SPECIAL();
  end_compare_xml_object_and_fixups:
    return result;
}

/* RECLAIM-XML-CHANGE */
Object reclaim_xml_change(change)
    Object change;
{
    Object e, ab_loop_list_;

    x_note_fn_call(136,42);
    e = Nil;
    ab_loop_list_ = SECOND(change);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    e = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_cons_1(e);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(SECOND(change));
    reclaim_gensym_list_1(change);
    return VALUES_1(Nil);
}

/* RECLAIM-XML-CHANGE-LIST */
Object reclaim_xml_change_list(changes)
    Object changes;
{
    Object change, ab_loop_list_;

    x_note_fn_call(136,43);
    change = Nil;
    ab_loop_list_ = changes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    change = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_xml_change(change);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(changes);
    return VALUES_1(Nil);
}

/* NOTE-XML-OBJECT-DIFFERENCE */
Object note_xml_object_difference(path,type,old,new_1)
    Object path, type, old, new_1;
{
    Object result;

    x_note_fn_call(136,44);
    if ( !TRUEP(Compare_xml_collect_diffs_p)) {
	result = VALUES_1(Nil);
	THROW(Qcompare_xml_object_and_fixups,result);
    }
    Xml_object_changes = gensym_cons_1(gensym_list_4(type,
	    copy_list_using_gensym_conses_1(path),old,new_1),
	    Xml_object_changes);
    return VALUES_1(Nil);
}

/* COMPARE-XML-OBJECT-AND-FIXUPS-1 */
Object compare_xml_object_and_fixups_1(object_and_fixups_1,
	    object_and_fixups_2,path)
    Object object_and_fixups_1, object_and_fixups_2, path;
{
    Object attr_p_1, attr_p_2, temp;

    x_note_fn_call(136,45);
    attr_p_1 = xml_object_has_attributes_p(object_and_fixups_1);
    attr_p_2 = xml_object_has_attributes_p(object_and_fixups_2);
    if (attr_p_1 && attr_p_2)
	compare_xml_object_and_fixups_2(object_and_fixups_1,
		object_and_fixups_2,path);
    else if (attr_p_1 || attr_p_2 ||  !TRUEP(evaluation_value_eql(2,
	    object_and_fixups_1,object_and_fixups_2))) {
	temp = get_xml_object(object_and_fixups_1);
	note_xml_object_difference(path,Qchange,temp,
		get_xml_object(object_and_fixups_2));
    }
    return VALUES_1(Nil);
}

/* COMPARE-XML-OBJECT-AND-FIXUPS-2 */
Object compare_xml_object_and_fixups_2(object_and_fixups_1,
	    object_and_fixups_2,path)
    Object object_and_fixups_1, object_and_fixups_2, path;
{
    Object object_and_fixups, object_and_fixups_vector, t_1, type_1, fixups;
    Object type, user_p_1, val_1, id_1, val_2, subpath, dot_uac_dot;
    Object dot_uac_index_dot, dot_uac_length_dot, dot_uac_sys_p_dot;
    Object dot_current_uac_dot, gensymed_symbol, gensymed_symbol_1;
    Object held_vector, attr_1_1, attribute_value, dot_last_user_p_dot;
    Object ab_loop_iter_flag_, t_2, type_2, user_p_2, id_2, attr_2_1;
    SI_Long attr_1, ab_loop_bind_, next_index, length_1, gensymed_symbol_2;
    SI_Long attr_2;
    char dot_only_system_attrs_p_dot;

    x_note_fn_call(136,46);
    object_and_fixups = object_and_fixups_1;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    t_1 = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(t_1,Qprimitive_value) || EQ(t_1,Qtext))
	type_1 = t_1;
    else if (EQ(t_1,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	type_1 = t_1;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	type_1 = t_1;
    }
    object_and_fixups = object_and_fixups_1;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (!(EQ(type,Qprimitive_value) || EQ(type,Qtext))) {
	if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (fixups) {
		user_p_1 = Nil;
		attr_1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		val_1 = Nil;
	      next_loop:
		if (attr_1 >= ab_loop_bind_)
		    goto end_loop;
		val_1 = evaluation_sequence_aref(fixups,FIX(attr_1));
		if ( !TRUEP(FIX(attr_1))) {
		    id_1 = id_of_xml_object(val_1);
		    val_2 = get_xml_object_from_id(object_and_fixups_2,
			    id_1,Attr_not_found);
		    subpath = gensym_cons_1(gensym_cons_1(Qid,id_1),path);
		    if (EQ(val_2,Attr_not_found))
			note_xml_object_difference(subpath,Qdeletion,val_1,
				Nil);
		    else
			compare_xml_object_and_fixups_1(val_1,val_2,subpath);
		    reclaim_gensym_cons_1(subpath);
		}
		else {
		    val_2 = get_xml_object_attribute(object_and_fixups_2,
			    FIX(attr_1),user_p_1,Attr_not_found);
		    subpath = gensym_cons_1(gensym_cons_1(type_1,
			    FIX(attr_1)),path);
		    if (EQ(val_2,Attr_not_found))
			note_xml_object_difference(subpath,
				Qattribute_deletion,val_1,Nil);
		    else
			compare_xml_object_and_fixups_1(val_1,val_2,subpath);
		    reclaim_gensym_cons_1(subpath);
		}
		attr_1 = attr_1 + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (fixups) {
		dot_uac_dot = structure_slot_1(object_and_fixups_vector,
			Quser_attribute_count,Nil);
		dot_only_system_attrs_p_dot =  !TRUEP(dot_uac_dot);
		dot_uac_index_dot = CONSP(dot_uac_dot) && 
			EQ(M_CDR(dot_uac_dot),Qsequence) ? 
			FIX((SI_Long)0L) : Nil;
		dot_uac_length_dot = dot_uac_index_dot ? 
			FIXNUM_SUB1(ISVREF(M_CAR(dot_uac_dot),
			(SI_Long)1L)) : Nil;
		dot_uac_sys_p_dot = FIXNUMP(dot_uac_dot) ? T : Nil;
		if (dot_only_system_attrs_p_dot)
		    dot_current_uac_dot = Nil;
		else if (dot_uac_index_dot) {
		    gensymed_symbol = M_CAR(dot_uac_dot);
		    gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
		    dot_current_uac_dot = 
			    FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(M_CAR(dot_uac_dot),
			    IFIX(FIXNUM_ADD(gensymed_symbol_1,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(gensymed_symbol,
			    (IFIX(gensymed_symbol_1) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(gensymed_symbol_1) & (SI_Long)1023L);
		}
		else if (dot_uac_sys_p_dot)
		    dot_current_uac_dot = FIX((SI_Long)2L);
		else
		    dot_current_uac_dot = Qnil;
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		attr_1_1 = Nil;
		attribute_value = Nil;
		val_1 = Nil;
		dot_last_user_p_dot = Nil;
		user_p_1 = Nil;
		ab_loop_iter_flag_ = T;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		attr_1_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_2 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 
			& (SI_Long)1023L);
		val_1 = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if ( !TRUEP(ab_loop_iter_flag_))
		    dot_last_user_p_dot = user_p_1;
		if (dot_only_system_attrs_p_dot)
		    user_p_1 = Nil;
		else if ((SI_Long)0L < IFIX(dot_current_uac_dot)) {
		    dot_current_uac_dot = FIXNUM_SUB1(dot_current_uac_dot);
		    user_p_1 = dot_last_user_p_dot;
		}
		else if (dot_uac_index_dot) {
		    dot_uac_index_dot = FIXNUM_ADD1(dot_uac_index_dot);
		    if (FIXNUM_LT(dot_uac_index_dot,dot_uac_length_dot)) {
			gensymed_symbol = M_CAR(dot_uac_dot);
			gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
			dot_current_uac_dot = 
				FIXNUM_SUB1(FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(M_CAR(dot_uac_dot),
				IFIX(FIXNUM_ADD(gensymed_symbol_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(gensymed_symbol,
				(IFIX(gensymed_symbol_1) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(gensymed_symbol_1) & (SI_Long)1023L));
		    }
		    else
			dot_current_uac_dot = Most_positive_fixnum;
		    user_p_1 =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		else if (dot_uac_sys_p_dot) {
		    dot_uac_sys_p_dot = Nil;
		    dot_current_uac_dot = FIXNUM_SUB1(dot_uac_dot);
		    user_p_1 =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		else {
		    dot_current_uac_dot = Most_positive_fixnum;
		    user_p_1 =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		if ( !TRUEP(attr_1_1)) {
		    id_1 = id_of_xml_object(val_1);
		    val_2 = get_xml_object_from_id(object_and_fixups_2,
			    id_1,Attr_not_found);
		    subpath = gensym_cons_1(gensym_cons_1(Qid,id_1),path);
		    if (EQ(val_2,Attr_not_found))
			note_xml_object_difference(subpath,Qdeletion,val_1,
				Nil);
		    else
			compare_xml_object_and_fixups_1(val_1,val_2,subpath);
		    reclaim_gensym_cons_1(subpath);
		}
		else {
		    val_2 = get_xml_object_attribute(object_and_fixups_2,
			    attr_1_1,user_p_1,Attr_not_found);
		    subpath = gensym_cons_1(gensym_cons_1(type_1,attr_1_1),
			    path);
		    if (EQ(val_2,Attr_not_found))
			note_xml_object_difference(subpath,
				Qattribute_deletion,val_1,Nil);
		    else
			compare_xml_object_and_fixups_1(val_1,val_2,subpath);
		    reclaim_gensym_cons_1(subpath);
		}
		ab_loop_iter_flag_ = Nil;
		goto next_loop_1;
	      end_loop_1:;
	    }
	}
    }
    object_and_fixups = object_and_fixups_2;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    t_2 = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(t_2,Qprimitive_value) || EQ(t_2,Qtext))
	type_2 = t_2;
    else if (EQ(t_2,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	type_2 = t_2;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	type_2 = t_2;
    }
    object_and_fixups = object_and_fixups_2;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (!(EQ(type,Qprimitive_value) || EQ(type,Qtext))) {
	if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (fixups) {
		user_p_2 = Nil;
		attr_2 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		val_2 = Nil;
	      next_loop_2:
		if (attr_2 >= ab_loop_bind_)
		    goto end_loop_2;
		val_2 = evaluation_sequence_aref(fixups,FIX(attr_2));
		if ( !TRUEP(FIX(attr_2))) {
		    id_2 = id_of_xml_object(val_2);
		    val_1 = get_xml_object_from_id(object_and_fixups_1,
			    id_2,Attr_not_found);
		    subpath = gensym_cons_1(gensym_cons_1(Qid,id_2),path);
		    if (EQ(val_1,Attr_not_found))
			note_xml_object_difference(subpath,Qaddition,Nil,
				val_2);
		    reclaim_gensym_cons_1(subpath);
		}
		else {
		    val_1 = get_xml_object_attribute(object_and_fixups_1,
			    FIX(attr_2),user_p_2,Attr_not_found);
		    subpath = gensym_cons_1(gensym_cons_1(type_2,
			    FIX(attr_2)),path);
		    if (EQ(val_1,Attr_not_found))
			note_xml_object_difference(subpath,
				Qattribute_addition,Nil,val_2);
		    reclaim_gensym_cons_1(subpath);
		}
		attr_2 = attr_2 + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
	    }
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (fixups) {
		dot_uac_dot = structure_slot_1(object_and_fixups_vector,
			Quser_attribute_count,Nil);
		dot_only_system_attrs_p_dot =  !TRUEP(dot_uac_dot);
		dot_uac_index_dot = CONSP(dot_uac_dot) && 
			EQ(M_CDR(dot_uac_dot),Qsequence) ? 
			FIX((SI_Long)0L) : Nil;
		dot_uac_length_dot = dot_uac_index_dot ? 
			FIXNUM_SUB1(ISVREF(M_CAR(dot_uac_dot),
			(SI_Long)1L)) : Nil;
		dot_uac_sys_p_dot = FIXNUMP(dot_uac_dot) ? T : Nil;
		if (dot_only_system_attrs_p_dot)
		    dot_current_uac_dot = Nil;
		else if (dot_uac_index_dot) {
		    gensymed_symbol = M_CAR(dot_uac_dot);
		    gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
		    dot_current_uac_dot = 
			    FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(M_CAR(dot_uac_dot),
			    IFIX(FIXNUM_ADD(gensymed_symbol_1,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(gensymed_symbol,
			    (IFIX(gensymed_symbol_1) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(gensymed_symbol_1) & (SI_Long)1023L);
		}
		else if (dot_uac_sys_p_dot)
		    dot_current_uac_dot = FIX((SI_Long)2L);
		else
		    dot_current_uac_dot = Qnil;
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		attr_2_1 = Nil;
		attribute_value = Nil;
		val_2 = Nil;
		dot_last_user_p_dot = Nil;
		user_p_2 = Nil;
		ab_loop_iter_flag_ = T;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_3:
		if (next_index >= length_1)
		    goto end_loop_3;
		attr_2_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_2 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 
			& (SI_Long)1023L);
		val_2 = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if ( !TRUEP(ab_loop_iter_flag_))
		    dot_last_user_p_dot = user_p_2;
		if (dot_only_system_attrs_p_dot)
		    user_p_2 = Nil;
		else if ((SI_Long)0L < IFIX(dot_current_uac_dot)) {
		    dot_current_uac_dot = FIXNUM_SUB1(dot_current_uac_dot);
		    user_p_2 = dot_last_user_p_dot;
		}
		else if (dot_uac_index_dot) {
		    dot_uac_index_dot = FIXNUM_ADD1(dot_uac_index_dot);
		    if (FIXNUM_LT(dot_uac_index_dot,dot_uac_length_dot)) {
			gensymed_symbol = M_CAR(dot_uac_dot);
			gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
			dot_current_uac_dot = 
				FIXNUM_SUB1(FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(M_CAR(dot_uac_dot),
				IFIX(FIXNUM_ADD(gensymed_symbol_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(gensymed_symbol,
				(IFIX(gensymed_symbol_1) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(gensymed_symbol_1) & (SI_Long)1023L));
		    }
		    else
			dot_current_uac_dot = Most_positive_fixnum;
		    user_p_2 =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		else if (dot_uac_sys_p_dot) {
		    dot_uac_sys_p_dot = Nil;
		    dot_current_uac_dot = FIXNUM_SUB1(dot_uac_dot);
		    user_p_2 =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		else {
		    dot_current_uac_dot = Most_positive_fixnum;
		    user_p_2 =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		}
		if ( !TRUEP(attr_2_1)) {
		    id_2 = id_of_xml_object(val_2);
		    val_1 = get_xml_object_from_id(object_and_fixups_1,
			    id_2,Attr_not_found);
		    subpath = gensym_cons_1(gensym_cons_1(Qid,id_2),path);
		    if (EQ(val_1,Attr_not_found))
			note_xml_object_difference(subpath,Qaddition,Nil,
				val_2);
		    reclaim_gensym_cons_1(subpath);
		}
		else {
		    val_1 = get_xml_object_attribute(object_and_fixups_1,
			    attr_2_1,user_p_2,Attr_not_found);
		    subpath = gensym_cons_1(gensym_cons_1(type_2,attr_2_1),
			    path);
		    if (EQ(val_1,Attr_not_found))
			note_xml_object_difference(subpath,
				Qattribute_addition,Nil,val_2);
		    reclaim_gensym_cons_1(subpath);
		}
		ab_loop_iter_flag_ = Nil;
		goto next_loop_3;
	      end_loop_3:;
	    }
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(All_xml_checksums, Qall_xml_checksums);

/* ADD-XML-CHECKSUM */
Object add_xml_checksum(name,var_name)
    Object name, var_name;
{
    x_note_fn_call(136,47);
    if ( !TRUEP(memq_function(name,All_xml_checksums)))
	All_xml_checksums = nconc2(All_xml_checksums,LIST_1(CONS(name,
		var_name)));
    return VALUES_1(name);
}

DEFINE_VARIABLE_WITH_SYMBOL(Attribute_name_xml_checksum, Qattribute_name_xml_checksum);

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_xml_checksum, Quuid_xml_checksum);

DEFINE_VARIABLE_WITH_SYMBOL(Value_xml_checksum, Qvalue_xml_checksum);

DEFINE_VARIABLE_WITH_SYMBOL(Text_xml_checksum, Qtext_xml_checksum);

DEFINE_VARIABLE_WITH_SYMBOL(Binary_xml_checksum, Qbinary_xml_checksum);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_checksums_enabled_p, Qxml_checksums_enabled_p);

DEFINE_VARIABLE_WITH_SYMBOL(Process_checksum_for_image_data_p, Qprocess_checksum_for_image_data_p);

Object Debug_xml_checksums_p = UNBOUND;

/* INITIALIZE-ALL-XML-CHECKSUMS */
Object initialize_all_xml_checksums()
{
    Object name, var_name, ab_loop_list_, index_plus_result_plus_debug;
    Object ab_loop_desetq_, fourth_new_value;

    x_note_fn_call(136,48);
    if (Xml_checksums_enabled_p) {
	name = Nil;
	var_name = Nil;
	ab_loop_list_ = All_xml_checksums;
	index_plus_result_plus_debug = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	name = CAR(ab_loop_desetq_);
	var_name = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	index_plus_result_plus_debug = SYMBOL_VALUE(var_name);
	g2ext_init_g2_MD5_context(IFIX(FIRST(index_plus_result_plus_debug)));
	reclaim_eval_list_1(FOURTH(index_plus_result_plus_debug));
	fourth_new_value = THIRD(index_plus_result_plus_debug);
	M_FOURTH(index_plus_result_plus_debug) = fourth_new_value;
	M_THIRD(index_plus_result_plus_debug) = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* FINALIZE-ALL-XML-CHECKSUMS */
Object finalize_all_xml_checksums()
{
    Object name, var_name, ab_loop_list_, index_plus_result_plus_debug;
    Object ab_loop_desetq_, second_new_value;

    x_note_fn_call(136,49);
    if (Xml_checksums_enabled_p) {
	name = Nil;
	var_name = Nil;
	ab_loop_list_ = All_xml_checksums;
	index_plus_result_plus_debug = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	name = CAR(ab_loop_desetq_);
	var_name = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	index_plus_result_plus_debug = SYMBOL_VALUE(var_name);
	if ( !TRUEP(SECOND(index_plus_result_plus_debug))) {
	    second_new_value = obtain_simple_gensym_string(FIX((SI_Long)16L));
	    M_SECOND(index_plus_result_plus_debug) = second_new_value;
	}
	finalize_indexed_md5_context(FIRST(index_plus_result_plus_debug),
		SECOND(index_plus_result_plus_debug));
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_19;  /* ";" */

static Object string_constant_20;  /* "[[ ~d  ~s ]]" */

/* UPDATE-XML-CHECKSUM-WITH-TEXT-STRING */
Object update_xml_checksum_with_text_string(index_plus_result_plus_debug,
	    text_string,object)
    Object index_plus_result_plus_debug, text_string, object;
{
    Object eval_push_modify_macro_arg, car_1, cdr_1, third_new_value;
    SI_Long temp;

    x_note_fn_call(136,50);
    if (Process_checksum_for_image_data_p && Xml_checksums_enabled_p) {
	update_indexed_md5_context(FIRST(index_plus_result_plus_debug),
		string_constant_19);
	temp = IFIX(FIRST(index_plus_result_plus_debug));
	g2ext_update_g2_MD5_context_wide(temp,
		UBYTE_16_SARRAY_TO_USHORT_PTR(text_string),
		IFIX(lengthw(text_string)));
	if (Debug_xml_checksums_p) {
	    eval_push_modify_macro_arg = FIXNUMP(object) || object && 
		    SYMBOLP(object) || SIMPLE_VECTOR_P(object) ? object : 
		    copy_if_evaluation_value_1(object);
	    car_1 = eval_push_modify_macro_arg;
	    cdr_1 = THIRD(index_plus_result_plus_debug);
	    third_new_value = eval_cons_1(car_1,cdr_1);
	    M_THIRD(index_plus_result_plus_debug) = third_new_value;
	}
	if (Debug_clear_text_checksums)
	    notify_user_at_console(3,string_constant_20,
		    FIRST(index_plus_result_plus_debug),text_string);
    }
    return VALUES_1(Nil);
}

/* UPDATE-XML-CHECKSUM-WITH-PRIMITIVE-OBJECT */
Object update_xml_checksum_with_primitive_object(index_plus_result_plus_debug,
	    object)
    Object index_plus_result_plus_debug, object;
{
    Object text_string;

    x_note_fn_call(136,51);
    if (Process_checksum_for_image_data_p) {
	text_string = text_string_for_xml_primitive_value(object);
	update_xml_checksum_with_text_string(index_plus_result_plus_debug,
		text_string,object);
	reclaim_text_string(text_string);
    }
    return VALUES_1(Nil);
}

/* UPDATE-XML-CHECKSUM-WITH-SYMBOL */
Object update_xml_checksum_with_symbol(index_plus_result_plus_debug,symbol)
    Object index_plus_result_plus_debug, symbol;
{
    x_note_fn_call(136,52);
    if (Process_checksum_for_image_data_p)
	update_xml_checksum_with_text_string(index_plus_result_plus_debug,
		symbol_name_text_string(symbol),symbol);
    return VALUES_1(Nil);
}

/* GET-XML-CHECKSUM */
Object get_xml_checksum(index_plus_result_plus_debug)
    Object index_plus_result_plus_debug;
{
    Object digest, result_1, digest_index;
    SI_Long index_1, aref_new_value;

    x_note_fn_call(136,53);
    if (Xml_checksums_enabled_p) {
	digest = SECOND(index_plus_result_plus_debug);
	result_1 = obtain_text_string(FIX((SI_Long)8L));
	index_1 = (SI_Long)0L;
	digest_index = Nil;
      next_loop:
	if (index_1 >= (SI_Long)8L)
	    goto end_loop;
	digest_index = FIX(index_1 << (SI_Long)1L);
	aref_new_value = (IFIX(CHAR_CODE(SCHAR(digest,digest_index))) << 
		(SI_Long)8L) + IFIX(CHAR_CODE(SCHAR(digest,
		FIXNUM_ADD1(digest_index))));
	UBYTE_16_ISASET_1(result_1,index_1,aref_new_value);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(result_1);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-XML-CHECKSUM-DEBUG-INFO */
Object get_xml_checksum_debug_info(index_plus_result_plus_debug,recent_p)
    Object index_plus_result_plus_debug, recent_p;
{
    x_note_fn_call(136,54);
    return copy_list_using_eval_conses_1(recent_p ? 
	    THIRD(index_plus_result_plus_debug) : 
	    FOURTH(index_plus_result_plus_debug));
}

/* GET-TEXT-FOR-XML-CHECKSUM */
Object get_text_for_xml_checksum(index_plus_result_plus_debug)
    Object index_plus_result_plus_debug;
{
    Object text_string, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(136,55);
    text_string = index_plus_result_plus_debug ? 
	    get_xml_checksum(index_plus_result_plus_debug) : 
	    make_empty_checksum();
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      twrite_uuid_printed_representation(text_string);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_text_string(text_string);
    return VALUES_1(temp);
}

/* MAKE-EMPTY-CHECKSUM */
Object make_empty_checksum()
{
    Object temp;

    x_note_fn_call(136,56);
    temp = make_stringw_function(FIX((SI_Long)8L),FIX((SI_Long)0L));
    return VALUES_1(temp);
}

/* RECLAIM-XML-CHECKSUM */
Object reclaim_xml_checksum(text_string_qm)
    Object text_string_qm;
{
    x_note_fn_call(136,57);
    if (text_string_qm)
	reclaim_text_string(text_string_qm);
    return VALUES_1(Nil);
}

static Object QModule;             /* |Module| */

static Object QCHECKSUMS;          /* |checksums| */

/* ADD-CHECKSUMS-TO-XML-OBJECT */
Object add_checksums_to_xml_object(xml_object,checksums)
    Object xml_object, checksums;
{
    Object module_fixups;

    x_note_fn_call(136,58);
    module_fixups = get_xml_fixups(xml_object,QModule,Nil);
    if (module_fixups) {
	replace_xml_fixups(module_fixups,QCHECKSUMS,
		make_xml_object_for_evaluation_value(checksums));
	if ( !(FIXNUMP(checksums) || SYMBOLP(checksums) || 
		SIMPLE_VECTOR_P(checksums)))
	    reclaim_if_evaluation_value_1(checksums);
    }
    return VALUES_1(xml_object);
}

/* GET-CHECKSUMS-FROM-XML-OBJECT */
Object get_checksums_from_xml_object(xml_object)
    Object xml_object;
{
    x_note_fn_call(136,59);
    return get_xml_fixups(get_xml_fixups(xml_object,QModule,Nil),
	    QCHECKSUMS,Nil);
}

/* CHECKSUMS-DIFFER-P */
Object checksums_differ_p(checksum1,checksum2)
    Object checksum1, checksum2;
{
    Object name, var_name, ab_loop_list_, checksum_sequence_1;
    Object checksum_sequence_2, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_;

    x_note_fn_call(136,60);
    name = Nil;
    var_name = Nil;
    ab_loop_list_ = All_xml_checksums;
    checksum_sequence_1 = Nil;
    checksum_sequence_2 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    var_name = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    checksum_sequence_1 = get_xml_object(get_xml_fixups(checksum1,name,Nil));
    checksum_sequence_2 = get_xml_object(get_xml_fixups(checksum2,name,Nil));
    if (checksum_sequence_1 && checksum_sequence_2 &&  
	    !TRUEP(evaluation_value_eq(checksum_sequence_1,
	    checksum_sequence_2))) {
	ab_loopvar__2 = gensym_cons_1(name,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* CHECK-XML-OBJECT-CHECKSUMS */
Object check_xml_object_checksums(xml_object)
    Object xml_object;
{
    Object found_checksums, computed_checksums, temp;

    x_note_fn_call(136,61);
    found_checksums = get_checksums_from_xml_object(xml_object);
    computed_checksums = 
	    make_xml_object_for_evaluation_value(compute_checksums_for_xml_object(xml_object,
	    Nil));
    temp = checksums_differ_p(found_checksums,computed_checksums);
    reclaim_xml_object_and_fixups(computed_checksums);
    return VALUES_1(temp);
}

/* GET-XML-CHECKSUM-INFORMATION */
Object get_xml_checksum_information()
{
    Object name, var_name, ab_loop_list_, checksum, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp;

    x_note_fn_call(136,62);
    if (Write_checksums_in_xml_file_p) {
	name = Nil;
	var_name = Nil;
	ab_loop_list_ = All_xml_checksums;
	checksum = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	name = CAR(ab_loop_desetq_);
	var_name = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	checksum = get_text_for_xml_checksum(Nil);
	ab_loopvar__2 = eval_list_2(name,checksum);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	return allocate_evaluation_structure(temp);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmodule;             /* module */

/* COMPUTE-CHECKSUMS-FOR-XML-OBJECT-1 */
Object compute_checksums_for_xml_object_1(xml_object)
    Object xml_object;
{
    Object object_and_fixups, object_and_fixups_vector, type, unit, object;
    Object fixups, user_p, value, dot_uac_dot, dot_uac_index_dot;
    Object dot_uac_length_dot, dot_uac_sys_p_dot, dot_current_uac_dot;
    Object gensymed_symbol, gensymed_symbol_1, held_vector, name_1;
    Object attribute_value, dot_last_user_p_dot, ab_loop_iter_flag_;
    SI_Long name, ab_loop_bind_, next_index, length_1, gensymed_symbol_2;
    char dot_only_system_attrs_p_dot;

    x_note_fn_call(136,63);
    object_and_fixups = xml_object;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    unit = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil) : Nil;
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext)) {
	if (EQ(type,Qtext) && text_string_p(object))
	    return update_xml_checksum_with_text_string(Text_xml_checksum,
		    object,object);
	else {
	    update_xml_checksum_with_symbol(Value_xml_checksum,type);
	    if (unit)
		update_xml_checksum_with_symbol(Value_xml_checksum,unit);
	    return update_xml_checksum_with_primitive_object(Value_xml_checksum,
		    object);
	}
    }
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	update_xml_checksum_with_symbol(Attribute_name_xml_checksum,type);
	if (EQ(type,Qbinary))
	    return compute_checksums_for_xml_object_2(object);
	else if (fixups) {
	    user_p = Nil;
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop:
	    if (name >= ab_loop_bind_)
		goto end_loop;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    compute_image_data_checksum_qm(type,FIX(name),value);
	    if (SYMBOLP(FIX(name)))
		update_xml_checksum_with_symbol(Attribute_name_xml_checksum,
			FIX(name));
	    else
		update_xml_checksum_with_primitive_object(Attribute_name_xml_checksum,
			FIX(name));
	    if (EQ(type,Qmodule) && EQ(FIX(name),QCHECKSUMS));
	    else if (EQ(type,Qitem) && EQ(FIX(name),Qab_class) && 
		    SYMBOLP(value))
		update_xml_checksum_with_symbol(Attribute_name_xml_checksum,
			value);
	    else if ( !TRUEP(user_p) && (EQ(FIX(name),Qid) || EQ(FIX(name),
		    QRDF_COL_RESOURCE)) && text_string_p(value))
		update_xml_checksum_with_text_string(Uuid_xml_checksum,
			value,value);
	    else
		compute_checksums_for_xml_object_1(value);
	    name = name + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	update_xml_checksum_with_symbol(Attribute_name_xml_checksum,type);
	if (EQ(type,Qbinary))
	    return compute_checksums_for_xml_object_2(object);
	else if (fixups) {
	    dot_uac_dot = structure_slot_1(object_and_fixups_vector,
		    Quser_attribute_count,Nil);
	    dot_only_system_attrs_p_dot =  !TRUEP(dot_uac_dot);
	    dot_uac_index_dot = CONSP(dot_uac_dot) && 
		    EQ(M_CDR(dot_uac_dot),Qsequence) ? FIX((SI_Long)0L) : Nil;
	    dot_uac_length_dot = dot_uac_index_dot ? 
		    FIXNUM_SUB1(ISVREF(M_CAR(dot_uac_dot),(SI_Long)1L)) : Nil;
	    dot_uac_sys_p_dot = FIXNUMP(dot_uac_dot) ? T : Nil;
	    if (dot_only_system_attrs_p_dot)
		dot_current_uac_dot = Nil;
	    else if (dot_uac_index_dot) {
		gensymed_symbol = M_CAR(dot_uac_dot);
		gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
		dot_current_uac_dot = FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(M_CAR(dot_uac_dot),
			IFIX(FIXNUM_ADD(gensymed_symbol_1,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(gensymed_symbol,
			(IFIX(gensymed_symbol_1) >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),IFIX(gensymed_symbol_1) & (SI_Long)1023L);
	    }
	    else if (dot_uac_sys_p_dot)
		dot_current_uac_dot = FIX((SI_Long)2L);
	    else
		dot_current_uac_dot = Qnil;
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    dot_last_user_p_dot = Nil;
	    user_p = Nil;
	    ab_loop_iter_flag_ = T;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_2 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_2 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		dot_last_user_p_dot = user_p;
	    if (dot_only_system_attrs_p_dot)
		user_p = Nil;
	    else if ((SI_Long)0L < IFIX(dot_current_uac_dot)) {
		dot_current_uac_dot = FIXNUM_SUB1(dot_current_uac_dot);
		user_p = dot_last_user_p_dot;
	    }
	    else if (dot_uac_index_dot) {
		dot_uac_index_dot = FIXNUM_ADD1(dot_uac_index_dot);
		if (FIXNUM_LT(dot_uac_index_dot,dot_uac_length_dot)) {
		    gensymed_symbol = M_CAR(dot_uac_dot);
		    gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
		    dot_current_uac_dot = 
			    FIXNUM_SUB1(FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(M_CAR(dot_uac_dot),
			    IFIX(FIXNUM_ADD(gensymed_symbol_1,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(gensymed_symbol,
			    (IFIX(gensymed_symbol_1) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(gensymed_symbol_1) & (SI_Long)1023L));
		}
		else
		    dot_current_uac_dot = Most_positive_fixnum;
		user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
	    }
	    else if (dot_uac_sys_p_dot) {
		dot_uac_sys_p_dot = Nil;
		dot_current_uac_dot = FIXNUM_SUB1(dot_uac_dot);
		user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
	    }
	    else {
		dot_current_uac_dot = Most_positive_fixnum;
		user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
	    }
	    compute_image_data_checksum_qm(type,name_1,value);
	    if (SYMBOLP(name_1))
		update_xml_checksum_with_symbol(Attribute_name_xml_checksum,
			name_1);
	    else if (FIXNUMP(name_1))
		update_xml_checksum_with_primitive_object(Attribute_name_xml_checksum,
			name_1);
	    if (EQ(type,Qmodule) && EQ(name_1,QCHECKSUMS));
	    else if (EQ(type,Qitem) && EQ(name_1,Qab_class) && SYMBOLP(value))
		update_xml_checksum_with_symbol(Attribute_name_xml_checksum,
			value);
	    else if ( !TRUEP(user_p) && (EQ(name_1,Qid) || EQ(name_1,
		    QRDF_COL_RESOURCE)) && text_string_p(value))
		update_xml_checksum_with_text_string(Uuid_xml_checksum,
			value,value);
	    else
		compute_checksums_for_xml_object_1(value);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qimage_data;         /* image-data */

static Object Qsave_image_data_with_kb;  /* save-image-data-with-kb */

/* COMPUTE-IMAGE-DATA-CHECKSUM? */
Object compute_image_data_checksum_qm(type,name,value)
    Object type, name, value;
{
    x_note_fn_call(136,64);
    if (EQ(Qitem,type)) {
	if (EQ(Qimage_data,name) &&  !TRUEP(get_xml_object_attribute(value,
		Qsave_image_data_with_kb,Nil,Nil))) {
	    Process_checksum_for_image_data_p = Nil;
	    return VALUES_1(Process_checksum_for_image_data_p);
	}
	else {
	    Process_checksum_for_image_data_p = T;
	    return VALUES_1(Process_checksum_for_image_data_p);
	}
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-CHECKSUMS-FOR-XML-OBJECT-2 */
Object compute_checksums_for_xml_object_2(value)
    Object value;
{
    Object gensymed_symbol, held_vector, element, elt_1, validated_elt, a_name;
    Object attribute_value, a_value;
    SI_Long next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(136,65);
    if (text_string_p(value))
	return update_xml_checksum_with_text_string(Binary_xml_checksum,
		value,value);
    else if (CONSP(value) && EQ(M_CDR(value),Qsequence)) {
	gensymed_symbol = value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	compute_checksums_for_xml_object_2(element);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (CONSP(value) && EQ(M_CDR(value),Qab_structure)) {
	gensymed_symbol = value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	a_name = Nil;
	attribute_value = Nil;
	a_value = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	a_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	a_value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	compute_checksums_for_xml_object_2(a_name);
	compute_checksums_for_xml_object_2(a_value);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return update_xml_checksum_with_primitive_object(Binary_xml_checksum,
		value);
}

/* COMPUTE-CHECKSUMS-FOR-XML-OBJECT */
Object compute_checksums_for_xml_object(xml_object,module_qm)
    Object xml_object, module_qm;
{
    Object xml_checksums_enabled_p, process_checksum_for_image_data_p;
    Object checksums_to_exclude, name, var_name, ab_loop_list_;
    Object exclude_checksum_p, checksum, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(136,66);
    xml_checksums_enabled_p = T;
    process_checksum_for_image_data_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Process_checksum_for_image_data_p,Qprocess_checksum_for_image_data_p,process_checksum_for_image_data_p,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Xml_checksums_enabled_p,Qxml_checksums_enabled_p,xml_checksums_enabled_p,
	      2);
	xml_checksums_enabled_p = T;
	process_checksum_for_image_data_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Process_checksum_for_image_data_p,Qprocess_checksum_for_image_data_p,process_checksum_for_image_data_p,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Xml_checksums_enabled_p,Qxml_checksums_enabled_p,xml_checksums_enabled_p,
		  0);
	    initialize_all_xml_checksums();
	    compute_checksums_for_xml_object_1(xml_object);
	    finalize_all_xml_checksums();
	  POP_SPECIAL();
	POP_SPECIAL();
	checksums_to_exclude = module_qm ? 
		get_kb_has_been_loaded_from_clear_text_with_differences(module_qm) 
		: Nil;
	name = Nil;
	var_name = Nil;
	ab_loop_list_ = All_xml_checksums;
	exclude_checksum_p = Nil;
	checksum = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	name = CAR(ab_loop_desetq_);
	var_name = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	exclude_checksum_p = memq_function(name,checksums_to_exclude);
	checksum =  !TRUEP(exclude_checksum_p) ? 
		get_text_for_xml_checksum(SYMBOL_VALUE(var_name)) : Nil;
	if ( !TRUEP(exclude_checksum_p)) {
	    ab_loopvar__2 = eval_list_2(name,checksum);
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	}
	goto next_loop;
      end_loop:
	reclaim_gensym_list_1(checksums_to_exclude);
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	result = allocate_evaluation_structure(temp);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* SEQUENCE-OF-BINARY-TEXT-STRINGS-P */
Object sequence_of_binary_text_strings_p(x)
    Object x;
{
    Object gensymed_symbol, held_vector, element, elt_1, validated_elt, temp_1;
    SI_Long next_index, length_1, length_2;
    char temp;

    x_note_fn_call(136,67);
    if (CONSP(x) && EQ(M_CDR(x),Qsequence) && (SI_Long)0L < 
	    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(x),(SI_Long)1L)))) {
	gensymed_symbol = x;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(element) != (SI_Long)0L) {
	    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element));
	    temp = (SI_Long)1L == UBYTE_16_ISAREF_1(element,
		    UBYTE_16_ISAREF_1(element,length_2 - (SI_Long)2L) + 
		    ((UBYTE_16_ISAREF_1(element,length_2 - (SI_Long)1L) & 
		    (SI_Long)8191L) << (SI_Long)16L));
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    temp_1 = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = T;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2binary_file_name, Qg2binary_file_name);

DEFINE_VARIABLE_WITH_SYMBOL(G2binary_file_position, Qg2binary_file_position);

DEFINE_VARIABLE_WITH_SYMBOL(Current_g2binary_file_symbol_index, Qcurrent_g2binary_file_symbol_index);

DEFINE_VARIABLE_WITH_SYMBOL(G2binary_file_symbol_list, Qg2binary_file_symbol_list);

DEFINE_VARIABLE_WITH_SYMBOL(G2binary_file_symbol_index_space, Qg2binary_file_symbol_index_space);

Object G2binary_file_symbol_index_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Using_temporary_g2binary_file_symbol_indices_p, Qusing_temporary_g2binary_file_symbol_indices_p);

DEFINE_VARIABLE_WITH_SYMBOL(Temporary_g2binary_file_symbol_indices, Qtemporary_g2binary_file_symbol_indices);

static Object Qg2binary_file_symbol_index;  /* g2binary-file-symbol-index */

/* GET-G2BINARY-FILE-SYMBOL-INDEX */
Object get_g2binary_file_symbol_index(symbol,skip_lookup_p)
    Object symbol, skip_lookup_p;
{
    Object temp, current_g2binary_file_symbol_index_new_value;

    x_note_fn_call(136,68);
    temp =  !TRUEP(skip_lookup_p) ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qg2binary_file_symbol_index) : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	temp = mutate_global_property(symbol,
		Current_g2binary_file_symbol_index,
		Qg2binary_file_symbol_index);
	if (Using_temporary_g2binary_file_symbol_indices_p)
	    Temporary_g2binary_file_symbol_indices = gensym_cons_1(symbol,
		    Temporary_g2binary_file_symbol_indices);
	else
	    G2binary_file_symbol_list = gensym_cons_1(symbol,
		    G2binary_file_symbol_list);
	current_g2binary_file_symbol_index_new_value = 
		FIXNUM_ADD1(Current_g2binary_file_symbol_index);
	Current_g2binary_file_symbol_index = 
		current_g2binary_file_symbol_index_new_value;
	return VALUES_1(temp);
    }
}

/* SET-G2BINARY-FILE-SYMBOL-FOR-INDEX */
Object set_g2binary_file_symbol_for_index(index_1,symbol)
    Object index_1, symbol;
{
    Object svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(136,69);
    if ( !TRUEP(G2binary_file_symbol_index_space))
	G2binary_file_symbol_index_space = make_index_space_1(Nil,Nil);
    if (FIXNUM_GE(index_1,ISVREF(G2binary_file_symbol_index_space,
	    (SI_Long)4L)))
	enlarge_index_space(G2binary_file_symbol_index_space,index_1);
    svref_arg_1 = ISVREF(ISVREF(G2binary_file_symbol_index_space,
	    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = symbol);
}

/* GET-G2BINARY-FILE-SYMBOL-FOR-INDEX */
Object get_g2binary_file_symbol_for_index(index_1)
    Object index_1;
{
    x_note_fn_call(136,70);
    if (G2binary_file_symbol_index_space) {
	if (FIXNUM_GE(index_1,ISVREF(G2binary_file_symbol_index_space,
		(SI_Long)4L)))
	    enlarge_index_space(G2binary_file_symbol_index_space,index_1);
	return VALUES_1(ISVREF(ISVREF(ISVREF(G2binary_file_symbol_index_space,
		(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		IFIX(index_1) & (SI_Long)1023L));
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_21;  /* "Could not open ~A for writing" */

/* MAYBE-OPEN-BINARY-OUTPUT-STREAM */
Object maybe_open_binary_output_stream()
{
    Object stream;

    x_note_fn_call(136,71);
    if (text_string_p(G2binary_file_stream)) {
	stream = g2_stream_open_for_binary_output(G2binary_file_stream);
	if ( !TRUEP(stream))
	    notify_user(2,string_constant_21,G2binary_file_stream);
	G2binary_file_stream = stream;
	if (stream)
	    return write_g2binary_file_header();
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_22;  /* "Could not open ~A for reading" */

/* MAYBE-OPEN-BINARY-INPUT-STREAM */
Object maybe_open_binary_input_stream()
{
    Object stream, error_string_qm;

    x_note_fn_call(136,72);
    if (text_string_p(G2binary_file_stream)) {
	stream = g2_stream_open_for_binary_input(G2binary_file_stream);
	G2binary_file_stream = stream;
	if ( !TRUEP(stream))
	    return tformat_text_string(2,string_constant_22,
		    G2binary_file_name);
	error_string_qm = read_g2binary_file_header();
	if (error_string_qm)
	    return VALUES_1(error_string_qm);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_23;  /* "Error reading ~A: size error" */

/* REPORT-G2BINARY-SIZE-ERROR */
Object report_g2binary_size_error()
{
    x_note_fn_call(136,73);
    return tformat_text_string(2,string_constant_23,G2binary_file_name);
}

static Object string_constant_24;  /* "Error reading ~A: ~A" */

/* REPORT-G2BINARY-ERROR */
Object report_g2binary_error(error_string)
    Object error_string;
{
    x_note_fn_call(136,74);
    return tformat_text_string(3,string_constant_24,G2binary_file_name,
	    error_string);
}

/* MAYBE-CLOSE-BINARY-STREAM */
Object maybe_close_binary_stream()
{
    Object temp;

    x_note_fn_call(136,75);
    temp =  !TRUEP(G2binary_file_stream) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (text_string_p(G2binary_file_stream)) {
	G2binary_file_stream = Nil;
	return VALUES_1(G2binary_file_stream);
    }
    else {
	g2_stream_close(G2binary_file_stream);
	G2binary_file_stream = Nil;
	return VALUES_1(G2binary_file_stream);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Remaining_bytes_in_g2binary_data, Qremaining_bytes_in_g2binary_data);

/* WRITE-FIXNUM-TO-G2BINARY-STREAM */
Object write_fixnum_to_g2binary_stream(fixnum,stream)
    Object fixnum, stream;
{
    SI_Long gensymed_symbol;

    x_note_fn_call(136,76);
    gensymed_symbol = (SI_Long)255L & IFIX(fixnum) >>  -  - (SI_Long)24L;
    g2_stream_write_char(CODE_CHAR(FIX(gensymed_symbol)),stream);
    gensymed_symbol = (SI_Long)255L & IFIX(fixnum) >>  -  - (SI_Long)16L;
    g2_stream_write_char(CODE_CHAR(FIX(gensymed_symbol)),stream);
    gensymed_symbol = (SI_Long)255L & IFIX(fixnum) >>  -  - (SI_Long)8L;
    g2_stream_write_char(CODE_CHAR(FIX(gensymed_symbol)),stream);
    gensymed_symbol = (SI_Long)255L & IFIX(fixnum);
    g2_stream_write_char(CODE_CHAR(FIX(gensymed_symbol)),stream);
    return VALUES_1(fixnum);
}

/* READ-FIXNUM-FROM-G2BINARY-STREAM */
Object read_fixnum_from_g2binary_stream(stream)
    Object stream;
{
    Object temp, byte_1;
    SI_Long remaining_bytes_in_g2binary_data_new_value, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(136,77);
    if (Remaining_bytes_in_g2binary_data) {
	remaining_bytes_in_g2binary_data_new_value = 
		IFIX(Remaining_bytes_in_g2binary_data) - (SI_Long)4L;
	Remaining_bytes_in_g2binary_data = 
		FIX(remaining_bytes_in_g2binary_data_new_value);
	if ( !((SI_Long)0L <= IFIX(Remaining_bytes_in_g2binary_data))) {
	    temp = report_g2binary_size_error();
	    return VALUES_2(Nil,temp);
	}
    }
    temp = g2_stream_read_char(stream);
    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code))
	return most_recent_file_operation_status_as_text();
    byte_1 = CHAR_CODE(temp);
    gensymed_symbol = (SI_Long)128L & IFIX(byte_1);
    gensymed_symbol = (SI_Long)128L == gensymed_symbol ? 
	    IFIX(FIXNUM_LOGIOR(FIX((SI_Long)-256L),byte_1)) : IFIX(byte_1);
    gensymed_symbol_1 = (SI_Long)24L;
    gensymed_symbol = gensymed_symbol << gensymed_symbol_1;
    temp = g2_stream_read_char(stream);
    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code))
	return most_recent_file_operation_status_as_text();
    gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) << (SI_Long)16L;
    temp = g2_stream_read_char(stream);
    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code))
	return most_recent_file_operation_status_as_text();
    gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) << (SI_Long)8L;
    temp = g2_stream_read_char(stream);
    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code))
	return most_recent_file_operation_status_as_text();
    gensymed_symbol_3 = IFIX(CHAR_CODE(temp));
    return VALUES_1(FIX(gensymed_symbol | gensymed_symbol_1 | 
	    gensymed_symbol_2 | gensymed_symbol_3));
}

/* WRITE-16BIT-UNSIGNED-INTEGER-TO-G2BINARY-STREAM */
Object write_16bit_unsigned_integer_to_g2binary_stream(integer,stream)
    Object integer, stream;
{
    SI_Long gensymed_symbol;

    x_note_fn_call(136,78);
    gensymed_symbol = (SI_Long)255L & IFIX(integer) >>  -  - (SI_Long)8L;
    g2_stream_write_char(CODE_CHAR(FIX(gensymed_symbol)),stream);
    gensymed_symbol = (SI_Long)255L & IFIX(integer);
    g2_stream_write_char(CODE_CHAR(FIX(gensymed_symbol)),stream);
    return VALUES_1(integer);
}

/* READ-16BIT-UNSIGNED-INTEGER-FROM-G2BINARY-STREAM */
Object read_16bit_unsigned_integer_from_g2binary_stream(stream)
    Object stream;
{
    Object temp;
    SI_Long remaining_bytes_in_g2binary_data_new_value, temp_1;

    x_note_fn_call(136,79);
    if (Remaining_bytes_in_g2binary_data) {
	remaining_bytes_in_g2binary_data_new_value = 
		IFIX(Remaining_bytes_in_g2binary_data) - (SI_Long)2L;
	Remaining_bytes_in_g2binary_data = 
		FIX(remaining_bytes_in_g2binary_data_new_value);
	if ( !((SI_Long)0L <= IFIX(Remaining_bytes_in_g2binary_data))) {
	    temp = report_g2binary_size_error();
	    return VALUES_2(Nil,temp);
	}
    }
    temp = g2_stream_read_char(stream);
    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code))
	return most_recent_file_operation_status_as_text();
    temp_1 = IFIX(CHAR_CODE(temp)) << (SI_Long)8L;
    temp = g2_stream_read_char(stream);
    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code))
	return most_recent_file_operation_status_as_text();
    return VALUES_1(FIX(temp_1 | IFIX(CHAR_CODE(temp))));
}

/* WRITE-8BIT-UNSIGNED-INTEGER-TO-G2BINARY-STREAM */
Object write_8bit_unsigned_integer_to_g2binary_stream(code,stream)
    Object code, stream;
{
    x_note_fn_call(136,80);
    return g2_stream_write_char(CODE_CHAR(code),stream);
}

/* READ-8BIT-UNSIGNED-INTEGER-FROM-G2BINARY-STREAM */
Object read_8bit_unsigned_integer_from_g2binary_stream(stream)
    Object stream;
{
    Object remaining_bytes_in_g2binary_data_new_value, temp;

    x_note_fn_call(136,81);
    if (Remaining_bytes_in_g2binary_data) {
	remaining_bytes_in_g2binary_data_new_value = 
		FIXNUM_SUB1(Remaining_bytes_in_g2binary_data);
	Remaining_bytes_in_g2binary_data = 
		remaining_bytes_in_g2binary_data_new_value;
	if ( !((SI_Long)0L <= IFIX(Remaining_bytes_in_g2binary_data))) {
	    temp = report_g2binary_size_error();
	    return VALUES_2(Nil,temp);
	}
    }
    temp = g2_stream_read_char(stream);
    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code))
	return most_recent_file_operation_status_as_text();
    return VALUES_1(CHAR_CODE(temp));
}

/* G2BINARY-FILE-HEADER-VALUE */
Object g2binary_file_header_value()
{
    x_note_fn_call(136,82);
    return VALUES_1(FIX((SI_Long)1L));
}

static Object array_constant_3;    /* # */

/* CHECK-G2BINARY-FILE-HEADER-VALUE */
Object check_g2binary_file_header_value(value)
    Object value;
{
    x_note_fn_call(136,83);
    if ( !EQ(value,FIX((SI_Long)1L)))
	return report_g2binary_error(array_constant_3);
    else
	return VALUES_1(Nil);
}

/* WRITE-G2BINARY-FILE-HEADER */
Object write_g2binary_file_header()
{
    Object value;

    x_note_fn_call(136,84);
    g2_stream_write_char(CHR('G'),G2binary_file_stream);
    g2_stream_write_char(CHR('2'),G2binary_file_stream);
    g2_stream_write_char(CHR('b'),G2binary_file_stream);
    g2_stream_write_char(CHR('n'),G2binary_file_stream);
    value = g2binary_file_header_value();
    write_data_to_g2binary_stream(value,G2binary_file_stream);
    return reclaim_evaluation_value(value);
}

static Object string_constant_25;  /* "Bad first 4 bytes" */

/* READ-G2BINARY-FILE-HEADER */
Object read_g2binary_file_header()
{
    Object temp, data, error_string_qm;
    char temp_1;
    Object result;

    x_note_fn_call(136,85);
    temp = g2_stream_read_char(G2binary_file_stream);
    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code))
	return most_recent_file_operation_status_as_text();
    if (CHAR_EQ(CHR('G'),temp)) {
	temp = g2_stream_read_char(G2binary_file_stream);
	if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
		File_operation_succeeded_code))
	    return most_recent_file_operation_status_as_text();
	temp_1 = CHAR_EQ(CHR('2'),temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = g2_stream_read_char(G2binary_file_stream);
	if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
		File_operation_succeeded_code))
	    return most_recent_file_operation_status_as_text();
	temp_1 = CHAR_EQ(CHR('b'),temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = g2_stream_read_char(G2binary_file_stream);
	if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
		File_operation_succeeded_code))
	    return most_recent_file_operation_status_as_text();
	temp_1 = CHAR_EQ(CHR('n'),temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	return report_g2binary_error(string_constant_25);
    result = read_data_from_g2binary_stream(G2binary_file_stream);
    MVS_2(result,data,error_string_qm);
    if (error_string_qm)
	return VALUES_1(error_string_qm);
    return check_g2binary_file_header_value(data);
}

static Object Qtruth_value;        /* truth-value */

/* SIZE-IN-BYTES-OF-G2BINARY-DATA */
Object size_in_bytes_of_g2binary_data(value)
    Object value;
{
    Object gensymed_symbol_2, held_vector, element, ab_loopvar_, elt_1;
    Object validated_elt, temp_1, a_name, attribute_value, a_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, temp, next_index, length_1;
    SI_Long gensymed_symbol_3;

    x_note_fn_call(136,86);
    gensymed_symbol = (SI_Long)1L;
    if ( !TRUEP(value))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (FIXNUMP(value))
	gensymed_symbol_1 = (SI_Long)4L;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	gensymed_symbol_1 = (SI_Long)8L;
    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value))
	gensymed_symbol_1 = (SI_Long)2L;
    else if (text_string_p(value))
	gensymed_symbol_1 = (SI_Long)4L + (SI_Long)2L * IFIX(lengthw(value));
    else if (SYMBOLP(value)) {
	if (getfq_function_no_default(INLINE_SYMBOL_PLIST(value),
		Qg2binary_file_symbol_index))
	    gensymed_symbol_1 = (SI_Long)4L;
	else {
	    temp = (SI_Long)4L + (SI_Long)2L * 
		    IFIX(lengthw(symbol_name_text_string(value)));
	    get_g2binary_file_symbol_index(value,T);
	    gensymed_symbol_1 = temp;
	}
    }
    else if (CONSP(value) && EQ(M_CDR(value),Qsequence)) {
	gensymed_symbol_1 = (SI_Long)4L;
	gensymed_symbol_2 = value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	ab_loopvar_ = FIX((SI_Long)0L);
	held_vector = M_CAR(gensymed_symbol_2);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	temp_1 = size_in_bytes_of_g2binary_data(element);
	ab_loopvar_ = add(temp_1,ab_loopvar_);
	goto next_loop;
      end_loop:
	gensymed_symbol_3 = IFIX(ab_loopvar_);
	goto end_1;
	gensymed_symbol_3 = IFIX(Qnil);
      end_1:;
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_3;
    }
    else if (CONSP(value) && EQ(M_CDR(value),Qab_structure)) {
	gensymed_symbol_1 = (SI_Long)4L;
	gensymed_symbol_2 = value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	a_name = Nil;
	attribute_value = Nil;
	a_value = Nil;
	ab_loopvar_ = FIX((SI_Long)0L);
	held_vector = M_CAR(gensymed_symbol_2);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	a_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_3 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_3 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_3 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_3 & 
		(SI_Long)1023L);
	a_value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	temp_1 = size_in_bytes_of_g2binary_data(a_name);
	temp_1 = FIXNUM_ADD(temp_1,size_in_bytes_of_g2binary_data(a_value));
	ab_loopvar_ = add(temp_1,ab_loopvar_);
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol_3 = IFIX(ab_loopvar_);
	goto end_2;
	gensymed_symbol_3 = IFIX(Qnil);
      end_2:;
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_3;
    }
    else
	gensymed_symbol_1 = (SI_Long)0L;
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
}

/* WRITE-G2BINARY-DATA-TO-STREAM */
Object write_g2binary_data_to_stream(value,stream)
    Object value, stream;
{
    Object index_1, code, length_1, value_1, gensymed_symbol, held_vector;
    Object element, elt_1, validated_elt, a_name, attribute_value, a_value;
    Object ab_loopvar_, temp_1;
    SI_Long b0, b1, b2, b3, next_index, length_2, gensymed_symbol_1;
    double temp;

    x_note_fn_call(136,87);
    index_1 = Nil;
    if ( !TRUEP(value))
	code = FIX((SI_Long)0L);
    else if (FIXNUMP(value))
	code = FIX((SI_Long)1L);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	code = FIX((SI_Long)2L);
    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value))
	code = FIX((SI_Long)3L);
    else if (text_string_p(value))
	code = FIX((SI_Long)4L);
    else if (SYMBOLP(value)) {
	index_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(value),
		Qg2binary_file_symbol_index);
	code = index_1 ? FIX((SI_Long)5L) : FIX((SI_Long)6L);
    }
    else if (CONSP(value) && EQ(M_CDR(value),Qsequence))
	code = FIX((SI_Long)7L);
    else if (CONSP(value) && EQ(M_CDR(value),Qab_structure))
	code = FIX((SI_Long)8L);
    else
	code = Qnil;
    write_8bit_unsigned_integer_to_g2binary_stream(code,stream);
    if ( !(FIXNUMP(code) && FIXNUM_LE(FIX((SI_Long)-128L),code) && 
	    FIXNUM_LE(code,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(code)) {
	  case 0:
	    return VALUES_1(Nil);
	  case 1:
	    return write_fixnum_to_g2binary_stream(value,stream);
	  case 2:
	    temp = DOUBLE_FLOAT_TO_DOUBLE(value);
	    g2ext_foreign_partition_float(temp,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	    b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	    b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	    b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	    b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	    write_16bit_unsigned_integer_to_g2binary_stream(FIX(b0),stream);
	    write_16bit_unsigned_integer_to_g2binary_stream(FIX(b1),stream);
	    write_16bit_unsigned_integer_to_g2binary_stream(FIX(b2),stream);
	    return write_16bit_unsigned_integer_to_g2binary_stream(FIX(b3),
		    stream);
	  case 3:
	    return write_16bit_unsigned_integer_to_g2binary_stream(FIX((SI_Long)32768L 
		    + IFIX(M_CAR(value))),stream);
	  case 4:
	    length_1 = lengthw(value);
	    write_fixnum_to_g2binary_stream(length_1,stream);
	    return g2_stream_write_from_wide_string_buffer(value,length_1,
		    stream);
	  case 5:
	    return write_fixnum_to_g2binary_stream(index_1,stream);
	  case 6:
	    write_fixnum_to_g2binary_stream(get_g2binary_file_symbol_index(value,
		    T),stream);
	    value_1 = symbol_name_text_string(value);
	    length_1 = lengthw(value);
	    write_fixnum_to_g2binary_stream(length_1,stream);
	    return g2_stream_write_from_wide_string_buffer(value_1,
		    length_1,stream);
	  case 7:
	    write_fixnum_to_g2binary_stream(FIXNUM_SUB1(ISVREF(M_CAR(value),
		    (SI_Long)1L)),stream);
	    gensymed_symbol = value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    element = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop:
	    if (next_index >= length_2)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    element = validated_elt;
	    write_g2binary_data_to_stream(element,stream);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	  case 8:
	    gensymed_symbol = value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    a_name = Nil;
	    attribute_value = Nil;
	    a_value = Nil;
	    ab_loopvar_ = FIX((SI_Long)0L);
	    held_vector = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_2)
		goto end_loop_1;
	    a_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    a_value = validate_item_or_evaluation_value(attribute_value,
		    Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    ab_loopvar_ = add1(ab_loopvar_);
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = ab_loopvar_;
	    goto end_1;
	    temp_1 = Qnil;
	  end_1:;
	    write_fixnum_to_g2binary_stream(temp_1,stream);
	    gensymed_symbol = value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    a_name = Nil;
	    attribute_value = Nil;
	    a_value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_2:
	    if (next_index >= length_2)
		goto end_loop_2;
	    a_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    a_value = validate_item_or_evaluation_value(attribute_value,
		    Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    write_g2binary_data_to_stream(a_name,stream);
	    write_g2binary_data_to_stream(a_value,stream);
	    goto next_loop_2;
	  end_loop_2:
	    return VALUES_1(Qnil);
	  default:
	    return VALUES_1(Nil);
	}
}

/* READ-G2BINARY-DATA-FROM-STREAM */
Object read_g2binary_data_from_stream(stream)
    Object stream;
{
    Object code, error_string_qm;
    Object result;

    x_note_fn_call(136,88);
    result = read_8bit_unsigned_integer_from_g2binary_stream(stream);
    MVS_2(result,code,error_string_qm);
    if (error_string_qm)
	return VALUES_2(Nil,error_string_qm);
    return read_g2binary_data_from_stream_1(code,stream);
}

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

/* READ-G2BINARY-DATA-FROM-STREAM-1 */
Object read_g2binary_data_from_stream_1(code,stream)
    Object code, stream;
{
    Object temp, b0, error_string_qm, b1, b2, b3, value, length_1;
    Object wide_string_bv16, string_1, index_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, attr;
    SI_Long gensymed_symbol, decff_1_arg, temp_1, bv16_length, aref_new_value;
    SI_Long i, ab_loop_bind_;
    Object result;

    x_note_fn_call(136,89);
    if ( !(FIXNUMP(code) && FIXNUM_LE(FIX((SI_Long)-128L),code) && 
	    FIXNUM_LE(code,FIX((SI_Long)127L)))) {
	temp = report_g2binary_error(array_constant_4);
	return VALUES_2(Nil,temp);
    }
    else
	switch (INTEGER_TO_CHAR(code)) {
	  case 0:
	    return VALUES_1(Nil);
	  case 1:
	    return read_fixnum_from_g2binary_stream(stream);
	  case 2:
	    result = read_16bit_unsigned_integer_from_g2binary_stream(stream);
	    MVS_2(result,b0,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    result = read_16bit_unsigned_integer_from_g2binary_stream(stream);
	    MVS_2(result,b1,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    result = read_16bit_unsigned_integer_from_g2binary_stream(stream);
	    MVS_2(result,b2,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    result = read_16bit_unsigned_integer_from_g2binary_stream(stream);
	    MVS_2(result,b3,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    return reconstruct_managed_float(b0,b1,b2,b3);
	  case 3:
	    result = read_16bit_unsigned_integer_from_g2binary_stream(stream);
	    MVS_2(result,value,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    gensymed_symbol = IFIX(value) - (SI_Long)32768L;
	    if (gensymed_symbol == IFIX(Truth))
		return VALUES_1(Evaluation_true_value);
	    else if (gensymed_symbol == IFIX(Falsity))
		return VALUES_1(Evaluation_false_value);
	    else
		return eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
	  case 4:
	    result = read_fixnum_from_g2binary_stream(stream);
	    MVS_2(result,length_1,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    if (IFIX(length_1) < (SI_Long)0L || FIXNUM_GT(length_1,
		    Maximum_byte_vector_16_length)) {
		temp = report_g2binary_error(array_constant_5);
		return VALUES_2(Nil,temp);
	    }
	    decff_1_arg = (SI_Long)2L * IFIX(length_1);
	    temp_1 = IFIX(Remaining_bytes_in_g2binary_data) - decff_1_arg;
	    Remaining_bytes_in_g2binary_data = FIX(temp_1);
	    if ( !((SI_Long)0L <= IFIX(Remaining_bytes_in_g2binary_data))) {
		temp = report_g2binary_size_error();
		return VALUES_2(Nil,temp);
	    }
	    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(length_1) 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    temp_1 = bv16_length - (SI_Long)2L;
	    aref_new_value = IFIX(length_1) & (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	    temp_1 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | IFIX(length_1) >>  -  - 
		    (SI_Long)16L;
	    UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(length_1),(SI_Long)0L);
	    string_1 = wide_string_bv16;
	    g2_stream_read_into_wide_string_buffer(string_1,length_1,stream);
	    if ( !FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
		    File_operation_succeeded_code)) {
		temp = most_recent_file_operation_status_as_text();
		return VALUES_2(Nil,temp);
	    }
	    return VALUES_1(string_1);
	  case 5:
	    result = read_fixnum_from_g2binary_stream(stream);
	    MVS_2(result,index_1,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    return get_g2binary_file_symbol_for_index(index_1);
	  case 6:
	    result = read_fixnum_from_g2binary_stream(stream);
	    MVS_2(result,index_1,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    result = read_g2binary_data_from_stream_1(FIX((SI_Long)4L),stream);
	    MVS_2(result,value,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    return set_g2binary_file_symbol_for_index(index_1,
		    intern_text_string(1,value));
	  case 7:
	    result = read_fixnum_from_g2binary_stream(stream);
	    MVS_2(result,length_1,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    if (IFIX(length_1) < (SI_Long)0L || IFIX(length_1) > 
		    IFIX(FIXNUM_SUB1(Maximum_managed_array_size))) {
		temp = report_g2binary_error(array_constant_6);
		return VALUES_2(Nil,temp);
	    }
	    value = Nil;
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length_1);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    result = read_g2binary_data_from_stream(stream);
	    MVS_2(result,value,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    ab_loopvar__2 = eval_cons_1(value,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = ab_loopvar_;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    return allocate_evaluation_sequence(temp);
	  case 8:
	    result = read_fixnum_from_g2binary_stream(stream);
	    MVS_2(result,length_1,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    if (IFIX(length_1) < (SI_Long)0L || IFIX(length_1) > 
		    IFIX(length_1) * (SI_Long)2L - (SI_Long)1L) {
		temp = report_g2binary_error(array_constant_6);
		return VALUES_2(Nil,temp);
	    }
	    attr = Nil;
	    value = Nil;
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length_1);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    result = read_g2binary_data_from_stream(stream);
	    MVS_2(result,attr,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    result = read_g2binary_data_from_stream(stream);
	    MVS_2(result,value,error_string_qm);
	    if (error_string_qm)
		return VALUES_2(Nil,error_string_qm);
	    ab_loopvar__2 = eval_list_2(attr,value);
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp = ab_loopvar_;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	    return allocate_evaluation_structure(temp);
	  default:
	    temp = report_g2binary_error(array_constant_4);
	    return VALUES_2(Nil,temp);
	}
}

/* WRITE-DATA-TO-G2BINARY-STREAM */
Object write_data_to_g2binary_stream(value,stream)
    Object value, stream;
{
    Object using_temporary_g2binary_file_symbol_indices_p;
    Object temporary_g2binary_file_symbol_indices;
    Object saved_g2binary_file_symbol_index, temp, symbol, ab_loop_list_;
    Declare_special(2);

    x_note_fn_call(136,90);
    using_temporary_g2binary_file_symbol_indices_p = T;
    temporary_g2binary_file_symbol_indices = Nil;
    saved_g2binary_file_symbol_index = Current_g2binary_file_symbol_index;
    PUSH_SPECIAL_WITH_SYMBOL(Temporary_g2binary_file_symbol_indices,Qtemporary_g2binary_file_symbol_indices,temporary_g2binary_file_symbol_indices,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Using_temporary_g2binary_file_symbol_indices_p,Qusing_temporary_g2binary_file_symbol_indices_p,using_temporary_g2binary_file_symbol_indices_p,
	      0);
	temp = size_in_bytes_of_g2binary_data(value);
	symbol = Nil;
	ab_loop_list_ = Temporary_g2binary_file_symbol_indices;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	mutate_global_property(symbol,Nil,Qg2binary_file_symbol_index);
	goto next_loop;
      end_loop:;
	reclaim_gensym_list_1(Temporary_g2binary_file_symbol_indices);
	Current_g2binary_file_symbol_index = saved_g2binary_file_symbol_index;
      POP_SPECIAL();
    POP_SPECIAL();
    write_fixnum_to_g2binary_stream(temp,stream);
    return write_g2binary_data_to_stream(value,stream);
}

/* READ-DATA-FROM-G2BINARY-STREAM */
Object read_data_from_g2binary_stream(stream)
    Object stream;
{
    Object size_in_bytes, error_string_qm, remaining_bytes_in_g2binary_data;
    Object value, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,91);
    result = read_fixnum_from_g2binary_stream(stream);
    MVS_2(result,size_in_bytes,error_string_qm);
    if (error_string_qm) {
	result = VALUES_2(Nil,error_string_qm);
	goto end_read_data_from_g2binary_stream;
    }
    remaining_bytes_in_g2binary_data = size_in_bytes;
    PUSH_SPECIAL_WITH_SYMBOL(Remaining_bytes_in_g2binary_data,Qremaining_bytes_in_g2binary_data,remaining_bytes_in_g2binary_data,
	    0);
      result = read_g2binary_data_from_stream(stream);
      MVS_2(result,value,error_string_qm);
      if (error_string_qm) {
	  result = VALUES_2(Nil,error_string_qm);
	  POP_SPECIAL();
	  goto end_read_data_from_g2binary_stream;
      }
      if ( !((SI_Long)0L == IFIX(Remaining_bytes_in_g2binary_data))) {
	  if (error_string_qm) {
	      temp = report_g2binary_size_error();
	      result = VALUES_2(Nil,temp);
	      POP_SPECIAL();
	      goto end_read_data_from_g2binary_stream;
	  }
      }
      result = VALUES_1(value);
    POP_SPECIAL();
  end_read_data_from_g2binary_stream:
    return result;
}

/* GET-NEXT-G2BINARY-FILE-POSITION */
Object get_next_g2binary_file_position()
{
    Object temp, g2binary_file_position_new_value;

    x_note_fn_call(136,92);
    temp = G2binary_file_position;
    g2binary_file_position_new_value = FIXNUM_ADD1(G2binary_file_position);
    G2binary_file_position = g2binary_file_position_new_value;
    return VALUES_1(temp);
}

/* WRITE-DATA-TO-G2BINARY-FILE */
Object write_data_to_g2binary_file(value)
    Object value;
{
    x_note_fn_call(136,93);
    if (G2binary_file_stream) {
	maybe_open_binary_output_stream();
	return write_data_to_g2binary_stream(value,G2binary_file_stream);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_26;  /* "Binary stream not open" */

/* READ-DATA-FROM-G2BINARY-FILE */
Object read_data_from_g2binary_file(index_1)
    Object index_1;
{
    Object temp, error_string_qm;

    x_note_fn_call(136,94);
    if ( !TRUEP(G2binary_file_stream)) {
	temp = copy_text_string(string_constant_26);
	return VALUES_2(Nil,temp);
    }
    error_string_qm = maybe_open_binary_input_stream();
    if (error_string_qm)
	return VALUES_2(Nil,error_string_qm);
    return read_data_from_g2binary_stream(G2binary_file_stream);
}

/* KB-FORMAT-WRITE-CHAR */
Object kb_format_write_char(char_1)
    Object char_1;
{
    Object temp, temp_1;

    x_note_fn_call(136,95);
    if (Xml_output_stream) {
	temp = Xml_output_buffer;
	temp_1 = Xml_output_position;
	SET_SCHAR(temp,temp_1,char_1);
	temp = FIXNUM_ADD1(Xml_output_position);
	Xml_output_position = temp;
	Length_of_xml_output_line = CHAR_EQ(CHR('\n'),char_1) ? 
		FIX((SI_Long)0L) : FIXNUM_ADD1(Length_of_xml_output_line);
	if (FIXNUM_EQ(Xml_output_position,Write_kb_buffer_length)) {
	    g2_stream_write_from_buffer(Xml_output_buffer,
		    Write_kb_buffer_length,Xml_output_stream);
	    Xml_output_position = FIX((SI_Long)0L);
	    return VALUES_1(Xml_output_position);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (CHAR_EQ(char_1,CHR('\n')))
	return start_new_kb_line();
    else {
	if (CHAR_EQ(CHR('\n'),char_1) && ISVREF(Current_kb_save,(SI_Long)8L))
	    write_char_for_kb(CHR('\r'));
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)29L));
	SVREF(temp,FIX((SI_Long)29L)) = temp_1;
	temp = ISVREF(Current_kb_save,(SI_Long)25L);
	temp_1 = ISVREF(Current_kb_save,(SI_Long)26L);
	SET_SCHAR(temp,temp_1,char_1);
	temp = Current_kb_save;
	temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)26L));
	if (FIXNUM_GE(SVREF(temp,FIX((SI_Long)26L)) = temp_1,
		Write_kb_buffer_length))
	    return flush_kb_write_buffer();
	else
	    return VALUES_1(Nil);
    }
}

/* KB-FORMAT-END-OF-FILE */
Object kb_format_end_of_file()
{
    Object temp;

    x_note_fn_call(136,96);
    temp = Xml_output_stream;
    if (temp)
	return VALUES_1(temp);
    else
	return update_file_progress_for_writing(1,T);
}

/* KB-FORMAT-ENSURE-BEGINNING-OF-LINE */
Object kb_format_ensure_beginning_of_line()
{
    x_note_fn_call(136,97);
    if (Xml_output_stream) {
	if ( !((SI_Long)0L == IFIX(Length_of_xml_output_line)))
	    return kb_format_write_char(CHR('\n'));
	else
	    return VALUES_1(Nil);
    }
    else if ( !((SI_Long)0L == IFIX(ISVREF(Current_kb_save,(SI_Long)29L))))
	return kb_format_write_char(CHR('\n'));
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Clear_text_primitive_value_style, Qclear_text_primitive_value_style);

DEFINE_VARIABLE_WITH_SYMBOL(Call_check_node_attribute_value_p, Qcall_check_node_attribute_value_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_module_being_saved, Qcurrent_module_being_saved);

DEFINE_VARIABLE_WITH_SYMBOL(Writing_xml_p, Qwriting_xml_p);

DEFINE_VARIABLE_WITH_SYMBOL(Writing_xml_cdata_p, Qwriting_xml_cdata_p);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_format_write_integer_buffer, Qkb_format_write_integer_buffer);

/* KB-FORMAT-WRITE-INTEGER */
Object kb_format_write_integer(arg)
    Object arg;
{
    Object buffer, digit_count, schar_new_value;
    SI_Long number, next, digit, temp, i;

    x_note_fn_call(136,98);
    if (IFIX(arg) < (SI_Long)0L) {
	kb_format_write_char(CHR('-'));
	arg = FIXNUM_NEGATE(arg);
    }
    buffer = Kb_format_write_integer_buffer;
    digit_count = FIX((SI_Long)0L);
    number = IFIX(arg);
    next = (SI_Long)0L;
    digit = (SI_Long)0L;
  next_loop:
    temp = number / (SI_Long)10L;
    next = temp;
    digit = number - next * (SI_Long)10L;
    schar_new_value = digit_char(FIX(digit),_,_);
    SET_SCHAR(buffer,digit_count,schar_new_value);
    digit_count = FIXNUM_ADD1(digit_count);
    if ((SI_Long)0L == next)
	goto end_loop;
    number = next;
    goto next_loop;
  end_loop:;
    i = IFIX(sub1(digit_count));
  next_loop_1:
    if (i < (SI_Long)0L)
	goto end_loop_1;
    kb_format_write_char(CHR(ISCHAR(buffer,i)));
    i = i - (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(Nil);
}

static Object Qutf_8_gensym_string_with_newline;  /* utf-8-gensym-string-with-newline */

static Object string_constant_27;  /* "&amp;" */

static Object string_constant_28;  /* "&lt;" */

static Object string_constant_29;  /* "&gt;" */

static Object string_constant_30;  /* "&quot;" */

/* KB-FORMAT-WRITE-STRING */
Object kb_format_write_string(arg,write_quotes_p,quote_markup_p)
    Object arg, write_quotes_p, quote_markup_p;
{
    Object reclaim_p, char_1, replacement;
    SI_Long j, ab_loop_bind_, j_1, ab_loop_bind__1;

    x_note_fn_call(136,99);
    reclaim_p = text_string_p(arg);
    if (reclaim_p)
	arg = export_text_string(2,arg,Qutf_8_gensym_string_with_newline);
    if (STRINGP(arg)) {
	if (write_quotes_p)
	    kb_format_write_char(CHR('\"'));
	j = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(arg));
	char_1 = Nil;
	replacement = Nil;
      next_loop:
	if (j >= ab_loop_bind_)
	    goto end_loop;
	char_1 = CHR(ICHAR(arg,j));
	if (quote_markup_p) {
	    if ( !CHARACTERP(char_1))
		replacement = Nil;
	    else
		switch (ICHAR_CODE(char_1)) {
		  case '&':
		    replacement = string_constant_27;
		    break;
		  case '<':
		    replacement = string_constant_28;
		    break;
		  case '>':
		    replacement = string_constant_29;
		    break;
		  case '\"':
		    replacement = string_constant_30;
		    break;
		  default:
		    replacement = Nil;
		    break;
		}
	}
	else
	    replacement = Nil;
	if (replacement) {
	    j_1 = (SI_Long)0L;
	    ab_loop_bind__1 = IFIX(length(replacement));
	  next_loop_1:
	    if (j_1 >= ab_loop_bind__1)
		goto end_loop_1;
	    kb_format_write_char(CHR(ISCHAR(replacement,j_1)));
	    j_1 = j_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	else
	    kb_format_write_char(char_1);
	j = j + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	if (write_quotes_p)
	    kb_format_write_char(CHR('\"'));
    }
    if (reclaim_p)
	reclaim_gensym_string(arg);
    return VALUES_1(Nil);
}

/* KB-FORMAT */
Object kb_format varargs_1(int, n)
{
    Object string_1;
    Object arg1, arg2, arg3, arg_index, i, len, ch, temp, ch1, at_mod, arg_p;
    Object arg;
    SI_Long i_1, ab_loop_bind_;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(136,100);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    arg_index = FIX((SI_Long)-1L);
    i = FIX((SI_Long)0L);
    len = length(string_1);
    ch = Nil;
  next_loop:
    if ( !FIXNUM_LT(i,len))
	goto end_loop;
    temp = SCHAR(string_1,i);
    i = FIXNUM_ADD1(i);
    ch = temp;
    if (CHAR_EQ(ch,CHR('~'))) {
	temp_1 = CHARACTER_TO_CHAR(SCHAR(string_1,i));
	i = FIXNUM_ADD1(i);
	temp = CHAR_TO_CHARACTER(temp_1);
	ch1 = CHAR_DOWNCASE(temp);
	if (CHAR_EQ(ch1,CHR('@'))) {
	    temp_1 = CHARACTER_TO_CHAR(SCHAR(string_1,i));
	    i = FIXNUM_ADD1(i);
	    temp = CHAR_TO_CHARACTER(temp_1);
	    ch1 = CHAR_DOWNCASE(temp);
	    at_mod = T;
	}
	else
	    at_mod = Nil;
	if ( !CHARACTERP(ch1))
	    arg_p = Nil;
	else
	    switch (ICHAR_CODE(ch1)) {
	      case '%':
		arg_p = at_mod;
		break;
	      case 'd':
		arg_p = T;
		break;
	      case 's':
		arg_p = T;
		break;
	      case 'a':
		arg_p = T;
		break;
	      default:
		arg_p = Nil;
		break;
	    }
	if (arg_p) {
	    arg_index = FIXNUM_ADD1(arg_index);
	    if ( !(FIXNUMP(arg_index) && FIXNUM_LE(FIX((SI_Long)-128L),
		    arg_index) && FIXNUM_LE(arg_index,FIX((SI_Long)127L))))
		arg = Nil;
	    else
		switch (INTEGER_TO_CHAR(arg_index)) {
		  case 0:
		    arg = arg1;
		    break;
		  case 1:
		    arg = arg2;
		    break;
		  case 2:
		    arg = arg3;
		    break;
		  default:
		    arg = Nil;
		    break;
		}
	}
	else
	    arg = Nil;
	if (! !CHARACTERP(ch1))
	    switch (ICHAR_CODE(ch1)) {
	      case '&':
		kb_format_ensure_beginning_of_line();
		break;
	      case '%':
		kb_format_write_char(CHR('\n'));
		if (at_mod) {
		    i_1 = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(arg);
		  next_loop_1:
		    if (i_1 >= ab_loop_bind_)
			goto end_loop_1;
		    kb_format_write_char(CHR(' '));
		    kb_format_write_char(CHR(' '));
		    i_1 = i_1 + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop_1:;
		}
		break;
	      case 'd':
		kb_format_write_integer(arg);
		break;
	      case 'a':
		kb_format_write_string(arg,Nil,Writing_xml_p ? ( 
			!TRUEP(Writing_xml_cdata_p) ? T : Nil) : Qnil);
		break;
	      case 's':
		kb_format_write_string(arg,T,Writing_xml_p);
		break;
	      default:
		break;
	    }
    }
    else
	kb_format_write_char(ch);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TFORMAT-TO-STREAM */
Object tformat_to_stream varargs_1(int, n)
{
    Object stream, format_control;
    Object arg1, arg2, string_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(136,101);
    INIT_ARGS_nonrelocating();
    stream = REQUIRED_ARG_nonrelocating();
    format_control = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    string_1 = tformat_text_string(3,format_control,arg1,arg2);
    write_text_string_to_stream(string_1,stream);
    reclaim_text_string(string_1);
    return VALUES_1(Nil);
}

/* TWRITE-SYMBOL-NAME-FOR-RDF */
Object twrite_symbol_name_for_rdf(symbol)
    Object symbol;
{
    Object name, ch, temp, schar_arg_2, schar_new_value, thing_1;
    SI_Long i, ab_loop_bind_;
    char thing;

    x_note_fn_call(136,102);
    name = export_text_string(2,symbol_name_text_string(symbol),
	    Qutf_8_gensym_string_with_newline);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(name));
    ch = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ch = CHR(ICHAR(name,i));
    if (CHAR_EQ(ch,CHR('\?'))) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = '_';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = '_';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = 'q';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = 'q';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = 'm';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = 'm';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
    }
    else if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing_1 = ch;
	twrite_wide_character(CHARACTERP(thing_1) ? CHAR_CODE(thing_1) : 
		thing_1);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing_1 = ch;
	schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		CHAR_CODE(thing_1) : thing_1);
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_gensym_string(name);
    return VALUES_1(Qnil);
}

static Object Qg2;                 /* g2 */

static Object Qgensym_string;      /* gensym-string */

static Object string_constant_31;  /* "~a~a~a~a" */

static Object string_constant_32;  /* "" */

static Object string_constant_33;  /* "g2m" */

static Object string_constant_34;  /* "g2" */

static Object string_constant_35;  /* ":" */

static Object string_constant_36;  /* "." */

/* GET-RDF-NAME-FOR-SYMBOL-1 */
Object get_rdf_name_for_symbol_1(symbol,indicator,nn_indicator,
	    suppress_namespace,user_p,prefix)
    Object symbol, indicator, nn_indicator, suppress_namespace, user_p, prefix;
{
    Object indicator_1, temp, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object rdf_name;
    char suppress_namespace_p;
    Declare_special(4);

    x_note_fn_call(136,103);
    suppress_namespace_p = EQ(suppress_namespace,user_p ? Qg2m : Qg2);
    indicator_1 = suppress_namespace_p ? nn_indicator : indicator;
    temp = get(symbol,indicator_1,_);
    if (temp)
	return VALUES_1(temp);
    else {
	current_gensym_string = 
		obtain_simple_gensym_string(FIX((SI_Long)2048L));
	PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
		3);
	  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		  2);
	    total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		    1);
	      current_twriting_output_type = Qgensym_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		tformat(5,string_constant_31,suppress_namespace_p ? 
			string_constant_32 : user_p ? string_constant_33 : 
			string_constant_34,suppress_namespace_p ? 
			string_constant_32 : string_constant_35,prefix ? 
			prefix : string_constant_32,prefix ? 
			string_constant_36 : string_constant_32);
		twrite_symbol_name_for_rdf(symbol);
		rdf_name = copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return mutate_global_property(symbol,rdf_name,indicator_1);
    }
}

/* GET-RDF-NAME-FOR-QUALIFIED-ATTRIBUTE-SYMBOL-1 */
Object get_rdf_name_for_qualified_attribute_symbol_1(unique_name,indicator,
	    nn_indicator,suppress_namespace,user_p,prefix,attribute_name,
	    qualifier)
    Object unique_name, indicator, nn_indicator, suppress_namespace, user_p;
    Object prefix, attribute_name, qualifier;
{
    Object indicator_1, temp, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object temp_1, schar_arg_2, schar_new_value, rdf_name;
    char suppress_namespace_p;
    char thing;
    Declare_special(4);

    x_note_fn_call(136,104);
    suppress_namespace_p = EQ(suppress_namespace,user_p ? Qg2m : Qg2);
    indicator_1 = suppress_namespace_p ? nn_indicator : indicator;
    temp = get(unique_name,indicator_1,_);
    if (temp)
	return VALUES_1(temp);
    else {
	current_gensym_string = 
		obtain_simple_gensym_string(FIX((SI_Long)2048L));
	PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
		3);
	  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		  2);
	    total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		    1);
	      current_twriting_output_type = Qgensym_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		tformat(5,string_constant_31,suppress_namespace_p ? 
			string_constant_32 : user_p ? string_constant_33 : 
			string_constant_34,suppress_namespace_p ? 
			string_constant_32 : string_constant_35,prefix ? 
			prefix : string_constant_32,prefix ? 
			string_constant_36 : string_constant_32);
		twrite_symbol_name_for_rdf(qualifier);
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing = '.';
		    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			    CHAR_CODE(CHR(thing)) : CHR(thing));
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_1 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing = '.';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			    CHAR_CODE(CHR(thing)) : CHR(thing));
		    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		    temp_1 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_1;
		}
		twrite_symbol_name_for_rdf(attribute_name);
		rdf_name = copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return mutate_global_property(unique_name,rdf_name,indicator_1);
    }
}

static Object Qrdf_class_name;     /* rdf-class-name */

static Object Qrdf_class_name_no_namespace;  /* rdf-class-name-no-namespace */

static Object string_constant_37;  /* "c" */

/* GET-RDF-CLASS-NAME */
Object get_rdf_class_name varargs_1(int, n)
{
    Object class_1;
    Object suppress_namespace, class_description_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(136,105);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    suppress_namespace = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    return get_rdf_name_for_symbol_1(class_1,Qrdf_class_name,
	    Qrdf_class_name_no_namespace,suppress_namespace,
	    class_description_qm ? ( !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L)) ? T : Nil) : Qnil,string_constant_37);
}

DEFINE_VARIABLE_WITH_SYMBOL(Writing_g2_rdf_file_p, Qwriting_g2_rdf_file_p);

static Object Qg2_defstruct_structure_name_slot_description_g2_struct;  /* g2-defstruct-structure-name::slot-description-g2-struct */

/* GET-RDF-ATTRIBUTE-NAME */
Object get_rdf_attribute_name varargs_1(int, n)
{
    Object node, node_type, attribute;
    Object suppress_namespace, temp, temp_1, x2, temp_2, temp_3;
    Declare_varargs_nonrelocating;

    x_note_fn_call(136,106);
    INIT_ARGS_nonrelocating();
    node = REQUIRED_ARG_nonrelocating();
    node_type = REQUIRED_ARG_nonrelocating();
    attribute = REQUIRED_ARG_nonrelocating();
    suppress_namespace = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = EQ(node_type,Qmodule) ? T : Nil;
    temp_1 = EQ(node_type,Qitem) ? T : Nil;
    if (temp_1);
    else if (SIMPLE_VECTOR_P(node) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) > (SI_Long)2L &&  
	    !EQ(ISVREF(node,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(node,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	temp_1 = Nil;
    if (temp_1);
    else
	temp_1 = xml_object_and_fixups_frame_p(node);
    temp_2 = node_attribute_name(node,node_type,attribute);
    temp_3 = node_attribute_name_qualifier(node,node_type,attribute);
    return get_rdf_attribute_name_1(temp,attribute,temp_1,temp_2,temp_3,
	    Traversing_xml_object_p ? (CONSP(attribute) ? T : Nil) : 
	    SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,(SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct) ? 
	    ISVREF(attribute,(SI_Long)8L) : Qnil,suppress_namespace);
}

static Object Qversion;            /* version */

static Object string_constant_38;  /* "version" */

static Object Qsystem_tables;      /* system-tables */

static Object string_constant_39;  /* "systemtables" */

static Object Qexternal_definitions;  /* external-definitions */

static Object string_constant_40;  /* "externaldefinitions" */

static Object Qformats;            /* formats */

static Object string_constant_41;  /* "formats" */

static Object Qpanes;              /* panes */

static Object string_constant_42;  /* "panes" */

static Object Qchecksums;          /* checksums */

static Object string_constant_43;  /* "checksums" */

static Object QVERSION;            /* |version| */

static Object QSYSTEMTABLES;       /* |systemtables| */

static Object QEXTERNALDEFINITIONS;  /* |externaldefinitions| */

static Object QFORMATS;            /* |formats| */

static Object QPANES;              /* |panes| */

static Object string_constant_44;  /* "g2:version" */

static Object string_constant_45;  /* "g2:systemtables" */

static Object string_constant_46;  /* "g2:externaldefinitions" */

static Object string_constant_47;  /* "g2:formats" */

static Object string_constant_48;  /* "g2:panes" */

static Object string_constant_49;  /* "g2:checksums" */

static Object Qrdf_structure_attribute_name;  /* rdf-structure-attribute-name */

static Object Qrdf_structure_attribute_name_no_namespace;  /* rdf-structure-attribute-name-no-namespace */

static Object string_constant_50;  /* "sa" */

static Object Qrdf_qualified_attribute_name;  /* rdf-qualified-attribute-name */

static Object Qrdf_qualified_attribute_name_no_namespace;  /* rdf-qualified-attribute-name-no-namespace */

static Object string_constant_51;  /* "uq" */

static Object Qrdf_user_attribute_name;  /* rdf-user-attribute-name */

static Object Qrdf_user_attribute_name_no_namespace;  /* rdf-user-attribute-name-no-namespace */

static Object string_constant_52;  /* "ua" */

static Object Qrdf_system_attribute_name;  /* rdf-system-attribute-name */

static Object Qrdf_system_attribute_name_no_namespace;  /* rdf-system-attribute-name-no-namespace */

static Object string_constant_53;  /* "a" */

/* GET-RDF-ATTRIBUTE-NAME-1 */
Object get_rdf_attribute_name_1(modulep,attribute,framep,name,qualifier,
	    user_p,suppress_namespace)
    Object modulep, attribute, framep, name, qualifier, user_p;
    Object suppress_namespace;
{
    x_note_fn_call(136,107);
    if (SYMBOLP(attribute) &&  !TRUEP(framep)) {
	if (modulep) {
	    if (EQ(suppress_namespace,Qg2)) {
		if (EQ(attribute,Qversion))
		    return VALUES_1(string_constant_38);
		else if (EQ(attribute,Qsystem_tables))
		    return VALUES_1(string_constant_39);
		else if (EQ(attribute,Qexternal_definitions))
		    return VALUES_1(string_constant_40);
		else if (EQ(attribute,Qformats))
		    return VALUES_1(string_constant_41);
		else if (EQ(attribute,Qpanes))
		    return VALUES_1(string_constant_42);
		else if (EQ(attribute,Qchecksums))
		    return VALUES_1(string_constant_43);
		else if (EQ(attribute,QVERSION))
		    return VALUES_1(string_constant_38);
		else if (EQ(attribute,QSYSTEMTABLES))
		    return VALUES_1(string_constant_39);
		else if (EQ(attribute,QEXTERNALDEFINITIONS))
		    return VALUES_1(string_constant_40);
		else if (EQ(attribute,QFORMATS))
		    return VALUES_1(string_constant_41);
		else if (EQ(attribute,QPANES))
		    return VALUES_1(string_constant_42);
		else if (EQ(attribute,QCHECKSUMS))
		    return VALUES_1(string_constant_43);
		else
		    return VALUES_1(Qnil);
	    }
	    else if (EQ(attribute,Qversion))
		return VALUES_1(string_constant_44);
	    else if (EQ(attribute,Qsystem_tables))
		return VALUES_1(string_constant_45);
	    else if (EQ(attribute,Qexternal_definitions))
		return VALUES_1(string_constant_46);
	    else if (EQ(attribute,Qformats))
		return VALUES_1(string_constant_47);
	    else if (EQ(attribute,Qpanes))
		return VALUES_1(string_constant_48);
	    else if (EQ(attribute,Qchecksums))
		return VALUES_1(string_constant_49);
	    else if (EQ(attribute,QVERSION))
		return VALUES_1(string_constant_44);
	    else if (EQ(attribute,QSYSTEMTABLES))
		return VALUES_1(string_constant_45);
	    else if (EQ(attribute,QEXTERNALDEFINITIONS))
		return VALUES_1(string_constant_46);
	    else if (EQ(attribute,QFORMATS))
		return VALUES_1(string_constant_47);
	    else if (EQ(attribute,QPANES))
		return VALUES_1(string_constant_48);
	    else if (EQ(attribute,QCHECKSUMS))
		return VALUES_1(string_constant_49);
	    else
		return VALUES_1(Qnil);
	}
	else
	    return get_rdf_name_for_symbol_1(name,
		    Qrdf_structure_attribute_name,
		    Qrdf_structure_attribute_name_no_namespace,
		    suppress_namespace,user_p,string_constant_50);
    }
    else if (qualifier)
	return get_rdf_name_for_qualified_attribute_symbol_1(CONSP(attribute) 
		? make_unique_slot_name_symbol(qualifier,name) : 
		ISVREF(attribute,(SI_Long)1L),
		Qrdf_qualified_attribute_name,
		Qrdf_qualified_attribute_name_no_namespace,
		suppress_namespace,user_p,string_constant_51,name,qualifier);
    else if (user_p)
	return get_rdf_name_for_symbol_1(name,Qrdf_user_attribute_name,
		Qrdf_user_attribute_name_no_namespace,suppress_namespace,
		user_p,string_constant_52);
    else
	return get_rdf_name_for_symbol_1(name,Qrdf_system_attribute_name,
		Qrdf_system_attribute_name_no_namespace,suppress_namespace,
		user_p,string_constant_53);
}

static Object string_constant_54;  /* "<rdf:RDF~%" */

static Object string_constant_55;  /* "  xmlns:rdf=\"http://www.w3.org/TR/WD-rdf-syntax#\"~%" */

static Object string_constant_56;  /* "  xmlns:rdfs=\"http://www.w3.org/TR/WD-rdf-schema#\"~%" */

static Object string_constant_57;  /* "  xmlns:g2=\"\">~%~%" */

static Object string_constant_58;  /* "<rdf:Class rdf:ID=\"Module\">~%" */

static Object string_constant_59;  /* "  <rdfs:subClassOf resource=\"http://www.w3.org/TR/WD-rdf-schema#Resource\"/>~%" */

static Object string_constant_60;  /* "</rdf:Class>~%~%" */

static Object string_constant_61;  /* "<rdf:Property ID=\"~a\" rdfs:domain=\"#Module\"/>~%" */

static Object list_constant_1;     /* # */

static Object string_constant_62;  /* "<rdf:Class rdf:ID=\"~a\">~%" */

static Object string_constant_63;  /* "<rdf:Property ID=\"type\"/>~%~%" */

static Object string_constant_64;  /* "<rdf:Property ID=\"value\"/>~%~%" */

static Object string_constant_65;  /* "<rdf:Property ID=\"unit\"/>~%~%" */

static Object string_constant_66;  /* "<rdf:Class rdf:ID=\"G2Class\">~%" */

static Object string_constant_67;  /* "<rdf:Class rdf:ID=\"G2Attribute\">~%" */

static Object string_constant_68;  /* "  <rdfs:subClassOf resource=\"http://www.w3.org/TR/WD-rdf-schema#Property\"/>~%" */

static Object Qsystem_item;        /* system-item */

static Object string_constant_69;  /* "<G2Class rdf:ID=\"~a\">~%" */

static Object string_constant_70;  /* "  <rdfs:subClassOf resource=\"#~a\"/>~%" */

static Object string_constant_71;  /* "  <rdfs:subClassOf resource=\"#G2Class\"/>~%" */

static Object string_constant_72;  /* "</G2Class>~%~&" */

static Object Qitem_or_evaluation_value;  /* item-or-evaluation-value */

static Object string_constant_73;  /* "<G2Attribute rdf:ID=\"~a\"/>~%" */

static Object string_constant_74;  /* "</rdf:RDF>~%" */

/* WRITE-RDF-SCHEMA-FOR-G2-TO-FILE */
Object write_rdf_schema_for_g2_to_file(file_name)
    Object file_name;
{
    Object stream, writing_g2_rdf_file_p, attribute, ab_loop_list_, pc;
    Object scope_conses, ab_loopvar_, class_1, ab_loopvar__1, ab_loopvar__2;
    Object ab_loopvar__3, temp, class_description_qm, sorted_class_names;
    Object attribute_names, direct_superior_classes, super_class;
    Object ab_loop_list__1, attributes, any_p, attribute_name;
    Declare_special(2);
    Object result;

    x_note_fn_call(136,108);
    stream = g2_stream_open_for_output(file_name);
    writing_g2_rdf_file_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Writing_g2_rdf_file_p,Qwriting_g2_rdf_file_p,writing_g2_rdf_file_p,
	    1);
      if (stream) {
	  tformat_to_stream(2,stream,string_constant_54);
	  tformat_to_stream(2,stream,string_constant_55);
	  tformat_to_stream(2,stream,string_constant_56);
	  tformat_to_stream(2,stream,string_constant_57);
	  tformat_to_stream(2,stream,string_constant_58);
	  tformat_to_stream(2,stream,string_constant_59);
	  tformat_to_stream(2,stream,string_constant_60);
	  attribute = Nil;
	  ab_loop_list_ = node_attributes(Nil,Qmodule);
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  attribute = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  tformat_to_stream(3,stream,string_constant_61,
		  get_rdf_attribute_name(4,Nil,Qmodule,attribute,Qg2));
	  goto next_loop;
	end_loop:;
	  tformat_to_stream(2,stream,string_constant_13);
	  pc = Nil;
	  ab_loop_list_ = list_constant_1;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  pc = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  tformat_to_stream(3,stream,string_constant_62,pc);
	  tformat_to_stream(2,stream,string_constant_59);
	  tformat_to_stream(2,stream,string_constant_60);
	  goto next_loop_1;
	end_loop_1:;
	  tformat_to_stream(2,stream,string_constant_63);
	  tformat_to_stream(2,stream,string_constant_64);
	  tformat_to_stream(2,stream,string_constant_65);
	  tformat_to_stream(2,stream,string_constant_66);
	  tformat_to_stream(2,stream,string_constant_59);
	  tformat_to_stream(2,stream,string_constant_60);
	  tformat_to_stream(2,stream,string_constant_67);
	  tformat_to_stream(2,stream,string_constant_68);
	  tformat_to_stream(2,stream,string_constant_60);
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar_ = Qsystem_item;
	  class_1 = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar_ = collect_subclasses(ab_loopvar_);
	  next_loop_2:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop_2;
	    temp = M_CAR(ab_loopvar_);
	    ab_loopvar_ = M_CDR(ab_loopvar_);
	    class_1 = temp;
	    class_description_qm = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop);
	    if ( !(class_description_qm &&  
		    !TRUEP(ISVREF(class_description_qm,(SI_Long)20L)))) {
		ab_loopvar__3 = eval_cons_1(class_1,Nil);
		if (ab_loopvar__2)
		    M_CDR(ab_loopvar__2) = ab_loopvar__3;
		else
		    ab_loopvar__1 = ab_loopvar__3;
		ab_loopvar__2 = ab_loopvar__3;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = ab_loopvar__1;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	  POP_SPECIAL();
	  sorted_class_names = sort_class_names(temp);
	  attribute_names = Nil;
	  class_1 = Nil;
	  ab_loop_list_ = sorted_class_names;
	  direct_superior_classes = Nil;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  class_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  direct_superior_classes = 
		  lookup_global_or_kb_specific_property_value(class_1,
		  Direct_superior_classes_gkbprop);
	  tformat_to_stream(3,stream,string_constant_69,
		  get_rdf_class_name(2,class_1,Qg2));
	  if (direct_superior_classes) {
	      super_class = Nil;
	      ab_loop_list__1 = direct_superior_classes;
	    next_loop_4:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_4;
	      super_class = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      tformat_to_stream(3,stream,string_constant_70,
		      get_rdf_class_name(2,super_class,Qg2));
	      goto next_loop_4;
	    end_loop_4:;
	  }
	  else
	      tformat_to_stream(2,stream,string_constant_71);
	  tformat_to_stream(2,stream,string_constant_72);
	  attributes = 
		  class_description_node_attributes(lookup_global_or_kb_specific_property_value(class_1,
		  Class_description_gkbprop));
	  any_p = Nil;
	  attribute = Nil;
	  ab_loop_list__1 = attributes;
	  attribute_name = Nil;
	next_loop_5:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_5;
	  attribute = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  attribute_name = node_attribute_name(Nil,
		  Qitem_or_evaluation_value,attribute);
	  if ( !TRUEP(memq_function(attribute_name,attribute_names))) {
	      attribute_names = eval_cons_1(attribute_name,attribute_names);
	      any_p = T;
	      tformat_to_stream(3,stream,string_constant_73,
		      get_rdf_attribute_name(4,Nil,
		      Qitem_or_evaluation_value,attribute,Qg2));
	  }
	  goto next_loop_5;
	end_loop_5:
	  if (any_p)
	      tformat_to_stream(2,stream,string_constant_13);
	  goto next_loop_3;
	end_loop_3:
	  tformat_to_stream(2,stream,string_constant_13);
	  reclaim_eval_list_1(sorted_class_names);
	  reclaim_eval_list_1(attribute_names);
	  tformat_to_stream(2,stream,string_constant_74);
	  result = g2_stream_close(stream);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

Object G2_rdf_file_name = UNBOUND;

static Object string_constant_75;  /* "prototype-" */

static Object string_constant_76;  /* "alpha-" */

static Object string_constant_77;  /* "beta-" */

static Object string_constant_78;  /* "g2-~A~D-~D~A-~D~A~A.rdf" */

static Object string_constant_79;  /* "-" */

/* GET-G2-RDF-FILE-NAME */
Object get_g2_rdf_file_name()
{
    Object temp, major, minor, quality, revision, patch_qm, tenths, hundredths;
    Object result;

    x_note_fn_call(136,109);
    temp = G2_rdf_file_name;
    if (temp)
	return VALUES_1(temp);
    else {
	major = Major_version_number_of_current_gensym_product_line;
	minor = Minor_version_number_of_current_gensym_product_line;
	if ( !TRUEP(T))
	    quality = Nil;
	else
	    switch (INTEGER_TO_CHAR(Release_quality_of_current_gensym_product_line)) 
			{
	      case 0:
		quality = string_constant_75;
		break;
	      case 1:
		quality = string_constant_76;
		break;
	      case 2:
		quality = string_constant_77;
		break;
	      case 3:
		quality = string_constant_32;
		break;
	      default:
		quality = Nil;
		break;
	    }
	revision = Revision_number_of_current_gensym_product_line;
	patch_qm = Patch_number_of_current_gensym_product_line_qm;
	result = l_round(minor,FIX((SI_Long)10L));
	MVS_2(result,tenths,hundredths);
	G2_rdf_file_name = tformat_text_string(8,string_constant_78,
		quality,major,tenths,IFIX(hundredths) == (SI_Long)0L ? 
		string_constant_32 : hundredths,revision,patch_qm ? 
		string_constant_79 : string_constant_32,patch_qm ? 
		patch_qm : string_constant_32);
	return VALUES_1(G2_rdf_file_name);
    }
}

/* WRITE-RDF-SCHEMA-FOR-G2 */
Object write_rdf_schema_for_g2()
{
    x_note_fn_call(136,110);
    return write_rdf_schema_for_g2_to_file(get_g2_rdf_file_name());
}

static Object string_constant_80;  /* "g2:Module" */

static Object string_constant_81;  /* "g2:Sequence" */

static Object string_constant_82;  /* "Sequence" */

static Object string_constant_83;  /* "g2:Structure" */

static Object string_constant_84;  /* "Structure" */

static Object string_constant_85;  /* "g2:BinaryData" */

static Object string_constant_86;  /* "BinaryData" */

static Object string_constant_87;  /* "g2:RawValue" */

static Object string_constant_88;  /* "RawValue" */

static Object string_constant_89;  /* "g2:Integer" */

static Object string_constant_90;  /* "Integer" */

static Object Qlong;               /* long */

static Object string_constant_91;  /* "g2:Long" */

static Object string_constant_92;  /* "Long" */

static Object string_constant_93;  /* "g2:Float" */

static Object string_constant_94;  /* "Float" */

static Object string_constant_95;  /* "g2:Symbol" */

static Object string_constant_96;  /* "Symbol" */

static Object string_constant_97;  /* "g2:Text" */

static Object string_constant_98;  /* "Text" */

static Object string_constant_99;  /* "g2:TruthValue" */

static Object string_constant_100;  /* "TruthValue" */

/* RDF-TYPE-NAME-FOR-NODE */
Object rdf_type_name_for_node(node,node_type,include_prefix_p)
    Object node, node_type, include_prefix_p;
{
    Object category, type;

    x_note_fn_call(136,111);
    category = refid_category_of_node(node,node_type);
    type = refid_type_of_node(node,node_type);
    if (EQ(category,Qmodule))
	return VALUES_1(string_constant_80);
    else if (EQ(category,Qitem))
	return get_rdf_class_name(2,type,Qg2m);
    else if (EQ(category,Qsequence)) {
	if (include_prefix_p)
	    return VALUES_1(string_constant_81);
	else
	    return VALUES_1(string_constant_82);
    }
    else if (EQ(category,Qab_structure)) {
	if (include_prefix_p)
	    return VALUES_1(string_constant_83);
	else
	    return VALUES_1(string_constant_84);
    }
    else if (EQ(category,Qbinary)) {
	if (include_prefix_p)
	    return VALUES_1(string_constant_85);
	else
	    return VALUES_1(string_constant_86);
    }
    else if (EQ(category,Qvalue) || EQ(category,Qprimitive_value)) {
	if (EQ(type,Qnil)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_87);
	    else
		return VALUES_1(string_constant_88);
	}
	else if (EQ(type,Qinteger)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_89);
	    else
		return VALUES_1(string_constant_90);
	}
	else if (EQ(type,Qlong)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_91);
	    else
		return VALUES_1(string_constant_92);
	}
	else if (EQ(type,Qfloat)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_93);
	    else
		return VALUES_1(string_constant_94);
	}
	else if (EQ(type,Qsymbol)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_95);
	    else
		return VALUES_1(string_constant_96);
	}
	else if (EQ(type,Qtext)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_97);
	    else
		return VALUES_1(string_constant_98);
	}
	else if (EQ(type,Qtruth_value)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_99);
	    else
		return VALUES_1(string_constant_100);
	}
	else if (EQ(type,Qsequence)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_81);
	    else
		return VALUES_1(string_constant_82);
	}
	else if (EQ(type,Qab_structure)) {
	    if (include_prefix_p)
		return VALUES_1(string_constant_83);
	    else
		return VALUES_1(string_constant_84);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_101;  /* "rdf:li" */

/* RDF-ATTRIBUTE-NAME-FOR-ATTRIBUTE */
Object rdf_attribute_name_for_attribute(node,node_type,attribute)
    Object node, node_type, attribute;
{
    x_note_fn_call(136,112);
    if (FIXNUMP(attribute))
	return VALUES_1(string_constant_101);
    else
	return get_rdf_attribute_name(4,node,node_type,attribute,Qg2m);
}

/* ATTRIBUTE-NAME-FOR-MAKE-XML-OBJECT */
Object attribute_name_for_make_xml_object(node,node_type,attribute)
    Object node, node_type, attribute;
{
    Object temp, name, qualifier;

    x_note_fn_call(136,113);
    if (FIXNUMP(attribute))
	temp = attribute;
    else {
	name = node_attribute_name(node,node_type,attribute);
	qualifier = node_attribute_name_qualifier(node,node_type,attribute);
	if (qualifier || (Traversing_xml_object_p ? CONSP(attribute) : 
		SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_slot_description_g2_struct) 
		&& ISVREF(attribute,(SI_Long)8L)))
	    temp = eval_cons_1(name,qualifier);
	else if (EQ(node_type,Qmodule)) {
	    if (EQ(attribute,Qversion))
		temp = QVERSION;
	    else if (EQ(attribute,Qsystem_tables))
		temp = QSYSTEMTABLES;
	    else if (EQ(attribute,Qexternal_definitions))
		temp = QEXTERNALDEFINITIONS;
	    else if (EQ(attribute,Qformats))
		temp = QFORMATS;
	    else if (EQ(attribute,Qpanes))
		temp = QPANES;
	    else if (EQ(attribute,Qchecksums))
		temp = QCHECKSUMS;
	    else
		temp = Qnil;
	}
	else
	    temp = name;
    }
    return VALUES_1(temp);
}

/* NODE-IS-RDF-SEQ-P */
Object node_is_rdf_seq_p(node,node_type)
    Object node, node_type;
{
    Object category, type;

    x_note_fn_call(136,114);
    category = refid_category_of_node(node,node_type);
    type = refid_type_of_node(node,node_type);
    if (EQ(category,Qsequence))
	return VALUES_1(T);
    else if (EQ(category,Qvalue)) {
	if (EQ(type,Qsequence))
	    return VALUES_1(T);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_102;  /* "~D" */

static Object string_constant_103;  /* "~A" */

/* TWRITE-REFID */
Object twrite_refid(refid)
    Object refid;
{
    x_note_fn_call(136,115);
    if (FIXNUMP(refid))
	return tformat(2,string_constant_102,refid);
    else if (text_string_p(refid))
	return tformat(2,string_constant_103,refid);
    else if (SYMBOLP(refid))
	return tformat(2,string_constant_103,refid);
    else
	return VALUES_1(Qnil);
}

static Object string_constant_104;  /* "~(~A~).bkb" */

static Object string_constant_105;  /* "#" */

/* RDF-STRING-FOR-REFID-INTERNAL */
Object rdf_string_for_refid_internal(resource,refid)
    Object resource, refid;
{
    Object firstp, name, ab_loop_list_;

    x_note_fn_call(136,116);
    if ( !EQ(resource,Qt)) {
	if (sequence_of_binary_text_strings_p(resource))
	    tformat(2,string_constant_104,Current_module_being_saved);
	else if (resource)
	    twrite_refid(resource);
	tformat(1,string_constant_105);
    }
    if (LISTP(refid)) {
	firstp = T;
	name = Nil;
	ab_loop_list_ = refid;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(firstp))
	    tformat(1,string_constant_36);
	twrite_refid(name);
	firstp = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return twrite_refid(refid);
}

/* RDF-STRING-FOR-REFID */
Object rdf_string_for_refid(resource,refid)
    Object resource, refid;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Declare_special(4);
    Object result;

    x_note_fn_call(136,117);
    current_gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2048L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    rdf_string_for_refid_internal(resource,refid);
	    result = copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* RDF-TEXT-STRING-FOR-REFID */
Object rdf_text_string_for_refid(resource,refid)
    Object resource, refid;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(136,118);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      rdf_string_for_refid_internal(resource,refid);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object Write_rdf_for_kb = UNBOUND;

Object Make_xml_object_for_kb = UNBOUND;

static Object QXMLNS_COL_RDF;      /* |xmlns:rdf| */

static Object array_constant_7;    /* # */

static Object QXMLNS_COL_G2;       /* |xmlns:g2| */

static Object QXMLNS;              /* |xmlns| */

static Object array_constant_8;    /* # */

/* GET-RDF-HEADER-LIST */
Object get_rdf_header_list()
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value;

    x_note_fn_call(136,119);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = QXMLNS_COL_RDF;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = copy_text_string(array_constant_7);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = QXMLNS_COL_G2;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = copy_text_string(get_g2_rdf_file_name());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = QXMLNS;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = copy_text_string(array_constant_8);
    M_CAR(gensymed_symbol_1) = car_new_value;
    return VALUES_1(gensymed_symbol);
}

DEFINE_VARIABLE_WITH_SYMBOL(Run_traverse_kb_xml_object_type, Qrun_traverse_kb_xml_object_type);

static Object string_constant_106;  /* "<?xml version=\"1.0\"?>~%" */

static Object string_constant_107;  /* "<rdf:RDF" */

static Object string_constant_108;  /* "~% ~A=~S" */

static Object string_constant_109;  /* ">~%" */

static Object string_constant_110;  /* "~&</rdf:RDF>~%" */

/* RUN-TRAVERSE-KB-FOR-WRITE-RDF-FOR-KB */
Object run_traverse_kb_for_write_rdf_for_kb(traversal,module,type)
    Object traversal, module, type;
{
    Object writing_xml_p, header, name, value, eval_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2, temp_1;
    Declare_special(1);

    x_note_fn_call(136,120);
    writing_xml_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Writing_xml_p,Qwriting_xml_p,writing_xml_p,0);
      kb_format(1,string_constant_106);
      kb_format(1,string_constant_107);
      header = get_rdf_header_list();
      name = Nil;
      value = Nil;
    next_loop:
      if ( !TRUEP(header))
	  goto end_loop;
      eval_pop_store = Nil;
      cons_1 = header;
      if (cons_1) {
	  eval_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_eval_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_eval_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_eval_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      header = next_cons;
      name = eval_pop_store;
      eval_pop_store = Nil;
      cons_1 = header;
      if (cons_1) {
	  eval_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_eval_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_eval_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_eval_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      header = next_cons;
      value = eval_pop_store;
      kb_format(3,string_constant_108,SYMBOL_NAME(name),value);
      reclaim_text_string(value);
      goto next_loop;
    end_loop:;
      kb_format(1,string_constant_109);
      traverse_kb_internal(traversal,module,type);
      kb_format(1,string_constant_110);
      temp_1 = kb_format_end_of_file();
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

/* RUN-TRAVERSE-KB-FOR-MAKE-XML-OBJECT-FOR-KB */
Object run_traverse_kb_for_make_xml_object_for_kb(traversal,module,type)
    Object traversal, module, type;
{
    Object temp, temp_1;

    x_note_fn_call(136,121);
    temp = Run_traverse_kb_xml_object_type;
    temp_1 = get_rdf_header_list();
    GENSYM_RETURN_ONE(make_xml_object(4,Nil,temp,nconc2(temp_1,
	    traverse_kb_internal(traversal,module,type)),T));
    return VALUES_1(Nil);
}

static Object string_constant_111;  /* "<~a ID=~s>" */

/* RUN-TRAVERSE-KB-NODE-FOR-WRITE-RDF-FOR-KB */
Object run_traverse_kb_node_for_write_rdf_for_kb(traversal,node,node_type,
	    nesting)
    Object traversal, node, node_type, nesting;
{
    Object type_name, refid_string_qm;

    x_note_fn_call(136,122);
    if ((SI_Long)0L == IFIX(nesting))
	kb_format(1,string_constant_13);
    type_name = rdf_type_name_for_node(node,node_type,T);
    refid_string_qm = rdf_string_for_refid_for_node(node,node_type,T);
    if (refid_string_qm) {
	kb_format(3,string_constant_111,type_name,refid_string_qm);
	reclaim_gensym_string(refid_string_qm);
    }
    else
	kb_format(2,string_constant_12,type_name);
    traverse_kb_node_internal(traversal,node,node_type,FIXNUM_ADD1(nesting));
    kb_format(2,string_constant_17,type_name);
    GENSYM_RETURN_ONE((SI_Long)0L == IFIX(nesting) ? kb_format(1,
	    string_constant_13) : Nil);
    return VALUES_1(Nil);
}

static Object Qiteration_state;    /* iteration-state */

/* RUN-TRAVERSE-KB-NODE-FOR-MAKE-XML-OBJECT-FOR-KB */
Object run_traverse_kb_node_for_make_xml_object_for_kb(traversal,node,
	    node_type,nesting)
    Object traversal, node, node_type, nesting;
{
    Object category, write_xml_object_items_collected_new_value, temp_2;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_3, entry_hash, x2, refid_text_string_qm, temp_4;
    SI_Long temp, key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(136,123);
    category = refid_category_of_node(node,node_type);
    if (EQ(Qitem,category) && Write_xml_object_items_collected) {
	write_xml_object_items_collected_new_value = 
		FIXNUM_ADD1(Write_xml_object_items_collected);
	Write_xml_object_items_collected = 
		write_xml_object_items_collected_new_value;
	if (BOUNDP(Qcurrent_kb_save) && ISVREF(Current_kb_save,(SI_Long)13L)) {
	    temp = IFIX(Write_xml_object_items_collected) % (SI_Long)10L;
	    temp_1 = (SI_Long)0L == temp;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    update_file_progress_display(2,ISVREF(Current_kb_save,
		    (SI_Long)13L),Write_xml_object_items_collected);
    }
    if (sequence_of_binary_text_strings_p(node))
	temp_2 = FIXNUMP(node) || node && SYMBOLP(node) ? node : 
		copy_evaluation_value_1(node);
    else {
	gensymed_symbol = node;
	temp_1 = FIXNUMP(gensymed_symbol);
	if (temp_1);
	else
	    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ?
		     IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp_1);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp_1 = EQ(gensymed_symbol,Qtruth_value);
	    if (temp_1);
	    else
		temp_1 = EQ(gensymed_symbol,Qiteration_state);
	    if (temp_1);
	    else if (SYMBOLP(gensymed_symbol)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop:
		if (level < ab_loop_bind_)
		    goto end_loop;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_1;
		goto next_loop_1;
	      end_loop_2:
	      end_1:
		level = level - (SI_Long)1L;
		goto next_loop;
	      end_loop:;
		temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp_2 = FIXNUMP(node) || node && SYMBOLP(node) ? node : 
		    copy_evaluation_value_1(node);
	else {
	    if (SIMPLE_VECTOR_P(node) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) > (SI_Long)2L && 
		     !EQ(ISVREF(node,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(node,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp_2 = node;
	    else
		temp_2 = Nil;
	}
    }
    temp_3 = EQ(Qitem,category) ? eval_list_2(Qab_class,
	    refid_type_of_node(node,node_type)) : Nil;
    refid_text_string_qm = rdf_text_string_for_refid_for_node(node,
	    node_type,T);
    temp_4 = refid_text_string_qm ? eval_list_2(Qid,refid_text_string_qm) :
	     Nil;
    GENSYM_RETURN_ONE(make_xml_object(4,temp_2,category,nconc2(temp_3,
	    nconc2(temp_4,traverse_kb_node_internal(traversal,node,
	    node_type,FIXNUM_ADD1(nesting)))),T));
    return VALUES_1(Nil);
}

static Object string_constant_112;  /* "~NV" */

/* GENSYM-STRING-FOR-XML-PRIMITIVE-VALUE */
Object gensym_string_for_xml_primitive_value(value)
    Object value;
{
    Object value_as_text_string, write_floats_accurately_p, temp;
    Declare_special(1);

    x_note_fn_call(136,124);
    if (Traversing_xml_object_p)
	value = get_xml_object(value);
    if (text_string_p(value))
	value_as_text_string = value;
    else if (SYMBOLP(value))
	value_as_text_string = symbol_name_text_string(value);
    else {
	write_floats_accurately_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_floats_accurately_p,Qwrite_floats_accurately_p,write_floats_accurately_p,
		0);
	  value_as_text_string = tformat_text_string(2,string_constant_112,
		  value);
	POP_SPECIAL();
    }
    temp = export_text_string(2,value_as_text_string,
	    Qutf_8_gensym_string_with_newline);
    if ( !(EQ(value_as_text_string,value) || SYMBOLP(value)))
	reclaim_text_string(value_as_text_string);
    return VALUES_1(temp);
}

/* TEXT-STRING-FOR-XML-PRIMITIVE-VALUE */
Object text_string_for_xml_primitive_value(value)
    Object value;
{
    Object write_floats_accurately_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,125);
    if (text_string_p(value))
	return copy_text_string(value);
    else if (SYMBOLP(value))
	return copy_text_string(symbol_name_text_string(value));
    else {
	write_floats_accurately_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_floats_accurately_p,Qwrite_floats_accurately_p,write_floats_accurately_p,
		0);
	  result = tformat_text_string(2,string_constant_112,value);
	POP_SPECIAL();
	return result;
    }
}

/* SHOULD-USE-CDATA-P */
Object should_use_cdata_p(gensym_string)
    Object gensym_string;
{
    Object use_cdata_p, can_not_use_cdata_p, len, ch, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(136,126);
    use_cdata_p = Nil;
    can_not_use_cdata_p = Nil;
    len = length(gensym_string);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(len);
    ch = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ch = CHR(ICHAR(gensym_string,i));
    if (CHAR_EQ(ch,CHR('&')) || CHAR_EQ(ch,CHR('<')) || CHAR_EQ(ch,
	    CHR('>')) || CHAR_EQ(ch,CHR('\n')) || CHAR_EQ(ch,CHR('\"')))
	use_cdata_p = T;
    if (CHAR_EQ(ch,CHR(']')) && i + (SI_Long)2L < IFIX(len) && 
	    CHAR_EQ(CHR(ICHAR(gensym_string,i + (SI_Long)1L)),CHR(']')) && 
	    CHAR_EQ(CHR(ICHAR(gensym_string,i + (SI_Long)2L)),CHR('>')))
	can_not_use_cdata_p = T;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = use_cdata_p ? ( !TRUEP(can_not_use_cdata_p) ? T : Nil) : Qnil;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute;  /* type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute */

static Object string_constant_113;  /* "~@%" */

static Object string_constant_114;  /* "<~a" */

static Object string_constant_115;  /* " g2:type=~s" */

static Object string_constant_116;  /* " g2:unit=~s" */

static Object Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type;  /* type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type */

static Object string_constant_117;  /* "<~a/>" */

static Object string_constant_118;  /* "<![CDATA[" */

static Object string_constant_119;  /* "~a" */

static Object string_constant_120;  /* "]]>" */

static Object string_constant_121;  /* " g2:value=~s/>" */

/* PRIMITIVE-VALUE-FOR-NODE-DEFINITION-FOR-WRITE-RDF-FOR-KB */
Object primitive_value_for_node_definition_for_write_rdf_for_kb(traversal,
	    node,node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    Object attr_name, type_name, unit_name, value_as_gensym_string;
    Object value_contains_newline_p, writing_xml_cdata_p;
    Object unit_as_gensym_string, style, value_is_raw;
    char only_value_p, value_is_contents_of_type;
    Declare_special(1);

    x_note_fn_call(136,127);
    attr_name = attribute ? rdf_attribute_name_for_attribute(node,
	    node_type,attribute) : Nil;
    type_name = EQ(Clear_text_primitive_value_style,
	    Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute) 
	    && node_attribute_value_is_primitive_p(node,node_type,
	    attribute,value,type) &&  
	    !TRUEP(node_attribute_value_is_untyped_primitive_p(node,
	    node_type,attribute,value,type)) ? 
	    rdf_type_name_for_node(value,Qitem_or_evaluation_value,Nil) : Nil;
    unit_name = type_name && unit_qm ? 
	    gensym_string_for_xml_primitive_value(unit_qm) : Nil;
    if (attr_name) {
	kb_format(2,string_constant_113,nesting);
	kb_format(2,string_constant_114,attr_name);
	if (type_name)
	    kb_format(2,string_constant_115,type_name);
	if (unit_name)
	    kb_format(2,string_constant_116,unit_name);
	kb_format(1,string_constant_2);
    }
    nesting = FIXNUMP(attribute) ? nesting : add1(nesting);
    value_as_gensym_string = gensym_string_for_xml_primitive_value(value);
    value_contains_newline_p = position_in_gensym_string(CHR('\n'),
	    value_as_gensym_string);
    writing_xml_cdata_p = should_use_cdata_p(value_as_gensym_string);
    PUSH_SPECIAL_WITH_SYMBOL(Writing_xml_cdata_p,Qwriting_xml_cdata_p,writing_xml_cdata_p,
	    0);
      unit_as_gensym_string = unit_qm ? 
	      gensym_string_for_xml_primitive_value(unit_qm) : Nil;
      type_name =  !TRUEP(node_attribute_value_is_untyped_primitive_p(node,
	      node_type,attribute,value,type)) ? 
	      rdf_type_name_for_node(value,Qitem_or_evaluation_value,T) : Nil;
      style = Clear_text_primitive_value_style;
      only_value_p = EQ(style,
	      Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute);
      value_is_contents_of_type = EQ(style,
	      Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type);
      value_is_raw = string_eq(2,type_name,string_constant_87);
      if ( !TRUEP(value) || EQ(refid_type_of_node(value,type),Qsequence)) {
	  if ( !only_value_p)
	      kb_format(2,string_constant_117,type_name);
      }
      else if ( !TRUEP(type_name) || value_is_contents_of_type || 
	      only_value_p || Writing_xml_cdata_p) {
	  if (type_name &&  !only_value_p) {
	      kb_format(2,string_constant_114,type_name);
	      if (unit_qm)
		  kb_format(2,string_constant_116,unit_as_gensym_string);
	      kb_format(1,string_constant_2);
	  }
	  if (Writing_xml_cdata_p || value_is_raw)
	      kb_format(1,string_constant_118);
	  if (value_contains_newline_p)
	      kb_format(1,string_constant_13);
	  if (value_is_raw)
	      write_element_for_kb(value);
	  else
	      kb_format(2,string_constant_119,value_as_gensym_string);
	  if (value_contains_newline_p)
	      kb_format(1,string_constant_13);
	  if (Writing_xml_cdata_p || value_is_raw)
	      kb_format(1,string_constant_120);
	  if (type_name &&  !only_value_p)
	      kb_format(2,string_constant_17,type_name);
      }
      else {
	  kb_format(2,string_constant_114,type_name);
	  if (unit_qm)
	      kb_format(2,string_constant_116,unit_as_gensym_string);
	  kb_format(2,string_constant_121,value_as_gensym_string);
      }
      reclaim_gensym_string(value_as_gensym_string);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(attr_name ? kb_format(2,string_constant_17,
	    attr_name) : Nil);
    return VALUES_1(Nil);
}

/* PRIMITIVE-VALUE-FOR-NODE-DEFINITION-FOR-MAKE-XML-OBJECT-FOR-KB */
Object primitive_value_for_node_definition_for_make_xml_object_for_kb(traversal,
	    node,node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    Object temp, temp_1;

    x_note_fn_call(136,128);
    temp = attribute_name_for_make_xml_object(node,node_type,attribute);
    nesting = FIXNUMP(attribute) ? nesting : add1(nesting);
    if (CONSP(value) && EQ(M_CDR(value),Qsequence))
	temp_1 = make_xml_object(4,FIXNUMP(value) || value && 
		SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? value : 
		copy_if_evaluation_value_1(value),Qsequence,Nil,T);
    else if (node_attribute_value_is_untyped_primitive_p(node,node_type,
	    attribute,value,type))
	temp_1 = make_xml_object(4,FIXNUMP(value) || value && 
		SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? value : 
		copy_if_evaluation_value_1(value),Qtext,Nil,T);
    else if (unit_qm)
	temp_1 = make_xml_object(6,FIXNUMP(value) || value && 
		SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? value : 
		copy_if_evaluation_value_1(value),Qprimitive_value,Nil,T,
		Nil,unit_qm);
    else
	temp_1 = FIXNUMP(value) || value && SYMBOLP(value) || 
		SIMPLE_VECTOR_P(value) ? value : 
		copy_if_evaluation_value_1(value);
    GENSYM_RETURN_ONE(eval_list_2(temp,temp_1));
    return VALUES_1(Nil);
}

static Object string_constant_122;  /* " rdf:resource=~s/>" */

/* REFERENCE-FOR-NODE-DEFINITION-FOR-WRITE-RDF-FOR-KB */
Object reference_for_node_definition_for_write_rdf_for_kb(traversal,node,
	    node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    Object attr_name, type_name, unit_name, refid_string_qm, temp;

    x_note_fn_call(136,129);
    attr_name = attribute ? rdf_attribute_name_for_attribute(node,
	    node_type,attribute) : Nil;
    type_name = EQ(Clear_text_primitive_value_style,
	    Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute) 
	    && node_attribute_value_is_primitive_p(node,node_type,
	    attribute,value,type) &&  
	    !TRUEP(node_attribute_value_is_untyped_primitive_p(node,
	    node_type,attribute,value,type)) ? 
	    rdf_type_name_for_node(value,Qitem_or_evaluation_value,Nil) : Nil;
    unit_name = type_name && unit_qm ? 
	    gensym_string_for_xml_primitive_value(unit_qm) : Nil;
    if (attr_name) {
	kb_format(2,string_constant_113,nesting);
	kb_format(2,string_constant_114,attr_name);
	if (type_name)
	    kb_format(2,string_constant_115,type_name);
	if (unit_name)
	    kb_format(2,string_constant_116,unit_name);
	kb_format(1,string_constant_2);
    }
    nesting = FIXNUMP(attribute) ? nesting : add1(nesting);
    type_name = rdf_type_name_for_node(value,type,T);
    refid_string_qm = rdf_string_for_refid_for_node(value,type,Nil);
    kb_format(2,string_constant_114,type_name);
    temp = refid_string_qm;
    if (temp);
    else
	temp = string_constant_32;
    kb_format(2,string_constant_122,temp);
    if (STRINGP(refid_string_qm))
	reclaim_gensym_string(refid_string_qm);
    if (EQ(Qbinary,refid_category_of_node(value,type)))
	write_data_to_g2binary_file(node_attribute_binary_value(node,
		node_type,attribute,value,type));
    GENSYM_RETURN_ONE(attr_name ? kb_format(2,string_constant_17,
	    attr_name) : Nil);
    return VALUES_1(Nil);
}

/* REFERENCE-FOR-NODE-DEFINITION-FOR-MAKE-XML-OBJECT-FOR-KB */
Object reference_for_node_definition_for_make_xml_object_for_kb(traversal,
	    node,node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    Object temp, category, resource_string, temp_1;

    x_note_fn_call(136,130);
    temp = attribute_name_for_make_xml_object(node,node_type,attribute);
    nesting = FIXNUMP(attribute) ? nesting : add1(nesting);
    category = refid_category_of_node(value,type);
    resource_string = rdf_text_string_for_refid_for_node(value,type,Nil);
    temp_1 = EQ(category,Qitem) ? eval_list_2(Qab_class,
	    refid_type_of_node(value,type)) : Nil;
    GENSYM_RETURN_ONE(eval_list_2(temp,make_xml_object(4,value,category,
	    nconc2(temp_1,eval_list_2(QRDF_COL_RESOURCE,resource_string)),T)));
    return VALUES_1(Nil);
}

/* TRAVERSE-FOR-NODE-DEFINITION-FOR-WRITE-RDF-FOR-KB */
Object traverse_for_node_definition_for_write_rdf_for_kb(traversal,node,
	    node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    Object attr_name, type_name, unit_name;

    x_note_fn_call(136,131);
    attr_name = attribute ? rdf_attribute_name_for_attribute(node,
	    node_type,attribute) : Nil;
    type_name = EQ(Clear_text_primitive_value_style,
	    Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute) 
	    && node_attribute_value_is_primitive_p(node,node_type,
	    attribute,value,type) &&  
	    !TRUEP(node_attribute_value_is_untyped_primitive_p(node,
	    node_type,attribute,value,type)) ? 
	    rdf_type_name_for_node(value,Qitem_or_evaluation_value,Nil) : Nil;
    unit_name = type_name && unit_qm ? 
	    gensym_string_for_xml_primitive_value(unit_qm) : Nil;
    if (attr_name) {
	kb_format(2,string_constant_113,nesting);
	kb_format(2,string_constant_114,attr_name);
	if (type_name)
	    kb_format(2,string_constant_115,type_name);
	if (unit_name)
	    kb_format(2,string_constant_116,unit_name);
	kb_format(1,string_constant_2);
    }
    nesting = FIXNUMP(attribute) ? nesting : add1(nesting);
    if (attribute)
	kb_format(2,string_constant_113,nesting);
    traverse_kb_node(traversal,value,type,nesting);
    GENSYM_RETURN_ONE(attr_name ? kb_format(2,string_constant_17,
	    attr_name) : Nil);
    return VALUES_1(Nil);
}

/* TRAVERSE-FOR-NODE-DEFINITION-FOR-MAKE-XML-OBJECT-FOR-KB */
Object traverse_for_node_definition_for_make_xml_object_for_kb(traversal,
	    node,node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    Object temp;

    x_note_fn_call(136,132);
    temp = attribute_name_for_make_xml_object(node,node_type,attribute);
    nesting = FIXNUMP(attribute) ? nesting : add1(nesting);
    GENSYM_RETURN_ONE(eval_list_2(temp,traverse_kb_node(traversal,value,
	    type,nesting)));
    return VALUES_1(Nil);
}

Object Find_references_for_writing = UNBOUND;

/* NODE-IS-REFERENCED-P */
Object node_is_referenced_p(node,node_type)
    Object node, node_type;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(136,133);
    if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(node,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? BOUNDP(Qcurrent_kb_save) : TRUEP(Nil))
	return block_referenced_in_current_save_p(node);
    else
	return VALUES_1(Nil);
}

/* SET-NODE-IS-REFERENCED-P */
Object set_node_is_referenced_p(node,node_type,new_value)
    Object node, node_type, new_value;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(136,134);
    if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(node,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? BOUNDP(Qcurrent_kb_save) : TRUEP(Nil))
	return set_block_referenced_in_current_save(node,new_value);
    else
	return VALUES_1(Nil);
}

/* RUN-TRAVERSE-KB-FOR-FIND-REFERENCES-FOR-WRITING */
Object run_traverse_kb_for_find_references_for_writing(traversal,module,type)
    Object traversal, module, type;
{
    x_note_fn_call(136,135);
    GENSYM_RETURN_ONE(traverse_kb_internal(traversal,module,type));
    return VALUES_1(Nil);
}

/* RUN-TRAVERSE-KB-NODE-FOR-FIND-REFERENCES-FOR-WRITING */
Object run_traverse_kb_node_for_find_references_for_writing(traversal,node,
	    node_type,nesting)
    Object traversal, node, node_type, nesting;
{
    x_note_fn_call(136,136);
    GENSYM_RETURN_ONE(traverse_kb_node_internal(traversal,node,node_type,
	    nesting));
    return VALUES_1(Nil);
}

/* TRAVERSE-FOR-NODE-DEFINITION-FOR-FIND-REFERENCES-FOR-WRITING */
Object traverse_for_node_definition_for_find_references_for_writing(traversal,
	    node,node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    x_note_fn_call(136,137);
    GENSYM_RETURN_ONE(traverse_kb_node(traversal,value,type,nesting));
    return VALUES_1(Nil);
}

/* REFERENCE-FOR-NODE-DEFINITION-FOR-FIND-REFERENCES-FOR-WRITING */
Object reference_for_node_definition_for_find_references_for_writing(traversal,
	    node,node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    x_note_fn_call(136,138);
    GENSYM_RETURN_ONE( 
	    !TRUEP(node_is_uniquely_and_persistantly_named(value,type)) ? 
	    set_node_is_referenced_p(value,type,T) : Nil);
    return VALUES_1(Nil);
}

static Object Qxml_primitive_value_style;  /* xml-primitive-value-style */

/* WRITE-CLEAR-TEXT-FROM-XML-OBJECT */
Object write_clear_text_from_xml_object(binary_file,xml_object)
    Object binary_file, xml_object;
{
    Object g2binary_file_name, g2binary_file_stream, g2binary_file_position;
    Object current_g2binary_file_symbol_index, g2binary_file_symbol_list;
    Object g2binary_file_symbol_index_space, traversing_xml_object_p;
    Object clear_text_primitive_value_style, temp, symbol, ab_loop_list_;
    Declare_special(8);
    Object result;

    x_note_fn_call(136,139);
    if (SIMPLE_VECTOR_P(binary_file) && EQ(ISVREF(binary_file,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	g2binary_file_name = gensym_namestring(1,binary_file);
    else if (text_string_p(binary_file))
	g2binary_file_name = copy_text_string(binary_file);
    else
	g2binary_file_name = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_name,Qg2binary_file_name,g2binary_file_name,
	    7);
      g2binary_file_stream = G2binary_file_name;
      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_stream,Qg2binary_file_stream,g2binary_file_stream,
	      6);
	g2binary_file_position = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_position,Qg2binary_file_position,g2binary_file_position,
		5);
	  current_g2binary_file_symbol_index = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_g2binary_file_symbol_index,Qcurrent_g2binary_file_symbol_index,current_g2binary_file_symbol_index,
		  4);
	    g2binary_file_symbol_list = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_list,Qg2binary_file_symbol_list,g2binary_file_symbol_list,
		    3);
	      g2binary_file_symbol_index_space = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_index_space,Qg2binary_file_symbol_index_space,g2binary_file_symbol_index_space,
		      2);
		traversing_xml_object_p = T;
		clear_text_primitive_value_style = 
			get_lookup_slot_value(Saving_parameters,
			Qxml_primitive_value_style);
		PUSH_SPECIAL_WITH_SYMBOL(Clear_text_primitive_value_style,Qclear_text_primitive_value_style,clear_text_primitive_value_style,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Traversing_xml_object_p,Qtraversing_xml_object_p,traversing_xml_object_p,
			  0);
		    temp = traverse_kb(Write_rdf_for_kb,xml_object,Qmodule);
		  POP_SPECIAL();
		POP_SPECIAL();
		maybe_close_binary_stream();
		symbol = Nil;
		ab_loop_list_ = G2binary_file_symbol_list;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		symbol = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		mutate_global_property(symbol,Nil,Qg2binary_file_symbol_index);
		goto next_loop;
	      end_loop:;
		reclaim_gensym_list_1(G2binary_file_symbol_list);
		if (G2binary_file_symbol_index_space)
		    reclaim_index_space_1(G2binary_file_symbol_index_space);
		if (text_string_p(G2binary_file_name))
		    reclaim_text_string(G2binary_file_name);
		result = VALUES_1(temp);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* WRITE-CLEAR-TEXT-FROM-MODULE */
Object write_clear_text_from_module(binary_file,module)
    Object binary_file, module;
{
    Object g2binary_file_name, g2binary_file_stream, g2binary_file_position;
    Object current_g2binary_file_symbol_index, g2binary_file_symbol_list;
    Object g2binary_file_symbol_index_space, temp, symbol, ab_loop_list_;
    Declare_special(6);
    Object result;

    x_note_fn_call(136,140);
    if (SIMPLE_VECTOR_P(binary_file) && EQ(ISVREF(binary_file,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	g2binary_file_name = gensym_namestring(1,binary_file);
    else if (text_string_p(binary_file))
	g2binary_file_name = copy_text_string(binary_file);
    else
	g2binary_file_name = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_name,Qg2binary_file_name,g2binary_file_name,
	    5);
      g2binary_file_stream = G2binary_file_name;
      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_stream,Qg2binary_file_stream,g2binary_file_stream,
	      4);
	g2binary_file_position = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_position,Qg2binary_file_position,g2binary_file_position,
		3);
	  current_g2binary_file_symbol_index = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_g2binary_file_symbol_index,Qcurrent_g2binary_file_symbol_index,current_g2binary_file_symbol_index,
		  2);
	    g2binary_file_symbol_list = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_list,Qg2binary_file_symbol_list,g2binary_file_symbol_list,
		    1);
	      g2binary_file_symbol_index_space = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_index_space,Qg2binary_file_symbol_index_space,g2binary_file_symbol_index_space,
		      0);
		temp = write_module_as_clear_text(module,Nil,Qmodule);
		maybe_close_binary_stream();
		symbol = Nil;
		ab_loop_list_ = G2binary_file_symbol_list;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		symbol = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		mutate_global_property(symbol,Nil,Qg2binary_file_symbol_index);
		goto next_loop;
	      end_loop:;
		reclaim_gensym_list_1(G2binary_file_symbol_list);
		if (G2binary_file_symbol_index_space)
		    reclaim_index_space_1(G2binary_file_symbol_index_space);
		if (text_string_p(G2binary_file_name))
		    reclaim_text_string(G2binary_file_name);
		result = VALUES_1(temp);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* WRITE-XML-OBJECT-FROM-MODULE */
Object write_xml_object_from_module(module)
    Object module;
{
    Object g2binary_file_name, g2binary_file_stream, g2binary_file_position;
    Object current_g2binary_file_symbol_index, g2binary_file_symbol_list;
    Object g2binary_file_symbol_index_space, temp, symbol, ab_loop_list_;
    Declare_special(6);
    Object result;

    x_note_fn_call(136,141);
    if (SIMPLE_VECTOR_P(Nil) && EQ(ISVREF(Nil,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	g2binary_file_name = gensym_namestring(1,Nil);
    else if (text_string_p(Nil))
	g2binary_file_name = copy_text_string(Nil);
    else
	g2binary_file_name = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_name,Qg2binary_file_name,g2binary_file_name,
	    5);
      g2binary_file_stream = G2binary_file_name;
      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_stream,Qg2binary_file_stream,g2binary_file_stream,
	      4);
	g2binary_file_position = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_position,Qg2binary_file_position,g2binary_file_position,
		3);
	  current_g2binary_file_symbol_index = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_g2binary_file_symbol_index,Qcurrent_g2binary_file_symbol_index,current_g2binary_file_symbol_index,
		  2);
	    g2binary_file_symbol_list = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_list,Qg2binary_file_symbol_list,g2binary_file_symbol_list,
		    1);
	      g2binary_file_symbol_index_space = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_index_space,Qg2binary_file_symbol_index_space,g2binary_file_symbol_index_space,
		      0);
		temp = write_module_as_clear_text(module,T,Qmodule);
		maybe_close_binary_stream();
		symbol = Nil;
		ab_loop_list_ = G2binary_file_symbol_list;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		symbol = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		mutate_global_property(symbol,Nil,Qg2binary_file_symbol_index);
		goto next_loop;
	      end_loop:;
		reclaim_gensym_list_1(G2binary_file_symbol_list);
		if (G2binary_file_symbol_index_space)
		    reclaim_index_space_1(G2binary_file_symbol_index_space);
		if (text_string_p(G2binary_file_name))
		    reclaim_text_string(G2binary_file_name);
		result = VALUES_1(temp);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* WRITE-XML-OBJECT-FROM-ITEM-OR-EVALUATION-VALUE */
Object write_xml_object_from_item_or_evaluation_value(item_or_evaluation_value)
    Object item_or_evaluation_value;
{
    Object g2binary_file_name, g2binary_file_stream, g2binary_file_position;
    Object current_g2binary_file_symbol_index, g2binary_file_symbol_list;
    Object g2binary_file_symbol_index_space, temp, symbol, ab_loop_list_;
    Declare_special(6);
    Object result;

    x_note_fn_call(136,142);
    if (SIMPLE_VECTOR_P(Nil) && EQ(ISVREF(Nil,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	g2binary_file_name = gensym_namestring(1,Nil);
    else if (text_string_p(Nil))
	g2binary_file_name = copy_text_string(Nil);
    else
	g2binary_file_name = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_name,Qg2binary_file_name,g2binary_file_name,
	    5);
      g2binary_file_stream = G2binary_file_name;
      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_stream,Qg2binary_file_stream,g2binary_file_stream,
	      4);
	g2binary_file_position = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_position,Qg2binary_file_position,g2binary_file_position,
		3);
	  current_g2binary_file_symbol_index = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_g2binary_file_symbol_index,Qcurrent_g2binary_file_symbol_index,current_g2binary_file_symbol_index,
		  2);
	    g2binary_file_symbol_list = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_list,Qg2binary_file_symbol_list,g2binary_file_symbol_list,
		    1);
	      g2binary_file_symbol_index_space = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_index_space,Qg2binary_file_symbol_index_space,g2binary_file_symbol_index_space,
		      0);
		temp = write_module_as_clear_text(item_or_evaluation_value,
			T,Qitem_or_evaluation_value);
		maybe_close_binary_stream();
		symbol = Nil;
		ab_loop_list_ = G2binary_file_symbol_list;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		symbol = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		mutate_global_property(symbol,Nil,Qg2binary_file_symbol_index);
		goto next_loop;
	      end_loop:;
		reclaim_gensym_list_1(G2binary_file_symbol_list);
		if (G2binary_file_symbol_index_space)
		    reclaim_index_space_1(G2binary_file_symbol_index_space);
		if (text_string_p(G2binary_file_name))
		    reclaim_text_string(G2binary_file_name);
		result = VALUES_1(temp);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* WRITE-RDF-SCHEMA-FOR-MODULE */
Object write_rdf_schema_for_module()
{
    Object temp, file_name;

    x_note_fn_call(136,143);
    temp = get_g2_rdf_file_name();
    file_name = gensym_namestring(1,gensym_merge_pathnames_function(temp,
	    ISVREF(Current_kb_save,(SI_Long)5L),Nil));
    if ( !TRUEP(g2_stream_probe_file_for_exist(file_name)))
	return write_rdf_schema_for_g2_to_file(file_name);
    else
	return VALUES_1(Nil);
}

/* WRITE-MODULE-AS-CLEAR-TEXT */
Object write_module_as_clear_text(value,xml_object_p,type)
    Object value, xml_object_p, type;
{
    Object in_write_module_as_clear_text_p, current_module_being_saved;
    Object write_xml_object_items_collected, call_check_node_attribute_value_p;
    Object clear_text_primitive_value_style, temp;
    Declare_special(5);

    x_note_fn_call(136,144);
    in_write_module_as_clear_text_p = T;
    current_module_being_saved = EQ(type,Qmodule) ? value : Nil;
    write_xml_object_items_collected = xml_object_p ? FIX((SI_Long)0L) : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Current_module_being_saved,Qcurrent_module_being_saved,current_module_being_saved,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(In_write_module_as_clear_text_p,Qin_write_module_as_clear_text_p,in_write_module_as_clear_text_p,
		2);
	  traverse_kb(Find_references_for_writing,value,type);
	  call_check_node_attribute_value_p =  !((SI_Long)0L != 
		  ((SI_Long)1L & IFIX(get_kb_clear_text_history(Nil,
		  Nil)))) ? T : Nil;
	  clear_text_primitive_value_style = 
		  get_lookup_slot_value(Saving_parameters,
		  Qxml_primitive_value_style);
	  PUSH_SPECIAL_WITH_SYMBOL(Clear_text_primitive_value_style,Qclear_text_primitive_value_style,clear_text_primitive_value_style,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Call_check_node_attribute_value_p,Qcall_check_node_attribute_value_p,call_check_node_attribute_value_p,
		    0);
	      temp = traverse_kb(xml_object_p ? Make_xml_object_for_kb : 
		      Write_rdf_for_kb,value,type);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    decache_all_cached_class_node_attributes();
    decache_all_formats_for_current_module();
    return VALUES_1(temp);
}

/* MAKE-XML-OBJECT-FOR-EVALUATION-VALUE */
Object make_xml_object_for_evaluation_value(value)
    Object value;
{
    x_note_fn_call(136,145);
    return traverse_kb_node(Make_xml_object_for_kb,value,
	    Qitem_or_evaluation_value,FIX((SI_Long)0L));
}

Object Find_stripped_text_slot = UNBOUND;

/* RUN-TRAVERSE-KB-FOR-FIND-STRIPPED-TEXT-SLOT */
Object run_traverse_kb_for_find_stripped_text_slot(traversal,module,type)
    Object traversal, module, type;
{
    x_note_fn_call(136,146);
    GENSYM_RETURN_ONE(traverse_kb_internal(traversal,module,type));
    return VALUES_1(Nil);
}

/* RUN-TRAVERSE-KB-NODE-FOR-FIND-STRIPPED-TEXT-SLOT */
Object run_traverse_kb_node_for_find_stripped_text_slot(traversal,node,
	    node_type,nesting)
    Object traversal, node, node_type, nesting;
{
    x_note_fn_call(136,147);
    GENSYM_RETURN_ONE(traverse_kb_node_internal(traversal,node,node_type,
	    nesting));
    return VALUES_1(Nil);
}

/* TRAVERSE-FOR-NODE-DEFINITION-FOR-FIND-STRIPPED-TEXT-SLOT */
Object traverse_for_node_definition_for_find_stripped_text_slot(traversal,
	    node,node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    x_note_fn_call(136,148);
    GENSYM_RETURN_ONE(traverse_kb_node(traversal,value,type,nesting));
    return VALUES_1(Nil);
}

static Object Qfree;               /* free */

static Object Qfree_text_attribute;  /* free-text-attribute */

static Object Qproprietary_package;  /* proprietary-package */

/* POSSIBLE-TEXT-STRIPPED-OR-PROPRIETARY-PACKAGE-ATTRIBUTE */
Object possible_text_stripped_or_proprietary_package_attribute(attribute)
    Object attribute;
{
    Object type_of_slot_qm, temp;

    x_note_fn_call(136,149);
    if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,(SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct)) {
	type_of_slot_qm = assq_function(Qtype,ISVREF(attribute,(SI_Long)9L));
	temp = type_of_slot_qm && memq_function(Qtext,
		CDDR(type_of_slot_qm)) ? ( !(EQ(CADR(type_of_slot_qm),
		Qfree) || EQ(CADR(type_of_slot_qm),Qfree_text_attribute)) ?
		 T : Nil) : Qnil;
	if (temp)
	    return VALUES_1(temp);
	else if ( !TRUEP(ISVREF(attribute,(SI_Long)8L)))
	    return VALUES_1(EQ(Qproprietary_package,ISVREF(attribute,
		    (SI_Long)2L)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_9;    /* # */

static Object Qtext_stripped;      /* text-stripped */

static Object Qproprietary;        /* proprietary */

static Object Qstripped_text_slot_search;  /* stripped-text-slot-search */

/* PRIMITIVE-VALUE-FOR-NODE-DEFINITION-FOR-FIND-STRIPPED-TEXT-SLOT */
Object primitive_value_for_node_definition_for_find_stripped_text_slot(traversal,
	    node,node_type,nesting,attribute,value,unit_qm,type)
    Object traversal, node, node_type, nesting, attribute, value, unit_qm;
    Object type;
{
    Object problem, temp, temp_2;
    char temp_1;
    Object result;

    x_note_fn_call(136,150);
    if (possible_text_stripped_or_proprietary_package_attribute(attribute)) {
	if (text_string_p(value) && equalw(value,array_constant_9))
	    problem = Qtext_stripped;
	else {
	    if (EQ(Qproprietary_package,ISVREF(attribute,(SI_Long)2L))) {
		temp = ISVREF(node,(SI_Long)26L);
		temp_1 =  !LISTP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		problem = Qproprietary;
	    else
		problem = Qnil;
	}
	if (problem) {
	    result = VALUES_2(node,problem);
	    THROW(Qstripped_text_slot_search,result);
	}
	else
	    temp_2 = Nil;
    }
    else
	temp_2 = Nil;
    GENSYM_RETURN_ONE(temp_2);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(In_find_stripped_text_slot_p, Qin_find_stripped_text_slot_p);

/* MODULE-CONTAINS-TEXT-STRIPPED-FRAMES-P */
Object module_contains_text_stripped_frames_p(module)
    Object module;
{
    Object in_find_stripped_text_slot_p, node, problem;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(136,151);
    if (PUSH_CATCH(Qstripped_text_slot_search,0)) {
	in_find_stripped_text_slot_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(In_find_stripped_text_slot_p,Qin_find_stripped_text_slot_p,in_find_stripped_text_slot_p,
		0);
	  traverse_kb(Find_stripped_text_slot,module,Qmodule);
	  result = VALUES_1(Nil);
	POP_SPECIAL();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_2(result,node,problem);
    decache_all_cached_class_node_attributes();
    return VALUES_2(node,problem);
}

/* ITEM-OR-EVALUATION-VALUE-CONTAINS-TEXT-STRIPPED-FRAMES-P */
Object item_or_evaluation_value_contains_text_stripped_frames_p(value)
    Object value;
{
    Object in_find_stripped_text_slot_p, node, problem;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(136,152);
    if (PUSH_CATCH(Qstripped_text_slot_search,0)) {
	in_find_stripped_text_slot_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(In_find_stripped_text_slot_p,Qin_find_stripped_text_slot_p,in_find_stripped_text_slot_p,
		0);
	  traverse_kb(Find_stripped_text_slot,value,Qitem_or_evaluation_value);
	  result = VALUES_1(Nil);
	POP_SPECIAL();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_2(result,node,problem);
    decache_all_cached_class_node_attributes();
    return VALUES_2(node,problem);
}

DEFINE_VARIABLE_WITH_SYMBOL(Traverse_kb_queued_nodes, Qtraverse_kb_queued_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Traverse_kb_queued_nodes_tail, Qtraverse_kb_queued_nodes_tail);

/* ENQUEUE-KB-NODE */
Object enqueue_kb_node(node_plus_type)
    Object node_plus_type;
{
    Object new_1, cdr_arg;

    x_note_fn_call(136,153);
    new_1 = eval_cons_1(node_plus_type,Nil);
    if (Traverse_kb_queued_nodes_tail) {
	cdr_arg = Traverse_kb_queued_nodes_tail;
	M_CDR(cdr_arg) = new_1;
    }
    else
	Traverse_kb_queued_nodes = new_1;
    Traverse_kb_queued_nodes_tail = new_1;
    return VALUES_1(Traverse_kb_queued_nodes_tail);
}

/* DEQUEUE-KB-NODE */
Object dequeue_kb_node()
{
    Object eval_pop_store, cons_1, next_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(136,154);
    if (Traverse_kb_queued_nodes) {
	eval_pop_store = Nil;
	cons_1 = Traverse_kb_queued_nodes;
	if (cons_1) {
	    eval_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Traverse_kb_queued_nodes = next_cons;
	temp_1 = eval_pop_store;
	if ( !TRUEP(Traverse_kb_queued_nodes))
	    Traverse_kb_queued_nodes_tail = Nil;
	return VALUES_1(temp_1);
    }
    else
	return VALUES_1(Nil);
}

/* ENQUEUE-ALL-ITEMS-IN-DFS-ORDER */
Object enqueue_all_items_in_dfs_order(workspace)
    Object workspace;
{
    Object item_list, sub_item, ab_loop_list_, subworkspace, x2;
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(136,155);
    enqueue_kb_node(eval_cons_1(workspace,Qitem_or_evaluation_value));
    item_list = subitems_in_definition_order_for_clear_text(workspace);
    sub_item = Nil;
    ab_loop_list_ = item_list;
    subworkspace = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(sub_item) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_item)) > (SI_Long)2L &&  
	    !EQ(ISVREF(sub_item,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(sub_item,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? (SI_Long)0L != (IFIX(ISVREF(sub_item,(SI_Long)4L)) & 
	    (SI_Long)1L) : TRUEP(Nil)) {
	temp_1 = ISVREF(sub_item,(SI_Long)18L);
	subworkspace = CAR(temp_1);
    }
    else
	subworkspace = Nil;
    enqueue_kb_node(eval_cons_1(sub_item,Qitem_or_evaluation_value));
    if (subworkspace)
	enqueue_all_items_in_dfs_order(subworkspace);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(item_list);
    return VALUES_1(Qnil);
}

/* TRAVERSE-KB */
Object traverse_kb(traversal,value,type)
    Object traversal, value, type;
{
    Object traverse_kb_queued_nodes, traverse_kb_queued_nodes_tail, cons_1;
    Object ab_loop_list_;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(136,156);
    SAVE_STACK();
    traverse_kb_queued_nodes = Nil;
    traverse_kb_queued_nodes_tail = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Traverse_kb_queued_nodes_tail,Qtraverse_kb_queued_nodes_tail,traverse_kb_queued_nodes_tail,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Traverse_kb_queued_nodes,Qtraverse_kb_queued_nodes,traverse_kb_queued_nodes,
	      0);
	if (PUSH_UNWIND_PROTECT(0))
	    SAVE_VALUES(traverse_kb_1(traversal,value,type));
	POP_UNWIND_PROTECT(0);
	cons_1 = Nil;
	ab_loop_list_ = Traverse_kb_queued_nodes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	cons_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_eval_cons_1(cons_1);
	goto next_loop;
      end_loop:;
	reclaim_eval_list_1(Traverse_kb_queued_nodes);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Item_color_pattern_returns_overrides_only_p, Qitem_color_pattern_returns_overrides_only_p);

DEFINE_VARIABLE_WITH_SYMBOL(Array_initialization_evaluation_values_use_designations_p, Qarray_initialization_evaluation_values_use_designations_p);

static Object Qworkspaces;         /* workspaces */

/* TRAVERSE-KB-1 */
Object traverse_kb_1(traversal,value,type)
    Object traversal, value, type;
{
    Object object_and_fixups, object_and_fixups_vector, type_1, fixups;
    Object module_seen_p, value_1, traversal_function, gensymed_symbol;
    Object held_vector, attribute_1, attribute_value;
    Object array_initialization_evaluation_values_use_designations_p;
    Object item_color_pattern_returns_overrides_only_p;
    Object current_computation_flags, ws_list, ws, elt_1, validated_elt;
    SI_Long attribute, ab_loop_bind_, next_index, length_1, gensymed_symbol_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(136,157);
    if (Traversing_xml_object_p) {
	object_and_fixups = value;
	object_and_fixups_vector = CONSP(object_and_fixups) && 
		EQ(M_CDR(object_and_fixups),Qab_structure) ? 
		M_CAR(object_and_fixups) : Nil;
	type_1 = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
	if (EQ(type_1,Qprimitive_value) || EQ(type_1,Qtext))
	    return VALUES_1(Nil);
	else if (EQ(type_1,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    module_seen_p =  !EQ(type,Qmodule) ? T : Nil;
	    if (fixups) {
		attribute = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		value_1 = Nil;
	      next_loop:
		if (attribute >= ab_loop_bind_)
		    goto end_loop;
		value_1 = evaluation_sequence_aref(fixups,FIX(attribute));
		if (EQ(FIX(attribute),QModule) && EQ(type,Qmodule)) {
		    module_seen_p = T;
		    enqueue_kb_node(eval_cons_1(value_1,Qmodule));
		}
		else if (module_seen_p)
		    enqueue_kb_node(eval_cons_1(value_1,
			    Qitem_or_evaluation_value));
		attribute = attribute + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	    traversal_function = ISVREF(traversal,(SI_Long)0L);
	    if (traversal_function)
		return VALUES_1(inline_funcall_3(traversal_function,
			traversal,value,type));
	    else
		return VALUES_1(Nil);
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    module_seen_p =  !EQ(type,Qmodule) ? T : Nil;
	    if (fixups) {
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		attribute_1 = Nil;
		attribute_value = Nil;
		value_1 = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		attribute_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 
			& (SI_Long)1023L);
		value_1 = 
			validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if (EQ(attribute_1,QModule) && EQ(type,Qmodule)) {
		    module_seen_p = T;
		    enqueue_kb_node(eval_cons_1(value_1,Qmodule));
		}
		else if (module_seen_p)
		    enqueue_kb_node(eval_cons_1(value_1,
			    Qitem_or_evaluation_value));
		goto next_loop_1;
	      end_loop_1:;
	    }
	    traversal_function = ISVREF(traversal,(SI_Long)0L);
	    if (traversal_function)
		return VALUES_1(inline_funcall_3(traversal_function,
			traversal,value,type));
	    else
		return VALUES_1(Nil);
	}
    }
    else {
	array_initialization_evaluation_values_use_designations_p = T;
	item_color_pattern_returns_overrides_only_p = T;
	current_computation_flags = Current_computation_flags;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Item_color_pattern_returns_overrides_only_p,Qitem_color_pattern_returns_overrides_only_p,item_color_pattern_returns_overrides_only_p,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Array_initialization_evaluation_values_use_designations_p,Qarray_initialization_evaluation_values_use_designations_p,array_initialization_evaluation_values_use_designations_p,
		    0);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)2048L);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)4096L);
	      enqueue_kb_node(eval_cons_1(value,type));
	      ws_list = node_attribute_value(value,type,Qworkspaces);
	      gensymed_symbol = ws_list;
	      held_vector = Nil;
	      next_index = (SI_Long)1L;
	      length_1 = (SI_Long)0L;
	      ws = Nil;
	      held_vector = M_CAR(gensymed_symbol);
	      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop_2:
	      if (next_index >= length_1)
		  goto end_loop_2;
	      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      next_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),next_index & 
		      (SI_Long)1023L);
	      validated_elt = elt_1 ? 
		      validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	      next_index = next_index + (SI_Long)1L;
	      ws = validated_elt;
	      enqueue_all_items_in_dfs_order(ws);
	      goto next_loop_2;
	    end_loop_2:
	      reclaim_node_attribute_value(value,type,Qworkspaces,ws_list);
	      traversal_function = ISVREF(traversal,(SI_Long)0L);
	      if (traversal_function)
		  result = VALUES_1(inline_funcall_3(traversal_function,
			  traversal,value,type));
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

/* TRAVERSE-KB-INTERNAL */
Object traverse_kb_internal(traversal,module,type)
    Object traversal, module, type;
{
    Object node_plus_type, node, node_type, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(136,158);
    if (EQ(traversal,Make_xml_object_for_kb)) {
	node_plus_type = Nil;
	node = Nil;
	node_type = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	node_plus_type = dequeue_kb_node();
	if ( !TRUEP(node_plus_type))
	    goto end_loop;
	node = CAR(node_plus_type);
	node_type = CDR(node_plus_type);
	reclaim_eval_cons_1(node_plus_type);
	temp = EQ(node_type,Qmodule) ? QModule : Nil;
	ab_loopvar__2 = eval_list_2(temp,traverse_kb_node(traversal,node,
		node_type,FIX((SI_Long)0L)));
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else {
	node_plus_type = Nil;
	node = Nil;
	node_type = Nil;
      next_loop_1:
	node_plus_type = dequeue_kb_node();
	if ( !TRUEP(node_plus_type))
	    goto end_loop_1;
	node = CAR(node_plus_type);
	node_type = CDR(node_plus_type);
	reclaim_eval_cons_1(node_plus_type);
	traverse_kb_node(traversal,node,node_type,FIX((SI_Long)0L));
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* WRITE-XML-OBJECT--MODULE */
Object write_xml_object__module(xml_object)
    Object xml_object;
{
    x_note_fn_call(136,159);
    return traverse_kb_node(Write_rdf_for_kb,xml_object,Qmodule,
	    FIX((SI_Long)0L));
}

/* WRITE-XML-OBJECT--ITEM-OR-EVALUATION-VALUE */
Object write_xml_object__item_or_evaluation_value(xml_object)
    Object xml_object;
{
    Object traversal, node, node_type, attribute, value, unit_qm, type, fn;
    Object traversal_function;
    SI_Long nesting;

    x_note_fn_call(136,160);
    traversal = Write_rdf_for_kb;
    node = Nil;
    node_type = Qitem_or_evaluation_value;
    attribute = Nil;
    value = xml_object;
    unit_qm = Nil;
    type = Qitem_or_evaluation_value;
    nesting = (SI_Long)0L;
    if (node_attribute_value_is_primitive_p(node,node_type,attribute,value,
	    type))
	fn = ISVREF(traversal,(SI_Long)2L);
    else if (node_attribute_value_is_definition_p(node,node_type,attribute,
	    value,type))
	fn = ISVREF(traversal,(SI_Long)4L);
    else
	fn = ISVREF(traversal,(SI_Long)3L);
    traversal_function = fn;
    if (traversal_function)
	return VALUES_1(inline_funcall_8(traversal_function,traversal,node,
		node_type,FIX(nesting),attribute,value,unit_qm,type));
    else
	return VALUES_1(Nil);
}

/* TRAVERSE-KB-NODE */
Object traverse_kb_node(traversal,node,node_type,nesting)
    Object traversal, node, node_type, nesting;
{
    Object traversal_function;

    x_note_fn_call(136,161);
    traversal_function = ISVREF(traversal,(SI_Long)1L);
    if (traversal_function)
	return VALUES_1(inline_funcall_4(traversal_function,traversal,node,
		node_type,nesting));
    else
	return VALUES_1(Nil);
}

/* DO-NOT-SAVE-IMAGE-DATA-P */
Object do_not_save_image_data_p(attribute,attributes)
    Object attribute, attributes;
{
    x_note_fn_call(136,162);
    if (EQ(Qimage_data,attribute))
	return VALUES_1( !TRUEP(memq_function(Qsave_image_data_with_kb,
		attributes)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* TRAVERSE-KB-NODE-INTERNAL */
Object traverse_kb_node_internal(traversal,node,node_type,nesting)
    Object traversal, node, node_type, nesting;
{
    Object attributes, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, attribute_1;
    Object ab_loop_list_;
    SI_Long attribute, ab_loop_bind_;

    x_note_fn_call(136,163);
    attributes = node_attributes(node,node_type);
    if (FIXNUMP(attributes)) {
	if (EQ(traversal,Make_xml_object_for_kb)) {
	    attribute = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(attributes);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if (attribute >= ab_loop_bind_)
		goto end_loop;
	    ab_loopvar__2 = traverse_kb_attribute(traversal,node,node_type,
		    FIX(attribute),nesting);
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	    attribute = attribute + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
	else {
	    attribute = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(attributes);
	  next_loop_1:
	    if (attribute >= ab_loop_bind_)
		goto end_loop_1;
	    traverse_kb_attribute(traversal,node,node_type,FIX(attribute),
		    nesting);
	    attribute = attribute + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
    }
    else if (EQ(traversal,Make_xml_object_for_kb)) {
	attribute_1 = Nil;
	ab_loop_list_ = attributes;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	attribute_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = traverse_kb_attribute(traversal,node,node_type,
		attribute_1,nesting);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop_2;
      end_loop_2:
	reclaim_node_attributes(node,node_type,attributes);
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else {
	attribute_1 = Nil;
	ab_loop_list_ = attributes;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	attribute_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(do_not_save_image_data_p(attribute_1,attributes)))
	    traverse_kb_attribute(traversal,node,node_type,attribute_1,
		    nesting);
	goto next_loop_3;
      end_loop_3:
	reclaim_node_attributes(node,node_type,attributes);
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Traversing_kb_attribute, Qtraversing_kb_attribute);

/* TRAVERSE-KB-ATTRIBUTE */
Object traverse_kb_attribute(traversal,node,node_type,attribute,nesting)
    Object traversal, node, node_type, attribute, nesting;
{
    Object value, unit_qm, type, temp, fn, module_attribute;
    Object traversing_kb_attribute, traversal_function;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,164);
    value = node_attribute_value(node,node_type,attribute);
    unit_qm = node_attribute_unit(node,node_type,attribute);
    type = node_attribute_type(node,node_type,attribute);
    if ( !TRUEP(skip_node_attribute_value_p(node,node_type,attribute,value,
	    type))) {
	if (Call_check_node_attribute_value_p)
	    check_node_attribute_value(node,node_type,attribute,value,type);
	if (node_attribute_value_is_primitive_p(node,node_type,attribute,
		value,type))
	    result = VALUES_1(ISVREF(traversal,(SI_Long)2L));
	else if (node_attribute_value_is_definition_p(node,node_type,
		attribute,value,type)) {
	    temp = ISVREF(traversal,(SI_Long)4L);
	    result = VALUES_2(temp,EQ(node_type,Qmodule) ? attribute : Qnil);
	}
	else
	    result = VALUES_1(ISVREF(traversal,(SI_Long)3L));
	MVS_2(result,fn,module_attribute);
	if (module_attribute) {
	    traversing_kb_attribute = module_attribute;
	    PUSH_SPECIAL_WITH_SYMBOL(Traversing_kb_attribute,Qtraversing_kb_attribute,traversing_kb_attribute,
		    0);
	      traversal_function = fn;
	      temp = traversal_function ? 
		      inline_funcall_8(traversal_function,traversal,node,
		      node_type,nesting,attribute,value,unit_qm,type) : Nil;
	    POP_SPECIAL();
	}
	else {
	    traversal_function = fn;
	    temp = traversal_function ? 
		    inline_funcall_8(traversal_function,traversal,node,
		    node_type,nesting,attribute,value,unit_qm,type) : Nil;
	}
    }
    else
	temp = Nil;
    reclaim_node_attribute_value(node,node_type,attribute,value);
    return VALUES_1(temp);
}

/* RDF-RESOURCE-FOR-NODE */
Object rdf_resource_for_node(value,type)
    Object value, type;
{
    Object x2, module;
    char temp;

    x_note_fn_call(136,165);
    if (SIMPLE_VECTOR_P(value) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	module = get_module_block_is_in(value);
	if (module && Current_module_being_saved &&  !EQ(module,
		Current_module_being_saved))
	    return VALUES_1(module);
	else
	    return VALUES_1(Nil);
    }
    else if (sequence_of_binary_text_strings_p(value))
	return VALUES_1(value);
    else
	return VALUES_1(Qnil);
}

/* REFID-FOR-NODE */
Object refid_for_node(node,node_type)
    Object node, node_type;
{
    Object temp, temp_1, superior, superior_type;
    Object result;

    x_note_fn_call(136,166);
    if (sequence_of_binary_text_strings_p(node))
	return get_next_g2binary_file_position();
    else if (EQ(Traversing_kb_attribute,Qexternal_definitions))
	return VALUES_1(Nil);
    else if (node_is_uniquely_and_persistantly_named(node,node_type))
	return node_unique_and_persistant_name(node,node_type);
    else if ( !TRUEP(node_is_referenced_p(node,node_type)))
	return VALUES_1(Nil);
    else if (node_is_uniquely_named_p(node,node_type))
	return node_unique_name(node,node_type);
    else {
	temp = index_for_unnamed_node(node,node_type);
	temp_1 = refid_type_of_node(node,node_type);
	result = refid_node_superior(node,node_type);
	MVS_2(result,superior,superior_type);
	return make_composite_name(temp,temp_1,superior_type ? 
		refid_for_node(superior,superior_type) : Nil);
    }
}

/* RDF-STRING-FOR-REFID-FOR-NODE */
Object rdf_string_for_refid_for_node(value,type,local_p)
    Object value, type, local_p;
{
    Object object_and_fixups, object_and_fixups_vector, type_1, temp, fixups;
    Object text_string_qm, refid, resource, refid_string;

    x_note_fn_call(136,167);
    if (Traversing_xml_object_p) {
	object_and_fixups = value;
	object_and_fixups_vector = CONSP(object_and_fixups) && 
		EQ(M_CDR(object_and_fixups),Qab_structure) ? 
		M_CAR(object_and_fixups) : Nil;
	type_1 = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
	if (EQ(type_1,Qprimitive_value) || EQ(type_1,Qtext))
	    temp = Nil;
	else if (EQ(type_1,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    text_string_qm = get_xml_fixups(value,QRDF_COL_RESOURCE,Nil);
	    if (text_string_qm);
	    else
		text_string_qm = get_xml_fixups(value,Qid,Nil);
	    temp = text_string_qm && text_string_p(text_string_qm) ? 
		    export_text_string(2,text_string_qm,
		    Qutf_8_gensym_string_with_newline) : Nil;
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    text_string_qm = get_xml_fixups(value,QRDF_COL_RESOURCE,Nil);
	    if (text_string_qm);
	    else
		text_string_qm = get_xml_fixups(value,Qid,Nil);
	    temp = text_string_qm && text_string_p(text_string_qm) ? 
		    export_text_string(2,text_string_qm,
		    Qutf_8_gensym_string_with_newline) : Nil;
	}
    }
    else {
	refid = refid_for_node(value,type);
	resource = local_p;
	if (resource);
	else
	    resource = refid ? rdf_resource_for_node(value,type) : Nil;
	refid_string = refid ? rdf_string_for_refid(resource,refid) : Nil;
	reclaim_refid(refid);
	temp = refid_string;
    }
    return VALUES_1(temp);
}

/* RDF-TEXT-STRING-FOR-REFID-FOR-NODE */
Object rdf_text_string_for_refid_for_node(value,type,local_p)
    Object value, type, local_p;
{
    Object object_and_fixups, object_and_fixups_vector, type_1, temp, fixups;
    Object thing, refid, resource, refid_string;

    x_note_fn_call(136,168);
    if (Traversing_xml_object_p) {
	object_and_fixups = value;
	object_and_fixups_vector = CONSP(object_and_fixups) && 
		EQ(M_CDR(object_and_fixups),Qab_structure) ? 
		M_CAR(object_and_fixups) : Nil;
	type_1 = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
	if (EQ(type_1,Qprimitive_value) || EQ(type_1,Qtext))
	    temp = Nil;
	else if (EQ(type_1,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    thing = get_xml_fixups(value,QRDF_COL_RESOURCE,Nil);
	    if (thing);
	    else
		thing = get_xml_fixups(value,Qid,Nil);
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ?
		     copy_text_string(thing) : thing;
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    thing = get_xml_fixups(value,QRDF_COL_RESOURCE,Nil);
	    if (thing);
	    else
		thing = get_xml_fixups(value,Qid,Nil);
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ?
		     copy_text_string(thing) : thing;
	}
    }
    else {
	refid = refid_for_node(value,type);
	resource = local_p;
	if (resource);
	else
	    resource = refid ? rdf_resource_for_node(value,type) : Nil;
	refid_string = refid ? rdf_text_string_for_refid(resource,refid) : Nil;
	reclaim_refid(refid);
	temp = refid_string;
    }
    return VALUES_1(temp);
}

/* NODE-IS-UNIQUELY-AND-PERSISTANTLY-NAMED */
Object node_is_uniquely_and_persistantly_named(node,node_type)
    Object node, node_type;
{
    Object temp, x2;

    x_note_fn_call(136,169);
    if (Traversing_xml_object_p) {
	temp = get_xml_fixups(node,QRDF_COL_RESOURCE,Nil);
	if (temp)
	    return VALUES_1(temp);
	else
	    return get_xml_fixups(node,Qid,Nil);
    }
    else if (EQ(node_type,Qmodule))
	return VALUES_1(node);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    if (SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct))
		return VALUES_1(x2);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* NODE-UNIQUE-AND-PERSISTANT-NAME */
Object node_unique_and_persistant_name(node,node_type)
    Object node, node_type;
{
    Object temp;

    x_note_fn_call(136,170);
    if (Traversing_xml_object_p) {
	temp = get_xml_fixups(node,QRDF_COL_RESOURCE,Nil);
	if (temp)
	    return VALUES_1(temp);
	else
	    return get_xml_fixups(node,Qid,Nil);
    }
    else if (EQ(node_type,Qmodule))
	return VALUES_1(node);
    else if (EQ(node_type,Qitem_or_evaluation_value))
	return item_uuid_representation(node);
    else
	return VALUES_1(Qnil);
}

/* ITEM-UUID-REPRESENTATION */
Object item_uuid_representation(item)
    Object item;
{
    Object uuid, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(136,171);
    uuid = item_uuid(item);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      twrite_uuid_printed_representation(uuid);
	      reclaim_text_string(uuid);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* NODE-IS-UNIQUELY-NAMED-P */
Object node_is_uniquely_named_p(node,node_type)
    Object node, node_type;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, name, frame_or_frames;
    Object temp_1, class_description, count_1, frame, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(136,172);
    if (EQ(node_type,Qmodule))
	return VALUES_1(node);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = get_lookup_slot_value_given_default(node,
		    Qname_or_names_for_frame,Nil);
	    frame_or_frames = name && ATOM(name) ? 
		    lookup_kb_specific_property_value(name,
		    Frame_or_frames_with_this_name_kbprop) : Qnil;
	    if (frame_or_frames) {
		temp_1 = ATOM(frame_or_frames) ? T : Nil;
		if (temp_1)
		    return VALUES_1(temp_1);
		else {
		    class_description = ISVREF(node,(SI_Long)1L);
		    count_1 = FIX((SI_Long)0L);
		    frame = Nil;
		    ab_loop_list_ = frame_or_frames;
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    frame = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (EQ(ISVREF(frame,(SI_Long)1L),class_description)) {
			if (IFIX(count_1) == (SI_Long)1L)
			    return VALUES_1(Nil);
			else
			    count_1 = FIXNUM_ADD1(count_1);
		    }
		    goto next_loop;
		  end_loop:
		    return VALUES_1(IFIX(count_1) == (SI_Long)1L ? T : Nil);
		    return VALUES_1(Qnil);
		}
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* NODE-UNIQUE-NAME */
Object node_unique_name(node,node_type)
    Object node, node_type;
{
    x_note_fn_call(136,173);
    if (EQ(node_type,Qitem_or_evaluation_value))
	return get_lookup_slot_value_given_default(node,
		Qname_or_names_for_frame,Nil);
    else
	return VALUES_1(Nil);
}

/* INDEX-FOR-UNNAMED-NODE */
Object index_for_unnamed_node(node,node_type)
    Object node, node_type;
{
    Object superior_qm, inferiors_of_superior, index_1, inferior;
    Object ab_loop_list_;

    x_note_fn_call(136,174);
    if (EQ(node_type,Qitem_or_evaluation_value)) {
	superior_qm = refid_node_superior(node,node_type);
	if (superior_qm) {
	    inferiors_of_superior = 
		    subitems_in_definition_order_for_clear_text(superior_qm);
	    index_1 = FIX((SI_Long)0L);
	    inferior = Nil;
	    ab_loop_list_ = inferiors_of_superior;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    inferior = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(node,inferior))
		goto end_loop;
	    else if (EQ(ISVREF(inferior,(SI_Long)1L),ISVREF(node,(SI_Long)1L)))
		index_1 = FIXNUM_ADD1(index_1);
	    goto next_loop;
	  end_loop:
	    reclaim_eval_list_1(inferiors_of_superior);
	    return VALUES_1(index_1);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(ISVREF(node,(SI_Long)3L));
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-COMPOSITE-NAME */
Object make_composite_name(name,type,superior_refid)
    Object name, type, superior_refid;
{
    x_note_fn_call(136,175);
    return eval_cons_1(type,eval_cons_1(name,superior_refid));
}

/* RECLAIM-REFID */
Object reclaim_refid(refid)
    Object refid;
{
    Object e, ab_loop_list_;

    x_note_fn_call(136,176);
    if (text_string_p(refid))
	return reclaim_text_string(refid);
    else if (CONSP(refid)) {
	e = Nil;
	ab_loop_list_ = refid;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	e = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_refid(e);
	goto next_loop;
      end_loop:;
	return reclaim_eval_list_1(refid);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qparent_frame;       /* parent-frame */

/* REFID-NODE-SUPERIOR */
Object refid_node_superior(node,node_type)
    Object node, node_type;
{
    Object x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(136,177);
    if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(node,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(ISVREF(node,(SI_Long)18L));
	    else
		return get_lookup_slot_value_given_default(node,
			Qparent_frame,Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REFID-TYPE-OF-NODE */
Object refid_type_of_node(node,node_type)
    Object node, node_type;
{
    Object temp, x2, type;
    char temp_1;

    x_note_fn_call(136,178);
    if (Traversing_xml_object_p) {
	temp = xml_object_and_fixups_frame_p(node);
	if (temp);
	else
	    temp = xml_object_and_fixups_evaluation_type(node);
	if (temp)
	    return VALUES_1(temp);
	else
	    return xml_object_and_fixups_binary_type(node);
    }
    else if (EQ(node_type,Qmodule))
	return VALUES_1(Qmodule);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return get_class(node);
	else if (sequence_of_binary_text_strings_p(node))
	    return VALUES_1(Qbinary);
	else {
	    type = node ? evaluation_value_type(node) : Nil;
	    if (CONSP(type))
		return VALUES_1(CAR(type));
	    else
		return VALUES_1(type);
	}
    }
    else
	return VALUES_1(Qnil);
}

/* REFID-CATEGORY-OF-NODE */
Object refid_category_of_node(node,node_type)
    Object node, node_type;
{
    Object object_and_fixups, object_and_fixups_vector, type, fixups, x2;
    char temp;

    x_note_fn_call(136,179);
    if (Traversing_xml_object_p) {
	object_and_fixups = node;
	object_and_fixups_vector = CONSP(object_and_fixups) && 
		EQ(M_CDR(object_and_fixups),Qab_structure) ? 
		M_CAR(object_and_fixups) : Nil;
	type = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
	if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	    return VALUES_1(type);
	else if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    return VALUES_1(type);
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    return VALUES_1(type);
	}
    }
    else if (EQ(node_type,Qmodule))
	return VALUES_1(Qmodule);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1(Qitem);
	else if (sequence_of_binary_text_strings_p(node))
	    return VALUES_1(Qbinary);
	else if (CONSP(node) && EQ(M_CDR(node),Qsequence))
	    return VALUES_1(Qsequence);
	else if (CONSP(node) && EQ(M_CDR(node),Qab_structure))
	    return VALUES_1(Qab_structure);
	else
	    return VALUES_1(Qprimitive_value);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_2;     /* # */

/* NODE-ATTRIBUTES */
Object node_attributes(node,node_type)
    Object node, node_type;
{
    Object attribute_list, framep, object_and_fixups, object_and_fixups_vector;
    Object type, fixups, user_p, value, qualifier, name, temp, dot_uac_dot;
    Object dot_uac_index_dot, dot_uac_length_dot, dot_uac_sys_p_dot;
    Object dot_current_uac_dot, gensymed_symbol, gensymed_symbol_1;
    Object held_vector, attribute_1, attribute_value, dot_last_user_p_dot;
    Object ab_loop_iter_flag_, x2, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long attribute, ab_loop_bind_, next_index, length_1, gensymed_symbol_2;
    char dot_only_system_attrs_p_dot, temp_1;
    Object result;

    x_note_fn_call(136,180);
    if (Traversing_xml_object_p) {
	attribute_list = Nil;
	framep = xml_object_and_fixups_frame_p(node);
	object_and_fixups = node;
	object_and_fixups_vector = CONSP(object_and_fixups) && 
		EQ(M_CDR(object_and_fixups),Qab_structure) ? 
		M_CAR(object_and_fixups) : Nil;
	type = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
	if (!(EQ(type,Qprimitive_value) || EQ(type,Qtext))) {
	    if (EQ(type,Qsequence)) {
		fixups = structure_slot_1(object_and_fixups_vector,
			Qelements,Nil);
		if (fixups) {
		    user_p = Nil;
		    attribute = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			    (SI_Long)1L)));
		    value = Nil;
		  next_loop:
		    if (attribute >= ab_loop_bind_)
			goto end_loop;
		    value = evaluation_sequence_aref(fixups,FIX(attribute));
		    if ( !(framep && (EQ(FIX(attribute),Qab_class) ||  
			    !TRUEP(user_p) && EQ(FIX(attribute),Qid)) ||  
			    !TRUEP(user_p) && (EQ(FIX(attribute),
			    QRDF_COL_RESOURCE) || EQ(FIX(attribute),Qid) 
			    && INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			    (SI_Long)0L))) {
			if (user_p) {
			    if (EQ(SYMBOL_PACKAGE(FIX(attribute)),
				    Keyword_package_1)) {
				result = decompose_class_qualified_symbol(FIX(attribute));
				MVS_2(result,qualifier,name);
				temp = eval_cons_1(name,qualifier);
			    }
			    else
				temp = eval_cons_1(FIX(attribute),Nil);
			}
			else
			    temp = FIX(attribute);
			attribute_list = eval_cons_1(temp,attribute_list);
		    }
		    attribute = attribute + (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		}
	    }
	    else {
		fixups = structure_slot_1(object_and_fixups_vector,
			Qattributes,Nil);
		if (fixups) {
		    dot_uac_dot = 
			    structure_slot_1(object_and_fixups_vector,
			    Quser_attribute_count,Nil);
		    dot_only_system_attrs_p_dot =  !TRUEP(dot_uac_dot);
		    dot_uac_index_dot = CONSP(dot_uac_dot) && 
			    EQ(M_CDR(dot_uac_dot),Qsequence) ? 
			    FIX((SI_Long)0L) : Nil;
		    dot_uac_length_dot = dot_uac_index_dot ? 
			    FIXNUM_SUB1(ISVREF(M_CAR(dot_uac_dot),
			    (SI_Long)1L)) : Nil;
		    dot_uac_sys_p_dot = FIXNUMP(dot_uac_dot) ? T : Nil;
		    if (dot_only_system_attrs_p_dot)
			dot_current_uac_dot = Nil;
		    else if (dot_uac_index_dot) {
			gensymed_symbol = M_CAR(dot_uac_dot);
			gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
			dot_current_uac_dot = 
				FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(M_CAR(dot_uac_dot),
				IFIX(FIXNUM_ADD(gensymed_symbol_1,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(gensymed_symbol,
				(IFIX(gensymed_symbol_1) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(gensymed_symbol_1) & (SI_Long)1023L);
		    }
		    else if (dot_uac_sys_p_dot)
			dot_current_uac_dot = FIX((SI_Long)2L);
		    else
			dot_current_uac_dot = Qnil;
		    gensymed_symbol = fixups;
		    held_vector = Nil;
		    next_index = (SI_Long)1L;
		    length_1 = (SI_Long)0L;
		    attribute_1 = Nil;
		    attribute_value = Nil;
		    value = Nil;
		    dot_last_user_p_dot = Nil;
		    user_p = Nil;
		    ab_loop_iter_flag_ = T;
		    held_vector = M_CAR(gensymed_symbol);
		    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		  next_loop_1:
		    if (next_index >= length_1)
			goto end_loop_1;
		    attribute_1 = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,next_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),next_index & 
			    (SI_Long)1023L);
		    gensymed_symbol_2 = next_index + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,gensymed_symbol_2 + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(gensymed_symbol_2 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol_2 & (SI_Long)1023L);
		    value = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index = next_index + (SI_Long)2L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			dot_last_user_p_dot = user_p;
		    if (dot_only_system_attrs_p_dot)
			user_p = Nil;
		    else if ((SI_Long)0L < IFIX(dot_current_uac_dot)) {
			dot_current_uac_dot = FIXNUM_SUB1(dot_current_uac_dot);
			user_p = dot_last_user_p_dot;
		    }
		    else if (dot_uac_index_dot) {
			dot_uac_index_dot = FIXNUM_ADD1(dot_uac_index_dot);
			if (FIXNUM_LT(dot_uac_index_dot,dot_uac_length_dot)) {
			    gensymed_symbol = M_CAR(dot_uac_dot);
			    gensymed_symbol_1 = FIXNUM_ADD1(dot_uac_index_dot);
			    dot_current_uac_dot = 
				    FIXNUM_SUB1(FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(M_CAR(dot_uac_dot),
				    IFIX(FIXNUM_ADD(gensymed_symbol_1,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(gensymed_symbol,
				    (IFIX(gensymed_symbol_1) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(gensymed_symbol_1) & (SI_Long)1023L));
			}
			else
			    dot_current_uac_dot = Most_positive_fixnum;
			user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		    }
		    else if (dot_uac_sys_p_dot) {
			dot_uac_sys_p_dot = Nil;
			dot_current_uac_dot = FIXNUM_SUB1(dot_uac_dot);
			user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		    }
		    else {
			dot_current_uac_dot = Most_positive_fixnum;
			user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		    }
		    if ( !(framep && (EQ(attribute_1,Qab_class) ||  
			    !TRUEP(user_p) && EQ(attribute_1,Qid)) ||  
			    !TRUEP(user_p) && (EQ(attribute_1,
			    QRDF_COL_RESOURCE) || EQ(attribute_1,Qid) && 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			    (SI_Long)0L))) {
			if (user_p) {
			    if (EQ(SYMBOL_PACKAGE(attribute_1),
				    Keyword_package_1)) {
				result = decompose_class_qualified_symbol(attribute_1);
				MVS_2(result,qualifier,name);
				temp = eval_cons_1(name,qualifier);
			    }
			    else
				temp = eval_cons_1(attribute_1,Nil);
			}
			else
			    temp = attribute_1;
			attribute_list = eval_cons_1(temp,attribute_list);
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_1;
		  end_loop_1:;
		}
	    }
	}
	return nreverse(attribute_list);
    }
    else if (EQ(node_type,Qmodule))
	return VALUES_1(list_constant_2);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (In_write_module_as_clear_text_p)
		note_saving_frame(node);
	    return class_description_node_attributes(ISVREF(node,(SI_Long)1L));
	}
	else if (CONSP(node) && EQ(M_CDR(node),Qab_structure)) {
	    gensymed_symbol = node;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_2:
	    if (next_index >= length_1)
		goto end_loop_2;
	    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_2 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_2 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    ab_loopvar__2 = eval_cons_1(name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_2;
	  end_loop_2:
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
	else if (CONSP(node) && EQ(M_CDR(node),Qsequence))
	    return VALUES_1(FIXNUM_SUB1(ISVREF(M_CAR(node),(SI_Long)1L)));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* RECLAIM-NODE-ATTRIBUTES */
Object reclaim_node_attributes(node,node_type,attributes)
    Object node, node_type, attributes;
{
    Object a, ab_loop_list_;

    x_note_fn_call(136,181);
    if (Traversing_xml_object_p) {
	a = Nil;
	ab_loop_list_ = attributes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	a = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(a))
	    reclaim_eval_cons_1(a);
	goto next_loop;
      end_loop:
	reclaim_eval_list_1(attributes);
	return VALUES_1(Qnil);
    }
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (CONSP(node) && EQ(M_CDR(node),Qab_structure))
	    return reclaim_eval_list_1(attributes);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(All_classes_for_cached_class_description_node_attributes, Qall_classes_for_cached_class_description_node_attributes);

DEFINE_VARIABLE_WITH_SYMBOL(All_classes_for_cached_class_description_node_attributes_for_external_definition, Qall_classes_for_cached_class_description_node_attributes_for_external_definition);

Object Cached_class_node_attributes_prop = UNBOUND;

Object Cached_class_node_attributes_for_external_definition_prop = UNBOUND;

static Object Qcached_class_node_attributes_for_external_definition;  /* cached-class-node-attributes-for-external-definition */

static Object Qcached_class_node_attributes;  /* cached-class-node-attributes */

/* CLASS-DESCRIPTION-NODE-ATTRIBUTES */
Object class_description_node_attributes(class_description)
    Object class_description;
{
    Object class_1, temp;

    x_note_fn_call(136,182);
    class_1 = ISVREF(class_description,(SI_Long)1L);
    if (EQ(Traversing_kb_attribute,Qexternal_definitions)) {
	temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
		Qcached_class_node_attributes_for_external_definition);
	if (temp)
	    return VALUES_1(temp);
	else {
	    All_classes_for_cached_class_description_node_attributes_for_external_definition 
		    = eval_cons_1(class_1,
		    All_classes_for_cached_class_description_node_attributes_for_external_definition);
	    return mutate_global_property(class_1,
		    compute_class_description_node_attributes(class_description),
		    Qcached_class_node_attributes_for_external_definition);
	}
    }
    else {
	temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
		Qcached_class_node_attributes);
	if (temp)
	    return VALUES_1(temp);
	else {
	    All_classes_for_cached_class_description_node_attributes = 
		    eval_cons_1(class_1,
		    All_classes_for_cached_class_description_node_attributes);
	    return mutate_global_property(class_1,
		    compute_class_description_node_attributes(class_description),
		    Qcached_class_node_attributes);
	}
    }
}

/* DECACHE-ALL-CACHED-CLASS-NODE-ATTRIBUTES */
Object decache_all_cached_class_node_attributes()
{
    Object class_1, ab_loop_list_, attributes;

    x_note_fn_call(136,183);
    class_1 = Nil;
    ab_loop_list_ = All_classes_for_cached_class_description_node_attributes;
    attributes = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attributes = getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
	    Qcached_class_node_attributes);
    mutate_global_property(class_1,Nil,Qcached_class_node_attributes);
    reclaim_eval_list_1(attributes);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(All_classes_for_cached_class_description_node_attributes);
    All_classes_for_cached_class_description_node_attributes = Nil;
    class_1 = Nil;
    ab_loop_list_ = 
	    All_classes_for_cached_class_description_node_attributes_for_external_definition;
    attributes = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attributes = getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
	    Qcached_class_node_attributes_for_external_definition);
    mutate_global_property(class_1,Nil,
	    Qcached_class_node_attributes_for_external_definition);
    reclaim_eval_list_1(attributes);
    goto next_loop_1;
  end_loop_1:
    reclaim_eval_list_1(All_classes_for_cached_class_description_node_attributes_for_external_definition);
    All_classes_for_cached_class_description_node_attributes_for_external_definition 
	    = Nil;
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Exclude_secondary_attributes, Qexclude_secondary_attributes);

Object Secondary_attributes = UNBOUND;

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object Qfollowing_item_in_workspace_layering;  /* following-item-in-workspace-layering */

static Object Qconnection_style;   /* connection-style */

static Object Qconnection_is_directed;  /* connection-is-directed */

static Object Qconnection_vertices;  /* connection-vertices */

/* COMPUTE-VAS-FOR-COMPUTE-CLASS-DESCRIPTION-NODE-ATTRIBUTES */
Object compute_vas_for_compute_class_description_node_attributes(class_description)
    Object class_description;
{
    Object temp, non_local_attr, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_1, all_virtual_attr_name_list, attr_name;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_2;

    x_note_fn_call(136,184);
    temp = all_virtual_attributes_for_class(2,class_description,Nil);
    non_local_attr = Nil;
    ab_loop_list_ = Virtual_attributes_not_local_to_a_class;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    non_local_attr = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (applicable_and_not_deprecated_virtual_attribute_p(class_description,
	    get_property_value_function(3,
	    get_symbol_properties_function(non_local_attr),
	    Qvirtual_attribute,Nil),Nil)) {
	ab_loopvar__2 = eval_cons_1(non_local_attr,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    all_virtual_attr_name_list = nconc2(temp,temp_1);
    attr_name = Nil;
    ab_loop_list_ = all_virtual_attr_name_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    attr_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(Traversing_kb_attribute,Qexternal_definitions) &&  
	    !TRUEP(memq_function(attr_name,list_constant_3)) &&  
	    !(Exclude_secondary_attributes && memq_function(attr_name,
	    Secondary_attributes))) {
	sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp_2 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !(temp_2 ? TRUEP(memq_function(attr_name,
		list_constant_4)) : TRUEP(Nil));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? ISVREF(get_property_value_function(3,
	    get_symbol_properties_function(attr_name),Qvirtual_attribute,
	    Nil),(SI_Long)7L) && memq_function(attr_name,list_constant_5) 
	    || EQ(attr_name,Qfollowing_item_in_workspace_layering) || 
	    EQ(attr_name,Qconnection_input) || EQ(attr_name,
	    Qconnection_output) || EQ(attr_name,Qconnection_style) || 
	    EQ(attr_name,Qconnection_is_directed) || EQ(attr_name,
	    Qconnection_vertices) : TRUEP(Nil)) {
	ab_loopvar__2 = eval_cons_1(get_property_value_function(3,
		get_symbol_properties_function(attr_name),
		Qvirtual_attribute,Nil),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_eval_list_1(all_virtual_attr_name_list);
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

Object Reason_to_exclude_slot_name_prop = UNBOUND;

static Object Qreason_to_exclude_slot_name;  /* reason-to-exclude-slot-name */

/* SET-REASON-TO-EXCLUDE-SLOT-NAMES-1 */
Object set_reason_to_exclude_slot_names_1(value,names)
    Object value, names;
{
    Object name, ab_loop_list_;

    x_note_fn_call(136,185);
    name = Nil;
    ab_loop_list_ = names;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(name,value,Qreason_to_exclude_slot_name);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qunknown;            /* unknown */

static Object Qframe_flags;        /* frame-flags */

static Object Qnot_saved_in_clear_text;  /* not-saved-in-clear-text */

static Object Qdo_not_save;        /* do-not-save */

static Object Qsave;               /* save */

static Object Qline_pattern;       /* line-pattern */

static Object Qconnection_arrows;  /* connection-arrows */

static Object Qnot_savable;        /* not-savable */

static Object Qno_type;            /* no-type */

static Object Qpreviously_put_in_attribute_tables;  /* previously-put-in-attribute-tables */

static Object Qdepreciated;        /* depreciated */

static Object Qno_category_in_type_specification;  /* no-category-in-type-specification */

static Object Qstatement;          /* statement */

static Object Qdata_type_of_variable_or_parameter;  /* data-type-of-variable-or-parameter */

static Object list_constant_6;     /* # */

static Object Qdependant;          /* dependant */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qslot_value_writer;  /* slot-value-writer */

static Object Qneither_rw_cei_nor_slot_value_writer;  /* neither-rw-cei-nor-slot-value-writer */

/* REASON-TO-EXCLUDE-SLOT-DESCRIPTION-FOR-COMPUTE-CLASS-DESCRIPTION-NODE-ATTRIBUTES */
Object reason_to_exclude_slot_description_for_compute_class_description_node_attributes(attribute)
    Object attribute;
{
    Object name, type_qm, category_qm, reason_symbol, slot_features;
    Object category_evaluator_interface;
    char temp;

    x_note_fn_call(136,186);
    name = ISVREF(attribute,(SI_Long)2L);
    type_qm = Nil;
    category_qm = Nil;
    reason_symbol = Nil;
    if (ISVREF(attribute,(SI_Long)8L))
	return VALUES_1(Nil);
    else {
	reason_symbol = getfq_function(INLINE_SYMBOL_PLIST(name),
		Qreason_to_exclude_slot_name,Qunknown);
	if ( !EQ(Qunknown,reason_symbol))
	    return VALUES_1(reason_symbol);
	else if (EQ(name,Qframe_flags) &&  !TRUEP(assq_function(Qtype,
		ISVREF(attribute,(SI_Long)9L))))
	    return VALUES_1(Qnot_saved_in_clear_text);
	else {
	    slot_features = ISVREF(attribute,(SI_Long)9L);
	    temp = assq_function(Qtype,slot_features) ?  
		    !TRUEP(assq_function(Qdo_not_save,slot_features)) : 
		    TRUEP(assq_function(Qsave,slot_features));
	    if (temp);
	    else
		temp = EQ(name,Qframe_flags);
	    if (temp);
	    else {
		temp = EQ(name,Qconnection_style);
		if (temp);
		else
		    temp = EQ(name,Qline_pattern);
		if (temp);
		else
		    temp = EQ(name,Qconnection_arrows);
	    }
	    if ( !temp)
		return VALUES_1(Qnot_savable);
	    else {
		type_qm = assq_function(Qtype,ISVREF(attribute,(SI_Long)9L));
		if ( !TRUEP(type_qm))
		    return VALUES_1(Qno_type);
		else if (assq_function(Qpreviously_put_in_attribute_tables,
			ISVREF(attribute,(SI_Long)9L)))
		    return VALUES_1(Qdepreciated);
		else if (memq_function(Qtext,CDDR(type_qm)))
		    return VALUES_1(Nil);
		else {
		    category_qm = SECOND(type_qm);
		    if ( !TRUEP(category_qm))
			return VALUES_1(Qno_category_in_type_specification);
		    else if (EQ(category_qm,Qstatement) || EQ(name,
			    Qdata_type_of_variable_or_parameter) && 
			    memq_function(category_qm,list_constant_6))
			return VALUES_1(Qdependant);
		    else {
			category_evaluator_interface = 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
				Qcategory_evaluator_interface);
			if (category_evaluator_interface && 
				ISVREF(category_evaluator_interface,
				(SI_Long)2L)) {
			    category_evaluator_interface = 
				    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
				    Qcategory_evaluator_interface);
			    temp = category_evaluator_interface ? 
				    TRUEP(ISVREF(category_evaluator_interface,
				    (SI_Long)3L)) : TRUEP(Qnil);
			}
			else
			    temp = TRUEP(Nil);
			if (temp);
			else
			    temp = 
				    TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
				    Qslot_value_writer));
			if ( !temp)
			    return VALUES_1(Qneither_rw_cei_nor_slot_value_writer);
			else
			    return VALUES_1(Qnil);
		    }
		}
	    }
	}
    }
}

/* COMPUTE-SDS-FOR-COMPUTE-CLASS-DESCRIPTION-NODE-ATTRIBUTES */
Object compute_sds_for_compute_class_description_node_attributes(class_description)
    Object class_description;
{
    Object attribute, ab_loop_list_, attr_name, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(136,187);
    attribute = Nil;
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
    attr_name = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attr_name = ISVREF(attribute,(SI_Long)2L);
    if ( !(Exclude_secondary_attributes &&  !TRUEP(ISVREF(attribute,
	    (SI_Long)8L)) && memq_function(attr_name,Secondary_attributes) 
	    || 
	    reason_to_exclude_slot_description_for_compute_class_description_node_attributes(attribute) 
	    || In_find_stripped_text_slot_p &&  
	    !TRUEP(possible_text_stripped_or_proprietary_package_attribute(attribute)))) 
		{
	ab_loopvar__2 = eval_cons_1(attribute,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* COMPUTE-CLASS-DESCRIPTION-NODE-ATTRIBUTES */
Object compute_class_description_node_attributes(class_description)
    Object class_description;
{
    Object temp;

    x_note_fn_call(136,188);
    temp = 
	    compute_sds_for_compute_class_description_node_attributes(class_description);
    return VALUES_1(nconc2(temp, !TRUEP(In_find_stripped_text_slot_p) ? 
	    compute_vas_for_compute_class_description_node_attributes(class_description) 
	    : Nil));
}

static Object Qg2_defstruct_structure_name_virtual_attribute_g2_struct;  /* g2-defstruct-structure-name::virtual-attribute-g2-struct */

/* NODE-ATTRIBUTE-NAME */
Object node_attribute_name(node,node_type,attribute)
    Object node, node_type, attribute;
{
    Object pretty_slot_name, class_or_frame_qm, temp;

    x_note_fn_call(136,189);
    if (FIXNUMP(attribute))
	return VALUES_1(attribute);
    else if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct)) {
	if (ISVREF(attribute,(SI_Long)8L))
	    return VALUES_1(ISVREF(attribute,(SI_Long)2L));
	else {
	    pretty_slot_name = ISVREF(attribute,(SI_Long)2L);
	    class_or_frame_qm = ISVREF(attribute,(SI_Long)3L);
	    temp = get_alias_for_slot_name_if_any(pretty_slot_name,
		    class_or_frame_qm);
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(pretty_slot_name);
	}
    }
    else if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_virtual_attribute_g2_struct))
	return VALUES_1(ISVREF(attribute,(SI_Long)1L));
    else if (ATOM(attribute))
	return VALUES_1(attribute);
    else
	return VALUES_1(CAR(attribute));
}

/* NODE-ATTRIBUTE-NAME-QUALIFIER */
Object node_attribute_name_qualifier(node,node_type,attribute)
    Object node, node_type, attribute;
{
    Object slot_description, class_description, temp;
    char temp_1;

    x_note_fn_call(136,190);
    if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,(SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct) && 
	    ISVREF(attribute,(SI_Long)8L)) {
	slot_description = attribute;
	class_description = ISVREF(node,(SI_Long)1L);
	if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	    temp = ISVREF(slot_description,(SI_Long)3L);
	    temp_1 =  !EQ(temp,
		    ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
		    (SI_Long)2L),class_description,Nil),(SI_Long)3L));
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(ISVREF(attribute,(SI_Long)3L));
    else if (ATOM(attribute))
	return VALUES_1(Nil);
    else
	return VALUES_1(CDR(attribute));
}

/* NODE-ATTRIBUTE-UNIQUE-NAME */
Object node_attribute_unique_name(node,node_type,attribute)
    Object node, node_type, attribute;
{
    Object pretty_slot_name, class_or_frame_qm, temp;

    x_note_fn_call(136,191);
    if (FIXNUMP(attribute))
	return VALUES_1(attribute);
    else if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct)) {
	if (ISVREF(attribute,(SI_Long)8L))
	    return VALUES_1(ISVREF(attribute,(SI_Long)1L));
	else {
	    pretty_slot_name = ISVREF(attribute,(SI_Long)2L);
	    class_or_frame_qm = ISVREF(attribute,(SI_Long)3L);
	    temp = get_alias_for_slot_name_if_any(pretty_slot_name,
		    class_or_frame_qm);
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(pretty_slot_name);
	}
    }
    else if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_virtual_attribute_g2_struct))
	return VALUES_1(ISVREF(attribute,(SI_Long)1L));
    else if (ATOM(attribute))
	return VALUES_1(attribute);
    else
	return VALUES_1(CAR(attribute));
}

static Object Qmajor_version;      /* major-version */

static Object Qminor_version;      /* minor-version */

static Object Qrelease_quality;    /* release-quality */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object Qrevision;           /* revision */

static Object Qbuild_identification;  /* build-identification */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object list_constant_7;     /* # */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qsubworkspaces;      /* subworkspaces */

static Object Qframe_edit_timestamp_qm;  /* frame-edit-timestamp? */

static Object Qitem_reference;     /* item-reference */

/* NODE-ATTRIBUTE-VALUE */
Object node_attribute_value(node,node_type,attribute)
    Object node, node_type, attribute;
{
    Object category_type, gensymed_symbol, temp, item_or_value, x2, temp_2;
    Object temp_3, name_list, name, ab_loop_list_, cdef, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, x, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_4, entry_hash, tail, head, new_cons;
    Object svref_new_value, gensymed_symbol_2, gensymed_symbol_3;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, workspace;
    Object write_proprietary_package_while_saving_xml_kb;
    SI_Long gensymed_symbol_1, svref_arg_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,192);
    category_type = Nil;
    if (Traversing_xml_object_p) {
	if (CONSP(attribute))
	    return get_xml_object_attribute(node,CDR(attribute) ? 
		    make_unique_slot_name_symbol(CDR(attribute),
		    CAR(attribute)) : CAR(attribute),T,Nil);
	else
	    return get_xml_object_attribute(node,attribute,Nil,Nil);
    }
    if (EQ(node_type,Qmodule)) {
	if (EQ(attribute,Qversion)) {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
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
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qmajor_version;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qmajor_version;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = 
			Major_version_number_of_current_gensym_product_line;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
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
		item_or_value = 
			Major_version_number_of_current_gensym_product_line;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qminor_version;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qminor_version;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = 
			Minor_version_number_of_current_gensym_product_line;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = 
			Minor_version_number_of_current_gensym_product_line;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp,FIX((SI_Long)4L)) = temp_2;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qrelease_quality;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)5L)) = Qrelease_quality;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		if ( !TRUEP(T))
		    temp_3 = array_constant_8;
		else
		    switch (INTEGER_TO_CHAR(Release_quality_of_current_gensym_product_line)) 
				{
		      case 0:
			temp_3 = array_constant_10;
			break;
		      case 1:
			temp_3 = array_constant_11;
			break;
		      case 2:
			temp_3 = array_constant_12;
			break;
		      case 3:
			temp_3 = array_constant_8;
			break;
		      default:
			temp_3 = array_constant_8;
			break;
		    }
		item_or_value = copy_wide_string(temp_3);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		if ( !TRUEP(T))
		    temp_3 = array_constant_8;
		else
		    switch (INTEGER_TO_CHAR(Release_quality_of_current_gensym_product_line)) 
				{
		      case 0:
			temp_3 = array_constant_10;
			break;
		      case 1:
			temp_3 = array_constant_11;
			break;
		      case 2:
			temp_3 = array_constant_12;
			break;
		      case 3:
			temp_3 = array_constant_8;
			break;
		      default:
			temp_3 = array_constant_8;
			break;
		    }
		item_or_value = copy_wide_string(temp_3);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp,FIX((SI_Long)6L)) = temp_2;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qrevision;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)7L)) = Qrevision;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Revision_number_of_current_gensym_product_line;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Revision_number_of_current_gensym_product_line;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp,FIX((SI_Long)8L)) = temp_2;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)11L)) = 
			Qbuild_identification;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)9L)) = Qbuild_identification;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = 
			copy_as_wide_string(Build_identification_string);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = 
			copy_as_wide_string(Build_identification_string);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp,FIX((SI_Long)10L)) = temp_2;
	    }
	    return eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else if (EQ(attribute,Qsystem_tables))
	    return get_xml_system_tables(node);
	else if (EQ(attribute,Qexternal_definitions)) {
	    name_list = get_names_of_external_definitions_for_module(node);
	    name = Nil;
	    ab_loop_list_ = name_list;
	    cdef = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    cdef = lookup_global_or_kb_specific_property_value(name,
		    Class_definition_gkbprop);
	    if ( !((SI_Long)0L != (IFIX(ISVREF(cdef,(SI_Long)5L)) & 
		    (SI_Long)262144L))) {
		x = ISVREF(cdef,(SI_Long)20L);
		if (SYMBOLP(x)) {
		    skip_list = CDR(Symbol_properties_table);
		    key_value = x;
		    key_hash_value = SXHASH_SYMBOL_1(x) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_1:
		    if (level < ab_loop_bind_)
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_2:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_4 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_4,temp_3);
		    MVS_2(result,succ,marked);
		  next_loop_3:
		    if ( !TRUEP(marked))
			goto end_loop_2;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_4 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_4,temp_3);
		    MVS_2(result,succ,marked);
		    goto next_loop_3;
		  end_loop_2:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_1;
		    goto next_loop_2;
		  end_loop_3:
		  end_1:
		    level = level - (SI_Long)1L;
		    goto next_loop_1;
		  end_loop_1:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = x;
			temp_4 = Symbol_properties_table;
			temp_3 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum));
			tail = 
				make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				Nil);
			head = 
				make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				tail);
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp = Available_lookup_conses_vector;
			    temp_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp,temp_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp = Available_lookup_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp,temp_2) = Nil;
			    }
			    gensymed_symbol_2 = new_cons;
			}
			else
			    gensymed_symbol_2 = Nil;
			if ( !TRUEP(gensymed_symbol_2))
			    gensymed_symbol_2 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_2) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp = Available_lookup_conses_vector;
			    temp_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp,temp_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp = Available_lookup_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp,temp_2) = Nil;
			    }
			    gensymed_symbol_3 = new_cons;
			}
			else
			    gensymed_symbol_3 = Nil;
			if ( !TRUEP(gensymed_symbol_3))
			    gensymed_symbol_3 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_3) = head;
			M_CDR(gensymed_symbol_3) = tail;
			inline_note_allocate_cons(gensymed_symbol_3,Qlookup);
			M_CDR(gensymed_symbol_2) = gensymed_symbol_3;
			inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
			gensymed_symbol = set_skip_list_entry(temp_4,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_3,gensymed_symbol_2);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			    & IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_4:
		    if (level < ab_loop_bind_)
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_5:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_4 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_4,temp_3);
		    MVS_2(result,succ,marked);
		  next_loop_6:
		    if ( !TRUEP(marked))
			goto end_loop_5;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_4 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_4,temp_3);
		    MVS_2(result,succ,marked);
		    goto next_loop_6;
		  end_loop_5:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_2;
		    goto next_loop_5;
		  end_loop_6:
		  end_2:
		    level = level - (SI_Long)1L;
		    goto next_loop_4;
		  end_loop_4:;
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_7:
			if (level < ab_loop_bind_)
			    goto end_loop_7;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_8:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_4 = ATOMIC_REF_OBJECT(reference);
			temp_3 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_4,temp_3);
			MVS_2(result,succ,marked);
		      next_loop_9:
			if ( !TRUEP(marked))
			    goto end_loop_8;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_4 = ATOMIC_REF_OBJECT(reference);
			temp_3 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_4,temp_3);
			MVS_2(result,succ,marked);
			goto next_loop_9;
		      end_loop_8:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_3;
			goto next_loop_8;
		      end_loop_9:
		      end_3:
			level = level - (SI_Long)1L;
			goto next_loop_7;
		      end_loop_7:;
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (kb_specific_value);
			else
			    kb_specific_value = No_specific_property_value;
		    }
		    else
			kb_specific_value = No_specific_property_value;
		    if ( !EQ(kb_specific_value,No_specific_property_value))
			resulting_value = kb_specific_value;
		    else {
			skip_list = CDR(global_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_10:
			if (level < ab_loop_bind_)
			    goto end_loop_10;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_11:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_4 = ATOMIC_REF_OBJECT(reference);
			temp_3 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_4,temp_3);
			MVS_2(result,succ,marked);
		      next_loop_12:
			if ( !TRUEP(marked))
			    goto end_loop_11;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_4 = ATOMIC_REF_OBJECT(reference);
			temp_3 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_4,temp_3);
			MVS_2(result,succ,marked);
			goto next_loop_12;
		      end_loop_11:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_4;
			goto next_loop_11;
		      end_loop_12:
		      end_4:
			level = level - (SI_Long)1L;
			goto next_loop_10;
		      end_loop_10:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    temp_1 = TRUEP(resulting_value);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		gensymed_symbol = ACCESS_ONCE(ISVREF(cdef,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		temp_1 =  !TRUEP(gensymed_symbol);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp_3 = ISVREF(cdef,(SI_Long)21L);
		temp_1 = EQUAL(temp_3,list_constant_7);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		ab_loopvar__2 = eval_cons_1(cdef,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop;
	  end_loop:
	    reclaim_eval_list_1(name_list);
	    temp_3 = ab_loopvar_;
	    goto end_5;
	    temp_3 = Qnil;
	  end_5:;
	    return allocate_evaluation_sequence(temp_3);
	}
	else if (EQ(attribute,Qworkspaces)) {
	    workspace = Nil;
	    ab_loop_list_ = lookup_kb_specific_property_value(node,
		    Workspaces_belonging_to_this_module_kbprop);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_13:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_13;
	    workspace = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ISVREF(workspace,(SI_Long)18L)) && (SI_Long)0L != 
		    (IFIX(ISVREF(workspace,(SI_Long)4L)) & (SI_Long)1L)) {
		ab_loopvar__2 = eval_cons_1(workspace,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_13;
	  end_loop_13:
	    temp_3 = ab_loopvar_;
	    goto end_6;
	    temp_3 = Qnil;
	  end_6:;
	    return allocate_evaluation_sequence(sort_items_in_definition_order(temp_3));
	}
	else if (EQ(attribute,Qformats))
	    return allocate_evaluation_sequence(sort_items_in_definition_order(copy_list_using_eval_conses_1(get_formats_for_current_module())));
	else if (EQ(attribute,Qpanes))
	    return get_xml_pane_information();
	else if (EQ(attribute,Qchecksums))
	    return get_xml_checksum_information();
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_virtual_attribute_g2_struct))
		return get_attribute_description_evaluation_value(node,
			attribute);
	    else if (ISVREF(attribute,(SI_Long)8L))
		return get_attribute_description_evaluation_value(node,
			attribute);
	    else if (EQ(ISVREF(attribute,(SI_Long)2L),
		    Qslot_group_for_block_qm))
		return get_slot_description_value(node,attribute);
	    else if (EQ(ISVREF(attribute,(SI_Long)2L),Qsubworkspaces)) {
		temp_3 = ISVREF(node,(SI_Long)18L);
		return VALUES_1(CAR(temp_3));
	    }
	    else if ( !TRUEP(assq_function(Qtype,ISVREF(attribute,
		    (SI_Long)9L))))
		return get_slot_description_value(node,attribute);
	    else {
		category_type = text_or_the_text_of_slot_p(attribute);
		if (category_type) {
		    if (EQ(category_type,Qframe_edit_timestamp_qm))
			return get_slot_description_value(node,attribute);
		    else {
			write_proprietary_package_while_saving_xml_kb = T;
			PUSH_SPECIAL_WITH_SYMBOL(Write_proprietary_package_while_saving_xml_kb,Qwrite_proprietary_package_while_saving_xml_kb,write_proprietary_package_while_saving_xml_kb,
				0);
			  result = make_text_string_representation_for_slot_value_itself(node,
				  get_slot_description_value(node,
				  attribute),assq_function(Qtype,
				  ISVREF(attribute,(SI_Long)9L)));
			POP_SPECIAL();
			return result;
		    }
		}
		else
		    return get_attribute_description_evaluation_value(node,
			    attribute);
	    }
	}
	else if (CONSP(node) && EQ(M_CDR(node),Qab_structure))
	    return estructure_slot(node,attribute,Nil);
	else if (CONSP(node) && EQ(M_CDR(node),Qsequence)) {
	    gensymed_symbol = M_CAR(node);
	    gensymed_symbol_2 = FIXNUM_ADD1(attribute);
	    item_or_value = FIXNUM_LE(ISVREF(M_CAR(node),(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(M_CAR(node),
		    IFIX(FIXNUM_ADD(gensymed_symbol_2,
		    Managed_array_index_offset))) : 
		    ISVREF(ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_2) 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(gensymed_symbol_2) & (SI_Long)1023L);
	    if (CONSP(item_or_value) && EQ(M_CDR(item_or_value),
		    Qitem_reference))
		return VALUES_1(ISVREF(M_CAR(item_or_value),(SI_Long)3L));
	    else
		return VALUES_1(item_or_value);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

/* NODE-ATTRIBUTE-UNIT */
Object node_attribute_unit(node,node_type,attribute)
    Object node, node_type, attribute;
{
    Object x2, value, temp_1;
    char temp;

    x_note_fn_call(136,193);
    if (Traversing_xml_object_p)
	return xml_object_unit(node_attribute_value(node,node_type,attribute));
    if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ((temp ? SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_slot_description_g2_struct) : 
		TRUEP(Nil)) ? TRUEP(ISVREF(attribute,(SI_Long)8L)) : 
		TRUEP(Nil)) {
	    value = ISVREF(ISVREF(node,(SI_Long)0L),IFIX(ISVREF(attribute,
		    (SI_Long)8L)));
	    if (CONSP(value) && slot_value_number_p(M_CAR(value))) {
		temp_1 = M_CDR(value);
		temp = CONSP(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(M_CAR(M_CDR(value)));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_details;  /* simulation-details */

/* TEXT-OR-THE-TEXT-OF-SLOT-P */
Object text_or_the_text_of_slot_p(attribute)
    Object attribute;
{
    Object type_qm, category_qm, category_evaluator_interface, temp_1;
    char temp;

    x_note_fn_call(136,194);
    if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,(SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct) &&  
	    !TRUEP(ISVREF(attribute,(SI_Long)8L))) {
	type_qm = assq_function(Qtype,ISVREF(attribute,(SI_Long)9L));
	category_qm = SECOND(type_qm);
	temp = TRUEP(memq_function(Qtext,CDDR(type_qm)));
	if (temp);
	else {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
		    Qcategory_evaluator_interface);
	    if (category_evaluator_interface && 
		    ISVREF(category_evaluator_interface,(SI_Long)2L)) {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
			Qcategory_evaluator_interface);
		temp = category_evaluator_interface ? 
			TRUEP(ISVREF(category_evaluator_interface,
			(SI_Long)3L)) : TRUEP(Qnil);
		if (temp);
		else
		    temp = EQ(ISVREF(attribute,(SI_Long)2L),
			    Qsimulation_details);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	}
	if (temp) {
	    temp_1 = category_qm;
	    if (temp_1);
	    else
		temp_1 = Qfree;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* CHECK-NODE-ATTRIBUTE-VALUE */
Object check_node_attribute_value(node,node_type,attribute,value,type)
    Object node, node_type, attribute, value, type;
{
    Object type_qm, x2, temp_1, category_qm, category_evaluator_interface;
    char temp;

    x_note_fn_call(136,195);
    if (Traversing_xml_object_p)
	return VALUES_1(Nil);
    if (EQ(node_type,Qmodule))
	return VALUES_1(Nil);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	type_qm = Nil;
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_virtual_attribute_g2_struct))
		return VALUES_1(Nil);
	    else if (ISVREF(attribute,(SI_Long)8L))
		return check_attribute_for_clear_text(4,node,
			node_attribute_unique_name(node,node_type,
			attribute),value,Nil);
	    else {
		temp_1 = EQ(ISVREF(attribute,(SI_Long)2L),
			Qslot_group_for_block_qm) ? T : Nil;
		if (temp_1)
		    return VALUES_1(temp_1);
		else {
		    temp_1 = EQ(ISVREF(attribute,(SI_Long)2L),
			    Qsubworkspaces) ? T : Nil;
		    if (temp_1)
			return VALUES_1(temp_1);
		    else {
			type_qm = assq_function(Qtype,ISVREF(attribute,
				(SI_Long)9L));
			temp = TRUEP(memq_function(Qtext,CDDR(type_qm)));
			if (temp);
			else {
			    category_qm = SECOND(type_qm);
			    category_evaluator_interface = 
				    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
				    Qcategory_evaluator_interface);
			    if (category_evaluator_interface && 
				    ISVREF(category_evaluator_interface,
				    (SI_Long)2L)) {
				category_evaluator_interface = 
					getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
					Qcategory_evaluator_interface);
				temp = category_evaluator_interface ? 
					TRUEP(ISVREF(category_evaluator_interface,
					(SI_Long)3L)) : TRUEP(Qnil);
				if (temp);
				else
				    temp = EQ(ISVREF(attribute,
					    (SI_Long)2L),Qsimulation_details);
			    }
			    else
				temp = TRUEP(Nil);
			    temp =  !temp;
			}
			if (temp)
			    return VALUES_1(Nil);
			else
			    return check_attribute_for_clear_text(4,node,
				    node_attribute_unique_name(node,
				    node_type,attribute),value,Nil);
		    }
		}
	    }
	}
	else {
	    temp_1 = CONSP(node) ? (EQ(M_CDR(node),Qab_structure) ? T : 
		    Nil) : Qnil;
	    if (temp_1)
		return VALUES_1(temp_1);
	    else {
		temp_1 = CONSP(node) ? (EQ(M_CDR(node),Qsequence) ? T : 
			Nil) : Qnil;
		if (temp_1)
		    return VALUES_1(temp_1);
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
    else
	return VALUES_1(Qnil);
}

/* RECLAIM-NODE-ATTRIBUTE-VALUE */
Object reclaim_node_attribute_value(node,node_type,attribute,value)
    Object node, node_type, attribute, value;
{
    Object x2, temp_1;
    char temp;

    x_note_fn_call(136,196);
    if (Traversing_xml_object_p)
	return VALUES_1(Nil);
    if (EQ(node_type,Qmodule)) {
	if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
	    return reclaim_if_evaluation_value_1(value);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_virtual_attribute_g2_struct)) 
			{
		if ( !(FIXNUMP(value) || SYMBOLP(value) || 
			SIMPLE_VECTOR_P(value)))
		    return reclaim_if_evaluation_value_1(value);
		else
		    return VALUES_1(Nil);
	    }
	    else if (ISVREF(attribute,(SI_Long)8L)) {
		if ( !(FIXNUMP(value) || SYMBOLP(value) || 
			SIMPLE_VECTOR_P(value)))
		    return reclaim_if_evaluation_value_1(value);
		else
		    return VALUES_1(Nil);
	    }
	    else {
		temp_1 = EQ(ISVREF(attribute,(SI_Long)2L),
			Qslot_group_for_block_qm) ? T : Nil;
		if (temp_1)
		    return VALUES_1(temp_1);
		else {
		    temp_1 = EQ(ISVREF(attribute,(SI_Long)2L),
			    Qsubworkspaces) ? T : Nil;
		    if (temp_1)
			return VALUES_1(temp_1);
		    else if ( !(FIXNUMP(value) || SYMBOLP(value) || 
			    SIMPLE_VECTOR_P(value)))
			return reclaim_if_evaluation_value_1(value);
		    else
			return VALUES_1(Nil);
		}
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qraw;                /* raw */

/* NODE-ATTRIBUTE-TYPE */
Object node_attribute_type(node,node_type,attribute)
    Object node, node_type, attribute;
{
    Object x2, temp_1;
    char temp;

    x_note_fn_call(136,197);
    if (EQ(node_type,Qmodule))
	return VALUES_1(Qitem_or_evaluation_value);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = frame_attribute_type(attribute);
	    if (temp_1)
		return VALUES_1(temp_1);
	    else
		return VALUES_1(Qraw);
	}
	else
	    return VALUES_1(Qitem_or_evaluation_value);
    }
    else
	return VALUES_1(Qnil);
}

static Object Quuid;               /* uuid */

static Object Qprocedure_method_name;  /* procedure-method-name */

static Object list_constant_8;     /* # */

static Object Qminimum_width_of_text_box;  /* minimum-width-of-text-box */

static Object Qminimum_height_of_text_box;  /* minimum-height-of-text-box */

static Object Qicon_slot_group;    /* icon-slot-group */

static Object list_constant_9;     /* # */

/* FRAME-ATTRIBUTE-TYPE */
Object frame_attribute_type(attribute)
    Object attribute;
{
    Object name, type_qm, category_qm, slot_features;
    Object category_evaluator_interface;
    char temp;

    x_note_fn_call(136,198);
    name = SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,(SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct) ? 
	    ISVREF(attribute,(SI_Long)2L) : Qnil;
    type_qm = Nil;
    category_qm = Nil;
    if (SYMBOLP(attribute))
	return VALUES_1(Nil);
    else if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_virtual_attribute_g2_struct))
	return VALUES_1(Qitem_or_evaluation_value);
    else if ( !(SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct)))
	return VALUES_1(Nil);
    else if (ISVREF(attribute,(SI_Long)8L))
	return VALUES_1(Qitem_or_evaluation_value);
    else if (EQ(name,Quuid))
	return VALUES_1(Nil);
    else if (EQ(name,Qprocedure_method_name))
	return VALUES_1(Nil);
    else if (memq_function(name,list_constant_8))
	return VALUES_1(Nil);
    else if (EQ(name,Qminimum_width_of_text_box) || EQ(name,
	    Qminimum_height_of_text_box))
	return VALUES_1(Nil);
    else if (EQ(name,Qslot_group_for_block_qm)) {
	if ( !EQ(Traversing_kb_attribute,Qexternal_definitions))
	    return VALUES_1(Qicon_slot_group);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(name,Qsubworkspaces))
	return VALUES_1(Nil);
    else {
	slot_features = ISVREF(attribute,(SI_Long)9L);
	temp = assq_function(Qtype,slot_features) ?  
		!TRUEP(assq_function(Qdo_not_save,slot_features)) : 
		TRUEP(assq_function(Qsave,slot_features));
	if (temp);
	else
	    temp = EQ(name,Qconnection_style);
	if (temp);
	else {
	    temp = EQ(name,Qconnection_style);
	    if (temp);
	    else
		temp = EQ(name,Qline_pattern);
	    if (temp);
	    else
		temp = EQ(name,Qconnection_arrows);
	}
	if (temp);
	else
	    temp = EQ(name,Qframe_flags);
	if (temp) {
	    type_qm = assq_function(Qtype,ISVREF(attribute,(SI_Long)9L));
	    temp = TRUEP(type_qm);
	}
	else
	    temp = TRUEP(Nil);
	if ( !(temp ?  
		!TRUEP(assq_function(Qpreviously_put_in_attribute_tables,
		ISVREF(attribute,(SI_Long)9L))) : TRUEP(Nil)))
	    return VALUES_1(Nil);
	else if (memq_function(Qtext,CDDR(type_qm)))
	    return VALUES_1(Qitem_or_evaluation_value);
	else {
	    category_qm = SECOND(type_qm);
	    if ( !TRUEP(category_qm))
		return VALUES_1(Nil);
	    else if (memq_function(category_qm,list_constant_9))
		return VALUES_1(Nil);
	    else {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
			Qcategory_evaluator_interface);
		if (category_evaluator_interface && 
			ISVREF(category_evaluator_interface,(SI_Long)2L)) {
		    category_evaluator_interface = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
			    Qcategory_evaluator_interface);
		    temp = category_evaluator_interface ? 
			    TRUEP(ISVREF(category_evaluator_interface,
			    (SI_Long)3L)) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp);
		else
		    temp = EQ(name,Qsimulation_details);
		if (temp);
		else
		    temp = 
			    TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
			    Qslot_value_writer));
		if (temp)
		    return VALUES_1(Qitem_or_evaluation_value);
		else
		    return VALUES_1(Nil);
	    }
	}
    }
}

/* NODE-ATTRIBUTE-VALUE-IS-PRIMITIVE-P */
Object node_attribute_value_is_primitive_p(node,node_type,attribute,value,type)
    Object node, node_type, attribute, value, type;
{
    Object object_and_fixups, object_and_fixups_vector, vtype, fixups, val;
    Object gensymed_symbol, held_vector, attr_1, attribute_value, temp;
    SI_Long attr, ab_loop_bind_, next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(136,199);
    if (Traversing_xml_object_p) {
	object_and_fixups = value;
	object_and_fixups_vector = CONSP(object_and_fixups) && 
		EQ(M_CDR(object_and_fixups),Qab_structure) ? 
		M_CAR(object_and_fixups) : Nil;
	vtype = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
	if (EQ(vtype,Qprimitive_value) || EQ(vtype,Qtext))
	    return VALUES_1( !EQ(vtype,Qbinary) ? T : Nil);
	else if (EQ(vtype,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (EQ(vtype,Qsequence)) {
		if (fixups) {
		    attr = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			    (SI_Long)1L)));
		    val = Nil;
		  next_loop:
		    if (attr >= ab_loop_bind_)
			goto end_loop;
		    val = evaluation_sequence_aref(fixups,FIX(attr));
		    return VALUES_1(Nil);
		    attr = attr + (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		}
		return VALUES_1(T);
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (EQ(vtype,Qsequence)) {
		if (fixups) {
		    gensymed_symbol = fixups;
		    held_vector = Nil;
		    next_index = (SI_Long)1L;
		    length_1 = (SI_Long)0L;
		    attr_1 = Nil;
		    attribute_value = Nil;
		    val = Nil;
		    held_vector = M_CAR(gensymed_symbol);
		    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		  next_loop_1:
		    if (next_index >= length_1)
			goto end_loop_1;
		    attr_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,next_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),next_index & 
			    (SI_Long)1023L);
		    gensymed_symbol_1 = next_index + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,gensymed_symbol_1 + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol_1 & (SI_Long)1023L);
		    val = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index = next_index + (SI_Long)2L;
		    return VALUES_1(Nil);
		    goto next_loop_1;
		  end_loop_1:;
		}
		return VALUES_1(T);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else if (EQ(type,Qmodule))
	return VALUES_1( !TRUEP(value) ? T : Nil);
    else if (EQ(type,Qitem_or_evaluation_value)) {
	temp =  !TRUEP(value) ? T : Nil;
	if (temp);
	else
	    temp = SYMBOLP(value) ? T : Nil;
	if (temp);
	else
	    temp = FIXNUMP(value) ? T : Nil;
	if (temp);
	else
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L ? 
		    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L 
		    ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = INLINE_LONG_VECTOR_P(value) != (SI_Long)0L ? 
		    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L 
		    ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = text_string_p(value);
	if (temp);
	else
	    temp = CONSP(value) ? (EQ(M_CDR(value),Qtruth_value) ? T : 
		    Nil) : Qnil;
	if (temp)
	    return VALUES_1(temp);
	else if (CONSP(value) && EQ(M_CDR(value),Qsequence))
	    return VALUES_1((SI_Long)0L == 
		    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(value),(SI_Long)1L))) ? 
		    T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(type,Qquote) || EQ(type,Qraw))
	return VALUES_1(T);
    else
	return VALUES_1(Qnil);
}

/* NODE-ATTRIBUTE-VALUE-IS-UNTYPED-PRIMITIVE-P */
Object node_attribute_value_is_untyped_primitive_p(node,node_type,
	    attribute,value,type)
    Object node, node_type, attribute, value, type;
{
    Object object_and_fixups, object_and_fixups_vector, vtype, fixups;

    x_note_fn_call(136,200);
    if (Traversing_xml_object_p) {
	object_and_fixups = value;
	object_and_fixups_vector = CONSP(object_and_fixups) && 
		EQ(M_CDR(object_and_fixups),Qab_structure) ? 
		M_CAR(object_and_fixups) : Nil;
	vtype = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
	if (EQ(vtype,Qprimitive_value) || EQ(vtype,Qtext))
	    return VALUES_1(EQ(vtype,Qtext) ? T : Nil);
	else if (EQ(vtype,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    return VALUES_1(Nil);
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    return VALUES_1(Nil);
	}
    }
    else if (EQ(type,Qmodule))
	return VALUES_1( !TRUEP(value) ? T : Nil);
    else if (EQ(type,Qitem_or_evaluation_value)) {
	if (text_string_p(value) ||  !TRUEP(value))
	    return text_or_the_text_of_slot_p(attribute);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* NODE-ATTRIBUTE-BINARY-VALUE */
Object node_attribute_binary_value(node,node_type,attribute,value,type)
    Object node, node_type, attribute, value, type;
{
    x_note_fn_call(136,201);
    if (Traversing_xml_object_p)
	return get_xml_object(value);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (sequence_of_binary_text_strings_p(value))
	    return VALUES_1(value);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsystem_frame;       /* system-frame */

static Object Qparent_attribute_name;  /* parent-attribute-name */

/* NODE-ATTRIBUTE-VALUE-IS-DEFINITION-P */
Object node_attribute_value_is_definition_p(node,node_type,attribute,value,
	    type)
    Object node, node_type, attribute, value, type;
{
    Object x2, temp_1, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector, attribute_name;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(136,202);
    if (Traversing_xml_object_p)
	return VALUES_1( !TRUEP(get_xml_fixups(value,QRDF_COL_RESOURCE,
		Nil)) ? T : Nil);
    if (EQ(node_type,Qmodule))
	return VALUES_1(T);
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if ( !TRUEP(sequence_of_binary_text_strings_p(value))) {
	    if (SIMPLE_VECTOR_P(value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp_1 =  !temp ? T : Nil;
	    if (temp_1);
	    else if (EQ(Traversing_kb_attribute,Qsystem_tables)) {
		if (SIMPLE_VECTOR_P(value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(value,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    gensymed_symbol_1 = 
			    lookup_global_or_kb_specific_property_value(Qsystem_frame,
			    Class_description_gkbprop);
		    if (gensymed_symbol_1) {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_2 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_3 = (SI_Long)1L;
			    gensymed_symbol_4 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_3 = gensymed_symbol_3 << 
				    gensymed_symbol_4;
			    gensymed_symbol_2 = gensymed_symbol_2 & 
				    gensymed_symbol_3;
			    temp_1 = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
			}
			else
			    temp_1 = Nil;
		    }
		    else
			temp_1 = Nil;
		}
		else
		    temp_1 = Nil;
	    }
	    else
		temp_1 = Nil;
	    if (temp_1);
	    else if (EQ(Traversing_kb_attribute,Qexternal_definitions)) {
		if (SIMPLE_VECTOR_P(value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(value,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Definition_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp_1 = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
		    }
		    else
			temp_1 = Nil;
		}
		else
		    temp_1 = Nil;
	    }
	    else
		temp_1 = Nil;
	    if (temp_1)
		return VALUES_1(temp_1);
	    else {
		if (SIMPLE_VECTOR_P(node) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) > 
			(SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(node,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if ((temp ?  !EQ(Traversing_kb_attribute,
			Qexternal_definitions) : TRUEP(Nil)) ? 
			SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_slot_description_g2_struct) 
			: TRUEP(Nil)) {
		    temp_1 = ISVREF(attribute,(SI_Long)8L);
		    if (temp_1)
			return VALUES_1(temp_1);
		    else {
			attribute_name = ISVREF(attribute,(SI_Long)2L);
			temp_1 = EQ(attribute_name,Qsubworkspaces) ? T : Nil;
			if (temp_1);
			else
			    temp_1 = EQ(attribute_name,
				    Qsimulation_details) ? T : Nil;
			if (temp_1)
			    return VALUES_1(temp_1);
			else if (EQ(attribute_name,
				get_lookup_slot_value_given_default(value,
				Qparent_attribute_name,Nil)))
			    return VALUES_1(EQ(node,
				    get_lookup_slot_value_given_default(value,
				    Qparent_frame,Nil)) ? T : Nil);
			else
			    return VALUES_1(Nil);
		    }
		}
		else
		    return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(T);
}

/* NODE-HAS-AN-INTERESTING-ATTRIBUTES-P */
Object node_has_an_interesting_attributes_p(value,type)
    Object value, type;
{
    Object attributes, value_attribute, ab_loop_list_, value_value, value_type;
    Object temp;

    x_note_fn_call(136,203);
    if (Traversing_xml_object_p)
	return VALUES_1(T);
    attributes = node_attributes(value,type);
    value_attribute = Nil;
    ab_loop_list_ = attributes;
    value_value = Nil;
    value_type = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    value_attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    value_value = node_attribute_value(value,type,value_attribute);
    value_type = node_attribute_type(value,type,value_attribute);
    if ( !TRUEP(skip_node_attribute_value_p(value,type,value_attribute,
	    value_value,value_type))) {
	temp = node_attribute_name(value,type,value_attribute);
	reclaim_node_attribute_value(value,type,value_attribute,value_value);
	return VALUES_1(temp);
    }
    reclaim_node_attribute_value(value,type,value_attribute,value_value);
    goto next_loop;
  end_loop:
    reclaim_node_attributes(value,type,attributes);
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_restrictions_names, Qkb_restrictions_names);

/* GET-KB-RESTRICTIONS-NAMES */
Object get_kb_restrictions_names()
{
    Object temp;

    x_note_fn_call(136,204);
    temp = Kb_restrictions_names;
    if (temp);
    else
	temp = allocate_evaluation_sequence(eval_list_2(Qkb_configuration,
		Qkb_restrictions));
    return VALUES_1(temp);
}

static Object Qnames;              /* names */

static Object Qattribute_initializations;  /* attribute-initializations */

static Object list_constant_10;    /* # */

static Object Qrelationships;      /* relationships */

static Object Qparent_of_subworkspace;  /* parent-of-subworkspace */

static Object Qposition_in_workspace;  /* position-in-workspace */

static Object Qsize_in_workspace;  /* size-in-workspace */

static Object Qminimum_size_in_workspace;  /* minimum-size-in-workspace */

static Object Qicon_heading;       /* icon-heading */

static Object Qicon_reflection;    /* icon-reflection */

static Object Qicon_color;         /* icon-color */

static Object Qblack;              /* black */

static Object Qforeground;         /* foreground */

static Object Qitem_color_pattern;  /* item-color-pattern */

static Object Qforeground_color;   /* foreground-color */

static Object Qbackground_color;   /* background-color */

static Object Qmanually_disabled_qm;  /* manually-disabled? */

static Object Qdo_not_strip_text_mark;  /* do-not-strip-text-mark */

static Object Qstrip_text_mark;    /* strip-text-mark */

static Object Qevaluation_attributes;  /* evaluation-attributes */

static Object Qmay_refer_to_inactive_items;  /* may-refer-to-inactive-items */

static Object Qmay_run_while_inactive;  /* may-run-while-inactive */

/* SKIP-NODE-ATTRIBUTE-VALUE-P */
Object skip_node_attribute_value_p(node,node_type,attribute,value,type)
    Object node, node_type, attribute, value, type;
{
    Object x2, temp_1, user_slot_p, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector, x, inner_item, evaluation_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(136,205);
    if (Traversing_xml_object_p)
	return VALUES_1(Nil);
    if (SIMPLE_VECTOR_P(value) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 =  !((SI_Long)0L != (IFIX(ISVREF(value,(SI_Long)4L)) & 
		(SI_Long)1L)) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = Exclude_secondary_attributes ? ( 
		    !TRUEP(node_has_an_interesting_attributes_p(value,
		    type)) ? T : Nil) : Qnil;
    }
    else
	temp_1 = Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else if (EQ(node_type,Qmodule)) {
	temp_1 =  !TRUEP(value) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else if (CONSP(value) && EQ(M_CDR(value),Qsequence))
	    return VALUES_1((SI_Long)0L == 
		    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(value),(SI_Long)1L))) ? 
		    T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(node_type,Qitem_or_evaluation_value)) {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (SYMBOLP(attribute))
		return VALUES_1( !TRUEP(value) ? T : Nil);
	    else if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_slot_description_g2_struct)) {
		if ( !TRUEP(assq_function(Qtype,ISVREF(attribute,
			(SI_Long)9L))) &&  !(FIXNUMP(value) || 
			INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L 
			&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L || text_string_p(value) || 
			CONSP(value) && EQ(M_CDR(value),Qtruth_value) || 
			CONSP(value) && EQ(M_CDR(value),Qsequence) && 
			(SI_Long)0L == 
			IFIX(FIXNUM_SUB1(ISVREF(M_CAR(value),(SI_Long)1L)))))
		    return VALUES_1(T);
		else {
		    user_slot_p = ISVREF(attribute,(SI_Long)8L);
		    temp_1 = EQ(user_slot_p ? value : 
			    get_slot_description_value(node,attribute),
			    ISVREF(attribute,(SI_Long)6L)) ? T : Nil;
		    if (temp_1);
		    else if ( !TRUEP(user_slot_p)) {
			temp_1 = node_attribute_name(node,node_type,attribute);
			if (EQ(temp_1,Qnames)) {
			    if (SIMPLE_VECTOR_P(node) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
				    > (SI_Long)2L &&  !EQ(ISVREF(node,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(node,(SI_Long)1L);
				gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? x2 : Qnil;
			    }
			    else
				gensymed_symbol = Nil;
			    if (gensymed_symbol) {
				gensymed_symbol_1 = 
					lookup_global_or_kb_specific_property_value(Qsystem_frame,
					Class_description_gkbprop);
				if (gensymed_symbol_1) {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(gensymed_symbol_1,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
				    if (sub_class_vector_index < 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						{
					gensymed_symbol_2 = 
						UBYTE_8_ISAREF_1(sub_class_bit_vector,
						sub_class_vector_index);
					gensymed_symbol_3 = (SI_Long)1L;
					gensymed_symbol_4 = 
						superior_class_bit_number 
						& (SI_Long)7L;
					gensymed_symbol_3 = 
						gensymed_symbol_3 << 
						gensymed_symbol_4;
					gensymed_symbol_2 = 
						gensymed_symbol_2 & 
						gensymed_symbol_3;
					temp = (SI_Long)0L < gensymed_symbol_2;
				    }
				    else
					temp = TRUEP(Nil);
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				if (SIMPLE_VECTOR_P(node) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
					> (SI_Long)2L &&  !EQ(ISVREF(node,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(node,(SI_Long)1L);
				    gensymed_symbol = SIMPLE_VECTOR_P(x2) 
					    && EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? x2 : Qnil;
				}
				else
				    gensymed_symbol = Nil;
				if (gensymed_symbol) {
				    gensymed_symbol_1 = 
					    lookup_global_or_kb_specific_property_value(Qkb_restrictions,
					    Class_description_gkbprop);
				    if (gensymed_symbol_1) {
					sub_class_bit_vector = 
						ISVREF(gensymed_symbol,
						(SI_Long)19L);
					superior_class_bit_number = 
						IFIX(ISVREF(gensymed_symbol_1,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
					if (sub_class_vector_index < 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						    {
					    gensymed_symbol_2 = 
						    UBYTE_8_ISAREF_1(sub_class_bit_vector,
						    sub_class_vector_index);
					    gensymed_symbol_3 = (SI_Long)1L;
					    gensymed_symbol_4 = 
						    superior_class_bit_number 
						    & (SI_Long)7L;
					    gensymed_symbol_3 = 
						    gensymed_symbol_3 << 
						    gensymed_symbol_4;
					    gensymed_symbol_2 = 
						    gensymed_symbol_2 & 
						    gensymed_symbol_3;
					    temp = (SI_Long)0L < 
						    gensymed_symbol_2;
					}
					else
					    temp = TRUEP(Nil);
				    }
				    else
					temp = TRUEP(Nil);
				}
				else
				    temp = TRUEP(Nil);
				temp_1 = evaluation_value_eql(2,value,temp 
					? get_kb_restrictions_names() : 
					ISVREF(ISVREF(node,(SI_Long)1L),
					(SI_Long)1L));
			    }
			    else
				temp_1 = Nil;
			}
			else if (EQ(temp_1,Qattribute_initializations))
			    temp_1 = CONSP(value) && EQ(M_CDR(value),
				    Qsequence) ? ((SI_Long)0L == 
				    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(value),
				    (SI_Long)1L))) ? T : Nil) : Qnil;
			else
			    temp_1 = Qnil;
		    }
		    else
			temp_1 = Nil;
		    if (temp_1)
			return VALUES_1(temp_1);
		    else if (EQ(value,Qnone) &&  !TRUEP(user_slot_p))
			return memq_function(node_attribute_name(node,
				node_type,attribute),list_constant_10);
		    else
			return VALUES_1(Nil);
		}
	    }
	    else if (SIMPLE_VECTOR_P(attribute) && EQ(ISVREF(attribute,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_virtual_attribute_g2_struct)) 
			{
		temp_1 = ISVREF(attribute,(SI_Long)1L);
		if (EQ(temp_1,Qrelationships))
		    return VALUES_1((SI_Long)0L == 
			    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(value),
			    (SI_Long)1L))) ? T : Nil);
		else if (EQ(temp_1,Qparent_of_subworkspace))
		    return VALUES_1( !TRUEP(ISVREF(node,(SI_Long)18L)) ? T 
			    : Nil);
		else if (EQ(temp_1,Qposition_in_workspace)) {
		    if (ISVREF(node,(SI_Long)14L)) {
			gensymed_symbol = ACCESS_ONCE(ISVREF(node,
				(SI_Long)14L));
			gensymed_symbol = gensymed_symbol ? 
				ACCESS_ONCE(ISVREF(gensymed_symbol,
				(SI_Long)5L)) : Nil;
			x = gensymed_symbol;
			if (SIMPLE_VECTOR_P(x) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
				(SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
				Qavailable_frame_vector)) {
			    x2 = ISVREF(x,(SI_Long)1L);
			    gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				    EQ(ISVREF(x2,(SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? x2 : Qnil;
			}
			else
			    gensymed_symbol = Nil;
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Kb_workspace_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol_2 = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_3 = (SI_Long)1L;
				gensymed_symbol_4 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_3 = gensymed_symbol_3 << 
					gensymed_symbol_4;
				gensymed_symbol_2 = gensymed_symbol_2 & 
					gensymed_symbol_3;
				temp = (SI_Long)0L < gensymed_symbol_2;
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    return VALUES_1( !temp ? T : Nil);
		}
		else if (EQ(temp_1,Qsize_in_workspace)) {
		    temp_1 =  !TRUEP(value) ? T : Nil;
		    if (temp_1)
			return VALUES_1(temp_1);
		    else {
			if (ISVREF(node,(SI_Long)14L)) {
			    gensymed_symbol = ACCESS_ONCE(ISVREF(node,
				    (SI_Long)14L));
			    gensymed_symbol = gensymed_symbol ? 
				    ACCESS_ONCE(ISVREF(gensymed_symbol,
				    (SI_Long)5L)) : Nil;
			    x = gensymed_symbol;
			    if (SIMPLE_VECTOR_P(x) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
				    (SI_Long)2L &&  !EQ(ISVREF(x,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(x,(SI_Long)1L);
				gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? x2 : Qnil;
			    }
			    else
				gensymed_symbol = Nil;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Kb_workspace_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_2 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_3 = (SI_Long)1L;
				    gensymed_symbol_4 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    << gensymed_symbol_4;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    & gensymed_symbol_3;
				    temp = (SI_Long)0L < gensymed_symbol_2;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			return VALUES_1( !temp ? T : Nil);
		    }
		}
		else if (EQ(temp_1,Qminimum_size_in_workspace)) {
		    temp_1 =  !TRUEP(value) ? T : Nil;
		    if (temp_1);
		    else {
			if (ISVREF(node,(SI_Long)14L)) {
			    gensymed_symbol = ACCESS_ONCE(ISVREF(node,
				    (SI_Long)14L));
			    gensymed_symbol = gensymed_symbol ? 
				    ACCESS_ONCE(ISVREF(gensymed_symbol,
				    (SI_Long)5L)) : Nil;
			    x = gensymed_symbol;
			    if (SIMPLE_VECTOR_P(x) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
				    (SI_Long)2L &&  !EQ(ISVREF(x,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(x,(SI_Long)1L);
				gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? x2 : Qnil;
			    }
			    else
				gensymed_symbol = Nil;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Kb_workspace_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_2 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_3 = (SI_Long)1L;
				    gensymed_symbol_4 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    << gensymed_symbol_4;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    & gensymed_symbol_3;
				    temp = (SI_Long)0L < gensymed_symbol_2;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			temp_1 =  !temp ? T : Nil;
		    }
		    if (temp_1)
			return VALUES_1(temp_1);
		    else {
			sub_class_bit_vector = ISVREF(ISVREF(node,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Type_in_box_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_2 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_3 = (SI_Long)1L;
			    gensymed_symbol_4 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_3 = gensymed_symbol_3 << 
				    gensymed_symbol_4;
			    gensymed_symbol_2 = gensymed_symbol_2 & 
				    gensymed_symbol_3;
			    temp = (SI_Long)0L < gensymed_symbol_2;
			}
			else
			    temp = TRUEP(Nil);
			inner_item = temp ? get_type_in_text_box(node) : node;
			if (EQ(FIX((SI_Long)0L),
				get_lookup_slot_value(inner_item,
				Qminimum_width_of_text_box)))
			    return VALUES_1(EQ(FIX((SI_Long)0L),
				    get_lookup_slot_value(inner_item,
				    Qminimum_height_of_text_box)) ? T : Nil);
			else
			    return VALUES_1(Nil);
		    }
		}
		else if (EQ(temp_1,Qicon_heading))
		    return VALUES_1(EQ(value,FIX((SI_Long)0L)) ? T : Nil);
		else if (EQ(temp_1,Qicon_reflection))
		    return VALUES_1( !TRUEP(value) ? T : Nil);
		else if (EQ(temp_1,Qicon_color)) {
		    temp_1 = EQ(value,Qblack) ? T : Nil;
		    if (temp_1)
			return VALUES_1(temp_1);
		    else
			return VALUES_1(EQ(value,Qforeground) ? T : Nil);
		}
		else if (EQ(temp_1,Qitem_color_pattern)) {
		    sub_class_bit_vector = ISVREF(ISVREF(node,(SI_Long)1L),
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Type_in_box_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp_1 = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
		    }
		    else
			temp_1 = Nil;
		    if (temp_1);
		    else {
			sub_class_bit_vector = ISVREF(ISVREF(node,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Loose_end_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_2 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_3 = (SI_Long)1L;
			    gensymed_symbol_4 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_3 = gensymed_symbol_3 << 
				    gensymed_symbol_4;
			    gensymed_symbol_2 = gensymed_symbol_2 & 
				    gensymed_symbol_3;
			    temp_1 = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
			}
			else
			    temp_1 = Nil;
		    }
		    if (temp_1)
			return VALUES_1(temp_1);
		    else
			return VALUES_1((SI_Long)0L == 
				IFIX(FIXNUM_SUB1(ISVREF(M_CAR(value),
				(SI_Long)1L))) >>  -  - (SI_Long)1L ? T : Nil);
		}
		else if (EQ(temp_1,Qforeground_color) || EQ(temp_1,
			Qbackground_color))
		    return VALUES_1(EQ(value,Qnone) ? T : Nil);
		else if (EQ(temp_1,Qmanually_disabled_qm) || EQ(temp_1,
			Qconnection_is_directed) || EQ(temp_1,
			Qdo_not_strip_text_mark) || EQ(temp_1,
			Qstrip_text_mark))
		    return VALUES_1( !(CONSP(value) && EQ(M_CDR(value),
			    Qtruth_value) && EQ(M_CAR(value),Truth)) ? T : 
			    Nil);
		else if (EQ(temp_1,Qevaluation_attributes)) {
		    temp_1 =  !(CONSP(value) && EQ(M_CDR(value),
			    Qab_structure)) ? T : Nil;
		    if (temp_1)
			return VALUES_1(temp_1);
		    else {
			evaluation_value = estructure_slot(value,
				Qmay_refer_to_inactive_items,Nil);
			if ( !(CONSP(evaluation_value) && 
				EQ(M_CDR(evaluation_value),Qtruth_value) ? 
				EQ(M_CAR(estructure_slot(value,
				Qmay_refer_to_inactive_items,Nil)),Truth) :
				 TRUEP(Nil))) {
			    evaluation_value = estructure_slot(value,
				    Qmay_run_while_inactive,Nil);
			    return VALUES_1( !(CONSP(evaluation_value) && 
				    EQ(M_CDR(evaluation_value),
				    Qtruth_value) ? 
				    EQ(M_CAR(estructure_slot(value,
				    Qmay_run_while_inactive,Nil)),Truth) : 
				    TRUEP(Nil)) ? T : Nil);
			}
			else
			    return VALUES_1(Nil);
		    }
		}
		else
		    return VALUES_1( !TRUEP(value) ? T : Nil);
	    }
	    else
		return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-XML-SYSTEM-TABLES */
Object get_xml_system_tables(node)
    Object node;
{
    Object frame, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, x2;
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, frames;
    Object order, name, table, ab_loop_list__1, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(136,206);
    frame = Nil;
    ab_loop_list_ = get_system_table_suite_for_module_or_nil(node);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(frame) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(frame,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qserver_parameters,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_3 = (SI_Long)1L;
		gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		temp = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp ? TRUEP(node_has_an_interesting_attributes_p(frame,
	    Qitem_or_evaluation_value)) : TRUEP(Nil)) {
	ab_loopvar__2 = eval_cons_1(frame,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    frames = ab_loopvar_;
    goto end_1;
    frames = Qnil;
  end_1:;
    order = gensym_cons_1(Qmodule_information,Order_of_system_tables_in_menu);
    name = Nil;
    ab_loop_list_ = order;
    frame = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    table = Nil;
    ab_loop_list__1 = frames;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    table = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (SIMPLE_VECTOR_P(table) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(table)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(table,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(table,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(name,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_3 = (SI_Long)1L;
		gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		temp = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	frames = delete_eval_element_1(table,frames);
	frame = table;
	goto end_2;
    }
    goto next_loop_2;
  end_loop_2:
    frame = Qnil;
  end_2:;
    if (frame) {
	ab_loopvar__2 = eval_cons_1(frame,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_1;
  end_loop_1:
    temp_1 = ab_loopvar_;
    goto end_3;
    temp_1 = Qnil;
  end_3:;
    reclaim_gensym_cons_1(order);
    return allocate_evaluation_sequence(nconc2(temp_1,frames));
}

static Object Qworkspace;          /* workspace */

static Object Qx_in_workspace;     /* x-in-workspace */

static Object Qy_in_workspace;     /* y-in-workspace */

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

/* GET-XML-PANE-INFORMATION */
Object get_xml_pane_information()
{
    Object description, workspace_pf, x, y, xmag, ymag, ab_loop_list_;
    Object workspace, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp, gensymed_symbol, x_1, y_1, xa, ya, temp_2;
    Object item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char new_description_p, temp_1;

    x_note_fn_call(136,207);
    new_description_p =  !BOUNDP(Qcurrent_kb_save);
    description = new_description_p ? 
	    get_pane_description_for_saving_if_any(Nil,
	    Current_module_being_saved) : ISVREF(Current_kb_save,(SI_Long)12L);
    workspace_pf = Nil;
    x = Nil;
    y = Nil;
    xmag = Nil;
    ymag = Nil;
    ab_loop_list_ = BOUNDP(Qcurrent_kb_save) ? ISVREF(Current_kb_save,
	    (SI_Long)12L) : get_pane_description_for_saving_if_any(Nil,
	    Current_module_being_saved);
    workspace = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    workspace_pf = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    x = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    y = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    xmag = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    ymag = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    workspace = ISVREF(workspace_pf,(SI_Long)1L);
    gensymed_symbol = ISVREF(workspace,(SI_Long)3L);
    temp_1 = SIMPLE_VECTOR_P(workspace) ? EQ(ISVREF(workspace,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp_1);
    else
	temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp_1);
    else {
	x_1 = gensymed_symbol;
	y_1 = ISVREF(workspace_pf,(SI_Long)2L);
	if (FIXNUMP(y_1))
	    temp_1 = FIXNUMP(x_1) ? FIXNUM_LT(y_1,x_1) : TRUEP(T);
	else if (FIXNUMP(x_1))
	    temp_1 = TRUEP(Nil);
	else {
	    xa = M_CAR(y_1);
	    ya = M_CAR(x_1);
	    temp_1 = FIXNUM_LT(xa,ya);
	    if (temp_1);
	    else
		temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y_1),
			M_CDR(x_1)) : TRUEP(Qnil);
	}
    }
    if ( !temp_1 ? (SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)4L)) & 
	    (SI_Long)1L) : TRUEP(Nil)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qworkspace;
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)1L)) = Qworkspace;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = workspace;
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
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = workspace;
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
	    SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qx_in_workspace;
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)3L)) = Qx_in_workspace;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = x;
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
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = x;
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
	    SVREF(temp_2,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qy_in_workspace;
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)5L)) = Qy_in_workspace;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = y;
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
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = y;
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
	    SVREF(temp_2,FIX((SI_Long)6L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qx_magnification;
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)7L)) = Qx_magnification;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = xmag;
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
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = xmag;
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
	    SVREF(temp_2,FIX((SI_Long)8L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qy_magnification;
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)9L)) = Qy_magnification;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ymag;
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
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ymag;
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
	    SVREF(temp_2,FIX((SI_Long)10L)) = svref_new_value;
	}
	ab_loopvar__2 = eval_cons_1(eval_cons_1(gensymed_symbol,
		Qab_structure),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    if (new_description_p)
	reclaim_slot_value(description);
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return allocate_evaluation_sequence(temp);
}

/* ITEM-REFERENCE< */
Object item_reference_lt(item_reference1,item_reference2)
    Object item_reference1, item_reference2;
{
    Object held_vector1, vector_1, uuid_block1, held_vector2, uuid_block2;
    Object temp;

    x_note_fn_call(136,208);
    held_vector1 = M_CAR(item_reference1);
    vector_1 = held_vector1;
    if ( !TRUEP(ISVREF(vector_1,(SI_Long)1L))) {
	if (ISVREF(vector_1,(SI_Long)3L))
	    get_block_and_offset_for_item_reference(vector_1);
    }
    uuid_block1 = ISVREF(vector_1,(SI_Long)1L);
    held_vector2 = M_CAR(item_reference2);
    vector_1 = held_vector2;
    if ( !TRUEP(ISVREF(vector_1,(SI_Long)1L))) {
	if (ISVREF(vector_1,(SI_Long)3L))
	    get_block_and_offset_for_item_reference(vector_1);
    }
    uuid_block2 = ISVREF(vector_1,(SI_Long)1L);
    temp = EQ(uuid_block1,uuid_block2) ? (FIXNUM_LT(ISVREF(held_vector1,
	    (SI_Long)2L),ISVREF(held_vector2,(SI_Long)2L)) ? T : Nil) : 
	    uuid_lt(ISVREF(uuid_block1,(SI_Long)2L),ISVREF(uuid_block2,
	    (SI_Long)2L));
    return VALUES_1(temp);
}

/* ITEM-UUID< */
Object item_uuid_lt(item1,item2)
    Object item1, item2;
{
    x_note_fn_call(136,209);
    return item_reference_lt(ISVREF(item1,(SI_Long)2L),ISVREF(item2,
	    (SI_Long)2L));
}

static Object Qitem_uuid_lt;       /* item-uuid< */

/* SORT-ITEMS-IN-DEFINITION-ORDER */
Object sort_items_in_definition_order(block_list)
    Object block_list;
{
    x_note_fn_call(136,210);
    return sort_list(block_list,SYMBOL_FUNCTION(Qitem_uuid_lt),
	    SYMBOL_FUNCTION(Qidentity));
}

/* SUBITEMS-IN-DEFINITION-ORDER-FOR-CLEAR-TEXT */
Object subitems_in_definition_order_for_clear_text(workspace)
    Object workspace;
{
    x_note_fn_call(136,211);
    return sort_items_in_definition_order(subitems_in_drawing_order_for_clear_text(workspace));
}

static Object Qtable_item;         /* table-item */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object list_constant_11;    /* # */

/* SUBITEMS-IN-DRAWING-ORDER-FOR-CLEAR-TEXT */
Object subitems_in_drawing_order_for_clear_text(workspace)
    Object workspace;
{
    Object result_1, gensymed_symbol, ab_queue_form_, ab_next_queue_element_;
    Object block, block_or_connection_frame, sub_class_bit_vector, temp_1;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object connection_frame_1, ab_less_than_branch_qm_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(136,212);
    result_1 = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    block_or_connection_frame = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    block_or_connection_frame = block;
    temp =  !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1L));
    if (temp);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qtable_item,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Graph_grid_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = get_type_of_slot_if_any(2,block,
		    Qbox_translation_and_text);
	    temp = TRUEP(memq_function(CADR(temp_1),list_constant_11));
	}
	else
	    temp = TRUEP(Nil);
    }
    if ( !temp) {
	result_1 = eval_cons_1(block_or_connection_frame,result_1);
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	ab_skip_list_form_ = gensymed_symbol;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	connection = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  connection_frame_1 = Nil;
	  block_or_connection_frame = Nil;
	  gensymed_symbol = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol)) {
	      temp_1 = M_CAR(gensymed_symbol);
	      temp = SIMPLE_VECTOR_P(temp_1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      temp_1 = M_CDR(gensymed_symbol);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	  }
	  else
	      ab_skip_list_p_ = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L));
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = CDR(ab_skip_list_form_);
	next_loop_1:
	next_loop_2:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_3:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_1;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_3;
		end_loop_1:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		  ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)3L),
		  block))
	      goto end_1;
	  goto next_loop_2;
	end_loop_2:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_3;
	  connection = ab_connection_;
	  connection_frame_1 =  !SYMBOLP(connection) ? 
		  get_or_make_connection_frame_and_activate_if_appropriate(connection) 
		  : Nil;
	  block_or_connection_frame = connection_frame_1;
	  if (connection_frame_1 &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)64L)))
	      result_1 = eval_cons_1(block_or_connection_frame,result_1);
	  goto next_loop_1;
	end_loop_3:;
	POP_SPECIAL();
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* NEXT-LOWER-ITEM-IN-DRAWING-ORDER-FOR-CLEAR-TEXT */
Object next_lower_item_in_drawing_order_for_clear_text(item)
    Object item;
{
    Object ws_qm, last_1, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, block, block_or_connection_frame;
    Object sub_class_bit_vector, temp_1, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection, connection_frame_1;
    Object ab_less_than_branch_qm_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,213);
    ws_qm = get_workspace_if_any_for_block(item);
    last_1 = Nil;
    if (ws_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(ws_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	block = Nil;
	block_or_connection_frame = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	block_or_connection_frame = block;
	temp =  !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
		(SI_Long)1L));
	if (temp);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qtable_item,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Graph_grid_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = get_type_of_slot_if_any(2,block,
			Qbox_translation_and_text);
		temp = TRUEP(memq_function(CADR(temp_1),list_constant_11));
	    }
	    else
		temp = TRUEP(Nil);
	}
	if ( !temp) {
	    if (serve_item_p(block_or_connection_frame)) {
		if (EQ(item,last_1)) {
		    result = VALUES_1(block_or_connection_frame);
		    goto end_next_lower_item_in_drawing_order_for_clear_text;
		}
		last_1 = block_or_connection_frame;
	    }
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    ab_skip_list_form_ = gensymed_symbol;
	    ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    ab_connection_ = Nil;
	    ab_connection_item_ = Nil;
	    connection = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      connection_frame_1 = Nil;
	      block_or_connection_frame = Nil;
	      gensymed_symbol = CDR(ab_skip_list_form_);
	      if (CONSP(gensymed_symbol)) {
		  temp_1 = M_CAR(gensymed_symbol);
		  temp = SIMPLE_VECTOR_P(temp_1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  temp_1 = M_CDR(gensymed_symbol);
		  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	      }
	      else
		  ab_skip_list_p_ = Nil;
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = CDR(ab_skip_list_form_);
	    next_loop_1:
	    next_loop_2:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_skip_list_p_) {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			      (SI_Long)0L),(SI_Long)0L));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_connection_item_ = ISVREF(ab_current_node_,
			      (SI_Long)3L);
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_3:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_1;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_3;
		    end_loop_1:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_connection_ = M_CAR(ab_entry_cons_);
		      ab_connection_item_ = M_CDR(ab_entry_cons_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		      ab_connection_ && EQ(ISVREF(ab_connection_,
		      (SI_Long)3L),block))
		  goto end_1;
	      goto next_loop_2;
	    end_loop_2:
	    end_1:
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_3;
	      connection = ab_connection_;
	      connection_frame_1 =  !SYMBOLP(connection) ? 
		      get_or_make_connection_frame_and_activate_if_appropriate(connection) 
		      : Nil;
	      block_or_connection_frame = connection_frame_1;
	      if (connection_frame_1 &&  !((SI_Long)0L != 
		      (IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)64L))) {
		  if (serve_item_p(block_or_connection_frame)) {
		      if (EQ(item,last_1)) {
			  result = VALUES_1(block_or_connection_frame);
			  POP_SPECIAL();
			  goto end_next_lower_item_in_drawing_order_for_clear_text;
		      }
		      last_1 = block_or_connection_frame;
		  }
	      }
	      goto next_loop_1;
	    end_loop_3:;
	    POP_SPECIAL();
	}
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    else
	result = VALUES_1(Nil);
  end_next_lower_item_in_drawing_order_for_clear_text:
    return result;
}

/* INITIAL-PARENT-OF-SUBWORKSPACE */
Object initial_parent_of_subworkspace(class_1)
    Object class_1;
{
    x_note_fn_call(136,214);
    return VALUES_1(Nil);
}

/* GET-PARENT-OF-SUBWORKSPACE */
Object get_parent_of_subworkspace(block)
    Object block;
{
    Object temp;

    x_note_fn_call(136,215);
    temp = ISVREF(block,(SI_Long)18L);
    return VALUES_1(temp);
}

/* SET-PARENT-OF-SUBWORKSPACE */
Object set_parent_of_subworkspace(block,new_value)
    Object block, new_value;
{
    Object disable_stack_error, permit_transfer_of_permanent_items_p, temp;
    Declare_special(2);

    x_note_fn_call(136,216);
    if (new_value) {
	disable_stack_error = T;
	permit_transfer_of_permanent_items_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Permit_transfer_of_permanent_items_p,Qpermit_transfer_of_permanent_items_p,permit_transfer_of_permanent_items_p,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Disable_stack_error,Qdisable_stack_error,disable_stack_error,
		  0);
	    temp = make_subworkspace_action_internal(block,new_value,Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* INITIAL-UNUSED-AREA-COLOR */
Object initial_unused_area_color(class_1)
    Object class_1;
{
    x_note_fn_call(136,217);
    return VALUES_1(Nil);
}

static Object Qunused_area_color_qm;  /* unused-area-color? */

static Object Qdefault;            /* default */

/* GET-UNUSED-AREA-COLOR */
Object get_unused_area_color(workspace)
    Object workspace;
{
    Object temp;

    x_note_fn_call(136,218);
    temp = get_lookup_slot_value_given_default(workspace,
	    Qunused_area_color_qm,Nil);
    if (temp);
    else
	temp = Qdefault;
    return VALUES_1(temp);
}

static Object Qbackground;         /* background */

static Object Qtransparent;        /* transparent */

static Object Qcolor_value_vector_index_and_intensity;  /* color-value-vector-index-and-intensity */

static Object Qsame_as_workspace;  /* same-as-workspace */

static Object string_constant_123;  /* "Unused-area-color must be a color name, DEFAULT, or SAME-AS-WORKSPACE, not ~NF." */

/* SET-UNUSED-AREA-COLOR */
Object set_unused_area_color(workspace,value)
    Object workspace, value;
{
    Object temp;

    x_note_fn_call(136,219);
    if (EQ(value,Qdefault))
	value = Nil;
    if ( !(EQ(value,Qforeground) || EQ(value,Qbackground) || EQ(value,
	    Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(value),
	    Qcolor_value_vector_index_and_intensity) || rgb_color_p(value) 
	    ||  !TRUEP(value) || EQ(value,Qsame_as_workspace)))
	temp = tformat_text_string(2,string_constant_123,value);
    else {
	temp = value;
	if (EQ(temp,get_lookup_slot_value_given_default(workspace,
		Qunused_area_color_qm,Nil)))
	    temp = Nil;
	else {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(workspace,Qunused_area_color_qm);
	    set_lookup_slot_value_1(workspace,Qunused_area_color_qm,value);
	    synchronize_unused_area_color(workspace);
	    invalidate_workspace(workspace);
	    temp = Nil;
	}
    }
    return VALUES_1(temp);
}

/* INITIAL-EDGES-OF-WORKSPACE */
Object initial_edges_of_workspace(class_1)
    Object class_1;
{
    x_note_fn_call(136,220);
    return VALUES_1(Nil);
}

static Object Qleft;               /* left */

static Object Qtop;                /* top */

static Object Qright;              /* right */

static Object Qbottom;             /* bottom */

/* GET-EDGES-OF-WORKSPACE */
Object get_edges_of_workspace(block)
    Object block;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    SI_Long gensymed_symbol_3, car_new_value;

    x_note_fn_call(136,221);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)8L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qleft;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    M_CAR(gensymed_symbol_1) = gensymed_symbol_2;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qtop;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
    car_new_value =  - gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qright;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    M_CAR(gensymed_symbol_1) = gensymed_symbol_2;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qbottom;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
    car_new_value =  - gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    temp = allocate_evaluation_structure(gensymed_symbol);
    return VALUES_1(temp);
}

/* SET-EDGES-OF-WORKSPACE */
Object set_edges_of_workspace(workspace,new_value)
    Object workspace, new_value;
{
    Object left, top, right, bottom, margin, updated_left, updated_top;
    Object updated_right, updated_bottom, temp;
    Object result;

    x_note_fn_call(136,222);
    left = estructure_slot(new_value,Qleft,Nil);
    top = FIXNUM_NEGATE(estructure_slot(new_value,Qtop,Nil));
    right = estructure_slot(new_value,Qright,Nil);
    bottom = FIXNUM_NEGATE(estructure_slot(new_value,Qbottom,Nil));
    margin = ISVREF(workspace,(SI_Long)17L);
    if (FIXNUM_GT(FIXNUM_MINUS(right,left),FIXNUM_ADD(margin,margin)) && 
	    FIXNUM_GT(FIXNUM_MINUS(bottom,top),FIXNUM_ADD(margin,margin))) {
	result = get_updated_edges_from_elements_and_background(workspace,
		left,top,right,bottom,margin);
	MVS_4(result,updated_left,updated_top,updated_right,updated_bottom);
	new_change_workspace_edges(workspace,updated_left,updated_top,
		updated_right,updated_bottom);
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* INITIAL-POSITION-IN-WORKSPACE */
Object initial_position_in_workspace(class_1)
    Object class_1;
{
    x_note_fn_call(136,223);
    return VALUES_1(Nil);
}

static Object Qx;                  /* x */

static Object Qy;                  /* y */

static Object Qsuperior;           /* superior */

/* GET-POSITION-IN-WORKSPACE */
Object get_position_in_workspace(block)
    Object block;
{
    Object sub_class_bit_vector, gensymed_symbol_3, gensymed_symbol_4;
    Object car_new_value, gensymed_symbol_5, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(136,224);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if ( !temp ? TRUEP(get_workspace_if_any(block)) : TRUEP(Nil)) {
	gensymed_symbol_3 = make_eval_list_1(FIX((SI_Long)6L));
	gensymed_symbol_4 = gensymed_symbol_3;
	M_CAR(gensymed_symbol_4) = Qx;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	car_new_value = item_x_position(block);
	M_CAR(gensymed_symbol_4) = car_new_value;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	M_CAR(gensymed_symbol_4) = Qy;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	car_new_value = item_y_position(block);
	M_CAR(gensymed_symbol_4) = car_new_value;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	M_CAR(gensymed_symbol_4) = Qsuperior;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	gensymed_symbol_5 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol_5 = gensymed_symbol_5 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_5,(SI_Long)5L)) : Nil;
	M_CAR(gensymed_symbol_4) = gensymed_symbol_5;
	temp_1 = allocate_evaluation_structure(gensymed_symbol_3);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* SET-POSITION-IN-WORKSPACE */
Object set_position_in_workspace(item,new_value)
    Object item, new_value;
{
    Object workspace_qm, x_in_workspace_qm, y_in_workspace_qm;
    Object disable_stack_error, permit_transfer_of_permanent_items_p, temp;
    Declare_special(2);

    x_note_fn_call(136,225);
    if (new_value) {
	workspace_qm = estructure_slot(new_value,Qsuperior,Nil);
	x_in_workspace_qm = estructure_slot(new_value,Qx,Nil);
	y_in_workspace_qm = estructure_slot(new_value,Qy,Nil);
	disable_stack_error = T;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_stack_error,Qdisable_stack_error,disable_stack_error,
		1);
	  permit_transfer_of_permanent_items_p = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Permit_transfer_of_permanent_items_p,Qpermit_transfer_of_permanent_items_p,permit_transfer_of_permanent_items_p,
		  0);
	    temp = transfer_action_internal(item,workspace_qm,
		    x_in_workspace_qm,y_in_workspace_qm,Nil,Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-WORKSPACE-IF-ANY-FOR-BLOCK */
Object get_workspace_if_any_for_block(block)
    Object block;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(136,226);
    if (SIMPLE_VECTOR_P(block) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(block,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    return get_workspace_if_any(temp ? ISVREF(ISVREF(block,(SI_Long)21L),
	    (SI_Long)2L) : block);
}

/* INITIAL-FOLLOWING-ITEM-IN-WORKSPACE-LAYERING */
Object initial_following_item_in_workspace_layering(class_1)
    Object class_1;
{
    x_note_fn_call(136,227);
    return VALUES_1(Nil);
}

/* GET-FOLLOWING-ITEM-IN-WORKSPACE-LAYERING */
Object get_following_item_in_workspace_layering(block)
    Object block;
{
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(136,228);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    temp_1 = ( !temp ? TRUEP(get_workspace_if_any_for_block(block)) : 
	    TRUEP(Nil)) ? 
	    next_lower_item_in_drawing_order_for_clear_text(block) : Nil;
    return VALUES_1(temp_1);
}

static Object Qlayering_information_for_clear_text;  /* layering-information-for-clear-text */

static Object string_constant_124;  /* "Can not set following-item-in-workspace-layering for ~NF" */

/* SET-FOLLOWING-ITEM-IN-WORKSPACE-LAYERING */
Object set_following_item_in_workspace_layering(block,above_qm)
    Object block, above_qm;
{
    Object workspace_qm, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object layering_information_for_clear_text_new_value, temp;

    x_note_fn_call(136,229);
    if (above_qm) {
	workspace_qm = get_workspace_if_any_for_block(block);
	if (Initializing_clear_text_p && above_qm && workspace_qm && 
		EQ(get_workspace_if_any_for_block(above_qm),workspace_qm)) {
	    gensym_push_modify_macro_arg = gensym_cons_1(block,above_qm);
	    car_1 = gensym_push_modify_macro_arg;
	    cdr_1 = get_lookup_slot_value_given_default(workspace_qm,
		    Qlayering_information_for_clear_text,Nil);
	    layering_information_for_clear_text_new_value = 
		    gensym_cons_1(car_1,cdr_1);
	    set_non_savable_lookup_slot_value(workspace_qm,
		    Qlayering_information_for_clear_text,
		    layering_information_for_clear_text_new_value);
	    temp = Nil;
	}
	else
	    temp = tformat_text_string(2,string_constant_124,block);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* INITIAL-SIZE-IN-WORKSPACE */
Object initial_size_in_workspace(class_1)
    Object class_1;
{
    x_note_fn_call(136,230);
    return VALUES_1(Nil);
}

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

/* GET-SIZE-IN-WORKSPACE */
Object get_size_in_workspace(block)
    Object block;
{
    Object gensymed_symbol, width, height, x2, sub_class_bit_vector, width_qm;
    Object height_qm, temp_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3;
    char temp;
    Object result;

    x_note_fn_call(136,231);
    if (get_workspace_if_any(block)) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	width = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	height = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	if ((SI_Long)0L < IFIX(width) && (SI_Long)0L < IFIX(height)) {
	    if (SIMPLE_VECTOR_P(block) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(block,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(block,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (SIMPLE_VECTOR_P(block) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > 
			(SI_Long)2L &&  !EQ(ISVREF(block,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(block,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Type_in_box_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		result = transformed_edges_of_entity(block,T);
		MVS_2(result,width_qm,height_qm);
		if (width_qm && height_qm) {
		    width = width_qm;
		    height = height_qm;
		}
	    }
	    temp_1 = allocate_evaluation_structure(eval_list_4(Qwidth,
		    width,Qheight,height));
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object string_constant_125;  /* "The width, ~D, must be positive" */

static Object string_constant_126;  /* "The height, ~D, must be positive" */

/* SET-SIZE-IN-WORKSPACE */
Object set_size_in_workspace(item,new_value)
    Object item, new_value;
{
    Object workspace_qm, sub_class_bit_vector, inner_item, width, fixnum_width;
    Object height, fixnum_height, temp_1, gensymed_symbol_3, left_edge;
    Object top_edge, right_edge, bottom_edge, width_for_change_size_qm;
    Object height_for_change_size_qm, force_change_to_minimum_size_p;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(3);

    x_note_fn_call(136,232);
    if (new_value) {
	workspace_qm = get_workspace_if_any(item);
	if (workspace_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Type_in_box_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	    inner_item = temp ? get_type_in_text_box(item) : item;
	    width = estructure_slot(new_value,Qwidth,Nil);
	    fixnum_width = INLINE_DOUBLE_FLOAT_VECTOR_P(width) != 
		    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(width)) 
		    == (SI_Long)1L ? 
		    l_round(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(width,
		    (SI_Long)0L)),_) : width;
	    height = estructure_slot(new_value,Qheight,Nil);
	    fixnum_height = INLINE_DOUBLE_FLOAT_VECTOR_P(height) != 
		    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(height)) 
		    == (SI_Long)1L ? 
		    l_round(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(height,
		    (SI_Long)0L)),_) : height;
	    if (IFIX(fixnum_width) <= (SI_Long)0L)
		temp_1 = tformat_text_string(2,string_constant_125,width);
	    else if (IFIX(fixnum_height) <= (SI_Long)0L)
		temp_1 = tformat_text_string(2,string_constant_126,height);
	    else {
		gensymed_symbol_3 = ISVREF(item,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		left_edge = gensymed_symbol_3;
		gensymed_symbol_3 = ISVREF(item,(SI_Long)14L);
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		top_edge = gensymed_symbol_3;
		right_edge = FIXNUM_ADD(left_edge,fixnum_width);
		bottom_edge = FIXNUM_ADD(top_edge,fixnum_height);
		width_for_change_size_qm = width;
		PUSH_SPECIAL_WITH_SYMBOL(Width_for_change_size_qm,Qwidth_for_change_size_qm,width_for_change_size_qm,
			2);
		  height_for_change_size_qm = height;
		  PUSH_SPECIAL_WITH_SYMBOL(Height_for_change_size_qm,Qheight_for_change_size_qm,height_for_change_size_qm,
			  1);
		    force_change_to_minimum_size_p = T;
		    PUSH_SPECIAL_WITH_SYMBOL(Force_change_to_minimum_size_p,Qforce_change_to_minimum_size_p,force_change_to_minimum_size_p,
			    0);
		      change_size_per_bounding_rectangle(5,inner_item,
			      left_edge,top_edge,right_edge,bottom_edge);
		      if ( !EQ(inner_item,item))
			  change_edges_of_block(item,left_edge,top_edge,
				  right_edge,bottom_edge);
		      temp_1 = Nil;
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* INITIAL-MINIMUM-SIZE-IN-WORKSPACE */
Object initial_minimum_size_in_workspace(class_1)
    Object class_1;
{
    x_note_fn_call(136,233);
    return VALUES_1(Nil);
}

/* GET-MINIMUM-SIZE-IN-WORKSPACE */
Object get_minimum_size_in_workspace(block)
    Object block;
{
    Object sub_class_bit_vector, inner_item, width, height, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(136,234);
    if (get_workspace_if_any(block)) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Type_in_box_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
	inner_item = temp ? get_type_in_text_box(block) : block;
	width = get_lookup_slot_value(inner_item,Qminimum_width_of_text_box);
	height = get_lookup_slot_value(inner_item,Qminimum_height_of_text_box);
	temp_1 = allocate_evaluation_structure(eval_list_4(Qwidth,
		IFIX(width) <= (SI_Long)0L ? Qnone : width,Qheight,
		IFIX(height) <= (SI_Long)0L ? Qnone : height));
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* SET-MINIMUM-SIZE-IN-WORKSPACE */
Object set_minimum_size_in_workspace(item,new_value)
    Object item, new_value;
{
    Object workspace_qm, sub_class_bit_vector, inner_item, width, height;
    Object temp_1, gensymed_symbol_3, temp_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(136,235);
    if (new_value) {
	workspace_qm = get_workspace_if_any(item);
	if (workspace_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Type_in_box_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	    inner_item = temp ? get_type_in_text_box(item) : item;
	    width = estructure_slot(new_value,Qwidth,Nil);
	    height = estructure_slot(new_value,Qheight,Nil);
	    if (FIXNUMP(width) && IFIX(width) <= (SI_Long)0L)
		temp_1 = tformat_text_string(2,string_constant_125,width);
	    else if (FIXNUMP(height) && IFIX(height) <= (SI_Long)0L)
		temp_1 = tformat_text_string(2,string_constant_126,height);
	    else {
		update_images_of_block(inner_item,T,T);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(inner_item,
			    Qminimum_width_of_text_box);
		set_lookup_slot_value_1(inner_item,
			Qminimum_width_of_text_box,EQ(width,Qnone) ? 
			FIX((SI_Long)0L) : width);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(inner_item,
			    Qminimum_height_of_text_box);
		set_lookup_slot_value_1(inner_item,
			Qminimum_height_of_text_box,EQ(height,Qnone) ? 
			FIX((SI_Long)0L) : height);
		reformat_text_box_in_place(1,inner_item);
		update_images_of_block(inner_item,Nil,T);
		if ( !EQ(inner_item,item)) {
		    gensymed_symbol_3 = ISVREF(inner_item,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    temp_1 = gensymed_symbol_3;
		    gensymed_symbol_3 = ISVREF(inner_item,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    temp_2 = gensymed_symbol_3;
		    gensymed_symbol_3 = ISVREF(inner_item,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    temp_3 = gensymed_symbol_3;
		    gensymed_symbol_3 = ISVREF(inner_item,(SI_Long)14L);
		    gensymed_symbol_3 = gensymed_symbol_3 ? 
			    ISVREF(gensymed_symbol_3,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    change_edges_of_block(item,temp_1,temp_2,temp_3,
			    gensymed_symbol_3);
		}
		temp_1 = Nil;
	    }
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* INITIAL-CONNECTION-INPUT */
Object initial_connection_input(class_1)
    Object class_1;
{
    x_note_fn_call(136,236);
    return VALUES_1(Nil);
}

static Object Qinput;              /* input */

/* GET-CONNECTION-INPUT */
Object get_connection_input(connection)
    Object connection;
{
    Object temp;

    x_note_fn_call(136,237);
    temp = get_connection_end_evaluation_structure(connection,Qinput);
    return VALUES_1(temp);
}

/* INITIAL-CONNECTION-OUTPUT */
Object initial_connection_output(class_1)
    Object class_1;
{
    x_note_fn_call(136,238);
    return VALUES_1(Nil);
}

static Object Qoutput;             /* output */

/* GET-CONNECTION-OUTPUT */
Object get_connection_output(connection)
    Object connection;
{
    Object temp;

    x_note_fn_call(136,239);
    temp = get_connection_end_evaluation_structure(connection,Qoutput);
    return VALUES_1(temp);
}

static Object Qside;               /* side */

static Object array_constant_13;   /* # */

static Object Qport_name;          /* port-name */

/* GET-CONNECTION-END-EVALUATION-STRUCTURE */
Object get_connection_end_evaluation_structure(connection,direction)
    Object connection, direction;
{
    Object connection_structure, block, position_1, gensymed_symbol;
    Object gensymed_symbol_1, car_new_value, port_name;
    SI_Long car_new_value_1;

    x_note_fn_call(136,240);
    connection_structure = ISVREF(connection,(SI_Long)21L);
    block = EQ(direction,Qinput) ? ISVREF(connection_structure,
	    (SI_Long)3L) : ISVREF(connection_structure,(SI_Long)2L);
    if (block) {
	position_1 = EQ(direction,Qinput) ? ISVREF(connection_structure,
		(SI_Long)5L) : ISVREF(connection_structure,(SI_Long)4L);
	gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qitem;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = block;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qside;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = ISVREF(array_constant_13,IFIX(position_1) & 
		(SI_Long)3L);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qposition;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value_1 = IFIX(position_1) >>  -  - (SI_Long)2L;
	M_CAR(gensymed_symbol_1) = FIX(car_new_value_1);
	port_name = get_port_name_given_block_and_connection(2,block,
		connection_structure);
	return allocate_evaluation_structure(nconc2(gensymed_symbol,
		port_name ? eval_list_2(Qport_name,port_name) : Nil));
    }
    else
	return VALUES_1(Nil);
}

/* INITIAL-CONNECTION-STYLE */
Object initial_connection_style(class_1)
    Object class_1;
{
    x_note_fn_call(136,241);
    return VALUES_1(Nil);
}

/* GET-CONNECTION-STYLE */
Object get_connection_style(connection)
    Object connection;
{
    Object temp;

    x_note_fn_call(136,242);
    temp = get_style_of_connection(ISVREF(connection,(SI_Long)21L));
    return VALUES_1(temp);
}

/* INITIAL-CONNECTION-VERTICES */
Object initial_connection_vertices(class_1)
    Object class_1;
{
    x_note_fn_call(136,243);
    return VALUES_1(Nil);
}

/* GET-CONNECTION-VERTICES */
Object get_connection_vertices(connection)
    Object connection;
{
    Object temp;

    x_note_fn_call(136,244);
    temp = 
	    allocate_evaluation_sequence(get_connection_vertices_accurately(connection,
	    Nil));
    return VALUES_1(temp);
}

Object Maximum_scale_for_workspaces_as_float = UNBOUND;

Object Minimum_scale_for_workspaces_as_float = UNBOUND;

static Object string_constant_127;  /* "The value for ~a, ~d, is outside the valid range ~d to ~d." */

/* CHECK-FOR-WINDOW-COORDINATE-PROBLEM */
Object check_for_window_coordinate_problem(coordinate,name)
    Object coordinate, name;
{
    Object temp;

    x_note_fn_call(136,245);
    temp =  !(FIXNUM_LE(Most_negative_window_coordinate,coordinate) && 
	    FIXNUM_LE(coordinate,Most_positive_window_coordinate)) ? 
	    tformat_text_string(5,string_constant_127,name,coordinate,
	    Most_negative_window_coordinate,
	    Most_positive_window_coordinate) : Nil;
    return VALUES_1(temp);
}

static Object string_constant_128;  /* "Illegal value for ~a: ~nv" */

static Object string_constant_129;  /* "The value for ~a, ~F, is outside the valid range ~f to ~f." */

/* CHECK-FOR-WORKSPACE-SCALE-PROBLEM */
Object check_for_workspace_scale_problem(scale_qm,name)
    Object scale_qm, name;
{
    Object temp;
    double arg, arg_1, arg_2;

    x_note_fn_call(136,246);
    if ( !TRUEP(scale_qm))
	temp = Nil;
    else if ( !(INLINE_DOUBLE_FLOAT_VECTOR_P(scale_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(scale_qm)) == (SI_Long)1L))
	temp = tformat_text_string(3,string_constant_128,name,scale_qm);
    else {
	arg = DOUBLE_FLOAT_TO_DOUBLE(Minimum_scale_for_workspaces_as_float);
	arg_1 = DFLOAT_ISAREF_1(scale_qm,(SI_Long)0L);
	arg_2 = DOUBLE_FLOAT_TO_DOUBLE(Maximum_scale_for_workspaces_as_float);
	if ( !(arg <= arg_1 && arg_1 <= arg_2 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) &&  
		!inline_nanp_for_comparison(arg_2)))
	    temp = tformat_text_string(5,string_constant_129,name,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(scale_qm,
		    (SI_Long)0L)),Minimum_scale_for_workspaces_as_float,
		    Maximum_scale_for_workspaces_as_float);
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

static Object string_constant_130;  /* "none" */

static Object string_constant_131;  /* "The value for x-scale/y-scale, ~NF and ~NF, must either both be specified or both left unspecified." */

/* CHECK-FOR-WORKSPACE-SCALE-PAIRING-PROBLEM */
Object check_for_workspace_scale_pairing_problem(x_scale_qm,y_scale_qm)
    Object x_scale_qm, y_scale_qm;
{
    Object temp, temp_1;

    x_note_fn_call(136,247);
    if ( !( !TRUEP(x_scale_qm) &&  !TRUEP(y_scale_qm) || x_scale_qm && 
	    y_scale_qm)) {
	temp = x_scale_qm;
	if (temp);
	else
	    temp = string_constant_130;
	temp_1 = y_scale_qm;
	if (temp_1);
	else
	    temp_1 = string_constant_130;
	temp_1 = tformat_text_string(3,string_constant_131,temp,temp_1);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* INITIAL-DEFAULT-WINDOW-POSITION-AND-SCALE */
Object initial_default_window_position_and_scale(class_1)
    Object class_1;
{
    x_note_fn_call(136,248);
    return VALUES_1(Nil);
}

static Object Qdetail_pane;        /* detail-pane */

static Object Qx_scale;            /* x-scale */

static Object Qy_scale;            /* y-scale */

/* GET-DEFAULT-WINDOW-POSITION-AND-SCALE */
Object get_default_window_position_and_scale(workspace)
    Object workspace;
{
    Object info_qm, temp, temp_1;

    x_note_fn_call(136,249);
    info_qm = getf(ISVREF(workspace,(SI_Long)19L),Qdetail_pane,_);
    if (info_qm) {
	temp = eval_list_4(Qx,FIRST(info_qm),Qy,SECOND(info_qm));
	if ( !(IFIX(THIRD(info_qm)) == (SI_Long)4096L && 
		IFIX(FOURTH(info_qm)) == (SI_Long)4096L)) {
	    temp_1 = unnormalized_managed_float_for_value(THIRD(info_qm));
	    temp_1 = eval_list_4(Qx_scale,temp_1,Qy_scale,
		    unnormalized_managed_float_for_value(FOURTH(info_qm)));
	}
	else
	    temp_1 = Nil;
	temp_1 = allocate_evaluation_structure(nconc2(temp,temp_1));
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qfloat_array;        /* float-array */

/* SET-DEFAULT-WINDOW-POSITION-AND-SCALE */
Object set_default_window_position_and_scale(workspace,value)
    Object workspace, value;
{
    Object x, y, x_scale_qm, y_scale_qm, problem_text_string_qm, temp;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, temp_3;

    x_note_fn_call(136,250);
    if (value) {
	x = estructure_slot(value,Qx,Nil);
	y = estructure_slot(value,Qy,Nil);
	x_scale_qm = estructure_slot(value,Qx_scale,Nil);
	y_scale_qm = estructure_slot(value,Qy_scale,Nil);
	problem_text_string_qm = check_for_window_coordinate_problem(x,Qx);
	if (problem_text_string_qm);
	else
	    problem_text_string_qm = check_for_window_coordinate_problem(y,Qy);
	if (problem_text_string_qm);
	else
	    problem_text_string_qm = 
		    check_for_workspace_scale_problem(x_scale_qm,Qx_scale);
	if (problem_text_string_qm);
	else
	    problem_text_string_qm = 
		    check_for_workspace_scale_problem(y_scale_qm,Qy_scale);
	if (problem_text_string_qm);
	else
	    problem_text_string_qm = 
		    check_for_workspace_scale_pairing_problem(x_scale_qm,
		    y_scale_qm);
	temp = problem_text_string_qm;
	if (temp);
	else {
	    temp = x_scale_qm;
	    if (temp);
	    else {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_2 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    M_CDR(amf_available_array_cons_qm) = Nil;
		    amf_result = amf_array;
		}
		else {
		    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			    FIX((SI_Long)1L));
		    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		    amf_result = generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,1.0);
		temp = new_float;
	    }
	    temp_3 = y_scale_qm;
	    if (temp_3);
	    else {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_2 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    M_CDR(amf_available_array_cons_qm) = Nil;
		    amf_result = amf_array;
		}
		else {
		    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			    FIX((SI_Long)1L));
		    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		    amf_result = generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,1.0);
		temp_3 = new_float;
	    }
	    set_remembered_window_position_and_scale(workspace,
		    Qdetail_pane,x,y,temp,temp_3);
	    temp = Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Classes_sorted_so_far, Qclasses_sorted_so_far);

DEFINE_VARIABLE_WITH_SYMBOL(Classes_remaining_to_sort, Qclasses_remaining_to_sort);

/* SORT-CLASS-NAMES */
Object sort_class_names(class_list)
    Object class_list;
{
    Object classes_sorted_so_far, classes_remaining_to_sort;
    Object class_with_no_predecessors;
    Declare_special(2);
    Object result;

    x_note_fn_call(136,251);
    classes_sorted_so_far = Nil;
    classes_remaining_to_sort = nreverse(class_list);
    PUSH_SPECIAL_WITH_SYMBOL(Classes_remaining_to_sort,Qclasses_remaining_to_sort,classes_remaining_to_sort,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Classes_sorted_so_far,Qclasses_sorted_so_far,classes_sorted_so_far,
	      0);
	class_with_no_predecessors = Nil;
      next_loop:
	if ( !TRUEP(Classes_remaining_to_sort))
	    goto end_loop;
	class_with_no_predecessors = 
		find_class_with_no_predecessors(CAR(Classes_remaining_to_sort),
		CDR(Classes_remaining_to_sort));
	Classes_sorted_so_far = eval_cons_1(class_with_no_predecessors,
		Classes_sorted_so_far);
	Classes_remaining_to_sort = 
		delete_eval_element_1(class_with_no_predecessors,
		Classes_remaining_to_sort);
	goto next_loop;
      end_loop:;
	result = VALUES_1(Classes_sorted_so_far);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* FIND-CLASS-WITH-NO-PREDECESSORS */
Object find_class_with_no_predecessors(class_1,class_list)
    Object class_1, class_list;
{
    Object class_description;

    x_note_fn_call(136,252);
    if ( !TRUEP(class_list))
	return VALUES_1(class_1);
    else {
	class_description = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	return find_class_with_no_predecessors(memq_function(CAR(class_list),
		ISVREF(class_description,(SI_Long)2L)) ? CAR(class_list) : 
		class_1,CDR(class_list));
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(All_classes_for_indirectly_referenced_class, Qall_classes_for_indirectly_referenced_class);

Object Indirectly_referenced_class_p_prop = UNBOUND;

static Object Qindirectly_referenced_class_p;  /* indirectly-referenced-class-p */

/* NOTE-INDIRECTLY-REFERENCED-CLASS */
Object note_indirectly_referenced_class(class_1)
    Object class_1;
{
    x_note_fn_call(136,253);
    mutate_global_property(class_1,T,Qindirectly_referenced_class_p);
    All_classes_for_indirectly_referenced_class = eval_cons_1(class_1,
	    All_classes_for_indirectly_referenced_class);
    return VALUES_1(class_1);
}

/* DECACHE-ALL-INDIRECTLY-REFERENCED-CLASSES */
Object decache_all_indirectly_referenced_classes()
{
    Object class_1, ab_loop_list_;

    x_note_fn_call(136,254);
    class_1 = Nil;
    ab_loop_list_ = All_classes_for_indirectly_referenced_class;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(class_1,Nil,Qindirectly_referenced_class_p);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(All_classes_for_indirectly_referenced_class);
    All_classes_for_indirectly_referenced_class = Nil;
    return VALUES_1(Qnil);
}

/* MARK-ALL-CLASSES-DEFINED-IN-MODULE */
Object mark_all_classes_defined_in_module(module)
    Object module;
{
    Object scope_conses, ab_loopvar_, subclass, ab_loopvar__1, ab_loopvar__2;
    Object ab_loopvar__3, temp, class_description_qm, block;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,255);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qblock;
    subclass = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      class_description_qm = 
	      lookup_global_or_kb_specific_property_value(subclass,
	      Class_description_gkbprop);
      if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	      (SI_Long)20L))) {
	  block = lookup_global_or_kb_specific_property_value(subclass,
		  Class_definition_gkbprop);
	  temp_1 = EQ(get_module_block_is_in(block),module);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  ab_loopvar__3 = 
		  eval_cons_1(note_indirectly_referenced_class(subclass),Nil);
	  if (ab_loopvar__2)
	      M_CDR(ab_loopvar__2) = ab_loopvar__3;
	  else
	      ab_loopvar__1 = ab_loopvar__3;
	  ab_loopvar__2 = ab_loopvar__3;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(ab_loopvar__1);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* COLLECT-UNMARKED-SUPERIORS-OF-CLASS */
Object collect_unmarked_superiors_of_class(needed_class)
    Object needed_class;
{
    Object class_1, class_description, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, class_description_qm;

    x_note_fn_call(136,256);
    class_1 = Nil;
    class_description = 
	    lookup_global_or_kb_specific_property_value(needed_class,
	    Class_description_gkbprop);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(needed_class,
	    Class_description_gkbprop);
    if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L)) ?  
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(needed_class),
	    Qindirectly_referenced_class_p)) : TRUEP(Nil)) {
	ab_loopvar__2 = 
		eval_cons_1(note_indirectly_referenced_class(needed_class),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* GET-NAMES-OF-EXTERNAL-DEFINITIONS-FOR-MODULE */
Object get_names_of_external_definitions_for_module(module)
    Object module;
{
    Object needed_class, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, class_description_qm, temp;

    x_note_fn_call(136,257);
    decache_all_indirectly_referenced_classes();
    reclaim_eval_list_1(mark_all_classes_defined_in_module(module));
    needed_class = Nil;
    ab_loop_list_ = All_classes_for_cached_class_description_node_attributes;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    needed_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(needed_class,
	    Class_description_gkbprop);
    if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L))) {
	ab_loopvar__2 = collect_unmarked_superiors_of_class(needed_class);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
    }
    goto next_loop;
  end_loop:
    decache_all_indirectly_referenced_classes();
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return sort_class_names(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(All_formats_in_module, Qall_formats_in_module);

/* NOTE-FORMAT-FOR-CURRENT-MODULE */
Object note_format_for_current_module(format_1)
    Object format_1;
{
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_;
    Object all_formats_in_module_new_value;
    char temp;

    x_note_fn_call(136,258);
    gensym_modify_macro_using_test_arg_1 = format_1;
    car_1 = gensym_modify_macro_using_test_arg_1;
    cdr_1 = All_formats_in_module;
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    all_formats_in_module_new_value = temp ? cdr_1 : gensym_cons_1(car_1,
	    cdr_1);
    All_formats_in_module = all_formats_in_module_new_value;
    return VALUES_1(format_1);
}

/* DECACHE-ALL-FORMATS-FOR-CURRENT-MODULE */
Object decache_all_formats_for_current_module()
{
    x_note_fn_call(136,259);
    reclaim_gensym_list_1(All_formats_in_module);
    All_formats_in_module = Nil;
    return VALUES_1(All_formats_in_module);
}

/* GET-FORMATS-FOR-CURRENT-MODULE */
Object get_formats_for_current_module()
{
    x_note_fn_call(136,260);
    return VALUES_1(All_formats_in_module);
}

/* GET-ATTRIBUTE-FOR-ATTRIBUTE-NAME */
Object get_attribute_for_attribute_name(item,attribute)
    Object item, attribute;
{
    Object slot_description_qm, virtual_attribute_qm, temp;
    Object result;

    x_note_fn_call(136,261);
    result = user_attribute_slot_description_or_virtual_attribute(item,
	    CONSP(attribute) ? CAR(attribute) : attribute,CONSP(attribute) 
	    ? CDR(attribute) : Nil,Qget);
    MVS_2(result,slot_description_qm,virtual_attribute_qm);
    temp = slot_description_qm;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(virtual_attribute_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Reading_initial_plist_for_clear_text_kb, Qreading_initial_plist_for_clear_text_kb);

static Object string_constant_132;  /* "Error reading ~A: no module information" */

/* READ-INITIAL-PLIST-FOR-CLEAR-TEXT-KB */
Object read_initial_plist_for_clear_text_kb()
{
    Object reading_initial_plist_for_clear_text_kb, object_and_fixups;
    Object error_or_plist;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,262);
    reading_initial_plist_for_clear_text_kb = T;
    PUSH_SPECIAL_WITH_SYMBOL(Reading_initial_plist_for_clear_text_kb,Qreading_initial_plist_for_clear_text_kb,reading_initial_plist_for_clear_text_kb,
	    0);
      result = read_top_level_xml_element(Nil,Nil);
      MVS_2(result,object_and_fixups,error_or_plist);
      reclaim_xml_object_and_fixups(object_and_fixups);
      if (text_string_p(error_or_plist)) {
	  notify_user(3,string_constant_24,
		  Name_text_string_for_kb_being_read,error_or_plist);
	  result = VALUES_1(Nil);
      }
      else if ( !TRUEP(error_or_plist)) {
	  notify_user(2,string_constant_132,
		  Name_text_string_for_kb_being_read);
	  result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(error_or_plist);
    POP_SPECIAL();
    return result;
}

/* READ-CLEAR-TEXT-MODULE */
Object read_clear_text_module(pathname_1,auto_merge_case_qm)
    Object pathname_1, auto_merge_case_qm;
{
    Object data;

    x_note_fn_call(136,263);
    data = read_top_level_xml_element(pathname_1,Nil);
    if (data) {
	if (Current_g2_rdf_module)
	    read_clear_text_module_from_xml_object(data,auto_merge_case_qm);
	reclaim_xml_object_and_fixups(data);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* READ-CLEAR-TEXT-MODULE-FROM-XML-OBJECT */
Object read_clear_text_module_from_xml_object(data,auto_merge_case_qm)
    Object data, auto_merge_case_qm;
{
    x_note_fn_call(136,264);
    update_read_xml_progress();
    check_and_report_xml_checksum_problems(data);
    build_kb_from_module_data(data,auto_merge_case_qm);
    return VALUES_1(T);
}

DEFINE_VARIABLE_WITH_SYMBOL(Read_xml_line, Qread_xml_line);

DEFINE_VARIABLE_WITH_SYMBOL(Read_kb_next_character, Qread_kb_next_character);

/* READ-NEXT-XML-CHAR */
Object read_next_xml_char()
{
    Object temp, char_1, temp_1, next_char, c, temp_2;
    SI_Long z, y, x, octet_count;

    x_note_fn_call(136,265);
    if (Read_kb_next_character) {
	temp = CODE_CHAR(Read_kb_next_character);
	Read_kb_next_character = Nil;
	char_1 = temp;
    }
    else if ( !TRUEP(Read_kb_buffer_index))
	char_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_1;
	char_1 = temp;
    }
    else
	char_1 = read_next_char_for_kb_from_refilled_buffer();
    char_1 = char_1 ? CHAR_CODE(char_1) : Nil;
    if ( !TRUEP(char_1));
    else if (IFIX(char_1) < (SI_Long)32L) {
	if (IFIX(char_1) == (SI_Long)13L) {
	    if (Read_kb_next_character) {
		temp = CODE_CHAR(Read_kb_next_character);
		Read_kb_next_character = Nil;
		char_1 = temp;
	    }
	    else if ( !TRUEP(Read_kb_buffer_index))
		char_1 = Nil;
	    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
		char_1 = temp;
	    }
	    else
		char_1 = read_next_char_for_kb_from_refilled_buffer();
	    next_char = char_1 ? CHAR_CODE(char_1) : Nil;
	    if ( !(IFIX(next_char) == (SI_Long)10L))
		Read_kb_next_character = next_char;
	    char_1 = FIX((SI_Long)8232L);
	}
	else if (IFIX(char_1) == (SI_Long)10L)
	    char_1 = FIX((SI_Long)8232L);
	else;
    }
    else if (IFIX(char_1) < (SI_Long)128L);
    else if (IFIX(char_1) < (SI_Long)256L) {
	z = IFIX(char_1);
	y = (SI_Long)0L;
	x = (SI_Long)0L;
	if (z < (SI_Long)192L)
	    octet_count = (SI_Long)1L;
	else if (z < (SI_Long)224L)
	    octet_count = (SI_Long)2L;
	else if (z < (SI_Long)240L)
	    octet_count = (SI_Long)3L;
	else if (z < (SI_Long)248L)
	    octet_count = (SI_Long)4L;
	else if (z < (SI_Long)252L)
	    octet_count = (SI_Long)5L;
	else
	    octet_count = (SI_Long)6L;
	if (octet_count > (SI_Long)3L)
	    char_1 = Nil;
	else {
	    if (octet_count > (SI_Long)1L) {
		if (Read_kb_next_character) {
		    temp = CODE_CHAR(Read_kb_next_character);
		    Read_kb_next_character = Nil;
		    char_1 = temp;
		}
		else if ( !TRUEP(Read_kb_buffer_index))
		    char_1 = Nil;
		else if (FIXNUM_LT(Read_kb_buffer_index,
			    Read_kb_buffer_length)) {
		    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		    temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		    Read_kb_buffer_index = temp_1;
		    char_1 = temp;
		}
		else
		    char_1 = read_next_char_for_kb_from_refilled_buffer();
		c = char_1 ? CHAR_CODE(char_1) : Nil;
		if ( !TRUEP(c))
		    y = (SI_Long)-1L;
		else {
		    y = IFIX(c);
		    if (octet_count > (SI_Long)2L) {
			if (Read_kb_next_character) {
			    temp = CODE_CHAR(Read_kb_next_character);
			    Read_kb_next_character = Nil;
			    char_1 = temp;
			}
			else if ( !TRUEP(Read_kb_buffer_index))
			    char_1 = Nil;
			else if (FIXNUM_LT(Read_kb_buffer_index,
				Read_kb_buffer_length)) {
			    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
			    temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
			    Read_kb_buffer_index = temp_1;
			    char_1 = temp;
			}
			else
			    char_1 = 
				    read_next_char_for_kb_from_refilled_buffer();
			c = char_1 ? CHAR_CODE(char_1) : Nil;
			if ( !TRUEP(c))
			    x = (SI_Long)-1L;
			else
			    x = IFIX(c);
		    }
		}
	    }
	    char_1 = y < (SI_Long)0L || x < (SI_Long)0L ? Nil : 
		    transform_utf_8_to_ucs_4(3,FIX(z),FIX(y),FIX(x));
	}
    }
    else
	char_1 = Nil;
    if (char_1) {
	if (IFIX(char_1) == (SI_Long)8232L) {
	    temp_1 = FIXNUM_ADD1(Read_xml_line);
	    Read_xml_line = temp_1;
	    temp = chestnut_modf_function(Read_xml_line,FIX((SI_Long)100L));
	    temp_2 = FIX((SI_Long)0L);
	    if (NUM_EQ(temp,temp_2))
		update_read_xml_progress();
	}
    }
    else
	update_read_xml_progress();
    return VALUES_1(char_1);
}

/* UPDATE-READ-XML-PROGRESS */
Object update_read_xml_progress()
{
    Object suppress_updating_of_slot_value_representations_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,266);
    if (Kb_file_progress) {
	suppress_updating_of_slot_value_representations_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm,Qsuppress_updating_of_slot_value_representations_qm,suppress_updating_of_slot_value_representations_qm,
		0);
	  result = update_file_progress_display(2,Kb_file_progress,
		  Read_xml_line);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* READ-TOP-LEVEL-XML-ELEMENT */
Object read_top_level_xml_element(pathname_qm,ignore_errors_p)
    Object pathname_qm, ignore_errors_p;
{
    Object binary_file, name, object_and_fixups, error_1, g2binary_file_name;
    Object g2binary_file_stream, g2binary_file_position;
    Object current_g2binary_file_symbol_index, g2binary_file_symbol_list;
    Object g2binary_file_symbol_index_space, read_xml_line, symbol;
    Object ab_loop_list_;
    Declare_special(7);
    Object result;

    x_note_fn_call(136,267);
    binary_file = pathname_qm ? 
	    gensym_make_pathname_with_copied_components(Nil,Nil,Nil,Nil,
	    array_constant_1,Nil,pathname_qm) : Nil;
    name = Nil;
    object_and_fixups = Nil;
    error_1 = Nil;
    if (SIMPLE_VECTOR_P(binary_file) && EQ(ISVREF(binary_file,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	g2binary_file_name = gensym_namestring(1,binary_file);
    else if (text_string_p(binary_file))
	g2binary_file_name = copy_text_string(binary_file);
    else
	g2binary_file_name = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_name,Qg2binary_file_name,g2binary_file_name,
	    6);
      g2binary_file_stream = G2binary_file_name;
      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_stream,Qg2binary_file_stream,g2binary_file_stream,
	      5);
	g2binary_file_position = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_position,Qg2binary_file_position,g2binary_file_position,
		4);
	  current_g2binary_file_symbol_index = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_g2binary_file_symbol_index,Qcurrent_g2binary_file_symbol_index,current_g2binary_file_symbol_index,
		  3);
	    g2binary_file_symbol_list = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_list,Qg2binary_file_symbol_list,g2binary_file_symbol_list,
		    2);
	      g2binary_file_symbol_index_space = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(G2binary_file_symbol_index_space,Qg2binary_file_symbol_index_space,g2binary_file_symbol_index_space,
		      1);
		read_xml_line = FIX((SI_Long)1L);
		PUSH_SPECIAL_WITH_SYMBOL(Read_xml_line,Qread_xml_line,read_xml_line,
			0);
		  result = read_xml_first_element(Nil);
		POP_SPECIAL();
		MVS_3(result,name,object_and_fixups,error_1);
		maybe_close_binary_stream();
		symbol = Nil;
		ab_loop_list_ = G2binary_file_symbol_list;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		symbol = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		mutate_global_property(symbol,Nil,Qg2binary_file_symbol_index);
		goto next_loop;
	      end_loop:;
		reclaim_gensym_list_1(G2binary_file_symbol_list);
		if (G2binary_file_symbol_index_space)
		    reclaim_index_space_1(G2binary_file_symbol_index_space);
		if (text_string_p(G2binary_file_name))
		    reclaim_text_string(G2binary_file_name);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (text_string_p(error_1)) {
	if ( !TRUEP(ignore_errors_p))
	    notify_user(3,string_constant_24,
		    Name_text_string_for_kb_being_read,error_1);
	reclaim_xml_object_and_fixups(object_and_fixups);
	return VALUES_1(Nil);
    }
    else if (error_1)
	return VALUES_2(Nil, !TRUEP(ignore_errors_p) ? error_1 : Nil);
    else
	return VALUES_1(object_and_fixups);
}

DEFINE_VARIABLE_WITH_SYMBOL(Xml_nil, Qxml_nil);

/* RECLAIM-XML-ATTRIBUTE-LIST-AND-CONTENTS */
Object reclaim_xml_attribute_list_and_contents(attribute_list,contents,
	    skip_value)
    Object attribute_list, contents, skip_value;
{
    Object name, value, ab_loop_list_, temp;

    x_note_fn_call(136,268);
    name = Nil;
    value = Nil;
    ab_loop_list_ = attribute_list;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    if ( !EQ(value,skip_value) && text_string_p(value))
	reclaim_text_string(value);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    reclaim_eval_list_1(attribute_list);
    temp =  !TRUEP(contents) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (text_string_p(contents)) {
	if ( !EQ(contents,skip_value))
	    return reclaim_text_string(contents);
	else
	    return VALUES_1(Nil);
    }
    else if (CONSP(contents)) {
	name = Nil;
	value = Nil;
	ab_loop_list_ = contents;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
      next_loop_1:
	name = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	value = CAR(temp);
	if (CONSP(name))
	    reclaim_eval_list_1(name);
	if ( !EQ(value,skip_value))
	    reclaim_xml_object_and_fixups(value);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:;
	return reclaim_eval_list_1(contents);
    }
    else
	return VALUES_1(Qnil);
}

Object Read_xml_context_string_width = UNBOUND;

static Object string_constant_133;  /* "~%[line: ~D, context: " */

static Object string_constant_134;  /* " ~S" */

static Object string_constant_135;  /* " ~A" */

static Object string_constant_136;  /* "]" */

/* TWRITE-READ-XML-CONTEXT-STRING */
Object twrite_read_xml_context_string(xml_read_context)
    Object xml_read_context;
{
    Object position_1, element, ab_loop_list_, stringp_1, string_1, size;
    Object incff_1_arg;

    x_note_fn_call(136,269);
    tformat(2,string_constant_133,Read_xml_line);
    position_1 = FIX((SI_Long)17L);
    element = Nil;
    ab_loop_list_ = xml_read_context;
    stringp_1 = Nil;
    string_1 = Nil;
    size = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    stringp_1 = text_string_p(element);
    if (stringp_1)
	string_1 = element;
    else if (element && SYMBOLP(element))
	string_1 = symbol_name_text_string(element);
    else
	string_1 = Qnil;
    size = string_1 ? lengthw(string_1) : Qnil;
    if (string_1) {
	if (FIXNUM_LT(Read_xml_context_string_width,
		FIXNUM_ADD(FIXNUM_ADD1(position_1),size))) {
	    tformat(1,string_constant_13);
	    position_1 = FIX((SI_Long)0L);
	}
	tformat(2,stringp_1 ? string_constant_134 : string_constant_135,
		string_1);
	incff_1_arg = FIXNUM_ADD1(size);
	position_1 = FIXNUM_ADD(position_1,incff_1_arg);
    }
    goto next_loop;
  end_loop:;
    return tformat(1,string_constant_136);
}

/* READ-XML-ERROR-STRING */
Object read_xml_error_string varargs_1(int, n)
{
    Object xml_read_context, format_1;
    Object arg1, arg2, arg3, arg4, arg5, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object result_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(136,270);
    INIT_ARGS_nonrelocating();
    xml_read_context = REQUIRED_ARG_nonrelocating();
    format_1 = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      tformat(6,format_1,arg1,arg2,arg3,arg4,arg5);
	      twrite_read_xml_context_string(xml_read_context);
	      result_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(result_1);
}

/* RECLAIM-TWO-EVAL-CONSES */
Object reclaim_two_eval_conses(list_1)
    Object list_1;
{
    x_note_fn_call(136,271);
    reclaim_eval_cons_1(CDR(list_1));
    reclaim_eval_cons_1(list_1);
    return VALUES_1(Nil);
}

static Object string_constant_137;  /* "End of file" */

/* READ-XML-FIRST-ELEMENT */
Object read_xml_first_element(first_char)
    Object first_char;
{
    Object ch, temp, temp_1, name, object_and_fixups, error_or_plist, valuep;
    Object result;

    x_note_fn_call(136,272);
    ch = Nil;
  next_loop:
    if (first_char) {
	temp = first_char;
	first_char = Nil;
	ch = temp;
    }
    else
	ch = read_next_xml_char();
    if ( !TRUEP(ch)) {
	temp = read_xml_error_string(2,Nil,string_constant_137);
	return VALUES_3(Nil,Nil,temp);
    }
    if (IFIX(ch) == (SI_Long)60L) {
	result = read_xml_content(Nil,Nil);
	MVS_5(result,name,temp,object_and_fixups,error_or_plist,valuep);
	if (object_and_fixups || error_or_plist || valuep)
	    return VALUES_4(name,object_and_fixups,error_or_plist,valuep);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_138;  /* "Malformed XML comment" */

static Object list_constant_12;    /* # */

static Object string_constant_139;  /* "Malformed XML CDATA" */

static Object string_constant_140;  /* "Expecting >" */

static Object string_constant_141;  /* "</~a> was seen at top level" */

static Object string_constant_142;  /* "Expecting </~a>, but found </~a>" */

/* READ-XML-CONTENT */
Object read_xml_content(name_qm,xml_read_context)
    Object name_qm, xml_read_context;
{
    Object ch, temp, ch1, ch2, ch3, c, ab_loop_list_, char_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object seen_first_char_p, chw, thing, temp_2, schar_arg_2, schar_new_value;
    Object n_1, nextn, name, next_char, error_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(136,273);
    ch = read_next_xml_char();
    if ( !TRUEP(ch)) {
	temp = read_xml_error_string(2,xml_read_context,string_constant_137);
	result = VALUES_4(Nil,Nil,Nil,temp);
	goto end_read_xml_content;
    }
    else if (IFIX(ch) == (SI_Long)63L) {
	ch1 = Nil;
	ch2 = Nil;
      next_loop:
	temp = read_next_xml_char();
	if (temp);
	else {
	    temp = read_xml_error_string(2,xml_read_context,
		    string_constant_137);
	    result = VALUES_4(Nil,Nil,Nil,temp);
	    goto end_read_xml_content;
	}
	ch2 = temp;
	if (ch1 && IFIX(ch1) == (SI_Long)63L && IFIX(ch2) == (SI_Long)62L)
	    goto end_loop;
	ch1 = ch2;
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    else if (IFIX(ch) == (SI_Long)33L) {
	ch = read_next_xml_char();
	if ((SI_Long)45L == IFIX(ch)) {
	    temp_1 = (SI_Long)45L == IFIX(read_next_xml_char());
	    if (temp_1);
	    else {
		temp = read_xml_error_string(2,xml_read_context,
			string_constant_138);
		result = VALUES_4(Nil,Nil,Nil,temp);
		goto end_read_xml_content;
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    ch1 = Nil;
	    ch2 = Nil;
	    ch3 = Nil;
	  next_loop_1:
	    temp = read_next_xml_char();
	    if (temp);
	    else {
		temp = read_xml_error_string(2,xml_read_context,
			string_constant_137);
		result = VALUES_4(Nil,Nil,Nil,temp);
		goto end_read_xml_content;
	    }
	    ch3 = temp;
	    if (ch1 && ch2 && IFIX(ch1) == (SI_Long)45L && IFIX(ch2) == 
		    (SI_Long)45L && IFIX(ch3) == (SI_Long)62L)
		goto end_loop_1;
	    ch1 = ch2;
	    ch2 = ch3;
	    goto next_loop_1;
	  end_loop_1:
	    result = VALUES_1(Qnil);
	}
	else if (IFIX(ch) == (SI_Long)91L) {
	    c = Nil;
	    ab_loop_list_ = list_constant_12;
	    char_1 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    c = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = read_next_xml_char();
	    if (temp);
	    else {
		temp = read_xml_error_string(2,xml_read_context,
			string_constant_137);
		result = VALUES_4(Nil,Nil,Nil,temp);
		goto end_read_xml_content;
	    }
	    char_1 = temp;
	    if ( !FIXNUM_EQ(c,char_1)) {
		temp_1 = TRUEP(T);
		goto end_1;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	    if (temp_1) {
		temp = read_xml_error_string(2,xml_read_context,
			string_constant_139);
		result = VALUES_4(Nil,Nil,Nil,temp);
		goto end_read_xml_content;
	    }
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
		      (SI_Long)3L));
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	      current_wide_string = wide_string_bv16;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		      3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      seen_first_char_p = Nil;
		      chw = Nil;
		      ch1 = Nil;
		      ch2 = Nil;
		      ch3 = Nil;
		    next_loop_3:
		      temp = read_next_xml_char();
		      if (temp);
		      else {
			  temp = read_xml_error_string(2,xml_read_context,
				  string_constant_137);
			  result = VALUES_4(Nil,Nil,Nil,temp);
			  POP_SPECIAL();
			  POP_SPECIAL();
			  POP_SPECIAL();
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_read_xml_content;
		      }
		      ch3 = temp;
		      if (ch1 && ch2 && IFIX(ch1) == (SI_Long)93L && 
			      IFIX(ch2) == (SI_Long)93L && IFIX(ch3) == 
			      (SI_Long)62L)
			  goto end_loop_3;
		      if (ch1) {
			  if ( !TRUEP(seen_first_char_p)) {
			      seen_first_char_p = T;
			      if (IFIX(ch1) == (SI_Long)8232L)
				  ch1 = Nil;
			  }
		      }
		      if (ch1) {
			  if (chw) {
			      if (EQ(Current_twriting_output_type,
				      Qwide_string)) {
				  thing = chw;
				  twrite_wide_character(CHARACTERP(thing) ?
					   CHAR_CODE(thing) : thing);
			      }
			      else {
				  if ( 
					  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					  Total_length_of_current_gensym_string))
				      extend_current_gensym_string(0);
				  temp_2 = Current_gensym_string;
				  schar_arg_2 = 
					  Fill_pointer_for_current_gensym_string;
				  thing = chw;
				  schar_new_value = 
					  CODE_CHAR(CHARACTERP(thing) ? 
					  CHAR_CODE(thing) : thing);
				  SET_SCHAR(temp_2,schar_arg_2,
					  schar_new_value);
				  temp_2 = 
					  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				  Fill_pointer_for_current_gensym_string = 
					  temp_2;
			      }
			  }
			  chw = ch1;
		      }
		      ch1 = ch2;
		      ch2 = ch3;
		      goto next_loop_3;
		    end_loop_3:
		      if (chw) {
			  if ( !(IFIX(chw) == (SI_Long)8232L)) {
			      if (EQ(Current_twriting_output_type,
				      Qwide_string)) {
				  thing = chw;
				  twrite_wide_character(CHARACTERP(thing) ?
					   CHAR_CODE(thing) : thing);
			      }
			      else {
				  if ( 
					  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					  Total_length_of_current_gensym_string))
				      extend_current_gensym_string(0);
				  temp_2 = Current_gensym_string;
				  schar_arg_2 = 
					  Fill_pointer_for_current_gensym_string;
				  thing = chw;
				  schar_new_value = 
					  CODE_CHAR(CHARACTERP(thing) ? 
					  CHAR_CODE(thing) : thing);
				  SET_SCHAR(temp_2,schar_arg_2,
					  schar_new_value);
				  temp_2 = 
					  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				  Fill_pointer_for_current_gensym_string = 
					  temp_2;
			      }
			  }
		      }
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    result = VALUES_3(Nil,Nil,temp);
	}
	else {
	    n_1 = FIX((SI_Long)1L);
	    ch = Nil;
	    nextn = Nil;
	  next_loop_4:
	    temp = read_next_xml_char();
	    if (temp);
	    else {
		temp = read_xml_error_string(2,xml_read_context,
			string_constant_137);
		result = VALUES_4(Nil,Nil,Nil,temp);
		goto end_read_xml_content;
	    }
	    ch = temp;
	    if (IFIX(ch) == (SI_Long)60L)
		nextn = FIXNUM_ADD1(n_1);
	    else if (IFIX(ch) == (SI_Long)62L)
		nextn = FIXNUM_SUB1(n_1);
	    else
		nextn = n_1;
	    if ((SI_Long)0L == IFIX(nextn))
		goto end_loop_4;
	    n_1 = nextn;
	    goto next_loop_4;
	  end_loop_4:
	    result = VALUES_1(Qnil);
	}
    }
    else if (IFIX(ch) == (SI_Long)47L) {
	result = read_xml_name(Nil);
	MVS_3(result,name,next_char,error_string);
	if (error_string) {
	    temp = read_xml_error_string(2,xml_read_context,error_string);
	    result = VALUES_4(Nil,Nil,Nil,temp);
	    goto end_read_xml_content;
	}
	else if ( !(IFIX(next_char) == (SI_Long)62L)) {
	    temp = read_xml_error_string(2,xml_read_context,
		    string_constant_140);
	    result = VALUES_4(Nil,Nil,Nil,temp);
	    goto end_read_xml_content;
	}
	else if ( !TRUEP(name_qm)) {
	    temp = read_xml_error_string(3,xml_read_context,
		    string_constant_141,name);
	    result = VALUES_4(Nil,Nil,Nil,temp);
	    goto end_read_xml_content;
	}
	else if ( !EQ(name,name_qm)) {
	    temp = read_xml_error_string(4,xml_read_context,
		    string_constant_142,name_qm,name);
	    result = VALUES_4(Nil,Nil,Nil,temp);
	    goto end_read_xml_content;
	}
	result = VALUES_4(Nil,Nil,Nil,T);
    }
    else
	result = read_xml_content_1(ch,xml_read_context);
  end_read_xml_content:
    return result;
}

/* READ-XML-CONTENT-1 */
Object read_xml_content_1(ch,xml_read_context)
    Object ch, xml_read_context;
{
    Object error_string, name, attribute_list, xml_read_context_1, empty_p;
    Object text_p, contents_rev, content_name, content_kind, object_and_fixups;
    Object error_or_plist, valuep;
    char temp;
    Object result;

    x_note_fn_call(136,274);
    result = read_xml_element_head(ch,xml_read_context);
    MVS_5(result,error_string,name,attribute_list,xml_read_context_1,empty_p);
    if (error_string)
	return VALUES_4(Nil,Nil,Nil,error_string);
    else {
	text_p = T;
	contents_rev = Nil;
      next_loop:
	error_string = Nil;
	if (empty_p)
	    result = VALUES_4(Nil,Nil,Nil,T);
	else {
	    ch = Nil;
	  next_loop_1:
	    ch = read_next_xml_char();
	    if (EQ(ch,Qnil))
		ch = read_xml_error_string(2,xml_read_context_1,
			string_constant_137);
	    else if (EQ(ch,FIX((SI_Long)38L)))
		ch = read_xml_reference(xml_read_context_1);
	    else if (EQ(ch,FIX((SI_Long)60L))) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    if (text_string_p(ch)) {
		error_string = ch;
		temp = TRUEP(error_string);
		goto end_1;
	    }
	    if (text_p)
		contents_rev = eval_cons_1(ch,contents_rev);
	    goto next_loop_1;
	  end_loop:
	    temp = TRUEP(Qnil);
	  end_1:;
	    if (temp)
		result = VALUES_4(Nil,Nil,Nil,error_string);
	    else
		result = read_xml_content(name,xml_read_context_1);
	}
	MVS_5(result,content_name,content_kind,object_and_fixups,
		error_or_plist,valuep);
	if (error_or_plist)
	    return read_xml_object(name,attribute_list,xml_read_context_1,
		    contents_rev,text_p,object_and_fixups,error_or_plist);
	result = read_xml_contents_2(contents_rev,text_p,content_name,
		content_kind,object_and_fixups,valuep);
	MVS_2(result,contents_rev,text_p);
	goto next_loop;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

static Object Qg2_col_Module;      /* |g2:Module| */

static Object string_constant_143;  /* "Bad module id" */

/* READ-XML-ELEMENT-HEAD */
Object read_xml_element_head(ch,xml_read_context)
    Object ch, xml_read_context;
{
    Object name, next_char, error_string, xml_read_context_1, attribute_list;
    Object empty_p, string_1, temp, identification;
    Object result;

    x_note_fn_call(136,275);
    result = read_xml_name(ch);
    MVS_3(result,name,next_char,error_string);
    if (error_string)
	return read_xml_error_string(2,xml_read_context,error_string);
    xml_read_context_1 = eval_cons_1(name,xml_read_context);
    result = read_xml_attributes(next_char,xml_read_context_1);
    MVS_2(result,attribute_list,empty_p);
    if (text_string_p(empty_p)) {
	reclaim_eval_cons_1(xml_read_context_1);
	return VALUES_1(empty_p);
    }
    else {
	if (EQ(name,Qg2_col_Module)) {
	    string_1 = getf(attribute_list,Qid,_);
	    if ( !TRUEP(text_string_p(string_1))) {
		temp = read_xml_error_string(2,xml_read_context_1,
			string_constant_143);
		reclaim_eval_cons_1(xml_read_context_1);
		return VALUES_1(temp);
	    }
	    Current_g2_rdf_module = intern_text_string_no_reclaim(1,string_1);
	}
	identification = getf(attribute_list,QRDF_COL_RESOURCE,_);
	if (identification);
	else
	    identification = getf(attribute_list,Qid,_);
	xml_read_context_1 = eval_cons_1(identification,xml_read_context_1);
	return VALUES_5(Nil,name,attribute_list,xml_read_context_1,empty_p);
    }
}

/* READ-XML-CONTENTS-1 */
Object read_xml_contents_1(contents_rev,text_p,object_and_fixups,
	    error_or_plist)
    Object contents_rev, text_p, object_and_fixups, error_or_plist;
{
    Object c, ab_loop_list_, content_name, content, temp, string_1;
    Object eval_pop_store, cons_1, next_cons, temp_1, temp_2, thing, contents;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object ch, thing_1, schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(136,276);
    if ( !EQ(error_or_plist,Qt)) {
	if (text_p) {
	    c = Nil;
	    ab_loop_list_ = contents_rev;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    c = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (text_string_p(c))
		reclaim_text_string(c);
	    goto next_loop;
	  end_loop:;
	}
	else {
	    content_name = Nil;
	    content = Nil;
	    ab_loop_list_ = contents_rev;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	  next_loop_1:
	    content_name = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    content = CAR(temp);
	    reclaim_xml_object_and_fixups(content);
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    goto next_loop_1;
	  end_loop_1:;
	}
	reclaim_eval_list_1(contents_rev);
	return VALUES_2(object_and_fixups,error_or_plist);
    }
    if ( !TRUEP(text_p)) {
	if (contents_rev) {
	    temp = nreverse(contents_rev);
	    return VALUES_3(temp,Nil,T);
	}
	else
	    return VALUES_1(Nil);
    }
    string_1 = Nil;
    if (contents_rev &&  !TRUEP(CDR(contents_rev)) && 
	    text_string_p(CAR(contents_rev))) {
	eval_pop_store = Nil;
	cons_1 = contents_rev;
	if (cons_1) {
	    eval_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = cons_1;
		temp_1 = Available_eval_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = cons_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = cons_1;
		temp_1 = Available_eval_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	contents_rev = next_cons;
	string_1 = eval_pop_store;
    }
    if (contents_rev) {
	thing = CAR(contents_rev);
	if (FIXNUMP(thing) ? IFIX(CAR(contents_rev)) == (SI_Long)8232L : 
		TRUEP(Nil)) {
	    eval_pop_store = Nil;
	    cons_1 = contents_rev;
	    if (cons_1) {
		eval_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = cons_1;
		    temp_1 = Available_eval_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = cons_1;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = cons_1;
		    temp_1 = Available_eval_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    contents_rev = next_cons;
	}
	contents = nreverse(contents_rev);
	thing = CAR(contents);
	if (FIXNUMP(thing) ? IFIX(CAR(contents)) == (SI_Long)8232L : 
		TRUEP(Nil)) {
	    eval_pop_store = Nil;
	    cons_1 = contents;
	    if (cons_1) {
		eval_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = cons_1;
		    temp_1 = Available_eval_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = cons_1;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = cons_1;
		    temp_1 = Available_eval_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    contents = next_cons;
	}
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  aref_arg_2 = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	  aref_arg_2 = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	  current_wide_string = wide_string_bv16;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		  3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  ch = Nil;
		  ab_loop_list_ = contents;
		next_loop_2:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  ch = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (FIXNUMP(ch)) {
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing_1 = ch;
			  twrite_wide_character(CHARACTERP(thing_1) ? 
				  CHAR_CODE(thing_1) : thing_1);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_1 = Current_gensym_string;
			  temp_2 = Fill_pointer_for_current_gensym_string;
			  thing_1 = ch;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ?
				   CHAR_CODE(thing_1) : thing_1);
			  SET_SCHAR(temp_1,temp_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		  }
		  else {
		      twrite_general_string(ch);
		      reclaim_text_string(ch);
		  }
		  goto next_loop_2;
		end_loop_2:;
		  string_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	reclaim_eval_list_1(contents);
    }
    return VALUES_1(string_1);
}

/* READ-XML-CONTENTS-2 */
Object read_xml_contents_2(contents_rev,text_p,content_name,content_kind,
	    object_and_fixups,valuep)
    Object contents_rev, text_p, content_name, content_kind, object_and_fixups;
    Object valuep;
{
    Object temp;

    x_note_fn_call(136,277);
    if ( !TRUEP(text_p)) {
	if (object_and_fixups || valuep) {
	    temp = read_xml_make_attribute_name(content_name,content_kind);
	    contents_rev = eval_cons_1(temp,contents_rev);
	    contents_rev = eval_cons_1(EQ(object_and_fixups,Xml_nil) ? Nil 
		    : object_and_fixups,contents_rev);
	}
    }
    else if ( !(content_name || content_kind || valuep || object_and_fixups));
    else if ( !(content_name || content_kind || valuep ||  
	    !TRUEP(text_string_p(object_and_fixups))))
	contents_rev = eval_cons_1(object_and_fixups,contents_rev);
    else {
	reclaim_eval_list_1(contents_rev);
	text_p = Nil;
	temp = EQ(object_and_fixups,Xml_nil) ? Nil : object_and_fixups;
	contents_rev = eval_list_2(temp,
		read_xml_make_attribute_name(content_name,content_kind));
    }
    return VALUES_2(contents_rev,text_p);
}

static Object list_constant_13;    /* # */

static Object string_constant_144;  /* "Malformed ~A" */

static Object Qg2_col_c_dot_MODULE_INFORMATION;  /* |g2:c.MODULE-INFORMATION| */

static Object list_constant_14;    /* # */

static Object Qkb_name;            /* kb-name */

static Object Qtop_level_module;   /* top-level-module */

static Object Qrequired_modules;   /* required-modules */

static Object Qdirectly_required_modules;  /* directly-required-modules */

static Object QG2_COL_TYPE;        /* |g2:type| */

static Object QG2_COL_UNIT;        /* |g2:unit| */

static Object QG2_COL_VALUE;       /* |g2:value| */

static Object Qg2_col_Sequence;    /* |g2:Sequence| */

static Object array_constant_14;   /* # */

static Object Qg2_col_Structure;   /* |g2:Structure| */

static Object array_constant_15;   /* # */

static Object Qg2_col_RawValue;    /* |g2:RawValue| */

static Object array_constant_16;   /* # */

static Object Qg2_col_BinaryData;  /* |g2:BinaryData| */

static Object array_constant_17;   /* # */

static Object Qg2_col_Integer;     /* |g2:Integer| */

static Object array_constant_18;   /* # */

static Object Qg2_col_Long;        /* |g2:Long| */

static Object array_constant_19;   /* # */

static Object Qg2_col_Float;       /* |g2:Float| */

static Object array_constant_20;   /* # */

static Object Qg2_col_Text;        /* |g2:Text| */

static Object array_constant_21;   /* # */

static Object Qg2_col_Symbol;      /* |g2:Symbol| */

static Object array_constant_22;   /* # */

static Object Qg2_col_TruthValue;  /* |g2:TruthValue| */

static Object array_constant_23;   /* # */

static Object Qfile;               /* file */

/* READ-XML-OBJECT */
Object read_xml_object(name,attribute_list,xml_read_context,contents_rev,
	    text_p,object_and_fixups,error_or_plist)
    Object name, attribute_list, xml_read_context, contents_rev, text_p;
    Object object_and_fixups, error_or_plist;
{
    Object contents, non_text_p, temp, pn, ab_loop_list_, value, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, seq, gensymed_symbol, held_vector, m;
    Object ab_loopvar__3, ab_loopvar__4, elt_1, validated_elt, attribute_type;
    Object attribute_unit, unit_qm, attribute_value, value_qm;
    Object type_string_from_name, error_string, symbol, kind;
    SI_Long next_index, length_1;
    Object result;

    x_note_fn_call(136,278);
    result = read_xml_contents_1(contents_rev,text_p,object_and_fixups,
	    error_or_plist);
    MVS_3(result,contents,error_or_plist,non_text_p);
    if (error_or_plist) {
	reclaim_xml_attribute_list_and_contents(attribute_list,contents,Nil);
	reclaim_two_eval_conses(xml_read_context);
	return VALUES_4(Nil,Nil,Nil,error_or_plist);
    }
    if (memq_function(name,list_constant_13) &&  !LISTP(contents)) {
	temp = read_xml_error_string(3,xml_read_context,
		string_constant_144,name);
	reclaim_two_eval_conses(xml_read_context);
	return VALUES_4(Nil,Nil,Nil,temp);
    }
    if (EQ(name,Qg2_col_c_dot_MODULE_INFORMATION) && 
	    Reading_initial_plist_for_clear_text_kb) {
	pn = Nil;
	ab_loop_list_ = list_constant_14;
	value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pn = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(pn,Qkb_name))
	    value = Current_g2_rdf_module;
	else if (EQ(pn,Qtop_level_module))
	    value = getf(contents,Qtop_level_module,_);
	else if (EQ(pn,Qrequired_modules)) {
	    seq = get_xml_object(getf(contents,Qdirectly_required_modules,_));
	    if (seq) {
		gensymed_symbol = seq;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		m = Nil;
		ab_loopvar__2 = Nil;
		ab_loopvar__3 = Nil;
		ab_loopvar__4 = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		validated_elt = elt_1 ? 
			validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
		next_index = next_index + (SI_Long)1L;
		m = validated_elt;
		ab_loopvar__4 = eval_cons_1(m,Nil);
		if (ab_loopvar__3)
		    M_CDR(ab_loopvar__3) = ab_loopvar__4;
		else
		    ab_loopvar__2 = ab_loopvar__4;
		ab_loopvar__3 = ab_loopvar__4;
		goto next_loop_1;
	      end_loop_1:
		value = ab_loopvar__2;
		goto end_1;
		value = Qnil;
	      end_1:;
	    }
	    else
		value = Nil;
	}
	else
	    value = Qnil;
	ab_loopvar__2 = value ? eval_list_2(pn,value) : Nil;
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_2;
	temp = Qnil;
      end_2:;
	reclaim_two_eval_conses(xml_read_context);
	reclaim_xml_attribute_list_and_contents(attribute_list,contents,Nil);
	return VALUES_4(Nil,Nil,Nil,temp);
    }
    attribute_type = getf(attribute_list,QG2_COL_TYPE,_);
    attribute_unit = getf(attribute_list,QG2_COL_UNIT,_);
    unit_qm = attribute_unit ? intern_text_string_no_reclaim(1,
	    attribute_unit) : Nil;
    attribute_value = getf(attribute_list,QG2_COL_VALUE,_);
    if (text_string_p(attribute_value))
	value_qm = copy_text_string(attribute_value);
    else if (text_string_p(contents))
	value_qm = copy_text_string(contents);
    else
	value_qm = Qnil;
    if (EQ(name,Qg2_col_Sequence))
	type_string_from_name = array_constant_14;
    else if (EQ(name,Qg2_col_Structure))
	type_string_from_name = array_constant_15;
    else if (EQ(name,Qg2_col_RawValue))
	type_string_from_name = array_constant_16;
    else if (EQ(name,Qg2_col_BinaryData))
	type_string_from_name = array_constant_17;
    else if (EQ(name,Qg2_col_Integer))
	type_string_from_name = array_constant_18;
    else if (EQ(name,Qg2_col_Long))
	type_string_from_name = array_constant_19;
    else if (EQ(name,Qg2_col_Float))
	type_string_from_name = array_constant_20;
    else if (EQ(name,Qg2_col_Text))
	type_string_from_name = array_constant_21;
    else if (EQ(name,Qg2_col_Symbol))
	type_string_from_name = array_constant_22;
    else if (EQ(name,Qg2_col_TruthValue))
	type_string_from_name = array_constant_23;
    else
	type_string_from_name = Qnil;
    if (type_string_from_name) {
	result = read_xml_value(type_string_from_name,value_qm,unit_qm,
		attribute_list,contents,xml_read_context);
	MVS_2(result,value,error_string);
	if (error_string) {
	    reclaim_two_eval_conses(xml_read_context);
	    return VALUES_4(Nil,Nil,Nil,error_string);
	}
	if (value) {
	    reclaim_two_eval_conses(xml_read_context);
	    return VALUES_5(Nil,Nil,value,Nil,T);
	}
    }
    result = symbol_from_rdf_symbol_name(name);
    MVS_2(result,symbol,kind);
    if (EQ(kind,Qab_class)) {
	if (text_string_p(value_qm))
	    reclaim_text_string(value_qm);
	reclaim_two_eval_conses(xml_read_context);
	temp = eval_list_2(Qab_class,symbol);
	temp = make_xml_object(4,Nil,Qitem,nconc2(temp,
		nconc2(attribute_list,contents)),T);
	return VALUES_3(Nil,Nil,temp);
    }
    else if (text_string_p(value_qm) || attribute_type ||  
	    !TRUEP(value_qm) &&  !TRUEP(contents)) {
	if (attribute_type) {
	    result = read_xml_value(attribute_type,value_qm,unit_qm,
		    attribute_list,contents,xml_read_context);
	    MVS_2(result,value,error_string);
	    reclaim_two_eval_conses(xml_read_context);
	    if (error_string)
		return VALUES_4(Nil,Nil,Nil,error_string);
	    temp = value;
	}
	else if (non_text_p) {
	    reclaim_two_eval_conses(xml_read_context);
	    if (text_string_p(value_qm))
		reclaim_text_string(value_qm);
	    reclaim_xml_attribute_list_and_contents(attribute_list,Nil,Nil);
	    temp = contents;
	}
	else {
	    reclaim_two_eval_conses(xml_read_context);
	    if (text_string_p(value_qm))
		reclaim_text_string(value_qm);
	    reclaim_xml_attribute_list_and_contents(attribute_list,Nil,Nil);
	    temp = contents;
	    if (temp);
	    else
		temp = copy_text_string(array_constant_8);
	    temp = make_xml_object(4,temp,Qtext,Nil,T);
	}
	return VALUES_5(symbol,kind,temp,Nil,T);
    }
    else if ( !(attribute_list || CAR(contents) || CDDR(contents))) {
	reclaim_two_eval_conses(xml_read_context);
	temp = CADR(contents);
	reclaim_xml_attribute_list_and_contents(attribute_list,contents,
		CADR(contents));
	return VALUES_5(symbol,kind,temp,Nil,non_text_p);
    }
    else {
	reclaim_two_eval_conses(xml_read_context);
	temp = EQ(name,Qg2_col_Module) ? Qmodule : Qfile;
	temp = make_xml_object(4,Nil,temp,nconc2(attribute_list,contents),T);
	return VALUES_3(symbol,kind,temp);
    }
}

static Object float_constant;      /* 0.0 */

static Object Knil;                /* :nil */

static Object string_constant_145;  /* "Missing g2:value attribute" */

/* READ-XML-VALUE */
Object read_xml_value(attribute_type,value_qm,unit_qm,attribute_list,
	    contents,xml_read_context)
    Object attribute_type, value_qm, unit_qm, attribute_list, contents;
    Object xml_read_context;
{
    Object value_len_qm, read_kb_buffer, read_kb_buffer_index;
    Object read_kb_buffer_length, result_1, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float, temp_3;
    Object gensymed_symbol, value, error_string;
    SI_Long length_1, type_len, temp;
    double aref_new_value;
    Declare_special(3);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(136,279);
    value_len_qm = value_qm ? lengthw(value_qm) : Nil;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute_type));
    type_len = UBYTE_16_ISAREF_1(attribute_type,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(attribute_type,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    if ( !((SI_Long)2L < type_len))
	return VALUES_1(Nil);
    temp = UBYTE_16_ISAREF_1(attribute_type,(SI_Long)0L);
    if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
	return VALUES_1(Nil);
    else
	switch ((char)temp) {
	  case 82:
	    if (string_eq_w(attribute_type,array_constant_16) && value_qm) {
		read_kb_buffer = wide_string_to_string(value_qm);
		PUSH_SPECIAL_WITH_SYMBOL(Read_kb_buffer,Qread_kb_buffer,read_kb_buffer,
			2);
		  read_kb_buffer_index = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Read_kb_buffer_index,Qread_kb_buffer_index,read_kb_buffer_index,
			  1);
		    read_kb_buffer_length = length(Read_kb_buffer);
		    PUSH_SPECIAL_WITH_SYMBOL(Read_kb_buffer_length,Qread_kb_buffer_length,read_kb_buffer_length,
			    0);
		      result_1 = read_element_for_kb(Nil);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		return VALUES_1(Nil);
	    break;
	  case 73:
	    if (string_eq_w(attribute_type,array_constant_18))
		result_1 = value_qm ? read_fixnum_from_string(3,value_qm,
			FIX((SI_Long)0L),value_len_qm) : Nil;
	    else
		return VALUES_1(Nil);
	    break;
	  case 76:
	    if (string_eq_w(attribute_type,array_constant_19))
		result_1 = value_qm ? read_long_from_string(3,value_qm,
			FIX((SI_Long)0L),value_len_qm) : Nil;
	    else
		return VALUES_1(Nil);
	    break;
	  case 70:
	    if (string_eq_w(attribute_type,array_constant_20)) {
		if (value_qm) {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_1 = Vector_of_simple_float_array_pools;
			    temp_2 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = amf_available_array_cons_qm;
				temp_1 = 
					Available_float_array_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_1 = Available_float_array_conses_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
				temp_1 = 
					Available_float_array_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
			    }
			    M_CDR(amf_available_array_cons_qm) = Nil;
			    amf_result = amf_array;
			}
			else {
			    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
				    FIX((SI_Long)1L));
			    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
				    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
			    amf_result = 
				    generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			temp_3 = lfloat(read_float_from_string(value_qm,
				FIX((SI_Long)0L),value_len_qm),float_constant);
			aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_3);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			result_1 = new_float;
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		}
		else
		    result_1 = Nil;
	    }
	    else
		return VALUES_1(Nil);
	    break;
	  case 83:
	    temp = UBYTE_16_ISAREF_1(attribute_type,(SI_Long)1L);
	    if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
		return VALUES_1(Nil);
	    else
		switch ((char)temp) {
		  case 121:
		    if (string_eq_w(attribute_type,array_constant_22)) {
			temp_3 = value_qm;
			value_qm = Nil;
			if (temp_3);
			else
			    temp_3 = copy_text_string(array_constant_8);
			result_1 = intern_text_string(1,temp_3);
			if (result_1);
			else
			    result_1 = Knil;
		    }
		    else
			return VALUES_1(Nil);
		    break;
		  case 101:
		    if (string_eq_w(attribute_type,array_constant_14)) {
			temp_3 = collect_xml_list(contents,Qsequence);
			contents = Nil;
			result_1 = temp_3;
		    }
		    else
			return VALUES_1(Nil);
		    break;
		  case 116:
		    if (string_eq_w(attribute_type,array_constant_15)) {
			temp_3 = collect_xml_list(contents,Qab_structure);
			contents = Nil;
			result_1 = temp_3;
		    }
		    else
			return VALUES_1(Nil);
		    break;
		  default:
		    return VALUES_1(Nil);
		    break;
		}
	    break;
	  case 84:
	    temp = UBYTE_16_ISAREF_1(attribute_type,(SI_Long)1L);
	    if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
		return VALUES_1(Nil);
	    else
		switch ((char)temp) {
		  case 101:
		    if (string_eq_w(attribute_type,array_constant_21)) {
			temp_3 = value_qm;
			value_qm = Nil;
			result_1 = temp_3;
			if (result_1);
			else
			    result_1 = copy_text_string(array_constant_8);
		    }
		    else
			return VALUES_1(Nil);
		    break;
		  case 114:
		    if (string_eq_w(attribute_type,array_constant_23)) {
			if (value_qm) {
			    gensymed_symbol = 
				    read_truth_value_from_string(value_qm,
				    FIX((SI_Long)0L),value_len_qm);
			    if (FIXNUM_EQ(gensymed_symbol,Truth))
				result_1 = Evaluation_true_value;
			    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
				result_1 = Evaluation_false_value;
			    else
				result_1 = eval_cons_1(gensymed_symbol,
					Qtruth_value);
			}
			else
			    result_1 = Nil;
		    }
		    else
			return VALUES_1(Nil);
		    break;
		  default:
		    return VALUES_1(Nil);
		    break;
		}
	    break;
	  case 66:
	    if (string_eq_w(attribute_type,array_constant_17)) {
		result = make_binary_xml_object(nconc2(attribute_list,
			contents),T);
		MVS_2(result,value,error_string);
		if (error_string) {
		    temp_3 = read_xml_error_string(2,xml_read_context,
			    error_string);
		    return VALUES_2(Nil,temp_3);
		}
		attribute_list = Nil;
		contents = Nil;
		result_1 = value;
	    }
	    else
		return VALUES_1(Nil);
	    break;
	  default:
	    return VALUES_1(Nil);
	    break;
	}
    if (value_qm)
	reclaim_text_string(value_qm);
    reclaim_xml_attribute_list_and_contents(attribute_list,contents,Nil);
    if ( !TRUEP(result_1)) {
	temp_3 = read_xml_error_string(2,xml_read_context,string_constant_145);
	return VALUES_2(Nil,temp_3);
    }
    if (unit_qm)
	return make_xml_object(6,result_1,Qprimitive_value,Nil,Nil,Nil,
		unit_qm);
    else
	return VALUES_1(result_1);
}

static Object string_constant_146;  /* "g2:" */

static Object string_constant_147;  /* "g2m:" */

static Object string_constant_148;  /* "c." */

static Object string_constant_149;  /* "a." */

static Object Qattribute;          /* attribute */

static Object string_constant_150;  /* "ua." */

static Object Quser_attribute;     /* user-attribute */

static Object string_constant_151;  /* "uq." */

static Object Qqualified_attribute;  /* qualified-attribute */

static Object string_constant_152;  /* "sa." */

static Object Qstructure_attribute;  /* structure-attribute */

/* SYMBOL-FROM-RDF-SYMBOL-NAME-1 */
Object symbol_from_rdf_symbol_name_1(symbol)
    Object symbol;
{
    Object p, name, index_1, length_1, dot_seen, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object ch, qmp, simple_or_wide_character, thing, temp_1, schar_arg_2;
    Object schar_new_value, temp_2, first_part, second_part;
    SI_Long temp, bv16_length, aref_new_value, length_2, incff_1_arg;
    Declare_special(5);

    x_note_fn_call(136,280);
    p = Nil;
    name = SYMBOL_NAME(symbol);
    index_1 = FIX((SI_Long)0L);
    length_1 = length(name);
    dot_seen = Nil;
    if (IFIX(length_1) < (SI_Long)3L);
    else if (string_eq(4,string_constant_146,name,Kend2,FIX((SI_Long)3L))) {
	temp = IFIX(index_1) + (SI_Long)3L;
	index_1 = FIX(temp);
    }
    else if (IFIX(length_1) < (SI_Long)4L);
    else if (string_eq(4,string_constant_147,name,Kend2,FIX((SI_Long)4L))) {
	temp = IFIX(index_1) + (SI_Long)4L;
	index_1 = FIX(temp);
    }
    if (string_eq(6,string_constant_148,name,Kstart2,index_1,Kend2,
	    FIX(IFIX(index_1) + (SI_Long)2L))) {
	p = Qab_class;
	temp = IFIX(index_1) + (SI_Long)2L;
	index_1 = FIX(temp);
    }
    else if (string_eq(6,string_constant_149,name,Kstart2,index_1,Kend2,
	    FIX(IFIX(index_1) + (SI_Long)2L))) {
	p = Qattribute;
	temp = IFIX(index_1) + (SI_Long)2L;
	index_1 = FIX(temp);
    }
    else if (string_eq(6,string_constant_150,name,Kstart2,index_1,Kend2,
	    FIX(IFIX(index_1) + (SI_Long)3L))) {
	p = Quser_attribute;
	temp = IFIX(index_1) + (SI_Long)3L;
	index_1 = FIX(temp);
    }
    else if (string_eq(6,string_constant_151,name,Kstart2,index_1,Kend2,
	    FIX(IFIX(index_1) + (SI_Long)3L))) {
	p = Qqualified_attribute;
	temp = IFIX(index_1) + (SI_Long)3L;
	index_1 = FIX(temp);
    }
    else if (string_eq(6,string_constant_152,name,Kstart2,index_1,Kend2,
	    FIX(IFIX(index_1) + (SI_Long)3L))) {
	p = Qstructure_attribute;
	temp = IFIX(index_1) + (SI_Long)3L;
	index_1 = FIX(temp);
    }
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      temp = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
      temp = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_2 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      ch = Nil;
	      qmp = Nil;
	    next_loop:
	      if ( !(FIXNUM_LT(index_1,length_1) &&  !TRUEP(dot_seen)))
		  goto end_loop;
	      ch = SCHAR(name,index_1);
	      qmp = CHAR_EQ(ch,CHR('_')) && IFIX(index_1) + (SI_Long)2L < 
		      IFIX(length_1) && CHAR_EQ(SCHAR(name,
		      FIXNUM_ADD1(index_1)),CHR('q')) ? 
		      (CHAR_EQ(CHR(ISCHAR(name,IFIX(index_1) + 
		      (SI_Long)2L)),CHR('m')) ? T : Nil) : Qnil;
	      if (EQ(p,Qqualified_attribute) && CHAR_EQ(ch,CHR('.'))) {
		  dot_seen = T;
		  index_1 = FIXNUM_ADD1(index_1);
	      }
	      else {
		  simple_or_wide_character = qmp ? CHR('\?') : ch;
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = simple_or_wide_character;
		      twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp_1 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		      temp_1 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_1;
		  }
		  incff_1_arg = qmp ? (SI_Long)3L : (SI_Long)1L;
		  temp = IFIX(index_1) + incff_1_arg;
		  index_1 = FIX(temp);
	      }
	      goto next_loop;
	    end_loop:;
	      temp_2 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    first_part = intern_text_string(1,temp_2);
    if (EQ(p,Qqualified_attribute) && dot_seen) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	  temp = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	  current_wide_string = wide_string_bv16;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		  3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  ch = Nil;
		  qmp = Nil;
		next_loop_1:
		  if ( !FIXNUM_LT(index_1,length_1))
		      goto end_loop_1;
		  ch = SCHAR(name,index_1);
		  qmp = CHAR_EQ(ch,CHR('_')) && IFIX(index_1) + 
			  (SI_Long)2L < IFIX(length_1) && 
			  CHAR_EQ(SCHAR(name,FIXNUM_ADD1(index_1)),
			  CHR('q')) ? (CHAR_EQ(CHR(ISCHAR(name,
			  IFIX(index_1) + (SI_Long)2L)),CHR('m')) ? T : 
			  Nil) : Qnil;
		  simple_or_wide_character = qmp ? CHR('\?') : ch;
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = simple_or_wide_character;
		      twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp_1 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		      temp_1 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_1;
		  }
		  incff_1_arg = qmp ? (SI_Long)3L : (SI_Long)1L;
		  temp = IFIX(index_1) + incff_1_arg;
		  index_1 = FIX(temp);
		  goto next_loop_1;
		end_loop_1:;
		  temp_2 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	second_part = intern_text_string(1,temp_2);
    }
    else
	second_part = Nil;
    return eval_cons_1(EQ(p,Qqualified_attribute) && dot_seen ? 
	    eval_cons_1(second_part,first_part) : first_part,p);
}

static Object Qsymbol_from_rdf_symbol_name;  /* symbol-from-rdf-symbol-name */

/* SYMBOL-FROM-RDF-SYMBOL-NAME */
Object symbol_from_rdf_symbol_name(symbol)
    Object symbol;
{
    Object s_plus_p, s, temp;

    x_note_fn_call(136,281);
    s_plus_p = get(symbol,Qsymbol_from_rdf_symbol_name,_);
    if (s_plus_p);
    else
	s_plus_p = mutate_global_property(symbol,
		symbol_from_rdf_symbol_name_1(symbol),
		Qsymbol_from_rdf_symbol_name);
    s = CAR(s_plus_p);
    if (CONSP(s)) {
	temp = eval_cons_1(CAR(s),CDR(s));
	return VALUES_2(temp,CDR(s_plus_p));
    }
    else
	return VALUES_2(s,CDR(s_plus_p));
}

/* READ-XML-NAME */
Object read_xml_name(first_char)
    Object first_char;
{
    Object ch, index_1, next_char, using_string_buffer_p;
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object temp, code, temp_2, temp_3, wide_character_code, code_1;
    Object extended_code, unicode, row, gensym_character_code_qm;
    Object gensym_character_code, extended_code_qm, char_1;
    Object simple_gensym_character_code, character_or_character_code;
    Object escape_character_qm, thing, schar_new_value, kanji_code, octet_1_qm;
    Object quotient, remainder_1, simple_or_wide_character, gensymed_symbol_2;
    SI_Long gensym_full_row, gensymed_symbol, gensymed_symbol_1, octet_2;
    SI_Long octet_3, thing_1, simple_or_wide_character_1;
    char temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(136,282);
    ch = Nil;
    index_1 = FIX((SI_Long)0L);
    next_char = Nil;
    using_string_buffer_p = T;
    current_gensym_string = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    4);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      3);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		2);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  1);
	    temp = first_char;
	    if (temp);
	    else
		temp = read_next_xml_char();
	    if (temp);
	    else {
		result = VALUES_3(Nil,Nil,string_constant_137);
		POP_SPECIAL();
		POP_SPECIAL();
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_read_xml_name;
	    }
	    next_char = temp;
	    if (using_string_buffer_p && FIXNUM_LT(index_1,
		    Intern_string_buffer_length)) {
		code = next_char;
		temp_1 = IFIX(code) < (SI_Long)127L ?  !((SI_Long)64L == 
			IFIX(code) || (SI_Long)126L == IFIX(code) || 
			(SI_Long)92L == IFIX(code)) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp_2 = Intern_string_buffer;
		temp_3 = CODE_CHAR(next_char);
		SET_CHAR(temp_2,index_1,temp_3);
	    }
	    else {
		if (using_string_buffer_p) {
		    using_string_buffer_p = Nil;
		    Current_gensym_string = 
			    obtain_simple_gensym_string(FIX((SI_Long)2048L));
		    twrite_intern_string_buffer_as_gensym_characters(index_1);
		}
		wide_character_code = next_char;
		code_1 = Nil;
		extended_code = Nil;
		unicode = wide_character_code;
		extended_code = Nil;
		code = unicode;
		if (IFIX(code) < (SI_Long)127L &&  !((SI_Long)64L == 
			IFIX(code) || (SI_Long)126L == IFIX(code) || 
			(SI_Long)92L == IFIX(code))) {
		    code_1 = unicode;
		    temp = code_1;
		}
		else {
		    row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
		    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		      gensym_full_row = 
			      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
			      IFIX(Row));
		      if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			  gensymed_symbol = gensym_full_row << (SI_Long)8L;
			  gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
			  gensym_character_code_qm = FIX(gensymed_symbol + 
				  gensymed_symbol_1);
		      }
		      else
			  gensym_character_code_qm = Nil;
		    POP_SPECIAL();
		    if (gensym_character_code_qm) {
			temp_1 = IFIX(gensym_character_code_qm) < 
				(SI_Long)256L ? 
				TRUEP(ISVREF(Iso_latin1_special_character_code_map,
				IFIX(gensym_character_code_qm))) : TRUEP(Nil);
			if (temp_1);
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_capital_ligature_oe))
			    temp_1 = 'W';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_small_ligature_oe))
			    temp_1 = 'w';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_bullet))
			    temp_1 = '*';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_small_letter_f_with_hook))
			    temp_1 = '&';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_trade_mark_sign))
			    temp_1 = ':';
			else
			    temp_1 = TRUEP(Qnil);
			if (temp_1);
			else
			    temp_1 = (SI_Long)8192L <= 
				    IFIX(gensym_character_code_qm) ? 
				    IFIX(gensym_character_code_qm) <= 
				    (SI_Long)8447L : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			code_1 = gensym_character_code_qm;
			temp = code_1;
		    }
		    else
			temp = Nil;
		    if (temp);
		    else {
			code_1 = 
				map_unicode_to_gensym_han_character_code(unicode);
			temp = code_1;
			if (temp);
			else {
			    row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
			    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			      gensym_full_row = 
				      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
				      IFIX(Row));
			      if ( !(gensym_full_row == 
				      IFIX(Invalid_gensym_full_row))) {
				  gensymed_symbol = gensym_full_row << 
					  (SI_Long)8L;
				  gensymed_symbol_1 = (SI_Long)255L & 
					  IFIX(unicode);
				  code_1 = FIX(gensymed_symbol + 
					  gensymed_symbol_1);
			      }
			      else
				  code_1 = Nil;
			    POP_SPECIAL();
			    temp = code_1;
			    if (temp);
			    else {
				gensymed_symbol = (SI_Long)63488L;
				gensymed_symbol_1 = (SI_Long)255L & 
					IFIX(unicode);
				extended_code = FIX(gensymed_symbol + 
					gensymed_symbol_1);
				code_1 = FIX((SI_Long)63232L + 
					(IFIX(unicode) >>  -  - (SI_Long)8L));
				temp = code_1;
			    }
			}
		    }
		}
		result = VALUES_2(temp,extended_code);
		MVS_2(result,gensym_character_code,extended_code_qm);
		char_1 = Nil;
		if (FIXNUM_EQ(gensym_character_code,Gensym_code_for_linebreak))
		    result = VALUES_2(Gensym_char_or_code_for_linebreak,
			    Gensym_esc_for_linebreak_qm);
		else if (FIXNUM_EQ(gensym_character_code,
			Gensym_code_for_paragraph_break))
		    result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
			    Gensym_esc_for_paragraph_break_qm);
		else {
		    if ((SI_Long)32L <= IFIX(gensym_character_code) && 
			    IFIX(gensym_character_code) <= (SI_Long)126L) {
			simple_gensym_character_code = gensym_character_code;
			temp_1 =  !(FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)64L)) || 
				FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)126L)) || 
				FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)92L)));
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			temp = CODE_CHAR(gensym_character_code);
			result = VALUES_2(temp,Nil);
		    }
		    else {
			temp = IFIX(gensym_character_code) < (SI_Long)256L 
				? 
				ISVREF(Iso_latin1_special_character_code_map,
				IFIX(gensym_character_code)) : Nil;
			if (temp);
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_capital_ligature_oe))
			    temp = CHR('W');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_small_ligature_oe))
			    temp = CHR('w');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_bullet))
			    temp = CHR('*');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_small_letter_f_with_hook))
			    temp = CHR('&');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_trade_mark_sign))
			    temp = CHR(':');
			else
			    temp = Qnil;
			char_1 = temp;
			if (char_1)
			    result = VALUES_2(char_1,CHR('~'));
			else
			    result = VALUES_2(gensym_character_code,CHR('\\'));
		    }
		}
		MVS_2(result,character_or_character_code,escape_character_qm);
		if ( !TRUEP(escape_character_qm)) {
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_or_character_code;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing = character_or_character_code;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
		    kanji_code = character_or_character_code;
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = (SI_Long)92L;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing_1 = (SI_Long)92L;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		    code = kanji_code;
		    result = chestnut_floorf_function(FIX(IFIX(code) & 
			    (SI_Long)8191L),FIX((SI_Long)95L));
		    MVS_2(result,quotient,remainder_1);
		    octet_2 = IFIX(quotient) + (SI_Long)40L;
		    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		    octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L == 
			    (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
			    (SI_Long)13L) + (SI_Long)32L) : Nil;
		    if (octet_1_qm) {
			simple_or_wide_character = octet_1_qm;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = simple_or_wide_character;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = simple_or_wide_character;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    simple_or_wide_character_1 = octet_2;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = simple_or_wide_character_1;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing_1 = simple_or_wide_character_1;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		    simple_or_wide_character_1 = octet_3;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = simple_or_wide_character_1;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing_1 = simple_or_wide_character_1;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		else {
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = escape_character_qm;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing = escape_character_qm;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_or_character_code;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing = character_or_character_code;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		if (extended_code_qm) {
		    char_1 = Nil;
		    if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_linebreak))
			result = VALUES_2(Gensym_char_or_code_for_linebreak,
				Gensym_esc_for_linebreak_qm);
		    else if (FIXNUM_EQ(extended_code_qm,
			    Gensym_code_for_paragraph_break))
			result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
				Gensym_esc_for_paragraph_break_qm);
		    else {
			if ((SI_Long)32L <= IFIX(extended_code_qm) && 
				IFIX(extended_code_qm) <= (SI_Long)126L) {
			    simple_gensym_character_code = extended_code_qm;
			    temp_1 =  
				    !(FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)64L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)126L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)92L)));
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    temp = CODE_CHAR(extended_code_qm);
			    result = VALUES_2(temp,Nil);
			}
			else {
			    temp = IFIX(extended_code_qm) < (SI_Long)256L ?
				     
				    ISVREF(Iso_latin1_special_character_code_map,
				    IFIX(extended_code_qm)) : Nil;
			    if (temp);
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_capital_ligature_oe))
				temp = CHR('W');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_small_ligature_oe))
				temp = CHR('w');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_bullet))
				temp = CHR('*');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_small_letter_f_with_hook))
				temp = CHR('&');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_trade_mark_sign))
				temp = CHR(':');
			    else
				temp = Qnil;
			    char_1 = temp;
			    if (char_1)
				result = VALUES_2(char_1,CHR('~'));
			    else
				result = VALUES_2(extended_code_qm,CHR('\\'));
			}
		    }
		    MVS_2(result,character_or_character_code,
			    escape_character_qm);
		    if ( !TRUEP(escape_character_qm)) {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
			kanji_code = character_or_character_code;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = (SI_Long)92L;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = (SI_Long)92L;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			code = kanji_code;
			result = chestnut_floorf_function(FIX(IFIX(code) & 
				(SI_Long)8191L),FIX((SI_Long)95L));
			MVS_2(result,quotient,remainder_1);
			octet_2 = IFIX(quotient) + (SI_Long)40L;
			octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L 
				== (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
				(SI_Long)13L) + (SI_Long)32L) : Nil;
			if (octet_1_qm) {
			    simple_or_wide_character = octet_1_qm;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = simple_or_wide_character;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = simple_or_wide_character;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
			simple_or_wide_character_1 = octet_2;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			simple_or_wide_character_1 = octet_3;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    else {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = escape_character_qm;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = escape_character_qm;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		}
	    }
	    index_1 = FIXNUM_ADD1(index_1);
	  next_loop:
	    ch = read_next_xml_char();
	    if ( !TRUEP(ch)) {
		result = VALUES_3(Nil,Nil,string_constant_137);
		POP_SPECIAL();
		POP_SPECIAL();
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_read_xml_name;
	    }
	    gensymed_symbol_2 = ch;
	    temp_1 = (SI_Long)97L <= IFIX(gensymed_symbol_2) ? 
		    IFIX(gensymed_symbol_2) <= (SI_Long)122L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = (SI_Long)65L <= IFIX(gensymed_symbol_2) ? 
			IFIX(gensymed_symbol_2) <= (SI_Long)90L : TRUEP(Qnil);
	    if (temp_1);
	    else {
		gensymed_symbol = IFIX(ch);
		temp_1 = (SI_Long)48L <= gensymed_symbol && 
			gensymed_symbol <= (SI_Long)57L ? 
			TRUEP(FIX(gensymed_symbol - (SI_Long)48L)) : 
			TRUEP(Nil);
	    }
	    if (temp_1);
	    else
		temp_1 = IFIX(ch) == (SI_Long)46L;
	    if (temp_1);
	    else
		temp_1 = IFIX(ch) == (SI_Long)45L;
	    if (temp_1);
	    else
		temp_1 = IFIX(ch) == (SI_Long)95L;
	    if (temp_1);
	    else
		temp_1 = IFIX(ch) == (SI_Long)58L;
	    if ( !temp_1)
		goto end_loop;
	    next_char = ch;
	    if (using_string_buffer_p && FIXNUM_LT(index_1,
		    Intern_string_buffer_length)) {
		code = next_char;
		temp_1 = IFIX(code) < (SI_Long)127L ?  !((SI_Long)64L == 
			IFIX(code) || (SI_Long)126L == IFIX(code) || 
			(SI_Long)92L == IFIX(code)) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp_2 = Intern_string_buffer;
		temp_3 = CODE_CHAR(next_char);
		SET_CHAR(temp_2,index_1,temp_3);
	    }
	    else {
		if (using_string_buffer_p) {
		    using_string_buffer_p = Nil;
		    Current_gensym_string = 
			    obtain_simple_gensym_string(FIX((SI_Long)2048L));
		    twrite_intern_string_buffer_as_gensym_characters(index_1);
		}
		wide_character_code = next_char;
		code_1 = Nil;
		extended_code = Nil;
		unicode = wide_character_code;
		extended_code = Nil;
		code = unicode;
		if (IFIX(code) < (SI_Long)127L &&  !((SI_Long)64L == 
			IFIX(code) || (SI_Long)126L == IFIX(code) || 
			(SI_Long)92L == IFIX(code))) {
		    code_1 = unicode;
		    temp = code_1;
		}
		else {
		    row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
		    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		      gensym_full_row = 
			      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
			      IFIX(Row));
		      if ( !(gensym_full_row == 
				  IFIX(Invalid_gensym_full_row))) {
			  gensymed_symbol = gensym_full_row << (SI_Long)8L;
			  gensymed_symbol_1 = (SI_Long)255L & IFIX(unicode);
			  gensym_character_code_qm = FIX(gensymed_symbol + 
				  gensymed_symbol_1);
		      }
		      else
			  gensym_character_code_qm = Nil;
		    POP_SPECIAL();
		    if (gensym_character_code_qm) {
			temp_1 = IFIX(gensym_character_code_qm) < 
				(SI_Long)256L ? 
				TRUEP(ISVREF(Iso_latin1_special_character_code_map,
				IFIX(gensym_character_code_qm))) : TRUEP(Nil);
			if (temp_1);
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_capital_ligature_oe))
			    temp_1 = 'W';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_small_ligature_oe))
			    temp_1 = 'w';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_bullet))
			    temp_1 = '*';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_small_letter_f_with_hook))
			    temp_1 = '&';
			else if (FIXNUM_EQ(gensym_character_code_qm,
				Gensym_code_for_trade_mark_sign))
			    temp_1 = ':';
			else
			    temp_1 = TRUEP(Qnil);
			if (temp_1);
			else
			    temp_1 = (SI_Long)8192L <= 
				    IFIX(gensym_character_code_qm) ? 
				    IFIX(gensym_character_code_qm) <= 
				    (SI_Long)8447L : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			code_1 = gensym_character_code_qm;
			temp = code_1;
		    }
		    else
			temp = Nil;
		    if (temp);
		    else {
			code_1 = 
				map_unicode_to_gensym_han_character_code(unicode);
			temp = code_1;
			if (temp);
			else {
			    row = FIX(IFIX(unicode) >>  -  - (SI_Long)8L);
			    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
			      gensym_full_row = 
				      UBYTE_8_ISAREF_1(Unicode_to_gensym_full_row_map,
				      IFIX(Row));
			      if ( !(gensym_full_row == 
				      IFIX(Invalid_gensym_full_row))) {
				  gensymed_symbol = gensym_full_row << 
					  (SI_Long)8L;
				  gensymed_symbol_1 = (SI_Long)255L & 
					  IFIX(unicode);
				  code_1 = FIX(gensymed_symbol + 
					  gensymed_symbol_1);
			      }
			      else
				  code_1 = Nil;
			    POP_SPECIAL();
			    temp = code_1;
			    if (temp);
			    else {
				gensymed_symbol = (SI_Long)63488L;
				gensymed_symbol_1 = (SI_Long)255L & 
					IFIX(unicode);
				extended_code = FIX(gensymed_symbol + 
					gensymed_symbol_1);
				code_1 = FIX((SI_Long)63232L + 
					(IFIX(unicode) >>  -  - (SI_Long)8L));
				temp = code_1;
			    }
			}
		    }
		}
		result = VALUES_2(temp,extended_code);
		MVS_2(result,gensym_character_code,extended_code_qm);
		char_1 = Nil;
		if (FIXNUM_EQ(gensym_character_code,Gensym_code_for_linebreak))
		    result = VALUES_2(Gensym_char_or_code_for_linebreak,
			    Gensym_esc_for_linebreak_qm);
		else if (FIXNUM_EQ(gensym_character_code,
			Gensym_code_for_paragraph_break))
		    result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
			    Gensym_esc_for_paragraph_break_qm);
		else {
		    if ((SI_Long)32L <= IFIX(gensym_character_code) && 
			    IFIX(gensym_character_code) <= (SI_Long)126L) {
			simple_gensym_character_code = gensym_character_code;
			temp_1 =  !(FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)64L)) || 
				FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)126L)) || 
				FIXNUM_EQ(simple_gensym_character_code,
				FIX((SI_Long)92L)));
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			temp = CODE_CHAR(gensym_character_code);
			result = VALUES_2(temp,Nil);
		    }
		    else {
			temp = IFIX(gensym_character_code) < (SI_Long)256L 
				? 
				ISVREF(Iso_latin1_special_character_code_map,
				IFIX(gensym_character_code)) : Nil;
			if (temp);
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_capital_ligature_oe))
			    temp = CHR('W');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_small_ligature_oe))
			    temp = CHR('w');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_bullet))
			    temp = CHR('*');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_small_letter_f_with_hook))
			    temp = CHR('&');
			else if (FIXNUM_EQ(gensym_character_code,
				Gensym_code_for_trade_mark_sign))
			    temp = CHR(':');
			else
			    temp = Qnil;
			char_1 = temp;
			if (char_1)
			    result = VALUES_2(char_1,CHR('~'));
			else
			    result = VALUES_2(gensym_character_code,CHR('\\'));
		    }
		}
		MVS_2(result,character_or_character_code,escape_character_qm);
		if ( !TRUEP(escape_character_qm)) {
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_or_character_code;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing = character_or_character_code;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
		    kanji_code = character_or_character_code;
		    octet_1_qm = Nil;
		    octet_2 = (SI_Long)0L;
		    octet_3 = (SI_Long)0L;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = (SI_Long)92L;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing_1 = (SI_Long)92L;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		    code = kanji_code;
		    result = chestnut_floorf_function(FIX(IFIX(code) & 
			    (SI_Long)8191L),FIX((SI_Long)95L));
		    MVS_2(result,quotient,remainder_1);
		    octet_2 = IFIX(quotient) + (SI_Long)40L;
		    octet_3 = IFIX(remainder_1) + (SI_Long)32L;
		    octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L == 
			    (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
			    (SI_Long)13L) + (SI_Long)32L) : Nil;
		    if (octet_1_qm) {
			simple_or_wide_character = octet_1_qm;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = simple_or_wide_character;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = simple_or_wide_character;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    simple_or_wide_character_1 = octet_2;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = simple_or_wide_character_1;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing_1 = simple_or_wide_character_1;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		    simple_or_wide_character_1 = octet_3;
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing_1 = simple_or_wide_character_1;
			twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing_1 = simple_or_wide_character_1;
			schar_new_value = 
				CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		else {
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = escape_character_qm;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing = escape_character_qm;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		    if (EQ(Current_twriting_output_type,Qwide_string)) {
			thing = character_or_character_code;
			twrite_wide_character(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
		    }
		    else {
			if ( 
				!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				Total_length_of_current_gensym_string))
			    extend_current_gensym_string(0);
			temp_2 = Current_gensym_string;
			temp_3 = Fill_pointer_for_current_gensym_string;
			thing = character_or_character_code;
			schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				CHAR_CODE(thing) : thing);
			SET_SCHAR(temp_2,temp_3,schar_new_value);
			temp_2 = 
				FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			Fill_pointer_for_current_gensym_string = temp_2;
		    }
		}
		if (extended_code_qm) {
		    char_1 = Nil;
		    if (FIXNUM_EQ(extended_code_qm,Gensym_code_for_linebreak))
			result = VALUES_2(Gensym_char_or_code_for_linebreak,
				Gensym_esc_for_linebreak_qm);
		    else if (FIXNUM_EQ(extended_code_qm,
			    Gensym_code_for_paragraph_break))
			result = VALUES_2(Gensym_char_or_code_for_paragraph_break,
				Gensym_esc_for_paragraph_break_qm);
		    else {
			if ((SI_Long)32L <= IFIX(extended_code_qm) && 
				IFIX(extended_code_qm) <= (SI_Long)126L) {
			    simple_gensym_character_code = extended_code_qm;
			    temp_1 =  
				    !(FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)64L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)126L)) || 
				    FIXNUM_EQ(simple_gensym_character_code,
				    FIX((SI_Long)92L)));
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    temp = CODE_CHAR(extended_code_qm);
			    result = VALUES_2(temp,Nil);
			}
			else {
			    temp = IFIX(extended_code_qm) < (SI_Long)256L ?
				     
				    ISVREF(Iso_latin1_special_character_code_map,
				    IFIX(extended_code_qm)) : Nil;
			    if (temp);
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_capital_ligature_oe))
				temp = CHR('W');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_small_ligature_oe))
				temp = CHR('w');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_bullet))
				temp = CHR('*');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_small_letter_f_with_hook))
				temp = CHR('&');
			    else if (FIXNUM_EQ(extended_code_qm,
				    Gensym_code_for_trade_mark_sign))
				temp = CHR(':');
			    else
				temp = Qnil;
			    char_1 = temp;
			    if (char_1)
				result = VALUES_2(char_1,CHR('~'));
			    else
				result = VALUES_2(extended_code_qm,CHR('\\'));
			}
		    }
		    MVS_2(result,character_or_character_code,
			    escape_character_qm);
		    if ( !TRUEP(escape_character_qm)) {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
			kanji_code = character_or_character_code;
			octet_1_qm = Nil;
			octet_2 = (SI_Long)0L;
			octet_3 = (SI_Long)0L;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = (SI_Long)92L;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = (SI_Long)92L;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			code = kanji_code;
			result = chestnut_floorf_function(FIX(IFIX(code) & 
				(SI_Long)8191L),FIX((SI_Long)95L));
			MVS_2(result,quotient,remainder_1);
			octet_2 = IFIX(quotient) + (SI_Long)40L;
			octet_3 = IFIX(remainder_1) + (SI_Long)32L;
			octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L 
				== (SI_Long)1L) ? FIX((IFIX(code) >>  -  - 
				(SI_Long)13L) + (SI_Long)32L) : Nil;
			if (octet_1_qm) {
			    simple_or_wide_character = octet_1_qm;
			    if (EQ(Current_twriting_output_type,
					Qwide_string)) {
				thing = simple_or_wide_character;
				twrite_wide_character(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
			    }
			    else {
				if ( 
					!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					Total_length_of_current_gensym_string))
				    extend_current_gensym_string(0);
				temp_2 = Current_gensym_string;
				temp_3 = 
					Fill_pointer_for_current_gensym_string;
				thing = simple_or_wide_character;
				schar_new_value = 
					CODE_CHAR(CHARACTERP(thing) ? 
					CHAR_CODE(thing) : thing);
				SET_SCHAR(temp_2,temp_3,schar_new_value);
				temp_2 = 
					FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				Fill_pointer_for_current_gensym_string = 
					temp_2;
			    }
			}
			simple_or_wide_character_1 = octet_2;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			simple_or_wide_character_1 = octet_3;
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing_1 = simple_or_wide_character_1;
			    twrite_wide_character(CHARACTERP(FIX(thing_1)) 
				    ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing_1 = simple_or_wide_character_1;
			    schar_new_value = 
				    CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
				    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		    else {
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = escape_character_qm;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = escape_character_qm;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
			if (EQ(Current_twriting_output_type,Qwide_string)) {
			    thing = character_or_character_code;
			    twrite_wide_character(CHARACTERP(thing) ? 
				    CHAR_CODE(thing) : thing);
			}
			else {
			    if ( 
				    !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				    Total_length_of_current_gensym_string))
				extend_current_gensym_string(0);
			    temp_2 = Current_gensym_string;
			    temp_3 = Fill_pointer_for_current_gensym_string;
			    thing = character_or_character_code;
			    schar_new_value = CODE_CHAR(CHARACTERP(thing) ?
				     CHAR_CODE(thing) : thing);
			    SET_SCHAR(temp_2,temp_3,schar_new_value);
			    temp_2 = 
				    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			    Fill_pointer_for_current_gensym_string = temp_2;
			}
		    }
		}
	    }
	    index_1 = FIXNUM_ADD1(index_1);
	    goto next_loop;
	  end_loop:
	    temp = using_string_buffer_p ? 
		    intern_using_string_buffer(Intern_string_buffer,
		    index_1,Nil) : intern_gensym_string(2,
		    copy_out_current_gensym_string(),Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    result = VALUES_2(temp,ch);
  end_read_xml_name:
    return result;
}

/* XML-WHITESPACE-P */
Object xml_whitespace_p(ch)
    Object ch;
{
    Object temp;

    x_note_fn_call(136,283);
    temp = IFIX(ch) == (SI_Long)32L ? T : Nil;
    if (temp);
    else
	temp = IFIX(ch) == (SI_Long)9L ? T : Nil;
    if (temp);
    else
	temp = IFIX(ch) == (SI_Long)8232L ? T : Nil;
    if (temp);
    else
	temp = IFIX(ch) == (SI_Long)10L ? T : Nil;
    if (temp);
    else
	temp = IFIX(ch) == (SI_Long)13L ? T : Nil;
    return VALUES_1(temp);
}

/* READ-XML-CHAR-SKIPPING-WHITESPACE */
Object read_xml_char_skipping_whitespace varargs_1(int, n)
{
    Object next_char, ch, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(136,284);
    INIT_ARGS_nonrelocating();
    next_char = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    ch = Nil;
  next_loop:
    if (next_char) {
	temp = next_char;
	next_char = Nil;
	ch = temp;
    }
    else
	ch = read_next_xml_char();
    if ( !(ch && xml_whitespace_p(ch)))
	return VALUES_1(ch);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_153;  /* "Expected >" */

static Object string_constant_154;  /* "Expected =" */

static Object string_constant_155;  /* "Expected an attribute, /, or >" */

/* READ-XML-ATTRIBUTES */
Object read_xml_attributes(next_char,xml_read_context)
    Object next_char, xml_read_context;
{
    Object emptyp, ch, attvalue, result_1, ab_loopvar_, ab_loopvar__1, temp;
    Object gensymed_symbol, name, next_char_after_name, error_string, error_1;
    char temp_1;
    Object result;

    x_note_fn_call(136,285);
    emptyp = Nil;
    ch = Nil;
    attvalue = Nil;
    result_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    temp = read_xml_char_skipping_whitespace(1,next_char);
    next_char = Nil;
    ch = temp;
    if (IFIX(ch) == (SI_Long)47L) {
	emptyp = T;
	if ( !((SI_Long)62L == IFIX(read_next_xml_char()))) {
	    reclaim_eval_list_1(result_1);
	    temp = read_xml_error_string(2,xml_read_context,
		    string_constant_153);
	    return VALUES_2(Nil,temp);
	}
	attvalue = T;
    }
    else if (IFIX(ch) == (SI_Long)62L)
	attvalue = T;
    else {
	gensymed_symbol = ch;
	temp_1 = (SI_Long)97L <= IFIX(gensymed_symbol) ? 
		IFIX(gensymed_symbol) <= (SI_Long)122L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = (SI_Long)65L <= IFIX(gensymed_symbol) ? 
		    IFIX(gensymed_symbol) <= (SI_Long)90L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = IFIX(ch) == (SI_Long)95L;
	if (temp_1);
	else
	    temp_1 = IFIX(ch) == (SI_Long)58L;
	if (temp_1) {
	    result = read_xml_name(ch);
	    MVS_3(result,name,next_char_after_name,error_string);
	    if (error_string) {
		reclaim_eval_list_1(result_1);
		temp = read_xml_error_string(2,xml_read_context,error_string);
		return VALUES_2(Nil,temp);
	    }
	    if ( !((SI_Long)61L == 
		    IFIX(read_xml_char_skipping_whitespace(1,
		    next_char_after_name)))) {
		reclaim_eval_list_1(result_1);
		temp = read_xml_error_string(2,xml_read_context,
			string_constant_154);
		return VALUES_2(Nil,temp);
	    }
	    result = read_xml_attvalue(read_xml_char_skipping_whitespace(0),
		    xml_read_context);
	    MVS_2(result,attvalue,error_1);
	    if (error_1)
		return VALUES_1(error_1);
	    attvalue = eval_list_2(name,attvalue);
	}
	else {
	    reclaim_eval_list_1(result_1);
	    temp = read_xml_error_string(2,xml_read_context,
		    string_constant_155);
	    return VALUES_2(Nil,temp);
	}
    }
    if (ATOM(attvalue))
	goto end_loop;
    ab_loopvar__1 = attvalue;
    if (ab_loopvar__1) {
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_1 = ab_loopvar__1;
	ab_loopvar_ = last(ab_loopvar__1,_);
    }
    goto next_loop;
  end_loop:
    temp = result_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_2(temp,emptyp);
}

static Object QAMP;                /* |amp| */

static Object QLT;                 /* |lt| */

static Object QGT;                 /* |gt| */

static Object QQUOT;               /* |quot| */

static Object string_constant_156;  /* "Unrecognized character reference \"&~a;\"" */

static Object string_constant_157;  /* "Expected \";\"" */

/* READ-XML-REFERENCE */
Object read_xml_reference(xml_read_context)
    Object xml_read_context;
{
    Object name, next_char, error_string;
    Object result;

    x_note_fn_call(136,286);
    result = read_xml_name(Nil);
    MVS_3(result,name,next_char,error_string);
    if (error_string)
	return read_xml_error_string(2,xml_read_context,error_string);
    else if ((SI_Long)59L == IFIX(next_char)) {
	if (EQ(name,QAMP))
	    return VALUES_1(FIX((SI_Long)38L));
	else if (EQ(name,QLT))
	    return VALUES_1(FIX((SI_Long)60L));
	else if (EQ(name,QGT))
	    return VALUES_1(FIX((SI_Long)62L));
	else if (EQ(name,QQUOT))
	    return VALUES_1(FIX((SI_Long)34L));
	else
	    return read_xml_error_string(3,xml_read_context,
		    string_constant_156,name);
    }
    else
	return read_xml_error_string(2,xml_read_context,string_constant_157);
}

static Object string_constant_158;  /* "Expected \" or '" */

/* READ-XML-ATTVALUE */
Object read_xml_attvalue(quote,xml_read_context)
    Object quote, xml_read_context;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object ch, result_1, simple_or_wide_character, thing, temp, schar_arg_2;
    Object schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(136,287);
    if ( !(IFIX(quote) == (SI_Long)34L || IFIX(quote) == (SI_Long)39L)) {
	result = VALUES_2(Nil,string_constant_158);
	goto end_read_xml_attvalue;
    }
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      ch = Nil;
	    next_loop:
	      ch = read_next_xml_char();
	      if (FIXNUM_EQ(ch,quote))
		  goto end_loop;
	      if ((SI_Long)38L == IFIX(ch)) {
		  result_1 = read_xml_reference(xml_read_context);
		  if (text_string_p(result_1)) {
		      result = VALUES_2(Nil,result_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_read_xml_attvalue;
		  }
		  else
		      simple_or_wide_character = result_1;
	      }
	      else
		  simple_or_wide_character = ch;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = simple_or_wide_character;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      goto next_loop;
	    end_loop:;
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
  end_read_xml_attvalue:
    return result;
}

/* TWRITE-TEXT-STRING */
Object twrite_text_string(string_1)
    Object string_1;
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long i, ab_loop_bind_, simple_or_wide_character, thing;

    x_note_fn_call(136,288);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(string_1));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    simple_or_wide_character = UBYTE_16_ISAREF_1(string_1,i);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = simple_or_wide_character;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = simple_or_wide_character;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* READ-XML-MAKE-ATTRIBUTE-NAME */
Object read_xml_make_attribute_name(name,kind)
    Object name, kind;
{
    x_note_fn_call(136,289);
    if ((EQ(kind,Quser_attribute) || EQ(kind,Qqualified_attribute)) && 
	    ATOM(name))
	return eval_cons_1(name,Nil);
    else
	return VALUES_1(name);
}

DEFINE_VARIABLE_WITH_SYMBOL(Most_recent_xml_checksum_differences, Qmost_recent_xml_checksum_differences);

static Object string_constant_159;  /* "Checksum Error in ~A: ~(~L,A~)" */

static Object string_constant_160;  /* "Checksum Error: ~(~L,A~)" */

/* CHECK-AND-REPORT-XML-CHECKSUM-PROBLEMS */
Object check_and_report_xml_checksum_problems(data)
    Object data;
{
    Object difference;

    x_note_fn_call(136,290);
    difference = check_xml_object_checksums(data);
    if (difference) {
	if (BOUNDP(Qname_text_string_for_kb_being_read) && 
		Name_text_string_for_kb_being_read)
	    notify_user(3,string_constant_159,
		    Name_text_string_for_kb_being_read,difference);
	else
	    notify_user(2,string_constant_160,difference);
    }
    if (CONSP(Most_recent_xml_checksum_differences))
	reclaim_gensym_list_1(Most_recent_xml_checksum_differences);
    Most_recent_xml_checksum_differences = difference;
    return VALUES_1(Most_recent_xml_checksum_differences);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_module_data, Qcurrent_module_data);

DEFINE_VARIABLE_WITH_SYMBOL(Initialize_items_count, Qinitialize_items_count);

DEFINE_VARIABLE_WITH_SYMBOL(Delayed_item_array_initializations, Qdelayed_item_array_initializations);

DEFINE_VARIABLE_WITH_SYMBOL(Delay_item_array_initializations_p, Qdelay_item_array_initializations_p);

DEFINE_VARIABLE_WITH_SYMBOL(Externaldefinitions_fixups, Qexternaldefinitions_fixups);

DEFINE_VARIABLE_WITH_SYMBOL(Systemtables_fixups, Qsystemtables_fixups);

DEFINE_VARIABLE_WITH_SYMBOL(Systemtables_are_initialized_p, Qsystemtables_are_initialized_p);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_window_for_initializing_definitions, Qkb_window_for_initializing_definitions);

DEFINE_VARIABLE_WITH_SYMBOL(Clear_text_item_layering_info, Qclear_text_item_layering_info);

DEFINE_VARIABLE_WITH_SYMBOL(Disable_update_button, Qdisable_update_button);

DEFINE_VARIABLE_WITH_SYMBOL(Disable_subworkspace_connection_posts, Qdisable_subworkspace_connection_posts);

DEFINE_VARIABLE_WITH_SYMBOL(Change_the_text_of_attributes_without_category_evaluator_interfaces_p, Qchange_the_text_of_attributes_without_category_evaluator_interfaces_p);

DEFINE_VARIABLE_WITH_SYMBOL(Changing_validity_interval_invalidates_current_value_p, Qchanging_validity_interval_invalidates_current_value_p);

DEFINE_VARIABLE_WITH_SYMBOL(Suppress_consistency_analysis_warnings_notes_qm, Qsuppress_consistency_analysis_warnings_notes_qm);

static Object Qkb_workspace;       /* kb-workspace */

static Object Qmodule_assignment;  /* module-assignment */

/* BUILD-KB-FROM-MODULE-DATA */
Object build_kb_from_module_data(data,auto_merge_case_qm)
    Object data, auto_merge_case_qm;
{
    Object current_module_data, current_computation_flags;
    Object ignore_kb_state_changes_p;
    Object suppress_updating_of_slot_value_representations_qm, reading_kb_p;
    Object loading_kb_p, initializing_clear_text_p;
    Object called_within_clear_text_loading;
    Object suppress_consistency_analysis_warnings_notes_qm;
    Object do_not_update_frame_authors_qm;
    Object changing_validity_interval_invalidates_current_value_p;
    Object change_the_text_of_attributes_without_category_evaluator_interfaces_p;
    Object keep_edit_workspace_hidden_no_matter_what_qm;
    Object allow_name_box_creation, disable_tracing_and_breakpoints_warning;
    Object delayed_item_array_initializations;
    Object delay_item_array_initializations_p;
    Object disable_subworkspace_connection_posts, disable_update_button;
    Object total_items_in_file, initialize_items_count;
    Object externaldefinitions_fixups, systemtables_fixups;
    Object systemtables_are_initialized_p;
    Object kb_window_for_initializing_definitions;
    Object clear_text_item_layering_info, do_not_note_permanent_changes_p;
    Object gensymed_symbol, gensymed_symbol_1;
    Declare_special(27);
    Object result;

    x_note_fn_call(136,291);
    current_module_data = data;
    current_computation_flags = Current_computation_flags;
    ignore_kb_state_changes_p = T;
    suppress_updating_of_slot_value_representations_qm = Nil;
    reading_kb_p = Nil;
    loading_kb_p = Nil;
    initializing_clear_text_p = T;
    called_within_clear_text_loading = T;
    suppress_consistency_analysis_warnings_notes_qm = T;
    do_not_update_frame_authors_qm = T;
    changing_validity_interval_invalidates_current_value_p = Nil;
    change_the_text_of_attributes_without_category_evaluator_interfaces_p = T;
    keep_edit_workspace_hidden_no_matter_what_qm = T;
    allow_name_box_creation = Nil;
    disable_tracing_and_breakpoints_warning = T;
    delayed_item_array_initializations = Nil;
    delay_item_array_initializations_p = T;
    disable_subworkspace_connection_posts = T;
    disable_update_button = T;
    total_items_in_file = Nil;
    initialize_items_count = FIX((SI_Long)0L);
    externaldefinitions_fixups = get_xml_fixups(get_xml_fixups(data,
	    QModule,Nil),QEXTERNALDEFINITIONS,Nil);
    systemtables_fixups = get_xml_fixups(get_xml_fixups(data,QModule,Nil),
	    QSYSTEMTABLES,Nil);
    systemtables_are_initialized_p = Nil;
    kb_window_for_initializing_definitions = Nil;
    clear_text_item_layering_info = Nil;
    do_not_note_permanent_changes_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    26);
      PUSH_SPECIAL_WITH_SYMBOL(Clear_text_item_layering_info,Qclear_text_item_layering_info,clear_text_item_layering_info,
	      25);
	PUSH_SPECIAL_WITH_SYMBOL(Kb_window_for_initializing_definitions,Qkb_window_for_initializing_definitions,kb_window_for_initializing_definitions,
		24);
	  PUSH_SPECIAL_WITH_SYMBOL(Systemtables_are_initialized_p,Qsystemtables_are_initialized_p,systemtables_are_initialized_p,
		  23);
	    PUSH_SPECIAL_WITH_SYMBOL(Systemtables_fixups,Qsystemtables_fixups,systemtables_fixups,
		    22);
	      PUSH_SPECIAL_WITH_SYMBOL(Externaldefinitions_fixups,Qexternaldefinitions_fixups,externaldefinitions_fixups,
		      21);
		PUSH_SPECIAL_WITH_SYMBOL(Initialize_items_count,Qinitialize_items_count,initialize_items_count,
			20);
		  PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
			  19);
		    PUSH_SPECIAL_WITH_SYMBOL(Disable_update_button,Qdisable_update_button,disable_update_button,
			    18);
		      PUSH_SPECIAL_WITH_SYMBOL(Disable_subworkspace_connection_posts,Qdisable_subworkspace_connection_posts,disable_subworkspace_connection_posts,
			      17);
			PUSH_SPECIAL_WITH_SYMBOL(Delay_item_array_initializations_p,Qdelay_item_array_initializations_p,delay_item_array_initializations_p,
				16);
			  PUSH_SPECIAL_WITH_SYMBOL(Delayed_item_array_initializations,Qdelayed_item_array_initializations,delayed_item_array_initializations,
				  15);
			    PUSH_SPECIAL_WITH_SYMBOL(Disable_tracing_and_breakpoints_warning,Qdisable_tracing_and_breakpoints_warning,disable_tracing_and_breakpoints_warning,
				    14);
			      PUSH_SPECIAL_WITH_SYMBOL(Allow_name_box_creation,Qallow_name_box_creation,allow_name_box_creation,
				      13);
				PUSH_SPECIAL_WITH_SYMBOL(Keep_edit_workspace_hidden_no_matter_what_qm,Qkeep_edit_workspace_hidden_no_matter_what_qm,keep_edit_workspace_hidden_no_matter_what_qm,
					12);
				  PUSH_SPECIAL_WITH_SYMBOL(Change_the_text_of_attributes_without_category_evaluator_interfaces_p,Qchange_the_text_of_attributes_without_category_evaluator_interfaces_p,change_the_text_of_attributes_without_category_evaluator_interfaces_p,
					  11);
				    PUSH_SPECIAL_WITH_SYMBOL(Changing_validity_interval_invalidates_current_value_p,Qchanging_validity_interval_invalidates_current_value_p,changing_validity_interval_invalidates_current_value_p,
					    10);
				      PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_frame_authors_qm,Qdo_not_update_frame_authors_qm,do_not_update_frame_authors_qm,
					      9);
					PUSH_SPECIAL_WITH_SYMBOL(Suppress_consistency_analysis_warnings_notes_qm,Qsuppress_consistency_analysis_warnings_notes_qm,suppress_consistency_analysis_warnings_notes_qm,
						8);
					  PUSH_SPECIAL_WITH_SYMBOL(Called_within_clear_text_loading,Qcalled_within_clear_text_loading,called_within_clear_text_loading,
						  7);
					    PUSH_SPECIAL_WITH_SYMBOL(Initializing_clear_text_p,Qinitializing_clear_text_p,initializing_clear_text_p,
						    6);
					      PUSH_SPECIAL_WITH_SYMBOL(Loading_kb_p,Qloading_kb_p,loading_kb_p,
						      5);
						PUSH_SPECIAL_WITH_SYMBOL(Reading_kb_p,Qreading_kb_p,reading_kb_p,
							4);
						  PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm,Qsuppress_updating_of_slot_value_representations_qm,suppress_updating_of_slot_value_representations_qm,
							  3);
						    PUSH_SPECIAL_WITH_SYMBOL(Ignore_kb_state_changes_p,Qignore_kb_state_changes_p,ignore_kb_state_changes_p,
							    2);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
							      1);
							PUSH_SPECIAL_WITH_SYMBOL(Current_module_data,Qcurrent_module_data,current_module_data,
								0);
							  Current_computation_flags 
								  = 
								  FIX(IFIX(Current_computation_flags) 
								  | 
								  (SI_Long)16L);
							  Current_computation_flags 
								  = 
								  FIX(IFIX(Current_computation_flags) 
								  | 
								  (SI_Long)2048L);
							  Current_computation_flags 
								  = 
								  FIX(IFIX(Current_computation_flags) 
								  | 
								  (SI_Long)4096L);
							  Current_g2_rdf_module 
								  = 
								  module_name_symbol_for_xml_object(data);
							  Kb_window_for_initializing_definitions 
								  = 
								  make_permanent_item(Qkb_workspace);
							  initialize_all_units_of_measure_declarations_from_module_data(data);
							  find_and_create_all_definitions_in_module_data(data);
							  create_all_system_frames_from_module_data();
							  create_all_instances_from_module_data(data,
								  Nil);
							  create_all_instances_from_module_data(data,
								  T);
							  initialize_all_relations_from_module_data(data);
							  update_initialize_xml_progress(0);
							  initialize_all_instances_from_module_data(data);
							  do_delayed_array_initializations();
							  create_and_initialize_all_connections_from_module_data(data,
								  T);
							  create_and_initialize_all_connections_from_module_data(data,
								  Nil);
							  create_all_instances_from_module_data(data,
								  T);
							  initialize_all_relationships_from_module_data(data);
							  update_initialize_xml_progress(1,
								  T);
							  fix_clear_text_item_layering_from_module_data(data);
							  re_initialize_all_generic_simulation_formulas_from_modula_data(data);
							  if (System_has_paused 
								  || 
								  System_is_running) 
								      {
							      Disable_update_button 
								      = Nil;
							      update_all_buttons_from_module_data(data);
							  }
							  Allow_name_box_creation 
								  = T;
							  deal_with_class_name_conflicts(auto_merge_case_qm,
								  T);
							  delete_blocks_and_connections_to_be_deleted_after_reading();
							  gensymed_symbol 
								  = 
								  ACCESS_ONCE(ISVREF(Kb_window_for_initializing_definitions,
								  (SI_Long)14L));
							  gensymed_symbol 
								  = 
								  gensymed_symbol 
								  ? 
								  ACCESS_ONCE(ISVREF(gensymed_symbol,
								  (SI_Long)4L)) 
								  : Nil;
							  if (gensymed_symbol) 
								      {
							      if (Current_g2_rdf_module)
								  initialize_attribute_from_module_data(3,
									  Kb_window_for_initializing_definitions,
									  Qmodule_assignment,
									  Current_g2_rdf_module);
							  }
							  else
							      delete_frame(Kb_window_for_initializing_definitions);
							  fix_all_workspace_sizes_from_module_data(data);
							  if ( 
								  !(System_has_paused 
								  || 
								  System_is_running)) 
								      {
							    next_loop:
							      gensymed_symbol 
								      = 
								      System_has_paused;
							      gensymed_symbol_1 
								      = T;
							      if (CAS_SYMBOL(Qsystem_has_paused,
								      gensymed_symbol,
								      gensymed_symbol_1))
								  goto end_1;
							      goto next_loop;
							    end_loop:
							    end_1:
							      system_reset();
							  }
							  set_up_panes_from_module_data(data);
							  result = VALUES_1(Nil);
							POP_SPECIAL();
						      POP_SPECIAL();
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qdetail_pane_description;  /* detail-pane-description */

/* SET-UP-PANES-FROM-MODULE-DATA */
Object set_up_panes_from_module_data(data)
    Object data;
{
    Object pane_fixups, gensymed_symbol, held_vector, pane, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt;
    Object gensymed_symbol_1, car_new_value, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(136,292);
    pane_fixups = get_xml_fixups(get_xml_fixups(data,QModule,Nil),QPANES,Nil);
    if (pane_fixups) {
	gensymed_symbol = get_xml_object(pane_fixups);
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	pane = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	pane = validated_elt;
	if (estructure_slot(pane,Qworkspace,Nil)) {
	    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    car_new_value = estructure_slot(pane,Qworkspace,Nil);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = estructure_slot(pane,Qx_in_workspace,Nil);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = estructure_slot(pane,Qy_in_workspace,Nil);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = estructure_slot(pane,Qx_magnification,Nil);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = estructure_slot(pane,Qy_magnification,Nil);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    ab_loopvar__2 = slot_value_cons_1(gensymed_symbol,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    Plist_from_end_element_qm = 
	    nconc2(slot_value_list_2(Qdetail_pane_description,temp),
	    Plist_from_end_element_qm);
    return VALUES_1(Plist_from_end_element_qm);
}

/* UPDATE-INITIALIZE-XML-PROGRESS */
Object update_initialize_xml_progress varargs_1(int, n)
{
    Object force_update_p, temp_1, temp_2;
    Object suppress_updating_of_slot_value_representations_qm;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,293);
    INIT_ARGS_nonrelocating();
    force_update_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Kb_file_progress && Systemtables_are_initialized_p) {
	temp = TRUEP(force_update_p);
	if (temp);
	else {
	    temp_1 = FIX((SI_Long)0L);
	    temp_2 = chestnut_modf_function(Initialize_items_count,
		    FIX((SI_Long)10L));
	    temp = NUM_EQ(temp_1,temp_2);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	suppress_updating_of_slot_value_representations_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm,Qsuppress_updating_of_slot_value_representations_qm,suppress_updating_of_slot_value_representations_qm,
		0);
	  result = update_file_progress_display(3,Kb_file_progress,
		  Initialize_items_count,force_update_p);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Definitions_in_module, Qdefinitions_in_module);

DEFINE_VARIABLE_WITH_SYMBOL(Definitions_in_module_to_go, Qdefinitions_in_module_to_go);

DEFINE_VARIABLE_WITH_SYMBOL(In_external_definitions_for_module_p, Qin_external_definitions_for_module_p);

static Object Qab_class_name;      /* class-name */

static Object Qdirect_superior_classes;  /* direct-superior-classes */

/* RECORD-DEFINITIONS-IN-MODULE-DATA */
Object record_definitions_in_module_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, temp, fixups;
    Object class_1, class_name, direct_superior_classes, value;
    Object gensymed_symbol, gensymed_symbol_1, car_new_value, held_vector;
    Object name_1, attribute_value;
    SI_Long name, ab_loop_bind_, next_index, length_1, gensymed_symbol_2;

    x_note_fn_call(136,294);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	temp = Nil;
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	class_1 = Nil;
	class_name = Nil;
	direct_superior_classes = Nil;
	if (fixups) {
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop:
	    if (name >= ab_loop_bind_)
		goto end_loop;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    if (EQ(FIX(name),Qab_class))
		class_1 = value;
	    else if (EQ(FIX(name),Qab_class_name))
		class_name = value;
	    else if (EQ(FIX(name),Qdirect_superior_classes))
		direct_superior_classes = value;
	    if ( !EQ(object_and_fixups,Externaldefinitions_fixups) || 
		    In_external_definitions_for_module_p)
		record_definitions_in_module_data(value);
	    name = name + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	if (class_1 && class_name && direct_superior_classes &&  
		!TRUEP(assq_function(class_name,Definitions_in_module))) {
	    gensymed_symbol = make_eval_list_1(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = class_name;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Nil;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = object_and_fixups;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = In_external_definitions_for_module_p;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = class_1;
	    Definitions_in_module = eval_cons_1(gensymed_symbol,
		    Definitions_in_module);
	    temp = Definitions_in_module;
	}
	else
	    temp = Nil;
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	class_1 = Nil;
	class_name = Nil;
	direct_superior_classes = Nil;
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_2 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_2 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    if (EQ(name_1,Qab_class))
		class_1 = value;
	    else if (EQ(name_1,Qab_class_name))
		class_name = value;
	    else if (EQ(name_1,Qdirect_superior_classes))
		direct_superior_classes = value;
	    if ( !EQ(object_and_fixups,Externaldefinitions_fixups) || 
		    In_external_definitions_for_module_p)
		record_definitions_in_module_data(value);
	    goto next_loop_1;
	  end_loop_1:;
	}
	if (class_1 && class_name && direct_superior_classes &&  
		!TRUEP(assq_function(class_name,Definitions_in_module))) {
	    gensymed_symbol = make_eval_list_1(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = class_name;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Nil;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = object_and_fixups;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = In_external_definitions_for_module_p;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = class_1;
	    Definitions_in_module = eval_cons_1(gensymed_symbol,
		    Definitions_in_module);
	    temp = Definitions_in_module;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* CREATE-ALL-DEFINITIONS-IN-MODULE */
Object create_all_definitions_in_module()
{
    Object gensymed_symbol, gensymed_symbol_1, definitions_in_module_to_go;
    Object eval_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(136,295);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    definitions_in_module_to_go = eval_cons_1(gensymed_symbol,
	    copy_list_using_eval_conses_1(Definitions_in_module));
    PUSH_SPECIAL_WITH_SYMBOL(Definitions_in_module_to_go,Qdefinitions_in_module_to_go,definitions_in_module_to_go,
	    0);
    next_loop:
      if ( !TRUEP(CDR(Definitions_in_module_to_go)))
	  goto end_loop;
      create_all_definitions_in_module_1(CADR(Definitions_in_module_to_go));
      goto next_loop;
    end_loop:
      eval_pop_store = Nil;
      cons_1 = Definitions_in_module_to_go;
      if (cons_1) {
	  eval_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_eval_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_eval_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_eval_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Definitions_in_module_to_go = next_cons;
      reclaim_eval_list_1(eval_pop_store);
    POP_SPECIAL();
  next_loop_1:
    if ( !TRUEP(Definitions_in_module))
	goto end_loop_1;
    eval_pop_store = Nil;
    cons_1 = Definitions_in_module;
    if (cons_1) {
	eval_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Definitions_in_module = next_cons;
    reclaim_eval_list_1(eval_pop_store);
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object Qclass_specific_attributes;  /* class-specific-attributes */

static Object Qattribute_initial_item_class;  /* attribute-initial-item-class */

/* CREATE-ALL-DEFINITIONS-IN-MODULE-1 */
Object create_all_definitions_in_module_1(name_plus_nname_plus_object_and_fixups_plus_ghostp_plus_class)
    Object name_plus_nname_plus_object_and_fixups_plus_ghostp_plus_class;
{
    Object object_and_fixups, reading_ghost_definitions_p, class_1;
    Object direct_superior_classes, class_specific_attributes, gensymed_symbol;
    Object held_vector, definition, elt_1, validated_elt, attr_spec;
    SI_Long next_index, length_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,296);
    if (memq_function(name_plus_nname_plus_object_and_fixups_plus_ghostp_plus_class,
	    Definitions_in_module_to_go)) {
	Definitions_in_module_to_go = 
		delete_eval_element_1(name_plus_nname_plus_object_and_fixups_plus_ghostp_plus_class,
		Definitions_in_module_to_go);
	object_and_fixups = 
		THIRD(name_plus_nname_plus_object_and_fixups_plus_ghostp_plus_class);
	reading_ghost_definitions_p = 
		FOURTH(name_plus_nname_plus_object_and_fixups_plus_ghostp_plus_class);
	PUSH_SPECIAL_WITH_SYMBOL(Reading_ghost_definitions_p,Qreading_ghost_definitions_p,reading_ghost_definitions_p,
		0);
	  class_1 = 
		  FIFTH(name_plus_nname_plus_object_and_fixups_plus_ghostp_plus_class);
	  direct_superior_classes = 
		  get_xml_object(get_xml_fixups(object_and_fixups,
		  Qdirect_superior_classes,Nil));
	  class_specific_attributes = 
		  get_xml_object(get_xml_fixups(object_and_fixups,
		  Qclass_specific_attributes,Nil));
	  create_all_definitions_in_module_1(class_1);
	  if (direct_superior_classes) {
	      gensymed_symbol = direct_superior_classes;
	      held_vector = Nil;
	      next_index = (SI_Long)1L;
	      length_1 = (SI_Long)0L;
	      class_1 = Nil;
	      definition = Nil;
	      held_vector = M_CAR(gensymed_symbol);
	      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop:
	      if (next_index >= length_1)
		  goto end_loop;
	      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      next_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),next_index & 
		      (SI_Long)1023L);
	      validated_elt = elt_1 ? 
		      validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	      next_index = next_index + (SI_Long)1L;
	      class_1 = validated_elt;
	      definition = assq_function(class_1,CDR(Definitions_in_module));
	      if (definition)
		  create_all_definitions_in_module_1(definition);
	      goto next_loop;
	    end_loop:;
	  }
	  if (class_specific_attributes) {
	      gensymed_symbol = class_specific_attributes;
	      held_vector = Nil;
	      next_index = (SI_Long)1L;
	      length_1 = (SI_Long)0L;
	      attr_spec = Nil;
	      class_1 = Nil;
	      definition = Nil;
	      held_vector = M_CAR(gensymed_symbol);
	      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop_1:
	      if (next_index >= length_1)
		  goto end_loop_1;
	      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      next_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),next_index & 
		      (SI_Long)1023L);
	      validated_elt = elt_1 ? 
		      validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	      next_index = next_index + (SI_Long)1L;
	      attr_spec = validated_elt;
	      class_1 = CONSP(attr_spec) && EQ(M_CDR(attr_spec),
		      Qab_structure) ? estructure_slot(attr_spec,
		      Qattribute_initial_item_class,Nil) : Qnil;
	      definition = class_1 ? assq_function(class_1,
		      CDR(Definitions_in_module)) : Qnil;
	      if (definition)
		  create_all_definitions_in_module_1(definition);
	      goto next_loop_1;
	    end_loop_1:;
	  }
	  create_all_instances_from_module_data(object_and_fixups,Nil);
	  create_all_instances_from_module_data(object_and_fixups,T);
	  result = initialize_definition_from_module_data(object_and_fixups);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* FIND-AND-CREATE-ALL-DEFINITIONS-IN-MODULE-DATA */
Object find_and_create_all_definitions_in_module_data(data)
    Object data;
{
    Object definitions_in_module, in_external_definitions_for_module_p;
    Declare_special(2);
    Object result;

    x_note_fn_call(136,297);
    definitions_in_module = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Definitions_in_module,Qdefinitions_in_module,definitions_in_module,
	    1);
      in_external_definitions_for_module_p = T;
      PUSH_SPECIAL_WITH_SYMBOL(In_external_definitions_for_module_p,Qin_external_definitions_for_module_p,in_external_definitions_for_module_p,
	      0);
	record_definitions_in_module_data(Externaldefinitions_fixups);
      POP_SPECIAL();
      record_definitions_in_module_data(data);
      result = create_all_definitions_in_module();
    POP_SPECIAL();
    return result;
}

/* GET-UUID-FROM-MODULE-DATA */
Object get_uuid_from_module_data(id_qm)
    Object id_qm;
{
    Object current_edit_state, uuid_qm, problem_report_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,298);
    if (id_qm) {
	current_edit_state = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		0);
	  result = compile_uuid_for_slot(3,id_qm,Nil,Quuid);
	POP_SPECIAL();
	MVS_2(result,uuid_qm,problem_report_qm);
	if (problem_report_qm) {
	    reclaim_text_string(problem_report_qm);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(uuid_qm);
    }
    else
	return VALUES_1(Nil);
}

/* GET-INSTANCE-FROM-UUID-REPRESENTATION */
Object get_instance_from_uuid_representation(id)
    Object id;
{
    Object uuid_qm, temp;

    x_note_fn_call(136,299);
    uuid_qm = get_uuid_from_module_data(id);
    temp = uuid_qm ? get_item_or_item_list_for_uuid(uuid_qm) : Nil;
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(uuid_qm) != (SI_Long)0L)
	reclaim_wide_string(uuid_qm);
    return VALUES_1(temp);
}

/* GET-INSTANCE-FROM-XML-LOCATOR */
Object get_instance_from_xml_locator(locator)
    Object locator;
{
    Object len, pos, id, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(136,300);
    if (text_string_p(locator)) {
	len = lengthw(locator);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(len);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if (UBYTE_16_ISAREF_1(locator,i) == (SI_Long)35L) {
	    pos = FIX(i);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	pos = Qnil;
      end_1:;
	if (pos) {
	    id = text_string_substring(locator,add1(pos),len);
	    temp = get_instance_from_uuid_representation(id);
	    reclaim_text_string(id);
	    return VALUES_1(temp);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-BINARY-FILE-INDEX-FROM-XML-LOCATOR */
Object get_binary_file_index_from_xml_locator(locator)
    Object locator;
{
    Object len, pos;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(136,301);
    if (text_string_p(locator)) {
	len = lengthw(locator);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(len);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if (UBYTE_16_ISAREF_1(locator,i) == (SI_Long)35L) {
	    pos = FIX(i);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	pos = Qnil;
      end_1:;
	if (pos)
	    return read_fixnum_from_string(2,locator,FIXNUM_ADD1(pos));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(May_create_simulation_subtable_from_module_data_p, Qmay_create_simulation_subtable_from_module_data_p);

static Object Qtext_cell_plist_for_text_box;  /* text-cell-plist-for-text-box */

/* CREATE-INSTANCE-FROM-MODULE-DATA */
Object create_instance_from_module_data(object_and_fixups,resolve_references_p)
    Object object_and_fixups, resolve_references_p;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object class_1, resource, class_description, sub_class_bit_vector, id;
    Object gensymed_symbol_3, names, total_items_in_file_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(136,302);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(object);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	class_1 = get_xml_fixups(object_and_fixups,Qab_class,Nil);
	resource = get_xml_fixups(object_and_fixups,QRDF_COL_RESOURCE,Nil);
	if ( !TRUEP(object)) {
	    if (resource) {
		if (resolve_references_p)
		    object = get_instance_from_xml_locator(resource);
	    }
	    else if (class_1) {
		if ( !TRUEP(resolve_references_p)) {
		    class_description = 
			    lookup_global_or_kb_specific_property_value(class_1,
			    Class_description_gkbprop);
		    if (class_description) {
			sub_class_bit_vector = ISVREF(class_description,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Connection_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			id = get_xml_fixups(object_and_fixups,Qid,Nil);
			if (id) {
			    Uuid_for_next_frame_qm = 
				    get_uuid_from_module_data(id);
			    Class_description_for_next_frame_qm = 
				    class_description;
			}
			sub_class_bit_vector = ISVREF(class_description,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Simulation_subtable_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    if (May_create_simulation_subtable_from_module_data_p) 
					{
				object = 
					make_frame_of_class_description(class_description);
				put_simulation_details(May_create_simulation_subtable_from_module_data_p,
					object,Nil);
				set_permanent_and_propagate(object,Nil);
			    }
			}
			else {
			    gensymed_symbol_3 = 
				    lookup_global_or_kb_specific_property_value(Qsystem_frame,
				    Class_description_gkbprop);
			    if (gensymed_symbol_3) {
				sub_class_bit_vector = 
					ISVREF(class_description,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol_3,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				object = make_system_frame(class_1);
			    else {
				object = 
					make_permanent_item_of_class_description(class_description);
				sub_class_bit_vector = 
					ISVREF(ISVREF(object,(SI_Long)1L),
					(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Block_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    remove_all_stubs_from_block(object);
				sub_class_bit_vector = 
					ISVREF(ISVREF(object,(SI_Long)1L),
					(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Text_box_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    change_slot_value(3,object,
					    Qtext_cell_plist_for_text_box,Nil);
			    }
			}
			if (object) {
			    gensymed_symbol_3 = 
				    lookup_global_or_kb_specific_property_value(Qsystem_frame,
				    Class_description_gkbprop);
			    if (gensymed_symbol_3) {
				sub_class_bit_vector = 
					ISVREF(class_description,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol_3,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp =  !temp;
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    names = 
				    get_xml_object(get_xml_fixups(object_and_fixups,
				    Qnames,Nil));
			    if (names)
				initialize_attribute_from_module_data(3,
					object,Qnames,names);
			}
		    }
		    if (class_description) {
			if ( !TRUEP(Total_items_in_file))
			    Total_items_in_file = FIX((SI_Long)0L);
			total_items_in_file_new_value = 
				FIXNUM_ADD1(Total_items_in_file);
			Total_items_in_file = total_items_in_file_new_value;
		    }
		}
	    }
	    if (object)
		set_evaluation_structure_slot(object_and_fixups_1,Qvalue,
			object);
	}
	return VALUES_1(object);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	class_1 = get_xml_fixups(object_and_fixups,Qab_class,Nil);
	resource = get_xml_fixups(object_and_fixups,QRDF_COL_RESOURCE,Nil);
	if ( !TRUEP(object)) {
	    if (resource) {
		if (resolve_references_p)
		    object = get_instance_from_xml_locator(resource);
	    }
	    else if (class_1) {
		if ( !TRUEP(resolve_references_p)) {
		    class_description = 
			    lookup_global_or_kb_specific_property_value(class_1,
			    Class_description_gkbprop);
		    if (class_description) {
			sub_class_bit_vector = ISVREF(class_description,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Connection_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			id = get_xml_fixups(object_and_fixups,Qid,Nil);
			if (id) {
			    Uuid_for_next_frame_qm = 
				    get_uuid_from_module_data(id);
			    Class_description_for_next_frame_qm = 
				    class_description;
			}
			sub_class_bit_vector = ISVREF(class_description,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Simulation_subtable_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    if (May_create_simulation_subtable_from_module_data_p) 
					{
				object = 
					make_frame_of_class_description(class_description);
				put_simulation_details(May_create_simulation_subtable_from_module_data_p,
					object,Nil);
				set_permanent_and_propagate(object,Nil);
			    }
			}
			else {
			    gensymed_symbol_3 = 
				    lookup_global_or_kb_specific_property_value(Qsystem_frame,
				    Class_description_gkbprop);
			    if (gensymed_symbol_3) {
				sub_class_bit_vector = 
					ISVREF(class_description,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol_3,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				object = make_system_frame(class_1);
			    else {
				object = 
					make_permanent_item_of_class_description(class_description);
				sub_class_bit_vector = 
					ISVREF(ISVREF(object,(SI_Long)1L),
					(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Block_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    remove_all_stubs_from_block(object);
				sub_class_bit_vector = 
					ISVREF(ISVREF(object,(SI_Long)1L),
					(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Text_box_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    change_slot_value(3,object,
					    Qtext_cell_plist_for_text_box,Nil);
			    }
			}
			if (object) {
			    gensymed_symbol_3 = 
				    lookup_global_or_kb_specific_property_value(Qsystem_frame,
				    Class_description_gkbprop);
			    if (gensymed_symbol_3) {
				sub_class_bit_vector = 
					ISVREF(class_description,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol_3,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp =  !temp;
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    names = 
				    get_xml_object(get_xml_fixups(object_and_fixups,
				    Qnames,Nil));
			    if (names)
				initialize_attribute_from_module_data(3,
					object,Qnames,names);
			}
		    }
		    if (class_description) {
			if ( !TRUEP(Total_items_in_file))
			    Total_items_in_file = FIX((SI_Long)0L);
			total_items_in_file_new_value = 
				FIXNUM_ADD1(Total_items_in_file);
			Total_items_in_file = total_items_in_file_new_value;
		    }
		}
	    }
	    if (object)
		set_evaluation_structure_slot(object_and_fixups_1,Qvalue,
			object);
	}
	return VALUES_1(object);
    }
}

/* REMOVE-ALL-STUBS-FROM-BLOCK */
Object remove_all_stubs_from_block(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, ab_less_than_branch_qm_, connections_to_delete;
    Object reference_serial_number, connection, ab_loop_list_, xa, ya;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(136,303);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = 
		  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L));
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
		      (SI_Long)0L),(SI_Long)0L));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection_qm = ab_connection_;
      ab_loopvar__2 = gensym_cons_1(connection_qm,Nil);
      if (ab_loopvar__1)
	  M_CDR(ab_loopvar__1) = ab_loopvar__2;
      else
	  ab_loopvar_ = ab_loopvar__2;
      ab_loopvar__1 = ab_loopvar__2;
      goto next_loop;
    end_loop_2:
      connections_to_delete = ab_loopvar_;
      goto end_2;
      connections_to_delete = Qnil;
    end_2:;
    POP_SPECIAL();
    reference_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    connection = Nil;
    ab_loop_list_ = connections_to_delete;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    connection = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(connection,(SI_Long)10L);
    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
	    (SI_Long)-1L : TRUEP(Nil);
    if (temp_1);
    else if (FIXNUMP(reference_serial_number))
	temp_1 = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_serial_number,gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp_1 = TRUEP(Nil);
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp_1 = FIXNUM_LT(xa,ya);
	if (temp_1);
	else
	    temp_1 = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp_1)
	delete_connection(1,connection);
    goto next_loop_3;
  end_loop_3:
    reclaim_frame_serial_number(reference_serial_number);
    reclaim_gensym_list_1(connections_to_delete);
    return VALUES_1(Qnil);
}

static Object list_constant_15;    /* # */

/* CREATE-AND-INITIALIZE-ALL-CONNECTIONS-FROM-MODULE-DATA */
Object create_and_initialize_all_connections_from_module_data(object_and_fixups,
	    do_loose_ends_p)
    Object object_and_fixups, do_loose_ends_p;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object class_1, class_description, sub_class_bit_vector, value;
    Object actual_value, temp_1, temp_2, temp_3;
    Object initialize_items_count_new_value, gensymed_symbol_3, held_vector;
    Object name_1, attribute_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, name, ab_loop_bind_;
    SI_Long next_index, length_1;
    char temp;

    x_note_fn_call(136,304);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(object);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if ( !TRUEP(object)) {
	    class_1 = get_xml_fixups(object_and_fixups,Qab_class,Nil);
	    if (class_1) {
		class_description = 
			lookup_global_or_kb_specific_property_value(class_1,
			Class_description_gkbprop);
		if (class_description) {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Connection_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    object = 
			    create_connection_from_module_data(class_description,
			    object_and_fixups,do_loose_ends_p);
	    }
	    if (object) {
		set_evaluation_structure_slot(object_and_fixups_1,Qvalue,
			object);
		if (fixups) {
		    name = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			    (SI_Long)1L)));
		    value = Nil;
		  next_loop:
		    if (name >= ab_loop_bind_)
			goto end_loop;
		    value = evaluation_sequence_aref(fixups,FIX(name));
		    if ( !TRUEP(memq_function(FIX(name),list_constant_15))) {
			actual_value = lookup_xml_object(value);
			if ( !(value &&  !TRUEP(actual_value))) {
			    temp_1 = object;
			    temp_2 = FIX(name);
			    temp_3 = xml_object_text_of_p(value);
			    initialize_attribute_from_module_data(5,temp_1,
				    temp_2,actual_value,temp_3,
				    xml_object_unit(value));
			}
		    }
		    name = name + (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		}
		if ( !TRUEP(get_xml_fixups(object_and_fixups,
			QRDF_COL_RESOURCE,Nil))) {
		    initialize_items_count_new_value = 
			    FIXNUM_ADD1(Initialize_items_count);
		    Initialize_items_count = initialize_items_count_new_value;
		    update_initialize_xml_progress(0);
		}
	    }
	}
	if (fixups) {
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop_1:
	    if (name >= ab_loop_bind_)
		goto end_loop_1;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    create_and_initialize_all_connections_from_module_data(value,
		    do_loose_ends_p);
	    name = name + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	return VALUES_1(object);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if ( !TRUEP(object)) {
	    class_1 = get_xml_fixups(object_and_fixups,Qab_class,Nil);
	    if (class_1) {
		class_description = 
			lookup_global_or_kb_specific_property_value(class_1,
			Class_description_gkbprop);
		if (class_description) {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Connection_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    object = 
			    create_connection_from_module_data(class_description,
			    object_and_fixups,do_loose_ends_p);
	    }
	    if (object) {
		set_evaluation_structure_slot(object_and_fixups_1,Qvalue,
			object);
		if (fixups) {
		    gensymed_symbol_3 = fixups;
		    held_vector = Nil;
		    next_index = (SI_Long)1L;
		    length_1 = (SI_Long)0L;
		    name_1 = Nil;
		    attribute_value = Nil;
		    value = Nil;
		    held_vector = M_CAR(gensymed_symbol_3);
		    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		  next_loop_2:
		    if (next_index >= length_1)
			goto end_loop_2;
		    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,next_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),next_index & 
			    (SI_Long)1023L);
		    gensymed_symbol = next_index + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,gensymed_symbol + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(gensymed_symbol >>  
			    -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol & (SI_Long)1023L);
		    value = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index = next_index + (SI_Long)2L;
		    if ( !TRUEP(memq_function(name_1,list_constant_15))) {
			actual_value = lookup_xml_object(value);
			if ( !(value &&  !TRUEP(actual_value))) {
			    temp_1 = object;
			    temp_2 = name_1;
			    temp_3 = xml_object_text_of_p(value);
			    initialize_attribute_from_module_data(5,temp_1,
				    temp_2,actual_value,temp_3,
				    xml_object_unit(value));
			}
		    }
		    goto next_loop_2;
		  end_loop_2:;
		}
		if ( !TRUEP(get_xml_fixups(object_and_fixups,
			QRDF_COL_RESOURCE,Nil))) {
		    initialize_items_count_new_value = 
			    FIXNUM_ADD1(Initialize_items_count);
		    Initialize_items_count = initialize_items_count_new_value;
		    update_initialize_xml_progress(0);
		}
	    }
	}
	if (fixups) {
	    gensymed_symbol_3 = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol_3);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_3:
	    if (next_index >= length_1)
		goto end_loop_3;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    create_and_initialize_all_connections_from_module_data(value,
		    do_loose_ends_p);
	    goto next_loop_3;
	  end_loop_3:;
	}
	return VALUES_1(object);
    }
}

/* CREATE-CONNECTION-FROM-MODULE-DATA */
Object create_connection_from_module_data(class_description,
	    object_and_fixups,do_loose_ends_p)
    Object class_description, object_and_fixups, do_loose_ends_p;
{
    Object disable_stack_error, connection_input, connection_output;
    Object connection_style, connection_vertices, connection_is_directed;
    Object permit_transfer_of_permanent_items_p, end_1_item, side_1_qm;
    Object position_1_qm, portname_1_qm, make_new_stub_1_qm, end_2_item_qm;
    Object side_2_qm, position_2_qm, portname_2_qm, make_new_stub_2_qm, id;
    Object uuid_for_next_frame_qm, class_description_for_next_frame_qm, x2;
    Object gensymed_symbol, sub_class_bit_vector, connection;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(4);
    Object result;

    x_note_fn_call(136,305);
    disable_stack_error = T;
    PUSH_SPECIAL_WITH_SYMBOL(Disable_stack_error,Qdisable_stack_error,disable_stack_error,
	    3);
      connection_input = get_xml_object(get_xml_fixups(object_and_fixups,
	      Qconnection_input,Nil));
      connection_output = get_xml_object(get_xml_fixups(object_and_fixups,
	      Qconnection_output,Nil));
      connection_style = get_xml_object(get_xml_fixups(object_and_fixups,
	      Qconnection_style,Nil));
      connection_vertices = 
	      get_xml_object(get_xml_fixups(object_and_fixups,
	      Qconnection_vertices,Nil));
      connection_is_directed = 
	      get_xml_object(get_xml_fixups(object_and_fixups,
	      Qconnection_is_directed,Nil));
      permit_transfer_of_permanent_items_p = T;
      PUSH_SPECIAL_WITH_SYMBOL(Permit_transfer_of_permanent_items_p,Qpermit_transfer_of_permanent_items_p,permit_transfer_of_permanent_items_p,
	      2);
	end_1_item = connection_input ? estructure_slot(connection_input,
		Qitem,Nil) : Nil;
	side_1_qm = connection_input ? estructure_slot(connection_input,
		Qside,Nil) : Nil;
	position_1_qm = connection_input ? 
		estructure_slot(connection_input,Qposition,Nil) : Nil;
	portname_1_qm = connection_input ? 
		estructure_slot(connection_input,Qport_name,Nil) : Nil;
	make_new_stub_1_qm = T;
	end_2_item_qm = connection_output ? 
		estructure_slot(connection_output,Qitem,Nil) : Nil;
	side_2_qm = connection_output ? estructure_slot(connection_output,
		Qside,Nil) : Nil;
	position_2_qm = connection_output ? 
		estructure_slot(connection_output,Qposition,Nil) : Nil;
	portname_2_qm = connection_output ? 
		estructure_slot(connection_output,Qport_name,Nil) : Nil;
	make_new_stub_2_qm = T;
	id = get_xml_fixups(object_and_fixups,Qid,Nil);
	uuid_for_next_frame_qm = id ? get_uuid_from_module_data(id) : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Uuid_for_next_frame_qm,Quuid_for_next_frame_qm,uuid_for_next_frame_qm,
		1);
	  class_description_for_next_frame_qm = class_description;
	  PUSH_SPECIAL_WITH_SYMBOL(Class_description_for_next_frame_qm,Qclass_description_for_next_frame_qm,class_description_for_next_frame_qm,
		  0);
	    temp =  !TRUEP(end_1_item);
	    if (temp);
	    else {
		if (SIMPLE_VECTOR_P(end_1_item) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(end_1_item)) > 
			(SI_Long)2L &&  !EQ(ISVREF(end_1_item,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(end_1_item,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Loose_end_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    if (temp);
	    else
		temp =  !TRUEP(end_2_item_qm);
	    if (temp);
	    else {
		if (SIMPLE_VECTOR_P(end_2_item_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(end_2_item_qm)) > 
			(SI_Long)2L &&  !EQ(ISVREF(end_2_item_qm,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(end_2_item_qm,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Loose_end_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    connection = EQ(do_loose_ends_p, ! !temp ? T : Nil) ? 
		    execute_create_connection_stack_instruction_internal(ISVREF(class_description,
		    (SI_Long)1L),class_description,end_1_item,
		    make_new_stub_1_qm,side_1_qm,position_1_qm,
		    portname_1_qm,end_2_item_qm,make_new_stub_2_qm,
		    side_2_qm,position_2_qm,portname_2_qm,connection_style,
		    CONSP(connection_is_directed) && 
		    EQ(M_CDR(connection_is_directed),Qtruth_value) && 
		    CONSP(connection_is_directed) && 
		    EQ(M_CDR(connection_is_directed),Qtruth_value) && 
		    EQ(M_CAR(connection_is_directed),Truth) ? Qoutput : 
		    Nil,connection_vertices,Nil) : Nil;
	    if ( !TRUEP(connection))
		result = VALUES_1(Nil);
	    else if (text_string_p(connection)) {
		notify_user(1,connection);
		result = VALUES_1(Nil);
	    }
	    else {
		set_permanent_and_propagate(connection,Nil);
		result = VALUES_1(connection);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qitem_reference_parameters;  /* item-reference-parameters */

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object Qclear_text_history;  /* clear-text-history */

/* CREATE-ALL-SYSTEM-FRAMES-FROM-MODULE-DATA */
Object create_all_system_frames_from_module_data()
{
    Object object_and_fixups, object_and_fixups_vector, type, object, fixups;
    Object value, value_1, actual_value, x2, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector, substituted_instance;
    Object type_1, fixups_1, svref_arg_1, item_or_value, temp_1, held_vector;
    Object name_2, attribute_value, held_vector_1, name_3, svref_new_value;
    Object sequence, system_frame, elt_1, validated_elt, frame, bits, mask;
    Object ab_loop_list_, ab_loop_list__1;
    SI_Long name, ab_loop_bind_, name_1, ab_loop_bind__1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long svref_arg_2, next_index, length_1, next_index_1, length_2;
    char temp;

    x_note_fn_call(136,306);
    create_all_instances_from_module_data(Systemtables_fixups,Nil);
    create_all_instances_from_module_data(Systemtables_fixups,T);
    object_and_fixups = Systemtables_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups) && 
	    EQ(M_CDR(object_and_fixups),Qab_structure) ? 
	    M_CAR(object_and_fixups) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups;
    if (!(EQ(type,Qprimitive_value) || EQ(type,Qtext))) {
	if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (CONSP(object) && EQ(M_CDR(object),Qsequence)) {
		if (fixups) {
		    name = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			    (SI_Long)1L)));
		    value = Nil;
		  next_loop:
		    if (name >= ab_loop_bind_)
			goto end_loop;
		    value = evaluation_sequence_aref(fixups,FIX(name));
		    if ( !TRUEP(get_xml_object(value)) && 
			    EQ(get_xml_fixups(value,Qab_class,Nil),
			    Qitem_reference_parameters)) {
			if (fixups) {
			    name_1 = (SI_Long)0L;
			    ab_loop_bind__1 = 
				    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
				    (SI_Long)1L)));
			    value_1 = Nil;
			  next_loop_1:
			    if (name_1 >= ab_loop_bind__1)
				goto end_loop_1;
			    value_1 = evaluation_sequence_aref(fixups,
				    FIX(name_1));
			    actual_value = get_xml_object(value_1);
			    if (SIMPLE_VECTOR_P(actual_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(actual_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(actual_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(actual_value,(SI_Long)1L);
				gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? x2 : Qnil;
			    }
			    else
				gensymed_symbol = Nil;
			    if (gensymed_symbol) {
				gensymed_symbol_1 = 
					lookup_global_or_kb_specific_property_value(Qmiscellaneous_parameters,
					Class_description_gkbprop);
				if (gensymed_symbol_1) {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(gensymed_symbol_1,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
				    if (sub_class_vector_index < 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						{
					gensymed_symbol_2 = 
						UBYTE_8_ISAREF_1(sub_class_bit_vector,
						sub_class_vector_index);
					gensymed_symbol_3 = (SI_Long)1L;
					gensymed_symbol_4 = 
						superior_class_bit_number 
						& (SI_Long)7L;
					gensymed_symbol_3 = 
						gensymed_symbol_3 << 
						gensymed_symbol_4;
					gensymed_symbol_2 = 
						gensymed_symbol_2 & 
						gensymed_symbol_3;
					temp = (SI_Long)0L < gensymed_symbol_2;
				    }
				    else
					temp = TRUEP(Nil);
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				substituted_instance = actual_value;
				goto end_1;
			    }
			    name_1 = name_1 + (SI_Long)1L;
			    goto next_loop_1;
			  end_loop_1:
			    substituted_instance = Qnil;
			  end_1:;
			}
			else
			    substituted_instance = Nil;
			object_and_fixups = value;
			object_and_fixups_vector = 
				CONSP(object_and_fixups) && 
				EQ(M_CDR(object_and_fixups),Qab_structure) 
				? M_CAR(object_and_fixups) : Nil;
			type_1 = object_and_fixups_vector ? 
				structure_slot_1(object_and_fixups_vector,
				Qtype,Nil) : Qprimitive_value;
			if (object_and_fixups_vector)
			    structure_slot_1(object_and_fixups_vector,
				    Qunit,Nil);
			if (object_and_fixups_vector)
			    structure_slot_1(object_and_fixups_vector,
				    Qvalue,Nil);
			if (!(EQ(type_1,Qprimitive_value) || EQ(type_1,
				    Qtext))) {
			    if (EQ(type_1,Qsequence)) {
				fixups_1 = 
					structure_slot_1(object_and_fixups_vector,
					Qelements,Nil);
				set_evaluation_structure_slot(object_and_fixups,
					Qvalue,substituted_instance);
			    }
			    else {
				fixups_1 = 
					structure_slot_1(object_and_fixups_vector,
					Qattributes,Nil);
				set_evaluation_structure_slot(object_and_fixups,
					Qvalue,substituted_instance);
			    }
			}
			gensymed_symbol = M_CAR(object);
			gensymed_symbol_2 = name + (SI_Long)1L;
			if (FIXNUM_LE(ISVREF(M_CAR(object),(SI_Long)1L),
				Maximum_in_place_array_size)) {
			    svref_arg_1 = M_CAR(object);
			    svref_arg_2 = gensymed_symbol_2 + 
				    IFIX(Managed_array_index_offset);
			    item_or_value = substituted_instance;
			    if (SIMPLE_VECTOR_P(item_or_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_1 = temp ? 
				    get_reference_to_item(item_or_value) : 
				    item_or_value;
			    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
			}
			else {
			    svref_arg_1 = ISVREF(gensymed_symbol,
				    (gensymed_symbol_2 >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    svref_arg_2 = gensymed_symbol_2 & (SI_Long)1023L;
			    item_or_value = substituted_instance;
			    if (SIMPLE_VECTOR_P(item_or_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_1 = temp ? 
				    get_reference_to_item(item_or_value) : 
				    item_or_value;
			    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
			}
		    }
		    name = name + (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		}
	    }
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (CONSP(object) && EQ(M_CDR(object),Qsequence)) {
		if (fixups) {
		    gensymed_symbol = fixups;
		    held_vector = Nil;
		    next_index = (SI_Long)1L;
		    length_1 = (SI_Long)0L;
		    name_2 = Nil;
		    attribute_value = Nil;
		    value = Nil;
		    held_vector = M_CAR(gensymed_symbol);
		    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		  next_loop_2:
		    if (next_index >= length_1)
			goto end_loop_2;
		    name_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,next_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),next_index & 
			    (SI_Long)1023L);
		    gensymed_symbol_2 = next_index + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,gensymed_symbol_2 + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(gensymed_symbol_2 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol_2 & (SI_Long)1023L);
		    value = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index = next_index + (SI_Long)2L;
		    if ( !TRUEP(get_xml_object(value)) && 
			    EQ(get_xml_fixups(value,Qab_class,Nil),
			    Qitem_reference_parameters)) {
			if (fixups) {
			    gensymed_symbol = fixups;
			    held_vector_1 = Nil;
			    next_index_1 = (SI_Long)1L;
			    length_2 = (SI_Long)0L;
			    name_3 = Nil;
			    attribute_value = Nil;
			    value_1 = Nil;
			    held_vector_1 = M_CAR(gensymed_symbol);
			    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
			  next_loop_3:
			    if (next_index_1 >= length_2)
				goto end_loop_3;
			    name_3 = FIXNUM_LE(ISVREF(held_vector_1,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(held_vector_1,next_index_1 + 
				    IFIX(Managed_array_index_offset)) : 
				    ISVREF(ISVREF(held_vector_1,
				    (next_index_1 >>  -  - (SI_Long)10L) + 
				    (SI_Long)2L),next_index_1 & 
				    (SI_Long)1023L);
			    gensymed_symbol_2 = next_index_1 + (SI_Long)1L;
			    attribute_value = 
				    FIXNUM_LE(ISVREF(held_vector_1,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(held_vector_1,gensymed_symbol_2 
				    + IFIX(Managed_array_index_offset)) : 
				    ISVREF(ISVREF(held_vector_1,
				    (gensymed_symbol_2 >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    gensymed_symbol_2 & (SI_Long)1023L);
			    value_1 = 
				    validate_item_or_evaluation_value(attribute_value,
				    Nil,Nil);
			    next_index_1 = next_index_1 + (SI_Long)2L;
			    actual_value = get_xml_object(value_1);
			    if (SIMPLE_VECTOR_P(actual_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(actual_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(actual_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(actual_value,(SI_Long)1L);
				gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? x2 : Qnil;
			    }
			    else
				gensymed_symbol = Nil;
			    if (gensymed_symbol) {
				gensymed_symbol_1 = 
					lookup_global_or_kb_specific_property_value(Qmiscellaneous_parameters,
					Class_description_gkbprop);
				if (gensymed_symbol_1) {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(gensymed_symbol_1,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
				    if (sub_class_vector_index < 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						{
					gensymed_symbol_2 = 
						UBYTE_8_ISAREF_1(sub_class_bit_vector,
						sub_class_vector_index);
					gensymed_symbol_3 = (SI_Long)1L;
					gensymed_symbol_4 = 
						superior_class_bit_number 
						& (SI_Long)7L;
					gensymed_symbol_3 = 
						gensymed_symbol_3 << 
						gensymed_symbol_4;
					gensymed_symbol_2 = 
						gensymed_symbol_2 & 
						gensymed_symbol_3;
					temp = (SI_Long)0L < gensymed_symbol_2;
				    }
				    else
					temp = TRUEP(Nil);
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				substituted_instance = actual_value;
				goto end_2;
			    }
			    goto next_loop_3;
			  end_loop_3:
			    substituted_instance = Qnil;
			  end_2:;
			}
			else
			    substituted_instance = Nil;
			object_and_fixups = value;
			object_and_fixups_vector = 
				CONSP(object_and_fixups) && 
				EQ(M_CDR(object_and_fixups),Qab_structure) 
				? M_CAR(object_and_fixups) : Nil;
			type_1 = object_and_fixups_vector ? 
				structure_slot_1(object_and_fixups_vector,
				Qtype,Nil) : Qprimitive_value;
			if (object_and_fixups_vector)
			    structure_slot_1(object_and_fixups_vector,
				    Qunit,Nil);
			if (object_and_fixups_vector)
			    structure_slot_1(object_and_fixups_vector,
				    Qvalue,Nil);
			if (!(EQ(type_1,Qprimitive_value) || EQ(type_1,
				    Qtext))) {
			    if (EQ(type_1,Qsequence)) {
				fixups_1 = 
					structure_slot_1(object_and_fixups_vector,
					Qelements,Nil);
				set_evaluation_structure_slot(object_and_fixups,
					Qvalue,substituted_instance);
			    }
			    else {
				fixups_1 = 
					structure_slot_1(object_and_fixups_vector,
					Qattributes,Nil);
				set_evaluation_structure_slot(object_and_fixups,
					Qvalue,substituted_instance);
			    }
			}
			gensymed_symbol = M_CAR(object);
			gensymed_symbol_1 = FIXNUM_ADD1(name_2);
			if (FIXNUM_LE(ISVREF(M_CAR(object),(SI_Long)1L),
				Maximum_in_place_array_size)) {
			    svref_arg_1 = M_CAR(object);
			    temp_1 = FIXNUM_ADD(gensymed_symbol_1,
				    Managed_array_index_offset);
			    item_or_value = substituted_instance;
			    if (SIMPLE_VECTOR_P(item_or_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    svref_new_value = temp ? 
				    get_reference_to_item(item_or_value) : 
				    item_or_value;
			    SVREF(svref_arg_1,temp_1) = svref_new_value;
			}
			else {
			    svref_arg_1 = ISVREF(gensymed_symbol,
				    (IFIX(gensymed_symbol_1) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    svref_arg_2 = IFIX(gensymed_symbol_1) & 
				    (SI_Long)1023L;
			    item_or_value = substituted_instance;
			    if (SIMPLE_VECTOR_P(item_or_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_1 = temp ? 
				    get_reference_to_item(item_or_value) : 
				    item_or_value;
			    ISVREF(svref_arg_1,svref_arg_2) = temp_1;
			}
		    }
		    goto next_loop_2;
		  end_loop_2:;
		}
	    }
	}
    }
    initialize_all_instances_from_module_data(Systemtables_fixups);
    sequence = get_xml_object(Systemtables_fixups);
    if (sequence) {
	gensymed_symbol = sequence;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	system_frame = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_4:
	if (next_index >= length_1)
	    goto end_loop_4;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	system_frame = validated_elt;
	if (SIMPLE_VECTOR_P(system_frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(system_frame)) > 
		(SI_Long)2L &&  !EQ(ISVREF(system_frame,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(system_frame,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ?  !TRUEP(memq_function(system_frame,
		System_tables_read_for_this_module)) : TRUEP(Nil))
	    System_tables_read_for_this_module = 
		    slot_value_cons_1(system_frame,
		    System_tables_read_for_this_module);
	goto next_loop_4;
      end_loop_4:;
	set_up_modules_and_system_tables_a_list_after_reading();
	frame = get_saving_parameters(Current_g2_rdf_module);
	if (frame) {
	    bits = ISVREF(frame,(SI_Long)23L);
	    if (bits);
	    else
		bits = FIX((SI_Long)0L);
	    mask = Nil;
	    ab_loop_list_ = list_constant_16;
	    name_2 = Nil;
	    ab_loop_list__1 = list_constant_17;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    mask = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_5;
	    name_2 = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (EQ(name_2,T) || memq_function(name_2,
		    Most_recent_xml_checksum_differences))
		bits = FIXNUM_LOGIOR(mask,bits);
	    goto next_loop_5;
	  end_loop_5:
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qclear_text_history);
	    SVREF(frame,FIX((SI_Long)23L)) = bits;
	}
    }
    Systemtables_are_initialized_p = T;
    return VALUES_1(Systemtables_are_initialized_p);
}

/* CREATE-ALL-INSTANCES-FROM-MODULE-DATA */
Object create_all_instances_from_module_data(object_and_fixups,
	    resolve_references_p)
    Object object_and_fixups, resolve_references_p;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object temp, value, old_value, new_value, gensymed_symbol, svref_arg_1;
    Object item_or_value, x2, temp_2, sub_class_bit_vector, v_p;
    Object may_create_simulation_subtable_from_module_data_p, actual_value;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_3;
    Object entry_hash, held_vector, name_1, attribute_value, gensymed_symbol_4;
    Object svref_new_value;
    SI_Long name, ab_loop_bind_, gensymed_symbol_1, svref_arg_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind__1, next_index, length_1;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,307);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext)) {
	if (FIXNUMP(object) || object && SYMBOLP(object) || 
		SIMPLE_VECTOR_P(object))
	    return VALUES_1(object);
	else
	    return copy_if_evaluation_value_1(object);
    }
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	temp = EQ(type,Qbinary) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if (CONSP(object)) {
	    if (CONSP(object) && EQ(M_CDR(object),Qsequence)) {
		if (fixups) {
		    name = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			    (SI_Long)1L)));
		    value = Nil;
		  next_loop:
		    if (name >= ab_loop_bind_)
			goto end_loop;
		    value = evaluation_sequence_aref(fixups,FIX(name));
		    old_value = evaluation_sequence_aref(object,FIX(name));
		    new_value = 
			    create_all_instances_from_module_data(value,
			    resolve_references_p);
		    if (old_value) {
			if ( !(FIXNUMP(new_value) || SYMBOLP(new_value) || 
				SIMPLE_VECTOR_P(new_value)))
			    reclaim_if_evaluation_value_1(new_value);
		    }
		    else {
			gensymed_symbol = M_CAR(object);
			gensymed_symbol_1 = name + (SI_Long)1L;
			if (FIXNUM_LE(ISVREF(M_CAR(object),(SI_Long)1L),
				Maximum_in_place_array_size)) {
			    svref_arg_1 = M_CAR(object);
			    svref_arg_2 = gensymed_symbol_1 + 
				    IFIX(Managed_array_index_offset);
			    item_or_value = new_value;
			    if (SIMPLE_VECTOR_P(item_or_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    temp_2 = temp_1 ? 
				    get_reference_to_item(item_or_value) : 
				    item_or_value;
			    ISVREF(svref_arg_1,svref_arg_2) = temp_2;
			}
			else {
			    svref_arg_1 = ISVREF(gensymed_symbol,
				    (gensymed_symbol_1 >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
			    item_or_value = new_value;
			    if (SIMPLE_VECTOR_P(item_or_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    temp_2 = temp_1 ? 
				    get_reference_to_item(item_or_value) : 
				    item_or_value;
			    ISVREF(svref_arg_1,svref_arg_2) = temp_2;
			}
		    }
		    name = name + (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		}
		return copy_evaluation_sequence(object);
	    }
	    else if (CONSP(object) && EQ(M_CDR(object),Qab_structure)) {
		if (fixups) {
		    name = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			    (SI_Long)1L)));
		    value = Nil;
		  next_loop_1:
		    if (name >= ab_loop_bind_)
			goto end_loop_1;
		    value = evaluation_sequence_aref(fixups,FIX(name));
		    old_value = estructure_slot(object,FIX(name),Nil);
		    new_value = 
			    create_all_instances_from_module_data(value,
			    resolve_references_p);
		    if (old_value) {
			if ( !(FIXNUMP(new_value) || SYMBOLP(new_value) || 
				SIMPLE_VECTOR_P(new_value)))
			    reclaim_if_evaluation_value_1(new_value);
		    }
		    else
			set_evaluation_structure_slot(object,FIX(name),
				new_value);
		    name = name + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop_1:;
		}
		return copy_evaluation_structure(object);
	    }
	    else
		return VALUES_1(Qnil);
	}
	else {
	    object = create_instance_from_module_data(object_and_fixups,
		    resolve_references_p);
	    if (SIMPLE_VECTOR_P(object) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(object,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(object,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    v_p = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
		}
		else
		    v_p = Nil;
	    }
	    else
		v_p = Nil;
	    if (fixups) {
		name = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		value = Nil;
	      next_loop_2:
		if (name >= ab_loop_bind_)
		    goto end_loop_2;
		value = evaluation_sequence_aref(fixups,FIX(name));
		may_create_simulation_subtable_from_module_data_p = v_p && 
			EQ(FIX(name),Qsimulation_details) ? object : Nil;
		PUSH_SPECIAL_WITH_SYMBOL(May_create_simulation_subtable_from_module_data_p,Qmay_create_simulation_subtable_from_module_data_p,may_create_simulation_subtable_from_module_data_p,
			0);
		  actual_value = 
			  create_all_instances_from_module_data(value,
			  resolve_references_p);
		  gensymed_symbol = actual_value;
		  temp_1 = FIXNUMP(gensymed_symbol);
		  if (temp_1);
		  else
		      temp_1 = 
			      INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			      != (SI_Long)0L ? 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			      == (SI_Long)1L : TRUEP(Qnil);
		  if (temp_1);
		  else
		      temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			      (SI_Long)0L ? 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			      == (SI_Long)1L : TRUEP(Qnil);
		  if (temp_1);
		  else
		      temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) :
			       TRUEP(Qnil);
		  if (temp_1);
		  else
		      temp_1 = 
			      INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			      != (SI_Long)0L;
		  if (temp_1);
		  else if (CONSP(gensymed_symbol)) {
		      gensymed_symbol = M_CDR(gensymed_symbol);
		      temp_1 = EQ(gensymed_symbol,Qtruth_value);
		      if (temp_1);
		      else
			  temp_1 = EQ(gensymed_symbol,Qiteration_state);
		      if (temp_1);
		      else if (SYMBOLP(gensymed_symbol)) {
			  skip_list = CDR(Defined_evaluation_value_types);
			  key_value = gensymed_symbol;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(gensymed_symbol) & 
				  IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind__1 = bottom_level;
			next_loop_3:
			  if (level < ab_loop_bind__1)
			      goto end_loop_3;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_4:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_3 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_3,temp);
			  MVS_2(result,succ,marked);
			next_loop_5:
			  if ( !TRUEP(marked))
			      goto end_loop_4;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_3 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_3,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_5;
			end_loop_4:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_1;
			  goto next_loop_4;
			end_loop_5:
			end_1:
			  level = level - (SI_Long)1L;
			  goto next_loop_3;
			end_loop_3:;
			  temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				  key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? 
				  TRUEP(ISVREF(curr,(SI_Long)3L)) : 
				  TRUEP(Nil)) : TRUEP(Nil);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      reclaim_evaluation_value(actual_value);
		POP_SPECIAL();
		name = name + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
	    }
	    return VALUES_1(object);
	}
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	temp = EQ(type,Qbinary) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if (CONSP(object)) {
	    if (CONSP(object) && EQ(M_CDR(object),Qsequence)) {
		if (fixups) {
		    gensymed_symbol = fixups;
		    held_vector = Nil;
		    next_index = (SI_Long)1L;
		    length_1 = (SI_Long)0L;
		    name_1 = Nil;
		    attribute_value = Nil;
		    value = Nil;
		    held_vector = M_CAR(gensymed_symbol);
		    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		  next_loop_6:
		    if (next_index >= length_1)
			goto end_loop_6;
		    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,next_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),next_index & 
			    (SI_Long)1023L);
		    gensymed_symbol_1 = next_index + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,gensymed_symbol_1 + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol_1 & (SI_Long)1023L);
		    value = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index = next_index + (SI_Long)2L;
		    old_value = evaluation_sequence_aref(object,name_1);
		    new_value = 
			    create_all_instances_from_module_data(value,
			    resolve_references_p);
		    if (old_value) {
			if ( !(FIXNUMP(new_value) || SYMBOLP(new_value) || 
				SIMPLE_VECTOR_P(new_value)))
			    reclaim_if_evaluation_value_1(new_value);
		    }
		    else {
			gensymed_symbol = M_CAR(object);
			gensymed_symbol_4 = FIXNUM_ADD1(name_1);
			if (FIXNUM_LE(ISVREF(M_CAR(object),(SI_Long)1L),
				Maximum_in_place_array_size)) {
			    svref_arg_1 = M_CAR(object);
			    temp_2 = FIXNUM_ADD(gensymed_symbol_4,
				    Managed_array_index_offset);
			    item_or_value = new_value;
			    if (SIMPLE_VECTOR_P(item_or_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    svref_new_value = temp_1 ? 
				    get_reference_to_item(item_or_value) : 
				    item_or_value;
			    SVREF(svref_arg_1,temp_2) = svref_new_value;
			}
			else {
			    svref_arg_1 = ISVREF(gensymed_symbol,
				    (IFIX(gensymed_symbol_4) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    svref_arg_2 = IFIX(gensymed_symbol_4) & 
				    (SI_Long)1023L;
			    item_or_value = new_value;
			    if (SIMPLE_VECTOR_P(item_or_value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    temp_2 = temp_1 ? 
				    get_reference_to_item(item_or_value) : 
				    item_or_value;
			    ISVREF(svref_arg_1,svref_arg_2) = temp_2;
			}
		    }
		    goto next_loop_6;
		  end_loop_6:;
		}
		return copy_evaluation_sequence(object);
	    }
	    else if (CONSP(object) && EQ(M_CDR(object),Qab_structure)) {
		if (fixups) {
		    gensymed_symbol = fixups;
		    held_vector = Nil;
		    next_index = (SI_Long)1L;
		    length_1 = (SI_Long)0L;
		    name_1 = Nil;
		    attribute_value = Nil;
		    value = Nil;
		    held_vector = M_CAR(gensymed_symbol);
		    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		  next_loop_7:
		    if (next_index >= length_1)
			goto end_loop_7;
		    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,next_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),next_index & 
			    (SI_Long)1023L);
		    gensymed_symbol_1 = next_index + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,gensymed_symbol_1 + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol_1 & (SI_Long)1023L);
		    value = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index = next_index + (SI_Long)2L;
		    old_value = estructure_slot(object,name_1,Nil);
		    new_value = 
			    create_all_instances_from_module_data(value,
			    resolve_references_p);
		    if (old_value) {
			if ( !(FIXNUMP(new_value) || SYMBOLP(new_value) || 
				SIMPLE_VECTOR_P(new_value)))
			    reclaim_if_evaluation_value_1(new_value);
		    }
		    else
			set_evaluation_structure_slot(object,name_1,new_value);
		    goto next_loop_7;
		  end_loop_7:;
		}
		return copy_evaluation_structure(object);
	    }
	    else
		return VALUES_1(Qnil);
	}
	else {
	    object = create_instance_from_module_data(object_and_fixups,
		    resolve_references_p);
	    if (SIMPLE_VECTOR_P(object) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(object,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(object,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    v_p = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
		}
		else
		    v_p = Nil;
	    }
	    else
		v_p = Nil;
	    if (fixups) {
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		name_1 = Nil;
		attribute_value = Nil;
		value = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_8:
		if (next_index >= length_1)
		    goto end_loop_8;
		name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 
			& (SI_Long)1023L);
		value = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		may_create_simulation_subtable_from_module_data_p = v_p && 
			EQ(name_1,Qsimulation_details) ? object : Nil;
		PUSH_SPECIAL_WITH_SYMBOL(May_create_simulation_subtable_from_module_data_p,Qmay_create_simulation_subtable_from_module_data_p,may_create_simulation_subtable_from_module_data_p,
			0);
		  actual_value = 
			  create_all_instances_from_module_data(value,
			  resolve_references_p);
		  gensymed_symbol = actual_value;
		  temp_1 = FIXNUMP(gensymed_symbol);
		  if (temp_1);
		  else
		      temp_1 = 
			      INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			      != (SI_Long)0L ? 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			      == (SI_Long)1L : TRUEP(Qnil);
		  if (temp_1);
		  else
		      temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			      (SI_Long)0L ? 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			      == (SI_Long)1L : TRUEP(Qnil);
		  if (temp_1);
		  else
		      temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) :
			       TRUEP(Qnil);
		  if (temp_1);
		  else
		      temp_1 = 
			      INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			      != (SI_Long)0L;
		  if (temp_1);
		  else if (CONSP(gensymed_symbol)) {
		      gensymed_symbol = M_CDR(gensymed_symbol);
		      temp_1 = EQ(gensymed_symbol,Qtruth_value);
		      if (temp_1);
		      else
			  temp_1 = EQ(gensymed_symbol,Qiteration_state);
		      if (temp_1);
		      else if (SYMBOLP(gensymed_symbol)) {
			  skip_list = CDR(Defined_evaluation_value_types);
			  key_value = gensymed_symbol;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(gensymed_symbol) & 
				  IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_9:
			  if (level < ab_loop_bind_)
			      goto end_loop_9;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_10:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_3 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_3,temp);
			  MVS_2(result,succ,marked);
			next_loop_11:
			  if ( !TRUEP(marked))
			      goto end_loop_10;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_3 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_3,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_11;
			end_loop_10:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_2;
			  goto next_loop_10;
			end_loop_11:
			end_2:
			  level = level - (SI_Long)1L;
			  goto next_loop_9;
			end_loop_9:;
			  temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				  key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? 
				  TRUEP(ISVREF(curr,(SI_Long)3L)) : 
				  TRUEP(Nil)) : TRUEP(Nil);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      reclaim_evaluation_value(actual_value);
		POP_SPECIAL();
		goto next_loop_8;
	      end_loop_8:;
	    }
	    return VALUES_1(object);
	}
    }
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object list_constant_18;    /* # */

/* INITIALIZE-DEFINITION-FROM-MODULE-DATA */
Object initialize_definition_from_module_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, result_1, current_flag_state_qm, slot_description, new_cons;
    Object temp_1, temp_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object item_or_value_1, value, actual_value, temp_4, temp_5;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons, held_vector, name_1;
    Object attribute_value;
    SI_Long temp_3, gensymed_symbol_4, item_or_value, name, ab_loop_bind_;
    SI_Long next_index, length_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(136,308);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(Nil);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    result_1 = Nil;
	    current_flag_state_qm = Nil;
	    slot_description = 
		    get_slot_description_of_class_description_function(Qframe_status_and_notes,
		    ISVREF(object,(SI_Long)1L),Nil);
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_stack_change_conses_vector;
		temp_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,temp_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_stack_change_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_stack_change_cons_pool();
	    if (Nil)
		gensymed_symbol_1 = nconc2(stack_change_list_2(object,
			slot_description),stack_change_cons_1(Nil,Nil));
	    else {
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_1 = Available_stack_change_conses_vector;
		    temp_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_1,temp_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_stack_change_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_stack_change_cons_pool();
		M_CAR(gensymed_symbol_1) = object;
		M_CDR(gensymed_symbol_1) = slot_description;
		inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	    }
	    M_CAR(gensymed_symbol) = gensymed_symbol_1;
	    temp_1 = Stack_of_slot_value_changes;
	    M_CDR(gensymed_symbol) = temp_1;
	    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	    stack_of_slot_value_changes = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		    0);
	      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(object,
		      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	      if ( !TRUEP(current_flag_state_qm)) {
		  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(object,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = object;
		  gensymed_symbol_2 = Nil;
		  gensymed_symbol_3 = T;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
		  temp_3 = IFIX(ISVREF(object,(SI_Long)5L)) | 
			  (SI_Long)16777216L;
		  ISVREF(object,(SI_Long)5L) = FIX(temp_3);
	      }
	      if ( !TRUEP(Reading_ghost_definitions_p)) {
		  gensymed_symbol = allocate_managed_array(1,
			  FIX((SI_Long)6L + (SI_Long)1L));
		  gensymed_symbol_4 = (SI_Long)0L;
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      temp_3 = gensymed_symbol_4 + 
			      IFIX(Managed_array_index_offset);
		      ISVREF(gensymed_symbol,temp_3) = FIX((SI_Long)1L);
		  }
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_4 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L);
		      temp_3 = gensymed_symbol_4 & (SI_Long)1023L;
		      ISVREF(temp_1,temp_3) = FIX((SI_Long)1L);
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size))
		      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qx;
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      SVREF(temp_1,FIX((SI_Long)1L)) = Qx;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      item_or_value = (SI_Long)0L;
		      if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(FIX(item_or_value),(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_1 = temp ? 
			      get_reference_to_item(FIX(item_or_value)) : 
			      FIX(item_or_value);
		      SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
		  }
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      item_or_value = (SI_Long)0L;
		      if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(FIX(item_or_value),(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_2 = temp ? 
			      get_reference_to_item(FIX(item_or_value)) : 
			      FIX(item_or_value);
		      SVREF(temp_1,FIX((SI_Long)2L)) = temp_2;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size))
		      SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qy;
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      SVREF(temp_1,FIX((SI_Long)3L)) = Qy;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      item_or_value = (SI_Long)0L;
		      if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(FIX(item_or_value),(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_1 = temp ? 
			      get_reference_to_item(FIX(item_or_value)) : 
			      FIX(item_or_value);
		      SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
		  }
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      item_or_value = (SI_Long)0L;
		      if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(FIX(item_or_value),(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_2 = temp ? 
			      get_reference_to_item(FIX(item_or_value)) : 
			      FIX(item_or_value);
		      SVREF(temp_1,FIX((SI_Long)4L)) = temp_2;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size))
		      SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsuperior;
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      SVREF(temp_1,FIX((SI_Long)5L)) = Qsuperior;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      item_or_value_1 = Kb_window_for_initializing_definitions;
		      if (SIMPLE_VECTOR_P(item_or_value_1) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) 
			      > (SI_Long)2L &&  !EQ(ISVREF(item_or_value_1,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(item_or_value_1,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_1 = temp ? 
			      get_reference_to_item(item_or_value_1) : 
			      item_or_value_1;
		      SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
		  }
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      item_or_value_1 = Kb_window_for_initializing_definitions;
		      if (SIMPLE_VECTOR_P(item_or_value_1) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) 
			      > (SI_Long)2L &&  !EQ(ISVREF(item_or_value_1,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(item_or_value_1,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_2 = temp ? 
			      get_reference_to_item(item_or_value_1) : 
			      item_or_value_1;
		      SVREF(temp_1,FIX((SI_Long)6L)) = temp_2;
		  }
		  value = eval_cons_1(gensymed_symbol,Qab_structure);
		  initialize_attribute_from_module_data(4,object,
			  Qposition_in_workspace,value,Nil);
		  reclaim_evaluation_value(value);
	      }
	      if (fixups) {
		  name = (SI_Long)0L;
		  ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			  (SI_Long)1L)));
		  value = Nil;
		next_loop:
		  if (name >= ab_loop_bind_)
		      goto end_loop;
		  value = evaluation_sequence_aref(fixups,FIX(name));
		  actual_value = lookup_xml_object(value);
		  if ( !TRUEP(memq_function(FIX(name),list_constant_18))) {
		      temp_4 = FIX(name);
		      temp_5 = xml_object_text_of_p(value);
		      initialize_attribute_from_module_data(5,object,
			      temp_4,actual_value,temp_5,
			      xml_object_unit(value));
		  }
		  name = name + (SI_Long)1L;
		  goto next_loop;
		end_loop:;
	      }
	      result_1 = initialize_attribute_from_module_data(3,object,
		      Qab_class_name,
		      get_xml_object(get_xml_fixups(object_and_fixups,
		      Qab_class_name,Nil)));
	      if ( !TRUEP(current_flag_state_qm)) {
		  temp_3 = IFIX(ISVREF(object,(SI_Long)5L)) &  
			  ~(SI_Long)16777216L;
		  ISVREF(object,(SI_Long)5L) = FIX(temp_3);
		  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(object,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = object;
		  gensymed_symbol_2 = T;
		  gensymed_symbol_3 = Nil;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
	      }
	      temp = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	      if (temp);
	      else if (M_CDR(Stack_of_slot_value_changes)) {
		  frame_and_slot_or_atom = Nil;
		  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		  ab_loop_it_ = Nil;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (ATOM(frame_and_slot_or_atom))
		      goto end_loop_1;
		  temp = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
		  if (temp);
		  else {
		      temp_4 = M_CDR(frame_and_slot_or_atom);
		      temp = CONSP(temp_4) ? EQ(slot_description,
			      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		  }
		  ab_loop_it_ = temp ? (EQ(object,
			  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		  if (ab_loop_it_) {
		      temp = TRUEP(ab_loop_it_);
		      goto end_1;
		  }
		  goto next_loop_1;
		end_loop_1:
		  temp = TRUEP(Qnil);
		end_1:;
	      }
	      else
		  temp = TRUEP(Nil);
	      if ( !temp)
		  update_all_representations_of_slot(object,
			  slot_description,Nil,Nil);
	      if (ISVREF(slot_description,(SI_Long)14L))
		  update_frame_name_references(object);
	      stack_change_pop_store = Nil;
	      cons_1 = Stack_of_slot_value_changes;
	      if (cons_1) {
		  stack_change_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qstack_change);
		  if (ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_1 = 
			      ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_1) = cons_1;
		      temp_1 = Available_stack_change_conses_tail_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = cons_1;
		  }
		  else {
		      temp_1 = Available_stack_change_conses_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = cons_1;
		      temp_1 = Available_stack_change_conses_tail_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Stack_of_slot_value_changes = next_cons;
	      reclaim_stack_change_tree_1(stack_change_pop_store);
	      if (Stack_of_slot_value_changes) {
		  temp_4 = M_CAR(Stack_of_slot_value_changes);
		  temp = ATOM(temp_4);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp ?  
		      !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
		      : TRUEP(Nil))
		  do_deferred_updates_to_representations_in_tables();
	    POP_SPECIAL();
	    return VALUES_1(result_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    result_1 = Nil;
	    current_flag_state_qm = Nil;
	    slot_description = 
		    get_slot_description_of_class_description_function(Qframe_status_and_notes,
		    ISVREF(object,(SI_Long)1L),Nil);
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_stack_change_conses_vector;
		temp_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,temp_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_stack_change_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_stack_change_cons_pool();
	    if (Nil)
		gensymed_symbol_1 = nconc2(stack_change_list_2(object,
			slot_description),stack_change_cons_1(Nil,Nil));
	    else {
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_1 = Available_stack_change_conses_vector;
		    temp_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_1,temp_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_stack_change_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_stack_change_cons_pool();
		M_CAR(gensymed_symbol_1) = object;
		M_CDR(gensymed_symbol_1) = slot_description;
		inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	    }
	    M_CAR(gensymed_symbol) = gensymed_symbol_1;
	    temp_1 = Stack_of_slot_value_changes;
	    M_CDR(gensymed_symbol) = temp_1;
	    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	    stack_of_slot_value_changes = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		    0);
	      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(object,
		      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	      if ( !TRUEP(current_flag_state_qm)) {
		  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(object,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = object;
		  gensymed_symbol_2 = Nil;
		  gensymed_symbol_3 = T;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
		  temp_3 = IFIX(ISVREF(object,(SI_Long)5L)) | 
			  (SI_Long)16777216L;
		  ISVREF(object,(SI_Long)5L) = FIX(temp_3);
	      }
	      if ( !TRUEP(Reading_ghost_definitions_p)) {
		  gensymed_symbol = allocate_managed_array(1,
			  FIX((SI_Long)6L + (SI_Long)1L));
		  gensymed_symbol_4 = (SI_Long)0L;
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      temp_3 = gensymed_symbol_4 + 
			      IFIX(Managed_array_index_offset);
		      ISVREF(gensymed_symbol,temp_3) = FIX((SI_Long)1L);
		  }
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_4 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L);
		      temp_3 = gensymed_symbol_4 & (SI_Long)1023L;
		      ISVREF(temp_1,temp_3) = FIX((SI_Long)1L);
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size))
		      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qx;
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      SVREF(temp_1,FIX((SI_Long)1L)) = Qx;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      item_or_value = (SI_Long)0L;
		      if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(FIX(item_or_value),(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_1 = temp ? 
			      get_reference_to_item(FIX(item_or_value)) : 
			      FIX(item_or_value);
		      SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
		  }
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      item_or_value = (SI_Long)0L;
		      if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(FIX(item_or_value),(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_2 = temp ? 
			      get_reference_to_item(FIX(item_or_value)) : 
			      FIX(item_or_value);
		      SVREF(temp_1,FIX((SI_Long)2L)) = temp_2;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size))
		      SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qy;
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      SVREF(temp_1,FIX((SI_Long)3L)) = Qy;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      item_or_value = (SI_Long)0L;
		      if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(FIX(item_or_value),(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_1 = temp ? 
			      get_reference_to_item(FIX(item_or_value)) : 
			      FIX(item_or_value);
		      SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
		  }
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      item_or_value = (SI_Long)0L;
		      if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(FIX(item_or_value),(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_2 = temp ? 
			      get_reference_to_item(FIX(item_or_value)) : 
			      FIX(item_or_value);
		      SVREF(temp_1,FIX((SI_Long)4L)) = temp_2;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size))
		      SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsuperior;
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      SVREF(temp_1,FIX((SI_Long)5L)) = Qsuperior;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      item_or_value_1 = Kb_window_for_initializing_definitions;
		      if (SIMPLE_VECTOR_P(item_or_value_1) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) 
			      > (SI_Long)2L &&  !EQ(ISVREF(item_or_value_1,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(item_or_value_1,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_1 = temp ? 
			      get_reference_to_item(item_or_value_1) : 
			      item_or_value_1;
		      SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
		  }
		  else {
		      temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		      item_or_value_1 = Kb_window_for_initializing_definitions;
		      if (SIMPLE_VECTOR_P(item_or_value_1) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) 
			      > (SI_Long)2L &&  !EQ(ISVREF(item_or_value_1,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(item_or_value_1,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp_2 = temp ? 
			      get_reference_to_item(item_or_value_1) : 
			      item_or_value_1;
		      SVREF(temp_1,FIX((SI_Long)6L)) = temp_2;
		  }
		  value = eval_cons_1(gensymed_symbol,Qab_structure);
		  initialize_attribute_from_module_data(4,object,
			  Qposition_in_workspace,value,Nil);
		  reclaim_evaluation_value(value);
	      }
	      if (fixups) {
		  gensymed_symbol = fixups;
		  held_vector = Nil;
		  next_index = (SI_Long)1L;
		  length_1 = (SI_Long)0L;
		  name_1 = Nil;
		  attribute_value = Nil;
		  value = Nil;
		  held_vector = M_CAR(gensymed_symbol);
		  length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		next_loop_2:
		  if (next_index >= length_1)
		      goto end_loop_2;
		  name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			  Maximum_in_place_array_size) ? 
			  ISVREF(held_vector,next_index + 
			  IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),next_index & 
			  (SI_Long)1023L);
		  gensymed_symbol_4 = next_index + (SI_Long)1L;
		  attribute_value = FIXNUM_LE(ISVREF(held_vector,
			  (SI_Long)1L),Maximum_in_place_array_size) ? 
			  ISVREF(held_vector,gensymed_symbol_4 + 
			  IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(held_vector,(gensymed_symbol_4 >>  
			  -  - (SI_Long)10L) + (SI_Long)2L),
			  gensymed_symbol_4 & (SI_Long)1023L);
		  value = 
			  validate_item_or_evaluation_value(attribute_value,
			  Nil,Nil);
		  next_index = next_index + (SI_Long)2L;
		  actual_value = lookup_xml_object(value);
		  if ( !TRUEP(memq_function(name_1,list_constant_18))) {
		      temp_4 = name_1;
		      temp_5 = xml_object_text_of_p(value);
		      initialize_attribute_from_module_data(5,object,
			      temp_4,actual_value,temp_5,
			      xml_object_unit(value));
		  }
		  goto next_loop_2;
		end_loop_2:;
	      }
	      result_1 = initialize_attribute_from_module_data(3,object,
		      Qab_class_name,
		      get_xml_object(get_xml_fixups(object_and_fixups,
		      Qab_class_name,Nil)));
	      if ( !TRUEP(current_flag_state_qm)) {
		  temp_3 = IFIX(ISVREF(object,(SI_Long)5L)) &  
			  ~(SI_Long)16777216L;
		  ISVREF(object,(SI_Long)5L) = FIX(temp_3);
		  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(object,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = object;
		  gensymed_symbol_2 = T;
		  gensymed_symbol_3 = Nil;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
	      }
	      temp = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	      if (temp);
	      else if (M_CDR(Stack_of_slot_value_changes)) {
		  frame_and_slot_or_atom = Nil;
		  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		  ab_loop_it_ = Nil;
		next_loop_3:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_3;
		  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (ATOM(frame_and_slot_or_atom))
		      goto end_loop_3;
		  temp = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
		  if (temp);
		  else {
		      temp_4 = M_CDR(frame_and_slot_or_atom);
		      temp = CONSP(temp_4) ? EQ(slot_description,
			      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		  }
		  ab_loop_it_ = temp ? (EQ(object,
			  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		  if (ab_loop_it_) {
		      temp = TRUEP(ab_loop_it_);
		      goto end_2;
		  }
		  goto next_loop_3;
		end_loop_3:
		  temp = TRUEP(Qnil);
		end_2:;
	      }
	      else
		  temp = TRUEP(Nil);
	      if ( !temp)
		  update_all_representations_of_slot(object,
			  slot_description,Nil,Nil);
	      if (ISVREF(slot_description,(SI_Long)14L))
		  update_frame_name_references(object);
	      stack_change_pop_store = Nil;
	      cons_1 = Stack_of_slot_value_changes;
	      if (cons_1) {
		  stack_change_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qstack_change);
		  if (ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_1 = 
			      ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_1) = cons_1;
		      temp_1 = Available_stack_change_conses_tail_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = cons_1;
		  }
		  else {
		      temp_1 = Available_stack_change_conses_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = cons_1;
		      temp_1 = Available_stack_change_conses_tail_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Stack_of_slot_value_changes = next_cons;
	      reclaim_stack_change_tree_1(stack_change_pop_store);
	      if (Stack_of_slot_value_changes) {
		  temp_4 = M_CAR(Stack_of_slot_value_changes);
		  temp = ATOM(temp_4);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp ?  
		      !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
		      : TRUEP(Nil))
		  do_deferred_updates_to_representations_in_tables();
	    POP_SPECIAL();
	    return VALUES_1(result_1);
	}
	else
	    return VALUES_1(Nil);
    }
}

Object Relation_attributes = UNBOUND;

/* INITIALIZE-ALL-RELATIONS-FROM-MODULE-DATA */
Object initialize_all_relations_from_module_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, gensymed_symbol, sub_class_bit_vector, name, ab_loop_list_;
    Object value, actual_value, temp_1, temp_2, temp_3, held_vector;
    Object attribute_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, name_1;
    SI_Long ab_loop_bind_, next_index, length_1;
    char temp;

    x_note_fn_call(136,309);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(Nil);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Relation_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = Nil;
	    ab_loop_list_ = Relation_attributes;
	    value = Nil;
	    actual_value = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    value = get_xml_fixups(object_and_fixups,name,Nil);
	    actual_value = initialize_all_instances_from_module_data(value);
	    if (actual_value) {
		temp_1 = name;
		temp_2 = actual_value;
		temp_3 = xml_object_text_of_p(value);
		initialize_attribute_from_module_data(5,object,temp_1,
			temp_2,temp_3,xml_object_unit(value));
	    }
	    goto next_loop;
	  end_loop:;
	}
	if (fixups) {
	    name_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop_1:
	    if (name_1 >= ab_loop_bind_)
		goto end_loop_1;
	    value = evaluation_sequence_aref(fixups,FIX(name_1));
	    initialize_all_relations_from_module_data(value);
	    name_1 = name_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Relation_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = Nil;
	    ab_loop_list_ = Relation_attributes;
	    value = Nil;
	    actual_value = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    value = get_xml_fixups(object_and_fixups,name,Nil);
	    actual_value = initialize_all_instances_from_module_data(value);
	    if (actual_value) {
		temp_1 = name;
		temp_2 = actual_value;
		temp_3 = xml_object_text_of_p(value);
		initialize_attribute_from_module_data(5,object,temp_1,
			temp_2,temp_3,xml_object_unit(value));
	    }
	    goto next_loop_2;
	  end_loop_2:;
	}
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_3:
	    if (next_index >= length_1)
		goto end_loop_3;
	    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    initialize_all_relations_from_module_data(value);
	    goto next_loop_3;
	  end_loop_3:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

Object Units_of_measure_declaration_attributes = UNBOUND;

static Object Qunits_of_measure_declaration;  /* units-of-measure-declaration */

/* INITIALIZE-ALL-UNITS-OF-MEASURE-DECLARATIONS-FROM-MODULE-DATA */
Object initialize_all_units_of_measure_declarations_from_module_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, fixups, object;
    Object name, ab_loop_list_, value, actual_value, temp, temp_1, temp_2;
    Object gensymed_symbol, held_vector, attribute_value;
    SI_Long name_1, ab_loop_bind_, next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(136,310);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qvalue,Nil);
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(Nil);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (EQ(get_xml_fixups(object_and_fixups,Qab_class,Nil),
		Qunits_of_measure_declaration)) {
	    object = create_instance_from_module_data(object_and_fixups,Nil);
	    name = Nil;
	    ab_loop_list_ = Units_of_measure_declaration_attributes;
	    value = Nil;
	    actual_value = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    value = get_xml_fixups(object_and_fixups,name,Nil);
	    actual_value = initialize_all_instances_from_module_data(value);
	    if (actual_value) {
		temp = name;
		temp_1 = actual_value;
		temp_2 = xml_object_text_of_p(value);
		initialize_attribute_from_module_data(5,object,temp,temp_1,
			temp_2,xml_object_unit(value));
	    }
	    goto next_loop;
	  end_loop:;
	}
	if (fixups) {
	    name_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop_1:
	    if (name_1 >= ab_loop_bind_)
		goto end_loop_1;
	    value = evaluation_sequence_aref(fixups,FIX(name_1));
	    initialize_all_units_of_measure_declarations_from_module_data(value);
	    name_1 = name_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (EQ(get_xml_fixups(object_and_fixups,Qab_class,Nil),
		Qunits_of_measure_declaration)) {
	    object = create_instance_from_module_data(object_and_fixups,Nil);
	    name = Nil;
	    ab_loop_list_ = Units_of_measure_declaration_attributes;
	    value = Nil;
	    actual_value = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    value = get_xml_fixups(object_and_fixups,name,Nil);
	    actual_value = initialize_all_instances_from_module_data(value);
	    if (actual_value) {
		temp = name;
		temp_1 = actual_value;
		temp_2 = xml_object_text_of_p(value);
		initialize_attribute_from_module_data(5,object,temp,temp_1,
			temp_2,xml_object_unit(value));
	    }
	    goto next_loop_2;
	  end_loop_2:;
	}
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_3:
	    if (next_index >= length_1)
		goto end_loop_3;
	    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    initialize_all_units_of_measure_declarations_from_module_data(value);
	    goto next_loop_3;
	  end_loop_3:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object list_constant_19;    /* # */

/* RE-INITIALIZE-ALL-GENERIC-SIMULATION-FORMULAS-FROM-MODULA-DATA */
Object re_initialize_all_generic_simulation_formulas_from_modula_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, gensymed_symbol, sub_class_bit_vector, name, ab_loop_list_;
    Object value, actual_value, temp_1, temp_2, temp_3, held_vector;
    Object attribute_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, name_1;
    SI_Long ab_loop_bind_, next_index, length_1;
    char temp;

    x_note_fn_call(136,311);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(Nil);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Generic_simulation_formula_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = Nil;
	    ab_loop_list_ = list_constant_19;
	    value = Nil;
	    actual_value = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    value = get_xml_fixups(object_and_fixups,name,Nil);
	    actual_value = get_xml_object(value);
	    if (actual_value) {
		temp_1 = name;
		temp_2 = actual_value;
		temp_3 = xml_object_text_of_p(value);
		initialize_attribute_from_module_data(5,object,temp_1,
			temp_2,temp_3,xml_object_unit(value));
	    }
	    goto next_loop;
	  end_loop:;
	}
	if (fixups) {
	    name_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop_1:
	    if (name_1 >= ab_loop_bind_)
		goto end_loop_1;
	    value = evaluation_sequence_aref(fixups,FIX(name_1));
	    re_initialize_all_generic_simulation_formulas_from_modula_data(value);
	    name_1 = name_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Generic_simulation_formula_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = Nil;
	    ab_loop_list_ = list_constant_19;
	    value = Nil;
	    actual_value = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    value = get_xml_fixups(object_and_fixups,name,Nil);
	    actual_value = get_xml_object(value);
	    if (actual_value) {
		temp_1 = name;
		temp_2 = actual_value;
		temp_3 = xml_object_text_of_p(value);
		initialize_attribute_from_module_data(5,object,temp_1,
			temp_2,temp_3,xml_object_unit(value));
	    }
	    goto next_loop_2;
	  end_loop_2:;
	}
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_3:
	    if (next_index >= length_1)
		goto end_loop_3;
	    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    re_initialize_all_generic_simulation_formulas_from_modula_data(value);
	    goto next_loop_3;
	  end_loop_3:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qnon_action_button;  /* non-action-button */

/* UPDATE-ALL-BUTTONS-FROM-MODULE-DATA */
Object update_all_buttons_from_module_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, value;
    Object held_vector, name_1, attribute_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, name;
    SI_Long ab_loop_bind_, next_index, length_1;
    char temp;

    x_note_fn_call(136,312);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(Nil);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qnon_action_button,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    update_button(object);
	if (fixups) {
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop:
	    if (name >= ab_loop_bind_)
		goto end_loop;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    update_all_buttons_from_module_data(value);
	    name = name + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qnon_action_button,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    update_button(object);
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_2 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_2 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    update_all_buttons_from_module_data(value);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* FIX-CLEAR-TEXT-ITEM-LAYERING-FROM-MODULE-DATA */
Object fix_clear_text_item_layering_from_module_data(object_and_fixups)
    Object object_and_fixups;
{
    x_note_fn_call(136,313);
    fix_clear_text_item_layering_from_module_data_1(object_and_fixups);
    return fix_clear_text_item_layering_from_module_data_2(object_and_fixups);
}

static Object list_constant_20;    /* # */

/* FIX-CLEAR-TEXT-ITEM-LAYERING-FROM-MODULE-DATA-1 */
Object fix_clear_text_item_layering_from_module_data_1(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, gensymed_symbol, sub_class_bit_vector, name, ab_loop_list_;
    Object fixups_1, actual_value, temp_1, temp_2, temp_3, value, held_vector;
    Object attribute_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, name_1;
    SI_Long ab_loop_bind_, next_index, length_1;
    char temp;

    x_note_fn_call(136,314);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(Nil);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (SIMPLE_VECTOR_P(object) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(object,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(object,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = Nil;
	    ab_loop_list_ = list_constant_20;
	    fixups_1 = Nil;
	    actual_value = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    fixups_1 = get_xml_fixups(object_and_fixups,name,Nil);
	    actual_value = lookup_xml_object(fixups_1);
	    if (actual_value) {
		temp_1 = name;
		temp_2 = actual_value;
		temp_3 = xml_object_text_of_p(fixups_1);
		initialize_attribute_from_module_data(5,object,temp_1,
			temp_2,temp_3,xml_object_unit(fixups_1));
	    }
	    goto next_loop;
	  end_loop:;
	}
	if (fixups) {
	    name_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop_1:
	    if (name_1 >= ab_loop_bind_)
		goto end_loop_1;
	    value = evaluation_sequence_aref(fixups,FIX(name_1));
	    fix_clear_text_item_layering_from_module_data_1(value);
	    name_1 = name_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (SIMPLE_VECTOR_P(object) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(object,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(object,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = Nil;
	    ab_loop_list_ = list_constant_20;
	    fixups_1 = Nil;
	    actual_value = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    fixups_1 = get_xml_fixups(object_and_fixups,name,Nil);
	    actual_value = lookup_xml_object(fixups_1);
	    if (actual_value) {
		temp_1 = name;
		temp_2 = actual_value;
		temp_3 = xml_object_text_of_p(fixups_1);
		initialize_attribute_from_module_data(5,object,temp_1,
			temp_2,temp_3,xml_object_unit(fixups_1));
	    }
	    goto next_loop_2;
	  end_loop_2:;
	}
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_3:
	    if (next_index >= length_1)
		goto end_loop_3;
	    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    fix_clear_text_item_layering_from_module_data_1(value);
	    goto next_loop_3;
	  end_loop_3:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* FIX-CLEAR-TEXT-ITEM-LAYERING-FROM-MODULE-DATA-2 */
Object fix_clear_text_item_layering_from_module_data_2(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, gensymed_symbol, sub_class_bit_vector, value, held_vector;
    Object name_1, attribute_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, name;
    SI_Long ab_loop_bind_, next_index, length_1;
    char temp;

    x_note_fn_call(136,315);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(Nil);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    fix_clear_text_item_layering(object);
	if (fixups) {
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop:
	    if (name >= ab_loop_bind_)
		goto end_loop;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    fix_clear_text_item_layering_from_module_data_2(value);
	    name = name + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    fix_clear_text_item_layering(object);
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    fix_clear_text_item_layering_from_module_data_2(value);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* GET-AND-CLEAR-ITEM-LAYERING-INFO-FOR-CLEAR-TEXT */
Object get_and_clear_item_layering_info_for_clear_text(kb_workspace)
    Object kb_workspace;
{
    Object info;

    x_note_fn_call(136,316);
    info = get_lookup_slot_value_given_default(kb_workspace,
	    Qlayering_information_for_clear_text,Nil);
    if (info) {
	set_non_savable_lookup_slot_value(kb_workspace,
		Qlayering_information_for_clear_text,Nil);
	return transform_item_layering_info_into_a_list(kb_workspace,info);
    }
    else
	return VALUES_1(Nil);
}

static Object Qab_gensym;          /* gensym */

static Object Qlayer_position_of_block;  /* layer-position-of-block */

/* TRANSFORM-ITEM-LAYERING-INFO-INTO-A-LIST */
Object transform_item_layering_info_into_a_list(kb_workspace,info)
    Object kb_workspace, info;
{
    Object e, after, before, collectp, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensym_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2, ab_loop_list_, ab_loop_desetq_, possible_top_item;
    Object higher_item, top_item, item, next_item, items_from_top_to_bottom;

    x_note_fn_call(136,317);
    e = Nil;
    after = Nil;
    before = Nil;
    collectp = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(info))
	goto end_loop;
    gensym_pop_store = Nil;
    cons_1 = info;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    info = next_cons;
    e = gensym_pop_store;
    after = CAR(e);
    before = CDR(e);
    collectp = EQ(kb_workspace,get_workspace_if_any_for_block(after)) ? 
	    (EQ(kb_workspace,get_workspace_if_any_for_block(before)) ? T : 
	    Nil) : Qnil;
    if ( !TRUEP(collectp))
	reclaim_gensym_cons_1(e);
    if (collectp) {
	ab_loopvar__2 = gensym_cons_1(e,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    info = ab_loopvar_;
    goto end_1;
    info = Qnil;
  end_1:;
    after = Nil;
    before = Nil;
    ab_loop_list_ = info;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    after = CAR(ab_loop_desetq_);
    before = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_non_savable_lookup_slot_value(after,Qlayer_position_of_block,Nil);
    set_non_savable_lookup_slot_value(before,Qlayer_position_of_block,Nil);
    goto next_loop_1;
  end_loop_1:;
    after = Nil;
    before = Nil;
    ab_loop_list_ = info;
    ab_loop_desetq_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    after = CAR(ab_loop_desetq_);
    before = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_non_savable_lookup_slot_value(before,Qlayer_position_of_block,after);
    goto next_loop_2;
  end_loop_2:;
    possible_top_item = CAAR(info);
    higher_item = Nil;
  next_loop_3:
    higher_item = get_lookup_slot_value_given_default(possible_top_item,
	    Qlayer_position_of_block,FIX((SI_Long)0L));
    if ( !TRUEP(higher_item))
	goto end_loop_3;
    set_non_savable_lookup_slot_value(possible_top_item,
	    Qlayer_position_of_block,Nil);
    possible_top_item = higher_item;
    goto next_loop_3;
  end_loop_3:
    top_item = possible_top_item;
    goto end_2;
    top_item = Qnil;
  end_2:;
    after = Nil;
    before = Nil;
    ab_loop_list_ = info;
    ab_loop_desetq_ = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    after = CAR(ab_loop_desetq_);
    before = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_non_savable_lookup_slot_value(before,Qlayer_position_of_block,Nil);
    set_non_savable_lookup_slot_value(after,Qlayer_position_of_block,Nil);
    goto next_loop_4;
  end_loop_4:;
    after = Nil;
    before = Nil;
    ab_loop_list_ = info;
    ab_loop_desetq_ = Nil;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    after = CAR(ab_loop_desetq_);
    before = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_non_savable_lookup_slot_value(after,Qlayer_position_of_block,before);
    goto next_loop_5;
  end_loop_5:;
    reclaim_gensym_tree_1(info);
    item = top_item;
    next_item = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_6:
    if ( !TRUEP(item))
	goto end_loop_6;
    next_item = get_lookup_slot_value_given_default(item,
	    Qlayer_position_of_block,FIX((SI_Long)0L));
    set_non_savable_lookup_slot_value(item,Qlayer_position_of_block,Nil);
    ab_loopvar__2 = gensym_cons_1(item,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    item = next_item;
    goto next_loop_6;
  end_loop_6:
    items_from_top_to_bottom = ab_loopvar_;
    goto end_3;
    items_from_top_to_bottom = Qnil;
  end_3:;
    recompute_layer_positions(kb_workspace);
    return VALUES_1(items_from_top_to_bottom);
}

/* FIX-CLEAR-TEXT-ITEM-LAYERING */
Object fix_clear_text_item_layering(kb_workspace)
    Object kb_workspace;
{
    Object info;

    x_note_fn_call(136,318);
    info = get_and_clear_item_layering_info_for_clear_text(kb_workspace);
    if (info)
	set_clear_item_layering_info_for_clear_text(kb_workspace,info);
    return VALUES_1(Nil);
}

/* SET-CLEAR-ITEM-LAYERING-INFO-FOR-CLEAR-TEXT */
Object set_clear_item_layering_info_for_clear_text(kb_workspace,
	    items_from_top_to_bottom)
    Object kb_workspace, items_from_top_to_bottom;
{
    Object item, ab_loop_list_;

    x_note_fn_call(136,319);
    item = Nil;
    ab_loop_list_ = items_from_top_to_bottom;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    lower_block_to_bottom(item);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(items_from_top_to_bottom);
    return VALUES_1(Nil);
}

static Object list_constant_21;    /* # */

static Object list_constant_22;    /* # */

static Object list_constant_23;    /* # */

static Object Qoptions;            /* options */

static Object list_constant_24;    /* # */

static Object list_constant_25;    /* # */

/* INITIALIZE-ALL-INSTANCES-FROM-MODULE-DATA */
Object initialize_all_instances_from_module_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, value, temp_1, reading_ghost_definitions_p;
    Object sub_class_bit_vector, class_definition_p, text_box_p, rule_p;
    Object name_1, ab_loop_list_, actual_value, temp_2, temp_3, user_p;
    Object size_in_workspace, minimum_size_in_workspace, position_in_workspace;
    Object current_size_in_workspace, gensymed_symbol_3, temp_5;
    Object svref_new_value, item_or_value_1, desired_position_in_workspace;
    Object held_vector, attribute_value, dot_uac_dot, dot_uac_index_dot;
    Object dot_uac_length_dot, dot_uac_sys_p_dot, dot_current_uac_dot;
    Object gensymed_symbol_4, dot_last_user_p_dot, ab_loop_iter_flag_;
    SI_Long name, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, temp_4, x_adjustment, y_adjustment, svref_arg_2;
    SI_Long item_or_value, next_index, length_1;
    char temp, dot_only_system_attrs_p_dot;
    Declare_special(1);

    x_note_fn_call(136,320);
    if ( !(Systemtables_are_initialized_p && EQ(object_and_fixups,
	    Systemtables_fixups))) {
	object_and_fixups_1 = object_and_fixups;
	object_and_fixups_vector = CONSP(object_and_fixups_1) && 
		EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
		M_CAR(object_and_fixups_1) : Nil;
	type = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
		Qprimitive_value;
	if (object_and_fixups_vector)
	    structure_slot_1(object_and_fixups_vector,Qunit,Nil);
	object = object_and_fixups_vector ? 
		structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
		object_and_fixups_1;
	if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	    return VALUES_1(object);
	else if (EQ(type,Qsequence)) {
	    fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	    if (SIMPLE_VECTOR_P(object) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(object,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(object,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp) {
		if (fixups) {
		    name = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			    (SI_Long)1L)));
		    value = Nil;
		  next_loop:
		    if (name >= ab_loop_bind_)
			goto end_loop;
		    value = evaluation_sequence_aref(fixups,FIX(name));
		    temp_1 = Reading_ghost_definitions_p;
		    if (temp_1);
		    else
			temp_1 = EQUAL(FIX(name),QEXTERNALDEFINITIONS) ? T 
				: Nil;
		    reading_ghost_definitions_p = temp_1;
		    PUSH_SPECIAL_WITH_SYMBOL(Reading_ghost_definitions_p,Qreading_ghost_definitions_p,reading_ghost_definitions_p,
			    0);
		      initialize_all_instances_from_module_data(value);
		    POP_SPECIAL();
		    name = name + (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		}
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		class_definition_p = temp ? ISVREF(object,(SI_Long)20L) : Nil;
		sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Type_in_box_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    text_box_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    text_box_p = Nil;
		if (text_box_p);
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(object,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Text_box_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			text_box_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			text_box_p = Nil;
		}
		sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Rule_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    rule_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    rule_p = Nil;
		name_1 = Nil;
		ab_loop_list_ = list_constant_21;
		value = Nil;
		actual_value = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		name_1 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		value = get_xml_fixups(object_and_fixups,name_1,Nil);
		actual_value = 
			initialize_all_instances_from_module_data(value);
		if (actual_value &&  !(text_box_p && EQ(name_1,
			Qsize_in_workspace))) {
		    temp_1 = name_1;
		    temp_2 = actual_value;
		    temp_3 = xml_object_text_of_p(value);
		    initialize_attribute_from_module_data(5,object,temp_1,
			    temp_2,temp_3,xml_object_unit(value));
		}
		goto next_loop_1;
	      end_loop_1:;
		if (rule_p) {
		    name_1 = Nil;
		    ab_loop_list_ = list_constant_22;
		    value = Nil;
		    actual_value = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    name_1 = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    value = get_xml_fixups(object_and_fixups,name_1,Nil);
		    actual_value = 
			    initialize_all_instances_from_module_data(value);
		    if (actual_value) {
			temp_1 = name_1;
			temp_2 = actual_value;
			temp_3 = xml_object_text_of_p(value);
			initialize_attribute_from_module_data(5,object,
				temp_1,temp_2,temp_3,xml_object_unit(value));
		    }
		    goto next_loop_2;
		  end_loop_2:;
		}
		if (fixups) {
		    user_p = Nil;
		    name = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			    (SI_Long)1L)));
		    value = Nil;
		  next_loop_3:
		    if (name >= ab_loop_bind_)
			goto end_loop_3;
		    value = evaluation_sequence_aref(fixups,FIX(name));
		    if ( !( !TRUEP(user_p) && (memq_function(FIX(name),
			    list_constant_23) || rule_p && EQ(FIX(name),
			    Qoptions)))) {
			actual_value = 
				initialize_all_instances_from_module_data(value);
			if (user_p ||  !TRUEP(memq_function(FIX(name),
				list_constant_24)) && ( 
				!TRUEP(class_definition_p) || 
				memq_function(FIX(name),list_constant_25))) {
			    temp_1 = FIX(name);
			    temp_2 = xml_object_text_of_p(value);
			    initialize_attribute_from_module_data(5,object,
				    temp_1,actual_value,temp_2,
				    xml_object_unit(value));
			}
		    }
		    name = name + (SI_Long)1L;
		    goto next_loop_3;
		  end_loop_3:;
		}
		size_in_workspace = 
			get_xml_object(get_xml_fixups(object_and_fixups,
			Qsize_in_workspace,Nil));
		minimum_size_in_workspace = 
			get_xml_object(get_xml_fixups(object_and_fixups,
			Qminimum_size_in_workspace,Nil));
		position_in_workspace = 
			get_xml_object(get_xml_fixups(object_and_fixups,
			Qposition_in_workspace,Nil));
		if (size_in_workspace &&  !TRUEP(text_box_p))
		    initialize_attribute_from_module_data(3,object,
			    Qsize_in_workspace,size_in_workspace);
		if (minimum_size_in_workspace)
		    initialize_attribute_from_module_data(3,object,
			    Qminimum_size_in_workspace,
			    minimum_size_in_workspace);
		if (position_in_workspace) {
		    if (text_box_p) {
			current_size_in_workspace = 
				get_size_in_workspace(object);
			temp_1 = 
				coerce_number_to_fixnum(estructure_slot(current_size_in_workspace,
				Qwidth,Nil));
			temp_4 = IFIX(FIXNUM_MINUS(temp_1,
				coerce_number_to_fixnum(estructure_slot(size_in_workspace,
				Qwidth,Nil))));
			x_adjustment = temp_4 >>  -  - (SI_Long)1L;
			y_adjustment = (SI_Long)0L;
			gensymed_symbol_3 = allocate_managed_array(1,
				FIX((SI_Long)6L + (SI_Long)1L));
			gensymed_symbol = (SI_Long)0L;
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    svref_arg_2 = gensymed_symbol + 
				    IFIX(Managed_array_index_offset);
			    ISVREF(gensymed_symbol_3,svref_arg_2) = 
				    FIX((SI_Long)1L);
			}
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,
				    (gensymed_symbol >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
			    ISVREF(temp_5,svref_arg_2) = FIX((SI_Long)1L);
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size))
			    SVREF(gensymed_symbol_3,FIX((SI_Long)3L)) = Qx;
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    SVREF(temp_5,FIX((SI_Long)1L)) = Qx;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    item_or_value = 
				    IFIX(estructure_slot(position_in_workspace,
				    Qx,Nil)) + x_adjustment;
			    if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(FIX(item_or_value),
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_5 = temp ? 
				    get_reference_to_item(FIX(item_or_value)) 
				    : FIX(item_or_value);
			    SVREF(gensymed_symbol_3,FIX((SI_Long)4L)) = temp_5;
			}
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    item_or_value = 
				    IFIX(estructure_slot(position_in_workspace,
				    Qx,Nil)) + x_adjustment;
			    if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(FIX(item_or_value),
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    svref_new_value = temp ? 
				    get_reference_to_item(FIX(item_or_value)) 
				    : FIX(item_or_value);
			    SVREF(temp_5,FIX((SI_Long)2L)) = svref_new_value;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size))
			    SVREF(gensymed_symbol_3,FIX((SI_Long)5L)) = Qy;
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    SVREF(temp_5,FIX((SI_Long)3L)) = Qy;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    item_or_value = 
				    IFIX(estructure_slot(position_in_workspace,
				    Qy,Nil)) + y_adjustment;
			    if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(FIX(item_or_value),
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_5 = temp ? 
				    get_reference_to_item(FIX(item_or_value)) 
				    : FIX(item_or_value);
			    SVREF(gensymed_symbol_3,FIX((SI_Long)6L)) = temp_5;
			}
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    item_or_value = 
				    IFIX(estructure_slot(position_in_workspace,
				    Qy,Nil)) + y_adjustment;
			    if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(FIX(item_or_value),
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    svref_new_value = temp ? 
				    get_reference_to_item(FIX(item_or_value)) 
				    : FIX(item_or_value);
			    SVREF(temp_5,FIX((SI_Long)4L)) = svref_new_value;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size))
			    SVREF(gensymed_symbol_3,FIX((SI_Long)7L)) = 
				    Qsuperior;
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    SVREF(temp_5,FIX((SI_Long)5L)) = Qsuperior;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    item_or_value_1 = 
				    estructure_slot(position_in_workspace,
				    Qsuperior,Nil);
			    if (SIMPLE_VECTOR_P(item_or_value_1) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value_1,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_5 = temp ? 
				    get_reference_to_item(item_or_value_1) 
				    : item_or_value_1;
			    SVREF(gensymed_symbol_3,FIX((SI_Long)8L)) = temp_5;
			}
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    item_or_value_1 = 
				    estructure_slot(position_in_workspace,
				    Qsuperior,Nil);
			    if (SIMPLE_VECTOR_P(item_or_value_1) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value_1,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    svref_new_value = temp ? 
				    get_reference_to_item(item_or_value_1) 
				    : item_or_value_1;
			    SVREF(temp_5,FIX((SI_Long)6L)) = svref_new_value;
			}
			desired_position_in_workspace = 
				eval_cons_1(gensymed_symbol_3,Qab_structure);
			initialize_attribute_from_module_data(3,object,
				Qposition_in_workspace,
				desired_position_in_workspace);
			if ( !(FIXNUMP(current_size_in_workspace) || 
				SYMBOLP(current_size_in_workspace) || 
				SIMPLE_VECTOR_P(current_size_in_workspace)))
			    reclaim_if_evaluation_value_1(current_size_in_workspace);
			reclaim_evaluation_structure(desired_position_in_workspace);
		    }
		    else
			initialize_attribute_from_module_data(3,object,
				Qposition_in_workspace,position_in_workspace);
		}
		if ( !TRUEP(get_xml_fixups(object_and_fixups,
			QRDF_COL_RESOURCE,Nil))) {
		    temp_5 = FIXNUM_ADD1(Initialize_items_count);
		    Initialize_items_count = temp_5;
		    update_initialize_xml_progress(0);
		}
	    }
	    return VALUES_1(object);
	}
	else {
	    fixups = structure_slot_1(object_and_fixups_vector,Qattributes,
		    Nil);
	    if (SIMPLE_VECTOR_P(object) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(object,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(object,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp) {
		if (fixups) {
		    gensymed_symbol_3 = fixups;
		    held_vector = Nil;
		    next_index = (SI_Long)1L;
		    length_1 = (SI_Long)0L;
		    name_1 = Nil;
		    attribute_value = Nil;
		    value = Nil;
		    held_vector = M_CAR(gensymed_symbol_3);
		    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		  next_loop_4:
		    if (next_index >= length_1)
			goto end_loop_4;
		    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,next_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),next_index & 
			    (SI_Long)1023L);
		    gensymed_symbol = next_index + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,gensymed_symbol + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(gensymed_symbol >>  
			    -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol & (SI_Long)1023L);
		    value = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index = next_index + (SI_Long)2L;
		    temp_1 = Reading_ghost_definitions_p;
		    if (temp_1);
		    else
			temp_1 = EQUAL(name_1,QEXTERNALDEFINITIONS) ? T : Nil;
		    reading_ghost_definitions_p = temp_1;
		    PUSH_SPECIAL_WITH_SYMBOL(Reading_ghost_definitions_p,Qreading_ghost_definitions_p,reading_ghost_definitions_p,
			    0);
		      initialize_all_instances_from_module_data(value);
		    POP_SPECIAL();
		    goto next_loop_4;
		  end_loop_4:;
		}
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		class_definition_p = temp ? ISVREF(object,(SI_Long)20L) : Nil;
		sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Type_in_box_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    text_box_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    text_box_p = Nil;
		if (text_box_p);
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(object,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Text_box_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			text_box_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			text_box_p = Nil;
		}
		sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Rule_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    rule_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    rule_p = Nil;
		name_1 = Nil;
		ab_loop_list_ = list_constant_21;
		value = Nil;
		actual_value = Nil;
	      next_loop_5:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_5;
		name_1 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		value = get_xml_fixups(object_and_fixups,name_1,Nil);
		actual_value = 
			initialize_all_instances_from_module_data(value);
		if (actual_value &&  !(text_box_p && EQ(name_1,
			Qsize_in_workspace))) {
		    temp_1 = name_1;
		    temp_2 = actual_value;
		    temp_3 = xml_object_text_of_p(value);
		    initialize_attribute_from_module_data(5,object,temp_1,
			    temp_2,temp_3,xml_object_unit(value));
		}
		goto next_loop_5;
	      end_loop_5:;
		if (rule_p) {
		    name_1 = Nil;
		    ab_loop_list_ = list_constant_22;
		    value = Nil;
		    actual_value = Nil;
		  next_loop_6:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_6;
		    name_1 = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    value = get_xml_fixups(object_and_fixups,name_1,Nil);
		    actual_value = 
			    initialize_all_instances_from_module_data(value);
		    if (actual_value) {
			temp_1 = name_1;
			temp_2 = actual_value;
			temp_3 = xml_object_text_of_p(value);
			initialize_attribute_from_module_data(5,object,
				temp_1,temp_2,temp_3,xml_object_unit(value));
		    }
		    goto next_loop_6;
		  end_loop_6:;
		}
		if (fixups) {
		    dot_uac_dot = 
			    structure_slot_1(object_and_fixups_vector,
			    Quser_attribute_count,Nil);
		    dot_only_system_attrs_p_dot =  !TRUEP(dot_uac_dot);
		    dot_uac_index_dot = CONSP(dot_uac_dot) && 
			    EQ(M_CDR(dot_uac_dot),Qsequence) ? 
			    FIX((SI_Long)0L) : Nil;
		    dot_uac_length_dot = dot_uac_index_dot ? 
			    FIXNUM_SUB1(ISVREF(M_CAR(dot_uac_dot),
			    (SI_Long)1L)) : Nil;
		    dot_uac_sys_p_dot = FIXNUMP(dot_uac_dot) ? T : Nil;
		    if (dot_only_system_attrs_p_dot)
			dot_current_uac_dot = Nil;
		    else if (dot_uac_index_dot) {
			gensymed_symbol_3 = M_CAR(dot_uac_dot);
			gensymed_symbol_4 = FIXNUM_ADD1(dot_uac_index_dot);
			dot_current_uac_dot = 
				FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(M_CAR(dot_uac_dot),
				IFIX(FIXNUM_ADD(gensymed_symbol_4,
				Managed_array_index_offset))) : 
				ISVREF(ISVREF(gensymed_symbol_3,
				(IFIX(gensymed_symbol_4) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(gensymed_symbol_4) & (SI_Long)1023L);
		    }
		    else if (dot_uac_sys_p_dot)
			dot_current_uac_dot = FIX((SI_Long)2L);
		    else
			dot_current_uac_dot = Qnil;
		    gensymed_symbol_3 = fixups;
		    held_vector = Nil;
		    next_index = (SI_Long)1L;
		    length_1 = (SI_Long)0L;
		    name_1 = Nil;
		    attribute_value = Nil;
		    value = Nil;
		    dot_last_user_p_dot = Nil;
		    user_p = Nil;
		    ab_loop_iter_flag_ = T;
		    held_vector = M_CAR(gensymed_symbol_3);
		    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		  next_loop_7:
		    if (next_index >= length_1)
			goto end_loop_7;
		    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,next_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),next_index & 
			    (SI_Long)1023L);
		    gensymed_symbol = next_index + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector,gensymed_symbol + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector,(gensymed_symbol >>  
			    -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol & (SI_Long)1023L);
		    value = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index = next_index + (SI_Long)2L;
		    if ( !TRUEP(ab_loop_iter_flag_))
			dot_last_user_p_dot = user_p;
		    if (dot_only_system_attrs_p_dot)
			user_p = Nil;
		    else if ((SI_Long)0L < IFIX(dot_current_uac_dot)) {
			dot_current_uac_dot = FIXNUM_SUB1(dot_current_uac_dot);
			user_p = dot_last_user_p_dot;
		    }
		    else if (dot_uac_index_dot) {
			dot_uac_index_dot = FIXNUM_ADD1(dot_uac_index_dot);
			if (FIXNUM_LT(dot_uac_index_dot,dot_uac_length_dot)) {
			    gensymed_symbol_3 = M_CAR(dot_uac_dot);
			    gensymed_symbol_4 = FIXNUM_ADD1(dot_uac_index_dot);
			    dot_current_uac_dot = 
				    FIXNUM_SUB1(FIXNUM_LE(ISVREF(M_CAR(dot_uac_dot),
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(M_CAR(dot_uac_dot),
				    IFIX(FIXNUM_ADD(gensymed_symbol_4,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(gensymed_symbol_3,
				    (IFIX(gensymed_symbol_4) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(gensymed_symbol_4) & (SI_Long)1023L));
			}
			else
			    dot_current_uac_dot = Most_positive_fixnum;
			user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		    }
		    else if (dot_uac_sys_p_dot) {
			dot_uac_sys_p_dot = Nil;
			dot_current_uac_dot = FIXNUM_SUB1(dot_uac_dot);
			user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		    }
		    else {
			dot_current_uac_dot = Most_positive_fixnum;
			user_p =  !TRUEP(dot_last_user_p_dot) ? T : Nil;
		    }
		    if ( !( !TRUEP(user_p) && (memq_function(name_1,
			    list_constant_23) || rule_p && EQ(name_1,
			    Qoptions)))) {
			actual_value = 
				initialize_all_instances_from_module_data(value);
			if (user_p ||  !TRUEP(memq_function(name_1,
				list_constant_24)) && ( 
				!TRUEP(class_definition_p) || 
				memq_function(name_1,list_constant_25))) {
			    temp_1 = name_1;
			    temp_2 = xml_object_text_of_p(value);
			    initialize_attribute_from_module_data(5,object,
				    temp_1,actual_value,temp_2,
				    xml_object_unit(value));
			}
		    }
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_7;
		  end_loop_7:;
		}
		size_in_workspace = 
			get_xml_object(get_xml_fixups(object_and_fixups,
			Qsize_in_workspace,Nil));
		minimum_size_in_workspace = 
			get_xml_object(get_xml_fixups(object_and_fixups,
			Qminimum_size_in_workspace,Nil));
		position_in_workspace = 
			get_xml_object(get_xml_fixups(object_and_fixups,
			Qposition_in_workspace,Nil));
		if (size_in_workspace &&  !TRUEP(text_box_p))
		    initialize_attribute_from_module_data(3,object,
			    Qsize_in_workspace,size_in_workspace);
		if (minimum_size_in_workspace)
		    initialize_attribute_from_module_data(3,object,
			    Qminimum_size_in_workspace,
			    minimum_size_in_workspace);
		if (position_in_workspace) {
		    if (text_box_p) {
			current_size_in_workspace = 
				get_size_in_workspace(object);
			temp_1 = 
				coerce_number_to_fixnum(estructure_slot(current_size_in_workspace,
				Qwidth,Nil));
			temp_4 = IFIX(FIXNUM_MINUS(temp_1,
				coerce_number_to_fixnum(estructure_slot(size_in_workspace,
				Qwidth,Nil))));
			x_adjustment = temp_4 >>  -  - (SI_Long)1L;
			y_adjustment = (SI_Long)0L;
			gensymed_symbol_3 = allocate_managed_array(1,
				FIX((SI_Long)6L + (SI_Long)1L));
			gensymed_symbol = (SI_Long)0L;
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    svref_arg_2 = gensymed_symbol + 
				    IFIX(Managed_array_index_offset);
			    ISVREF(gensymed_symbol_3,svref_arg_2) = 
				    FIX((SI_Long)1L);
			}
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,
				    (gensymed_symbol >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
			    ISVREF(temp_5,svref_arg_2) = FIX((SI_Long)1L);
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size))
			    SVREF(gensymed_symbol_3,FIX((SI_Long)3L)) = Qx;
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    SVREF(temp_5,FIX((SI_Long)1L)) = Qx;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    item_or_value = 
				    IFIX(estructure_slot(position_in_workspace,
				    Qx,Nil)) + x_adjustment;
			    if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(FIX(item_or_value),
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_5 = temp ? 
				    get_reference_to_item(FIX(item_or_value)) 
				    : FIX(item_or_value);
			    SVREF(gensymed_symbol_3,FIX((SI_Long)4L)) = temp_5;
			}
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    item_or_value = 
				    IFIX(estructure_slot(position_in_workspace,
				    Qx,Nil)) + x_adjustment;
			    if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(FIX(item_or_value),
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    svref_new_value = temp ? 
				    get_reference_to_item(FIX(item_or_value)) 
				    : FIX(item_or_value);
			    SVREF(temp_5,FIX((SI_Long)2L)) = svref_new_value;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size))
			    SVREF(gensymed_symbol_3,FIX((SI_Long)5L)) = Qy;
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    SVREF(temp_5,FIX((SI_Long)3L)) = Qy;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    item_or_value = 
				    IFIX(estructure_slot(position_in_workspace,
				    Qy,Nil)) + y_adjustment;
			    if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(FIX(item_or_value),
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_5 = temp ? 
				    get_reference_to_item(FIX(item_or_value)) 
				    : FIX(item_or_value);
			    SVREF(gensymed_symbol_3,FIX((SI_Long)6L)) = temp_5;
			}
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    item_or_value = 
				    IFIX(estructure_slot(position_in_workspace,
				    Qy,Nil)) + y_adjustment;
			    if (SIMPLE_VECTOR_P(FIX(item_or_value)) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value))) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(FIX(item_or_value),
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(FIX(item_or_value),(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    svref_new_value = temp ? 
				    get_reference_to_item(FIX(item_or_value)) 
				    : FIX(item_or_value);
			    SVREF(temp_5,FIX((SI_Long)4L)) = svref_new_value;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size))
			    SVREF(gensymed_symbol_3,FIX((SI_Long)7L)) = 
				    Qsuperior;
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    SVREF(temp_5,FIX((SI_Long)5L)) = Qsuperior;
			}
			if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    item_or_value_1 = 
				    estructure_slot(position_in_workspace,
				    Qsuperior,Nil);
			    if (SIMPLE_VECTOR_P(item_or_value_1) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value_1,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp_5 = temp ? 
				    get_reference_to_item(item_or_value_1) 
				    : item_or_value_1;
			    SVREF(gensymed_symbol_3,FIX((SI_Long)8L)) = temp_5;
			}
			else {
			    temp_5 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
			    item_or_value_1 = 
				    estructure_slot(position_in_workspace,
				    Qsuperior,Nil);
			    if (SIMPLE_VECTOR_P(item_or_value_1) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_1)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(item_or_value_1,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(item_or_value_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp = TRUEP(Nil);
			    svref_new_value = temp ? 
				    get_reference_to_item(item_or_value_1) 
				    : item_or_value_1;
			    SVREF(temp_5,FIX((SI_Long)6L)) = svref_new_value;
			}
			desired_position_in_workspace = 
				eval_cons_1(gensymed_symbol_3,Qab_structure);
			initialize_attribute_from_module_data(3,object,
				Qposition_in_workspace,
				desired_position_in_workspace);
			if ( !(FIXNUMP(current_size_in_workspace) || 
				SYMBOLP(current_size_in_workspace) || 
				SIMPLE_VECTOR_P(current_size_in_workspace)))
			    reclaim_if_evaluation_value_1(current_size_in_workspace);
			reclaim_evaluation_structure(desired_position_in_workspace);
		    }
		    else
			initialize_attribute_from_module_data(3,object,
				Qposition_in_workspace,position_in_workspace);
		}
		if ( !TRUEP(get_xml_fixups(object_and_fixups,
			QRDF_COL_RESOURCE,Nil))) {
		    temp_5 = FIXNUM_ADD1(Initialize_items_count);
		    Initialize_items_count = temp_5;
		    update_initialize_xml_progress(0);
		}
	    }
	    return VALUES_1(object);
	}
    }
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-ALL-RELATIONSHIPS-FROM-MODULE-DATA */
Object initialize_all_relationships_from_module_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, value, actual_value, temp_1, temp_2, gensymed_symbol;
    Object held_vector, name_1, attribute_value;
    SI_Long name, ab_loop_bind_, next_index, length_1, gensymed_symbol_1;
    char temp;

    x_note_fn_call(136,321);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(object);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    if (fixups) {
		name = (SI_Long)0L;
		ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
			(SI_Long)1L)));
		value = Nil;
	      next_loop:
		if (name >= ab_loop_bind_)
		    goto end_loop;
		value = evaluation_sequence_aref(fixups,FIX(name));
		initialize_all_relationships_from_module_data(value);
		name = name + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	}
	else if (fixups) {
	    name = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop_1:
	    if (name >= ab_loop_bind_)
		goto end_loop_1;
	    value = evaluation_sequence_aref(fixups,FIX(name));
	    actual_value = 
		    initialize_all_relationships_from_module_data(value);
	    if (EQ(FIX(name),Qrelationships)) {
		temp_1 = FIX(name);
		temp_2 = xml_object_text_of_p(value);
		initialize_attribute_from_module_data(5,object,temp_1,
			actual_value,temp_2,xml_object_unit(value));
	    }
	    name = name + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	return VALUES_1(object);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    if (fixups) {
		gensymed_symbol = fixups;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		name_1 = Nil;
		attribute_value = Nil;
		value = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_2:
		if (next_index >= length_1)
		    goto end_loop_2;
		name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 
			& (SI_Long)1023L);
		value = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		initialize_all_relationships_from_module_data(value);
		goto next_loop_2;
	      end_loop_2:;
	    }
	}
	else if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name_1 = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_3:
	    if (next_index >= length_1)
		goto end_loop_3;
	    name_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    actual_value = 
		    initialize_all_relationships_from_module_data(value);
	    if (EQ(name_1,Qrelationships)) {
		temp_1 = name_1;
		temp_2 = xml_object_text_of_p(value);
		initialize_attribute_from_module_data(5,object,temp_1,
			actual_value,temp_2,xml_object_unit(value));
	    }
	    goto next_loop_3;
	  end_loop_3:;
	}
	return VALUES_1(object);
    }
}

/* INITIALIZE-ATTRIBUTE-FROM-MODULE-DATA */
Object initialize_attribute_from_module_data varargs_1(int, n)
{
    Object item, attribute, value;
    Object text_of_p, unit_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(136,322);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    attribute = REQUIRED_ARG_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    text_of_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    unit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return initialize_or_check_attribute_from_module_data(item,attribute,
	    value,T,text_of_p,unit_qm);
}

/* CHECK-ATTRIBUTE-FOR-CLEAR-TEXT */
Object check_attribute_for_clear_text varargs_1(int, n)
{
    Object item, attribute, value;
    Object text_of_p, unit_qm, disable_tracing_and_breakpoints_warning;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,323);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    attribute = REQUIRED_ARG_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    text_of_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    unit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    disable_tracing_and_breakpoints_warning = T;
    PUSH_SPECIAL_WITH_SYMBOL(Disable_tracing_and_breakpoints_warning,Qdisable_tracing_and_breakpoints_warning,disable_tracing_and_breakpoints_warning,
	    0);
      result = initialize_or_check_attribute_from_module_data(item,
	      attribute,value,Nil,text_of_p,unit_qm);
    POP_SPECIAL();
    return result;
}

static Object list_constant_26;    /* # */

static Object Qsimulation_frame_qm;  /* simulation-frame? */

static Object string_constant_161;  /* "Illegal simulation-details" */

static Object string_constant_162;  /* "Illegal text value" */

static Object list_constant_27;    /* # */

static Object Qg2_array_initial_values;  /* g2-array-initial-values */

static Object list_constant_28;    /* # */

/* INITIALIZE-OR-CHECK-ATTRIBUTE-FROM-MODULE-DATA */
Object initialize_or_check_attribute_from_module_data(item,attribute,value,
	    initialize_p,text_of_p,unit_qm)
    Object item, attribute, value, initialize_p, text_of_p, unit_qm;
{
    Object current_computation_frame, class_description, attribute_name;
    Object class_qualifier_qm, slot_description_qm, unaliased_name_qm;
    Object unaliased_slot_description_qm, slot_type_qm, text_slot_p, x2;
    Object gensymed_symbol, sub_class_bit_vector, second_arg, second_new_value;
    Object problem_description_qm, temp_1, copied_text_string, success_qm;
    Object reason_for_failure_qm, x, type, sub_item, parent_frame_qm;
    Object slot_value_qm, slot_value_class_description_qm;
    Object slot_type_specification;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,324);
    if ( !TRUEP(memq_function(attribute,list_constant_26))) {
	current_computation_frame = item;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  class_description = ISVREF(item,(SI_Long)1L);
	  attribute_name = CONSP(attribute) ? CAR(attribute) : attribute;
	  class_qualifier_qm = CONSP(attribute) ? CDR(attribute) : Nil;
	  slot_description_qm = 
		  get_slot_description_of_class_description_function(attribute_name,
		  class_description,class_qualifier_qm);
	  unaliased_name_qm =  !TRUEP(slot_description_qm) ||  
		  !TRUEP(ISVREF(slot_description_qm,(SI_Long)8L)) ? 
		  get_slot_name_for_alias_if_any(attribute_name,item) : Nil;
	  unaliased_slot_description_qm = unaliased_name_qm ? 
		  get_slot_description_of_class_description_function(unaliased_name_qm,
		  class_description,Nil) : slot_description_qm;
	  slot_type_qm = unaliased_slot_description_qm ? 
		  assq_function(Qtype,ISVREF(unaliased_slot_description_qm,
		  (SI_Long)9L)) : Qnil;
	  text_slot_p = slot_type_qm ? memq_function(Qtext,
		  CDDR(slot_type_qm)) : Qnil;
	  if (EQ(attribute,Qab_class_name)) {
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol = Nil;
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Definition_class_description,
			  (SI_Long)18L));
		  sub_class_vector_index = superior_class_bit_number >>  - 
			   - (SI_Long)3L;
		  if (sub_class_vector_index < 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			      {
		      gensymed_symbol_1 = 
			      UBYTE_8_ISAREF_1(sub_class_bit_vector,
			      sub_class_vector_index);
		      gensymed_symbol_2 = (SI_Long)1L;
		      gensymed_symbol_3 = superior_class_bit_number & 
			      (SI_Long)7L;
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      if (initialize_p) {
		  if (Reading_ghost_definitions_p) {
		      if (assq_function(value,Definitions_in_module)) {
			  second_arg = assq_function(value,
				  Definitions_in_module);
			  second_new_value = read_ghost_definition_2(value,
				  item,Definitions_in_module);
			  M_SECOND(second_arg) = second_new_value;
		      }
		      else
			  read_ghost_definition_2(value,item,
				  Definitions_in_module);
		  }
		  else
		      install_class_definition(value,item,Nil,Nil,T);
	      }
	      problem_description_qm = Nil;
	  }
	  else if (EQ(SECOND(slot_type_qm),Qsimulation_frame_qm)) {
	      if ( !TRUEP(value)) {
		  if (initialize_p)
		      put_simulation_details(item,value,Nil);
		  problem_description_qm = Nil;
	      }
	      else {
		  if (SIMPLE_VECTOR_P(value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(value,(SI_Long)1L);
		      gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
			      EQ(ISVREF(x2,(SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? x2 : Qnil;
		  }
		  else
		      gensymed_symbol = Nil;
		  if (gensymed_symbol) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Simulation_subtable_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
		      if (sub_class_vector_index < 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				  {
			  gensymed_symbol_1 = 
				  UBYTE_8_ISAREF_1(sub_class_bit_vector,
				  sub_class_vector_index);
			  gensymed_symbol_2 = (SI_Long)1L;
			  gensymed_symbol_3 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_2 = gensymed_symbol_2 << 
				  gensymed_symbol_3;
			  gensymed_symbol_1 = gensymed_symbol_1 & 
				  gensymed_symbol_2;
			  temp = (SI_Long)0L < gensymed_symbol_1;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if ( !temp)
		      problem_description_qm = tformat_text_string(1,
			      string_constant_161);
		  else
		      problem_description_qm = Nil;
	      }
	  }
	  else if (EQ(SECOND(slot_type_qm),Qframe_edit_timestamp_qm)) {
	      change_slot_value(3,item,attribute_name,value);
	      problem_description_qm = Nil;
	  }
	  else if (text_of_p) {
	      if ( !(text_string_p(value) ||  !TRUEP(value)))
		  problem_description_qm = tformat_text_string(1,
			  string_constant_162);
	      else if (initialize_p) {
		  temp_1 = value;
		  if (temp_1);
		  else
		      temp_1 = array_constant_8;
		  copied_text_string = copy_text_string(temp_1);
		  result = parse_and_change_slot(item,
			  unaliased_slot_description_qm,copied_text_string,
			  slot_type_qm);
		  MVS_2(result,success_qm,reason_for_failure_qm);
		  if ( !TRUEP(success_qm))
		      reclaim_text_string(copied_text_string);
		  problem_description_qm = reason_for_failure_qm;
	      }
	      else
		  problem_description_qm = Nil;
	  }
	  else if (text_slot_p)
	      problem_description_qm = tformat_text_string(1,
		      string_constant_162);
	  else if (unit_qm && unaliased_slot_description_qm && 
		  ISVREF(unaliased_slot_description_qm,(SI_Long)8L) && 
		  (FIXNUMP(value) || INLINE_DOUBLE_FLOAT_VECTOR_P(value) 
		  != (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) 
		  == (SI_Long)1L) && type_specification_type_p(value,
		  ISVREF(unaliased_slot_description_qm,(SI_Long)5L))) {
	      if (initialize_p) {
		  change_slot_description_value_function(item,
			  unaliased_slot_description_qm,
			  slot_value_list_2(FIXNUMP(value) || value && 
			  SYMBOLP(value) ? value : 
			  copy_evaluation_value_1(value),unit_qm),Nil,Nil);
		  problem_description_qm = Nil;
	      }
	      else
		  problem_description_qm = Nil;
	  }
	  else {
	      if (unaliased_slot_description_qm && 
		      ISVREF(unaliased_slot_description_qm,(SI_Long)8L)) {
		  temp =  !TRUEP(value);
		  if (temp);
		  else if (SIMPLE_VECTOR_P(value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(value,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp);
		  else {
		      x = get_slot_description_value(item,
			      unaliased_slot_description_qm);
		      if (SIMPLE_VECTOR_P(x) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(x,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		  }
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  type = ISVREF(unaliased_slot_description_qm,(SI_Long)5L);
		  temp = TRUEP(type_specification_type_p(value,type));
		  if (temp);
		  else
		      temp = class_type_specification_p(type) || 
			      type_specifications_could_intersect_in_kb_p(list_constant_27,
			      type) ?  !TRUEP(value) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  if (SIMPLE_VECTOR_P(value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(value,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      sub_item = item;
		      parent_frame_qm = Nil;
		    next_loop:
		      if (EQ(value,sub_item)) {
			  temp = TRUEP(sub_item);
			  goto end_1;
		      }
		      parent_frame_qm = 
			      get_lookup_slot_value_given_default(sub_item,
			      Qparent_frame,Nil);
		      if ( !TRUEP(parent_frame_qm))
			  goto end_loop;
		      sub_item = parent_frame_qm;
		      goto next_loop;
		    end_loop:
		      temp = TRUEP(Qnil);
		    end_1:;
		      if (temp);
		      else
			  temp = TRUEP(ancestor_p(value,item));
		  }
		  else
		      temp = TRUEP(Nil);
		  temp =  !temp;
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  if (initialize_p &&  !EQ(value,
			  get_slot_description_value(item,
			  unaliased_slot_description_qm))) {
		      change_slot_description_value_function(item,
			      unaliased_slot_description_qm,FIXNUMP(value) 
			      || value && SYMBOLP(value) || 
			      SIMPLE_VECTOR_P(value) ? value : 
			      copy_if_evaluation_value_1(value),Nil,Nil);
		      if (SIMPLE_VECTOR_P(value) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(value,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(value,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  update_attribute_tables(1,
				  get_lookup_slot_value_given_default(value,
				  Qparent_frame,Nil));
			  gensymed_symbol = ACCESS_ONCE(ISVREF(value,
				  (SI_Long)14L));
			  gensymed_symbol = gensymed_symbol ? 
				  ACCESS_ONCE(ISVREF(gensymed_symbol,
				  (SI_Long)5L)) : Nil;
			  if (gensymed_symbol) {
			      update_images_of_block(value,T,Nil);
			      gensymed_symbol = ACCESS_ONCE(ISVREF(value,
				      (SI_Long)14L));
			      gensymed_symbol = gensymed_symbol ? 
				      ACCESS_ONCE(ISVREF(gensymed_symbol,
				      (SI_Long)5L)) : Nil;
			      transfer_workspace_subblock(value,
				      gensymed_symbol,Nil);
			  }
		      }
		  }
		  problem_description_qm = Nil;
	      }
	      else if (EQ(unaliased_name_qm,Qg2_array_initial_values) && 
		      Delay_item_array_initializations_p) {
		  if (initialize_p)
		      Delayed_item_array_initializations = 
			      eval_cons_1(eval_cons_1(item,value),
			      Delayed_item_array_initializations);
		  problem_description_qm = Nil;
	      }
	      else if (initialize_p)
		  problem_description_qm = 
			  conclude_into_attribute_component(6,item,
			  attribute_name,class_qualifier_qm,FIXNUMP(value) 
			  || value && SYMBOLP(value) || 
			  SIMPLE_VECTOR_P(value) ? value : 
			  copy_if_evaluation_value_1(value),Nil,Nil);
	      else if ( !(SIMPLE_VECTOR_P(unaliased_slot_description_qm) 
		      && EQ(ISVREF(unaliased_slot_description_qm,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_slot_description_g2_struct)))
		  problem_description_qm = Nil;
	      else if (ISVREF(unaliased_slot_description_qm,(SI_Long)8L)) {
		  slot_value_qm = get_slot_description_value(item,
			  unaliased_slot_description_qm);
		  if (SIMPLE_VECTOR_P(slot_value_qm) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(slot_value_qm,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(slot_value_qm,(SI_Long)1L);
		      slot_value_class_description_qm = 
			      SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? x2 : Qnil;
		  }
		  else
		      slot_value_class_description_qm = Nil;
		  if (slot_value_class_description_qm)
		      problem_description_qm = Nil;
		  else {
		      slot_type_specification = 
			      ISVREF(unaliased_slot_description_qm,
			      (SI_Long)5L);
		      problem_description_qm =  
			      !(type_specification_type_p(value,
			      slot_type_specification) || FIXNUMP(value) 
			      && EQ(slot_type_specification,Qfloat)) ? 
			      make_conclude_type_error_string(value,
			      slot_description_qm,class_description,item,
			      slot_type_specification) : Nil;
		  }
	      }
	      else if (memq_function(attribute,list_constant_28))
		  problem_description_qm = Nil;
	      else
		  problem_description_qm = 
			  check_for_category_evaluator_and_slot_value_compiler_errors(item,
			  value,unaliased_slot_description_qm,
			  unaliased_name_qm);
	  }
	  if (problem_description_qm)
	      report_clear_text_problem(initialize_p ? Qload : Qsave,item,
		      attribute_name,value,problem_description_qm);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object array_constant_24;   /* # */

static Object array_constant_25;   /* # */

static Object string_constant_163;  /* "Save" */

static Object string_constant_164;  /* "Load" */

static Object string_constant_165;  /* "~A problem: ~A" */

static Object string_constant_166;  /* "~A problem when making ~NF be the ~S of ~NF: ~A" */

static Object string_constant_167;  /* "~A problem when making ~NV be the ~S of ~NF: ~A" */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

/* REPORT-CLEAR-TEXT-PROBLEM */
Object report_clear_text_problem(save_or_load,item,attribute,value,
	    problem_description_qm)
    Object save_or_load, item, attribute, value, problem_description_qm;
{
    Object module, skip_prefix, operation_string, control_string, x2;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(7);

    x_note_fn_call(136,325);
    if (EQ(save_or_load,Qsave)) {
	module = Current_module_being_saved;
	if ( !TRUEP(memq_function(module,
		Clear_text_saving_problems_were_encountered_p)))
	    Clear_text_saving_problems_were_encountered_p = 
		    gensym_cons_1(module,
		    Clear_text_saving_problems_were_encountered_p);
    }
    skip_prefix = match_prefix(array_constant_24,problem_description_qm);
    if (skip_prefix);
    else
	skip_prefix = match_prefix(array_constant_25,problem_description_qm);
    if (EQ(save_or_load,Qsave))
	operation_string = string_constant_163;
    else if (EQ(save_or_load,Qload))
	operation_string = string_constant_164;
    else
	operation_string = Qnil;
    if (skip_prefix)
	control_string = string_constant_165;
    else {
	if (SIMPLE_VECTOR_P(value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L &&  
		!EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	control_string = temp ? string_constant_166 : string_constant_167;
    }
    snapshots_of_related_blocks = Nil;
    note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
	      5);
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  aref_arg_2 = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	  aref_arg_2 = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	  current_wide_string = wide_string_bv16;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		  3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  if (skip_prefix)
		      tformat(3,control_string,operation_string,
			      problem_description_qm);
		  else
		      tformat(6,control_string,operation_string,value,
			      attribute,item,problem_description_qm);
		  record_block_for_tformat(item);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	notify_user_1(temp_1);
	if (Snapshots_of_related_blocks) {
	    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
	    Snapshots_of_related_blocks = Nil;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_text_string(problem_description_qm);
    return VALUES_1(Nil);
}

/* MATCH-PREFIX */
Object match_prefix(desired_prefix,string_1)
    Object desired_prefix, string_1;
{
    Object desired_prefix_length, prefix, temp;

    x_note_fn_call(136,326);
    desired_prefix_length = lengthw(desired_prefix);
    prefix = FIXNUM_LT(desired_prefix_length,lengthw(string_1)) ? 
	    copy_partial_wide_string(string_1,desired_prefix_length) : Qnil;
    temp = prefix ? string_eq_w(prefix,desired_prefix) : Qnil;
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(prefix) != (SI_Long)0L)
	reclaim_wide_string(prefix);
    return VALUES_1(temp);
}

static Object Qinitial_values;     /* initial-values */

/* DO-DELAYED-ARRAY-INITIALIZATIONS */
Object do_delayed_array_initializations()
{
    Object e, ab_loop_list_, item, value;

    x_note_fn_call(136,327);
    Delay_item_array_initializations_p = Nil;
    e = Nil;
    ab_loop_list_ = Delayed_item_array_initializations;
    item = Nil;
    value = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    e = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    item = CAR(e);
    value = CDR(e);
    initialize_attribute_from_module_data(3,item,Qinitial_values,value);
    reclaim_eval_cons_1(e);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(Delayed_item_array_initializations);
    return VALUES_1(Qnil);
}

static Object Qedges_of_workspace;  /* edges-of-workspace */

/* FIX-ALL-WORKSPACE-SIZES-FROM-MODULE-DATA */
Object fix_all_workspace_sizes_from_module_data(object_and_fixups)
    Object object_and_fixups;
{
    Object object_and_fixups_1, object_and_fixups_vector, type, object, fixups;
    Object x2, gensymed_symbol, sub_class_bit_vector, name, edges, value;
    Object held_vector, attribute_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, name_1;
    SI_Long ab_loop_bind_, next_index, length_1;
    char temp;

    x_note_fn_call(136,328);
    object_and_fixups_1 = object_and_fixups;
    object_and_fixups_vector = CONSP(object_and_fixups_1) && 
	    EQ(M_CDR(object_and_fixups_1),Qab_structure) ? 
	    M_CAR(object_and_fixups_1) : Nil;
    type = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qtype,Nil) : 
	    Qprimitive_value;
    if (object_and_fixups_vector)
	structure_slot_1(object_and_fixups_vector,Qunit,Nil);
    object = object_and_fixups_vector ? 
	    structure_slot_1(object_and_fixups_vector,Qvalue,Nil) : 
	    object_and_fixups_1;
    if (EQ(type,Qprimitive_value) || EQ(type,Qtext))
	return VALUES_1(Nil);
    else if (EQ(type,Qsequence)) {
	fixups = structure_slot_1(object_and_fixups_vector,Qelements,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = Qedges_of_workspace;
	    edges = get_xml_object(get_xml_fixups(object_and_fixups,name,Nil));
	    if (edges)
		initialize_attribute_from_module_data(3,object,name,edges);
	}
	if (fixups) {
	    name_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(fixups),
		    (SI_Long)1L)));
	    value = Nil;
	  next_loop:
	    if (name_1 >= ab_loop_bind_)
		goto end_loop;
	    value = evaluation_sequence_aref(fixups,FIX(name_1));
	    fix_all_workspace_sizes_from_module_data(value);
	    name_1 = name_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	fixups = structure_slot_1(object_and_fixups_vector,Qattributes,Nil);
	if (SIMPLE_VECTOR_P(object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) > (SI_Long)2L &&  
		!EQ(ISVREF(object,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(object,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    name = Qedges_of_workspace;
	    edges = get_xml_object(get_xml_fixups(object_and_fixups,name,Nil));
	    if (edges)
		initialize_attribute_from_module_data(3,object,name,edges);
	}
	if (fixups) {
	    gensymed_symbol = fixups;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    name = Nil;
	    attribute_value = Nil;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    fix_all_workspace_sizes_from_module_data(value);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Allow_comparison_of_slot_value_to_parse_result, Qallow_comparison_of_slot_value_to_parse_result);

static Object Qslot_value_compiler;  /* slot-value-compiler */

static Object string_constant_168;  /* "Slot value does not match compiled result.~
				     *                               ~%  ~A ~A~%  ~A~%  ~A"
				     */

/* CHECK-FOR-CATEGORY-EVALUATOR-AND-SLOT-VALUE-COMPILER-ERRORS */
Object check_for_category_evaluator_and_slot_value_compiler_errors(item,
	    new_value,slot_description,unaliased_name)
    Object item, new_value, slot_description, unaliased_name;
{
    Object slot_type_qm, category_qm, category_evaluator_interface;
    Object parse_result_maker_qm, slot_value_compiler_qm, current_edit_state;
    Object svref_arg_1, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, parse_result_or_bad_phrase;
    Object cei_error_string_qm, temp, new_value_or_bad_phrase;
    Object svc_error_string_qm, value;
    Declare_special(1);
    Object result;

    x_note_fn_call(136,329);
    slot_type_qm = assq_function(Qtype,ISVREF(slot_description,(SI_Long)9L));
    category_qm = slot_type_qm ? SECOND(slot_type_qm) : Nil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
	    Qcategory_evaluator_interface);
    parse_result_maker_qm = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    slot_value_compiler_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
	    Qslot_value_compiler);
    if (parse_result_maker_qm) {
	current_edit_state = make_edit_state_1();
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		0);
	  svref_arg_1 = Current_edit_state;
	  SVREF(svref_arg_1,FIX((SI_Long)3L)) = item;
	  gensymed_symbol = parse_result_maker_qm;
	  gensymed_symbol_1 = new_value;
	  gensymed_symbol_2 = item;
	  gensymed_symbol_3 = slot_description;
	  gensymed_symbol_4 = Nil;
	  result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	  MVS_2(result,parse_result_or_bad_phrase,cei_error_string_qm);
	  if (EQ(parse_result_or_bad_phrase,Bad_phrase))
	      temp = cei_error_string_qm;
	  else if (slot_value_compiler_qm) {
	      result = funcall(7,slot_value_compiler_qm,
		      parse_result_or_bad_phrase,item,unaliased_name,Nil,
		      Nil,Nil);
	      MVS_2(result,new_value_or_bad_phrase,svc_error_string_qm);
	      if (EQ(new_value_or_bad_phrase,Bad_phrase))
		  temp = svc_error_string_qm;
	      else {
		  if (Allow_comparison_of_slot_value_to_parse_result) {
		      value = get_slot_description_value(item,
			      slot_description);
		      if ( !TRUEP(compare_slot_value_to_parse_result(item,
			      slot_description,value,
				  new_value_or_bad_phrase))) {
			  notify_user_at_console(5,string_constant_168,
				  ISVREF(ISVREF(item,(SI_Long)1L),
				  (SI_Long)1L),ISVREF(slot_description,
				  (SI_Long)2L),value,new_value_or_bad_phrase);
			  temp = Nil;
		      }
		      else
			  temp = Nil;
		  }
		  else
		      temp = Nil;
		  if (temp);
		  else
		      temp = Nil;
	      }
	  }
	  else
	      temp = Qnil;
	  goto end_attribute_export_conclude_context;
	end_attribute_export_conclude_context:
	  reclaim_edit_state_1(Current_edit_state);
	  result = VALUES_1(temp);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qframe_author_or_authors;  /* frame-author-or-authors */

static Object Qicon_description_for_class_qm;  /* icon-description-for-class? */

static Object Qdefault_message_properties;  /* default-message-properties */

static Object Qdefault_overrides;  /* default-overrides */

static Object Qchart_annotations;  /* chart-annotations */

static Object Qlog_file_name;      /* log-file-name */

/* COMPARE-SLOT-VALUE-TO-PARSE-RESULT */
Object compare_slot_value_to_parse_result(item,slot_description,value,
	    new_value_or_bad_phrase)
    Object item, slot_description, value, new_value_or_bad_phrase;
{
    Object temp, sv_author, sv_timestamp, sv_previous, new_author;
    Object new_timestamp, new_previous, x2, gensymed_symbol;
    Object sub_class_bit_vector, sv_override, ab_loop_list_, new_override;
    Object ab_loop_list__1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Object result;

    x_note_fn_call(136,330);
    temp = compare_slot_value_to_parse_result_1(value,new_value_or_bad_phrase);
    if (temp)
	return VALUES_1(temp);
    else {
	temp = ISVREF(slot_description,(SI_Long)2L);
	if (EQ(temp,Qframe_author_or_authors)) {
	    result = decode_frame_author_or_authors(value,Nil);
	    MVS_3(result,sv_author,sv_timestamp,sv_previous);
	    result = decode_frame_author_or_authors(value,Nil);
	    MVS_3(result,new_author,new_timestamp,new_previous);
	    if (EQUAL(sv_author,new_author) && EQUAL(sv_timestamp,
		    new_timestamp))
		return VALUES_1(EQUAL(sv_previous,new_previous) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(temp,Qicon_description_for_class_qm))
	    return VALUES_1(T);
	else if (EQ(temp,Qdefault_message_properties))
	    return plist_equal_p(value,new_value_or_bad_phrase);
	else if (EQ(temp,Qdefault_overrides)) {
	    if (SIMPLE_VECTOR_P(item) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L && 
		     !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Object_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? FIXNUM_EQ(length(value),
		    length(new_value_or_bad_phrase)) : TRUEP(Nil)) {
		sv_override = Nil;
		ab_loop_list_ = value;
		new_override = Nil;
		ab_loop_list__1 = new_value_or_bad_phrase;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		sv_override = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop;
		new_override = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !(compare_slot_value_to_parse_result_1(sv_override,
			new_override) || 
			symbolic_parameter_initial_value_override(sv_override) 
			|| 
			symbolic_parameter_initial_value_override(new_override) 
			|| EQ(Nil,CADR(sv_override)) || EQ(Qnone,
			CADR(new_override))))
		    return VALUES_1(Nil);
		goto next_loop;
	      end_loop:
		return VALUES_1(T);
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(temp,Qchart_annotations))
	    return VALUES_1(T);
	else if (EQ(temp,Qlog_file_name))
	    return VALUES_1(T);
	else
	    return VALUES_1(Qnil);
    }
}

/* COMPARE-SLOT-VALUE-TO-PARSE-RESULT-1 */
Object compare_slot_value_to_parse_result_1(slot_value,phrase_value)
    Object slot_value, phrase_value;
{
    Object gensymed_symbol, held_vector, slot_value_value, gensymed_symbol_1;
    Object held_vector_1, phrase_value_value, elt_1, validated_elt;
    Object slot_value_key, attribute_value, phrase_value_key;
    SI_Long next_index, length_1, next_index_1, length_2, gensymed_symbol_2;
    double arg, arg_1;

    x_note_fn_call(136,331);
    if (EQ(slot_value,phrase_value))
	return VALUES_1(T);
    else if (FIXNUMP(slot_value)) {
	if (FIXNUMP(phrase_value))
	    return VALUES_1(FIXNUM_EQ(slot_value,phrase_value) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_value)) == (SI_Long)1L) {
	    arg = DFLOAT_ISAREF_1(slot_value,(SI_Long)0L);
	    arg_1 = DFLOAT_ISAREF_1(phrase_value,(SI_Long)0L);
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg))
		return VALUES_1( !inline_nanp_for_comparison(arg_1) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (text_string_p(slot_value)) {
	if (text_string_p(phrase_value))
	    return string_eq_w(slot_value,phrase_value);
	else
	    return VALUES_1(Nil);
    }
    else if (SYMBOLP(slot_value))
	return VALUES_1(Nil);
    else if (ATOM(slot_value))
	return VALUES_1(Nil);
    else if (ATOM(phrase_value))
	return VALUES_1(EQUAL(slot_value,phrase_value) ? T : Nil);
    else if (CONSP(slot_value) && EQ(M_CDR(slot_value),Qsequence)) {
	if (CONSP(phrase_value) && EQ(M_CDR(phrase_value),Qsequence) && 
		IFIX(FIXNUM_SUB1(ISVREF(M_CAR(slot_value),(SI_Long)1L))) 
		== IFIX(FIXNUM_SUB1(ISVREF(M_CAR(phrase_value),
		    (SI_Long)1L)))) {
	    gensymed_symbol = slot_value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    slot_value_value = Nil;
	    gensymed_symbol_1 = phrase_value;
	    held_vector_1 = Nil;
	    next_index_1 = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    phrase_value_value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    held_vector_1 = M_CAR(gensymed_symbol_1);
	    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
	  next_loop:
	    if (next_index >= length_1)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    slot_value_value = validated_elt;
	    if (next_index_1 >= length_2)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		    next_index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_1 & 
		    (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index_1 = next_index_1 + (SI_Long)1L;
	    phrase_value_value = validated_elt;
	    if ( 
		    !TRUEP(compare_slot_value_to_parse_result_1(slot_value_value,
		    phrase_value_value)))
		return VALUES_1(Nil);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(T);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (CONSP(slot_value) && EQ(M_CDR(slot_value),Qab_structure)) {
	if (CONSP(phrase_value) && EQ(M_CDR(phrase_value),Qab_structure)) {
	    if (FIXNUM_EQ(ISVREF(M_CAR(slot_value),(SI_Long)1L),
		    ISVREF(M_CAR(phrase_value),(SI_Long)1L))) {
		gensymed_symbol = slot_value;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		slot_value_key = Nil;
		attribute_value = Nil;
		slot_value_value = Nil;
		gensymed_symbol_1 = phrase_value;
		held_vector_1 = Nil;
		next_index_1 = (SI_Long)1L;
		length_2 = (SI_Long)0L;
		phrase_value_key = Nil;
		attribute_value = Nil;
		phrase_value_value = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		held_vector_1 = M_CAR(gensymed_symbol_1);
		length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		slot_value_key = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_2 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 
			& (SI_Long)1023L);
		slot_value_value = 
			validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if (next_index_1 >= length_2)
		    goto end_loop_1;
		phrase_value_key = FIXNUM_LE(ISVREF(held_vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector_1,next_index_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index_1 & 
			(SI_Long)1023L);
		gensymed_symbol_2 = next_index_1 + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector_1,gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector_1,(gensymed_symbol_2 >>  
			-  - (SI_Long)10L) + (SI_Long)2L),
			gensymed_symbol_2 & (SI_Long)1023L);
		phrase_value_value = 
			validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index_1 = next_index_1 + (SI_Long)2L;
		if ( !(EQ(slot_value_key,phrase_value_key) && 
			compare_slot_value_to_parse_result_1(slot_value_value,
			phrase_value_value)))
		    return VALUES_1(Nil);
		goto next_loop_1;
	      end_loop_1:
		return VALUES_1(T);
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (compare_slot_value_to_parse_result_1(CAR(slot_value),
	    CAR(phrase_value)))
	return compare_slot_value_to_parse_result_1(CDR(slot_value),
		CDR(phrase_value));
    else
	return VALUES_1(Nil);
}

/* PLIST-EQUAL-P */
Object plist_equal_p(p1,p2)
    Object p1, p2;
{
    Object name, ab_loop_list_, temp, temp_1;
    char temp_2;

    x_note_fn_call(136,332);
    name = Nil;
    ab_loop_list_ = p1;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    name = CAR(ab_loop_list_);
    temp = getf(p1,name,_);
    temp_1 = getf(p2,name,_);
    if ( !EQUAL(temp,temp_1)) {
	temp_2 = TRUEP(Nil);
	goto end_1;
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp_2 = TRUEP(T);
    goto end_1;
    temp_2 = TRUEP(Qnil);
  end_1:;
    if (temp_2) {
	name = Nil;
	ab_loop_list_ = p2;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
      next_loop_1:
	name = CAR(ab_loop_list_);
	temp = getf(p1,name,_);
	temp_1 = getf(p2,name,_);
	if ( !EQUAL(temp,temp_1))
	    return VALUES_1(Nil);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qinitial_value;      /* initial-value */

static Object Qsymbolic_parameter;  /* symbolic-parameter */

/* SYMBOLIC-PARAMETER-INITIAL-VALUE-OVERRIDE */
Object symbolic_parameter_initial_value_override(override)
    Object override;
{
    Object temp;
    char temp_1;

    x_note_fn_call(136,333);
    if (CONSP(override)) {
	temp = CDR(override);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = CDDR(override);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? EQ(CAR(override),Qinitial_value) : TRUEP(Nil))
	return VALUES_1(EQ(CADR(override),Qsymbolic_parameter) ? T : Nil);
    else
	return VALUES_1(Nil);
}

void kb_save4_INIT()
{
    Object gensymed_symbol, run_traverse_kb_for_write_rdf_for_kb_1, temp;
    Object run_traverse_kb_for_make_xml_object_for_kb_1;
    Object run_traverse_kb_node_for_write_rdf_for_kb_1;
    Object run_traverse_kb_node_for_make_xml_object_for_kb_1;
    Object primitive_value_for_node_definition_for_write_rdf_for_kb_1;
    Object primitive_value_for_node_definition_for_make_xml_object_for_kb_1;
    Object reference_for_node_definition_for_write_rdf_for_kb_1;
    Object reference_for_node_definition_for_make_xml_object_for_kb_1;
    Object traverse_for_node_definition_for_write_rdf_for_kb_1;
    Object traverse_for_node_definition_for_make_xml_object_for_kb_1;
    Object run_traverse_kb_for_find_references_for_writing_1;
    Object run_traverse_kb_node_for_find_references_for_writing_1;
    Object traverse_for_node_definition_for_find_references_for_writing_1;
    Object reference_for_node_definition_for_find_references_for_writing_1;
    Object run_traverse_kb_for_find_stripped_text_slot_1;
    Object run_traverse_kb_node_for_find_stripped_text_slot_1;
    Object traverse_for_node_definition_for_find_stripped_text_slot_1;
    Object primitive_value_for_node_definition_for_find_stripped_text_slot_1;
    Object temp_1;
    Object AB_package, list_constant_29, Qinverse_of_relation, Qrelation_name;
    Object Qfilename_of_basis_kb, Qidentifier_of_basis_kb, list_constant_108;
    Object Qname_box, Qicon_variables, list_constant_109;
    Object Qrelation_is_permanent, Qrelation_is_symmetric, Qtype_of_relation;
    Object Qsecond_class, Qfirst_class, Qattribute_name, list_constant_107;
    Object Qrdf_col_Seq, Qset_default_window_position_and_scale;
    Object Qget_default_window_position_and_scale;
    Object Qinitial_default_window_position_and_scale, list_constant_106;
    Object list_constant_39, Qdefault_window_position_and_scale;
    Object list_constant_105, list_constant_37, Qab_or, list_constant_104;
    Object list_constant_103, list_constant_102, list_constant_101;
    Object list_constant_51, list_constant_50, list_constant_100;
    Object Qvirtual_attributes_local_to_class;
    Object Qminimum_scale_for_workspaces_as_float;
    Object Qminimum_scale_for_workspaces;
    Object Qmaximum_scale_for_workspaces_as_float;
    Object Qmaximum_scale_for_workspaces, Qget_connection_vertices;
    Object Qinitial_connection_vertices, list_constant_99, list_constant_96;
    Object Qconnection, Qget_connection_style, Qinitial_connection_style;
    Object list_constant_98, Qorthogonal, Qdiagonal, Qget_connection_output;
    Object Qinitial_connection_output, list_constant_97, Qget_connection_input;
    Object Qinitial_connection_input, list_constant_95, list_constant_94;
    Object list_constant_93, list_constant_92, list_constant_91;
    Object list_constant_90, list_constant_42, list_constant_89;
    Object list_constant_41, Qset_minimum_size_in_workspace;
    Object Qget_minimum_size_in_workspace, Qinitial_minimum_size_in_workspace;
    Object list_constant_88, list_constant_87, list_constant_86;
    Object list_constant_85, list_constant_84, list_constant_73;
    Object list_constant_83, list_constant_82, list_constant_81;
    Object list_constant_80, list_constant_79, list_constant_78;
    Object list_constant_77, list_constant_68, list_constant_67;
    Object list_constant_66, list_constant_65, list_constant_64, Qtype_in_box;
    Object Qset_size_in_workspace, Qget_size_in_workspace;
    Object Qinitial_size_in_workspace, list_constant_76, list_constant_75;
    Object list_constant_74, list_constant_72, list_constant_71;
    Object list_constant_70, list_constant_69, list_constant_63;
    Object list_constant_62, list_constant_61, list_constant_60;
    Object list_constant_59, list_constant_58, Qscrap, Qmessage;
    Object list_constant_57, Qborderless_free_text, Qfree_text;
    Object Qfreeform_table, Qreadout_table, Qgraph, Qtrend_chart, Qentity;
    Object Qset_following_item_in_workspace_layering;
    Object Qget_following_item_in_workspace_layering;
    Object Qinitial_following_item_in_workspace_layering, list_constant_40;
    Object list_constant_38, Qset_position_in_workspace;
    Object Qget_position_in_workspace, Qinitial_position_in_workspace;
    Object list_constant_56, list_constant_55, list_constant_54;
    Object list_constant_53, list_constant_52, Qset_edges_of_workspace;
    Object Qget_edges_of_workspace, Qinitial_edges_of_workspace;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_45, list_constant_44;
    Object list_constant_43, Qset_unused_area_color, Qget_unused_area_color;
    Object Qinitial_unused_area_color, Qunused_area_color;
    Object Qset_parent_of_subworkspace, Qget_parent_of_subworkspace;
    Object Qinitial_parent_of_subworkspace, Qno_item, Quser_password;
    Object Qmessage_change, Qconnection_change, Qobject_change;
    Object Qclass_definition_change, Qrelation_summary;
    Object Qjava_read_only_package_declaration;
    Object Qjava_read_only_import_declarations;
    Object Qjava_class_and_interface_names, Qinherited_attributes;
    Object Qgsi_variable_status_code, Qread_only_truth_value_data_type;
    Object Qread_only_text_data_type, Qread_only_symbol_data_type;
    Object Qread_only_positive_integer, Qformat_of_image, Qdepth_of_image;
    Object Qheight_of_image, Qwidth_of_image, Qg2_window_height;
    Object Qg2_window_width, Qg2_window_y, Qg2_window_x, Qdefault_junction;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_36;
    Object Qpackage_declaration, Qimport_declarations, Qgsi_variable_status;
    Object Qg2_window_y_resolution, Qg2_window_x_resolution, list_constant_35;
    Object Qkb_version_information_for_change_logging, Qframe_change_log;
    Object list_constant_34, Qsaved_as_minimum_size_in_workspace;
    Object list_constant_33, Qtraversal, list_constant_32, Qsupplied_as_the_id;
    Object list_constant_31, Qmedia_bin_data, Qcurrent_attribute_displays;
    Object Qtext_alignment, Qtext_font, Qg2_array_sequence, Qg2_list_sequence;
    Object Qtable_cells, Qvalues_for_table_of_values, Qhistory;
    Object Qvalue_structure, list_constant_30, Qobject_configuration;
    Object Qitem_configuration, Qicon_description;
    Object Qhistory_structure_using_unix_time;
    Object Qvalue_structure_using_unix_time, Qtext_color, Qborder_color;
    Object Qauthors, Qwrite_clear_text_kb, Qg2_compare_xml_objects;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_copy_xml_object_without_annotations;
    Object Qg2_copy_xml_object_with_annotations;
    Object Qg2_restore_module_from_xml_object, Qg2_save_module_into_xml_object;
    Object Qg2_read_xml_object_from_file, Qg2_write_xml_object_to_file;

    x_note_fn_call(136,334);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2_write_xml_object_to_file = 
	    STATIC_SYMBOL("G2-WRITE-XML-OBJECT-TO-FILE",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_write_xml_object_to_file,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_write_xml_object_to_file,
	    STATIC_FUNCTION(g2_write_xml_object_to_file,NIL,FALSE,2,2));
    Qg2_read_xml_object_from_file = 
	    STATIC_SYMBOL("G2-READ-XML-OBJECT-FROM-FILE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_read_xml_object_from_file,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_read_xml_object_from_file,
	    STATIC_FUNCTION(g2_read_xml_object_from_file,NIL,FALSE,1,1));
    Qg2_save_module_into_xml_object = 
	    STATIC_SYMBOL("G2-SAVE-MODULE-INTO-XML-OBJECT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_save_module_into_xml_object,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_save_module_into_xml_object,
	    STATIC_FUNCTION(g2_save_module_into_xml_object,NIL,FALSE,1,1));
    Qg2_restore_module_from_xml_object = 
	    STATIC_SYMBOL("G2-RESTORE-MODULE-FROM-XML-OBJECT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_restore_module_from_xml_object,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qrestore_xml_kb = STATIC_SYMBOL("RESTORE-XML-KB",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_restore_module_from_xml_object,
	    STATIC_FUNCTION(g2_restore_module_from_xml_object,NIL,FALSE,1,1));
    Qg2_copy_xml_object_with_annotations = 
	    STATIC_SYMBOL("G2-COPY-XML-OBJECT-WITH-ANNOTATIONS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_copy_xml_object_with_annotations,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_copy_xml_object_with_annotations,
	    STATIC_FUNCTION(g2_copy_xml_object_with_annotations,NIL,FALSE,
	    1,1));
    Qg2_copy_xml_object_without_annotations = 
	    STATIC_SYMBOL("G2-COPY-XML-OBJECT-WITHOUT-ANNOTATIONS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_copy_xml_object_without_annotations,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_copy_xml_object_without_annotations,
	    STATIC_FUNCTION(g2_copy_xml_object_without_annotations,NIL,
	    FALSE,1,1));
    Qg2_compare_xml_objects = STATIC_SYMBOL("G2-COMPARE-XML-OBJECTS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_compare_xml_objects,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_compare_xml_objects,
	    STATIC_FUNCTION(g2_compare_xml_objects,NIL,FALSE,3,3));
    if (Write_diffs_after_saving_clear_text_p == UNBOUND)
	Write_diffs_after_saving_clear_text_p = Nil;
    if (Write_checksums_in_xml_file_p == UNBOUND)
	Write_checksums_in_xml_file_p = T;
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_clear_text_kb = STATIC_SYMBOL("WRITE-CLEAR-TEXT-KB",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_clear_text_kb,
	    STATIC_FUNCTION(write_clear_text_kb,NIL,FALSE,0,0));
    array_constant_2 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    QAUTHOR = STATIC_SYMBOL("author",AB_package);
    QDATE = STATIC_SYMBOL("date",AB_package);
    Qget_xml_kb = STATIC_SYMBOL("GET-XML-KB",AB_package);
    QModule = STATIC_SYMBOL("Module",AB_package);
    QSYSTEMTABLES = STATIC_SYMBOL("systemtables",AB_package);
    Qtop_level_module = STATIC_SYMBOL("TOP-LEVEL-MODULE",AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,QModule,QSYSTEMTABLES,
	    FIX((SI_Long)0L),Qtop_level_module);
    if (Xml_output_stream == UNBOUND)
	Xml_output_stream = Nil;
    if (Length_of_xml_output_line == UNBOUND)
	Length_of_xml_output_line = FIX((SI_Long)0L);
    if (Xml_output_buffer == UNBOUND)
	Xml_output_buffer = Nil;
    if (Xml_output_position == UNBOUND)
	Xml_output_position = FIX((SI_Long)0L);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Show_deletions_in_xml_changes_p == UNBOUND)
	Show_deletions_in_xml_changes_p = Nil;
    string_constant = STATIC_STRING("~%<kbchanges");
    string_constant_1 = STATIC_STRING("~%  ~a=~s");
    string_constant_2 = STATIC_STRING(">");
    Qdeletion = STATIC_SYMBOL("DELETION",AB_package);
    string_constant_3 = STATIC_STRING("~%~%<delete rdf:resource=\"#~a\"/>");
    Qaddition = STATIC_SYMBOL("ADDITION",AB_package);
    string_constant_4 = STATIC_STRING("~%~%<add>");
    string_constant_5 = STATIC_STRING("~%</add>");
    Qattribute_deletion = STATIC_SYMBOL("ATTRIBUTE-DELETION",AB_package);
    Qattribute_addition = STATIC_SYMBOL("ATTRIBUTE-ADDITION",AB_package);
    Qchange = STATIC_SYMBOL("CHANGE",AB_package);
    string_constant_6 = STATIC_STRING("~%~%</kbchanges>~%~%");
    if (Write_xml_attribute_change_old_value_p == UNBOUND)
	Write_xml_attribute_change_old_value_p = Nil;
    string_constant_7 = STATIC_STRING("deleteattribute");
    string_constant_8 = STATIC_STRING("addattribute");
    string_constant_9 = STATIC_STRING("changeattribute");
    string_constant_10 = STATIC_STRING("~%~%<~a rdf:resource=\"#~a\">");
    string_constant_11 = STATIC_STRING("<element index=\"~d\">");
    string_constant_12 = STATIC_STRING("<~a>");
    string_constant_13 = STATIC_STRING("~%");
    string_constant_14 = STATIC_STRING("<OLDVALUE>");
    string_constant_15 = STATIC_STRING("</OLDVALUE>");
    string_constant_16 = STATIC_STRING("</element>");
    string_constant_17 = STATIC_STRING("</~a>");
    string_constant_18 = STATIC_STRING("~%</~a>");
    Qid = STATIC_SYMBOL("ID",AB_package);
    Qg2m = STATIC_SYMBOL("G2M",AB_package);
    if (Traversing_xml_object_p == UNBOUND)
	Traversing_xml_object_p = Nil;
    Qprimitive_value = STATIC_SYMBOL("PRIMITIVE-VALUE",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qunit = STATIC_SYMBOL("UNIT",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Quser_attribute_count = STATIC_SYMBOL("USER-ATTRIBUTE-COUNT",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qelements = STATIC_SYMBOL("ELEMENTS",AB_package);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    QRDF_COL_RESOURCE = STATIC_SYMBOL("rdf:resource",AB_package);
    Qbinary = STATIC_SYMBOL("BINARY",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qattr_not_found = STATIC_SYMBOL("ATTR-NOT-FOUND",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattr_not_found,Attr_not_found);
    if (Attr_not_found == UNBOUND)
	Attr_not_found = LIST_1(Qattr_not_found);
    if (Xml_object_changes == UNBOUND)
	Xml_object_changes = Nil;
    if (Compare_xml_collect_diffs_p == UNBOUND)
	Compare_xml_collect_diffs_p = Nil;
    Qconnection_input = STATIC_SYMBOL("CONNECTION-INPUT",AB_package);
    Qconnection_output = STATIC_SYMBOL("CONNECTION-OUTPUT",AB_package);
    Qcompare_xml_object_and_fixups = 
	    STATIC_SYMBOL("COMPARE-XML-OBJECT-AND-FIXUPS",AB_package);
    SET_SYMBOL_FUNCTION(Qcompare_xml_object_and_fixups,
	    STATIC_FUNCTION(compare_xml_object_and_fixups,NIL,FALSE,3,3));
    if (All_xml_checksums == UNBOUND)
	All_xml_checksums = Nil;
    if (Attribute_name_xml_checksum == UNBOUND)
	Attribute_name_xml_checksum = LIST_4(FIX((SI_Long)1L),Nil,Nil,Nil);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Qattribute_name_xml_checksum = 
	    STATIC_SYMBOL("ATTRIBUTE-NAME-XML-CHECKSUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_name_xml_checksum,
	    Attribute_name_xml_checksum);
    add_xml_checksum(Qattribute_name,Qattribute_name_xml_checksum);
    if (Uuid_xml_checksum == UNBOUND)
	Uuid_xml_checksum = LIST_4(FIX((SI_Long)2L),Nil,Nil,Nil);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Quuid_xml_checksum = STATIC_SYMBOL("UUID-XML-CHECKSUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quuid_xml_checksum,Uuid_xml_checksum);
    add_xml_checksum(Quuid,Quuid_xml_checksum);
    if (Value_xml_checksum == UNBOUND)
	Value_xml_checksum = LIST_4(FIX((SI_Long)3L),Nil,Nil,Nil);
    Qvalue_xml_checksum = STATIC_SYMBOL("VALUE-XML-CHECKSUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvalue_xml_checksum,Value_xml_checksum);
    add_xml_checksum(Qvalue,Qvalue_xml_checksum);
    if (Text_xml_checksum == UNBOUND)
	Text_xml_checksum = LIST_4(FIX((SI_Long)4L),Nil,Nil,Nil);
    Qtext_xml_checksum = STATIC_SYMBOL("TEXT-XML-CHECKSUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtext_xml_checksum,Text_xml_checksum);
    add_xml_checksum(Qtext,Qtext_xml_checksum);
    if (Binary_xml_checksum == UNBOUND)
	Binary_xml_checksum = LIST_4(FIX((SI_Long)5L),Nil,Nil,Nil);
    Qbinary_xml_checksum = STATIC_SYMBOL("BINARY-XML-CHECKSUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbinary_xml_checksum,Binary_xml_checksum);
    add_xml_checksum(Qbinary,Qbinary_xml_checksum);
    if (Xml_checksums_enabled_p == UNBOUND)
	Xml_checksums_enabled_p = Nil;
    if (Process_checksum_for_image_data_p == UNBOUND)
	Process_checksum_for_image_data_p = Nil;
    Debug_xml_checksums_p = Nil;
    Debug_clear_text_checksums = Nil;
    string_constant_19 = STATIC_STRING(";");
    string_constant_20 = STATIC_STRING("[[ ~d  ~s ]]");
    QCHECKSUMS = STATIC_SYMBOL("checksums",AB_package);
    Qmodule = STATIC_SYMBOL("MODULE",AB_package);
    Qimage_data = STATIC_SYMBOL("IMAGE-DATA",AB_package);
    Qsave_image_data_with_kb = STATIC_SYMBOL("SAVE-IMAGE-DATA-WITH-KB",
	    AB_package);
    if (G2binary_file_name == UNBOUND)
	G2binary_file_name = Nil;
    if (G2binary_file_stream == UNBOUND)
	G2binary_file_stream = Nil;
    if (G2binary_file_position == UNBOUND)
	G2binary_file_position = FIX((SI_Long)0L);
    if (Current_g2binary_file_symbol_index == UNBOUND)
	Current_g2binary_file_symbol_index = FIX((SI_Long)0L);
    if (G2binary_file_symbol_list == UNBOUND)
	G2binary_file_symbol_list = Nil;
    if (G2binary_file_symbol_index_space == UNBOUND)
	G2binary_file_symbol_index_space = Nil;
    Qg2binary_file_symbol_index = 
	    STATIC_SYMBOL("G2BINARY-FILE-SYMBOL-INDEX",AB_package);
    G2binary_file_symbol_index_prop = Qg2binary_file_symbol_index;
    if (Using_temporary_g2binary_file_symbol_indices_p == UNBOUND)
	Using_temporary_g2binary_file_symbol_indices_p = Nil;
    if (Temporary_g2binary_file_symbol_indices == UNBOUND)
	Temporary_g2binary_file_symbol_indices = Nil;
    string_constant_21 = STATIC_STRING("Could not open ~A for writing");
    string_constant_22 = STATIC_STRING("Could not open ~A for reading");
    string_constant_23 = STATIC_STRING("Error reading ~A: size error");
    string_constant_24 = STATIC_STRING("Error reading ~A: ~A");
    if (Remaining_bytes_in_g2binary_data == UNBOUND)
	Remaining_bytes_in_g2binary_data = Nil;
    array_constant_3 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    string_constant_25 = STATIC_STRING("Bad first 4 bytes");
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    string_constant_26 = STATIC_STRING("Binary stream not open");
    if (Clear_text_primitive_value_style == UNBOUND)
	Clear_text_primitive_value_style = Nil;
    if (In_write_module_as_clear_text_p == UNBOUND)
	In_write_module_as_clear_text_p = Nil;
    if (Call_check_node_attribute_value_p == UNBOUND)
	Call_check_node_attribute_value_p = Nil;
    if (Current_module_being_saved == UNBOUND)
	Current_module_being_saved = Nil;
    if (Writing_xml_p == UNBOUND)
	Writing_xml_p = Nil;
    if (Writing_xml_cdata_p == UNBOUND)
	Writing_xml_cdata_p = Nil;
    if (Kb_format_write_integer_buffer == UNBOUND)
	Kb_format_write_integer_buffer = make_string(1,FIX((SI_Long)12L));
    Qutf_8_gensym_string_with_newline = 
	    STATIC_SYMBOL("UTF-8-GENSYM-STRING-WITH-NEWLINE",AB_package);
    string_constant_27 = STATIC_STRING("&amp;");
    string_constant_28 = STATIC_STRING("&lt;");
    string_constant_29 = STATIC_STRING("&gt;");
    string_constant_30 = STATIC_STRING("&quot;");
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    string_constant_31 = STATIC_STRING("~a~a~a~a");
    string_constant_32 = STATIC_STRING("");
    string_constant_33 = STATIC_STRING("g2m");
    string_constant_34 = STATIC_STRING("g2");
    string_constant_35 = STATIC_STRING(":");
    string_constant_36 = STATIC_STRING(".");
    Qrdf_class_name = STATIC_SYMBOL("RDF-CLASS-NAME",AB_package);
    Qrdf_class_name_no_namespace = 
	    STATIC_SYMBOL("RDF-CLASS-NAME-NO-NAMESPACE",AB_package);
    string_constant_37 = STATIC_STRING("c");
    if (Writing_g2_rdf_file_p == UNBOUND)
	Writing_g2_rdf_file_p = Nil;
    Qg2_defstruct_structure_name_slot_description_g2_struct = 
	    STATIC_SYMBOL("SLOT-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qversion = STATIC_SYMBOL("VERSION",AB_package);
    string_constant_38 = STATIC_STRING("version");
    Qsystem_tables = STATIC_SYMBOL("SYSTEM-TABLES",AB_package);
    string_constant_39 = STATIC_STRING("systemtables");
    Qexternal_definitions = STATIC_SYMBOL("EXTERNAL-DEFINITIONS",AB_package);
    string_constant_40 = STATIC_STRING("externaldefinitions");
    Qformats = STATIC_SYMBOL("FORMATS",AB_package);
    string_constant_41 = STATIC_STRING("formats");
    Qpanes = STATIC_SYMBOL("PANES",AB_package);
    string_constant_42 = STATIC_STRING("panes");
    Qchecksums = STATIC_SYMBOL("CHECKSUMS",AB_package);
    string_constant_43 = STATIC_STRING("checksums");
    QVERSION = STATIC_SYMBOL("version",AB_package);
    QEXTERNALDEFINITIONS = STATIC_SYMBOL("externaldefinitions",AB_package);
    QFORMATS = STATIC_SYMBOL("formats",AB_package);
    QPANES = STATIC_SYMBOL("panes",AB_package);
    string_constant_44 = STATIC_STRING("g2:version");
    string_constant_45 = STATIC_STRING("g2:systemtables");
    string_constant_46 = STATIC_STRING("g2:externaldefinitions");
    string_constant_47 = STATIC_STRING("g2:formats");
    string_constant_48 = STATIC_STRING("g2:panes");
    string_constant_49 = STATIC_STRING("g2:checksums");
    Qrdf_structure_attribute_name = 
	    STATIC_SYMBOL("RDF-STRUCTURE-ATTRIBUTE-NAME",AB_package);
    Qrdf_structure_attribute_name_no_namespace = 
	    STATIC_SYMBOL("RDF-STRUCTURE-ATTRIBUTE-NAME-NO-NAMESPACE",
	    AB_package);
    string_constant_50 = STATIC_STRING("sa");
    Qrdf_qualified_attribute_name = 
	    STATIC_SYMBOL("RDF-QUALIFIED-ATTRIBUTE-NAME",AB_package);
    Qrdf_qualified_attribute_name_no_namespace = 
	    STATIC_SYMBOL("RDF-QUALIFIED-ATTRIBUTE-NAME-NO-NAMESPACE",
	    AB_package);
    string_constant_51 = STATIC_STRING("uq");
    Qrdf_user_attribute_name = STATIC_SYMBOL("RDF-USER-ATTRIBUTE-NAME",
	    AB_package);
    Qrdf_user_attribute_name_no_namespace = 
	    STATIC_SYMBOL("RDF-USER-ATTRIBUTE-NAME-NO-NAMESPACE",AB_package);
    string_constant_52 = STATIC_STRING("ua");
    Qrdf_system_attribute_name = STATIC_SYMBOL("RDF-SYSTEM-ATTRIBUTE-NAME",
	    AB_package);
    Qrdf_system_attribute_name_no_namespace = 
	    STATIC_SYMBOL("RDF-SYSTEM-ATTRIBUTE-NAME-NO-NAMESPACE",AB_package);
    string_constant_53 = STATIC_STRING("a");
    string_constant_54 = STATIC_STRING("<rdf:RDF~%");
    string_constant_55 = 
	    STATIC_STRING("  xmlns:rdf=\"http://www.w3.org/TR/WD-rdf-syntax#\"~%");
    string_constant_56 = 
	    STATIC_STRING("  xmlns:rdfs=\"http://www.w3.org/TR/WD-rdf-schema#\"~%");
    string_constant_57 = STATIC_STRING("  xmlns:g2=\"\">~%~%");
    string_constant_58 = STATIC_STRING("<rdf:Class rdf:ID=\"Module\">~%");
    string_constant_59 = 
	    STATIC_STRING("  <rdfs:subClassOf resource=\"http://www.w3.org/TR/WD-rdf-schema#Resource\"/>~%");
    string_constant_60 = STATIC_STRING("</rdf:Class>~%~%");
    string_constant_61 = 
	    STATIC_STRING("<rdf:Property ID=\"~a\" rdfs:domain=\"#Module\"/>~%");
    string_constant_88 = STATIC_STRING("RawValue");
    string_constant_90 = STATIC_STRING("Integer");
    string_constant_94 = STATIC_STRING("Float");
    string_constant_96 = STATIC_STRING("Symbol");
    string_constant_98 = STATIC_STRING("Text");
    string_constant_100 = STATIC_STRING("TruthValue");
    string_constant_82 = STATIC_STRING("Sequence");
    string_constant_84 = STATIC_STRING("Structure");
    list_constant_1 = STATIC_LIST((SI_Long)8L,string_constant_88,
	    string_constant_90,string_constant_94,string_constant_96,
	    string_constant_98,string_constant_100,string_constant_82,
	    string_constant_84);
    string_constant_62 = STATIC_STRING("<rdf:Class rdf:ID=\"~a\">~%");
    string_constant_63 = STATIC_STRING("<rdf:Property ID=\"type\"/>~%~%");
    string_constant_64 = STATIC_STRING("<rdf:Property ID=\"value\"/>~%~%");
    string_constant_65 = STATIC_STRING("<rdf:Property ID=\"unit\"/>~%~%");
    string_constant_66 = STATIC_STRING("<rdf:Class rdf:ID=\"G2Class\">~%");
    string_constant_67 = STATIC_STRING("<rdf:Class rdf:ID=\"G2Attribute\">~%");
    string_constant_68 = 
	    STATIC_STRING("  <rdfs:subClassOf resource=\"http://www.w3.org/TR/WD-rdf-schema#Property\"/>~%");
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    string_constant_69 = STATIC_STRING("<G2Class rdf:ID=\"~a\">~%");
    string_constant_70 = 
	    STATIC_STRING("  <rdfs:subClassOf resource=\"#~a\"/>~%");
    string_constant_71 = 
	    STATIC_STRING("  <rdfs:subClassOf resource=\"#G2Class\"/>~%");
    string_constant_72 = STATIC_STRING("</G2Class>~%~&");
    Qitem_or_evaluation_value = STATIC_SYMBOL("ITEM-OR-EVALUATION-VALUE",
	    AB_package);
    string_constant_73 = STATIC_STRING("<G2Attribute rdf:ID=\"~a\"/>~%");
    string_constant_74 = STATIC_STRING("</rdf:RDF>~%");
    G2_rdf_file_name = Nil;
    string_constant_75 = STATIC_STRING("prototype-");
    string_constant_76 = STATIC_STRING("alpha-");
    string_constant_77 = STATIC_STRING("beta-");
    string_constant_78 = STATIC_STRING("g2-~A~D-~D~A-~D~A~A.rdf");
    string_constant_79 = STATIC_STRING("-");
    string_constant_80 = STATIC_STRING("g2:Module");
    string_constant_81 = STATIC_STRING("g2:Sequence");
    string_constant_83 = STATIC_STRING("g2:Structure");
    string_constant_85 = STATIC_STRING("g2:BinaryData");
    string_constant_86 = STATIC_STRING("BinaryData");
    string_constant_87 = STATIC_STRING("g2:RawValue");
    string_constant_89 = STATIC_STRING("g2:Integer");
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    string_constant_91 = STATIC_STRING("g2:Long");
    string_constant_92 = STATIC_STRING("Long");
    string_constant_93 = STATIC_STRING("g2:Float");
    string_constant_95 = STATIC_STRING("g2:Symbol");
    string_constant_97 = STATIC_STRING("g2:Text");
    string_constant_99 = STATIC_STRING("g2:TruthValue");
    string_constant_101 = STATIC_STRING("rdf:li");
    string_constant_102 = STATIC_STRING("~D");
    string_constant_103 = STATIC_STRING("~A");
    string_constant_104 = STATIC_STRING("~(~A~).bkb");
    string_constant_105 = STATIC_STRING("#");
    Write_rdf_for_kb = make_array(1,FIX((SI_Long)5L));
    Make_xml_object_for_kb = make_array(1,FIX((SI_Long)5L));
    QXMLNS_COL_RDF = STATIC_SYMBOL("xmlns:rdf",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)57344L);
    QXMLNS_COL_G2 = STATIC_SYMBOL("xmlns:g2",AB_package);
    QXMLNS = STATIC_SYMBOL("xmlns",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    Qfile = STATIC_SYMBOL("FILE",AB_package);
    if (Run_traverse_kb_xml_object_type == UNBOUND)
	Run_traverse_kb_xml_object_type = Qfile;
    string_constant_106 = STATIC_STRING("<\?xml version=\"1.0\"\?>~%");
    string_constant_107 = STATIC_STRING("<rdf:RDF");
    string_constant_108 = STATIC_STRING("~% ~A=~S");
    string_constant_109 = STATIC_STRING(">~%");
    string_constant_110 = STATIC_STRING("~&</rdf:RDF>~%");
    run_traverse_kb_for_write_rdf_for_kb_1 = 
	    STATIC_FUNCTION(run_traverse_kb_for_write_rdf_for_kb,NIL,FALSE,
	    3,3);
    temp = Write_rdf_for_kb;
    SVREF(temp,FIX((SI_Long)0L)) = run_traverse_kb_for_write_rdf_for_kb_1;
    run_traverse_kb_for_make_xml_object_for_kb_1 = 
	    STATIC_FUNCTION(run_traverse_kb_for_make_xml_object_for_kb,NIL,
	    FALSE,3,3);
    temp = Make_xml_object_for_kb;
    SVREF(temp,FIX((SI_Long)0L)) = 
	    run_traverse_kb_for_make_xml_object_for_kb_1;
    string_constant_111 = STATIC_STRING("<~a ID=~s>");
    run_traverse_kb_node_for_write_rdf_for_kb_1 = 
	    STATIC_FUNCTION(run_traverse_kb_node_for_write_rdf_for_kb,NIL,
	    FALSE,4,4);
    temp = Write_rdf_for_kb;
    SVREF(temp,FIX((SI_Long)1L)) = run_traverse_kb_node_for_write_rdf_for_kb_1;
    Qcurrent_kb_save = STATIC_SYMBOL("CURRENT-KB-SAVE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_kb_save,Current_kb_save);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    run_traverse_kb_node_for_make_xml_object_for_kb_1 = 
	    STATIC_FUNCTION(run_traverse_kb_node_for_make_xml_object_for_kb,
	    NIL,FALSE,4,4);
    temp = Make_xml_object_for_kb;
    SVREF(temp,FIX((SI_Long)1L)) = 
	    run_traverse_kb_node_for_make_xml_object_for_kb_1;
    string_constant_112 = STATIC_STRING("~NV");
    Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute 
	    = 
	    STATIC_SYMBOL("TYPE-IS-ATTRIBUTE-OF-G2-ATTRIBUTE-AND-VALUE-IS-CONTENTS-OF-G2-ATTRIBUTE",
	    AB_package);
    string_constant_113 = STATIC_STRING("~@%");
    string_constant_114 = STATIC_STRING("<~a");
    string_constant_115 = STATIC_STRING(" g2:type=~s");
    string_constant_116 = STATIC_STRING(" g2:unit=~s");
    Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type = 
	    STATIC_SYMBOL("TYPE-IS-SUB-ELEMENT-OF-G2-ATTRIBUTE-AND-VALUE-IS-CONTENTS-OF-TYPE",
	    AB_package);
    string_constant_117 = STATIC_STRING("<~a/>");
    string_constant_118 = STATIC_STRING("<![CDATA[");
    string_constant_119 = STATIC_STRING("~a");
    string_constant_120 = STATIC_STRING("]]>");
    string_constant_121 = STATIC_STRING(" g2:value=~s/>");
    primitive_value_for_node_definition_for_write_rdf_for_kb_1 = 
	    STATIC_FUNCTION(primitive_value_for_node_definition_for_write_rdf_for_kb,
	    NIL,FALSE,8,8);
    temp = Write_rdf_for_kb;
    SVREF(temp,FIX((SI_Long)2L)) = 
	    primitive_value_for_node_definition_for_write_rdf_for_kb_1;
    primitive_value_for_node_definition_for_make_xml_object_for_kb_1 = 
	    STATIC_FUNCTION(primitive_value_for_node_definition_for_make_xml_object_for_kb,
	    NIL,FALSE,8,8);
    temp = Make_xml_object_for_kb;
    SVREF(temp,FIX((SI_Long)2L)) = 
	    primitive_value_for_node_definition_for_make_xml_object_for_kb_1;
    string_constant_122 = STATIC_STRING(" rdf:resource=~s/>");
    reference_for_node_definition_for_write_rdf_for_kb_1 = 
	    STATIC_FUNCTION(reference_for_node_definition_for_write_rdf_for_kb,
	    NIL,FALSE,8,8);
    temp = Write_rdf_for_kb;
    SVREF(temp,FIX((SI_Long)3L)) = 
	    reference_for_node_definition_for_write_rdf_for_kb_1;
    reference_for_node_definition_for_make_xml_object_for_kb_1 = 
	    STATIC_FUNCTION(reference_for_node_definition_for_make_xml_object_for_kb,
	    NIL,FALSE,8,8);
    temp = Make_xml_object_for_kb;
    SVREF(temp,FIX((SI_Long)3L)) = 
	    reference_for_node_definition_for_make_xml_object_for_kb_1;
    traverse_for_node_definition_for_write_rdf_for_kb_1 = 
	    STATIC_FUNCTION(traverse_for_node_definition_for_write_rdf_for_kb,
	    NIL,FALSE,8,8);
    temp = Write_rdf_for_kb;
    SVREF(temp,FIX((SI_Long)4L)) = 
	    traverse_for_node_definition_for_write_rdf_for_kb_1;
    traverse_for_node_definition_for_make_xml_object_for_kb_1 = 
	    STATIC_FUNCTION(traverse_for_node_definition_for_make_xml_object_for_kb,
	    NIL,FALSE,8,8);
    temp = Make_xml_object_for_kb;
    SVREF(temp,FIX((SI_Long)4L)) = 
	    traverse_for_node_definition_for_make_xml_object_for_kb_1;
    Find_references_for_writing = make_array(1,FIX((SI_Long)5L));
    run_traverse_kb_for_find_references_for_writing_1 = 
	    STATIC_FUNCTION(run_traverse_kb_for_find_references_for_writing,
	    NIL,FALSE,3,3);
    temp = Find_references_for_writing;
    SVREF(temp,FIX((SI_Long)0L)) = 
	    run_traverse_kb_for_find_references_for_writing_1;
    run_traverse_kb_node_for_find_references_for_writing_1 = 
	    STATIC_FUNCTION(run_traverse_kb_node_for_find_references_for_writing,
	    NIL,FALSE,4,4);
    temp = Find_references_for_writing;
    SVREF(temp,FIX((SI_Long)1L)) = 
	    run_traverse_kb_node_for_find_references_for_writing_1;
    traverse_for_node_definition_for_find_references_for_writing_1 = 
	    STATIC_FUNCTION(traverse_for_node_definition_for_find_references_for_writing,
	    NIL,FALSE,8,8);
    temp = Find_references_for_writing;
    SVREF(temp,FIX((SI_Long)4L)) = 
	    traverse_for_node_definition_for_find_references_for_writing_1;
    reference_for_node_definition_for_find_references_for_writing_1 = 
	    STATIC_FUNCTION(reference_for_node_definition_for_find_references_for_writing,
	    NIL,FALSE,8,8);
    temp = Find_references_for_writing;
    SVREF(temp,FIX((SI_Long)3L)) = 
	    reference_for_node_definition_for_find_references_for_writing_1;
    Qxml_primitive_value_style = STATIC_SYMBOL("XML-PRIMITIVE-VALUE-STYLE",
	    AB_package);
    Find_stripped_text_slot = make_array(1,FIX((SI_Long)5L));
    run_traverse_kb_for_find_stripped_text_slot_1 = 
	    STATIC_FUNCTION(run_traverse_kb_for_find_stripped_text_slot,
	    NIL,FALSE,3,3);
    temp = Find_stripped_text_slot;
    SVREF(temp,FIX((SI_Long)0L)) = 
	    run_traverse_kb_for_find_stripped_text_slot_1;
    run_traverse_kb_node_for_find_stripped_text_slot_1 = 
	    STATIC_FUNCTION(run_traverse_kb_node_for_find_stripped_text_slot,
	    NIL,FALSE,4,4);
    temp = Find_stripped_text_slot;
    SVREF(temp,FIX((SI_Long)1L)) = 
	    run_traverse_kb_node_for_find_stripped_text_slot_1;
    traverse_for_node_definition_for_find_stripped_text_slot_1 = 
	    STATIC_FUNCTION(traverse_for_node_definition_for_find_stripped_text_slot,
	    NIL,FALSE,8,8);
    temp = Find_stripped_text_slot;
    SVREF(temp,FIX((SI_Long)4L)) = 
	    traverse_for_node_definition_for_find_stripped_text_slot_1;
    Qfree = STATIC_SYMBOL("FREE",AB_package);
    Qfree_text_attribute = STATIC_SYMBOL("FREE-TEXT-ATTRIBUTE",AB_package);
    Qproprietary_package = STATIC_SYMBOL("PROPRIETARY-PACKAGE",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    Qtext_stripped = STATIC_SYMBOL("TEXT-STRIPPED",AB_package);
    Qproprietary = STATIC_SYMBOL("PROPRIETARY",AB_package);
    Qstripped_text_slot_search = STATIC_SYMBOL("STRIPPED-TEXT-SLOT-SEARCH",
	    AB_package);
    primitive_value_for_node_definition_for_find_stripped_text_slot_1 = 
	    STATIC_FUNCTION(primitive_value_for_node_definition_for_find_stripped_text_slot,
	    NIL,FALSE,8,8);
    temp = Find_stripped_text_slot;
    SVREF(temp,FIX((SI_Long)2L)) = 
	    primitive_value_for_node_definition_for_find_stripped_text_slot_1;
    if (In_find_stripped_text_slot_p == UNBOUND)
	In_find_stripped_text_slot_p = Nil;
    Qworkspaces = STATIC_SYMBOL("WORKSPACES",AB_package);
    if (Traversing_kb_attribute == UNBOUND)
	Traversing_kb_attribute = Nil;
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)6L,Qversion,Qsystem_tables,
	    Qexternal_definitions,Qformats,Qpanes,Qchecksums);
    if (All_classes_for_cached_class_description_node_attributes == UNBOUND)
	All_classes_for_cached_class_description_node_attributes = Nil;
    if (All_classes_for_cached_class_description_node_attributes_for_external_definition 
	    == UNBOUND)
	All_classes_for_cached_class_description_node_attributes_for_external_definition 
		= Nil;
    Qcached_class_node_attributes = 
	    STATIC_SYMBOL("CACHED-CLASS-NODE-ATTRIBUTES",AB_package);
    Cached_class_node_attributes_prop = Qcached_class_node_attributes;
    Qcached_class_node_attributes_for_external_definition = 
	    STATIC_SYMBOL("CACHED-CLASS-NODE-ATTRIBUTES-FOR-EXTERNAL-DEFINITION",
	    AB_package);
    Cached_class_node_attributes_for_external_definition_prop = 
	    Qcached_class_node_attributes_for_external_definition;
    if (Exclude_secondary_attributes == UNBOUND)
	Exclude_secondary_attributes = Nil;
    Qauthors = STATIC_SYMBOL("AUTHORS",AB_package);
    Qframe_author_or_authors = STATIC_SYMBOL("FRAME-AUTHOR-OR-AUTHORS",
	    AB_package);
    Qicon_variables = STATIC_SYMBOL("ICON-VARIABLES",AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qitem_color_pattern = STATIC_SYMBOL("ITEM-COLOR-PATTERN",AB_package);
    Qtext_alignment = STATIC_SYMBOL("TEXT-ALIGNMENT",AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qforeground_color = STATIC_SYMBOL("FOREGROUND-COLOR",AB_package);
    Qname_box = STATIC_SYMBOL("NAME-BOX",AB_package);
    Qcurrent_attribute_displays = 
	    STATIC_SYMBOL("CURRENT-ATTRIBUTE-DISPLAYS",AB_package);
    Qvalue_structure_using_unix_time = 
	    STATIC_SYMBOL("VALUE-STRUCTURE-USING-UNIX-TIME",AB_package);
    Qhistory_structure_using_unix_time = 
	    STATIC_SYMBOL("HISTORY-STRUCTURE-USING-UNIX-TIME",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qicon_description_for_class_qm = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-FOR-CLASS\?",AB_package);
    Qitem_configuration = STATIC_SYMBOL("ITEM-CONFIGURATION",AB_package);
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)18L,Qauthors,
	    Qframe_author_or_authors,Qicon_variables,Qicon_color,
	    Qitem_color_pattern,Qtext_alignment,Qborder_color,Qtext_color,
	    Qbackground_color,Qforeground_color,Qname_box,
	    Qcurrent_attribute_displays,Qvalue_structure_using_unix_time,
	    Qhistory_structure_using_unix_time,Qicon_description,
	    Qicon_description_for_class_qm,Qitem_configuration,
	    Qobject_configuration);
    Secondary_attributes = list_constant_30;
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qvalue_structure = STATIC_SYMBOL("VALUE-STRUCTURE",AB_package);
    Qhistory = STATIC_SYMBOL("HISTORY",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qvalue_structure,Qhistory);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qicon_variables,Qicon_color);
    Qrelationships = STATIC_SYMBOL("RELATIONSHIPS",AB_package);
    Qvalues_for_table_of_values = 
	    STATIC_SYMBOL("VALUES-FOR-TABLE-OF-VALUES",AB_package);
    Qtable_cells = STATIC_SYMBOL("TABLE-CELLS",AB_package);
    Qg2_list_sequence = STATIC_SYMBOL("G2-LIST-SEQUENCE",AB_package);
    Qg2_array_sequence = STATIC_SYMBOL("G2-ARRAY-SEQUENCE",AB_package);
    Qtext_font = STATIC_SYMBOL("TEXT-FONT",AB_package);
    Qmanually_disabled_qm = STATIC_SYMBOL("MANUALLY-DISABLED\?",AB_package);
    Qparent_of_subworkspace = STATIC_SYMBOL("PARENT-OF-SUBWORKSPACE",
	    AB_package);
    Qedges_of_workspace = STATIC_SYMBOL("EDGES-OF-WORKSPACE",AB_package);
    Qposition_in_workspace = STATIC_SYMBOL("POSITION-IN-WORKSPACE",AB_package);
    Qsize_in_workspace = STATIC_SYMBOL("SIZE-IN-WORKSPACE",AB_package);
    Qminimum_size_in_workspace = STATIC_SYMBOL("MINIMUM-SIZE-IN-WORKSPACE",
	    AB_package);
    Qicon_heading = STATIC_SYMBOL("ICON-HEADING",AB_package);
    Qicon_reflection = STATIC_SYMBOL("ICON-REFLECTION",AB_package);
    Qmedia_bin_data = STATIC_SYMBOL("MEDIA-BIN-DATA",AB_package);
    Qevaluation_attributes = STATIC_SYMBOL("EVALUATION-ATTRIBUTES",AB_package);
    Qstrip_text_mark = STATIC_SYMBOL("STRIP-TEXT-MARK",AB_package);
    Qdo_not_strip_text_mark = STATIC_SYMBOL("DO-NOT-STRIP-TEXT-MARK",
	    AB_package);
    Qdefault_window_position_and_scale = 
	    STATIC_SYMBOL("DEFAULT-WINDOW-POSITION-AND-SCALE",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)26L,Qrelationships,
	    Qvalues_for_table_of_values,Qtable_cells,Qg2_list_sequence,
	    Qg2_array_sequence,Qname_box,Qtext_font,Qtext_alignment,
	    Qcurrent_attribute_displays,Qitem_color_pattern,Qicon_color,
	    Qicon_variables,Qmanually_disabled_qm,Qparent_of_subworkspace,
	    Qedges_of_workspace,Qposition_in_workspace,Qsize_in_workspace,
	    Qminimum_size_in_workspace,Qicon_heading,Qicon_reflection,
	    Qimage_data,Qmedia_bin_data,Qevaluation_attributes,
	    Qstrip_text_mark,Qdo_not_strip_text_mark,
	    Qdefault_window_position_and_scale);
    Qfollowing_item_in_workspace_layering = 
	    STATIC_SYMBOL("FOLLOWING-ITEM-IN-WORKSPACE-LAYERING",AB_package);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qconnection_is_directed = STATIC_SYMBOL("CONNECTION-IS-DIRECTED",
	    AB_package);
    Qconnection_vertices = STATIC_SYMBOL("CONNECTION-VERTICES",AB_package);
    Qreason_to_exclude_slot_name = 
	    STATIC_SYMBOL("REASON-TO-EXCLUDE-SLOT-NAME",AB_package);
    Reason_to_exclude_slot_name_prop = Qreason_to_exclude_slot_name;
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    list_constant_31 = STATIC_CONS(Qsimulation_details,Qnil);
    set_reason_to_exclude_slot_names_1(Qnil,list_constant_31);
    Qsupplied_as_the_id = STATIC_SYMBOL("SUPPLIED-AS-THE-ID",AB_package);
    list_constant_32 = STATIC_CONS(Quuid,Qnil);
    set_reason_to_exclude_slot_names_1(Qsupplied_as_the_id,list_constant_32);
    Qtraversal = STATIC_SYMBOL("TRAVERSAL",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qsubworkspaces = STATIC_SYMBOL("SUBWORKSPACES",AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qslot_group_for_block_qm,
	    Qsubworkspaces);
    set_reason_to_exclude_slot_names_1(Qtraversal,list_constant_33);
    Qsaved_as_minimum_size_in_workspace = 
	    STATIC_SYMBOL("SAVED-AS-MINIMUM-SIZE-IN-WORKSPACE",AB_package);
    Qminimum_width_of_text_box = STATIC_SYMBOL("MINIMUM-WIDTH-OF-TEXT-BOX",
	    AB_package);
    Qminimum_height_of_text_box = 
	    STATIC_SYMBOL("MINIMUM-HEIGHT-OF-TEXT-BOX",AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qminimum_width_of_text_box,
	    Qminimum_height_of_text_box);
    set_reason_to_exclude_slot_names_1(Qsaved_as_minimum_size_in_workspace,
	    list_constant_34);
    Qnot_saved_in_clear_text = STATIC_SYMBOL("NOT-SAVED-IN-CLEAR-TEXT",
	    AB_package);
    Qidentifier_of_basis_kb = STATIC_SYMBOL("IDENTIFIER-OF-BASIS-KB",
	    AB_package);
    Qfilename_of_basis_kb = STATIC_SYMBOL("FILENAME-OF-BASIS-KB",AB_package);
    Qframe_change_log = STATIC_SYMBOL("FRAME-CHANGE-LOG",AB_package);
    Qkb_version_information_for_change_logging = 
	    STATIC_SYMBOL("KB-VERSION-INFORMATION-FOR-CHANGE-LOGGING",
	    AB_package);
    Qclear_text_history = STATIC_SYMBOL("CLEAR-TEXT-HISTORY",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)5L,Qidentifier_of_basis_kb,
	    Qfilename_of_basis_kb,Qframe_change_log,
	    Qkb_version_information_for_change_logging,Qclear_text_history);
    set_reason_to_exclude_slot_names_1(Qnot_saved_in_clear_text,
	    list_constant_35);
    Qdependant = STATIC_SYMBOL("DEPENDANT",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qg2_window_width = STATIC_SYMBOL("G2-WINDOW-WIDTH",AB_package);
    Qg2_window_height = STATIC_SYMBOL("G2-WINDOW-HEIGHT",AB_package);
    Qwidth_of_image = STATIC_SYMBOL("WIDTH-OF-IMAGE",AB_package);
    Qheight_of_image = STATIC_SYMBOL("HEIGHT-OF-IMAGE",AB_package);
    Qdepth_of_image = STATIC_SYMBOL("DEPTH-OF-IMAGE",AB_package);
    Qformat_of_image = STATIC_SYMBOL("FORMAT-OF-IMAGE",AB_package);
    Qg2_window_x = STATIC_SYMBOL("G2-WINDOW-X",AB_package);
    Qg2_window_y = STATIC_SYMBOL("G2-WINDOW-Y",AB_package);
    Qg2_window_x_resolution = STATIC_SYMBOL("G2-WINDOW-X-RESOLUTION",
	    AB_package);
    Qg2_window_y_resolution = STATIC_SYMBOL("G2-WINDOW-Y-RESOLUTION",
	    AB_package);
    Qgsi_variable_status = STATIC_SYMBOL("GSI-VARIABLE-STATUS",AB_package);
    Qinherited_attributes = STATIC_SYMBOL("INHERITED-ATTRIBUTES",AB_package);
    Qjava_class_and_interface_names = 
	    STATIC_SYMBOL("JAVA-CLASS-AND-INTERFACE-NAMES",AB_package);
    Qimport_declarations = STATIC_SYMBOL("IMPORT-DECLARATIONS",AB_package);
    Qpackage_declaration = STATIC_SYMBOL("PACKAGE-DECLARATION",AB_package);
    Qrelation_summary = STATIC_SYMBOL("RELATION-SUMMARY",AB_package);
    Quser_password = STATIC_SYMBOL("USER-PASSWORD",AB_package);
    Qprocedure_method_name = STATIC_SYMBOL("PROCEDURE-METHOD-NAME",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)22L,Qframe_status_and_notes,
	    Qg2_window_width,Qg2_window_height,Qwidth_of_image,
	    Qheight_of_image,Qdepth_of_image,Qformat_of_image,Qg2_window_x,
	    Qg2_window_y,Qg2_window_width,Qg2_window_height,
	    Qg2_window_x_resolution,Qg2_window_y_resolution,
	    Qgsi_variable_status,Qinherited_attributes,
	    Qjava_class_and_interface_names,Qimport_declarations,
	    Qpackage_declaration,Qrelation_summary,Qchange,Quser_password,
	    Qprocedure_method_name);
    set_reason_to_exclude_slot_names_1(Qdependant,list_constant_36);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qline_pattern = STATIC_SYMBOL("LINE-PATTERN",AB_package);
    Qconnection_arrows = STATIC_SYMBOL("CONNECTION-ARROWS",AB_package);
    Qnot_savable = STATIC_SYMBOL("NOT-SAVABLE",AB_package);
    Qno_type = STATIC_SYMBOL("NO-TYPE",AB_package);
    Qpreviously_put_in_attribute_tables = 
	    STATIC_SYMBOL("PREVIOUSLY-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    Qdepreciated = STATIC_SYMBOL("DEPRECIATED",AB_package);
    Qno_category_in_type_specification = 
	    STATIC_SYMBOL("NO-CATEGORY-IN-TYPE-SPECIFICATION",AB_package);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    Qdata_type_of_variable_or_parameter = 
	    STATIC_SYMBOL("DATA-TYPE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qread_only_symbol_data_type = 
	    STATIC_SYMBOL("READ-ONLY-SYMBOL-DATA-TYPE",AB_package);
    Qread_only_text_data_type = STATIC_SYMBOL("READ-ONLY-TEXT-DATA-TYPE",
	    AB_package);
    Qread_only_truth_value_data_type = 
	    STATIC_SYMBOL("READ-ONLY-TRUTH-VALUE-DATA-TYPE",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qread_only_symbol_data_type,
	    Qread_only_text_data_type,Qread_only_truth_value_data_type);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    Qneither_rw_cei_nor_slot_value_writer = 
	    STATIC_SYMBOL("NEITHER-RW-CEI-NOR-SLOT-VALUE-WRITER",AB_package);
    Qg2_defstruct_structure_name_virtual_attribute_g2_struct = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmajor_version = STATIC_SYMBOL("MAJOR-VERSION",AB_package);
    Qminor_version = STATIC_SYMBOL("MINOR-VERSION",AB_package);
    Qrelease_quality = STATIC_SYMBOL("RELEASE-QUALITY",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    Qrevision = STATIC_SYMBOL("REVISION",AB_package);
    Qbuild_identification = STATIC_SYMBOL("BUILD-IDENTIFICATION",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qdefault_junction = STATIC_SYMBOL("DEFAULT-JUNCTION",AB_package);
    list_constant_7 = STATIC_CONS(Qdefault_junction,Qnil);
    Qframe_edit_timestamp_qm = STATIC_SYMBOL("FRAME-EDIT-TIMESTAMP\?",
	    AB_package);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qraw = STATIC_SYMBOL("RAW",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)9L,Qframe_status_and_notes,
	    Qg2_window_x,Qg2_window_y,Qg2_window_width,Qg2_window_height,
	    Qwidth_of_image,Qheight_of_image,Qdepth_of_image,Qformat_of_image);
    Qicon_slot_group = STATIC_SYMBOL("ICON-SLOT-GROUP",AB_package);
    Qread_only_positive_integer = 
	    STATIC_SYMBOL("READ-ONLY-POSITIVE-INTEGER",AB_package);
    Qgsi_variable_status_code = STATIC_SYMBOL("GSI-VARIABLE-STATUS-CODE",
	    AB_package);
    Qjava_read_only_import_declarations = 
	    STATIC_SYMBOL("JAVA-READ-ONLY-IMPORT-DECLARATIONS",AB_package);
    Qjava_read_only_package_declaration = 
	    STATIC_SYMBOL("JAVA-READ-ONLY-PACKAGE-DECLARATION",AB_package);
    Qclass_definition_change = STATIC_SYMBOL("CLASS-DEFINITION-CHANGE",
	    AB_package);
    Qobject_change = STATIC_SYMBOL("OBJECT-CHANGE",AB_package);
    Qconnection_change = STATIC_SYMBOL("CONNECTION-CHANGE",AB_package);
    Qmessage_change = STATIC_SYMBOL("MESSAGE-CHANGE",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)16L,Qread_only_positive_integer,
	    Qread_only_symbol_data_type,Qread_only_text_data_type,
	    Qread_only_truth_value_data_type,Qgsi_variable_status_code,
	    Qinherited_attributes,Qjava_class_and_interface_names,
	    Qjava_read_only_import_declarations,
	    Qjava_read_only_package_declaration,Qrelation_summary,
	    Qstatement,Qclass_definition_change,Qobject_change,
	    Qconnection_change,Qmessage_change,Quser_password);
    Qsystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",AB_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    if (Kb_restrictions_names == UNBOUND)
	Kb_restrictions_names = Nil;
    Qkb_configuration = STATIC_SYMBOL("KB-CONFIGURATION",AB_package);
    Qkb_restrictions = STATIC_SYMBOL("KB-RESTRICTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_restrictions,Kb_restrictions);
    Qnames = STATIC_SYMBOL("NAMES",AB_package);
    Qattribute_initializations = STATIC_SYMBOL("ATTRIBUTE-INITIALIZATIONS",
	    AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qforeground_color,
	    Qbackground_color);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qmay_refer_to_inactive_items = 
	    STATIC_SYMBOL("MAY-REFER-TO-INACTIVE-ITEMS",AB_package);
    Qmay_run_while_inactive = STATIC_SYMBOL("MAY-RUN-WHILE-INACTIVE",
	    AB_package);
    Qserver_parameters = STATIC_SYMBOL("SERVER-PARAMETERS",AB_package);
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qx_in_workspace = STATIC_SYMBOL("X-IN-WORKSPACE",AB_package);
    Qy_in_workspace = STATIC_SYMBOL("Y-IN-WORKSPACE",AB_package);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Qitem_uuid_lt = STATIC_SYMBOL("ITEM-UUID<",AB_package);
    SET_SYMBOL_FUNCTION(Qitem_uuid_lt,STATIC_FUNCTION(item_uuid_lt,NIL,
	    FALSE,2,2));
    Qtable_item = STATIC_SYMBOL("TABLE-ITEM",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qnil,Qstatement);
    temp = CONS(Qparent_of_subworkspace,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qkb_workspace),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qparent_of_subworkspace,temp_1);
    set_property_value_function(get_symbol_properties_function(Qkb_workspace),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qab_class,Qkb_workspace);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_37 = STATIC_CONS(Qno_item,Qnil);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qab_class,Qblock);
    list_constant_40 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_37,
	    list_constant_38);
    Qinitial_parent_of_subworkspace = 
	    STATIC_SYMBOL("INITIAL-PARENT-OF-SUBWORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_parent_of_subworkspace,
	    STATIC_FUNCTION(initial_parent_of_subworkspace,NIL,FALSE,1,1));
    Qget_parent_of_subworkspace = 
	    STATIC_SYMBOL("GET-PARENT-OF-SUBWORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_parent_of_subworkspace,
	    STATIC_FUNCTION(get_parent_of_subworkspace,NIL,FALSE,1,1));
    Qset_parent_of_subworkspace = 
	    STATIC_SYMBOL("SET-PARENT-OF-SUBWORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_parent_of_subworkspace,
	    STATIC_FUNCTION(set_parent_of_subworkspace,NIL,FALSE,2,2));
    add_virtual_attribute(Qparent_of_subworkspace,list_constant_39,
	    list_constant_40,Qnil,
	    SYMBOL_FUNCTION(Qinitial_parent_of_subworkspace),
	    SYMBOL_FUNCTION(Qget_parent_of_subworkspace),
	    SYMBOL_FUNCTION(Qset_parent_of_subworkspace));
    Qunused_area_color = STATIC_SYMBOL("UNUSED-AREA-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qunused_area_color,
	    STATIC_FUNCTION(unused_area_color,NIL,FALSE,1,1));
    temp = CONS(Qunused_area_color,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qkb_workspace),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qunused_area_color,temp_1);
    set_property_value_function(get_symbol_properties_function(Qkb_workspace),
	    Qvirtual_attributes_local_to_class,temp);
    Qunused_area_color_qm = STATIC_SYMBOL("UNUSED-AREA-COLOR\?",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qcolor_value_vector_index_and_intensity = 
	    STATIC_SYMBOL("COLOR-VALUE-VECTOR-INDEX-AND-INTENSITY",AB_package);
    Qsame_as_workspace = STATIC_SYMBOL("SAME-AS-WORKSPACE",AB_package);
    string_constant_123 = 
	    STATIC_STRING("Unused-area-color must be a color name, DEFAULT, or SAME-AS-WORKSPACE, not ~NF.");
    list_constant_41 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_37,
	    Qsymbol);
    Qinitial_unused_area_color = STATIC_SYMBOL("INITIAL-UNUSED-AREA-COLOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_unused_area_color,
	    STATIC_FUNCTION(initial_unused_area_color,NIL,FALSE,1,1));
    Qget_unused_area_color = STATIC_SYMBOL("GET-UNUSED-AREA-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qget_unused_area_color,
	    STATIC_FUNCTION(get_unused_area_color,NIL,FALSE,1,1));
    Qset_unused_area_color = STATIC_SYMBOL("SET-UNUSED-AREA-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qset_unused_area_color,
	    STATIC_FUNCTION(set_unused_area_color,NIL,FALSE,2,2));
    add_virtual_attribute(Qunused_area_color,list_constant_39,
	    list_constant_41,Qnil,
	    SYMBOL_FUNCTION(Qinitial_unused_area_color),
	    SYMBOL_FUNCTION(Qget_unused_area_color),
	    SYMBOL_FUNCTION(Qset_unused_area_color));
    temp = CONS(Qedges_of_workspace,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qkb_workspace),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qedges_of_workspace,temp_1);
    set_property_value_function(get_symbol_properties_function(Qkb_workspace),
	    Qvirtual_attributes_local_to_class,temp);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    list_constant_42 = STATIC_CONS(Qinteger,Qnil);
    list_constant_43 = STATIC_CONS(Qleft,list_constant_42);
    list_constant_44 = STATIC_CONS(Qtop,list_constant_42);
    list_constant_45 = STATIC_CONS(Qright,list_constant_42);
    list_constant_46 = STATIC_CONS(Qbottom,list_constant_42);
    list_constant_47 = STATIC_LIST((SI_Long)4L,list_constant_43,
	    list_constant_44,list_constant_45,list_constant_46);
    list_constant_48 = STATIC_LIST((SI_Long)5L,Qand,Qleft,Qtop,Qright,Qbottom);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_47,list_constant_48);
    Qinitial_edges_of_workspace = 
	    STATIC_SYMBOL("INITIAL-EDGES-OF-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_edges_of_workspace,
	    STATIC_FUNCTION(initial_edges_of_workspace,NIL,FALSE,1,1));
    Qget_edges_of_workspace = STATIC_SYMBOL("GET-EDGES-OF-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_edges_of_workspace,
	    STATIC_FUNCTION(get_edges_of_workspace,NIL,FALSE,1,1));
    Qset_edges_of_workspace = STATIC_SYMBOL("SET-EDGES-OF-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_edges_of_workspace,
	    STATIC_FUNCTION(set_edges_of_workspace,NIL,FALSE,2,2));
    add_virtual_attribute(Qedges_of_workspace,list_constant_39,
	    list_constant_49,Qnil,
	    SYMBOL_FUNCTION(Qinitial_edges_of_workspace),
	    SYMBOL_FUNCTION(Qget_edges_of_workspace),
	    SYMBOL_FUNCTION(Qset_edges_of_workspace));
    temp = CONS(Qposition_in_workspace,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qposition_in_workspace,temp_1);
    set_property_value_function(get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,temp);
    Qx = STATIC_SYMBOL("X",AB_package);
    Qy = STATIC_SYMBOL("Y",AB_package);
    Qsuperior = STATIC_SYMBOL("SUPERIOR",AB_package);
    list_constant_50 = STATIC_CONS(Qx,list_constant_42);
    list_constant_51 = STATIC_CONS(Qy,list_constant_42);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qsuperior,list_constant_39);
    list_constant_53 = STATIC_LIST((SI_Long)3L,list_constant_50,
	    list_constant_51,list_constant_52);
    list_constant_54 = STATIC_LIST((SI_Long)4L,Qand,Qx,Qy,Qsuperior);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_53,list_constant_54);
    list_constant_56 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_37,
	    list_constant_55);
    Qinitial_position_in_workspace = 
	    STATIC_SYMBOL("INITIAL-POSITION-IN-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_position_in_workspace,
	    STATIC_FUNCTION(initial_position_in_workspace,NIL,FALSE,1,1));
    Qget_position_in_workspace = STATIC_SYMBOL("GET-POSITION-IN-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_position_in_workspace,
	    STATIC_FUNCTION(get_position_in_workspace,NIL,FALSE,1,1));
    Qset_position_in_workspace = STATIC_SYMBOL("SET-POSITION-IN-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_position_in_workspace,
	    STATIC_FUNCTION(set_position_in_workspace,NIL,FALSE,2,2));
    add_virtual_attribute(Qposition_in_workspace,list_constant_38,
	    list_constant_56,Qnil,
	    SYMBOL_FUNCTION(Qinitial_position_in_workspace),
	    SYMBOL_FUNCTION(Qget_position_in_workspace),
	    SYMBOL_FUNCTION(Qset_position_in_workspace));
    temp = CONS(Qfollowing_item_in_workspace_layering,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qfollowing_item_in_workspace_layering,temp_1);
    set_property_value_function(get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,temp);
    Qlayering_information_for_clear_text = 
	    STATIC_SYMBOL("LAYERING-INFORMATION-FOR-CLEAR-TEXT",AB_package);
    string_constant_124 = 
	    STATIC_STRING("Can not set following-item-in-workspace-layering for ~NF");
    Qinitial_following_item_in_workspace_layering = 
	    STATIC_SYMBOL("INITIAL-FOLLOWING-ITEM-IN-WORKSPACE-LAYERING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_following_item_in_workspace_layering,
	    STATIC_FUNCTION(initial_following_item_in_workspace_layering,
	    NIL,FALSE,1,1));
    Qget_following_item_in_workspace_layering = 
	    STATIC_SYMBOL("GET-FOLLOWING-ITEM-IN-WORKSPACE-LAYERING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_following_item_in_workspace_layering,
	    STATIC_FUNCTION(get_following_item_in_workspace_layering,NIL,
	    FALSE,1,1));
    Qset_following_item_in_workspace_layering = 
	    STATIC_SYMBOL("SET-FOLLOWING-ITEM-IN-WORKSPACE-LAYERING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_following_item_in_workspace_layering,
	    STATIC_FUNCTION(set_following_item_in_workspace_layering,NIL,
	    FALSE,2,2));
    add_virtual_attribute(Qfollowing_item_in_workspace_layering,
	    list_constant_38,list_constant_40,Qnil,
	    SYMBOL_FUNCTION(Qinitial_following_item_in_workspace_layering),
	    SYMBOL_FUNCTION(Qget_following_item_in_workspace_layering),
	    SYMBOL_FUNCTION(Qset_following_item_in_workspace_layering));
    temp = CONS(Qsize_in_workspace,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qsize_in_workspace,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    string_constant_125 = STATIC_STRING("The width, ~D, must be positive");
    string_constant_126 = STATIC_STRING("The height, ~D, must be positive");
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qab_class,Qentity);
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qab_class,Qchart);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qab_class,Qtrend_chart);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qab_class,Qgraph);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qab_class,Qreadout_table);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qab_class,Qfreeform_table);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qab_class,Qfree_text);
    Qborderless_free_text = STATIC_SYMBOL("BORDERLESS-FREE-TEXT",AB_package);
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qborderless_free_text);
    list_constant_57 = STATIC_CONS(Qstatement,Qnil);
    list_constant_66 = STATIC_CONS(Qab_class,list_constant_57);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qab_class,Qmessage);
    Qscrap = STATIC_SYMBOL("SCRAP",AB_package);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qab_class,Qscrap);
    list_constant_75 = STATIC_LIST((SI_Long)12L,Qab_or,list_constant_58,
	    list_constant_59,list_constant_60,list_constant_61,
	    list_constant_62,list_constant_63,list_constant_64,
	    list_constant_65,list_constant_66,list_constant_67,
	    list_constant_68);
    list_constant_69 = STATIC_CONS(Qnumber,Qnil);
    list_constant_70 = STATIC_CONS(Qwidth,list_constant_69);
    list_constant_71 = STATIC_CONS(Qheight,list_constant_69);
    list_constant_72 = STATIC_LIST((SI_Long)2L,list_constant_70,
	    list_constant_71);
    list_constant_73 = STATIC_LIST((SI_Long)3L,Qand,Qwidth,Qheight);
    list_constant_74 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_72,list_constant_73);
    list_constant_76 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_37,
	    list_constant_74);
    Qinitial_size_in_workspace = STATIC_SYMBOL("INITIAL-SIZE-IN-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_size_in_workspace,
	    STATIC_FUNCTION(initial_size_in_workspace,NIL,FALSE,1,1));
    Qget_size_in_workspace = STATIC_SYMBOL("GET-SIZE-IN-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_size_in_workspace,
	    STATIC_FUNCTION(get_size_in_workspace,NIL,FALSE,1,1));
    Qset_size_in_workspace = STATIC_SYMBOL("SET-SIZE-IN-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_size_in_workspace,
	    STATIC_FUNCTION(set_size_in_workspace,NIL,FALSE,2,2));
    add_virtual_attribute(Qsize_in_workspace,list_constant_75,
	    list_constant_76,Qnil,
	    SYMBOL_FUNCTION(Qinitial_size_in_workspace),
	    SYMBOL_FUNCTION(Qget_size_in_workspace),
	    SYMBOL_FUNCTION(Qset_size_in_workspace));
    temp = CONS(Qminimum_size_in_workspace,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qminimum_size_in_workspace,
	    Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qtype_in_box = STATIC_SYMBOL("TYPE-IN-BOX",AB_package);
    list_constant_77 = STATIC_LIST((SI_Long)2L,Qab_class,Qtype_in_box);
    list_constant_78 = STATIC_LIST((SI_Long)5L,list_constant_64,
	    list_constant_65,list_constant_66,list_constant_67,
	    list_constant_68);
    list_constant_87 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_77,list_constant_78);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qmember,Qnone);
    list_constant_80 = STATIC_LIST((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_79);
    list_constant_81 = STATIC_CONS(list_constant_80,Qnil);
    list_constant_82 = STATIC_CONS(Qwidth,list_constant_81);
    list_constant_83 = STATIC_CONS(Qheight,list_constant_81);
    list_constant_84 = STATIC_LIST((SI_Long)2L,list_constant_82,
	    list_constant_83);
    list_constant_85 = STATIC_CONS(list_constant_73,Qnil);
    list_constant_86 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_84,list_constant_85);
    list_constant_88 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_37,
	    list_constant_86);
    Qinitial_minimum_size_in_workspace = 
	    STATIC_SYMBOL("INITIAL-MINIMUM-SIZE-IN-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_minimum_size_in_workspace,
	    STATIC_FUNCTION(initial_minimum_size_in_workspace,NIL,FALSE,1,1));
    Qget_minimum_size_in_workspace = 
	    STATIC_SYMBOL("GET-MINIMUM-SIZE-IN-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_minimum_size_in_workspace,
	    STATIC_FUNCTION(get_minimum_size_in_workspace,NIL,FALSE,1,1));
    Qset_minimum_size_in_workspace = 
	    STATIC_SYMBOL("SET-MINIMUM-SIZE-IN-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_minimum_size_in_workspace,
	    STATIC_FUNCTION(set_minimum_size_in_workspace,NIL,FALSE,2,2));
    add_virtual_attribute(Qminimum_size_in_workspace,list_constant_87,
	    list_constant_88,Qnil,
	    SYMBOL_FUNCTION(Qinitial_minimum_size_in_workspace),
	    SYMBOL_FUNCTION(Qget_minimum_size_in_workspace),
	    SYMBOL_FUNCTION(Qset_minimum_size_in_workspace));
    temp = CONS(Qconnection_input,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qconnection_input,temp_1);
    set_property_value_function(get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,temp);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    list_constant_96 = STATIC_LIST((SI_Long)2L,Qab_class,Qconnection);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_90 = STATIC_LIST((SI_Long)2L,Qitem,list_constant_27);
    Qport_name = STATIC_SYMBOL("PORT-NAME",AB_package);
    list_constant_91 = STATIC_LIST((SI_Long)2L,Qport_name,list_constant_41);
    Qside = STATIC_SYMBOL("SIDE",AB_package);
    list_constant_89 = STATIC_LIST((SI_Long)5L,Qmember,Qtop,Qbottom,Qleft,
	    Qright);
    list_constant_92 = STATIC_LIST((SI_Long)2L,Qside,list_constant_89);
    list_constant_93 = STATIC_CONS(Qposition,list_constant_42);
    list_constant_94 = STATIC_LIST((SI_Long)4L,list_constant_90,
	    list_constant_91,list_constant_92,list_constant_93);
    list_constant_95 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_94);
    list_constant_97 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_37,
	    list_constant_95);
    Qinitial_connection_input = STATIC_SYMBOL("INITIAL-CONNECTION-INPUT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_connection_input,
	    STATIC_FUNCTION(initial_connection_input,NIL,FALSE,1,1));
    Qget_connection_input = STATIC_SYMBOL("GET-CONNECTION-INPUT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_connection_input,
	    STATIC_FUNCTION(get_connection_input,NIL,FALSE,1,1));
    add_virtual_attribute(Qconnection_input,list_constant_96,
	    list_constant_97,Qnil,
	    SYMBOL_FUNCTION(Qinitial_connection_input),
	    SYMBOL_FUNCTION(Qget_connection_input),Nil);
    temp = CONS(Qconnection_output,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qconnection_output,temp_1);
    set_property_value_function(get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,temp);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qinitial_connection_output = STATIC_SYMBOL("INITIAL-CONNECTION-OUTPUT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_connection_output,
	    STATIC_FUNCTION(initial_connection_output,NIL,FALSE,1,1));
    Qget_connection_output = STATIC_SYMBOL("GET-CONNECTION-OUTPUT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_connection_output,
	    STATIC_FUNCTION(get_connection_output,NIL,FALSE,1,1));
    add_virtual_attribute(Qconnection_output,list_constant_96,
	    list_constant_97,Qnil,
	    SYMBOL_FUNCTION(Qinitial_connection_output),
	    SYMBOL_FUNCTION(Qget_connection_output),Nil);
    array_constant_13 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    ISASET_1(array_constant_13,(SI_Long)0L,Qtop);
    ISASET_1(array_constant_13,(SI_Long)1L,Qleft);
    ISASET_1(array_constant_13,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant_13,(SI_Long)3L,Qright);
    temp = CONS(Qconnection_style,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qconnection_style,temp_1);
    set_property_value_function(get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,temp);
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    Qorthogonal = STATIC_SYMBOL("ORTHOGONAL",AB_package);
    list_constant_98 = STATIC_LIST((SI_Long)3L,Qmember,Qdiagonal,Qorthogonal);
    Qinitial_connection_style = STATIC_SYMBOL("INITIAL-CONNECTION-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_connection_style,
	    STATIC_FUNCTION(initial_connection_style,NIL,FALSE,1,1));
    Qget_connection_style = STATIC_SYMBOL("GET-CONNECTION-STYLE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_connection_style,
	    STATIC_FUNCTION(get_connection_style,NIL,FALSE,1,1));
    add_virtual_attribute(Qconnection_style,list_constant_96,
	    list_constant_98,Qnil,
	    SYMBOL_FUNCTION(Qinitial_connection_style),
	    SYMBOL_FUNCTION(Qget_connection_style),Nil);
    temp = CONS(Qconnection_vertices,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qconnection_vertices,temp_1);
    set_property_value_function(get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_99 = STATIC_LIST((SI_Long)3L,Qsequence,Qinteger,
	    FIX((SI_Long)1L));
    Qinitial_connection_vertices = 
	    STATIC_SYMBOL("INITIAL-CONNECTION-VERTICES",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_connection_vertices,
	    STATIC_FUNCTION(initial_connection_vertices,NIL,FALSE,1,1));
    Qget_connection_vertices = STATIC_SYMBOL("GET-CONNECTION-VERTICES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_connection_vertices,
	    STATIC_FUNCTION(get_connection_vertices,NIL,FALSE,1,1));
    add_virtual_attribute(Qconnection_vertices,list_constant_96,
	    list_constant_99,Qnil,
	    SYMBOL_FUNCTION(Qinitial_connection_vertices),
	    SYMBOL_FUNCTION(Qget_connection_vertices),Nil);
    Qmaximum_scale_for_workspaces = 
	    STATIC_SYMBOL("MAXIMUM-SCALE-FOR-WORKSPACES",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_scale_for_workspaces,FIX((SI_Long)16384L));
    Qmaximum_scale_for_workspaces_as_float = 
	    STATIC_SYMBOL("MAXIMUM-SCALE-FOR-WORKSPACES-AS-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_scale_for_workspaces_as_float,
	    Maximum_scale_for_workspaces_as_float);
    SET_SYMBOL_VALUE(Qmaximum_scale_for_workspaces_as_float,
	    DOUBLE_TO_DOUBLE_FLOAT(16384.0 / (double)(SI_Long)4096L));
    Qminimum_scale_for_workspaces = 
	    STATIC_SYMBOL("MINIMUM-SCALE-FOR-WORKSPACES",AB_package);
    SET_SYMBOL_VALUE(Qminimum_scale_for_workspaces,FIX((SI_Long)32L));
    Qminimum_scale_for_workspaces_as_float = 
	    STATIC_SYMBOL("MINIMUM-SCALE-FOR-WORKSPACES-AS-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_scale_for_workspaces_as_float,
	    Minimum_scale_for_workspaces_as_float);
    SET_SYMBOL_VALUE(Qminimum_scale_for_workspaces_as_float,
	    DOUBLE_TO_DOUBLE_FLOAT(32.0 / (double)(SI_Long)4096L));
    string_constant_127 = 
	    STATIC_STRING("The value for ~a, ~d, is outside the valid range ~d to ~d.");
    string_constant_128 = STATIC_STRING("Illegal value for ~a: ~nv");
    string_constant_129 = 
	    STATIC_STRING("The value for ~a, ~F, is outside the valid range ~f to ~f.");
    string_constant_130 = STATIC_STRING("none");
    string_constant_131 = 
	    STATIC_STRING("The value for x-scale/y-scale, ~NF and ~NF, must either both be specified or both left unspecified.");
    temp = CONS(Qdefault_window_position_and_scale,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qkb_workspace),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qdefault_window_position_and_scale,temp_1);
    set_property_value_function(get_symbol_properties_function(Qkb_workspace),
	    Qvirtual_attributes_local_to_class,temp);
    Qdetail_pane = STATIC_SYMBOL("DETAIL-PANE",AB_package);
    Qx_scale = STATIC_SYMBOL("X-SCALE",AB_package);
    Qy_scale = STATIC_SYMBOL("Y-SCALE",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    list_constant_100 = STATIC_CONS(Qfloat,Qnil);
    list_constant_101 = STATIC_CONS(Qx_scale,list_constant_100);
    list_constant_102 = STATIC_CONS(Qy_scale,list_constant_100);
    list_constant_103 = STATIC_LIST((SI_Long)4L,list_constant_50,
	    list_constant_51,list_constant_101,list_constant_102);
    list_constant_104 = STATIC_LIST((SI_Long)3L,Qand,Qx,Qy);
    list_constant_105 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_103,list_constant_104);
    list_constant_106 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_37,
	    list_constant_105);
    Qinitial_default_window_position_and_scale = 
	    STATIC_SYMBOL("INITIAL-DEFAULT-WINDOW-POSITION-AND-SCALE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_default_window_position_and_scale,
	    STATIC_FUNCTION(initial_default_window_position_and_scale,NIL,
	    FALSE,1,1));
    Qget_default_window_position_and_scale = 
	    STATIC_SYMBOL("GET-DEFAULT-WINDOW-POSITION-AND-SCALE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_default_window_position_and_scale,
	    STATIC_FUNCTION(get_default_window_position_and_scale,NIL,
	    FALSE,1,1));
    Qset_default_window_position_and_scale = 
	    STATIC_SYMBOL("SET-DEFAULT-WINDOW-POSITION-AND-SCALE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_default_window_position_and_scale,
	    STATIC_FUNCTION(set_default_window_position_and_scale,NIL,
	    FALSE,2,2));
    add_virtual_attribute(Qdefault_window_position_and_scale,
	    list_constant_39,list_constant_106,Qnil,
	    SYMBOL_FUNCTION(Qinitial_default_window_position_and_scale),
	    SYMBOL_FUNCTION(Qget_default_window_position_and_scale),
	    SYMBOL_FUNCTION(Qset_default_window_position_and_scale));
    if (Classes_sorted_so_far == UNBOUND)
	Classes_sorted_so_far = Nil;
    if (Classes_remaining_to_sort == UNBOUND)
	Classes_remaining_to_sort = Nil;
    if (All_classes_for_indirectly_referenced_class == UNBOUND)
	All_classes_for_indirectly_referenced_class = Nil;
    Qindirectly_referenced_class_p = 
	    STATIC_SYMBOL("INDIRECTLY-REFERENCED-CLASS-P",AB_package);
    Indirectly_referenced_class_p_prop = Qindirectly_referenced_class_p;
    if (All_formats_in_module == UNBOUND)
	All_formats_in_module = Nil;
    if (Reading_initial_plist_for_clear_text_kb == UNBOUND)
	Reading_initial_plist_for_clear_text_kb = Nil;
    string_constant_132 = 
	    STATIC_STRING("Error reading ~A: no module information");
    if (Current_g2_rdf_module == UNBOUND)
	Current_g2_rdf_module = Nil;
    if (Read_xml_line == UNBOUND)
	Read_xml_line = FIX((SI_Long)0L);
    if (Read_kb_next_character == UNBOUND)
	Read_kb_next_character = Nil;
    Qxml_nil = STATIC_SYMBOL("XML-NIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qxml_nil,Xml_nil);
    if (Xml_nil == UNBOUND)
	Xml_nil = LIST_1(Qxml_nil);
    Read_xml_context_string_width = FIX((SI_Long)48L);
    string_constant_133 = STATIC_STRING("~%[line: ~D, context: ");
    string_constant_134 = STATIC_STRING(" ~S");
    string_constant_135 = STATIC_STRING(" ~A");
    string_constant_136 = STATIC_STRING("]");
    string_constant_137 = STATIC_STRING("End of file");
    string_constant_138 = STATIC_STRING("Malformed XML comment");
    list_constant_12 = STATIC_LIST((SI_Long)6L,FIX((SI_Long)67L),
	    FIX((SI_Long)68L),FIX((SI_Long)65L),FIX((SI_Long)84L),
	    FIX((SI_Long)65L),FIX((SI_Long)91L));
    string_constant_139 = STATIC_STRING("Malformed XML CDATA");
    string_constant_140 = STATIC_STRING("Expecting >");
    string_constant_141 = STATIC_STRING("</~a> was seen at top level");
    string_constant_142 = STATIC_STRING("Expecting </~a>, but found </~a>");
    Qg2_col_Module = STATIC_SYMBOL("g2:Module",AB_package);
    string_constant_143 = STATIC_STRING("Bad module id");
    Qg2_col_Sequence = STATIC_SYMBOL("g2:Sequence",AB_package);
    Qg2_col_Structure = STATIC_SYMBOL("g2:Structure",AB_package);
    Qrdf_col_Seq = STATIC_SYMBOL("rdf:Seq",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qg2_col_Sequence,
	    Qg2_col_Structure,Qrdf_col_Seq);
    string_constant_144 = STATIC_STRING("Malformed ~A");
    Qg2_col_c_dot_MODULE_INFORMATION = 
	    STATIC_SYMBOL("g2:c.MODULE-INFORMATION",AB_package);
    Qkb_name = STATIC_SYMBOL("KB-NAME",AB_package);
    Qrequired_modules = STATIC_SYMBOL("REQUIRED-MODULES",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qkb_name,Qtop_level_module,
	    Qrequired_modules);
    Qdirectly_required_modules = STATIC_SYMBOL("DIRECTLY-REQUIRED-MODULES",
	    AB_package);
    QG2_COL_TYPE = STATIC_SYMBOL("g2:type",AB_package);
    QG2_COL_UNIT = STATIC_SYMBOL("g2:unit",AB_package);
    QG2_COL_VALUE = STATIC_SYMBOL("g2:value",AB_package);
    array_constant_14 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    Qg2_col_RawValue = STATIC_SYMBOL("g2:RawValue",AB_package);
    array_constant_16 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)57344L);
    Qg2_col_BinaryData = STATIC_SYMBOL("g2:BinaryData",AB_package);
    array_constant_17 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)57344L);
    Qg2_col_Integer = STATIC_SYMBOL("g2:Integer",AB_package);
    array_constant_18 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)57344L);
    Qg2_col_Long = STATIC_SYMBOL("g2:Long",AB_package);
    array_constant_19 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)57344L);
    Qg2_col_Float = STATIC_SYMBOL("g2:Float",AB_package);
    array_constant_20 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)57344L);
    Qg2_col_Text = STATIC_SYMBOL("g2:Text",AB_package);
    array_constant_21 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    Qg2_col_Symbol = STATIC_SYMBOL("g2:Symbol",AB_package);
    array_constant_22 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)57344L);
    Qg2_col_TruthValue = STATIC_SYMBOL("g2:TruthValue",AB_package);
    array_constant_23 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)57344L);
    float_constant = STATIC_FLOAT(0.0);
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    string_constant_145 = STATIC_STRING("Missing g2:value attribute");
    string_constant_146 = STATIC_STRING("g2:");
    string_constant_147 = STATIC_STRING("g2m:");
    string_constant_148 = STATIC_STRING("c.");
    string_constant_149 = STATIC_STRING("a.");
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    string_constant_150 = STATIC_STRING("ua.");
    Quser_attribute = STATIC_SYMBOL("USER-ATTRIBUTE",AB_package);
    string_constant_151 = STATIC_STRING("uq.");
    Qqualified_attribute = STATIC_SYMBOL("QUALIFIED-ATTRIBUTE",AB_package);
    string_constant_152 = STATIC_STRING("sa.");
    Qstructure_attribute = STATIC_SYMBOL("STRUCTURE-ATTRIBUTE",AB_package);
    Qsymbol_from_rdf_symbol_name = 
	    STATIC_SYMBOL("SYMBOL-FROM-RDF-SYMBOL-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qsymbol_from_rdf_symbol_name,
	    STATIC_FUNCTION(symbol_from_rdf_symbol_name,NIL,FALSE,1,1));
    string_constant_153 = STATIC_STRING("Expected >");
    string_constant_154 = STATIC_STRING("Expected =");
    string_constant_155 = STATIC_STRING("Expected an attribute, /, or >");
    QAMP = STATIC_SYMBOL("amp",AB_package);
    QLT = STATIC_SYMBOL("lt",AB_package);
    QGT = STATIC_SYMBOL("gt",AB_package);
    QQUOT = STATIC_SYMBOL("quot",AB_package);
    string_constant_156 = 
	    STATIC_STRING("Unrecognized character reference \"&~a;\"");
    string_constant_157 = STATIC_STRING("Expected \";\"");
    string_constant_158 = STATIC_STRING("Expected \" or \'");
    if (Most_recent_xml_checksum_differences == UNBOUND)
	Most_recent_xml_checksum_differences = Nil;
    Qname_text_string_for_kb_being_read = 
	    STATIC_SYMBOL("NAME-TEXT-STRING-FOR-KB-BEING-READ",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qname_text_string_for_kb_being_read,
	    Name_text_string_for_kb_being_read);
    string_constant_159 = STATIC_STRING("Checksum Error in ~A: ~(~L,A~)");
    string_constant_160 = STATIC_STRING("Checksum Error: ~(~L,A~)");
    if (Current_module_data == UNBOUND)
	Current_module_data = Nil;
    if (Initialize_items_count == UNBOUND)
	Initialize_items_count = Nil;
    if (Delayed_item_array_initializations == UNBOUND)
	Delayed_item_array_initializations = Nil;
    if (Delay_item_array_initializations_p == UNBOUND)
	Delay_item_array_initializations_p = Nil;
    if (Initializing_clear_text_p == UNBOUND)
	Initializing_clear_text_p = Nil;
    if (Externaldefinitions_fixups == UNBOUND)
	Externaldefinitions_fixups = Nil;
    if (Systemtables_fixups == UNBOUND)
	Systemtables_fixups = Nil;
    if (Systemtables_are_initialized_p == UNBOUND)
	Systemtables_are_initialized_p = Nil;
    if (Kb_window_for_initializing_definitions == UNBOUND)
	Kb_window_for_initializing_definitions = Nil;
    if (Clear_text_item_layering_info == UNBOUND)
	Clear_text_item_layering_info = Nil;
    Qmodule_assignment = STATIC_SYMBOL("MODULE-ASSIGNMENT",AB_package);
    Qsystem_has_paused = STATIC_SYMBOL("SYSTEM-HAS-PAUSED",AB_package);
    Qdetail_pane_description = STATIC_SYMBOL("DETAIL-PANE-DESCRIPTION",
	    AB_package);
    if (Definitions_in_module == UNBOUND)
	Definitions_in_module = Nil;
    if (Definitions_in_module_to_go == UNBOUND)
	Definitions_in_module_to_go = Nil;
    if (In_external_definitions_for_module_p == UNBOUND)
	In_external_definitions_for_module_p = Nil;
    Qab_class_name = STATIC_SYMBOL("CLASS-NAME",AB_package);
    Qdirect_superior_classes = STATIC_SYMBOL("DIRECT-SUPERIOR-CLASSES",
	    AB_package);
    Qclass_specific_attributes = STATIC_SYMBOL("CLASS-SPECIFIC-ATTRIBUTES",
	    AB_package);
    Qattribute_initial_item_class = 
	    STATIC_SYMBOL("ATTRIBUTE-INITIAL-ITEM-CLASS",AB_package);
    if (May_create_simulation_subtable_from_module_data_p == UNBOUND)
	May_create_simulation_subtable_from_module_data_p = Nil;
    Qtext_cell_plist_for_text_box = 
	    STATIC_SYMBOL("TEXT-CELL-PLIST-FOR-TEXT-BOX",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)10L,Qab_class,Qid,
	    QRDF_COL_RESOURCE,Qconnection_input,Qconnection_output,
	    Qconnection_style,Qconnection_vertices,Qconnection_is_directed,
	    Qfollowing_item_in_workspace_layering,Qrelationships);
    Qitem_reference_parameters = STATIC_SYMBOL("ITEM-REFERENCE-PARAMETERS",
	    AB_package);
    Qmiscellaneous_parameters = STATIC_SYMBOL("MISCELLANEOUS-PARAMETERS",
	    AB_package);
    list_constant_107 = STATIC_CONS(FIX((SI_Long)16L),Qnil);
    list_constant_16 = STATIC_LIST_STAR((SI_Long)5L,FIX((SI_Long)1L),
	    FIX((SI_Long)2L),FIX((SI_Long)4L),FIX((SI_Long)8L),
	    list_constant_107);
    list_constant_17 = STATIC_LIST((SI_Long)5L,Qt,Qattribute_name,Quuid,
	    Qvalue,Qtext);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    list_constant_108 = STATIC_CONS(Qrelationships,Qnil);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)15L,Qab_class_name,
	    Qab_class,Qid,QRDF_COL_RESOURCE,Qparent_of_subworkspace,
	    Qedges_of_workspace,Qposition_in_workspace,Qicon_variables,
	    Qicon_reflection,Qicon_heading,Qsize_in_workspace,
	    Qminimum_size_in_workspace,
	    Qfollowing_item_in_workspace_layering,Qname_box,list_constant_108);
    Qfirst_class = STATIC_SYMBOL("FIRST-CLASS",AB_package);
    Qsecond_class = STATIC_SYMBOL("SECOND-CLASS",AB_package);
    Qrelation_name = STATIC_SYMBOL("RELATION-NAME",AB_package);
    Qinverse_of_relation = STATIC_SYMBOL("INVERSE-OF-RELATION",AB_package);
    Qtype_of_relation = STATIC_SYMBOL("TYPE-OF-RELATION",AB_package);
    Qrelation_is_symmetric = STATIC_SYMBOL("RELATION-IS-SYMMETRIC",AB_package);
    Qrelation_is_permanent = STATIC_SYMBOL("RELATION-IS-PERMANENT",AB_package);
    list_constant_109 = STATIC_LIST((SI_Long)7L,Qfirst_class,Qsecond_class,
	    Qrelation_name,Qinverse_of_relation,Qtype_of_relation,
	    Qrelation_is_symmetric,Qrelation_is_permanent);
    Relation_attributes = list_constant_109;
    list_constant_19 = STATIC_CONS(Qtext,Qnil);
    Units_of_measure_declaration_attributes = list_constant_19;
    Qunits_of_measure_declaration = 
	    STATIC_SYMBOL("UNITS-OF-MEASURE-DECLARATION",AB_package);
    Qnon_action_button = STATIC_SYMBOL("NON-ACTION-BUTTON",AB_package);
    list_constant_20 = STATIC_CONS(Qfollowing_item_in_workspace_layering,Qnil);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qlayer_position_of_block = STATIC_SYMBOL("LAYER-POSITION-OF-BLOCK",
	    AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)8L,Qposition_in_workspace,
	    Qicon_variables,Qicon_reflection,Qicon_heading,
	    Qsize_in_workspace,Qminimum_size_in_workspace,
	    Qparent_of_subworkspace,Qedges_of_workspace);
    Qoptions = STATIC_SYMBOL("OPTIONS",AB_package);
    list_constant_22 = STATIC_CONS(Qoptions,Qnil);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)9L,
	    Qparent_of_subworkspace,Qedges_of_workspace,Qsize_in_workspace,
	    Qminimum_size_in_workspace,Qposition_in_workspace,
	    Qicon_variables,Qicon_reflection,Qicon_heading,list_constant_20);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)9L,Qab_class,Qid,
	    QRDF_COL_RESOURCE,Qconnection_input,Qconnection_output,
	    Qconnection_style,Qconnection_vertices,Qconnection_is_directed,
	    list_constant_108);
    list_constant_25 = STATIC_CONS(Qname_box,list_constant_108);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qidentifier_of_basis_kb,
	    Qfilename_of_basis_kb);
    Qsimulation_frame_qm = STATIC_SYMBOL("SIMULATION-FRAME\?",AB_package);
    string_constant_161 = STATIC_STRING("Illegal simulation-details");
    string_constant_162 = STATIC_STRING("Illegal text value");
    Qg2_array_initial_values = STATIC_SYMBOL("G2-ARRAY-INITIAL-VALUES",
	    AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qrelation_name,
	    Qinverse_of_relation);
    if (Clear_text_saving_problems_were_encountered_p == UNBOUND)
	Clear_text_saving_problems_were_encountered_p = Nil;
    array_constant_24 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)23L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)25L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)27L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)28L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)37L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)38L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)47L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_29,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)57344L);
    string_constant_163 = STATIC_STRING("Save");
    string_constant_164 = STATIC_STRING("Load");
    string_constant_165 = STATIC_STRING("~A problem: ~A");
    string_constant_166 = 
	    STATIC_STRING("~A problem when making ~NF be the ~S of ~NF: ~A");
    string_constant_167 = 
	    STATIC_STRING("~A problem when making ~NV be the ~S of ~NF: ~A");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qinitial_values = STATIC_SYMBOL("INITIAL-VALUES",AB_package);
    if (Allow_comparison_of_slot_value_to_parse_result == UNBOUND)
	Allow_comparison_of_slot_value_to_parse_result = Nil;
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    string_constant_168 = 
	    STATIC_STRING("Slot value does not match compiled result.~\n                              ~%  ~A ~A~%  ~A~%  ~A");
    Qdefault_message_properties = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES",AB_package);
    Qdefault_overrides = STATIC_SYMBOL("DEFAULT-OVERRIDES",AB_package);
    Qchart_annotations = STATIC_SYMBOL("CHART-ANNOTATIONS",AB_package);
    Qlog_file_name = STATIC_SYMBOL("LOG-FILE-NAME",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    Qsymbolic_parameter = STATIC_SYMBOL("SYMBOLIC-PARAMETER",AB_package);
}
