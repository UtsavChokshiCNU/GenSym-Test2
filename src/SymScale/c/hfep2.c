/* hfep2.c
 * Input file:  hfep2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "hfep2.h"


DEFINE_VARIABLE_WITH_SYMBOL(Hfep_state, Qhfep_state);

DEFINE_VARIABLE_WITH_SYMBOL(Hfep_action, Qhfep_action);

DEFINE_VARIABLE_WITH_SYMBOL(Hfep_cho_ksc2c, Qhfep_cho_ksc2c);

DEFINE_VARIABLE_WITH_SYMBOL(Hfep_jung_ksc2c, Qhfep_jung_ksc2c);

DEFINE_VARIABLE_WITH_SYMBOL(Hfep_jong_ksc2c, Qhfep_jong_ksc2c);

Object The_type_description_of_hfep_hanc_type = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_hfep_hanc_types, Qchain_of_available_hfep_hanc_types);

DEFINE_VARIABLE_WITH_SYMBOL(Hfep_hanc_type_count, Qhfep_hanc_type_count);

Object Chain_of_available_hfep_hanc_types_vector = UNBOUND;

/* HFEP-HANC-TYPE-STRUCTURE-MEMORY-USAGE */
Object hfep_hanc_type_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(124,0);
    temp = Hfep_hanc_type_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-HFEP-HANC-TYPE-COUNT */
Object outstanding_hfep_hanc_type_count()
{
    Object def_structure_hfep_hanc_type_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(124,1);
    gensymed_symbol = IFIX(Hfep_hanc_type_count);
    def_structure_hfep_hanc_type_variable = Chain_of_available_hfep_hanc_types;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_hfep_hanc_type_variable))
	goto end_loop;
    def_structure_hfep_hanc_type_variable = 
	    ISVREF(def_structure_hfep_hanc_type_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-HFEP-HANC-TYPE-1 */
Object reclaim_hfep_hanc_type_1(hfep_hanc_type)
    Object hfep_hanc_type;
{
    Object temp, svref_arg_2;

    x_note_fn_call(124,2);
    inline_note_reclaim_cons(hfep_hanc_type,Nil);
    temp = ISVREF(Chain_of_available_hfep_hanc_types_vector,
	    IFIX(Current_thread_index));
    SVREF(hfep_hanc_type,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_hfep_hanc_types_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = hfep_hanc_type;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-HFEP-HANC-TYPE */
Object reclaim_structure_for_hfep_hanc_type(hfep_hanc_type)
    Object hfep_hanc_type;
{
    x_note_fn_call(124,3);
    return reclaim_hfep_hanc_type_1(hfep_hanc_type);
}

static Object Qg2_defstruct_structure_name_hfep_hanc_type_g2_struct;  /* g2-defstruct-structure-name::hfep-hanc-type-g2-struct */

/* MAKE-PERMANENT-HFEP-HANC-TYPE-STRUCTURE-INTERNAL */
Object make_permanent_hfep_hanc_type_structure_internal()
{
    Object def_structure_hfep_hanc_type_variable;
    Object defstruct_g2_hfep_hanc_type_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(124,4);
    def_structure_hfep_hanc_type_variable = Nil;
    atomic_incff_symval(Qhfep_hanc_type_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_hfep_hanc_type_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
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
	defstruct_g2_hfep_hanc_type_variable = the_array;
	SVREF(defstruct_g2_hfep_hanc_type_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_hfep_hanc_type_g2_struct;
	def_structure_hfep_hanc_type_variable = 
		defstruct_g2_hfep_hanc_type_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_hfep_hanc_type_variable);
}

/* MAKE-HFEP-HANC-TYPE-1 */
Object make_hfep_hanc_type_1()
{
    Object def_structure_hfep_hanc_type_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(124,5);
    def_structure_hfep_hanc_type_variable = 
	    ISVREF(Chain_of_available_hfep_hanc_types_vector,
	    IFIX(Current_thread_index));
    if (def_structure_hfep_hanc_type_variable) {
	svref_arg_1 = Chain_of_available_hfep_hanc_types_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_hfep_hanc_type_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_hfep_hanc_type_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_hfep_hanc_type_g2_struct;
    }
    else
	def_structure_hfep_hanc_type_variable = 
		make_permanent_hfep_hanc_type_structure_internal();
    inline_note_allocate_cons(def_structure_hfep_hanc_type_variable,Nil);
    return VALUES_1(def_structure_hfep_hanc_type_variable);
}

/* MAKE-HFEP-HANC-TYPE-FUNCTION */
Object make_hfep_hanc_type_function()
{
    x_note_fn_call(124,6);
    return make_hfep_hanc_type_1();
}

/* RECLAIM-HFEP-HANC-TYPE-FUNCTION */
Object reclaim_hfep_hanc_type_function(hfep_hanc_type)
    Object hfep_hanc_type;
{
    x_note_fn_call(124,7);
    return reclaim_hfep_hanc_type_1(hfep_hanc_type);
}

/* RESET-HFEP-HANC-TYPE-INSTANCE */
Object reset_hfep_hanc_type_instance(hanc_type)
    Object hanc_type;
{
    x_note_fn_call(124,8);
    SVREF(hanc_type,FIX((SI_Long)1L)) = Hfep_none;
    SVREF(hanc_type,FIX((SI_Long)2L)) = Hfep_null;
    SVREF(hanc_type,FIX((SI_Long)3L)) = Hfep_null;
    SVREF(hanc_type,FIX((SI_Long)4L)) = Hfep_null;
    SVREF(hanc_type,FIX((SI_Long)5L)) = Hfep_null;
    SVREF(hanc_type,FIX((SI_Long)6L)) = Hfep_null_code;
    return VALUES_1(SVREF(hanc_type,FIX((SI_Long)7L)) = Hfep_null_code);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_hfep_cchar, Qcurrent_hfep_cchar);

DEFINE_VARIABLE_WITH_SYMBOL(Current_hfep_nchar, Qcurrent_hfep_nchar);

DEFINE_VARIABLE_WITH_SYMBOL(Current_hfep_c_state, Qcurrent_hfep_c_state);

DEFINE_VARIABLE_WITH_SYMBOL(Current_hfep_c_act, Qcurrent_hfep_c_act);

/* SHIFT-HFEP-CCHAR-TO-NCHAR-AND-RESET-CCHAR */
Object shift_hfep_cchar_to_nchar_and_reset_cchar()
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(124,9);
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = ISVREF(Current_hfep_nchar,(SI_Long)1L);
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = svref_new_value;
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = ISVREF(Current_hfep_nchar,(SI_Long)2L);
    SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = ISVREF(Current_hfep_nchar,(SI_Long)3L);
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = ISVREF(Current_hfep_nchar,(SI_Long)4L);
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = ISVREF(Current_hfep_nchar,(SI_Long)5L);
    SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = ISVREF(Current_hfep_nchar,(SI_Long)6L);
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = ISVREF(Current_hfep_nchar,(SI_Long)7L);
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
    return reset_hfep_hanc_type_instance(Current_hfep_nchar);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "CG~c~c" */

static Object string_constant_1;   /* "CD~c~c" */

static Object string_constant_2;   /* "NW~c~c" */

static Object string_constant_3;   /* "NN~c~c" */

static Object string_constant_4;   /* "NE~c~c" */

static Object string_constant_5;   /* "CW~c~c" */

static Object string_constant_6;   /* "NG~c~c" */

static Object string_constant_7;   /* "CF~c~c" */

static Object string_constant_8;   /* "NF~c~c" */

/* RUN-HFEP-AUTOMATON */
Object run_hfep_automaton(input_string)
    Object input_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, svref_arg_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, temp;
    SI_Long gensymed_symbol;
    Declare_special(5);
    Object result;

    x_note_fn_call(124,10);
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
	      temp = UBYTE_16_ISAREF_1(input_string,(SI_Long)0L);
	      if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L)) {
		  hfep_into_hanc(FIX(UBYTE_16_ISAREF_1(input_string,
			  (SI_Long)1L)));
		  temp_1 = ISVREF(Current_hfep_cchar,(SI_Long)1L);
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 0:
			case 1:
			  temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
				  (SI_Long)7L)) >>  -  - (SI_Long)8L);
			  gensymed_symbol = (SI_Long)255L & 
				  IFIX(ISVREF(Current_hfep_cchar,(SI_Long)7L));
			  tformat(3,string_constant,temp_1,
				  FIX(gensymed_symbol));
			  break;
			case 2:
			  temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
				  (SI_Long)7L)) >>  -  - (SI_Long)8L);
			  gensymed_symbol = (SI_Long)255L & 
				  IFIX(ISVREF(Current_hfep_cchar,(SI_Long)7L));
			  tformat(3,string_constant_1,temp_1,
				  FIX(gensymed_symbol));
			  temp_1 = ISVREF(Current_hfep_nchar,(SI_Long)1L);
			  if (! !(FIXNUMP(temp_1) && 
				  FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				  FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			      switch (INTEGER_TO_CHAR(temp_1)) {
				case 1:
				case 3:
				  temp_1 = 
					  FIX(IFIX(ISVREF(Current_hfep_nchar,
					  (SI_Long)7L)) >>  -  - (SI_Long)8L);
				  gensymed_symbol = (SI_Long)255L & 
					  IFIX(ISVREF(Current_hfep_nchar,
					  (SI_Long)7L));
				  tformat(3,string_constant_2,temp_1,
					  FIX(gensymed_symbol));
				  shift_hfep_cchar_to_nchar_and_reset_cchar();
				  break;
				case 0:
				  temp_1 = 
					  FIX(IFIX(ISVREF(Current_hfep_nchar,
					  (SI_Long)7L)) >>  -  - (SI_Long)8L);
				  gensymed_symbol = (SI_Long)255L & 
					  IFIX(ISVREF(Current_hfep_nchar,
					  (SI_Long)7L));
				  tformat(3,string_constant_3,temp_1,
					  FIX(gensymed_symbol));
				  shift_hfep_cchar_to_nchar_and_reset_cchar();
				  break;
				case 4:
				  temp_1 = 
					  FIX(IFIX(ISVREF(Current_hfep_nchar,
					  (SI_Long)7L)) >>  -  - (SI_Long)8L);
				  gensymed_symbol = (SI_Long)255L & 
					  IFIX(ISVREF(Current_hfep_nchar,
					  (SI_Long)7L));
				  tformat(3,string_constant_4,temp_1,
					  FIX(gensymed_symbol));
				  shift_hfep_cchar_to_nchar_and_reset_cchar();
				  svref_arg_1 = Current_hfep_cchar;
				  SVREF(svref_arg_1,FIX((SI_Long)1L)) = 
					  Hfep_done;
				  break;
				default:
				  break;
			      }
			  break;
			case 3:
			  temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
				  (SI_Long)7L)) >>  -  - (SI_Long)8L);
			  gensymed_symbol = (SI_Long)255L & 
				  IFIX(ISVREF(Current_hfep_cchar,(SI_Long)7L));
			  tformat(3,string_constant_5,temp_1,
				  FIX(gensymed_symbol));
			  shift_hfep_cchar_to_nchar_and_reset_cchar();
			  break;
			case 4:
			  temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
				  (SI_Long)7L)) >>  -  - (SI_Long)8L);
			  gensymed_symbol = (SI_Long)255L & 
				  IFIX(ISVREF(Current_hfep_cchar,(SI_Long)7L));
			  tformat(3,string_constant_5,temp_1,
				  FIX(gensymed_symbol));
			  if (EQ(ISVREF(Current_hfep_nchar,(SI_Long)1L),
				  FIX((SI_Long)1L))) {
			      temp_1 = FIX(IFIX(ISVREF(Current_hfep_nchar,
				      (SI_Long)7L)) >>  -  - (SI_Long)8L);
			      gensymed_symbol = (SI_Long)255L & 
				      IFIX(ISVREF(Current_hfep_nchar,
				      (SI_Long)7L));
			      tformat(3,string_constant_6,temp_1,
				      FIX(gensymed_symbol));
			      shift_hfep_cchar_to_nchar_and_reset_cchar();
			  }
			  break;
			default:
			  break;
		      }
	      }
	      else
		  switch ((char)temp) {
		    case 82:
		      Current_hfep_c_state = FIX((SI_Long)0L);
		      Current_hfep_c_act = FIX((SI_Long)0L);
		      reset_hfep_hanc_type_instance(Current_hfep_cchar);
		      reset_hfep_hanc_type_instance(Current_hfep_nchar);
		      break;
		    case 70:
		      temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
			      (SI_Long)7L)) >>  -  - (SI_Long)8L);
		      gensymed_symbol = (SI_Long)255L & 
			      IFIX(ISVREF(Current_hfep_cchar,(SI_Long)7L));
		      tformat(3,string_constant_7,temp_1,FIX(gensymed_symbol));
		      temp_1 = FIX(IFIX(ISVREF(Current_hfep_nchar,
			      (SI_Long)7L)) >>  -  - (SI_Long)8L);
		      gensymed_symbol = (SI_Long)255L & 
			      IFIX(ISVREF(Current_hfep_nchar,(SI_Long)7L));
		      tformat(3,string_constant_8,temp_1,FIX(gensymed_symbol));
		      Current_hfep_c_state = FIX((SI_Long)0L);
		      Current_hfep_c_act = FIX((SI_Long)0L);
		      reset_hfep_hanc_type_instance(Current_hfep_cchar);
		      reset_hfep_hanc_type_instance(Current_hfep_nchar);
		      break;
		    default:
		      hfep_into_hanc(FIX(UBYTE_16_ISAREF_1(input_string,
			      (SI_Long)1L)));
		      temp_1 = ISVREF(Current_hfep_cchar,(SI_Long)1L);
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 0:
			    case 1:
			      temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
				      (SI_Long)7L)) >>  -  - (SI_Long)8L);
			      gensymed_symbol = (SI_Long)255L & 
				      IFIX(ISVREF(Current_hfep_cchar,
				      (SI_Long)7L));
			      tformat(3,string_constant,temp_1,
				      FIX(gensymed_symbol));
			      break;
			    case 2:
			      temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
				      (SI_Long)7L)) >>  -  - (SI_Long)8L);
			      gensymed_symbol = (SI_Long)255L & 
				      IFIX(ISVREF(Current_hfep_cchar,
				      (SI_Long)7L));
			      tformat(3,string_constant_1,temp_1,
				      FIX(gensymed_symbol));
			      temp_1 = ISVREF(Current_hfep_nchar,(SI_Long)1L);
			      if (! !(FIXNUMP(temp_1) && 
				      FIXNUM_LE(FIX((SI_Long)-128L),
				      temp_1) && FIXNUM_LE(temp_1,
				      FIX((SI_Long)127L))))
				  switch (INTEGER_TO_CHAR(temp_1)) {
				    case 1:
				    case 3:
				      temp_1 = 
					      FIX(IFIX(ISVREF(Current_hfep_nchar,
					      (SI_Long)7L)) >>  -  - 
					      (SI_Long)8L);
				      gensymed_symbol = (SI_Long)255L & 
					      IFIX(ISVREF(Current_hfep_nchar,
					      (SI_Long)7L));
				      tformat(3,string_constant_2,temp_1,
					      FIX(gensymed_symbol));
				      shift_hfep_cchar_to_nchar_and_reset_cchar();
				      break;
				    case 0:
				      temp_1 = 
					      FIX(IFIX(ISVREF(Current_hfep_nchar,
					      (SI_Long)7L)) >>  -  - 
					      (SI_Long)8L);
				      gensymed_symbol = (SI_Long)255L & 
					      IFIX(ISVREF(Current_hfep_nchar,
					      (SI_Long)7L));
				      tformat(3,string_constant_3,temp_1,
					      FIX(gensymed_symbol));
				      shift_hfep_cchar_to_nchar_and_reset_cchar();
				      break;
				    case 4:
				      temp_1 = 
					      FIX(IFIX(ISVREF(Current_hfep_nchar,
					      (SI_Long)7L)) >>  -  - 
					      (SI_Long)8L);
				      gensymed_symbol = (SI_Long)255L & 
					      IFIX(ISVREF(Current_hfep_nchar,
					      (SI_Long)7L));
				      tformat(3,string_constant_4,temp_1,
					      FIX(gensymed_symbol));
				      shift_hfep_cchar_to_nchar_and_reset_cchar();
				      svref_arg_1 = Current_hfep_cchar;
				      SVREF(svref_arg_1,FIX((SI_Long)1L)) 
					      = Hfep_done;
				      break;
				    default:
				      break;
				  }
			      break;
			    case 3:
			      temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
				      (SI_Long)7L)) >>  -  - (SI_Long)8L);
			      gensymed_symbol = (SI_Long)255L & 
				      IFIX(ISVREF(Current_hfep_cchar,
				      (SI_Long)7L));
			      tformat(3,string_constant_5,temp_1,
				      FIX(gensymed_symbol));
			      shift_hfep_cchar_to_nchar_and_reset_cchar();
			      break;
			    case 4:
			      temp_1 = FIX(IFIX(ISVREF(Current_hfep_cchar,
				      (SI_Long)7L)) >>  -  - (SI_Long)8L);
			      gensymed_symbol = (SI_Long)255L & 
				      IFIX(ISVREF(Current_hfep_cchar,
				      (SI_Long)7L));
			      tformat(3,string_constant_5,temp_1,
				      FIX(gensymed_symbol));
			      if (EQ(ISVREF(Current_hfep_nchar,
				      (SI_Long)1L),FIX((SI_Long)1L))) {
				  temp_1 = 
					  FIX(IFIX(ISVREF(Current_hfep_nchar,
					  (SI_Long)7L)) >>  -  - (SI_Long)8L);
				  gensymed_symbol = (SI_Long)255L & 
					  IFIX(ISVREF(Current_hfep_nchar,
					  (SI_Long)7L));
				  tformat(3,string_constant_6,temp_1,
					  FIX(gensymed_symbol));
				  shift_hfep_cchar_to_nchar_and_reset_cchar();
			      }
			      break;
			    default:
			      break;
			  }
		      break;
		  }
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* HFEP-INTO-HANC */
Object hfep_into_hanc(c)
    Object c;
{
    Object temp, temp_1, temp_2, svref_arg_1, svref_new_value;

    x_note_fn_call(124,11);
    temp = Nil;
    temp_1 = Hfep_action;
    temp_2 = Current_hfep_c_state;
    temp = hfep_chgroup(c);
    Current_hfep_c_act = aref2(temp_1,temp_2,temp);
    Current_hfep_c_state = aref2(Hfep_state,Current_hfep_c_state,temp);
    if (! !(FIXNUMP(Current_hfep_c_act) && FIXNUM_LE(FIX((SI_Long)-128L),
	    Current_hfep_c_act) && FIXNUM_LE(Current_hfep_c_act,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(Current_hfep_c_act)) {
	  case -2:
	    reset_hfep_hanc_type_instance(Current_hfep_cchar);
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_wrong;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = c;
	    reset_hfep_hanc_type_instance(Current_hfep_nchar);
	    break;
	  case -1:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_done;
	    reset_hfep_hanc_type_instance(Current_hfep_nchar);
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_wrong;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = c;
	    break;
	  case 0:
	    reset_hfep_hanc_type_instance(Current_hfep_cchar);
	    reset_hfep_hanc_type_instance(Current_hfep_nchar);
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = c;
	    break;
	  case 1:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_error;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = Hfep_null;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = c;
	    break;
	  case 2:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = c;
	    break;
	  case 3:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_cchar;
	    svref_new_value = hfep_mixvowel(ISVREF(Current_hfep_cchar,
		    (SI_Long)3L),c);
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
	    break;
	  case 4:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)4L)) = c;
	    break;
	  case 5:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)4L)) = c;
	    break;
	  case 6:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)5L)) = c;
	    break;
	  case 7:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_done;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = c;
	    break;
	  case 8:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_done;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = c;
	    break;
	  case 9:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_done;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_nchar;
	    svref_new_value = ISVREF(Current_hfep_cchar,(SI_Long)4L);
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)4L)) = Hfep_null;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = c;
	    break;
	  case 10:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_done;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_nchar;
	    svref_new_value = ISVREF(Current_hfep_cchar,(SI_Long)5L);
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)5L)) = Hfep_null;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = c;
	    break;
	  case 11:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_done;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_error;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = c;
	    break;
	  case 12:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_error;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = c;
	    break;
	  case 13:
	    svref_arg_1 = Current_hfep_cchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_done;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Hfep_go_on;
	    svref_arg_1 = Current_hfep_nchar;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = c;
	    break;
	  default:
	    break;
	}
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = hfep_intoksc2c(ISVREF(Current_hfep_cchar,
	    (SI_Long)2L),ISVREF(Current_hfep_cchar,(SI_Long)3L),
	    ISVREF(Current_hfep_cchar,(SI_Long)4L),
	    ISVREF(Current_hfep_cchar,(SI_Long)5L));
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
    svref_arg_1 = Current_hfep_cchar;
    svref_new_value = hfep_intoksc2s(ISVREF(Current_hfep_cchar,(SI_Long)6L));
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
    if ( !EQ(ISVREF(Current_hfep_nchar,(SI_Long)1L),FIX((SI_Long)0L))) {
	svref_arg_1 = Current_hfep_nchar;
	svref_new_value = hfep_intoksc2c(ISVREF(Current_hfep_nchar,
		(SI_Long)2L),ISVREF(Current_hfep_nchar,(SI_Long)3L),
		ISVREF(Current_hfep_nchar,(SI_Long)4L),
		ISVREF(Current_hfep_nchar,(SI_Long)5L));
	SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
	svref_arg_1 = Current_hfep_nchar;
	svref_new_value = hfep_intoksc2s(ISVREF(Current_hfep_nchar,
		(SI_Long)6L));
	return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value);
    }
    else {
	svref_arg_1 = Current_hfep_nchar;
	SVREF(svref_arg_1,FIX((SI_Long)6L)) = Hfep_null_code;
	svref_arg_1 = Current_hfep_nchar;
	return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)7L)) = Hfep_null_code);
    }
}

/* HFEP-INTOKSC2C */
Object hfep_intoksc2c(c1,c2,c3,c4)
    Object c1, c2, c3, c4;
{
    Object i1, i2, i3, i4, temp;

    x_note_fn_call(124,12);
    i1 = FIX((SI_Long)41984L);
    i2 = FIX((SI_Long)512L);
    i3 = FIX((SI_Long)1L);
    i4 = Nil;
    if (IFIX(c1) >= (SI_Long)65L && IFIX(c1) <= (SI_Long)122L)
	i1 = ISVREF(Hfep_cho_ksc2c,IFIX(c1) - (SI_Long)65L);
    if (FIXNUM_NE(c1,Hfep_null) && IFIX(i1) == (SI_Long)41984L)
	return VALUES_1(c1);
    else {
	if (FIXNUM_NE(c2,Hfep_null))
	    i2 = ISVREF(Hfep_jung_ksc2c,IFIX(c2) - (SI_Long)65L);
	else
	    i2 = FIX((SI_Long)512L);
	if (FIXNUM_NE(c3,Hfep_null)) {
	    temp = Hfep_jong_ksc2c;
	    i3 = ISVREF(temp,IFIX(hfep_mixconso(c3,c4)) - (SI_Long)65L);
	}
	else
	    i3 = FIX((SI_Long)1L);
	i4 = logxorn(3,i1,i2,i3);
	return VALUES_1(i4);
    }
}

/* HFEP-INTOKSC2S */
Object hfep_intoksc2s(key)
    Object key;
{
    Object l, u_1, m, tmp;

    x_note_fn_call(124,13);
    l = FIX((SI_Long)0L);
    u_1 = FIXNUM_SUB1(Hfep_ks_size);
    m = Nil;
    tmp = Nil;
  next_loop:
    if ( !FIXNUM_LE(l,u_1))
	goto end_loop;
    m = FIX(IFIX(FIXNUM_ADD(l,u_1)) >>  -  - (SI_Long)1L);
    tmp = aref1(Hfep_ksc2cs,FIX(IFIX(m) * (SI_Long)2L));
    if (FIXNUM_GT(key,tmp))
	l = FIXNUM_ADD1(m);
    else if (FIXNUM_EQ(key,tmp))
	return aref1(Hfep_ksc2cs,FIX(IFIX(m) * (SI_Long)2L + (SI_Long)1L));
    else if (FIXNUM_LT(key,tmp))
	u_1 = FIXNUM_SUB1(m);
    goto next_loop;
  end_loop:
    return VALUES_1(key);
    return VALUES_1(Qnil);
}

/* HFEP-CHGROUP */
Object hfep_chgroup(c)
    Object c;
{
    Object temp;

    x_note_fn_call(124,14);
    temp = c;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	return VALUES_1(FIX((SI_Long)16L));
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 114:
	  case 113:
	    return VALUES_1(FIX((SI_Long)0L));
	  case 115:
	    return VALUES_1(FIX((SI_Long)1L));
	  case 102:
	    return VALUES_1(FIX((SI_Long)2L));
	  case 116:
	    return VALUES_1(FIX((SI_Long)3L));
	  case 119:
	    return VALUES_1(FIX((SI_Long)4L));
	  case 103:
	    return VALUES_1(FIX((SI_Long)5L));
	  case 69:
	  case 81:
	  case 87:
	    return VALUES_1(FIX((SI_Long)6L));
	  case 97:
	  case 120:
	  case 118:
	    return VALUES_1(FIX((SI_Long)7L));
	  case 82:
	  case 101:
	  case 84:
	  case 100:
	  case 99:
	  case 122:
	    return VALUES_1(FIX((SI_Long)8L));
	  case 104:
	    return VALUES_1(FIX((SI_Long)9L));
	  case 110:
	    return VALUES_1(FIX((SI_Long)10L));
	  case 109:
	    return VALUES_1(FIX((SI_Long)11L));
	  case 107:
	  case 111:
	    return VALUES_1(FIX((SI_Long)12L));
	  case 106:
	  case 112:
	    return VALUES_1(FIX((SI_Long)13L));
	  case 108:
	    return VALUES_1(FIX((SI_Long)14L));
	  case 105:
	  case 117:
	  case 98:
	  case 79:
	  case 80:
	  case 121:
	    return VALUES_1(FIX((SI_Long)15L));
	  case 75:
	  case 74:
	  case 72:
	  case 78:
	  case 77:
	  case 76:
	  case 66:
	    return VALUES_1(FIX((SI_Long)15L));
	  default:
	    return VALUES_1(FIX((SI_Long)16L));
	}
}

/* HFEP-MIXVOWEL */
Object hfep_mixvowel(c1,c2)
    Object c1, c2;
{
    Object c, temp;

    x_note_fn_call(124,15);
    c = c1;
    if (FIXNUM_NE(c1,Hfep_o) && FIXNUM_NE(c1,Hfep_u) && FIXNUM_NE(c1,
		Hfep_eu)) {
	c = c1;
	c1 = c2;
	c2 = c;
    }
    temp = c1;
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 104:
	    if (FIXNUM_EQ(c2,Hfep_a))
		c = Hfep_o_a;
	    if (FIXNUM_EQ(c2,Hfep_ai))
		c = Hfep_o_ai;
	    if (FIXNUM_EQ(c2,Hfep_i))
		c = Hfep_o_i;
	    break;
	  case 110:
	    if (FIXNUM_EQ(c2,Hfep_eo))
		c = Hfep_u_eo;
	    if (FIXNUM_EQ(c2,Hfep_e))
		c = Hfep_u_e;
	    if (FIXNUM_EQ(c2,Hfep_i))
		c = Hfep_u_i;
	    break;
	  case 109:
	    if (FIXNUM_EQ(c2,Hfep_i))
		c = Hfep_eu_i;
	    break;
	  default:
	    break;
	}
    return VALUES_1(c);
}

/* HFEP-MIXCONSO */
Object hfep_mixconso(c1,c2)
    Object c1, c2;
{
    Object c, temp;

    x_note_fn_call(124,16);
    c = c1;
    temp = c1;
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 114:
	    if (FIXNUM_EQ(c2,Hfep_s))
		c = Hfep_g_s;
	    break;
	  case 115:
	    if (FIXNUM_EQ(c2,Hfep_j))
		c = Hfep_n_j;
	    if (FIXNUM_EQ(c2,Hfep_h))
		c = Hfep_n_h;
	    break;
	  case 102:
	    if (FIXNUM_EQ(c2,Hfep_g))
		c = Hfep_r_g;
	    if (FIXNUM_EQ(c2,Hfep_m))
		c = Hfep_r_m;
	    if (FIXNUM_EQ(c2,Hfep_b))
		c = Hfep_r_b;
	    if (FIXNUM_EQ(c2,Hfep_s))
		c = Hfep_r_s;
	    if (FIXNUM_EQ(c2,Hfep_t))
		c = Hfep_r_t;
	    if (FIXNUM_EQ(c2,Hfep_p))
		c = Hfep_r_p;
	    if (FIXNUM_EQ(c2,Hfep_h))
		c = Hfep_r_h;
	    break;
	  case 113:
	    if (FIXNUM_EQ(c2,Hfep_s))
		c = Hfep_b_s;
	    break;
	  default:
	    break;
	}
    return VALUES_1(c);
}

void hfep2_INIT()
{
    Object temp, reclaim_structure_for_hfep_hanc_type_1;
    Object AB_package, Qhfep_hanc_type, Qreclaim_structure;
    Object Qoutstanding_hfep_hanc_type_count;
    Object Qhfep_hanc_type_structure_memory_usage, Qutilities2;
    Object string_constant_22, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_21, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12, list_constant;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object Qhfep_eoln, Qhfep_spc, Qhfep_esc, Qhfep_null, Qhfep_u_i, Qhfep_o_i;
    Object Qhfep_i, Qhfep_eu_i, Qhfep_eu, Qhfep_yu, Qhfep_u_e, Qhfep_u;
    Object Qhfep_yo, Qhfep_o_ai, Qhfep_o, Qhfep_ye, Qhfep_yeo, Qhfep_e;
    Object Qhfep_u_eo, Qhfep_eo, Qhfep_yai, Qhfep_ya, Qhfep_ai, Qhfep_o_a;
    Object Qhfep_a, Qhfep_h, Qhfep_p, Qhfep_t, Qhfep_k, Qhfep_c, Qhfep_jj;
    Object Qhfep_j, Qhfep_oo, Qhfep_ss, Qhfep_s, Qhfep_b_s, Qhfep_bb, Qhfep_b;
    Object Qhfep_m, Qhfep_r_h, Qhfep_r_p, Qhfep_r_t, Qhfep_r_b, Qhfep_r_s;
    Object Qhfep_r_m, Qhfep_r_g, Qhfep_r, Qhfep_dd, Qhfep_d, Qhfep_n_h;
    Object Qhfep_n_j, Qhfep_n, Qhfep_g_s, Qhfep_gg, Qhfep_g;

    x_note_fn_call(124,17);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qhfep_g = STATIC_SYMBOL("HFEP-G",AB_package);
    SET_SYMBOL_VALUE(Qhfep_g,FIX((SI_Long)114L));
    Qhfep_gg = STATIC_SYMBOL("HFEP-GG",AB_package);
    SET_SYMBOL_VALUE(Qhfep_gg,FIX((SI_Long)82L));
    Qhfep_g_s = STATIC_SYMBOL("HFEP-G-S",AB_package);
    SET_SYMBOL_VALUE(Qhfep_g_s,FIX((SI_Long)83L));
    Qhfep_n = STATIC_SYMBOL("HFEP-N",AB_package);
    SET_SYMBOL_VALUE(Qhfep_n,FIX((SI_Long)115L));
    Qhfep_n_j = STATIC_SYMBOL("HFEP-N-J",AB_package);
    SET_SYMBOL_VALUE(Qhfep_n_j,FIX((SI_Long)74L));
    Qhfep_n_h = STATIC_SYMBOL("HFEP-N-H",AB_package);
    SET_SYMBOL_VALUE(Qhfep_n_h,FIX((SI_Long)72L));
    Qhfep_d = STATIC_SYMBOL("HFEP-D",AB_package);
    SET_SYMBOL_VALUE(Qhfep_d,FIX((SI_Long)101L));
    Qhfep_dd = STATIC_SYMBOL("HFEP-DD",AB_package);
    SET_SYMBOL_VALUE(Qhfep_dd,FIX((SI_Long)69L));
    Qhfep_r = STATIC_SYMBOL("HFEP-R",AB_package);
    SET_SYMBOL_VALUE(Qhfep_r,FIX((SI_Long)102L));
    Qhfep_r_g = STATIC_SYMBOL("HFEP-R-G",AB_package);
    SET_SYMBOL_VALUE(Qhfep_r_g,FIX((SI_Long)71L));
    Qhfep_r_m = STATIC_SYMBOL("HFEP-R-M",AB_package);
    SET_SYMBOL_VALUE(Qhfep_r_m,FIX((SI_Long)77L));
    Qhfep_r_s = STATIC_SYMBOL("HFEP-R-S",AB_package);
    SET_SYMBOL_VALUE(Qhfep_r_s,FIX((SI_Long)78L));
    Qhfep_r_b = STATIC_SYMBOL("HFEP-R-B",AB_package);
    SET_SYMBOL_VALUE(Qhfep_r_b,FIX((SI_Long)65L));
    Qhfep_r_t = STATIC_SYMBOL("HFEP-R-T",AB_package);
    SET_SYMBOL_VALUE(Qhfep_r_t,FIX((SI_Long)66L));
    Qhfep_r_p = STATIC_SYMBOL("HFEP-R-P",AB_package);
    SET_SYMBOL_VALUE(Qhfep_r_p,FIX((SI_Long)86L));
    Qhfep_r_h = STATIC_SYMBOL("HFEP-R-H",AB_package);
    SET_SYMBOL_VALUE(Qhfep_r_h,FIX((SI_Long)70L));
    Qhfep_m = STATIC_SYMBOL("HFEP-M",AB_package);
    SET_SYMBOL_VALUE(Qhfep_m,FIX((SI_Long)97L));
    Qhfep_b = STATIC_SYMBOL("HFEP-B",AB_package);
    SET_SYMBOL_VALUE(Qhfep_b,FIX((SI_Long)113L));
    Qhfep_bb = STATIC_SYMBOL("HFEP-BB",AB_package);
    SET_SYMBOL_VALUE(Qhfep_bb,FIX((SI_Long)81L));
    Qhfep_b_s = STATIC_SYMBOL("HFEP-B-S",AB_package);
    SET_SYMBOL_VALUE(Qhfep_b_s,FIX((SI_Long)67L));
    Qhfep_s = STATIC_SYMBOL("HFEP-S",AB_package);
    SET_SYMBOL_VALUE(Qhfep_s,FIX((SI_Long)116L));
    Qhfep_ss = STATIC_SYMBOL("HFEP-SS",AB_package);
    SET_SYMBOL_VALUE(Qhfep_ss,FIX((SI_Long)84L));
    Qhfep_oo = STATIC_SYMBOL("HFEP-OO",AB_package);
    SET_SYMBOL_VALUE(Qhfep_oo,FIX((SI_Long)100L));
    Qhfep_j = STATIC_SYMBOL("HFEP-J",AB_package);
    SET_SYMBOL_VALUE(Qhfep_j,FIX((SI_Long)119L));
    Qhfep_jj = STATIC_SYMBOL("HFEP-JJ",AB_package);
    SET_SYMBOL_VALUE(Qhfep_jj,FIX((SI_Long)87L));
    Qhfep_c = STATIC_SYMBOL("HFEP-C",AB_package);
    SET_SYMBOL_VALUE(Qhfep_c,FIX((SI_Long)99L));
    Qhfep_k = STATIC_SYMBOL("HFEP-K",AB_package);
    SET_SYMBOL_VALUE(Qhfep_k,FIX((SI_Long)122L));
    Qhfep_t = STATIC_SYMBOL("HFEP-T",AB_package);
    SET_SYMBOL_VALUE(Qhfep_t,FIX((SI_Long)120L));
    Qhfep_p = STATIC_SYMBOL("HFEP-P",AB_package);
    SET_SYMBOL_VALUE(Qhfep_p,FIX((SI_Long)118L));
    Qhfep_h = STATIC_SYMBOL("HFEP-H",AB_package);
    SET_SYMBOL_VALUE(Qhfep_h,FIX((SI_Long)103L));
    Qhfep_a = STATIC_SYMBOL("HFEP-A",AB_package);
    SET_SYMBOL_VALUE(Qhfep_a,FIX((SI_Long)107L));
    Qhfep_o_a = STATIC_SYMBOL("HFEP-O-A",AB_package);
    SET_SYMBOL_VALUE(Qhfep_o_a,FIX((SI_Long)75L));
    Qhfep_ai = STATIC_SYMBOL("HFEP-AI",AB_package);
    SET_SYMBOL_VALUE(Qhfep_ai,FIX((SI_Long)111L));
    Qhfep_ya = STATIC_SYMBOL("HFEP-YA",AB_package);
    SET_SYMBOL_VALUE(Qhfep_ya,FIX((SI_Long)105L));
    Qhfep_yai = STATIC_SYMBOL("HFEP-YAI",AB_package);
    SET_SYMBOL_VALUE(Qhfep_yai,FIX((SI_Long)79L));
    Qhfep_eo = STATIC_SYMBOL("HFEP-EO",AB_package);
    SET_SYMBOL_VALUE(Qhfep_eo,FIX((SI_Long)106L));
    Qhfep_u_eo = STATIC_SYMBOL("HFEP-U-EO",AB_package);
    SET_SYMBOL_VALUE(Qhfep_u_eo,FIX((SI_Long)74L));
    Qhfep_e = STATIC_SYMBOL("HFEP-E",AB_package);
    SET_SYMBOL_VALUE(Qhfep_e,FIX((SI_Long)112L));
    Qhfep_yeo = STATIC_SYMBOL("HFEP-YEO",AB_package);
    SET_SYMBOL_VALUE(Qhfep_yeo,FIX((SI_Long)117L));
    Qhfep_ye = STATIC_SYMBOL("HFEP-YE",AB_package);
    SET_SYMBOL_VALUE(Qhfep_ye,FIX((SI_Long)80L));
    Qhfep_o = STATIC_SYMBOL("HFEP-O",AB_package);
    SET_SYMBOL_VALUE(Qhfep_o,FIX((SI_Long)104L));
    Qhfep_o_ai = STATIC_SYMBOL("HFEP-O-AI",AB_package);
    SET_SYMBOL_VALUE(Qhfep_o_ai,FIX((SI_Long)72L));
    Qhfep_yo = STATIC_SYMBOL("HFEP-YO",AB_package);
    SET_SYMBOL_VALUE(Qhfep_yo,FIX((SI_Long)121L));
    Qhfep_u = STATIC_SYMBOL("HFEP-U",AB_package);
    SET_SYMBOL_VALUE(Qhfep_u,FIX((SI_Long)110L));
    Qhfep_u_e = STATIC_SYMBOL("HFEP-U-E",AB_package);
    SET_SYMBOL_VALUE(Qhfep_u_e,FIX((SI_Long)78L));
    Qhfep_yu = STATIC_SYMBOL("HFEP-YU",AB_package);
    SET_SYMBOL_VALUE(Qhfep_yu,FIX((SI_Long)98L));
    Qhfep_eu = STATIC_SYMBOL("HFEP-EU",AB_package);
    SET_SYMBOL_VALUE(Qhfep_eu,FIX((SI_Long)109L));
    Qhfep_eu_i = STATIC_SYMBOL("HFEP-EU-I",AB_package);
    SET_SYMBOL_VALUE(Qhfep_eu_i,FIX((SI_Long)77L));
    Qhfep_i = STATIC_SYMBOL("HFEP-I",AB_package);
    SET_SYMBOL_VALUE(Qhfep_i,FIX((SI_Long)108L));
    Qhfep_o_i = STATIC_SYMBOL("HFEP-O-I",AB_package);
    SET_SYMBOL_VALUE(Qhfep_o_i,FIX((SI_Long)76L));
    Qhfep_u_i = STATIC_SYMBOL("HFEP-U-I",AB_package);
    SET_SYMBOL_VALUE(Qhfep_u_i,FIX((SI_Long)66L));
    Qhfep_null = STATIC_SYMBOL("HFEP-NULL",AB_package);
    SET_SYMBOL_VALUE(Qhfep_null,FIX((SI_Long)0L));
    Qhfep_esc = STATIC_SYMBOL("HFEP-ESC",AB_package);
    SET_SYMBOL_VALUE(Qhfep_esc,FIX((SI_Long)27L));
    Qhfep_spc = STATIC_SYMBOL("HFEP-SPC",AB_package);
    SET_SYMBOL_VALUE(Qhfep_spc,FIX((SI_Long)32L));
    Qhfep_eoln = STATIC_SYMBOL("HFEP-EOLN",AB_package);
    SET_SYMBOL_VALUE(Qhfep_eoln,FIX((SI_Long)10L));
    list_constant = STATIC_LIST((SI_Long)2L,FIX((SI_Long)14L),
	    FIX((SI_Long)17L));
    string_constant_9 = 
	    STATIC_STRING("1y13Dylllllllllkkkkkkkk13Dylllllllllmnopqrsk13Dytuvwwwwwwkkkskskk13Dytuvwwwwwwkkkksskk13Dytuvwwwwwwkkkkkskk13Dytuvwwwwwwskkkkkkk");
    string_constant_10 = 
	    STATIC_STRING("13Dytuvwwwwwwkskkkkkk13Dytuvwwwwwwssskkkkk13Dytuvwwwlwwkkkkkkkk13Dylllxlllllmnopqrsk13Dyllllxxlllmnopqrsk13Dyxllxlxlxlmnopqrsk13");
    string_constant_11 = 
	    STATIC_STRING("Dylllllllllmnopqrsk13Dylllllllllmnopqrsk");
    if (Hfep_state == UNBOUND)
	Hfep_state = make_array(3,list_constant,Kinitial_contents,
		regenerate_optimized_constant(LIST_3(string_constant_9,
		string_constant_10,string_constant_11)));
    string_constant_12 = 
	    STATIC_STRING("1y13Dykkkkkkkkkllllllli13Dywwwwwwwwwmmmmmmmj13Dyoooppppppvvvnvnvj13Dyoooppppppvvvvnnvj13Dyoooppppppvvvvvnvj13Dyoooppppppnvvvvvvj");
    string_constant_13 = 
	    STATIC_STRING("13Dyoooppppppvnvvvvvj13Dyoooppppppnnnvvvvj13Dyooopppxppvvvvvvvj13Dyrrrqrrrrrtttttttj13Dyrrrrqqrrrtttttttj13Dyqrrqrqrqrtttttttj13");
    string_constant_14 = 
	    STATIC_STRING("Dyrrrrrrrrrtttttttj13Dysssssssssuuuuuuuj");
    if (Hfep_action == UNBOUND)
	Hfep_action = make_array(3,list_constant,Kinitial_contents,
		regenerate_optimized_constant(LIST_3(string_constant_12,
		string_constant_13,string_constant_14)));
    string_constant_15 = 
	    STATIC_STRING("43sy36C+y36C+y36C+y36C+y37S+y36C+y36C+y36C+y36C+y36C+y36C+y36C+y36C+y36C+y36C+y36C+y38S+y36i+y36C+y39++y36C+y36C+y39i+y36C+y36C+");
    string_constant_16 = 
	    STATIC_STRING("y36C+y36C+y36C+y36C+y36C+y36C+y36C+y38++y36C+y3A++y39C+y37C+y37i+y3B++y36C+y36C+y36C+y36C+y36C+y36C+y36C+y36C+y36C+y38C+y36S+y37");
    string_constant_17 = 
	    STATIC_STRING("++y38i+y36C+y3Ai+y39S+y3AS+y36C+y3AC+y");
    if (Hfep_cho_ksc2c == UNBOUND)
	Hfep_cho_ksc2c = 
		regenerate_optimized_constant(LIST_3(string_constant_15,
		string_constant_16,string_constant_17));
    string_constant_18 = 
	    STATIC_STRING("43sy3Sy37Sy3Sy3Sy3Sy3Sy3Sy33Sy3Sy36Sy33+y34Sy39Sy37+y3=+y31Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy3Sy38Sy3Sy3Sy3Sy3Sy");
    string_constant_19 = 
	    STATIC_STRING("3Sy32Sy3*Sy3=Sy3-+y3ASy39+y35Sy3-Sy30Sy3Sy3Sy3Sy3Sy31+y3Sy3Sy3Sy35+y3Sy");
    if (Hfep_jung_ksc2c == UNBOUND)
	Hfep_jung_ksc2c = 
		regenerate_optimized_constant(LIST_2(string_constant_18,
		string_constant_19));
    string_constant_20 = 
	    STATIC_STRING("43sywy3Fyll3Cyurlqllvxlllno3Hylzllllllllll3Dyl3Ky3Iyst3Oylllllllll3Eymp3Gyl3Ny3Jy3Myl3Ly");
    if (Hfep_jong_ksc2c == UNBOUND)
	Hfep_jong_ksc2c = regenerate_optimized_constant(string_constant_20);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_hfep_hanc_type_g2_struct = 
	    STATIC_SYMBOL("HFEP-HANC-TYPE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhfep_hanc_type = STATIC_SYMBOL("HFEP-HANC-TYPE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_hfep_hanc_type_g2_struct,
	    Qhfep_hanc_type,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qhfep_hanc_type,
	    Qg2_defstruct_structure_name_hfep_hanc_type_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_hfep_hanc_type == UNBOUND)
	The_type_description_of_hfep_hanc_type = Nil;
    string_constant_21 = 
	    STATIC_STRING("43Dy8m83iRy1n83iRy8n8k1l8n0000000ksk0k0");
    temp = The_type_description_of_hfep_hanc_type;
    The_type_description_of_hfep_hanc_type = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_21));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_hfep_hanc_type_g2_struct,
	    The_type_description_of_hfep_hanc_type,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qhfep_hanc_type,
	    The_type_description_of_hfep_hanc_type,Qtype_description_of_type);
    Qoutstanding_hfep_hanc_type_count = 
	    STATIC_SYMBOL("OUTSTANDING-HFEP-HANC-TYPE-COUNT",AB_package);
    Qhfep_hanc_type_structure_memory_usage = 
	    STATIC_SYMBOL("HFEP-HANC-TYPE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_22 = STATIC_STRING("1q83iRy8s83-Xjy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_hfep_hanc_type_count);
    push_optimized_constant(Qhfep_hanc_type_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_22));
    Qchain_of_available_hfep_hanc_types = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-HFEP-HANC-TYPES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_hfep_hanc_types,
	    Chain_of_available_hfep_hanc_types);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_hfep_hanc_types,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qhfep_hanc_type_count = STATIC_SYMBOL("HFEP-HANC-TYPE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhfep_hanc_type_count,Hfep_hanc_type_count);
    record_system_variable(Qhfep_hanc_type_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_hfep_hanc_types_vector == UNBOUND)
	Chain_of_available_hfep_hanc_types_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qhfep_hanc_type_structure_memory_usage,
	    STATIC_FUNCTION(hfep_hanc_type_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_hfep_hanc_type_count,
	    STATIC_FUNCTION(outstanding_hfep_hanc_type_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_hfep_hanc_type_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_hfep_hanc_type,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qhfep_hanc_type,
	    reclaim_structure_for_hfep_hanc_type_1);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("CG~c~c");
    string_constant_1 = STATIC_STRING("CD~c~c");
    string_constant_2 = STATIC_STRING("NW~c~c");
    string_constant_3 = STATIC_STRING("NN~c~c");
    string_constant_4 = STATIC_STRING("NE~c~c");
    string_constant_5 = STATIC_STRING("CW~c~c");
    string_constant_6 = STATIC_STRING("NG~c~c");
    string_constant_7 = STATIC_STRING("CF~c~c");
    string_constant_8 = STATIC_STRING("NF~c~c");
}
