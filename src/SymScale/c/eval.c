/* eval.c
 * Input file:  eval.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "eval.h"


static Object string_constant;     /* "!!!" */

static Object Qgiver_of_value;     /* giver-of-value */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object Qvar_spot;           /* var-spot */

static Object Qclass_qualified_method;  /* class-qualified-method */

static Object array_constant_3;    /* # */

static Object Qthis_workspace;     /* this-workspace */

static Object string_constant_1;   /* "this workspace" */

static Object Qthis_window;        /* this-window */

static Object string_constant_2;   /* "this window" */

static Object Qthis_rule;          /* this-rule */

static Object string_constant_3;   /* "this rule" */

static Object Qthis_procedure;     /* this-procedure */

static Object string_constant_4;   /* "this procedure" */

static Object Qthis_procedure_invocation;  /* this-procedure-invocation */

static Object string_constant_5;   /* "this procedure-invocation" */

/* PRINT-DESIGNATION */
Object print_designation(designation)
    Object designation;
{
    Object temp, second_qm;
    SI_Long designation_length;
    char temp_1;

    x_note_fn_call(150,0);
    if (CONSP(designation)) {
	temp = M_CDR(designation);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    second_qm = temp_1 ? SECOND(designation) : Nil;
    designation_length = CONSP(designation) ? IFIX(length(designation)) : 
	    (SI_Long)0L;
    if (ATOM(designation)) {
	if (SYMBOLP(designation))
	    return twrite_symbol(1,designation);
	else
	    return twrite(string_constant);
    }
    else if (EQ(FIRST(designation),Qgiver_of_value)) {
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)4L));
	if (SYMBOLP(second_qm))
	    twrite_symbol(1,second_qm);
	else {
	    twrite_symbol(1,CAR(second_qm));
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)1L));
	    twrite_symbol(1,CDR(second_qm));
	}
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)8L));
	return print_designation(THIRD(designation));
    }
    else if (designation_length == (SI_Long)2L && CONSP(second_qm) && 
	    EQ(CAR(second_qm),Qvar_spot))
	return print_var_spot_for_stack(2,second_qm,Nil);
    else if ((designation_length == (SI_Long)2L || designation_length == 
	    (SI_Long)3L) && EQ(CAR(designation),Qvar_spot))
	return print_var_spot_for_stack(2,designation,Nil);
    else {
	if (designation_length == (SI_Long)2L) {
	    temp = SECOND(designation);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = SECOND(designation);
	    temp_1 = EQ(CAR(temp),Qclass_qualified_method);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = SECOND(designation);
	    twrite_symbol(1,SECOND(temp));
	    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
	    temp = SECOND(designation);
	    return twrite_symbol(1,THIRD(temp));
	}
	else if (designation_length == (SI_Long)2L && SYMBOLP(second_qm)) {
	    twrite_symbol(1,FIRST(designation));
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)1L));
	    return twrite_symbol(1,second_qm);
	}
	else {
	    if (CONSP(second_qm)) {
		temp_1 = EQ(FIRST(second_qm),Qthis_workspace);
		if (temp_1);
		else {
		    temp = CDR(second_qm);
		    temp_1 = CONSP(temp) ? EQ(SECOND(second_qm),
			    Qthis_workspace) : TRUEP(Nil);
		}
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		return twrite(string_constant_1);
	    else {
		if (CONSP(second_qm)) {
		    temp_1 = EQ(FIRST(second_qm),Qthis_window);
		    if (temp_1);
		    else {
			temp = CDR(second_qm);
			temp_1 = CONSP(temp) ? EQ(SECOND(second_qm),
				Qthis_window) : TRUEP(Nil);
		    }
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    return twrite(string_constant_2);
		else {
		    if (CONSP(second_qm)) {
			temp_1 = EQ(FIRST(second_qm),Qthis_rule);
			if (temp_1);
			else {
			    temp = CDR(second_qm);
			    temp_1 = CONSP(temp) ? EQ(SECOND(second_qm),
				    Qthis_rule) : TRUEP(Nil);
			}
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			return twrite(string_constant_3);
		    else {
			if (CONSP(second_qm)) {
			    temp_1 = EQ(FIRST(second_qm),Qthis_procedure);
			    if (temp_1);
			    else {
				temp = CDR(second_qm);
				temp_1 = CONSP(temp) ? 
					EQ(SECOND(second_qm),
					Qthis_procedure) : TRUEP(Nil);
			    }
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    return twrite(string_constant_4);
			else {
			    if (CONSP(second_qm)) {
				temp_1 = EQ(FIRST(second_qm),
					Qthis_procedure_invocation);
				if (temp_1);
				else {
				    temp = CDR(second_qm);
				    temp_1 = CONSP(temp) ? 
					    EQ(SECOND(second_qm),
					    Qthis_procedure_invocation) : 
					    TRUEP(Nil);
				}
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1)
				return twrite(string_constant_5);
			    else if (IFIX(length(designation)) == 
					(SI_Long)2L) {
				twrite_symbol(1,FIRST(designation));
				twrite_beginning_of_wide_string(array_constant_1,
					FIX((SI_Long)1L));
				return print_role(second_qm);
			    }
			    else
				return print_role_or_role_and_designation(second_qm,
					FIRST(designation),CDDR(designation));
			}
		    }
		}
	    }
	}
    }
}

static Object Qrole_and_designation_printer;  /* role-and-designation-printer */

static Object Qwide_string;        /* wide-string */

/* PRINT-ROLE-OR-ROLE-AND-DESIGNATION */
Object print_role_or_role_and_designation(role,designation_quantifier,domains)
    Object role, designation_quantifier, domains;
{
    Object role_name, role_and_designation_printer_qm, temp, schar_arg_2;
    Object schar_new_value;
    SI_Long thing;

    x_note_fn_call(150,1);
    role_name = role_name_of_role(simple_role_of_role(role));
    role_and_designation_printer_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name),
	    Qrole_and_designation_printer);
    if (role_and_designation_printer_qm)
	return FUNCALL_3(role_and_designation_printer_qm,role,
		FIRST(domains),SECOND(domains));
    else {
	twrite_symbol(1,designation_quantifier);
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)32L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)32L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	print_role(role);
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)32L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)32L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	return print_designation(FIRST(domains));
    }
}

static Object array_constant_4;    /* # */

/* PRINT-ROLE */
Object print_role(role)
    Object role;
{
    Object local_variable;

    x_note_fn_call(150,2);
    if (ATOM(role)) {
	twrite_symbol(1,role);
	return twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)3L));
    }
    else {
	local_variable = 
		get_explicitly_specified_local_name_of_role_if_any(role);
	role = simple_role_of_role(role);
	return print_role_1(role,local_variable);
    }
}

static Object string_constant_6;   /* " " */

static Object Qrole_server;        /* role-server */

static Object Qrole_server_printer;  /* role-server-printer */

/* PRINT-ROLE-1 */
Object print_role_1(role,local_variable_qm)
    Object role, local_variable_qm;
{
    Object role_1, role_car, gensymed_symbol, role_server_printer_qm;
    Object gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(150,3);
    if (ATOM(role)) {
	twrite_symbol(1,role);
	if (local_variable_qm) {
	    twrite(string_constant_6);
	    twrite(local_variable_qm);
	}
	return twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)3L));
    }
    else {
	role_1 = role;
	role_car = M_CAR(role_1);
	gensymed_symbol = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) 
		: role_car;
	role_server_printer_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qrole_server_printer);
	if (role_server_printer_qm) {
	    gensymed_symbol = role_server_printer_qm;
	    gensymed_symbol_1 = role;
	    gensymed_symbol_2 = local_variable_qm;
	    return VALUES_1(inline_funcall_2(gensymed_symbol,
		    gensymed_symbol_1,gensymed_symbol_2));
	}
	else
	    return twrite(role);
    }
}

static Object Qitem;               /* item */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object string_constant_7;   /* "The name ~ND, which occurred in ~NF, does not designate anything." */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object string_constant_8;   /* "Very strange designation ~ND found in ~NF.  It should not be ~
				    *                         possible to create an atomic, but non-symbolic designation!  ~
				    *                         Please call Gensym Software Support."
				    */

static Object string_constant_9;   /* "The expression \"~ND\" could not be evaluated." */

static Object string_constant_10;  /* "Two entities were designated by ~ND in ~NF, ~
				    *                                      the quantifier \"the\" requires that it designate only one."
				    */

static Object string_constant_11;  /* "There are no objects which match the designation ~ND in ~NF." */

static Object string_constant_12;  /* "Two entities were designated by ~ND ~
				    * ???             in ~NF, the quantifier \"the\" requires ~
				    *                                      that it designate only one."
				    */

static Object string_constant_13;  /* "There are no objects which match the designation ~ND ~
				    * ???          in ~NF, though there is an object matching ~ND."
				    */

static Object string_constant_14;  /* "A constant was specified as the ~a giving a value in ~NF." */

static Object string_constant_15;  /* "The item ~NF specified in ~NF as giving a value, is not a ~a." */

static Object string_constant_16;  /* "The designation ~ND in ~NF could not be evaluated." */

/* EVALUATE-DESIGNATION */
Object evaluate_designation(designation,alist)
    Object designation, alist;
{
    Object item_or_constant, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, role, alist_entry, role_value, role_expiration;
    Object too_many_objects_qm, domain_value, item, frame, symbol;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long designation_length, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp_1;
    Declare_special(7);
    Object result;

    x_note_fn_call(150,4);
    if (ATOM(designation)) {
	if (SYMBOLP(designation)) {
	    item_or_constant = assq_function(designation,alist);
	    item_or_constant = item_or_constant ? CDR(item_or_constant) : 
		    get_instance_with_name_if_any(Qitem,designation);
	    if ( !TRUEP(item_or_constant)) {
		if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
			!TRUEP(Debugging_reset)) {
		    if ( !TRUEP(Defer_notifications_qm))
			break_out_of_debug_messages();
		    snapshots_of_related_blocks = Nil;
		    note_blocks_in_tformat = 
			    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			    6);
		      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			      5);
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  write_warning_message_header(FIX((SI_Long)3L));
				  tformat(3,string_constant_7,designation,
					  Current_computation_frame);
				  temp = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			notify_user_1(temp);
			if (Snapshots_of_related_blocks) {
			    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			    Snapshots_of_related_blocks = Nil;
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		temp = Nil;
	    }
	    else if (SIMPLE_VECTOR_P(item_or_constant) && 
		    EQ(ISVREF(item_or_constant,(SI_Long)0L),
		    Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		temp = copy_temporary_constant(item_or_constant);
	    else if (serve_item_p(item_or_constant))
		temp = item_or_constant;
	    else
		temp = Nil;
	}
	else {
	    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		    !TRUEP(Debugging_reset)) {
		if ( !TRUEP(Defer_notifications_qm))
		    break_out_of_debug_messages();
		snapshots_of_related_blocks = Nil;
		note_blocks_in_tformat = 
			SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			6);
		  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			  5);
		    current_wide_string_list = Qdo_not_use;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			    4);
		      wide_string_bv16 = 
			      allocate_byte_vector_16(FIX((SI_Long)2048L + 
			      (SI_Long)3L));
		      bv16_length = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			      (SI_Long)0L);
		      current_wide_string = wide_string_bv16;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			      3);
			fill_pointer_for_current_wide_string = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				2);
			  length_1 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			  total_length_of_current_wide_string = 
				  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
			  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				  1);
			    current_twriting_output_type = Qwide_string;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				    0);
			      write_warning_message_header(FIX((SI_Long)1L));
			      tformat(3,string_constant_8,designation,
				      Current_computation_frame);
			      temp = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    notify_user_1(temp);
		    if (Snapshots_of_related_blocks) {
			reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			Snapshots_of_related_blocks = Nil;
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    temp = Nil;
	}
    }
    else if (EQ(M_CAR(designation),Qthe)) {
	designation_length = IFIX(length(designation));
	if ( !((SI_Long)-128L <= designation_length && designation_length 
		<= (SI_Long)127L)) {
	    if ((SI_Long)3L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)3L),string_constant_9,
			designation);
	    temp = Nil;
	}
	else
	    switch ((char)designation_length) {
	      case 2:
		role = SECOND(designation);
		alist_entry = Nil;
		if (SYMBOLP(role)) {
		    alist_entry = assq_function(role,alist);
		    temp_1 = TRUEP(alist_entry);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    temp = CDR(alist_entry);
		else {
		    result = serve_unique_value_of_role(2,
			    simple_role_of_role(role),Nil);
		    MVS_3(result,role_value,role_expiration,
			    too_many_objects_qm);
		    if (role_expiration)
			temp = role_value;
		    else if (too_many_objects_qm) {
			if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
				!TRUEP(Debugging_reset)) {
			    if ( !TRUEP(Defer_notifications_qm))
				break_out_of_debug_messages();
			    snapshots_of_related_blocks = Nil;
			    note_blocks_in_tformat = 
				    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				    6);
			      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				      5);
				current_wide_string_list = Qdo_not_use;
				PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  allocate_byte_vector_16(FIX((SI_Long)2048L 
					  + (SI_Long)3L));
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)2048L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)0L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  (SI_Long)2048L,(SI_Long)0L);
				  current_wide_string = wide_string_bv16;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
					  3);
				    fill_pointer_for_current_wide_string = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					    2);
				      length_1 = 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qwide_string;
					PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
						0);
					  write_warning_message_header(FIX((SI_Long)3L));
					  tformat(3,string_constant_10,
						  designation,
						  Current_computation_frame);
					  temp = 
						  copy_out_current_wide_string();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
				notify_user_1(temp);
				if (Snapshots_of_related_blocks) {
				    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
				    Snapshots_of_related_blocks = Nil;
				}
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
			temp = Nil;
		    }
		    else {
			if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
				!TRUEP(Debugging_reset)) {
			    if ( !TRUEP(Defer_notifications_qm))
				break_out_of_debug_messages();
			    snapshots_of_related_blocks = Nil;
			    note_blocks_in_tformat = 
				    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				    6);
			      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				      5);
				current_wide_string_list = Qdo_not_use;
				PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  allocate_byte_vector_16(FIX((SI_Long)2048L 
					  + (SI_Long)3L));
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)2048L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)0L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  (SI_Long)2048L,(SI_Long)0L);
				  current_wide_string = wide_string_bv16;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
					  3);
				    fill_pointer_for_current_wide_string = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					    2);
				      length_1 = 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qwide_string;
					PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
						0);
					  write_warning_message_header(FIX((SI_Long)3L));
					  tformat(3,string_constant_11,
						  designation,
						  Current_computation_frame);
					  temp = 
						  copy_out_current_wide_string();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
				notify_user_1(temp);
				if (Snapshots_of_related_blocks) {
				    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
				    Snapshots_of_related_blocks = Nil;
				}
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
			temp = Nil;
		    }
		}
		break;
	      case 3:
		domain_value = evaluate_designation(THIRD(designation),alist);
		if (domain_value) {
		    result = serve_unique_value_of_role(2,
			    simple_role_of_role(SECOND(designation)),
			    domain_value);
		    MVS_3(result,role_value,role_expiration,
			    too_many_objects_qm);
		    if (SIMPLE_VECTOR_P(domain_value) && 
			    EQ(ISVREF(domain_value,(SI_Long)0L),
			    Qg2_defstruct_structure_name_temporary_constant_g2_struct))
			reclaim_temporary_constant_1(domain_value);
		    if (role_expiration)
			temp = role_value;
		    else if (too_many_objects_qm) {
			if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
				!TRUEP(Debugging_reset)) {
			    if ( !TRUEP(Defer_notifications_qm))
				break_out_of_debug_messages();
			    snapshots_of_related_blocks = Nil;
			    note_blocks_in_tformat = 
				    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				    6);
			      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				      5);
				current_wide_string_list = Qdo_not_use;
				PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  allocate_byte_vector_16(FIX((SI_Long)2048L 
					  + (SI_Long)3L));
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)2048L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)0L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  (SI_Long)2048L,(SI_Long)0L);
				  current_wide_string = wide_string_bv16;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
					  3);
				    fill_pointer_for_current_wide_string = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					    2);
				      length_1 = 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qwide_string;
					PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
						0);
					  write_warning_message_header(FIX((SI_Long)3L));
					  tformat(3,string_constant_12,
						  designation,
						  Current_computation_frame);
					  temp = 
						  copy_out_current_wide_string();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
				notify_user_1(temp);
				if (Snapshots_of_related_blocks) {
				    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
				    Snapshots_of_related_blocks = Nil;
				}
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
			temp = Nil;
		    }
		    else {
			if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
				!TRUEP(Debugging_reset)) {
			    if ( !TRUEP(Defer_notifications_qm))
				break_out_of_debug_messages();
			    snapshots_of_related_blocks = Nil;
			    note_blocks_in_tformat = 
				    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				    6);
			      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				      5);
				current_wide_string_list = Qdo_not_use;
				PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  allocate_byte_vector_16(FIX((SI_Long)2048L 
					  + (SI_Long)3L));
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)2048L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)0L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  (SI_Long)2048L,(SI_Long)0L);
				  current_wide_string = wide_string_bv16;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
					  3);
				    fill_pointer_for_current_wide_string = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					    2);
				      length_1 = 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qwide_string;
					PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
						0);
					  write_warning_message_header(FIX((SI_Long)3L));
					  tformat(4,string_constant_13,
						  designation,
						  Current_computation_frame,
						  THIRD(designation));
					  temp = 
						  copy_out_current_wide_string();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
				notify_user_1(temp);
				if (Snapshots_of_related_blocks) {
				    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
				    Snapshots_of_related_blocks = Nil;
				}
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
			temp = Nil;
		    }
		}
		else
		    temp = Nil;
		break;
	      default:
		if ((SI_Long)3L <= IFIX(Warning_message_level))
		    give_warning_1(3,FIX((SI_Long)3L),string_constant_9,
			    designation);
		temp = Nil;
		break;
	    }
    }
    else if (EQ(CAR(designation),Qgiver_of_value)) {
	item = evaluate_designation(THIRD(designation),alist);
	if ( !TRUEP(item))
	    temp = Nil;
	else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(4,FIX((SI_Long)1L),string_constant_14,
			SECOND(designation),Current_computation_frame);
	    Suppress_warning_message_header_qm = Nil;
	    temp = Nil;
	}
	else {
	    frame = item;
	    symbol = SECOND(designation);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(5,FIX((SI_Long)1L),string_constant_15,
			    item,Current_computation_frame,
			    SECOND(designation));
		Suppress_warning_message_header_qm = Nil;
		temp = Nil;
	    }
	    else
		temp = item;
	}
    }
    else {
	if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	    if ( !TRUEP(Defer_notifications_qm))
		break_out_of_debug_messages();
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		    6);
	      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		      5);
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
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
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  write_warning_message_header(FIX((SI_Long)1L));
			  tformat(3,string_constant_16,designation,
				  Current_computation_frame);
			  temp = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notify_user_1(temp);
		if (Snapshots_of_related_blocks) {
		    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		    Snapshots_of_related_blocks = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qlong;               /* long */

static Object list_constant;       /* # */

static Object Qtext;               /* text */

static Object Qtruth_value;        /* truth-value */

/* DATUM-EQUAL */
Object datum_equal(value1,type1,value2,type2)
    Object value1, type1, value2, type2;
{
    Object temp;
    SI_Long fuzzy_equality;

    x_note_fn_call(150,5);
    if (EQ(type1,type2) || EQ(type1,Qnumber) && (EQ(type2,Qnumber) || 
	    EQ(type2,Qinteger) || EQ(type2,Qfloat) || EQ(type2,Qlong) || 
	    lookup_global_or_kb_specific_property_value(type2,
	    Numeric_data_type_gkbprop)) || EQ(type2,Qnumber) && (EQ(type1,
	    Qnumber) || EQ(type1,Qinteger) || EQ(type1,Qfloat) || EQ(type1,
	    Qlong) || lookup_global_or_kb_specific_property_value(type1,
	    Numeric_data_type_gkbprop)) || (EQ(type1,Qinteger) || 
	    memq_function(type1,list_constant)) && (EQ(type2,Qinteger) || 
	    memq_function(type2,list_constant))) {
	if (EQ(type1,Qnumber) || EQ(type1,Qfloat) || EQ(type1,Qinteger))
	    return VALUES_1(NUM_EQ(value1,value2) ? T : Nil);
	else if (EQ(type1,Qtext))
	    return string_equalw(value1,value2);
	else if (EQ(type1,Qtruth_value)) {
	    temp = FIXNUM_MINUS(value1,value2);
	    fuzzy_equality = (SI_Long)1000L - IFIX(FIXNUM_ABS(temp));
	    return VALUES_1(fuzzy_equality >= 
		    IFIX(ISVREF(Inference_engine_parameters,(SI_Long)26L)) 
		    ? T : Nil);
	}
	else
	    return VALUES_1(EQL(value1,value2) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Built_in_functions = UNBOUND;

/* ADD-BUILT-IN-FUNCTIONS-TO-DIRECTORY */
Object add_built_in_functions_to_directory(category_symbol)
    Object category_symbol;
{
    Object function_name, ab_loop_list_;

    x_note_fn_call(150,6);
    function_name = Nil;
    ab_loop_list_ = Built_in_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    function_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_to_directory_of_names(function_name,category_symbol);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Argument_range_gkbprop = UNBOUND;

Object Built_in_function_argument_names_prop = UNBOUND;

static Object Qbuilt_in_function_argument_names;  /* built-in-function-argument-names */

/* GET-BUILT-IN-FUNCTION-ARGUMENT-NAMES */
Object get_built_in_function_argument_names(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(150,7);
    temp = SYMBOLP(symbol) ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qbuilt_in_function_argument_names) : Nil;
    return VALUES_1(temp);
}

Object Evaluator_form_writer_prop = UNBOUND;

static Object Qfuzzy_lt;           /* fuzzy-< */

static Object string_constant_17;  /* " < " */

static Object Qfuzzy_gt;           /* fuzzy-> */

static Object string_constant_18;  /* " > " */

static Object Qfuzzy_eq;           /* fuzzy-= */

static Object string_constant_19;  /* " = " */

static Object string_constant_20;  /* " /= " */

static Object string_constant_21;  /* " (+- " */

static Object string_constant_22;  /* ")" */

/* FUZZY-WRITER */
Object fuzzy_writer(form)
    Object form;
{
    Object temp;

    x_note_fn_call(150,8);
    write_expression(SECOND(form));
    if (EQ(CAR(form),Qfuzzy_lt))
	temp = string_constant_17;
    else if (EQ(CAR(form),Qfuzzy_gt))
	temp = string_constant_18;
    else if (EQ(CAR(form),Qfuzzy_eq))
	temp = string_constant_19;
    else
	temp = string_constant_20;
    twrite(temp);
    write_expression(THIRD(form));
    twrite(string_constant_21);
    write_expression(FOURTH(form));
    return twrite(string_constant_22);
}

static Object Qis_more_true_than;  /* is-more-true-than */

static Object string_constant_23;  /* " is more true than " */

static Object Qis_not_more_true_than;  /* is-not-more-true-than */

static Object string_constant_24;  /* " is not more true than " */

static Object Qis_less_true_than;  /* is-less-true-than */

static Object string_constant_25;  /* " is less true than " */

static Object Qis_not_less_true_than;  /* is-not-less-true-than */

static Object string_constant_26;  /* " is not less true than " */

static Object string_constant_27;  /* " ??? " */

/* FUZZY-LOGIC-COMPARITOR-STRING-NAME */
Object fuzzy_logic_comparitor_string_name(name)
    Object name;
{
    x_note_fn_call(150,9);
    if (EQ(name,Qis_more_true_than))
	return VALUES_1(string_constant_23);
    else if (EQ(name,Qis_not_more_true_than))
	return VALUES_1(string_constant_24);
    else if (EQ(name,Qis_less_true_than))
	return VALUES_1(string_constant_25);
    else if (EQ(name,Qis_not_less_true_than))
	return VALUES_1(string_constant_26);
    else
	return VALUES_1(string_constant_27);
}

/* FUZZY-LOGIC-COMPARITOR-WRITER */
Object fuzzy_logic_comparitor_writer(expression)
    Object expression;
{
    x_note_fn_call(150,10);
    write_expression(SECOND(expression));
    twrite_general_string(fuzzy_logic_comparitor_string_name(CAR(expression)));
    return write_expression(THIRD(expression));
}

static Object Qvalue_of;           /* value-of */

static Object string_constant_28;  /* "the value of " */

static Object string_constant_29;  /* " is false" */

static Object Qcurrent_value_of;   /* current-value-of */

static Object string_constant_30;  /* "the current value of " */

/* FALSE-WRITER */
Object false_writer(exp_1)
    Object exp_1;
{
    Object negated_exp, keyword;

    x_note_fn_call(150,11);
    negated_exp = SECOND(exp_1);
    keyword = CONSP(negated_exp) ? CAR(negated_exp) : Nil;
    if (EQ(keyword,Qvalue_of)) {
	twrite(string_constant_28);
	write_expression(SECOND(negated_exp));
	return twrite(string_constant_29);
    }
    else if (EQ(keyword,Qcurrent_value_of)) {
	twrite(string_constant_30);
	write_expression(SECOND(negated_exp));
	return twrite(string_constant_29);
    }
    else {
	write_expression(SECOND(exp_1));
	return twrite(string_constant_29);
    }
}

static Object string_constant_31;  /* "the symbol ~(~a~)" */

/* QUOTE-EXPRESSION-WRITER */
Object quote_expression_writer(form)
    Object form;
{
    x_note_fn_call(150,12);
    return tformat(2,string_constant_31,SECOND(form));
}

static Object string_constant_32;  /* "(if " */

static Object string_constant_33;  /* " then " */

static Object string_constant_34;  /* " else " */

/* IF-EXPRESSION-WRITER */
Object if_expression_writer(form)
    Object form;
{
    x_note_fn_call(150,13);
    twrite(string_constant_32);
    write_expression(SECOND(form));
    twrite(string_constant_33);
    write_expression(THIRD(form));
    twrite(string_constant_34);
    write_expression(FOURTH(form));
    return twrite(string_constant_22);
}

static Object Qinterpolated_value;  /* interpolated-value */

static Object string_constant_35;  /* "the interpolated value " */

static Object Qhistoric_value;     /* historic-value */

static Object Qvalue_of_previous_datapoint;  /* value-of-previous-datapoint */

static Object string_constant_36;  /* "the value " */

static Object Qcollection_time_of_previous_datapoint;  /* collection-time-of-previous-datapoint */

static Object string_constant_37;  /* "the collection time " */

static Object Qmaximum_value;      /* maximum-value */

static Object string_constant_38;  /* "the maximum value" */

static Object Qminimum_value;      /* minimum-value */

static Object string_constant_39;  /* "the minimum value " */

static Object Qaverage_value;      /* average-value */

static Object string_constant_40;  /* "the average value " */

static Object Qsum_of_values;      /* sum-of-values */

static Object string_constant_41;  /* "the sum of the values " */

static Object Qstandard_deviation;  /* standard-deviation */

static Object string_constant_42;  /* "the standard deviation " */

static Object Qintegral;           /* integral */

static Object string_constant_43;  /* "the integral " */

static Object Qrate_of_change;     /* rate-of-change */

static Object string_constant_44;  /* "the rate of change " */

static Object string_constant_45;  /* "the unknown function " */

static Object list_constant_1;     /* # */

static Object string_constant_46;  /* "in " */

static Object string_constant_47;  /* " of " */

static Object string_constant_48;  /* "per " */

static Object string_constant_49;  /* "of " */

static Object list_constant_2;     /* # */

static Object string_constant_50;  /* " as of " */

static Object string_constant_51;  /* " datapoints ago" */

static Object Qtrue;               /* true */

static Object string_constant_52;  /* " during the " */

static Object string_constant_53;  /* " ending with the collection time" */

static Object string_constant_54;  /* " between " */

static Object string_constant_55;  /* " ago and " */

static Object string_constant_56;  /* " ago" */

static Object string_constant_57;  /* " during the last " */

/* HISTORIC-FUNCTION-WRITER */
Object historic_function_writer(form)
    Object form;
{
    Object name, prefix, designation, interval_1, interval_2, time_unit, temp;

    x_note_fn_call(150,14);
    name = FIRST(form);
    if (EQ(name,Qinterpolated_value))
	prefix = string_constant_35;
    else if (EQ(name,Qhistoric_value) || EQ(name,Qvalue_of_previous_datapoint))
	prefix = string_constant_36;
    else if (EQ(name,Qcollection_time_of_previous_datapoint))
	prefix = string_constant_37;
    else if (EQ(name,Qmaximum_value))
	prefix = string_constant_38;
    else if (EQ(name,Qminimum_value))
	prefix = string_constant_39;
    else if (EQ(name,Qaverage_value))
	prefix = string_constant_40;
    else if (EQ(name,Qsum_of_values))
	prefix = string_constant_41;
    else if (EQ(name,Qstandard_deviation))
	prefix = string_constant_42;
    else if (EQ(name,Qintegral))
	prefix = string_constant_43;
    else if (EQ(name,Qrate_of_change))
	prefix = string_constant_44;
    else
	prefix = string_constant_45;
    designation = SECOND(form);
    interval_1 = Nil;
    interval_2 = Nil;
    time_unit = Nil;
    if (memq_function(name,list_constant_1)) {
	temp = THIRD(form);
	time_unit = SECOND(temp);
	interval_1 = FOURTH(form);
	interval_2 = FIFTH(form);
    }
    else {
	interval_1 = THIRD(form);
	interval_2 = FOURTH(form);
    }
    twrite(prefix);
    if (EQ(name,Qintegral)) {
	twrite(string_constant_46);
	twrite_symbol(1,time_unit);
	twrite(string_constant_47);
    }
    else if (EQ(name,Qrate_of_change)) {
	twrite(string_constant_48);
	twrite_symbol(1,time_unit);
	twrite(string_constant_47);
    }
    else
	twrite(string_constant_49);
    print_designation(designation);
    if (memq_function(name,list_constant_2)) {
	twrite(string_constant_50);
	write_expression(interval_1);
	return twrite(string_constant_51);
    }
    else if (interval_2) {
	if (EQ(interval_2,Qtrue)) {
	    twrite(string_constant_52);
	    write_expression(interval_1);
	    return twrite(string_constant_53);
	}
	else {
	    twrite(string_constant_54);
	    write_expression(interval_1);
	    twrite(string_constant_55);
	    write_expression(interval_2);
	    return twrite(string_constant_56);
	}
    }
    else if (EQ(name,Qhistoric_value)) {
	twrite(string_constant_50);
	write_expression(interval_1);
	return twrite(string_constant_56);
    }
    else {
	twrite(string_constant_57);
	return write_expression(interval_1);
    }
}

static Object Qhas_a_value;        /* has-a-value */

static Object Qhas_current_value;  /* has-current-value */

static Object string_constant_58;  /* " has a value" */

static Object Qhas_no_value;       /* has-no-value */

static Object string_constant_59;  /* " has no value" */

static Object Qhas_a_current_value;  /* has-a-current-value */

static Object string_constant_60;  /* " has a current value" */

static Object Qhas_no_current_value;  /* has-no-current-value */

static Object string_constant_61;  /* " has-no-current-value" */

static Object Qreceives_a_value;   /* receives-a-value */

static Object string_constant_62;  /* " receives a value" */

static Object Qfails_to_receive_a_value;  /* fails-to-receive-a-value */

static Object string_constant_63;  /* " fails to receive a value" */

static Object Qis_moved;           /* is-moved */

static Object string_constant_64;  /* " is moved" */

static Object Qis_moved_by_the_user;  /* is-moved-by-the-user */

static Object string_constant_65;  /* " is moved by the user" */

static Object Qis_moved_by_g2;     /* is-moved-by-g2 */

static Object string_constant_66;  /* " is moved by G2" */

static Object Qis_resized_by_the_user;  /* is-resized-by-the-user */

static Object string_constant_67;  /* " is resized by the user" */

static Object Qhas_a_name;         /* has-a-name */

static Object string_constant_68;  /* " has a name" */

static Object Qhas_no_name;        /* has-no-name */

static Object string_constant_69;  /* " has no name" */

/* POSTFIX-WRITER */
Object postfix_writer(exp_1)
    Object exp_1;
{
    Object temp;

    x_note_fn_call(150,15);
    write_expression(SECOND(exp_1));
    temp = FIRST(exp_1);
    if (EQ(temp,Qhas_a_value) || EQ(temp,Qhas_current_value))
	temp = string_constant_58;
    else if (EQ(temp,Qhas_no_value))
	temp = string_constant_59;
    else if (EQ(temp,Qhas_a_current_value))
	temp = string_constant_60;
    else if (EQ(temp,Qhas_no_current_value))
	temp = string_constant_61;
    else if (EQ(temp,Qreceives_a_value))
	temp = string_constant_62;
    else if (EQ(temp,Qfails_to_receive_a_value))
	temp = string_constant_63;
    else if (EQ(temp,Qis_moved))
	temp = string_constant_64;
    else if (EQ(temp,Qis_moved_by_the_user))
	temp = string_constant_65;
    else if (EQ(temp,Qis_moved_by_g2))
	temp = string_constant_66;
    else if (EQ(temp,Qis_resized_by_the_user))
	temp = string_constant_67;
    else if (EQ(temp,Qhas_a_name))
	temp = string_constant_68;
    else if (EQ(temp,Qhas_no_name))
	temp = string_constant_69;
    else
	temp = Qnil;
    return twrite(temp);
}

static Object Qexpiration_time_of;  /* expiration-time-of */

static Object string_constant_70;  /* "the expiration time of " */

static Object Qcollection_time_of;  /* collection-time-of */

static Object string_constant_71;  /* "the collection time of " */

/* PREFIX-WRITER */
Object prefix_writer(exp_1)
    Object exp_1;
{
    Object temp;

    x_note_fn_call(150,16);
    temp = FIRST(exp_1);
    if (EQ(temp,Qvalue_of))
	temp = string_constant_28;
    else if (EQ(temp,Qcurrent_value_of))
	temp = string_constant_30;
    else if (EQ(temp,Qexpiration_time_of))
	temp = string_constant_70;
    else if (EQ(temp,Qcollection_time_of))
	temp = string_constant_71;
    else
	temp = Qnil;
    twrite(temp);
    return write_expression(SECOND(exp_1));
}

static Object Qis;                 /* is */

static Object string_constant_72;  /* " is " */

static Object string_constant_73;  /* " is not " */

/* WRITE-IS */
Object write_is(form)
    Object form;
{
    Object temp;

    x_note_fn_call(150,17);
    write_expression(SECOND(form));
    twrite_general_string(EQ(FIRST(form),Qis) ? string_constant_72 : 
	    string_constant_73);
    temp = THIRD(form);
    return tprin(SECOND(temp),Nil);
}

static Object array_constant_5;    /* # */

/* ATTRIBUTE-NAME-FUNCTION-WRITER */
Object attribute_name_function_writer(expression)
    Object expression;
{
    x_note_fn_call(150,18);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)22L));
    return print_designation(SECOND(expression));
}

static Object array_constant_6;    /* # */

/* WRITE-THE-CURRENT-TIME */
Object write_the_current_time(expression)
    Object expression;
{
    Object temp;

    x_note_fn_call(150,19);
    temp = twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)16L));
    return VALUES_1(temp);
}

static Object array_constant_7;    /* # */

/* WRITE-THE-CURRENT-REAL-TIME */
Object write_the_current_real_time(expression)
    Object expression;
{
    Object temp;

    x_note_fn_call(150,20);
    temp = twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)21L));
    return VALUES_1(temp);
}

static Object array_constant_8;    /* # */

/* WRITE-THE-CURRENT-SUBSECOND-TIME */
Object write_the_current_subsecond_time(expression)
    Object expression;
{
    Object temp;

    x_note_fn_call(150,21);
    temp = twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)26L));
    return VALUES_1(temp);
}

static Object Qbecomes;            /* becomes */

static Object string_constant_74;  /* " becomes " */

static Object string_constant_75;  /* " ceases to be " */

/* WRITE-RELATION-EVENT-LITERAL */
Object write_relation_event_literal(exp_1)
    Object exp_1;
{
    x_note_fn_call(150,22);
    print_designation(THIRD(exp_1));
    twrite(EQ(FIRST(exp_1),Qbecomes) ? string_constant_74 : 
	    string_constant_75);
    twrite_symbol(1,SECOND(exp_1));
    twrite(string_constant_6);
    return print_designation(FOURTH(exp_1));
}

static Object string_constant_76;  /* " has a " */

static Object string_constant_77;  /* " event" */

/* WRITE-GENERIC-EVENT-LITERAL */
Object write_generic_event_literal(exp_1)
    Object exp_1;
{
    Object temp;

    x_note_fn_call(150,23);
    print_designation(SECOND(exp_1));
    twrite(string_constant_76);
    temp = THIRD(exp_1);
    return twrite_symbol(2,temp,twrite(string_constant_77));
}

static Object array_constant_9;    /* # */

/* WRITE-NUPEC-SYNCHRONIZATION-OCCURS */
Object write_nupec_synchronization_occurs(expression)
    Object expression;
{
    x_note_fn_call(150,24);
    return twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)28L));
}

static Object Qdistance_between;   /* distance-between */

static Object string_constant_78;  /* "the distance between " */

static Object string_constant_79;  /* " and " */

/* WRITE-IN-BINARY-ROLE-STYLE */
Object write_in_binary_role_style(exp_1)
    Object exp_1;
{
    Object temp;

    x_note_fn_call(150,25);
    temp = CAR(exp_1);
    twrite(EQ(temp,Qdistance_between) ? string_constant_78 : Nil);
    print_designation(SECOND(exp_1));
    twrite(string_constant_79);
    return print_designation(THIRD(exp_1));
}

static Object array_constant_10;   /* # */

static Object string_constant_80;  /* " and the nearest ~(~a~)" */

/* WRITE-DISTANCE-BETWEEN-AND-THE-NEAREST */
Object write_distance_between_and_the_nearest(expression)
    Object expression;
{
    Object temp;

    x_note_fn_call(150,26);
    twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)21L));
    print_designation(SECOND(expression));
    temp = THIRD(expression);
    return tformat(2,string_constant_80,SECOND(temp));
}

static Object Qsame_as;            /* same-as */

static Object string_constant_81;  /* " is the same object as " */

static Object string_constant_82;  /* " is not the same object as " */

/* WRITE-SAME-AS */
Object write_same_as(exp_1)
    Object exp_1;
{
    x_note_fn_call(150,27);
    print_designation(SECOND(exp_1));
    twrite(EQ(FIRST(exp_1),Qsame_as) ? string_constant_81 : 
	    string_constant_82);
    return print_designation(THIRD(exp_1));
}

static Object Qis_of_class;        /* is-of-class */

static Object string_constant_83;  /* "an instance of the class named by (" */

/* WRITE-IS-A */
Object write_is_a(exp_1)
    Object exp_1;
{
    Object operator_1, designation, class_exp_or_quoted_name;

    x_note_fn_call(150,28);
    operator_1 = FIRST(exp_1);
    designation = SECOND(exp_1);
    class_exp_or_quoted_name = THIRD(exp_1);
    print_designation(designation);
    if (EQ(operator_1,Qis_of_class))
	twrite(string_constant_72);
    else
	twrite(string_constant_73);
    if (CONSP(class_exp_or_quoted_name) && 
	    EQ(CAR(class_exp_or_quoted_name),Qquote))
	return write_symbol_with_a_or_an(2,
		SECOND(class_exp_or_quoted_name),Nil);
    else {
	twrite(string_constant_83);
	write_expression(class_exp_or_quoted_name);
	return twrite(string_constant_22);
    }
}

static Object Qis_active;          /* is-active */

static Object string_constant_84;  /* " has been activated" */

static Object string_constant_85;  /* " has not been activated" */

/* WRITE-IS-ACTIVE */
Object write_is_active(exp_1)
    Object exp_1;
{
    x_note_fn_call(150,29);
    print_designation(SECOND(exp_1));
    return twrite(EQ(CAR(exp_1),Qis_active) ? string_constant_84 : 
	    string_constant_85);
}

static Object string_constant_86;  /* "the " */

/* WRITE-AS-IF-ROLE */
Object write_as_if_role(exp_1)
    Object exp_1;
{
    x_note_fn_call(150,30);
    twrite(string_constant_86);
    twrite_symbol(1,FIRST(exp_1));
    twrite(string_constant_47);
    return print_designation(SECOND(exp_1));
}

static Object Qis_related;         /* is-related */

static Object Qis_not_related;     /* is-not-related */

/* RELATION-WRITER */
Object relation_writer(exp_1)
    Object exp_1;
{
    Object temp, relation;

    x_note_fn_call(150,31);
    print_designation(THIRD(exp_1));
    temp = FIRST(exp_1);
    if (EQ(temp,Qis_related))
	temp = string_constant_72;
    else if (EQ(temp,Qis_not_related))
	temp = string_constant_73;
    else
	temp = Qnil;
    twrite_general_string(temp);
    relation = SECOND(exp_1);
    if (SYMBOLP(relation))
	twrite_symbol(1,relation);
    else if (CONSP(relation) && EQ(M_CAR(relation),Qquote))
	twrite_symbol(1,SECOND(relation));
    else
	write_expression(relation);
    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)1L));
    return print_designation(FOURTH(exp_1));
}

static Object Qdq;                 /* \" */

static Object Qobt;                /* [ */

static Object Qcbt;                /* ] */

/* WRITE-FORMAT-FORM */
Object write_format_form(form)
    Object form;
{
    Object listed_component, component;

    x_note_fn_call(150,32);
    listed_component = CDDR(form);
    component = Nil;
    twrite(Qdq);
    twrite(SECOND(form));
    twrite(Qobt);
  next_loop:
    if ( !TRUEP(listed_component))
	goto end_loop;
    component = CAR(listed_component);
    if ( !TRUEP(CDR(listed_component)))
	goto end_loop;
    if (text_string_p(component)) {
	twrite(Qcbt);
	twrite(component);
	twrite(Qobt);
    }
    else
	write_expression(component);
    listed_component = M_CDR(listed_component);
    goto next_loop;
  end_loop:
    twrite(Qcbt);
    twrite(component);
    twrite(Qdq);
    return VALUES_1(Qnil);
}

static Object string_constant_87;  /* "the number of elements in " */

/* WRITE-G2-LIST-OR-SEQUENCE-LENGTH */
Object write_g2_list_or_sequence_length(exp_1)
    Object exp_1;
{
    x_note_fn_call(150,33);
    twrite(string_constant_87);
    return print_designation(SECOND(exp_1));
}

static Object string_constant_88;  /* "the network interface for " */

/* WRITE-NETWORK-INTERFACE-FOR */
Object write_network_interface_for(exp_1)
    Object exp_1;
{
    x_note_fn_call(150,34);
    twrite(string_constant_88);
    return print_designation(SECOND(exp_1));
}

static Object Qop;                 /* \( */

static Object string_constant_89;  /* " where " */

static Object string_constant_90;  /* "; " */

static Object Qcp;                 /* \) */

/* WRITE-LET */
Object write_let(form)
    Object form;
{
    Object var, binding, rest_1, ab_loop_list_, temp;

    x_note_fn_call(150,35);
    twrite(Qop);
    write_expression(THIRD(form));
    twrite(string_constant_89);
    var = Nil;
    binding = Nil;
    rest_1 = Nil;
    ab_loop_list_ = SECOND(form);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    temp = CAR(ab_loop_list_);
    var = CAR(temp);
    temp = CAR(ab_loop_list_);
    temp = CDR(temp);
    binding = CAR(temp);
    rest_1 = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    twrite_symbol(1,var);
    twrite(string_constant_19);
    write_expression(binding);
    if (rest_1)
	twrite(string_constant_90);
    goto next_loop;
  end_loop:;
    return twrite(Qcp);
}

static Object string_constant_91;  /* "the ~(~a~) over each " */

static Object Qaggregated_average;  /* aggregated-average */

static Object Qaverage;            /* average */

static Object Qnone;               /* none */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

/* WRITE-AGGREGATOR */
Object write_aggregator(form)
    Object form;
{
    Object scope, aggregated_expression, role, name_from_role;
    Object atomic_name_for_role, binding, domain;

    x_note_fn_call(150,36);
    scope = SECOND(form);
    aggregated_expression = THIRD(form);
    role = FIRST(scope);
    name_from_role = get_name_provided_by_role(role);
    atomic_name_for_role = 
	    atomic_naming_element_of_simple_role(simple_role_of_role(role));
    binding = SECOND(scope);
    domain = THIRD(scope);
    tformat(2,string_constant_91,EQ(CAR(form),Qaggregated_average) ? 
	    Qaverage : CAR(form));
    if (domain) {
	print_role_1(role, !EQ(name_from_role,binding) ? binding : Nil);
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)1L));
	print_designation(domain);
    }
    else {
	if (SYMBOLP(atomic_name_for_role))
	    twrite_symbol(1,atomic_name_for_role);
	else if (CONSP(atomic_name_for_role))
	    twrite_symbol(1,CAR(atomic_name_for_role));
	else
	    twrite_symbol(1,Qnone);
	if ( !EQ(role,binding)) {
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)1L));
	    twrite(binding);
	}
    }
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)5L));
    write_expression(aggregated_expression);
    return twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)1L));
}

static Object Qthere_exists_literal;  /* there-exists-literal */

static Object string_constant_92;  /* "there exists " */

static Object Qfor_every_literal;  /* for-every-literal */

static Object string_constant_93;  /* "for every " */

static Object string_constant_94;  /* " such that (" */

static Object string_constant_95;  /* " (" */

/* WRITE-NEW-QUANTIFIED-FORM */
Object write_new_quantified_form(form)
    Object form;
{
    Object scope, quantified_expression, role, name_from_role, binding, domain;
    Object atomic_name_for_role, temp;
    char temp_1;

    x_note_fn_call(150,37);
    scope = SECOND(form);
    quantified_expression = THIRD(form);
    role = Nil;
    name_from_role = Nil;
    binding = Nil;
    domain = Nil;
    atomic_name_for_role = Nil;
    if ( !TRUEP(CDR(scope))) {
	if (simple_role_p(CAR(scope))) {
	    role = CAR(scope);
	    binding = get_name_provided_by_role(role);
	    domain = Nil;
	}
	else {
	    role = CAAR(scope);
	    binding = CDAR(scope);
	    domain = Nil;
	}
    }
    else if ( !TRUEP(simple_role_p(CAR(scope)))) {
	role = CAAR(scope);
	binding = CDAR(scope);
	domain = SECOND(scope);
    }
    else {
	if ( !TRUEP(CDDR(scope))) {
	    temp = SECOND(scope);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = SECOND(scope);
	    temp_1 =  !EQ(CAR(temp),Qvar_spot);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    role = FIRST(scope);
	    binding = get_name_provided_by_role(FIRST(scope));
	    domain = SECOND(scope);
	}
	else {
	    role = FIRST(scope);
	    binding = SECOND(scope);
	    domain = THIRD(scope);
	}
    }
    name_from_role = get_name_provided_by_role(role);
    atomic_name_for_role = 
	    atomic_naming_element_of_simple_role(simple_role_of_role(role));
    temp = CAR(form);
    if (EQ(temp,Qthere_exists_literal)) {
	twrite(string_constant_92);
	twrite(supply_a_or_an(name_from_role));
    }
    else if (EQ(temp,Qfor_every_literal))
	twrite(string_constant_93);
    if (domain) {
	print_role_1(role, !EQ(name_from_role,binding) ? binding : Nil);
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)1L));
	print_designation(domain);
    }
    else {
	twrite_symbol(1,atomic_name_for_role);
	if ( !EQ(role,binding)) {
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)1L));
	    twrite(binding);
	}
    }
    temp = CAR(form);
    if (EQ(temp,Qthere_exists_literal))
	temp = string_constant_94;
    else if (EQ(temp,Qfor_every_literal))
	temp = string_constant_95;
    else
	temp = Qnil;
    twrite(temp);
    write_expression(quantified_expression);
    return twrite(string_constant_22);
}

static Object string_constant_96;  /* "A number was computed that is too big to store in ~
				    *                       floating point format.  It was ~A, and ~D is being ~
				    *                       stored instead."
				    */

static Object string_constant_97;  /* "negative" */

static Object string_constant_98;  /* "positive" */

static Object string_constant_99;  /* "The preceding occurred within ~NF." */

/* WARN-OF-BIG-BIGNUM */
Object warn_of_big_bignum(negative_qm)
    Object negative_qm;
{
    x_note_fn_call(150,38);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(4,FIX((SI_Long)1L),string_constant_96,negative_qm ? 
		string_constant_97 : string_constant_98,negative_qm ? 
		FIX((SI_Long)-1L) : FIX((SI_Long)1L));
    Suppress_warning_message_header_qm = Nil;
    if (BOUNDP(Qcurrent_computation_frame) && Current_computation_frame) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_99,
		    Current_computation_frame);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
    else
	return VALUES_1(Nil);
}

void eval_INIT()
{
    Object function_name, ab_loop_list_;
    Object AB_package, Qwrite_new_quantified_form, Qwrite_aggregator;
    Object list_constant_3, Qwrite_let, Qwrite_network_interface_for;
    Object Qwrite_g2_list_or_sequence_length, Qwrite_format_form;
    Object Qrelation_writer, Qwrite_as_if_role, Qwrite_is_active, Qwrite_is_a;
    Object Qwrite_same_as, Qwrite_distance_between_and_the_nearest;
    Object Qwrite_in_binary_role_style, Qwrite_nupec_synchronization_occurs;
    Object Qwrite_generic_event_literal, Qwrite_relation_event_literal;
    Object Qwrite_the_current_subsecond_time, Qwrite_the_current_real_time;
    Object Qwrite_the_current_time, Qattribute_name_function_writer, Qwrite_is;
    Object Qprefix_writer, Qpostfix_writer, Qhistoric_function_writer;
    Object Qif_expression_writer, Qquote_expression_writer, Qfalse_writer;
    Object Qfuzzy_logic_comparitor_writer, Qfuzzy_writer;
    Object Qevaluator_form_writer, Qminimum, Qmaximum, Qproduct, Qsum, Qab_let;
    Object Qnetwork_interface_for, Qg2_list_or_sequence_length, Qformat_form;
    Object Qname, Qis_not_active, Qis_not_of_class, Qnot_same_as;
    Object Qdistance_between_and_the_nearest, Qnupec_synchronization_occurs;
    Object Qhas_generic_event, Qceases_to_be_related, Qbecomes_related;
    Object Qcurrent_subsecond_time, Qcurrent_time, Qattribute_name, Qis_not;
    Object Qsimulated_value_of, Qnumber_of_datapoints, Qif_expression, Qfalse;
    Object Qfuzzy_not_eq, list_constant_81, Qnative_float_array_get;
    Object list_constant_84, Qnative_float_array_set, list_constant_83;
    Object Qnative_float_array_free, list_constant_82;
    Object Qnative_float_array_alloc, Qnative_array_alloc, Qnative_array_get;
    Object list_constant_79, Qnative_array_set, list_constant_39, Qindex;
    Object Qhandle, Qsize, list_constant_80, Qvalue, list_constant_78;
    Object Qdiv_long, Qlong_2, Qlong_1, list_constant_77, Qis_nan;
    Object list_constant_76, Qevaluated_structure, list_constant_72;
    Object Qitem_or_value_cbt, Qobt_obt_symbol_expression, list_constant_75;
    Object Qab_structure, QOBT_OBT_ATTRIBUTE_NAME_COL_SP_ITEM_OR_VALUE_CBT;
    Object list_constant_74, Qobt_sequence, list_constant_73;
    Object Qobt_item_or_value, Qdot_dot_dot_cbt, list_constant_71;
    Object Qcall_function, Qobt_argument, Qfunction_definition_expression;
    Object list_constant_65, list_constant_70, Qitems_are_connected_at_ports;
    Object Qportname_2, Qportname_1, Qitem_2, Qitem_1, list_constant_69;
    Object Qitems_are_connected_with_direction, Qitem_1_direction;
    Object list_constant_68, Qitems_are_connected, list_constant_67;
    Object Qconnection_style, Qconnection, list_constant_66, Qconnection_side;
    Object Qconnection_position, Qconnection_portname, Qconnection_direction;
    Object Qdot_dot_dot, Qquantity_2, Qquantity_1, list_constant_63;
    Object Qbitwise_set, Qbitwise_test, Qbitwise_left_shift;
    Object Qbitwise_right_shift, Qbitwise_xor, list_constant_64, Qbitwise_not;
    Object Qbitwise_or, Qbitwise_and, Qinteger_2, Qinteger_1;
    Object Qformat_numeric_text, list_constant_62, Qddd_dot_dddd_format_text;
    Object Qnumber_as_text, Qfind_java_class, list_constant_61;
    Object Qtransform_text_for_g2_4_dot_0_comparison;
    Object Qtransform_text_for_unicode_comparison, Qconsider_case;
    Object Qtext_to_transform, list_constant_60, Qexport_text;
    Object list_constant_59, Qunicode_text, Qconversion_style;
    Object list_constant_58, Qimport_text, Qexternal_text, list_constant_57;
    Object Qcompare_text, Qtext_2, Qtext_1, list_constant_56;
    Object Qreadable_symbol_text, Qreadable_text, Qprinted_text;
    Object Qreadable_text_for_value, list_constant_55;
    Object Qis_readable_digit_in_radix, Qradix, Qcharacter_code;
    Object list_constant_54, Qis_readable_digit, Qis_digit, Qto_lowercase;
    Object Qto_titlecase, Qto_uppercase, Qis_lowercase, Qis_titlecase;
    Object Qis_uppercase, list_constant_20, Qtext_to_character_codes;
    Object list_constant_53, Qcharacter_codes_to_text, Qcharacter_codes;
    Object Qattribute_descriptions_of_class_as_structure;
    Object Qattribute_descriptions_of_item_as_structure, list_constant_52;
    Object Qremove_evaluated_attribute, Qsymbol_expression, list_constant_51;
    Object Qremove_attribute, list_constant_50, Qchange_evaluated_attribute;
    Object list_constant_49, Qitem_or_value, list_constant_48;
    Object Qchange_attribute, list_constant_47, Qportion, Qnumber_to_copy;
    Object Qstart_index, list_constant_46, Qchange_element;
    Object Qinsert_after_element, Qinsert_before_element, Qnew_element;
    Object list_constant_45, Qinsert_after, Qinsert_before, Qexisting_element;
    Object list_constant_44, Qinsert_at_end, Qinsert_at_beginning;
    Object Qitem_or_value_to_add, list_constant_43, Qindex_to_remove;
    Object list_constant_42, Qminute, Qhour, Qdate, Qmonth, Qyear;
    Object list_constant_41, Qday_of_the_week, Qday_of_the_month;
    Object list_constant_40, Qtext_to_symbol, Qtext_begins_with_quantity;
    Object Qquantity, list_constant_38, Qarctan, list_constant_37;
    Object list_constant_36, Qx, Qy, list_constant_15, list_constant_35;
    Object Qlexeme, Qtoken, Qsource_text, list_constant_34, Qget_next_token;
    Object list_constant_33, Qtokenizer, Qstart_position, list_constant_26;
    Object list_constant_32, Qfind_and_replace_pattern, list_constant_31;
    Object list_constant_30, Qflags, Qend_position, Qtext_to_substitute;
    Object Qsearch_pattern, list_constant_29, list_constant_28;
    Object Qfind_next_substring_matching_pattern, Qfind_next_pattern;
    Object list_constant_27, list_constant_25, Qget_from_text;
    Object list_constant_24, Qend_index, list_constant_23, Qreplace_in_text;
    Object list_constant_22, Qomit_from_text, Qend, Qbegin, list_constant_21;
    Object Qinsert_in_text, Qtext_to_insert, Qcapitalize_words;
    Object Qlower_case_text, Qupper_case_text, list_constant_19;
    Object Qposition_of_text, Qlength_of_text, Qis_contained_in_text;
    Object Qcontaining_text, list_constant_18, list_constant_17;
    Object list_constant_16, Qlower_bound_quantity, Qupper_bound_quantity;
    Object list_constant_14, Qremainder, Qquotient, Qdivisor_quantity;
    Object Qdividend_quantity, list_constant_13, Qpower_quantity;
    Object Qbase_quantity, list_constant_12, list_constant_11, Qrgb_symbol;
    Object Qblue_value_integer, Qgreen_value_integer, Qred_value_integer;
    Object list_constant_10, Qgreat_circle_distance, Qradius_quantity;
    Object Qlongitude_2_quantity, Qlatitude_2_quantity, Qlongitude_1_quantity;
    Object Qlatitude_1_quantity, list_constant_9, list_constant_8, Qln;
    Object Qargument_range, list_constant_7, list_constant_6, list_constant_5;
    Object list_constant_4, Qvector_scalar_multiply, Qvector_multiply;
    Object Qvector_add, Qcount_datapoints_that_evaluate_true;
    Object Qkbf_g2nke_count_history_matching_op;
    Object Qcount_datapoints_that_evaluate_true_with_eventflag;
    Object Qkbf_g2nke_count_history_matching_op_and_eventflag;
    Object Qnative_integer_array_free, Qnative_integer_array_alloc;
    Object Qnative_integer_array_get, Qnative_integer_array_set, Qinterval;
    Object Qseconds, G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(150,39);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING("!!!");
    AB_package = STATIC_PACKAGE("AB");
    Qgiver_of_value = STATIC_SYMBOL("GIVER-OF-VALUE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    Qclass_qualified_method = STATIC_SYMBOL("CLASS-QUALIFIED-METHOD",
	    AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qthis_workspace = STATIC_SYMBOL("THIS-WORKSPACE",AB_package);
    string_constant_1 = STATIC_STRING("this workspace");
    Qthis_window = STATIC_SYMBOL("THIS-WINDOW",AB_package);
    string_constant_2 = STATIC_STRING("this window");
    Qthis_rule = STATIC_SYMBOL("THIS-RULE",AB_package);
    string_constant_3 = STATIC_STRING("this rule");
    Qthis_procedure = STATIC_SYMBOL("THIS-PROCEDURE",AB_package);
    string_constant_4 = STATIC_STRING("this procedure");
    Qthis_procedure_invocation = STATIC_SYMBOL("THIS-PROCEDURE-INVOCATION",
	    AB_package);
    string_constant_5 = STATIC_STRING("this procedure-invocation");
    Qrole_and_designation_printer = 
	    STATIC_SYMBOL("ROLE-AND-DESIGNATION-PRINTER",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    string_constant_6 = STATIC_STRING(" ");
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qrole_server_printer = STATIC_SYMBOL("ROLE-SERVER-PRINTER",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    string_constant_7 = 
	    STATIC_STRING("The name ~ND, which occurred in ~NF, does not designate anything.");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_8 = 
	    string_append2(STATIC_STRING("Very strange designation ~ND found in ~NF.  It should not be ~\n                        possible to create an atomic, but non-symbolic designation!  ~\n                        P"),
	    STATIC_STRING("lease call Gensym Software Support."));
    string_constant_9 = 
	    STATIC_STRING("The expression \"~ND\" could not be evaluated.");
    string_constant_10 = 
	    STATIC_STRING("Two entities were designated by ~ND in ~NF, ~\n                                     the quantifier \"the\" requires that it designate only one.");
    string_constant_11 = 
	    STATIC_STRING("There are no objects which match the designation ~ND in ~NF.");
    string_constant_12 = 
	    STATIC_STRING("Two entities were designated by ~ND ~\n\t\t\t             in ~NF, the quantifier \"the\" requires ~\n                                     that it designate only one.");
    string_constant_13 = 
	    STATIC_STRING("There are no objects which match the designation ~ND ~\n\t\t\t          in ~NF, though there is an object matching ~ND.");
    string_constant_14 = 
	    STATIC_STRING("A constant was specified as the ~a giving a value in ~NF.");
    string_constant_15 = 
	    STATIC_STRING("The item ~NF specified in ~NF as giving a value, is not a ~a.");
    string_constant_16 = 
	    STATIC_STRING("The designation ~ND in ~NF could not be evaluated.");
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qseconds,Qinterval);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qarctan = STATIC_SYMBOL("ARCTAN",AB_package);
    Qln = STATIC_SYMBOL("LN",AB_package);
    Qquotient = STATIC_SYMBOL("QUOTIENT",AB_package);
    Qremainder = STATIC_SYMBOL("REMAINDER",AB_package);
    Qgreat_circle_distance = STATIC_SYMBOL("GREAT-CIRCLE-DISTANCE",AB_package);
    Qrgb_symbol = STATIC_SYMBOL("RGB-SYMBOL",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qyear = STATIC_SYMBOL("YEAR",AB_package);
    Qmonth = STATIC_SYMBOL("MONTH",AB_package);
    Qday_of_the_month = STATIC_SYMBOL("DAY-OF-THE-MONTH",AB_package);
    Qday_of_the_week = STATIC_SYMBOL("DAY-OF-THE-WEEK",AB_package);
    Qaverage = STATIC_SYMBOL("AVERAGE",AB_package);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    Qtext_begins_with_quantity = STATIC_SYMBOL("TEXT-BEGINS-WITH-QUANTITY",
	    AB_package);
    Qis_contained_in_text = STATIC_SYMBOL("IS-CONTAINED-IN-TEXT",AB_package);
    Qlength_of_text = STATIC_SYMBOL("LENGTH-OF-TEXT",AB_package);
    Qposition_of_text = STATIC_SYMBOL("POSITION-OF-TEXT",AB_package);
    Qupper_case_text = STATIC_SYMBOL("UPPER-CASE-TEXT",AB_package);
    Qlower_case_text = STATIC_SYMBOL("LOWER-CASE-TEXT",AB_package);
    Qcapitalize_words = STATIC_SYMBOL("CAPITALIZE-WORDS",AB_package);
    Qinsert_in_text = STATIC_SYMBOL("INSERT-IN-TEXT",AB_package);
    Qomit_from_text = STATIC_SYMBOL("OMIT-FROM-TEXT",AB_package);
    Qget_from_text = STATIC_SYMBOL("GET-FROM-TEXT",AB_package);
    Qreplace_in_text = STATIC_SYMBOL("REPLACE-IN-TEXT",AB_package);
    Qfind_next_pattern = STATIC_SYMBOL("FIND-NEXT-PATTERN",AB_package);
    Qfind_next_substring_matching_pattern = 
	    STATIC_SYMBOL("FIND-NEXT-SUBSTRING-MATCHING-PATTERN",AB_package);
    Qfind_and_replace_pattern = STATIC_SYMBOL("FIND-AND-REPLACE-PATTERN",
	    AB_package);
    Qget_next_token = STATIC_SYMBOL("GET-NEXT-TOKEN",AB_package);
    Qlexeme = STATIC_SYMBOL("LEXEME",AB_package);
    SET_SYMBOL_FUNCTION(Qlexeme,STATIC_FUNCTION(lexeme,NIL,FALSE,2,2));
    Qcall_function = STATIC_SYMBOL("CALL-FUNCTION",AB_package);
    Qtext_to_symbol = STATIC_SYMBOL("TEXT-TO-SYMBOL",AB_package);
    Qconnection_direction = STATIC_SYMBOL("CONNECTION-DIRECTION",AB_package);
    Qconnection_portname = STATIC_SYMBOL("CONNECTION-PORTNAME",AB_package);
    Qconnection_position = STATIC_SYMBOL("CONNECTION-POSITION",AB_package);
    Qconnection_side = STATIC_SYMBOL("CONNECTION-SIDE",AB_package);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qbitwise_and = STATIC_SYMBOL("BITWISE-AND",AB_package);
    Qbitwise_or = STATIC_SYMBOL("BITWISE-OR",AB_package);
    Qbitwise_not = STATIC_SYMBOL("BITWISE-NOT",AB_package);
    Qbitwise_xor = STATIC_SYMBOL("BITWISE-XOR",AB_package);
    Qbitwise_right_shift = STATIC_SYMBOL("BITWISE-RIGHT-SHIFT",AB_package);
    Qbitwise_left_shift = STATIC_SYMBOL("BITWISE-LEFT-SHIFT",AB_package);
    Qbitwise_test = STATIC_SYMBOL("BITWISE-TEST",AB_package);
    Qbitwise_set = STATIC_SYMBOL("BITWISE-SET",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    Qitems_are_connected = STATIC_SYMBOL("ITEMS-ARE-CONNECTED",AB_package);
    Qitems_are_connected_with_direction = 
	    STATIC_SYMBOL("ITEMS-ARE-CONNECTED-WITH-DIRECTION",AB_package);
    Qitems_are_connected_at_ports = 
	    STATIC_SYMBOL("ITEMS-ARE-CONNECTED-AT-PORTS",AB_package);
    Qinsert_at_beginning = STATIC_SYMBOL("INSERT-AT-BEGINNING",AB_package);
    Qinsert_at_end = STATIC_SYMBOL("INSERT-AT-END",AB_package);
    Qinsert_before = STATIC_SYMBOL("INSERT-BEFORE",AB_package);
    Qinsert_after = STATIC_SYMBOL("INSERT-AFTER",AB_package);
    Qinsert_before_element = STATIC_SYMBOL("INSERT-BEFORE-ELEMENT",AB_package);
    Qinsert_after_element = STATIC_SYMBOL("INSERT-AFTER-ELEMENT",AB_package);
    Qchange_element = STATIC_SYMBOL("CHANGE-ELEMENT",AB_package);
    Qportion = STATIC_SYMBOL("PORTION",AB_package);
    Qevaluated_structure = STATIC_SYMBOL("EVALUATED-STRUCTURE",AB_package);
    Qchange_attribute = STATIC_SYMBOL("CHANGE-ATTRIBUTE",AB_package);
    Qchange_evaluated_attribute = 
	    STATIC_SYMBOL("CHANGE-EVALUATED-ATTRIBUTE",AB_package);
    Qremove_attribute = STATIC_SYMBOL("REMOVE-ATTRIBUTE",AB_package);
    Qremove_evaluated_attribute = 
	    STATIC_SYMBOL("REMOVE-EVALUATED-ATTRIBUTE",AB_package);
    Qcharacter_codes_to_text = STATIC_SYMBOL("CHARACTER-CODES-TO-TEXT",
	    AB_package);
    Qtext_to_character_codes = STATIC_SYMBOL("TEXT-TO-CHARACTER-CODES",
	    AB_package);
    Qis_uppercase = STATIC_SYMBOL("IS-UPPERCASE",AB_package);
    Qis_titlecase = STATIC_SYMBOL("IS-TITLECASE",AB_package);
    Qis_lowercase = STATIC_SYMBOL("IS-LOWERCASE",AB_package);
    Qto_uppercase = STATIC_SYMBOL("TO-UPPERCASE",AB_package);
    Qto_titlecase = STATIC_SYMBOL("TO-TITLECASE",AB_package);
    Qto_lowercase = STATIC_SYMBOL("TO-LOWERCASE",AB_package);
    Qis_digit = STATIC_SYMBOL("IS-DIGIT",AB_package);
    Qis_readable_digit = STATIC_SYMBOL("IS-READABLE-DIGIT",AB_package);
    Qis_readable_digit_in_radix = 
	    STATIC_SYMBOL("IS-READABLE-DIGIT-IN-RADIX",AB_package);
    Qreadable_text_for_value = STATIC_SYMBOL("READABLE-TEXT-FOR-VALUE",
	    AB_package);
    Qreadable_text = STATIC_SYMBOL("READABLE-TEXT",AB_package);
    Qreadable_symbol_text = STATIC_SYMBOL("READABLE-SYMBOL-TEXT",AB_package);
    Qcompare_text = STATIC_SYMBOL("COMPARE-TEXT",AB_package);
    Qimport_text = STATIC_SYMBOL("IMPORT-TEXT",AB_package);
    Qexport_text = STATIC_SYMBOL("EXPORT-TEXT",AB_package);
    Qtransform_text_for_unicode_comparison = 
	    STATIC_SYMBOL("TRANSFORM-TEXT-FOR-UNICODE-COMPARISON",AB_package);
    Qtransform_text_for_g2_4_dot_0_comparison = 
	    STATIC_SYMBOL("TRANSFORM-TEXT-FOR-G2-4.0-COMPARISON",AB_package);
    Qfind_java_class = STATIC_SYMBOL("FIND-JAVA-CLASS",AB_package);
    Qformat_numeric_text = STATIC_SYMBOL("FORMAT-NUMERIC-TEXT",AB_package);
    Qdiv_long = STATIC_SYMBOL("DIV-LONG",AB_package);
    SET_SYMBOL_FUNCTION(Qdiv_long,STATIC_FUNCTION(div_long,NIL,FALSE,2,2));
    Qis_nan = STATIC_SYMBOL("IS-NAN",AB_package);
    Qnative_integer_array_set = STATIC_SYMBOL("NATIVE-INTEGER-ARRAY-SET",
	    AB_package);
    Qnative_integer_array_get = STATIC_SYMBOL("NATIVE-INTEGER-ARRAY-GET",
	    AB_package);
    Qnative_integer_array_alloc = 
	    STATIC_SYMBOL("NATIVE-INTEGER-ARRAY-ALLOC",AB_package);
    Qnative_integer_array_free = STATIC_SYMBOL("NATIVE-INTEGER-ARRAY-FREE",
	    AB_package);
    Qnative_float_array_alloc = STATIC_SYMBOL("NATIVE-FLOAT-ARRAY-ALLOC",
	    AB_package);
    Qnative_float_array_free = STATIC_SYMBOL("NATIVE-FLOAT-ARRAY-FREE",
	    AB_package);
    Qnative_float_array_set = STATIC_SYMBOL("NATIVE-FLOAT-ARRAY-SET",
	    AB_package);
    Qnative_float_array_get = STATIC_SYMBOL("NATIVE-FLOAT-ARRAY-GET",
	    AB_package);
    Qkbf_g2nke_count_history_matching_op_and_eventflag = 
	    STATIC_SYMBOL("KBF-G2NKE-COUNT-HISTORY-MATCHING-OP-AND-EVENTFLAG",
	    AB_package);
    Qcount_datapoints_that_evaluate_true_with_eventflag = 
	    STATIC_SYMBOL("COUNT-DATAPOINTS-THAT-EVALUATE-TRUE-WITH-EVENTFLAG",
	    AB_package);
    Qkbf_g2nke_count_history_matching_op = 
	    STATIC_SYMBOL("KBF-G2NKE-COUNT-HISTORY-MATCHING-OP",AB_package);
    Qcount_datapoints_that_evaluate_true = 
	    STATIC_SYMBOL("COUNT-DATAPOINTS-THAT-EVALUATE-TRUE",AB_package);
    Qvector_add = STATIC_SYMBOL("VECTOR-ADD",AB_package);
    Qvector_multiply = STATIC_SYMBOL("VECTOR-MULTIPLY",AB_package);
    Qvector_scalar_multiply = STATIC_SYMBOL("VECTOR-SCALAR-MULTIPLY",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)30L,Qis_digit,
	    Qis_readable_digit,Qis_readable_digit_in_radix,
	    Qreadable_text_for_value,Qreadable_text,Qreadable_symbol_text,
	    Qcompare_text,Qimport_text,Qexport_text,
	    Qtransform_text_for_unicode_comparison,
	    Qtransform_text_for_g2_4_dot_0_comparison,Qfind_java_class,
	    Qformat_numeric_text,Qdiv_long,Qis_nan,
	    Qnative_integer_array_set,Qnative_integer_array_get,
	    Qnative_integer_array_alloc,Qnative_integer_array_free,
	    Qnative_float_array_alloc,Qnative_float_array_free,
	    Qnative_float_array_set,Qnative_float_array_get,
	    Qkbf_g2nke_count_history_matching_op_and_eventflag,
	    Qcount_datapoints_that_evaluate_true_with_eventflag,
	    Qkbf_g2nke_count_history_matching_op,
	    Qcount_datapoints_that_evaluate_true,Qvector_add,
	    Qvector_multiply,Qvector_scalar_multiply);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)32L,Qbitwise_test,
	    Qbitwise_set,Qfalse,Qnot,Qitems_are_connected,
	    Qitems_are_connected_with_direction,
	    Qitems_are_connected_at_ports,Qsequence,Qremove,
	    Qinsert_at_beginning,Qinsert_at_end,Qinsert_before,
	    Qinsert_after,Qinsert_before_element,Qinsert_after_element,
	    Qchange_element,Qconcatenate,Qportion,Qevaluated_structure,
	    Qchange_attribute,Qchange_evaluated_attribute,
	    Qremove_attribute,Qremove_evaluated_attribute,
	    Qcharacter_codes_to_text,Qtext_to_character_codes,
	    Qis_uppercase,Qis_titlecase,Qis_lowercase,Qto_uppercase,
	    Qto_titlecase,Qto_lowercase,list_constant_4);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)32L,Qtime,
	    Qtext_begins_with_quantity,Qis_contained_in_text,
	    Qlength_of_text,Qposition_of_text,Qupper_case_text,
	    Qlower_case_text,Qcapitalize_words,Qinsert_in_text,
	    Qomit_from_text,Qget_from_text,Qreplace_in_text,
	    Qfind_next_pattern,Qfind_next_substring_matching_pattern,
	    Qfind_and_replace_pattern,Qget_next_token,Qlexeme,
	    Qcall_function,Qsymbol,Qtext_to_symbol,Qconnection_direction,
	    Qconnection_portname,Qconnection_position,Qconnection_side,
	    Qconnection_style,Qbitwise_and,Qbitwise_or,Qbitwise_not,
	    Qbitwise_xor,Qbitwise_right_shift,Qbitwise_left_shift,
	    list_constant_5);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)32L,Qarctan,Qabs,Qceiling,
	    Qcos,Qexp,Qexpt,Qfloor,Qln,Qlog,Qmax,Qmin,Qquotient,Qrandom,
	    Qremainder,Qround,Qsin,Qsqrt,Qtruncate,Qtan,
	    Qgreat_circle_distance,Qrgb_symbol,Qtruth_value,Qquantity,
	    Qyear,Qmonth,Qday_of_the_month,Qday_of_the_week,Qaverage,Qhour,
	    Qminute,Qsecond,list_constant_6);
    Built_in_functions = list_constant_7;
    Qargument_range = STATIC_SYMBOL("ARGUMENT-RANGE",AB_package);
    Kb_specific_property_names = CONS(Qargument_range,
	    Kb_specific_property_names);
    Argument_range_gkbprop = Qargument_range;
    Qbuilt_in_function_argument_names = 
	    STATIC_SYMBOL("BUILT-IN-FUNCTION-ARGUMENT-NAMES",AB_package);
    Built_in_function_argument_names_prop = Qbuilt_in_function_argument_names;
    list_constant_8 = STATIC_LIST((SI_Long)12L,Qsin,Qcos,Qsqrt,Qabs,
	    Qceiling,Qfloor,Qround,Qtan,Qexp,Qln,Qlog,Qtruncate);
    list_constant_9 = STATIC_CONS(Qquantity,Qnil);
    function_name = Nil;
    ab_loop_list_ = list_constant_8;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    function_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_or_kb_specific_property_value(function_name,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(function_name,list_constant_9,
	    Qbuilt_in_function_argument_names);
    goto next_loop;
  end_loop:;
    mutate_global_or_kb_specific_property_value(Qgreat_circle_distance,
	    FIX((SI_Long)5L),Argument_range_gkbprop);
    Qlatitude_1_quantity = STATIC_SYMBOL("LATITUDE-1-QUANTITY",AB_package);
    Qlongitude_1_quantity = STATIC_SYMBOL("LONGITUDE-1-QUANTITY",AB_package);
    Qlatitude_2_quantity = STATIC_SYMBOL("LATITUDE-2-QUANTITY",AB_package);
    Qlongitude_2_quantity = STATIC_SYMBOL("LONGITUDE-2-QUANTITY",AB_package);
    Qradius_quantity = STATIC_SYMBOL("RADIUS-QUANTITY",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)5L,Qlatitude_1_quantity,
	    Qlongitude_1_quantity,Qlatitude_2_quantity,
	    Qlongitude_2_quantity,Qradius_quantity);
    mutate_global_property(Qgreat_circle_distance,list_constant_10,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qrgb_symbol,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qred_value_integer = STATIC_SYMBOL("RED-VALUE-INTEGER",AB_package);
    Qgreen_value_integer = STATIC_SYMBOL("GREEN-VALUE-INTEGER",AB_package);
    Qblue_value_integer = STATIC_SYMBOL("BLUE-VALUE-INTEGER",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qred_value_integer,
	    Qgreen_value_integer,Qblue_value_integer);
    mutate_global_property(Qrgb_symbol,list_constant_11,
	    Qbuilt_in_function_argument_names);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qexpt,Qquotient,Qremainder);
    function_name = Nil;
    ab_loop_list_ = list_constant_12;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    function_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_or_kb_specific_property_value(function_name,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    goto next_loop_1;
  end_loop_1:;
    Qbase_quantity = STATIC_SYMBOL("BASE-QUANTITY",AB_package);
    Qpower_quantity = STATIC_SYMBOL("POWER-QUANTITY",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qbase_quantity,Qpower_quantity);
    mutate_global_property(Qexpt,list_constant_13,
	    Qbuilt_in_function_argument_names);
    Qdividend_quantity = STATIC_SYMBOL("DIVIDEND-QUANTITY",AB_package);
    Qdivisor_quantity = STATIC_SYMBOL("DIVISOR-QUANTITY",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qdividend_quantity,
	    Qdivisor_quantity);
    mutate_global_property(Qquotient,list_constant_14,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qremainder,list_constant_14,
	    Qbuilt_in_function_argument_names);
    list_constant_15 = STATIC_CONS(FIX((SI_Long)1L),FIX((SI_Long)2L));
    mutate_global_or_kb_specific_property_value(Qrandom,list_constant_15,
	    Argument_range_gkbprop);
    Qupper_bound_quantity = STATIC_SYMBOL("UPPER-BOUND-QUANTITY",AB_package);
    list_constant_16 = STATIC_CONS(Qupper_bound_quantity,Qnil);
    Qlower_bound_quantity = STATIC_SYMBOL("LOWER-BOUND-QUANTITY",AB_package);
    list_constant_17 = STATIC_CONS(Qlower_bound_quantity,list_constant_16);
    list_constant_18 = STATIC_LIST((SI_Long)2L,list_constant_16,
	    list_constant_17);
    mutate_global_property(Qrandom,list_constant_18,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qis_contained_in_text,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qcontaining_text = STATIC_SYMBOL("CONTAINING-TEXT",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qtext,Qcontaining_text);
    mutate_global_property(Qis_contained_in_text,list_constant_19,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qlength_of_text,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    list_constant_20 = STATIC_CONS(Qtext,Qnil);
    mutate_global_property(Qlength_of_text,list_constant_20,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qposition_of_text,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    mutate_global_property(Qposition_of_text,list_constant_19,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qupper_case_text,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qupper_case_text,list_constant_20,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qlower_case_text,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qlower_case_text,list_constant_20,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qcapitalize_words,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qcapitalize_words,list_constant_20,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qinsert_in_text,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qtext_to_insert = STATIC_SYMBOL("TEXT-TO-INSERT",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)3L,Qtext_to_insert,Qtext,
	    Qposition);
    mutate_global_property(Qinsert_in_text,list_constant_21,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qomit_from_text,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qbegin = STATIC_SYMBOL("BEGIN",AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)3L,Qtext,Qbegin,Qend);
    mutate_global_property(Qomit_from_text,list_constant_22,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qreplace_in_text,
	    FIX((SI_Long)4L),Argument_range_gkbprop);
    Qtext_to_substitute = STATIC_SYMBOL("TEXT-TO-SUBSTITUTE",AB_package);
    Qsource_text = STATIC_SYMBOL("SOURCE-TEXT",AB_package);
    Qstart_index = STATIC_SYMBOL("START-INDEX",AB_package);
    Qend_index = STATIC_SYMBOL("END-INDEX",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)4L,Qtext_to_substitute,
	    Qsource_text,Qstart_index,Qend_index);
    mutate_global_property(Qreplace_in_text,list_constant_23,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qget_from_text,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qstart_index,Qend_index);
    list_constant_25 = STATIC_CONS(Qtext,list_constant_24);
    mutate_global_property(Qget_from_text,list_constant_25,
	    Qbuilt_in_function_argument_names);
    list_constant_26 = STATIC_CONS(FIX((SI_Long)3L),FIX((SI_Long)4L));
    mutate_global_or_kb_specific_property_value(Qfind_next_pattern,
	    list_constant_26,Argument_range_gkbprop);
    Qsearch_pattern = STATIC_SYMBOL("SEARCH-PATTERN",AB_package);
    Qstart_position = STATIC_SYMBOL("START-POSITION",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qsearch_pattern,
	    Qsource_text,Qstart_position);
    list_constant_28 = STATIC_CONS(list_constant_27,Qnil);
    mutate_global_property(Qfind_next_pattern,list_constant_28,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qfind_next_substring_matching_pattern,
	    list_constant_26,Argument_range_gkbprop);
    mutate_global_property(Qfind_next_substring_matching_pattern,
	    list_constant_28,Qbuilt_in_function_argument_names);
    list_constant_29 = STATIC_CONS(FIX((SI_Long)5L),FIX((SI_Long)6L));
    mutate_global_or_kb_specific_property_value(Qfind_and_replace_pattern,
	    list_constant_29,Argument_range_gkbprop);
    Qend_position = STATIC_SYMBOL("END-POSITION",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)5L,Qsearch_pattern,
	    Qtext_to_substitute,Qsource_text,Qstart_position,Qend_position);
    Qflags = STATIC_SYMBOL("FLAGS",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)6L,Qsearch_pattern,
	    Qtext_to_substitute,Qsource_text,Qstart_position,Qend_position,
	    Qflags);
    list_constant_32 = STATIC_LIST((SI_Long)2L,list_constant_30,
	    list_constant_31);
    mutate_global_property(Qfind_and_replace_pattern,list_constant_32,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qget_next_token,
	    list_constant_26,Argument_range_gkbprop);
    Qtokenizer = STATIC_SYMBOL("TOKENIZER",AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qsource_text,Qstart_position);
    list_constant_34 = STATIC_CONS(Qtokenizer,list_constant_33);
    mutate_global_property(Qget_next_token,list_constant_34,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qlexeme,FIX((SI_Long)2L),
	    Argument_range_gkbprop);
    Qtoken = STATIC_SYMBOL("TOKEN",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qsource_text,Qtoken);
    mutate_global_property(Qlexeme,list_constant_35,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qarctan,list_constant_15,
	    Argument_range_gkbprop);
    Qy = STATIC_SYMBOL("Y",AB_package);
    list_constant_36 = STATIC_CONS(Qy,Qnil);
    Qx = STATIC_SYMBOL("X",AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qy,Qx);
    list_constant_38 = STATIC_LIST((SI_Long)2L,list_constant_36,
	    list_constant_37);
    mutate_global_property(Qarctan,list_constant_38,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qtruth_value,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    list_constant_39 = STATIC_CONS(Qvalue,Qnil);
    mutate_global_property(Qtruth_value,list_constant_39,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qquantity,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    mutate_global_property(Qquantity,list_constant_39,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qtext_begins_with_quantity,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qtext_begins_with_quantity,list_constant_20,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qsymbol,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    mutate_global_property(Qsymbol,list_constant_20,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qtext_to_symbol,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qtext_to_symbol,list_constant_20,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qnot,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    list_constant_40 = STATIC_CONS(Qtruth_value,Qnil);
    mutate_global_property(Qnot,list_constant_40,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qfalse,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    mutate_global_property(Qfalse,list_constant_40,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qyear,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    list_constant_41 = STATIC_CONS(Qtime,Qnil);
    mutate_global_property(Qyear,list_constant_41,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qmonth,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    mutate_global_property(Qmonth,list_constant_41,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qday_of_the_month,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qday_of_the_month,list_constant_41,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qday_of_the_week,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qday_of_the_week,list_constant_41,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qhour,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    mutate_global_property(Qhour,list_constant_41,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qminute,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    mutate_global_property(Qminute,list_constant_41,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qsecond,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    mutate_global_property(Qsecond,list_constant_41,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qtime,FIX((SI_Long)6L),
	    Argument_range_gkbprop);
    Qdate = STATIC_SYMBOL("DATE",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)6L,Qyear,Qmonth,Qdate,Qhour,
	    Qminute,Qsecond);
    mutate_global_property(Qtime,list_constant_42,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qremove,FIX((SI_Long)2L),
	    Argument_range_gkbprop);
    Qindex_to_remove = STATIC_SYMBOL("INDEX-TO-REMOVE",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qsequence,Qindex_to_remove);
    mutate_global_property(Qremove,list_constant_43,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qinsert_at_beginning,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qitem_or_value_to_add = STATIC_SYMBOL("ITEM-OR-VALUE-TO-ADD",AB_package);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qsequence,
	    Qitem_or_value_to_add);
    mutate_global_property(Qinsert_at_beginning,list_constant_44,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qinsert_at_end,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    mutate_global_property(Qinsert_at_end,list_constant_44,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qinsert_before,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qnew_element = STATIC_SYMBOL("NEW-ELEMENT",AB_package);
    Qexisting_element = STATIC_SYMBOL("EXISTING-ELEMENT",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)3L,Qsequence,Qnew_element,
	    Qexisting_element);
    mutate_global_property(Qinsert_before,list_constant_45,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qinsert_after,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    mutate_global_property(Qinsert_after,list_constant_45,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qinsert_before_element,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qindex = STATIC_SYMBOL("INDEX",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)3L,Qsequence,Qindex,Qnew_element);
    mutate_global_property(Qinsert_before_element,list_constant_46,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qinsert_after_element,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    mutate_global_property(Qinsert_after_element,list_constant_46,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qchange_element,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    mutate_global_property(Qchange_element,list_constant_46,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qportion,FIX((SI_Long)3L),
	    Argument_range_gkbprop);
    Qnumber_to_copy = STATIC_SYMBOL("NUMBER-TO-COPY",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)3L,Qsequence,Qstart_index,
	    Qnumber_to_copy);
    mutate_global_property(Qportion,list_constant_47,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qchange_attribute,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    list_constant_48 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    Qattribute_name,Qitem_or_value);
    mutate_global_property(Qchange_attribute,list_constant_48,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qchange_evaluated_attribute,
	    FIX((SI_Long)3L),Argument_range_gkbprop);
    Qsymbol_expression = STATIC_SYMBOL("SYMBOL-EXPRESSION",AB_package);
    list_constant_49 = STATIC_CONS(Qitem_or_value,Qnil);
    list_constant_50 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    Qsymbol_expression,list_constant_49);
    mutate_global_property(Qchange_evaluated_attribute,list_constant_50,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qremove_attribute,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qab_structure,Qattribute_name);
    mutate_global_property(Qremove_attribute,list_constant_51,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qremove_evaluated_attribute,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    Qsymbol_expression);
    mutate_global_property(Qremove_evaluated_attribute,list_constant_52,
	    Qbuilt_in_function_argument_names);
    Qattribute_descriptions_of_item_as_structure = 
	    STATIC_SYMBOL("ATTRIBUTE-DESCRIPTIONS-OF-ITEM-AS-STRUCTURE",
	    AB_package);
    mutate_global_or_kb_specific_property_value(Qattribute_descriptions_of_item_as_structure,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qattribute_descriptions_of_class_as_structure = 
	    STATIC_SYMBOL("ATTRIBUTE-DESCRIPTIONS-OF-CLASS-AS-STRUCTURE",
	    AB_package);
    mutate_global_or_kb_specific_property_value(Qattribute_descriptions_of_class_as_structure,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    mutate_global_or_kb_specific_property_value(Qcharacter_codes_to_text,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    Qcharacter_codes = STATIC_SYMBOL("CHARACTER-CODES",AB_package);
    list_constant_53 = STATIC_CONS(Qcharacter_codes,Qnil);
    mutate_global_property(Qcharacter_codes_to_text,list_constant_53,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qtext_to_character_codes,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qtext_to_character_codes,list_constant_20,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qis_uppercase,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    Qcharacter_code = STATIC_SYMBOL("CHARACTER-CODE",AB_package);
    list_constant_54 = STATIC_CONS(Qcharacter_code,Qnil);
    mutate_global_property(Qis_uppercase,list_constant_54,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qis_titlecase,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qis_titlecase,list_constant_54,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qis_lowercase,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qis_lowercase,list_constant_54,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qto_uppercase,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qto_uppercase,list_constant_54,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qto_titlecase,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qto_titlecase,list_constant_54,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qto_lowercase,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qto_lowercase,list_constant_54,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qis_digit,FIX((SI_Long)1L),
	    Argument_range_gkbprop);
    mutate_global_property(Qis_digit,list_constant_54,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qis_readable_digit,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qis_readable_digit,list_constant_54,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qis_readable_digit_in_radix,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qradix = STATIC_SYMBOL("RADIX",AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qcharacter_code,Qradix);
    mutate_global_property(Qis_readable_digit_in_radix,list_constant_55,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qreadable_text_for_value,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qreadable_text_for_value,list_constant_39,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qreadable_text,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    Qprinted_text = STATIC_SYMBOL("PRINTED-TEXT",AB_package);
    list_constant_56 = STATIC_CONS(Qprinted_text,Qnil);
    mutate_global_property(Qreadable_text,list_constant_56,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qreadable_symbol_text,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    mutate_global_property(Qreadable_symbol_text,list_constant_56,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qcompare_text,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qtext_1 = STATIC_SYMBOL("TEXT-1",AB_package);
    Qtext_2 = STATIC_SYMBOL("TEXT-2",AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qtext_1,Qtext_2);
    mutate_global_property(Qcompare_text,list_constant_57,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qimport_text,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qexternal_text = STATIC_SYMBOL("EXTERNAL-TEXT",AB_package);
    Qconversion_style = STATIC_SYMBOL("CONVERSION-STYLE",AB_package);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qexternal_text,
	    Qconversion_style);
    mutate_global_property(Qimport_text,list_constant_58,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qexport_text,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qunicode_text = STATIC_SYMBOL("UNICODE-TEXT",AB_package);
    list_constant_59 = STATIC_CONS(Qconversion_style,Qnil);
    list_constant_60 = STATIC_CONS(Qunicode_text,list_constant_59);
    mutate_global_property(Qexport_text,list_constant_60,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qtransform_text_for_unicode_comparison,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qtext_to_transform = STATIC_SYMBOL("TEXT-TO-TRANSFORM",AB_package);
    Qconsider_case = STATIC_SYMBOL("CONSIDER-CASE",AB_package);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qtext_to_transform,
	    Qconsider_case);
    mutate_global_property(Qtransform_text_for_unicode_comparison,
	    list_constant_61,Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qtransform_text_for_g2_4_dot_0_comparison,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    mutate_global_property(Qtransform_text_for_g2_4_dot_0_comparison,
	    list_constant_61,Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qfind_java_class,
	    FIX((SI_Long)1L),Argument_range_gkbprop);
    Qnumber_as_text = STATIC_SYMBOL("NUMBER-AS-TEXT",AB_package);
    Qddd_dot_dddd_format_text = STATIC_SYMBOL("DDD.DDDD-FORMAT-TEXT",
	    AB_package);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qnumber_as_text,
	    Qddd_dot_dddd_format_text);
    mutate_global_property(Qformat_numeric_text,list_constant_62,
	    Qbuilt_in_function_argument_names);
    mutate_global_or_kb_specific_property_value(Qformat_numeric_text,
	    FIX((SI_Long)2L),Argument_range_gkbprop);
    Qinteger_1 = STATIC_SYMBOL("INTEGER-1",AB_package);
    Qinteger_2 = STATIC_SYMBOL("INTEGER-2",AB_package);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qinteger_1,Qinteger_2);
    mutate_global_property(Qbitwise_and,list_constant_63,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qbitwise_or,list_constant_63,
	    Qbuilt_in_function_argument_names);
    list_constant_64 = STATIC_CONS(Qinteger,Qnil);
    mutate_global_property(Qbitwise_not,list_constant_64,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qbitwise_xor,list_constant_63,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qbitwise_right_shift,list_constant_63,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qbitwise_left_shift,list_constant_63,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qbitwise_test,list_constant_63,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qbitwise_set,list_constant_63,
	    Qbuilt_in_function_argument_names);
    Qquantity_1 = STATIC_SYMBOL("QUANTITY-1",AB_package);
    Qquantity_2 = STATIC_SYMBOL("QUANTITY-2",AB_package);
    Qdot_dot_dot = STATIC_SYMBOL("...",AB_package);
    list_constant_65 = STATIC_LIST((SI_Long)3L,Qquantity_1,Qquantity_2,
	    Qdot_dot_dot);
    mutate_global_property(Qmax,list_constant_65,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qmin,list_constant_65,
	    Qbuilt_in_function_argument_names);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qitem,Qconnection);
    mutate_global_property(Qconnection_direction,list_constant_66,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qconnection_portname,list_constant_66,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qconnection_position,list_constant_66,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qconnection_side,list_constant_66,
	    Qbuilt_in_function_argument_names);
    list_constant_67 = STATIC_CONS(Qconnection,Qnil);
    mutate_global_property(Qconnection_style,list_constant_67,
	    Qbuilt_in_function_argument_names);
    Qitem_1 = STATIC_SYMBOL("ITEM-1",AB_package);
    Qitem_2 = STATIC_SYMBOL("ITEM-2",AB_package);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qitem_1,Qitem_2);
    mutate_global_property(Qitems_are_connected,list_constant_68,
	    Qbuilt_in_function_argument_names);
    Qitem_1_direction = STATIC_SYMBOL("ITEM-1-DIRECTION",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)3L,Qitem_1,Qitem_2,
	    Qitem_1_direction);
    mutate_global_property(Qitems_are_connected_with_direction,
	    list_constant_69,Qbuilt_in_function_argument_names);
    Qportname_1 = STATIC_SYMBOL("PORTNAME-1",AB_package);
    Qportname_2 = STATIC_SYMBOL("PORTNAME-2",AB_package);
    list_constant_70 = STATIC_LIST((SI_Long)4L,Qitem_1,Qitem_2,Qportname_1,
	    Qportname_2);
    mutate_global_property(Qitems_are_connected_at_ports,list_constant_70,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qaverage,list_constant_65,
	    Qbuilt_in_function_argument_names);
    Qfunction_definition_expression = 
	    STATIC_SYMBOL("FUNCTION-DEFINITION-EXPRESSION",AB_package);
    Qobt_argument = STATIC_SYMBOL("[ARGUMENT",AB_package);
    Qdot_dot_dot_cbt = STATIC_SYMBOL("...]",AB_package);
    list_constant_71 = STATIC_LIST((SI_Long)3L,
	    Qfunction_definition_expression,Qobt_argument,Qdot_dot_dot_cbt);
    mutate_global_property(Qcall_function,list_constant_71,
	    Qbuilt_in_function_argument_names);
    Qobt_item_or_value = STATIC_SYMBOL("[ITEM-OR-VALUE",AB_package);
    list_constant_72 = STATIC_CONS(Qdot_dot_dot_cbt,Qnil);
    list_constant_73 = STATIC_CONS(Qobt_item_or_value,list_constant_72);
    mutate_global_property(Qsequence,list_constant_73,
	    Qbuilt_in_function_argument_names);
    Qobt_sequence = STATIC_SYMBOL("[SEQUENCE",AB_package);
    list_constant_74 = STATIC_CONS(Qobt_sequence,list_constant_72);
    mutate_global_property(Qconcatenate,list_constant_74,
	    Qbuilt_in_function_argument_names);
    QOBT_OBT_ATTRIBUTE_NAME_COL_SP_ITEM_OR_VALUE_CBT = 
	    STATIC_SYMBOL("[[attribute-name: item-or-value]",AB_package);
    list_constant_75 = 
	    STATIC_CONS(QOBT_OBT_ATTRIBUTE_NAME_COL_SP_ITEM_OR_VALUE_CBT,
	    list_constant_72);
    mutate_global_property(Qab_structure,list_constant_75,
	    Qbuilt_in_function_argument_names);
    Qobt_obt_symbol_expression = STATIC_SYMBOL("[[SYMBOL-EXPRESSION",
	    AB_package);
    Qitem_or_value_cbt = STATIC_SYMBOL("ITEM-OR-VALUE]",AB_package);
    list_constant_76 = STATIC_LIST_STAR((SI_Long)3L,
	    Qobt_obt_symbol_expression,Qitem_or_value_cbt,list_constant_72);
    mutate_global_property(Qevaluated_structure,list_constant_76,
	    Qbuilt_in_function_argument_names);
    list_constant_77 = STATIC_CONS(Qfloat,Qnil);
    mutate_global_property(Qis_nan,list_constant_77,
	    Qbuilt_in_function_argument_names);
    Qlong_1 = STATIC_SYMBOL("LONG-1",AB_package);
    Qlong_2 = STATIC_SYMBOL("LONG-2",AB_package);
    list_constant_78 = STATIC_LIST((SI_Long)2L,Qlong_1,Qlong_2);
    mutate_global_property(Qdiv_long,list_constant_78,
	    Qbuilt_in_function_argument_names);
    Qnative_array_set = STATIC_SYMBOL("NATIVE-ARRAY-SET",AB_package);
    Qhandle = STATIC_SYMBOL("HANDLE",AB_package);
    list_constant_79 = STATIC_LIST((SI_Long)3L,Qhandle,Qvalue,Qindex);
    mutate_global_property(Qnative_array_set,list_constant_79,
	    Qbuilt_in_function_argument_names);
    Qnative_array_get = STATIC_SYMBOL("NATIVE-ARRAY-GET",AB_package);
    list_constant_80 = STATIC_CONS(Qindex,Qnil);
    list_constant_81 = STATIC_CONS(Qhandle,list_constant_80);
    mutate_global_property(Qnative_array_get,list_constant_81,
	    Qbuilt_in_function_argument_names);
    Qnative_array_alloc = STATIC_SYMBOL("NATIVE-ARRAY-ALLOC",AB_package);
    Qsize = STATIC_SYMBOL("SIZE",AB_package);
    list_constant_82 = STATIC_CONS(Qsize,Qnil);
    mutate_global_property(Qnative_array_alloc,list_constant_82,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_alloc,list_constant_82,
	    Qbuilt_in_function_argument_names);
    list_constant_83 = STATIC_CONS(Qhandle,Qnil);
    mutate_global_property(Qnative_float_array_free,list_constant_83,
	    Qbuilt_in_function_argument_names);
    list_constant_84 = STATIC_LIST_STAR((SI_Long)3L,Qhandle,Qindex,
	    list_constant_39);
    mutate_global_property(Qnative_float_array_set,list_constant_84,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_get,list_constant_81,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_array_set,list_constant_79,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_array_get,list_constant_81,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_array_alloc,list_constant_82,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_alloc,list_constant_82,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_free,list_constant_83,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_set,list_constant_84,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_get,list_constant_81,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_array_set,list_constant_79,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_array_get,list_constant_81,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_array_alloc,list_constant_82,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_alloc,list_constant_82,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_free,list_constant_83,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_set,list_constant_84,
	    Qbuilt_in_function_argument_names);
    mutate_global_property(Qnative_float_array_get,list_constant_81,
	    Qbuilt_in_function_argument_names);
    Qevaluator_form_writer = STATIC_SYMBOL("EVALUATOR-FORM-WRITER",AB_package);
    Evaluator_form_writer_prop = Qevaluator_form_writer;
    Qfuzzy_lt = STATIC_SYMBOL("FUZZY-<",AB_package);
    Qfuzzy_writer = STATIC_SYMBOL("FUZZY-WRITER",AB_package);
    mutate_global_property(Qfuzzy_lt,Qfuzzy_writer,Qevaluator_form_writer);
    Qfuzzy_gt = STATIC_SYMBOL("FUZZY->",AB_package);
    mutate_global_property(Qfuzzy_gt,Qfuzzy_writer,Qevaluator_form_writer);
    Qfuzzy_eq = STATIC_SYMBOL("FUZZY-=",AB_package);
    mutate_global_property(Qfuzzy_eq,Qfuzzy_writer,Qevaluator_form_writer);
    Qfuzzy_not_eq = STATIC_SYMBOL("FUZZY-NOT-=",AB_package);
    mutate_global_property(Qfuzzy_not_eq,Qfuzzy_writer,Qevaluator_form_writer);
    Qis_more_true_than = STATIC_SYMBOL("IS-MORE-TRUE-THAN",AB_package);
    Qfuzzy_logic_comparitor_writer = 
	    STATIC_SYMBOL("FUZZY-LOGIC-COMPARITOR-WRITER",AB_package);
    mutate_global_property(Qis_more_true_than,
	    Qfuzzy_logic_comparitor_writer,Qevaluator_form_writer);
    Qis_not_more_true_than = STATIC_SYMBOL("IS-NOT-MORE-TRUE-THAN",AB_package);
    mutate_global_property(Qis_not_more_true_than,
	    Qfuzzy_logic_comparitor_writer,Qevaluator_form_writer);
    Qis_less_true_than = STATIC_SYMBOL("IS-LESS-TRUE-THAN",AB_package);
    mutate_global_property(Qis_less_true_than,
	    Qfuzzy_logic_comparitor_writer,Qevaluator_form_writer);
    Qis_not_less_true_than = STATIC_SYMBOL("IS-NOT-LESS-TRUE-THAN",AB_package);
    mutate_global_property(Qis_not_less_true_than,
	    Qfuzzy_logic_comparitor_writer,Qevaluator_form_writer);
    Qfalse_writer = STATIC_SYMBOL("FALSE-WRITER",AB_package);
    mutate_global_property(Qfalse,Qfalse_writer,Qevaluator_form_writer);
    Qquote_expression_writer = STATIC_SYMBOL("QUOTE-EXPRESSION-WRITER",
	    AB_package);
    mutate_global_property(Qquote,Qquote_expression_writer,
	    Qevaluator_form_writer);
    Qif_expression = STATIC_SYMBOL("IF-EXPRESSION",AB_package);
    Qif_expression_writer = STATIC_SYMBOL("IF-EXPRESSION-WRITER",AB_package);
    mutate_global_property(Qif_expression,Qif_expression_writer,
	    Qevaluator_form_writer);
    Qinterpolated_value = STATIC_SYMBOL("INTERPOLATED-VALUE",AB_package);
    Qhistoric_function_writer = STATIC_SYMBOL("HISTORIC-FUNCTION-WRITER",
	    AB_package);
    mutate_global_property(Qinterpolated_value,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qhistoric_value = STATIC_SYMBOL("HISTORIC-VALUE",AB_package);
    mutate_global_property(Qhistoric_value,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qvalue_of_previous_datapoint = 
	    STATIC_SYMBOL("VALUE-OF-PREVIOUS-DATAPOINT",AB_package);
    mutate_global_property(Qvalue_of_previous_datapoint,
	    Qhistoric_function_writer,Qevaluator_form_writer);
    Qcollection_time_of_previous_datapoint = 
	    STATIC_SYMBOL("COLLECTION-TIME-OF-PREVIOUS-DATAPOINT",AB_package);
    mutate_global_property(Qcollection_time_of_previous_datapoint,
	    Qhistoric_function_writer,Qevaluator_form_writer);
    Qmaximum_value = STATIC_SYMBOL("MAXIMUM-VALUE",AB_package);
    mutate_global_property(Qmaximum_value,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qminimum_value = STATIC_SYMBOL("MINIMUM-VALUE",AB_package);
    mutate_global_property(Qminimum_value,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qaverage_value = STATIC_SYMBOL("AVERAGE-VALUE",AB_package);
    mutate_global_property(Qaverage_value,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qsum_of_values = STATIC_SYMBOL("SUM-OF-VALUES",AB_package);
    mutate_global_property(Qsum_of_values,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qstandard_deviation = STATIC_SYMBOL("STANDARD-DEVIATION",AB_package);
    mutate_global_property(Qstandard_deviation,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qnumber_of_datapoints = STATIC_SYMBOL("NUMBER-OF-DATAPOINTS",AB_package);
    mutate_global_property(Qnumber_of_datapoints,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qrate_of_change = STATIC_SYMBOL("RATE-OF-CHANGE",AB_package);
    mutate_global_property(Qrate_of_change,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qintegral = STATIC_SYMBOL("INTEGRAL",AB_package);
    mutate_global_property(Qintegral,Qhistoric_function_writer,
	    Qevaluator_form_writer);
    Qhas_current_value = STATIC_SYMBOL("HAS-CURRENT-VALUE",AB_package);
    Qpostfix_writer = STATIC_SYMBOL("POSTFIX-WRITER",AB_package);
    mutate_global_property(Qhas_current_value,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qhas_a_value = STATIC_SYMBOL("HAS-A-VALUE",AB_package);
    mutate_global_property(Qhas_a_value,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qhas_no_value = STATIC_SYMBOL("HAS-NO-VALUE",AB_package);
    mutate_global_property(Qhas_no_value,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qhas_a_name = STATIC_SYMBOL("HAS-A-NAME",AB_package);
    mutate_global_property(Qhas_a_name,Qpostfix_writer,Qevaluator_form_writer);
    Qhas_no_name = STATIC_SYMBOL("HAS-NO-NAME",AB_package);
    mutate_global_property(Qhas_no_name,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qhas_a_current_value = STATIC_SYMBOL("HAS-A-CURRENT-VALUE",AB_package);
    mutate_global_property(Qhas_a_current_value,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qhas_no_current_value = STATIC_SYMBOL("HAS-NO-CURRENT-VALUE",AB_package);
    mutate_global_property(Qhas_no_current_value,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qvalue_of = STATIC_SYMBOL("VALUE-OF",AB_package);
    Qprefix_writer = STATIC_SYMBOL("PREFIX-WRITER",AB_package);
    mutate_global_property(Qvalue_of,Qprefix_writer,Qevaluator_form_writer);
    Qcurrent_value_of = STATIC_SYMBOL("CURRENT-VALUE-OF",AB_package);
    mutate_global_property(Qcurrent_value_of,Qprefix_writer,
	    Qevaluator_form_writer);
    Qsimulated_value_of = STATIC_SYMBOL("SIMULATED-VALUE-OF",AB_package);
    mutate_global_property(Qsimulated_value_of,Qprefix_writer,
	    Qevaluator_form_writer);
    Qexpiration_time_of = STATIC_SYMBOL("EXPIRATION-TIME-OF",AB_package);
    mutate_global_property(Qexpiration_time_of,Qprefix_writer,
	    Qevaluator_form_writer);
    Qcollection_time_of = STATIC_SYMBOL("COLLECTION-TIME-OF",AB_package);
    mutate_global_property(Qcollection_time_of,Qprefix_writer,
	    Qevaluator_form_writer);
    Qis_not = STATIC_SYMBOL("IS-NOT",AB_package);
    Qwrite_is = STATIC_SYMBOL("WRITE-IS",AB_package);
    mutate_global_property(Qis_not,Qwrite_is,Qevaluator_form_writer);
    Qis = STATIC_SYMBOL("IS",AB_package);
    mutate_global_property(Qis,Qwrite_is,Qevaluator_form_writer);
    Qattribute_name_function_writer = 
	    STATIC_SYMBOL("ATTRIBUTE-NAME-FUNCTION-WRITER",AB_package);
    mutate_global_property(Qattribute_name,Qattribute_name_function_writer,
	    Qevaluator_form_writer);
    Qcurrent_time = STATIC_SYMBOL("CURRENT-TIME",AB_package);
    Qwrite_the_current_time = STATIC_SYMBOL("WRITE-THE-CURRENT-TIME",
	    AB_package);
    mutate_global_property(Qcurrent_time,Qwrite_the_current_time,
	    Qevaluator_form_writer);
    Qcurrent_real_time = STATIC_SYMBOL("CURRENT-REAL-TIME",AB_package);
    Qwrite_the_current_real_time = 
	    STATIC_SYMBOL("WRITE-THE-CURRENT-REAL-TIME",AB_package);
    mutate_global_property(Qcurrent_real_time,Qwrite_the_current_real_time,
	    Qevaluator_form_writer);
    Qcurrent_subsecond_time = STATIC_SYMBOL("CURRENT-SUBSECOND-TIME",
	    AB_package);
    Qwrite_the_current_subsecond_time = 
	    STATIC_SYMBOL("WRITE-THE-CURRENT-SUBSECOND-TIME",AB_package);
    mutate_global_property(Qcurrent_subsecond_time,
	    Qwrite_the_current_subsecond_time,Qevaluator_form_writer);
    Qreceives_a_value = STATIC_SYMBOL("RECEIVES-A-VALUE",AB_package);
    mutate_global_property(Qreceives_a_value,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qfails_to_receive_a_value = STATIC_SYMBOL("FAILS-TO-RECEIVE-A-VALUE",
	    AB_package);
    mutate_global_property(Qfails_to_receive_a_value,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qis_moved = STATIC_SYMBOL("IS-MOVED",AB_package);
    mutate_global_property(Qis_moved,Qpostfix_writer,Qevaluator_form_writer);
    Qis_moved_by_the_user = STATIC_SYMBOL("IS-MOVED-BY-THE-USER",AB_package);
    mutate_global_property(Qis_moved_by_the_user,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qis_moved_by_g2 = STATIC_SYMBOL("IS-MOVED-BY-G2",AB_package);
    mutate_global_property(Qis_moved_by_g2,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qis_resized_by_the_user = STATIC_SYMBOL("IS-RESIZED-BY-THE-USER",
	    AB_package);
    mutate_global_property(Qis_resized_by_the_user,Qpostfix_writer,
	    Qevaluator_form_writer);
    Qbecomes_related = STATIC_SYMBOL("BECOMES-RELATED",AB_package);
    Qwrite_relation_event_literal = 
	    STATIC_SYMBOL("WRITE-RELATION-EVENT-LITERAL",AB_package);
    mutate_global_property(Qbecomes_related,Qwrite_relation_event_literal,
	    Qevaluator_form_writer);
    Qceases_to_be_related = STATIC_SYMBOL("CEASES-TO-BE-RELATED",AB_package);
    mutate_global_property(Qceases_to_be_related,
	    Qwrite_relation_event_literal,Qevaluator_form_writer);
    Qhas_generic_event = STATIC_SYMBOL("HAS-GENERIC-EVENT",AB_package);
    Qwrite_generic_event_literal = 
	    STATIC_SYMBOL("WRITE-GENERIC-EVENT-LITERAL",AB_package);
    mutate_global_property(Qhas_generic_event,Qwrite_generic_event_literal,
	    Qevaluator_form_writer);
    Qnupec_synchronization_occurs = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZATION-OCCURS",AB_package);
    Qwrite_nupec_synchronization_occurs = 
	    STATIC_SYMBOL("WRITE-NUPEC-SYNCHRONIZATION-OCCURS",AB_package);
    mutate_global_property(Qnupec_synchronization_occurs,
	    Qwrite_nupec_synchronization_occurs,Qevaluator_form_writer);
    Qdistance_between = STATIC_SYMBOL("DISTANCE-BETWEEN",AB_package);
    Qwrite_in_binary_role_style = 
	    STATIC_SYMBOL("WRITE-IN-BINARY-ROLE-STYLE",AB_package);
    mutate_global_property(Qdistance_between,Qwrite_in_binary_role_style,
	    Qevaluator_form_writer);
    Qdistance_between_and_the_nearest = 
	    STATIC_SYMBOL("DISTANCE-BETWEEN-AND-THE-NEAREST",AB_package);
    Qwrite_distance_between_and_the_nearest = 
	    STATIC_SYMBOL("WRITE-DISTANCE-BETWEEN-AND-THE-NEAREST",AB_package);
    mutate_global_property(Qdistance_between_and_the_nearest,
	    Qwrite_distance_between_and_the_nearest,Qevaluator_form_writer);
    Qsame_as = STATIC_SYMBOL("SAME-AS",AB_package);
    Qwrite_same_as = STATIC_SYMBOL("WRITE-SAME-AS",AB_package);
    mutate_global_property(Qsame_as,Qwrite_same_as,Qevaluator_form_writer);
    Qnot_same_as = STATIC_SYMBOL("NOT-SAME-AS",AB_package);
    mutate_global_property(Qnot_same_as,Qwrite_same_as,Qevaluator_form_writer);
    Qis_of_class = STATIC_SYMBOL("IS-OF-CLASS",AB_package);
    Qwrite_is_a = STATIC_SYMBOL("WRITE-IS-A",AB_package);
    mutate_global_property(Qis_of_class,Qwrite_is_a,Qevaluator_form_writer);
    Qis_not_of_class = STATIC_SYMBOL("IS-NOT-OF-CLASS",AB_package);
    mutate_global_property(Qis_not_of_class,Qwrite_is_a,
	    Qevaluator_form_writer);
    Qis_active = STATIC_SYMBOL("IS-ACTIVE",AB_package);
    Qwrite_is_active = STATIC_SYMBOL("WRITE-IS-ACTIVE",AB_package);
    mutate_global_property(Qis_active,Qwrite_is_active,Qevaluator_form_writer);
    Qis_not_active = STATIC_SYMBOL("IS-NOT-ACTIVE",AB_package);
    mutate_global_property(Qis_not_active,Qwrite_is_active,
	    Qevaluator_form_writer);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qwrite_as_if_role = STATIC_SYMBOL("WRITE-AS-IF-ROLE",AB_package);
    mutate_global_property(Qname,Qwrite_as_if_role,Qevaluator_form_writer);
    Qis_related = STATIC_SYMBOL("IS-RELATED",AB_package);
    Qrelation_writer = STATIC_SYMBOL("RELATION-WRITER",AB_package);
    mutate_global_property(Qis_related,Qrelation_writer,
	    Qevaluator_form_writer);
    Qis_not_related = STATIC_SYMBOL("IS-NOT-RELATED",AB_package);
    mutate_global_property(Qis_not_related,Qrelation_writer,
	    Qevaluator_form_writer);
    Qformat_form = STATIC_SYMBOL("FORMAT-FORM",AB_package);
    Qwrite_format_form = STATIC_SYMBOL("WRITE-FORMAT-FORM",AB_package);
    mutate_global_property(Qformat_form,Qwrite_format_form,
	    Qevaluator_form_writer);
    Qg2_list_or_sequence_length = 
	    STATIC_SYMBOL("G2-LIST-OR-SEQUENCE-LENGTH",AB_package);
    Qwrite_g2_list_or_sequence_length = 
	    STATIC_SYMBOL("WRITE-G2-LIST-OR-SEQUENCE-LENGTH",AB_package);
    mutate_global_property(Qg2_list_or_sequence_length,
	    Qwrite_g2_list_or_sequence_length,Qevaluator_form_writer);
    Qnetwork_interface_for = STATIC_SYMBOL("NETWORK-INTERFACE-FOR",AB_package);
    Qwrite_network_interface_for = 
	    STATIC_SYMBOL("WRITE-NETWORK-INTERFACE-FOR",AB_package);
    mutate_global_property(Qnetwork_interface_for,
	    Qwrite_network_interface_for,Qevaluator_form_writer);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qwrite_let = STATIC_SYMBOL("WRITE-LET",AB_package);
    mutate_global_property(Qab_let,Qwrite_let,Qevaluator_form_writer);
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    Qwrite_new_quantified_form = STATIC_SYMBOL("WRITE-NEW-QUANTIFIED-FORM",
	    AB_package);
    mutate_global_property(Qthere_exists_literal,
	    Qwrite_new_quantified_form,Qevaluator_form_writer);
    Qfor_every_literal = STATIC_SYMBOL("FOR-EVERY-LITERAL",AB_package);
    mutate_global_property(Qfor_every_literal,Qwrite_new_quantified_form,
	    Qevaluator_form_writer);
    Qsum = STATIC_SYMBOL("SUM",AB_package);
    Qwrite_aggregator = STATIC_SYMBOL("WRITE-AGGREGATOR",AB_package);
    mutate_global_property(Qsum,Qwrite_aggregator,Qevaluator_form_writer);
    Qproduct = STATIC_SYMBOL("PRODUCT",AB_package);
    mutate_global_property(Qproduct,Qwrite_aggregator,Qevaluator_form_writer);
    Qaggregated_average = STATIC_SYMBOL("AGGREGATED-AVERAGE",AB_package);
    mutate_global_property(Qaggregated_average,Qwrite_aggregator,
	    Qevaluator_form_writer);
    Qmaximum = STATIC_SYMBOL("MAXIMUM",AB_package);
    mutate_global_property(Qmaximum,Qwrite_aggregator,Qevaluator_form_writer);
    Qminimum = STATIC_SYMBOL("MINIMUM",AB_package);
    mutate_global_property(Qminimum,Qwrite_aggregator,Qevaluator_form_writer);
    mutate_global_property(Qcount,Qwrite_aggregator,Qevaluator_form_writer);
    string_constant_17 = STATIC_STRING(" < ");
    string_constant_18 = STATIC_STRING(" > ");
    string_constant_19 = STATIC_STRING(" = ");
    string_constant_20 = STATIC_STRING(" /= ");
    string_constant_21 = STATIC_STRING(" (+- ");
    string_constant_22 = STATIC_STRING(")");
    SET_SYMBOL_FUNCTION(Qfuzzy_writer,STATIC_FUNCTION(fuzzy_writer,NIL,
	    FALSE,1,1));
    string_constant_23 = STATIC_STRING(" is more true than ");
    string_constant_24 = STATIC_STRING(" is not more true than ");
    string_constant_25 = STATIC_STRING(" is less true than ");
    string_constant_26 = STATIC_STRING(" is not less true than ");
    string_constant_27 = STATIC_STRING(" \?\?\? ");
    SET_SYMBOL_FUNCTION(Qfuzzy_logic_comparitor_writer,
	    STATIC_FUNCTION(fuzzy_logic_comparitor_writer,NIL,FALSE,1,1));
    string_constant_28 = STATIC_STRING("the value of ");
    string_constant_29 = STATIC_STRING(" is false");
    string_constant_30 = STATIC_STRING("the current value of ");
    SET_SYMBOL_FUNCTION(Qfalse_writer,STATIC_FUNCTION(false_writer,NIL,
	    FALSE,1,1));
    string_constant_31 = STATIC_STRING("the symbol ~(~a~)");
    SET_SYMBOL_FUNCTION(Qquote_expression_writer,
	    STATIC_FUNCTION(quote_expression_writer,NIL,FALSE,1,1));
    string_constant_32 = STATIC_STRING("(if ");
    string_constant_33 = STATIC_STRING(" then ");
    string_constant_34 = STATIC_STRING(" else ");
    SET_SYMBOL_FUNCTION(Qif_expression_writer,
	    STATIC_FUNCTION(if_expression_writer,NIL,FALSE,1,1));
    string_constant_35 = STATIC_STRING("the interpolated value ");
    string_constant_36 = STATIC_STRING("the value ");
    string_constant_37 = STATIC_STRING("the collection time ");
    string_constant_38 = STATIC_STRING("the maximum value");
    string_constant_39 = STATIC_STRING("the minimum value ");
    string_constant_40 = STATIC_STRING("the average value ");
    string_constant_41 = STATIC_STRING("the sum of the values ");
    string_constant_42 = STATIC_STRING("the standard deviation ");
    string_constant_43 = STATIC_STRING("the integral ");
    string_constant_44 = STATIC_STRING("the rate of change ");
    string_constant_45 = STATIC_STRING("the unknown function ");
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qintegral,Qrate_of_change);
    string_constant_46 = STATIC_STRING("in ");
    string_constant_47 = STATIC_STRING(" of ");
    string_constant_48 = STATIC_STRING("per ");
    string_constant_49 = STATIC_STRING("of ");
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qvalue_of_previous_datapoint,
	    Qcollection_time_of_previous_datapoint);
    string_constant_50 = STATIC_STRING(" as of ");
    string_constant_51 = STATIC_STRING(" datapoints ago");
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    string_constant_52 = STATIC_STRING(" during the ");
    string_constant_53 = STATIC_STRING(" ending with the collection time");
    string_constant_54 = STATIC_STRING(" between ");
    string_constant_55 = STATIC_STRING(" ago and ");
    string_constant_56 = STATIC_STRING(" ago");
    string_constant_57 = STATIC_STRING(" during the last ");
    SET_SYMBOL_FUNCTION(Qhistoric_function_writer,
	    STATIC_FUNCTION(historic_function_writer,NIL,FALSE,1,1));
    string_constant_58 = STATIC_STRING(" has a value");
    string_constant_59 = STATIC_STRING(" has no value");
    string_constant_60 = STATIC_STRING(" has a current value");
    string_constant_61 = STATIC_STRING(" has-no-current-value");
    string_constant_62 = STATIC_STRING(" receives a value");
    string_constant_63 = STATIC_STRING(" fails to receive a value");
    string_constant_64 = STATIC_STRING(" is moved");
    string_constant_65 = STATIC_STRING(" is moved by the user");
    string_constant_66 = STATIC_STRING(" is moved by G2");
    string_constant_67 = STATIC_STRING(" is resized by the user");
    string_constant_68 = STATIC_STRING(" has a name");
    string_constant_69 = STATIC_STRING(" has no name");
    SET_SYMBOL_FUNCTION(Qpostfix_writer,STATIC_FUNCTION(postfix_writer,NIL,
	    FALSE,1,1));
    string_constant_70 = STATIC_STRING("the expiration time of ");
    string_constant_71 = STATIC_STRING("the collection time of ");
    SET_SYMBOL_FUNCTION(Qprefix_writer,STATIC_FUNCTION(prefix_writer,NIL,
	    FALSE,1,1));
    string_constant_72 = STATIC_STRING(" is ");
    string_constant_73 = STATIC_STRING(" is not ");
    SET_SYMBOL_FUNCTION(Qwrite_is,STATIC_FUNCTION(write_is,NIL,FALSE,1,1));
    array_constant_5 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qattribute_name_function_writer,
	    STATIC_FUNCTION(attribute_name_function_writer,NIL,FALSE,1,1));
    array_constant_6 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qwrite_the_current_time,
	    STATIC_FUNCTION(write_the_current_time,NIL,FALSE,1,1));
    array_constant_7 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qwrite_the_current_real_time,
	    STATIC_FUNCTION(write_the_current_real_time,NIL,FALSE,1,1));
    array_constant_8 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qwrite_the_current_subsecond_time,
	    STATIC_FUNCTION(write_the_current_subsecond_time,NIL,FALSE,1,1));
    Qbecomes = STATIC_SYMBOL("BECOMES",AB_package);
    string_constant_74 = STATIC_STRING(" becomes ");
    string_constant_75 = STATIC_STRING(" ceases to be ");
    SET_SYMBOL_FUNCTION(Qwrite_relation_event_literal,
	    STATIC_FUNCTION(write_relation_event_literal,NIL,FALSE,1,1));
    string_constant_76 = STATIC_STRING(" has a ");
    string_constant_77 = STATIC_STRING(" event");
    SET_SYMBOL_FUNCTION(Qwrite_generic_event_literal,
	    STATIC_FUNCTION(write_generic_event_literal,NIL,FALSE,1,1));
    array_constant_9 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qwrite_nupec_synchronization_occurs,
	    STATIC_FUNCTION(write_nupec_synchronization_occurs,NIL,FALSE,1,1));
    string_constant_78 = STATIC_STRING("the distance between ");
    string_constant_79 = STATIC_STRING(" and ");
    SET_SYMBOL_FUNCTION(Qwrite_in_binary_role_style,
	    STATIC_FUNCTION(write_in_binary_role_style,NIL,FALSE,1,1));
    array_constant_10 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)57344L);
    string_constant_80 = STATIC_STRING(" and the nearest ~(~a~)");
    SET_SYMBOL_FUNCTION(Qwrite_distance_between_and_the_nearest,
	    STATIC_FUNCTION(write_distance_between_and_the_nearest,NIL,
	    FALSE,1,1));
    string_constant_81 = STATIC_STRING(" is the same object as ");
    string_constant_82 = STATIC_STRING(" is not the same object as ");
    SET_SYMBOL_FUNCTION(Qwrite_same_as,STATIC_FUNCTION(write_same_as,NIL,
	    FALSE,1,1));
    string_constant_83 = STATIC_STRING("an instance of the class named by (");
    SET_SYMBOL_FUNCTION(Qwrite_is_a,STATIC_FUNCTION(write_is_a,NIL,FALSE,1,1));
    string_constant_84 = STATIC_STRING(" has been activated");
    string_constant_85 = STATIC_STRING(" has not been activated");
    SET_SYMBOL_FUNCTION(Qwrite_is_active,STATIC_FUNCTION(write_is_active,
	    NIL,FALSE,1,1));
    string_constant_86 = STATIC_STRING("the ");
    SET_SYMBOL_FUNCTION(Qwrite_as_if_role,STATIC_FUNCTION(write_as_if_role,
	    NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qrelation_writer,STATIC_FUNCTION(relation_writer,
	    NIL,FALSE,1,1));
    Qdq = STATIC_SYMBOL("\"",AB_package);
    Qobt = STATIC_SYMBOL("[",AB_package);
    Qcbt = STATIC_SYMBOL("]",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_format_form,
	    STATIC_FUNCTION(write_format_form,NIL,FALSE,1,1));
    string_constant_87 = STATIC_STRING("the number of elements in ");
    SET_SYMBOL_FUNCTION(Qwrite_g2_list_or_sequence_length,
	    STATIC_FUNCTION(write_g2_list_or_sequence_length,NIL,FALSE,1,1));
    string_constant_88 = STATIC_STRING("the network interface for ");
    SET_SYMBOL_FUNCTION(Qwrite_network_interface_for,
	    STATIC_FUNCTION(write_network_interface_for,NIL,FALSE,1,1));
    Qop = STATIC_SYMBOL("(",AB_package);
    string_constant_89 = STATIC_STRING(" where ");
    string_constant_90 = STATIC_STRING("; ");
    Qcp = STATIC_SYMBOL(")",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_let,STATIC_FUNCTION(write_let,NIL,FALSE,1,1));
    string_constant_91 = STATIC_STRING("the ~(~a~) over each ");
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qwrite_aggregator,STATIC_FUNCTION(write_aggregator,
	    NIL,FALSE,1,1));
    string_constant_92 = STATIC_STRING("there exists ");
    string_constant_93 = STATIC_STRING("for every ");
    string_constant_94 = STATIC_STRING(" such that (");
    string_constant_95 = STATIC_STRING(" (");
    SET_SYMBOL_FUNCTION(Qwrite_new_quantified_form,
	    STATIC_FUNCTION(write_new_quantified_form,NIL,FALSE,1,1));
    string_constant_96 = 
	    STATIC_STRING("A number was computed that is too big to store in ~\n                      floating point format.  It was ~A, and ~D is being ~\n                      stored instead.");
    string_constant_97 = STATIC_STRING("negative");
    string_constant_98 = STATIC_STRING("positive");
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    string_constant_99 = STATIC_STRING("The preceding occurred within ~NF.");
}
