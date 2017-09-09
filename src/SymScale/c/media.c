/* media.c
 * Input file:  media.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "media.h"


static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qimage_definition;   /* image-definition */

static Object Qimage_definition_media_bin;  /* image-definition-media-bin */

/* CLEANUP-FOR-MEDIA-BIN */
Object cleanup_for_media_bin(media_bin)
    Object media_bin;
{
    Object owner_qm, gensymed_symbol, x, y, xa, ya, gensymed_symbol_1;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(229,0);
    owner_qm = ISVREF(media_bin,(SI_Long)23L);
    if (owner_qm) {
	gensymed_symbol = ISVREF(owner_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(owner_qm) ? EQ(ISVREF(owner_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(media_bin,(SI_Long)24L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(owner_qm,(SI_Long)1L);
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qimage_definition,
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
	if (temp) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(owner_qm,Qimage_definition_media_bin);
	    return set_lookup_slot_value_1(owner_qm,
		    Qimage_definition_media_bin,Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmedia_bin_data;     /* media-bin-data */

static Object Qab_directory;       /* directory */

/* INITIALIZE-FOR-MEDIA-BIN */
Object initialize_for_media_bin(media_bin)
    Object media_bin;
{
    Object wide_string_bv16, svref_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(229,1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(media_bin,Qmedia_bin_data);
    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = (SI_Long)0L & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
    svref_new_value = make_media_file(Qab_directory,wide_string_bv16);
    return VALUES_1(SVREF(media_bin,FIX((SI_Long)20L)) = svref_new_value);
}

/* RECLAIM-MEDIA-BIN-OWNER?-VALUE */
Object reclaim_media_bin_owner_qm_value(owner,media_bin)
    Object owner, media_bin;
{
    x_note_fn_call(229,2);
    ISVREF(media_bin,(SI_Long)23L) = Nil;
    reclaim_frame_serial_number(ISVREF(media_bin,(SI_Long)24L));
    ISVREF(media_bin,(SI_Long)24L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-MEDIA-BIN-OWNER-SERIAL-VALUE */
Object reclaim_media_bin_owner_serial_value(serial_number,gensymed_symbol)
    Object serial_number, gensymed_symbol;
{
    x_note_fn_call(229,3);
    return VALUES_1(Nil);
}

/* MAKE-MEDIA-FILE-1 */
Object make_media_file_1(type,name,status,size,contents,binary_odd_p,
	    create_date)
    Object type, name, status, size, contents, binary_odd_p, create_date;
{
    Object file, svref_arg_1;

    x_note_fn_call(229,4);
    file = allocate_managed_array(1,FIX((SI_Long)8L));
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)2L)) = type;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)0L)) = type;
    }
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)3L)) = name;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)1L)) = name;
    }
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)4L)) = status;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)2L)) = status;
    }
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)5L)) = size;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = size;
    }
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)6L)) = contents;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)4L)) = contents;
    }
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)9L)) = binary_odd_p;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)7L)) = binary_odd_p;
    }
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)8L)) = create_date;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)6L)) = create_date;
    }
    return VALUES_1(file);
}

static Object Qnormal;             /* normal */

static Object Qnew;                /* new */

static Object Qfloat_array;        /* float-array */

/* MAKE-MEDIA-FILE */
Object make_media_file(type,name)
    Object type, name;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(229,5);
    temp = EQ(type,Qab_directory) ? Qnormal : Qnew;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp_1 = Vector_of_simple_float_array_pools;
	temp_2 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
    aref_new_value = g2ext_unix_time_as_float();
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return make_media_file_1(type,name,temp,FIX((SI_Long)0L),Nil,Nil,
	    new_float);
}

Object The_type_description_of_media_stream = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_media_streams, Qchain_of_available_media_streams);

DEFINE_VARIABLE_WITH_SYMBOL(Media_stream_count, Qmedia_stream_count);

Object Chain_of_available_media_streams_vector = UNBOUND;

/* MEDIA-STREAM-STRUCTURE-MEMORY-USAGE */
Object media_stream_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(229,6);
    temp = Media_stream_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-MEDIA-STREAM-COUNT */
Object outstanding_media_stream_count()
{
    Object def_structure_media_stream_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(229,7);
    gensymed_symbol = IFIX(Media_stream_count);
    def_structure_media_stream_variable = Chain_of_available_media_streams;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_media_stream_variable))
	goto end_loop;
    def_structure_media_stream_variable = 
	    ISVREF(def_structure_media_stream_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-MEDIA-STREAM-1 */
Object reclaim_media_stream_1(media_stream)
    Object media_stream;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(229,8);
    inline_note_reclaim_cons(media_stream,Nil);
    structure_being_reclaimed = media_stream;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_media_file_location(ISVREF(media_stream,(SI_Long)2L));
      SVREF(media_stream,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_media_streams_vector,
	    IFIX(Current_thread_index));
    SVREF(media_stream,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_media_streams_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = media_stream;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-MEDIA-STREAM */
Object reclaim_structure_for_media_stream(media_stream)
    Object media_stream;
{
    x_note_fn_call(229,9);
    return reclaim_media_stream_1(media_stream);
}

static Object Qg2_defstruct_structure_name_media_stream_g2_struct;  /* g2-defstruct-structure-name::media-stream-g2-struct */

/* MAKE-PERMANENT-MEDIA-STREAM-STRUCTURE-INTERNAL */
Object make_permanent_media_stream_structure_internal()
{
    Object def_structure_media_stream_variable;
    Object defstruct_g2_media_stream_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(229,10);
    def_structure_media_stream_variable = Nil;
    atomic_incff_symval(Qmedia_stream_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_media_stream_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_media_stream_variable = the_array;
	SVREF(defstruct_g2_media_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_media_stream_g2_struct;
	def_structure_media_stream_variable = 
		defstruct_g2_media_stream_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_media_stream_variable);
}

/* MAKE-MEDIA-STREAM-1 */
Object make_media_stream_1(media_stream_file_descriptor,
	    media_stream_location,media_stream_file,media_stream_direction)
    Object media_stream_file_descriptor, media_stream_location;
    Object media_stream_file, media_stream_direction;
{
    Object def_structure_media_stream_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(229,11);
    def_structure_media_stream_variable = 
	    ISVREF(Chain_of_available_media_streams_vector,
	    IFIX(Current_thread_index));
    if (def_structure_media_stream_variable) {
	svref_arg_1 = Chain_of_available_media_streams_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_media_stream_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_media_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_media_stream_g2_struct;
    }
    else
	def_structure_media_stream_variable = 
		make_permanent_media_stream_structure_internal();
    inline_note_allocate_cons(def_structure_media_stream_variable,Nil);
    SVREF(def_structure_media_stream_variable,FIX((SI_Long)1L)) = 
	    media_stream_file_descriptor;
    SVREF(def_structure_media_stream_variable,FIX((SI_Long)2L)) = 
	    media_stream_location;
    SVREF(def_structure_media_stream_variable,FIX((SI_Long)3L)) = 
	    media_stream_file;
    SVREF(def_structure_media_stream_variable,FIX((SI_Long)4L)) = 
	    media_stream_direction;
    SVREF(def_structure_media_stream_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_media_stream_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_media_stream_variable);
}

/* MEDIA-STREAM-P-FUNCTION */
Object media_stream_p_function(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(229,12);
    temp = SIMPLE_VECTOR_P(thing) ? (EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_media_stream_g2_struct) ? T : 
	    Nil) : Qnil;
    return VALUES_1(temp);
}

Object Media_block_size = UNBOUND;

static Object Qmedia_bin;          /* media-bin */

/* INITIALIZE-AFTER-READING-FOR-MEDIA-BIN */
Object initialize_after_reading_for_media_bin(media_bin)
    Object media_bin;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(229,13);
    frame = media_bin;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmedia_bin)) {
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
    return remove_dead_media_streams(ISVREF(media_bin,(SI_Long)20L));
}

/* REMOVE-DEAD-MEDIA-STREAMS */
Object remove_dead_media_streams(media_file)
    Object media_file;
{
    Object file, ab_loop_list_, svref_arg_1;

    x_note_fn_call(229,14);
    if (EQ(FIXNUM_LE(ISVREF(media_file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(media_file,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(media_file,
	    (SI_Long)2L),(SI_Long)0L),Qab_directory)) {
	file = Nil;
	ab_loop_list_ = FIXNUM_LE(ISVREF(media_file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(media_file,
		(SI_Long)4L + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(media_file,(SI_Long)2L),(SI_Long)4L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	file = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	remove_dead_media_streams(file);
	goto next_loop;
      end_loop:;
    }
    else {
	reclaim_slot_value(FIXNUM_LE(ISVREF(media_file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(media_file,
		(SI_Long)5L + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(media_file,(SI_Long)2L),(SI_Long)5L));
	if (FIXNUM_LE(ISVREF(media_file,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(media_file,FIX((SI_Long)7L)) = Nil;
	else {
	    svref_arg_1 = ISVREF(media_file,(SI_Long)2L);
	    SVREF(svref_arg_1,FIX((SI_Long)5L)) = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qinput;              /* input */

static Object Qoutput;             /* output */

/* G2-MEDIA-BIN-OPEN-STREAM */
Object g2_media_bin_open_stream(media_bin,location_sequence,name,direction,
	    data_type,mode)
    Object media_bin, location_sequence, name, direction, data_type, mode;
{
    Object location, file_qm;

    x_note_fn_call(229,15);
    location = make_location_from_sequence(location_sequence,T);
    file_qm = locate_media_file_node(ISVREF(media_bin,(SI_Long)20L),location);
    if ( !TRUEP(file_qm))
	return media_bin_file_not_found_error(media_bin,location);
    else if ( !EQ(FIXNUM_LE(ISVREF(file_qm,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file_qm,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file_qm,
	    (SI_Long)2L),(SI_Long)0L),Qab_directory))
	return media_bin_non_directory_error(media_bin,location);
    else if (EQ(direction,Qinput))
	return media_bin_open_input_stream(media_bin,file_qm,location,name,
		data_type,mode);
    else if (EQ(direction,Qoutput))
	return media_bin_open_output_stream(media_bin,file_qm,location,
		name,data_type,mode);
    else
	return media_bin_unknown_io_direction_error(media_bin,location,
		direction);
}

static Object Kstack_error;        /* :stack-error */

/* G2-MEDIA-BIN-OPEN-STREAM-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_open_stream_system_rpc_internal(gensymed_symbol,
	    media_bin,location_sequence,name,direction,data_type,mode)
    Object gensymed_symbol, media_bin, location_sequence, name, direction;
    Object data_type, mode;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,16);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_media_bin_open_stream(media_bin,location_sequence,
		    name,direction,data_type,mode);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object list_constant;       /* # */

static Object Qcreate_or_overwrite;  /* create-or-overwrite */

static Object Qwriting;            /* writing */

/* MEDIA-BIN-OPEN-OUTPUT-STREAM */
Object media_bin_open_output_stream(media_bin,directory_1,location,name,
	    data_type,mode)
    Object media_bin, directory_1, location, name, data_type, mode;
{
    Object existing_file_qm, temp, new_file, new_stream, svref_arg_1;

    x_note_fn_call(229,17);
    existing_file_qm = find_media_file_in_directory(directory_1,name);
    if ( !TRUEP(memq_function(data_type,list_constant)))
	temp = media_bin_unsupported_file_type_error(media_bin,location,
		data_type);
    else if (EQ(mode,Qcreate_or_overwrite)) {
	if (existing_file_qm) {
	    remove_media_file_from_directory(directory_1,existing_file_qm);
	    reclaim_media_file(media_bin,existing_file_qm);
	}
	new_file = make_media_file(data_type,copy_text_string(name));
	temp = FIXNUM_ADD1(ISVREF(media_bin,(SI_Long)22L));
	ISVREF(media_bin,(SI_Long)22L) = temp;
	new_stream = make_media_stream_1(temp,
		extend_media_file_location(copy_media_file_location(location),
		name),new_file,Qoutput);
	if (FIXNUM_LE(ISVREF(new_file,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(new_file,FIX((SI_Long)4L)) = Qwriting;
	else {
	    svref_arg_1 = ISVREF(new_file,(SI_Long)2L);
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qwriting;
	}
	add_media_file_to_directory(directory_1,new_file);
	add_stream_to_media_file(new_file,new_stream);
	add_stream_to_media_bin(media_bin,new_stream);
	ISVREF(new_stream,(SI_Long)5L) = FIX((SI_Long)0L);
	temp = ISVREF(new_stream,(SI_Long)1L);
    }
    else
	temp = media_bin_unsupported_mode_error(media_bin,location,mode);
    return VALUES_1(temp);
}

static Object Qread_shared;        /* read-shared */

static Object list_constant_1;     /* # */

static Object Qreading;            /* reading */

/* MEDIA-BIN-OPEN-INPUT-STREAM */
Object media_bin_open_input_stream(media_bin,directory_1,location,name,
	    data_type,mode)
    Object media_bin, directory_1, location, name, data_type, mode;
{
    Object existing_file_qm, temp, new_stream, temp_1;

    x_note_fn_call(229,18);
    existing_file_qm = find_media_file_in_directory(directory_1,name);
    if ( !TRUEP(memq_function(data_type,list_constant)))
	return media_bin_unsupported_file_type_error(media_bin,location,
		data_type);
    else if ( !TRUEP(existing_file_qm))
	return media_bin_file_not_found_error(media_bin,
		extend_media_file_location(location,name));
    else if ( !EQ(FIXNUM_LE(ISVREF(existing_file_qm,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(existing_file_qm,
	    (SI_Long)0L + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(existing_file_qm,(SI_Long)2L),(SI_Long)0L),
	    data_type))
	return media_bin_incompatible_file_type_error(media_bin,location,
		FIXNUM_LE(ISVREF(existing_file_qm,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(existing_file_qm,
		(SI_Long)0L + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(existing_file_qm,(SI_Long)2L),(SI_Long)0L),
		data_type);
    else if (EQ(mode,Qread_shared)) {
	if ( !TRUEP(memq_function(FIXNUM_LE(ISVREF(existing_file_qm,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(existing_file_qm,(SI_Long)2L + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(existing_file_qm,(SI_Long)2L),(SI_Long)2L),
		list_constant_1)))
	    media_bin_file_locked_error(media_bin,location);
	temp = FIXNUM_ADD1(ISVREF(media_bin,(SI_Long)22L));
	ISVREF(media_bin,(SI_Long)22L) = temp;
	new_stream = make_media_stream_1(temp,
		extend_media_file_location(copy_media_file_location(location),
		name),existing_file_qm,Qinput);
	if (FIXNUM_LE(ISVREF(existing_file_qm,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(existing_file_qm,FIX((SI_Long)4L)) = Qreading;
	else {
	    temp_1 = ISVREF(existing_file_qm,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)2L)) = Qreading;
	}
	add_stream_to_media_file(existing_file_qm,new_stream);
	add_stream_to_media_bin(media_bin,new_stream);
	ISVREF(new_stream,(SI_Long)5L) = FIX((SI_Long)0L);
	temp_1 = FIXNUM_LE(ISVREF(existing_file_qm,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(existing_file_qm,
		(SI_Long)4L + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(existing_file_qm,(SI_Long)2L),(SI_Long)4L);
	SVREF(new_stream,FIX((SI_Long)6L)) = temp_1;
	return VALUES_1(ISVREF(new_stream,(SI_Long)1L));
    }
    else
	return media_bin_unsupported_mode_error(media_bin,location,mode);
}

/* G2-MEDIA-BIN-CLOSE-STREAM */
Object g2_media_bin_close_stream(media_bin,file_descriptor,abort_ev)
    Object media_bin, file_descriptor, abort_ev;
{
    Object stream, temp, file, svref_arg_1, svref_new_value, stream_1;
    Object ab_loop_list_, stream_file, ab_loop_it_;
    char temp_1;

    x_note_fn_call(229,19);
    stream = get_media_stream_or_error(media_bin,file_descriptor,Nil);
    if ( !TRUEP(stream)) {
	if (EQ(abort_ev,Evaluation_true_value))
	    return VALUES_1(Evaluation_true_value);
	else
	    return VALUES_1(Evaluation_false_value);
    }
    if ( !TRUEP(ISVREF(stream,(SI_Long)3L))) {
	if (EQ(abort_ev,Evaluation_true_value))
	    return VALUES_1(Evaluation_true_value);
	else
	    media_bin_stream_file_deleted_error(media_bin,
		    copy_media_file_location(ISVREF(stream,(SI_Long)2L)));
    }
    temp = ISVREF(stream,(SI_Long)4L);
    if (EQ(temp,Qoutput)) {
	file = ISVREF(stream,(SI_Long)3L);
	if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	    SVREF(file,FIX((SI_Long)4L)) = Qnormal;
	else {
	    svref_arg_1 = ISVREF(file,(SI_Long)2L);
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qnormal;
	}
	svref_new_value = ISVREF(stream,(SI_Long)5L);
	if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	    SVREF(file,FIX((SI_Long)5L)) = svref_new_value;
	else {
	    svref_arg_1 = ISVREF(file,(SI_Long)2L);
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
	}
	remove_stream_from_media_file(file,stream);
	remove_stream_from_media_bin(media_bin,stream);
	reclaim_media_stream_1(stream);
    }
    else if (EQ(temp,Qinput)) {
	file = ISVREF(stream,(SI_Long)3L);
	remove_stream_from_media_file(file,stream);
	remove_stream_from_media_bin(media_bin,stream);
	stream_1 = Nil;
	ab_loop_list_ = ISVREF(media_bin,(SI_Long)21L);
	stream_file = Nil;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	stream_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	stream_file = ISVREF(stream_1,(SI_Long)3L);
	ab_loop_it_ = EQ(stream_file,file) ? T : Nil;
	if (ab_loop_it_) {
	    temp_1 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = TRUEP(Qnil);
      end_1:;
	if (temp_1) {
	    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(file,FIX((SI_Long)4L)) = Qreading;
	    else {
		svref_arg_1 = ISVREF(file,(SI_Long)2L);
		SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qreading;
	    }
	}
	else if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(file,FIX((SI_Long)4L)) = Qnormal;
	else {
	    svref_arg_1 = ISVREF(file,(SI_Long)2L);
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qnormal;
	}
	reclaim_media_stream_1(stream);
    }
    return VALUES_1(Evaluation_true_value);
}

/* G2-MEDIA-BIN-CLOSE-STREAM-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_close_stream_system_rpc_internal(gensymed_symbol,
	    media_bin,file_descriptor,abort_ev)
    Object gensymed_symbol, media_bin, file_descriptor, abort_ev;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,20);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_media_bin_close_stream(media_bin,file_descriptor,
		    abort_ev);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qbinary;             /* binary */

/* G2-MEDIA-BIN-SET-IGNORE-LAST-BYTE */
Object g2_media_bin_set_ignore_last_byte(media_bin,file_descriptor)
    Object media_bin, file_descriptor;
{
    Object stream, temp, file, svref_arg_1;

    x_note_fn_call(229,21);
    stream = get_media_stream_or_error(media_bin,file_descriptor,T);
    if ( !EQ(ISVREF(stream,(SI_Long)4L),Qoutput)) {
	temp = copy_media_file_location(ISVREF(stream,(SI_Long)2L));
	media_bin_io_direction_error(media_bin,temp,Qoutput,ISVREF(stream,
		(SI_Long)4L));
    }
    file = ISVREF(stream,(SI_Long)3L);
    if ( !EQ(FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)0L),Qbinary))
	media_bin_stream_must_be_binary_error(media_bin,
		copy_media_file_location(ISVREF(stream,(SI_Long)2L)));
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)9L)) = T;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)7L)) = T;
    }
    return VALUES_1(Evaluation_true_value);
}

/* G2-MEDIA-BIN-SET-IGNORE-LAST-BYTE-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_set_ignore_last_byte_system_rpc_internal(gensymed_symbol,
	    media_bin,file_descriptor)
    Object gensymed_symbol, media_bin, file_descriptor;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,22);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_media_bin_set_ignore_last_byte(media_bin,
		    file_descriptor);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MEDIA-BIN-IGNORE-LAST-BYTE */
Object g2_media_bin_ignore_last_byte(media_bin,file_descriptor)
    Object media_bin, file_descriptor;
{
    Object stream, temp, file;

    x_note_fn_call(229,23);
    stream = get_media_stream_or_error(media_bin,file_descriptor,T);
    if ( !EQ(ISVREF(stream,(SI_Long)4L),Qinput)) {
	temp = copy_media_file_location(ISVREF(stream,(SI_Long)2L));
	media_bin_io_direction_error(media_bin,temp,Qoutput,ISVREF(stream,
		(SI_Long)4L));
    }
    file = ISVREF(stream,(SI_Long)3L);
    if ( !EQ(FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)0L),Qbinary))
	media_bin_stream_must_be_binary_error(media_bin,
		copy_media_file_location(ISVREF(stream,(SI_Long)2L)));
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    TRUEP(ISVREF(file,(SI_Long)7L + 
	    IFIX(Managed_array_index_offset))) : TRUEP(ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)7L)))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-MEDIA-BIN-IGNORE-LAST-BYTE-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_ignore_last_byte_system_rpc_internal(gensymed_symbol,
	    media_bin,file_descriptor)
    Object gensymed_symbol, media_bin, file_descriptor;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,24);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_media_bin_ignore_last_byte(media_bin,file_descriptor);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MEDIA-BIN-WRITE */
Object g2_media_bin_write(media_bin,file_descriptor,data)
    Object media_bin, file_descriptor, data;
{
    Object stream, temp, file, data_pointer, data_length, file_pointer;
    Object pointer_in_block, space_in_first_segment, current_block;
    Object current_block_data, source_length, incff_1_arg;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(229,25);
    stream = get_media_stream_or_error(media_bin,file_descriptor,T);
    if ( !EQ(ISVREF(stream,(SI_Long)4L),Qoutput)) {
	temp = copy_media_file_location(ISVREF(stream,(SI_Long)2L));
	media_bin_io_direction_error(media_bin,temp,Qoutput,ISVREF(stream,
		(SI_Long)4L));
    }
    file = ISVREF(stream,(SI_Long)3L);
    data_pointer = FIX((SI_Long)0L);
    data_length = text_string_length(data);
    file_pointer = ISVREF(stream,(SI_Long)5L);
    pointer_in_block = chestnut_modf_function(file_pointer,Media_block_size);
    space_in_first_segment = FIXNUM_MINUS(Media_block_size,pointer_in_block);
    current_block = ISVREF(stream,(SI_Long)6L);
    current_block_data = CAR(current_block);
    if (IFIX(data_length) > (SI_Long)0L) {
	if (FIXNUM_NE(space_in_first_segment,Media_block_size)) {
	    source_length = FIXNUM_MIN(space_in_first_segment,data_length);
	    media_block_copy(data,FIX((SI_Long)0L),source_length,
		    current_block_data,pointer_in_block);
	    incff_1_arg = source_length;
	    file_pointer = FIXNUM_ADD(file_pointer,incff_1_arg);
	    incff_1_arg = source_length;
	    data_pointer = FIXNUM_ADD(data_pointer,incff_1_arg);
	}
	if (FIXNUM_GT(data_length,space_in_first_segment)) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = 
		    IFIX(chestnut_floorf_function(FIXNUM_MINUS(data_length,
		    data_pointer),Media_block_size));
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    current_block = extend_media_file(file,current_block);
	    current_block_data = CAR(current_block);
	    media_block_copy(data,data_pointer,Media_block_size,
		    current_block_data,FIX((SI_Long)0L));
	    incff_1_arg = Media_block_size;
	    file_pointer = FIXNUM_ADD(file_pointer,incff_1_arg);
	    incff_1_arg = Media_block_size;
	    data_pointer = FIXNUM_ADD(data_pointer,incff_1_arg);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	if (FIXNUM_LT(data_pointer,data_length)) {
	    source_length = FIXNUM_MINUS(data_length,data_pointer);
	    current_block = extend_media_file(file,current_block);
	    current_block_data = CAR(current_block);
	    media_block_copy(data,data_pointer,source_length,
		    current_block_data,FIX((SI_Long)0L));
	    incff_1_arg = source_length;
	    file_pointer = FIXNUM_ADD(file_pointer,incff_1_arg);
	    incff_1_arg = source_length;
	    data_pointer = FIXNUM_ADD(data_pointer,incff_1_arg);
	}
	SVREF(stream,FIX((SI_Long)6L)) = current_block;
	SVREF(stream,FIX((SI_Long)5L)) = file_pointer;
    }
    return VALUES_1(Evaluation_true_value);
}

/* G2-MEDIA-BIN-WRITE-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_write_system_rpc_internal(gensymed_symbol,media_bin,
	    file_descriptor,data)
    Object gensymed_symbol, media_bin, file_descriptor, data;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, temp;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,26);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(data) != (SI_Long)0L)
		temp = data;
	    else {
		temp = M_CAR(data);
		reclaim_eval_cons_1(data);
	    }
	    result = g2_media_bin_write(media_bin,file_descriptor,temp);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MEDIA-BIN-READ */
Object g2_media_bin_read(media_bin,file_descriptor,max_length)
    Object media_bin, file_descriptor, max_length;
{
    Object stream, temp, file, file_pointer, file_size, data_pointer;
    Object data_length, wide_string_bv16, wide_string_bv16_1, data;
    Object pointer_in_block, space_in_first_segment, current_block;
    Object current_block_data, source_length, incff_1_arg;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;

    x_note_fn_call(229,27);
    stream = get_media_stream_or_error(media_bin,file_descriptor,T);
    if ( !EQ(ISVREF(stream,(SI_Long)4L),Qinput)) {
	temp = copy_media_file_location(ISVREF(stream,(SI_Long)2L));
	media_bin_io_direction_error(media_bin,temp,Qoutput,ISVREF(stream,
		(SI_Long)4L));
    }
    if ( !(IFIX(max_length) >= (SI_Long)0L))
	media_bin_negative_length_error(media_bin,
		copy_media_file_location(ISVREF(stream,(SI_Long)2L)),
		max_length);
    file = ISVREF(stream,(SI_Long)3L);
    file_pointer = ISVREF(stream,(SI_Long)5L);
    file_size = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)3L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)3L);
    data_pointer = FIX((SI_Long)0L);
    temp = FIXNUM_MINUS(file_size,file_pointer);
    data_length = FIXNUM_MIN(max_length,temp);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(data_length) + 
	    (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(data_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(data_length) >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(data_length),(SI_Long)0L);
    wide_string_bv16_1 = wide_string_bv16;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16_1));
    length_1 = UBYTE_16_ISAREF_1(wide_string_bv16_1,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16_1,length_1 
	    - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    UBYTE_16_ISASET_1(wide_string_bv16_1,length_1,(SI_Long)1L);
    data = wide_string_bv16_1;
    pointer_in_block = chestnut_modf_function(file_pointer,Media_block_size);
    space_in_first_segment = FIXNUM_MINUS(Media_block_size,pointer_in_block);
    current_block = ISVREF(stream,(SI_Long)6L);
    current_block_data = CAR(current_block);
    if (FIXNUM_EQ(file_pointer,file_size))
	return VALUES_1(Evaluation_false_value);
    else if (IFIX(data_length) > (SI_Long)0L) {
	if (FIXNUM_NE(space_in_first_segment,Media_block_size)) {
	    source_length = FIXNUM_MIN(space_in_first_segment,data_length);
	    media_block_copy(current_block_data,pointer_in_block,
		    source_length,data,FIX((SI_Long)0L));
	    incff_1_arg = source_length;
	    file_pointer = FIXNUM_ADD(file_pointer,incff_1_arg);
	    incff_1_arg = source_length;
	    data_pointer = FIXNUM_ADD(data_pointer,incff_1_arg);
	    if (FIXNUM_EQ(source_length,space_in_first_segment)) {
		current_block = CDR(current_block);
		current_block_data = CAR(current_block);
	    }
	}
	if (FIXNUM_LT(data_pointer,data_length)) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = 
		    IFIX(chestnut_floorf_function(FIXNUM_MINUS(data_length,
		    data_pointer),Media_block_size));
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    media_block_copy(current_block_data,FIX((SI_Long)0L),
		    Media_block_size,data,data_pointer);
	    incff_1_arg = Media_block_size;
	    file_pointer = FIXNUM_ADD(file_pointer,incff_1_arg);
	    incff_1_arg = Media_block_size;
	    data_pointer = FIXNUM_ADD(data_pointer,incff_1_arg);
	    current_block = CDR(current_block);
	    current_block_data = CAR(current_block);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	if (FIXNUM_LT(data_pointer,data_length)) {
	    source_length = FIXNUM_MINUS(data_length,data_pointer);
	    media_block_copy(current_block_data,FIX((SI_Long)0L),
		    source_length,data,data_pointer);
	    incff_1_arg = source_length;
	    file_pointer = FIXNUM_ADD(file_pointer,incff_1_arg);
	    incff_1_arg = source_length;
	    data_pointer = FIXNUM_ADD(data_pointer,incff_1_arg);
	}
	SVREF(stream,FIX((SI_Long)6L)) = current_block;
	SVREF(stream,FIX((SI_Long)5L)) = file_pointer;
	return VALUES_1(data);
    }
    else
	return VALUES_1(data);
}

/* G2-MEDIA-BIN-READ-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_read_system_rpc_internal(gensymed_symbol,media_bin,
	    file_descriptor,max_length)
    Object gensymed_symbol, media_bin, file_descriptor, max_length;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, result_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,28);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result_1 = g2_media_bin_read(media_bin,file_descriptor,max_length);
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(result_1) != (SI_Long)0L)
		result = maybe_make_evaluation_unsigned_vector_16(result_1);
	    else
		result = VALUES_1(result_1);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qsize;               /* size */

static Object Qsize_in_bytes;      /* size-in-bytes */

static Object Qcreate_date;        /* create-date */

static Object Qab_structure;       /* structure */

static Object Qcontents;           /* contents */

/* G2-MEDIA-BIN-DESCRIBE */
Object g2_media_bin_describe(media_bin,location_sequence_or_file_descriptor)
    Object media_bin, location_sequence_or_file_descriptor;
{
    Object file_qm, temp, type, size, gensymed_symbol, temp_1, item_or_value;
    Object x2, temp_3, amf_available_array_cons_qm, amf_array, amf_result;
    Object new_float, temp_4, info, file, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;
    SI_Long binary_size, gensymed_symbol_1, svref_arg_2, item_or_value_1;
    char temp_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(229,29);
    if (FIXNUMP(location_sequence_or_file_descriptor))
	file_qm = ISVREF(get_media_stream_or_error(media_bin,
		location_sequence_or_file_descriptor,Nil),(SI_Long)3L);
    else {
	temp = ISVREF(media_bin,(SI_Long)20L);
	file_qm = locate_media_file_node(temp,
		make_location_from_sequence(location_sequence_or_file_descriptor,
		T));
    }
    if (file_qm) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    type = FIXNUM_LE(ISVREF(file_qm,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(file_qm,
		    (SI_Long)0L + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(file_qm,(SI_Long)2L),(SI_Long)0L);
	    size = FIXNUM_LE(ISVREF(file_qm,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(file_qm,
		    (SI_Long)3L + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(file_qm,(SI_Long)2L),(SI_Long)3L);
	    binary_size = (FIXNUM_LE(ISVREF(file_qm,(SI_Long)1L),
		    Maximum_in_place_array_size) ? TRUEP(ISVREF(file_qm,
		    (SI_Long)7L + IFIX(Managed_array_index_offset))) : 
		    TRUEP(ISVREF(ISVREF(file_qm,(SI_Long)2L),
		    (SI_Long)7L))) ? (SI_Long)2L * IFIX(size) - 
		    (SI_Long)1L : (SI_Long)2L * IFIX(size);
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = type;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = type;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = temp_3;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qsize;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qsize;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = size;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = size;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = temp_3;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsize_in_bytes;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)5L)) = Qsize_in_bytes;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value_1 = binary_size;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
		SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value_1 = binary_size;
		if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) 
			> (SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_3 = temp_2 ? 
			get_reference_to_item(FIX(item_or_value_1)) : 
			FIX(item_or_value_1);
		SVREF(temp_1,FIX((SI_Long)6L)) = temp_3;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qcreate_date;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)7L)) = Qcreate_date;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_1,temp_3) = amf_available_array_cons_qm;
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
		aref_new_value = DFLOAT_ISAREF_1(FIXNUM_LE(ISVREF(file_qm,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(file_qm,(SI_Long)6L + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(file_qm,(SI_Long)2L),(SI_Long)6L),
			(SI_Long)0L);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_3 = Vector_of_simple_float_array_pools;
		    temp_4 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_3 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_3) = amf_available_array_cons_qm;
			temp_3 = Available_float_array_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
		    }
		    else {
			temp_3 = Available_float_array_conses_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			temp_3 = Available_float_array_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
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
		aref_new_value = DFLOAT_ISAREF_1(FIXNUM_LE(ISVREF(file_qm,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(file_qm,(SI_Long)6L + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(file_qm,(SI_Long)2L),(SI_Long)6L),
			(SI_Long)0L);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		item_or_value = new_float;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_3 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp_1,FIX((SI_Long)8L)) = temp_3;
	    }
	    info = eval_cons_1(gensymed_symbol,Qab_structure);
	    if (EQ(type,Qab_directory)) {
		file = Nil;
		ab_loop_list_ = FIXNUM_LE(ISVREF(file_qm,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(file_qm,
			(SI_Long)4L + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(file_qm,(SI_Long)2L),(SI_Long)4L);
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		file = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loopvar__2 = 
			eval_cons_1(copy_as_wide_string(FIXNUM_LE(ISVREF(file,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(file,
			IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
			ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)1L)),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop;
	      end_loop:
		temp = ab_loopvar_;
		goto end_1;
		temp = Qnil;
	      end_1:;
		set_evaluation_structure_slot(info,Qcontents,
			allocate_evaluation_sequence(temp));
	    }
	    result = VALUES_1(info);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-MEDIA-BIN-DESCRIBE-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_describe_system_rpc_internal(gensymed_symbol,media_bin,
	    location_sequence_or_file_descriptor)
    Object gensymed_symbol, media_bin, location_sequence_or_file_descriptor;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,30);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_media_bin_describe(media_bin,
		    location_sequence_or_file_descriptor);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MEDIA-BIN-MAKE-DIRECTORY */
Object g2_media_bin_make_directory(media_bin,location_sequence,name)
    Object media_bin, location_sequence, name;
{
    Object location, file_qm, new_directory;

    x_note_fn_call(229,31);
    location = make_location_from_sequence(location_sequence,T);
    file_qm = locate_media_file_node(ISVREF(media_bin,(SI_Long)20L),location);
    if ( !TRUEP(file_qm))
	media_bin_file_not_found_error(media_bin,location);
    else if ( !EQ(FIXNUM_LE(ISVREF(file_qm,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file_qm,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file_qm,
	    (SI_Long)2L),(SI_Long)0L),Qab_directory))
	media_bin_non_directory_error(media_bin,location);
    else if (find_media_file_in_directory(file_qm,name))
	media_bin_already_exists_error(media_bin,location);
    else {
	new_directory = make_media_file(Qab_directory,copy_text_string(name));
	add_media_file_to_directory(file_qm,new_directory);
    }
    return VALUES_1(Evaluation_true_value);
}

/* G2-MEDIA-BIN-MAKE-DIRECTORY-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_make_directory_system_rpc_internal(gensymed_symbol,
	    media_bin,location_sequence,name)
    Object gensymed_symbol, media_bin, location_sequence, name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,32);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_media_bin_make_directory(media_bin,
		    location_sequence,name);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MEDIA-BIN-DELETE */
Object g2_media_bin_delete(media_bin,location_sequence)
    Object media_bin, location_sequence;
{
    Object location, file_qm, parent_file_qm, wide_string_bv16;
    Object svref_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(229,33);
    location = make_location_from_sequence(location_sequence,T);
    file_qm = locate_media_file_node(ISVREF(media_bin,(SI_Long)20L),location);
    parent_file_qm = locate_media_file_parent_node(ISVREF(media_bin,
	    (SI_Long)20L),location);
    if (file_qm) {
	delete_media_file_or_directory(media_bin,file_qm,parent_file_qm);
	if ( !TRUEP(location)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(media_bin,Qmedia_bin_data);
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
	    svref_new_value = make_media_file(Qab_directory,wide_string_bv16);
	    SVREF(media_bin,FIX((SI_Long)20L)) = svref_new_value;
	}
    }
    else
	media_bin_file_not_found_error(media_bin,location);
    return VALUES_1(Evaluation_true_value);
}

/* G2-MEDIA-BIN-DELETE-SYSTEM-RPC-INTERNAL */
Object g2_media_bin_delete_system_rpc_internal(gensymed_symbol,media_bin,
	    location_sequence)
    Object gensymed_symbol, media_bin, location_sequence;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(229,34);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_media_bin_delete(media_bin,location_sequence);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* DELETE-MEDIA-FILE-OR-DIRECTORY */
Object delete_media_file_or_directory(media_bin,file,parent_file_qm)
    Object media_bin, file, parent_file_qm;
{
    Object sub_file, ab_loop_list_, svref_arg_1;

    x_note_fn_call(229,35);
    if (EQ(FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size) 
	    ? ISVREF(file,(SI_Long)0L + IFIX(Managed_array_index_offset)) :
	     ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)0L),Qab_directory)) {
	sub_file = Nil;
	ab_loop_list_ = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)4L + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
		(SI_Long)2L),(SI_Long)4L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sub_file = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	delete_media_file_or_directory(media_bin,sub_file,file);
	goto next_loop;
      end_loop:;
	reclaim_slot_value_list_1(FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)4L + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
		(SI_Long)2L),(SI_Long)4L));
	if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	    SVREF(file,FIX((SI_Long)6L)) = Nil;
	else {
	    svref_arg_1 = ISVREF(file,(SI_Long)2L);
	    SVREF(svref_arg_1,FIX((SI_Long)4L)) = Nil;
	}
	if (parent_file_qm)
	    remove_media_file_from_directory(parent_file_qm,file);
	reclaim_slot_value(file);
    }
    else {
	if (parent_file_qm)
	    remove_media_file_from_directory(parent_file_qm,file);
	reclaim_media_file(media_bin,file);
    }
    return VALUES_1(Nil);
}

/* GET-MEDIA-STREAM-OR-ERROR */
Object get_media_stream_or_error(media_bin,file_descriptor,throw_error_p)
    Object media_bin, file_descriptor, throw_error_p;
{
    Object stream, ab_loop_list_;

    x_note_fn_call(229,36);
    stream = Nil;
    ab_loop_list_ = ISVREF(media_bin,(SI_Long)21L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    stream = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(file_descriptor,ISVREF(stream,(SI_Long)1L))) {
	if ( !TRUEP(ISVREF(stream,(SI_Long)3L))) {
	    if (throw_error_p)
		media_bin_stream_file_deleted_error(media_bin,
			copy_media_file_location(ISVREF(stream,(SI_Long)2L)));
	    else
		return VALUES_1(Nil);
	}
	return VALUES_1(stream);
    }
    goto next_loop;
  end_loop:
    if (throw_error_p)
	media_bin_no_such_stream_error(media_bin,file_descriptor);
    else
	return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* LOCATE-MEDIA-FILE-NODE */
Object locate_media_file_node(root,location)
    Object root, location;
{
    Object level_name, ab_loop_list_, media_file, ab_loop_list__1, temp_1;
    char temp;

    x_note_fn_call(229,37);
    level_name = Nil;
    ab_loop_list_ = location;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    level_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(FIXNUM_LE(ISVREF(root,(SI_Long)1L),Maximum_in_place_array_size) 
	    ? ISVREF(root,(SI_Long)0L + IFIX(Managed_array_index_offset)) :
	     ISVREF(ISVREF(root,(SI_Long)2L),(SI_Long)0L),Qab_directory)) {
	media_file = Nil;
	ab_loop_list__1 = FIXNUM_LE(ISVREF(root,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(root,(SI_Long)4L + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(root,
		(SI_Long)2L),(SI_Long)4L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	media_file = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (string_eq_w(FIXNUM_LE(ISVREF(media_file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(media_file,
		IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
		ISVREF(ISVREF(media_file,(SI_Long)2L),(SI_Long)1L),
		    level_name)) {
	    root = media_file;
	    temp = TRUEP(T);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	if ( !temp) {
	    temp_1 = Nil;
	    goto end_2;
	}
    }
    else {
	temp_1 = Nil;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp_1 = root;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

/* LOCATE-MEDIA-FILE-PARENT-NODE */
Object locate_media_file_parent_node(root,location)
    Object root, location;
{
    Object parent_qm, level_name, ab_loop_list_, media_file, ab_loop_list__1;
    Object temp_1;
    char temp;

    x_note_fn_call(229,38);
    parent_qm = Nil;
    level_name = Nil;
    ab_loop_list_ = location;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    level_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(FIXNUM_LE(ISVREF(root,(SI_Long)1L),Maximum_in_place_array_size) 
	    ? ISVREF(root,(SI_Long)0L + IFIX(Managed_array_index_offset)) :
	     ISVREF(ISVREF(root,(SI_Long)2L),(SI_Long)0L),Qab_directory)) {
	media_file = Nil;
	ab_loop_list__1 = FIXNUM_LE(ISVREF(root,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(root,(SI_Long)4L + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(root,
		(SI_Long)2L),(SI_Long)4L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	media_file = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (string_eq_w(FIXNUM_LE(ISVREF(media_file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(media_file,
		IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
		ISVREF(ISVREF(media_file,(SI_Long)2L),(SI_Long)1L),
		    level_name)) {
	    parent_qm = root;
	    root = media_file;
	    temp = TRUEP(T);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	if ( !temp) {
	    temp_1 = Nil;
	    goto end_2;
	}
    }
    else {
	temp_1 = parent_qm;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp_1 = parent_qm;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

/* FIND-MEDIA-FILE-IN-DIRECTORY */
Object find_media_file_in_directory(directory_1,filename)
    Object directory_1, filename;
{
    Object media_file, ab_loop_list_, temp;

    x_note_fn_call(229,39);
    media_file = Nil;
    ab_loop_list_ = FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(directory_1,(SI_Long)4L 
	    + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(directory_1,(SI_Long)2L),(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    media_file = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_eq_w(FIXNUM_LE(ISVREF(media_file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(media_file,
	    IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
	    ISVREF(ISVREF(media_file,(SI_Long)2L),(SI_Long)1L),filename)) {
	temp = media_file;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* EXTEND-MEDIA-FILE */
Object extend_media_file(file,end_block)
    Object file, end_block;
{
    Object wide_string_bv16, temp, result_1, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(229,40);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(Media_block_size) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Media_block_size) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(Media_block_size) >>  -  - 
	    (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    temp = Media_block_size;
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(temp),(SI_Long)0L);
    result_1 = slot_value_cons_1(wide_string_bv16,Nil);
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    TRUEP(ISVREF(file,(SI_Long)4L + 
	    IFIX(Managed_array_index_offset))) : TRUEP(ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)4L))) {
	M_CDR(end_block) = result_1;
	temp_1 = result_1;
    }
    else {
	if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	    SVREF(file,FIX((SI_Long)6L)) = result_1;
	else {
	    temp = ISVREF(file,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)4L)) = result_1;
	}
	temp_1 = result_1;
    }
    return VALUES_1(temp_1);
}

/* MEDIA-BLOCK-COPY */
Object media_block_copy(source,source_start,source_length,destination,
	    destination_start)
    Object source, source_start, source_length, destination, destination_start;
{
    Object source_string, source_end, destination_string, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(229,41);
    source_string = source;
    source_end = FIXNUM_ADD(source_start,source_length);
    destination_string = destination;
    gensymed_symbol = source_string;
    gensymed_symbol_1 = IFIX(source_start);
    gensymed_symbol_2 = destination_string;
    gensymed_symbol_3 = IFIX(destination_start);
    gensymed_symbol_4 = IFIX(FIXNUM_MINUS(source_end,source_start));
    INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
	    gensymed_symbol_1,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
	    gensymed_symbol_3,gensymed_symbol_4);
    return VALUES_1(Nil);
}

/* ADD-MEDIA-FILE-TO-DIRECTORY */
Object add_media_file_to_directory(directory_1,file)
    Object directory_1, file;
{
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    Object svref_arg_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value_1;

    x_note_fn_call(229,42);
    slot_value_push_modify_macro_arg = file;
    car_1 = slot_value_push_modify_macro_arg;
    cdr_1 = FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(directory_1,(SI_Long)4L 
	    + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(directory_1,(SI_Long)2L),(SI_Long)4L);
    svref_new_value = slot_value_cons_1(car_1,cdr_1);
    if (FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(directory_1,FIX((SI_Long)6L)) = svref_new_value;
    else {
	svref_arg_1 = ISVREF(directory_1,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    gensymed_symbol = FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(directory_1,
	    (SI_Long)3L + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(directory_1,(SI_Long)2L),(SI_Long)3L));
    gensymed_symbol_1 = (SI_Long)1L;
    svref_new_value_1 = gensymed_symbol + gensymed_symbol_1;
    if (FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),Maximum_in_place_array_size))
	ISVREF(directory_1,(SI_Long)5L) = FIX(svref_new_value_1);
    else {
	svref_arg_1 = ISVREF(directory_1,(SI_Long)2L);
	ISVREF(svref_arg_1,(SI_Long)3L) = FIX(svref_new_value_1);
    }
    return VALUES_1(Nil);
}

/* REMOVE-MEDIA-FILE-FROM-DIRECTORY */
Object remove_media_file_from_directory(directory_1,file)
    Object directory_1, file;
{
    Object svref_new_value, svref_arg_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value_1;

    x_note_fn_call(229,43);
    svref_new_value = delete_slot_value_element_1(file,
	    FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(directory_1,(SI_Long)4L 
	    + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(directory_1,(SI_Long)2L),(SI_Long)4L));
    if (FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(directory_1,FIX((SI_Long)6L)) = svref_new_value;
    else {
	svref_arg_1 = ISVREF(directory_1,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    gensymed_symbol = FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(directory_1,
	    (SI_Long)3L + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(directory_1,(SI_Long)2L),(SI_Long)3L));
    gensymed_symbol_1 = (SI_Long)1L;
    svref_new_value_1 = gensymed_symbol - gensymed_symbol_1;
    if (FIXNUM_LE(ISVREF(directory_1,(SI_Long)1L),Maximum_in_place_array_size))
	ISVREF(directory_1,(SI_Long)5L) = FIX(svref_new_value_1);
    else {
	svref_arg_1 = ISVREF(directory_1,(SI_Long)2L);
	ISVREF(svref_arg_1,(SI_Long)3L) = FIX(svref_new_value_1);
    }
    return VALUES_1(Nil);
}

/* ADD-STREAM-TO-MEDIA-FILE */
Object add_stream_to_media_file(file,stream)
    Object file, stream;
{
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    Object svref_arg_1;

    x_note_fn_call(229,44);
    slot_value_push_modify_macro_arg = stream;
    car_1 = slot_value_push_modify_macro_arg;
    cdr_1 = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)5L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)5L);
    svref_new_value = slot_value_cons_1(car_1,cdr_1);
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)7L)) = svref_new_value;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* REMOVE-STREAM-FROM-MEDIA-FILE */
Object remove_stream_from_media_file(file,stream)
    Object file, stream;
{
    Object svref_new_value, svref_arg_1;

    x_note_fn_call(229,45);
    svref_new_value = delete_slot_value_element_1(stream,
	    FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)5L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)5L));
    if (FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size))
	SVREF(file,FIX((SI_Long)7L)) = svref_new_value;
    else {
	svref_arg_1 = ISVREF(file,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* ADD-STREAM-TO-MEDIA-BIN */
Object add_stream_to_media_bin(media_bin,stream)
    Object media_bin, stream;
{
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(229,46);
    slot_value_push_modify_macro_arg = stream;
    car_1 = slot_value_push_modify_macro_arg;
    cdr_1 = ISVREF(media_bin,(SI_Long)21L);
    svref_new_value = slot_value_cons_1(car_1,cdr_1);
    ISVREF(media_bin,(SI_Long)21L) = svref_new_value;
    return VALUES_1(Nil);
}

/* REMOVE-STREAM-FROM-MEDIA-BIN */
Object remove_stream_from_media_bin(media_bin,stream)
    Object media_bin, stream;
{
    Object svref_new_value;

    x_note_fn_call(229,47);
    svref_new_value = delete_slot_value_element_1(stream,ISVREF(media_bin,
	    (SI_Long)21L));
    ISVREF(media_bin,(SI_Long)21L) = svref_new_value;
    return VALUES_1(Nil);
}

static Object string_constant;     /* "~NV is not a sequence of text" */

/* MAKE-LOCATION-FROM-SEQUENCE */
Object make_location_from_sequence(sequence,reclaim_p)
    Object sequence, reclaim_p;
{
    Object location, gensymed_symbol, held_vector, elt_1, elt_2, validated_elt;
    Object temp, top_of_stack, message_1;
    SI_Long next_index, length_1;

    x_note_fn_call(229,48);
    location = Qnil;
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    elt_1 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_2 ? validate_item_or_evaluation_value(elt_2,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    elt_1 = validated_elt;
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(elt_1) != (SI_Long)0L) {
	temp = copy_text_string(elt_1);
	location = slot_value_cons_1(temp,location);
    }
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    goto next_loop;
  end_loop:
    if (reclaim_p) {
	reclaim_evaluation_value(sequence);
	temp = nreverse(location);
	goto end_1;
    }
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* RECLAIM-MEDIA-FILE */
Object reclaim_media_file(media_bin,media_file)
    Object media_bin, media_file;
{
    Object stream, ab_loop_list_;

    x_note_fn_call(229,49);
    if (EQ(FIXNUM_LE(ISVREF(media_file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(media_file,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(media_file,
	    (SI_Long)2L),(SI_Long)0L),Qab_directory))
	cerror((SI_Long)2L,"go on","write me");
    else {
	stream = Nil;
	ab_loop_list_ = ISVREF(media_bin,(SI_Long)21L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	stream = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(ISVREF(stream,(SI_Long)3L),media_file))
	    SVREF(stream,FIX((SI_Long)3L)) = Nil;
	goto next_loop;
      end_loop:;
	reclaim_slot_value(media_file);
    }
    return VALUES_1(Nil);
}

/* EXTEND-MEDIA-FILE-LOCATION */
Object extend_media_file_location(location,extension)
    Object location, extension;
{
    x_note_fn_call(229,50);
    return VALUES_1(nconc2(location,text_string_p(extension) ? 
	    slot_value_cons_1(extension,Nil) : extension));
}

/* COPY-MEDIA-FILE-LOCATION */
Object copy_media_file_location(location)
    Object location;
{
    x_note_fn_call(229,51);
    return copy_for_slot_value(location);
}

/* RECLAIM-MEDIA-FILE-LOCATION */
Object reclaim_media_file_location(location)
    Object location;
{
    x_note_fn_call(229,52);
    reclaim_slot_value(location);
    return VALUES_1(Nil);
}

/* G2-MEDIA-BIN-UPLOAD-BINARY-FILE */
Object g2_media_bin_upload_binary_file(media_bin,location_sequence,name,
	    local_file_name)
    Object media_bin, location_sequence, name, local_file_name;
{
    x_note_fn_call(229,53);
    return g2_media_bin_upload_binary_file_1(media_bin,location_sequence,
	    name,local_file_name);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

/* G2-MEDIA-BIN-UPLOAD-BINARY-FILE-1 */
Object g2_media_bin_upload_binary_file_1(media_bin,location_sequence,name,
	    local_file_name)
    Object media_bin, location_sequence, name, local_file_name;
{
    volatile Object pathname_used_p;
    volatile Object namestring_1;
    volatile Object binary_file_stream;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(229,54);
    SAVE_STACK();
    pathname_used_p = Qunbound_in_protected_let;
    namestring_1 = Qunbound_in_protected_let;
    binary_file_stream = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_used_p = SIMPLE_VECTOR_P(local_file_name) ? 
		(EQ(ISVREF(local_file_name,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		T : Nil) : Qnil;
	namestring_1 = SIMPLE_VECTOR_P(local_file_name) && 
		EQ(ISVREF(local_file_name,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		gensym_namestring(1,local_file_name) : local_file_name;
	binary_file_stream = 
		g2_stream_open_for_random_access_binary_input(namestring_1);
	if ( !TRUEP(binary_file_stream))
	    SAVE_VALUES(media_bin_no_local_file_error(media_bin,
		    local_file_name));
	else
	    SAVE_VALUES(g2_media_bin_upload_binary_file_2(binary_file_stream,
		    media_bin,location_sequence,name));
    }
    POP_UNWIND_PROTECT(0);
    if (binary_file_stream) {
	if ( !EQ(binary_file_stream,Qunbound_in_protected_let))
	    g2_stream_close(binary_file_stream);
    }
    if (namestring_1) {
	if ( !EQ(namestring_1,Qunbound_in_protected_let)) {
	    if (pathname_used_p)
		reclaim_text_string(namestring_1);
	}
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-MEDIA-BIN-UPLOAD-BINARY-FILE-2 */
Object g2_media_bin_upload_binary_file_2(binary_file_stream,media_bin,
	    location_sequence,name)
    Object binary_file_stream, media_bin, location_sequence, name;
{
    Object media_stream, wide_string_bv16, aref_arg_2, buffer, last_byte_qm, i;
    Object ch_qm, ab_loop_iter_flag_, last_buffer;
    SI_Long bv16_length, temp, aref_new_value, count_1;

    x_note_fn_call(229,55);
    media_stream = g2_media_bin_open_stream(media_bin,location_sequence,
	    name,Qoutput,Qbinary,Qcreate_or_overwrite);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(Media_block_size) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    temp = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Media_block_size) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
    temp = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(Media_block_size) >>  -  - 
	    (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
    aref_arg_2 = Media_block_size;
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(aref_arg_2),(SI_Long)0L);
    buffer = wide_string_bv16;
    last_byte_qm = FIX((SI_Long)0L);
    i = FIX((SI_Long)0L);
    ch_qm = Nil;
    count_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    ch_qm = g2_stream_read_ascii_byte(binary_file_stream);
    if ( !TRUEP(ab_loop_iter_flag_))
	count_1 = count_1 + (SI_Long)1L;
    if ( !TRUEP(ch_qm))
	goto end_loop;
    if ((count_1 & (SI_Long)1L) == (SI_Long)0L)
	last_byte_qm = ch_qm;
    else {
	temp = (IFIX(ch_qm) << (SI_Long)8L) + IFIX(last_byte_qm);
	UBYTE_16_ISASET_1(buffer,IFIX(i),temp);
	i = FIXNUM_ADD1(i);
	last_byte_qm = Nil;
    }
    if (FIXNUM_EQ(i,Media_block_size)) {
	g2_media_bin_write(media_bin,media_stream,buffer);
	i = FIX((SI_Long)0L);
	last_byte_qm = Nil;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    if (last_byte_qm) {
	UBYTE_16_ISASET_1(buffer,IFIX(i),IFIX(last_byte_qm));
	i = FIXNUM_ADD1(i);
    }
    if (IFIX(i) > (SI_Long)0L) {
	wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(i) + (SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(i) & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	temp = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | IFIX(i) >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,IFIX(i),(SI_Long)0L);
	last_buffer = wide_string_bv16;
	media_block_copy(buffer,FIX((SI_Long)0L),i,last_buffer,
		FIX((SI_Long)0L));
	g2_media_bin_write(media_bin,media_stream,last_buffer);
	reclaim_wide_string(last_buffer);
    }
    if ((count_1 & (SI_Long)1L) == (SI_Long)1L)
	g2_media_bin_set_ignore_last_byte(media_bin,media_stream);
    reclaim_wide_string(buffer);
    return g2_media_bin_close_stream(media_bin,media_stream,
	    Evaluation_false_value);
}

static Object array_constant;      /* # */

/* DESCRIBE-FRAME-FOR-MEDIA-BIN */
Object describe_frame_for_media_bin(media_bin)
    Object media_bin;
{
    Object temp, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(229,56);
    temp = ISVREF(media_bin,(SI_Long)20L) ? describe_media_bin(media_bin,
	    ISVREF(media_bin,(SI_Long)20L),FIX((SI_Long)0L)) : 
	    eval_cons_1(copy_constant_wide_string_given_length(array_constant,
	    FIX((SI_Long)18L)),Nil);
    frame = media_bin;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmedia_bin)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    return VALUES_1(nconc2(temp,method_function_qm ? 
	    inline_funcall_1(method_function_qm,frame) : Nil));
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_1;   /* " " */

static Object string_constant_2;   /* "~A:" */

static Object array_constant_1;    /* # */

static Object string_constant_3;   /* "~A size = ~s" */

/* DESCRIBE-MEDIA-BIN */
Object describe_media_bin(media_bin,file,depth)
    Object media_bin, file, depth;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, result_1, sub_file, ab_loop_list_, sub_description;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_, gensymed_symbol, gensymed_symbol_1;
    Declare_special(5);

    x_note_fn_call(229,57);
    if (EQ(FIXNUM_LE(ISVREF(file,(SI_Long)1L),Maximum_in_place_array_size) 
	    ? ISVREF(file,(SI_Long)0L + IFIX(Managed_array_index_offset)) :
	     ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)0L),Qab_directory)) {
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
		  i = (SI_Long)0L;
		  ab_loop_bind_ = IFIX(depth);
		next_loop:
		  if (i >= ab_loop_bind_)
		      goto end_loop;
		  twrite(string_constant_1);
		  i = i + (SI_Long)1L;
		  goto next_loop;
		end_loop:;
		  tformat(2,string_constant_2,IFIX(depth) == (SI_Long)0L ? 
			  array_constant_1 : FIXNUM_LE(ISVREF(file,
			  (SI_Long)1L),Maximum_in_place_array_size) ? 
			  ISVREF(file,
			  IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
			  ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)1L));
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result_1 = eval_cons_1(temp,Nil);
	sub_file = Nil;
	ab_loop_list_ = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)4L + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
		(SI_Long)2L),(SI_Long)4L);
	sub_description = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	sub_file = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_description = describe_media_bin(media_bin,sub_file,
		FIX((SI_Long)2L + IFIX(depth)));
	result_1 = nconc2(sub_description,result_1);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(result_1);
	return VALUES_1(Qnil);
    }
    else {
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
		  i = (SI_Long)0L;
		  ab_loop_bind_ = IFIX(depth);
		next_loop_2:
		  if (i >= ab_loop_bind_)
		      goto end_loop_2;
		  twrite(string_constant_1);
		  i = i + (SI_Long)1L;
		  goto next_loop_2;
		end_loop_2:;
		  temp = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
			  Maximum_in_place_array_size) ? ISVREF(file,
			  IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
			  ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)1L);
		  gensymed_symbol = (SI_Long)2L;
		  gensymed_symbol_1 = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
			  Maximum_in_place_array_size) ? IFIX(ISVREF(file,
			  (SI_Long)3L + IFIX(Managed_array_index_offset))) 
			  : IFIX(ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)3L));
		  gensymed_symbol = gensymed_symbol * gensymed_symbol_1;
		  gensymed_symbol_1 = (FIXNUM_LE(ISVREF(file,(SI_Long)1L),
			  Maximum_in_place_array_size) ? TRUEP(ISVREF(file,
			  (SI_Long)7L + IFIX(Managed_array_index_offset))) 
			  : TRUEP(ISVREF(ISVREF(file,(SI_Long)2L),
			  (SI_Long)7L))) ? (SI_Long)1L : (SI_Long)0L;
		  tformat(3,string_constant_3,temp,FIX(gensymed_symbol - 
			  gensymed_symbol_1));
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return eval_cons_1(temp,Nil);
    }
}

/* INITIAL-CACHED-MEDIA-BIN */
Object initial_cached_media_bin(class_1)
    Object class_1;
{
    x_note_fn_call(229,58);
    return VALUES_1(Nil);
}

/* GET-CACHED-MEDIA-BIN */
Object get_cached_media_bin(image_definition)
    Object image_definition;
{
    Object temp;

    x_note_fn_call(229,59);
    cache_media_bin_if_possible(image_definition,Nil);
    temp = get_lookup_slot_value_given_default(image_definition,
	    Qimage_definition_media_bin,Nil);
    return VALUES_1(temp);
}

static Object Qframe_flags;        /* frame-flags */

static Object array_constant_2;    /* # */

/* CACHE-MEDIA-BIN-IF-POSSIBLE */
Object cache_media_bin_if_possible(image_definition,decache_p)
    Object image_definition, decache_p;
{
    Object pathname_qm, cacheable_p, existing_bin_qm, media_bin;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value_1, temp;
    Object structure_or_false, file_description_qm, namestring_1, temp_1;
    SI_Long svref_new_value;

    x_note_fn_call(229,60);
    pathname_qm = full_pathname_of_image_qm(image_definition);
    cacheable_p = pathname_qm ? file_exists_p(pathname_qm) : Qnil;
    existing_bin_qm = get_lookup_slot_value_given_default(image_definition,
	    Qimage_definition_media_bin,Nil);
    if (cacheable_p) {
	media_bin = get_lookup_slot_value_given_default(image_definition,
		Qimage_definition_media_bin,Nil);
	if ( !TRUEP(media_bin)) {
	    media_bin = make_transient_item(Qmedia_bin);
	    if ( !((SI_Long)0L != (IFIX(ISVREF(image_definition,
		    (SI_Long)5L)) & (SI_Long)262144L))) {
		svref_new_value = IFIX(ISVREF(media_bin,(SI_Long)5L)) &  
			~(SI_Long)262144L;
		ISVREF(media_bin,(SI_Long)5L) = FIX(svref_new_value);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(media_bin,Qframe_flags);
		svref_new_value = IFIX(ISVREF(media_bin,(SI_Long)4L)) | 
			(SI_Long)1L;
		ISVREF(media_bin,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(image_definition,
			Qimage_definition_media_bin);
	    set_lookup_slot_value_1(image_definition,
		    Qimage_definition_media_bin,media_bin);
	    ISVREF(media_bin,(SI_Long)23L) = image_definition;
	    frame_serial_number_setf_arg = ISVREF(image_definition,
		    (SI_Long)3L);
	    old = ISVREF(media_bin,(SI_Long)24L);
	    new_1 = frame_serial_number_setf_arg;
	    svref_new_value_1 = (FIXNUMP(old) ||  !TRUEP(old)) && 
		    (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    ISVREF(media_bin,(SI_Long)24L) = svref_new_value_1;
	}
	temp = media_bin;
	structure_or_false = g2_media_bin_describe(temp,
		allocate_evaluation_sequence(eval_cons_1(copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)5L)),Nil)));
	file_description_qm = EQ(structure_or_false,
		Evaluation_false_value) ? Nil : structure_or_false;
	if ( !TRUEP(file_description_qm) || decache_p) {
	    namestring_1 = gensym_namestring(1,pathname_qm);
	    temp = media_bin;
	    temp_1 = allocate_evaluation_sequence(Nil);
	    g2_media_bin_upload_binary_file(temp,temp_1,
		    copy_constant_wide_string_given_length(array_constant_2,
		    FIX((SI_Long)5L)),namestring_1);
	    reclaim_text_string(namestring_1);
	}
	if (file_description_qm)
	    reclaim_evaluation_structure(file_description_qm);
    }
    else if (existing_bin_qm && decache_p) {
	delete_frame(existing_bin_qm);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(image_definition,
		    Qimage_definition_media_bin);
	set_lookup_slot_value_1(image_definition,
		Qimage_definition_media_bin,Nil);
    }
    else;
    if (pathname_qm)
	return reclaim_gensym_pathname(pathname_qm);
    else
	return VALUES_1(Nil);
}

static Object Qg2_java_bean_media_bin;  /* g2-java-bean-media-bin */

/* MAKE-MEDIA-BIN-FOR-G2-JAVA-BEAN */
Object make_media_bin_for_g2_java_bean(g2_java_bean)
    Object g2_java_bean;
{
    Object media_bin, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value_1;
    SI_Long svref_new_value;

    x_note_fn_call(229,61);
    media_bin = Nil;
    media_bin = make_transient_item(Qmedia_bin);
    if ( !((SI_Long)0L != (IFIX(ISVREF(g2_java_bean,(SI_Long)5L)) & 
	    (SI_Long)262144L))) {
	svref_new_value = IFIX(ISVREF(media_bin,(SI_Long)5L)) &  
		~(SI_Long)262144L;
	ISVREF(media_bin,(SI_Long)5L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(media_bin,Qframe_flags);
	svref_new_value = IFIX(ISVREF(media_bin,(SI_Long)4L)) | (SI_Long)1L;
	ISVREF(media_bin,(SI_Long)4L) = FIX(svref_new_value);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_java_bean,Qg2_java_bean_media_bin);
    set_lookup_slot_value_1(g2_java_bean,Qg2_java_bean_media_bin,media_bin);
    ISVREF(media_bin,(SI_Long)23L) = g2_java_bean;
    frame_serial_number_setf_arg = ISVREF(g2_java_bean,(SI_Long)3L);
    old = ISVREF(media_bin,(SI_Long)24L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value_1 = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) 
	    ||  !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    ISVREF(media_bin,(SI_Long)24L) = svref_new_value_1;
    return VALUES_1(Nil);
}

static Object string_constant_4;   /* "Media file ~A not found in media bin ~NF" */

/* MEDIA-BIN-FILE-NOT-FOUND-ERROR */
Object media_bin_file_not_found_error(media_bin,location)
    Object media_bin, location;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,62);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_4,
	    location_string,media_bin);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_5;   /* "file ~A in ~NF is locked" */

/* MEDIA-BIN-FILE-LOCKED-ERROR */
Object media_bin_file_locked_error(media_bin,location)
    Object media_bin, location;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,63);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_5,
	    location_string,media_bin);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_6;   /* "~a in media bin ~NF is not a directory" */

/* MEDIA-BIN-NON-DIRECTORY-ERROR */
Object media_bin_non_directory_error(media_bin,location)
    Object media_bin, location;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,64);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_6,
	    location_string,media_bin);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_7;   /* "~a in media bin ~NF must be BINARY" */

/* MEDIA-BIN-STREAM-MUST-BE-BINARY-ERROR */
Object media_bin_stream_must_be_binary_error(media_bin,location)
    Object media_bin, location;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,65);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_7,
	    location_string,media_bin);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_8;   /* "opening file, ~a, in media bin ~NF with unknown directionn ~A" */

/* MEDIA-BIN-UNKNOWN-IO-DIRECTION-ERROR */
Object media_bin_unknown_io_direction_error(media_bin,location,direction)
    Object media_bin, location, direction;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,66);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(4,string_constant_8,
	    location_string,media_bin,direction);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_9;   /* "opening file, ~a, in media bin ~NF with unsupported file type, ~A" */

/* MEDIA-BIN-UNSUPPORTED-FILE-TYPE-ERROR */
Object media_bin_unsupported_file_type_error(media_bin,location,file_type)
    Object media_bin, location, file_type;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,67);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(4,string_constant_9,
	    location_string,media_bin,file_type);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_10;  /* "opening file, ~a, in media bin ~NF with unsupported mode, ~A" */

/* MEDIA-BIN-UNSUPPORTED-MODE-ERROR */
Object media_bin_unsupported_mode_error(media_bin,location,mode)
    Object media_bin, location, mode;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,68);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(4,string_constant_10,
	    location_string,media_bin,mode);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_11;  /* "attempting to ~a file, ~a, in media bin ~NF, open for ~a" */

/* MEDIA-BIN-IO-DIRECTION-ERROR */
Object media_bin_io_direction_error(media_bin,location,stream_direction,
	    operation)
    Object media_bin, location, stream_direction, operation;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,69);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(5,string_constant_11,
	    operation,location_string,media_bin,stream_direction);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_12;  /* "reading negative (~s) number of bytes or characters from ~a in ~NF" */

/* MEDIA-BIN-NEGATIVE-LENGTH-ERROR */
Object media_bin_negative_length_error(media_bin,location,length_1)
    Object media_bin, location, length_1;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,70);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(4,string_constant_12,
	    length_1,location_string,media_bin);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_13;  /* "attempting to create ~a in ~NF, which already exists" */

/* MEDIA-BIN-ALREADY-EXISTS-ERROR */
Object media_bin_already_exists_error(media_bin,location)
    Object media_bin, location;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,71);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_13,
	    location_string,media_bin);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_14;  /* "attempting to use ~a in ~NF, which was deleted" */

/* MEDIA-BIN-STREAM-FILE-DELETED-ERROR */
Object media_bin_stream_file_deleted_error(media_bin,location)
    Object media_bin, location;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,72);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_14,
	    location_string,media_bin);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_15;  /* "cannot open ~a in ~NF, a ~a file, as ~a" */

/* MEDIA-BIN-INCOMPATIBLE-FILE-TYPE-ERROR */
Object media_bin_incompatible_file_type_error(media_bin,location,file_type,
	    open_type)
    Object media_bin, location, file_type, open_type;
{
    Object location_string, top_of_stack, message_1;

    x_note_fn_call(229,73);
    location_string = media_file_location_to_string(location);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(5,string_constant_15,
	    location_string,media_bin,file_type,open_type);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_16;  /* "No stream in ~NF known for file descriptor ~s" */

/* MEDIA-BIN-NO-SUCH-STREAM-ERROR */
Object media_bin_no_such_stream_error(media_bin,file_descriptor)
    Object media_bin, file_descriptor;
{
    Object top_of_stack, message_1;

    x_note_fn_call(229,74);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_16,
	    media_bin,file_descriptor);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object string_constant_17;  /* "Cannot open for ~a for uploading into ~NF" */

/* MEDIA-BIN-NO-LOCAL-FILE-ERROR */
Object media_bin_no_local_file_error(media_bin,local_file_name)
    Object media_bin, local_file_name;
{
    Object top_of_stack, message_1;

    x_note_fn_call(229,75);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_17,
	    local_file_name,media_bin);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object array_constant_3;    /* # */

/* MEDIA-FILE-LOCATION-TO-STRING */
Object media_file_location_to_string(location)
    Object location;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object name, ab_loop_list_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(229,76);
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
	      name = Nil;
	      ab_loop_list_ = location;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      name = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      twrite_beginning_of_wide_string(array_constant_3,
		      FIX((SI_Long)1L));
	      twrite_general_string(name);
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_slot_value(location);
    return VALUES_1(temp);
}

static Object Qowner;              /* owner */

static Object Qname;               /* name */

static Object Qstatus;             /* status */

static Object Qtext;               /* text */

/* MEDIA-FILE-EVALUATION-VALUE */
Object media_file_evaluation_value(file,owner_qm)
    Object file, owner_qm;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, car_new_value, temp_1;
    Object element, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object wide_string_bv16;
    SI_Long length_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(229,77);
    temp = owner_qm ? eval_list_2(Qowner,owner_qm) : Nil;
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)10L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qtype;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)0L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qname;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = copy_text_string(FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,
	    IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
	    ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)1L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qstatus;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)2L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)2L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qcontents;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp_1 = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)0L);
    if (EQ(temp_1,Qab_directory)) {
	element = Nil;
	ab_loop_list_ = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)4L + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
		(SI_Long)2L),(SI_Long)4L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = eval_cons_1(media_file_evaluation_value(element,
		Nil),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	car_new_value = allocate_evaluation_sequence(temp_1);
    }
    else if (EQ(temp_1,Qtext)) {
	element = Nil;
	ab_loop_list_ = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)4L + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
		(SI_Long)2L),(SI_Long)4L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = eval_cons_1(copy_text_string(element),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	car_new_value = allocate_evaluation_sequence(temp_1);
    }
    else if (EQ(temp_1,Qbinary)) {
	element = Nil;
	ab_loop_list_ = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)4L + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
		(SI_Long)2L),(SI_Long)4L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	wide_string_bv16 = copy_text_string(element);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	length_1 = UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	UBYTE_16_ISASET_1(wide_string_bv16,length_1,(SI_Long)1L);
	ab_loopvar__2 = eval_cons_1(wide_string_bv16,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	temp_1 = ab_loopvar_;
	goto end_3;
	temp_1 = Qnil;
      end_3:;
	car_new_value = allocate_evaluation_sequence(temp_1);
    }
    else
	car_new_value = Qnil;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qcreate_date;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = copy_managed_float(FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)6L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)6L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    if ( !EQ(FIXNUM_LE(ISVREF(file,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(file,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(file,
	    (SI_Long)2L),(SI_Long)0L),Qab_directory)) {
	gensymed_symbol_2 = (SI_Long)2L;
	gensymed_symbol_3 = FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size) ? IFIX(ISVREF(file,
		(SI_Long)3L + IFIX(Managed_array_index_offset))) : 
		IFIX(ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)3L));
	gensymed_symbol_2 = gensymed_symbol_2 * gensymed_symbol_3;
	gensymed_symbol_3 = (FIXNUM_LE(ISVREF(file,(SI_Long)1L),
		Maximum_in_place_array_size) ? TRUEP(ISVREF(file,
		(SI_Long)7L + IFIX(Managed_array_index_offset))) : 
		TRUEP(ISVREF(ISVREF(file,(SI_Long)2L),(SI_Long)7L))) ? 
		(SI_Long)1L : (SI_Long)0L;
	temp_1 = eval_list_2(Qsize_in_bytes,FIX(gensymed_symbol_2 + 
		gensymed_symbol_3));
    }
    else
	temp_1 = Nil;
    return allocate_evaluation_structure(nconc2(temp,
	    nconc2(gensymed_symbol,temp_1)));
}

static Object string_constant_18;  /* "~S is not a structure" */

static Object Qg2_java_bean;       /* g2-java-bean */

static Object string_constant_19;  /* "bad owner" */

static Object list_constant_2;     /* # */

static Object string_constant_20;  /* "media-bin type error" */

static Object string_constant_21;  /* "media-bin name error" */

static Object list_constant_3;     /* # */

static Object string_constant_22;  /* "media-bin status error" */

static Object string_constant_23;  /* "media-bin size-in-bytes error" */

static Object string_constant_24;  /* "media-bin create-date error" */

static Object string_constant_25;  /* "media-bin contents error" */

/* EVALUATION-VALUE-MEDIA-BIN */
Object evaluation_value_media_bin(evaluation_value)
    Object evaluation_value;
{
    Object owner, type, name, status, contents, create_date, size_in_bytes, x2;
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object held_vector, element, value_or_error, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, temp_1, temp_2, temp_3, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long next_index, length_1;
    char temp;

    x_note_fn_call(229,78);
    if ( !(CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qab_structure)))
	return tformat_text_string(2,string_constant_18,evaluation_value);
    owner = estructure_slot(evaluation_value,Qowner,Nil);
    type = estructure_slot(evaluation_value,Qtype,Nil);
    name = estructure_slot(evaluation_value,Qname,Nil);
    status = estructure_slot(evaluation_value,Qstatus,Nil);
    contents = estructure_slot(evaluation_value,Qcontents,Nil);
    create_date = estructure_slot(evaluation_value,Qcreate_date,Nil);
    size_in_bytes = estructure_slot(evaluation_value,Qsize_in_bytes,Nil);
    temp =  !TRUEP(owner);
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(owner) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(owner)) > (SI_Long)2L &&  
		!EQ(ISVREF(owner,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(owner,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qimage_definition,
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
    }
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(owner) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(owner)) > (SI_Long)2L &&  
		!EQ(ISVREF(owner,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(owner,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qg2_java_bean,
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
    }
    if ( !temp)
	return tformat_text_string(1,string_constant_19);
    if ( !TRUEP(memq_function(type,list_constant_2)))
	return tformat_text_string(1,string_constant_20);
    if ( !TRUEP(text_string_p(name)))
	return tformat_text_string(1,string_constant_21);
    if ( !TRUEP(memq_function(status,list_constant_3)))
	return tformat_text_string(1,string_constant_22);
    if ( !( !TRUEP(size_in_bytes) || FIXNUMP(size_in_bytes) && (SI_Long)0L 
	    <= IFIX(size_in_bytes)))
	return tformat_text_string(1,string_constant_23);
    if ( !(INLINE_DOUBLE_FLOAT_VECTOR_P(create_date) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(create_date)) == (SI_Long)1L))
	return tformat_text_string(1,string_constant_24);
    if ( !(CONSP(contents) && EQ(M_CDR(contents),Qsequence)))
	return tformat_text_string(1,string_constant_25);
    gensymed_symbol = contents;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
    value_or_error = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    element = validated_elt;
    value_or_error = EQ(type,Qab_directory) ? (CONSP(element) && 
	    EQ(M_CDR(element),Qab_structure) ? 
	    evaluation_value_media_bin(element) : tformat_text_string(1,
	    string_constant_25)) : text_string_p(element) ? Nil : 
	    tformat_text_string(1,string_constant_25);
    if (text_string_p(value_or_error))
	return VALUES_1(value_or_error);
    temp_1 = value_or_error;
    if (temp_1);
    else
	temp_1 = copy_text_string(element);
    ab_loopvar__2 = slot_value_cons_1(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    contents = ab_loopvar_;
    goto end_1;
    contents = Qnil;
  end_1:;
    temp_2 = FIXNUMP(name) || name && SYMBOLP(name) || 
	    SIMPLE_VECTOR_P(name) ? name : copy_if_evaluation_value_1(name);
    temp_3 = size_in_bytes ? FIX(IFIX(size_in_bytes) >>  -  - (SI_Long)1L) 
	    : length(contents);
    temp_4 = contents;
    temp_1 = size_in_bytes ? ((SI_Long)1L == (IFIX(size_in_bytes) & 
	    (SI_Long)1L) ? T : Nil) : Nil;
    return make_media_file_1(type,temp_2,status,temp_3,temp_4,temp_1,
	    FIXNUMP(create_date) || create_date && SYMBOLP(create_date) || 
	    SIMPLE_VECTOR_P(create_date) ? create_date : 
	    copy_if_evaluation_value_1(create_date));
}

/* INITIAL-MEDIA-BIN-DATA */
Object initial_media_bin_data(class_1)
    Object class_1;
{
    x_note_fn_call(229,79);
    return VALUES_1(Nil);
}

/* GET-MEDIA-BIN-DATA */
Object get_media_bin_data(media_bin)
    Object media_bin;
{
    Object temp, owner_qm, gensymed_symbol, x, y, xa, ya;
    char temp_1;

    x_note_fn_call(229,80);
    temp = ISVREF(media_bin,(SI_Long)20L);
    owner_qm = ISVREF(media_bin,(SI_Long)23L);
    if (owner_qm) {
	gensymed_symbol = ISVREF(owner_qm,(SI_Long)3L);
	temp_1 = SIMPLE_VECTOR_P(owner_qm) ? EQ(ISVREF(owner_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(media_bin,(SI_Long)24L);
	    if (FIXNUMP(y))
		temp_1 = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
			    M_CDR(x)) : TRUEP(Qnil);
	    }
	}
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    temp = media_file_evaluation_value(temp,temp_1 ? owner_qm : Nil);
    return VALUES_1(temp);
}

/* SET-MEDIA-BIN-DATA */
Object set_media_bin_data(media_bin,new_value)
    Object media_bin, new_value;
{
    Object media_data, temp;

    x_note_fn_call(229,81);
    media_data = evaluation_value_media_bin(new_value);
    if (text_string_p(media_data))
	temp = media_data;
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(media_bin,Qmedia_bin_data);
	SVREF(media_bin,FIX((SI_Long)20L)) = media_data;
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object string_constant_26;  /* "This kb has called an unsupported system procedure which is no longer ~
				    *        present in G2."
				    */

/* G2-NEW-SECRET-ENTITY */
Object g2_new_secret_entity(workspace,g2_window,class_name)
    Object workspace, g2_window, class_name;
{
    Object top_of_stack, message_1;

    x_note_fn_call(229,82);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(1,string_constant_26);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

void media_INIT()
{
    Object temp, temp_1, temp_2, reclaim_structure_for_media_stream_1;
    Object gensymed_symbol;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, list_constant_42, Qexternal_java_class;
    Object Qcreate_icon_description, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object AB_package, string_constant_56, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object Qtw_resource, Qicon_color, string_constant_51, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, Qentity, Qitem;
    Object Qg2_new_secret_entity;
    Object Qfunction_keeps_procedure_environment_valid_qm, Qset_media_bin_data;
    Object Qget_media_bin_data, Qinitial_media_bin_data, list_constant_41;
    Object Qdatum, list_constant_5, Qexclude_from_wildcard_denotation;
    Object Qvirtual_attributes_local_to_class, list_constant_40;
    Object list_constant_36, Qget_cached_media_bin, Qinitial_cached_media_bin;
    Object list_constant_39, list_constant_38, Qcached_media_bin;
    Object list_constant_37, Qab_or, Qno_item, Qab_class;
    Object Qclasses_which_define, Qdescribe_frame;
    Object Qdescribe_frame_for_media_bin, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2_media_bin_upload_binary_file;
    Object Qg2_media_bin_delete_system_rpc_internal, Qg2_media_bin_delete;
    Object Qsystem_defined_rpc, list_constant_20, list_constant_35;
    Object list_constant_9, list_constant_8;
    Object Qg2_media_bin_make_directory_system_rpc_internal;
    Object Qg2_media_bin_make_directory, list_constant_34, list_constant_10;
    Object Qg2_media_bin_describe_system_rpc_internal, Qg2_media_bin_describe;
    Object list_constant_30, list_constant_33, list_constant_32;
    Object list_constant_31, Qlocation_sequence_or_file_descriptor;
    Object Qg2_media_bin_read_system_rpc_internal, Qg2_media_bin_read;
    Object list_constant_29, list_constant_28, list_constant_22;
    Object list_constant_27, list_constant_17, list_constant_26, Qmax_length;
    Object list_constant_15, Qg2_media_bin_write_system_rpc_internal;
    Object Qg2_media_bin_write, list_constant_25, list_constant_24;
    Object list_constant_23, Qdata, Qunsigned_vector_16;
    Object Qg2_media_bin_ignore_last_byte_system_rpc_internal;
    Object Qg2_media_bin_ignore_last_byte, list_constant_21;
    Object Qg2_media_bin_set_ignore_last_byte_system_rpc_internal;
    Object Qg2_media_bin_set_ignore_last_byte;
    Object Qg2_media_bin_close_stream_system_rpc_internal;
    Object Qg2_media_bin_close_stream, list_constant_19, Qtruth_value;
    Object list_constant_18, Qabort_ev, Qfile_descriptor, list_constant_16;
    Object Qg2_media_bin_open_stream_system_rpc_internal;
    Object Qg2_media_bin_open_stream, list_constant_14, list_constant_13;
    Object list_constant_12, list_constant_11, list_constant_7, Qmode;
    Object Qdata_type, Qdirection, list_constant_6, Qlocation_sequence;
    Object Qinitialize_after_reading, Qinitialize_after_reading_for_media_bin;
    Object Qmedia_stream, Qreclaim_structure, Qoutstanding_media_stream_count;
    Object Qmedia_stream_structure_memory_usage, Qutilities2;
    Object string_constant_41, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_40, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qslot_value_reclaimer;
    Object Qreclaim_media_bin_owner_serial_value, Qmedia_bin_owner_serial;
    Object Qreclaim_media_bin_owner_qm_value, Qmedia_bin_owner_qm, Qinitialize;
    Object Qinitialize_for_media_bin, Qcleanup, Qcleanup_for_media_bin;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36, string_constant_35, list_constant_4;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27;

    x_note_fn_call(229,83);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qmedia_bin = STATIC_SYMBOL("MEDIA-BIN",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qentity,Qitem);
    check_if_superior_classes_are_defined(Qmedia_bin,list_constant_4);
    string_constant_27 = STATIC_STRING("1l1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    string_constant_28 = 
	    STATIC_STRING("1q4z8r8u8u83V3y83V3y01p8w9k3uy3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk1m3k");
    string_constant_29 = 
	    STATIC_STRING("y3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-my1q83qy");
    string_constant_30 = 
	    STATIC_STRING("1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m");
    string_constant_31 = 
	    STATIC_STRING("3hy3hy9l1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Gy+s3-9y3-1y3-0y3-5y3--ykp3A++y1ms3Hy83-Vy1o83Gy+s3fy3-*y3-5y3-Aykko3A++y1mt3ay83-Vy1o");
    string_constant_32 = 
	    STATIC_STRING("83Oy1m3eyp1mpp1mp3fy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r83V4");
    string_constant_33 = 
	    STATIC_STRING("y83V4y83V3y83V3y00001n1l8l1l83Cy1l8o000004z8r83V8y83V8y83V3y83V3y00001m1l8l1l8o000004z8r83V5y83V5y83V3y83V3y0k001m1l8l1l8o000004");
    string_constant_34 = 
	    STATIC_STRING("z8r83V7y83V7y83V3y83V3y00001m1l8l1l8o000004z8r83V6y83V6y83V3y83V3y00001m1l8l1l8o00000");
    string_constant_35 = 
	    STATIC_STRING("1s8q1n83V3y1m83-+y83Ry8t1m8u1p8w9k3uy3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1");
    string_constant_36 = 
	    STATIC_STRING("mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-m");
    string_constant_37 = 
	    STATIC_STRING("y1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1");
    string_constant_38 = 
	    STATIC_STRING("mn3hy1m3hy3hy9l1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Gy5pMEDIA1ms3Hy83-Vy1o83Gy5o-BIN1mt3ay83-Vy1o83Oy1m3eyp1mpp1mp3fy83-ny1o83Oy1mp");
    string_constant_39 = 
	    STATIC_STRING("3fy1m3ey3fy1m3eyp1p83V4y08l83Cy8o1o83V8y08l8o1o83V5yk8l8o1o83V7y08l8o1o83V6y08l8o");
    temp = regenerate_optimized_constant(string_constant_27);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    temp_1 = regenerate_optimized_constant(list(7,string_constant_28,
	    string_constant_29,string_constant_30,string_constant_31,
	    string_constant_32,string_constant_33,string_constant_34));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    add_class_to_environment(9,Qmedia_bin,list_constant_4,Nil,temp,Nil,
	    temp_1,list_constant_4,
	    regenerate_optimized_constant(LIST_5(string_constant_35,
	    string_constant_36,string_constant_37,string_constant_38,
	    string_constant_39)),Nil);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qimage_definition_media_bin = 
	    STATIC_SYMBOL("IMAGE-DEFINITION-MEDIA-BIN",AB_package);
    Qcleanup_for_media_bin = STATIC_SYMBOL("CLEANUP-FOR-MEDIA-BIN",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_media_bin,
	    STATIC_FUNCTION(cleanup_for_media_bin,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_media_bin);
    set_get(Qmedia_bin,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qmedia_bin,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qmedia_bin_data = STATIC_SYMBOL("MEDIA-BIN-DATA",AB_package);
    Qab_directory = STATIC_SYMBOL("DIRECTORY",AB_package);
    Qinitialize_for_media_bin = STATIC_SYMBOL("INITIALIZE-FOR-MEDIA-BIN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_media_bin,
	    STATIC_FUNCTION(initialize_for_media_bin,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_media_bin);
    set_get(Qmedia_bin,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qmedia_bin,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qmedia_bin_owner_qm = STATIC_SYMBOL("MEDIA-BIN-OWNER\?",AB_package);
    Qreclaim_media_bin_owner_qm_value = 
	    STATIC_SYMBOL("RECLAIM-MEDIA-BIN-OWNER\?-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_media_bin_owner_qm_value,
	    STATIC_FUNCTION(reclaim_media_bin_owner_qm_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qmedia_bin_owner_qm,
	    SYMBOL_FUNCTION(Qreclaim_media_bin_owner_qm_value),
	    Qslot_value_reclaimer);
    Qmedia_bin_owner_serial = STATIC_SYMBOL("MEDIA-BIN-OWNER-SERIAL",
	    AB_package);
    Qreclaim_media_bin_owner_serial_value = 
	    STATIC_SYMBOL("RECLAIM-MEDIA-BIN-OWNER-SERIAL-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_media_bin_owner_serial_value,
	    STATIC_FUNCTION(reclaim_media_bin_owner_serial_value,NIL,FALSE,
	    2,2));
    mutate_global_property(Qmedia_bin_owner_serial,
	    SYMBOL_FUNCTION(Qreclaim_media_bin_owner_serial_value),
	    Qslot_value_reclaimer);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qnew = STATIC_SYMBOL("NEW",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_media_stream_g2_struct = 
	    STATIC_SYMBOL("MEDIA-STREAM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmedia_stream = STATIC_SYMBOL("MEDIA-STREAM",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_media_stream_g2_struct,
	    Qmedia_stream,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qmedia_stream,
	    Qg2_defstruct_structure_name_media_stream_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_media_stream == UNBOUND)
	The_type_description_of_media_stream = Nil;
    string_constant_40 = 
	    STATIC_STRING("43Dy8m83kdy1n83kdy8n8k1l8n0000001l1n8y83-4ny1o83-6Wy83-6Xy83-6Vy83-6Uykrk0k0");
    temp = The_type_description_of_media_stream;
    The_type_description_of_media_stream = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_40));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_media_stream_g2_struct,
	    The_type_description_of_media_stream,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qmedia_stream,
	    The_type_description_of_media_stream,Qtype_description_of_type);
    Qoutstanding_media_stream_count = 
	    STATIC_SYMBOL("OUTSTANDING-MEDIA-STREAM-COUNT",AB_package);
    Qmedia_stream_structure_memory_usage = 
	    STATIC_SYMBOL("MEDIA-STREAM-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_41 = STATIC_STRING("1q83kdy8s83-e7y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_media_stream_count);
    push_optimized_constant(Qmedia_stream_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_41));
    Qchain_of_available_media_streams = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-MEDIA-STREAMS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_media_streams,
	    Chain_of_available_media_streams);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_media_streams,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qmedia_stream_count = STATIC_SYMBOL("MEDIA-STREAM-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmedia_stream_count,Media_stream_count);
    record_system_variable(Qmedia_stream_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_media_streams_vector == UNBOUND)
	Chain_of_available_media_streams_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmedia_stream_structure_memory_usage,
	    STATIC_FUNCTION(media_stream_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_media_stream_count,
	    STATIC_FUNCTION(outstanding_media_stream_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_media_stream_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_media_stream,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmedia_stream,
	    reclaim_structure_for_media_stream_1);
    Media_block_size = FIX((SI_Long)1024L);
    Qinitialize_after_reading_for_media_bin = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-MEDIA-BIN",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_media_bin,
	    STATIC_FUNCTION(initialize_after_reading_for_media_bin,NIL,
	    FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_media_bin);
    set_get(Qmedia_bin,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qmedia_bin,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qg2_media_bin_open_stream = STATIC_SYMBOL("G2-MEDIA-BIN-OPEN-STREAM",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_open_stream,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_open_stream,
	    STATIC_FUNCTION(g2_media_bin_open_stream,NIL,FALSE,6,6));
    Qg2_media_bin_open_stream_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-OPEN-STREAM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qab_class,Qmedia_bin);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qmedia_bin,Ktype,
	    list_constant_5);
    Qlocation_sequence = STATIC_SYMBOL("LOCATION-SEQUENCE",AB_package);
    list_constant_6 = STATIC_CONS(Qsequence,Qnil);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qlocation_sequence,Ktype,
	    list_constant_6);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Qname,Ktype,Qtext);
    Qdirection = STATIC_SYMBOL("DIRECTION",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Ktype,Qsymbol);
    list_constant_11 = STATIC_CONS(Qdirection,list_constant_7);
    Qdata_type = STATIC_SYMBOL("DATA-TYPE",AB_package);
    list_constant_12 = STATIC_CONS(Qdata_type,list_constant_7);
    Qmode = STATIC_SYMBOL("MODE",AB_package);
    list_constant_13 = STATIC_CONS(Qmode,list_constant_7);
    list_constant_14 = STATIC_LIST((SI_Long)6L,list_constant_8,
	    list_constant_9,list_constant_10,list_constant_11,
	    list_constant_12,list_constant_13);
    list_constant_15 = STATIC_CONS(Qinteger,Qnil);
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    mutate_global_property(Qg2_media_bin_open_stream,
	    make_system_rpc_1(Qg2_media_bin_open_stream_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_14,
	    Nil,T),list_constant_15),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_open_stream,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_open_stream_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_open_stream_system_rpc_internal,
	    NIL,FALSE,7,7));
    Qbinary = STATIC_SYMBOL("BINARY",AB_package);
    list_constant_16 = STATIC_CONS(Qtext,Qnil);
    list_constant = STATIC_CONS(Qbinary,list_constant_16);
    Qcreate_or_overwrite = STATIC_SYMBOL("CREATE-OR-OVERWRITE",AB_package);
    Qwriting = STATIC_SYMBOL("WRITING",AB_package);
    Qread_shared = STATIC_SYMBOL("READ-SHARED",AB_package);
    Qreading = STATIC_SYMBOL("READING",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnormal,Qreading);
    Qg2_media_bin_close_stream = STATIC_SYMBOL("G2-MEDIA-BIN-CLOSE-STREAM",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_close_stream,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_close_stream,
	    STATIC_FUNCTION(g2_media_bin_close_stream,NIL,FALSE,3,3));
    Qg2_media_bin_close_stream_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-CLOSE-STREAM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qfile_descriptor = STATIC_SYMBOL("FILE-DESCRIPTOR",AB_package);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,Qfile_descriptor,Ktype,
	    list_constant_15);
    Qabort_ev = STATIC_SYMBOL("ABORT-EV",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qabort_ev,Ktype,Qdatum);
    list_constant_19 = STATIC_LIST((SI_Long)3L,list_constant_8,
	    list_constant_17,list_constant_18);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_20 = STATIC_CONS(Qtruth_value,Qnil);
    mutate_global_property(Qg2_media_bin_close_stream,
	    make_system_rpc_1(Qg2_media_bin_close_stream_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_19,
	    Nil,T),list_constant_20),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_close_stream,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_media_bin_close_stream_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_close_stream_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_media_bin_set_ignore_last_byte = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-SET-IGNORE-LAST-BYTE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_set_ignore_last_byte,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_set_ignore_last_byte,
	    STATIC_FUNCTION(g2_media_bin_set_ignore_last_byte,NIL,FALSE,2,2));
    Qg2_media_bin_set_ignore_last_byte_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-SET-IGNORE-LAST-BYTE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,list_constant_8,
	    list_constant_17);
    mutate_global_property(Qg2_media_bin_set_ignore_last_byte,
	    make_system_rpc_1(Qg2_media_bin_set_ignore_last_byte_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_20),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_set_ignore_last_byte,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_media_bin_set_ignore_last_byte_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_set_ignore_last_byte_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_media_bin_ignore_last_byte = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-IGNORE-LAST-BYTE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_ignore_last_byte,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_ignore_last_byte,
	    STATIC_FUNCTION(g2_media_bin_ignore_last_byte,NIL,FALSE,2,2));
    Qg2_media_bin_ignore_last_byte_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-IGNORE-LAST-BYTE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_media_bin_ignore_last_byte,
	    make_system_rpc_1(Qg2_media_bin_ignore_last_byte_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_20),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_ignore_last_byte,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_media_bin_ignore_last_byte_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_ignore_last_byte_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_media_bin_write = STATIC_SYMBOL("G2-MEDIA-BIN-WRITE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_write,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_write,
	    STATIC_FUNCTION(g2_media_bin_write,NIL,FALSE,3,3));
    Qg2_media_bin_write_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-WRITE-SYSTEM-RPC-INTERNAL",AB_package);
    Qdata = STATIC_SYMBOL("DATA",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qunsigned_vector_16 = STATIC_SYMBOL("UNSIGNED-VECTOR-16",AB_package);
    list_constant_22 = STATIC_CONS(Qunsigned_vector_16,Qnil);
    list_constant_23 = STATIC_LIST((SI_Long)3L,Qab_or,Qtext,list_constant_22);
    list_constant_24 = STATIC_LIST((SI_Long)3L,Qdata,Ktype,list_constant_23);
    list_constant_25 = STATIC_LIST((SI_Long)3L,list_constant_8,
	    list_constant_17,list_constant_24);
    mutate_global_property(Qg2_media_bin_write,
	    make_system_rpc_1(Qg2_media_bin_write_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_25,
	    Nil,T),list_constant_20),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_write,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_media_bin_write_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_write_system_rpc_internal,NIL,
	    FALSE,4,4));
    Qg2_media_bin_read = STATIC_SYMBOL("G2-MEDIA-BIN-READ",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_read,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_read,
	    STATIC_FUNCTION(g2_media_bin_read,NIL,FALSE,3,3));
    Qg2_media_bin_read_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-READ-SYSTEM-RPC-INTERNAL",AB_package);
    Qmax_length = STATIC_SYMBOL("MAX-LENGTH",AB_package);
    list_constant_26 = STATIC_CONS(Ktype,list_constant_15);
    list_constant_27 = STATIC_CONS(Qmax_length,list_constant_26);
    list_constant_28 = STATIC_LIST((SI_Long)3L,list_constant_8,
	    list_constant_17,list_constant_27);
    list_constant_29 = STATIC_CONS(list_constant_22,Qnil);
    mutate_global_property(Qg2_media_bin_read,
	    make_system_rpc_1(Qg2_media_bin_read_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_28,
	    Nil,T),list_constant_29),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_read,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_media_bin_read_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_read_system_rpc_internal,NIL,
	    FALSE,4,4));
    Qg2_media_bin_describe = STATIC_SYMBOL("G2-MEDIA-BIN-DESCRIBE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_describe,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsize = STATIC_SYMBOL("SIZE",AB_package);
    Qsize_in_bytes = STATIC_SYMBOL("SIZE-IN-BYTES",AB_package);
    Qcreate_date = STATIC_SYMBOL("CREATE-DATE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qcontents = STATIC_SYMBOL("CONTENTS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_describe,
	    STATIC_FUNCTION(g2_media_bin_describe,NIL,FALSE,2,2));
    Qg2_media_bin_describe_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-DESCRIBE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qlocation_sequence_or_file_descriptor = 
	    STATIC_SYMBOL("LOCATION-SEQUENCE-OR-FILE-DESCRIPTOR",AB_package);
    list_constant_30 = STATIC_CONS(Qdatum,Qnil);
    list_constant_31 = STATIC_CONS(Ktype,list_constant_30);
    list_constant_32 = STATIC_CONS(Qlocation_sequence_or_file_descriptor,
	    list_constant_31);
    list_constant_33 = STATIC_LIST((SI_Long)2L,list_constant_8,
	    list_constant_32);
    mutate_global_property(Qg2_media_bin_describe,
	    make_system_rpc_1(Qg2_media_bin_describe_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_33,
	    Nil,T),list_constant_30),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_describe,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_media_bin_describe_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_describe_system_rpc_internal,NIL,
	    FALSE,3,3));
    Qg2_media_bin_make_directory = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-MAKE-DIRECTORY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_make_directory,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_make_directory,
	    STATIC_FUNCTION(g2_media_bin_make_directory,NIL,FALSE,3,3));
    Qg2_media_bin_make_directory_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-MAKE-DIRECTORY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)3L,list_constant_8,
	    list_constant_9,list_constant_10);
    mutate_global_property(Qg2_media_bin_make_directory,
	    make_system_rpc_1(Qg2_media_bin_make_directory_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_34,
	    Nil,T),list_constant_20),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_make_directory,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_media_bin_make_directory_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_make_directory_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_media_bin_delete = STATIC_SYMBOL("G2-MEDIA-BIN-DELETE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_delete,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_delete,
	    STATIC_FUNCTION(g2_media_bin_delete,NIL,FALSE,2,2));
    Qg2_media_bin_delete_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-DELETE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)2L,list_constant_8,
	    list_constant_9);
    mutate_global_property(Qg2_media_bin_delete,
	    make_system_rpc_1(Qg2_media_bin_delete_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_35,
	    Nil,T),list_constant_20),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_media_bin_delete,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_media_bin_delete_system_rpc_internal,
	    STATIC_FUNCTION(g2_media_bin_delete_system_rpc_internal,NIL,
	    FALSE,3,3));
    string_constant = STATIC_STRING("~NV is not a sequence of text");
    Qg2_media_bin_upload_binary_file = 
	    STATIC_SYMBOL("G2-MEDIA-BIN-UPLOAD-BINARY-FILE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_media_bin_upload_binary_file,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_media_bin_upload_binary_file,
	    STATIC_FUNCTION(g2_media_bin_upload_binary_file,NIL,FALSE,4,4));
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_36,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qdescribe_frame_for_media_bin = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-MEDIA-BIN",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_media_bin,
	    STATIC_FUNCTION(describe_frame_for_media_bin,NIL,FALSE,1,1));
    Qdescribe_frame = STATIC_SYMBOL("DESCRIBE-FRAME",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_media_bin);
    set_get(Qmedia_bin,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qmedia_bin,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_1 = STATIC_STRING(" ");
    string_constant_2 = STATIC_STRING("~A:");
    array_constant_1 = STATIC_ARRAY(list_constant_36,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    string_constant_3 = STATIC_STRING("~A size = ~s");
    Qcached_media_bin = STATIC_SYMBOL("CACHED-MEDIA-BIN",AB_package);
    temp_2 = CONS(Qcached_media_bin,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qimage_definition),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qcached_media_bin,temp);
    set_property_value_function(get_symbol_properties_function(Qimage_definition),
	    Qvirtual_attributes_local_to_class,temp_2);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qab_class,Qimage_definition);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_37 = STATIC_CONS(Qno_item,Qnil);
    list_constant_39 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_37);
    Qinitial_cached_media_bin = STATIC_SYMBOL("INITIAL-CACHED-MEDIA-BIN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_cached_media_bin,
	    STATIC_FUNCTION(initial_cached_media_bin,NIL,FALSE,1,1));
    Qget_cached_media_bin = STATIC_SYMBOL("GET-CACHED-MEDIA-BIN",AB_package);
    SET_SYMBOL_FUNCTION(Qget_cached_media_bin,
	    STATIC_FUNCTION(get_cached_media_bin,NIL,FALSE,1,1));
    add_virtual_attribute(Qcached_media_bin,list_constant_38,
	    list_constant_39,Qnil,
	    SYMBOL_FUNCTION(Qinitial_cached_media_bin),
	    SYMBOL_FUNCTION(Qget_cached_media_bin),Nil);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_36,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qg2_java_bean_media_bin = STATIC_SYMBOL("G2-JAVA-BEAN-MEDIA-BIN",
	    AB_package);
    string_constant_4 = 
	    STATIC_STRING("Media file ~A not found in media bin ~NF");
    string_constant_5 = STATIC_STRING("file ~A in ~NF is locked");
    string_constant_6 = 
	    STATIC_STRING("~a in media bin ~NF is not a directory");
    string_constant_7 = STATIC_STRING("~a in media bin ~NF must be BINARY");
    string_constant_8 = 
	    STATIC_STRING("opening file, ~a, in media bin ~NF with unknown directionn ~A");
    string_constant_9 = 
	    STATIC_STRING("opening file, ~a, in media bin ~NF with unsupported file type, ~A");
    string_constant_10 = 
	    STATIC_STRING("opening file, ~a, in media bin ~NF with unsupported mode, ~A");
    string_constant_11 = 
	    STATIC_STRING("attempting to ~a file, ~a, in media bin ~NF, open for ~a");
    string_constant_12 = 
	    STATIC_STRING("reading negative (~s) number of bytes or characters from ~a in ~NF");
    string_constant_13 = 
	    STATIC_STRING("attempting to create ~a in ~NF, which already exists");
    string_constant_14 = 
	    STATIC_STRING("attempting to use ~a in ~NF, which was deleted");
    string_constant_15 = 
	    STATIC_STRING("cannot open ~a in ~NF, a ~a file, as ~a");
    string_constant_16 = 
	    STATIC_STRING("No stream in ~NF known for file descriptor ~s");
    string_constant_17 = 
	    STATIC_STRING("Cannot open for ~a for uploading into ~NF");
    array_constant_3 = STATIC_ARRAY(list_constant_36,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qowner = STATIC_SYMBOL("OWNER",AB_package);
    Qstatus = STATIC_SYMBOL("STATUS",AB_package);
    string_constant_18 = STATIC_STRING("~S is not a structure");
    Qg2_java_bean = STATIC_SYMBOL("G2-JAVA-BEAN",AB_package);
    string_constant_19 = STATIC_STRING("bad owner");
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_directory,Qtext,Qbinary);
    string_constant_20 = STATIC_STRING("media-bin type error");
    string_constant_21 = STATIC_STRING("media-bin name error");
    list_constant_40 = STATIC_CONS(Qreading,Qnil);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)4L,Qnormal,Qnew,Qwriting,
	    list_constant_40);
    string_constant_22 = STATIC_STRING("media-bin status error");
    string_constant_23 = STATIC_STRING("media-bin size-in-bytes error");
    string_constant_24 = STATIC_STRING("media-bin create-date error");
    string_constant_25 = STATIC_STRING("media-bin contents error");
    temp_2 = CONS(Qmedia_bin_data,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qmedia_bin),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qmedia_bin_data,temp);
    set_property_value_function(get_symbol_properties_function(Qmedia_bin),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qexclude_from_wildcard_denotation = 
	    STATIC_SYMBOL("EXCLUDE-FROM-WILDCARD-DENOTATION",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,
	    Qexclude_from_wildcard_denotation,Qt);
    Qinitial_media_bin_data = STATIC_SYMBOL("INITIAL-MEDIA-BIN-DATA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_media_bin_data,
	    STATIC_FUNCTION(initial_media_bin_data,NIL,FALSE,1,1));
    Qget_media_bin_data = STATIC_SYMBOL("GET-MEDIA-BIN-DATA",AB_package);
    SET_SYMBOL_FUNCTION(Qget_media_bin_data,
	    STATIC_FUNCTION(get_media_bin_data,NIL,FALSE,1,1));
    Qset_media_bin_data = STATIC_SYMBOL("SET-MEDIA-BIN-DATA",AB_package);
    SET_SYMBOL_FUNCTION(Qset_media_bin_data,
	    STATIC_FUNCTION(set_media_bin_data,NIL,FALSE,2,2));
    add_virtual_attribute(Qmedia_bin_data,list_constant_5,Qdatum,
	    list_constant_41,SYMBOL_FUNCTION(Qinitial_media_bin_data),
	    SYMBOL_FUNCTION(Qget_media_bin_data),
	    SYMBOL_FUNCTION(Qset_media_bin_data));
    Qg2_new_secret_entity = STATIC_SYMBOL("G2-NEW-SECRET-ENTITY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_new_secret_entity,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_26 = 
	    STATIC_STRING("This kb has called an unsupported system procedure which is no longer ~\n       present in G2.");
    SET_SYMBOL_FUNCTION(Qg2_new_secret_entity,
	    STATIC_FUNCTION(g2_new_secret_entity,NIL,FALSE,3,3));
    Qtw_resource = STATIC_SYMBOL("TW-RESOURCE",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qtw_resource,list_constant_42);
    string_constant_42 = STATIC_STRING("1m1l8t1m8v83AIy");
    string_constant_43 = 
	    STATIC_STRING("1o4z8r83--y83--y83AIy83AIy00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_44 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_45 = 
	    STATIC_STRING("0004z8r83-Fy83-Fy83AIy83AIy00001q1l8l1m8p01l83Cy1l83Uy1l83*-y1m83Dy53MySee comment in class block000004z8r8u8u83AIy83AIy01p8w9k3");
    string_constant_46 = 
	    STATIC_STRING("ky3ky1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1");
    string_constant_47 = 
	    STATIC_STRING("m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky");
    string_constant_48 = 
	    STATIC_STRING("1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy9l1p83Jy1mkk1mk3ky1m3k");
    string_constant_49 = 
	    STATIC_STRING("y3ky1m3kyk1o83Gy+s3-Gy3-Jy3fykkkn3A++y1ms3Hy83-Vy1o83Gy+s3-Ey3-Fy3-Ey3-=ykko3A++y1mt3ay83-Vy1o83Oy1m3eyp1mpp1mp3fy83-ny1o83Oy1mp");
    string_constant_50 = 
	    STATIC_STRING("3fy1m3ey3fy1m3eyp001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r83Z1y83Z1y83AIy83AIy00001m1l8o1l8l0000");
    string_constant_51 = STATIC_STRING("0");
    string_constant_52 = 
	    STATIC_STRING("1q8q1o83AIy1m83Ry83-+y8t1m8v83AIy1n83--y01m8p83-*y1p83-Fy08l1m8p083Cy1m8u1p8w9k3ky3ky1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-");
    string_constant_53 = 
	    STATIC_STRING("Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn");
    string_constant_54 = 
	    STATIC_STRING("3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1m");
    string_constant_55 = 
	    STATIC_STRING("k3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy9l1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Gy5nTW-1ms3Hy83-Vy1o83Gy5oRSRC1mt3");
    string_constant_56 = 
	    STATIC_STRING("ay83-Vy1o83Oy1m3eyp1mpp1mp3fy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp1o83Z1y08o8l");
    temp = regenerate_optimized_constant(string_constant_42);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    temp_1 = regenerate_optimized_constant(list(9,string_constant_43,
	    string_constant_44,string_constant_45,string_constant_46,
	    string_constant_47,string_constant_48,string_constant_49,
	    string_constant_50,string_constant_51));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    add_class_to_environment(9,Qtw_resource,list_constant_42,Nil,temp,Nil,
	    temp_1,list_constant_42,
	    regenerate_optimized_constant(LIST_5(string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56)),Nil);
    Qexternal_java_class = STATIC_SYMBOL("EXTERNAL-JAVA-CLASS",AB_package);
    check_if_superior_classes_are_defined(Qexternal_java_class,
	    list_constant_42);
    string_constant_57 = STATIC_STRING("1m1l83Iy1l8t");
    string_constant_58 = 
	    STATIC_STRING("1s4z8r83-Fy83-Fy83Kuy83Kuy00001q1l8l1m8p83-ky1l83Cy1l83Uy1l83*-y1m83Dy53MySee comment in class block000004z8r83JXy83JXy83Kuy83Ku");
    string_constant_59 = 
	    STATIC_STRING("y00001o1l8o1l8l1m8p83Ky1l83Cy000004z8r83T1y83T1y83Kuy83Kuy00001p1m8p83T1y1l8o1l8l1l83Cy1l83Fy000004z8r8u8u83Kuy83Kuy01p8w9k3ky3k");
    string_constant_60 = 
	    STATIC_STRING("y13Fy1r83-1y2l83-Ly83-Wy2l83-my83-Ry2l83-ny83-gy2l835Jy83Ty2l835by83*2y2l835ay832Vy1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky83-my1q8");
    string_constant_61 = 
	    STATIC_STRING("3qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3h");
    string_constant_62 = 
	    STATIC_STRING("y1m3hy3hy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1");
    string_constant_63 = 
	    STATIC_STRING("m3hyn1mnn1n1mnn1mk3ky1mkk835Jy1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Oy1m3eyp1mpp1mp3fy835by1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1mt3Oy83-");
    string_constant_64 = 
	    STATIC_STRING("Vy835ay1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1mt3Ny83-Vy1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1ms3Ny83-Vy001o1l8l1l8o1l8z1m83Dy53YySee comme");
    string_constant_65 = 
	    STATIC_STRING("nt on ENTITY class definition000004z8r83T7y83T7y83Kuy83Kuy0+s3jy3gy3jykkkn3A++y001o1l8l1m8p83-qy1l83Fy1l83Cy000004z8r83XSy83XSy8");
    string_constant_66 = 
	    STATIC_STRING("3Kuy83Kuy00001p1m8p83T5y1l8o1l8l1l83Cy1l83Fy000004z8r83Cqy83Cqy83Kuy83Kuy00001p1m8p83T4y1l8o1l8l1l83Cy1l83Fy000004z8r83BKy83BKy8");
    string_constant_67 = 
	    STATIC_STRING("3Kuy83Kuy00001p1n8p83DGy83Gy1l8o1l8l1l83Cy1l83-3y00000");
    string_constant_68 = 
	    STATIC_STRING("1u8q1o83Kuy1m83Ry83-+y83Iy8t1p83-Fy08l1m8p83-ky83Cy1q83JXy08o8l1m8p83Ky83Cy1r83T1y01m8p83T1y8o8l83Cy83Fy1m8u1p8w9k3ky3ky13Fy1r83");
    string_constant_69 = 
	    STATIC_STRING("-1y2l83-Ly83-Wy2l83-my83-Ry2l83-ny83-gy2l835Jy83Ty2l835by83*2y2l835ay832Vy1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky83-my1q83qy1q1m3h");
    string_constant_70 = 
	    STATIC_STRING("yn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy");
    string_constant_71 = 
	    STATIC_STRING("83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn");
    string_constant_72 = 
	    STATIC_STRING("1n1mnn1mk3ky1mkk835Jy1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Oy1m3eyp1mpp1mp3fy835by1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1mt3Oy83-Vy835ay1o");
    string_constant_73 = 
	    STATIC_STRING("83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1mt3Ny83-Vy1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1ms3Ny83-Vy1q83T7y+s3jy3gy3jykkkn3A++y8l1m8p83-qy83Fy83");
    string_constant_74 = 
	    STATIC_STRING("Cy1r83XSy01m8p83T5y8o8l83Cy83Fy1r83Cqy01m8p83T4y8o8l83Cy83Fy1r83BKy01n8p83DGy83Gy8o8l83Cy83-3y");
    temp = regenerate_optimized_constant(string_constant_57);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(10,string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64,
	    string_constant_65,string_constant_66,string_constant_67));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qexternal_java_class,list_constant_42,Nil,
	    temp,Nil,temp_1,list_constant_42,
	    regenerate_optimized_constant(list(7,string_constant_68,
	    string_constant_69,string_constant_70,string_constant_71,
	    string_constant_72,string_constant_73,string_constant_74)),Nil);
}
